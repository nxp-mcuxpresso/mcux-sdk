Overview
========
The KBI Example project is a demonstration program that uses the KSDK software to use
keyboard interrupt.
The example uses one KBI pin to generate a raising edge interrupt to show the example.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini USB cable
- Two FRDM-KE04Z boards
- Personal Computer

Board settings
==============
connect 20# & 18# on J2.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KBI Driver Example Start.

 The KBI keyboard interrupt has happened!

 KBI Driver Example End.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
