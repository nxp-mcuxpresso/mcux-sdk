/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Internal_PointComparison_FUP.c
 * @brief FUP programs for EdDSA Signature Verification
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_Internal_PointComparison_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_PointComparisonHom[10] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xf0u,0xf1u,0xd8u,0x77u},{0x80u,0x00u,0x04u,0x22u,0x00u,0x19u},{0x80u,0x00u,0x05u,0x22u,0x00u,0x1bu},{0x80u,0x00u,0x20u,0x06u,0x00u,0x1du},{0x80u,0x00u,0x21u,0x06u,0x00u,0x1fu},{0x80u,0x2au,0x10u,0x19u,0x1du,0x19u},{0x80u,0x2au,0x10u,0x1bu,0x1fu,0x1bu},{0x80u,0x00u,0x19u,0x1bu,0x00u,0x1du},{0x80u,0x33u,0x1du,0x00u,0x00u,0x1bu},{0x80u,0x2au,0x00u,0x1bu,0x00u,0x1bu}};



/**
 * FUP program to check if two projective points P1 and P2 are equal
 *
 * Prerequisites:
 *  - ECC_V0 contains the X-coordinate of point P1
 *  - ECC_V1 contains the Y-coordinate of point P1
 *  - ECC_V2 contains the Z-coordinate of point P1
 *  - ECC_COORD00 contains the X-coordinate of point P2
 *  - ECC_COORD01 contains the Y-coordinate of point P2
 *  - ECC_COORD02 contains the Z-coordinate of point P2
 *
 * Result:
 *  - The zero flag is set if and only if the two points are equal
 */
