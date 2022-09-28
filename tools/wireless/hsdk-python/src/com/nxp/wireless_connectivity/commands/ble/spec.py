'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
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
        self.L2CAPCBRegisterLeCbCallbacksRequestFrame = self.InitL2CAPCBRegisterLeCbCallbacksRequest()
        self.L2CAPCBRegisterLePsmRequestFrame = self.InitL2CAPCBRegisterLePsmRequest()
        self.L2CAPCBDeregisterLePsmRequestFrame = self.InitL2CAPCBDeregisterLePsmRequest()
        self.L2CAPCBConnectLePsmRequestFrame = self.InitL2CAPCBConnectLePsmRequest()
        self.L2CAPCBDisconnectLeCbChannelRequestFrame = self.InitL2CAPCBDisconnectLeCbChannelRequest()
        self.L2CAPCBCancelConnectionRequestFrame = self.InitL2CAPCBCancelConnectionRequest()
        self.L2CAPCBSendLeCbDataRequestFrame = self.InitL2CAPCBSendLeCbDataRequest()
        self.L2CAPCBSendLeCreditRequestFrame = self.InitL2CAPCBSendLeCreditRequest()
        self.GATTInitRequestFrame = self.InitGATTInitRequest()
        self.GATTGetMtuRequestFrame = self.InitGATTGetMtuRequest()
        self.GATTClientInitRequestFrame = self.InitGATTClientInitRequest()
        self.GATTClientResetProcedureRequestFrame = self.InitGATTClientResetProcedureRequest()
        self.GATTClientRegisterProcedureCallbackRequestFrame = self.InitGATTClientRegisterProcedureCallbackRequest()
        self.GATTClientRegisterNotificationCallbackRequestFrame = self.InitGATTClientRegisterNotificationCallbackRequest()
        self.GATTClientRegisterIndicationCallbackRequestFrame = self.InitGATTClientRegisterIndicationCallbackRequest()
        self.GATTClientExchangeMtuRequestFrame = self.InitGATTClientExchangeMtuRequest()
        self.GATTClientDiscoverAllPrimaryServicesRequestFrame = self.InitGATTClientDiscoverAllPrimaryServicesRequest()
        self.GATTClientDiscoverPrimaryServicesByUuidRequestFrame = self.InitGATTClientDiscoverPrimaryServicesByUuidRequest()
        self.GATTClientFindIncludedServicesRequestFrame = self.InitGATTClientFindIncludedServicesRequest()
        self.GATTClientDiscoverAllCharacteristicsOfServiceRequestFrame = self.InitGATTClientDiscoverAllCharacteristicsOfServiceRequest()
        self.GATTClientDiscoverCharacteristicOfServiceByUuidRequestFrame = self.InitGATTClientDiscoverCharacteristicOfServiceByUuidRequest()
        self.GATTClientDiscoverAllCharacteristicDescriptorsRequestFrame = self.InitGATTClientDiscoverAllCharacteristicDescriptorsRequest()
        self.GATTClientReadCharacteristicValueRequestFrame = self.InitGATTClientReadCharacteristicValueRequest()
        self.GATTClientReadUsingCharacteristicUuidRequestFrame = self.InitGATTClientReadUsingCharacteristicUuidRequest()
        self.GATTClientReadMultipleCharacteristicValuesRequestFrame = self.InitGATTClientReadMultipleCharacteristicValuesRequest()
        self.GATTClientWriteCharacteristicValueRequestFrame = self.InitGATTClientWriteCharacteristicValueRequest()
        self.GATTClientReadCharacteristicDescriptorRequestFrame = self.InitGATTClientReadCharacteristicDescriptorRequest()
        self.GATTClientWriteCharacteristicDescriptorRequestFrame = self.InitGATTClientWriteCharacteristicDescriptorRequest()
        self.GATTServerInitRequestFrame = self.InitGATTServerInitRequest()
        self.GATTServerRegisterCallbackRequestFrame = self.InitGATTServerRegisterCallbackRequest()
        self.GATTServerRegisterHandlesForWriteNotificationsRequestFrame = self.InitGATTServerRegisterHandlesForWriteNotificationsRequest()
        self.GATTServerSendAttributeWrittenStatusRequestFrame = self.InitGATTServerSendAttributeWrittenStatusRequest()
        self.GATTServerSendNotificationRequestFrame = self.InitGATTServerSendNotificationRequest()
        self.GATTServerSendIndicationRequestFrame = self.InitGATTServerSendIndicationRequest()
        self.GATTServerSendInstantValueNotificationRequestFrame = self.InitGATTServerSendInstantValueNotificationRequest()
        self.GATTServerSendInstantValueIndicationRequestFrame = self.InitGATTServerSendInstantValueIndicationRequest()
        self.GATTServerRegisterHandlesForReadNotificationsRequestFrame = self.InitGATTServerRegisterHandlesForReadNotificationsRequest()
        self.GATTServerSendAttributeReadStatusRequestFrame = self.InitGATTServerSendAttributeReadStatusRequest()
        self.GATTServerRegisterUniqueHandlesForNotificationsRequestFrame = self.InitGATTServerRegisterUniqueHandlesForNotificationsRequest()
        self.GATTServerUnregisterHandlesForWriteNotificationsRequestFrame = self.InitGATTServerUnregisterHandlesForWriteNotificationsRequest()
        self.GATTServerUnregisterHandlesForReadNotificationsRequestFrame = self.InitGATTServerUnregisterHandlesForReadNotificationsRequest()
        self.GATTDBWriteAttributeRequestFrame = self.InitGATTDBWriteAttributeRequest()
        self.GATTDBReadAttributeRequestFrame = self.InitGATTDBReadAttributeRequest()
        self.GATTDBFindServiceHandleRequestFrame = self.InitGATTDBFindServiceHandleRequest()
        self.GATTDBFindCharValueHandleInServiceRequestFrame = self.InitGATTDBFindCharValueHandleInServiceRequest()
        self.GATTDBFindCccdHandleForCharValueHandleRequestFrame = self.InitGATTDBFindCccdHandleForCharValueHandleRequest()
        self.GATTDBFindDescriptorHandleForCharValueHandleRequestFrame = self.InitGATTDBFindDescriptorHandleForCharValueHandleRequest()
        self.GATTDBDynamicInitRequestFrame = self.InitGATTDBDynamicInitRequest()
        self.GATTDBDynamicReleaseDatabaseRequestFrame = self.InitGATTDBDynamicReleaseDatabaseRequest()
        self.GATTDBDynamicAddPrimaryServiceDeclarationRequestFrame = self.InitGATTDBDynamicAddPrimaryServiceDeclarationRequest()
        self.GATTDBDynamicAddSecondaryServiceDeclarationRequestFrame = self.InitGATTDBDynamicAddSecondaryServiceDeclarationRequest()
        self.GATTDBDynamicAddIncludeDeclarationRequestFrame = self.InitGATTDBDynamicAddIncludeDeclarationRequest()
        self.GATTDBDynamicAddCharacteristicDeclarationAndValueRequestFrame = self.InitGATTDBDynamicAddCharacteristicDeclarationAndValueRequest()
        self.GATTDBDynamicAddCharacteristicDescriptorRequestFrame = self.InitGATTDBDynamicAddCharacteristicDescriptorRequest()
        self.GATTDBDynamicAddCccdRequestFrame = self.InitGATTDBDynamicAddCccdRequest()
        self.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequestFrame = self.InitGATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest()
        self.GATTDBDynamicRemoveServiceRequestFrame = self.InitGATTDBDynamicRemoveServiceRequest()
        self.GATTDBDynamicRemoveCharacteristicRequestFrame = self.InitGATTDBDynamicRemoveCharacteristicRequest()
        self.GATTDBDynamicAddCharDescriptorWithUniqueValueRequestFrame = self.InitGATTDBDynamicAddCharDescriptorWithUniqueValueRequest()
        self.BLEHostInitializeRequestFrame = self.InitBLEHostInitializeRequest()
        self.GAPRegisterDeviceSecurityRequirementsRequestFrame = self.InitGAPRegisterDeviceSecurityRequirementsRequest()
        self.GAPSetAdvertisingParametersRequestFrame = self.InitGAPSetAdvertisingParametersRequest()
        self.GAPSetAdvertisingDataRequestFrame = self.InitGAPSetAdvertisingDataRequest()
        self.GAPStartAdvertisingRequestFrame = self.InitGAPStartAdvertisingRequest()
        self.GAPStopAdvertisingRequestFrame = self.InitGAPStopAdvertisingRequest()
        self.GAPAuthorizeRequestFrame = self.InitGAPAuthorizeRequest()
        self.GAPSaveCccdRequestFrame = self.InitGAPSaveCccdRequest()
        self.GAPCheckNotificationStatusRequestFrame = self.InitGAPCheckNotificationStatusRequest()
        self.GAPCheckIndicationStatusRequestFrame = self.InitGAPCheckIndicationStatusRequest()
        self.GAPPairRequestFrame = self.InitGAPPairRequest()
        self.GAPSendSlaveSecurityRequestRequestFrame = self.InitGAPSendSlaveSecurityRequestRequest()
        self.GAPEncryptLinkRequestFrame = self.InitGAPEncryptLinkRequest()
        self.GAPAcceptPairingRequestRequestFrame = self.InitGAPAcceptPairingRequestRequest()
        self.GAPRejectPairingRequestFrame = self.InitGAPRejectPairingRequest()
        self.GAPEnterPasskeyRequestFrame = self.InitGAPEnterPasskeyRequest()
        self.GAPProvideOobRequestFrame = self.InitGAPProvideOobRequest()
        self.GAPRejectPasskeyRequestRequestFrame = self.InitGAPRejectPasskeyRequestRequest()
        self.GAPSendSmpKeysRequestFrame = self.InitGAPSendSmpKeysRequest()
        self.GAPRejectKeyExchangeRequestRequestFrame = self.InitGAPRejectKeyExchangeRequestRequest()
        self.GAPProvideLongTermKeyRequestFrame = self.InitGAPProvideLongTermKeyRequest()
        self.GAPDenyLongTermKeyRequestFrame = self.InitGAPDenyLongTermKeyRequest()
        self.GAPLoadEncryptionInformationRequestFrame = self.InitGAPLoadEncryptionInformationRequest()
        self.GAPSetLocalPasskeyRequestFrame = self.InitGAPSetLocalPasskeyRequest()
        self.GAPStartScanningRequestFrame = self.InitGAPStartScanningRequest()
        self.GAPStopScanningRequestFrame = self.InitGAPStopScanningRequest()
        self.GAPConnectRequestFrame = self.InitGAPConnectRequest()
        self.GAPDisconnectRequestFrame = self.InitGAPDisconnectRequest()
        self.GAPSaveCustomPeerInformationRequestFrame = self.InitGAPSaveCustomPeerInformationRequest()
        self.GAPLoadCustomPeerInformationRequestFrame = self.InitGAPLoadCustomPeerInformationRequest()
        self.GAPCheckIfBondedRequestFrame = self.InitGAPCheckIfBondedRequest()
        self.GAPReadWhiteListSizeRequestFrame = self.InitGAPReadWhiteListSizeRequest()
        self.GAPClearWhiteListRequestFrame = self.InitGAPClearWhiteListRequest()
        self.GAPAddDeviceToWhiteListRequestFrame = self.InitGAPAddDeviceToWhiteListRequest()
        self.GAPRemoveDeviceFromWhiteListRequestFrame = self.InitGAPRemoveDeviceFromWhiteListRequest()
        self.GAPReadPublicDeviceAddressRequestFrame = self.InitGAPReadPublicDeviceAddressRequest()
        self.GAPCreateRandomDeviceAddressRequestFrame = self.InitGAPCreateRandomDeviceAddressRequest()
        self.GAPSaveDeviceNameRequestFrame = self.InitGAPSaveDeviceNameRequest()
        self.GAPGetBondedDevicesCountRequestFrame = self.InitGAPGetBondedDevicesCountRequest()
        self.GAPGetBondedDeviceNameRequestFrame = self.InitGAPGetBondedDeviceNameRequest()
        self.GAPRemoveBondRequestFrame = self.InitGAPRemoveBondRequest()
        self.GAPRemoveAllBondsRequestFrame = self.InitGAPRemoveAllBondsRequest()
        self.GAPReadRadioPowerLevelRequestFrame = self.InitGAPReadRadioPowerLevelRequest()
        self.GAPVerifyPrivateResolvableAddressRequestFrame = self.InitGAPVerifyPrivateResolvableAddressRequest()
        self.GAPSetRandomAddressRequestFrame = self.InitGAPSetRandomAddressRequest()
        self.GAPSetScanModeRequestFrame = self.InitGAPSetScanModeRequest()
        self.GAPSetDefaultPairingParametersRequestFrame = self.InitGAPSetDefaultPairingParametersRequest()
        self.GAPUpdateConnectionParametersRequestFrame = self.InitGAPUpdateConnectionParametersRequest()
        self.GAPEnableUpdateConnectionParametersRequestFrame = self.InitGAPEnableUpdateConnectionParametersRequest()
        self.GapUpdateLeDataLengthRequestFrame = self.InitGapUpdateLeDataLengthRequest()
        self.GAPEnableHostPrivacyRequestFrame = self.InitGAPEnableHostPrivacyRequest()
        self.GAPEnableControllerPrivacyRequestFrame = self.InitGAPEnableControllerPrivacyRequest()
        self.GAPLeScRegeneratePublicKeyRequestFrame = self.InitGAPLeScRegeneratePublicKeyRequest()
        self.GAPLeScValidateNumericValueRequestFrame = self.InitGAPLeScValidateNumericValueRequest()
        self.GAPLeScGetLocalOobDataRequestFrame = self.InitGAPLeScGetLocalOobDataRequest()
        self.GAPLeScSetPeerOobDataRequestFrame = self.InitGAPLeScSetPeerOobDataRequest()
        self.GAPLeScSendKeypressNotificationPrivacyRequestFrame = self.InitGAPLeScSendKeypressNotificationPrivacyRequest()
        self.GAPGetBondedDevicesIdentityInformationRequestFrame = self.InitGAPGetBondedDevicesIdentityInformationRequest()
        self.GAPSetTxPowerLevelRequestFrame = self.InitGAPSetTxPowerLevelRequest()
        self.GAPLeReadPhyRequestFrame = self.InitGAPLeReadPhyRequest()
        self.GAPLeSetPhyRequestFrame = self.InitGAPLeSetPhyRequest()
        self.GAPControllerEnhancedNotificationRequestFrame = self.InitGAPControllerEnhancedNotificationRequest()
        self.GAPLoadKeysRequestFrame = self.InitGAPLoadKeysRequest()
        self.GAPSaveKeysRequestFrame = self.InitGAPSaveKeysRequest()
        self.GAPSetChannelMapRequestFrame = self.InitGAPSetChannelMapRequest()
        self.GAPReadChannelMapRequestFrame = self.InitGAPReadChannelMapRequest()
        self.GAPSetPrivacyModeRequestFrame = self.InitGAPSetPrivacyModeRequest()
        self.FSCICPUResetRequestFrame = self.InitFSCICPUResetRequest()
        self.FSCIGetNumberOfFreeBuffersRequestFrame = self.InitFSCIGetNumberOfFreeBuffersRequest()
        self.FSCIAllowDeviceToSleepRequestFrame = self.InitFSCIAllowDeviceToSleepRequest()
        self.FSCIGetWakeupReasonRequestFrame = self.InitFSCIGetWakeupReasonRequest()
        self.FSCIGetNumberOfFreeBuffersResponseFrame = self.InitFSCIGetNumberOfFreeBuffersResponse()
        self.FSCIAckIndicationFrame = self.InitFSCIAckIndication()
        self.FSCIErrorIndicationFrame = self.InitFSCIErrorIndication()
        self.FSCIAllowDeviceToSleepConfirmFrame = self.InitFSCIAllowDeviceToSleepConfirm()
        self.FSCIWakeUpIndicationFrame = self.InitFSCIWakeUpIndication()
        self.FSCIGetWakeupReasonResponseFrame = self.InitFSCIGetWakeupReasonResponse()
        self.L2CAPCBConfirmFrame = self.InitL2CAPCBConfirm()
        self.L2CAPCBLePsmConnectionRequestIndicationFrame = self.InitL2CAPCBLePsmConnectionRequestIndication()
        self.L2CAPCBLePsmConnectionCompleteIndicationFrame = self.InitL2CAPCBLePsmConnectionCompleteIndication()
        self.L2CAPCBLePsmDisconnectNotificationIndicationFrame = self.InitL2CAPCBLePsmDisconnectNotificationIndication()
        self.L2CAPCBNoPeerCreditsIndicationFrame = self.InitL2CAPCBNoPeerCreditsIndication()
        self.L2CAPCBLocalCreditsNotificationIndicationFrame = self.InitL2CAPCBLocalCreditsNotificationIndication()
        self.L2CAPCBLeCbDataIndicationFrame = self.InitL2CAPCBLeCbDataIndication()
        self.L2CAPCBErrorIndicationFrame = self.InitL2CAPCBErrorIndication()
        self.GATTConfirmFrame = self.InitGATTConfirm()
        self.GATTGetMtuIndicationFrame = self.InitGATTGetMtuIndication()
        self.GATTClientProcedureExchangeMtuIndicationFrame = self.InitGATTClientProcedureExchangeMtuIndication()
        self.GATTClientProcedureDiscoverAllPrimaryServicesIndicationFrame = self.InitGATTClientProcedureDiscoverAllPrimaryServicesIndication()
        self.GATTClientProcedureDiscoverPrimaryServicesByUuidIndicationFrame = self.InitGATTClientProcedureDiscoverPrimaryServicesByUuidIndication()
        self.GATTClientProcedureFindIncludedServicesIndicationFrame = self.InitGATTClientProcedureFindIncludedServicesIndication()
        self.GATTClientProcedureDiscoverAllCharacteristicsIndicationFrame = self.InitGATTClientProcedureDiscoverAllCharacteristicsIndication()
        self.GATTClientProcedureDiscoverCharacteristicByUuidIndicationFrame = self.InitGATTClientProcedureDiscoverCharacteristicByUuidIndication()
        self.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndicationFrame = self.InitGATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication()
        self.GATTClientProcedureReadCharacteristicValueIndicationFrame = self.InitGATTClientProcedureReadCharacteristicValueIndication()
        self.GATTClientProcedureReadUsingCharacteristicUuidIndicationFrame = self.InitGATTClientProcedureReadUsingCharacteristicUuidIndication()
        self.GATTClientProcedureReadMultipleCharacteristicValuesIndicationFrame = self.InitGATTClientProcedureReadMultipleCharacteristicValuesIndication()
        self.GATTClientProcedureWriteCharacteristicValueIndicationFrame = self.InitGATTClientProcedureWriteCharacteristicValueIndication()
        self.GATTClientProcedureReadCharacteristicDescriptorIndicationFrame = self.InitGATTClientProcedureReadCharacteristicDescriptorIndication()
        self.GATTClientProcedureWriteCharacteristicDescriptorIndicationFrame = self.InitGATTClientProcedureWriteCharacteristicDescriptorIndication()
        self.GATTClientNotificationIndicationFrame = self.InitGATTClientNotificationIndication()
        self.GATTClientIndicationIndicationFrame = self.InitGATTClientIndicationIndication()
        self.GATTServerMtuChangedIndicationFrame = self.InitGATTServerMtuChangedIndication()
        self.GATTServerHandleValueConfirmationIndicationFrame = self.InitGATTServerHandleValueConfirmationIndication()
        self.GATTServerAttributeWrittenIndicationFrame = self.InitGATTServerAttributeWrittenIndication()
        self.GATTServerCharacteristicCccdWrittenIndicationFrame = self.InitGATTServerCharacteristicCccdWrittenIndication()
        self.GATTServerAttributeWrittenWithoutResponseIndicationFrame = self.InitGATTServerAttributeWrittenWithoutResponseIndication()
        self.GATTServerErrorIndicationFrame = self.InitGATTServerErrorIndication()
        self.GATTServerLongCharacteristicWrittenIndicationFrame = self.InitGATTServerLongCharacteristicWrittenIndication()
        self.GATTServerAttributeReadIndicationFrame = self.InitGATTServerAttributeReadIndication()
        self.GATTDBConfirmFrame = self.InitGATTDBConfirm()
        self.GATTDBReadAttributeIndicationFrame = self.InitGATTDBReadAttributeIndication()
        self.GATTDBFindServiceHandleIndicationFrame = self.InitGATTDBFindServiceHandleIndication()
        self.GATTDBFindCharValueHandleInServiceIndicationFrame = self.InitGATTDBFindCharValueHandleInServiceIndication()
        self.GATTDBFindCccdHandleForCharValueHandleIndicationFrame = self.InitGATTDBFindCccdHandleForCharValueHandleIndication()
        self.GATTDBFindDescriptorHandleForCharValueHandleIndicationFrame = self.InitGATTDBFindDescriptorHandleForCharValueHandleIndication()
        self.GATTDBDynamicAddPrimaryServiceDeclarationIndicationFrame = self.InitGATTDBDynamicAddPrimaryServiceDeclarationIndication()
        self.GATTDBDynamicAddSecondaryServiceDeclarationIndicationFrame = self.InitGATTDBDynamicAddSecondaryServiceDeclarationIndication()
        self.GATTDBDynamicAddIncludeDeclarationIndicationFrame = self.InitGATTDBDynamicAddIncludeDeclarationIndication()
        self.GATTDBDynamicAddCharacteristicDeclarationAndValueIndicationFrame = self.InitGATTDBDynamicAddCharacteristicDeclarationAndValueIndication()
        self.GATTDBDynamicAddCharacteristicDescriptorIndicationFrame = self.InitGATTDBDynamicAddCharacteristicDescriptorIndication()
        self.GATTDBDynamicAddCccdIndicationFrame = self.InitGATTDBDynamicAddCccdIndication()
        self.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndicationFrame = self.InitGATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication()
        self.GATTDBDynamicAddCharDescriptorWithUniqueValueIndicationFrame = self.InitGATTDBDynamicAddCharDescriptorWithUniqueValueIndication()
        self.GAPConfirmFrame = self.InitGAPConfirm()
        self.GAPCheckNotificationStatusIndicationFrame = self.InitGAPCheckNotificationStatusIndication()
        self.GAPCheckIndicationStatusIndicationFrame = self.InitGAPCheckIndicationStatusIndication()
        self.GAPLoadKeysIndicationFrame = self.InitGAPLoadKeysIndication()
        self.GAPLoadEncryptionInformationIndicationFrame = self.InitGAPLoadEncryptionInformationIndication()
        self.GAPLoadCustomPeerInformationIndicationFrame = self.InitGAPLoadCustomPeerInformationIndication()
        self.GAPCheckIfBondedIndicationFrame = self.InitGAPCheckIfBondedIndication()
        self.GAPGetBondedDevicesCountIndicationFrame = self.InitGAPGetBondedDevicesCountIndication()
        self.GAPGetBondedDeviceNameIndicationFrame = self.InitGAPGetBondedDeviceNameIndication()
        self.GAPGenericEventInitializationCompleteIndicationFrame = self.InitGAPGenericEventInitializationCompleteIndication()
        self.GAPGenericEventInternalErrorIndicationFrame = self.InitGAPGenericEventInternalErrorIndication()
        self.GAPGenericEventAdvertisingSetupFailedIndicationFrame = self.InitGAPGenericEventAdvertisingSetupFailedIndication()
        self.GAPGenericEventAdvertisingParametersSetupCompleteIndicationFrame = self.InitGAPGenericEventAdvertisingParametersSetupCompleteIndication()
        self.GAPGenericEventAdvertisingDataSetupCompleteIndicationFrame = self.InitGAPGenericEventAdvertisingDataSetupCompleteIndication()
        self.GAPGenericEventWhiteListSizeReadIndicationFrame = self.InitGAPGenericEventWhiteListSizeReadIndication()
        self.GAPGenericEventDeviceAddedToWhiteListIndicationFrame = self.InitGAPGenericEventDeviceAddedToWhiteListIndication()
        self.GAPGenericEventDeviceRemovedFromWhiteListIndicationFrame = self.InitGAPGenericEventDeviceRemovedFromWhiteListIndication()
        self.GAPGenericEventWhiteListClearedIndicationFrame = self.InitGAPGenericEventWhiteListClearedIndication()
        self.GAPGenericEventRandomAddressReadyIndicationFrame = self.InitGAPGenericEventRandomAddressReadyIndication()
        self.GAPGenericEventCreateConnectionCanceledIndicationFrame = self.InitGAPGenericEventCreateConnectionCanceledIndication()
        self.GAPGenericEventPublicAddressReadIndicationFrame = self.InitGAPGenericEventPublicAddressReadIndication()
        self.GAPGenericEventAdvTxPowerLevelReadIndicationFrame = self.InitGAPGenericEventAdvTxPowerLevelReadIndication()
        self.GAPGenericEventPrivateResolvableAddressVerifiedIndicationFrame = self.InitGAPGenericEventPrivateResolvableAddressVerifiedIndication()
        self.GAPGenericEventRandomAddressSetIndicationFrame = self.InitGAPGenericEventRandomAddressSetIndication()
        self.GAPAdvertisingEventStateChangedIndicationFrame = self.InitGAPAdvertisingEventStateChangedIndication()
        self.GAPAdvertisingEventCommandFailedIndicationFrame = self.InitGAPAdvertisingEventCommandFailedIndication()
        self.GAPScanningEventStateChangedIndicationFrame = self.InitGAPScanningEventStateChangedIndication()
        self.GAPScanningEventCommandFailedIndicationFrame = self.InitGAPScanningEventCommandFailedIndication()
        self.GAPScanningEventDeviceScannedIndicationFrame = self.InitGAPScanningEventDeviceScannedIndication()
        self.GAPConnectionEventConnectedIndicationFrame = self.InitGAPConnectionEventConnectedIndication()
        self.GAPConnectionEventPairingRequestIndicationFrame = self.InitGAPConnectionEventPairingRequestIndication()
        self.GAPConnectionEventSlaveSecurityRequestIndicationFrame = self.InitGAPConnectionEventSlaveSecurityRequestIndication()
        self.GAPConnectionEventPairingResponseIndicationFrame = self.InitGAPConnectionEventPairingResponseIndication()
        self.GAPConnectionEventAuthenticationRejectedIndicationFrame = self.InitGAPConnectionEventAuthenticationRejectedIndication()
        self.GAPConnectionEventPasskeyRequestIndicationFrame = self.InitGAPConnectionEventPasskeyRequestIndication()
        self.GAPConnectionEventOobRequestIndicationFrame = self.InitGAPConnectionEventOobRequestIndication()
        self.GAPConnectionEventPasskeyDisplayIndicationFrame = self.InitGAPConnectionEventPasskeyDisplayIndication()
        self.GAPConnectionEventKeyExchangeRequestIndicationFrame = self.InitGAPConnectionEventKeyExchangeRequestIndication()
        self.GAPConnectionEventKeysReceivedIndicationFrame = self.InitGAPConnectionEventKeysReceivedIndication()
        self.GAPConnectionEventLongTermKeyRequestIndicationFrame = self.InitGAPConnectionEventLongTermKeyRequestIndication()
        self.GAPConnectionEventEncryptionChangedIndicationFrame = self.InitGAPConnectionEventEncryptionChangedIndication()
        self.GAPConnectionEventPairingCompleteIndicationFrame = self.InitGAPConnectionEventPairingCompleteIndication()
        self.GAPConnectionEventDisconnectedIndicationFrame = self.InitGAPConnectionEventDisconnectedIndication()
        self.GAPConnectionEventRssiReadIndicationFrame = self.InitGAPConnectionEventRssiReadIndication()
        self.GAPConnectionEventTxPowerLevelReadIndicationFrame = self.InitGAPConnectionEventTxPowerLevelReadIndication()
        self.GAPConnectionEventPowerReadFailureIndicationFrame = self.InitGAPConnectionEventPowerReadFailureIndication()
        self.GAPConnectionEventParameterUpdateRequestIndicationFrame = self.InitGAPConnectionEventParameterUpdateRequestIndication()
        self.GAPConnectionEventParameterUpdateCompleteIndicationFrame = self.InitGAPConnectionEventParameterUpdateCompleteIndication()
        self.GAPConnectionEventLeDataLengthChangedIndicationFrame = self.InitGAPConnectionEventLeDataLengthChangedIndication()
        self.GAPConnectionEventLeScOobDataRequestIndicationFrame = self.InitGAPConnectionEventLeScOobDataRequestIndication()
        self.GAPConnectionEventLeScDisplayNumericValueIndicationFrame = self.InitGAPConnectionEventLeScDisplayNumericValueIndication()
        self.GAPConnectionEventLeScKeypressNotificationIndicationFrame = self.InitGAPConnectionEventLeScKeypressNotificationIndication()
        self.GAPLeScPublicKeyRegeneratedIndicationFrame = self.InitGAPLeScPublicKeyRegeneratedIndication()
        self.GAPGenericEventLeScLocalOobDataIndicationFrame = self.InitGAPGenericEventLeScLocalOobDataIndication()
        self.GAPGenericEventHostPrivacyStateChangedIndicationFrame = self.InitGAPGenericEventHostPrivacyStateChangedIndication()
        self.GAPGenericEventControllerPrivacyStateChangedIndicationFrame = self.InitGAPGenericEventControllerPrivacyStateChangedIndication()
        self.GAPGenericEventTxPowerLevelSetCompleteIndicationFrame = self.InitGAPGenericEventTxPowerLevelSetCompleteIndication()
        self.GAPGenericEventLePhyEventIndicationFrame = self.InitGAPGenericEventLePhyEventIndication()
        self.GAPGetBondedDevicesIdentityInformationIndicationFrame = self.InitGAPGetBondedDevicesIdentityInformationIndication()
        self.GAPControllerNotificationIndicationFrame = self.InitGAPControllerNotificationIndication()
        self.GAPBondCreatedIndicationFrame = self.InitGAPBondCreatedIndication()
        self.GAPGenericEventChannelMapSetIndicationFrame = self.InitGAPGenericEventChannelMapSetIndication()
        self.GAPConnectionEventChannelMapReadIndicationFrame = self.InitGAPConnectionEventChannelMapReadIndication()
        self.GAPConnectionEventChannelMapReadFailureIndicationFrame = self.InitGAPConnectionEventChannelMapReadFailureIndication()
        self.GAPConnectionEventChannelSelectionAlgorithm2IndicationFrame = self.InitGAPConnectionEventChannelSelectionAlgorithm2Indication()
        self.GAPGenericEventTxEntryAvailableIndicationFrame = self.InitGAPGenericEventTxEntryAvailableIndication()


    def InitL2CAPCBRegisterLeCbCallbacksRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x42, 0x01, cmdParams)

    def InitL2CAPCBRegisterLePsmRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        LePsmMtu = FsciParameter("LePsmMtu", 2)
        cmdParams.append(LePsmMtu)
        return FsciFrameDescription(0x42, 0x02, cmdParams)

    def InitL2CAPCBDeregisterLePsmRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        return FsciFrameDescription(0x42, 0x03, cmdParams)

    def InitL2CAPCBConnectLePsmRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        InitialCredits = FsciParameter("InitialCredits", 2)
        cmdParams.append(InitialCredits)
        return FsciFrameDescription(0x42, 0x04, cmdParams)

    def InitL2CAPCBDisconnectLeCbChannelRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ChannelId = FsciParameter("ChannelId", 2)
        cmdParams.append(ChannelId)
        return FsciFrameDescription(0x42, 0x05, cmdParams)

    def InitL2CAPCBCancelConnectionRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RefuseReason = FsciParameter("RefuseReason", 2)
        cmdParams.append(RefuseReason)
        return FsciFrameDescription(0x42, 0x06, cmdParams)

    def InitL2CAPCBSendLeCbDataRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ChannelId = FsciParameter("ChannelId", 2)
        cmdParams.append(ChannelId)
        PacketLength = FsciParameter("PacketLength", 2)
        cmdParams.append(PacketLength)
        Packet = FsciParameter("Packet", 1, PacketLength)
        cmdParams.append(Packet)
        return FsciFrameDescription(0x42, 0x07, cmdParams)

    def InitL2CAPCBSendLeCreditRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ChannelId = FsciParameter("ChannelId", 2)
        cmdParams.append(ChannelId)
        Credits = FsciParameter("Credits", 2)
        cmdParams.append(Credits)
        return FsciFrameDescription(0x42, 0x08, cmdParams)

    def InitGATTInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x01, cmdParams)

    def InitGATTGetMtuRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x45, 0x02, cmdParams)

    def InitGATTClientInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x03, cmdParams)

    def InitGATTClientResetProcedureRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x04, cmdParams)

    def InitGATTClientRegisterProcedureCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x05, cmdParams)

    def InitGATTClientRegisterNotificationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x06, cmdParams)

    def InitGATTClientRegisterIndicationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x07, cmdParams)

    def InitGATTClientExchangeMtuRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Mtu = FsciParameter("Mtu", 2)
        cmdParams.append(Mtu)
        return FsciFrameDescription(0x45, 0x08, cmdParams)

    def InitGATTClientDiscoverAllPrimaryServicesRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        MaxNbOfServices = FsciParameter("MaxNbOfServices", 1)
        cmdParams.append(MaxNbOfServices)
        return FsciFrameDescription(0x45, 0x09, cmdParams)

    def InitGATTClientDiscoverPrimaryServicesByUuidRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        MaxNbOfServices = FsciParameter("MaxNbOfServices", 1)
        cmdParams.append(MaxNbOfServices)
        return FsciFrameDescription(0x45, 0x0A, cmdParams)

    def InitGATTClientFindIncludedServicesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x0B, cmdParams)

    def InitGATTClientDiscoverAllCharacteristicsOfServiceRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x0C, cmdParams)

    def InitGATTClientDiscoverCharacteristicOfServiceByUuidRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x0D, cmdParams)

    def InitGATTClientDiscoverAllCharacteristicDescriptorsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x0E, cmdParams)

    def InitGATTClientReadCharacteristicValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x0F, cmdParams)

    def InitGATTClientReadUsingCharacteristicUuidRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x10, cmdParams)

    def InitGATTClientReadMultipleCharacteristicValuesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x11, cmdParams)

    def InitGATTClientWriteCharacteristicValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x12, cmdParams)

    def InitGATTClientReadCharacteristicDescriptorRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Descriptor_Handle = FsciParameter("Descriptor_Handle", 2)
        cmdParams.append(Descriptor_Handle)
        Descriptor_UuidType = FsciParameter("Descriptor_UuidType", 1)
        cmdParams.append(Descriptor_UuidType)
        Descriptor_Uuiddict = {}
        currentList = []
        Descriptor_UuidUuid16Bits = FsciParameter("Descriptor_UuidUuid16Bits", 2)
        currentList.append(Descriptor_UuidUuid16Bits)
        Descriptor_Uuiddict[0x01] = currentList
        currentList = []
        Descriptor_UuidUuid128Bits = FsciParameter("Descriptor_UuidUuid128Bits", 16)
        currentList.append(Descriptor_UuidUuid128Bits)
        Descriptor_Uuiddict[0x02] = currentList
        currentList = []
        Descriptor_UuidUuid32Bits = FsciParameter("Descriptor_UuidUuid32Bits", 4)
        currentList.append(Descriptor_UuidUuid32Bits)
        Descriptor_Uuiddict[0x03] = currentList
        Descriptor_Uuid = FsciParameter("Descriptor_Uuid", 1, Descriptor_UuidType, Descriptor_Uuiddict)
        cmdParams.append(Descriptor_Uuid)
        Descriptor_ValueLength = FsciParameter("Descriptor_ValueLength", 2)
        cmdParams.append(Descriptor_ValueLength)
        Descriptor_MaxValueLength = FsciParameter("Descriptor_MaxValueLength", 2)
        cmdParams.append(Descriptor_MaxValueLength)
        Descriptor_Value = FsciParameter("Descriptor_Value", 1, Descriptor_ValueLength)
        cmdParams.append(Descriptor_Value)
        MaxReadBytes = FsciParameter("MaxReadBytes", 2)
        cmdParams.append(MaxReadBytes)
        return FsciFrameDescription(0x45, 0x13, cmdParams)

    def InitGATTClientWriteCharacteristicDescriptorRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Descriptor_Handle = FsciParameter("Descriptor_Handle", 2)
        cmdParams.append(Descriptor_Handle)
        Descriptor_UuidType = FsciParameter("Descriptor_UuidType", 1)
        cmdParams.append(Descriptor_UuidType)
        Descriptor_Uuiddict = {}
        currentList = []
        Descriptor_UuidUuid16Bits = FsciParameter("Descriptor_UuidUuid16Bits", 2)
        currentList.append(Descriptor_UuidUuid16Bits)
        Descriptor_Uuiddict[0x01] = currentList
        currentList = []
        Descriptor_UuidUuid128Bits = FsciParameter("Descriptor_UuidUuid128Bits", 16)
        currentList.append(Descriptor_UuidUuid128Bits)
        Descriptor_Uuiddict[0x02] = currentList
        currentList = []
        Descriptor_UuidUuid32Bits = FsciParameter("Descriptor_UuidUuid32Bits", 4)
        currentList.append(Descriptor_UuidUuid32Bits)
        Descriptor_Uuiddict[0x03] = currentList
        Descriptor_Uuid = FsciParameter("Descriptor_Uuid", 1, Descriptor_UuidType, Descriptor_Uuiddict)
        cmdParams.append(Descriptor_Uuid)
        Descriptor_ValueLength = FsciParameter("Descriptor_ValueLength", 2)
        cmdParams.append(Descriptor_ValueLength)
        Descriptor_MaxValueLength = FsciParameter("Descriptor_MaxValueLength", 2)
        cmdParams.append(Descriptor_MaxValueLength)
        Descriptor_Value = FsciParameter("Descriptor_Value", 1, Descriptor_ValueLength)
        cmdParams.append(Descriptor_Value)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x14, cmdParams)

    def InitGATTServerInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x15, cmdParams)

    def InitGATTServerRegisterCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x16, cmdParams)

    def InitGATTServerRegisterHandlesForWriteNotificationsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x17, cmdParams)

    def InitGATTServerSendAttributeWrittenStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        AttributeHandle = FsciParameter("AttributeHandle", 2)
        cmdParams.append(AttributeHandle)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0x45, 0x18, cmdParams)

    def InitGATTServerSendNotificationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x45, 0x19, cmdParams)

    def InitGATTServerSendIndicationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x45, 0x1A, cmdParams)

    def InitGATTServerSendInstantValueNotificationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x1B, cmdParams)

    def InitGATTServerSendInstantValueIndicationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x1C, cmdParams)

    def InitGATTServerRegisterHandlesForReadNotificationsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x1D, cmdParams)

    def InitGATTServerSendAttributeReadStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        AttributeHandle = FsciParameter("AttributeHandle", 2)
        cmdParams.append(AttributeHandle)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0x45, 0x1E, cmdParams)

    def InitGATTServerRegisterUniqueHandlesForNotificationsRequest(self):
        cmdParams = []
        bWrite = FsciParameter("bWrite", 1)
        cmdParams.append(bWrite)
        bRead = FsciParameter("bRead", 1)
        cmdParams.append(bRead)
        return FsciFrameDescription(0x45, 0x1F, cmdParams)

    def InitGATTServerUnregisterHandlesForWriteNotificationsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x20, cmdParams)

    def InitGATTServerUnregisterHandlesForReadNotificationsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x21, cmdParams)

    def InitGATTDBWriteAttributeRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x46, 0x02, cmdParams)

    def InitGATTDBReadAttributeRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        MaxBytes = FsciParameter("MaxBytes", 2)
        cmdParams.append(MaxBytes)
        return FsciFrameDescription(0x46, 0x03, cmdParams)

    def InitGATTDBFindServiceHandleRequest(self):
        cmdParams = []
        StartHandle = FsciParameter("StartHandle", 2)
        cmdParams.append(StartHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x04, cmdParams)

    def InitGATTDBFindCharValueHandleInServiceRequest(self):
        cmdParams = []
        ServiceHandle = FsciParameter("ServiceHandle", 2)
        cmdParams.append(ServiceHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x05, cmdParams)

    def InitGATTDBFindCccdHandleForCharValueHandleRequest(self):
        cmdParams = []
        CharValueHandle = FsciParameter("CharValueHandle", 2)
        cmdParams.append(CharValueHandle)
        return FsciFrameDescription(0x46, 0x06, cmdParams)

    def InitGATTDBFindDescriptorHandleForCharValueHandleRequest(self):
        cmdParams = []
        CharValueHandle = FsciParameter("CharValueHandle", 2)
        cmdParams.append(CharValueHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x07, cmdParams)

    def InitGATTDBDynamicInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x08, cmdParams)

    def InitGATTDBDynamicReleaseDatabaseRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x09, cmdParams)

    def InitGATTDBDynamicAddPrimaryServiceDeclarationRequest(self):
        cmdParams = []
        DesiredHandle = FsciParameter("DesiredHandle", 2)
        cmdParams.append(DesiredHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x0A, cmdParams)

    def InitGATTDBDynamicAddSecondaryServiceDeclarationRequest(self):
        cmdParams = []
        DesiredHandle = FsciParameter("DesiredHandle", 2)
        cmdParams.append(DesiredHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x0B, cmdParams)

    def InitGATTDBDynamicAddIncludeDeclarationRequest(self):
        cmdParams = []
        IncludedServiceHandle = FsciParameter("IncludedServiceHandle", 2)
        cmdParams.append(IncludedServiceHandle)
        EndGroupHandle = FsciParameter("EndGroupHandle", 2)
        cmdParams.append(EndGroupHandle)
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        return FsciFrameDescription(0x46, 0x0C, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationAndValueRequest(self):
        cmdParams = []
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        CharacteristicProperties = FsciParameter("CharacteristicProperties", 1)
        cmdParams.append(CharacteristicProperties)
        MaxValueLength = FsciParameter("MaxValueLength", 2)
        cmdParams.append(MaxValueLength)
        InitialValueLength = FsciParameter("InitialValueLength", 2)
        cmdParams.append(InitialValueLength)
        InitialValue = FsciParameter("InitialValue", 1, InitialValueLength)
        cmdParams.append(InitialValue)
        ValueAccessPermissions = FsciParameter("ValueAccessPermissions", 1)
        cmdParams.append(ValueAccessPermissions)
        return FsciFrameDescription(0x46, 0x0D, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDescriptorRequest(self):
        cmdParams = []
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        DescriptorValueLength = FsciParameter("DescriptorValueLength", 2)
        cmdParams.append(DescriptorValueLength)
        Value = FsciParameter("Value", 1, DescriptorValueLength)
        cmdParams.append(Value)
        DescriptorAccessPermissions = FsciParameter("DescriptorAccessPermissions", 1)
        cmdParams.append(DescriptorAccessPermissions)
        return FsciFrameDescription(0x46, 0x0E, cmdParams)

    def InitGATTDBDynamicAddCccdRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x0F, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(self):
        cmdParams = []
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        CharacteristicProperties = FsciParameter("CharacteristicProperties", 1)
        cmdParams.append(CharacteristicProperties)
        ValueAccessPermissions = FsciParameter("ValueAccessPermissions", 1)
        cmdParams.append(ValueAccessPermissions)
        return FsciFrameDescription(0x46, 0x10, cmdParams)

    def InitGATTDBDynamicRemoveServiceRequest(self):
        cmdParams = []
        ServiceHandle = FsciParameter("ServiceHandle", 2)
        cmdParams.append(ServiceHandle)
        return FsciFrameDescription(0x46, 0x11, cmdParams)

    def InitGATTDBDynamicRemoveCharacteristicRequest(self):
        cmdParams = []
        CharacteristicHandle = FsciParameter("CharacteristicHandle", 2)
        cmdParams.append(CharacteristicHandle)
        return FsciFrameDescription(0x46, 0x12, cmdParams)

    def InitGATTDBDynamicAddCharDescriptorWithUniqueValueRequest(self):
        cmdParams = []
        UuidType = FsciParameter("UuidType", 1)
        cmdParams.append(UuidType)
        Uuiddict = {}
        currentList = []
        UuidUuid16Bits = FsciParameter("UuidUuid16Bits", 2)
        currentList.append(UuidUuid16Bits)
        Uuiddict[0x01] = currentList
        currentList = []
        UuidUuid128Bits = FsciParameter("UuidUuid128Bits", 16)
        currentList.append(UuidUuid128Bits)
        Uuiddict[0x02] = currentList
        currentList = []
        UuidUuid32Bits = FsciParameter("UuidUuid32Bits", 4)
        currentList.append(UuidUuid32Bits)
        Uuiddict[0x03] = currentList
        Uuid = FsciParameter("Uuid", 1, UuidType, Uuiddict)
        cmdParams.append(Uuid)
        DescriptorAccessPermissions = FsciParameter("DescriptorAccessPermissions", 1)
        cmdParams.append(DescriptorAccessPermissions)
        return FsciFrameDescription(0x46, 0x13, cmdParams)

    def InitBLEHostInitializeRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x01, cmdParams)

    def InitGAPRegisterDeviceSecurityRequirementsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x02, cmdParams)

    def InitGAPSetAdvertisingParametersRequest(self):
        cmdParams = []
        AdvertisingParameters_MinInterval = FsciParameter("AdvertisingParameters_MinInterval", 2)
        cmdParams.append(AdvertisingParameters_MinInterval)
        AdvertisingParameters_MaxInterval = FsciParameter("AdvertisingParameters_MaxInterval", 2)
        cmdParams.append(AdvertisingParameters_MaxInterval)
        AdvertisingParameters_AdvertisingType = FsciParameter("AdvertisingParameters_AdvertisingType", 1)
        cmdParams.append(AdvertisingParameters_AdvertisingType)
        AdvertisingParameters_OwnAddressType = FsciParameter("AdvertisingParameters_OwnAddressType", 1)
        cmdParams.append(AdvertisingParameters_OwnAddressType)
        AdvertisingParameters_PeerAddressType = FsciParameter("AdvertisingParameters_PeerAddressType", 1)
        cmdParams.append(AdvertisingParameters_PeerAddressType)
        AdvertisingParameters_PeerAddress = FsciParameter("AdvertisingParameters_PeerAddress", 6)
        cmdParams.append(AdvertisingParameters_PeerAddress)
        AdvertisingParameters_ChannelMap = FsciParameter("AdvertisingParameters_ChannelMap", 1)
        cmdParams.append(AdvertisingParameters_ChannelMap)
        AdvertisingParameters_FilterPolicy = FsciParameter("AdvertisingParameters_FilterPolicy", 1)
        cmdParams.append(AdvertisingParameters_FilterPolicy)
        return FsciFrameDescription(0x48, 0x03, cmdParams)

    def InitGAPSetAdvertisingDataRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x04, cmdParams)

    def InitGAPStartAdvertisingRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x05, cmdParams)

    def InitGAPStopAdvertisingRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x06, cmdParams)

    def InitGAPAuthorizeRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        Access = FsciParameter("Access", 1)
        cmdParams.append(Access)
        return FsciFrameDescription(0x48, 0x07, cmdParams)

    def InitGAPSaveCccdRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        Cccd = FsciParameter("Cccd", 1)
        cmdParams.append(Cccd)
        return FsciFrameDescription(0x48, 0x08, cmdParams)

    def InitGAPCheckNotificationStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x09, cmdParams)

    def InitGAPCheckIndicationStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x0A, cmdParams)

    def InitGAPPairRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingParameters_WithBonding = FsciParameter("PairingParameters_WithBonding", 1)
        cmdParams.append(PairingParameters_WithBonding)
        PairingParameters_SecurityModeAndLevel = FsciParameter("PairingParameters_SecurityModeAndLevel", 1)
        cmdParams.append(PairingParameters_SecurityModeAndLevel)
        PairingParameters_MaxEncryptionKeySize = FsciParameter("PairingParameters_MaxEncryptionKeySize", 1)
        cmdParams.append(PairingParameters_MaxEncryptionKeySize)
        PairingParameters_LocalIoCapabilities = FsciParameter("PairingParameters_LocalIoCapabilities", 1)
        cmdParams.append(PairingParameters_LocalIoCapabilities)
        PairingParameters_OobAvailable = FsciParameter("PairingParameters_OobAvailable", 1)
        cmdParams.append(PairingParameters_OobAvailable)
        PairingParameters_CentralKeys = FsciParameter("PairingParameters_CentralKeys", 1)
        cmdParams.append(PairingParameters_CentralKeys)
        PairingParameters_PeripheralKeys = FsciParameter("PairingParameters_PeripheralKeys", 1)
        cmdParams.append(PairingParameters_PeripheralKeys)
        PairingParameters_LeSecureConnectionSupported = FsciParameter("PairingParameters_LeSecureConnectionSupported", 1)
        cmdParams.append(PairingParameters_LeSecureConnectionSupported)
        PairingParameters_UseKeypressNotifications = FsciParameter("PairingParameters_UseKeypressNotifications", 1)
        cmdParams.append(PairingParameters_UseKeypressNotifications)
        return FsciFrameDescription(0x48, 0x0C, cmdParams)

    def InitGAPSendSlaveSecurityRequestRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingParameters_WithBonding = FsciParameter("PairingParameters_WithBonding", 1)
        cmdParams.append(PairingParameters_WithBonding)
        PairingParameters_SecurityModeAndLevel = FsciParameter("PairingParameters_SecurityModeAndLevel", 1)
        cmdParams.append(PairingParameters_SecurityModeAndLevel)
        PairingParameters_MaxEncryptionKeySize = FsciParameter("PairingParameters_MaxEncryptionKeySize", 1)
        cmdParams.append(PairingParameters_MaxEncryptionKeySize)
        PairingParameters_LocalIoCapabilities = FsciParameter("PairingParameters_LocalIoCapabilities", 1)
        cmdParams.append(PairingParameters_LocalIoCapabilities)
        PairingParameters_OobAvailable = FsciParameter("PairingParameters_OobAvailable", 1)
        cmdParams.append(PairingParameters_OobAvailable)
        PairingParameters_CentralKeys = FsciParameter("PairingParameters_CentralKeys", 1)
        cmdParams.append(PairingParameters_CentralKeys)
        PairingParameters_PeripheralKeys = FsciParameter("PairingParameters_PeripheralKeys", 1)
        cmdParams.append(PairingParameters_PeripheralKeys)
        PairingParameters_LeSecureConnectionSupported = FsciParameter("PairingParameters_LeSecureConnectionSupported", 1)
        cmdParams.append(PairingParameters_LeSecureConnectionSupported)
        PairingParameters_UseKeypressNotifications = FsciParameter("PairingParameters_UseKeypressNotifications", 1)
        cmdParams.append(PairingParameters_UseKeypressNotifications)
        return FsciFrameDescription(0x48, 0x0D, cmdParams)

    def InitGAPEncryptLinkRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x0E, cmdParams)

    def InitGAPAcceptPairingRequestRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingParameters_WithBonding = FsciParameter("PairingParameters_WithBonding", 1)
        cmdParams.append(PairingParameters_WithBonding)
        PairingParameters_SecurityModeAndLevel = FsciParameter("PairingParameters_SecurityModeAndLevel", 1)
        cmdParams.append(PairingParameters_SecurityModeAndLevel)
        PairingParameters_MaxEncryptionKeySize = FsciParameter("PairingParameters_MaxEncryptionKeySize", 1)
        cmdParams.append(PairingParameters_MaxEncryptionKeySize)
        PairingParameters_LocalIoCapabilities = FsciParameter("PairingParameters_LocalIoCapabilities", 1)
        cmdParams.append(PairingParameters_LocalIoCapabilities)
        PairingParameters_OobAvailable = FsciParameter("PairingParameters_OobAvailable", 1)
        cmdParams.append(PairingParameters_OobAvailable)
        PairingParameters_CentralKeys = FsciParameter("PairingParameters_CentralKeys", 1)
        cmdParams.append(PairingParameters_CentralKeys)
        PairingParameters_PeripheralKeys = FsciParameter("PairingParameters_PeripheralKeys", 1)
        cmdParams.append(PairingParameters_PeripheralKeys)
        PairingParameters_LeSecureConnectionSupported = FsciParameter("PairingParameters_LeSecureConnectionSupported", 1)
        cmdParams.append(PairingParameters_LeSecureConnectionSupported)
        PairingParameters_UseKeypressNotifications = FsciParameter("PairingParameters_UseKeypressNotifications", 1)
        cmdParams.append(PairingParameters_UseKeypressNotifications)
        return FsciFrameDescription(0x48, 0x0F, cmdParams)

    def InitGAPRejectPairingRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Reason = FsciParameter("Reason", 1)
        cmdParams.append(Reason)
        return FsciFrameDescription(0x48, 0x10, cmdParams)

    def InitGAPEnterPasskeyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Passkey = FsciParameter("Passkey", 4)
        cmdParams.append(Passkey)
        return FsciFrameDescription(0x48, 0x11, cmdParams)

    def InitGAPProvideOobRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Oob = FsciParameter("Oob", 16)
        cmdParams.append(Oob)
        return FsciFrameDescription(0x48, 0x12, cmdParams)

    def InitGAPRejectPasskeyRequestRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x13, cmdParams)

    def InitGAPSendSmpKeysRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x14, cmdParams)

    def InitGAPRejectKeyExchangeRequestRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x15, cmdParams)

    def InitGAPProvideLongTermKeyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        LtkSize = FsciParameter("LtkSize", 1)
        cmdParams.append(LtkSize)
        Ltk = FsciParameter("Ltk", 1, LtkSize)
        cmdParams.append(Ltk)
        return FsciFrameDescription(0x48, 0x16, cmdParams)

    def InitGAPDenyLongTermKeyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x17, cmdParams)

    def InitGAPLoadEncryptionInformationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x18, cmdParams)

    def InitGAPSetLocalPasskeyRequest(self):
        cmdParams = []
        Passkey = FsciParameter("Passkey", 4)
        cmdParams.append(Passkey)
        return FsciFrameDescription(0x48, 0x19, cmdParams)

    def InitGAPStartScanningRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x1A, cmdParams)

    def InitGAPStopScanningRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x1B, cmdParams)

    def InitGAPConnectRequest(self):
        cmdParams = []
        CreateConnectionParameters_ScanInterval = FsciParameter("CreateConnectionParameters_ScanInterval", 2)
        cmdParams.append(CreateConnectionParameters_ScanInterval)
        CreateConnectionParameters_ScanWindow = FsciParameter("CreateConnectionParameters_ScanWindow", 2)
        cmdParams.append(CreateConnectionParameters_ScanWindow)
        CreateConnectionParameters_FilterPolicy = FsciParameter("CreateConnectionParameters_FilterPolicy", 1)
        cmdParams.append(CreateConnectionParameters_FilterPolicy)
        CreateConnectionParameters_OwnAddressType = FsciParameter("CreateConnectionParameters_OwnAddressType", 1)
        cmdParams.append(CreateConnectionParameters_OwnAddressType)
        CreateConnectionParameters_PeerAddressType = FsciParameter("CreateConnectionParameters_PeerAddressType", 1)
        cmdParams.append(CreateConnectionParameters_PeerAddressType)
        CreateConnectionParameters_PeerAddress = FsciParameter("CreateConnectionParameters_PeerAddress", 6)
        cmdParams.append(CreateConnectionParameters_PeerAddress)
        CreateConnectionParameters_ConnIntervalMin = FsciParameter("CreateConnectionParameters_ConnIntervalMin", 2)
        cmdParams.append(CreateConnectionParameters_ConnIntervalMin)
        CreateConnectionParameters_ConnIntervalMax = FsciParameter("CreateConnectionParameters_ConnIntervalMax", 2)
        cmdParams.append(CreateConnectionParameters_ConnIntervalMax)
        CreateConnectionParameters_ConnLatency = FsciParameter("CreateConnectionParameters_ConnLatency", 2)
        cmdParams.append(CreateConnectionParameters_ConnLatency)
        CreateConnectionParameters_SupervisionTimeout = FsciParameter("CreateConnectionParameters_SupervisionTimeout", 2)
        cmdParams.append(CreateConnectionParameters_SupervisionTimeout)
        CreateConnectionParameters_ConnEventLengthMin = FsciParameter("CreateConnectionParameters_ConnEventLengthMin", 2)
        cmdParams.append(CreateConnectionParameters_ConnEventLengthMin)
        CreateConnectionParameters_ConnEventLengthMax = FsciParameter("CreateConnectionParameters_ConnEventLengthMax", 2)
        cmdParams.append(CreateConnectionParameters_ConnEventLengthMax)
        CreateConnectionParameters_usePeerIdentityAddress = FsciParameter("CreateConnectionParameters_usePeerIdentityAddress", 1)
        cmdParams.append(CreateConnectionParameters_usePeerIdentityAddress)
        CreateConnectionParameters_Initiating_PHYs = FsciParameter("CreateConnectionParameters_Initiating_PHYs", 1)
        cmdParams.append(CreateConnectionParameters_Initiating_PHYs)
        return FsciFrameDescription(0x48, 0x1C, cmdParams)

    def InitGAPDisconnectRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x1D, cmdParams)

    def InitGAPSaveCustomPeerInformationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Offset = FsciParameter("Offset", 2)
        cmdParams.append(Offset)
        InfoSize = FsciParameter("InfoSize", 2)
        cmdParams.append(InfoSize)
        Info = FsciParameter("Info", 1, InfoSize)
        cmdParams.append(Info)
        return FsciFrameDescription(0x48, 0x1E, cmdParams)

    def InitGAPLoadCustomPeerInformationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Offset = FsciParameter("Offset", 2)
        cmdParams.append(Offset)
        InfoSize = FsciParameter("InfoSize", 2)
        cmdParams.append(InfoSize)
        return FsciFrameDescription(0x48, 0x1F, cmdParams)

    def InitGAPCheckIfBondedRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x20, cmdParams)

    def InitGAPReadWhiteListSizeRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x21, cmdParams)

    def InitGAPClearWhiteListRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x22, cmdParams)

    def InitGAPAddDeviceToWhiteListRequest(self):
        cmdParams = []
        AddressType = FsciParameter("AddressType", 1)
        cmdParams.append(AddressType)
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x23, cmdParams)

    def InitGAPRemoveDeviceFromWhiteListRequest(self):
        cmdParams = []
        AddressType = FsciParameter("AddressType", 1)
        cmdParams.append(AddressType)
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x24, cmdParams)

    def InitGAPReadPublicDeviceAddressRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x25, cmdParams)

    def InitGAPCreateRandomDeviceAddressRequest(self):
        cmdParams = []
        IrkIncluded = FsciParameter("IrkIncluded", 1)
        cmdParams.append(IrkIncluded)
        Irk = FsciParameter("Irk", 16, IrkIncluded)
        cmdParams.append(Irk)
        RandomPartIncluded = FsciParameter("RandomPartIncluded", 1, IrkIncluded)
        cmdParams.append(RandomPartIncluded)
        RandomPart = FsciParameter("RandomPart", 3, RandomPartIncluded)
        cmdParams.append(RandomPart)
        return FsciFrameDescription(0x48, 0x26, cmdParams)

    def InitGAPSaveDeviceNameRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        NameSize = FsciParameter("NameSize", 1)
        cmdParams.append(NameSize)
        Name = FsciParameter("Name", 1, NameSize)
        cmdParams.append(Name)
        return FsciFrameDescription(0x48, 0x27, cmdParams)

    def InitGAPGetBondedDevicesCountRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x28, cmdParams)

    def InitGAPGetBondedDeviceNameRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        MaxNameSize = FsciParameter("MaxNameSize", 1)
        cmdParams.append(MaxNameSize)
        return FsciFrameDescription(0x48, 0x29, cmdParams)

    def InitGAPRemoveBondRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        return FsciFrameDescription(0x48, 0x2A, cmdParams)

    def InitGAPRemoveAllBondsRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x2B, cmdParams)

    def InitGAPReadRadioPowerLevelRequest(self):
        cmdParams = []
        TxReadType = FsciParameter("TxReadType", 1)
        cmdParams.append(TxReadType)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x2C, cmdParams)

    def InitGAPVerifyPrivateResolvableAddressRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x2D, cmdParams)

    def InitGAPSetRandomAddressRequest(self):
        cmdParams = []
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x2E, cmdParams)

    def InitGAPSetScanModeRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x2F, cmdParams)

    def InitGAPSetDefaultPairingParametersRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x30, cmdParams)

    def InitGAPUpdateConnectionParametersRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        IntervalMin = FsciParameter("IntervalMin", 2)
        cmdParams.append(IntervalMin)
        IntervalMax = FsciParameter("IntervalMax", 2)
        cmdParams.append(IntervalMax)
        SlaveLatency = FsciParameter("SlaveLatency", 2)
        cmdParams.append(SlaveLatency)
        TimeoutMultiplier = FsciParameter("TimeoutMultiplier", 2)
        cmdParams.append(TimeoutMultiplier)
        MinCeLength = FsciParameter("MinCeLength", 2)
        cmdParams.append(MinCeLength)
        MaxCeLength = FsciParameter("MaxCeLength", 2)
        cmdParams.append(MaxCeLength)
        return FsciFrameDescription(0x48, 0x31, cmdParams)

    def InitGAPEnableUpdateConnectionParametersRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Enable = FsciParameter("Enable", 1)
        cmdParams.append(Enable)
        return FsciFrameDescription(0x48, 0x32, cmdParams)

    def InitGapUpdateLeDataLengthRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        TxOctets = FsciParameter("TxOctets", 2)
        cmdParams.append(TxOctets)
        TxTime = FsciParameter("TxTime", 2)
        cmdParams.append(TxTime)
        return FsciFrameDescription(0x48, 0x33, cmdParams)

    def InitGAPEnableHostPrivacyRequest(self):
        cmdParams = []
        Enable = FsciParameter("Enable", 1)
        cmdParams.append(Enable)
        Irk = FsciParameter("Irk", 16, Enable)
        cmdParams.append(Irk)
        return FsciFrameDescription(0x48, 0x35, cmdParams)

    def InitGAPEnableControllerPrivacyRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x36, cmdParams)

    def InitGAPLeScRegeneratePublicKeyRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x37, cmdParams)

    def InitGAPLeScValidateNumericValueRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Valid = FsciParameter("Valid", 1)
        cmdParams.append(Valid)
        return FsciFrameDescription(0x48, 0x38, cmdParams)

    def InitGAPLeScGetLocalOobDataRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x39, cmdParams)

    def InitGAPLeScSetPeerOobDataRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RandomValue = FsciParameter("RandomValue", 16)
        cmdParams.append(RandomValue)
        ConfirmValue = FsciParameter("ConfirmValue", 16)
        cmdParams.append(ConfirmValue)
        return FsciFrameDescription(0x48, 0x3A, cmdParams)

    def InitGAPLeScSendKeypressNotificationPrivacyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        GapLeScKeypressNotificationParams_keypressNotifType = FsciParameter("GapLeScKeypressNotificationParams_keypressNotifType", 1)
        cmdParams.append(GapLeScKeypressNotificationParams_keypressNotifType)
        return FsciFrameDescription(0x48, 0x3B, cmdParams)

    def InitGAPGetBondedDevicesIdentityInformationRequest(self):
        cmdParams = []
        maxDevices = FsciParameter("maxDevices", 1)
        cmdParams.append(maxDevices)
        return FsciFrameDescription(0x48, 0x3C, cmdParams)

    def InitGAPSetTxPowerLevelRequest(self):
        cmdParams = []
        powerLevel = FsciParameter("powerLevel", 1)
        cmdParams.append(powerLevel)
        channelType = FsciParameter("channelType", 1)
        cmdParams.append(channelType)
        return FsciFrameDescription(0x48, 0x3D, cmdParams)

    def InitGAPLeReadPhyRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x3E, cmdParams)

    def InitGAPLeSetPhyRequest(self):
        cmdParams = []
        defaultMode = FsciParameter("defaultMode", 1)
        cmdParams.append(defaultMode)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        allPhys = FsciParameter("allPhys", 1)
        cmdParams.append(allPhys)
        txPhys = FsciParameter("txPhys", 1)
        cmdParams.append(txPhys)
        rxPhys = FsciParameter("rxPhys", 1)
        cmdParams.append(rxPhys)
        phyOptions = FsciParameter("phyOptions", 2)
        cmdParams.append(phyOptions)
        return FsciFrameDescription(0x48, 0x3F, cmdParams)

    def InitGAPControllerEnhancedNotificationRequest(self):
        cmdParams = []
        EventType = FsciParameter("EventType", 2)
        cmdParams.append(EventType)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x40, cmdParams)

    def InitGAPLoadKeysRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        return FsciFrameDescription(0x48, 0x41, cmdParams)

    def InitGAPSaveKeysRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x42, cmdParams)

    def InitGAPSetChannelMapRequest(self):
        cmdParams = []
        ChannelMap = FsciParameter("ChannelMap", 5)
        cmdParams.append(ChannelMap)
        return FsciFrameDescription(0x48, 0x43, cmdParams)

    def InitGAPReadChannelMapRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x44, cmdParams)

    def InitGAPSetPrivacyModeRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        PrivacyMode = FsciParameter("PrivacyMode", 1)
        cmdParams.append(PrivacyMode)
        return FsciFrameDescription(0x48, 0x45, cmdParams)

    def InitFSCICPUResetRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0x08, cmdParams)

    def InitFSCIGetNumberOfFreeBuffersRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0x09, cmdParams)

    def InitFSCIAllowDeviceToSleepRequest(self):
        cmdParams = []
        SignalHostWhenWakeUp = FsciParameter("SignalHostWhenWakeUp", 1)
        cmdParams.append(SignalHostWhenWakeUp)
        DeepSleepDuration = FsciParameter("DeepSleepDuration", 4)
        cmdParams.append(DeepSleepDuration)
        DeepSleepMode = FsciParameter("DeepSleepMode", 1)
        cmdParams.append(DeepSleepMode)
        return FsciFrameDescription(0xA3, 0x70, cmdParams)

    def InitFSCIGetWakeupReasonRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0x72, cmdParams)

    def InitFSCIGetNumberOfFreeBuffersResponse(self):
        cmdParams = []
        FreeBuffers = FsciParameter("FreeBuffers", 2)
        cmdParams.append(FreeBuffers)
        return FsciFrameDescription(0xA4, 0x09, cmdParams)

    def InitFSCIAckIndication(self):
        cmdParams = []
        Checksum = FsciParameter("Checksum", 1)
        cmdParams.append(Checksum)
        return FsciFrameDescription(0xA4, 0xFD, cmdParams)

    def InitFSCIErrorIndication(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0xFE, cmdParams)

    def InitFSCIAllowDeviceToSleepConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0xA4, 0x70, cmdParams)

    def InitFSCIWakeUpIndication(self):
        cmdParams = []
        return FsciFrameDescription(0xA4, 0x71, cmdParams)

    def InitFSCIGetWakeupReasonResponse(self):
        cmdParams = []
        WakeUpReason = FsciParameter("WakeUpReason", 1)
        cmdParams.append(WakeUpReason)
        return FsciFrameDescription(0xA4, 0x72, cmdParams)


    def InitL2CAPCBConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        return FsciFrameDescription(0x42, 0x80, cmdParams)

    def InitL2CAPCBLePsmConnectionRequestIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x81, cmdParams)

    def InitL2CAPCBLePsmConnectionCompleteIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x82, cmdParams)

    def InitL2CAPCBLePsmDisconnectNotificationIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x83, cmdParams)

    def InitL2CAPCBNoPeerCreditsIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x84, cmdParams)

    def InitL2CAPCBLocalCreditsNotificationIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x85, cmdParams)

    def InitL2CAPCBLeCbDataIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        SrcCid = FsciParameter("SrcCid", 2)
        cmdParams.append(SrcCid)
        PacketLength = FsciParameter("PacketLength", 2)
        cmdParams.append(PacketLength)
        Packet = FsciParameter("Packet", 1, PacketLength)
        cmdParams.append(Packet)
        return FsciFrameDescription(0x42, 0x86, cmdParams)

    def InitL2CAPCBErrorIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x87, cmdParams)

    def InitGATTConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        return FsciFrameDescription(0x45, 0x80, cmdParams)

    def InitGATTGetMtuIndication(self):
        cmdParams = []
        Mtu = FsciParameter("Mtu", 2)
        cmdParams.append(Mtu)
        return FsciFrameDescription(0x45, 0x81, cmdParams)

    def InitGATTClientProcedureExchangeMtuIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        return FsciFrameDescription(0x45, 0x82, cmdParams)

    def InitGATTClientProcedureDiscoverAllPrimaryServicesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x83, cmdParams)

    def InitGATTClientProcedureDiscoverPrimaryServicesByUuidIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x84, cmdParams)

    def InitGATTClientProcedureFindIncludedServicesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x85, cmdParams)

    def InitGATTClientProcedureDiscoverAllCharacteristicsIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x86, cmdParams)

    def InitGATTClientProcedureDiscoverCharacteristicByUuidIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x87, cmdParams)

    def InitGATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x88, cmdParams)

    def InitGATTClientProcedureReadCharacteristicValueIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x89, cmdParams)

    def InitGATTClientProcedureReadUsingCharacteristicUuidIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        NbOfReadBytes = FsciParameter("NbOfReadBytes", 2)
        cmdParams.append(NbOfReadBytes)
        ReadBytes = FsciParameter("ReadBytes", 1, NbOfReadBytes)
        cmdParams.append(ReadBytes)
        return FsciFrameDescription(0x45, 0x8A, cmdParams)

    def InitGATTClientProcedureReadMultipleCharacteristicValuesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x8B, cmdParams)

    def InitGATTClientProcedureWriteCharacteristicValueIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        return FsciFrameDescription(0x45, 0x8C, cmdParams)

    def InitGATTClientProcedureReadCharacteristicDescriptorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        Descriptor_Handle = FsciParameter("Descriptor_Handle", 2)
        cmdParams.append(Descriptor_Handle)
        Descriptor_UuidType = FsciParameter("Descriptor_UuidType", 1)
        cmdParams.append(Descriptor_UuidType)
        Descriptor_Uuiddict = {}
        currentList = []
        Descriptor_UuidUuid16Bits = FsciParameter("Descriptor_UuidUuid16Bits", 2)
        currentList.append(Descriptor_UuidUuid16Bits)
        Descriptor_Uuiddict[0x01] = currentList
        currentList = []
        Descriptor_UuidUuid128Bits = FsciParameter("Descriptor_UuidUuid128Bits", 16)
        currentList.append(Descriptor_UuidUuid128Bits)
        Descriptor_Uuiddict[0x02] = currentList
        currentList = []
        Descriptor_UuidUuid32Bits = FsciParameter("Descriptor_UuidUuid32Bits", 4)
        currentList.append(Descriptor_UuidUuid32Bits)
        Descriptor_Uuiddict[0x03] = currentList
        Descriptor_Uuid = FsciParameter("Descriptor_Uuid", 1, Descriptor_UuidType, Descriptor_Uuiddict)
        cmdParams.append(Descriptor_Uuid)
        Descriptor_ValueLength = FsciParameter("Descriptor_ValueLength", 2)
        cmdParams.append(Descriptor_ValueLength)
        Descriptor_MaxValueLength = FsciParameter("Descriptor_MaxValueLength", 2)
        cmdParams.append(Descriptor_MaxValueLength)
        Descriptor_Value = FsciParameter("Descriptor_Value", 1, Descriptor_ValueLength)
        cmdParams.append(Descriptor_Value)
        return FsciFrameDescription(0x45, 0x8D, cmdParams)

    def InitGATTClientProcedureWriteCharacteristicDescriptorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        return FsciFrameDescription(0x45, 0x8E, cmdParams)

    def InitGATTClientNotificationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        CharacteristicValueHandle = FsciParameter("CharacteristicValueHandle", 2)
        cmdParams.append(CharacteristicValueHandle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x8F, cmdParams)

    def InitGATTClientIndicationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        CharacteristicValueHandle = FsciParameter("CharacteristicValueHandle", 2)
        cmdParams.append(CharacteristicValueHandle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x90, cmdParams)

    def InitGATTServerMtuChangedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        MtuChangedEvent_NewMtu = FsciParameter("MtuChangedEvent_NewMtu", 2)
        cmdParams.append(MtuChangedEvent_NewMtu)
        return FsciFrameDescription(0x45, 0x91, cmdParams)

    def InitGATTServerHandleValueConfirmationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x45, 0x92, cmdParams)

    def InitGATTServerAttributeWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        AttributeWrittenEvent_Handle = FsciParameter("AttributeWrittenEvent_Handle", 2)
        cmdParams.append(AttributeWrittenEvent_Handle)
        AttributeWrittenEvent_ValueLength = FsciParameter("AttributeWrittenEvent_ValueLength", 2)
        cmdParams.append(AttributeWrittenEvent_ValueLength)
        AttributeWrittenEvent_Value = FsciParameter("AttributeWrittenEvent_Value", 1, AttributeWrittenEvent_ValueLength)
        cmdParams.append(AttributeWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0x93, cmdParams)

    def InitGATTServerCharacteristicCccdWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        CharCccdWrittenEvent_Handle = FsciParameter("CharCccdWrittenEvent_Handle", 2)
        cmdParams.append(CharCccdWrittenEvent_Handle)
        CharCccdWrittenEvent_NewCccd = FsciParameter("CharCccdWrittenEvent_NewCccd", 1)
        cmdParams.append(CharCccdWrittenEvent_NewCccd)
        return FsciFrameDescription(0x45, 0x94, cmdParams)

    def InitGATTServerAttributeWrittenWithoutResponseIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        AttributeWrittenEvent_Handle = FsciParameter("AttributeWrittenEvent_Handle", 2)
        cmdParams.append(AttributeWrittenEvent_Handle)
        AttributeWrittenEvent_ValueLength = FsciParameter("AttributeWrittenEvent_ValueLength", 2)
        cmdParams.append(AttributeWrittenEvent_ValueLength)
        AttributeWrittenEvent_Value = FsciParameter("AttributeWrittenEvent_Value", 1, AttributeWrittenEvent_ValueLength)
        cmdParams.append(AttributeWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0x95, cmdParams)

    def InitGATTServerErrorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ProcedureError_ProcedureType = FsciParameter("ProcedureError_ProcedureType", 1)
        cmdParams.append(ProcedureError_ProcedureType)
        ProcedureError_Error = FsciParameter("ProcedureError_Error", 2)
        cmdParams.append(ProcedureError_Error)
        return FsciFrameDescription(0x45, 0x96, cmdParams)

    def InitGATTServerLongCharacteristicWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        LongCharacteristicWrittenEvent_Handle = FsciParameter("LongCharacteristicWrittenEvent_Handle", 2)
        cmdParams.append(LongCharacteristicWrittenEvent_Handle)
        LongCharacteristicWrittenEvent_ValueLength = FsciParameter("LongCharacteristicWrittenEvent_ValueLength", 2)
        cmdParams.append(LongCharacteristicWrittenEvent_ValueLength)
        LongCharacteristicWrittenEvent_Value = FsciParameter("LongCharacteristicWrittenEvent_Value", 1, LongCharacteristicWrittenEvent_ValueLength)
        cmdParams.append(LongCharacteristicWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0x97, cmdParams)

    def InitGATTServerAttributeReadIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        AttributeReadEvent_Handle = FsciParameter("AttributeReadEvent_Handle", 2)
        cmdParams.append(AttributeReadEvent_Handle)
        return FsciFrameDescription(0x45, 0x98, cmdParams)

    def InitGATTDBConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        return FsciFrameDescription(0x46, 0x80, cmdParams)

    def InitGATTDBReadAttributeIndication(self):
        cmdParams = []
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x46, 0x81, cmdParams)

    def InitGATTDBFindServiceHandleIndication(self):
        cmdParams = []
        ServiceHandle = FsciParameter("ServiceHandle", 2)
        cmdParams.append(ServiceHandle)
        return FsciFrameDescription(0x46, 0x82, cmdParams)

    def InitGATTDBFindCharValueHandleInServiceIndication(self):
        cmdParams = []
        CharValueHandle = FsciParameter("CharValueHandle", 2)
        cmdParams.append(CharValueHandle)
        return FsciFrameDescription(0x46, 0x83, cmdParams)

    def InitGATTDBFindCccdHandleForCharValueHandleIndication(self):
        cmdParams = []
        CccdHandle = FsciParameter("CccdHandle", 2)
        cmdParams.append(CccdHandle)
        return FsciFrameDescription(0x46, 0x84, cmdParams)

    def InitGATTDBFindDescriptorHandleForCharValueHandleIndication(self):
        cmdParams = []
        DescriptorHandle = FsciParameter("DescriptorHandle", 2)
        cmdParams.append(DescriptorHandle)
        return FsciFrameDescription(0x46, 0x85, cmdParams)

    def InitGATTDBDynamicAddPrimaryServiceDeclarationIndication(self):
        cmdParams = []
        ServiceHandle = FsciParameter("ServiceHandle", 2)
        cmdParams.append(ServiceHandle)
        return FsciFrameDescription(0x46, 0x86, cmdParams)

    def InitGATTDBDynamicAddSecondaryServiceDeclarationIndication(self):
        cmdParams = []
        ServiceHandle = FsciParameter("ServiceHandle", 2)
        cmdParams.append(ServiceHandle)
        return FsciFrameDescription(0x46, 0x87, cmdParams)

    def InitGATTDBDynamicAddIncludeDeclarationIndication(self):
        cmdParams = []
        IncludeHandle = FsciParameter("IncludeHandle", 2)
        cmdParams.append(IncludeHandle)
        return FsciFrameDescription(0x46, 0x88, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationAndValueIndication(self):
        cmdParams = []
        CharacteristicHandle = FsciParameter("CharacteristicHandle", 2)
        cmdParams.append(CharacteristicHandle)
        return FsciFrameDescription(0x46, 0x89, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDescriptorIndication(self):
        cmdParams = []
        DescriptorHandle = FsciParameter("DescriptorHandle", 2)
        cmdParams.append(DescriptorHandle)
        return FsciFrameDescription(0x46, 0x8A, cmdParams)

    def InitGATTDBDynamicAddCccdIndication(self):
        cmdParams = []
        CCCDHandle = FsciParameter("CCCDHandle", 2)
        cmdParams.append(CCCDHandle)
        return FsciFrameDescription(0x46, 0x8B, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication(self):
        cmdParams = []
        CharacteristicHandle = FsciParameter("CharacteristicHandle", 2)
        cmdParams.append(CharacteristicHandle)
        return FsciFrameDescription(0x46, 0x8C, cmdParams)

    def InitGATTDBDynamicAddCharDescriptorWithUniqueValueIndication(self):
        cmdParams = []
        DescriptorHandle = FsciParameter("DescriptorHandle", 2)
        cmdParams.append(DescriptorHandle)
        return FsciFrameDescription(0x46, 0x8D, cmdParams)

    def InitGAPConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        return FsciFrameDescription(0x48, 0x80, cmdParams)

    def InitGAPCheckNotificationStatusIndication(self):
        cmdParams = []
        IsActive = FsciParameter("IsActive", 1)
        cmdParams.append(IsActive)
        return FsciFrameDescription(0x48, 0x81, cmdParams)

    def InitGAPCheckIndicationStatusIndication(self):
        cmdParams = []
        IsActive = FsciParameter("IsActive", 1)
        cmdParams.append(IsActive)
        return FsciFrameDescription(0x48, 0x82, cmdParams)

    def InitGAPLoadKeysIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x48, 0x83, cmdParams)

    def InitGAPLoadEncryptionInformationIndication(self):
        cmdParams = []
        LtkSize = FsciParameter("LtkSize", 1)
        cmdParams.append(LtkSize)
        Ltk = FsciParameter("Ltk", 1, LtkSize)
        cmdParams.append(Ltk)
        return FsciFrameDescription(0x48, 0x84, cmdParams)

    def InitGAPLoadCustomPeerInformationIndication(self):
        cmdParams = []
        InfoSize = FsciParameter("InfoSize", 2)
        cmdParams.append(InfoSize)
        Info = FsciParameter("Info", 1, InfoSize)
        cmdParams.append(Info)
        return FsciFrameDescription(0x48, 0x85, cmdParams)

    def InitGAPCheckIfBondedIndication(self):
        cmdParams = []
        IsBonded = FsciParameter("IsBonded", 1)
        cmdParams.append(IsBonded)
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        return FsciFrameDescription(0x48, 0x86, cmdParams)

    def InitGAPGetBondedDevicesCountIndication(self):
        cmdParams = []
        NbOfBondedDevices = FsciParameter("NbOfBondedDevices", 1)
        cmdParams.append(NbOfBondedDevices)
        return FsciFrameDescription(0x48, 0x87, cmdParams)

    def InitGAPGetBondedDeviceNameIndication(self):
        cmdParams = []
        NameSize = FsciParameter("NameSize", 1)
        cmdParams.append(NameSize)
        Name = FsciParameter("Name", 1, NameSize)
        cmdParams.append(Name)
        return FsciFrameDescription(0x48, 0x88, cmdParams)

    def InitGAPGenericEventInitializationCompleteIndication(self):
        cmdParams = []
        initCompleteData_SupportedFeatures = FsciParameter("initCompleteData_SupportedFeatures", 4)
        cmdParams.append(initCompleteData_SupportedFeatures)
        initCompleteData_MaxAdvDataSize = FsciParameter("initCompleteData_MaxAdvDataSize", 2)
        cmdParams.append(initCompleteData_MaxAdvDataSize)
        initCompleteData_NumOfSupportedAdvSets = FsciParameter("initCompleteData_NumOfSupportedAdvSets", 1)
        cmdParams.append(initCompleteData_NumOfSupportedAdvSets)
        initCompleteData_PeriodicAdvListSize = FsciParameter("initCompleteData_PeriodicAdvListSize", 1)
        cmdParams.append(initCompleteData_PeriodicAdvListSize)
        return FsciFrameDescription(0x48, 0x89, cmdParams)

    def InitGAPGenericEventInternalErrorIndication(self):
        cmdParams = []
        InternalError_ErrorCode = FsciParameter("InternalError_ErrorCode", 2)
        cmdParams.append(InternalError_ErrorCode)
        InternalError_ErrorSource = FsciParameter("InternalError_ErrorSource", 1)
        cmdParams.append(InternalError_ErrorSource)
        InternalError_HciCommandOpcode = FsciParameter("InternalError_HciCommandOpcode", 2)
        cmdParams.append(InternalError_HciCommandOpcode)
        return FsciFrameDescription(0x48, 0x8A, cmdParams)

    def InitGAPGenericEventAdvertisingSetupFailedIndication(self):
        cmdParams = []
        SetupFailReason = FsciParameter("SetupFailReason", 2)
        cmdParams.append(SetupFailReason)
        return FsciFrameDescription(0x48, 0x8B, cmdParams)

    def InitGAPGenericEventAdvertisingParametersSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x8C, cmdParams)

    def InitGAPGenericEventAdvertisingDataSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x8D, cmdParams)

    def InitGAPGenericEventWhiteListSizeReadIndication(self):
        cmdParams = []
        WhiteListSize = FsciParameter("WhiteListSize", 1)
        cmdParams.append(WhiteListSize)
        return FsciFrameDescription(0x48, 0x8E, cmdParams)

    def InitGAPGenericEventDeviceAddedToWhiteListIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x8F, cmdParams)

    def InitGAPGenericEventDeviceRemovedFromWhiteListIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x90, cmdParams)

    def InitGAPGenericEventWhiteListClearedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x91, cmdParams)

    def InitGAPGenericEventRandomAddressReadyIndication(self):
        cmdParams = []
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x92, cmdParams)

    def InitGAPGenericEventCreateConnectionCanceledIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x93, cmdParams)

    def InitGAPGenericEventPublicAddressReadIndication(self):
        cmdParams = []
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x94, cmdParams)

    def InitGAPGenericEventAdvTxPowerLevelReadIndication(self):
        cmdParams = []
        AdvTxPowerLevel = FsciParameter("AdvTxPowerLevel", 1)
        cmdParams.append(AdvTxPowerLevel)
        return FsciFrameDescription(0x48, 0x95, cmdParams)

    def InitGAPGenericEventPrivateResolvableAddressVerifiedIndication(self):
        cmdParams = []
        Verified = FsciParameter("Verified", 1)
        cmdParams.append(Verified)
        return FsciFrameDescription(0x48, 0x96, cmdParams)

    def InitGAPGenericEventRandomAddressSetIndication(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x97, cmdParams)

    def InitGAPAdvertisingEventStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x98, cmdParams)

    def InitGAPAdvertisingEventCommandFailedIndication(self):
        cmdParams = []
        FailReason = FsciParameter("FailReason", 2)
        cmdParams.append(FailReason)
        return FsciFrameDescription(0x48, 0x99, cmdParams)

    def InitGAPScanningEventStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x9A, cmdParams)

    def InitGAPScanningEventCommandFailedIndication(self):
        cmdParams = []
        FailReason = FsciParameter("FailReason", 2)
        cmdParams.append(FailReason)
        return FsciFrameDescription(0x48, 0x9B, cmdParams)

    def InitGAPScanningEventDeviceScannedIndication(self):
        cmdParams = []
        ScannedDevice_AddressType = FsciParameter("ScannedDevice_AddressType", 1)
        cmdParams.append(ScannedDevice_AddressType)
        ScannedDevice_Address = FsciParameter("ScannedDevice_Address", 6)
        cmdParams.append(ScannedDevice_Address)
        ScannedDevice_Rssi = FsciParameter("ScannedDevice_Rssi", 1)
        cmdParams.append(ScannedDevice_Rssi)
        ScannedDevice_DataLength = FsciParameter("ScannedDevice_DataLength", 1)
        cmdParams.append(ScannedDevice_DataLength)
        ScannedDevice_Data = FsciParameter("ScannedDevice_Data", 1, ScannedDevice_DataLength)
        cmdParams.append(ScannedDevice_Data)
        ScannedDevice_AdvEventType = FsciParameter("ScannedDevice_AdvEventType", 1)
        cmdParams.append(ScannedDevice_AdvEventType)
        ScannedDevice_DirectRpaUsed = FsciParameter("ScannedDevice_DirectRpaUsed", 1)
        cmdParams.append(ScannedDevice_DirectRpaUsed)
        ScannedDevice_DirectRpa = FsciParameter("ScannedDevice_DirectRpa", 6, ScannedDevice_DirectRpaUsed)
        cmdParams.append(ScannedDevice_DirectRpa)
        ScannedDevice_advertisingAddressResolved = FsciParameter("ScannedDevice_advertisingAddressResolved", 1)
        cmdParams.append(ScannedDevice_advertisingAddressResolved)
        return FsciFrameDescription(0x48, 0x9C, cmdParams)

    def InitGAPConnectionEventConnectedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ConnectionParameters_ConnInterval = FsciParameter("ConnectionParameters_ConnInterval", 2)
        cmdParams.append(ConnectionParameters_ConnInterval)
        ConnectionParameters_ConnLatency = FsciParameter("ConnectionParameters_ConnLatency", 2)
        cmdParams.append(ConnectionParameters_ConnLatency)
        ConnectionParameters_SupervisionTimeout = FsciParameter("ConnectionParameters_SupervisionTimeout", 2)
        cmdParams.append(ConnectionParameters_SupervisionTimeout)
        ConnectionParameters_MasterClockAccuracy = FsciParameter("ConnectionParameters_MasterClockAccuracy", 1)
        cmdParams.append(ConnectionParameters_MasterClockAccuracy)
        PeerAddressType = FsciParameter("PeerAddressType", 1)
        cmdParams.append(PeerAddressType)
        PeerAddress = FsciParameter("PeerAddress", 6)
        cmdParams.append(PeerAddress)
        peerRpaResolved = FsciParameter("peerRpaResolved", 1)
        cmdParams.append(peerRpaResolved)
        peerRpa = FsciParameter("peerRpa", 6, peerRpaResolved)
        cmdParams.append(peerRpa)
        localRpaUsed = FsciParameter("localRpaUsed", 1)
        cmdParams.append(localRpaUsed)
        localRpa = FsciParameter("localRpa", 6, localRpaUsed)
        cmdParams.append(localRpa)
        connectionRole = FsciParameter("connectionRole", 1)
        cmdParams.append(connectionRole)
        return FsciFrameDescription(0x48, 0x9D, cmdParams)

    def InitGAPConnectionEventPairingRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingParameters_WithBonding = FsciParameter("PairingParameters_WithBonding", 1)
        cmdParams.append(PairingParameters_WithBonding)
        PairingParameters_SecurityModeAndLevel = FsciParameter("PairingParameters_SecurityModeAndLevel", 1)
        cmdParams.append(PairingParameters_SecurityModeAndLevel)
        PairingParameters_MaxEncryptionKeySize = FsciParameter("PairingParameters_MaxEncryptionKeySize", 1)
        cmdParams.append(PairingParameters_MaxEncryptionKeySize)
        PairingParameters_LocalIoCapabilities = FsciParameter("PairingParameters_LocalIoCapabilities", 1)
        cmdParams.append(PairingParameters_LocalIoCapabilities)
        PairingParameters_OobAvailable = FsciParameter("PairingParameters_OobAvailable", 1)
        cmdParams.append(PairingParameters_OobAvailable)
        PairingParameters_CentralKeys = FsciParameter("PairingParameters_CentralKeys", 1)
        cmdParams.append(PairingParameters_CentralKeys)
        PairingParameters_PeripheralKeys = FsciParameter("PairingParameters_PeripheralKeys", 1)
        cmdParams.append(PairingParameters_PeripheralKeys)
        PairingParameters_LeSecureConnectionSupported = FsciParameter("PairingParameters_LeSecureConnectionSupported", 1)
        cmdParams.append(PairingParameters_LeSecureConnectionSupported)
        PairingParameters_UseKeypressNotifications = FsciParameter("PairingParameters_UseKeypressNotifications", 1)
        cmdParams.append(PairingParameters_UseKeypressNotifications)
        return FsciFrameDescription(0x48, 0x9E, cmdParams)

    def InitGAPConnectionEventSlaveSecurityRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        SlaveSecurityRequestParameters_BondAfterPairing = FsciParameter("SlaveSecurityRequestParameters_BondAfterPairing", 1)
        cmdParams.append(SlaveSecurityRequestParameters_BondAfterPairing)
        SlaveSecurityRequestParameters_bAuthenticationRequired = FsciParameter("SlaveSecurityRequestParameters_bAuthenticationRequired", 1)
        cmdParams.append(SlaveSecurityRequestParameters_bAuthenticationRequired)
        return FsciFrameDescription(0x48, 0x9F, cmdParams)

    def InitGAPConnectionEventPairingResponseIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingParameters_WithBonding = FsciParameter("PairingParameters_WithBonding", 1)
        cmdParams.append(PairingParameters_WithBonding)
        PairingParameters_SecurityModeAndLevel = FsciParameter("PairingParameters_SecurityModeAndLevel", 1)
        cmdParams.append(PairingParameters_SecurityModeAndLevel)
        PairingParameters_MaxEncryptionKeySize = FsciParameter("PairingParameters_MaxEncryptionKeySize", 1)
        cmdParams.append(PairingParameters_MaxEncryptionKeySize)
        PairingParameters_LocalIoCapabilities = FsciParameter("PairingParameters_LocalIoCapabilities", 1)
        cmdParams.append(PairingParameters_LocalIoCapabilities)
        PairingParameters_OobAvailable = FsciParameter("PairingParameters_OobAvailable", 1)
        cmdParams.append(PairingParameters_OobAvailable)
        PairingParameters_CentralKeys = FsciParameter("PairingParameters_CentralKeys", 1)
        cmdParams.append(PairingParameters_CentralKeys)
        PairingParameters_PeripheralKeys = FsciParameter("PairingParameters_PeripheralKeys", 1)
        cmdParams.append(PairingParameters_PeripheralKeys)
        PairingParameters_LeSecureConnectionSupported = FsciParameter("PairingParameters_LeSecureConnectionSupported", 1)
        cmdParams.append(PairingParameters_LeSecureConnectionSupported)
        PairingParameters_UseKeypressNotifications = FsciParameter("PairingParameters_UseKeypressNotifications", 1)
        cmdParams.append(PairingParameters_UseKeypressNotifications)
        return FsciFrameDescription(0x48, 0xA0, cmdParams)

    def InitGAPConnectionEventAuthenticationRejectedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RejectReason = FsciParameter("RejectReason", 1)
        cmdParams.append(RejectReason)
        return FsciFrameDescription(0x48, 0xA1, cmdParams)

    def InitGAPConnectionEventPasskeyRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xA2, cmdParams)

    def InitGAPConnectionEventOobRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xA3, cmdParams)

    def InitGAPConnectionEventPasskeyDisplayIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PasskeyForDisplay = FsciParameter("PasskeyForDisplay", 4)
        cmdParams.append(PasskeyForDisplay)
        return FsciFrameDescription(0x48, 0xA4, cmdParams)

    def InitGAPConnectionEventKeyExchangeRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RequestedKeys = FsciParameter("RequestedKeys", 1)
        cmdParams.append(RequestedKeys)
        RequestedLtkSize = FsciParameter("RequestedLtkSize", 1)
        cmdParams.append(RequestedLtkSize)
        return FsciFrameDescription(0x48, 0xA5, cmdParams)

    def InitGAPConnectionEventKeysReceivedIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x48, 0xA6, cmdParams)

    def InitGAPConnectionEventLongTermKeyRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Ediv = FsciParameter("Ediv", 2)
        cmdParams.append(Ediv)
        RandSize = FsciParameter("RandSize", 1)
        cmdParams.append(RandSize)
        Rand = FsciParameter("Rand", 1, RandSize)
        cmdParams.append(Rand)
        return FsciFrameDescription(0x48, 0xA7, cmdParams)

    def InitGAPConnectionEventEncryptionChangedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        NewEncryptionState = FsciParameter("NewEncryptionState", 1)
        cmdParams.append(NewEncryptionState)
        return FsciFrameDescription(0x48, 0xA8, cmdParams)

    def InitGAPConnectionEventPairingCompleteIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PairingStatus = FsciParameter("PairingStatus", 1)
        cmdParams.append(PairingStatus)
        PairingDatadict = {}
        currentList = []
        PairingSuccessfulWithBonding = FsciParameter("PairingSuccessfulWithBonding", 1)
        currentList.append(PairingSuccessfulWithBonding)
        PairingDatadict[0x01] = currentList
        currentList = []
        PairingFailedFailReason = FsciParameter("PairingFailedFailReason", 2)
        currentList.append(PairingFailedFailReason)
        PairingDatadict[0x00] = currentList
        PairingData = FsciParameter("PairingData", 1, PairingStatus, PairingDatadict)
        cmdParams.append(PairingData)
        return FsciFrameDescription(0x48, 0xA9, cmdParams)

    def InitGAPConnectionEventDisconnectedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Reason = FsciParameter("Reason", 2)
        cmdParams.append(Reason)
        return FsciFrameDescription(0x48, 0xAA, cmdParams)

    def InitGAPConnectionEventRssiReadIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Rssi = FsciParameter("Rssi", 1)
        cmdParams.append(Rssi)
        return FsciFrameDescription(0x48, 0xAB, cmdParams)

    def InitGAPConnectionEventTxPowerLevelReadIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        TxPowerLevel = FsciParameter("TxPowerLevel", 1)
        cmdParams.append(TxPowerLevel)
        return FsciFrameDescription(0x48, 0xAC, cmdParams)

    def InitGAPConnectionEventPowerReadFailureIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        FailReason = FsciParameter("FailReason", 2)
        cmdParams.append(FailReason)
        return FsciFrameDescription(0x48, 0xAD, cmdParams)

    def InitGAPConnectionEventParameterUpdateRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ConnectionParameterUpdateRequest_IntervalMin = FsciParameter("ConnectionParameterUpdateRequest_IntervalMin", 2)
        cmdParams.append(ConnectionParameterUpdateRequest_IntervalMin)
        ConnectionParameterUpdateRequest_IntervalMax = FsciParameter("ConnectionParameterUpdateRequest_IntervalMax", 2)
        cmdParams.append(ConnectionParameterUpdateRequest_IntervalMax)
        ConnectionParameterUpdateRequest_SlaveLatency = FsciParameter("ConnectionParameterUpdateRequest_SlaveLatency", 2)
        cmdParams.append(ConnectionParameterUpdateRequest_SlaveLatency)
        ConnectionParameterUpdateRequest_TimeoutMultiplier = FsciParameter("ConnectionParameterUpdateRequest_TimeoutMultiplier", 2)
        cmdParams.append(ConnectionParameterUpdateRequest_TimeoutMultiplier)
        return FsciFrameDescription(0x48, 0xAE, cmdParams)

    def InitGAPConnectionEventParameterUpdateCompleteIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ConnectionParameterUpdateComplete_Status = FsciParameter("ConnectionParameterUpdateComplete_Status", 2)
        cmdParams.append(ConnectionParameterUpdateComplete_Status)
        ConnectionParameterUpdateComplete_ConnInterval = FsciParameter("ConnectionParameterUpdateComplete_ConnInterval", 2)
        cmdParams.append(ConnectionParameterUpdateComplete_ConnInterval)
        ConnectionParameterUpdateComplete_ConnLatency = FsciParameter("ConnectionParameterUpdateComplete_ConnLatency", 2)
        cmdParams.append(ConnectionParameterUpdateComplete_ConnLatency)
        ConnectionParameterUpdateComplete_SupervisionTimeout = FsciParameter("ConnectionParameterUpdateComplete_SupervisionTimeout", 2)
        cmdParams.append(ConnectionParameterUpdateComplete_SupervisionTimeout)
        return FsciFrameDescription(0x48, 0xAF, cmdParams)

    def InitGAPConnectionEventLeDataLengthChangedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        LeDataLengthChanged_MaxTxOctets = FsciParameter("LeDataLengthChanged_MaxTxOctets", 2)
        cmdParams.append(LeDataLengthChanged_MaxTxOctets)
        LeDataLengthChanged_MaxTxTime = FsciParameter("LeDataLengthChanged_MaxTxTime", 2)
        cmdParams.append(LeDataLengthChanged_MaxTxTime)
        LeDataLengthChanged_MaxRxOctets = FsciParameter("LeDataLengthChanged_MaxRxOctets", 2)
        cmdParams.append(LeDataLengthChanged_MaxRxOctets)
        LeDataLengthChanged_MaxRxTime = FsciParameter("LeDataLengthChanged_MaxRxTime", 2)
        cmdParams.append(LeDataLengthChanged_MaxRxTime)
        return FsciFrameDescription(0x48, 0xB0, cmdParams)

    def InitGAPConnectionEventLeScOobDataRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xB1, cmdParams)

    def InitGAPConnectionEventLeScDisplayNumericValueIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ncValue = FsciParameter("ncValue", 4)
        cmdParams.append(ncValue)
        return FsciFrameDescription(0x48, 0xB2, cmdParams)

    def InitGAPConnectionEventLeScKeypressNotificationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        GapLeScKeypressNotificationParams_keypressNotifType = FsciParameter("GapLeScKeypressNotificationParams_keypressNotifType", 1)
        cmdParams.append(GapLeScKeypressNotificationParams_keypressNotifType)
        return FsciFrameDescription(0x48, 0xB3, cmdParams)


    def InitGAPLeScPublicKeyRegeneratedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xB5, cmdParams)

    def InitGAPGenericEventLeScLocalOobDataIndication(self):
        cmdParams = []
        RandomValue = FsciParameter("RandomValue", 16)
        cmdParams.append(RandomValue)
        ConfirmValue = FsciParameter("ConfirmValue", 16)
        cmdParams.append(ConfirmValue)
        return FsciFrameDescription(0x48, 0xB6, cmdParams)

    def InitGAPGenericEventHostPrivacyStateChangedIndication(self):
        cmdParams = []
        NewHostPrivacyState = FsciParameter("NewHostPrivacyState", 1)
        cmdParams.append(NewHostPrivacyState)
        return FsciFrameDescription(0x48, 0xB7, cmdParams)

    def InitGAPGenericEventControllerPrivacyStateChangedIndication(self):
        cmdParams = []
        NewControllerPrivacyState = FsciParameter("NewControllerPrivacyState", 1)
        cmdParams.append(NewControllerPrivacyState)
        return FsciFrameDescription(0x48, 0xB8, cmdParams)

    def InitGAPGenericEventTxPowerLevelSetCompleteIndication(self):
        cmdParams = []
        status = FsciParameter("status", 1)
        cmdParams.append(status)
        return FsciFrameDescription(0x48, 0xB9, cmdParams)

    def InitGAPGenericEventLePhyEventIndication(self):
        cmdParams = []
        eventType = FsciParameter("eventType", 1)
        cmdParams.append(eventType)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        txPhy = FsciParameter("txPhy", 1)
        cmdParams.append(txPhy)
        rxPhy = FsciParameter("rxPhy", 1)
        cmdParams.append(rxPhy)
        return FsciFrameDescription(0x48, 0xBA, cmdParams)

    def InitGAPGetBondedDevicesIdentityInformationIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x48, 0xBB, cmdParams)

    def InitGAPControllerNotificationIndication(self):
        cmdParams = []
        EventType = FsciParameter("EventType", 2)
        cmdParams.append(EventType)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RSSI = FsciParameter("RSSI", 1)
        cmdParams.append(RSSI)
        Channel = FsciParameter("Channel", 1)
        cmdParams.append(Channel)
        ConnEvCounter = FsciParameter("ConnEvCounter", 2)
        cmdParams.append(ConnEvCounter)
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        Timestamp = FsciParameter("Timestamp", 2)
        cmdParams.append(Timestamp)
        AdvHandle = FsciParameter("AdvHandle", 1)
        cmdParams.append(AdvHandle)
        return FsciFrameDescription(0x48, 0xBC, cmdParams)

    def InitGAPBondCreatedIndication(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        AddrType = FsciParameter("AddrType", 1)
        cmdParams.append(AddrType)
        Addr = FsciParameter("Addr", 6)
        cmdParams.append(Addr)
        return FsciFrameDescription(0x48, 0xBD, cmdParams)

    def InitGAPGenericEventChannelMapSetIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xBE, cmdParams)

    def InitGAPConnectionEventChannelMapReadIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ChannelMap = FsciParameter("ChannelMap", 5)
        cmdParams.append(ChannelMap)
        return FsciFrameDescription(0x48, 0xBF, cmdParams)

    def InitGAPConnectionEventChannelMapReadFailureIndication(self):
        cmdParams = []
        FailReason = FsciParameter("FailReason", 2)
        cmdParams.append(FailReason)
        return FsciFrameDescription(0x48, 0xC0, cmdParams)

    def InitGAPConnectionEventChannelSelectionAlgorithm2Indication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xD1, cmdParams)

    def InitGAPGenericEventTxEntryAvailableIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xD2, cmdParams)
