Overview
========
The flexio_spi_slave_dma_spi_master example shows how to use flexio spi slave driver in dma way:

In this example, a flexio simulated slave connect to a spi master.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-K32L2B board
- Personal Computer

Board settings
==============
The flexio_spi_slave_dma_spi_master example is requires connecting between FlexIO pins with SPI pins
The connection should be set as following:
- J1-7, J2-6 connected
- J1-9, J2-8 connected
- J1-11, J2-10 connected
- J1-15, J2-12 connected

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
SPI Master interrupt - FLEXIO SPI Slave dma example start.

This example use one spi instance as master and one flexio spi as slave on one board.

Master uses interrupt and slave uses dma way.

Please make sure you make the correct line connection. Basically, the connection is:

SPI_master -- FLEXIO_SPI_slave

   SCK      --    SCK

   PCS0     --    PCS0

   MOSI     --    MOSI

   MISO     --    MISO

This is FLEXIO SPI slave call back.

SPI master <-> FLEXIO SPI slave transfer all data matched!
~~~~~~~~~~~~~~~~~~~~~
