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
- Mini USB cable
- FRDM-K32L2A4S board
- Personal Computer

Board settings
==============
This demo prints through the OpenSDA serial port, don't need special board setting.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port (J13) on frdmk32l2a4s board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo. For detailed instructions, see Getting Started with Software Development Kit for
   K32L2A (document SDKK32L2AGSUG).

Running the demo
================
When the demo runs successfully, will get the following messages on the OpenSDA terminal.

~~~~~~~~~~~~~~~~~~~~~~~~~~~
SCG Example Start

SCG clock source frequency
SIRC clock: 8000000 Hz
FIRC clock: 48000000 Hz
SPLL clock: 72000000 Hz

Current power mode: VLPR
Core clock: 4000000 Hz
Slow clock: 1000000 Hz

Current system clock: RUN
Core clock: 48000000 Hz
Slow clock: 24000000 Hz

Current power mode: HSRUN
Core clock: 72000000 Hz
Slow clock: 24000000 Hz

Current power mode: RUN
Core clock: 8000000 Hz
Slow clock: 4000000 Hz

SCG Example End.
~~~~~~~~~~~~~~~~~~~~~~~~~~~
