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

#include <mcuxCsslAnalysis.h>
#include <mcuxClMemory_Clear.h>
#include <mcuxClAead.h>
#include <mcuxClAeadModes.h>
#include <mcuxClAes.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>


static inline bool mcuxClPsaDriver_psa_driver_wrapper_aead_algNeedsLengthsSet(const psa_algorithm_t alg)
{
    return ((PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM)
                || (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM_STAR_NO_TAG));
}


static inline psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(const psa_algorithm_t alg)
{
    uint32_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    /* Recover default algorithm (could be CCM with changed tag size) */
    const psa_algorithm_t algDefault = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);

    psa_status_t status = PSA_SUCCESS;

    switch(algDefault)
    {
        case PSA_ALG_CCM:
            /* Add checks for valid CCM tag length, otherwise return error*/
            if( (tag_length < 4u) || (tag_length > 16u) || (tag_length % 2u != 0u) )
            {
                status = ( PSA_ERROR_INVALID_ARGUMENT );
            }
            break;

        case PSA_ALG_GCM:
            /* Add checks for valid GCM tag length, otherwise return error*/
            if( (4u != tag_length) && (8u != tag_length) && ((tag_length < 12u) || (tag_length > 16u)) )
            {
                status = ( PSA_ERROR_INVALID_ARGUMENT );
            }
            break;

        default:
            status = ( PSA_ERROR_INVALID_ARGUMENT );
            break;
    }

    return( status );
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_abort(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
   psa_aead_operation_t *operation)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&pClnsAeadData->keydesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Clear the clns data */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenClear, mcuxClMemory_clear(
                                                        (uint8_t *) pClnsAeadData,
                                                        MCUXCLPSADRIVER_CLNSDATA_AEAD_SIZE,
                                                        MCUXCLPSADRIVER_CLNSDATA_AEAD_SIZE));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear) != tokenClear)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    /* Reset operation */
    *operation = (psa_aead_operation_t) PSA_AEAD_OPERATION_INIT;

    /* Return with success */
    return PSA_SUCCESS;
}

/*
 * Authenticated decryption compare tags function
 */
static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_compare_tags(const unsigned char *tag1, const unsigned char *tag2, size_t tag_len)
{
    unsigned char diff = 0u;

    /* Check tag in "constant-time" */
    for(size_t i = 0u; i < tag_len; i++ )
    {
        diff |= tag1[i] ^ tag2[i];
    }

    if( diff != 0u )
    {
        return( PSA_ERROR_INVALID_SIGNATURE );
    }
    return( PSA_SUCCESS );
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt_internal(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length )
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* For algorithms supported by CLNS, add implementation. */
    if(mcuxClPsaDriver_psa_driver_wrapper_aead_isAlgSupported(attributes))
    {
        /* Validate given sizes */
        uint32_t needed_output_size = PSA_AEAD_DECRYPT_OUTPUT_SIZE(attributes->core.type, alg, ciphertext_length);
        if(plaintext_size < needed_output_size)
        {
            return PSA_ERROR_BUFFER_TOO_SMALL;
        }

        /* Validate given key */
        if((PSA_KEY_USAGE_DECRYPT != (PSA_KEY_USAGE_DECRYPT & attributes->core.policy.usage))
            || !mcuxClPsaDriver_psa_driver_wrapper_aead_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Get the correct AEAD mode based on the given algorithm. */
        mcuxClAead_Mode_t mode = mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeDec(alg);
        if(NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(alg))
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

        /* Create session */
        mcuxClSession_Descriptor_t session;
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                        mcuxClSession_init(&session,
                                                          cpuWorkarea,
                                                          MCUXCLAEAD_WA_SIZE_MAX,
                                                          NULL,
                                                          0u));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* get the tag in local variable */
        unsigned char tag_for_comparison[16];
        psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

        /* Get the correct tag length based on the given algorithm. */
        uint32_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

        *plaintext_length = 0u;

        /* Do the decryption */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultCrypt, tokenCrypt,
                                        mcuxClAead_crypt(&session,
                                                        pKey,
                                                        mode,
                                                        nonce, nonce_length,
                                                        ciphertext, ciphertext_length - tag_length,
                                                        additional_data, additional_data_length,
                                                        plaintext, (uint32_t *)plaintext_length,
                                                        tag_for_comparison, tag_length));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_crypt) != tokenCrypt) || (MCUXCLAEAD_STATUS_OK != resultCrypt))
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

        /* perform validation of correct ciphered text */
        status = mcuxClPsaDriver_psa_driver_wrapper_aead_compare_tags( &ciphertext[ciphertext_length - tag_length], tag_for_comparison, tag_length );

        if( status != PSA_SUCCESS )
        {
            //todo by CL: also clear output buffer contents, just to be on safe side
            return( status );
        }

        MCUX_CSSL_FP_FUNCTION_CALL_END();
        /* Return with success */
        return PSA_SUCCESS;
    }

    return PSA_ERROR_NOT_SUPPORTED;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER() 
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length )
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
    status = mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt_internal(
                         &key,
                         alg,
                         nonce, nonce_length,
                         additional_data, additional_data_length,
                         ciphertext, ciphertext_length,
                         plaintext, plaintext_size, plaintext_length);

    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt_setup(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer,
   size_t key_buffer_size,
   psa_algorithm_t alg)
{
    /* For algorithms supported by CLNS, add implementation. */
    if(mcuxClPsaDriver_psa_driver_wrapper_aead_isAlgSupported(attributes))
    {
        /* Validate given key */
        if((PSA_KEY_USAGE_DECRYPT != (PSA_KEY_USAGE_DECRYPT & attributes->core.policy.usage))
            || !mcuxClPsaDriver_psa_driver_wrapper_aead_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Validate state
         *   - operation must not be active */
        if(0u != operation->body_started)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* Initialize the operation */
        operation->alg = alg;
        operation->key_type = attributes->core.type;
        operation->is_encrypt = 0u;
        operation->ad_remaining = 0u;
        operation->body_remaining = 0u;

        if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(alg))
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        /* Create the key */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
        mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

        /* Copy attributes, for AEAD domain_parameters should be NULL/0, but we will still copy pointer and size */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenNxpClMemory_copy, mcuxClMemory_copy(pClnsAeadData->keyAttributes, (const uint8_t *)attributes, MCUXCLPSADRIVER_AEAD_KEYATT_SIZE, sizeof(psa_key_attributes_t)));
        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenNxpClMemory_copy)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

        /* Get the correct tag length based on the given algorithm. */
        /*We should update the tag length here, as later in call, operation->alg is restored to psa_base_algo value by psa_crypto.c, hence by the time,
        we reach to function naunce set, where CL is setting tag length based upon operation->alg, it determines incorrect tag length as
        operation->alg is already reset to psa_base_alg_value. I have moved the value setting of tag length in psa_driver_wrapper_aead_encrypt_setup
        function instead of determining it in psa_driver_wrapper_aead_set_nonce.*/
        uint32_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(operation->alg);

        /* Only update a valid tag length in clns_ctx*/
        pClnsAeadData->ctx.tagLength = tag_length;
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        psa_status_t createKeyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey((const psa_key_attributes_t *)pClnsAeadData->keyAttributes, key_buffer, key_buffer_size, pKey);
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
        if(PSA_SUCCESS != createKeyStatus)
        {
            return createKeyStatus;
        }

        if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(pKey))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }

        /* Update the operation's status */
        operation->id = psa_driver_wrapper_get_clns_operation_id();

        /* Return with success */
        return PSA_SUCCESS;
    }

  return PSA_ERROR_NOT_SUPPORTED;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt_internal(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* For algorithms supported by CLNS, add implementation. */
    if(mcuxClPsaDriver_psa_driver_wrapper_aead_isAlgSupported(attributes))
    {
        /* Validate given sizes */
        uint32_t needed_output_size = PSA_AEAD_ENCRYPT_OUTPUT_SIZE(attributes->core.type, alg, plaintext_length);
        if(ciphertext_size < needed_output_size)
        {
            return PSA_ERROR_BUFFER_TOO_SMALL;
        }

        /* Validate given key */
        if((PSA_KEY_USAGE_ENCRYPT != (PSA_KEY_USAGE_ENCRYPT & attributes->core.policy.usage))
            || !mcuxClPsaDriver_psa_driver_wrapper_aead_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Get the correct AEAD mode based on the given algorithm. */
        mcuxClAead_Mode_t mode = mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeEnc(alg);
        if(NULL == mode)
        {
            return PSA_ERROR_CORRUPTION_DETECTED;
        }

        if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(alg))
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        /* Key buffer for the CPU workarea in memory. */
        uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

        /* Create session */
        mcuxClSession_Descriptor_t session;
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                        mcuxClSession_init(&session,
                                                          cpuWorkarea,
                                                          MCUXCLAEAD_WA_SIZE_MAX,
                                                          NULL,
                                                          0u));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Get the correct tag length based on the given algorithm. */
        uint32_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

        *ciphertext_length = 0u;
        /* Do the encryption */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultCrypt, tokenCrypt,
                                        mcuxClAead_crypt(&session,
                                                        pKey,
                                                        mode,
                                                        nonce, nonce_length,
                                                        plaintext, plaintext_length,
                                                        additional_data, additional_data_length,
                                                        ciphertext, (uint32_t *)ciphertext_length,
                                                        (uint8_t *)&ciphertext[plaintext_length], tag_length));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_crypt) != tokenCrypt) || (MCUXCLAEAD_STATUS_OK != resultCrypt))
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
        /* Update ciphertext_length by tag size, as they are in the same buffer */
        *ciphertext_length += tag_length;

        /* Return with success */
        return PSA_SUCCESS;
    }

    return PSA_ERROR_NOT_SUPPORTED;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length)
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
    status = mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt_internal(
                         &key,
                         alg,
                         nonce, nonce_length,
                         additional_data,additional_data_length,
                         plaintext, plaintext_length,
                         ciphertext, ciphertext_size, ciphertext_length);

    keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
    if(PSA_SUCCESS !=  keyStatus)
    {
        return keyStatus;
    }

    return status;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt_setup(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer,
   size_t key_buffer_size,
   psa_algorithm_t alg)
{
    /* For algorithms supported by CLNS, add implementation. */
    if(mcuxClPsaDriver_psa_driver_wrapper_aead_isAlgSupported(attributes))
    {
        /* Validate given key */
        if((PSA_KEY_USAGE_ENCRYPT != (PSA_KEY_USAGE_ENCRYPT & attributes->core.policy.usage))
            || !mcuxClPsaDriver_psa_driver_wrapper_aead_doesKeyPolicySupportAlg(attributes, alg))
        {
            return PSA_ERROR_NOT_PERMITTED;
        }

        /* Validate state
         *   - operation must not be active */
        if(0u != operation->id)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* Initialize the operation */
        operation->alg = alg;
        operation->key_type = attributes->core.type;
        operation->is_encrypt = 1u;
        operation->ad_remaining = 0u;
        operation->body_remaining = 0u;

        if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(alg))
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        /* Create the key */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
        mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

        /* Copy attributes, for AEAD domain_parameters should be NULL/0, but we will still copy pointer and size */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenNxpClMemory_copy, mcuxClMemory_copy(pClnsAeadData->keyAttributes, (const uint8_t *)attributes, MCUXCLPSADRIVER_AEAD_KEYATT_SIZE, sizeof(psa_key_attributes_t)));
        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenNxpClMemory_copy)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

        /* Get the correct tag length based on the given algorithm. */
        /*We should update the tag length here, as later in call, operation->alg is restored to psa_base_algo value by psa_crypto.c, hence by the time,
        we reach to function naunce set, where CL is setting tag length based upon operation->alg, it determines incorrect tag length as
        operation->alg is already reset to psa_base_alg_value. I have moved the value setting of tag length in psa_driver_wrapper_aead_encrypt_setup
        function instead of determining it in psa_driver_wrapper_aead_set_nonce.*/
        uint32_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(operation->alg);

        /* Only update a valid tag length in clns_ctx*/
        pClnsAeadData->ctx.tagLength = tag_length;
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        psa_status_t createKeyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey((const psa_key_attributes_t *)pClnsAeadData->keyAttributes, key_buffer, key_buffer_size, pKey);
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
        if(PSA_SUCCESS != createKeyStatus)
        {
            return createKeyStatus;
        }
        if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(pKey))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }

        /* Update the operation's status */
        operation->id = psa_driver_wrapper_get_clns_operation_id();

        /* Return with success */
        return PSA_SUCCESS;
    }

    return PSA_ERROR_NOT_SUPPORTED;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_finish(
   psa_aead_operation_t *operation,
   uint8_t *ciphertext,
   size_t ciphertext_size,
   size_t *ciphertext_length,
   uint8_t *tag,
   size_t tag_size,
   size_t *tag_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Validate state
     *   - must be active encryption operation
     *   - setup must be finished, i.e. nonce must have been set */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
       || (1u != operation->is_encrypt)
       || (1u != operation->nonce_set))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Validate that aad and input data were both fully provided */
    if((0u != operation->ad_remaining) || (0u != operation->body_remaining))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* Validate the given buffer sizes */
    /* operation->alg is already restored to base values. So, we cannot determine tag-Length here with its value.
    Tag_length is already determined during setup function and can be used from
    operation->ctx.clns_ctx.context.tagLength or pContext->tagLength*/
    uint32_t needed_tag_size    = pClnsAeadData->ctx.tagLength;
    uint32_t needed_output_size = PSA_AEAD_FINISH_OUTPUT_SIZE(operation->key_type, operation->alg);
    if((tag_size < needed_tag_size)
        /* if input is not a multiple of blocksize, check sufficient buffer size for ciphertext as well */
        || ((0u != (pClnsAeadData->ctx.dataLength % MCUXCLAES_BLOCK_SIZE)) && (ciphertext_size < needed_output_size)))
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

    /* Create session */
    mcuxClSession_Descriptor_t session;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLAEAD_WA_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call Finish AEAD */
    mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    *ciphertext_length = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultFinish, tokenFinish,
                                    mcuxClAead_finish(&session,
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                     (mcuxClAead_Context_t *) &pClnsAeadData->ctx,
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                     ciphertext,
                                                     (uint32_t *)ciphertext_length,
                                                     tag
                                                     ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_finish) != tokenFinish) || (MCUXCLAEAD_STATUS_OK != resultFinish))
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
    /* Set the tag_length */
    *tag_length = needed_tag_size;

    /* Return with success */
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_psa_driver_get_tag_len(
    psa_aead_operation_t *operation,
    uint8_t *tag_len )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    if(operation != NULL)
    {
        /* Create the key */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

        /* Only update a valid tag length in clns_ctx*/
        *tag_len = (uint8_t)pClnsAeadData->ctx.tagLength;

        status = PSA_SUCCESS;
    }
    /* Return psa status */
    return status;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_set_lengths(
   psa_aead_operation_t *operation,
   size_t ad_length,
   size_t plaintext_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Validate state
     *   - operation must be active
     *   - no nonce must have been set yet */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
        || (1u == operation->nonce_set))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Update the operation's status */
    operation->ad_remaining = ad_length;
    operation->body_remaining = plaintext_length;
    operation->lengths_set = 1u;

    /* Return with success */
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_set_nonce(
   psa_aead_operation_t *operation,
   const uint8_t *nonce,
   size_t nonce_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Validate state
     *   - operation must be active
     *   - no nonce must have been set yet
     *   - the lenghts must have been set if the algorithm requires it */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
       || (0u != operation->nonce_set)
       || (mcuxClPsaDriver_psa_driver_wrapper_aead_algNeedsLengthsSet(operation->alg) && (1u != operation->lengths_set)))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Get the correct AEAD mode based on the given algorithm. */
    const mcuxClAead_ModeDescriptor_t * mode = NULL;
    if(1u == operation->is_encrypt)
    {
        mode = mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeEnc(operation->alg);
    }
    else
    {
        mode = mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeDec(operation->alg);
    }
    if(NULL == mode)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* operation->alg is already restored to base values. So, we cannot determine tag-Length here with its value. Its already determined
    during setup and can be used from operation->ctx.clns_ctx.context.tagLength*/
    uint32_t tag_length = pClnsAeadData->ctx.tagLength;

    /* Add checks for valid tag length, otherwise return error*/
    psa_status_t status = mcuxClPsaDriver_psa_driver_wrapper_aead_checkTagLength(operation->alg);
    if(PSA_SUCCESS != status)
    {
        return( status );
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

    /* Create session */
    mcuxClSession_Descriptor_t session;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLAEAD_WA_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Initialize AEAD multi-part */
    mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume( pKey ))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultInit, tokenInit,
                                    mcuxClAead_init(&session,
                                                    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                   (mcuxClAead_Context_t *) &pClnsAeadData->ctx,
                                                    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                   pKey,
                                                   mode,
                                                   nonce,
                                                   nonce_length,
                                                   operation->body_remaining,
                                                   operation->ad_remaining,
                                                   tag_length
                                                   ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend( pKey ))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_init) != tokenInit) || (MCUXCLAEAD_STATUS_OK != resultInit))
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
    /* Update the operation's status */
    operation->nonce_set = 1u;

    /* Return with success */
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_update_ad(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Validate state
     *   - operation must be active
     *   - setup must be finished, i.e. nonce must have been set
     *   - aead_update/finish functions must not have been called yet */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
       || (1u != operation->nonce_set)
       || (0u != operation->body_started))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Validate given length: can be skipped as this is performed by psa_aead_update_ad(...) */

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

    /* Create session */
    mcuxClSession_Descriptor_t session;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLAEAD_WA_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call process additional data AEAD */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultProcessAad, tokenProcessAad,
                                    mcuxClAead_process_adata(&session,
                                                            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                            (mcuxClAead_Context_t *) &pClnsAeadData->ctx,
                                                            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                            input,
                                                            input_length
                                                            ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process_adata) != tokenProcessAad) || (MCUXCLAEAD_STATUS_OK != resultProcessAad))
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

    /* Update the operation's status */
    operation->ad_started = 1u;
    /* Update of operation->ad_remaining is performed by psa_aead_update_ad(...) in psa_crypto.c */

    /* Return with success */
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_update(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length,
   uint8_t *output,
   size_t output_size,
   size_t *output_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Validate state
     *   - operation must be active
     *   - setup must be finished, i.e. nonce must have been set */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
      || (1u != operation->nonce_set))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Validate given length: can be skipped as this is performed by psa_aead_update(...) */

    /* Validate the given buffer size */
    if(output_size < input_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

    /* Create session */
    mcuxClSession_Descriptor_t session;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLAEAD_WA_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call Process AEAD */


    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }


    *output_length = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultProcess, tokenProcess,
                                    mcuxClAead_process(&session,
                                                      MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                      (mcuxClAead_Context_t *) &pClnsAeadData->ctx,
                                                      MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                      input,
                                                      input_length,
                                                      output,
                                                      (uint32_t *)output_length
                                                      ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process) != tokenProcess) || (MCUXCLAEAD_STATUS_OK != resultProcess))
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
    /* Update the operation's status */
    operation->body_started = 1u;
    /* Update of operation->body_remaining is performed by psa_aead_update(...) in psa_crypto.c */

    /* Return with success */
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_verify(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
   psa_aead_operation_t *operation,
   uint8_t *plaintext,
   size_t plaintext_size,
   size_t *plaintext_length,
   const uint8_t *tag,
   size_t tag_length)
{
    /* Validate state
     *   - must be active decryption operation
     *   - setup must be finished, i.e. nonce must have been set */
    if((psa_driver_wrapper_get_clns_operation_id() != operation->id) // already checked in calling function
       || (0u != operation->is_encrypt)
       || (1u != operation->nonce_set))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Validate that aad and input data were both fully provided */
    if((0u != operation->ad_remaining) || (0u != operation->body_remaining))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    *plaintext_length = 0u;

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Aead_t * pClnsAeadData = (mcuxClPsaDriver_ClnsData_Aead_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* Validate the given buffer sizes */
    /* Used stored tag length from pContext instead of determining it at run time,
    as operation->alg has been overwritten to base_algo value*/
    if (tag_length < pClnsAeadData->ctx.tagLength)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLAEAD_WA_SIZE_IN_WORDS_MAX];

    /* Create session */
    mcuxClSession_Descriptor_t session;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLAEAD_WA_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call Verify AEAD */
    mcuxClKey_Descriptor_t * pKey = &pClnsAeadData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultVerify, tokenVerify,
                                    mcuxClAead_verify(&session,
                                                     MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                     (mcuxClAead_Context_t *) &pClnsAeadData->ctx,
                                                     MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                     tag,
                                                     plaintext,
                                                     (uint32_t *)plaintext_length
                                                     ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(pKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_verify) != tokenVerify) || (MCUXCLAEAD_STATUS_OK != resultVerify))
    {
        return PSA_ERROR_INVALID_SIGNATURE;
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

