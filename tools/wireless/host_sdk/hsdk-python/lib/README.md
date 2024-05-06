This folder contains the DLLs for host_sdk. Only Python 2.7 supported.

1. Depending on the Python version installed 32 bit / 64 bit, copy the appropriate
DLL to <Python install dir>\DLLs (usually C:\Python27\DLLs).

2. Make sure you have __Visual C++ Redistributable Packages for Visual Studio 2013__ installed, depending on the arch (vcredist_x86.exe or vcredist_x64.exe).

3. Add Python source folder to PYTHONPATH

    - `My Computer > Properties > Advanced System Settings > Environment Variables > System Variables`
    - Modify existing or create new variable named `PYTHONPATH`. Should become something like:
    `C:\Python27\Lib;C:\Python27\DLLs;C:\Python27\Lib\lib-tk;C:\...\kw-host-sdk\hsdk-python\src`

4. Test:

    - `> cd host_sdk\hsdk-python\src\com\nxp\wireless_connectivity\test`
    - `> python getaddr.py COM42`

5. Optional: copy hsdk/res/hsdk.conf to C:\Python27\DLLs in order to globally configure
parameters such as FSCI-ACKs. No .conf file means FSCI-ACKs are disabled by default.
