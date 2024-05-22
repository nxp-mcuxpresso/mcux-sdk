/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClEls_Cipher.c
 *  @brief ELS implementation for symmetric ciphers.
 * This file implements the functions declared in mcuxClEls_Cipher.h. */

#include <platform_specific_headers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Cipher_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Cipher_Async(
    mcuxClEls_CipherOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pIV,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Cipher_Async);

    // ignored misra violation -> false positive
    // misra_c_2012_rule_11_9_violation: Literal 0 shall not be used as null pointer constant.

#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    #define TMP_NO_INTERNAL_STATE_FLAGS (MCUXCLELS_CIPHER_STATE_IN_ENABLE == options.bits.cphsie)
#else
    #define TMP_NO_INTERNAL_STATE_FLAGS (false)
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Cipher_Async,
                                          (0U == inputLength) 
                                          || (0U != (inputLength % MCUXCLELS_CIPHER_BLOCK_SIZE_AES))
                                          || ((MCUXCLELS_CIPHER_INTERNAL_KEY == options.bits.extkey) && (ELS_KS_CNT <= keyIdx))
                                          || ((MCUXCLELS_CIPHER_EXTERNAL_KEY == options.bits.extkey) && ((MCUXCLELS_CIPHER_KEY_SIZE_AES_128 != keyLength) && (MCUXCLELS_CIPHER_KEY_SIZE_AES_192 != keyLength) && (MCUXCLELS_CIPHER_KEY_SIZE_AES_256 != keyLength)))
                                          || (MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CTR < options.bits.cphmde)
            /* ECB doesn't support importing or exporting an IV */
                                          || ((MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB == options.bits.cphmde) && ((MCUXCLELS_CIPHER_STATE_OUT_ENABLE == options.bits.cphsoe) || (TMP_NO_INTERNAL_STATE_FLAGS == true))));
    
#undef TMP_NO_INTERNAL_STATE_FLAGS

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Cipher_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    mcuxClEls_setInput0(pInput, inputLength);
    if (0U == options.bits.extkey)
    {
        mcuxClEls_setKeystoreIndex0(keyIdx);
    }
    else
    {
        mcuxClEls_setInput2(pKey, keyLength);
    }
    
    mcuxClEls_setInput1_fixedSize(pIV);
    mcuxClEls_setOutput_fixedSize(pOutput);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Cipher_Async, MCUXCLELS_STATUS_OK_WAIT);
}
