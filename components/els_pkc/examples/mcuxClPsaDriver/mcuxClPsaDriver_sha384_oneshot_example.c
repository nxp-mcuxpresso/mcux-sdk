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

bool mcuxClPsaDriver_sha384_oneshot_example(void)
{
    /* Input for the SHA-384 operation */
    const uint8_t data[] = {
        0x61u, 0x62u, 0x63u
    };

    /* Expected output for the SHA-384 operation */
    const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_384] = {
        0xCBu, 0x00u, 0x75u, 0x3Fu, 0x45u, 0xA3u, 0x5Eu, 0x8Bu,
        0xB5u, 0xA0u, 0x3Du, 0x69u, 0x9Au, 0xC6u, 0x50u, 0x07u,
        0x27u, 0x2Cu, 0x32u, 0xABu, 0x0Eu, 0xDEu, 0xD1u, 0x63u,
        0x1Au, 0x8Bu, 0x60u, 0x5Au, 0x43u, 0xFFu, 0x5Bu, 0xEDu,
        0x80u, 0x86u, 0x07u, 0x2Bu, 0xA1u, 0xE7u, 0xCCu, 0x23u,
        0x58u, 0xBAu, 0xECu, 0xA1u, 0x34u, 0xC8u, 0x25u, 0xA7u
    };

    /* Output buffer for the SHA-384 operation */
    uint8_t hashOutput[MCUXCLHASH_OUTPUT_SIZE_SHA_384];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    /* Variable for the output length of the encryption operation */
    size_t hashOutput_length;

    /* Call the hashing operation */
    psa_status_t result = psa_driver_wrapper_hash_compute(
        PSA_ALG_SHA_384,                     // psa_algorithm_t alg
        data,                                // const uint8_t *input
        sizeof(data),                        // size_t input_length
        hashOutput,                          // uint8_t *hash
        MCUXCLHASH_OUTPUT_SIZE_SHA_384,       // size_t hash_size
        &hashOutput_length);                 // size_t *hash_length

    /* Check the return value */
    if(result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(hashOutput_length != MCUXCLHASH_OUTPUT_SIZE_SHA_384) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the content */
    for (size_t i = 0U; i < MCUXCLHASH_OUTPUT_SIZE_SHA_384; i++)
    {
        if (hashOutput[i] != hashExpected[i]) // Expect that the resulting encrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_sha384_oneshot_example(void)
{
    bool result = mcuxClPsaDriver_sha384_oneshot_example();
    return result;
}
