/*--------------------------------------------------------------------------*/
/* Copyright 2024 NXP                                                       */
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
 * @file  mcuxClEcc_ECDSA_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_ECDSA_INTERNAL_FUP_H_
#define MCUXCLECC_ECDSA_INTERNAL_FUP_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()

#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC
/**
 * FUP program declaration mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK
 */
#define mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK[mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK
 */
#define mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK[mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK_LEN];
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */

MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_ECDSA_INTERNAL_FUP_H_ */
