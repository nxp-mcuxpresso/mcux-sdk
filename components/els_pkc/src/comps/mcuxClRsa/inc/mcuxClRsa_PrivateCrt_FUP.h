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
#include <internal/mcuxClRsa_PrivateCrt_FUP.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_PrivateCrt_T1mb_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Calculate Mq_bm = Mq_b * QDash mod p_b */
    FUP_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* Mq_bm */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET4 /* QDash */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET3 /* Mq_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */),
    /* Calculate T1_mb = Mp_bm - Mq_bm mod p_b */
    FUP_MC2_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET5 /* T1_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_R /* Mp_bm */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* Mq_bm */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */)
);
MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_PrivateCrt_T2T3T4mb_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Calculate T2_mb = QDash*qInv_b mod p_b */
    FUP_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* T2_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET4 /* QDash */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET2 /* qInv_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */),
    /* Calculate T3_mb = QDash*R_qInv mod p_b */
    FUP_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET2 /* T3_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET4 /* QDash */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1 /* R_qInv */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */),
    /* Calculate qInv_bm = T2_mb-T3_mb mod p_b */
    FUP_MC2_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1 /* qInv_bm */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* T2_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET2 /* T3_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */),
    /* Calculate T4_mb = T1_mb*qInv_bm mod p_b */
    FUP_MC2_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* T4_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET5 /* T1_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1 /* qInv_bm */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */),
    /* Convert back into normal representation: T4_b = T4_mb mod p_b */
    FUP_MC2_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1 /* T4_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0  /* T4_mb */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B /* p_b */)
);
MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_PrivateCrt_CalcM_b_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Calculate T5_b = T4_b*q in MODT4 which has a size of
     * (primeAlignLen + blindedPrimeAlignLen = blindedMessageAlignLen)
     */
    FUP_MC1_PM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4 /* T5_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0 /* q */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1 /* T4_b */),
    /* For the following addition, move Mq_b to the bigger buffer N,
     * which is used as a temporary buffer
     */
    FUP_OP2_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_CONST0),
    FUP_OP1_OR_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* Mq_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET3  /* Mq_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_CONST0),
    /* Calculate masked message M_b = T5_b + Mq_b */
    FUP_OP2_ADD(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3 /* M_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4 /* T5_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* Mq_b */)
);
MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_PrivateCrt_CalcM1_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Calculate reduction M_br of M_b mod N */
    FUP_MC2_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4 /* M_br */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3 /* M_b */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */),
    /* Calculate message M1 = M_br * QDash mod N  */
    FUP_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3 /* M1 */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT1 /* QDash */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4 /* M_br */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */),
    /* Normalize result (case if M1 > N) */
    FUP_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_M /* M */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3 /* M1 */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */)
);
MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_PrivateCrt_ReductionME_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Convert from Montgomery to normal representation */
    FUP_MC1_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */),
    /* Normalize the result (case if R > N) and copy to the temp buffer for C' */
    FUP_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT2 /* C' */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N /* N */)
);
