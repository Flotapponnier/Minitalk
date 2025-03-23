# Minitalk - 42 Project

## Introduction
Minitalk is a small but practical project that involves creating a server and client communication system using Unix signals. The goal is to send and receive messages between processes, utilizing the low-level concept of signals, which will allow you to dive deep into system programming and bitwise operations. This project teaches fundamental programming concepts like inter-process communication (IPC), signals, and bit manipulation in C.

__Learning Objectives__
Bitwise Operations: One of the key techniques used in this project is bitwise operations. Specifically, you manipulate individual bits of a character to represent data as a series of signals.

Signals: This project helps you understand how Unix signals work (specifically SIGUSR1 and SIGUSR2) and how they can be used for inter-process communication.

Process Management: You'll also work with process IDs (PIDs) and use system calls like kill, pause, and signal to send and receive messages.

Memory Management: This project involves dynamic memory management, especially in managing strings and message buffers.

## How It Works

__Client Code__
The client sends a message to the server by converting each character in the message into bits. Each bit is sent as a signal to the server. The client works as follows:

Input: The client takes in the server's process ID (PID) and the message to send.

Send Signal: For each character in the message, the client breaks it into its 8 bits and sends each bit as a signal:

0 bit: Sends SIGUSR1.

1 bit: Sends SIGUSR2.

Wait for Acknowledgment: After sending the message, the client waits for an acknowledgment from the server.

__Server Code__
The server listens for incoming signals (SIGUSR1 and SIGUSR2). It works like this:

Signal Reception: The server waits for SIGUSR1 or SIGUSR2. Each signal corresponds to a bit of the message.

Reconstruct Message: The server reconstructs the received message byte by byte, based on the incoming signals.

Display Message: When a full byte (8 bits) is received, the server displays the character on the screen. If a null byte ('\0') is received, it prints a newline and terminates the message.

__Bonus Features__
The bonus part of the project adds two features:

Acknowledgment: After receiving the complete message, the server sends a SIGUSR2 signal back to the client as an acknowledgment.

Null Byte: The client sends a special signal sequence to indicate the end of the message, represented by sending 8 consecutive SIGUSR1 signals.

## Code Breakdown
__Client:__
send_bit(pid, a): Sends each bit of the character a to the server.

main(): Reads the arguments, validates them, and sends the message bit by bit.

__Server:__
handle(): Listens for incoming signals and reconstructs the message byte by byte.

main(): Sets up the signal handlers and keeps the server running.

__Bonus Client:__
send_bit(pid, a): Same as the main client but with slightly reduced sleep time to improve message delivery speed.

send_null(pid): Sends 8 consecutive SIGUSR1 signals to indicate the end of the message.

handler_sig(): Waits for an acknowledgment from the server using SIGUSR2.

main(): Same as the client but with added acknowledgment handling.

__Bonus Server:__
handle(): Similar to the main server but also sends a signal back to the client for acknowledgment.

main(): Waits for incoming signals using the bonus version of the signal handler.

__How to Compile__
To compile the project, use the following command:

```sh
make
```
This will create two executables: client and server.

__Running the Program__
Start the Server:

```sh
./server
```
Run the Client:

```sh
./client <server_pid> <message>
Replace <server_pid> with the server's PID and <message> with the message you want to send.
```

## Conclusion
The Minitalk project is an excellent exercise in understanding low-level systems programming and inter-process communication using signals. 
It helps you grasp essential concepts like bitwise operations, signal handling, and process management. 
By completing this project, you’ll enhance your understanding of how processes communicate in Unix-like systems, preparing you for more advanced programming challenges in systems-level programming.

