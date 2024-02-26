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
 * @file  mcuxClEcc_EdDSA_Internal_SignatureMechanisms.c
 * @brief implementation of functions for signature modes
 */

#include <mcuxClCore_Platform.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_GenerateHashPrefix)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateHashPrefix(
    const mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint32_t phflag,
    mcuxCl_InputBuffer_t pContext,
    uint32_t contextLen,
    mcuxCl_Buffer_t pHashPrefix)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_GenerateHashPrefix);

    uint8_t *pHashPrefixTmp = (uint8_t*) pHashPrefix;

    /* Check whether the pContext is not NULL if the contextLen is set */
    if (((0u < contextLen) && (NULL == pContext)) || (255u < contextLen) || (2u < phflag))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateHashPrefix, MCUXCLECC_STATUS_INVALID_PARAMS);
    }

    /* Check whether the pDomPrefix is not NULL if the domPrefixLen is set */
    /* pHashPrefixTmp is not NULL and allocate the buffer pHashPrefix with sufficient size */
    if ((MCUXCLECC_EDDSA_ED25519_DOMPREFIXLEN < pDomainParams->domPrefixLen) || (NULL == pDomainParams->pDomPrefix)
        || (NULL == pHashPrefixTmp))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateHashPrefix, MCUXCLECC_STATUS_INVALID_PARAMS);
    }

    /* Write the fixed prefix string for dom2/dom4 to the output buffer */
    MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pHashPrefixTmp,
                                        (const uint8_t*)pDomainParams->pDomPrefix,
                                        pDomainParams->domPrefixLen,
                                        MCUXCLECC_EDDSA_ED25519_SIZE_HASH_PREFIX(contextLen));
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pHashPrefixTmp will be in the valid range pHashPrefix[0 ~ pDomainParams->domPrefixLen+contextLen+1u].")
    pHashPrefixTmp += pDomainParams->domPrefixLen;

    /* Write phflag to the output buffer */
    *pHashPrefixTmp = (uint8_t)phflag;
    pHashPrefixTmp++;
    /* Write contextLen to the output buffer */
    *pHashPrefixTmp = (uint8_t)contextLen;
    pHashPrefixTmp++;
    /* Write pContext to the output buffer */
    MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pHashPrefixTmp,
                                        pContext,
                                        contextLen,
                                        MCUXCLECC_EDDSA_ED25519_SIZE_HASH_PREFIX(contextLen));
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateHashPrefix, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_PreHashMessage)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_PreHashMessage(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint32_t phflag,
    const uint8_t *pIn,
    uint32_t inSize,
    const uint8_t **pMessage,
    uint32_t *messageSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_PreHashMessage);

    MCUX_CSSL_FP_BRANCH_DECL(phflagSet);
    if (MCUXCLECC_EDDSA_PHFLAG_ONE == phflag)
    {
        /* phflag is set, pre-hash the message */
        uint8_t *pMessageTmp = (uint8_t*) mcuxClSession_allocateWords_cpuWa(pSession, (uint32_t)pDomainParams->b / 4u);
        uint32_t hashOutputSize = 0u;

        MCUX_CSSL_FP_FUNCTION_CALL(hash_result, mcuxClHash_compute(pSession, pDomainParams->algoHash, pIn, inSize, pMessageTmp, &hashOutputSize));

        if (MCUXCLHASH_STATUS_OK != hash_result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_PreHashMessage, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        *pMessage = (const uint8_t *) pMessageTmp;
        *messageSize = (uint32_t)pDomainParams->b / 4u;

        MCUX_CSSL_FP_BRANCH_POSITIVE(phflagSet, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) );
    }
    else if (MCUXCLECC_EDDSA_PHFLAG_ZERO == phflag)
    {
        /* phflag is not set, the message is not modified */
        *pMessage = pIn;
        *messageSize = inSize;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_PreHashMessage, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_PreHashMessage, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(phflagSet, MCUXCLECC_EDDSA_PHFLAG_ONE == phflag) );
}
