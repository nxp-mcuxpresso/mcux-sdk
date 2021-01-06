Overview
========

The SCG example shows how to use SCG driver:

 1. How to setup the SCG clock source.
 2. How to use SCG clock while power mode switch.
 3. How to use SCG APIs to get clock frequency.

This example prints the clock frequency through the terminal using the SDK driver.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE16Z board
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
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
SCG Example Start

SCG clock source frequency
SIRC clock: 8000000 Hz
FIRC clock: 48000000 Hz
LPFLL clock: 48000000 Hz

Current power mode: VLPR
Core clock: 4000000 Hz
Slow clock: 1000000 Hz

Current system clock: RUN
Core clock: 48000000 Hz
Slow clock: 24000000 Hz

Current power mode: RUN
Core clock: 8000000 Hz
Slow clock: 4000000 Hz

SCG Example End.
~~~~~~~~~~~~~~~~~~~~~
