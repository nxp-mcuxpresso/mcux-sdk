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
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
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
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~
edma signle transfer interleave start

0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	

edma signle transfer interleave finished

1	0	2	0	3	0	4	0	5	0	6	0	7	0	8	0	

edma minor loop interleave start

0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	

edma minor loop interleave finished

1	2	0	4	5	0	7	8	0	10	11	0	13	14	0	0
~~~~~~~~~~~~~~~~~~~~~

