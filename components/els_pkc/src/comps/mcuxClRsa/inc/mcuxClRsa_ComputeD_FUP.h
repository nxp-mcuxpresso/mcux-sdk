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

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_ComputeD_FUP.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_ComputeD_Steps123_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Compute p' = p-1 */
    FUP_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PSUB1, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_P,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_CONSTANT),
    /* Compute q' = q-1 */
    FUP_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_Q,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_CONSTANT),
    /* Compute phi = (p−1)(q−1) */
    FUP_MC1_PM(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PSUB1, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1),

    /* Compute qsub1 = gcd(p-1,q−1) */
    FUP_MC1_GCD(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PSUB1, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1),
    /* for both operand are congruent 2 mod 4, the result should be left shift by 1 bit */
    FUP_OP1_SHL(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_CONSTANT)
);
