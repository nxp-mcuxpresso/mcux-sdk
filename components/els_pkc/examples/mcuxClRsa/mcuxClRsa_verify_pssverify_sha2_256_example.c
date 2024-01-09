/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClRsa_verify_pssverify_sha2_256_example.c
 * @brief Example of using function mcuxClRsa_verify to perform the RSA signature verification with
 * EMSA-PSS-VERIFY padding scheme according to PKCS #1 v2.2.
 *
 * @example  mcuxClRsa_verify_pssverify_sha2_256_example.c
 * @brief Example of using function mcuxClRsa_verify to perform the RSA signature verification with
 * EMSA-PSS-VERIFY padding scheme according to PKCS #1 v2.2.
 */

#include <mcuxClSession.h>          // Interface to the entire mcuxClSession component
#include <mcuxClExample_Session_Helper.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClRandom.h>           // Interface to the entire mcuxClRandom component
#include <mcuxClRsa.h>              // Interface to the entire mcuxClRsa component
#include <mcuxClToolchain.h>             // Memory segment definitions
#include <mcuxClCore_Examples.h>
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>

/**********************************************************/
/* Example test vectors                                   */
/**********************************************************/

#define RSA_KEY_BIT_LENGTH         (2048u)                   ///< The example uses a 2048-bit key
#define RSA_KEY_BYTE_LENGTH        (RSA_KEY_BIT_LENGTH / 8u) ///< Converting the key-bitlength to bytelength
#define RSA_PUBLIC_EXP_BYTE_LENGTH (3u)                      ///< The public exponent has a length of three bytes
#define RSA_MESSAGE_DIGEST_LENGTH  (32u)                     ///< The example uses a Sha2-256 digest, which is 32 bytes long
#define RSA_PSS_SALT_LENGTH        (32u)                     ///< The salt for the PSS padding is 32 bytes long

/**
 * @brief Example value for public RSA modulus N.
 */
static const uint8_t modulus[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
  0xb4u, 0xbfu, 0xc5u, 0xdeu, 0x4au, 0x63u, 0xe3u, 0xe2u, 0x58u, 0x1cu, 0x43u, 0x91u, 0xeau, 0x42u, 0x31u, 0x1au,
  0x86u, 0xc3u, 0xddu, 0x71u, 0x8au, 0xa2u, 0x56u, 0xd2u, 0xdcu, 0xedu, 0xecu, 0x81u, 0x1cu, 0xebu, 0x6cu, 0xeeu,
  0x54u, 0xe1u, 0x39u, 0xb2u, 0x53u, 0x34u, 0x5du, 0x4bu, 0xc5u, 0x37u, 0x0eu, 0xe9u, 0xcfu, 0xe3u, 0x93u, 0x47u,
  0xdau, 0x6bu, 0x3du, 0x72u, 0x95u, 0xecu, 0xeeu, 0x13u, 0x9fu, 0xd0u, 0x00u, 0x06u, 0x57u, 0x29u, 0xe3u, 0xd2u,
  0xc5u, 0x93u, 0x31u, 0x79u, 0x55u, 0x94u, 0x8cu, 0x3eu, 0xf1u, 0xfdu, 0x82u, 0xf1u, 0x26u, 0xf0u, 0x5bu, 0x28u,
  0xc2u, 0x72u, 0x22u, 0x67u, 0x3au, 0x36u, 0x9cu, 0xf5u, 0x1fu, 0xb5u, 0xeeu, 0xc0u, 0x06u, 0x86u, 0xbbu, 0x3cu,
  0xcdu, 0xbcu, 0x92u, 0x6fu, 0x82u, 0x08u, 0x7eu, 0xa8u, 0x05u, 0xd4u, 0xecu, 0xccu, 0xbcu, 0xacu, 0x68u, 0x19u,
  0x7fu, 0x2du, 0x5cu, 0x2du, 0xe1u, 0x86u, 0xfdu, 0xa1u, 0xf6u, 0xffu, 0x8du, 0xa3u, 0x03u, 0x4fu, 0x71u, 0xe7u,
  0x99u, 0x50u, 0xb9u, 0x69u, 0x7cu, 0xa4u, 0x10u, 0xcdu, 0xbeu, 0xbfu, 0x68u, 0xb6u, 0x5bu, 0xacu, 0xfbu, 0x74u,
  0xe1u, 0x8du, 0x58u, 0x33u, 0x07u, 0x8eu, 0xcdu, 0x46u, 0x34u, 0x9au, 0xd8u, 0x49u, 0xb5u, 0x58u, 0x4bu, 0xceu,
  0x2bu, 0xa2u, 0x0au, 0x77u, 0x46u, 0xdau, 0x8cu, 0xfbu, 0x7eu, 0xd7u, 0xc7u, 0xddu, 0xffu, 0x9eu, 0x10u, 0x43u,
  0xb8u, 0xfeu, 0x67u, 0x95u, 0xe4u, 0x0fu, 0x68u, 0x47u, 0xd3u, 0xc2u, 0x11u, 0x83u, 0xbbu, 0x53u, 0x0du, 0xc5u,
  0x4du, 0x8eu, 0x75u, 0x53u, 0x86u, 0xe5u, 0x90u, 0xffu, 0x7fu, 0x7au, 0x47u, 0x17u, 0x7au, 0x69u, 0x13u, 0x52u,
  0xb6u, 0xa7u, 0xf0u, 0xceu, 0x48u, 0x9eu, 0x83u, 0xecu, 0x43u, 0xfdu, 0x05u, 0xd6u, 0xe4u, 0xbcu, 0xd5u, 0x1au,
  0x90u, 0xc2u, 0x4bu, 0xfdu, 0x38u, 0xd3u, 0xf7u, 0x66u, 0x6du, 0x2au, 0xccu, 0x5bu, 0x5fu, 0xc5u, 0x67u, 0x0cu,
  0x3eu, 0xe8u, 0xc8u, 0xbeu, 0xb9u, 0x2fu, 0xa4u, 0x8au, 0xb6u, 0x5du, 0x5fu, 0xecu, 0xfeu, 0xf3u, 0x2eu, 0xd7u,
 };

/**
 * @brief Example value for public RSA exponent e.
 */
static const uint8_t exponent[RSA_PUBLIC_EXP_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
  0x01u, 0x00u, 0x01u
};

/**
 * @brief Example value for Sha2-256 message digest.
 */
static const uint8_t message[RSA_MESSAGE_DIGEST_LENGTH] __attribute__ ((aligned (4))) = {
  0x9fu, 0x86u, 0xd0u, 0x81u, 0x88u, 0x4cu, 0x7du, 0x65u, 0x9au, 0x2fu, 0xeau, 0xa0u, 0xc5u, 0x5au, 0xd0u, 0x15u,
  0xa3u, 0xbfu, 0x4fu, 0x1bu, 0x2bu, 0x0bu, 0x82u, 0x2cu, 0xd1u, 0x5du, 0x6cu, 0x15u, 0xb0u, 0xf0u, 0x0au, 0x08u,
};

/**
 * @brief Example value for RSA signature s.
 */
static const uint8_t signature[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
  0x5eu, 0xa5u, 0x03u, 0x94u, 0x3cu, 0x28u, 0xbcu, 0x90u, 0x66u, 0xb6u, 0xedu, 0x45u, 0x00u, 0x79u, 0x0fu, 0x85u,
  0x23u, 0xf5u, 0x6bu, 0x20u, 0x7du, 0x55u, 0x6fu, 0x0fu, 0x28u, 0x5fu, 0x2du, 0xdbu, 0x85u, 0xe7u, 0x8eu, 0x7bu,
  0x42u, 0xbau, 0x10u, 0x79u, 0xc0u, 0x16u, 0xd2u, 0x01u, 0x21u, 0x6bu, 0xc6u, 0x4cu, 0x57u, 0x0au, 0x4eu, 0x85u,
  0x2au, 0x89u, 0xdeu, 0x4bu, 0xccu, 0xb3u, 0xa0u, 0xdcu, 0x35u, 0xe9u, 0xf7u, 0xfeu, 0xe8u, 0xe9u, 0x2cu, 0xfeu,
  0x20u, 0x96u, 0x04u, 0x5fu, 0x46u, 0x09u, 0xb5u, 0xb7u, 0x1eu, 0xf9u, 0xcdu, 0x73u, 0x05u, 0xf8u, 0xe8u, 0xdeu,
  0x2cu, 0x17u, 0x50u, 0xd1u, 0xd5u, 0x66u, 0x4fu, 0xa2u, 0x9au, 0x26u, 0x28u, 0xd9u, 0x66u, 0x7fu, 0x87u, 0x80u,
  0x69u, 0x34u, 0x3du, 0xd3u, 0xdbu, 0x06u, 0xe5u, 0x7cu, 0x3cu, 0xf3u, 0x4au, 0x3fu, 0xb7u, 0x97u, 0x90u, 0x4fu,
  0x72u, 0x92u, 0x54u, 0xa0u, 0x9cu, 0x2fu, 0x29u, 0x94u, 0x65u, 0xa0u, 0xd6u, 0xafu, 0x9bu, 0xcau, 0xa6u, 0x0fu,
  0x90u, 0x45u, 0x79u, 0x36u, 0x00u, 0xeau, 0x08u, 0xb2u, 0x0du, 0x8cu, 0xe7u, 0xefu, 0x08u, 0x95u, 0x61u, 0xf3u,
  0x79u, 0x54u, 0xd7u, 0xb6u, 0x22u, 0x01u, 0x46u, 0x41u, 0xb0u, 0xadu, 0xf1u, 0x03u, 0x0cu, 0x00u, 0xdcu, 0xb9u,
  0x33u, 0x3du, 0x1cu, 0xe1u, 0x16u, 0xd6u, 0xd9u, 0x4au, 0x16u, 0x9cu, 0x51u, 0x12u, 0x22u, 0x54u, 0x15u, 0xe0u,
  0xefu, 0x2au, 0xb9u, 0xeeu, 0x3cu, 0x2cu, 0xe8u, 0x5eu, 0xaau, 0x58u, 0x26u, 0x0cu, 0xeeu, 0x4bu, 0x34u, 0x94u,
  0x53u, 0xc9u, 0x97u, 0x50u, 0xceu, 0xb4u, 0xd1u, 0xceu, 0x38u, 0xbfu, 0xe4u, 0x5cu, 0x5du, 0x24u, 0x00u, 0xceu,
  0xfau, 0x8au, 0xbau, 0x42u, 0xeau, 0xa8u, 0x4fu, 0x7du, 0xa2u, 0x37u, 0x17u, 0x7eu, 0x62u, 0xe7u, 0x60u, 0x2cu,
  0x01u, 0x97u, 0x68u, 0x26u, 0xb6u, 0xf0u, 0x8bu, 0xe6u, 0x4eu, 0xa6u, 0xb2u, 0x4fu, 0x0eu, 0x11u, 0x3cu, 0x93u,
  0x5eu, 0xcdu, 0x35u, 0x70u, 0x82u, 0x63u, 0xadu, 0x5fu, 0x3cu, 0x6au, 0x51u, 0x9fu, 0x5eu, 0xd5u, 0xbau, 0xf6u,
};



/** Performs a session set-up; a call to function mcuxClRsa_verify using mode mcuxClRsa_Mode_Verify_Pss_Sha2_256; a session clean-up
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRsa_verify_pssverify_sha2_256_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Create session handle to be used by verify function */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session,
                                                 MCUXCLRSA_VERIFY_PSSVERIFY_WACPU_SIZE,
                                                 MCUXCLRSA_VERIFY_2048_WAPKC_SIZE);

    /* Initialize the PRNG */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result)) 
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Create key struct of type MCUXCLRSA_KEY_PUBLIC */
    const mcuxClRsa_KeyEntry_t Mod1 = {
                       .pKeyEntryData = (uint8_t *)modulus,
                       .keyEntryLength = RSA_KEY_BYTE_LENGTH };

    const mcuxClRsa_KeyEntry_t Exp1 = {
                       .pKeyEntryData = (uint8_t *)exponent,
                       .keyEntryLength = RSA_PUBLIC_EXP_BYTE_LENGTH };

    const mcuxClRsa_Key public_key = {
                       .keytype = MCUXCLRSA_KEY_PUBLIC,
                       .pMod1 = (mcuxClRsa_KeyEntry_t *)&Mod1,
                       .pMod2 = NULL,
                       .pQInv = NULL,
                       .pExp1 = (mcuxClRsa_KeyEntry_t *)&Exp1,
                       .pExp2 = NULL,
                       .pExp3 = NULL };

    /**************************************************************************/
    /* RSA verification call                                                  */
    /**************************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClRsa_verify(
                /* mcuxClSession_Handle_t           pSession: */           session,
                /* const mcuxClRsa_Key * const      pKey: */               &public_key,
                /* mcuxCl_InputBuffer_t             pMessageOrDigest: */   (uint8_t *)message,
                /* const uint32_t                  messageLength: */      0u,
                /* mcuxCl_Buffer_t                  pSignature: */         (uint8_t *)signature,
                /* const mcuxClRsa_SignVerifyMode   pVerifyMode: */        (mcuxClRsa_SignVerifyMode_t *)&mcuxClRsa_Mode_Verify_Pss_Sha2_256,
                /* const uint32_t                  saltLength: */         RSA_PSS_SALT_LENGTH,
                /* uint32_t                        options: */            MCUXCLRSA_OPTION_MESSAGE_DIGEST,
                /* mcuxCl_Buffer_t                  pOutput: */            NULL));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_verify) != verify_token) || (MCUXCLRSA_STATUS_VERIFY_OK != verify_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Session clean-up                                                       */
    /**************************************************************************/

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(session))
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
