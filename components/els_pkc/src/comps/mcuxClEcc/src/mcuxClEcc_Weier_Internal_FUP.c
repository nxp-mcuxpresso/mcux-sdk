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
 * @file  mcuxClEcc_Weier_Internal_FUP.c
 * @brief Generic FUP programs for ECC
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_UpdateJacobianCoordinates[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xa7u,0xcfu,0xb1u,0x04u},{0x80u,0x00u,0x22u,0x22u,0x00u,0x1du},{0x80u,0x00u,0x1du,0x22u,0x00u,0x1fu},{0x80u,0x00u,0x24u,0x1du,0x00u,0x26u},{0x80u,0x00u,0x25u,0x1fu,0x00u,0x27u},{0x00u,0x1eu,0x00u,0x23u,0x03u,0x19u},{0x80u,0x00u,0x19u,0x22u,0x00u,0x23u}};



/* FUP program: update P:  (X0,Y0, old Z) -> (X1,Y1, new Z) Jacobian; */
/*              update z = z * z'.                                    */
