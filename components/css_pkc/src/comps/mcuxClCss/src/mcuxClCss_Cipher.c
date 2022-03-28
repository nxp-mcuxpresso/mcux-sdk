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

/** @file  impl/mcuxClCss_Cipher.c
 *  @brief CSSv2 implementation for symmetric ciphers.
 * This file implements the functions declared in mcuxClCss_Cipher.h. */

#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Cipher_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Cipher_Async(mcuxClCss_CipherOption_t options,
                                                                  mcuxClCss_KeyIndex_t keyIdx,
                                                                  uint8_t const *pKey,
                                                                  size_t keyLength,
                                                                  uint8_t const *pInput,
                                                                  size_t inputLength,
                                                                  uint8_t *pIV,
                                                                  uint8_t *pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Cipher_Async);

    // ignored misra violation -> false positive
    // misra_c_2012_rule_11_9_violation: Literal 0 shall not be used as null pointer constant.
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(
        mcuxClCss_Cipher_Async,
        (0U == inputLength) || (0U != (inputLength % MCUXCLCSS_CIPHER_BLOCK_SIZE_AES)) ||
            (MCUXCLCSS_CIPHER_INTERNAL_KEY == options.bits.extkey && CSS_KS_CNT <= keyIdx) ||
            ((MCUXCLCSS_CIPHER_EXTERNAL_KEY == options.bits.extkey) &&
             ((MCUXCLCSS_CIPHER_KEY_SIZE_AES_128 != keyLength) && (MCUXCLCSS_CIPHER_KEY_SIZE_AES_192 != keyLength) &&
              (MCUXCLCSS_CIPHER_KEY_SIZE_AES_256 != keyLength))) ||
            (MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_CTR < options.bits.cphmde)
            /* ECB doesn't support importing or exporting an IV */
            || ((MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_ECB == options.bits.cphmde) &&
                ((MCUXCLCSS_CIPHER_STATE_IN_ENABLE == options.bits.cphsie) ||
                 (MCUXCLCSS_CIPHER_STATE_OUT_ENABLE == options.bits.cphsoe))));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Cipher_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    MCUXCLCSS_SETCSSINPUT0(pInput, inputLength);
    if (0U == options.bits.extkey)
    {
        MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    }
    else
    {
        MCUXCLCSS_SETCSSINPUT2(pKey, keyLength);
    }

    MCUXCLCSS_SETCSSINPUT1_FIXEDSIZE(pIV);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_CIPHER, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Cipher_Async, MCUXCLCSS_STATUS_OK_WAIT);
}
