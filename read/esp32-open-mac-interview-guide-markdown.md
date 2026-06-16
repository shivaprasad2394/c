# esp32-open-mac — Open-Source Wi-Fi MAC on the ESP32

### Driver Internals, Packet Hand-over & 2.4 GHz Coexistence

*Principal-Level Technical Interview Study Guide*

> Grounded in a working **SoftMAC + AP + BLE-coexistence** build (ESP-IDF v5.0.1, plain ESP32).
>
> **Scope:** SoftMAC architecture · register-level RX/TX · STA/AP state machines · DHCP hand-over · PTA / TDMA / DCF coexistence.

---

## Contents

**Part 1 — Wi-Fi Driver Internals & the esp32-open-mac Architecture**
- 1.1  SoftMAC vs. the Closed-Source Architecture
- 1.2  The openmac Execution Flow — Boot to RX/TX Loops
- 1.3  The RX/TX Pipe & Register Manipulation
- 1.4  Smart Frames — the TX Buffer Pool
- 1.5  Wi-Fi MAC Timing — DCF, SIFS/DIFS, CW, Backoff, CCA & TSF
- 1.6  Block-by-Block: What Each Part Does on TX and RX

**Part 2 — State-Machine Control & Packet Hand-over (PHY → L3 / DHCP)**
- 2.1  Station Connection & DHCP Hand-over Flow
- 2.2  AP-Mode Beaconing & Frame Routing
- 2.3  Commercialisation vs. Custom R&D — Decoupling the Boundaries

**Part 3 — Advanced Coexistence & Hardware Protocols**
- 3.1  PTA — Packet Traffic Arbitration
- 3.2  TDMA for Coexistence — and the Software TDM This Build Uses
- 3.3  Hardware Slots & Backoff Timers — DCF in Silicon

**Appendix A — Rapid-Fire Recall & Likely Grilling Points**

---

# Part 1 — Wi-Fi Driver Internals & the esp32-open-mac Architecture

This part establishes the mental model an interviewer will probe first: **where the silicon ends, where Espressif’s binary blobs historically sat, and exactly which seam esp32-open-mac cuts to insert open C code.** Everything that follows is grounded in the working build — a plain ESP32, ESP-IDF v5.0.1, AP mode live, a NimBLE controller advertising, and a software time-division scheme keeping the two radios out of each other’s way.

## 1.1  SoftMAC vs. the Closed-Source Architecture

**Why the ESP32 is fundamentally a SoftMAC part.** In 802.11 terminology a FullMAC NIC implements the entire MAC sublayer — scanning, authentication, association, retransmission, ACK generation, power-save — inside the device firmware, exposing only an Ethernet-like interface to the host. A SoftMAC NIC implements only the timing-critical *lower MAC* (PHY framing, the DCF backoff/ACK state machine, TSF) in hardware, and leaves the *upper MAC* (management frames, the connection state machine, sequence control) to software running on the host CPU. The ESP32 has no dedicated MAC coprocessor with its own firmware image: the 802.11 MAC logic executes on the same Xtensa LX6 cores as your application, driven by Espressif’s libraries. That is the definition of SoftMAC, and it is precisely what makes the chip reverse-engineerable — the MAC is just code on a CPU you already control.

It helps to see FullMAC and SoftMAC as two ends of a spectrum defined by **where the MAC/host interface is drawn**. On a FullMAC part (most USB/SDIO Wi-Fi dongles, many smartphone combo chips) the NIC firmware terminates 802.11 entirely and the host driver speaks a vendor command interface plus an 802.3 (Ethernet) data path — the host never sees a management frame. On a classic SoftMAC part (Atheros ath9k, the mac80211 model in Linux) the device exposes the PHY and the hard-real-time lower MAC, and the host’s `mac80211` layer implements the upper MAC in software. The ESP32 sits at the SoftMAC end, but with an unusual twist: there is no separate host — the ‘host driver’ and the ‘device’ are the **same two CPU cores**, so the MAC software and the application share cache, RAM, and scheduler. This is why task priority and core pinning (Section 1.2) are first-class correctness concerns here in a way they never are on a discrete NIC.

**What ‘MAC on the CPU’ actually costs and buys.** Because the upper MAC is ordinary code, every management decision — when to send a beacon, how to answer a probe, whether to accept an association — is observable, patchable, and yours. That is the entire premise of esp32-open-mac. The flip side is that anything the CPU is too slow or too jittery to do must stay in silicon: the SIFS-bounded ACK (~10 µs turnaround), the per-slot backoff countdown (9/20 µs granularity), and the TSF timestamp written into a beacon at the instant of transmission. The dividing line between open code and the blob is therefore not ideological — it is a **latency budget**. Anything with a microsecond deadline is hardware; anything with a millisecond budget is software.

**The historical boundary line.** Espressif ships the Wi-Fi stack as a set of pre-compiled static archives linked into your firmware. The two that matter:

- `libnet80211.a` — the **upper MAC / SME** (Station Management Entity): the connection state machines, management-frame construction and parsing, the scan engine, AMPDU/BA sessions, crypto key management, power-save. This is ‘the brain.’
- `libpp.a` — the **‘packet processor’ / lower MAC + HAL**: the layer that drives the MAC hardware registers, owns the RX/TX DMA descriptor rings, fields the WMAC interrupt, talks to the PHY, and enforces the microsecond-scale DCF timing. This is ‘the hands.’
Below `libpp.a` sits the PHY/RF blob (`libphy.a` plus ROM functions) which performs RF calibration, channel synthesis, AGC, and TX power control — analog-domain work that cannot realistically be reimplemented in open code. The chip’s memory-mapped MAC peripheral begins at `0x3ff73000` and is the true hardware boundary: above it is software (open or blob), below it is silicon. The diagram below shows the whole subsystem end-to-end — the two CPU-side tasks, the MMIO register banks the open driver pokes, the closed PHY blobs, and the shared analog front-end — so the rest of Part 1 can refer to concrete blocks rather than abstractions.

![Figure 1](images/fig01-wifi-subsystem-datapath.png)

**Figure 1.**  *The ESP32 Wi-Fi subsystem as a connected datapath. Open C software on core 0 (left) drives the digital MAC peripheral over the CPU bus by reading and writing memory-mapped registers (centre); the MAC peripheral contains the DCF timing engine in silicon and hands symbols to the closed-source PHY (right), which converts them to the analog waveform driven onto the shared 2.4 GHz antenna. Register names and addresses are exactly those used by hardware.c.*

**Where esp32-open-mac cuts.** The project draws the line **inside what used to be libpp.a**. It discards `libnet80211.a` entirely and reimplements the upper MAC as open C (your `80211_mac.c` state machine). It discards most of `libpp.a` and reimplements the lower-MAC HAL — descriptor rings, register pokes, the interrupt handler, MAC-address filtering — as open C (your `hardware.c`). What it **keeps** is the irreducible analog floor: PHY calibration and RF control, plus a few ROM/peripheral bring-up helpers. The residual closed symbols are explicitly enumerated in the project’s headers:

```text
proprietary.h  /  hwinit.c  — residual closed-source symbols still linked in
────────────────────────────────────────────────────────────────────────────
  PHY / RF (analog, never reimplemented):
      esp_phy_load_cal_and_init()   chip_v7_set_chan_nomac(ch, 0)
      esp_phy_common_clock_enable() disable_wifi_agc() / enable_wifi_agc()
      tx_pwctrl_background()        phy_get_romfuncs()
 
  Power / clock / peripheral bring-up (one-shot at boot):
      esp_wifi_power_domain_on()    wifi_module_enable()
      periph_module_reset(0x19)     hal_init()  ic_enable_rx()
      ic_mac_init() (we re-do this open: IC_MAC_INIT_REG &= 0xffffe800)
 
  Coexistence ROM glue (present, but PTA deliberately NOT enabled — see Part 3):
      coex_bt_high_prio()           esp_coex_adapter_register()
 
  Interrupt plumbing:  _xt_interrupt_table[]   config_get_wifi_task_core_id()
```

Everything above that floor — frame formatting, the DCF-driving register sequence, the descriptor rings, RX dispatch, and the entire 802.11 management state machine — is open and is what you have customised.

> **INTERVIEW HOOK**  If asked “is the ESP32 SoftMAC or FullMAC?”, the precise answer is: **hardware-assisted SoftMAC**. The silicon implements the DCF slot/SIFS/ACK timing and TSF in a state machine (too fast for software), but everything above the per-frame timing — including the connection state machine — is software. esp32-open-mac proves this by replacing the software half wholesale while keeping the hardware timing engine untouched.

## 1.2  The openmac Execution Flow — Boot to RX/TX Loops

The runtime is a **two-task pipeline** pinned to core 0, fed by one hardware ISR and decoupled by two FreeRTOS queues. Understanding the hand-offs between them is the core of the architecture.

### 1.2.1  Boot & initialisation order

The ordering in `app_main()` is deliberate and is a favourite interview trap. BLE is brought up **before** Wi-Fi:

```text
app_main()  (main.c)                              rationale
──────────────────────────────────────────────   ───────────────────────────────
 1  phy_version assert == "4670,719f9f6,..."       fail fast on wrong PHY blob
 2  nvs_flash_init()                               PHY cal data + BLE NVS live here
 3  esp_netif_init();  esp_event_loop_create()     IP stack + event pump
 4  register IP_EVENT_AP_STAIPASSIGNED handler     fires when a client gets a lease
 5  coexistence_init()                             create BLE-done semaphore (scaffold)
 6  custom_ble_init()        ◄── BLE FIRST         NimBLE calls esp_phy_load_cal_and_init()
 7  xTaskCreatePinnedToCore(wifi_hardware_task,    prio 23, core 0  ── starts HW + spawns
                            ...,prio 23, core 0)                       the MAC task
 8  openmac_netif_start()                          create AP netif, attach IO driver
 
 WHY BLE FIRST: the BLE controller's init re-runs PHY calibration. If Wi-Fi
 configured the channel/PHY first, BLE would clobber it. Initialising BLE first
 means Wi-Fi's hwinit() (channel set to 6, MAC regs) is applied LAST and wins.
```

**Why the order is fragile, step by step.** Several of these steps have a hard dependency on an earlier one, and getting the order wrong produces a specific, recognisable failure — which is exactly what an interviewer will probe:

- **NVS before either radio.** `esp_phy_load_cal_and_init()` reads stored RF calibration data from NVS; if `nvs_flash_init()` hasn’t run (or the partition is corrupt and wasn’t erased/retried), PHY init falls back to a full re-calibration or fails outright. The BLE controller also stores its own NVS keys, so a missing NVS surfaces as a confusing BLE-init error rather than an obvious storage error.
- **Event loop before netif actions.** The default event loop must exist before `openmac_netif_start()` and before the DHCP server can post `IP_EVENT_AP_STAIPASSIGNED`; register the handler too late and the very first client’s lease event is silently dropped.
- **BLE before Wi-Fi hwinit — the headline.** Both radios share one PHY. BLE controller init calls into the same `esp_phy_load_cal_and_init()` path and leaves the PHY tuned for BLE’s needs. If Wi-Fi’s `hwinit()` (which ends by setting channel 6 and the MAC/TSF registers) runs first, BLE init silently overwrites the channel synth and AGC state and Wi-Fi goes deaf — beacons transmit but no client ever associates. Bringing BLE up first means Wi-Fi’s configuration is applied *last* and is the one that survives.
- **Coex scaffold is initialised but inert.** Step 5 creates the semaphore used by `coexistence_control.c`, but as Part 3 explains, PTA is deliberately never enabled; the actual coexistence mechanism is the software TDM watchdog started inside the hardware task at step 7.
> **INTERVIEW HOOK**  The crisp framing: “BLE-before-Wi-Fi isn’t a preference, it’s a **last-writer-wins** arrangement on a shared PHY. Whichever radio configures the channel synth and AGC last owns the air. I order init so Wi-Fi’s `hwinit()` is the last writer, then the runtime TDM watchdog re-asserts Wi-Fi’s PHY state every time BLE has been allowed a window (Part 3.2).”

The hardware task itself runs the low-level bring-up and then spawns the MAC task:

```text
wifi_hardware_task()  (hardware.c)          c_mac_task()  (80211_mac_interface.c)
─────────────────────────────────────       ─────────────────────────────────────
 hardware_event_queue = xQueueCreate()        interface_init():
 rx_queue_resources  = counting sem(10)          - rust_mac_event_queue (35 slots)
 tx_queue_resources  = counting sem(10)          - 5 TX smart-frame buffers (2352B)
 hwinit()  ──► see below                         - 5 RX frame buffers (2304B)
 setup_interrupt()  (WMAC ISR)                 rust_mac_task():
 setup_rx_chain()   (10 × 1600B DMA bufs)         filters_set_ap_mode(1, AP_MAC)
 disable all MAC/BSSID filters initially          change_channel_to(6)
 change_channel_to(6)   ◄ first beacon RF         loop: rs_get_next_mac_event_raw()
 xTaskCreatePinnedToCore(c_mac_task,                     -> handle RX / TX / beacon
        "rs_wifi", 16384, prio 22, core 0)  ───────────────────┘
 loop: drain hardware_event_queue + run TDM coex watchdog
 
 hwinit():  adc2_wifi_acquire(); [SKIP coex_init — PTA OFF]; wifi_hw_start_openmac(0):
   power_domain_on -> module_enable -> esp_phy_enable_openmac (clock+cal+bt_high_prio)
   -> periph_module_reset(0x19) -> clear bit31 of MAC_BITMASK_084 -> ic_mac_init
   -> hal_init -> ic_enable_rx ;  then _do_wifi_start_openmac -> hal_mac_tsf_reset(0)
```

### 1.2.2  The two-task split and why it exists

This is a classic **top-half / bottom-half** decomposition extended across two cooperating tasks:

- **Hardware task (prio 23) — the “bottom half + register driver.”** It owns all MMIO. It services the WMAC interrupt’s deferred work (walking the RX descriptor ring, reaping completed TX slots), performs the actual TX register sequence on request, changes channel, and runs the coexistence watchdog. It must never block on the network stack.
- **MAC task (prio 22) — the “802.11 brain.”** It runs the connection/AP state machine, parses received management/data frames, builds beacons/auth/assoc responses, and decides *what* to transmit. It never touches a hardware register directly; it calls `rs_tx_smart_frame()` / `rs_change_channel()` which marshal work to the hardware task.
The two are decoupled by **two queues**, which is what keeps an ISR-rate event source from stalling the slower MAC logic and vice-versa. The layered architecture and the concurrency hand-offs are shown below:

![Figure 2](images/fig02-openmac-layering-tasks.png)

**Figure 2.**  *openmac layering and the two-task / two-queue concurrency model. The hardware task owns every register; the MAC task owns policy; the WMAC ISR and the two FreeRTOS queues isolate the SIFS/TBTT deadline from lwIP latency. PHY/RF stays closed-source below the open/closed boundary.*

Backpressure is enforced with counting semaphores (`rx_queue_resources`, `tx_queue_resources`, both depth 10). The ISR only enqueues an RX event if it can take an RX resource token; the token is returned when the hardware task finishes draining that interrupt. This bounds the in-flight RX work and prevents the queue from growing without limit under a packet flood.

### 1.2.3  The steady-state RX and TX loops

Before tracing the loops, it is worth pinning down four pieces of vocabulary that recur constantly — **WMAC**, **DMA**, the **descriptor ring**, and **TX slots** — because the rest of Part 1 leans on them. They are the hardware nouns the open driver manipulates; the diagram below defines each one in place, with a one-line glossary underneath.

![Figure 3](images/fig03-four-hardware-concepts.png)

**Figure 3.**  *The four core hardware concepts. WMAC is the Wi-Fi MAC peripheral; the DMA engine moves frame bytes between SRAM and the radio without the CPU; the RX descriptor ring is a 10-entry linked list the hardware fills and software drains; the five TX slots are independent launch pads, each with its own PLCP/CONFIG registers. The CPU only sets up descriptors and slot registers — the WMAC does the timed work and raises an interrupt.*

### 1.2.3.1  RX and TX, step by step

**RX loop** (air → MAC task): the PHY DMAs a received frame into the next free descriptor in the ring and raises the WMAC interrupt. The ISR is intentionally tiny — it reads/clears the cause register and posts a `RX_ENTRY`. The hardware task’s `handle_rx_messages()` then walks the descriptor chain while `has_data` is set, unlinks each filled descriptor, and hands it up via `c_hand_rx_to_mac_stack()`, which enqueues a `EVENT_TYPE_PHY_RX_DATA` carrying the `dma_list_item*`. The MAC task pops it, checks the hardware `filter_match` bits, parses the 802.11 header, and either replies (management) or pushes payload to lwIP (data), then recycles the descriptor with `rs_recycle_dma_item()`.

**TX loop** (MAC task → air): the MAC task obtains a pre-allocated `rs_smart_frame_t` from the pool of five, fills the 802.11 bytes, and calls `rs_tx_smart_frame()` → `transmit_80211_frame()`. The hardware task finds a free TX slot, computes the FCS in software, writes the descriptor and the PLCP/CONFIG registers, and finally sets the GO bits. A TX-complete interrupt later sets a bit in the TXQ-complete register; `processTxComplete()` reaps the slot and recycles the smart frame. Stale slots are swept by a 50 ms timeout in the hardware-task idle path — this timeout is also the trigger for the coexistence watchdog (Part 3).

## 1.3  The RX/TX Pipe & Register Manipulation

This section is the register-level heart of the driver and the area where an interviewer can verify you actually understand the hardware rather than the abstraction. All offsets below are taken directly from the working `hardware.c`.

### 1.3.1  The MAC peripheral register map (the parts that matter)

The MAC peripheral is a bank of memory-mapped 32-bit registers based at `0x3ff73000`. The open driver never calls a vendor API to transmit or receive — it reads and writes these words directly, which is what makes the data path fully inspectable. The registers fall into five functional groups: **interrupt/DMA control** (what woke us), the **RX descriptor-ring pointers**, the **per-slot TX engine**, the **address/BSSID filters**, and **TSF/timing**. The table lists the ones `hardware.c` actually touches:

| **Symbol** | **Address** | **Role** |
|---|---|---|
| `WIFI_DMA_INT_STATUS` | 0x3ff73c48 | RX/TX interrupt cause bitmap (read in ISR) |
| `WIFI_DMA_INT_CLR` | 0x3ff73c4c | Write-1-to-clear interrupt cause |
| `WIFI_BASE_RX_DSCR` | 0x3ff73088 | Head pointer of RX DMA descriptor ring |
| `WIFI_NEXT/LAST_RX_DSCR` | 0x3ff7308c / 90 | HW cursor into the RX ring |
| `MAC_TX_PLCP0[slot]` | 0x3ff73d20, −8/slot | TX descriptor ptr + GO bits (0xC0000000) |
| `WIFI_TX_CONFIG[slot]` | 0x3ff73d1c, −8/slot | Per-slot TX enable / arm bits |
| `MAC_TX_PLCP1[slot]` | 0x3ff74258, −60/slot | Length, PHY rate, HT flag, key slot |
| `MAC_TX_PLCP2 / DURATION` | 0x3ff7425c / 268 | PLCP service field / NAV duration |
| `WIFI_TXQ_GET_STATE_COMPLETE` | 0x3ff73cc8 | Per-slot TX-done bitmap |
| `WIFI_MAC_BITMASK_084` | 0x3ff73084 | bit0=RX-chain reload, bit31=TSF beacon stamp |
| `WIFI_MAC_ADDR_SLOT_0` | 0x3ff73040 (+8/slot) | Per-interface RX MAC-address filter + ACK |
| `WIFI_BSSID_FILTER_SLOT_0` | 0x3ff73000 | Per-interface BSSID filter |
| `MAC_CTRL_REG` | 0x3ff73cb8 | MAC enable/deinit (used around channel change) |

**Reading the strides.** The `[slot]` registers are arrays addressed by a signed stride, which trips people up. The TX engine has five slots, and consecutive slots step *downward* in memory: `MAC_TX_PLCP0[n] = 0x3ff73d20 − 8·n`, `MAC_TX_PLCP1[n] = 0x3ff74258 − 60·n`. The filter banks step *upward*: `WIFI_MAC_ADDR_SLOT_0 + 8·iface`. Mixing up the sign of the stride writes a neighbouring slot’s control word and manifests as ‘the wrong frame transmitted’ or ‘TX on a slot I never armed’ — a nasty class of bug because the build still compiles and mostly works. The macros in `hardware.c` (built on `_MMIO_DWORD` / `_MMIO_ADDR` from `hardware.h`) encapsulate the arithmetic so the strides live in exactly one place.

### 1.3.2  Transmit — the exact register choreography

A frame is launched by writing a DMA descriptor and then a precise sequence of PLCP/CONFIG words. Note two project-specific quirks worth calling out in interview: the FCS is computed in **software** (hardware CRC is disabled), and the firing bit pattern is `0xC0000000` in PLCP0 — the “GO” signal also visible in the beacon timing diagram.

```text
transmit_80211_frame(frame)                       hardware.c
────────────────────────────────────────────────────────────────────────────
 1  pick first free TX slot (of 5); mark in_use; bind frame -> slot
 2  crc = calculate_crc32(payload, len);  append 4-byte FCS  (SW CRC)
       actual_len = payload_length + 4 ;  size = actual_len + 32
 3  build DMA descriptor in slot:
       owner=1; has_data=1; length=actual_len; size; packet=payload; next=NULL
 4  WIFI_TX_CONFIG[slot] |= 0xA                  ; arm config
 5  MAC_TX_PLCP0[slot]    = (desc_addr & 0xFFFFF) | 0x0  ; (HW CRC disabled = 0)
 6  MAC_TX_PLCP1[slot]    = 0x10000000
                          | (actual_len & 0xFFF)         ; length
                          | ((rate & 0x1F) << 12)        ; PHY rate index
                          | ((is_ht & 1) << 25)          ; HT vs legacy
                          | ((key_slot & 0x1F) << 17)    ; crypto key (0 = open)
 7  MAC_TX_PLCP2[slot]    = 0x20   ; MAC_TX_DURATION[slot] = 0  (HW fills NAV)
 8  (if HT) write HT-SIG + HT-unknown words
 9  WIFI_TX_CONFIG[slot] |= 0x02000000 ; |= 0x00003000     ; enable + queue
10  MAC_TX_PLCP0[slot]   |= 0xC0000000     ◄── "GO": hand slot to DCF engine
11  tx_slot_timestamps[slot] = esp_timer_get_time()        ; for stale sweep
────────────────────────────────────────────────────────────────────────────
 After step 10 the HARDWARE owns the frame: it runs CCA, DIFS, random backoff,
 transmits at the PLCP1 rate, awaits an ACK, retransmits on failure — all in
 silicon. Software is not involved again until the TX-complete interrupt.
```

**Decoding the PLCP words.** The three PLCP registers are the hardware’s description of how to put the frame on air. `PLCP0` carries the low 20 bits of the DMA descriptor address plus, in its top two bits, the GO signal that hands the slot to the DCF engine. `PLCP1` is the densest: bits 0–11 are the byte length (payload + 4-byte FCS), bits 12–16 select the PHY rate from the rate table (e.g. 1 Mbps long-preamble for beacons), bit 25 chooses HT vs. legacy framing, and bits 17–21 name the hardware crypto key slot (0 means open/no encryption, which is what this build uses). `PLCP2` holds the PLCP service field; `MAC_TX_DURATION` is left 0 because the hardware computes and inserts the 802.11 Duration/NAV value itself. The diagram lays out the exact bit fields:

![Figure 4](images/fig04-tx-plcp-bitfields.png)

**Figure 4.**  *Bit-field layout of the TX PLCP registers written per slot. PLCP0 = GO bits + descriptor address; PLCP1 packs the base flag, HT bit, crypto key slot, PHY rate index and length; PLCP2 is the service field; DURATION is left zero so the silicon fills the NAV. Software states intent here; the hardware owns the timing.*

**The ordering is an invariant, not a style.** The GO write in step 10 must be **last**. Every field the DCF engine and PHY will consume — descriptor pointer, length, rate, config arming — has to be committed before the top two bits of `PLCP0` are raised, because the instant they go high the hardware may begin CCA and latch the descriptor. Setting GO in the same write as the descriptor pointer, or arming `WIFI_TX_CONFIG` after GO, races the hardware and produces sporadic malformed transmissions that are maddening to reproduce. Treating ‘fill everything, then fire’ as a strict barrier is the correct mental model, and on this single-core-ordered MMIO path the natural write order is sufficient (no explicit memory fence is required, though a `volatile` access — which `_MMIO_DWORD` guarantees — is).

**GOTCHA**  Computing the FCS in software and disabling the hardware CRC is unusual and an interviewer may push on it: it costs a CRC32 pass per frame on the CPU but sidesteps a hardware-FCS configuration that was not behaving on this register layout. The `size = len + 32` padding leaves head-room the PHY expects beyond the descriptor’s logical length. Be ready to justify the trade-off (correctness/observability now, micro-optimise later).

### 1.3.3  Receive — the descriptor ring and DMA hand-off

RX is a singly-linked ring of `dma_list_item` descriptors (10 buffers of 1600 B). The PHY fills the next free descriptor, sets its `has_data` bit, advances its internal cursor, and raises the WMAC interrupt. Re-arming the chain after consuming a descriptor is done by toggling bit 0 of `MAC_BITMASK_084` and spinning until the hardware clears it (a hardware ‘reload’ handshake).

![Figure 5](images/fig05-rx-dma-descriptor-chain.png)

**Figure 5.**  *The RX DMA descriptor chain. setup_rx_chain() builds ten descriptors; the PHY fills the next free buffer, sets has_data, and fires the WMAC interrupt; the hardware task walks the chain and hands filled descriptors to the MAC stack; rs_recycle_dma_item() relinks an emptied buffer at the tail and commits with MAC_BITMASK_084 |= 0x1.*

The RX metadata header `wifi_pkt_rx_ctrl_openmac_t` is a reverse-engineered bitfield struct prepended to every received buffer, carrying RSSI, PHY rate, `sig_len` (length incl. FCS), the primary channel, and crucially the `filter_match` field that tells software which hardware filter slot accepted the frame.

### 1.3.4  Hardware MAC-address filtering — the replacement for promiscuous mode

Early open-MAC work received *everything* in promiscuous mode and filtered in software, which wastes CPU and, more importantly, cannot auto-generate ACKs (ACKs must go out within SIFS, far faster than software can react). The project reverse-engineered the per-interface **address-match slots** so the hardware both filters RX and auto-ACKs. There are `NUM_VIRTUAL_INTERFACES = 2` slots, mirroring the two virtual interfaces (e.g. STA + AP).

```text
Per-slot filter programming (hardware.c)
────────────────────────────────────────────────────────────────────────────
 set_mac_addr_filter(slot, addr):
     WIFI_MAC_ADDR_SLOT_0 + slot*8      = addr[0..3]
     WIFI_MAC_ADDR_SLOT_0 + slot*8 + 4  = addr[4..5]
     WIFI_MAC_ADDR_SLOT_0 + slot*8 +32  = 0xFFFFFFFF   (mask: match all bits)
     ACK_ENABLE_SLOT_0    + slot*8     |= 0xFFFF       (auto-ACK on match)
 set_enable_mac_addr_filter(slot,en):  ACK_ENABLE |= / &= ~0x10000
 set_bssid_filter(slot, addr):  programs BSSID match @ 0x3ff73000 region
 
 Three role presets compose these primitives:
   scanning_mode : own MAC + own BSSID, rx_policy ON   (hear everything addressed loosely)
   client_mode   : own MAC + AP's BSSID, rx_policy OFF (only my BSS)
   ap_mode       : BSSID filter on AP MAC, rx_policy OFF,
                   + hal_mac_tsf_reset(1)  + MAC_BITMASK_084 |= 0x80000000
                                                    └─ enable HW TSF beacon stamping
```

The `filter_match` bits in the RX header report which slot matched, so the MAC task can demultiplex frames to the correct virtual interface without re-parsing addresses. The AP-mode preset additionally resets the TSF timer and sets bit 31 of `MAC_BITMASK_084`, which arms the hardware to stamp the 8-byte Timestamp field of outgoing beacons/probe-responses with the live TSF — the single most timing-critical thing an AP must get right, offloaded entirely to silicon.

**The mask register is the subtle part.** Each slot has not just an address but a 32-bit *match mask* (written to `slot*8 + 32`). Writing `0xFFFFFFFF` means ‘every bit of the address must match’ — an exact unicast match. A narrower mask lets one slot match a *range* of addresses, which is how multicast/broadcast acceptance is expressed without burning a dedicated slot: the broadcast and multicast bit patterns are admitted by relaxing the mask rather than by adding entries. With only `NUM_VIRTUAL_INTERFACES = 2` exact-match slots available, the mask is the only way to accept the several address classes (own unicast, broadcast, the multicast groups DHCP and ARP need) that even a minimal AP must hear.

**Why three presets, not a free-for-all.** The `rx_policy` flag toggles how permissive the accept logic is, and each role wants a different posture. **Scanning** turns the policy *on* so the station hears beacons and probe-responses from any BSS while it looks for its target SSID — necessary because before association you don’t yet know the BSSID to filter on. **Client** mode, once associated, turns the policy *off* and pins the BSSID filter to the AP, so the radio stops waking the CPU for every nearby network — a power and CPU win. **AP** mode filters on its own BSSID, turns the policy off, and additionally arms TSF stamping. The presets exist so the MAC task can switch roles with a single call (`rs_filters_set_scanning / _client / _ap_mode`) rather than re-deriving a dozen register writes at each state transition — and so the auto-ACK enable is never accidentally left on for an address the stack can’t actually service.

> **INTERVIEW HOOK**  “Why not just stay in promiscuous mode and filter in software?” — Because **auto-ACK has a SIFS deadline (~10 µs)**. A frame addressed to us must be acknowledged before the sender’s ACK-timeout or it retransmits and the link collapses. Only the hardware filter can decide ‘this is for me’ and emit the ACK inside SIFS. Software filtering can classify, but it can never ACK in time.

## 1.4  Smart Frames — the TX Buffer Pool

Every transmitted frame travels in a `rs_smart_frame_t` — a buffer plus its PHY metadata (rate, valid length, capacity). Five of them are allocated once in `interface_init()` and recycled forever, so the data path performs **zero TX-buffer allocation at steady state**. A second tracker, the five hardware `tx_slots[]`, binds a smart frame to a DMA descriptor while the radio owns it. Understanding this pool is the key to the whole TX story: it is the unit the MAC task fills, the hardware task fires, and the TX-complete interrupt recycles.

![Figure 6](images/fig06-smart-frame-lifecycle.png)

**Figure 6.**  *The smart-frame lifecycle. rs_get_smart_frame() leases a free buffer from the pool of five; the MAC task fills the 802.11 bytes and rate; rs_tx_smart_frame() → transmit_80211_frame() binds it to a hardware TX slot and sets the GO bit; the TX-complete IRQ runs c_recycle_tx_smart_frame() to return it to the pool. A 50 ms stale-slot sweep is the safety net — and the trigger for BLE coexistence recovery.*

**Why a fixed pool rather than malloc-per-frame.** Allocating on the TX path would couple frame transmission to heap latency and fragmentation — unacceptable when a beacon must go out on a 102.4 ms cadence and an ACK within SIFS. A pre-sized pool gives constant-time `rs_get_smart_frame()` (a linear scan of five `in_use` flags) and a constant-time recycle. The cost is a hard ceiling of five in-flight TX frames; if all five are busy, `transmit_80211_frame()` returns false and the caller must retry — which is exactly what makes the stale-slot sweep necessary.

**The recycle paths.** There are two ways a slot frees: the happy path is `processTxComplete()`, which reads `WIFI_TXQ_GET_STATE_COMPLETE`, finds the finished slot with `31 − __builtin_clz()`, and calls `c_recycle_tx_smart_frame()`. The unhappy path is the idle-branch sweep: any slot held longer than 50 ms is force-recycled (the frame is dropped). Three consecutive sweep cycles with timeouts is the heuristic that BLE has seized the radio, escalating into the coexistence recovery covered in Part 3.

## 1.5  Wi-Fi MAC Timing — DCF, SIFS/DIFS, CW, Backoff, CCA & TSF

This section is a from-first-principles tour of the 802.11 timing rules, because the whole open/closed split, the smart-frame stale-sweep, and the coexistence design in Part 3 only make sense once these are second nature. The unifying idea: 802.11’s basic access method is **CSMA/CA** — Carrier Sense Multiple Access with Collision *Avoidance*. Unlike wired Ethernet, a radio cannot listen while it transmits, so it cannot detect a collision mid-frame; it must instead **avoid** them by sensing the medium, waiting a mandated idle gap, and backing off a random amount before transmitting. The function that implements this is the **DCF (Distributed Coordination Function)**, and on the ESP32 it runs entirely in silicon.

### 1.5.1  The building blocks

- **CCA (Clear Channel Assessment).** The PHY’s continuous answer to ‘is the medium busy?’ — by RF energy detection and/or decoding a valid preamble. Every timing rule below is gated on CCA: idle time only accrues while CCA says clear.
- **Slot time (9 µs OFDM / 20 µs DSSS).** The quantum of contention. Backoff is counted in whole slots, and the interframe spaces are defined as multiples of it.
- **SIFS (~10 µs).** The shortest interframe space, used between the pieces of one exchange — notably before an ACK. Because it is the shortest, a station sending an ACK after SIFS always seizes the medium before any station waiting the longer DIFS could start. SIFS is how 802.11 gives in-flight exchanges priority over new ones.
- **DIFS (= SIFS + 2 × slot).** The idle gap a station must observe before it may begin contending for a *new* transmission. The two-slot penalty over SIFS is deliberate: it guarantees ACKs and other SIFS-spaced responses win.
- **Contention Window (CW: CWmin=15 … CWmax=1023).** The integer range from which the random backoff is drawn. It starts at CWmin and **doubles on every failed transmission** (binary exponential backoff), resetting to CWmin after a success. Widening CW under load statistically spreads retransmissions and reduces repeat collisions.
- **Backoff.** A counter set to `random(0, CW)` slots. It decrements once per idle slot and **freezes (does not reset)** whenever CCA goes busy, resuming after the medium is idle for DIFS again. Reaching zero is the moment of transmission.
- **TSF (Timing Synchronisation Function).** A 64-bit microsecond counter maintained in hardware. The AP writes its live TSF into the Timestamp field of every beacon (the bit-31 stamp of `MAC_BITMASK_084` from §1.3.4); clients slave their own TSF to it, which is what keeps power-save wake-ups and the whole BSS on a common clock.
### 1.5.2  How they compose on a transmission

The diagram shows three canonical scenarios: a clean transmit-and-ACK, a failure that doubles the contention window, and a backoff that freezes mid-countdown when another station grabs the medium.

![Figure 7](images/fig07-dcf-timing-scenarios.png)

**Figure 7.**  *DCF timing in three scenarios. (1) A station waits DIFS, counts down a random backoff, transmits, and the receiver replies after only SIFS — so the ACK always wins the medium. (2) No ACK arrives: the contention window doubles and a wider random backoff is drawn before the retransmit. (3) The backoff counter freezes the instant CCA reports another transmitter, then resumes from where it paused after the medium is idle for DIFS again.*

**Walking scenario 1.** The medium is busy with a previous frame. When it goes idle the station waits `DIFS`; if still idle, it loads `backoff = random(0, CW)` and decrements one slot at a time. At zero it transmits the DATA frame. The receiver, having matched its hardware address filter, waits exactly `SIFS` — shorter than anyone else’s DIFS — and sends the ACK, which is why an ACK never has to contend. On the ESP32 every step here is silicon: software set the GO bit (§1.3.2) and is not consulted again until the TX-complete interrupt.

**Walking scenarios 2 and 3.** If no ACK returns within the ACK timeout, the transmission is presumed lost; the hardware sets `CW = min(2·CW + 1, CWmax)` and retries with a wider random backoff, up to a retry limit, after which the frame is dropped. Separately, if another station begins transmitting while our backoff is counting down, CCA flips to busy and the counter **freezes in place** — it is critical that it is not reset, because preserving the residual backoff is what gives stations that have already waited a long time a fair, eventually-decreasing chance to transmit. It resumes counting once the medium has been idle for a fresh DIFS.

> **INTERVIEW HOOK**  Connect the timing to this codebase in one breath: “The reason my driver’s TX path ends at the GO bit and my coexistence is software-timed is the same reason — 802.11’s **microsecond layer (CCA, slot backoff, SIFS-bounded ACK, TSF) is hardware** and can’t be done in C on a 240 MHz CPU. My open code only makes **millisecond** policy decisions: which frame, what rate, when to beacon, and — because I left PTA off — which radio gets a multi-second turn (Part 3).”

## 1.6  Block-by-Block: What Each Part Does on TX and RX

This closing section is the one to read last and revise first. It takes every block from the subsystem diagram in §1.1 and states, in plain terms, what that block does when a packet is **transmitted** and what it does when one is **received**. Read down the table to learn the parts; read the two narratives after it to see them work together on a single frame.

### 1.6.1  Every block, on TX and on RX

| **Block (from the diagram)** | **Role during TRANSMIT** | **Role during RECEIVE** |
|---|---|---|
| **MAC task (prio 22)** | Decides what to send and builds the 802.11 frame bytes (beacon, auth, assoc, data); leases a smart frame and calls rs_tx_smart_frame(). | Parses the received 802.11 header, runs the AP/STA state machine, and either replies or forwards the payload up to lwIP. |
| **hardware task (prio 23)** | Owns the registers: finds a free TX slot, computes the FCS, writes the descriptor + PLCP/CONFIG words, sets the GO bit. | Drains the RX descriptor ring on the ISR’s signal, unlinks filled buffers, hands them to the MAC task, then recycles them. |
| **WMAC ISR (IRAM)** | Wakes on the TX-complete interrupt and posts the event so the hardware task can reap the finished slot. | Wakes on the RX interrupt; reads and clears the cause register and posts RX_ENTRY — nothing heavier (top-half). |
| **DMA descriptor memory (SRAM)** | Holds the 5 TX payload buffers the DMA reads from when streaming a frame to the radio. | Holds the 10 RX buffers the DMA writes incoming frames into; each is described by a ring descriptor. |
| `WIFI_DMA_INT_STATUS / _CLR` | Signals ‘TX slot finished’ (a bit per slot) so software knows the frame left the air. | Signals ‘RX frame arrived’ / ‘ring needs servicing’; the ISR reads it to know why it was called, then write-1-clears it. |
| `WIFI_BASE_RX_DSCR + ring` | Not used for TX. | The head of the RX ring the hardware walks, filling each descriptor’s buffer and advancing its cursor. |
| `WIFI_MAC_BITMASK_084` | bit31 arms the hardware to stamp the live TSF into an outgoing beacon’s Timestamp field. | bit0 is toggled to re-arm (‘reload’) the RX chain after a descriptor has been consumed and relinked. |
| **TX engine — 5 slots** `(PLCP0/1/2, TX_CONFIG)` | The launch pads: each slot’s registers describe one frame (address, length, rate, key); setting PLCP0’s GO bits fires it. | Not used for RX. |
| `WIFI_TXQ_GET_STATE_COMPLETE` | Per-slot ‘done’ bitmap; processTxComplete() reads it to find which slot finished and recycles the smart frame. | Not used for RX. |
| **RX address filter / ACK** `(MAC/BSSID slots)` | Not used for TX (the source address is written into the frame by software). | Decides ‘is this frame for us?’ by matching MAC/BSSID, reports which slot matched via filter_match, and auto-ACKs within SIFS. |
| **TSF / beacon timing** | Provides the live 64-bit timestamp the hardware writes into beacons/probe-responses at the instant of TX. | Slaved to the AP’s TSF on a station; keeps the BSS clock so power-save wake-ups line up. |
| **DCF timing engine (silicon)** | After GO: senses the medium (CCA), waits DIFS, runs the random backoff, transmits at the chosen rate, awaits the ACK, retransmits on failure. | Generates the SIFS-bounded ACK for an accepted frame and enforces the NAV/medium state so the radio doesn’t talk over others. |
| **PTA coex arbiter** | Would grant/deny the antenna per TX event vs. BLE — but is DISABLED here, so Wi-Fi never asks permission (software TDM substitutes, Part 3). | Same: disabled; RX is unaffected by arbitration in this build. |
| **PHY: Digital→Analog / TX power** | Frames the PLCP/PPDU, modulates the bits (OFDM/DSSS), and sets transmit power for the outgoing waveform. | Not used for TX direction — see AGC/RX gain below. |
| **PHY: AGC / RX gain** | Not used for TX. | Sets receive gain and recovers the signal so the demodulator can decode a clean bitstream from a weak/strong frame. |
| **PHY: Channel synth / clock** | Tunes the synthesiser to the operating channel (6) and supplies the clock for transmission. | Same synthesiser/clock tune the receiver to the channel it listens on. |
| **RF front-end + antenna** | PA amplifies the modulated signal; the T/R switch connects the antenna to the transmitter; the antenna radiates it. | The antenna captures RF; the T/R switch routes it to the LNA, which amplifies the faint signal for the mixer/PHY. |

### 1.6.2  One TX, narrated through the blocks

![Figure 8](images/fig08-tx-walkthrough.png)

**Figure 8.**  *TX walkthrough. Control flows left → right: the MAC task builds the frame, the hardware task arms a TX slot and sets GO, the DCF engine and PHY put it on air through the RF front-end, and a completion interrupt recycles the slot. Numbered steps match the narrative below; RX-only blocks are dimmed.*

Follow a single beacon outward and notice how control passes left-to-right across the diagram. The **MAC task** decides it is time to beacon and builds the frame, leasing a buffer from **DMA descriptor memory**. The **hardware task** picks a free **TX slot**, computes the FCS into the payload, and writes that slot’s `PLCP0/1/2` and `TX_CONFIG` registers — length, rate, descriptor pointer — then sets the `GO` bits in `PLCP0`. Control now leaves software entirely. The **DCF timing engine** senses the medium via the PHY’s CCA, waits DIFS, counts down its backoff, and releases the frame; **TSF/beacon timing** stamps the live timestamp as it goes. The **PHY** frames and modulates the bits and the **RF front-end** amplifies and radiates them through the **antenna**. When the air time is done, the hardware sets this slot’s bit in `WIFI_TXQ_GET_STATE_COMPLETE` and raises the interrupt; the **WMAC ISR** posts it, the **hardware task** runs `processTxComplete()`, and the smart frame returns to the pool. Software touched only the millisecond-scale decisions at the two ends; the microsecond timing in the middle was all silicon.

### 1.6.3  One RX, narrated through the blocks

![Figure 9](images/fig09-rx-walkthrough.png)

**Figure 9.**  *RX walkthrough. Control flows right → left: the antenna and PHY recover the bits, the address filter accepts the frame and the DCF engine auto-ACKs in hardware, the DMA lands it in the ring, the ISR defers to the hardware task, and the MAC task parses it up to lwIP. Numbered steps match the narrative below; TX-only blocks are dimmed.*

Now follow a client’s data frame inward — right-to-left. The **antenna** captures the RF and the **RF front-end’s** T/R switch routes it to the LNA; the **PHY’s AGC** sets gain and the demodulator recovers the bits. Before the CPU is involved at all, the **RX address filter** checks the frame against our MAC/BSSID slots: if it matches, the **DCF engine** emits an **auto-ACK within SIFS** — far faster than software could — and the frame is accepted. The **DMA engine** writes the bytes into the next free buffer in the **RX descriptor ring**, sets that descriptor’s `has_data`, and the hardware raises the interrupt. The **WMAC ISR** reads and clears `WIFI_DMA_INT_STATUS` and posts `RX_ENTRY`; the **hardware task** walks the ring, hands the buffer (with its `filter_match` metadata) to the **MAC task**, which strips the 802.11 and LLC headers and pushes an Ethernet frame to lwIP, then relinks the descriptor and toggles the reload bit in `WIFI_MAC_BITMASK_084` so the hardware can reuse it. The symmetry with TX is exact: hardware owns the air-facing, deadline-bound steps; software owns the parsing and policy.

> **INTERVIEW HOOK**  If asked to ‘explain the chip end to end,’ sweep the diagram in one direction and back: “Left to right on TX — MAC task builds, hardware task arms a slot, DCF + PHY + RF put it on air, interrupt recycles it. Right to left on RX — antenna and PHY recover the bits, the **address filter accepts and auto-ACKs in hardware**, DMA lands it in the ring, the ISR defers to the hardware task, the MAC task parses to lwIP. The boundary never moves: **microseconds are silicon, milliseconds are software**.”

# Part 2 — State-Machine Control & Packet Hand-over (PHY → L3 / DHCP)

Part 1 covered the plumbing; Part 2 traces a packet end-to-end through it. The current build runs **AP mode live** with the STA path present but commented out in `mac.c`, so the STA flow below is described as the state machine implements it, and the AP + DHCP flow is described as it actually runs.

The single most useful mental model for everything in this part is the **layered wrap/unwrap**: on transmit each layer adds its own header to the payload below it, and on receive each layer strips the header it owns before handing the rest upward. The diagram traces one beacon outbound and one client data frame inbound across all the layers this build implements:

![Figure 10](images/fig10-end-to-end-packet-journey.png)

**Figure 10.**  *End-to-end packet journey. On TX (top) the AP’s intent becomes an 802.11 beacon, gains an FCS, then a PLCP/preamble, and goes out as a PPDU. On RX (bottom) a client’s PPDU is demodulated and hardware-filtered/ACKed, the 802.11 and LLC headers are stripped to an Ethernet frame, handed to ESP-NETIF, and lwIP peels IP/UDP to deliver the payload to the socket. Only the microsecond-timed, air-facing steps are hardware.*

## 2.1  Station Connection & DHCP Hand-over Flow

The STA state machine in `80211_mac.c` is a four-state progression — scan, authenticate, associate, associated — driven by the event loop’s timeouts. The full initialization and connect handshake is shown below:

![Figure 11](images/fig11-sta-connect-flow.png)

**Figure 11.**  *STA-mode initialization and connect flow. The state machine sets RX filters and hops channels while scanning, transitions on a matching beacon/probe-response, then drives the Auth and Assoc exchanges (each retried at 500 ms) before marking the interface up so data frames flow to lwIP.*

### 2.1.1  The full L1→L3 swimlane

This is the pipeline an interviewer will ask you to draw on a whiteboard. It maps a DHCP exchange across every layer of the working architecture — TX of the Discover down the stack, and RX of the Offer/Ack back up to lwIP:

![Figure 12](images/fig12-dhcp-handover.png)

**Figure 12.**  *DHCP traffic handling and hand-over to lwIP. On TX, a DHCP Discover from lwIP is marshalled by ESP-NETIF, copied and queued by the MAC task, encapsulated Ethernet→802.11 (FromDS + LLC/SNAP), and fired by the hardware. On RX, the Offer is hardware-filtered and auto-ACKed, stripped back to Ethernet, and injected via esp_netif_receive() so the lease completes.*

### 2.1.2  What actually happens to a DHCP Discover

- **L3 generates it.** lwIP’s DHCP client emits a broadcast UDP datagram; ESP-NETIF presents it to the registered IO driver as an Ethernet frame via `openmac_netif_transmit()`.
- **L2 marshals, doesn’t encapsulate-in-place.** To avoid doing real work on the netif thread, `c_transmit_data_frame()` *copies* the Ethernet frame into a fresh `malloc` buffer prefixed with a 1-byte interface id (`[iface][eth…]`) and posts `EVENT_TYPE_MAC_TX_DATA_FRAME` onto the MAC queue. Ownership transfers to the MAC task, which frees it after use.
- **Ethernet → 802.11 conversion.** `encapsulate_and_send()` builds a 24-byte 802.11 data header with the **FromDS** bit set (frame-control `0x0802`): Addr1 = destination (Eth dst), Addr2 = BSSID (our AP MAC), Addr3 = source (Eth src). It then inserts the 8-byte LLC/SNAP shim (`AA AA 03 00 00 00` + EtherType) and copies the L3 payload after it.
- **Backoff/slot timing is hardware.** Software never computes a backoff. It writes the descriptor + PLCP regs and sets the GO bits; the DCF engine performs CCA, waits DIFS, draws a random backoff from the contention window, transmits, and waits for the ACK. (Detailed in Part 3.3.)
- **RX OFFER/ACK pushed up.** The reply matches our hardware MAC filter (auto-ACKed within SIFS), is DMA’d into the RX ring, classified by `filter_match`, stripped of its 802.11 + LLC headers back to an Ethernet frame, and handed to `esp_netif_receive()` via `rs_rx_mac_frame() → openmac_netif_receive()`. lwIP advances DISCOVER→REQUEST→ACK and the client is bound; the AP’s DHCP server then posts `IP_EVENT_AP_STAIPASSIGNED`, which your `on_wifi_event()` handler observes.
**GOTCHA**  The RX free-path has a subtle ownership hazard the code explicitly guards: `openmac_free()` must distinguish a hardware DMA buffer (recycle via `c_recycle_mac_rx_frame`) from a software-malloc’d injection buffer. The sentinel `NETIF_FREE_MALLOC_BUFFER = 0xFFFFFFFF` is passed as the netstack handle so the free callback can early-return instead of recycling a non-ring buffer — a real crash that was fixed. Expect to be asked how you debugged a double-free / wild-pointer abort here.

## 2.2  AP-Mode Beaconing & Frame Routing

In AP mode the build broadcasts SSID `esp32-ap` on channel 6, beaconing every 102.4 ms and onboarding clients through the probe → auth → assoc handshake. The end-to-end AP behaviour is shown below before the timing-critical beacon path is examined in detail:

![Figure 13](images/fig13-ap-beacon-onboarding.png)

**Figure 13.**  *AP-mode beacon loop and client onboarding. handle_state_ap() emits a beacon every BEACON_INTERVAL_US; incoming probe/auth/assoc frames are serviced by the management handlers, advancing each client through AP_CLIENT_AUTHENTICATING → AP_CLIENT_ASSOCIATED, after which the DHCP exchange begins.*

### 2.2.1  Periodic beacon transmission and TBTT offload

The AP must emit a beacon every **TBTT** (Target Beacon Transmission Time). The build uses `BEACON_INTERVAL_US = 1024 × 100 = 102.4 ms` — the canonical 100 TU interval. Crucially, the **timing-critical part is split**: software decides *roughly* when to build and queue the beacon (soft timer in the event loop), while the **hardware** stamps the exact TSF into the beacon’s Timestamp field at the moment of transmission:

![Figure 14](images/fig14-periodic-beacon-tx.png)

**Figure 14.**  *Periodic beacon transmission. The MAC task builds the beacon and leases a smart frame; the hardware task writes the PLCP registers and sets the GO bit; the silicon stamps the live TSF into the Timestamp field (armed by bit 31 of MAC_BITMASK_084) and broadcasts at 1 Mbps; the TX-complete interrupt recycles the frame and the task sleeps until the next TBTT.*

The event loop returns a computed sleep — `(next_beacon − now)/1000` ms — to `rs_get_next_mac_event_raw()`, so the MAC task naturally wakes just in time for the next TBTT unless an RX event preempts it. The beacon body built by `build_beacon_frame()` carries the standard IEs: SSID (`esp32-ap`), supported + extended rates, DS-Parameter (channel 6), and a TIM. The 8-byte Timestamp is zeroed in software precisely because the hardware overwrites it with the live TSF.

> **INTERVIEW HOOK**  “Your beacon timer is a soft FreeRTOS sleep — isn’t TBTT supposed to be jitter-free?” Correct, and this is the honest limitation of a SoftMAC beacon: the **interval** jitters with scheduler latency, but the **Timestamp/TSF inside each beacon is hardware-exact**, which is what clients actually synchronise their power-save and TSF to. A production design would arm a hardware TBTT timer to fire the pre-staged beacon; the prototype accepts interval jitter because clients tolerate it and the TSF is still correct.

### 2.2.2  Station-to-station frame routing through the AP

When a connected station sends a frame to another station on the same AP, the question is whether the AP forwards at L2 or parses to L3. In this architecture the frame **rises to the bridge/IP layer and comes back down** — there is no L2 fast-path in the MAC task:

```text
  STA-A ──(802.11, ToDS)──► AP hardware RX ──► MAC task: handle_ap_hardware_rx
                                                  strip 802.11+LLC -> Ethernet
                                                  rs_rx_mac_frame() -> ESP-NETIF
                                                        │
                                            esp_netif_receive() -> lwIP / bridge
                                                        │  (L3 / netif decides dst)
                                            openmac_netif_transmit() (Eth frame back down)
                                                        │
                              c_transmit_data_frame -> encapsulate_and_send (FromDS)
                                                        │
  STA-B ◄──(802.11, FromDS)── AP hardware TX ◄──────────┘
```

Every inter-STA packet therefore makes a full L2→L3→L2 round trip. That is simple and correct, but it doubles airtime (each frame is received then re-transmitted) and burns CPU on two header rewrites. A production AP would implement a **local L2 forwarding table** (associate each client MAC with its virtual-interface/AID) and bounce intra-BSS unicast directly in the MAC task — receive, swap ToDS→FromDS, re-queue — without ever touching lwIP. Knowing both the current behaviour and the optimisation is the expected answer.

**Why the round trip happens — and why it’s defensible.** The frame a station sends to another station arrives with the **ToDS** bit set and three addresses: Addr1 = the AP’s BSSID (the radio destination), Addr2 = the sender, Addr3 = the *final* destination station. A real 802.11 AP is supposed to read Addr3, notice the destination is another associated client, and re-transmit the frame with **FromDS** set and the addresses re-ordered — a pure L2 relay (the ‘four-address’/three-address bridging logic). This build doesn’t do that in the MAC; it strips the 802.11 header down to an Ethernet frame and lets `esp_netif_receive()` hand it to lwIP, where the netif/bridge layer makes the forwarding decision by destination MAC and sends it back down through `openmac_netif_transmit()`. The upside is that there is exactly **one** forwarding code path (lwIP’s), it correctly handles the AP-as-gateway case (client → internet) and the inter-client case with the same logic, and it needs no association table in the MAC. The cost is real, though: a unicast between two clients occupies the channel twice and is rewritten twice.

**What the production fast-path looks like.** To cut intra-BSS traffic to a single airtime, the MAC task would keep a small table mapping `client MAC → {AID, virtual interface, power-save state}`, populated at association and torn down at disassociation. On RX of a ToDS data frame whose Addr3 is found in that table, it would forward at L2: rewrite the frame-control bits (ToDS→FromDS), set Addr1 = the destination client, Addr2 = BSSID, Addr3 = original sender, and re-queue it directly via `rs_tx_smart_frame()` — never allocating an Ethernet copy, never entering lwIP. Two details make this more than a copy-paste: the destination might be in **power-save**, so the AP must buffer the frame and advertise it in the TIM of the next beacon rather than transmit immediately; and broadcast/multicast from a client must be both relayed to all other clients *and* passed up to lwIP (for the AP’s own IP stack), so the fast-path and the slow-path are not mutually exclusive. The honest interview answer is that the round-trip design is the right *prototype* choice — one code path, provably correct — and the L2 fast-path with TIM-aware buffering is the right *product* choice once intra-BSS throughput matters.

## 2.3  Commercialisation vs. Custom R&D — How the Boundaries Should Decouple

This section contrasts the prototype you have (raw hooks + shared FreeRTOS queues) with what a shippable driver demands. The interviewer is checking whether you can see past “it works on my bench.”

| **Concern** | **Prototype (this build)** | **Production-grade target** |
|---|---|---|
| Buffer flow | malloc + memcpy per TX (c_transmit_data_frame copies eth into a new buffer); 5 fixed pools | Zero-copy pbuf ownership transfer; DMA directly from/to pbuf payload; no per-frame memcpy |
| RX descriptors | 10 static 1600B bufs, relinked by hand | Pre-mapped DMA ring with watermark refill; pbuf-backed RX so lwIP holds the DMA buffer directly |
| ISR work | ISR posts cause to a queue; counting-sem backpressure | Strict top/bottom-half: ISR only ACKs HW + signals; all parsing in a deferred context |
| Concurrency | Two pinned tasks + queues; some shared globals (tx_slots) touched by ISR-adjacent code | Explicit lock domains, lock-free SPSC rings, documented ISR-safe vs task-safe APIs |
| Coexistence | Software TDM watchdog reacting to TX timeouts | Hardware PTA arbitration or scheduled TDMA negotiated with the BT controller |
| Error handling | abort() on unexpected recycle; printf logging | Bounded recovery, statistics counters, no aborts on the data path |

### 2.3.1  Zero-copy memory management

In lwIP the unit of buffer ownership is the `pbuf`, a reference-counted, possibly-chained buffer. The prototype breaks zero-copy twice: on TX it `memcpy`s the Ethernet frame into a malloc’d staging buffer; on RX it copies the 802.11 payload into a separate Ethernet buffer before injection. A production driver makes the **DMA engine read and write pbuf payloads directly**: TX DMA points at the pbuf’s data with the 802.11 header prepended in reserved head-room (lwIP’s `PBUF_RAW` + `pbuf_header` pattern), and RX hands the DMA buffer up as a `PBUF_REF` whose custom free callback recycles the descriptor. Ownership is transferred, never duplicated; the `NETIF_FREE_MALLOC_BUFFER` sentinel hack disappears because there is exactly one buffer lifecycle.

### 2.3.2  Interrupt concurrency isolation (top-half / bottom-half)

The WMAC ISR (`wifi_interrupt_handler`, `IRAM_ATTR`) is already a clean top-half: it reads `WIFI_DMA_INT_STATUS`, write-1-clears it, and defers all real work by posting to `hardware_event_queue`. The bottom half (the hardware task) walks the ring and reaps TX slots. The production refinement is to **guarantee the data path never aborts and never blocks**: replace the `abort()` calls in the recycle paths with counter-incrementing recovery, keep every ISR-touched structure either lock-free or accessed only from the ISR, and ensure `IRAM_ATTR` + DRAM placement so the ISR survives flash-cache disable during writes.

### 2.3.3  Thread safety between the real-time MAC task and lwIP

The high-priority MAC/hardware tasks (prio 22/23, core 0) and lwIP’s TCP/IP thread (lower priority, typically core-agnostic) meet at exactly two points: TX (`openmac_netif_transmit → c_transmit_data_frame`) and RX (`esp_netif_receive`). Both hand-offs are mediated by FreeRTOS queues, which are the right primitive — they are the only shared mutable state, and they are internally locked. The danger zone is the `tx_slots[]` array and the smart-frame pools, which are manipulated from the hardware task and indirectly from completion handling. The *in_use* flags are currently plain `bool`s; a production driver would make the pool allocation/free explicitly atomic or confine it to a single task, and would document which APIs are ISR-safe (the `*_from_isr` coex wrappers in `hwinit.c` are the model). The guiding rule: **the MAC task must never inherit lwIP’s latency, and lwIP must never stall the DCF deadline** — the queues enforce that separation.

> **INTERVIEW HOOK**  A strong closing line for this section: “The prototype is correct because it serialises everything that could race onto two pinned tasks and two locked queues. The production version trades that conservative serialisation for **zero-copy and lock-free SPSC rings**, but only after proving — with counters, not aborts — that the data path never violates the SIFS/TBTT deadlines under worst-case lwIP load.”

# Part 3 — Advanced Coexistence & Hardware Protocols

The ESP32 has **one 2.4 GHz radio shared between Wi-Fi and Bluetooth/BLE**. They cannot both be on-air at the same instant, so something must arbitrate. There are two industry answers — hardware PTA and time-division (TDMA) — and a third reality: this build **deliberately disables hardware PTA** and implements a coarse software time-division recovery instead. This part explains all three and ties the theory to exactly what your code does.

## 3.1  PTA — Packet Traffic Arbitration

PTA is a **sub-microsecond hardware handshake** between the Wi-Fi and BT MAC engines that decides, on a per-event basis, who gets the antenna. On a discrete two-chip design it is literally four wires; on the single-die ESP32 it is an on-chip arbiter in the modem, but the signal semantics are identical:

| **Signal** | **Driven by** | **Meaning** |
|---|---|---|
| REQUEST / *_ACTIVE | Each radio | “I want the medium for an upcoming event.” |
| PRIORITY | Each radio | Class of the request (e.g. BLE connection event vs. Wi-Fi background TX). |
| GRANT | Arbiter | “You won — transmit/receive now.” |
| STATUS | Arbiter | Feedback to the loser (abort / defer / denied). |

The arbiter compares the two PRIORITY values; the higher-priority requester gets GRANT and the other receives a deny via STATUS and must abort or defer its event. The classic collision an interviewer will name is a **BLE connection event vs. a Wi-Fi ACK**: a BLE connection event is latency-critical (miss it and the link supervision timer ticks toward disconnect), but a Wi-Fi ACK has a hard SIFS deadline. The priority table is what resolves it — typically BLE connection/scan events are given high priority via `coex_bt_high_prio()`, while Wi-Fi background traffic yields.

![Figure 15](images/fig15-pta-collision-resolution.png)

**Figure 15.**  *PTA arbitration of a BLE-vs-Wi-Fi collision, and why this build disables it. The hardware arbiter grants the medium to the higher-priority requester; the loser defers. Enabling it here (coex_init/coex_enable) let the BLE blob gate Wi-Fi TX during every advertising event, permanently timing out all five TX slots — so PTA is left off and a software watchdog recovers instead.*

At the wiring level, PTA is a set of signals between the two MACs and a central arbiter that ultimately drives the one radio. On a two-chip design these are physical pins (the classic 3-/4-wire coexistence interface); on the single-die ESP32 they are on-chip signals managed by `libcoexist.a`, but the semantics are identical:

![Figure 16](images/fig16-pta-coex-wiring.png)

**Figure 16.**  *PTA coexistence wiring. Each radio asserts REQUEST/ACTIVE and a PRIORITY when it wants the medium; the arbiter compares priorities (BLE connection events are raised to high priority via coex_bt_high_prio()) and raises GRANT to exactly one radio, returning STATUS/deny to the other so its MAC freezes the DCF backoff rather than colliding. In this build the path is left unwired — coex is never enabled — and the software TDM watchdog substitutes for the hardware GRANT.*

**GOTCHA — why this build turns PTA OFF**  The `hwinit()` comment is explicit: enabling coex activates the PTA, which lets the BLE controller **gate Wi-Fi TX during every advertising event**. On this register layout that gating caused **all five TX slots to time out permanently** — the GRANT for Wi-Fi never came back. So PTA was disabled and the two radios share the band *unarbitrated*, relying on slow BLE advertising intervals (1–2 s) to keep the collision window tiny (~1 ms/event), with a software watchdog to recover from the collisions that do happen. Be ready to defend this as a pragmatic R&D choice, and to say what you’d fix to re-enable real PTA.

## 3.2  TDMA for Coexistence — and the Software TDM This Build Actually Uses

When hardware PTA is unavailable or insufficient, radios fall back to **time-division**: carve time into slots and assign each slot to one radio. True TDMA negotiates slot boundaries between the two MACs (often anchored to the BLE connection-interval anchor points). Your build implements a **reactive, coarse-grained software TDM** instead: it does not pre-allocate slots; it *detects* that BLE has seized the radio and forcibly hands a multi-second slot back to Wi-Fi. This is the mechanism that makes the build “work,” and it lives in the hardware-task idle path.

### 3.2.1  The detection signal: consecutive TX-slot timeouts

Every queued TX records `esp_timer_get_time()`. In the idle branch the hardware task sweeps the five slots; any slot in-use longer than **50 ms** is declared timed-out (the DCF engine never got the medium). Isolated timeouts are normal RF collisions and are ignored; **three consecutive timeout cycles** is the heuristic for “BLE has taken the radio.”

![Figure 17](images/fig17-software-tdm-watchdog.png)

**Figure 17.**  *The reactive software-TDM watchdog in the hardware-task idle branch. Three consecutive 50 ms TX-slot timeouts are read as “BLE seized the radio”; the driver stops advertising, recycles slots, restores the Wi-Fi PHY and channel, runs a ~5 s Wi-Fi-only window, then re-opens a short BLE advertising burst — repeating.*

**The mechanism in code.** Each idle tick the hardware task runs `processTxComplete()`, then sweeps the five slots; any slot in use longer than 50 ms is recycled and flags a timeout. `consecutive_timeouts` increments on a timeout cycle and resets otherwise. At three in a row with BLE not already paused, the recovery fires: `ble_coex_stop_advertising()`, recycle all in-use slots, a 10 ms delay to let the controller drop the radio, then `esp_phy_common_clock_enable()` → `esp_phy_load_cal_and_init()` → `coex_bt_high_prio()` to rebuild the Wi-Fi PHY that BLE clobbered, and finally `change_channel_to(restore_ch)` to re-apply the MAC/channel state. After roughly five seconds of Wi-Fi-only operation, `ble_coex_start_advertising()` re-opens the BLE window.

This is exactly the cycle the success log shows in steady state: *“TDM:3 consecutive tx timeout — BLE has taken the radio” → “stop advertising” → “wifi phy fully restored on ch6” → 5 s later → “BLE advertising window started,”* repeating. The 5-second Wi-Fi window is intentionally long so a client has time to complete auth, association, and DHCP before BLE is allowed back on-air.

**How Wi-Fi TX is suspended “gracefully.”** When the BLE slot is active the driver does not try to micro-suspend the DCF engine; instead, when Wi-Fi can’t get the medium its TX slots simply time out and are **recycled back to the smart-frame pool** (the frame is dropped, not wedged). Because the upper layers retransmit (ARP/DHCP/TCP all retry), dropping a few frames during a BLE burst is recoverable. The “graceful” part is that recycling frees the slot so the queue never deadlocks — which is exactly the failure mode that enabling PTA produced.

**The coexistence_control.c scaffold.** Separately, there is a semaphore-based gate (`coexistence_notify_ble_start/end`, `coexistence_wifi_wait_for_access`) intended to let the BLE stack signal radio bursts so Wi-Fi can wait on a binary semaphore. In the current build this is an **advisory scaffold** — initialised but not yet wired into the TX decision path, which instead relies on the timeout-driven TDM above. Calling this out honestly (scaffold vs. active mechanism) is the kind of precision that distinguishes a principal candidate.

> **INTERVIEW HOOK**  “Is this real TDMA?” No — real TDMA negotiates and honours slot boundaries **proactively** (Wi-Fi knows the BLE anchor and stays off-air during connection events). This is **reactive recovery**: Wi-Fi discovers it lost the medium after the fact (three 50 ms timeouts ≈ 150 ms of detection latency) and seizes a long compensating window. The upgrade path is to subscribe to the BLE controller’s event-start callback and pre-emptively park Wi-Fi TX for the known connection-event duration — i.e. move from detect-and-recover to schedule-and-avoid.

## 3.3  Hardware Slots & Backoff Timers — DCF in Silicon

Underneath all coexistence sits the 802.11 **DCF** (Distributed Coordination Function): CSMA/CA with binary-exponential backoff. The ESP32 implements the microsecond-scale parts of DCF in hardware because software on a 240 MHz CPU cannot reliably hit a 10 µs SIFS. This is why your TX path ends at “set the GO bit” and stops — the rest is silicon. Section 1.5 introduced these timing rules from first principles with a timeline view; this section focuses on the **per-attempt control flow** the silicon runs and how it surfaces back to software.

### 3.3.1  The interframe spaces and the slot

| **Quantity** | **2.4 GHz value** | **Purpose** |
|---|---|---|
| Slot time | 9 µs (OFDM) / 20 µs (DSSS) | Quantum of the backoff countdown. |
| SIFS | 10 µs | Gap before ACK / CTS — highest priority, no contention. |
| DIFS | SIFS + 2×slot ≈ 28/50 µs | Idle time a station must see before starting contention. |
| CW | CWmin=15 … CWmax=1023 | Range the random backoff is drawn from; doubles per retry. |

Priority falls naturally out of the timing: a responder waits only SIFS (so ACKs/CTS always beat new transmissions, which must wait the longer DIFS), and contending stations each pick a random backoff in `[0, CW]` so collisions are statistically spread out.

### 3.3.2  How the hardware runs the countdown

After software sets the GO bit, the silicon runs the entire CSMA/CA attempt — DIFS sensing, random backoff with freeze/resume, transmit, and the SIFS-bounded ACK wait — retrying with a doubled contention window on failure:

![Figure 18](images/fig18-dcf-in-silicon.png)

**Figure 18.**  *DCF in silicon: the hardware sequence triggered by PLCP0 |= 0xC0000000. The medium is sensed idle for DIFS, a random backoff is drawn from the contention window and decremented per idle slot (frozen when the medium goes busy), the frame is transmitted at the PLCP1 rate, and an ACK is awaited within SIFS — success sets the TXQ-complete bit, failure doubles CW and retries.*

The hardware maintains the contention window, performs CCA (clear-channel assessment) via the PHY, freezes and resumes the backoff counter as the medium goes busy/idle, emits the frame at the rate encoded in `MAC_TX_PLCP1`, auto-receives the ACK against the SIFS deadline, and signals completion by setting the slot’s bit in `WIFI_TXQ_GET_STATE_COMPLETE`. Your `processTxComplete()` reads that register, finds the slot via `31 − __builtin_clz()`, clears it, and recycles the frame. The `MAC_TX_DURATION` register is set to 0 because the hardware computes and inserts the NAV/duration itself.

> **INTERVIEW HOOK**  Tie it all together: “The reason this whole project is even possible is that 802.11’s **timing-critical core — slot countdown, SIFS-bounded ACK, CW backoff, TSF — is in hardware**, so open software only has to make policy decisions (what frame, what rate, when to beacon) at millisecond scale. The same property is why my coexistence is software-timed: I’m arbitrating at the policy layer (who beacons / advertises this second), while the silicon still owns the microsecond DCF underneath.”

# Appendix A — Rapid-Fire Recall & Likely Grilling Points

### A.1  The build at a glance

| **Fact** | **Value** |
|---|---|
| Target / IDF | Plain ESP32 (rev v3.1), ESP-IDF v5.0.1 (asserted at boot) |
| PHY version pinned | 4670,719f9f6,Feb 18 2021,17:07:07 |
| Active mode | AP (SSID esp32-ap), channel 6; STA path present but commented out |
| AP MAC / BSSID | 00:20:91:00:00:00 |
| Beacon interval | 102.4 ms (100 TU) |
| TX slots / RX ring | 5 smart-frame slots / 10 × 1600B DMA descriptors |
| MAC queue depth | 30 + 5 events; counting sems depth 10 (RX/TX backpressure) |
| Tasks | wifi_hardware (prio 23) + rs_wifi MAC (prio 22), both pinned core 0 |
| Coexistence | Hardware PTA DISABLED; reactive software TDM (3×50ms timeout → 5s Wi-Fi window) |
| FCS | Computed in software (CRC32), HW CRC disabled |

### A.2  Ten questions to expect

- Is the ESP32 SoftMAC or FullMAC, and where exactly is the cut? (hardware-assisted SoftMAC; cut inside libpp.a, keep PHY/RF blob).
- Walk a DHCP Discover from lwIP to the air and the Offer back. (2.1.2 swimlane).
- Why initialise BLE before Wi-Fi? (BLE re-runs PHY cal; Wi-Fi config must be applied last).
- Why hardware MAC filtering instead of promiscuous mode? (SIFS-deadline auto-ACK).
- What does PLCP0 |= 0xC0000000 do, and what happens after? (hands the slot to the DCF engine; HW does CCA/backoff/TX/ACK).
- How does the AP stamp the beacon Timestamp? (bit 31 of MAC_BITMASK_084; HW writes live TSF).
- Why did you disable PTA, and how do you recover collisions? (PTA gated all TX → permanent timeout; reactive software TDM).
- Difference between your software TDM and real TDMA? (reactive detect-and-recover vs. proactive scheduled slots).
- Where are the thread-safety hazards and how are they contained? (tx_slots pool; two pinned tasks + locked queues).
- What would you change to ship this? (zero-copy pbufs, hardware TBTT timer, L2 forwarding table, PTA or scheduled TDMA, no aborts on data path).

*Prepared as an interview study aid for a working esp32-open-mac AP + BLE-coexistence build. All register offsets, task priorities, timeouts, and flows are taken directly from the project’s hardware.c, hwinit.c, 80211_mac.c, 80211_mac_interface.c, mac.c, main.c, and the captured success log.*
