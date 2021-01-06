Overview
========

The src_reset_source example shows how to check the reset source and boot option with SRC driver.

When run this example firstly on the board after power up, the POR reset or IPP reset flag would be asserted. But when running it again, the flag would be cleared, since it is no longer a reset.

Usually, the reset flags are used and cleared by ROM code or bootloader to check which reset occurred. With the boot mode words, the initial boot code would go to the right way to execute the start code. For example, when the SoC is waked up from some low power mode, all necessary data are already staying in the RAM, the CPU would not have to reload the program to RAM and execute the application directly.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVKB-IMXRT1050 board
- Personal Computer

Board settings
==============
No special settings are required.

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
When the demo runs successfully, the log would be seen on the terminal like:

Example: SRC Reset Soruce.
SRC_GetResetStatusFlags(): 0x3.
SRC_GetBootModeWord1(): 0x200.
SRC_GetBootModeWord2(): 0x2000001.
