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

/** @file  mcuxClCipherModes_Modes.c
 *  @brief Definition of the mode descriptors for all provided Cipher modes
 */

#include <mcuxClCore_Analysis.h>
#include <mcuxClCipherModes_Modes.h>
#include <internal/mcuxClCipherModes_Internal.h>
#include <internal/mcuxClCipher_Internal.h>

MCUXCLCORE_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
/*
 * Crypt Modes using the ELS
 */
/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_NoPadding = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_NoPadding_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1 = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2 = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Dec = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Dec_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};


const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingPKCS7 =
{
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingPKCS7_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};



/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_NoPadding = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_NoPadding_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1 = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2 = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};


const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingPKCS7 =
{
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingPKCS7_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};


const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Dec = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Dec_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CTR = {
    .crypt = mcuxClCipherModes_SkeletonAes,
    .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes),
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
    .pAlgorithm = (void *) &mcuxClCipherModes_AlgorithmDescriptor_AES_CTR_Els
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

MCUXCLCORE_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
