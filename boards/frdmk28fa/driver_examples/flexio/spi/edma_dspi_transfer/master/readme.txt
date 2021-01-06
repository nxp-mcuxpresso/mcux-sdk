Overview
========
The flexio_spi_master_edma_dspi_slave example shows how to use flexio spi master driver in edma way:

In this example, a flexio simulated master connect to a dspi slave .

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
The flexio_spi_master_edma_dspi_slave example is requires connecting between FlexIO pins with DSPI pins
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
FLEXIO Master edma - DSPI Slave interrupt example start.

This example use one flexio spi as master and one dspi instance as slave on one board.

Master uses edma and slave uses interrupt way.

Please make sure you make the correct line connection. Basically, the connection is:

FLEXIO_SPI_master -- DSPI_slave

   CLK      --    CLK

   PCS      --    PCS

   SOUT     --    SIN

   SIN      --    SOUT

This is DSPI slave call back.

FLEXIO SPI master <-> DSPI slave transfer all data matched!
~~~~~~~~~~~~~~~~~~~~~
