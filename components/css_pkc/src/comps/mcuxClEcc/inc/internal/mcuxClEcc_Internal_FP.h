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

/** @file  mcuxClEcc_Internal_FP.h
 *  @brief Internal header of flow protection in mcuxClEcc component
 */

#ifndef MCUXCLECC_INTERNAL_FP_H_
#define MCUXCLECC_INTERNAL_FP_H_

#define MCUXCLECC_FP_KEYGEN_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT)

#define MCUXCLECC_FP_KEYGEN_CURVE_PARAM_0  \
    MCUXCLECC_FP_KEYGEN_INIT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_KEYGEN_CURVE_PARAM  \
    MCUXCLECC_FP_KEYGEN_CURVE_PARAM_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_KEYGEN_BASE_POINT  \
    MCUXCLECC_FP_KEYGEN_CURVE_PARAM,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY  \
    MCUXCLECC_FP_KEYGEN_BASE_POINT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_CoreKeyGen)

#define MCUXCLECC_FP_KEYGEN_CALC_PUBKEY  \
    MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult)

#define MCUXCLECC_FP_KEYGEN_CONVERT_PUBKEY  \
    MCUXCLECC_FP_KEYGEN_CALC_PUBKEY,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_KEYGEN_FINAL  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)

#define MCUXCLECC_FP_SIGN_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT)

#define MCUXCLECC_FP_SIGN_CURVE_PARAM_0  \
    MCUXCLECC_FP_SIGN_INIT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_SIGN_CURVE_PARAM  \
    MCUXCLECC_FP_SIGN_CURVE_PARAM_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_SIGN_BEFORE_LOOP  \
    MCUXCLECC_FP_SIGN_CURVE_PARAM

#define MCUXCLECC_FP_SIGN_LOOP_R_0  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_SIGN_LOOP_R_1  \
    MCUXCLECC_FP_SIGN_LOOP_R_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_CoreKeyGen)

#define MCUXCLECC_FP_SIGN_LOOP_R  \
    MCUXCLECC_FP_SIGN_LOOP_R_1,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MS

#define MCUXCLECC_FP_SIGN_LOOP_S  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
     \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MS

#define MCUXCLECC_FP_SIGN_FINAL  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)

#define MCUXCLECC_FP_POINTMULT_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT)

#define MCUXCLECC_FP_POINTMULT_CURVE_PARAM_0  \
    MCUXCLECC_FP_POINTMULT_INIT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_POINTMULT_CURVE_PARAM  \
    MCUXCLECC_FP_POINTMULT_CURVE_PARAM_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)

#define MCUXCLECC_FP_POINTMULT_BASE_POINT  \
    MCUXCLECC_FP_POINTMULT_CURVE_PARAM,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_POINTMULT_SCALAR  \
    MCUXCLECC_FP_POINTMULT_BASE_POINT,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
	MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,  \
	MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_ADD,  \
	MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

#define MCUXCLECC_FP_POINTMULT_SCALAR_MULTIPLICATION  \
    MCUXCLECC_FP_POINTMULT_SCALAR,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult)

#define MCUXCLECC_FP_POINTMULT_CONVERT_POINT  \
    MCUXCLECC_FP_POINTMULT_SCALAR_MULTIPLICATION,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_POINTMULT_FINAL  \
\
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)

#endif
