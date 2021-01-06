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

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- J-Link Debug Probe
- 5V power supply
- Personal Computer

Board settings
==============
The example requires doing connection between FLEXIO pins and LPI2C pins.
Please use two dupontline to touch the test point (TP) on MCIMX7ULP-EVK base board as following:
- TP24, TP25 connected
- TP26, TP27 connected

#### Please note this application can't support running with Linux BSP! ####

#### Please note this application can only run well with RAM link file!
If run it in QSPI flash in place, there's high latency when instruction fetch cache miss. The FlexIO I2C
has critical timing requirement that I2C data must be read/write in time, otherwise the state machine works
abnormally. ####

Prepare the Demo
================
1.  Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2.  Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
FlexIO I2C example read accelerometer value
Found a FXOS8700 on board, the device address is 0x1E. 
The accel values:
status_reg = 0xff , x =   180 , y =   -47 , z =  2024 
status_reg = 0xff , x =    25 , y =     4 , z =  2029 
status_reg = 0xff , x =   130 , y =   -98 , z =  2115 
status_reg = 0xff , x =   103 , y =   -84 , z =  2137 
status_reg = 0xff , x =    57 , y =   -55 , z =  2093 
status_reg = 0xff , x =    80 , y =   -53 , z =  2066 
status_reg = 0xff , x =    93 , y =   -70 , z =  2064 
status_reg = 0xff , x =    96 , y =   -70 , z =  2072 
status_reg = 0xff , x =    89 , y =   -64 , z =  2067 
status_reg = 0xff , x =    67 , y =   -60 , z =  2111 

End of I2C example .
~~~~~~~~~~~~~~~~~~~~~
