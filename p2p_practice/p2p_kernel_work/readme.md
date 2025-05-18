Goal involves interacting with the wireless stack from the kernel side via Netlink (which is how userspace nl80211 commands communicate with the kernel), a good starting point is a simple kernel module that can receive Netlink messages from userspace and interact with the wireless subsystem.

Below are two code snippets:

A basic Linux Kernel Module (.c file): This module will register a simple generic Netlink family and implement a handler to receive a message. When it receives a message, it will attempt to find a wireless device (wiphy) and print its name to the kernel logs (dmesg).
A basic Userspace Netlink Client (.c file): This application will send a simple Netlink message to the kernel module.
This code does NOT implement the complex P2P interface creation, parallel operation, or resource sharing logic. It is purely a skeleton to demonstrate how a kernel module can communicate with userspace via Netlink and perform a basic interaction with the wireless subsystem (finding a wiphy).


g++ my_wireless_client.c -o my_wireless_client -l:libnl-3.a -l:libnl-genl-3.a # Link statically if available
# OR dynamically if static libs are not preferred/available:
# g++ my_wireless_client.c -o my_wireless_client -lnl-3 -lnl-genl-3

Load the kernel module
sudo insmod my_wireless_module.ko

Run the userspace client:
sudo ./my_wireless_client

Unload the kernel module when done
sudo rmmod my_wireless_module


Check dmesg for the module exit message
