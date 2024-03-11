/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_FUP_H_
#define MCUXCLECC_WEIER_INTERNAL_FUP_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()

/**********************************************************/
/* FUPs for Weier Point Conversion operations             */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine
 */
#define mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine_LEN  11u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine[mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac
 */
#define mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac[mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_ConvertJacToAffine
 */
#define mcuxClEcc_FUP_Weier_ConvertJacToAffine_LEN   10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertJacToAffine[mcuxClEcc_FUP_Weier_ConvertJacToAffine_LEN];

/*
 * FUP program declaration mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian
 */
#define mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian_LEN 5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian[mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian_LEN];


/**********************************************************/
/* FUPs for Weier Miscellaneous operations                */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_UpdateJacobianCoordinates
 */
#define mcuxClEcc_FUP_UpdateJacobianCoordinates_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_UpdateJacobianCoordinates[mcuxClEcc_FUP_UpdateJacobianCoordinates_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_PointCheckAffNR
 */
#define mcuxClEcc_FUP_Weier_PointCheckAffNR_LEN  10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_PointCheckAffNR[mcuxClEcc_FUP_Weier_PointCheckAffNR_LEN];


/**********************************************************/
/* FUPs for Weier Point Arithmetic Operations             */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_DoubleAdd
 */
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len1   5u
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len2  15u
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len   (mcuxClEcc_FUP_Weier_DoubleAdd_Len1 + mcuxClEcc_FUP_Weier_DoubleAdd_Len2)
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_DoubleAdd[mcuxClEcc_FUP_Weier_DoubleAdd_Len];

#define MCUXCLECC_FP_CALCFUP_ADD_ONLY()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len)
#define MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

#define MCUXCLECC_FP_CALCFUP_DOUBLE_ADD()  \
    do{  \
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len);  \
        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len1,  \
                                   mcuxClEcc_FUP_Weier_DoubleAdd_Len2);  \
    } while (false)
#define MCUXCLECC_FP_CALLED_CALCFUP_DOUBLE_ADD  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)


/**
 * FUP program declaration mcuxClEcc_FUP_Weier_RepeatDouble
 */
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len1  5u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len2  16u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len3  3u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len   (mcuxClEcc_FUP_Weier_RepeatDouble_Len1 + mcuxClEcc_FUP_Weier_RepeatDouble_Len2 + mcuxClEcc_FUP_Weier_RepeatDouble_Len3)
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_RepeatDouble[mcuxClEcc_FUP_Weier_RepeatDouble_Len];

#define MCUXCLECC_FP_CALCFUP_ONE_DOUBLE()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_RepeatDouble,  \
                        mcuxClEcc_FUP_Weier_RepeatDouble_Len1 + mcuxClEcc_FUP_Weier_RepeatDouble_Len2)
#define MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)


/**
 * FUP program declaration mcuxClEcc_FUP_Weier_CoZPointAddSub
 */
#define mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN1   7u
#define mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN2   18u
#define mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN3   3u
#define mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN  \
    (mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN1 + mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN2 + mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN3)
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_CoZPointAddSub[mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN];


/**
 * FUP program declaration mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP
 */
#define mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP_LEN  8
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP[mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP_LEN];


/**
 * FUP program declaration mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1
 */
#define mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1  4u
#define mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2  11u
#define mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN3  5u
#define mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN  \
    (  mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1  \
     + mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2  \
     + mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN3 )
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1[mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN];


/**********************************************************/
/* FUPs for Weier KeyGeneration                           */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey
 */
#define mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey_LEN  7u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey[mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey_LEN];


/**********************************************************/
/* FUPs for WeierECC blinded secret key generation        */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps34
 */
#define mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps34_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps34[mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps34_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps56
 */
#define mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps56_LEN  8u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps56[mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Steps56_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Step7
 */
#define mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Step7_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Step7[mcuxClEcc_FUP_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits_Step7_LEN];


/**********************************************************/
/* FUPs for ECDH PointMult (KeyAgreement)                 */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR
 */
#define mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR_LEN  10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR[mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR_LEN];


/**********************************************************/
/* FUPs for ECDSA Sign                                    */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_Sign_CalculateS
 */
#define mcuxClEcc_FUP_Weier_Sign_CalculateS_LEN  13u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_Sign_CalculateS[mcuxClEcc_FUP_Weier_Sign_CalculateS_LEN];


/**********************************************************/
/* FUPs for ECDSA Verify                                  */
/**********************************************************/

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


MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_INTERNAL_FUP_H_ */
