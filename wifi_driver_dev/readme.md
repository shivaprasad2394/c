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
