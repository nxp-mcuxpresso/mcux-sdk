Overview
========
The mmau project is a simple demonstration program that use the MMAU driver:
How to use calculate functions to create sine function for the arithmetic computation.

In this example, use calculate functions to compute sinusoidal function for various angles.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- TWR-KM35Z75M board
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
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MMAU example : start

    Sin(pi)      = 0x0 in frac32 format
    Sin(0.8*pi)  = 0x4B3C8C10 in frac32 format
    Sin(0.6*pi)  = 0x79BC3848 in frac32 format
    Sin(0.4*pi)  = 0x79BC3848 in frac32 format
    Sin(0.2*pi)  = 0x4B3C8C10 in frac32 format
    Sin(0)       = 0x0 in frac32 format
    Sin(-0.2*pi) = 0xB4C373E8 in frac32 format
    Sin(-0.4*pi) = 0x8643C7B0 in frac32 format
    Sin(-0.6*pi) = 0x8643C7B0 in frac32 format
    Sin(-0.8*pi) = 0xB4C373E8 in frac32 format
    Sin(-pi)     = 0x0 in frac32 format

MMAU example : end
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
