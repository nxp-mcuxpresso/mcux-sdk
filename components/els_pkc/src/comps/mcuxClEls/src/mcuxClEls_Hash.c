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

#ifdef MCUXCL_FEATURE_ELS_SHA_DIRECT
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_ShaDirect_Enable)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_ShaDirect_Enable(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_ShaDirect_Enable);

    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_ShaDirect_Enable, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    MCUXCLELS_SET_CFG_FIELD(MCUXCLELS_SFR_CFG_SHA2_DIRECT, 1u);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_ShaDirect_Enable, MCUXCLELS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_ShaDirect_Disable)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_ShaDirect_Disable(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_ShaDirect_Disable);

    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_ShaDirect_Disable, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    MCUXCLELS_SET_CFG_FIELD(MCUXCLELS_SFR_CFG_SHA2_DIRECT, 0u);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_ShaDirect_Disable, MCUXCLELS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Hash_ShaDirect)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hash_ShaDirect(
    mcuxClEls_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest,
    mcuxClEls_TransferToRegisterFunction_t pCallback,
    void * pCallerData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Hash_ShaDirect);

    /* Length must not be zero and aligned with the block length */
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Hash_ShaDirect,
                               (0u == inputLength)
                               || ((MCUXCLELS_HASH_MODE_SHA_224 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_224)))
                               || ((MCUXCLELS_HASH_MODE_SHA_256 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_256)))
                               || ((MCUXCLELS_HASH_MODE_SHA_384 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_384)))
                               || ((MCUXCLELS_HASH_MODE_SHA_512 == options.bits.hashmd) && (0u != (inputLength % MCUXCLELS_HASH_BLOCK_SIZE_SHA_512)))
                               );

    size_t state_size = MCUXCLELS_HASH_STATE_SIZE_SHA_256;
    if (MCUXCLELS_HASH_MODE_SHA_512 == options.bits.hashmd)
    {
        state_size = MCUXCLELS_HASH_STATE_SIZE_SHA_512;
    }
    if (MCUXCLELS_HASH_MODE_SHA_384 == options.bits.hashmd)
    {
        state_size = MCUXCLELS_HASH_STATE_SIZE_SHA_384;
    }

    /* Check for SHA Direct mode */
    if (1u != MCUXCLELS_GET_CFG_FIELD(MCUXCLELS_SFR_CFG_SHA2_DIRECT))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_SW_INVALID_STATE);
    }

    /* Check if SHA Direct is busy */
    if (1u == MCUXCLELS_GET_SHA2_STATUS_FIELD(MCUXCLELS_SFR_SHA2_STATUS_SHA2_BUSY))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

#ifdef MCUXCL_FEATURE_ELS_SHA_DIRECT_MODE_FLAG
    /* Get hash mode */
    uint32_t hash_mode = options.bits.hashmd;
#endif

    if (1u == options.bits.hashini) {
        /* Set the SHA IV */
        uint32_t sha2_ctrl = 0u;
        sha2_ctrl = MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_START, 1u)
                    | MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_INIT, 1u)
#ifdef MCUXCL_FEATURE_ELS_SHA_DIRECT_MODE_FLAG
                    | MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_MODE, hash_mode)
#endif
                    | MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_BYTE_ORDER, 1u);

        MCUXCLELS_SFR_WRITE(ELS_SHA2_CTRL, sha2_ctrl);
    }

    if (1u == options.bits.hashld) {
        if(NULL == pDigest)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_SW_INVALID_PARAM);
        }
        /* Load previous state from pHash */
        uint32_t sha2_ctrl = 0u;
        sha2_ctrl = MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_LOAD, 1u)
#ifdef MCUXCL_FEATURE_ELS_SHA_DIRECT_MODE_FLAG
                    | MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_MODE, hash_mode)
#endif
                    | MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_BYTE_ORDER, 1u);

        MCUXCLELS_SFR_WRITE(ELS_SHA2_CTRL, sha2_ctrl);

        for (size_t i = 0; i < state_size; i += sizeof(uint32_t))
        {
            MCUXCLELS_SFR_WRITE(ELS_SHA2_DIN, mcuxClMemory_LoadLittleEndian32(&pDigest[i]));
        }

        /* LOAD flag clearing and START flag setting must be done separately */
        sha2_ctrl &= ~MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_LOAD, 1u);
        MCUXCLELS_SFR_WRITE(ELS_SHA2_CTRL, sha2_ctrl);
        sha2_ctrl |= MCUXCLELS_SFR_FIELD_FORMAT(ELS_SHA2_CTRL, SHA2_START, 1u);
        MCUXCLELS_SFR_WRITE(ELS_SHA2_CTRL, sha2_ctrl);
    }

    if (NULL != pCallback)
    {
        /* Use callback function to import data into ELS */
        if ( MCUXCLELS_STATUS_OK != pCallback(&(MCUXCLELS_SFR_READ(ELS_SHA2_DIN)), pInput, inputLength, pCallerData))
        {
            /* Callback function returned with an error */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_SW_FAULT);
        }
    }
    else
    {
        /* Use CPU copy to import data into ELS */
        for (size_t i = 0; i < inputLength; i += sizeof(uint32_t))
        {
            MCUXCLELS_SFR_WRITE(ELS_SHA2_DIN, mcuxClMemory_LoadLittleEndian32(&pInput[i]));
        }
    }

    /* Busy wait to */
    while (1u == MCUXCLELS_GET_SHA2_STATUS_FIELD(MCUXCLELS_SFR_SHA2_STATUS_SHA2_BUSY))
    {
        // Do nothing
    }

    /* Output the result */
    if (1u == options.bits.hashoe)
    {
        if(NULL == pDigest)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_SW_INVALID_PARAM);
        }
        /* Final hash value will be written to pDigest */
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 0U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT0));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 1U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT1));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 2U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT2));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 3U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT3));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 4U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT4));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 5U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT5));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 6U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT6));
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 7U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT7));
#ifdef MCUXCLELS_HASH_STATE_SIZE_SHA_512
        if(MCUXCLELS_HASH_STATE_SIZE_SHA_512 == state_size) /* only check for SHA-512, as STATE_SIZE_SHA_384 = STATE_SIZE_SHA_512 */
#else
        if(MCUXCLELS_HASH_STATE_SIZE_SHA_384 == state_size)
#endif /* MCUXCLELS_HASH_STATE_SIZE_SHA_512 */
        {
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 8U],  MCUXCLELS_SFR_READ(ELS_SHA2_DOUT8));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 9U],  MCUXCLELS_SFR_READ(ELS_SHA2_DOUT9));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 10U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT10));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 11U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT11));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 12U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT12));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 13U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT13));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 14U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT14));
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 15U], MCUXCLELS_SFR_READ(ELS_SHA2_DOUT15));
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hash_ShaDirect, MCUXCLELS_STATUS_OK);
}
#endif /* MCUXCL_FEATURE_ELS_SHA_DIRECT */
