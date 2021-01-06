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
- Micro USB cable
- TWR-KM35Z75M board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
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
When the demo runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DMA channel link example begin.



Destination Buffer:

0	0	0	0	



DMA channel link example finish.



Destination Buffer 0:

1	2	3	4	

Destination Buffer 1:

1	2	3	4	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

