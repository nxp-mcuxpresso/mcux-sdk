Overview
========
The EDMA interleave transfer example is a simple demonstration program that uses the SDK software.
It excuates interleave transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the interleave feature of EDMA and to provide a simple example for
debugging and further development.
The example demostrates the interleave transfer by features:
1. edma minor loop offset.

              +---------------------+                          +------------------+
              |  transfer complete  | -----------------------> | example complete |
              +---------------------+                          +------------------+
                ^
                |
                |
              +---------------------+
              | major loop finished |
              +---------------------+
                ^
                |
                |
+-------+     +---------------------+  major loop not finish   +------------------+     +---------------------+
| start | --> |     major loop      | -----------------------> |    minor loop    | --> | minor loop finished |
+-------+     +---------------------+                          +------------------+     +---------------------+
                ^                     dest/source address offset                          |
                +-------------------------------------------------------------------------+

2. edma source/destination address offset.

              +---------------------+                          +------------------+
              |  transfer complete  | -----------------------> | example complete |
              +---------------------+                          +------------------+
                ^
                |
                |
              +---------------------+
              | major loop finished |
              +---------------------+
                ^
                |
                |
+-------+     +---------------------+  major loop not finish   +------------------+  dest/source address offset   +---------------------+
| start | --> |     major loop      | -----------------------> |    minor loop    | ----------------------------> | minor loop finished |
+-------+     +---------------------+                          +------------------+                               +---------------------+
                ^                                                                                                   |
                +---------------------------------------------------------------------------------------------------+


Please reference user manual for the detail of the feature.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KV31F board
- Personal Computer

Board settings
==============
The EDMA memory to memory demo does not call for any special hardware configurations.

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
EDMA interleave transfer example.



edma signle transfer interleave start

0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	

edma signle transfer interleave finished

1	0	2	0	3	0	4	0	5	0	6	0	7	0	8	0	

edma minor loop interleave start

0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	
~~~~~~~~~~~~~~~~~~~~~


