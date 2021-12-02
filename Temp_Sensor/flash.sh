#!/bin/bash

# Load the esp-idf tools into your environment.
. $HOME/esp/esp-idf/export.sh

# Target ESP32S2 and build an image.
idf.py set-target esp32s2
idf.py build

# Flash to the device.
if [ $# -eq 0 ];
    then
        echo Serial port options:
        ls /dev/cu.* # MacOS only.

        echo What serial port is the device on?:
        read port
else
    $port = $0
fi

idf.py -p $port flash