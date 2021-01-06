Overview
========
The DMA channel link example is a simple demonstration program that uses the SDK software.
It executes channel link transfer using the SDK DMA drivers.
The purpose of this example is to show how to use the DMA and to provide a simple example for
debugging and further development.
                  not finished                                   not finished
                +----------------+                             +----------------+
                v                |                             v                |
+-------+     +--------------------+  each request trigger   +--------------------+  finished   +------------------+
| start | --> | channel 0 transfer | ----------------------> | channel 1 transfer | ----------> | example complete |
+-------+     +--------------------+                         +--------------------+             +------------------+

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L2B board
- Personal Computer

Board settings
==============
The DMA memory to memory demo does not call for any special hardware configurations.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~
DMA channel link example begin.



Destination Buffer:

0	0	0	0	



DMA channel link example finish.



Destination Buffer 0:

1	2	3	4	
Destination Buffer 1:

1	2	3	4
~~~~~~~~~~~~~~~~~~~~~	

