#!/bin/bash

clear
printf "Running program..\n"
# Find the highest number in the existing log file names
i=0

# If no log files were found, start from 0
if [ -z "$i" ]; then
    i=0
fi
while true; do
    echo "Running miniRT for the $i time"
    ./miniRT scene.rt
    # sleep half a second
    sleep 0.5
    i=$((i+1))
done