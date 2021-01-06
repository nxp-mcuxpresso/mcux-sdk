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
- MIMX8QX MEK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Note! ####
1. The M4 WDOG will reboot the partition that contains the M4 core. The Partition need correctly configured for the M4 core.
   When using imx-mkimage build the bootable image, add "-flags 0x200000" for the first container and add "-p3" to configure the partition for M4 core.
   (1) If only boot M4 core, use -p3 for the M4 image. For example,
        flash_m4: $(MKIMG) $(AHAB_IMG) scfw_tcm.bin m4_image.bin
        ./$(MKIMG) -soc QX -rev B0 -dcd skip -append $(AHAB_IMG) -c -flags 0x200000 -scfw scfw_tcm.bin -p3 -m4 m4_image.bin 0 0x34FE0000 -out flash.bin
   (2) If boot M4 core with A core, use -p3 for M4 core. And add -flags 0x200000 for the first container. Such as the availabe targets in imx-mkimage:flash_linux_m4.
   
   For more information about the reset, please refer to System Controller Firmware Porting Guide.

2. Please use imx-mkimage to load the application. Debugging or loading using debugger does not work.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board.
2.  Connect a micro USB cable between the host PC and the J11 USB port on the cpu board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~
Low Byte test success
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
~~~~~~~~~~~~~~~~~~~~~

