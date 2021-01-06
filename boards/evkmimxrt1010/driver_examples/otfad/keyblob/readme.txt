Overview
========

The OTFAD example shows how to use on the fly AES-128 decryption driver.

In this example, the external flash memory will be used to show the example.
The flash memory will store ciphertext and keyblob, and this example will use OTFAD to decrypt ciphertext with flexspi.
The FlexSPI fetches the context 0 key blob from the external flash memory, sends the data to the OTFAD which automatically
performs the required key blob unwrap function and loads the recovered plaintext data into the context 0 programming model registers.
OTFAD always processes key blob data for all four contexts when enabled, and the flash A1 zero address has been loaded valid key wraped data
for all four contexts and OTFAD will decryption automatically.

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
OTFAD keyblob example started!
Erasing Serial NOR over FlexSPI...
Erase sector finished !
Hitted context: 0x0
Decrypted data - successfully. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
For ram target:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OTFAD keyblob example started!
Erasing whole chip over FlexSPI...
Erase whole chip finished !
Erasing Serial NOR over FlexSPI...
Erase sector finished !
Hitted context: 0x0
Decrypted data - successfully. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note: flash target
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J41.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
   - if you want to run more time, you only need to hardware reset it and it will re-run again.

Note: ram target
To debug in ram, following steps are needed:
1. Select the ram target and compile.
2. Set the SW8: 1 off 2 off 3 off 4 on, then power on the board and connect USB cable to J41.
3. Start debugging in IDE.
    - ram taeget only can run one time because software needs to set SKBP only once after a hard reset.
    - if you want to run more time, you need to hardware reset it and re-step step 1/2/3.


Note:
To generate ciphertext, you can use OTFAD_GetEncryptedCounter() and OTFAD_EncryptData() API in example[selected] or other library.
1. use OTFAD_GetEncryptedCounter() API get encrypted counter.
2. use encrypted counter XOR plaintext to generate ciphertext.

Note:
To generate keyblob, address need to be 1KB aligned, otherwise OTFAD doesn't decrypt keyblob successfully in keyblob process.
