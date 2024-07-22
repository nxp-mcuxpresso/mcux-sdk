/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClOsccaRandomModes_Constants.h
 * @brief Mode definitions of mcuxClOsccaRandomModes component
 */

#ifndef MCUXCLOSCCARANDOMMODES_CONSTANTS_H_
#define MCUXCLOSCCARANDOMMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClRandom_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Types of mcuxClOsccaRandomModes                         */
/**********************************************************/
/**
 * @defgroup mcuxClOsccaRandomModes_Modes mcuxClOsccaRandomModes_Modes
 * @brief Defines all modes of @ref mcuxClOsccaRandomModes
 * @ingroup mcuxClOsccaRandomModes
 * @{
 */
#ifdef MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG
/**
 * @brief DTRNG implemented in ROTRNG mode descriptor
 */
extern const mcuxClRandom_ModeDescriptor_t mcuxClOsccaRandomModes_mdROTRNG_Trng;
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClRandom_Mode_t mcuxClOsccaRandomModes_Mode_TRNG = &mcuxClOsccaRandomModes_mdROTRNG_Trng;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()
#endif /* MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG */

/**
 * @}
 */ /* mcuxClOsccaRandomModes_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCARANDOMMODES_CONSTANTS_H_ */
