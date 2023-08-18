/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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

/** @file  mcuxClKey_KeyTypes.c
 *  @brief Instantiation of the key types supported by the mcuxClKey component. */

#include <stddef.h>
#include <mcuxClKey.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <mcuxClCore_Analysis.h>

MCUXCLCORE_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
// Only support ELS internal keys, only supports 256 bits HMAC keys
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256_variableLength = {.algoId = MCUXCLKEY_ALGO_ID_HMAC + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, .size = 0u, .info = NULL};

/* key types supported by coprocessor keystore only */
// HMAC internal only supports 256-bit keys
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256 = {.algoId = MCUXCLKEY_ALGO_ID_HMAC + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, .size = MCUXCLKEY_SIZE_256, .info = NULL};

MCUXCLCORE_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
