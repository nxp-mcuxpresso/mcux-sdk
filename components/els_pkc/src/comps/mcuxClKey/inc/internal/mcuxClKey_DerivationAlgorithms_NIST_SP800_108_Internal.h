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
 * @file  mcuxClKey_DerivationAlgorithms_NIST_SP800_108.h
 * @brief Declarations and definitions for the NIST SP800-108 KDF
 */

#ifndef MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_INTERNAL_H_
#define MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClSession.h>
#include <mcuxClKey.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Key derivation engine function for NIST SP800-108.
 *
 * @param[in]     pSession          Session handle.
 * @param[in]     derivationMode    Derivation mode, can be created with corresponding ModeConstructor.
 * @param[in]     derivationKey     Input derivation key.
 * @param[in]     inputs            The first element contains the label, the second contains the context and the third contains IV (only for Feedback mode).
 * @param[in]     numberOfInputs    Fixed to 3 for Feedback mode and 2 for other modes.
 * @param[out]    derivedKey        Output key handle.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_derivationEngine_NIST_SP800_108, mcuxClKey_DerivationEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivationEngine_NIST_SP800_108(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[],
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey
);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_DERIVATIONALGORITHMS_NIST_SP800_108_INTERNAL_H_ */
