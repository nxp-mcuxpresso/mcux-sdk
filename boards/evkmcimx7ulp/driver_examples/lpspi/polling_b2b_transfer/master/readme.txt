Overview
========
The lpspi_polling_b2b_transfer example shows how to use LPSPI driver in polling way:

In this example , we need two boards, one board used as LPSPI master and another board used as LPSPI slave.
The file 'lpspi_polling_b2b_transfer_master.c' includes the LPSPI master code.

1. LPSPI master send/received data to/from LPSPI slave in polling . (LPSPI Slave using interrupt to receive/send the data)

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
Populate R188, R189, R190, R191 on both base boards.

SPI one board:
Transfer data from one board instance to another board's instance.
SPI1 pins are connected with SPI1 pins of another board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0(SPI1)     CONNECTS TO         INSTANCE0(SPI1)
Pin Name   Board Location     Pin Name  Board Location
SPI1_SCK    J8 pin 6            SPI1_SCK  J8 pin 6
SPI1_SIN    J8 pin 5            SPI1_SOUT J8 pin 4
SPI1_SOUT   J8 pin 4            SPI1_SIN  J8 pin 5
SPI1_PCS0   J8 pin 3            SPI1_PCS0 J8 pin 3
GND                             GND
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Please note this application can't support running with Linux BSP! ####
Note
~~~~~~~~~~~~~~
Because of the LPSPI signal pin allocating issue, you can not restart this demo/example by press the ResetButton(SW3):
The LPSPI1_SIN, LPSPI1_SOUT, LPSPI1_SCK and LPSPI1_PCS0 pins are connected to PTA12, PTA13, PTA14 and PTA15 pads.
These pins are also used as BOO_CFG12, BOO_CFG13, BOO_CFG14 and BOO_CFG15 when the i.MX SoC reboot. These signals are
driven by LPSPI1 pins on the other board, when user press ResetButton. This may cause M4 Core enter enter
incorrect boot modes and only re-powerup both boards can let the M4 core exit such modes.

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
5.  Either cold boot your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPSPI board to board polling example.
This example use one board as master and another as slave.
Master uses polling way and slave uses interrupt way. 
Please make sure you make the correct line connection. Basically, the connection is: 
LPSPI_master --  LPSPI_slave   
   CLK       --    CLK  
   PCS       --    PCS 
   SOUT      --    SIN  
   SIN       --    SOUT 
   GND       --    GND 

 Master transmit:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40
 
LPSPI transfer all data matched! 

 Master received:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Press any key to run again
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
