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

/** @file  mcuxClOsccaMacModes_Algorithms.h
 *  @brief Internal header for the MAC context for modes using the SM4
 */

#ifndef MCUXCLOSCCAMACMODES_ALGORITHMS_H_
#define MCUXCLOSCCAMACMODES_ALGORITHMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClOsccaMacModes_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
extern const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CMAC_SM4;
#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */
#ifdef MCUXCL_FEATURE_MACMODES_CBCMAC_SM4
extern const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_NoPadding;
extern const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method1;
extern const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method2;
extern const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingPKCS7;
#endif /* MCUXCL_FEATURE_MACMODES_CBCMAC_SM4 */



/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAMACMODES_ALGORITHMS_H_ */
