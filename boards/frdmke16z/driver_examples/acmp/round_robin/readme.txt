Overview
========
The ACMP Round-Robin project is a simple demonstration program that uses the SDK software. User
must set the round-robin mode trigger in specific board properly according to the board resource
before running the example. When the example running, it sets positive port as fixed channel and
internal DAC output as comparison reference in positive port and sets the channels input by user
as round-robin checker channel. The example will enter stop mode and wait user to change the voltage
of round-robin checker channel. It will exit stop mode after the voltage of round-robin checker
channel changed by user.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE16Z board
- Personal Computer

Board settings
==============
This example project uses ACMP instance 0 to compare the voltage signal input from channel 0(J4-12)
with the voltage signal(half of VDDA) output by ACMP's internal DAC. In order to observe the low
power wakeup phenomenon, channel 0(J4-12) should be connected to GND signal(J2-14) on the board before
the example running. Example will exit stop mode when channel 0(J4-12) is disconnected from GND signal
and connect to volatage above half of VDDA, the disconnected time is last for about 1s.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal with the following settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, following information can be seen on the OpenSDA terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Example to demonstrate low power wakeup by round robin comparison!
In order to wakeup the MCU, please change the analog input voltage to be different from original pre-state setting.

Press S for enter: Stop Mode

The system entered into stop mode.

The system exited from stop mode!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
