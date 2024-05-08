'''
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from ctypes import cast, c_uint8, c_void_p, POINTER
import inspect
import sys

from com.nxp.wireless_connectivity.commands.firmware.frames import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.commands.firmware.spec import Spec as _Spec
from com.nxp.wireless_connectivity.hsdk.CFsciLibrary import FsciFrame
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader
from com.nxp.wireless_connectivity.hsdk.utils import Observer, overrides, print_event


fsciLibrary = LibraryLoader().CFsciLibrary
fsciLibrary.DestroyFSCIFrame.argtypes = [c_void_p]
Spec = _Spec()


class FSCIFirmware_QueryImageIndicationObserver(Observer):

    opGroup = Spec.FSCIFirmware_QueryImageIndicationFrame.opGroup
    opCode = Spec.FSCIFirmware_QueryImageIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_QueryImageIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_QueryImageIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ManufacturerCode = packet.getParamValueAsNumber("ManufacturerCode")
        frame.ImageType = packet.getParamValueAsNumber("ImageType")
        frame.FileVersion = packet.getParamValueAsNumber("FileVersion")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_ChunkIndicationObserver(Observer):

    opGroup = Spec.FSCIFirmware_ChunkIndicationFrame.opGroup
    opCode = Spec.FSCIFirmware_ChunkIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_ChunkIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_ChunkIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ImageOffset = packet.getParamValueAsNumber("ImageOffset")
        frame.BlockLength = packet.getParamValueAsNumber("BlockLength")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_StartImageConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_StartImageConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_StartImageConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_StartImageConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_StartImageConfirm()
        frame.Status = FSCIFirmware_StartImageConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        frame.ProtocolVersion = packet.getParamValueAsNumber("ProtocolVersion")
        frame.ExternalMemorySupported = packet.getParamValueAsNumber("ExternalMemorySupported")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_SetOperationModeConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_SetOperationModeConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_SetOperationModeConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_SetOperationModeConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_SetOperationModeConfirm()
        frame.Status = FSCIFirmware_SetOperationModeConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_QueryImageRspConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_QueryImageRspConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_QueryImageRspConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_QueryImageRspConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_QueryImageRspConfirm()
        frame.Status = FSCIFirmware_QueryImageRspConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_PushImageChunkConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_PushImageChunkConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_PushImageChunkConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_PushImageChunkConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_PushImageChunkConfirm()
        frame.Status = FSCIFirmware_PushImageChunkConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_CancelProcessConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_CancelProcessConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_CancelProcessConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_CancelProcessConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_CancelProcessConfirm()
        frame.Status = FSCIFirmware_CancelProcessConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_CommitImageConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_CommitImageConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_CommitImageConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_CommitImageConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_CommitImageConfirm()
        frame.Status = FSCIFirmware_CommitImageConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_ImageNotifyConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_ImageNotifyConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_ImageNotifyConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_ImageNotifyConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_ImageNotifyConfirm()
        frame.Status = FSCIFirmware_ImageNotifyConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIFirmware_SetFileVersionPolicyConfirmObserver(Observer):

    opGroup = Spec.FSCIFirmware_SetFileVersionPolicyConfirmFrame.opGroup
    opCode = Spec.FSCIFirmware_SetFileVersionPolicyConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIFirmware_SetFileVersionPolicyConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIFirmware_SetFileVersionPolicyConfirm()
        frame.Status = FSCIFirmware_SetFileVersionPolicyConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


allObservers = {}
observersList = [cls(clsName[:-len('Observer')]) for (clsName, cls) in inspect.getmembers(
    sys.modules[__name__], inspect.isclass) if clsName.endswith('Observer') and clsName != 'Observer']
for observer in observersList:
    allObservers[(observer.opGroup, observer.opCode)] = observer
