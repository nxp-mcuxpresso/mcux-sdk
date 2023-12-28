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

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_RemoveBlinding_FUP.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_RemoveBlinding_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* Set T2 = 0 */
    FUP_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_ZERO),
    /* Compute T1 = T2 + B */
    FUP_OP1_ADD_Z0(MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_B),
    /* Compute T2 = T1 * X mod Nb (X in Montgomery representation, T2 and T1 in normal representation) */
    FUP_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_NB),
    /* Normalize the result T1 = (T2 – Nb) mod Nb */
    FUP_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_NB, MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_NB)
);
