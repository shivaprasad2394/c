# 🌐 Wireless LAN and IEEE 802.11 Overview

## 🔧 What is Wireless LAN?

A **Wireless LAN** is a network where devices communicate using wireless protocols/technologies within a defined area.

---

## 📜 IEEE 802.11 Standard

IEEE 802.11 provides a standard for wireless LAN, it specifies functionalities across two key layers of the OSI model:

- **Physical Layer**
- **Data Link Layer**

---

## 📶 Wireless Services in IEEE 802.11
802.11 standard we have two kinds of services
## 1. **BSS (Basic Service Set)**

- A group/unit of wireless network devices communicating with the same **Access Point (AP)**.

### 2. **ESS (Extended Service Set)**

- A collection of multiple APs and their associated client stations, all united by a single **Distribution System Medium (DSM)**.
- The **ESSID** (Extended SSID) is the shared network name.
- The terms **SSID** and **ESSID** are often used interchangeably.

---

## 📡 Key Terms

- **BSSID**: The physical /MAC address of the AP (48-bit hex).
- **AP (Access Point)**:these are devices which accept Wireless signals from multiple devices and retransmit them to  the rest of the network.
  - Acts as a bridge between wireless devices and the wired network.
  - Operates at Layer 2 (Data Link Layer).
- **SSID**: A unique string identifying a wireless network.

# 📡 Wireless Network Modes

Wireless network interface cards (NICs) can operate in several modes, each designed for specific purposes. Below are the common Wi-Fi modes:

## **1. Infrastructure Mode**
- **Most common mode** used in Wi-Fi networks.
- Devices (stations) communicate through a central **Access Point (AP)**.
- AP manages traffic and facilitates communication between devices and external networks (e.g., internet).

## **2. Ad-Hoc Mode (IBSS - Independent Basic Service Set)**
- Peer-to-peer communication **without** an Access Point.
- Devices connect directly in a **decentralized** network.
- Suitable for small or temporary networks.

## **3. Monitor Mode (Promiscuous Mode)**
- NIC listens to all wireless frames in the air, even if not addressed to it.
- Used for:
  - Packet sniffing
  - Wireless troubleshooting
  - Network analysis and security auditing
- Unlike promiscuous mode in Ethernet, monitor mode works at the radio level.

## **4. Master Mode**
- Typically used by **Access Points**.
- The device acts as a central controller allowing other devices (clients) to connect.

## **5. Repeater Mode**
- Extends the range of an existing wireless network.
- Receives signal from an AP and rebroadcasts it.

## **6. Bridge Mode**
- Connects two different network segments, often wired and wireless.
- Used to link two LANs using wireless communication.

## **7. Mesh Mode**
- Devices (nodes) act as both clients and routers.
- Creates a **self-healing, self-configuring** wireless network.
- Common in large area deployments like campuses or smart cities.

## **8. Client Mode**
- Standard mode where a device (e.g., laptop, phone) connects to an AP to access the network.

---

# 🧩 Data Link Layer Details

The **Data Link Layer** in the OSI model ensures reliable data transfer between two directly connected nodes. It is divided into two sublayers:

## **Two Sublayers**

### 1. Logical Link Control (LLC)
- Provides an interface between the network layer and MAC sublayer.
- Responsible for:
  - Frame synchronization
  - Flow control
  - Error checking

### 2. Medium Access Control (MAC)
- Controls access to the physical transmission medium.
- Responsible for:
  - Addressing (MAC addresses)
  - Channel access control
  - Frame delimiting and error detection

---
## 🕹️ MAC Layer Functions:-
In Mac we have two more layers
### 1. **DCF (Distributed Coordination Function)**

- it provides contention Based Services i.e it uses **CSMA/CA** (Carrier Sense Multiple Access with Collision Avoidance).
- Operates on **half-duplex**.
- **csma\ca Timers** are used to avoid collisions.

> 📌 *CSMA/CA is for wireless, CSMA/CD is for wired.*

### 2. **PCF (Point Coordination Function)**

- Poll-based / priority-based access mechanism.

---

# 📡 CSMA/CA in Wi-Fi: Problems Explained

## 🧠 What is CSMA/CA?

**Carrier Sense Multiple Access with Collision Avoidance (CSMA/CA)** is a network protocol used in **Wi-Fi** to manage how multiple devices share the same wireless channel.

> 💡 It tries to **avoid** collisions *before* they happen, unlike CSMA/CD (used in Ethernet), which handles collisions *after* they occur.

---

## ⚙️ How CSMA/CA Works (Simplified)

1. A device **"listens"** to check if the wireless channel is free.
2. If the channel is **idle**, it waits for a short, random time.
3. If still idle, it **sends** the data.
4. If the channel is **busy**, the device waits and tries again later.

---

## ❗ Common Problems with CSMA/CA in Wi-Fi

### 1. 🔇 Hidden Node Problem

#### 📍 What happens:
- Two devices (A and C) are **out of range** of each other but **both in range** of the same Access Point (B).
- A and C **can’t hear** each other.
- Both think the channel is free and **transmit at the same time** → causing a **collision** at B.

#### 📌 Real-World Analogy:
> Imagine two people in separate rooms trying to talk to the same receptionist over a walkie-talkie. They can’t hear each other and both talk at once, confusing the receptionist.

---

### 2. 📡 Exposed Node Problem

#### 📍 What happens:
- A device refrains from transmitting, thinking the channel is busy, even when its transmission **would not cause interference**.

#### 📌 Example:
- Device A is sending data to B.
- Device C wants to send data to D.
- C hears A's signal and assumes the channel is busy.
- But since C → D and A → B are **non-interfering**, it could have transmitted safely.

#### ❌ Result:
- **Unnecessary waiting** → **inefficient use** of the wireless channel.

---

### 3. 🐢 High Overhead from Waiting

- Due to **random backoff timers** and **acknowledgments**, there is a delay even when the network is idle.
- Leads to **reduced throughput**, especially with many devices.

---

### 4. 📶 Performance Drops with More Devices

- As more devices share the channel, the chances of collisions and delays increase.
- **Congestion** leads to **packet loss**, **retransmissions**, and **slower speeds**.

---

### 5. 🔁 No Central Control

- Wi-Fi uses a **distributed system**, so each device independently decides when to transmit.
- This can lead to **poor coordination**, especially in crowded networks.

---

## ✅ Summary of CSMA/CA Limitations
| **Issue**            | **Description**                                                            | **Solutions**                                                                 |
|----------------------|-----------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| **Hidden Node**       | Devices unaware of each other cause unintentional collisions               | Use of **RTS/CTS (Request to Send / Clear to Send)** mechanism in 802.11     |
| **Exposed Node**      | Devices unnecessarily delay sending even when it's safe                    | Improved MAC protocols and **carrier sensing** with RTS/CTS                   |
| **Overhead**          | Waiting, backoff, and acknowledgment mechanisms reduce speed               | **Frame aggregation**, **block acknowledgments**, and **802.11n/ac/ax** improvements |
| **Scalability**       | Performance degrades as the number of users increases                      | Introduction of **OFDMA** (Orthogonal Frequency Division Multiple Access) and **MU-MIMO** in 802.11ax |
| **Lack of Coordination** | No central controller leads to inefficiencies in shared environments   | Use of **Access Points** in Infrastructure mode and centralized management via controllers (in enterprise WLANs) |


---

## 🧠 Alternatives & Solutions

- 🧱 **RTS/CTS (Request to Send / Clear to Send)**: Optional handshake that reduces hidden node collisions.
- 🚀 **Wi-Fi 6 (802.11ax)** introduces better coordination through **OFDMA** and **BSS Coloring**.
- 🛰️ **Mesh Networking** helps balance loads and reduce interference.

---

## 🌐 Final Thought

CSMA/CA is **essential** for wireless networking, but it comes with **challenges**, especially in **crowded** or **large** networks. Understanding these problems helps in designing **better Wi-Fi** systems and troubleshooting **connectivity issues**.

### 🚦 OFDMA (Orthogonal Frequency Division Multiple Access)

- **What it is**: An enhancement of OFDM (used in previous Wi-Fi standards) that allows multiple users to transmit data **simultaneously** by dividing a channel into smaller sub-channels called **Resource Units (RUs)**.
  
- **How it works**:
  - The available bandwidth (e.g., 20/40/80 MHz) is divided into smaller frequency tones (subcarriers).
  - Each user is assigned a group of these subcarriers (RUs), allowing multiple users to share the channel **at the same time** instead of waiting their turn.
### 👥 MU-MIMO (Multi-User Multiple Input, Multiple Output)

- **What it is**: A method that allows a wireless access point to transmit **different data streams to multiple devices simultaneously**, using multiple antennas.

- **How it works**:
  - The AP has multiple antennas that can focus signals (beamforming) and serve several clients **at once** instead of one at a time.
  - Previously, MU-MIMO worked only for **downlink**; 802.11ax introduces **uplink MU-MIMO** as well.
### 🔄 Downlink vs Uplink MU-MIMO

**MU-MIMO (Multi-User Multiple Input, Multiple Output)** allows multiple devices to communicate with an access point (AP) at the same time, using multiple antennas. This can happen in two directions:

---

#### 📤 Uplink MU-MIMO

- **What it is**: Multiple client devices **simultaneously send data** to the access point.
- **Introduced in**: **802.11ax** (Wi-Fi 6)
- **Example**: Several smartphones uploading photos to the cloud at the same time.
- **Benefit**: Reduces congestion and wait time when many devices are transmitting data to the AP.

---

#### 📥 Downlink MU-MIMO

- **What it is**: The access point **simultaneously sends different data streams** to multiple devices.
- **Introduced in**: **802.11ac Wave 2** (downlink only), enhanced in **802.11ax**
- **Example**: Streaming different videos to a tablet, a laptop, and a smart TV — all at once.
- **Benefit**: Increases download efficiency and overall throughput.

---

### 🧠 Summary Table

| Direction     | Introduced In | Who Sends Data | Who Receives Data | Real-Life Example                            |
|---------------|----------------|----------------|--------------------|----------------------------------------------|
| **Downlink**  | 802.11ac (Wave 2) | Access Point   | Multiple Devices   | Watching YouTube on multiple devices         |
| **Uplink**    | 802.11ax          | Multiple Devices | Access Point       | Uploading files to Google Drive from phones  |

---

## 🔍 Scanning and Association

### What is Scanning?

The process by which a station discovers available wireless networks(AP) before associating with an AP.

### Scanning Steps:

1. Station sends a **probe request frame**.
2. Nearby APs respond with **probe response frames**.
3. Station sends an **association request** to the chosen AP.
4. AP sends back an **association response**.

### Scanning Types:

- **Active Scanning**: Station sends probe request → AP responds.
- **Passive Scanning**: APs periodically send **beacon frames**( advertising packets illustrating its capability to all stations).

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

## 🔐 WPA2 Encrypted Connection Process

The process of establishing a secure WPA2 connection between a **client station (STA)** and an **Access Point (AP)** involves several key steps:

1. **🔎 Probe Request**
   - The **station** sends a **probe request** to discover nearby APs.
   - It includes supported data rates, security capabilities, and SSID (if known).

2. **📡 Probe Response**
   - The **AP** responds with a **probe response** containing its capabilities and supported configurations.

3. **🛂 Authentication Request**
   - The **station** sends an **authentication request** to the AP (Open System Authentication is used in WPA2).

4. **🛡️ Authentication Response**
   - The **AP** sends back an **authentication response**, typically approving the request.
   - At this stage, the station is **authenticated but not yet associated**.

5. **🔗 Association Request**
   - The **station** sends an **association request** to the AP.
   - This includes supported features and the **encryption type** (e.g., WPA2 with AES).

6. **📶 Association Response**
   - The **AP** sends an **association response** containing a **status code** and an **Association ID (AID)**.

7. **🔐 Four-Way Handshake (if WPA2/WPA/WEP)**
   - If encryption is enabled (WPA2/WPA/WEP), the AP and station perform a **Four-Way Handshake** to:
     - Confirm mutual possession of the **Pairwise Master Key (PMK)**
     - Derive **session keys** for encryption (PTK & GTK)
     - Ensure secure communication is established

---

### ✅ Summary
Once the Four-Way Handshake is complete, the station is **fully connected and encrypted** using WPA2, and can securely send and receive data over the wireless network.



---
## 🔐 Four-Way Handshake (WPA2)

Used for secure key exchange between client and AP.

### Steps:

1. **AP** generates **ANonce** and sends to **station**.
2. **Station** computes **PMK**(Pairwise Master Key)  from SSID + password, generates **SNonce**, and derives **PTK**.
3. **Station** sends **SNonce** to AP.
4. **AP** derives **PTK**, generates **GTK**, and sends GTK to station.
5. **Station** sends **ACK** to confirm.

---
## 🔐 Wi-Fi Security Standards, Encryption, and Authentication Overview

| **Name**   | **Category**             | **Purpose**                                         | **Encryption**                  | **Authentication**                        | **Status / Notes**                             |
|------------|--------------------------|-----------------------------------------------------|----------------------------------|--------------------------------------------|-------------------------------------------------|
| **WEP**    | Security Protocol         | Original Wi-Fi security (weak)                     | RC4                              | Static pre-shared key                     | ❌ Obsolete / Insecure                          |
| **WPA**    | Security Protocol         | Temporary improvement over WEP                     | TKIP (uses RC4)                  | PSK / 802.1X                              | ⚠️ Deprecated                                   |
| **WPA2**   | Security Protocol         | Strong standard since 2004                         | AES (via CCMP)                   | PSK / 802.1X                              | ✅ Secure / Widely adopted                     |
| **WPA3**   | Security Protocol         | Latest standard (2018), improves WPA2              | AES (with GCMP-256 or CCMP-128)  | SAE (Personal) / 802.1X + EAP (Enterprise) | ✅ Modern / Strongest available                |

---

| **Name**   | **Category**             | **Purpose**                                         | **Encryption**                  | **Used In**                                | **Status / Notes**                             |
|------------|--------------------------|-----------------------------------------------------|----------------------------------|---------------------------------------------|------------------------------------------------|
| **TKIP**   | Encryption Algorithm      | Fix WEP flaws using per-packet keying              | RC4 + MIC + IV mixing            | WPA                                          | ❌ Deprecated / Weak                           |
| **CCMP**   | Encryption Algorithm      | Strong AES-based encryption + data integrity       | AES (CTR + CBC-MAC)              | WPA2, WPA3                                  | ✅ Secure and mandatory in WPA2 and WPA3       |
| **GCMP**   | Encryption Algorithm      | More efficient & secure than CCMP (used in WPA3)   | AES (Galois/Counter Mode)        | WPA3                                        | ✅ Stronger, used in high-security deployments |

---

| **Name**   | **Category**             | **Purpose**                                         | **Encryption Varies?**          | **Used In**                                | **Status / Notes**                             |
|------------|--------------------------|-----------------------------------------------------|----------------------------------|---------------------------------------------|------------------------------------------------|
| **SAE**    | Auth Protocol (WPA3-Personal) | Replaces PSK with secure key exchange             | Yes (AES + GCMP/CCMP)           | WPA3-Personal                               | ✅ Secure / Resists offline dictionary attacks |
| **EAP**    | Auth Framework (WPA2/WPA3-Enterprise) | Flexible authentication in enterprise networks | Depends on EAP type              | WPA2/WPA3-Enterprise                        | ✅ Secure with certificates (e.g. EAP-TLS)     |

---

### 📝 Quick Definitions:
- **Security Protocol**: Overall system that defines how Wi-Fi is secured.
- **Encryption Algorithm**: Technique used to encrypt and ensure data integrity.
- **Authentication Method**: How users/devices prove their identity.

---
## 🔐 WPA3 Encrypted Connection Process (with SAE)

In **WPA3-Personal**, the connection process replaces the traditional PSK-based handshake with **SAE (Simultaneous Authentication of Equals)** for improved security. Here's how a WPA3 connection is established:

---

### 1. 🔎 **Probe Request**
- The **station (STA)** sends a **probe request** to discover nearby APs.
- It includes supported security capabilities and optionally the SSID.

### 2. 📡 **Probe Response**
- The **AP** replies with a **probe response**, listing its supported features, including WPA3 (SAE).

---

### 3. 🤝 **SAE Handshake (Authentication)**
- **SAE** replaces the traditional open-system authentication.
- A secure **Diffie-Hellman key exchange** is performed:
  - Both station and AP generate cryptographic elements using the shared password.
  - They exchange public values.
  - Each side derives the same **Pairwise Master Key (PMK)** without exposing the password.
- **Mutual authentication** is achieved.
- SAE is **resistant to offline dictionary attacks**.
- After a successful exchange, the **station is authenticated**.

---

### 4. 🔗 **Association Request**
- The **station** sends an **association request**, indicating its desire to join the network and confirming support for WPA3.

### 5. 📶 **Association Response**
- The **AP** replies with an **association response**, assigning an **Association ID (AID)** and confirming success.

---

### 6. 🔐 **Four-Way Handshake**
- Just like WPA2, WPA3 still uses the **Four-Way Handshake**, but with the **SAE-derived PMK**:
  - Establishes the **Pairwise Transient Key (PTK)** for encryption.
  - Delivers the **Group Temporal Key (GTK)** for multicast/broadcast.
  - Confirms mutual possession of keys.

---

### ✅ Summary
Once the SAE handshake and Four-Way Handshake are completed:
- The **station is securely authenticated**.
- All data transmission is **encrypted using AES (CCMP or GCMP)**.
- The connection offers **forward secrecy** and stronger protection against brute-force attacks.

## 🏢 WPA2-Enterprise Connection Process (with EAP-TLS / PEAP)

**WPA2-Enterprise** uses **802.1X authentication** and the **Extensible Authentication Protocol (EAP)** to provide **strong, centralized, and certificate-based security**, ideal for enterprise environments.

The process differs from WPA2-Personal, as it involves a **RADIUS server** and may use **client/server certificates** depending on the EAP method.

---

### 🔁 Shared Steps (WPA2-Enterprise with EAP)

1. **🔎 Probe Request / Response**
   - The **station (STA)** sends a **probe request** to discover nearby APs.
   - The **AP** replies with its supported capabilities.

2. **🛂 Open System Authentication**
   - A basic **open authentication exchange** occurs (not actual security auth).
   - STA is now authenticated at Layer 2 but not yet authorized to access the network.

3. **🔗 Association Request / Response**
   - The STA sends an **association request** to the AP, signaling intent to join the network.
   - The AP responds with an **association response**, assigning an AID.

4. **🧠 802.1X Authentication Begins**
   - The AP acts as a **relay** between the STA and the **RADIUS server**.
   - The **EAP authentication method** is negotiated (e.g., EAP-TLS or PEAP).

---

### 🔐 EAP-TLS (Certificate-Based)

- **Mutual certificate-based authentication**:
  - The **RADIUS server presents its certificate** to the client.
  - The **client also presents a certificate** to the server.
- **TLS handshake** establishes a **secure tunnel**.
- A **master session key (MSK)** is derived and securely shared with the AP.
- Requires:
  - **Client certificate**
  - **Server certificate**
- **Security**: Very high, with mutual authentication and no passwords.

---

### 🔐 PEAP (Password + TLS Tunnel)

- **Protected EAP (PEAP)** creates a secure TLS tunnel between the client and server.
- Only the **server presents a certificate** (client does not).
- After the tunnel is established:
  - The client authenticates using **username/password** (e.g., MSCHAPv2).
- Easier to manage (no client certs), but:
  - Slightly **less secure** than EAP-TLS.
  - Still strong when configured properly.

---

### 🔄 4-Way Handshake

- Once EAP authentication succeeds:
  - Both parties derive a shared **Pairwise Master Key (PMK)**.
  - The AP and station perform the **Four-Way Handshake**:
    - Derive **PTK** (Pairwise Transient Key)
    - Exchange **GTK** (Group Temporal Key)
    - Finalize encryption setup

---

### ✅ Summary

After successful EAP authentication and the 4-Way Handshake:
- The client is **securely authenticated**.
- **Encrypted communication** is enabled using AES (CCMP).
- Centralized identity and access management is enforced via the **RADIUS server**.

---

### 🔍 EAP-TLS vs PEAP Comparison

| Feature                   | **EAP-TLS**                          | **PEAP (e.g., with MSCHAPv2)**             |
|---------------------------|--------------------------------------|--------------------------------------------|
| Auth Method               | Mutual certificate-based             | Username/password inside TLS tunnel        |
| Client Certificate Needed | ✅ Yes                                | ❌ No                                       |
| Server Certificate Needed | ✅ Yes                                | ✅ Yes                                      |
| Mutual Authentication     | ✅ Strong                             | ⚠️ Partial (only server verified directly)  |
| Security Level            | 🔒 Very High                          | 🔐 Moderate–High (depends on password policy) |
| Management Overhead       | ⚠️ Higher (certificate provisioning)  | ✅ Lower (easier for large orgs)            |

---

## 📡 What is EAPOL (Extensible Authentication Protocol over LAN)?

**EAPOL** is the protocol used to transport **EAP messages** between the **station (client)** and the **Access Point (AP)** in **802.1X-based authentication**, including EAP-TLS and PEAP.

- Defined by: **IEEE 802.1X**
- Runs at: **Data Link Layer (Layer 2)**
- Used in: **Both wired and wireless networks**

---

### 📥 Where is EAPOL Used in the WPA2-Enterprise (EAP-TLS/PEAP) Process?

Here's how it fits into the authentication sequence:

1. **Station connects to the AP** via association request/response (standard Wi-Fi process).
2. **802.1X authentication begins.**
   - AP sends an **EAP-Request/Identity** frame to the station using **EAPOL**.
   - Station responds with **EAPOL-Response/Identity**.
3. All subsequent **EAP-TLS or PEAP messages** (certificates, credentials, etc.) are exchanged over **EAPOL** between the station and AP.
   - The AP **relays EAPOL messages** to/from the **RADIUS server** using **RADIUS over UDP**.

---

### 🔐 Transition to 4-Way Handshake

- Once the **EAP-TLS handshake is complete**, a **Pairwise Master Key (PMK)** is derived.
- Then, the **4-Way Handshake** begins, which is also carried over **EAPOL frames**:
  - These include key confirmation, PTK/GTK derivation, and key installation.

---

### ✅ Summary Table

| Stage                        | Protocol Used | Transport Medium      |
|-----------------------------|---------------|------------------------|
| EAP Identity Exchange        | EAPOL         | Between STA and AP     |
| EAP-TLS / PEAP Auth Process  | EAP over EAPOL| STA ↔ AP ↔ RADIUS Server|
| 4-Way Handshake (Key Exchange)| EAPOL-Key     | STA ↔ AP               |

---

### 📝 Key Points
- **EAPOL** is not an EAP method itself; it’s the **carrier** for EAP messages in 802.1X.
- It’s used in **both authentication and key exchange** phases of WPA2-Enterprise.
- **EAPOL-Key frames** are used specifically in the **4-Way Handshake** after authentication succeeds.



## 🌍 Layer 3 – DHCP Process + Network Info

After a successful Layer 2 (Wi-Fi) connection, your device begins the **DHCP (Dynamic Host Configuration Protocol)** process to obtain Layer 3 network configuration.

---

### 🔁 DHCP Exchange & Network Info

| **DHCP Step**         | **Who Sends It**         | **Message Type**       | **Purpose**                                                                 |
|-----------------------|---------------------------|-------------------------|------------------------------------------------------------------------------|
| **1. DHCP Discover**  | 📱 Your device             | 🔊 Broadcast            | "Is there a DHCP server? I need an IP address!"                            |
| **2. DHCP Offer**     | 📡 Router/AP               | 📢 Unicast/Broadcast    | "Here’s an IP config you can use!"                                         |
|                       |                           |                         | → Offers: IP address, subnet mask, gateway, DNS                            |
| **3. DHCP Request**   | 📱 Your device             | 🔊 Broadcast            | "Yes, I accept this configuration. Please assign it to me."                |
| **4. DHCP ACK**       | 📡 Router/AP               | 📩 Unicast              | "Confirmed! The IP and network settings are now officially assigned to you."|

---

### 📦 Network Info Received in DHCP Offer & ACK

| **Network Info**        | **Example**              | **Received In**         | **Purpose**                                              |
|-------------------------|--------------------------|--------------------------|----------------------------------------------------------|
| **IP Address**          | `192.168.0.101`           | 📩 DHCP Offer & ACK      | Identifies your device on the local network              |
| **Subnet Mask**         | `255.255.255.0`           | 📩 DHCP Offer & ACK      | Defines which IPs are in the same network                |
| **Default Gateway**     | `192.168.0.1`             | 📩 DHCP Offer & ACK      | Where to send traffic destined for the internet          |
| **DNS Server**          | `8.8.8.8` or router IP    | 📩 DHCP Offer & ACK      | Resolves domain names like `google.com` to IP addresses  |

---

### ✅ Final Summary

- DHCP is part of the **Layer 3 setup** after the device joins Wi-Fi at Layer 2.
- It gives your device everything it needs to **communicate beyond the local network**.
- Without DHCP, you'd need to configure all these values **manually** (static IP).

> 🧠 DHCP is the bridge between being connected to Wi-Fi and actually accessing the internet.

## 📡 Wi-Fi MAC Frame Format (802.11)

| **Field** | **Duration** | **Address 1** | **Address 2** | **Address 3** | **Seq Ctrl** | **Address 4** | **Frame Body** | **FCS** |
|-----------|--------------|---------------|---------------|---------------|---------------|----------------|----------------|----------|
| FC (2 B)  | Duration (2 B) | 6 bytes      | 6 bytes       | 6 bytes       | 2 bytes       | 6 bytes        | 0–2312 bytes   | 4 bytes  |

> **Total Size:** Variable (typically 28–2346 bytes depending on payload)




### 🧩 Frame Control Field Structure (2 bytes = 16 bits)
it consists of various bits Namely
| **Subfield**             | **Size** |
|--------------------------|----------|
| Protocol Version         | 2 bits   |
| Type                     | 2 bits   |
| Subtype                  | 4 bits   |
| To DS                    | 1 bit    |
| From DS                  | 1 bit    |
| More Fragments           | 1 bit    |
| Retry                    | 1 bit    |
| Power Management         | 1 bit    |
| More Data                | 1 bit    |
| WEP (Encryption Enabled) | 1 bit    |
| Order                    | 1 bit    |

> 🧪 This field defines the **type, control, and behavior** of the 802.11 frame.

## 🧾 IEEE 802.11 Frame Types and Subtypes

Each 802.11 frame has a **Frame Type** field (2 bits) and a **Subtype** field (4 bits) inside the **Frame Control (FC)** field.
These determine **what kind of frame it is** and **what it's used for**.
### Frame Types:
Frame type is subdivided into
1. **Management Frames**
2. **Control Frames**
3. **Data Frames**

Sub type helps specify the exact frametype(Probe,RTS etc..)

---

### 📊 Frame Types & Subtypes Table

| **Frame Type**       | **Type Value** | **Common Subtypes**                          | **Usage**                                         |
|----------------------|----------------|-----------------------------------------------|--------------------------------------------------|
| **Management**       | `00`           | - Association Request<br>- Association Response<br>- Probe Request<br>- Probe Response<br>- Beacon<br>- Authentication<br>- Deauthentication | Used to **establish, manage, and terminate** Wi-Fi connections |
| **Control**          | `01`           | - RTS (Request to Send)<br>- CTS (Clear to Send)<br>- ACK (Acknowledgment)<br>- PS-Poll | Assists with **medium access control**, power saving, and reliability |
| **Data**             | `10`           | - Data<br>- QoS Data<br>- Null Function<br>- CF-Ack | Carries **actual payload** (e.g., IP packets, ARP, DNS, etc.) |
| **Reserved**         | `11`           | - N/A                                          | Reserved for future use by IEEE                  |

---

### 🧠 Key Concepts

- The **Frame Type** tells us the category (Mgmt, Control, Data).
- The **Subtype** field (4 bits) tells us **exactly what kind of frame** it is within that category.
- These values are found inside the **Frame Control field** of every 802.11 frame.

> 🔍 Example:  
> A **Beacon Frame** has Frame Type = `00` (Management), Subtype = `1000` (Beacon)

---


### Other Fields:

- **Duration**: The duration bit specify  time interval we want to occupy the channel.
- **Sequence Control (SC)**: Used for Synchronization
- **FCS**: Frame Check Sequence is used for are checking probably (CRC32)
---
To DS( a packet going to distributed system) & from DS  (a packet coming from distributed system) are Wired lan address 1 to address 4
## 🧭 Addressing in Wi-Fi

| Address | Purpose                        |
|---------|--------------------------------|
| Addr1   | Next Destination               |
| Addr2   | Previous Sender                |
| Addr3   | Final Destination              |
| Addr4   | Original Source (if needed)    |

> 🔹 If `To DS = 0` and `From DS = 0` → Direct station-to-station communication.

**More frag** (More fragments): It is 1 bit long field which when set to 1 means frame is followed by other fragments.
**Order**: It is 1 bit long field, if this bit is set to 1 the received frames must be processed in strict order.
**retry**:it is 1-bit long field, if the current frame is a retransmission of an earlier frame.
**power mgmt**:If the field is set to 1, station goes into power-save mode. If the field is set to 0, the station stays active.

---

## ⚙️ Physical Layer and Modulation Schemes

### Based on encoding, speed, and range:

- **802.11a**: 5.75 GHz, OFDM, PSK, 6–54 Mbps
- **802.11b**: 2.44 GHz, DSSS, PSK, 5.5–11 Mbps
- **802.11g**: 2.4 GHz, OFDM, 54 Mbps
- **802.11n**: 2.4/5 GHz,64-QAM,600 Mbps

> 💡 Wi-Fi uses unlicensed **ISM bands**.

---
## 📡 Beacon Frames in Wi-Fi

Beacon frames are **broadcast management frames** sent periodically by Access Points (APs) to announce the presence of a Wi-Fi network.

---

### 🧭 Purpose of Beacon Frames

| **Function**                   | **Description**                                                                 |
|-------------------------------|---------------------------------------------------------------------------------|
| **Announce the network**      | AP advertises its SSID (network name)                                          |
| **Synchronization**           | Helps client devices sync their internal clocks with the AP's timestamp        |
| **Transmit network parameters** | Includes channel, supported data rates, security info, etc.                    |
| **Power saving support**      | Contains **TIM (Traffic Indication Map)** to help sleeping clients know if data is buffered for them |

---
## 🧱 Beacon Frame Structure (Expanded)

| **Field**                              | **Purpose**                                                              |
|---------------------------------------|---------------------------------------------------------------------------|
| **Timestamp**                         | Syncs client clock with AP                                               |
| **Beacon Interval**                   | Interval between beacons (in TUs)                                        |
| **Capability Info**                   | Flags: ESS, Privacy (WEP/WPA), IBSS, etc.                                |
| **SSID**                              | Network name (may be null for hidden networks)                           |
| **Supported Rates**                   | Data rates supported by AP                                               |
| **DS Parameter Set**                  | Includes **current channel** (e.g., 6, 11, etc.)                          |
| **TIM (Traffic Indication Map)**      | Shows if AP has buffered data for sleeping clients                       |
| **WMM Parameter Element** *(optional)*| **QoS settings** for Voice, Video, Best Effort, Background queues        |
| **RSN Information (Security)**        | Info about WPA2/WPA3 authentication and encryption                       |
| **Vendor-Specific IEs**               | Optional extensions like 802.11k/v/r, roaming hints, etc.                |

**DS Parameter Set** = Just the channel number — tells clients what RF channel the AP is using.

**QoS Info** is included only if AP supports WMM, and it appears in the WMM Parameter Element inside the optional IEs section of the beacon frame.
Tag: WMM Parameter Element (WME)
  - QoS Info (U-APSD support, queue settings)
  - Access Categories: Voice, Video, Best Effort, Background



### ⏱️ Beacon Interval

- Defined in **time units (TUs)** — 1 TU = **1024 microseconds**
- Default interval: **100 TUs** → ~102.4 ms (approx. 10 beacons/sec)

---

### 📶 Beacon Frame Properties

| **Property**           | **Value**               |
|------------------------|-------------------------|
| **Frame Type/Subtype** | Management / Subtype 8  |
| **Transmission Mode**  | Broadcast (to all clients) |
| **Reliability**        | Not ACKed (unreliable delivery) |
| **Frequency**          | Sent on primary channel only |
| **Encryption**         | Never encrypted         |

---

### 🔍 Real-World Use Cases

- Wi-Fi scanners (e.g., in phones or `Wireshark`) **rely on beacon frames** to detect nearby SSIDs.
- Beacons are **always sent**, even if the SSID is "hidden" (though in that case, SSID field is null).
- Client devices use the **timestamp and interval** to sync their sleep/wake schedules (important for power saving).

---

### ⚠️ Security Note

- Beacon frames **advertise the presence of a network**, so:
  - Hidden SSIDs don't offer real security — they just omit the SSID name
  - Attackers can still detect networks based on beacon frame traffic

---

## ✅ Summary

| **Why Beacons Matter** |
|------------------------|
| 📡 They announce the Wi-Fi network to nearby devices |
| 🕒 Help clients stay synchronized and manage power |
| 🔑 Carry critical info like supported rates, channel, and security |
| 🧭 Clients scan and connect based on beacon frame contents |

> 💡 Without beacon frames, Wi-Fi devices wouldn’t even know which networks exist — they're like digital lighthouses!

## 🚶‍♂️ Fast & Smart Roaming in Wi-Fi: 802.11k / v / r

When you're moving around (like walking with your phone), Wi-Fi clients need to **switch between APs** — this is called **roaming**. Without optimizations, roaming can be slow or result in dropped packets.

### 📦 Purpose of 802.11k/v/r
| **Standard** | **Focus**         | **Goal**                                |
|--------------|------------------|-----------------------------------------|
| **802.11k**  | Knowledge         | Help clients discover better APs faster |
| **802.11v**  | Direction         | Let APs steer clients toward better APs |
| **802.11r**  | Speed             | Make roaming itself faster (Fast BSS Transition) |

---

## 🔍 802.11k – "Know Before You Roam"

**k = knowledge**

- AP provides a **neighbor report** (a list of nearby APs + their signal strengths, channels, BSSIDs).
- Client uses this to **pre-scan** and decide **where to roam next**.
- Reduces delay because the client **doesn't have to scan every channel** blindly.

### ✨ Example:
- Your phone asks the AP: “Who else is nearby?”
- The AP replies: “Here are 3 APs with good coverage.”

---

## 🧭 802.11v – "You Should Go Now"

**v = direction / suggestion**

- AP can suggest a better AP for the client to connect to.
- Known as **BSS Transition Management**.
- Used in **load balancing**, weak signal detection, or power-saving modes.

### ✨ Example:
- AP says: “Hey client, your signal is weak. Please roam to AP-2 at -55 dBm.”
- The client may **accept or ignore** the suggestion.

---

## ⚡ 802.11r – "Roam Fast (FT)"

**r = rapid roaming**

- Reduces the **authentication delay** when switching APs.
- Implements **Fast BSS Transition (FT)**.
- Pre-shares cryptographic keys (PMK-R0/R1) between APs.
- So when the client switches, it **doesn’t need full WPA2 handshake** again.

### ✨ Example:
- Without 802.11r: Roaming takes 300+ ms → noticeable lag (VoIP, gaming)
- With 802.11r: Roaming in ~50 ms → smooth handoff

---

## 📶 Summary Table

| **Feature** | **802.11k**              | **802.11v**                  | **802.11r**                          |
|-------------|---------------------------|-------------------------------|--------------------------------------|
| **Goal**    | AP Discovery               | Roaming Decision Assistance   | Fast Authentication Handoff         |
| **Main Idea**| Get neighbor list         | AP recommends better BSS      | Pre-authenticate before roaming      |
| **Client Control?** | Yes               | Yes                           | Yes                                  |
| **Improves** | Scan time, battery life   | Load balancing, performance   | Handoff speed for real-time traffic  |
| **Best Use Case** | Large campus Wi-Fi   | Mesh / enterprise networks    | VoIP, video calls, low-latency apps  |

---

## ✅ Real World Analogy

> Imagine you're moving between conference rooms in a building with many Wi-Fi hotspots:

- 🧠 **802.11k** gives you a **map** of other nearby access points.
- 🧭 **802.11v** acts like a **guide**, telling you which door to take next.
- ⚡ **802.11r** gives you a **VIP pass**, letting you skip the security line when you arrive.

---

## 🛠️ How to Use These?

- Supported only if **both AP and client device** support these standards.
- Most modern enterprise APs (e.g., Cisco, Aruba, UniFi) support them.
- Most modern phones/laptops support **k/v**, and many also support **r**.
- Configuration is typically done in the **Wi-Fi controller / AP settings**.



# 🔗 Fragmentation & Aggregation in Wi-Fi

In Wi-Fi, **performance** and **reliability** are affected by how data is packaged and transmitted. Two techniques that help optimize wireless communication are:

- **Fragmentation** – Breaking data into smaller pieces.
- **Aggregation** – Combining multiple data packets into one.

---

## ✂️ Fragmentation in Wi-Fi

### 📍 What is it?

**Fragmentation** divides a large data frame into smaller parts (fragments) before transmission.

### 💡 Why it’s used:

- To **reduce retransmission time** if a packet is lost or corrupted.
- Smaller fragments have a **higher chance of successful delivery**, especially in noisy environments.

### 🧠 How it works:

1. A large data frame is split into smaller fragments.
2. Each fragment is sent with its own **header** and **checksum**.
3. Only the **lost or corrupted fragment** needs to be retransmitted.

### ✅ Benefits:

- **Improved reliability** in environments with high interference.
- **Faster recovery** from transmission errors.

### ❌ Drawbacks:

- **More overhead** due to extra headers.
- Can **reduce throughput** if not managed properly.

---

## 📦 Aggregation in Wi-Fi

### 📍 What is it?

**Aggregation** combines multiple data packets into a **single larger frame** before transmission.

> Introduced in **802.11n (Wi-Fi 4)** and enhanced in **Wi-Fi 5/6**, aggregation improves **efficiency**.

### 🧠 Types of Aggregation:

| **Type**    | **Full Name**                        | **Description**                                              |
|-------------|---------------------------------------|--------------------------------------------------------------|
| **A-MSDU**  | Aggregated MAC Service Data Unit     | Combines multiple data units at the **higher MAC layer**     |
| **A-MPDU**  | Aggregated MAC Protocol Data Unit    | Combines multiple MPDUs at the **lower MAC layer**           |

### ✅ Benefits:

- **Less overhead** (fewer headers per packet)
- **Higher throughput** and **better efficiency**
- Especially useful in **high-speed** or **low-error** environments

### ❌ Drawbacks:

- If one part of an aggregated frame is corrupted, **entire frame may need retransmission**
- **Delay-sensitive** applications may suffer due to buffering before aggregation

---
# 🧱 MPDU vs MSDU in Wi-Fi

In Wi-Fi communication, data flows through several layers. Two key units involved in packaging and transmitting this data are:

- **MSDU (MAC Service Data Unit)**
- **MPDU (MAC Protocol Data Unit)**

Understanding the difference between them helps in grasping how Wi-Fi handles data efficiency, error control, and speed.

---

## 📦 What is MSDU?

### ➕ Full Form:
**MAC Service Data Unit**

### 📍 Description:
An **MSDU** is a data packet received from the **upper layers** (like IP or TCP) and handed off to the **MAC layer** for transmission.

### 🔄 Example:
Think of it as a **customer's order** that needs to be packed before shipping.

### ✅ Key Points:

- Contains actual **payload** (user data)
- Sits at the **interface between Layer 2 and Layer 3** (Data Link ↔ Network)
- Before transmission, it's usually **converted into MPDU**

---

## 📡 What is MPDU?

### ➕ Full Form:
**MAC Protocol Data Unit**

### 📍 Description:
An **MPDU** is the **final packet** that is transmitted over the air by the Wi-Fi interface.

### 🔄 Example:
Think of it as the **shipping box** that actually leaves the warehouse.

### ✅ Key Points:

- Includes **MAC header**, **frame check sequence (FCS)**, and **possibly one or more MSDUs**
- It’s what actually gets **transmitted on the wireless medium**
- Can be aggregated (A-MPDU) for performance

---

## ⚙️ Flow of Data: From MSDU to MPDU

```text
App/Data → TCP/UDP → IP Packet → MSDU → MPDU → Wireless Transmission
```
## ⚖️ Fragmentation vs Aggregation

|                | **Fragmentation**                          | **Aggregation**                             |
|----------------|---------------------------------------------|----------------------------------------------|
| **Purpose**     | Increase reliability                        | Improve efficiency and speed                 |
| **Use Case**    | Noisy environments, weak signals            | Clean environments, high-speed transmissions |
| **Overhead**    | High (more headers, more frames)            | Low (shared headers across packets)          |
| **Throughput**  | Can reduce throughput                       | Increases throughput                         |
| **Introduced In**| Legacy Wi-Fi (before 802.11n)              | 802.11n and later (Wi-Fi 4, 5, 6)            |

---

## 🏠 Real-World Analogy

### Fragmentation:
> Like sending multiple **smaller envelopes** instead of one big package when mailing fragile items — fewer chances of complete loss.

### Aggregation:
> Like putting several letters into a **single large envelope** to save on postage and time — more efficient, unless the envelope gets damaged.

---

## 🧠 Final Summary

- **Fragmentation** helps improve **reliability** by reducing the size of each transmission.
- **Aggregation** improves **efficiency** and **speed** by sending more data in fewer transmissions.
- **Modern Wi-Fi** standards use both smartly, depending on signal quality, traffic type, and device capability.

> 🚀 Efficient data handling = Faster Wi-Fi + Fewer errors!



# 🔋 Power Management in Wi-Fi

Wi-Fi devices (like phones, laptops, and IoT devices) often run on batteries. To **extend battery life**, Wi-Fi includes smart **power-saving mechanisms**.

---

## 🧠 Why Power Management Matters

- 🪫 Devices are **often idle** between data transmissions.
- ⚡ Wireless radios consume **significant power** when active.
- 💡 Power management allows devices to **sleep intelligently** without losing connectivity.

---

## ⚙️ How Power Management Works in Wi-Fi

Wi-Fi power-saving is based on a **client–AP (Access Point)** relationship.

### 🧱 Key Concepts:

| **Term**             | **Meaning**                                                                 |
|----------------------|------------------------------------------------------------------------------|
| **Sleep Mode**       | Client turns off its radio to save power                                     |
| **Listen Interval**  | Tells the AP how often the client wakes up to check for data                 |
| **Traffic Indication Map (TIM)** | Bitmap in beacon frames that indicates if AP has data for sleeping clients  |
| **Beacon Frame**     | Periodic signal from AP that includes the TIM and other control info         |
| **PS-Poll**          | Power Save Poll — client uses this to request queued data from AP            |

---

## 📶 Power Save Mechanism – Step by Step

1. **Client enters Power Save mode** and informs the AP.
2. AP **buffers data** for that client.
3. Client **wakes up periodically** based on the *Listen Interval*.
4. AP sends a **Beacon** with a TIM indicating buffered data.
5. Client sends a **PS-Poll** or triggers download to receive data.
6. After receiving, the client may **go back to sleep**.


## 🔋 Power Saving Mode (Legacy PS Mode only)

- Client sends a **null data frame** with the **Power Management bit set** to indicate it's entering sleep mode.
- The **Access Point (AP)** buffers any incoming data for the client while it’s asleep.
- AP includes a **TIM (Traffic Indication Map)** in its periodic **beacon frames**, signaling which clients have buffered data.
- When the client wakes up and sees its ID in the TIM, it sends a **PS-Poll** frame to request the buffered data from the AP.

---

## 💡 Types of Wi-Fi Power Saving Techniques

### 1. 💤 Legacy Power Save Mode

- Defined in early Wi-Fi standards.
- Based on **PS-Poll** mechanism and **beacon-based** listening.
- Still widely supported, but **not optimal** for modern use.

---

### 2. 🚀 WMM Power Save (U-APSD)

> **WMM = Wi-Fi Multimedia**  
> **U-APSD = Unscheduled Automatic Power Save Delivery**

**WMM Power Save**, also known as **Unscheduled Automatic Power Save Delivery (U-APSD)**, is an enhanced power-saving mechanism introduced with **Wi-Fi Multimedia (WMM)**.

- Introduced to support **VoIP** and **real-time multimedia**.
- More **efficient** than legacy methods.
- Client tells AP when it’s ready, and AP **pushes** buffered packets.

### ⚙️ How It Works

- The client (STA) enters power-save mode.
- Instead of sending **PS-Poll** frames, the client sends a **trigger frame** (like a QoS data or null frame).
- The AP, upon receiving the trigger, delivers **all buffered packets** for that Access Category (AC).
- After delivery, the client may go back to sleep.

---

### 3. 📡 Target Wake Time (TWT) – Wi-Fi 6 (802.11ax) and Beyond

- AP and client **negotiate scheduled communication windows** to avoid unnecessary radio activity. 
- Great for **IoT devices** and **smart homes**.
- Dramatically reduces **power consumption** by avoiding unnecessary wakeups.

---
### ⚙️ How It Works

1. Client and AP agree on a **TWT schedule** — e.g., wake every 100ms.
2. Outside of the agreed window, the client **sleeps**.
3. At the TWT time, both AP and client **wake up and exchange data**.
4. The client goes back to sleep until the next window.

### 📋 Key Features

| Feature                   | Description                                                  |
|---------------------------|--------------------------------------------------------------|
| **Trigger-based**         | Client initiates delivery by sending a frame                 |
| **Low latency**           | Better for voice/video since delivery is immediate           |
| **Efficient**             | Reduces need for constant polling or waking                  |
| **AC-specific**           | Buffers and delivers data per Access Category (voice, video) |

### 🧠 Real-World Analogy

> Like telling the receptionist: “I’m ready now, give me **all my messages** at once.”  
> You don’t have to keep asking — just one signal, and you get everything.
---

## ⚖️ Power Save Modes – Summary Comparison

| Feature               | Legacy Power Save         | WMM Power Save (U-APSD)            | TWT (Wi-Fi 6+)                        |
|------------------------|---------------------------|-------------------------------------|---------------------------------------|
| **Wake Trigger**       | TIM + PS-Poll              | Trigger Frame (QoS Null/Data)       | Pre-scheduled wake times              |
| **Best For**           | General traffic            | Voice, Video                        | IoT, battery-powered smart devices    |
| **Latency**            | Medium                     | Low                                 | Very Low (scheduled)                  |
| **Power Efficiency**   | Moderate                   | High                                | Very High                             |
| **Standard**           | 802.11a/b/g/n              | 802.11e (WMM)                       | 802.11ax (Wi-Fi 6 and later)          |
| **Mechanism**       | Beacon + PS-Poll            | Client-triggered AP delivery  | Scheduled wake/sleep windows      |

---
## 🧠 Real-World Analogy

> Imagine a student (device) who doesn’t stay in the classroom (network) all the time:

- 💤 **Legacy Mode**: They peek into the room every 10 minutes to see if there’s homework.
- 🚪 **WMM PS**: They notify the teacher when they’re ready, and the teacher gives all the homework at once.
- 🕐 **TWT**: They and the teacher agree on *exact times* to meet. No wasted trips!

---

## ✅ Final Summary

- Wi-Fi uses **smart power-saving** to help mobile and IoT devices conserve energy.
- **Legacy**, **WMM Power Save**, and **TWT** are different techniques depending on device needs and Wi-Fi generation.
- Modern devices leverage **TWT** for scheduled, ultra-efficient communication.

> 🔋 Smart Wi-Fi = Fast Internet + Longer Battery Life

# 💡 CAM (Constantly Awake Mode) in Wi-Fi

## 🔍 What is CAM?

**CAM** stands for **Constantly Awake Mode**. It is the **default power mode** in Wi-Fi where the device's radio is **always on** and actively listening for data or signals from the Access Point (AP).

---

## ⚙️ How CAM Works

In CAM:

- The Wi-Fi radio **never sleeps**.
- The device **immediately processes** all incoming and outgoing data.
- There is **no buffering** of data at the AP — the client is always ready.

---

## ✅ Advantages of CAM

| **Benefit**                  | **Explanation**                                           |
|------------------------------|-----------------------------------------------------------|
| ⚡ Low Latency                | Instant response times; good for real-time applications  |
| 🔁 Immediate Connectivity     | Always ready to send/receive data                        |
| 📶 Reliable Signal Handling   | Better performance in voice, video, or gaming apps       |

---

## ❌ Disadvantages of CAM

| **Drawback**                 | **Explanation**                                           |
|------------------------------|-----------------------------------------------------------|
| 🔋 High Power Consumption     | Constantly running the radio drains the battery faster   |
| 🔥 Not Energy Efficient       | Unsuitable for IoT or battery-powered devices            |

---

## 🧠 Real-World Analogy

> Imagine a **security guard** (your device) who never sleeps, watching the front door **24/7**.  
> They can react instantly — but they'll be **exhausted** and **consume a lot of energy**!

---

## 🔁 CAM vs Power Save Mode – Quick Comparison

| **Feature**           | **CAM (Constantly Awake Mode)** | **Power Save Mode**               |
|------------------------|----------------------------------|-----------------------------------|
| **Radio State**        | Always ON                        | Sleeps when idle                  |
| **Power Usage**        | High                             | Low to Medium                     |
| **Latency**            | Very Low                         | Slight delay (due to wake-ups)    |
| **Best For**           | Video, VoIP, gaming, real-time   | Background apps, IoT, sensors     |

---

## 🔧 When is CAM Used?

- **Laptops and desktops** plugged into power
- **Real-time communication apps** like Zoom or Teams
- **Streaming** or **gaming**
- When **power saving is turned off** in network settings

---

## ✅ Final Summary

- **CAM (Constantly Awake Mode)** keeps the device ready for communication at all times.
- Great for **performance**, not great for **battery life**.
- Choose CAM when **speed and responsiveness** matter more than power savings.

> ⚡ Always awake = always fast, but at a power cost!

---
## 🔀 Band Switching: From 2.4 GHz to 5 GHz in Wi-Fi

Modern dual-band Wi-Fi networks operate on both:

- **2.4 GHz** (longer range, lower speed)
- **5 GHz** (shorter range, higher speed, less interference)

---

### 🧠 Why Switch from 2.4 GHz to 5 GHz?

| **Reason**                  | **Explanation**                                                                 |
|----------------------------|----------------------------------------------------------------------------------|
| 🚀 **Faster Speeds**        | 5 GHz supports higher throughput (e.g., 802.11ac/ax), ideal for streaming, gaming |
| 🤫 **Less Congestion**      | 2.4 GHz is crowded (Bluetooth, microwaves, neighbors), 5 GHz has more channels   |
| 🎯 **Better QoS**           | APs may steer capable clients to 5 GHz for better load balancing                |

---

## 🔄 How Band Switching Happens (Client-Side)

When your device connects to Wi-Fi, here's what can happen:

### 1. **Initial Connection**
- Device scans both 2.4 and 5 GHz.
- If signal strength on 5 GHz is **too weak**, it may connect to **2.4 GHz** first.

### 2. **Monitoring Signal Quality**
- Device continuously monitors **RSSI**, **SNR**, **packet loss**, etc.
- If 5 GHz becomes viable (e.g., you walk closer to AP), it considers switching.

### 3. **Switch Triggered**
- The device **disconnects from 2.4 GHz** and **reassociates with 5 GHz** on same SSID.
- The AP may **assist** using **802.11k/v** to suggest a better band.

---

## 📡 AP-Assisted Band Steering

Enterprise-grade or mesh APs use **band steering**:

| **Technique**              | **What AP Does**                                                              |
|----------------------------|--------------------------------------------------------------------------------|
| 🔕 **Ignore 2.4 GHz requests** | If client supports 5 GHz, AP may delay or reject 2.4 GHz probes             |
| 🧭 **802.11v BSS Transition** | AP suggests a 5 GHz BSSID via **BSS Transition Request**                   |
| 📊 **Load Balancing**         | AP monitors client count and may steer clients for better performance       |

> 🧠 Band steering is more like **“client suggestion”** — clients make the final roaming decision.

---

## 📶 Technical Example: iPhone Switches from 2.4 → 5 GHz

1. Initially connects to 2.4 GHz due to strong signal at range
2. As user moves closer, iPhone receives 5 GHz **beacon frames** with good RSSI
3. AP may send **802.11v BSS Transition Request** to 5 GHz BSSID
4. iPhone disconnects from 2.4 GHz and reassociates to 5 GHz using:
   - **Same SSID**
   - New **BSSID** on a 5 GHz channel
5. **DHCP is not redone** (same L3 settings usually retained)

---

## 🛠️ Troubleshooting Tip

| **Symptom**                       | **Possible Cause**                        | **Fix**                          |
|----------------------------------|-------------------------------------------|----------------------------------|
| Stuck on 2.4 GHz                 | Weak 5 GHz signal or client preference    | Adjust AP power/band steering   |
| Flaky switching                  | Poor AP placement, no roaming support     | Enable 802.11k/v/r on AP        |
| No switch even near AP          | Device roaming aggressiveness is low      | Tweak client-side roaming settings (if possible) |

---

## ✅ Summary: Band Switch Flow

```mermaid

graph TD
A[Device connects on 2.4 GHz] --> B[AP sends 5 GHz beacons]
B --> C[Client sees stronger 5 GHz signal]
C --> D{AP sends BSS Transition (802.11v)?}
D -- Yes --> E[Client roams to 5 GHz]
D -- No --> F[Client may still roam by itself]

```
# 🔍 DFS Scan in Wi-Fi

DFS Scan is a special type of **passive channel scan** that access points (APs) must perform **before** using any **DFS channel** (radar-sensitive) in the 5 GHz band.

---

## ⚙️ What is a DFS Scan?

- Also known as **Channel Availability Check (CAC)**.
- It is a **mandatory listening period** where the AP checks for radar signals **before transmitting** on a DFS channel.
- The AP must stay **completely silent** during this scan.

---

## ⏱️ How Long Does It Take?

| **Region** | **Scan Duration (CAC Time)** |
|------------|------------------------------|
| 🇺🇸 US (FCC) | **60 seconds**               |
| 🇪🇺 EU (ETSI) | **60 – 600 seconds** depending on channel |
| 🌏 Others     | **Usually 60 seconds**       |

> 🛑 During this time, the AP **won’t broadcast SSID** or allow connections on that channel.

---

## 📶 When Does DFS Scan Happen?

### 💡 Scenario 1: Initial Boot or Channel Change
- AP boots up and selects a DFS channel → **must perform DFS scan first**.
- No Wi-Fi service until the scan completes.

### 💡 Scenario 2: DFS Radar Detected
- AP already operating on a DFS channel.
- Radar appears → AP **immediately switches** to a new channel (DFS or non-DFS).
- If new channel is also DFS → another **DFS scan is triggered**.

---

## 🧠 What Happens During DFS Scan?

```mermaid
sequenceDiagram
Client->>AP: Attempt to join network
AP--xClient: No beacon / no SSID broadcast
AP->>Itself: Listen silently for radar (60s)
Note right of AP: DFS scan in progress
AP->>All: Beacon starts on selected channel
Client->>AP: Association begins
```

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

```
# 📚 Key Terms for Beginners

| **Term**         | **Meaning**                                                                 |
|------------------|------------------------------------------------------------------------------|
| **SSID**         | Network name (e.g., *"HomeWiFi"*)                                            |
| **DHCP**         | Automatically assigns an IP address to your device                          |
| **NAT**          | Shares one public IP among multiple private devices                         |
| **IP Address**   | A unique number identifying your device on a network                        |
| **DNS**          | Converts website names (like `google.com`) into IP addresses                |
| **Gateway**      | Routes traffic between your local network and the internet                  |
| **Subnet Mask**  | Defines the network range (usually `255.255.255.0` for home networks)        |
| **ISP**          | Internet Service Provider (e.g., **Jio**, **Airtel**, **BSNL**)              |

---

# 🏠 Real-World Analogy

**Think of your Wi-Fi Access Point like a receptionist at an office:**

- 🧑‍💻 You (*the device*) ask the receptionist for internet access.
- 🪪 The receptionist gives you an **ID badge** (*IP address*).
- 📤 When you send a letter (*data*), the receptionist logs your name and sends it out.
- 📥 When mail comes back (*a reply*), the receptionist knows it's for you and hands it over.

---

# ✅ Final Summary

📶 Your **device** connects to the **Access Point (AP)** via **Wi-Fi**.

- The **AP/router** assigns your device an IP address using **DHCP**.
- Your device sends **data to the internet**, and the AP handles the forwarding.
- The AP uses **NAT** to allow multiple devices to **share one internet connection**.
- Incoming data is routed **back to the correct device** using the IP address.

---

# 📡 The AP is your **wireless gateway** to the digital world!


# 📡 Ad-Hoc & Wi-Fi Direct (P2P) Operation - Deep Technical Dive

This guide explores two decentralized wireless networking models:

* **Ad-Hoc Mode** (IBSS - Independent Basic Service Set)
* **Wi-Fi Direct** (P2P - Peer-to-Peer Mode)

---

## 🧩 1. Ad-Hoc Mode (IBSS)

### 🔍 Concept

Ad-Hoc mode allows Wi-Fi-capable devices to communicate directly without an access point (AP). It's useful for simple, short-term or mesh-like wireless networks.

### ⚙️ Technical Characteristics

- **No Access Point**: Fully peer-to-peer.
- **Shared SSID**: All devices use the same SSID and channel.
- **Randomized BSSID**: Typically the MAC address of the initiating node.
- **Beaconing**: All nodes may send beacon frames; one acts as a timing master.
- **Frame Addressing**:
  - `To DS = 0`, `From DS = 0`
  - `Address1 = Destination`, `Address2 = Source`, `Address3 = BSSID`

### 🔄 Formation Process

1. One device creates an IBSS with an SSID and channel.
2. Others scan and join by matching SSID and channel.
3. Synchronization and periodic beaconing occur.

### ⚠️ Limitations

- ❌ No QoS
- ❌ No security enforcement (encryption optional)
- ❌ Poor power management
- ⚠️ Poor scalability; not suitable for complex networks
- ⚠️ Largely deprecated in modern OSes

---

## 🔁 2. Wi-Fi Direct (P2P)

### 🧠 Concept

Wi-Fi Direct enables devices to create a network **without an AP**, using the full 802.11 stack with enhanced features like security, power saving, and service discovery. A device assumes the role of a **Group Owner (GO)** and acts as a soft AP.

---

## 🏗️ Architecture Overview

### 👥 Entities

| Component       | Description                          |
| --------------- | ------------------------------------ |
| P2P Device      | Wi-Fi Direct capable device          |
| P2P Group       | Logical group formed for communication |
| Group Owner (GO)| Acts like a soft AP                  |
| P2P Client      | Joins the GO to access services/data |
| Persistent Group| Remembers credentials for rejoining |

---

## 🧭 Group Formation Phases

### 1. 📡 Device Discovery

- Devices scan on **social channels (1, 6, 11)**.
- Exchange **Probe Requests/Responses** with **P2P IE** fields.

### 2. 🤝 GO Negotiation

- Devices send a **GO Negotiation Request**.
- Exchange **GO Intent Value (0–15)**.
- Higher intent becomes GO.
- If tied, tie-breaker bit is used.

### 3. 🔐 Provisioning

- Devices use **Wi-Fi Protected Setup (WPS)**:
  - Push Button Method (PBC)
  - PIN Method

### 4. 📶 Group Formation

- GO starts beaconing (`SSID="DIRECT-XXXX"`)
- Client performs a WPA2 4-way handshake.
- Devices now communicate like STA <-> AP.

### 5. 🔁 Persistent Groups

- Devices store credentials and roles.
- Reconnect later without repeating GO negotiation.

### 6. ⚙️ Autonomous GO

- A device **pre-configures itself as GO**.
- Starts beaconing immediately.
- Allows other devices to join without negotiation.

---

## 🌐 Operation After Formation

| Layer       | Behavior                                                                 |
| ----------- | ------------------------------------------------------------------------ |
| MAC/PHY     | GO sends beacon frames, clients behave like STA                          |
| Security    | WPA2-PSK or WPA3-SAE + 4-way handshake                                   |
| IP Layer    | GO acts as **DHCP server** (or uses APIPA)                               |
| Power Mgmt  | Supports **Notice of Absence (NoA)** and client power-saving mechanisms |
| Service Disc| Uses **Bonjour, UPnP, DNS-SD**                                           |

---

## 🗂️ Comparison Table

| Feature                 | Ad-Hoc (IBSS)     | Wi-Fi Direct (P2P)       |
|------------------------|------------------|--------------------------|
| Central Control         | ❌ None           | ✅ GO as soft AP          |
| Security                | ❌ Optional       | ✅ WPA2/WPA3               |
| Power Management        | ❌ Poor           | ✅ NoA, P2P PS             |
| Discovery               | ❌ Manual         | ✅ Standardized            |
| Persistent Groups       | ❌ Not supported  | ✅ Auto reconnect          |
| Service Discovery       | ❌ No             | ✅ Bonjour, UPnP, mDNS     |
| MAC Header Format       | IBSS style        | Infrastructure style      |
| IP Assignment           | ❌ Manual/Static  | ✅ DHCP/APIPA              |
| OS Support              | ⚠️ Deprecated     | ✅ Widely supported        |
| Internet Sharing        | ❌ Manual NAT     | ✅ GO shares via NAT       |
| Multi-hop Support       | ❌ Not supported  | ⚠️ Limited                 |

---

## 🧪 Use Cases

### Ad-Hoc (IBSS)

- Quick file sharing (legacy devices)
- Sensor networks
- Military/field communications
- Offline, infrastructure-less networking

### Wi-Fi Direct (P2P)

- Android Nearby Share, AirDrop-style transfers
- Wi-Fi printing (printer is GO)
- Wireless displays (Miracast)
- IoT provisioning
- Game console linking

---

## 🔍 Wi-Fi P2P Group Formation - Sequence Diagram

```mermaid
sequenceDiagram
    participant DeviceA as Device A
    participant DeviceB as Device B
    participant GO as Group Owner
    
    DeviceA->>DeviceB: Probe Request (P2P IE)
    DeviceB-->>DeviceA: Probe Response (P2P IE)
    
    DeviceA->>DeviceB: GO Negotiation Request (Intent=7)
    DeviceB-->>DeviceA: GO Negotiation Response (Intent=10)
    DeviceA->>DeviceB: GO Negotiation Confirmation
    
    note over DeviceB, GO: Device B becomes Group Owner (GO)
    
    GO->>DeviceA: Beacon (SSID, P2P Group Info)
    DeviceA->>GO: WPS Authentication (PIN/PBC)
    GO->>DeviceA: WPA2 4-Way Handshake
    GO->>DeviceA: DHCP Offer (IP Address)
    DeviceA->>GO: Join Group (Ready)
```

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

# 📡 Advanced Wi-Fi MAC/PHY Topics: OFDMA, TSPEC, MLO (802.11be)

---

## 🔬 OFDMA Scheduling Internals (802.11ax)

### 🧠 Concept

OFDMA = Orthogonal Frequency Division Multiple Access. Introduced in Wi-Fi 6 to allow **multiple clients to share a single channel simultaneously**.

### 📐 Resource Units (RUs)

* Channel is divided into **Resource Units** (RUs)
* AP assigns RUs to clients

  * Smallest RU = 26-tone
  * Largest RU = 996-tone (entire 80 MHz channel)

### 🗂️ Scheduler Logic

The AP’s MAC layer scheduler dynamically:

* Monitors **Buffer Status Reports (BSR)**
* Accounts for **QoS** levels (voice, video, etc.)
* Uses **Channel State Information (CSI)** to optimize throughput
* Sends **Trigger Frames** to initiate uplink OFDMA

### 🧱 OFDMA Downlink Frame Structure

* Preamble

  * Common + User-specific
* Data: RUs interleaved for different clients

### 📶 Trigger-Based Uplink

1. AP sends **Trigger Frame**
2. STAs respond with **OFDMA-scheduled data** on assigned RUs
3. Enables synchronized, low-latency access

### 🛠️ Benefits

* Spectral efficiency
* Reduced latency
* Scalable IoT performance

---

## 🎯 TSPEC Negotiation (WMM Admission Control)

### 🔁 Process

1. STA sends **ADDTS Request** with TSPEC IE (via Action Frame)
2. AP evaluates and replies with **ADDTS Response** (Accept or Reject)

### 🧾 TSPEC IE Fields

* **Traffic Type** (e.g., Voice)
* **Nominal MSDU Size**
* **Mean Data Rate**
* **Minimum PHY Rate**
* **Delay Bound**
* **Surplus Bandwidth Allowance**

### ⚖️ Admission Control Decision

* AP uses **ACM (Admission Control Mandatory)** flags
* Checks **available bandwidth** and **QoS policy**
* May reject if traffic cannot be guaranteed

### 🧪 Use Case: Voice over Wi-Fi

* Voice STA uses AC\_VO
* Sends ADDTS for \~64 Kbps traffic
* Low delay bound (e.g., < 50ms)

### 🔍 Frame View (Wireshark)

* Frame Type: Action
* Category: QoS
* Element ID: TSPEC (221)

---

## 🚀 Multi-Link Operation (MLO) in Wi-Fi 7 (802.11be)

### 🌐 Motivation

* Combine multiple frequency bands and links for **ultra-high throughput** and **reliability**

### 🔗 Types of MLO

1. **STR-MLO**: Simultaneous Tx/Rx
2. **Non-STR-MLO**: Alternating link usage
3. **Link Aggregation**: Data split across links
4. **Link Redundancy**: Same data sent over multiple links

### 🧠 MAC Coordination

* **Single MLD (Multi-Link Device)** entity at MAC layer
* Each link has a **Link Context**
* Shared queues and session state

### ⚙️ Frame Structure

* MLO-specific fields in MAC header
* Extended sequence numbers per link
* Shared Block Ack sessions

### 📚 Reordering Logic

* Reorder buffers per link
* Maintain in-order delivery
* Handles lost/misaligned frames independently

### 🚦 Traffic Steering

* Based on:

  * Link quality (SNR)
  * Congestion
  * Power efficiency (battery-aware clients)

---

## 🧱 Summary Table

| Feature | Wi-Fi 6 (ax)   | Wi-Fi 7 (be)  |
| ------- | -------------- | ------------- |
| OFDMA   | ✅ UL+DL        | ✅ Enhanced    |
| MU-MIMO | ✅              | ✅ 16x16 DL+UL |
| MLO     | ❌              | ✅             |
| TSPEC   | ✅              | ✅             |
| QoS AC  | VO, VI, BE, BK | Same          |

---



# 🧠 Wi-Fi Advanced Deep Dive: MLO, TSPEC, Drivers, and Future Standards

---

## 🔍 Real MLO + TSPEC Frame Captures (Wireshark)

### 🧪 Multi-Link Operation (MLO) in Action

* **Multi-Link frames** are embedded with:

  * **Link ID subfields** in the MAC header
  * **Link-specific Block Ack (BA) frames**
* **A-MPDU** is split and mapped across links
* Use **"Radiotap" headers** in Wireshark to inspect:

  * Band/frequency
  * MCS/NSS per link
  * Frame Reordering

### 📜 TSPEC Frame Capture Breakdown

* **ADDTS Request** Frame:

  * Frame Type: Action
  * Category: Spectrum Management
  * Action Code: ADDTS Request (0x00)
  * Includes TSPEC IE with QoS details
* **ADDTS Response**:

  * Admission Accepted/Denied
  * Reason Code (if rejected)

### 🧰 Wireshark Filters

* `wlan.fc.type_subtype == 0x00` → Management frames
* `wlan.qos.tspec.*` → Specific TSPEC IE fields
* `radiotap.mcs` → MCS index
* `wlan_mlo.*` → Fields (in recent Wireshark builds)

---

## 🧬 Linux Wi-Fi Driver Internals: mac80211, cfg80211, and Firmware Flow

### 📚 mac80211 (SoftMAC)

* Handles most of the MAC logic in software

* **TX Flow**:

  1. `cfg80211_ops::start_ap()` or `join_ibss()` calls from user space (via `nl80211`)
  2. Calls `ieee80211_ops::start()`
  3. Queues frames → `ieee80211_tx()` → Hardware queues
  4. Handles encryption, A-MPDU, Block ACKs

* **RX Flow**:

  1. Firmware posts frames to kernel via `ieee80211_rx()`
  2. Reordering, defragmentation, decryption (if needed)
  3. Sent up via `cfg80211_rx_mgmt()` or `netif_rx()`

### 🧠 cfg80211

* Acts as bridge between `nl80211` and mac80211
* Exposes kernel control to user space (e.g. wpa\_supplicant, hostapd)

### 🔌 Firmware (iwlwifi / ath10k / esp32)

* Handles:

  * DMA of frames
  * Low-level PHY timing
  * Wake/sleep (TWT)
  * MLO link management (in Wi-Fi 7 chips)
* Communicates with kernel via shared memory or RPC

---

## 📦 ESP32-C3 (TX/RX Concepts from PFIP)

### 🧠 PFIP (Programmable Frame Injection Path)

* Used to send custom Wi-Fi frames or emulate advanced MAC features

### 📡 TX Concepts

* **Raw Frame Injection** via ESP32 Wi-Fi driver
* Examples:

  * 802.11 Beacon or Probe Response
  * Deauthentication, custom Action frames
* Often done via `esp_wifi_80211_tx()`

### 📥 RX Concepts

* **Sniffer Mode (Promiscuous)**:

  * `esp_wifi_set_promiscuous(true)`
  * Capture ALL 802.11 frames
* Useful for monitoring TSPEC requests, control frames, MLO frames (if supported)

### 🛠 PFIP Use Cases

* Emulating OFDMA/BSS Coloring behavior
* Custom QoS scheduling
* Passive capture of roaming/association handshakes

---

## 🛰 Wi-Fi 8 Preview (802.11bn)

### 🚀 What We Know (Draft Stage as of 2025)

* Focus: **Ultra-low latency**, **AI/ML integration**, **massive multi-user support**
* Expected PHY advances:

  * Advanced MIMO topologies (16x16)
  * AI-guided Beamforming
  * Adaptive waveform shaping
* MAC layer goals:

  * **QoS Orchestration** using ML (dynamic priority elevation)
  * **Latency Budgeting** per STA/application
  * Enhanced **TWT++** (more dynamic wake scheduling)

### 📐 Timeline & Compatibility

* Likely finalization by **2028**
* Will operate in **6 GHz+ spectrum**, possibly introducing 7 GHz usage

### 🔮 Vision

* Wi-Fi 8 aims to merge:

  * Real-time edge inference
  * Deterministic latency for robotics/AR/medical
  * Ubiquitous ambient sensing + high-precision localization

---
# 🚀 Final Deep Dive: Target Wake Time (TWT) & IEEE 802.11p

---

## ⏰ Target Wake Time (TWT) — Wi-Fi 6 / 6E / 7 Power Optimization

### 📘 What is TWT?

TWT (Target Wake Time) is a power-saving mechanism introduced in **IEEE 802.11ax (Wi-Fi 6)**. It allows devices (STAs) to **negotiate specific times** with the Access Point (AP) to wake up for transmissions.

This reduces the time the radio stays awake — critical for **IoT, wearables, mobile clients**, and **dense network** scenarios.

---

### ⚙️ How TWT Works

#### 🧩 Types of TWT Agreements

* **Individual TWT**: Specific to a client (STA and AP negotiate directly)
* **Broadcast TWT**: AP schedules a group of STAs to wake at the same time

#### 🗂️ Key Parameters in a TWT Agreement

* **TWT Wake Interval**: How often to wake (in TU — Time Units)
* **TWT Duration**: How long to stay awake after waking
* **TWT Target Time**: Exact wake-up moment (relative to Beacon time)
* **TWT Flow Identifier**: Identifies TWT sessions

---

### 🔄 TWT Negotiation Process

1. **TWT Request Frame** (from STA)
2. **TWT Response Frame** (from AP): Accept/Decline + parameters
3. STA configures its sleep/wake schedule

#### 💡 Implementation Insights

* TWT IE (Information Element) is embedded in **Action Frames**
* Uses **Management Action Frame Category: QoS Management**
* Bit fields indicate negotiation type (Request, Accept, Teardown, etc.)

---

### 📉 Benefits of TWT

* 💤 **Power Efficiency**: Clients sleep for longer intervals
* 📶 **Reduced Contention**: Predictable wake-ups lower airtime contention
* 🔋 **Battery Gains**: Especially for Wi-Fi 6 IoT devices

---

## 🚘 IEEE 802.11p — Wireless Access in Vehicular Environments (WAVE)

### 📘 Overview

802.11p is designed for **Vehicle-to-Vehicle (V2V)** and **Vehicle-to-Infrastructure (V2I)** communication — enabling **DSRC (Dedicated Short-Range Communication)**.

Primarily operates in **5.9 GHz band** with 10 MHz channel widths for reduced delay.

---

### 🚗 Use Cases

* Collision avoidance
* Traffic signal alerts
* Emergency vehicle priority
* Platooning & Cooperative Adaptive Cruise Control (CACC)

---

### ⚙️ PHY/MAC Differences (from 802.11a)

* **OFDM-based** like 802.11a
* **10 MHz channel bandwidth** (vs 20 MHz in 802.11a)
* **No association process** — "connectionless mode"
* **Wildcard BSSID** used (since no AP association)
* **No encryption/authentication** in base spec (safety prioritized over security)

---

### 🔄 Frame Exchange in 802.11p

* Data exchange starts directly using wildcard BSSID
* Beaconing still used for service announcements
* Uses **WAVE Service Advertisements (WSA)** to indicate app-level services

---

### 🧪 Performance Aspects

* Lower PHY rate than 11a (due to 10 MHz)
* Highly tolerant to delay, Doppler shifts
* Designed for **high-mobility scenarios** (>100 km/h)

---

### 🔐 Security Extensions

802.11p alone doesn't define security — usually coupled with:

* **IEEE 1609.2** (security for vehicular messages)
* **PKI-based certificates** for trusted messages

---

### 🛠️ Simulation/Testing Tools

* **NS-3** with `wave` module
* **OMNeT++** + Veins + SUMO for mobility
* Wireshark with DSRC support (some experimental patches)

---

Let me know if you'd like packet traces, NS-3 simulation samples, or want to connect this with future tech like **C-V2X** or **802.11bd** (next-gen vehicular Wi-Fi extension of 802.11p and 802.11ac, designed for backward compatibility and high data rate V2X applications like HD sensor sharing, cooperative driving, and real-time updates) Wi-Fi).


Perfect! Here's the detailed explanation for **IEEE 802.11bd**, extending your `.md` with advanced insights into the evolution from 802.11p. I'll append it in the same clean format right below your 802.11p section:

---

## 🚘 IEEE 802.11bd — Next-Gen V2X (Vehicular Wi-Fi Evolution)

### 📘 What is 802.11bd?

IEEE 802.11bd is the successor to 802.11p, designed to bring **higher data rates, reliability, and backward compatibility** for advanced **V2X (Vehicle-to-Everything)** applications. It enhances the PHY/MAC layers using features from **802.11ac/ax** while maintaining interop with 11p devices.

---

### 🌐 Use Cases (Beyond 802.11p)

* High-definition sensor data sharing (LiDAR, camera)
* Real-time map updates
* Collaborative perception & driving (ADAS, automated driving)
* Intersection coordination, see-through vehicles

---

### 🔁 Key Features & Enhancements

#### 🧬 1. **Backward Compatibility**

* Can operate in **dual-mode**: fall back to 802.11p for older vehicles
* Uses **preamble reuse** to ensure legacy receivers can decode packets

#### 🚀 2. **High Data Rates**

* Utilizes **802.11ac PHY**: wider bandwidths (20/40/80 MHz)
* MIMO support and **higher modulation (up to 256-QAM)**

#### 🧠 3. **Low-Latency & Reliable Scheduling**

* Leverages **QoS features** from Wi-Fi 6 (e.g., TWT, BSS coloring)
* Optional **NR (New Radio)-like** scheduling patterns with short guard intervals

#### 📡 4. **Robustness for Mobility**

* Doppler-tolerant designs
* Adaptive modulation and coding schemes based on speed and signal quality

---

### ⚙️ MAC-Level Improvements

* **Immediate feedback** mechanisms (e.g., fast ACK)
* **HARQ-like retransmissions** (Hybrid Automatic Repeat Request)
* **Sidelink MAC scheduling** for direct vehicle-to-vehicle communication (no AP required)

---

### 🔐 Security Enhancements

* Integrates **IEEE 1609.2.1** for PKI-based message signing and encryption
* Forward-secrecy and anti-replay mechanisms

---

### 🔬 Frame Format Comparison (11p vs 11bd)

| Field        | 802.11p        | 802.11bd                            |
| ------------ | -------------- | ----------------------------------- |
| Bandwidth    | 10 MHz         | 10/20/40/80 MHz                     |
| Modulation   | BPSK/QPSK only | BPSK to 256-QAM                     |
| Coding Rate  | ≤ 1/2          | Up to 5/6 (like 11ac)               |
| MIMO         | Not supported  | Up to 2x2 MIMO                      |
| Feedback     | None           | ACK + Optional HARQ                 |
| PHY Preamble | Unique to 11p  | 11p-compatible preamble (dual-mode) |

---

### 🛠️ Tools and Simulation

* **NS-3 (wave + 11bd extensions)** — available in development branches
* **OMNeT++/Veins** with patches to simulate 802.11bd-style QoS
* **DSRC & 11bd coexistence testing** via SDR platforms (e.g., NI/Ettus USRP)

---

### 🔄 802.11bd vs C-V2X

| Feature          | 802.11bd                         | C-V2X (Rel. 14–16)               |
| ---------------- | -------------------------------- | -------------------------------- |
| Standard Body    | IEEE                             | 3GPP                             |
| MAC Type         | Decentralized                    | Scheduled (via sidelink control) |
| Latency          | <10 ms (typical)                 | <5 ms (ideal)                    |
| Range            | \~1 km                           | \~1.5 km                         |
| Spectrum         | 5.9 GHz                          | 5.9 GHz                          |
| Interoperability | Backward compatible w/ 802.11p   | Not backward compatible          |
| Deployment Model | Open (no SIM/network dependency) | Operator-based (often SIM-bound) |

---

Let me know if you'd like to:

* Visualize the **MIMO+MAC timing** for 802.11bd
* Add **driver/firmware notes** for Linux V2X stacks
* Or build a testbed using **SDR + NS-3 + SUMO**

We’ve now covered the **full modern Wi-Fi & vehicular comms stack** — from energy-saving and QoS to automotive and futuristic V2X tech 🚘📡🚀

