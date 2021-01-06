Overview
========
The flexio_spi_slave_interrupt_lpspi_master example shows how to use flexio spi slave driver in interrupt way:

In this example, a flexio simulated slave connect to a lpspi master.



Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- J-Link Debug Probe
- 5V power supply
- Personal Computer

Board settings
==============
1.The example requires connecting the FLEXIO pins with the LPSPI pins;

2.Remove the resistors R101, R19 on base board;
Note:
Remove R101,R19 to avoid some other signals may have interference on LPSPI,
if users just run this application to demonstrate LPSPI function and no other applicaions are running at the same time,
then R101 & R19 do not need to be removed.

please connect between LPSPI1 pins and LPSPI0 pins
The connection should be set as following:
- J8-3(R191 should be short-circuited), R101 pad1(On base board) connected
- J8-4(R190 should be short-circuited), R22(On base board) connected
- J8-5(R189 should be short-circuited), TP25(On base board) connected
- J8-6(R188 should be short-circuited), TP27(On base board) connected

#### Please note this application can't support running with Linux BSP! ####

#### Please note this application can only run well with RAM link file!
If run it in QSPI flash, there's high latency when instruction cache miss. As the FlexIO SPI has
no FIFO so it has critical timing requirement that SPI data must be read in time, otherwise
overflow may occur which causes data loss. To run FlexIO SPI slave in QSPI flash, either use DMA
driver or do synchronization for data exchange. ####

Note
~~~~~~~~~~~~~~
Because of the LPSPI signal pin allocating issue, you can not restart this demo/example by press the ResetButton(SW3):
The LPSPI1_SIN, LPSPI1_SOUT, LPSPI1_SCK and LPSPI0_SOUT pins is connected to PTA12, PTA13, PTA14 and PTA15 pins.
These pins is also used as BOO_CFG12, BOO_CFG13, BOO_CFG14 and BOO_CFG15 when the i.MX SoC reboot. These signals is
driven by LPSPI0 pins(PTA18, PTA19, PTA20 and PTA23), when user press ResetButton. This may cause M4 Core enter enter
incorrect boot modes and only re-powerup the board can let the M4 core exit such modes.

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
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
LPSPI Master interrupt - FLEXIO SPI Slave interrupt example start.

This example use one lpspi instance as master and one flexio spi slave on one board.

Master and slave are both use interrupt way.

Please make sure you make the correct line connection. Basically, the connection is:

LPSPI_master -- FLEXIO_SPI_slave

   CLK      --    CLK

   PCS      --    PCS

   SOUT     --    SIN

   SIN      --    SOUT

This is FLEXIO SPI slave call back.

LPSPI master <-> FLEXIO SPI slave transfer all data matched!

End of Example.
~~~~~~~~~~~~~~~~~~~~~
