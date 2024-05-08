#!/usr/bin/env python
'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

import os
from random import randint
import sys
from threading import Event, Thread
from time import sleep

sys.path.append(os.path.abspath('../../../..'))
from com.nxp.wireless_connectivity.commands.ble.ble_sig_defines import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.commands.ble.gatt_database_dynamic import *
from com.nxp.wireless_connectivity.commands.ble.heart_rate_interface import *  # @UnusedWildImport
from com.nxp.wireless_connectivity.commands.ble.sync_requests import *  # @UnusedWildImport


CharProp = GATTDBDynamicAddCharacteristicDeclarationAndValueRequestCharacteristicProperties
CharPerm = GATTDBDynamicAddCharacteristicDeclarationAndValueRequestValueAccessPermissions

mHeartRateReportInterval_c = 1
mBatteryLevelReportInterval_c = 5

INVALID_HANDLE = 0xFF
mHrsServiceHandle = INVALID_HANDLE
mBsServiceHandle = INVALID_HANDLE
mDisServiceHandle = INVALID_HANDLE

mLocalPasskey = 999999

mLtk = [0xD6, 0x93, 0xE8, 0xA4, 0x23, 0x55, 0x48, 0x99,
        0x1D, 0x77, 0x61, 0xE6, 0x63, 0x2B, 0x10, 0x8E]
mIrk = [0x0A, 0x2D, 0xF4, 0x65, 0xE3, 0xBD, 0x7B, 0x49,
        0x1E, 0xB4, 0xC0, 0x95, 0x95, 0x13, 0x46, 0x73]
mCsrk = [0x90, 0xD5, 0x06, 0x95, 0x92, 0xED, 0x91, 0xD7,
         0xA8, 0x9E, 0x2C, 0xDC, 0x4A, 0x93, 0x5B, 0xF9]

mRand = [0x26, 0x1E, 0xF6, 0x09, 0x97, 0x2E, 0xAD, 0x7E]
mEdiv = 0x1F99


def usage():
    '''
    Define the command-line interface.
    '''
    import argparse

    parser = argparse.ArgumentParser(description='BLE demo app which implements a ble_fsci_heart_rate_sensor.')
    parser.add_argument('dev', metavar='<serial_port ble_fsci_black_box>', type=str, help='Kinetis-W system device node.')
    parser.add_argument('-p', '--pair', help='Use pairing, passkey is 999999', action='store_true')
    args = parser.parse_args()
    print(args)

    return args


class BLEDevice(object):
    '''
    Class which defines the actions performed on a generic BLE device.
    Services implemented: GATT, GAP, Device Info.
    '''

    def __init__(self, args):
        self.serial_port = args.dev
        self.pair = args.pair
        self.protocol = args.protocol
        self.framer = FsciFramer(
            self.serial_port, ack_policy=FsciAckPolicy.GLOBAL, protocol=self.protocol, baudrate=Baudrate.BR115200)

        subscribe_to_async_ble_events_from(self.serial_port)

        if args.reset:
            FSCICPUReset(self.serial_port, protocol=self.protocol)
            sleep(7)

        self.handles = {}
        self.client_device_id = None
        self.ble_device_address = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

        self.framer.addObserver(
            GAPConnectionEventConnectedIndicationObserver('GAPConnectionEventConnectedIndication'),
            self.cb_gap_conn_event_connected_cb
        )

        self.framer.addObserver(
            GAPConnectionEventDisconnectedIndicationObserver(
                'GAPConnectionEventDisconnectedIndication'),
            self.cb_gap_conn_event_disconnected_cb
        )

        self.framer.addObserver(
            GAPConnectionEventPairingRequestIndicationObserver(
                'GAPConnectionEventPairingRequestIndication'),
            self.cb_gap_conn_event_pairing_request_cb
        )

        self.framer.addObserver(
            GAPConnectionEventKeyExchangeRequestIndicationObserver(
                'GAPConnectionEventKeyExchangeRequestIndication'),
            self.cb_gap_conn_event_key_exchange_request_cb
        )

        self.framer.addObserver(
            GAPConnectionEventPairingCompleteIndicationObserver(
                'GAPConnectionEventPairingCompleteIndication'),
            self.cb_gap_conn_event_pairing_complete_cb
        )

        self.gap_event_connected = Event()

    def cb_gap_conn_event_connected_cb(self, _, event):
        '''
        Callback executed when a smartphone connects to this device.

        @param event: GAPConnectionEventConnectedIndication
        '''
        print_event(self.serial_port, event)
        self.client_device_id = event.DeviceId
        if not self.pair:
            self.gap_event_connected.set()
        else:
            sleep(1)

    def cb_gap_conn_event_disconnected_cb(self, _, event):
        '''
        Callback executed when a smartphone disconnects from this device.

        @param event: GAPConnectionEventdisConnectedIndication
        '''
        print_event(self.serial_port, event)
        self.gap_event_connected.clear()

    def cb_gap_conn_event_pairing_request_cb(self, _, event):
        '''
        Callback executed when a pairing request is received from a device.
        @param event: GAPConnectionEventPairingRequestIndication
        '''
        print_event(self.serial_port, event)
        self.gap_accept_pairing_req()

    def cb_gap_conn_event_key_exchange_request_cb(self, _, event):
        '''
        Callback executed when a key exchange request is received from a device.
        @param event: GAPConnectionEventKeyExchangeRequestIndication
        '''
        print_event(self.serial_port, event)
        self.gap_send_smp_keys_req(event)

    def cb_gap_conn_event_pairing_complete_cb(self, _, event):
        '''
        Callback executed when pairing complete is received from a device.
        @param event: GAPConnectionEventPairingCompleteIndication
        '''
        print_event(self.serial_port, event)
        self.gap_event_connected.set()

    def gattdb_dynamic_add_psd(self, service_uuid, retries=1):
        '''
        Declare a primary service.

        @param service_uuid: UUID of the service
        @return: handle of the service
        '''
        ind = GATTDBDynamicAddPrimaryServiceDeclaration(
            self.serial_port,
            UuidType=UuidType.Uuid16Bits,
            Uuid=service_uuid,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gattdb_dynamic_add_psd(service_uuid, 0)
        if ind is None:
            return None

        print('\tService Handle for UUID 0x%04X ->' % service_uuid, ind.ServiceHandle)
        self.handles[service_uuid] = ind.ServiceHandle
        return ind.ServiceHandle

    def gattdb_dynamic_add_cdv(self, char_uuid, char_prop, maxval_len, initval, val_perm, retries=1):
        '''
        Declare a characteristic and assign it a value.

        @param char_uuid: UUID of the characteristic
        @param char_prop: properties of the characteristic
        @param maxval_len: maximum length of the value
        @param initval: initial value
        @param val_perm: access permissions on the value
        @return: handle of the characteristic
        '''
        ind = GATTDBDynamicAddCharacteristicDeclarationAndValue(
            self.serial_port,
            UuidType=UuidType.Uuid16Bits,
            Uuid=char_uuid,
            CharacteristicProperties=char_prop,
            MaxValueLength=maxval_len,
            InitialValueLength=len(initval),
            InitialValue=initval,
            ValueAccessPermissions=val_perm,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gattdb_dynamic_add_cdv(char_uuid, char_prop, maxval_len, initval, val_perm, 0)
        if ind is None:
            return None

        print('\tCharacteristic Handle for UUID 0x%04X ->' % char_uuid, ind.CharacteristicHandle)
        self.handles[char_uuid] = ind.CharacteristicHandle
        return ind.CharacteristicHandle

    def gattdb_dynamic_add_cccd(self, retries=1):
        '''
        Add a Client Characteristic Configuration Descriptor.

        @return: handle of the CCCD
        '''
        ind = GATTDBDynamicAddCccd(self.serial_port, protocol=self.protocol)
        if ind is None and retries != 0:
            return self.gattdb_dynamic_add_cccd(0)
        if ind is None:
            return None

        print('\tCCCD Handle ->', ind.CCCDHandle)
        return ind.CCCDHandle

    def gattdb_dynamic_add_cd(self, uuid, val, desc_perm, retries=1):
        '''
        Add a characteristic descriptor.

        @param uuid: UUID of the descriptor
        @param val: value of the descriptor
        @param desc_perm: access permissions on the descriptor
        @return: handle of the descriptor
        '''
        ind = GATTDBDynamicAddCharacteristicDescriptor(
            self.serial_port,
            UuidType=UuidType.Uuid16Bits,
            Uuid=uuid,
            DescriptorValueLength=len(val),
            Value=val,
            DescriptorAccessPermissions=desc_perm,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gattdb_dynamic_add_cd(uuid, val, desc_perm, 0)
        if ind is None:
            return None

        print('\tDescriptor Handle for UUID 0x%04X ->' % uuid, ind.DescriptorHandle)
        self.handles[uuid] = ind.DescriptorHandle
        return ind.DescriptorHandle

    def gattdb_add_service_gatt(self):
        '''
        Sequence of commands to add the GATT service.
        '''
        self.gattdb_dynamic_add_psd(service_uuid=gBleSig_GenericAttributeProfile_d)
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_GattServiceChanged_d,
            char_prop=CharProp.gRead_c | CharProp.gNotify_c,
            maxval_len=0,
            initval=mGattDbDynamic_GattServiceChangedInitValue,
            val_perm=CharPerm.gPermissionNone_c
        )
        self.handles['GATT_CCCD'] = self.gattdb_dynamic_add_cccd()

    def gattdb_add_service_gap(self):
        '''
        Sequence of commands to add the GAP service.
        '''
        self.gattdb_dynamic_add_psd(service_uuid=gBleSig_GenericAccessProfile_d)
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_GapDeviceName_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0x14,
            initval=mGattDbDynamic_GapServiceDeviceNameInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_GapAppearance_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_GapServiceAppearanceInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_GapPpcp_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_GapServicePpcpInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )

    def gattdb_add_service_device_info(self):
        '''
        Sequence of commands to add the Device Info service.
        '''
        self.mDisServiceHandle = self.gattdb_dynamic_add_psd(
            service_uuid=gBleSig_DeviceInformationService_d)
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_ManufacturerNameString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceManufNameInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_ModelNumberString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceModelNbInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_SerialNumberString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceSerialNoInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_HardwareRevisionString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceHwRevInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_FirmwareRevisionString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceFwRevInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_SoftwareRevisionString_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceSwRevInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_SystemId_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceSysIdInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_IeeeRcdl_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_DIServiceIeeeRcdlInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )

    def gap_read_public_dev_addr(self, retries=1):
        '''
        Read the public address of the device.

        @return: address as upper case hex string
        '''
        ind = GAPReadPublicDeviceAddress(self.serial_port, protocol=self.protocol)
        if ind is None and retries != 0:
            return self.gap_read_public_dev_addr(0)
        if ind is None:
            return None

        addr = ''.join('%02X' % x for x in ind.Address)
        print('\tPublic Device Address ->', addr)
        self.ble_device_address = addr
        return addr

    def gap_register_device_security_requirements(self):
        '''
        Set the device service security requirements.
        '''
        CentralSec = GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements.CentralSecurityRequirements(
            SecurityModeLevel=RequirementsSecurityModeLevel.gMode1Level1_c,
            Authorization=False,
            MinimumEncryptionKeySize=7
        )

        ReqStructure = GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements.GapServiceSecurityRequirements.Requirements(
            SecurityModeLevel=RequirementsSecurityModeLevel.gMode1Level3_c,
            Authorization=False,
            MinimumEncryptionKeySize=7
        )

        ServiceStructures = []
        ServiceStructures.append(GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements.GapServiceSecurityRequirements(
            ServiceHandle=self.mHrsServiceHandle,
            Requirements=ReqStructure
        ))

        ServiceStructures.append(GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements.GapServiceSecurityRequirements(
            ServiceHandle=self.mBsServiceHandle,
            Requirements=ReqStructure
        ))

        ServiceStructures.append(GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements.GapServiceSecurityRequirements(
            ServiceHandle=self.mDisServiceHandle,
            Requirements=ReqStructure
        ))

        SecurityRequirement = GAPRegisterDeviceSecurityRequirementsRequest.SecurityRequirements(
            CentralSecurityRequirements=CentralSec,
            NbOfServices=3,
            GapServiceSecurityRequirements=ServiceStructures
        )

        GAPRegisterDeviceSecurityRequirements(
            self.serial_port,
            SecurityRequirementsIncluded=1,
            SecurityRequirements=SecurityRequirement,
            protocol=self.protocol
        )

    def gap_set_local_passkey(self):
        '''
        Set the local passkey.
        '''
        GAPSetLocalPasskey(
            self.serial_port,
            mLocalPasskey,
            protocol=self.protocol
        )
        sleep(.1)

    def gap_accept_pairing_req(self):
        '''
        GAP pairing request received through event
        '''
        GAPAcceptPairingRequest(
            self.serial_port,
            DeviceId=self.client_device_id,
            PairingParameters_WithBonding=False,
            PairingParameters_SecurityModeAndLevel=RequirementsSecurityModeLevel.gMode1Level3_c,
            PairingParameters_MaxEncryptionKeySize=0x10,
            PairingParameters_LocalIoCapabilities=False,
            PairingParameters_OobAvailable=False,
            PairingParameters_CentralKeys=0x02, # gIrk_c
            PairingParameters_PeripheralKeys=0x03, # gLtk_c | gIrk_c
            PairingParameters_LeSecureConnectionSupported=True,
            PairingParameters_UseKeypressNotifications=False,
            protocol=self.protocol
        )
        sleep(.1)

    def gap_send_smp_keys_req(self, event):
        '''
        GAP key exchange request received, send SMP keys
        '''
        # Long Term Key
        gLtk_c = 0x01
        # Identity Resolving Key
        gIrk_c = 0x02
        # Connection Signature Resolving Key
        gCsrk_c = 0x04

        ltkIncluded, irkIncluded, csrkIncluded = False, False, False

        if event.RequestedKeys & gLtk_c:
            ltkIncluded = True
        if event.RequestedKeys & gIrk_c:
            irkIncluded = True
        if event.RequestedKeys & gCsrk_c:
            csrkIncluded = True

        LtkInfo = GAPSendSmpKeysRequest.Keys_LtkInfo(
            LtkSize=event.RequestedLtkSize,
            Ltk=mLtk[:event.RequestedLtkSize],
        )

        RandEdivInfo = GAPSendSmpKeysRequest.Keys_RandEdivInfo(
            RandSize=len(mRand),
            Rand=mRand,
            Ediv=mEdiv
        )

        AddressInfo = GAPSendSmpKeysRequest.Keys_AddressInfo(
            DeviceAddress=self.ble_device_address
        )

        GAPSendSmpKeys(
            self.serial_port,
            self.client_device_id,
            Keys_LtkIncluded=ltkIncluded,
            Keys_LtkInfo=LtkInfo,
            Keys_IrkIncluded=irkIncluded,
            Keys_Irk=mIrk,
            Keys_CsrkIncluded=csrkIncluded,
            Keys_Csrk=mCsrk,
            Keys_RandEdivInfo=RandEdivInfo,
            Keys_AddressIncluded=True,
            Keys_AddressInfo=AddressInfo,
            protocol=self.protocol
        )
        sleep(.1)

    def gap_set_adv_parameters():
        '''
        Set the advertising parameters.
        '''
        ind = GAPSetAdvertisingParameters(
            self.serial_port,
            AdvertisingParameters_MinInterval=0x0030,
            AdvertisingParameters_MaxInterval=0x0030,
            AdvertisingParameters_ChannelMap=0x7,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gap_set_adv_parameters(0)
        if ind is None:
            return None


    def gap_set_adv_data(self, retries=1):
        '''
        Set the advertising data. Assert on wrong type of indication.
        '''
        AdStructures = []
        AdStructures.append(GAPSetAdvertisingDataRequest.AdvertisingData.AdStructures(
            Length=1,
            Type=AdStructuresType.gAdFlags_c,
            Data=0x06
        ))
        AdStructures.append(GAPSetAdvertisingDataRequest.AdvertisingData.AdStructures(
            Length=2,
            Type=AdStructuresType.gAdIncomplete16bitServiceList_c,
            Data=gBleSig_HeartRateService_d
        ))
        AdStructures.append(GAPSetAdvertisingDataRequest.AdvertisingData.AdStructures(
            Length=len('NXP_HRS'),
            Type=AdStructuresType.gAdShortenedLocalName_c,
            Data='NXP_HRS'
        ))

        ind = GAPSetAdvertisingData(
            self.serial_port,
            AdvertisingDataIncluded=True,
            AdvertisingData=GAPSetAdvertisingDataRequest.AdvertisingData(
                NbOfAdStructures=3, AdStructures=AdStructures),
            ScanResponseDataIncluded=False,
            ScanResponseData=None,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gap_set_adv_data(0)
        if ind is None:
            return None

        print('\tReceived GAP Generic Event Advertising Data Setup Complete Indication - OK!')

    def gap_set_adv_parameters(self, retries=1):
        '''
        Set the advertising parameters. Assert on wrong type of indication.
        '''
        ind = GAPSetAdvertisingParameters(
            self.serial_port,
            AdvertisingParameters_MinInterval=gFastConnMinAdvInterval_c,
            AdvertisingParameters_MaxInterval=gFastConnMaxAdvInterval_c,
            AdvertisingParameters_AdvertisingType=gAdvConnectableUndirected_c,
            AdvertisingParameters_OwnAddressType=gBleAddrTypePublic_c,
            AdvertisingParameters_PeerAddressType=gBleAddrTypePublic_c,
            AdvertisingParameters_PeerAddress=[0, 0, 0, 0, 0, 0],
            AdvertisingParameters_ChannelMap=gGapAdvertisingChannelMapDefault_c,
            AdvertisingParameters_FilterPolicy=gProcessAll_c,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gap_set_adv_parameters(0)
        if ind is None:
            return None

        print('\tReceived GAP Generic Event Advertising Parameters Setup Complete Indication - OK!')

    def gap_start_adv(self, retries=1):
        '''
        Start advertising. Assert on wrong type of indication.
        '''
        ind = GAPStartAdvertising(self.serial_port, protocol=self.protocol)
        if ind is None and retries != 0:
            return self.gap_start_adv(0)
        if ind is None:
            return None

        print('\tReceived GAP Advertising Event State Changed Indication - OK!')

    def gatt_server_register_for_write_notifications(self, service_uuid):
        '''
        Register for write notifications on a service.
        Add 100ms sleep as the GATT bindings used do not return indications.

        @param service_uuid: UUID of the service
        '''
        GATTServerRegisterHandlesForWriteNotifications(
            self.serial_port,
            HandleCount=1,
            AttributeHandles=[self.handles[service_uuid]],
            protocol=self.protocol
        )
        sleep(.1)
        GATTServerRegisterCallback(self.serial_port, protocol=self.protocol)
        sleep(.1)

    def gattdb_find_char_value_handle_in_service(self, service_uuid, char_uuid, retries=1):
        '''
        Find the handle of a characteristic value of a given characteristic in a given service.

        @param service_uuid: UUID of the service
        @param char_uuid: UUID of the characteristic
        @return: handle of the characteristic value
        '''
        ind = GATTDBFindCharValueHandleInService(
            self.serial_port,
            ServiceHandle=self.handles[service_uuid],
            UuidType=UuidType.Uuid16Bits,
            Uuid=char_uuid,
            protocol=self.protocol
        )
        if ind is None and retries != 0:
            return self.gattdb_find_char_value_handle_in_service(service_uuid, char_uuid, 0)
        if ind is None:
            return None

        print('\tCharacteristic Value Handle for UUID 0x%04X ->' % char_uuid, ind.CharValueHandle)
        return ind.CharValueHandle

    def gattdb_find_cccd_handle_for_char_value_handle(self, char_value_handle, retries=1):
        '''
        Find the handle of the CCCD of a given characteristic value handle.

        @param char_value_handle: UUID of the characteristic value
        @return: handle of the CCCD
        '''
        ind = GATTDBFindCccdHandleForCharValueHandle(
            self.serial_port, CharValueHandle=char_value_handle, protocol=self.protocol)
        if ind is None and retries != 0:
            return self.gattdb_find_cccd_handle_for_char_value_handle(char_value_handle, 0)
        if ind is None:
            return None

        print('\tCCCD Handle for Characteristic Value Handle %d ->' % char_value_handle, ind.CccdHandle)
        return ind.CccdHandle

    def gattdb_write_attr(self, handle, val_len, val):
        '''
        Write the value of an attribute.

        @param handle: the handle of a characteristic value
        @param val_len: the length in bytes of the value
        @param val: the actual value
        '''
        GATTDBWriteAttribute(
            self.serial_port,
            Handle=handle,
            ValueLength=val_len,
            Value=val,
            protocol=self.protocol
        )
        sleep(.1)

    def gattdb_read_attr(self, handle, max_bytes):
        '''
        Read the value of an attribute.

        @param handle: the handle of a characteristic value
        @param max_bytes: read at most this number of bytes
        @return: value read
        '''
        ind = GATTDBReadAttribute(
            self.serial_port,
            Handle=handle,
            MaxBytes=max_bytes,
            protocol=self.protocol
        )
        if ind is None:
            return None
        return ind.Value

    def gap_check_notification_status(self, handle):
        '''
        Check the notification status on a given handle.
        '''
        GAPCheckNotificationStatus(
            self.serial_port, DeviceId=self.client_device_id, Handle=handle, protocol=self.protocol, timeout=0.05)

    def gatt_server_send_notification(self, handle):
        '''
        Send notification on a given handle.
        '''
        GATTServerSendNotification(self.serial_port, DeviceId=self.client_device_id, Handle=handle, protocol=self.protocol)


class BLEHeartRateDevice(BLEDevice):
    '''
    Services implemented: Heart Rate.
    '''

    def gattdb_add_service_heart_rate(self):
        '''
        Sequence of commands to add the Heart Rate service.
        '''
        self.mHrsServiceHandle = self.gattdb_dynamic_add_psd(
            service_uuid=gBleSig_HeartRateService_d)
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_HrMeasurement_d,
            char_prop=CharProp.gNotify_c,
            maxval_len=0x16,
            initval=mGattDbDynamic_HRServiceHrMeasurementInitValue,
            val_perm=CharPerm.gPermissionNone_c
        )
        self.handles['HR_CCCD'] = self.gattdb_dynamic_add_cccd()
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_BodySensorLocation_d,
            char_prop=CharProp.gRead_c,
            maxval_len=0,
            initval=mGattDbDynamic_HRServiceBodySensorLocationInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_HrControlPoint_d,
            char_prop=CharProp.gWrite_c,
            maxval_len=0,
            initval=mGattDbDynamic_HRServiceHrControlPointInitValue,
            val_perm=CharPerm.gPermissionFlagWritable_c
        )

    def hr_measurement_cb(self):
        '''
        Update the heart rate measurement value each mHeartRateReportInterval_c seconds.
        '''
        while self.gap_event_connected.is_set():
            try:
                sleep(mHeartRateReportInterval_c)
                hValueHrMeasurement = self.gattdb_find_char_value_handle_in_service(
                    service_uuid=gBleSig_HeartRateService_d,
                    char_uuid=gBleSig_HrMeasurement_d
                )

                self.gattdb_read_attr(handle=hValueHrMeasurement, max_bytes=1)
                self.gattdb_write_attr(
                    handle=hValueHrMeasurement,
                    val_len=2,  # Flags + Heart Rate Measurement Value (uint8)
                    val=[gHrs_8BitHeartRateFormat_c, randint(60, 100)]
                )

                hCccdHrMeasurement = self.gattdb_find_cccd_handle_for_char_value_handle(
                    hValueHrMeasurement)

                self.gap_check_notification_status(handle=hCccdHrMeasurement)
                self.gatt_server_send_notification(hValueHrMeasurement)
            except AttributeError:
                pass


class BLEBatteryDevice(BLEDevice):
    '''
    Services implemented: Battery.
    '''

    def gattdb_add_service_battery(self):
        '''
        Sequence of commands to add the Battery service.
        '''
        self.mBsServiceHandle = self.gattdb_dynamic_add_psd(service_uuid=gBleSig_BatteryService_d)
        self.gattdb_dynamic_add_cdv(
            char_uuid=gBleSig_BatteryLevel_d,
            char_prop=CharProp.gRead_c | CharProp.gNotify_c,
            maxval_len=0,
            initval=mGattDbDynamic_BServiceLevelInitValue,
            val_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.gattdb_dynamic_add_cd(
            uuid=gBleSig_CharPresFormatDescriptor_d,
            val=mGattDbDynamic_BServiceCharPresFormatDescriptorInitValue,
            desc_perm=CharPerm.gPermissionFlagReadable_c
        )
        self.handles['BATTERY_CCCD'] = self.gattdb_dynamic_add_cccd()

    def battery_measurement_cb(self):
        '''
        Update the battery measurement value each mBatteryLevelReportInterval_c seconds.
        '''
        while self.gap_event_connected.is_set():
            try:
                sleep(mBatteryLevelReportInterval_c)
                hValueBatteryLevel = self.gattdb_find_char_value_handle_in_service(
                    service_uuid=gBleSig_BatteryService_d,
                    char_uuid=gBleSig_BatteryLevel_d
                )
                # write a random battery level at each iteration
                self.gattdb_write_attr(hValueBatteryLevel, val_len=1, val=randint(1, 100))
            except AttributeError:
                pass


class BLEHeartRateBatteryDevice(BLEHeartRateDevice, BLEBatteryDevice):
    '''
    Placeholder for a device which implements both Heart Rate and Battery services.
    '''

    pass


def main(args):
    dev = BLEHeartRateBatteryDevice(args)

    # GATT Service
    dev.gattdb_add_service_gatt()
    # GAP Service
    dev.gattdb_add_service_gap()
    # Heart Rate Service
    dev.gattdb_add_service_heart_rate()
    # Battery Service
    dev.gattdb_add_service_battery()
    # Device Info Service
    dev.gattdb_add_service_device_info()

    dev.gap_read_public_dev_addr()

    if args.pair:
        dev.gap_register_device_security_requirements()
        dev.gap_set_local_passkey()

    dev.gap_set_adv_parameters()
    dev.gap_set_adv_data()
    dev.gatt_server_register_for_write_notifications(gBleSig_BatteryService_d)

    # get characteristic value handles
    hValueHrMeasurement = dev.gattdb_find_char_value_handle_in_service(
        service_uuid=gBleSig_HeartRateService_d,
        char_uuid=gBleSig_HrMeasurement_d
    )
    hValueBodyLocation = dev.gattdb_find_char_value_handle_in_service(
        service_uuid=gBleSig_HeartRateService_d,
        char_uuid=gBleSig_BodySensorLocation_d
    )
    # write attributes on these value handles
    dev.gattdb_write_attr(hValueHrMeasurement, 1,
                          (gHrs_EnergyExpendedEnabled_c | gHrs_SensorContactSupported_c | gHrs_SensorContactDetected_c))
    dev.gattdb_write_attr(hValueBodyLocation, 1, gHrs_BodySensorLocChest_c)

    hValueBatteryLevel = dev.gattdb_find_char_value_handle_in_service(
        gBleSig_BatteryService_d, gBleSig_BatteryLevel_d)
    dev.gattdb_write_attr(hValueBatteryLevel, 1, 100)  # 100% battery level

    print(79 * '=' + '\nPlease open NXP IoT Toolbox and select Heart Rate, and then NXP_HRS device.\n' + 79 * '=')
    while True:
        try:
            dev.gap_set_adv_parameters()
            dev.gap_start_adv()
            while not dev.gap_event_connected.is_set():
                sleep(.1)
                #print(123)

            hrs_thread = Thread(target=dev.hr_measurement_cb)
            battery_thread = Thread(target=dev.battery_measurement_cb)
            hrs_thread.daemon, battery_thread.daemon = True, True

            hrs_thread.start()
            battery_thread.start()

            hrs_thread.join()
            battery_thread.join()

            print(79 * '=' + '\nDisconnected - please click Connect or <- and Scan again.\n' + 79 * '=')
        except KeyboardInterrupt:
            print('Exiting at user\'s request..')
            sys.exit()

if __name__ == '__main__':

    args = usage()
    args.protocol = Protocol.BLE
    args.reset = True
    main(args)
