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
 * @file  mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder_FUP.c
 * @brief FUP programs for Weierstrass curve internal secure point multiplication
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_CoZPointAddSub[28] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xc8u,0x49u,0x18u,0x02u},{0x00u,0x1eu,0x00u,0x08u,0x03u,0x1du},{0x80u,0x00u,0x1bu,0x1bu,0x00u,0x08u},{0x80u,0x21u,0x00u,0x08u,0x19u,0x08u},{0x80u,0x2au,0x00u,0x1du,0x08u,0x1du},{0x80u,0x00u,0x1bu,0x1du,0x00u,0x19u},{0x80u,0x2au,0x00u,0x19u,0x09u,0x09u},{0x10u,0x00u,0xd0u,0xdeu,0x33u,0x29u},{0x80u,0x2au,0x00u,0x04u,0x08u,0x1du},{0x80u,0x00u,0x07u,0x1du,0x00u,0x1bu},{0x00u,0x1eu,0x00u,0x1bu,0x03u,0x07u},{0x80u,0x00u,0x1du,0x1du,0x00u,0x1bu},{0x80u,0x00u,0x1bu,0x04u,0x00u,0x08u},{0x80u,0x00u,0x1bu,0x1du,0x00u,0x19u},{0x80u,0x21u,0x00u,0x05u,0x09u,0x1bu},{0x80u,0x2au,0x00u,0x05u,0x09u,0x1du},{0x80u,0x00u,0x05u,0x19u,0x00u,0x09u},{0x81u,0x2au,0x00u,0x19u,0x08u,0x19u},{0x80u,0x00u,0x1du,0x1du,0x00u,0x04u},{0x80u,0x21u,0x00u,0x04u,0x19u,0x04u},{0x82u,0x2au,0x00u,0x04u,0x00u,0x04u},{0x80u,0x2au,0x00u,0x08u,0x04u,0x1fu},{0x80u,0x00u,0x1fu,0x1du,0x00u,0x05u},{0x80u,0x2au,0x00u,0x05u,0x09u,0x05u},{0x80u,0x2au,0x00u,0x05u,0x00u,0x05u},{0x10u,0x00u,0xd7u,0xe0u,0x2au,0x7eu},{0x80u,0x2au,0x00u,0x08u,0x00u,0x08u},{0x80u,0x2au,0x00u,0x09u,0x00u,0x09u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1[20] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xf2u,0xf2u,0x1au,0xe6u},{0x80u,0x33u,0x22u,0x00u,0x00u,0x19u},{0x00u,0x15u,0x00u,0x19u,0x02u,0x22u},{0x00u,0x1au,0x00u,0x22u,0x02u,0x22u},{0x10u,0x00u,0xedu,0x4bu,0x97u,0xdau},{0x80u,0x00u,0x23u,0x22u,0x00u,0x19u},{0x00u,0x1eu,0x00u,0x19u,0x03u,0x23u},{0x80u,0x00u,0x22u,0x22u,0x00u,0x19u},{0x80u,0x2au,0x00u,0x19u,0x00u,0x19u},{0x80u,0x00u,0x22u,0x19u,0x00u,0x1bu},{0x80u,0x2au,0x00u,0x1bu,0x00u,0x1bu},{0x80u,0x00u,0x24u,0x19u,0x00u,0x1du},{0x80u,0x00u,0x25u,0x1bu,0x00u,0x1fu},{0x80u,0x2au,0x00u,0x1du,0x00u,0x24u},{0x80u,0x2au,0x00u,0x1fu,0x00u,0x25u},{0x10u,0x00u,0xc6u,0x85u,0x6eu,0x2du},{0x80u,0x00u,0x26u,0x19u,0x00u,0x1du},{0x80u,0x00u,0x27u,0x1bu,0x00u,0x1fu},{0x80u,0x2au,0x00u,0x1du,0x00u,0x26u},{0x80u,0x2au,0x00u,0x1fu,0x00u,0x27u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP[8] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x9du,0x26u,0xf0u,0xb4u},{0x80u,0x33u,0x16u,0x00u,0x00u,0x19u},{0x80u,0x00u,0x26u,0x19u,0x00u,0x1bu},{0x80u,0x00u,0x27u,0x19u,0x00u,0x1du},{0x80u,0x2au,0x00u,0x1bu,0x00u,0x26u},{0x80u,0x2au,0x00u,0x1du,0x00u,0x27u},{0x80u,0x00u,0x22u,0x19u,0x00u,0x1bu},{0x80u,0x2au,0x00u,0x1bu,0x00u,0x22u}};



/* FUP program for point addition and subtraction with co-Z coordinate
 * to be used for a Montgomery ladder step with following input and output:
 *
 * Input:
 *   P0 = (x0,y0, z) in (VX0,VY0,VZ) in Jacobian coordinates in MR with x0,y0 < p
 *   P1 = (x1,y1, z) in (VX1,VY1,VZ) in Jacobian coordinates in MR with x1,y1 < p
 *
 * Output:
 *   P0Res = (x0Res,y0Res,zRes) = 2*P0    in (VX0,VY0,VZ) in Jacobian coordinates in MR with x0Res,y0Res < p
 *   P1Res = (x1Res,y1Res,zRes) = P0 + P1 in (VX1,VY1,VZ) in Jacobian coordinates in MR with x0Res,y0Res < p
 *
 * The FUP program is divided into several parts which perform different arithmetic operations.
 * It shall be called twice with different entry points and FUP program lengths to realize
 * a full Montgomery ladder step:
 *   1. Execute part 2 of the FUP program for the first point addition and Z-coordinate update:
 *       - P0Int = (x0Int,y0Int,zInt) = P0 + P1             in (VX0,VY0,VZ) in Jacobian coordinates in MR with x0Int,y0Int < p
 *       - P1Int = (x1Int,y1Int,zInt) = P0 (with updated Z) in (VX1,VY1,VZ) in Jacobian coordinates in MR
 *
 *   2. Execute parts 1-3 of the FUP program for point subtraction, second point addition and coordinate reduction:
 *       - P1Sub = (x1Sub,y1Sub,zInt) = P1Int - P1 = P0 - P1    in (VX1,VY1,VZ) in Jacobian coordinates in MR
 *       - P0Res = (x0Res,y0Res,zRes) = P0Int + P0 - P1 = 2*P0  in (VX0,VY0,VZ) in Jacobian coordinates in MR with x0Res,y0Res < p
 *       - P1Res = (x1Res,y1Res,zRes) = P0Int (with updated Z)  in (VX1,VY1,VZ) in Jacobian coordinates in MR with x1Res,y1Res < p
 *
 * ATTENTION: The FUP program shall only be used with P0 != +/- P1, otherwise the result will be incorrect.
 *
 * NOTE: The FUP program performs modular additions and subtractions modulo p instead of modulo the shifted modulus.
 *       While this helps to ensure that the output coordinates are again < p, it might as a side-effect cause conditional
 *       subtractions resp. additions with the modulus p. Due to the assumptions on the input coordinates, however,
 *       the number of these conditional operations is usually rather small and in no case related to the scalar bits. */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()


/* FUP program to reduce values in X1, Y1 and ZA modulo p */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/* FUP program:
 *   - 1st part: Preparation of ZA in [1,p-1]
 *   - 2nd part: Update Z-coordinate and update Jacobian coordinates of R0 in MR
 *   - 3nd part: Update Jacobian coordinates of R1 in MR
 *
 * Input:
 *   R0 = (x0,y0, z) in (X0, Y0, Z), Jacobian in MR with x0, y0 < p
 *   R1 = (x1,y1, z) in (X1, Y1, Z), Jacobian in MR with x1, y1 < p
 * Output:
 *   Updated R0 = (x0,y0, z) in (X0, Y0, Z), Jacobian in MR with x0, y0 < p
 *   Updated R1 = (x1,y1, z) in (X1, Y1, Z), Jacobian in MR with x1, y1 < p
 *
 * NOTES:
 *   - If the 1st part is skipped, then X0, Y0, X1, Y1 are only in [0,p-1] if ZA is ensured to be in [0,p-1] */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
