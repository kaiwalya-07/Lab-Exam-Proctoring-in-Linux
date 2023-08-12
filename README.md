# Lab-Exam-Proctoring-in-Linux
To build this proctor framework, we mainly focused on problems like the use of the internet for
offline or online lab exams, the use of external devices like pen drives, and the use of already
present files in the system. Keeping in mind these problems, we started working on building
Linux kernel modules to prevent the previously mentioned cheating activities. We have basically
three modules related to this inserted in the Linux kernel that will be triggered at the time of the
exam and perform the required activities the modules are intended to perform. We also used SSH
to write a script that would insert these modules into the connected lab systems from the main
computer. This will directly insert the modules inside the computer. The three modules that we
built are:

 1. Internet Blocking Module: This module was built with the intention of disabling the
     entire internet from the system. For an exam that requires working on offline software,
     this module is useful to block access to the internet connection. This module made use of
     the netfilter framework provided in Linux, which is helpful for network filtering, packet
     manipulation, etc.
     
  2. Internet Blocking except for a particular website: This module was built with the
     intention of tailoring access to the internet by blocking the internet except for a particular
     website, maybe where the exam is being conducted. This is useful when an exam is to be
     taken on an online platform. This module can be expanded to give more freedom to the
     examiner to add any website to the allowed website list.
     
  3. External device blocker module: This module blocks the specified port where the external
     devices (except for keyboard or mouse) are connected. This helps to avoid using any
     help that can be offered from the data on an external device.
     
We have also written a focus script to detect the change from the exam window to some other
place, another directory, or any other location. This script will log all the paths that the user
traversed and which files he/she opened into a text file, which can be investigated for cheating
detection purposes.


## Prerequisites
● A system with a Linux OS

● An user account with root access to the system

● At least 12 GB of available space



## Steps to follow from scratch
##### Step 1. Building Linux Kernel/Compiling Linux Kernel from Source Code
 It involves building a custom version of the Linux system by compiling the source code. This
process has several steps, like configuring, compiling, and installing the kernel.
Step 1. Source Code Download
The latest kernel version can be downloaded from the official kernel website. It can also be
downloaded from the given command line in the terminal.

 ```bash
     wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.0.7.tar.xz
```

##### Step 2. Extracting Source Code
Run the following command to extract the source code
  ```bash
   tar xvf linux-6.0.7.tar.xz
```

##### Step 3. Installing the Core Packages
Some additional packages are required for building the kernel. To do this, run the
following command:
```bash
 sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
```

##### Step 4. Kernel Configuration
This step involves changing kernel settings based on your needs, as they come with their default
configuration. Here we have set the kernel to its default configuration.
```bash
 cp -v /boot/config-$(uname -r) .config
 make menuconfig
```

##### Step 5. Building Kernel
This process will take some time execute , run the below code
```bash
make
```
There may be the following error that will interrupt the building process if you are on Ubuntu.
No rule to make target 'debian/canonical-certs.pem, then fix this issue with the two given commands
```bash
 scripts/config --disable SYSTEM_TRUSTED_KEYS
 scripts/config --disable SYSTEM_REVOCATION_KEYS
```
Now install the require modules by the following code:
```bash
sudo make modules_install
```
Finally, install the kernel by running the following code:
```bash
sudo make install
```

##### Step 6. Testing modules to validate kernel building
We have used two basic and simple modules which will justify the kernel that it has successfully
built.
You can test the modules by following these commands in the terminal navigated in the same
directory.

Command to load the module:
```bash
sudo insmod <module_name>.ko
```

Verification for successful loading:
```bash
lsmod | grep <module_name>
```


Command to unload the module
```bash
sudo rmmod <module_name>
```
