'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.fsci_frame_description import Protocol, FsciAckPolicy
from com.nxp.wireless_connectivity.commands.firmware.enums import *  # @UnusedWildImport
import com.nxp.wireless_connectivity.commands.firmware.frames as Frames
from com.nxp.wireless_connectivity.commands.firmware.operations import *  # @UnusedWildImport


def FSCIOTASupportSetKey(
    device,
    KeyType=FSCIOTASupportSetKeyRequestKeyType.RHK,
    # Unit length: 32 bytes
    Key=bytearray(32),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Thread,
    timeout=3
):
    request = Frames.FSCIOTASupportSetKeyRequest(KeyType, Key)
    return FSCIOTASupportSetKeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIEnterBootloader(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=1
):
    request = Frames.FSCIEnterBootloaderRequest()
    return FSCIEnterBootloaderOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCICPUReset(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=1
):
    request = Frames.FSCICPUResetRequest()
    return FSCICPUResetOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_StartImage(
    device,
    ImageSize=bytearray(4),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_StartImageRequest(ImageSize)
    return FSCIFirmware_StartImageOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_SetOperationMode(
    device,
    OperationMode=FSCIFirmware_SetOperationModeRequestOperationMode.Reserved,
    TransferType=FSCIFirmware_SetOperationModeRequestTransferType.Unicast,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_SetOperationModeRequest(OperationMode)
    return FSCIFirmware_SetOperationModeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_QueryImageRsp(
    device,
    OtaImageStatus=FSCIFirmware_QueryImageRspRequestOtaImageStatus.Success,
    DeviceId=bytearray(2),
    ManufacturerCode=bytearray(2),
    ImageType=bytearray(2),
    FileVersion=bytearray(4),
    ImageSize=bytearray(4),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_QueryImageRspRequest(OtaImageStatus, DeviceId, ManufacturerCode, ImageType, FileVersion, ImageSize)
    return FSCIFirmware_QueryImageRspOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_PushImageChunk(
    device,
    DataImageBlock=bytearray(),
    SeqNo=bytearray(1),
    FSCIBootloaderMode=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_PushImageChunkRequest(DataImageBlock, SeqNo, FSCIBootloaderMode)
    return FSCIFirmware_PushImageChunkOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_CancelProcess(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_CancelProcessRequest()
    return FSCIFirmware_CancelProcessOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_CommitImage(
    device,
    BitMask=bytearray(32),
    CRCEnabled=True,
    CRCval=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_CommitImageRequest(BitMask, CRCEnabled, CRCval)
    return FSCIFirmware_CommitImageOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_ImageNotify(
    device,
    DeviceId=bytearray(2),
    ManufacturerCode=bytearray(2),
    ImageType=bytearray(2),
    ImageSize=bytearray(4),
    FileSize=bytearray(4),
    FileVersion=bytearray(4),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_ImageNotifyRequest(DeviceId, ManufacturerCode, ImageType, ImageSize, FileSize, FileVersion)
    return FSCIFirmware_ImageNotifyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_SetFileVersionPolicy(
    device,
    FileVersionPolicy=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_SetFileVersionPolicyRequest(FileVersionPolicy)
    return FSCIFirmware_SetFileVersionPolicyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIFirmware_Abort(
    device,
    DeviceId=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.Firmware,
    timeout=3
):
    request = Frames.FSCIFirmware_AbortRequest(DeviceId)
    return FSCIFirmware_AbortOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)
