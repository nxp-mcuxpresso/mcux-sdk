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

/** @file  mcuxClEls_Aead.c
 *  @brief ELS implementation for Authenticated Encryption with Associated Data (AEAD).
 * This file implements the functions declared in mcuxClEls_Aead.h. */

#include <platform_specific_headers.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Aead_Init_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Aead_Init_Async(
    mcuxClEls_AeadOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pIV,
    size_t ivLength,
    uint8_t * pAeadCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Aead_Init_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Aead_Init_Async, (MCUXCLELS_AEAD_INTERN_KEY == options.bits.extkey && ELS_KS_CNT <= keyIdx) || ((MCUXCLELS_AEAD_EXTERN_KEY == options.bits.extkey && ((MCUXCLELS_CIPHER_KEY_SIZE_AES_128 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_192 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_256 != keyLength))))
            || (0u == ivLength) || (0u != ivLength % MCUXCLELS_AEAD_IV_BLOCK_SIZE));

    uint8_t * pStartIpCtxArea = pAeadCtx + MCUXCLELS_CIPHER_BLOCK_SIZE_AES;

    /* Set init mode */
    options.bits.acpmod = MCUXCLELS_AEAD_ACPMOD_INIT;
    options.bits.lastinit = MCUXCLELS_AEAD_LASTINIT_TRUE;

    options.bits.acpsie = MCUXCLELS_AEAD_STATE_IN_DISABLE;
#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    options.bits.acpsoe = MCUXCLELS_AEAD_STATE_OUT_ENABLE;
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_Init_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0(pIV, ivLength);
    mcuxClEls_setInput1_fixedSize(pStartIpCtxArea);
    mcuxClEls_setInput2(pKey, keyLength);
    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_AUTH_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_Init_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Aead_PartialInit_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Aead_PartialInit_Async(
    mcuxClEls_AeadOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pIV,
    size_t ivLength,
    uint8_t * pAeadCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Aead_PartialInit_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Aead_PartialInit_Async, (MCUXCLELS_AEAD_INTERN_KEY == options.bits.extkey && ELS_KS_CNT <= keyIdx) || ((MCUXCLELS_AEAD_EXTERN_KEY == options.bits.extkey && ((MCUXCLELS_CIPHER_KEY_SIZE_AES_128 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_192 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_256 != keyLength))))
            || (0u == ivLength) || (0u != ivLength % MCUXCLELS_AEAD_IV_BLOCK_SIZE));

    uint8_t * pStartIpCtxArea = pAeadCtx + MCUXCLELS_CIPHER_BLOCK_SIZE_AES;

    /* Set init mode */
    options.bits.acpmod = MCUXCLELS_AEAD_ACPMOD_INIT;

#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    options.bits.acpsoe = MCUXCLELS_AEAD_STATE_OUT_ENABLE;
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_PartialInit_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0(pIV, ivLength);
    mcuxClEls_setInput1_fixedSize(pStartIpCtxArea);
    mcuxClEls_setInput2(pKey, keyLength);
    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_AUTH_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_PartialInit_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Aead_UpdateAad_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Aead_UpdateAad_Async(
    mcuxClEls_AeadOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pAad,
    size_t aadLength,
    uint8_t * pAeadCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Aead_UpdateAad_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Aead_UpdateAad_Async, (MCUXCLELS_AEAD_INTERN_KEY == options.bits.extkey && ELS_KS_CNT <= keyIdx)
            || (MCUXCLELS_AEAD_EXTERN_KEY == options.bits.extkey && (MCUXCLELS_CIPHER_KEY_SIZE_AES_128 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_192 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_256 != keyLength))
            || (0U == aadLength) || (0u != aadLength % MCUXCLELS_AEAD_AAD_BLOCK_SIZE));

    uint8_t * pStartIpCtxArea = pAeadCtx + MCUXCLELS_CIPHER_BLOCK_SIZE_AES;

    options.bits.acpmod = MCUXCLELS_AEAD_ACPMOD_AADPROC;

#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    options.bits.acpsie = MCUXCLELS_AEAD_STATE_IN_ENABLE;
    options.bits.acpsoe = MCUXCLELS_AEAD_STATE_OUT_ENABLE;
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_UpdateAad_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput2(pKey, keyLength);
    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_setInput0(pAad, aadLength);
    mcuxClEls_setInput1_fixedSize(pStartIpCtxArea);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_AUTH_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_UpdateAad_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Aead_UpdateData_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Aead_UpdateData_Async(
    mcuxClEls_AeadOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pOutput,
    uint8_t * pAeadCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Aead_UpdateData_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Aead_UpdateData_Async, (0U == inputLength)  || (0u != inputLength % MCUXCLELS_CIPHER_BLOCK_SIZE_AES) || (MCUXCLELS_AEAD_INTERN_KEY == options.bits.extkey && ELS_KS_CNT <= keyIdx)
            || (MCUXCLELS_AEAD_EXTERN_KEY == options.bits.extkey && (MCUXCLELS_CIPHER_KEY_SIZE_AES_128 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_192 != keyLength && MCUXCLELS_CIPHER_KEY_SIZE_AES_256 != keyLength)));

    uint8_t * pStartIpCtxArea = pAeadCtx + MCUXCLELS_CIPHER_BLOCK_SIZE_AES;

    options.bits.acpmod = MCUXCLELS_AEAD_ACPMOD_MSGPROC;

#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    options.bits.acpsie = MCUXCLELS_AEAD_STATE_IN_ENABLE;
    options.bits.acpsoe = MCUXCLELS_AEAD_STATE_OUT_ENABLE;
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_UpdateData_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput2(pKey, keyLength);
    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_setInput0(pInput, inputLength);
    mcuxClEls_setInput1_fixedSize(pStartIpCtxArea);
    mcuxClEls_setOutput_fixedSize(pOutput);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_AUTH_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_UpdateData_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Aead_Finalize_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Aead_Finalize_Async(
    mcuxClEls_AeadOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    size_t aadLength,
    size_t dataLength,
    uint8_t * pTag,
    uint8_t * pAeadCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Aead_Finalize_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Aead_Finalize_Async, (MCUXCLELS_AEAD_INTERN_KEY == options.bits.extkey && ELS_KS_CNT <= keyIdx) || (MCUXCLELS_AEAD_EXTERN_KEY == options.bits.extkey && (16U != keyLength && 24U != keyLength && 32U != keyLength)));

    uint8_t * pStartIpCtxArea = pAeadCtx + MCUXCLELS_CIPHER_BLOCK_SIZE_AES;

#ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    options.bits.acpsie = MCUXCLELS_AEAD_STATE_IN_ENABLE;
#endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    /* Update the length of the AAD to store in the context */
    aadLength <<= 3;
    /* Update the length of the data to store in the context */
    dataLength <<= 3;
    /* Store both in the context */
    mcuxClMemory_StoreBigEndian32(&pAeadCtx[ 0u], (uint32_t) 0U);
    mcuxClMemory_StoreBigEndian32(&pAeadCtx[ 4u], aadLength );
    mcuxClMemory_StoreBigEndian32(&pAeadCtx[ 8u], (uint32_t) 0U);
    mcuxClMemory_StoreBigEndian32(&pAeadCtx[12u], dataLength);

    options.bits.acpmod = MCUXCLELS_AEAD_ACPMOD_FINAL;

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_Finalize_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput2(pKey, keyLength);
    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_setInput0_fixedSize(pAeadCtx);
    mcuxClEls_setInput1_fixedSize(pStartIpCtxArea);
    mcuxClEls_setOutput_fixedSize(pTag);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_AUTH_CIPHER, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Aead_Finalize_Async, MCUXCLELS_STATUS_OK_WAIT);
}
