Overview
========
The ACMP Interrupt project is a simple demonstration program that uses the SDK software. It
compares the selected analog input with ACMP internal DAC output continuously and print information
corresponding to different comparison result in terminal. The purpose of this demo is to show how to
use the ACMP driver in SDK software by interrupt way. The ACMP can be configured based on default
configuration returned by the API ACMP_GetDefaultConfig(). The default configuration is: high
speed is not enabled, invert output is not enabled, unfiltered output is not enabled, pin out
is not enabled, offset level is level 0, hysteresis level is level 0.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- EVK-MIMXRT685 board
- Personal Computer

Board settings
==============
This example project uses ACMP to compare the voltage signal input from External Input1(J1-9)
with the voltage signal(half of Vin1 from internal PMC) output by ACMP's internal DAC. Terminal will print information
corresponding to different comparison result.

Connect ACMP External Input1(J1-9) to stable external voltage generator to avoid floating voltage.
The example serial port output may be frequent change otherwise.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J5) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The example compares analog input to the reference DAC output(CMP positive port).

The terminal will print CMP's output value when press any key.

Please press any key to get CMP's output value.

The analog input is LOWER than DAC output

The analog input is HIGHER than DAC output
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
