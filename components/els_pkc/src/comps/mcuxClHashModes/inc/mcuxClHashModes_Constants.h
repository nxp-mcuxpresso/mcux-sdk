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

/** @file  mcuxClHashModes_Constants.h
 *  @brief Constants for use with the mcuxClHashModes component */

#ifndef MCUXCLHASHMODES_CONSTANTS_H_
#define MCUXCLHASHMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClHash_Constants mcuxClHash_Constants
 * @brief Constants of @ref mcuxClHash component
 * @ingroup mcuxClHash
 * @{
 */

/**
 * @defgroup MCUXCLHASH_OUTPUT_SIZE_ MCUXCLHASH_OUTPUT_SIZE_
 * @brief Defines for digest sizes
 * @ingroup mcuxClHash_Constants
 * @{
 */
#define MCUXCLHASH_OUTPUT_SIZE_MD5                   (16U) ///< MD5 output size: 128 bit (16 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_1                 (20U) ///< SHA-1 output size: 160 bit (20 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_224               (28U) ///< SHA-224 output size: 224 bit (28 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_256               (32U) ///< SHA-256 output size: 256 bit (32 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_384               (48U) ///< SHA-384 output size: 384 bit (48 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_512               (64U) ///< SHA-512 output size: 512 bit (64 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_512_224           (28U) ///< SHA-512/224 output size: 224 bit (28 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA_512_256           (32U) ///< SHA-512/256 output size: 256 bit (32 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_224              (28uL)  ///< SHA3-224        output size:  224 bit (28 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_256              (32uL)  ///< SHA3-256        output size:  256 bit (32 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_384              (48uL)  ///< SHA3-384        output size:  384 bit (48 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_512              (64uL)  ///< SHA3-512        output size:  512 bit (64 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_SHAKE_128        (168uL) ///< SHA3-SHAKE 128  output size: 1344 bit (168 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_SHAKE_256        (136uL) ///< SHA3-SHAKE 256  output size: 1088 bit (136 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_CSHAKE_128       (168uL) ///< SHA3-CSHAKE 128 output size: 1344 bit (168 bytes)
#define MCUXCLHASH_OUTPUT_SIZE_SHA3_CSHAKE_256       (136uL) ///< SHA3-CSHAKE 256 output size: 1088 bit (136 bytes)
#define MCUXCLHASH_MAX_OUTPUT_SIZE                   (MCUXCLHASH_OUTPUT_SIZE_SHA3_SHAKE_128) ///< Maximum output size
/**@}*/




/**@}*/

#endif /* MCUXCLHASHMODES_CONSTANTS_H_ */
