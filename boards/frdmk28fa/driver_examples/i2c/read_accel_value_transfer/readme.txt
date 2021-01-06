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
- Mini/Micro USB cable
- FRDM-K28FA board
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

I2C example -- Read Accelerometer Value
Found an FXOS8700 on board , the device address is 0x1c . 
The accel values:
status_reg = 0xff , x =    32 , y =  -100 , z =  2087 
status_reg = 0xff , x =    38 , y =   -97 , z =  2082 
status_reg = 0xff , x =    38 , y =   -94 , z =  2082 
status_reg = 0xff , x =    38 , y =   -92 , z =  2088 
status_reg = 0xff , x =    36 , y =   -95 , z =  2077 
status_reg = 0xff , x =    37 , y =  -100 , z =  2087 
status_reg = 0xff , x =    46 , y =   -96 , z =  2087 
status_reg = 0xff , x =    43 , y =   -97 , z =  2086 
status_reg = 0xff , x =    37 , y =   -96 , z =  2085 
status_reg = 0xff , x =    37 , y =   -92 , z =  2079 

End of I2C example .


