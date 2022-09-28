'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.ble.enums import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.hsdk.utils import list_to_int, to_bytes


from com.nxp.wireless_connectivity.commands.ble.enums import ValueUuidType as UuidType




class L2CAPCBRegisterLeCbCallbacksRequest(object):

    pass


class L2CAPCBRegisterLePsmRequest(object):

    def __init__(self, LePsm=bytearray(2), LePsmMtu=bytearray(2)):
        '''
        @param LePsm: Bluetooth SIG or Vendor LE_PSM
        @param LePsmMtu: MTU value
        '''
        self.LePsm = LePsm
        self.LePsmMtu = LePsmMtu


class L2CAPCBDeregisterLePsmRequest(object):

    def __init__(self, LePsm=bytearray(2)):
        '''
        @param LePsm: Bluetooth SIG or Vendor LE_PSM
        '''
        self.LePsm = LePsm


class L2CAPCBConnectLePsmRequest(object):

    def __init__(self, LePsm=bytearray(2), DeviceId=bytearray(1), InitialCredits=bytearray(2)):
        '''
        @param LePsm: Bluetooth SIG or Vendor LE_PSM
        @param DeviceId: The DeviceId for which the command is intended
        @param InitialCredits: Initial credits
        '''
        self.LePsm = LePsm
        self.DeviceId = DeviceId
        self.InitialCredits = InitialCredits


class L2CAPCBDisconnectLeCbChannelRequest(object):

    def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2)):
        '''
        @param DeviceId: The DeviceId for which the command is intended
        @param ChannelId: The L2CAP Channel Id assigned on the initiator
        '''
        self.DeviceId = DeviceId
        self.ChannelId = ChannelId


class L2CAPCBCancelConnectionRequest(object):

    def __init__(self, LePsm=bytearray(2), DeviceId=bytearray(1), RefuseReason=L2CAPCBCancelConnectionRequestRefuseReason.gSuccessful_c):
        '''
        @param LePsm: Bluetooth SIG or Vendor LE_PSM
        @param DeviceId: The DeviceId for which the command is intended
        @param RefuseReason: Refuse reason
        '''
        self.LePsm = LePsm
        self.DeviceId = DeviceId
        self.RefuseReason = RefuseReason


class L2CAPCBSendLeCbDataRequest(object):

    def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2), PacketLength=bytearray(2), Packet=[]):
        '''
        @param DeviceId: The DeviceId for which the command is intended
        @param ChannelId: The L2CAP Channel Id assigned on the initiator
        @param PacketLength: Length of the data packet to be sent
        @param Packet: The data packet to be transmitted
        '''
        self.DeviceId = DeviceId
        self.ChannelId = ChannelId
        self.PacketLength = PacketLength
        self.Packet = Packet


class L2CAPCBSendLeCreditRequest(object):

    def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2), Credits=bytearray(2)):
        '''
        @param DeviceId: The DeviceID to which credits are given
        @param ChannelId: The L2CAP Channel Id assigned on the initiator
        @param Credits: Number of credits to be given
        '''
        self.DeviceId = DeviceId
        self.ChannelId = ChannelId
        self.Credits = Credits






class GATTInitRequest(object):

    pass


class GATTGetMtuRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        '''
        self.DeviceId = DeviceId


class GATTClientInitRequest(object):

    pass


class GATTClientResetProcedureRequest(object):

    pass


class GATTClientRegisterProcedureCallbackRequest(object):

    pass


class GATTClientRegisterNotificationCallbackRequest(object):

    pass


class GATTClientRegisterIndicationCallbackRequest(object):

    pass


class GATTClientExchangeMtuRequest(object):

    def __init__(self, DeviceId=bytearray(1), Mtu=bytearray(2)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Mtu: Desired MTU size for the connected peer
        '''
        self.DeviceId = DeviceId
        self.Mtu = Mtu


class GATTClientDiscoverAllPrimaryServicesRequest(object):

    def __init__(self, DeviceId=bytearray(1), MaxNbOfServices=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param MaxNbOfServices: Maximum number of services to be filled
        '''
        self.DeviceId = DeviceId
        self.MaxNbOfServices = MaxNbOfServices


class GATTClientDiscoverPrimaryServicesByUuidRequest(object):

    def __init__(self, DeviceId=bytearray(1), UuidType=GATTClientDiscoverPrimaryServicesByUuidRequestUuidType.Uuid16Bits, Uuid=[], MaxNbOfServices=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param MaxNbOfServices: Maximum number of services to be filled
        '''
        self.DeviceId = DeviceId
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.MaxNbOfServices = MaxNbOfServices


class GATTClientFindIncludedServicesRequest(object):

    class Service_Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        def __init__(self, Properties=Service_CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Properties, 1)
            result += self.Value.pickle()
            result += to_bytes(self.NbOfDescriptors, 1)
            for i in range(list_to_int(self.NbOfDescriptors, False)):
                result += self.Descriptors[i].pickle()
            return result

    class Service_IncludedServices(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=Service_IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            self.NbOfIncludedServices = NbOfIncludedServices

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.StartHandle, 2)
            result += to_bytes(self.EndHandle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.NbOfCharacteristics, 1)
            result += to_bytes(self.NbOfIncludedServices, 1)
            return result

    def __init__(self, DeviceId=bytearray(1), Service_StartHandle=bytearray(2), Service_EndHandle=bytearray(2), Service_UuidType=GATTClientFindIncludedServicesRequestService_UuidType.Uuid16Bits, Service_Uuid=[], Service_NbOfCharacteristics=bytearray(1), Service_Characteristics=[], Service_NbOfIncludedServices=bytearray(1), Service_IncludedServices=[], MaxNbOfIncludedServices=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Service_StartHandle: The handle of the Service Declaration attribute
        @param Service_EndHandle: The last handle belonging to this Service (followed by another Service declaration of the end of the database)
        @param Service_UuidType: UUID type
        @param Service_Uuid: UUID value
        @param Service_NbOfCharacteristics: Size of the Characteristic array
        @param Service_Characteristics: Characteristic array
        @param Service_NbOfIncludedServices: Size of the Included Services array
        @param Service_IncludedServices: Included Services array
        @param MaxNbOfIncludedServices: Maximum number of included services to be filled
        '''
        self.DeviceId = DeviceId
        self.Service_StartHandle = Service_StartHandle
        self.Service_EndHandle = Service_EndHandle
        self.Service_UuidType = Service_UuidType
        self.Service_Uuid = Service_Uuid
        self.Service_NbOfCharacteristics = Service_NbOfCharacteristics
        self.Service_Characteristics = Service_Characteristics
        self.Service_NbOfIncludedServices = Service_NbOfIncludedServices
        self.Service_IncludedServices = Service_IncludedServices
        self.MaxNbOfIncludedServices = MaxNbOfIncludedServices

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Service_StartHandle, 2)
        result += to_bytes(self.Service_EndHandle, 2)
        result += to_bytes(self.Service_UuidType, 1)
        if self.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        if self.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        if self.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        result += to_bytes(self.Service_Uuid, selected_len)
        result += to_bytes(self.Service_NbOfCharacteristics, 1)
        for i in range(list_to_int(self.Service_NbOfCharacteristics, False)):
            result += self.Service_Characteristics[i].pickle()
        result += to_bytes(self.Service_NbOfIncludedServices, 1)
        for i in range(list_to_int(self.Service_NbOfIncludedServices, False)):
            result += self.Service_IncludedServices[i].pickle()
        result += to_bytes(self.MaxNbOfIncludedServices, 1)
        return result


class GATTClientDiscoverAllCharacteristicsOfServiceRequest(object):

    class Service_Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        def __init__(self, Properties=Service_CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Properties, 1)
            result += self.Value.pickle()
            result += to_bytes(self.NbOfDescriptors, 1)
            for i in range(list_to_int(self.NbOfDescriptors, False)):
                result += self.Descriptors[i].pickle()
            return result

    class Service_IncludedServices(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=Service_IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            self.NbOfIncludedServices = NbOfIncludedServices

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.StartHandle, 2)
            result += to_bytes(self.EndHandle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.NbOfCharacteristics, 1)
            result += to_bytes(self.NbOfIncludedServices, 1)
            return result

    def __init__(self, DeviceId=bytearray(1), Service_StartHandle=bytearray(2), Service_EndHandle=bytearray(2), Service_UuidType=GATTClientDiscoverAllCharacteristicsOfServiceRequestService_UuidType.Uuid16Bits, Service_Uuid=[], Service_NbOfCharacteristics=bytearray(1), Service_Characteristics=[], Service_NbOfIncludedServices=bytearray(1), Service_IncludedServices=[], MaxNbOfCharacteristics=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Service_StartHandle: The handle of the Service Declaration attribute
        @param Service_EndHandle: The last handle belonging to this Service (followed by another Service declaration of the end of the database)
        @param Service_UuidType: UUID type
        @param Service_Uuid: UUID value
        @param Service_NbOfCharacteristics: Size of the Characteristic array
        @param Service_Characteristics: Characteristic array
        @param Service_NbOfIncludedServices: Size of the Included Services array
        @param Service_IncludedServices: Included Services array
        @param MaxNbOfCharacteristics: Maximum number of characteristics to be filled
        '''
        self.DeviceId = DeviceId
        self.Service_StartHandle = Service_StartHandle
        self.Service_EndHandle = Service_EndHandle
        self.Service_UuidType = Service_UuidType
        self.Service_Uuid = Service_Uuid
        self.Service_NbOfCharacteristics = Service_NbOfCharacteristics
        self.Service_Characteristics = Service_Characteristics
        self.Service_NbOfIncludedServices = Service_NbOfIncludedServices
        self.Service_IncludedServices = Service_IncludedServices
        self.MaxNbOfCharacteristics = MaxNbOfCharacteristics

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Service_StartHandle, 2)
        result += to_bytes(self.Service_EndHandle, 2)
        result += to_bytes(self.Service_UuidType, 1)
        if self.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        if self.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        if self.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        result += to_bytes(self.Service_Uuid, selected_len)
        result += to_bytes(self.Service_NbOfCharacteristics, 1)
        for i in range(list_to_int(self.Service_NbOfCharacteristics, False)):
            result += self.Service_Characteristics[i].pickle()
        result += to_bytes(self.Service_NbOfIncludedServices, 1)
        for i in range(list_to_int(self.Service_NbOfIncludedServices, False)):
            result += self.Service_IncludedServices[i].pickle()
        result += to_bytes(self.MaxNbOfCharacteristics, 1)
        return result


class GATTClientDiscoverCharacteristicOfServiceByUuidRequest(object):

    class Service_Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        def __init__(self, Properties=Service_CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Properties, 1)
            result += self.Value.pickle()
            result += to_bytes(self.NbOfDescriptors, 1)
            for i in range(list_to_int(self.NbOfDescriptors, False)):
                result += self.Descriptors[i].pickle()
            return result

    class Service_IncludedServices(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=Service_IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            self.NbOfIncludedServices = NbOfIncludedServices

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.StartHandle, 2)
            result += to_bytes(self.EndHandle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.NbOfCharacteristics, 1)
            result += to_bytes(self.NbOfIncludedServices, 1)
            return result

    def __init__(self, DeviceId=bytearray(1), UuidType=GATTClientDiscoverCharacteristicOfServiceByUuidRequestUuidType.Uuid16Bits, Uuid=[], Service_StartHandle=bytearray(2), Service_EndHandle=bytearray(2), Service_UuidType=GATTClientDiscoverCharacteristicOfServiceByUuidRequestService_UuidType.Uuid16Bits, Service_Uuid=[], Service_NbOfCharacteristics=bytearray(1), Service_Characteristics=[], Service_NbOfIncludedServices=bytearray(1), Service_IncludedServices=[], MaxNbOfCharacteristics=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param Service_StartHandle: The handle of the Service Declaration attribute
        @param Service_EndHandle: The last handle belonging to this Service (followed by another Service declaration of the end of the database)
        @param Service_UuidType: UUID type
        @param Service_Uuid: UUID value
        @param Service_NbOfCharacteristics: Size of the Characteristic array
        @param Service_Characteristics: Characteristic array
        @param Service_NbOfIncludedServices: Size of the Included Services array
        @param Service_IncludedServices: Included Services array
        @param MaxNbOfCharacteristics: Maximum number of characteristics to be filled
        '''
        self.DeviceId = DeviceId
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.Service_StartHandle = Service_StartHandle
        self.Service_EndHandle = Service_EndHandle
        self.Service_UuidType = Service_UuidType
        self.Service_Uuid = Service_Uuid
        self.Service_NbOfCharacteristics = Service_NbOfCharacteristics
        self.Service_Characteristics = Service_Characteristics
        self.Service_NbOfIncludedServices = Service_NbOfIncludedServices
        self.Service_IncludedServices = Service_IncludedServices
        self.MaxNbOfCharacteristics = MaxNbOfCharacteristics

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.UuidType, 1)
        if self.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        if self.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        if self.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        result += to_bytes(self.Uuid, selected_len)
        result += to_bytes(self.Service_StartHandle, 2)
        result += to_bytes(self.Service_EndHandle, 2)
        result += to_bytes(self.Service_UuidType, 1)
        if self.Service_UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        if self.Service_UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        if self.Service_UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        result += to_bytes(self.Service_Uuid, selected_len)
        result += to_bytes(self.Service_NbOfCharacteristics, 1)
        for i in range(list_to_int(self.Service_NbOfCharacteristics, False)):
            result += self.Service_Characteristics[i].pickle()
        result += to_bytes(self.Service_NbOfIncludedServices, 1)
        for i in range(list_to_int(self.Service_NbOfIncludedServices, False)):
            result += self.Service_IncludedServices[i].pickle()
        result += to_bytes(self.MaxNbOfCharacteristics, 1)
        return result


class GATTClientDiscoverAllCharacteristicDescriptorsRequest(object):

    class Characteristic_Value(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    class Characteristic_Descriptors(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    def __init__(self, DeviceId=bytearray(1), Characteristic_Properties=GATTClientDiscoverAllCharacteristicDescriptorsRequestCharacteristic_Properties.gNone_c, Characteristic_Value=Characteristic_Value(), Characteristic_NbOfDescriptors=bytearray(1), Characteristic_Descriptors=[], EndingHandle=bytearray(2), MaxNbOfDescriptors=bytearray(1)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Characteristic_Properties: Characteristic Properties as defined by GATT
        @param Characteristic_Value: Characteristic Value attribute
        @param Characteristic_NbOfDescriptors: Size of the Characteristic Descriptors array
        @param Characteristic_Descriptors: Characteristic Descriptors array
        @param EndingHandle: The last handle of the Characteristic
        @param MaxNbOfDescriptors: Maximum number of descriptors to be filled
        '''
        self.DeviceId = DeviceId
        self.Characteristic_Properties = Characteristic_Properties
        self.Characteristic_Value = Characteristic_Value
        self.Characteristic_NbOfDescriptors = Characteristic_NbOfDescriptors
        self.Characteristic_Descriptors = Characteristic_Descriptors
        self.EndingHandle = EndingHandle
        self.MaxNbOfDescriptors = MaxNbOfDescriptors

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Characteristic_Properties, 1)
        result += self.Characteristic_Value.pickle()
        result += to_bytes(self.Characteristic_NbOfDescriptors, 1)
        for i in range(list_to_int(self.Characteristic_NbOfDescriptors, False)):
            result += self.Characteristic_Descriptors[i].pickle()
        result += to_bytes(self.EndingHandle, 2)
        result += to_bytes(self.MaxNbOfDescriptors, 1)
        return result


class GATTClientReadCharacteristicValueRequest(object):

    class Characteristic_Value(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    class Characteristic_Descriptors(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    def __init__(self, DeviceId=bytearray(1), Characteristic_Properties=GATTClientReadCharacteristicValueRequestCharacteristic_Properties.gNone_c, Characteristic_Value=Characteristic_Value(), Characteristic_NbOfDescriptors=bytearray(1), Characteristic_Descriptors=[], MaxReadBytes=bytearray(2)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Characteristic_Properties: Characteristic Properties as defined by GATT
        @param Characteristic_Value: Characteristic Value attribute
        @param Characteristic_NbOfDescriptors: Size of the Characteristic Descriptors array
        @param Characteristic_Descriptors: Characteristic Descriptors array
        @param MaxReadBytes: Maximum number of bytes to be read
        '''
        self.DeviceId = DeviceId
        self.Characteristic_Properties = Characteristic_Properties
        self.Characteristic_Value = Characteristic_Value
        self.Characteristic_NbOfDescriptors = Characteristic_NbOfDescriptors
        self.Characteristic_Descriptors = Characteristic_Descriptors
        self.MaxReadBytes = MaxReadBytes

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Characteristic_Properties, 1)
        result += self.Characteristic_Value.pickle()
        result += to_bytes(self.Characteristic_NbOfDescriptors, 1)
        for i in range(list_to_int(self.Characteristic_NbOfDescriptors, False)):
            result += self.Characteristic_Descriptors[i].pickle()
        result += to_bytes(self.MaxReadBytes, 2)
        return result


class GATTClientReadUsingCharacteristicUuidRequest(object):

    class HandleRange(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.StartHandle, 2)
            result += to_bytes(self.EndHandle, 2)
            return result

    def __init__(self, DeviceId=bytearray(1), UuidType=GATTClientReadUsingCharacteristicUuidRequestUuidType.Uuid16Bits, Uuid=[], HandleRangeIncluded=bytearray(1), HandleRange=HandleRange(), MaxReadBytes=bytearray(2)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param HandleRangeIncluded: Boolean value which indicates if handle range is included or not
        @param HandleRange: Handle range for the search
        @param MaxReadBytes: Maximum number of bytes to be read
        '''
        self.DeviceId = DeviceId
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.HandleRangeIncluded = HandleRangeIncluded
        self.HandleRange = HandleRange
        self.MaxReadBytes = MaxReadBytes

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.UuidType, 1)
        if self.UuidType == UuidType.Uuid16Bits:
            selected_len = 2
        if self.UuidType == UuidType.Uuid128Bits:
            selected_len = 16
        if self.UuidType == UuidType.Uuid32Bits:
            selected_len = 4
        result += to_bytes(self.Uuid, selected_len)
        result += to_bytes(self.HandleRangeIncluded, 1)
        if self.HandleRangeIncluded:
            result += self.HandleRange.pickle()
        result += to_bytes(self.MaxReadBytes, 2)
        return result


class GATTClientReadMultipleCharacteristicValuesRequest(object):

    class Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Handle, 2)
                result += to_bytes(self.UuidType, 1)
                if self.UuidType == UuidType.Uuid16Bits:
                    selected_len = 2
                if self.UuidType == UuidType.Uuid128Bits:
                    selected_len = 16
                if self.UuidType == UuidType.Uuid32Bits:
                    selected_len = 4
                result += to_bytes(self.Uuid, selected_len)
                result += to_bytes(self.ValueLength, 2)
                result += to_bytes(self.MaxValueLength, 2)
                result += to_bytes(self.Value, self.ValueLength)
                return result

        def __init__(self, Properties=CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Properties, 1)
            result += self.Value.pickle()
            result += to_bytes(self.NbOfDescriptors, 1)
            for i in range(list_to_int(self.NbOfDescriptors, False)):
                result += self.Descriptors[i].pickle()
            return result

    def __init__(self, DeviceId=bytearray(1), NbOfCharacteristics=bytearray(1), Characteristics=[]):
        '''
        @param DeviceId: Device ID of the connected peer
        @param NbOfCharacteristics: Number of characteristics in the array
        @param Characteristics: Array of the characteristics whose values are to be read
        '''
        self.DeviceId = DeviceId
        self.NbOfCharacteristics = NbOfCharacteristics
        self.Characteristics = Characteristics

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.NbOfCharacteristics, 1)
        for i in range(list_to_int(self.NbOfCharacteristics, False)):
            result += self.Characteristics[i].pickle()
        return result


class GATTClientWriteCharacteristicValueRequest(object):

    class Characteristic_Value(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    class Characteristic_Descriptors(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            result += to_bytes(self.UuidType, 1)
            if self.UuidType == UuidType.Uuid16Bits:
                selected_len = 2
            if self.UuidType == UuidType.Uuid128Bits:
                selected_len = 16
            if self.UuidType == UuidType.Uuid32Bits:
                selected_len = 4
            result += to_bytes(self.Uuid, selected_len)
            result += to_bytes(self.ValueLength, 2)
            result += to_bytes(self.MaxValueLength, 2)
            result += to_bytes(self.Value, self.ValueLength)
            return result

    def __init__(self, DeviceId=bytearray(1), Characteristic_Properties=GATTClientWriteCharacteristicValueRequestCharacteristic_Properties.gNone_c, Characteristic_Value=Characteristic_Value(), Characteristic_NbOfDescriptors=bytearray(1), Characteristic_Descriptors=[], ValueLength=bytearray(2), Value=[], WithoutResponse=bytearray(1), SignedWrite=bytearray(1), ReliableLongCharWrites=bytearray(1), Csrk=bytearray(16)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Characteristic_Properties: Characteristic Properties as defined by GATT
        @param Characteristic_Value: Characteristic Value attribute
        @param Characteristic_NbOfDescriptors: Size of the Characteristic Descriptors array
        @param Characteristic_Descriptors: Characteristic Descriptors array
        @param ValueLength: Number of bytes to be written
        @param Value: Array of bytes to be written
        @param WithoutResponse: Indicates if a Write Command will be used
        @param SignedWrite: Indicates if a Signed Write will be performed
        @param ReliableLongCharWrites: Indicates Reliable Long Writes
        @param Csrk: The CSRK if signedWrite is TRUE, ignored otherwise
        '''
        self.DeviceId = DeviceId
        self.Characteristic_Properties = Characteristic_Properties
        self.Characteristic_Value = Characteristic_Value
        self.Characteristic_NbOfDescriptors = Characteristic_NbOfDescriptors
        self.Characteristic_Descriptors = Characteristic_Descriptors
        self.ValueLength = ValueLength
        self.Value = Value
        self.WithoutResponse = WithoutResponse
        self.SignedWrite = SignedWrite
        self.ReliableLongCharWrites = ReliableLongCharWrites
        self.Csrk = Csrk

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Characteristic_Properties, 1)
        result += self.Characteristic_Value.pickle()
        result += to_bytes(self.Characteristic_NbOfDescriptors, 1)
        for i in range(list_to_int(self.Characteristic_NbOfDescriptors, False)):
            result += self.Characteristic_Descriptors[i].pickle()
        result += to_bytes(self.ValueLength, 2)
        for i in range(list_to_int(self.ValueLength, False)):
            result += to_bytes(self.Value[i], 1)
        result += to_bytes(self.WithoutResponse, 1)
        result += to_bytes(self.SignedWrite, 1)
        result += to_bytes(self.ReliableLongCharWrites, 1)
        result += to_bytes(self.Csrk, 16)
        return result


class GATTClientReadCharacteristicDescriptorRequest(object):

    def __init__(self, DeviceId=bytearray(1), Descriptor_Handle=bytearray(2), Descriptor_UuidType=GATTClientReadCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits, Descriptor_Uuid=[], Descriptor_ValueLength=bytearray(2), Descriptor_MaxValueLength=bytearray(2), Descriptor_Value=[], MaxReadBytes=bytearray(2)):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Descriptor_Handle: Attribute handle
        @param Descriptor_UuidType: UUID type
        @param Descriptor_Uuid: UUID value
        @param Descriptor_ValueLength: Length of the attribute value array
        @param Descriptor_MaxValueLength: Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
        @param Descriptor_Value: Attribute value array
        @param MaxReadBytes: Maximum number of bytes to be read
        '''
        self.DeviceId = DeviceId
        self.Descriptor_Handle = Descriptor_Handle
        self.Descriptor_UuidType = Descriptor_UuidType
        self.Descriptor_Uuid = Descriptor_Uuid
        self.Descriptor_ValueLength = Descriptor_ValueLength
        self.Descriptor_MaxValueLength = Descriptor_MaxValueLength
        self.Descriptor_Value = Descriptor_Value
        self.MaxReadBytes = MaxReadBytes


class GATTClientWriteCharacteristicDescriptorRequest(object):

    def __init__(self, DeviceId=bytearray(1), Descriptor_Handle=bytearray(2), Descriptor_UuidType=GATTClientWriteCharacteristicDescriptorRequestDescriptor_UuidType.Uuid16Bits, Descriptor_Uuid=[], Descriptor_ValueLength=bytearray(2), Descriptor_MaxValueLength=bytearray(2), Descriptor_Value=[], ValueLength=bytearray(2), Value=[]):
        '''
        @param DeviceId: Device ID of the connected peer
        @param Descriptor_Handle: Attribute handle
        @param Descriptor_UuidType: UUID type
        @param Descriptor_Uuid: UUID value
        @param Descriptor_ValueLength: Length of the attribute value array
        @param Descriptor_MaxValueLength: Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
        @param Descriptor_Value: Attribute value array
        @param ValueLength: Number of bytes to be written
        @param Value: Array of bytes to be written
        '''
        self.DeviceId = DeviceId
        self.Descriptor_Handle = Descriptor_Handle
        self.Descriptor_UuidType = Descriptor_UuidType
        self.Descriptor_Uuid = Descriptor_Uuid
        self.Descriptor_ValueLength = Descriptor_ValueLength
        self.Descriptor_MaxValueLength = Descriptor_MaxValueLength
        self.Descriptor_Value = Descriptor_Value
        self.ValueLength = ValueLength
        self.Value = Value


class GATTServerInitRequest(object):

    pass


class GATTServerRegisterCallbackRequest(object):

    pass


class GATTServerRegisterHandlesForWriteNotificationsRequest(object):

    def __init__(self, HandleCount=bytearray(1), AttributeHandles=[]):
        '''
        @param HandleCount: Number of handles in array
        @param AttributeHandles: Statically allocated array of handles
        '''
        self.HandleCount = HandleCount
        self.AttributeHandles = AttributeHandles

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.HandleCount, 1)
        for i in range(list_to_int(self.HandleCount, False)):
            result += to_bytes(self.AttributeHandles[i], 2)
        return result


class GATTServerSendAttributeWrittenStatusRequest(object):

    def __init__(self, DeviceId=bytearray(1), AttributeHandle=bytearray(2), Status=bytearray(1)):
        '''
        @param DeviceId: The device ID of the connected peer
        @param AttributeHandle: The attribute handle that was written
        @param Status: The status of the write operation
        '''
        self.DeviceId = DeviceId
        self.AttributeHandle = AttributeHandle
        self.Status = Status


class GATTServerSendNotificationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2)):
        '''
        @param DeviceId: The device ID of the connected peer
        @param Handle: Handle of the Value of the Characteristic to be notified
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle


class GATTServerSendIndicationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2)):
        '''
        @param DeviceId: The device ID of the connected peer
        @param Handle: Handle of the Value of the Characteristic to be indicated
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle


class GATTServerSendInstantValueNotificationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2), ValueLength=bytearray(2), Value=[]):
        '''
        @param DeviceId: The device ID of the connected peer
        @param Handle: Handle of the Value of the Characteristic to be notified
        @param ValueLength: Length of data to be notified
        @param Value: Data to be notified
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle
        self.ValueLength = ValueLength
        self.Value = Value


class GATTServerSendInstantValueIndicationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2), ValueLength=bytearray(2), Value=[]):
        '''
        @param DeviceId: The device ID of the connected peer
        @param Handle: Handle of the Value of the Characteristic to be indicated
        @param ValueLength: Length of data to be indicated
        @param Value: Data to be indicated
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle
        self.ValueLength = ValueLength
        self.Value = Value


class GATTServerRegisterHandlesForReadNotificationsRequest(object):

    def __init__(self, HandleCount=bytearray(1), AttributeHandles=[]):
        '''
        @param HandleCount: Number of handles in array
        @param AttributeHandles: Statically allocated array of handles
        '''
        self.HandleCount = HandleCount
        self.AttributeHandles = AttributeHandles

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.HandleCount, 1)
        for i in range(list_to_int(self.HandleCount, False)):
            result += to_bytes(self.AttributeHandles[i], 2)
        return result


class GATTServerSendAttributeReadStatusRequest(object):

    def __init__(self, DeviceId=bytearray(1), AttributeHandle=bytearray(2), Status=bytearray(1)):
        '''
        @param DeviceId: The device ID of the connected peer
        @param AttributeHandle: The attribute handle that was read
        @param Status: The status of the read operation
        '''
        self.DeviceId = DeviceId
        self.AttributeHandle = AttributeHandle
        self.Status = Status


class GATTServerRegisterUniqueHandlesForNotificationsRequest(object):

    def __init__(self, bWrite=bytearray(1), bRead=bytearray(1)):
        '''
        @param bWrite: Boolean value which indicates unique handles are notified for write or not
        @param bRead: Boolean value which indicates unique handles are notified for read or not
        '''
        self.bWrite = bWrite
        self.bRead = bRead
class GATTServerUnregisterHandlesForWriteNotificationsRequest(object):

    class AttributeHandles(object):

        def __init__(self, Handle=bytearray(2)):
            self.Handle = Handle

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            return result

    def __init__(self, HandleCount=bytearray(1), AttributeHandles=[]):
        '''
        @param HandleCount: Number of handles in array
        @param AttributeHandles: Statically allocated array of handles
        '''
        self.HandleCount = HandleCount
        self.AttributeHandles = AttributeHandles

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.HandleCount, 1)
        for i in range(list_to_int(self.HandleCount, False)):
            result += self.AttributeHandles[i].pickle()
        return result


class GATTServerUnregisterHandlesForReadNotificationsRequest(object):

    class AttributeHandles(object):

        def __init__(self, Handle=bytearray(2)):
            self.Handle = Handle

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Handle, 2)
            return result

    def __init__(self, HandleCount=bytearray(1), AttributeHandles=[]):
        '''
        @param HandleCount: Number of handles in array
        @param AttributeHandles: Statically allocated array of handles
        '''
        self.HandleCount = HandleCount
        self.AttributeHandles = AttributeHandles

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.HandleCount, 1)
        for i in range(list_to_int(self.HandleCount, False)):
            result += self.AttributeHandles[i].pickle()
        return result


class GATTDBWriteAttributeRequest(object):

    def __init__(self, Handle=bytearray(2), ValueLength=bytearray(2), Value=[]):
        '''
        @param Handle: The handle of the attribute to be written
        @param ValueLength: The number of bytes to be written
        @param Value: The value to be written
        '''
        self.Handle = Handle
        self.ValueLength = ValueLength
        self.Value = Value


class GATTDBReadAttributeRequest(object):

    def __init__(self, Handle=bytearray(2), MaxBytes=bytearray(2)):
        '''
        @param Handle: The handle of the attribute to be read
        @param MaxBytes: The maximum number of bytes to be read
        '''
        self.Handle = Handle
        self.MaxBytes = MaxBytes


class GATTDBFindServiceHandleRequest(object):

    def __init__(self, StartHandle=bytearray(2), UuidType=GATTDBFindServiceHandleRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param StartHandle: The handle to start the search. Should be 0x0001 on the first call
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.StartHandle = StartHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBFindCharValueHandleInServiceRequest(object):

    def __init__(self, ServiceHandle=bytearray(2), UuidType=GATTDBFindCharValueHandleInServiceRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param ServiceHandle: The handle of the Service declaration
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.ServiceHandle = ServiceHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBFindCccdHandleForCharValueHandleRequest(object):

    def __init__(self, CharValueHandle=bytearray(2)):
        '''
        @param CharValueHandle: The handle of the characteristic value
        '''
        self.CharValueHandle = CharValueHandle


class GATTDBFindDescriptorHandleForCharValueHandleRequest(object):

    def __init__(self, CharValueHandle=bytearray(2), UuidType=GATTDBFindDescriptorHandleForCharValueHandleRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param CharValueHandle: The handle of the characteristic value
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.CharValueHandle = CharValueHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBDynamicInitRequest(object):

    pass


class GATTDBDynamicReleaseDatabaseRequest(object):

    pass


class GATTDBDynamicAddPrimaryServiceDeclarationRequest(object):

    def __init__(self, DesiredHandle=bytearray(2), UuidType=GATTDBDynamicAddPrimaryServiceDeclarationRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param DesiredHandle: The desired handle for the Primary Service declaration
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.DesiredHandle = DesiredHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBDynamicAddSecondaryServiceDeclarationRequest(object):

    def __init__(self, DesiredHandle=bytearray(2), UuidType=GATTDBDynamicAddSecondaryServiceDeclarationRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param DesiredHandle: The desired handle for the Secondary Service declaration
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.DesiredHandle = DesiredHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBDynamicAddIncludeDeclarationRequest(object):

    def __init__(self, IncludedServiceHandle=bytearray(2), EndGroupHandle=bytearray(2), UuidType=GATTDBDynamicAddIncludeDeclarationRequestUuidType.Uuid16Bits, Uuid=[]):
        '''
        @param IncludedServiceHandle: Handle of the included Service declaration
        @param EndGroupHandle: Last handle of the included Service
        @param UuidType: UUID type
        @param Uuid: UUID value
        '''
        self.IncludedServiceHandle = IncludedServiceHandle
        self.EndGroupHandle = EndGroupHandle
        self.UuidType = UuidType
        self.Uuid = Uuid


class GATTDBDynamicAddCharacteristicDeclarationAndValueRequest(object):

    def __init__(self, UuidType=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestUuidType.Uuid16Bits, Uuid=[], CharacteristicProperties=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestCharacteristicProperties.gNone_c, MaxValueLength=bytearray(2), InitialValueLength=bytearray(2), InitialValue=[], ValueAccessPermissions=GATTDBDynamicAddCharacteristicDeclarationAndValueRequestValueAccessPermissions.gPermissionNone_c):
        '''
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param CharacteristicProperties: Characteristic properties
        @param MaxValueLength: If the Characteristic Value length is variable, this is the maximum length; for fixed lengths this must be set to 0
        @param InitialValueLength: Value length at initialization; remains fixed if maxValueLength is set to 0, otherwise cannot be greater than maxValueLength
        @param InitialValue: Contains the initial value of the Characteristic
        @param ValueAccessPermissions: Access permissions for the value attribute
        '''
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.CharacteristicProperties = CharacteristicProperties
        self.MaxValueLength = MaxValueLength
        self.InitialValueLength = InitialValueLength
        self.InitialValue = InitialValue
        self.ValueAccessPermissions = ValueAccessPermissions


class GATTDBDynamicAddCharacteristicDescriptorRequest(object):

    def __init__(self, UuidType=GATTDBDynamicAddCharacteristicDescriptorRequestUuidType.Uuid16Bits, Uuid=[], DescriptorValueLength=bytearray(2), Value=[], DescriptorAccessPermissions=GATTDBDynamicAddCharacteristicDescriptorRequestDescriptorAccessPermissions.gPermissionNone_c):
        '''
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param DescriptorValueLength: Fixed length of the descriptor attribute value
        @param Value: Initial value of the descriptor attribute
        @param DescriptorAccessPermissions: Access permissions for the descriptor attribute
        '''
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.DescriptorValueLength = DescriptorValueLength
        self.Value = Value
        self.DescriptorAccessPermissions = DescriptorAccessPermissions


class GATTDBDynamicAddCccdRequest(object):

    pass


class GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(object):

    def __init__(self, UuidType=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestUuidType.Uuid16Bits, Uuid=[], CharacteristicProperties=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestCharacteristicProperties.gNone_c, ValueAccessPermissions=GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestValueAccessPermissions.gPermissionNone_c):
        '''
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param CharacteristicProperties: Characteristic properties
        @param ValueAccessPermissions: Access permissions for the value attribute
        '''
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.CharacteristicProperties = CharacteristicProperties
        self.ValueAccessPermissions = ValueAccessPermissions


class GATTDBDynamicRemoveServiceRequest(object):

    def __init__(self, ServiceHandle=bytearray(2)):
        '''
        @param ServiceHandle: Attribute handle of the Service declaration
        '''
        self.ServiceHandle = ServiceHandle


class GATTDBDynamicRemoveCharacteristicRequest(object):

    def __init__(self, CharacteristicHandle=bytearray(2)):
        '''
        @param CharacteristicHandle: Attribute handle of the Characteristic declaration
        '''
        self.CharacteristicHandle = CharacteristicHandle


class GATTDBDynamicAddCharDescriptorWithUniqueValueRequest(object):

    def __init__(self, UuidType=GATTDBDynamicAddCharDescriptorWithUniqueValueRequestUuidType.Uuid16Bits, Uuid=[], DescriptorAccessPermissions=GATTDBDynamicAddCharDescriptorWithUniqueValueRequestDescriptorAccessPermissions.gPermissionNone_c):
        '''
        @param UuidType: UUID type
        @param Uuid: UUID value
        @param DescriptorAccessPermissions: Access permissions for the descriptor attribute
        '''
        self.UuidType = UuidType
        self.Uuid = Uuid
        self.DescriptorAccessPermissions = DescriptorAccessPermissions


class BLEHostInitializeRequest(object):

    pass


class GAPRegisterDeviceSecurityRequirementsRequest(object):

    class SecurityRequirements(object):

        class MasterSecurityRequirements(object):

            def __init__(self, SecurityModeLevel=MasterSecurityRequirementsSecurityModeLevel.gMode1Level1_c, Authorization=bytearray(1), MinimumEncryptionKeySize=bytearray(2)):
                self.SecurityModeLevel = SecurityModeLevel
                self.Authorization = Authorization
                self.MinimumEncryptionKeySize = MinimumEncryptionKeySize

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.SecurityModeLevel, 1)
                result += to_bytes(self.Authorization, 1)
                result += to_bytes(self.MinimumEncryptionKeySize, 2)
                return result

        class GapServiceSecurityRequirements(object):

            class Requirements(object):

                def __init__(self, SecurityModeLevel=RequirementsSecurityModeLevel.gMode1Level1_c, Authorization=bytearray(1), MinimumEncryptionKeySize=bytearray(2)):
                    self.SecurityModeLevel = SecurityModeLevel
                    self.Authorization = Authorization
                    self.MinimumEncryptionKeySize = MinimumEncryptionKeySize

                def pickle(self):
                    result = bytearray()
                    result += to_bytes(self.SecurityModeLevel, 1)
                    result += to_bytes(self.Authorization, 1)
                    result += to_bytes(self.MinimumEncryptionKeySize, 2)
                    return result

            def __init__(self, ServiceHandle=bytearray(2), Requirements=Requirements()):
                self.ServiceHandle = ServiceHandle
                self.Requirements = Requirements

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.ServiceHandle, 2)
                result += self.Requirements.pickle()
                return result

        def __init__(self, MasterSecurityRequirements=MasterSecurityRequirements(), NbOfServices=bytearray(1), GapServiceSecurityRequirements=[]):
            self.MasterSecurityRequirements = MasterSecurityRequirements
            self.NbOfServices = NbOfServices
            # Array length depends on NbOfServices.
            self.GapServiceSecurityRequirements = GapServiceSecurityRequirements

        def pickle(self):
            result = bytearray()
            result += self.MasterSecurityRequirements.pickle()
            result += to_bytes(self.NbOfServices, 1)
            for i in range(list_to_int(self.NbOfServices, False)):
                result += self.GapServiceSecurityRequirements[i].pickle()
            return result

    def __init__(self, SecurityRequirementsIncluded=bytearray(1), SecurityRequirements=SecurityRequirements()):
        '''
        @param SecurityRequirementsIncluded: Boolean value which indicates if security requirements are included or not
        @param SecurityRequirements: Device security requirements
        '''
        self.SecurityRequirementsIncluded = SecurityRequirementsIncluded
        self.SecurityRequirements = SecurityRequirements

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.SecurityRequirementsIncluded, 1)
        if self.SecurityRequirementsIncluded:
            result += self.SecurityRequirements.pickle()
        return result


class GAPSetAdvertisingParametersRequest(object):

    def __init__(self, AdvertisingParameters_MinInterval=bytearray(2), AdvertisingParameters_MaxInterval=bytearray(2), AdvertisingParameters_AdvertisingType=GAPSetAdvertisingParametersRequestAdvertisingParameters_AdvertisingType.gConnectableUndirected_c, AdvertisingParameters_OwnAddressType=GAPSetAdvertisingParametersRequestAdvertisingParameters_OwnAddressType.gPublic_c, AdvertisingParameters_PeerAddressType=GAPSetAdvertisingParametersRequestAdvertisingParameters_PeerAddressType.gPublic_c, AdvertisingParameters_PeerAddress=bytearray(6), AdvertisingParameters_ChannelMap=bytearray(1), AdvertisingParameters_FilterPolicy=GAPSetAdvertisingParametersRequestAdvertisingParameters_FilterPolicy.gProcessAll_c):
        '''
        @param AdvertisingParameters_MinInterval: Minimum desired advertising interval - default 1.28s
        @param AdvertisingParameters_MaxInterval: Maximum desired advertising interval - default 1.28s
        @param AdvertisingParameters_AdvertisingType: Advertising type - default connectable undirected
        @param AdvertisingParameters_OwnAddressType: Indicates whether the advertising address will be the public address or the random address
        @param AdvertisingParameters_PeerAddressType: Address type of the peer; only used in directed advertising and Enhanced Privacy
        @param AdvertisingParameters_PeerAddress: Address of the peer
        @param AdvertisingParameters_ChannelMap: Bit mask indicating which of the three advertising channels will be used - default all three
        @param AdvertisingParameters_FilterPolicy: Indicates whether the connect and scan requests are filtered using the White List - default does not use White List
        '''
        self.AdvertisingParameters_MinInterval = AdvertisingParameters_MinInterval
        self.AdvertisingParameters_MaxInterval = AdvertisingParameters_MaxInterval
        self.AdvertisingParameters_AdvertisingType = AdvertisingParameters_AdvertisingType
        self.AdvertisingParameters_OwnAddressType = AdvertisingParameters_OwnAddressType
        self.AdvertisingParameters_PeerAddressType = AdvertisingParameters_PeerAddressType
        self.AdvertisingParameters_PeerAddress = AdvertisingParameters_PeerAddress
        self.AdvertisingParameters_ChannelMap = AdvertisingParameters_ChannelMap
        self.AdvertisingParameters_FilterPolicy = AdvertisingParameters_FilterPolicy


class GAPSetAdvertisingDataRequest(object):

    class AdvertisingData(object):

        class AdStructures(object):

            def __init__(self, Length=bytearray(1), Type=AdStructuresType(), Data=[]):
                self.Length = Length
                self.Type = Type
                # Array length depends on Length.
                self.Data = Data

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Length, 1)
                result += to_bytes(self.Type, 1)
                result += to_bytes(self.Data, self.Length)
                return result

        def __init__(self, NbOfAdStructures=bytearray(1), AdStructures=[]):
            self.NbOfAdStructures = NbOfAdStructures
            # Array length depends on NbOfAdStructures.
            self.AdStructures = AdStructures

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.NbOfAdStructures, 1)
            for i in range(list_to_int(self.NbOfAdStructures, False)):
                result += self.AdStructures[i].pickle()
            return result

    class ScanResponseData(object):

        class AdStructures(object):

            def __init__(self, Length=bytearray(1), Type=AdStructuresType(), Data=[]):
                self.Length = Length
                self.Type = Type
                # Array length depends on Length.
                self.Data = Data

            def pickle(self):
                result = bytearray()
                result += to_bytes(self.Length, 1)
                result += to_bytes(self.Type, 1)
                result += to_bytes(self.Data, self.Length)
                return result

        def __init__(self, NbOfAdStructures=bytearray(1), AdStructures=[]):
            self.NbOfAdStructures = NbOfAdStructures
            # Array length depends on NbOfAdStructures.
            self.AdStructures = AdStructures

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.NbOfAdStructures, 1)
            for i in range(list_to_int(self.NbOfAdStructures, False)):
                result += self.AdStructures[i].pickle()
            return result

    def __init__(self, AdvertisingDataIncluded=bytearray(1), AdvertisingData=AdvertisingData(), ScanResponseDataIncluded=bytearray(1), ScanResponseData=ScanResponseData()):
        '''
        @param AdvertisingDataIncluded: Boolean value which indicates if advertising data is included or not
        @param AdvertisingData: Advertising data
        @param ScanResponseDataIncluded: Boolean value which indicates if scan response data is included or not
        @param ScanResponseData: Scan response data
        '''
        self.AdvertisingDataIncluded = AdvertisingDataIncluded
        self.AdvertisingData = AdvertisingData
        self.ScanResponseDataIncluded = ScanResponseDataIncluded
        self.ScanResponseData = ScanResponseData

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.AdvertisingDataIncluded, 1)
        if self.AdvertisingDataIncluded:
            result += self.AdvertisingData.pickle()
        result += to_bytes(self.ScanResponseDataIncluded, 1)
        if self.ScanResponseDataIncluded:
            result += self.ScanResponseData.pickle()
        return result


class GAPStartAdvertisingRequest(object):

    pass


class GAPStopAdvertisingRequest(object):

    pass


class GAPAuthorizeRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2), Access=GAPAuthorizeRequestAccess.gRead_c):
        '''
        @param DeviceId: The peer being authorized
        @param Handle: The attribute handle
        @param Access: GATT Database access type (the type of access granted - read or write)
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle
        self.Access = Access


class GAPSaveCccdRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2), Cccd=GAPSaveCccdRequestCccd.gEmpty_c):
        '''
        @param DeviceId: The peer GATT client
        @param Handle: The handle of the CCCD as defined in the GATT Database
        @param Cccd: The bit mask representing the CCCD value to be saved
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle
        self.Cccd = Cccd


class GAPCheckNotificationStatusRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2)):
        '''
        @param DeviceId: The peer GATT client
        @param Handle: The handle of the CCCD
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle


class GAPCheckIndicationStatusRequest(object):

    def __init__(self, DeviceId=bytearray(1), Handle=bytearray(2)):
        '''
        @param DeviceId: The peer GATT client
        @param Handle: The handle of the CCCD
        '''
        self.DeviceId = DeviceId
        self.Handle = Handle


class GAPPairRequest(object):

    def __init__(self, DeviceId=bytearray(1), PairingParameters_WithBonding=bytearray(1), PairingParameters_SecurityModeAndLevel=GAPPairRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c, PairingParameters_MaxEncryptionKeySize=bytearray(1), PairingParameters_LocalIoCapabilities=GAPPairRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c, PairingParameters_OobAvailable=bytearray(1), PairingParameters_CentralKeys=bytearray(1), PairingParameters_PeripheralKeys=bytearray(1), PairingParameters_LeSecureConnectionSupported=bytearray(1), PairingParameters_UseKeypressNotifications=bytearray(1)):
        '''
        @param DeviceId: The peer to pair with
        @param PairingParameters_WithBonding: TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
        @param PairingParameters_SecurityModeAndLevel: The desired security mode-level
        @param PairingParameters_MaxEncryptionKeySize: Maximum LTK size supported by the device
        @param PairingParameters_LocalIoCapabilities: I/O capabilities used to determine the pairing method
        @param PairingParameters_OobAvailable: TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
        @param PairingParameters_CentralKeys: SMP keys to be distributed by the Central
        @param PairingParameters_PeripheralKeys: SMP keys to be distributed by the Peripheral
        @param PairingParameters_LeSecureConnectionSupported: indicates if device supports LE Secure Connections pairing
        @param PairingParameters_UseKeypressNotifications: Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
        '''
        self.DeviceId = DeviceId
        self.PairingParameters_WithBonding = PairingParameters_WithBonding
        self.PairingParameters_SecurityModeAndLevel = PairingParameters_SecurityModeAndLevel
        self.PairingParameters_MaxEncryptionKeySize = PairingParameters_MaxEncryptionKeySize
        self.PairingParameters_LocalIoCapabilities = PairingParameters_LocalIoCapabilities
        self.PairingParameters_OobAvailable = PairingParameters_OobAvailable
        self.PairingParameters_CentralKeys = PairingParameters_CentralKeys
        self.PairingParameters_PeripheralKeys = PairingParameters_PeripheralKeys
        self.PairingParameters_LeSecureConnectionSupported = PairingParameters_LeSecureConnectionSupported
        self.PairingParameters_UseKeypressNotifications = PairingParameters_UseKeypressNotifications


class GAPSendSlaveSecurityRequestRequest(object):

    def __init__(self, DeviceId=bytearray(1), PairingParameters_WithBonding=bytearray(1), PairingParameters_SecurityModeAndLevel=GAPSendSlaveSecurityRequestRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c, PairingParameters_MaxEncryptionKeySize=bytearray(1), PairingParameters_LocalIoCapabilities=GAPSendSlaveSecurityRequestRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c, PairingParameters_OobAvailable=bytearray(1), PairingParameters_CentralKeys=bytearray(1), PairingParameters_PeripheralKeys=bytearray(1), PairingParameters_LeSecureConnectionSupported=bytearray(1), PairingParameters_UseKeypressNotifications=bytearray(1)):
        '''
        @param DeviceId: The GAP peer to pair with
        @param PairingParameters_WithBonding: TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
        @param PairingParameters_SecurityModeAndLevel: The desired security mode-level
        @param PairingParameters_MaxEncryptionKeySize: Maximum LTK size supported by the device
        @param PairingParameters_LocalIoCapabilities: I/O capabilities used to determine the pairing method
        @param PairingParameters_OobAvailable: TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
        @param PairingParameters_CentralKeys: SMP keys to be distributed by the Central
        @param PairingParameters_PeripheralKeys: SMP keys to be distributed by the Peripheral
        @param PairingParameters_LeSecureConnectionSupported: indicates if device supports LE Secure Connections pairing
        @param PairingParameters_UseKeypressNotifications: Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
        '''
        self.DeviceId = DeviceId
        self.PairingParameters_WithBonding = PairingParameters_WithBonding
        self.PairingParameters_SecurityModeAndLevel = PairingParameters_SecurityModeAndLevel
        self.PairingParameters_MaxEncryptionKeySize = PairingParameters_MaxEncryptionKeySize
        self.PairingParameters_LocalIoCapabilities = PairingParameters_LocalIoCapabilities
        self.PairingParameters_OobAvailable = PairingParameters_OobAvailable
        self.PairingParameters_CentralKeys = PairingParameters_CentralKeys
        self.PairingParameters_PeripheralKeys = PairingParameters_PeripheralKeys
        self.PairingParameters_LeSecureConnectionSupported = PairingParameters_LeSecureConnectionSupported
        self.PairingParameters_UseKeypressNotifications = PairingParameters_UseKeypressNotifications


class GAPEncryptLinkRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the peer
        '''
        self.DeviceId = DeviceId


class GAPAcceptPairingRequestRequest(object):

    def __init__(self, DeviceId=bytearray(1), PairingParameters_WithBonding=bytearray(1), PairingParameters_SecurityModeAndLevel=GAPAcceptPairingRequestRequestPairingParameters_SecurityModeAndLevel.gMode1Level1_c, PairingParameters_MaxEncryptionKeySize=bytearray(1), PairingParameters_LocalIoCapabilities=GAPAcceptPairingRequestRequestPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c, PairingParameters_OobAvailable=bytearray(1), PairingParameters_CentralKeys=bytearray(1), PairingParameters_PeripheralKeys=bytearray(1), PairingParameters_LeSecureConnectionSupported=bytearray(1), PairingParameters_UseKeypressNotifications=bytearray(1)):
        '''
        @param DeviceId: The peer requesting authentication
        @param PairingParameters_WithBonding: TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
        @param PairingParameters_SecurityModeAndLevel: The desired security mode-level
        @param PairingParameters_MaxEncryptionKeySize: Maximum LTK size supported by the device
        @param PairingParameters_LocalIoCapabilities: I/O capabilities used to determine the pairing method
        @param PairingParameters_OobAvailable: TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
        @param PairingParameters_CentralKeys: SMP keys to be distributed by the Central
        @param PairingParameters_PeripheralKeys: SMP keys to be distributed by the Peripheral
        @param PairingParameters_LeSecureConnectionSupported: indicates if device supports LE Secure Connections pairing
        @param PairingParameters_UseKeypressNotifications: Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
        '''
        self.DeviceId = DeviceId
        self.PairingParameters_WithBonding = PairingParameters_WithBonding
        self.PairingParameters_SecurityModeAndLevel = PairingParameters_SecurityModeAndLevel
        self.PairingParameters_MaxEncryptionKeySize = PairingParameters_MaxEncryptionKeySize
        self.PairingParameters_LocalIoCapabilities = PairingParameters_LocalIoCapabilities
        self.PairingParameters_OobAvailable = PairingParameters_OobAvailable
        self.PairingParameters_CentralKeys = PairingParameters_CentralKeys
        self.PairingParameters_PeripheralKeys = PairingParameters_PeripheralKeys
        self.PairingParameters_LeSecureConnectionSupported = PairingParameters_LeSecureConnectionSupported
        self.PairingParameters_UseKeypressNotifications = PairingParameters_UseKeypressNotifications


class GAPRejectPairingRequest(object):

    def __init__(self, DeviceId=bytearray(1), Reason=GAPRejectPairingRequestReason.gOobNotAvailable_c):
        '''
        @param DeviceId: The GAP peer who requested authentication
        @param Reason: Pairing reject reason
        '''
        self.DeviceId = DeviceId
        self.Reason = Reason


class GAPEnterPasskeyRequest(object):

    def __init__(self, DeviceId=bytearray(1), Passkey=bytearray(4)):
        '''
        @param DeviceId: The GAP peer that requested a passkey entry
        @param Passkey: The peer's secret passkey
        '''
        self.DeviceId = DeviceId
        self.Passkey = Passkey


class GAPProvideOobRequest(object):

    def __init__(self, DeviceId=bytearray(1), Oob=bytearray(16)):
        '''
        @param DeviceId: The pairing device
        @param Oob: OOB data
        '''
        self.DeviceId = DeviceId
        self.Oob = Oob


class GAPRejectPasskeyRequestRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: The GAP peer that requested a passkey entry
        '''
        self.DeviceId = DeviceId


class GAPSendSmpKeysRequest(object):

    class Keys_LtkInfo(object):

        def __init__(self, LtkSize=bytearray(1), Ltk=[]):
            self.LtkSize = LtkSize
            # Array length depends on LtkSize.
            self.Ltk = Ltk

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.LtkSize, 1)
            result += to_bytes(self.Ltk, self.LtkSize)
            return result

    class Keys_RandEdivInfo(object):

        def __init__(self, RandSize=bytearray(1), Rand=[], Ediv=bytearray(2)):
            self.RandSize = RandSize
            # Array length depends on RandSize.
            self.Rand = Rand
            self.Ediv = Ediv

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.RandSize, 1)
            result += to_bytes(self.Rand, self.RandSize)
            result += to_bytes(self.Ediv, 2)
            return result

    class Keys_AddressInfo(object):

        def __init__(self, DeviceAddressType=Keys_AddressInfoDeviceAddressType.gPublic_c, DeviceAddress=bytearray(6)):
            self.DeviceAddressType = DeviceAddressType
            # Unit length: 6 bytes
            self.DeviceAddress = DeviceAddress

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.DeviceAddressType, 1)
            result += to_bytes(self.DeviceAddress, 6)
            return result

    def __init__(self, DeviceId=bytearray(1), Keys_LtkIncluded=bytearray(1), Keys_LtkInfo=Keys_LtkInfo(), Keys_IrkIncluded=bytearray(1), Keys_Irk=[], Keys_CsrkIncluded=bytearray(1), Keys_Csrk=[], Keys_RandEdivInfo=Keys_RandEdivInfo(), Keys_AddressIncluded=[], Keys_AddressInfo=Keys_AddressInfo()):
        '''
        @param DeviceId: The GAP peer who initiated the procedure
        @param Keys_LtkIncluded: Boolean value which indicates if LTK size and LTK are included or not
        @param Keys_LtkInfo: LTK information (size and value)
        @param Keys_IrkIncluded: Boolean value which indicates if IRK is included or not
        @param Keys_Irk: Identity Resolving Key
        @param Keys_CsrkIncluded: Boolean value which indicates if CSRK is included or not
        @param Keys_Csrk: Connection Signature Resolving Key
        @param Keys_RandEdivInfo: Rand information (size and value) and Ediv
        @param Keys_AddressIncluded: Boolean value which indicates if Address is included or not
        @param Keys_AddressInfo: Address information (type and value)
        '''
        self.DeviceId = DeviceId
        self.Keys_LtkIncluded = Keys_LtkIncluded
        self.Keys_LtkInfo = Keys_LtkInfo
        self.Keys_IrkIncluded = Keys_IrkIncluded
        self.Keys_Irk = Keys_Irk
        self.Keys_CsrkIncluded = Keys_CsrkIncluded
        self.Keys_Csrk = Keys_Csrk
        self.Keys_RandEdivInfo = Keys_RandEdivInfo
        self.Keys_AddressIncluded = Keys_AddressIncluded
        self.Keys_AddressInfo = Keys_AddressInfo

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.DeviceId, 1)
        result += to_bytes(self.Keys_LtkIncluded, 1)
        if self.Keys_LtkIncluded:
            result += self.Keys_LtkInfo.pickle()
        result += to_bytes(self.Keys_IrkIncluded, 1)
        if self.Keys_IrkIncluded:
            result += to_bytes(self.Keys_Irk, 16)
        result += to_bytes(self.Keys_CsrkIncluded, 1)
        if self.Keys_CsrkIncluded:
            result += to_bytes(self.Keys_Csrk, 16)
        if self.Keys_LtkIncluded:
            result += self.Keys_RandEdivInfo.pickle()
        if self.Keys_IrkIncluded:
            result += to_bytes(self.Keys_AddressIncluded, 1)
        if self.Keys_AddressIncluded:
            result += self.Keys_AddressInfo.pickle()
        return result


class GAPRejectKeyExchangeRequestRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: The GAP peer who requested the Key Exchange procedure
        '''
        self.DeviceId = DeviceId


class GAPProvideLongTermKeyRequest(object):

    def __init__(self, DeviceId=bytearray(1), LtkSize=bytearray(1), Ltk=[]):
        '''
        @param DeviceId: The GAP peer who requested encryption
        @param LtkSize: The Long Term Key size
        @param Ltk: The Long Term Key
        '''
        self.DeviceId = DeviceId
        self.LtkSize = LtkSize
        self.Ltk = Ltk


class GAPDenyLongTermKeyRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: The GAP peer who requested encryption
        '''
        self.DeviceId = DeviceId


class GAPLoadEncryptionInformationRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the peer
        '''
        self.DeviceId = DeviceId


class GAPSetLocalPasskeyRequest(object):

    def __init__(self, Passkey=bytearray(4)):
        '''
        @param Passkey: The SMP passkey
        '''
        self.Passkey = Passkey


class GAPStartScanningRequest(object):

    class ScanningParameters(object):

        def __init__(self, Type=ScanningParametersType.gPassive_c, Interval=bytearray(2), Window=bytearray(2), OwnAddressType=ScanningParametersOwnAddressType.gPublic_c, FilterPolicy=ScanningParametersFilterPolicy.gScanAll_c):
            self.Type = Type
            self.Interval = Interval
            self.Window = Window
            self.OwnAddressType = OwnAddressType
            self.FilterPolicy = FilterPolicy

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.Type, 1)
            result += to_bytes(self.Interval, 2)
            result += to_bytes(self.Window, 2)
            result += to_bytes(self.OwnAddressType, 1)
            result += to_bytes(self.FilterPolicy, 1)
            return result

    def __init__(self, ScanningParametersIncluded=bytearray(1), ScanningParameters=ScanningParameters(), FilterDuplicates=bytearray(1), ScanningPHYs=bytearray(1), Duration=bytearray(2), Period=bytearray(2)):
        '''
        @param ScanningParametersIncluded: Boolean value which indicates if scanning parameters are included or not
        @param ScanningParameters: The scanning parameters
        @param FilterDuplicates: Indicates whether duplicate advertising report filtering is enabled. For BLE 5.0 adds the possibility to reset filtering for each scan period
        @param ScanningPHYs: ScanningPHYs
        @param Duration: Scan duration - Time = N * 10ms
        @param Period: Periodic scanning - Time = N * 1.28s
        '''
        self.ScanningParametersIncluded = ScanningParametersIncluded
        self.ScanningParameters = ScanningParameters
        self.FilterDuplicates = FilterDuplicates
        self.ScanningPHYs = ScanningPHYs
        self.Duration = Duration
        self.Period = Period

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.ScanningParametersIncluded, 1)
        if self.ScanningParametersIncluded:
            result += self.ScanningParameters.pickle()
        result += to_bytes(self.FilterDuplicates, 1)
        result += to_bytes(self.ScanningPHYs, 1)
        result += to_bytes(self.Duration, 2)
        result += to_bytes(self.Period, 2)
        return result


class GAPStopScanningRequest(object):

    pass


class GAPConnectRequest(object):

    class CreateConnectionParameters_Initiating_PHYs(object):

        def __init__(self, gLePhy1M_c=bytearray(1), gLePhy2M_c=bytearray(1), gLePhyCoded_c=bytearray(1)):
            self.gLePhy1M_c = gLePhy1M_c
            self.gLePhy2M_c = gLePhy2M_c
            self.gLePhyCoded_c = gLePhyCoded_c

    def __init__(self, CreateConnectionParameters_ScanInterval=bytearray(2), CreateConnectionParameters_ScanWindow=bytearray(2), CreateConnectionParameters_FilterPolicy=GAPConnectRequestCreateConnectionParameters_FilterPolicy.gUseDeviceAddress_c, CreateConnectionParameters_OwnAddressType=GAPConnectRequestCreateConnectionParameters_OwnAddressType.gPublic_c, CreateConnectionParameters_PeerAddressType=GAPConnectRequestCreateConnectionParameters_PeerAddressType.gPublic_c, CreateConnectionParameters_PeerAddress=bytearray(6), CreateConnectionParameters_ConnIntervalMin=bytearray(2), CreateConnectionParameters_ConnIntervalMax=bytearray(2), CreateConnectionParameters_ConnLatency=bytearray(2), CreateConnectionParameters_SupervisionTimeout=bytearray(2), CreateConnectionParameters_ConnEventLengthMin=bytearray(2), CreateConnectionParameters_ConnEventLengthMax=bytearray(2), CreateConnectionParameters_usePeerIdentityAddress=bytearray(1), CreateConnectionParameters_Initiating_PHYs=bytearray(1)):
        '''
        @param CreateConnectionParameters_ScanInterval: Scanning interval - default 10ms
        @param CreateConnectionParameters_ScanWindow: Scanning window - default 10ms
        @param CreateConnectionParameters_FilterPolicy: Indicates whether the connection request is issued for a specific device or for all the devices in the White List - default specific device
        @param CreateConnectionParameters_OwnAddressType: Indicates whether the address used in connection requests will be the public address or the random address - default public address
        @param CreateConnectionParameters_PeerAddressType: When connecting to a specific device, this indicates that device's address type - default public address
        @param CreateConnectionParameters_PeerAddress: When connecting to a specific device, this indicates that device's address
        @param CreateConnectionParameters_ConnIntervalMin: The minimum desired connection interval - default 100ms
        @param CreateConnectionParameters_ConnIntervalMax: The maximum desired connection interval - default 200ms
        @param CreateConnectionParameters_ConnLatency: The desired connection latency (the maximum number of consecutive connection events the Slave is allowed to ignore) - default 0
        @param CreateConnectionParameters_SupervisionTimeout: The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped - default 10s
        @param CreateConnectionParameters_ConnEventLengthMin: The minimum desired connection event length - default 0ms
        @param CreateConnectionParameters_ConnEventLengthMax: The maximum desired connection event length - default maximum possible, ~41 s
        @param CreateConnectionParameters_usePeerIdentityAddress: TRUE if the address defined in the peerAddressType and peerAddress is an identity address
        @param CreateConnectionParameters_Initiating_PHYs: Phy Flags
        '''
        self.CreateConnectionParameters_ScanInterval = CreateConnectionParameters_ScanInterval
        self.CreateConnectionParameters_ScanWindow = CreateConnectionParameters_ScanWindow
        self.CreateConnectionParameters_FilterPolicy = CreateConnectionParameters_FilterPolicy
        self.CreateConnectionParameters_OwnAddressType = CreateConnectionParameters_OwnAddressType
        self.CreateConnectionParameters_PeerAddressType = CreateConnectionParameters_PeerAddressType
        self.CreateConnectionParameters_PeerAddress = CreateConnectionParameters_PeerAddress
        self.CreateConnectionParameters_ConnIntervalMin = CreateConnectionParameters_ConnIntervalMin
        self.CreateConnectionParameters_ConnIntervalMax = CreateConnectionParameters_ConnIntervalMax
        self.CreateConnectionParameters_ConnLatency = CreateConnectionParameters_ConnLatency
        self.CreateConnectionParameters_SupervisionTimeout = CreateConnectionParameters_SupervisionTimeout
        self.CreateConnectionParameters_ConnEventLengthMin = CreateConnectionParameters_ConnEventLengthMin
        self.CreateConnectionParameters_ConnEventLengthMax = CreateConnectionParameters_ConnEventLengthMax
        self.CreateConnectionParameters_usePeerIdentityAddress = CreateConnectionParameters_usePeerIdentityAddress
        self.CreateConnectionParameters_Initiating_PHYs = CreateConnectionParameters_Initiating_PHYs


class GAPDisconnectRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: The connected peer to disconnect from
        '''
        self.DeviceId = DeviceId


class GAPSaveCustomPeerInformationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Offset=bytearray(2), InfoSize=bytearray(2), Info=[]):
        '''
        @param DeviceId: Device ID of the GAP peer
        @param Offset: Data offset (offset from the beginning)
        @param InfoSize: Data size
        @param Info: Data
        '''
        self.DeviceId = DeviceId
        self.Offset = Offset
        self.InfoSize = InfoSize
        self.Info = Info


class GAPLoadCustomPeerInformationRequest(object):

    def __init__(self, DeviceId=bytearray(1), Offset=bytearray(2), InfoSize=bytearray(2)):
        '''
        @param DeviceId: Device ID of the GAP peer
        @param Offset: Data offset (offset from the beginning)
        @param InfoSize: Data size
        '''
        self.DeviceId = DeviceId
        self.Offset = Offset
        self.InfoSize = InfoSize


class GAPCheckIfBondedRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the GAP peer
        '''
        self.DeviceId = DeviceId


class GAPReadWhiteListSizeRequest(object):

    pass


class GAPClearWhiteListRequest(object):

    pass


class GAPAddDeviceToWhiteListRequest(object):

    def __init__(self, AddressType=GAPAddDeviceToWhiteListRequestAddressType.gPublic_c, Address=bytearray(6)):
        '''
        @param AddressType: The address type (public or random)
        @param Address: The address of the white-listed device
        '''
        self.AddressType = AddressType
        self.Address = Address


class GAPRemoveDeviceFromWhiteListRequest(object):

    def __init__(self, AddressType=GAPRemoveDeviceFromWhiteListRequestAddressType.gPublic_c, Address=bytearray(6)):
        '''
        @param AddressType: The address type (public or random)
        @param Address: The address of the white-listed device
        '''
        self.AddressType = AddressType
        self.Address = Address


class GAPReadPublicDeviceAddressRequest(object):

    pass


class GAPCreateRandomDeviceAddressRequest(object):

    def __init__(self, IrkIncluded=bytearray(1), Irk=[], RandomPartIncluded=[], RandomPart=[]):
        '''
        @param IrkIncluded: Boolean value which indicates if IRK is included or not
        @param Irk: The Identity Resolving Key to be used for a private resolvable address
        @param RandomPartIncluded: Boolean value which indicates if random part is included or not
        @param RandomPart: Array containing the random part of a Private Resolvable Address
        '''
        self.IrkIncluded = IrkIncluded
        self.Irk = Irk
        self.RandomPartIncluded = RandomPartIncluded
        self.RandomPart = RandomPart


class GAPSaveDeviceNameRequest(object):

    def __init__(self, DeviceId=bytearray(1), NameSize=bytearray(1), Name=[]):
        '''
        @param DeviceId: Device ID for the active peer which name is saved
        @param NameSize: Number of characters to be saved
        @param Name: Array of characters holding the name
        '''
        self.DeviceId = DeviceId
        self.NameSize = NameSize
        self.Name = Name


class GAPGetBondedDevicesCountRequest(object):

    pass


class GAPGetBondedDeviceNameRequest(object):

    def __init__(self, NvmIndex=bytearray(1), MaxNameSize=bytearray(1)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        @param MaxNameSize: Maximum number of characters to be copied, including the terminating NULL character
        '''
        self.NvmIndex = NvmIndex
        self.MaxNameSize = MaxNameSize


class GAPRemoveBondRequest(object):

    def __init__(self, NvmIndex=bytearray(1)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        '''
        self.NvmIndex = NvmIndex


class GAPRemoveAllBondsRequest(object):

    pass


class GAPReadRadioPowerLevelRequest(object):

    def __init__(self, TxReadType=GAPReadRadioPowerLevelRequestTxReadType.gTxPowerCurrentLevelInConnection_c, DeviceId=bytearray(1)):
        '''
        @param TxReadType: Transmission read type
        @param DeviceId: The DeviceId for which the command is intended
        '''
        self.TxReadType = TxReadType
        self.DeviceId = DeviceId


class GAPVerifyPrivateResolvableAddressRequest(object):

    def __init__(self, NvmIndex=bytearray(1), Address=bytearray(6)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area whose IRK must be checked
        @param Address: The Private Resolvable Address to be verified
        '''
        self.NvmIndex = NvmIndex
        self.Address = Address


class GAPSetRandomAddressRequest(object):

    def __init__(self, Address=bytearray(6)):
        '''
        @param Address: The Private Resolvable, Private Non-Resolvable, or Static Random Address
        '''
        self.Address = Address


class GAPSetScanModeRequest(object):

    class AutoConnectParams_AutoConnectData(object):

        def __init__(self, ScanInterval=bytearray(2), ScanWindow=bytearray(2), FilterPolicy=AutoConnectParams_AutoConnectDataFilterPolicy.gUseDeviceAddress_c, OwnAddressType=AutoConnectParams_AutoConnectDataOwnAddressType.gPublic_c, PeerAddressType=AutoConnectParams_AutoConnectDataPeerAddressType.gPublic_c, PeerAddress=bytearray(6), ConnIntervalMin=bytearray(2), ConnIntervalMax=bytearray(2), ConnLatency=bytearray(2), SupervisionTimeout=bytearray(2), ConnEventLengthMin=bytearray(2), ConnEventLengthMax=bytearray(2), usePeerIdentityAddress=bytearray(1), Initiating_PHYs=bytearray(1)):
            self.ScanInterval = ScanInterval
            self.ScanWindow = ScanWindow
            self.FilterPolicy = FilterPolicy
            self.OwnAddressType = OwnAddressType
            self.PeerAddressType = PeerAddressType
            # Unit length: 6 bytes
            self.PeerAddress = PeerAddress
            self.ConnIntervalMin = ConnIntervalMin
            self.ConnIntervalMax = ConnIntervalMax
            self.ConnLatency = ConnLatency
            self.SupervisionTimeout = SupervisionTimeout
            self.ConnEventLengthMin = ConnEventLengthMin
            self.ConnEventLengthMax = ConnEventLengthMax
            self.usePeerIdentityAddress = usePeerIdentityAddress
            self.Initiating_PHYs = Initiating_PHYs

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.ScanInterval, 2)
            result += to_bytes(self.ScanWindow, 2)
            result += to_bytes(self.FilterPolicy, 1)
            result += to_bytes(self.OwnAddressType, 1)
            result += to_bytes(self.PeerAddressType, 1)
            result += to_bytes(self.PeerAddress, 6)
            result += to_bytes(self.ConnIntervalMin, 2)
            result += to_bytes(self.ConnIntervalMax, 2)
            result += to_bytes(self.ConnLatency, 2)
            result += to_bytes(self.SupervisionTimeout, 2)
            result += to_bytes(self.ConnEventLengthMin, 2)
            result += to_bytes(self.ConnEventLengthMax, 2)
            result += to_bytes(self.usePeerIdentityAddress, 1)
            result += to_bytes(self.Initiating_PHYs, 1)
            return result

    def __init__(self, ScanMode=GAPSetScanModeRequestScanMode.gDefaultScan_c, AutoConnectParams_NbOfAddresses=bytearray(1), AutoConnectParams_WriteInWhiteList=bytearray(1), AutoConnectParams_AutoConnectData=[]):
        '''
        @param ScanMode: The scan mode to be activated.
        @param AutoConnectParams_NbOfAddresses: Number of device addresses to automatically connect to
        @param AutoConnectParams_WriteInWhiteList: If set to TRUE, the device addresses will be written in the White List before scanning is enabled
        @param AutoConnectParams_AutoConnectData: The connection request parameters
        '''
        self.ScanMode = ScanMode
        self.AutoConnectParams_NbOfAddresses = AutoConnectParams_NbOfAddresses
        self.AutoConnectParams_WriteInWhiteList = AutoConnectParams_WriteInWhiteList
        self.AutoConnectParams_AutoConnectData = AutoConnectParams_AutoConnectData

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.ScanMode, 1)
        result += to_bytes(self.AutoConnectParams_NbOfAddresses, 1)
        result += to_bytes(self.AutoConnectParams_WriteInWhiteList, 1)
        for i in range(list_to_int(self.AutoConnectParams_NbOfAddresses, False)):
            result += self.AutoConnectParams_AutoConnectData[i].pickle()
        return result


class GAPSetDefaultPairingParametersRequest(object):

    class PairingParameters(object):

        def __init__(self, WithBonding=bytearray(1), SecurityModeAndLevel=PairingParametersSecurityModeAndLevel.gMode1Level1_c, MaxEncryptionKeySize=bytearray(1), LocalIoCapabilities=PairingParametersLocalIoCapabilities.gIoDisplayOnly_c, OobAvailable=bytearray(1), CentralKeys=bytearray(1), PeripheralKeys=bytearray(1), LeSecureConnectionSupported=bytearray(1), UseKeypressNotifications=bytearray(1)):
            self.WithBonding = WithBonding
            self.SecurityModeAndLevel = SecurityModeAndLevel
            self.MaxEncryptionKeySize = MaxEncryptionKeySize
            self.LocalIoCapabilities = LocalIoCapabilities
            self.OobAvailable = OobAvailable
            self.CentralKeys = CentralKeys
            self.PeripheralKeys = PeripheralKeys
            self.LeSecureConnectionSupported = LeSecureConnectionSupported
            self.UseKeypressNotifications = UseKeypressNotifications

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.WithBonding, 1)
            result += to_bytes(self.SecurityModeAndLevel, 1)
            result += to_bytes(self.MaxEncryptionKeySize, 1)
            result += to_bytes(self.LocalIoCapabilities, 1)
            result += to_bytes(self.OobAvailable, 1)
            result += to_bytes(self.CentralKeys, 1)
            result += to_bytes(self.PeripheralKeys, 1)
            result += to_bytes(self.LeSecureConnectionSupported, 1)
            result += to_bytes(self.UseKeypressNotifications, 1)
            return result

    def __init__(self, PairingParametersIncluded=bytearray(1), PairingParameters=PairingParameters()):
        '''
        @param PairingParametersIncluded: Boolean value which indicates if pairing parameters are included or not
        @param PairingParameters: Pairing parameters as required by the SMP
        '''
        self.PairingParametersIncluded = PairingParametersIncluded
        self.PairingParameters = PairingParameters

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.PairingParametersIncluded, 1)
        if self.PairingParametersIncluded:
            result += self.PairingParameters.pickle()
        return result


class GAPUpdateConnectionParametersRequest(object):

    def __init__(self, DeviceId=bytearray(1), IntervalMin=bytearray(2), IntervalMax=bytearray(2), SlaveLatency=bytearray(2), TimeoutMultiplier=bytearray(2), MinCeLength=bytearray(2), MaxCeLength=bytearray(2)):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param IntervalMin: The minimum value for the connection event interval
        @param IntervalMax: The maximum value for the connection event interval
        @param SlaveLatency: The slave latency parameter
        @param TimeoutMultiplier: The connection timeout parameter
        @param MinCeLength: The minimum connection event length
        @param MaxCeLength: The maximum connection event length
        '''
        self.DeviceId = DeviceId
        self.IntervalMin = IntervalMin
        self.IntervalMax = IntervalMax
        self.SlaveLatency = SlaveLatency
        self.TimeoutMultiplier = TimeoutMultiplier
        self.MinCeLength = MinCeLength
        self.MaxCeLength = MaxCeLength


class GAPEnableUpdateConnectionParametersRequest(object):

    def __init__(self, DeviceId=bytearray(1), Enable=bytearray(1)):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param Enable: Allow/dissalow the parameters update
        '''
        self.DeviceId = DeviceId
        self.Enable = Enable


class GapUpdateLeDataLengthRequest(object):

    def __init__(self, DeviceId=bytearray(1), TxOctets=bytearray(2), TxTime=bytearray(2)):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param TxOctets: Maximum transmission number of payload octets
        @param TxTime: Maximum transmission time
        '''
        self.DeviceId = DeviceId
        self.TxOctets = TxOctets
        self.TxTime = TxTime


class GAPEnableHostPrivacyRequest(object):

    def __init__(self, Enable=bytearray(1), Irk=[]):
        '''
        @param Enable: Enables or disables Host Privacy
        @param Irk: Local IRK to be used for Resolvable Private Address generation
        '''
        self.Enable = Enable
        self.Irk = Irk


class GAPEnableControllerPrivacyRequest(object):

    class PeerIdentities(object):

        def __init__(self, IdentityAddressType=PeerIdentitiesIdentityAddressType.gPublic_c, IdentityAddress=bytearray(6), Irk=bytearray(16), PrivacyMode=PeerIdentitiesPrivacyMode.gNetworkPrivacy_c):
            self.IdentityAddressType = IdentityAddressType
            # Unit length: 6 bytes
            self.IdentityAddress = IdentityAddress
            # Unit length: 16 bytes
            self.Irk = Irk
            self.PrivacyMode = PrivacyMode

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.IdentityAddressType, 1)
            result += to_bytes(self.IdentityAddress, 6)
            result += to_bytes(self.Irk, 16)
            result += to_bytes(self.PrivacyMode, 1)
            return result

    def __init__(self, Enable=bytearray(1), OwnIrk=[], PeerIdCount=[], PeerIdentities=[]):
        '''
        @param Enable: Enables or disables Controller Privacy
        @param OwnIrk: Local IRK
        @param PeerIdCount: Size of PeerIdentities array
        @param PeerIdentities: Array of peer identity addresses and IRKs
        '''
        self.Enable = Enable
        self.OwnIrk = OwnIrk
        self.PeerIdCount = PeerIdCount
        self.PeerIdentities = PeerIdentities

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.Enable, 1)
        if self.Enable:
            result += to_bytes(self.OwnIrk, 16)
        if self.Enable:
            result += to_bytes(self.PeerIdCount, 1)
        for i in range(list_to_int(self.PeerIdCount, False)):
            result += self.PeerIdentities[i].pickle()
        return result


class GAPLeScRegeneratePublicKeyRequest(object):

    pass


class GAPLeScValidateNumericValueRequest(object):

    def __init__(self, DeviceId=bytearray(1), Valid=bytearray(1)):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param Valid: TRUE if user has indicated that numeric values are matched, FALSE otherwise
        '''
        self.DeviceId = DeviceId
        self.Valid = Valid


class GAPLeScGetLocalOobDataRequest(object):

    pass


class GAPLeScSetPeerOobDataRequest(object):

    def __init__(self, DeviceId=bytearray(1), RandomValue=bytearray(16), ConfirmValue=bytearray(16)):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param RandomValue: LE SC OOB r (Random value)
        @param ConfirmValue: LE SC OOB Cr (Random Confirm value)
        '''
        self.DeviceId = DeviceId
        self.RandomValue = RandomValue
        self.ConfirmValue = ConfirmValue


class GAPLeScSendKeypressNotificationPrivacyRequest(object):

    def __init__(self, DeviceId=bytearray(1), GapLeScKeypressNotificationParams_keypressNotifType=GAPLeScSendKeypressNotificationPrivacyRequestGapLeScKeypressNotificationParams_keypressNotifType.gKnPasskeyEntryStarted_c):
        '''
        @param DeviceId: The DeviceID for which the command is intended
        @param GapLeScKeypressNotificationParams_keypressNotifType: keypressNotifType
        '''
        self.DeviceId = DeviceId
        self.GapLeScKeypressNotificationParams_keypressNotifType = GapLeScKeypressNotificationParams_keypressNotifType


class GAPGetBondedDevicesIdentityInformationRequest(object):

    def __init__(self, maxDevices=bytearray(1)):
        '''
        @param maxDevices: Maximum number of addresses to be obtained
        '''
        self.maxDevices = maxDevices


class GAPSetTxPowerLevelRequest(object):

    def __init__(self, powerLevel=bytearray(1), channelType=GAPSetTxPowerLevelRequestchannelType.Advertising):
        '''
        @param powerLevel: power level value as described by the controller interface
        @param channelType: Advertising or Connection channel type for the Tx power level
        '''
        self.powerLevel = powerLevel
        self.channelType = channelType


class GAPLeReadPhyRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the peer.
        '''
        self.DeviceId = DeviceId


class GAPLeSetPhyRequest(object):

    def __init__(self, defaultMode=bytearray(1), DeviceId=bytearray(1), allPhys=bytearray(1), txPhys=bytearray(1), rxPhys=bytearray(1), phyOptions=GAPLeSetPhyRequestphyOptions.gLeCodingNoPreference_c):
        '''
        @param defaultMode: Use the provided values for all subsequent connections or provide a device ID for a single connection
        @param DeviceId: Device ID of the peer.
        @param allPhys: Bit mask indicating Host preferences on Tx and Rx Phy
        @param txPhys: Bit mask indicating Host preferences on Tx Phy
        @param rxPhys: Bit mask indicating Host preferences on Rx Phy
        @param phyOptions: Host preferences on Coded Phy
        '''
        self.defaultMode = defaultMode
        self.DeviceId = DeviceId
        self.allPhys = allPhys
        self.txPhys = txPhys
        self.rxPhys = rxPhys
        self.phyOptions = phyOptions


class GAPControllerEnhancedNotificationRequest(object):

    class EventType(object):

        def __init__(self, Value0x01=bytearray(1), Value0x02=bytearray(1), Value0x04=bytearray(1), Value0x08=bytearray(1), Value0x10=bytearray(1), Value0x20=bytearray(1), Value0x40=bytearray(1), Value0x80=bytearray(1), Value0x0100=bytearray(1), Value0x0200=bytearray(1), Value0x0400=bytearray(1)):
            self.Value0x01 = Value0x01
            self.Value0x02 = Value0x02
            self.Value0x04 = Value0x04
            self.Value0x08 = Value0x08
            self.Value0x10 = Value0x10
            self.Value0x20 = Value0x20
            self.Value0x40 = Value0x40
            self.Value0x80 = Value0x80
            self.Value0x0100 = Value0x0100
            self.Value0x0200 = Value0x0200
            self.Value0x0400 = Value0x0400

    def __init__(self, EventType=EventType(2), DeviceId=bytearray(1)):
        '''
        @param EventType: Events to enable.
        @param DeviceId: Device ID of the peer.
        '''
        self.EventType = EventType
        self.DeviceId = DeviceId


class GAPLoadKeysRequest(object):

    def __init__(self, NvmIndex=bytearray(1)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        '''
        self.NvmIndex = NvmIndex


class GAPSaveKeysRequest(object):

    class Keys_LtkInfo(object):

        def __init__(self, LtkSize=bytearray(1), Ltk=[]):
            self.LtkSize = LtkSize
            # Array length depends on LtkSize.
            self.Ltk = Ltk

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.LtkSize, 1)
            result += to_bytes(self.Ltk, self.LtkSize)
            return result

    class Keys_RandEdivInfo(object):

        def __init__(self, RandSize=bytearray(1), Rand=[], Ediv=bytearray(2)):
            self.RandSize = RandSize
            # Array length depends on RandSize.
            self.Rand = Rand
            self.Ediv = Ediv

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.RandSize, 1)
            result += to_bytes(self.Rand, self.RandSize)
            result += to_bytes(self.Ediv, 2)
            return result

    class Keys_AddressInfo(object):

        def __init__(self, DeviceAddressType=Keys_AddressInfoDeviceAddressType.gPublic_c, DeviceAddress=bytearray(6)):
            self.DeviceAddressType = DeviceAddressType
            # Unit length: 6 bytes
            self.DeviceAddress = DeviceAddress

        def pickle(self):
            result = bytearray()
            result += to_bytes(self.DeviceAddressType, 1)
            result += to_bytes(self.DeviceAddress, 6)
            return result

    def __init__(self, NvmIndex=bytearray(1), Keys_LtkIncluded=bytearray(1), Keys_LtkInfo=Keys_LtkInfo(), Keys_IrkIncluded=bytearray(1), Keys_Irk=[], Keys_CsrkIncluded=bytearray(1), Keys_Csrk=[], Keys_RandEdivInfo=Keys_RandEdivInfo(), Keys_AddressIncluded=[], Keys_AddressInfo=Keys_AddressInfo(), LeSc=bytearray(1), Authenticated=bytearray(1)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        @param Keys_LtkIncluded: Boolean value which indicates if LTK size and LTK are included or not
        @param Keys_LtkInfo: LTK information (size and value)
        @param Keys_IrkIncluded: Boolean value which indicates if IRK is included or not
        @param Keys_Irk: Identity Resolving Key
        @param Keys_CsrkIncluded: Boolean value which indicates if CSRK is included or not
        @param Keys_Csrk: Connection Signature Resolving Key
        @param Keys_RandEdivInfo: Rand information (size and value) and Ediv
        @param Keys_AddressIncluded: Boolean value which indicates if Address is included or not
        @param Keys_AddressInfo: Address information (type and value)
        @param LeSc: LE SC connections pairing
        @param Authenticated: Peer was authenticated during pairing
        '''
        self.NvmIndex = NvmIndex
        self.Keys_LtkIncluded = Keys_LtkIncluded
        self.Keys_LtkInfo = Keys_LtkInfo
        self.Keys_IrkIncluded = Keys_IrkIncluded
        self.Keys_Irk = Keys_Irk
        self.Keys_CsrkIncluded = Keys_CsrkIncluded
        self.Keys_Csrk = Keys_Csrk
        self.Keys_RandEdivInfo = Keys_RandEdivInfo
        self.Keys_AddressIncluded = Keys_AddressIncluded
        self.Keys_AddressInfo = Keys_AddressInfo
        self.LeSc = LeSc
        self.Authenticated = Authenticated

    def pickle(self):
        result = bytearray()
        result += to_bytes(self.NvmIndex, 1)
        result += to_bytes(self.Keys_LtkIncluded, 1)
        if self.Keys_LtkIncluded:
            result += self.Keys_LtkInfo.pickle()
        result += to_bytes(self.Keys_IrkIncluded, 1)
        if self.Keys_IrkIncluded:
            result += to_bytes(self.Keys_Irk, 16)
        result += to_bytes(self.Keys_CsrkIncluded, 1)
        if self.Keys_CsrkIncluded:
            result += to_bytes(self.Keys_Csrk, 16)
        if self.Keys_LtkIncluded:
            result += self.Keys_RandEdivInfo.pickle()
        if self.Keys_IrkIncluded:
            result += to_bytes(self.Keys_AddressIncluded, 1)
        if self.Keys_AddressIncluded:
            result += self.Keys_AddressInfo.pickle()
        result += to_bytes(self.LeSc, 1)
        result += to_bytes(self.Authenticated, 1)
        return result


class GAPSetChannelMapRequest(object):

    def __init__(self, ChannelMap=bytearray(5)):
        '''
        @param ChannelMap: Channel Map
        '''
        self.ChannelMap = ChannelMap


class GAPReadChannelMapRequest(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID of the peer.
        '''
        self.DeviceId = DeviceId


class GAPSetPrivacyModeRequest(object):

    def __init__(self, NvmIndex=bytearray(1), PrivacyMode=GAPSetPrivacyModeRequestPrivacyMode.gNetworkPrivacy_c):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        @param PrivacyMode: Privacy Mode
        '''
        self.NvmIndex = NvmIndex
        self.PrivacyMode = PrivacyMode




class FSCICPUResetRequest(object):

    pass


class FSCIGetNumberOfFreeBuffersRequest(object):

    pass


class FSCIAllowDeviceToSleepRequest(object):

    def __init__(self, SignalHostWhenWakeUp=FSCIAllowDeviceToSleepRequestSignalHostWhenWakeUp.FALSE, DeepSleepDuration=bytearray(4), DeepSleepMode=bytearray(1)):
        '''
        @param SignalHostWhenWakeUp: Signal Host When Wake Up
        @param DeepSleepDuration: Deep sleep duration in units of 16 us. Default value is 5 s
        @param DeepSleepMode: Deep sleep mode selection.
        '''
        self.SignalHostWhenWakeUp = SignalHostWhenWakeUp
        self.DeepSleepDuration = DeepSleepDuration
        self.DeepSleepMode = DeepSleepMode


class FSCIGetWakeupReasonRequest(object):

    pass


class FSCIGetNumberOfFreeBuffersResponse(object):

    def __init__(self, FreeBuffers=bytearray(2)):
        '''
        @param FreeBuffers: Number of free buffers
        '''
        self.FreeBuffers = FreeBuffers


class FSCIAckIndication(object):

    def __init__(self, Checksum=bytearray(1)):
        '''
        @param Checksum: Checksum of the FSCI packet being acknowledged
        '''
        self.Checksum = Checksum


class FSCIErrorIndication(object):

    def __init__(self, Status=FSCIErrorIndicationStatus.gFsciSuccess_c):
        '''
        @param Status: Occurred error
        '''
        self.Status = Status


class FSCIAllowDeviceToSleepConfirm(object):

    def __init__(self, Status=FSCIAllowDeviceToSleepConfirmStatus.gSuccess):
        '''
        @param Status: Status
        '''
        self.Status = Status


class FSCIWakeUpIndication(object):

    pass


class FSCIGetWakeupReasonResponse(object):

    def __init__(self, WakeUpReason=bytearray(1)):
        '''
        @param WakeUpReason: Wake Up Reason
        '''
        self.WakeUpReason = WakeUpReason



class L2CAPCBConfirm(object):

    def __init__(self, Status=L2CAPCBConfirmStatus.gBleSuccess_c):
        '''
        @param Status: The status of the L2CAP request
        '''
        self.Status = Status


class L2CAPCBLePsmConnectionRequestIndication(object):

    class LeCbConnectionRequest(object):

        def __init__(self, DeviceId=bytearray(1), LePsm=bytearray(2), PeerMtu=bytearray(2), PeerMps=bytearray(2), InitialCredits=bytearray(2)):
            self.DeviceId = DeviceId
            self.LePsm = LePsm
            self.PeerMtu = PeerMtu
            self.PeerMps = PeerMps
            self.InitialCredits = InitialCredits

    def __init__(self, InformationIncluded=bytearray(1), LeCbConnectionRequest=LeCbConnectionRequest()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbConnectionRequest: Connection request event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbConnectionRequest = LeCbConnectionRequest


class L2CAPCBLePsmConnectionCompleteIndication(object):

    class LeCbConnectionComplete(object):

        def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2), PeerMtu=bytearray(2), PeerMps=bytearray(2), InitialCredits=bytearray(2), Result=LeCbConnectionCompleteResult.gSuccessful_c):
            self.DeviceId = DeviceId
            self.ChannelId = ChannelId
            self.PeerMtu = PeerMtu
            self.PeerMps = PeerMps
            self.InitialCredits = InitialCredits
            self.Result = Result

    def __init__(self, InformationIncluded=bytearray(1), LeCbConnectionComplete=LeCbConnectionComplete()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbConnectionComplete: Connection complete event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbConnectionComplete = LeCbConnectionComplete


class L2CAPCBLePsmDisconnectNotificationIndication(object):

    class LeCbDisconnection(object):

        def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2)):
            self.DeviceId = DeviceId
            self.ChannelId = ChannelId

    def __init__(self, InformationIncluded=bytearray(1), LeCbDisconnection=LeCbDisconnection()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbDisconnection: Disconnection event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbDisconnection = LeCbDisconnection


class L2CAPCBNoPeerCreditsIndication(object):

    class LeCbNoPeerCredits(object):

        def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2)):
            self.DeviceId = DeviceId
            self.ChannelId = ChannelId

    def __init__(self, InformationIncluded=bytearray(1), LeCbNoPeerCredits=LeCbNoPeerCredits()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbNoPeerCredits: No peer credits event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbNoPeerCredits = LeCbNoPeerCredits


class L2CAPCBLocalCreditsNotificationIndication(object):

    class LeCbLocalCreditsNotification(object):

        def __init__(self, DeviceId=bytearray(1), ChannelId=bytearray(2), LocalCredits=bytearray(2)):
            self.DeviceId = DeviceId
            self.ChannelId = ChannelId
            self.LocalCredits = LocalCredits

    def __init__(self, InformationIncluded=bytearray(1), LeCbLocalCreditsNotification=LeCbLocalCreditsNotification()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbLocalCreditsNotification: Local credits notification event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbLocalCreditsNotification = LeCbLocalCreditsNotification


class L2CAPCBLeCbDataIndication(object):

    def __init__(self, DeviceId=bytearray(1), SrcCid=bytearray(2), PacketLength=bytearray(2), Packet=[]):
        '''
        @param DeviceId: The DeviceId from which data packet is received
        @param SrcCid: Source Channel Id
        @param PacketLength: Length of the received data packet
        @param Packet: The received data packet
        '''
        self.DeviceId = DeviceId
        self.SrcCid = SrcCid
        self.PacketLength = PacketLength
        self.Packet = Packet


class L2CAPCBErrorIndication(object):

    class LeCbError(object):

        def __init__(self, DeviceId=bytearray(1), Error=LeCbErrorError.gBleSuccess_c, l2caErrorSource_t=LeCbErrorl2caErrorSource_t.gL2ca_CancelConnection_c):
            self.DeviceId = DeviceId
            self.Error = Error
            self.l2caErrorSource_t = l2caErrorSource_t

    def __init__(self, InformationIncluded=bytearray(1), LeCbError=LeCbError()):
        '''
        @param InformationIncluded: Information is included or not
        @param LeCbError: Internal error event data
        '''
        self.InformationIncluded = InformationIncluded
        self.LeCbError = LeCbError


class GATTConfirm(object):

    def __init__(self, Status=GATTConfirmStatus.gBleSuccess_c):
        '''
        @param Status: The status of the GATT request
        '''
        self.Status = Status


class GATTGetMtuIndication(object):

    def __init__(self, Mtu=bytearray(2)):
        '''
        @param Mtu: MTU value
        '''
        self.Mtu = Mtu


class GATTClientProcedureExchangeMtuIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureExchangeMtuIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureExchangeMtuIndicationError.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error


class GATTClientProcedureDiscoverAllPrimaryServicesIndication(object):

    class DiscoveredServices(object):

        class Characteristics(object):

            class Value(object):

                def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                    self.Handle = Handle
                    self.UuidType = UuidType
                    # Array length depends on UuidType.
                    self.Uuid = Uuid
                    self.ValueLength = ValueLength
                    self.MaxValueLength = MaxValueLength
                    # Array length depends on ValueLength.
                    self.Value = Value

            class Descriptors(object):

                def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                    self.Handle = Handle
                    self.UuidType = UuidType
                    # Array length depends on UuidType.
                    self.Uuid = Uuid
                    self.ValueLength = ValueLength
                    self.MaxValueLength = MaxValueLength
                    # Array length depends on ValueLength.
                    self.Value = Value

            def __init__(self, Properties=CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
                self.Properties = Properties
                self.Value = Value
                self.NbOfDescriptors = NbOfDescriptors
                # Array length depends on NbOfDescriptors.
                self.Descriptors = Descriptors

        class IncludedServices(object):

            def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
                self.StartHandle = StartHandle
                self.EndHandle = EndHandle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.NbOfCharacteristics = NbOfCharacteristics
                self.NbOfIncludedServices = NbOfIncludedServices

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=DiscoveredServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), Characteristics=[], NbOfIncludedServices=bytearray(1), IncludedServices=[]):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            # Array length depends on NbOfCharacteristics.
            self.Characteristics = Characteristics
            self.NbOfIncludedServices = NbOfIncludedServices
            # Array length depends on NbOfIncludedServices.
            self.IncludedServices = IncludedServices

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureDiscoverAllPrimaryServicesIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureDiscoverAllPrimaryServicesIndicationError.gBleSuccess_c, NbOfDiscoveredServices=bytearray(1), DiscoveredServices=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param NbOfDiscoveredServices: Number of discovered services
        @param DiscoveredServices: Discovered services
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.NbOfDiscoveredServices = NbOfDiscoveredServices
        self.DiscoveredServices = DiscoveredServices


class GATTClientProcedureDiscoverPrimaryServicesByUuidIndication(object):

    class DiscoveredServices(object):

        class Characteristics(object):

            class Value(object):

                def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                    self.Handle = Handle
                    self.UuidType = UuidType
                    # Array length depends on UuidType.
                    self.Uuid = Uuid
                    self.ValueLength = ValueLength
                    self.MaxValueLength = MaxValueLength
                    # Array length depends on ValueLength.
                    self.Value = Value

            class Descriptors(object):

                def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                    self.Handle = Handle
                    self.UuidType = UuidType
                    # Array length depends on UuidType.
                    self.Uuid = Uuid
                    self.ValueLength = ValueLength
                    self.MaxValueLength = MaxValueLength
                    # Array length depends on ValueLength.
                    self.Value = Value

            def __init__(self, Properties=CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
                self.Properties = Properties
                self.Value = Value
                self.NbOfDescriptors = NbOfDescriptors
                # Array length depends on NbOfDescriptors.
                self.Descriptors = Descriptors

        class IncludedServices(object):

            def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
                self.StartHandle = StartHandle
                self.EndHandle = EndHandle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.NbOfCharacteristics = NbOfCharacteristics
                self.NbOfIncludedServices = NbOfIncludedServices

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=DiscoveredServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), Characteristics=[], NbOfIncludedServices=bytearray(1), IncludedServices=[]):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            # Array length depends on NbOfCharacteristics.
            self.Characteristics = Characteristics
            self.NbOfIncludedServices = NbOfIncludedServices
            # Array length depends on NbOfIncludedServices.
            self.IncludedServices = IncludedServices

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationError.gBleSuccess_c, NbOfDiscoveredServices=bytearray(1), DiscoveredServices=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param NbOfDiscoveredServices: Number of discovered services
        @param DiscoveredServices: Discovered services
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.NbOfDiscoveredServices = NbOfDiscoveredServices
        self.DiscoveredServices = DiscoveredServices


class GATTClientProcedureFindIncludedServicesIndication(object):

    class Service_Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        def __init__(self, Properties=Service_CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

    class Service_IncludedServices(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=Service_IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            self.NbOfIncludedServices = NbOfIncludedServices

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureFindIncludedServicesIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureFindIncludedServicesIndicationError.gBleSuccess_c, Service_StartHandle=bytearray(2), Service_EndHandle=bytearray(2), Service_UuidType=GATTClientProcedureFindIncludedServicesIndicationService_UuidType.Uuid16Bits, Service_Uuid=[], Service_NbOfCharacteristics=bytearray(1), Service_Characteristics=[], Service_NbOfIncludedServices=bytearray(1), Service_IncludedServices=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param Service_StartHandle: The handle of the Service Declaration attribute
        @param Service_EndHandle: The last handle belonging to this Service (followed by another Service declaration of the end of the database)
        @param Service_UuidType: UUID type
        @param Service_Uuid: UUID value
        @param Service_NbOfCharacteristics: Size of the Characteristic array
        @param Service_Characteristics: Characteristic array
        @param Service_NbOfIncludedServices: Size of the Included Services array
        @param Service_IncludedServices: Included Services array
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.Service_StartHandle = Service_StartHandle
        self.Service_EndHandle = Service_EndHandle
        self.Service_UuidType = Service_UuidType
        self.Service_Uuid = Service_Uuid
        self.Service_NbOfCharacteristics = Service_NbOfCharacteristics
        self.Service_Characteristics = Service_Characteristics
        self.Service_NbOfIncludedServices = Service_NbOfIncludedServices
        self.Service_IncludedServices = Service_IncludedServices


class GATTClientProcedureDiscoverAllCharacteristicsIndication(object):

    class Service_Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        def __init__(self, Properties=Service_CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

    class Service_IncludedServices(object):

        def __init__(self, StartHandle=bytearray(2), EndHandle=bytearray(2), UuidType=Service_IncludedServicesUuidType.Uuid16Bits, Uuid=[], NbOfCharacteristics=bytearray(1), NbOfIncludedServices=bytearray(1)):
            self.StartHandle = StartHandle
            self.EndHandle = EndHandle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.NbOfCharacteristics = NbOfCharacteristics
            self.NbOfIncludedServices = NbOfIncludedServices

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureDiscoverAllCharacteristicsIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureDiscoverAllCharacteristicsIndicationError.gBleSuccess_c, Service_StartHandle=bytearray(2), Service_EndHandle=bytearray(2), Service_UuidType=GATTClientProcedureDiscoverAllCharacteristicsIndicationService_UuidType.Uuid16Bits, Service_Uuid=[], Service_NbOfCharacteristics=bytearray(1), Service_Characteristics=[], Service_NbOfIncludedServices=bytearray(1), Service_IncludedServices=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param Service_StartHandle: The handle of the Service Declaration attribute
        @param Service_EndHandle: The last handle belonging to this Service (followed by another Service declaration of the end of the database)
        @param Service_UuidType: UUID type
        @param Service_Uuid: UUID value
        @param Service_NbOfCharacteristics: Size of the Characteristic array
        @param Service_Characteristics: Characteristic array
        @param Service_NbOfIncludedServices: Size of the Included Services array
        @param Service_IncludedServices: Included Services array
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.Service_StartHandle = Service_StartHandle
        self.Service_EndHandle = Service_EndHandle
        self.Service_UuidType = Service_UuidType
        self.Service_Uuid = Service_Uuid
        self.Service_NbOfCharacteristics = Service_NbOfCharacteristics
        self.Service_Characteristics = Service_Characteristics
        self.Service_NbOfIncludedServices = Service_NbOfIncludedServices
        self.Service_IncludedServices = Service_IncludedServices


class GATTClientProcedureDiscoverCharacteristicByUuidIndication(object):

    class Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        def __init__(self, Properties=CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureDiscoverCharacteristicByUuidIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureDiscoverCharacteristicByUuidIndicationError.gBleSuccess_c, NbOfCharacteristics=bytearray(1), Characteristics=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param NbOfCharacteristics: Number of discovered characteristics
        @param Characteristics: Characteristics that were filled
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.NbOfCharacteristics = NbOfCharacteristics
        self.Characteristics = Characteristics


class GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication(object):

    class Characteristic_Value(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

    class Characteristic_Descriptors(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationError.gBleSuccess_c, Characteristic_Properties=GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationCharacteristic_Properties.gNone_c, Characteristic_Value=Characteristic_Value(), Characteristic_NbOfDescriptors=bytearray(1), Characteristic_Descriptors=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param Characteristic_Properties: Characteristic Properties as defined by GATT
        @param Characteristic_Value: Characteristic Value attribute
        @param Characteristic_NbOfDescriptors: Size of the Characteristic Descriptors array
        @param Characteristic_Descriptors: Characteristic Descriptors array
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.Characteristic_Properties = Characteristic_Properties
        self.Characteristic_Value = Characteristic_Value
        self.Characteristic_NbOfDescriptors = Characteristic_NbOfDescriptors
        self.Characteristic_Descriptors = Characteristic_Descriptors


class GATTClientProcedureReadCharacteristicValueIndication(object):

    class Characteristic_Value(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

    class Characteristic_Descriptors(object):

        def __init__(self, Handle=bytearray(2), UuidType=Characteristic_DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
            self.Handle = Handle
            self.UuidType = UuidType
            # Array length depends on UuidType.
            self.Uuid = Uuid
            self.ValueLength = ValueLength
            self.MaxValueLength = MaxValueLength
            # Array length depends on ValueLength.
            self.Value = Value

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureReadCharacteristicValueIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureReadCharacteristicValueIndicationError.gBleSuccess_c, Characteristic_Properties=GATTClientProcedureReadCharacteristicValueIndicationCharacteristic_Properties.gNone_c, Characteristic_Value=Characteristic_Value(), Characteristic_NbOfDescriptors=bytearray(1), Characteristic_Descriptors=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param Characteristic_Properties: Characteristic Properties as defined by GATT
        @param Characteristic_Value: Characteristic Value attribute
        @param Characteristic_NbOfDescriptors: Size of the Characteristic Descriptors array
        @param Characteristic_Descriptors: Characteristic Descriptors array
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.Characteristic_Properties = Characteristic_Properties
        self.Characteristic_Value = Characteristic_Value
        self.Characteristic_NbOfDescriptors = Characteristic_NbOfDescriptors
        self.Characteristic_Descriptors = Characteristic_Descriptors


class GATTClientProcedureReadUsingCharacteristicUuidIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureReadUsingCharacteristicUuidIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureReadUsingCharacteristicUuidIndicationError.gBleSuccess_c, NbOfReadBytes=bytearray(2), ReadBytes=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param NbOfReadBytes: The number of bytes that were read
        @param ReadBytes: The bytes that were read
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.NbOfReadBytes = NbOfReadBytes
        self.ReadBytes = ReadBytes


class GATTClientProcedureReadMultipleCharacteristicValuesIndication(object):

    class Characteristics(object):

        class Value(object):

            def __init__(self, Handle=bytearray(2), UuidType=ValueUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        class Descriptors(object):

            def __init__(self, Handle=bytearray(2), UuidType=DescriptorsUuidType.Uuid16Bits, Uuid=[], ValueLength=bytearray(2), MaxValueLength=bytearray(2), Value=[]):
                self.Handle = Handle
                self.UuidType = UuidType
                # Array length depends on UuidType.
                self.Uuid = Uuid
                self.ValueLength = ValueLength
                self.MaxValueLength = MaxValueLength
                # Array length depends on ValueLength.
                self.Value = Value

        def __init__(self, Properties=CharacteristicsProperties.gNone_c, Value=Value(), NbOfDescriptors=bytearray(1), Descriptors=[]):
            self.Properties = Properties
            self.Value = Value
            self.NbOfDescriptors = NbOfDescriptors
            # Array length depends on NbOfDescriptors.
            self.Descriptors = Descriptors

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureReadMultipleCharacteristicValuesIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureReadMultipleCharacteristicValuesIndicationError.gBleSuccess_c, NbOfCharacteristics=bytearray(1), Characteristics=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param NbOfCharacteristics: Number of characteristics whose values were read
        @param Characteristics: Characteristics whose values were read
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.NbOfCharacteristics = NbOfCharacteristics
        self.Characteristics = Characteristics


class GATTClientProcedureWriteCharacteristicValueIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureWriteCharacteristicValueIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureWriteCharacteristicValueIndicationError.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error


class GATTClientProcedureReadCharacteristicDescriptorIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureReadCharacteristicDescriptorIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureReadCharacteristicDescriptorIndicationError.gBleSuccess_c, Descriptor_Handle=bytearray(2), Descriptor_UuidType=GATTClientProcedureReadCharacteristicDescriptorIndicationDescriptor_UuidType.Uuid16Bits, Descriptor_Uuid=[], Descriptor_ValueLength=bytearray(2), Descriptor_MaxValueLength=bytearray(2), Descriptor_Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        @param Descriptor_Handle: Attribute handle
        @param Descriptor_UuidType: UUID type
        @param Descriptor_Uuid: UUID value
        @param Descriptor_ValueLength: Length of the attribute value array
        @param Descriptor_MaxValueLength: Maximum length of the attribute value array; if this is set to 0, then the attribute's length is fixed and cannot be changed
        @param Descriptor_Value: Attribute value array
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error
        self.Descriptor_Handle = Descriptor_Handle
        self.Descriptor_UuidType = Descriptor_UuidType
        self.Descriptor_Uuid = Descriptor_Uuid
        self.Descriptor_ValueLength = Descriptor_ValueLength
        self.Descriptor_MaxValueLength = Descriptor_MaxValueLength
        self.Descriptor_Value = Descriptor_Value


class GATTClientProcedureWriteCharacteristicDescriptorIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureResult=GATTClientProcedureWriteCharacteristicDescriptorIndicationProcedureResult.gGattProcSuccess_c, Error=GATTClientProcedureWriteCharacteristicDescriptorIndicationError.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureResult: The result of the completed procedure
        @param Error: If procedureResult is not gSuccess_c, this contains the error that terminated the procedure
        '''
        self.DeviceId = DeviceId
        self.ProcedureResult = ProcedureResult
        self.Error = Error


class GATTClientNotificationIndication(object):

    def __init__(self, DeviceId=bytearray(1), CharacteristicValueHandle=bytearray(2), ValueLength=bytearray(2), Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param CharacteristicValueHandle: Handle of the Characteristic Value attribute to be notified
        @param ValueLength: Value array size
        @param Value: The Characteristic value array
        '''
        self.DeviceId = DeviceId
        self.CharacteristicValueHandle = CharacteristicValueHandle
        self.ValueLength = ValueLength
        self.Value = Value


class GATTClientIndicationIndication(object):

    def __init__(self, DeviceId=bytearray(1), CharacteristicValueHandle=bytearray(2), ValueLength=bytearray(2), Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param CharacteristicValueHandle: Handle of the Characteristic Value attribute to be indicated
        @param ValueLength: Value array size
        @param Value: The Characteristic value array
        '''
        self.DeviceId = DeviceId
        self.CharacteristicValueHandle = CharacteristicValueHandle
        self.ValueLength = ValueLength
        self.Value = Value


class GATTServerMtuChangedIndication(object):

    def __init__(self, DeviceId=bytearray(1), MtuChangedEvent_NewMtu=bytearray(2)):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param MtuChangedEvent_NewMtu: Value of the agreed ATT_MTU for this connection
        '''
        self.DeviceId = DeviceId
        self.MtuChangedEvent_NewMtu = MtuChangedEvent_NewMtu


class GATTServerHandleValueConfirmationIndication(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the active connection
        '''
        self.DeviceId = DeviceId


class GATTServerAttributeWrittenIndication(object):

    def __init__(self, DeviceId=bytearray(1), AttributeWrittenEvent_Handle=bytearray(2), AttributeWrittenEvent_ValueLength=bytearray(2), AttributeWrittenEvent_Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param AttributeWrittenEvent_Handle: Handle of the attribute
        @param AttributeWrittenEvent_ValueLength: Length of the attribute value array
        @param AttributeWrittenEvent_Value: Attribute value array attempted to be written
        '''
        self.DeviceId = DeviceId
        self.AttributeWrittenEvent_Handle = AttributeWrittenEvent_Handle
        self.AttributeWrittenEvent_ValueLength = AttributeWrittenEvent_ValueLength
        self.AttributeWrittenEvent_Value = AttributeWrittenEvent_Value


class GATTServerCharacteristicCccdWrittenIndication(object):

    def __init__(self, DeviceId=bytearray(1), CharCccdWrittenEvent_Handle=bytearray(2), CharCccdWrittenEvent_NewCccd=GATTServerCharacteristicCccdWrittenIndicationCharCccdWrittenEvent_NewCccd.gCccdEmpty_c):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param CharCccdWrittenEvent_Handle: Handle of the CCCD attribute
        @param CharCccdWrittenEvent_NewCccd: New value of the CCCD
        '''
        self.DeviceId = DeviceId
        self.CharCccdWrittenEvent_Handle = CharCccdWrittenEvent_Handle
        self.CharCccdWrittenEvent_NewCccd = CharCccdWrittenEvent_NewCccd


class GATTServerAttributeWrittenWithoutResponseIndication(object):

    def __init__(self, DeviceId=bytearray(1), AttributeWrittenEvent_Handle=bytearray(2), AttributeWrittenEvent_ValueLength=bytearray(2), AttributeWrittenEvent_Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param AttributeWrittenEvent_Handle: Handle of the attribute
        @param AttributeWrittenEvent_ValueLength: Length of the attribute value array
        @param AttributeWrittenEvent_Value: Attribute value array attempted to be written
        '''
        self.DeviceId = DeviceId
        self.AttributeWrittenEvent_Handle = AttributeWrittenEvent_Handle
        self.AttributeWrittenEvent_ValueLength = AttributeWrittenEvent_ValueLength
        self.AttributeWrittenEvent_Value = AttributeWrittenEvent_Value


class GATTServerErrorIndication(object):

    def __init__(self, DeviceId=bytearray(1), ProcedureError_ProcedureType=GATTServerErrorIndicationProcedureError_ProcedureType.gSendAttributeWrittenStatus_c, ProcedureError_Error=GATTServerErrorIndicationProcedureError_Error.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param ProcedureError_ProcedureType: Procedure that generated error
        @param ProcedureError_Error: Error generated
        '''
        self.DeviceId = DeviceId
        self.ProcedureError_ProcedureType = ProcedureError_ProcedureType
        self.ProcedureError_Error = ProcedureError_Error


class GATTServerLongCharacteristicWrittenIndication(object):

    def __init__(self, DeviceId=bytearray(1), LongCharacteristicWrittenEvent_Handle=bytearray(2), LongCharacteristicWrittenEvent_ValueLength=bytearray(2), LongCharacteristicWrittenEvent_Value=[]):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param LongCharacteristicWrittenEvent_Handle: Handle of the characteristic value
        @param LongCharacteristicWrittenEvent_ValueLength: Length of the characteristic value
        @param LongCharacteristicWrittenEvent_Value: Characteristic value array
        '''
        self.DeviceId = DeviceId
        self.LongCharacteristicWrittenEvent_Handle = LongCharacteristicWrittenEvent_Handle
        self.LongCharacteristicWrittenEvent_ValueLength = LongCharacteristicWrittenEvent_ValueLength
        self.LongCharacteristicWrittenEvent_Value = LongCharacteristicWrittenEvent_Value


class GATTServerAttributeReadIndication(object):

    def __init__(self, DeviceId=bytearray(1), AttributeReadEvent_Handle=bytearray(2)):
        '''
        @param DeviceId: Device ID identifying the active connection
        @param AttributeReadEvent_Handle: Handle of the attribute
        '''
        self.DeviceId = DeviceId
        self.AttributeReadEvent_Handle = AttributeReadEvent_Handle


class GATTDBConfirm(object):

    def __init__(self, Status=GATTDBConfirmStatus.gBleSuccess_c):
        '''
        @param Status: The status of the GATT Database request
        '''
        self.Status = Status


class GATTDBReadAttributeIndication(object):

    def __init__(self, ValueLength=bytearray(2), Value=[]):
        '''
        @param ValueLength: Attribute value length
        @param Value: Attribute value
        '''
        self.ValueLength = ValueLength
        self.Value = Value


class GATTDBFindServiceHandleIndication(object):

    def __init__(self, ServiceHandle=bytearray(2)):
        '''
        @param ServiceHandle: Service handle
        '''
        self.ServiceHandle = ServiceHandle


class GATTDBFindCharValueHandleInServiceIndication(object):

    def __init__(self, CharValueHandle=bytearray(2)):
        '''
        @param CharValueHandle: Characteristic value handle
        '''
        self.CharValueHandle = CharValueHandle


class GATTDBFindCccdHandleForCharValueHandleIndication(object):

    def __init__(self, CccdHandle=bytearray(2)):
        '''
        @param CccdHandle: CCCD handle
        '''
        self.CccdHandle = CccdHandle


class GATTDBFindDescriptorHandleForCharValueHandleIndication(object):

    def __init__(self, DescriptorHandle=bytearray(2)):
        '''
        @param DescriptorHandle: Descriptor handle
        '''
        self.DescriptorHandle = DescriptorHandle


class GATTDBDynamicAddPrimaryServiceDeclarationIndication(object):

    def __init__(self, ServiceHandle=bytearray(2)):
        '''
        @param ServiceHandle: Handle of the Service declaration
        '''
        self.ServiceHandle = ServiceHandle


class GATTDBDynamicAddSecondaryServiceDeclarationIndication(object):

    def __init__(self, ServiceHandle=bytearray(2)):
        '''
        @param ServiceHandle: Handle of the Service declaration
        '''
        self.ServiceHandle = ServiceHandle


class GATTDBDynamicAddIncludeDeclarationIndication(object):

    def __init__(self, IncludeHandle=bytearray(2)):
        '''
        @param IncludeHandle: Handle of the Include declaration
        '''
        self.IncludeHandle = IncludeHandle


class GATTDBDynamicAddCharacteristicDeclarationAndValueIndication(object):

    def __init__(self, CharacteristicHandle=bytearray(2)):
        '''
        @param CharacteristicHandle: Handle of the Characteristic declaration
        '''
        self.CharacteristicHandle = CharacteristicHandle


class GATTDBDynamicAddCharacteristicDescriptorIndication(object):

    def __init__(self, DescriptorHandle=bytearray(2)):
        '''
        @param DescriptorHandle: Handle of the Descriptor declaration
        '''
        self.DescriptorHandle = DescriptorHandle


class GATTDBDynamicAddCccdIndication(object):

    def __init__(self, CCCDHandle=bytearray(2)):
        '''
        @param CCCDHandle: Handle of the CCCD declaration
        '''
        self.CCCDHandle = CCCDHandle


class GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication(object):

    def __init__(self, CharacteristicHandle=bytearray(2)):
        '''
        @param CharacteristicHandle: Handle of the Characteristic declaration
        '''
        self.CharacteristicHandle = CharacteristicHandle


class GATTDBDynamicAddCharDescriptorWithUniqueValueIndication(object):

    def __init__(self, DescriptorHandle=bytearray(2)):
        '''
        @param DescriptorHandle: Handle of the Descriptor declaration
        '''
        self.DescriptorHandle = DescriptorHandle


class GAPConfirm(object):

    def __init__(self, Status=GAPConfirmStatus.gBleSuccess_c):
        '''
        @param Status: The status of the GAP request
        '''
        self.Status = Status


class GAPCheckNotificationStatusIndication(object):

    def __init__(self, IsActive=bytearray(1)):
        '''
        @param IsActive: Notification status
        '''
        self.IsActive = IsActive


class GAPCheckIndicationStatusIndication(object):

    def __init__(self, IsActive=bytearray(1)):
        '''
        @param IsActive: Indication status
        '''
        self.IsActive = IsActive


class GAPLoadKeysIndication(object):

    class Keys_LtkInfo(object):

        def __init__(self, LtkSize=bytearray(1), Ltk=[]):
            self.LtkSize = LtkSize
            # Array length depends on LtkSize.
            self.Ltk = Ltk

    class Keys_RandEdivInfo(object):

        def __init__(self, RandSize=bytearray(1), Rand=[], Ediv=bytearray(2)):
            self.RandSize = RandSize
            # Array length depends on RandSize.
            self.Rand = Rand
            self.Ediv = Ediv

    class Keys_AddressInfo(object):

        def __init__(self, DeviceAddressType=Keys_AddressInfoDeviceAddressType.gPublic_c, DeviceAddress=bytearray(6)):
            self.DeviceAddressType = DeviceAddressType
            # Unit length: 6 bytes
            self.DeviceAddress = DeviceAddress

    def __init__(self, Keys_LtkIncluded=bytearray(1), Keys_LtkInfo=Keys_LtkInfo(), Keys_IrkIncluded=bytearray(1), Keys_Irk=[], Keys_CsrkIncluded=bytearray(1), Keys_Csrk=[], Keys_RandEdivInfo=Keys_RandEdivInfo(), Keys_AddressIncluded=[], Keys_AddressInfo=Keys_AddressInfo(), KeyFlags=bytearray(1), LeSc=bytearray(1), Authenticated=bytearray(1)):
        '''
        @param Keys_LtkIncluded: Boolean value which indicates if LTK size and LTK are included or not
        @param Keys_LtkInfo: LTK information (size and value)
        @param Keys_IrkIncluded: Boolean value which indicates if IRK is included or not
        @param Keys_Irk: Identity Resolving Key
        @param Keys_CsrkIncluded: Boolean value which indicates if CSRK is included or not
        @param Keys_Csrk: Connection Signature Resolving Key
        @param Keys_RandEdivInfo: Rand information (size and value) and Ediv
        @param Keys_AddressIncluded: Boolean value which indicates if Address is included or not
        @param Keys_AddressInfo: Address information (type and value)
        @param KeyFlags: Mask identifying the keys stored
        @param LeSc: LE SC pairing
        @param Authenticated: Peer is authenticated during pairing
        '''
        self.Keys_LtkIncluded = Keys_LtkIncluded
        self.Keys_LtkInfo = Keys_LtkInfo
        self.Keys_IrkIncluded = Keys_IrkIncluded
        self.Keys_Irk = Keys_Irk
        self.Keys_CsrkIncluded = Keys_CsrkIncluded
        self.Keys_Csrk = Keys_Csrk
        self.Keys_RandEdivInfo = Keys_RandEdivInfo
        self.Keys_AddressIncluded = Keys_AddressIncluded
        self.Keys_AddressInfo = Keys_AddressInfo
        self.KeyFlags = KeyFlags
        self.LeSc = LeSc
        self.Authenticated = Authenticated


class GAPLoadEncryptionInformationIndication(object):

    def __init__(self, LtkSize=bytearray(1), Ltk=[]):
        '''
        @param LtkSize: LTK size
        @param Ltk: LTK value
        '''
        self.LtkSize = LtkSize
        self.Ltk = Ltk


class GAPLoadCustomPeerInformationIndication(object):

    def __init__(self, InfoSize=bytearray(2), Info=[]):
        '''
        @param InfoSize: Data size
        @param Info: Data value
        '''
        self.InfoSize = InfoSize
        self.Info = Info


class GAPCheckIfBondedIndication(object):

    def __init__(self, IsBonded=bytearray(1), NvmIndex=bytearray(1)):
        '''
        @param IsBonded: Bonded flag
        @param NvmIndex: NVM Index
        '''
        self.IsBonded = IsBonded
        self.NvmIndex = NvmIndex


class GAPGetBondedDevicesCountIndication(object):

    def __init__(self, NbOfBondedDevices=bytearray(1)):
        '''
        @param NbOfBondedDevices: Number of bonded devices
        '''
        self.NbOfBondedDevices = NbOfBondedDevices


class GAPGetBondedDeviceNameIndication(object):

    def __init__(self, NameSize=bytearray(1), Name=[]):
        '''
        @param NameSize: The name size
        @param Name: The name value
        '''
        self.NameSize = NameSize
        self.Name = Name


class GAPGenericEventInitializationCompleteIndication(object):

    def __init__(self, initCompleteData_SupportedFeatures=bytearray(4), initCompleteData_MaxAdvDataSize=bytearray(2), initCompleteData_NumOfSupportedAdvSets=bytearray(1), initCompleteData_PeriodicAdvListSize=bytearray(1)):
        '''
        @param initCompleteData_SupportedFeatures: local supported features
        @param initCompleteData_MaxAdvDataSize: The maximum length of data supported by the Controller for use as advertisement data or scan response data in an advertising event or as periodic advertisement data
        @param initCompleteData_NumOfSupportedAdvSets: number of supported advertising sets
        @param initCompleteData_PeriodicAdvListSize: periodic advertiser list size
        '''
        self.initCompleteData_SupportedFeatures = initCompleteData_SupportedFeatures
        self.initCompleteData_MaxAdvDataSize = initCompleteData_MaxAdvDataSize
        self.initCompleteData_NumOfSupportedAdvSets = initCompleteData_NumOfSupportedAdvSets
        self.initCompleteData_PeriodicAdvListSize = initCompleteData_PeriodicAdvListSize


class GAPGenericEventInternalErrorIndication(object):

    def __init__(self, InternalError_ErrorCode=GAPGenericEventInternalErrorIndicationInternalError_ErrorCode.gBleSuccess_c, InternalError_ErrorSource=GAPGenericEventInternalErrorIndicationInternalError_ErrorSource.gHciCommandStatus_c, InternalError_HciCommandOpcode=bytearray(2)):
        '''
        @param InternalError_ErrorCode: Error code
        @param InternalError_ErrorSource: Error source
        @param InternalError_HciCommandOpcode: HCI command operation code
        '''
        self.InternalError_ErrorCode = InternalError_ErrorCode
        self.InternalError_ErrorSource = InternalError_ErrorSource
        self.InternalError_HciCommandOpcode = InternalError_HciCommandOpcode


class GAPGenericEventAdvertisingSetupFailedIndication(object):

    def __init__(self, SetupFailReason=GAPGenericEventAdvertisingSetupFailedIndicationSetupFailReason.gBleSuccess_c):
        '''
        @param SetupFailReason: Setup fail reason
        '''
        self.SetupFailReason = SetupFailReason


class GAPGenericEventAdvertisingParametersSetupCompleteIndication(object):

    pass


class GAPGenericEventAdvertisingDataSetupCompleteIndication(object):

    pass


class GAPGenericEventWhiteListSizeReadIndication(object):

    def __init__(self, WhiteListSize=bytearray(1)):
        '''
        @param WhiteListSize: White list size
        '''
        self.WhiteListSize = WhiteListSize


class GAPGenericEventDeviceAddedToWhiteListIndication(object):

    pass


class GAPGenericEventDeviceRemovedFromWhiteListIndication(object):

    pass


class GAPGenericEventWhiteListClearedIndication(object):

    pass


class GAPGenericEventRandomAddressReadyIndication(object):

    def __init__(self, Address=bytearray(6), Handle=bytearray(1)):
        '''
        @param Address: Random address
        @param Handle: Advertising set handle if the generated device address will be used on an extended set, 0xFF otherwise
        '''
        self.Address = Address
        self.Handle = Handle


class GAPGenericEventCreateConnectionCanceledIndication(object):

    pass


class GAPGenericEventPublicAddressReadIndication(object):

    def __init__(self, Address=bytearray(6)):
        '''
        @param Address: Public address
        '''
        self.Address = Address


class GAPGenericEventAdvTxPowerLevelReadIndication(object):

    def __init__(self, AdvTxPowerLevel=bytearray(1)):
        '''
        @param AdvTxPowerLevel: Advertising transmission power level (in dBm)
        '''
        self.AdvTxPowerLevel = AdvTxPowerLevel


class GAPGenericEventPrivateResolvableAddressVerifiedIndication(object):

    def __init__(self, Verified=bytearray(1)):
        '''
        @param Verified: Private Resolvable Address verified
        '''
        self.Verified = Verified


class GAPGenericEventRandomAddressSetIndication(object):

    def __init__(self, Handle=bytearray(1)):
        '''
        @param Handle: Advertising handle of the configured set or 0xFF in case of legacy advertising or scanning and initiating address
        '''
        self.Handle = Handle


class GAPAdvertisingEventStateChangedIndication(object):

    pass


class GAPAdvertisingEventCommandFailedIndication(object):

    def __init__(self, FailReason=GAPAdvertisingEventCommandFailedIndicationFailReason.gBleSuccess_c):
        '''
        @param FailReason: The reason of failure
        '''
        self.FailReason = FailReason


class GAPScanningEventStateChangedIndication(object):

    pass


class GAPScanningEventCommandFailedIndication(object):

    def __init__(self, FailReason=GAPScanningEventCommandFailedIndicationFailReason.gBleSuccess_c):
        '''
        @param FailReason: The reason of failure
        '''
        self.FailReason = FailReason


class GAPScanningEventDeviceScannedIndication(object):

    def __init__(self, ScannedDevice_AddressType=GAPScanningEventDeviceScannedIndicationScannedDevice_AddressType.gPublic_c, ScannedDevice_Address=bytearray(6), ScannedDevice_Rssi=bytearray(1), ScannedDevice_DataLength=bytearray(1), ScannedDevice_Data=[], ScannedDevice_AdvEventType=GAPScanningEventDeviceScannedIndicationScannedDevice_AdvEventType.gBleAdvRepAdvInd_c, ScannedDevice_DirectRpaUsed=bytearray(1), ScannedDevice_DirectRpa=[], ScannedDevice_advertisingAddressResolved=bytearray(1)):
        '''
        @param ScannedDevice_AddressType: Device's advertising address type
        @param ScannedDevice_Address: Device's advertising address
        @param ScannedDevice_Rssi: RSSI on the advertising channel; may be compared to the TX power contained in the AD Structure of type gAdTxPowerLevel_c to estimate distance from the advertiser
        @param ScannedDevice_DataLength: Length of the advertising or scan response data
        @param ScannedDevice_Data: Advertising or scan response data
        @param ScannedDevice_AdvEventType: Advertising report type, indicating what type of event generated this data (advertising, scan response)
        @param ScannedDevice_DirectRpaUsed: TRUE if directed advertising with Resolvable Private Address as Direct Address was detected while Enhanced Privacy is enabled
        @param ScannedDevice_DirectRpa: Resolvable Private Address set as Direct Address for directed advertising
        @param ScannedDevice_advertisingAddressResolved: TRUE if the address contained in the addressType and aAddress fields is the identity address of a resolved RPA from the Advertising Address field
        '''
        self.ScannedDevice_AddressType = ScannedDevice_AddressType
        self.ScannedDevice_Address = ScannedDevice_Address
        self.ScannedDevice_Rssi = ScannedDevice_Rssi
        self.ScannedDevice_DataLength = ScannedDevice_DataLength
        self.ScannedDevice_Data = ScannedDevice_Data
        self.ScannedDevice_AdvEventType = ScannedDevice_AdvEventType
        self.ScannedDevice_DirectRpaUsed = ScannedDevice_DirectRpaUsed
        self.ScannedDevice_DirectRpa = ScannedDevice_DirectRpa
        self.ScannedDevice_advertisingAddressResolved = ScannedDevice_advertisingAddressResolved


class GAPConnectionEventConnectedIndication(object):

    def __init__(self, DeviceId=bytearray(1), ConnectionParameters_ConnInterval=bytearray(2), ConnectionParameters_ConnLatency=bytearray(2), ConnectionParameters_SupervisionTimeout=bytearray(2), ConnectionParameters_MasterClockAccuracy=GAPConnectionEventConnectedIndicationConnectionParameters_MasterClockAccuracy.gMasterClkAcc500ppm_c, PeerAddressType=GAPConnectionEventConnectedIndicationPeerAddressType.gPublic_c, PeerAddress=bytearray(6), peerRpaResolved=bytearray(1), peerRpa=[], localRpaUsed=bytearray(1), localRpa=[], connectionRole=GAPConnectionEventConnectedIndicationconnectionRole.gBleLlConnectionMaster_c):
        '''
        @param DeviceId: Device ID identifying the connection
        @param ConnectionParameters_ConnInterval: Interval between connection events
        @param ConnectionParameters_ConnLatency: Number of consecutive connection events the Slave may ignore
        @param ConnectionParameters_SupervisionTimeout: The maximum time interval between consecutive over-the-air packets; if this timer expires, the connection is dropped
        @param ConnectionParameters_MasterClockAccuracy: Accuracy of master's clock, allowing for frame detection optimizations
        @param PeerAddressType: Connected device's address type
        @param PeerAddress: Connected device's address
        @param peerRpaResolved: TRUE if the address defined by peerAddressType and peerAddress is the identity address of the peer, and the peer used an RPA that was resolved by the Controller and is contained in the peerRpa field
        @param peerRpa: Peer Resolvable Private Address if Controller Privacy is active and peerRpaResolved is TRUE
        @param localRpaUsed: TRUE if the Controller has used an RPA contained in the localRpa field
        @param localRpa: Local Resolvable Private Address if Controller Privacy is active and localRpaUsed is TRUE
        @param connectionRole: The role of the device in the connection - central (master) or peripheral (slave) 
        '''
        self.DeviceId = DeviceId
        self.ConnectionParameters_ConnInterval = ConnectionParameters_ConnInterval
        self.ConnectionParameters_ConnLatency = ConnectionParameters_ConnLatency
        self.ConnectionParameters_SupervisionTimeout = ConnectionParameters_SupervisionTimeout
        self.ConnectionParameters_MasterClockAccuracy = ConnectionParameters_MasterClockAccuracy
        self.PeerAddressType = PeerAddressType
        self.PeerAddress = PeerAddress
        self.peerRpaResolved = peerRpaResolved
        self.peerRpa = peerRpa
        self.localRpaUsed = localRpaUsed
        self.localRpa = localRpa
        self.connectionRole = connectionRole


class GAPConnectionEventPairingRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1), PairingParameters_WithBonding=bytearray(1), PairingParameters_SecurityModeAndLevel=GAPConnectionEventPairingRequestIndicationPairingParameters_SecurityModeAndLevel.gMode1Level1_c, PairingParameters_MaxEncryptionKeySize=bytearray(1), PairingParameters_LocalIoCapabilities=GAPConnectionEventPairingRequestIndicationPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c, PairingParameters_OobAvailable=bytearray(1), PairingParameters_CentralKeys=bytearray(1), PairingParameters_PeripheralKeys=bytearray(1), PairingParameters_LeSecureConnectionSupported=bytearray(1), PairingParameters_UseKeypressNotifications=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param PairingParameters_WithBonding: TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
        @param PairingParameters_SecurityModeAndLevel: The desired security mode-level
        @param PairingParameters_MaxEncryptionKeySize: Maximum LTK size supported by the device
        @param PairingParameters_LocalIoCapabilities: I/O capabilities used to determine the pairing method
        @param PairingParameters_OobAvailable: TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
        @param PairingParameters_CentralKeys: SMP keys to be distributed by the Central
        @param PairingParameters_PeripheralKeys: SMP keys to be distributed by the Peripheral
        @param PairingParameters_LeSecureConnectionSupported: indicates if device supports LE Secure Connections pairing
        @param PairingParameters_UseKeypressNotifications: Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
        '''
        self.DeviceId = DeviceId
        self.PairingParameters_WithBonding = PairingParameters_WithBonding
        self.PairingParameters_SecurityModeAndLevel = PairingParameters_SecurityModeAndLevel
        self.PairingParameters_MaxEncryptionKeySize = PairingParameters_MaxEncryptionKeySize
        self.PairingParameters_LocalIoCapabilities = PairingParameters_LocalIoCapabilities
        self.PairingParameters_OobAvailable = PairingParameters_OobAvailable
        self.PairingParameters_CentralKeys = PairingParameters_CentralKeys
        self.PairingParameters_PeripheralKeys = PairingParameters_PeripheralKeys
        self.PairingParameters_LeSecureConnectionSupported = PairingParameters_LeSecureConnectionSupported
        self.PairingParameters_UseKeypressNotifications = PairingParameters_UseKeypressNotifications


class GAPConnectionEventSlaveSecurityRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1), SlaveSecurityRequestParameters_BondAfterPairing=bytearray(1), SlaveSecurityRequestParameters_bAuthenticationRequired=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param SlaveSecurityRequestParameters_BondAfterPairing: TRUE if the Slave supports bonding, FALSE otherwise
        @param SlaveSecurityRequestParameters_bAuthenticationRequired: TRUE if the slave requires authentication for MITM protection, FALSE otherwise
        '''
        self.DeviceId = DeviceId
        self.SlaveSecurityRequestParameters_BondAfterPairing = SlaveSecurityRequestParameters_BondAfterPairing
        self.SlaveSecurityRequestParameters_bAuthenticationRequired = SlaveSecurityRequestParameters_bAuthenticationRequired


class GAPConnectionEventPairingResponseIndication(object):

    def __init__(self, DeviceId=bytearray(1), PairingParameters_WithBonding=bytearray(1), PairingParameters_SecurityModeAndLevel=GAPConnectionEventPairingResponseIndicationPairingParameters_SecurityModeAndLevel.gMode1Level1_c, PairingParameters_MaxEncryptionKeySize=bytearray(1), PairingParameters_LocalIoCapabilities=GAPConnectionEventPairingResponseIndicationPairingParameters_LocalIoCapabilities.gIoDisplayOnly_c, PairingParameters_OobAvailable=bytearray(1), PairingParameters_CentralKeys=bytearray(1), PairingParameters_PeripheralKeys=bytearray(1), PairingParameters_LeSecureConnectionSupported=bytearray(1), PairingParameters_UseKeypressNotifications=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param PairingParameters_WithBonding: TRUE if this device is able to and wants to bond after pairing, FALSE otherwise
        @param PairingParameters_SecurityModeAndLevel: The desired security mode-level
        @param PairingParameters_MaxEncryptionKeySize: Maximum LTK size supported by the device
        @param PairingParameters_LocalIoCapabilities: I/O capabilities used to determine the pairing method
        @param PairingParameters_OobAvailable: TRUE if this device has Out-of-Band data that can be used for authenticated pairing, FALSE otherwise
        @param PairingParameters_CentralKeys: SMP keys to be distributed by the Central
        @param PairingParameters_PeripheralKeys: SMP keys to be distributed by the Peripheral
        @param PairingParameters_LeSecureConnectionSupported: indicates if device supports LE Secure Connections pairing
        @param PairingParameters_UseKeypressNotifications: Indicates if device supports Keypress Notification PDUs during Passkey Entry pairing
        '''
        self.DeviceId = DeviceId
        self.PairingParameters_WithBonding = PairingParameters_WithBonding
        self.PairingParameters_SecurityModeAndLevel = PairingParameters_SecurityModeAndLevel
        self.PairingParameters_MaxEncryptionKeySize = PairingParameters_MaxEncryptionKeySize
        self.PairingParameters_LocalIoCapabilities = PairingParameters_LocalIoCapabilities
        self.PairingParameters_OobAvailable = PairingParameters_OobAvailable
        self.PairingParameters_CentralKeys = PairingParameters_CentralKeys
        self.PairingParameters_PeripheralKeys = PairingParameters_PeripheralKeys
        self.PairingParameters_LeSecureConnectionSupported = PairingParameters_LeSecureConnectionSupported
        self.PairingParameters_UseKeypressNotifications = PairingParameters_UseKeypressNotifications


class GAPConnectionEventAuthenticationRejectedIndication(object):

    def __init__(self, DeviceId=bytearray(1), RejectReason=GAPConnectionEventAuthenticationRejectedIndicationRejectReason.gOobNotAvailable_c):
        '''
        @param DeviceId: Device ID identifying the connection
        @param RejectReason: The reason of the rejection
        '''
        self.DeviceId = DeviceId
        self.RejectReason = RejectReason


class GAPConnectionEventPasskeyRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        '''
        self.DeviceId = DeviceId


class GAPConnectionEventOobRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        '''
        self.DeviceId = DeviceId


class GAPConnectionEventPasskeyDisplayIndication(object):

    def __init__(self, DeviceId=bytearray(1), PasskeyForDisplay=bytearray(4)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param PasskeyForDisplay: Passkey to be displayed by this Slave
        '''
        self.DeviceId = DeviceId
        self.PasskeyForDisplay = PasskeyForDisplay


class GAPConnectionEventKeyExchangeRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1), RequestedKeys=bytearray(1), RequestedLtkSize=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param RequestedKeys: Mask identifying the keys being requested
        @param RequestedLtkSize: Requested size of the encryption key
        '''
        self.DeviceId = DeviceId
        self.RequestedKeys = RequestedKeys
        self.RequestedLtkSize = RequestedLtkSize


class GAPConnectionEventKeysReceivedIndication(object):

    class Keys_LtkInfo(object):

        def __init__(self, LtkSize=bytearray(1), Ltk=[]):
            self.LtkSize = LtkSize
            # Array length depends on LtkSize.
            self.Ltk = Ltk

    class Keys_RandEdivInfo(object):

        def __init__(self, RandSize=bytearray(1), Rand=[], Ediv=bytearray(2)):
            self.RandSize = RandSize
            # Array length depends on RandSize.
            self.Rand = Rand
            self.Ediv = Ediv

    class Keys_AddressInfo(object):

        def __init__(self, DeviceAddressType=Keys_AddressInfoDeviceAddressType.gPublic_c, DeviceAddress=bytearray(6)):
            self.DeviceAddressType = DeviceAddressType
            # Unit length: 6 bytes
            self.DeviceAddress = DeviceAddress

    def __init__(self, DeviceId=bytearray(1), Keys_LtkIncluded=bytearray(1), Keys_LtkInfo=Keys_LtkInfo(), Keys_IrkIncluded=bytearray(1), Keys_Irk=[], Keys_CsrkIncluded=bytearray(1), Keys_Csrk=[], Keys_RandEdivInfo=Keys_RandEdivInfo(), Keys_AddressIncluded=[], Keys_AddressInfo=Keys_AddressInfo()):
        '''
        @param DeviceId: Device ID identifying the connection
        @param Keys_LtkIncluded: Boolean value which indicates if LTK size and LTK are included or not
        @param Keys_LtkInfo: LTK information (size and value)
        @param Keys_IrkIncluded: Boolean value which indicates if IRK is included or not
        @param Keys_Irk: Identity Resolving Key
        @param Keys_CsrkIncluded: Boolean value which indicates if CSRK is included or not
        @param Keys_Csrk: Connection Signature Resolving Key
        @param Keys_RandEdivInfo: Rand information (size and value) and Ediv
        @param Keys_AddressIncluded: Boolean value which indicates if Address is included or not
        @param Keys_AddressInfo: Address information (type and value)
        '''
        self.DeviceId = DeviceId
        self.Keys_LtkIncluded = Keys_LtkIncluded
        self.Keys_LtkInfo = Keys_LtkInfo
        self.Keys_IrkIncluded = Keys_IrkIncluded
        self.Keys_Irk = Keys_Irk
        self.Keys_CsrkIncluded = Keys_CsrkIncluded
        self.Keys_Csrk = Keys_Csrk
        self.Keys_RandEdivInfo = Keys_RandEdivInfo
        self.Keys_AddressIncluded = Keys_AddressIncluded
        self.Keys_AddressInfo = Keys_AddressInfo


class GAPConnectionEventLongTermKeyRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1), Ediv=bytearray(2), RandSize=bytearray(1), Rand=[]):
        '''
        @param DeviceId: Device ID identifying the connection
        @param Ediv: The Encryption Diversifier, as defined by the SMP
        @param RandSize: Random number size
        @param Rand: The Random number, as defined by the SMP
        '''
        self.DeviceId = DeviceId
        self.Ediv = Ediv
        self.RandSize = RandSize
        self.Rand = Rand


class GAPConnectionEventEncryptionChangedIndication(object):

    def __init__(self, DeviceId=bytearray(1), NewEncryptionState=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param NewEncryptionState: TRUE if link has been encrypted, FALSE if encryption was paused or removed
        '''
        self.DeviceId = DeviceId
        self.NewEncryptionState = NewEncryptionState


class GAPConnectionEventPairingCompleteIndication(object):

    class PairingSuccessful(object):

        def __init__(self, WithBonding=bytearray(1)):
            self.WithBonding = WithBonding

    class PairingFailed(object):

        def __init__(self, FailReason=PairingFailedFailReason.gBleSuccess_c):
            self.FailReason = FailReason

    def __init__(self, DeviceId=bytearray(1), PairingStatus=GAPConnectionEventPairingCompleteIndicationPairingStatus.PairingSuccessful, PairingData=[]):
        '''
        @param DeviceId: Device ID identifying the connection
        @param PairingStatus: Pairing status
        @param PairingData: Information of pairing completion
        '''
        self.DeviceId = DeviceId
        self.PairingStatus = PairingStatus
        self.PairingData = PairingData


class GAPConnectionEventDisconnectedIndication(object):

    def __init__(self, DeviceId=bytearray(1), Reason=GAPConnectionEventDisconnectedIndicationReason.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the connection
        @param Reason: Reason for disconnection
        '''
        self.DeviceId = DeviceId
        self.Reason = Reason


class GAPConnectionEventRssiReadIndication(object):

    def __init__(self, DeviceId=bytearray(1), Rssi=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param Rssi: Value of the RSSI
        '''
        self.DeviceId = DeviceId
        self.Rssi = Rssi


class GAPConnectionEventTxPowerLevelReadIndication(object):

    def __init__(self, DeviceId=bytearray(1), TxPowerLevel=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param TxPowerLevel: Value of the TX power
        '''
        self.DeviceId = DeviceId
        self.TxPowerLevel = TxPowerLevel


class GAPConnectionEventPowerReadFailureIndication(object):

    def __init__(self, DeviceId=bytearray(1), FailReason=GAPConnectionEventPowerReadFailureIndicationFailReason.gBleSuccess_c):
        '''
        @param DeviceId: Device ID identifying the connection
        @param FailReason: Reason for power reading failure
        '''
        self.DeviceId = DeviceId
        self.FailReason = FailReason


class GAPConnectionEventParameterUpdateRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1), ConnectionParameterUpdateRequest_IntervalMin=bytearray(2), ConnectionParameterUpdateRequest_IntervalMax=bytearray(2), ConnectionParameterUpdateRequest_SlaveLatency=bytearray(2), ConnectionParameterUpdateRequest_TimeoutMultiplier=bytearray(2)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param ConnectionParameterUpdateRequest_IntervalMin: Minimum interval
        @param ConnectionParameterUpdateRequest_IntervalMax: Maximum interval
        @param ConnectionParameterUpdateRequest_SlaveLatency: Slave latency
        @param ConnectionParameterUpdateRequest_TimeoutMultiplier: Timeout multiplier
        '''
        self.DeviceId = DeviceId
        self.ConnectionParameterUpdateRequest_IntervalMin = ConnectionParameterUpdateRequest_IntervalMin
        self.ConnectionParameterUpdateRequest_IntervalMax = ConnectionParameterUpdateRequest_IntervalMax
        self.ConnectionParameterUpdateRequest_SlaveLatency = ConnectionParameterUpdateRequest_SlaveLatency
        self.ConnectionParameterUpdateRequest_TimeoutMultiplier = ConnectionParameterUpdateRequest_TimeoutMultiplier


class GAPConnectionEventParameterUpdateCompleteIndication(object):

    def __init__(self, DeviceId=bytearray(1), ConnectionParameterUpdateComplete_Status=GAPConnectionEventParameterUpdateCompleteIndicationConnectionParameterUpdateComplete_Status.gBleSuccess_c, ConnectionParameterUpdateComplete_ConnInterval=bytearray(2), ConnectionParameterUpdateComplete_ConnLatency=bytearray(2), ConnectionParameterUpdateComplete_SupervisionTimeout=bytearray(2)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param ConnectionParameterUpdateComplete_Status: The status of the request
        @param ConnectionParameterUpdateComplete_ConnInterval: Connection interval
        @param ConnectionParameterUpdateComplete_ConnLatency: Connection latency
        @param ConnectionParameterUpdateComplete_SupervisionTimeout: Supervision timeout
        '''
        self.DeviceId = DeviceId
        self.ConnectionParameterUpdateComplete_Status = ConnectionParameterUpdateComplete_Status
        self.ConnectionParameterUpdateComplete_ConnInterval = ConnectionParameterUpdateComplete_ConnInterval
        self.ConnectionParameterUpdateComplete_ConnLatency = ConnectionParameterUpdateComplete_ConnLatency
        self.ConnectionParameterUpdateComplete_SupervisionTimeout = ConnectionParameterUpdateComplete_SupervisionTimeout


class GAPConnectionEventLeDataLengthChangedIndication(object):

    def __init__(self, DeviceId=bytearray(1), LeDataLengthChanged_MaxTxOctets=bytearray(2), LeDataLengthChanged_MaxTxTime=bytearray(2), LeDataLengthChanged_MaxRxOctets=bytearray(2), LeDataLengthChanged_MaxRxTime=bytearray(2)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param LeDataLengthChanged_MaxTxOctets: The maximum number of payload octets in a Link Layer Data Channel PDU to transmit on this connection
        @param LeDataLengthChanged_MaxTxTime: The maximum time that the local Controller will take to send a Link Layer Data Channel PDU on this connection
        @param LeDataLengthChanged_MaxRxOctets: The maximum number of payload octets in a Link Layer Data Channel PDU to receive on this connection
        @param LeDataLengthChanged_MaxRxTime: The maximum time that the local Controller will take to receive a Link Layer Data Channel PDU on this connection
        '''
        self.DeviceId = DeviceId
        self.LeDataLengthChanged_MaxTxOctets = LeDataLengthChanged_MaxTxOctets
        self.LeDataLengthChanged_MaxTxTime = LeDataLengthChanged_MaxTxTime
        self.LeDataLengthChanged_MaxRxOctets = LeDataLengthChanged_MaxRxOctets
        self.LeDataLengthChanged_MaxRxTime = LeDataLengthChanged_MaxRxTime


class GAPConnectionEventLeScOobDataRequestIndication(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: Device ID identifying the connection
        '''
        self.DeviceId = DeviceId


class GAPConnectionEventLeScDisplayNumericValueIndication(object):

    def __init__(self, DeviceId=bytearray(1), ncValue=bytearray(4)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param ncValue: A number between 0 and 999999 decimal which must be confirmed by the user on both pairing devices
        '''
        self.DeviceId = DeviceId
        self.ncValue = ncValue


class GAPConnectionEventLeScKeypressNotificationIndication(object):

    def __init__(self, DeviceId=bytearray(1), GapLeScKeypressNotificationParams_keypressNotifType=GAPConnectionEventLeScKeypressNotificationIndicationGapLeScKeypressNotificationParams_keypressNotifType.gKnPasskeyEntryStarted_c):
        '''
        @param DeviceId: Device ID identifying the connection
        @param GapLeScKeypressNotificationParams_keypressNotifType: keypressNotifType
        '''
        self.DeviceId = DeviceId
        self.GapLeScKeypressNotificationParams_keypressNotifType = GapLeScKeypressNotificationParams_keypressNotifType


class GAPLeScPublicKeyRegeneratedIndication(object):

    pass


class GAPGenericEventLeScLocalOobDataIndication(object):

    def __init__(self, RandomValue=bytearray(16), ConfirmValue=bytearray(16)):
        '''
        @param RandomValue: LE SC OOB r (Random value)
        @param ConfirmValue: LE SC OOB Cr (Random Confirm value)
        '''
        self.RandomValue = RandomValue
        self.ConfirmValue = ConfirmValue


class GAPGenericEventHostPrivacyStateChangedIndication(object):

    def __init__(self, NewHostPrivacyState=bytearray(1)):
        '''
        @param NewHostPrivacyState: Indicates the new state of the host privacy: TRUE if enabled, FALSE if disabled
        '''
        self.NewHostPrivacyState = NewHostPrivacyState


class GAPGenericEventControllerPrivacyStateChangedIndication(object):

    def __init__(self, NewControllerPrivacyState=bytearray(1)):
        '''
        @param NewControllerPrivacyState: Indicates the new state of the controller privacy: TRUE if enabled, FALSE if disabled
        '''
        self.NewControllerPrivacyState = NewControllerPrivacyState


class GAPGenericEventTxPowerLevelSetCompleteIndication(object):

    def __init__(self, status=bytearray(1)):
        '''
        @param status: Indicates the status of the Set Tx Power Level request
        '''
        self.status = status


class GAPGenericEventLePhyEventIndication(object):

    def __init__(self, eventType=GAPGenericEventLePhyEventIndicationeventType.gPhySetDefaultComplete_c, DeviceId=bytearray(1), txPhy=GAPGenericEventLePhyEventIndicationtxPhy(), rxPhy=GAPGenericEventLePhyEventIndicationrxPhy()):
        '''
        @param eventType: Specifies the Phy event type
        @param DeviceId: Device ID identifying the connection
        @param txPhy: Specifies the Tx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type.
        @param rxPhy: Specifies the Rx Phy, valid only for gPhyRead_c or gPhyUpdateComplete_c event type.
        '''
        self.eventType = eventType
        self.DeviceId = DeviceId
        self.txPhy = txPhy
        self.rxPhy = rxPhy


class GAPGetBondedDevicesIdentityInformationIndication(object):

    class IdentityAddresses(object):

        def __init__(self, IdentityAddressType=IdentityAddressesIdentityAddressType.gPublic_c, IdentityAddress=bytearray(6), Irk=bytearray(16), PrivacyMode=IdentityAddressesPrivacyMode.gNetworkPrivacy_c):
            self.IdentityAddressType = IdentityAddressType
            # Unit length: 6 bytes
            self.IdentityAddress = IdentityAddress
            # Unit length: 16 bytes
            self.Irk = Irk
            self.PrivacyMode = PrivacyMode

    def __init__(self, NbOfDeviceIdentityAddresses=bytearray(1), IdentityAddresses=[]):
        '''
        @param NbOfDeviceIdentityAddresses: The number of device identity addresses
        @param IdentityAddresses: Identity addresses list
        '''
        self.NbOfDeviceIdentityAddresses = NbOfDeviceIdentityAddresses
        self.IdentityAddresses = IdentityAddresses


class GAPControllerNotificationIndication(object):

    def __init__(self, EventType=bytearray(2), DeviceId=bytearray(1), RSSI=bytearray(1), Channel=bytearray(1), ConnEvCounter=bytearray(2), Status=bytearray(1), Timestamp=bytearray(2), AdvHandle=bytearray(1)):
        '''
        @param EventType: Events type.
        @param DeviceId: Device ID identifying the connection
        @param RSSI: RSSI, valid for Rx event types
        @param Channel: Channel, valid for conn event over or Rx/Tx events
        @param ConnEvCounter: Connection event counter, valid for conn event over or Conn Rx event
        @param Status: Status of the request to select which events to be enabled/disabled
        @param Timestamp: Timestamp of the event, valid for conn created or Conn Rx event
        @param AdvHandle: Advertising Handle, valid for advertising events from multiple sets
        '''
        self.EventType = EventType
        self.DeviceId = DeviceId
        self.RSSI = RSSI
        self.Channel = Channel
        self.ConnEvCounter = ConnEvCounter
        self.Status = Status
        self.Timestamp = Timestamp
        self.AdvHandle = AdvHandle


class GAPBondCreatedIndication(object):

    def __init__(self, NvmIndex=bytearray(1), AddrType=GAPBondCreatedIndicationAddrType.gPublic_c, Addr=bytearray(6)):
        '''
        @param NvmIndex: Index of the device in NVM bonding area
        @param AddrType: BLE Address Type
        @param Addr: BLE Address
        '''
        self.NvmIndex = NvmIndex
        self.AddrType = AddrType
        self.Addr = Addr


class GAPGenericEventChannelMapSetIndication(object):

    pass


class GAPConnectionEventChannelMapReadIndication(object):

    def __init__(self, DeviceId=bytearray(1), ChannelMap=bytearray(5)):
        '''
        @param DeviceId: Device ID identifying the connection
        @param ChannelMap: Channel Map
        '''
        self.DeviceId = DeviceId
        self.ChannelMap = ChannelMap


class GAPConnectionEventChannelMapReadFailureIndication(object):

    def __init__(self, FailReason=GAPConnectionEventChannelMapReadFailureIndicationFailReason.gBleSuccess_c):
        '''
        @param FailReason: Reason for channel read failure
        '''
        self.FailReason = FailReason


class GAPConnectionEventChannelSelectionAlgorithm2Indication(object):

    def __init__(self, DeviceId=bytearray(1)):
        '''
        @param DeviceId: The DeviceId for which the command is intended
        '''
        self.DeviceId = DeviceId







