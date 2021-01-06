Overview
========

The adc12_lpit_trgmux example shows how to use the LPIT and TRGMUX to generate a ADC trigger.

In this example, user should indicate a channel to provide a voltage signal (can be controlled by user) as the ADC12's
sample input. When run the example, the ADC is triggered by TRGMUX and gets the ADC conversion result in the ADC
Conversion Complete (COCO) Interrupt. The LPIT is configured as periodic counter which will output pre-trigger and
tigger signal to TRGMUX periodically.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE15Z board
- Personal Computer

Board settings
==============
This example project uses ADC12 instance 0 to sample and convert the voltage signal input from channel 0(PTA0).
So the voltage signal input from PTA0 should be changed to observe the dynamical conversion result.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADC Full Range: 4096

Change the input voltage to check ADC12's conversion result...

ADC12 Interrupt Counter: 1
ADC12 Conversion Completed, result value: 4056

ADC12 Interrupt Counter: 2
ADC12 Conversion Completed, result value: 781
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
