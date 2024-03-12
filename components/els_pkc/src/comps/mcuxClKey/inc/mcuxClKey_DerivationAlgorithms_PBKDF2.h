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
 * @file  mcuxClKey_DerivationAlgorithms_PBKDF2.h
 * @brief Declarations and definitions for the Implementation of PBKDF2 Key Derivation
 */

#ifndef MCUXCLKEY_DERIVATIONALGORITHMS_PBKDF2_H_
#define MCUXCLKEY_DERIVATIONALGORITHMS_PBKDF2_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxCsslAnalysis.h>
#include <mcuxClKey.h>
#include <mcuxClMac.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Construct a key derivation function (KDF) mode according to RFC2898 (PBKDF2).
 *
 * @param[out]    pDerivationMode        Pointer to the key derivation mode structure to be initialized.
 * @param[in]     derivationAlgorithm    Function pointer to the key derivation algorithm function.
 * @param[in]     macMode                Mac mode type, must represent an HMAC mode.
 * @param[in]     iterationCount         Security parameter
 *
 * @details When calling mcuxClKey_derivation function with this constructor additional inputs must be provided via mcuxClKey_DerivationInput_t inputs[]
 *          parameter array. Detailed description of possible inputs is provided for each algorithm type.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_Derivation_ModeConstructor_PBKDF2)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_PBKDF2(
    mcuxClKey_DerivationMode_t * pDerivationMode,
    const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
    mcuxClMac_Mode_t macMode,
    uint32_t iterationCount
);

/**
 * @brief PBKDF2 key derivation algorithm descriptor
 */
extern const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_PBKDF2;

/**
 * @brief PBKDF2 key derivation algorithm type
 *
 * @details When using this algorithm possible inputs[] for mcuxClKey_derivation function are:
 *          - inputs[0] salt
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced.")
static mcuxClKey_DerivationAlgorithm_t mcuxClKey_DerivationAlgorithm_PBKDF2 = &mcuxClKey_DerivationAlgorithmDescriptor_PBKDF2;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_DERIVATIONALGORITHMS_PBKDF2_H_ */
