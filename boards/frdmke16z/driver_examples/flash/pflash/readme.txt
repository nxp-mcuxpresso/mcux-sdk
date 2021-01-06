Overview
========
The pflash example shows how to use flash driver to operate program flash:



Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE16Z board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1. Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
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
When the example runs successfully, the following message is displayed in the terminal

~~~~~~~~~~~~

 PFlash Example Start 

 PFlash Information: 
 Total Program Flash Size:	64 KB, Hex: (0x10000)
 Program Flash Sector Size:	1 KB, Hex: (0x400) 
 Flash is UNSECURE!

 Erase a sector of flash
 Successfully Erased Sector 0xfc00 -> 0x10000

 Program a buffer to a sector of flash 
 Successfully Programmed and Verified Location 0xfc00 -> 0xfc10 

 End of PFlash Example 
~~~~~~~~~~~~
