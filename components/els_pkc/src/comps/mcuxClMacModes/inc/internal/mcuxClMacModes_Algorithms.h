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

/** @file  mcuxClMacModes_Algorithms.h
 *  @brief Internal header for the MAC context for modes using the SGI
 */

#ifndef MCUXCLMACMODES_ALGORITHMS_H_
#define MCUXCLMACMODES_ALGORITHMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMacModes_Els_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Common mode and algorithm descriptors
 */
extern const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CMAC;
extern const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_NoPadding;
extern const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method1;
extern const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method2;
extern const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_Padding_PKCS7;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_ALGORITHMS_H_ */
