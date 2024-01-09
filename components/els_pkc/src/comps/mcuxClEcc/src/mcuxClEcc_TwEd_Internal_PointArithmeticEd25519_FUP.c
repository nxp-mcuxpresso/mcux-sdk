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
 * @file  mcuxClEcc_TwEd_Internal_FUP.c
 * @brief mcuxClEcc: FUP programs used in ECC functions for Twisted Edwards curve Ed25519
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal_Ed25519_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_MixedPointAddEd25519[19] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xd8u,0x3fu,0xd1u,0x4cu},{0x80u,0x00u,0x23u,0x0fu,0x00u,0x19u},{0x80u,0x00u,0x13u,0x19u,0x00u,0x1fu},{0x80u,0x21u,0x10u,0x1fu,0x1fu,0x1fu},{0x80u,0x21u,0x10u,0x0eu,0x0du,0x23u},{0x80u,0x2au,0x10u,0x0eu,0x0du,0x1du},{0x80u,0x21u,0x10u,0x21u,0x20u,0x19u},{0x80u,0x2au,0x10u,0x21u,0x20u,0x21u},{0x80u,0x00u,0x19u,0x23u,0x00u,0x1bu},{0x80u,0x00u,0x21u,0x1du,0x00u,0x19u},{0x80u,0x21u,0x10u,0x22u,0x22u,0x22u},{0x80u,0x2au,0x10u,0x1bu,0x19u,0x1du},{0x80u,0x21u,0x10u,0x1bu,0x19u,0x19u},{0x80u,0x2au,0x10u,0x22u,0x1fu,0x1bu},{0x80u,0x21u,0x10u,0x22u,0x1fu,0x1fu},{0x80u,0x00u,0x1du,0x1bu,0x00u,0x20u},{0x80u,0x00u,0x1fu,0x19u,0x00u,0x21u},{0x80u,0x00u,0x1du,0x19u,0x00u,0x23u},{0x80u,0x00u,0x1bu,0x1fu,0x00u,0x22u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointDoubleEd25519[16] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x6eu,0x03u,0x54u,0xcbu},{0x80u,0x00u,0x20u,0x20u,0x00u,0x19u},{0x80u,0x00u,0x21u,0x21u,0x00u,0x1bu},{0x80u,0x00u,0x22u,0x22u,0x00u,0x1du},{0x80u,0x21u,0x10u,0x1du,0x1du,0x1du},{0x80u,0x21u,0x10u,0x21u,0x20u,0x23u},{0x80u,0x00u,0x23u,0x23u,0x00u,0x1fu},{0x80u,0x21u,0x10u,0x19u,0x1bu,0x23u},{0x80u,0x2au,0x10u,0x1fu,0x23u,0x1fu},{0x80u,0x2au,0x10u,0x1bu,0x19u,0x19u},{0x80u,0x2au,0x10u,0x19u,0x1du,0x1du},{0x80u,0x2au,0x10u,0x10u,0x23u,0x1bu},{0x80u,0x00u,0x1fu,0x1du,0x00u,0x20u},{0x80u,0x00u,0x19u,0x1bu,0x00u,0x21u},{0x80u,0x00u,0x1fu,0x1bu,0x00u,0x23u},{0x80u,0x00u,0x1du,0x19u,0x00u,0x22u}};



/* FUP program: perform point doubling on Ed25519 in extended homogeneous   */
/*   coordinates.                                                           */
/* Prerequisites:                                                           */
/* - Buffers TWED_X, TWED_Y, TWED_Z and TWED_T contain the homogeneous      */
/*      coordinates (X:Y:Z:T) of P in MR                                    */
/* - ps1Len = (operandSize, operandSize)                                    */
/* - Buffer ECC_PFULL contains p'||p                                        */
/* - Buffer ECC_PS contains the shifted modulus associated to p             */
/* Result:                                                                  */
/* - The resulting coordinates (Xres:Yres:Zres:Tres) are stored in buffers  */
/*      TWED_X, TWED_Y, TWED_Z and TWED_T in MR.                            */


/* FUP program: perform unified mixed extended point addition on Ed25519    */
/* Prerequisites:                                                           */
/* - Buffers TWED_X, TWED_Y, TWED_Z and TWED_T contain the homogeneous      */
/*      coordinates (X1:Y1:Z1:T1) of P1 in MR                               */
/* - Pointers TWED_PP_VX0, TWED_PP_VY0 and TWED_PP_VT0 point to the         */
/*      coordinates X2, Y2 and T2 in MR.                                    */
/* - ps1Len = (operandSize, operandSize)                                    */
/* - Buffer ECC_PFULL contains p'||p                                        */
/* - Buffer ECC_PS contains the shifted modulus associated to p             */
/* Result:                                                                  */
/* - The resulting coordinates (Xres:Yres:Zres:Tres) are stored in buffers  */
/*      TWED_X, TWED_Y, TWED_Z and TWED_T in MR.                            */

