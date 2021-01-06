Overview
========
The TPM project is a simple demonstration program of the SDK TPM driver. It sets up the TPM
hardware block to output PWM signals on two TPM channels. The PWM dutycycle on both channels
is manually updated. On boards that have an LED connected to the TPM pins, the user will see
a change in LED brightness if user enter different values.

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
- Oscilloscope

Board settings
==============
Connect TP86(PTB0) to Oscilloscope channel 1.
Connect J9-4 to Oscilloscope channel 2. Please note both sides of R149 should be short-circuited.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1. Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2. Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3. Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Download the program to the target board.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, you can see information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TPM example to output PWM on 2 channels
You will see a change in LED brightness if an LED is connected to the TPM pin
If no LED is connected to the TPM pin, then probe the signal using an oscilloscope
Please enter a value to update the Duty cycle:
Note: The range of value is 0 to 9.
For example: If enter '5', the duty cycle will be set to 50 percent.
Value:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
