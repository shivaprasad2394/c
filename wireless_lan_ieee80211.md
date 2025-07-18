# 🌐 Wireless LAN and IEEE 802.11 Overview

## 🔧 What is Wireless LAN?

A **Wireless LAN** is a network where devices communicate using wireless protocols/technologies within a defined area.

---

## 📜 IEEE 802.11 Standard

IEEE 802.11 provides a standard for wireless LAN, covering two layers:

- **Physical Layer**
- **Data Link Layer**

---

## 📶 Wireless Services in IEEE 802.11

### 1. **BSS (Basic Service Set)**

- A unit of wireless network devices communicating with the same **Access Point (AP)**.

### 2. **ESS (Extended Service Set)**

- A collection of multiple APs and their associated client stations, all united by a single **Distribution System Medium (DSM)**.
- The **ESSID** (Extended SSID) is the shared network name.
- The terms **SSID** and **ESSID** are often used interchangeably.

---

## 📡 Key Terms

- **BSSID**: The physical MAC address of the AP (48-bit hex).
- **AP (Access Point)**:
  - Acts as a bridge between wireless devices and the wired network.
  - Operates at Layer 2 (Data Link Layer).
- **SSID**: A unique string identifying a wireless network.
- **Ad-Hoc Mode**:
  - Peer-to-peer communication without AP.
  - Decentralized, direct communication between stations.
- **Promiscuous Mode (Monitor Mode)**:
  - Allows a device to listen to all Wi-Fi packets over-the-air.

---

## 🧩 Data Link Layer Details

### Two Sublayers:
1. **Logical Link Control (LLC)**
2. **Medium Access Control (MAC)**

---

## 🕹️ MAC Layer Functions

### 1. **DCF (Distributed Coordination Function)**

- Uses **CSMA/CA** (Carrier Sense Multiple Access with Collision Avoidance).
- Operates on **half-duplex**.
- **Timers** are used to avoid collisions.

> 📌 *CSMA/CA is for wireless, CSMA/CD is for wired.*

### 2. **PCF (Point Coordination Function)**

- Poll-based / priority-based access mechanism.

---

## 🔍 Scanning and Association

### What is Scanning?

The process by which a station associates with an AP.

### Scanning Steps:

1. Station sends a **probe request frame**.
2. Nearby APs respond with **probe response frames**.
3. Station sends an **association request** to the chosen AP.
4. AP sends back an **association response**.

### Scanning Types:

- **Active Scanning**: Station sends probe request → AP responds.
- **Passive Scanning**: APs periodically send **beacon frames**.

---

## ⚠️ CSMA/CA Problems

### 1. **Hidden Terminal Problem**

- Solved using **RTS/CTS** (Request to Send / Clear to Send).

### 2. **Exposed Station Problem**

- Also mitigated using RTS/CTS (requires synchronized stations).

---

## 🧱 Fragmentation

- Encouraged to reduce retransmission overhead due to noisy channels.

---

## 🧾 IEEE 802.11 Frame Format


### Frame Control (FC) Fields:

- **Protocol Version**
- **Frame Type**
- **Subtype**
- **To DS**
- **From DS**

### Frame Types:

1. **Management Frames**
   - Probe, Association, Authentication, Beacon
2. **Control Frames**
   - RTS, CTS, Acknowledgment
3. **Data Frames**

### Other Fields:

- **Duration**: Time to occupy channel
- **Sequence Control (SC)**: Synchronization
- **FCS**: Frame Check Sequence (CRC32)

---

## 🧭 Addressing in Wi-Fi

| Address | Purpose                        |
|---------|--------------------------------|
| Addr1   | Next Destination               |
| Addr2   | Previous Sender                |
| Addr3   | Final Destination              |
| Addr4   | Original Source (if needed)    |

> 🔹 If `To DS = 0` and `From DS = 0` → Direct station-to-station communication.

---

## ⚙️ Physical Layer and Modulation Schemes

### Based on encoding, speed, and range:

- **802.11a**: 5.75 GHz, OFDM, PSK, 6–54 Mbps
- **802.11b**: 2.44 GHz, DSSS, PSK, 5.5–11 Mbps
- **802.11g**: 2.4 GHz, OFDM, 54 Mbps

> 💡 Wi-Fi uses unlicensed **ISM bands**.

---

## 📢 Beacon Frame Includes:

- SSID
- Channel Information
- Supported & Required Data Rates
- Security Capabilities
- QoS Parameters

---

## 🔐 Open (No Encryption) Connection Process

1. AP sends **beacon frame** (broadcast).
2. Client sends **probe request** with SSID.
3. AP replies with **probe response**.
4. Client sends **authentication request**.
5. AP sends **authentication response**.
6. Client sends **association request**.
7. AP sends **association response**.
8. Client may later send **disconnect frame**.

---

## 🔋 Power Saving Mode

- Client sends **null data** frame with **PS-Poll bit** set.
- AP buffers data for the client.
- AP uses **TIM** flag in beacons to notify the client.
- Client sends **PS-Poll** to retrieve buffered data.

---

## 🔐 Four-Way Handshake (WPA2)

Used for secure key exchange between client and AP.

### Steps:

1. **AP** generates **ANonce** and sends to **station**.
2. **Station** computes **PMK** from SSID + password, generates **SNonce**, and derives **PTK**.
3. **Station** sends **SNonce** to AP.
4. **AP** derives **PTK**, generates **GTK**, and sends GTK to station.
5. **Station** sends **ACK** to confirm.

---

## 🔐 WPA2 Encrypted Connection Process

1. Station sends **probe request** (with supported data rates and capabilities).
2. AP checks compatibility and sends **probe response**.
3. Station sends **authentication request**.
4. AP sends **authentication response**.
5. Station is now *authenticated* but not yet *associated*.
6. Station sends **association request** (includes selected encryption type).
7. AP responds with **association response** (includes status code and AID).
8. If encryption is WPA2/WPA/WEP → **Four-Way Handshake** is performed for secure communication.

---



