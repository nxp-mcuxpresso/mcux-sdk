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
 * @file  mcuxClMath_QDash_FUP.h
 * @brief defines FUP program byte arrays for mcuxClMath_QDash
 */

#ifndef MCUXCLMATH_QDASH_FUP_H_
#define MCUXCLMATH_QDASH_FUP_H_

#include <mcuxClCore_Platform.h>
#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * FUP program declaration mcuxClMath_QDash_Fup_Init
 */
#define mcuxClMath_QDash_Fup_Init_LEN  3u

extern const mcuxClPkc_FUPEntry_t mcuxClMath_QDash_Fup_Init[mcuxClMath_QDash_Fup_Init_LEN];

/*
 * FUP program declaration mcuxClMath_QDash_Fup_Loop0
 */
#define mcuxClMath_QDash_Fup_Loop0_LEN  3u

extern const mcuxClPkc_FUPEntry_t mcuxClMath_QDash_Fup_Loop0[mcuxClMath_QDash_Fup_Loop0_LEN];

/*
 * FUP program declaration mcuxClMath_QDash_Fup_Loop1
 */
#define mcuxClMath_QDash_Fup_Loop1_LEN  3u

extern const mcuxClPkc_FUPEntry_t mcuxClMath_QDash_Fup_Loop1[mcuxClMath_QDash_Fup_Loop1_LEN];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMATH_QDASH_FUP_H_*/
