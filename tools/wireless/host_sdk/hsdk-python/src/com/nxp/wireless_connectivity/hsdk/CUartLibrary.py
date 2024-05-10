'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import Structure, c_char_p, c_int, c_uint8
import sys


class DeviceState(Structure):

    '''
    ctypes Structure that maps over the DeviceState C structure.
    '''

    _fields_ = [
        ('availability', c_int),
        ('friendlyName', c_char_p),
        ('deviceName', c_char_p),
        ('isKinetisWDevice', c_uint8),
        ('vid', c_char_p),
        ('pid', c_char_p)
    ]

    def __str__(self):
        s = ''
        # get Availability human-readable name
        for k, v in Availability.__dict__.items():
            if v == self.availability:
                s += k + ' '
        s += str(self.friendlyName) + ' '
        s += str(self.deviceName) + ' '
        s += str(bool(self.isKinetisWDevice)) + ' '
        s += str(self.vid) + ' '
        s += str(self.pid)
        return s


class DeviceType(object):
    UART = 0
    USB = 1
    PCAP = 2
    SPI = 3
    BT = 4


class Baudrate(object):
    BR110 = 0
    BR300 = 1
    BR600 = 2
    BR1200 = 3
    BR2400 = 4
    BR4800 = 5
    BR9600 = 6
    BR19200 = 7
    BR38400 = 8
    BR57600 = 9
    BR115200 = 10
    BR921600 = 11


class Availability(object):
    NoInfo = 0
    Available = 1
    NotPluggedIn = 2
    InUse = 3
    DeviceError = 4
