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
 * @file  mcuxClEcc_Weier_Internal_ConvertPoint_FUP.c
 * @brief FUP program for Weierstrass curve internal point conversion
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h>

#include <mcuxCsslAnalysis.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x5bu,0xa9u,0x51u,0x00u},{0x80u,0x00u,0x20u,0x16u,0x00u,0x24u},{0x80u,0x00u,0x21u,0x16u,0x00u,0x25u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x23u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x22u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x10u,0x8cu,0x25u,0x66u},{0x80u,0x00u,0x26u,0x16u,0x00u,0x20u},{0x80u,0x00u,0x27u,0x16u,0x00u,0x21u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x22u},{0x80u,0x00u,0x28u,0x16u,0x00u,0x24u},{0x80u,0x00u,0x29u,0x16u,0x00u,0x25u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x23u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertJacToAffine[10] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x2bu,0xd4u,0x4fu,0x6cu},{0x80u,0x00u,0x19u,0x16u,0x00u,0x1bu},{0x80u,0x00u,0x1bu,0x16u,0x00u,0x19u},{0x80u,0x00u,0x19u,0x19u,0x00u,0x1du},{0x80u,0x00u,0x1du,0x19u,0x00u,0x1fu},{0x80u,0x00u,0x20u,0x1du,0x00u,0x19u},{0x80u,0x33u,0x19u,0x00u,0x00u,0x24u},{0x80u,0x2au,0x00u,0x24u,0x00u,0x24u},{0x80u,0x00u,0x21u,0x1fu,0x00u,0x19u},{0x80u,0x33u,0x19u,0x00u,0x00u,0x25u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine[11] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xb2u,0xc8u,0x75u,0x8bu},{0x80u,0x00u,0x19u,0x16u,0x00u,0x1bu},{0x80u,0x00u,0x1bu,0x16u,0x00u,0x19u},{0x80u,0x00u,0x19u,0x19u,0x00u,0x1du},{0x80u,0x00u,0x1du,0x19u,0x00u,0x1fu},{0x80u,0x00u,0x24u,0x1du,0x00u,0x19u},{0x80u,0x00u,0x25u,0x1fu,0x00u,0x1bu},{0x80u,0x33u,0x19u,0x00u,0x00u,0x20u},{0x80u,0x33u,0x1bu,0x00u,0x00u,0x21u},{0x80u,0x2au,0x00u,0x20u,0x00u,0x20u},{0x80u,0x2au,0x00u,0x21u,0x00u,0x21u}};


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/* FUP program: convert points P1 and P2 from affine coordinates        */
/* to Jacobian coordinates in MR                                        */
/* Input: P1 = (x,y) in NR in (WEIER_X1,WEIER_Y1)                       */
/*        P2 = (x,y) in NR in (WEIER_X2,WEIER_Y2)                       */
/* Output: P1 = (X,Y,Z) in MR in (WEIER_XA,WEIER_YA,WEIER_ZA)           */
/*         P2 = (X,Y,Z) in MR in (WEIER_X0,WEIER_Y0,WEIER_Z)            */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/* FUP program: convert point P from affine coordinates         */
/* to Jacobian coordinates in MR                                */
/* Input: P = (x,y) in NR in (XA,YA)                            */
/* Output: P = (X,Y,Z) in MR in (WEIER_X0, WEIER_Y0, WEIER_Z)   */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/* FUP program: convert point P from Jacobian in MR to affine coordinates in NR     */
/* Input:                                                                           */
/*   P = (X,Y,Z) in (WEIER_XA,WEIER_YA,-), Jacobian coordinates                     */
/*   ECC_T0 = (z*z')^(-1) * 256^(-LEN), with z is Z coordinate in P relative to z'  */
/* Output:                                                                          */
/*   P = (x,y)     in (WEIER_X0,WEIER_Y0), affine coordinates                       */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
