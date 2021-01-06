Overview
========
The qspi_polling example shows how to use qspi driver with polling:

In this example, qspi will send data and operate the external flash connected with QSPI. Some simple flash command will
be executed, such as Write Enable, Erase sector, Program page.
Example will first erase the sector and programe a page into the flash, at last check if the data in flash is correct.

Notice: While do program, it is not suggested to make the flash write frequency bigger than the core clock frequency.
In some tool chain's Debug version, this may cause core do not have enough speed to send data to flash.
The flash write frequency equals to QSPI working frequency plus data line number. For example, if QSPI working in 48MHz,
program command uses quad mode, the write frequency is 48MHz * 4 = 192MHz.

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
The example is uses QSPI0. The module uses PTB8, PTB15 ~PTB19 pins.
No special jumper needs to be connected.

#### Please note this application can't support running with Linux BSP! ####

#### Please note that this application must be built with ram link file! Because if running the application in QSPI
flash in place, the QSPI flash erase/program feature of the application might affect the instruction fetch. If QSPI
execution in place(XIP) is really needed, please make sure the flash erase/program operation must be handled by RAM
function and disable all interrupts to avoid jumping into interrupt handler in flash area during flash updating. ####

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

NOTE: Don't build this example with flash linkage file since this example need to modify QSPI controller, so
program itself cannot be run in QSPI flash.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
QSPI example started!

Erase finished!

Program data finished!

Program through QSPI polling succeed!
~~~~~~~~~~~~~~~~~~~~~
