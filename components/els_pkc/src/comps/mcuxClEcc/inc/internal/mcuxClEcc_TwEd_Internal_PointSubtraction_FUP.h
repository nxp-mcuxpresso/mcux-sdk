/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClEcc_TwEd_Internal_PointSubtraction_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_EDDSA_POINTSUBTRACTION_FUP_H_
#define MCUXCLECC_EDDSA_POINTSUBTRACTION_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FUP program declaration mcuxClEcc_FUP_TwEd_PointSubtraction
 */
#define mcuxClEcc_FUP_TwEd_PointSubtraction_LEN  22u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointSubtraction[mcuxClEcc_FUP_TwEd_PointSubtraction_LEN];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_EDDSA_POINTSUBTRACTION_FUP_H_ */
