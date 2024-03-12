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

/** @file  mcuxClOsccaSm2_KeyTypes.c
 *  @brief Instantiation of the key types supported by the mcuxClOsccaSm2 component. */

#include <mcuxClKey_Constants.h>
#include <mcuxClKey_Types.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <mcuxClOsccaSm2.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to set the generic pointer.")
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Std_Public = {.algoId = (MCUXCLKEY_ALGO_ID_SM2 + MCUXCLKEY_ALGO_ID_PUBLIC_KEY), .size = MCUXCLOSCCASM2_SM2P256_SIZE_PUBLICKEY, .info =(void*) &mcuxClOsccaSm2_DomainParams_SM2P256_Std};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Std_Private = {.algoId = (MCUXCLKEY_ALGO_ID_SM2 + MCUXCLKEY_ALGO_ID_PRIVATE_KEY), .size = MCUXCLOSCCASM2_SM2P256_SIZE_PRIVATEKEY, .info =(void*) &mcuxClOsccaSm2_DomainParams_SM2P256_Std};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Ext_Public = {.algoId = (MCUXCLKEY_ALGO_ID_SM2 + MCUXCLKEY_ALGO_ID_PUBLIC_KEY), .size = MCUXCLOSCCASM2_SM2P256_SIZE_PUBLICKEY,.info = (void*) &mcuxClOsccaSm2_DomainParams_SM2P256_Ext};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Ext_Private = {.algoId = (MCUXCLKEY_ALGO_ID_SM2 + MCUXCLKEY_ALGO_ID_PRIVATE_KEY), .size = MCUXCLOSCCASM2_SM2P256_SIZE_PRIVATEKEY, .info =(void*) &mcuxClOsccaSm2_DomainParams_SM2P256_Ext};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
