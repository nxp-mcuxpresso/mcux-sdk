Overview
========
The adc_polling example shows the simplest way to use adc driver.

In this example, user should indicate a channel to provide a voltage signal (can be controlled by user) as the adc's
sample input. When running the project, typing any key into debug console would trigger the conversion. The execution 
would check the conversion completed flag in loop until the flag is asserted, which means the conversion is completed. 
Then read the conversion result value and print it to debug console.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KE04Z board
- Personal Computer

Board settings
==============
ADC_SE2 is selected as ADC input channel and J3-8 is ADC input pin.

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
ADC polling Example.
ADC Full Range: XXXX
Press any key to get user channel's ADC value.
ADC Value: 132
ADC Value: 174
ADC Value: 255
ADC Value: 255
ADC Value: 255
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The user can sample voltage by J3-8 pin.
