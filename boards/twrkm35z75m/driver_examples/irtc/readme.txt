Overview
========

The IRTC project is a simple demonstration program of the SDK IRTC driver.
This example is a low power module that provides time keeping and calendaring functions and additionally provides
protection against tampering, protection against spurious memory/register updates and battery operation.

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
~~~~~~~~~~~~~~~~~~~~~~~~
RTC Example START:

Start Time is 2015/1/21 18:55:30

Ring, ring, ring
Alarm Time is 2015/1/21 18:55:33

RTC Example END.
~~~~~~~~~~~~~~~~~~~~~~~

