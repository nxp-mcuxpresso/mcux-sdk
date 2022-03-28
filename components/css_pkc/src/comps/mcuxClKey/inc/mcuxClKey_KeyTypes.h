/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClKey_KeyTypes.h
 * @brief Definition of supported key types in mcuxClKey component
 */

#ifndef MCUXCLKEY_KEYTYPES_H_
#define MCUXCLKEY_KEYTYPES_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup mcuxClKey_KeyTypes mcuxClKey_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**********************************************
 * CONSTANTS
 **********************************************/
/* None */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @brief Type for algorithm based key id.
 */
typedef uint16_t mcuxClKey_AlgorithmId_t;

/**
 * @brief Type for algorithm based key size.
 */
typedef uint16_t mcuxClKey_Size_t;

/**
 * @brief Type to map algorithm id and size.
 */
typedef struct mcuxClKey_Type {
  mcuxClKey_AlgorithmId_t    algoId; ///< the identifier of the algorithm, refer to #mcuxClKey_KeyTypes
  mcuxClKey_Size_t           size;   ///< the key size for the key type, refer to #mcuxClKey_KeySize
  void *                    info;   ///< pointer to additional information for this key type (e.g. curve parameters, public exponent)
} mcuxClKey_Type_t;


/* Define algorithm IDs */
/**
 * @defgroup mcuxClKey_KeyTypes mcuxClKey_KeyTypes
 * @brief Defines all key types of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

#define MCUXCLKEY_ALGO_ID_AES            0x0F01u ///< AES key
#define MCUXCLKEY_ALGO_ID_RSA            0x0E02u ///< RSA key
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP   0x0D03u ///< ECC key using Short Weierstrass Curve over GF(p)
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GF2M  0x0C04u ///< ECC key using Short Weierstrass Curve over GF(2^m)
#define MCUXCLKEY_ALGO_ID_ECC_MONT_GFP   0x0B05u ///< ECC key using Montgomery Curve over GF(p)
#define MCUXCLKEY_ALGO_ID_ECC_TWED_GFP   0x0A06u ///< ECC key using Twisted Edwards Curve over GF(p)
#define MCUXCLKEY_ALGO_ID_ALGO_MASK      0x0FFFu ///< Mask for Algorithm

#define MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY  0x0000u ///< Symmetric key
#define MCUXCLKEY_ALGO_ID_PUBLIC_KEY     0x8000u ///< Public key
#define MCUXCLKEY_ALGO_ID_PRIVATE_KEY    0x4000u ///< Private key
#define MCUXCLKEY_ALGO_ID_KEY_PAIR       0xC000u ///< Key pair
#define MCUXCLKEY_ALGO_ID_USAGE_MASK     0xC000u ///< Mask for Key Usage

/**
 * @}
 */

/* Define key sizes */
/**
 * @defgroup mcuxClKey_KeySize mcuxClKey_KeySize
 * @brief Defines all key sizes of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

#define MCUXCLKEY_SIZE_NOTUSED           0u      ///< key length field is not used (e.g. ECC keys)
#define MCUXCLKEY_SIZE_128               16u     ///< 128 bit key
#define MCUXCLKEY_SIZE_192               24u     ///< 192 bit key
#define MCUXCLKEY_SIZE_256               32u     ///< 256 bit key
#define MCUXCLKEY_SIZE_512               64u     ///< 512 bit key
#define MCUXCLKEY_SIZE_2048              2048u   ///< 2048 bit key
#define MCUXCLKEY_SIZE_3072              3072u   ///< 3072 bit key
#define MCUXCLKEY_SIZE_4096              4096u   ///< 4096 bit key

/**
 * @}
 */

/**
 * @brief Key type pointer for AES-128 based keys.
 */
extern const mcuxClKey_Type_t mcuxKey_keyType_Aes128;

/**
 * @brief Key type pointer for AES-192 based keys.
 */
extern const mcuxClKey_Type_t mcuxKey_keyType_Aes192;

/**
 * @brief Key type pointer for AES-256 based keys.
 */
extern const mcuxClKey_Type_t mcuxKey_keyType_Aes256;

/**
 * @def MCUXCLKEY_WA_SIZE_MAX
 * @brief Define the max workarea size required for this component
 */
#define MCUXCLKEY_WA_SIZE_MAX 0U

/**********************************************
 * FUNCTIONS
 **********************************************/
/* None */

/**
 * @}
 */ /* mcuxClKey_KeyTypes */

#endif /* MCUXCLKEY_KEYTYPES_H_ */
