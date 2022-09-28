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
#include "cmd_ble_1.7.1.h"

#if FSCI_ENABLE
static const char *gFsciSuccess_c = "gFsciSuccess_c";
static const char *gFsciSAPDisabled_c = "gFsciSAPDisabled_c";
static const char *gFsciAppMsgTooBig_c = "gFsciAppMsgTooBig_c";
static const char *gFsciOutOfMessages_c = "gFsciOutOfMessages_c";
static const char *gFsciUnknownOpcodeGroup_c = "gFsciUnknownOpcodeGroup_c";
static const char *gFsciOpcodeGroupIsDisabled_c = "gFsciOpcodeGroupIsDisabled_c";
static const char *gFsciUnknownOpcode_c = "gFsciUnknownOpcode_c";
static const char *gFsciTooBig_c = "gFsciTooBig_c";
static const char *gFsciError_c = "gFsciError_c";
static const char *gSuccess = "gSuccess";
static const char *gError = "gError";
#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
static const char *gBleSuccess_c = "gBleSuccess_c";
static const char *gBleInvalidParameter_c = "gBleInvalidParameter_c";
static const char *gBleOverflow_c = "gBleOverflow_c";
static const char *gBleUnavailable_c = "gBleUnavailable_c";
static const char *gBleFeatureNotSupported_c = "gBleFeatureNotSupported_c";
static const char *gBleOutOfMemory_c = "gBleOutOfMemory_c";
static const char *gBleAlreadyInitialized_c = "gBleAlreadyInitialized_c";
static const char *gBleOsError_c = "gBleOsError_c";
static const char *gBleUnexpectedError_c = "gBleUnexpectedError_c";
static const char *gBleInvalidState_c = "gBleInvalidState_c";
static const char *gBleTimerError_c = "gBleTimerError_c";
static const char *gHciUnknownHciCommand_c = "gHciUnknownHciCommand_c";
static const char *gHciUnknownConnectionIdentifier_c = "gHciUnknownConnectionIdentifier_c";
static const char *gHciHardwareFailure_c = "gHciHardwareFailure_c";
static const char *gHciPageTimeout_c = "gHciPageTimeout_c";
static const char *gHciAuthenticationFailure_c = "gHciAuthenticationFailure_c";
static const char *gHciPinOrKeyMissing_c = "gHciPinOrKeyMissing_c";
static const char *gHciMemoryCapacityExceeded_c = "gHciMemoryCapacityExceeded_c";
static const char *gHciConnectionTimeout_c = "gHciConnectionTimeout_c";
static const char *gHciConnectionLimitExceeded_c = "gHciConnectionLimitExceeded_c";
static const char *gHciSynchronousConnectionLimitToADeviceExceeded_c = "gHciSynchronousConnectionLimitToADeviceExceeded_c";
static const char *gHciAclConnectionAlreadyExists_c = "gHciAclConnectionAlreadyExists_c";
static const char *gHciCommandDisallowed_c = "gHciCommandDisallowed_c";
static const char *gHciConnectionRejectedDueToLimitedResources_c = "gHciConnectionRejectedDueToLimitedResources_c";
static const char *gHciConnectionRejectedDueToSecurityReasons_c = "gHciConnectionRejectedDueToSecurityReasons_c";
static const char *gHciConnectionRejectedDueToUnacceptableBdAddr_c = "gHciConnectionRejectedDueToUnacceptableBdAddr_c";
static const char *gHciConnectionAcceptTimeoutExceeded_c = "gHciConnectionAcceptTimeoutExceeded_c";
static const char *gHciUnsupportedFeatureOrParameterValue_c = "gHciUnsupportedFeatureOrParameterValue_c";
static const char *gHciInvalidHciCommandParameters_c = "gHciInvalidHciCommandParameters_c";
static const char *gHciRemoteUserTerminatedConnection_c = "gHciRemoteUserTerminatedConnection_c";
static const char *gHciRemoteDeviceTerminatedConnectionLowResources_c = "gHciRemoteDeviceTerminatedConnectionLowResources_c";
static const char *gHciRemoteDeviceTerminatedConnectionPowerOff_c = "gHciRemoteDeviceTerminatedConnectionPowerOff_c";
static const char *gHciConnectionTerminatedByLocalHost_c = "gHciConnectionTerminatedByLocalHost_c";
static const char *gHciRepeatedAttempts_c = "gHciRepeatedAttempts_c";
static const char *gHciPairingNotAllowed_c = "gHciPairingNotAllowed_c";
static const char *gHciUnknownLpmPdu_c = "gHciUnknownLpmPdu_c";
static const char *gHciUnsupportedRemoteFeature_c = "gHciUnsupportedRemoteFeature_c";
static const char *gHciScoOffsetRejected_c = "gHciScoOffsetRejected_c";
static const char *gHciScoIntervalRejected_c = "gHciScoIntervalRejected_c";
static const char *gHciScoAirModeRejected_c = "gHciScoAirModeRejected_c";
static const char *gHciInvalidLpmParameters_c = "gHciInvalidLpmParameters_c";
static const char *gHciUnspecifiedError_c = "gHciUnspecifiedError_c";
static const char *gHciUnsupportedLpmParameterValue_c = "gHciUnsupportedLpmParameterValue_c";
static const char *gHciRoleChangeNotAllowed_c = "gHciRoleChangeNotAllowed_c";
static const char *gHciLLResponseTimeout_c = "gHciLLResponseTimeout_c";
static const char *gHciLmpErrorTransactionCollision_c = "gHciLmpErrorTransactionCollision_c";
static const char *gHciLmpPduNotAllowed_c = "gHciLmpPduNotAllowed_c";
static const char *gHciEncryptionModeNotAcceptable_c = "gHciEncryptionModeNotAcceptable_c";
static const char *gHciLinkKeyCannotBeChanged_c = "gHciLinkKeyCannotBeChanged_c";
static const char *gHciRequestedQosNotSupported_c = "gHciRequestedQosNotSupported_c";
static const char *gHciInstantPassed_c = "gHciInstantPassed_c";
static const char *gHciPairingWithUnitKeyNotSupported_c = "gHciPairingWithUnitKeyNotSupported_c";
static const char *gHciDifferentTransactionCollision_c = "gHciDifferentTransactionCollision_c";
static const char *gHciReserved_0x2B_c = "gHciReserved_0x2B_c";
static const char *gHciQosNotAcceptableParameter_c = "gHciQosNotAcceptableParameter_c";
static const char *gHciQosRejected_c = "gHciQosRejected_c";
static const char *gHciChannelClassificationNotSupported_c = "gHciChannelClassificationNotSupported_c";
static const char *gHciInsufficientSecurity_c = "gHciInsufficientSecurity_c";
static const char *gHciParameterOutOfMandatoryRange_c = "gHciParameterOutOfMandatoryRange_c";
static const char *gHciReserved_0x31_c = "gHciReserved_0x31_c";
static const char *gHciRoleSwitchPending_c = "gHciRoleSwitchPending_c";
static const char *gHciReserved_0x33_c = "gHciReserved_0x33_c";
static const char *gHciReservedSlotViolation_c = "gHciReservedSlotViolation_c";
static const char *gHciRoleSwitchFailed_c = "gHciRoleSwitchFailed_c";
static const char *gHciExtendedInquiryResponseTooLarge_c = "gHciExtendedInquiryResponseTooLarge_c";
static const char *gHciSecureSimplePairingNotSupportedByHost_c = "gHciSecureSimplePairingNotSupportedByHost_c";
static const char *gHciHostBusyPairing_c = "gHciHostBusyPairing_c";
static const char *gHciConnectionRejectedDueToNoSuitableChannelFound_c = "gHciConnectionRejectedDueToNoSuitableChannelFound_c";
static const char *gHciControllerBusy_c = "gHciControllerBusy_c";
static const char *gHciUnacceptableConnectionParameters_c = "gHciUnacceptableConnectionParameters_c";
static const char *gHciDirectedAdvertisingTimeout_c = "gHciDirectedAdvertisingTimeout_c";
static const char *gHciConnectionTerminatedDueToMicFailure_c = "gHciConnectionTerminatedDueToMicFailure_c";
static const char *gHciConnectionFailedToBeEstablishedOrSyncTimeout_c = "gHciConnectionFailedToBeEstablishedOrSyncTimeout_c";
static const char *gHciMacConnectionFailed_c = "gHciMacConnectionFailed_c";
static const char *gHciCoarseClockAdjustmentRejected_c = "gHciCoarseClockAdjustmentRejected_c";
static const char *gHciType0SubmapNotDefined_c = "gHciType0SubmapNotDefined_c";
static const char *gHciUnknownAdvertisingIdentifier_c = "gHciUnknownAdvertisingIdentifier_c";
static const char *gHciLimitReached_c = "gHciLimitReached_c";
static const char *gHciOperationCancelledByHost_c = "gHciOperationCancelledByHost_c";
static const char *gHciAlreadyInit_c = "gHciAlreadyInit_c";
static const char *gHciInvalidParameter_c = "gHciInvalidParameter_c";
static const char *gHciCallbackNotInstalled_c = "gHciCallbackNotInstalled_c";
static const char *gHciCallbackAlreadyInstalled_c = "gHciCallbackAlreadyInstalled_c";
static const char *gHciCommandNotSupported_c = "gHciCommandNotSupported_c";
static const char *gHciEventNotSupported_c = "gHciEventNotSupported_c";
static const char *gHciTransportError_c = "gHciTransportError_c";
static const char *gL2caAlreadyInit_c = "gL2caAlreadyInit_c";
static const char *gL2caInsufficientResources_c = "gL2caInsufficientResources_c";
static const char *gL2caCallbackNotInstalled_c = "gL2caCallbackNotInstalled_c";
static const char *gL2caCallbackAlreadyInstalled_c = "gL2caCallbackAlreadyInstalled_c";
static const char *gL2caLePsmInvalid_c = "gL2caLePsmInvalid_c";
static const char *gL2caLePsmAlreadyRegistered_c = "gL2caLePsmAlreadyRegistered_c";
static const char *gL2caLePsmNotRegistered_c = "gL2caLePsmNotRegistered_c";
static const char *gL2caLePsmInsufficientResources_c = "gL2caLePsmInsufficientResources_c";
static const char *gL2caChannelInvalid_c = "gL2caChannelInvalid_c";
static const char *gL2caChannelClosed_c = "gL2caChannelClosed_c";
static const char *gL2caChannelAlreadyConnected_c = "gL2caChannelAlreadyConnected_c";
static const char *gL2caConnectionParametersRejected_c = "gL2caConnectionParametersRejected_c";
static const char *gL2caChannelBusy_c = "gL2caChannelBusy_c";
static const char *gL2caInvalidParameter_c = "gL2caInvalidParameter_c";
static const char *gL2caError_c = "gL2caError_c";
static const char *gSmNullCBFunction_c = "gSmNullCBFunction_c";
static const char *gSmCommandNotSupported_c = "gSmCommandNotSupported_c";
static const char *gSmUnexpectedCommand_c = "gSmUnexpectedCommand_c";
static const char *gSmInvalidCommandCode_c = "gSmInvalidCommandCode_c";
static const char *gSmInvalidCommandLength_c = "gSmInvalidCommandLength_c";
static const char *gSmInvalidCommandParameter_c = "gSmInvalidCommandParameter_c";
static const char *gSmInvalidDeviceId_c = "gSmInvalidDeviceId_c";
static const char *gSmInvalidInternalOperation_c = "gSmInvalidInternalOperation_c";
static const char *gSmInvalidConnectionHandle_c = "gSmInvalidConnectionHandle_c";
static const char *gSmInproperKeyDistributionField_c = "gSmInproperKeyDistributionField_c";
static const char *gSmUnexpectedKeyType_c = "gSmUnexpectedKeyType_c";
static const char *gSmUnexpectedPairingTerminationReason_c = "gSmUnexpectedPairingTerminationReason_c";
static const char *gSmUnexpectedKeyset_c = "gSmUnexpectedKeyset_c";
static const char *gSmSmpTimeoutOccurred_c = "gSmSmpTimeoutOccurred_c";
static const char *gSmUnknownSmpPacketType_c = "gSmUnknownSmpPacketType_c";
static const char *gSmInvalidSmpPacketLength_c = "gSmInvalidSmpPacketLength_c";
static const char *gSmInvalidSmpPacketParameter_c = "gSmInvalidSmpPacketParameter_c";
static const char *gSmReceivedUnexpectedSmpPacket_c = "gSmReceivedUnexpectedSmpPacket_c";
static const char *gSmReceivedSmpPacketFromUnknownDevice_c = "gSmReceivedSmpPacketFromUnknownDevice_c";
static const char *gSmReceivedUnexpectedHciEvent_c = "gSmReceivedUnexpectedHciEvent_c";
static const char *gSmReceivedHciEventFromUnknownDevice_c = "gSmReceivedHciEventFromUnknownDevice_c";
static const char *gSmInvalidHciEventParameter_c = "gSmInvalidHciEventParameter_c";
static const char *gSmLlConnectionEncryptionInProgress_c = "gSmLlConnectionEncryptionInProgress_c";
static const char *gSmLlConnectionEncryptionFailure_c = "gSmLlConnectionEncryptionFailure_c";
static const char *gSmInsufficientResources_c = "gSmInsufficientResources_c";
static const char *gSmOobDataAddressMismatch_c = "gSmOobDataAddressMismatch_c";
static const char *gSmSmpPacketReceivedAfterTimeoutOccurred_c = "gSmSmpPacketReceivedAfterTimeoutOccurred_c";
static const char *gSmReceivedTimerEventForUnknownDevice_c = "gSmReceivedTimerEventForUnknownDevice_c";
static const char *gSmUnattainableLocalDeviceSecRequirements_c = "gSmUnattainableLocalDeviceSecRequirements_c";
static const char *gSmUnattainableLocalDeviceMinKeySize_c = "gSmUnattainableLocalDeviceMinKeySize_c";
static const char *gSmUnattainableSlaveSecReqRequirements_c = "gSmUnattainableSlaveSecReqRequirements_c";
static const char *gSmPairingErrorPasskeyEntryFailed_c = "gSmPairingErrorPasskeyEntryFailed_c";
static const char *gSmPairingErrorConfirmValueFailed_c = "gSmPairingErrorConfirmValueFailed_c";
static const char *gSmPairingErrorCommandNotSupported_c = "gSmPairingErrorCommandNotSupported_c";
static const char *gSmPairingErrorInvalidParameters_c = "gSmPairingErrorInvalidParameters_c";
static const char *gSmPairingErrorUnknownReason_c = "gSmPairingErrorUnknownReason_c";
static const char *gSmTbResolvableAddressDoesNotMatchIrk_c = "gSmTbResolvableAddressDoesNotMatchIrk_c";
static const char *gSmTbInvalidDataSignature_c = "gSmTbInvalidDataSignature_c";
static const char *gAttInvalidHandle_c = "gAttInvalidHandle_c";
static const char *gAttReadNotPermitted_c = "gAttReadNotPermitted_c";
static const char *gAttWriteNotPermitted_c = "gAttWriteNotPermitted_c";
static const char *gAttInvalidPdu_c = "gAttInvalidPdu_c";
static const char *gAttInsufficientAuthentication_c = "gAttInsufficientAuthentication_c";
static const char *gAttRequestNotSupported_c = "gAttRequestNotSupported_c";
static const char *gAttInvalidOffset_c = "gAttInvalidOffset_c";
static const char *gAttInsufficientAuthorization_c = "gAttInsufficientAuthorization_c";
static const char *gAttPrepareQueueFull_c = "gAttPrepareQueueFull_c";
static const char *gAttAttributeNotFound_c = "gAttAttributeNotFound_c";
static const char *gAttAttributeNotLong_c = "gAttAttributeNotLong_c";
static const char *gAttInsufficientEncryptionKeySize_c = "gAttInsufficientEncryptionKeySize_c";
static const char *gAttInvalidAttributeValueLength_c = "gAttInvalidAttributeValueLength_c";
static const char *gAttUnlikelyor_c = "gAttUnlikelyor_c";
static const char *gAttInsufficientEncryption_c = "gAttInsufficientEncryption_c";
static const char *gAttUnsupportedGroupType_c = "gAttUnsupportedGroupType_c";
static const char *gAttInsufficientResources_c = "gAttInsufficientResources_c";
static const char *gGattAnotherProcedureInProgress_c = "gGattAnotherProcedureInProgress_c";
static const char *gGattLongAttributePacketsCorrupted_c = "gGattLongAttributePacketsCorrupted_c";
static const char *gGattMultipleAttributesOverflow_c = "gGattMultipleAttributesOverflow_c";
static const char *gGattUnexpectedReadMultipleResponseLength_c = "gGattUnexpectedReadMultipleResponseLength_c";
static const char *gGattInvalidValueLength_c = "gGattInvalidValueLength_c";
static const char *gGattServerTimeout_c = "gGattServerTimeout_c";
static const char *gGattIndicationAlreadyInProgress_c = "gGattIndicationAlreadyInProgress_c";
static const char *gGattClientConfirmationTimeout_c = "gGattClientConfirmationTimeout_c";
static const char *gGapAdvDataTooLong_c = "gGapAdvDataTooLong_c";
static const char *gGapScanRspDataTooLong_c = "gGapScanRspDataTooLong_c";
static const char *gGapDeviceNotBonded_c = "gGapDeviceNotBonded_c";
static const char *gGapAnotherProcedureInProgress_c = "gGapAnotherProcedureInProgress_c";
static const char *gDevDbCccdLimitReached_c = "gDevDbCccdLimitReached_c";
static const char *gDevDbCccdNotFound_c = "gDevDbCccdNotFound_c";
static const char *gGattDbInvalidHandle_c = "gGattDbInvalidHandle_c";
static const char *gGattDbCharacteristicNotFound_c = "gGattDbCharacteristicNotFound_c";
static const char *gGattDbCccdNotFound_c = "gGattDbCccdNotFound_c";
static const char *gGattDbServiceNotFound_c = "gGattDbServiceNotFound_c";
static const char *gGattDbDescriptorNotFound_c = "gGattDbDescriptorNotFound_c";
#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
static const char *gGattProcSuccess_c = "gGattProcSuccess_c";
static const char *gProcedureError_c = "gProcedureError_c";
static const char *gBleOsc = "gBleOsc";
static const char *gBleUnexpectedc = "gBleUnexpectedc";
static const char *gBleTimerc = "gBleTimerc";
static const char *gHciUnspecifiedc = "gHciUnspecifiedc";
static const char *gHciTransportc = "gHciTransportc";
static const char *gL2cac = "gL2cac";
#endif  /* GATT_ENABLE */

#if GAP_ENABLE
static const char *gNoKeys_c = "gNoKeys_c";
static const char *gLtk_c = "gLtk_c";
static const char *gIrk_c = "gIrk_c";
static const char *gCsrk_c = "gCsrk_c";
static const char *gHciCommandStatus_c = "gHciCommandStatus_c";
static const char *gCheckPrivateResolvableAddress_c = "gCheckPrivateResolvableAddress_c";
static const char *gVerifySignature_c = "gVerifySignature_c";
static const char *gAddNewConnection_c = "gAddNewConnection_c";
static const char *gResetController_c = "gResetController_c";
static const char *gSetEventMask_c = "gSetEventMask_c";
static const char *gReadLeBufferSize_c = "gReadLeBufferSize_c";
static const char *gSetLeEventMask_c = "gSetLeEventMask_c";
static const char *gReadDeviceAddress_c = "gReadDeviceAddress_c";
static const char *gReadLocalSupportedFeatures_c = "gReadLocalSupportedFeatures_c";
static const char *gReadWhiteListSize_c = "gReadWhiteListSize_c";
static const char *gClearWhiteList_c = "gClearWhiteList_c";
static const char *gAddDeviceToWhiteList_c = "gAddDeviceToWhiteList_c";
static const char *gRemoveDeviceFromWhiteList_c = "gRemoveDeviceFromWhiteList_c";
static const char *gCancelCreateConnection_c = "gCancelCreateConnection_c";
static const char *gReadRadioPower_c = "gReadRadioPower_c";
static const char *gSetRandomAddress_c = "gSetRandomAddress_c";
static const char *gCreateRandomAddress_c = "gCreateRandomAddress_c";
static const char *gEncryptLink_c = "gEncryptLink_c";
static const char *gProvideLongTermKey_c = "gProvideLongTermKey_c";
static const char *gDenyLongTermKey_c = "gDenyLongTermKey_c";
static const char *gConnect_c = "gConnect_c";
static const char *gDisconnect_c = "gDisconnect_c";
static const char *gTerminatePairing_c = "gTerminatePairing_c";
static const char *gSendSlaveSecurityRequest_c = "gSendSlaveSecurityRequest_c";
static const char *gEnterPasskey_c = "gEnterPasskey_c";
static const char *gProvideOob_c = "gProvideOob_c";
static const char *gSendSmpKeys_c = "gSendSmpKeys_c";
static const char *gWriteSuggestedDefaultDataLength_c = "gWriteSuggestedDefaultDataLength_c";
static const char *gReadSuggestedDefaultDataLength_c = "gReadSuggestedDefaultDataLength_c";
static const char *gUpdateLeDataLength_c = "gUpdateLeDataLength_c";
static const char *gEnableHostPrivacy_c = "gEnableHostPrivacy_c";
static const char *gEnableControllerPrivacy_c = "gEnableControllerPrivacy_c";
static const char *gLeScSendKeypressNotification_c = "gLeScSendKeypressNotification_c";
static const char *gLeScSetPeerOobData_c = "gLeScSetPeerOobData_c";
static const char *gLeScGetLocalOobData_c = "gLeScGetLocalOobData_c";
static const char *gLeScValidateNumericValue_c = "gLeScValidateNumericValue_c";
static const char *gLeScRegeneratePublicKey_c = "gLeScRegeneratePublicKey_c";
static const char *gLeSetResolvablePrivateAddressTimeout_c = "gLeSetResolvablePrivateAddressTimeout_c";
static const char *gDefaultPairingProcedure_c = "gDefaultPairingProcedure_c";
static const char *gLeControllerTest_c = "gLeControllerTest_c";
static const char *gLeReadPhy_c = "gLeReadPhy_c";
static const char *gLeSetPhy_c = "gLeSetPhy_c";
static const char *gSaveKeys_c = "gSaveKeys_c";
static const char *gSetChannelMap_c = "gSetChannelMap_c";
static const char *gReadLocalSupportedCommands_c = "gReadLocalSupportedCommands_c";
static const char *gEnableLdmTimer_c = "gEnableLdmTimer_c";
static const char *gRemoveAdvertisingSet_c = "gRemoveAdvertisingSet_c";
static const char *gLePeriodicAdvSyncEstb_c = "gLePeriodicAdvSyncEstb_c";
static const char *gLePeriodicAdvSyncLost_c = "gLePeriodicAdvSyncLost_c";
static const char *gLeRemoveDeviceFromPeriodicAdvList_c = "gLeRemoveDeviceFromPeriodicAdvList_c";
static const char *gLeClearPeriodicAdvList_c = "gLeClearPeriodicAdvList_c";
static const char *gLeAddDeviceToPeriodicAdvList_c = "gLeAddDeviceToPeriodicAdvList_c";
static const char *gLeReadNumOfSupportedAdvSets_c = "gLeReadNumOfSupportedAdvSets_c";
static const char *gLeReadPeriodicAdvListSize_c = "gLeReadPeriodicAdvListSize_c";
static const char *gLeReadMaxAdvDataLen_c = "gLeReadMaxAdvDataLen_c";
static const char *gPeriodicAdvCreateSync = "gPeriodicAdvCreateSync";
static const char *gPeriodicAdvCancelSync = "gPeriodicAdvCancelSync";
static const char *gPeriodicAdvTerminateSync = "gPeriodicAdvTerminateSync";
static const char *gPublic_c = "gPublic_c";
static const char *gRandom_c = "gRandom_c";
static const char *gBleAdvRepAdvInd_c = "gBleAdvRepAdvInd_c";
static const char *gBleAdvRepAdvDirectInd_c = "gBleAdvRepAdvDirectInd_c";
static const char *gBleAdvRepAdvScanInd_c = "gBleAdvRepAdvScanInd_c";
static const char *gBleAdvRepAdvNonconnInd_c = "gBleAdvRepAdvNonconnInd_c";
static const char *gBleAdvRepScanRsp_c = "gBleAdvRepScanRsp_c";
static const char *gOobNotAvailable_c = "gOobNotAvailable_c";
static const char *gIncompatibleIoCapabilities_c = "gIncompatibleIoCapabilities_c";
static const char *gPairingNotSupported_c = "gPairingNotSupported_c";
static const char *gLowEncryptionKeySize_c = "gLowEncryptionKeySize_c";
static const char *gUnspecifiedReason_c = "gUnspecifiedReason_c";
static const char *gRepeatedAttempts_c = "gRepeatedAttempts_c";
static const char *gLinkEncryptionFailed_c = "gLinkEncryptionFailed_c";
static const char *PairingSuccessful = "PairingSuccessful";
static const char *PairingFailed = "PairingFailed";
static const char *gSmUnexpectedPairingTerminationc = "gSmUnexpectedPairingTerminationc";
static const char *gSmPairingErrorUnknownc = "gSmPairingErrorUnknownc";
static const char *gPhySetDefaultComplete_c = "gPhySetDefaultComplete_c";
static const char *gPhyRead_c = "gPhyRead_c";
static const char *gPhyUpdateComplete_c = "gPhyUpdateComplete_c";
static const char *gLeTxPhy1M_c = "gLeTxPhy1M_c";
static const char *gLeTxPhy2M_c = "gLeTxPhy2M_c";
static const char *gLeTxPhyCoded_c = "gLeTxPhyCoded_c";
static const char *gLeRxPhy1M_c = "gLeRxPhy1M_c";
static const char *gLeRxPhy2M_c = "gLeRxPhy2M_c";
static const char *gLeRxPhyCoded_c = "gLeRxPhyCoded_c";
static const char *gNotifConnEventOver_c = "gNotifConnEventOver_c";
static const char *gNotifConnRxPdu_c = "gNotifConnRxPdu_c";
static const char *gNotifAdvEventOver_c = "gNotifAdvEventOver_c";
static const char *gNotifAdvTx_c = "gNotifAdvTx_c";
static const char *gNotifAdvScanReqRx_c = "gNotifAdvScanReqRx_c";
static const char *gNotifAdvConnReqRx_c = "gNotifAdvConnReqRx_c";
static const char *gNotifScanEventOver_c = "gNotifScanEventOver_c";
static const char *gNotifScanAdvPktRx_c = "gNotifScanAdvPktRx_c";
static const char *gNotifScanRspRx_c = "gNotifScanRspRx_c";
static const char *gNotifScanReqTx_c = "gNotifScanReqTx_c";
static const char *gNotifConnCreated_c = "gNotifConnCreated_c";
#endif  /* GAP_ENABLE */


void SHELL_BleEventNotify(void *param)
{
	bleEvtContainer_t *container = (bleEvtContainer_t *)param;

	switch (container->id)
	{
#if FSCI_ENABLE
		case FSCIAckIndication_FSCI_ID:
			shell_write("FSCIAckIndication");
			break;

		case FSCIErrorIndication_FSCI_ID:
			shell_write("FSCIErrorIndication");
			shell_write(" -> ");
			switch (container->Data.FSCIErrorIndication.Status)
			{
				case FSCIErrorIndication_Status_gFsciSuccess_c:
					shell_write(gFsciSuccess_c);
					break;
				case FSCIErrorIndication_Status_gFsciSAPDisabled_c:
					shell_write(gFsciSAPDisabled_c);
					break;
				case FSCIErrorIndication_Status_gFsciAppMsgTooBig_c:
					shell_write(gFsciAppMsgTooBig_c);
					break;
				case FSCIErrorIndication_Status_gFsciOutOfMessages_c:
					shell_write(gFsciOutOfMessages_c);
					break;
				case FSCIErrorIndication_Status_gFsciUnknownOpcodeGroup_c:
					shell_write(gFsciUnknownOpcodeGroup_c);
					break;
				case FSCIErrorIndication_Status_gFsciOpcodeGroupIsDisabled_c:
					shell_write(gFsciOpcodeGroupIsDisabled_c);
					break;
				case FSCIErrorIndication_Status_gFsciUnknownOpcode_c:
					shell_write(gFsciUnknownOpcode_c);
					break;
				case FSCIErrorIndication_Status_gFsciTooBig_c:
					shell_write(gFsciTooBig_c);
					break;
				case FSCIErrorIndication_Status_gFsciError_c:
					shell_write(gFsciError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.FSCIErrorIndication.Status);
					break;
			}
			break;

		case FSCIAllowDeviceToSleepConfirm_FSCI_ID:
			shell_write("FSCIAllowDeviceToSleepConfirm");
			shell_write(" -> ");
			switch (container->Data.FSCIAllowDeviceToSleepConfirm.Status)
			{
				case FSCIAllowDeviceToSleepConfirm_Status_gSuccess:
					shell_write(gSuccess);
					break;
				case FSCIAllowDeviceToSleepConfirm_Status_gError:
					shell_write(gError);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.FSCIAllowDeviceToSleepConfirm.Status);
					break;
			}
			break;

		case FSCIWakeUpIndication_FSCI_ID:
			shell_write("FSCIWakeUpIndication");
			break;

		case FSCIGetWakeupReasonResponse_FSCI_ID:
			shell_write("FSCIGetWakeupReasonResponse");
			break;

#endif  /* FSCI_ENABLE */

#if L2CAPCB_ENABLE
		case L2CAPCBConfirm_FSCI_ID:
			shell_write("L2CAPCBConfirm");
			shell_write(" -> ");
			switch (container->Data.L2CAPCBConfirm.Status)
			{
				case L2CAPCBConfirm_Status_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case L2CAPCBConfirm_Status_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case L2CAPCBConfirm_Status_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case L2CAPCBConfirm_Status_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case L2CAPCBConfirm_Status_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case L2CAPCBConfirm_Status_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case L2CAPCBConfirm_Status_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case L2CAPCBConfirm_Status_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case L2CAPCBConfirm_Status_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case L2CAPCBConfirm_Status_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case L2CAPCBConfirm_Status_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case L2CAPCBConfirm_Status_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case L2CAPCBConfirm_Status_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case L2CAPCBConfirm_Status_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case L2CAPCBConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case L2CAPCBConfirm_Status_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case L2CAPCBConfirm_Status_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case L2CAPCBConfirm_Status_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case L2CAPCBConfirm_Status_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case L2CAPCBConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case L2CAPCBConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case L2CAPCBConfirm_Status_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case L2CAPCBConfirm_Status_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case L2CAPCBConfirm_Status_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case L2CAPCBConfirm_Status_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case L2CAPCBConfirm_Status_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case L2CAPCBConfirm_Status_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case L2CAPCBConfirm_Status_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case L2CAPCBConfirm_Status_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case L2CAPCBConfirm_Status_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case L2CAPCBConfirm_Status_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case L2CAPCBConfirm_Status_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case L2CAPCBConfirm_Status_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case L2CAPCBConfirm_Status_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case L2CAPCBConfirm_Status_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case L2CAPCBConfirm_Status_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case L2CAPCBConfirm_Status_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case L2CAPCBConfirm_Status_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case L2CAPCBConfirm_Status_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case L2CAPCBConfirm_Status_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case L2CAPCBConfirm_Status_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case L2CAPCBConfirm_Status_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case L2CAPCBConfirm_Status_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case L2CAPCBConfirm_Status_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case L2CAPCBConfirm_Status_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case L2CAPCBConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case L2CAPCBConfirm_Status_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case L2CAPCBConfirm_Status_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case L2CAPCBConfirm_Status_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case L2CAPCBConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case L2CAPCBConfirm_Status_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case L2CAPCBConfirm_Status_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case L2CAPCBConfirm_Status_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case L2CAPCBConfirm_Status_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case L2CAPCBConfirm_Status_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case L2CAPCBConfirm_Status_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case L2CAPCBConfirm_Status_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case L2CAPCBConfirm_Status_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case L2CAPCBConfirm_Status_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case L2CAPCBConfirm_Status_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case L2CAPCBConfirm_Status_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case L2CAPCBConfirm_Status_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case L2CAPCBConfirm_Status_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case L2CAPCBConfirm_Status_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case L2CAPCBConfirm_Status_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case L2CAPCBConfirm_Status_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case L2CAPCBConfirm_Status_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case L2CAPCBConfirm_Status_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case L2CAPCBConfirm_Status_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case L2CAPCBConfirm_Status_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case L2CAPCBConfirm_Status_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case L2CAPCBConfirm_Status_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case L2CAPCBConfirm_Status_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case L2CAPCBConfirm_Status_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case L2CAPCBConfirm_Status_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case L2CAPCBConfirm_Status_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case L2CAPCBConfirm_Status_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case L2CAPCBConfirm_Status_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case L2CAPCBConfirm_Status_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case L2CAPCBConfirm_Status_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case L2CAPCBConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case L2CAPCBConfirm_Status_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case L2CAPCBConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case L2CAPCBConfirm_Status_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case L2CAPCBConfirm_Status_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case L2CAPCBConfirm_Status_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case L2CAPCBConfirm_Status_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case L2CAPCBConfirm_Status_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case L2CAPCBConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case L2CAPCBConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case L2CAPCBConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case L2CAPCBConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case L2CAPCBConfirm_Status_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case L2CAPCBConfirm_Status_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case L2CAPCBConfirm_Status_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case L2CAPCBConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case L2CAPCBConfirm_Status_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case L2CAPCBConfirm_Status_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case L2CAPCBConfirm_Status_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case L2CAPCBConfirm_Status_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case L2CAPCBConfirm_Status_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case L2CAPCBConfirm_Status_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case L2CAPCBConfirm_Status_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case L2CAPCBConfirm_Status_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case L2CAPCBConfirm_Status_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case L2CAPCBConfirm_Status_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case L2CAPCBConfirm_Status_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case L2CAPCBConfirm_Status_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case L2CAPCBConfirm_Status_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case L2CAPCBConfirm_Status_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case L2CAPCBConfirm_Status_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case L2CAPCBConfirm_Status_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case L2CAPCBConfirm_Status_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case L2CAPCBConfirm_Status_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case L2CAPCBConfirm_Status_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case L2CAPCBConfirm_Status_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case L2CAPCBConfirm_Status_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case L2CAPCBConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case L2CAPCBConfirm_Status_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case L2CAPCBConfirm_Status_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case L2CAPCBConfirm_Status_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case L2CAPCBConfirm_Status_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case L2CAPCBConfirm_Status_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case L2CAPCBConfirm_Status_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case L2CAPCBConfirm_Status_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case L2CAPCBConfirm_Status_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case L2CAPCBConfirm_Status_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case L2CAPCBConfirm_Status_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case L2CAPCBConfirm_Status_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case L2CAPCBConfirm_Status_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case L2CAPCBConfirm_Status_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case L2CAPCBConfirm_Status_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.L2CAPCBConfirm.Status);
					break;
			}
			break;

		case L2CAPCBLePsmConnectionRequestIndication_FSCI_ID:
			shell_write("L2CAPCBLePsmConnectionRequestIndication");
			break;

		case L2CAPCBLePsmConnectionCompleteIndication_FSCI_ID:
			shell_write("L2CAPCBLePsmConnectionCompleteIndication");
			break;

		case L2CAPCBLePsmDisconnectNotificationIndication_FSCI_ID:
			shell_write("L2CAPCBLePsmDisconnectNotificationIndication");
			break;

		case L2CAPCBNoPeerCreditsIndication_FSCI_ID:
			shell_write("L2CAPCBNoPeerCreditsIndication");
			break;

		case L2CAPCBLocalCreditsNotificationIndication_FSCI_ID:
			shell_write("L2CAPCBLocalCreditsNotificationIndication");
			break;

		case L2CAPCBLeCbDataIndication_FSCI_ID:
			shell_write("L2CAPCBLeCbDataIndication");
			break;

		case L2CAPCBErrorIndication_FSCI_ID:
			shell_write("L2CAPCBErrorIndication");
			break;

#endif  /* L2CAPCB_ENABLE */

#if GATT_ENABLE
		case GATTConfirm_FSCI_ID:
			shell_write("GATTConfirm");
			shell_write(" -> ");
			switch (container->Data.GATTConfirm.Status)
			{
				case GATTConfirm_Status_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTConfirm_Status_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTConfirm_Status_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTConfirm_Status_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTConfirm_Status_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTConfirm_Status_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTConfirm_Status_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTConfirm_Status_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GATTConfirm_Status_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GATTConfirm_Status_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTConfirm_Status_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GATTConfirm_Status_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTConfirm_Status_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTConfirm_Status_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTConfirm_Status_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTConfirm_Status_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTConfirm_Status_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTConfirm_Status_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTConfirm_Status_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTConfirm_Status_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTConfirm_Status_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTConfirm_Status_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTConfirm_Status_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTConfirm_Status_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTConfirm_Status_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTConfirm_Status_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTConfirm_Status_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTConfirm_Status_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTConfirm_Status_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTConfirm_Status_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTConfirm_Status_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTConfirm_Status_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTConfirm_Status_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTConfirm_Status_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GATTConfirm_Status_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTConfirm_Status_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTConfirm_Status_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTConfirm_Status_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTConfirm_Status_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTConfirm_Status_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTConfirm_Status_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTConfirm_Status_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTConfirm_Status_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTConfirm_Status_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTConfirm_Status_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTConfirm_Status_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTConfirm_Status_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTConfirm_Status_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTConfirm_Status_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTConfirm_Status_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTConfirm_Status_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTConfirm_Status_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTConfirm_Status_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTConfirm_Status_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTConfirm_Status_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTConfirm_Status_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTConfirm_Status_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTConfirm_Status_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTConfirm_Status_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTConfirm_Status_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTConfirm_Status_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTConfirm_Status_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTConfirm_Status_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTConfirm_Status_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTConfirm_Status_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTConfirm_Status_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTConfirm_Status_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTConfirm_Status_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTConfirm_Status_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTConfirm_Status_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTConfirm_Status_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTConfirm_Status_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTConfirm_Status_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTConfirm_Status_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GATTConfirm_Status_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTConfirm_Status_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTConfirm_Status_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTConfirm_Status_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTConfirm_Status_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTConfirm_Status_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTConfirm_Status_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTConfirm_Status_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTConfirm_Status_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTConfirm_Status_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTConfirm_Status_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTConfirm_Status_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTConfirm_Status_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTConfirm_Status_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTConfirm_Status_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GATTConfirm_Status_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTConfirm_Status_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTConfirm_Status_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTConfirm_Status_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTConfirm_Status_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTConfirm_Status_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTConfirm_Status_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTConfirm_Status_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTConfirm_Status_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTConfirm_Status_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTConfirm_Status_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTConfirm_Status_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTConfirm_Status_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTConfirm_Status_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTConfirm_Status_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTConfirm_Status_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTConfirm_Status_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTConfirm_Status_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTConfirm_Status_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTConfirm_Status_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTConfirm_Status_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTConfirm_Status_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTConfirm_Status_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTConfirm_Status_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTConfirm_Status_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTConfirm_Status_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTConfirm_Status_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTConfirm_Status_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTConfirm_Status_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTConfirm_Status_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTConfirm_Status_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTConfirm_Status_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTConfirm_Status_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTConfirm_Status_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTConfirm_Status_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTConfirm_Status_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTConfirm_Status_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTConfirm_Status_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTConfirm_Status_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTConfirm_Status_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTConfirm_Status_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTConfirm_Status_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTConfirm_Status_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTConfirm_Status_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTConfirm_Status_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTConfirm_Status_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTConfirm_Status_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTConfirm_Status_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTConfirm_Status_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTConfirm_Status_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTConfirm_Status_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTConfirm_Status_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTConfirm_Status_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTConfirm_Status_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTConfirm_Status_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTConfirm_Status_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTConfirm_Status_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTConfirm_Status_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTConfirm_Status_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTConfirm_Status_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTConfirm_Status_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTConfirm_Status_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTConfirm_Status_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTConfirm_Status_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTConfirm.Status);
					break;
			}
			break;

		case GATTGetMtuIndication_FSCI_ID:
			shell_write("GATTGetMtuIndication");
			break;

		case GATTClientProcedureExchangeMtuIndication_FSCI_ID:
			shell_write("GATTClientProcedureExchangeMtuIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureExchangeMtuIndication.ProcedureResult)
			{
				case GATTClientProcedureExchangeMtuIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureExchangeMtuIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureExchangeMtuIndication.Error)
			{
				case GATTClientProcedureExchangeMtuIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureExchangeMtuIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureExchangeMtuIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureDiscoverAllPrimaryServicesIndication_FSCI_ID:
			shell_write("GATTClientProcedureDiscoverAllPrimaryServicesIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllPrimaryServicesIndication.ProcedureResult)
			{
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureDiscoverAllPrimaryServicesIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllPrimaryServicesIndication.Error)
			{
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllPrimaryServicesIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureDiscoverAllPrimaryServicesIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_FSCI_ID:
			shell_write("GATTClientProcedureDiscoverPrimaryServicesByUuidIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.ProcedureResult)
			{
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.Error)
			{
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureDiscoverPrimaryServicesByUuidIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureDiscoverPrimaryServicesByUuidIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureFindIncludedServicesIndication_FSCI_ID:
			shell_write("GATTClientProcedureFindIncludedServicesIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureFindIncludedServicesIndication.ProcedureResult)
			{
				case GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureFindIncludedServicesIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureFindIncludedServicesIndication.Error)
			{
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureFindIncludedServicesIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureFindIncludedServicesIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureDiscoverAllCharacteristicsIndication_FSCI_ID:
			shell_write("GATTClientProcedureDiscoverAllCharacteristicsIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllCharacteristicsIndication.ProcedureResult)
			{
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureDiscoverAllCharacteristicsIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllCharacteristicsIndication.Error)
			{
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicsIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureDiscoverAllCharacteristicsIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureDiscoverCharacteristicByUuidIndication_FSCI_ID:
			shell_write("GATTClientProcedureDiscoverCharacteristicByUuidIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverCharacteristicByUuidIndication.ProcedureResult)
			{
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureDiscoverCharacteristicByUuidIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverCharacteristicByUuidIndication.Error)
			{
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureDiscoverCharacteristicByUuidIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureDiscoverCharacteristicByUuidIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_FSCI_ID:
			shell_write("GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication.ProcedureResult)
			{
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication.Error)
			{
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureDiscoverAllCharacteristicDescriptorsIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureReadCharacteristicValueIndication_FSCI_ID:
			shell_write("GATTClientProcedureReadCharacteristicValueIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadCharacteristicValueIndication.ProcedureResult)
			{
				case GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureReadCharacteristicValueIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadCharacteristicValueIndication.Error)
			{
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicValueIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureReadCharacteristicValueIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureReadUsingCharacteristicUuidIndication_FSCI_ID:
			shell_write("GATTClientProcedureReadUsingCharacteristicUuidIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadUsingCharacteristicUuidIndication.ProcedureResult)
			{
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureReadUsingCharacteristicUuidIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadUsingCharacteristicUuidIndication.Error)
			{
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureReadUsingCharacteristicUuidIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureReadUsingCharacteristicUuidIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureReadMultipleCharacteristicValuesIndication_FSCI_ID:
			shell_write("GATTClientProcedureReadMultipleCharacteristicValuesIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadMultipleCharacteristicValuesIndication.ProcedureResult)
			{
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureReadMultipleCharacteristicValuesIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadMultipleCharacteristicValuesIndication.Error)
			{
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureReadMultipleCharacteristicValuesIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureReadMultipleCharacteristicValuesIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureWriteCharacteristicValueIndication_FSCI_ID:
			shell_write("GATTClientProcedureWriteCharacteristicValueIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureWriteCharacteristicValueIndication.ProcedureResult)
			{
				case GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureWriteCharacteristicValueIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureWriteCharacteristicValueIndication.Error)
			{
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicValueIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureWriteCharacteristicValueIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureReadCharacteristicDescriptorIndication_FSCI_ID:
			shell_write("GATTClientProcedureReadCharacteristicDescriptorIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadCharacteristicDescriptorIndication.ProcedureResult)
			{
				case GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureReadCharacteristicDescriptorIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureReadCharacteristicDescriptorIndication.Error)
			{
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureReadCharacteristicDescriptorIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureReadCharacteristicDescriptorIndication.Error);
					break;
			}
			break;

		case GATTClientProcedureWriteCharacteristicDescriptorIndication_FSCI_ID:
			shell_write("GATTClientProcedureWriteCharacteristicDescriptorIndication");
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureWriteCharacteristicDescriptorIndication.ProcedureResult)
			{
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_gGattProcSuccess_c:
					shell_write(gGattProcSuccess_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_ProcedureResult_gProcedureError_c:
					shell_write(gProcedureError_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GATTClientProcedureWriteCharacteristicDescriptorIndication.ProcedureResult);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GATTClientProcedureWriteCharacteristicDescriptorIndication.Error)
			{
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleOsError_c:
					shell_write(gBleOsc);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedc);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gBleTimerError_c:
					shell_write(gBleTimerc);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedc);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gHciTransportError_c:
					shell_write(gHciTransportc);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gL2caError_c:
					shell_write(gL2cac);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTClientProcedureWriteCharacteristicDescriptorIndication_Error_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTClientProcedureWriteCharacteristicDescriptorIndication.Error);
					break;
			}
			break;

		case GATTClientNotificationIndication_FSCI_ID:
			shell_write("GATTClientNotificationIndication");
			break;

		case GATTClientIndicationIndication_FSCI_ID:
			shell_write("GATTClientIndicationIndication");
			break;

		case GATTServerMtuChangedIndication_FSCI_ID:
			shell_write("GATTServerMtuChangedIndication");
			break;

		case GATTServerHandleValueConfirmationIndication_FSCI_ID:
			shell_write("GATTServerHandleValueConfirmationIndication");
			break;

		case GATTServerAttributeWrittenIndication_FSCI_ID:
			shell_write("GATTServerAttributeWrittenIndication");
			break;

		case GATTServerCharacteristicCccdWrittenIndication_FSCI_ID:
			shell_write("GATTServerCharacteristicCccdWrittenIndication");
			break;

		case GATTServerAttributeWrittenWithoutResponseIndication_FSCI_ID:
			shell_write("GATTServerAttributeWrittenWithoutResponseIndication");
			break;

		case GATTServerErrorIndication_FSCI_ID:
			shell_write("GATTServerErrorIndication");
			break;

		case GATTServerLongCharacteristicWrittenIndication_FSCI_ID:
			shell_write("GATTServerLongCharacteristicWrittenIndication");
			break;

		case GATTServerAttributeReadIndication_FSCI_ID:
			shell_write("GATTServerAttributeReadIndication");
			break;

#endif  /* GATT_ENABLE */

#if GATTDB_APP_ENABLE
		case GATTDBConfirm_FSCI_ID:
			shell_write("GATTDBConfirm");
			shell_write(" -> ");
			switch (container->Data.GATTDBConfirm.Status)
			{
				case GATTDBConfirm_Status_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GATTDBConfirm_Status_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GATTDBConfirm_Status_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GATTDBConfirm_Status_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GATTDBConfirm_Status_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GATTDBConfirm_Status_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GATTDBConfirm_Status_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GATTDBConfirm_Status_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GATTDBConfirm_Status_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GATTDBConfirm_Status_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GATTDBConfirm_Status_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GATTDBConfirm_Status_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GATTDBConfirm_Status_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GATTDBConfirm_Status_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GATTDBConfirm_Status_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GATTDBConfirm_Status_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GATTDBConfirm_Status_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GATTDBConfirm_Status_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GATTDBConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GATTDBConfirm_Status_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GATTDBConfirm_Status_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GATTDBConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GATTDBConfirm_Status_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GATTDBConfirm_Status_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GATTDBConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GATTDBConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GATTDBConfirm_Status_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GATTDBConfirm_Status_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GATTDBConfirm_Status_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GATTDBConfirm_Status_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GATTDBConfirm_Status_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GATTDBConfirm_Status_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GATTDBConfirm_Status_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GATTDBConfirm_Status_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GATTDBConfirm_Status_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GATTDBConfirm_Status_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GATTDBConfirm_Status_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GATTDBConfirm_Status_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GATTDBConfirm_Status_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GATTDBConfirm_Status_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GATTDBConfirm_Status_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GATTDBConfirm_Status_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GATTDBConfirm_Status_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GATTDBConfirm_Status_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GATTDBConfirm_Status_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GATTDBConfirm_Status_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GATTDBConfirm_Status_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GATTDBConfirm_Status_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GATTDBConfirm_Status_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GATTDBConfirm_Status_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GATTDBConfirm_Status_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GATTDBConfirm_Status_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GATTDBConfirm_Status_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GATTDBConfirm_Status_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GATTDBConfirm_Status_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GATTDBConfirm_Status_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GATTDBConfirm_Status_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GATTDBConfirm_Status_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GATTDBConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GATTDBConfirm_Status_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GATTDBConfirm_Status_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GATTDBConfirm_Status_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GATTDBConfirm_Status_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GATTDBConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GATTDBConfirm_Status_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GATTDBConfirm_Status_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GATTDBConfirm_Status_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GATTDBConfirm_Status_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GATTDBConfirm_Status_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GATTDBConfirm_Status_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GATTDBConfirm_Status_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GATTDBConfirm_Status_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GATTDBConfirm_Status_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GATTDBConfirm_Status_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GATTDBConfirm_Status_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GATTDBConfirm_Status_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GATTDBConfirm_Status_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GATTDBConfirm_Status_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GATTDBConfirm_Status_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GATTDBConfirm_Status_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GATTDBConfirm_Status_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GATTDBConfirm_Status_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GATTDBConfirm_Status_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GATTDBConfirm_Status_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GATTDBConfirm_Status_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GATTDBConfirm_Status_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GATTDBConfirm_Status_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GATTDBConfirm_Status_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GATTDBConfirm_Status_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GATTDBConfirm_Status_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GATTDBConfirm_Status_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GATTDBConfirm_Status_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GATTDBConfirm_Status_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GATTDBConfirm_Status_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GATTDBConfirm_Status_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GATTDBConfirm_Status_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GATTDBConfirm_Status_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GATTDBConfirm_Status_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GATTDBConfirm_Status_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GATTDBConfirm_Status_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GATTDBConfirm_Status_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GATTDBConfirm_Status_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GATTDBConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GATTDBConfirm_Status_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GATTDBConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GATTDBConfirm_Status_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GATTDBConfirm_Status_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GATTDBConfirm_Status_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GATTDBConfirm_Status_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GATTDBConfirm_Status_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GATTDBConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GATTDBConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GATTDBConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GATTDBConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GATTDBConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GATTDBConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GATTDBConfirm_Status_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GATTDBConfirm_Status_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GATTDBConfirm_Status_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GATTDBConfirm_Status_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GATTDBConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GATTDBConfirm_Status_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GATTDBConfirm_Status_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GATTDBConfirm_Status_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GATTDBConfirm_Status_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GATTDBConfirm_Status_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GATTDBConfirm_Status_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GATTDBConfirm_Status_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GATTDBConfirm_Status_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GATTDBConfirm_Status_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GATTDBConfirm_Status_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GATTDBConfirm_Status_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GATTDBConfirm_Status_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GATTDBConfirm_Status_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GATTDBConfirm_Status_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GATTDBConfirm_Status_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GATTDBConfirm_Status_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GATTDBConfirm_Status_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GATTDBConfirm_Status_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GATTDBConfirm_Status_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GATTDBConfirm_Status_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GATTDBConfirm_Status_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GATTDBConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GATTDBConfirm_Status_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GATTDBConfirm_Status_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GATTDBConfirm_Status_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GATTDBConfirm_Status_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GATTDBConfirm_Status_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GATTDBConfirm_Status_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GATTDBConfirm_Status_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GATTDBConfirm_Status_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GATTDBConfirm_Status_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GATTDBConfirm_Status_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GATTDBConfirm_Status_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GATTDBConfirm_Status_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GATTDBConfirm_Status_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GATTDBConfirm_Status_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GATTDBConfirm_Status_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GATTDBConfirm.Status);
					break;
			}
			break;

		case GATTDBReadAttributeIndication_FSCI_ID:
			shell_write("GATTDBReadAttributeIndication");
			break;

		case GATTDBFindServiceHandleIndication_FSCI_ID:
			shell_write("GATTDBFindServiceHandleIndication");
			break;

		case GATTDBFindCharValueHandleInServiceIndication_FSCI_ID:
			shell_write("GATTDBFindCharValueHandleInServiceIndication");
			break;

		case GATTDBFindCccdHandleForCharValueHandleIndication_FSCI_ID:
			shell_write("GATTDBFindCccdHandleForCharValueHandleIndication");
			break;

		case GATTDBFindDescriptorHandleForCharValueHandleIndication_FSCI_ID:
			shell_write("GATTDBFindDescriptorHandleForCharValueHandleIndication");
			break;

		case GATTDBDynamicAddPrimaryServiceDeclarationIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddPrimaryServiceDeclarationIndication");
			break;

		case GATTDBDynamicAddSecondaryServiceDeclarationIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddSecondaryServiceDeclarationIndication");
			break;

		case GATTDBDynamicAddIncludeDeclarationIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddIncludeDeclarationIndication");
			break;

		case GATTDBDynamicAddCharacteristicDeclarationAndValueIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddCharacteristicDeclarationAndValueIndication");
			break;

		case GATTDBDynamicAddCharacteristicDescriptorIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddCharacteristicDescriptorIndication");
			break;

		case GATTDBDynamicAddCccdIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddCccdIndication");
			break;

		case GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddCharacteristicDeclarationWithUniqueValueIndication");
			break;

		case GATTDBDynamicAddCharDescriptorWithUniqueValueIndication_FSCI_ID:
			shell_write("GATTDBDynamicAddCharDescriptorWithUniqueValueIndication");
			break;

#endif  /* GATTDB_APP_ENABLE */

#if GAP_ENABLE
		case GAPConfirm_FSCI_ID:
			shell_write("GAPConfirm");
			shell_write(" -> ");
			switch (container->Data.GAPConfirm.Status)
			{
				case GAPConfirm_Status_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPConfirm_Status_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPConfirm_Status_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPConfirm_Status_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPConfirm_Status_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPConfirm_Status_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPConfirm_Status_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPConfirm_Status_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPConfirm_Status_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPConfirm_Status_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPConfirm_Status_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPConfirm_Status_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPConfirm_Status_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPConfirm_Status_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPConfirm_Status_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPConfirm_Status_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPConfirm_Status_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPConfirm_Status_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPConfirm_Status_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPConfirm_Status_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPConfirm_Status_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPConfirm_Status_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPConfirm_Status_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPConfirm_Status_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPConfirm_Status_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPConfirm_Status_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPConfirm_Status_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPConfirm_Status_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPConfirm_Status_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPConfirm_Status_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPConfirm_Status_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPConfirm_Status_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPConfirm_Status_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPConfirm_Status_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPConfirm_Status_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPConfirm_Status_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPConfirm_Status_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPConfirm_Status_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPConfirm_Status_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPConfirm_Status_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPConfirm_Status_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPConfirm_Status_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPConfirm_Status_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPConfirm_Status_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPConfirm_Status_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPConfirm_Status_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPConfirm_Status_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPConfirm_Status_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPConfirm_Status_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPConfirm_Status_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPConfirm_Status_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPConfirm_Status_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPConfirm_Status_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPConfirm_Status_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPConfirm_Status_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPConfirm_Status_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPConfirm_Status_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPConfirm_Status_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPConfirm_Status_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPConfirm_Status_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPConfirm_Status_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPConfirm_Status_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPConfirm_Status_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPConfirm_Status_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPConfirm_Status_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPConfirm_Status_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPConfirm_Status_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPConfirm_Status_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPConfirm_Status_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPConfirm_Status_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPConfirm_Status_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPConfirm_Status_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPConfirm_Status_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPConfirm_Status_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPConfirm_Status_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPConfirm_Status_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPConfirm_Status_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPConfirm_Status_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPConfirm_Status_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPConfirm_Status_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPConfirm_Status_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPConfirm_Status_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPConfirm_Status_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPConfirm_Status_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPConfirm_Status_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPConfirm_Status_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPConfirm_Status_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPConfirm_Status_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPConfirm_Status_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPConfirm_Status_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPConfirm_Status_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPConfirm_Status_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPConfirm_Status_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPConfirm_Status_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPConfirm_Status_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPConfirm_Status_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPConfirm_Status_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPConfirm_Status_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPConfirm_Status_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPConfirm_Status_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPConfirm_Status_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPConfirm_Status_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPConfirm_Status_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPConfirm_Status_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPConfirm_Status_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPConfirm_Status_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPConfirm_Status_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPConfirm_Status_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPConfirm_Status_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPConfirm_Status_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPConfirm_Status_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPConfirm_Status_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPConfirm_Status_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPConfirm_Status_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPConfirm_Status_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPConfirm_Status_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPConfirm_Status_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPConfirm_Status_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPConfirm_Status_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPConfirm_Status_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPConfirm_Status_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPConfirm_Status_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPConfirm_Status_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPConfirm_Status_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPConfirm_Status_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPConfirm_Status_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPConfirm_Status_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPConfirm_Status_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPConfirm_Status_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPConfirm_Status_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPConfirm_Status_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPConfirm_Status_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPConfirm_Status_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPConfirm_Status_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPConfirm_Status_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPConfirm_Status_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPConfirm_Status_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPConfirm_Status_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPConfirm_Status_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPConfirm_Status_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPConfirm_Status_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPConfirm_Status_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPConfirm_Status_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPConfirm_Status_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPConfirm_Status_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPConfirm_Status_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPConfirm_Status_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPConfirm_Status_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPConfirm_Status_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPConfirm_Status_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPConfirm_Status_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPConfirm_Status_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPConfirm_Status_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPConfirm_Status_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPConfirm_Status_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPConfirm_Status_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPConfirm_Status_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPConfirm_Status_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPConfirm_Status_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPConfirm_Status_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPConfirm_Status_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPConfirm_Status_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPConfirm_Status_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPConfirm_Status_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPConfirm_Status_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPConfirm_Status_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPConfirm_Status_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPConfirm_Status_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPConfirm_Status_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPConfirm_Status_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPConfirm_Status_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPConfirm_Status_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPConfirm_Status_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPConfirm_Status_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPConfirm_Status_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPConfirm.Status);
					break;
			}
			break;

		case GAPCheckNotificationStatusIndication_FSCI_ID:
			shell_write("GAPCheckNotificationStatusIndication");
			break;

		case GAPCheckIndicationStatusIndication_FSCI_ID:
			shell_write("GAPCheckIndicationStatusIndication");
			break;

		case GAPLoadKeysIndication_FSCI_ID:
			shell_write("GAPLoadKeysIndication");
			shell_write(" -> ");
			switch (container->Data.GAPLoadKeysIndication.KeyFlags)
			{
				case GAPLoadKeysIndication_KeyFlags_gNoKeys_c:
					shell_write(gNoKeys_c);
					break;
				case GAPLoadKeysIndication_KeyFlags_gLtk_c:
					shell_write(gLtk_c);
					break;
				case GAPLoadKeysIndication_KeyFlags_gIrk_c:
					shell_write(gIrk_c);
					break;
				case GAPLoadKeysIndication_KeyFlags_gCsrk_c:
					shell_write(gCsrk_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPLoadKeysIndication.KeyFlags);
					break;
			}
			break;

		case GAPLoadEncryptionInformationIndication_FSCI_ID:
			shell_write("GAPLoadEncryptionInformationIndication");
			break;

		case GAPLoadCustomPeerInformationIndication_FSCI_ID:
			shell_write("GAPLoadCustomPeerInformationIndication");
			break;

		case GAPCheckIfBondedIndication_FSCI_ID:
			shell_write("GAPCheckIfBondedIndication");
			break;

		case GAPGetBondedDevicesCountIndication_FSCI_ID:
			shell_write("GAPGetBondedDevicesCountIndication");
			break;

		case GAPGetBondedDeviceNameIndication_FSCI_ID:
			shell_write("GAPGetBondedDeviceNameIndication");
			break;

		case GAPGenericEventInitializationCompleteIndication_FSCI_ID:
			shell_write("GAPGenericEventInitializationCompleteIndication");
			break;

		case GAPGenericEventInternalErrorIndication_FSCI_ID:
			shell_write("GAPGenericEventInternalErrorIndication");
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventInternalErrorIndication.ErrorCode)
			{
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorCode_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPGenericEventInternalErrorIndication.ErrorCode);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventInternalErrorIndication.ErrorSource)
			{
				case GAPGenericEventInternalErrorIndication_ErrorSource_gHciCommandStatus_c:
					shell_write(gHciCommandStatus_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gCheckPrivateResolvableAddress_c:
					shell_write(gCheckPrivateResolvableAddress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gVerifySignature_c:
					shell_write(gVerifySignature_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gAddNewConnection_c:
					shell_write(gAddNewConnection_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gResetController_c:
					shell_write(gResetController_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSetEventMask_c:
					shell_write(gSetEventMask_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadLeBufferSize_c:
					shell_write(gReadLeBufferSize_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSetLeEventMask_c:
					shell_write(gSetLeEventMask_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadDeviceAddress_c:
					shell_write(gReadDeviceAddress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadLocalSupportedFeatures_c:
					shell_write(gReadLocalSupportedFeatures_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadWhiteListSize_c:
					shell_write(gReadWhiteListSize_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gClearWhiteList_c:
					shell_write(gClearWhiteList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gAddDeviceToWhiteList_c:
					shell_write(gAddDeviceToWhiteList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gRemoveDeviceFromWhiteList_c:
					shell_write(gRemoveDeviceFromWhiteList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gCancelCreateConnection_c:
					shell_write(gCancelCreateConnection_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadRadioPower_c:
					shell_write(gReadRadioPower_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSetRandomAddress_c:
					shell_write(gSetRandomAddress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gCreateRandomAddress_c:
					shell_write(gCreateRandomAddress_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gEncryptLink_c:
					shell_write(gEncryptLink_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gProvideLongTermKey_c:
					shell_write(gProvideLongTermKey_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gDenyLongTermKey_c:
					shell_write(gDenyLongTermKey_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gConnect_c:
					shell_write(gConnect_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gDisconnect_c:
					shell_write(gDisconnect_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gTerminatePairing_c:
					shell_write(gTerminatePairing_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSendSlaveSecurityRequest_c:
					shell_write(gSendSlaveSecurityRequest_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gEnterPasskey_c:
					shell_write(gEnterPasskey_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gProvideOob_c:
					shell_write(gProvideOob_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSendSmpKeys_c:
					shell_write(gSendSmpKeys_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gWriteSuggestedDefaultDataLength_c:
					shell_write(gWriteSuggestedDefaultDataLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadSuggestedDefaultDataLength_c:
					shell_write(gReadSuggestedDefaultDataLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gUpdateLeDataLength_c:
					shell_write(gUpdateLeDataLength_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gEnableHostPrivacy_c:
					shell_write(gEnableHostPrivacy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gEnableControllerPrivacy_c:
					shell_write(gEnableControllerPrivacy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeScSendKeypressNotification_c:
					shell_write(gLeScSendKeypressNotification_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeScSetPeerOobData_c:
					shell_write(gLeScSetPeerOobData_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeScGetLocalOobData_c:
					shell_write(gLeScGetLocalOobData_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeScValidateNumericValue_c:
					shell_write(gLeScValidateNumericValue_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeScRegeneratePublicKey_c:
					shell_write(gLeScRegeneratePublicKey_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeSetResolvablePrivateAddressTimeout_c:
					shell_write(gLeSetResolvablePrivateAddressTimeout_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gDefaultPairingProcedure_c:
					shell_write(gDefaultPairingProcedure_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeControllerTest_c:
					shell_write(gLeControllerTest_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadPhy_c:
					shell_write(gLeReadPhy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeSetPhy_c:
					shell_write(gLeSetPhy_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSaveKeys_c:
					shell_write(gSaveKeys_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gSetChannelMap_c:
					shell_write(gSetChannelMap_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gReadLocalSupportedCommands_c:
					shell_write(gReadLocalSupportedCommands_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gEnableLdmTimer_c:
					shell_write(gEnableLdmTimer_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gRemoveAdvertisingSet_c:
					shell_write(gRemoveAdvertisingSet_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLePeriodicAdvSyncEstb_c:
					shell_write(gLePeriodicAdvSyncEstb_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLePeriodicAdvSyncLost_c:
					shell_write(gLePeriodicAdvSyncLost_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeRemoveDeviceFromPeriodicAdvList_c:
					shell_write(gLeRemoveDeviceFromPeriodicAdvList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeClearPeriodicAdvList_c:
					shell_write(gLeClearPeriodicAdvList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeAddDeviceToPeriodicAdvList_c:
					shell_write(gLeAddDeviceToPeriodicAdvList_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadNumOfSupportedAdvSets_c:
					shell_write(gLeReadNumOfSupportedAdvSets_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadPeriodicAdvListSize_c:
					shell_write(gLeReadPeriodicAdvListSize_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gLeReadMaxAdvDataLen_c:
					shell_write(gLeReadMaxAdvDataLen_c);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvCreateSync:
					shell_write(gPeriodicAdvCreateSync);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvCancelSync:
					shell_write(gPeriodicAdvCancelSync);
					break;
				case GAPGenericEventInternalErrorIndication_ErrorSource_gPeriodicAdvTerminateSync:
					shell_write(gPeriodicAdvTerminateSync);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPGenericEventInternalErrorIndication.ErrorSource);
					break;
			}
			break;

		case GAPGenericEventAdvertisingSetupFailedIndication_FSCI_ID:
			shell_write("GAPGenericEventAdvertisingSetupFailedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventAdvertisingSetupFailedIndication.SetupFailReason)
			{
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPGenericEventAdvertisingSetupFailedIndication_SetupFailReason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPGenericEventAdvertisingSetupFailedIndication.SetupFailReason);
					break;
			}
			break;

		case GAPGenericEventAdvertisingParametersSetupCompleteIndication_FSCI_ID:
			shell_write("GAPGenericEventAdvertisingParametersSetupCompleteIndication");
			break;

		case GAPGenericEventAdvertisingDataSetupCompleteIndication_FSCI_ID:
			shell_write("GAPGenericEventAdvertisingDataSetupCompleteIndication");
			break;

		case GAPGenericEventWhiteListSizeReadIndication_FSCI_ID:
			shell_write("GAPGenericEventWhiteListSizeReadIndication");
			break;

		case GAPGenericEventDeviceAddedToWhiteListIndication_FSCI_ID:
			shell_write("GAPGenericEventDeviceAddedToWhiteListIndication");
			break;

		case GAPGenericEventDeviceRemovedFromWhiteListIndication_FSCI_ID:
			shell_write("GAPGenericEventDeviceRemovedFromWhiteListIndication");
			break;

		case GAPGenericEventWhiteListClearedIndication_FSCI_ID:
			shell_write("GAPGenericEventWhiteListClearedIndication");
			break;

		case GAPGenericEventRandomAddressReadyIndication_FSCI_ID:
			shell_write("GAPGenericEventRandomAddressReadyIndication");
			break;

		case GAPGenericEventCreateConnectionCanceledIndication_FSCI_ID:
			shell_write("GAPGenericEventCreateConnectionCanceledIndication");
			break;

		case GAPGenericEventPublicAddressReadIndication_FSCI_ID:
			shell_write("GAPGenericEventPublicAddressReadIndication");
			break;

		case GAPGenericEventAdvTxPowerLevelReadIndication_FSCI_ID:
			shell_write("GAPGenericEventAdvTxPowerLevelReadIndication");
			break;

		case GAPGenericEventPrivateResolvableAddressVerifiedIndication_FSCI_ID:
			shell_write("GAPGenericEventPrivateResolvableAddressVerifiedIndication");
			break;

		case GAPGenericEventRandomAddressSetIndication_FSCI_ID:
			shell_write("GAPGenericEventRandomAddressSetIndication");
			break;

		case GAPAdvertisingEventStateChangedIndication_FSCI_ID:
			shell_write("GAPAdvertisingEventStateChangedIndication");
			break;

		case GAPAdvertisingEventCommandFailedIndication_FSCI_ID:
			shell_write("GAPAdvertisingEventCommandFailedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPAdvertisingEventCommandFailedIndication.FailReason)
			{
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPAdvertisingEventCommandFailedIndication_FailReason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPAdvertisingEventCommandFailedIndication.FailReason);
					break;
			}
			break;

		case GAPScanningEventStateChangedIndication_FSCI_ID:
			shell_write("GAPScanningEventStateChangedIndication");
			break;

		case GAPScanningEventCommandFailedIndication_FSCI_ID:
			shell_write("GAPScanningEventCommandFailedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPScanningEventCommandFailedIndication.FailReason)
			{
				case GAPScanningEventCommandFailedIndication_FailReason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPScanningEventCommandFailedIndication_FailReason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPScanningEventCommandFailedIndication.FailReason);
					break;
			}
			break;

		case GAPScanningEventDeviceScannedIndication_FSCI_ID:
			shell_write("GAPScanningEventDeviceScannedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPScanningEventDeviceScannedIndication.AddressType)
			{
				case GAPScanningEventDeviceScannedIndication_AddressType_gPublic_c:
					shell_write(gPublic_c);
					break;
				case GAPScanningEventDeviceScannedIndication_AddressType_gRandom_c:
					shell_write(gRandom_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPScanningEventDeviceScannedIndication.AddressType);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GAPScanningEventDeviceScannedIndication.AdvEventType)
			{
				case GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvInd_c:
					shell_write(gBleAdvRepAdvInd_c);
					break;
				case GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvDirectInd_c:
					shell_write(gBleAdvRepAdvDirectInd_c);
					break;
				case GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvScanInd_c:
					shell_write(gBleAdvRepAdvScanInd_c);
					break;
				case GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepAdvNonconnInd_c:
					shell_write(gBleAdvRepAdvNonconnInd_c);
					break;
				case GAPScanningEventDeviceScannedIndication_AdvEventType_gBleAdvRepScanRsp_c:
					shell_write(gBleAdvRepScanRsp_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPScanningEventDeviceScannedIndication.AdvEventType);
					break;
			}
			break;

		case GAPConnectionEventConnectedIndication_FSCI_ID:
			shell_write("GAPConnectionEventConnectedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventConnectedIndication.PeerAddressType)
			{
				case GAPConnectionEventConnectedIndication_PeerAddressType_gPublic_c:
					shell_write(gPublic_c);
					break;
				case GAPConnectionEventConnectedIndication_PeerAddressType_gRandom_c:
					shell_write(gRandom_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventConnectedIndication.PeerAddressType);
					break;
			}
			break;

		case GAPConnectionEventPairingRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventPairingRequestIndication");
			break;

		case GAPConnectionEventSlaveSecurityRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventSlaveSecurityRequestIndication");
			break;

		case GAPConnectionEventPairingResponseIndication_FSCI_ID:
			shell_write("GAPConnectionEventPairingResponseIndication");
			break;

		case GAPConnectionEventAuthenticationRejectedIndication_FSCI_ID:
			shell_write("GAPConnectionEventAuthenticationRejectedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventAuthenticationRejectedIndication.RejectReason)
			{
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gOobNotAvailable_c:
					shell_write(gOobNotAvailable_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gIncompatibleIoCapabilities_c:
					shell_write(gIncompatibleIoCapabilities_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gPairingNotSupported_c:
					shell_write(gPairingNotSupported_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gLowEncryptionKeySize_c:
					shell_write(gLowEncryptionKeySize_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gUnspecifiedReason_c:
					shell_write(gUnspecifiedReason_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gRepeatedAttempts_c:
					shell_write(gRepeatedAttempts_c);
					break;
				case GAPConnectionEventAuthenticationRejectedIndication_RejectReason_gLinkEncryptionFailed_c:
					shell_write(gLinkEncryptionFailed_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventAuthenticationRejectedIndication.RejectReason);
					break;
			}
			break;

		case GAPConnectionEventPasskeyRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventPasskeyRequestIndication");
			break;

		case GAPConnectionEventOobRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventOobRequestIndication");
			break;

		case GAPConnectionEventPasskeyDisplayIndication_FSCI_ID:
			shell_write("GAPConnectionEventPasskeyDisplayIndication");
			break;

		case GAPConnectionEventKeyExchangeRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventKeyExchangeRequestIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventKeyExchangeRequestIndication.RequestedKeys)
			{
				case GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gNoKeys_c:
					shell_write(gNoKeys_c);
					break;
				case GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gLtk_c:
					shell_write(gLtk_c);
					break;
				case GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gIrk_c:
					shell_write(gIrk_c);
					break;
				case GAPConnectionEventKeyExchangeRequestIndication_RequestedKeys_gCsrk_c:
					shell_write(gCsrk_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventKeyExchangeRequestIndication.RequestedKeys);
					break;
			}
			break;

		case GAPConnectionEventKeysReceivedIndication_FSCI_ID:
			shell_write("GAPConnectionEventKeysReceivedIndication");
			break;

		case GAPConnectionEventLongTermKeyRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventLongTermKeyRequestIndication");
			break;

		case GAPConnectionEventEncryptionChangedIndication_FSCI_ID:
			shell_write("GAPConnectionEventEncryptionChangedIndication");
			break;

		case GAPConnectionEventPairingCompleteIndication_FSCI_ID:
			shell_write("GAPConnectionEventPairingCompleteIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventPairingCompleteIndication.PairingStatus)
			{
				case GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingSuccessful:
					shell_write(PairingSuccessful);
					break;
				case GAPConnectionEventPairingCompleteIndication_PairingStatus_PairingFailed:
					shell_write(PairingFailed);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventPairingCompleteIndication.PairingStatus);
					break;
			}
			break;

		case GAPConnectionEventDisconnectedIndication_FSCI_ID:
			shell_write("GAPConnectionEventDisconnectedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventDisconnectedIndication.Reason)
			{
				case GAPConnectionEventDisconnectedIndication_Reason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationc);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownc);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPConnectionEventDisconnectedIndication_Reason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPConnectionEventDisconnectedIndication.Reason);
					break;
			}
			break;

		case GAPConnectionEventRssiReadIndication_FSCI_ID:
			shell_write("GAPConnectionEventRssiReadIndication");
			break;

		case GAPConnectionEventTxPowerLevelReadIndication_FSCI_ID:
			shell_write("GAPConnectionEventTxPowerLevelReadIndication");
			break;

		case GAPConnectionEventPowerReadFailureIndication_FSCI_ID:
			shell_write("GAPConnectionEventPowerReadFailureIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventPowerReadFailureIndication.FailReason)
			{
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPConnectionEventPowerReadFailureIndication_FailReason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPConnectionEventPowerReadFailureIndication.FailReason);
					break;
			}
			break;

		case GAPConnectionEventParameterUpdateRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventParameterUpdateRequestIndication");
			break;

		case GAPConnectionEventParameterUpdateCompleteIndication_FSCI_ID:
			shell_write("GAPConnectionEventParameterUpdateCompleteIndication");
			break;

		case GAPConnectionEventLeDataLengthChangedIndication_FSCI_ID:
			shell_write("GAPConnectionEventLeDataLengthChangedIndication");
			break;

		case GAPConnectionEventLeScOobDataRequestIndication_FSCI_ID:
			shell_write("GAPConnectionEventLeScOobDataRequestIndication");
			break;

		case GAPConnectionEventLeScDisplayNumericValueIndication_FSCI_ID:
			shell_write("GAPConnectionEventLeScDisplayNumericValueIndication");
			break;

		case GAPConnectionEventLeScKeypressNotificationIndication_FSCI_ID:
			shell_write("GAPConnectionEventLeScKeypressNotificationIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventLeScKeypressNotificationIndication.GapLeScKeypressNotificationParams_keypressNotifType)
			{
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPConnectionEventLeScKeypressNotificationIndication.GapLeScKeypressNotificationParams_keypressNotifType);
					break;
			}
			break;

		case GAPGenericEventControllerResetCompleteIndication_FSCI_ID:
			shell_write("GAPGenericEventControllerResetCompleteIndication");
			break;

		case GAPLeScPublicKeyRegeneratedIndication_FSCI_ID:
			shell_write("GAPLeScPublicKeyRegeneratedIndication");
			break;

		case GAPGenericEventLeScLocalOobDataIndication_FSCI_ID:
			shell_write("GAPGenericEventLeScLocalOobDataIndication");
			break;

		case GAPGenericEventHostPrivacyStateChangedIndication_FSCI_ID:
			shell_write("GAPGenericEventHostPrivacyStateChangedIndication");
			break;

		case GAPGenericEventControllerPrivacyStateChangedIndication_FSCI_ID:
			shell_write("GAPGenericEventControllerPrivacyStateChangedIndication");
			break;

		case GAPGenericEventTxPowerLevelSetCompleteIndication_FSCI_ID:
			shell_write("GAPGenericEventTxPowerLevelSetCompleteIndication");
			break;

		case GAPGenericEventLePhyEventIndication_FSCI_ID:
			shell_write("GAPGenericEventLePhyEventIndication");
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventLePhyEventIndication.eventType)
			{
				case GAPGenericEventLePhyEventIndication_eventType_gPhySetDefaultComplete_c:
					shell_write(gPhySetDefaultComplete_c);
					break;
				case GAPGenericEventLePhyEventIndication_eventType_gPhyRead_c:
					shell_write(gPhyRead_c);
					break;
				case GAPGenericEventLePhyEventIndication_eventType_gPhyUpdateComplete_c:
					shell_write(gPhyUpdateComplete_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPGenericEventLePhyEventIndication.eventType);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventLePhyEventIndication.txPhy)
			{
				case GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhy1M_c:
					shell_write(gLeTxPhy1M_c);
					break;
				case GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhy2M_c:
					shell_write(gLeTxPhy2M_c);
					break;
				case GAPGenericEventLePhyEventIndication_txPhy_gLeTxPhyCoded_c:
					shell_write(gLeTxPhyCoded_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPGenericEventLePhyEventIndication.txPhy);
					break;
			}
			shell_write(" -> ");
			switch (container->Data.GAPGenericEventLePhyEventIndication.rxPhy)
			{
				case GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhy1M_c:
					shell_write(gLeRxPhy1M_c);
					break;
				case GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhy2M_c:
					shell_write(gLeRxPhy2M_c);
					break;
				case GAPGenericEventLePhyEventIndication_rxPhy_gLeRxPhyCoded_c:
					shell_write(gLeRxPhyCoded_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPGenericEventLePhyEventIndication.rxPhy);
					break;
			}
			break;

		case GAPGetBondedDevicesIdentityInformationIndication_FSCI_ID:
			shell_write("GAPGetBondedDevicesIdentityInformationIndication");
			break;

		case GAPControllerNotificationIndication_FSCI_ID:
			shell_write("GAPControllerNotificationIndication");
			shell_write(" -> ");
			switch (container->Data.GAPControllerNotificationIndication.EventType)
			{
				case GAPControllerNotificationIndication_EventType_gNotifConnEventOver_c:
					shell_write(gNotifConnEventOver_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifConnRxPdu_c:
					shell_write(gNotifConnRxPdu_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifAdvEventOver_c:
					shell_write(gNotifAdvEventOver_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifAdvTx_c:
					shell_write(gNotifAdvTx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifAdvScanReqRx_c:
					shell_write(gNotifAdvScanReqRx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifAdvConnReqRx_c:
					shell_write(gNotifAdvConnReqRx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifScanEventOver_c:
					shell_write(gNotifScanEventOver_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifScanAdvPktRx_c:
					shell_write(gNotifScanAdvPktRx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifScanRspRx_c:
					shell_write(gNotifScanRspRx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifScanReqTx_c:
					shell_write(gNotifScanReqTx_c);
					break;
				case GAPControllerNotificationIndication_EventType_gNotifConnCreated_c:
					shell_write(gNotifConnCreated_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPControllerNotificationIndication.EventType);
					break;
			}
			break;

		case GAPBondCreatedIndication_FSCI_ID:
			shell_write("GAPBondCreatedIndication");
			shell_write(" -> ");
			switch (container->Data.GAPBondCreatedIndication.AddrType)
			{
				case GAPBondCreatedIndication_AddrType_gPublic_c:
					shell_write(gPublic_c);
					break;
				case GAPBondCreatedIndication_AddrType_gRandom_c:
					shell_write(gRandom_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%02X", container->Data.GAPBondCreatedIndication.AddrType);
					break;
			}
			break;

		case GAPGenericEventChannelMapSetIndication_FSCI_ID:
			shell_write("GAPGenericEventChannelMapSetIndication");
			break;

		case GAPConnectionEventChannelMapReadIndication_FSCI_ID:
			shell_write("GAPConnectionEventChannelMapReadIndication");
			break;

		case GAPConnectionEventChannelMapReadFailureIndication_FSCI_ID:
			shell_write("GAPConnectionEventChannelMapReadFailureIndication");
			shell_write(" -> ");
			switch (container->Data.GAPConnectionEventChannelMapReadFailureIndication.FailReason)
			{
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleSuccess_c:
					shell_write(gBleSuccess_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleInvalidParameter_c:
					shell_write(gBleInvalidParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOverflow_c:
					shell_write(gBleOverflow_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleUnavailable_c:
					shell_write(gBleUnavailable_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleFeatureNotSupported_c:
					shell_write(gBleFeatureNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOutOfMemory_c:
					shell_write(gBleOutOfMemory_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleAlreadyInitialized_c:
					shell_write(gBleAlreadyInitialized_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleOsError_c:
					shell_write(gBleOsError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleUnexpectedError_c:
					shell_write(gBleUnexpectedError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleInvalidState_c:
					shell_write(gBleInvalidState_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gBleTimerError_c:
					shell_write(gBleTimerError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownHciCommand_c:
					shell_write(gHciUnknownHciCommand_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownConnectionIdentifier_c:
					shell_write(gHciUnknownConnectionIdentifier_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciHardwareFailure_c:
					shell_write(gHciHardwareFailure_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPageTimeout_c:
					shell_write(gHciPageTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAuthenticationFailure_c:
					shell_write(gHciAuthenticationFailure_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPinOrKeyMissing_c:
					shell_write(gHciPinOrKeyMissing_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciMemoryCapacityExceeded_c:
					shell_write(gHciMemoryCapacityExceeded_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTimeout_c:
					shell_write(gHciConnectionTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionLimitExceeded_c:
					shell_write(gHciConnectionLimitExceeded_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciSynchronousConnectionLimitToADeviceExceeded_c:
					shell_write(gHciSynchronousConnectionLimitToADeviceExceeded_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAclConnectionAlreadyExists_c:
					shell_write(gHciAclConnectionAlreadyExists_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCommandDisallowed_c:
					shell_write(gHciCommandDisallowed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToLimitedResources_c:
					shell_write(gHciConnectionRejectedDueToLimitedResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToSecurityReasons_c:
					shell_write(gHciConnectionRejectedDueToSecurityReasons_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToUnacceptableBdAddr_c:
					shell_write(gHciConnectionRejectedDueToUnacceptableBdAddr_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionAcceptTimeoutExceeded_c:
					shell_write(gHciConnectionAcceptTimeoutExceeded_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedFeatureOrParameterValue_c:
					shell_write(gHciUnsupportedFeatureOrParameterValue_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidHciCommandParameters_c:
					shell_write(gHciInvalidHciCommandParameters_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteUserTerminatedConnection_c:
					shell_write(gHciRemoteUserTerminatedConnection_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionLowResources_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionLowResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRemoteDeviceTerminatedConnectionPowerOff_c:
					shell_write(gHciRemoteDeviceTerminatedConnectionPowerOff_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTerminatedByLocalHost_c:
					shell_write(gHciConnectionTerminatedByLocalHost_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRepeatedAttempts_c:
					shell_write(gHciRepeatedAttempts_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPairingNotAllowed_c:
					shell_write(gHciPairingNotAllowed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownLpmPdu_c:
					shell_write(gHciUnknownLpmPdu_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedRemoteFeature_c:
					shell_write(gHciUnsupportedRemoteFeature_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoOffsetRejected_c:
					shell_write(gHciScoOffsetRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoIntervalRejected_c:
					shell_write(gHciScoIntervalRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciScoAirModeRejected_c:
					shell_write(gHciScoAirModeRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidLpmParameters_c:
					shell_write(gHciInvalidLpmParameters_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnspecifiedError_c:
					shell_write(gHciUnspecifiedError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnsupportedLpmParameterValue_c:
					shell_write(gHciUnsupportedLpmParameterValue_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleChangeNotAllowed_c:
					shell_write(gHciRoleChangeNotAllowed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLLResponseTimeout_c:
					shell_write(gHciLLResponseTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLmpErrorTransactionCollision_c:
					shell_write(gHciLmpErrorTransactionCollision_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLmpPduNotAllowed_c:
					shell_write(gHciLmpPduNotAllowed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciEncryptionModeNotAcceptable_c:
					shell_write(gHciEncryptionModeNotAcceptable_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLinkKeyCannotBeChanged_c:
					shell_write(gHciLinkKeyCannotBeChanged_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRequestedQosNotSupported_c:
					shell_write(gHciRequestedQosNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInstantPassed_c:
					shell_write(gHciInstantPassed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciPairingWithUnitKeyNotSupported_c:
					shell_write(gHciPairingWithUnitKeyNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciDifferentTransactionCollision_c:
					shell_write(gHciDifferentTransactionCollision_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x2B_c:
					shell_write(gHciReserved_0x2B_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciQosNotAcceptableParameter_c:
					shell_write(gHciQosNotAcceptableParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciQosRejected_c:
					shell_write(gHciQosRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciChannelClassificationNotSupported_c:
					shell_write(gHciChannelClassificationNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInsufficientSecurity_c:
					shell_write(gHciInsufficientSecurity_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciParameterOutOfMandatoryRange_c:
					shell_write(gHciParameterOutOfMandatoryRange_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x31_c:
					shell_write(gHciReserved_0x31_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleSwitchPending_c:
					shell_write(gHciRoleSwitchPending_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReserved_0x33_c:
					shell_write(gHciReserved_0x33_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciReservedSlotViolation_c:
					shell_write(gHciReservedSlotViolation_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciRoleSwitchFailed_c:
					shell_write(gHciRoleSwitchFailed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciExtendedInquiryResponseTooLarge_c:
					shell_write(gHciExtendedInquiryResponseTooLarge_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciSecureSimplePairingNotSupportedByHost_c:
					shell_write(gHciSecureSimplePairingNotSupportedByHost_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciHostBusyPairing_c:
					shell_write(gHciHostBusyPairing_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionRejectedDueToNoSuitableChannelFound_c:
					shell_write(gHciConnectionRejectedDueToNoSuitableChannelFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciControllerBusy_c:
					shell_write(gHciControllerBusy_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnacceptableConnectionParameters_c:
					shell_write(gHciUnacceptableConnectionParameters_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciDirectedAdvertisingTimeout_c:
					shell_write(gHciDirectedAdvertisingTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionTerminatedDueToMicFailure_c:
					shell_write(gHciConnectionTerminatedDueToMicFailure_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciConnectionFailedToBeEstablishedOrSyncTimeout_c:
					shell_write(gHciConnectionFailedToBeEstablishedOrSyncTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciMacConnectionFailed_c:
					shell_write(gHciMacConnectionFailed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCoarseClockAdjustmentRejected_c:
					shell_write(gHciCoarseClockAdjustmentRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciType0SubmapNotDefined_c:
					shell_write(gHciType0SubmapNotDefined_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciUnknownAdvertisingIdentifier_c:
					shell_write(gHciUnknownAdvertisingIdentifier_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciLimitReached_c:
					shell_write(gHciLimitReached_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciOperationCancelledByHost_c:
					shell_write(gHciOperationCancelledByHost_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciAlreadyInit_c:
					shell_write(gHciAlreadyInit_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciInvalidParameter_c:
					shell_write(gHciInvalidParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCallbackNotInstalled_c:
					shell_write(gHciCallbackNotInstalled_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCallbackAlreadyInstalled_c:
					shell_write(gHciCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciCommandNotSupported_c:
					shell_write(gHciCommandNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciEventNotSupported_c:
					shell_write(gHciEventNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gHciTransportError_c:
					shell_write(gHciTransportError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caAlreadyInit_c:
					shell_write(gL2caAlreadyInit_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caInsufficientResources_c:
					shell_write(gL2caInsufficientResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caCallbackNotInstalled_c:
					shell_write(gL2caCallbackNotInstalled_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caCallbackAlreadyInstalled_c:
					shell_write(gL2caCallbackAlreadyInstalled_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmInvalid_c:
					shell_write(gL2caLePsmInvalid_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmAlreadyRegistered_c:
					shell_write(gL2caLePsmAlreadyRegistered_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmNotRegistered_c:
					shell_write(gL2caLePsmNotRegistered_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caLePsmInsufficientResources_c:
					shell_write(gL2caLePsmInsufficientResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelInvalid_c:
					shell_write(gL2caChannelInvalid_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelClosed_c:
					shell_write(gL2caChannelClosed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelAlreadyConnected_c:
					shell_write(gL2caChannelAlreadyConnected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caConnectionParametersRejected_c:
					shell_write(gL2caConnectionParametersRejected_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caChannelBusy_c:
					shell_write(gL2caChannelBusy_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caInvalidParameter_c:
					shell_write(gL2caInvalidParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gL2caError_c:
					shell_write(gL2caError_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmNullCBFunction_c:
					shell_write(gSmNullCBFunction_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmCommandNotSupported_c:
					shell_write(gSmCommandNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedCommand_c:
					shell_write(gSmUnexpectedCommand_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandCode_c:
					shell_write(gSmInvalidCommandCode_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandLength_c:
					shell_write(gSmInvalidCommandLength_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidCommandParameter_c:
					shell_write(gSmInvalidCommandParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidDeviceId_c:
					shell_write(gSmInvalidDeviceId_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidInternalOperation_c:
					shell_write(gSmInvalidInternalOperation_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidConnectionHandle_c:
					shell_write(gSmInvalidConnectionHandle_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInproperKeyDistributionField_c:
					shell_write(gSmInproperKeyDistributionField_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedKeyType_c:
					shell_write(gSmUnexpectedKeyType_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedPairingTerminationReason_c:
					shell_write(gSmUnexpectedPairingTerminationReason_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnexpectedKeyset_c:
					shell_write(gSmUnexpectedKeyset_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmSmpTimeoutOccurred_c:
					shell_write(gSmSmpTimeoutOccurred_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnknownSmpPacketType_c:
					shell_write(gSmUnknownSmpPacketType_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidSmpPacketLength_c:
					shell_write(gSmInvalidSmpPacketLength_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidSmpPacketParameter_c:
					shell_write(gSmInvalidSmpPacketParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedUnexpectedSmpPacket_c:
					shell_write(gSmReceivedUnexpectedSmpPacket_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedSmpPacketFromUnknownDevice_c:
					shell_write(gSmReceivedSmpPacketFromUnknownDevice_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedUnexpectedHciEvent_c:
					shell_write(gSmReceivedUnexpectedHciEvent_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedHciEventFromUnknownDevice_c:
					shell_write(gSmReceivedHciEventFromUnknownDevice_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInvalidHciEventParameter_c:
					shell_write(gSmInvalidHciEventParameter_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmLlConnectionEncryptionInProgress_c:
					shell_write(gSmLlConnectionEncryptionInProgress_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmLlConnectionEncryptionFailure_c:
					shell_write(gSmLlConnectionEncryptionFailure_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmInsufficientResources_c:
					shell_write(gSmInsufficientResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmOobDataAddressMismatch_c:
					shell_write(gSmOobDataAddressMismatch_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmSmpPacketReceivedAfterTimeoutOccurred_c:
					shell_write(gSmSmpPacketReceivedAfterTimeoutOccurred_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmReceivedTimerEventForUnknownDevice_c:
					shell_write(gSmReceivedTimerEventForUnknownDevice_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableLocalDeviceSecRequirements_c:
					shell_write(gSmUnattainableLocalDeviceSecRequirements_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableLocalDeviceMinKeySize_c:
					shell_write(gSmUnattainableLocalDeviceMinKeySize_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmUnattainableSlaveSecReqRequirements_c:
					shell_write(gSmUnattainableSlaveSecReqRequirements_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorPasskeyEntryFailed_c:
					shell_write(gSmPairingErrorPasskeyEntryFailed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorConfirmValueFailed_c:
					shell_write(gSmPairingErrorConfirmValueFailed_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorCommandNotSupported_c:
					shell_write(gSmPairingErrorCommandNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorInvalidParameters_c:
					shell_write(gSmPairingErrorInvalidParameters_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmPairingErrorUnknownReason_c:
					shell_write(gSmPairingErrorUnknownReason_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmTbResolvableAddressDoesNotMatchIrk_c:
					shell_write(gSmTbResolvableAddressDoesNotMatchIrk_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gSmTbInvalidDataSignature_c:
					shell_write(gSmTbInvalidDataSignature_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidHandle_c:
					shell_write(gAttInvalidHandle_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttReadNotPermitted_c:
					shell_write(gAttReadNotPermitted_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttWriteNotPermitted_c:
					shell_write(gAttWriteNotPermitted_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidPdu_c:
					shell_write(gAttInvalidPdu_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientAuthentication_c:
					shell_write(gAttInsufficientAuthentication_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttRequestNotSupported_c:
					shell_write(gAttRequestNotSupported_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidOffset_c:
					shell_write(gAttInvalidOffset_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientAuthorization_c:
					shell_write(gAttInsufficientAuthorization_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttPrepareQueueFull_c:
					shell_write(gAttPrepareQueueFull_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttAttributeNotFound_c:
					shell_write(gAttAttributeNotFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttAttributeNotLong_c:
					shell_write(gAttAttributeNotLong_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientEncryptionKeySize_c:
					shell_write(gAttInsufficientEncryptionKeySize_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInvalidAttributeValueLength_c:
					shell_write(gAttInvalidAttributeValueLength_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttUnlikelyor_c:
					shell_write(gAttUnlikelyor_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientEncryption_c:
					shell_write(gAttInsufficientEncryption_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttUnsupportedGroupType_c:
					shell_write(gAttUnsupportedGroupType_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gAttInsufficientResources_c:
					shell_write(gAttInsufficientResources_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattAnotherProcedureInProgress_c:
					shell_write(gGattAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattLongAttributePacketsCorrupted_c:
					shell_write(gGattLongAttributePacketsCorrupted_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattMultipleAttributesOverflow_c:
					shell_write(gGattMultipleAttributesOverflow_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattUnexpectedReadMultipleResponseLength_c:
					shell_write(gGattUnexpectedReadMultipleResponseLength_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattInvalidValueLength_c:
					shell_write(gGattInvalidValueLength_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattServerTimeout_c:
					shell_write(gGattServerTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattIndicationAlreadyInProgress_c:
					shell_write(gGattIndicationAlreadyInProgress_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattClientConfirmationTimeout_c:
					shell_write(gGattClientConfirmationTimeout_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapAdvDataTooLong_c:
					shell_write(gGapAdvDataTooLong_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapScanRspDataTooLong_c:
					shell_write(gGapScanRspDataTooLong_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapDeviceNotBonded_c:
					shell_write(gGapDeviceNotBonded_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGapAnotherProcedureInProgress_c:
					shell_write(gGapAnotherProcedureInProgress_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gDevDbCccdLimitReached_c:
					shell_write(gDevDbCccdLimitReached_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gDevDbCccdNotFound_c:
					shell_write(gDevDbCccdNotFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbInvalidHandle_c:
					shell_write(gGattDbInvalidHandle_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbCharacteristicNotFound_c:
					shell_write(gGattDbCharacteristicNotFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbCccdNotFound_c:
					shell_write(gGattDbCccdNotFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbServiceNotFound_c:
					shell_write(gGattDbServiceNotFound_c);
					break;
				case GAPConnectionEventChannelMapReadFailureIndication_FailReason_gGattDbDescriptorNotFound_c:
					shell_write(gGattDbDescriptorNotFound_c);
					break;
				default:
					shell_printf("Unrecognized status 0x%04X", container->Data.GAPConnectionEventChannelMapReadFailureIndication.FailReason);
					break;
			}
			break;

		case GAPConnectionEventChannelSelectionAlgorithm2Indication_FSCI_ID:
			shell_write("GAPConnectionEventChannelSelectionAlgorithm2Indication");
			break;

		case GAPGenericEventTxEntryAvailableIndication_FSCI_ID:
			shell_write("GAPGenericEventTxEntryAvailableIndication");
			break;

#endif  /* GAP_ENABLE */

	}

	shell_refresh();
}
