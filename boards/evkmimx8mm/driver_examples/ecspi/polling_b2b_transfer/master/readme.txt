Overview
========
The ecspi_polling_b2b_transfer example shows how to use ECSPI driver in polling way:

In this example , we need two boards, one board used as ECSPI master and another board used as ECSPI slave.
The file 'ecspi_polling_b2b_transfer_master.c' includes the ECSPI master code.

1. ECSPI master send/received data to/from ECSPI slave in polling . (ECSPI Slave using interrupt to receive/send the data)

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MM6-EVK  board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
ECSPI board to board:
Transfers data through the instance 2 of the ECSPI interface. ECSPI2 pins of the master board are
connected to the ECSPI2 pins of the slave board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER BOARD           CONNECTS TO         SLAVE BOARD
Pin Name    Board Location                 Pin Name  Board Location
MISO        J1003 - 21                     MISO      J1003 - 21
MOSI        J1003 - 19                     MOSI      J1003 - 19
SCK         J1003 - 23                     SCK       J1003 - 23
SS0         J1003 - 24                     SS0       J1003 - 24
GND         J1003 - 6                      GND       J1003 - 6
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW101 to power on the board
2.  Connect a USB cable between the host PC and the J901 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the debug terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECSPI board to board polling example.
This example use one board as master and another as slave.
Master uses polling way and slave uses interrupt way. 
Please make sure you make the correct line connection. Basically, the connection is: 
ECSPI_master -- ECSPI_slave   
   CLK      --    CLK  
   PCS      --    PCS 
   MOSI     --    MOSI  
   MISO     --    MISO 
   GND      --    GND 

 Master transmit:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

Start receive data from slave.

ECSPI transfer all data matched! 

 Master received:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Press any key to run again
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
