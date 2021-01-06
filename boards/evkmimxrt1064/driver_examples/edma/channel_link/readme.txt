Overview
========
The EDMA channel link example is a simple demonstration program that uses the SDK software.
It excuates channel link transfer using the SDK EDMA drivers.
The purpose of this example is to show how to use the EDMA and to provide a simple example for
debugging and further development, it demostrates how to use the minor loop link and major loop link:
Since each transfer request can be divided into MAJOR_LOOPS_COUNTS * MINOR_LOOPS_BYTES,
such as you want to request DMA transfer 8 bytes total, 4 bytes each request, then MAJOR_LOOPS_COUNTS = 2, MINOR_LOOPS_BYTES = 4.
The minor loop channel linking occurs at the completion of the minor loop 4 byte transferred.
The major loop channel linking is occurs at the major loop exhausted.
The example demostrate the channel link transfer by the feature of edma:
1. minor loop channel link
                                                                                                                   +-----------------------------+                          +----------------------+
                                                                                                                   | channel 1 transfer complete | -----------------------> |   example complete   |
                                                                                                                   +-----------------------------+                          +----------------------+
                                                                                                                     ^
                                                                                                                     | major loop finished
                                                                                                                     |
                        +-----------------------------+     +-------------------------------+  trigger channel 1   +-----------------------------+  major loop not finish   +----------------------+     +-------------------------------+
                        |    channel 0 minor loop     | --> | channel 0 minor loop finished | -------------------> |    channel 1 major loop     | -----------------------> | channel 1 minor loop | --> | channel 1 minor loop finished |
                        +-----------------------------+     +-------------------------------+                      +-----------------------------+                          +----------------------+     +-------------------------------+
                          ^                                                                                                                                                                                |
                          | major loop not finish                                                                                                                                                          |
                          |                                                                                                                                                                                |
+-----------------+     +-----------------------------+      trigger channel 0                                                                                                                             |
| channel 0 start | --> |    channel 0 major loop     | <--------------------------------------------------------------------------------------------------------------------------------------------------+
+-----------------+     +-----------------------------+
                          |
                          | major loop finished
                          v
                        +-----------------------------+
                        | channel 0 transfer complete |
                        +-----------------------------+

2. major loop channel link

                         channel 1 minor loop finished
  +---------------------------------------------------------+
  |                                                         v
+----------------------+  major loop not finish           +-------------------------------+  major loop finished     +-----------------------------+     +-------------------------------+
| channel 1 minor loop | <------------------------------- |     channel 1 major loop      | -----------------------> | channel 1 transfer complete | --> |       example complete        |
+----------------------+                                  +-------------------------------+                          +-----------------------------+     +-------------------------------+
                                                            ^
                                                            | trigger channel 1
                                                            |
                                                          +-------------------------------+                          +-----------------------------+
                                                          | channel 0 major loop finished | -----------------------> | channel 0 transfer complete |
                                                          +-------------------------------+                          +-----------------------------+
                                                            ^
                                                            |
                                                            |
+----------------------+                                  +-------------------------------+  major loop not finish   +-----------------------------+     +-------------------------------+
|   channel 0 start    | -------------------------------> |     channel 0 major loop      | -----------------------> |    channel 0 minor loop     | --> | channel 0 minor loop finished |
+----------------------+                                  +-------------------------------+                          +-----------------------------+     +-------------------------------+
                                                            ^                                                                                              |
                                                            +----------------------------------------------------------------------------------------------+


Please reference user manual for the detail of the feature.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

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
edma minor loop link start

0	0	0	0	0	0	0	0	

edma minor loop link finished

1	2	3	4	5	6	7	8	

edma major loop link start

0	0	0	0	0	0	0	0	

edma major loop link finished

1	2	3	4	5	6	7	8	
~~~~~~~~~~~~~~~~~~~~~

