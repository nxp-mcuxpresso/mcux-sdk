'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2022 NXP
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
        self.L2CAPInitRequestFrame = self.InitL2CAPInitRequest()
        self.L2CAPSendAttDataRequestFrame = self.InitL2CAPSendAttDataRequest()
        self.L2CAPSendSmpDataRequestFrame = self.InitL2CAPSendSmpDataRequest()
        self.L2CAPRegisterAttCallbackRequestFrame = self.InitL2CAPRegisterAttCallbackRequest()
        self.L2CAPRegisterSmpCallbackRequestFrame = self.InitL2CAPRegisterSmpCallbackRequest()
        self.L2CAPCBRegisterLeCbCallbacksRequestFrame = self.InitL2CAPCBRegisterLeCbCallbacksRequest()
        self.L2CAPCBRegisterLePsmRequestFrame = self.InitL2CAPCBRegisterLePsmRequest()
        self.L2CAPCBDeregisterLePsmRequestFrame = self.InitL2CAPCBDeregisterLePsmRequest()
        self.L2CAPCBConnectLePsmRequestFrame = self.InitL2CAPCBConnectLePsmRequest()
        self.L2CAPCBDisconnectLeCbChannelRequestFrame = self.InitL2CAPCBDisconnectLeCbChannelRequest()
        self.L2CAPCBCancelConnectionRequestFrame = self.InitL2CAPCBCancelConnectionRequest()
        self.L2CAPCBSendLeCbDataRequestFrame = self.InitL2CAPCBSendLeCbDataRequest()
        self.L2CAPCBSendLeCreditRequestFrame = self.InitL2CAPCBSendLeCreditRequest()
        self.L2CAPCBEnhancedConnectLePsmRequestFrame = self.InitL2CAPCBEnhancedConnectLePsmRequest()
        self.L2CAPCBEnhancedChannelReconfigureRequestFrame = self.InitL2CAPCBEnhancedChannelReconfigureRequest()
        self.L2CAPCBEnhancedCancelConnectionRequestFrame = self.InitL2CAPCBEnhancedCancelConnectionRequest()
        self.GATTInitRequestFrame = self.InitGATTInitRequest()
        self.GATTGetMtuRequestFrame = self.InitGATTGetMtuRequest()
        self.GATTClientInitRequestFrame = self.InitGATTClientInitRequest()
        self.GATTClientResetProcedureRequestFrame = self.InitGATTClientResetProcedureRequest()
        self.GATTClientRegisterProcedureCallbackRequestFrame = self.InitGATTClientRegisterProcedureCallbackRequest()
        self.GATTClientRegisterNotificationCallbackRequestFrame = self.InitGATTClientRegisterNotificationCallbackRequest()
        self.GATTClientRegisterMultipleValueNotificationCallbackRequestFrame = self.InitGATTClientRegisterMultipleValueNotificationCallbackRequest()
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
        self.GATTServerSendMultipleHandleValueNotificationRequestFrame = self.InitGATTServerSendMultipleHandleValueNotificationRequest()
        self.GATTServerRegisterHandlesForReadNotificationsRequestFrame = self.InitGATTServerRegisterHandlesForReadNotificationsRequest()
        self.GATTServerSendAttributeReadStatusRequestFrame = self.InitGATTServerSendAttributeReadStatusRequest()
        self.GATTServerRegisterUniqueHandlesForNotificationsRequestFrame = self.InitGATTServerRegisterUniqueHandlesForNotificationsRequest()
        self.GATTServerUnregisterHandlesForWriteNotificationsRequestFrame = self.InitGATTServerUnregisterHandlesForWriteNotificationsRequest()
        self.GATTServerUnregisterHandlesForReadNotificationsRequestFrame = self.InitGATTServerUnregisterHandlesForReadNotificationsRequest()
        self.GATTClientReadMultipleVariableCharacteristicValuesRequestFrame = self.InitGATTClientReadMultipleVariableCharacteristicValuesRequest()
        self.GATTClientRegisterEnhancedProcedureCallbackRequestFrame = self.InitGATTClientRegisterEnhancedProcedureCallbackRequest()
        self.GATTClientRegisterEnhancedNotificationCallbackRequestFrame = self.InitGATTClientRegisterEnhancedNotificationCallbackRequest()
        self.GATTClientRegisterEnhancedIndicationCallbackRequestFrame = self.InitGATTClientRegisterEnhancedIndicationCallbackRequest()
        self.GATTClientRegisterEnhancedMultipleValueNotificationCallbackRequestFrame = self.InitGATTClientRegisterEnhancedMultipleValueNotificationCallbackRequest()
        self.GATTClientEnhancedDiscoverAllPrimaryServicesRequestFrame = self.InitGATTClientEnhancedDiscoverAllPrimaryServicesRequest()
        self.GATTClientEnhancedDiscoverPrimaryServicesByUuidRequestFrame = self.InitGATTClientEnhancedDiscoverPrimaryServicesByUuidRequest()
        self.GATTClientEnhancedFindIncludedServicesRequestFrame = self.InitGATTClientEnhancedFindIncludedServicesRequest()
        self.GATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequestFrame = self.InitGATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest()
        self.GATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequestFrame = self.InitGATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest()
        self.GATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequestFrame = self.InitGATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest()
        self.GATTClientEnhancedReadCharacteristicValueRequestFrame = self.InitGATTClientEnhancedReadCharacteristicValueRequest()
        self.GATTClientEnhancedReadUsingCharacteristicUuidRequestFrame = self.InitGATTClientEnhancedReadUsingCharacteristicUuidRequest()
        self.GATTClientEnhancedReadMultipleCharacteristicValuesRequestFrame = self.InitGATTClientEnhancedReadMultipleCharacteristicValuesRequest()
        self.GATTClientEnhancedWriteCharacteristicValueRequestFrame = self.InitGATTClientEnhancedWriteCharacteristicValueRequest()
        self.GATTClientEnhancedReadCharacteristicDescriptorRequestFrame = self.InitGATTClientEnhancedReadCharacteristicDescriptorRequest()
        self.GATTClientEnhancedWriteCharacteristicDescriptorRequestFrame = self.InitGATTClientEnhancedWriteCharacteristicDescriptorRequest()
        self.GATTClientEnhancedReadMultipleVariableCharacteristicValuesRequestFrame = self.InitGATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest()
        self.GATTServerRegisterEnhancedCallbackRequestFrame = self.InitGATTServerRegisterEnhancedCallbackRequest()
        self.GATTServerEnhancedSendAttributeWrittenStatusRequestFrame = self.InitGATTServerEnhancedSendAttributeWrittenStatusRequest()
        self.GATTServerEnhancedSendNotificationRequestFrame = self.InitGATTServerEnhancedSendNotificationRequest()
        self.GATTServerEnhancedSendIndicationRequestFrame = self.InitGATTServerEnhancedSendIndicationRequest()
        self.GATTServerEnhancedSendInstantValueNotificationRequestFrame = self.InitGATTServerEnhancedSendInstantValueNotificationRequest()
        self.GATTServerEnhancedSendInstantValueIndicationRequestFrame = self.InitGATTServerEnhancedSendInstantValueIndicationRequest()
        self.GATTServerEnhancedSendAttributeReadStatusRequestFrame = self.InitGATTServerEnhancedSendAttributeReadStatusRequest()
        self.GATTServerEnhancedSendMultipleHandleValueNotificationRequestFrame = self.InitGATTServerEnhancedSendMultipleHandleValueNotificationRequest()
        self.GATTClientGetDatabaseHashRequestFrame = self.InitGATTClientGetDatabaseHashRequest()
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
        self.GATTDBDynamicEndDatabaseUpdateRequestFrame = self.InitGATTDBDynamicEndDatabaseUpdateRequest()
        self.GATTDBAttFindInformationRequestFrame = self.InitGATTDBAttFindInformationRequest()
        self.GATTDBAttFindByTypeValueRequestFrame = self.InitGATTDBAttFindByTypeValueRequest()
        self.GATTDBAttReadByTypeRequestFrame = self.InitGATTDBAttReadByTypeRequest()
        self.GATTDBAttReadRequestFrame = self.InitGATTDBAttReadRequest()
        self.GATTDBAttReadBlobRequestFrame = self.InitGATTDBAttReadBlobRequest()
        self.GATTDBAttReadMultipleRequestFrame = self.InitGATTDBAttReadMultipleRequest()
        self.GATTDBAttReadByGroupTypeRequestFrame = self.InitGATTDBAttReadByGroupTypeRequest()
        self.GATTDBAttWriteRequestFrame = self.InitGATTDBAttWriteRequest()
        self.GATTDBAttWriteCommandRequestFrame = self.InitGATTDBAttWriteCommandRequest()
        self.GATTDBAttSignedWriteCommandRequestFrame = self.InitGATTDBAttSignedWriteCommandRequest()
        self.GATTDBAttPrepareWriteRequestFrame = self.InitGATTDBAttPrepareWriteRequest()
        self.GATTDBAttExecuteWriteRequestFrame = self.InitGATTDBAttExecuteWriteRequest()
        self.GATTDBAttExecuteWriteFromQueueRequestFrame = self.InitGATTDBAttExecuteWriteFromQueueRequest()
        self.GATTDBAttPrepareNotificationIndicationRequestFrame = self.InitGATTDBAttPrepareNotificationIndicationRequest()
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
        self.GAPSendPeripheralSecurityRequestRequestFrame = self.InitGAPSendPeripheralSecurityRequestRequest()
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
        self.GAPReadFilterAcceptListSizeRequestFrame = self.InitGAPReadFilterAcceptListSizeRequest()
        self.GAPClearFilterAcceptListRequestFrame = self.InitGAPClearFilterAcceptListRequest()
        self.GAPAddDeviceToFilterAcceptListRequestFrame = self.InitGAPAddDeviceToFilterAcceptListRequest()
        self.GAPRemoveDeviceFromFilterAcceptListRequestFrame = self.InitGAPRemoveDeviceFromFilterAcceptListRequest()
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
        self.ControllerSetScanDupFiltModeRequestFrame = self.InitControllerSetScanDupFiltModeRequest()
        self.GAPReadControllerLocalRPARequestFrame = self.InitGAPReadControllerLocalRPARequest()
        self.GAPCheckNvmIndexRequestFrame = self.InitGAPCheckNvmIndexRequest()
        self.GAPGetDeviceIdFromConnHandleRequestFrame = self.InitGAPGetDeviceIdFromConnHandleRequest()
        self.GAPGetConnectionHandleFromDeviceIdFrame = self.InitGAPGetConnectionHandleFromDeviceId()
        self.GAPAdvIndexChangeRequestFrame = self.InitGAPAdvIndexChangeRequest()
        self.GAPGetHostVersionFrame = self.InitGAPGetHostVersion()
        self.GAPSetExtAdvertisingParametersRequestFrame = self.InitGAPSetExtAdvertisingParametersRequest()
        self.GAPStartExtAdvertisingRequestFrame = self.InitGAPStartExtAdvertisingRequest()
        self.GAPRemoveAdvertisingSetRequestFrame = self.InitGAPRemoveAdvertisingSetRequest()
        self.GAPStopExtAdvertisingRequestFrame = self.InitGAPStopExtAdvertisingRequest()
        self.GAPUpdatePeriodicAdvListRequestFrame = self.InitGAPUpdatePeriodicAdvListRequest()
        self.GAPSetPeriodicAdvParametersRequestFrame = self.InitGAPSetPeriodicAdvParametersRequest()
        self.GAPStartPeriodicAdvertisingRequestFrame = self.InitGAPStartPeriodicAdvertisingRequest()
        self.GAPStopPeriodicAdvertisingRequestFrame = self.InitGAPStopPeriodicAdvertisingRequest()
        self.GAPSetExtAdvertisingDataRequestFrame = self.InitGAPSetExtAdvertisingDataRequest()
        self.GAPSetPeriodicAdvertisingDataRequestFrame = self.InitGAPSetPeriodicAdvertisingDataRequest()
        self.GAPPeriodicAdvCreateSyncRequestFrame = self.InitGAPPeriodicAdvCreateSyncRequest()
        self.GAPPeriodicAdvTerminateSyncRequestFrame = self.InitGAPPeriodicAdvTerminateSyncRequest()
        self.GAPGenerateDHKeyV2RequestFrame = self.InitGAPGenerateDHKeyV2Request()
        self.GAPModifySleepClockAccuracyRequestFrame = self.InitGAPModifySleepClockAccuracyRequest()
        self.ControllerConfigureAdvCodingSchemeRequestFrame = self.InitControllerConfigureAdvCodingSchemeRequest()
        self.GAPSetConnectionlessCteTransmitParametersRequestFrame = self.InitGAPSetConnectionlessCteTransmitParametersRequest()
        self.GAPEnableConnectionlessCteTransmitRequestFrame = self.InitGAPEnableConnectionlessCteTransmitRequest()
        self.GAPEnableConnectionlessIqSamplingRequestFrame = self.InitGAPEnableConnectionlessIqSamplingRequest()
        self.GAPSetConnectionCteReceiveParametersRequestFrame = self.InitGAPSetConnectionCteReceiveParametersRequest()
        self.GAPSetConnectionCteTransmitParametersRequestFrame = self.InitGAPSetConnectionCteTransmitParametersRequest()
        self.GAPEnableConnectionCteRequestRequestFrame = self.InitGAPEnableConnectionCteRequestRequest()
        self.GAPEnableConnectionCteResponseRequestFrame = self.InitGAPEnableConnectionCteResponseRequest()
        self.GAPReadAntennaInformationRequestFrame = self.InitGAPReadAntennaInformationRequest()
        self.WritePublicDeviceAddressRequestFrame = self.InitWritePublicDeviceAddressRequest()
        self.GAPPeriodicAdvReceiveEnableRequestFrame = self.InitGAPPeriodicAdvReceiveEnableRequest()
        self.GAPPeriodicAdvReceiveDisableRequestFrame = self.InitGAPPeriodicAdvReceiveDisableRequest()
        self.GAPPeriodicAdvSyncTransferRequestFrame = self.InitGAPPeriodicAdvSyncTransferRequest()
        self.GAPPeriodicAdvSetInfoTransferRequestFrame = self.InitGAPPeriodicAdvSetInfoTransferRequest()
        self.GAPSetPeriodicAdvSyncTransferParamsRequestFrame = self.InitGAPSetPeriodicAdvSyncTransferParamsRequest()
        self.GAPSetDefaultPeriodicAdvSyncTransferParamsRequestFrame = self.InitGAPSetDefaultPeriodicAdvSyncTransferParamsRequest()
        self.GAPEnhancedReadTransmitPowerLevelRequestFrame = self.InitGAPEnhancedReadTransmitPowerLevelRequest()
        self.GAPReadRemoteTransmitPowerLevelRequestFrame = self.InitGAPReadRemoteTransmitPowerLevelRequest()
        self.GAPSetPathLossReportingParametersRequestFrame = self.InitGAPSetPathLossReportingParametersRequest()
        self.GAPEnablePathLossReportingRequestFrame = self.InitGAPEnablePathLossReportingRequest()
        self.GAPEnableTransmitPowerReportingRequestFrame = self.InitGAPEnableTransmitPowerReportingRequest()
        self.GAPEattConnectionRequestFrame = self.InitGAPEattConnectionRequest()
        self.GAPEattConnectionAcceptFrame = self.InitGAPEattConnectionAccept()
        self.GAPEattReconfigureRequestFrame = self.InitGAPEattReconfigureRequest()
        self.GAPEattSendCreditsRequestFrame = self.InitGAPEattSendCreditsRequest()
        self.FSCICPUResetRequestFrame = self.InitFSCICPUResetRequest()
        self.FSCIGetNumberOfFreeBuffersRequestFrame = self.InitFSCIGetNumberOfFreeBuffersRequest()
        self.FSCIAllowDeviceToSleepRequestFrame = self.InitFSCIAllowDeviceToSleepRequest()
        self.FSCIGetWakeupReasonRequestFrame = self.InitFSCIGetWakeupReasonRequest()
        self.FSCIGetNbuVersionRequestFrame = self.InitFSCIGetNbuVersionRequest()
        self.FSCINVGetNvVPSizeRequestFrame = self.InitFSCINVGetNvVPSizeRequest()
        self.FSCIGetNumberOfFreeBuffersResponseFrame = self.InitFSCIGetNumberOfFreeBuffersResponse()
        self.FSCIAckIndicationFrame = self.InitFSCIAckIndication()
        self.FSCIErrorIndicationFrame = self.InitFSCIErrorIndication()
        self.FSCIAllowDeviceToSleepConfirmFrame = self.InitFSCIAllowDeviceToSleepConfirm()
        self.FSCIWakeUpIndicationFrame = self.InitFSCIWakeUpIndication()
        self.FSCIGetWakeupReasonResponseFrame = self.InitFSCIGetWakeupReasonResponse()
        self.FSCIGetNbuVersionResponseFrame = self.InitFSCIGetNbuVersionResponse()
        self.L2CAPCBConfirmFrame = self.InitL2CAPCBConfirm()
        self.L2CAPCBLePsmConnectionRequestIndicationFrame = self.InitL2CAPCBLePsmConnectionRequestIndication()
        self.L2CAPCBLePsmConnectionCompleteIndicationFrame = self.InitL2CAPCBLePsmConnectionCompleteIndication()
        self.L2CAPCBLePsmDisconnectNotificationIndicationFrame = self.InitL2CAPCBLePsmDisconnectNotificationIndication()
        self.L2CAPCBNoPeerCreditsIndicationFrame = self.InitL2CAPCBNoPeerCreditsIndication()
        self.L2CAPCBLocalCreditsNotificationIndicationFrame = self.InitL2CAPCBLocalCreditsNotificationIndication()
        self.L2CAPCBLeCbDataIndicationFrame = self.InitL2CAPCBLeCbDataIndication()
        self.L2CAPCBErrorIndicationFrame = self.InitL2CAPCBErrorIndication()
        self.L2CAPCBChannelStatusNotificationIndicationFrame = self.InitL2CAPCBChannelStatusNotificationIndication()
        self.L2CAPCBLePsmEnhancedConnectRequestIndicationFrame = self.InitL2CAPCBLePsmEnhancedConnectRequestIndication()
        self.L2CAPCBLePsmEnhancedConnectionCompleteIndicationFrame = self.InitL2CAPCBLePsmEnhancedConnectionCompleteIndication()
        self.L2CAPCBEnhancedReconfigureRequestIndicationFrame = self.InitL2CAPCBEnhancedReconfigureRequestIndication()
        self.L2CAPCBEnhancedReconfigureResponseIndicationFrame = self.InitL2CAPCBEnhancedReconfigureResponseIndication()
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
        self.GATTClientMultipleHandleValueNotificationIndicationFrame = self.InitGATTClientMultipleHandleValueNotificationIndication()
        self.GATTClientProcedureReadMultipleVariableLenCharValuesIndicationFrame = self.InitGATTClientProcedureReadMultipleVariableLenCharValuesIndication()
        self.GATTClientIndicationIndicationFrame = self.InitGATTClientIndicationIndication()
        self.GATTServerMtuChangedIndicationFrame = self.InitGATTServerMtuChangedIndication()
        self.GATTServerHandleValueConfirmationIndicationFrame = self.InitGATTServerHandleValueConfirmationIndication()
        self.GATTServerAttributeWrittenIndicationFrame = self.InitGATTServerAttributeWrittenIndication()
        self.GATTServerCharacteristicCccdWrittenIndicationFrame = self.InitGATTServerCharacteristicCccdWrittenIndication()
        self.GATTServerAttributeWrittenWithoutResponseIndicationFrame = self.InitGATTServerAttributeWrittenWithoutResponseIndication()
        self.GATTServerErrorIndicationFrame = self.InitGATTServerErrorIndication()
        self.GATTServerLongCharacteristicWrittenIndicationFrame = self.InitGATTServerLongCharacteristicWrittenIndication()
        self.GATTServerAttributeReadIndicationFrame = self.InitGATTServerAttributeReadIndication()
        self.GATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndicationFrame = self.InitGATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication()
        self.GATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndicationFrame = self.InitGATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication()
        self.GATTClientProcedureEnhancedFindIncludedServicesIndicationFrame = self.InitGATTClientProcedureEnhancedFindIncludedServicesIndication()
        self.GATTClientProcedureEnhancedDiscoverAllCharacteristicsIndicationFrame = self.InitGATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication()
        self.GATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndicationFrame = self.InitGATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication()
        self.GATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndicationFrame = self.InitGATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndication()
        self.GATTClientProcedureEnhancedReadCharacteristicValueIndicationFrame = self.InitGATTClientProcedureEnhancedReadCharacteristicValueIndication()
        self.GATTClientProcedureEnhancedReadUsingCharacteristicUuidIndicationFrame = self.InitGATTClientProcedureEnhancedReadUsingCharacteristicUuidIndication()
        self.GATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndicationFrame = self.InitGATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication()
        self.GATTClientProcedureEnhancedWriteCharacteristicValueIndicationFrame = self.InitGATTClientProcedureEnhancedWriteCharacteristicValueIndication()
        self.GATTClientProcedureEnhancedReadCharacteristicDescriptorIndicationFrame = self.InitGATTClientProcedureEnhancedReadCharacteristicDescriptorIndication()
        self.GATTClientProcedureEnhancedWriteCharacteristicDescriptorIndicationFrame = self.InitGATTClientProcedureEnhancedWriteCharacteristicDescriptorIndication()
        self.GATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndicationFrame = self.InitGATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication()
        self.GATTClientEnhancedMultipleHandleValueNotificationIndicationFrame = self.InitGATTClientEnhancedMultipleHandleValueNotificationIndication()
        self.GATTClientEnhancedNotificationIndicationFrame = self.InitGATTClientEnhancedNotificationIndication()
        self.GATTClientEnhancedIndicationIndicationFrame = self.InitGATTClientEnhancedIndicationIndication()
        self.GATTServerEnhancedHandleValueConfirmationIndicationFrame = self.InitGATTServerEnhancedHandleValueConfirmationIndication()
        self.GATTServerEnhancedAttributeWrittenIndicationFrame = self.InitGATTServerEnhancedAttributeWrittenIndication()
        self.GATTServerEnhancedCharacteristicCccdWrittenIndicationFrame = self.InitGATTServerEnhancedCharacteristicCccdWrittenIndication()
        self.GATTServerEnhancedAttributeWrittenWithoutResponseIndicationFrame = self.InitGATTServerEnhancedAttributeWrittenWithoutResponseIndication()
        self.GATTServerEnhancedErrorIndicationFrame = self.InitGATTServerEnhancedErrorIndication()
        self.GATTServerEnhancedLongCharacteristicWrittenIndicationFrame = self.InitGATTServerEnhancedLongCharacteristicWrittenIndication()
        self.GATTServerEnhancedAttributeReadIndicationFrame = self.InitGATTServerEnhancedAttributeReadIndication()
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
        self.GATTDBAttConfirmFrame = self.InitGATTDBAttConfirm()
        self.GATTDBAttFindInformationIndicationFrame = self.InitGATTDBAttFindInformationIndication()
        self.GATTDBAttFindByTypeValueIndicationFrame = self.InitGATTDBAttFindByTypeValueIndication()
        self.GATTDBAttReadByTypeIndicationFrame = self.InitGATTDBAttReadByTypeIndication()
        self.GATTDBAttReadIndicationFrame = self.InitGATTDBAttReadIndication()
        self.GATTDBAttReadBlobIndicationFrame = self.InitGATTDBAttReadBlobIndication()
        self.GATTDBAttReadMultipleIndicationFrame = self.InitGATTDBAttReadMultipleIndication()
        self.GATTDBAttReadByGroupTypeIndicationFrame = self.InitGATTDBAttReadByGroupTypeIndication()
        self.GATTDBAttWriteIndicationFrame = self.InitGATTDBAttWriteIndication()
        self.GATTDBAttPrepareWriteIndicationFrame = self.InitGATTDBAttPrepareWriteIndication()
        self.GATTDBAttExecuteWriteIndicationFrame = self.InitGATTDBAttExecuteWriteIndication()
        self.GATTDBAttExecuteWriteFromQueueIndicationFrame = self.InitGATTDBAttExecuteWriteFromQueueIndication()
        self.GATTDBAttPrepareNotificationIndicationIndicationFrame = self.InitGATTDBAttPrepareNotificationIndicationIndication()
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
        self.GAPGenericEventFilterAcceptListSizeReadIndicationFrame = self.InitGAPGenericEventFilterAcceptListSizeReadIndication()
        self.GAPGenericEventDeviceAddedToFilterAcceptListIndicationFrame = self.InitGAPGenericEventDeviceAddedToFilterAcceptListIndication()
        self.GAPGenericEventDeviceRemovedFromFilterAcceptListIndicationFrame = self.InitGAPGenericEventDeviceRemovedFromFilterAcceptListIndication()
        self.GAPGenericEventFilterAcceptListClearedIndicationFrame = self.InitGAPGenericEventFilterAcceptListClearedIndication()
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
        self.GAPConnectionEventPeripheralSecurityRequestIndicationFrame = self.InitGAPConnectionEventPeripheralSecurityRequestIndication()
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
        self.GAPGenericEventExtAdvertisingParamSetupCompleteIndicationFrame = self.InitGAPGenericEventExtAdvertisingParamSetupCompleteIndication()
        self.GAPGenericEventExtAdvertisingDataSetupCompleteIndicationFrame = self.InitGAPGenericEventExtAdvertisingDataSetupCompleteIndication()
        self.GAPGenericEventPeriodicAdvParamSetupCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvParamSetupCompleteIndication()
        self.GAPGenericEventPeriodicAdvDataSetupCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvDataSetupCompleteIndication()
        self.GAPGenericEventPeriodicAdvListUpdateCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvListUpdateCompleteIndication()
        self.GAPAdvertisingEventExtAdvertisingStateChangedIndicationFrame = self.InitGAPAdvertisingEventExtAdvertisingStateChangedIndication()
        self.GAPAdvertisingEventAdvertisingSetTerminatedIndicationFrame = self.InitGAPAdvertisingEventAdvertisingSetTerminatedIndication()
        self.GAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndicationFrame = self.InitGAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndication()
        self.GAPAdvertisingEventExtScanReqReceivedIndicationFrame = self.InitGAPAdvertisingEventExtScanReqReceivedIndication()
        self.GAPGenericEventPeriodicAdvertisingStateChangedIndicationFrame = self.InitGAPGenericEventPeriodicAdvertisingStateChangedIndication()
        self.GAPScanningEventExtDeviceScannedIndicationFrame = self.InitGAPScanningEventExtDeviceScannedIndication()
        self.GAPScanningEventPeriodicAdvSyncEstablishedIndicationFrame = self.InitGAPScanningEventPeriodicAdvSyncEstablishedIndication()
        self.GAPScanningEventPeriodicAdvSyncTerminatedIndicationFrame = self.InitGAPScanningEventPeriodicAdvSyncTerminatedIndication()
        self.GAPScanningEventPeriodicAdvSyncLostIndicationFrame = self.InitGAPScanningEventPeriodicAdvSyncLostIndication()
        self.GAPScanningEventPeriodicDeviceScannedIndicationFrame = self.InitGAPScanningEventPeriodicDeviceScannedIndication()
        self.GAPGenericEventPeriodicAdvCreateSyncCancelledIndicationFrame = self.InitGAPGenericEventPeriodicAdvCreateSyncCancelledIndication()
        self.GAPConnectionEventChannelSelectionAlgorithm2IndicationFrame = self.InitGAPConnectionEventChannelSelectionAlgorithm2Indication()
        self.GAPGenericEventTxEntryAvailableIndicationFrame = self.InitGAPGenericEventTxEntryAvailableIndication()
        self.GAPGenericEventControllerLocalRPAReadIndicationFrame = self.InitGAPGenericEventControllerLocalRPAReadIndication()
        self.GAPCheckNvmIndexIndicationFrame = self.InitGAPCheckNvmIndexIndication()
        self.GAPGetDeviceIdFromConnHandleIndicationFrame = self.InitGAPGetDeviceIdFromConnHandleIndication()
        self.GAPGetConnectionHandleFromDeviceIdIndicationFrame = self.InitGAPGetConnectionHandleFromDeviceIdIndication()
        self.GAPPairingEventNoLTKIndicationFrame = self.InitGAPPairingEventNoLTKIndication()
        self.GAPPairingAlreadyStartedIndicationFrame = self.InitGAPPairingAlreadyStartedIndication()
        self.GAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndicationFrame = self.InitGAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndication()
        self.GAPGenericEventConnectionlessCteTransmitStateChangedIndicationFrame = self.InitGAPGenericEventConnectionlessCteTransmitStateChangedIndication()
        self.GAPGenericEventConnectionlessIqSamplingStateChangedIndicationFrame = self.InitGAPGenericEventConnectionlessIqSamplingStateChangedIndication()
        self.GAPGenericEventAntennaInformationReadIndicationFrame = self.InitGAPGenericEventAntennaInformationReadIndication()
        self.GAPScanningEventConnectionlessIqReportReceivedIndicationFrame = self.InitGAPScanningEventConnectionlessIqReportReceivedIndication()
        self.GAPConnectionEventIqReportReceivedIndicationFrame = self.InitGAPConnectionEventIqReportReceivedIndication()
        self.GAPConnectionEventCteRequestFailedIndicationFrame = self.InitGAPConnectionEventCteRequestFailedIndication()
        self.GAPConnectionEventCteReceiveParamsSetupCompleteIndicationFrame = self.InitGAPConnectionEventCteReceiveParamsSetupCompleteIndication()
        self.GAPConnectionEventCteTransmitParamsSetupCompleteIndicationFrame = self.InitGAPConnectionEventCteTransmitParamsSetupCompleteIndication()
        self.GAPConnectionEventCteReqStateChangedIndicationFrame = self.InitGAPConnectionEventCteReqStateChangedIndication()
        self.GAPConnectionEventCteRspStateChangedIndicationFrame = self.InitGAPConnectionEventCteRspStateChangedIndication()
        self.GAPGenericEventPeriodicAdvRecvEnableCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvRecvEnableCompleteIndication()
        self.GAPGenericEventPeriodicAdvSyncTransferCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvSyncTransferCompleteIndication()
        self.GAPGenericEventPeriodicAdvSetInfoTransferCompleteIndicationFrame = self.InitGAPGenericEventPeriodicAdvSetInfoTransferCompleteIndication()
        self.GAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndicationFrame = self.InitGAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndication()
        self.GAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndicationFrame = self.InitGAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndication()
        self.GAPScanningEventPeriodicAdvSyncTransferReceivedIndicationFrame = self.InitGAPScanningEventPeriodicAdvSyncTransferReceivedIndication()
        self.GAPConnectionEventPathLossThresholdIndicationFrame = self.InitGAPConnectionEventPathLossThresholdIndication()
        self.GAPConnectionEventTransmitPowerReportingIndicationFrame = self.InitGAPConnectionEventTransmitPowerReportingIndication()
        self.GAPConnectionEventEnhancedReadTransmitPowerLevelIndicationFrame = self.InitGAPConnectionEventEnhancedReadTransmitPowerLevelIndication()
        self.GAPConnectionEventPathLossReportingParamsSetupCompleteIndicationFrame = self.InitGAPConnectionEventPathLossReportingParamsSetupCompleteIndication()
        self.GAPConnectionEventPathLossReportingStateChangedIndicationFrame = self.InitGAPConnectionEventPathLossReportingStateChangedIndication()
        self.GAPConnectionEventTransmitPowerReportingStateChangedIndicationFrame = self.InitGAPConnectionEventTransmitPowerReportingStateChangedIndication()
        self.GAPConnectionEventEattConnectionRequestIndicationFrame = self.InitGAPConnectionEventEattConnectionRequestIndication()
        self.GAPConnectionEventEattConnectionCompleteIndicationFrame = self.InitGAPConnectionEventEattConnectionCompleteIndication()
        self.GAPConnectionEventEattReconfigureResponseIndicationFrame = self.InitGAPConnectionEventEattReconfigureResponseIndication()
        self.GAPConnectionEventEattBearerStatusNotificationIndicationFrame = self.InitGAPConnectionEventEattBearerStatusNotificationIndication()
        self.GAPGenericEventLeGenerateDhKeyCompleteIndicationFrame = self.InitGAPGenericEventLeGenerateDhKeyCompleteIndication()
        self.GAPGetHostVersionIndicationFrame = self.InitGAPGetHostVersionIndication()


    def InitL2CAPInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x41, 0x01, cmdParams)

    def InitL2CAPSendAttDataRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PacketLength = FsciParameter("PacketLength", 2)
        cmdParams.append(PacketLength)
        Packet = FsciParameter("Packet", 1, PacketLength)
        cmdParams.append(Packet)
        return FsciFrameDescription(0x41, 0x03, cmdParams)

    def InitL2CAPSendSmpDataRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PacketLength = FsciParameter("PacketLength", 2)
        cmdParams.append(PacketLength)
        Packet = FsciParameter("Packet", 1, PacketLength)
        cmdParams.append(Packet)
        return FsciFrameDescription(0x41, 0x04, cmdParams)

    def InitL2CAPRegisterAttCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x41, 0x06, cmdParams)

    def InitL2CAPRegisterSmpCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x41, 0x07, cmdParams)

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

    def InitL2CAPCBEnhancedConnectLePsmRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Mtu = FsciParameter("Mtu", 2)
        cmdParams.append(Mtu)
        InitialCredits = FsciParameter("InitialCredits", 2)
        cmdParams.append(InitialCredits)
        NoOfChannels = FsciParameter("NoOfChannels", 1)
        cmdParams.append(NoOfChannels)
        Cids = FsciParameter("Cids", 2, NoOfChannels)
        cmdParams.append(Cids)
        return FsciFrameDescription(0x42, 0x09, cmdParams)

    def InitL2CAPCBEnhancedChannelReconfigureRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        NewMtu = FsciParameter("NewMtu", 2)
        cmdParams.append(NewMtu)
        NewMps = FsciParameter("NewMps", 2)
        cmdParams.append(NewMps)
        NoOfChannels = FsciParameter("NoOfChannels", 1)
        cmdParams.append(NoOfChannels)
        Cids = FsciParameter("Cids", 2, NoOfChannels)
        cmdParams.append(Cids)
        return FsciFrameDescription(0x42, 0x0A, cmdParams)

    def InitL2CAPCBEnhancedCancelConnectionRequest(self):
        cmdParams = []
        LePsm = FsciParameter("LePsm", 2)
        cmdParams.append(LePsm)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        RefuseReason = FsciParameter("RefuseReason", 2)
        cmdParams.append(RefuseReason)
        NoOfChannels = FsciParameter("NoOfChannels", 1)
        cmdParams.append(NoOfChannels)
        Cids = FsciParameter("Cids", 2, NoOfChannels)
        cmdParams.append(Cids)
        return FsciFrameDescription(0x42, 0x0B, cmdParams)

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

    def InitGATTClientRegisterMultipleValueNotificationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x23, cmdParams)

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
        # not generated, pickle() is used instead; see frames.py
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
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x13, cmdParams)

    def InitGATTClientWriteCharacteristicDescriptorRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
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

    def InitGATTServerSendMultipleHandleValueNotificationRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x22, cmdParams)

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

    def InitGATTClientReadMultipleVariableCharacteristicValuesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x24, cmdParams)

    def InitGATTClientRegisterEnhancedProcedureCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x25, cmdParams)

    def InitGATTClientRegisterEnhancedNotificationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x26, cmdParams)

    def InitGATTClientRegisterEnhancedIndicationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x27, cmdParams)

    def InitGATTClientRegisterEnhancedMultipleValueNotificationCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x28, cmdParams)

    def InitGATTClientEnhancedDiscoverAllPrimaryServicesRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        MaxNbOfServices = FsciParameter("MaxNbOfServices", 1)
        cmdParams.append(MaxNbOfServices)
        return FsciFrameDescription(0x45, 0x29, cmdParams)

    def InitGATTClientEnhancedDiscoverPrimaryServicesByUuidRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2A, cmdParams)

    def InitGATTClientEnhancedFindIncludedServicesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2B, cmdParams)

    def InitGATTClientEnhancedDiscoverAllCharacteristicsOfServiceRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2C, cmdParams)

    def InitGATTClientEnhancedDiscoverCharacteristicOfServiceByUuidRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2D, cmdParams)

    def InitGATTClientEnhancedDiscoverAllCharacteristicDescriptorsRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2E, cmdParams)

    def InitGATTClientEnhancedReadCharacteristicValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x2F, cmdParams)

    def InitGATTClientEnhancedReadUsingCharacteristicUuidRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x30, cmdParams)

    def InitGATTClientEnhancedReadMultipleCharacteristicValuesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x31, cmdParams)

    def InitGATTClientEnhancedWriteCharacteristicValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x32, cmdParams)

    def InitGATTClientEnhancedReadCharacteristicDescriptorRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x33, cmdParams)

    def InitGATTClientEnhancedWriteCharacteristicDescriptorRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x34, cmdParams)

    def InitGATTClientEnhancedReadMultipleVariableCharacteristicValuesRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x45, 0x35, cmdParams)

    def InitGATTServerRegisterEnhancedCallbackRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x45, 0x36, cmdParams)

    def InitGATTServerEnhancedSendAttributeWrittenStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        AttributeHandle = FsciParameter("AttributeHandle", 2)
        cmdParams.append(AttributeHandle)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0x45, 0x37, cmdParams)

    def InitGATTServerEnhancedSendNotificationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x45, 0x38, cmdParams)

    def InitGATTServerEnhancedSendIndicationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x45, 0x39, cmdParams)

    def InitGATTServerEnhancedSendInstantValueNotificationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x3A, cmdParams)

    def InitGATTServerEnhancedSendInstantValueIndicationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Handle = FsciParameter("Handle", 2)
        cmdParams.append(Handle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0x3B, cmdParams)

    def InitGATTServerEnhancedSendAttributeReadStatusRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        AttributeHandle = FsciParameter("AttributeHandle", 2)
        cmdParams.append(AttributeHandle)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0x45, 0x3C, cmdParams)

    def InitGATTServerEnhancedSendMultipleHandleValueNotificationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        TotalLength = FsciParameter("TotalLength", 3)
        cmdParams.append(TotalLength)
        HandleLengthValueList = FsciParameter("HandleLengthValueList", 1, TotalLength)
        cmdParams.append(HandleLengthValueList)
        return FsciFrameDescription(0x45, 0x3D, cmdParams)

    def InitGATTClientGetDatabaseHashRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BondIdx = FsciParameter("BondIdx", 1)
        cmdParams.append(BondIdx)
        return FsciFrameDescription(0x45, 0x3E, cmdParams)

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
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x04, cmdParams)

    def InitGATTDBFindCharValueHandleInServiceRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x05, cmdParams)

    def InitGATTDBFindCccdHandleForCharValueHandleRequest(self):
        cmdParams = []
        CharValueHandle = FsciParameter("CharValueHandle", 2)
        cmdParams.append(CharValueHandle)
        return FsciFrameDescription(0x46, 0x06, cmdParams)

    def InitGATTDBFindDescriptorHandleForCharValueHandleRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x07, cmdParams)

    def InitGATTDBDynamicInitRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x08, cmdParams)

    def InitGATTDBDynamicReleaseDatabaseRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x09, cmdParams)

    def InitGATTDBDynamicAddPrimaryServiceDeclarationRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x0A, cmdParams)

    def InitGATTDBDynamicAddSecondaryServiceDeclarationRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x0B, cmdParams)

    def InitGATTDBDynamicAddIncludeDeclarationRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x0C, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationAndValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x0D, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDescriptorRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x0E, cmdParams)

    def InitGATTDBDynamicAddCccdRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x0F, cmdParams)

    def InitGATTDBDynamicAddCharacteristicDeclarationWithUniqueValueRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
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
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x46, 0x13, cmdParams)

    def InitGATTDBDynamicEndDatabaseUpdateRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x46, 0x14, cmdParams)

    def InitGATTDBAttFindInformationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_StartingHandle = FsciParameter("Params_StartingHandle", 2)
        cmdParams.append(Params_StartingHandle)
        Params_EndingHandle = FsciParameter("Params_EndingHandle", 2)
        cmdParams.append(Params_EndingHandle)
        return FsciFrameDescription(0x47, 0x01, cmdParams)

    def InitGATTDBAttFindByTypeValueRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_StartingHandle = FsciParameter("Params_StartingHandle", 2)
        cmdParams.append(Params_StartingHandle)
        Params_EndingHandle = FsciParameter("Params_EndingHandle", 2)
        cmdParams.append(Params_EndingHandle)
        Params_AttributeType = FsciParameter("Params_AttributeType", 2)
        cmdParams.append(Params_AttributeType)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x02, cmdParams)

    def InitGATTDBAttReadByTypeRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x47, 0x03, cmdParams)

    def InitGATTDBAttReadRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        return FsciFrameDescription(0x47, 0x04, cmdParams)

    def InitGATTDBAttReadBlobRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_ValueOffset = FsciParameter("Params_ValueOffset", 2)
        cmdParams.append(Params_ValueOffset)
        return FsciFrameDescription(0x47, 0x05, cmdParams)

    def InitGATTDBAttReadMultipleRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x47, 0x06, cmdParams)

    def InitGATTDBAttReadByGroupTypeRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x47, 0x07, cmdParams)

    def InitGATTDBAttWriteRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x08, cmdParams)

    def InitGATTDBAttWriteCommandRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x09, cmdParams)

    def InitGATTDBAttSignedWriteCommandRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        Params_AuthenticationSignature = FsciParameter("Params_AuthenticationSignature", 12)
        cmdParams.append(Params_AuthenticationSignature)
        return FsciFrameDescription(0x47, 0x0A, cmdParams)

    def InitGATTDBAttPrepareWriteRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_ValueOffset = FsciParameter("Params_ValueOffset", 2)
        cmdParams.append(Params_ValueOffset)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x0B, cmdParams)

    def InitGATTDBAttExecuteWriteRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_Flags = FsciParameter("Params_Flags", 1)
        cmdParams.append(Params_Flags)
        return FsciFrameDescription(0x47, 0x0C, cmdParams)

    def InitGATTDBAttExecuteWriteFromQueueRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_ValueOffset = FsciParameter("Params_ValueOffset", 2)
        cmdParams.append(Params_ValueOffset)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x0D, cmdParams)

    def InitGATTDBAttPrepareNotificationIndicationRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        return FsciFrameDescription(0x47, 0x0E, cmdParams)

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

    def InitGAPSendPeripheralSecurityRequestRequest(self):
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

    def InitGAPReadFilterAcceptListSizeRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x21, cmdParams)

    def InitGAPClearFilterAcceptListRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x22, cmdParams)

    def InitGAPAddDeviceToFilterAcceptListRequest(self):
        cmdParams = []
        AddressType = FsciParameter("AddressType", 1)
        cmdParams.append(AddressType)
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0x23, cmdParams)

    def InitGAPRemoveDeviceFromFilterAcceptListRequest(self):
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
        PeripheralLatency = FsciParameter("PeripheralLatency", 2)
        cmdParams.append(PeripheralLatency)
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

    def InitControllerSetScanDupFiltModeRequest(self):
        cmdParams = []
        Mode = FsciParameter("Mode", 1)
        cmdParams.append(Mode)
        return FsciFrameDescription(0x48, 0x46, cmdParams)

    def InitGAPReadControllerLocalRPARequest(self):
        cmdParams = []
        PeerIdentityAddressType = FsciParameter("PeerIdentityAddressType", 1)
        cmdParams.append(PeerIdentityAddressType)
        PeerIdentityAddress = FsciParameter("PeerIdentityAddress", 6)
        cmdParams.append(PeerIdentityAddress)
        return FsciFrameDescription(0x48, 0x47, cmdParams)

    def InitGAPCheckNvmIndexRequest(self):
        cmdParams = []
        NvmIndex = FsciParameter("NvmIndex", 1)
        cmdParams.append(NvmIndex)
        return FsciFrameDescription(0x48, 0x49, cmdParams)

    def InitGAPGetDeviceIdFromConnHandleRequest(self):
        cmdParams = []
        ConnHandle = FsciParameter("ConnHandle", 2)
        cmdParams.append(ConnHandle)
        return FsciFrameDescription(0x48, 0x4A, cmdParams)

    def InitGAPGetConnectionHandleFromDeviceId(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0x4B, cmdParams)

    def InitGAPAdvIndexChangeRequest(self):
        cmdParams = []
        AdvIndexType = FsciParameter("AdvIndexType", 1)
        cmdParams.append(AdvIndexType)
        AUserDefinedChannels = FsciParameter("AUserDefinedChannels", 3)
        cmdParams.append(AUserDefinedChannels)
        return FsciFrameDescription(0x48, 0x4C, cmdParams)

    def InitGAPGetHostVersion(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x4D, cmdParams)
    def InitGAPSetExtAdvertisingParametersRequest(self):
        cmdParams = []
        SID = FsciParameter("SID", 1)
        cmdParams.append(SID)
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        MinInterval = FsciParameter("MinInterval", 4)
        cmdParams.append(MinInterval)
        MaxInterval = FsciParameter("MaxInterval", 4)
        cmdParams.append(MaxInterval)
        OwnAddressType = FsciParameter("OwnAddressType", 1)
        cmdParams.append(OwnAddressType)
        OwnRandomAddress = FsciParameter("OwnRandomAddress", 6)
        cmdParams.append(OwnRandomAddress)
        PeerAddressType = FsciParameter("PeerAddressType", 1)
        cmdParams.append(PeerAddressType)
        PeerAddress = FsciParameter("PeerAddress", 6)
        cmdParams.append(PeerAddress)
        ChannelMap = FsciParameter("ChannelMap", 1)
        cmdParams.append(ChannelMap)
        FilterPolicy = FsciParameter("FilterPolicy", 1)
        cmdParams.append(FilterPolicy)
        AdvProperties = FsciParameter("AdvProperties", 2)
        cmdParams.append(AdvProperties)
        AdvTxPowerLevel = FsciParameter("AdvTxPowerLevel", 1)
        cmdParams.append(AdvTxPowerLevel)
        PrimaryAdvPHY = FsciParameter("PrimaryAdvPHY", 1)
        cmdParams.append(PrimaryAdvPHY)
        SecondaryAdvPHY = FsciParameter("SecondaryAdvPHY", 1)
        cmdParams.append(SecondaryAdvPHY)
        SecondaryAdvMaxSkip = FsciParameter("SecondaryAdvMaxSkip", 1)
        cmdParams.append(SecondaryAdvMaxSkip)
        EnableScanReqNotification = FsciParameter("EnableScanReqNotification", 1)
        cmdParams.append(EnableScanReqNotification)
        return FsciFrameDescription(0x48, 0x50, cmdParams)

    def InitGAPStartExtAdvertisingRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        Duration = FsciParameter("Duration", 2)
        cmdParams.append(Duration)
        MaxExtAdvEvents = FsciParameter("MaxExtAdvEvents", 1)
        cmdParams.append(MaxExtAdvEvents)
        return FsciFrameDescription(0x48, 0x51, cmdParams)

    def InitGAPRemoveAdvertisingSetRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x52, cmdParams)

    def InitGAPStopExtAdvertisingRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x53, cmdParams)

    def InitGAPUpdatePeriodicAdvListRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x54, cmdParams)

    def InitGAPSetPeriodicAdvParametersRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        IncludeTxPower = FsciParameter("IncludeTxPower", 1)
        cmdParams.append(IncludeTxPower)
        MinInterval = FsciParameter("MinInterval", 2)
        cmdParams.append(MinInterval)
        MaxInterval = FsciParameter("MaxInterval", 2)
        cmdParams.append(MaxInterval)
        return FsciFrameDescription(0x48, 0x55, cmdParams)

    def InitGAPStartPeriodicAdvertisingRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x56, cmdParams)

    def InitGAPStopPeriodicAdvertisingRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        return FsciFrameDescription(0x48, 0x57, cmdParams)

    def InitGAPSetExtAdvertisingDataRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x58, cmdParams)

    def InitGAPSetPeriodicAdvertisingDataRequest(self):
        cmdParams = []
        # not generated, pickle() is used instead; see frames.py
        return FsciFrameDescription(0x48, 0x59, cmdParams)

    def InitGAPPeriodicAdvCreateSyncRequest(self):
        cmdParams = []
        Options = FsciParameter("Options", 1)
        cmdParams.append(Options)
        SID = FsciParameter("SID", 1)
        cmdParams.append(SID)
        DeviceAddressType = FsciParameter("DeviceAddressType", 1)
        cmdParams.append(DeviceAddressType)
        DeviceAddress = FsciParameter("DeviceAddress", 6)
        cmdParams.append(DeviceAddress)
        SkipCount = FsciParameter("SkipCount", 2)
        cmdParams.append(SkipCount)
        Timeout = FsciParameter("Timeout", 2)
        cmdParams.append(Timeout)
        SyncCteType = FsciParameter("SyncCteType", 1)
        cmdParams.append(SyncCteType)
        return FsciFrameDescription(0x48, 0x5A, cmdParams)

    def InitGAPPeriodicAdvTerminateSyncRequest(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0x5B, cmdParams)

    def InitGAPGenerateDHKeyV2Request(self):
        cmdParams = []
        RemoteP256PublicKey = FsciParameter("RemoteP256PublicKey", 64)
        cmdParams.append(RemoteP256PublicKey)
        PrivateKeyType = FsciParameter("PrivateKeyType", 1)
        cmdParams.append(PrivateKeyType)
        return FsciFrameDescription(0x48, 0x65, cmdParams)

    def InitGAPModifySleepClockAccuracyRequest(self):
        cmdParams = []
        Action = FsciParameter("Action", 1)
        cmdParams.append(Action)
        return FsciFrameDescription(0x48, 0x66, cmdParams)

    def InitControllerConfigureAdvCodingSchemeRequest(self):
        cmdParams = []
        CodingScheme = FsciParameter("CodingScheme", 1)
        cmdParams.append(CodingScheme)
        return FsciFrameDescription(0x48, 0x5C, cmdParams)

    def InitGAPSetConnectionlessCteTransmitParametersRequest(self):
        cmdParams = []
        pTransmitParams_Handle = FsciParameter("pTransmitParams_Handle", 1)
        cmdParams.append(pTransmitParams_Handle)
        pTransmitParams_CteLength = FsciParameter("pTransmitParams_CteLength", 1)
        cmdParams.append(pTransmitParams_CteLength)
        pTransmitParams_CteType = FsciParameter("pTransmitParams_CteType", 1)
        cmdParams.append(pTransmitParams_CteType)
        pTransmitParams_CteCount = FsciParameter("pTransmitParams_CteCount", 1)
        cmdParams.append(pTransmitParams_CteCount)
        pTransmitParams_SwitchingPatternLength = FsciParameter("pTransmitParams_SwitchingPatternLength", 1)
        cmdParams.append(pTransmitParams_SwitchingPatternLength)
        pTransmitParams_AntennaIds = FsciParameter("pTransmitParams_AntennaIds", 1, pTransmitParams_SwitchingPatternLength)
        cmdParams.append(pTransmitParams_AntennaIds)
        return FsciFrameDescription(0x48, 0x5D, cmdParams)

    def InitGAPEnableConnectionlessCteTransmitRequest(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        Enable = FsciParameter("Enable", 1)
        cmdParams.append(Enable)
        return FsciFrameDescription(0x48, 0x5E, cmdParams)

    def InitGAPEnableConnectionlessIqSamplingRequest(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        pIqSamplingParams_IqSamplingEnable = FsciParameter("pIqSamplingParams_IqSamplingEnable", 1)
        cmdParams.append(pIqSamplingParams_IqSamplingEnable)
        pIqSamplingParams_SlotDurations = FsciParameter("pIqSamplingParams_SlotDurations", 1)
        cmdParams.append(pIqSamplingParams_SlotDurations)
        pIqSamplingParams_MaxSampledCtes = FsciParameter("pIqSamplingParams_MaxSampledCtes", 1)
        cmdParams.append(pIqSamplingParams_MaxSampledCtes)
        pIqSamplingParams_SwitchingPatternLength = FsciParameter("pIqSamplingParams_SwitchingPatternLength", 1)
        cmdParams.append(pIqSamplingParams_SwitchingPatternLength)
        pIqSamplingParams_AntennaIds = FsciParameter("pIqSamplingParams_AntennaIds", 1, pIqSamplingParams_SwitchingPatternLength)
        cmdParams.append(pIqSamplingParams_AntennaIds)
        return FsciFrameDescription(0x48, 0x5F, cmdParams)

    def InitGAPSetConnectionCteReceiveParametersRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        pReceiveParams_IqSamplingEnable = FsciParameter("pReceiveParams_IqSamplingEnable", 1)
        cmdParams.append(pReceiveParams_IqSamplingEnable)
        pReceiveParams_SlotDurations = FsciParameter("pReceiveParams_SlotDurations", 1)
        cmdParams.append(pReceiveParams_SlotDurations)
        pReceiveParams_SwitchingPatternLength = FsciParameter("pReceiveParams_SwitchingPatternLength", 1)
        cmdParams.append(pReceiveParams_SwitchingPatternLength)
        pReceiveParams_AntennaIds = FsciParameter("pReceiveParams_AntennaIds", 1, pReceiveParams_SwitchingPatternLength)
        cmdParams.append(pReceiveParams_AntennaIds)
        return FsciFrameDescription(0x48, 0x60, cmdParams)

    def InitGAPSetConnectionCteTransmitParametersRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        pTransmitParams_CteTypes = FsciParameter("pTransmitParams_CteTypes", 1)
        cmdParams.append(pTransmitParams_CteTypes)
        pTransmitParams_SwitchingPatternLength = FsciParameter("pTransmitParams_SwitchingPatternLength", 1)
        cmdParams.append(pTransmitParams_SwitchingPatternLength)
        pTransmitParams_AntennaIds = FsciParameter("pTransmitParams_AntennaIds", 1, pTransmitParams_SwitchingPatternLength)
        cmdParams.append(pTransmitParams_AntennaIds)
        return FsciFrameDescription(0x48, 0x61, cmdParams)

    def InitGAPEnableConnectionCteRequestRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        pCteReqEnableParams_CteReqEnable = FsciParameter("pCteReqEnableParams_CteReqEnable", 1)
        cmdParams.append(pCteReqEnableParams_CteReqEnable)
        pCteReqEnableParams_CteReqInterval = FsciParameter("pCteReqEnableParams_CteReqInterval", 2)
        cmdParams.append(pCteReqEnableParams_CteReqInterval)
        pCteReqEnableParams_RequestedCteLength = FsciParameter("pCteReqEnableParams_RequestedCteLength", 1)
        cmdParams.append(pCteReqEnableParams_RequestedCteLength)
        pCteReqEnableParams_RequestedCteType = FsciParameter("pCteReqEnableParams_RequestedCteType", 1)
        cmdParams.append(pCteReqEnableParams_RequestedCteType)
        return FsciFrameDescription(0x48, 0x62, cmdParams)

    def InitGAPEnableConnectionCteResponseRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Enable = FsciParameter("Enable", 1)
        cmdParams.append(Enable)
        return FsciFrameDescription(0x48, 0x63, cmdParams)

    def InitGAPReadAntennaInformationRequest(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x64, cmdParams)

    def InitWritePublicDeviceAddressRequest(self):
        cmdParams = []
        CPUReset = FsciParameter("CPUReset", 1)
        cmdParams.append(CPUReset)
        BluetoothAddress = FsciParameter("BluetoothAddress", 6)
        cmdParams.append(BluetoothAddress)
        return FsciFrameDescription(0x48, 0x48, cmdParams)

    def InitGAPPeriodicAdvReceiveEnableRequest(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0x67, cmdParams)

    def InitGAPPeriodicAdvReceiveDisableRequest(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0x68, cmdParams)

    def InitGAPPeriodicAdvSyncTransferRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ServiceData = FsciParameter("ServiceData", 2)
        cmdParams.append(ServiceData)
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0x69, cmdParams)

    def InitGAPPeriodicAdvSetInfoTransferRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        ServiceData = FsciParameter("ServiceData", 2)
        cmdParams.append(ServiceData)
        AdvHandle = FsciParameter("AdvHandle", 2)
        cmdParams.append(AdvHandle)
        return FsciFrameDescription(0x48, 0x6A, cmdParams)

    def InitGAPSetPeriodicAdvSyncTransferParamsRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Mode = FsciParameter("Mode", 1)
        cmdParams.append(Mode)
        Skip = FsciParameter("Skip", 2)
        cmdParams.append(Skip)
        SyncTimeout = FsciParameter("SyncTimeout", 2)
        cmdParams.append(SyncTimeout)
        CTEType = FsciParameter("CTEType", 1)
        cmdParams.append(CTEType)
        return FsciFrameDescription(0x48, 0x6B, cmdParams)

    def InitGAPSetDefaultPeriodicAdvSyncTransferParamsRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Mode = FsciParameter("Mode", 1)
        cmdParams.append(Mode)
        Skip = FsciParameter("Skip", 2)
        cmdParams.append(Skip)
        SyncTimeout = FsciParameter("SyncTimeout", 2)
        cmdParams.append(SyncTimeout)
        CTEType = FsciParameter("CTEType", 1)
        cmdParams.append(CTEType)
        return FsciFrameDescription(0x48, 0x6C, cmdParams)

    def InitGAPEnhancedReadTransmitPowerLevelRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Phy = FsciParameter("Phy", 1)
        cmdParams.append(Phy)
        return FsciFrameDescription(0x48, 0x6D, cmdParams)

    def InitGAPReadRemoteTransmitPowerLevelRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Phy = FsciParameter("Phy", 1)
        cmdParams.append(Phy)
        return FsciFrameDescription(0x48, 0x6E, cmdParams)

    def InitGAPSetPathLossReportingParametersRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        pPathLossReportingParams_HighThreshold = FsciParameter("pPathLossReportingParams_HighThreshold", 1)
        cmdParams.append(pPathLossReportingParams_HighThreshold)
        pPathLossReportingParams_HighHysteresis = FsciParameter("pPathLossReportingParams_HighHysteresis", 1)
        cmdParams.append(pPathLossReportingParams_HighHysteresis)
        pPathLossReportingParams_LowThreshold = FsciParameter("pPathLossReportingParams_LowThreshold", 1)
        cmdParams.append(pPathLossReportingParams_LowThreshold)
        pPathLossReportingParams_LowHysteresis = FsciParameter("pPathLossReportingParams_LowHysteresis", 1)
        cmdParams.append(pPathLossReportingParams_LowHysteresis)
        pPathLossReportingParams_minTimeSpent = FsciParameter("pPathLossReportingParams_minTimeSpent", 2)
        cmdParams.append(pPathLossReportingParams_minTimeSpent)
        return FsciFrameDescription(0x48, 0x6F, cmdParams)

    def InitGAPEnablePathLossReportingRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Enable = FsciParameter("Enable", 1)
        cmdParams.append(Enable)
        return FsciFrameDescription(0x48, 0x70, cmdParams)

    def InitGAPEnableTransmitPowerReportingRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        LocalEnable = FsciParameter("LocalEnable", 1)
        cmdParams.append(LocalEnable)
        RemoteEnable = FsciParameter("RemoteEnable", 1)
        cmdParams.append(RemoteEnable)
        return FsciFrameDescription(0x48, 0x71, cmdParams)

    def InitGAPEattConnectionRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        MTU = FsciParameter("MTU", 2)
        cmdParams.append(MTU)
        NoOfBearers = FsciParameter("NoOfBearers", 1)
        cmdParams.append(NoOfBearers)
        InitialCredits = FsciParameter("InitialCredits", 2)
        cmdParams.append(InitialCredits)
        AutoCreditsMgmt = FsciParameter("AutoCreditsMgmt", 1)
        cmdParams.append(AutoCreditsMgmt)
        return FsciFrameDescription(0x48, 0x72, cmdParams)

    def InitGAPEattConnectionAccept(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Accept = FsciParameter("Accept", 1)
        cmdParams.append(Accept)
        MTU = FsciParameter("MTU", 2)
        cmdParams.append(MTU)
        InitialCredits = FsciParameter("InitialCredits", 2)
        cmdParams.append(InitialCredits)
        AutoCreditsMgmt = FsciParameter("AutoCreditsMgmt", 1)
        cmdParams.append(AutoCreditsMgmt)
        return FsciFrameDescription(0x48, 0x73, cmdParams)

    def InitGAPEattReconfigureRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        MTU = FsciParameter("MTU", 2)
        cmdParams.append(MTU)
        MPS = FsciParameter("MPS", 2)
        cmdParams.append(MPS)
        NoOfBearers = FsciParameter("NoOfBearers", 1)
        cmdParams.append(NoOfBearers)
        BearerIds = FsciParameter("BearerIds", 1, NoOfBearers)
        cmdParams.append(BearerIds)
        return FsciFrameDescription(0x48, 0x74, cmdParams)

    def InitGAPEattSendCreditsRequest(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Credits = FsciParameter("Credits", 2)
        cmdParams.append(Credits)
        return FsciFrameDescription(0x48, 0x75, cmdParams)

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

    def InitFSCIGetNbuVersionRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA3, 0xB3, cmdParams)

    def InitFSCINVGetNvVPSizeRequest(self):
        cmdParams = []
        return FsciFrameDescription(0xA7, 0xE7, cmdParams)

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

    def InitFSCIGetNbuVersionResponse(self):
        cmdParams = []
        versionNumber = FsciParameter("versionNumber", 3)
        cmdParams.append(versionNumber)
        ShaLength = FsciParameter("ShaLength", 1)
        cmdParams.append(ShaLength)
        SHA = FsciParameter("SHA", 1)
        cmdParams.append(SHA)
        TagLength = FsciParameter("TagLength", 1)
        cmdParams.append(TagLength)
        TagString = FsciParameter("TagString", 1)
        cmdParams.append(TagString)
        return FsciFrameDescription(0xA4, 0xB3, cmdParams)

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

    def InitL2CAPCBChannelStatusNotificationIndication(self):
        cmdParams = []
        InformationIncluded = FsciParameter("InformationIncluded", 1)
        cmdParams.append(InformationIncluded)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        SrcCid = FsciParameter("SrcCid", 2)
        cmdParams.append(SrcCid)
        ChannelStatus = FsciParameter("ChannelStatus", 1)
        cmdParams.append(ChannelStatus)
        return FsciFrameDescription(0x42, 0x88, cmdParams)

    def InitL2CAPCBLePsmEnhancedConnectRequestIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x89, cmdParams)

    def InitL2CAPCBLePsmEnhancedConnectionCompleteIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x8A, cmdParams)

    def InitL2CAPCBEnhancedReconfigureRequestIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x8B, cmdParams)

    def InitL2CAPCBEnhancedReconfigureResponseIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x42, 0x8C, cmdParams)

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

    def InitGATTClientMultipleHandleValueNotificationIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x99, cmdParams)

    def InitGATTClientProcedureReadMultipleVariableLenCharValuesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9A, cmdParams)

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

    def InitGATTClientProcedureEnhancedDiscoverAllPrimaryServicesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9B, cmdParams)

    def InitGATTClientProcedureEnhancedDiscoverPrimaryServicesByUuidIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9C, cmdParams)

    def InitGATTClientProcedureEnhancedFindIncludedServicesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9D, cmdParams)

    def InitGATTClientProcedureEnhancedDiscoverAllCharacteristicsIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9E, cmdParams)

    def InitGATTClientProcedureEnhancedDiscoverCharacteristicByUuidIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0x9F, cmdParams)

    def InitGATTClientProcedureEnhancedDiscoverAllCharacteristicDescriptorsIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0xA0, cmdParams)

    def InitGATTClientProcedureEnhancedReadCharacteristicValueIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0xA1, cmdParams)

    def InitGATTClientProcedureEnhancedReadUsingCharacteristicUuidIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        NbOfReadBytes = FsciParameter("NbOfReadBytes", 2)
        cmdParams.append(NbOfReadBytes)
        ReadBytes = FsciParameter("ReadBytes", 1, NbOfReadBytes)
        cmdParams.append(ReadBytes)
        return FsciFrameDescription(0x45, 0xA2, cmdParams)

    def InitGATTClientProcedureEnhancedReadMultipleCharacteristicValuesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0xA3, cmdParams)

    def InitGATTClientProcedureEnhancedWriteCharacteristicValueIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        return FsciFrameDescription(0x45, 0xA4, cmdParams)

    def InitGATTClientProcedureEnhancedReadCharacteristicDescriptorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
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
        return FsciFrameDescription(0x45, 0xA5, cmdParams)

    def InitGATTClientProcedureEnhancedWriteCharacteristicDescriptorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        ProcedureResult = FsciParameter("ProcedureResult", 1)
        cmdParams.append(ProcedureResult)
        Error = FsciParameter("Error", 2)
        cmdParams.append(Error)
        return FsciFrameDescription(0x45, 0xA6, cmdParams)

    def InitGATTClientProcedureEnhancedReadMultipleVariableLenCharValuesIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0xA7, cmdParams)

    def InitGATTClientEnhancedMultipleHandleValueNotificationIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x45, 0xA8, cmdParams)

    def InitGATTClientEnhancedNotificationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        CharacteristicValueHandle = FsciParameter("CharacteristicValueHandle", 2)
        cmdParams.append(CharacteristicValueHandle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0xA9, cmdParams)

    def InitGATTClientEnhancedIndicationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        CharacteristicValueHandle = FsciParameter("CharacteristicValueHandle", 2)
        cmdParams.append(CharacteristicValueHandle)
        ValueLength = FsciParameter("ValueLength", 2)
        cmdParams.append(ValueLength)
        Value = FsciParameter("Value", 1, ValueLength)
        cmdParams.append(Value)
        return FsciFrameDescription(0x45, 0xAA, cmdParams)

    def InitGATTServerEnhancedHandleValueConfirmationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        return FsciFrameDescription(0x45, 0xAB, cmdParams)

    def InitGATTServerEnhancedAttributeWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        AttributeWrittenEvent_Handle = FsciParameter("AttributeWrittenEvent_Handle", 2)
        cmdParams.append(AttributeWrittenEvent_Handle)
        AttributeWrittenEvent_ValueLength = FsciParameter("AttributeWrittenEvent_ValueLength", 2)
        cmdParams.append(AttributeWrittenEvent_ValueLength)
        AttributeWrittenEvent_Value = FsciParameter("AttributeWrittenEvent_Value", 1, AttributeWrittenEvent_ValueLength)
        cmdParams.append(AttributeWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0xAC, cmdParams)

    def InitGATTServerEnhancedCharacteristicCccdWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        CharCccdWrittenEvent_Handle = FsciParameter("CharCccdWrittenEvent_Handle", 2)
        cmdParams.append(CharCccdWrittenEvent_Handle)
        CharCccdWrittenEvent_NewCccd = FsciParameter("CharCccdWrittenEvent_NewCccd", 1)
        cmdParams.append(CharCccdWrittenEvent_NewCccd)
        return FsciFrameDescription(0x45, 0xAD, cmdParams)

    def InitGATTServerEnhancedAttributeWrittenWithoutResponseIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        AttributeWrittenEvent_Handle = FsciParameter("AttributeWrittenEvent_Handle", 2)
        cmdParams.append(AttributeWrittenEvent_Handle)
        AttributeWrittenEvent_ValueLength = FsciParameter("AttributeWrittenEvent_ValueLength", 2)
        cmdParams.append(AttributeWrittenEvent_ValueLength)
        AttributeWrittenEvent_Value = FsciParameter("AttributeWrittenEvent_Value", 1, AttributeWrittenEvent_ValueLength)
        cmdParams.append(AttributeWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0xAE, cmdParams)

    def InitGATTServerEnhancedErrorIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        ProcedureError_ProcedureType = FsciParameter("ProcedureError_ProcedureType", 1)
        cmdParams.append(ProcedureError_ProcedureType)
        ProcedureError_Error = FsciParameter("ProcedureError_Error", 2)
        cmdParams.append(ProcedureError_Error)
        return FsciFrameDescription(0x45, 0xAF, cmdParams)

    def InitGATTServerEnhancedLongCharacteristicWrittenIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        LongCharacteristicWrittenEvent_Handle = FsciParameter("LongCharacteristicWrittenEvent_Handle", 2)
        cmdParams.append(LongCharacteristicWrittenEvent_Handle)
        LongCharacteristicWrittenEvent_ValueLength = FsciParameter("LongCharacteristicWrittenEvent_ValueLength", 2)
        cmdParams.append(LongCharacteristicWrittenEvent_ValueLength)
        LongCharacteristicWrittenEvent_Value = FsciParameter("LongCharacteristicWrittenEvent_Value", 1, LongCharacteristicWrittenEvent_ValueLength)
        cmdParams.append(LongCharacteristicWrittenEvent_Value)
        return FsciFrameDescription(0x45, 0xB0, cmdParams)

    def InitGATTServerEnhancedAttributeReadIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        AttributeReadEvent_Handle = FsciParameter("AttributeReadEvent_Handle", 2)
        cmdParams.append(AttributeReadEvent_Handle)
        return FsciFrameDescription(0x45, 0xB1, cmdParams)

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

    def InitGATTDBAttConfirm(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        return FsciFrameDescription(0x47, 0x80, cmdParams)

    def InitGATTDBAttFindInformationIndication(self):
        cmdParams = []
        Params_Format = FsciParameter("Params_Format", 1)
        cmdParams.append(Params_Format)
        Params_InformationDatadict = {}
        currentList = []
        Uuid16BitFormatHandleUuid16PairCount = FsciParameter("Uuid16BitFormatHandleUuid16PairCount", 1)
        currentList.append(Uuid16BitFormatHandleUuid16PairCount)
        HandleUuid16Handle = FsciParameter("HandleUuid16Handle", 2)
        currentList.append(HandleUuid16Handle)
        HandleUuid16Uuid16 = FsciParameter("HandleUuid16Uuid16", 2)
        currentList.append(HandleUuid16Uuid16)
        Params_InformationDatadict[0x01] = currentList
        currentList = []
        Uuid128BitFormatHandleUuid128PairCount = FsciParameter("Uuid128BitFormatHandleUuid128PairCount", 1)
        currentList.append(Uuid128BitFormatHandleUuid128PairCount)
        HandleUuid128Handle = FsciParameter("HandleUuid128Handle", 2)
        currentList.append(HandleUuid128Handle)
        HandleUuid128Uuid128 = FsciParameter("HandleUuid128Uuid128", 16)
        currentList.append(HandleUuid128Uuid128)
        Params_InformationDatadict[0x02] = currentList
        Params_InformationData = FsciParameter("Params_InformationData", 1, Params_Format, Params_InformationDatadict)
        cmdParams.append(Params_InformationData)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x81, cmdParams)

    def InitGATTDBAttFindByTypeValueIndication(self):
        cmdParams = []
        # not generated, cursor based approach in observer; see events.py
        return FsciFrameDescription(0x47, 0x82, cmdParams)

    def InitGATTDBAttReadByTypeIndication(self):
        cmdParams = []
        Params_Length = FsciParameter("Params_Length", 1)
        cmdParams.append(Params_Length)
        Params_AttributeDataListLength = FsciParameter("Params_AttributeDataListLength", 2)
        cmdParams.append(Params_AttributeDataListLength)
        Params_AttributeDataList = FsciParameter("Params_AttributeDataList", 1, Params_AttributeDataListLength)
        cmdParams.append(Params_AttributeDataList)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x83, cmdParams)

    def InitGATTDBAttReadIndication(self):
        cmdParams = []
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x84, cmdParams)

    def InitGATTDBAttReadBlobIndication(self):
        cmdParams = []
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x85, cmdParams)

    def InitGATTDBAttReadMultipleIndication(self):
        cmdParams = []
        Params_ListLength = FsciParameter("Params_ListLength", 2)
        cmdParams.append(Params_ListLength)
        Params_ListOfValues = FsciParameter("Params_ListOfValues", 1, Params_ListLength)
        cmdParams.append(Params_ListOfValues)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x86, cmdParams)

    def InitGATTDBAttReadByGroupTypeIndication(self):
        cmdParams = []
        Params_Length = FsciParameter("Params_Length", 1)
        cmdParams.append(Params_Length)
        Params_AttributeDataListLength = FsciParameter("Params_AttributeDataListLength", 2)
        cmdParams.append(Params_AttributeDataListLength)
        Params_AttributeDataList = FsciParameter("Params_AttributeDataList", 1, Params_AttributeDataListLength)
        cmdParams.append(Params_AttributeDataList)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x87, cmdParams)

    def InitGATTDBAttWriteIndication(self):
        cmdParams = []
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x88, cmdParams)

    def InitGATTDBAttPrepareWriteIndication(self):
        cmdParams = []
        Params_AttributeHandle = FsciParameter("Params_AttributeHandle", 2)
        cmdParams.append(Params_AttributeHandle)
        Params_ValueOffset = FsciParameter("Params_ValueOffset", 2)
        cmdParams.append(Params_ValueOffset)
        Params_AttributeLength = FsciParameter("Params_AttributeLength", 2)
        cmdParams.append(Params_AttributeLength)
        Params_AttributeValue = FsciParameter("Params_AttributeValue", 1, Params_AttributeLength)
        cmdParams.append(Params_AttributeValue)
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x89, cmdParams)

    def InitGATTDBAttExecuteWriteIndication(self):
        cmdParams = []
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x8A, cmdParams)

    def InitGATTDBAttExecuteWriteFromQueueIndication(self):
        cmdParams = []
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x8B, cmdParams)

    def InitGATTDBAttPrepareNotificationIndicationIndication(self):
        cmdParams = []
        ErrorAttributeHandle = FsciParameter("ErrorAttributeHandle", 2)
        cmdParams.append(ErrorAttributeHandle)
        return FsciFrameDescription(0x47, 0x8C, cmdParams)

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

    def InitGAPGenericEventFilterAcceptListSizeReadIndication(self):
        cmdParams = []
        FilterAcceptListSize = FsciParameter("FilterAcceptListSize", 1)
        cmdParams.append(FilterAcceptListSize)
        return FsciFrameDescription(0x48, 0x8E, cmdParams)

    def InitGAPGenericEventDeviceAddedToFilterAcceptListIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x8F, cmdParams)

    def InitGAPGenericEventDeviceRemovedFromFilterAcceptListIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0x90, cmdParams)

    def InitGAPGenericEventFilterAcceptListClearedIndication(self):
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
        ConnectionParameters_CentralClockAccuracy = FsciParameter("ConnectionParameters_CentralClockAccuracy", 1)
        cmdParams.append(ConnectionParameters_CentralClockAccuracy)
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

    def InitGAPConnectionEventPeripheralSecurityRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        PeripheralSecurityRequestParameters_BondAfterPairing = FsciParameter("PeripheralSecurityRequestParameters_BondAfterPairing", 1)
        cmdParams.append(PeripheralSecurityRequestParameters_BondAfterPairing)
        PeripheralSecurityRequestParameters_bAuthenticationRequired = FsciParameter("PeripheralSecurityRequestParameters_bAuthenticationRequired", 1)
        cmdParams.append(PeripheralSecurityRequestParameters_bAuthenticationRequired)
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
        ConnectionParameterUpdateRequest_PeripheralLatency = FsciParameter("ConnectionParameterUpdateRequest_PeripheralLatency", 2)
        cmdParams.append(ConnectionParameterUpdateRequest_PeripheralLatency)
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

    def InitGAPGenericEventExtAdvertisingParamSetupCompleteIndication(self):
        cmdParams = []
        SelectedTxPower = FsciParameter("SelectedTxPower", 1)
        cmdParams.append(SelectedTxPower)
        return FsciFrameDescription(0x48, 0xC1, cmdParams)

    def InitGAPGenericEventExtAdvertisingDataSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC2, cmdParams)

    def InitGAPGenericEventPeriodicAdvParamSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC3, cmdParams)

    def InitGAPGenericEventPeriodicAdvDataSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC4, cmdParams)

    def InitGAPGenericEventPeriodicAdvListUpdateCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC5, cmdParams)

    def InitGAPAdvertisingEventExtAdvertisingStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC6, cmdParams)

    def InitGAPAdvertisingEventAdvertisingSetTerminatedIndication(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        NbExtAdvEvents = FsciParameter("NbExtAdvEvents", 1)
        cmdParams.append(NbExtAdvEvents)
        return FsciFrameDescription(0x48, 0xC7, cmdParams)

    def InitGAPAdvertisingEventExtAdvertisingSetRemoveCompletedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xC8, cmdParams)

    def InitGAPAdvertisingEventExtScanReqReceivedIndication(self):
        cmdParams = []
        Handle = FsciParameter("Handle", 1)
        cmdParams.append(Handle)
        ScannerAddressType = FsciParameter("ScannerAddressType", 1)
        cmdParams.append(ScannerAddressType)
        ScannerAddress = FsciParameter("ScannerAddress", 6)
        cmdParams.append(ScannerAddress)
        ScannerAddressResolved = FsciParameter("ScannerAddressResolved", 1)
        cmdParams.append(ScannerAddressResolved)
        return FsciFrameDescription(0x48, 0xC9, cmdParams)

    def InitGAPGenericEventPeriodicAdvertisingStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xCA, cmdParams)

    def InitGAPScanningEventExtDeviceScannedIndication(self):
        cmdParams = []
        AddressType = FsciParameter("AddressType", 1)
        cmdParams.append(AddressType)
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        SID = FsciParameter("SID", 1)
        cmdParams.append(SID)
        AdvertisingAddressResolved = FsciParameter("AdvertisingAddressResolved", 1)
        cmdParams.append(AdvertisingAddressResolved)
        AdvEventProperties = FsciParameter("AdvEventProperties", 2)
        cmdParams.append(AdvEventProperties)
        Rssi = FsciParameter("Rssi", 1)
        cmdParams.append(Rssi)
        TxPower = FsciParameter("TxPower", 1)
        cmdParams.append(TxPower)
        PrimaryPHY = FsciParameter("PrimaryPHY", 1)
        cmdParams.append(PrimaryPHY)
        SecondaryPHY = FsciParameter("SecondaryPHY", 1)
        cmdParams.append(SecondaryPHY)
        PeriodicAdvInterval = FsciParameter("PeriodicAdvInterval", 2)
        cmdParams.append(PeriodicAdvInterval)
        DirectRpaUsed = FsciParameter("DirectRpaUsed", 1)
        cmdParams.append(DirectRpaUsed)
        DirectRpaType = FsciParameter("DirectRpaType", 1)
        cmdParams.append(DirectRpaType)
        DirectRpa = FsciParameter("DirectRpa", 6)
        cmdParams.append(DirectRpa)
        DataLength = FsciParameter("DataLength", 2)
        cmdParams.append(DataLength)
        Data = FsciParameter("Data", 1, DataLength)
        cmdParams.append(Data)
        return FsciFrameDescription(0x48, 0xCB, cmdParams)

    def InitGAPScanningEventPeriodicAdvSyncEstablishedIndication(self):
        cmdParams = []
        Status = FsciParameter("Status", 2)
        cmdParams.append(Status)
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0xCC, cmdParams)

    def InitGAPScanningEventPeriodicAdvSyncTerminatedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xCD, cmdParams)

    def InitGAPScanningEventPeriodicAdvSyncLostIndication(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0xCE, cmdParams)

    def InitGAPScanningEventPeriodicDeviceScannedIndication(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        Rssi = FsciParameter("Rssi", 1)
        cmdParams.append(Rssi)
        TxPower = FsciParameter("TxPower", 1)
        cmdParams.append(TxPower)
        DataLength = FsciParameter("DataLength", 2)
        cmdParams.append(DataLength)
        Data = FsciParameter("Data", 1, DataLength)
        cmdParams.append(Data)
        return FsciFrameDescription(0x48, 0xCF, cmdParams)

    def InitGAPGenericEventPeriodicAdvCreateSyncCancelledIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xD0, cmdParams)

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

    def InitGAPGenericEventControllerLocalRPAReadIndication(self):
        cmdParams = []
        Address = FsciParameter("Address", 6)
        cmdParams.append(Address)
        return FsciFrameDescription(0x48, 0xD3, cmdParams)

    def InitGAPCheckNvmIndexIndication(self):
        cmdParams = []
        IsFree = FsciParameter("IsFree", 1)
        cmdParams.append(IsFree)
        return FsciFrameDescription(0x48, 0xD4, cmdParams)

    def InitGAPGetDeviceIdFromConnHandleIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xD5, cmdParams)

    def InitGAPGetConnectionHandleFromDeviceIdIndication(self):
        cmdParams = []
        ConnectionHandle = FsciParameter("ConnectionHandle", 2)
        cmdParams.append(ConnectionHandle)
        return FsciFrameDescription(0x48, 0xD6, cmdParams)

    def InitGAPPairingEventNoLTKIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xD7, cmdParams)

    def InitGAPPairingAlreadyStartedIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        return FsciFrameDescription(0x48, 0xD8, cmdParams)

    def InitGAPGenericEventConnectionlessCteTransmitParamsSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xD9, cmdParams)

    def InitGAPGenericEventConnectionlessCteTransmitStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xDA, cmdParams)

    def InitGAPGenericEventConnectionlessIqSamplingStateChangedIndication(self):
        cmdParams = []
        SyncHandle = FsciParameter("SyncHandle", 2)
        cmdParams.append(SyncHandle)
        return FsciFrameDescription(0x48, 0xDB, cmdParams)

    def InitGAPGenericEventAntennaInformationReadIndication(self):
        cmdParams = []
        AntennaInformation_SupportedSwitchingSamplingRates = FsciParameter("AntennaInformation_SupportedSwitchingSamplingRates", 1)
        cmdParams.append(AntennaInformation_SupportedSwitchingSamplingRates)
        AntennaInformation_NumAntennae = FsciParameter("AntennaInformation_NumAntennae", 1)
        cmdParams.append(AntennaInformation_NumAntennae)
        AntennaInformation_MaxSwitchingPatternLength = FsciParameter("AntennaInformation_MaxSwitchingPatternLength", 1)
        cmdParams.append(AntennaInformation_MaxSwitchingPatternLength)
        AntennaInformation_MaxCteLength = FsciParameter("AntennaInformation_MaxCteLength", 1)
        cmdParams.append(AntennaInformation_MaxCteLength)
        return FsciFrameDescription(0x48, 0xDC, cmdParams)

    def InitGAPScanningEventConnectionlessIqReportReceivedIndication(self):
        cmdParams = []
        IqReport_SyncHandle = FsciParameter("IqReport_SyncHandle", 2)
        cmdParams.append(IqReport_SyncHandle)
        IqReport_ChannelIndex = FsciParameter("IqReport_ChannelIndex", 1)
        cmdParams.append(IqReport_ChannelIndex)
        IqReport_Rssi = FsciParameter("IqReport_Rssi", 2)
        cmdParams.append(IqReport_Rssi)
        IqReport_RssiAntennaId = FsciParameter("IqReport_RssiAntennaId", 1)
        cmdParams.append(IqReport_RssiAntennaId)
        IqReport_CteType = FsciParameter("IqReport_CteType", 1)
        cmdParams.append(IqReport_CteType)
        IqReport_SlotDurations = FsciParameter("IqReport_SlotDurations", 1)
        cmdParams.append(IqReport_SlotDurations)
        IqReport_PacketStatus = FsciParameter("IqReport_PacketStatus", 1)
        cmdParams.append(IqReport_PacketStatus)
        IqReport_PeriodicEventCounter = FsciParameter("IqReport_PeriodicEventCounter", 2)
        cmdParams.append(IqReport_PeriodicEventCounter)
        IqReport_sampleCount = FsciParameter("IqReport_sampleCount", 1)
        cmdParams.append(IqReport_sampleCount)
        IqReport_I_samples = FsciParameter("IqReport_I_samples", 1, IqReport_sampleCount)
        cmdParams.append(IqReport_I_samples)
        IqReport_Q_samples = FsciParameter("IqReport_Q_samples", 1, IqReport_sampleCount)
        cmdParams.append(IqReport_Q_samples)
        return FsciFrameDescription(0x48, 0xDD, cmdParams)

    def InitGAPConnectionEventIqReportReceivedIndication(self):
        cmdParams = []
        ConnIqReport_RxPhy = FsciParameter("ConnIqReport_RxPhy", 1)
        cmdParams.append(ConnIqReport_RxPhy)
        ConnIqReport_DataChannelIndex = FsciParameter("ConnIqReport_DataChannelIndex", 1)
        cmdParams.append(ConnIqReport_DataChannelIndex)
        ConnIqReport_Rssi = FsciParameter("ConnIqReport_Rssi", 2)
        cmdParams.append(ConnIqReport_Rssi)
        ConnIqReport_RssiAntennaId = FsciParameter("ConnIqReport_RssiAntennaId", 1)
        cmdParams.append(ConnIqReport_RssiAntennaId)
        ConnIqReport_CteType = FsciParameter("ConnIqReport_CteType", 1)
        cmdParams.append(ConnIqReport_CteType)
        ConnIqReport_SlotDurations = FsciParameter("ConnIqReport_SlotDurations", 1)
        cmdParams.append(ConnIqReport_SlotDurations)
        ConnIqReport_PacketStatus = FsciParameter("ConnIqReport_PacketStatus", 1)
        cmdParams.append(ConnIqReport_PacketStatus)
        ConnIqReport_ConnEventCounter = FsciParameter("ConnIqReport_ConnEventCounter", 2)
        cmdParams.append(ConnIqReport_ConnEventCounter)
        ConnIqReport_sampleCount = FsciParameter("ConnIqReport_sampleCount", 1)
        cmdParams.append(ConnIqReport_sampleCount)
        ConnIqReport_I_samples = FsciParameter("ConnIqReport_I_samples", 1, ConnIqReport_sampleCount)
        cmdParams.append(ConnIqReport_I_samples)
        ConnIqReport_Q_samples = FsciParameter("ConnIqReport_Q_samples", 1, ConnIqReport_sampleCount)
        cmdParams.append(ConnIqReport_Q_samples)
        return FsciFrameDescription(0x48, 0xDE, cmdParams)

    def InitGAPConnectionEventCteRequestFailedIndication(self):
        cmdParams = []
        CteRequestFailedEvent_Status = FsciParameter("CteRequestFailedEvent_Status", 2)
        cmdParams.append(CteRequestFailedEvent_Status)
        return FsciFrameDescription(0x48, 0xDF, cmdParams)

    def InitGAPConnectionEventCteReceiveParamsSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xE0, cmdParams)

    def InitGAPConnectionEventCteTransmitParamsSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xE1, cmdParams)

    def InitGAPConnectionEventCteReqStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xE2, cmdParams)

    def InitGAPConnectionEventCteRspStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xE3, cmdParams)

    def InitGAPGenericEventPeriodicAdvRecvEnableCompleteIndication(self):
        cmdParams = []
        PerAdvSyncTransferEnable = FsciParameter("PerAdvSyncTransferEnable", 2)
        cmdParams.append(PerAdvSyncTransferEnable)
        return FsciFrameDescription(0x48, 0xE4, cmdParams)

    def InitGAPGenericEventPeriodicAdvSyncTransferCompleteIndication(self):
        cmdParams = []
        PerAdvSyncTransfer_DeviceId = FsciParameter("PerAdvSyncTransfer_DeviceId", 1)
        cmdParams.append(PerAdvSyncTransfer_DeviceId)
        PerAdvSyncTransfer_Status = FsciParameter("PerAdvSyncTransfer_Status", 2)
        cmdParams.append(PerAdvSyncTransfer_Status)
        return FsciFrameDescription(0x48, 0xE5, cmdParams)

    def InitGAPGenericEventPeriodicAdvSetInfoTransferCompleteIndication(self):
        cmdParams = []
        PerAdvSetInfoTransfer_DeviceId = FsciParameter("PerAdvSetInfoTransfer_DeviceId", 1)
        cmdParams.append(PerAdvSetInfoTransfer_DeviceId)
        PerAdvSetInfoTransfer_Status = FsciParameter("PerAdvSetInfoTransfer_Status", 2)
        cmdParams.append(PerAdvSetInfoTransfer_Status)
        return FsciFrameDescription(0x48, 0xE6, cmdParams)

    def InitGAPGenericEventSetPeriodicAdvSyncTransferParamsCompleteIndication(self):
        cmdParams = []
        PerAdvSetSyncTransferParams_DeviceId = FsciParameter("PerAdvSetSyncTransferParams_DeviceId", 1)
        cmdParams.append(PerAdvSetSyncTransferParams_DeviceId)
        PerAdvSetSyncTransferParams_Status = FsciParameter("PerAdvSetSyncTransferParams_Status", 2)
        cmdParams.append(PerAdvSetSyncTransferParams_Status)
        return FsciFrameDescription(0x48, 0xE7, cmdParams)

    def InitGAPGenericEventSetDefaultPeriodicAdvSyncTransferParamsCompleteIndication(self):
        cmdParams = []
        PerAdvSetDefaultPerAdvSyncTransferParams = FsciParameter("PerAdvSetDefaultPerAdvSyncTransferParams", 2)
        cmdParams.append(PerAdvSetDefaultPerAdvSyncTransferParams)
        return FsciFrameDescription(0x48, 0xE8, cmdParams)

    def InitGAPScanningEventPeriodicAdvSyncTransferReceivedIndication(self):
        cmdParams = []
        PerAdvSyncTransferReceived_Status = FsciParameter("PerAdvSyncTransferReceived_Status", 2)
        cmdParams.append(PerAdvSyncTransferReceived_Status)
        PerAdvSyncTransferReceived_DeviceId = FsciParameter("PerAdvSyncTransferReceived_DeviceId", 1)
        cmdParams.append(PerAdvSyncTransferReceived_DeviceId)
        PerAdvSyncTransferReceived_ServiceData = FsciParameter("PerAdvSyncTransferReceived_ServiceData", 2)
        cmdParams.append(PerAdvSyncTransferReceived_ServiceData)
        PerAdvSyncTransferReceived_SyncHandle = FsciParameter("PerAdvSyncTransferReceived_SyncHandle", 2)
        cmdParams.append(PerAdvSyncTransferReceived_SyncHandle)
        PerAdvSyncTransferReceived_AdvSID = FsciParameter("PerAdvSyncTransferReceived_AdvSID", 1)
        cmdParams.append(PerAdvSyncTransferReceived_AdvSID)
        PerAdvSyncTransferReceived_AdvAddressType = FsciParameter("PerAdvSyncTransferReceived_AdvAddressType", 1)
        cmdParams.append(PerAdvSyncTransferReceived_AdvAddressType)
        PerAdvSyncTransferReceived_AdvAddress = FsciParameter("PerAdvSyncTransferReceived_AdvAddress", 6)
        cmdParams.append(PerAdvSyncTransferReceived_AdvAddress)
        PerAdvSyncTransferReceived_AdvPhy = FsciParameter("PerAdvSyncTransferReceived_AdvPhy", 1)
        cmdParams.append(PerAdvSyncTransferReceived_AdvPhy)
        PerAdvSyncTransferReceived_PeriodicAdvInt = FsciParameter("PerAdvSyncTransferReceived_PeriodicAdvInt", 2)
        cmdParams.append(PerAdvSyncTransferReceived_PeriodicAdvInt)
        PerAdvSyncTransferReceived_AdvClockAccuracy = FsciParameter("PerAdvSyncTransferReceived_AdvClockAccuracy", 1)
        cmdParams.append(PerAdvSyncTransferReceived_AdvClockAccuracy)
        return FsciFrameDescription(0x48, 0xE9, cmdParams)

    def InitGAPConnectionEventPathLossThresholdIndication(self):
        cmdParams = []
        PathLossThreshold_CurrentPathLoss = FsciParameter("PathLossThreshold_CurrentPathLoss", 1)
        cmdParams.append(PathLossThreshold_CurrentPathLoss)
        PathLossThreshold_ZoneEntered = FsciParameter("PathLossThreshold_ZoneEntered", 1)
        cmdParams.append(PathLossThreshold_ZoneEntered)
        return FsciFrameDescription(0x48, 0xEA, cmdParams)

    def InitGAPConnectionEventTransmitPowerReportingIndication(self):
        cmdParams = []
        TransmitPowerReporting_Reason = FsciParameter("TransmitPowerReporting_Reason", 1)
        cmdParams.append(TransmitPowerReporting_Reason)
        TransmitPowerReporting_Phy = FsciParameter("TransmitPowerReporting_Phy", 1)
        cmdParams.append(TransmitPowerReporting_Phy)
        TransmitPowerReporting_TxPowerLevel = FsciParameter("TransmitPowerReporting_TxPowerLevel", 1)
        cmdParams.append(TransmitPowerReporting_TxPowerLevel)
        TransmitPowerReporting_Flags = FsciParameter("TransmitPowerReporting_Flags", 1)
        cmdParams.append(TransmitPowerReporting_Flags)
        TransmitPowerReporting_Delta = FsciParameter("TransmitPowerReporting_Delta", 1)
        cmdParams.append(TransmitPowerReporting_Delta)
        return FsciFrameDescription(0x48, 0xEB, cmdParams)

    def InitGAPConnectionEventEnhancedReadTransmitPowerLevelIndication(self):
        cmdParams = []
        TransmitPowerInfo_Phy = FsciParameter("TransmitPowerInfo_Phy", 1)
        cmdParams.append(TransmitPowerInfo_Phy)
        TransmitPowerInfo_CurrTxPowerLevel = FsciParameter("TransmitPowerInfo_CurrTxPowerLevel", 1)
        cmdParams.append(TransmitPowerInfo_CurrTxPowerLevel)
        TransmitPowerInfo_MaxTxPowerLevel = FsciParameter("TransmitPowerInfo_MaxTxPowerLevel", 1)
        cmdParams.append(TransmitPowerInfo_MaxTxPowerLevel)
        return FsciFrameDescription(0x48, 0xEC, cmdParams)

    def InitGAPConnectionEventPathLossReportingParamsSetupCompleteIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xED, cmdParams)

    def InitGAPConnectionEventPathLossReportingStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xEE, cmdParams)

    def InitGAPConnectionEventTransmitPowerReportingStateChangedIndication(self):
        cmdParams = []
        return FsciFrameDescription(0x48, 0xEF, cmdParams)

    def InitGAPConnectionEventEattConnectionRequestIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        MTU = FsciParameter("MTU", 2)
        cmdParams.append(MTU)
        NoOfBearers = FsciParameter("NoOfBearers", 1)
        cmdParams.append(NoOfBearers)
        InitialCredits = FsciParameter("InitialCredits", 2)
        cmdParams.append(InitialCredits)
        return FsciFrameDescription(0x48, 0xF0, cmdParams)

    def InitGAPConnectionEventEattConnectionCompleteIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        MTU = FsciParameter("MTU", 2)
        cmdParams.append(MTU)
        NoOfBearers = FsciParameter("NoOfBearers", 1)
        cmdParams.append(NoOfBearers)
        BearerIDs = FsciParameter("BearerIDs", 1, NoOfBearers)
        cmdParams.append(BearerIDs)
        return FsciFrameDescription(0x48, 0xF1, cmdParams)

    def InitGAPConnectionEventEattReconfigureResponseIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        LocalMtu = FsciParameter("LocalMtu", 2)
        cmdParams.append(LocalMtu)
        NoOfBearers = FsciParameter("NoOfBearers", 1)
        cmdParams.append(NoOfBearers)
        BearerIDs = FsciParameter("BearerIDs", 1, NoOfBearers)
        cmdParams.append(BearerIDs)
        return FsciFrameDescription(0x48, 0xF2, cmdParams)

    def InitGAPConnectionEventEattBearerStatusNotificationIndication(self):
        cmdParams = []
        DeviceId = FsciParameter("DeviceId", 1)
        cmdParams.append(DeviceId)
        BearerId = FsciParameter("BearerId", 1)
        cmdParams.append(BearerId)
        Status = FsciParameter("Status", 1)
        cmdParams.append(Status)
        return FsciFrameDescription(0x48, 0xF3, cmdParams)

    def InitGAPGenericEventLeGenerateDhKeyCompleteIndication(self):
        cmdParams = []
        DHKey = FsciParameter("DHKey", 32)
        cmdParams.append(DHKey)
        return FsciFrameDescription(0x48, 0xF4, cmdParams)

    def InitGAPGetHostVersionIndication(self):
        cmdParams = []
        GapHostVersion_BleHostVerMajor = FsciParameter("GapHostVersion_BleHostVerMajor", 1)
        cmdParams.append(GapHostVersion_BleHostVerMajor)
        GapHostVersion_BleHostVerMinor = FsciParameter("GapHostVersion_BleHostVerMinor", 1)
        cmdParams.append(GapHostVersion_BleHostVerMinor)
        GapHostVersion_BleHostVerPatch = FsciParameter("GapHostVersion_BleHostVerPatch", 1)
        cmdParams.append(GapHostVersion_BleHostVerPatch)
        return FsciFrameDescription(0x48, 0xF5, cmdParams)
