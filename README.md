Wi-Fi Network Scanner (C Program)

Description:
This project is a Wi-Fi Network Scanner built using the C programming language. It leverages Linux Wireless Extensions (ioctl, linux/wireless.h) to interact directly with the wireless network interface (e.g., wlan0). The program initiates a Wi-Fi scan, retrieves available networks, and displays information such as network SSIDs and MAC addresses.

It works at a low system level, using sockets and system calls, which makes it lightweight and fast compared to higher-level tools. The scanner demonstrates how system programming concepts can be applied to access hardware information and interact with network interfaces.

🔹 Key Features

Initiates Wi-Fi scans from the wireless interface.

Retrieves raw scan results using ioctl system calls.

Displays available Wi-Fi SSIDs and MAC addresses (with parsing).

Demonstrates low-level socket programming in C.

Can be extended to show signal strength, frequency, and encryption type.

🔹 Technologies Used

C Programming Language

Linux Wireless Extensions (<linux/wireless.h>)

System Calls & Sockets (ioctl, socket)

GCC Compiler for building the project

🔹 Use Cases

Learning system-level programming with C.

Understanding how wireless networks are scanned at the OS level.

Basis for building more advanced tools (e.g., Wi-Fi analyzers, penetration testing tools, or network monitoring applications).
