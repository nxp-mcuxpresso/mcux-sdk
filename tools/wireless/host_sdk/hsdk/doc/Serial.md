# Documentation of the serial Module

## Table of contents
1. Module Functionality
2. Module Structure
    * 2.1 PhysicalDevice
        * 2.1.1 Functionality
        * 2.1.2 API
    * 2.2 UARTConfiguration
        * 2.2.1 Functionality
        * 2.2.2 API
    * 2.3 UARTDiscovery
        * 2.3.1 Functionality
        * 2.3.2 API
    * 2.4 UARTDevice
        * 2.4.1 Functionality
        * 2.4.2 API
3. Dependencies

## 1. Module Functionality
The _serial_ module provides functions based on the supported devices. Among
these, functions to encapsulate a physical device into well defined structures,
functions for configuring the serial port, device discovery and more.

## 2 Module Structure
The module is structured in:
* PhysicalDevice - generic functions for all physical devices
* UART folder provides a UART specific implementation of functions
    * UARTConfiguration - functions for configuring the UART port
    * UARTDiscovery - functions for detection of devices
    * UARTDevice - functions for interaction with the device

### 2.1 PhysicalDevice
#### 2.1.1 Functionality
_PhysicalDevice_ provides a common set of functions available to each
implementation of a device standard. It provides function pointers for opening
and closing a device, as well as sending data to the device. It creates a thread
 to wait on data from the device and raises an event enqueuing the data to the
 framer.
#### 2.1.2 API
Exposed functions:
* `InitPhysicalDevice` - creates a _PhysicalDevice_ data type, starts the thread
 and initializes a specific device
* `DestroyPhysicalDevice` - frees the object
* `OpenPhysicalDevice`
* `ClosePhysicalDevice`
* `ConfigurePhysicalDevice`
* `WritePhysicalDevice`
* `AttachToPhysicalDevice` - a framer attaches to a _PhysicalDevice_ to receive
notifications
* `DetachFromPhysicalDevice`

### 2.2 UARTConfiguration
#### 2.2.1 Functionality
_UARTConfiguration_ provides a data type for encapsulating UART configuration as
 well as functions to set the specified configuration to the device.
#### 2.2.2 API
_UARTConfiguration_ exports:
* `setDefaultLineConfig` - sets the default line configuration
* `setDefaultTimeConfig` - sets the default timeout configuration
* `defaultConfigurationData` - creates an object with the default configurations
* `freeConfigurationData` - frees the configuration data
* `setBaudrate` - sets the baudrate for a configuration data type to the
specified value
* `setParity` - sets the parity for a configuration data type
* `InitPort` - configures the device

### 2.3 UARTDiscovery
#### 2.3.1 Functionality
_UARTDiscovery_ finds the connected devices and exposes their state, name and
other relevant information.
#### 2.3.2 API
_UARTDiscovery_ exports:
* `GetAllDevices` - creates a list of all devices plugged in
* `isKinetisWDevice` - checks to see if the device is a NXP Kinetis-W device, based
 on the (vendor ID, product ID) pair

### 2.4 UARTDevice
#### 2.4.1 Functionality
_UARTDevice_ provides support for interacting with a UART device. It may open,
close, read from and write to a UART device, providing concrete implementation
of these functions to the _PhysicalDevice_.
#### 2.4.2 API
_UARTDevice_ exports:
* `AttachToUARTDevice` - assigns concrete implementations to _PhysicalDevice_
function pointers
* `DetachFromUARTDevice` - sets the _PhysicalDevice_ function pointers to NULL

## 3 Dependencies
The __serial__ module depends on the __sys__ module for _MessageQueue_,
_RawFrame_ and _hsdkOSCommon_ functions. Internally, they depend on each other.
