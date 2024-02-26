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
 * @file  mcuxClRsa_sign_NoEncode_example.c
 * @brief Example of using function mcuxClRsa_sign to perform the RSA signature generation primitive RSASP1
 *      (private exponentiation and NO padding) according to PKCS #1 v2.2, using a key in plain format.
 *
 * @example mcuxClRsa_sign_NoEncode_example.c
 * @brief Example of using function mcuxClRsa_sign to perform the RSA signature generation primitive RSASP1
 *      (private exponentiation and NO padding) according to PKCS #1 v2.2, using a key in plain format.
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
#define RSA_KEY_BIT_LENGTH (1024U)                    ///< The example uses a 1024-bit key
#define RSA_KEY_BYTE_LENGTH (RSA_KEY_BIT_LENGTH / 8U) ///< Converting the key-bitlength to bytelength


/**
 * @brief Example value for public RSA modulus N.
 */
static const uint8_t modulus[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
    0xd0u, 0xb7u, 0x50u, 0xc8u, 0x55u, 0x4bu, 0x64u, 0xc7u,
    0xa9u, 0xd3u, 0x4du, 0x06u, 0x8eu, 0x02u, 0x0fu, 0xb5u,
    0x2fu, 0xeau, 0x1bu, 0x39u, 0xc4u, 0x79u, 0x71u, 0xa3u,
    0x59u, 0xf0u, 0xeeu, 0xc5u, 0xdau, 0x04u, 0x37u, 0xeau,
    0x3fu, 0xc9u, 0x45u, 0x97u, 0xd8u, 0xdbu, 0xffu, 0x54u,
    0x44u, 0xf6u, 0xceu, 0x5au, 0x32u, 0x93u, 0xacu, 0x89u,
    0xb1u, 0xeeu, 0xbbu, 0x3fu, 0x71u, 0x2bu, 0x3au, 0xd6u,
    0xa0u, 0x63u, 0x86u, 0xe6u, 0x40u, 0x19u, 0x85u, 0xe1u,
    0x98u, 0x98u, 0x71u, 0x5bu, 0x1eu, 0xa3u, 0x2au, 0xc0u,
    0x34u, 0x56u, 0xfeu, 0x17u, 0x96u, 0xd3u, 0x1eu, 0xd4u,
    0xafu, 0x38u, 0x9fu, 0x4fu, 0x67u, 0x5cu, 0x23u, 0xc4u,
    0x21u, 0xa1u, 0x25u, 0x49u, 0x1eu, 0x74u, 0x0fu, 0xdau,
    0xc4u, 0x32u, 0x2eu, 0xc2u, 0xd4u, 0x6eu, 0xc9u, 0x45u,
    0xddu, 0xc3u, 0x49u, 0x22u, 0x7bu, 0x49u, 0x21u, 0x91u,
    0xc9u, 0x04u, 0x91u, 0x45u, 0xfbu, 0x2fu, 0x8cu, 0x29u,
    0x98u, 0xc4u, 0x86u, 0xa8u, 0x40u, 0xeau, 0xc4u, 0xd3u
 };


/**
 * @brief Example value for private RSA exponent d.
 */
static const uint8_t d[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
    0x27u, 0xb7u, 0x11u, 0x9au, 0x09u, 0xedu, 0xb8u, 0x27u,
    0xc1u, 0x34u, 0x18u, 0xc8u, 0x20u, 0xb5u, 0x22u, 0xa1u,
    0xeeu, 0x08u, 0xdeu, 0x0eu, 0x4bu, 0xb2u, 0x81u, 0x06u,
    0xdbu, 0x6bu, 0xb9u, 0x14u, 0x98u, 0xa3u, 0xb3u, 0x61u,
    0xabu, 0x29u, 0x3au, 0xf8u, 0x3fu, 0xefu, 0xcdu, 0xd8u,
    0xa6u, 0xbdu, 0x21u, 0x34u, 0xcau, 0x4au, 0xfau, 0xcfu,
    0x64u, 0xa0u, 0xe3u, 0x3cu, 0x01u, 0x4fu, 0x48u, 0xf4u,
    0x75u, 0x30u, 0xf8u, 0x84u, 0x7cu, 0xc9u, 0x18u, 0x5cu,
    0xbeu, 0xdeu, 0xc0u, 0xd9u, 0x23u, 0x8cu, 0x8fu, 0x1du,
    0x54u, 0x98u, 0xf7u, 0x1cu, 0x7cu, 0x0cu, 0xffu, 0x48u,
    0xdcu, 0x21u, 0x34u, 0x21u, 0x74u, 0x2eu, 0x34u, 0x35u,
    0x0cu, 0xa9u, 0x40u, 0x07u, 0x75u, 0x3cu, 0xc0u, 0xe5u,
    0xa7u, 0x83u, 0x26u, 0x4cu, 0xf4u, 0x9fu, 0xf6u, 0x44u,
    0xffu, 0xeau, 0x94u, 0x25u, 0x3cu, 0xfeu, 0x86u, 0x85u,
    0x9au, 0xcdu, 0x2au, 0x22u, 0x76u, 0xcau, 0x4eu, 0x72u,
    0x15u, 0xf8u, 0xebu, 0xaau, 0x2fu, 0x18u, 0x8fu, 0x51u
 };

 /**
 * @brief Input message
 */
static const uint8_t message[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
    0x00u, 0x01u, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x30u, 0x31u, 0x30u,
    0x0du, 0x06u, 0x09u, 0x60u, 0x86u, 0x48u, 0x01u, 0x65u,
    0x03u, 0x04u, 0x02u, 0x01u, 0x05u, 0x00u, 0x04u, 0x20u,
    0x7cu, 0x50u, 0xbdu, 0xf5u, 0xafu, 0x92u, 0x3du, 0x43u,
    0x2cu, 0xefu, 0x56u, 0x84u, 0xfdu, 0xfau, 0x9du, 0xbau,
    0x18u, 0x9au, 0xaeu, 0x69u, 0x98u, 0x92u, 0xb9u, 0xa6u,
    0x86u, 0x3au, 0x35u, 0xeeu, 0xcfu, 0x54u, 0x6du, 0xecu
 };

 /**
 * @brief Expected signature
 */
static const uint8_t referenceSignature[RSA_KEY_BYTE_LENGTH] __attribute__ ((aligned (4))) = {
    0x02u, 0x3au, 0x8du, 0x88u, 0x87u, 0xd3u, 0x81u, 0x4fu,
    0xb6u, 0xceu, 0xb1u, 0x2cu, 0xf9u, 0x87u, 0x9cu, 0x49u,
    0xebu, 0xf2u, 0x16u, 0xd0u, 0x6cu, 0x32u, 0x2du, 0xa7u,
    0x72u, 0xb2u, 0xe5u, 0x1fu, 0x7au, 0x70u, 0xc1u, 0x30u,
    0x74u, 0x3au, 0xacu, 0xebu, 0x0cu, 0x81u, 0x01u, 0x6cu,
    0x55u, 0xe1u, 0x1cu, 0x7eu, 0x93u, 0x1fu, 0x1au, 0x28u,
    0xcau, 0xe9u, 0xe1u, 0x70u, 0xa9u, 0xf9u, 0x7bu, 0x2du,
    0xfcu, 0xc0u, 0xbfu, 0x3cu, 0x56u, 0xbdu, 0x8fu, 0xe1u,
    0xd3u, 0xa1u, 0xb4u, 0xe3u, 0xe5u, 0xd2u, 0xb2u, 0x51u,
    0x88u, 0xe9u, 0x9au, 0x90u, 0x19u, 0x33u, 0xb8u, 0xa6u,
    0xd4u, 0x55u, 0x3du, 0xcbu, 0xc3u, 0x0cu, 0xdbu, 0x27u,
    0xdcu, 0x86u, 0x55u, 0xe2u, 0x0du, 0x1du, 0x59u, 0xc5u,
    0xb4u, 0x23u, 0xcbu, 0xaau, 0xcau, 0x1bu, 0x7bu, 0x8au,
    0xe7u, 0x30u, 0x64u, 0xc8u, 0x42u, 0x28u, 0xd9u, 0xd3u,
    0xdbu, 0x6au, 0x54u, 0x7fu, 0x21u, 0x95u, 0x12u, 0x58u,
    0xf3u, 0xc9u, 0x98u, 0x54u, 0x1du, 0x6au, 0x15u, 0x96u
 };



/** Performs a session set-up; a call to function mcuxClRsa_sign using mode mcuxClRsa_Mode_Verify_NoVerify; a session clean-up
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRsa_sign_NoEncode_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Create session handle to be used by mcuxClRsa_sign */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session,
                                                 MCUXCLRSA_SIGN_PLAIN_NOENCODE_1024_WACPU_SIZE,
                                                 MCUXCLRSA_SIGN_PLAIN_1024_WAPKC_SIZE);

    /* Initialize the PRNG */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result)) 
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Create key struct of type MCUXCLRSA_KEY_PRIVATEPLAIN */
    const mcuxClRsa_KeyEntry_t Mod1 = {
                       .pKeyEntryData = (uint8_t *)modulus,
                       .keyEntryLength = RSA_KEY_BYTE_LENGTH };

    const mcuxClRsa_KeyEntry_t Exp1 = {
                       .pKeyEntryData = (uint8_t *)d,
                       .keyEntryLength = sizeof(d) };

    const mcuxClRsa_Key private_key = {
                                     .keytype = MCUXCLRSA_KEY_PRIVATEPLAIN,
                                     .pMod1 = (mcuxClRsa_KeyEntry_t *)&Mod1,
                                     .pMod2 = NULL,
                                     .pQInv = NULL,
                                     .pExp1 = (mcuxClRsa_KeyEntry_t *)&Exp1,
                                     .pExp2 = NULL,
                                     .pExp3 = NULL };

    /* Prepare buffer to store the result */
    uint8_t signature[RSA_KEY_BYTE_LENGTH];

    /**************************************************************************/
    /* RSA signature generation call                                          */
    /**************************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(sign_status, sign_token, mcuxClRsa_sign(
                /* mcuxClSession_Handle_t           pSession: */           session,
                /* const mcuxClRsa_Key * const      pKey: */               &private_key,
                /* mcuxCl_InputBuffer_t             pMessageOrDigest: */   message,
                /* const uint32_t                  messageLength: */      RSA_KEY_BYTE_LENGTH,
                /* const mcuxClRsa_SignVerifyMode   pPaddingMode: */       (mcuxClRsa_SignVerifyMode_t *)&mcuxClRsa_Mode_Sign_NoEncode,
                /* const uint32_t                  saltLength: */         0u,
                /* uint32_t                        options: */            0u,
                /* mcuxCl_Buffer_t                  pSignature: */         signature));

    if(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_sign) != sign_token || MCUXCLRSA_STATUS_SIGN_OK != sign_status)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Verification of the result                                             */
    /**************************************************************************/
    for(size_t i = 0U; i < RSA_KEY_BYTE_LENGTH; i++)
    {
        if(referenceSignature[i] != signature[i])
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

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
