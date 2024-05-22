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

/** @file  mcuxClOsccaSm3_Algorithms.h
 *  @brief Algorithm/mode definitions for the mcuxClOsccaSm3 component
 */

#ifndef MCUXCLOSCCASM3_ALGORITHMS_H_
#define MCUXCLOSCCASM3_ALGORITHMS_H_

#include <mcuxClHash_Types.h>
#include <mcuxCsslAnalysis.h>

/**
* @defgroup mcuxClOsccaSm3_Modes mcuxClOsccaSm3_Modes
* @brief Hashing modes of the @ref mcuxClOsccaSm3 component
* @ingroup mcuxClOsccaSm3_Constants
* @{
*/

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")

#if defined(MCUXCL_FEATURE_HASH_HW_SM3)
/**
 * @brief SM3 algorithm descriptor
 *        SM3 hash calculation using the Hash functionality OSCCA SM3.
 */
extern const mcuxClHash_AlgorithmDescriptor_t mcuxClOsccaSm3_AlgorithmDescriptor_Sm3;

/**
 * @brief SM3 algorithm descriptor
 *        SM3 hash calculation using the Hash functionality OSCCA SM3.
 */
static mcuxClHash_Algo_t mcuxClOsccaSm3_Algorithm_Sm3 = &mcuxClOsccaSm3_AlgorithmDescriptor_Sm3;

#endif /* MCUXCL_FEATURE_HASH_HW_SM3 */

MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**@}*/

#endif /* MCUXCLOSCCASM3_ALGORITHMS_H_ */
