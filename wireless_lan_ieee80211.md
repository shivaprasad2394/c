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



# 📡 Wi-Fi Access Point (AP) Process

A **Wi-Fi Access Point (AP)** is a Layer 2 device that acts as a bridge between wireless client devices and the wired network (LAN).

It plays a central role in managing communication, association, and data forwarding in wireless networks.

---

## 🔁 Access Point Roles

- **Beacon Broadcasting**: Periodically advertises its presence and capabilities.
- **Authentication & Association Handling**: Manages connection requests from stations.
- **Frame Forwarding**: Routes data between wireless clients and the wired network.
- **Encryption Management**: Initiates and completes secure key handshakes (e.g., WPA2/WPA3).
- **QoS & Buffering**: Supports traffic prioritization and manages buffers (especially for sleeping clients).

---

## 🔄 Wi-Fi AP Process Workflow

### 1. **Beacon Frame Broadcast**

- AP periodically sends **beacon frames** on its operating channel.
- Beacon includes:
  - **SSID**
  - **Channel info**
  - **Supported data rates**
  - **Security capabilities**
  - **QoS and TIM (Traffic Indication Map)**

> 🔔 This is part of **passive scanning**—clients listen to beacons to discover networks.

---

### 2. **Handling Probe Requests (Active Scanning)**

- Client sends a **probe request** (with or without SSID).
- AP responds with a **probe response** containing:
  - Network info
  - Capabilities
  - Encryption methods

---

### 3. **Authentication Request**

- The client sends an **authentication request** to the AP.
- AP replies with an **authentication response** (accept or reject).

> 📌 This is **open system authentication** in most modern networks (pre-shared key authentication handled later via 4-way handshake).

---

### 4. **Association Request/Response**

- Once authenticated, client sends an **association request**:
  - SSID
  - Supported rates
  - Security capabilities
- AP sends an **association response**:
  - Status (success/failure)
  - Association ID (AID)

> ✅ After this, the client is fully associated and allowed to exchange data frames.

---

## 🔐 Optional: WPA2/WPA3 Four-Way Handshake

If encryption is enabled (WPA2/WPA3):

1. **AP sends ANonce** to client.
2. **Client generates PMK/PTK**, sends SNonce.
3. **AP generates PTK**, derives GTK, sends it to client.
4. **Client sends ACK** to complete the handshake.

> 🔑 This step ensures both sides share secure session keys.

---

## 🔁 Frame Forwarding & Data Handling

- Once associated:
  - AP receives **data frames** from clients.
  - Forwards them to:
    - Another wireless client (intra-BSS)
    - Or a wired LAN endpoint (via **DS** – Distribution System)

---

## 💤 Power Save Mode Handling

- AP buffers packets for clients in **sleep mode**.
- AP sets **TIM flag** in beacon to notify pending data.
- Client wakes up and sends **PS-Poll frame** to retrieve data.

---

## 📶 AP Channel Management

- Operates on a fixed or dynamic channel in 2.4GHz/5GHz/6GHz bands.
- May support:
  - **Channel bonding** (40/80/160 MHz)
  - **DFS** (Dynamic Frequency Selection)
  - **Band Steering** (2.4 → 5GHz steering)

---

## 🧠 Other AP Features

- **QoS Management**: Uses WMM (Wi-Fi Multimedia) to prioritize traffic.
- **Load Balancing**: Distributes clients among neighboring APs (in ESS).
- **Client Isolation**: Prevents client-to-client traffic on the same BSS.
- **Roaming Support**: Coordinates with other APs in ESS for seamless handover.

---

## 🧾 AP Responsibilities Summary

| Task                        | Description                                                                 |
|-----------------------------|-----------------------------------------------------------------------------|
| Beacon Broadcast            | Periodically sends management frames to advertise network presence         |
| Handle Probe Requests       | Replies to active scan requests from client devices                        |
| Manage Authentication       | Handles client authentication using open/shared key                        |
| Manage Association          | Accepts or denies client association requests                              |
| Encryption Setup            | Coordinates 4-way handshake for WPA2/WPA3                                  |
| Frame Forwarding            | Forwards frames to other wireless clients or wired LAN                     |
| Power Save Support          | Buffers data and uses TIM/PS-Poll mechanism for sleeping clients           |
| QoS / WMM Support           | Enables traffic prioritization (voice, video, best-effort, background)     |
| Roaming & Load Balancing    | Part of ESS to support seamless mobility and balanced network usage        |

---

# 🌐 How a Wireless Access Point (AP) Provides Internet/Data Access

When you connect your phone or laptop to Wi-Fi, you're actually communicating with a **Wireless Access Point (AP)**. But how does that AP give you access to the internet? Let's break it down step by step.

---

## 📡 Step 1: Device Connects to the AP

1. Your device (called a **station** or **STA**) turns on Wi-Fi.
2. It scans for available networks (either **passively** by listening to beacon frames or **actively** by sending probe requests).
3. When you select a network (SSID), your device sends:
   - **Authentication Request**
   - **Association Request**
4. AP responds and **establishes the connection**.

✅ Now your device is connected **to the AP**, but it doesn’t yet have internet access.

---

## 🧠 Step 2: AP Acts as a Bridge or Gateway

Once connected, the AP needs to **bridge your device to the internet**. It does this in one of two roles:

### 1. **Bridge Mode**

- The AP is **just a wireless extension** of a wired router.
- It passes traffic back and forth **without assigning IP addresses**.
- The **router** handles DHCP (assigning IPs) and internet routing.

### 2. **Router Mode (Standalone AP)**

- The AP itself has **routing capability**.
- It performs **DHCP, NAT, DNS**, and **routes traffic** to the internet.

> 📝 Most home routers combine both AP + Router + DHCP Server in one device (like TP-Link, Netgear, etc.).

---

## 🗂️ Step 3: Device Gets an IP Address (DHCP)

To talk on any network, your device needs an **IP address**.

### Here's how it works (automatically via DHCP):

1. Your device sends a **DHCP Discover** message (broadcast).
2. The AP (or router) replies with a **DHCP Offer** (suggesting an IP address).
3. Your device responds with **DHCP Request** (accepting the offer).
4. The AP replies with **DHCP ACK** (confirmation).

> 🎯 Now your device has:
> - IP address (e.g., `192.168.0.101`)
> - Subnet mask (e.g., `255.255.255.0`)
> - Default gateway (the AP/router IP, e.g., `192.168.0.1`)
> - DNS server address

---

## 🌍 Step 4: Device Sends a Request to the Internet

Let’s say you open a browser and go to `www.google.com`.

1. Your device sends a **DNS request** to find Google’s IP.
2. DNS server replies: `www.google.com` → `142.250.182.36`
3. Your device sends a **data packet** to that IP address.
4. The AP/router **receives the packet** and forwards it to your **internet provider (ISP)** via the modem.

---

## 🔄 Step 5: AP Uses NAT (Network Address Translation)

Your AP shares one **public IP address** (from the ISP) among multiple devices.

- It keeps a **mapping table** of who sent what request.
- This process is called **NAT (Network Address Translation)**.
- So when Google replies, the AP knows which internal device (you) to send it to.

> 📦 NAT allows **many private devices** to use **one public IP**.

---

## 🚥 Step 6: Internet Data Comes Back

- The internet server (like Google) replies to your request.
- The AP receives the data, looks up the correct client, and **forwards it to your device over Wi-Fi**.
- This happens **in milliseconds**.

✅ Congratulations! You now have internet access.

---

## 📶 Wi-Fi Data Flow Summary

Here’s a simplified diagram of the flow:

```txt
[Your Device] ⇄ Wi-Fi ⇄ [Access Point]
                             ↓
                   [Local Network Router/AP]
                             ↓
                       [Internet Modem]
                             ↓
                          [ISP]
                             ↓
                       [Internet Websites]


📚 Key Terms for Beginners
Term	Meaning
- SSID	Network name (e.g., "HomeWiFi")
- DHCP	Automatically gives IP address to your device
- NAT	Shares public IP among many private devices
- IP Address	A unique number identifying your device on a network
- DNS	Converts website names into IP addresses
- Gateway	A device that routes traffic between local network and internet
- Subnet Mask	Defines network range (usually 255.255.255.0 for home networks)
- ISP	Internet Service Provider (e.g., Jio, Airtel, BSNL)

🏠 Real World Analogy
Think of your Wi-Fi Access Point like a receptionist at an office:

- You (the device) ask the receptionist for internet access.

- The receptionist gives you an ID badge (IP address).

- When you send a letter (data), the receptionist logs your name and sends it out.

- When mail comes back (reply), the receptionist knows it's for you and hands it over.

✅ Final Summary
Your device connects to the AP via Wi-Fi.

- The AP (or router) gives your device an IP address using DHCP.

- Your device sends data to the internet, and the AP handles forwarding.

- AP uses NAT to allow multiple devices to share one internet connection.

- Data comes back from the internet and is delivered to the correct device.

📡 The AP is your wireless gateway to the digital world!



# 📡 Adhoc & Wi-Fi P2P (Peer-to-Peer) Operation - Deep Technical Dive

## 🧩 Overview

This guide covers two decentralized wireless communication modes:

* **Adhoc Mode** (aka IBSS - Independent Basic Service Set)
* **Wi-Fi Direct / P2P (Peer-to-Peer)**

We'll explain their concepts, architecture, operation, and differences, with **Wi-Fi P2P** explored in **deep technical detail**.

---

## 🔄 1. Adhoc Mode (IBSS)

### 🧠 Concept

* A wireless network where devices communicate **directly** with each other **without** an Access Point (AP).
* Ideal for **temporary**, **decentralized**, or **mesh** networks.

### 📦 Characteristics

* **No AP needed**: All nodes are equal (peer-to-peer)
* Uses a **shared SSID** and operates in a common channel
* Each station acts as both transmitter and receiver
* Devices must agree on the same **SSID**, **channel**, and optionally **BSSID**

### 🧱 Formation Process

1. One device creates an IBSS with SSID, channel
2. Others scan for the SSID & join by forming IBSS associations
3. All members periodically send **beacon frames**
4. One member takes over **timing synchronization** responsibility

### 📡 Frame Structure Differences

* IBSS uses a special **BSSID** = **random MAC** generated by the initiating station
* Frame addressing differs slightly:

  * **To DS / From DS** = 0 (no distribution system)
  * **Address1 = Destination**, **Address2 = Source**, **Address3 = BSSID**

### 📉 Limitations

* No centralized control (harder QoS, power management)
* Not ideal for large or dynamic networks
* Devices must manually select channels/SSID

---

## 🔁 2. Wi-Fi P2P (Wi-Fi Direct) - In-Depth

### 🧠 Concept

Wi-Fi P2P (802.11 Task Group P) enables devices to form **direct wireless links** with each other, much like Bluetooth, but using full Wi-Fi speed.

Unlike adhoc, **Wi-Fi Direct elects one peer as a temporary AP** (called **P2P Group Owner - GO**) and supports more structured communication.

> 📘 Think of it as "adhoc++" – no infrastructure needed, but retains features like authentication, power save, service discovery, and even IP assignment.

---

## 🏗️ P2P Architecture

### 👥 Entities

* **P2P Device**: A Wi-Fi device supporting Wi-Fi Direct capabilities
* **P2P Group**: Collection of devices connected via Wi-Fi P2P
* **Group Owner (GO)**: Acts like a soft AP
* **Group Client**: Connects to GO, like a station (STA)

### 🕹️ Roles

| Role                 | Description                                                         |
| -------------------- | ------------------------------------------------------------------- |
| P2P GO               | Controls the group; provides beaconing, DHCP (optionally), security |
| P2P Client           | Joins GO; initiates or participates in service discovery            |
| P2P Persistent Group | Saved connection for future reuse                                   |

### 🔌 MAC/PHY Layer Behavior

* Uses standard 802.11 **STA and AP modes**, dynamically created
* Supports **QoS**, **power save**, **encryption (WPA2/WPA3)**
* Wi-Fi Direct still uses **infrastructure-like MAC headers**

---

## 🔍 P2P Group Formation Process

### 🧭 Discovery Phase

1. **Device Discovery**

   * P2P devices send **P2P Probe Requests** (with P2P IE - Information Element)
   * Others reply with **P2P Probe Response**
2. **Capability Exchange**

   * Devices exchange supported roles, intents

### 🏁 Group Formation Phase

1. **GO Negotiation**

   * Devices exchange GO negotiation requests/responses (3-way handshake)
   * GO is chosen based on **GO Intent value** (0-15)
2. **Group Formation**

   * GO creates a P2P Group (acts like AP)
   * Sends **Beacon frames**, **Group Owner IE**, etc.
3. **Authentication & Provisioning**

   * Devices exchange **WPS handshake** (PIN / Push Button Method)
   * Establish WPA2 connection

---

## 🔄 Group Operation Phase

Once connected:

* GO assigns **IP addresses** via DHCP or APIPA
* Devices communicate over standard **IP protocols**
* Optional features:

  * **Service discovery** (UPnP, Bonjour)
  * **Wi-Fi Display / Miracast**
  * **Multicast DNS** for local name resolution

---

## 🧠 Deep Dive: Under-the-Hood

### 📶 Wireless Layer (MAC/PHY)

* GO behaves like a soft AP:

  * Sends **Beacon frames** (P2P IE, SSID="DIRECT-xyz")
  * Accepts **Probe requests**, replies with **Probe responses**
* Clients behave like stations, scanning and associating like in regular Wi-Fi

### 🔒 Security

* WPA2-PSK/WPA3-SAE
* Pairwise keys derived during provisioning
* Optional: GO may enforce group password / PIN input

### ⚡ Power Management

* GO tracks **power save status** of clients
* Implements **Notice of Absence (NoA)**
* Can schedule **client wakeup windows**

### 🌐 IP Layer

* DHCP server runs on GO
* Clients get dynamic IP
* Routing is possible (e.g., to share mobile internet)

---

## 🆚 P2P vs Adhoc - Comparison Table

| Feature                 | Adhoc (IBSS)         | Wi-Fi P2P (Direct)     |
| ----------------------- | -------------------- | ---------------------- |
| Central control         | ❌ None               | ✅ Group Owner (GO)     |
| Security                | 🚫 Optional / Weak   | ✅ WPA2/WPA3            |
| Power Save              | 🚫 Poor              | ✅ Yes (NoA, etc.)      |
| Internet Sharing        | ❌ Difficult          | ✅ GO can share via NAT |
| Service Discovery       | ❌ No                 | ✅ UPnP/Bonjour         |
| Supported in modern OS? | ⚠️ Mostly deprecated | ✅ Widely supported     |
| MAC header format       | IBSS-style           | Infrastructure-style   |

---

## 🧪 Real-World Use Cases

### Adhoc Mode

* Legacy file sharing
* Mesh sensor networks
* Temporary networks with low complexity

### P2P Mode

* Wi-Fi File Transfer (e.g., Android Nearby Share)
* Wireless printing
* Miracast screen sharing
* Game consoles linking
* IoT provisioning

---

## 📚 Summary

* **Adhoc (IBSS)**: Peer-to-peer, decentralized, limited
* **Wi-Fi P2P**: Structured peer-to-peer, uses standard Wi-Fi stack with AP emulation, security, and service discovery
* P2P offers all modern features while removing infrastructure dependency

> 🚀 For developers: Modern P2P implementation involves working with **wpa\_supplicant**, **nl80211**, and **D-Bus API** or **Android Wi-Fi P2P APIs**

---

Let me know if you'd like a diagram or code walkthrough for **P2P GO/Client setup using `wpa_supplicant` and netlink/D-Bus**!
