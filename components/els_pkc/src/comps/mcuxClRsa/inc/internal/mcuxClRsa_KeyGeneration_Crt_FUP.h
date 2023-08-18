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

/** @file  mcuxClRsa_KeyGeneration_Crt_FUP.h
*  @brief defines FUP programs byte arrays for mcuxClRsa_KeyGeneration_Crt
*/
#ifndef MCUXCLRSA_KEYGENERATION_CRT_FUP_H_
#define MCUXCLRSA_KEYGENERATION_CRT_FUP_H_
#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>

#define mcuxClRsa_KeyGeneration_Crt_Steps10_FUP_LEN  3u
#define mcuxClRsa_KeyGeneration_Crt_Steps11_FUP_LEN  3u
#define mcuxClRsa_KeyGeneration_Crt_Steps12_FUP_LEN  3u

extern const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps10_FUP[mcuxClRsa_KeyGeneration_Crt_Steps10_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps11_FUP[mcuxClRsa_KeyGeneration_Crt_Steps11_FUP_LEN];
extern const mcuxClPkc_FUPEntry_t mcuxClRsa_KeyGeneration_Crt_Steps12_FUP[mcuxClRsa_KeyGeneration_Crt_Steps12_FUP_LEN];

#endif /* MCUXCLRSA_KEYGENERATION_CRT_FUP_H_ */ 
