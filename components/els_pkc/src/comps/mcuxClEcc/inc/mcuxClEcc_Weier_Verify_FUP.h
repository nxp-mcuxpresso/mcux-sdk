/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClEcc_Weier_Verify_FUP.h
*  @brief defines FUP programs byte arrays
*/
#ifndef MCUXCLECC_WEIER_VERIFY_FUP_H_
#define MCUXCLECC_WEIER_VERIFY_FUP_H_
#include <internal/mcuxClPkc_FupMacros.h>

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR[5];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR[10];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR[6];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_InitZ_CalcU1U2[6];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Update_G_to_Prec1[5];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z[9];

#endif /* MCUXCLECC_WEIER_VERIFY_FUP*/ 
