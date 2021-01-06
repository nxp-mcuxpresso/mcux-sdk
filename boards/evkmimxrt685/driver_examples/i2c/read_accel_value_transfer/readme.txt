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
- Micro USB cable
- EVK-MIMXRT685 board
- Personal Computer

Board settings
==============
Make sure J15 and J30 are shorted.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J5) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
The following message shows in the terminal if the example runs successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
I2C example -- Read Accelerometer Value
Found an FXOS8700 on board , the device address is 0x1e.
The accel values:
status_reg = 0xff , x =   -88 , y =   -84 , z =  2084 
status_reg = 0xff , x =   -84 , y =   -88 , z =  2096 
status_reg = 0xff , x =   -84 , y =   -88 , z =  2092 
status_reg = 0xff , x =   -76 , y =   -88 , z =  2104 
status_reg = 0xff , x =   -80 , y =   -88 , z =  2096 
status_reg = 0xff , x =   -84 , y =   -80 , z =  2100 
status_reg = 0xff , x =   -80 , y =   -80 , z =  2080 
status_reg = 0xff , x =   -72 , y =   -92 , z =  2088 
status_reg = 0xff , x =   -84 , y =   -88 , z =  2084 
status_reg = 0xff , x =   -88 , y =   -88 , z =  2104 

End of I2C example .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
