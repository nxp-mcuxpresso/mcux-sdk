'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import byref, c_uint32, POINTER

import com.nxp.wireless_connectivity.hsdk.singleton as Singleton

from com.nxp.wireless_connectivity.commands.fsci_frame_description import Protocol
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Availability, DeviceState
from com.nxp.wireless_connectivity.hsdk.device.physical_device import PhysicalDevice
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader


@Singleton.singleton
class DeviceManager(object):

    '''
    Class that handles device discovery and creation of objects that map on devices.
    '''

    def __init__(self):
        '''
        Constructor method for DeviceManager that also loads the UART library.
        '''
        self.devices = []
        self.loader = LibraryLoader()
        self.CUartLibrary = self.loader.CUartLibrary
        self.CUartLibrary.InitializeDeviceManager()
        self.initDeviceList()

    def initDeviceList(self, detect_sniffers=False):
        '''
        Handles the initialization of the devices. Takes care of device detection based on
        the GetAllDevices function from the C library.
        '''
        self.devices = [PhysicalDevice(ds) for ds in PhysicalDevice.OPENED_DEVICES]

        ''' First retrieve the number of devices and store in pcount. '''
        GetAllDevices = self.CUartLibrary.GetAllDevices  # function pointer
        pcount = c_uint32()
        GetAllDevices(byref(pcount))
        ''' Now use pcount to retrieve all elements. '''
        GetAllDevices.restype = POINTER(DeviceState * pcount.value)
        dsp = GetAllDevices(byref(pcount))  # DeviceState*

        for i in range(pcount.value):
            if dsp.contents[i].isKinetisWDevice and (dsp.contents[i].availability != Availability.DeviceError):
                self.devices.append(PhysicalDevice(dsp.contents[i]))

        if detect_sniffers:

            from com.nxp.wireless_connectivity.commands.thread.sync_requests import Sniffer_Detect

            for i in range(len(self.devices)):

                # send a command to which only sniffers respond
                confirm = Sniffer_Detect(self.devices[i].name, timeout=1)

                # sniffer
                if confirm is not None:
                    self.devices[i].is_sniffer = True

                # not sniffer
                else:
                    # Sniffer_Detect opens the device, so we'll close it here
                    self.devices[i].close()
                    # and remove any singleton reference
                    for k in Singleton.known_instances.keys():
                        if self.devices[i].name in str(k):
                            obj = Singleton.known_instances.pop(k)
                            if 'FsciFramer' in obj.__class__.__name__:
                                obj.destroy()

    def getDevices(self):
        '''
        Getter for all present devices.
        '''
        return self.devices

    def getDevice(self, deviceName):
        '''
        Getter of a specific device based on its name.

        @param deviceName: the device OS identifier. e.g. /dev/ttyACMx on Linux.
        '''
        for device in self.devices:
            if str(device.name.decode()) == deviceName:
                return device
        return None
