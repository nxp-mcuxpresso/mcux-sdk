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
 * @file  mcuxClKey_DerivationAlgorithms_NIST_SP800_56C.h
 * @brief Declarations and definitions for the NIST SP800-56C KDF
 */

#ifndef MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_56C_H_
#define MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_56C_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxCsslAnalysis.h>
#include <mcuxClKey.h>
#include <mcuxClMac.h>
#include <mcuxClHash.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Construct a key derivation function (KDF) mode according to NIST SP800-56C.
 *
 * @param[out]    pDerivationMode        Pointer to the key derivation mode structure to be initialized.
 * @param[in]     derivationAlgorithm    Function pointer to the key derivation algorithm function.
 * @param[in]     macMode                Mac mode type, in case a Mac mode is used within the key derivation algorithm.
 * @param[in]     hashFunction           hash function type, in case a hash function is used within the key derivation algorithm. SecSha algorithm descriptors are not supported.
 * @param[in]     options                Generic options field containing algorithm-specific parameters (e.g., counter length or iteration count). Currently not used.
 *
 * @details When calling mcuxClKey_derivation function with this constructor additional inputs may be provided via mcuxClKey_DerivationInput_t inputs[]
 *          parameter array. Detailed description of possible inputs is provided for each algorithm type.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_Derivation_ModeConstructor_NIST_SP800_56C)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_NIST_SP800_56C(
    mcuxClKey_DerivationMode_t * pDerivationMode,
    const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
    mcuxClMac_Mode_t macMode,
    mcuxClHash_Algo_t hashFunction,
    uint32_t options // no options for this mode, might remove the parameter
);

/**
 * @brief NIST SP800-56C key derivation algorithm descriptors
 */
extern const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_56C_OneStep;
extern const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_56C_TwoStep;

/**
 * @brief NIST SP800-56C key derivation algorithm types
 */

/**
 * @brief SP800 56C OneStep derivation algorithm type
 *
 * @details When using this algorithm possible inputs[] for mcuxClKey_derivation function are:
 *          - inputs[0] fixedInfo
 *          - inputs[1] salt (optional)
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced.")
static mcuxClKey_DerivationAlgorithm_t mcuxClKey_DerivationAlgorithm_NIST_SP800_56C_OneStep = &mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_56C_OneStep;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief SP800 56C TwoStep derivation algorithm type
 *
 * @details When using this algorithm possible inputs[] for mcuxClKey_derivation function are:
 *          - inputs[0] = Label
 *          - inputs[1] = Context
 *          - inputs[2] = salt (length is required, data pointer may be NULL which defaults to all-zero salt)
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced.")
static mcuxClKey_DerivationAlgorithm_t mcuxClKey_DerivationAlgorithm_NIST_SP800_56C_TwoStep = &mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_56C_TwoStep;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_56C_H_ */
