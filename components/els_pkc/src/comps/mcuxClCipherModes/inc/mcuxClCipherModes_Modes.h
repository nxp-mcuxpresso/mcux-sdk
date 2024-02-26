/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClCipherModes_Modes.h
 *  @brief Supported modes for the mcuxClCipher component
 */

#ifndef MCUXCLCIPHERMODES_MODES_H_
#define MCUXCLCIPHERMODES_MODES_H_

#include <mcuxClCipher_Types.h>

#include <mcuxCsslAnalysis.h>

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup clCipherModes Cipher mode definitions
 * @brief Modes used by the Cipher operations.
 * @ingroup mcuxClCipher
 * @{
 */

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")

/*
 * Crypt Modes using the ELS
 */
/**
 * @brief AES ECB Encryption mode descriptor without padding
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_NoPadding;

/**
 * @brief AES ECB Encryption mode without padding
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_ECB_Enc_NoPadding =
  &mcuxClCipher_ModeDescriptor_AES_ECB_Enc_NoPadding;

/**
 * @brief AES ECB Encryption mode descriptor with ISO/IEC 9797-1 padding method 1
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1;

/**
 * @brief AES ECB Encryption mode with ISO/IEC 9797-1 padding method 1
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_ECB_Enc_PaddingISO9797_1_Method1 =
  &mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1;

/**
 * @brief AES ECB Encryption mode descriptor with ISO/IEC 9797-1 padding method 2
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2;

/**
 * @brief AES ECB Encryption mode with ISO/IEC 9797-1 padding method 2
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_ECB_Enc_PaddingISO9797_1_Method2 =
  &mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2;

/**
 * @brief AES ECB Encryption mode descriptor with PKCS7 padding
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingPKCS7;

/**
 * @brief AES ECB Encryption mode with PKCS7 padding
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_ECB_Enc_PaddingPKCS7 =
  &mcuxClCipher_ModeDescriptor_AES_ECB_Enc_PaddingPKCS7;

/**
 * @brief AES ECB Decryption mode descriptor
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_ECB_Dec;

/**
 * @brief AES ECB Decryption mode
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_ECB_Dec_NoPadding =
  &mcuxClCipher_ModeDescriptor_AES_ECB_Dec;

/**
 * @brief AES CBC Encryption mode descriptor without padding
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_NoPadding;

/**
 * @brief AES CBC Encryption mode without padding
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CBC_Enc_NoPadding =
  &mcuxClCipher_ModeDescriptor_AES_CBC_Enc_NoPadding;

/**
 * @brief AES CBC Encryption mode descriptor with ISO/IEC 9797-1 padding method 1
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1;

/**
 * @brief AES CBC Encryption mode with ISO/IEC 9797-1 padding method 1
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CBC_Enc_PaddingISO9797_1_Method1 =
  &mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1;

/**
 * @brief AES CBC Encryption mode descriptor with ISO/IEC 9797-1 padding method 2
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2;

/**
 * @brief AES CBC Encryption mode with ISO/IEC 9797-1 padding method 2
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CBC_Enc_PaddingISO9797_1_Method2 =
  &mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2;

/**
 * @brief AES CBC Encryption mode descriptor with PKCS7 padding
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingPKCS7;

/**
 * @brief AES CBC Encryption mode with PKCS7 padding
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CBC_Enc_PKCS7 =
  &mcuxClCipher_ModeDescriptor_AES_CBC_Enc_PaddingPKCS7;

/**
 * @brief AES CBC Decryption mode descriptor
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CBC_Dec;

/**
 * @brief AES CBC Decryption mode
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CBC_Dec_NoPadding =
  &mcuxClCipher_ModeDescriptor_AES_CBC_Dec;

/**
 * @brief CTR Encryption/Decryption mode descriptor
 */
extern const mcuxClCipher_ModeDescriptor_t mcuxClCipher_ModeDescriptor_AES_CTR;

/**
 * @brief CTR Encryption/Decryption mode
 */
static mcuxClCipher_Mode_t mcuxClCipher_Mode_AES_CTR =
  &mcuxClCipher_ModeDescriptor_AES_CTR;



MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHERMODES_MODES_H_ */

