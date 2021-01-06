Overview
========

The OTFAD example shows how to use on the fly AES-128 decryption driver.

In this example, the external flash memory will be used to show the example.
The flash memory will store ciphertext, and this example will use OTFAD to decrypt ciphertext with flexspi. 
It including configure AES key and counter into OTFAD and OTFAD will decryption automatically.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- EVK-MIMXRT685 board
- Personal Computer

Board settings
==============

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J40) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OTFAD example started!
Hit context: 0x0
Erasing Serial NOR over FlexSPI...
Erase sector finished !
Decrypted data - successfully. 

Note:
To generate ciphertext, you can use OTFAD_GetEncryptedCounter() and OTFAD_EncryptData() API in example[selected] or other library.
1. use OTFAD_GetEncryptedCounter() API get encrypted counter.
2. use encrypted counter XOR plaintext to generate ciphertext.

