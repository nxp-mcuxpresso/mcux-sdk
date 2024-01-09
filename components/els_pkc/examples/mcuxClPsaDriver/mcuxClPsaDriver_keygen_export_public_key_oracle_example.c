/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/**
 * @file  mcuxClPsaDriver_keygen_export_public_key_oracle_example.c
 * @brief Example for generating and exporting internal key
 *
 * @example mcuxClPsaDriver_keygen_export_public_key_oracle_example.c
 * @brief Example for generating and exporting internal key
 */

#include "common.h"

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>
#include <mcuxClCore_Examples.h>

static const uint8_t expectKeyRet[MCUXCLELS_ECC_PUBLICKEY_SIZE] __attribute__ ((aligned (4))) =
{
    0x8b, 0xb1, 0x94, 0xb4, 0xaa, 0xa6, 0xd5, 0x73, 0xde, 0x81, 0xdd, 0x4a, 0xfd, 0x0a, 0x28, 0x5c,
    0x53, 0x57, 0x42, 0x9e, 0x81, 0x3a, 0x56, 0x90, 0x42, 0xbe, 0x91, 0xd2, 0x7a, 0xbd, 0x67, 0x20,
    0xb1, 0x39, 0xef, 0x56, 0x3c, 0x33, 0x7f, 0x08, 0xf0, 0x2b, 0x3a, 0xa2, 0xbf, 0x53, 0xe8, 0x2c,
    0x02, 0xe9, 0xb7, 0x84, 0x6f, 0xec, 0xef, 0x87, 0xd0, 0x96, 0x63, 0x3f, 0x93, 0x80, 0x0a, 0x3e
};
static const uint8_t privateKey[32u] __attribute__ ((aligned (4))) =
{
    0x5d, 0x6a, 0x75, 0xe6, 0x84, 0x8d, 0xd5, 0xc7, 0x93, 0xd0, 0x1c, 0xc0, 0x08, 0xac, 0x72, 0x93,
    0x8b, 0x70, 0x01, 0xd3, 0x38, 0x6c, 0x0d, 0x31, 0xa0, 0xeb, 0x2c, 0x0f, 0x72, 0x24, 0x09, 0x65
};
#define LIFETIME_INTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_EXTERNAL_STORAGE)
#define LIFETIME_EXTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)

/**
 * Internal function that loads a known key into the ELS key store via mcuxClEls_KeyProvision_Async.
 **/
static bool load_key_udf(
    mcuxClEls_KeyIndex_t targetKeyIdx,       ///< The key index at which the key shall be loaded
    mcuxClEls_KeyProp_t targetKeyProperties, ///< The target properties of the key
    uint8_t * pOutKey                       ///< Pointer to a memory location which receives the key which was loaded
)
{
    uint8_t keyprov_external_part1[MCUXCLELS_KEYPROV_KEY_PART_1_SIZE]  = {
        0x02, 0xed, 0x0c, 0xee, 0x10, 0x3d, 0x7b, 0x5a,
        0x74, 0xbf, 0x2e, 0xdf, 0x9f, 0x08, 0x68, 0xb6,
        0x4c, 0xba, 0xb9, 0xa2, 0xe9, 0xb5, 0x66, 0x05,
        0xc2, 0x87, 0xa7, 0xa9, 0x40, 0x6f, 0xe6, 0x29
    };

    uint8_t keyprov_external_part2[36]  = {
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22
    };
    // Desired key value
    const static uint8_t aes256_key[MCUXCLELS_CIPHER_KEY_SIZE_AES_256] = {
      0x4a, 0xdf, 0x2d, 0xd0, 0x0c, 0x88, 0xc7, 0x27,
      0x89, 0x00, 0x80, 0xc8, 0x65, 0x8a, 0x26, 0x54,
      0xee, 0x72, 0x57, 0x7b, 0x51, 0x42, 0xce, 0xe7,
      0x54, 0x9a, 0x67, 0xb2, 0x96, 0x63, 0x4c, 0x68
    };

    mcuxClEls_KeyProvisionOption_t options;
    options.word.value = 0;
    options.bits.noic  = 1;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ret_KeyProvision, token_KeyProvision, mcuxClEls_KeyProvision_Async(
            options,
            keyprov_external_part1,
            keyprov_external_part2,
            sizeof(keyprov_external_part2),
            targetKeyIdx,
            targetKeyProperties
    ));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyProvision_Async) != token_KeyProvision) || (MCUXCLELS_STATUS_OK_WAIT != ret_KeyProvision))
    {
        return false; // Expect that no error occurred, meaning that the mcuxClEls_EccKeyGen_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ret_WaitForOperation, token_WaitForOperation, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token_WaitForOperation) || (MCUXCLELS_STATUS_OK != ret_WaitForOperation))
    {
        return false; // Expect that no error occurred, meaning that the mcuxClEls_EccKeyGen_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    if (NULL != pOutKey)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (&pOutKey[0],
                                                                     aes256_key,
                                                                     MCUXCLELS_CIPHER_KEY_SIZE_AES_256,
                                                                     MCUXCLELS_CIPHER_KEY_SIZE_AES_256));

        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
        {
            return false;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    }
    return true;
}

/**
 * Internal function that performs RFC3394 key wrapping.
 * @retval true  Wrapping successful.
 * @retval false Wrapping error. */
static bool rfc3394_wrap(
    const uint8_t * pInput,         //< pointer to key to be wrapped
    size_t inputLength,             //< length of key to be wrapped in bytes
    mcuxClEls_KeyIndex_t keyIdx,     //< keyslot index of key wrapping key
    uint8_t * pOutput,              //< pointer to output buffer, size has to be inputLength + 16 bytes
    mcuxClEls_KeyProp_t properties   //< properties of the key to be wrapped
)
{
    uint32_t concat[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };

    uint32_t input[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };

    // Intermediate state is stored in pOutput as it is large enough

    // initialize buffer
    concat[0] = 0xA6A6A6A6u;   // first half of concat is the A from the standard, initialized to RFC3394 IV
    concat[1] = 0xA6A6A6A6u;
    concat[2] = properties.word.value;  // second half of concat is R(input)/B(output), first R consists of properties...
    concat[3] = 0x00000000u;            // ... and ELS padding (zeros)
    concat[2] = (concat[2] << 24u) | (concat[2] >> 24u) | ((concat[2] & 0x0000ff00u) << 8u) | ((concat[2] >> 8u) & 0x0000ff00u); // swap endianness

    // initialize ELS encryption parameters
    mcuxClEls_CipherOption_t cipher_options;
    cipher_options.word.value   = 0;
    cipher_options.bits.cphmde  = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipher_options.bits.dcrpt   = MCUXCLELS_CIPHER_ENCRYPT;
    cipher_options.bits.extkey  = 0;

    // input has to be multiple of 64 bits
    if (inputLength % sizeof(uint64_t) != 0u)
    {
        return false;
    }

    uint32_t *pSource = (uint32_t*) pInput;
    uint32_t *pDest   = (uint32_t*) pOutput;
    uint32_t std_n = inputLength/sizeof(uint64_t) + 1; // n value from standard
    for(size_t jdx = 0u; jdx < 6u; jdx++)
    {
        for(size_t idx = 0u; idx < std_n; idx++)
        {
            input[0]=concat[0];
            input[1]=concat[1];
            input[2]=concat[2];
            input[3]=concat[3];

            // Encrypt concatenated A and chunk to be processed
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Cipher_Async(
                cipher_options,
                keyIdx,
                NULL,
                0u,
                (uint8_t*) input,
                MCUXCLELS_CIPHER_BLOCK_SIZE_AES,
                NULL,
                (uint8_t*) concat));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            // Write out processed key chunk
            pDest[2u*idx + 2u] = concat[2u];
            pDest[2u*idx + 3u] = concat[3u];

            if( idx == std_n - 1u)
            {
                // Load next key chunk
                concat[2u] = pDest[2u];
                concat[3u] = pDest[3u];
                pSource = pDest + 4;
            }
            else
            {
                // Load next key chunk
                concat[2u] = pSource[2u*idx + 0u];
                concat[3u] = pSource[2u*idx + 1u];
            }

            // XOR round constant into A
            uint32_t gdx = std_n * jdx + (idx+1);  // all values should fit into a uint32_t
            gdx = (gdx << 24u) | (gdx >> 24u) | ((gdx & 0x0000ff00u) << 8u) | ((gdx >> 8u) & 0x0000ff00u); // swap endianness
            concat[1u] ^= gdx;
        }
    }
    // Write out processed key chunk
    pDest[0u] = concat[0u];
    pDest[1u] = concat[1u];

    return true;
}

bool mcuxClPsaDriver_keygen_export_public_key_oracle_example(void)
{
    /* Enable ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Enable_Async()); // Enable the ELS.
    // mcuxClEls_Enable_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Enable_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Enable_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Step 0.1:
        Reset ELS
        Note: this should better happen in the test framework CLNS-395
    */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Reset_Async(MCUXCLELS_RESET_CANCEL));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Reset_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Enable_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**********************************************************************************************/
    /*************************** Example Gen key pair *********************************************/
    /**********************************************************************************************/
    /* Set up PSA key attributes. */
    psa_key_attributes_t attributes = {
      .core = {                                                               // Core attributes
        .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),            // Keypair family with curve p-256
        .bits = 256U,                                                         // Key bits of a curve p-256
        .lifetime = LIFETIME_INTERNAL,                                        // Volatile (RAM), S50 Temporary Storage for private key
        .id = 6U,                                                             // private key slot
        .policy = {
          .usage = PSA_ALG_NONE,
          .alg = PSA_ALG_ECDSA_ANY,
          .alg2 = PSA_ALG_NONE},
        .flags = 0U},                                                         // No flags
      .domain_parameters = NULL,
      .domain_parameters_size = 0U};

    /* Call generate_key operation */
    uint32_t keyBuffer[32u/sizeof(uint32_t)] = {0};
    size_t key_buffer_length = 0U;

    psa_status_t status = psa_driver_wrapper_generate_key(
                &attributes,
                (uint8_t*)keyBuffer, sizeof(keyBuffer), &key_buffer_length );

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(key_buffer_length != 32u)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**********************************************************************************************/
    /*************************** Export SECP_R1 curve public key***********************************/
    /**********************************************************************************************/
    /* Step 1:
         Execute KEYPROV command
    */
    mcuxClEls_KeyIndex_t keyIdxKwk = 4U;
    mcuxClEls_KeyIndex_t aesHelperKeyIdx = 10U;
    mcuxClEls_KeyIndex_t  keyIdxExp = 14U;

    mcuxClEls_KeyProp_t          keyProp;
    keyProp.word.value       = 0u;
    keyProp.bits.ukwk        = MCUXCLELS_KEYPROPERTY_KWK_TRUE;
    keyProp.bits.ksize       = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv       = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_FALSE;
    bool keyProv_result = load_key_udf(keyIdxKwk, keyProp, NULL);
    if (!keyProv_result)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    keyProp.word.value = 0u;
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    keyProp.bits.upprot_sec =  MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
    keyProp.bits.uaes = MCUXCLELS_KEYPROPERTY_AES_TRUE;
    keyProp.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    keyProp.bits.kbase = MCUXCLELS_KEYPROPERTY_BASE_SLOT;
    bool keyProv_result2 = load_key_udf(aesHelperKeyIdx, keyProp, NULL);
    if (!keyProv_result2)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Step 2:
         Import private key
    */
    uint8_t key_rfc3394[MCUXCLELS_RFC3394_CONTAINER_SIZE_256];
    keyProp.word.value       = 0u;
    keyProp.bits.ksize       = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv       = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    keyProp.bits.ukgsrc      = MCUXCLELS_KEYPROPERTY_INPUT_FOR_ECC_TRUE;
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_FALSE;
    keyProp.bits.wrpok       = MCUXCLELS_KEYPROPERTY_WRAP_TRUE;

    bool wrap_result = rfc3394_wrap(privateKey,
                                    MCUXCLELS_CIPHER_KEY_SIZE_AES_256,
                                    aesHelperKeyIdx,
                                    key_rfc3394,
                                    keyProp);

    if (!wrap_result)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    mcuxClEls_KeyImportOption_t import_options;
    import_options.word.value = 0u;
    import_options.bits.kfmt = MCUXCLELS_KEYIMPORT_KFMT_RFC3394;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ret_KeyImport, token_KeyImport, mcuxClEls_KeyImport_Async(import_options, key_rfc3394, MCUXCLELS_RFC3394_CONTAINER_SIZE_256, keyIdxKwk, keyIdxExp));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyImport_Async) != token_KeyImport) || (MCUXCLELS_STATUS_OK_WAIT != ret_KeyImport))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Step 3:
         Call export_public_key operation
    */
    uint8_t data[MCUXCLELS_ECC_PUBLICKEY_SIZE] = {0U};
    size_t data_size = MCUXCLELS_ECC_PUBLICKEY_SIZE;
    size_t data_length = 0U;
    attributes.core.policy.usage = PSA_KEY_USAGE_EXPORT;
    status = psa_driver_wrapper_export_public_key(
                &attributes,
                (uint8_t*)&keyIdxExp,  sizeof(privateKey),
                data, data_size, &data_length );

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(data_length != MCUXCLELS_ECC_PUBLICKEY_SIZE)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    /**************************************************************************/
    /* Verification of the result                                             */
    /**************************************************************************/
    for (size_t i = 0U; i < sizeof(data_length); i++)
    {
        if (data[i] != expectKeyRet[i])
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_KeyDelete_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /*Step 4:
        Delete kwk and helperkey slot
    */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(keyIdxKwk));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(aesHelperKeyIdx));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(keyIdxExp));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Disable ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Disable()); // Disable the ELS.
    // mcuxClEls_Disable is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Disable) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_keygen_export_public_key_oracle_example(void)
{
    bool result = mcuxClPsaDriver_keygen_export_public_key_oracle_example();
    return result;
}
