Overview
========
The EEprom example shows how to use flash driver to operate program EEprom:



Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KE02z40m board
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
~~~~~~~~~~~~~
 EEPROM example Start
 
 EEPROM Information:
 EEPROM Base Address: xx
 Total EEPROM Size: xx B
 EEPROM Sector Size: xx B
 Erase a sector of EEPROM
 Program a buffer to a sector of EEPROM
 Successfully Programmed and Verified Location xx -> xx
 
 End of EEPROM example
~~~~~~~~~~~~~
