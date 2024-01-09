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

#include "common.h"

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>
#include <mcuxClAes.h> // Interface to AES-related definitions and types
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>

#define LIFETIME_INTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_EXTERNAL_STORAGE)
#define LIFETIME_EXTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)

bool mcuxClPsaDriver_truncated_mac_oneshot_example(void)
{
    /* Example AES-128 key. */
    const uint8_t aes128_key[MCUXCLAES_AES128_KEY_SIZE] = {
                                        0x7c, 0x0b, 0x7d, 0xb9,
                                        0x81, 0x1f, 0x10, 0xd0,
                                        0x0e, 0x47, 0x6c, 0x7a,
                                        0x0d, 0x92, 0xf6, 0xe0
    };

    /* Example input to the CMAC function. */
    const uint8_t cmac_input[] = {
                                        0x1e, 0xe0, 0xec, 0x46,
                                        0x6d, 0x46, 0xfd, 0x84,
                                        0x9b, 0x40, 0xc0, 0x66,
                                        0xb4, 0xfb, 0xbd, 0x22,
                                        0xa2, 0x0a, 0x4d, 0x80,
                                        0xa0, 0x08, 0xac, 0x9a,
                                        0xf1, 0x7e, 0x4f, 0xdf,
                                        0xd1, 0x06, 0x78, 0x5e
    };

    /* Example reference CMAC. */
    const uint8_t cmac_output_reference[4] = {
                                        0xba, 0xec, 0xdc, 0x91
    };

    /* Output buffer for the MAC operation */
    uint8_t cmac_output[PSA_MAC_MAX_SIZE];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Set up PSA key attributes. */
    psa_key_attributes_t attributes = {
        .core = {                                               // Core attributes
            .type = PSA_KEY_TYPE_AES,                           // Key is for CMAC operations
            .bits = 8u * MCUXCLELS_CIPHER_KEY_SIZE_AES_128,      // Key size in bits
            .lifetime = LIFETIME_EXTERNAL,                      // Volatile (RAM), Local Storage (plain) key
            .id = 0U,                                           // ID zero
            .policy = {
                .usage = PSA_KEY_USAGE_SIGN_HASH,               // Key may be used for encryption
                .alg = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CMAC, 4u), // truncated CMAC requested
                .alg2 = PSA_ALG_NONE},
            .flags = 0u},                                       // No flags
        .domain_parameters = NULL,                              // No domain parameters
        .domain_parameters_size = 0u};

    /* Variable for the output length of the encryption operation */
    size_t output_length;

    /* Call the encryption operation */
    psa_status_t result = psa_driver_wrapper_mac_compute(
        &attributes,                                                                                                       // const psa_key_attributes_t *attributes,
        aes128_key,                                                                                                        // const uint8_t *key_buffer
        MCUXCLELS_CIPHER_KEY_SIZE_AES_128,                                                                                  // size_t key_buffer_size
        PSA_ALG_TRUNCATED_MAC(PSA_ALG_CMAC, 4u),                                                                           // psa_algorithm_t alg
        cmac_input,                                                                                                        // const uint8_t *input
        sizeof(cmac_input),                                                                                                // size_t input_length
        cmac_output,                                                                                                       // uint8_t *output
        PSA_MAC_LENGTH(PSA_KEY_TYPE_AES, 8u * MCUXCLELS_CIPHER_KEY_SIZE_AES_128, PSA_ALG_TRUNCATED_MAC(PSA_ALG_CMAC, 4u)),  // size_t output_size
        &output_length);                                                                                                   // size_t *output_length

    /* Check the return value */
    if(result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(output_length != PSA_MAC_LENGTH(PSA_KEY_TYPE_AES, 8u * MCUXCLELS_CIPHER_KEY_SIZE_AES_128, PSA_ALG_TRUNCATED_MAC(PSA_ALG_CMAC, 4u)))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(sizeof(cmac_output_reference) != output_length)
    {
        return MCUXCLEXAMPLE_STATUS_FAILURE;
    }

    /* Check the content */
    for (size_t i = 0U; i < output_length; i++)
    {
        if (cmac_output[i] != cmac_output_reference[i]) // Expect that the resulting encrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_truncated_mac_oneshot_example(void)
{
    bool result = mcuxClPsaDriver_truncated_mac_oneshot_example();
    return result;
}
