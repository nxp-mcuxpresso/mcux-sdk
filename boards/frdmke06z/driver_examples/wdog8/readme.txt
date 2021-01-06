Overview
========
The WDOG8 Example project is to demonstrate usage of the wdog8 driver.
In this example, fast testing is first implemented to test the wdog8.
After this, refreshing the watchdog in None-window mode and window mode is executed.
Note wdog8 is disabled in SystemInit function which means wdog8 is disabled
after chip emerges from reset.



Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KE06Z board
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
The log below shows the output of the hello world demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Low Byte test success
High Byte test success

----- Refresh test start -----
----- None-window mode -----
Refresh wdog8 0 time
Refresh wdog8 1 time
Refresh wdog8 2 time
Refresh wdog8 3 time
Refresh wdog8 4 time
Refresh wdog8 5 time
Refresh wdog8 6 time
Refresh wdog8 7 time
Refresh wdog8 8 time
Refresh wdog8 9 time
----- Window mode -----
Refresh wdog8 0 time
Refresh wdog8 1 time
Refresh wdog8 2 time
----- Refresh test success  -----

----- End of WDOG8 example  -----
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
