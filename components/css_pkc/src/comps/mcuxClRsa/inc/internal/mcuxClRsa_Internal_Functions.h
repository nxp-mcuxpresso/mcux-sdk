/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClRsa_Internal_Functions.h
 *  @brief Internal functions of the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_FUNCTIONS_H_
#define MCUXCLRSA_INTERNAL_FUNCTIONS_H_

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClHash.h>
#include <mcuxClRsa_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClRsa_Internal_Functions mcuxClRsa_Internal_Functions
 * @brief Defines all internal functions of @ref mcuxClRsa
 * @ingroup mcuxClRsa
 * @{
 */

/**
 * \brief RSA public operation
 *
 * This function performs an RSA public key operation according to PKCS #1 v2.2.
 * The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8.
 * The public exponent is limited to 2 <= e < N.
 *
 * \param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * \param[in]  pKey                 Pointer to key structure of type @ref mcuxClRsa_Key
 * \param[in]  pInput               Pointer to input
 * \param[out] pOutput              Pointer to result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pKey:</dt>
 *          <dd>The key entries meet the following conditions:
 *              - Entry keytype must be set to #MCUXCLRSA_KEY_PUBLIC. In case of passing another key type, the function
 *                returns #MCUXCLRSA_STATUS_INVALID_INPUT. The functions checks, internally, whether the required key entries
 *                are not set to NULL. If so, the function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *              - The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8;
 *              - It is required that e is greater or equal to 2 and smaller than n.
 *      <dt>pInput:</dt>
 *          <dd>The input must meet the following conditions:
 *               - It is provided in big-endian byte order;
 *               - The input length is determined by the modulus length.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - It is located in PKC RAM;
 *               - A buffer of modulus length bytes has to be allocated;
 *               - The result is stored in little-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_public operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK    The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT        The input parameters are not valid.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_public)
mcuxClRsa_Status_Protected_t mcuxClRsa_public(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  const uint8_t * const      pInput,
  uint8_t * const            pOutput
);

/**
 * \brief RSA private plain operation
 *
 * This function performs an RSA private plain key operation according to PKCS #1 v2.2.
 * The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8.
 * The private exponent is limited to d < N.
 *
 * \param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * \param[in]  pKey                 Pointer to key structure of type @ref mcuxClRsa_Key
 * \param[in]  pInput               Pointer to input
 * \param[out] pOutput              Pointer to result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pKey:</dt>
 *          <dd>The key entries meet the following conditions:
 *              - Entry keytype must be set to #MCUXCLRSA_KEY_PRIVATEPLAIN. In case of passing another key type, the function
 *                returns #MCUXCLRSA_STATUS_INVALID_INPUT. The functions checks, internally, whether the required key entries
 *                are not set to NULL. If so, the function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *              - The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8;
 *              - It is required that d is smaller than n.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is located in PKC RAM;
 *               - It is provided in little-endian byte order;
 *               - The input length is determined by the modulus length.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated;
 *               - The result is stored in big-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_privatePlain operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK    The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT        The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_privatePlain)
mcuxClRsa_Status_Protected_t mcuxClRsa_privatePlain(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  const uint8_t * const      pInput,
  uint8_t * const            pOutput
);

/**
 * \brief RSA private CRT operation
 *
 * This function performs an RSA private CRT key operation according to PKCS #1 v2.2.
 * The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8.
 * The length of the primes is limited to: size(p) = size(q) = 1/2 size(n).
 * The private exponent is limited to d < N.
 *
 * \param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * \param[in]  pKey                 Pointer to key structure of type @ref mcuxClRsa_Key
 * \param[in]  pInput               Pointer to input
 * \param[out] pOutput              Pointer to result
 *
 ** <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pKey:</dt>
 *          <dd>The key entries meet the following conditions:
 *              - Entry keytype must be set to #MCUXCLRSA_KEY_PRIVATECRT or #MCUXCLRSA_KEY_PRIVATECRT_DFA. In case of passing
 *                another key type, the function returns #MCUXCLRSA_STATUS_INVALID_INPUT. The functions checks, internally,
 *                whether the required key entries are not set to NULL. If so, the function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *              - The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8;
 *              - The length of the primes is limited to: size(p) = size(q) = 1/2 size(n);
 *              - It is required that d is smaller than n.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is located in PKC RAM;
 *               - It is provided in little-endian byte order;
 *               - The input length is determined by the modulus length.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated;
 *               - The result is stored in big-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_privateCRT operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK    The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT        The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_privateCRT)
mcuxClRsa_Status_Protected_t mcuxClRsa_privateCRT(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  const uint8_t * const      pInput,
  uint8_t * const            pOutput
);

/**
 * @brief No encoding operation
 *
 * This function is used to implement the RSASP1 primitive of PKCS #1 v2.2, i.e. signature
 * generation, without prior padding.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput               Pointer to input
 * @param[in]  inputLength          RFU: please set to zero
 * @param[in]  pVerificationInput   RFU: please set to NULL
 * @param[in]  pHashAlgo            RFU: please set to NULL
 * @param[in]  pLabel               RFU: please set to NULL
 * @param[in]  saltlabelLength      RFU: please set to zero
 * @param[in]  keyBitLength         Bit-length of modulus (bit-length of encoded message). Note: This function only supports moduli, whose bit-length is a multiple of 8
 * @param[in]  options              RFU: please set to zero
 * @param[out] pOutput              Pointer to buffer, which contains the result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is provided in big-endian byte order;
 *               - The input length is determined by the BYTE_LENGTH(keyBitLength).
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated in PKC RAM;
 *               - The result is stored in little-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_noEncode operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK    The function executed successfully.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_noEncode)
mcuxClRsa_Status_Protected_t mcuxClRsa_noEncode(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);

/**
 * @brief No verify operation
 *
 * This function is used to implement the RSAVP1 primitive of PKCS #1 v2.2, i.e. signature
 * a call to the public exponentiation, without padding verification and digest comparison.
 *
 * @param[in]  pSession                Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput                  RFU: please set to NULL
 * @param[in]  inputLength             RFU: please set to zero
 * @param[in]  pVerificationInput      Pointer to input
 * @param[in]  pHashAlgo               RFU: please set to NULL
 * @param[in]  pLabel                  RFU: please set to NULL
 * @param[in]  saltlabelLength         RFU: please set to zero
 * @param[in]  keyBitLength            Bit-length of modulus (bit-length of encoded message). Note: This function only supports moduli, whose bit-length is a multiple of 8
 * @param[in]  options                 RFU: please set to zero
 * @param[out] pOutput                 Pointer to buffer, which contains the result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pVerificationInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is located in PKC RAM;
 *               - It is provided in little-endian byte order;
 *               - The input length is determined by the BYTE_LENGTH(keyBitLength).
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated;
 *               - The result is stored in big-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_noVerify operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_STATUS_VERIFYPRIMITIVE_OK  The function executed successfully.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_noVerify)
mcuxClRsa_Status_Protected_t mcuxClRsa_noVerify(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);

/**
 * @brief RSA PSS mask generation function
 *
 * This function is used to implement the mask generation function MGF1 of PKCS #1 v2.2.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pHashAlgo            Pointer to hash algorithm information
 * @param[in]  pInput               Pointer to seed, of which the mask is generated
 * @param[in]  inputLength          Length of seed, of which mask is generated
 * @param[in]  outputLength         Length of mask to be generated
 * @param[out] pOutput              Pointer to result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pHashAlgo:</dt>
 *          <dd>Specifies the targeted hash algorithm, to be used for the mask generation function operation.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is located in PKC RAM.
 *      <dt>inputLength:</dt>
 *          <dd>Byte-length of the seed, of which the mask is generated.
 *      <dt>outputLength:</dt>
 *          <dd>Byte-length of mask, which is generated.
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of outputLength bytes has to be allocated.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_mgf1 operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_MGF_OK      The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_ERROR                An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_mgf1)
mcuxClRsa_Status_Protected_t mcuxClRsa_mgf1(
  mcuxClSession_Handle_t       pSession,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pInput,
  const uint32_t              inputLength,
  const uint32_t              outputLength,
  uint8_t *                   pOutput
);

/**
 * @brief RSA PSS Encoding operation
 *
 * This function performs an RSA PSS encoding operation according to EMSA-PSS-ENCODE of PKCS #1 v2.2.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput               Pointer to buffer, which contains the message or message digest to be encoded
 * @param[in]  inputLength          Size of Input
 * @param[in]  pVerificationInput   RFU: please set to NULL
 * @param[in]  pHashAlgo            Pointer to hash algorithm information
 * @param[in]  pLabel               RFU: please set to NULL
 * @param[in]  saltlabelLength      Byte-length of salt
 * @param[in]  keyBitLength         Bit-length of key (bit-length of encoded message).  Note: This function only supports moduli, whose bit-length is a multiple of 8
 * @param[in]  options              Options field
 * @param[out] pOutput              Pointer to result
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is provided in big-endian byte order.
 *      <dt>inputLength:</dt>
 *          <dd>Specifies the size of the buffer pointed to by pInput in case of option MCUXCLRSA_OPTION_MESSAGE_PLAIN. In case of option MCUXCLRSA_OPTION_MESSAGE_DIGEST,
 *               this buffer size is specified by the targeted hash algorithm. Thus for MCUXCLRSA_OPTION_MESSAGE_DIGEST, please set inputLength to zero.
 *      <dt>pHashAlgo:</dt>
 *          <dd>Specifies the targeted hash algorithm, to be used for the mask generation function operation.
 *      <dt>saltlabelLength:</dt>
 *          <dd>Byte-length salt.
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:   Specify, whether pInput is provided as plain message (MCUXCLRSA_OPTION_MESSAGE_PLAIN) to be hashed
 *                                                    internally by the mcuxClRsa_pssEncode function, or as message digest (MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated in PKC RAM;
 *               - The result is stored in little-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_pssEncode operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK   The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT        The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_pssEncode)
mcuxClRsa_Status_Protected_t mcuxClRsa_pssEncode(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);

/**
 * @brief RSA PSS verification operation
 *
 * This function performs an RSA PSS verification operation according to EMSA-PSS-VERIFY of PKCS #1 v2.2.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput               Pointer to buffer, which contains the message or message digest to be verified
 * @param[in]  inputLength          Size of Input
 * @param[in]  pVerificationInput   Pointer to buffer, which contains the encoded message digest to be verified
 * @param[in]  pHashAlgo            Pointer to hash algorithm information
 * @param[in]  pLabel               RFU: please set to NULL
 * @param[in]  saltlabelLength      Byte-length of salt
 * @param[in]  keyBitLength         Bit-length of key (bit-length of encoded message).  Note: This function only supports moduli, whose bit-length is a multiple of 8.
 * @param[in]  options              Options field
 * @param[out] pOutput              RFU: please set to NULL
 *
 *<dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is provided in big-endian byte order.
 *      <dt>inputLength:</dt>
 *          <dd>Specifies the size of the buffer pointed to by pInput in case of option MCUXCLRSA_OPTION_MESSAGE_PLAIN. In case of option MCUXCLRSA_OPTION_MESSAGE_DIGEST,
 *               this buffer size is specified by the targeted hash algorithm. Thus for MCUXCLRSA_OPTION_MESSAGE_DIGEST, please set inputLength to zero.
 *     <dt>pVerificationInput:</dt>
 *          <dd>The padded message meets the following conditions:
 *               - It is located in PKC RAM;
 *               - It is provided in little-endian byte order.
 *      <dt>pHashAlgo:</dt>
 *          <dd>Specifies the targeted hash algorithm, to be used for the mask generation function operation.
 *      <dt>saltlabelLength:</dt>
 *          <dd>Byte-length salt.
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:   Specify, whether pInput is provided as plain message (MCUXCLRSA_OPTION_MESSAGE_PLAIN) to be hashed
 *                                                    internally by the mcuxClRsa_pssVerify function, or as message digest (MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_pssVerify operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_STATUS_VERIFY_OK        The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_VERIFY_FAILED    The verification failed.
 * @retval #MCUXCLRSA_STATUS_ERROR            An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_pssVerify)
mcuxClRsa_Status_Protected_t mcuxClRsa_pssVerify(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);

/**
 * @brief RSA PKCS1-v1_5 Encoding operation
 *
 * This function performs an RSA PKCS1-v1_5 encoding operation according to EMSA-PKCS1-v1_5-ENCODE of PKCS #1 v2.2.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput               Pointer to buffer, which contains the message or message digest to be encoded
 * @param[in]  inputLength          Size of Input
 * @param[in]  pVerificationInput   RFU: please set to NULL
 * @param[in]  pHashAlgo            Pointer to hash algorithm information
 * @param[in]  pLabel               RFU: please set to NULL
 * @param[in]  saltlabelLength      RFU: please set to zero
 * @param[in]  keyBitLength         Bit-length of key (bit-length of encoded message).  Note: This function only supports moduli, whose bit-length is a multiple of 8
 * @param[in]  options              Options field
 * @param[out] pOutput              Pointer to result
 *
 *<dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is provided in big-endian byte order.
 *      <dt>inputLength:</dt>
 *          <dd>Specifies the size of the buffer pointed to by pInput in case of option MCUXCLRSA_OPTION_MESSAGE_PLAIN. In case of option MCUXCLRSA_OPTION_MESSAGE_DIGEST,
 *               this buffer size is specified by the targeted hash algorithm. Thus for MCUXCLRSA_OPTION_MESSAGE_DIGEST, please set inputLength to zero.
 *      <dt>pHashAlgo:</dt>
 *          <dd>Specifies the targeted hash algorithm, to be used for the mask generation function operation.
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:   Specify, whether pInput is provided as plain message (MCUXCLRSA_OPTION_MESSAGE_PLAIN) to be hashed
 *                                                    internally by the mcuxClRsa_pkcs1v15Encode function, or as message digest (MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *      <dt>pOutput:</dt>
 *          <dd>The output meets the following conditions:
 *               - A buffer of modulus length bytes has to be allocated in PKC RAM;
 *               - The result is stored in little-endian byte order in the buffer pointed to by pOutput.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_pkcs1v15Encode operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK   The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT        The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_pkcs1v15Encode)
mcuxClRsa_Status_Protected_t mcuxClRsa_pkcs1v15Encode(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);

/**
 * @brief RSA PKCS1-v1_5 verification operation
 *
 * This function performs an RSA PKCS1-v1_5 verification operation according to PKCS #1 v2.2.
 *
 * @param[in]  pSession             Pointer to #mcuxClSession_Descriptor
 * @param[in]  pInput               Pointer to buffer, which contains the message or message digest to be verified
 * @param[in]  inputLength          Size of Input
 * @param[in]  pVerificationInput   Pointer to buffer, which contains the encoded message digest to be verified
 * @param[in]  pHashAlgo            Pointer to hash algorithm information
 * @param[in]  pLabel               RFU: please set to NULL.
 * @param[in]  saltlabelLength      RFU: please set to zero.
 * @param[in]  keyBitLength         Bit-length of key (bit-length of encoded message). Note: This function only supports moduli, whose bit-length is a multiple of 8
 * @param[in]  options              Options field
 * @param[out] pOutput              RFU: please set to NULL
 *
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pInput:</dt>
 *          <dd>The input meets the following conditions:
 *               - It is provided in big-endian byte order.
 *      <dt>inputLength:</dt>
 *          <dd>Specifies the size of the buffer pointed to by pInput in case of option MCUXCLRSA_OPTION_MESSAGE_PLAIN. In case of option MCUXCLRSA_OPTION_MESSAGE_DIGEST,
 *               this buffer size is specified by the targeted hash algorithm. Thus for MCUXCLRSA_OPTION_MESSAGE_DIGEST, please set inputLength to zero.
 *      <dt>pVerificationInput:</dt>
 *          <dd>The padded message meets the following conditions:
 *               - It is provided in little-endian byte order.
 *               - It is located in PKC RAM;
 *      <dt>pHashAlgo:</dt>
 *          <dd>Specifies the targeted hash algorithm, to be used for the mask generation function operation.
 *      <dt>keyBitLength:</dt>
 *          <dd>The key bit-length meets the following conditions:
 *               - This function only supports moduli, whose bit-length is a multiple of 8.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:   Specify, whether pInput is provided as plain message (MCUXCLRSA_OPTION_MESSAGE_PLAIN) to be hashed
 *                                                    internally by the mcuxClRsa_pkcs1v15Verify function, or as message digest (MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_pkcs1v15Verify operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_STATUS_VERIFY_OK        The function executed successfully.
 * @retval #MCUXCLRSA_STATUS_VERIFY_FAILED    The verification failed.
 * @retval #MCUXCLRSA_STATUS_ERROR            An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_pkcs1v15Verify)
mcuxClRsa_Status_Protected_t mcuxClRsa_pkcs1v15Verify(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput
);


/**
 * @}
 */ /* mcuxClRsa_Internal_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_FUNCTIONS_H_ */
