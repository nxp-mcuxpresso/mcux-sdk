Overview
========
The pflash example shows how to use flash driver to operate program flash:



Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
This Example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
These instructions are displayed/shown on the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PFlash Example Start
 PFlash Information:
 Total Program Flash Size:      1024 KB, Hex: (0x100000)
 Program Flash Sector Size:     4 KB, Hex: (0x1000)
 Flash is UNSECURE!
 Erase a sector of flash
 Successfully Erased Sector 0xfe000 -> 0xff000
 Program a buffer to a sector of flash
 Successfully Programmed and Verified Location 0xfe000 -> 0xfe010
 End of PFlash Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
