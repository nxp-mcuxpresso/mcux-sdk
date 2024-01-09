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
#include <internal/mcuxClRsa_TestPrimeCandidate_FUP.h>

#include <mcuxCsslAnalysis.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_TestPrimeCandidate_Steps2_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    FUP_OP1_OR_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0),
    FUP_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0), //clear GCD2
    FUP_OP2_OR_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_A0,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0), //copy A0 to GCD2
    FUP_MC1_GCD(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2),
    FUP_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT2)
);
MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_TestPrimeCandidate_Steps3_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    FUP_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT1),
    FUP_OP1_OR_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_E,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0),
    FUP_MC1_GCD(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2),
    FUP_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT2)
);
