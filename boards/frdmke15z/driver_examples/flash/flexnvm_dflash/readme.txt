Overview
========
The flexnvm_dflash example shows how to use flash driver to operate data flash:



Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE15Z board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
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
 FlexNVM DFlash example Start
 Flash is UNSECURE!
 DFlash Information: 
 Data Flash Base Address: (xx)
 Data Flash Total Size: xx KB, hex: (xx)
 Data Flash Sector Size: xx KB, hex: (xx)
 Erase a sector of Data Flash
 Successfully Erased Sector xx -> xx
 Program a buffer to a sector of Data Flash
 Successfully Programmed and Verified Location xx -> xx


 End of FlexNVM Dflash example
~~~~~~~~~~~~
