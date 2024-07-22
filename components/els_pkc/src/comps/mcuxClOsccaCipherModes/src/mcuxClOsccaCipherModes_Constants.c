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

/** @file  mcuxClOsccaCipherModes_Constants.c
 *  @brief Definition of the constants descriptors for all provided Cipher modes */

#include <mcuxCsslAnalysis.h>
#include <mcuxClOsccaCipherModes_Constants.h>
#include <internal/mcuxClOsccaCipherModes_Internal_Types.h>
#include <internal/mcuxClOsccaCipherModes_Internal_Functions.h>
#include <internal/mcuxClOsccaCipherModes_Algorithms.h>
#include <internal/mcuxClCipher_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
#ifdef MCUXCL_FEATURE_CIPHERMODES_SM4

static const mcuxClCipher_ModeFunctions_t mcuxClOscca_CipherModeFunctions_OsccaCipherModes = {
  .crypt = mcuxClOsccaCipherModes_SkeletonSM4,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4),
};


const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_NoPadding = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_NoPadding
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method1 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingISO9797_1_Method1
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method2 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingISO9797_1_Method2
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingPKCS7 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingPKCS7
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_DEC = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Dec
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_NoPadding = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_NoPadding
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method1 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingISO9797_1_Method1
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method2 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingISO9797_1_Method2
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingPKCS7 = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingPKCS7
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_DEC = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Dec
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CTR_ENC = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CTR_Enc
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CTR_DEC = {
    .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaCipherModes,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CTR_Dec
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};



#endif /* MCUXCL_FEATURE_CIPHERMODES_SM4 */
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
