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
 * @file  mcuxClRsa_Internal_Types.h
 * @brief Internal type definitions for the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_TYPES_H_
#define MCUXCLRSA_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClRsa_Types.h>
#include <mcuxClHash_Types.h>
#include <mcuxClBuffer.h>

#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
#include <mcuxClRsa_ModeConstructors.h>
#endif /* defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT) || defined(MCUXCL_FEATURE_SIGNATURE_RSA_SIGN) || defined(MCUXCL_FEATURE_SIGNATURE_RSA_VERIFY) || defined(MCUXCL_FEATURE_KEY_GENERATION_RSA) */

#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
#include <internal/mcuxClCipher_Internal_Types.h>
#endif /* MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT || MCUXCL_FEATURE_CIPHER_RSA_DECRYPT */

#ifdef __cplusplus
extern "C" {
#endif

 /**
 * @defgroup mcuxClRsa_Internal_Macros mcuxClRsa_Internal_Macros
 * @brief Defines all internal macros of the @ref mcuxClRsa component
 * @ingroup mcuxClRsa
 * @{
 */

/**
 * @defgroup MCUXCLRSA_STATUS_INTERNAL_ MCUXCLRSA_STATUS_INTERNAL_
 * @brief Internal return code definitions
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK    ((mcuxClRsa_Status_t) 0xB2B25A5Au )  ///< RSA key operation successful
#define MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK   ((mcuxClRsa_Status_t) 0xB2B29A9Au )  ///< RSA encoding operation successful
#define MCUXCLRSA_STATUS_INTERNAL_MGF_OK      ((mcuxClRsa_Status_t) 0xB2B2AAAAu )  ///< RSA mask generation function operation successful
#define MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_CMP_FAILED      ((mcuxClRsa_Status_t) 0xB2B2ABABu )  ///< RSA key generation test failed at comparison stage
#define MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_GCDA0_FAILED    ((mcuxClRsa_Status_t) 0xB2B2ADADu )  ///< RSA key generation test failed at the stage of GCD with A0
#define MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_GCDE_FAILED     ((mcuxClRsa_Status_t) 0xB2B2AEAEu )  ///< RSA key generation test failed at the stage of GCD with E
#define MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_MRT_FAILED      ((mcuxClRsa_Status_t) 0xB2B2AFAFu )  ///< RSA key generation test failed at the stage of Miller Rabin Test

/** @} */

/**
 * @}
 */

/***********************************************************
 *  TYPES RELATED TO PADDING FUNCTIONALITY
 **********************************************************/

 /**
 * @brief Function type for padding engine
 *
 * Generic function pointer to padding function declarations
 *
 * @param[in]  pSession                Pointer to session.
 * @param[in]  pInput                  Buffer that contains the input data.
 * @param[in]  inputLength             Length of input in bytes.
 * @param[in]  pVerificationInput      Pointer to encoded message that is verified.
 * @param[in]  pHashAlgo               Pointer to hash algorithm used in padding function.
 * @param[in]  pLabel                  Buffer that contains the label in case of OAEP padding.
 * @param[in]  saltlabelLength         Length of salt in case of PSS padding, or label in case of OAEP padding.
 * @param[in]  keyBitLength            Bitlength of public modulus n.
 * @param[in]  options                 Options.
 * @param[out] pOutput                 Buffer that contains the output of the padding function.
 * @param[out] pOutLength              Length of output in bytes.
 *
 * @return Status of the padding operation
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClRsa_PadVerModeEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) (* mcuxClRsa_PadVerModeEngine_t)(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  uint8_t *                   pVerificationInput,
  mcuxClHash_Algo_t            pHashAlgo,
  mcuxCl_InputBuffer_t         pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength));


/**
 * @brief Structure type for RSA-specific padding modes, i.e. required information to execute a selected padding mode.
 */
struct mcuxClRsa_SignVerifyMode_t
{
  uint32_t                      EncodeVerify_FunId; ///< Flow protection function identifier of encoding or verify function.
  mcuxClHash_Algo_t              pHashAlgo1;         ///< Pointer to hashing functionality.
  mcuxClHash_Algo_t              pHashAlgo2;         ///< RFU
  mcuxClRsa_PadVerModeEngine_t   pPaddingFunction;   ///< Pointer to padding functionality.
};

#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
/**
 * @brief RSA-specific key types
 */
#define MCUXCLRSA_KEYTYPE_INTERNAL_PUBLIC         (MCUXCLKEY_ALGO_ID_RSA + MCUXCLKEY_ALGO_ID_PUBLIC_KEY)
#define MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATEPLAIN   (MCUXCLKEY_ALGO_ID_RSA + MCUXCLKEY_ALGO_ID_PRIVATE_KEY)
#define MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRT     (MCUXCLKEY_ALGO_ID_RSA + MCUXCLKEY_ALGO_ID_PRIVATE_KEY_CRT)
#define MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRTDFA  (MCUXCLKEY_ALGO_ID_RSA + MCUXCLKEY_ALGO_ID_PRIVATE_KEY_CRT_DFA)
#endif /*  defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT) || defined(MCUXCL_FEATURE_SIGNATURE_RSA_SIGN) || defined(MCUXCL_FEATURE_SIGNATURE_RSA_VERIFY) || defined(MCUXCL_FEATURE_KEY_GENERATION_RSA) */


#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)
/**
 * @brief RSA-specific algorithm descriptor structure for encryption/decryption with @ref mcuxClCipher
 */
typedef struct
{
  mcuxClHash_AlgorithmDescriptor_t *  pHashAlgo;   ///< Pointer to hashing functionality.
  mcuxClRsa_PadVerModeEngine_t   pCryptMode;       ///< Pointer to padding functionality for the crypt mode.
  uint32_t                      crypt_FunId;      ///< Flow protection function identifier of padding.
} mcuxClRsa_Cipher_AlgorithmDescriptor_t;

/**
 * @brief This structure captures all the information related to the functions
 * of the Cipher interfaces.
 */
typedef struct mcuxClRsa_Cipher_ModeFunctions
{
  MCUXCLCIPHER_ENCRYPT_DECRYPT_ONESHOT_MODEFUNCTIONS // used with MCUXCL_FEATURE_CIPHER_ENCRYPT_DECRYPT
  MCUXCLCIPHER_CRYPT_MODEFUNCTIONS                   // used with MCUXCL_FEATURE_CIPHER_CRYPT
} mcuxClRsa_Cipher_ModeFunctions_t;
#endif /* MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT || MCUXCL_FEATURE_CIPHER_RSA_DECRYPT */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_TYPES_H_ */
