Overview
========
The i2c_read_accel_value example shows how to use I2C driver to communicate with an i2c device:

 1. How to use the i2c driver to read a i2c device who_am_I register.
 2. How to use the i2c driver to write/read the device registers.

In this example, the values of three-axis accelerometer print to the serial terminal on PC through
the virtual serial port on board.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-KV11Z board
- Personal Computer

Board settings
==============
No special setting is needed.

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

I2C example -- Read Accelerometer Value
Found an MMA8451 on board , the device address is 0x1d .
The accel values:
status_reg = 0xff , x =  -105 , y =  -229 , z =  2020
status_reg = 0xff , x =  -107 , y =  -223 , z =  2014
status_reg = 0xff , x =  -109 , y =  -227 , z =  2018
status_reg = 0xff , x =   -97 , y =  -235 , z =  2023
status_reg = 0xff , x =  -106 , y =  -225 , z =  2020
status_reg = 0xff , x =  -101 , y =  -227 , z =  2032
status_reg = 0xff , x =  -104 , y =  -230 , z =  2023
status_reg = 0xff , x =  -106 , y =  -230 , z =  2025
status_reg = 0xff , x =  -104 , y =  -230 , z =  2013
status_reg = 0xff , x =  -105 , y =  -230 , z =  2015

End of I2C example .
