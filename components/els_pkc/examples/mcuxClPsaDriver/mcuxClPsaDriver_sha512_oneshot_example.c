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

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>             // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>

bool mcuxClPsaDriver_sha512_oneshot_example(void)
{
    /* Input for the SHA-384 operation */
    const uint8_t data[] = {
        0x61u, 0x62u, 0x63u
    };

    /* Expected output for the SHA-384 operation */
    const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_512] = {
        0xDDu, 0xAFu, 0x35u, 0xA1u, 0x93u, 0x61u, 0x7Au, 0xBAu,
        0xCCu, 0x41u, 0x73u, 0x49u, 0xAEu, 0x20u, 0x41u, 0x31u,
        0x12u, 0xE6u, 0xFAu, 0x4Eu, 0x89u, 0xA9u, 0x7Eu, 0xA2u,
        0x0Au, 0x9Eu, 0xEEu, 0xE6u, 0x4Bu, 0x55u, 0xD3u, 0x9Au,
        0x21u, 0x92u, 0x99u, 0x2Au, 0x27u, 0x4Fu, 0xC1u, 0xA8u,
        0x36u, 0xBAu, 0x3Cu, 0x23u, 0xA3u, 0xFEu, 0xEBu, 0xBDu,
        0x45u, 0x4Du, 0x44u, 0x23u, 0x64u, 0x3Cu, 0xE8u, 0x0Eu,
        0x2Au, 0x9Au, 0xC9u, 0x4Fu, 0xA5u, 0x4Cu, 0xA4u, 0x9Fu
    };

    /* Output buffer for the SHA-384 operation */
    uint8_t hashOutput[MCUXCLHASH_OUTPUT_SIZE_SHA_512];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Variable for the output length of the encryption operation */
    size_t hashOutput_length;

    /* Call the hashing operation */
    psa_status_t result = psa_driver_wrapper_hash_compute(
        PSA_ALG_SHA_512,                     // psa_algorithm_t alg
        data,                                // const uint8_t *input
        sizeof(data),                        // size_t input_length
        hashOutput,                          // uint8_t *hash
        MCUXCLHASH_OUTPUT_SIZE_SHA_512,       // size_t hash_size
        &hashOutput_length);                 // size_t *hash_length

    /* Check the return value */
    if(result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(hashOutput_length != MCUXCLHASH_OUTPUT_SIZE_SHA_512) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the content */
    for (size_t i = 0U; i < MCUXCLHASH_OUTPUT_SIZE_SHA_512; i++)
    {
        if (hashOutput[i] != hashExpected[i]) // Expect that the resulting encrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_sha512_oneshot_example(void)
{
    bool result = mcuxClPsaDriver_sha512_oneshot_example();
    return result;
}
