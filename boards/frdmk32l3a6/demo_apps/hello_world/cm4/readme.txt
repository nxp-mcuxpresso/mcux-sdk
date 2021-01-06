Overview
========
The Hello World demo application provides a sanity check for the new SDK build environments and board bring up. The Hello
World demo prints the "Hello World" string to the terminal using the SDK UART drivers. The purpose of this demo is to
show how to use the UART, and to provide a simple project for debugging and further development.
Note: Please input one character at a time. If you input too many characters each time, the receiver may overflow
because the low level UART uses simple polling way for receiving. If you want to try inputting many characters each time,
just define DEBUG_CONSOLE_TRANSFER_NON_BLOCKING in your project to use the advanced debug console utility.

Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
No special settings are required.
If download M0+ core project, need to let MCU boot from M0+ core. By default, MCU will boot from M4 core, it can
be configured to boot from M0+ core. To do so, bitfield BOOT_CORE in FTFE_FOPT register needs to be set to 0.
The register needs to be set to 0xFFFFFFBF. Below, steps how to access (program, read, erase) the FOPT register
using J-Link Commander are listed:
1. Connect J12 on board to PC using USB cable.
2. Connect J7 on board to PC using Jlink.
3. Open Jlink Command, input follow instructions, please make sure FTFE_FOPT value are 0xFFFFFFFF before doing
   below steps, and new configuration will become active after power-on-reset:
    w1 0x40023007 0x43  // FCCOB0: CMD_PROGRAM_ONCE (IFR)
    w1 0x40023006 0x84  // FCCOB1: IFR Index of the FOPT
    w1 0x40023005 0x00  // FCCOB2: Not used
    w1 0x40023004 0x00  // FCCOB3: Not used
    w1 0x4002300B 0xFF  // FCCOB4: Record byte 0 value --> FOPT (Bit31:Bit24)
    w1 0x4002300A 0xFF  // FCCOB5: Record byte 1 value --> FOPT (Bit23:Bit16)
    w1 0x40023009 0xFF  // FCCOB6: Record byte 2 value --> FOPT (Bit15:Bit8)
    w1 0x40023008 0xBF  // FCCOB7: Record byte 3 value --> FOPT (Bit7:Bit0)
    w1 0x40023000 0x80  // Trigger operation
4. More details can be found on webpage https://wiki.segger.com/K32W#Boot_ROM.


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
The log below shows the output of the hello world demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
hello world.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
