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

/** @file  mcuxClHmac_Modes.c
 *  @brief Definition of the mode descriptors for all provided HMAC modes
 */

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClHmac_Constants.h>
#include <mcuxClHmac_Modes.h>
#include <internal/mcuxClHmac_Internal_Types.h>
#include <internal/mcuxClHmac_Internal_Functions.h>

/**
 *  Constant top-level mode descriptors and common mode descriptors for custom modes
 */

/*
 * Common mode descriptor needed for constructor of HMAC mode
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_CommonModeDescriptor_t mcuxClHmac_CommonModeDescriptor_Sw = {
    .compute = mcuxClHmac_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_compute),
    .init = mcuxClHmac_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_init),
    .process = mcuxClHmac_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_process),
    .finish = mcuxClHmac_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_finish),
    .macByteSize = 0u, /* To be set by create function */
    .pAlgorithm = (void *) &mcuxClHmac_AlgorithmDescriptor_Sw
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 *  Top-level mode structure for HMAC using ELS
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClHmac_ModeDescriptor_SHA2_256_ELS = {
  .common = {
    .compute = mcuxClHmac_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_compute),
    .init = mcuxClHmac_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_init),
    .process = mcuxClHmac_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_process),
    .finish = mcuxClHmac_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_finish),
    .macByteSize = MCUXCLHMAC_ELS_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClHmac_AlgorithmDescriptor_Els
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

