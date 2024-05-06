# Documentation of the protocol Module

## Table of contents
1. Module Functionality
2. Module Structure
    * 2.1 Framer
        * 2.1.1 Functionality
        * 2.1.2 API
    * 2.2 FSCIFrame
        * 2.2.1 Functionality
        * 2.2.2 API
    * 2.3 FSCIFramer
        * 2.3.1 Functionality
        * 2.3.2 API
3. Dependencies

## 1. Module Functionality
The __protocol__ module provides functions based on the supported protocol
representation. They provide functions for converting protocol data types
into sequences of bytes, as well as accumulating received bytes and interpreting
them as protocol frames.

## 2. Module structure
The module is structured into:
* Framer - generic functions for all protocol specific framers
* FSCI folder provides a protocol specific implementation
    * FSCIFrame - the data type for the protocol and its representation
    * FSCIFramer - functions for converting between FSCIFrame and a byte sequence

### 2.1 Framer
#### 2.1.1 Functionality
_Framer_ provides a common set of functions available to each implementation of
a protocol. It provides function pointers for converting a protocol
representation to a sequence of bytes, as well as a thread that converts data
received from the serial into protocol representations and capable of raising
events.
#### 2.1.2 API
The _Framer_ exposes the following functions:
* `InitializeFramer` - creates the object from the Framer data type
representation and starts its thread. It expects to receive a pointer to the
device it is communicating with, a callback for announcing frames, a starting
point for framing and a reference to the caller.
* `DestroyFramer` - frees the memory for the framer
* `SendFrame` - converts a protocol data type into a sequence of bytes
* `ReadJunkData` - extracts bytes from the received data until the start byte
* `ReadSingleByte` - extracts a single byte from the received data
* `ReadMultiByte` - extracts multiple bytes from the received data

### 2.2 FSCIFrame
#### 2.2.1 Functionality
It defines the data type for representing a FSCI protocol frame, as well as
functions for handling it.
#### 2.2.2 API
Exported functions:
* `CreateFSCIFrame` - receives the components of a frame and returns an object
for the data type _FSCIFrame_. It adds the starting byte and CRC bytes as well.
* `PrintFSCIFrame` - prints the content of a frame
* `DestroyFSCIFrame` - deallocates the object

### 2.3 FSCIFramer
#### 2.3.1 Functionality
Implements the conversion between meaningful representation and sequence
of bytes. It functions as a state machine, by advancing to the next state
after each extraction of data from the accumulated date in the _Framer_'s
message queue.
#### 2.3.2 API
Exported functions:
* `CreateFSCIPacket` - returns a sequence of bytes based on the contents of the
received _FSCIFrame_
* `FSCIStartState` - returns the start state of the FSCI StateMachine
* `FSCIFinalState` - returns the accepting state of the FSCI StateMachine
* `FSCIFramerInitialization` - assigns function implementations to the function
pointers of the _Framer_ object

Internally, _FSCIFramer_ implements a function for handling each field of the
protocol. Each function extracts data from the queue and advances the state
machine accordingly.

## 3. Dependencies
The __protocol__ module depends on the elements from the __sys__ module
(_MessageQueue_, _RawFrame_, _utils_ and _hsdkOSCommon_). Internally, each
specific implementation of a protocol depends on _Framer_.
