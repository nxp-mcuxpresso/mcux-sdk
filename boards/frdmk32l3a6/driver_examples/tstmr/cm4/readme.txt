Overview
========

The tstmr example shows the usage of TSTMR driver in application. The TSTMR module is a free running incrementing counter that starts running after system reset de-assertion and can be read at any time by the software for determining the software ticks.The TSTMR runs off the 1 MHz clock and resets on every system reset.

In this example, it would output a time stamp information when the application is ready. And then, delay for 1 second with TSTMR_DelayUs() function. Before and after the delay, it would output the two time stamps information again.


Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
This demo prints through the OpenSDA serial port, don't need special board setting.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port on FRDM-K32L3A6 board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the demo runs successfully, will get the similar messages on the OpenSDA terminal.

~~~~~~~~~~~~~~~~~~~~~~
 Timestamp1 = 09c4460

 Test the delay function, delay for 1 second

 Start time = 09c5cfd

 End time = 0aba7c9
~~~~~~~~~~~~~~~~~~~~~~
