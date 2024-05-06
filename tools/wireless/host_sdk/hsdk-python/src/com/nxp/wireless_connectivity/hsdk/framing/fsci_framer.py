'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import POINTER, CFUNCTYPE, c_int, c_uint8, c_uint32, c_void_p, cast
from datetime import datetime
import sys
if sys.version[0] == '2':
    from Queue import Queue, Empty
else:
    from queue import Queue, Empty
import sys
import traceback

from com.nxp.wireless_connectivity.hsdk.CFsciLibrary import FsciFrame, Endianess
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate
from com.nxp.wireless_connectivity.hsdk.device.device_manager import DeviceManager
from com.nxp.wireless_connectivity.hsdk.device.physical_device import PhysicalDevice
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader
from com.nxp.wireless_connectivity.hsdk.singleton import singleton
from com.nxp.wireless_connectivity.hsdk.utils import Observable, DEBUG, USE_LOGGER
from com.nxp.wireless_connectivity.hsdk import config

from com.nxp.wireless_connectivity.commands.fsci_frame_description import FsciAckPolicy, Protocol
if config.FSCI_TX_ACK:
    from com.nxp.wireless_connectivity.commands.thread.events import FSCIACKObserver
    from com.nxp.wireless_connectivity.commands.thread.frames import FSCIACK

# callback function header
CALLBACK = CFUNCTYPE(None, c_void_p, c_void_p)
# use python's logging module
if USE_LOGGER:
    DEBUG = False
    import logging
    logger = logging.getLogger('root.framer')

@singleton
class FsciDevice(object):

    def __init__(self, deviceName, ack_policy, baudrate):
        '''
        Constructor.
        @param deviceName: OS string
        @param ack_policy: the policy for FSCI ACK synchronization
        @param baudrate: see Baudrate class for possible values
        '''

        # sanity checks
        if deviceName is None:
            for line in traceback.format_stack():
                print (line.strip())
            raise RuntimeError('FsciDevice __init__: deviceName cannot be None')

        if not isinstance(deviceName, str) and not isinstance(deviceName, basestring):
            for line in traceback.format_stack():
                print (line.strip())
            raise RuntimeError('FsciDevice __init__: deviceName must be a string, got ' + str(type(deviceName)))

        if deviceName.startswith(('eth', '/dev/ttymxc', '/dev/spidev')):
            self.device = PhysicalDevice(type('mock', (object,), {'deviceName': deviceName, 'vid': 'FFFF', 'pid': 'FFFF'}))
        else:
            self.device = DeviceManager().getDevice(deviceName)
        try:
            self.device.open(ack_policy, baudrate)
        except AttributeError as ae:
            raise RuntimeError('FsciDevice __init__: %s is not currently available' % deviceName)


@singleton
class FsciFramer(Observable):

    '''
    Singleton class per one device. It handles the transmission and reception of frames.
    Upon reception, it notifies the subscribers for the encountered event.
    '''

    def getCallbackFunc(self):
        '''
        Creates a ctypes compatible callback function to notify the observers that
        subscribed to an event, based on the operation group and code.
        '''
        def func(deviceName, fsciFrameReference):
            '''
            Inner function implemented as a closure because ctypes does not allow instance
            or class method as callback.

            @param deviceName: the caller device
            @param fsciFrameReference: pointer to a FSCI frame that is to be handled in the Observer
            '''
            self.notifyObservers(
                self.deviceName,
                self.getOpGroup(fsciFrameReference),
                self.getOpCode(fsciFrameReference),
                fsciFrameReference,
                self.protocol
            )

        return CALLBACK(func)

    def __init__(self, deviceName, ack_policy=FsciAckPolicy.GLOBAL, protocol=Protocol.Thread, baudrate=Baudrate.BR115200):
        self.ll = LibraryLoader()
        self.dm = DeviceManager()
        # open the NXP Kinetis-W device
        self.deviceName = deviceName
        self.device = FsciDevice(deviceName=deviceName, ack_policy=ack_policy, baudrate=baudrate).device

        # Queue to store synchronous events, i.e. confirmations
        self.event_queue = Queue()
        # Queue to store asynchronous events, i.e. indications
        self.async_queue = Queue()

        # Queue to store packets from sniffer
        if protocol == Protocol.Sniffer:
            self.sniffer_queue = Queue()

        self.protocol = protocol
        self.endianess = Endianess.Little
        self.lengthFieldSize = 2

        # init framer
        self.ll.CFramerLibrary.InitializeFramer.argtypes = [c_void_p, c_int, c_uint8, c_uint8, c_int]
        self.ll.CFramerLibrary.InitializeFramer.restype = c_void_p
        self.framerPointer = self.ll.CFramerLibrary.InitializeFramer(
            self.device.devicePointer,
            0,  # FramerProtocol - FSCI
            self.lengthFieldSize,
            1,  # 1 byte for CRC
            self.endianess)
        # attach to framer the RX callback
        self.callback = self.getCallbackFunc()  # to prevent garbage collecting
        self.ll.CFramerLibrary.AttachToFramer.argtypes = [c_void_p, c_void_p, CALLBACK]
        self.ll.CFramerLibrary.AttachToFramer(self.framerPointer, id(self), self.callback)

        # add the ACK observer when having #define gFsciTxAck_c TRUE
        if config.FSCI_TX_ACK:
            self.addObserver(FSCIACKObserver('FSCI_Ack'))

        # set commonly used C functions arg/res types here
        self.ll.CFsciLibrary.CreateFSCIFrame.argtypes = [c_void_p, c_uint8, c_uint8, c_void_p, c_uint32, c_uint8]
        self.ll.CFsciLibrary.CreateFSCIFrame.restype = POINTER(FsciFrame)

        self.ll.CFramerLibrary.SendFrame.argtypes = [c_void_p, c_void_p]
        self.ll.CFramerLibrary.SendFrame.restype = c_int

        self.ll.CFramerLibrary.SetCrcFieldSize.argtypes = [c_void_p, c_uint8]

    def send(self, fsciCommand, virtualInterface=0):
        '''
        Defers the sending of the frame to the underlying FSCI framer in the C library.

        @param fsciCommand: the packet to be transmitted
        '''
        if fsciCommand.payload is None:
            frameLength = 0
            data = None
        else:
            frameLength = len(fsciCommand.payload)
            data = (c_uint8 * frameLength)(*fsciCommand.payload)

        if virtualInterface == 1:
            self.ll.CFramerLibrary.SetCrcFieldSize(self.framerPointer, 2)

        framePointer = self.ll.CFsciLibrary.CreateFSCIFrame(
            self.framerPointer,
            fsciCommand.opGroup,
            fsciCommand.opCode,
            data,
            frameLength,
            virtualInterface,
        )

        # send FSCI frame
        if DEBUG:
            print ('[Send][Command]', str(fsciCommand), '@', datetime.now().strftime("%H:%M:%S.%f"))
        elif USE_LOGGER:
            logger.info('[Send][Command]' + str(fsciCommand) + '@' + datetime.now().strftime("%H:%M:%S.%f"))

        rc = self.ll.CFramerLibrary.SendFrame(self.framerPointer, framePointer)

        # block for 3 seconds waiting for ACK, exit if not present
        if config.FSCI_TX_ACK:
            try:
                ack = self.event_queue.get(block=True, timeout=3)
                assert isinstance(ack, FSCIACK), 'Did not receive ACK for command: ' + str(fsciCommand)
            except Empty:
                print ('Did not receive ACK for command:', str(fsciCommand))
                sys.exit(1)

        self.destroyFrame(framePointer)

        return rc

    def destroyFrame(self, fsciFrameReference):
        '''
        Frees the memory allocated for a frame.

        @param fsciFrameReference: pointer to a FSCI frame
        '''
        self.ll.CFsciLibrary.DestroyFSCIFrame.argtypes = [c_void_p]
        self.ll.CFsciLibrary.DestroyFSCIFrame(fsciFrameReference)

    def getOpGroup(self, fsciFrameReference):
        '''
        Retrieves the operation group byte from a frame.

        @param fsciFrameReference: pointer to a FSCI frame
        @return: operation group byte
        '''
        return cast(fsciFrameReference + 1, POINTER(c_uint8)).contents.value

    def getOpCode(self, fsciFrameReference):
        '''
        Retrieves the operation code byte from a frame.

        @param fsciFrameReference: pointer to a FSCI frame
        @return: operation code byte
        '''
        return cast(fsciFrameReference + 2, POINTER(c_uint8)).contents.value

    def detach(self):
        self.ll.CFramerLibrary.DetachFromFramer.argtypes = [c_void_p, c_void_p]
        self.ll.CFramerLibrary.DetachFromFramer(self.framerPointer, id(self))

    def destroy(self):
        self.detach()
        self.ll.CFramerLibrary.DestroyFramer.argtypes = [c_void_p]
        self.ll.CFramerLibrary.DestroyFramer(self.framerPointer)
        self.framerPointer = None
