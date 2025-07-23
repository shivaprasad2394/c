# PFIP Project Code Walkthrough and Architecture Overview

This markdown document provides a concise but complete overview of the [PFIP project](https://git.nt.uni-saarland.de/open-access/pfip), tailored for ESP32-C3 platforms, including Wi-Fi initialization, MAC-level handling, and Petri Net-based logic.

---

## \:rocket: Project Purpose

PFIP (Programmable Fully Integrated Platform) is designed to:

* Provide a custom Wi-Fi driver implementation (below `esp_wifi`) for ESP32-C3
* Enable low-level MAC layer packet analysis and control
* Integrate a Petri-net-style transition system to manage task execution
* Enable deterministic experimentation and measurements for embedded networking research

---

## \:file\_folder: Key Project Structure

```bash
pfip/
├── main/                # Core application logic
│   ├── net_setup.c      # Wi-Fi initialization & connection logic
│   ├── wifi_driver.c    # Driver logic: RX queues, DMA desc, hooks
│   ├── wifi_mac.c       # MAC-layer packet parsing and processing
│   ├── wifi_analysis.c  # Analysis tools for packet inspection
│   ├── checkpointing.c  # App state persistence (energy-related)
│   └── queue.c          # Internal data queue management
│
├── components/
│   ├── petri/           # Petri Net execution engine
│   └── ip_stack/        # Custom IP stack (experimental)
│
├── tests/               # Unit and integration test apps
├── sdkconfig            # ESP-IDF config file
└── README.md
```

---

## \:satellite: Wi-Fi Flow (`net_setup.c`)

This is where your device connects to the Wi-Fi network (`SSID: Shivaprasad`, `Password: 12345678`).

**Important functions:**

* `net_setup()`

  * Initializes NVS
  * Sets up `wifi_init_config_t` and `wifi_config_t`
  * Starts Wi-Fi in `WIFI_MODE_STA`
  * Calls `esp_wifi_connect()`
* Uses `event_handler()` to handle:

  * `WIFI_EVENT_STA_START`
  * `WIFI_EVENT_STA_CONNECTED`

---

## \:gear: Driver Layer (`wifi_driver.c`)

This file implements the RX DMA descriptor management and queues raw packets to higher layers.

**What it does:**

* Initializes RX ring buffers
* Handles incoming data and queues it
* Logs packet reception
* Example logs:

  ```
  Queueing RX entry
  There are 2 packets received so far
  ```

---

## \:zap: MAC Layer (`wifi_mac.c`)

This part filters packets and does MAC-level analysis.

**Key roles:**

* Packet demultiplexing (IPv4, non-IPv4)
* Tracks packet metadata
* Handles raw frame analysis hooks
* Runs under `mac_task`

Example log:

```text
wifi_mac: Non IPv4 packet
```

---

## \:brain: Petri Net Engine (`components/petri/`)

Used to model and control execution flow.

**Logs show transitions tested:**

```text
petri: test transition = 14, current transition = 0
```

**Features:**

* Transition execution model
* Useful for repeatable test conditions
* Logs buffer pool usage:

  ```
  all buffers in pool 12 used
  ```

---

## \:wrench: App Startup Sequence

1. **Bootloader** initialized
2. `app_main()` calls `net_setup()`
3. Event loop waits for connection success
4. On Wi-Fi connect:

   * `wifi_driver` starts
   * `mac_task` starts
   * Petri net transitions begin

---

## \:bookmark\_tabs: Observed Runtime Behavior (from Log)

| Phase  | Action             | Log/Result                              |
| ------ | ------------------ | --------------------------------------- |
| Boot   | Load + Init        | SPI boot @ 80 MHz, flash size 4MB       |
| Wi-Fi  | Connect            | Found AP `Shivaprasad` on channel 11    |
| Wi-Fi  | Connected          | WPA2-PSK, RSSI -33 dBm                  |
| Driver | RX Queue           | Packets queued, RX entries logged       |
| MAC    | Processing         | Logs indicate non-IPv4 packets filtered |
| Petri  | Firing transitions | Transitions 0–14 cycled repeatedly      |

---

## \:warning: Issues Observed

* Buffer pool exhaustion seen:

  ```
  [FATAL] all buffers in pool 12 used
  ```

  This indicates a leak or non-freed descriptors in the Petri execution engine.

* UDP server send error:

  ```
  udp_server: failed to send 5 bytes, err = -1
  ```

---

## \:memo: Summary

PFIP is a **custom Wi-Fi MAC + driver framework** built atop ESP32-C3, ideal for deterministic networking research. It overrides parts of the ESP-IDF stack to:

* Gain low-level control over Wi-Fi packet flow
* Experiment with custom MAC behavior
* Integrate a Petri-net for formal modeling of task flows

The modular structure in `main/` and `components/` makes it easy to trace:

* **Wi-Fi connection** in `net_setup.c`
* **Packet reception** in `wifi_driver.c`
* **MAC parsing** in `wifi_mac.c`
* **Control flow** in `petri`

---

Let me know if you'd like visual architecture or want to contribute this as a GitHub README! ✅
