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

/** @file  mcuxClRsa_PrivateCrt_FUP.h
*  @brief defines FUP programs byte arrays for mcuxClRsa_PrivateCrt
*/
#ifndef MCUXCLRSA_PRIVATECRT_FUP_H_
#define MCUXCLRSA_PRIVATECRT_FUP_H_
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

#define mcuxClRsa_PrivateCrt_T1mb_FUP_LEN            3u
#define mcuxClRsa_PrivateCrt_T2T3T4mb_FUP_LEN        6u
#define mcuxClRsa_PrivateCrt_CalcM_b_FUP_LEN         5u
#define mcuxClRsa_PrivateCrt_CalcM1_FUP_LEN          4u

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_T2T3T4mb_FUP[mcuxClRsa_PrivateCrt_T2T3T4mb_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_T1mb_FUP[mcuxClRsa_PrivateCrt_T1mb_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_CalcM1_FUP[mcuxClRsa_PrivateCrt_CalcM1_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_PrivateCrt_CalcM_b_FUP[mcuxClRsa_PrivateCrt_CalcM_b_FUP_LEN];
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()

#endif /* MCUXCLRSA_PRIVATECRT_FUP_H_ */
