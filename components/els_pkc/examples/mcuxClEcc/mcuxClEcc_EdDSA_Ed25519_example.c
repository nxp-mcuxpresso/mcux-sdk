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
 * @file  mcuxClEcc_EdDSA_Ed25519_example.c
 * @brief Example for the mcuxClEcc component
 *
 * @example mcuxClEcc_EdDSA_Ed25519_example.c
 * @brief   Example for the mcuxClEcc component EdDsa related functions
 */

#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClRandomModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_RNG_Helper.h>

#include <mcuxClExample_ELS_Helper.h>

static const uint8_t digest[] = {
  0xC4u, 0x93u, 0xCFu, 0x6Bu, 0xE5u, 0x11u, 0x35u, 0x22u,
  0x1Au, 0x3Fu, 0x5Cu, 0x7Bu, 0xCFu, 0xF4u, 0x6Du, 0xC6u,
  0x10u, 0x77u, 0x6Eu, 0x2Cu, 0x04u, 0xA3u, 0xB9u, 0x9Du,
  0x39u, 0x3Bu, 0x4Bu, 0xEEu, 0xD5u, 0xDDu, 0x88u, 0x86u,
};

#define MAX_CPUWA_SIZE MCUXCLEXAMPLE_MAX(MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE,\
                       MCUXCLEXAMPLE_MAX(MCUXCLRANDOMMODES_INIT_WACPU_SIZE,\
                       MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WACPU_SIZE,   \
                       MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WACPU_SIZE, \
                                          MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WACPU_SIZE))))
#define MAX_PKCWA_SIZE MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WAPKC_SIZE,   \
                       MCUXCLEXAMPLE_MAX(MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WAPKC_SIZE, \
                                          MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WAPKC_SIZE))
                                         
MCUXCLEXAMPLE_FUNCTION(mcuxClEcc_EdDSA_Ed25519_example)
{
  /**************************************************************************/
  /* Preparation                                                            */
  /**************************************************************************/

  /* Initialize ELS, Enable the ELS */
  if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Setup one session to be used by all functions called */
  mcuxClSession_Descriptor_t session;
  /* Allocate and initialize session with pkcWA on the beginning of PKC RAM */
  MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(&session, MAX_CPUWA_SIZE, MAX_PKCWA_SIZE);

  /* Initialize the RNG context and Initialize the PRNG */
  MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_RNG(&session, 0u, mcuxClRandomModes_Mode_ELS_Drbg);

  /* Prepare buffers for generated data */
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

  /**************************************************************************/
  /* Key pair generation for EdDSA on Ed25519                               */
  /**************************************************************************/

  /* Call mcuxClEcc_EdDSA_GenerateKeyPair to derive the public key from the private one. */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygen_result, keygen_token, mcuxClEcc_EdDSA_GenerateKeyPair(
  /*  mcuxClSession_Handle_t pSession                          */ &session,
  /*  const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode  */ &mcuxClEcc_EdDsa_GeneratePrivKeyDescriptor,
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

  uint8_t signature[MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE] = {0};
  uint32_t signatureSize = 0u;

  /* Call mcuxClEcc_EdDSA_GenerateSignature to generate the signature. */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(sign_result, sign_token, mcuxClEcc_EdDSA_GenerateSignature(
  /*  mcuxClSession_Handle_t pSession                           */ &session,
  /*  mcuxClKey_Handle_t key                                    */ privKey,
  /*  const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode */ &mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor,
  /*  const uint8_t *pIn                                       */ digest,
  /*  uint32_t inSize                                          */ sizeof(digest),
  /*  uint8_t *pSignature                                      */ signature,
  /*  uint32_t *const pSignatureSize                           */ &signatureSize));

  if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateSignature) != sign_token)
      || (MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE != signatureSize)
      || (MCUXCLECC_STATUS_OK != sign_result))
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }
  MCUX_CSSL_FP_FUNCTION_CALL_END();

  if(MCUXCLECC_EDDSA_ED25519_SIZE_SIGNATURE != signatureSize)
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }
  
  /**************************************************************************/
  /* Ed25519 signature verification                                         */
  /**************************************************************************/

  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClEcc_EdDSA_VerifySignature(
  /* mcuxClSession_Handle_t pSession                       */ &session,
  /* mcuxClKey_Handle_t key                                */ pubKey,
  /* const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t * */ &mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor,
  /* const uint8_t *pIn                                   */ digest,
  /* uint32_t inSize                                      */ sizeof(digest),
  /* const uint8_t *pSignature                            */ signature,
  /* uint32_t signatureSize                               */ signatureSize
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
