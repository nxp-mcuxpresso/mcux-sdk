Overview
========
The lpi2c_functional_interrupt example shows how to use lpi2c functional driver to build a interrupt based application:

In this example , one lpi2c instance used as lpi2c master and another lpi2c instance used as lpi2c slave .
1. lpi2c master send data using interrupt to lpi2c slave in interrupt .
2. lpi2c master read data using interrupt from lpi2c slave in interrupt .
3. The example assumes that the connection is OK between master and slave, so there's NO error handling code.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
To make lpi2c example work(M4), connections needed to be as follows:
        LPI2C1        connected to   LPI2C0
SCL     PTB14(J1-10)    -->          PTC10(J2-20)
SDA     PTB6(J2-6)      -->          PTC9(J2-18)
To make lpi2c example work(M0), connections needed to be as follows:
        LPI2C3        connected to   LPI2C0
SCL     PTB15(J3-15)    -->          PTC10(J2-20)
SDA     PTB16(J3-13)    -->          PTC9(J2-18)

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
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
The following message shows in the terminal if the example runs successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- MasterFunctionalInterrupt_SlaveFunctionalInterrupt.
Master will send data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f

Slave received data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f

This time , slave will send data:
0xff  0xfe  0xfd  0xfc  0xfb  0xfa  0xf9  0xf8
0xf7  0xf6  0xf5  0xf4  0xf3  0xf2  0xf1  0xf0
0xef  0xee  0xed  0xec  0xeb  0xea  0xe9  0xe8
0xe7  0xe6  0xe5  0xe4  0xe3  0xe2  0xe1  0xe0

Master received data :
0xff  0xfe  0xfd  0xfc  0xfb  0xfa  0xf9  0xf8
0xf7  0xf6  0xf5  0xf4  0xf3  0xf2  0xf1  0xf0
0xef  0xee  0xed  0xec  0xeb  0xea  0xe9  0xe8
0xe7  0xe6  0xe5  0xe4  0xe3  0xe2  0xe1  0xe0

End of I2C example .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
