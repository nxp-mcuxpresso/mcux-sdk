'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.fsci_data_packet import FsciDataPacket


class FsciFrameDescription(object):

    def __init__(self, opGroup, opCode, cmdParams):
        '''
        Constructor

        @param opGroup: byte
        @param opCode: byte
        @param cmdParams: List<FsciParameter>
        '''
        self.opGroup = opGroup
        self.opCode = opCode
        self.cmdParams = cmdParams
        self.paramDict = {}
        self.buildParamDict()

    def buildParamDict(self):

        for param in self.cmdParams:

            if param.selectDict is not None:

                for paramList in param.selectDict.values():

                    for subParam in paramList:

                        origKey = subParam.name
                        if origKey == '':
                            origKey = 'xparam'

                        keySuffix = 1
                        tempKey = origKey

                        while tempKey in self.paramDict:
                            tempKey = origKey + str(keySuffix)
                            keySuffix += 1

                        subParam.name = tempKey
                        self.paramDict[tempKey] = subParam

            origKey2 = param.name
            if origKey2 == '':
                origKey2 = 'xparam'

            keySuffix2 = 1
            tempKey2 = origKey2

            while tempKey2 in self.paramDict:
                tempKey2 = origKey2 + str(keySuffix2)
                keySuffix2 += 1

            param.name = tempKey2
            self.paramDict[tempKey2] = param

    def getParam(self, paramName):
        '''
        @param paramName: String
        '''
        if paramName in self.paramDict:
            return self.paramDict[paramName]
        return None

    def getNewFsciPacket(self):
        return FsciDataPacket(self)

    def getFsciPacketFromByteArray(self, payload, payloadLength):
        payloadInstance = FsciDataPacket(self)
        payloadInstance.fillFromBytes(payload, payloadLength)
        return payloadInstance

    def __repr__(self):
        s = '(OG, OC) = ' + str((self.opGroup, self.opCode)) + '\n'
        for cmdParam in self.cmdParams:
            s += str(cmdParam) + '\n'
        return s


class Protocol(object):
    ZigBee = 0
    FlexibleIP = 1
    Thread = 2
    Sniffer = 3
    BLE = 4
    Firmware = 5
    Hybrid = Thread + BLE


class FsciAckPolicy(object):
    NONE = 0        # no ACKs
    TX = 1          # validate ACKs sent from the device: gFsciTxAck_c TRUE
    RX = 2          # host sends ACKs: gFsciRxAck_c TRUE
    TX_RX = 3       # ACKs in both directions: gFsciTxAck_c, gFsciRxAck_c = TRUE, TRUE
    GLOBAL = 4      # use settings in hsdk.conf
