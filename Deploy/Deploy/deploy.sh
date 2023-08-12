#!/bin/bash

if [ $# -ne 2 ]; then
    exit 1
fi

file1=$1
file2=$2
timeofexam=$3

password="iphone6s"
username="iiitdwd"

ip_list=("192.168.1.100" "192.168.1.101" "192.168.1.102")

for ip in "${ip_list[@]}"
do
	sshpass -p "$password" ssh "$username"@"$ip" 'echo "iphone6s" | sudo -Sv && bash -s file1 file2 timeofexam' < shell.sh
done

