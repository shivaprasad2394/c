1)find port

    ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null

2)source code build and flash

     1992  idf.py build
     1993  idf.py -p /dev/ttyUSB0 erase-flash
     1994  idf.py -p /dev/ttyUSB0 flash monitor
