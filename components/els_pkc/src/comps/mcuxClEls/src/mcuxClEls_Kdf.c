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

/** @file  mcuxClEls_Kdf.c
 *  @brief ELS implementation for key derivation.
 * This file implements the functions declared in mcuxClEls_Kdf.h. */

#include <platform_specific_headers.h>
#include <mcuxClEls_Kdf.h>
#include <mcuxClEls_Hash.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Ckdf_Sp800108_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Ckdf_Sp800108_Async(
    mcuxClEls_KeyIndex_t derivationKeyIdx,
    mcuxClEls_KeyIndex_t targetKeyIdx,
    mcuxClEls_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Ckdf_Sp800108_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Ckdf_Sp800108_Async, (ELS_KS_CNT <= derivationKeyIdx) || (ELS_KS_CNT <= targetKeyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Ckdf_Sp800108_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_CkdfOption_t option = {0};
    option.bits.ckdf_algo = MCUXCLELS_CKDF_ALGO_SP800108;

    mcuxClEls_setKeystoreIndex0(derivationKeyIdx);
    mcuxClEls_setKeystoreIndex1(targetKeyIdx);
    mcuxClEls_setRequestedKeyProperties(targetKeyProperties.word.value);
    mcuxClEls_setInput0_fixedSize(pDerivationData);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_CKDF, option.word.value, ELS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Ckdf_Sp800108_Async, MCUXCLELS_STATUS_OK_WAIT);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Hkdf_Rfc5869_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hkdf_Rfc5869_Async(
    mcuxClEls_HkdfOption_t options,
    mcuxClEls_KeyIndex_t derivationKeyIdx,
    mcuxClEls_KeyIndex_t targetKeyIdx,
    mcuxClEls_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Hkdf_Rfc5869_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Hkdf_Rfc5869_Async, (ELS_KS_CNT <= derivationKeyIdx) || (ELS_KS_CNT <= targetKeyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hkdf_Rfc5869_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    options.bits.hkdf_algo = MCUXCLELS_HKDF_ALGO_RFC5869;

    mcuxClEls_setKeystoreIndex0(derivationKeyIdx);
    mcuxClEls_setKeystoreIndex1(targetKeyIdx);
    mcuxClEls_setRequestedKeyProperties(targetKeyProperties.word.value);
    mcuxClEls_setInput0_fixedSize(pDerivationData);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_HKDF, options.word.value, ELS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hkdf_Rfc5869_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Hkdf_Sp80056c_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hkdf_Sp80056c_Async(
    mcuxClEls_KeyIndex_t derivationKeyIdx,
    uint8_t * pTagetKey,
    uint8_t const * pDerivationData,
    size_t derivationDataLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Hkdf_Sp80056c_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Hkdf_Sp80056c_Async, (ELS_KS_CNT <= derivationKeyIdx) );

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hkdf_Sp80056c_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_HkdfOption_t options = {0};
    options.bits.hkdf_algo = MCUXCLELS_HKDF_ALGO_SP80056C;

    mcuxClEls_setKeystoreIndex0(derivationKeyIdx);
    mcuxClEls_setInput0(pDerivationData, derivationDataLength);
    mcuxClEls_setOutput_fixedSize(pTagetKey);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_HKDF, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Hkdf_Sp80056c_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClEls_KeyProp_t keyProperties,
    mcuxClEls_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async, (ELS_KS_CNT <= keyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_TlsOption_t options = {0};
    options.bits.mode = MCUXCLELS_TLS_INIT;

    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_setRequestedKeyProperties(keyProperties.word.value);
    mcuxClEls_setInput0_fixedSize(pDerivationData);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_TLS, options.word.value, ELS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClEls_KeyProp_t keyProperties,
    mcuxClEls_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async, ((ELS_KS_CNT - 4U) <= keyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_TlsOption_t options = {0};
    options.bits.mode = MCUXCLELS_TLS_FINALIZE;

    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_setRequestedKeyProperties(keyProperties.word.value);
    mcuxClEls_setInput0_fixedSize(pDerivationData);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_TLS, options.word.value, ELS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async, MCUXCLELS_STATUS_OK_WAIT);
}
