Overview
========
The RGPIO Example project is a demonstration program that uses the SDK software to manipulate the general-purpose
outputs.
The example is supported by the set, clear, and toggle write-only registers for each port output data register. The 
example take turns to shine the LED.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK Board
- MCIMX8-8X-BB
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- Oscilloscope

Board settings
==============
For CM4_0 core : Use Oscilloscope to check output on J27-1(on base board)

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
Since no LED connected to the RGPIO. Please use oscilloscope probe to the pin to check the output. The output will toggle periodically.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 RGPIO Driver example
 The LED is taking turns to shine.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
