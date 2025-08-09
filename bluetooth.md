# Bluetooth Classic (BR/EDR) Overview

---

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

---

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

---

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

---

## **Step 4: BR/EDR Link Types**

In Bluetooth Classic, there are **two primary link types**:

| Link Type              | Purpose                                              | Used By                          |
|------------------------|------------------------------------------------------|-----------------------------------|
| **ACL** (Asynchronous Connection-Less) | General, packet-based data transfer          | RFCOMM, OBEX, PAN                 |
| **SCO / eSCO** (Synchronous Connection-Oriented / extended SCO) | Constant bit rate audio streaming | HFP (Hands-Free Profile), HSP     |

---

## **Step 5: Key Terminology**

| Term           | Description |
|----------------|-------------|
| **Device Address (BD_ADDR)** | 48-bit unique hardware identifier for a Bluetooth device |
| **Piconet**    | One *master* device connected to up to 7 *active* slave devices |
| **Inquiry**    | Process of discovering nearby Bluetooth devices |
| **Paging**     | Connecting to a specific known device |
| **Pairing**    | Exchanging link keys for authentication & encryption |
| **Bonding**    | Storing link keys for future reconnection without re-pairing |

---

This breakdown gives you the **functional overview of Bluetooth Classic**, the **stack layers**, how **BlueZ fits in Linux**, and the **link types and terminology** you’ll encounter when working with BR/EDR.
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
# Key Bluetooth Classic Protocol Layers Explained

---

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
  Like an **airport control tower**—the host tells the controller which “flights” (connections) to handle, the controller reports back real-time events.

---

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

---

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

---

## **Layer 4: SDP (Service Discovery Protocol)**

- **Role:**  
  Allows devices to discover which services (profiles/features) are offered by a peer.
- **Location:**  
  Host side.
- **Functions:**  
  - Queries remote devices: “What services do you support?”
  - Retrieves attribute details: UUIDs, supported features, connection parameters, etc.
  - Service discovery is generally required before connecting to most profiles.
- **Analogy:**  
  Like **checking a restaurant’s menu** before placing your order.

---

## **How These Layers Work Together: SPP Example Flow**

**Scenario:** Connecting to a Bluetooth Serial Port Profile (SPP) device.

1. **HCI**
    - Host initiates an Inquiry (scan) via HCI, controller finds nearby devices, host receives BD_ADDR (Bluetooth Device Address).
2. **SDP**
    - Host asks, “Do you support SPP?” via SDP.  
      Remote device replies with corresponding RFCOMM channel number for SPP.
3. **RFCOMM over L2CAP**
    - Host opens an L2CAP channel to peer, negotiates an RFCOMM session over that channel, and establishes the virtual serial link.
4. **Data Flow**
    - Your application writes bytes to an RFCOMM socket.
    - RFCOMM data is multiplexed and segmented by L2CAP.
    - HCI transmits the data via ACL packets to the controller.
    - Controller radios it across the air to the paired device.
5. **SDP** sits next to RFCOMM/L2CAP (not always in the main data path).
   - It’s used before a connection to discover available services and their parameters.
   - Once SDP replies with, say, “SPP is on RFCOMM channel 3,” your app then opens that channel.


---

**Summary Table**

| Layer   | Role                                 | Typical Function                                      | Analogy                        |
|---------|--------------------------------------|-------------------------------------------------------|--------------------------------|
| HCI     | Host/controller bridge               | Commands, events, basic data flow                     | Airport control tower          |
| L2CAP   | Multiplexing & segmentation          | Channel mgmt, packet split/reassembly, QoS            | Post office                    |
| RFCOMM  | Serial emulation (app link)          | Virtual serial ports over L2CAP                        | Virtual USB/serial cable       |
| SDP     | Service discovery                    | Service queries/advertisement                          | Restaurant menu                |

---


# Part 1 – Classic Bluetooth vs BLE

You already know **BLE** is:
- Low energy, short bursts of data
- GATT services/characteristics
- Optimized for sensors, wearables

**Classic Bluetooth**:
- Designed for continuous streaming or higher data throughput
- Uses profiles (SPP, A2DP, HFP, HID, etc.) rather than GATT
- Usually higher power than BLE
- Backward compatibility with older devices

### Key Differences Table

| Feature        | BLE                   | Classic Bluetooth               |
| -------------- | --------------------- | ------------------------------- |
| Data Rate      | ~1Mbps                | Up to 3Mbps (EDR)               |
| Latency        | Low for short packets | Higher, but continuous          |
| Use Cases      | Sensors, beacons, fitness | Audio, serial data, keyboards, file transfer |
| Architecture   | GATT Services/Characteristics | Profiles over RFCOMM, L2CAP     |
| Range          | Similar (~10–100m)    | Similar (~10–100m)              |

---

# Part 2 – Classic Bluetooth Architecture

**Classic Bluetooth stack layers:**
- **Radio** – Physical wireless link (2.4GHz ISM)
- **Baseband** – Controls physical channel, device addressing
- **L2CAP** – Logical Link Control and Adaptation Protocol (multiplexing, packet segmentation)
- **RFCOMM** – Serial port emulation (SPP profile)
- **Profiles** – Define application behavior (SPP, A2DP, HFP, etc.)

---

# Part 3 – Coding Basics

Assuming **Android** development (Java/Kotlin). If you need for ESP32 or Linux BlueZ, let me know.

**Example: Discover Classic Bluetooth Devices (Android, Java/Kotlin)**
```java
BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
if (bluetoothAdapter == null) {
Log.e("BT", "Device doesn't support Bluetooth");
} else if (!bluetoothAdapter.isEnabled()) {
Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
}

// Start discovery
bluetoothAdapter.startDiscovery();

// Listen for found devices
private final BroadcastReceiver receiver = new BroadcastReceiver() {
public void onReceive(Context context, Intent intent) {
String action = intent.getAction();
if (BluetoothDevice.ACTION_FOUND.equals(action)) {
BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
Log.i("BT", "Found device: " + device.getName() + " - " + device.getAddress());
}
}
};
```
---
# Comparing BLE GATT and Classic Bluetooth SPP

compare BLE GATT with something very similar in Classic Bluetooth — the SPP (Serial Port Profile) — since both  for general-purpose, arbitrary data exchange, but their stack architectures and data-handling paradigms are quite different.

---

## 1. Architecture Difference — BLE vs Classic Bluetooth

### **BLE Stack Architecture**
Application
  ↑
GATT (Services / Characteristics)
  ↑
ATT (Attribute Protocol)
  ↑
L2CAP (Low Energy mode)
  ↑
Link Layer (BLE-specific)
  ↑
Radio (2.4 GHz)



- **GATT** (Generic Attribute Profile) is the main application-level protocol that structures data as "Services" (containers) and "Characteristics" (data points).
- **ATT** (Attribute Protocol) moves these attributes (data units) around.
- **L2CAP** in BLE is simplified, optimized for low energy.
- Devices advertise services/characteristics; interactions are attribute-based.

---



### Classic Bluetooth Stack

Application
  ↑
Profile (e.g., SPP, A2DP, HFP)
  ↑
RFCOMM (Serial Port Emulation) / Other profile transport
  ↑
L2CAP (Full-featured, multiplexing channels)
  ↑
Baseband
  ↑
Radio (2.4 GHz)

- **Profiles**: Instead of GATT, Classic Bluetooth uses Profiles — predefined rules for use cases (e.g., SPP for serial, A2DP for audio).
- **SPP** (Serial Port Profile) emulates a serial port, allowing bidirectional byte streams as if over RS-232, ideal for serial data exchange between devices.
- **RFCOMM** provides the "virtual serial cable."
- **L2CAP** here is more capable: supports multiple streams and greater throughput; not optimized for energy efficiency.

---

## **Key Points of Comparison**

| Layer/Concept  | BLE (GATT)                                | Classic Bluetooth (SPP)                        |
| -------------- | ----------------------------------------- | ----------------------------------------------- |
| **Stack Top**  | GATT (Services & Characteristics)         | Profile (e.g., SPP)                            |
| **Transport**  | ATT (attribute-based transactions)        | RFCOMM (serial port emulation)                  |
| **L2CAP**      | Simplified for low energy                 | Full-featured, supports channel multiplexing    |
| **Data Model** | Structured: Services & Characteristics    | Unstructured: Byte stream                       |
| **Use Case**   | Sensors, control/status, small data       | Serial replacement, bulk continuous data        |
| **Power**      | Low power, connectionless by default      | Higher power, continuous connections            |

- **GATT vs. SPP**: GATT organizes data in a hierarchical, structured way (services/characteristics), while SPP offers a simple, virtual serial port with just raw byte transmission.
- **BLE GATT** is best for applications needing low power, intermittent communications.
- **SPP** excels for legacy serial devices or whenever you want seamless, bidirectional data streaming[7][13][15].

---

## **Summary Table**

| Feature          | BLE GATT                              | Classic SPP                                   |
| ---------------- | ------------------------------------- | --------------------------------------------- |
| Data Structure   | Services, Characteristics             | Simple byte stream                            |
| Protocol         | ATT/GATT                              | RFCOMM                                        |
| Multiplexing     | Limited                               | Supported via L2CAP                           |
| Energy Usage     | Low                                   | Higher                                        |
| Best Use Case    | IoT, sensors, status/control devices  | Serial port replacement, Arduino, bulk data   |

---

This highlights the core differences between BLE GATT and Classic Bluetooth SPP — both enable flexible data transfer but are architected for very different use-cases and constraints.

# Flow Comparison — Connecting & Exchanging Data

Both **BLE GATT** and **Classic Bluetooth SPP** enable device-to-device communication, but their connection flows and interaction styles differ significantly.

---

## **BLE GATT Flow**  
*(Example: Reading temperature from a BLE sensor)*

1. **Scan for devices** — Listen for *advertisements* broadcast by nearby BLE devices.
2. **Connect** — Establish a link at the BLE Link Layer.
3. **Discover services & characteristics** — Query the device for available GATT services (containers) and characteristics (data points).
4. **Read characteristic value** — Request a specific characteristic; data flows through:  
   `ATT → L2CAP (Low Energy) → Link Layer → Radio (2.4 GHz)`
5. **Disconnect** — Close the connection to conserve power.

---

## **Classic Bluetooth SPP Flow**  
*(Example: Sending text to a microcontroller)*

1. **Inquiry scan** — Search for nearby Classic Bluetooth devices.
2. **Pair / bond** — Exchange a PIN code or complete authentication.
3. **Connect to RFCOMM channel** — Use the SPP-assigned channel for serial communication.
4. **Send/receive data** — Exchange bytes in a continuous stream, like a UART over wireless.
5. **Disconnect** — End the session when done.

---

## **Key Insight**

> **SPP is like "GATT without the database"** —  
> - BLE GATT imposes a *structured data model* (services & characteristics).  
> - SPP gives you a *raw bidirectional data pipe* you can write bytes into and read from, with no predefined schema.

---

## **Flow Comparison Table**

| Step                | BLE GATT                                     | Classic Bluetooth SPP              |
| ------------------- | -------------------------------------------- | ------------------------------------ |
| **Discovery**       | Advertisement scan                          | Inquiry scan                         |
| **Authentication**  | Optional (pairing depends on config)        | Usually requires PIN pairing         |
| **Connection**      | Link Layer connection                       | RFCOMM channel connection            |
| **Data Format**     | Structured (services/characteristics)       | Raw byte stream                      |
| **Overhead**        | Higher (due to discovery & attribute reads)  | Lower (direct byte send/receive)     |
| **Power Use**       | Low (short bursts)                          | Higher (continuous connection)       |
| **Best For**        | Small structured sensor/control data         | Bulk or continuous serial data flow  |

---

This breakdown shows how **BLE GATT prioritizes structure and efficiency**, while **SPP prioritizes simplicity and continuous throughput**.
<img width="1580" height="1180" alt="image" src="https://github.com/user-attachments/assets/296f18df-5080-4bb5-9a34-d86f78548242" />

# Real-World Classic Bluetooth SPP Flow on BlueZ (C / D-Bus)

This guide walks through a **Classic Bluetooth Serial Port Profile (SPP) connection** using BlueZ, the official Linux Bluetooth stack, via the C / D-Bus API approach. Each step below describes the API call as well as the kind of information you will typically see or need.

---

## 1. **Inquiry Scan (Discovery)**

- **Purpose:** Find nearby Bluetooth Classic (BR/EDR) devices.
- **How:** Uses the Bluetooth inquiry procedure.
- **Returns:**  
  - **MAC Address** (e.g., `00:1A:7D:DA:71:13`)
  - **Class of Device** (CoD, e.g., `0x1F00` = wearable)
  - **RSSI** (signal strength)
  - Sometimes **device name** (if the remote responds)
- **D-Bus method:**  
  `org.bluez.Adapter1.StartDiscovery()`  
  - Starts device discovery and populates properties for each discovered device[6][11].

---

## 2. **Pairing (Bonding)**

- **Purpose:** Secure the link with encryption/authentication by exchanging keys.
- **How:** Initiate bonding, potentially requiring a PIN/passkey depending on device capabilities.
- **Returns:**  
  - Pairing **success or failure**.
  - If successful, the device is added to `/var/lib/bluetooth/<adapter>/<device>/info` and marked as trusted.
- **D-Bus method:**  
  `org.bluez.Device1.Pair()`  
  - Handles the pairing exchange and stores credentials in BlueZ[7][8][17].

---

## 3. **Service Discovery (SDP)**

- **Purpose:** Discover supported profiles/services on the remote device.
- **How:** Query the device's Service Discovery Protocol records for available UUIDs.
- **For SPP:**
  - **Service UUID:** `00001101-0000-1000-8000-00805f9b34fb`
  - Find the corresponding **RFCOMM channel** (e.g., Channel 1).
- **D-Bus method:**  
  - Connect a specific profile using `org.bluez.Device1.ConnectProfile(UUID)`
  - You can also use tools like `sdptool` to browse service records and identify the RFCOMM channel[7][8][14].

---

## 4. **RFCOMM Connect**

- **Purpose:** Open a virtual serial port for unstructured byte stream communication.
- **How:**  
  - Bind an **RFCOMM** device such as `/dev/rfcomm0`, which acts like a classic serial port.
  - You can now `read()`/`write()` bytes similar to UART.
- **D-Bus API:**  
  - Not directly exposed for the raw socket; you typically open the RFCOMM connection in C via 
    ```
    socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)
    ```
  - Client-side applications use the known RFCOMM channel from SDP to connect[8][14].

---

## **Summary Table: SPP Flow with BlueZ**

| Step                | D-Bus API Call / Tool                      | Info Returned / Used                      |
|---------------------|--------------------------------------------|--------------------------------------------|
| **Scan/Discovery**  | Adapter1.StartDiscovery()                  | MAC, CoD, RSSI, Name                      |
| **Pairing**         | Device1.Pair()                             | Paired status, trust info                 |
| **Service Discovery**| Device1.ConnectProfile(UUID) / sdptool    | Service UUID, RFCOMM channel              |
| **RFCOMM Connect**  | socket(), /dev/rfcomm0                     | Virtual serial port, read/write byte stream|

---

> **Tip:** The flow above is how most SPP applications (e.g., wireless serial bridges, robot controllers) are established on Linux using BlueZ and the D-Bus API.  
# profiles and underlying protocol
<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/1a2b962d-4afe-42da-989b-ac6439d5701c" />

# Part 4 – Learning Roadmap

We’ll start with SPP (Serial Port Profile) because it’s the simplest to reason about and implement, then I’ll show:

- A clear step‑by‑step sequence (what Device A and Device B each do, and what happens inside the controller + host), and
- Working C examples:
  - Discovery with raw HCI calls,
  - RFCOMM server (Device A) and RFCOMM client (Device B) using raw sockets, and
  - A compact D‑Bus (GDBus) C snippet showing how to call Pair() and Connect() via BlueZ.

If that looks good I’ll move on to the next profile (HFP / A2DP / HID / etc.) the same way.

---

### Real-world scenario (SPP) Assume:

- **Device A** = embedded device running an RFCOMM SPP server (will `bind()` to RFCOMM channel 3 and `listen()`).
- **Device B** = PC or phone acting as RFCOMM client (will discover Device A, query for SPP service, pair if needed, then open RFCOMM and exchange bytes).

---

### High-level sequence (6 steps)

1. Inquiry / Discovery  
2. Service Discovery (SDP) to find SPP’s RFCOMM channel  
3. Pairing / Authentication (if security required)  
4. Connection (L2CAP → RFCOMM) — RFCOMM open on channel from SDP  
5. Data exchange (read/write over RFCOMM socket)  
6. Disconnect / optional bonding (store link keys)

I’ll expand what each side and the controller do for each step.

---

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

- Its controller automatically responds to inquiry if it’s set to be discoverable.
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

---

### Raw C examples (tested patterns you can compile)

**Notes before running:**

- These programs require Bluetooth dev headers and BlueZ libraries (`libbluetooth`).
- On many systems you must be root (or give capabilities) to open HCI and raw Bluetooth sockets.
- Compile with `-lbluetooth`. Example:  
  `gcc -o hci_discover hci_discover.c -lbluetooth`
