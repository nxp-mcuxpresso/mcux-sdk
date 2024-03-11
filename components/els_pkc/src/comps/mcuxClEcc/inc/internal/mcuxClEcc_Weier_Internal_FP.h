/*--------------------------------------------------------------------------*/
/* Copyright 2020-2024 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_FP.h
 * @brief flow protection definitions
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_FP_H_
#define MCUXCLECC_WEIER_INTERNAL_FP_H_

#include <mcuxClConfig.h> // Exported features flags header


/**********************************************************/
/* mcuxClEcc_KeyGen                                        */
/**********************************************************/

/* Initialization */
#define MCUXCLECC_FP_KEYGEN_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared)

/* Import/check base point */
#define MCUXCLECC_FP_KEYGEN_BASE_POINT  \
    MCUXCLECC_FP_KEYGEN_INIT,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

/* Generate private key */
#define MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY  \
    MCUXCLECC_FP_KEYGEN_BASE_POINT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits)

/* Calculate public key */
#define MCUXCLECC_FP_KEYGEN_CALC_PUBKEY  \
    MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_LSB0s,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult)

/* Convert/check public key */
#define MCUXCLECC_FP_KEYGEN_CONVERT_PUBKEY  \
    MCUXCLECC_FP_KEYGEN_CALC_PUBKEY,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

/* Check n/p and export */
#define MCUXCLECC_FP_KEYGEN_FINAL  \
    MCUXCLECC_FP_KEYGEN_CONVERT_PUBKEY,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE


/**********************************************************/
/* mcuxClEcc_Sign                                          */
/**********************************************************/

/* Initialization */
#define MCUXCLECC_FP_SIGN_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment)

#define MCUXCLECC_FP_SIGN_BEFORE_LOOP  \
    MCUXCLECC_FP_SIGN_INIT, \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared)

/* Mail loop - first part, until checking r */
#define MCUXCLECC_FP_SIGN_LOOP_R_0  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC
#define MCUXCLECC_FP_SIGN_LOOP_R_1_DETERMINISTIC  \
    MCUXCLECC_FP_SIGN_LOOP_R_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen)

#define MCUXCLECC_FP_SIGN_LOOP_R_DETERMINISTIC  \
    MCUXCLECC_FP_SIGN_LOOP_R_1_DETERMINISTIC,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_LSB0s,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MS
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */

#define MCUXCLECC_FP_SIGN_LOOP_R_1_RANDOMIZED  \
    MCUXCLECC_FP_SIGN_LOOP_R_0,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits)

#define MCUXCLECC_FP_SIGN_LOOP_R_RANDOMIZED  \
    MCUXCLECC_FP_SIGN_LOOP_R_1_RANDOMIZED,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_LSB0s,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MS

/* Mail loop - second part, checking s */
#define MCUXCLECC_FP_SIGN_LOOP_S  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    /* optional SHR will be balanced separately */ \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,  \
    MCUXCLPKC_FP_CALLED_CALC_MC1_MS

#define MCUXCLECC_FP_SIGN_FINAL  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_EXPORTBIGENDIANFROMPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_EXPORTBIGENDIANFROMPKC_BUFFEROFFSET,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE


/**********************************************************/
/* mcuxClEcc_PointMult                                     */
/**********************************************************/

/* Initialization */
#define MCUXCLECC_FP_POINTMULT_INIT  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_RandomizeUPTRT),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash)

/* Import/check base point */
#define MCUXCLECC_FP_POINTMULT_BASE_POINT  \
    MCUXCLECC_FP_POINTMULT_INIT,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

/* Import scalar */
// TODO (CLNS-979) Avoid multiplication with 2 if CLNS-979 is reseolved
#define MCUXCLECC_FP_POINTMULT_SCALAR  \
    MCUXCLECC_FP_POINTMULT_BASE_POINT,  \
    (2u * MCUXCLPKC_FP_CALLED_CALC_OP1_CONST),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_OR,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUXCLPKC_FP_CALLED_SECUREIMPORTBIGENDIANTOPKC_BUFFER,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_ADD,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

/* Calculate scalar multiplication */
#define MCUXCLECC_FP_POINTMULT_SCALAR_MULTIPLICATION  \
    MCUXCLECC_FP_POINTMULT_SCALAR,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_LSB0s,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SecurePointMult)

/* Convert/check result of scalar multiplication */
#define MCUXCLECC_FP_POINTMULT_CONVERT_POINT  \
    MCUXCLECC_FP_POINTMULT_SCALAR_MULTIPLICATION,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

/* Check n/p and export */
// TODO (CLNS-979) Avoid multiplication with 2 if CLNS-979 is reseolved
#define MCUXCLECC_FP_POINTMULT_FINAL  \
    MCUXCLECC_FP_POINTMULT_CONVERT_POINT,  \
    (2u * MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER),  \
    (2u * MCUXCLPKC_FP_CALLED_CALC_OP1_CMP),  \
    MCUXCLPKC_FP_CALLED_SECUREEXPORTBIGENDIANFROMPKC_BUFFER,  \
    MCUXCLPKC_FP_CALLED_SECUREEXPORTBIGENDIANFROMPKC_BUFFEROFFSET,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE


/**********************************************************/
/* mcuxClEcc_Verify                                        */
/**********************************************************/

#define MCUXCLECC_FP_VERIFY_INIT  \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment)+ \
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER+ \
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET)

#define MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK \
        (MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER+ \
        MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN), \
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR)+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_InterleaveTwoScalars))

#define MCUXCLECC_FP_VERIFY_CALC_P1 \
       (MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero), \
            MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER, \
            MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET, \
            MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER, \
            MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET, \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup), \
            MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY, \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult), \
            MCUXCLPKC_FP_CALLED_CALC_MC1_MM, \
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST)+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc))

#define MCUXCLECC_FP_VERIFY_CALC_P2 \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RepeatPointDouble)+ \
        MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult))

#define MCUXCLECC_FP_VERIFY_CALC_P1_ADD_P2 \
        (MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd))+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP)



#endif /* MCUXCLECC_WEIER_INTERNAL_FP_H_ */
