Overview
========
The DMA ring buffer example is a simple demonstration program that uses the SDK software.It demostrates how to implement ring buffer using the SDK DMA drivers.The purpose of this example is to show how to use the DMA and to provide a simple example for debugging and further development.
There are two channels involved in this demo:
1. channel 0 is used for handling the ring buffer transfer
2. channel 1 is used for restart channel 0.

+-------+     +-----------------------------+
| start | --> |     channel 0 transfer      | <+
+-------+     +-----------------------------+  |
                |                              |
                | finished                     |
                v                              |
              +-----------------------------+  |
              | channel 1 restart channel 0 | -+
              +-----------------------------+

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
DMA ring buffer example begin.



Destination Buffer:

0	0	0	0	



DMA ring buffer example finish.



Destination Buffer:

8	9	10	11	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

