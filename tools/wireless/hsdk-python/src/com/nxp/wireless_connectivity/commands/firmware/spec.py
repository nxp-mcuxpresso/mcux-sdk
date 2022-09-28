'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.fsci_frame_description import FsciFrameDescription
from com.nxp.wireless_connectivity.commands.fsci_parameter import FsciParameter
from com.nxp.wireless_connectivity.hsdk.singleton import singleton


@singleton
class Spec(object):

    def __init__(self):
        self.FSCIOTASupportSetKeyRequestFrame = self.InitFSCIOTASupportSetKeyRequest()
        self.FSCIEnterBootloaderRequestFrame = self.InitFSCIEnterBootloaderRequest()
        self.FSCICPUResetRequestFrame = self.InitFSCICPUResetRequest()
        self.FSCIFirmware_StartImageRequestFrame = self.InitFSCIFirmware_StartImageRequest()
        self.FSCIFirmware_SetOperationModeRequestFrame = self.InitFSCIFirmware_SetOperationModeRequest()
        self.FSCIFirmware_QueryImageRspRequestFrame = self.InitFSCIFirmware_QueryImageRspRequest()
        self.FSCIFirmware_PushImageChunkRequestFrame = self.InitFSCIFirmware_PushImageChunkRequest()
        self.FSCIFirmware_CancelProcessRequestFrame = self.InitFSCIFirmware_CancelProcessRequest()
        self.FSCIFirmware_CommitImageRequestFrame = self.InitFSCIFirmware_CommitImageRequest()
        self.FSCIFirmware_ImageNotifyRequestFrame = self.InitFSCIFirmware_ImageNotifyRequest()
        self.FSCIFirmware_SetFileVersionPolicyRequestFrame = self.InitFSCIFirmware_SetFileVersionPolicyRequest()
        self.FSCIFirmware_AbortRequestFrame = self.InitFSCIFirmware_AbortRequest()
        self.FSCIFirmware_QueryImageIndicationFrame = self.InitFSCIFirmware_QueryImageIndication()
        self.FSCIFirmware_ChunkIndicationFrame = self.InitFSCIFirmware_ChunkIndication()
        self.FSCIFirmware_StartImageConfirmFrame = self.InitFSCIFirmware_StartImageConfirm()
        self.FSCIFirmware_SetOperationModeConfirmFrame = self.InitFSCIFirmware_SetOperationModeConfirm()
        self.FSCIFirmware_QueryImageRspConfirmFrame = self.InitFSCIFirmware_QueryImageRspConfirm()
        self.FSCIFirmware_PushImageChunkConfirmFrame = self.InitFSCIFirmware_PushImageChunkConfirm()
        self.FSCIFirmware_CancelProcessConfirmFrame = self.InitFSCIFirmware_CancelProcessConfirm()
        self.FSCIFirmware_CommitImageConfirmFrame = self.InitFSCIFirmware_CommitImageConfirm()
        self.FSCIFirmware_ImageNotifyConfirmFrame = self.InitFSCIFirmware_ImageNotifyConfirm()
        self.FSCIFirmware_SetFileVersionPolicyConfirmFrame = self.InitFSCIFirmware_SetFileVersionPolicyConfirm()

    def InitFSCIOTASupportSetKeyRequest(self):
        cmdParams = []
        KeyType = FsciParameter("KeyType", 1)
        cmdParams.append(KeyType)
        Key = FsciParameter("Key", 32)
        cmdParams.append(Key)
        return FsciFrameDescription(0xA3, 0x27, cmdParams)

    def InitFSCIEnterBootloaderRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0xCF, cmdParams)

    def InitFSCICPUResetRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0x08, cmdParams)

    def InitFSCIFirmware_StartImageRequest(self):
        cmdParams = []
        ImageSize = FsciParameter("ImageSize", 4)
        cmdParams.append(ImageSize)
        return FsciFrameDescription(0xA3, 0x29, cmdParams)

    def InitFSCIFirmware_SetOperationModeRequest(self):
        cmdParams = []
        OperationMode = FsciParameter("OperationMode", 1)
        cmdParams.append(OperationMode)
        TransferType = FsciParameter("TransferType", 1)
        cmdParams.append(TransferType)
        return FsciFrameDescription(0xA3, 0x28, cmdParams)

    def InitFSCIFirmware_QueryImageRspRequest(self):
        cmdParams = []
        OtaImageStatus = FsciParameter("OtaImageStatus", 1)
        cmdParams.append(OtaImageStatus)
        DeviceId = FsciParameter("DeviceId", 2)
        cmdParams.append(DeviceId)
        ManufacturerCode = FsciParameter("ManufacturerCode", 2)
        cmdParams.append(ManufacturerCode)
        ImageType = FsciParameter("ImageType", 2)
        cmdParams.append(ImageType)
        FileVersion = FsciParameter("FileVersion", 4)
        cmdParams.append(FileVersion)
        ImageSize = FsciParameter("ImageSize", 4)
        cmdParams.append(ImageSize)
        return FsciFrameDescription(0xA3, 0xC3, cmdParams)

    def InitFSCIFirmware_PushImageChunkRequest(self):
        cmdParams = []
        DataImageBlock = FsciParameter("DataImageBlock", 150)
        cmdParams.append(DataImageBlock)
        return FsciFrameDescription(0xA3, 0x2A, cmdParams)

    def InitFSCIFirmware_CancelProcessRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0x2C, cmdParams)

    def InitFSCIFirmware_CommitImageRequest(self):
        cmdParams = []
        CRCval = FsciParameter("CRCval", 2)
        cmdParams.append(CRCval)
        return FsciFrameDescription(0xA3, 0x2B, cmdParams)

    def InitFSCIFirmware_ImageNotifyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 2)
        cmdParams.append(DeviceId)
        ManufacturerCode = FsciParameter("ManufacturerCode", 2)
        cmdParams.append(ManufacturerCode)
        ImageType = FsciParameter("ImageType", 2)
        cmdParams.append(ImageType)
        ImageSize = FsciParameter("ImageSize", 4)
        cmdParams.append(ImageSize)
        FileSize = FsciParameter("FileSize", 4)
        cmdParams.append(FileSize)
        FileVersion = FsciParameter("FileVersion", 4)
        cmdParams.append(FileVersion)
        return FsciFrameDescription(0xA3, 0xC4, cmdParams)

    def InitFSCIFirmware_SetFileVersionPolicyRequest(self):
        cmdParams = []
        FileVersionPolicy = FsciParameter("FileVersionPolicy", 1)
        cmdParams.append(FileVersionPolicy)
        return FsciFrameDescription(0xA3, 0x2D, cmdParams)

    def InitFSCIFirmware_AbortRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 2)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0xA3, 0x2E, cmdParams)

    def InitFSCIFirmware_QueryImageIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 2)
        cmdParams.append(DeviceId)
        ManufacturerCode = FsciParameter("ManufacturerCode", 2)
        cmdParams.append(ManufacturerCode)
        ImageType = FsciParameter("ImageType", 2)
        cmdParams.append(ImageType)
        FileVersion = FsciParameter("FileVersion", 4)
        cmdParams.append(FileVersion)
        return FsciFrameDescription(0xA3, 0xC2, cmdParams)

    def InitFSCIFirmware_ChunkIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 2)
        cmdParams.append(DeviceId)
        ImageOffset = FsciParameter("ImageOffset", 4)
        cmdParams.append(ImageOffset)
        BlockLength = FsciParameter("BlockLength", 1)
        cmdParams.append(BlockLength)
        return FsciFrameDescription(0xA3, 0x2F, cmdParams)

    def InitFSCIFirmware_StartImageConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        ProtocolVersion = FsciParameter("ProtocolVersion", 1)
        cmdParams.append(ProtocolVersion)
        ExternalMemorySupported = FsciParameter("ExternalMemorySupported", 1)
        cmdParams.append(ExternalMemorySupported)
        return FsciFrameDescription(0xA4, 0x29, cmdParams)

    def InitFSCIFirmware_SetOperationModeConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x28, cmdParams)

    def InitFSCIFirmware_QueryImageRspConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0xC3, cmdParams)

    def InitFSCIFirmware_PushImageChunkConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x2A, cmdParams)

    def InitFSCIFirmware_CancelProcessConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x2C, cmdParams)

    def InitFSCIFirmware_CommitImageConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x2B, cmdParams)

    def InitFSCIFirmware_ImageNotifyConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0xC4, cmdParams)

    def InitFSCIFirmware_SetFileVersionPolicyConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x2D, cmdParams)
