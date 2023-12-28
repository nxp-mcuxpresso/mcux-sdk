/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClEcc_WeierECC_Internal_GenerateCustomKeyType.c
 * @brief Implementation of the custom key type constructor.
 */


#include <mcuxClKey.h>
#include <mcuxClEcc_WeierECC.h>
#include <internal/mcuxClKey_Types_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_WeierECC_GenerateCustomKeyType)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_WeierECC_GenerateCustomKeyType(
    mcuxClKey_CustomType_t customType,
    mcuxClKey_AlgorithmId_t algoId,
    mcuxClKey_Size_t size,
    void *pCustomParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_WeierECC_GenerateCustomKeyType);

    /* Extract algo and usage specifiers from the algoId */
    const uint32_t algoSpecifier  = (uint32_t) algoId & MCUXCLKEY_ALGO_ID_ALGO_MASK;
    const uint32_t usageSpecifier = (uint32_t) algoId & MCUXCLKEY_ALGO_ID_USAGE_MASK;

    /* Verify that the algoId is supported. If not, return FAULT_ATTACK */
    if (   (MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP_EPHEMERAL_CUSTOM != algoSpecifier)
        && (MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP_STATIC_CUSTOM    != algoSpecifier) )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateCustomKeyType, MCUXCLECC_STATUS_INVALID_PARAMS, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    if (   (MCUXCLKEY_ALGO_ID_PUBLIC_KEY  != usageSpecifier)
        && (MCUXCLKEY_ALGO_ID_PRIVATE_KEY != usageSpecifier)
        && (MCUXCLKEY_ALGO_ID_KEY_PAIR    != usageSpecifier) )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateCustomKeyType, MCUXCLECC_STATUS_INVALID_PARAMS, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Fill custom key type descriptor */
    customType->algoId = algoId;
    customType->size   = size;
    customType->info   = pCustomParams;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateCustomKeyType, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK);
}
