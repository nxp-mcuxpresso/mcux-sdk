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

/** @file  mcuxClOsccaAeadModes_Modes.h
 *  @brief Supported modes for the mcuxClOsccaAeadModes component
 */

#ifndef MCUXCLOSCCAAEADMODES_MODES_H_
#define MCUXCLOSCCAAEADMODES_MODES_H_

#include <mcuxCsslAnalysis.h>
#include <mcuxClAead_Types.h>
#include <mcuxCsslAnalysis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup clAeadModes AEAD mode definitions
 * @brief Modes used by the AEAD operations.
 * @ingroup mcuxClOsccaAeadModes
 * @{
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")
#ifdef MCUXCL_FEATURE_SM4_CCM

/**
 * @brief AES CCM encrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClOsccaAeadModes_ModeDescriptor_CCM_ENC;

/**
 * @brief AES CCM encrypt mode
 */
static mcuxClAead_Mode_t mcuxClOsccaAead_Mode_CCM_ENC =
  &mcuxClOsccaAeadModes_ModeDescriptor_CCM_ENC;

/**
 * @brief AES CCM decrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClOsccaAeadModes_ModeDescriptor_CCM_DEC;

/**
 * @brief AES CCM decrypt mode
 */
static mcuxClAead_Mode_t mcuxClOsccaAead_Mode_CCM_DEC =
  &mcuxClOsccaAeadModes_ModeDescriptor_CCM_DEC;


#endif /* MCUXCL_FEATURE_SM4_CCM */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAAEADMODES_MODES_H_ */
