Overview
========
The lpi2c_read_accel_value example shows how to use LPI2C driver to communicate with an lpi2c device:

 1. How to use the lpi2c driver to read a lpi2c device who_am_I register.
 2. How to use the lpi2c driver to write/read the device registers.

In this example, the values of three-axis accelerometer print to the serial terminal on PC through
the virtual serial port on board.

Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- Read Accelerometer Value

Found a FXOS8700 on board , the device address is 0x1e .

The accel values:

status_reg = 0xff , x =    24 , y =   -66 , z =  2119
status_reg = 0xff , x =    24 , y =   -65 , z =  2120
status_reg = 0xff , x =    27 , y =   -68 , z =  2112
status_reg = 0xff , x =    29 , y =   -64 , z =  2114
status_reg = 0xff , x =    21 , y =   -66 , z =  2114
status_reg = 0xff , x =    31 , y =   -69 , z =  2124
status_reg = 0xff , x =    28 , y =   -65 , z =  2117
status_reg = 0xff , x =    28 , y =   -67 , z =  2115
status_reg = 0xff , x =    24 , y =   -64 , z =  2114
status_reg = 0xff , x =    28 , y =   -73 , z =  2115

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
