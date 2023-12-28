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
 * @file  mcuxClEcc_EdDSA_GenerateKeyPair_FUP.c
 * @brief FUP programs for EdDSA Key Generation
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_EdDSA_GenerateKeyPair_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x95u,0x8du,0x40u,0xc9u},{0x40u,0x14u,0x00u,0x04u,0x06u,0x18u},{0x00u,0x1au,0x00u,0x18u,0x02u,0x18u},{0x40u,0x17u,0x00u,0x18u,0x02u,0x04u},{0x00u,0x15u,0x00u,0x05u,0x07u,0x18u},{0x00u,0x14u,0x00u,0x18u,0x08u,0x1cu}};



/**
 * [DESIGN]                 Ed25519               Ed448
 * PS1 LEN =                256-bit               448-bit (64-bit PkcWord) or 512-bit (128-bit PkcWord)
 * PS2 LEN =                256-bit               512-bit
 * v2 =                     2                     9
 * v3 =                     4                     2 (64-bit PkcWord) or 66 (128-bit PkcWord)
 * v4 =                     3                     2
 *
 *                     V0 = (h0..h255)            (?*56,h0..h455)
 * 1. L-shift v2 bits: S0 = (0,0,h0..h253)        (0,0*8,?*56,h0..h446)
 * 2. +1:              S0 = (1,0,h0..h253)        (1,0*8,?*56,h0..h446)
 * 3. R-rotate 1 bit:  V0 = (0,h0..h253,1)        (0*8,?*56,h0..h446,1)
 *                     V1 = V0                    (h0..h446,1)     if 64-bit PkcWord; or V0                    if 128-bit PkcWord
 * 4. R-shift v3 bits: S0 = (h3..h253,1,0*4)      (h2..h446,1,0*2) if 64-bit PkcWord; or (h2..h446,1,0*66)     if 128-bit PkcWord
 * 5. L-shift v4 bits: S2 = (0,0,0,h3..h253,1,0)  (0,0,h2..h446,1) if 64-bit PkcWord; or (0,0,h2..h446,1,0*64) if 128-bit PkcWord
 */
