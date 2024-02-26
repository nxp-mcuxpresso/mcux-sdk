/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021, 2023 NXP                                            */
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

/**
 * @file  mcuxClEcc_Weier_Internal_KeyGen_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_KEYGEN_FUP_H_
#define MCUXCLECC_WEIER_INTERNAL_KEYGEN_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34
 */
#define mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34[mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56
 */
#define mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56_LEN  8u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56[mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_CoreKeyGen_Step7
 */
#define mcuxClEcc_FUP_Weier_CoreKeyGen_Step7_LEN  5u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_CoreKeyGen_Step7[mcuxClEcc_FUP_Weier_CoreKeyGen_Step7_LEN];


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_INTERNAL_KEYGEN_FUP_H_ */
