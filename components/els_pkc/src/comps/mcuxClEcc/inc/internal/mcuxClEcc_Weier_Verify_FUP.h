/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021, 2023 NXP                                            */
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
 * @file  mcuxClEcc_Weier_Verify_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_WEIER_VERIFY_FUP_H_
#define MCUXCLECC_WEIER_VERIFY_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR
 */
#define mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR[mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR_LEN];

/**
 * FUP program declaration mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR
 */
#define mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR_LEN  10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR[mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR_LEN];

/**
 * FUP program declaration mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR
 */
#define mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR[mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR_LEN];

/**
 * FUP program declaration mcuxClEcc_Fup_Verify_InitZ_CalcU1U2
 */
#define mcuxClEcc_Fup_Verify_InitZ_CalcU1U2_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_InitZ_CalcU1U2[mcuxClEcc_Fup_Verify_InitZ_CalcU1U2_LEN];

/**
 * FUP program declaration mcuxClEcc_Fup_Verify_Update_G_to_Prec1
 */
#define mcuxClEcc_Fup_Verify_Update_G_to_Prec1_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Update_G_to_Prec1[mcuxClEcc_Fup_Verify_Update_G_to_Prec1_LEN];

/**
 * FUP program declaration mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z
 */
#define mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z_LEN  9u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z[mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z_LEN];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_VERIFY_FUP_H_ */
