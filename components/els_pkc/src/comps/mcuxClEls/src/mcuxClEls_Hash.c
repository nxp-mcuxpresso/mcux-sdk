/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

/** @file  mcuxClEls_Hash.c
 *  @brief ELS implementation for hashing.
 * This file implements the functions declared in mcuxClEls_Hash.h. */

#include <mcuxClEls_Hash.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Hash_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hash_Async(
    mcuxClEls_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Hash_Async);

    /* Length must not be zero and aligned with the block length */
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Hash_Async,
                               (0 == 1) // fixing MISRA warning
                               || ((MCUXCLELS_HASH_MODE_SHA_224 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_224)))
                               || ((MCUXCLELS_HASH_MODE_SHA_256 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_256)))
                               || ((MCUXCLELS_HASH_RTF_UPDATE_ENABLE == options.bits.rtfupd) && (MCUXCLELS_HASH_MODE_SHA_256 != options.bits.hashmd))
                               || ((MCUXCLELS_HASH_RTF_UPDATE_ENABLE != options.bits.rtfupd) && (MCUXCLELS_HASH_RTF_OUTPUT_ENABLE == options.bits.rtfoe))
                               || ((MCUXCLELS_HASH_OUTPUT_ENABLE != options.bits.hashoe) && (MCUXCLELS_HASH_RTF_OUTPUT_ENABLE == options.bits.rtfoe))
                               || ((MCUXCLELS_HASH_MODE_SHA_384 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_384)))
                               || ((MCUXCLELS_HASH_MODE_SHA_512 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_512)))
                               );

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0(pInput, inputLength);
    mcuxClEls_setInput1_fixedSize(pDigest);
    mcuxClEls_setOutput_fixedSize(pDigest);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_HASH, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_Async, MCUXCLELS_STATUS_OK_WAIT);

}

