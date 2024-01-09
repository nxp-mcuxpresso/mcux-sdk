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

/** @file  mcuxClCipherModes_Algorithms_Els.h
 *  @brief Supported algorithms for the mcuxClCipherModes component
 */

#ifndef MCUXCLCIPHERMODES_ALGORITHMS_ELS_H_
#define MCUXCLCIPHERMODES_ALGORITHMS_ELS_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClCipherModes_Internal_Types_Els.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup clCipherModesAlgorithms Cipher algorithm definitions
 * @brief Modes used by the Cipher operations.
 * @ingroup mcuxClCipherModes
 * @{
 */

/**
 * @brief AES ECB Encryption algorithm descriptor without padding, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_NoPadding_Els;

/**
 * @brief AES ECB Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 1, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1_Els;

/**
 * @brief AES ECB Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 2, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2_Els;


/**
 * @brief AES ECB Encryption algorithm descriptor with PKCS7 padding, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingPKCS7_Els;


/**
 * @brief AES ECB Decryption algorithm descriptor, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Dec_Els;


/**
 * @brief AES CBC Encryption algorithm descriptor without padding, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_NoPadding_Els;

/**
 * @brief AES CBC Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 1, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1_Els;

/**
 * @brief AES CBC Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 2, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2_Els;


/**
 * @brief AES CBC Encryption algorithm descriptor with PKCS7 padding, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingPKCS7_Els;


/**
 * @brief AES CBC Decryption algorithm descriptor, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Dec_Els;


/**
 * @brief CTR Encryption/Decryption algorithm descriptor, using ELS
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CTR_Els;


/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHERMODES_ALGORITHMS_ELS_H_ */
