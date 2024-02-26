/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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
 * @file  mcuxClMath_ModInv_FUP.c
 * @brief mcuxClMath: modular inversion implementation
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_Internal_ModInv.h>
#include <internal/mcuxClMath_ModInv_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup1[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x1bu,0x93u,0xa9u,0x40u},{0x40u,0x3eu,0x00u,0x00u,0x06u,0x00u},{0x00u,0x1au,0x00u,0x00u,0x05u,0x03u},{0x80u,0x5du,0x01u,0x02u,0x03u,0x04u},{0x00u,0x1eu,0x00u,0x03u,0x06u,0x01u},{0x00u,0x3eu,0x00u,0x00u,0x06u,0x03u},{0x80u,0x2au,0x01u,0x01u,0x04u,0x02u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup3a[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xc9u,0x51u,0x7au,0xe2u},{0x80u,0x00u,0x02u,0x03u,0x01u,0x00u},{0x00u,0x1eu,0x00u,0x00u,0x06u,0x03u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup3b[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x00u,0xf6u,0x90u,0xd4u},{0x80u,0x00u,0x02u,0x03u,0x01u,0x00u},{0x80u,0x33u,0x00u,0x00u,0x01u,0x03u}};


/* ps1Len = (31*MCUXCLPKC_WORDSIZE, operandSize), i.e., LC = 31 */
/* ps2Len = (                   -, operandSize + PKC wordsize) */

/* If the modulus n shall be restored even when x and n are not coprime, */
/* n can be calculated by FUP_MC1_MMP2(MODINV_T, MODINV_N, MODINV_R).    */
/* ps, MMP2 needs extra PKC word of T as workspace, and this FUP program */
/* needs to be split to backup T0 before calculating n.                  */

/* ps1Len = (operandSize, operandSize) */

/* ps1Len = (operandSize, operandSize) */
