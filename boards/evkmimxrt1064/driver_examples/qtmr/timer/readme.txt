Overview
========

The QTMR project is a simple demonstration program of the SDK QTMR driver to use QTMR as a timer.
The quad-timer module provides four timer channels with a variety of controls affecting both individual
and multi-channel features. 
It sets up the QTMR hardware block to trigger an interrupt every 50 millisecond.
When chaining the first channel and the second channel, Timer interrupt occur every 10 second.
When the QTMR interrupt is triggered a message a printed on the UART terminal.
In lots of RT10x devices, overflow flag and related interrupt cannot be generated successfully in upward 
count mode (ERRATA050194), the workaround is to use compare interrupt instead of overflow interrupt 
by setting compare value to 0xFFFF, the compare interrupt has the same timing effect as overflow interrupt 
in this way. So we add a new demo scene like that, when setting the compare value to 0xFFFF, Timer compare 
interrupt occurs every 65.5 seconds.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
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
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*********QUADTIMER EXAMPLE START*********
****Timer use-case, 50 millisecond tick.****

 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
****Chain Timer use-case, 10 second tick.****

 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
 Timer interrupt has occured !
****Timer use-case, Over flow Test.****

 Timer Overflow has occurred !
*********QUADTIMER EXAMPLE END.*********
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
