/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/**
 * @file  mcuxClEcc_EdDSA_GenerateSignatureMode.c
 * @brief implementation of signature modes
 */

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClSession.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClEcc_EdDSA_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_GenerateProtocolDescriptor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateProtocolDescriptor(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *pProtocolDescriptor,
    uint32_t phflag,
    mcuxCl_InputBuffer_t pContext,
    uint32_t contextLen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_GenerateProtocolDescriptor);

    (void) pSession;

    /* Create pHashPrefix buffer after the protocol descriptor. */
    /* It is assumed that sufficient space was allocated by users, with the macro MCUXCLECC_EDDSA_ED25519_SIZE_HASH_PREFIX() */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxCl_Buffer_t pHashPrefix = (mcuxCl_Buffer_t) ((uint8_t*)pProtocolDescriptor + sizeof(mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* Generate the hash prefix */
    MCUX_CSSL_FP_FUNCTION_CALL(retVal_GenHashPrefix, mcuxClEcc_EdDSA_GenerateHashPrefix(pDomainParams, phflag, pContext, contextLen, pHashPrefix));
    if (MCUXCLECC_STATUS_OK != retVal_GenHashPrefix)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateHashPrefix, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    pProtocolDescriptor->generateOption = 0u;
    pProtocolDescriptor->verifyOption = 0u;
    pProtocolDescriptor->phflag = phflag;
    pProtocolDescriptor->pHashPrefix = (const uint8_t*)pHashPrefix;
    pProtocolDescriptor->hashPrefixLen = MCUXCLECC_EDDSA_ED25519_SIZE_HASH_PREFIX(contextLen);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_GenerateProtocolDescriptor, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateHashPrefix) );
}

