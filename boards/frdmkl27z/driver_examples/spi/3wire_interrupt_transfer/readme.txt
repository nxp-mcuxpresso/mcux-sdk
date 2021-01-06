Overview
========
The spi_3wire_interrupt_transfer example shows how to use spi driver in 3-wire mode:

In this example, one spi instance as master and another spi instance as slave. Master sends a piece of data to slave,
and check if the data slave received is correct. Actually, spi 3-wire mode can also support DMA transfer.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-KL27Z board
- Personal Computer

Board settings
==============
SPI one board:
  + Transfer data from instance0 to instance 1 of SPI interface, SPI0 pins are connected with
    SPI1 pins of board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0        CONNECTS TO         INSTANCE1
Pin Name   Board Location     Pin Name  Board Location
MOSI       J2 pin 8           MISO      J2 pin 20
SCK        J2 pin 12          SCK       J1 pin 11
PCS0       J2 pin 6           PCS0      J1 pin 9
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SPI one board 3-wire interrupt transfer example started!
This example will use 3 wires for transmission.
For SPI master: MOSI pin is an I/O pin for master to transmit data or receive data.
For SPI slave: MISO pin is an I/O pin for slave to transmit data or receive data.
Please make sure you make the correct line connection. Basically, the connection is: 
 SPI_master --  SPI_slave   
   CLK      --    CLK  
   PCS      --    PCS  
   MOSI     --    MISO  

SPI master starts to transmit data to slave.

SPI master transmit data completed!
SPI master starts to receive data from slave.

Please input any character to continue the transmission.

SPI master receive data completed!
SPI transfer finished! All data matched!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
