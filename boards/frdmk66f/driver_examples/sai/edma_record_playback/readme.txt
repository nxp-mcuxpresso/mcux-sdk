Overview
========
The sai_edma_record_playback example shows how to use sai driver with EDMA:

In this example, one sai instance record the audio data from input and playbacks the audio data.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K66F board
- Personal Computer
- Headphones
- Line-in line

Board settings
==============

Prepare the Demo
================
1. Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2. Open a serial terminal on PC for JLink serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Insert the headphones into the headphone jack on FRDM-K66F board (J28). Insert line-in line into J29.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs, the log would be seen on the OpenSDA terminal like:
~~~~~~~~~~~~~~~~~~~
SAI example started!
 ~~~~~~~~~~~~~~~~~~~



