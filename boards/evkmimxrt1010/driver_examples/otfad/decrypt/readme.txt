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
- Mini/micro USB cable
- EVK-MIMXRT1010 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the ocotp example in the terminal window:
For flash target:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OTFAD example started!
Hitted context: 0x0
Erasing Serial NOR over FlexSPI...
Erase sector finished !
Decrypted data - successfully. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
For ram target:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OTFAD example started!
Hitted context: 0x0
Erasing whole chip over FlexSPI...
Erase whole chip finished !
Erasing Serial NOR over FlexSPI...
Erase sector finished !
Decrypted data - successfully. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J41.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.

Note:
To generate ciphertext, you can use OTFAD_GetEncryptedCounter() and OTFAD_EncryptData() API in example[selected] or other library.
1. use OTFAD_GetEncryptedCounter() API get encrypted counter.
2. use encrypted counter XOR plaintext to generate ciphertext.
