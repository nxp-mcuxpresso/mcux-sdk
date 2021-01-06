Overview
========
The EDMA wrap transfer example is a simple demonstration program that uses the SDK software.
It excuates wrap transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the wrap feature of EDMA and to provide a simple example for
debugging and further development.
The example demostrate the wrap transfer by the feature of EDMA:
1. edma modulo feature
                                       minor loop finished
                +-------------------------------------------------+
                v                                                 |
+-------+     +----------------------+  major loop not finish   +----------------------------------------+  source address range not hit modulo range   +---------------------------+
| start | --> |      major loop      | -----------------------> |               minor loop               | -------------------------------------------> | source address increament |
+-------+     +----------------------+                          +----------------------------------------+                                              +---------------------------+
                |                                                 |
                | major loop finished                             | source address range hit modulo range
                v                                                 v
              +----------------------+                          +----------------------------------------+
              |  example complete    |                          |          source address wrap           |
              +----------------------+                          +----------------------------------------+

2. edma major loop offet feature.

              +----------------------+                          +--------------------------------------------------------------+  trigger again   +------------------+
              |  transfer complete   | -----------------------> | source/destination address wrap(SLAST/DLAST) to origin value | ---------------> | example complete |
              +----------------------+                          +--------------------------------------------------------------+                  +------------------+
                ^
                | major loop finished
                |
+-------+     +----------------------+  major loop not finish   +--------------------------------------------------------------+
| start | --> |      major loop      | -----------------------> |                          minor loop                          |
+-------+     +----------------------+                          +--------------------------------------------------------------+
                ^                      minor loop finished        |
                +-------------------------------------------------+


Please reference user manual for the detail of the feature.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K28FA board
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
EDMA wrap transfer example.



edma modulo wrap start

0	0	0	0	0	0	0	0	

EDMA modulo wrap finished.

1	2	3	4	1	2	3	4	

edma major loop wrap start

0	0	0	0	0	0	0	0	

edma major loop wrap finished

1	2	3	4	5	6	7	8	
~~~~~~~~~~~~~~~~~~~~~


