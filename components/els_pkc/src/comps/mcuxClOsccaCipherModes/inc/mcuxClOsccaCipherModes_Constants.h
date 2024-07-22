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

/** @file  mcuxClOsccaCipherModes_Constants.h
 *  @brief Supported constants for the mcuxClOsccaCipherModes component
 */

#ifndef MCUXCLOSCCACIPHERMODES_CONSTANTS_H_
#define MCUXCLOSCCACIPHERMODES_CONSTANTS_H_

#include <mcuxCsslAnalysis.h>
#include <mcuxClCipher_Types.h>
#include <mcuxCsslAnalysis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClOsccaCipherModes constants definitions
 * @brief Constants used by the Cipher operations.
 * @ingroup mcuxClOsccaCipherModes
 * @{
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_NoPadding;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_ECB_ENC_NoPadding =
  &mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_NoPadding;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method1;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_ECB_ENC_PaddingISO9797_1_Method1 =
  &mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method1;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method2;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_ECB_ENC_PaddingISO9797_1_Method2 =
  &mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingISO9797_1_Method2;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingPKCS7;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_ECB_ENC_PaddingPKCS7 =
  &mcuxClOscca_Cipher_ModeDesc_SM4_ECB_ENC_PaddingPKCS7;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_ECB_DEC;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_ECB_DEC =
  &mcuxClOscca_Cipher_ModeDesc_SM4_ECB_DEC;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_NoPadding;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CBC_ENC_NoPadding =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_NoPadding;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method1;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CBC_ENC_PaddingISO9797_1_Method1 =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method1;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method2;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CBC_ENC_PaddingISO9797_1_Method2 =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingISO9797_1_Method2;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingPKCS7;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CBC_ENC_PaddingPKCS7=
  &mcuxClOscca_Cipher_ModeDesc_SM4_CBC_ENC_PaddingPKCS7;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CBC_DEC;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CBC_DEC =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CBC_DEC;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CTR_ENC;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CTR_ENC =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CTR_ENC;

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM4_CTR_DEC;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
static mcuxClCipher_Mode_t mcuxClOscca_Cipher_Mode_SM4_CTR_DEC =
  &mcuxClOscca_Cipher_ModeDesc_SM4_CTR_DEC;


MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCACIPHERMODES_CONSTANTS_H_ */
