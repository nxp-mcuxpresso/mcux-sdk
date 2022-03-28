/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClCss_Hash.c
 *  @brief CSSv2 implementation for hashing.
 * This file implements the functions declared in mcuxClCss_Hash.h. */

#include <mcuxClCss_Hash.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <stdbool.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Hash_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hash_Async(
    mcuxClCss_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Hash_Async);

    /* Length must not be zero and aligned with the block length */
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Hash_Async,
                               false
                               || ((MCUXCLCSS_HASH_MODE_SHA_224 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_224)))
                               || ((MCUXCLCSS_HASH_MODE_SHA_256 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256)))
                               || ((MCUXCLCSS_HASH_RTF_UPDATE_ENABLE == options.bits.rtfupd) && (MCUXCLCSS_HASH_MODE_SHA_256 != options.bits.hashmd))
                               || ((MCUXCLCSS_HASH_RTF_UPDATE_ENABLE != options.bits.rtfupd) && (MCUXCLCSS_HASH_RTF_OUTPUT_ENABLE == options.bits.rtfoe))
                               || ((MCUXCLCSS_HASH_OUTPUT_ENABLE != options.bits.hashoe) && (MCUXCLCSS_HASH_RTF_OUTPUT_ENABLE == options.bits.rtfoe))
                               || ((MCUXCLCSS_HASH_MODE_SHA_384 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_384)))
                               || ((MCUXCLCSS_HASH_MODE_SHA_512 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_512)))
                               );

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    MCUXCLCSS_SETCSSINPUT0(pInput, inputLength);
    MCUXCLCSS_SETCSSINPUT1_FIXEDSIZE(pDigest);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pDigest);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_HASH, options.word.value, CSS_CMD_BIG_ENDIAN);
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_ShaDirect_Enable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ShaDirect_Enable(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_ShaDirect_Enable);

    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ShaDirect_Enable, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    IP_CSS->CSS_CFG_b.SHA2_DIRECT = 1;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ShaDirect_Enable, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_ShaDirect_Disable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ShaDirect_Disable(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_ShaDirect_Disable);

    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ShaDirect_Disable, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    IP_CSS->CSS_CFG_b.SHA2_DIRECT = 0;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ShaDirect_Disable, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Hash_ShaDirect)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hash_ShaDirect(
    mcuxClCss_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest,
    mcuxClCss_TransferToRegisterFunction_t pCallback,
    void * pCallerData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Hash_ShaDirect);

    /* Length must not be zero and aligned with the block length */
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Hash_ShaDirect,
                               false
                               || (0u == inputLength)
                               || ((MCUXCLCSS_HASH_MODE_SHA_224 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_224)))
                               || ((MCUXCLCSS_HASH_MODE_SHA_256 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256)))
                               || ((MCUXCLCSS_HASH_MODE_SHA_384 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_384)))
                               || ((MCUXCLCSS_HASH_MODE_SHA_512 == options.bits.hashmd) && (0u != (inputLength % MCUXCLCSS_HASH_BLOCK_SIZE_SHA_512)))
                               );

    size_t state_size = MCUXCLCSS_HASH_STATE_SIZE_SHA_256;
    if (MCUXCLCSS_HASH_MODE_SHA_512 == options.bits.hashmd)
    {
        state_size = MCUXCLCSS_HASH_STATE_SIZE_SHA_512;
    }
#ifdef MCUXCLCSS_HASH_MODE_SHA_384
    if (MCUXCLCSS_HASH_MODE_SHA_384 == options.bits.hashmd)
    {
        state_size = MCUXCLCSS_HASH_STATE_SIZE_SHA_512;
    }
#endif
    
    /* Check for SHA Direct mode */
    if (1u != IP_CSS->CSS_CFG_b.SHA2_DIRECT)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_ShaDirect, MCUXCLCSS_STATUS_SW_INVALID_STATE);
    }

    /* Check if SHA Direct is busy */
    if (1u == IP_CSS->CSS_SHA2_STATUS_b.SHA2_BUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_ShaDirect, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    /* Get hash mode */
    uint32_t hash_mode = options.bits.hashmd;

    if (1u == options.bits.hashini) {
        /* Set the SHA IV */
        IP_CSS->CSS_SHA2_CTRL = 0u;
        IP_CSS->CSS_SHA2_CTRL = ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_START_Pos) | ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_INIT_Pos)
         | (hash_mode << CSS_SHA2_CTRL_SHA2_MODE_Pos)
         | ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Pos);
    }

    if (1u == options.bits.hashld) {
        /* Load previous state from pHash */
        IP_CSS->CSS_SHA2_CTRL = 0u;
        IP_CSS->CSS_SHA2_CTRL = ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_LOAD_Pos)
         | (hash_mode << CSS_SHA2_CTRL_SHA2_MODE_Pos)
         | ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Pos);
        
        for (size_t i = 0; i < state_size; i += sizeof(uint32_t))
        {
            IP_CSS->CSS_SHA2_DIN = mcuxClMemory_LoadLittleEndian32(&pDigest[i]);
        }
        
        IP_CSS->CSS_SHA2_CTRL = 0u;
        IP_CSS->CSS_SHA2_CTRL = ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_START_Pos)
         | (hash_mode << CSS_SHA2_CTRL_SHA2_MODE_Pos)
         | ((uint32_t) 1u << CSS_SHA2_CTRL_SHA2_BYTE_ORDER_Pos);
    }

    if (NULL != pCallback)
    {
        /* Use callback function to import data into CSS */
        if ( MCUXCLCSS_STATUS_OK != pCallback(&(IP_CSS->CSS_SHA2_DIN), pInput, inputLength, pCallerData))
        {
            /* Callback function returned with an error */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_ShaDirect, MCUXCLCSS_STATUS_SW_FAULT);
        }
    }
    else
    {
        /* Use CPU copy to import data into CSS */
        for (size_t i = 0; i < inputLength; i += sizeof(uint32_t))
        {
            IP_CSS->CSS_SHA2_DIN = mcuxClMemory_LoadLittleEndian32(&pInput[i]);
        }
    }
    
    /* Busy wait to */
    while (1u == IP_CSS->CSS_SHA2_STATUS_b.SHA2_BUSY)
    {
        // Do nothing
    }
    
    /* Output the result */
    if (1u == options.bits.hashoe)
    {
        /* Final hash value will be written to pDigest */
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 0U], IP_CSS->CSS_SHA2_DOUT0);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 1U], IP_CSS->CSS_SHA2_DOUT1);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 2U], IP_CSS->CSS_SHA2_DOUT2);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 3U], IP_CSS->CSS_SHA2_DOUT3);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 4U], IP_CSS->CSS_SHA2_DOUT4);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 5U], IP_CSS->CSS_SHA2_DOUT5);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 6U], IP_CSS->CSS_SHA2_DOUT6);
        mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 7U], IP_CSS->CSS_SHA2_DOUT7);
#ifdef MCUXCLCSS_HASH_MODE_SHA_512
        if (MCUXCLCSS_HASH_STATE_SIZE_SHA_512 == state_size)
        {
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 8U],  IP_CSS->CSS_SHA2_DOUT8);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 9U],  IP_CSS->CSS_SHA2_DOUT9);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 10U], IP_CSS->CSS_SHA2_DOUT10);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 11U], IP_CSS->CSS_SHA2_DOUT11);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 12U], IP_CSS->CSS_SHA2_DOUT12);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 13U], IP_CSS->CSS_SHA2_DOUT13);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 14U], IP_CSS->CSS_SHA2_DOUT14);
            mcuxClMemory_StoreLittleEndian32(&pDigest[sizeof(uint32_t) * 15U], IP_CSS->CSS_SHA2_DOUT15);
        }
#endif
    }
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hash_ShaDirect, MCUXCLCSS_STATUS_OK);
}
