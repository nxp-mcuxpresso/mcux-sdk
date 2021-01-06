Overview
========
The flexio_i2c_read_accel_value example shows how to use FLEXIO I2C  Master driver to communicate with an i2c device:

 1. How to use the flexio i2c master driver to read a i2c device who_am_I register.
 2. How to use the flexio i2c master driver to write/read the device registers.

In this example, the values of three-axis accelerometer print to the serial terminal on PC through
the virtual serial port on board.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1010 board
- Personal Computer

Board settings
==============
- remove J64,J63
- To make this example work, connections needed to be as follows:

    FLEXIO_I2C        connected to  LPI2C1
SCL     J26-8           -->        J57-20
SDA     J26-6           -->        J57-18

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
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~
FlexIO I2C example read accelerometer value

Found a FXOS8700 on board , the device address is 0x1D.

The accel values:

status_reg = 0xff , x =   -50 , y =    11 , z =  2045
status_reg = 0xff , x =   -50 , y =     9 , z =  2031
status_reg = 0xff , x =   -49 , y =    12 , z =  2032
status_reg = 0xff , x =   -50 , y =     6 , z =  2046
status_reg = 0xff , x =   -51 , y =     8 , z =  2040
status_reg = 0xff , x =   -45 , y =     4 , z =  2032
status_reg = 0xff , x =   -52 , y =    13 , z =  2042
status_reg = 0xff , x =   -53 , y =    12 , z =  2041
status_reg = 0xff , x =   -51 , y =     8 , z =  2048
status_reg = 0xff , x =   -52 , y =     9 , z =  2036

End of I2C example .
~~~~~~~~~~~~~~~~~~~~~

Note:
if sensor chip(U26) is not welded on the board, the log would be seen on the OpenSDA terminal like:

FlexIO I2C example read accelerometer value

Not a successful i2c communication

End of I2C example .

Note:
Make sure connect FLEXIO_I2C to LPI2C1 after power cycling/resetting the board.
Pulling up GPIO_EMC_20 and GPIO_EMC_26 will have impact on boot process.

Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J41.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
