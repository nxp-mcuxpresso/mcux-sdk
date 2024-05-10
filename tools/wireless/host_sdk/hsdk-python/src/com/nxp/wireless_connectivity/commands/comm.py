'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from binascii import hexlify
from threading import Lock
import time

from com.nxp.wireless_connectivity.commands.fsci_frame_description import FsciAckPolicy, Protocol
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate
from com.nxp.wireless_connectivity.hsdk.framing.fsci_command import FsciCommand
from com.nxp.wireless_connectivity.hsdk.framing.fsci_framer import FsciFramer
from com.nxp.wireless_connectivity.hsdk.singleton import singleton
from com.nxp.wireless_connectivity.hsdk.utils import DEBUG, USE_LOGGER, print_command


if USE_LOGGER:
    DEBUG = False
    import logging
    logger = logging.getLogger('root.comm')


@singleton
class Comm(object):

    '''
    The communication module. It handles the construction of the frames and sends the packet
    below to the Framer.
    '''

    def __init__(self, deviceName, ack_policy=FsciAckPolicy.GLOBAL, protocol=Protocol.Thread, baudrate=Baudrate.BR115200):
        '''
        Comm constructor.

        @param deviceName: The OS name of the NXP Kinetis-W device. e.g. /dev/ttyACMx on Linux.
        @param ack_policy: The policy for FSCI ACK synchronization.
        @param protocol: The protocol to be used. Defaults to Thread.
        @param baudrate: The baudrate for opening the UART device. Defaults to 115200.
        '''
        self.deviceName = deviceName
        self.protocol = protocol
        self.lock = Lock()
        self.fsciFramer = FsciFramer(deviceName, ack_policy=ack_policy, protocol=protocol, baudrate=baudrate)

    def send(self, commandSpec, commandPayload, virtualInterface=0, printCmd=True):
        '''
        Wrapper function over the Framer's send method. Builds an packet based on the command specification and
        the frame (which is an object with fields at this point) and calls the Framer send method to send the packet.

        @param commandSpec: The specification of the command.
        @param commandPayload: The bytes composing the packet.
        '''
        if printCmd:
            print_command(self.deviceName, commandPayload)

        # sanity check
        if commandSpec is None or commandPayload is None:
            if DEBUG:
                print ("No request to send!")
            elif USE_LOGGER:
                logger.debug("No request to send!")
            return

        if DEBUG:
            print (80 * '=')
        elif USE_LOGGER:
            logger.info(80 * '=')

        if 'pickle' in [method for method in dir(commandPayload) if callable(getattr(commandPayload, method))]:
            self.fsciFramer.send(
                FsciCommand(commandSpec.opGroup, commandSpec.opCode, commandPayload.pickle()),
                virtualInterface=virtualInterface
            )
            if DEBUG:
                try:
                    print (hexlify(commandPayload.pickle()))
                except Exception:
                    print ('This request has no payload.')
            elif USE_LOGGER:
                try:
                    logger.debug('[Send][' + self.deviceName + ']' + hexlify(commandPayload.pickle()))
                except Exception:
                    logger.debug('[Send][' + self.deviceName + ']' + 'This request has no payload.')
        else:
            packet = commandSpec.getNewFsciPacket()
            # Instead of overloading send function, setPacket three times so that all
            # dependencies can be processed. __dict__ does not provide chronological
            # order, so situations when data is set before size could occur.
            self.setPacket(commandPayload.__dict__, packet)
            self.setPacket(commandPayload.__dict__, packet)
            self.setPacket(commandPayload.__dict__, packet)

            self.fsciFramer.send(
                FsciCommand(commandSpec.opGroup, commandSpec.opCode, packet.getBytes()),
                virtualInterface=virtualInterface
            )

            if DEBUG:
                print ('[Send][' + self.deviceName + ']',)
                try:
                    print (hexlify(packet.getBytes()))
                except Exception:
                    print ('This request has no payload.')
            elif USE_LOGGER:
                try:
                    logger.debug('[Send][' + self.deviceName + ']' + hexlify(packet.getBytes()))
                except Exception:
                    logger.debug('[Send][' + self.deviceName + ']' + 'This request has no payload.')

        # reset needs more wait time
        if (commandSpec.opGroup, commandSpec.opCode) == (0xA3, 0x08):
            time.sleep(2)
        # push firmware chunks as fast as possible
        elif (commandSpec.opGroup, commandSpec.opCode) == (0xA3, 0x2A):
            pass
        # delay between successive commands, may be tweaked depending on the host system's
        # speed; by default 50ms
        else:
            time.sleep(0.05)

    def setPacket(self, commandPayloadDict, packet, prefix=''):
        '''
        Recursively builds an packet from an object. The object may contain other objects inside
        it, so traverse it until we reach primitive types.

        @param commandPayloadDict: The object. Each Python object has a __dict__ attribute.
        @param packet: The packet which will be filled with information from the object,
                        commandPayloadDict
        @param prefix: In case duplicate names exist within the object at all levels, add a prefix
                         string to differentiate them.
        '''
        for k, v in commandPayloadDict.items():
            if hasattr(v, '__dict__'):
                self.setPacket(v.__dict__, packet, prefix=k)
            else:
                packet.setParamValueAsNumber(prefix + k, v)
