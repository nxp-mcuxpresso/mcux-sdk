/*--------------------------------------------------------------------------*/
/* Copyright 2021-2024 NXP                                                  */
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
 * @file  mcuxClEcc_MontDH_Curve25519_example.c
 * @brief Example for the mcuxClEcc component
 *
 * @example mcuxClEcc_MontDH_Curve25519_example.c
 * @brief   Example for the mcuxClEcc component Curve25519 related functions
 */

#include <mcuxClToolchain.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRandom.h>
#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_RNG_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection

#include <mcuxClExample_ELS_Helper.h>

#if MCUXCLECC_MONTDH_GENERATEKEYPAIR_CURVE25519_WACPU_SIZE >= MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE
    #define MAX_CPUWA_SIZE MCUXCLECC_MONTDH_GENERATEKEYPAIR_CURVE25519_WACPU_SIZE
#else
    #define MAX_CPUWA_SIZE MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE
#endif

#if MCUXCLECC_MONTDH_GENERATEKEYPAIR_CURVE25519_WAPKC_SIZE >= MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WAPKC_SIZE
    #define MAX_PKCWA_SIZE MCUXCLECC_MONTDH_GENERATEKEYPAIR_CURVE25519_WAPKC_SIZE
#else
    #define MAX_PKCWA_SIZE MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WAPKC_SIZE
#endif


MCUXCLEXAMPLE_FUNCTION(mcuxClEcc_MontDH_Curve25519_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Setup one session to be used by all functions called */
    mcuxClSession_Descriptor_t session;
    //Allocate and initialize session with pkcWA on the beginning of PKC RAM
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(&session, MAX_CPUWA_SIZE, MAX_PKCWA_SIZE);

    /* Initialize the RNG and Initialize the PRNG */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_RNG(&session, 0u, mcuxClRandomModes_Mode_ELS_Drbg);

    /* Prepare input for Alice key generation */
    ALIGNED uint8_t alicePrivKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t alicePrivKeyHandler = (mcuxClKey_Handle_t) &alicePrivKeyDesc;
    ALIGNED uint8_t alicePrivKeyBuffer[MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY]={0};

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(aliceprivkeyinit_result, aliceprivkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ alicePrivKeyHandler,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PrivateKey,
    /* const uint8_t * pKeyData              */ alicePrivKeyBuffer,
    /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != aliceprivkeyinit_token) || (MCUXCLKEY_STATUS_OK != aliceprivkeyinit_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    ALIGNED uint8_t alicePubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t alicePubKeyHandler = (mcuxClKey_Handle_t) &alicePubKeyDesc;
    ALIGNED uint8_t alicePubKeyBuffer[MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY]={0};

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(alicepubkeyinit_result, alicepubkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ alicePubKeyHandler,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PublicKey,
    /* const uint8_t * pKeyData              */ alicePubKeyBuffer,
    /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != alicepubkeyinit_token) || (MCUXCLKEY_STATUS_OK != alicepubkeyinit_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Prepare input for Bob key generation */
    ALIGNED uint8_t bobPrivKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t bobPrivKeyHandler = (mcuxClKey_Handle_t) &bobPrivKeyDesc;
    ALIGNED uint8_t bobPrivKeyBuffer[MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY]={0};

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(bobprivkeyinit_result, bobprivkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ bobPrivKeyHandler,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PrivateKey,
    /* const uint8_t * pKeyData              */ bobPrivKeyBuffer,
    /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != bobprivkeyinit_token) || (MCUXCLKEY_STATUS_OK != bobprivkeyinit_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    ALIGNED uint8_t bobPubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t bobPubKeyHandler = (mcuxClKey_Handle_t) &bobPubKeyDesc;
    ALIGNED uint8_t bobPubKeyBuffer[MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY]={0};

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(bobpubkeyinit_result, bobpubkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ bobPubKeyHandler,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PublicKey,
    /* const uint8_t * pKeyData              */ bobPubKeyBuffer,
    /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != bobpubkeyinit_token) || (MCUXCLKEY_STATUS_OK != bobpubkeyinit_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call Dh KeyGeneration for Alice keys generation and check FP and return code */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(alice_keygeneration_result, alice_keygeneration_token,
        mcuxClEcc_MontDH_GenerateKeyPair(&session,
                                        alicePrivKeyHandler,
                                        alicePubKeyHandler) );
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_GenerateKeyPair) != alice_keygeneration_token) || (MCUXCLECC_STATUS_OK != alice_keygeneration_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call Dh KeyGeneration for Bob keys generation and check FP and return code */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(bob_keygeneration_result, bob_keygeneration_token,
        mcuxClEcc_MontDH_GenerateKeyPair(&session,
                                        bobPrivKeyHandler,
                                        bobPubKeyHandler) );
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_GenerateKeyPair) != bob_keygeneration_token) || (MCUXCLECC_STATUS_OK != bob_keygeneration_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Prepare input for Alice shared secret calculation */
    ALIGNED uint8_t aliceSharedSecret[MCUXCLECC_MONTDH_CURVE25519_SIZE_SHAREDSECRET];
    uint32_t aliceSharedSecretSize;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(alice_keyagreement_result, alice_keyagreement_token,
        mcuxClEcc_MontDH_KeyAgreement(&session,
                                     alicePrivKeyHandler,
                                     bobPubKeyHandler,
                                     aliceSharedSecret,
                                     &aliceSharedSecretSize));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != alice_keyagreement_token) || (MCUXCLECC_STATUS_OK != alice_keyagreement_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Prepare input for Bob shared secret calculation */
    ALIGNED uint8_t bobSharedSecret[MCUXCLECC_MONTDH_CURVE25519_SIZE_SHAREDSECRET];
    uint32_t bobSharedSecretSize;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(bob_keyagreement_result, bob_keyagreement_token,
        mcuxClEcc_MontDH_KeyAgreement(&session,
                                     bobPrivKeyHandler,
                                     alicePubKeyHandler,
                                     bobSharedSecret,
                                     &bobSharedSecretSize));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != bob_keyagreement_token) || (MCUXCLECC_STATUS_OK != bob_keyagreement_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Alice's shared secret shall be equal to Bob's shared secret */
    for(size_t i = 0u; i < MCUXCLECC_MONTDH_CURVE25519_SIZE_SHAREDSECRET; i++)
    {
        if(bobSharedSecret[i] != aliceSharedSecret[i])
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(&session))
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
