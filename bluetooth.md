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

# Part 4 – Learning Roadmap

We’ll build in stages:
- **Scanning** – Discover Classic Bluetooth devices
- **Pairing** – Initiate and manage pairing
- **SPP Communication** – Send/receive data like a serial port
- **Profile-based features** – e.g., audio streaming (A2DP), file transfer (OBEX)
- **Embedded side** – How to interact with microcontrollers (ESP32, Raspberry Pi)
