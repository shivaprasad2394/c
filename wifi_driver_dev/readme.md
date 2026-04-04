==============================COEX  GUIDE======================================================
---

## Build & Flash Guide

Tested on **Ubuntu 22.04**, **ESP-IDF v5.0.1**, **ESP32 chip rev v3.1**.

---

### Prerequisites

- Python 3.10
- Git
- `build-essential`, `cmake`, `ninja-build`

```bash
sudo apt install git cmake ninja-build build-essential python3 python3-pip
```

---

### 1. Install ESP-IDF v5.0.1

```bash
mkdir -p ~/esp && cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
git checkout v5.0.1
git submodule update --init --recursive
./install.sh
```

> If you have another ESP-IDF version installed (e.g. v6.x), keep them separate.
> This project **requires v5.0.1** — other versions are not tested.

---

### 2. Fix Python Environment

ESP-IDF v5.0.1 depends on `pkg_resources`, which was removed from `setuptools >= 81`.
After `install.sh`, apply these fixes **once**:

```bash
# Pin setuptools to a version that includes pkg_resources
~/.espressif/python_env/idf5.0_py3.10_env/bin/python \
  -m pip install --force-reinstall setuptools==69.5.1

# Install ruamel.yaml with proper dist-info
~/.espressif/python_env/idf5.0_py3.10_env/bin/python \
  -m pip install --force-reinstall ruamel.yaml==0.17.21

# Fix ruamel.yaml.clib namespace package dist-info (known pip bug)
cd ~/.espressif/python_env/idf5.0_py3.10_env/lib/python3.10/site-packages/
cp -r ruamel_yaml_clib-0.2.15.dist-info "ruamel.yaml.clib-0.2.15.dist-info"
cd ~
```

Verify it works:

```bash
~/.espressif/python_env/idf5.0_py3.10_env/bin/python \
  -c "import pkg_resources; print(pkg_resources.get_distribution('ruamel.yaml'))"
# Expected: ruamel.yaml 0.17.21
```

---

### 3. Activate ESP-IDF

Run this in every new terminal before building or flashing:

```bash
source ~/esp/esp-idf/export.sh
```

**Recommended**: add an alias to `~/.bashrc` so you never forget:

```bash
echo "alias get_idf='. ~/esp/esp-idf/export.sh'" >> ~/.bashrc
source ~/.bashrc
```

Then just type `get_idf` in any terminal.

> Do **not** add `source export.sh` directly to `~/.bashrc` — it runs on every terminal
> open and causes conflicts if you have multiple IDF versions.

---

### 4. Clone & Enter the Project

```bash
git clone <repo-url>
cd <repo-folder>
```

---

### 5. Set Target

```bash
idf.py set-target esp32
```

---

### 6. Build

```bash
idf.py build
```

Expected output at the end:

```
Project build complete. To flash, run:
  idf.py -p (PORT) flash
```

> **Tip for low-RAM machines (< 4 GB):** Close Chrome and other heavy apps before
> building. ESP-IDF builds are memory-intensive. Swap usage during build is normal
> but will slow things down significantly.

---

### 7. Flash

Find your port first:

```bash
ls /dev/ttyUSB* /dev/ttyACM*
```

Flash and open serial monitor in one command:

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

Exit the monitor with `Ctrl + ]`.

---

### 8. Expected Boot Sequence

A successful boot prints the following in order (timestamps approximate):

```
I (1550) COEX: Coeistence control initialized
I (1560) MAIN: Initializing BLE Stack...
I (2270) BLE_INIT: BLE Controller enabled
I (2320) BLE_INIT: --- NimBLE Host SYNC Complete! ---
I (2320) BLE_INIT: Device Address: xx:xx:xx:xx:xx:xx (type=0)
I (2330) NimBLE: adv_itvl_min=1600 adv_itvl_max=3200
I (2360) BLE_INIT: Advertising started!
I (2410) BLE_INIT: BLE Initialization Complete - SUCCESS
I (2420) MAIN: Custom BLE started successfully!
I (2440) hwinit: Skipping coex init (PTA disabled) - WiFi and BLE share radio without arbitration
I (2590) hardware.c: Wifi channel set to:6
AP Started on Channel 6
I (2760) MAIN: WiFi + BLE Coexistence Active
```

Within a few seconds you will see probe requests from nearby devices:

```
[PROBE #1] From xx:xx:xx... Ch=6
```

And the TDM coexistence kicking in automatically when needed:

```
W hardware.c: TDM:3 consecutive tx timeout - BLE has taken the radio
I hardware.c: TDM: BLE stopped, wifi phy fully restored on ch6
```

---

### Troubleshooting

| Symptom | Fix |
|---|---|
| `pkg_resources cannot be imported` | Re-run step 2 (setuptools fix) |
| `ruamel.yaml not found` | Re-run step 2 (ruamel.yaml fix) |
| `source export.sh` resets `IDF_PATH` to wrong version | Check `~/.bashrc` for stale `source` lines pointing to another IDF install |
| Flash fails: permission denied on `/dev/ttyUSB0` | `sudo usermod -aG dialout $USER` then log out and back in |
| Flash fails: port not found | Check USB cable (must be data cable, not charge-only) |
| Build runs out of memory / very slow | Close Chrome, run `sudo swapoff -a && sudo swapon -a` to flush swap |
| `No such file or directory: esp32_heap_caps.h` | Wrong file — correct include is `esp_heap_caps.h` |
| `xPortInISRContext undeclared` | ESP-IDF 5.x renamed it to `xPortInIsrContext` (lowercase Isr) |

Current Status ✅
Working successfully:

Boot completes cleanly on ESP-IDF v5.0.1
WiFi AP starts on Channel 6 — beacons transmitting every ~110ms
Multiple devices are actively probing (3 different MAC addresses detected within first 4 seconds)
RX pipeline working — frames being handed to MAC stack
TX pipeline working — multiple slots cycling (0, 1, 2, 3) with correct CRC-appended lengths
DHCP server started successfully
A client actually connected and exchanged IP data (ARP + IP packets visible at ~81–84 seconds)
TDM coexistence working — at t=4.67s the system detected 3 consecutive TX timeouts, stopped BLE advertising, restored WiFi PHY on ch6, and resumed cleanly
BLE GAP stop advertising confirmed by NimBLE stack log


What You CAN Do
WiFi (AP mode):

Beacon transmission ✅
Probe request reception and response ✅
Client association ✅
DHCP assignment ✅
ARP + IP data exchange ✅
Channel selection ✅
Multi-slot TX (up to 5 slots) ✅
RX DMA chain management ✅

BLE:

BLE advertising (slow interval 1–2s) ✅
TDM stop/start advertising from WiFi task ✅
NimBLE host stack running on core 1 ✅
BLE connection events handled ✅

Coexistence:

Software TDM arbitration ✅
Automatic BLE pause on WiFi TX starvation ✅
Full PHY restoration after BLE pause ✅
BLE resumes after 5 seconds of WiFi-only window ✅


What You CANNOT Do (Current Limitations)
WiFi:

No WPA2/security — open AP only (open-mac limitation, no crypto in open code)
No power save / modem sleep — radio always on
No scanning while in AP mode
No STA+AP (dual interface) simultaneously
No 802.11n HT rates — legacy rates only
TX slot count limited to 5 — high throughput will saturate

BLE:

No BLE data transfer while WiFi is active — advertising only
No BLE connections sustained during WiFi TX bursts (radio contention)
No hardware PTA arbitration (intentionally disabled) — pure software TDM
BLE connection reliability will be poor if a client tries to connect during heavy WiFi traffic

Coexistence:

No fine-grained time slicing — it's reactive, not predictive
3-timeout threshold is a heuristic — may trigger false positives on RF noise
5-second WiFi window is fixed — not adaptive to actual traffic load
No feedback from BLE side about connection state to WiFi task


Future Scope of Improvement
Short term:

Make TDM window sizes adaptive based on actual WiFi throughput and BLE connection state
Add BLE connection awareness — don't pause advertising if a BLE client is connected
Reduce the 3-timeout threshold logging noise by adding a debounce

Medium term:

Implement proper PTA (Packet Traffic Arbiter) with the coex library instead of bypassing it — the current bypass was needed to get it working but proper PTA would give better radio sharing
Add WPA2 support to the open-mac WiFi stack
Implement proper TX completion interrupts instead of polling

Long term:

Port to ESP32-C3/S3 which have native hardware coexistence support
Implement 802.11n support for higher throughput
Add BLE GATT server so connected BLE clients can query WiFi AP status

===============================================================================================

1)for ble_wifi_coex_minimal_opt_todo.7z -->source from 5.4 idf shivaprasad@anonymous:~/esp-at/esp-idf/components$
as of now
```c
        I (16474) BLE_WIFI_COEX: Status: BLE Connected (pairing...)
        I (16474) BLE_WIFI_COEX: Dynamic heap total: 263464 bytes
        I (16474) BLE_WIFI_COEX: Dynamic free: 139580 bytes
        I (16474) BLE_WIFI_COEX: Dynamic used: 123884 bytes
        
        I (16474) BLE_WIFI_COEX: Approx total RAM used (static + dynamic): 169400 bytes

        #include <inttypes.h>
        uint32_t get_total_ram_used_bytes(void) {
            // Total dynamic DRAM heap size (available for malloc at startup)
            size_t total_heap = heap_caps_get_total_size(MALLOC_CAP_8BIT);
            
            // Current free dynamic DRAM heap
            size_t free_heap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
            
            // Dynamic used = total_heap - free_heap
            uint32_t dynamic_used = total_heap - free_heap;
            
            // Approximate total used RAM = static DRAM + dynamic used
            // Note: Static DRAM from idf.py size (e.g., your build ~45KB)
            // For runtime estimate, use this (static not directly available runtime)
            uint32_t approx_total_used = dynamic_used + 45516;  // Replace with your static DRAM from idf.py size
            
            ESP_LOGI(TAG, "Dynamic heap total: %zu bytes", total_heap);
            ESP_LOGI(TAG, "Dynamic free: %zu bytes", free_heap);
            ESP_LOGI(TAG, "Dynamic used: %" PRIu32 " bytes", dynamic_used);
        	ESP_LOGI(TAG, "Approx total RAM used (static + dynamic): %" PRIu32 " bytes", approx_total_used);
            
            return approx_total_used;
        }

┏━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━┳━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓
┃ Archive File            ┃ Total Size ┃  DRAM ┃ .bss ┃ .data ┃  IRAM ┃ .text ┃ .vectors ┃ Flash Code ┃  .text ┃ Flash Data ┃ .rodata ┃ .appdesc ┃ RTC FAST ┃ .force_fast ┃ RTC SLOW ┃ .rtc_slow_reserved ┃
┡━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━╇━━━━━━━╇━━━━━━╇━━━━━━━╇━━━━━━━╇━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━━━╇━━━━━━━━╇━━━━━━━━━━━━╇━━━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━┩
│ libnet80211.a           │     141478 │  9053 │ 7971 │  1082 │  5311 │  5311 │        0 │     114383 │ 114383 │      12731 │   12731 │        0 │        0 │           0 │        0 │                  0 │
│ libbt.a                 │      77632 │ 11704 │ 6677 │  5027 │  1778 │  1778 │        0 │      60915 │  60915 │       3235 │    3235 │        0 │        0 │           0 │        0 │                  0 │
│ libbtdm_app.a           │      76690 │  3609 │ 2672 │   937 │ 21943 │ 21943 │        0 │      50610 │  50610 │        528 │     528 │        0 │        0 │           0 │        0 │                  0 │
│ libpp.a                 │      69028 │  4111 │ 1488 │  2623 │ 20969 │ 20969 │        0 │      38996 │  38996 │       4952 │    4952 │        0 │        0 │           0 │        0 │                  0 │
│ libmbedcrypto.a         │      62074 │    85 │   25 │    60 │     0 │     0 │        0 │      55694 │  55694 │       6295 │    6295 │        0 │        0 │           0 │        0 │                  0 │
│ libc.a                  │      56780 │   576 │  316 │   260 │     0 │     0 │        0 │      52784 │  52784 │       3420 │    3420 │        0 │        0 │           0 │        0 │                  0 │
│ libphy.a                │      46187 │  3054 │  635 │  2419 │  9006 │  9006 │        0 │      34127 │  34127 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libwpa_supplicant.a     │      33407 │  1138 │ 1138 │     0 │     0 │     0 │        0 │      32207 │  32207 │         62 │      62 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_app_format.a     │      31628 │    10 │   10 │     0 │     0 │     0 │        0 │        434 │    434 │      31184 │   30928 │      256 │        0 │           0 │        0 │                  0 │
│ libfreertos.a           │      16203 │  3841 │  741 │  3100 │ 11942 │ 11942 │        0 │        416 │    416 │          4 │       4 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_hw_support.a     │      12716 │   844 │   92 │   752 │  4664 │  4664 │        0 │       6567 │   6567 │        589 │     589 │        0 │       28 │          28 │       24 │                 24 │
│ libnvs_flash.a          │      12576 │    28 │   28 │     0 │     0 │     0 │        0 │      12412 │  12412 │        136 │     136 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_system.a         │      12036 │   793 │  313 │   480 │  4063 │  4063 │        0 │       6723 │   6723 │        457 │     457 │        0 │        0 │           0 │        0 │                  0 │
│ libspi_flash.a          │       9897 │  1299 │   16 │  1283 │  7626 │  7626 │        0 │        748 │    748 │        224 │     224 │        0 │        0 │           0 │        0 │                  0 │
│ libcoexist.a            │       9465 │  1820 │    1 │  1819 │  3381 │  3381 │        0 │       4242 │   4242 │         22 │      22 │        0 │        0 │           0 │        0 │                  0 │
│ libheap.a               │       8965 │    20 │    8 │    12 │  5069 │  5069 │        0 │       2725 │   2725 │       1151 │    1151 │        0 │        0 │           0 │        0 │                  0 │
│ libhal.a                │       7612 │     8 │    8 │     0 │  5016 │  5016 │        0 │       2588 │   2588 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_driver_uart.a    │       6142 │   240 │   32 │   208 │     0 │     0 │        0 │       5476 │   5476 │        426 │     426 │        0 │        0 │           0 │        0 │                  0 │
│ libvfs.a                │       3536 │   236 │   44 │   192 │     0 │     0 │        0 │       3172 │   3172 │        128 │     128 │        0 │        0 │           0 │        0 │                  0 │
│ libxtensa.a             │       3388 │  1044 │    0 │  1044 │  2209 │  1785 │      424 │         99 │     99 │         36 │      36 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_mm.a             │       3166 │   164 │  128 │    36 │   801 │   801 │        0 │       2080 │   2080 │        121 │     121 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_timer.a          │       2733 │    56 │   24 │    32 │  1330 │  1330 │        0 │       1331 │   1331 │         16 │      16 │        0 │        0 │           0 │        0 │                  0 │
│ libnewlib.a             │       2730 │   388 │  200 │   188 │  1177 │  1177 │        0 │       1149 │   1149 │         16 │      16 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_wifi.a           │       2613 │   494 │   10 │   484 │   326 │   326 │        0 │       1785 │   1785 │          8 │       8 │        0 │        0 │           0 │        0 │                  0 │
│ libmain.a               │       2317 │     9 │    7 │     2 │     0 │     0 │        0 │       2292 │   2292 │         16 │      16 │        0 │        0 │           0 │        0 │                  0 │
│ librtc.a                │       2227 │     4 │    4 │     0 │  2223 │  2223 │        0 │          0 │      0 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_phy.a            │       1964 │    53 │   36 │    17 │   205 │   205 │        0 │       1488 │   1488 │        218 │     218 │        0 │        0 │           0 │        0 │                  0 │
│ libbootloader_support.a │       1817 │     0 │    0 │     0 │  1740 │  1740 │        0 │         77 │     77 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libsoc.a                │       1538 │     0 │    0 │     0 │    33 │    33 │        0 │         41 │     41 │       1464 │    1464 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_partition.a      │       1481 │     8 │    8 │     0 │     0 │     0 │        0 │       1473 │   1473 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libstdc++.a             │       1477 │    21 │   17 │     4 │     0 │     0 │        0 │       1257 │   1257 │        199 │     199 │        0 │        0 │           0 │        0 │                  0 │
│ liblog.a                │       1469 │   280 │  272 │     8 │   320 │   320 │        0 │        869 │    869 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libefuse.a              │       1227 │    64 │    4 │    60 │     0 │     0 │        0 │       1067 │   1067 │         96 │      96 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_ringbuf.a        │        749 │     0 │    0 │     0 │   749 │   749 │        0 │          0 │      0 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_vfs_console.a    │        644 │    16 │   16 │     0 │     0 │     0 │        0 │        448 │    448 │        180 │     180 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_coex.a           │        643 │    96 │    0 │    96 │   147 │   147 │        0 │        400 │    400 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libxt_hal.a             │        475 │     0 │    0 │     0 │   443 │   443 │        0 │          0 │      0 │         32 │      32 │        0 │        0 │           0 │        0 │                  0 │
│ libpthread.a            │        408 │    12 │    4 │     8 │     0 │     0 │        0 │        396 │    396 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libcore.a               │        323 │    33 │   33 │     0 │     0 │     0 │        0 │        247 │    247 │         43 │      43 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_event.a          │        301 │     4 │    4 │     0 │     0 │     0 │        0 │        297 │    297 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_rom.a            │        201 │     0 │    0 │     0 │   201 │   201 │        0 │          0 │      0 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libapp_update.a         │        110 │     4 │    4 │     0 │     0 │     0 │        0 │        106 │    106 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libgcc.a                │         89 │     0 │    0 │     0 │     0 │     0 │        0 │         89 │     89 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libesp_security.a       │         56 │     4 │    4 │     0 │     0 │     0 │        0 │         44 │     44 │          8 │       8 │        0 │        0 │           0 │        0 │                  0 │
│ libcxx.a                │         46 │     0 │    0 │     0 │     0 │     0 │        0 │         46 │     46 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ libnvs_sec_provider.a   │          5 │     0 │    0 │     0 │     0 │     0 │        0 │          5 │      5 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
│ (exe)                   │          3 │     0 │    0 │     0 │     3 │     0 │        3 │          0 │      0 │          0 │       0 │        0 │        0 │           0 │        0 │                  0 │
└─────────────────────────┴────────────┴───────┴──────┴───────┴───────┴───────┴──────────┴────────────┴────────┴────────────┴─────────┴──────────┴──────────┴─────────────┴──────────┴────────────────────┘


```
1)find port

    ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null

2)source code build and flash

     1992  idf.py build
     1993  idf.py -p /dev/ttyUSB0 erase-flash
     1994  idf.py -p /dev/ttyUSB0 flash monitor

issue file path

     echo $PATH
     1833  export PATH=$PATH:~/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin
     1834  # Verify
     1835  which xtensa-esp32-elf-gcc
     1836  xtensa-esp32-elf-gcc --version

     1892  cd ~/esp/esp-idf
     1893  git checkout v5.0.1
     1894  source ~/esp/esp-idf/export.sh
     1895  cd ~/esp/esp-idf
     1896  python3 install.sh esp32
     1897  ./install.sh esp32
     1898  source ~/esp/esp-idf/export.sh
     1899  which xtensa-esp32-elf-gcc
     1900  cd ~/chandu/husband/esp_rust_c/esp32-open-mac-main
     1901  idf.py fullclean
     1902  idf.py build
     1903  cd ~/chandu/husband/esp_rust_c/esp32-open-mac-main
     1904  find . -name "lwipopts.h" -o -name "sdkconfig*" | grep -v build
     1905  cd ~/chandu/husband/esp_rust_c/esp32-open-mac-main
     1906  grep -i "DHCP\|LWIP" sdkconfig | head -20
     1907  idf.py build
     1908  idf.py menuconfig
     1909  idf.py build
     1910  grep -inrs "CONFIG_MBEDTLS_PLATFORM_TIME"
     1911  vi sdkconfig


     1837  nano /home/shivaprasad/esp/esp-idf/components/lwip/lwip/src/core/ipv4/dhcp.c
     1838  vi /home/shivaprasad/esp/esp-idf/components/lwip/lwip/src/core/ipv4/dhcp.c
     1839  vi components/mbedtls/mbedtls/include/mbedtls/check_config.h +975
     1840  git submodule update --init --recursive
     1841  vi components/mbedtls/mbedtls/library/psa_crypto.c +5766
     1842  vi components/esp_local_ctrl/src/esp_local_ctrl_transport_httpd.c +19
     1843  vi components/protocomm/include/transports/protocomm_httpd.h +64
     1844  cd components/



```txt
shivaprasad@anonymous:~/chandu/husband/esp_rust_c/esp32-open-mac-main-Ap-working/esp32-open-mac-main$ xtensa-esp32-elf-nm components/ble/lib_esp32/esp32/libbtdm_app.a | grep -i "controller\|init\|enable" | head -20
         U ble_ll_qa_test_enable
         U bt_bb_init_cmplx
00000370 T btdm_app_ref_init
000012e0 T btdm_controller_compile_version_check
00001280 T btdm_controller_deinit
00000030 t btdm_controller_deinit_internal
00000e34 T btdm_controller_disable
00000dd8 T btdm_controller_enable
00001308 T btdm_controller_enable_sleep
000012ec T btdm_controller_get_compile_version
000012bc T btdm_controller_get_mode
0000135c T btdm_controller_get_sleep_mode
00000ef0 T btdm_controller_init
000013b0 T btdm_controller_scan_duplicate_list_clear
000012d0 T btdm_controller_set_mode
00001348 T btdm_controller_set_sleep_mode
00000544 T btdm_controller_sleep_enabled
00000800 T btdm_controller_task
         U btdm_enable_scan_forever
000003e4 T btdm_rom_ref_init

```



ncp set upguide
This is a substantial but doable extension. Here's the step-by-step guide to add RPC-based AP start/stop control from host to slave.
```c
Step 1: Define new RPC messages in protobuf
File: common/proto/esp_hosted_rpc.proto
Open this file and find the existing Wi-Fi RPC message definitions (look for message RpcReqWifiSetMode, message RpcReqWifiStart, etc.).​

Add two new messages for AP control. Append them near the other Wi-Fi request/response pairs:

text
// AP Start Request
message RpcReqWifiApStart {
    string ssid = 1;           // AP SSID
    string password = 2;       // AP password
    uint32 channel = 3;        // Wi-Fi channel (1-13)
    uint32 max_connections = 4; // Max clients
    string ip = 5;             // Static IP (e.g., "192.168.120.254")
    string gateway = 6;        // Gateway IP
    string netmask = 7;        // Netmask
}

message RpcRespWifiApStart {
    uint32 resp = 1;  // 0 = success, non-zero = error code
}

// AP Stop Request
message RpcReqWifiApStop {
    // Empty for now; just stops AP
}

message RpcRespWifiApStop {
    uint32 resp = 1;  // 0 = success, non-zero = error code
}
Then, find the main Rpc message (near the bottom of the file) that has a oneof union of all request/response pairs. Add your new messages to it:

text
message Rpc {
    uint32 msg_type = 1;
    uint32 msg_id = 2;
    
    oneof payload {
        // ... existing messages ...
        RpcReqWifiApStart req_wifi_ap_start = XX;    // pick a unique number
        RpcRespWifiApStart resp_wifi_ap_start = YY;
        RpcReqWifiApStop req_wifi_ap_stop = ZZ;
        RpcRespWifiApStop resp_wifi_ap_stop = WW;
        // ... rest ...
    }
}
Use unique field numbers (e.g., 45, 46, 47, 48) that don't conflict with existing ones. Check what numbers are already used in the oneof block.​

Step 2: Regenerate protobuf C code
From the repo root:

bash
cd common/proto
protoc --c_out=. --plugin=protoc-gen-c=../protobuf-c/protoc-c/protoc-gen-c \
    esp_hosted_rpc.proto
This generates updated esp_hosted_rpc.pb-c.c and esp_hosted_rpc.pb-c.h with your new messages.​

If protoc is not installed, install it:

bash
sudo apt-get install protobuf-compiler libprotobuf-c-dev
Step 3: Add RPC message ID constants
File: common/rpc/esp_hosted_rpc.h
Find the enum that defines RPC message IDs (look for RPC_ID__Req_WifiSetMode, etc.). Add your new message IDs:

c
#define RPC_ID__Req_WifiApStart   XX   // match the protobuf field number
#define RPC_ID__Resp_WifiApStart  YY
#define RPC_ID__Req_WifiApStop    ZZ
#define RPC_ID__Resp_WifiApStop   WW
Use the same field numbers you chose in the .proto file.​

Step 4: Implement RPC handlers on slave
File: slave/main/slave_control.c
Add two handler functions. First, include the header you need:

Near the top (after other includes):

c
#include "esp_netif.h"
#include "lwip/ip4_addr.h"
Then, before the main RPC handler table, add your two handler functions:

c
// Helper: start AP with config
static esp_err_t start_ap_with_config(const char *ssid, const char *password, 
                                      uint32_t channel, uint32_t max_conn,
                                      const char *ip_str, const char *gw_str, const char *nm_str)
{
    esp_wifi_set_mode(WIFI_MODE_AP);
    
    wifi_config_t ap_config = { 0 };
    strlcpy((char *)ap_config.ap.ssid, ssid, sizeof(ap_config.ap.ssid));
    ap_config.ap.ssid_len = strlen(ssid);
    strlcpy((char *)ap_config.ap.password, password, sizeof(ap_config.ap.password));
    ap_config.ap.channel = channel;
    ap_config.ap.max_connection = max_conn;
    ap_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
    
    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
    esp_wifi_start();
    
    // Set static IP
    esp_netif_t *ap_netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
    if (ap_netif) {
        esp_netif_ip_info_t ip_info = { 0 };
        inet_pton(AF_INET, ip_str, &ip_info.ip);
        inet_pton(AF_INET, gw_str, &ip_info.gw);
        inet_pton(AF_INET, nm_str, &ip_info.netmask);
        
        esp_netif_dhcps_stop(ap_netif);
        esp_netif_set_ip_info(ap_netif, &ip_info);
        esp_netif_dhcps_start(ap_netif);
        ESP_LOGI(TAG, "AP started: SSID=%s, IP=%s", ssid, ip_str);
    }
    
    return ESP_OK;
}

// RPC handler: start AP
static esp_err_t req_wifi_ap_start(Rpc *req, Rpc *resp, void *priv_data)
{
    RPC_TEMPLATE(RpcRespWifiApStart, resp_wifi_ap_start,
                 RpcReqWifiApStart, req_wifi_ap_start,
                 rpc__resp__wifi_ap_start__init);
    
    if (!req_payload || !req_payload->ssid || !req_payload->password) {
        resp_payload->resp = ESP_ERR_INVALID_ARG;
        return ESP_OK;
    }
    
    esp_err_t ret = start_ap_with_config(
        req_payload->ssid,
        req_payload->password,
        req_payload->channel ? req_payload->channel : 1,
        req_payload->max_connections ? req_payload->max_connections : 4,
        req_payload->ip ? req_payload->ip : "192.168.120.254",
        req_payload->gateway ? req_payload->gateway : "192.168.120.254",
        req_payload->netmask ? req_payload->netmask : "255.255.255.0"
    );
    
    resp_payload->resp = ret;
    return ESP_OK;
}

// RPC handler: stop AP
static esp_err_t req_wifi_ap_stop(Rpc *req, Rpc *resp, void *priv_data)
{
    RPC_TEMPLATE_SIMPLE(RpcRespWifiApStop, resp_wifi_ap_stop,
                        RpcReqWifiApStop, req_wifi_ap_stop,
                        rpc__resp__wifi_ap_stop__init);
    
    esp_err_t ret = esp_wifi_stop();
    resp_payload->resp = ret;
    return ESP_OK;
}
Now find the RPC handler dispatch table (search for static const RpcHandler or similar, where all req_wifi_* handlers are registered). Add your handlers:

c
// In the handler table:
{ RPC_ID__Req_WifiApStart, req_wifi_ap_start },
{ RPC_ID__Req_WifiApStop, req_wifi_ap_stop },
Step 5: Add host-side wrapper API
File: host/api/src/esp_hosted_wifi.c (or create if doesn't exist)
Add client wrapper functions that the host app will call:

c
#include "esp_hosted.h"
#include "esp_hosted_rpc.h"

esp_err_t esp_hosted_wifi_ap_start(const char *ssid, const char *password, 
                                   uint32_t channel, uint32_t max_conn,
                                   const char *ip, const char *gateway, const char *netmask)
{
    Rpc req = {0}, resp = {0};
    
    req.msg_type = RPC_MSG_TYPE__Request;
    req.msg_id = RPC_MSG_ID__Increment();
    
    RpcReqWifiApStart wifi_ap_start = RPC_REQ_WIFI_AP_START__INIT;
    wifi_ap_start.ssid = (char *)ssid;
    wifi_ap_start.password = (char *)password;
    wifi_ap_start.channel = channel;
    wifi_ap_start.max_connections = max_conn;
    wifi_ap_start.ip = (char *)ip;
    wifi_ap_start.gateway = (char *)gateway;
    wifi_ap_start.netmask = (char *)netmask;
    
    req.req_wifi_ap_start = &wifi_ap_start;
    
    int ret = esp_hosted_send_rpc(&req, &resp);
    if (ret != 0) return ESP_FAIL;
    
    return resp.resp_wifi_ap_start->resp;
}

esp_err_t esp_hosted_wifi_ap_stop(void)
{
    Rpc req = {0}, resp = {0};
    
    req.msg_type = RPC_MSG_TYPE__Request;
    req.msg_id = RPC_MSG_ID__Increment();
    
    RpcReqWifiApStop wifi_ap_stop = RPC_REQ_WIFI_AP_STOP__INIT;
    req.req_wifi_ap_stop = &wifi_ap_stop;
    
    int ret = esp_hosted_send_rpc(&req, &resp);
    if (ret != 0) return ESP_FAIL;
    
    return resp.resp_wifi_ap_stop->resp;
}
File: host/api/include/esp_hosted_wifi.h (or in host/esp_hosted.h)
Add the function declarations:

c
esp_err_t esp_hosted_wifi_ap_start(const char *ssid, const char *password, 
                                   uint32_t channel, uint32_t max_conn,
                                   const char *ip, const char *gateway, const char *netmask);
esp_err_t esp_hosted_wifi_ap_stop(void);
Step 6: Use the new API in your host TLS server
File: examples/host_tls_server/main/main.c
Replace start_remote_ap() with a call to your new RPC wrapper:

c
#include "esp_hosted_wifi.h"  // your new header

static void start_slave_ap(void)
{
    esp_err_t ret = esp_hosted_wifi_ap_start(
        "MySecureAP",
        "securepass123",
        1,                          // channel
        4,                          // max_connections
        "192.168.120.254",          // IP
        "192.168.120.254",          // gateway
        "255.255.255.0"             // netmask
    );
    
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Slave AP started via RPC");
    } else {
        ESP_LOGE(TAG, "Failed to start slave AP: %d", ret);
    }
}
Then in app_main():

c
void app_main(void)
{
    esp_hosted_init();  // initialize esp-hosted
    
    start_slave_ap();   // trigger slave AP via RPC
    
    vTaskDelay(pdMS_TO_TICKS(1000));  // wait for AP to come up
    
    xTaskCreate(tls_server_task, "tls_server_task", 8192, NULL, 5, NULL);
}
Step 7: Rebuild and test
Regenerate protobuf (Step 2 above) to get esp_hosted_rpc.pb-c.c/h.

Rebuild slave:

bash
cd ~/esp-hosted-mcu/slave
idf.py -p /dev/ttyUSB_SLAVE fullclean build flash monitor
Rebuild host_tls_server:

bash
cd ~/esp-hosted-mcu/examples/host_tls_server
idf.py -p /dev/ttyUSB_HOST fullclean build flash monitor
Test:

Host boots, sends RPC RpcReqWifiApStart to slave.

Slave receives RPC, runs req_wifi_ap_start(), starts AP with SSID/password/IP.

Host's TLS server listens and waits for clients on port 443.

Client connects to slave AP, then to https://192.168.120.254:443.

Monitor output:

Slave: I (xxx) TAG: AP started: SSID=MySecureAP, IP=192.168.120.254

Host: I (xxx) TAG: Slave AP started via RPC + I (xxx) TAG: TLS server listening on port 443

Key points:

The protobuf .proto file defines the interface (what data the RPC carries).

esp_hosted_rpc.pb-c.c/h is the generated glue (serialization/deserialization).

slave_control.c has the slave implementation (what happens when RPC arrives).

esp_hosted_wifi.c has the host client wrapper (how the host calls the RPC).

Your host app calls the wrapper, which sends the RPC over the transport (UART/SPI), slave handles it, responds.

This extends the esp-hosted protocol to give the host full control over the slave's AP mode, exactly as you want.​​

shivaprasad@anonymous:~/esp-hosted-mcu/common/proto$ protoc --c_out=. --plugin=protoc-gen-c=../protobuf-c/protoc-c/protoc-gen-c esp_hosted_rpc.proto
../protobuf-c/protoc-c/protoc-gen-c: program not found or is not executable
Please specify a program using absolute path or make sure the program is available in your PATH system variable
--c_out: protoc-gen-c: Plugin failed with status code 1.
shivaprasad@anonymous:~/esp-hosted-mcu/common/proto$
The protoc-gen-c plugin needs to be built first. Here's how to fix it:

Option 1: Build protobuf-c from source (recommended for this repo)
bash
cd ~/esp-hosted-mcu/common/protobuf-c
mkdir -p build
cd build
cmake ..
make
make install
Then try the protoc command again:

bash
cd ~/esp-hosted-mcu/common/proto
protoc --c_out=. --plugin=protoc-gen-c=../protobuf-c/build/protoc-c/protoc-gen-c \
    esp_hosted_rpc.proto
Option 2: Use system protobuf-c (simpler)
Install the prebuilt protobuf-c tools:

bash
sudo apt-get install protobuf-c-compiler libprotobuf-c-dev
Then regenerate using the system binary:

bash
cd ~/esp-hosted-mcu/common/proto
protoc-c --c_out=. esp_hosted_rpc.proto
This will generate esp_hosted_rpc.pb-c.c and esp_hosted_rpc.pb-c.h directly.​

Verify regeneration worked
Check that the files were updated and contain your new messages:

bash
cd ~/esp-hosted-mcu/common/proto
grep -i "wifi_ap_start" esp_hosted_rpc.pb-c.h
You should see RpcReqWifiApStart, RpcRespWifiApStart, etc.

Then proceed with Step 5: Add host-side wrapper API from the previous guide.
```
