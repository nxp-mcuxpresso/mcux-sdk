/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClHash_Constants.h
 *  @brief Constants for use with the mcuxClHash component */

#ifndef MCUXCLHASH_CONSTANTS_H_
#define MCUXCLHASH_CONSTANTS_H_

#include <mcuxClHash_Types.h>

/**
 * @defgroup mcuxClHash_Constants mcuxClHash_Constants
 * @brief Constants of @ref mcuxClHash component
 * @ingroup mcuxClHash
 * @{
 */

/**
* @defgroup mcuxClHash_Modes mcuxClHash_Modes
* @brief Hashing modes of the @ref mcuxClHash component
* @ingroup mcuxClHash_Constants
* @{
*/
/**
 * @brief Sha-224 hash calculation using the SHA-direct feature of CSS, it does not support RTF.
 *        SHA-direct mode has to be enabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA224_direct;
/**
 * @brief Sha-224 hash calculation using the Hash functionality of CSS, it does not support RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA224;
/**
 * @brief Sha-256 hash calculation using the SHA-direct feature of CSS, it does not support RTF.
 *        SHA-direct mode has to be enabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA256_direct;
/**
 * @brief Sha-256 hash calculation using the Hash functionality of CSS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA256;
/**
 * @brief Sha-384 hash calculation using the SHA-direct feature of CSS, it does not support RTF.
 *        SHA-direct mode has to be enabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA384_direct;
/**
 * @brief Sha-384 hash calculation using the Hash functionality of CSS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA384;
/**
 * @brief Sha-512 hash calculation using the SHA-direct feature of CSS, it does not support RTF.
 *        SHA-direct mode has to be enabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA512_direct;
/**
 * @brief Sha-512 hash calculation using the Hash functionality of CSS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_Algo_t mcuxClHash_AlgoSHA512;


/**@}*/

/**@}*/

#endif /* MCUXCLHASH_CONSTANTS_H_ */
