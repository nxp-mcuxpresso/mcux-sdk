/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

#include "common.h"

#include <mcuxClMemory_Clear.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClAes.h>
#include <mcuxClCipher.h>
#include <mcuxClCipherModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClCipherModes_Internal_Types_Els.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_abort(
    psa_cipher_operation_t *operation )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&pClnsCipherData->keydesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Clear cipher ctx */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_clear ((uint8_t*)pClnsCipherData,
                                                                       MCUXCLPSADRIVER_CLNSDATA_CIPHER_SIZE,
                                                                       MCUXCLPSADRIVER_CLNSDATA_CIPHER_SIZE));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear) != token)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    return PSA_SUCCESS;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_internal(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* For algorithms supported by CLNS, add implementation. */
    if (mcuxClPsaDriver_psa_driver_wrapper_cipher_isAlgSupported(attributes))
    {

        if (!mcuxClPsaDriver_psa_driver_wrapper_cipher_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Variable for the AES mode. Set this according to the key policy. */
        const mcuxClCipher_ModeDescriptor_t *mode = NULL;
        uint32_t iv_required = mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectDec(alg, &mode);
        if (NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        /* check for invalid input based upon following rule
           inLength needs to be a multiple of the granularity, if this is not the case, return an error. */
        const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = mode->pAlgorithm;
        if((input_length % pAlgo->granularity) != 0u)
        {
            return (PSA_ERROR_INVALID_ARGUMENT);
        }

        size_t expected_output_size;
        expected_output_size = output_size == 0u ? output_size : input_length;

        /* Check for small output buffer size*/
        if( output_size < expected_output_size )
        {
            return( PSA_ERROR_BUFFER_TOO_SMALL );
        }

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];

        /* Create session */
        mcuxClSession_Descriptor_t session;

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        // If there is no need for IV iv_length will be set to 0 and ciphertext will point to begining of input buffer
        // In other case first 16B of input buffer will be used as IV and ciphertext will point to input buffer + iv_length
        uint32_t iv_length = (1u == iv_required) ? MCUXCLAES_BLOCK_SIZE : 0u;
        /* Initializing the output length with zero */
        *output_length = 0;

        /* Do the decryption */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_crypt(&session, pKey, mode,
                                                                         input, // IV buffer (when needed by mode) is located at the begining of input buffer
                                                                         iv_length, input + iv_length, input_length - iv_length, output, (uint32_t *)output_length));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_crypt) != token) || (MCUXCLCIPHER_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        /* Destroy the session */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Return with success */
        return PSA_SUCCESS;
    }
    else{
        return PSA_ERROR_NOT_SUPPORTED;
    }
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt(
    const psa_key_attributes_t * attributes,
    const uint8_t * key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    // The driver handles multiple storage locations, call it first then default to builtin driver
    /* Create the key */
    mcuxClKey_Descriptor_t key = {0};
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_internal(&key,
                                                                       alg,
                                                                       input,
                                                                       input_length,
                                                                       output,
                                                                       output_size,
                                                                       output_length);

    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_setup_internal(
    psa_cipher_operation_t *operation,
    mcuxClKey_Descriptor_t *keyDesc,
    psa_algorithm_t alg)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(keyDesc);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* For algorithms supported by CLNS, add implementation. */
    if (mcuxClPsaDriver_psa_driver_wrapper_cipher_isAlgSupported(attributes))
    {
        if (!mcuxClPsaDriver_psa_driver_wrapper_cipher_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Variable for the AES mode. Set this according to the key policy. */
        const mcuxClCipher_ModeDescriptor_t *mode = NULL;
        operation->iv_required = mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectDec(alg, &mode);
        if (NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        operation->iv_set = 0u;
        operation->default_iv_length = (1u == operation->iv_required) ? MCUXCLAES_BLOCK_SIZE : 0u;

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];

        /* Create session */
        mcuxClSession_Descriptor_t session;

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        uint8_t tempIV[16] = {0u};

        /* Do the encryption */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_init(&session, (mcuxClCipher_Context_t *) &pClnsCipherData->ctx, keyDesc, mode, tempIV, operation->default_iv_length));
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_init) != token) || (MCUXCLCIPHER_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        /* Destroy the session */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        operation->id = psa_driver_wrapper_get_clns_operation_id();

        /* Return with success */
        return PSA_SUCCESS;
    }
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    // The driver handles multiple storage locations, call it first then default to builtin driver
    /* Create the key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    mcuxClKey_Descriptor_t *keyDesc = &pClnsCipherData->keydesc;
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, keyDesc);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_setup_internal(operation,
                                                         keyDesc,
                                                         alg);
														 
    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(keyDesc);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_internal(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *iv,
    size_t iv_length,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* For algorithms supported by CLNS, add implementation. */
    if (mcuxClPsaDriver_psa_driver_wrapper_cipher_isAlgSupported(attributes))
    {
        if (!mcuxClPsaDriver_psa_driver_wrapper_cipher_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Variable for the AES mode. Set this according to the key policy. */
        const mcuxClCipher_ModeDescriptor_t *mode = NULL;
        (void)mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectEnc(alg, &mode);
        if (NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        /* check for invalid input based upon following rule
           inLength needs to be a multiple of the granularity, if this is not the case, return an error. */
        const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = mode->pAlgorithm;
        if((input_length % pAlgo->granularity) != 0u)
        {
            return (PSA_ERROR_INVALID_ARGUMENT);
        }

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];
        /* Initializing the output length with zero */
        *output_length = 0u;

        /* Create session */
        mcuxClSession_Descriptor_t session;

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Do the encryption */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_crypt(&session, pKey, mode, iv, iv_length, input, input_length, output, (uint32_t *)output_length));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_crypt) != token) || (MCUXCLCIPHER_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Destroy the session */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        /* Return with success */
        return PSA_SUCCESS;
    }
    else{
        return PSA_ERROR_NOT_SUPPORTED;
    }
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *iv,
    size_t iv_length,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    // The driver handles multiple storage locations, call it first then default to builtin driver
    /* Create the key */
    mcuxClKey_Descriptor_t key = {0};
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_internal( &key,
					                                                    alg,
					                                                    iv,
					                                                    iv_length,
					                                                    input,
					                                                    input_length,
					                                                    output,
					                                                    output_size,
					                                                    output_length);

    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_setup_internal(
    psa_cipher_operation_t *operation,
    mcuxClKey_Descriptor_t *keyDesc,
    psa_algorithm_t alg)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(keyDesc);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* For algorithms supported by CLNS, add implementation. */
    if (mcuxClPsaDriver_psa_driver_wrapper_cipher_isAlgSupported(attributes))
    {

        if (!mcuxClPsaDriver_psa_driver_wrapper_cipher_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Variable for the AES mode. Set this according to the key policy. */
        const mcuxClCipher_ModeDescriptor_t *mode = NULL;
        operation->iv_required = mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectEnc(alg, &mode);
        if (NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        uint8_t tempIV[16] = {0u};
        operation->default_iv_length = (1u == operation->iv_required) ? MCUXCLAES_BLOCK_SIZE : 0u;
        operation->iv_set = 0u;

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];

        /* Create session */
        mcuxClSession_Descriptor_t session;

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Do the encryption */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_init(&session, (mcuxClCipher_Context_t *) &pClnsCipherData->ctx, keyDesc, mode, tempIV, operation->default_iv_length));
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_init) != token) || (MCUXCLCIPHER_STATUS_OK != result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Destroy the session */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        operation->id = psa_driver_wrapper_get_clns_operation_id();

        /* Return with success */
        return PSA_SUCCESS;
    }
    else{
        return PSA_ERROR_NOT_SUPPORTED;
    }
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t * attributes,
    const uint8_t * key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    // The driver handles multiple storage locations, call it first then default to builtin driver
    /* Create the key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES();
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY();
    mcuxClKey_Descriptor_t *keyDesc = &pClnsCipherData->keydesc;
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, keyDesc);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_setup_internal(operation,
					                                                         keyDesc,
					                                                         alg);

    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(keyDesc);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_finish(
    psa_cipher_operation_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Check if IV is required and set*/
    if ((1u == operation->iv_required) && (0u == operation->iv_set))
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    /* check for invalid input based upon following rule
       inLength needs to be a multiple of the granularity, if this is not the case, return an error. */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    mcuxClCipherModes_Context_Aes_Els_t  *const pContext = &pClnsCipherData->ctx;
    const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = pContext->common.pMode->pAlgorithm;
    if((pContext->common.blockBufferUsed % pAlgo->granularity) != 0u)
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];

    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /*not used*/
    (void)output_size;
    *output_length = 0u;

    mcuxClKey_Descriptor_t *keyDesc = &pClnsCipherData->keydesc;
    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    *output_length = 0u;

    /* Do the encryption */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_finish(&session, (mcuxClCipher_Context_t *) &pClnsCipherData->ctx, output, (uint32_t *)output_length));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_finish) != token) || (MCUXCLCIPHER_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Return with success */
    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_set_iv(
    psa_cipher_operation_t *operation,
    const uint8_t *iv,
    size_t iv_length )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    operation->iv_set = 1u;

    /* check if input iv_length is less than default iv length, then the argument is invalid */
    if (operation->default_iv_length > iv_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t *pIvState = (uint8_t *) pClnsCipherData->ctx.ivState;
    for (uint32_t i = 0u; i < iv_length; ++i)
    {
        pIvState[i] = iv[i];
    }

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_update(
    psa_cipher_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    size_t expected_output_size;

    expected_output_size = output_size == 0u ? output_size : input_length;

    /* Check if IV is required and set*/
    if ((1u == operation->iv_required) && (0u == operation->iv_set))
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    /* Potential check for small output buffer size*/
    if( output_size < expected_output_size )
    {
        return( PSA_ERROR_BUFFER_TOO_SMALL );
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE_IN_WORDS];

    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session, cpuWorkarea, MCUXCLCIPHER_MAX_AES_CPU_WA_BUFFER_SIZE, NULL, 0u));

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* not used */
    (void)output_size;
    *output_length = 0u;

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Cipher_t * pClnsCipherData = (mcuxClPsaDriver_ClnsData_Cipher_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    mcuxClKey_Descriptor_t *keyDesc = &pClnsCipherData->keydesc;
    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    *output_length = 0u;

    /* Do the encryption */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCipher_process(&session, (mcuxClCipher_Context_t *) &pClnsCipherData->ctx, input, input_length, output, (uint32_t *) output_length));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipher_process) != token) || (MCUXCLCIPHER_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Return with success */
    return PSA_SUCCESS;
}
