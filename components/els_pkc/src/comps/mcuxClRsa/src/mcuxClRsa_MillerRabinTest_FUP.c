/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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

/** @file  mcuxClRsa_MillerRabinTest_FUP.c
 *  @brief mcuxClRsa: FUP programs for implementation of Rsa Miller-Rabin test
 */

#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_MillerRabinTest_FUP.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_FUP_PROGRAM()
const mcuxClPkc_FUPEntry_t mcuxClRsa_MillerRabinTest_ReducAndCheck_FUP[4] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xaau,0x2fu,0x08u,0x77u},{0xc0u,0x33u,0x02u,0x02u,0x00u,0x03u},{0xc0u,0x2au,0x00u,0x03u,0x00u,0x03u},{0x40u,0x1bu,0x03u,0x03u,0x09u,0x02u}};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP_PROGRAM()


/*
 * FUP to do Montgoery reduction and check the result
 */
