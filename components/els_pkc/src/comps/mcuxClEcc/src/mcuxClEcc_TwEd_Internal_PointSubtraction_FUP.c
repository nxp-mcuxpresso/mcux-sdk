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
 * @file  mcuxClEcc_TwEd_Internal_PointSubtraction_FUP.c
 * @brief FUP programs used in ECC functions for Twisted Edwards curve Ed25519
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_TwEd_Internal_PointSubtraction_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointSubtraction[22] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x88u,0x80u,0xb5u,0xf0u},{0x80u,0x2au,0x10u,0x10u,0x20u,0x20u},{0x80u,0x00u,0x3bu,0x22u,0x00u,0x18u},{0x80u,0x00u,0x18u,0x18u,0x00u,0x19u},{0x80u,0x00u,0x39u,0x20u,0x00u,0x1au},{0x80u,0x00u,0x3au,0x21u,0x00u,0x1bu},{0x80u,0x00u,0x1au,0x1bu,0x00u,0x1cu},{0x80u,0x00u,0x13u,0x1cu,0x00u,0x1eu},{0x80u,0x2au,0x10u,0x19u,0x1eu,0x1du},{0x80u,0x21u,0x10u,0x19u,0x1eu,0x19u},{0x80u,0x21u,0x10u,0x39u,0x3au,0x1cu},{0x80u,0x21u,0x10u,0x20u,0x21u,0x1eu},{0x80u,0x00u,0x1cu,0x1eu,0x00u,0x1fu},{0x80u,0x2au,0x10u,0x1fu,0x1au,0x1cu},{0x80u,0x2au,0x10u,0x1cu,0x1bu,0x1cu},{0x80u,0x00u,0x18u,0x1du,0x00u,0x1eu},{0x80u,0x00u,0x1eu,0x1cu,0x00u,0x20u},{0x80u,0x00u,0x12u,0x1au,0x00u,0x1cu},{0x80u,0x2au,0x10u,0x1bu,0x1cu,0x1bu},{0x80u,0x00u,0x18u,0x19u,0x00u,0x1au},{0x80u,0x00u,0x1au,0x1bu,0x00u,0x21u},{0x80u,0x00u,0x1du,0x19u,0x00u,0x22u}};



MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * FUP program to do point subtraction P1 - P2.
 * The source for algorithm used for addition is:
 *      2008 Bernstein--Birkner--Joye--Lange--Peters http://eprint.iacr.org/2008/013 Section 6
 *
 * Prerequisites:
 *  - TWED_PP_X7 contains the X-coordinate of point P1
 *  - TWED_PP_Y7 contains the Y-coordinate of point P1
 *  - TWED_PP_T7 contains the Z-coordinate of point P1
 *  - TWED_X contains the X-coordinate of point P2
 *  - TWED_Y contains the Y-coordinate of point P2
 *  - TWED_Z contains the Z-coordinate of point P2
 *  - ECC_CP0 contains domain parameter a
 *
 * Result:
 *  - Buffers TWED_X, TWED_Y, TWED_Z contain the result (X:Y:Z) in MR
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
