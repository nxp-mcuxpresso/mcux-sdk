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
 * @file  mcuxClEcc_EdDSA_Internal_CalcHashModN_FUP.c
 * @brief FUP programs for EdDSA Signature Verification
 */

#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_TwEd_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_EdDSA_Internal_FUP.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_FUP_PROGRAM()
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x9du,0xc3u,0xb1u,0x8bu},{0x00u,0x3eu,0x1bu,0x1bu,0x03u,0x1bu},{0x00u,0x1au,0x04u,0x04u,0x02u,0x04u},{0x80u,0x00u,0x1bu,0x17u,0x01u,0x1du},{0xc0u,0x00u,0x18u,0x1du,0x01u,0x1bu},{0x80u,0x00u,0x1bu,0x17u,0x01u,0x1du},{0x80u,0x2au,0x01u,0x1du,0x01u,0x18u}};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP_PROGRAM()




/**
 * FUP program to compute Hash mod N
 *
 * Prerequisites:
 *  - ECC_V0 points to the second PKC word of ECC_T1
 *  - ECC_S0 contains the hash h (of size (operandSize + bufferSize))
 *  - PS2 lengths set to (operandSize + bufferSize, operandSize)
 *
 * Result:
 *  - ECC_S0 contains Hash mod N in NR
 */
