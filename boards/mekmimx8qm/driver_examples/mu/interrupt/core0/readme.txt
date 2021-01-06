Overview
========
The mu_interrupt example shows how to use MU driver in interrupt way:

In this example:
1. Core 0 send message to Core 1 in interrupt mode via MU module.
2. Core 1 send message back to Core 0 in interrupt mode.
3. Core 0 receive message sent from Core 1 in interrupt mode.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK Board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the demo
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
This example shows two cores communicating using MU. Both core0 and core1 interrupt example should be run at the same time!

When the demo runs successfully, the log would be seen on the core0's debug terminal like as below:

~~~~~~~~~~~~~~~~~~~~~
MU example interrupt!
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
