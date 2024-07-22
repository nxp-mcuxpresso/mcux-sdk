/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClOsccaSm2_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */

#ifndef MCUXCLOSCCASM2_INTERNAL_FUP_H_
#define MCUXCLOSCCASM2_INTERNAL_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClOsccaPkc_FupMacros.h>

#define mcuxClOsccaSm2_FUP_InvertPrivateKey_LEN  9u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_InvertPrivateKey[mcuxClOsccaSm2_FUP_InvertPrivateKey_LEN];

#define mcuxClOsccaSm2_FUP_PointDouble_LEN  23u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_PointDouble[mcuxClOsccaSm2_FUP_PointDouble_LEN];

#define mcuxClOsccaSm2_FUP_PointAdd_LEN  20u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_PointAdd[mcuxClOsccaSm2_FUP_PointAdd_LEN];

#define mcuxClOsccaSm2_FUP_PointCheckCoordinateX_LEN  6u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_PointCheckCoordinateX[mcuxClOsccaSm2_FUP_PointCheckCoordinateX_LEN];

#define mcuxClOsccaSm2_FUP_PointCheckCoordinateY_LEN  6u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_PointCheckCoordinateY[mcuxClOsccaSm2_FUP_PointCheckCoordinateY_LEN];

#define mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY_LEN  4u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY[mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY_LEN];

#define mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac_LEN  8u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac[mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac_LEN];

#define mcuxClOsccaSm2_FUP_JacPointCheck_LEN  16u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_JacPointCheck[mcuxClOsccaSm2_FUP_JacPointCheck_LEN];

#define mcuxClOsccaSm2_FUP_CheckRPlusS_LEN  5u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_CheckRPlusS[mcuxClOsccaSm2_FUP_CheckRPlusS_LEN];

#define mcuxClOsccaSm2_FUP_CheckSignature_LEN  5u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_CheckSignature[mcuxClOsccaSm2_FUP_CheckSignature_LEN];

#define mcuxClOsccaSm2_FUP_Sign_Prepare_KD_LEN  6u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_Sign_Prepare_KD[mcuxClOsccaSm2_FUP_Sign_Prepare_KD_LEN];

#define mcuxClOsccaSm2_FUP_Sign_RPlusK_LEN  7u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_Sign_RPlusK[mcuxClOsccaSm2_FUP_Sign_RPlusK_LEN];

#define mcuxClOsccaSm2_FUP_Sign_Check_r_LEN  5u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_Sign_Check_r[mcuxClOsccaSm2_FUP_Sign_Check_r_LEN];

#define mcuxClOsccaSm2_FUP_Sign_Double_Check_r_LEN  6u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_Sign_Double_Check_r[mcuxClOsccaSm2_FUP_Sign_Double_Check_r_LEN];

#define mcuxClOsccaSm2_FUP_Sign_Compute_s_LEN  22u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_Sign_Compute_s[mcuxClOsccaSm2_FUP_Sign_Compute_s_LEN];

#define mcuxClOsccaSm2_FUP_UpdateZ_LEN  6u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_UpdateZ[mcuxClOsccaSm2_FUP_UpdateZ_LEN];

#define mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints_LEN  7u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints[mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints_LEN];

#define mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0_LEN  4u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0[mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0_LEN];

#define mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1_LEN  4u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1[mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1_LEN];

#define mcuxClOsccaSm2_FUP_EccPointConvert2Affine_prepareZ3_LEN  5u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccPointConvert2Affine_PrepareZ3[mcuxClOsccaSm2_FUP_EccPointConvert2Affine_prepareZ3_LEN];

#define mcuxClOsccaSm2_FUP_EccImportInputPointWithInit_PrepareZ23_LEN  4u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_EccImportInputPointInputPointWithInit_PrepareZ23[mcuxClOsccaSm2_FUP_EccImportInputPointWithInit_PrepareZ23_LEN];

#define mcuxClOsccaSm2_FUP_KeyExchgCalcTa_LEN  11u
extern const mcuxClOsccaPkc_FUPEntry_t mcuxClOsccaSm2_FUP_KeyExchgCalcTa[mcuxClOsccaSm2_FUP_KeyExchgCalcTa_LEN];

#endif /* MCUXCLOSCCASM2_INTERNAL_FUP_H_ */
