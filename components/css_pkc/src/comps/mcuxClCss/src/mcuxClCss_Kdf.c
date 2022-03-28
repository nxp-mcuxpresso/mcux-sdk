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

/** @file  mcuxClCss_Kdf.c
 *  @brief CSSv2 implementation for key derivation.
 * This file implements the functions declared in mcuxClCss_Kdf.h. */

#include <mcuxClCss_Kdf.h>
#include <mcuxClCss_Hash.h>
#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Ckdf_Sp800108_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Ckdf_Sp800108_Async(
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx,
    mcuxClCss_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Ckdf_Sp800108_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Ckdf_Sp800108_Async, (CSS_KS_CNT <= derivationKeyIdx) || (CSS_KS_CNT <= targetKeyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Ckdf_Sp800108_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClCss_CkdfOption_t option = {0};
    option.bits.ckdf_algo = MCUXCLCSS_CKDF_ALGO_SP800108 ;

    MCUXCLCSS_SETKEYSTOREINDEX0(derivationKeyIdx);
    MCUXCLCSS_SETKEYSTOREINDEX1(targetKeyIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(targetKeyProperties);
    MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pDerivationData);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_CKDF, option.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Ckdf_Sp800108_Async, MCUXCLCSS_STATUS_OK_WAIT);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Hkdf_Rfc5869_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hkdf_Rfc5869_Async(
    mcuxClCss_HkdfOption_t options,
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx,
    mcuxClCss_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Hkdf_Rfc5869_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Hkdf_Rfc5869_Async, (CSS_KS_CNT <= derivationKeyIdx) || (CSS_KS_CNT <= targetKeyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hkdf_Rfc5869_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    options.bits.hkdf_algo = MCUXCLCSS_HKDF_ALGO_RFC5869;

    MCUXCLCSS_SETKEYSTOREINDEX0(derivationKeyIdx);
    MCUXCLCSS_SETKEYSTOREINDEX1(targetKeyIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(targetKeyProperties);
    MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pDerivationData);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_HKDF, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hkdf_Rfc5869_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Hkdf_Sp80056c_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hkdf_Sp80056c_Async(
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    uint8_t * pTagetKey,
    uint8_t const * pDerivationData,
    size_t derivationDataLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Hkdf_Sp80056c_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_Hkdf_Rfc5869_Async, (CSS_KS_CNT <= derivationKeyIdx) );

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hkdf_Rfc5869_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClCss_HkdfOption_t options = {0};
    options.bits.hkdf_algo = MCUXCLCSS_HKDF_ALGO_SP80056C;

    MCUXCLCSS_SETKEYSTOREINDEX0(derivationKeyIdx);
    MCUXCLCSS_SETCSSINPUT0(pDerivationData, derivationDataLength);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pTagetKey);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_HKDF, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Hkdf_Sp80056c_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClCss_KeyProp_t keyProperties,
    mcuxClCss_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async, (CSS_KS_CNT <= keyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClCss_TlsOption_t options = {0};
    options.bits.mode = MCUXCLCSS_TLS_INIT;

    MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(keyProperties);
    MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pDerivationData);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_TLS, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClCss_KeyProp_t keyProperties,
    mcuxClCss_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async, ((CSS_KS_CNT - 4U) <= keyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClCss_TlsOption_t options = {0};
    options.bits.mode = MCUXCLCSS_TLS_FINALIZE;

    MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(keyProperties);
    MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pDerivationData);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_TLS, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async, MCUXCLCSS_STATUS_OK_WAIT);
}
