## Overview
-----------------------------------------------------------------------------------------
The Hello World demo application provides a sanity check for the new SDK build environments
and board bring up. The Hello World demo prints the "hello world." string to the terminal
using the SDK UART drivers. The purpose of this demo is to show how to use the UART, and
to provide a simple project for debugging and further development.

## Functional description
-----------------------------------------------------------------------------------------
This demo is just for bring up a new SDK build environments on board.
Board will initialize the hardware configuration, then print a "hello world." string to 
the terminal emulator on PC, and print out the received characters in while loop of 
main routine.

## Toolchain supported
---------------------
- IAR embedded Workbench 8.50.5
- Keil MDK 5.31
- GCC ARM Embedded  9.2.1
- MCUXpresso 11.2.0

## Hardware Requirements
------------------------
- Mini/micro USB cable
- LPCXpresso824MAX board
- Personal Computer

## Board Settings
------------------------
Connect SJ9: 2-3

## Run the Demo
------------------------
1. Connect a micro USB cable between the PC host and the CMSIS DAP port(J3 on the board).

2. Open a serial terminal with the following settings:
   - 9600 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control

3. Choose an IDE, building the project and download the program to the target board.
   More information about how to compile and program the project can refer to the 

   [Getting Started with MCUXpresso SDK](../../../../docs/Getting Started with MCUXpresso SDK.pdf).

4. Launch the debugger in your IDE to begin running the demo.

## Expected Result
------------------------
- Board will print "hello world." to the terminal, and if users input some characters,
  board will send them back to the terminal emulator immediately.

