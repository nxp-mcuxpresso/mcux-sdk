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
- i.MX8QM MEK CPU Board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Note! ####
This application requires the SCFW(System Controller Firmware) with CM4 core's Partition/Domain
configuration and related Resource Management, for detailed information please refer to 
"System Controller Firmware Porting Guide" doc in Linux BSP package.
To enable this function of SCFW, add "-flags 0x00200000" parameter
for the first container in Makefile target in <imx-mkimage folder>/iMX8QM/soc.mak, e.g.

For debug/release/ddr_debug/ddr_release target:
flash: $(MKIMG) mx8qm-ahab-container.img scfw_tcm.bin u-boot-atf.bin
	./$(MKIMG) -soc QM -rev B0 -append mx8qm-ahab-container.img -c -flags 0x200000 -scfw scfw_tcm.bin -ap u-boot-atf.bin a53 0x80000000 -out flash.bin
For flash_debug/flash_release target: flash_linux_m4_xip

Prepare the Demo
================
This example should be run together with uboot.
1.  Prepare an bootable SD card with the SCFW and U-Boot image.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings, please refer to Getting Started with MCUXpresso SDK 
    to determine the Cortex-M4 and Cortex-A debug COM port:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Connect 12V power supply and J-Link Debug Probe to the board.
5.  Hit any key to stop uboot autoboot in the Cortex-A terminals.
6.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
7.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
The simliar log below in the Cortex-M terminal window shows the commands to use in uboot:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
For M4 core0:
**************************************************************
* Please make sure the uboot is started now.                 *
* Use the following commands in uboot for SEMA42 gate access *
* - md.b 0x371b0003 1 : Get SEMA42 gate status.              *
*   - 0 - Unlocked;                                          *
*   - 1 - Locked by Cortex-A;                                *
*   - 4 - Locked by Cortex-M;                                *
* - mw.b 0x371b0003 1 1 : Lock the SEMA42 gate.              *
* - mw.b 0x371b0003 0 1 : Unlock the SEMA42 gate.            *
**************************************************************

For M4 core1:
**************************************************************
* Please make sure the uboot is started now.                 *
* Use the following commands in uboot for SEMA42 gate access *
* - md.b 0x3b1b0003 1 : Get SEMA42 gate status.              *
*   - 0 - Unlocked;                                          *
*   - 1 - Locked by Cortex-A;                                *
*   - 4 - Locked by Cortex-M;                                *
* - mw.b 0x3b1b0003 1 1 : Lock the SEMA42 gate.              *
* - mw.b 0x3b1b0003 0 1 : Unlock the SEMA42 gate.            *
**************************************************************

Press anykey to start the example...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Follow the example output instructions:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Now the SEMA42 gate is unlocked, checking status in uboot returns 0.
Press anykey to lock the SEMA42 gate...

Now the SEMA42 gate is locked, checking status in uboot returns 4.
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
