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
 * @file  mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
 * @brief Example for the mcuxClEcc component
 *
 * @example mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
 * @brief   Example for the mcuxClEcc component EdDsa signature verification using the test vectors
 *          from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032
 */

#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection

#include <mcuxClExample_ELS_Helper.h>

#define RAM_START_ADDRESS MCUXCLPKC_RAM_START_ADDRESS
#define MAX_CPUWA_SIZE MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WACPU_SIZE
#define MAX_PKCWA_SIZE MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WAPKC_SIZE

/* Input taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pIn[] __attribute__ ((aligned (4))) =
{
    0xddu, 0xafu, 0x35u, 0xa1u, 0x93u, 0x61u, 0x7au, 0xbau,
    0xccu, 0x41u, 0x73u, 0x49u, 0xaeu, 0x20u, 0x41u, 0x31u,
    0x12u, 0xe6u, 0xfau, 0x4eu, 0x89u, 0xa9u, 0x7eu, 0xa2u,
    0x0au, 0x9eu, 0xeeu, 0xe6u, 0x4bu, 0x55u, 0xd3u, 0x9au,
    0x21u, 0x92u, 0x99u, 0x2au, 0x27u, 0x4fu, 0xc1u, 0xa8u,
    0x36u, 0xbau, 0x3cu, 0x23u, 0xa3u, 0xfeu, 0xebu, 0xbdu,
    0x45u, 0x4du, 0x44u, 0x23u, 0x64u, 0x3cu, 0xe8u, 0x0eu,
    0x2au, 0x9au, 0xc9u, 0x4fu, 0xa5u, 0x4cu, 0xa4u, 0x9fu
};

/* Signature taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pSignature[MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE] __attribute__ ((aligned (4))) =
{
    0xdcu, 0x2au, 0x44u, 0x59u, 0xe7u, 0x36u, 0x96u, 0x33u,
    0xa5u, 0x2bu, 0x1bu, 0xf2u, 0x77u, 0x83u, 0x9au, 0x00u,
    0x20u, 0x10u, 0x09u, 0xa3u, 0xefu, 0xbfu, 0x3eu, 0xcbu,
    0x69u, 0xbeu, 0xa2u, 0x18u, 0x6cu, 0x26u, 0xb5u, 0x89u,
    0x09u, 0x35u, 0x1fu, 0xc9u, 0xacu, 0x90u, 0xb3u, 0xecu,
    0xfdu, 0xfbu, 0xc7u, 0xc6u, 0x64u, 0x31u, 0xe0u, 0x30u,
    0x3du, 0xcau, 0x17u, 0x9cu, 0x13u, 0x8au, 0xc1u, 0x7au,
    0xd9u, 0xbeu, 0xf1u, 0x17u, 0x73u, 0x31u, 0xa7u, 0x04u
};

/* Public key taken from "TEST SHA(abc)" from Section 7.1 of IRTF rfc 8032 */
static const uint8_t pPublicKey[MCUXCLECC_EDDSA_ED25519_SIZE_PUBLICKEY] __attribute__ ((aligned (4))) =
{
    0xecu, 0x17u, 0x2bu, 0x93u, 0xadu, 0x5eu, 0x56u, 0x3bu,
    0xf4u, 0x93u, 0x2cu, 0x70u, 0xe1u, 0x24u, 0x50u, 0x34u,
    0xc3u, 0x54u, 0x67u, 0xefu, 0x2eu, 0xfdu, 0x4du, 0x64u,
    0xebu, 0xf8u, 0x19u, 0x68u, 0x34u, 0x67u, 0xe2u, 0xbfu
};

MCUXCLEXAMPLE_FUNCTION(mcuxClEcc_EdDSA_VerifySignature_Ed25519_example)
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

    /******************************************/
    /* Initialize the public key              */
    /******************************************/

    /* Initialize public key */
    uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
    mcuxClKey_Handle_t pubKeyHandler = (mcuxClKey_Handle_t) &pubKeyDesc;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyInit_status, keyInit_token, mcuxClKey_init(
        /* mcuxClSession_Handle_t session         */ &session,
        /* mcuxClKey_Handle_t key                 */ pubKeyHandler,
        /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_EdDSA_Ed25519_Pub,
        /* mcuxCl_Buffer_t pKeyData               */ (mcuxCl_Buffer_t) pPublicKey,
        /* uint32_t keyDataLength                */ sizeof(pPublicKey))
    );

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != keyInit_token) || (MCUXCLKEY_STATUS_OK != keyInit_status))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /**************************************************************************/
    /* Ed25519 signature verification                                         */
    /**************************************************************************/

    /* Call mcuxClEcc_EdDSA_VerifySignature to verify the signature */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClEcc_EdDSA_VerifySignature(
    /* mcuxClSession_Handle_t pSession                        */ &session,
    /* mcuxClKey_Handle_t pubKey                              */ pubKeyHandler,
    /* const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t*   */ &mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor,
    /* const uint8_t *pIn                                    */ pIn,
    /* uint32_t inSize                                       */ sizeof(pIn),
    /* const uint8_t *pSignature                             */ pSignature,
    /* uint32_t signatureSize                                */ sizeof(pSignature)
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_VerifySignature) != verify_token) || (MCUXCLECC_STATUS_OK != verify_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

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
