/*
 * Copyright 2022-2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include <mcuxClPsaDriver.h>
#include <mcuxClPsaDriver_Oracle_Macros.h>
#include <mcuxClPsaDriver_Oracle_ElsUtils.h>

static bool mcuxClPsaDriver_Oracle_ElsUtils_IsActiveKeyslot(mcuxClEls_KeyIndex_t keyIdx)
{
    mcuxClEls_KeyProp_t key_properties;
    key_properties.word.value = ((const volatile uint32_t *)(&ELS->ELS_KS0))[keyIdx];
    return (bool) key_properties.bits.kactv;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties(mcuxClEls_KeyIndex_t keyIdx,
                                                              mcuxClEls_KeyProp_t *keyProperties)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetKeyProperties(keyIdx, keyProperties));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_GetKeyProperties failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}

bool mcuxClPsaDriver_Oracle_ElsUtils_IsFreeKeySlot(mcuxClEls_KeyIndex_t keyIdx, uint32_t requiredKeyslots)
{
    for (uint32_t i = 0; i < requiredKeyslots; i++)
    {
        if (mcuxClPsaDriver_Oracle_ElsUtils_IsActiveKeyslot(keyIdx + i))
        {
            return false;
        }
    }
    return true;
}

mcuxClEls_KeyIndex_t mcuxClPsaDriver_Oracle_ElsUtils_GetFreeKeySlot(uint32_t requiredKeyslots)
{
    for (mcuxClEls_KeyIndex_t keyIdx = 0; keyIdx <= (MCUXCLELS_KEY_SLOTS - requiredKeyslots); keyIdx++)
    {
        bool is_valid_keyslot = true;
        for (uint32_t i = 0; i < requiredKeyslots; i++)
        {
            if (mcuxClPsaDriver_Oracle_ElsUtils_IsActiveKeyslot(keyIdx + i))
            {
                is_valid_keyslot = false;
                break;
            }
        }

        if (is_valid_keyslot)
        {
            return keyIdx;
        }
    }
    return MCUXCLELS_KEY_SLOTS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Ckdf(mcuxClEls_KeyIndex_t derivationKeyIdx,
                                                  mcuxClEls_KeyIndex_t targetKeyIdx,
                                                  mcuxClEls_KeyProp_t targetKeyProperties,
                                                  uint8_t const *pDerivationData)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClEls_Ckdf_Sp800108_Async(derivationKeyIdx, targetKeyIdx, targetKeyProperties, pDerivationData));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Ckdf_Sp800108_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("Css_Ckdf_Sp800108_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("Css_Ckdf_Sp800108_Asyn WaitForOperation failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(mcuxClEls_EccKeyGenOption_t options,
                                                       mcuxClEls_KeyIndex_t privateKeyIdx,
                                                       mcuxClEls_KeyProp_t generatedKeyProperties,
                                                       uint8_t *pPublicKey)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_EccKeyGen_Async(options, (mcuxClEls_KeyIndex_t)0, privateKeyIdx,
                                                               generatedKeyProperties, NULL, pPublicKey));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccKeyGen_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("Css_EccKeyGen_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("Css_EccKeyGen_Async WaitForOperation failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(mcuxClEls_KeyIndex_t targetKeyIdx)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(targetKeyIdx));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("Css_KeyDelete_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("Css_KeyDelete_Async WaitForOperation failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_KeyIn(const uint8_t *keyin_command_blob,
                                                   size_t keyin_command_blob_size,
                                                   mcuxClEls_KeyIndex_t unwrapKeyIdx,
                                                   mcuxClEls_KeyIndex_t targetKeyIdx)
{
    mcuxClEls_KeyImportOption_t options;
    options.bits.kfmt = MCUXCLELS_KEYIMPORT_KFMT_RFC3394;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClEls_KeyImport_Async(options, keyin_command_blob, keyin_command_blob_size, unwrapKeyIdx, targetKeyIdx));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyImport_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("mcuxClEls_KeyImport_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_KeyImport_Async WaitForOperation failed: 0x%x", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Cmac(uint8_t *data,
                                                  size_t data_size,
                                                  mcuxClEls_KeyIndex_t authKeyIdx,
                                                  uint8_t *pCmac)
{
    mcuxClEls_CmacOption_t options;
    options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_ENABLE;
    options.bits.finalize   = MCUXCLELS_CMAC_FINALIZE_ENABLE;
    options.bits.extkey     = MCUXCLELS_CMAC_EXTERNAL_KEY_DISABLE;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_Cmac_Async(options, authKeyIdx, NULL, 0, data, data_size, pCmac));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("mcuxClEls_Cmac_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_Cmac_Async LimitedWaitForOperation failed: 0x%x", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Cipher_Decrypt(
    const uint8_t *data, size_t data_size, mcuxClEls_KeyIndex_t tfmKekKeyIdx, const uint8_t *iv, uint8_t *pOut)
{
    mcuxClEls_CipherOption_t cipher_options = {0U};
    cipher_options.bits.cphmde              = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC;
    cipher_options.bits.dcrpt               = MCUXCLELS_CIPHER_DECRYPT;

    // We use CSS in a mode where it will not output its state, so casting away
    // the const is safe here.
    uint8_t *state = (uint8_t *)iv;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClEls_Cipher_Async(cipher_options, tfmKekKeyIdx, NULL, (size_t)0u, data, data_size, state, pOut));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("mcuxClEls_Cipher_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_Cipher_Async LimitedWaitForOperation failed: 0x%x", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

psa_status_t mcxClPsaDriver_Oracle_ElsUtils_Key_Export(
    mcuxClEls_KeyIndex_t wrappingKeyIdx,
    mcuxClEls_KeyIndex_t exportKeyIdx,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClEls_KeyExport_Async(wrappingKeyIdx, exportKeyIdx, pOutput));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyExport_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("mcuxClEls_KeyExport_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_KeyExport_Async LimitedWaitForOperation failed: 0x%x", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_EccKeyAgreement(
                                                       mcuxClEls_KeyIndex_t privateKeyIdx,
                                                       uint8_t *pPublicKey,
                                                       mcuxClEls_KeyIndex_t sharedSecretIdx,
                                                       mcuxClEls_KeyProp_t sharedSecretProperties)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_EccKeyExchange_Async(privateKeyIdx, pPublicKey, sharedSecretIdx, sharedSecretProperties));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccKeyExchange_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        PRINTF("mcuxClEls_EccKeyExchange_Async failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        PRINTF("mcuxClEls_EccKeyExchange_Async WaitForOperation failed: 0x%x\r\n", result);
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}
