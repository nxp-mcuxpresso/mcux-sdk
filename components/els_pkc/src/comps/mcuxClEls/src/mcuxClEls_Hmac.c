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

/** @file  mcuxClEls_Hmac.c
 *  @brief ELS implementation for HMAC support.
 * This file implements the functions declared in mcuxClEls_Hmac.h. */

#include <platform_specific_headers.h>
#include <mcuxClEls_Hmac.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Hmac_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hmac_Async(
    mcuxClEls_HmacOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pPaddedKey,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Hmac_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Hmac_Async, (0U == inputLength) || (MCUXCLELS_HMAC_EXTERNAL_KEY_DISABLE == options.bits.extkey && ELS_KS_CNT <= keyIdx));
    
    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hmac_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    if (0U == options.bits.extkey)
    {
        mcuxClEls_setKeystoreIndex0(keyIdx);
    }
    else
    {
        mcuxClEls_setInput2_fixedSize(pPaddedKey);
    }
    mcuxClEls_setInput0(pInput, inputLength);
    mcuxClEls_setOutput_fixedSize(pOutput);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_HMAC, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hmac_Async, MCUXCLELS_STATUS_OK_WAIT);
}
