Overview
========
The ACMP Polling project is a simple demonstration program that uses the SDK software. It compares
the selected analog input with ACMP internal DAC output continuously and toggle the LED when the
final comparison result changed. The purpose of this demo is to show how to use the ACMP driver
in SDK software by polling way. The ACMP can be configured based on default configuration returned
by the API ACMP_GetDefaultConfig(). 


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KE02Z40M board
- Personal Computer

Board settings
==============
J2-2 is ACMP input pin.

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
The example compares analog input to the reference DAC output(CMP positive port).
The LED will be turned ON/OFF when the analog input is LOWER/HIGHER than the DAC output.
Change the analog input voltage to see the LED status.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
User can change J2-2 pin to see the LED status.
