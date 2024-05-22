/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

#ifndef MCUXCLAES_CONSTANTS_H_
#define MCUXCLAES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClKey_Constants.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClAes_Constants mcuxClAes_Constants
 * @brief Defines of constants associated with @ref mcuxClAes
 * @ingroup mcuxClAes
 * @{
 */

/* Block size */
#define MCUXCLAES_BLOCK_SIZE                (16u)                                      ///< AES block size in bytes
#define MCUXCLAES_BLOCK_SIZE_IN_WORDS       (MCUXCLAES_BLOCK_SIZE / sizeof(uint32_t)) ///< AES block size in words

/* Key sizes */
#define MCUXCLAES_AES128_KEY_SIZE           (MCUXCLKEY_SIZE_128)            ///< AES-128 key size in bytes
#define MCUXCLAES_AES128_KEY_SIZE_IN_WORDS  (MCUXCLKEY_SIZE_128_IN_WORDS)   ///< AES-128 key size in words
#define MCUXCLAES_AES192_KEY_SIZE           (MCUXCLKEY_SIZE_192)            ///< AES-192 key size in bytes
#define MCUXCLAES_AES192_KEY_SIZE_IN_WORDS  (MCUXCLKEY_SIZE_192_IN_WORDS)   ///< AES-192 key size in words
#define MCUXCLAES_AES256_KEY_SIZE           (MCUXCLKEY_SIZE_256)            ///< AES-256 key size in bytes
#define MCUXCLAES_AES256_KEY_SIZE_IN_WORDS  (MCUXCLKEY_SIZE_256_IN_WORDS)   ///< AES-256 key size in words

/**
 * @}
 */ /* mcuxClAes_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAES_CONSTANTS_H_ */
