Overview
========
The sema42 example shows how to use SEMA42 driver to lock and unlock a sema gate:

In this example:
1. Firstly, Core 0 turn on LED  and lock a sema gate then boot up Core 1 wake up.
2. Core 1 must be wait until Core 0 unlocks this sema gate to lock it.
3. After user press any key in terminal window, the sema gate will be unlocked by core 0,
then core 1 will lock it and turn off the LED

If the board does not have LED to show the status, then core 1 will send a flag
to core 0 when core 1 has locked the sema gate. Core 0 outputs the success log
after it received the flag.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the demo
1.  Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Build core1 project first, then build core0 project.
4.  Download the core0 program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like below
and Red LED will turn on.

~~~~~~~~~~~~~~~~~~~~~
Sema42 example!

Press any key to unlock semaphore and Core 1 will turn off the LED
~~~~~~~~~~~~~~~~~~~~~

When press any key in the terminal, the LED will be turned off and the terminal tells

~~~~~~~~~~~~~~~~~~~~~
Now the LED should be turned off

Sema42 example succeed!
~~~~~~~~~~~~~~~~~~~~~
