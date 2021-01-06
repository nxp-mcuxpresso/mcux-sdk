Overview
========
The TEMPMON project is a simple demonstration program of the SDK TEMPMON driver.The
temperatue monitor (TEMPMON) module features alarm functions that can raise independent
interrupt signals if the temperature is above two high-temperature thresholds and below
a low temperature threshold, the system can then use this module to monitor the on-die
temperature and take appropriate actions such as throttling back the core frequency when
a the high temperature interrupt is set.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Board settings
==============

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
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~
TEMPMON driver example.
The chip initial temperature is 40.8 ℃.
The chip temperature has reached high temperature that is 42.7 ℃.
The chip throttling back core frequency to waiting a desired cool down temperature .
The chip core frequency is 62500000 Hz.
The chip temperature has reached low temperature that is 39.5 ℃.
The chip will return to the normal process .
The chip core frequency is 500000000 Hz.
~~~~~~~~~~~~~~~~~~~~~~~

Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
3. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J23.
4. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
