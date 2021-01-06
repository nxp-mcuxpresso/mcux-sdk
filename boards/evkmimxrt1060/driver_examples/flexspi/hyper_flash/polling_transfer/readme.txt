Overview
========
The flexspi_hyper_flash_polling_transfer example shows how to use flexspi driver with polling:

In this example, flexspi will send data and operate the external Hyper flash connected with FLEXSPI. Some simple flash command will
be executed, such as Read ID, Erase Sector and Program Buffer.
Example will first configures hyper flash to enter ASO mode, read ID-CFI parameters, then exit ASO mode.
Second, the example erase a sector in flash, check if the erase is successful and program the same sector, then read back
the sector data. At last check if the data read back is correct.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1060 board
- Personal Computer

Board settings
==============
The board enable QSPI flash (U33) by default. To enables hyper flash (U19), some hardware rework is needed:
Mount R356,R361,R362,R363,R364,R365,R366 and DNP R153,R154,R155,R156,R157,R158.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

For flexspi_nor targets, the result is:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FLEXSPI hyperflash example started!
Found the HyperFlash by CFI
loop nummber: 0
loop nummber: 1
loop nummber: 2
loop nummber: 3
loop nummber: 4
loop nummber: 5
FLEXSPI hyperflash example successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~


For ram/sdram targets, the result is:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FLEXSPI hyperflash example started!
Found the HyperFlash by CFI
Erasing whole chip over FlexSPI...
Erase finished !
loop nummber: 0
loop nummber: 1
loop nummber: 2
loop nummber: 3
loop nummber: 4
loop nummber: 5
FLEXSPI hyperflash example successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
