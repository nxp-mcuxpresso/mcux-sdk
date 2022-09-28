# Documentation of the sys Module

## Table of contents
1. Module Functionality
2. Module Structure
    * 2.1 utils
        * 2.1.1 Functionality
        * 2.1.2 API
    * 2.2 RawFrame
        * 2.2.1 Functionality
        * 2.2.2 API
    * 2.3 hsdkOSCommon
        * 2.3.1 Functionality
        * 2.3.2 API
    * 2.4 MessageQueue
        * 2.4.1 Functionality
        * 2.4.2 API
3. Dependencies

## 1. Module Functionality
The __sys__ module contains functions and structures common to each of the HDSK
other layers. It provides implementation for converting between primitive types
and arrays dependant on the endianness, a structure for sending data between
layers, as well as OS specific functions.

## 2. Module Structure
The module is structured into:
* _utils_, it provides functions for handling endianness
* _RawFrame_, used to encapsulate data into protocol independent frames
* _hsdkOSCommon_, wrapper functions over OS specific functions
* _MessageQueue_, functions and data types for a message queue

### 2.1 utils
#### 2.1.1 Functionality
As functions for user interaction expose their API to accommodate primitive
types, the functions in _utils_ handle the operations of converting between
primitive types and arrays based on the required endianness. As primitive types
in C go to a maximum of 64 bits, i.e. `uint64_t`, the maximum number of bytes
that the functions can handle is 8. Furthermore, _utils_ exports the enumerator
type defining endianness in HSDK.

#### 2.1.2 API
The functions exported by _utils_ are:
* `ReadX` - extracts the bytes from the given integer and stores them in the
specified order in the array
* `StoreX` - stores the bytes from the array in the integer in the specified
order

For each of these functions X is a value in the set {16, 32, 64}. The value of X
determines the size of the primitive type used in the operation.

### 2.2 RawFrame
#### 2.2.1 Functionality
For inter-layer communication, as well as storing sequences which are incomplete
(no stack protocol involved yet), the type _RawFrame_ is used. It provides a
simple method of encapsulating a sequence of bytes with its size and a timestamp
upon its creation. Most commonly, its usage is for either sending non-protocol
specific frames to the PhysicalDevice for transmission, or for accumulation of
bytes until they are processed as a meaningful frame.

#### 2.2.2 API
The functions exported by RawFrame:
* `CreateRxRawFrame` - Creates a RawFrame from the data received from the
device, while incrementing the counter of frames received
* `CreateTxRawFrame` - Creates a RawFrame from the data to be sent to the
device, while incrementing the counter of frames sent
* `DestroyRawFrame` - Deallocates the RawFrame

### 2.3 hsdkOSCommon
#### 2.3.1 Functionality
It provides wrapper functions with a common interface to OS specific functions.
Thus, it provides functions for handling threads, events, files, semaphores and
locks, in all supported OSes.
#### 2.3.2 API
_hsdkOSCommon_ exposes the following functions:
* For thread handling:
    * `HSDKCreateThread`
    * `HSDKDestroyThread`
* For event handling:
    * `HSDKCreateEvent`
    * `HSDKDeviceTriggerableEvent`
    * `HSDKFinishTriggerableEvent`
    * `HSDKDestroyEvent`
    * `HSDKResetEvent`
    * `HSDKSignalEvent`
    * `HSDKWaitEvent`
    * `HSDKWaitMultipleEvents`
* For file handling:
    * `HSDKOpenFile`
    * `HSDKCloseFile`
    * `HSDKWriteFile`
    * `HSDKReadFile`
    * `HSDKIsDescriptorValid`
    * `HSDKHandleError`
    * `HSDKInvalidateDescriptor`
* For lock handling:
    * `HSDKCreateLock`
    * `HSDKDestroyLock`
    * `HSDKAcquireLock`
    * `HSDKReleaseLock`
* For semaphore handling:
    * `HSDKCreateSemaphore`
    * `HSDKDestroySemaphore`
    * `HSDKAcquireExplicitlySemaphore`
    * `HSDKReleaseSemaphore`

### 2.4 MessageQueue
#### 2.4.1 Functionality
Each layer is represented by a thread, thus inter-thread communication is
achieved by message passing, messages being in the form of frames. The
_MessageQueue_ provides synchronized access to its elements.
#### 2.4.2 API
Exported functions:
* `InitializeMessageQueue`
* `DestroyMessageQueue`
* `MessageQueuePut`
* `MessageQueueGet`
* `MessageQueuePutWithSize`
* `MessageQueueDecrementSize`
* `MessageQueueGetContentSize`
* `IsEmpty`
* `PeekFront`
* `PushFront`

## 3. Dependencies
The functions inside the __sys__ module do not depend on the other modules
inside HSDK, although they depend internally on _hsdkOSCommon_. Externally,
their dependencies are based on OS specific functions and libraries for handling
threads, files, events, and so on.
