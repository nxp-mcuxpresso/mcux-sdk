## Overview
-----------------------------------------------------------------------------------------
The DMA wrap transfer example is a simple demonstration program that uses the SDK software.
It executes two burst transfer from source buffer to destination buffer using the SDK DMA drivers.
The purpose of this example is to show how to use the DMA wrap feature and to provide a simple 
example for debugging and further development.

## Functional description
-----------------------------------------------------------------------------------------
This example shows the usage of burst transfer from source buffer to destination buffer.

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
No special settings are required.

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
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~
DMA wrap transfer example begin.

Destination address wrap transfer:
5	6	7	8	0	0	0	0
Source address wrap transfer:
1	2	3	4	1	2	3	4

DMA wrap transfer example finish.
~~~~~~~~~~~~~~~~~~~~~
