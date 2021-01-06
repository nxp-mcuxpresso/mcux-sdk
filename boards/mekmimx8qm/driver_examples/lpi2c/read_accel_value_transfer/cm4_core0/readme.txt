Overview
========
The lpi2c_read_accel_value example shows how to use LPI2C driver to communicate with an lpi2c device:

 1. How to use the lpi2c driver to read a lpi2c device who_am_I register.
 2. How to use the lpi2c driver to write/read the device registers.

In this example, the values of three-axis accelerometer print to the serial terminal on PC through
the virtual serial port on board.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK Board
- MCIMX8-8X-BB
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####
This example aims to show the basic usage of the IP's function, some of the used Pads/Resources are also used by Cortex-A core.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- Read Accelerometer Value
Found an FXOS8700 on board , the device address is 0x1d . 
The accel values:
status_reg = 0xff , x =    49 , y =   -35 , z =  2084 
status_reg = 0xff , x =    49 , y =   -43 , z =  2099 
status_reg = 0xff , x =    49 , y =   -45 , z =  2071 
status_reg = 0xff , x =    48 , y =   -34 , z =  2095 
status_reg = 0xff , x =    53 , y =   -42 , z =  2056 
status_reg = 0xff , x =    55 , y =   -42 , z =  2092 
status_reg = 0xff , x =    57 , y =   -44 , z =  2057 
status_reg = 0xff , x =    52 , y =   -32 , z =  2107 
status_reg = 0xff , x =    44 , y =   -43 , z =  2111 
status_reg = 0xff , x =    48 , y =   -38 , z =  2087 

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
