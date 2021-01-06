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
- FRDM-K28FA board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
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
~~~~~~~~~~~~
PFlash Example Start 

 PFlash Information: 
 Total Program Flash Size:	2048 KB, Hex: (0x200000)
 Program Flash Sector Size:	4 KB, Hex: (0x1000) 
 Flash is UNSECURE!

 Erase a sector of flash
 Successfully Erased Sector 0x1fe000 -> 0x1ff000

 Program a buffer to a sector of flash 
 Successfully Programmed and Verified Location 0x1fe000 -> 0x1fe010 

 End of PFlash Example 
~~~~~~~~~~~~
