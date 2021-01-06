Overview
========

The QTMR project is a simple demonstration program of the SDK QTMR driver.
The quad-timer module provides four timer channels with a variety of controls affecting both individual
and multi-channel features. Specific features include up/down count,cascading of counters, programmable modulo,
count once/repeated, counter preload, compare registers with preload, shared use of input signals, prescaler controls,
independent capture/compare, fault input control, programmable input filters, and multichannel synchronization.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- TWR-KM35Z75M board
- Personal Computer

Board settings
==============
Probe signal at J25-20 using oscillator.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*********QUADTIMER EXAMPLE START*********
****Timer use-case, 1 second tick.****
 Timer interrupt has occurred !
 Timer interrupt has occurred !
....................
....................
****Chain Timer use-case, 10 second tick.****
 Timer interrupt has occurred !
 Timer interrupt has occurred !
.........
.........
****Input capture example.****
****Provide a signal input to the TMR0 pin****
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input rising signal at J21-1. Then the following message is displayed:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input Captured value=bebe

*********Make sure to connect a scope.*********

****A 50 duty cycle PWM wave is observed in the scope.****

*********QUADTIMER EXAMPLE END.*********
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
And you will find the LED RED is taking turns to shine.
