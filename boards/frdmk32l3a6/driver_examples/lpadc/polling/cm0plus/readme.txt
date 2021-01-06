Overview
========

The lpadc_single_polling example shows the simplest way to use LPADC driver.

In this example, user should indicate a channel to provide a voltage signal (can be controlled by user) as the LPADC's
sample input. When running the project, typing any key into debug console would trigger the conversion. The execution 
would check the FIFO valid flag in loop until the flag is asserted, which means the conversion is completed. 
Then read the conversion result value and print it to debug console.

Note, the default setting of initialization for the ADC converter is just an available configuration. User can change
the configuration structure's setting in application to fit the special requirement.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
- LPADC CH6A Input signal J4-2(ptc11)

Prepare the Demo
================
1.  Connect a USB to Serial Line between the host PC and the J73 serial port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
The log below shows in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPADC Polling Example
Please press any key to get user channel's ADC value.
ADC value: 4079
ADC value: 4079
ADC value: 4080
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
