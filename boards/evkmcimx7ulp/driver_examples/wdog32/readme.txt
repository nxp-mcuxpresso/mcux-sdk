Overview
========
The WDOG32 Example project is to demonstrate usage of the KSDK wdog32 driver.
In this example, fast testing is first implemented to test the wdog32.
After this, refreshing the watchdog in None-window mode and window mode is executed.
Note wdog32 is disabled in SystemInit function which means wdog32 is disabled
after chip emerges from reset.



Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- 5V power supply
- Personal Computer
- SD card

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
This should be run together with uboot.
1.  Build the project and generate the .bin file.
2.  Copy the .bin file to <sdk_dir>/tools/imgutil/evkmcimx7ulp folder and rename
    to sdk20-app.bin.
3.  In the folder <sdk_dir>/tools/imgutil/evkmcimx7ulp, run "mkimage.sh ram or mkimage.sh flash" 
    (see readme in the <sdk_dir>/tools/imgutil )to create bootable image.
4.  Prepare an SD card with the prebuilt U-Boot image and copy the sdk20-app.img
    generated into the SD card. Then, insert the SD card to the target board.
    Make sure to use the default boot SD slot and check the dip switch configuration
5.  Open a serial terminal with the following settings to connect to Cortex-A:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
6.  Connect 5V power supply to the board, switch SW1 to power on the board.
7.  Hit any key to stop autoboot in the terminals, then enter to U-Boot command
    line mode. Then write the image and run it from QSPI Flash with the following
    commands:
    - sf probe
    - sf erase 0x0 0x20000
    - fatload mmc 0:1 0x62000000 sdk20-app.img
    - sf write 0x62000000 0x0 0x20000
8.  Open a serial terminal with the following settings to connect to Cortex-M:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
9.  Switch the SW1 to re-power the board.
10. Hit any key to stop uboot autoboot in the Cortex-A terminals.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
High Byte test success

----- Refresh test start -----
----- None-window mode -----
Refresh wdog32 0 time
Refresh wdog32 1 time
Refresh wdog32 2 time
Refresh wdog32 3 time
Refresh wdog32 4 time
Refresh wdog32 5 time
Refresh wdog32 6 time
Refresh wdog32 7 time
Refresh wdog32 8 time
Refresh wdog32 9 time
----- Window mode -----
Refresh wdog32 0 time
Refresh wdog32 1 time
Refresh wdog32 2 time
----- Refresh test success  -----

----- End of WDOG32 example  -----
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
