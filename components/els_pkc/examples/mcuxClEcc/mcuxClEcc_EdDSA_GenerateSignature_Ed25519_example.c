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
 * @file  mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
 * @brief Example for the mcuxClEcc component
 *
 * @example mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
 * @brief   Example for the mcuxClEcc component EdDsa signature generation using the test vectors
 *          from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032
 */

#include <mcuxClRandomModes.h>
#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_RNG_Helper.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection

#include <mcuxClExample_ELS_Helper.h>

#define RAM_START_ADDRESS MCUXCLPKC_RAM_START_ADDRESS
#define MAX_CPUWA_SIZE MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WACPU_SIZE, \
                                        MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WACPU_SIZE)
#define MAX_PKCWA_SIZE MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WAPKC_SIZE, \
                                        MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WAPKC_SIZE)

/* Private key input taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pPrivKeyInput[MCUXCLECC_EDDSA_ED25519_SIZE_PRIVATEKEY] __attribute__ ((aligned (4))) =
{
     0x83u, 0x3fu, 0xe6u, 0x24u, 0x09u, 0x23u, 0x7bu, 0x9du,
     0x62u, 0xecu, 0x77u, 0x58u, 0x75u, 0x20u, 0x91u, 0x1eu,
     0x9au, 0x75u, 0x9cu, 0xecu, 0x1du, 0x19u, 0x75u, 0x5bu,
     0x7du, 0xa9u, 0x01u, 0xb9u, 0x6du, 0xcau, 0x3du, 0x42u
};

/* Reference signature taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pRefSignature[MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE] __attribute__ ((aligned (4))) =
{
    0xDCu, 0x2Au, 0x44u, 0x59u, 0xE7u, 0x36u, 0x96u, 0x33u,
    0xA5u, 0x2Bu, 0x1Bu, 0xF2u, 0x77u, 0x83u, 0x9Au, 0x00u,
    0x20u, 0x10u, 0x09u, 0xA3u, 0xEFu, 0xBFu, 0x3Eu, 0xCBu,
    0x69u, 0xBEu, 0xA2u, 0x18u, 0x6Cu, 0x26u, 0xB5u, 0x89u,
    0x09u, 0x35u, 0x1Fu, 0xC9u, 0xACu, 0x90u, 0xB3u, 0xECu,
    0xFDu, 0xFBu, 0xC7u, 0xC6u, 0x64u, 0x31u, 0xE0u, 0x30u,
    0x3Du, 0xCAu, 0x17u, 0x9Cu, 0x13u, 0x8Au, 0xC1u, 0x7Au,
    0xD9u, 0xBEu, 0xF1u, 0x17u, 0x73u, 0x31u, 0xA7u, 0x04u
};

/* Input message taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pMessage[] __attribute__ ((aligned (4))) =
{
    0xDDu, 0xAFu, 0x35u, 0xA1u, 0x93u, 0x61u, 0x7Au, 0xBAu,
    0xCCu, 0x41u, 0x73u, 0x49u, 0xAEu, 0x20u, 0x41u, 0x31u,
    0x12u, 0xE6u, 0xFAu, 0x4Eu, 0x89u, 0xA9u, 0x7Eu, 0xA2u,
    0x0Au, 0x9Eu, 0xEEu, 0xE6u, 0x4Bu, 0x55u, 0xD3u, 0x9Au,
    0x21u, 0x92u, 0x99u, 0x2Au, 0x27u, 0x4Fu, 0xC1u, 0xA8u,
    0x36u, 0xBAu, 0x3Cu, 0x23u, 0xA3u, 0xFEu, 0xEBu, 0xBDu,
    0x45u, 0x4Du, 0x44u, 0x23u, 0x64u, 0x3Cu, 0xE8u, 0x0Eu,
    0x2Au, 0x9Au, 0xC9u, 0x4Fu, 0xA5u, 0x4Cu, 0xA4u, 0x9Fu
};

MCUXCLEXAMPLE_FUNCTION(mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example)
{
    /******************************************/
    /* Set up the environment                 */
    /******************************************/

    /* Initialize ELS, Enable the ELS */
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }


    /* Setup one session to be used by all functions called */
    mcuxClSession_Descriptor_t session;

    /* Allocate and initialize PKC workarea */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(&session, MAX_CPUWA_SIZE, MAX_PKCWA_SIZE);


    /* Initialize the RNG context and Initialize the PRNG */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_RNG(&session, 0u, mcuxClRandomModes_Mode_ELS_Drbg);

    /******************************************/
    /* Initialize the private and public keys */
    /******************************************/

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
        return MCUXCLEXAMPLE_STATUS_ERROR;
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
        return MCUXCLEXAMPLE_STATUS_ERROR;
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
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Key pair generation for EdDSA on Ed25519                               */
    /**************************************************************************/

    /* Call mcuxClEcc_EdDSA_GenerateKeyPair to derive the public key from the private one. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygen_result, keygen_token, mcuxClEcc_EdDSA_GenerateKeyPair(
    /*  mcuxClSession_Handle_t pSession                          */ &session,
    /*  const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode  */ (mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *) &privKeyInputDescriptor,
    /*  mcuxClKey_Handle_t privKey                               */ privKey,
    /*  mcuxClKey_Handle_t pubKey                                */ pubKey));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateKeyPair) != keygen_token) || (MCUXCLECC_STATUS_OK != keygen_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Ed25519 signature generation                                           */
    /**************************************************************************/

    /* Call mcuxClEcc_EdDSA_GenerateSignature to generate the signature. */
    uint8_t signatureBuffer[MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE] = {0};
    uint32_t signatureSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(sign_result, sign_token, mcuxClEcc_EdDSA_GenerateSignature(
    /*  mcuxClSession_Handle_t pSession                           */ &session,
    /*  mcuxClKey_Handle_t key                                    */ privKey,
    /*  const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode */ &mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor,
    /*  const uint8_t *pIn                                       */ pMessage,
    /*  uint32_t inSize                                          */ sizeof(pMessage),
    /*  uint8_t *pSignature                                      */ signatureBuffer,
    /*  uint32_t *const pSignatureSize                           */ &signatureSize));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateSignature) != sign_token)
        || (MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE != signatureSize)
        || (MCUXCLECC_STATUS_OK != sign_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /**************************************************************************/
    /* Ed25519 signature verification                                         */
    /**************************************************************************/

    /* Call mcuxClEcc_EdDSA_VerifySignature to verify the signature. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClEcc_EdDSA_VerifySignature(
    /* mcuxClSession_Handle_t pSession                       */ &session,
    /* mcuxClKey_Handle_t key                                */ pubKey,
    /* const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t * */ &mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor,
    /* const uint8_t *pIn                                   */ pMessage,
    /* uint32_t inSize                                      */ sizeof(pMessage),
    /* const uint8_t *pSignature                            */ (const uint8_t*)signatureBuffer,
    /* uint32_t signatureSize                               */ signatureSize
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_VerifySignature) != verify_token) || (MCUXCLECC_STATUS_OK != verify_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Compare the generated signature to the reference. */
    mcuxClCore_assertEqual(signatureBuffer, pRefSignature, MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE);

    /******************************************/
    /* Clean up                               */
    /******************************************/

    /* Destroy Session and cleanup Session */
    if(!mcuxClExample_Session_Clean(&session))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Disable the ELS */
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
