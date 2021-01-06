Overview
========
The flexio_spi_slave_interrupt_dspi_master example shows how to use flexio spi slave driver in interrupt way:

In this example, a flexio simulated slave connect to a dspi master.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K28FA boards
- Personal Computer

Board settings
==============
The flexio_spi_slave_interrupt_dspi_master example is requires connecting between FlexIO pins with DSPI pins
For revA board,the connection should be set as following:
- J27-19(PTD8),  J27-9(PTA17) connected
- J4-12(PTB2),   J27-12(PTA14) connected
- J27-20(PTD9),  J27-10(PTA16) connected
- J4-10(PTB3),   J27-11(PTA15) connected

For revB board,the connection should be set as following:
- J27-21(PTD8),  J27-20(PTA17) connected
- J4-12(PTB2),   J27-17(PTA14) connected
- J27-22(PTD9),  J27-19(PTA16) connected
- J4-10(PTB3),   J27-18(PTA15) connected

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
DSPI Master interrupt - FLEXIO SPI Slave interrupt example start.

This example use one dspi instance as master and one flexio spi slave on one board.

Master and slave are both use interrupt way.

Please make sure you make the correct line connection. Basically, the connection is:

DSPI_master -- FLEXIO_SPI_slave

   CLK      --    CLK

   PCS      --    PCS

   SOUT     --    SIN

   SIN      --    SOUT

This is FLEXIO SPI slave call back.

DSPI master <-> FLEXIO SPI slave transfer all data matched!
~~~~~~~~~~~~~~~~~~~~~
