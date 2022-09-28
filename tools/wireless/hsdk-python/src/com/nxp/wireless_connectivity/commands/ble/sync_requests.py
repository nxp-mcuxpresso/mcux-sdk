'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.ble.enums import *  # @UnusedWildImport
import com.nxp.wireless_connectivity.commands.ble.frames as Frames
from com.nxp.wireless_connectivity.commands.ble.operations import *  # @UnusedWildImport

def L2CAPCBRegisterLeCbCallbacks(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBRegisterLeCbCallbacksRequest()
    return L2CAPCBRegisterLeCbCallbacksOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBRegisterLePsm(
    device,
    LePsm=bytearray(2),
    LePsmMtu=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBRegisterLePsmRequest(LePsm, LePsmMtu)
    return L2CAPCBRegisterLePsmOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBDeregisterLePsm(
    device,
    LePsm=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBDeregisterLePsmRequest(LePsm)
    return L2CAPCBDeregisterLePsmOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBConnectLePsm(
    device,
    LePsm=bytearray(2),
    DeviceId=bytearray(1),
    InitialCredits=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBConnectLePsmRequest(LePsm, DeviceId, InitialCredits)
    return L2CAPCBConnectLePsmOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBDisconnectLeCbChannel(
    device,
    DeviceId=bytearray(1),
    ChannelId=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBDisconnectLeCbChannelRequest(DeviceId, ChannelId)
    return L2CAPCBDisconnectLeCbChannelOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBCancelConnection(
    device,
    LePsm=bytearray(2),
    DeviceId=bytearray(1),
    RefuseReason=L2CAPCBCancelConnectionRequestRefuseReason.gSuccessful_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBCancelConnectionRequest(LePsm, DeviceId, RefuseReason)
    return L2CAPCBCancelConnectionOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBSendLeCbData(
    device,
    DeviceId=bytearray(1),
    ChannelId=bytearray(2),
    PacketLength=bytearray(2),
    # Array length depends on PacketLength. Mask: 0xFFFF. Shift: 0x0000.
    Packet=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBSendLeCbDataRequest(DeviceId, ChannelId, PacketLength, Packet)
    return L2CAPCBSendLeCbDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def L2CAPCBSendLeCredit(
    device,
    DeviceId=bytearray(1),
    ChannelId=bytearray(2),
    Credits=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBSendLeCreditRequest(DeviceId, ChannelId, Credits)
    return L2CAPCBSendLeCreditOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTInit(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTInitRequest()
    return GATTInitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTGetMtu(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTGetMtuRequest(DeviceId)
    return GATTGetMtuOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientInit(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientInitRequest()
    return GATTClientInitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientResetProcedure(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientResetProcedureRequest()
    return GATTClientResetProcedureOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientRegisterProcedureCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterProcedureCallbackRequest()
    return GATTClientRegisterProcedureCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientRegisterNotificationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterNotificationCallbackRequest()
    return GATTClientRegisterNotificationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientRegisterIndicationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterIndicationCallbackRequest()
    return GATTClientRegisterIndicationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientExchangeMtu(
    device,
    DeviceId=bytearray(1),
    Mtu=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientExchangeMtuRequest(DeviceId, Mtu)
    return GATTClientExchangeMtuOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientDiscoverAllPrimaryServices(
    device,
    DeviceId=bytearray(1),
    MaxNbOfServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientDiscoverAllPrimaryServicesRequest(DeviceId, MaxNbOfServices)
    return GATTClientDiscoverAllPrimaryServicesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientDiscoverPrimaryServicesByUuid(
    device,
    DeviceId=bytearray(1),
    UuidType=GATTClientDiscoverPrimaryServicesByUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    MaxNbOfServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientDiscoverPrimaryServicesByUuidRequest(DeviceId, UuidType, Uuid, MaxNbOfServices)
    return GATTClientDiscoverPrimaryServicesByUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientFindIncludedServices(
    device,
    DeviceId=bytearray(1),
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientFindIncludedServicesRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientFindIncludedServicesRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientFindIncludedServicesRequest.Service_IncludedServices(),
    MaxNbOfIncludedServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientFindIncludedServicesRequest(DeviceId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics,
                                                           Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfIncludedServices)
    return GATTClientFindIncludedServicesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientDiscoverAllCharacteristicsOfService(
    device,
    DeviceId=bytearray(1),
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientDiscoverAllCharacteristicsOfServiceRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientDiscoverAllCharacteristicsOfServiceRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientDiscoverAllCharacteristicsOfServiceRequest.Service_IncludedServices(),
    MaxNbOfCharacteristics=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientDiscoverAllCharacteristicsOfServiceRequest(DeviceId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid,
                                                                          Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
    return GATTClientDiscoverAllCharacteristicsOfServiceOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientDiscoverCharacteristicOfServiceByUuid(
    device,
    DeviceId=bytearray(1),
    UuidType=GATTClientDiscoverCharacteristicOfServiceByUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientDiscoverCharacteristicOfServiceByUuidRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientDiscoverCharacteristicOfServiceByUuidRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientDiscoverCharacteristicOfServiceByUuidRequest.Service_IncludedServices(),
    MaxNbOfCharacteristics=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientDiscoverCharacteristicOfServiceByUuidRequest(DeviceId, UuidType, Uuid, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid,
                                                                            Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
    return GATTClientDiscoverCharacteristicOfServiceByUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientDiscoverAllCharacteristicDescriptors(
    device,
    DeviceId=bytearray(1),
    Characteristic_Properties=GATTClientDiscoverAllCharacteristicDescriptorsRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientDiscoverAllCharacteristicDescriptorsRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientDiscoverAllCharacteristicDescriptorsRequest.Characteristic_Descriptors(),
    EndingHandle=bytearray(2),
    MaxNbOfDescriptors=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientDiscoverAllCharacteristicDescriptorsRequest(DeviceId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, EndingHandle, MaxNbOfDescriptors)
    return GATTClientDiscoverAllCharacteristicDescriptorsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientReadCharacteristicValue(
    device,
    DeviceId=bytearray(1),
    Characteristic_Properties=GATTClientReadCharacteristicValueRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientReadCharacteristicValueRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientReadCharacteristicValueRequest.Characteristic_Descriptors(),
    MaxReadBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientReadCharacteristicValueRequest(DeviceId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, MaxReadBytes)
    return GATTClientReadCharacteristicValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientReadUsingCharacteristicUuid(
    device,
    DeviceId=bytearray(1),
    UuidType=GATTClientReadUsingCharacteristicUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    HandleRangeIncluded=False,
    # Array length depends on HandleRangeIncluded. Mask: 0xFF. Shift: 0x00.
    HandleRange=GATTClientReadUsingCharacteristicUuidRequest.HandleRange(),
    MaxReadBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientReadUsingCharacteristicUuidRequest(DeviceId, UuidType, Uuid, HandleRangeIncluded, HandleRange, MaxReadBytes)
    return GATTClientReadUsingCharacteristicUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientReadMultipleCharacteristicValues(
    device,
    DeviceId=bytearray(1),
    NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Characteristics=GATTClientReadMultipleCharacteristicValuesRequest.Characteristics(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientReadMultipleCharacteristicValuesRequest(DeviceId, NbOfCharacteristics, Characteristics)
    return GATTClientReadMultipleCharacteristicValuesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientWriteCharacteristicValue(
    device,
    DeviceId=bytearray(1),
    Characteristic_Properties=GATTClientWriteCharacteristicValueRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientWriteCharacteristicValueRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientWriteCharacteristicValueRequest.Characteristic_Descriptors(),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    WithoutResponse=False,
    SignedWrite=False,
    ReliableLongCharWrites=False,
    # Unit length: 16 bytes
    Csrk=bytearray(16),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientWriteCharacteristicValueRequest(DeviceId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors,
                                                               Characteristic_Descriptors, ValueLength, Value, WithoutResponse, SignedWrite, ReliableLongCharWrites, Csrk)
    return GATTClientWriteCharacteristicValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientReadCharacteristicDescriptor(
    device,
    DeviceId=bytearray(1),
    Descriptor_Handle=bytearray(2),
    Descriptor_UuidType=GATTClientReadCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Descriptor_Uuid=[],
    Descriptor_ValueLength=bytearray(2),
    Descriptor_MaxValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Descriptor_Value=[],
    MaxReadBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientReadCharacteristicDescriptorRequest(DeviceId, Descriptor_Handle, Descriptor_UuidType, Descriptor_Uuid, Descriptor_ValueLength, Descriptor_MaxValueLength, Descriptor_Value, MaxReadBytes)
    return GATTClientReadCharacteristicDescriptorOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTClientWriteCharacteristicDescriptor(
    device,
    DeviceId=bytearray(1),
    Descriptor_Handle=bytearray(2),
    Descriptor_UuidType=GATTClientWriteCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Descriptor_Uuid=[],
    Descriptor_ValueLength=bytearray(2),
    Descriptor_MaxValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Descriptor_Value=[],
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientWriteCharacteristicDescriptorRequest(DeviceId, Descriptor_Handle, Descriptor_UuidType, Descriptor_Uuid, Descriptor_ValueLength, Descriptor_MaxValueLength, Descriptor_Value, ValueLength, Value)
    return GATTClientWriteCharacteristicDescriptorOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerInit(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerInitRequest()
    return GATTServerInitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerRegisterCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerRegisterCallbackRequest()
    return GATTServerRegisterCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerRegisterHandlesForWriteNotifications(
    device,
    HandleCount=bytearray(1),
    # Array length depends on HandleCount. Mask: 0xFF. Shift: 0x00.
    AttributeHandles=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerRegisterHandlesForWriteNotificationsRequest(HandleCount, AttributeHandles)
    return GATTServerRegisterHandlesForWriteNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendAttributeWrittenStatus(
    device,
    DeviceId=bytearray(1),
    AttributeHandle=bytearray(2),
    Status=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendAttributeWrittenStatusRequest(DeviceId, AttributeHandle, Status)
    return GATTServerSendAttributeWrittenStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendNotification(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendNotificationRequest(DeviceId, Handle)
    return GATTServerSendNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendIndication(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendIndicationRequest(DeviceId, Handle)
    return GATTServerSendIndicationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendInstantValueNotification(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendInstantValueNotificationRequest(DeviceId, Handle, ValueLength, Value)
    return GATTServerSendInstantValueNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendInstantValueIndication(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendInstantValueIndicationRequest(DeviceId, Handle, ValueLength, Value)
    return GATTServerSendInstantValueIndicationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerRegisterHandlesForReadNotifications(
    device,
    HandleCount=bytearray(1),
    # Array length depends on HandleCount. Mask: 0xFF. Shift: 0x00.
    AttributeHandles=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerRegisterHandlesForReadNotificationsRequest(HandleCount, AttributeHandles)
    return GATTServerRegisterHandlesForReadNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTServerSendAttributeReadStatus(
    device,
    DeviceId=bytearray(1),
    AttributeHandle=bytearray(2),
    Status=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendAttributeReadStatusRequest(DeviceId, AttributeHandle, Status)
    return GATTServerSendAttributeReadStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerRegisterUniqueHandlesForNotifications(
    device,
    bWrite=False,
    bRead=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerRegisterUniqueHandlesForNotificationsRequest(bWrite, bRead)
    return GATTServerRegisterUniqueHandlesForNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerUnregisterHandlesForWriteNotifications(
    device,
    HandleCount=bytearray(1),
    # Array length depends on HandleCount. Mask: 0xFF. Shift: 0x00.
    AttributeHandles=GATTServerUnregisterHandlesForWriteNotificationsRequest.AttributeHandles(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerUnregisterHandlesForWriteNotificationsRequest(HandleCount, AttributeHandles)
    return GATTServerUnregisterHandlesForWriteNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerUnregisterHandlesForReadNotifications(
    device,
    HandleCount=bytearray(1),
    # Array length depends on HandleCount. Mask: 0xFF. Shift: 0x00.
    AttributeHandles=GATTServerUnregisterHandlesForReadNotificationsRequest.AttributeHandles(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerUnregisterHandlesForReadNotificationsRequest(HandleCount, AttributeHandles)
    return GATTServerUnregisterHandlesForReadNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBWriteAttribute(
    device,
    Handle=bytearray(2),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFF. Shift: 0x00.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBWriteAttributeRequest(Handle, ValueLength, Value)
    return GATTDBWriteAttributeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBReadAttribute(
    device,
    Handle=bytearray(2),
    MaxBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBReadAttributeRequest(Handle, MaxBytes)
    return GATTDBReadAttributeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBFindServiceHandle(
    device,
    StartHandle=bytearray(2),
    UuidType=GATTDBFindServiceHandleRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBFindServiceHandleRequest(StartHandle, UuidType, Uuid)
    return GATTDBFindServiceHandleOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBFindCharValueHandleInService(
    device,
    ServiceHandle=bytearray(2),
    UuidType=GATTDBFindCharValueHandleInServiceRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBFindCharValueHandleInServiceRequest(ServiceHandle, UuidType, Uuid)
    return GATTDBFindCharValueHandleInServiceOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBFindCccdHandleForCharValueHandle(
    device,
    CharValueHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBFindCccdHandleForCharValueHandleRequest(CharValueHandle)
    return GATTDBFindCccdHandleForCharValueHandleOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBFindDescriptorHandleForCharValueHandle(
    device,
    CharValueHandle=bytearray(2),
    UuidType=GATTDBFindDescriptorHandleForCharValueHandleRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBFindDescriptorHandleForCharValueHandleRequest(CharValueHandle, UuidType, Uuid)
    return GATTDBFindDescriptorHandleForCharValueHandleOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBDynamicInit(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicInitRequest()
    return GATTDBDynamicInitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBDynamicReleaseDatabase(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicReleaseDatabaseRequest()
    return GATTDBDynamicReleaseDatabaseOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddPrimaryServiceDeclaration(
    device,
    DesiredHandle=bytearray(2),
    UuidType=GATTDBDynamicAddPrimaryServiceDeclarationRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddPrimaryServiceDeclarationRequest(DesiredHandle, UuidType, Uuid)
    return GATTDBDynamicAddPrimaryServiceDeclarationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddSecondaryServiceDeclaration(
    device,
    DesiredHandle=bytearray(2),
    UuidType=GATTDBDynamicAddSecondaryServiceDeclarationRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddSecondaryServiceDeclarationRequest(DesiredHandle, UuidType, Uuid)
    return GATTDBDynamicAddSecondaryServiceDeclarationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddIncludeDeclaration(
    device,
    IncludedServiceHandle=bytearray(2),
    EndGroupHandle=bytearray(2),
    UuidType=GATTDBDynamicAddIncludeDeclarationRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddIncludeDeclarationRequest(IncludedServiceHandle, EndGroupHandle, UuidType, Uuid)
    return GATTDBDynamicAddIncludeDeclarationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddCharacteristicDeclarationAndValue(
    device,
    UuidType=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    CharacteristicProperties=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestCharacteristicProperties.gNone_c,
    MaxValueLength=bytearray(2),
    InitialValueLength=bytearray(2),
    # Array length depends on InitialValueLength. Mask: 0xFFFF. Shift: 0x0000.
    InitialValue=[],
    ValueAccessPermissions=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestValueAccessPermissions.gPermissionNone_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(UuidType, Uuid, CharacteristicProperties, MaxValueLength, InitialValueLength, InitialValue, ValueAccessPermissions)
    return GATTDBDynamicAddCharacteristicDeclarationAndValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddCharacteristicDescriptor(
    device,
    UuidType=GATTDBDynamicAddCharacteristicDescriptorRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    DescriptorValueLength=bytearray(2),
    # Array length depends on DescriptorValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    DescriptorAccessPermissions=GATTDBDynamicAddCharacteristicDescriptorRequestDescriptorAccessPermissions.gPermissionNone_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddCharacteristicDescriptorRequest(UuidType, Uuid, DescriptorValueLength, Value, DescriptorAccessPermissions)
    return GATTDBDynamicAddCharacteristicDescriptorOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddCccd(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddCccdRequest()
    return GATTDBDynamicAddCccdOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicAddCharacteristicDeclarationWithUniqueValue(
    device,
    UuidType=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    CharacteristicProperties=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestCharacteristicProperties.gNone_c,
    ValueAccessPermissions=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestValueAccessPermissions.gPermissionNone_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(UuidType, Uuid, CharacteristicProperties, ValueAccessPermissions)
    return GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicRemoveService(
    device,
    ServiceHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicRemoveServiceRequest(ServiceHandle)
    return GATTDBDynamicRemoveServiceOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GATTDBDynamicRemoveCharacteristic(
    device,
    CharacteristicHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicRemoveCharacteristicRequest(CharacteristicHandle)
    return GATTDBDynamicRemoveCharacteristicOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBDynamicAddCharDescriptorWithUniqueValue(
    device,
    UuidType=GATTDBDynamicAddCharDescriptorWithUniqueValueRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    DescriptorAccessPermissions=GATTDBDynamicAddCharDescriptorWithUniqueValueRequestDescriptorAccessPermissions.gPermissionNone_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicAddCharDescriptorWithUniqueValueRequest(UuidType, Uuid, DescriptorAccessPermissions)
    return GATTDBDynamicAddCharDescriptorWithUniqueValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def BLEHostInitialize(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.BLEHostInitializeRequest()
    return BLEHostInitializeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRegisterDeviceSecurityRequirements(
    device,
    SecurityRequirementsIncluded=False,
    # Array length depends on SecurityRequirementsIncluded. Mask: 0xFF. Shift: 0x00.
    SecurityRequirements=GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRegisterDeviceSecurityRequirementsRequest(SecurityRequirementsIncluded, SecurityRequirements)
    return GAPRegisterDeviceSecurityRequirementsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetAdvertisingParameters(
    device,
    AdvertisingParameters_MinInterval=bytearray(2),
    AdvertisingParameters_MaxInterval=bytearray(2),
    AdvertisingParameters_AdvertisingType=GAPSetAdvertisingParametersRequestAdvertisingParameters_AdvertisingType.gConnectableUndirected_c,
    AdvertisingParameters_OwnAddressType=GAPSetAdvertisingParametersRequestAdvertisingParameters_OwnAddressType.gPublic_c,
    AdvertisingParameters_PeerAddressType=GAPSetAdvertisingParametersRequestAdvertisingParameters_PeerAddressType.gPublic_c,
    # Unit length: 6 bytes
    AdvertisingParameters_PeerAddress=bytearray(6),
    AdvertisingParameters_ChannelMap=bytearray(1),
    AdvertisingParameters_FilterPolicy=GAPSetAdvertisingParametersRequestAdvertisingParameters_FilterPolicy.gProcessAll_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetAdvertisingParametersRequest(AdvertisingParameters_MinInterval, AdvertisingParameters_MaxInterval, AdvertisingParameters_AdvertisingType, AdvertisingParameters_OwnAddressType,
                                                        AdvertisingParameters_PeerAddressType, AdvertisingParameters_PeerAddress, AdvertisingParameters_ChannelMap, AdvertisingParameters_FilterPolicy)
    return GAPSetAdvertisingParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetAdvertisingData(
    device,
    AdvertisingDataIncluded=False,
    # Array length depends on AdvertisingDataIncluded. Mask: 0xFF. Shift: 0x00.
    AdvertisingData=GAPSetAdvertisingDataRequest.AdvertisingData(),
    ScanResponseDataIncluded=False,
    # Array length depends on ScanResponseDataIncluded. Mask: 0xFF. Shift: 0x00.
    ScanResponseData=GAPSetAdvertisingDataRequest.ScanResponseData(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetAdvertisingDataRequest(AdvertisingDataIncluded, AdvertisingData, ScanResponseDataIncluded, ScanResponseData)
    return GAPSetAdvertisingDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPStartAdvertising(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStartAdvertisingRequest()
    return GAPStartAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPStopAdvertising(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStopAdvertisingRequest()
    return GAPStopAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPAuthorize(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    Access=GAPAuthorizeRequestAccess.gRead_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPAuthorizeRequest(DeviceId, Handle, Access)
    return GAPAuthorizeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSaveCccd(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    Cccd=GAPSaveCccdRequestCccd.gEmpty_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSaveCccdRequest(DeviceId, Handle, Cccd)
    return GAPSaveCccdOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPCheckNotificationStatus(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPCheckNotificationStatusRequest(DeviceId, Handle)
    return GAPCheckNotificationStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPCheckIndicationStatus(
    device,
    DeviceId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPCheckIndicationStatusRequest(DeviceId, Handle)
    return GAPCheckIndicationStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPPair(
    device,
    DeviceId=bytearray(1),
    PairingParameters_WithBonding=False,
    PairingParameters_SecurityModeAndLevel=GAPPairRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c,
    PairingParameters_MaxEncryptionKeySize=bytearray(1),
    PairingParameters_LocalIoCapabilities=GAPPairRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c,
    PairingParameters_OobAvailable=False,
    PairingParameters_CentralKeys=bytearray(1),
    PairingParameters_PeripheralKeys=bytearray(1),
    PairingParameters_LeSecureConnectionSupported=False,
    PairingParameters_UseKeypressNotifications=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPairRequest(DeviceId, PairingParameters_WithBonding, PairingParameters_SecurityModeAndLevel, PairingParameters_MaxEncryptionKeySize, PairingParameters_LocalIoCapabilities, PairingParameters_OobAvailable, PairingParameters_CentralKeys, PairingParameters_PeripheralKeys, PairingParameters_LeSecureConnectionSupported, PairingParameters_UseKeypressNotifications)
    return GAPPairOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSendSlaveSecurityRequest(
    device,
    DeviceId=bytearray(1),
    PairingParameters_WithBonding=False,
    PairingParameters_SecurityModeAndLevel=GAPSendSlaveSecurityRequestRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c,
    PairingParameters_MaxEncryptionKeySize=bytearray(1),
    PairingParameters_LocalIoCapabilities=GAPSendSlaveSecurityRequestRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c,
    PairingParameters_OobAvailable=False,
    PairingParameters_CentralKeys=bytearray(1),
    PairingParameters_PeripheralKeys=bytearray(1),
    PairingParameters_LeSecureConnectionSupported=False,
    PairingParameters_UseKeypressNotifications=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSendSlaveSecurityRequestRequest(DeviceId, PairingParameters_WithBonding, PairingParameters_SecurityModeAndLevel, PairingParameters_MaxEncryptionKeySize, PairingParameters_LocalIoCapabilities, PairingParameters_OobAvailable, PairingParameters_CentralKeys, PairingParameters_PeripheralKeys, PairingParameters_LeSecureConnectionSupported, PairingParameters_UseKeypressNotifications)
    return GAPSendSlaveSecurityRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPEncryptLink(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEncryptLinkRequest(DeviceId)
    return GAPEncryptLinkOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPAcceptPairingRequest(
    device,
    DeviceId=bytearray(1),
    PairingParameters_WithBonding=False,
    PairingParameters_SecurityModeAndLevel=GAPAcceptPairingRequestRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c,
    PairingParameters_MaxEncryptionKeySize=bytearray(1),
    PairingParameters_LocalIoCapabilities=GAPAcceptPairingRequestRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c,
    PairingParameters_OobAvailable=False,
    PairingParameters_CentralKeys=bytearray(1),
    PairingParameters_PeripheralKeys=bytearray(1),
    PairingParameters_LeSecureConnectionSupported=False,
    PairingParameters_UseKeypressNotifications=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPAcceptPairingRequestRequest(DeviceId, PairingParameters_WithBonding, PairingParameters_SecurityModeAndLevel, PairingParameters_MaxEncryptionKeySize, PairingParameters_LocalIoCapabilities,
                                                    PairingParameters_OobAvailable, PairingParameters_CentralKeys, PairingParameters_PeripheralKeys, PairingParameters_LeSecureConnectionSupported, PairingParameters_UseKeypressNotifications)
    return GAPAcceptPairingRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRejectPairing(
    device,
    DeviceId=bytearray(1),
    Reason=GAPRejectPairingRequestReason.gOobNotAvailable_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRejectPairingRequest(DeviceId, Reason)
    return GAPRejectPairingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPEnterPasskey(
    device,
    DeviceId=bytearray(1),
    Passkey=bytearray(4),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnterPasskeyRequest(DeviceId, Passkey)
    return GAPEnterPasskeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPProvideOob(
    device,
    DeviceId=bytearray(1),
    # Unit length: 16 bytes
    Oob=bytearray(16),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPProvideOobRequest(DeviceId, Oob)
    return GAPProvideOobOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRejectPasskeyRequest(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRejectPasskeyRequestRequest(DeviceId)
    return GAPRejectPasskeyRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSendSmpKeys(
    device,
    DeviceId=bytearray(1),
    Keys_LtkIncluded=False,
    # Array length depends on LtkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_LtkInfo=GAPSendSmpKeysRequest.Keys_LtkInfo(),
    Keys_IrkIncluded=False,
    # Unit length: 16 bytes
        # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_Irk=[],
    Keys_CsrkIncluded=False,
    # Unit length: 16 bytes
        # Array length depends on CsrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_Csrk=[],
    # Array length depends on LtkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_RandEdivInfo=GAPSendSmpKeysRequest.Keys_RandEdivInfo(),
    # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_AddressIncluded=[],
    # Array length depends on AddressIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_AddressInfo=GAPSendSmpKeysRequest.Keys_AddressInfo(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSendSmpKeysRequest(DeviceId, Keys_LtkIncluded, Keys_LtkInfo, Keys_IrkIncluded, Keys_Irk, Keys_CsrkIncluded, Keys_Csrk, Keys_RandEdivInfo, Keys_AddressIncluded, Keys_AddressInfo)
    return GAPSendSmpKeysOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRejectKeyExchangeRequest(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRejectKeyExchangeRequestRequest(DeviceId)
    return GAPRejectKeyExchangeRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPProvideLongTermKey(
    device,
    DeviceId=bytearray(1),
    LtkSize=bytearray(1),
    # Array length depends on LtkSize. Mask: 0xFF. Shift: 0x00.
    Ltk=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPProvideLongTermKeyRequest(DeviceId, LtkSize, Ltk)
    return GAPProvideLongTermKeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPDenyLongTermKey(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPDenyLongTermKeyRequest(DeviceId)
    return GAPDenyLongTermKeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLoadEncryptionInformation(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLoadEncryptionInformationRequest(DeviceId)
    return GAPLoadEncryptionInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetLocalPasskey(
    device,
    Passkey=bytearray(4),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetLocalPasskeyRequest(Passkey)
    return GAPSetLocalPasskeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPStartScanning(
    device,
    ScanningParametersIncluded=False,
    # Array length depends on ScanningParametersIncluded. Mask: 0xFF. Shift: 0x00.
    ScanningParameters=GAPStartScanningRequest.ScanningParameters(),
    EnableFilterDuplicates=False,
    ScanningPHY=bytearray(1),
    Duration=bytearray(2),
    Period=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStartScanningRequest(ScanningParametersIncluded, ScanningParameters, EnableFilterDuplicates, ScanningPHY, Duration, Period)
    return GAPStartScanningOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPStopScanning(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStopScanningRequest()
    return GAPStopScanningOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPConnect(
    device,
    CreateConnectionParameters_ScanInterval=bytearray(2),
    CreateConnectionParameters_ScanWindow=bytearray(2),
    CreateConnectionParameters_FilterPolicy=GAPConnectRequestCreateConnectionParameters_FilterPolicy.gUseDeviceAddress_c,
    CreateConnectionParameters_OwnAddressType=GAPConnectRequestCreateConnectionParameters_OwnAddressType.gPublic_c,
    CreateConnectionParameters_PeerAddressType=GAPConnectRequestCreateConnectionParameters_PeerAddressType.gPublic_c,
    # Unit length: 6 bytes
    CreateConnectionParameters_PeerAddress=bytearray(6),
    CreateConnectionParameters_ConnIntervalMin=bytearray(2),
    CreateConnectionParameters_ConnIntervalMax=bytearray(2),
    CreateConnectionParameters_ConnLatency=bytearray(2),
    CreateConnectionParameters_SupervisionTimeout=bytearray(2),
    CreateConnectionParameters_ConnEventLengthMin=bytearray(2),
    CreateConnectionParameters_ConnEventLengthMax=bytearray(2),
    CreateConnectionParameters_usePeerIdentityAddress=False,
    CreateConnectionParameters_Initiating_PHY=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPConnectRequest(CreateConnectionParameters_ScanInterval, CreateConnectionParameters_ScanWindow, CreateConnectionParameters_FilterPolicy, CreateConnectionParameters_OwnAddressType, CreateConnectionParameters_PeerAddressType, CreateConnectionParameters_PeerAddress, CreateConnectionParameters_ConnIntervalMin,
                                       CreateConnectionParameters_ConnIntervalMax, CreateConnectionParameters_ConnLatency, CreateConnectionParameters_SupervisionTimeout, CreateConnectionParameters_ConnEventLengthMin, CreateConnectionParameters_ConnEventLengthMax, CreateConnectionParameters_usePeerIdentityAddress, CreateConnectionParameters_Initiating_PHY)
    return GAPConnectOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPDisconnect(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPDisconnectRequest(DeviceId)
    return GAPDisconnectOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSaveCustomPeerInformation(
    device,
    DeviceId=bytearray(1),
    Offset=bytearray(2),
    InfoSize=bytearray(2),
    # Array length depends on InfoSize. Mask: 0xFFFF. Shift: 0x0000.
    Info=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSaveCustomPeerInformationRequest(DeviceId, Offset, InfoSize, Info)
    return GAPSaveCustomPeerInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLoadCustomPeerInformation(
    device,
    DeviceId=bytearray(1),
    Offset=bytearray(2),
    InfoSize=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLoadCustomPeerInformationRequest(DeviceId, Offset, InfoSize)
    return GAPLoadCustomPeerInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPCheckIfBonded(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPCheckIfBondedRequest(DeviceId)
    return GAPCheckIfBondedOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPReadWhiteListSize(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadWhiteListSizeRequest()
    return GAPReadWhiteListSizeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPClearWhiteList(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPClearWhiteListRequest()
    return GAPClearWhiteListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPAddDeviceToWhiteList(
    device,
    AddressType=GAPAddDeviceToWhiteListRequestAddressType.gPublic_c,
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPAddDeviceToWhiteListRequest(AddressType, Address)
    return GAPAddDeviceToWhiteListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRemoveDeviceFromWhiteList(
    device,
    AddressType=GAPRemoveDeviceFromWhiteListRequestAddressType.gPublic_c,
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRemoveDeviceFromWhiteListRequest(AddressType, Address)
    return GAPRemoveDeviceFromWhiteListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPReadPublicDeviceAddress(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadPublicDeviceAddressRequest()
    return GAPReadPublicDeviceAddressOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPCreateRandomDeviceAddress(
    device,
    IrkIncluded=False,
    # Unit length: 16 bytes
        # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    Irk=[],
    # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    RandomPartIncluded=[],
    # Unit length: 3 bytes
        # Array length depends on RandomPartIncluded. Mask: 0xFF. Shift: 0x00.
    RandomPart=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPCreateRandomDeviceAddressRequest(IrkIncluded, Irk, RandomPartIncluded, RandomPart)
    return GAPCreateRandomDeviceAddressOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSaveDeviceName(
    device,
    DeviceId=bytearray(1),
    NameSize=bytearray(1),
    # Array length depends on NameSize. Mask: 0xFF. Shift: 0x00.
    Name=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSaveDeviceNameRequest(DeviceId, NameSize, Name)
    return GAPSaveDeviceNameOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPGetBondedDevicesCount(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPGetBondedDevicesCountRequest()
    return GAPGetBondedDevicesCountOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPGetBondedDeviceName(
    device,
    NvmIndex=bytearray(1),
    MaxNameSize=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPGetBondedDeviceNameRequest(NvmIndex, MaxNameSize)
    return GAPGetBondedDeviceNameOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRemoveBond(
    device,
    NvmIndex=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRemoveBondRequest(NvmIndex)
    return GAPRemoveBondOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPRemoveAllBonds(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRemoveAllBondsRequest()
    return GAPRemoveAllBondsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPReadRadioPowerLevel(
    device,
    TxReadType=GAPReadRadioPowerLevelRequestTxReadType.gTxPowerCurrentLevelInConnection_c,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadRadioPowerLevelRequest(TxReadType, DeviceId)
    return GAPReadRadioPowerLevelOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPVerifyPrivateResolvableAddress(
    device,
    NvmIndex=bytearray(1),
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPVerifyPrivateResolvableAddressRequest(NvmIndex, Address)
    return GAPVerifyPrivateResolvableAddressOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetRandomAddress(
    device,
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetRandomAddressRequest(Address)
    return GAPSetRandomAddressOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetScanMode(
    device,
    ScanMode=GAPSetScanModeRequestScanMode.gDefaultScan_c,
    AutoConnectParams_NbOfAddresses=bytearray(1),
    AutoConnectParams_WriteInWhiteList=False,
    # Array length depends on NbOfAddresses. Mask: 0xFF. Shift: 0x00.
    AutoConnectParams_AutoConnectData=GAPSetScanModeRequest.AutoConnectParams_AutoConnectData(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetScanModeRequest(ScanMode, AutoConnectParams_NbOfAddresses, AutoConnectParams_WriteInWhiteList, AutoConnectParams_AutoConnectData)
    return GAPSetScanModeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetDefaultPairingParameters(
    device,
    PairingParametersIncluded=False,
    # Array length depends on PairingParametersIncluded. Mask: 0xFF. Shift: 0x00.
    PairingParameters=GAPSetDefaultPairingParametersRequest.PairingParameters(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetDefaultPairingParametersRequest(PairingParametersIncluded, PairingParameters)
    return GAPSetDefaultPairingParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPUpdateConnectionParameters(
    device,
    DeviceId=bytearray(1),
    IntervalMin=bytearray(2),
    IntervalMax=bytearray(2),
    SlaveLatency=bytearray(2),
    TimeoutMultiplier=bytearray(2),
    MinCeLength=bytearray(2),
    MaxCeLength=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPUpdateConnectionParametersRequest(DeviceId, IntervalMin, IntervalMax, SlaveLatency, TimeoutMultiplier, MinCeLength, MaxCeLength)
    return GAPUpdateConnectionParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPEnableUpdateConnectionParameters(
    device,
    DeviceId=bytearray(1),
    Enable=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableUpdateConnectionParametersRequest(DeviceId, Enable)
    return GAPEnableUpdateConnectionParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GapUpdateLeDataLength(
    device,
    DeviceId=bytearray(1),
    TxOctets=bytearray(2),
    TxTime=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GapUpdateLeDataLengthRequest(DeviceId, TxOctets, TxTime)
    return GapUpdateLeDataLengthOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)



def GAPEnableHostPrivacy(
    device,
    Enable=False,
    # Unit length: 16 bytes
        # Array length depends on Enable. Mask: 0xFF. Shift: 0x00.
    Irk=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableHostPrivacyRequest(Enable, Irk)
    return GAPEnableHostPrivacyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPEnableControllerPrivacy(
    device,
    Enable=False,
    # Unit length: 16 bytes
        # Array length depends on Enable. Mask: 0xFF. Shift: 0x00.
    OwnIrk=[],
    # Array length depends on Enable. Mask: 0xFF. Shift: 0x00.
    PeerIdCount=[],
    # Array length depends on PeerIdCount. Mask: 0xFF. Shift: 0x00.
    PeerIdentities=GAPEnableControllerPrivacyRequest.PeerIdentities(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableControllerPrivacyRequest(Enable, OwnIrk, PeerIdCount, PeerIdentities)
    return GAPEnableControllerPrivacyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeScRegeneratePublicKey(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeScRegeneratePublicKeyRequest()
    return GAPLeScRegeneratePublicKeyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeScValidateNumericValue(
    device,
    DeviceId=bytearray(1),
    Valid=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeScValidateNumericValueRequest(DeviceId, Valid)
    return GAPLeScValidateNumericValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeScGetLocalOobData(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeScGetLocalOobDataRequest()
    return GAPLeScGetLocalOobDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeScSetPeerOobData(
    device,
    DeviceId=bytearray(1),
    # Unit length: 16 bytes
    RandomValue=bytearray(16),
    # Unit length: 16 bytes
    ConfirmValue=bytearray(16),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeScSetPeerOobDataRequest(DeviceId, RandomValue, ConfirmValue)
    return GAPLeScSetPeerOobDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeScSendKeypressNotificationPrivacy(
    device,
    DeviceId=bytearray(1),
    GapLeScKeypressNotificationParams_keypressNotifType=GAPLeScSendKeypressNotificationPrivacyRequestGapLeScKeypressNotificationParams_keypressNotifType.gKnPasskeyEntryStarted_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeScSendKeypressNotificationPrivacyRequest(DeviceId, GapLeScKeypressNotificationParams_keypressNotifType)
    return GAPLeScSendKeypressNotificationPrivacyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPGetBondedDevicesIdentityInformation(
    device,
    maxDevices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPGetBondedDevicesIdentityInformationRequest(maxDevices)
    return GAPGetBondedDevicesIdentityInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetTxPowerLevel(
    device,
    powerLevel=bytearray(1),
    channelType=GAPSetTxPowerLevelRequestchannelType.Advertising,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetTxPowerLevelRequest(powerLevel, channelType)
    return GAPSetTxPowerLevelOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeReadPhy(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeReadPhyRequest(DeviceId)
    return GAPLeReadPhyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLeSetPhy(
    device,
    defaultMode=False,
    DeviceId=bytearray(1),
    allPhys=bytearray(1),
    txPhys=bytearray(1),
    rxPhys=bytearray(1),
    phyOptions=GAPLeSetPhyRequestphyOptions.gLeCodingNoPreference_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLeSetPhyRequest(defaultMode, DeviceId, allPhys, txPhys, rxPhys, phyOptions)
    return GAPLeSetPhyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPControllerEnhancedNotification(
    device,
    EventType=bytearray(2),
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPControllerEnhancedNotificationRequest(EventType, DeviceId)
    return GAPControllerEnhancedNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPLoadKeys(
    device,
    NvmIndex=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPLoadKeysRequest(NvmIndex)
    return GAPLoadKeysOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSaveKeys(
    device,
    NvmIndex=bytearray(1),
    Keys_LtkIncluded=False,
    # Array length depends on LtkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_LtkInfo=GAPSaveKeysRequest.Keys_LtkInfo(),
    Keys_IrkIncluded=False,
    # Unit length: 16 bytes
        # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_Irk=[],
    Keys_CsrkIncluded=False,
    # Unit length: 16 bytes
        # Array length depends on CsrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_Csrk=[],
    # Array length depends on LtkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_RandEdivInfo=GAPSaveKeysRequest.Keys_RandEdivInfo(),
    # Array length depends on IrkIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_AddressIncluded=[],
    # Array length depends on AddressIncluded. Mask: 0xFF. Shift: 0x00.
    Keys_AddressInfo=GAPSaveKeysRequest.Keys_AddressInfo(),
    LeSc=False,
    Authenticated=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSaveKeysRequest(NvmIndex, Keys_LtkIncluded, Keys_LtkInfo, Keys_IrkIncluded, Keys_Irk, Keys_CsrkIncluded, Keys_Csrk, Keys_RandEdivInfo, Keys_AddressIncluded, Keys_AddressInfo, LeSc, Authenticated)
    return GAPSaveKeysOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPSetChannelMap(
    device,
    # Unit length: 5 bytes
    ChannelMap=bytearray(5),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetChannelMapRequest(ChannelMap)
    return GAPSetChannelMapOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def GAPReadChannelMap(
    device,
    DeviceId=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadChannelMapRequest(DeviceId)
    return GAPReadChannelMapOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetPrivacyMode(
    device,
    NvmIndex=bytearray(1),
    PrivacyMode=GAPSetPrivacyModeRequestPrivacyMode.gNetworkPrivacy_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetPrivacyModeRequest(NvmIndex, PrivacyMode)
    return GAPSetPrivacyModeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def FSCICPUReset(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCICPUResetRequest()
    return FSCICPUResetOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def FSCIGetNumberOfFreeBuffers(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCIGetNumberOfFreeBuffersRequest()
    return FSCIGetNumberOfFreeBuffersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def FSCIAllowDeviceToSleep(
    device,
    SignalHostWhenWakeUp=FSCIAllowDeviceToSleepRequestSignalHostWhenWakeUp.FALSE,
    DeepSleepDuration=bytearray(4),
    DeepSleepMode=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCIAllowDeviceToSleepRequest(SignalHostWhenWakeUp, DeepSleepDuration, DeepSleepMode)
    return FSCIAllowDeviceToSleepOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)


def FSCIGetWakeupReason(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCIGetWakeupReasonRequest()
    return FSCIGetWakeupReasonOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)
