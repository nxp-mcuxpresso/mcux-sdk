# Python Wrapper for Host SDK

Description: This software is designed to help developers interact with Host SDK (a set of C libraries) from the Python programming language.

## Project Setup

### Linux
1. Build Host SDK

    `cd host_sdk/hsdk`

    `make`

    `sudo make install`

2. Add Python source folder to PYTHONPATH

    `export PYTHONPATH=$PYTHONPATH:/home/.../host_sdk/hsdk-python/src` (optional: add this line to ~/.bashrc)

    Edit `/etc/sudoers` with your favorite text editor. Modify

    `Defaults	env_reset` -> `Defaults	env_keep="PYTHONPATH"`

### Windows
1. Host SDK .dll files are located under `host_sdk\hsdk-python\lib\HSDK*.dll`. Optional: compile Host SDK with Microsoft Visual Studio 2013.

2. Make sure to have __Visual C++ Redistributable Packages for Visual Studio 2013__ installed, depending on the HSDK library version (vcredist_x86.exe or vcredist_x64.exe).

3. Add Python source folder to PYTHONPATH

    `My Computer > Properties > Advanced System Settings > Environment Variables > System Variables`

    Modify existing or create new variable named `PYTHONPATH`. Should become something like

    `C:\Python3x\Lib;C:\Python3x\DLLs;C:\Python3x\Lib\lib-tk;C:\...\host_sdk\hsdk-python\src`

4. Copy HSDK.dll to C:\Python3x\DLLs. Copy HSDK_x64.dll to C:\Python3x\DLLs\HSDK.dll if using the x64 Python version.


## Testing

Run the project's demos

`sudo host_sdk/hsdk-python/src/com/nxp/wireless_connectivity/test/commissioning.py`

## Development

### Requests
Sending a request consists of three steps: opening a communication channel, customizing the request and sending the bytes.

`comm = Comm('/dev/ttyACM0')` or `comm = Comm('COM42')`

`request = SocketCreateRequest(`
        `SocketDomain=SocketCreateRequestSocketDomain.AF_INET6,`
        `SocketType=SocketCreateRequestSocketType.Datagram,`
        `SocketProtocol=SocketCreateRequestSocketProtocol.UDP`
    `)`

`comm.send(Spec().SocketCreateRequestFrame, request)`

### Events
In order to obtain the event triggered by the request, an observer and callback must be added to the program logic.

`def callback(expectedEvent): print 'Callback for ' + str(type(expectedFrame))`

`observer = SocketCreateConfirmObserver()`

`comm.fsciFramer.addObserver(observer, callback)`

Note 1: if the callback argument is not present, by default the program will output the received frame in the console.

Note 2: the callback method __must__ have a single parameter which will be used to gain access to the event object.

### Operations
An operation consists in sending a request and obtaining the events via observers, automatically.

`request = SocketCreateRequest(`
        `SocketDomain=SocketCreateRequestSocketDomain.AF_INET6,`
        `SocketType=SocketCreateRequestSocketType.Datagram,`
        `SocketProtocol=SocketCreateRequestSocketProtocol.UDP`
    `)`

`operation = SocketCreateOperation('/dev/ttyACM0', request)`

`operation.begin()`

This will send the request and print the SocketCreateConfirm to the console. Adding a custom callback is easy:

`operation = SocketCreateRequest('/dev/ttyACM0', request, [callback])`
