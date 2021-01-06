Overview
========
The pf1550 driver example demonstrates the usage of pf1550 SDK component driver.
The example shows the usage of PF1550 API to:
1. Set regulator output voltages;
2. Query regulator output voltages;
3. Dump PF1550 register content;
4. Charge a Li-on Battery Cell.

To use this example, user need to pay attention the output voltage when update the regulator
output and make sure the output voltage to set will not cause hardware damage;
You need also to pay attention to the charging voltage setting when charging Li-on battery cell,
and make sure that the battery is not over-charged.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- J-Link Debug Probe
- 5V power supply
- Personal Computer
- Li-on Battery Cell

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1.  Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2.  Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
The log below shows the output of the pf1550 example in the terminal window:

-------------- PF1550 on board PMIC driver example --------------

Please select the PMIC example you want to run:
[1]. Setting Regulator Output Voltage
[2]. Dumping Regulator Output Voltage
[3]. Dumping Selected Register Content
[4]. Charge Li-on Battery

User can press the number key to try the corresponding function of the demo.

Note
In order to protect the i.MX 7ULP from over-voltage, it is recommended to setting
regulator's output voltage with following restraint:
Buck Switch1's range: 800mV ~ 1100mV;
Buck Switch2's range: Fixed to 1200mV;
Buck Switch3's range: Fixed to 1800mV;
LDO1's range        : 3000mV to 3300mV;
LDO2's range        : Fixed to 3300mV;
LDO3's range        : Fixed to 1800mV.
The Setting Regulator Output Voltage function of this example is used to demonstrate
the usage of SDK PF1550 bare-bone driver, user need to adjust the regulator output
according to specific board design.
