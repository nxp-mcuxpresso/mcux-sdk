'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''


class GenericEnum(object):

    @classmethod
    def getEnumString(cls, value):
        for k, v in cls.__dict__.items():
            if v == value:
                return k
        return value


class FSCIOTASupportSetKeyRequestKeyType(GenericEnum):

    # RHK (authentication)
    RHK = 0x00
    # SBKEK (encryption)
    SBKEK = 0x01


class FSCIFirmware_SetOperationModeRequestOperationMode(GenericEnum):

    Reserved = 0x00
    Standalone = 0x01
    Dongle = 0x02


class FSCIFirmware_SetOperationModeRequestTransferType(GenericEnum):
    Unicast = 0x00
    Multicast = 0x01


class FSCIFirmware_QueryImageRspRequestOtaImageStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
    Abort = 0x95
    NotAuthorized = 0x7E
    InvalidImage = 0x96
    WaitForData = 0x97
    NoImageAvailable = 0x98


class FSCIFirmware_StartImageConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
    InvalidParameter = 0x05
    InvalidOperation = 0x06


class FSCIFirmware_StartImageConfirmProtocolVersion(GenericEnum):

    # ZigbeeCodebase_3.10-3.11_Version
    ZigbeeCodebase_310311_Version = 0x00
    NewVersion = 0x01


class FSCIFirmware_SetOperationModeConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
    # Invalid Parameter
    InvalidParameter = 0x05
    NoMemory = 0x06


class FSCIFirmware_QueryImageRspConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
    # Invalid Parameter
    InvalidParameter = 0x05


class FSCIFirmware_PushImageChunkConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
    UnexpectedSeqNo = 0x03
    InvalidParameter = 0x05
    InvalidOperation = 0x06
    FlashError = 0x07
    MCUFlashError = 0x08


class FSCIFirmware_CancelProcessConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01


class FSCIFirmware_CommitImageConfirmStatus(GenericEnum):

    Success = 0x00
    InvalidParam = 0x05
    InvalidOperation = 0x06
    ExternalFlashError = 0x07
    MCUFlashError = 0x08
    CRCCheckError = 0x04


class FSCIFirmware_ImageNotifyConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01


class FSCIFirmware_SetFileVersionPolicyConfirmStatus(GenericEnum):

    Success = 0x00
    Failed = 0x01
