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
 * @file  mcuxClRsa_KeyTypes.h
 * @brief Definition of supported key types in mcuxClRsa component, see also @ref mcuxClKey component
 */

#ifndef MCUXCLRSA_KEYTYPES_H_
#define MCUXCLRSA_KEYTYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <stdint.h>
#include <stdbool.h>

#include <mcuxClKey_Types.h>
#include <mcuxClRsa_Types.h>

#include <mcuxCsslAnalysis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClRsa_KeyTypes_Descriptors Key Type Descriptors
 * @brief Definition of supported key types in @ref mcuxClRsa component, see also @ref mcuxClKey component
 * @ingroup mcuxClRsa_Descriptors
 * @{
 */

/**********************************************
 * KEY TYPE DEFS
 **********************************************/

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")
#if defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT)

/**
 * @defgroup mcuxClRsa_KeyTypes_Public_Structures RSA public key type structures
 * @brief Defines key type structures for RSA public keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_Public_1024; ///< Key type structure for RSA public key and key size 1024 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_Public_2048; ///< Key type structure for RSA public key and key size 2048 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_Public_3072; ///< Key type structure for RSA public key and key size 3072 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_Public_4096; ///< Key type structure for RSA public key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_Public_Structures */

/**
 * @defgroup mcuxClRsa_KeyTypes_Public_Pointers RSA public key type pointers
 * @brief Defines key type pointers for public RSA keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_Public_1024 = &mcuxClKey_TypeDescriptor_Rsa_Public_1024; ///< Key type pointer for RSA public key and key size 1024 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_Public_2048 = &mcuxClKey_TypeDescriptor_Rsa_Public_2048; ///< Key type pointer for RSA public key and key size 2048 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_Public_3072 = &mcuxClKey_TypeDescriptor_Rsa_Public_3072; ///< Key type pointer for RSA public key and key size 3072 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_Public_4096 = &mcuxClKey_TypeDescriptor_Rsa_Public_4096; ///< Key type pointer for RSA public key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_Public_Pointers */
#endif /* defined(MCUXCL_FEATURE_SIGNATURE_RSA_VERIFY) || defined(MCUXCL_FEATURE_CIPHER_RSA_ENCRYPT) || defined(MCUXCL_FEATURE_KEY_GENERATION_RSA) */

#if defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT)

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivatePlain_Structures RSA private plain key type structures
 * @brief Defines key type structures for RSA private plain keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_1024; ///< Key type structure for RSA private plain key and key size 1024 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_2048; ///< Key type structure for RSA private plain key and key size 2048 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_3072; ///< Key type structure for RSA private plain key and key size 3072 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_4096; ///< Key type structure for RSA private plain key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivatePlain_Structures */

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivatePlain_Pointers RSA private plain key type pointers
 * @brief Defines key type pointers for private plain RSA keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivatePlain_1024 = &mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_1024; ///< Key type pointer for RSA private plain key and key size 1024 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivatePlain_2048 = &mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_2048; ///< Key type pointer for RSA private plain key and key size 2048 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivatePlain_3072 = &mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_3072; ///< Key type pointer for RSA private plain key and key size 3072 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivatePlain_4096 = &mcuxClKey_TypeDescriptor_Rsa_PrivatePlain_4096; ///< Key type pointer for RSA private plain key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivatePlain_Pointers */

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivateCrt_Structures RSA private CRT key type structures
 * @brief Defines key type structures for RSA private CRT keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_1024; ///< Key type structure for RSA private CRT key and key size 1024 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_2048; ///< Key type structure for RSA private CRT key and key size 2048 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_3072; ///< Key type structure for RSA private CRT key and key size 3072 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_4096; ///< Key type structure for RSA private CRT key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivateCrt_Structures */

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivateCRT_Pointers RSA private CRT key type pointers
 * @brief Defines key type pointers for private CRT RSA keys of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_1024 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_1024; ///< Key type pointer for RSA private CRT key and key size 1024 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_2048 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_2048; ///< Key type pointer for RSA private CRT key and key size 2048 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_3072 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_3072; ///< Key type pointer for RSA private CRT key and key size 3072 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_4096 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_4096; ///< Key type pointer for RSA private CRT key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivateCrt_Pointers */

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivateCrt_DFA_Structures RSA private CRT_DFA key type structures with
 * @brief Defines key type structures for RSA private CRT keys with DFA protection enabled of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_1024; ///< Key type structure for RSA private CRT_DFA key and key size 1024 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_2048; ///< Key type structure for RSA private CRT_DFA key and key size 2048 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_3072; ///< Key type structure for RSA private CRT_DFA key and key size 3072 bits.
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_4096; ///< Key type structure for RSA private CRT_DFA key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivateCrt_DFA_Structures */

/**
 * @defgroup mcuxClRsa_KeyTypes_PrivateCrt_DFA_Pointers RSA private CRT_DFA key type pointers with
 * @brief Defines key type pointers for RSA private CRT keys with DFA protection enabled of @ref mcuxClRsa, see @ref mcuxClKey.
 * @ingroup mcuxClRsa_KeyTypes_Descriptors
 * @{
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_DFA_1024 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_1024; ///< Key type pointer for RSA private CRT_DFA key and key size 1024 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_DFA_2048 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_2048; ///< Key type pointer for RSA private CRT_DFA key and key size 2048 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_DFA_3072 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_3072; ///< Key type pointer for RSA private CRT_DFA key and key size 3072 bits.
static const mcuxClKey_Type_t mcuxClKey_Type_Rsa_PrivateCRT_DFA_4096 = &mcuxClKey_TypeDescriptor_Rsa_PrivateCRT_DFA_4096; ///< Key type pointer for RSA private CRT_DFA key and key size 4096 bits.
/**
 * @}
 */ /* mcuxClRsa_KeyTypes_PrivateCrt_DFA_Pointers */

#endif /* defined(MCUXCL_FEATURE_SIGNATURE_RSA_SIGN) || defined(MCUXCL_FEATURE_CIPHER_RSA_DECRYPT) || defined(MCUXCL_FEATURE_KEY_GENERATION_RSA) */

MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()
/**
 * @}
 */ /* mcuxClRsa_KeyTypes */

/**
 * @defgroup mcuxClRsa_KeyData Rsa Key Types
 * @brief Struct to supported key data for @ref mcuxClRsa, see @ref mcuxClKey
 * @ingroup mcuxClRsa_Types
 * @{
 */
/**********************************************
 * MACROS AND DEFINITIONS TO SETUP RSA KEY
 **********************************************/

/**
 * @brief Structure type for Rsa plain key data.
 */
typedef struct
{
  mcuxClRsa_KeyEntry_t modulus;    ///< Key entry for the modulus
  mcuxClRsa_KeyEntry_t exponent;   ///< Key entry for the exponent - it can be the public or the private exponent, depending on the key type
}mcuxClRsa_KeyData_Plain_t;

/**
 * @brief Structure type for Rsa CRT key data.
 */
typedef struct
{
  mcuxClRsa_KeyEntry_t p;     ///< Key entry for the prime factor P
  mcuxClRsa_KeyEntry_t q;     ///< Key entry for the prime factor Q
  mcuxClRsa_KeyEntry_t qInv;  ///< Key entry for the QInv = (1 / (Q % P))
  mcuxClRsa_KeyEntry_t dp;    ///< Key entry for the exponent DP = D % (P-1)
  mcuxClRsa_KeyEntry_t dq;    ///< Key entry for the exponent DQ = D % (Q-1)
  mcuxClRsa_KeyEntry_t e;     ///< Key entry for the public exponent E - it should be specified for a key type Rsa_PrivateCRT_DFA, and can be ignored otherwise
}mcuxClRsa_KeyData_Crt_t;

// TODO CLNS-6135: remove those definitions
#define MCUXCLRSA_KEYSTRUCT_PLAIN_SIZE (sizeof(mcuxClRsa_KeyData_Plain_t)) ///< Size of mcuxClRsa_KeyData_Plain_t
#define MCUXCLRSA_KEYSTRUCT_CRT_SIZE (sizeof(mcuxClRsa_KeyData_Crt_t)) ///< Size of mcuxClRsa_KeyData_Crt_t

/**
 * @}
 */ /* mcuxClRsa_KeyTypes */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_KEYTYPES_H_ */
