/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/** @file  mcuxClRsa_ModeConstructors.c
 *  @brief mcuxClRsa: implementation of RSA mode constructors for Signature and Cipher components
 */


#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
#include <mcuxClCipher.h>
#include <internal/mcuxClCipher_Internal.h>
#endif /* defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT) */

#include <mcuxClPkc_Functions.h>

#include <internal/mcuxClRsa_Internal_Macros.h>


#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxClRsa.h>
#include <mcuxClRsa_ModeConstructors.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <mcuxCsslAnalysis.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()

#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
/* Cipher crypt mode function for RSA encrypt operation */
static const mcuxClRsa_Cipher_ModeFunctions_t mcuxClRsa_Cipher_ModeFunctions_Rsa_encrypt = {
  .crypt = mcuxClRsa_Util_encrypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_Util_encrypt)
};
 
/* Cipher crypt mode function for RSA decrypt operation */
static const mcuxClRsa_Cipher_ModeFunctions_t mcuxClRsa_Cipher_ModeFunctions_Rsa_decrypt  = {
  .crypt = mcuxClRsa_Util_decrypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_Util_decrypt)
};

#ifdef MCUXCL_FEATURE_RSA_RSAES_OAEP
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_CipherModeConstructor_RSAES_OAEP_Encrypt)
void mcuxClRsa_CipherModeConstructor_RSAES_OAEP_Encrypt(
  mcuxClCipher_ModeDescriptor_t * pCipherMode,
  mcuxClHash_Algo_t hashAlgorithm
)
{
  /* Create RSA algorithm descriptor after the cipher mode.
   * It is assumed that sufficient space was allocated by users, with the macro MCUXCLRSA_CIPHER_MODE_SIZE */
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Cipher_AlgorithmDescriptor_t *pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) ((uint8_t*)pCipherMode + sizeof(mcuxClCipher_ModeDescriptor_t));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  /* Fill cipher algorithm parameters for RSA with OAEP encoding */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the cipher algorithm parameters.")
  pAlgorithmDescriptor->pHashAlgo = (mcuxClHash_AlgorithmDescriptor_t *)hashAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  pAlgorithmDescriptor->pCryptMode = mcuxClRsa_oaepEncode;
  pAlgorithmDescriptor->crypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_oaepEncode);

  /* Fill cipher mode parameters for RSA */
  pCipherMode->pModeFunctions = (const void *) &mcuxClRsa_Cipher_ModeFunctions_Rsa_encrypt;
  pCipherMode->pAlgorithm = pAlgorithmDescriptor;
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_CipherModeConstructor_RSAES_OAEP_Decrypt)
void mcuxClRsa_CipherModeConstructor_RSAES_OAEP_Decrypt(
  mcuxClCipher_ModeDescriptor_t * pCipherMode,
  mcuxClHash_Algo_t hashAlgorithm
)
{
  /* Create RSA algorithm descriptor after the cipher mode.
   * It is assumed that sufficient space was allocated by users, with the macro MCUXCLRSA_CIPHER_MODE_SIZE */
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Cipher_AlgorithmDescriptor_t *pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) ((uint8_t*)pCipherMode + sizeof(mcuxClCipher_ModeDescriptor_t));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  /* Fill cipher algorithm parameters for RSA with OAEP decoding */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the cipher algorithm parameters.")
  pAlgorithmDescriptor->pHashAlgo = (mcuxClHash_AlgorithmDescriptor_t *)hashAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  pAlgorithmDescriptor->pCryptMode = mcuxClRsa_oaepDecode;
  pAlgorithmDescriptor->crypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_oaepDecode);

  /* Fill cipher mode parameters for RSA */
  pCipherMode->pModeFunctions = (const void *) &mcuxClRsa_Cipher_ModeFunctions_Rsa_decrypt;
  pCipherMode->pAlgorithm = pAlgorithmDescriptor;
}
#endif /* MCUXCL_FEATURE_RSA_RSAES_OAEP */

#ifdef MCUXCL_FEATURE_RSA_RSAES_PKCS1v15
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_CipherModeConstructor_RSAES_PKCS1_v1_5_Encrypt)
void mcuxClRsa_CipherModeConstructor_RSAES_PKCS1_v1_5_Encrypt(
  mcuxClCipher_ModeDescriptor_t * pCipherMode
)
{
  /* Create RSA algorithm descriptor after the cipher mode.
   * It is assumed that sufficient space was allocated by users, with the macro MCUXCLRSA_CIPHER_MODE_SIZE */
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Cipher_AlgorithmDescriptor_t *pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) ((uint8_t*)pCipherMode + sizeof(mcuxClCipher_ModeDescriptor_t));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  /* Fill cipher algorithm parameters for RSA with PKCS#1 v1.5 encoding */
  pAlgorithmDescriptor->pHashAlgo = NULL; /* No hash algorithm is used for RSAES-PKCS1-v1_5 */
  pAlgorithmDescriptor->pCryptMode = mcuxClRsa_pkcs1v15Encode_encrypt;
  pAlgorithmDescriptor->crypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode_encrypt);

  /* Fill cipher mode parameters for RSA */
  pCipherMode->pModeFunctions = (const void *) &mcuxClRsa_Cipher_ModeFunctions_Rsa_encrypt;
  pCipherMode->pAlgorithm = pAlgorithmDescriptor;
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_CipherModeConstructor_RSAES_PKCS1_v1_5_Decrypt)
void mcuxClRsa_CipherModeConstructor_RSAES_PKCS1_v1_5_Decrypt(
  mcuxClCipher_ModeDescriptor_t * pCipherMode
)
{
  /* Create RSA algorithm descriptor after the cipher mode.
   * It is assumed that sufficient space was allocated by users, with the macro MCUXCLRSA_CIPHER_MODE_SIZE */
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Cipher_AlgorithmDescriptor_t *pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) ((uint8_t*)pCipherMode + sizeof(mcuxClCipher_ModeDescriptor_t));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  /* Fill cipher algorithm parameters for RSA with PKCS#1 v1.5 encoding */
  pAlgorithmDescriptor->pHashAlgo = NULL; /* No hash algorithm is used for RSAES-PKCS1-v1_5 */
  pAlgorithmDescriptor->pCryptMode = mcuxClRsa_pkcs1v15Decode_decrypt;
  pAlgorithmDescriptor->crypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Decode_decrypt);

  /* Fill cipher mode parameters for RSA */
  pCipherMode->pModeFunctions = (const void *) &mcuxClRsa_Cipher_ModeFunctions_Rsa_decrypt;
  pCipherMode->pAlgorithm = pAlgorithmDescriptor;
}
#endif /* MCUXCL_FEATURE_RSA_RSAES_PKCS1v15 */

#endif /* MCUXCL_FEATURE_CIPHER_CRYPT */




MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_Public_KeyType_ModeConstructor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_Public_KeyType_ModeConstructor(
  mcuxClKey_TypeDescriptor_t * pKeyType,
  mcuxClKey_Size_t keySize
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_Public_KeyType_ModeConstructor);
  mcuxClRsa_Status_t ret = MCUXCLRSA_STATUS_INVALID_INPUT;
  //The supported bit-size of the key range from 512 to max (4096 or 8192) in multiples of 8
  if((keySize >= 512u/8u) && (keySize <= MCUXCLRSA_MAX_MODLEN))
  {
    pKeyType->algoId = MCUXCLRSA_KEYTYPE_INTERNAL_PUBLIC;
    pKeyType->size = keySize * 8u; //For RSA the size needs to be in bits
    pKeyType->info = NULL;
    ret = MCUXCLRSA_STATUS_OK;
  }
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_Public_KeyType_ModeConstructor, ret, MCUXCLRSA_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_PrivatePlain_KeyType_ModeConstructor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_PrivatePlain_KeyType_ModeConstructor(
  mcuxClKey_TypeDescriptor_t * pKeyType,
  mcuxClKey_Size_t keySize
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_PrivatePlain_KeyType_ModeConstructor);
  mcuxClRsa_Status_t ret = MCUXCLRSA_STATUS_INVALID_INPUT;
  //The supported bit-size of the key range from 512 to max (4096 or 8192) in multiples of 8
  if((keySize >= 512u/8u) && (keySize <= MCUXCLRSA_MAX_MODLEN))
  {
    pKeyType->algoId = MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATEPLAIN;
    pKeyType->size = keySize * 8u; //For RSA the size needs to be in bits
    pKeyType->info = NULL;
    ret = MCUXCLRSA_STATUS_OK;
  }
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_PrivatePlain_KeyType_ModeConstructor, ret, MCUXCLRSA_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_PrivateCRT_KeyType_ModeConstructor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_PrivateCRT_KeyType_ModeConstructor(
  mcuxClKey_TypeDescriptor_t * pKeyType,
  mcuxClKey_Size_t keySize
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_PrivateCRT_KeyType_ModeConstructor);
  mcuxClRsa_Status_t ret = MCUXCLRSA_STATUS_INVALID_INPUT;
  //The supported bit-size of the key range from 512 to max (4096 or 8192) in multiples of 8
  if((keySize >= 512u/8u) && (keySize <= MCUXCLRSA_MAX_MODLEN))
  {
    pKeyType->algoId = MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRT;
    pKeyType->size = keySize * 8u; //For RSA the size needs to be in bits
    pKeyType->info = NULL;
    ret = MCUXCLRSA_STATUS_OK;
  }
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_PrivateCRT_KeyType_ModeConstructor, ret, MCUXCLRSA_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_PrivateCRT_DFA_KeyType_ModeConstructor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_PrivateCRT_DFA_KeyType_ModeConstructor(
  mcuxClKey_TypeDescriptor_t * pKeyType,
  mcuxClKey_Size_t keySize
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_PrivateCRT_DFA_KeyType_ModeConstructor);
  mcuxClRsa_Status_t ret = MCUXCLRSA_STATUS_INVALID_INPUT;
  //The supported bit-size of the key range from 512 to max (4096 or 8192) in multiples of 8
  if((keySize >= 512u/8u) && (keySize <= MCUXCLRSA_MAX_MODLEN))
  {
    pKeyType->algoId = MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRTDFA;
    pKeyType->size = keySize * 8u; //For RSA the size needs to be in bits
    pKeyType->info = NULL;
    ret = MCUXCLRSA_STATUS_OK;
  }
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_PrivateCRT_DFA_KeyType_ModeConstructor, ret, MCUXCLRSA_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
