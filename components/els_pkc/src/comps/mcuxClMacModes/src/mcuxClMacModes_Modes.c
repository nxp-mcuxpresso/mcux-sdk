/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClMacModes_Modes.c
 *  @brief Definition of the mode descriptors for all provided MAC modes
 */

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClMacModes_MemoryConsumption.h>
#include <mcuxClMacModes_Constants.h>
#include <mcuxClMacModes_Modes.h>
#include <internal/mcuxClMacModes_Algorithms.h>
#include <internal/mcuxClMacModes_Internal_Functions.h>

/**
 *  Constant top-level mode descriptors and common mode descriptors for custom modes
 */


/**
 *  Top-level mode structure for CMAC
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CMAC = {
  .common = {
    .compute = mcuxClMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_compute),
    .init = mcuxClMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_init),
    .process = mcuxClMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_process),
    .finish = mcuxClMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_finish),
    .macByteSize = MCUXCLMAC_CMAC_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClMacModes_AlgorithmDescriptor_CMAC
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()


/**
 *  Top-level mode structure for CBCMAC without padding
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_NoPadding = {
    .common = {
    .compute = mcuxClMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_compute),
    .init = mcuxClMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_init),
    .process = mcuxClMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_process),
    .finish = mcuxClMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_finish),
    .macByteSize = MCUXCLMAC_CBCMAC_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClMacModes_AlgorithmDescriptor_CBCMAC_NoPadding
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
/**
 *  Top-level mode structure for CBCMAC using ISO9797-1 Method 1 Padding
 */
/* MISRA Ex. 20 - Rule 5.1 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1 = {
  .common = {
    .compute = mcuxClMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_compute),
    .init = mcuxClMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_init),
    .process = mcuxClMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_process),
    .finish = mcuxClMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_finish),
    .macByteSize = MCUXCLMAC_CBCMAC_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method1
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 *  Top-level mode structure forCBCMAC using ISO9797-1 Method 2 Padding
 */
/* MISRA Ex. 20 - Rule 5.1 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2 = {
  .common = {
    .compute = mcuxClMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_compute),
    .init = mcuxClMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_init),
    .process = mcuxClMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_process),
    .finish = mcuxClMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_finish),
    .macByteSize = MCUXCLMAC_CBCMAC_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method2
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 *  Top-level mode structure for CBCMAC using PKCS7 Padding
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_Padding_PKCS7 = {
  .common = {
    .compute = mcuxClMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_compute),
    .init = mcuxClMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_init),
    .process = mcuxClMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_process),
    .finish = mcuxClMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_finish),
    .macByteSize = MCUXCLMAC_CBCMAC_OUTPUT_SIZE,
    .pAlgorithm = (void *) &mcuxClMacModes_AlgorithmDescriptor_CBCMAC_Padding_PKCS7
  },
  .pCustom = NULL
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

