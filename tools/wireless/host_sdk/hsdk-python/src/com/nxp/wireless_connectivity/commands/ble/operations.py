'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2022 NXP
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




class L2CAPInitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPInitRequestFrame
        self.observers = []
        super(L2CAPInitOperation, self).subscribeToEvents()

class L2CAPSendAttDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPSendAttDataRequestFrame
        self.observers = []
        super(L2CAPSendAttDataOperation, self).subscribeToEvents()

class L2CAPSendSmpDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPSendSmpDataRequestFrame
        self.observers = []
        super(L2CAPSendSmpDataOperation, self).subscribeToEvents()


class L2CAPRegisterAttCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPRegisterAttCallbackRequestFrame
        self.observers = []
        super(L2CAPRegisterAttCallbackOperation, self).subscribeToEvents()

class L2CAPRegisterSmpCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPRegisterSmpCallbackRequestFrame
        self.observers = []
        super(L2CAPRegisterSmpCallbackOperation, self).subscribeToEvents()


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

class L2CAPCBEnhancedConnectLePsmOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBEnhancedConnectLePsmRequestFrame
        self.observers = []
        super(L2CAPCBEnhancedConnectLePsmOperation, self).subscribeToEvents()

class L2CAPCBEnhancedChannelReconfigureOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBEnhancedChannelReconfigureRequestFrame
        self.observers = []
        super(L2CAPCBEnhancedChannelReconfigureOperation, self).subscribeToEvents()

class L2CAPCBEnhancedCancelConnectionOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.L2CAPCBEnhancedCancelConnectionRequestFrame
        self.observers = []
        super(L2CAPCBEnhancedCancelConnectionOperation, self).subscribeToEvents()


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

class GATTClientRegisterMultipleValueNotificationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterMultipleValueNotificationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterMultipleValueNotificationCallbackOperation, self).subscribeToEvents()

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

class GATTServerSendMultipleHandleValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerSendMultipleHandleValueNotificationRequestFrame
        self.observers = []
        super(GATTServerSendMultipleHandleValueNotificationOperation, self).subscribeToEvents()

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

class GATTClientReadMultipleVariableCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientReadMultipleVariableCharacteristicValuesRequestFrame
        self.observers = []
        super(GATTClientReadMultipleVariableCharacteristicValuesOperation, self).subscribeToEvents()

class GATTClientRegisterEnhancedProcedureCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterEnhancedProcedureCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterEnhancedProcedureCallbackOperation, self).subscribeToEvents()

class GATTClientRegisterEnhancedNotificationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterEnhancedNotificationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterEnhancedNotificationCallbackOperation, self).subscribeToEvents()

class GATTClientRegisterEnhancedIndicationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterEnhancedIndicationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterEnhancedIndicationCallbackOperation, self).subscribeToEvents()

class GATTClientRegisterEnhancedMultipleValueNotificationCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientRegisterEnhancedMultipleValueNotificationCallbackRequestFrame
        self.observers = []
        super(GATTClientRegisterEnhancedMultipleValueNotificationCallbackOperation, self).subscribeToEvents()

class GATTClientEnhancedDiscoverAllPrimaryServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedDiscoverAllPrimaryServicesRequestFrame
        self.observers = []
        super(GATTClientEnhancedDiscoverAllPrimaryServicesOperation, self).subscribeToEvents()

class GATTClientEnhancedDiscoverPrimaryServicesByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedDiscoverPrimaryServicesByUuidRequestFrame
        self.observers = []
        super(GATTClientEnhancedDiscoverPrimaryServicesByUuidOperation, self).subscribeToEvents()

class GATTClientEnhancedFindIncludedServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedFindIncludedServicesRequestFrame
        self.observers = []
        super(GATTClientEnhancedFindIncludedServicesOperation, self).subscribeToEvents()

class GATTClientEnhancedDiscoverAllCharacteristicsOfServiceOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequestFrame
        self.observers = []
        super(GATTClientEnhancedDiscoverAllCharacteristicsOfServiceOperation, self).subscribeToEvents()

class GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequestFrame
        self.observers = []
        super(GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidOperation, self).subscribeToEvents()

class GATTClientEnhancedDiscoverAllCharacteristicDescriptorsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequestFrame
        self.observers = []
        super(GATTClientEnhancedDiscoverAllCharacteristicDescriptorsOperation, self).subscribeToEvents()

class GATTClientEnhancedReadCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedReadCharacteristicValueRequestFrame
        self.observers = []
        super(GATTClientEnhancedReadCharacteristicValueOperation, self).subscribeToEvents()

class GATTClientEnhancedReadUsingCharacteristicUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedReadUsingCharacteristicUuidRequestFrame
        self.observers = []
        super(GATTClientEnhancedReadUsingCharacteristicUuidOperation, self).subscribeToEvents()

class GATTClientEnhancedReadMultipleCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedReadMultipleCharacteristicValuesRequestFrame
        self.observers = []
        super(GATTClientEnhancedReadMultipleCharacteristicValuesOperation, self).subscribeToEvents()

class GATTClientEnhancedWriteCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedWriteCharacteristicValueRequestFrame
        self.observers = []
        super(GATTClientEnhancedWriteCharacteristicValueOperation, self).subscribeToEvents()

class GATTClientEnhancedReadCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedReadCharacteristicDescriptorRequestFrame
        self.observers = []
        super(GATTClientEnhancedReadCharacteristicDescriptorOperation, self).subscribeToEvents()

class GATTClientEnhancedWriteCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedWriteCharacteristicDescriptorRequestFrame
        self.observers = []
        super(GATTClientEnhancedWriteCharacteristicDescriptorOperation, self).subscribeToEvents()

class GATTClientEnhancedReadMultipleVariableCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequestFrame
        self.observers = []
        super(GATTClientEnhancedReadMultipleVariableCharacteristicValuesOperation, self).subscribeToEvents()

class GATTServerRegisterEnhancedCallbackOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerRegisterEnhancedCallbackRequestFrame
        self.observers = []
        super(GATTServerRegisterEnhancedCallbackOperation, self).subscribeToEvents()

class GATTServerEnhancedSendAttributeWrittenStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendAttributeWrittenStatusRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendAttributeWrittenStatusOperation, self).subscribeToEvents()

class GATTServerEnhancedSendNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendNotificationRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendNotificationOperation, self).subscribeToEvents()

class GATTServerEnhancedSendIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendIndicationRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendIndicationOperation, self).subscribeToEvents()

class GATTServerEnhancedSendInstantValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendInstantValueNotificationRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendInstantValueNotificationOperation, self).subscribeToEvents()

class GATTServerEnhancedSendInstantValueIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendInstantValueIndicationRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendInstantValueIndicationOperation, self).subscribeToEvents()

class GATTServerEnhancedSendAttributeReadStatusOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendAttributeReadStatusRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendAttributeReadStatusOperation, self).subscribeToEvents()

class GATTServerEnhancedSendMultipleHandleValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTServerEnhancedSendMultipleHandleValueNotificationRequestFrame
        self.observers = []
        super(GATTServerEnhancedSendMultipleHandleValueNotificationOperation, self).subscribeToEvents()

class GATTClientGetDatabaseHashOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTClientGetDatabaseHashRequestFrame
        self.observers = []
        super(GATTClientGetDatabaseHashOperation, self).subscribeToEvents()


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

class GATTDBDynamicEndDatabaseUpdateOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBDynamicEndDatabaseUpdateRequestFrame
        self.observers = []
        super(GATTDBDynamicEndDatabaseUpdateOperation, self).subscribeToEvents()


class GATTDBAttFindInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttFindInformationRequestFrame
        self.observers = [GATTDBAttFindInformationIndicationObserver('GATTDBAttFindInformationIndication'), ]
        super(GATTDBAttFindInformationOperation, self).subscribeToEvents()

class GATTDBAttFindByTypeValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttFindByTypeValueRequestFrame
        self.observers = [GATTDBAttFindByTypeValueIndicationObserver('GATTDBAttFindByTypeValueIndication'), ]
        super(GATTDBAttFindByTypeValueOperation, self).subscribeToEvents()

class GATTDBAttReadByTypeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttReadByTypeRequestFrame
        self.observers = [GATTDBAttReadByTypeIndicationObserver('GATTDBAttReadByTypeIndication'), ]
        super(GATTDBAttReadByTypeOperation, self).subscribeToEvents()

class GATTDBAttReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttReadRequestFrame
        self.observers = [GATTDBAttReadIndicationObserver('GATTDBAttReadIndication'), ]
        super(GATTDBAttReadOperation, self).subscribeToEvents()

class GATTDBAttReadBlobOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttReadBlobRequestFrame
        self.observers = [GATTDBAttReadBlobIndicationObserver('GATTDBAttReadBlobIndication'), ]
        super(GATTDBAttReadBlobOperation, self).subscribeToEvents()

class GATTDBAttReadMultipleOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttReadMultipleRequestFrame
        self.observers = [GATTDBAttReadMultipleIndicationObserver('GATTDBAttReadMultipleIndication'), ]
        super(GATTDBAttReadMultipleOperation, self).subscribeToEvents()

class GATTDBAttReadByGroupTypeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttReadByGroupTypeRequestFrame
        self.observers = [GATTDBAttReadByGroupTypeIndicationObserver('GATTDBAttReadByGroupTypeIndication'), ]
        super(GATTDBAttReadByGroupTypeOperation, self).subscribeToEvents()

class GATTDBAttWriteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttWriteRequestFrame
        self.observers = [GATTDBAttWriteIndicationObserver('GATTDBAttWriteIndication'), ]
        super(GATTDBAttWriteOperation, self).subscribeToEvents()

class GATTDBAttWriteCommandOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttWriteCommandRequestFrame
        self.observers = []
        super(GATTDBAttWriteCommandOperation, self).subscribeToEvents()

class GATTDBAttSignedWriteCommandOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttSignedWriteCommandRequestFrame
        self.observers = []
        super(GATTDBAttSignedWriteCommandOperation, self).subscribeToEvents()

class GATTDBAttPrepareWriteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttPrepareWriteRequestFrame
        self.observers = [GATTDBAttPrepareWriteIndicationObserver('GATTDBAttPrepareWriteIndication'), ]
        super(GATTDBAttPrepareWriteOperation, self).subscribeToEvents()

class GATTDBAttExecuteWriteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttExecuteWriteRequestFrame
        self.observers = [GATTDBAttExecuteWriteIndicationObserver('GATTDBAttExecuteWriteIndication'), ]
        super(GATTDBAttExecuteWriteOperation, self).subscribeToEvents()

class GATTDBAttExecuteWriteFromQueueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttExecuteWriteFromQueueRequestFrame
        self.observers = [GATTDBAttExecuteWriteFromQueueIndicationObserver('GATTDBAttExecuteWriteFromQueueIndication'), ]
        super(GATTDBAttExecuteWriteFromQueueOperation, self).subscribeToEvents()

class GATTDBAttPrepareNotificationIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GATTDBAttPrepareNotificationIndicationRequestFrame
        self.observers = []
        super(GATTDBAttPrepareNotificationIndicationOperation, self).subscribeToEvents()


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

class GAPSendPeripheralSecurityRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSendPeripheralSecurityRequestRequestFrame
        self.observers = []
        super(GAPSendPeripheralSecurityRequestOperation, self).subscribeToEvents()

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

class GAPReadFilterAcceptListSizeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadFilterAcceptListSizeRequestFrame
        self.observers = []
        super(GAPReadFilterAcceptListSizeOperation, self).subscribeToEvents()

class GAPClearFilterAcceptListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPClearFilterAcceptListRequestFrame
        self.observers = []
        super(GAPClearFilterAcceptListOperation, self).subscribeToEvents()

class GAPAddDeviceToFilterAcceptListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPAddDeviceToFilterAcceptListRequestFrame
        self.observers = []
        super(GAPAddDeviceToFilterAcceptListOperation, self).subscribeToEvents()

class GAPRemoveDeviceFromFilterAcceptListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRemoveDeviceFromFilterAcceptListRequestFrame
        self.observers = []
        super(GAPRemoveDeviceFromFilterAcceptListOperation, self).subscribeToEvents()

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

class ControllerSetScanDupFiltModeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.ControllerSetScanDupFiltModeRequestFrame
        self.observers = []
        super(ControllerSetScanDupFiltModeOperation, self).subscribeToEvents()

class GAPReadControllerLocalRPAOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadControllerLocalRPARequestFrame
        self.observers = []
        super(GAPReadControllerLocalRPAOperation, self).subscribeToEvents()

class GAPCheckNvmIndexOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPCheckNvmIndexRequestFrame
        self.observers = [GAPCheckNvmIndexIndicationObserver('GAPCheckNvmIndexIndication'), ]
        super(GAPCheckNvmIndexOperation, self).subscribeToEvents()

class GAPGetDeviceIdFromConnHandleOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPGetDeviceIdFromConnHandleRequestFrame
        self.observers = [GAPGetDeviceIdFromConnHandleIndicationObserver('GAPGetDeviceIdFromConnHandleIndication'), ]
        super(GAPGetDeviceIdFromConnHandleOperation, self).subscribeToEvents()

class GAPAdvIndexChangeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPAdvIndexChangeRequestFrame
        self.observers = []
        super(GAPAdvIndexChangeOperation, self).subscribeToEvents()

class GAPSetExtAdvertisingParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetExtAdvertisingParametersRequestFrame
        self.observers = []
        super(GAPSetExtAdvertisingParametersOperation, self).subscribeToEvents()

class GAPStartExtAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStartExtAdvertisingRequestFrame
        self.observers = []
        super(GAPStartExtAdvertisingOperation, self).subscribeToEvents()

class GAPRemoveAdvertisingSetOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPRemoveAdvertisingSetRequestFrame
        self.observers = []
        super(GAPRemoveAdvertisingSetOperation, self).subscribeToEvents()

class GAPStopExtAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStopExtAdvertisingRequestFrame
        self.observers = []
        super(GAPStopExtAdvertisingOperation, self).subscribeToEvents()

class GAPUpdatePeriodicAdvListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPUpdatePeriodicAdvListRequestFrame
        self.observers = []
        super(GAPUpdatePeriodicAdvListOperation, self).subscribeToEvents()

class GAPSetPeriodicAdvParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetPeriodicAdvParametersRequestFrame
        self.observers = []
        super(GAPSetPeriodicAdvParametersOperation, self).subscribeToEvents()

class GAPStartPeriodicAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStartPeriodicAdvertisingRequestFrame
        self.observers = []
        super(GAPStartPeriodicAdvertisingOperation, self).subscribeToEvents()

class GAPStopPeriodicAdvertisingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPStopPeriodicAdvertisingRequestFrame
        self.observers = []
        super(GAPStopPeriodicAdvertisingOperation, self).subscribeToEvents()

class GAPSetExtAdvertisingDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetExtAdvertisingDataRequestFrame
        self.observers = []
        super(GAPSetExtAdvertisingDataOperation, self).subscribeToEvents()

class GAPSetPeriodicAdvertisingDataOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetPeriodicAdvertisingDataRequestFrame
        self.observers = []
        super(GAPSetPeriodicAdvertisingDataOperation, self).subscribeToEvents()

class GAPPeriodicAdvCreateSyncOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvCreateSyncRequestFrame
        self.observers = []
        super(GAPPeriodicAdvCreateSyncOperation, self).subscribeToEvents()

class GAPPeriodicAdvTerminateSyncOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvTerminateSyncRequestFrame
        self.observers = []
        super(GAPPeriodicAdvTerminateSyncOperation, self).subscribeToEvents()

class GAPGenerateDHKeyV2Operation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPGenerateDHKeyV2RequestFrame
        self.observers = []
        super(GAPGenerateDHKeyV2Operation, self).subscribeToEvents()

class GAPModifySleepClockAccuracyOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPModifySleepClockAccuracyRequestFrame
        self.observers = []
        super(GAPModifySleepClockAccuracyOperation, self).subscribeToEvents()

class ControllerConfigureAdvCodingSchemeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.ControllerConfigureAdvCodingSchemeRequestFrame
        self.observers = []
        super(ControllerConfigureAdvCodingSchemeOperation, self).subscribeToEvents()

class GAPSetConnectionlessCteTransmitParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetConnectionlessCteTransmitParametersRequestFrame
        self.observers = []
        super(GAPSetConnectionlessCteTransmitParametersOperation, self).subscribeToEvents()

class GAPEnableConnectionlessCteTransmitOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableConnectionlessCteTransmitRequestFrame
        self.observers = []
        super(GAPEnableConnectionlessCteTransmitOperation, self).subscribeToEvents()

class GAPEnableConnectionlessIqSamplingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableConnectionlessIqSamplingRequestFrame
        self.observers = []
        super(GAPEnableConnectionlessIqSamplingOperation, self).subscribeToEvents()

class GAPSetConnectionCteReceiveParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetConnectionCteReceiveParametersRequestFrame
        self.observers = []
        super(GAPSetConnectionCteReceiveParametersOperation, self).subscribeToEvents()

class GAPSetConnectionCteTransmitParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetConnectionCteTransmitParametersRequestFrame
        self.observers = []
        super(GAPSetConnectionCteTransmitParametersOperation, self).subscribeToEvents()

class GAPEnableConnectionCteRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableConnectionCteRequestRequestFrame
        self.observers = []
        super(GAPEnableConnectionCteRequestOperation, self).subscribeToEvents()

class GAPEnableConnectionCteResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableConnectionCteResponseRequestFrame
        self.observers = []
        super(GAPEnableConnectionCteResponseOperation, self).subscribeToEvents()

class GAPReadAntennaInformationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadAntennaInformationRequestFrame
        self.observers = []
        super(GAPReadAntennaInformationOperation, self).subscribeToEvents()

class WritePublicDeviceAddressOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.WritePublicDeviceAddressRequestFrame
        self.observers = []
        super(WritePublicDeviceAddressOperation, self).subscribeToEvents()

class GAPPeriodicAdvReceiveEnableOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvReceiveEnableRequestFrame
        self.observers = []
        super(GAPPeriodicAdvReceiveEnableOperation, self).subscribeToEvents()

class GAPPeriodicAdvReceiveDisableOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvReceiveDisableRequestFrame
        self.observers = []
        super(GAPPeriodicAdvReceiveDisableOperation, self).subscribeToEvents()

class GAPPeriodicAdvSyncTransferOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvSyncTransferRequestFrame
        self.observers = []
        super(GAPPeriodicAdvSyncTransferOperation, self).subscribeToEvents()

class GAPPeriodicAdvSetInfoTransferOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPPeriodicAdvSetInfoTransferRequestFrame
        self.observers = []
        super(GAPPeriodicAdvSetInfoTransferOperation, self).subscribeToEvents()

class GAPSetPeriodicAdvSyncTransferParamsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetPeriodicAdvSyncTransferParamsRequestFrame
        self.observers = []
        super(GAPSetPeriodicAdvSyncTransferParamsOperation, self).subscribeToEvents()

class GAPSetDefaultPeriodicAdvSyncTransferParamsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetDefaultPeriodicAdvSyncTransferParamsRequestFrame
        self.observers = []
        super(GAPSetDefaultPeriodicAdvSyncTransferParamsOperation, self).subscribeToEvents()

class GAPEnhancedReadTransmitPowerLevelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnhancedReadTransmitPowerLevelRequestFrame
        self.observers = []
        super(GAPEnhancedReadTransmitPowerLevelOperation, self).subscribeToEvents()

class GAPReadRemoteTransmitPowerLevelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPReadRemoteTransmitPowerLevelRequestFrame
        self.observers = []
        super(GAPReadRemoteTransmitPowerLevelOperation, self).subscribeToEvents()

class GAPSetPathLossReportingParametersOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPSetPathLossReportingParametersRequestFrame
        self.observers = []
        super(GAPSetPathLossReportingParametersOperation, self).subscribeToEvents()

class GAPEnablePathLossReportingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnablePathLossReportingRequestFrame
        self.observers = []
        super(GAPEnablePathLossReportingOperation, self).subscribeToEvents()

class GAPEnableTransmitPowerReportingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEnableTransmitPowerReportingRequestFrame
        self.observers = []
        super(GAPEnableTransmitPowerReportingOperation, self).subscribeToEvents()

class GAPEattConnectionOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEattConnectionRequestFrame
        self.observers = []
        super(GAPEattConnectionOperation, self).subscribeToEvents()

class GAPEattReconfigureOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEattReconfigureRequestFrame
        self.observers = []
        super(GAPEattReconfigureOperation, self).subscribeToEvents()

class GAPEattSendCreditsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.GAPEattSendCreditsRequestFrame
        self.observers = []
        super(GAPEattSendCreditsOperation, self).subscribeToEvents()


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

class FSCIGetNbuVersionOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCIGetNbuVersionRequestFrame
        self.observers = [FSCIGetNbuVersionResponseObserver('FSCIGetNbuVersionResponse'), ]
        super(FSCIGetNbuVersionOperation, self).subscribeToEvents()

class FSCINVGetNvVPSizeOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = Spec.FSCINVGetNvVPSizeRequestFrame
        self.observers = []
        super(FSCINVGetNvVPSizeOperation, self).subscribeToEvents()

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

class L2CAPCBChannelStatusNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBChannelStatusNotificationIndicationObserver('L2CAPCBChannelStatusNotificationIndication'), ]
        super(L2CAPCBChannelStatusNotificationOperation, self).subscribeToEvents()

class L2CAPCBLePsmEnhancedConnectRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLePsmEnhancedConnectRequestIndicationObserver('L2CAPCBLePsmEnhancedConnectRequestIndication'), ]
        super(L2CAPCBLePsmEnhancedConnectRequestOperation, self).subscribeToEvents()

class L2CAPCBLePsmEnhancedConnectionCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBLePsmEnhancedConnectionCompleteIndicationObserver('L2CAPCBLePsmEnhancedConnectionCompleteIndication'), ]
        super(L2CAPCBLePsmEnhancedConnectionCompleteOperation, self).subscribeToEvents()

class L2CAPCBEnhancedReconfigureRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBEnhancedReconfigureRequestIndicationObserver('L2CAPCBEnhancedReconfigureRequestIndication'), ]
        super(L2CAPCBEnhancedReconfigureRequestOperation, self).subscribeToEvents()

class L2CAPCBEnhancedReconfigureResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [L2CAPCBEnhancedReconfigureResponseIndicationObserver('L2CAPCBEnhancedReconfigureResponseIndication'), ]
        super(L2CAPCBEnhancedReconfigureResponseOperation, self).subscribeToEvents()


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

class GATTClientMultipleHandleValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientMultipleHandleValueNotificationIndicationObserver('GATTClientMultipleHandleValueNotificationIndication'), ]
        super(GATTClientMultipleHandleValueNotificationOperation, self).subscribeToEvents()

class GATTClientProcedureReadMultipleVariableLenCharValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureReadMultipleVariableLenCharValuesIndicationObserver('GATTClientProcedureReadMultipleVariableLenCharValuesIndication'), ]
        super(GATTClientProcedureReadMultipleVariableLenCharValuesOperation, self).subscribeToEvents()

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

class GATTClientProcedureEnhancedDiscoverAllPrimaryServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndicationObserver('GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication'), ]
        super(GATTClientProcedureEnhancedDiscoverAllPrimaryServicesOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndicationObserver('GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication'), ]
        super(GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedFindIncludedServicesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedFindIncludedServicesIndicationObserver('GATTClientProcedureEnhancedFindIncludedServicesIndication'), ]
        super(GATTClientProcedureEnhancedFindIncludedServicesOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedDiscoverAllCharacteristicsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndicationObserver('GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication'), ]
        super(GATTClientProcedureEnhancedDiscoverAllCharacteristicsOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedDiscoverCharacteristicByUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndicationObserver('GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication'), ]
        super(GATTClientProcedureEnhancedDiscoverCharacteristicByUuidOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndicationObserver('GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndication'), ]
        super(GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedReadCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedReadCharacteristicValueIndicationObserver('GATTClientProcedureEnhancedReadCharacteristicValueIndication'), ]
        super(GATTClientProcedureEnhancedReadCharacteristicValueOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedReadUsingCharacteristicUuidOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationObserver('GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndication'), ]
        super(GATTClientProcedureEnhancedReadUsingCharacteristicUuidOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedReadMultipleCharacteristicValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndicationObserver('GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication'), ]
        super(GATTClientProcedureEnhancedReadMultipleCharacteristicValuesOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedWriteCharacteristicValueOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedWriteCharacteristicValueIndicationObserver('GATTClientProcedureEnhancedWriteCharacteristicValueIndication'), ]
        super(GATTClientProcedureEnhancedWriteCharacteristicValueOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedReadCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationObserver('GATTClientProcedureEnhancedReadCharacteristicDescriptorIndication'), ]
        super(GATTClientProcedureEnhancedReadCharacteristicDescriptorOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedWriteCharacteristicDescriptorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationObserver('GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndication'), ]
        super(GATTClientProcedureEnhancedWriteCharacteristicDescriptorOperation, self).subscribeToEvents()

class GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndicationObserver('GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication'), ]
        super(GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesOperation, self).subscribeToEvents()

class GATTClientEnhancedMultipleHandleValueNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientEnhancedMultipleHandleValueNotificationIndicationObserver('GATTClientEnhancedMultipleHandleValueNotificationIndication'), ]
        super(GATTClientEnhancedMultipleHandleValueNotificationOperation, self).subscribeToEvents()

class GATTClientEnhancedNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientEnhancedNotificationIndicationObserver('GATTClientEnhancedNotificationIndication'), ]
        super(GATTClientEnhancedNotificationOperation, self).subscribeToEvents()

class GATTClientEnhancedIndicationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTClientEnhancedIndicationIndicationObserver('GATTClientEnhancedIndicationIndication'), ]
        super(GATTClientEnhancedIndicationOperation, self).subscribeToEvents()

class GATTServerEnhancedHandleValueConfirmationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedHandleValueConfirmationIndicationObserver('GATTServerEnhancedHandleValueConfirmationIndication'), ]
        super(GATTServerEnhancedHandleValueConfirmationOperation, self).subscribeToEvents()

class GATTServerEnhancedAttributeWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedAttributeWrittenIndicationObserver('GATTServerEnhancedAttributeWrittenIndication'), ]
        super(GATTServerEnhancedAttributeWrittenOperation, self).subscribeToEvents()

class GATTServerEnhancedCharacteristicCccdWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedCharacteristicCccdWrittenIndicationObserver('GATTServerEnhancedCharacteristicCccdWrittenIndication'), ]
        super(GATTServerEnhancedCharacteristicCccdWrittenOperation, self).subscribeToEvents()

class GATTServerEnhancedAttributeWrittenWithoutResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedAttributeWrittenWithoutResponseIndicationObserver('GATTServerEnhancedAttributeWrittenWithoutResponseIndication'), ]
        super(GATTServerEnhancedAttributeWrittenWithoutResponseOperation, self).subscribeToEvents()

class GATTServerEnhancedErrorOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedErrorIndicationObserver('GATTServerEnhancedErrorIndication'), ]
        super(GATTServerEnhancedErrorOperation, self).subscribeToEvents()

class GATTServerEnhancedLongCharacteristicWrittenOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedLongCharacteristicWrittenIndicationObserver('GATTServerEnhancedLongCharacteristicWrittenIndication'), ]
        super(GATTServerEnhancedLongCharacteristicWrittenOperation, self).subscribeToEvents()

class GATTServerEnhancedAttributeReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTServerEnhancedAttributeReadIndicationObserver('GATTServerEnhancedAttributeReadIndication'), ]
        super(GATTServerEnhancedAttributeReadOperation, self).subscribeToEvents()

class GATTDBAttOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GATTDBAttConfirmObserver('GATTDBAttConfirm'), ]
        super(GATTDBAttOperation, self).subscribeToEvents()

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

class GAPGenericEventFilterAcceptListSizeReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventFilterAcceptListSizeReadIndicationObserver('GAPGenericEventFilterAcceptListSizeReadIndication'), ]
        super(GAPGenericEventFilterAcceptListSizeReadOperation, self).subscribeToEvents()

class GAPGenericEventDeviceAddedToFilterAcceptListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventDeviceAddedToFilterAcceptListIndicationObserver('GAPGenericEventDeviceAddedToFilterAcceptListIndication'), ]
        super(GAPGenericEventDeviceAddedToFilterAcceptListOperation, self).subscribeToEvents()

class GAPGenericEventDeviceRemovedFromFilterAcceptListOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventDeviceRemovedFromFilterAcceptListIndicationObserver('GAPGenericEventDeviceRemovedFromFilterAcceptListIndication'), ]
        super(GAPGenericEventDeviceRemovedFromFilterAcceptListOperation, self).subscribeToEvents()

class GAPGenericEventFilterAcceptListClearedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventFilterAcceptListClearedIndicationObserver('GAPGenericEventFilterAcceptListClearedIndication'), ]
        super(GAPGenericEventFilterAcceptListClearedOperation, self).subscribeToEvents()

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

class GAPConnectionEventPeripheralSecurityRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPeripheralSecurityRequestIndicationObserver('GAPConnectionEventPeripheralSecurityRequestIndication'), ]
        super(GAPConnectionEventPeripheralSecurityRequestOperation, self).subscribeToEvents()

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

class GAPGenericEventExtAdvertisingParamSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventExtAdvertisingParamSetupCompleteIndicationObserver('GAPGenericEventExtAdvertisingParamSetupCompleteIndication'), ]
        super(GAPGenericEventExtAdvertisingParamSetupCompleteOperation, self).subscribeToEvents()

class GAPGenericEventExtAdvertisingDataSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventExtAdvertisingDataSetupCompleteIndicationObserver('GAPGenericEventExtAdvertisingDataSetupCompleteIndication'), ]
        super(GAPGenericEventExtAdvertisingDataSetupCompleteOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvParamSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvParamSetupCompleteIndicationObserver('GAPGenericEventPeriodicAdvParamSetupCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvParamSetupCompleteOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvDataSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvDataSetupCompleteIndicationObserver('GAPGenericEventPeriodicAdvDataSetupCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvDataSetupCompleteOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvListUpdateCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvListUpdateCompleteIndicationObserver('GAPGenericEventPeriodicAdvListUpdateCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvListUpdateCompleteOperation, self).subscribeToEvents()

class GAPAdvertisingEventExtAdvertisingStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventExtAdvertisingStateChangedIndicationObserver('GAPAdvertisingEventExtAdvertisingStateChangedIndication'), ]
        super(GAPAdvertisingEventExtAdvertisingStateChangedOperation, self).subscribeToEvents()

class GAPAdvertisingEventAdvertisingSetTerminatedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventAdvertisingSetTerminatedIndicationObserver('GAPAdvertisingEventAdvertisingSetTerminatedIndication'), ]
        super(GAPAdvertisingEventAdvertisingSetTerminatedOperation, self).subscribeToEvents()

class GAPAdvertisingEventExtAdvertisingSetRemoveCompletedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndicationObserver('GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndication'), ]
        super(GAPAdvertisingEventExtAdvertisingSetRemoveCompletedOperation, self).subscribeToEvents()

class GAPAdvertisingEventExtScanReqReceivedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPAdvertisingEventExtScanReqReceivedIndicationObserver('GAPAdvertisingEventExtScanReqReceivedIndication'), ]
        super(GAPAdvertisingEventExtScanReqReceivedOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvertisingStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvertisingStateChangedIndicationObserver('GAPGenericEventPeriodicAdvertisingStateChangedIndication'), ]
        super(GAPGenericEventPeriodicAdvertisingStateChangedOperation, self).subscribeToEvents()

class GAPScanningEventExtDeviceScannedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventExtDeviceScannedIndicationObserver('GAPScanningEventExtDeviceScannedIndication'), ]
        super(GAPScanningEventExtDeviceScannedOperation, self).subscribeToEvents()

class GAPScanningEventPeriodicAdvSyncEstablishedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventPeriodicAdvSyncEstablishedIndicationObserver('GAPScanningEventPeriodicAdvSyncEstablishedIndication'), ]
        super(GAPScanningEventPeriodicAdvSyncEstablishedOperation, self).subscribeToEvents()

class GAPScanningEventPeriodicAdvSyncTerminatedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventPeriodicAdvSyncTerminatedIndicationObserver('GAPScanningEventPeriodicAdvSyncTerminatedIndication'), ]
        super(GAPScanningEventPeriodicAdvSyncTerminatedOperation, self).subscribeToEvents()

class GAPScanningEventPeriodicAdvSyncLostOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventPeriodicAdvSyncLostIndicationObserver('GAPScanningEventPeriodicAdvSyncLostIndication'), ]
        super(GAPScanningEventPeriodicAdvSyncLostOperation, self).subscribeToEvents()

class GAPScanningEventPeriodicDeviceScannedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventPeriodicDeviceScannedIndicationObserver('GAPScanningEventPeriodicDeviceScannedIndication'), ]
        super(GAPScanningEventPeriodicDeviceScannedOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvCreateSyncCancelledOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvCreateSyncCancelledIndicationObserver('GAPGenericEventPeriodicAdvCreateSyncCancelledIndication'), ]
        super(GAPGenericEventPeriodicAdvCreateSyncCancelledOperation, self).subscribeToEvents()

class GAPConnectionEventChannelSelectionAlgorithm2Operation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventChannelSelectionAlgorithm2IndicationObserver('GAPConnectionEventChannelSelectionAlgorithm2Indication'), ]
        super(GAPConnectionEventChannelSelectionAlgorithm2Operation, self).subscribeToEvents()

class GAPGenericEventTxEntryAvailableOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventTxEntryAvailableIndicationObserver('GAPGenericEventTxEntryAvailableIndication'), ]
        super(GAPGenericEventTxEntryAvailableOperation, self).subscribeToEvents()

class GAPGenericEventControllerLocalRPAReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventControllerLocalRPAReadIndicationObserver('GAPGenericEventControllerLocalRPAReadIndication'), ]
        super(GAPGenericEventControllerLocalRPAReadOperation, self).subscribeToEvents()

class GAPGetConnectionHandleFromDeviceIdOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGetConnectionHandleFromDeviceIdIndicationObserver('GAPGetConnectionHandleFromDeviceIdIndication'), ]
        super(GAPGetConnectionHandleFromDeviceIdOperation, self).subscribeToEvents()

class GAPPairingEventNoLTKOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPPairingEventNoLTKIndicationObserver('GAPPairingEventNoLTKIndication'), ]
        super(GAPPairingEventNoLTKOperation, self).subscribeToEvents()

class GAPPairingAlreadyStartedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPPairingAlreadyStartedIndicationObserver('GAPPairingAlreadyStartedIndication'), ]
        super(GAPPairingAlreadyStartedOperation, self).subscribeToEvents()

class GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndicationObserver('GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndication'), ]
        super(GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteOperation, self).subscribeToEvents()

class GAPGenericEventConnectionlessCteTransmitStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventConnectionlessCteTransmitStateChangedIndicationObserver('GAPGenericEventConnectionlessCteTransmitStateChangedIndication'), ]
        super(GAPGenericEventConnectionlessCteTransmitStateChangedOperation, self).subscribeToEvents()

class GAPGenericEventConnectionlessIqSamplingStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventConnectionlessIqSamplingStateChangedIndicationObserver('GAPGenericEventConnectionlessIqSamplingStateChangedIndication'), ]
        super(GAPGenericEventConnectionlessIqSamplingStateChangedOperation, self).subscribeToEvents()

class GAPGenericEventAntennaInformationReadOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventAntennaInformationReadIndicationObserver('GAPGenericEventAntennaInformationReadIndication'), ]
        super(GAPGenericEventAntennaInformationReadOperation, self).subscribeToEvents()

class GAPScanningEventConnectionlessIqReportReceivedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventConnectionlessIqReportReceivedIndicationObserver('GAPScanningEventConnectionlessIqReportReceivedIndication'), ]
        super(GAPScanningEventConnectionlessIqReportReceivedOperation, self).subscribeToEvents()

class GAPConnectionEventIqReportReceivedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventIqReportReceivedIndicationObserver('GAPConnectionEventIqReportReceivedIndication'), ]
        super(GAPConnectionEventIqReportReceivedOperation, self).subscribeToEvents()

class GAPConnectionEventCteRequestFailedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventCteRequestFailedIndicationObserver('GAPConnectionEventCteRequestFailedIndication'), ]
        super(GAPConnectionEventCteRequestFailedOperation, self).subscribeToEvents()

class GAPConnectionEventCteReceiveParamsSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventCteReceiveParamsSetupCompleteIndicationObserver('GAPConnectionEventCteReceiveParamsSetupCompleteIndication'), ]
        super(GAPConnectionEventCteReceiveParamsSetupCompleteOperation, self).subscribeToEvents()

class GAPConnectionEventCteTransmitParamsSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventCteTransmitParamsSetupCompleteIndicationObserver('GAPConnectionEventCteTransmitParamsSetupCompleteIndication'), ]
        super(GAPConnectionEventCteTransmitParamsSetupCompleteOperation, self).subscribeToEvents()

class GAPConnectionEventCteReqStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventCteReqStateChangedIndicationObserver('GAPConnectionEventCteReqStateChangedIndication'), ]
        super(GAPConnectionEventCteReqStateChangedOperation, self).subscribeToEvents()

class GAPConnectionEventCteRspStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventCteRspStateChangedIndicationObserver('GAPConnectionEventCteRspStateChangedIndication'), ]
        super(GAPConnectionEventCteRspStateChangedOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvRecvEnableCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationObserver('GAPGenericEventPeriodicAdvRecvEnableCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvRecvEnableCompleteOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvSyncTransferCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationObserver('GAPGenericEventPeriodicAdvSyncTransferCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvSyncTransferCompleteOperation, self).subscribeToEvents()

class GAPGenericEventPeriodicAdvSetInfoTransferCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationObserver('GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndication'), ]
        super(GAPGenericEventPeriodicAdvSetInfoTransferCompleteOperation, self).subscribeToEvents()

class GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationObserver('GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndication'), ]
        super(GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteOperation, self).subscribeToEvents()

class GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationObserver('GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndication'), ]
        super(GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteOperation, self).subscribeToEvents()

class GAPScanningEventPeriodicAdvSyncTransferReceivedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationObserver('GAPScanningEventPeriodicAdvSyncTransferReceivedIndication'), ]
        super(GAPScanningEventPeriodicAdvSyncTransferReceivedOperation, self).subscribeToEvents()

class GAPConnectionEventPathLossThresholdOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPathLossThresholdIndicationObserver('GAPConnectionEventPathLossThresholdIndication'), ]
        super(GAPConnectionEventPathLossThresholdOperation, self).subscribeToEvents()

class GAPConnectionEventTransmitPowerReportingOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventTransmitPowerReportingIndicationObserver('GAPConnectionEventTransmitPowerReportingIndication'), ]
        super(GAPConnectionEventTransmitPowerReportingOperation, self).subscribeToEvents()

class GAPConnectionEventEnhancedReadTransmitPowerLevelOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationObserver('GAPConnectionEventEnhancedReadTransmitPowerLevelIndication'), ]
        super(GAPConnectionEventEnhancedReadTransmitPowerLevelOperation, self).subscribeToEvents()

class GAPConnectionEventPathLossReportingParamsSetupCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPathLossReportingParamsSetupCompleteIndicationObserver('GAPConnectionEventPathLossReportingParamsSetupCompleteIndication'), ]
        super(GAPConnectionEventPathLossReportingParamsSetupCompleteOperation, self).subscribeToEvents()

class GAPConnectionEventPathLossReportingStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventPathLossReportingStateChangedIndicationObserver('GAPConnectionEventPathLossReportingStateChangedIndication'), ]
        super(GAPConnectionEventPathLossReportingStateChangedOperation, self).subscribeToEvents()

class GAPConnectionEventTransmitPowerReportingStateChangedOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventTransmitPowerReportingStateChangedIndicationObserver('GAPConnectionEventTransmitPowerReportingStateChangedIndication'), ]
        super(GAPConnectionEventTransmitPowerReportingStateChangedOperation, self).subscribeToEvents()

class GAPConnectionEventEattConnectionRequestOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEattConnectionRequestIndicationObserver('GAPConnectionEventEattConnectionRequestIndication'), ]
        super(GAPConnectionEventEattConnectionRequestOperation, self).subscribeToEvents()

class GAPConnectionEventEattConnectionCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEattConnectionCompleteIndicationObserver('GAPConnectionEventEattConnectionCompleteIndication'), ]
        super(GAPConnectionEventEattConnectionCompleteOperation, self).subscribeToEvents()

class GAPConnectionEventEattReconfigureResponseOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEattReconfigureResponseIndicationObserver('GAPConnectionEventEattReconfigureResponseIndication'), ]
        super(GAPConnectionEventEattReconfigureResponseOperation, self).subscribeToEvents()

class GAPConnectionEventEattBearerStatusNotificationOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPConnectionEventEattBearerStatusNotificationIndicationObserver('GAPConnectionEventEattBearerStatusNotificationIndication'), ]
        super(GAPConnectionEventEattBearerStatusNotificationOperation, self).subscribeToEvents()

class GAPGenericEventLeGenerateDhKeyCompleteOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGenericEventLeGenerateDhKeyCompleteIndicationObserver('GAPGenericEventLeGenerateDhKeyCompleteIndication'), ]
        super(GAPGenericEventLeGenerateDhKeyCompleteOperation, self).subscribeToEvents()


class GAPGetHostVersionOperation(FsciOperation):

    def subscribeToEvents(self):
        self.spec = None
        self.observers = [GAPGetHostVersionIndicationObserver('GAPGetHostVersionIndication'), ]
        super(GAPGetHostVersionOperation, self).subscribeToEvents()



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
