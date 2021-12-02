#!/bin/bash

# Load the esp-idf tools into your environment.
. $HOME/esp/esp-idf/export.sh

# Start monitoring the device.
if [ $# -eq 0 ];
    then
        echo Serial port options:
        ls /dev/cu.* # MacOS only.

        echo What serial port is the device on?:
        read port
else
    $port = $0
fi

idf.py -p $port monitor