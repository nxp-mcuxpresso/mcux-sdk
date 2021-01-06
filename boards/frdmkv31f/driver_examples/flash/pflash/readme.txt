Overview
========
The pflash example shows how to use flash driver to operate program flash:



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
The log below shows the output of the hello world demo in the terminal window:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PFlash Example Start

 PFlash Information:

 Total Program Flash Size:      512 KB, Hex: (0x80000)

 Program Flash Sector Size:     2 KB, Hex: (0x800)

 Flash is UNSECURE!

 Erase a sector of flash

 Successfully Erased Sector 0x7f800 -> 0x80000

 Program a buffer to a sector of flash

 Successfully Programmed and Verified Location 0x7f800 -> 0x7f810

 End of PFlash Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
