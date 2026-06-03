# 🐧 Linux Wi-Fi Networking — Interview Deep Dive

### Data-Path Hand-over (L3 → L2), Control vs Data Command Flows, and User-Space → Kernel-Driver Plumbing

> **Why this document exists.** It targets three specific gaps raised in a Cisco interview:
> 1. **L3 → L2 hand-over** — what *actually* happens to a `ping` (ICMP) packet as it crosses from the IP layer to the link layer, and how L2 decides what frame to build.
> 2. **Linux platform flows** — a complete, end-to-end trace for **one control command** and **one data command**, named function by named function.
> 3. **User-space → kernel driver** — how a user-space request ("turn on Wi-Fi") reaches the driver, and exactly how `open`/`close`/`read`/`write`/`ioctl`/`socket` are wired to driver entry points.
>
> It is the **Linux counterpart** to the FreeRTOS/ESP32 SoftMAC guide: same concepts (SoftMAC vs FullMAC, TX/RX rings, DCF-in-silicon, control vs data plane), expressed in the **Linux kernel** networking and driver model (`socket` → `net_device` → `cfg80211`/`mac80211` → driver → firmware).

---

## 📑 Contents

**Part 1 — The Linux Network & Wi-Fi Stack (the map)**
- 1.1  Two completely different driver models: char-device vs network-device
- 1.2  The Linux Wi-Fi layering: nl80211 → cfg80211 → mac80211 → driver → firmware
- 1.3  SoftMAC vs FullMAC on Linux (where mac80211 fits)
- 1.4  The two key objects: `struct net_device` and `sk_buff` (skb)

**Part 2 — Gap #1: L3 → L2 Hand-over, traced with `ping`**
- 2.1  The misconception, stated and corrected
- 2.2  Step-by-step: from `ping` syscall to bytes on the wire
- 2.3  How L2 decides *what* frame to build (EtherType + neighbour/ARP)
- 2.4  Where 802.3 (Ethernet) becomes 802.11 (mac80211 encapsulation)
- 2.5  The skb as the universal carrier

**Part 3 — Gap #2: One Control Command and One Data Command, end to end**
- 3.1  Control plane vs data plane (why they are separate)
- 3.2  CONTROL command walkthrough: `iw dev wlan0 set channel 6`
- 3.3  CONTROL command (richer): `wpa_supplicant` connect/associate
- 3.4  DATA command walkthrough: a `ping` packet to the air and back

**Part 4 — Gap #3: User-Space → Kernel-Space Driver**
- 4.1  "Turn on Wi-Fi": the three real paths (`ip link up`, `rfkill`, nl80211)
- 4.2  The VFS model: how `open/read/write/ioctl` reach a *char* driver
- 4.3  The network model: how `socket()` and `ip link` reach a *net* driver
- 4.4  Side-by-side: file-ops vs net-device-ops vs netlink

**Appendix A — Rapid-fire answers to the exact questions asked**

---

# Part 1 — The Linux Network & Wi-Fi Stack (the map)

Before tracing any packet, you need the map. The single most important thing to internalise — and the thing that makes interviewers nod — is that **Linux has two different driver models**, and Wi-Fi touches **both**.

## 1.1  Two completely different driver models

| | **Character / block device** | **Network device** |
|---|---|---|
| Appears as | a file in `/dev` (e.g. `/dev/ttyS0`) | **not** a file — an interface like `wlan0` |
| User opens it via | `open("/dev/...")` → fd | `socket()` → fd (and `ip`/`iw` via netlink) |
| Entry points | `struct file_operations`: `.open .read .write .unlocked_ioctl .release` | `struct net_device_ops`: `.ndo_open .ndo_stop .ndo_start_xmit` |
| Data movement | `read()`/`write()` copy bytes to/from the fd | packets flow as **`sk_buff`s**, not via `read/write` on the iface |
| Examples | UART, GPIO, a custom char driver | `eth0`, `wlan0`, `lo` |

> 🔑 **This distinction is the answer to half of Gap #3.** People assume "a driver has `open/read/write`". That is true for a **char driver** (VFS `file_operations`). A **Wi-Fi interface is a network device** — you never `read()`/`write()` `wlan0`. Instead you `socket()`, and the kernel routes your packet to the device's `ndo_start_xmit()`. Control (turning it on, setting channel) goes over a **netlink socket** to `cfg80211`, not through `ioctl` on a `/dev` node. Both models are covered in Part 4.

## 1.2  The Linux Wi-Fi control layering

```mermaid
flowchart TD
    subgraph US["USER SPACE"]
        APP["app: ping / curl / browser"]
        TOOLS["iw / wpa_supplicant / NetworkManager"]
    end
    subgraph K["KERNEL SPACE"]
        SOCK["Socket layer (AF_INET / AF_PACKET)"]
        IP["IP / routing / neighbour (ARP)"]
        NL["nl80211 (generic netlink family)"]
        CFG["cfg80211 (config & policy, regulatory)"]
        MAC["mac80211 (SoftMAC: 802.11 state machine, TX/RX)"]
        DRV["driver (ath9k / iwlwifi / mt76 / brcmfmac ...)"]
    end
    HW["Wi-Fi chip + firmware + PHY/RF"]

    APP -->|"data: send()/sendto()"| SOCK --> IP --> NETDEV["net_device (wlan0)"] --> MAC
    TOOLS -->|"control: netlink msg"| NL --> CFG --> MAC --> DRV --> HW
    MAC --> DRV
    DRV -->|"DMA / registers"| HW
```

The split to remember:
- **Control plane (left-to-right top):** user tool → **netlink** → `nl80211` → `cfg80211` → `mac80211` (or a FullMAC driver) → driver → firmware. This configures the device (scan, connect, set channel, key install, turn radio on/off).
- **Data plane (the packet path):** `socket()` → IP stack → `net_device` (`wlan0`) → `mac80211` TX → driver `xmit` → DMA → air. This carries your actual `ping`/TCP/UDP bytes.

These planes are **deliberately separate** (Part 3.1 explains why). Mixing them up is the classic interview stumble.

## 1.3  SoftMAC vs FullMAC on Linux

Same dichotomy as the ESP32 guide, expressed in Linux components:

| | **SoftMAC** | **FullMAC** |
|---|---|---|
| Who runs the 802.11 MAC state machine (auth/assoc, sequencing, retries policy) | **`mac80211`** (kernel software) | the **chip firmware** |
| Linux module in the middle | `cfg80211` + **`mac80211`** + thin driver | `cfg80211` + a driver that talks to firmware (no `mac80211`) |
| Driver examples | `ath9k`, `ath5k`, `mt76`, `rtl8xxxu`, `b43` | `brcmfmac` (Broadcom), most mobile/SDIO combos, `mwifiex` |
| Where DCF/SIFS/backoff/ACK live | **always hardware** (too fast for software) | hardware |
| What the host CPU does | builds/parses management frames, runs the MAC SM, manages queues | sends high-level commands ("connect to SSID X"); firmware does the rest |

> 🔑 **Interview framing:** "Linux Wi-Fi is `cfg80211` for everyone, plus **`mac80211` only for SoftMAC** parts. FullMAC drivers register with `cfg80211` directly and push the MAC into firmware. Either way the **microsecond-timed DCF (CCA, SIFS, backoff, ACK) is in silicon** — the SoftMAC/FullMAC line is only about where the *millisecond* MAC management lives." This is the exact same "microseconds = silicon, milliseconds = software" boundary from the ESP32 guide.

## 1.4  The two objects you must be able to name

Almost every answer below pivots on these two structures:

**`struct net_device`** — the kernel's representation of an interface (`wlan0`). It holds the MAC address, MTU, state flags, and crucially a pointer to **`netdev_ops`** (`struct net_device_ops`), whose function pointers are the driver's entry points:

```c
struct net_device_ops {
    int  (*ndo_open)(struct net_device *dev);          // 'ip link set wlan0 up'
    int  (*ndo_stop)(struct net_device *dev);          // 'ip link set wlan0 down'
    netdev_tx_t (*ndo_start_xmit)(struct sk_buff *skb, // TX a packet
                                  struct net_device *dev);
    void (*ndo_set_rx_mode)(struct net_device *dev);   // multicast/promisc
    int  (*ndo_set_mac_address)(struct net_device *dev, void *addr);
    /* ... */
};
```

**`struct sk_buff` (the "skb")** — the universal packet buffer. One skb travels the *entire* stack; each layer adjusts pointers rather than copying. Key fields:

```c
struct sk_buff {
    /* layout: [ headroom ][ data ........... ][ tailroom ] */
    unsigned char *head, *data, *tail, *end;  // buffer + current cursor
    __be16  protocol;        // L3 type as seen by L2  (e.g. ETH_P_IP, ETH_P_ARP)
    struct net_device *dev;  // which interface
    /* header offsets, set as the packet is built/parsed */
    __u16 transport_header;  // -> TCP/UDP/ICMP
    __u16 network_header;    // -> IP
    __u16 mac_header;        // -> Ethernet/802.11
    /* helpers: skb_push() grows toward head (prepend header),
                skb_pull() shrinks from data (strip header)   */
};
```

> 🔑 The whole TX story is *"prepend headers with `skb_push()` as you go down; strip them with `skb_pull()` as you go up."* No payload copy between layers — only pointer math. This is the Linux analogue of the ESP32 "smart frame".

---

# Part 2 — Gap #1: L3 → L2 Hand-over, traced with `ping`

> **The exact interview question:** *"You run `ping`. What happens? What goes to L2 and how? How does L2 know what type of frame to create and what address to use, from the ICMP packet?"*

## 2.1  The misconception, stated and corrected

The trap in the question is the phrase **"from the ICMP packet."** It tempts you to say *"L2 looks inside the ICMP packet to decide what to build."* **That is wrong, and stating the correction is what scores the point:**

> ❌ **Myth:** L2 inspects ICMP/IP contents to choose the frame type and destination MAC.
>
> ✅ **Reality:** **L2 never looks at ICMP at all.** By the time the packet reaches L2 it is an opaque payload. Two pieces of metadata — decided *above* L2 — tell L2 everything it needs:
> 1. **`skb->protocol`** (the EtherType, e.g. `ETH_P_IP = 0x0800`) — set by the IP layer. This becomes the Type field of the L2 header. L2 copies it; it does not derive it.
> 2. **The next-hop L2 (MAC) address** — resolved by the **neighbour subsystem (ARP for IPv4 / ND for IPv6)**, *driven by the routing decision*, **not** by anything inside ICMP.

So the honest, precise answer is: *"L2 doesn't parse ICMP. The IP layer tags the skb with an EtherType and asks the neighbour layer to resolve the next-hop MAC; L2 just frames the bytes using those two values."*

## 2.2  Step-by-step: from `ping` to bytes on the wire

```mermaid
sequenceDiagram
    participant APP as ping (user space)
    participant SOCK as Socket layer (AF_INET, SOCK_RAW/DGRAM ICMP)
    participant ICMP as ICMP / IP (L3)
    participant RT as Route + Neighbour (ARP)
    participant L2 as L2 output (dev_hard_header)
    participant Q as qdisc (queue)
    participant DRV as net_device (ndo_start_xmit)

    APP->>SOCK: sendto(fd, icmp_echo, ... dest IP)
    Note over SOCK: syscall -> sys_sendto -> sock->ops->sendmsg
    SOCK->>ICMP: build ICMP Echo Request, hand to IP
    ICMP->>ICMP: ip_send_skb(): fill IP header (proto=ICMP=1, dst IP)
    ICMP->>RT: ip_route_output(): which device + next hop?
    Note over RT: route says: out via wlan0, gateway = 192.168.1.1
    RT->>RT: neigh_lookup(next-hop IP) -> need its MAC?
    alt MAC unknown
        RT->>RT: ARP: who-has 192.168.1.1 -> reply: AA:BB:..
        Note over RT: skb queued until ARP resolves
    end
    RT->>L2: neigh_resolve_output(): dst MAC now known
    L2->>L2: dev_hard_header(): PREPEND L2 header<br/>{dst MAC, src MAC, EtherType=skb->protocol}
    L2->>Q: dev_queue_xmit(skb)
    Q->>DRV: dequeue -> dev->netdev_ops->ndo_start_xmit(skb, dev)
    Note over DRV: driver maps skb for DMA, writes TX descriptor,<br/>rings doorbell -> hardware frames + transmits
```

**Named-function call path (IPv4 ICMP, the version to recite):**

```text
USER:   ping  ->  sendto(2)
SYSCALL: __sys_sendto -> sock_sendmsg -> inet_sendmsg
L4/ICMP: raw_sendmsg (or ping_v4_sendmsg for unprivileged ping)
L3 IP:   ip_send_skb -> ip_local_out -> __ip_local_out -> ip_output
         ip_finish_output -> ip_finish_output2
NEIGH:   ip_finish_output2 calls neigh_output()
            -> if resolved: neigh_hh_output()/dev_queue_xmit
            -> if NOT resolved: neigh_resolve_output()
                 -> arp_solicit() sends ARP, skb queued on neigh->arp_queue
                 -> on ARP reply (arp_process -> neigh_update) the queued
                    skb is released and continues
L2 HDR:  dev_hard_header() -> dev->header_ops->create()
            (for Ethernet: eth_header() writes {dst,src,EtherType})
QDISC:   __dev_queue_xmit -> q->enqueue ... qdisc_run -> sch_direct_xmit
DEVICE:  netdev_start_xmit -> dev->netdev_ops->ndo_start_xmit(skb, dev)
```

> 📌 Everything from `ip_route_output` to `dev_hard_header` is the **L3→L2 hand-over**. The packet stops being "an IP datagram" and becomes "a framed link-layer unit" at `dev_hard_header()`.

## 2.3  How L2 decides *what* frame to build (the two inputs)

At `dev_hard_header()` the link layer needs exactly **three** things, and all three come from above L2 — never from ICMP:

| What L2 needs | Where it comes from | Set by |
|---|---|---|
| **EtherType** (frame's Type field) | `skb->protocol` | the socket/IP layer (`ETH_P_IP` for IPv4, `ETH_P_ARP` for ARP, `ETH_P_IPV6` for v6) |
| **Source MAC** | `dev->dev_addr` | the `net_device` (the interface's own address) |
| **Destination MAC** | the **neighbour entry** for the next hop | ARP/ND resolution, triggered by the **routing** decision |

The crucial causal chain for the destination MAC:

```text
dst IP (in ICMP/IP header)
   -> routing table picks NEXT-HOP IP (the host itself if on-link,
        otherwise the gateway) and the egress device (wlan0)
   -> neighbour table maps NEXT-HOP IP  ->  next-hop MAC  (via ARP)
   -> that MAC becomes the L2 destination address
```

> 🔑 **Answer to "how does L2 know the address from the ICMP packet?":** *It doesn't read the ICMP packet. The destination IP (from L3) drives a **routing lookup** to find the next hop, then the **neighbour/ARP** subsystem turns that next-hop IP into a MAC. L2 is handed the finished MAC. If the next hop is off-subnet, the MAC is the **gateway's**, not the ping target's — proof that L2 addressing is a routing/ARP outcome, not an ICMP field.*

> 🔑 **Answer to "what type of packet does L2 create?":** *L2 creates whatever `skb->protocol` says — `ETH_P_IP` here. The same L2 code would stamp `ETH_P_ARP` for an ARP frame or `ETH_P_IPV6` for v6. L2 is payload-agnostic; the EtherType is a label it copies, not a decision it makes.*

## 2.4  Where Ethernet becomes 802.11 (the Wi-Fi-specific twist)

On **wired** Ethernet, `dev_hard_header()` writes a 14-byte Ethernet header and you are done. On **Wi-Fi**, the device presents an **Ethernet-looking** `net_device` to the IP stack (so the whole path above is identical), but `mac80211` then **converts the 802.3 frame into an 802.11 frame** on the way down. This is the Linux equivalent of the ESP32 `encapsulate_and_send()`:

```mermaid
flowchart LR
    A["skb: Ethernet frame<br/>{dst MAC, src MAC, EtherType=IP}<br/>+ IP + ICMP payload"]
      --> B["mac80211 TX<br/>ieee80211_subif_start_xmit()"]
    B --> C["ieee80211_xmit -> __ieee80211_xmit_fast<br/>build 802.11 header"]
    C --> D["802.11 data frame:<br/>FrameCtrl, Dur, Addr1/2/3, Seq<br/>+ LLC/SNAP (AA-AA-03-00-00-00, EtherType)<br/>+ IP + ICMP"]
    D --> E["driver->ops->tx()<br/>(ieee80211_ops.tx)"]
    E --> F["DMA descriptor -> hardware -> DCF -> air"]
```

The conversion specifics (worth stating):
- The **802.3 header is replaced** by an **802.11 MAC header** (24–30 bytes): Frame Control, Duration, **Address 1/2/3** (BSSID/SA/DA depending on To-DS/From-DS), Sequence Control.
- The original EtherType is preserved inside an **LLC/SNAP** shim (`AA AA 03 00 00 00` + EtherType) that sits between the 802.11 header and the IP payload.
- The destination MAC resolved by ARP becomes one of **Addr1/Addr3** depending on direction (STA→AP uses To-DS: Addr1=BSSID, Addr3=real DA).
- From the IP stack's point of view none of this happened — it still thinks it handed an Ethernet frame to an Ethernet-like device. **mac80211 hides 802.11 behind an Ethernet façade.**

> 🔑 **Tie-back to ESP32:** in the open-MAC build, `encapsulate_and_send()` did exactly this (Eth → 802.11 + LLC/SNAP, set FromDS, fill Addr1/2/3). On Linux the same job is `mac80211`'s `ieee80211_xmit()` path. Same transformation, different layer owner.

## 2.5  The skb as the universal carrier

Throughout the entire path **one `sk_buff` is reused**; each layer prepends its header into the pre-reserved headroom:

```text
TX (going down — each layer skb_push()es its header):

  ping payload
  + ICMP header        <- L4 (icmp_push_reply / raw)
  + IP header          <- L3 (ip_build_and_send / ip_finish_output)
  + 802.11 + LLC/SNAP  <- mac80211 (replaces the Ethernet header)
  ---------------------------------------------
  = the bytes DMA'd to the chip

RX (going up — each layer skb_pull()s its header):

  hardware DMAs frame into an skb
  - strip 802.11 + LLC/SNAP   -> mac80211 hands an 802.3 skb up (netif_rx/NAPI)
  - strip Ethernet, set skb->protocol -> __netif_receive_skb -> ip_rcv
  - strip IP                  -> icmp_rcv
  - ICMP Echo Reply matched   -> delivered to ping's socket
```

> 🔑 The reason the stack is fast is that this is **all pointer arithmetic on one buffer** — `skb_reserve()` makes headroom up front, `skb_push()`/`skb_pull()` move the `data` pointer. No per-layer `memcpy` of the payload. (Contrast: the ESP32 prototype *did* copy the Ethernet frame into a fresh malloc buffer in `c_transmit_data_frame()` — a deliberate prototype simplification; production Linux is zero-copy here.)

---

# Part 3 — Gap #2: One Control Command and One Data Command, end to end

> **The exact interview ask:** *"Give me a complete flow for one control command and one data command — Linux platform-wise."*

## 3.1  Control plane vs data plane — and why they are separate

| | **Control plane** | **Data plane** |
|---|---|---|
| Purpose | configure the device: scan, connect, set channel, install keys, up/down | move packets: your `ping`, TCP, UDP traffic |
| User entry | `iw`, `wpa_supplicant`, `NetworkManager` | `socket()` + `send()/recv()` (any app) |
| Kernel transport | **netlink** socket → `nl80211` (generic netlink family) | the **IP stack** → `net_device` |
| Kernel path | `nl80211` → `cfg80211` → `mac80211`/driver `ops` | socket → IP → `mac80211` TX → driver `tx()` |
| Frequency | rare, human/daemon-driven (per second/minute) | hot path, millions of packets/sec |
| Latency budget | milliseconds is fine | per-packet, must not stall |

> 🔑 They are separate so the **hot data path never blocks on slow configuration**, and so policy/regulatory checks (`cfg80211` enforces the regulatory domain, valid channels, etc.) live in one place. Same principle as the ESP32 guide's two-task split — config and packet-pumping are decoupled.

---

## 3.2  CONTROL command walkthrough — `iw dev wlan0 set channel 6`

A small, self-contained control command makes the whole chain visible.

```mermaid
sequenceDiagram
    participant IW as iw (user space, libnl)
    participant NL as Netlink socket (NETLINK_GENERIC)
    participant N80 as nl80211 (genl family)
    participant CFG as cfg80211
    participant MAC as mac80211 (SoftMAC)
    participant DRV as driver (e.g. ath9k)
    participant HW as chip + firmware

    IW->>NL: build genl msg: NL80211_CMD_SET_CHANNEL<br/>attrs: ifindex(wlan0), freq=2437MHz
    Note over IW,NL: AF_NETLINK / NETLINK_GENERIC socket, then send
    NL->>N80: genl dispatch -> nl80211_set_channel()
    N80->>N80: parse attrs, validate ifindex/wiphy
    N80->>CFG: cfg80211_set_monitor_channel()/rdev_set_channel
    CFG->>CFG: regulatory check: is 2437MHz allowed here?
    CFG->>MAC: rdev->ops->set_channel() == ieee80211_ops.config
    MAC->>DRV: drv_config(): IEEE80211_CONF_CHANGE_CHANNEL
    DRV->>HW: program PHY synth / write registers / fw command
    HW-->>DRV: done
    DRV-->>IW: netlink ACK propagates back (return 0)
```

**Named-function call path:**

```text
USER:    iw dev wlan0 set channel 6
LIB:     libnl builds a Generic Netlink message:
            family=nl80211, cmd=NL80211_CMD_SET_CHANNEL,
            NL80211_ATTR_IFINDEX, NL80211_ATTR_WIPHY_FREQ=2437
SYSCALL: sendmsg() on an AF_NETLINK / NETLINK_GENERIC socket
KERNEL:  netlink_rcv -> genl_rcv -> genl_family_rcv_msg
            -> nl80211 doit handler: nl80211_set_channel()
CFG80211: cfg80211_set_monitor_channel() / nl80211_parse_chandef()
            -> regulatory_check (channel legal in current reg domain?)
            -> rdev_set_channel() -> rdev->ops->set_channel()
MAC80211: for SoftMAC, ops map into mac80211:
            ieee80211_set_channel -> ieee80211_hw_config()
            -> drv_config(local, IEEE80211_CONF_CHANGE_CHANNEL)
DRIVER:  local->ops->config()  e.g. ath9k_config()
            -> ath9k_set_channel() -> ath9k_hw_reset() programs PHY/synth
HARDWARE: PLL/synth retuned to 2437 MHz (channel 6)
RETURN:  0 propagates up; netlink ACK to iw
```

> 🔑 The shape to memorise: **`iw`/`wpa_supplicant` → netlink → `nl80211` → `cfg80211` (policy/regulatory) → `mac80211` (`ieee80211_ops`) → driver `ops` → firmware/registers.** Every control command (scan, connect, set-key, set-power, set-channel) follows this spine; only the `NL80211_CMD_*` and the `ops` callback change.

---

## 3.3  CONTROL command (richer) — associating to an AP via `wpa_supplicant`

`set channel` is one hop; **connect** exercises the whole control plane and shows where the 802.11 management frames are built.

```text
USER:     wpa_supplicant (or 'iw dev wlan0 connect SSID')
NL80211:  NL80211_CMD_TRIGGER_SCAN  -> driver scans, results via
          NL80211_CMD_NEW_SCAN_RESULTS (cfg80211_scan_done)
          NL80211_CMD_AUTHENTICATE   -> nl80211_authenticate()
          NL80211_CMD_ASSOCIATE      -> nl80211_associate()
CFG80211: cfg80211 sanity + regulatory; calls rdev->ops->{auth,assoc}
MAC80211: ieee80211_mgd_auth() / ieee80211_mgd_assoc()
            -> BUILDS the 802.11 Authentication / Association Request
               MANAGEMENT frames in software (this is the SoftMAC job)
            -> ieee80211_tx_skb() -> driver tx() to put mgmt frame on air
DRIVER:   ieee80211_ops.tx() -> DMA the mgmt frame; HW does DCF/ACK
HW:       auth/assoc exchange on air; AP replies
UP:       responses RX'd -> mac80211 parses -> cfg80211_rx_assoc_resp()
            -> NL80211_CMD_CONNECT result back to wpa_supplicant
THEN:     EAPOL 4-way handshake (wpa_supplicant in user space) over the
          DATA path as normal data frames; keys installed via
          NL80211_CMD_NEW_KEY -> rdev->ops->add_key -> drv set_key()
```

> 🔑 Two facts that impress here: (1) for **SoftMAC**, the **management frames (Auth/Assoc) are constructed by `mac80211` in the kernel**, not the firmware — exactly like the ESP32 `build_authentication_frame()`/`build_association_request()`. (2) The **EAPOL 4-way handshake runs in user space (`wpa_supplicant`)** and travels as ordinary **data frames** — control plane sets up the link, then a data-plane exchange establishes keys, which are pushed back down via `NL80211_CMD_NEW_KEY`.

---

## 3.4  DATA command walkthrough — a `ping` packet to the air and back

This is the data-plane counterpart and it stitches Part 2 to the driver/hardware.

### TX (down the stack)

```text
USER:    ping -> sendto()                              [user space]
SOCKET:  __sys_sendto -> sock_sendmsg -> inet_sendmsg
L4/ICMP: raw_sendmsg / ping_v4_sendmsg  (build ICMP echo)
L3 IP:   ip_send_skb -> ip_output -> ip_finish_output2
NEIGH:   neigh_output -> (ARP if needed) -> dst MAC resolved
L2:      dev_hard_header() writes Ethernet-style header
QDISC:   __dev_queue_xmit -> qdisc enqueue -> qdisc_run
NETDEV:  netdev_start_xmit -> ndo_start_xmit
            For a Wi-Fi netif this enters mac80211:
MAC80211: ieee80211_subif_start_xmit()
            -> ieee80211_xmit() : 802.3 -> 802.11 + LLC/SNAP (see 2.4)
            -> sequence number, QoS TID, encryption (if keyed)
            -> ieee80211_tx_frags() -> drv_tx()
DRIVER:  ieee80211_ops.tx(hw, control, skb)  e.g. ath9k_tx()
            -> dma_map_single(skb->data)  (get bus address)
            -> build TX descriptor: buf addr, len, rate, flags
            -> push to TX DMA ring; write 'TX DP'/doorbell register
HW/PHY:  DMA reads the frame; MAC does DCF (CCA, DIFS, backoff),
         transmits at chosen rate, awaits 802.11 ACK (all in silicon)
IRQ:     TX-done interrupt -> driver reaps descriptor ->
         ieee80211_tx_status() -> dev_kfree_skb() (skb freed)
```

### RX (up the stack)

```text
HW:      frame arrives; PHY demod; MAC checks addr filter, AUTO-ACKs
         (SIFS, hardware); DMAs frame into an RX buffer/descriptor
IRQ:     RX interrupt -> driver ISR (top half) just schedules NAPI
NAPI:    driver->poll() (e.g. ath9k_rx_tasklet/napi) runs in softirq:
            for each RX descriptor with data:
              build/refill skb, dma_unmap, set skb->dev = wlan0
              ieee80211_rx() / ieee80211_rx_napi()
MAC80211: parse 802.11 header, decrypt, reorder (BA), de-aggregate,
          strip 802.11 + LLC/SNAP -> 802.3 skb, set skb->protocol
            -> netif_receive_skb() / napi_gro_receive()
L3 IP:   __netif_receive_skb_core -> ip_rcv -> ip_local_deliver
L4/ICMP: icmp_rcv : Echo Reply matched to the ping socket
USER:    recvmsg() in ping returns; round-trip time printed
```

```mermaid
flowchart TD
    PING["ping: sendto()"] --> SOCK["socket -> IP -> neigh/ARP -> dev_hard_header"]
    SOCK --> NDO["ndo_start_xmit (wlan0)"]
    NDO --> M["mac80211: 802.3 -> 802.11 + LLC, seq, crypto"]
    M --> TX["driver tx(): dma_map + TX descriptor + doorbell"]
    TX --> AIR(("DCF in HW: CCA/backoff/TX/ACK -> AIR"))
    AIR -. "reply frame" .-> RXHW["HW RX + auto-ACK (SIFS) + DMA"]
    RXHW --> NAPI["IRQ -> NAPI poll (softirq)"]
    NAPI --> M2["mac80211: 802.11 -> 802.3, decrypt, reorder"]
    M2 --> IP["netif_receive_skb -> ip_rcv -> icmp_rcv"]
    IP --> PING2["ping: recvmsg() prints RTT"]
```

> 🔑 **NAPI is the Linux answer to "don't drown in interrupts."** The hardware RX interrupt does almost nothing — it **schedules NAPI** and the actual receive processing runs in a **softirq poll loop**, draining many frames per interrupt. This is precisely the ESP32 guide's **top-half / bottom-half** split (tiny ISR posts an event; a deferred context does the real work), implemented with NAPI instead of a FreeRTOS queue.

> 🔑 **Where DCF lives (unchanged from the ESP32 story):** the driver's job ends at "build descriptor + ring doorbell." **CCA, DIFS, random backoff, the transmit, and the SIFS-bounded ACK are all in the chip.** Linux never runs the microsecond MAC timing — same boundary, different OS.

---

# Part 4 — Gap #3: User-Space → Kernel-Space Driver

> **The exact question that caught you off guard:** *"How does a user-space request to turn on Wi-Fi get passed to the kernel-space driver? How does the kernel do this? How are the driver's `open`/`close`/`read`/`write` linked to the user-space system call / file / socket?"*

The honest expert answer has **two halves**, because Linux has **two driver entry models** (recall Part 1.1). The interviewer's mention of `open/read/write` is the **char-device (VFS) model**; "Wi-Fi" and "socket" is the **network-device model**. You score by explaining both and saying which one Wi-Fi actually uses.

## 4.1  "Turn on Wi-Fi" — the three real paths

"Turn on Wi-Fi" is ambiguous; name the three things it can mean and the path each takes:

| User action | Mechanism | Reaches driver via |
|---|---|---|
| `ip link set wlan0 up` | netlink **RTM_NEWLINK** (rtnetlink) → `net_device` | **`ndo_open()`** |
| Toggle the radio kill-switch (airplane mode) | **rfkill** subsystem (`/dev/rfkill`, sysfs) | driver `rfkill` ops / `wiphy` |
| NetworkManager "enable Wi-Fi" / connect | **nl80211** netlink → `cfg80211` | `cfg80211`/`mac80211` → driver `ops` |

The cleanest one to trace is `ip link set wlan0 up`:

```mermaid
sequenceDiagram
    participant IP as ip (iproute2)
    participant RTN as rtnetlink socket (NETLINK_ROUTE)
    participant CORE as net core (dev.c)
    participant DRV as driver

    IP->>RTN: RTM_NEWLINK, ifi_flags |= IFF_UP, ifindex=wlan0
    Note over IP,RTN: AF_NETLINK / NETLINK_ROUTE socket, then send
    RTN->>CORE: rtnetlink_rcv -> rtnl_newlink -> do_setlink
    CORE->>CORE: dev_change_flags() -> __dev_open()
    CORE->>DRV: dev->netdev_ops->ndo_open(dev)
    Note over DRV: e.g. ieee80211_open then ieee80211_do_open<br/>powers radio, allocs rings, starts firmware, starts queue
    DRV-->>CORE: 0 (success) -> dev marked IFF_UP & __LINK_STATE_START
    CORE-->>IP: netlink ACK
```

```text
USER:   ip link set wlan0 up
LIB:    iproute2 builds RTM_NEWLINK with IFF_UP over NETLINK_ROUTE
KERNEL: rtnetlink_rcv_msg -> rtnl_newlink/rtnl_setlink -> do_setlink
        -> dev_change_flags(dev, flags|IFF_UP)
        -> __dev_open(dev):
              if (netdev_ops->ndo_validate_addr) ...
              netdev_ops->ndo_open(dev);   <=== DRIVER ENTRY POINT
              set bit __LINK_STATE_START; netif_start_queue()
WIFI:   for mac80211 ifaces ndo_open == ieee80211_open
            -> ieee80211_do_open(): add interface, drv_start() if first,
               power up radio, start RX, begin allowing TX
RESULT: wlan0 is administratively UP; data path can now run
```

## 4.2  The VFS model — how `open/read/write/ioctl` reach a *char* driver

This is the model the interviewer's wording (`open/read/write`) refers to. It is how **character devices** (UART, GPIO, a custom driver exposing `/dev/foo`) work — and it's the right thing to explain to show you understand the file abstraction, *before* clarifying that Wi-Fi differs.

**Registration:** a char driver fills a `struct file_operations` and binds it to a device number:

```c
static const struct file_operations my_fops = {
    .owner          = THIS_MODULE,
    .open           = my_open,     // <- userspace open("/dev/foo")
    .release        = my_release,  // <- userspace close(fd)
    .read           = my_read,     // <- userspace read(fd, ...)
    .write          = my_write,    // <- userspace write(fd, ...)
    .unlocked_ioctl = my_ioctl,    // <- userspace ioctl(fd, CMD, arg)
};
/* register: register_chrdev() or cdev_add() ties a dev_t -> my_fops */
```

**The linkage, syscall by syscall:**

```mermaid
flowchart TD
    U1["open('/dev/foo')"] --> S1["sys_openat -> do_sys_open"]
    S1 --> V1["VFS: path lookup finds inode (char dev_t)"]
    V1 --> C1["chrdev_open(): inode->i_cdev -> file->f_op = my_fops"]
    C1 --> D1["calls my_fops.open == my_open(inode,file)"]

    U2["read(fd,buf,n)"] --> S2["sys_read -> vfs_read"]
    S2 --> D2["file->f_op->read == my_read()"]

    U3["ioctl(fd,CMD,arg)"] --> S3["sys_ioctl -> vfs_ioctl"]
    S3 --> D3["file->f_op->unlocked_ioctl == my_ioctl()"]
```

```text
open("/dev/foo")  -> sys_openat -> do_sys_openat2 -> do_filp_open
                  -> VFS resolves the inode; sees S_ISCHR (char device)
                  -> chrdev_open(): looks up the cdev by major/minor,
                     sets file->f_op = driver's file_operations,
                     then calls f_op->open()  ===> my_open()
read(fd,...)      -> sys_read -> ksys_read -> vfs_read -> f_op->read  ===> my_read()
write(fd,...)     -> sys_write -> vfs_write -> f_op->write           ===> my_write()
ioctl(fd,CMD,..)  -> sys_ioctl -> vfs_ioctl -> f_op->unlocked_ioctl  ===> my_ioctl()
close(fd)         -> __close_fd -> filp_close -> f_op->release        ===> my_release()
```

> 🔑 **The one-sentence mechanism:** *the kernel `struct file` for an open fd has an `f_op` pointer; every `read/write/ioctl/close` syscall is a thin VFS wrapper that dereferences `file->f_op->{read,write,...}` and calls the driver's function.* That pointer was installed at `open()` time from the device's registered `file_operations`. **This is the universal "syscall → driver function" bridge for char/block devices.**

## 4.3  The network model — how `socket()` and `ip link` reach a *net* driver

**Wi-Fi does not use the file model above.** `wlan0` has no `/dev/wlan0`; you never `read()`/`write()` it. Instead there are **two distinct user→kernel→driver bridges**:

**(a) Data: `socket()` → protocol ops → `net_device` ndo_***

```text
socket(AF_INET, SOCK_DGRAM, 0)
   -> sys_socket -> sock_create -> inet_create
   -> file->f_op = &socket_file_ops   (a socket IS an fd, but its f_op
        routes to the protocol, not to a device)
send()/sendto()
   -> sys_sendto -> sock_sendmsg -> sock->ops->sendmsg (inet_sendmsg)
   -> ... IP stack ... -> dev_queue_xmit
   -> dev->netdev_ops->ndo_start_xmit(skb, dev)   <=== DRIVER TX ENTRY
recv()/recvfrom()
   -> data arrives via NAPI -> netif_receive_skb -> IP -> socket queue
   -> sock->ops->recvmsg returns it to userspace
```

So a socket fd's `read/write` (yes, you *can* `read()`/`write()` a socket) are routed by `socket_file_ops` to `sock_read_iter`/`sock_write_iter` → `sock->ops` (the **protocol**), **never** to a device's `read`. The device is reached only through the **IP stack → `ndo_start_xmit`**, and inbound through **NAPI → `netif_receive_skb`**. There is no `ndo_read`/`ndo_write` — packets are pushed/pulled as skbs, not byte streams.

**(b) Control: `ip`/`iw`/`wpa_supplicant` → netlink socket → subsystem → driver ops**

```text
socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE|NETLINK_GENERIC)
   -> a netlink socket; send() a structured message
RTM_NEWLINK (IFF_UP)  -> rtnetlink -> __dev_open -> ndo_open()   (4.1)
NL80211_CMD_*         -> genl -> nl80211 -> cfg80211 -> mac80211/driver ops (3.2)
```

> 🔑 **The crisp answer to the interviewer's question:** *"Turning on/controlling Wi-Fi does **not** go through a `/dev` file's `open/read/write`. A Wi-Fi interface is a **network device**, not a char device. Configuration (up, channel, connect, keys) travels over a **netlink socket** to rtnetlink/`nl80211` → `cfg80211` → `mac80211` → the driver's **`ndo_open`** and **`ieee80211_ops`** callbacks. Data travels via **`socket()` → IP stack → `ndo_start_xmit`**, with RX coming back through **NAPI → `netif_receive_skb`**. The classic `file->f_op->{open,read,write,ioctl}` bridge is the **char-device** model — correct for a UART or a custom `/dev` driver, but not how `wlan0` works."*

## 4.4  Side-by-side — the three bridges

```mermaid
flowchart TD
    subgraph CHAR["CHAR DEVICE (e.g. /dev/ttyS0)"]
        c1["open/read/write/ioctl(fd)"] --> c2["VFS: file->f_op"] --> c3["driver file_operations"]
    end
    subgraph NETDATA["NET DEVICE — DATA"]
        d1["socket(); send()/recv()"] --> d2["sock->ops (protocol) -> IP stack"] --> d3["ndo_start_xmit / netif_receive_skb"]
    end
    subgraph NETCTRL["NET DEVICE — CONTROL"]
        e1["ip / iw / wpa_supplicant"] --> e2["netlink: rtnetlink / nl80211 -> cfg80211"] --> e3["ndo_open / ieee80211_ops"]
    end
```

| Aspect | Char driver | Net device (data) | Net device (control) |
|---|---|---|---|
| User fd from | `open("/dev/x")` | `socket()` | `socket(AF_NETLINK,..)` |
| Kernel dispatch table | `struct file_operations` | `struct proto_ops` + `struct net_device_ops` | `genl_ops`/rtnetlink + `cfg80211_ops`/`ieee80211_ops` |
| "open" maps to | `f_op->open` | `ndo_open` (via `ip link up`) | `ndo_open` / `cfg80211` start |
| "write/tx" maps to | `f_op->write` | `ndo_start_xmit` | n/a (config messages) |
| "read/rx" maps to | `f_op->read` | NAPI → `netif_receive_skb` | netlink reply/event |
| Used by Wi-Fi? | ❌ no `/dev/wlan0` | ✅ data path | ✅ control path |

> 🔑 If you remember one diagram from this whole document, make it this one. The interviewer's question conflated three bridges; naming all three and assigning Wi-Fi to the right two is the complete answer.

---

# Appendix A — Rapid-fire answers to the exact questions asked

Use these as 20–30-second spoken answers. Each maps to a specific piece of the Cisco feedback.

### Q1. "You run `ping` — what happens, what goes to L2 and how?"
> `ping` does `sendto()` on an ICMP socket. The kernel builds the ICMP Echo and IP header, then does a **route lookup** to pick the egress device (`wlan0`) and the **next-hop IP**. The **neighbour/ARP** subsystem turns that next-hop IP into a **MAC address**. At `dev_hard_header()` the link layer prepends an L2 header `{dst MAC, src MAC, EtherType}` and the skb is queued to the device's `ndo_start_xmit()`. **What "goes to L2" is the skb** — IP+ICMP as an opaque payload, plus two pieces of metadata: the EtherType and the resolved destination MAC.

### Q2. "How does L2 know the frame type and address *from the ICMP packet*?"
> It doesn't read the ICMP packet at all. **The frame type comes from `skb->protocol`** (`ETH_P_IP`), set by the IP layer — L2 just copies it into the Type field. **The destination MAC comes from routing + ARP**, not from ICMP: the destination IP drives a routing lookup to a next hop, and ARP resolves that next hop's MAC. If the target is off-subnet, the L2 destination is the **gateway's** MAC — which proves L2 addressing is a routing/ARP result, not an ICMP field.

### Q3. "Where does Ethernet become 802.11?"
> In **`mac80211`** on the way down (`ieee80211_subif_start_xmit` → `ieee80211_xmit`). The IP stack thinks `wlan0` is Ethernet; `mac80211` replaces the 802.3 header with an **802.11 MAC header (Addr1/2/3, FrameCtrl, Seq)** and inserts an **LLC/SNAP** shim carrying the original EtherType. This is the Linux version of the ESP32 `encapsulate_and_send()`.

### Q4. "Give a complete flow for one CONTROL command."
> `iw dev wlan0 set channel 6`: `iw` sends a **Generic Netlink** message (`NL80211_CMD_SET_CHANNEL`) over an `AF_NETLINK` socket → `nl80211_set_channel()` → **`cfg80211`** does the **regulatory check** → `rdev->ops->set_channel` maps into **`mac80211`** `ieee80211_hw_config()` → `drv_config()` → the **driver** (`ath9k_set_channel`) reprograms the PHY synthesiser. Spine for *every* control command: **netlink → nl80211 → cfg80211 → mac80211/driver ops → firmware.**

### Q5. "Give a complete flow for one DATA command."
> A `ping` packet: `sendto()` → IP → ARP/neigh → `dev_hard_header` → `ndo_start_xmit` → **`mac80211`** (802.3→802.11, sequence, crypto) → **driver `tx()`** (`dma_map`, build TX descriptor, ring doorbell) → **hardware DCF** (CCA/backoff/TX/ACK) → air. RX comes back via **IRQ → NAPI poll (softirq)** → `mac80211` (802.11→802.3) → `netif_receive_skb` → `ip_rcv` → `icmp_rcv` → the socket.

### Q6. "How does a user-space request to turn on Wi-Fi reach the kernel driver?"
> `ip link set wlan0 up` sends **rtnetlink `RTM_NEWLINK`** with `IFF_UP` → `__dev_open()` → **`dev->netdev_ops->ndo_open()`** (for mac80211, `ieee80211_open`), which powers the radio and starts queues. It is **not** a `/dev` file open — a Wi-Fi interface is a **network device**, reached via netlink, not via `open("/dev/...")`.

### Q7. "How are the driver's open/close/read/write linked to syscall / file / socket?"
> Two different models. For a **char device**, the kernel's `struct file` for an fd has an **`f_op`** pointer; `read/write/ioctl/close` syscalls are VFS wrappers that call `file->f_op->{read,write,...}`, installed from the driver's `file_operations` at `open()`. **Wi-Fi uses the network model instead**: there's no `/dev/wlan0`. **Data** goes `socket()` → IP stack → **`ndo_start_xmit`** (TX) and **NAPI → `netif_receive_skb`** (RX); **control** goes over **netlink** to `ndo_open` / `ieee80211_ops`. So the `open/read/write/ioctl→file_operations` bridge is the **char-device** answer; for Wi-Fi the bridges are **`socket`→`ndo_*`** and **netlink→`cfg80211/mac80211 ops`**.

### Q8. "SoftMAC vs FullMAC on Linux?"
> **SoftMAC** = the 802.11 MAC state machine (auth/assoc, sequencing, queue mgmt) runs in **`mac80211`** in the kernel; drivers like `ath9k`/`mt76`. **FullMAC** = that MAC lives in **firmware**; the driver (e.g. `brcmfmac`) talks to `cfg80211` directly with no `mac80211`. Either way the **microsecond DCF (CCA/SIFS/backoff/ACK) is in silicon** — the dividing line is only about where the millisecond MAC management runs.

### Q9. "Why are control and data planes separate?"
> So the **hot data path never blocks on slow configuration**, and so **policy/regulatory enforcement** lives in one place (`cfg80211`). Control is rare and netlink-driven; data is per-packet and must not stall. Same rationale as the ESP32 two-task (MAC-task vs hardware-task) split.

---

## 🔗 Mapping back to the ESP32/FreeRTOS reference guide

| Concept | ESP32 / FreeRTOS (reference doc) | Linux (this doc) |
|---|---|---|
| MAC state machine (SoftMAC) | `c_mac_task` / `80211_mac.c` | **`mac80211`** |
| Config/policy layer | (implicit in app) | **`cfg80211`** + **`nl80211`** |
| Eth → 802.11 encapsulation | `encapsulate_and_send()` | `ieee80211_xmit()` (LLC/SNAP) |
| TX entry point | `rs_tx_smart_frame()` → `transmit_80211_frame()` | `ndo_start_xmit` → driver `tx()` |
| RX deferral (top/bottom half) | tiny ISR posts `RX_ENTRY`; hardware task drains | tiny IRQ schedules **NAPI**; softirq poll drains |
| Packet buffer | smart frame (`rs_smart_frame_t`) | **`sk_buff`** (zero-copy `skb_push/pull`) |
| DCF timing | in silicon (GO bit → hardware) | in silicon (driver builds descriptor → hardware) |
| Control vs data split | MAC-task vs hardware-task | control plane (netlink/cfg80211) vs data plane (IP/ndo) |

> The mental model transfers cleanly: **microseconds are silicon, milliseconds are software** — on Linux the "software" is split into the netlink/`cfg80211`/`mac80211` control spine and the `socket`/IP/`ndo_start_xmit` data spine.
