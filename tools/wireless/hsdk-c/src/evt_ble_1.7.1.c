/* Source file generated from BLE_1.7.1.xml */
/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*==================================================================================================
Include Files
==================================================================================================*/
#include "cmd_ble_1.7.1.h"

/*==================================================================================================
Private Prototypes
==================================================================================================*/
#if FSCI_ENABLE
static memStatus_t Load_FSCIAckIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_FSCIErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_FSCIAllowDeviceToSleepConfirm(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_FSCIWakeUpIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_FSCIGetWakeupReasonResponse(bleEvtContainer_t *container, uint8_t *pPayload);
#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
static memStatus_t Load_L2CAPCBConfirm(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBLePsmConnectionRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBLePsmConnectionCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBLePsmDisconnectNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBNoPeerCreditsIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBLocalCreditsNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBLeCbDataIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_L2CAPCBErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
static memStatus_t Load_GATTConfirm(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTGetMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureExchangeMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureDiscoverAllPrimaryServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureDiscoverPrimaryServicesByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureFindIncludedServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicsIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureDiscoverCharacteristicByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureReadCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureReadUsingCharacteristicUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureReadMultipleCharacteristicValuesIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureWriteCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureReadCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientProcedureWriteCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTClientIndicationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerMtuChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerHandleValueConfirmationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerAttributeWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerCharacteristicCccdWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerAttributeWrittenWithoutResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerLongCharacteristicWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTServerAttributeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
static memStatus_t Load_GATTDBConfirm(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBReadAttributeIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBFindServiceHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBFindCharValueHandleInServiceIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBFindCccdHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBFindDescriptorHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddPrimaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddSecondaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddIncludeDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationAndValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddCccdIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GATTDBDynamicAddCharDescriptorWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
static memStatus_t Load_GAPConfirm(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPCheckNotificationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPCheckIndicationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPLoadKeysIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPLoadEncryptionInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPLoadCustomPeerInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPCheckIfBondedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGetBondedDevicesCountIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGetBondedDeviceNameIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventInitializationCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventInternalErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventAdvertisingSetupFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventAdvertisingParametersSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventAdvertisingDataSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventWhiteListSizeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventDeviceAddedToWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventDeviceRemovedFromWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventWhiteListClearedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventRandomAddressReadyIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventCreateConnectionCanceledIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventPublicAddressReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventAdvTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventPrivateResolvableAddressVerifiedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventRandomAddressSetIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPAdvertisingEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPAdvertisingEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPScanningEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPScanningEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPScanningEventDeviceScannedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventConnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPairingRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventSlaveSecurityRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPairingResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventAuthenticationRejectedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPasskeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventOobRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPasskeyDisplayIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventKeyExchangeRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventKeysReceivedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventLongTermKeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventEncryptionChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPairingCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventDisconnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventRssiReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventPowerReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventParameterUpdateRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventParameterUpdateCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventLeDataLengthChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventLeScOobDataRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventLeScDisplayNumericValueIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventLeScKeypressNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventControllerResetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPLeScPublicKeyRegeneratedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventLeScLocalOobDataIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventHostPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventControllerPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventTxPowerLevelSetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventLePhyEventIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGetBondedDevicesIdentityInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPControllerNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPBondCreatedIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventChannelMapSetIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventChannelMapReadIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventChannelMapReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPConnectionEventChannelSelectionAlgorithm2Indication(bleEvtContainer_t *container, uint8_t *pPayload);
static memStatus_t Load_GAPGenericEventTxEntryAvailableIndication(bleEvtContainer_t *container, uint8_t *pPayload);
#endif  /* GAP_ENABLE */

/*==================================================================================================
Private global variables declarations
==================================================================================================*/
static const bleEvtHandler_t evtHandlerTbl[] =
{
#if FSCI_ENABLE
	{FSCIAckIndication_FSCI_ID, Load_FSCIAckIndication},
	{FSCIErrorIndication_FSCI_ID, Load_FSCIErrorIndication},
	{FSCIAllowDeviceToSleepConfirm_FSCI_ID, Load_FSCIAllowDeviceToSleepConfirm},
	{FSCIWakeUpIndication_FSCI_ID, Load_FSCIWakeUpIndication},
	{FSCIGetWakeupReasonResponse_FSCI_ID, Load_FSCIGetWakeupReasonResponse},
#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
	{L2CAPCBConfirm_FSCI_ID, Load_L2CAPCBConfirm},
	{L2CAPCBLePsmConnectionRequestIndication_FSCI_ID, Load_L2CAPCBLePsmConnectionRequestIndication},
	{L2CAPCBLePsmConnectionCompleteIndication_FSCI_ID, Load_L2CAPCBLePsmConnectionCompleteIndication},
	{L2CAPCBLePsmDisconnectNotificationIndication_FSCI_ID, Load_L2CAPCBLePsmDisconnectNotificationIndication},
	{L2CAPCBNoPeerCreditsIndication_FSCI_ID, Load_L2CAPCBNoPeerCreditsIndication},
	{L2CAPCBLocalCreditsNotificationIndication_FSCI_ID, Load_L2CAPCBLocalCreditsNotificationIndication},
	{L2CAPCBLeCbDataIndication_FSCI_ID, Load_L2CAPCBLeCbDataIndication},
	{L2CAPCBErrorIndication_FSCI_ID, Load_L2CAPCBErrorIndication},
#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
	{GATTConfirm_FSCI_ID, Load_GATTConfirm},
	{GATTGetMtuIndication_FSCI_ID, Load_GATTGetMtuIndication},
	{GATTClientProcedureExchangeMtuIndication_FSCI_ID, Load_GATTClientProcedureExchangeMtuIndication},
	{GATTClientProcedureDiscoverAllPrimaryServicesIndication_FSCI_ID, Load_GATTClientProcedureDiscoverAllPrimaryServicesIndication},
	{GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_FSCI_ID, Load_GATTClientProcedureDiscoverPrimaryServicesByUuidIndication},
	{GATTClientProcedureFindIncludedServicesIndication_FSCI_ID, Load_GATTClientProcedureFindIncludedServicesIndication},
	{GATTClientProcedureDiscoverAllCharacteristicsIndication_FSCI_ID, Load_GATTClientProcedureDiscoverAllCharacteristicsIndication},
	{GATTClientProcedureDiscoverCharacteristicByUuidIndication_FSCI_ID, Load_GATTClientProcedureDiscoverCharacteristicByUuidIndication},
	{GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_FSCI_ID, Load_GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication},
	{GATTClientProcedureReadCharacteristicValueIndication_FSCI_ID, Load_GATTClientProcedureReadCharacteristicValueIndication},
	{GATTClientProcedureReadUsingCharacteristicUuidIndication_FSCI_ID, Load_GATTClientProcedureReadUsingCharacteristicUuidIndication},
	{GATTClientProcedureReadMultipleCharacteristicValuesIndication_FSCI_ID, Load_GATTClientProcedureReadMultipleCharacteristicValuesIndication},
	{GATTClientProcedureWriteCharacteristicValueIndication_FSCI_ID, Load_GATTClientProcedureWriteCharacteristicValueIndication},
	{GATTClientProcedureReadCharacteristicDescriptorIndication_FSCI_ID, Load_GATTClientProcedureReadCharacteristicDescriptorIndication},
	{GATTClientProcedureWriteCharacteristicDescriptorIndication_FSCI_ID, Load_GATTClientProcedureWriteCharacteristicDescriptorIndication},
	{GATTClientNotificationIndication_FSCI_ID, Load_GATTClientNotificationIndication},
	{GATTClientIndicationIndication_FSCI_ID, Load_GATTClientIndicationIndication},
	{GATTServerMtuChangedIndication_FSCI_ID, Load_GATTServerMtuChangedIndication},
	{GATTServerHandleValueConfirmationIndication_FSCI_ID, Load_GATTServerHandleValueConfirmationIndication},
	{GATTServerAttributeWrittenIndication_FSCI_ID, Load_GATTServerAttributeWrittenIndication},
	{GATTServerCharacteristicCccdWrittenIndication_FSCI_ID, Load_GATTServerCharacteristicCccdWrittenIndication},
	{GATTServerAttributeWrittenWithoutResponseIndication_FSCI_ID, Load_GATTServerAttributeWrittenWithoutResponseIndication},
	{GATTServerErrorIndication_FSCI_ID, Load_GATTServerErrorIndication},
	{GATTServerLongCharacteristicWrittenIndication_FSCI_ID, Load_GATTServerLongCharacteristicWrittenIndication},
	{GATTServerAttributeReadIndication_FSCI_ID, Load_GATTServerAttributeReadIndication},
#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
	{GATTDBConfirm_FSCI_ID, Load_GATTDBConfirm},
	{GATTDBReadAttributeIndication_FSCI_ID, Load_GATTDBReadAttributeIndication},
	{GATTDBFindServiceHandleIndication_FSCI_ID, Load_GATTDBFindServiceHandleIndication},
	{GATTDBFindCharValueHandleInServiceIndication_FSCI_ID, Load_GATTDBFindCharValueHandleInServiceIndication},
	{GATTDBFindCccdHandleForCharValueHandleIndication_FSCI_ID, Load_GATTDBFindCccdHandleForCharValueHandleIndication},
	{GATTDBFindDescriptorHandleForCharValueHandleIndication_FSCI_ID, Load_GATTDBFindDescriptorHandleForCharValueHandleIndication},
	{GATTDBDynamicAddPrimaryServiceDeclarationIndication_FSCI_ID, Load_GATTDBDynamicAddPrimaryServiceDeclarationIndication},
	{GATTDBDynamicAddSecondaryServiceDeclarationIndication_FSCI_ID, Load_GATTDBDynamicAddSecondaryServiceDeclarationIndication},
	{GATTDBDynamicAddIncludeDeclarationIndication_FSCI_ID, Load_GATTDBDynamicAddIncludeDeclarationIndication},
	{GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_FSCI_ID, Load_GATTDBDynamicAddCharacteristicDeclarationAndValueIndication},
	{GATTDBDynamicAddCharacteristicDescriptorIndication_FSCI_ID, Load_GATTDBDynamicAddCharacteristicDescriptorIndication},
	{GATTDBDynamicAddCccdIndication_FSCI_ID, Load_GATTDBDynamicAddCccdIndication},
	{GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_FSCI_ID, Load_GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication},
	{GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_FSCI_ID, Load_GATTDBDynamicAddCharDescriptorWithUniqueValueIndication},
#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
	{GAPConfirm_FSCI_ID, Load_GAPConfirm},
	{GAPCheckNotificationStatusIndication_FSCI_ID, Load_GAPCheckNotificationStatusIndication},
	{GAPCheckIndicationStatusIndication_FSCI_ID, Load_GAPCheckIndicationStatusIndication},
	{GAPLoadKeysIndication_FSCI_ID, Load_GAPLoadKeysIndication},
	{GAPLoadEncryptionInformationIndication_FSCI_ID, Load_GAPLoadEncryptionInformationIndication},
	{GAPLoadCustomPeerInformationIndication_FSCI_ID, Load_GAPLoadCustomPeerInformationIndication},
	{GAPCheckIfBondedIndication_FSCI_ID, Load_GAPCheckIfBondedIndication},
	{GAPGetBondedDevicesCountIndication_FSCI_ID, Load_GAPGetBondedDevicesCountIndication},
	{GAPGetBondedDeviceNameIndication_FSCI_ID, Load_GAPGetBondedDeviceNameIndication},
	{GAPGenericEventInitializationCompleteIndication_FSCI_ID, Load_GAPGenericEventInitializationCompleteIndication},
	{GAPGenericEventInternalErrorIndication_FSCI_ID, Load_GAPGenericEventInternalErrorIndication},
	{GAPGenericEventAdvertisingSetupFailedIndication_FSCI_ID, Load_GAPGenericEventAdvertisingSetupFailedIndication},
	{GAPGenericEventAdvertisingParametersSetupCompleteIndication_FSCI_ID, Load_GAPGenericEventAdvertisingParametersSetupCompleteIndication},
	{GAPGenericEventAdvertisingDataSetupCompleteIndication_FSCI_ID, Load_GAPGenericEventAdvertisingDataSetupCompleteIndication},
	{GAPGenericEventWhiteListSizeReadIndication_FSCI_ID, Load_GAPGenericEventWhiteListSizeReadIndication},
	{GAPGenericEventDeviceAddedToWhiteListIndication_FSCI_ID, Load_GAPGenericEventDeviceAddedToWhiteListIndication},
	{GAPGenericEventDeviceRemovedFromWhiteListIndication_FSCI_ID, Load_GAPGenericEventDeviceRemovedFromWhiteListIndication},
	{GAPGenericEventWhiteListClearedIndication_FSCI_ID, Load_GAPGenericEventWhiteListClearedIndication},
	{GAPGenericEventRandomAddressReadyIndication_FSCI_ID, Load_GAPGenericEventRandomAddressReadyIndication},
	{GAPGenericEventCreateConnectionCanceledIndication_FSCI_ID, Load_GAPGenericEventCreateConnectionCanceledIndication},
	{GAPGenericEventPublicAddressReadIndication_FSCI_ID, Load_GAPGenericEventPublicAddressReadIndication},
	{GAPGenericEventAdvTxPowerLevelReadIndication_FSCI_ID, Load_GAPGenericEventAdvTxPowerLevelReadIndication},
	{GAPGenericEventPrivateResolvableAddressVerifiedIndication_FSCI_ID, Load_GAPGenericEventPrivateResolvableAddressVerifiedIndication},
	{GAPGenericEventRandomAddressSetIndication_FSCI_ID, Load_GAPGenericEventRandomAddressSetIndication},
	{GAPAdvertisingEventStateChangedIndication_FSCI_ID, Load_GAPAdvertisingEventStateChangedIndication},
	{GAPAdvertisingEventCommandFailedIndication_FSCI_ID, Load_GAPAdvertisingEventCommandFailedIndication},
	{GAPScanningEventStateChangedIndication_FSCI_ID, Load_GAPScanningEventStateChangedIndication},
	{GAPScanningEventCommandFailedIndication_FSCI_ID, Load_GAPScanningEventCommandFailedIndication},
	{GAPScanningEventDeviceScannedIndication_FSCI_ID, Load_GAPScanningEventDeviceScannedIndication},
	{GAPConnectionEventConnectedIndication_FSCI_ID, Load_GAPConnectionEventConnectedIndication},
	{GAPConnectionEventPairingRequestIndication_FSCI_ID, Load_GAPConnectionEventPairingRequestIndication},
	{GAPConnectionEventSlaveSecurityRequestIndication_FSCI_ID, Load_GAPConnectionEventSlaveSecurityRequestIndication},
	{GAPConnectionEventPairingResponseIndication_FSCI_ID, Load_GAPConnectionEventPairingResponseIndication},
	{GAPConnectionEventAuthenticationRejectedIndication_FSCI_ID, Load_GAPConnectionEventAuthenticationRejectedIndication},
	{GAPConnectionEventPasskeyRequestIndication_FSCI_ID, Load_GAPConnectionEventPasskeyRequestIndication},
	{GAPConnectionEventOobRequestIndication_FSCI_ID, Load_GAPConnectionEventOobRequestIndication},
	{GAPConnectionEventPasskeyDisplayIndication_FSCI_ID, Load_GAPConnectionEventPasskeyDisplayIndication},
	{GAPConnectionEventKeyExchangeRequestIndication_FSCI_ID, Load_GAPConnectionEventKeyExchangeRequestIndication},
	{GAPConnectionEventKeysReceivedIndication_FSCI_ID, Load_GAPConnectionEventKeysReceivedIndication},
	{GAPConnectionEventLongTermKeyRequestIndication_FSCI_ID, Load_GAPConnectionEventLongTermKeyRequestIndication},
	{GAPConnectionEventEncryptionChangedIndication_FSCI_ID, Load_GAPConnectionEventEncryptionChangedIndication},
	{GAPConnectionEventPairingCompleteIndication_FSCI_ID, Load_GAPConnectionEventPairingCompleteIndication},
	{GAPConnectionEventDisconnectedIndication_FSCI_ID, Load_GAPConnectionEventDisconnectedIndication},
	{GAPConnectionEventRssiReadIndication_FSCI_ID, Load_GAPConnectionEventRssiReadIndication},
	{GAPConnectionEventTxPowerLevelReadIndication_FSCI_ID, Load_GAPConnectionEventTxPowerLevelReadIndication},
	{GAPConnectionEventPowerReadFailureIndication_FSCI_ID, Load_GAPConnectionEventPowerReadFailureIndication},
	{GAPConnectionEventParameterUpdateRequestIndication_FSCI_ID, Load_GAPConnectionEventParameterUpdateRequestIndication},
	{GAPConnectionEventParameterUpdateCompleteIndication_FSCI_ID, Load_GAPConnectionEventParameterUpdateCompleteIndication},
	{GAPConnectionEventLeDataLengthChangedIndication_FSCI_ID, Load_GAPConnectionEventLeDataLengthChangedIndication},
	{GAPConnectionEventLeScOobDataRequestIndication_FSCI_ID, Load_GAPConnectionEventLeScOobDataRequestIndication},
	{GAPConnectionEventLeScDisplayNumericValueIndication_FSCI_ID, Load_GAPConnectionEventLeScDisplayNumericValueIndication},
	{GAPConnectionEventLeScKeypressNotificationIndication_FSCI_ID, Load_GAPConnectionEventLeScKeypressNotificationIndication},
	{GAPGenericEventControllerResetCompleteIndication_FSCI_ID, Load_GAPGenericEventControllerResetCompleteIndication},
	{GAPLeScPublicKeyRegeneratedIndication_FSCI_ID, Load_GAPLeScPublicKeyRegeneratedIndication},
	{GAPGenericEventLeScLocalOobDataIndication_FSCI_ID, Load_GAPGenericEventLeScLocalOobDataIndication},
	{GAPGenericEventHostPrivacyStateChangedIndication_FSCI_ID, Load_GAPGenericEventHostPrivacyStateChangedIndication},
	{GAPGenericEventControllerPrivacyStateChangedIndication_FSCI_ID, Load_GAPGenericEventControllerPrivacyStateChangedIndication},
	{GAPGenericEventTxPowerLevelSetCompleteIndication_FSCI_ID, Load_GAPGenericEventTxPowerLevelSetCompleteIndication},
	{GAPGenericEventLePhyEventIndication_FSCI_ID, Load_GAPGenericEventLePhyEventIndication},
	{GAPGetBondedDevicesIdentityInformationIndication_FSCI_ID, Load_GAPGetBondedDevicesIdentityInformationIndication},
	{GAPControllerNotificationIndication_FSCI_ID, Load_GAPControllerNotificationIndication},
	{GAPBondCreatedIndication_FSCI_ID, Load_GAPBondCreatedIndication},
	{GAPGenericEventChannelMapSetIndication_FSCI_ID, Load_GAPGenericEventChannelMapSetIndication},
	{GAPConnectionEventChannelMapReadIndication_FSCI_ID, Load_GAPConnectionEventChannelMapReadIndication},
	{GAPConnectionEventChannelMapReadFailureIndication_FSCI_ID, Load_GAPConnectionEventChannelMapReadFailureIndication},
	{GAPConnectionEventChannelSelectionAlgorithm2Indication_FSCI_ID, Load_GAPConnectionEventChannelSelectionAlgorithm2Indication},
	{GAPGenericEventTxEntryAvailableIndication_FSCI_ID, Load_GAPGenericEventTxEntryAvailableIndication},
#endif  /* GAP_ENABLE */
};

/*==================================================================================================
Public Functions
==================================================================================================*/
#if FSCI_ENABLE
/*!*************************************************************************************************
\fn		static memStatus_t Load_FSCIAckIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	FSCI packet sent as acknowledgment to a received FSCI packet.
***************************************************************************************************/
static memStatus_t Load_FSCIAckIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	FSCIAckIndication_t *evt = &(container->Data.FSCIAckIndication);

	/* Store (OG, OC) in ID */
	container->id = FSCIAckIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(FSCIAckIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_FSCIErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	FSCI is reporting an error condition.
***************************************************************************************************/
static memStatus_t Load_FSCIErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	FSCIErrorIndication_t *evt = &(container->Data.FSCIErrorIndication);

	/* Store (OG, OC) in ID */
	container->id = FSCIErrorIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(FSCIErrorIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_FSCIAllowDeviceToSleepConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	FSCI-AllowDeviceToSleep.Confirm description
***************************************************************************************************/
static memStatus_t Load_FSCIAllowDeviceToSleepConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
{
	FSCIAllowDeviceToSleepConfirm_t *evt = &(container->Data.FSCIAllowDeviceToSleepConfirm);

	/* Store (OG, OC) in ID */
	container->id = FSCIAllowDeviceToSleepConfirm_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(FSCIAllowDeviceToSleepConfirm_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_FSCIWakeUpIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	FSCI-WakeUp.Indication description
***************************************************************************************************/
static memStatus_t Load_FSCIWakeUpIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	FSCIWakeUpIndication_t *evt = &(container->Data.FSCIWakeUpIndication);

	/* Store (OG, OC) in ID */
	container->id = FSCIWakeUpIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(FSCIWakeUpIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_FSCIGetWakeupReasonResponse(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	FSCI-GetWakeupReason.Response description
***************************************************************************************************/
static memStatus_t Load_FSCIGetWakeupReasonResponse(bleEvtContainer_t *container, uint8_t *pPayload)
{
	FSCIGetWakeupReasonResponse_t *evt = &(container->Data.FSCIGetWakeupReasonResponse);

	/* Store (OG, OC) in ID */
	container->id = FSCIGetWakeupReasonResponse_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(FSCIGetWakeupReasonResponse_t));

	return MEM_SUCCESS_c;
}

#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Status of the L2CAP request
***************************************************************************************************/
static memStatus_t Load_L2CAPCBConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBConfirm_t *evt = &(container->Data.L2CAPCBConfirm);

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBConfirm_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(L2CAPCBConfirm_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBLePsmConnectionRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - Connection request event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBLePsmConnectionRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBLePsmConnectionRequestIndication_t *evt = &(container->Data.L2CAPCBLePsmConnectionRequestIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBLePsmConnectionRequestIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbConnectionRequest.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbConnectionRequest.LePsm), pPayload + idx, sizeof(evt->LeCbConnectionRequest.LePsm)); idx += sizeof(evt->LeCbConnectionRequest.LePsm);
		FLib_MemCpy(&(evt->LeCbConnectionRequest.PeerMtu), pPayload + idx, sizeof(evt->LeCbConnectionRequest.PeerMtu)); idx += sizeof(evt->LeCbConnectionRequest.PeerMtu);
		FLib_MemCpy(&(evt->LeCbConnectionRequest.PeerMps), pPayload + idx, sizeof(evt->LeCbConnectionRequest.PeerMps)); idx += sizeof(evt->LeCbConnectionRequest.PeerMps);
		FLib_MemCpy(&(evt->LeCbConnectionRequest.InitialCredits), pPayload + idx, sizeof(evt->LeCbConnectionRequest.InitialCredits)); idx += sizeof(evt->LeCbConnectionRequest.InitialCredits);
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBLePsmConnectionCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - Connection complete event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBLePsmConnectionCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBLePsmConnectionCompleteIndication_t *evt = &(container->Data.L2CAPCBLePsmConnectionCompleteIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBLePsmConnectionCompleteIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbConnectionComplete.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbConnectionComplete.ChannelId), pPayload + idx, sizeof(evt->LeCbConnectionComplete.ChannelId)); idx += sizeof(evt->LeCbConnectionComplete.ChannelId);
		FLib_MemCpy(&(evt->LeCbConnectionComplete.PeerMtu), pPayload + idx, sizeof(evt->LeCbConnectionComplete.PeerMtu)); idx += sizeof(evt->LeCbConnectionComplete.PeerMtu);
		FLib_MemCpy(&(evt->LeCbConnectionComplete.PeerMps), pPayload + idx, sizeof(evt->LeCbConnectionComplete.PeerMps)); idx += sizeof(evt->LeCbConnectionComplete.PeerMps);
		FLib_MemCpy(&(evt->LeCbConnectionComplete.InitialCredits), pPayload + idx, sizeof(evt->LeCbConnectionComplete.InitialCredits)); idx += sizeof(evt->LeCbConnectionComplete.InitialCredits);
		FLib_MemCpy(&(evt->LeCbConnectionComplete.Result), pPayload + idx, 2); idx += 2;
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBLePsmDisconnectNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - Disconnection notification event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBLePsmDisconnectNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBLePsmDisconnectNotificationIndication_t *evt = &(container->Data.L2CAPCBLePsmDisconnectNotificationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBLePsmDisconnectNotificationIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbDisconnection.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbDisconnection.ChannelId), pPayload + idx, sizeof(evt->LeCbDisconnection.ChannelId)); idx += sizeof(evt->LeCbDisconnection.ChannelId);
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBNoPeerCreditsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - No peer credits event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBNoPeerCreditsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBNoPeerCreditsIndication_t *evt = &(container->Data.L2CAPCBNoPeerCreditsIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBNoPeerCreditsIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbNoPeerCredits.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbNoPeerCredits.ChannelId), pPayload + idx, sizeof(evt->LeCbNoPeerCredits.ChannelId)); idx += sizeof(evt->LeCbNoPeerCredits.ChannelId);
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBLocalCreditsNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - Local credits notification event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBLocalCreditsNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBLocalCreditsNotificationIndication_t *evt = &(container->Data.L2CAPCBLocalCreditsNotificationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBLocalCreditsNotificationIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbLocalCreditsNotification.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbLocalCreditsNotification.ChannelId), pPayload + idx, sizeof(evt->LeCbLocalCreditsNotification.ChannelId)); idx += sizeof(evt->LeCbLocalCreditsNotification.ChannelId);
		FLib_MemCpy(&(evt->LeCbLocalCreditsNotification.LocalCredits), pPayload + idx, sizeof(evt->LeCbLocalCreditsNotification.LocalCredits)); idx += sizeof(evt->LeCbLocalCreditsNotification.LocalCredits);
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBLeCbDataIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Data packet received through Credit Based Channel
***************************************************************************************************/
static memStatus_t Load_L2CAPCBLeCbDataIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBLeCbDataIndication_t *evt = &(container->Data.L2CAPCBLeCbDataIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBLeCbDataIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->SrcCid), pPayload + idx, sizeof(evt->SrcCid)); idx += sizeof(evt->SrcCid);
	FLib_MemCpy(&(evt->PacketLength), pPayload + idx, sizeof(evt->PacketLength)); idx += sizeof(evt->PacketLength);

	if (evt->PacketLength > 0)
	{
		evt->Packet = MEM_BufferAlloc(evt->PacketLength);

		if (!evt->Packet)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Packet = NULL;
	}

	FLib_MemCpy(evt->Packet, pPayload + idx, evt->PacketLength); idx += evt->PacketLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_L2CAPCBErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Credit Based - Internal error event
***************************************************************************************************/
static memStatus_t Load_L2CAPCBErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	L2CAPCBErrorIndication_t *evt = &(container->Data.L2CAPCBErrorIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = L2CAPCBErrorIndication_FSCI_ID;

	evt->InformationIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->InformationIncluded)
	{
		evt->LeCbError.DeviceId = pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->LeCbError.Error), pPayload + idx, 2); idx += 2;
	}


	return MEM_SUCCESS_c;
}

#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Status of the GATT request
***************************************************************************************************/
static memStatus_t Load_GATTConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTConfirm_t *evt = &(container->Data.GATTConfirm);

	/* Store (OG, OC) in ID */
	container->id = GATTConfirm_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTConfirm_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTGetMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies the MTU used with a given connected device
***************************************************************************************************/
static memStatus_t Load_GATTGetMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTGetMtuIndication_t *evt = &(container->Data.GATTGetMtuIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTGetMtuIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTGetMtuIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureExchangeMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the MTU exchange procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureExchangeMtuIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureExchangeMtuIndication_t *evt = &(container->Data.GATTClientProcedureExchangeMtuIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureExchangeMtuIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTClientProcedureExchangeMtuIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureDiscoverAllPrimaryServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Primary Service Discovery procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureDiscoverAllPrimaryServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureDiscoverAllPrimaryServicesIndication_t *evt = &(container->Data.GATTClientProcedureDiscoverAllPrimaryServicesIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureDiscoverAllPrimaryServicesIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->NbOfDiscoveredServices = pPayload[idx]; idx++;

	if (evt->NbOfDiscoveredServices > 0)
	{
		evt->DiscoveredServices = MEM_BufferAlloc(evt->NbOfDiscoveredServices * sizeof(evt->DiscoveredServices[0]));

		if (!evt->DiscoveredServices)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->DiscoveredServices = NULL;
	}


	for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
	{
		FLib_MemCpy(&(evt->DiscoveredServices[i].StartHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].StartHandle)); idx += sizeof(evt->DiscoveredServices[i].StartHandle);
		FLib_MemCpy(&(evt->DiscoveredServices[i].EndHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].EndHandle)); idx += sizeof(evt->DiscoveredServices[i].EndHandle);
		evt->DiscoveredServices[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->DiscoveredServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		evt->DiscoveredServices[i].NbOfCharacteristics = pPayload[idx]; idx++;

		if (evt->DiscoveredServices[i].NbOfCharacteristics > 0)
		{
			evt->DiscoveredServices[i].Characteristics = MEM_BufferAlloc(evt->DiscoveredServices[i].NbOfCharacteristics * sizeof(evt->DiscoveredServices[i].Characteristics[0]));

			if (!evt->DiscoveredServices[i].Characteristics)
			{
				MEM_BufferFree(evt->DiscoveredServices);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->DiscoveredServices[i].Characteristics = NULL;
		}


		for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
		{
			evt->DiscoveredServices[i].Characteristics[j].Properties = (Properties_t)pPayload[idx]; idx++;
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.Handle), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.Handle)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.Handle);
			evt->DiscoveredServices[i].Characteristics[j].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->DiscoveredServices[i].Characteristics[j].Value.UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength);
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength);

			if (evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength > 0)
			{
				evt->DiscoveredServices[i].Characteristics[j].Value.Value = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength);

				if (!evt->DiscoveredServices[i].Characteristics[j].Value.Value)
				{
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
					}
					MEM_BufferFree(evt->DiscoveredServices);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->DiscoveredServices[i].Characteristics[j].Value.Value = NULL;
			}

			FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Value, pPayload + idx, evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength); idx += evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength;
			evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors = pPayload[idx]; idx++;

			if (evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors > 0)
			{
				evt->DiscoveredServices[i].Characteristics[j].Descriptors = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors * sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[0]));

				if (!evt->DiscoveredServices[i].Characteristics[j].Descriptors)
				{
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
						}
					}
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
					}
					MEM_BufferFree(evt->DiscoveredServices);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->DiscoveredServices[i].Characteristics[j].Descriptors = NULL;
			}


			for (uint32_t k = 0; k < evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors; k++)
			{
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle);
				evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].UuidType = (UuidType_t)pPayload[idx]; idx++;

				switch (evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].UuidType)
				{
					case Uuid16Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
						break;

					case Uuid128Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
						break;

					case Uuid32Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
						break;
				}
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength);
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength);

				if (evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength > 0)
				{
					evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength);

					if (!evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value)
					{
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
							{
								MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors);
							}
						}
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
							{
								MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
							}
						}
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
						}
						MEM_BufferFree(evt->DiscoveredServices);
						return MEM_ALLOC_ERROR_c;
					}

				}
				else
				{
					evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value = NULL;
				}

				FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value, pPayload + idx, evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength); idx += evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength;
			}
		}
		evt->DiscoveredServices[i].NbOfIncludedServices = pPayload[idx]; idx++;

		if (evt->DiscoveredServices[i].NbOfIncludedServices > 0)
		{
			evt->DiscoveredServices[i].IncludedServices = MEM_BufferAlloc(evt->DiscoveredServices[i].NbOfIncludedServices * sizeof(evt->DiscoveredServices[i].IncludedServices[0]));

			if (!evt->DiscoveredServices[i].IncludedServices)
			{
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						for (uint32_t k = 0; k < evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors; k++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value);
						}
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors);
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
				}
				MEM_BufferFree(evt->DiscoveredServices);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->DiscoveredServices[i].IncludedServices = NULL;
		}


		for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfIncludedServices; j++)
		{
			FLib_MemCpy(&(evt->DiscoveredServices[i].IncludedServices[j].StartHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].IncludedServices[j].StartHandle)); idx += sizeof(evt->DiscoveredServices[i].IncludedServices[j].StartHandle);
			FLib_MemCpy(&(evt->DiscoveredServices[i].IncludedServices[j].EndHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].IncludedServices[j].EndHandle)); idx += sizeof(evt->DiscoveredServices[i].IncludedServices[j].EndHandle);
			evt->DiscoveredServices[i].IncludedServices[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->DiscoveredServices[i].IncludedServices[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			evt->DiscoveredServices[i].IncludedServices[j].NbOfCharacteristics = pPayload[idx]; idx++;
			evt->DiscoveredServices[i].IncludedServices[j].NbOfIncludedServices = pPayload[idx]; idx++;
		}
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureDiscoverPrimaryServicesByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Primary Service Discovery By UUID procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureDiscoverPrimaryServicesByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_t *evt = &(container->Data.GATTClientProcedureDiscoverPrimaryServicesByUuidIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->NbOfDiscoveredServices = pPayload[idx]; idx++;

	if (evt->NbOfDiscoveredServices > 0)
	{
		evt->DiscoveredServices = MEM_BufferAlloc(evt->NbOfDiscoveredServices * sizeof(evt->DiscoveredServices[0]));

		if (!evt->DiscoveredServices)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->DiscoveredServices = NULL;
	}


	for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
	{
		FLib_MemCpy(&(evt->DiscoveredServices[i].StartHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].StartHandle)); idx += sizeof(evt->DiscoveredServices[i].StartHandle);
		FLib_MemCpy(&(evt->DiscoveredServices[i].EndHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].EndHandle)); idx += sizeof(evt->DiscoveredServices[i].EndHandle);
		evt->DiscoveredServices[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->DiscoveredServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->DiscoveredServices[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		evt->DiscoveredServices[i].NbOfCharacteristics = pPayload[idx]; idx++;

		if (evt->DiscoveredServices[i].NbOfCharacteristics > 0)
		{
			evt->DiscoveredServices[i].Characteristics = MEM_BufferAlloc(evt->DiscoveredServices[i].NbOfCharacteristics * sizeof(evt->DiscoveredServices[i].Characteristics[0]));

			if (!evt->DiscoveredServices[i].Characteristics)
			{
				MEM_BufferFree(evt->DiscoveredServices);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->DiscoveredServices[i].Characteristics = NULL;
		}


		for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
		{
			evt->DiscoveredServices[i].Characteristics[j].Properties = (Properties_t)pPayload[idx]; idx++;
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.Handle), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.Handle)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.Handle);
			evt->DiscoveredServices[i].Characteristics[j].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->DiscoveredServices[i].Characteristics[j].Value.UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength);
			FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Value.MaxValueLength);

			if (evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength > 0)
			{
				evt->DiscoveredServices[i].Characteristics[j].Value.Value = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength);

				if (!evt->DiscoveredServices[i].Characteristics[j].Value.Value)
				{
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
					}
					MEM_BufferFree(evt->DiscoveredServices);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->DiscoveredServices[i].Characteristics[j].Value.Value = NULL;
			}

			FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Value.Value, pPayload + idx, evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength); idx += evt->DiscoveredServices[i].Characteristics[j].Value.ValueLength;
			evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors = pPayload[idx]; idx++;

			if (evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors > 0)
			{
				evt->DiscoveredServices[i].Characteristics[j].Descriptors = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors * sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[0]));

				if (!evt->DiscoveredServices[i].Characteristics[j].Descriptors)
				{
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
						}
					}
					for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
					}
					MEM_BufferFree(evt->DiscoveredServices);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->DiscoveredServices[i].Characteristics[j].Descriptors = NULL;
			}


			for (uint32_t k = 0; k < evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors; k++)
			{
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Handle);
				evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].UuidType = (UuidType_t)pPayload[idx]; idx++;

				switch (evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].UuidType)
				{
					case Uuid16Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
						break;

					case Uuid128Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
						break;

					case Uuid32Bits:
						FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
						break;
				}
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength);
				FLib_MemCpy(&(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength), pPayload + idx, sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength)); idx += sizeof(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].MaxValueLength);

				if (evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength > 0)
				{
					evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value = MEM_BufferAlloc(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength);

					if (!evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value)
					{
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
							{
								MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors);
							}
						}
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
							{
								MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
							}
						}
						for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
						}
						MEM_BufferFree(evt->DiscoveredServices);
						return MEM_ALLOC_ERROR_c;
					}

				}
				else
				{
					evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value = NULL;
				}

				FLib_MemCpy(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value, pPayload + idx, evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength); idx += evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].ValueLength;
			}
		}
		evt->DiscoveredServices[i].NbOfIncludedServices = pPayload[idx]; idx++;

		if (evt->DiscoveredServices[i].NbOfIncludedServices > 0)
		{
			evt->DiscoveredServices[i].IncludedServices = MEM_BufferAlloc(evt->DiscoveredServices[i].NbOfIncludedServices * sizeof(evt->DiscoveredServices[i].IncludedServices[0]));

			if (!evt->DiscoveredServices[i].IncludedServices)
			{
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						for (uint32_t k = 0; k < evt->DiscoveredServices[i].Characteristics[j].NbOfDescriptors; k++)
						{
							MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors[k].Value);
						}
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Descriptors);
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfCharacteristics; j++)
					{
						MEM_BufferFree(evt->DiscoveredServices[i].Characteristics[j].Value.Value);
					}
				}
				for (uint32_t i = 0; i < evt->NbOfDiscoveredServices; i++)
				{
					MEM_BufferFree(evt->DiscoveredServices[i].Characteristics);
				}
				MEM_BufferFree(evt->DiscoveredServices);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->DiscoveredServices[i].IncludedServices = NULL;
		}


		for (uint32_t j = 0; j < evt->DiscoveredServices[i].NbOfIncludedServices; j++)
		{
			FLib_MemCpy(&(evt->DiscoveredServices[i].IncludedServices[j].StartHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].IncludedServices[j].StartHandle)); idx += sizeof(evt->DiscoveredServices[i].IncludedServices[j].StartHandle);
			FLib_MemCpy(&(evt->DiscoveredServices[i].IncludedServices[j].EndHandle), pPayload + idx, sizeof(evt->DiscoveredServices[i].IncludedServices[j].EndHandle)); idx += sizeof(evt->DiscoveredServices[i].IncludedServices[j].EndHandle);
			evt->DiscoveredServices[i].IncludedServices[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->DiscoveredServices[i].IncludedServices[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->DiscoveredServices[i].IncludedServices[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			evt->DiscoveredServices[i].IncludedServices[j].NbOfCharacteristics = pPayload[idx]; idx++;
			evt->DiscoveredServices[i].IncludedServices[j].NbOfIncludedServices = pPayload[idx]; idx++;
		}
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureFindIncludedServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Find Included Services procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureFindIncludedServicesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureFindIncludedServicesIndication_t *evt = &(container->Data.GATTClientProcedureFindIncludedServicesIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureFindIncludedServicesIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	FLib_MemCpy(&(evt->Service.StartHandle), pPayload + idx, sizeof(evt->Service.StartHandle)); idx += sizeof(evt->Service.StartHandle);
	FLib_MemCpy(&(evt->Service.EndHandle), pPayload + idx, sizeof(evt->Service.EndHandle)); idx += sizeof(evt->Service.EndHandle);
	evt->Service.UuidType = (UuidType_t)pPayload[idx]; idx++;

	switch (evt->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
			break;
	}
	evt->Service.NbOfCharacteristics = pPayload[idx]; idx++;

	if (evt->Service.NbOfCharacteristics > 0)
	{
		evt->Service.Characteristics = MEM_BufferAlloc(evt->Service.NbOfCharacteristics * sizeof(evt->Service.Characteristics[0]));

		if (!evt->Service.Characteristics)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Service.Characteristics = NULL;
	}


	for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
	{
		evt->Service.Characteristics[i].Properties = (Properties_t)pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.Handle), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.Handle)); idx += sizeof(evt->Service.Characteristics[i].Value.Handle);
		evt->Service.Characteristics[i].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.ValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(evt->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.MaxValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(evt->Service.Characteristics[i].Value.MaxValueLength);

		if (evt->Service.Characteristics[i].Value.ValueLength > 0)
		{
			evt->Service.Characteristics[i].Value.Value = MEM_BufferAlloc(evt->Service.Characteristics[i].Value.ValueLength);

			if (!evt->Service.Characteristics[i].Value.Value)
			{
				MEM_BufferFree(evt->Service.Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Service.Characteristics[i].Value.Value = NULL;
		}

		FLib_MemCpy(evt->Service.Characteristics[i].Value.Value, pPayload + idx, evt->Service.Characteristics[i].Value.ValueLength); idx += evt->Service.Characteristics[i].Value.ValueLength;
		evt->Service.Characteristics[i].NbOfDescriptors = pPayload[idx]; idx++;

		if (evt->Service.Characteristics[i].NbOfDescriptors > 0)
		{
			evt->Service.Characteristics[i].Descriptors = MEM_BufferAlloc(evt->Service.Characteristics[i].NbOfDescriptors * sizeof(evt->Service.Characteristics[i].Descriptors[0]));

			if (!evt->Service.Characteristics[i].Descriptors)
			{
				for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
				{
					MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
				}
				MEM_BufferFree(evt->Service.Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Service.Characteristics[i].Descriptors = NULL;
		}


		for (uint32_t j = 0; j < evt->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].Handle), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].Handle);
			evt->Service.Characteristics[i].Descriptors[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].ValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength);

			if (evt->Service.Characteristics[i].Descriptors[j].ValueLength > 0)
			{
				evt->Service.Characteristics[i].Descriptors[j].Value = MEM_BufferAlloc(evt->Service.Characteristics[i].Descriptors[j].ValueLength);

				if (!evt->Service.Characteristics[i].Descriptors[j].Value)
				{
					for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Service.Characteristics[i].Descriptors);
					}
					for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
					}
					MEM_BufferFree(evt->Service.Characteristics);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->Service.Characteristics[i].Descriptors[j].Value = NULL;
			}

			FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Value, pPayload + idx, evt->Service.Characteristics[i].Descriptors[j].ValueLength); idx += evt->Service.Characteristics[i].Descriptors[j].ValueLength;
		}
	}
	evt->Service.NbOfIncludedServices = pPayload[idx]; idx++;

	if (evt->Service.NbOfIncludedServices > 0)
	{
		evt->Service.IncludedServices = MEM_BufferAlloc(evt->Service.NbOfIncludedServices * sizeof(evt->Service.IncludedServices[0]));

		if (!evt->Service.IncludedServices)
		{
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				for (uint32_t j = 0; j < evt->Service.Characteristics[i].NbOfDescriptors; j++)
				{
					MEM_BufferFree(evt->Service.Characteristics[i].Descriptors[j].Value);
				}
			}
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				MEM_BufferFree(evt->Service.Characteristics[i].Descriptors);
			}
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
			}
			MEM_BufferFree(evt->Service.Characteristics);
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Service.IncludedServices = NULL;
	}


	for (uint32_t i = 0; i < evt->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(&(evt->Service.IncludedServices[i].StartHandle), pPayload + idx, sizeof(evt->Service.IncludedServices[i].StartHandle)); idx += sizeof(evt->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(&(evt->Service.IncludedServices[i].EndHandle), pPayload + idx, sizeof(evt->Service.IncludedServices[i].EndHandle)); idx += sizeof(evt->Service.IncludedServices[i].EndHandle);
		evt->Service.IncludedServices[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		evt->Service.IncludedServices[i].NbOfCharacteristics = pPayload[idx]; idx++;
		evt->Service.IncludedServices[i].NbOfIncludedServices = pPayload[idx]; idx++;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Discovery procedure for a given service ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureDiscoverAllCharacteristicsIndication_t *evt = &(container->Data.GATTClientProcedureDiscoverAllCharacteristicsIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureDiscoverAllCharacteristicsIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	FLib_MemCpy(&(evt->Service.StartHandle), pPayload + idx, sizeof(evt->Service.StartHandle)); idx += sizeof(evt->Service.StartHandle);
	FLib_MemCpy(&(evt->Service.EndHandle), pPayload + idx, sizeof(evt->Service.EndHandle)); idx += sizeof(evt->Service.EndHandle);
	evt->Service.UuidType = (UuidType_t)pPayload[idx]; idx++;

	switch (evt->Service.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(evt->Service.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
			break;
	}
	evt->Service.NbOfCharacteristics = pPayload[idx]; idx++;

	if (evt->Service.NbOfCharacteristics > 0)
	{
		evt->Service.Characteristics = MEM_BufferAlloc(evt->Service.NbOfCharacteristics * sizeof(evt->Service.Characteristics[0]));

		if (!evt->Service.Characteristics)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Service.Characteristics = NULL;
	}


	for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
	{
		evt->Service.Characteristics[i].Properties = (Properties_t)pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.Handle), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.Handle)); idx += sizeof(evt->Service.Characteristics[i].Value.Handle);
		evt->Service.Characteristics[i].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Service.Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Service.Characteristics[i].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.ValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.ValueLength)); idx += sizeof(evt->Service.Characteristics[i].Value.ValueLength);
		FLib_MemCpy(&(evt->Service.Characteristics[i].Value.MaxValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Value.MaxValueLength)); idx += sizeof(evt->Service.Characteristics[i].Value.MaxValueLength);

		if (evt->Service.Characteristics[i].Value.ValueLength > 0)
		{
			evt->Service.Characteristics[i].Value.Value = MEM_BufferAlloc(evt->Service.Characteristics[i].Value.ValueLength);

			if (!evt->Service.Characteristics[i].Value.Value)
			{
				MEM_BufferFree(evt->Service.Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Service.Characteristics[i].Value.Value = NULL;
		}

		FLib_MemCpy(evt->Service.Characteristics[i].Value.Value, pPayload + idx, evt->Service.Characteristics[i].Value.ValueLength); idx += evt->Service.Characteristics[i].Value.ValueLength;
		evt->Service.Characteristics[i].NbOfDescriptors = pPayload[idx]; idx++;

		if (evt->Service.Characteristics[i].NbOfDescriptors > 0)
		{
			evt->Service.Characteristics[i].Descriptors = MEM_BufferAlloc(evt->Service.Characteristics[i].NbOfDescriptors * sizeof(evt->Service.Characteristics[i].Descriptors[0]));

			if (!evt->Service.Characteristics[i].Descriptors)
			{
				for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
				{
					MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
				}
				MEM_BufferFree(evt->Service.Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Service.Characteristics[i].Descriptors = NULL;
		}


		for (uint32_t j = 0; j < evt->Service.Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].Handle), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].Handle)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].Handle);
			evt->Service.Characteristics[i].Descriptors[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->Service.Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].ValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(&(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength), pPayload + idx, sizeof(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(evt->Service.Characteristics[i].Descriptors[j].MaxValueLength);

			if (evt->Service.Characteristics[i].Descriptors[j].ValueLength > 0)
			{
				evt->Service.Characteristics[i].Descriptors[j].Value = MEM_BufferAlloc(evt->Service.Characteristics[i].Descriptors[j].ValueLength);

				if (!evt->Service.Characteristics[i].Descriptors[j].Value)
				{
					for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Service.Characteristics[i].Descriptors);
					}
					for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
					}
					MEM_BufferFree(evt->Service.Characteristics);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->Service.Characteristics[i].Descriptors[j].Value = NULL;
			}

			FLib_MemCpy(evt->Service.Characteristics[i].Descriptors[j].Value, pPayload + idx, evt->Service.Characteristics[i].Descriptors[j].ValueLength); idx += evt->Service.Characteristics[i].Descriptors[j].ValueLength;
		}
	}
	evt->Service.NbOfIncludedServices = pPayload[idx]; idx++;

	if (evt->Service.NbOfIncludedServices > 0)
	{
		evt->Service.IncludedServices = MEM_BufferAlloc(evt->Service.NbOfIncludedServices * sizeof(evt->Service.IncludedServices[0]));

		if (!evt->Service.IncludedServices)
		{
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				for (uint32_t j = 0; j < evt->Service.Characteristics[i].NbOfDescriptors; j++)
				{
					MEM_BufferFree(evt->Service.Characteristics[i].Descriptors[j].Value);
				}
			}
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				MEM_BufferFree(evt->Service.Characteristics[i].Descriptors);
			}
			for (uint32_t i = 0; i < evt->Service.NbOfCharacteristics; i++)
			{
				MEM_BufferFree(evt->Service.Characteristics[i].Value.Value);
			}
			MEM_BufferFree(evt->Service.Characteristics);
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Service.IncludedServices = NULL;
	}


	for (uint32_t i = 0; i < evt->Service.NbOfIncludedServices; i++)
	{
		FLib_MemCpy(&(evt->Service.IncludedServices[i].StartHandle), pPayload + idx, sizeof(evt->Service.IncludedServices[i].StartHandle)); idx += sizeof(evt->Service.IncludedServices[i].StartHandle);
		FLib_MemCpy(&(evt->Service.IncludedServices[i].EndHandle), pPayload + idx, sizeof(evt->Service.IncludedServices[i].EndHandle)); idx += sizeof(evt->Service.IncludedServices[i].EndHandle);
		evt->Service.IncludedServices[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Service.IncludedServices[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Service.IncludedServices[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		evt->Service.IncludedServices[i].NbOfCharacteristics = pPayload[idx]; idx++;
		evt->Service.IncludedServices[i].NbOfIncludedServices = pPayload[idx]; idx++;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureDiscoverCharacteristicByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Discovery procedure for a given service (with a given UUID) ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureDiscoverCharacteristicByUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureDiscoverCharacteristicByUuidIndication_t *evt = &(container->Data.GATTClientProcedureDiscoverCharacteristicByUuidIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureDiscoverCharacteristicByUuidIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->NbOfCharacteristics = pPayload[idx]; idx++;

	if (evt->NbOfCharacteristics > 0)
	{
		evt->Characteristics = MEM_BufferAlloc(evt->NbOfCharacteristics * sizeof(evt->Characteristics[0]));

		if (!evt->Characteristics)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristics = NULL;
	}


	for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
	{
		evt->Characteristics[i].Properties = (Properties_t)pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->Characteristics[i].Value.Handle), pPayload + idx, sizeof(evt->Characteristics[i].Value.Handle)); idx += sizeof(evt->Characteristics[i].Value.Handle);
		evt->Characteristics[i].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Characteristics[i].Value.ValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Value.ValueLength)); idx += sizeof(evt->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(&(evt->Characteristics[i].Value.MaxValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Value.MaxValueLength)); idx += sizeof(evt->Characteristics[i].Value.MaxValueLength);

		if (evt->Characteristics[i].Value.ValueLength > 0)
		{
			evt->Characteristics[i].Value.Value = MEM_BufferAlloc(evt->Characteristics[i].Value.ValueLength);

			if (!evt->Characteristics[i].Value.Value)
			{
				MEM_BufferFree(evt->Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristics[i].Value.Value = NULL;
		}

		FLib_MemCpy(evt->Characteristics[i].Value.Value, pPayload + idx, evt->Characteristics[i].Value.ValueLength); idx += evt->Characteristics[i].Value.ValueLength;
		evt->Characteristics[i].NbOfDescriptors = pPayload[idx]; idx++;

		if (evt->Characteristics[i].NbOfDescriptors > 0)
		{
			evt->Characteristics[i].Descriptors = MEM_BufferAlloc(evt->Characteristics[i].NbOfDescriptors * sizeof(evt->Characteristics[i].Descriptors[0]));

			if (!evt->Characteristics[i].Descriptors)
			{
				for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
				{
					MEM_BufferFree(evt->Characteristics[i].Value.Value);
				}
				MEM_BufferFree(evt->Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristics[i].Descriptors = NULL;
		}


		for (uint32_t j = 0; j < evt->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].Handle), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(evt->Characteristics[i].Descriptors[j].Handle);
			evt->Characteristics[i].Descriptors[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].ValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(evt->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].MaxValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(evt->Characteristics[i].Descriptors[j].MaxValueLength);

			if (evt->Characteristics[i].Descriptors[j].ValueLength > 0)
			{
				evt->Characteristics[i].Descriptors[j].Value = MEM_BufferAlloc(evt->Characteristics[i].Descriptors[j].ValueLength);

				if (!evt->Characteristics[i].Descriptors[j].Value)
				{
					for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Characteristics[i].Descriptors);
					}
					for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Characteristics[i].Value.Value);
					}
					MEM_BufferFree(evt->Characteristics);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->Characteristics[i].Descriptors[j].Value = NULL;
			}

			FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Value, pPayload + idx, evt->Characteristics[i].Descriptors[j].ValueLength); idx += evt->Characteristics[i].Descriptors[j].ValueLength;
		}
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Descriptor Discovery procedure for a given characteristic ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_t *evt = &(container->Data.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->Characteristic.Properties = (Properties_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Characteristic.Value.Handle), pPayload + idx, sizeof(evt->Characteristic.Value.Handle)); idx += sizeof(evt->Characteristic.Value.Handle);
	evt->Characteristic.Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

	switch (evt->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
			break;
	}
	FLib_MemCpy(&(evt->Characteristic.Value.ValueLength), pPayload + idx, sizeof(evt->Characteristic.Value.ValueLength)); idx += sizeof(evt->Characteristic.Value.ValueLength);
	FLib_MemCpy(&(evt->Characteristic.Value.MaxValueLength), pPayload + idx, sizeof(evt->Characteristic.Value.MaxValueLength)); idx += sizeof(evt->Characteristic.Value.MaxValueLength);

	if (evt->Characteristic.Value.ValueLength > 0)
	{
		evt->Characteristic.Value.Value = MEM_BufferAlloc(evt->Characteristic.Value.ValueLength);

		if (!evt->Characteristic.Value.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristic.Value.Value = NULL;
	}

	FLib_MemCpy(evt->Characteristic.Value.Value, pPayload + idx, evt->Characteristic.Value.ValueLength); idx += evt->Characteristic.Value.ValueLength;
	evt->Characteristic.NbOfDescriptors = pPayload[idx]; idx++;

	if (evt->Characteristic.NbOfDescriptors > 0)
	{
		evt->Characteristic.Descriptors = MEM_BufferAlloc(evt->Characteristic.NbOfDescriptors * sizeof(evt->Characteristic.Descriptors[0]));

		if (!evt->Characteristic.Descriptors)
		{
			MEM_BufferFree(evt->Characteristic.Value.Value);
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristic.Descriptors = NULL;
	}


	for (uint32_t i = 0; i < evt->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].Handle), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].Handle)); idx += sizeof(evt->Characteristic.Descriptors[i].Handle);
		evt->Characteristic.Descriptors[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].ValueLength), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(evt->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].MaxValueLength), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(evt->Characteristic.Descriptors[i].MaxValueLength);

		if (evt->Characteristic.Descriptors[i].ValueLength > 0)
		{
			evt->Characteristic.Descriptors[i].Value = MEM_BufferAlloc(evt->Characteristic.Descriptors[i].ValueLength);

			if (!evt->Characteristic.Descriptors[i].Value)
			{
				MEM_BufferFree(evt->Characteristic.Descriptors);
				MEM_BufferFree(evt->Characteristic.Value.Value);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristic.Descriptors[i].Value = NULL;
		}

		FLib_MemCpy(evt->Characteristic.Descriptors[i].Value, pPayload + idx, evt->Characteristic.Descriptors[i].ValueLength); idx += evt->Characteristic.Descriptors[i].ValueLength;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureReadCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Read procedure for a given characteristic ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureReadCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureReadCharacteristicValueIndication_t *evt = &(container->Data.GATTClientProcedureReadCharacteristicValueIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureReadCharacteristicValueIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->Characteristic.Properties = (Properties_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Characteristic.Value.Handle), pPayload + idx, sizeof(evt->Characteristic.Value.Handle)); idx += sizeof(evt->Characteristic.Value.Handle);
	evt->Characteristic.Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

	switch (evt->Characteristic.Value.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(evt->Characteristic.Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
			break;
	}
	FLib_MemCpy(&(evt->Characteristic.Value.ValueLength), pPayload + idx, sizeof(evt->Characteristic.Value.ValueLength)); idx += sizeof(evt->Characteristic.Value.ValueLength);
	FLib_MemCpy(&(evt->Characteristic.Value.MaxValueLength), pPayload + idx, sizeof(evt->Characteristic.Value.MaxValueLength)); idx += sizeof(evt->Characteristic.Value.MaxValueLength);

	if (evt->Characteristic.Value.ValueLength > 0)
	{
		evt->Characteristic.Value.Value = MEM_BufferAlloc(evt->Characteristic.Value.ValueLength);

		if (!evt->Characteristic.Value.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristic.Value.Value = NULL;
	}

	FLib_MemCpy(evt->Characteristic.Value.Value, pPayload + idx, evt->Characteristic.Value.ValueLength); idx += evt->Characteristic.Value.ValueLength;
	evt->Characteristic.NbOfDescriptors = pPayload[idx]; idx++;

	if (evt->Characteristic.NbOfDescriptors > 0)
	{
		evt->Characteristic.Descriptors = MEM_BufferAlloc(evt->Characteristic.NbOfDescriptors * sizeof(evt->Characteristic.Descriptors[0]));

		if (!evt->Characteristic.Descriptors)
		{
			MEM_BufferFree(evt->Characteristic.Value.Value);
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristic.Descriptors = NULL;
	}


	for (uint32_t i = 0; i < evt->Characteristic.NbOfDescriptors; i++)
	{
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].Handle), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].Handle)); idx += sizeof(evt->Characteristic.Descriptors[i].Handle);
		evt->Characteristic.Descriptors[i].UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Characteristic.Descriptors[i].UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Characteristic.Descriptors[i].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].ValueLength), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].ValueLength)); idx += sizeof(evt->Characteristic.Descriptors[i].ValueLength);
		FLib_MemCpy(&(evt->Characteristic.Descriptors[i].MaxValueLength), pPayload + idx, sizeof(evt->Characteristic.Descriptors[i].MaxValueLength)); idx += sizeof(evt->Characteristic.Descriptors[i].MaxValueLength);

		if (evt->Characteristic.Descriptors[i].ValueLength > 0)
		{
			evt->Characteristic.Descriptors[i].Value = MEM_BufferAlloc(evt->Characteristic.Descriptors[i].ValueLength);

			if (!evt->Characteristic.Descriptors[i].Value)
			{
				MEM_BufferFree(evt->Characteristic.Descriptors);
				MEM_BufferFree(evt->Characteristic.Value.Value);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristic.Descriptors[i].Value = NULL;
		}

		FLib_MemCpy(evt->Characteristic.Descriptors[i].Value, pPayload + idx, evt->Characteristic.Descriptors[i].ValueLength); idx += evt->Characteristic.Descriptors[i].ValueLength;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureReadUsingCharacteristicUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Read By UUID procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureReadUsingCharacteristicUuidIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureReadUsingCharacteristicUuidIndication_t *evt = &(container->Data.GATTClientProcedureReadUsingCharacteristicUuidIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureReadUsingCharacteristicUuidIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	FLib_MemCpy(&(evt->NbOfReadBytes), pPayload + idx, sizeof(evt->NbOfReadBytes)); idx += sizeof(evt->NbOfReadBytes);

	if (evt->NbOfReadBytes > 0)
	{
		evt->ReadBytes = MEM_BufferAlloc(evt->NbOfReadBytes);

		if (!evt->ReadBytes)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->ReadBytes = NULL;
	}

	FLib_MemCpy(evt->ReadBytes, pPayload + idx, evt->NbOfReadBytes); idx += evt->NbOfReadBytes;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureReadMultipleCharacteristicValuesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Read Multiple procedure ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureReadMultipleCharacteristicValuesIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureReadMultipleCharacteristicValuesIndication_t *evt = &(container->Data.GATTClientProcedureReadMultipleCharacteristicValuesIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureReadMultipleCharacteristicValuesIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	evt->NbOfCharacteristics = pPayload[idx]; idx++;

	if (evt->NbOfCharacteristics > 0)
	{
		evt->Characteristics = MEM_BufferAlloc(evt->NbOfCharacteristics * sizeof(evt->Characteristics[0]));

		if (!evt->Characteristics)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Characteristics = NULL;
	}


	for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
	{
		evt->Characteristics[i].Properties = (Properties_t)pPayload[idx]; idx++;
		FLib_MemCpy(&(evt->Characteristics[i].Value.Handle), pPayload + idx, sizeof(evt->Characteristics[i].Value.Handle)); idx += sizeof(evt->Characteristics[i].Value.Handle);
		evt->Characteristics[i].Value.UuidType = (UuidType_t)pPayload[idx]; idx++;

		switch (evt->Characteristics[i].Value.UuidType)
		{
			case Uuid16Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
				break;

			case Uuid128Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
				break;

			case Uuid32Bits:
				FLib_MemCpy(evt->Characteristics[i].Value.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
				break;
		}
		FLib_MemCpy(&(evt->Characteristics[i].Value.ValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Value.ValueLength)); idx += sizeof(evt->Characteristics[i].Value.ValueLength);
		FLib_MemCpy(&(evt->Characteristics[i].Value.MaxValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Value.MaxValueLength)); idx += sizeof(evt->Characteristics[i].Value.MaxValueLength);

		if (evt->Characteristics[i].Value.ValueLength > 0)
		{
			evt->Characteristics[i].Value.Value = MEM_BufferAlloc(evt->Characteristics[i].Value.ValueLength);

			if (!evt->Characteristics[i].Value.Value)
			{
				MEM_BufferFree(evt->Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristics[i].Value.Value = NULL;
		}

		FLib_MemCpy(evt->Characteristics[i].Value.Value, pPayload + idx, evt->Characteristics[i].Value.ValueLength); idx += evt->Characteristics[i].Value.ValueLength;
		evt->Characteristics[i].NbOfDescriptors = pPayload[idx]; idx++;

		if (evt->Characteristics[i].NbOfDescriptors > 0)
		{
			evt->Characteristics[i].Descriptors = MEM_BufferAlloc(evt->Characteristics[i].NbOfDescriptors * sizeof(evt->Characteristics[i].Descriptors[0]));

			if (!evt->Characteristics[i].Descriptors)
			{
				for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
				{
					MEM_BufferFree(evt->Characteristics[i].Value.Value);
				}
				MEM_BufferFree(evt->Characteristics);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Characteristics[i].Descriptors = NULL;
		}


		for (uint32_t j = 0; j < evt->Characteristics[i].NbOfDescriptors; j++)
		{
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].Handle), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].Handle)); idx += sizeof(evt->Characteristics[i].Descriptors[j].Handle);
			evt->Characteristics[i].Descriptors[j].UuidType = (UuidType_t)pPayload[idx]; idx++;

			switch (evt->Characteristics[i].Descriptors[j].UuidType)
			{
				case Uuid16Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
					break;

				case Uuid128Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
					break;

				case Uuid32Bits:
					FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
					break;
			}
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].ValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].ValueLength)); idx += sizeof(evt->Characteristics[i].Descriptors[j].ValueLength);
			FLib_MemCpy(&(evt->Characteristics[i].Descriptors[j].MaxValueLength), pPayload + idx, sizeof(evt->Characteristics[i].Descriptors[j].MaxValueLength)); idx += sizeof(evt->Characteristics[i].Descriptors[j].MaxValueLength);

			if (evt->Characteristics[i].Descriptors[j].ValueLength > 0)
			{
				evt->Characteristics[i].Descriptors[j].Value = MEM_BufferAlloc(evt->Characteristics[i].Descriptors[j].ValueLength);

				if (!evt->Characteristics[i].Descriptors[j].Value)
				{
					for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Characteristics[i].Descriptors);
					}
					for (uint32_t i = 0; i < evt->NbOfCharacteristics; i++)
					{
						MEM_BufferFree(evt->Characteristics[i].Value.Value);
					}
					MEM_BufferFree(evt->Characteristics);
					return MEM_ALLOC_ERROR_c;
				}

			}
			else
			{
				evt->Characteristics[i].Descriptors[j].Value = NULL;
			}

			FLib_MemCpy(evt->Characteristics[i].Descriptors[j].Value, pPayload + idx, evt->Characteristics[i].Descriptors[j].ValueLength); idx += evt->Characteristics[i].Descriptors[j].ValueLength;
		}
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureWriteCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Write procedure for a given characteristic ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureWriteCharacteristicValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureWriteCharacteristicValueIndication_t *evt = &(container->Data.GATTClientProcedureWriteCharacteristicValueIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureWriteCharacteristicValueIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTClientProcedureWriteCharacteristicValueIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureReadCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Descriptor Read procedure for a given characteristic's descriptor ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureReadCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureReadCharacteristicDescriptorIndication_t *evt = &(container->Data.GATTClientProcedureReadCharacteristicDescriptorIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureReadCharacteristicDescriptorIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->ProcedureResult = (GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_t)pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Error), pPayload + idx, 2); idx += 2;
	FLib_MemCpy(&(evt->Descriptor.Handle), pPayload + idx, sizeof(evt->Descriptor.Handle)); idx += sizeof(evt->Descriptor.Handle);
	evt->Descriptor.UuidType = (UuidType_t)pPayload[idx]; idx++;

	switch (evt->Descriptor.UuidType)
	{
		case Uuid16Bits:
			FLib_MemCpy(evt->Descriptor.Uuid.Uuid16Bits, pPayload + idx, 2); idx += 2;
			break;

		case Uuid128Bits:
			FLib_MemCpy(evt->Descriptor.Uuid.Uuid128Bits, pPayload + idx, 16); idx += 16;
			break;

		case Uuid32Bits:
			FLib_MemCpy(evt->Descriptor.Uuid.Uuid32Bits, pPayload + idx, 4); idx += 4;
			break;
	}
	FLib_MemCpy(&(evt->Descriptor.ValueLength), pPayload + idx, sizeof(evt->Descriptor.ValueLength)); idx += sizeof(evt->Descriptor.ValueLength);
	FLib_MemCpy(&(evt->Descriptor.MaxValueLength), pPayload + idx, sizeof(evt->Descriptor.MaxValueLength)); idx += sizeof(evt->Descriptor.MaxValueLength);

	if (evt->Descriptor.ValueLength > 0)
	{
		evt->Descriptor.Value = MEM_BufferAlloc(evt->Descriptor.ValueLength);

		if (!evt->Descriptor.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Descriptor.Value = NULL;
	}

	FLib_MemCpy(evt->Descriptor.Value, pPayload + idx, evt->Descriptor.ValueLength); idx += evt->Descriptor.ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientProcedureWriteCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Specifies that the Characteristic Descriptor Write procedure for a given characteristic's descriptor ended
***************************************************************************************************/
static memStatus_t Load_GATTClientProcedureWriteCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientProcedureWriteCharacteristicDescriptorIndication_t *evt = &(container->Data.GATTClientProcedureWriteCharacteristicDescriptorIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTClientProcedureWriteCharacteristicDescriptorIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTClientProcedureWriteCharacteristicDescriptorIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Client notification
***************************************************************************************************/
static memStatus_t Load_GATTClientNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientNotificationIndication_t *evt = &(container->Data.GATTClientNotificationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientNotificationIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->CharacteristicValueHandle), pPayload + idx, sizeof(evt->CharacteristicValueHandle)); idx += sizeof(evt->CharacteristicValueHandle);
	FLib_MemCpy(&(evt->ValueLength), pPayload + idx, sizeof(evt->ValueLength)); idx += sizeof(evt->ValueLength);

	if (evt->ValueLength > 0)
	{
		evt->Value = MEM_BufferAlloc(evt->ValueLength);

		if (!evt->Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Value = NULL;
	}

	FLib_MemCpy(evt->Value, pPayload + idx, evt->ValueLength); idx += evt->ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTClientIndicationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Client indication
***************************************************************************************************/
static memStatus_t Load_GATTClientIndicationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTClientIndicationIndication_t *evt = &(container->Data.GATTClientIndicationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTClientIndicationIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->CharacteristicValueHandle), pPayload + idx, sizeof(evt->CharacteristicValueHandle)); idx += sizeof(evt->CharacteristicValueHandle);
	FLib_MemCpy(&(evt->ValueLength), pPayload + idx, sizeof(evt->ValueLength)); idx += sizeof(evt->ValueLength);

	if (evt->ValueLength > 0)
	{
		evt->Value = MEM_BufferAlloc(evt->ValueLength);

		if (!evt->Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Value = NULL;
	}

	FLib_MemCpy(evt->Value, pPayload + idx, evt->ValueLength); idx += evt->ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerMtuChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server MTU changed indication
***************************************************************************************************/
static memStatus_t Load_GATTServerMtuChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerMtuChangedIndication_t *evt = &(container->Data.GATTServerMtuChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTServerMtuChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTServerMtuChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerHandleValueConfirmationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server handle value confirmation
***************************************************************************************************/
static memStatus_t Load_GATTServerHandleValueConfirmationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerHandleValueConfirmationIndication_t *evt = &(container->Data.GATTServerHandleValueConfirmationIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTServerHandleValueConfirmationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTServerHandleValueConfirmationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerAttributeWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server attribute written
***************************************************************************************************/
static memStatus_t Load_GATTServerAttributeWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerAttributeWrittenIndication_t *evt = &(container->Data.GATTServerAttributeWrittenIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTServerAttributeWrittenIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->AttributeWrittenEvent.Handle), pPayload + idx, sizeof(evt->AttributeWrittenEvent.Handle)); idx += sizeof(evt->AttributeWrittenEvent.Handle);
	FLib_MemCpy(&(evt->AttributeWrittenEvent.ValueLength), pPayload + idx, sizeof(evt->AttributeWrittenEvent.ValueLength)); idx += sizeof(evt->AttributeWrittenEvent.ValueLength);

	if (evt->AttributeWrittenEvent.ValueLength > 0)
	{
		evt->AttributeWrittenEvent.Value = MEM_BufferAlloc(evt->AttributeWrittenEvent.ValueLength);

		if (!evt->AttributeWrittenEvent.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->AttributeWrittenEvent.Value = NULL;
	}

	FLib_MemCpy(evt->AttributeWrittenEvent.Value, pPayload + idx, evt->AttributeWrittenEvent.ValueLength); idx += evt->AttributeWrittenEvent.ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerCharacteristicCccdWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server characteristic cccd written
***************************************************************************************************/
static memStatus_t Load_GATTServerCharacteristicCccdWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerCharacteristicCccdWrittenIndication_t *evt = &(container->Data.GATTServerCharacteristicCccdWrittenIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTServerCharacteristicCccdWrittenIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTServerCharacteristicCccdWrittenIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerAttributeWrittenWithoutResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server attribute written without response
***************************************************************************************************/
static memStatus_t Load_GATTServerAttributeWrittenWithoutResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerAttributeWrittenWithoutResponseIndication_t *evt = &(container->Data.GATTServerAttributeWrittenWithoutResponseIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTServerAttributeWrittenWithoutResponseIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->AttributeWrittenEvent.Handle), pPayload + idx, sizeof(evt->AttributeWrittenEvent.Handle)); idx += sizeof(evt->AttributeWrittenEvent.Handle);
	FLib_MemCpy(&(evt->AttributeWrittenEvent.ValueLength), pPayload + idx, sizeof(evt->AttributeWrittenEvent.ValueLength)); idx += sizeof(evt->AttributeWrittenEvent.ValueLength);

	if (evt->AttributeWrittenEvent.ValueLength > 0)
	{
		evt->AttributeWrittenEvent.Value = MEM_BufferAlloc(evt->AttributeWrittenEvent.ValueLength);

		if (!evt->AttributeWrittenEvent.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->AttributeWrittenEvent.Value = NULL;
	}

	FLib_MemCpy(evt->AttributeWrittenEvent.Value, pPayload + idx, evt->AttributeWrittenEvent.ValueLength); idx += evt->AttributeWrittenEvent.ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server error
***************************************************************************************************/
static memStatus_t Load_GATTServerErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerErrorIndication_t *evt = &(container->Data.GATTServerErrorIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTServerErrorIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTServerErrorIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerLongCharacteristicWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server long characteristic written
***************************************************************************************************/
static memStatus_t Load_GATTServerLongCharacteristicWrittenIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerLongCharacteristicWrittenIndication_t *evt = &(container->Data.GATTServerLongCharacteristicWrittenIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTServerLongCharacteristicWrittenIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->LongCharacteristicWrittenEvent.Handle), pPayload + idx, sizeof(evt->LongCharacteristicWrittenEvent.Handle)); idx += sizeof(evt->LongCharacteristicWrittenEvent.Handle);
	FLib_MemCpy(&(evt->LongCharacteristicWrittenEvent.ValueLength), pPayload + idx, sizeof(evt->LongCharacteristicWrittenEvent.ValueLength)); idx += sizeof(evt->LongCharacteristicWrittenEvent.ValueLength);

	if (evt->LongCharacteristicWrittenEvent.ValueLength > 0)
	{
		evt->LongCharacteristicWrittenEvent.Value = MEM_BufferAlloc(evt->LongCharacteristicWrittenEvent.ValueLength);

		if (!evt->LongCharacteristicWrittenEvent.Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->LongCharacteristicWrittenEvent.Value = NULL;
	}

	FLib_MemCpy(evt->LongCharacteristicWrittenEvent.Value, pPayload + idx, evt->LongCharacteristicWrittenEvent.ValueLength); idx += evt->LongCharacteristicWrittenEvent.ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTServerAttributeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	GATT Server attribute read
***************************************************************************************************/
static memStatus_t Load_GATTServerAttributeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTServerAttributeReadIndication_t *evt = &(container->Data.GATTServerAttributeReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTServerAttributeReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTServerAttributeReadIndication_t));

	return MEM_SUCCESS_c;
}

#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Status of the GATT Database (application) request
***************************************************************************************************/
static memStatus_t Load_GATTDBConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBConfirm_t *evt = &(container->Data.GATTDBConfirm);

	/* Store (OG, OC) in ID */
	container->id = GATTDBConfirm_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBConfirm_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBReadAttributeIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Reads an attribute value (from application level)
***************************************************************************************************/
static memStatus_t Load_GATTDBReadAttributeIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBReadAttributeIndication_t *evt = &(container->Data.GATTDBReadAttributeIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GATTDBReadAttributeIndication_FSCI_ID;

	FLib_MemCpy(&(evt->ValueLength), pPayload + idx, sizeof(evt->ValueLength)); idx += sizeof(evt->ValueLength);

	if (evt->ValueLength > 0)
	{
		evt->Value = MEM_BufferAlloc(evt->ValueLength);

		if (!evt->Value)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Value = NULL;
	}

	FLib_MemCpy(evt->Value, pPayload + idx, evt->ValueLength); idx += evt->ValueLength;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBFindServiceHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Finds the handle of a Service Declaration with a given UUID inside the database
***************************************************************************************************/
static memStatus_t Load_GATTDBFindServiceHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBFindServiceHandleIndication_t *evt = &(container->Data.GATTDBFindServiceHandleIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBFindServiceHandleIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBFindServiceHandleIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBFindCharValueHandleInServiceIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Finds the handle of a characteristic value (with a given UUID) inside a service
***************************************************************************************************/
static memStatus_t Load_GATTDBFindCharValueHandleInServiceIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBFindCharValueHandleInServiceIndication_t *evt = &(container->Data.GATTDBFindCharValueHandleInServiceIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBFindCharValueHandleInServiceIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBFindCharValueHandleInServiceIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBFindCccdHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Finds the handle of a characteristic's CCCD (giving the characteristic's value handle)
***************************************************************************************************/
static memStatus_t Load_GATTDBFindCccdHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBFindCccdHandleForCharValueHandleIndication_t *evt = &(container->Data.GATTDBFindCccdHandleForCharValueHandleIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBFindCccdHandleForCharValueHandleIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBFindCccdHandleForCharValueHandleIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBFindDescriptorHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Finds the handle of a characteristic descriptor (giving the characteristic's value handle and descriptor's UUID)
***************************************************************************************************/
static memStatus_t Load_GATTDBFindDescriptorHandleForCharValueHandleIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBFindDescriptorHandleForCharValueHandleIndication_t *evt = &(container->Data.GATTDBFindDescriptorHandleForCharValueHandleIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBFindDescriptorHandleForCharValueHandleIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBFindDescriptorHandleForCharValueHandleIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddPrimaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Primary Service declaration into the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddPrimaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddPrimaryServiceDeclarationIndication_t *evt = &(container->Data.GATTDBDynamicAddPrimaryServiceDeclarationIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddPrimaryServiceDeclarationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddPrimaryServiceDeclarationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddSecondaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Secondary Service declaration into the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddSecondaryServiceDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddSecondaryServiceDeclarationIndication_t *evt = &(container->Data.GATTDBDynamicAddSecondaryServiceDeclarationIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddSecondaryServiceDeclarationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddSecondaryServiceDeclarationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddIncludeDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds an Include declaration into the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddIncludeDeclarationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddIncludeDeclarationIndication_t *evt = &(container->Data.GATTDBDynamicAddIncludeDeclarationIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddIncludeDeclarationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddIncludeDeclarationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationAndValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Characteristic declaration and its Value into the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationAndValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_t *evt = &(container->Data.GATTDBDynamicAddCharacteristicDeclarationAndValueIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Characteristic descriptor into the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddCharacteristicDescriptorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddCharacteristicDescriptorIndication_t *evt = &(container->Data.GATTDBDynamicAddCharacteristicDescriptorIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddCharacteristicDescriptorIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddCharacteristicDescriptorIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddCccdIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a CCCD in the database
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddCccdIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddCccdIndication_t *evt = &(container->Data.GATTDBDynamicAddCccdIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddCccdIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddCccdIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Characteristic declaration with a Value contained in an universal value buffer
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_t *evt = &(container->Data.GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GATTDBDynamicAddCharDescriptorWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Adds a Characteristic descriptor with a Value contained in an universal value buffer
***************************************************************************************************/
static memStatus_t Load_GATTDBDynamicAddCharDescriptorWithUniqueValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_t *evt = &(container->Data.GATTDBDynamicAddCharDescriptorWithUniqueValueIndication);

	/* Store (OG, OC) in ID */
	container->id = GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_t));

	return MEM_SUCCESS_c;
}

#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Status of the GAP request
***************************************************************************************************/
static memStatus_t Load_GAPConfirm(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConfirm_t *evt = &(container->Data.GAPConfirm);

	/* Store (OG, OC) in ID */
	container->id = GAPConfirm_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConfirm_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPCheckNotificationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the notification status for a given Client and a given CCCD handle
***************************************************************************************************/
static memStatus_t Load_GAPCheckNotificationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPCheckNotificationStatusIndication_t *evt = &(container->Data.GAPCheckNotificationStatusIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPCheckNotificationStatusIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPCheckNotificationStatusIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPCheckIndicationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the indication status for a given Client and a given CCCD handle
***************************************************************************************************/
static memStatus_t Load_GAPCheckIndicationStatusIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPCheckIndicationStatusIndication_t *evt = &(container->Data.GAPCheckIndicationStatusIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPCheckIndicationStatusIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPCheckIndicationStatusIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPLoadKeysIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the keys of a bonded device
***************************************************************************************************/
static memStatus_t Load_GAPLoadKeysIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPLoadKeysIndication_t *evt = &(container->Data.GAPLoadKeysIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPLoadKeysIndication_FSCI_ID;

	evt->Keys.LtkIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->Keys.LtkIncluded)
	{
		evt->Keys.LtkInfo.LtkSize = pPayload[idx]; idx++;

		if (evt->Keys.LtkInfo.LtkSize > 0)
		{
			evt->Keys.LtkInfo.Ltk = MEM_BufferAlloc(evt->Keys.LtkInfo.LtkSize);

			if (!evt->Keys.LtkInfo.Ltk)
			{
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Keys.LtkInfo.Ltk = NULL;
		}

		FLib_MemCpy(evt->Keys.LtkInfo.Ltk, pPayload + idx, evt->Keys.LtkInfo.LtkSize); idx += evt->Keys.LtkInfo.LtkSize;
	}

	evt->Keys.IrkIncluded = (bool_t)pPayload[idx]; idx++;


	evt->Keys.CsrkIncluded = (bool_t)pPayload[idx]; idx++;



	if (evt->Keys.LtkIncluded)
	{
		evt->Keys.RandEdivInfo.RandSize = pPayload[idx]; idx++;

		if (evt->Keys.RandEdivInfo.RandSize > 0)
		{
			evt->Keys.RandEdivInfo.Rand = MEM_BufferAlloc(evt->Keys.RandEdivInfo.RandSize);

			if (!evt->Keys.RandEdivInfo.Rand)
			{
				MEM_BufferFree(evt->Keys.LtkInfo.Ltk);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Keys.RandEdivInfo.Rand = NULL;
		}

		FLib_MemCpy(evt->Keys.RandEdivInfo.Rand, pPayload + idx, evt->Keys.RandEdivInfo.RandSize); idx += evt->Keys.RandEdivInfo.RandSize;
		FLib_MemCpy(&(evt->Keys.RandEdivInfo.Ediv), pPayload + idx, sizeof(evt->Keys.RandEdivInfo.Ediv)); idx += sizeof(evt->Keys.RandEdivInfo.Ediv);
	}


	if (evt->Keys.IrkIncluded)
	{
		evt->Keys.AddressIncluded = (bool_t)pPayload[idx]; idx++;
	}



	if (evt->Keys.AddressIncluded)
	{
		evt->Keys.AddressInfo.DeviceAddressType = (GAPLoadKeysIndication_Keys_AddressInfo_DeviceAddressType_t)pPayload[idx]; idx++;
		FLib_MemCpy(evt->Keys.AddressInfo.DeviceAddress, pPayload + idx, 6); idx += 6;
	}

	evt->KeyFlags = (GAPLoadKeysIndication_KeyFlags_t)pPayload[idx]; idx++;
	evt->LeSc = (bool_t)pPayload[idx]; idx++;
	evt->Authenticated = (bool_t)pPayload[idx]; idx++;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPLoadEncryptionInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the encryption key for a bonded device
***************************************************************************************************/
static memStatus_t Load_GAPLoadEncryptionInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPLoadEncryptionInformationIndication_t *evt = &(container->Data.GAPLoadEncryptionInformationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPLoadEncryptionInformationIndication_FSCI_ID;

	evt->LtkSize = pPayload[idx]; idx++;

	if (evt->LtkSize > 0)
	{
		evt->Ltk = MEM_BufferAlloc(evt->LtkSize);

		if (!evt->Ltk)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Ltk = NULL;
	}

	FLib_MemCpy(evt->Ltk, pPayload + idx, evt->LtkSize); idx += evt->LtkSize;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPLoadCustomPeerInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the custom peer information in raw data format
***************************************************************************************************/
static memStatus_t Load_GAPLoadCustomPeerInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPLoadCustomPeerInformationIndication_t *evt = &(container->Data.GAPLoadCustomPeerInformationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPLoadCustomPeerInformationIndication_FSCI_ID;

	FLib_MemCpy(&(evt->InfoSize), pPayload + idx, sizeof(evt->InfoSize)); idx += sizeof(evt->InfoSize);

	if (evt->InfoSize > 0)
	{
		evt->Info = MEM_BufferAlloc(evt->InfoSize);

		if (!evt->Info)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Info = NULL;
	}

	FLib_MemCpy(evt->Info, pPayload + idx, evt->InfoSize); idx += evt->InfoSize;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPCheckIfBondedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns whether a connected peer device is bonded or not
***************************************************************************************************/
static memStatus_t Load_GAPCheckIfBondedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPCheckIfBondedIndication_t *evt = &(container->Data.GAPCheckIfBondedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPCheckIfBondedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPCheckIfBondedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGetBondedDevicesCountIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the number of bonded devices
***************************************************************************************************/
static memStatus_t Load_GAPGetBondedDevicesCountIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGetBondedDevicesCountIndication_t *evt = &(container->Data.GAPGetBondedDevicesCountIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGetBondedDevicesCountIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGetBondedDevicesCountIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGetBondedDeviceNameIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns the name of a bonded device
***************************************************************************************************/
static memStatus_t Load_GAPGetBondedDeviceNameIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGetBondedDeviceNameIndication_t *evt = &(container->Data.GAPGetBondedDeviceNameIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPGetBondedDeviceNameIndication_FSCI_ID;

	evt->NameSize = pPayload[idx]; idx++;

	if (evt->NameSize > 0)
	{
		evt->Name = MEM_BufferAlloc(evt->NameSize);

		if (!evt->Name)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Name = NULL;
	}

	FLib_MemCpy(evt->Name, pPayload + idx, evt->NameSize); idx += evt->NameSize;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventInitializationCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - initialization complete
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventInitializationCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventInitializationCompleteIndication_t *evt = &(container->Data.GAPGenericEventInitializationCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventInitializationCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventInitializationCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventInternalErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - controller error
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventInternalErrorIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventInternalErrorIndication_t *evt = &(container->Data.GAPGenericEventInternalErrorIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventInternalErrorIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventInternalErrorIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventAdvertisingSetupFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - advertising setup failed
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventAdvertisingSetupFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventAdvertisingSetupFailedIndication_t *evt = &(container->Data.GAPGenericEventAdvertisingSetupFailedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventAdvertisingSetupFailedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventAdvertisingSetupFailedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventAdvertisingParametersSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - advertising parameters setup completed
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventAdvertisingParametersSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventAdvertisingParametersSetupCompleteIndication_t *evt = &(container->Data.GAPGenericEventAdvertisingParametersSetupCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventAdvertisingParametersSetupCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventAdvertisingParametersSetupCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventAdvertisingDataSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - advertising data setup completed
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventAdvertisingDataSetupCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventAdvertisingDataSetupCompleteIndication_t *evt = &(container->Data.GAPGenericEventAdvertisingDataSetupCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventAdvertisingDataSetupCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventAdvertisingDataSetupCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventWhiteListSizeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - White List size
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventWhiteListSizeReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventWhiteListSizeReadIndication_t *evt = &(container->Data.GAPGenericEventWhiteListSizeReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventWhiteListSizeReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventWhiteListSizeReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventDeviceAddedToWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - device added to White List
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventDeviceAddedToWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventDeviceAddedToWhiteListIndication_t *evt = &(container->Data.GAPGenericEventDeviceAddedToWhiteListIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventDeviceAddedToWhiteListIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventDeviceAddedToWhiteListIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventDeviceRemovedFromWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - device removed from White List
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventDeviceRemovedFromWhiteListIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventDeviceRemovedFromWhiteListIndication_t *evt = &(container->Data.GAPGenericEventDeviceRemovedFromWhiteListIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventDeviceRemovedFromWhiteListIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventDeviceRemovedFromWhiteListIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventWhiteListClearedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - White List cleared
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventWhiteListClearedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventWhiteListClearedIndication_t *evt = &(container->Data.GAPGenericEventWhiteListClearedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventWhiteListClearedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventWhiteListClearedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventRandomAddressReadyIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - random address ready
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventRandomAddressReadyIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventRandomAddressReadyIndication_t *evt = &(container->Data.GAPGenericEventRandomAddressReadyIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventRandomAddressReadyIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventRandomAddressReadyIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventCreateConnectionCanceledIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - create connection procedure canceled
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventCreateConnectionCanceledIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventCreateConnectionCanceledIndication_t *evt = &(container->Data.GAPGenericEventCreateConnectionCanceledIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventCreateConnectionCanceledIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventCreateConnectionCanceledIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventPublicAddressReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - public address read
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventPublicAddressReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventPublicAddressReadIndication_t *evt = &(container->Data.GAPGenericEventPublicAddressReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventPublicAddressReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventPublicAddressReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventAdvTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - advertising transmission power level
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventAdvTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventAdvTxPowerLevelReadIndication_t *evt = &(container->Data.GAPGenericEventAdvTxPowerLevelReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventAdvTxPowerLevelReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventAdvTxPowerLevelReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventPrivateResolvableAddressVerifiedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - Private Resolvable Address verified
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventPrivateResolvableAddressVerifiedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventPrivateResolvableAddressVerifiedIndication_t *evt = &(container->Data.GAPGenericEventPrivateResolvableAddressVerifiedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventPrivateResolvableAddressVerifiedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventPrivateResolvableAddressVerifiedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventRandomAddressSetIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Controller event - A random address was set
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventRandomAddressSetIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventRandomAddressSetIndication_t *evt = &(container->Data.GAPGenericEventRandomAddressSetIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventRandomAddressSetIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventRandomAddressSetIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPAdvertisingEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event received when advertising has been successfully enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPAdvertisingEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPAdvertisingEventStateChangedIndication_t *evt = &(container->Data.GAPAdvertisingEventStateChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPAdvertisingEventStateChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPAdvertisingEventStateChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPAdvertisingEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event received when advertising could not be enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPAdvertisingEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPAdvertisingEventCommandFailedIndication_t *evt = &(container->Data.GAPAdvertisingEventCommandFailedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPAdvertisingEventCommandFailedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPAdvertisingEventCommandFailedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPScanningEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event received when scanning had been successfully enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPScanningEventStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPScanningEventStateChangedIndication_t *evt = &(container->Data.GAPScanningEventStateChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPScanningEventStateChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPScanningEventStateChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPScanningEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event received when scanning could not be enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPScanningEventCommandFailedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPScanningEventCommandFailedIndication_t *evt = &(container->Data.GAPScanningEventCommandFailedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPScanningEventCommandFailedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPScanningEventCommandFailedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPScanningEventDeviceScannedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event received when an advertising device has been scanned
***************************************************************************************************/
static memStatus_t Load_GAPScanningEventDeviceScannedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPScanningEventDeviceScannedIndication_t *evt = &(container->Data.GAPScanningEventDeviceScannedIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPScanningEventDeviceScannedIndication_FSCI_ID;

	evt->AddressType = (GAPScanningEventDeviceScannedIndication_AddressType_t)pPayload[idx]; idx++;
	FLib_MemCpy(evt->Address, pPayload + idx, 6); idx += 6;
	evt->Rssi = pPayload[idx]; idx++;
	evt->DataLength = pPayload[idx]; idx++;

	if (evt->DataLength > 0)
	{
		evt->Data = MEM_BufferAlloc(evt->DataLength);

		if (!evt->Data)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Data = NULL;
	}

	FLib_MemCpy(evt->Data, pPayload + idx, evt->DataLength); idx += evt->DataLength;
	evt->AdvEventType = (GAPScanningEventDeviceScannedIndication_AdvEventType_t)pPayload[idx]; idx++;
	evt->DirectRpaUsed = (bool_t)pPayload[idx]; idx++;


	evt->advertisingAddressResolved = (bool_t)pPayload[idx]; idx++;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventConnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A connection has been established
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventConnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventConnectedIndication_t *evt = &(container->Data.GAPConnectionEventConnectedIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventConnectedIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->ConnectionParameters.ConnInterval), pPayload + idx, sizeof(evt->ConnectionParameters.ConnInterval)); idx += sizeof(evt->ConnectionParameters.ConnInterval);
	FLib_MemCpy(&(evt->ConnectionParameters.ConnLatency), pPayload + idx, sizeof(evt->ConnectionParameters.ConnLatency)); idx += sizeof(evt->ConnectionParameters.ConnLatency);
	FLib_MemCpy(&(evt->ConnectionParameters.SupervisionTimeout), pPayload + idx, sizeof(evt->ConnectionParameters.SupervisionTimeout)); idx += sizeof(evt->ConnectionParameters.SupervisionTimeout);
	evt->ConnectionParameters.MasterClockAccuracy = (GAPConnectionEventConnectedIndication_ConnectionParameters_MasterClockAccuracy_t)pPayload[idx]; idx++;
	evt->PeerAddressType = (GAPConnectionEventConnectedIndication_PeerAddressType_t)pPayload[idx]; idx++;
	FLib_MemCpy(evt->PeerAddress, pPayload + idx, 6); idx += 6;
	evt->peerRpaResolved = (bool_t)pPayload[idx]; idx++;


	evt->localRpaUsed = (bool_t)pPayload[idx]; idx++;



	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPairingRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A pairing request has been received from the peer Master
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPairingRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPairingRequestIndication_t *evt = &(container->Data.GAPConnectionEventPairingRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPairingRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventPairingRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventSlaveSecurityRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A Slave Security Request has been received from the peer Slave
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventSlaveSecurityRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventSlaveSecurityRequestIndication_t *evt = &(container->Data.GAPConnectionEventSlaveSecurityRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventSlaveSecurityRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventSlaveSecurityRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPairingResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A pairing response has been received from the peer Slave
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPairingResponseIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPairingResponseIndication_t *evt = &(container->Data.GAPConnectionEventPairingResponseIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPairingResponseIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventPairingResponseIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventAuthenticationRejectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A link encryption or pairing request has been rejected by the peer Slave
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventAuthenticationRejectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventAuthenticationRejectedIndication_t *evt = &(container->Data.GAPConnectionEventAuthenticationRejectedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventAuthenticationRejectedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventAuthenticationRejectedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPasskeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Peer Slave has requested a passkey (maximum 6 digit PIN) for the pairing procedure
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPasskeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPasskeyRequestIndication_t *evt = &(container->Data.GAPConnectionEventPasskeyRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPasskeyRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventPasskeyRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventOobRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Out-of-Band data must be provided for the pairing procedure
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventOobRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventOobRequestIndication_t *evt = &(container->Data.GAPConnectionEventOobRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventOobRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventOobRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPasskeyDisplayIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The pairing procedure requires this Slave to display the passkey for the Master's user
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPasskeyDisplayIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPasskeyDisplayIndication_t *evt = &(container->Data.GAPConnectionEventPasskeyDisplayIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPasskeyDisplayIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventPasskeyDisplayIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventKeyExchangeRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The pairing procedure requires the SMP keys to be distributed to the peer
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventKeyExchangeRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventKeyExchangeRequestIndication_t *evt = &(container->Data.GAPConnectionEventKeyExchangeRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventKeyExchangeRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventKeyExchangeRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventKeysReceivedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	SMP keys distributed by the peer during pairing have been received
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventKeysReceivedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventKeysReceivedIndication_t *evt = &(container->Data.GAPConnectionEventKeysReceivedIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventKeysReceivedIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->Keys.LtkIncluded = (bool_t)pPayload[idx]; idx++;

	if (evt->Keys.LtkIncluded)
	{
		evt->Keys.LtkInfo.LtkSize = pPayload[idx]; idx++;

		if (evt->Keys.LtkInfo.LtkSize > 0)
		{
			evt->Keys.LtkInfo.Ltk = MEM_BufferAlloc(evt->Keys.LtkInfo.LtkSize);

			if (!evt->Keys.LtkInfo.Ltk)
			{
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Keys.LtkInfo.Ltk = NULL;
		}

		FLib_MemCpy(evt->Keys.LtkInfo.Ltk, pPayload + idx, evt->Keys.LtkInfo.LtkSize); idx += evt->Keys.LtkInfo.LtkSize;
	}

	evt->Keys.IrkIncluded = (bool_t)pPayload[idx]; idx++;


	evt->Keys.CsrkIncluded = (bool_t)pPayload[idx]; idx++;



	if (evt->Keys.LtkIncluded)
	{
		evt->Keys.RandEdivInfo.RandSize = pPayload[idx]; idx++;

		if (evt->Keys.RandEdivInfo.RandSize > 0)
		{
			evt->Keys.RandEdivInfo.Rand = MEM_BufferAlloc(evt->Keys.RandEdivInfo.RandSize);

			if (!evt->Keys.RandEdivInfo.Rand)
			{
				MEM_BufferFree(evt->Keys.LtkInfo.Ltk);
				return MEM_ALLOC_ERROR_c;
			}

		}
		else
		{
			evt->Keys.RandEdivInfo.Rand = NULL;
		}

		FLib_MemCpy(evt->Keys.RandEdivInfo.Rand, pPayload + idx, evt->Keys.RandEdivInfo.RandSize); idx += evt->Keys.RandEdivInfo.RandSize;
		FLib_MemCpy(&(evt->Keys.RandEdivInfo.Ediv), pPayload + idx, sizeof(evt->Keys.RandEdivInfo.Ediv)); idx += sizeof(evt->Keys.RandEdivInfo.Ediv);
	}


	if (evt->Keys.IrkIncluded)
	{
		evt->Keys.AddressIncluded = (bool_t)pPayload[idx]; idx++;
	}



	if (evt->Keys.AddressIncluded)
	{
		evt->Keys.AddressInfo.DeviceAddressType = (GAPConnectionEventKeysReceivedIndication_Keys_AddressInfo_DeviceAddressType_t)pPayload[idx]; idx++;
		FLib_MemCpy(evt->Keys.AddressInfo.DeviceAddress, pPayload + idx, 6); idx += 6;
	}


	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventLongTermKeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The bonded peer Master has requested link encryption and the LTK must be provided
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventLongTermKeyRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventLongTermKeyRequestIndication_t *evt = &(container->Data.GAPConnectionEventLongTermKeyRequestIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventLongTermKeyRequestIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	FLib_MemCpy(&(evt->Ediv), pPayload + idx, sizeof(evt->Ediv)); idx += sizeof(evt->Ediv);
	evt->RandSize = pPayload[idx]; idx++;

	if (evt->RandSize > 0)
	{
		evt->Rand = MEM_BufferAlloc(evt->RandSize);

		if (!evt->Rand)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->Rand = NULL;
	}

	FLib_MemCpy(evt->Rand, pPayload + idx, evt->RandSize); idx += evt->RandSize;

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventEncryptionChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Link's encryption state has changed, e.g. during pairing or after a reconnection with a bonded peer
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventEncryptionChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventEncryptionChangedIndication_t *evt = &(container->Data.GAPConnectionEventEncryptionChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventEncryptionChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventEncryptionChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPairingCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Pairing procedure is complete, either successfully or with failure
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPairingCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPairingCompleteIndication_t *evt = &(container->Data.GAPConnectionEventPairingCompleteIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPairingCompleteIndication_FSCI_ID;

	evt->DeviceId = pPayload[idx]; idx++;
	evt->PairingStatus = (GAPConnectionEventPairingCompleteIndication_PairingStatus_t)pPayload[idx]; idx++;

	switch (evt->PairingStatus)
	{
		case GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingSuccessful:
			evt->PairingData.PairingSuccessful_WithBonding = (bool_t)pPayload[idx]; idx++;
			break;

		case GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingFailed:
			FLib_MemCpy(&(evt->PairingData.PairingFailed_FailReason), pPayload + idx, 2); idx += 2;
			break;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventDisconnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A connection has been terminated
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventDisconnectedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventDisconnectedIndication_t *evt = &(container->Data.GAPConnectionEventDisconnectedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventDisconnectedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventDisconnectedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventRssiReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	RSSI for an active connection has been read
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventRssiReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventRssiReadIndication_t *evt = &(container->Data.GAPConnectionEventRssiReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventRssiReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventRssiReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	TX power level for an active connection has been read
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventTxPowerLevelReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventTxPowerLevelReadIndication_t *evt = &(container->Data.GAPConnectionEventTxPowerLevelReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventTxPowerLevelReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventTxPowerLevelReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventPowerReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Power reading could not be performed
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventPowerReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventPowerReadFailureIndication_t *evt = &(container->Data.GAPConnectionEventPowerReadFailureIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventPowerReadFailureIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventPowerReadFailureIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventParameterUpdateRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A connection parameter update request has been received
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventParameterUpdateRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventParameterUpdateRequestIndication_t *evt = &(container->Data.GAPConnectionEventParameterUpdateRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventParameterUpdateRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventParameterUpdateRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventParameterUpdateCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The connection has new parameters
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventParameterUpdateCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventParameterUpdateCompleteIndication_t *evt = &(container->Data.GAPConnectionEventParameterUpdateCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventParameterUpdateCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventParameterUpdateCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventLeDataLengthChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The new TX/RX Data Length paramaters
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventLeDataLengthChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventLeDataLengthChangedIndication_t *evt = &(container->Data.GAPConnectionEventLeDataLengthChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventLeDataLengthChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventLeDataLengthChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventLeScOobDataRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event sent to request LE SC OOB Data (r, Cr and Addr) received from a peer
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventLeScOobDataRequestIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventLeScOobDataRequestIndication_t *evt = &(container->Data.GAPConnectionEventLeScOobDataRequestIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventLeScOobDataRequestIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventLeScOobDataRequestIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventLeScDisplayNumericValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Event sent to display and confirm a Numeric Comparison Value when using the LE SC Numeric Comparison pairing method
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventLeScDisplayNumericValueIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventLeScDisplayNumericValueIndication_t *evt = &(container->Data.GAPConnectionEventLeScDisplayNumericValueIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventLeScDisplayNumericValueIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventLeScDisplayNumericValueIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventLeScKeypressNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Remote Keypress Notification recieved during Passkey Entry Pairing Method
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventLeScKeypressNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventLeScKeypressNotificationIndication_t *evt = &(container->Data.GAPConnectionEventLeScKeypressNotificationIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventLeScKeypressNotificationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventLeScKeypressNotificationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventControllerResetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The controller has been reset
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventControllerResetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventControllerResetCompleteIndication_t *evt = &(container->Data.GAPGenericEventControllerResetCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventControllerResetCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventControllerResetCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPLeScPublicKeyRegeneratedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The private/public key pair used for LE Secure Connections pairing has been regenerated
***************************************************************************************************/
static memStatus_t Load_GAPLeScPublicKeyRegeneratedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPLeScPublicKeyRegeneratedIndication_t *evt = &(container->Data.GAPLeScPublicKeyRegeneratedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPLeScPublicKeyRegeneratedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPLeScPublicKeyRegeneratedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventLeScLocalOobDataIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Local OOB data used for LE Secure Connections pairing
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventLeScLocalOobDataIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventLeScLocalOobDataIndication_t *evt = &(container->Data.GAPGenericEventLeScLocalOobDataIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventLeScLocalOobDataIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventLeScLocalOobDataIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventHostPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The Host Privacy was enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventHostPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventHostPrivacyStateChangedIndication_t *evt = &(container->Data.GAPGenericEventHostPrivacyStateChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventHostPrivacyStateChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventHostPrivacyStateChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventControllerPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	The Controller Privacy was enabled or disabled
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventControllerPrivacyStateChangedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventControllerPrivacyStateChangedIndication_t *evt = &(container->Data.GAPGenericEventControllerPrivacyStateChangedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventControllerPrivacyStateChangedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventControllerPrivacyStateChangedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventTxPowerLevelSetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Tx Power Level set completed.
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventTxPowerLevelSetCompleteIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventTxPowerLevelSetCompleteIndication_t *evt = &(container->Data.GAPGenericEventTxPowerLevelSetCompleteIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventTxPowerLevelSetCompleteIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventTxPowerLevelSetCompleteIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventLePhyEventIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Phy Mode of a connection has been updated by the Controller.
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventLePhyEventIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventLePhyEventIndication_t *evt = &(container->Data.GAPGenericEventLePhyEventIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventLePhyEventIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventLePhyEventIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGetBondedDevicesIdentityInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	Returns a list of the identity information of bonded devices
***************************************************************************************************/
static memStatus_t Load_GAPGetBondedDevicesIdentityInformationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGetBondedDevicesIdentityInformationIndication_t *evt = &(container->Data.GAPGetBondedDevicesIdentityInformationIndication);

	uint32_t idx = 0;

	/* Store (OG, OC) in ID */
	container->id = GAPGetBondedDevicesIdentityInformationIndication_FSCI_ID;

	evt->NbOfDeviceIdentityAddresses = pPayload[idx]; idx++;

	if (evt->NbOfDeviceIdentityAddresses > 0)
	{
		evt->IdentityAddresses = MEM_BufferAlloc(evt->NbOfDeviceIdentityAddresses * sizeof(evt->IdentityAddresses[0]));

		if (!evt->IdentityAddresses)
		{
			return MEM_ALLOC_ERROR_c;
		}

	}
	else
	{
		evt->IdentityAddresses = NULL;
	}


	for (uint32_t i = 0; i < evt->NbOfDeviceIdentityAddresses; i++)
	{
		evt->IdentityAddresses[i].IdentityAddressType = (GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_IdentityAddressType_t)pPayload[idx]; idx++;
		FLib_MemCpy(evt->IdentityAddresses[i].IdentityAddress, pPayload + idx, 6); idx += 6;
		FLib_MemCpy(evt->IdentityAddresses[i].Irk, pPayload + idx, 16); idx += 16;
		evt->IdentityAddresses[i].PrivacyMode = (GAPGetBondedDevicesIdentityInformationIndication_IdentityAddresses_PrivacyMode_t)pPayload[idx]; idx++;
	}

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPControllerNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	ADV/SCAN/CONN notification event from the controller
***************************************************************************************************/
static memStatus_t Load_GAPControllerNotificationIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPControllerNotificationIndication_t *evt = &(container->Data.GAPControllerNotificationIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPControllerNotificationIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPControllerNotificationIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPBondCreatedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A bond has been created by the stack or the application
***************************************************************************************************/
static memStatus_t Load_GAPBondCreatedIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPBondCreatedIndication_t *evt = &(container->Data.GAPBondCreatedIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPBondCreatedIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPBondCreatedIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventChannelMapSetIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A channel map set operation has completed
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventChannelMapSetIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventChannelMapSetIndication_t *evt = &(container->Data.GAPGenericEventChannelMapSetIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventChannelMapSetIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventChannelMapSetIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventChannelMapReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A channel map read operation has completed
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventChannelMapReadIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventChannelMapReadIndication_t *evt = &(container->Data.GAPConnectionEventChannelMapReadIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventChannelMapReadIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventChannelMapReadIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventChannelMapReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	A channel map set operation has failed
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventChannelMapReadFailureIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventChannelMapReadFailureIndication_t *evt = &(container->Data.GAPConnectionEventChannelMapReadFailureIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventChannelMapReadFailureIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventChannelMapReadFailureIndication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPConnectionEventChannelSelectionAlgorithm2Indication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	LE Channel Selection Algorithm #2 is used on the data channel connection
***************************************************************************************************/
static memStatus_t Load_GAPConnectionEventChannelSelectionAlgorithm2Indication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPConnectionEventChannelSelectionAlgorithm2Indication_t *evt = &(container->Data.GAPConnectionEventChannelSelectionAlgorithm2Indication);

	/* Store (OG, OC) in ID */
	container->id = GAPConnectionEventChannelSelectionAlgorithm2Indication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPConnectionEventChannelSelectionAlgorithm2Indication_t));

	return MEM_SUCCESS_c;
}

/*!*************************************************************************************************
\fn		static memStatus_t Load_GAPGenericEventTxEntryAvailableIndication(bleEvtContainer_t *container, uint8_t *pPayload)
\brief	At least one Tx entry is available in the L2CAP queue
***************************************************************************************************/
static memStatus_t Load_GAPGenericEventTxEntryAvailableIndication(bleEvtContainer_t *container, uint8_t *pPayload)
{
	GAPGenericEventTxEntryAvailableIndication_t *evt = &(container->Data.GAPGenericEventTxEntryAvailableIndication);

	/* Store (OG, OC) in ID */
	container->id = GAPGenericEventTxEntryAvailableIndication_FSCI_ID;

	FLib_MemCpy(evt, pPayload, sizeof(GAPGenericEventTxEntryAvailableIndication_t));

	return MEM_SUCCESS_c;
}

#endif  /* GAP_ENABLE */


void KHC_BLE_RX_MsgHandler(void *pData, void *param, uint8_t fsciInterface)
{
	if (!pData || !param)
	{
		return;
	}

	fsciPacket_t *frame = (fsciPacket_t *)pData;
	bleEvtContainer_t *container = (bleEvtContainer_t *)param;
	uint8_t og = frame->opGroup;
	uint8_t oc = frame->opCode;
	uint8_t *pPayload = frame->data;
	uint16_t id = (og << 8) + oc, i;

	for (i = 0; i < sizeof(evtHandlerTbl) / sizeof(evtHandlerTbl[0]); i++)
	{
		if (evtHandlerTbl[i].id == id)
		{
			evtHandlerTbl[i].handlerFunc(container, pPayload);
			break;
		}
	}
}
