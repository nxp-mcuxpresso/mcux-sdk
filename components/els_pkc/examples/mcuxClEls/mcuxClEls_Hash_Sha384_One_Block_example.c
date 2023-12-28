/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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
 * @file  mcuxClEls_Hash_Sha384_One_Block_example.c
 * @brief Example of SHA2-384 hashing using the ELS (CLNS component mcuxClEls)
 *
 * @example mcuxClEls_Hash_Sha384_One_Block_example.c
 * @brief   Example of SHA2-384 hashing using the ELS (CLNS component mcuxClEls)
 */

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>

/** Data input for SHA2-384 hashing. */
static uint8_t const sha384_padded_input[MCUXCLELS_HASH_BLOCK_SIZE_SHA_384] = {0x61U, 0x62U, 0x63U, 0x80U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00u, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00u, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x00U,
                                                                              0x00U, 0x00U, 0x00U, 0x18U};

/** Expected hash value. */
static uint8_t sha384_reference_digest[MCUXCLELS_HASH_OUTPUT_SIZE_SHA_384] = {0xcbU, 0x00U, 0x75U, 0x3fU,
                                                                             0x45U, 0xa3U, 0x5eU, 0x8bU,
                                                                             0xb5U, 0xa0U, 0x3dU, 0x69U,
                                                                             0x9aU, 0xc6U, 0x50U, 0x07U,
                                                                             0x27U, 0x2cU, 0x32U, 0xabU,
                                                                             0x0eU, 0xdeU, 0xd1U, 0x63U,
                                                                             0x1aU, 0x8bU, 0x60U, 0x5aU,
                                                                             0x43U, 0xffU, 0x5bU, 0xedU,
                                                                             0x80U, 0x86U, 0x07U, 0x2bU,
                                                                             0xa1U, 0xe7U, 0xccU, 0x23U,
                                                                             0x58U, 0xbaU, 0xecU, 0xa1U,
                                                                             0x34U, 0xc8U, 0x25U, 0xa7U};

/** Destination buffer to receive the hash output of the SHA2-384 hashing. */
static uint8_t sha2_384_digest[MCUXCLELS_HASH_STATE_SIZE_SHA_384]; // MCUXCLELS_HASH_STATE_SIZE_SHA_384 has to be used as the mcuxClEls_Hash_Async do not perform the truncation of the hash state.



/** Performs SHA2-384 hashing using mcuxClEls functions.
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Hash_Sha384_One_Block_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    
    mcuxClEls_HashOption_t hash_options = {0U};              // Initialize a new configuration for the planned mcuxClEls_Hash_Async operation.
    hash_options.bits.hashini = MCUXCLELS_HASH_INIT_ENABLE;  // Configure that the mcuxClEls_Hash_Async operation shall initialized with the standard IV (Initialization Vector).
    hash_options.bits.hashoe = MCUXCLELS_HASH_OUTPUT_ENABLE; // Configure the mcuxClEls_Hash_Async operation so that the hash digest is moved into memory at the end of the operation.
    hash_options.bits.hashmd = MCUXCLELS_HASH_MODE_SHA_384;  // Configure the mcuxClEls_Hash_Async operation so that the Sha2-384 algorithm is used.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Hash_Async( // Perform the hashing.
            hash_options,                                               // Set the prepared configuration.
            sha384_padded_input, sizeof(sha384_padded_input),           // Set the data to be hashed. Note that this data's length is a multiple of the block length, so no padding is required
            sha2_384_digest                                             // Output buffer, which the operation will write the hash digest to.
            ));
    // mcuxClEls_Hash_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hash_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Hash_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Hash_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    
    for (size_t i = 0; i < sizeof(sha384_reference_digest); i++)
    {
        if (sha2_384_digest[i] != sha384_reference_digest[i])
        {
           return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that the resulting hash digest matches our expected output
        }
    }
    
    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    
    return MCUXCLEXAMPLE_STATUS_OK;
}
