Overview
========

The dac_buffer_interrupt example shows how to use DAC FIFO interrupt.

When the DAC FIFO empty interrupt is enabled firstly, the application would enter the DAC ISR immediately, since the FIFO is actually empty. Then the FIFO would be feed inside the ISR. Then the DAC interrupt could be restrained. Once the DAC FIFO is triggered in while loop, the data in FIFO is read out, then it becomes empty, so the FIFO would be feed again in DAC ISR. 

With this example, user can define the DAC output array to generate the different wave output. Also the software trigger can be called in some timer ISR so that the DAC would output the analog signal in indicated period. Or even use the hardware trigger to release the CPU.

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
5.  A multimeter may be used to measure the DAC output voltage (Connector J4-12).

Running the demo
================
When the demo runs successfully, the log would be seen on the debug console terminal like:

DAC buffer interrupt Example.
Press any key to trigger the DAC...
DAC next output: 200
DAC next output: 300
DAC next output: 400
DAC next output: 500
DAC next output: 600
DAC next output: 700
DAC next output: 800
DAC next output: 900

Then user can measure the DAC output pin to check responding voltage.

