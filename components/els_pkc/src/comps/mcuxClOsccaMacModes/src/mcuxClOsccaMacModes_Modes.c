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

/** @file  mcuxClOsccaMacModes_Modes.c
 *  @brief Definition of the mode descriptors for all provided MAC modes
 */

#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <mcuxClOsccaMacModes_Constants.h>
#include <internal/mcuxClOsccaMacModes_Internal_Functions.h>
#include <internal/mcuxClOsccaMacModes_Types.h>
#include <internal/mcuxClOsccaMacModes_Algorithms.h>
#include <mcuxClOsccaMacModes_Modes.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CMAC = {
  .common = {
    .compute = mcuxClOsccaMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_compute),
    .init = mcuxClOsccaMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_init),
    .process = mcuxClOsccaMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_process),
    .finish = mcuxClOsccaMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_finish),
    .macByteSize = MCUXCLOSCCASM4_CMAC_OUTPUT_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaMacModes_AlgorithmDescriptor_CMAC_SM4
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  },
  .pCustom = NULL
};
#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */

#ifdef MCUXCL_FEATURE_MACMODES_CBCMAC_SM4
const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_NoPadding = {
  .common = {
    .compute = mcuxClOsccaMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_compute),
    .init = mcuxClOsccaMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_init),
    .process = mcuxClOsccaMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_process),
    .finish = mcuxClOsccaMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_finish),
    .macByteSize = MCUXCLOSCCASM4_CBCMAC_OUTPUT_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_NoPadding
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  },
  .pCustom = NULL
};

const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1 = {
  .common = {
    .compute = mcuxClOsccaMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_compute),
    .init = mcuxClOsccaMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_init),
    .process = mcuxClOsccaMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_process),
    .finish = mcuxClOsccaMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_finish),
    .macByteSize = MCUXCLOSCCASM4_CBCMAC_OUTPUT_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method1
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  },
  .pCustom = NULL
};

const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2 = {
  .common = {
    .compute = mcuxClOsccaMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_compute),
    .init = mcuxClOsccaMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_init),
    .process = mcuxClOsccaMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_process),
    .finish = mcuxClOsccaMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_finish),
    .macByteSize = MCUXCLOSCCASM4_CBCMAC_OUTPUT_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method2
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  },
  .pCustom = NULL
};
const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_Padding_PKCS7 = {
  .common = {
    .compute = mcuxClOsccaMacModes_compute,
    .protectionToken_compute = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_compute),
    .init = mcuxClOsccaMacModes_init,
    .protectionToken_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_init),
    .process = mcuxClOsccaMacModes_process,
    .protectionToken_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_process),
    .finish = mcuxClOsccaMacModes_finish,
    .protectionToken_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_finish),
    .macByteSize = MCUXCLOSCCASM4_CBCMAC_OUTPUT_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingPKCS7
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
  },
  .pCustom = NULL
};
#endif /* MCUXCL_FEATURE_MACMODES_CBCMAC_SM4 */

MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
