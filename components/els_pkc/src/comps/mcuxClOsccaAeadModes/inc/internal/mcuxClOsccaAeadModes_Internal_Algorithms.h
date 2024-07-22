/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

/** @file  mcuxClOsccaAeadModes_Internal_Algorithms.h
 *  @brief Internal header for the AEAD algorithm using the SM4
 */

#ifndef MCUXCLOSCCAAEADMODES_INTERNAL_ALGORITHMS_H_
#define MCUXCLOSCCAAEADMODES_INTERNAL_ALGORITHMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MCUXCL_FEATURE_SM4_CCM

extern const mcuxClOsccaAeadModes_algorithm_t mcuxClOsccaAead_algorithm_CCM_ENC;
extern const mcuxClOsccaAeadModes_algorithm_t mcuxClOsccaAead_algorithm_CCM_DEC;


#endif /* MCUXCL_FEATURE_SM4_CCM */
/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAAEADMODES_INTERNAL_ALGORITHMS_H_ */
