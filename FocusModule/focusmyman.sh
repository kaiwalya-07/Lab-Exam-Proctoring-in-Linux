#!/bin/bash

if [ -f ~/kernel/FocusModule/focus.txt ]; then
    echo "File exists and is a regular file"
else
    touch ~/kernel/FocusModule/focus.txt
fi
total_time=$1

time=0

while true; do

    
    active_window=$(xdotool getwindowfocus getwindowname)
	
    echo "$active_window" >> ~/kernel/FocusModule/focus.txt    
    sleep 5
done
