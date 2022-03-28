/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClEcc_Verify_FUUP_programs.h
 * @brief Header of ECDSA signature verification supporting curve P-384
 */

#ifndef MCUXCLECC_VERIFY_FUP_PROGRAMS_H_
#define MCUXCLECC_VERIFY_FUP_PROGRAMS_H_

#include <internal/mcuxClPkc_FupMacros.h>

#include <mcuxClEcc_Verify_FUP.h>
#include <mcuxClEcc_Verify_P384_FUP.h>

#define mcuxClEcc_Fup_Verify_InitZ_CalcU1U2_LEN  6u

#define mcuxClEcc_Fup_Verify_Convert_G_PrecG_toMR_LEN  5u

#define mcuxClEcc_Fup_Verify_Update_G_to_Prec1_LEN  5u

#define mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR_LEN  6u

#define mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z_LEN  9u

#define mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR_LEN  10u

#define mcuxClEcc_Fup_InitZ_CalcU1U2_LEN  6u

#define mcuxClEcc_Fup_Convert_G_PrecG_toMR_LEN  5u

#define mcuxClEcc_Fup_Update_G_to_Prec1_LEN  5u

#define mcuxClEcc_Fup_Convert_pubkeyQ_toJacobianMR_LEN  6u

#define mcuxClEcc_Fup_Update_pubkeyQ_P1_z_LEN  9u

#define mcuxClEcc_Fup_Convert_P1plusP2_toAffineNR_CalcR_LEN  9u

#endif
