'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.firmware.enums import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.hsdk.utils import to_bytes


class FSCIOTASupportSetKeyRequest(object):

    def __init__(self, KeyType=FSCIOTASupportSetKeyRequestKeyType.RHK, Key=bytearray(32)):
        '''
        @param KeyType: Type of key (RHK or SBKEK)
        @param Key: Key value
        '''
        self.KeyType = KeyType
        self.Key = Key


class FSCIEnterBootloaderRequest(object):

    pass


class FSCICPUResetRequest(object):

    pass


class FSCIFirmware_StartImageRequest(object):

    def __init__(self, ImageSize=bytearray(4)):
        '''
        @param ImageSize: ImageSize with all sub-elements
        '''
        self.ImageSize = ImageSize


class FSCIFirmware_SetOperationModeRequest(object):

    def __init__(self, OperationMode=FSCIFirmware_SetOperationModeRequestOperationMode.Reserved, TransferType=FSCIFirmware_SetOperationModeRequestTransferType.Unicast):
        '''
        @param OperationMode: operation mode
        @param TransferType: transfer type: Unicast|Multicast
        '''
        self.OperationMode = OperationMode
        self.TransferType = TransferType


class FSCIFirmware_QueryImageRspRequest(object):

    def __init__(self, OtaImageStatus=FSCIFirmware_QueryImageRspRequestOtaImageStatus.Success, DeviceId=bytearray(2), ManufacturerCode=bytearray(2), ImageType=bytearray(2), FileVersion=bytearray(4), ImageSize=bytearray(4)):
        '''
        @param OtaImageStatus: OTA image status
        @param DeviceId: Device Identifier
        @param ManufacturerCode: Manufacturer Code
        @param ImageType: Image Type
        @param FileVersion: File Version
        @param ImageSize: Image Size
        '''
        self.OtaImageStatus = OtaImageStatus
        self.DeviceId = DeviceId
        self.ManufacturerCode = ManufacturerCode
        self.ImageType = ImageType
        self.FileVersion = FileVersion
        self.ImageSize = ImageSize


class FSCIFirmware_PushImageChunkRequest(object):

    def __init__(self, DataImageBlock=bytearray(), SeqNo=bytearray(1), FSCIBootloaderMode=False):
        '''
        @param DataImageBlock: DataImageBlock - variable length
        @param SeqNo: The sequence number of the current image chunk. Optional, can be disabled from SW.
        @param BootloaderMode: if True, add SeqNo to packet
        '''
        self.DataImageBlock = DataImageBlock
        self.SeqNo = SeqNo
        self.FSCIBootloaderMode = FSCIBootloaderMode  # not sent OTW

    def pickle(self):
        # return as is, do not go through Spec
        if self.FSCIBootloaderMode:
            return bytearray([self.SeqNo]) + bytearray(self.DataImageBlock)
        else:
            return bytearray(self.DataImageBlock)


class FSCIFirmware_CancelProcessRequest(object):

    pass


class FSCIFirmware_CommitImageRequest(object):

    def __init__(self, BitMask=bytearray(32), CRCEnabled=True, CRCval=bytearray(2)):
        '''
        @param CRCEnabled: whether or not to include CRCval on send. Not sent OTW.
        @param CRCval: Expected CRCval of flash bootload image contents, passed in and check via internal CRC check
        '''
        self.BitMask = BitMask
        self.CRCEnabled = CRCEnabled
        self.CRCval = CRCval

    def pickle(self):
        result = bytearray(to_bytes(self.BitMask, 32))
        if self.CRCEnabled:
            result += bytearray(to_bytes(self.CRCval, 2))
        return result


class FSCIFirmware_ImageNotifyRequest(object):

    def __init__(self, DeviceId=bytearray(2), ManufacturerCode=bytearray(2), ImageType=bytearray(2), ImageSize=bytearray(4), FileSize=bytearray(4), FileVersion=bytearray(4)):
        '''
        @param DeviceId: Device Identifier
        @param ManufacturerCode: ManufacturerCode
        @param ImageType: ImageType
        @param ImageSize: ImageSize
        @param FileSize: FileSize
        @param FileVersion: FileVersion
        '''
        self.DeviceId = DeviceId
        self.ManufacturerCode = ManufacturerCode
        self.ImageType = ImageType
        self.ImageSize = ImageSize
        self.FileSize = FileSize
        self.FileVersion = FileVersion


class FSCIFirmware_SetFileVersionPolicyRequest(object):

    def __init__(self, FileVersionPolicy=bytearray(1)):
        '''
        @param FileVersionPolicy: File version Policy: bit 0 - upgrade, bit 1- reinstall, bit 2 - downgrade
        '''
        self.FileVersionPolicy = FileVersionPolicy


class FSCIFirmware_AbortRequest(object):

    def __init__(self, DeviceId=bytearray(2)):
        '''
        @param DeviceId: DeviceID
        '''
        self.DeviceId = DeviceId


class FSCIFirmware_QueryImageIndication(object):

    def __init__(self, DeviceId=bytearray(2), ManufacturerCode=bytearray(2), ImageType=bytearray(2), FileVersion=bytearray(4)):
        '''
        @param DeviceId: Device Identifier
        @param ManufacturerCode: Manufacturer Code
        @param ImageType: Image Type
        @param FileVersion: File Version
        '''
        self.DeviceId = DeviceId
        self.ManufacturerCode = ManufacturerCode
        self.ImageType = ImageType
        self.FileVersion = FileVersion


class FSCIFirmware_ChunkIndication(object):

    def __init__(self, DeviceId=bytearray(2), ImageOffset=bytearray(4), BlockLength=bytearray(1)):
        '''
        @param DeviceId: Device Identifier
        @param ImageOffset: ImageOffset
        @param BlockLength: BlockLength
        '''
        self.DeviceId = DeviceId
        self.ImageOffset = ImageOffset
        self.BlockLength = BlockLength


class FSCIFirmware_StartImageConfirm(object):

    def __init__(self, Status=FSCIFirmware_StartImageConfirmStatus.Success, ProtocolVersion=FSCIFirmware_StartImageConfirmProtocolVersion.ZigbeeCodebase_310311_Version, ExternalMemorySupported=bytearray(1)):
        '''
        @param Status: Status
        @param ProtocolVersion: ProtocolVersion
        @param ExternalMemorySupported: ExternalMemorySupported
        '''
        self.Status = Status
        self.ProtocolVersion = ProtocolVersion
        self.ExternalMemorySupported = ExternalMemorySupported


class FSCIFirmware_SetOperationModeConfirm(object):

    def __init__(self, Status=FSCIFirmware_SetOperationModeConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_QueryImageRspConfirm(object):

    def __init__(self, Status=FSCIFirmware_QueryImageRspConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_PushImageChunkConfirm(object):

    def __init__(self, Status=FSCIFirmware_PushImageChunkConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_CancelProcessConfirm(object):

    def __init__(self, Status=FSCIFirmware_CancelProcessConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_CommitImageConfirm(object):

    def __init__(self, Status=FSCIFirmware_CommitImageConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_ImageNotifyConfirm(object):

    def __init__(self, Status=FSCIFirmware_ImageNotifyConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIFirmware_SetFileVersionPolicyConfirm(object):

    def __init__(self, Status=FSCIFirmware_SetFileVersionPolicyConfirmStatus.Success):
        '''
        @param Status: Status
        '''
        self.Status = Status
