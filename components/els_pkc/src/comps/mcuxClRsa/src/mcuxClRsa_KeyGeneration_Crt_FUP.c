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
#include <internal/mcuxClRsa_KeyGeneration_Crt_FUP.h>

#include <mcuxCsslAnalysis.h>

const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps10_FUP[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xc4u,0xd2u,0x1du,0xf3u},{0x00u,0x1bu,0x00u,0x01u,0x0bu,0x09u},{0x00u,0x1eu,0x00u,0x00u,0x0au,0x08u}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps11_FUP[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xc4u,0xd2u,0x1du,0xf0u},{0x00u,0x1bu,0x00u,0x02u,0x0bu,0x09u},{0x00u,0x1eu,0x00u,0x00u,0x0au,0x08u}};
const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps12_FUP[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xfbu,0xe7u,0x09u,0x32u},{0x00u,0x1eu,0x00u,0x01u,0x0au,0x09u},{0x00u,0x1eu,0x00u,0x02u,0x0au,0x08u}};


/*
 * FUP to compute p - 1 and copy E
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/*
 * FUP to compute q - 1 and copy E
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/*
 * FUP to copy p and q
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
