Overview
========
This demo describes how to use SDK drivers to implement the PWM feature by FLEXIO IP module.
It outputs the PWM singal with fixed frequency defined by "DEMO_FLEXIO_FREQUENCY" in source code
and dynamic duty from 99 to 1 to one of the FLEXIO pin.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-K28FA board
- Personal Computer

Board settings
==============
The example requires connection between the flexio output pin and LED pin.
- J2-20, J1-15 connected
Use oscilloscope to measure output the 48KHz PWM signal pin at J2-20 pin of board.

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
When the demo runs successfully, you can see the GREEN LED from dim to light.Use oscilloscope to check the waveform.
And these messages are displayed/shown on the terminal window:
~~~~~~~~~~~~
FLEXIO_PWM demo start.
~~~~~~~~~~~~
