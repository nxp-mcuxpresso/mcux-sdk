'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from __future__ import print_function
from com.nxp.wireless_connectivity.commands.fsci_frame_description import Protocol
from com.nxp.wireless_connectivity.hsdk.config import DEBUG, VERBOSE, MONITOR_MODE, COLORED_OUTPUT, USE_LOGGER
from com.nxp.wireless_connectivity.hsdk.CFsciLibrary import FsciFrame
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader

from binascii import hexlify, unhexlify
from ctypes import cast, c_void_p, POINTER
from datetime import datetime
import sys
import struct


try:
    from numbers import Number
except ImportError:  # New in version 2.6.
    Number = (int, long)


if USE_LOGGER:
    DEBUG = False
    import logging
    logger = logging.getLogger('root.utils')


def overrides(interface_class):
    def overrider(method):
        assert(method.__name__ in dir(interface_class))
        return method
    return overrider


class Observable(list):

    """
    A class for objects that can be observed.  When its notifyObservers()
    method is called with an event, it passes that event on to its
    observers.
    """

    fsciLibrary = LibraryLoader().CFsciLibrary
    fsciLibrary.DestroyFSCIFrame.argtypes = [c_void_p]

    def addObserver(self, observer, callback=None, sync_request=False):
        if (observer, callback) not in self:
            self.append((observer, callback, sync_request))

    def removeObserver(self, observer):
        for entry in self:
            if entry[0] == observer:
                self.remove(entry)

    def removeObservers(self, observers=[]):
        for observer in observers:
            self.removeObserver(observer)

    def removeAllObservers(self):
        self[:] = []

    def notifyObservers(self, deviceName, og, oc, event, protocol):

        observerFound = False

        for entry in self:
            observer, callback, sync_request = entry
            if observer.opGroup == og and observer.opCode == oc:
                observerFound = True
                observer.deviceName = deviceName
                observer.observeEvent(self, event, callback, sync_request)

        if not observerFound:

            if DEBUG and not MONITOR_MODE:
                print ('[Receive] Unknown event', str((hex(og), hex(oc))), '-> free memory')
                Observable.fsciLibrary.DestroyFSCIFrame(event)

            if MONITOR_MODE:
                if protocol == Protocol.Thread:
                    from com.nxp.wireless_connectivity.commands.thread.events import allObservers
                elif protocol == Protocol.BLE:
                    from com.nxp.wireless_connectivity.commands.ble.events import allObservers
                elif protocol == Protocol.ZigBee:
                    from com.nxp.wireless_connectivity.commands.zigbee.events import allObservers
                try:
                    allObservers[(og, oc)].deviceName = deviceName
                    allObservers[(og, oc)].observeEvent(self, event, None, False)
                except KeyError:
                    if DEBUG:
                        print ('[Receive] Could not find an observer for', str((hex(og), hex(oc))))
                        Observable.fsciLibrary.DestroyFSCIFrame(event)


class Observer(object):

    """
    A class for objects that observe an Observable. The Observable will
    call the Observer's observeEvent() method.
    """

    def __init__(self, name):
        self.name = name
        self.deviceName = None

    def observeEvent(self, framer, event, callback, sync_request):
        # Cast the event to a FSCI frame.
        fsciFrame = cast(event, POINTER(FsciFrame))
        # Debug information
        if DEBUG:
            print ('>>> %s @ %s\n' % (self.name, datetime.now().strftime("%H:%M:%S.%f")),)
            print ('Sync    [1 byte]  = ' + str(hex(fsciFrame.contents.sync)))
            print ('OpGroup [1 byte]  = ' + str(hex(fsciFrame.contents.opGroup)))
            print ('OpCode  [1 byte]  = ' + str(hex(fsciFrame.contents.opCode)))
            print ('Length  [1 byte]  = ' + str(hex(fsciFrame.contents.length)))
        elif USE_LOGGER:
            logging._acquireLock()
            logger.debug('>>> %s @ %s' % (self.name, datetime.now().strftime("%H:%M:%S.%f")))
            logger.debug('Sync    [1 byte]  = ' + str(hex(fsciFrame.contents.sync)))
            logger.debug('OpGroup [1 byte]  = ' + str(hex(fsciFrame.contents.opGroup)))
            logger.debug('OpCode  [1 byte]  = ' + str(hex(fsciFrame.contents.opCode)))
            logger.debug('Length  [1 byte]  = ' + str(hex(fsciFrame.contents.length)))
            logging._releaseLock()


def list_to_int(list_num, reverse=True):
    # Check if already integer
    if isinstance(list_num, Number):
        return list_num
    if list_num == []:
        return 0
    # Supporting just byte arrays for now
    if any([x for x in list_num if x > 0xff]):
        print ('[list_to_int] List does not contain only bytes.')
        return []
    if not reverse:
        return int(''.join(['%02x' % x for x in list_num]), 16)
    else:
        return int(''.join(['%02x' % x for x in list_num][::-1]), 16)


def to_bytes(n, length, reverse=True):
    
    # verify if length is byte array so transform back to unsigned value
    if isinstance(length, bytearray):
        if len(length) <= 2:
            length = struct.unpack(">H", length)[0]
        elif len(length) == 4:
            length = struct.unpack(">I", length)[0]
        elif len(length) == 8:
            length = struct.unpack(">Q", length)[0]

    # sanity checks
    if n == [] and length > 0:
        return bytearray(length)

    if n == [] or length == [] or n == None or length == None or length == 0:
        return bytearray(0)

    if isinstance(n, bytearray):
        return n
    if isinstance(n, list):
        if any([x for x in n if x > 0xff]):
            print ('[list_to_int] List does not contain only bytes.')
            return bytearray()
        elif n == []:
            return bytearray(length)
        else:
            return bytearray(n)
    if isinstance(n, str):
        return bytearray(n, 'utf-8')

    h = '%x' % n
    s = ('0' * (len(h) % 2) + h).zfill(length * 2)#.decode('hex')
    s = unhexlify(s)
    return s if not reverse else s[::-1]


def getBytesFromIPv6Address(address, endianness='little'):
    '''
    @attention: This method uses the 3rd party module netaddr. Install it from
    https://pypi.python.org/pypi/netaddr
    @param address: IPV6 address, type String. Supports all kinds of formats.
    '''
    try:
        import netaddr
    except ImportError:
        print ('3rd party netaddr module is not installed.')
        sys.exit(1)

    value = netaddr.IPAddress(address).value
    h = '%x' % value
    if endianness == 'little':
        return bytearray(('0' * (len(h) % 2) + h).decode('hex'))[::-1]
    else:
        return bytearray(('0' * (len(h) % 2) + h).decode('hex'))


if COLORED_OUTPUT:
    try:
        from colorama import init
        from colorama import Fore
        init(autoreset=True)
    except ImportError:
        Fore = type('Fore', (object,), {'CYAN': '', 'MAGENTA': '', 'RED': '', 'YELLOW': ''})
else:
    Fore = type('Fore', (object,), {'CYAN': '', 'MAGENTA': '', 'RED': '', 'YELLOW': ''})


def print_pkt(device_name, pkt, timestamp=None):
    if hasattr(pkt, 'time'):
        print (Fore.MAGENTA + pkt.time + ': ' + str(pkt))
    elif timestamp is not None:
        print (Fore.MAGENTA + str(timestamp) + ': ' + str(pkt))
    else:
        print (Fore.MAGENTA + str(datetime.now()) + ': ' + hexlify(pkt))


count = -1


def print_command(device_name, command):
    global count
    count += 1

    if VERBOSE:
        try:
            print (Fore.YELLOW + '[Command %d] ' % count + device_name + ': ' + command.__class__.__name__ + ' -> {', end="")
            it = 0
            for k, v in command.__dict__.iteritems():
                if it != 0:
                    print (Fore.YELLOW + ', ', end="")
                if isinstance(v, float):
                    print (Fore.CYAN + k + ': ' + str(v), end="")
                elif isinstance(v, Number):
                    print (Fore.YELLOW + k + ': ' + hex(v), end="")
                elif isinstance(v, bytearray):
                    print (Fore.YELLOW + k + ': 0x' + hexlify(v), end="")
                elif isinstance(v, list) and all(isinstance(item, Number) for item in v):
                    print (Fore.YELLOW + k + ': ' + str(['0x%X' % x for x in v]), end="")
                elif isinstance(v, str) and not v.isalnum():
                    print (Fore.YELLOW + k + ': 0x' + hexlify(v), end="")
                else:
                    print (Fore.YELLOW + k + ': ' + str(v), end="")
                it += 1
            print (Fore.YELLOW + '}')

        except AttributeError:  # 'NoneType' object has no attribute '__dict__'
            print (Fore.YELLOW + '[Command] ' + device_name + ': ' + command.__class__.__name__)


def print_event(device_name, event):
    global count
    count += 1

    if VERBOSE:
        print (Fore.CYAN + '[Event %d] ' % count + device_name + ': ' + event.__class__.__name__ + ' -> {', end="")

        it = 0
        for k, v in event.__dict__.items():
            if k == '_DevicePort':
                continue
            if it != 0:
                print (Fore.CYAN + ', ', end="")
            if isinstance(v, float):
                print (Fore.CYAN + k + ': ' + str(v), end="")
            elif isinstance(v, Number):
                print (Fore.CYAN + k + ': ' + hex(v), end="")
            elif isinstance(v, list) and all(isinstance(item, Number) for item in v):
                print (Fore.CYAN + k + ': ' + str(['0x%X' % x for x in v]), end="")
            else:
                print (Fore.CYAN + k + ': ' + str(v), end="")
            it += 1
        print (Fore.CYAN + '}')


CRC16_XMODEM_TABLE = [
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0,
]


def crc16xmodem(contents):
    crc = 0

    for c in contents:
        crc = ((crc << 8) & 0xff00) ^ CRC16_XMODEM_TABLE[((crc >> 8) & 0xff) ^ ord(c)]

    return crc & 0xffff
