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

# Part 4 – Learning Roadmap

We’ll build in stages:
- **Scanning** – Discover Classic Bluetooth devices
- **Pairing** – Initiate and manage pairing
- **SPP Communication** – Send/receive data like a serial port
- **Profile-based features** – e.g., audio streaming (A2DP), file transfer (OBEX)
- **Embedded side** – How to interact with microcontrollers (ESP32, Raspberry Pi)
