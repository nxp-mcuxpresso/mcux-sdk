'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2022 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

import copy
from ctypes import cast, c_uint8, c_void_p, POINTER
from datetime import datetime
import inspect
import re
import sys

from com.nxp.wireless_connectivity.commands.ble.frames import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.commands.ble.spec import Spec as _Spec
from com.nxp.wireless_connectivity.hsdk.CFsciLibrary import FsciFrame
from com.nxp.wireless_connectivity.hsdk.library_loader import LibraryLoader
from com.nxp.wireless_connectivity.hsdk.utils import Observer, overrides, print_event


fsciLibrary = LibraryLoader().CFsciLibrary
fsciLibrary.DestroyFSCIFrame.argtypes = [c_void_p]
Spec = _Spec()

class GAPGetConnectionHandleFromDeviceIdObserver(Observer):

    opGroup = Spec.GAPGetConnectionHandleFromDeviceIdFrame.opGroup
    opCode = Spec.GAPGetConnectionHandleFromDeviceIdFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetConnectionHandleFromDeviceIdFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetConnectionHandleFromDeviceId()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetHostVersionObserver(Observer):

    opGroup = Spec.GAPGetHostVersionFrame.opGroup
    opCode = Spec.GAPGetHostVersionFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGetHostVersion()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPEattConnectionAcceptObserver(Observer):

    opGroup = Spec.GAPEattConnectionAcceptFrame.opGroup
    opCode = Spec.GAPEattConnectionAcceptFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPEattConnectionAcceptFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPEattConnectionAccept()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Accept = packet.getParamValueAsNumber("Accept")
        frame.MTU = packet.getParamValueAsNumber("MTU")
        frame.InitialCredits = packet.getParamValueAsNumber("InitialCredits")
        frame.AutoCreditsMgmt = packet.getParamValueAsNumber("AutoCreditsMgmt")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIGetNumberOfFreeBuffersResponseObserver(Observer):

    opGroup = Spec.FSCIGetNumberOfFreeBuffersResponseFrame.opGroup
    opCode = Spec.FSCIGetNumberOfFreeBuffersResponseFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIGetNumberOfFreeBuffersResponseFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIGetNumberOfFreeBuffersResponse()
        frame.FreeBuffers = packet.getParamValueAsNumber("FreeBuffers")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIAckIndicationObserver(Observer):

    opGroup = Spec.FSCIAckIndicationFrame.opGroup
    opCode = Spec.FSCIAckIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIAckIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIAckIndication()
        frame.Checksum = packet.getParamValueAsNumber("Checksum")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIErrorIndicationObserver(Observer):

    opGroup = Spec.FSCIErrorIndicationFrame.opGroup
    opCode = Spec.FSCIErrorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIErrorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIErrorIndication()
        frame.Status = FSCIErrorIndicationStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIAllowDeviceToSleepConfirmObserver(Observer):

    opGroup = Spec.FSCIAllowDeviceToSleepConfirmFrame.opGroup
    opCode = Spec.FSCIAllowDeviceToSleepConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIAllowDeviceToSleepConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIAllowDeviceToSleepConfirm()
        frame.Status = FSCIAllowDeviceToSleepConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIWakeUpIndicationObserver(Observer):

    opGroup = Spec.FSCIWakeUpIndicationFrame.opGroup
    opCode = Spec.FSCIWakeUpIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = FSCIWakeUpIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIGetWakeupReasonResponseObserver(Observer):

    opGroup = Spec.FSCIGetWakeupReasonResponseFrame.opGroup
    opCode = Spec.FSCIGetWakeupReasonResponseFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIGetWakeupReasonResponseFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIGetWakeupReasonResponse()
        frame.WakeUpReason = packet.getParamValueAsNumber("WakeUpReason")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class FSCIGetNbuVersionResponseObserver(Observer):

    opGroup = Spec.FSCIGetNbuVersionResponseFrame.opGroup
    opCode = Spec.FSCIGetNbuVersionResponseFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.FSCIGetNbuVersionResponseFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = FSCIGetNbuVersionResponse()
        frame.versionNumber = packet.getParamValueAsNumber("versionNumber")
        frame.ShaLength = packet.getParamValueAsNumber("ShaLength")
        frame.SHA = packet.getParamValueAsNumber("SHA")
        frame.TagLength = packet.getParamValueAsNumber("TagLength")
        frame.TagString = packet.getParamValueAsList("TagString")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBConfirmObserver(Observer):

    opGroup = Spec.L2CAPCBConfirmFrame.opGroup
    opCode = Spec.L2CAPCBConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.L2CAPCBConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = L2CAPCBConfirm()
        frame.Status = L2CAPCBConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLePsmConnectionRequestIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLePsmConnectionRequestIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLePsmConnectionRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLePsmConnectionRequestIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbConnectionRequest = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbConnectionRequest = L2CAPCBLePsmConnectionRequestIndication.LeCbConnectionRequest()
            LeCbConnectionRequest.DeviceId = data.contents[curr]
            curr += 1
            LeCbConnectionRequest.LePsm = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionRequest.PeerMtu = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionRequest.PeerMps = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionRequest.InitialCredits = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.LeCbConnectionRequest = copy.deepcopy(LeCbConnectionRequest)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLePsmConnectionCompleteIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLePsmConnectionCompleteIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLePsmConnectionCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLePsmConnectionCompleteIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbConnectionComplete = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbConnectionComplete = L2CAPCBLePsmConnectionCompleteIndication.LeCbConnectionComplete()
            LeCbConnectionComplete.DeviceId = data.contents[curr]
            curr += 1
            LeCbConnectionComplete.ChannelId = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionComplete.PeerMtu = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionComplete.PeerMps = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionComplete.InitialCredits = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbConnectionComplete.Result = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.LeCbConnectionComplete = copy.deepcopy(LeCbConnectionComplete)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLePsmDisconnectNotificationIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLePsmDisconnectNotificationIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLePsmDisconnectNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLePsmDisconnectNotificationIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbDisconnection = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbDisconnection = L2CAPCBLePsmDisconnectNotificationIndication.LeCbDisconnection()
            LeCbDisconnection.DeviceId = data.contents[curr]
            curr += 1
            LeCbDisconnection.ChannelId = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.LeCbDisconnection = copy.deepcopy(LeCbDisconnection)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBNoPeerCreditsIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBNoPeerCreditsIndicationFrame.opGroup
    opCode = Spec.L2CAPCBNoPeerCreditsIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBNoPeerCreditsIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbNoPeerCredits = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbNoPeerCredits = L2CAPCBNoPeerCreditsIndication.LeCbNoPeerCredits()
            LeCbNoPeerCredits.DeviceId = data.contents[curr]
            curr += 1
            LeCbNoPeerCredits.ChannelId = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.LeCbNoPeerCredits = copy.deepcopy(LeCbNoPeerCredits)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLocalCreditsNotificationIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLocalCreditsNotificationIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLocalCreditsNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLocalCreditsNotificationIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbLocalCreditsNotification = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbLocalCreditsNotification = L2CAPCBLocalCreditsNotificationIndication.LeCbLocalCreditsNotification()
            LeCbLocalCreditsNotification.DeviceId = data.contents[curr]
            curr += 1
            LeCbLocalCreditsNotification.ChannelId = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbLocalCreditsNotification.LocalCredits = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.LeCbLocalCreditsNotification = copy.deepcopy(LeCbLocalCreditsNotification)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLeCbDataIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLeCbDataIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLeCbDataIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.L2CAPCBLeCbDataIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = L2CAPCBLeCbDataIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.SrcCid = packet.getParamValueAsNumber("SrcCid")
        frame.PacketLength = packet.getParamValueAsNumber("PacketLength")
        frame.Packet = packet.getParamValueAsList("Packet")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBErrorIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBErrorIndicationFrame.opGroup
    opCode = Spec.L2CAPCBErrorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBErrorIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.LeCbError = []
        if frame.InformationIncluded:
            # Create sub-object container
            LeCbError = L2CAPCBErrorIndication.LeCbError()
            LeCbError.DeviceId = data.contents[curr]
            curr += 1
            LeCbError.Error = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            LeCbError.l2caErrorSource_t = data.contents[curr]
            curr += 1
            frame.LeCbError = copy.deepcopy(LeCbError)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBChannelStatusNotificationIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBChannelStatusNotificationIndicationFrame.opGroup
    opCode = Spec.L2CAPCBChannelStatusNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.L2CAPCBChannelStatusNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = L2CAPCBChannelStatusNotificationIndication()
        frame.InformationIncluded = packet.getParamValueAsNumber("InformationIncluded")
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.SrcCid = packet.getParamValueAsNumber("SrcCid")
        frame.ChannelStatus = L2CAPCBChannelStatusNotificationIndicationChannelStatus.getEnumString(packet.getParamValueAsNumber("ChannelStatus"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLePsmEnhancedConnectRequestIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLePsmEnhancedConnectRequestIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLePsmEnhancedConnectRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLePsmEnhancedConnectRequestIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.EnhancedConnRequest = []
        if frame.InformationIncluded:
            # Create sub-object container
            EnhancedConnRequest = L2CAPCBLePsmEnhancedConnectRequestIndication.EnhancedConnRequest()
            EnhancedConnRequest.DeviceId = data.contents[curr]
            curr += 1
            EnhancedConnRequest.LePsm = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnRequest.PeerMtu = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnRequest.PeerMps = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnRequest.InitialCredits = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnRequest.NoOfChannels = data.contents[curr]
            curr += 1
            EnhancedConnRequest.aCids = list_to_int(data.contents[curr:curr + EnhancedConnRequest.NoOfChannels * 2])
            curr += EnhancedConnRequest.NoOfChannels * 2
            frame.EnhancedConnRequest = copy.deepcopy(EnhancedConnRequest)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBLePsmEnhancedConnectionCompleteIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBLePsmEnhancedConnectionCompleteIndicationFrame.opGroup
    opCode = Spec.L2CAPCBLePsmEnhancedConnectionCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBLePsmEnhancedConnectionCompleteIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.EnhancedConnComplete = []
        if frame.InformationIncluded:
            # Create sub-object container
            EnhancedConnComplete = L2CAPCBLePsmEnhancedConnectionCompleteIndication.EnhancedConnComplete()
            EnhancedConnComplete.DeviceId = data.contents[curr]
            curr += 1
            EnhancedConnComplete.PeerMtu = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnComplete.PeerMps = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnComplete.InitialCredits = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnComplete.Result = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedConnComplete.NoOfChannels = data.contents[curr]
            curr += 1
            EnhancedConnComplete.aCids = list_to_int(data.contents[curr:curr + EnhancedConnComplete.NoOfChannels * 2])
            curr += EnhancedConnComplete.NoOfChannels * 2
            frame.EnhancedConnComplete = copy.deepcopy(EnhancedConnComplete)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBEnhancedReconfigureRequestIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBEnhancedReconfigureRequestIndicationFrame.opGroup
    opCode = Spec.L2CAPCBEnhancedReconfigureRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBEnhancedReconfigureRequestIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.EnhancedReconfigureRequest = []
        if frame.InformationIncluded:
            # Create sub-object container
            EnhancedReconfigureRequest = L2CAPCBEnhancedReconfigureRequestIndication.EnhancedReconfigureRequest()
            EnhancedReconfigureRequest.DeviceId = data.contents[curr]
            curr += 1
            EnhancedReconfigureRequest.NewMtu = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedReconfigureRequest.NewMps = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedReconfigureRequest.Result = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            EnhancedReconfigureRequest.NoOfChannels = data.contents[curr]
            curr += 1
            EnhancedReconfigureRequest.aCids = list_to_int(data.contents[curr:curr + EnhancedReconfigureRequest.NoOfChannels * 2])
            curr += EnhancedReconfigureRequest.NoOfChannels * 2
            frame.EnhancedReconfigureRequest = copy.deepcopy(EnhancedReconfigureRequest)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class L2CAPCBEnhancedReconfigureResponseIndicationObserver(Observer):

    opGroup = Spec.L2CAPCBEnhancedReconfigureResponseIndicationFrame.opGroup
    opCode = Spec.L2CAPCBEnhancedReconfigureResponseIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = L2CAPCBEnhancedReconfigureResponseIndication()
        curr = 0
        frame.InformationIncluded = data.contents[curr]
        curr += 1
        frame.EnhancedReconfigureResponse = []
        if frame.InformationIncluded:
            # Create sub-object container
            EnhancedReconfigureResponse = L2CAPCBEnhancedReconfigureResponseIndication.EnhancedReconfigureResponse()
            EnhancedReconfigureResponse.DeviceId = data.contents[curr]
            curr += 1
            EnhancedReconfigureResponse.Result = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.EnhancedReconfigureResponse = copy.deepcopy(EnhancedReconfigureResponse)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTConfirmObserver(Observer):

    opGroup = Spec.GATTConfirmFrame.opGroup
    opCode = Spec.GATTConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTConfirm()
        frame.Status = GATTConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
            if frame.Status != 'gBleSuccess_c':
                print('\t[warning] GATTConfirm w/ Status ' + str(frame.Status))
        fsciLibrary.DestroyFSCIFrame(event)


class GATTGetMtuIndicationObserver(Observer):

    opGroup = Spec.GATTGetMtuIndicationFrame.opGroup
    opCode = Spec.GATTGetMtuIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTGetMtuIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTGetMtuIndication()
        frame.Mtu = packet.getParamValueAsNumber("Mtu")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureExchangeMtuIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureExchangeMtuIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureExchangeMtuIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureExchangeMtuIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureExchangeMtuIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureDiscoverAllPrimaryServicesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureDiscoverAllPrimaryServicesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureDiscoverAllPrimaryServicesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureDiscoverAllPrimaryServicesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfDiscoveredServices = data.contents[curr]
        curr += 1
        frame.DiscoveredServices = []
        for _ in range(frame.NbOfDiscoveredServices):
            # Create sub-object container
            DiscoveredServices = GATTClientProcedureDiscoverAllPrimaryServicesIndication.DiscoveredServices()
            DiscoveredServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.UuidType = data.contents[curr]
            curr += 1
            if DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            DiscoveredServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            DiscoveredServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            DiscoveredServices.Characteristics = []
            for _ in range(DiscoveredServices.NbOfCharacteristics):
                # Create sub-object container
                Characteristics = GATTClientProcedureDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics()
                Characteristics.Properties = data.contents[curr]
                curr += 1
                # Create sub-object container
                Characteristics.Value = GATTClientProcedureDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics.Value()
                Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.UuidType = data.contents[curr]
                curr += 1
                if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                    selected_len = 2
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                    selected_len = 16
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
                curr += Characteristics.Value.ValueLength * 1
                Characteristics.NbOfDescriptors = data.contents[curr]
                curr += 1
                Characteristics.Descriptors = []
                for _ in range(Characteristics.NbOfDescriptors):
                    # Create sub-object container
                    Descriptors = GATTClientProcedureDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics.Descriptors()
                    Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.UuidType = data.contents[curr]
                    curr += 1
                    if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                        selected_len = 2
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                        selected_len = 16
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                        selected_len = 4
                    else:
                        print("Wrong UuidType value!")
                    Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                    curr += selected_len
                    Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                    curr += Descriptors.ValueLength * 1
                    # Add sub-object to list container.
                    Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

                # Add sub-object to list container.
                DiscoveredServices.Characteristics.append(copy.deepcopy(Characteristics))

            DiscoveredServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            DiscoveredServices.IncludedServices = []
            for _ in range(DiscoveredServices.NbOfIncludedServices):
                # Create sub-object container
                IncludedServices = GATTClientProcedureDiscoverAllPrimaryServicesIndication.DiscoveredServices.IncludedServices()
                IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.UuidType = data.contents[curr]
                curr += 1
                if IncludedServices.UuidType == IncludedServicesUuidType.Uuid16Bits:
                    selected_len = 2
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid128Bits:
                    selected_len = 16
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                IncludedServices.NbOfCharacteristics = data.contents[curr]
                curr += 1
                IncludedServices.NbOfIncludedServices = data.contents[curr]
                curr += 1
                # Add sub-object to list container.
                DiscoveredServices.IncludedServices.append(copy.deepcopy(IncludedServices))

            # Add sub-object to list container.
            frame.DiscoveredServices.append(copy.deepcopy(DiscoveredServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfDiscoveredServices = data.contents[curr]
        curr += 1
        frame.DiscoveredServices = []
        for _ in range(frame.NbOfDiscoveredServices):
            # Create sub-object container
            DiscoveredServices = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.DiscoveredServices()
            DiscoveredServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.UuidType = data.contents[curr]
            curr += 1
            if DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            DiscoveredServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            DiscoveredServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            DiscoveredServices.Characteristics = []
            for _ in range(DiscoveredServices.NbOfCharacteristics):
                # Create sub-object container
                Characteristics = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics()
                Characteristics.Properties = data.contents[curr]
                curr += 1
                # Create sub-object container
                Characteristics.Value = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics.Value()
                Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.UuidType = data.contents[curr]
                curr += 1
                if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                    selected_len = 2
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                    selected_len = 16
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
                curr += Characteristics.Value.ValueLength * 1
                Characteristics.NbOfDescriptors = data.contents[curr]
                curr += 1
                Characteristics.Descriptors = []
                for _ in range(Characteristics.NbOfDescriptors):
                    # Create sub-object container
                    Descriptors = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics.Descriptors()
                    Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.UuidType = data.contents[curr]
                    curr += 1
                    if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                        selected_len = 2
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                        selected_len = 16
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                        selected_len = 4
                    else:
                        print("Wrong UuidType value!")
                    Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                    curr += selected_len
                    Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                    curr += Descriptors.ValueLength * 1
                    # Add sub-object to list container.
                    Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

                # Add sub-object to list container.
                DiscoveredServices.Characteristics.append(copy.deepcopy(Characteristics))

            DiscoveredServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            DiscoveredServices.IncludedServices = []
            for _ in range(DiscoveredServices.NbOfIncludedServices):
                # Create sub-object container
                IncludedServices = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.IncludedServices()
                IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.UuidType = data.contents[curr]
                curr += 1
                if IncludedServices.UuidType == IncludedServicesUuidType.Uuid16Bits:
                    selected_len = 2
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid128Bits:
                    selected_len = 16
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                IncludedServices.NbOfCharacteristics = data.contents[curr]
                curr += 1
                IncludedServices.NbOfIncludedServices = data.contents[curr]
                curr += 1
                # Add sub-object to list container.
                DiscoveredServices.IncludedServices.append(copy.deepcopy(IncludedServices))

            # Add sub-object to list container.
            frame.DiscoveredServices.append(copy.deepcopy(DiscoveredServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureFindIncludedServicesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureFindIncludedServicesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureFindIncludedServicesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureFindIncludedServicesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Service_StartHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_EndHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_UuidType = data.contents[curr]
        curr += 1
        #frame.Service_Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        frame.Service_Uuid = list_to_int(data.contents[curr:curr + selected_len])
        curr += selected_len
        frame.Service_NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Service_Characteristics = []
        for _ in range(frame.Service_NbOfCharacteristics):
            # Create sub-object container
            Service_Characteristics = GATTClientProcedureFindIncludedServicesIndication.Service_Characteristics()
            Service_Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Service_Characteristics.Value = GATTClientProcedureFindIncludedServicesIndication.Service_Characteristics.Value()
            Service_Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Service_Characteristics.Value.ValueLength * 1])
            curr += Service_Characteristics.Value.ValueLength * 1
            Service_Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Service_Characteristics.Descriptors = []
            for _ in range(Service_Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureFindIncludedServicesIndication.Service_Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Service_Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Service_Characteristics.append(copy.deepcopy(Service_Characteristics))

        frame.Service_NbOfIncludedServices = data.contents[curr]
        curr += 1
        frame.Service_IncludedServices = []
        for _ in range(frame.Service_NbOfIncludedServices):
            # Create sub-object container
            Service_IncludedServices = GATTClientProcedureFindIncludedServicesIndication.Service_IncludedServices()
            Service_IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.UuidType = data.contents[curr]
            curr += 1
            if Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_IncludedServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            Service_IncludedServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            # Add sub-object to list container.
            frame.Service_IncludedServices.append(copy.deepcopy(Service_IncludedServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureDiscoverAllCharacteristicsIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureDiscoverAllCharacteristicsIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureDiscoverAllCharacteristicsIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureDiscoverAllCharacteristicsIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Service_StartHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_EndHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_UuidType = data.contents[curr]
        curr += 1
        #frame.Service_Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        frame.Service_Uuid = list_to_int(data.contents[curr:curr + selected_len])
        curr += selected_len
        frame.Service_NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Service_Characteristics = []
        for _ in range(frame.Service_NbOfCharacteristics):
            # Create sub-object container
            Service_Characteristics = GATTClientProcedureDiscoverAllCharacteristicsIndication.Service_Characteristics()
            Service_Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Service_Characteristics.Value = GATTClientProcedureDiscoverAllCharacteristicsIndication.Service_Characteristics.Value()
            Service_Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Service_Characteristics.Value.ValueLength * 1])
            curr += Service_Characteristics.Value.ValueLength * 1
            Service_Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Service_Characteristics.Descriptors = []
            for _ in range(Service_Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureDiscoverAllCharacteristicsIndication.Service_Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Service_Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Service_Characteristics.append(copy.deepcopy(Service_Characteristics))

        frame.Service_NbOfIncludedServices = data.contents[curr]
        curr += 1
        frame.Service_IncludedServices = []
        for _ in range(frame.Service_NbOfIncludedServices):
            # Create sub-object container
            Service_IncludedServices = GATTClientProcedureDiscoverAllCharacteristicsIndication.Service_IncludedServices()
            Service_IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.UuidType = data.contents[curr]
            curr += 1
            if Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_IncludedServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            Service_IncludedServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            # Add sub-object to list container.
            frame.Service_IncludedServices.append(copy.deepcopy(Service_IncludedServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureDiscoverCharacteristicByUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureDiscoverCharacteristicByUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureDiscoverCharacteristicByUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureDiscoverCharacteristicByUuidIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureDiscoverCharacteristicByUuidIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureDiscoverCharacteristicByUuidIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureDiscoverCharacteristicByUuidIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Characteristic_Properties = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Handle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.UuidType = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Characteristic_Value.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
        curr += selected_len
        frame.Characteristic_Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        #frame.Characteristic_Value.Value = data.contents[curr]
        #curr += 1
        frame.Characteristic_Value.Value = data.contents[curr:curr + frame.Characteristic_Value.ValueLength]
        curr += frame.Characteristic_Value.ValueLength

        frame.Characteristic_NbOfDescriptors = data.contents[curr]
        curr += 1
        frame.Characteristic_Descriptors = []
        for _ in range(frame.Characteristic_NbOfDescriptors):
            # Create sub-object container
            Characteristic_Descriptors = GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication.Characteristic_Descriptors()
            Characteristic_Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.UuidType = data.contents[curr]
            curr += 1
            if Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristic_Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristic_Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.Value = list_to_int(data.contents[curr:curr + Characteristic_Descriptors.ValueLength * 1])
            curr += Characteristic_Descriptors.ValueLength * 1
            # Add sub-object to list container.
            frame.Characteristic_Descriptors.append(copy.deepcopy(Characteristic_Descriptors))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureReadCharacteristicValueIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureReadCharacteristicValueIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureReadCharacteristicValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureReadCharacteristicValueIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Characteristic_Properties = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Handle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.UuidType = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Characteristic_Value.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
        curr += selected_len
        frame.Characteristic_Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        #frame.Characteristic_Value.Value = data.contents[curr]
        #curr += 1
        frame.Characteristic_Value.Value = data.contents[curr:curr + frame.Characteristic_Value.ValueLength]
        curr += frame.Characteristic_Value.ValueLength
        frame.Characteristic_NbOfDescriptors = data.contents[curr]
        curr += 1
        frame.Characteristic_Descriptors = []
        for _ in range(frame.Characteristic_NbOfDescriptors):
            # Create sub-object container
            Characteristic_Descriptors = GATTClientProcedureReadCharacteristicValueIndication.Characteristic_Descriptors()
            Characteristic_Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.UuidType = data.contents[curr]
            curr += 1
            if Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristic_Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristic_Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.Value = list_to_int(data.contents[curr:curr + Characteristic_Descriptors.ValueLength * 1])
            curr += Characteristic_Descriptors.ValueLength * 1
            # Add sub-object to list container.
            frame.Characteristic_Descriptors.append(copy.deepcopy(Characteristic_Descriptors))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureReadUsingCharacteristicUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureReadUsingCharacteristicUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureReadUsingCharacteristicUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureReadUsingCharacteristicUuidIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureReadUsingCharacteristicUuidIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfReadBytes = packet.getParamValueAsNumber("NbOfReadBytes")
        frame.ReadBytes = packet.getParamValueAsList("ReadBytes")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureReadMultipleCharacteristicValuesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureReadMultipleCharacteristicValuesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureReadMultipleCharacteristicValuesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureReadMultipleCharacteristicValuesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureReadMultipleCharacteristicValuesIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureReadMultipleCharacteristicValuesIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureReadMultipleCharacteristicValuesIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureWriteCharacteristicValueIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureWriteCharacteristicValueIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureWriteCharacteristicValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureWriteCharacteristicValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureWriteCharacteristicValueIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureReadCharacteristicDescriptorIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureReadCharacteristicDescriptorIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureReadCharacteristicDescriptorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureReadCharacteristicDescriptorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureReadCharacteristicDescriptorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Descriptor_Handle = packet.getParamValueAsNumber("Descriptor_Handle")
        frame.Descriptor_UuidType = packet.getParamValueAsNumber("Descriptor_UuidType")
        frame.Descriptor_Uuid = packet.getParamValueAsNumber("Descriptor_Uuid")
        frame.Descriptor_ValueLength = packet.getParamValueAsNumber("Descriptor_ValueLength")
        frame.Descriptor_MaxValueLength = packet.getParamValueAsNumber("Descriptor_MaxValueLength")
        frame.Descriptor_Value = packet.getParamValueAsList("Descriptor_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureWriteCharacteristicDescriptorIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureWriteCharacteristicDescriptorIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureWriteCharacteristicDescriptorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureWriteCharacteristicDescriptorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureWriteCharacteristicDescriptorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientNotificationIndicationObserver(Observer):

    opGroup = Spec.GATTClientNotificationIndicationFrame.opGroup
    opCode = Spec.GATTClientNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientNotificationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.CharacteristicValueHandle = packet.getParamValueAsNumber("CharacteristicValueHandle")
        frame.ValueLength = packet.getParamValueAsNumber("ValueLength")
        frame.Value = packet.getParamValueAsList("Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientMultipleHandleValueNotificationIndicationObserver(Observer):

    opGroup = Spec.GATTClientMultipleHandleValueNotificationIndicationFrame.opGroup
    opCode = Spec.GATTClientMultipleHandleValueNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientMultipleHandleValueNotificationIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.HandleCount = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.HandleLengthValueList = []
        for _ in range(frame.HandleCount):
            # Create sub-object container
            HandleLengthValueList = GATTClientMultipleHandleValueNotificationIndication.HandleLengthValueList()
            HandleLengthValueList.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            HandleLengthValueList.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            HandleLengthValueList.Value = list_to_int(data.contents[curr:curr + HandleLengthValueList.ValueLength * 1])
            curr += HandleLengthValueList.ValueLength * 1
            # Add sub-object to list container.
            frame.HandleLengthValueList.append(copy.deepcopy(HandleLengthValueList))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureReadMultipleVariableLenCharValuesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureReadMultipleVariableLenCharValuesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureReadMultipleVariableLenCharValuesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureReadMultipleVariableLenCharValuesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureReadMultipleVariableLenCharValuesIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureReadMultipleVariableLenCharValuesIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureReadMultipleVariableLenCharValuesIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientIndicationIndicationObserver(Observer):

    opGroup = Spec.GATTClientIndicationIndicationFrame.opGroup
    opCode = Spec.GATTClientIndicationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientIndicationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientIndicationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.CharacteristicValueHandle = packet.getParamValueAsNumber("CharacteristicValueHandle")
        frame.ValueLength = packet.getParamValueAsNumber("ValueLength")
        frame.Value = packet.getParamValueAsList("Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerMtuChangedIndicationObserver(Observer):

    opGroup = Spec.GATTServerMtuChangedIndicationFrame.opGroup
    opCode = Spec.GATTServerMtuChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerMtuChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerMtuChangedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.MtuChangedEvent_NewMtu = packet.getParamValueAsNumber("MtuChangedEvent_NewMtu")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerHandleValueConfirmationIndicationObserver(Observer):

    opGroup = Spec.GATTServerHandleValueConfirmationIndicationFrame.opGroup
    opCode = Spec.GATTServerHandleValueConfirmationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerHandleValueConfirmationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerHandleValueConfirmationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerAttributeWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerAttributeWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerAttributeWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerAttributeWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerAttributeWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.AttributeWrittenEvent_Handle = packet.getParamValueAsNumber("AttributeWrittenEvent_Handle")
        frame.AttributeWrittenEvent_ValueLength = packet.getParamValueAsNumber("AttributeWrittenEvent_ValueLength")
        frame.AttributeWrittenEvent_Value = packet.getParamValueAsList("AttributeWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerCharacteristicCccdWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerCharacteristicCccdWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerCharacteristicCccdWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerCharacteristicCccdWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerCharacteristicCccdWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.CharCccdWrittenEvent_Handle = packet.getParamValueAsNumber("CharCccdWrittenEvent_Handle")
        frame.CharCccdWrittenEvent_NewCccd = packet.getParamValueAsNumber("CharCccdWrittenEvent_NewCccd")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerAttributeWrittenWithoutResponseIndicationObserver(Observer):

    opGroup = Spec.GATTServerAttributeWrittenWithoutResponseIndicationFrame.opGroup
    opCode = Spec.GATTServerAttributeWrittenWithoutResponseIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerAttributeWrittenWithoutResponseIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerAttributeWrittenWithoutResponseIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.AttributeWrittenEvent_Handle = packet.getParamValueAsNumber("AttributeWrittenEvent_Handle")
        frame.AttributeWrittenEvent_ValueLength = packet.getParamValueAsNumber("AttributeWrittenEvent_ValueLength")
        frame.AttributeWrittenEvent_Value = packet.getParamValueAsList("AttributeWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerErrorIndicationObserver(Observer):

    opGroup = Spec.GATTServerErrorIndicationFrame.opGroup
    opCode = Spec.GATTServerErrorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerErrorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerErrorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ProcedureError_ProcedureType = packet.getParamValueAsNumber("ProcedureError_ProcedureType")
        frame.ProcedureError_Error = packet.getParamValueAsNumber("ProcedureError_Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerLongCharacteristicWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerLongCharacteristicWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerLongCharacteristicWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerLongCharacteristicWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerLongCharacteristicWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.LongCharacteristicWrittenEvent_Handle = packet.getParamValueAsNumber("LongCharacteristicWrittenEvent_Handle")
        frame.LongCharacteristicWrittenEvent_ValueLength = packet.getParamValueAsNumber("LongCharacteristicWrittenEvent_ValueLength")
        frame.LongCharacteristicWrittenEvent_Value = packet.getParamValueAsList("LongCharacteristicWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerAttributeReadIndicationObserver(Observer):

    opGroup = Spec.GATTServerAttributeReadIndicationFrame.opGroup
    opCode = Spec.GATTServerAttributeReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerAttributeReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerAttributeReadIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.AttributeReadEvent_Handle = packet.getParamValueAsNumber("AttributeReadEvent_Handle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfDiscoveredServices = data.contents[curr]
        curr += 1
        frame.DiscoveredServices = []
        for _ in range(frame.NbOfDiscoveredServices):
            # Create sub-object container
            DiscoveredServices = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication.DiscoveredServices()
            DiscoveredServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.UuidType = data.contents[curr]
            curr += 1
            if DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            DiscoveredServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            DiscoveredServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            DiscoveredServices.Characteristics = []
            for _ in range(DiscoveredServices.NbOfCharacteristics):
                # Create sub-object container
                Characteristics = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics()
                Characteristics.Properties = data.contents[curr]
                curr += 1
                # Create sub-object container
                Characteristics.Value = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics.Value()
                Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.UuidType = data.contents[curr]
                curr += 1
                if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                    selected_len = 2
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                    selected_len = 16
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
                curr += Characteristics.Value.ValueLength * 1
                Characteristics.NbOfDescriptors = data.contents[curr]
                curr += 1
                Characteristics.Descriptors = []
                for _ in range(Characteristics.NbOfDescriptors):
                    # Create sub-object container
                    Descriptors = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication.DiscoveredServices.Characteristics.Descriptors()
                    Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.UuidType = data.contents[curr]
                    curr += 1
                    if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                        selected_len = 2
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                        selected_len = 16
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                        selected_len = 4
                    else:
                        print("Wrong UuidType value!")
                    Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                    curr += selected_len
                    Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                    curr += Descriptors.ValueLength * 1
                    # Add sub-object to list container.
                    Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

                # Add sub-object to list container.
                DiscoveredServices.Characteristics.append(copy.deepcopy(Characteristics))

            DiscoveredServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            DiscoveredServices.IncludedServices = []
            for _ in range(DiscoveredServices.NbOfIncludedServices):
                # Create sub-object container
                IncludedServices = GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication.DiscoveredServices.IncludedServices()
                IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.UuidType = data.contents[curr]
                curr += 1
                if IncludedServices.UuidType == IncludedServicesUuidType.Uuid16Bits:
                    selected_len = 2
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid128Bits:
                    selected_len = 16
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                IncludedServices.NbOfCharacteristics = data.contents[curr]
                curr += 1
                IncludedServices.NbOfIncludedServices = data.contents[curr]
                curr += 1
                # Add sub-object to list container.
                DiscoveredServices.IncludedServices.append(copy.deepcopy(IncludedServices))

            # Add sub-object to list container.
            frame.DiscoveredServices.append(copy.deepcopy(DiscoveredServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfDiscoveredServices = data.contents[curr]
        curr += 1
        frame.DiscoveredServices = []
        for _ in range(frame.NbOfDiscoveredServices):
            # Create sub-object container
            DiscoveredServices = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication.DiscoveredServices()
            DiscoveredServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            DiscoveredServices.UuidType = data.contents[curr]
            curr += 1
            if DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif DiscoveredServices.UuidType == DiscoveredServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            DiscoveredServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            DiscoveredServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            DiscoveredServices.Characteristics = []
            for _ in range(DiscoveredServices.NbOfCharacteristics):
                # Create sub-object container
                Characteristics = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics()
                Characteristics.Properties = data.contents[curr]
                curr += 1
                # Create sub-object container
                Characteristics.Value = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics.Value()
                Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.UuidType = data.contents[curr]
                curr += 1
                if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                    selected_len = 2
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                    selected_len = 16
                elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
                curr += Characteristics.Value.ValueLength * 1
                Characteristics.NbOfDescriptors = data.contents[curr]
                curr += 1
                Characteristics.Descriptors = []
                for _ in range(Characteristics.NbOfDescriptors):
                    # Create sub-object container
                    Descriptors = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.Characteristics.Descriptors()
                    Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.UuidType = data.contents[curr]
                    curr += 1
                    if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                        selected_len = 2
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                        selected_len = 16
                    elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                        selected_len = 4
                    else:
                        print("Wrong UuidType value!")
                    Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                    curr += selected_len
                    Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                    curr += 2
                    Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                    curr += Descriptors.ValueLength * 1
                    # Add sub-object to list container.
                    Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

                # Add sub-object to list container.
                DiscoveredServices.Characteristics.append(copy.deepcopy(Characteristics))

            DiscoveredServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            DiscoveredServices.IncludedServices = []
            for _ in range(DiscoveredServices.NbOfIncludedServices):
                # Create sub-object container
                IncludedServices = GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication.DiscoveredServices.IncludedServices()
                IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                IncludedServices.UuidType = data.contents[curr]
                curr += 1
                if IncludedServices.UuidType == IncludedServicesUuidType.Uuid16Bits:
                    selected_len = 2
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid128Bits:
                    selected_len = 16
                elif IncludedServices.UuidType == IncludedServicesUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                IncludedServices.NbOfCharacteristics = data.contents[curr]
                curr += 1
                IncludedServices.NbOfIncludedServices = data.contents[curr]
                curr += 1
                # Add sub-object to list container.
                DiscoveredServices.IncludedServices.append(copy.deepcopy(IncludedServices))

            # Add sub-object to list container.
            frame.DiscoveredServices.append(copy.deepcopy(DiscoveredServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedFindIncludedServicesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedFindIncludedServicesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedFindIncludedServicesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedFindIncludedServicesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Service_StartHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_EndHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_UuidType = data.contents[curr]
        curr += 1
        frame.Service_Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        curr += selected_len
        frame.Service_NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Service_Characteristics = []
        for _ in range(frame.Service_NbOfCharacteristics):
            # Create sub-object container
            Service_Characteristics = GATTClientProcedureEnhancedFindIncludedServicesIndication.Service_Characteristics()
            Service_Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Service_Characteristics.Value = GATTClientProcedureEnhancedFindIncludedServicesIndication.Service_Characteristics.Value()
            Service_Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Service_Characteristics.Value.ValueLength * 1])
            curr += Service_Characteristics.Value.ValueLength * 1
            Service_Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Service_Characteristics.Descriptors = []
            for _ in range(Service_Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureEnhancedFindIncludedServicesIndication.Service_Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Service_Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Service_Characteristics.append(copy.deepcopy(Service_Characteristics))

        frame.Service_NbOfIncludedServices = data.contents[curr]
        curr += 1
        frame.Service_IncludedServices = []
        for _ in range(frame.Service_NbOfIncludedServices):
            # Create sub-object container
            Service_IncludedServices = GATTClientProcedureEnhancedFindIncludedServicesIndication.Service_IncludedServices()
            Service_IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.UuidType = data.contents[curr]
            curr += 1
            if Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_IncludedServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            Service_IncludedServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            # Add sub-object to list container.
            frame.Service_IncludedServices.append(copy.deepcopy(Service_IncludedServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Service_StartHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_EndHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Service_UuidType = data.contents[curr]
        curr += 1
        frame.Service_Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        curr += selected_len
        frame.Service_NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Service_Characteristics = []
        for _ in range(frame.Service_NbOfCharacteristics):
            # Create sub-object container
            Service_Characteristics = GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication.Service_Characteristics()
            Service_Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Service_Characteristics.Value = GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication.Service_Characteristics.Value()
            Service_Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_Characteristics.Value.UuidType == Service_Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Service_Characteristics.Value.ValueLength * 1])
            curr += Service_Characteristics.Value.ValueLength * 1
            Service_Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Service_Characteristics.Descriptors = []
            for _ in range(Service_Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication.Service_Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Service_Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Service_Characteristics.append(copy.deepcopy(Service_Characteristics))

        frame.Service_NbOfIncludedServices = data.contents[curr]
        curr += 1
        frame.Service_IncludedServices = []
        for _ in range(frame.Service_NbOfIncludedServices):
            # Create sub-object container
            Service_IncludedServices = GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication.Service_IncludedServices()
            Service_IncludedServices.StartHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.EndHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Service_IncludedServices.UuidType = data.contents[curr]
            curr += 1
            if Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid16Bits:
                selected_len = 2
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid128Bits:
                selected_len = 16
            elif Service_IncludedServices.UuidType == Service_IncludedServicesUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Service_IncludedServices.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Service_IncludedServices.NbOfCharacteristics = data.contents[curr]
            curr += 1
            Service_IncludedServices.NbOfIncludedServices = data.contents[curr]
            curr += 1
            # Add sub-object to list container.
            frame.Service_IncludedServices.append(copy.deepcopy(Service_IncludedServices))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Characteristic_Properties = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Handle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.UuidType = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Characteristic_Value.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        curr += selected_len
        frame.Characteristic_Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.Value = data.contents[curr]
        curr += 1
        frame.Characteristic_NbOfDescriptors = data.contents[curr]
        curr += 1
        frame.Characteristic_Descriptors = []
        for _ in range(frame.Characteristic_NbOfDescriptors):
            # Create sub-object container
            Characteristic_Descriptors = GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndication.Characteristic_Descriptors()
            Characteristic_Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.UuidType = data.contents[curr]
            curr += 1
            if Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristic_Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristic_Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.Value = list_to_int(data.contents[curr:curr + Characteristic_Descriptors.ValueLength * 1])
            curr += Characteristic_Descriptors.ValueLength * 1
            # Add sub-object to list container.
            frame.Characteristic_Descriptors.append(copy.deepcopy(Characteristic_Descriptors))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedReadCharacteristicValueIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedReadCharacteristicValueIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedReadCharacteristicValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedReadCharacteristicValueIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Characteristic_Properties = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Handle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.UuidType = data.contents[curr]
        curr += 1
        frame.Characteristic_Value.Uuid = list_to_int(data.contents[curr:curr + 0])
        if frame.Characteristic_Value.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        elif frame.Characteristic_Value.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        else:
            print("Wrong UuidType value!")
        curr += selected_len
        frame.Characteristic_Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Characteristic_Value.Value = data.contents[curr]
        curr += 1
        frame.Characteristic_NbOfDescriptors = data.contents[curr]
        curr += 1
        frame.Characteristic_Descriptors = []
        for _ in range(frame.Characteristic_NbOfDescriptors):
            # Create sub-object container
            Characteristic_Descriptors = GATTClientProcedureEnhancedReadCharacteristicValueIndication.Characteristic_Descriptors()
            Characteristic_Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.UuidType = data.contents[curr]
            curr += 1
            if Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristic_Descriptors.UuidType == Characteristic_DescriptorsUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristic_Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristic_Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristic_Descriptors.Value = list_to_int(data.contents[curr:curr + Characteristic_Descriptors.ValueLength * 1])
            curr += Characteristic_Descriptors.ValueLength * 1
            # Add sub-object to list container.
            frame.Characteristic_Descriptors.append(copy.deepcopy(Characteristic_Descriptors))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfReadBytes = packet.getParamValueAsNumber("NbOfReadBytes")
        frame.ReadBytes = packet.getParamValueAsList("ReadBytes")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedWriteCharacteristicValueIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedWriteCharacteristicValueIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedWriteCharacteristicValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureEnhancedWriteCharacteristicValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureEnhancedWriteCharacteristicValueIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureEnhancedReadCharacteristicDescriptorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.Descriptor_Handle = packet.getParamValueAsNumber("Descriptor_Handle")
        frame.Descriptor_UuidType = packet.getParamValueAsNumber("Descriptor_UuidType")
        frame.Descriptor_Uuid = packet.getParamValueAsNumber("Descriptor_Uuid")
        frame.Descriptor_ValueLength = packet.getParamValueAsNumber("Descriptor_ValueLength")
        frame.Descriptor_MaxValueLength = packet.getParamValueAsNumber("Descriptor_MaxValueLength")
        frame.Descriptor_Value = packet.getParamValueAsList("Descriptor_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.ProcedureResult = packet.getParamValueAsNumber("ProcedureResult")
        frame.Error = packet.getParamValueAsNumber("Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndicationObserver(Observer):

    opGroup = Spec.GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndicationFrame.opGroup
    opCode = Spec.GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.ProcedureResult = data.contents[curr]
        curr += 1
        frame.Error = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        if frame.ProcedureResult == 0x01:
            callback(self.deviceName, frame) if callback else print_event(self.deviceName, frame)
            fsciLibrary.DestroyFSCIFrame(event)
            return
        frame.NbOfCharacteristics = data.contents[curr]
        curr += 1
        frame.Characteristics = []
        for _ in range(frame.NbOfCharacteristics):
            # Create sub-object container
            Characteristics = GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication.Characteristics()
            Characteristics.Properties = data.contents[curr]
            curr += 1
            # Create sub-object container
            Characteristics.Value = GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication.Characteristics.Value()
            Characteristics.Value.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.UuidType = data.contents[curr]
            curr += 1
            if Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid16Bits:
                selected_len = 2
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid128Bits:
                selected_len = 16
            elif Characteristics.Value.UuidType == Characteristics.ValueUuidType.Uuid32Bits:
                selected_len = 4
            else:
                print("Wrong UuidType value!")
            Characteristics.Value.Uuid = list_to_int(data.contents[curr:curr + selected_len])
            curr += selected_len
            Characteristics.Value.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Characteristics.Value.Value = list_to_int(data.contents[curr:curr + Characteristics.Value.ValueLength * 1])
            curr += Characteristics.Value.ValueLength * 1
            Characteristics.NbOfDescriptors = data.contents[curr]
            curr += 1
            Characteristics.Descriptors = []
            for _ in range(Characteristics.NbOfDescriptors):
                # Create sub-object container
                Descriptors = GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication.Characteristics.Descriptors()
                Descriptors.Handle = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.UuidType = data.contents[curr]
                curr += 1
                if Descriptors.UuidType == DescriptorsUuidType.Uuid16Bits:
                    selected_len = 2
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid128Bits:
                    selected_len = 16
                elif Descriptors.UuidType == DescriptorsUuidType.Uuid32Bits:
                    selected_len = 4
                else:
                    print("Wrong UuidType value!")
                Descriptors.Uuid = list_to_int(data.contents[curr:curr + selected_len])
                curr += selected_len
                Descriptors.ValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.MaxValueLength = list_to_int(data.contents[curr:curr + 2])
                curr += 2
                Descriptors.Value = list_to_int(data.contents[curr:curr + Descriptors.ValueLength * 1])
                curr += Descriptors.ValueLength * 1
                # Add sub-object to list container.
                Characteristics.Descriptors.append(copy.deepcopy(Descriptors))

            # Add sub-object to list container.
            frame.Characteristics.append(copy.deepcopy(Characteristics))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientEnhancedMultipleHandleValueNotificationIndicationObserver(Observer):

    opGroup = Spec.GATTClientEnhancedMultipleHandleValueNotificationIndicationFrame.opGroup
    opCode = Spec.GATTClientEnhancedMultipleHandleValueNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTClientEnhancedMultipleHandleValueNotificationIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.BearerId = data.contents[curr]
        curr += 1
        frame.HandleCount = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.HandleLengthValueList = []
        for _ in range(frame.HandleCount):
            # Create sub-object container
            HandleLengthValueList = GATTClientEnhancedMultipleHandleValueNotificationIndication.HandleLengthValueList()
            HandleLengthValueList.Handle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            HandleLengthValueList.ValueLength = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            HandleLengthValueList.Value = list_to_int(data.contents[curr:curr + HandleLengthValueList.ValueLength * 1])
            curr += HandleLengthValueList.ValueLength * 1
            # Add sub-object to list container.
            frame.HandleLengthValueList.append(copy.deepcopy(HandleLengthValueList))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientEnhancedNotificationIndicationObserver(Observer):

    opGroup = Spec.GATTClientEnhancedNotificationIndicationFrame.opGroup
    opCode = Spec.GATTClientEnhancedNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientEnhancedNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientEnhancedNotificationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.CharacteristicValueHandle = packet.getParamValueAsNumber("CharacteristicValueHandle")
        frame.ValueLength = packet.getParamValueAsNumber("ValueLength")
        frame.Value = packet.getParamValueAsList("Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTClientEnhancedIndicationIndicationObserver(Observer):

    opGroup = Spec.GATTClientEnhancedIndicationIndicationFrame.opGroup
    opCode = Spec.GATTClientEnhancedIndicationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTClientEnhancedIndicationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTClientEnhancedIndicationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.CharacteristicValueHandle = packet.getParamValueAsNumber("CharacteristicValueHandle")
        frame.ValueLength = packet.getParamValueAsNumber("ValueLength")
        frame.Value = packet.getParamValueAsList("Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedHandleValueConfirmationIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedHandleValueConfirmationIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedHandleValueConfirmationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedHandleValueConfirmationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedHandleValueConfirmationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedAttributeWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedAttributeWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedAttributeWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedAttributeWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedAttributeWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.AttributeWrittenEvent_Handle = packet.getParamValueAsNumber("AttributeWrittenEvent_Handle")
        frame.AttributeWrittenEvent_ValueLength = packet.getParamValueAsNumber("AttributeWrittenEvent_ValueLength")
        frame.AttributeWrittenEvent_Value = packet.getParamValueAsList("AttributeWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedCharacteristicCccdWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedCharacteristicCccdWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedCharacteristicCccdWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedCharacteristicCccdWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedCharacteristicCccdWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.CharCccdWrittenEvent_Handle = packet.getParamValueAsNumber("CharCccdWrittenEvent_Handle")
        frame.CharCccdWrittenEvent_NewCccd = packet.getParamValueAsNumber("CharCccdWrittenEvent_NewCccd")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedAttributeWrittenWithoutResponseIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedAttributeWrittenWithoutResponseIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedAttributeWrittenWithoutResponseIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedAttributeWrittenWithoutResponseIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedAttributeWrittenWithoutResponseIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.AttributeWrittenEvent_Handle = packet.getParamValueAsNumber("AttributeWrittenEvent_Handle")
        frame.AttributeWrittenEvent_ValueLength = packet.getParamValueAsNumber("AttributeWrittenEvent_ValueLength")
        frame.AttributeWrittenEvent_Value = packet.getParamValueAsList("AttributeWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedErrorIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedErrorIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedErrorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedErrorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedErrorIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.ProcedureError_ProcedureType = packet.getParamValueAsNumber("ProcedureError_ProcedureType")
        frame.ProcedureError_Error = packet.getParamValueAsNumber("ProcedureError_Error")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedLongCharacteristicWrittenIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedLongCharacteristicWrittenIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedLongCharacteristicWrittenIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedLongCharacteristicWrittenIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedLongCharacteristicWrittenIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.LongCharacteristicWrittenEvent_Handle = packet.getParamValueAsNumber("LongCharacteristicWrittenEvent_Handle")
        frame.LongCharacteristicWrittenEvent_ValueLength = packet.getParamValueAsNumber("LongCharacteristicWrittenEvent_ValueLength")
        frame.LongCharacteristicWrittenEvent_Value = packet.getParamValueAsList("LongCharacteristicWrittenEvent_Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTServerEnhancedAttributeReadIndicationObserver(Observer):

    opGroup = Spec.GATTServerEnhancedAttributeReadIndicationFrame.opGroup
    opCode = Spec.GATTServerEnhancedAttributeReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTServerEnhancedAttributeReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTServerEnhancedAttributeReadIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.AttributeReadEvent_Handle = packet.getParamValueAsNumber("AttributeReadEvent_Handle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBConfirmObserver(Observer):

    opGroup = Spec.GATTDBConfirmFrame.opGroup
    opCode = Spec.GATTDBConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBConfirm()
        #frame.Status = GATTDBConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        frame.Status = packet.getParamValueAsNumber("Status")

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBReadAttributeIndicationObserver(Observer):

    opGroup = Spec.GATTDBReadAttributeIndicationFrame.opGroup
    opCode = Spec.GATTDBReadAttributeIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBReadAttributeIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBReadAttributeIndication()
        frame.ValueLength = packet.getParamValueAsNumber("ValueLength")
        frame.Value = packet.getParamValueAsList("Value")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBFindServiceHandleIndicationObserver(Observer):

    opGroup = Spec.GATTDBFindServiceHandleIndicationFrame.opGroup
    opCode = Spec.GATTDBFindServiceHandleIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBFindServiceHandleIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBFindServiceHandleIndication()
        frame.ServiceHandle = packet.getParamValueAsNumber("ServiceHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBFindCharValueHandleInServiceIndicationObserver(Observer):

    opGroup = Spec.GATTDBFindCharValueHandleInServiceIndicationFrame.opGroup
    opCode = Spec.GATTDBFindCharValueHandleInServiceIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBFindCharValueHandleInServiceIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBFindCharValueHandleInServiceIndication()
        frame.CharValueHandle = packet.getParamValueAsNumber("CharValueHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBFindCccdHandleForCharValueHandleIndicationObserver(Observer):

    opGroup = Spec.GATTDBFindCccdHandleForCharValueHandleIndicationFrame.opGroup
    opCode = Spec.GATTDBFindCccdHandleForCharValueHandleIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBFindCccdHandleForCharValueHandleIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBFindCccdHandleForCharValueHandleIndication()
        frame.CccdHandle = packet.getParamValueAsNumber("CccdHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBFindDescriptorHandleForCharValueHandleIndicationObserver(Observer):

    opGroup = Spec.GATTDBFindDescriptorHandleForCharValueHandleIndicationFrame.opGroup
    opCode = Spec.GATTDBFindDescriptorHandleForCharValueHandleIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBFindDescriptorHandleForCharValueHandleIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBFindDescriptorHandleForCharValueHandleIndication()
        frame.DescriptorHandle = packet.getParamValueAsNumber("DescriptorHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddPrimaryServiceDeclarationIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddPrimaryServiceDeclarationIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddPrimaryServiceDeclarationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddPrimaryServiceDeclarationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddPrimaryServiceDeclarationIndication()
        frame.ServiceHandle = packet.getParamValueAsNumber("ServiceHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddSecondaryServiceDeclarationIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddSecondaryServiceDeclarationIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddSecondaryServiceDeclarationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddSecondaryServiceDeclarationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddSecondaryServiceDeclarationIndication()
        frame.ServiceHandle = packet.getParamValueAsNumber("ServiceHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddIncludeDeclarationIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddIncludeDeclarationIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddIncludeDeclarationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddIncludeDeclarationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddIncludeDeclarationIndication()
        frame.IncludeHandle = packet.getParamValueAsNumber("IncludeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddCharacteristicDeclarationAndValueIndication()
        frame.CharacteristicHandle = packet.getParamValueAsNumber("CharacteristicHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddCharacteristicDescriptorIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddCharacteristicDescriptorIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddCharacteristicDescriptorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddCharacteristicDescriptorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddCharacteristicDescriptorIndication()
        frame.DescriptorHandle = packet.getParamValueAsNumber("DescriptorHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddCccdIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddCccdIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddCccdIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddCccdIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddCccdIndication()
        frame.CCCDHandle = packet.getParamValueAsNumber("CCCDHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication()
        frame.CharacteristicHandle = packet.getParamValueAsNumber("CharacteristicHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationObserver(Observer):

    opGroup = Spec.GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationFrame.opGroup
    opCode = Spec.GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBDynamicAddCharDescriptorWithUniqueValueIndication()
        frame.DescriptorHandle = packet.getParamValueAsNumber("DescriptorHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttConfirmObserver(Observer):

    opGroup = Spec.GATTDBAttConfirmFrame.opGroup
    opCode = Spec.GATTDBAttConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttConfirm()
        frame.Status = GATTDBAttConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttFindInformationIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttFindInformationIndicationFrame.opGroup
    opCode = Spec.GATTDBAttFindInformationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttFindInformationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttFindInformationIndication()
        frame.Params_Format = packet.getParamValueAsNumber("Params_Format")
        frame.Params_InformationData = packet.getParamValueAsNumber("Params_InformationData")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttFindByTypeValueIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttFindByTypeValueIndicationFrame.opGroup
    opCode = Spec.GATTDBAttFindByTypeValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GATTDBAttFindByTypeValueIndication()
        curr = 0
        frame.Params_GroupCount = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        frame.Params_HandleGroup = []
        for _ in range(frame.Params_GroupCount):
            # Create sub-object container
            Params_HandleGroup = GATTDBAttFindByTypeValueIndication.Params_HandleGroup()
            Params_HandleGroup.StartingHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            Params_HandleGroup.EndingHandle = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            # Add sub-object to list container.
            frame.Params_HandleGroup.append(copy.deepcopy(Params_HandleGroup))

        frame.ErrorAttributeHandle = list_to_int(data.contents[curr:curr + 2])
        curr += 2
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttReadByTypeIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttReadByTypeIndicationFrame.opGroup
    opCode = Spec.GATTDBAttReadByTypeIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttReadByTypeIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttReadByTypeIndication()
        frame.Params_Length = packet.getParamValueAsNumber("Params_Length")
        frame.Params_AttributeDataListLength = packet.getParamValueAsNumber("Params_AttributeDataListLength")
        frame.Params_AttributeDataList = packet.getParamValueAsList("Params_AttributeDataList")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttReadIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttReadIndicationFrame.opGroup
    opCode = Spec.GATTDBAttReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttReadIndication()
        frame.Params_AttributeLength = packet.getParamValueAsNumber("Params_AttributeLength")
        frame.Params_AttributeValue = packet.getParamValueAsList("Params_AttributeValue")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttReadBlobIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttReadBlobIndicationFrame.opGroup
    opCode = Spec.GATTDBAttReadBlobIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttReadBlobIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttReadBlobIndication()
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttReadMultipleIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttReadMultipleIndicationFrame.opGroup
    opCode = Spec.GATTDBAttReadMultipleIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttReadMultipleIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttReadMultipleIndication()
        frame.Params_ListLength = packet.getParamValueAsNumber("Params_ListLength")
        frame.Params_ListOfValues = packet.getParamValueAsList("Params_ListOfValues")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttReadByGroupTypeIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttReadByGroupTypeIndicationFrame.opGroup
    opCode = Spec.GATTDBAttReadByGroupTypeIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttReadByGroupTypeIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttReadByGroupTypeIndication()
        frame.Params_Length = packet.getParamValueAsNumber("Params_Length")
        frame.Params_AttributeDataListLength = packet.getParamValueAsNumber("Params_AttributeDataListLength")
        frame.Params_AttributeDataList = packet.getParamValueAsList("Params_AttributeDataList")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttWriteIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttWriteIndicationFrame.opGroup
    opCode = Spec.GATTDBAttWriteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttWriteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttWriteIndication()
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttPrepareWriteIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttPrepareWriteIndicationFrame.opGroup
    opCode = Spec.GATTDBAttPrepareWriteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttPrepareWriteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttPrepareWriteIndication()
        frame.Params_AttributeHandle = packet.getParamValueAsNumber("Params_AttributeHandle")
        frame.Params_ValueOffset = packet.getParamValueAsNumber("Params_ValueOffset")
        frame.Params_AttributeLength = packet.getParamValueAsNumber("Params_AttributeLength")
        frame.Params_AttributeValue = packet.getParamValueAsList("Params_AttributeValue")
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttExecuteWriteIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttExecuteWriteIndicationFrame.opGroup
    opCode = Spec.GATTDBAttExecuteWriteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttExecuteWriteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttExecuteWriteIndication()
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttExecuteWriteFromQueueIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttExecuteWriteFromQueueIndicationFrame.opGroup
    opCode = Spec.GATTDBAttExecuteWriteFromQueueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttExecuteWriteFromQueueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttExecuteWriteFromQueueIndication()
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GATTDBAttPrepareNotificationIndicationIndicationObserver(Observer):

    opGroup = Spec.GATTDBAttPrepareNotificationIndicationIndicationFrame.opGroup
    opCode = Spec.GATTDBAttPrepareNotificationIndicationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GATTDBAttPrepareNotificationIndicationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GATTDBAttPrepareNotificationIndicationIndication()
        frame.ErrorAttributeHandle = packet.getParamValueAsNumber("ErrorAttributeHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConfirmObserver(Observer):

    opGroup = Spec.GAPConfirmFrame.opGroup
    opCode = Spec.GAPConfirmFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConfirmFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConfirm()
        frame.Status = GAPConfirmStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
            if frame.Status != 'gBleSuccess_c':
                print('\t[warning] GAPConfirm w/ Status ' + str(frame.Status))
        fsciLibrary.DestroyFSCIFrame(event)


class GAPCheckNotificationStatusIndicationObserver(Observer):

    opGroup = Spec.GAPCheckNotificationStatusIndicationFrame.opGroup
    opCode = Spec.GAPCheckNotificationStatusIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPCheckNotificationStatusIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPCheckNotificationStatusIndication()
        frame.IsActive = packet.getParamValueAsNumber("IsActive")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPCheckIndicationStatusIndicationObserver(Observer):

    opGroup = Spec.GAPCheckIndicationStatusIndicationFrame.opGroup
    opCode = Spec.GAPCheckIndicationStatusIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPCheckIndicationStatusIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPCheckIndicationStatusIndication()
        frame.IsActive = packet.getParamValueAsNumber("IsActive")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPLoadKeysIndicationObserver(Observer):

    opGroup = Spec.GAPLoadKeysIndicationFrame.opGroup
    opCode = Spec.GAPLoadKeysIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GAPLoadKeysIndication()
        curr = 0
        frame.Keys_LtkIncluded = data.contents[curr]
        curr += 1
        frame.Keys_LtkInfo = []
        if frame.Keys_LtkIncluded:
            # Create sub-object container
            Keys_LtkInfo = GAPLoadKeysIndication.Keys_LtkInfo()
            Keys_LtkInfo.LtkSize = data.contents[curr]
            curr += 1
            Keys_LtkInfo.Ltk = list_to_int(data.contents[curr:curr + Keys_LtkInfo.LtkSize * 1])
            curr += Keys_LtkInfo.LtkSize * 1
            frame.Keys_LtkInfo = copy.deepcopy(Keys_LtkInfo)

        frame.Keys_IrkIncluded = data.contents[curr]
        curr += 1
        if frame.Keys_IrkIncluded:
            frame.Keys_Irk = data.contents[curr:curr + 16]
            curr += 16
        frame.Keys_CsrkIncluded = data.contents[curr]
        curr += 1
        if frame.Keys_CsrkIncluded:
            frame.Keys_Csrk = data.contents[curr:curr + 16]
            curr += 16
        frame.Keys_RandEdivInfo = []
        if frame.Keys_LtkIncluded:
            # Create sub-object container
            Keys_RandEdivInfo = GAPLoadKeysIndication.Keys_RandEdivInfo()
            Keys_RandEdivInfo.RandSize = data.contents[curr]
            curr += 1
            Keys_RandEdivInfo.Rand = list_to_int(data.contents[curr:curr + Keys_RandEdivInfo.RandSize * 1])
            curr += Keys_RandEdivInfo.RandSize * 1
            Keys_RandEdivInfo.Ediv = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.Keys_RandEdivInfo = copy.deepcopy(Keys_RandEdivInfo)

        if frame.Keys_IrkIncluded:
            frame.Keys_AddressIncluded = data.contents[curr]
            curr += 1
        frame.Keys_AddressInfo = []
        if frame.Keys_AddressIncluded:
            # Create sub-object container
            Keys_AddressInfo = GAPLoadKeysIndication.Keys_AddressInfo()
            Keys_AddressInfo.DeviceAddressType = data.contents[curr]
            curr += 1
            Keys_AddressInfo.DeviceAddress = list_to_int(data.contents[curr:curr + 6])
            curr += 6
            frame.Keys_AddressInfo = copy.deepcopy(Keys_AddressInfo)

        frame.KeyFlags = data.contents[curr]
        curr += 1
        frame.LeSc = data.contents[curr]
        curr += 1
        frame.Authenticated = data.contents[curr]
        curr += 1
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPLoadEncryptionInformationIndicationObserver(Observer):

    opGroup = Spec.GAPLoadEncryptionInformationIndicationFrame.opGroup
    opCode = Spec.GAPLoadEncryptionInformationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPLoadEncryptionInformationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPLoadEncryptionInformationIndication()
        frame.LtkSize = packet.getParamValueAsNumber("LtkSize")
        frame.Ltk = packet.getParamValueAsList("Ltk")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPLoadCustomPeerInformationIndicationObserver(Observer):

    opGroup = Spec.GAPLoadCustomPeerInformationIndicationFrame.opGroup
    opCode = Spec.GAPLoadCustomPeerInformationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPLoadCustomPeerInformationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPLoadCustomPeerInformationIndication()
        frame.InfoSize = packet.getParamValueAsNumber("InfoSize")
        frame.Info = packet.getParamValueAsList("Info")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPCheckIfBondedIndicationObserver(Observer):

    opGroup = Spec.GAPCheckIfBondedIndicationFrame.opGroup
    opCode = Spec.GAPCheckIfBondedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPCheckIfBondedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPCheckIfBondedIndication()
        frame.IsBonded = packet.getParamValueAsNumber("IsBonded")
        frame.NvmIndex = packet.getParamValueAsNumber("NvmIndex")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetBondedDevicesCountIndicationObserver(Observer):

    opGroup = Spec.GAPGetBondedDevicesCountIndicationFrame.opGroup
    opCode = Spec.GAPGetBondedDevicesCountIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetBondedDevicesCountIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetBondedDevicesCountIndication()
        frame.NbOfBondedDevices = packet.getParamValueAsNumber("NbOfBondedDevices")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetBondedDeviceNameIndicationObserver(Observer):

    opGroup = Spec.GAPGetBondedDeviceNameIndicationFrame.opGroup
    opCode = Spec.GAPGetBondedDeviceNameIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetBondedDeviceNameIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetBondedDeviceNameIndication()
        frame.NameSize = packet.getParamValueAsNumber("NameSize")
        frame.Name = packet.getParamValueAsList("Name")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventInitializationCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventInitializationCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventInitializationCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventInitializationCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventInitializationCompleteIndication()
        frame.initCompleteData_SupportedFeatures = packet.getParamValueAsNumber("initCompleteData_SupportedFeatures")
        frame.initCompleteData_MaxAdvDataSize = packet.getParamValueAsNumber("initCompleteData_MaxAdvDataSize")
        frame.initCompleteData_NumOfSupportedAdvSets = packet.getParamValueAsNumber("initCompleteData_NumOfSupportedAdvSets")
        frame.initCompleteData_PeriodicAdvListSize = packet.getParamValueAsNumber("initCompleteData_PeriodicAdvListSize")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventInternalErrorIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventInternalErrorIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventInternalErrorIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventInternalErrorIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventInternalErrorIndication()
        frame.InternalError_ErrorCode = packet.getParamValueAsNumber("InternalError_ErrorCode")
        frame.InternalError_ErrorSource = packet.getParamValueAsNumber("InternalError_ErrorSource")
        frame.InternalError_HciCommandOpcode = packet.getParamValueAsNumber("InternalError_HciCommandOpcode")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventAdvertisingSetupFailedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventAdvertisingSetupFailedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventAdvertisingSetupFailedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventAdvertisingSetupFailedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventAdvertisingSetupFailedIndication()
        frame.SetupFailReason = GAPGenericEventAdvertisingSetupFailedIndicationSetupFailReason.getEnumString(packet.getParamValueAsNumber("SetupFailReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventAdvertisingParametersSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventAdvertisingParametersSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventAdvertisingParametersSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventAdvertisingParametersSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventAdvertisingDataSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventAdvertisingDataSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventAdvertisingDataSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventAdvertisingDataSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventFilterAcceptListSizeReadIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventFilterAcceptListSizeReadIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventFilterAcceptListSizeReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventFilterAcceptListSizeReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventFilterAcceptListSizeReadIndication()
        frame.FilterAcceptListSize = packet.getParamValueAsNumber("FilterAcceptListSize")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventDeviceAddedToFilterAcceptListIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventDeviceAddedToFilterAcceptListIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventDeviceAddedToFilterAcceptListIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventDeviceAddedToFilterAcceptListIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventDeviceRemovedFromFilterAcceptListIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventDeviceRemovedFromFilterAcceptListIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventDeviceRemovedFromFilterAcceptListIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventDeviceRemovedFromFilterAcceptListIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventFilterAcceptListClearedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventFilterAcceptListClearedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventFilterAcceptListClearedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventFilterAcceptListClearedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventRandomAddressReadyIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventRandomAddressReadyIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventRandomAddressReadyIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventRandomAddressReadyIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventRandomAddressReadyIndication()
        frame.Address = packet.getParamValueAsList("Address")
        frame.Handle = packet.getParamValueAsNumber("Handle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventCreateConnectionCanceledIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventCreateConnectionCanceledIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventCreateConnectionCanceledIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventCreateConnectionCanceledIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPublicAddressReadIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPublicAddressReadIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPublicAddressReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventPublicAddressReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventPublicAddressReadIndication()
        frame.Address = packet.getParamValueAsList("Address")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventAdvTxPowerLevelReadIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventAdvTxPowerLevelReadIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventAdvTxPowerLevelReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventAdvTxPowerLevelReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventAdvTxPowerLevelReadIndication()
        frame.AdvTxPowerLevel = packet.getParamValueAsNumber("AdvTxPowerLevel")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPrivateResolvableAddressVerifiedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPrivateResolvableAddressVerifiedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPrivateResolvableAddressVerifiedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventPrivateResolvableAddressVerifiedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventPrivateResolvableAddressVerifiedIndication()
        frame.Verified = packet.getParamValueAsNumber("Verified")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventRandomAddressSetIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventRandomAddressSetIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventRandomAddressSetIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventRandomAddressSetIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventRandomAddressSetIndication()
        frame.Handle = packet.getParamValueAsNumber("Handle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPAdvertisingEventStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventCommandFailedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventCommandFailedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventCommandFailedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPAdvertisingEventCommandFailedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPAdvertisingEventCommandFailedIndication()
        frame.FailReason = GAPAdvertisingEventCommandFailedIndicationFailReason.getEnumString(packet.getParamValueAsNumber("FailReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPScanningEventStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventCommandFailedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventCommandFailedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventCommandFailedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventCommandFailedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventCommandFailedIndication()
        frame.FailReason = GAPScanningEventCommandFailedIndicationFailReason.getEnumString(packet.getParamValueAsNumber("FailReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventDeviceScannedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventDeviceScannedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventDeviceScannedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventDeviceScannedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventDeviceScannedIndication()
        frame.ScannedDevice_AddressType = packet.getParamValueAsNumber("ScannedDevice_AddressType")
        frame.ScannedDevice_Address = packet.getParamValueAsList("ScannedDevice_Address")
        frame.ScannedDevice_Rssi = packet.getParamValueAsNumber("ScannedDevice_Rssi")
        frame.ScannedDevice_DataLength = packet.getParamValueAsNumber("ScannedDevice_DataLength")
        frame.ScannedDevice_Data = packet.getParamValueAsList("ScannedDevice_Data")
        frame.ScannedDevice_AdvEventType = packet.getParamValueAsNumber("ScannedDevice_AdvEventType")
        frame.ScannedDevice_DirectRpaUsed = packet.getParamValueAsNumber("ScannedDevice_DirectRpaUsed")
        frame.ScannedDevice_DirectRpa = packet.getParamValueAsList("ScannedDevice_DirectRpa")
        frame.ScannedDevice_advertisingAddressResolved = packet.getParamValueAsNumber("ScannedDevice_advertisingAddressResolved")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventConnectedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventConnectedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventConnectedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventConnectedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventConnectedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ConnectionParameters_ConnInterval = packet.getParamValueAsNumber("ConnectionParameters_ConnInterval")
        frame.ConnectionParameters_ConnLatency = packet.getParamValueAsNumber("ConnectionParameters_ConnLatency")
        frame.ConnectionParameters_SupervisionTimeout = packet.getParamValueAsNumber("ConnectionParameters_SupervisionTimeout")
        frame.ConnectionParameters_CentralClockAccuracy = packet.getParamValueAsNumber("ConnectionParameters_CentralClockAccuracy")
        frame.PeerAddressType = packet.getParamValueAsNumber("PeerAddressType")
        frame.PeerAddress = packet.getParamValueAsList("PeerAddress")
        frame.peerRpaResolved = packet.getParamValueAsNumber("peerRpaResolved")
        frame.peerRpa = packet.getParamValueAsList("peerRpa")
        frame.localRpaUsed = packet.getParamValueAsNumber("localRpaUsed")
        frame.localRpa = packet.getParamValueAsList("localRpa")
        frame.connectionRole = packet.getParamValueAsNumber("connectionRole")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPairingRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPairingRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPairingRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPairingRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPairingRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.PairingParameters_WithBonding = packet.getParamValueAsNumber("PairingParameters_WithBonding")
        frame.PairingParameters_SecurityModeAndLevel = packet.getParamValueAsNumber("PairingParameters_SecurityModeAndLevel")
        frame.PairingParameters_MaxEncryptionKeySize = packet.getParamValueAsNumber("PairingParameters_MaxEncryptionKeySize")
        frame.PairingParameters_LocalIoCapabilities = packet.getParamValueAsNumber("PairingParameters_LocalIoCapabilities")
        frame.PairingParameters_OobAvailable = packet.getParamValueAsNumber("PairingParameters_OobAvailable")
        frame.PairingParameters_CentralKeys = packet.getParamValueAsNumber("PairingParameters_CentralKeys")
        frame.PairingParameters_PeripheralKeys = packet.getParamValueAsNumber("PairingParameters_PeripheralKeys")
        frame.PairingParameters_LeSecureConnectionSupported = packet.getParamValueAsNumber("PairingParameters_LeSecureConnectionSupported")
        frame.PairingParameters_UseKeypressNotifications = packet.getParamValueAsNumber("PairingParameters_UseKeypressNotifications")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPeripheralSecurityRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPeripheralSecurityRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPeripheralSecurityRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPeripheralSecurityRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPeripheralSecurityRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.PeripheralSecurityRequestParameters_BondAfterPairing = packet.getParamValueAsNumber("PeripheralSecurityRequestParameters_BondAfterPairing")
        frame.PeripheralSecurityRequestParameters_bAuthenticationRequired = packet.getParamValueAsNumber("PeripheralSecurityRequestParameters_bAuthenticationRequired")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPairingResponseIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPairingResponseIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPairingResponseIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPairingResponseIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPairingResponseIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.PairingParameters_WithBonding = packet.getParamValueAsNumber("PairingParameters_WithBonding")
        frame.PairingParameters_SecurityModeAndLevel = packet.getParamValueAsNumber("PairingParameters_SecurityModeAndLevel")
        frame.PairingParameters_MaxEncryptionKeySize = packet.getParamValueAsNumber("PairingParameters_MaxEncryptionKeySize")
        frame.PairingParameters_LocalIoCapabilities = packet.getParamValueAsNumber("PairingParameters_LocalIoCapabilities")
        frame.PairingParameters_OobAvailable = packet.getParamValueAsNumber("PairingParameters_OobAvailable")
        frame.PairingParameters_CentralKeys = packet.getParamValueAsNumber("PairingParameters_CentralKeys")
        frame.PairingParameters_PeripheralKeys = packet.getParamValueAsNumber("PairingParameters_PeripheralKeys")
        frame.PairingParameters_LeSecureConnectionSupported = packet.getParamValueAsNumber("PairingParameters_LeSecureConnectionSupported")
        frame.PairingParameters_UseKeypressNotifications = packet.getParamValueAsNumber("PairingParameters_UseKeypressNotifications")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventAuthenticationRejectedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventAuthenticationRejectedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventAuthenticationRejectedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventAuthenticationRejectedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventAuthenticationRejectedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.RejectReason = GAPConnectionEventAuthenticationRejectedIndicationRejectReason.getEnumString(packet.getParamValueAsNumber("RejectReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPasskeyRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPasskeyRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPasskeyRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPasskeyRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPasskeyRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventOobRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventOobRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventOobRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventOobRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventOobRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPasskeyDisplayIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPasskeyDisplayIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPasskeyDisplayIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPasskeyDisplayIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPasskeyDisplayIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.PasskeyForDisplay = packet.getParamValueAsNumber("PasskeyForDisplay")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventKeyExchangeRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventKeyExchangeRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventKeyExchangeRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventKeyExchangeRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventKeyExchangeRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.RequestedKeys = packet.getParamValueAsNumber("RequestedKeys")
        frame.RequestedLtkSize = packet.getParamValueAsNumber("RequestedLtkSize")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventKeysReceivedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventKeysReceivedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventKeysReceivedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GAPConnectionEventKeysReceivedIndication()
        curr = 0
        frame.DeviceId = data.contents[curr]
        curr += 1
        frame.Keys_LtkIncluded = data.contents[curr]
        curr += 1
        frame.Keys_LtkInfo = []
        if frame.Keys_LtkIncluded:
            # Create sub-object container
            Keys_LtkInfo = GAPConnectionEventKeysReceivedIndication.Keys_LtkInfo()
            Keys_LtkInfo.LtkSize = data.contents[curr]
            curr += 1
            Keys_LtkInfo.Ltk = list_to_int(data.contents[curr:curr + Keys_LtkInfo.LtkSize * 1])
            curr += Keys_LtkInfo.LtkSize * 1
            frame.Keys_LtkInfo = copy.deepcopy(Keys_LtkInfo)

        frame.Keys_IrkIncluded = data.contents[curr]
        curr += 1
        if frame.Keys_IrkIncluded:
            frame.Keys_Irk = data.contents[curr:curr + 16]
            curr += 16
        frame.Keys_CsrkIncluded = data.contents[curr]
        curr += 1
        if frame.Keys_CsrkIncluded:
            frame.Keys_Csrk = data.contents[curr:curr + 16]
            curr += 16
        frame.Keys_RandEdivInfo = []
        if frame.Keys_LtkIncluded:
            # Create sub-object container
            Keys_RandEdivInfo = GAPConnectionEventKeysReceivedIndication.Keys_RandEdivInfo()
            Keys_RandEdivInfo.RandSize = data.contents[curr]
            curr += 1
            Keys_RandEdivInfo.Rand = list_to_int(data.contents[curr:curr + Keys_RandEdivInfo.RandSize * 1])
            curr += Keys_RandEdivInfo.RandSize * 1
            Keys_RandEdivInfo.Ediv = list_to_int(data.contents[curr:curr + 2])
            curr += 2
            frame.Keys_RandEdivInfo = copy.deepcopy(Keys_RandEdivInfo)

        if frame.Keys_IrkIncluded:
            frame.Keys_AddressIncluded = data.contents[curr]
            curr += 1
        frame.Keys_AddressInfo = []
        if frame.Keys_AddressIncluded:
            # Create sub-object container
            Keys_AddressInfo = GAPConnectionEventKeysReceivedIndication.Keys_AddressInfo()
            Keys_AddressInfo.DeviceAddressType = data.contents[curr]
            curr += 1
            Keys_AddressInfo.DeviceAddress = list_to_int(data.contents[curr:curr + 6])
            curr += 6
            frame.Keys_AddressInfo = copy.deepcopy(Keys_AddressInfo)

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventLongTermKeyRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventLongTermKeyRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventLongTermKeyRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventLongTermKeyRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventLongTermKeyRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Ediv = packet.getParamValueAsNumber("Ediv")
        frame.RandSize = packet.getParamValueAsNumber("RandSize")
        frame.Rand = packet.getParamValueAsList("Rand")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEncryptionChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEncryptionChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEncryptionChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEncryptionChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEncryptionChangedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.NewEncryptionState = packet.getParamValueAsNumber("NewEncryptionState")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPairingCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPairingCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPairingCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPairingCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPairingCompleteIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.PairingStatus = GAPConnectionEventPairingCompleteIndicationPairingStatus.getEnumString(packet.getParamValueAsNumber("PairingStatus"))
        frame.PairingData = packet.getParamValueAsNumber("PairingData")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventDisconnectedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventDisconnectedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventDisconnectedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventDisconnectedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventDisconnectedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Reason = GAPConnectionEventDisconnectedIndicationReason.getEnumString(packet.getParamValueAsNumber("Reason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventRssiReadIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventRssiReadIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventRssiReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventRssiReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventRssiReadIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Rssi = packet.getParamValueAsNumber("Rssi")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventTxPowerLevelReadIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventTxPowerLevelReadIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventTxPowerLevelReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventTxPowerLevelReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventTxPowerLevelReadIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.TxPowerLevel = packet.getParamValueAsNumber("TxPowerLevel")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPowerReadFailureIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPowerReadFailureIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPowerReadFailureIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPowerReadFailureIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPowerReadFailureIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.FailReason = GAPConnectionEventPowerReadFailureIndicationFailReason.getEnumString(packet.getParamValueAsNumber("FailReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventParameterUpdateRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventParameterUpdateRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventParameterUpdateRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventParameterUpdateRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventParameterUpdateRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ConnectionParameterUpdateRequest_IntervalMin = packet.getParamValueAsNumber("ConnectionParameterUpdateRequest_IntervalMin")
        frame.ConnectionParameterUpdateRequest_IntervalMax = packet.getParamValueAsNumber("ConnectionParameterUpdateRequest_IntervalMax")
        frame.ConnectionParameterUpdateRequest_PeripheralLatency = packet.getParamValueAsNumber("ConnectionParameterUpdateRequest_PeripheralLatency")
        frame.ConnectionParameterUpdateRequest_TimeoutMultiplier = packet.getParamValueAsNumber("ConnectionParameterUpdateRequest_TimeoutMultiplier")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventParameterUpdateCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventParameterUpdateCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventParameterUpdateCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventParameterUpdateCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventParameterUpdateCompleteIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ConnectionParameterUpdateComplete_Status = GAPConnectionEventParameterUpdateCompleteIndicationConnectionParameterUpdateComplete_Status.getEnumString(packet.getParamValueAsNumber("ConnectionParameterUpdateComplete_Status"))
        frame.ConnectionParameterUpdateComplete_ConnInterval = packet.getParamValueAsNumber("ConnectionParameterUpdateComplete_ConnInterval")
        frame.ConnectionParameterUpdateComplete_ConnLatency = packet.getParamValueAsNumber("ConnectionParameterUpdateComplete_ConnLatency")
        frame.ConnectionParameterUpdateComplete_SupervisionTimeout = packet.getParamValueAsNumber("ConnectionParameterUpdateComplete_SupervisionTimeout")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventLeDataLengthChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventLeDataLengthChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventLeDataLengthChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventLeDataLengthChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventLeDataLengthChangedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.LeDataLengthChanged_MaxTxOctets = packet.getParamValueAsNumber("LeDataLengthChanged_MaxTxOctets")
        frame.LeDataLengthChanged_MaxTxTime = packet.getParamValueAsNumber("LeDataLengthChanged_MaxTxTime")
        frame.LeDataLengthChanged_MaxRxOctets = packet.getParamValueAsNumber("LeDataLengthChanged_MaxRxOctets")
        frame.LeDataLengthChanged_MaxRxTime = packet.getParamValueAsNumber("LeDataLengthChanged_MaxRxTime")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventLeScOobDataRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventLeScOobDataRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventLeScOobDataRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventLeScOobDataRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventLeScOobDataRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventLeScDisplayNumericValueIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventLeScDisplayNumericValueIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventLeScDisplayNumericValueIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventLeScDisplayNumericValueIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventLeScDisplayNumericValueIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ncValue = packet.getParamValueAsNumber("ncValue")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventLeScKeypressNotificationIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventLeScKeypressNotificationIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventLeScKeypressNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventLeScKeypressNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventLeScKeypressNotificationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.GapLeScKeypressNotificationParams_keypressNotifType = packet.getParamValueAsNumber("GapLeScKeypressNotificationParams_keypressNotifType")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPLeScPublicKeyRegeneratedIndicationObserver(Observer):

    opGroup = Spec.GAPLeScPublicKeyRegeneratedIndicationFrame.opGroup
    opCode = Spec.GAPLeScPublicKeyRegeneratedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPLeScPublicKeyRegeneratedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventLeScLocalOobDataIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventLeScLocalOobDataIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventLeScLocalOobDataIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventLeScLocalOobDataIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventLeScLocalOobDataIndication()
        frame.RandomValue = packet.getParamValueAsList("RandomValue")
        frame.ConfirmValue = packet.getParamValueAsList("ConfirmValue")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventHostPrivacyStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventHostPrivacyStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventHostPrivacyStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventHostPrivacyStateChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventHostPrivacyStateChangedIndication()
        frame.NewHostPrivacyState = packet.getParamValueAsNumber("NewHostPrivacyState")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventControllerPrivacyStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventControllerPrivacyStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventControllerPrivacyStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventControllerPrivacyStateChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventControllerPrivacyStateChangedIndication()
        frame.NewControllerPrivacyState = packet.getParamValueAsNumber("NewControllerPrivacyState")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventTxPowerLevelSetCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventTxPowerLevelSetCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventTxPowerLevelSetCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventTxPowerLevelSetCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventTxPowerLevelSetCompleteIndication()
        frame.status = packet.getParamValueAsNumber("status")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventLePhyEventIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventLePhyEventIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventLePhyEventIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventLePhyEventIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventLePhyEventIndication()
        frame.eventType = packet.getParamValueAsNumber("eventType")
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.txPhy = packet.getParamValueAsNumber("txPhy")
        frame.rxPhy = packet.getParamValueAsNumber("rxPhy")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetBondedDevicesIdentityInformationIndicationObserver(Observer):

    opGroup = Spec.GAPGetBondedDevicesIdentityInformationIndicationFrame.opGroup
    opCode = Spec.GAPGetBondedDevicesIdentityInformationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        # Create frame object
        frame = GAPGetBondedDevicesIdentityInformationIndication()
        curr = 0
        frame.NbOfDeviceIdentityAddresses = data.contents[curr]
        curr += 1
        frame.IdentityAddresses = []
        for _ in range(frame.NbOfDeviceIdentityAddresses):
            # Create sub-object container
            IdentityAddresses = GAPGetBondedDevicesIdentityInformationIndication.IdentityAddresses()
            IdentityAddresses.IdentityAddressType = data.contents[curr]
            curr += 1
            IdentityAddresses.IdentityAddress = list_to_int(data.contents[curr:curr + 6])
            curr += 6
            IdentityAddresses.Irk = list_to_int(data.contents[curr:curr + 16])
            curr += 16
            IdentityAddresses.PrivacyMode = data.contents[curr]
            curr += 1
            # Add sub-object to list container.
            frame.IdentityAddresses.append(copy.deepcopy(IdentityAddresses))

        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPControllerNotificationIndicationObserver(Observer):

    opGroup = Spec.GAPControllerNotificationIndicationFrame.opGroup
    opCode = Spec.GAPControllerNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPControllerNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPControllerNotificationIndication()
        frame.EventType = packet.getParamValueAsNumber("EventType")
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.RSSI = packet.getParamValueAsNumber("RSSI")
        frame.Channel = packet.getParamValueAsNumber("Channel")
        frame.ConnEvCounter = packet.getParamValueAsNumber("ConnEvCounter")
        #frame.Status = GAPControllerNotificationIndicationStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        frame.Status = packet.getParamValueAsNumber("Status")
        frame.Timestamp = packet.getParamValueAsNumber("Timestamp")
        frame.AdvHandle = packet.getParamValueAsNumber("AdvHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPBondCreatedIndicationObserver(Observer):

    opGroup = Spec.GAPBondCreatedIndicationFrame.opGroup
    opCode = Spec.GAPBondCreatedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPBondCreatedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPBondCreatedIndication()
        frame.NvmIndex = packet.getParamValueAsNumber("NvmIndex")
        frame.AddrType = packet.getParamValueAsNumber("AddrType")
        frame.Addr = packet.getParamValueAsList("Addr")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventChannelMapSetIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventChannelMapSetIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventChannelMapSetIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventChannelMapSetIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventChannelMapReadIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventChannelMapReadIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventChannelMapReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventChannelMapReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventChannelMapReadIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.ChannelMap = packet.getParamValueAsList("ChannelMap")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventChannelMapReadFailureIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventChannelMapReadFailureIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventChannelMapReadFailureIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventChannelMapReadFailureIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventChannelMapReadFailureIndication()
        frame.FailReason = GAPConnectionEventChannelMapReadFailureIndicationFailReason.getEnumString(packet.getParamValueAsNumber("FailReason"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventExtAdvertisingParamSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventExtAdvertisingParamSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventExtAdvertisingParamSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventExtAdvertisingParamSetupCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventExtAdvertisingParamSetupCompleteIndication()
        frame.SelectedTxPower = packet.getParamValueAsNumber("SelectedTxPower")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventExtAdvertisingDataSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventExtAdvertisingDataSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventExtAdvertisingDataSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventExtAdvertisingDataSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvParamSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvParamSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvParamSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvParamSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvDataSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvDataSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvDataSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvDataSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvListUpdateCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvListUpdateCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvListUpdateCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvListUpdateCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventExtAdvertisingStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventExtAdvertisingStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventExtAdvertisingStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPAdvertisingEventExtAdvertisingStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventAdvertisingSetTerminatedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventAdvertisingSetTerminatedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventAdvertisingSetTerminatedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPAdvertisingEventAdvertisingSetTerminatedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPAdvertisingEventAdvertisingSetTerminatedIndication()
        frame.Status = GAPAdvertisingEventAdvertisingSetTerminatedIndicationStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        frame.Handle = packet.getParamValueAsNumber("Handle")
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.NbExtAdvEvents = packet.getParamValueAsNumber("NbExtAdvEvents")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPAdvertisingEventExtScanReqReceivedIndicationObserver(Observer):

    opGroup = Spec.GAPAdvertisingEventExtScanReqReceivedIndicationFrame.opGroup
    opCode = Spec.GAPAdvertisingEventExtScanReqReceivedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPAdvertisingEventExtScanReqReceivedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPAdvertisingEventExtScanReqReceivedIndication()
        frame.Handle = packet.getParamValueAsNumber("Handle")
        frame.ScannerAddressType = packet.getParamValueAsNumber("ScannerAddressType")
        frame.ScannerAddress = packet.getParamValueAsList("ScannerAddress")
        frame.ScannerAddressResolved = packet.getParamValueAsNumber("ScannerAddressResolved")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvertisingStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvertisingStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvertisingStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvertisingStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventExtDeviceScannedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventExtDeviceScannedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventExtDeviceScannedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventExtDeviceScannedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventExtDeviceScannedIndication()
        frame.AddressType = packet.getParamValueAsNumber("AddressType")
        frame.Address = packet.getParamValueAsList("Address")
        frame.SID = packet.getParamValueAsNumber("SID")
        frame.AdvertisingAddressResolved = packet.getParamValueAsNumber("AdvertisingAddressResolved")
        frame.AdvEventProperties = packet.getParamValueAsNumber("AdvEventProperties")
        frame.Rssi = packet.getParamValueAsNumber("Rssi")
        frame.TxPower = packet.getParamValueAsNumber("TxPower")
        frame.PrimaryPHY = packet.getParamValueAsNumber("PrimaryPHY")
        frame.SecondaryPHY = packet.getParamValueAsNumber("SecondaryPHY")
        frame.PeriodicAdvInterval = packet.getParamValueAsNumber("PeriodicAdvInterval")
        frame.DirectRpaUsed = packet.getParamValueAsNumber("DirectRpaUsed")
        frame.DirectRpaType = packet.getParamValueAsNumber("DirectRpaType")
        frame.DirectRpa = packet.getParamValueAsList("DirectRpa")
        frame.DataLength = packet.getParamValueAsNumber("DataLength")
        frame.Data = packet.getParamValueAsList("Data")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventPeriodicAdvSyncEstablishedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventPeriodicAdvSyncEstablishedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventPeriodicAdvSyncEstablishedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventPeriodicAdvSyncEstablishedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventPeriodicAdvSyncEstablishedIndication()
        frame.Status = GAPScanningEventPeriodicAdvSyncEstablishedIndicationStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        frame.SyncHandle = packet.getParamValueAsNumber("SyncHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventPeriodicAdvSyncTerminatedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventPeriodicAdvSyncTerminatedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventPeriodicAdvSyncTerminatedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPScanningEventPeriodicAdvSyncTerminatedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventPeriodicAdvSyncLostIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventPeriodicAdvSyncLostIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventPeriodicAdvSyncLostIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventPeriodicAdvSyncLostIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventPeriodicAdvSyncLostIndication()
        frame.SyncHandle = packet.getParamValueAsNumber("SyncHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventPeriodicDeviceScannedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventPeriodicDeviceScannedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventPeriodicDeviceScannedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventPeriodicDeviceScannedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventPeriodicDeviceScannedIndication()
        frame.SyncHandle = packet.getParamValueAsNumber("SyncHandle")
        frame.Rssi = packet.getParamValueAsNumber("Rssi")
        frame.TxPower = packet.getParamValueAsNumber("TxPower")
        frame.DataLength = packet.getParamValueAsNumber("DataLength")
        frame.Data = packet.getParamValueAsList("Data")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvCreateSyncCancelledIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvCreateSyncCancelledIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvCreateSyncCancelledIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvCreateSyncCancelledIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventChannelSelectionAlgorithm2IndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventChannelSelectionAlgorithm2IndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventChannelSelectionAlgorithm2IndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventChannelSelectionAlgorithm2IndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventChannelSelectionAlgorithm2Indication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventTxEntryAvailableIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventTxEntryAvailableIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventTxEntryAvailableIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventTxEntryAvailableIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventTxEntryAvailableIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventControllerLocalRPAReadIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventControllerLocalRPAReadIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventControllerLocalRPAReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventControllerLocalRPAReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventControllerLocalRPAReadIndication()
        frame.Address = packet.getParamValueAsList("Address")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPCheckNvmIndexIndicationObserver(Observer):

    opGroup = Spec.GAPCheckNvmIndexIndicationFrame.opGroup
    opCode = Spec.GAPCheckNvmIndexIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPCheckNvmIndexIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPCheckNvmIndexIndication()
        frame.IsFree = packet.getParamValueAsNumber("IsFree")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetDeviceIdFromConnHandleIndicationObserver(Observer):

    opGroup = Spec.GAPGetDeviceIdFromConnHandleIndicationFrame.opGroup
    opCode = Spec.GAPGetDeviceIdFromConnHandleIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetDeviceIdFromConnHandleIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetDeviceIdFromConnHandleIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetConnectionHandleFromDeviceIdIndicationObserver(Observer):

    opGroup = Spec.GAPGetConnectionHandleFromDeviceIdIndicationFrame.opGroup
    opCode = Spec.GAPGetConnectionHandleFromDeviceIdIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetConnectionHandleFromDeviceIdIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetConnectionHandleFromDeviceIdIndication()
        frame.ConnectionHandle = packet.getParamValueAsNumber("ConnectionHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPPairingEventNoLTKIndicationObserver(Observer):

    opGroup = Spec.GAPPairingEventNoLTKIndicationFrame.opGroup
    opCode = Spec.GAPPairingEventNoLTKIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPPairingEventNoLTKIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPPairingEventNoLTKIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPPairingAlreadyStartedIndicationObserver(Observer):

    opGroup = Spec.GAPPairingAlreadyStartedIndicationFrame.opGroup
    opCode = Spec.GAPPairingAlreadyStartedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPPairingAlreadyStartedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPPairingAlreadyStartedIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventConnectionlessCteTransmitStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventConnectionlessCteTransmitStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventConnectionlessCteTransmitStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPGenericEventConnectionlessCteTransmitStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventConnectionlessIqSamplingStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventConnectionlessIqSamplingStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventConnectionlessIqSamplingStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventConnectionlessIqSamplingStateChangedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventConnectionlessIqSamplingStateChangedIndication()
        frame.SyncHandle = packet.getParamValueAsNumber("SyncHandle")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventAntennaInformationReadIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventAntennaInformationReadIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventAntennaInformationReadIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventAntennaInformationReadIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventAntennaInformationReadIndication()
        frame.AntennaInformation_SupportedSwitchingSamplingRates.Value0x01 = packet.getParamValueAsNumber("AntennaInformation_SupportedSwitchingSamplingRatesValue0x01")
        frame.AntennaInformation_SupportedSwitchingSamplingRates.Value0x02 = packet.getParamValueAsNumber("AntennaInformation_SupportedSwitchingSamplingRatesValue0x02")
        frame.AntennaInformation_SupportedSwitchingSamplingRates.Value0x04 = packet.getParamValueAsNumber("AntennaInformation_SupportedSwitchingSamplingRatesValue0x04")
        frame.AntennaInformation_NumAntennae = packet.getParamValueAsNumber("AntennaInformation_NumAntennae")
        frame.AntennaInformation_MaxSwitchingPatternLength = packet.getParamValueAsNumber("AntennaInformation_MaxSwitchingPatternLength")
        frame.AntennaInformation_MaxCteLength = packet.getParamValueAsNumber("AntennaInformation_MaxCteLength")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventConnectionlessIqReportReceivedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventConnectionlessIqReportReceivedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventConnectionlessIqReportReceivedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventConnectionlessIqReportReceivedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventConnectionlessIqReportReceivedIndication()
        frame.IqReport_SyncHandle = packet.getParamValueAsNumber("IqReport_SyncHandle")
        frame.IqReport_ChannelIndex = packet.getParamValueAsNumber("IqReport_ChannelIndex")
        frame.IqReport_Rssi = packet.getParamValueAsNumber("IqReport_Rssi")
        frame.IqReport_RssiAntennaId = packet.getParamValueAsNumber("IqReport_RssiAntennaId")
        frame.IqReport_CteType = packet.getParamValueAsNumber("IqReport_CteType")
        frame.IqReport_SlotDurations = packet.getParamValueAsNumber("IqReport_SlotDurations")
        frame.IqReport_PacketStatus = GAPScanningEventConnectionlessIqReportReceivedIndicationIqReport_PacketStatus.getEnumString(packet.getParamValueAsNumber("IqReport_PacketStatus"))
        frame.IqReport_PeriodicEventCounter = packet.getParamValueAsNumber("IqReport_PeriodicEventCounter")
        frame.IqReport_sampleCount = packet.getParamValueAsNumber("IqReport_sampleCount")
        frame.IqReport_I_samples = packet.getParamValueAsList("IqReport_I_samples")
        frame.IqReport_Q_samples = packet.getParamValueAsList("IqReport_Q_samples")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventIqReportReceivedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventIqReportReceivedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventIqReportReceivedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventIqReportReceivedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventIqReportReceivedIndication()
        frame.ConnIqReport_RxPhy = packet.getParamValueAsNumber("ConnIqReport_RxPhy")
        frame.ConnIqReport_DataChannelIndex = packet.getParamValueAsNumber("ConnIqReport_DataChannelIndex")
        frame.ConnIqReport_Rssi = packet.getParamValueAsNumber("ConnIqReport_Rssi")
        frame.ConnIqReport_RssiAntennaId = packet.getParamValueAsNumber("ConnIqReport_RssiAntennaId")
        frame.ConnIqReport_CteType = packet.getParamValueAsNumber("ConnIqReport_CteType")
        frame.ConnIqReport_SlotDurations = packet.getParamValueAsNumber("ConnIqReport_SlotDurations")
        frame.ConnIqReport_PacketStatus = GAPConnectionEventIqReportReceivedIndicationConnIqReport_PacketStatus.getEnumString(packet.getParamValueAsNumber("ConnIqReport_PacketStatus"))
        frame.ConnIqReport_ConnEventCounter = packet.getParamValueAsNumber("ConnIqReport_ConnEventCounter")
        frame.ConnIqReport_sampleCount = packet.getParamValueAsNumber("ConnIqReport_sampleCount")
        frame.ConnIqReport_I_samples = packet.getParamValueAsList("ConnIqReport_I_samples")
        frame.ConnIqReport_Q_samples = packet.getParamValueAsList("ConnIqReport_Q_samples")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventCteRequestFailedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventCteRequestFailedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventCteRequestFailedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventCteRequestFailedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventCteRequestFailedIndication()
        frame.CteRequestFailedEvent_Status = GAPConnectionEventCteRequestFailedIndicationCteRequestFailedEvent_Status.getEnumString(packet.getParamValueAsNumber("CteRequestFailedEvent_Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventCteReceiveParamsSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventCteReceiveParamsSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventCteReceiveParamsSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventCteReceiveParamsSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventCteTransmitParamsSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventCteTransmitParamsSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventCteTransmitParamsSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventCteTransmitParamsSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventCteReqStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventCteReqStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventCteReqStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventCteReqStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventCteRspStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventCteRspStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventCteRspStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventCteRspStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvRecvEnableCompleteIndication()
        frame.PerAdvSyncTransferEnable = packet.getParamValueAsNumber("PerAdvSyncTransferEnable")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvSyncTransferCompleteIndication()
        frame.PerAdvSyncTransfer_DeviceId = packet.getParamValueAsNumber("PerAdvSyncTransfer_DeviceId")
        frame.PerAdvSyncTransfer_Status = GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationPerAdvSyncTransfer_Status.getEnumString(packet.getParamValueAsNumber("PerAdvSyncTransfer_Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndication()
        frame.PerAdvSetInfoTransfer_DeviceId = packet.getParamValueAsNumber("PerAdvSetInfoTransfer_DeviceId")
        frame.PerAdvSetInfoTransfer_Status = GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationPerAdvSetInfoTransfer_Status.getEnumString(packet.getParamValueAsNumber("PerAdvSetInfoTransfer_Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndication()
        frame.PerAdvSetSyncTransferParams_DeviceId = packet.getParamValueAsNumber("PerAdvSetSyncTransferParams_DeviceId")
        frame.PerAdvSetSyncTransferParams_Status = GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationPerAdvSetSyncTransferParams_Status.getEnumString(packet.getParamValueAsNumber("PerAdvSetSyncTransferParams_Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndication()
        frame.PerAdvSetDefaultPerAdvSyncTransferParams = packet.getParamValueAsNumber("PerAdvSetDefaultPerAdvSyncTransferParams")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationObserver(Observer):

    opGroup = Spec.GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationFrame.opGroup
    opCode = Spec.GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPScanningEventPeriodicAdvSyncTransferReceivedIndication()
        frame.PerAdvSyncTransferReceived_Status = GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationPerAdvSyncTransferReceived_Status.getEnumString(packet.getParamValueAsNumber("PerAdvSyncTransferReceived_Status"))
        frame.PerAdvSyncTransferReceived_DeviceId = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_DeviceId")
        frame.PerAdvSyncTransferReceived_ServiceData = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_ServiceData")
        frame.PerAdvSyncTransferReceived_SyncHandle = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_SyncHandle")
        frame.PerAdvSyncTransferReceived_AdvSID = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_AdvSID")
        frame.PerAdvSyncTransferReceived_AdvAddressType = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_AdvAddressType")
        frame.PerAdvSyncTransferReceived_AdvAddress = packet.getParamValueAsList("PerAdvSyncTransferReceived_AdvAddress")
        frame.PerAdvSyncTransferReceived_AdvPhy = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_AdvPhy")
        frame.PerAdvSyncTransferReceived_PeriodicAdvInt = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_PeriodicAdvInt")
        frame.PerAdvSyncTransferReceived_AdvClockAccuracy = packet.getParamValueAsNumber("PerAdvSyncTransferReceived_AdvClockAccuracy")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPathLossThresholdIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPathLossThresholdIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPathLossThresholdIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventPathLossThresholdIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventPathLossThresholdIndication()
        frame.PathLossThreshold_CurrentPathLoss = packet.getParamValueAsNumber("PathLossThreshold_CurrentPathLoss")
        frame.PathLossThreshold_ZoneEntered = packet.getParamValueAsNumber("PathLossThreshold_ZoneEntered")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventTransmitPowerReportingIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventTransmitPowerReportingIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventTransmitPowerReportingIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventTransmitPowerReportingIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventTransmitPowerReportingIndication()
        frame.TransmitPowerReporting_Reason = GAPConnectionEventTransmitPowerReportingIndicationTransmitPowerReporting_Reason.getEnumString(packet.getParamValueAsNumber("TransmitPowerReporting_Reason"))
        frame.TransmitPowerReporting_Phy = packet.getParamValueAsNumber("TransmitPowerReporting_Phy")
        frame.TransmitPowerReporting_TxPowerLevel = packet.getParamValueAsNumber("TransmitPowerReporting_TxPowerLevel")
        frame.TransmitPowerReporting_Flags.Value0x01 = packet.getParamValueAsNumber("TransmitPowerReporting_FlagsValue0x01")
        frame.TransmitPowerReporting_Flags.Value0x02 = packet.getParamValueAsNumber("TransmitPowerReporting_FlagsValue0x02")
        frame.TransmitPowerReporting_Delta = packet.getParamValueAsNumber("TransmitPowerReporting_Delta")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEnhancedReadTransmitPowerLevelIndication()
        frame.TransmitPowerInfo_Phy = packet.getParamValueAsNumber("TransmitPowerInfo_Phy")
        frame.TransmitPowerInfo_CurrTxPowerLevel = packet.getParamValueAsNumber("TransmitPowerInfo_CurrTxPowerLevel")
        frame.TransmitPowerInfo_MaxTxPowerLevel = packet.getParamValueAsNumber("TransmitPowerInfo_MaxTxPowerLevel")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPathLossReportingParamsSetupCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPathLossReportingParamsSetupCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPathLossReportingParamsSetupCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventPathLossReportingParamsSetupCompleteIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventPathLossReportingStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventPathLossReportingStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventPathLossReportingStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventPathLossReportingStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventTransmitPowerReportingStateChangedIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventTransmitPowerReportingStateChangedIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventTransmitPowerReportingStateChangedIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Create frame object
        frame = GAPConnectionEventTransmitPowerReportingStateChangedIndication()
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEattConnectionRequestIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEattConnectionRequestIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEattConnectionRequestIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEattConnectionRequestIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEattConnectionRequestIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.MTU = packet.getParamValueAsNumber("MTU")
        frame.NoOfBearers = packet.getParamValueAsNumber("NoOfBearers")
        frame.InitialCredits = packet.getParamValueAsNumber("InitialCredits")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEattConnectionCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEattConnectionCompleteIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEattConnectionCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEattConnectionCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEattConnectionCompleteIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Status = packet.getParamValueAsNumber("Status")
        frame.MTU = packet.getParamValueAsNumber("MTU")
        frame.NoOfBearers = packet.getParamValueAsNumber("NoOfBearers")
        frame.BearerIDs = packet.getParamValueAsList("BearerIDs")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEattReconfigureResponseIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEattReconfigureResponseIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEattReconfigureResponseIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEattReconfigureResponseIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEattReconfigureResponseIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.Status = packet.getParamValueAsNumber("Status")
        frame.LocalMtu = packet.getParamValueAsNumber("LocalMtu")
        frame.NoOfBearers = packet.getParamValueAsNumber("NoOfBearers")
        frame.BearerIDs = packet.getParamValueAsList("BearerIDs")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPConnectionEventEattBearerStatusNotificationIndicationObserver(Observer):

    opGroup = Spec.GAPConnectionEventEattBearerStatusNotificationIndicationFrame.opGroup
    opCode = Spec.GAPConnectionEventEattBearerStatusNotificationIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPConnectionEventEattBearerStatusNotificationIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPConnectionEventEattBearerStatusNotificationIndication()
        frame.DeviceId = packet.getParamValueAsNumber("DeviceId")
        frame.BearerId = packet.getParamValueAsNumber("BearerId")
        frame.Status = GAPConnectionEventEattBearerStatusNotificationIndicationStatus.getEnumString(packet.getParamValueAsNumber("Status"))
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGenericEventLeGenerateDhKeyCompleteIndicationObserver(Observer):

    opGroup = Spec.GAPGenericEventLeGenerateDhKeyCompleteIndicationFrame.opGroup
    opCode = Spec.GAPGenericEventLeGenerateDhKeyCompleteIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGenericEventLeGenerateDhKeyCompleteIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGenericEventLeGenerateDhKeyCompleteIndication()
        frame.DHKey = packet.getParamValueAsList("DHKey")
        framer.event_queue.put(frame) if sync_request else None

        if callback is not None:
            callback(self.deviceName, frame)
        else:
            print_event(self.deviceName, frame)
        fsciLibrary.DestroyFSCIFrame(event)


class GAPGetHostVersionIndicationObserver(Observer):

    opGroup = Spec.GAPGetHostVersionIndicationFrame.opGroup
    opCode = Spec.GAPGetHostVersionIndicationFrame.opCode

    @overrides(Observer)
    def observeEvent(self, framer, event, callback, sync_request):
        # Call super, print common information
        Observer.observeEvent(self, framer, event, callback, sync_request)
        # Get payload
        fsciFrame = cast(event, POINTER(FsciFrame))
        data = cast(fsciFrame.contents.data, POINTER(fsciFrame.contents.length * c_uint8))
        packet = Spec.GAPGetHostVersionIndicationFrame.getFsciPacketFromByteArray(data.contents, fsciFrame.contents.length)
        # Create frame object
        frame = GAPGetHostVersionIndication()
        frame.GapHostVersion_BleHostVerMajor = packet.getParamValueAsNumber("GapHostVersion_BleHostVerMajor")
        frame.GapHostVersion_BleHostVerMinor = packet.getParamValueAsNumber("GapHostVersion_BleHostVerMinor")
        frame.GapHostVersion_BleHostVerPatch = packet.getParamValueAsNumber("GapHostVersion_BleHostVerPatch")
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

