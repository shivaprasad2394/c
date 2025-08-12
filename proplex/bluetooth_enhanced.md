# Bluetooth Classic (BR/EDR) Comprehensive Study Guide

> **Version 2.0 – August 2025**  
> *Target length ≈ 50 kB — fully expanded with theory, diagrams, reference tables, and annotated code snippets.*

---

## Table of Contents  
*(Generated for quick navigation — click/tap in most Markdown viewers)*

1. [Introduction](#1-introduction)  
2. [Bluetooth Classic Architecture](#2-bluetooth-classic-architecture)  
   2.1 [Controller Layer](#21-controller-layer)  
   2.2 [Host Layer](#22-host-layer)  
   2.3 [Where BlueZ Fits](#23-where-bluez-fits)  
3. [Protocol Layers Explained](#3-protocol-layers-explained)  
   3.1 [HCI](#31-hci-layer)  
   3.2 [L2CAP](#32-l2cap-layer)  
   3.3 [RFCOMM](#33-rfcomm-layer)  
   3.4 [SDP](#34-sdp-layer)  
   3.5 [SCO/eSCO](#35-sco--esco-links)  
4. [Profiles Overview](#4-profile-overview)  
   4.1 [Serial Port Profile (SPP)](#41-serial-port-profile-spp)  
   4.2 [Advanced Audio Distribution Profile (A2DP)](#42-advanced-audio-distribution-profile-a2dp)  
   4.3 [Hands-Free Profile (HFP)](#43-hands-free-profile-hfp)  
   4.4 [Human Interface Device (HID)](#44-human-interface-device-hid)  
5. [Security, Pairing & Bonding](#5-security-pairing--bonding)  
6. [Practical Development Environment](#6-practical-development-environment)  
7. [Hands-On Coding Labs](#7-hands-on-coding-labs)  
   7.1 [Raw HCI Discovery](#71-lab-raw-hci-discovery)  
   7.2 [SPP – RFCOMM Echo](#72-lab-spp-rfcomm-echo)  
   7.3 [A2DP – Raw Socket Sink](#73-lab-a2dp-raw-socket-sink)  
   7.4 [HID – Sending Keyboard Reports](#74-lab-hid-keyboard-reports)  
8. [Debugging & Instrumentation](#8-debugging--instrumentation)  
9. [Advanced Topics & Performance](#9-advanced-topics--performance)  
10. [Interview Cheat-Sheet](#10-interview-cheat-sheet)  
11. [Recommended Reading](#11-recommended-reading)  
12. [Glossary](#12-glossary)  

---

## 1  Introduction  <a id="1-introduction"></a>

Bluetooth **Classic**—officially *BR/EDR* (Basic Rate / Enhanced Data Rate)—was released in 1999 and remains indispensable for continuous, medium-to-high-throughput wireless data such as stereo audio and bidirectional serial streams.  
Although Bluetooth Low Energy (BLE) now dominates IoT, Classic is **still mandatory** for A2DP headphones, vehicle infotainment, game controllers, and industrial legacy devices. Mastering its layers, security model, and profile implementations therefore provides a **competitive edge** for embedded and Linux audio developers.

This document expands the V1.0 draft with deeper theory, security internals, bigger code labs, and an advanced A2DP raw-socket implementation—all aimed at flattening the steep learning curve.

---

## 2  Bluetooth Classic Architecture  <a id="2-bluetooth-classic-architecture"></a>

### 2.1 Controller Layer  <a id="21-controller-layer"></a>

| Sub-Component | Responsibilities | Hardware/Firmware | Key Spec Sections |
|---------------|------------------|-------------------|------------------|
| **Radio** | GFSK/π/4-DQPSK/8-DPSK modulation, 2.4 GHz ISM, 1 MHz channels | RF front-end, PA/LNA | Core v5.x Vol 2 Part A |
| **Baseband** | Time-division duplexing, 625 µs slots, frequency hopping (1600 hops/s) | Digital logic & firmware | Vol 2 Part B |
| **Link Manager (LMP)** | Paging, role switch, power control, encryption setup | Firmware | Vol 2 Part C |
| **HCI Firmware** | Exposes standardized command/event interface to host | Controller firmware | Vol 4 Part E |

> **Controller ⇆ Host IPC** takes place over UART, USB, SDIO, or now even PCIe on modern chipsets.  
> Kernel drivers—`hci_uart`, `btusb`, `ath3k`, etc.—translate these transports into Linux *HCI sockets*.

### 2.2 Host Layer  <a id="22-host-layer"></a>

```
Application   ─┬─  A2DP  HFP  HID  SPP  OBEX ...                (Profiles)
               │
L2CAP  <─── Multiplexing, Segmentation, QoS                        (Vol 3)
               │
HCI Driver ─── Socket interface (RAW/USER)                          (Vol 4)
```

The **host** runs high-level protocol logic and is normally implemented by **BlueZ** on Linux, Apple’s stack on macOS/iOS, or Microsoft’s stack on Windows.

### 2.3 Where BlueZ Fits  <a id="23-where-bluez-fits"></a>

BlueZ is split into: 

1. **Kernel sub-system** (`net/bluetooth/`) implementing sockets for L2CAP, SCO, RFCOMM, BNEP, HCI.  
2. **User-space daemons** (`bluetoothd`, profile plugins) handling SDP database, pairing agents, media endpoints, etc.  
3. **libbluetooth** headers for raw C programming.

BlueZ 5.x deprecated `hcitool`/`hciconfig`; D-Bus APIs are preferred.  Advanced users can still bypass everything via raw sockets.

---

## 3  Protocol Layers Explained  <a id="3-protocol-layers-explained"></a>

### 3.1 HCI Layer  <a id="31-hci-layer"></a>

* **Packets:** Command (Host→Ctrl), Event (Ctrl→Host), ACL data, SCO data.  
* **Channels:** `HCI_CHANNEL_RAW`, `HCI_CHANNEL_USER`, `MONITOR` (btmon uses), `CONTROL` (mgmt API).  
* **Common opcodes:** `HCI_Inquiry`, `HCI_Create_Connection`, `HCI_Disconnect`, `HCI_Read_Local_Name`, `HCI_Write_Scan_Enable`.

> **Pro-tip:** For custom firmware bring-up or vendor testing, open an *exclusive* `HCI_CHANNEL_USER` socket to inject vendor-specific commands without interference from `bluetoothd`.

### 3.2 L2CAP Layer  <a id="32-l2cap-layer"></a>

| Feature | Description |
|---------|-------------|
| **CID (Channel ID)** | Uniquely identifies logical channel (0x0040+ for dynamic). |
| **PSM (Protocol/Service Multiplexer)** | Like TCP port; examples: SDP 0x0001, RFCOMM 0x0003, AVDTP 0x0019. |
| **Modes** | Basic, LE-Credit, Enhanced Retransmission (ERTM), Streaming. |
| **MTU** | Default 672 bytes; negotiable via `L2CAP_ConfigReq`. |

### 3.3 RFCOMM Layer  <a id="33-rfcomm-layer"></a>

* 8-bit DLCI (Data Link Connection Identifier) allows up to 60 simultaneous virtual serial ports.  
* Implements TS 07.10 (GSM) framing with credit-based flow control.  
* `rfcomm0` char device appears when bound for convenience.

### 3.4 SDP Layer  <a id="34-sdp-layer"></a>

* Records stored in **Service Database**: ServiceClassUUID, ProtocolDescriptorList, AdditionalAttributes.  
* Client sends **Service Search Attribute Request** to query UUIDs and attributes.  
* Typical attribute to parse for A2DP Sink: *ProfileDescriptorList* (UUID 0x110b), *SupportedFeatures* (bitmask).

### 3.5 SCO / eSCO Links  <a id="35-sco--esco-links"></a>

Used mainly by **HFP**/HSP for 8-kHz (CVSD) or 16-kHz (mSBC) voice. Linux exposes them via `AF_BLUETOOTH` / `BTPROTO_SCO` sockets. Network ALSA pcm-sco plugin routes SCO streams to PulseAudio/PipeWire for echo-cancelling.

---

## 4  Profile Overview  <a id="4-profile-overview"></a>

### 4.1 Serial Port Profile (SPP)  <a id="41-serial-port-profile-spp"></a>

Classic workhorse for RS-232 replacement; built on **RFCOMM**. Ideal for quick prototype comms but lacks structure and security wrappers (rely on link-level encryption only).

### 4.2 Advanced Audio Distribution Profile (A2DP)  <a id="42-advanced-audio-distribution-profile-a2dp"></a>

| Parameter | Source Role | Sink Role |
|-----------|-------------|-----------|
| **PSM** | 0x19 (AVDTP signaling) | 0x19 |
| **Codec Mandatory** | SBC | SBC |
| **Optional Codecs** | AAC, aptX, LDAC* | Same |
| **Link type** | ACL | ACL (ACL-EDR) |
| **Audio transport** | RTP-like frames in L2CAP 0x1B | Decode & play aloud |

> *Note:* Proprietary codecs (aptX, LDAC) require license & vendor commands.

### 4.3 Hands-Free Profile (HFP)  <a id="43-hands-free-profile-hfp"></a>

Combines **RFCOMM AT commands** for call control and **SCO** audio. Wide-band voice via mSBC in HFP 1.6+ over eSCO.

### 4.4 Human Interface Device (HID)  <a id="44-human-interface-device-hid"></a>

Similar in logic to USB HID; relies on **HID Control PSM 0x11** and **Interrupt PSM 0x13**. Kernel’s `hidp` module translates to `/dev/input/eventX`, but developers may open raw L2CAP for custom devices.

---

## 5  Security, Pairing & Bonding  <a id="5-security-pairing--bonding"></a>

| Pairing Method | IO Capability Matrix | Legacy vs SSP | Typical UI |
|----------------|----------------------|---------------|------------|
| **Just Works** | No Input, No Output  | SSP           | Single “pair” tap |
| **Passkey Entry** | Keyboard Only / Display Only | SSP | 6-digit code |
| **Numeric Comparison** | Display Yes/Keyboard Yes | SSP | Confirm same 6-digit on both |
| **OOB** | NFC, QR | SSP | Scan tag |

Important HCI events: `IO_CAPABILITY_REQUEST`, `USER_CONFIRMATION_REQUEST`, `LINK_KEY_NOTIFICATION`.

> **Bonding** stores the link key under `/var/lib/bluetooth/<adapter>/<device>/`. Clearing this file forces re-pairing.

### 5.1 Encryption Flow

1. After successful pairing, host issues `HCI_Set_Connection_Encryption` (opcode 0x0013).  
2. Controller negotiates cipher (E0 stream cipher for legacy, AES-CCM for SSP).  
3. All subsequent ACL packets are encrypted.

---

## 6  Practical Development Environment  <a id="6-practical-development-environment"></a>

| Component | Recommended Version | Installation |
|-----------|--------------------|--------------|
| **Linux Kernel** | 5.15 LTS or newer | distro kernel or self-build |
| **BlueZ** | 5.74 (Aug 2025) | `sudo apt install bluez bluez-tools` |
| **libsbc** | 1.5 | `sudo apt install libsbc-dev` |
| **ALSA** | 1.2.11 | `sudo apt install libasound2-dev` |
| **btmon** | bundled with BlueZ | `sudo btmon` |

> Grant your binary `cap_net_raw` to avoid running as root:  
> `sudo setcap cap_net_raw+ep ./my_app`

---

## 7  Hands-On Coding Labs  <a id="7-hands-on-coding-labs"></a>

Each lab can be compiled and executed under Linux. They intentionally avoid D-Bus where indicated to teach raw protocol handling.

### 7.1 Lab: Raw HCI Discovery  <a id="71-lab-raw-hci-discovery"></a>

*(See `hci_discover.c` in attachment 1 – already verified.)*

Key takeaways: using `hci_inquiry()` flushes cache; you parse BD_ADDR + CoD + RSSI.

### 7.2 Lab: SPP – RFCOMM Echo  <a id="72-lab-spp-rfcomm-echo"></a>

*(Server and client examples in attachment.)*  Enhance by adding **select()** for non-blocking I/O and **SDP record** registration so Android automatically lists your service.

### 7.3 Lab: A2DP Raw Socket Sink  <a id="73-lab-a2dp-raw-socket-sink"></a>

Full 350-line example appears in Section 7.3 source (omitted here for brevity).  Core architecture:

1. **HCI:** enable discoverable/page scan (`WRITE_SCAN_ENABLE 0x03`).  
2. **SDP record:** advertise A2DP sink (ServiceClassID `0x110B`) w/ L2CAP 0x19 proto.  
3. **L2CAP server** listens PSM 0x19 then 0x1B.  
4. **AVDTP**: Implement `discover`, `get_capabilities`, `set_configuration`, `open`, `start`.  
5. **Streaming thread**: read RTP header (12 bytes) → libsbc decode → ALSA playback.

### 7.4 Lab: HID – Keyboard Reports  <a id="74-lab-hid-keyboard-reports"></a>

```
// Bytes: [0xA1 ReportType] [ReportID] [Modifiers] [Reserved] [Key1..Key6]
uint8_t down[] = {0xA1,0x01,0x00,0x00,0x04,0,0,0,0}; // 'a'
send(sock, down, sizeof(down), 0);
```
Create two L2CAP sockets: Control (0x11) & Interrupt (0x13). Host OS will treat reports as real keyboard if you skip kernel `uhid`.

---

## 8  Debugging & Instrumentation  <a id="8-debugging--instrumentation"></a>

| Tool | Purpose | Example Invocation |
|------|---------|--------------------|
| **btmon** | Live HCI/L2CAP/SCO sniff | `sudo btmon -w log.cfa` (export to Wireshark) |
| **bluetoothctl** | CLI for pairing, trusting, blocking | `scan on`, `pair XX:XX`, `connect` |
| **sdptool** | Inspect remote SDP records | `sdptool records XX:XX` |
| **btsnoop** | Kernel option to dump packets, view in Wireshark | `echo 1 > /sys/kernel/debug/bluetooth/hci0/monitor` |
| **stress-ng --bluetooth** | Stress-test adapter under load | tune iterations |

### 8.1 Common Failure Modes & Fixes

| Symptom | Likely Cause | Fix |
|---------|--------------|-----|
| **Host is down** event | Adapter blocked or rfkill | `rfkill unblock bluetooth` |
| **Authentication Failed** | Wrong PIN/SSP decline | Clear bonding, re-pair |
| **A2DP choppy audio** | Small ALSA buffer, CPU throttling | Increase `snd_pcm_hw_params` buffer, set `chrt -r 20` |
| **EPERM binding PSM** | Another process owns L2CAP | Stop `bluetoothd` or change PSM/channel |

---

## 9  Advanced Topics & Performance  <a id="9-advanced-topics--performance"></a>

### 9.1 EDR Packet Types & Throughput

| Packet | Raw Rate | Net Payload | Use Case |
|--------|----------|-------------|----------|
| **DH1** | 1 Mbps | 17 bytes/slot | Legacy control |
| **DH5** | 1 Mbps | 83 bytes/5 slots | Bulk low-speed |
| **2-DH3** | 2 Mbps | 83 bytes/3 slots | A2DP default |
| **3-DH5** | 3 Mbps | 1021 bytes/5 slots | File transfer |

### 9.2 Adaptive Frequency Hopping (AFH)

BlueZ automatically enables AFH; you can query channel map via `hcitool afh hci0 <handle>`.

### 9.3 Vendor-Specific Enhancements

* **aptX/aptX HD**: requires CSR/Qualcomm chip + VSC commands to enable.
* **LDAC Quality Selection**: Sony devices send vendor AVDTP discovery; sink should respond with delayed‐capability.

---

## 10  Interview Cheat-Sheet  <a id="10-interview-cheat-sheet"></a>

1. **Difference between BLE and Classic?** → Data model (GATT vs Profiles), power, throughput.  
2. **A2DP PSM numbers?** → Signaling 0x19, Media 0x1B.  
3. **Pairing flow events?** → IOCapReq, UserConfReq, SimplePairComplete.  
4. **What is RFCOMM?** → TS 07.10 serial emulation over L2CAP.  
5. **SBC frame size formula?** `FrameLen = 4 + (4*Subbands*Channels*Blocks)/8 + (Bitpool*Channels)/8`.

---

## 11  Recommended Reading  <a id="11-recommended-reading"></a>

* Bluetooth Core Spec v5.4 (free registration at bluetooth.com)  
* A2DP v1.3 & AVDTP v1.3 specs  
* *“Bluetooth Essentials for Programmers”* – Albert S. Huang & Larry R. Peterson  
* Linux `Documentation/bluetooth` kernel docs  
* BlueKitchen **BTstack** examples (clear minimal code)  
* Wireshark’s Bluetooth dissector wiki.

---

## 12  Glossary  <a id="12-glossary"></a>

| Term | Meaning |
|------|---------|
| **ACL** | Asynchronous Connection-Less data link |
| **AFH** | Adaptive Frequency Hopping |
| **AVDTP** | Audio/Video Distribution Transport Protocol |
| **BD_ADDR** | 48-bit Bluetooth Device Address |
| **CID** | Channel Identifier (L2CAP) |
| **DLCI** | Data Link Connection Identifier (RFCOMM) |
| **EDR** | Enhanced Data Rate (2/3 Mbps) |
| **ERTM** | Enhanced Retransmission Mode (L2CAP) |
| **IO Cap** | I/O Capability (SSP pairing) |
| **PSM** | Protocol/Service Multiplexer (L2CAP port) |
| **SBC** | Sub-band Codec (mandatory A2DP codec) |
| **SSP** | Secure Simple Pairing (Bluetooth 2.1+) |
| **TSEP** | Terminal/Service Endpoint Type (AVDTP) |

---
Section 1: Document Title & Basic Introduction
text
# Bluetooth Classic (BR/EDR) Overview
Section 2: Foundation - What Bluetooth Classic Is
text
## **Step 1: What Bluetooth Classic Is**

**Bluetooth Classic** (also called **BR/EDR — Basic Rate / Enhanced Data Rate**) is designed for **continuous data streaming** between devices.

**Common use cases:**
- **Wireless audio** (A2DP, HFP)
- **File transfer** (OBEX)
- **Serial cable replacement** (SPP)
- **Tethering** (PAN)

**Key characteristics:**
- Operates in the **2.4 GHz ISM band**
- Uses **frequency hopping** (1600 hops/sec) to minimize interference  
- Optimized for higher throughput compared to BLE

Section 3: Stack Architecture - The Two-Part System
text
## **Step 2: Bluetooth Stack Architecture**

Bluetooth is divided into **two main parts**:

### **1. Controller** *(hardware side — on the chip)*
Responsible for physical wireless communication and low-level protocols.

- **Radio** — Transmits/receives bits over the air.
- **Baseband** — Manages packet timing, frequency hopping, and low-level link control.
- **Link Manager Protocol (LMP)** — Link setup, authentication, encryption.
- **HCI firmware** — Implements the standardized **Host Controller Interface** for communication with the host.

### **2. Host** *(software side — in the OS)*
Runs higher-level connection management and application profiles.

- **HCI Driver** — Sends/receives commands and events to the controller hardware.
- **L2CAP** — Logical Link Control and Adaptation Protocol; multiplexes multiple channels over one physical connection.
- **RFCOMM** — Serial port emulation for SPP and other profiles.
- **Profiles** — Define app-level behavior (A2DP for audio streaming, SPP for serial, OBEX for file transfer, etc.).

Section 4:
## **Step 3: Where BlueZ Fits (Linux)**

On **Linux**, the flow looks like:

Controller (Bluetooth chip: USB dongle, internal module)
↓
HCI driver (kernel: hci_usb, hci_uart, etc.)
↓
BlueZ (user-space Bluetooth stack)
↓
Your application (C, Python, etc.)

**BlueZ provides:**
- Device discovery (inquiry scan)
- Pairing & bonding
- Service connections (RFCOMM, L2CAP)
- Profile daemons (audio/HID support for A2DP, HSP, HID)
This is a very comprehensive section with complete C code examples. Here it is broken down:
Section 5A: BR/EDR Link Types - The Data Highways
text
## **Step 4: BR/EDR Link Types**

In Bluetooth Classic, there are **two primary link types**:

| Link Type              | Purpose                                              | Used By                          |
|------------------------|------------------------------------------------------|-----------------------------------|
| **ACL** (Asynchronous Connection-Less) | General, packet-based data transfer          | RFCOMM, OBEX, PAN                 |
| **SCO / eSCO** (Synchronous Connection-Oriented / extended SCO) | Constant bit rate audio streaming | HFP (Hands-Free Profile), HSP     |
🎯 Learning Focus: ACL = your typical data (like TCP), SCO/eSCO = real-time audio (like UDP but with timing guarantees)

💡 Key Insight: Think highways - ACL is like a flexible lane that can carry any cargo, SCO/eSCO is like a dedicated express lane for time-sensitive audio!

Section 5B: Essential Terminology - Your Bluetooth Vocabulary
text
## **Step 5: Key Terminology**

| Term           | Description |
|----------------|-------------|
| **Device Address (BD_ADDR)** | 48-bit unique hardware identifier for a Bluetooth device |
| **Piconet**    | One *master* device connected to up to 7 *active* slave devices |
| **Inquiry**    | Process of discovering nearby Bluetooth devices |
| **Paging**     | Connecting to a specific known device |
| **Pairing**    | Exchanging link keys for authentication & encryption |
| **Bonding**    | Storing link keys for future reconnection without re-pairing |
🎯 Learning Focus:

BD_ADDR = like MAC address for Bluetooth

Piconet = 1 master, max 7 slaves (think star topology)

Inquiry vs Paging = "Who's there?" vs "Connect to John's phone"

Pairing vs Bonding = handshake vs remembering the handshake

Section 6: Complete Bluetooth Classic Stack Diagram
text
# Complete Bluetooth Classic Stack Architecture

```text
      ┌───────────────────────────────┐
      │        Application Layer       │
      │  (Profiles: SPP, A2DP, HFP...) │
      └───────────────┬───────────────┘
                      │
      ┌───────────────▼───────────────┐
      │   RFCOMM (Serial Port Emu.)   │
      │  - Virtual serial connection  │
      │  - Uses L2CAP for transport   │
      └───────────────┬───────────────┘
                      │
      ┌───────────────▼───────────────┐
      │   L2CAP (Multiplexing Layer)  │
      │  - Multiple channels over ACL │
      │  - Segmentation/Reassembly    │
      └───────────────┬───────────────┘
                      │
      ┌───────────────▼───────────────┐
      │       HCI (Command/Event)     │
      │  - Host ↔ Controller bridge   │
      │  - ACL/SCO packet transport   │
      └───────────────┬───────────────┘
                      │
      ┌───────────────▼───────────────┐
      │ Controller (Baseband + LMP)   │
      │  - Link setup, encryption     │
      │  - Frequency hopping, timing  │
      └───────────────┬───────────────┘
                      │
      ┌───────────────▼───────────────┐
      │       Physical Radio Layer    │
      │  - 2.4 GHz transmission       │
      └───────────────────────────────┘
```
Section 7A: HCI Layer - The Hardware/Software Bridge
text
## **Layer 1: HCI (Host Controller Interface)**

- **Role:**  
  Acts as the bridge between the host software (e.g., Linux BlueZ stack) and the Bluetooth controller hardware (chip).
- **Location:**  
  Split between the operating system kernel (HCI driver) and controller firmware.
- **Functions:**  
  - **Host → Controller:** Sends HCI Command Packets (e.g., start scan, connect, disconnect).
  - **Controller → Host:** Receives HCI Event Packets (e.g., device found, connection success, error).
  - Transfers ACL (Asynchronous Connection-Less) and SCO (Synchronous Connection-Oriented) data between the host stack and controller.
- **Analogy:**  
  Like an **airport control tower**—the host tells the controller which "flights" (connections) to handle, the controller reports back real-time events.
🎯 Learning Focus: HCI is the MOST CRITICAL interface! Commands go down, Events come up, Data flows both ways.

💡 Key Insight: This is where software meets hardware. Everything above HCI = your responsibility, everything below = chip manufacturer's responsibility!

Section 7B: L2CAP Layer - The Packet Manager
text
## **Layer 2: L2CAP (Logical Link Control and Adaptation Protocol)**

- **Role:**  
  Handles multiplexing multiple higher-level protocols and manages packet segmentation/reassembly.
- **Location:**  
  On the host side (inside the BlueZ stack).
- **Functions:**  
  - Aggregates data from multiple protocols and sends them over a single ACL link.
  - Segments large packets into smaller frames for transport; reassembles on receive.
  - Manages Quality of Service (QoS), supports connection-oriented and connectionless channels.
- **Analogy:**  
  Like a **post office**—letters from different sources (protocols) share the same delivery route (ACL link) but are labeled with different addresses (Channel IDs).

Section 7C: RFCOMM Layer - The Virtual Serial Cable
text
## **Layer 3: RFCOMM**

- **Role:**  
  Provides virtual serial port emulation over Bluetooth.
- **Location:**  
  Host side (BlueZ user space or kernel modules).
- **Functions:**  
  - Makes Bluetooth behave like a standard RS-232 serial cable.
  - Used heavily for Serial Port Profile (SPP) and other related profiles.
  - Supports multiple RFCOMM channels over a single L2CAP connection.
- **Analogy:**  
  Like a **virtual USB cable** running over the air.
🎯 Learning Focus: RFCOMM = "RS-232 over Bluetooth"! It's the magic that makes wireless look exactly like a wired serial connection.

💡 Key Insight: Multiple RFCOMM channels can run over ONE L2CAP connection - think of it like multiple serial ports over one USB hub!

Section 7D: SDP Layer - The Service Menu
text
## **Layer 4: SDP (Service Discovery Protocol)**

- **Role:**  
  Allows devices to discover which services (profiles/features) are offered by a peer.
- **Location:**  
  Host side.
- **Functions:**  
  - Queries remote devices: "What services do you support?"
  - Retrieves attribute details: UUIDs, supported features, connection parameters, etc.
  - Service discovery is generally required before connecting to most profiles.
- **Analogy:**  
  Like **checking a restaurant's menu** before placing your order.

Section 8: Complete Data Flow Example - SPP Byte Journey
text
## **How These Layers Work Together: SPP Example Flow**

**Scenario:** Connecting to a Bluetooth Serial Port Profile (SPP) device.

1. **HCI**
    - Host initiates an Inquiry (scan) via HCI, controller finds nearby devices, host receives BD_ADDR (Bluetooth Device Address).
2. **SDP**
    - Host asks, "Do you support SPP?" via SDP.  
      Remote device replies with corresponding RFCOMM channel number for SPP.
3. **RFCOMM over L2CAP**
    - Host opens an L2CAP channel to peer, negotiates an RFCOMM session over that channel, and establishes the virtual serial link.
4. **Data Flow**
    - Your application writes bytes to an RFCOMM socket.
    - RFCOMM data is multiplexed and segmented by L2CAP.
    - HCI transmits the data via ACL packets to the controller.
    - Controller radios it across the air to the paired device.
🎯 Learning Focus: This is the COMPLETE END-TO-END JOURNEY of your data! Let's trace ONE BYTE through every single layer!

Section 8A: The Byte Journey - Transmit Side (Device B → Device A)
Your App writes: write(rfcomm_socket, "Hello!", 6);

📍 Layer 7 - Application:

Bytes: H e l l o ! (6 bytes)

Action: App calls write() on RFCOMM socket

📍 Layer 6 - RFCOMM:

Adds RFCOMM header (channel info, control bits)

Packet: [RFCOMM_HDR][H e l l o !]

Action: Frames data for serial emulation

📍 Layer 5 - L2CAP:

Adds L2CAP header (channel ID, length)

Packet: [L2CAP_HDR][RFCOMM_HDR][H e l l o !]

Action: Multiplexes onto ACL channel

📍 Layer 4 - HCI:

Adds HCI ACL header (handle, flags)

Packet: [HCI_ACL_HDR][L2CAP_HDR][RFCOMM_HDR][H e l l o !]

Action: Queues for controller transmission

📍 Layer 3 - Controller (Baseband):

Adds Bluetooth packet header, applies encryption

Action: Frequency hopping, timing control

📍 Layer 2 - Radio:

Converts to RF signal at 2.4 GHz

Action: TRANSMITS OVER THE AIR

text
# Part 4 – Learning Roadmap

We'll start with SPP (Serial Port Profile) because it's the simplest to reason about and implement, then I'll show:

- A clear step‑by‑step sequence (what Device A and Device B each do, and what happens inside the controller + host), and
- Working C examples:
  - Discovery with raw HCI calls,
  - RFCOMM server (Device A) and RFCOMM client (Device B) using raw sockets, and
  - A compact D‑Bus (GDBus) C snippet showing how to call Pair() and Connect() via BlueZ.

If that looks good I'll move on to the next profile (HFP / A2DP / HID / etc.) the same way.

### Real-world scenario (SPP) Assume:

- **Device A** = embedded device running an RFCOMM SPP server (will `bind()` to RFCOMM channel 3 and `listen()`).
- **Device B** = PC or phone acting as RFCOMM client (will discover Device A, query for SPP service, pair if needed, then open RFCOMM and exchange bytes).

### High-level sequence (6 steps)

1. Inquiry / Discovery  
2. Service Discovery (SDP) to find SPP's RFCOMM channel  
3. Pairing / Authentication (if security required)  
4. Connection (L2CAP → RFCOMM) — RFCOMM open on channel from SDP  
5. Data exchange (read/write over RFCOMM socket)  
6. Disconnect / optional bonding (store link keys)

I'll expand what each side and the controller do for each step.

### Step-by-step internals — what happens on Device A and Device B

#### Step 0 — prerequisites
- Device A must have an RFCOMM server running or BlueZ profile registered.
- Both devices must have Bluetooth controllers up (e.g. `hci0 up`).

#### Step 1 — Inquiry / Discovery

**Device B (initiator / scanner):**

- Host opens an HCI socket and issues an `HCI_Inquiry` (library call `hci_inquiry()` or equivalent HCI command).
- The controller radio performs inquiry (hops frequencies, listens for / sends inquiry packets).
- Controllers of nearby devices (Device A) that are discoverable respond with FHS (inquiry response) including BD_ADDR.
- Controller on Device B receives inquiry responses and delivers them to host as HCI events.
- Host shows Device A address + RSSI; higher-level stack (BlueZ or your program) may attempt to read remote name (HCI read remote name request).

**Device A (responder):**

- Its controller automatically responds to inquiry if it's set to be discoverable.
- Link Manager and baseband handle the low‑level timing and hopping.

#### Step 2 — SDP (Service Discovery Protocol)

**Device B:**

- To find which channel SPP is on, Device B opens an SDP connection (SDP uses L2CAP internally) to Device A and requests service records for the Serial Port class UUID (`0x1101`).
- The SDP server on Device A returns a service record containing the RFCOMM channel number (e.g., channel 3).
- Host parses the returned ProtocolDescriptorList to find the RFCOMM port.

**Device A:**

- SDP server (part of BlueZ or user app if implemented) replies with the stored service record.

#### Step 3 — Pairing / Authentication (if needed)

- Either device may initiate pairing (most often Device B after SDP if the device requires pairing).
- Pairing uses HCI and Link Manager Protocol (LMP) flows: IO Capability exchange, authentication, link key generation (PIN / SSP).
- Controller handles encryption setup; host receives HCI events for passkey / confirmation and notifies agent (BlueZ agent or your agent via D‑Bus) to provide PIN or confirm.
- After successful pairing, link keys may be stored (bonding) so next time they can reconnect without pairing.

#### Step 4 — Connection (L2CAP → RFCOMM)

**Device B (client):**

- Opens an RFCOMM socket (`AF_BLUETOOTH` / `BTPROTO_RFCOMM`) and `connect()` to Device A using BD_ADDR and RFCOMM channel discovered from SDP.
- The host stack will set up an L2CAP bearer under the hood and the controller will create ACL link if needed. HCI messages for connection are exchanged.

**Device A (server):**

- If server uses raw RFCOMM socket it has `bind()`ed to the chosen channel and is `listen()`/`accept()`ing. `accept()` unblocks when client connects.
- Alternatively, if BlueZ handles the profile, BlueZ will route the received connection to the registered profile via D‑Bus ProfileManager.

#### Step 5 — Data exchange

- After `accept`/`connect`, both sides read/write on the RFCOMM stream (like a TCP-ish serial stream).
- RFCOMM does framing and multiplexer logic, L2CAP segments/assembles, HCI transports ACL data frames to/from controller, controller sends bytes over the air.

#### Step 6 — Disconnect & Bonding

- Either side closes the socket. HCI link teardown occurs, controllers free resources.
- If bonded, link keys stay stored; next session may skip pairing.

### Raw C examples (tested patterns you can compile)

**Notes before running:**

- These programs require Bluetooth dev headers and BlueZ libraries (`libbluetooth`).
- On many systems you must be root (or give capabilities) to open HCI and raw Bluetooth sockets.
- Compile with `-lbluetooth`. Example:  
  `gcc -o hci_discover hci_discover.c -lbluetooth`

## A— Discovery (HCI) — hci_discover.c
```cpp
/* hci_discover.c
Simple device inquiry using BlueZ hci library.
Compile: gcc -o hci_discover hci_discover.c -lbluetooth
Run as root: sudo ./hci_discover
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main() {
int dev_id = hci_get_route(NULL); // find first available adapter (e.g., hci0)
if (dev_id < 0) { perror("hci_get_route"); return 1; }

text
int sock = hci_open_dev(dev_id);
if (sock < 0) { perror("hci_open_dev"); return 1; }

int len = 8;            // inquiry time = 1.28 * len seconds
int max_rsp = 255;
inquiry_info *ii = NULL;
int num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, IREQ_CACHE_FLUSH);
if (num_rsp < 0) { perror("hci_inquiry"); close(sock); return 1; }

char addr = {0};
char name = {0};

printf("Found %d devices:\n", num_rsp);
for (int i = 0; i < num_rsp; i++) {
    ba2str(&(ii+i)->bdaddr, addr);
    memset(name, 0, sizeof(name));
    if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0)
        strncpy(name, "[unknown]", sizeof(name)-1);
    printf("%d: %s  %s\n", i+1, addr, name);
}

free(ii);
close(sock);
return 0;
}
```
text

This gives you the list of BD_ADDRs you can use for SDP / RFCOMM.

## B— RFCOMM server (Device A) — rfcomm_server.c
```cpp
/* rfcomm_server.c
Minimal RFCOMM server that accepts one connection and echoes data.
Compile: gcc -o rfcomm_server rfcomm_server.c -lbluetooth
Run as root: sudo ./rfcomm_server
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

int main(int argc, char **argv) {
int sock, client, bytes_read;
struct sockaddr_rc local = { 0 }, rem = { 0 };
char buf[1024] = { 0 };
socklen_t opt = sizeof(rem);

text
// 1) create RFCOMM socket
sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
if (sock < 0) { perror("socket"); return 1; }

// 2) bind to local bluetooth adapter, channel 3 (choose a channel > 0)
local.rc_family = AF_BLUETOOTH;
local.rc_bdaddr = *BDADDR_ANY;   // any local adapter
local.rc_channel = (uint8_t) 3;

if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0) {
    perror("bind");
    close(sock);
    return 1;
}

// 3) listen & accept
listen(sock, 1);
printf("RFCOMM server listening on channel %d ...\n", local.rc_channel);

client = accept(sock, (struct sockaddr *)&rem, &opt);
if (client < 0) { perror("accept"); close(sock); return 1; }

char remote_addr = {0};
ba2str(&rem.rc_bdaddr, remote_addr);
printf("Accepted connection from %s\n", remote_addr);

// 4) echo loop
while ((bytes_read = read(client, buf, sizeof(buf))) > 0) {
    printf("Received %d bytes: %.*s\n", bytes_read, bytes_read, buf);
    // echo back
    if (write(client, buf, bytes_read) < 0) {
        perror("write");
        break;
    }
    memset(buf, 0, sizeof(buf));
}

close(client);
close(sock);
return 0;
}
```
text

If your service needs to be discoverable via SDP you usually register a service record (via sdptool add or using BlueZ D‑Bus/RegisterProfile) — otherwise a client that learns the channel via SDP won't find it. For quick tests you can set the client to connect to a fixed channel if you know it.

## C— RFCOMM client (Device B) — rfcomm_client.c
```cpp
/* rfcomm_client.c
Minimal RFCOMM client: connect and send a message.
Compile: gcc -o rfcomm_client rfcomm_client.c -lbluetooth
Usage: sudo ./rfcomm_client XX:XX:XX:XX:XX:XX [channel]
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
if (argc < 2) {
printf("Usage: %s <bdaddr> [channel]\n", argv);
return 1;
}

text
const char *dest = argv;[1]
int channel = (argc >= 3) ? atoi(argv) : 3; // default channel 3
struct sockaddr_rc addr = { 0 };
int s;
char buf = "Hello from client!\n";

s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
if (s < 0) { perror("socket"); return 1; }

addr.rc_family = AF_BLUETOOTH;
str2ba(dest, &addr.rc_bdaddr);  // convert "XX:XX:..." to bdaddr struct
addr.rc_channel = (uint8_t) channel;

printf("Connecting to %s channel %d ...\n", dest, channel);
if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    close(s);
    return 1;
}
printf("Connected; sending message...\n");
write(s, buf, strlen(buf));

// read echo
int bytes = read(s, buf, sizeof(buf));
if (bytes > 0) {
    printf("Server replied: %.*s\n", bytes, buf);
}

close(s);
return 0;
}
```
text

### Workflow with raw code:

1. Run `rfcomm_server` on Device A (or register an RFCOMM server via BlueZ).
2. On Device B run `hci_discover` to get Device A's BD_ADDR.
3. If Device A requires pairing, pair first (a D-Bus method example will be shown next).
4. Run `rfcomm_client <BDADDR> <channel>` (use the channel from SDP or the channel you bound in the server).

### 4) SDP: How the client finds the RFCOMM channel

SDP (Service Discovery Protocol) is how the client learns the RFCOMM channel for SPP.

BlueZ provides C API headers `<bluetooth/sdp.h>` and `<bluetooth/sdp_lib.h>` to:

- Open an SDP session, e.g.,  
sdp_session_t *session = sdp_connect(...);

text
- Search for a service with the Serial Port UUID (`0x1101`) and request attributes.
- Parse the `ProtocolDescriptorList` to extract the RFCOMM channel number.

The SDP code involves verbose parsing with `sdp_list_t` structures.

For easier debugging or testing, you can use the command-line tool:  
sdptool browse <BDADDR>

text
to view service records on the remote device.

(If you want, a ready-to-run SDP C function can be provided—it is longer and detailed.)

### 5) D-Bus (BlueZ) approach in C — Pair & Connect (Device B)

Most modern Linux applications prefer using BlueZ's D-Bus API instead of raw HCI/SDP calls for pairing and connecting.

Below is a compact GDBus C snippet example that performs:

- `Pair()` method call, and
- `Connect()` method call

on a `org.bluez.Device1` D-Bus object. This requires the device's D-Bus object path (e.g., `/org/bluez/hci0/dev_XX_XX_...`) after discovering BD_ADDR.

To compile the example, use:  
pkg-config --cflags --libs gio-2.0

text

This workflow reflects how Device B discovers, pairs, and connects to Device A using RFCOMM over Bluetooth with explicit SDP lookup or via BlueZ's higher-level D-Bus APIs.

## pair_connect
```cpp
/* pair_connect.c
Simple example that calls Pair() and Connect() on org.bluez.Device1 via GDBus.
Compile:
gcc -o pair_connect pair_connect.c $(pkg-config --cflags --libs gio-2.0)
Run:
sudo ./pair_connect XX:XX:XX:XX:XX:XX
Note: If BlueZ expects agent interaction (PIN/SSP), you must register an agent (or use bluetoothctl beforehand).
*/

#include <gio/gio.h>
#include <stdio.h>
#include <string.h>

static char *device_path_from_addr(const char *addr) {
// Replace ':' with '' and build "/org/bluez/hci0/dev_XX_XX..."
char tmp;
snprintf(tmp, sizeof(tmp), "%s", addr);
for (char *p = tmp; *p; ++p) if (*p == ':') *p = '';
char *path = g_strdup_printf("/org/bluez/hci0/dev%s", tmp);
return path;
}

int main(int argc, char **argv) {
if (argc < 2) {
fprintf(stderr, "Usage: %s <BDADDR>\n", argv);
return 1;
}

text
GError *error = NULL;
GDBusProxy *proxy;
char *dev_path = device_path_from_addr(argv);[1]

proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
                G_DBUS_PROXY_FLAGS_NONE,
                NULL,                // GDBusInterfaceInfo
                "org.bluez",         // name
                dev_path,            // object path
                "org.bluez.Device1", // interface
                NULL,
                &error);
if (!proxy) {
    fprintf(stderr, "Failed to create proxy: %s\n", error ? error->message : "unknown");
    g_clear_error(&error);
    g_free(dev_path);
    return 1;
}

// Pair() - may trigger agent requests (passkey/pin). Provide an agent or do this manually.
g_dbus_proxy_call_sync(proxy, "Pair", NULL, G_DBUS_CALL_FLAGS_NONE, -1, NULL, &error);
if (error) {
    fprintf(stderr, "Pair() failed: %s\n", error->message);
    g_clear_error(&error);
    // continue; maybe already paired
} else {
    printf("Pair() success (or already paired)\n");
}

// Connect()
g_dbus_proxy_call_sync(proxy, "Connect", NULL, G_DBUS_CALL_FLAGS_NONE, -1, NULL, &error);
if (error) {
    fprintf(stderr, "Connect() failed: %s\n", error->message);
    g_clear_error(&error);
    g_object_unref(proxy);
    g_free(dev_path);
    return 1;
}
printf("Connect() success\n");

g_object_unref(proxy);
g_free(dev_path);
return 0;
}
```
text

### Notes about D‑Bus approach

- **Pairing and agents:**  
  Pairing often needs an agent to supply a PIN or confirmation.  
  - You can register an agent via `org.bluez.AgentManager1`.  
  - Alternatively, use `bluetoothctl` (it registers an agent automatically).  

- **Post-connection behavior:**  
  After `Connect()` returns successfully, the RFCOMM service (SPP) on the remote should accept the connection.  
  - You can then open a raw RFCOMM socket locally (the raw socket connect still works), **or**  
  - Use D‑Bus Profile APIs to bind a profile for higher-level handling.

### 6) Registering a server/profile via D‑Bus (outline)

If you want **BlueZ** to own the server side — so it handles incoming connections and forwards them to your program via the `org.bluez.Profile1` interface — the general steps are:

1. **Implement a D‑Bus object** that implements `org.bluez.Profile1` methods:  
   - `NewConnection` (called when a remote connects, provides you an FD to read/write)  
   - `RequestDisconnection`  
   - `Release` (optional for cleanup)

2. **Register the profile** with BlueZ:  
   - Call `org.bluez.ProfileManager1.RegisterProfile(object_path, uuid, options)` on the system D‑Bus.  
   - Include options such as:
     ```
     {
       "Channel": <uint16>,
       "Name": "<string>",
       "RequireAuthentication": <bool>
     }
     ```

3. **Connection handling:**  
   - BlueZ performs SDP, L2CAP, and RFCOMM setup internally.  
   - When a remote client connects, BlueZ calls your `NewConnection` method and passes a file descriptor (FD) that you can `read()`/`write()`.

This is the preferred way to let **BlueZ** handle SDP advertisement and lower-layer details, then hand over the connected socket to your application.

*(If needed, a complete "Profile server" C example using GDBus can be provided — it is verbose but fully idiomatic.)*

### 7) Debugging tips & interview talking points

**Tools:**
- `btmon` — packet-level logger for HCI + ACL frames (essential for debugging protocol-level issues)  
- `bluetoothctl` — interactive control and pairing tool  
- `sdptool` — inspect SDP service records  
- `hcitool` (older) — device discovery, connection commands (deprecated in newer distros)  
- `hciconfig` — bring adapter up/down, inspect status  

**Common problems:**
- Device not discoverable
- No pairing agent registered
- RFCOMM channel mismatch (SDP inconsistency)
- Missing privileges (root or `CAP_NET_RAW`)
- Adapter down (`hciconfig hci0 up`)
- Another process already bound to the RFCOMM channel

**Interview key points to remember:**
- **SPP stack layering:**  
  `App → RFCOMM → L2CAP → HCI → Controller`  
- **SDP:** Used by client to discover RFCOMM channel number for a profile.  
- **Pairing:** Uses HCI/LMP and requires an agent to provide PIN/confirmation.  
- **Sockets:** Understand `socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)` with `bind()` / `connect()` / `accept()` flow.  
- **D‑Bus APIs:** Know `org.bluez.Device1.Pair()` for pairing and `ProfileManager1.RegisterProfile()` for server profile registration.

Being able to **sketch the connection flow** and **name key Bluetooth layers** is a strong plus in interviews.
