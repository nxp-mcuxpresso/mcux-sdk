Overview
========

The OCOTP example project is a demonstration program that uses the KSDK software to access eFuse map.
Consider of the feature of One-Time programable, this example will just print the version of OCOTP controller.

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
The log below shows the output of the oxotp example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OCOTP Peripheral Driver Example

OCOTP controller version: 0x06000000

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note:
To download binary into hyper flash and boot from hyperflash directly, following steps are needed:
1. Select the target flexspi_nor_debug or flexspi_nor_release.
2. Compile the project, and get the binaray file "ocotp_example.bin"
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



