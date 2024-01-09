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
#include <internal/mcuxClRsa_Public_FUP.h>

MCUXCLPKC_FUP_EXT_ROM(mcuxClRsa_Public_ReductionME_FUP,
    PH_CLNS_UTILS_FAME_CRC_ENTRY,
    //Convert from Montgomery to normal representation
    FUP_MC1_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N),
    //Normalize the result (case if R > N) and copy to the output buffer
    FUP_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N)
);
