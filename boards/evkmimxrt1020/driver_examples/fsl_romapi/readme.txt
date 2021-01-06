Overview
========
The fsl_romapi example shows how to use ROM API:

In this example, fsl_romapi driver will call the API and operate the external Nor flash connected to
the FLEXSPI controller. Some simple flash command will be executed, such as FLEXSPI NOR get config, FLEXSPI NOR Flash init,
Erase sector, Program page.
Example will first erase the sector and program a page into the flash, at last check if the data in flash is correct.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1020 board
- Personal Computer

Board settings
==============

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

For FLEXSPI NOR targets, the result is:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FLEXSPI NOR example started!

Successfully init FLEXSPI serial NOR flash

serial flash has been found successfully

Vendor ID: xx

Serial NOR flash Information:

Total program flash size: xx KB, Hex: (xx)

Program flash sector size: xx KB, Hex: (xx)

Program flash page size: xx B, Hex: (xx)

Erasing serial NOR flash over FLEXSPI

Successfully erased one sector of NOR flash device xx -> xx

Program a buffer to a page of NOR flash

Successfully programmed and verified location FLEXSPI memory xx -> xx

End of FLEXSPI NOR Example!
