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
- Mini USB cable
- FRDM-KL27Z board
- Personal Computer

Board settings
==============
The DMA memroy to memory demo does not call for any special hardware configurations.

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
DMA ring buffer example begin.



Destination Buffer:

0	0	0	0	



DMA ring buffer example finish.



Destination Buffer:

8	9	10	11	
~~~~~~~~~~~~~~~~~~~~~


