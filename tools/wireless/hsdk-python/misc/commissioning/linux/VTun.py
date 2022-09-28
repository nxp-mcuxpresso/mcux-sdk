#!/usr/bin/env python
'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from binascii import hexlify
from com.nxp.wireless_connectivity.commands.comm import Comm
from com.nxp.wireless_connectivity.commands.thread.enums import SerialTun_LinkIndicationRequestState
from com.nxp.wireless_connectivity.commands.thread.events import SerialTun_IPPacketReceivedConfirmObserver
from com.nxp.wireless_connectivity.commands.thread.frames import SerialTun_IPPacketSendRequest
from com.nxp.wireless_connectivity.commands.thread.spec import Spec
from com.nxp.wireless_connectivity.commands.thread.sync_requests import SerialTun_LinkIndication
from com.nxp.wireless_connectivity.hsdk.device.device_manager import DeviceManager

import commands
import threading

from pytun import TunTapDevice, IFF_TUN, IFF_TAP, IFF_NO_PI


class VTunInterface(threading.Thread):
    '''
    Handles the sending/receiving of data over the TUN/TAP interface.
    '''

    def __init__(self, port, tun_mode=True, debug=False):
        threading.Thread.__init__(self)

        self.port = port
        self.debug = debug

        # enable forwarding on host
        print commands.getoutput('sysctl -w net.ipv6.conf.all.forwarding=1')

        # create a TUN/TAP device and get an object pointing to it
        if tun_mode:
            print commands.getoutput('ip -6 tuntap add mode tun threadtun0')
            print commands.getoutput('ip -6 addr add fd01::2 dev threadtun0')
            print commands.getoutput('ip -6 route add fd01::1 dev threadtun0')
            print commands.getoutput('ip -6 route add fd01:0000:0000:3ead::/64 dev threadtun0')
            print commands.getoutput('ip link set threadtun0 up')

            self.tun = TunTapDevice(name='threadtun0', flags=IFF_TUN | IFF_NO_PI)
        else:
            print commands.getoutput('ip -6 tuntap add mode tap threadtap0')
            print commands.getoutput('ip -6 addr add fd01::2 dev threadtap0')
            print commands.getoutput('ip -6 route add fd01::1 dev threadtap0')
            print commands.getoutput('ip -6 route add fd01:0000:0000:3ead::/64 via fe80::260:37ff:fe00:fa5c dev threadtap0')
            print commands.getoutput('ip link set threadtap0 up')

            self.tun = TunTapDevice(name='threadtap0', flags=IFF_TAP | IFF_NO_PI)
        self.tun.up()

        # open FSL device
        self.comm = Comm(self.port)

        observer = SerialTun_IPPacketReceivedConfirmObserver('RX')
        self.comm.fsciFramer.addObserver(observer, self.event_callback)

    def event_callback(self, devName, event):
        '''
        Gets executed by libframer.so whenever the board sends VTun packets back.
        @param event: VTUNIPPacketReceivedConfirm object, IPpayload of interest
        '''
        # concatenate bytes into a string
        response = ''.join([chr(x) for x in event.IPpayload])
        # send the response on the tun interface
        if self.debug:
            print 'RX: ' + hexlify(response) + '\n'
        self.tun.write(response)

    def run(self):

        SerialTun_LinkIndication(self.port, SerialTun_LinkIndicationRequestState.Up)

        while 1:
            try:
                # read data from the TUN interface
                buf = self.tun.read(self.tun.mtu)
                if self.debug:
                    print 'TX: ' + hexlify(buf)

                # send it to the Kinetis-W device, FSCI encapsulated
                buf_fsci = SerialTun_IPPacketSendRequest(
                    Size=bytearray([len(buf) & 0x00FF, (len(buf) & 0xFF00) >> 8]),
                    Data=bytearray(buf)
                )
                self.comm.send(Spec().SerialTun_IPPacketSendRequestFrame, buf_fsci, printCmd=False)

            except KeyboardInterrupt:
                self.tun.close()
                break

if __name__ == '__main__':
    vtun_thread = VTunInterface('/dev/ttyACM0')
    vtun_thread.start()
