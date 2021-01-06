Overview
========

The demo shows how to use the PDB to generate a DAC trigger and use the DMA to transfer data into DAC buffer.

In this example, DAC is first set to normal buffer mode. PDB is as DAC hardware trigger source and DMA would work 
when DAC read pointer is zero. When run the example, the DAC is triggered by PDB and the read pointer increases by one,
every time the trigger occurs. When the read pointer reaches the upper limit, it goes to zero directly in the next trigger event.
while read pointer goes to zero, DMA request will be triggered and transfer data into DAC buffer. The user should probe
the DAC output with a oscilloscope to see the Half-sine signal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K66F board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.
5.  A multimeter may be used to measure the DAC output voltage.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

DAC CONTINUOUS PDB EDMA DEMO
Please probe the DAC output with a oscilloscope.

Then user can probe the DAC output with a oscilloscope to see the Half-sine signal.

