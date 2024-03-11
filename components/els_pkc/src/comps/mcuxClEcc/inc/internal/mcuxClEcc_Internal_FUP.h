/*--------------------------------------------------------------------------*/
/* Copyright 2021-2024 NXP                                                  */
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
 * @file  mcuxClEcc_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_INTERNAL_FUP_H_
#define MCUXCLECC_INTERNAL_FUP_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * FUP program declaration mcuxClEcc_FUP_ConvertHomToAffine
 */
#define mcuxClEcc_FUP_ConvertHomToAffine_LEN  7u

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_ConvertHomToAffine[mcuxClEcc_FUP_ConvertHomToAffine_LEN];
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()


/*
 * FUP program declaration mcuxClEcc_FUP_Interleave
 */
#define mcuxClEcc_FUP_Interleave_LEN  7u

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Interleave[mcuxClEcc_FUP_Interleave_LEN];
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()

/**
 * FUP program declaration mcuxClEcc_FUP_PointComparisonHom
 */
#define mcuxClEcc_FUP_PointComparisonHom_LEN  10u

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_PointComparisonHom[mcuxClEcc_FUP_PointComparisonHom_LEN];
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()


/**
 * FUP program declaration mcuxClEcc_FUP_SetupEnvironment_ClearBuffers
 */
#define mcuxClEcc_FUP_SetupEnvironment_ClearBuffers_LEN  5u

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_SetupEnvironment_ClearBuffers[mcuxClEcc_FUP_SetupEnvironment_ClearBuffers_LEN];
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_INTERNAL_FUP_H_ */
