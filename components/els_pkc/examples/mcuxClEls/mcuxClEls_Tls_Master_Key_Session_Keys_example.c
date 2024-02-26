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
 * @file  mcuxClEls_Tls_Master_Key_Session_Keys_example.c
 * @brief TLS key derivation example
 *
 * @example mcuxClEls_Tls_Master_Key_Session_Keys_example.c
 * @brief   TLS key derivation example
 */

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_ELS_Key_Helper.h>


/** Destination buffer to receive the public key of the mcuxClEls_EccKeyGen_Async operation. */
static uint32_t ecc_public_key_client[MCUXCLELS_ECC_PUBLICKEY_SIZE / sizeof(uint32_t)];
static uint32_t ecc_public_key_server[MCUXCLELS_ECC_PUBLICKEY_SIZE / sizeof(uint32_t)];

static uint8_t derivation_data[MCUXCLELS_TLS_DERIVATIONDATA_SIZE];
static uint8_t client_random[MCUXCLELS_TLS_RANDOM_SIZE];
static uint8_t server_random[MCUXCLELS_TLS_RANDOM_SIZE];

static uint8_t master_key_string[] = "master secret";
static uint8_t key_expansion_string[] = "key expansion";


/** Performs key derivation for TLS protocol.
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Tls_Master_Key_Session_Keys_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Generate client key pair */
    mcuxClEls_EccKeyGenOption_t KeyGenOptions = {0};
    KeyGenOptions.bits.kgsrc = MCUXCLELS_ECC_OUTPUTKEY_RANDOM; // Configure that a non-deterministic key is generated.
    KeyGenOptions.bits.kgtypedh = MCUXCLELS_ECC_OUTPUTKEY_KEYEXCHANGE; //Key will be used for Key Exchange

    mcuxClEls_KeyProp_t GenKeyProp = {0};
    GenKeyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE; // Configure that user access rights: non-privileged access
    GenKeyProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;       // Configure that user access rights: secure access

    mcuxClEls_KeyIndex_t keyIdxPrivClient = 0u;  // Set keystore index at which mcuxClEls_EccKeyGen_Async is storing the private key.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccKeyGen_Async( // Perform key generation.
            KeyGenOptions,                                  // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t) 0U,                       // This parameter (signingKeyIdx) is ignored, since no signature is requested in the configuration.
            keyIdxPrivClient,                               // Keystore index at which the generated private key is stored.
            GenKeyProp,                                     // Set the generated key properties.
            NULL,
			(uint8_t *)ecc_public_key_client                           // Output buffer, which the operation will write the public key to.
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

    /* Generate server key pair */
    mcuxClEls_KeyIndex_t keyIdxPrivServer = 2u;  // Set keystore index at which mcuxClEls_EccKeyGen_Async is storing the private key.

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccKeyGen_Async( // Perform key generation.
            KeyGenOptions,                                  // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t) 0U,                       // This parameter (signingKeyIdx) is ignored, since no signature is requested in the configuration.
            keyIdxPrivServer,                               // Keystore index at which the generated private key is stored.
            GenKeyProp,                                     // Set the generated key properties.
            NULL,
			(uint8_t *)ecc_public_key_server                           // Output buffer, which the operation will write the public key to.
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

    //Perform Key Exchange
    mcuxClEls_KeyIndex_t sharedSecretIdx = 10U; // Set shared key index

    mcuxClEls_KeyProp_t SharedSecretProp = {0};                           // Initialize a new configuration for the mcuxClEls_EccKeyExchange_Async generated key properties.
    SharedSecretProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE; // Configure that user access rights: non-privileged access
    SharedSecretProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;       // Configure that user access rights: secure access
    SharedSecretProp.bits.utlpsms = MCUXCLELS_KEYPROPERTY_TLS_PREMASTER_SECRET_TRUE; //Shared Secret is used as pre-master secret for TLS

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccKeyExchange_Async(
                                    keyIdxPrivClient,
									(uint8_t *)ecc_public_key_server,
                                    sharedSecretIdx,
                                    SharedSecretProp));

    // mcuxClEls_EccKeyExchange_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccKeyExchange_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_EccKeyExchange_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccKeyExchange_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    // PRNG needs to be initialized; this can be done by calling mcuxClEls_KeyDelete_Async (delete any key slot, can be empty)
    // However mcuxClEls_EccKeyExchange_Async also guarantees PRNG is initialized

    //generate server random
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Prng_GetRandom(server_random, 32U));
    // mcuxClEls_Prng_GetRandom is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Prng_GetRandom operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    //generate client random
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Prng_GetRandom(client_random, 32U));
    // mcuxClEls_Prng_GetRandom is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Prng_GetRandom operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    //perpare derivation data for master key
    //the derivation data has a fixed length of 640 bits and is composed as follows
    //"key expansion"||server random||client random||800000

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data,
                 key_expansion_string,
                 sizeof(key_expansion_string),
                 sizeof(key_expansion_string)
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data+sizeof(key_expansion_string),
                 server_random,
                 sizeof(server_random),
                 sizeof(server_random)
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data+sizeof(key_expansion_string)+32U,
                 client_random,
                 sizeof(client_random),
                 sizeof(client_random)
            ));
    // mcuxClMemory_set is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_set(
                 derivation_data+sizeof(key_expansion_string)+32U+32U,
                 0x80,
                 1U,
                 1U
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_set(
                 derivation_data+sizeof(key_expansion_string)+32U+32U+1U,
                 0x00,
                 2U,
                 2U
            ));
    // mcuxClMemory_set is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();


    mcuxClEls_KeyProp_t tlsMasterKeyProp = {0};
    tlsMasterKeyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE; // Configure that user access rights: non-privileged access
    tlsMasterKeyProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;       // Configure that user access rights: secure access
    tlsMasterKeyProp.bits.utlsms = MCUXCLELS_KEYPROPERTY_TLS_MASTER_SECRET_TRUE;
    //Generate TLS master key
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async(
                 derivation_data,  ///< [in] The TLS derivation data
                 tlsMasterKeyProp,  ///< [in] Desired key properties. Only #mcuxClEls_KeyProp_t::upprot_priv and #mcuxClEls_KeyProp_t::upprot_sec are used, the rest are ignored.
                 sharedSecretIdx        ///< [in] The index of the TLS pre-master key, which is overwritten with the master key
            ));
    // mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_TlsGenerateMasterKeyFromPreMasterKey_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    //perpare derivation data for session keys
    //the derivation data has a fixed length of 640 bits and is composed as follows
    //"master secret"||client random||server random||800000

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data,
                 master_key_string,
                 sizeof(master_key_string),
                 sizeof(master_key_string)
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data+sizeof(master_key_string),
                 client_random,
                 sizeof(client_random),
                 sizeof(client_random)
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(
                 derivation_data+sizeof(master_key_string)+32U,
                 server_random,
                 sizeof(server_random),
                 sizeof(server_random)
            ));
    // mcuxClMemory_set is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_set(
                 derivation_data+sizeof(master_key_string)+32U+32U,
                 0x80,
                 1U,
                 1U
            ));
    // mcuxClMemory_copy is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_set(
                 derivation_data+sizeof(master_key_string)+32U+32U+1U,
                 0x00,
                 2U,
                 2U
            ));
    // mcuxClMemory_set is a flow-protected function: Check the protection token and the return value
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) != token)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    mcuxClEls_KeyProp_t KeyProp = {0};
    mcuxClEls_GetKeyProperties(sharedSecretIdx, &KeyProp);

    //Generate TLS session keys
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async(
        derivation_data,  ///< [in] The TLS derivation data
        GenKeyProp,       ///< [in] Desired key properties. Only #mcuxClEls_KeyProp_t::upprot_priv and #mcuxClEls_KeyProp_t::upprot_sec are used, the rest are ignored.
        sharedSecretIdx   ///< [in] The index of the TLS master key, which is overwritten with one of the session keys.
        ));
    // mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_LimitedWaitForOperation(0x00100000U, MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_TlsGenerateSessionKeysFromMasterKey_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_LimitedWaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    //Delete all keys from keystore
    /** deleted keyIdxPrivClient keySlot **/
    if(!mcuxClExample_Els_KeyDelete(keyIdxPrivClient))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /** deleted keyIdxPrivServer keySlot **/
    if(!mcuxClExample_Els_KeyDelete(keyIdxPrivServer))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    for(uint8_t i = sharedSecretIdx;i<sharedSecretIdx + 6;i++)
    {
        /** deleted i keySlot **/
        if(!mcuxClExample_Els_KeyDelete(i))
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    //Now the session keys are stored in the key store as follows:
    //Client Mac Key : sharedSecretIdx (2-3)
    //Server Mac Key : sharedSecretIdx+2 (4-5)
    //Client Encryption Key : sharedSecretIdx+4 (6)
    //Server Encryption Key : sharedSecretIdx+6 (7)

    return MCUXCLEXAMPLE_STATUS_OK;
}
