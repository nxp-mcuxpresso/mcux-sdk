---
name: Bug report
about: Create a report to help us improve
title: "[BUG]"
labels: bug
assignees: ''

---

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
* Environment (please complete the following information):
   - Tag/Commit hash: [e.g. MCUX_2.9.0]
   - Toolchain: [e.g. ARMGCC 9-2020-q2-update]
   - Board/SoC: [e.g. FRDM-K64F]
   - Example [e.g. adc16_interrupt]  
* Steps to reproduce the behavior:
  Below uses adc16_interrupt example ARMGCC run issue on frdm-k64f as an example, you may follow similar description.
  1. cd frdmk64f\driver_examples\adc16\interrupt\armgcc
  2. [optional] If modified code is needed, please provide the modified code snippet.
  3. Run build_debug.bat to build example, see error. Skip the below steps for run error.
  4. Connect frdmk64f board to PC and do set up follow the description in frdmk64f\driver_examples\adc16\interrupt\readme.txt. Refer to the guide running a ARMGCC demo to download and run the example, see error in console output.

**Expected behavior**
A clear and concise description of what you expected to happen.

**Screenshots and console output**
If applicable, add screenshots and paste your console output to help explain your problem. If the error information is captured by other tools such as Oscilloscope, logic analyzer or wireshark, please share us the screenshot of these information which could help the progress.

**Additional context**
Add any other context about the problem here.
