for ble_wifi_coex_minimal_opt_todo.7z -->source from 5.4 idf shivaprasad@anonymous:~/esp-at/esp-idf/components$
as of now
        I (16474) BLE_WIFI_COEX: Status: BLE Connected (pairing...)
        I (16474) BLE_WIFI_COEX: Dynamic heap total: 263464 bytes
        I (16474) BLE_WIFI_COEX: Dynamic free: 139580 bytes
        I (16474) BLE_WIFI_COEX: Dynamic used: 123884 bytes
        
        I (16474) BLE_WIFI_COEX: Approx total RAM used (static + dynamic): 169400 bytes


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
