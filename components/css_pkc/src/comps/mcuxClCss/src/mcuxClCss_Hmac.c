/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClCss_Hmac.c
 *  @brief CSSv2 implementation for HMAC support.
 * This file implements the functions declared in mcuxClCss_Hmac.h. */

#include <mcuxClCss_Hmac.h>
#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Hmac_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hmac_Async(
    mcuxClCss_HmacOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pPaddedKey,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Hmac_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Hmac_Async, (0U == inputLength) || (MCUXCLCSS_HMAC_EXTERNAL_KEY_DISABLE == options.bits.extkey && CSS_KS_CNT <= keyIdx));
    
    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hmac_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    if (0U == options.bits.extkey)
    {
        MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    }
    else
    {
        MCUXCLCSS_SETCSSINPUT2_FIXEDSIZE(pPaddedKey);
    }
    MCUXCLCSS_SETCSSINPUT0(pInput, inputLength);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_HMAC, options.word.value, CSS_CMD_BIG_ENDIAN);
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hmac_Async, MCUXCLCSS_STATUS_OK_WAIT);
}
