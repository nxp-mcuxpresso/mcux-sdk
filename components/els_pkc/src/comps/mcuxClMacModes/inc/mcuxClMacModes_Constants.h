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
 * @file  mcuxClMacModes_Constants.h
 * @brief Constants for the mcuxClMacModes component
 */

#ifndef MCUXCLMACMODES_CONSTANTS_H_
#define MCUXCLMACMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClMacModes_Constants mcuxClMacModes_Constants
 * @brief Constants of @ref mcuxClMacModes component
 * @ingroup mcuxClMacModes
 * @{
 */

/* Output sizes */
#define MCUXCLMAC_CBCMAC_OUTPUT_SIZE                   (16u)                                              ///< Size of CBCMAC output in bytes:       128 bits (16 bytes)
#define MCUXCLMAC_CBCMAC_OUTPUT_SIZE_IN_WORDS          (MCUXCLMAC_CBCMAC_OUTPUT_SIZE / sizeof(uint32_t)) ///< Size of CBCMAC output in bytes:       128 bits (16 bytes)
#define MCUXCLMAC_CMAC_OUTPUT_SIZE                     (16u)                                              ///< Size of CMAC output in bytes:         128 bits (16 bytes)
#define MCUXCLMAC_CMAC_OUTPUT_SIZE_IN_WORDS            (MCUXCLMAC_CMAC_OUTPUT_SIZE / sizeof(uint32_t))   ///< Size of CMAC output in bytes:         128 bits (16 bytes)
#define MCUXCLMAC_HMAC_SHA_256_OUTPUT_SIZE             (32u)                                                    ///< Size of HMAC SHA-256 output in bytes: 256 bits (32 bytes)
#define MCUXCLMAC_HMAC_SHA_256_OUTPUT_SIZE_IN_WORDS    (MCUXCLMAC_HMAC_SHA_256_OUTPUT_SIZE / sizeof(uint32_t)) ///< Size of HMAC SHA-256 output in bytes: 256 bits (32 bytes)

#define MCUXCLMAC_MAX_OUTPUT_SIZE                      (32u)
#define MCUXCLMAC_MAX_OUTPUT_SIZE_IN_WORDS             (MCUXCLMAC_MAX_OUTPUT_SIZE / sizeof(uint32_t))

/* Helper macros and constants for HMAC buffer sizes */
#define MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE      (64u)
#define MCUXCLMAC_HMAC_SIZE_OF_LENGTH_FIELD    (8u)
#define MCUXCLMAC_HMAC_MIN_PADDING_LENGTH      (MCUXCLMAC_HMAC_SIZE_OF_LENGTH_FIELD + 1u) ///< Size of minimum HMAC padding length
#define MCUXCLMACMODES_GET_HMAC_INPUTBUFFER_LENGTH(dataLength) \
  ((((dataLength) + MCUXCLMAC_HMAC_MIN_PADDING_LENGTH) + (MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE) - 1) / (MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE)) * MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE ///< Formula to calculate input buffer size for HMAC with SHA-256

/** @}*/

#endif /* MCUXCLMACMODES_CONSTANTS_H_ */
