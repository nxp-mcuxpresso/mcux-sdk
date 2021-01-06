Overview
========
The DMA wrap transfer example is a simple demonstration program that uses the SDK software.
It executes two burst transfer from source buffer to destination buffer using the SDK DMA drivers.
The purpose of this example is to show how to use the DMA wrap feature and to provide a simple example for
debugging and further development.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- LPCXpresso55S28 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
Note: MCUXpresso IDE project default debug console is semihost
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (P6) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~
DMA wrap transfer example begin.

Destination address wrap transfer:
5	6	7	8	0	0	0	0
Source address wrap transfer:
1	2	3	4	1	2	3	4

DMA wrap transfer example finish.

~~~~~~~~~~~~~~~~~~~~~
