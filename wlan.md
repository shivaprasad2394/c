# Wi-Fi Direct: Deep Dive & Internal Architecture

## Introduction

**Wi-Fi Direct** is a peer-to-peer (P2P) wireless communication technology that allows devices to connect directly to each other without requiring a traditional Wi-Fi access point (AP). 

Built on the IEEE 802.11 family of standards, Wi-Fi Direct reuses several underlying MAC/PHY mechanisms such as **probe requests/responses**, **beacons**, and **association procedures**. However, it introduces **dynamic role negotiation**, **enhanced power-saving mechanisms**, and **secure direct communication**, enabling flexible and efficient wireless connectivity.

---

## Internal Components of Wi-Fi Direct

At its core, Wi-Fi Direct operates with two primary roles:

### 1. P2P Group Owner (GO)
- Functions similarly to a traditional AP.
- Manages **beaconing**, **client associations**, **network parameter coordination**, **encryption**, and **security protocols**.
  
### 2. P2P Client
- Connects to the P2P Group managed by the GO.
- Participates in **power-saving protocols**, **security handshakes**, and **data exchanges** under GO instructions.

---

## Internal Working of Wi-Fi Direct

### 1. MAC/PHY Layer Interactions
Wi-Fi Direct reuses standard IEEE 802.11 frame formats (e.g., **probe request**, **probe response**, **authentication**, **association**).

- **Discovery Phase:** Devices alternate between `search` and `listen` states.
- These states occur over pre-defined **social channels**: **Channel 1**, **Channel 6**, and **Channel 11** in the 2.4 GHz band.

### 2. Dynamic Role Negotiation
- Devices calculate a **GO Intent value** during discovery to indicate their willingness to act as Group Owner.
- The device with the **higher intent value becomes the GO**.
- A **tie-breaker bit** is used if intent values are equal.
- This logic is managed internally by a **state machine** within the Wi-Fi Direct protocol stack.

### 3. Concurrent Mode Support
- Some devices can operate as:
  - A P2P GO and,
  - A traditional client simultaneously.
- Requires **internal scheduling**, **resource allocation**, and **interface sharing** logic.

---

## Group Formation Scenarios

Wi-Fi Direct supports three group formation mechanisms. Each mechanism follows a slightly different procedure.

---

## 1. Standard Group Formation

Standard group formation is the most common Wi-Fi Direct group setup method, where two devices dynamically negotiate their roles (GO vs. Client) and establish a secure, temporary group.

---

### Step-by-step Process

1. **Device Discovery Phase**
   - Devices enter **discovery mode** and alternate between:
     - **Search state** – Actively sending **Probe Requests**
     - **Listen state** – Waiting to receive **Probe Requests**
   - Discovery occurs only on the **social channels**:
     - Channel **1**, **6**, and **11** (2.4 GHz band)
   - **Probe Requests** include:
     - **P2P IE** (with device capabilities, config timeout, group capabilities)
     - **WSC IE** (Wi-Fi Simple Config – with device info like name, category, method support)
   - **Probe Responses** echo back the supported parameters.

2. **GO Negotiation Phase**
   - Devices initiate **P2P Group Owner Negotiation**
   - Exchange three messages:
     - **GO Negotiation Request**
     - **GO Negotiation Response**
     - **GO Negotiation Confirmation**
   - Each device includes a **GO Intent Value** (0–15) in negotiation messages
   - A **Tie Breaker Bit** is used in case of equal intent values
   - The device with the **higher GO Intent** becomes the **Group Owner (GO)**

3. **Beaconing**
   - The elected GO starts **broadcasting Beacon Frames**
   - Beacons include:
     - **SSID** (e.g., "DIRECT-xy-DeviceName")
     - **P2P IE** with group info
     - **WSC IE** with security configuration info

4. **Client Association**
   - P2P Client scans for beacons
   - Sends **Association Request** to GO
   - GO replies with **Association Response**
   - Association frames also include **P2P IEs** for capability synchronization

5. **Security Handshake**
   - Wi-Fi Direct mandates **Wi-Fi Protected Setup (WPS)** for secure group formation
   - WPS methods:
     - **Push Button Configuration (PBC)**
     - **PIN entry**
   - During WPS:
     - Devices exchange **public keys**, **nonces**, and **authentication hashes**
     - Derive a **Pre-Shared Key (PSK)** for **WPA2-PSK** or **WPA3-SAE**
   - PMF (Protected Management Frames) can also be enabled for added protection

6. **Group Formation Complete**
   - Encrypted channel is established
   - Devices can begin **IP address assignment** via DHCP
   - Data transfer may now begin

---

### Key Information Elements Used

| Frame Type        | Included IEs                        |
|-------------------|-------------------------------------|
| Probe Request      | P2P IE, WSC IE                     |
| Probe Response     | P2P IE, WSC IE                     |
| GO Negotiation     | P2P GO Negotiation IE              |
| Beacon             | SSID, P2P IE, WSC IE               |
| Assoc Request/Resp | P2P Capability, Group Capability   |

---

### Use Case

Used in general-purpose, **on-demand P2P communication**:
- Smartphone-to-smartphone file sharing
- Wireless printing
- Temporary display casting
- One-time game controller pairing

---

### Mermaid Diagram

```mermaid
sequenceDiagram
    participant Device A
    participant Device B

    Device A->>Device B: Probe Request (P2P IE + WSC IE)
    Device B->>Device A: Probe Response (P2P IE + WSC IE)

    Device A->>Device B: GO Negotiation Request (Intent=7)
    Device B->>Device A: GO Negotiation Response (Intent=5)
    Device A->>Device B: GO Confirmation (Device A becomes GO)

    Device A-->>Device B: Beaconing Starts (SSID + P2P + WSC)

    Device B->>Device A: Association Request (P2P IE)
    Device A->>Device B: Association Response (P2P IE)

    Note right of Device B: WPS Handshake (e.g., Push Button)
    Note right of Device B: Secure Group Formation (WPA2-PSK)
```
## 2. Autonomous Group Formation

In this mode, a device **self-initiates** and starts functioning as a Group Owner (GO) **without role negotiation**.

### Step-by-Step Process

1. Device declares itself as GO  
2. Starts broadcasting **Beacons**  
3. Other devices discover and join as clients

### Use Case

Used in **IoT devices**, **printers**, or **digital displays**, where one device is always the GO and expects clients to join without negotiation.

### Mermaid Diagram

```mermaid
sequenceDiagram
    participant Device GO
    participant Device Client

    Device GO->>All: Beacon (IE: P2P Group Info)
    Device Client->>Device GO: Probe Request
    Device GO-->>Device Client: Probe Response

    Device Client->>Device GO: Provision Discovery Request
    Device GO-->>Device Client: WPS Push Button Method

    Device Client->>Device GO: Association Request
    Device GO-->>Device Client: Association Response
```
## 3. Persistent Group Formation

**Persistent groups** are pre-negotiated and saved on devices for **seamless future reconnection**.

### Step-by-Step Process

1. First connection is a standard group formation with the **"Persistent" bit set**  
2. Devices **store credentials** and assigned **GO/Client roles**  
3. On future encounters, devices **skip role negotiation and security exchange**, reconnecting automatically

---

### Use Case

Persistent groups are ideal for recurring connections, such as:

- Wireless speakers  
- Smart TVs  
- Previously paired mobile phones

---

### Mermaid Diagram

```mermaid
sequenceDiagram
    participant Device A
    participant Device B

    Note over Device A,Device B: Initial Standard Formation
    Device A->>Device B: GO Negotiation + Security Exchange
    Device A-->>Device B: Mark Group as Persistent

    Note over Device A,Device B: Future Encounter
    Device A->>Device B: Probe Request (Persistent Group Info)
    Device B-->>Device A: Join without full negotiation
    Note over Device A,Device B: Fast Group Reconnection
```
## Additional Functional Aspects

---

### Data Transfer

- Communication is based on standard **IEEE 802.11 data frames**
- Wi-Fi Direct supports all **IP-based protocols**, including:
  - **UDP**
  - **TCP/IP**
  - **HTTP**, **FTP**, **RTSP**, and others
- Throughput and performance vary depending on:
  - **Channel quality**
  - **Signal interference**
  - **Device role** (Group Owner (GO) has higher processing and scheduling overhead)
- Performance is often comparable to infrastructure mode Wi-Fi in short-range scenarios

---

### QoS (Quality of Service)

- Uses **Wi-Fi Multimedia (WMM)** to provide traffic prioritization
- Traffic is classified into **four Access Categories (ACs)**:
  - **Voice** – Highest priority (low latency)
  - **Video** – Medium-high priority
  - **Best Effort** – Default priority
  - **Background** – Lowest priority (e.g., file downloads)
- Enables smooth streaming and VoIP over Wi-Fi Direct links

---
### Power Saving Mechanisms
Wi-Fi Direct introduces specialized mechanisms to minimize energy consumption during peer-to-peer communication.
- Clients follow the **Notice of Absence (NoA)** schedule defined by the GO
- Implements **P2P Power Save Protocol (PPSP)** to reduce power consumption
- Key techniques include:
  - **GO buffering data** for clients while asleep
  - **Traffic Indication Maps (TIMs)** to notify clients when data is buffered
- Critical for mobile and battery-powered devices
---

#### Notice of Absence (NoA)

- The **Group Owner (GO)** periodically broadcasts a **Notice of Absence (NoA)** schedule to inform clients when it will be unavailable for communication.
- Clients synchronize their power-saving cycles with this schedule to avoid unnecessary wake-ups.
- NoA Parameters include:
  - **Count** – Number of absence intervals (0 = indefinite)
  - **Duration** – Duration of each absence period
  - **Interval** – Time between the start of two consecutive absence periods
  - **Start Time (TSF)** – Timestamp for when absence starts
- Helps reduce contention and idle listening, especially when GO is also serving as a legacy client (concurrent mode).

---

#### P2P Power Save Protocol (PPSP)

- Wi-Fi Direct implements **P2P Power Save Protocol (PPSP)** to manage power-saving behaviors beyond standard 802.11 mechanisms.
- PPSP supports:
  - **Client-initiated sleep** with GO-aware coordination
  - **Buffered traffic handling** by the GO
  - **Client wake-up signaling** using **Traffic Indication Maps (TIMs)**
- GO maintains a **traffic buffer** and notifies sleeping clients only when data is pending.
- Reduces unnecessary data polling and active channel usage.

---

#### Key Benefits

- Enhances battery life of connected clients
- Minimizes airtime usage during idle periods
- Enables better coexistence with infrastructure networks or other P2P groups (especially in concurrent operation scenarios)

---

### Security Mechanisms

- Supports industry-standard **Wi-Fi Protected Access**:
  - **WPA2-PSK (Pre-Shared Key)**
  - **WPA3-SAE (Simultaneous Authentication of Equals)** for stronger protection
- Uses **Wi-Fi Protected Setup (WPS)** for group formation:
  - **PIN Method** – Displays a code for manual entry
  - **Push Button Configuration (PBC)** – User-friendly pairing
  - **NFC (Near-Field Communication)** – Tap-to-pair support
- All management frames are optionally protected using **Protected Management Frames (PMF)** to prevent spoofing and eavesdropping

---

### Connection Management

- The **Group Owner (GO)** maintains a dynamic list of connected clients
- Provides mechanisms for:
  - **Client eviction** – Manual or automated disconnection
  - **Disassociation** – Graceful connection teardown
  - **Group termination** – Ends group and clears all clients
- Clients can:
  - **Re-negotiate roles** dynamically during reconnection
  - **Initiate or join** new groups as needed
- Wi-Fi Direct also supports **concurrent operation** with infrastructure networks (via virtual interfaces), enabling devices to act as both:
  - **GO or Client**
  - **Standard Wi-Fi STA** (Station) simultaneously

---
