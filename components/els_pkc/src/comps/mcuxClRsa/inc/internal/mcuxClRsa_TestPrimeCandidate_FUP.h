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

/** @file  mcuxClRsa_TestPrimeCandidate_FUP.h
*  @brief defines FUP programs byte arrays for mcuxClRsa_TestPrimeCandidate
*/
#ifndef MCUXCLRSA_TESTPRIMECANDIDATE_FUP_H_
#define MCUXCLRSA_TESTPRIMECANDIDATE_FUP_H_
#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

#define mcuxClRsa_TestPrimeCandidate_Steps2_FUP_LEN  6u
#define mcuxClRsa_TestPrimeCandidate_Steps3_FUP_LEN  5u

extern const mcuxClPkc_FUPEntry_t mcuxClRsa_TestPrimeCandidate_Steps2_FUP[mcuxClRsa_TestPrimeCandidate_Steps2_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_TestPrimeCandidate_Steps3_FUP[mcuxClRsa_TestPrimeCandidate_Steps3_FUP_LEN];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_TESTPRIMECANDIDATE_FUP_H_ */ 
