Overview
========
The ccm_clockout driver example shows how to output the internal clock signal. In this driver example, users can choose
the clock signal to be outputted, and the divider of the output clock signal. By probing the output pin, users can
observe the selected internal clock signal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1015 board
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

Running the demo
================
To measure the output signal of CLKO1, please use the oscilloscope to probe D27;
To measure the output signal of CLKO2, please use the oscilloscope to probe TP31.
These instructions are displayed/shown on the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Clock Output Driver Example.
Please Choose one clock to be outputted on CLKO1.
	A -- PLL3 SW Clock.
	B -- PLL2(divided by 2).
	C -- ENET PLL(divided by 2).
	D -- AHB Clock Root.
	E -- IPG Clock Root.
	F -- Perclk Root.
	G -- PLL4 Main Clock.
a

Please set the clock divider, range from 1 to 8.
1

Theoretically, the output frequency of CLKO1 is 240000000 Hz.
Please Choose one clock to be outputted on CLKO2.
	A -- IPI2C Clock Root.
	B -- OSC Clock.
	C -- LPSPI Clock Root.
	D -- SAI1 Clock Root.
	E -- SAI2 Clock Root.
	F -- SAI3 Clock Root.
	G -- Trace Clock Root.
	H -- Flexspi Clock Root.
	I -- UART Clock Root.
	J -- Spdif0 Clock Root.
c

Please set the clock divider, range from 1 to 8.
2

Theoretically, the output frequency of CLKO2 is 52800000 Hz.

Please press any key to continue.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
