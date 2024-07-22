'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

class FsciCommand(object):

    '''
    Simple object class that formalizes a FSCI command.
    '''

    def __init__(self, opGroup, opCode, payload):
        '''
        A FSCI command comprises an operation group, an operation code and the
        effective payload data.

        @param opGroup: byte
        @param opCode: byte
        @param payload: bytearray, list of bytes
        '''
        self.opGroup = opGroup
        self.opCode = opCode
        self.payload = payload

    def __str__(self):
        return '(OG, OC) = ' + str((hex(self.opGroup), hex(self.opCode)))
