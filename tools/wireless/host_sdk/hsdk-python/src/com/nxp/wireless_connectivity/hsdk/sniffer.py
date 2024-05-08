'''
* Copyright 2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

import commands
import sys
if sys.version[0] == '2':
    import Queue
else:
    import queue as Queue
import socket
import struct
import sys
from threading import Thread, Event
import time

from com.nxp.wireless_connectivity.commands.comm import Comm
from com.nxp.wireless_connectivity.commands.fsci_frame_description import Protocol,\
    FsciAckPolicy
from com.nxp.wireless_connectivity.commands.thread.enums import Sniffer_MacSetPIBAttributeRequestPIBAttribute
from com.nxp.wireless_connectivity.commands.thread.events import MAC_PromiscuousRxIndicationObserver
from com.nxp.wireless_connectivity.commands.thread.sync_requests import Sniffer_MacSetPIBAttribute
from com.nxp.wireless_connectivity.hsdk.config import THREAD_HARNESS
from com.nxp.wireless_connectivity.hsdk.utils import print_pkt
from com.nxp.wireless_connectivity.hsdk.device.device_manager import DeviceManager
from com.nxp.wireless_connectivity.hsdk.framing.fsci_framer import FsciFramer
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate


pack = lambda pkt: struct.pack('%sB' % len(pkt), *pkt)

# Missing Ethernet header definition for sniffed packets.
_eth_header = [0xff] * 6 + [0x22] * 6 + [0x80, 0x9a]
ETH_header = struct.pack('14B', *_eth_header)
STANDARD_DECRYPTION_KEY = '00112233445566778899aabbccddeeff'
INFINITE = 1e6


def compute_802154_fcs(macframe):
    fcs = 0
    for i in range(len(macframe)):
        fcs = (fcs ^ macframe[i]) & 0xffff
        for _ in range(8):
            if fcs & 0x0001 == 0x01:
                fcs = ((fcs >> 1) ^ 0x8408) & 0xffff
            else:
                fcs = (fcs >> 1) & 0xffff
    return struct.pack('H', fcs)


class Sniffer(object):

    OBJ_COUNTER = 0

    def __init__(self, port, channel, decryption_key=STANDARD_DECRYPTION_KEY, use_tshark=False, use_rpcap=False, use_tap=False):
        self.idx = Sniffer.OBJ_COUNTER
        Sniffer.OBJ_COUNTER += 1

        self.dm = DeviceManager()

        if THREAD_HARNESS:
            self.dm.initDeviceList(detect_sniffers=False)
        else:
            self.dm.initDeviceList(detect_sniffers=True)
            # Do we actually have a sniffer on COM port?
            true_sniffer = False
            for device in self.dm.getDevices():
                if device.is_sniffer and device.name == port:
                    true_sniffer = True

            if not true_sniffer:
                raise IOError(port + ' is not an 802.15.4 sniffer!')

        self.port = port
        self.channel = channel
        self.decryption_key = decryption_key
        self.use_tshark = use_tshark
        self.use_rpcap = use_rpcap
        self.use_tap = use_tap
        self.comm = Comm(self.port,
            ack_policy=FsciAckPolicy.NONE,
            protocol=Protocol.Sniffer,
            baudrate=Baudrate.BR115200
        )
        self.observer = MAC_PromiscuousRxIndicationObserver('Data Received from Sniffer')
        self.sniffer_queue = self.comm.fsciFramer.sniffer_queue

    def change_channel(self, new_channel):
        self.channel = new_channel

    def start(self, time_to_run=INFINITE, apply_on_each_pkt=print_pkt):
        '''
        Starts the actual sniffing.

        :param time_to_run: Only used for pyshark, since stop() cannot be used for breaking the while True loop in
        __sniff_continuously. Defaults to 60.
        '''

        MAC_PromiscuousRxIndicationObserver.SNIFFER_QUEUE_ENABLED = False
        self.__configure(self.port, apply_on_each_pkt)

        if self.use_tshark:
            self.__configure_for_tshark()
            self.__sniff_continuously(time_to_run, apply_on_each_pkt)
        elif self.use_rpcap:
            MAC_PromiscuousRxIndicationObserver.SNIFFER_QUEUE_ENABLED = True
            self.rpcap_counter = 0
            self.stop_event = Event()
            self.wireshark_connected = Event()
            self.rpcap_thread = Thread(target=self.__start_rpcap_server)
            self.rpcap_thread.daemon = True
            self.rpcap_thread.start()
        elif self.use_tap:
            if not sys.platform.startswith('linux'):
                raise RuntimeError('TAP devices are only supported on Linux!')
            self.__configure_for_tap()
            self.__sniff_continuously(time_to_run, apply_on_each_pkt)

    def stop(self):
        self.comm.fsciFramer.removeObserver(self.observer)

        Sniffer_MacSetPIBAttribute(
            self.port,
            Sniffer_MacSetPIBAttributeRequestPIBAttribute.macMAC_PromiscuousRxIndicationMode,
            Value=False
        )

        Sniffer_MacSetPIBAttribute(
            self.port,
            Sniffer_MacSetPIBAttributeRequestPIBAttribute.macRxOnWhenIdle,
            Value=False
        )

        if self.use_rpcap:
            self.stop_event.set()
            self.rpcap_thread.join()

    def __configure_for_tshark(self):
        try:
            import pyshark
        except ImportError:
            raise ImportError('Please install pyshark for using the sniffer in tshark mode.')
        self.capture = pyshark.InMemCapture(only_summaries=True, decryption_key=self.decryption_key)
        MAC_PromiscuousRxIndicationObserver.SNIFFER_QUEUE_ENABLED = True

    def __configure_for_tap(self):
        try:
            from pytun import TunTapDevice, IFF_TAP, IFF_NO_PI
        except ImportError:
            raise ImportError('Please install the pytun module: `pip install python-pytun`.')

        commands.getoutput('ip link delete dev sniffer802154_' + str(self.idx))
        print (commands.getoutput('ip tuntap add mode tap sniffer802154_' + str(self.idx)))
        self.tap = TunTapDevice(name='sniffer802154_' + str(self.idx), flags=IFF_TAP | IFF_NO_PI)
        self.tap.up()
        MAC_PromiscuousRxIndicationObserver.SNIFFER_QUEUE_ENABLED = True

    def __configure(self, dev_name, pkt_callback):
        # Channel
        Sniffer_MacSetPIBAttribute(
            self.port,
            Sniffer_MacSetPIBAttributeRequestPIBAttribute.macLogicalChannel,
            Value=self.channel
        )

        # Promiscuous mode
        Sniffer_MacSetPIBAttribute(
            self.port,
            Sniffer_MacSetPIBAttributeRequestPIBAttribute.macMAC_PromiscuousRxIndicationMode,
            Value=True
        )

        # RX on when idle
        Sniffer_MacSetPIBAttribute(
            self.port,
            Sniffer_MacSetPIBAttributeRequestPIBAttribute.macRxOnWhenIdle,
            Value=True
        )

        self.comm.fsciFramer.addObserver(self.observer, pkt_callback)

    def __sniff_continuously(self, time_to_run=INFINITE, apply_on_each_pkt=print_pkt):
        time_passed = 0

        while time_passed < time_to_run:
            try:
                raw_from_sniffer = []
                packets_to_feed = []
                timestamps = []

                # Get frames from sniffer's queue
                try:

                    if self.use_tshark:
                        # Get all packets that occurred in the past second.
                        time.sleep(1)
                        time_passed += 1
                    elif self.use_tap:
                        # Avoid consuming 100% of a core
                        time.sleep(.1)
                        time_passed += .1

                    while True:
                        raw_from_sniffer.append(self.sniffer_queue.get_nowait())
                        self.sniffer_queue.task_done()

                # Retrieved all elements, now feed them to be parsed.
                except Queue.Empty:

                    if raw_from_sniffer == []:
                        continue

                    for timestamp, payload_list in raw_from_sniffer:
                        # Format it
                        payload = pack(payload_list)
                        fcs = compute_802154_fcs(payload_list)
                        packets_to_feed.append(ETH_header + payload + fcs)
                        timestamps.append(timestamp)

                    if self.use_tshark:
                        # Inject packets
                        self.capture.feed_packets(packets_to_feed)

                        # Get them parsed
                        for i in range(len(packets_to_feed)):
                            curr_pkt = self.capture.next()
                            setattr(curr_pkt, 'time', timestamps[i])
                            apply_on_each_pkt(self.port, curr_pkt)

                    elif self.use_tap:
                        # Inject packets
                        for curr_pkt in packets_to_feed:
                            self.tap.write(curr_pkt)
                            apply_on_each_pkt(self.port, curr_pkt[len(ETH_header):])

                    # Clear the mess
                    del raw_from_sniffer[:]
                    del packets_to_feed[:]
                    del timestamps[:]

            except KeyboardInterrupt:
                Sniffer_MacSetPIBAttribute(
                    self.port,
                    Sniffer_MacSetPIBAttributeRequestPIBAttribute.macMAC_PromiscuousRxIndicationMode,
                    Value=False
                )
                print ('Your wish is my command.')
                break

        self.stop()

    def __start_rpcap_server(self):
        TCP_IP = '127.0.0.1'
        CONTROL_PORT = 3333
        DATA_PORT = CONTROL_PORT + 1
        BUFFER_SIZE = 1024

        control_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        test_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # check if CONTROL_PORT available to bind on
        while True:
            port_available = test_sock.connect_ex((TCP_IP, CONTROL_PORT))
            if port_available:
                test_sock.close()
                break
            CONTROL_PORT += 2
            DATA_PORT += 2

        try:
            control_sock.bind((TCP_IP, CONTROL_PORT))
        except Exception:
            print ('[__start_rpcap_server] An error occurred on port', CONTROL_PORT)
            control_sock.close()
            return

        control_sock.listen(1)
        print ('Listening for Wireshark connections on port %d..' % CONTROL_PORT)

        conn, _ = control_sock.accept()
        while True:
            data = conn.recv(BUFFER_SIZE)
            if not data:
                conn, _ = control_sock.accept()
                continue

            if data[1] == chr(0x08):
                auth_reply_list = [0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
                auth_reply = struct.pack('%sB' % len(auth_reply_list), *auth_reply_list)
                conn.send(auth_reply)

            elif data[1] == chr(0x02):
                # need to have a unique interface name: USB-KW24D512-X
                # https://www.winpcap.org/docs/docs_40_2/html/
                # USB-KW24D512-
                find_all_ifaces_reply_hexstream = '0082000100000432000e001a00000000000200005553422d4b573234443531322d'
                # 1, 2, 3..
                find_all_ifaces_reply_hexstream += '%02x' % ord(str(((CONTROL_PORT % 3333) / 2)))
                find_all_ifaces_reply_hexstream += '467265657363616c65203830322e31352e3420536e6966666572000200007f000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000233337f00000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000023333ffffff0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000023333ffffffff0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000'
                find_all_ifaces_reply_list = [int(find_all_ifaces_reply_hexstream[
                                                  i: i + 2], 16) for i in range(0, len(find_all_ifaces_reply_hexstream), 2)]
                find_all_ifaces_reply = struct.pack(
                    '%sB' % len(find_all_ifaces_reply_list), *find_all_ifaces_reply_list)
                conn.send(find_all_ifaces_reply)

            elif data[1] == chr(0x03):
                open_reply_list = [0x00, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00]
                open_reply = struct.pack('%sB' % len(open_reply_list), *open_reply_list)
                conn.send(open_reply)

            elif data[1] == chr(0x06):
                conn, _ = control_sock.accept()
                continue

            elif data[1] == chr(0x04):
                start_reply_list = [0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x08, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
                start_reply_list[12] = (DATA_PORT & 0xff00) >> 8
                start_reply_list[13] = DATA_PORT & 0x00ff
                start_reply = struct.pack('%sB' % len(start_reply_list), *start_reply_list)
                conn.send(start_reply)
                break

        data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        data_sock.bind((TCP_IP, DATA_PORT))
        data_sock.listen(1)

        dataconn, addr = data_sock.accept()
        while 1:
            data = conn.recv(BUFFER_SIZE)
            if not data:
                break

            if data[1] == chr(0x05):
                update_filter_reply_list = [0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
                update_filter_reply = struct.pack(
                    '%sB' % len(update_filter_reply_list), *update_filter_reply_list)
                conn.send(update_filter_reply)
                break

        conn.close()
        control_sock.close()
        print ('Wireshark client on', addr, 'connected.')
        self.wireshark_connected.set()

        while not self.stop_event.is_set():
            try:
                (_, packet) = self.sniffer_queue.get(True, 1)
            except Queue.Empty:
                continue

            self.sniffer_queue.task_done()
            dataconn.send(self.__build_rpcap_packet(packet))

        dataconn.close()
        data_sock.close()

        print ('Wireshark client on', addr, 'disconnected.')
        self.wireshark_connected.clear()

    def __build_rpcap_packet(self, payload):
        self.rpcap_counter += 1

        eth_header_len = 14
        version = [0x00]
        message_type = [0x07]  # Packet
        message_value = [0x00, 0x00]

        payload_length_list = [
            ((len(payload) + eth_header_len + 22) & 0xff000000) >> 24,
            ((len(payload) + eth_header_len + 22) & 0x00ff0000) >> 16,
            ((len(payload) + eth_header_len + 22) & 0x0000ff00) >> 8,
            ((len(payload) + eth_header_len + 22) & 0x000000ff)
        ]

        arrival_time = int('%x' % time.time(), 16)
        arrival_time_list = [
            (arrival_time & 0xff000000) >> 24,
            (arrival_time & 0x00ff0000) >> 16,
            (arrival_time & 0x0000ff00) >> 8,
            (arrival_time & 0x000000ff),
            0, 0, 0, 0
        ]

        capture_length = [
            ((len(payload) + eth_header_len + 2) & 0xff000000) >> 24,
            ((len(payload) + eth_header_len + 2) & 0x00ff0000) >> 16,
            ((len(payload) + eth_header_len + 2) & 0x0000ff00) >> 8,
            ((len(payload) + eth_header_len + 2) & 0x000000ff)
        ]

        frame_length = capture_length
        frame_number = [
            (self.rpcap_counter & 0xff000000) >> 24,
            (self.rpcap_counter & 0x00ff0000) >> 16,
            (self.rpcap_counter & 0x0000ff00) >> 8,
            (self.rpcap_counter & 0x000000ff)
        ]

        rpcap_header = version + message_type + message_value + payload_length_list + \
            arrival_time_list + capture_length + frame_length + frame_number
        packet_list = rpcap_header + _eth_header + payload

        return struct.pack('%sB' % len(packet_list), *packet_list) + compute_802154_fcs(payload)
