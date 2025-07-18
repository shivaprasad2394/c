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

Version2:-
# 📶 Ad-Hoc & Wi-Fi Direct (P2P) Operations Explained

---

## 📡 1. Ad-Hoc (IBSS - Independent Basic Service Set)

### 🔍 What is Ad-Hoc Mode?

* **Ad-Hoc Mode** is a type of **wireless communication** setup where devices connect directly to each other **without using an Access Point (AP)**.
* Also called **peer-to-peer wireless** or **IBSS** (Independent Basic Service Set).

### 🧱 Characteristics

* No centralized control (no AP).
* Each device acts as both a **client** and a **router**.
* Suitable for small networks or quick sharing.
* Uses the **SSID** to identify the group.

### 📋 Setup Process

1. Device A creates an Ad-Hoc network (assigns SSID, channel, etc.).
2. Device B scans for available Ad-Hoc networks.
3. Device B joins using the same SSID and channel.
4. Devices communicate **directly over Layer 2 (MAC)**.

### ⚠️ Limitations

* Poor scalability.
* No support for power-saving features.
* Higher collision rate due to lack of coordination.
* Difficult to route data beyond one hop (no mesh natively).

---

## 🤝 2. Wi-Fi Direct (P2P - Peer-to-Peer)

### 🔍 What is Wi-Fi Direct?

* **Wi-Fi Direct (P2P)** is a standard from the **Wi-Fi Alliance** that allows devices to connect **without an AP**, while still supporting advanced features like **WPA2 security**, **service discovery**, and **dynamic group management**.
* Built on top of **IEEE 802.11** standards.

### 🔧 Key Components

* **P2P Device**: Any device that supports Wi-Fi Direct.
* **P2P Group**: A logical grouping of devices connected together.
* **P2P Group Owner (GO)**: A device that acts like a soft AP to manage the group.
* **P2P Client**: A device that joins the group owned by a GO.

### 🛠️ Modes of Operation

* **Group Formation**
* **Persistent Group Reconnection**
* **Autonomous Group Formation**

---

## 🔄 Group Formation Process (Non-Persistent)

### 🧭 Step-by-Step

1. **Device Discovery**

   * Each P2P device broadcasts **probe requests**.
   * Nearby devices respond with **probe responses**.

2. **Negotiation Phase**

   * Devices exchange **GO Intent Values** (0-15).
   * Higher intent becomes **Group Owner (GO)**.
   * If tied, tie-breaker bit is used.

3. **Group Formation**

   * The GO configures the SSID, channel, and security.
   * Sends **Beacon frames** like a real AP.
   * The client performs WPA2 handshake and joins.

4. **Connection Ready**

   * The P2P group now acts like a soft AP + client model.
   * Devices can now communicate, share data, stream, etc.

---

## 🔁 Persistent Group

### 🔐 What is Persistent Mode?

* After the first group formation, credentials and roles are **stored**.
* On future discovery, devices can **auto-connect without GO negotiation**.
* Enables seamless reconnection (e.g., Wi-Fi printers).

---

## 🚀 Autonomous Group Owner

### ⚙️ How it works:

* A device **pre-configures itself** as a Group Owner.
* Starts broadcasting **beacons** like an AP.
* Other devices can **scan and connect** directly.

✅ Useful when:

* You want a permanent GO (like a printer).
* You don’t want to run GO negotiation every time.

---

## 🧠 Technical Internals

### 🔐 Security

* Uses **WPA2-PSK** (AES) for encryption.
* Uses a **4-way handshake** like in normal AP-based Wi-Fi.

### 📡 Wi-Fi Frames

* Uses **standard 802.11 management frames** for discovery.
* Adds **P2P IE (Information Element)** fields in beacons and probes.

### 🔀 Channels

* 2.4 GHz (default) or 5 GHz bands.
* Usually uses **social channels (1, 6, 11)** for initial discovery.

---

## 📉 Limitations of Wi-Fi Direct

* Battery-intensive for GOs.
* Limited support on some OS/devices.
* Limited multi-hop capabilities.
* Doesn’t scale like full mesh or infrastructure networks.

---

## 📚 Use Cases

* File sharing between two phones.
* Wi-Fi printing (printer as GO).
* Screen casting from phone to smart TV.
* IoT devices communicating directly.

---

## 🧭 Quick Comparison: Ad-Hoc vs. Wi-Fi Direct

| Feature                | Ad-Hoc (IBSS)     | Wi-Fi Direct (P2P)         |
| ---------------------- | ----------------- | -------------------------- |
| Central Management     | ❌ No              | ✅ GO acts like AP          |
| WPA2 Security          | ❌ Limited support | ✅ Full WPA2-PSK            |
| Device Discovery       | ❌ Manual          | ✅ Built-in                 |
| OS Support             | ⚠️ Limited        | ✅ Broad (Android, Windows) |
| Reconnection Support   | ❌                 | ✅ Persistent Group         |
| Power Saving           | ❌ Poor            | ✅ Good with P2P PS         |
| Data Rate Optimization | ❌ No coordination | ✅ Better channel use       |

---

> 📘 **Learning Curve Tip:**
> Understanding Wi-Fi Direct requires familiarity with 802.11 frame types, state machines, and device roles (GO vs Client). Use tools like Wireshark in monitor mode to capture real-world P2P packets!

# 📡 Ad-Hoc vs Wi-Fi Direct (P2P) Operation: Deep Dive

---

## 🔸 Overview

Wireless communication without traditional infrastructure (like routers or APs) can happen in two ways:

* **Ad-Hoc Mode** (IBSS)
* **Wi-Fi Direct (P2P)**

---

## 🧱 Ad-Hoc Mode (IBSS - Independent Basic Service Set)

* **Decentralized** network architecture.
* Devices communicate **directly** with each other.
* No AP (Access Point) involved.
* Often used for temporary, small-scale sharing.

### 🔧 Characteristics

* Operates in **infrastructure-less** mode.
* Devices form a **Basic Service Set (BSS)** without a central controller.
* Each station acts as both transmitter and receiver.
* Same SSID is used for identification.
* Typically uses 2.4 GHz band (but can also be 5 GHz).

### 🔄 Communication Process

1. Devices scan for existing Ad-Hoc networks.
2. If found, they join using matching SSID/channel.
3. If not found, a device starts a new IBSS network.
4. All devices use the same channel to exchange frames.

---

## 🔹 Wi-Fi Direct (P2P - Peer-to-Peer)

Wi-Fi Direct is a standard that enables devices to connect **directly** without a traditional AP, yet still use Wi-Fi protocols. Unlike Ad-Hoc, it's more structured.

### 📘 Based On

* Defined in **Wi-Fi Alliance P2P Technical Specification**.
* Uses standard **802.11 MAC/PHY**.
* Often implemented via **wpa\_supplicant** or **nl80211**.

### 🎯 Key Concepts

* **P2P Device**: A Wi-Fi Direct capable device.
* **P2P Group**: A network of P2P devices, one acts as **Group Owner (GO)**.
* **GO (Group Owner)**: Acts like an AP for the P2P group.
* **P2P Client**: Joins a group created by the GO.
* **Persistent Group**: Remembered group configuration for automatic reconnection.

---

## 🧩 P2P Group Formation Phases

### 🔸 1. Device Discovery

* Devices send **P2P Probe Requests** with P2P IE.
* Others respond with **Probe Responses**.

### 🔸 2. GO Negotiation

* Three-way handshake:

  1. **GO Negotiation Request**
  2. **GO Negotiation Response**
  3. **GO Negotiation Confirmation**
* Device with higher intent becomes **Group Owner**.

### 🔸 3. Provisioning Phase

* If WPS is used:

  * Push Button / PIN method to exchange credentials securely.

### 🔸 4. Group Formation

* GO starts beaconing.
* Clients connect like standard STA → AP connection.

### 🌀 Persistent Groups

* Devices store credentials (like SSID, passphrase).
* Future reconnection skips GO negotiation.

### 🔹 Autonomous GO

* A device **preemptively** creates a P2P group.
* Doesn’t require other device to initiate GO negotiation.

---

## 📦 P2P Information Elements (IE) in Wi-Fi Frames

P2P-specific data is embedded in standard Wi-Fi frames (e.g. Beacons, Probe Requests, GO Negotiation frames).

### 🧬 P2P IE Structure

Each P2P IE follows this format:

* **Element ID**: `0xDD` (Vendor Specific)
* **Length**: Total length of this IE
* **OUI**: `50 6F 9A` (Wi-Fi Alliance OUI)
* **OUI Type**: `09` (P2P)
* **P2P Attributes**: Sequence of TLV (Type-Length-Value) blocks

### 📄 Example P2P Attributes

| Type | Attribute Name        | Description                    |
| ---- | --------------------- | ------------------------------ |
| 0x00 | P2P Capability        | Group/Device capabilities      |
| 0x01 | P2P Device ID         | MAC address of device          |
| 0x02 | Group Owner Intent    | GO score: higher wins          |
| 0x04 | Configuration Timeout | Timeout during connection      |
| 0x06 | P2P Group ID          | SSID + Device Address          |
| 0x0D | Channel List          | Supported channels/frequencies |
| 0x0E | Notice of Absence     | Power saving scheduling        |
| 0x0F | Device Info           | Manufacturer, device name, etc |

### 📘 Used In Frames:

* Probe Request/Response
* GO Negotiation Request/Response/Confirm
* Association Request
* Beacon (for GO)

### 🧠 Notes:

* Devices parse P2P IE to evaluate capabilities of peers.
* Helps determine channel, WPS method, intent score, etc.
* `Group Owner Intent` plays a major role in deciding who becomes GO.

---

## ⚖️ Ad-Hoc vs P2P (Wi-Fi Direct)

| Feature                  | Ad-Hoc (IBSS)  | Wi-Fi Direct (P2P)                             |
| ------------------------ | -------------- | ---------------------------------------------- |
| AP Required              | ❌ No           | ❌ No (GO acts like AP)                         |
| Connection Setup         | Manual         | Automated with WPS                             |
| Power Saving             | Less Efficient | More Efficient                                 |
| Persistent Group Support | ❌ No           | ✅ Yes                                          |
| Frame Management         | Basic          | Extended (IEs, WPS)                            |
| Real-World Usage         | Rare           | Widely used (Miracast, printing, file sharing) |

---

## 🔍 Key Takeaways

* **Wi-Fi Direct** is more feature-rich and secure than **Ad-Hoc**.
* Uses **standard Wi-Fi infrastructure** (beacons, authentication).
* **Group Owner Negotiation** is core to the protocol.
* IEs are crucial for capability sharing and negotiation.
* Often abstracted by software like **wpa\_supplicant**, but you can observe it via packet capture tools (e.g. Wireshark).

---

# 📡 Wi-Fi Direct, Hotspot 2.0 and Advanced Wi-Fi Operation

---

## 🌐 Hotspot 2.0 / Passpoint Deep Dive

### 📘 What is Hotspot 2.0 / Passpoint?

* **Hotspot 2.0**, also known as **Passpoint**, is a Wi-Fi Alliance certification aimed at making public Wi-Fi access seamless and secure—just like cellular networks.
* Built on **IEEE 802.11u**, with extensions for secure authentication, automatic provisioning, and roaming.

### 🧠 Key Concepts

| Term          | Meaning                                                                                             |
| ------------- | --------------------------------------------------------------------------------------------------- |
| **ANQP**      | Access Network Query Protocol — protocol for client to discover network details before associating  |
| **OSU**       | Online Sign-Up — secure method to provision credentials over HTTPS                                  |
| **EAP**       | Extensible Authentication Protocol — supports secure authentication like EAP-TTLS, EAP-SIM, EAP-AKA |
| **AAA**       | Authentication, Authorization, Accounting — back-end service, often RADIUS                          |
| **NAI Realm** | Network Access Identifier — identifies home service provider                                        |
| **HESSID**    | Homogeneous Extended Service Set ID — like BSSID, used to identify network groups                   |

### 📡 Operational Flow

1. **Discovery Phase**

   * Client sends Probe Request
   * AP responds with **ANQP Response** containing:

     * Supported Roaming Consortium
     * Venue Name
     * Network Type (e.g., free, commercial)
     * NAI Realms
     * IP Capability
     * WAN Metrics

2. **Authentication**

   * If client has credentials for roaming consortium, it connects using EAP (e.g., EAP-SIM/TTLS/AKA)

3. **Provisioning (if no credentials)**

   * Client connects to **OSU SSID**
   * HTTPS used to securely download a profile
   * Device stores credentials for future use

4. **Roaming**

   * Once provisioned, user can roam between providers using same identity (SIM, certificate, username)

### 📦 Hotspot 2.0 Information Elements

| IE Name                 | Description                                                   |
| ----------------------- | ------------------------------------------------------------- |
| Interworking IE         | Advertises network type, access (emergency, chargeable, etc.) |
| Roaming Consortium IE   | Lists OI (Organization Identifiers) for partner networks      |
| HESSID                  | Identifies the extended network group (like cellular PLMN)    |
| WAN Metrics IE          | Indicates network bandwidth, load, etc.                       |
| Venue Name IE           | Human-readable venue description                              |
| IP Address Availability | Shows whether IPv4/IPv6 is supported                          |
| Connection Capability   | Lists accessible TCP/UDP ports                                |

### 🔧 Backend RADIUS + EAP (TTLS / SIM / AKA)

When the client decides to authenticate, the access point forwards the authentication to a **RADIUS server**, which handles AAA (Authentication, Authorization, Accounting).

#### 🔐 EAP-TTLS Flow (Username + Password)

1. Client sends EAP-Request to AP
2. AP forwards to RADIUS server
3. RADIUS and client set up TLS tunnel
4. Inside the tunnel, user credentials are validated
5. If valid, server sends EAP-Success
6. Session keys are derived → 802.11 association completed

#### 📱 EAP-SIM / EAP-AKA (SIM-Based Auth)

* Used in mobile devices (smartphones, tablets)
* SIM card generates authentication tokens
* RADIUS server forwards to **Mobile Core** or **HSS/HLR** to validate SIM
* Enables **seamless roaming** just like LTE/5G

#### 🔐 Certificates (EAP-TLS)

* Uses X.509 certificates on both client and server
* Strongest security, but provisioning is harder

### 🧪 Real Frame Exchange

* **Client sends:** Probe Request (with Hotspot 2.0 capability)
* **AP replies with:** Probe Response + ANQP advertisement
* **Client issues:** ANQP Query (NAI Realm, Roaming Consortium, etc.)
* **AP sends:** ANQP Response
* **Client decides:** Whether to authenticate or use OSU provisioning
* **Authentication:** EAP-based (handled via RADIUS)

### 🧪 Real-World Tools

* `hostapd` with Hotspot 2.0 config
* `wpa_supplicant` with Passpoint credentials
* `wireshark` filters: `anqp`, `hs20`, `eap`
* Supported in Android (>=4.4), iOS (>=7), Windows 10+

### 🆚 Regular AP vs Passpoint AP

| Feature              | Regular Wi-Fi   | Passpoint (HS2.0)    |
| -------------------- | --------------- | -------------------- |
| Auto Sign-In         | ❌ Manual        | ✅ Seamless           |
| SIM Auth             | ❌ No            | ✅ Yes (EAP-SIM/AKA)  |
| Roaming              | ❌ Rare          | ✅ Standardized       |
| Security             | WPA2-PSK        | WPA2/WPA3 Enterprise |
| Venue Info           | ❌ No            | ✅ Venue IE           |
| Profile Provisioning | ❌ Not supported | ✅ OSU                |

---



# 📡 Wi-Fi Aware (NAN) and Advanced Wi-Fi Operation

---

## 📘 What is Wi-Fi Aware (NAN - Neighbor Awareness Networking)?

* **Wi-Fi Aware** is a peer-to-peer discovery and communication protocol based on **IEEE 802.11mc**.
* Enables continuous background discovery without requiring an internet connection or access point.
* Built for **proximity-based services**: file sharing, multiplayer gaming, location-aware apps, etc.
* Unlike Wi-Fi Direct, Wi-Fi Aware focuses more on discovery and low-latency communication using a shared aware infrastructure.

---

## 🧠 Key Concepts

| Term                            | Meaning                                                               |
| ------------------------------- | --------------------------------------------------------------------- |
| **NAN Master Indication (NMI)** | Indicates which peer acts as the synchronization anchor               |
| **Service Hash**                | Unique hash that represents a service being advertised                |
| **Discovery Window**            | Time interval when nodes wake up to listen or transmit                |
| **Publish / Subscribe**         | Core paradigm — advertise (publish) or listen (subscribe) to services |
| **SDF / FSD / USF**             | Types of Service Discovery Frames: Solicited/Unsolicited              |
| **NAN Cluster**                 | Group of devices synchronized via a Master Election protocol          |
| **Synchronization Beacon**      | Broadcast by master to maintain time sync across cluster              |

---

## 🔄 Operational Workflow

### 1. **Cluster Formation (Discovery and Sync Phase)**

* Devices start by scanning for **NAN beacons**.
* Each device evaluates if a cluster exists; if not, it becomes a **Master**.
* Master sends out **Synchronization Beacons (NAN Sync Beacons)**.
* Other devices sync their clocks and join the cluster as **slaves**.

### 2. **Service Discovery (Publish / Subscribe)**

* **Publish**:

  * Device announces a service (e.g., multiplayer game available).
  * Can be **solicited** (expects a response) or **unsolicited**.

* **Subscribe**:

  * Another device listens for service hash that matches.
  * If match is found, a response is sent.

* Discovery uses **NAN SDF frames** with TLVs (Type-Length-Value):

  * Service Hash
  * Service Info
  * Match Filter

### 3. **Secure Data Path Setup (NAN Data Path - NDP)**

* After discovery:

  * Devices exchange **NDP Setup Request / Response**
  * Negotiate channel, security (e.g., PMKID, MAC addresses)
  * Establish a **direct peer-to-peer data path** using Wi-Fi

* Uses **NDI (NAN Data Interface)** to send traffic outside of traditional IP stack

---

## 🧬 Wi-Fi Aware Frame Types

| Frame Type                        | Description                                                  |
| --------------------------------- | ------------------------------------------------------------ |
| **Sync Beacon**                   | Sent by master — includes timing, cluster ID                 |
| **Sync + Discovery**              | Combined frame for synchronization and service advertisement |
| **SDF (Service Discovery Frame)** | Carries service name, match filter, etc.                     |
| **NDP Setup Req/Resp**            | Used to initiate and confirm data path setup                 |
| **NDPE**                          | Encapsulation for sending user data over NDP                 |

---

## 🔒 Security

* NAN itself is discovery focused, but for NDP:

  * Encryption is possible with **PMK (Pairwise Master Key)** or **PMKID**
  * Some implementations rely on Wi-Fi Protected Management Frames
  * Identity protection is minimal by default — security is app-layer driven

---

## 🧪 Real-World Use Cases

| Use Case             | Description                                         |
| -------------------- | --------------------------------------------------- |
| Multiplayer Gaming   | Discover nearby players and establish data channel  |
| Contactless Payments | Authenticate and transact via NDP                   |
| Smart Home           | Devices automatically find and sync with each other |
| Location-Based Ads   | Proximity triggers messages or actions              |
| Device Pairing       | No need for QR scan or passwords                    |

---

## 🧰 Developer Tools and Ecosystem

* **Android Wi-Fi Aware API** (since Android 8.0):

  * `WifiAwareManager`
  * Supports session callbacks, message exchange, and data paths
* **Linux mac80211 + cfg80211 (nl80211 NAN commands)**
* **Wireshark filters**: `nan`, `ndp`, `nan-action`, `nan-mgmt`
* **chipset support**: QCA6174, QCA9377, and newer Intel/MediaTek chips

---

## ⚙️ Internal MAC/PHY Layer Flow

1. **MAC Layer: NAN State Machine**

   * Handles cluster formation, master election, DW scheduling
   * Manages publish/subscribe SDF and beacon timing

2. **PHY Layer: Timing + Power Efficiency**

   * Leverages **target wake time (TWT)** and **low duty cycle sync**
   * Ensures high power efficiency for mobile nodes

3. **Data Plane Path (NDP)**

   * Operates outside TCP/IP stack
   * Traffic over **NDI interfaces**, bypassing IP routing
   * Ideal for low-latency, short-lived data transfers

---

## 📉 Comparison: Wi-Fi Direct vs Wi-Fi Aware

| **Feature**          | Wi-Fi Direct    | Wi-Fi Aware (NAN)          |
| ---------------- | --------------- | -------------------------- |
| Discovery        | One-time        | Continuous Background      |
| Sync Model       | Leader-Follower | Distributed Clustered Sync |
| Data Path        | IP-based        | Optional Direct NDP        |
| Power Efficiency | Moderate        | High (TWT, DW)             |
| Group Ownership  | Yes             | No (clustered peers)       |
| Internet Routing | Possible        | No (local only)            |

---


# 🔐 Advanced Wi-Fi Technologies: DPP, FTM/RTT, and Wi-Fi Sensing

---

## 📶 Device Provisioning Protocol (DPP - Easy Connect)

DPP is a modern, secure, and flexible method to provision Wi-Fi devices without needing default passwords or QR codes.

---

### 🔑 Why DPP?

* Replaces legacy WPA2-PSK (pre-shared key)
* Eliminates default credentials and manual password entry
* Enables secure out-of-band (OOB) device onboarding via QR code, NFC, or BLE
* Designed for smart homes, IoT, and enterprise onboarding

---

### 🧠 DPP Core Concepts

| Term                       | Meaning                                               |
| -------------------------- | ----------------------------------------------------- |
| **Configurator**           | Device that initiates provisioning (e.g., smartphone) |
| **Enrollee**               | Device being provisioned (e.g., IoT device, AP)       |
| **Bootstrapping**          | Establish initial secure contact (QR/NFC/BLE/PKEX)    |
| **Authentication**         | Mutual public key cryptography (Curve25519/ED25519)   |
| **Configurator Connector** | Contains encrypted Wi-Fi credentials and policy       |

---

### 🔄 DPP Operation Flow

1. **Bootstrapping Phase**

   * Enrollee shares bootstrapping info (QR code, NFC tag, BLE, PKEX)
   * Configurator captures and stores public key and bootstrapping info

2. **Authentication Phase**

   * Mutual authentication via authenticated Diffie-Hellman (Curve25519)
   * Prevents MITM and impersonation

3. **Configuration Phase**

   * Configurator sends Connector (Wi-Fi SSID, password, AKMs, etc.) encrypted to Enrollee
   * Enrollee applies credentials and connects to Wi-Fi

4. **Acknowledgment**

   * Enrollee confirms successful provisioning

---

### 🛡️ Security Highlights

* Public key cryptography
* Authenticated Diffie-Hellman exchange
* Anti-cloning & anti-spoofing
* No need for shared secrets or default keys

---

## 🛰️ Fine Time Measurement (FTM) / Wi-Fi RTT (802.11mc)

FTM allows accurate distance measurement using Wi-Fi by calculating the round-trip time of frames between devices.

---

### 🔧 How RTT Works

1. **FTM Request / Response**

   * Initiator sends an FTM request to Responder (e.g., AP)
   * Responder replies with timestamps (T1, T2)

2. **Timing Exchange**

   * Round-trip time = (T4 - T1) - (T3 - T2)
   * Distance ≈ (RTT × speed of light) / 2

---

### ⚙️ Requirements

* 802.11mc support on both devices (AP and client)
* Location permission (on Android)
* Accurate timestamping capability in hardware/firmware

---

### 📐 Applications

* Indoor navigation (malls, airports)
* Device localization and AR
* Home automation triggering based on proximity

---

### 🔍 Packet Types Involved

* **Action frames** (FTM Request / Response)
* **Timestamp IEs**
* Timestamps at PHY-level resolution (sub-microsecond)

---

## 🌐 Wi-Fi Sensing / Location Awareness

Wi-Fi Sensing uses variations in RF signals (amplitude, phase, Doppler shifts) to infer motion, presence, or gestures.

---

### 🎯 Key Concepts

| Feature                             | Description                                |
| ----------------------------------- | ------------------------------------------ |
| **Channel State Information (CSI)** | Fine-grained per-subcarrier signal info    |
| **RSSI/Phase/ToF**                  | Traditional signal parameters              |
| **Doppler Shift**                   | Used to detect motion and velocity         |
| **Multipath Analysis**              | Detect presence via changes in reflections |

---

### ⚙️ Sensing Techniques

1. **Passive Sensing**: Analyze changes in signal from ambient traffic (e.g., AP to client)
2. **Active Sensing**: Generate specific probe packets and analyze returns

---

### 🤖 Use Cases

* Intrusion detection (human presence)
* Sleep monitoring
* Gesture recognition
* Fall detection for elderly
* Smart lighting and HVAC control

---

### 📡 Technical Stack

* Wi-Fi 802.11bf (Sensing standardization effort)
* Use of OFDM and MIMO reflections
* CSI extraction from firmware/driver (Intel, Atheros, Mediatek chips)

---

### 🔬 Real-World Integration

* Qualcomm, Intel, Cisco developing Wi-Fi sensing APIs
* Wi-Fi sensing chipsets with CSI export becoming more common

---
# 🚀 Advanced Wi-Fi Topics: Wi-Fi 5, Wi-Fi 6, Wi-Fi 7, and QoS (WMM/TSPEC)

---

## 📶 IEEE 802.11ac (Wi-Fi 5)

### 🧠 Key Features

* Introduced in 2013 (Wave 1) and extended in 2016 (Wave 2)
* Operates in **5 GHz** band only
* **MU-MIMO (Downlink)** for simultaneous stream transmission
* **Channel bandwidths**: 20, 40, 80, 160 MHz (Wave 2)
* Max theoretical PHY rate: \~6.9 Gbps (8 spatial streams, 160 MHz)

### 📐 Technology Stack

* **Modulation**: Up to 256-QAM
* **FEC**: LDPC (optional)
* **Beamforming**: Explicit Beamforming for targeted spatial streams
* **Frame Aggregation**: A-MPDU, A-MSDU
* **Block Ack**: Improves efficiency by grouping ACKs

### 🧪 Practical Impact

| Feature        | Benefit                                  |
| -------------- | ---------------------------------------- |
| Wider Channels | Higher throughput                        |
| MU-MIMO        | Better performance with multiple clients |
| 256-QAM        | Higher spectral efficiency               |

---

## ⚡ IEEE 802.11ax (Wi-Fi 6)

### 🧠 Key Innovations

* Operates in both **2.4 GHz + 5 GHz** bands
* Introduced **OFDMA (Orthogonal Frequency Division Multiple Access)**
* **Uplink + Downlink MU-MIMO**
* **Target Wake Time (TWT)** for power efficiency
* **1024-QAM** modulation for denser packing

### 📐 OFDMA Breakdown

* Each channel is split into **Resource Units (RUs)**
* Multiple clients can transmit simultaneously in a single channel
* Reduces latency and improves spectrum use

### 📉 Airtime Fairness

* Legacy Wi-Fi gives time fairness, not throughput fairness
* Wi-Fi 6 allocates **equal airtime** using scheduling and OFDMA

### 🔐 BSS Coloring

* Tags frames from different APs to reduce co-channel interference
* Enables spatial reuse in dense environments

### 🧪 Wi-Fi 6 Performance Features

| Feature           | Role                                |
| ----------------- | ----------------------------------- |
| TWT               | Reduces power drain                 |
| OFDMA             | Multi-user channel access           |
| MU-MIMO (UL + DL) | Better simultaneous client handling |
| 1024-QAM          | Denser data modulation              |
| Spatial Reuse     | Better range & concurrency          |

---

## 🚀 IEEE 802.11be (Wi-Fi 7)

### 🧠 Evolutionary Goals

* Operates in **2.4, 5, and 6 GHz** (multi-band convergence)
* Up to **320 MHz channel bandwidth**
* **4096-QAM** (12 bits/symbol)
* **Multi-Link Operation (MLO)**: combine multiple bands/interfaces
* **Preamble Puncturing**: dynamically use portions of spectrum
* **Extremely Low Latency (ELL)**: <1ms target for AR/VR

### 🔗 Multi-Link Operation (MLO)

* One MAC coordinates multiple PHYs
* Parallel use of 5 GHz + 6 GHz + 2.4 GHz
* Improves reliability and latency by switching or aggregating links

### 🧠 Technical Enhancements

| Feature           | Function                   |
| ----------------- | -------------------------- |
| 320 MHz BW        | Doubles max throughput     |
| MLO               | Seamless multi-band use    |
| 4096-QAM          | Very high data density     |
| Flexible OFDMA    | Smarter dynamic scheduling |
| Coordinated OFDMA | Low-latency group access   |

### 📈 Expected Throughput

* Max theoretical rate: **>46 Gbps**
* Depends on channel conditions, MLO, QAM, and stream count

---

## 🎯 QoS in Wi-Fi: WMM and TSPEC

### 📘 WMM (Wi-Fi Multimedia)

* Based on IEEE 802.11e
* Defines **Access Categories (ACs)**:

  * **AC\_VO**: Voice
  * **AC\_VI**: Video
  * **AC\_BE**: Best Effort
  * **AC\_BK**: Background

Each AC has its own **Contention Window (CW)** and **Arbitration Inter-Frame Space (AIFS)**:

* Voice gets smallest CW and AIFS → prioritized
* Background gets largest → deprioritized

### ⚙️ WMM Parameters Table

| AC | CWmin | CWmax | AIFS | TXOP Limit |
| -- | ----- | ----- | ---- | ---------- |
| VO | 3     | 7     | 2    | 1.504 ms   |
| VI | 7     | 15    | 2    | 3.008 ms   |
| BE | 15    | 1023  | 3    | N/A        |
| BK | 15    | 1023  | 7    | N/A        |

### 🎯 TSPEC (Traffic Specification)

* TSPEC is used in **QoS-capable networks** for reserved traffic
* Clients send TSPEC requests with:

  * Traffic type (voice, video)
  * Data rate
  * Delay bounds
  * Service intervals
* AP admits or rejects based on available resources

### 🧪 Use Cases

| Application | AC     | Why?                         |
| ----------- | ------ | ---------------------------- |
| Voice Call  | AC\_VO | Lowest latency needed        |
| Video Call  | AC\_VI | High throughput & low jitter |
| Web Surfing | AC\_BE | No strict requirements       |
| Sync Backup | AC\_BK | Least priority               |

---


