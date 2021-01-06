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
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- Two FRDM-KE16Z boards
- Personal Computer

Board settings
==============
LPI2C one board:
  + Transfer data from MASTER_BOARD to SLAVE_BOARD of LPI2C interface, LPI2C0 pins of MASTER_BOARD are connected with
    LPI2C0 pins of SLAVE_BOARD
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER_BOARD        CONNECTS TO         SLAVE_BOARD
Pin Name     Board Location     Pin Name     Board Location
LPI2C0_SCL   J2-20              LPI2C0_SCL   J2-20
LPI2C0_SDA   J2-18              LPI2C0_SDA   J2-18
GND          J2-14              GND          J2-14
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
LPI2C board2board polling example -- Slave transfer.


End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
