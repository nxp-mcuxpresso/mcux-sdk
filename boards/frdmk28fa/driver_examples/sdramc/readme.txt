Overview
========

The sdramc example shows how to use SDRAM controller driver to initialize the external SDRAM chip.
After the SDRAM initialization, SDRAM address access is very simple.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- J-Link ARM
- FRDM-K28FA board
- Personal Computer

Board settings
==============


Prepare the Demo
================
1.  Connect a mini/micro USB cable between the PC host and the USB port on the board.
2.  Connect the J-link between the PC and the board. 
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

SDRAM Example Start!  

SDRAM Memory Write Start, Start Address 0x70000000, Data Length 4096 ! 

SDRAM Write finished!

SDRAM Read Start, Start Address 0x70000000, Data Length 4096 !

SDRAM Read finished!

SDRAM Write Data and Read Data Compare Start! 

SDRAM Write Data and Read Data Succeed.

SDRAM Example End.

