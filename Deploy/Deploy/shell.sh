#!/bin/bash

file1=$1
file2=$2
timeofexam=$3

sudo mkdir /opt/modules
sudo cd /opt/modules
git clone https://github.com/grimreaperLinux/Procter-LKM.git

cd Procter-LKM/"Simple Module"

sudo insmod test.ko
cd ..

if [ -e "$file1" ]; then
	cd Blocknet; sudo insmod blocknet.ko;
else
	cd Filternet; sudo /bin/bash domtoip.sh $file1
	
cd ..

cd USB
sudo insmod usbblock.ko

cd ..

sudo /bin/bash focusmyman.sh $file2 $timeofexam





