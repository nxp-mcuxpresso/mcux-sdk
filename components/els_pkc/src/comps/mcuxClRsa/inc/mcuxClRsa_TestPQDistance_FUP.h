/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
#include <internal/mcuxClRsa_TestPQDistance_FUP.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_TestPQDistance_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    /* 1. Copy 100 MSbits of p in to buffer in PKC RAM */
    FUP_OP1_SHR(MCUXCLRSA_INTERNAL_TESTPQDISTANCE_P100MSB,
        MCUXCLRSA_INTERNAL_TESTPQDISTANCE_P128MSB,
        MCUXCLRSA_INTERNAL_TESTPQDISTANCE_CONSTANT28),
    /* 2. Copy 100 MS bits of q into buffer in PKC RAM */
    FUP_OP1_SHR(MCUXCLRSA_INTERNAL_TESTPQDISTANCE_Q100MSB,
        MCUXCLRSA_INTERNAL_TESTPQDISTANCE_Q128MSB,
        MCUXCLRSA_INTERNAL_TESTPQDISTANCE_CONSTANT28),
    /*
    * 3. Compare 100 MSbits of p and q
    *    If they are equal, then function returns MCUXCLRSA_STATUS_INVALID_INPUT error code
    *    (primes do not meet the FIPS requirements).
    */
    FUP_OP1_CMP(MCUXCLRSA_INTERNAL_TESTPQDISTANCE_P100MSB,
        MCUXCLRSA_INTERNAL_TESTPQDISTANCE_Q100MSB),
);
