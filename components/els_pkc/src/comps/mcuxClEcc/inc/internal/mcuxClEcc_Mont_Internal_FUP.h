/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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
 * @file  mcuxClEcc_Mont_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_MONT_INTERNAL_FUP_H_
#define MCUXCLECC_MONT_INTERNAL_FUP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>


/**********************************************************/
/* FUPs for Montgomery DH functionalities                 */
/**********************************************************/

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
/**
 * FUP program declaration mcuxClEcc_FUP_MontDhDecodeScalar
 */
#define mcuxClEcc_FUP_MontDhDecodeScalar_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_MontDhDecodeScalar[mcuxClEcc_FUP_MontDhDecodeScalar_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_MontDhX_CalcAffineX
 */
#define mcuxClEcc_FUP_MontDhX_CalcAffineX_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_MontDhX_CalcAffineX[mcuxClEcc_FUP_MontDhX_CalcAffineX_LEN];


/**********************************************************/
/* FUPs for SecureSacalarMult operation                   */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep
 */
#define mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep_Affine_LEN  19u
#define mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep_Projective_LEN  22u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep[mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep_Projective_LEN];

MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_MONT_INTERNAL_FUP_H_ */
