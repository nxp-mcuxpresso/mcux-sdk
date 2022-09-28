'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import c_int, c_uint8, c_uint32, c_longlong, Structure, POINTER


class FsciFrame(Structure):

    '''
    ctypes Structure that maps over the FsciFrame C structure.
    '''

    _fields_ = [
        ('sync', c_uint8),
        ('opGroup', c_uint8),
        ('opCode', c_uint8),
        ('length', c_uint32),
        ('data', POINTER(c_uint8)),
        ('crc', c_uint32),
        ('timestamp', c_longlong),
        ('index', c_uint32),
        ('endian', c_int),
        ('virtualInterface', c_uint8),
        ('direction', c_int)
    ]


class Endianess(object):
    Big = 0
    Little = 1


class DataDirection(object):
    HostToDevice = 0
    DeviceToHost = 1
