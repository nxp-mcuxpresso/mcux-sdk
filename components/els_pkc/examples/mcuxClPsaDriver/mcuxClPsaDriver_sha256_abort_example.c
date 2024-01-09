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

bool mcuxClPsaDriver_sha256_abort_example(void)
{
    /* Input for the SHA-256 operation */
    const uint8_t data[] = {
        0x45u, 0x11u, 0x01u, 0x25u, 0x0eu, 0xc6u, 0xf2u, 0x66u,
        0x52u, 0x24u, 0x9du, 0x59u, 0xdcu, 0x97u, 0x4bu, 0x73u,
        0x61u, 0xd5u, 0x71u, 0xa8u, 0x10u, 0x1cu, 0xdfu, 0xd3u,
        0x6au, 0xbau, 0x3bu, 0x58u, 0x54u, 0xd3u, 0xaeu, 0x08u,
        0x6bu, 0x5fu, 0xddu, 0x45u, 0x97u, 0x72u, 0x1bu, 0x66u,
        0xe3u, 0xc0u, 0xdcu, 0x5du, 0x8cu, 0x60u, 0x6du, 0x96u,
        0x57u, 0xd0u, 0xe3u, 0x23u, 0x28u, 0x3au, 0x52u, 0x17u,
        0xd1u, 0xf5u, 0x3fu, 0x2fu, 0x28u, 0x4fu, 0x57u, 0xb8u,
        0x5cu, 0x8au, 0x61u, 0xacu, 0x89u, 0x24u, 0x71u, 0x1fu,
        0x89u, 0x5cu, 0x5eu, 0xd9u, 0x0eu, 0xf1u, 0x77u, 0x45u,
        0xedu, 0x2du, 0x72u, 0x8au, 0xbdu, 0x22u, 0xa5u, 0xf7u,
        0xa1u, 0x34u, 0x79u, 0xa4u, 0x62u, 0xd7u, 0x1bu, 0x56u,
        0xc1u, 0x9au, 0x74u, 0xa4u, 0x0bu, 0x65u, 0x5cu, 0x58u,
        0xedu, 0xfeu, 0x0au, 0x18u, 0x8au, 0xd2u, 0xcfu, 0x46u,
        0xcbu, 0xf3u, 0x05u, 0x24u, 0xf6u, 0x5du, 0x42u, 0x3cu,
        0x83u, 0x7du, 0xd1u, 0xffu, 0x2bu, 0xf4u, 0x62u, 0xacu,
        0x41u, 0x98u, 0x00u, 0x73u, 0x45u, 0xbbu, 0x44u, 0xdbu,
        0xb7u, 0xb1u, 0xc8u, 0x61u, 0x29u, 0x8cu, 0xdfu, 0x61u,
        0x98u, 0x2au, 0x83u, 0x3au, 0xfcu, 0x72u, 0x8fu, 0xaeu,
        0x1eu, 0xdau, 0x2fu, 0x87u, 0xaau, 0x2cu, 0x94u, 0x80u,
        0x85u, 0x8bu, 0xecu
    };

    /* Expected output for the SHA-256 operation */
    const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_256] = {
          0x3cu, 0x59u, 0x3au, 0xa5u, 0x39u, 0xfdu, 0xcdu, 0xaeu,
          0x51u, 0x6cu, 0xdfu, 0x2fu, 0x15u, 0x00u, 0x0fu, 0x66u,
          0x34u, 0x18u, 0x5cu, 0x88u, 0xf5u, 0x05u, 0xb3u, 0x97u,
          0x75u, 0xfbu, 0x9au, 0xb1u, 0x37u, 0xa1u, 0x0au, 0xa2u
    };

    /* Output buffer for the SHA-256 operation */
    uint8_t hashOutput[MCUXCLHASH_OUTPUT_SIZE_SHA_256];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Variable for the output length of the encryption operation */
    size_t hashOutput_length = 0u;

    psa_hash_operation_t hashOperation;

    /* Set up a hashing operation */
    psa_status_t setup_result =  psa_driver_wrapper_hash_setup(
        &hashOperation,                      // psa_hash_operation_t *operation
        PSA_ALG_SHA_256);                    // psa_algorithm_t alg

    /* Check the return value */
    if(setup_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Call the hashing update operation on data that needs to be discarded by hash_abort */
    psa_status_t update1_result = psa_driver_wrapper_hash_update(
        &hashOperation,                      // psa_hash_operation_t *operation
        data + 32u,                          // const uint8_t *input
        32u);                                // size_t input_length

    /* Check the return value */
    if(update1_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Call the hashing abort operation */
    psa_status_t abort_result = psa_driver_wrapper_hash_abort(
        &hashOperation);                     // psa_hash_operation_t *operation

    /* Check the return value */
    if(abort_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Set up a hashing operation */
    psa_status_t setup2_result =  psa_driver_wrapper_hash_setup(
        &hashOperation,                      // psa_hash_operation_t *operation
        PSA_ALG_SHA_256);                    // psa_algorithm_t alg

    /* Check the return value */
    if(setup2_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Call the hashing update operation again */
    psa_status_t update2_result = psa_driver_wrapper_hash_update(
        &hashOperation,                      // psa_hash_operation_t *operation
        data,                                // const uint8_t *input
        sizeof(data));                       // size_t input_length

    /* Check the return value */
    if(update2_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Call the hashing finish operation */
    psa_status_t finish_result = psa_driver_wrapper_hash_finish(
        &hashOperation,                      // psa_hash_operation_t *operation
        hashOutput,                          // uint8_t *hash
        MCUXCLHASH_OUTPUT_SIZE_SHA_256,       // size_t hash_size
        &hashOutput_length);                 // size_t *hash_length

    /* Check the return value */
    if(finish_result != PSA_SUCCESS) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(hashOutput_length != MCUXCLHASH_OUTPUT_SIZE_SHA_256) {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the content */
    for (size_t i = 0U; i < MCUXCLHASH_OUTPUT_SIZE_SHA_256; i++)
    {
        if (hashOutput[i] != hashExpected[i]) // Expect that the resulting encrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_sha256_abort_example(void)
{
    bool result = mcuxClPsaDriver_sha256_abort_example();
    return result;
}
