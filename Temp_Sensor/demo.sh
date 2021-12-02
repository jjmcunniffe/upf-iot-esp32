#!/bin/bash

# Get the serial port of the device.
echo Serial port options:
ls /dev/cu.* # MacOS only.

echo What serial port is the device on?:
read port

# Build, flash and monitor the device.
/bin/bash ./flash.sh $port
/bin/bash ./monitor.sh $port
