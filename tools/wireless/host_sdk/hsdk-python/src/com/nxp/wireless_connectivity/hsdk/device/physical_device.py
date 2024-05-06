'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import c_char_p, c_int, c_uint32, c_void_p
from time import sleep

from com.nxp.wireless_connectivity.commands.fsci_frame_description import FsciAckPolicy
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import DeviceType, Baudrate
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader
from com.nxp.wireless_connectivity.hsdk.config import MAX_SPEED_HZ, THREAD_HARNESS
from com.nxp.wireless_connectivity.hsdk.utils import DEBUG


class PhysicalDevice(object):

    '''
    Class that operates on physical Kinetis-W devices. It handles the operations of
    open/close, by deferring calls to the underlying C libraries.
    '''
    OPENED_DEVICES = []

    def __init__(self, deviceState):
        '''
        Constructor of a PhysicalDevice. The only argument is the device state.

        @param deviceState: Object that describes the state of the device, the most important
                            field of it being the device name.
        '''
        self.devicePointer = None
        self.ll = LibraryLoader()
        self.deviceState = deviceState
        self.name = deviceState.deviceName
        self.is_sniffer = False
        self.config = None
        self.ack_policy = None

        if self.name.startswith(b'eth'):
            self.device_type = DeviceType.PCAP
        elif self.name.startswith(b'/dev/spidev'):
            self.device_type = DeviceType.SPI
            self.ll.CSpiLibrary.defaultSettingsSPI.restype = c_void_p
            self.config = self.ll.CSpiLibrary.defaultSettingsSPI()
        else:
            self.device_type = DeviceType.UART
            self.ll.CUartLibrary.defaultConfigurationData.restype = c_void_p
            self.config = self.ll.CUartLibrary.defaultConfigurationData()

    def __str__(self):
        return str(self.deviceState) + ' Sniffer: ' + str(self.is_sniffer)

    def __repr__(self):
        return str(self.deviceState) + ' Sniffer: ' + str(self.is_sniffer)

    def open(self, ack_policy=FsciAckPolicy.GLOBAL, baudrate=Baudrate.BR115200):
        '''
        Method for opening a UART/RNDIS device. It defers the logic to the underlying C library.

        @param ack_policy: the policy for FSCI ACK synchronization
        @param baudrate: the baudrate of the serial connection
        '''
        # cannot change the ACK policy on-the-fly
        if not THREAD_HARNESS:
            if self.ack_policy is not None and self.ack_policy != ack_policy:
                print ('[WARNING] Cannot change the ACK policy for the already configured', self.name)

        # set baudrate on UART devices
        if self.device_type == DeviceType.UART:
            self.ll.CUartLibrary.setBaudrate.argtypes = [c_void_p, c_int]
            self.ll.CUartLibrary.setBaudrate(self.config, baudrate)

        # set speed (Hz) on SPI devices, on Linux only
        if self.device_type == DeviceType.SPI:
            self.ll.CSpiLibrary.setSpeedHzSPI.argtypes = [c_void_p, c_uint32]
            self.ll.CSpiLibrary.setSpeedHzSPI(self.config, MAX_SPEED_HZ)

        # disable flow control for JN devices and EEB-KW35
        if '0403' in self.deviceState.vid.decode() and ('6015' in self.deviceState.pid.decode() or '6001' in self.deviceState.pid.decode()):
            print ('[INFO] Flow control is disabled on port', self.name)
            self.ll.CUartLibrary.disableFlowControl.argtypes = [c_void_p]
            self.ll.CUartLibrary.disableFlowControl(self.config)

        # open device - init once
        if self.devicePointer is None:
            self.ll.CPhysicalLibrary.InitPhysicalDevice.restype = c_void_p
            self.ll.CPhysicalLibrary.InitPhysicalDevice.argtypes = [c_int, c_void_p, c_char_p, c_int]
            self.devicePointer = self.ll.CPhysicalLibrary.InitPhysicalDevice(
                self.device_type, self.config, c_char_p(self.name), ack_policy)
            self.ack_policy = ack_policy

        self.ll.CPhysicalLibrary.OpenPhysicalDevice.restype = c_int
        self.ll.CPhysicalLibrary.OpenPhysicalDevice.argtypes = [c_void_p]
        openStatus = self.ll.CPhysicalLibrary.OpenPhysicalDevice(self.devicePointer)
        if openStatus == 0:
            PhysicalDevice.OPENED_DEVICES.append(self.deviceState)

        # the PhysicalDevice thread spawned does little more for SPI devices
        if self.device_type == DeviceType.SPI:
            sleep(1)

        if DEBUG:
            if openStatus != 0:
                print ('[Python Wrapper][' + str(self.name) + '][Open] Fail, errno:' + str(openStatus))
            else:
                print ('[Python Wrapper][' + str(self.name) + '][Open] Success')

        return openStatus

    def close(self):
        '''
        Method for closing a UART device. It defers the logic to the underlying C library.
        '''
        self.ack_policy = None

        self.ll.CPhysicalLibrary.ClosePhysicalDevice.argtypes = [c_void_p]
        self.ll.CPhysicalLibrary.ClosePhysicalDevice.restype = c_int

        closeStatus = self.ll.CPhysicalLibrary.ClosePhysicalDevice(self.devicePointer)
        if closeStatus == 0:
            PhysicalDevice.OPENED_DEVICES.remove(self.deviceState)

        if DEBUG:
            if closeStatus != 0:
                print ('[Python Wrapper][' + str(self.name) + '][Close] Fail, errno:' + str(closeStatus))
            else:
                print ('[Python Wrapper][' + str(self.name) + '][Close] Success')

        return closeStatus
