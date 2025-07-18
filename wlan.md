📡 Wireless LAN and IEEE 802.11 Overview
Wireless LAN is a network where devices use wireless protocols/technology to communicate within a defined area.

🌐 IEEE 802.11 Standards
IEEE 802.11 provides standards for wireless LAN covering two primary layers:

Physical Layer

Data Link Layer

🔧 Types of Services in IEEE 802.11
1. BSS (Basic Service Set)
A group/unit of wireless devices communicating with the same Access Point (AP).

BSSID: The AP's MAC address (48-bit hexadecimal).

2. ESS (Extended Service Set)
A network of multiple APs and their associated clients connected via a single Distribution System Medium (DSM).

ESSID: Shared network name across APs.

SSID and ESSID are often used interchangeably.

📶 Access Point (AP)
Devices that accept wireless signals from clients and retransmit them to the wired network.

Acts as a Layer 2 device (bridge).

Also known as a Base Station.

🧩 Ad-Hoc Mode
Without AP (peer-to-peer).

Wireless devices communicate directly.

Decentralized network.

🕵️ Promiscuous Mode (Monitor Mode)
Used to listen to Wi-Fi packets over the air (e.g., sniffers, analyzers).

🧱 IEEE 802.11 Layer Structure
➤ Data Link Layer
Divided into:

Logical Link Control (LLC)

Medium Access Control (MAC)

MAC Sublayers:
DCF (Distributed Coordination Function):

Based on CSMA/CA (Carrier Sense Multiple Access with Collision Avoidance).

Used for wireless (unlike CSMA/CD for wired).

Half-duplex only (can send or receive, not both).

PCF (Point Coordination Function):

Poll-based, priority access mechanism.

🔍 Scanning Process (Joining a Network)
A station scans to associate with an AP.

🔄 Steps:
Send a Probe Frame

Nearby APs respond with Probe Response

Station sends Association Request

AP replies with Association Response

🧭 Types of Scanning
Active Scanning: Station sends probe → AP replies.

Passive Scanning: APs broadcast Beacon Frames regularly.

🚫 CSMA/CA Problems
1. Hidden Terminal Problem
Clients can't detect each other, causing collisions.

Solved using RTS/CTS mechanism.

2. Exposed Terminal Problem
Station avoids transmitting despite the channel being idle.

Also solved using RTS/CTS, if devices are synchronized.

✂️ Fragmentation
Encouraged in noisy channels.

Prevents retransmitting the whole packet on error.

🧾 Frame Format
less
Copy
Edit
FC | Duration | Addr1 | Addr2 | Addr3 | SC | Addr4 | Body | FCS
Frame Control (FC) contains:
Protocol Version

Frame Type (Management, Control, Data)

Subtype

To DS / From DS bits

Addresses:
Addr1: Next destination

Addr2: Previous sender

Addr3: Final destination

Addr4: Original source (used in WDS or mesh)

Other Fields:
SC (Sequence Control): Synchronization

FCS (Frame Check Sequence): CRC32 checking

🧬 Frame Types
1. Management Frames
Probe

Association

Authentication

Beacon

2. Control Frames
RTS (Request to Send)

CTS (Clear to Send)

ACK (Acknowledgement)

3. Data Frames
Carry user payloads

🔐 Beacon Frame Contents
Broadcasted periodically by APs, containing:

SSID

Channel Information

Supported & Required Data Rates

Security Capabilities

QoS Parameters

🌐 IEEE 802.11 Versions (Physical Layer)
Version	Frequency	Modulation	Speed (Max)
802.11a	5.75 GHz	OFDM, PSK	6–54 Mbps
802.11b	2.44 GHz	DSSS, PSK	5.5–11 Mbps
802.11g	2.4 GHz	OFDM	54 Mbps

Wi-Fi operates in the unlicensed ISM band.

🔓 Connection Process (No Encryption)
AP sends a Beacon Frame (broadcast)

Client sends Probe Request (with SSID)

AP responds (if open, no encryption required)

Client sends Authentication Request

AP replies with Authentication Response

Client sends Association Request

AP responds with Association Response

Client can now send a Disassociation Frame to disconnect

💤 Power Saving Mode
Station sends null data frame with PS-Poll bit.

AP buffers data and signals via TIM (Traffic Indication Map).

Station polls when it wakes to retrieve buffered data.

🔐 Four-Way Handshake (WPA2)
Used to establish encrypted data traffic.

Steps:
AP sends ANonce (random number) to station.

Station computes PMK (from password + SSID), generates SNonce, and computes PTK.

Station sends SNonce to AP.

AP computes PTK, generates GTK (Group Temporal Key), and sends it to the station.

Station sends ACK — handshake complete.

🔒 WPA2 Encrypted Connection Process
Client sends Probe Request (includes capabilities)

AP responds with Probe Response (SSID + encryption info)

Client sends Authentication Request

AP replies with Authentication Response

Client is authenticated (but not yet associated)

Client sends Association Request (includes desired encryption)

AP responds with Association Response

If WPA2 is chosen, the Four-Way Handshake occurs for encryption

Note: A station can be authenticated to multiple APs, but associated with only one at a time.
