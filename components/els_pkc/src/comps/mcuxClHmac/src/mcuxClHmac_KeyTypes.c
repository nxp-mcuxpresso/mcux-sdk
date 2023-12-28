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

/** @file  mcuxClHmac_KeyTypes.c
 *  @brief Instantiation of the key types supported by the mcuxClHmac component. */

#include <mcuxClKey.h>
#include <mcuxClHmac_KeyTypes.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <mcuxCsslAnalysis.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
// HMAC internal only supports 256-bit keys
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256 = {.algoId = MCUXCLKEY_ALGO_ID_HMAC + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, .size = MCUXCLKEY_SIZE_256, .info = NULL};

const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Hmac_variableLength = {.algoId = MCUXCLKEY_ALGO_ID_HMAC + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, .size = 0u, .info = NULL};

MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
