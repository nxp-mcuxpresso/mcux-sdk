Overview
========
The vref example shows how to use the vref driver.

In this example, the adc16 module is initialized and used to measure the VREF output voltage. So, it cannot use internal
VREF as the reference voltage.

Then, user should configure the VREF output pin as the ADC16's sample input. When running the project, it will firstly
measure the VREF output voltage within the default (factory) trim value. Then, it will measure the VREF output voltage
under different trim values.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K22F board
- Personal Computer

Board settings
==============
- No special setting is needed.

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

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

VREF example

ADC16_DoAutoCalibration() Done.

ADC Full Range: 4096

Defalut (Factory) trim value is :34

ADC value: 1336

Use trim value: 0

ADC value: 1340

Use trim value: 4

ADC value: 1338

......

Use trim value: 60

ADC value: 1337
