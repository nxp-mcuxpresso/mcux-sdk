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
To enable this function of SCFW, add "-flags 0x200000" parameter
for the first container in Makefile target in <imx-mkimage folder>/iMX8QM/soc.mak, e.g.

flash_scfw: $(MKIMG) mx8qm-ahab-container.img scfw_tcm.bin
	./$(MKIMG) -soc QM -rev B0 -dcd skip -append mx8qm-ahab-container.img -c -flags 0x200000 -scfw scfw_tcm.bin -out flash.bin

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
This example requires run both core0 and core1 at the same time! 

When the demo runs successfully, the log would be seen on the core0's terminal like below.

~~~~~~~~~~~~~~~~~~~~~
Sema42 example!

Press any key to unlock semaphore and Core 1 will lock it
~~~~~~~~~~~~~~~~~~~~~

When press any key in the terminal, the terminal tells

~~~~~~~~~~~~~~~~~~~~~
Wait for core 1 lock the semaphore

Sema42 example succeed!
~~~~~~~~~~~~~~~~~~~~~
