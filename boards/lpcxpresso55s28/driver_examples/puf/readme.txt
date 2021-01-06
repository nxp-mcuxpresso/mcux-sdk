Overview
========
The PUF Example project is a demonstration program that uses the KSDK software implement secure key storage using PUF software driver.

Usual use consists of these steps:
1. 	Enroll: The controller retrieves the Startup Data (SD) from the memory (SRAM), derives a digital fingerprint, 
	generates the corresponding Activation Code (AC) and sends it to the storage system. 
	Perform this step only once for each device. There is a control register that can block further enrollment. 
	This control register is write only and is reset on a power-on reset.

2. 	Start: The AC generated during the enroll operation and the SD are used to reconstruct the digital fingerprint. 
	It is done after every power-up and reset.

3. 	Generate Key: The controller generates an unique key and combines it with the digital fingerprint to output a key code. 
	Each time a Generate Key operation is executed a new unique key is generated.

4. 	Set Key: The digital fingerprint generated during the Enroll/Start operations and the key provided by the Client Design (CD) 
	are used to generate a Key Code. This KC can be stored externally. Perform this operation only once for each key.

5. 	Get Key: The digital fingerprint generated during the Start operation and the KC generated during a Set Key operation 
	are used to retrieve a stored key. Perform this operation every time a key is needed.

Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- LPCXpresso55S28 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
Note: MCUXpresso IDE project default debug console is semihost
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (P6) on the board
2.  Open a serial terminal with the following settings (See Appendix A in Getting started guide for description how to determine serial port number):
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the PUF driver example in the terminal window (the key value will vary):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PUF Peripheral Driver Example

Reconstructed key = ad e7 b4 fe 99 ce 41 b7 c6 f9 78 2f 49 6b 87 27
Example end.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
