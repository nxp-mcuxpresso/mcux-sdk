Overview
========
The flexnvm_flexram example shows how to use flash driver to operate flexram as traditional RAM:



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
When the example runs successfully, the following message is displayed in the terminal

~~~~~~~~~~~~
FlexNVM EEprom Example Start 

 Flash is UNSECURE!

 There is no available EEprom (FlexNVM) on this Device by default.
 Example is trying to configure FlexNVM block as EEprom.
 Perform a system reset 
 FlexNVM EEprom Example Start 

 Flash is UNSECURE!

 EEprom Information: 
 EEprom Base Address:	262144 KB, Hex: (0x10000000) 
 EEprom Total Size:	1 KB, Hex: (0x400)
 Program a buffer to a sector of EEprom
 Successfully Programmed Location 0x14000000 -> 0x14000010 

 End of FlexNVM EEprom Example 
~~~~~~~~~~~~
