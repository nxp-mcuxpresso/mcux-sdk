Overview
========
The EDMA memory to memory example is a simple demonstration program that uses the SDK software.
It excuates one shot transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the EDMA and to provide a simple example for
debugging and further development.
                                                                     +---------------------------+                          +------------------+
                                                                     | tcd 1 major loop finished | -----------------------> | example complete |
                                                                     +---------------------------+                          +------------------+
                                                                       ^
                                                                       |
                                                                       |
              +---------------------------+  load tcd1               +---------------------------+  major loop not finish   +------------------+
              | tcd 0 major loop finished | -----------------------> |     tcd 1 major loop      | -----------------------> | tcd 1 minor loop |
              +---------------------------+                          +---------------------------+                          +------------------+
                ^                                                      ^                           minor loop finished        |
                |                                                      +------------------------------------------------------+
                |
+-------+     +---------------------------+  major loop not finish   +---------------------------+
| start | --> |     tcd 0 major loop      | -----------------------> |     tcd 0 minor loop      |
+-------+     +---------------------------+                          +---------------------------+
                ^                           minor loop finished        |
                +------------------------------------------------------+

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1015 board
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
EDMA scatter gather transfer example begin.



Destination Buffer:

0	0	0	0	0	0	0	0	



EDMA scatter gather transfer example finish.



Destination Buffer:

1	2	3	4	5	6	7	8	
~~~~~~~~~~~~~~~~~~~~~


Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
3. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J41.
4. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
