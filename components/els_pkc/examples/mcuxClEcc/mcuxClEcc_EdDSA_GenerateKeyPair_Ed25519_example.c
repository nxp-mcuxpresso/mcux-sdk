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
 * @file  mcuxClEcc_EdDSA_GenerateKeyPair_Ed25519_example.c
 * @brief Example for the mcuxClEcc component
 *
 * @example mcuxClEcc_EdDSA_GenerateKeyPair_Ed25519_example.c
 * @brief   Example for the mcuxClEcc component EdDsa key pair generation using the test vectors
 *          from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032
 */

#include <mcuxClRandomModes.h>
#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_RNG_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection

#define RAM_START_ADDRESS MCUXCLPKC_RAM_START_ADDRESS
#define MAX_CPUWA_SIZE MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WACPU_SIZE
#define MAX_PKCWA_SIZE MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WAPKC_SIZE

/* Private key input taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pPrivKeyInput[MCUXCLECC_EDDSA_ED25519_SIZE_PRIVATEKEY] __attribute__ ((aligned (4))) =
{
     0x83u, 0x3fu, 0xe6u, 0x24u, 0x09u, 0x23u, 0x7bu, 0x9du,
     0x62u, 0xecu, 0x77u, 0x58u, 0x75u, 0x20u, 0x91u, 0x1eu,
     0x9au, 0x75u, 0x9cu, 0xecu, 0x1du, 0x19u, 0x75u, 0x5bu,
     0x7du, 0xa9u, 0x01u, 0xb9u, 0x6du, 0xcau, 0x3du, 0x42u
};

/* Reference public key taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pRefPubKey[MCUXCLECC_EDDSA_ED25519_SIZE_PUBLICKEY] __attribute__ ((aligned (4))) =
{
    0xecu, 0x17u, 0x2bu, 0x93u, 0xadu, 0x5eu, 0x56u, 0x3bu,
    0xf4u, 0x93u, 0x2cu, 0x70u, 0xe1u, 0x24u, 0x50u, 0x34u,
    0xc3u, 0x54u, 0x67u, 0xefu, 0x2eu, 0xfdu, 0x4du, 0x64u,
    0xebu, 0xf8u, 0x19u, 0x68u, 0x34u, 0x67u, 0xe2u, 0xbfu
};

MCUXCLEXAMPLE_FUNCTION(mcuxClEcc_EdDSA_GenerateKeyPair_Ed25519_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_ERROR;
    }


    /* Setup one session to be used by all functions called */
    mcuxClSession_Descriptor_t session;


    /* Allocate and initialize PKC workarea */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(&session, MAX_CPUWA_SIZE, MAX_PKCWA_SIZE);


    /* Initialize the RNG context and Initialize the PRNG */
    // TODO: Use AES-256 DRBG (CLNS-6508)
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_RNG(&session, 0u, mcuxClRandomModes_Mode_ELS_Drbg);
                                             
    /* Allocate space for and initialize private key handle for an Ed25519 private key */
    uint8_t privKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t privKey = (mcuxClKey_Handle_t) &privKeyDesc;
    uint8_t pPrivKeyData[MCUXCLECC_EDDSA_ED25519_SIZE_PRIVATEKEYDATA];

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(privkeyinit_result, privkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ privKey,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_EdDSA_Ed25519_Priv,
    /* mcuxCl_Buffer_t pKeyData               */ (mcuxCl_Buffer_t) pPrivKeyData,
    /* uint32_t keyDataLength                */ sizeof(pPrivKeyData)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != privkeyinit_token) || (MCUXCLKEY_STATUS_OK != privkeyinit_result))
    {
        return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Allocate space for and initialize public key handle for an Ed25519 public key */
    uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t pubKey = (mcuxClKey_Handle_t) &pubKeyDesc;
    uint8_t pPubKeyData[MCUXCLECC_EDDSA_ED25519_SIZE_PUBLICKEY];

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pubkeyinit_result, pubkeyinit_token, mcuxClKey_init(
    /* mcuxClSession_Handle_t session         */ &session,
    /* mcuxClKey_Handle_t key                 */ pubKey,
    /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_EdDSA_Ed25519_Pub,
    /* mcuxCl_Buffer_t pKeyData               */ (mcuxCl_Buffer_t) pPubKeyData,
    /* uint32_t keyDataLength                */ sizeof(pPubKeyData)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != pubkeyinit_token) || (MCUXCLKEY_STATUS_OK != pubkeyinit_result))
    {
        return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Allocate space for and initialize EdDSA key pair generation descriptor for private key input */
    uint8_t privKeyInputDescriptor[MCUXCLECC_EDDSA_GENERATEKEYPAIR_DESCRIPTOR_SIZE];
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(initmode_result, initmode_token, mcuxClEcc_EdDSA_InitPrivKeyInputMode(
    /* mcuxClSession_Handle_t pSession                   */ &session,
    /* mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode */ (mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *) &privKeyInputDescriptor,
    /* const uint8_t *pPrivKey                          */ pPrivKeyInput));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_InitPrivKeyInputMode) != initmode_token) || (MCUXCLECC_STATUS_OK != initmode_result))
    {
        return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Call mcuxClEcc_EdDSA_GenerateKeyPair to derive the public key from the private one. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygen_result, keygen_token, mcuxClEcc_EdDSA_GenerateKeyPair(
    /*  mcuxClSession_Handle_t pSession                          */ &session,
    /*  const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode  */ (mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *) &privKeyInputDescriptor,
    /*  mcuxClKey_Handle_t privKey                               */ privKey,
    /*  mcuxClKey_Handle_t pubKey                                */ pubKey));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateKeyPair) != keygen_token) || (MCUXCLECC_STATUS_OK != keygen_result))
    {
        return MCUXCLEXAMPLE_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Compare the generated public key to the reference. */
    mcuxClCore_assertEqual(pPubKeyData, pRefPubKey, MCUXCLECC_EDDSA_ED25519_SIZE_PUBLICKEY);


    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(&session))
    {
        return MCUXCLEXAMPLE_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_ERROR;
    }

    return MCUXCLEXAMPLE_OK;
}
