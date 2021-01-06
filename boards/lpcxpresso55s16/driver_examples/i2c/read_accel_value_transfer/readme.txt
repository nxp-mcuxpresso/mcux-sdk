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
- LPCXpresso55S16 boards
- Personal Computer

Board settings
==============
No special settings are required.
The jumper setting:
    Default jumpers configuration does not work,  you will need to add JP20 and JP21 (JP22 optional for ADC use)

# Prepare the Demo

1. Connect a micro USB cable between the PC host and the LPC-Link USB port (J1) on the board.
2. Open a serial terminal on PC for JLink serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

I2C example -- Read Accelerometer Value
Found an MMA8652 on board , the device address is 0x1d . 
The accel values:
status_reg = 0xff , x =  -192 , y =   188 , z =  2152 
status_reg = 0xff , x =  -168 , y =   192 , z =  2160 
status_reg = 0xff , x =  -180 , y =   152 , z =  2144 
status_reg = 0xff , x =  -200 , y =   132 , z =  2064 
status_reg = 0xff , x =  -192 , y =   108 , z =  2196 
status_reg = 0xff , x =  -232 , y =   136 , z =  2092 
status_reg = 0xff , x =  -260 , y =   192 , z =  1992 
status_reg = 0xff , x =  -240 , y =   304 , z =  1968 
status_reg = 0xff , x =  -208 , y =   336 , z =  1976 
status_reg = 0xff , x =  -208 , y =   296 , z =  1900 

End of I2C example .
