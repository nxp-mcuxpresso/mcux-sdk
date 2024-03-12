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

/** @file  mcuxClOsccaCipherModes_Algorithms.h
 *  @brief Supported algorithms for the mcuxClOsccaCipherModes component
 */

#ifndef MCUXCLOSCCACIPHERMODES_ALGORITHMS_H_
#define MCUXCLOSCCACIPHERMODES_ALGORITHMS_H_

#include <internal/mcuxClOsccaCipherModes_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup mcuxClOsccaCipherModes_Algorithms Cipher algorithm definitions
 * @brief Modes used by the Cipher operations.
 * @ingroup mcuxClOsccaCipherModes
 * @{
 */
#ifdef MCUXCL_FEATURE_CIPHERMODES_SM4

/**
 * @brief SM4 ECB Encryption algorithm descriptor without padding, using OSCCA SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_NoPadding;

/**
 * @brief SM4 ECB Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 1, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingISO9797_1_Method1;

/**
 * @brief SM4 ECB Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 2, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingISO9797_1_Method2;

/**
 * @brief SM4 ECB Encryption algorithm descriptor with PKCS7 padding method, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Enc_PaddingPKCS7;

/**
 * @brief SM4 ECB Decryption algorithm descriptor, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_ECB_Dec;

/**
 * @brief SM4 CBC Encryption algorithm descriptor without padding, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_NoPadding;

/**
 * @brief SM4 CBC Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 1, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingISO9797_1_Method1;

/**
 * @brief SM4 CBC Encryption algorithm descriptor with ISO/IEC 9797-1 padding method 2, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingISO9797_1_Method2;

/**
 * @brief SM4 CBC Encryption algorithm descriptor with PKCS7 padding method, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Enc_PaddingPKCS7;

/**
 * @brief SM4 CBC Decryption algorithm descriptor, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CBC_Dec;

/**
 * @brief SM4 CTR Encryption algorithm descriptor without padding, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CTR_Enc;

/**
 * @brief SM4 CTR Decryption algorithm descriptor, using SM4
 */
extern const mcuxClCipherModes_AlgorithmDescriptor_SM4_t mcuxClOsccaCipherModes_AlgorithmDescriptor_SM4_CTR_Dec;


#endif /* MCUXCL_FEATURE_CIPHERMODES_SM4 */
/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCACIPHERMODES_ALGORITHMS_H_ */
