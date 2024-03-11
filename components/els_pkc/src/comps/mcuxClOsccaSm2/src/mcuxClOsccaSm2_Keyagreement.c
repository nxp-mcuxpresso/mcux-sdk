/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClOsccaSm2_Keyagreement.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 Sign function
 */
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_key_agreement, mcuxClKey_AgreementFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClOsccaSm2_key_agreement(
    mcuxClSession_Handle_t session,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Handle_t key,
    mcuxClKey_Handle_t otherKey,
    mcuxClKey_Agreement_AdditionalInput_t additionalInputs[],
    uint32_t numberOfInputs,
    uint8_t * pOut,
    uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_key_agreement);

    /*****************************************************/
    /* Perform key agreement operation                   */
    /*****************************************************/
    /* Setup the parameters used by SM2 internal functions */

    /* Set up SM2 key, to be used internally in SM2 functions */
    /* Set up domain parameters, to be used internally in SM2 functions */
    uint8_t* privateKey = mcuxClKey_getKeyData(key);
    uint8_t* publicKeyParty2 = mcuxClKey_getKeyData(otherKey);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);

    /* Setup the parameters used by SM2 internal functions, based on the protocol descriptor */
    uint16_t options = ((const mcuxClOsccaSm2_AgreementProtocolDescriptor_t*)agreement->pProtocolDescriptor)->options;

    /****************************************************************/
    /* OSCCA SM2 key agreement                                      */
    /****************************************************************/
    /* Create parameter structure for function mcuxClOsccaSm2_KeyExchange */
    mcuxClOsccaSm2_KeyExchange_Param_t param;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(param.domainParameters, (*pSm2DomainParams));
    param.pPrivateKey = privateKey;
    param.pPublicKeyParty2 = publicKeyParty2;
    param.pCommonSecret = pOut;
    param.commonSecretLength = *pOutLength;

    if (numberOfInputs != MCUXCLOSCCASM2_KEYAGREEMENT_NUM_OF_ADDITIONAL_INPUTS)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_key_agreement, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }
    param.pPreHashInfoInitiator = additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_PREHASH_INITIATOR].input;
    param.pPreHashInfoResponder = additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_PREHASH_RESPONDER].input;
    param.pPrivateEphemeralScalar = additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_PRIVATEEPHEMERALKEY].input;
    param.pPublicEphemeralPoint = additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_PUBLICEPHEMERALPOINT].input;
    param.pPublicEphemeralPointParty2 = additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_PUBLICEPHEMERALPOINT_PARTY2].input;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to set the generic pointer.")
    param.pConfirmationFromResponderToInitiator = (mcuxCl_Buffer_t)(additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_CONFIRMATION_R2I].input);
    param.pConfirmationFromInitiatorToResponder = (mcuxCl_Buffer_t)(additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_CONFIRMATION_I2R].input);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
    param.options = options;

    /* Call function mcuxClOsccaSm2_KeyExchange */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2KeyExchgRet, mcuxClOsccaSm2_KeyExchange(session, &param));
    if (MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_OK != SM2KeyExchgRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_key_agreement, MCUXCLKEY_STATUS_FAILURE, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_key_agreement, MCUXCLKEY_STATUS_OK, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange));

}
