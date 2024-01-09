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

/** @file  mcuxClHashModes_Algorithms.h
 *  @brief Algorithm/mode definitions for the mcuxClHashModes component
 */

#ifndef MCUXCLHASHMODES_ALGORITHMS_H_
#define MCUXCLHASHMODES_ALGORITHMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClHash_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup mcuxClHashModes_Algorithms mcuxClHashModes_Algorithms
* @brief Hashing algorithms of the @ref mcuxClHashModes component
* @ingroup mcuxClHash_Constants
* @{
*/

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()











/**
 * @brief Sha-224 algorithm descriptor
 *        Sha-224 hash calculation using the Hash functionality of ELS, it does not support RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha224;

/**
 * @brief Sha-224 algorithm
 *        Sha-224 hash calculation using the Hash functionality of ELS, it does not support RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
static mcuxClHash_Algo_t mcuxClHash_Algorithm_Sha224 = &mcuxClHash_AlgorithmDescriptor_Sha224;


/**
 * @brief Sha-256 algorithm descriptor
 *        Sha-256 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha256;

/**
 * @brief Sha-256 algorithm
 *        Sha-256 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
static mcuxClHash_Algo_t mcuxClHash_Algorithm_Sha256 = &mcuxClHash_AlgorithmDescriptor_Sha256;


/**
 * @brief Sha-384 algorithm descriptor
 *        Sha-384 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha384;

/**
 * @brief Sha-384 algorithm
 *        Sha-384 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
static mcuxClHash_Algo_t mcuxClHash_Algorithm_Sha384 = &mcuxClHash_AlgorithmDescriptor_Sha384;


/**
 * @brief Sha-512 algorithm descriptor
 *        Sha-512 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
extern const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha512;

/**
 * @brief Sha-512 algorithm
 *        Sha-512 hash calculation using the Hash functionality of ELS, it supports RTF.
 *        SHA-direct mode has to be disabled prior to using this algorithm
 */
static mcuxClHash_Algo_t mcuxClHash_Algorithm_Sha512 = &mcuxClHash_AlgorithmDescriptor_Sha512;




























MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**@}*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_ALGORITHMS_H_ */
