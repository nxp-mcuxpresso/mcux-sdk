#!/usr/bin/env python
'''
* Copyright 2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.comm import Comm
from com.nxp.wireless_connectivity.commands.thread.sync_requests import *
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate
from com.nxp.wireless_connectivity.hsdk.device.device_manager import DeviceManager
from com.nxp.wireless_connectivity.hsdk.framing.fsci_framer import FsciFramer

from binascii import hexlify
from Queue import Empty
import struct
import threading

from VTun import VTunInterface

ULAs = []


class ThreadBorderRouter():

    JOINER_EUI = 0xFFFFFFFFFFFFFFFF  # allow all joiners
    JOINER_PSKD = 'THREAD'

    def __init__(self, tty_port):
        self.tty = tty_port
        self.subscribe_to_async_events()
        Comm(self.tty).fsciFramer.addObserver(THR_MgmtDiagnosticGetRspIndicationObserver(
            'THR_MgmtDiagnosticGetRspIndication'), self.cb_diag_get_rsp)

    def factory_reset(self):
        confirm = None
        confirm = THR_FactoryReset(self.tty)
        if confirm.Status != 'Success':
            print '[FAIL] Factory Reset'
            return False
        return True

    def is_connected(self):
        confirm = THR_GetAttr(
            self.tty,
            AttributeId=THR_GetAttrRequestAttributeId.IsDevConnected,
        )
        if confirm.Status != 'Success':
            print '[FAIL] THR_GetAttr IsDevConnected'
            return False

        return True if bool(confirm.AttributeValue) else False

    def get_channel(self):
        confirm = THR_GetAttr(
            self.tty,
            AttributeId=THR_GetAttrRequestAttributeId.Channel,
        )
        if confirm.Status != 'Success':
            print '[FAIL] THR_GetAttr Channel'
            return 0

        return confirm.AttributeValue

    def set_channel(self, channel):
        confirm = THR_SetAttr(
            self.tty,
            AttributeId=THR_SetAttrRequestAttributeId.Channel,
            AttrSize=1,
            AttributeValue=int(channel)
        )
        if confirm.Status != 'Success':
            print '[FAIL] THR_SetAttr Channel'
            return False
        return True

    def set_eui_addr(self, eui):
        confirm = THR_SetAttr(
            self.tty,
            AttributeId=THR_SetAttrRequestAttributeId.IeeeExtendedAddr,
            AttrSize=8,
            AttributeValue=eui
        )
        if confirm.Status != 'Success':
            print '[FAIL] THR_SetAttr IeeeExtendedAddr'
            return False
        return True

    def subscribe_to_async_events(self):
        subscribe_to_async_thread_events_from(self.tty)

    def configure(self, eui_addr, channel, reset):
        if reset:
            assert self.factory_reset(), 'Factory Reset failed'
        assert self.set_eui_addr(eui_addr), 'Set Extended Address failed'
        assert self.set_channel(channel), 'Set Channel failed'

    def start_commissioner(self):
        confirm = THR_CreateNwk(self.tty, InstanceID=0)
        if confirm.Status != 'OK':
            return False

        # expect async events: watch console
        sleep(7)

        confirm = MESHCOP_StartCommissioner(self.tty, InstanceId=0)
        if confirm.Status != 'Success':
            return False

        # removing all the obsolete joiners, if any
        confirm = MESHCOP_RemoveAllExpectedJoiners(self.tty, InstanceId=0)
        if confirm.Status != 'Success':
            return False

        return True

    def allow_all_joiners(self):
        confirm = MESHCOP_AddExpectedJoiner(
            self.tty,
            Selected=True,
            EuiType=MESHCOP_AddExpectedJoinerRequestEuiType.LongEUI,
            EUI=ThreadBorderRouter.JOINER_EUI,
            PSKdSize=len(ThreadBorderRouter.JOINER_PSKD),
            PSKd=ThreadBorderRouter.JOINER_PSKD
        )
        if confirm.Status != 'Success':
            return False

        confirm = MESHCOP_SyncSteeringData(
            self.tty,
            InstanceId=0,
            EuiMask=MESHCOP_SyncSteeringDataRequestEuiMask.AllFFs
        )
        if confirm.Status != 'Success':
            return False

        return True

    def validate_joiner_accepted(self):
        while True:
            # we keep consuming async events until the Joiner confirmation
            # occurs
            try:
                event = FsciFramer(self.tty, ack_policy=FsciAckPolicy.GLOBAL, protocol=Protocol.Thread,
                                   baudrate=Baudrate.BR115200).async_queue.get(block=True, timeout=1)
            except Empty:
                continue
            except KeyboardInterrupt:
                print 'Exiting at user request..'
                sys.exit()
            if isinstance(event, THR_EventNwkCommissioningIndication) and event.EventStatus == 'CommissionerJoinerAccepted':
                break
        # If the number of active Routers on the Thread Network partition, as reported in the
        # Route64 TLV of neighboring nodes, is less than ROUTER_UPGRADE_THRESHOLD, a REED MUST wait
        # a random period between 0 and ROUTER_SELECTION_JITTER (120 seconds) [...] and then [...]
        # MUST attempt to become an active Router by requesting a Router ID
        # from the Leader.
        print '\nWaiting 120 seconds for the Joiner to promote to Router for it to be available in our neighbor table..\n'
        sleep(120)

    def add_prefix(self):
        confirm = THR_BrPrefixAddEntry(
            self.tty,
            InstanceId=0,
            prefixLength=64,
            PrefixValue=[0xFD, 0x01, 0x00, 0x00,
                         0x00, 0x00, 0x3E, 0xAD] + 8 * [0x00],
            PrefixFlagsReserved=0x00,
            PrefixFlags=0b00110011,  # P + S + R + O
            prefixLifetime=0xFFFFFFFF,
            prefixAdvertised=True,
            ExternalRouteFlags=0x00,
            ExternalRouteLifetime=0xFFFFFFFF,
            ExternalRouteAdvertised=False
        )
        if confirm.Status != 'Success':
            return False

        confirm = THR_BrPrefixSync(self.tty, InstanceId=0)
        if confirm.Status != 'Success':
            return False

        return True

    def cb_diag_get_rsp(self, devName, rsp):
        global ULAs

        try:
            Ip6AddrList = rsp.TLVs[0].raw_value
            ULAs.append(':'.join([('%02x' % Ip6AddrList[
                        i] + '%02x' % Ip6AddrList[i + 1]) for i in range(48, 64, 2)]))
        except AttributeError:
            print '\nNeighbor', ':'.join([('%02x' % dest_ll[i] + '%02x' % dest_ll[i + 1]) for i in range(0, 16, 2)]), 'expired!\n'

        print
        for i in range(len(ULAs)):
            print 'ULA NEIGHBOR' + str(i), '->', ULAs[i]

    def expect_joiners(self, validate=False):
        global ULAs

        ULAs = []
        if validate:
            self.validate_joiner_accepted()

        table = THR_GetNeighborTable(self.tty, NoOfElements=10)
        for entry in table.NeighborEntries:
            raw_ext_addr = struct.unpack(
                '8B', struct.pack('>Q', entry.ExtendedAddress))
            dest_ll = [0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00] + [raw_ext_addr[0] ^ 0x02] + list(raw_ext_addr[1:])

            diag_response = THR_MgmtDiagnosticGet(
                self.tty,
                DestIpAddr=dest_ll,
                NumberOfTlvIds=1,
                TlvIds=[THR_MgmtDiagnosticGetRequestTlvId.Ip6AddrList],
            )

            if diag_response.Status != 'Success':
                print 'Neighbor', dest_ll, 'failed to respond to /d/dg..'

        self.expect_joiners(validate=True)


def usage():
    import argparse

    parser = argparse.ArgumentParser(
        description='Starts a Thread Border Router with Serial TUN capabilities.')
    parser.add_argument('dev', metavar='serial port', type=str, nargs='?',
                        help='Kinetis-W system device node', default='/dev/ttymxc1')
    parser.add_argument('channel', metavar='802.15.4 RF channel', type=int, choices=range(
        11, 27), nargs='?', help='RF channel for the Thread network', default=25)
    parser.add_argument(
        '-r', '--reset', help='Perform a factory reset of the device at start', action='store_true')
    parser.add_argument('--tap', help='Use black-box in TAP mode', action='store_true')

    args = parser.parse_args()
    print args

    return args


if __name__ == '__main__':

    args = usage()
    leader = ThreadBorderRouter(args.dev)

    # don't allow channel change if not --reset and device is already connected
    if not args.reset:
        # retrieve current device state
        current_channel = leader.get_channel()
        dev_connected = leader.is_connected()
        # exit on bad condition
        if dev_connected and (current_channel != args.channel):
            print '%s: error: Changing the channel while the Thread network is created is forbidden.' % sys.argv[0]
            print '%s: error: The Thread network is currently running on channel %d.' % (sys.argv[0], current_channel)
            print '%s: error: Please use -r/--reset to switch to the desired channel.' % sys.argv[0]
            sys.exit(1)

    # configure device if user requests reset or if the device is not connected
    if args.reset or not dev_connected:
        leader.configure(eui_addr=0x146E0A0000000001,
                         channel=args.channel, reset=args.reset)
        assert leader.start_commissioner(), 'Start Commissioner failed'
        assert leader.allow_all_joiners(), 'Allow Joiners into Network failed'
        # ULA prefix is added by the serial TUN embedded code. Source code is left here as demo.
        # assert leader.add_prefix(), 'Border Router Prefix Add failed'

    vtun_thread = VTunInterface(args.dev, tun_mode=(not args.tap), debug=False)
    vtun_thread.daemon = True
    vtun_thread.start()

    print 'Everything is set up. Expecting Joiners now.'
    # if reset is False, we do not validate the already connected Joiners
    leader.expect_joiners(args.reset)
