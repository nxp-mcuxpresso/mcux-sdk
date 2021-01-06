Overview
========
The sema42 uboot example shows how to use SEMA42 driver to lock and unlock a sema gate.
This example should work together with uboot. This example runs on Cortex-M core,
the uboot runs on the Cortex-A core.

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
The log below in the Cortex-M terminal window shows the commands to use in uboot:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**************************************************************
* Please make sure the uboot is started now.                 *
* Use the following commands in uboot for SEMA42 gate access *
* - md.b 0x4101b003 1 : Get SEMA42 gate status.              *
*   - 0 - Unlocked;                                          *
*   - 2 - Locked by Cortex-A;                                *
*   - 3 - Locked by Cortex-M;                                *
* - mw.b 0x4101b003 2 1 : Lock the SEMA42 gate.              *
* - mw.b 0x4101b003 0 1 : Unlock the SEMA42 gate.            *
**************************************************************

Press anykey to start the example...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Follow the example output instructions:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Now the SEMA42 gate is unlocked, checking status in uboot returns 0.
Press anykey to lock the SEMA42 gate...

Now the SEMA42 gate is locked, checking status in uboot returns 3.
Lock or unlock the SEMA42 gate in uboot, the status does not change.

Press anykey to unlock the SEMA42 gate...

Now the SEMA42 gate is unlocked, checking status in uboot returns 0.

Lock the SEMA42 gate in uboot, after locked, then press anykey...

Cortex-A has locked the SEMA42 gate in uboot, Cortex-M could not lock.

Press anykey to reset the SEMA42 gate...

Now the SEMA42 gate is unlocked, checking status in uboot returns 0.

Press anykey to finish the example...

SEMA42 uboot example successed.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
