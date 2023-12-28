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

const mcuxClPkc_FUPEntry_t mcuxClRsa_TestPrimeCandidate_Steps2_FUP[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xd1u,0x20u,0xd8u,0x0bu},{0x00u,0x1eu,0x00u,0x01u,0x07u,0x05u},{0x00u,0x3eu,0x00u,0x00u,0x07u,0x06u},{0x40u,0x1eu,0x00u,0x04u,0x07u,0x06u},{0x80u,0xa7u,0x05u,0x05u,0x06u,0x06u},{0x00u,0x1bu,0x00u,0x06u,0x09u,0x05u}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_TestPrimeCandidate_Steps3_FUP[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x5fu,0x25u,0x45u,0x45u},{0x00u,0x1bu,0x00u,0x01u,0x08u,0x05u},{0x00u,0x1eu,0x00u,0x00u,0x07u,0x06u},{0x80u,0xa7u,0x05u,0x05u,0x06u,0x06u},{0x00u,0x1bu,0x00u,0x06u,0x09u,0x05u}};


/*
 * FUP to check the candidate is coprime with the product of first 9
 * prime.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/*
 * FUP to check the candidate is coprime with the public E
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
