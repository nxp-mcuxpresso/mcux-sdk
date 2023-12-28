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

/**
 * @file  mcuxClPadding_Functions_Internal.h
 * @brief Functions of the padding component.
 */

#ifndef MCUXCLPADDING_FUNCTIONS_INTERNAL_H
#define MCUXCLPADDING_FUNCTIONS_INTERNAL_H

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClPadding_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif



/**
 * @brief No-padding function, which adds no padding at all
 * @api
 *
 * This function throws an error if @p lastBlockLength is anything other than zero,
 * and does nothing (adding no padding) and returns OK otherwise.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes
 *                              in @p pIn. Must be 0.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_None, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_None(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);


/**
 * @brief Zero-padding function, which pads a block with zeroes in the end.
 * @api
 *
 * This function copies @p lastBlockLength bytes to @p pOut and fills the
 * remainder with zeroes.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes
 *                              in @p pIn. Must be smaller than @p blockLength.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_ISO9797_1_Method1, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_ISO9797_1_Method1(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);

/**
 * @brief ISO/IEC 9797-1 padding method 2 function.
 * @api
 *
 * This function adds a single bit with value 1 after the data and fills the
 * remaining block with zeroes.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes
 *                              in @p pIn. Must be smaller than @p blockLength.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_ISO9797_1_Method2, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_ISO9797_1_Method2(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);

/**
 * @brief ISO/IEC 9797-1 padding method 2 function.
 * @api
 *
 * This function adds a single bit with value 1 after the data and fills the
 * remaining block with zeroes for CMAC and XCBCMAC mode using.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes
 *                              in @p pIn. Must be smaller than or equal to @p blockLength.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_MAC_ISO9797_1_Method2, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_MAC_ISO9797_1_Method2(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);
/**
 * @brief PKCS7 padding function.
 * @api
 *
 * This function adds PKCS7 padding according to rfc2315, it adds the remaning
 * bytes in the block with the value equal to the total number of added bytes.
 * The random masking byte depends on a call to @ref mcuxClRandom_ncInit.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes
 *                              in @p pIn. Must be smaller than @p blockLength.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_PKCS7, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_PKCS7(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);

/**
 * @brief Random-padding function, which pads a block with random bytes in the end.
 * @api
 *
 * This function copies @p lastBlockLength bytes to @p pOut and fills the
 * remainder with random bytes.
 * The random bytes depend on a call to @ref mcuxClRandom_ncInit.
 *
 * @param[in]  blockLength      The block length of the used block cipher.
 *
 * @param[in]  pIn              Pointer to the input buffer of the block that will
 *                              be padded.
 * @param[in]  lastBlockLength  Number of bytes in the last block, i.e. the number of bytes in
 *                              @p pIn. Must be greater than 0 and less than or equal to @p blockLength.
 * @param[in]  totalInputLength Total number of plaintext/ciphertext bytes.
 *
 * @param[out] pOut             Pointer to the output buffer where the padded data
 *                              needs to be written.
 * @param[out] pOutLength       Length of the data written to @p pOut, including the padding.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPadding_addPadding_Random, mcuxClPadding_addPaddingMode_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPadding_Status_t) mcuxClPadding_addPadding_Random(
  uint32_t blockLength,
  const uint8_t * const pIn,
  uint32_t lastBlockLength,
  uint32_t totalInputLength,
  uint8_t * const pOut,
  uint32_t * const pOutLength
);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPADDING_FUNCTIONS_INTERNAL_H */

