Overview
========
The mu_polling example shows how to use MU driver in polling way:

In this example:
1. Core 0 send message to Core 1 in polling mode via MU module.
2. Core 1 send message back to Core 0 in polling mode.
3. Core 0 receive message sent from Core 1 in polling mode.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the demo
1.  Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Build core1 project first, then build core0 project.
4.  Download the core0 program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like as below and LED will blink:

~~~~~~~~~~~~~~~~~~~~~
MU example polling!
Send: 0. Receive 0
Send: 1. Receive 1
Send: 2. Receive 2
Send: 3. Receive 3
Send: 4. Receive 4
Send: 5. Receive 5
Send: 6. Receive 6
Send: 7. Receive 7
Send: 8. Receive 8
Send: 9. Receive 9
Send: 10. Receive 10
Send: 11. Receive 11
Send: 12. Receive 12
Send: 13. Receive 13
Send: 14. Receive 14
Send: 15. Receive 15
Send: 16. Receive 16
Send: 17. Receive 17
Send: 18. Receive 18
Send: 19. Receive 19
Send: 20. Receive 20
Send: 21. Receive 21
Send: 22. Receive 22
Send: 23. Receive 23
Send: 24. Receive 24
Send: 25. Receive 25
Send: 26. Receive 26
Send: 27. Receive 27
Send: 28. Receive 28
Send: 29. Receive 29
Send: 30. Receive 30
Send: 31. Receive 31
MU example run succeed!
~~~~~~~~~~~~~~~~~~~~~
