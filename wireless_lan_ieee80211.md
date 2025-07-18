Here's your content, beautifully organized in **Markdown format**. You can directly copy this into your `.md` file.

---

```markdown
# 📶 Wireless LAN (WLAN) & IEEE 802.11 Overview

Wireless LAN is a network where devices use wireless protocols/technology to communicate within a defined area.

---

## 📚 IEEE 802.11 Standard Overview

IEEE 802.11 provides the standard for wireless LAN, covering two key layers:

1. **Physical Layer**
2. **Data Link Layer**

---

## 🔗 IEEE 802.11 Services

### 1. **Basic Service Set (BSS)**
- A group/unit of wireless network devices communicating with the **same Access Point (AP)**.
- **BSSID**: MAC address of the AP (48-bit hexadecimal).

### 2. **Extended Service Set (ESS)**
- A collection of multiple APs and their associated clients, united by a **Distribution System (DSM)**.
- Logical network name: **ESSID** (same as SSID in practice).

---

## 🔧 Access Point (AP)

- A **Layer 2 device** that retransmits wireless signals to the rest of the network.
- Also referred to as the **Base Station**.

---

## 📛 SSID & ESSID

- **SSID**: Unique character string identifying an AP.
- When multiple APs provide the same network service, it's referred to as **ESSID**.

---

## 🤝 Ad-hoc Mode (IBSS)

- Decentralized (peer-to-peer) network **without an AP**.
- Devices communicate directly with each other.

---

## 🔍 Promiscuous Mode

- Also called **Monitor Mode**.
- Used for **listening to Wi-Fi packets over-the-air**.

---

## 📐 Data Link Layer Structure

Divided into:
- **Logical Link Control (LLC)**
- **Medium Access Control (MAC)**

### MAC Sublayers:

1. **DCF (Distributed Coordination Function)**
   - Provides **contention-based** access using **CSMA/CA**.
   - Wireless: `CSMA/CA`
   - Wired: `CSMA/CD` (not suitable for wireless as Wi-Fi is half-duplex)

2. **PCF (Point Coordination Function)**
   - **Poll-based / Priority-based** access.

---

## ⚙️ CSMA/CA Details

- Used for avoiding collisions in wireless networks.
- Timers are maintained to check for channel availability.

---

## 🔎 Scanning Process

When a station enters a network, it performs **scanning** to associate with an AP.

### Steps:

1. Send a **Probe Request** frame.
2. APs within range reply with **Probe Response**.
3. Station sends **Association Request** to chosen AP.
4. AP responds with **Association Response**.

### Types:

- **Active Scanning**: Station sends probe; AP responds.
- **Passive Scanning**: AP periodically sends **Beacon Frames**.

---

## ⚠️ CSMA/CA Problems

1. **Hidden Terminal Problem**
   - Solved using **RTS/CTS**.
   - Makes stations aware of others via AP.

2. **Exposed Station Problem**
   - Station refrains from transmitting due to false channel occupancy perception.
   - Also addressed via **RTS/CTS**, assuming station synchronization.

---

## 📦 Fragmentation

- Encouraged in noisy environments.
- Prevents retransmission of large packets in case of corruption.

---

## 🧾 Wi-Fi Frame Format

```

FC | D | Addr1 | Addr2 | Addr3 | SC | Addr4 | Body | FCS

```

### Frame Control (FC) Fields:

1. Protocol Version
2. Frame Type
3. Subtype
4. To DS
5. From DS

### Frame Types:

- **Management Frames**
  - Probe
  - Association
  - Authentication
  - Beacon
- **Control Frames**
  - RTS
  - CTS
  - ACK
- **Data Frames**

### Address Fields:

- **Addr1**: Next destination
- **Addr2**: Previous sender
- **Addr3**: Final destination
- **Addr4**: Original source (used only in WDS)

### Other Fields:

- **Duration**: Time to occupy channel
- **SC (Sequence Control)**: Used for synchronization
- **FCS (Frame Check Sequence)**: Error detection (likely CRC32)

---

## 🧬 Physical Layer Variants

Based on modulation/encoding techniques, IEEE 802.11 versions include:

| Standard   | Frequency | Modulation | Speed       |
|------------|-----------|------------|-------------|
| 802.11a    | 5.75 GHz  | OFDM, PSK  | 6–54 Mbps   |
| 802.11b    | 2.44 GHz  | DSSS, PSK  | 5.5–11 Mbps |
| 802.11g    | 2.4 GHz   | OFDM       | 54 Mbps     |

> Wi-Fi operates in **unlicensed ISM bands**.

---

## 📡 Beacon Frame Contents

1. SSID
2. Channel Information
3. Supported & Required Data Rates
4. Security Capabilities
5. QoS Parameters

---

## 🔐 WPA2 - No Encryption Connection Flow

1. AP sends **Beacon Broadcast** frame.
2. Client sends **Probe Request** with SSID.
3. AP responds with **Probe Response** (no encryption).
4. Client sends **Authentication Request**.
5. AP sends **Authentication Response**.
6. Client sends **Association Request**.
7. AP responds with **Association Response**.
8. Client sends **Disassociation Request** when disconnecting.

---

## 🔋 Power Saving Mode (PSM)

- Client sends **null data frame** with **PS-Poll** bit set.
- AP buffers data and notifies via **TIM** in Beacon.
- Client wakes up and sends **PS-Poll** to retrieve buffered data.

---

## 🔐 Four-Way Handshake (WPA2)

1. **AP** sends **ANonce** to station.
2. **Station**:
   - Generates **PMK** using password+SSID.
   - Combines PMK + ANonce + SNounce to create **PTK**.
   - Sends **SNounce** to AP.
3. **AP**:
   - Generates **PTK**
   - Generates **GTK** and sends it securely to the station.
4. **Station** sends ACK.

---

## 🔑 WPA2 Encrypted Association Flow

1. Station sends **Probe Request** (data rates + capabilities).
2. AP responds with **Probe Response** (SSID + encryption types).
3. Station selects AP and sends **Authentication Request**.
4. AP responds with **Authentication Response**.
5. Station is now authenticated (but not associated).
6. Station sends **Association Request** (includes encryption type).
7. AP validates and sends **Association Response** (status + ID).
8. If using WPA2, performs **Four-Way Handshake** for encryption.
```

Let me know if you want this exported as a `.md` file or want diagrams included!
