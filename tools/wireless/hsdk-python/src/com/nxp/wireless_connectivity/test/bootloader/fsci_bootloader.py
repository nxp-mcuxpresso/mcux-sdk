#!/usr/bin/env python
'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.hsdk import utils, config

from com.nxp.wireless_connectivity.commands.comm import Comm
from com.nxp.wireless_connectivity.commands.firmware.sync_requests import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate
from com.nxp.wireless_connectivity.hsdk.framing.fsci_command import FsciCommand
from com.nxp.wireless_connectivity.hsdk.utils import crc16xmodem

import os
from threading import Event
from time import time, sleep

config.MAX_SPEED_HZ = 2000000  # bootloader supports higher speeds than a stack

SECTOR_SIZE = 2048
KW_NVM_SECTOR_START, KW_NVM_SECTOR_END = 0x0006F800 / SECTOR_SIZE, 0x0007F7FF / SECTOR_SIZE
CHUNK_LEN = 2048

new_request = Event()
new_request.set()
bytes_sent, seq_no = 0, 0
authenticated_image = False
encrypted_image = False


def usage():
    import argparse

    parser = argparse.ArgumentParser(
        description='Script to flash a binary file using the FSCI bootloader.')
    parser.add_argument(
        'dev', metavar='serial_port', type=str, help='Kinetis-W system device node.')
    parser.add_argument(
        'bin', metavar='binary_file', type=str, help='The binary file to be written.')
    parser.add_argument(
        '-s', '--chunk-size', help='Push chunks this large (in bytes). Defaults to 2048.',
        type=int, default=2048)
    parser.add_argument(
        '-d', '--disable-crc', help='Disable the CRC check on commit image.', action='store_true')
    parser.add_argument(
        '-e', '--erase-nvm', help='Erase the non-volatile memory. Useful if gEraseNVMLink_d=0 in Linker flags, '
        'otherwise the NVM is erased by default.', action='store_true')
    parser.add_argument(
        '-k', '--decryption-key', help='Key used to decrypt the encrypted image')
    parser.add_argument(
        '-a', '--authentication-key', help='Key used to authenticate the image')

    args = parser.parse_args()
    print args

    return args


def decode_hex_key(hex_key_string):
    key = hex_key_string.replace(" 0x", "")
    key = key.replace("0x", "")
    key = key.decode('hex')
    return key


def nvm_erase_bitmask(start_sector=KW_NVM_SECTOR_START, end_sector=KW_NVM_SECTOR_END):
    result = bytearray()
    index = 0

    NVM_ERASE_BITMASK = '0' * (start_sector - 1) + \
                        '1' * (end_sector - start_sector + 1) + \
                        '0' * (256 - end_sector)
    NVM_ERASE_BITMASK = int(NVM_ERASE_BITMASK, 2)

    while NVM_ERASE_BITMASK:
        result.append(NVM_ERASE_BITMASK & 0xFF)
        NVM_ERASE_BITMASK >>= 8
        index += 1

    return bytearray(32 - index) + result[::-1]


def read_image(path):
    global authenticated_image, encrypted_image

    if not os.path.isfile(path):
        sys.exit(path + ' does not exist or is inaccessible.')

    with open(path, 'rb') as fin:
        contents = fin.read()

    if args.bin.endswith(".sbin"):
        certificate_offset = contents[0x28: 0x28 + 4]
        if ((ord(certificate_offset[0]) + ord(certificate_offset[1]) + ord(certificate_offset[2]) + ord(certificate_offset[3])) != 0):
            authenticated_image = True
        else:
            encrypted_image = True

    if authenticated_image is False:
        # remove useless 0xFFs at the end
        to_remove = bytearray([0xFF for _ in range(SECTOR_SIZE)])
        while contents.endswith(to_remove):
            contents = contents[:-SECTOR_SIZE]
    size = len(contents)

    return size, contents


def cb_push_image_cnf(_, cnf):
    global bytes_sent, seq_no

    if cnf.Status == 'Success':
        bytes_sent = bytes_sent + CHUNK_LEN
        seq_no = (seq_no + 1) & 0xFF
        new_request.set()
    else:
        # repeat
        new_request.set()


def flash_image(args, size, contents):
    '''
    Flashes a binary image over FSCI.

    @param device: destination device
    @param size: size of the image in bytes
    @param contents: actual contents of the image as byte array
    '''
    global bytes_sent, seq_no, authenticated_image, encrypted_image

    FSCIEnterBootloader(args.dev)
    sleep(.5)

    if (authenticated_image is None) or (encrypted_image is None):
        confirm = FSCIFirmware_CancelProcess(args.dev)
        if confirm is None or confirm.Status != 'Success':
            sys.exit('Cannot communicate with the board, please try again. Exiting..')

        # add a callback on push image request.
    comm = Comm(args.dev, ack_policy=FsciAckPolicy.GLOBAL,
                protocol=Protocol.Firmware, baudrate=Baudrate.BR115200)
    comm.fsciFramer.addObserver(FSCIFirmware_PushImageChunkConfirmObserver(
        'FSCIFirmware_PushImageChunkConfirm'), cb_push_image_cnf)

    if (authenticated_image or encrypted_image) and args.decryption_key is not None:
        hex_key = decode_hex_key(args.decryption_key)
        FSCIOTASupportSetKey(args.dev, KeyType=FSCIOTASupportSetKeyRequestKeyType.SBKEK, Key=hex_key)

    if authenticated_image and args.authentication_key is not None:
        hex_hash = decode_hex_key(args.authentication_key)
        FSCIOTASupportSetKey(args.dev, KeyType=FSCIOTASupportSetKeyRequestKeyType.RHK, Key=hex_hash)

    while True:
        confirm = FSCIFirmware_StartImage(args.dev, ImageSize=size)
        assert confirm.Status == 'Success', 'Start Image Failed'

        # turn off FSCI-related prints to avoid flooding the console
        utils.VERBOSE = False

        # start transfer
        start = time()
        while new_request.wait():

            if bytes_sent < size:
                print '\rProgress: ', '{0:.2f}%'.format(100 * float(bytes_sent) / float(size)),
                comm.fsciFramer.send(FsciCommand(
                    opGroup=0xA3,
                    opCode=0x2A,
                    payload=bytearray(chr(seq_no) + contents[bytes_sent:bytes_sent + CHUNK_LEN])
                ))
                new_request.clear()

            elif bytes_sent >= size:
                print '\rProgress: ', '100.00%',
                break
        end = time()
        print '\nAll chunks sent in', end - start, 'seconds.'

        # turn on FSCI-related prints
        utils.VERBOSE = True

        # measure commit image time
        start = time()
        CRCval, BitMask = bytearray(2), bytearray(32)

        if not args.disable_crc:
            CRCval = crc16xmodem(contents)
        if args.erase_nvm:
            BitMask = nvm_erase_bitmask()

        confirm = FSCIFirmware_CommitImage(args.dev, BitMask, not args.disable_crc, CRCval)
        end = time()
        print 'Commit image completed in', end - start, 'seconds.'

        if confirm.Status == 'CRCCheckError' and args.disable_crc:
            print '[FAILED] Bootloader has gFsciUseCRC_c = TRUE;',
            print 'please enable the CRC check by removing -d/--disable-crc.'
            break
        elif confirm.Status == 'CRCCheckError' and not args.disable_crc:
            print '[FAILED] CRC validation failed.'
            break
        elif confirm.Status != 'Success':
            if authenticated_image:
                print '[FAILED] Image authentication failed', confirm.Status
            elif encrypted_image:
                print '[FAILED] Image decryption failed', confirm.Status
            else:
                print '[FAILED] Something went wrong. Commit image return status is', confirm.Status
            break

        if authenticated_image:
            print "Image was authenticated successfully! Sending again for decryption..."
            bytes_sent, seq_no = 0, 0
            authenticated_image = False
            encrypted_image = True
        else:
            break

    FSCICPUReset(args.dev)
    comm.fsciFramer.device.close()


def image_extension_verification(args):

    # verify the image extension

    if not args.bin.endswith(".sbin") and not args.bin.endswith(".bin"):
        return False
    return True


if __name__ == '__main__':

    start = time()
    args = usage()

    if not image_extension_verification(args):
        sys.exit(1)

    # CHUNK_LEN is also used by cb_push_image_cnf, so make it global
    CHUNK_LEN = args.chunk_size
    flash_image(args, *read_image(args.bin))
    end = time()

    print 80 * '='
    print 'TOTAL EXECUTION TIME:', end - start, 'seconds.'
    print 80 * '='
