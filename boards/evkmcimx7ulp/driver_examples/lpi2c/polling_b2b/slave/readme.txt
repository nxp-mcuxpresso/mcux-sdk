Overview
========
The lpi2c_polling_b2b_slave example shows how to use lpi2c driver as slave to do board to board transfer
with a polling master:

In this example, one lpi2c instance as slave and another lpi2c instance on the other board as master. Master sends a
piece of data to slave, and receive a piece of data from slave. This example checks if the data received from
slave is correct.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- two MCIMX7ULP-EVK boards
- J-Link Debug Probe
- 5V power supply
- Personal Computer

Board settings
==============
LPI2C one board:
  + Transfer data from MASTER_BOARD to SLAVE_BOARD of LPI2C interface, LPI2C3 pins of MASTER_BOARD are connected with
    LPI2C3 pins of SLAVE_BOARD
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER_BOARD        CONNECTS TO         SLAVE_BOARD
Pin Name     Board Location     Pin Name     Board Location
I2C3_SCL     TP24               I2C3_SCL     TP24
I2C3_SDA     TP26               I2C3_SDA     TP26
GND                             GND
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Please note this application can't support running with Linux BSP! ####

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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
LPI2C board2board polling example -- Slave transfer.


End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
