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
 * @file  mcuxClEcc_WeierECC_Internal_GenerateDomainParams_FUP.c
 * @brief FUP programs for Weierstrass domain parameter generation
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_WeierECC_Internal_GenerateDomainParams_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_GenerateDomainParams_Convert_G_toJacMR[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xa9u,0xb8u,0x80u,0xfeu},{0x00u,0x09u,0x00u,0x00u,0x00u,0x23u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x22u},{0x80u,0x00u,0x18u,0x16u,0x00u,0x24u},{0x80u,0x00u,0x1au,0x16u,0x00u,0x25u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_GenerateDomainParams_Reduce_R2N_R2P[4] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xb3u,0xa5u,0xceu,0x11u},{0x80u,0x33u,0x1fu,0x00u,0x01u,0x17u},{0x80u,0x00u,0x16u,0x16u,0x00u,0x1fu},{0x80u,0x33u,0x1fu,0x00u,0x00u,0x16u}};



MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
/* FUP program: prepare R2P and R2N strictly smaller than P and N. */


/* FUP program: converts base point G to Jacobian coordinates (X:Y:Z=1) in MR */
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
