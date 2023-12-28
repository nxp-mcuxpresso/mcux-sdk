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
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

/* Generate private key */
#define MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY  \
    MCUXCLECC_FP_KEYGEN_BASE_POINT,  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_CoreKeyGen),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

/* Calculate public key */
#define MCUXCLECC_FP_KEYGEN_CALC_PUBKEY  \
    MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY,  \
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
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
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
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    /* optional SHR will be balanced separately */ \
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
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
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
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),  \
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
    (2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,  \
    (2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc)),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,  \
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE


/**********************************************************/
/* mcuxClEcc_Verify                                        */
/**********************************************************/

#define MCUXCLECC_FP_VERIFY_INIT  \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc))

#define MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK \
        (MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)+ \
        MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN), \
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR)+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_InterleaveTwoScalars))

#define MCUXCLECC_FP_VERIFY_CALC_P1 \
       (MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc), \
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

#define MCUXCLECC_FP_VERIFY_P384_BEFORE_POINT_ADD \
        (MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384)+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_AND_CONST+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384)+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS+ \
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_InterleaveTwoScalars)+ \
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_NONZERO == checkHashZero), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup), \
            MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY, \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult_NIST), \
            MCUXCLPKC_FP_CALLED_CALC_MC1_MM, \
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST)+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST))

#define MCUXCLECC_FP_VERIFY_P384_POINT_ADD \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RepeatPointDouble_NIST)+ \
        MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult_NIST)+ \
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero), \
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd_NIST)))

#define MCUXCLECC_FP_VERIFY_P384_FINAL \
        (MCUXCLPKC_FP_CALLED_CALC_MC1_MM+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)+ \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST)+ \
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP)


/**********************************************************/
/* mcuxClEcc_WeierECC_GenerateDomainParams                 */
/**********************************************************/

#define MCUXCLECC_FP_WEIERECC_GENERATEDOMAINPARAMS_INIT_AND_VERIFY  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR)

#define MCUXCLECC_FP_WEIERECC_GENERATEDOMAINPARAMS_FINAL(options)  \
    MCUXCLECC_FP_WEIERECC_GENERATEDOMAINPARAMS_INIT_AND_VERIFY,  \
    MCUX_CSSL_FP_CONDITIONAL(MCUXCLECC_OPTION_GENERATEPRECPOINT_YES == ((options) & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK), \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RepeatPointDouble),  \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),  \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) ),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
    MCUX_CSSL_FP_CONDITIONAL(MCUXCLECC_OPTION_GENERATEPRECPOINT_YES == ((options) & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK),  \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),  \
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc) ),  \
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE


#endif /* MCUXCLECC_WEIER_INTERNAL_FP_H_ */
