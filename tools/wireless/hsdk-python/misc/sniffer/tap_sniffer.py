#!/usr/bin/env python
'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

import sys
sys.path.append('../../src/')

from com.nxp.wireless_connectivity.commands.thread.sync_requests import FSCIGetSwVersions
from com.nxp.wireless_connectivity.hsdk.sniffer import Sniffer
from threading import Thread
from time import sleep

def usage():
    import argparse

    parser = argparse.ArgumentParser(
        description='Starts one or two 802.15.4 sniffer instances on TAP interfaces sniffer802154_x.'
    )
    parser.add_argument(
        'dev1',
        metavar='serial port sniffer 1',
        type=str,
        nargs='?',
        help='Kinetis-W system device node',
        default='/dev/ttyACM0'
    )
    parser.add_argument(
        'channel1',
        metavar='802.15.4 RF channel',
        type=int,
        choices=range(11, 27),
        nargs='?',
        help='RF channel for the Thread network',
        default=25
    )
    parser.add_argument(
        'dev2',
        metavar='serial port sniffer 2',
        type=str,
        nargs='?',
        help='Kinetis-W system device node',
        default=None
    )
    parser.add_argument(
        'channel2',
        metavar='802.15.4 RF channel',
        type=int,
        choices=range(11, 27),
        nargs='?',
        help='RF channel for the Thread network',
        default=25
    )

    args = parser.parse_args()
    print args

    return args

if __name__ == '__main__':

    args = usage()

    s1 = Sniffer(args.dev1, args.channel1, use_tap=True)
    FSCIGetSwVersions(args.dev1)
    t1 = Thread(target=s1.start)
    t1.daemon = True
    t1.start()

    if args.dev2 is not None:
        s2 = Sniffer(args.dev2, args.channel2, use_tap=True)
        FSCIGetSwVersions(args.dev2)
        t2 = Thread(target=s2.start)
        t2.daemon = True
        t2.start()

    # serve forever on daemon threads
    try:
        while 1:
            sleep(1)
    except KeyboardInterrupt:
        sys.exit(0)
