Overview
========
The spi_dma_b2b_transfer_master example shows how to use driver API to transfer in DMA way.  

In this example, one spi instance as master and another spi instance on the other board as slave. 
Master sends a piece of data to slave, and receive a piece of data from slave. This example checks
if the data received from slave is correct. This example needs to work with spi_dma_b2b_transfer_slave 
example.

Note: This example will run in master mode, please prepare another board for slave, and the slave 
      board should be started first.

Project Infomation
1.How to set the baudrate of SPI?
  The baudrate of SPI is easy to set, just make sure the source clock of SPI.
  The formula is below:
  
  baudrate = PCLK_SPIn / DIVVAL
  SPIn->DIV = DIVVAL -1
  For example, if the needed baudrate of SPI is 500khz, and the SPI clock is 12MHz
  DIVVAL = 12000000/500000
  DIVVAL = 24
  SPIn->DIV = DIVVAL -1 = 23

Program Flow:
Main routine:
  1.Initialize the hardware.
	Configure pin settings, clock settings by using BOARD_InitHardware();
	
  2.Send information to terminal by using debug console.
	
  3.Initialize the SPI with configuration.
	
  4.Set up DMA configuration for master SPI.
    Initialize DMA and DMA channel setting(create handle and set callback) for both
    SPI RX and TX, set prioritory for TX channel and RX channel.
	
  5.Start SPI master transfer in DMA way.
    Initialize buffers and start SPI transfer in DMA way.
	
  6.Check if data from master is all right.
    Waiting for transmission complete, print received data and log information to terminal.
  
  7.De-initialize the SPI and DMA.

Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- Two LPCXpresso54628 boards
- Personal Computer

Board settings
==============
Populate jumper JP6.
Connect SPI master on board to SPI slave on other board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Master_board(SPI9)           Slave_board(SPI9)                          
Pin Name   Board Location     Pin Name   Board Location                     
MISO       J9  pin 11          MISO       J9  pin 11
MOSI       J9  pin 13          MOSI       J9  pin 13
SCK        J9  pin 9           SCK        J9  pin 9
PCS0       J9  pin 15          PCS0       J9  pin 15
GND        J14 pin 5           GND        J14 pin 5
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Change the solder jumper JS27 to 2-3 to use P3_30 pin as SSEL or
to use the Arduino connector J9 Pin 15.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the LPC-Link USB port (J8) on the board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This is SPI DMA transfer master example.
This example will communicate with another slave SPI on the other board.
Please start the slave board first!

The received data are:
    0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F
    0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17  0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F
    0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27  0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
    0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37  0x38  0x39  0x3A  0x3B  0x3C  0x3D  0x3E  0x3F
SPI transfer all data matched!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
