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
- MIMX8QX MEK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
Base Board is needed to run this demo.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board.
2.  Connect a micro USB cable between the host PC and the J11 USB port on the cpu board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- Read Accelerometer Value

Found a FXOS8700 on board , the device address is 0x1C .

The accel values:

status_reg = 0xff , x =    60 , y =   -80 , z =  2094

status_reg = 0xff , x =    54 , y =   -73 , z =  2088

status_reg = 0xff , x =    54 , y =   -77 , z =  2096

status_reg = 0xff , x =    57 , y =   -79 , z =  2096

status_reg = 0xff , x =    57 , y =   -83 , z =  2089

status_reg = 0xff , x =    55 , y =   -78 , z =  2102

status_reg = 0xff , x =    56 , y =   -77 , z =  2097

status_reg = 0xff , x =    57 , y =   -77 , z =  2085

status_reg = 0xff , x =    59 , y =   -78 , z =  2094

status_reg = 0xff , x =    56 , y =   -79 , z =  2093

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
