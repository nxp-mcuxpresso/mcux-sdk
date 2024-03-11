/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClKey_DerivationAlgorithms_NIST_SP800_108.h
 * @brief Declarations and definitions for the NIST SP800-108 KDF
 */

#ifndef MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_H_
#define MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxCsslAnalysis.h>
#include <mcuxClKey.h>
#include <mcuxClMac.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Construct a key derivation function (KDF) mode according to NIST SP800-108.
 *
 * @param[out]    pDerivationMode        Pointer to the key derivation mode structure to be initialized.
 * @param[in]     derivationAlgorithm    Function pointer to the key derivation algorithm function.
 * @param[in]     macMode                Mac mode type, in case a Mac mode is used within the key derivation algorithm.
 * @param[in]     options                Generic options field containing algorithm-specific parameters (e.g., counter length or iteration count).
 *                                       Must not be larger than 32. Use MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_* definitions.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108(
    mcuxClKey_DerivationMode_t * pDerivationMode,
    const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
    mcuxClMac_Mode_t macMode,
    uint32_t options
);

/**
 * @brief NIST SP800-108 key derivation algorithm descriptors
 */
extern const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_108;

/**
 * @brief NIST SP800-108 key derivation algorithm types
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced.")
static mcuxClKey_DerivationAlgorithm_t mcuxClKey_DerivationAlgorithm_NIST_SP800_108 = &mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_108;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief NIST SP800-108 Counter Mode with CMAC algorithm descriptor
 */
extern const mcuxClKey_DerivationMode_t mcuxClKey_DerivationMode_SP800_108_CM_CMAC;

/**
 * @brief NIST SP800-108 algorithm type
 *
 * Parameters:
 * - Counter Mode
 * - CMAC
 * - 8-bit counter
 *
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced.")
static const mcuxClKey_Derivation_t mcuxClKey_Derivation_SP800_108_CM_CMAC = &mcuxClKey_DerivationMode_SP800_108_CM_CMAC;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_H_ */
