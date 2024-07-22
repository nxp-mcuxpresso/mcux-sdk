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

#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_PrivateCrt_FUP.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_FUP_PROGRAM()
const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_CalcM1_FUP[4] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x10u,0x7du,0x59u,0x76u},{0xc0u,0x33u,0x0eu,0x0eu,0x10u,0x0fu},{0x80u,0x00u,0x0cu,0x0fu,0x10u,0x0eu},{0x80u,0x2au,0x10u,0x0eu,0x10u,0x0bu}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_CalcM_b_FUP[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x11u,0x17u,0x00u,0xe2u},{0x80u,0x13u,0x03u,0x04u,0x03u,0x0fu},{0x40u,0x3eu,0x10u,0x10u,0x11u,0x10u},{0x00u,0x1eu,0x06u,0x06u,0x11u,0x10u},{0x40u,0x0au,0x0fu,0x0fu,0x10u,0x0eu}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_T1mb_FUP[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xf7u,0x3au,0x71u,0x0au},{0x80u,0x00u,0x07u,0x06u,0x02u,0x03u},{0xc0u,0x2au,0x02u,0x09u,0x03u,0x0au}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_T2T3T4mb_FUP[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x2du,0x85u,0x77u,0xe6u},{0x80u,0x00u,0x07u,0x05u,0x02u,0x03u},{0x80u,0x00u,0x07u,0x04u,0x02u,0x05u},{0xc0u,0x2au,0x02u,0x03u,0x05u,0x04u},{0xc0u,0x00u,0x0au,0x04u,0x02u,0x03u},{0xc0u,0x33u,0x03u,0x03u,0x02u,0x04u}};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP_PROGRAM()


/*
 * FUP to calculate Mp_bm - Mq_bm mod p_b
 * PS1 len: (qDashAlignLen, blindedPrimeAlignLen)
 * PS2 len: (blindedPrimeAlignLen, blindedPrimeAlignLen)
 */

/*
 * FUP to calculate T2_mb, T3_mb, qInv_bm, T4_mb, T4_b
 * PS1 len: (qDashAlignLen, blindedPrimeAlignLen)
 * PS2 len: (blindedPrimeAlignLen, blindedPrimeAlignLen)
 */

/*
 * FUP to calculate the masked message M_b
 * PS1 len: (primeAlignLen, blindedPrimeAlignLen)
 * PS2 len: (0u, blindedMessageAlignLen)
 */

/*
 * FUP to calculate and normalized the message M1
 * PS1 len: (modAlignLen, modAlignLen)
 * PS2 len: (blindedMessageAlignLen, modAlignLen)
 */
