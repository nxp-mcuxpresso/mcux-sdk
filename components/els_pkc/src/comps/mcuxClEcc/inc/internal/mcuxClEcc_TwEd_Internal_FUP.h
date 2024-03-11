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
 * @file  mcuxClEcc_TwEd_Internal_FUP.h
 * @brief defines FUP programs byte arrays for twisted Edwards curve Ed448
 */


#ifndef MCUXCLECC_TWED_INTERNAL_FUP_H_
#define MCUXCLECC_TWED_INTERNAL_FUP_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()



/**********************************************************/
/* FUPs for Ed25519 curve operations                      */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_TwEd_PointDoubleEd25519
 */
#define mcuxClEcc_FUP_TwEd_PointDoubleEd25519_Len  16u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointDoubleEd25519[mcuxClEcc_FUP_TwEd_PointDoubleEd25519_Len];

/**
 * FUP program declaration mcuxClEcc_FUP_TwEd_MixedPointAddEd25519
 */
#define mcuxClEcc_FUP_TwEd_MixedPointAddEd25519_Len  19u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_MixedPointAddEd25519[mcuxClEcc_FUP_TwEd_MixedPointAddEd25519_Len];


/**********************************************************/
/* FUPs for Variable Scalar Mult operation                */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep
 */
#define mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep_LEN  29u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep[mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate
 */
#define mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate_LEN  15u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate[mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate_LEN];


/**********************************************************/
/* FUPs for miscellaneous operations on TwEd curves       */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_TwEd_PointValidation
 */
#define mcuxClEcc_FUP_TwEd_PointValidation_Len  14u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointValidation[mcuxClEcc_FUP_TwEd_PointValidation_Len];

/**
 * FUP program declaration mcuxClEcc_FUP_TwEd_PointSubtraction
 */
#define mcuxClEcc_FUP_TwEd_PointSubtraction_LEN  22u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointSubtraction[mcuxClEcc_FUP_TwEd_PointSubtraction_LEN];

MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_TWED_INTERNAL_FUP_H_ */
