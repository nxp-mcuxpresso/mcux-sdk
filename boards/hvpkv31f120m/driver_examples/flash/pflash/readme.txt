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
- HVP-KV31F120M board
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

 Total Program Flash Size:      256 KB, Hex: (0x40000)

 Program Flash Sector Size:     4 KB, Hex: (0x1000)

 Flash is UNSECURE!

 Erase a sector of flash

 Successfully Erased Sector 0x3f000 -> 0x40000

 Program a buffer to a sector of flash

 Successfully Programmed and Verified Location 0x3f000 -> 0x3f010

 End of PFlash Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
