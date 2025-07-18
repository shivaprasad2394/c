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

