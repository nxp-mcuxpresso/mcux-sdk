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

/**
 * @file  mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
 * @brief Example of ECC for key generation, signing and verification using the ELS (CLNS component mcuxClEls)
 *
 * @example mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
 * @brief   Example of ECC for key generation, signing and verification using the ELS (CLNS component mcuxClEls)
 */

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_ELS_Key_Helper.h>


/** Pre-hashed data to be signed */
static uint32_t const ecc_digest[MCUXCLELS_HASH_OUTPUT_SIZE_SHA_256 / sizeof(uint32_t)] = {0x11111111,
                                                                                           0x22222222,
                                                                                           0x33333333,
                                                                                           0x44444444,
                                                                                           0x55555555,
                                                                                           0x66666666,
                                                                                           0x77777777,
                                                                                           0x88888888};

/** Destination buffer to receive the public key of the mcuxClEls_EccKeyGen_Async operation. */
static uint32_t ecc_public_key[MCUXCLELS_ECC_PUBLICKEY_SIZE / sizeof(uint32_t)];

/** Destination buffer to receive the signature of the mcuxClEls_EccSign_Async operation. */
static uint32_t ecc_signature[MCUXCLELS_ECC_SIGNATURE_SIZE / sizeof(uint32_t)];


/** Destination buffer to receive the signature part r of the VerifyOptions operation. */
static uint32_t ecc_signature_r[MCUXCLELS_ECC_SIGNATURE_R_SIZE / sizeof(uint32_t)];


/** Concatenation of the ECC signature and public key, needed for the mcuxClEls_EccVerify_Async operation. */
static uint32_t ecc_signature_and_public_key[(MCUXCLELS_ECC_SIGNATURE_SIZE + MCUXCLELS_ECC_PUBLICKEY_SIZE) / sizeof(uint32_t)];


/**
 * Performs SHA2-256 hashing using mcuxClEls functions.
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Ecc_Keygen_Sign_Verify_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Generate signing key */
    mcuxClEls_EccKeyGenOption_t KeyGenOptions = {0};                      // Initialize a new configuration for the planned mcuxClEls_EccKeyGen_Async operation.
    KeyGenOptions.bits.kgsrc = MCUXCLELS_ECC_OUTPUTKEY_RANDOM;            // Configure that a non-deterministic key is generated.
    KeyGenOptions.bits.kgsign = MCUXCLELS_ECC_PUBLICKEY_SIGN_DISABLE;     // Configure that the generated public key is not signed
    KeyGenOptions.bits.kgsign_rnd = MCUXCLELS_ECC_NO_RANDOM_DATA;         // Configure that no external random data is provided
    
    mcuxClEls_KeyProp_t GenKeyProp = {0};                                 // Initialize a new configuration for the mcuxClEls_EccKeyGen_Async generated key properties.
    GenKeyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE; // Configure that user access rights: non-privileged access
    GenKeyProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;       // Configure that user access rights: non-secure access

    mcuxClEls_KeyIndex_t keyIdx = 10u;  // Set keystore index at which mcuxClEls_EccKeyGen_Async is storing the private key.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccKeyGen_Async( // Perform key generation.
            KeyGenOptions,                                  // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t) 0U,                       // This parameter (signingKeyIdx) is ignored, since no signature is requested in the configuration.
            keyIdx,                                         // Keystore index at which the generated private key is stored.
            GenKeyProp,                                     // Set the generated key properties.
            NULL,                                           // No random data is provided
            (uint8_t *) ecc_public_key                      // Output buffer, which the operation will write the public key to.
            ));
    // mcuxClEls_EccKeyGen_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccKeyGen_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_EccKeyGen_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccKeyGen_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Sign message digest */
    mcuxClEls_EccSignOption_t SignOptions = {0}; // Initialize a new configuration for the planned mcuxClEls_EccSign_Async operation.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccSign_Async(// Perform signature generation.
            SignOptions,                                                  // Set the prepared configuration.
            keyIdx,                                                       // Set index of private key in keystore.
            (const uint8_t *) ecc_digest, NULL, (size_t) 0U,              // Pre-hashed data to sign. Note that inputLength parameter is ignored since pre-hashed data has a fixed length.
            (uint8_t *)ecc_signature                                                 // Output buffer, which the operation will write the signature to.
            ));
    // mcuxClEls_EccSign_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccSign_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_EccSign_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccSign_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Verify signature */
    /* Concatenate signature and public key to prepare input for EccVerify_Async */
    for(size_t i = 0u; i < MCUXCLELS_ECC_SIGNATURE_SIZE; i++) {
        ((uint8_t *)ecc_signature_and_public_key)[i] = ((uint8_t *)ecc_signature)[i];
    }
    for(size_t i = 0u; i < MCUXCLELS_ECC_PUBLICKEY_SIZE; i++) {
        ((uint8_t *)ecc_signature_and_public_key)[MCUXCLELS_ECC_SIGNATURE_SIZE + i] = *((uint8_t *) ecc_public_key + i);
    }

    mcuxClEls_EccVerifyOption_t VerifyOptions = {0}; // Initialize a new configuration for the planned mcuxClEls_EccVerify_Async operation.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccVerify_Async(// Perform signature verification.
            VerifyOptions,                                                  // Set the prepared configuration.
            (const uint8_t *) ecc_digest, NULL, (size_t) 0U,                // Pre-hashed data to verify. Note that inputLength parameter is ignored since pre-hashed data has a fixed length.
            (const uint8_t *)ecc_signature_and_public_key,                  // Concatenation of signature of the pre-hashed data and public key used
            (uint8_t *)ecc_signature_r                                      // Output buffer, which the operation will write the signature part r to, to allow external comparison of between given and recalculated r.
            ));
    // mcuxClEls_EccVerify_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccVerify_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_EccVerify_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccVerify_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    mcuxClEls_HwState_t state;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetHwState(&state));
    // mcuxClEls_GetHwState is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    if (MCUXCLELS_STATUS_ECDSAVFY_OK != state.bits.ecdsavfy)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that mcuxClEls_EccVerify_Async operation successfully performed the signature verification.
    }

    /** deleted keyIdx keySlot **/
    if(!mcuxClExample_Els_KeyDelete(keyIdx))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }


    return MCUXCLEXAMPLE_STATUS_OK;
}
