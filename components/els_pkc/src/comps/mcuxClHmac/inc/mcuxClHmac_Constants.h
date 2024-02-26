/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClHmac_Constants.h
 * @brief Constants for the mcuxClHmac component
 */

#ifndef MCUXCLHMAC_CONSTANTS_H_
#define MCUXCLHMAC_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClHashModes_Constants.h>

/**
 * @defgroup mcuxClHmac_Constants mcuxClHmac Constants
 * @brief Constants of @ref mcuxClHmac component
 * @ingroup mcuxClHmac
 * @{
 */

/* Output sizes */

#define MCUXCLHMAC_ELS_OUTPUT_SIZE               (32u)  /* Size of HMAC SHA-256 output in bytes: 256 bits (32 bytes) */
#define MCUXCLHMAC_ELS_OUTPUT_SIZE_IN_WORDS      (MCUXCLHMAC_ELS_OUTPUT_SIZE / sizeof(uint32_t))

#define MCUXCLHMAC_MAX_OUTPUT_SIZE               (MCUXCLHASH_MAX_OUTPUT_SIZE)
#define MCUXCLHMAC_MAX_OUTPUT_SIZE_IN_WORDS      (MCUXCLHMAC_MAX_OUTPUT_SIZE / sizeof(uint32_t))

/* Helper macros and constants for HMAC buffer sizes, assuming HMAC on ELS with SHA-256 is used */
#define MCUXCLHMAC_ELS_BLOCK_SIZE                (64u)
#define MCUXCLHMAC_ELS_SIZE_OF_LENGTH_FIELD      (8u)
#define MCUXCLHMAC_ELS_MIN_PADDING_LENGTH        (MCUXCLHMAC_ELS_SIZE_OF_LENGTH_FIELD + 1u) ///< Size of minimum HMAC padding length
#define MCUXCLHMAC_ELS_INPUTBUFFER_LENGTH(dataLength) \
  ((((dataLength) + MCUXCLHMAC_ELS_MIN_PADDING_LENGTH) + (MCUXCLHMAC_ELS_BLOCK_SIZE) - 1) / (MCUXCLHMAC_ELS_BLOCK_SIZE)) * MCUXCLHMAC_ELS_BLOCK_SIZE ///< Formula to calculate input buffer size for HMAC with SHA-256

/** @}*/

#endif /* MCUXCLHMAC_CONSTANTS_H_ */
