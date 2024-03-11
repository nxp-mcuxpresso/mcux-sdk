/*--------------------------------------------------------------------------*/
/* Copyright 2024 NXP                                                       */
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
 * @file  mcuxClEcc_DeterministicECDSA_Internal_BlindedSecretKeyGen_FUP.c
 * @brief FUP programs for ECDSA related functionality
 */

#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_ECDSA_Internal_FUP.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_FUP_PROGRAM()
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xbau,0x72u,0x7du,0x97u},{0x80u,0x00u,0x19u,0x17u,0x01u,0x1bu},{0x80u,0x00u,0x1cu,0x17u,0x01u,0x1fu},{0x80u,0x00u,0x1bu,0x1fu,0x01u,0x1du},{0x80u,0x33u,0x1du,0x1du,0x01u,0x1bu},{0x80u,0x2au,0x01u,0x1bu,0x01u,0x1au}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x84u,0xb3u,0x28u,0x9fu},{0x40u,0x0au,0x1cu,0x1cu,0x1du,0x1bu},{0x40u,0x3eu,0x19u,0x19u,0x03u,0x19u},{0x00u,0x1eu,0x01u,0x01u,0x03u,0x19u},{0x40u,0x0au,0x19u,0x19u,0x1du,0x1fu},{0x40u,0x4bu,0x1bu,0x1bu,0x1fu,0x1bu}};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP_PROGRAM()



MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
/* FUP program to check in a blinded way if ephemeral key k is smaller than base point order n
 *
 * Prerequisites:
 *  - ECC_S2 = ephemeral key k (considered as of size bufferSize)
 *  - ECC_T2 = random blinding of size bufferSize-1
 *  - ECC_N  = base point order n
 *
 * Result:
 *  - The PKC CARRY flag is set after the FUP program, iff k is smaller than n. */


/* FUP program to blind the ephemeral key k multiplicatively with a 64-bit random blinding k0 (with MSBit set to 1)
 * and check in blinded form if k is zero
 *
 * Prerequisites:
 *  - ECC_S2 = ephemeral key k
 *  - ECC_T1 = k0^(-1) mod n
 *  - ECC_N  = base point order n
 *  - ECC_NQSQR = Montgomery factor R^2 associated to n
 *
 * Result:
 *  - Buffer ECC_S1 contains k1 = k0^(-1) * k mod n
 *  - The PKC ZERO flag is set after the FUP program, iff k equals 0. */
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
