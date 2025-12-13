for ble_wifi_coex_minimal_opt_todo.7z -->source from 5.4 idf shivaprasad@anonymous:~/esp-at/esp-idf/components$
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





D (3234) event: running post IP_EVENT:2 with handler 0x400d6394 and context 0x3ffba1bc on loop 0x3ffb925c
0x400d6394: on_wifi_event at /home/shivaprasad/chandu/husband/esp_rust_c/esp32-open-mac-main-Ap-working/esp32-open-mac-main/main/main.c:42

ip connection done start uart task
Initialising BLE controllerE (3244) CUSTOM_BLE: btdm_controller_init failed: -1
Failed to init custom BLE: ESP_FAIL
