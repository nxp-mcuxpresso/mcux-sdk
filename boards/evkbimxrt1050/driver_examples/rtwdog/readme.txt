Overview
========
The RTWDOG Example project is to demonstrate usage of the KSDK rtwdog driver.
In this example, fast testing is first implemented to test the rtwdog.
After this, refreshing the watchdog in None-window mode and window mode is executed.
Note rtwdog is disabled in SystemInit function which means rtwdog is disabled
after chip emerges from reset.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVKB-IMXRT1050 board
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
Note:
To download binary into hyper flash and boot from hyperflash directly, following steps are needed:
1. Select the target flexspi_nor_debug or flexspi_nor_release.
2. Compile the project, and get the binaray file "rtwdog.bin"
3. Set the SW7: 1 off 2 off 3 off 4 on, then power on the board and connect USB cable to J28
4. Drop the binaray into disk "EVK-MIMXRT"
5. Wait for the disk disappear and appear again which will take around ~10s, then power off the board
6. Set the SW7: 1 off 2 on 3 on 4 off, then power on the board
7. After power on the baord, program has already started to run, reset SW4 is recommended.

Note:
To debug in hyper flash in MDK, following steps are needed:
1. Select the target flexspi_nor_debug or flexspi_nor_release.
2. Compile the project.
3. Press F8 or click the download button, to program the application into hyper flash.
4. Set the SW7: 1 off 2 on 3 on 4 off, then power on the board
5. Push SW4 to reset.
6. Start to debug.

When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
----- Fast test starts -----
----- Low Byte test starts -----
Waiting for timeout reset
Low Byte test succeeded
----- High Byte test starts -----
Waiting for timeout reset
High Byte test succeeded
----- The end of RTWDOG fast test -----
----- Refresh test start -----
----- None-window mode -----
Refresh rtwdog 1 time
Refresh rtwdog 2 time
Refresh rtwdog 3 time
Refresh rtwdog 4 time
Refresh rtwdog 5 time
Refresh rtwdog 6 time
Waiting for time out reset
None-window mode reset succeeded
----- Window mode -----
Refresh rtwdog 1 time
Refresh rtwdog 2 time
Refresh rtwdog 3 time
Waiting for time out reset
Window mode reset succeeded
~~~~~~~~~~~~~~~~~~~~~
