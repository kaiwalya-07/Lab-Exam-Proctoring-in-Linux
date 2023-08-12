### Lab-Exam-Proctoring-in-Linux

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
