'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2022 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.ble.enums import *  # @UnusedWildImport
import com.nxp.wireless_connectivity.commands.ble.frames as Frames
from com.nxp.wireless_connectivity.commands.ble.operations import *  # @UnusedWildImport

def L2CAPInit(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPInitRequest()
    return L2CAPInitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPSendAttData(
    device,
    DeviceId=bytearray(1),
    PacketLength=bytearray(2),
    # Array length depends on PacketLength. Mask: 0xFFFF. Shift: 0x0000.
    Packet=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPSendAttDataRequest(DeviceId, PacketLength, Packet)
    return L2CAPSendAttDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPSendSmpData(
    device,
    DeviceId=bytearray(1),
    PacketLength=bytearray(2),
    # Array length depends on PacketLength. Mask: 0xFFFF. Shift: 0x0000.
    Packet=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPSendSmpDataRequest(DeviceId, PacketLength, Packet)
    return L2CAPSendSmpDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPRegisterAttCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPRegisterAttCallbackRequest()
    return L2CAPRegisterAttCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPRegisterSmpCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPRegisterSmpCallbackRequest()
    return L2CAPRegisterSmpCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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

def L2CAPCBEnhancedConnectLePsm(
    device,
    LePsm=bytearray(2),
    DeviceId=bytearray(1),
    Mtu=bytearray(2),
    InitialCredits=bytearray(2),
    NoOfChannels=bytearray(1),
    # Array length depends on NoOfChannels. Mask: 0xFFFF. Shift: 0x0000.
    Cids=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBEnhancedConnectLePsmRequest(LePsm, DeviceId, Mtu, InitialCredits, NoOfChannels, Cids)
    return L2CAPCBEnhancedConnectLePsmOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPCBEnhancedChannelReconfigure(
    device,
    DeviceId=bytearray(1),
    NewMtu=bytearray(2),
    NewMps=bytearray(2),
    NoOfChannels=bytearray(1),
    # Array length depends on NoOfChannels. Mask: 0xFFFF. Shift: 0x0000.
    Cids=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBEnhancedChannelReconfigureRequest(DeviceId, NewMtu, NewMps, NoOfChannels, Cids)
    return L2CAPCBEnhancedChannelReconfigureOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def L2CAPCBEnhancedCancelConnection(
    device,
    LePsm=bytearray(2),
    DeviceId=bytearray(1),
    RefuseReason=L2CAPCBEnhancedCancelConnectionRequestRefuseReason.gSuccessful_c,
    NoOfChannels=bytearray(1),
    # Array length depends on NoOfChannels. Mask: 0xFFFF. Shift: 0x0000.
    Cids=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.L2CAPCBEnhancedCancelConnectionRequest(LePsm, DeviceId, RefuseReason, NoOfChannels, Cids)
    return L2CAPCBEnhancedCancelConnectionOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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

def GATTClientRegisterMultipleValueNotificationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterMultipleValueNotificationCallbackRequest()
    return GATTClientRegisterMultipleValueNotificationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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
    request = Frames.GATTClientFindIncludedServicesRequest(DeviceId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfIncludedServices)
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
    request = Frames.GATTClientDiscoverAllCharacteristicsOfServiceRequest(DeviceId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
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
    request = Frames.GATTClientDiscoverCharacteristicOfServiceByUuidRequest(DeviceId, UuidType, Uuid, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
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
    request = Frames.GATTClientWriteCharacteristicValueRequest(DeviceId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, ValueLength, Value, WithoutResponse, SignedWrite, ReliableLongCharWrites, Csrk)
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

def GATTServerSendMultipleHandleValueNotification(
    device,
    DeviceId=bytearray(1),
    HandleCount=bytearray(1),
    # Array length depends on HandleCount. Mask: 0xFF. Shift: 0x00.
    HandleLengthValueList=GATTServerSendMultipleHandleValueNotificationRequest.HandleLengthValueList(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerSendMultipleHandleValueNotificationRequest(DeviceId, HandleCount, HandleLengthValueList)
    return GATTServerSendMultipleHandleValueNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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
    AttributeHandles=[],
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
    AttributeHandles=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerUnregisterHandlesForReadNotificationsRequest(HandleCount, AttributeHandles)
    return GATTServerUnregisterHandlesForReadNotificationsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientReadMultipleVariableCharacteristicValues(
    device,
    DeviceId=bytearray(1),
    NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Characteristics=GATTClientReadMultipleVariableCharacteristicValuesRequest.Characteristics(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientReadMultipleVariableCharacteristicValuesRequest(DeviceId, NbOfCharacteristics, Characteristics)
    return GATTClientReadMultipleVariableCharacteristicValuesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientRegisterEnhancedProcedureCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterEnhancedProcedureCallbackRequest()
    return GATTClientRegisterEnhancedProcedureCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientRegisterEnhancedNotificationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterEnhancedNotificationCallbackRequest()
    return GATTClientRegisterEnhancedNotificationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientRegisterEnhancedIndicationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterEnhancedIndicationCallbackRequest()
    return GATTClientRegisterEnhancedIndicationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientRegisterEnhancedMultipleValueNotificationCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientRegisterEnhancedMultipleValueNotificationCallbackRequest()
    return GATTClientRegisterEnhancedMultipleValueNotificationCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedDiscoverAllPrimaryServices(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    MaxNbOfServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedDiscoverAllPrimaryServicesRequest(DeviceId, BearerId, MaxNbOfServices)
    return GATTClientEnhancedDiscoverAllPrimaryServicesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedDiscoverPrimaryServicesByUuid(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    UuidType=GATTClientEnhancedDiscoverPrimaryServicesByUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    MaxNbOfServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedDiscoverPrimaryServicesByUuidRequest(DeviceId, BearerId, UuidType, Uuid, MaxNbOfServices)
    return GATTClientEnhancedDiscoverPrimaryServicesByUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedFindIncludedServices(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientEnhancedFindIncludedServicesRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientEnhancedFindIncludedServicesRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientEnhancedFindIncludedServicesRequest.Service_IncludedServices(),
    MaxNbOfIncludedServices=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedFindIncludedServicesRequest(DeviceId, BearerId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfIncludedServices)
    return GATTClientEnhancedFindIncludedServicesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedDiscoverAllCharacteristicsOfService(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest.Service_IncludedServices(),
    MaxNbOfCharacteristics=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest(DeviceId, BearerId, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
    return GATTClientEnhancedDiscoverAllCharacteristicsOfServiceOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedDiscoverCharacteristicOfServiceByUuid(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    UuidType=GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    Service_StartHandle=bytearray(2),
    Service_EndHandle=bytearray(2),
    Service_UuidType=GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequestService_UuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Service_Uuid=[],
    Service_NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Service_Characteristics=GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest.Service_Characteristics(),
    Service_NbOfIncludedServices=bytearray(1),
    # Array length depends on NbOfIncludedServices. Mask: 0xFF. Shift: 0x00.
    Service_IncludedServices=GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest.Service_IncludedServices(),
    MaxNbOfCharacteristics=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest(DeviceId, BearerId, UuidType, Uuid, Service_StartHandle, Service_EndHandle, Service_UuidType, Service_Uuid, Service_NbOfCharacteristics, Service_Characteristics, Service_NbOfIncludedServices, Service_IncludedServices, MaxNbOfCharacteristics)
    return GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedDiscoverAllCharacteristicDescriptors(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Characteristic_Properties=GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest.Characteristic_Descriptors(),
    EndingHandle=bytearray(2),
    MaxNbOfDescriptors=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest(DeviceId, BearerId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, EndingHandle, MaxNbOfDescriptors)
    return GATTClientEnhancedDiscoverAllCharacteristicDescriptorsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedReadCharacteristicValue(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Characteristic_Properties=GATTClientEnhancedReadCharacteristicValueRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientEnhancedReadCharacteristicValueRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientEnhancedReadCharacteristicValueRequest.Characteristic_Descriptors(),
    MaxReadBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedReadCharacteristicValueRequest(DeviceId, BearerId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, MaxReadBytes)
    return GATTClientEnhancedReadCharacteristicValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedReadUsingCharacteristicUuid(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    UuidType=GATTClientEnhancedReadUsingCharacteristicUuidRequestUuidType.Uuid16Bits,
    # Array length depends on UuidType. Mask: 0xFF. Shift: 0x00.
    Uuid=[],
    HandleRangeIncluded=False,
    # Array length depends on HandleRangeIncluded. Mask: 0xFF. Shift: 0x00.
    HandleRange=GATTClientEnhancedReadUsingCharacteristicUuidRequest.HandleRange(),
    MaxReadBytes=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedReadUsingCharacteristicUuidRequest(DeviceId, BearerId, UuidType, Uuid, HandleRangeIncluded, HandleRange, MaxReadBytes)
    return GATTClientEnhancedReadUsingCharacteristicUuidOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedReadMultipleCharacteristicValues(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Characteristics=GATTClientEnhancedReadMultipleCharacteristicValuesRequest.Characteristics(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedReadMultipleCharacteristicValuesRequest(DeviceId, BearerId, NbOfCharacteristics, Characteristics)
    return GATTClientEnhancedReadMultipleCharacteristicValuesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedWriteCharacteristicValue(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Characteristic_Properties=GATTClientEnhancedWriteCharacteristicValueRequestCharacteristic_Properties.gNone_c,
    Characteristic_Value=GATTClientEnhancedWriteCharacteristicValueRequest.Characteristic_Value(),
    Characteristic_NbOfDescriptors=bytearray(1),
    # Array length depends on NbOfDescriptors. Mask: 0xFF. Shift: 0x00.
    Characteristic_Descriptors=GATTClientEnhancedWriteCharacteristicValueRequest.Characteristic_Descriptors(),
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
    request = Frames.GATTClientEnhancedWriteCharacteristicValueRequest(DeviceId, BearerId, Characteristic_Properties, Characteristic_Value, Characteristic_NbOfDescriptors, Characteristic_Descriptors, ValueLength, Value, WithoutResponse, SignedWrite, ReliableLongCharWrites, Csrk)
    return GATTClientEnhancedWriteCharacteristicValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedReadCharacteristicDescriptor(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Descriptor_Handle=bytearray(2),
    Descriptor_UuidType=GATTClientEnhancedReadCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits,
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
    request = Frames.GATTClientEnhancedReadCharacteristicDescriptorRequest(DeviceId, BearerId, Descriptor_Handle, Descriptor_UuidType, Descriptor_Uuid, Descriptor_ValueLength, Descriptor_MaxValueLength, Descriptor_Value, MaxReadBytes)
    return GATTClientEnhancedReadCharacteristicDescriptorOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedWriteCharacteristicDescriptor(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Descriptor_Handle=bytearray(2),
    Descriptor_UuidType=GATTClientEnhancedWriteCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits,
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
    request = Frames.GATTClientEnhancedWriteCharacteristicDescriptorRequest(DeviceId, BearerId, Descriptor_Handle, Descriptor_UuidType, Descriptor_Uuid, Descriptor_ValueLength, Descriptor_MaxValueLength, Descriptor_Value, ValueLength, Value)
    return GATTClientEnhancedWriteCharacteristicDescriptorOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientEnhancedReadMultipleVariableCharacteristicValues(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    NbOfCharacteristics=bytearray(1),
    # Array length depends on NbOfCharacteristics. Mask: 0xFF. Shift: 0x00.
    Characteristics=GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest.Characteristics(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest(DeviceId, BearerId, NbOfCharacteristics, Characteristics)
    return GATTClientEnhancedReadMultipleVariableCharacteristicValuesOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerRegisterEnhancedCallback(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerRegisterEnhancedCallbackRequest()
    return GATTServerRegisterEnhancedCallbackOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendAttributeWrittenStatus(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    AttributeHandle=bytearray(2),
    Status=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendAttributeWrittenStatusRequest(DeviceId, BearerId, AttributeHandle, Status)
    return GATTServerEnhancedSendAttributeWrittenStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendNotification(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendNotificationRequest(DeviceId, BearerId, Handle)
    return GATTServerEnhancedSendNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendIndication(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Handle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendIndicationRequest(DeviceId, BearerId, Handle)
    return GATTServerEnhancedSendIndicationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendInstantValueNotification(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Handle=bytearray(2),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendInstantValueNotificationRequest(DeviceId, BearerId, Handle, ValueLength, Value)
    return GATTServerEnhancedSendInstantValueNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendInstantValueIndication(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Handle=bytearray(2),
    ValueLength=bytearray(2),
    # Array length depends on ValueLength. Mask: 0xFFFF. Shift: 0x0000.
    Value=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendInstantValueIndicationRequest(DeviceId, BearerId, Handle, ValueLength, Value)
    return GATTServerEnhancedSendInstantValueIndicationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendAttributeReadStatus(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    AttributeHandle=bytearray(2),
    Status=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendAttributeReadStatusRequest(DeviceId, BearerId, AttributeHandle, Status)
    return GATTServerEnhancedSendAttributeReadStatusOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTServerEnhancedSendMultipleHandleValueNotification(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    # Unit length: 3 bytes
    TotalLength=bytearray(3),
    # Array length depends on TotalLength. Mask: 0xFFFF. Shift: 0x0000.
    HandleLengthValueList=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTServerEnhancedSendMultipleHandleValueNotificationRequest(DeviceId, BearerId, TotalLength, HandleLengthValueList)
    return GATTServerEnhancedSendMultipleHandleValueNotificationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTClientGetDatabaseHash(
    device,
    DeviceId=bytearray(1),
    BondIdx=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTClientGetDatabaseHashRequest(DeviceId, BondIdx)
    return GATTClientGetDatabaseHashOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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

def GATTDBDynamicEndDatabaseUpdate(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBDynamicEndDatabaseUpdateRequest()
    return GATTDBDynamicEndDatabaseUpdateOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttFindInformation(
    device,
    DeviceId=bytearray(1),
    Params_StartingHandle=bytearray(2),
    Params_EndingHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttFindInformationRequest(DeviceId, Params_StartingHandle, Params_EndingHandle)
    return GATTDBAttFindInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttFindByTypeValue(
    device,
    DeviceId=bytearray(1),
    Params_StartingHandle=bytearray(2),
    Params_EndingHandle=bytearray(2),
    Params_AttributeType=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFF. Shift: 0x00.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttFindByTypeValueRequest(DeviceId, Params_StartingHandle, Params_EndingHandle, Params_AttributeType, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttFindByTypeValueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttReadByType(
    device,
    DeviceId=bytearray(1),
    Params_StartingHandle=bytearray(2),
    Params_EndingHandle=bytearray(2),
    Params_Format=GATTDBAttReadByTypeRequestParams_Format(),
    # Array length depends on Format. Mask: 0xFF. Shift: 0x00.
    Params_AttributeType=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttReadByTypeRequest(DeviceId, Params_StartingHandle, Params_EndingHandle, Params_Format, Params_AttributeType)
    return GATTDBAttReadByTypeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttRead(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttReadRequest(DeviceId, Params_AttributeHandle)
    return GATTDBAttReadOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttReadBlob(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_ValueOffset=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttReadBlobRequest(DeviceId, Params_AttributeHandle, Params_ValueOffset)
    return GATTDBAttReadBlobOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttReadMultiple(
    device,
    DeviceId=bytearray(1),
    Params_HandleCount=bytearray(2),
    # Array length depends on HandleCount. Mask: 0xFFFF. Shift: 0x0000.
    Params_ListOfHandles=GATTDBAttReadMultipleRequest.Params_ListOfHandles(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttReadMultipleRequest(DeviceId, Params_HandleCount, Params_ListOfHandles)
    return GATTDBAttReadMultipleOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttReadByGroupType(
    device,
    DeviceId=bytearray(1),
    Params_StartingHandle=bytearray(2),
    Params_EndingHandle=bytearray(2),
    Params_Format=GATTDBAttReadByGroupTypeRequestParams_Format(),
    # Array length depends on Format. Mask: 0xFF. Shift: 0x00.
    Params_AttributeType=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttReadByGroupTypeRequest(DeviceId, Params_StartingHandle, Params_EndingHandle, Params_Format, Params_AttributeType)
    return GATTDBAttReadByGroupTypeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttWrite(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttWriteRequest(DeviceId, Params_AttributeHandle, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttWriteOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttWriteCommand(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttWriteCommandRequest(DeviceId, Params_AttributeHandle, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttWriteCommandOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttSignedWriteCommand(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    # Unit length: 12 bytes
    Params_AuthenticationSignature=bytearray(12),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttSignedWriteCommandRequest(DeviceId, Params_AttributeHandle, Params_AttributeLength, Params_AttributeValue, Params_AuthenticationSignature)
    return GATTDBAttSignedWriteCommandOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttPrepareWrite(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_ValueOffset=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttPrepareWriteRequest(DeviceId, Params_AttributeHandle, Params_ValueOffset, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttPrepareWriteOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttExecuteWrite(
    device,
    DeviceId=bytearray(1),
    Params_Flags=GATTDBAttExecuteWriteRequestParams_Flags.gCancel_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttExecuteWriteRequest(DeviceId, Params_Flags)
    return GATTDBAttExecuteWriteOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttExecuteWriteFromQueue(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_ValueOffset=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttExecuteWriteFromQueueRequest(DeviceId, Params_AttributeHandle, Params_ValueOffset, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttExecuteWriteFromQueueOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GATTDBAttPrepareNotificationIndication(
    device,
    DeviceId=bytearray(1),
    Params_AttributeHandle=bytearray(2),
    Params_AttributeLength=bytearray(2),
    # Array length depends on AttributeLength. Mask: 0xFFFF. Shift: 0x0000.
    Params_AttributeValue=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GATTDBAttPrepareNotificationIndicationRequest(DeviceId, Params_AttributeHandle, Params_AttributeLength, Params_AttributeValue)
    return GATTDBAttPrepareNotificationIndicationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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
    request = Frames.GAPSetAdvertisingParametersRequest(AdvertisingParameters_MinInterval, AdvertisingParameters_MaxInterval, AdvertisingParameters_AdvertisingType, AdvertisingParameters_OwnAddressType, AdvertisingParameters_PeerAddressType, AdvertisingParameters_PeerAddress, AdvertisingParameters_ChannelMap, AdvertisingParameters_FilterPolicy)
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

def GAPSendPeripheralSecurityRequest(
    device,
    DeviceId=bytearray(1),
    PairingParameters_WithBonding=False,
    PairingParameters_SecurityModeAndLevel=GAPSendPeripheralSecurityRequestRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c,
    PairingParameters_MaxEncryptionKeySize=bytearray(1),
    PairingParameters_LocalIoCapabilities=GAPSendPeripheralSecurityRequestRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c,
    PairingParameters_OobAvailable=False,
    PairingParameters_CentralKeys=bytearray(1),
    PairingParameters_PeripheralKeys=bytearray(1),
    PairingParameters_LeSecureConnectionSupported=False,
    PairingParameters_UseKeypressNotifications=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSendPeripheralSecurityRequestRequest(DeviceId, PairingParameters_WithBonding, PairingParameters_SecurityModeAndLevel, PairingParameters_MaxEncryptionKeySize, PairingParameters_LocalIoCapabilities, PairingParameters_OobAvailable, PairingParameters_CentralKeys, PairingParameters_PeripheralKeys, PairingParameters_LeSecureConnectionSupported, PairingParameters_UseKeypressNotifications)
    return GAPSendPeripheralSecurityRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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
    request = Frames.GAPAcceptPairingRequestRequest(DeviceId, PairingParameters_WithBonding, PairingParameters_SecurityModeAndLevel, PairingParameters_MaxEncryptionKeySize, PairingParameters_LocalIoCapabilities, PairingParameters_OobAvailable, PairingParameters_CentralKeys, PairingParameters_PeripheralKeys, PairingParameters_LeSecureConnectionSupported, PairingParameters_UseKeypressNotifications)
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
    FilterDuplicates=GAPStartScanningRequestFilterDuplicates(),
    ScanningPHYs=bytearray(1),
    Duration=bytearray(2),
    Period=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStartScanningRequest(ScanningParametersIncluded, ScanningParameters, FilterDuplicates, ScanningPHYs, Duration, Period)
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
    CreateConnectionParameters_Initiating_PHYs=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPConnectRequest(CreateConnectionParameters_ScanInterval, CreateConnectionParameters_ScanWindow, CreateConnectionParameters_FilterPolicy, CreateConnectionParameters_OwnAddressType, CreateConnectionParameters_PeerAddressType, CreateConnectionParameters_PeerAddress, CreateConnectionParameters_ConnIntervalMin, CreateConnectionParameters_ConnIntervalMax, CreateConnectionParameters_ConnLatency, CreateConnectionParameters_SupervisionTimeout, CreateConnectionParameters_ConnEventLengthMin, CreateConnectionParameters_ConnEventLengthMax, CreateConnectionParameters_usePeerIdentityAddress, CreateConnectionParameters_Initiating_PHYs)
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

def GAPReadFilterAcceptListSize(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadFilterAcceptListSizeRequest()
    return GAPReadFilterAcceptListSizeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPClearFilterAcceptList(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPClearFilterAcceptListRequest()
    return GAPClearFilterAcceptListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPAddDeviceToFilterAcceptList(
    device,
    AddressType=GAPAddDeviceToFilterAcceptListRequestAddressType.gPublic_c,
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPAddDeviceToFilterAcceptListRequest(AddressType, Address)
    return GAPAddDeviceToFilterAcceptListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPRemoveDeviceFromFilterAcceptList(
    device,
    AddressType=GAPRemoveDeviceFromFilterAcceptListRequestAddressType.gPublic_c,
    # Unit length: 6 bytes
    Address=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRemoveDeviceFromFilterAcceptListRequest(AddressType, Address)
    return GAPRemoveDeviceFromFilterAcceptListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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
    AutoConnectParams_WriteInFilterAcceptList=False,
    # Array length depends on NbOfAddresses. Mask: 0xFF. Shift: 0x00.
    AutoConnectParams_AutoConnectData=GAPSetScanModeRequest.AutoConnectParams_AutoConnectData(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetScanModeRequest(ScanMode, AutoConnectParams_NbOfAddresses, AutoConnectParams_WriteInFilterAcceptList, AutoConnectParams_AutoConnectData)
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
    PeripheralLatency=bytearray(2),
    TimeoutMultiplier=bytearray(2),
    MinCeLength=bytearray(2),
    MaxCeLength=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPUpdateConnectionParametersRequest(DeviceId, IntervalMin, IntervalMax, PeripheralLatency, TimeoutMultiplier, MinCeLength, MaxCeLength)
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

def ControllerSetScanDupFiltMode(
    device,
    Mode=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.ControllerSetScanDupFiltModeRequest(Mode)
    return ControllerSetScanDupFiltModeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPReadControllerLocalRPA(
    device,
    PeerIdentityAddressType=GAPReadControllerLocalRPARequestPeerIdentityAddressType.gPublic_c,
    # Unit length: 6 bytes
    PeerIdentityAddress=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadControllerLocalRPARequest(PeerIdentityAddressType, PeerIdentityAddress)
    return GAPReadControllerLocalRPAOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPCheckNvmIndex(
    device,
    NvmIndex=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPCheckNvmIndexRequest(NvmIndex)
    return GAPCheckNvmIndexOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPGetDeviceIdFromConnHandle(
    device,
    ConnHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPGetDeviceIdFromConnHandleRequest(ConnHandle)
    return GAPGetDeviceIdFromConnHandleOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPAdvIndexChange(
    device,
    AdvIndexType=GAPAdvIndexChangeRequestAdvIndexType.gAdvIndexAscend_c,
    # Unit length: 3 bytes
    AUserDefinedChannels=bytearray(3),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPAdvIndexChangeRequest(AdvIndexType, AUserDefinedChannels)
    return GAPAdvIndexChangeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetExtAdvertisingParameters(
    device,
    SID=bytearray(1),
    Handle=bytearray(1),
    MinInterval=bytearray(4),
    MaxInterval=bytearray(4),
    OwnAddressType=GAPSetExtAdvertisingParametersRequestOwnAddressType.gPublic_c,
    # Unit length: 6 bytes
    OwnRandomAddress=bytearray(6),
    PeerAddressType=GAPSetExtAdvertisingParametersRequestPeerAddressType.gPublic_c,
    # Unit length: 6 bytes
    PeerAddress=bytearray(6),
    ChannelMap=bytearray(1),
    FilterPolicy=GAPSetExtAdvertisingParametersRequestFilterPolicy.gProcessAll_c,
    AdvProperties=bytearray(2),
    AdvTxPowerLevel=bytearray(1),
    PrimaryAdvPHY=GAPSetExtAdvertisingParametersRequestPrimaryAdvPHY.gLePhy1M_c,
    SecondaryAdvPHY=GAPSetExtAdvertisingParametersRequestSecondaryAdvPHY.gLePhy1M_c,
    SecondaryAdvMaxSkip=bytearray(1),
    EnableScanReqNotification=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetExtAdvertisingParametersRequest(SID, Handle, MinInterval, MaxInterval, OwnAddressType, OwnRandomAddress, PeerAddressType, PeerAddress, ChannelMap, FilterPolicy, AdvProperties, AdvTxPowerLevel, PrimaryAdvPHY, SecondaryAdvPHY, SecondaryAdvMaxSkip, EnableScanReqNotification)
    return GAPSetExtAdvertisingParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPStartExtAdvertising(
    device,
    Handle=bytearray(1),
    Duration=bytearray(2),
    MaxExtAdvEvents=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStartExtAdvertisingRequest(Handle, Duration, MaxExtAdvEvents)
    return GAPStartExtAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPRemoveAdvertisingSet(
    device,
    Handle=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPRemoveAdvertisingSetRequest(Handle)
    return GAPRemoveAdvertisingSetOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPStopExtAdvertising(
    device,
    Handle=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStopExtAdvertisingRequest(Handle)
    return GAPStopExtAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPUpdatePeriodicAdvList(
    device,
    Operation=GAPUpdatePeriodicAdvListRequestOperation.gAddDevice_c,
    # Array length depends on Operation. Mask: 0xFF. Shift: 0x00.
    OperationValue=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPUpdatePeriodicAdvListRequest(Operation, OperationValue)
    return GAPUpdatePeriodicAdvListOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetPeriodicAdvParameters(
    device,
    Handle=bytearray(1),
    IncludeTxPower=False,
    MinInterval=bytearray(2),
    MaxInterval=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetPeriodicAdvParametersRequest(Handle, IncludeTxPower, MinInterval, MaxInterval)
    return GAPSetPeriodicAdvParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPStartPeriodicAdvertising(
    device,
    Handle=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStartPeriodicAdvertisingRequest(Handle)
    return GAPStartPeriodicAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPStopPeriodicAdvertising(
    device,
    Handle=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPStopPeriodicAdvertisingRequest(Handle)
    return GAPStopPeriodicAdvertisingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetExtAdvertisingData(
    device,
    Handle=bytearray(1),
    AdvertisingDataIncluded=False,
    # Array length depends on AdvertisingDataIncluded. Mask: 0xFF. Shift: 0x00.
    ExtAdvertisingData=GAPSetExtAdvertisingDataRequest.ExtAdvertisingData(),
    ScanResponseDataIncluded=False,
    # Array length depends on ScanResponseDataIncluded. Mask: 0xFF. Shift: 0x00.
    ExtScanResponseData=GAPSetExtAdvertisingDataRequest.ExtScanResponseData(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetExtAdvertisingDataRequest(Handle, AdvertisingDataIncluded, ExtAdvertisingData, ScanResponseDataIncluded, ExtScanResponseData)
    return GAPSetExtAdvertisingDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetPeriodicAdvertisingData(
    device,
    Handle=bytearray(1),
    PeriodicAdvertisingData_NbOfAdStructures=bytearray(1),
    # Array length depends on NbOfAdStructures. Mask: 0xFF. Shift: 0x00.
    PeriodicAdvertisingData_AdStructures=GAPSetPeriodicAdvertisingDataRequest.PeriodicAdvertisingData_AdStructures(),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetPeriodicAdvertisingDataRequest(Handle, PeriodicAdvertisingData_NbOfAdStructures, PeriodicAdvertisingData_AdStructures)
    return GAPSetPeriodicAdvertisingDataOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvCreateSync(
    device,
    Options=bytearray(1),
    SID=bytearray(1),
    DeviceAddressType=GAPPeriodicAdvCreateSyncRequestDeviceAddressType.gPublic_c,
    # Unit length: 6 bytes
    DeviceAddress=bytearray(6),
    SkipCount=bytearray(2),
    Timeout=bytearray(2),
    SyncCteType=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvCreateSyncRequest(Options, SID, DeviceAddressType, DeviceAddress, SkipCount, Timeout, SyncCteType)
    return GAPPeriodicAdvCreateSyncOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvTerminateSync(
    device,
    SyncHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvTerminateSyncRequest(SyncHandle)
    return GAPPeriodicAdvTerminateSyncOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPGenerateDHKeyV2(
    device,
    # Unit length: 64 bytes
    RemoteP256PublicKey=bytearray(64),
    PrivateKeyType=GAPGenerateDHKeyV2RequestPrivateKeyType.UseGeneratedKey,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPGenerateDHKeyV2Request(RemoteP256PublicKey, PrivateKeyType)
    return GAPGenerateDHKeyV2Operation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPModifySleepClockAccuracy(
    device,
    Action=GAPModifySleepClockAccuracyRequestAction.SwitchToMoreAccurateClock,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPModifySleepClockAccuracyRequest(Action)
    return GAPModifySleepClockAccuracyOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def ControllerConfigureAdvCodingScheme(
    device,
    CodingScheme=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.ControllerConfigureAdvCodingSchemeRequest(CodingScheme)
    return ControllerConfigureAdvCodingSchemeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetConnectionlessCteTransmitParameters(
    device,
    pTransmitParams_Handle=bytearray(1),
    pTransmitParams_CteLength=bytearray(1),
    pTransmitParams_CteType=GAPSetConnectionlessCteTransmitParametersRequestpTransmitParams_CteType.gCteTypeAoA_c,
    pTransmitParams_CteCount=bytearray(1),
    pTransmitParams_SwitchingPatternLength=bytearray(1),
    # Array length depends on SwitchingPatternLength. Mask: 0xFF. Shift: 0x00.
    pTransmitParams_AntennaIds=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetConnectionlessCteTransmitParametersRequest(pTransmitParams_Handle, pTransmitParams_CteLength, pTransmitParams_CteType, pTransmitParams_CteCount, pTransmitParams_SwitchingPatternLength, pTransmitParams_AntennaIds)
    return GAPSetConnectionlessCteTransmitParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnableConnectionlessCteTransmit(
    device,
    Handle=bytearray(1),
    Enable=GAPEnableConnectionlessCteTransmitRequestEnable.gCteTransmitDisable_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableConnectionlessCteTransmitRequest(Handle, Enable)
    return GAPEnableConnectionlessCteTransmitOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnableConnectionlessIqSampling(
    device,
    SyncHandle=bytearray(2),
    pIqSamplingParams_IqSamplingEnable=GAPEnableConnectionlessIqSamplingRequestpIqSamplingParams_IqSamplingEnable.gIqSamplingDisable_c,
    pIqSamplingParams_SlotDurations=GAPEnableConnectionlessIqSamplingRequestpIqSamplingParams_SlotDurations.gSlotDurations1us_c,
    pIqSamplingParams_MaxSampledCtes=bytearray(1),
    pIqSamplingParams_SwitchingPatternLength=bytearray(1),
    # Array length depends on SwitchingPatternLength. Mask: 0xFF. Shift: 0x00.
    pIqSamplingParams_AntennaIds=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableConnectionlessIqSamplingRequest(SyncHandle, pIqSamplingParams_IqSamplingEnable, pIqSamplingParams_SlotDurations, pIqSamplingParams_MaxSampledCtes, pIqSamplingParams_SwitchingPatternLength, pIqSamplingParams_AntennaIds)
    return GAPEnableConnectionlessIqSamplingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetConnectionCteReceiveParameters(
    device,
    DeviceId=bytearray(1),
    pReceiveParams_IqSamplingEnable=GAPSetConnectionCteReceiveParametersRequestpReceiveParams_IqSamplingEnable.gIqSamplingDisable_c,
    pReceiveParams_SlotDurations=GAPSetConnectionCteReceiveParametersRequestpReceiveParams_SlotDurations.gSlotDurations1us_c,
    pReceiveParams_SwitchingPatternLength=bytearray(1),
    # Array length depends on SwitchingPatternLength. Mask: 0xFF. Shift: 0x00.
    pReceiveParams_AntennaIds=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetConnectionCteReceiveParametersRequest(DeviceId, pReceiveParams_IqSamplingEnable, pReceiveParams_SlotDurations, pReceiveParams_SwitchingPatternLength, pReceiveParams_AntennaIds)
    return GAPSetConnectionCteReceiveParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetConnectionCteTransmitParameters(
    device,
    DeviceId=bytearray(1),
    pTransmitParams_CteTypes=bytearray(1),
    pTransmitParams_SwitchingPatternLength=bytearray(1),
    # Array length depends on SwitchingPatternLength. Mask: 0xFF. Shift: 0x00.
    pTransmitParams_AntennaIds=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetConnectionCteTransmitParametersRequest(DeviceId, pTransmitParams_CteTypes, pTransmitParams_SwitchingPatternLength, pTransmitParams_AntennaIds)
    return GAPSetConnectionCteTransmitParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnableConnectionCteRequest(
    device,
    DeviceId=bytearray(1),
    pCteReqEnableParams_CteReqEnable=GAPEnableConnectionCteRequestRequestpCteReqEnableParams_CteReqEnable.gCteReqDisable_c,
    pCteReqEnableParams_CteReqInterval=bytearray(2),
    pCteReqEnableParams_RequestedCteLength=bytearray(1),
    pCteReqEnableParams_RequestedCteType=GAPEnableConnectionCteRequestRequestpCteReqEnableParams_RequestedCteType.gCteTypeAoA_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableConnectionCteRequestRequest(DeviceId, pCteReqEnableParams_CteReqEnable, pCteReqEnableParams_CteReqInterval, pCteReqEnableParams_RequestedCteLength, pCteReqEnableParams_RequestedCteType)
    return GAPEnableConnectionCteRequestOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnableConnectionCteResponse(
    device,
    DeviceId=bytearray(1),
    Enable=GAPEnableConnectionCteResponseRequestEnable.gCteRspDisable_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableConnectionCteResponseRequest(DeviceId, Enable)
    return GAPEnableConnectionCteResponseOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPReadAntennaInformation(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadAntennaInformationRequest()
    return GAPReadAntennaInformationOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def WritePublicDeviceAddress(
    device,
    CPUReset=False,
    # Unit length: 6 bytes
    BluetoothAddress=bytearray(6),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.WritePublicDeviceAddressRequest(CPUReset, BluetoothAddress)
    return WritePublicDeviceAddressOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvReceiveEnable(
    device,
    SyncHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvReceiveEnableRequest(SyncHandle)
    return GAPPeriodicAdvReceiveEnableOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvReceiveDisable(
    device,
    SyncHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvReceiveDisableRequest(SyncHandle)
    return GAPPeriodicAdvReceiveDisableOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvSyncTransfer(
    device,
    DeviceId=bytearray(1),
    ServiceData=bytearray(2),
    SyncHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvSyncTransferRequest(DeviceId, ServiceData, SyncHandle)
    return GAPPeriodicAdvSyncTransferOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPPeriodicAdvSetInfoTransfer(
    device,
    DeviceId=bytearray(1),
    ServiceData=bytearray(2),
    AdvHandle=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPPeriodicAdvSetInfoTransferRequest(DeviceId, ServiceData, AdvHandle)
    return GAPPeriodicAdvSetInfoTransferOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetPeriodicAdvSyncTransferParams(
    device,
    DeviceId=bytearray(1),
    Mode=GAPSetPeriodicAdvSyncTransferParamsRequestMode(),
    Skip=bytearray(2),
    SyncTimeout=bytearray(2),
    CTEType=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetPeriodicAdvSyncTransferParamsRequest(DeviceId, Mode, Skip, SyncTimeout, CTEType)
    return GAPSetPeriodicAdvSyncTransferParamsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetDefaultPeriodicAdvSyncTransferParams(
    device,
    DeviceId=bytearray(1),
    Mode=GAPSetDefaultPeriodicAdvSyncTransferParamsRequestMode(),
    Skip=bytearray(2),
    SyncTimeout=bytearray(2),
    CTEType=bytearray(1),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetDefaultPeriodicAdvSyncTransferParamsRequest(DeviceId, Mode, Skip, SyncTimeout, CTEType)
    return GAPSetDefaultPeriodicAdvSyncTransferParamsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnhancedReadTransmitPowerLevel(
    device,
    DeviceId=bytearray(1),
    Phy=GAPEnhancedReadTransmitPowerLevelRequestPhy.gPowerControlLePhy1M_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnhancedReadTransmitPowerLevelRequest(DeviceId, Phy)
    return GAPEnhancedReadTransmitPowerLevelOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPReadRemoteTransmitPowerLevel(
    device,
    DeviceId=bytearray(1),
    Phy=GAPReadRemoteTransmitPowerLevelRequestPhy.gPowerControlLePhy1M_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPReadRemoteTransmitPowerLevelRequest(DeviceId, Phy)
    return GAPReadRemoteTransmitPowerLevelOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPSetPathLossReportingParameters(
    device,
    DeviceId=bytearray(1),
    pPathLossReportingParams_HighThreshold=bytearray(1),
    pPathLossReportingParams_HighHysteresis=bytearray(1),
    pPathLossReportingParams_LowThreshold=bytearray(1),
    pPathLossReportingParams_LowHysteresis=bytearray(1),
    pPathLossReportingParams_minTimeSpent=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPSetPathLossReportingParametersRequest(DeviceId, pPathLossReportingParams_HighThreshold, pPathLossReportingParams_HighHysteresis, pPathLossReportingParams_LowThreshold, pPathLossReportingParams_LowHysteresis, pPathLossReportingParams_minTimeSpent)
    return GAPSetPathLossReportingParametersOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnablePathLossReporting(
    device,
    DeviceId=bytearray(1),
    Enable=GAPEnablePathLossReportingRequestEnable.gPathLossReportingDisable_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnablePathLossReportingRequest(DeviceId, Enable)
    return GAPEnablePathLossReportingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEnableTransmitPowerReporting(
    device,
    DeviceId=bytearray(1),
    LocalEnable=GAPEnableTransmitPowerReportingRequestLocalEnable.gTxPowerReportingDisable_c,
    RemoteEnable=GAPEnableTransmitPowerReportingRequestRemoteEnable.gTxPowerReportingDisable_c,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEnableTransmitPowerReportingRequest(DeviceId, LocalEnable, RemoteEnable)
    return GAPEnableTransmitPowerReportingOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEattConnection(
    device,
    DeviceId=bytearray(1),
    MTU=bytearray(2),
    NoOfBearers=bytearray(1),
    InitialCredits=bytearray(2),
    AutoCreditsMgmt=False,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEattConnectionRequest(DeviceId, MTU, NoOfBearers, InitialCredits, AutoCreditsMgmt)
    return GAPEattConnectionOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEattReconfigure(
    device,
    DeviceId=bytearray(1),
    MTU=bytearray(2),
    MPS=bytearray(2),
    NoOfBearers=bytearray(1),
    # Array length depends on NoOfBearers. Mask: 0xFF. Shift: .
    BearerIds=[],
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEattReconfigureRequest(DeviceId, MTU, MPS, NoOfBearers, BearerIds)
    return GAPEattReconfigureOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def GAPEattSendCredits(
    device,
    DeviceId=bytearray(1),
    BearerId=bytearray(1),
    Credits=bytearray(2),
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.GAPEattSendCreditsRequest(DeviceId, BearerId, Credits)
    return GAPEattSendCreditsOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

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

def FSCIGetNbuVersion(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCIGetNbuVersionRequest()
    return FSCIGetNbuVersionOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

def FSCINVGetNvVPSize(
    device,
    ack_policy=FsciAckPolicy.GLOBAL,
    protocol=Protocol.BLE,
    timeout=1
):
    request = Frames.FSCINVGetNvVPSizeRequest()
    return FSCINVGetNvVPSizeOperation(device, request, ack_policy=ack_policy, protocol=protocol, sync_request=True).begin(timeout)

