'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

from com.nxp.wireless_connectivity.commands.fsci_frame_description import FsciAckPolicy,\
    Protocol
from com.nxp.wireless_connectivity.commands.fsci_operation import FsciOperation
from com.nxp.wireless_connectivity.hsdk.CUartLibrary import Baudrate
from com.nxp.wireless_connectivity.hsdk.framing.fsci_framer import FsciFramer

from com.nxp.wireless_connectivity.commands.ble.events import *  # @UnusedWildImport



class L2CAPCBRegisterLeCbCallbacksOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBRegisterLeCbCallbacksRequestFrame
        self.observers = []
        super(L2CAPCBRegisterLeCbCallbacksOperation, self).subscribeToEvents()


class L2CAPCBRegisterLePsmOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBRegisterLePsmRequestFrame
        self.observers = []
        super(L2CAPCBRegisterLePsmOperation, self).subscribeToEvents()


class L2CAPCBDeregisterLePsmOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBDeregisterLePsmRequestFrame
        self.observers = []
        super(L2CAPCBDeregisterLePsmOperation, self).subscribeToEvents()


class L2CAPCBConnectLePsmOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBConnectLePsmRequestFrame
        self.observers = []
        super(L2CAPCBConnectLePsmOperation, self).subscribeToEvents()


class L2CAPCBDisconnectLeCbChannelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBDisconnectLeCbChannelRequestFrame
        self.observers = []
        super(L2CAPCBDisconnectLeCbChannelOperation, self).subscribeToEvents()


class L2CAPCBCancelConnectionOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBCancelConnectionRequestFrame
        self.observers = []
        super(L2CAPCBCancelConnectionOperation, self).subscribeToEvents()


class L2CAPCBSendLeCbDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBSendLeCbDataRequestFrame
        self.observers = []
        super(L2CAPCBSendLeCbDataOperation, self).subscribeToEvents()


class L2CAPCBSendLeCreditOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBSendLeCreditRequestFrame
        self.observers = []
        super(L2CAPCBSendLeCreditOperation, self).subscribeToEvents()


class GATTInitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTInitRequestFrame
        self.observers = []
        super(GATTInitOperation, self).subscribeToEvents()


class GATTGetMtuOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTGetMtuRequestFrame
        self.observers = [GATTGetMtuIndicationObserver('GATTGetMtuIndication'), ]
        super(GATTGetMtuOperation, self).subscribeToEvents()


class GATTClientInitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientInitRequestFrame
        self.observers = []
        super(GATTClientInitOperation, self).subscribeToEvents()


class GATTClientResetProcedureOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientResetProcedureRequestFrame
        self.observers = []
        super(GATTClientResetProcedureOperation, self).subscribeToEvents()


class GATTClientRegisterProcedureCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterProcedureCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterProcedureCallbackOperation, self).subscribeToEvents()


class GATTClientRegisterNotificationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterNotificationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterNotificationCallbackOperation, self).subscribeToEvents()


class GATTClientRegisterIndicationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterIndicationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterIndicationCallbackOperation, self).subscribeToEvents()


class GATTClientExchangeMtuOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientExchangeMtuRequestFrame
        self.observers = []
        super(GATTClientExchangeMtuOperation, self).subscribeToEvents()


class GATTClientDiscoverAllPrimaryServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientDiscoverAllPrimaryServicesRequestFrame
        self.observers = []
        super(GATTClientDiscoverAllPrimaryServicesOperation, self).subscribeToEvents()


class GATTClientDiscoverPrimaryServicesByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientDiscoverPrimaryServicesByUuidRequestFrame
        self.observers = []
        super(GATTClientDiscoverPrimaryServicesByUuidOperation, self).subscribeToEvents()


class GATTClientFindIncludedServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientFindIncludedServicesRequestFrame
        self.observers = []
        super(GATTClientFindIncludedServicesOperation, self).subscribeToEvents()


class GATTClientDiscoverAllCharacteristicsOfServiceOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientDiscoverAllCharacteristicsOfServiceRequestFrame
        self.observers = []
        super(GATTClientDiscoverAllCharacteristicsOfServiceOperation, self).subscribeToEvents()


class GATTClientDiscoverCharacteristicOfServiceByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientDiscoverCharacteristicOfServiceByUuidRequestFrame
        self.observers = []
        super(GATTClientDiscoverCharacteristicOfServiceByUuidOperation, self).subscribeToEvents()


class GATTClientDiscoverAllCharacteristicDescriptorsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientDiscoverAllCharacteristicDescriptorsRequestFrame
        self.observers = []
        super(GATTClientDiscoverAllCharacteristicDescriptorsOperation, self).subscribeToEvents()


class GATTClientReadCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientReadCharacteristicValueRequestFrame
        self.observers = []
        super(GATTClientReadCharacteristicValueOperation, self).subscribeToEvents()


class GATTClientReadUsingCharacteristicUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientReadUsingCharacteristicUuidRequestFrame
        self.observers = []
        super(GATTClientReadUsingCharacteristicUuidOperation, self).subscribeToEvents()


class GATTClientReadMultipleCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientReadMultipleCharacteristicValuesRequestFrame
        self.observers = []
        super(GATTClientReadMultipleCharacteristicValuesOperation, self).subscribeToEvents()


class GATTClientWriteCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientWriteCharacteristicValueRequestFrame
        self.observers = []
        super(GATTClientWriteCharacteristicValueOperation, self).subscribeToEvents()


class GATTClientReadCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientReadCharacteristicDescriptorRequestFrame
        self.observers = []
        super(GATTClientReadCharacteristicDescriptorOperation, self).subscribeToEvents()


class GATTClientWriteCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientWriteCharacteristicDescriptorRequestFrame
        self.observers = []
        super(GATTClientWriteCharacteristicDescriptorOperation, self).subscribeToEvents()


class GATTServerInitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerInitRequestFrame
        self.observers = []
        super(GATTServerInitOperation, self).subscribeToEvents()


class GATTServerRegisterCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerRegisterCallbackRequestFrame
        self.observers = []
        super(GATTServerRegisterCallbackOperation, self).subscribeToEvents()


class GATTServerRegisterHandlesForWriteNotificationsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerRegisterHandlesForWriteNotificationsRequestFrame
        self.observers = []
        super(GATTServerRegisterHandlesForWriteNotificationsOperation, self).subscribeToEvents()


class GATTServerSendAttributeWrittenStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendAttributeWrittenStatusRequestFrame
        self.observers = []
        super(GATTServerSendAttributeWrittenStatusOperation, self).subscribeToEvents()


class GATTServerSendNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendNotificationRequestFrame
        self.observers = []
        super(GATTServerSendNotificationOperation, self).subscribeToEvents()


class GATTServerSendIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendIndicationRequestFrame
        self.observers = []
        super(GATTServerSendIndicationOperation, self).subscribeToEvents()


class GATTServerSendInstantValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendInstantValueNotificationRequestFrame
        self.observers = []
        super(GATTServerSendInstantValueNotificationOperation, self).subscribeToEvents()


class GATTServerSendInstantValueIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendInstantValueIndicationRequestFrame
        self.observers = []
        super(GATTServerSendInstantValueIndicationOperation, self).subscribeToEvents()


class GATTServerRegisterHandlesForReadNotificationsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerRegisterHandlesForReadNotificationsRequestFrame
        self.observers = []
        super(GATTServerRegisterHandlesForReadNotificationsOperation, self).subscribeToEvents()


class GATTServerSendAttributeReadStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendAttributeReadStatusRequestFrame
        self.observers = []
        super(GATTServerSendAttributeReadStatusOperation, self).subscribeToEvents()

class GATTServerRegisterUniqueHandlesForNotificationsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerRegisterUniqueHandlesForNotificationsRequestFrame
        self.observers = []
        super(GATTServerRegisterUniqueHandlesForNotificationsOperation, self).subscribeToEvents()

class GATTServerUnregisterHandlesForWriteNotificationsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerUnregisterHandlesForWriteNotificationsRequestFrame
        self.observers = []
        super(GATTServerUnregisterHandlesForWriteNotificationsOperation, self).subscribeToEvents()

class GATTServerUnregisterHandlesForReadNotificationsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerUnregisterHandlesForReadNotificationsRequestFrame
        self.observers = []
        super(GATTServerUnregisterHandlesForReadNotificationsOperation, self).subscribeToEvents()

class GATTDBWriteAttributeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBWriteAttributeRequestFrame
        self.observers = []
        super(GATTDBWriteAttributeOperation, self).subscribeToEvents()


class GATTDBReadAttributeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBReadAttributeRequestFrame
        self.observers = [GATTDBReadAttributeIndicationObserver('GATTDBReadAttributeIndication'), ]
        super(GATTDBReadAttributeOperation, self).subscribeToEvents()


class GATTDBFindServiceHandleOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBFindServiceHandleRequestFrame
        self.observers = [GATTDBFindServiceHandleIndicationObserver('GATTDBFindServiceHandleIndication'), ]
        super(GATTDBFindServiceHandleOperation, self).subscribeToEvents()


class GATTDBFindCharValueHandleInServiceOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBFindCharValueHandleInServiceRequestFrame
        self.observers = [GATTDBFindCharValueHandleInServiceIndicationObserver('GATTDBFindCharValueHandleInServiceIndication'), ]
        super(GATTDBFindCharValueHandleInServiceOperation, self).subscribeToEvents()


class GATTDBFindCccdHandleForCharValueHandleOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBFindCccdHandleForCharValueHandleRequestFrame
        self.observers = [GATTDBFindCccdHandleForCharValueHandleIndicationObserver('GATTDBFindCccdHandleForCharValueHandleIndication'), ]
        super(GATTDBFindCccdHandleForCharValueHandleOperation, self).subscribeToEvents()


class GATTDBFindDescriptorHandleForCharValueHandleOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBFindDescriptorHandleForCharValueHandleRequestFrame
        self.observers = [GATTDBFindDescriptorHandleForCharValueHandleIndicationObserver('GATTDBFindDescriptorHandleForCharValueHandleIndication'), ]
        super(GATTDBFindDescriptorHandleForCharValueHandleOperation, self).subscribeToEvents()

class GATTDBDynamicInitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicInitRequestFrame
        self.observers = []
        super(GATTDBDynamicInitOperation, self).subscribeToEvents()

class GATTDBDynamicReleaseDatabaseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicReleaseDatabaseRequestFrame
        self.observers = []
        super(GATTDBDynamicReleaseDatabaseOperation, self).subscribeToEvents()


class GATTDBDynamicAddPrimaryServiceDeclarationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddPrimaryServiceDeclarationRequestFrame
        self.observers = [GATTDBDynamicAddPrimaryServiceDeclarationIndicationObserver('GATTDBDynamicAddPrimaryServiceDeclarationIndication'), ]
        super(GATTDBDynamicAddPrimaryServiceDeclarationOperation, self).subscribeToEvents()


class GATTDBDynamicAddSecondaryServiceDeclarationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddSecondaryServiceDeclarationRequestFrame
        self.observers = [GATTDBDynamicAddSecondaryServiceDeclarationIndicationObserver('GATTDBDynamicAddSecondaryServiceDeclarationIndication'), ]
        super(GATTDBDynamicAddSecondaryServiceDeclarationOperation, self).subscribeToEvents()


class GATTDBDynamicAddIncludeDeclarationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddIncludeDeclarationRequestFrame
        self.observers = [GATTDBDynamicAddIncludeDeclarationIndicationObserver('GATTDBDynamicAddIncludeDeclarationIndication'), ]
        super(GATTDBDynamicAddIncludeDeclarationOperation, self).subscribeToEvents()


class GATTDBDynamicAddCharacteristicDeclarationAndValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddCharacteristicDeclarationAndValueRequestFrame
        self.observers = [GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationObserver('GATTDBDynamicAddCharacteristicDeclarationAndValueIndication'), ]
        super(GATTDBDynamicAddCharacteristicDeclarationAndValueOperation, self).subscribeToEvents()


class GATTDBDynamicAddCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddCharacteristicDescriptorRequestFrame
        self.observers = [GATTDBDynamicAddCharacteristicDescriptorIndicationObserver('GATTDBDynamicAddCharacteristicDescriptorIndication'), ]
        super(GATTDBDynamicAddCharacteristicDescriptorOperation, self).subscribeToEvents()


class GATTDBDynamicAddCccdOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddCccdRequestFrame
        self.observers = [GATTDBDynamicAddCccdIndicationObserver('GATTDBDynamicAddCccdIndication'), ]
        super(GATTDBDynamicAddCccdOperation, self).subscribeToEvents()


class GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestFrame
        self.observers = [GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationObserver('GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication'), ]
        super(GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueOperation, self).subscribeToEvents()


class GATTDBDynamicRemoveServiceOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicRemoveServiceRequestFrame
        self.observers = []
        super(GATTDBDynamicRemoveServiceOperation, self).subscribeToEvents()


class GATTDBDynamicRemoveCharacteristicOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicRemoveCharacteristicRequestFrame
        self.observers = []
        super(GATTDBDynamicRemoveCharacteristicOperation, self).subscribeToEvents()

class GATTDBDynamicAddCharDescriptorWithUniqueValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicAddCharDescriptorWithUniqueValueRequestFrame
        self.observers = [GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationObserver('GATTDBDynamicAddCharDescriptorWithUniqueValueIndication'), ]
        super(GATTDBDynamicAddCharDescriptorWithUniqueValueOperation, self).subscribeToEvents()
class BLEHostInitializeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.BLEHostInitializeRequestFrame
        self.observers = []
        super(BLEHostInitializeOperation, self).subscribeToEvents()


class GAPRegisterDeviceSecurityRequirementsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRegisterDeviceSecurityRequirementsRequestFrame
        self.observers = []
        super(GAPRegisterDeviceSecurityRequirementsOperation, self).subscribeToEvents()


class GAPSetAdvertisingParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetAdvertisingParametersRequestFrame
        self.observers = [GAPGenericEventAdvertisingParametersSetupCompleteIndicationObserver('GAPGenericEventAdvertisingParametersSetupCompleteIndication'), ]
        super(GAPSetAdvertisingParametersOperation, self).subscribeToEvents()


class GAPSetAdvertisingDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetAdvertisingDataRequestFrame
        self.observers = [GAPGenericEventAdvertisingDataSetupCompleteIndicationObserver('GAPGenericEventAdvertisingDataSetupCompleteIndication')]
        super(GAPSetAdvertisingDataOperation, self).subscribeToEvents()


class GAPStartAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStartAdvertisingRequestFrame
        self.observers = [GAPAdvertisingEventStateChangedIndicationObserver('GAPAdvertisingEventStateChangedIndication'), ]
        super(GAPStartAdvertisingOperation, self).subscribeToEvents()


class GAPStopAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStopAdvertisingRequestFrame
        self.observers = []
        super(GAPStopAdvertisingOperation, self).subscribeToEvents()


class GAPAuthorizeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPAuthorizeRequestFrame
        self.observers = []
        super(GAPAuthorizeOperation, self).subscribeToEvents()


class GAPSaveCccdOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSaveCccdRequestFrame
        self.observers = []
        super(GAPSaveCccdOperation, self).subscribeToEvents()


class GAPCheckNotificationStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPCheckNotificationStatusRequestFrame
        self.observers = [GAPCheckNotificationStatusIndicationObserver('GAPCheckNotificationStatusIndication'), ]
        super(GAPCheckNotificationStatusOperation, self).subscribeToEvents()


class GAPCheckIndicationStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPCheckIndicationStatusRequestFrame
        self.observers = []
        super(GAPCheckIndicationStatusOperation, self).subscribeToEvents()


class GAPPairOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPairRequestFrame
        self.observers = []
        super(GAPPairOperation, self).subscribeToEvents()


class GAPSendSlaveSecurityRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSendSlaveSecurityRequestRequestFrame
        self.observers = []
        super(GAPSendSlaveSecurityRequestOperation, self).subscribeToEvents()


class GAPEncryptLinkOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEncryptLinkRequestFrame
        self.observers = []
        super(GAPEncryptLinkOperation, self).subscribeToEvents()


class GAPAcceptPairingRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPAcceptPairingRequestRequestFrame
        self.observers = []
        super(GAPAcceptPairingRequestOperation, self).subscribeToEvents()


class GAPRejectPairingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRejectPairingRequestFrame
        self.observers = []
        super(GAPRejectPairingOperation, self).subscribeToEvents()


class GAPEnterPasskeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnterPasskeyRequestFrame
        self.observers = []
        super(GAPEnterPasskeyOperation, self).subscribeToEvents()


class GAPProvideOobOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPProvideOobRequestFrame
        self.observers = []
        super(GAPProvideOobOperation, self).subscribeToEvents()


class GAPRejectPasskeyRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRejectPasskeyRequestRequestFrame
        self.observers = []
        super(GAPRejectPasskeyRequestOperation, self).subscribeToEvents()


class GAPSendSmpKeysOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSendSmpKeysRequestFrame
        self.observers = []
        super(GAPSendSmpKeysOperation, self).subscribeToEvents()


class GAPRejectKeyExchangeRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRejectKeyExchangeRequestRequestFrame
        self.observers = []
        super(GAPRejectKeyExchangeRequestOperation, self).subscribeToEvents()


class GAPProvideLongTermKeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPProvideLongTermKeyRequestFrame
        self.observers = []
        super(GAPProvideLongTermKeyOperation, self).subscribeToEvents()


class GAPDenyLongTermKeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPDenyLongTermKeyRequestFrame
        self.observers = []
        super(GAPDenyLongTermKeyOperation, self).subscribeToEvents()


class GAPLoadEncryptionInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLoadEncryptionInformationRequestFrame
        self.observers = [GAPLoadEncryptionInformationIndicationObserver('GAPLoadEncryptionInformationIndication'), ]
        super(GAPLoadEncryptionInformationOperation, self).subscribeToEvents()


class GAPSetLocalPasskeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetLocalPasskeyRequestFrame
        self.observers = []
        super(GAPSetLocalPasskeyOperation, self).subscribeToEvents()


class GAPStartScanningOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStartScanningRequestFrame
        self.observers = [GAPScanningEventStateChangedIndicationObserver('GAPScanningEventStateChangedIndication'), ]
        super(GAPStartScanningOperation, self).subscribeToEvents()


class GAPStopScanningOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStopScanningRequestFrame
        self.observers = [GAPScanningEventStateChangedIndicationObserver('GAPScanningEventStateChangedIndication'), ]
        super(GAPStopScanningOperation, self).subscribeToEvents()


class GAPConnectOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPConnectRequestFrame
        self.observers = []
        super(GAPConnectOperation, self).subscribeToEvents()


class GAPDisconnectOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPDisconnectRequestFrame
        self.observers = []
        super(GAPDisconnectOperation, self).subscribeToEvents()


class GAPSaveCustomPeerInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSaveCustomPeerInformationRequestFrame
        self.observers = []
        super(GAPSaveCustomPeerInformationOperation, self).subscribeToEvents()


class GAPLoadCustomPeerInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLoadCustomPeerInformationRequestFrame
        self.observers = [GAPLoadCustomPeerInformationIndicationObserver('GAPLoadCustomPeerInformationIndication'), ]
        super(GAPLoadCustomPeerInformationOperation, self).subscribeToEvents()


class GAPCheckIfBondedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPCheckIfBondedRequestFrame
        self.observers = [GAPCheckIfBondedIndicationObserver('GAPCheckIfBondedIndication'), ]
        super(GAPCheckIfBondedOperation, self).subscribeToEvents()


class GAPReadWhiteListSizeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadWhiteListSizeRequestFrame
        self.observers = []
        super(GAPReadWhiteListSizeOperation, self).subscribeToEvents()


class GAPClearWhiteListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPClearWhiteListRequestFrame
        self.observers = []
        super(GAPClearWhiteListOperation, self).subscribeToEvents()


class GAPAddDeviceToWhiteListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPAddDeviceToWhiteListRequestFrame
        self.observers = []
        super(GAPAddDeviceToWhiteListOperation, self).subscribeToEvents()


class GAPRemoveDeviceFromWhiteListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRemoveDeviceFromWhiteListRequestFrame
        self.observers = []
        super(GAPRemoveDeviceFromWhiteListOperation, self).subscribeToEvents()


class GAPReadPublicDeviceAddressOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadPublicDeviceAddressRequestFrame
        self.observers = [GAPGenericEventPublicAddressReadIndicationObserver('GAPGenericEventPublicAddressReadIndication'), ]
        super(GAPReadPublicDeviceAddressOperation, self).subscribeToEvents()


class GAPCreateRandomDeviceAddressOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPCreateRandomDeviceAddressRequestFrame
        self.observers = []
        super(GAPCreateRandomDeviceAddressOperation, self).subscribeToEvents()


class GAPSaveDeviceNameOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSaveDeviceNameRequestFrame
        self.observers = []
        super(GAPSaveDeviceNameOperation, self).subscribeToEvents()


class GAPGetBondedDevicesCountOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPGetBondedDevicesCountRequestFrame
        self.observers = [GAPGetBondedDevicesCountIndicationObserver('GAPGetBondedDevicesCountIndication'), ]
        super(GAPGetBondedDevicesCountOperation, self).subscribeToEvents()


class GAPGetBondedDeviceNameOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPGetBondedDeviceNameRequestFrame
        self.observers = [GAPGetBondedDeviceNameIndicationObserver('GAPGetBondedDeviceNameIndication'), ]
        super(GAPGetBondedDeviceNameOperation, self).subscribeToEvents()


class GAPRemoveBondOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRemoveBondRequestFrame
        self.observers = []
        super(GAPRemoveBondOperation, self).subscribeToEvents()


class GAPRemoveAllBondsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRemoveAllBondsRequestFrame
        self.observers = []
        super(GAPRemoveAllBondsOperation, self).subscribeToEvents()


class GAPReadRadioPowerLevelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadRadioPowerLevelRequestFrame
        self.observers = []
        super(GAPReadRadioPowerLevelOperation, self).subscribeToEvents()


class GAPVerifyPrivateResolvableAddressOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPVerifyPrivateResolvableAddressRequestFrame
        self.observers = []
        super(GAPVerifyPrivateResolvableAddressOperation, self).subscribeToEvents()


class GAPSetRandomAddressOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetRandomAddressRequestFrame
        self.observers = [GAPGenericEventRandomAddressSetIndicationObserver('GAPGenericEventRandomAddressSetIndication'), ]
        super(GAPSetRandomAddressOperation, self).subscribeToEvents()


class GAPSetScanModeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetScanModeRequestFrame
        self.observers = []
        super(GAPSetScanModeOperation, self).subscribeToEvents()


class GAPSetDefaultPairingParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetDefaultPairingParametersRequestFrame
        self.observers = []
        super(GAPSetDefaultPairingParametersOperation, self).subscribeToEvents()


class GAPUpdateConnectionParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPUpdateConnectionParametersRequestFrame
        self.observers = []
        super(GAPUpdateConnectionParametersOperation, self).subscribeToEvents()


class GAPEnableUpdateConnectionParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableUpdateConnectionParametersRequestFrame
        self.observers = []
        super(GAPEnableUpdateConnectionParametersOperation, self).subscribeToEvents()


class GapUpdateLeDataLengthOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GapUpdateLeDataLengthRequestFrame
        self.observers = []
        super(GapUpdateLeDataLengthOperation, self).subscribeToEvents()

class GAPEnableHostPrivacyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableHostPrivacyRequestFrame
        self.observers = []
        super(GAPEnableHostPrivacyOperation, self).subscribeToEvents()


class GAPEnableControllerPrivacyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableControllerPrivacyRequestFrame
        self.observers = []
        super(GAPEnableControllerPrivacyOperation, self).subscribeToEvents()


class GAPLeScRegeneratePublicKeyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeScRegeneratePublicKeyRequestFrame
        self.observers = []
        super(GAPLeScRegeneratePublicKeyOperation, self).subscribeToEvents()


class GAPLeScValidateNumericValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeScValidateNumericValueRequestFrame
        self.observers = []
        super(GAPLeScValidateNumericValueOperation, self).subscribeToEvents()


class GAPLeScGetLocalOobDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeScGetLocalOobDataRequestFrame
        self.observers = []
        super(GAPLeScGetLocalOobDataOperation, self).subscribeToEvents()


class GAPLeScSetPeerOobDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeScSetPeerOobDataRequestFrame
        self.observers = []
        super(GAPLeScSetPeerOobDataOperation, self).subscribeToEvents()


class GAPLeScSendKeypressNotificationPrivacyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeScSendKeypressNotificationPrivacyRequestFrame
        self.observers = []
        super(GAPLeScSendKeypressNotificationPrivacyOperation, self).subscribeToEvents()


class GAPGetBondedDevicesIdentityInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPGetBondedDevicesIdentityInformationRequestFrame
        self.observers = [GAPGetBondedDevicesIdentityInformationIndicationObserver('GAPGetBondedDevicesIdentityInformationIndication'), ]
        super(GAPGetBondedDevicesIdentityInformationOperation, self).subscribeToEvents()


class GAPSetTxPowerLevelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetTxPowerLevelRequestFrame
        self.observers = []
        super(GAPSetTxPowerLevelOperation, self).subscribeToEvents()


class GAPLeReadPhyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeReadPhyRequestFrame
        self.observers = []
        super(GAPLeReadPhyOperation, self).subscribeToEvents()


class GAPLeSetPhyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLeSetPhyRequestFrame
        self.observers = []
        super(GAPLeSetPhyOperation, self).subscribeToEvents()


class GAPControllerEnhancedNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPControllerEnhancedNotificationRequestFrame
        self.observers = []
        super(GAPControllerEnhancedNotificationOperation, self).subscribeToEvents()


class GAPLoadKeysOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPLoadKeysRequestFrame
        self.observers = [GAPLoadKeysIndicationObserver('GAPLoadKeysIndication'), ]
        super(GAPLoadKeysOperation, self).subscribeToEvents()

class GAPSaveKeysOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSaveKeysRequestFrame
        self.observers = []
        super(GAPSaveKeysOperation, self).subscribeToEvents()


class GAPSetChannelMapOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetChannelMapRequestFrame
        self.observers = []
        super(GAPSetChannelMapOperation, self).subscribeToEvents()


class GAPReadChannelMapOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadChannelMapRequestFrame
        self.observers = []
        super(GAPReadChannelMapOperation, self).subscribeToEvents()

class GAPSetPrivacyModeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetPrivacyModeRequestFrame
        self.observers = []
        super(GAPSetPrivacyModeOperation, self).subscribeToEvents()

class FSCICPUResetOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCICPUResetRequestFrame
        self.observers = []
        super(FSCICPUResetOperation, self).subscribeToEvents()

class FSCIGetNumberOfFreeBuffersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIGetNumberOfFreeBuffersRequestFrame
        self.observers = [FSCIGetNumberOfFreeBuffersResponseObserver('FSCIGetNumberOfFreeBuffersResponse'), ]
        super(FSCIGetNumberOfFreeBuffersOperation, self).subscribeToEvents()

class FSCIAllowDeviceToSleepOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIAllowDeviceToSleepRequestFrame
        self.observers = [FSCIAllowDeviceToSleepConfirmObserver('FSCIAllowDeviceToSleepConfirm'), ]
        super(FSCIAllowDeviceToSleepOperation, self).subscribeToEvents()


class FSCIGetWakeupReasonOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIGetWakeupReasonRequestFrame
        self.observers = [FSCIGetWakeupReasonResponseObserver('FSCIGetWakeupReasonResponse'), ]
        super(FSCIGetWakeupReasonOperation, self).subscribeToEvents()


class FSCIAckOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [FSCIAckIndicationObserver('FSCIAckIndication'), ]
        super(FSCIAckOperation, self).subscribeToEvents()


class FSCIErrorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [FSCIErrorIndicationObserver('FSCIErrorIndication'), ]
        super(FSCIErrorOperation, self).subscribeToEvents()


class FSCIWakeUpOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [FSCIWakeUpIndicationObserver('FSCIWakeUpIndication'), ]
        super(FSCIWakeUpOperation, self).subscribeToEvents()


class L2CAPCBOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBConfirmObserver('L2CAPCBConfirm'), ]
        super(L2CAPCBOperation, self).subscribeToEvents()


class L2CAPCBLePsmConnectionRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLePsmConnectionRequestIndicationObserver('L2CAPCBLePsmConnectionRequestIndication'), ]
        super(L2CAPCBLePsmConnectionRequestOperation, self).subscribeToEvents()


class L2CAPCBLePsmConnectionCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLePsmConnectionCompleteIndicationObserver('L2CAPCBLePsmConnectionCompleteIndication'), ]
        super(L2CAPCBLePsmConnectionCompleteOperation, self).subscribeToEvents()


class L2CAPCBLePsmDisconnectNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLePsmDisconnectNotificationIndicationObserver('L2CAPCBLePsmDisconnectNotificationIndication'), ]
        super(L2CAPCBLePsmDisconnectNotificationOperation, self).subscribeToEvents()


class L2CAPCBNoPeerCreditsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBNoPeerCreditsIndicationObserver('L2CAPCBNoPeerCreditsIndication'), ]
        super(L2CAPCBNoPeerCreditsOperation, self).subscribeToEvents()


class L2CAPCBLocalCreditsNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLocalCreditsNotificationIndicationObserver('L2CAPCBLocalCreditsNotificationIndication'), ]
        super(L2CAPCBLocalCreditsNotificationOperation, self).subscribeToEvents()


class L2CAPCBLeCbDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLeCbDataIndicationObserver('L2CAPCBLeCbDataIndication'), ]
        super(L2CAPCBLeCbDataOperation, self).subscribeToEvents()

class L2CAPCBErrorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBErrorIndicationObserver('L2CAPCBErrorIndication'), ]
        super(L2CAPCBErrorOperation, self).subscribeToEvents()

class GATTClientProcedureExchangeMtuOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureExchangeMtuIndicationObserver('GATTClientProcedureExchangeMtuIndication'), ]
        super(GATTClientProcedureExchangeMtuOperation, self).subscribeToEvents()


class GATTClientProcedureDiscoverAllPrimaryServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureDiscoverAllPrimaryServicesIndicationObserver('GATTClientProcedureDiscoverAllPrimaryServicesIndication'), ]
        super(GATTClientProcedureDiscoverAllPrimaryServicesOperation, self).subscribeToEvents()


class GATTClientProcedureDiscoverPrimaryServicesByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationObserver('GATTClientProcedureDiscoverPrimaryServicesByUuidIndication'), ]
        super(GATTClientProcedureDiscoverPrimaryServicesByUuidOperation, self).subscribeToEvents()


class GATTClientProcedureFindIncludedServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureFindIncludedServicesIndicationObserver('GATTClientProcedureFindIncludedServicesIndication'), ]
        super(GATTClientProcedureFindIncludedServicesOperation, self).subscribeToEvents()


class GATTClientProcedureDiscoverAllCharacteristicsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureDiscoverAllCharacteristicsIndicationObserver('GATTClientProcedureDiscoverAllCharacteristicsIndication'), ]
        super(GATTClientProcedureDiscoverAllCharacteristicsOperation, self).subscribeToEvents()


class GATTClientProcedureDiscoverCharacteristicByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureDiscoverCharacteristicByUuidIndicationObserver('GATTClientProcedureDiscoverCharacteristicByUuidIndication'), ]
        super(GATTClientProcedureDiscoverCharacteristicByUuidOperation, self).subscribeToEvents()


class GATTClientProcedureDiscoverAllCharacteristicDescriptorsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationObserver('GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication'), ]
        super(GATTClientProcedureDiscoverAllCharacteristicDescriptorsOperation, self).subscribeToEvents()


class GATTClientProcedureReadCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureReadCharacteristicValueIndicationObserver('GATTClientProcedureReadCharacteristicValueIndication'), ]
        super(GATTClientProcedureReadCharacteristicValueOperation, self).subscribeToEvents()


class GATTClientProcedureReadUsingCharacteristicUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureReadUsingCharacteristicUuidIndicationObserver('GATTClientProcedureReadUsingCharacteristicUuidIndication'), ]
        super(GATTClientProcedureReadUsingCharacteristicUuidOperation, self).subscribeToEvents()


class GATTClientProcedureReadMultipleCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureReadMultipleCharacteristicValuesIndicationObserver('GATTClientProcedureReadMultipleCharacteristicValuesIndication'), ]
        super(GATTClientProcedureReadMultipleCharacteristicValuesOperation, self).subscribeToEvents()


class GATTClientProcedureWriteCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureWriteCharacteristicValueIndicationObserver('GATTClientProcedureWriteCharacteristicValueIndication'), ]
        super(GATTClientProcedureWriteCharacteristicValueOperation, self).subscribeToEvents()


class GATTClientProcedureReadCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureReadCharacteristicDescriptorIndicationObserver('GATTClientProcedureReadCharacteristicDescriptorIndication'), ]
        super(GATTClientProcedureReadCharacteristicDescriptorOperation, self).subscribeToEvents()


class GATTClientProcedureWriteCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureWriteCharacteristicDescriptorIndicationObserver('GATTClientProcedureWriteCharacteristicDescriptorIndication'), ]
        super(GATTClientProcedureWriteCharacteristicDescriptorOperation, self).subscribeToEvents()


class GATTClientNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientNotificationIndicationObserver('GATTClientNotificationIndication'), ]
        super(GATTClientNotificationOperation, self).subscribeToEvents()


class GATTClientIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientIndicationIndicationObserver('GATTClientIndicationIndication'), ]
        super(GATTClientIndicationOperation, self).subscribeToEvents()


class GATTServerMtuChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerMtuChangedIndicationObserver('GATTServerMtuChangedIndication'), ]
        super(GATTServerMtuChangedOperation, self).subscribeToEvents()


class GATTServerHandleValueConfirmationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerHandleValueConfirmationIndicationObserver('GATTServerHandleValueConfirmationIndication'), ]
        super(GATTServerHandleValueConfirmationOperation, self).subscribeToEvents()


class GATTServerAttributeWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerAttributeWrittenIndicationObserver('GATTServerAttributeWrittenIndication'), ]
        super(GATTServerAttributeWrittenOperation, self).subscribeToEvents()


class GATTServerCharacteristicCccdWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerCharacteristicCccdWrittenIndicationObserver('GATTServerCharacteristicCccdWrittenIndication'), ]
        super(GATTServerCharacteristicCccdWrittenOperation, self).subscribeToEvents()


class GATTServerAttributeWrittenWithoutResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerAttributeWrittenWithoutResponseIndicationObserver('GATTServerAttributeWrittenWithoutResponseIndication'), ]
        super(GATTServerAttributeWrittenWithoutResponseOperation, self).subscribeToEvents()


class GATTServerErrorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerErrorIndicationObserver('GATTServerErrorIndication'), ]
        super(GATTServerErrorOperation, self).subscribeToEvents()


class GATTServerLongCharacteristicWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerLongCharacteristicWrittenIndicationObserver('GATTServerLongCharacteristicWrittenIndication'), ]
        super(GATTServerLongCharacteristicWrittenOperation, self).subscribeToEvents()


class GATTServerAttributeReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerAttributeReadIndicationObserver('GATTServerAttributeReadIndication'), ]
        super(GATTServerAttributeReadOperation, self).subscribeToEvents()


class GAPGenericEventInitializationCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventInitializationCompleteIndicationObserver('GAPGenericEventInitializationCompleteIndication'), ]
        super(GAPGenericEventInitializationCompleteOperation, self).subscribeToEvents()


class GAPGenericEventInternalErrorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventInternalErrorIndicationObserver('GAPGenericEventInternalErrorIndication'), ]
        super(GAPGenericEventInternalErrorOperation, self).subscribeToEvents()


class GAPGenericEventAdvertisingSetupFailedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventAdvertisingSetupFailedIndicationObserver('GAPGenericEventAdvertisingSetupFailedIndication'), ]
        super(GAPGenericEventAdvertisingSetupFailedOperation, self).subscribeToEvents()


class GAPGenericEventAdvertisingParametersSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventAdvertisingParametersSetupCompleteIndicationObserver('GAPGenericEventAdvertisingParametersSetupCompleteIndication'), ]
        super(GAPGenericEventAdvertisingParametersSetupCompleteOperation, self).subscribeToEvents()


class GAPGenericEventAdvertisingDataSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventAdvertisingDataSetupCompleteIndicationObserver('GAPGenericEventAdvertisingDataSetupCompleteIndication'), ]
        super(GAPGenericEventAdvertisingDataSetupCompleteOperation, self).subscribeToEvents()


class GAPGenericEventWhiteListSizeReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventWhiteListSizeReadIndicationObserver('GAPGenericEventWhiteListSizeReadIndication'), ]
        super(GAPGenericEventWhiteListSizeReadOperation, self).subscribeToEvents()


class GAPGenericEventDeviceAddedToWhiteListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventDeviceAddedToWhiteListIndicationObserver('GAPGenericEventDeviceAddedToWhiteListIndication'), ]
        super(GAPGenericEventDeviceAddedToWhiteListOperation, self).subscribeToEvents()


class GAPGenericEventDeviceRemovedFromWhiteListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventDeviceRemovedFromWhiteListIndicationObserver('GAPGenericEventDeviceRemovedFromWhiteListIndication'), ]
        super(GAPGenericEventDeviceRemovedFromWhiteListOperation, self).subscribeToEvents()


class GAPGenericEventWhiteListClearedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventWhiteListClearedIndicationObserver('GAPGenericEventWhiteListClearedIndication'), ]
        super(GAPGenericEventWhiteListClearedOperation, self).subscribeToEvents()


class GAPGenericEventRandomAddressReadyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventRandomAddressReadyIndicationObserver('GAPGenericEventRandomAddressReadyIndication'), ]
        super(GAPGenericEventRandomAddressReadyOperation, self).subscribeToEvents()


class GAPGenericEventCreateConnectionCanceledOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventCreateConnectionCanceledIndicationObserver('GAPGenericEventCreateConnectionCanceledIndication'), ]
        super(GAPGenericEventCreateConnectionCanceledOperation, self).subscribeToEvents()


class GAPGenericEventPublicAddressReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPublicAddressReadIndicationObserver('GAPGenericEventPublicAddressReadIndication'), ]
        super(GAPGenericEventPublicAddressReadOperation, self).subscribeToEvents()


class GAPGenericEventAdvTxPowerLevelReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventAdvTxPowerLevelReadIndicationObserver('GAPGenericEventAdvTxPowerLevelReadIndication'), ]
        super(GAPGenericEventAdvTxPowerLevelReadOperation, self).subscribeToEvents()


class GAPGenericEventPrivateResolvableAddressVerifiedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPrivateResolvableAddressVerifiedIndicationObserver('GAPGenericEventPrivateResolvableAddressVerifiedIndication'), ]
        super(GAPGenericEventPrivateResolvableAddressVerifiedOperation, self).subscribeToEvents()


class GAPGenericEventRandomAddressSetOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventRandomAddressSetIndicationObserver('GAPGenericEventRandomAddressSetIndication'), ]
        super(GAPGenericEventRandomAddressSetOperation, self).subscribeToEvents()


class GAPAdvertisingEventStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventStateChangedIndicationObserver('GAPAdvertisingEventStateChangedIndication'), ]
        super(GAPAdvertisingEventStateChangedOperation, self).subscribeToEvents()


class GAPAdvertisingEventCommandFailedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventCommandFailedIndicationObserver('GAPAdvertisingEventCommandFailedIndication'), ]
        super(GAPAdvertisingEventCommandFailedOperation, self).subscribeToEvents()

class GAPScanningEventStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventStateChangedIndicationObserver('GAPScanningEventStateChangedIndication'), ]
        super(GAPScanningEventStateChangedOperation, self).subscribeToEvents()


class GAPScanningEventCommandFailedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventCommandFailedIndicationObserver('GAPScanningEventCommandFailedIndication'), ]
        super(GAPScanningEventCommandFailedOperation, self).subscribeToEvents()


class GAPScanningEventDeviceScannedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventDeviceScannedIndicationObserver('GAPScanningEventDeviceScannedIndication'), ]
        super(GAPScanningEventDeviceScannedOperation, self).subscribeToEvents()


class GAPConnectionEventConnectedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventConnectedIndicationObserver('GAPConnectionEventConnectedIndication'), ]
        super(GAPConnectionEventConnectedOperation, self).subscribeToEvents()


class GAPConnectionEventPairingRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPairingRequestIndicationObserver('GAPConnectionEventPairingRequestIndication'), ]
        super(GAPConnectionEventPairingRequestOperation, self).subscribeToEvents()


class GAPConnectionEventSlaveSecurityRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventSlaveSecurityRequestIndicationObserver('GAPConnectionEventSlaveSecurityRequestIndication'), ]
        super(GAPConnectionEventSlaveSecurityRequestOperation, self).subscribeToEvents()


class GAPConnectionEventPairingResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPairingResponseIndicationObserver('GAPConnectionEventPairingResponseIndication'), ]
        super(GAPConnectionEventPairingResponseOperation, self).subscribeToEvents()


class GAPConnectionEventAuthenticationRejectedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventAuthenticationRejectedIndicationObserver('GAPConnectionEventAuthenticationRejectedIndication'), ]
        super(GAPConnectionEventAuthenticationRejectedOperation, self).subscribeToEvents()


class GAPConnectionEventPasskeyRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPasskeyRequestIndicationObserver('GAPConnectionEventPasskeyRequestIndication'), ]
        super(GAPConnectionEventPasskeyRequestOperation, self).subscribeToEvents()


class GAPConnectionEventOobRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventOobRequestIndicationObserver('GAPConnectionEventOobRequestIndication'), ]
        super(GAPConnectionEventOobRequestOperation, self).subscribeToEvents()


class GAPConnectionEventPasskeyDisplayOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPasskeyDisplayIndicationObserver('GAPConnectionEventPasskeyDisplayIndication'), ]
        super(GAPConnectionEventPasskeyDisplayOperation, self).subscribeToEvents()


class GAPConnectionEventKeyExchangeRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventKeyExchangeRequestIndicationObserver('GAPConnectionEventKeyExchangeRequestIndication'), ]
        super(GAPConnectionEventKeyExchangeRequestOperation, self).subscribeToEvents()


class GAPConnectionEventKeysReceivedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventKeysReceivedIndicationObserver('GAPConnectionEventKeysReceivedIndication'), ]
        super(GAPConnectionEventKeysReceivedOperation, self).subscribeToEvents()


class GAPConnectionEventLongTermKeyRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventLongTermKeyRequestIndicationObserver('GAPConnectionEventLongTermKeyRequestIndication'), ]
        super(GAPConnectionEventLongTermKeyRequestOperation, self).subscribeToEvents()


class GAPConnectionEventEncryptionChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEncryptionChangedIndicationObserver('GAPConnectionEventEncryptionChangedIndication'), ]
        super(GAPConnectionEventEncryptionChangedOperation, self).subscribeToEvents()


class GAPConnectionEventPairingCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPairingCompleteIndicationObserver('GAPConnectionEventPairingCompleteIndication'), ]
        super(GAPConnectionEventPairingCompleteOperation, self).subscribeToEvents()


class GAPConnectionEventDisconnectedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventDisconnectedIndicationObserver('GAPConnectionEventDisconnectedIndication'), ]
        super(GAPConnectionEventDisconnectedOperation, self).subscribeToEvents()


class GAPConnectionEventRssiReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventRssiReadIndicationObserver('GAPConnectionEventRssiReadIndication'), ]
        super(GAPConnectionEventRssiReadOperation, self).subscribeToEvents()


class GAPConnectionEventTxPowerLevelReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventTxPowerLevelReadIndicationObserver('GAPConnectionEventTxPowerLevelReadIndication'), ]
        super(GAPConnectionEventTxPowerLevelReadOperation, self).subscribeToEvents()


class GAPConnectionEventPowerReadFailureOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPowerReadFailureIndicationObserver('GAPConnectionEventPowerReadFailureIndication'), ]
        super(GAPConnectionEventPowerReadFailureOperation, self).subscribeToEvents()


class GAPConnectionEventParameterUpdateRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventParameterUpdateRequestIndicationObserver('GAPConnectionEventParameterUpdateRequestIndication'), ]
        super(GAPConnectionEventParameterUpdateRequestOperation, self).subscribeToEvents()


class GAPConnectionEventParameterUpdateCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventParameterUpdateCompleteIndicationObserver('GAPConnectionEventParameterUpdateCompleteIndication'), ]
        super(GAPConnectionEventParameterUpdateCompleteOperation, self).subscribeToEvents()


class GAPConnectionEventLeDataLengthChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventLeDataLengthChangedIndicationObserver('GAPConnectionEventLeDataLengthChangedIndication'), ]
        super(GAPConnectionEventLeDataLengthChangedOperation, self).subscribeToEvents()


class GAPConnectionEventLeScOobDataRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventLeScOobDataRequestIndicationObserver('GAPConnectionEventLeScOobDataRequestIndication'), ]
        super(GAPConnectionEventLeScOobDataRequestOperation, self).subscribeToEvents()


class GAPConnectionEventLeScDisplayNumericValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventLeScDisplayNumericValueIndicationObserver('GAPConnectionEventLeScDisplayNumericValueIndication'), ]
        super(GAPConnectionEventLeScDisplayNumericValueOperation, self).subscribeToEvents()


class GAPConnectionEventLeScKeypressNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventLeScKeypressNotificationIndicationObserver('GAPConnectionEventLeScKeypressNotificationIndication'), ]
        super(GAPConnectionEventLeScKeypressNotificationOperation, self).subscribeToEvents()

class GAPLeScPublicKeyRegeneratedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPLeScPublicKeyRegeneratedIndicationObserver('GAPLeScPublicKeyRegeneratedIndication'), ]
        super(GAPLeScPublicKeyRegeneratedOperation, self).subscribeToEvents()


class GAPGenericEventLeScLocalOobDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventLeScLocalOobDataIndicationObserver('GAPGenericEventLeScLocalOobDataIndication'), ]
        super(GAPGenericEventLeScLocalOobDataOperation, self).subscribeToEvents()


class GAPGenericEventHostPrivacyStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventHostPrivacyStateChangedIndicationObserver('GAPGenericEventHostPrivacyStateChangedIndication'), ]
        super(GAPGenericEventHostPrivacyStateChangedOperation, self).subscribeToEvents()


class GAPGenericEventControllerPrivacyStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventControllerPrivacyStateChangedIndicationObserver('GAPGenericEventControllerPrivacyStateChangedIndication'), ]
        super(GAPGenericEventControllerPrivacyStateChangedOperation, self).subscribeToEvents()


class GAPGenericEventTxPowerLevelSetCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventTxPowerLevelSetCompleteIndicationObserver('GAPGenericEventTxPowerLevelSetCompleteIndication'), ]
        super(GAPGenericEventTxPowerLevelSetCompleteOperation, self).subscribeToEvents()


class GAPGenericEventLePhyEventOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventLePhyEventIndicationObserver('GAPGenericEventLePhyEventIndication'), ]
        super(GAPGenericEventLePhyEventOperation, self).subscribeToEvents()


class GAPControllerNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPControllerNotificationIndicationObserver('GAPControllerNotificationIndication'), ]
        super(GAPControllerNotificationOperation, self).subscribeToEvents()


class GAPBondCreatedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPBondCreatedIndicationObserver('GAPBondCreatedIndication'), ]
        super(GAPBondCreatedOperation, self).subscribeToEvents()


class GAPGenericEventChannelMapSetOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventChannelMapSetIndicationObserver('GAPGenericEventChannelMapSetIndication'), ]
        super(GAPGenericEventChannelMapSetOperation, self).subscribeToEvents()


class GAPConnectionEventChannelMapReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventChannelMapReadIndicationObserver('GAPConnectionEventChannelMapReadIndication'), ]
        super(GAPConnectionEventChannelMapReadOperation, self).subscribeToEvents()


class GAPConnectionEventChannelMapReadFailureOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventChannelMapReadFailureIndicationObserver('GAPConnectionEventChannelMapReadFailureIndication'), ]
        super(GAPConnectionEventChannelMapReadFailureOperation, self).subscribeToEvents()

class GAPConnectionEventChannelSelectionAlgorithm2Operation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventChannelSelectionAlgorithm2IndicationObserver('GAPConnectionEventChannelSelectionAlgorithm2Indication'), ]
        super(GAPConnectionEventChannelSelectionAlgorithm2Operation, self).subscribeToEvents()



def subscribe_to_async_ble_events_from(device, ack_policy=FsciAckPolicy.GLOBAL):
    ble_events = [
        L2CAPCBConfirmObserver('L2CAPCBConfirm'),
        GAPGenericEventInitializationCompleteIndicationObserver('GAPGenericEventInitializationCompleteIndication'),
        GAPAdvertisingEventCommandFailedIndicationObserver('GAPAdvertisingEventCommandFailedIndication'),
        GAPConnectionEventLeDataLengthChangedIndicationObserver('GAPConnectionEventLeDataLengthChangedIndication'),
        GATTServerCharacteristicCccdWrittenIndicationObserver('GATTServerCharacteristicCccdWrittenIndication')
    ]

    for ble_event in ble_events:
        FsciFramer(device, ack_policy=ack_policy, protocol=Protocol.BLE, baudrate=Baudrate.BR115200).addObserver(ble_event)
