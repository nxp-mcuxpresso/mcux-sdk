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
 * @file  mcuxClEcc_EdDSA_Internal_DecodePoint_FUP.c
 * @brief FUP programs for EdDSA Signature Verification
 */

#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_TwEd_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_EdDSA_Internal_FUP.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_FUP_PROGRAM()
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed25519[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x64u,0x95u,0x0eu,0x43u},{0x80u,0x00u,0x1du,0x20u,0x00u,0x1fu},{0x80u,0x00u,0x1fu,0x1fu,0x00u,0x23u},{0x80u,0x00u,0x23u,0x1bu,0x00u,0x1du},{0x80u,0x21u,0x10u,0x1du,0x19u,0x1du},{0x80u,0x00u,0x24u,0x16u,0x00u,0x1bu},{0x82u,0x2au,0x00u,0x1du,0x00u,0x1du}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xddu,0x23u,0x11u,0x23u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x22u},{0x80u,0x00u,0x19u,0x16u,0x00u,0x21u},{0x80u,0x00u,0x21u,0x21u,0x00u,0x19u},{0x80u,0x00u,0x19u,0x13u,0x00u,0x1bu},{0x80u,0x2au,0x10u,0x19u,0x22u,0x19u},{0x00u,0x15u,0x00u,0x00u,0x04u,0x23u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed25519[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x2du,0x7au,0x46u,0x16u},{0x80u,0x21u,0x10u,0x1bu,0x22u,0x1bu},{0x80u,0x00u,0x1bu,0x1bu,0x00u,0x1du},{0x80u,0x00u,0x1du,0x1bu,0x00u,0x1fu},{0x80u,0x00u,0x19u,0x1fu,0x00u,0x1du},{0x80u,0x00u,0x1du,0x1fu,0x00u,0x20u},{0x80u,0x00u,0x20u,0x1bu,0x00u,0x1fu}};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP_PROGRAM()


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
/**
 * FUP program for Ed25519 and Ed448 to compute in Decode Point: Y, Z, u and exp in MR, with
 * Y = Y-coordinate for the point decoding result (X:Y:Z)
 * Z = Z-coordinate for the point decoding result (X:Y:Z)
 * u = y^2 - 1
 * exp = (p-5)/8 for Ed25519 or (p-3)/4 for Ed448
 *
 * Prerequisites:
 *  - ECC_T0 contains Y in NR
 *  - ECC_V0 contains 3 for Ed25519 or 2 for Ed448
 *  - ECC_P contains modulus p in NR
 *  - ECC_PS contains the shifted modulus associated to p
 *  - ECC_CP1 contains domain parameter d in MR
 *  - ECC_PQSQR contains the R^2 values modulo p
 *
 * Result:
 *  - ECC_T0 contains u in MR
 *  - ECC_T1 contains d * y^2 in MR
 *  - ECC_COORD01 contains Y in MR
 *  - ECC_COORD02 contains Z in MR
 *  - ECC_COORD03 contains the exp (p-5)/8 for Ed25519 or (p-3)/4 for Ed448
 */

/**
 * FUP program for Ed25519 to compute in Decode Point: v, v^3, u * v^3 and  u * v^7 in MR, with
 * v = d * y^2 + 1
 *
 * Prerequisites:
 *  - ECC_T0 contains u in MR
 *  - ECC_T1 contains d * y^2 in MR
 *  - ECC_COORD02 contains 1 in MR
 *  - ECC_P contains modulus p in NR
 *  - ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - ECC_T1 contains v in MR
 *  - ECC_T2 contains u * v^3 in MR
 *  - ECC_T3 contains u * v^7 in MR
 */

/**
 * FUP program for Ed25519 to compute in Decode Point: x~ and x~^2 * v + u and square root of -1 mod p in MR, with
 * x~ = u * v^3 * (u * v^7)^((p-5)/8) mod p = X-coordinate candidate for the point decoding result (X:Y:Z)
 * v = d * y^2 + 1
 * u = y^2 - 1
 *
 * Prerequisites:
 *  - ECC_T0 contains u in MR
 *  - ECC_T1 contains v in MR
 *  - ECC_T2 contains u * v^3 in MR
 *  - ECC_COORD00 contains (u * v^7)^((p-5)/8) mod p in NR
 *  - ECC_COORD04 contains square root of -1 mod p in NR
 *  - ECC_P contains modulus p in NR
 *  - ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - ECC_T1 contains square root of -1 mod p in MR
 *  - ECC_T2 contains x~^2 * v + u in MR
 *  - ECC_T3 contains x~ in MR
 */


MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
