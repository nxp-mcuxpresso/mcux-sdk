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
 * @file  mcuxClKey_Constants.h
 * @brief Constants for the mcuxClKey component.
 */

#ifndef MCUXCLKEY_CONSTANTS_H_
#define MCUXCLKEY_CONSTANTS_H_

#include <mcuxCsslAnalysis.h>
#include <mcuxClConfig.h> // Exported features flags header

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClKey_Macros mcuxClKey_Macros
 * @brief Defines all macros of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */
/**
 * @defgroup MCUXCLKEY_STATUS_  MCUXCLKEY_STATUS_
 * @brief Return code definitions
 * @{
 */
#define MCUXCLKEY_STATUS_OK                   ((mcuxClKey_Status_t) 0x07772E03u)  ///< Key operation successful
#define MCUXCLKEY_STATUS_ERROR                ((mcuxClKey_Status_t) 0x07775330u)  ///< Error occured during Key operation
#define MCUXCLKEY_STATUS_FAILURE              ((mcuxClKey_Status_t) 0x07775334u)  ///< Failure during execution
#define MCUXCLKEY_STATUS_INVALID_INPUT        ((mcuxClKey_Status_t) 0x07775338u)  ///< Invalid input
#define MCUXCLKEY_STATUS_FAULT_ATTACK         ((mcuxClKey_Status_t) 0x0777F0F0u)  ///< Fault attack detected
#define MCUXCLKEY_STATUS_CRC_NOT_OK           ((mcuxClKey_Status_t) 0x077753FCu)  ///< CRC verification failed
#define MCUXCLKEY_STATUS_NOT_SUPPORTED        ((mcuxClKey_Status_t) 0x07775370u)  ///< Functionality not supported
/** @} */

/**
 * @defgroup MCUXCLKEY_LOADSTATUS_ MCUXCLKEY_LOADSTATUS_
 * @brief Load location options
 * @ingroup mcuxClKey_Macros
 * @{ */
#define MCUXCLKEY_LOADSTATUS_NOTLOADED     0x0000u   ///< Key not loaded
#define MCUXCLKEY_LOADSTATUS_MEMORY        0x0001u   ///< Key is loaded to memory
#define MCUXCLKEY_LOADSTATUS_COPRO         0x0002u   ///< Key is loaded to HW IP slot
#define MCUXCLKEY_LOADSTATUS_KEEPLOADED    0x8000u   ///< Do not flush the key after the operation (for Symmetric keys only)
/** @} */


/* Define algorithm IDs */
/**
 * @defgroup mcuxClKey_KeyTypes mcuxClKey_KeyTypes
 * @brief Defines all key types of @ref mcuxClKey
 * @ingroup mcuxClKey_Macros
 * @{
 */
#define MCUXCLKEY_ALGO_ID_AES                  0x0F01u ///< AES key
#define MCUXCLKEY_ALGO_ID_RSA                  0x0E02u ///< RSA key
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP         0x0D03u ///< ECC key using Short Weierstrass Curve over GF(p)
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GF2M        0x0C04u ///< ECC key using Short Weierstrass Curve over GF(2^m)
#define MCUXCLKEY_ALGO_ID_ECC_MONTDH           0x0B05u ///< ECC key for MontDH key exchange scheme
#define MCUXCLKEY_ALGO_ID_ECC_EDDSA            0x0A06u ///< ECC key for EdDSA signature scheme
#define MCUXCLKEY_ALGO_ID_HMAC                 0x0907u ///< HMAC key
#define MCUXCLKEY_ALGO_ID_SM4                  0x0808u ///< SM4 key
#define MCUXCLKEY_ALGO_ID_SM2                  0x0809u ///< SM2 key
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP_EPHEMERAL_CUSTOM 0x0709u ///< ECC key using Short Weierstrass Curve over GF(p) with ephemeral custom domain parameters
#define MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP_STATIC_CUSTOM 0x060Au    ///< ECC key using Short Weierstrass Curve over GF(p) with static custom domain parameters
#define MCUXCLKEY_ALGO_ID_ALGO_MASK            0x0FFFu ///< Mask for Algorithm

#define MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY        0x0000u ///< Symmetric key
#define MCUXCLKEY_ALGO_ID_PUBLIC_KEY           0x8000u ///< Public key
#define MCUXCLKEY_ALGO_ID_PRIVATE_KEY          0x4000u ///< Private key
#define MCUXCLKEY_ALGO_ID_PRIVATE_KEY_CRT      0x6000u ///< Private RSA key in CRT format
#define MCUXCLKEY_ALGO_ID_KEY_PAIR             0xC000u ///< Key pair
#define MCUXCLKEY_ALGO_ID_PRIVATE_KEY_CRT_DFA  0xE000u ///< RSA key pair, with the private part in CRT format

#define MCUXCLKEY_ALGO_ID_USAGE_MASK           0xF000u ///< Mask for Key Usage
/** @} */

/* Define key sizes */
/**
 * @defgroup mcuxClKey_KeySize mcuxClKey_KeySize
 * @brief Defines all key sizes of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */
#define MCUXCLKEY_SIZE_NOTUSED           0u      ///< key length field is not used (e.g. ECC keys)
#define MCUXCLKEY_SIZE_128               16u     ///< 128 bit key, size in bytes
#define MCUXCLKEY_SIZE_160               20u     ///< 160 bit key, size in bytes
#define MCUXCLKEY_SIZE_192               24u     ///< 192 bit key, size in bytes
#define MCUXCLKEY_SIZE_224               28u     ///< 224 bit key, size in bytes
#define MCUXCLKEY_SIZE_256               32u     ///< 256 bit key, size in bytes
#define MCUXCLKEY_SIZE_320               40u     ///< 320 bit key, size in bytes
#define MCUXCLKEY_SIZE_384               48u     ///< 348 bit key, size in bytes
#define MCUXCLKEY_SIZE_512               64u     ///< 512 bit key, size in bytes
#define MCUXCLKEY_SIZE_521               66u     ///< 521 bit key, size in bytes
#define MCUXCLKEY_SIZE_1024              1024u   ///< 1024 bit key, size in bits
#define MCUXCLKEY_SIZE_2048              2048u   ///< 2048 bit key, size in bits
#define MCUXCLKEY_SIZE_3072              3072u   ///< 3072 bit key, size in bits
#define MCUXCLKEY_SIZE_4096              4096u   ///< 4096 bit key, size in bits
#define MCUXCLKEY_SIZE_6144              6144u   ///< 6144 bit key, size in bits
#define MCUXCLKEY_SIZE_8192              8192u   ///< 8192 bit key, size in bits

// TODO CLNS-6135: replace these divides by a macro that ensures rounding up
#define MCUXCLKEY_SIZE_128_IN_WORDS      (MCUXCLKEY_SIZE_128 / sizeof(uint32_t))     ///< 128 bit key, size in words
#define MCUXCLKEY_SIZE_160_IN_WORDS      (MCUXCLKEY_SIZE_160 / sizeof(uint32_t))     ///< 160 bit key, size in words
#define MCUXCLKEY_SIZE_192_IN_WORDS      (MCUXCLKEY_SIZE_192 / sizeof(uint32_t))     ///< 192 bit key, size in words
#define MCUXCLKEY_SIZE_224_IN_WORDS      (MCUXCLKEY_SIZE_224 / sizeof(uint32_t))     ///< 224 bit key, size in words
#define MCUXCLKEY_SIZE_256_IN_WORDS      (MCUXCLKEY_SIZE_256 / sizeof(uint32_t))     ///< 256 bit key, size in words
#define MCUXCLKEY_SIZE_320_IN_WORDS      (MCUXCLKEY_SIZE_320 / sizeof(uint32_t))     ///< 320 bit key, size in words
#define MCUXCLKEY_SIZE_384_IN_WORDS      (MCUXCLKEY_SIZE_384 / sizeof(uint32_t))     ///< 348 bit key, size in words
#define MCUXCLKEY_SIZE_512_IN_WORDS      (MCUXCLKEY_SIZE_512 / sizeof(uint32_t))     ///< 512 bit key, size in words
#define MCUXCLKEY_SIZE_521_IN_WORDS      ((MCUXCLKEY_SIZE_521 + sizeof(uint32_t) - 1u) / sizeof(uint32_t))     ///< 521 bit key, size in words
#define MCUXCLKEY_SIZE_1024_IN_WORDS     (MCUXCLKEY_SIZE_1024 / (sizeof(uint32_t) * 8u))    ///< 1024 bit key, size in words
#define MCUXCLKEY_SIZE_2048_IN_WORDS     (MCUXCLKEY_SIZE_2048 / (sizeof(uint32_t) * 8u))    ///< 2048 bit key, size in words
#define MCUXCLKEY_SIZE_3072_IN_WORDS     (MCUXCLKEY_SIZE_3072 / (sizeof(uint32_t) * 8u))    ///< 3072 bit key, size in words
#define MCUXCLKEY_SIZE_4096_IN_WORDS     (MCUXCLKEY_SIZE_4096 / (sizeof(uint32_t) * 8u))    ///< 4096 bit key, size in words
#define MCUXCLKEY_SIZE_6144_IN_WORDS     (MCUXCLKEY_SIZE_6144 / (sizeof(uint32_t) * 8u))    ///< 6144 bit key, size in words
#define MCUXCLKEY_SIZE_8192_IN_WORDS     (MCUXCLKEY_SIZE_8192 / (sizeof(uint32_t) * 8u))    ///< 8192 bit key, size in words
/** @} */



/**
 * @def MCUXCLKEY_WA_SIZE_MAX
 * @brief Define the max workarea size required for this component
 */
#define MCUXCLKEY_WA_SIZE_MAX 0U

/**
 * @def MCUXCLKEY_INVALID_KEYSLOT
 * @brief Define the value for an invalid key slot.
 */
#define MCUXCLKEY_INVALID_KEYSLOT    0xFFu

#endif /* MCUXCLKEY_CONSTANTS_H_ */
