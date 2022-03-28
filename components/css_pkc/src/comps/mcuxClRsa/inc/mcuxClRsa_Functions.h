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

/** 
 * @file  mcuxClRsa_Functions.h
 * @brief Top-level API of the mcuxClRsa component 
 */

#ifndef MCUXCLRSA_FUNCTIONS_H_
#define MCUXCLRSA_FUNCTIONS_H_

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClHash.h>
#include <mcuxClRsa_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClRsa_Functions mcuxClRsa_Functions
 * @brief Defines all functions of @ref mcuxClRsa
 * @ingroup mcuxClRsa
 * @{
 */


/**
 * @brief RSA sign operation
 *
 * This function performs an RSA signature generation according to RSASP1, RSASSA-PSS-SIGN or RSASSA-PKCS1-v1_5-SIGN
 * of PKCS #1 v2.2. Based on the passed key type, it is selected, whether to perform this operation using a private
 * plain, a private CRT key, or whether to use a private CRT key and protect the operation against perturbation attacks.
 * Based on the selection of the padding mode, it is determined, whether to perform no padding, or whether to perform
 * one of the supported paddings based on one of the supported hash functions.
 * The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8.
 * The private exponent is limited to d < n.
 *
 * @param[in]  pSession                  Pointer to #mcuxClSession_Descriptor
 * @param[in]  pKey                      Pointer to key structure of type @ref mcuxClRsa_Key
 * @param[in]  pMessageOrDigest          Pointer to buffer, which contains the input to the sign operation
 * @param[in]  messageLength             Byte-length of MessageOrDigest
 * @param[in]  pPaddingMode              Pointer to signing mode of type @ref mcuxClRsa_SignVerifyMode_t
 * @param[in]  saltLength                Byte-length of salt
 * @param[in]  options                   Options field
 * @param[out] pSignature                Pointer to buffer, which contains the result (signature)
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pKey:</dt>
 *          <dd>The key entries must meet the following conditions:
 *              - Entry keytype can be set to #MCUXCLRSA_KEY_PRIVATEPLAIN to perform the secure exponentiation with
 *                a private plain key, #MCUXCLRSA_KEY_PRIVATECRT to perform the secure exponentiation with a private CRT key,
 *                or #MCUXCLRSA_KEY_PRIVATECRT_DFA to perform the secure exponentiation with a private CRT key,
 *                protecting the operation against perturbation attacks. In case of specifying another key type, the
 *                function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *              - The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8;
 *              - In case of type #MCUXCLRSA_KEY_PRIVATEPLAIN, the exponent
 *                d must be smaller than modulus n; in case of type #MCUXCLRSA_KEY_PRIVATECRT or #MCUXCLRSA_KEY_PRIVATECRT_DFA,
 *                the d from which dp and dq are derived must be smaller than (p * q);
 *              - In case of type #MCUXCLRSA_KEY_PRIVATECRT
 *                or #MCUXCLRSA_KEY_PRIVATECRT_DFA it is required that: bitlength(p) == bitlength(q) == 1/2 * bitlength(n).
 *      <dt>pMessageOrDigest:</dt>
 *          <dd>The input must meet the following conditions:
 *               - It must be given in big-endian byte order;
 *               - In case of key type #MCUXCLRSA_KEY_PRIVATEPLAIN and mode #mcuxClRsa_Mode_Sign_NoEncode, the input must
 *                 be smaller than n, otherwise the function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *               - In case of type #MCUXCLRSA_KEY_PRIVATECRT or #MCUXCLRSA_KEY_PRIVATECRT_DFA and mode
 *                 #mcuxClRsa_Mode_Sign_NoEncode, the input must be smaller than (p * q), otherwise the function
 *                 returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *               - In case of option #MCUXCLRSA_OPTION_MESSAGE_DIGEST the length of pMessageOrDigest is determined by the selected
 *                 hash algorithm;
 *               - In case of mode #mcuxClRsa_Mode_Sign_NoEncode the length of pMessageOrDigest is determined by the length of n;
 *               - The signature length is determined by the modulus length (bytelength(n)).
 *      <dt>messageLength:</dt>
 *          <dd> This value is only regarded in case of option #MCUXCLRSA_OPTION_MESSAGE_PLAIN.
 *               In case of option #MCUXCLRSA_OPTION_MESSAGE_DIGEST, or mode RSASP1, please set to zero.
 *      <dt>pPaddingMode:</dt>
 *          <dd> The mode specifies the targeted padding and hashing algorithms.
 *               Please set to one of @ref mcuxClRsa_Sign_Modes.
 *      <dt>saltLength:</dt>
 *          <dd> This value is only regarded in case of performing a RSASSA-PSS-SIGN operation. Otherwise, please set to zero.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:  Specify, whether pMessageOrDigest points to a plain message (#MCUXCLRSA_OPTION_MESSAGE_PLAIN)
 *                             to be hashed internally by the sign function, or to a message digest (#MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *                             In case of mode RSASP1, please set to zero.
 *      <dt>pSignature:</dt>
 *          <dd>The output is returned in in big-endian byte order.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_sign operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_STATUS_SIGN_OK               Sign operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT         The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                 An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_sign)
mcuxClRsa_Status_Protected_t mcuxClRsa_sign(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  const uint8_t * const           pMessageOrDigest,
  const uint32_t                  messageLength,
  const mcuxClRsa_SignVerifyMode   pPaddingMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  uint8_t * const                 pSignature
);

/**
 * @brief RSA verify operation
 *
 * This function performs an RSA signature verification according to RSAVP1, RSASSA-PSS-VERIFY or RSASSA-PKCS1-v1_5-VERIFY
 * of PKCS #1 v2.2. Based on the selection of the padding mode, it is determined, whether to perform no padding verification,
 * or whether to perform one of the supported padding verifications based on one of the supported hash functions.
 * The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8. The public
 * exponent is limited to 2 <= e < N.
 *
 * @param[in]  pSession                  Pointer to #mcuxClSession_Descriptor
 * @param[in]  pKey                      Pointer to key structure of type @ref mcuxClRsa_Key
 * @param[in]  pMessageOrDigest          Pointer to buffer, which contains the input to the verify operation
 * @param[in]  messageLength             Byte-length of MessageOrDigest
 * @param[in]  pSignature                Pointer to buffer, which contains the signature
 * @param[in]  pVerifyMode               Pointer to verification mode of type @ref mcuxClRsa_SignVerifyMode_t
 * @param[in]  saltLength                Byte-length of salt
 * @param[in]  options                   Options field
 * @param[out] pOutput                   Pointer to output buffer
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *      <dt>pKey:</dt>
 *          <dd>The key entries must meet the following conditions:
 *              - Entry keytype must be set to #MCUXCLRSA_KEY_PUBLIC. In case of passing another key type, the function
 *                returns #MCUXCLRSA_STATUS_INVALID_INPUT. The functions checks, internally, whether the required key entries
 *                are not set to NULL. If so, the function returns #MCUXCLRSA_STATUS_INVALID_INPUT;
 *              - The supported bit-lengths of the modulus range from 512 to 4096 in multiples of 8;
 *              - It is required that e is greater or equal to 2 and smaller than n.
 *      <dt>pMessageOrDigest:</dt>
 *          <dd>The input must meet the following conditions:
 *               - It must be provided in big-endian byte order;
 *               - In case of mode RSAVP1, please set to NULL.
 *      <dt>messageLength:</dt>
 *          <dd> This value is only regarded in case of option #MCUXCLRSA_OPTION_MESSAGE_PLAIN.
 *               In case of option #MCUXCLRSA_OPTION_MESSAGE_DIGEST, or mode RSAVP1, please set to zero.
 *      <dt>pSignature:</dt>
 *          <dd> The signature must meet the following conditions:
 *               - It must be given in big-endian byte order;
 *               - The signature length is determined by the modulus length (bytelength(n));
 *               - The signature value must be smaller than n. If it is bigger the function returns #MCUXCLRSA_STATUS_INVALID_INPUT.
 *      <dt>pVerifyMode:</dt>
 *          <dd> The mode specifies the targeted padding verification and hashing algorithms.
 *               Please set to one of @ref mcuxClRsa_Verify_Modes.
 *      <dt>saltLength:</dt>
 *          <dd> This value is only regarded in case of performing a RSASSA-PSS-VERIFY operation. Otherwise, please set to zero.
 *      <dt>options:</dt>
 *          <dd> This field is used to select options of the sign operation:
 *                - bits 31-8: RFU; please set to zero
 *                - bits 7-0:  Specify, whether pMessageOrDigest points to a plain message (#MCUXCLRSA_OPTION_MESSAGE_PLAIN)
 *                             to be hashed internally by the verify function, or to a message digest (#MCUXCLRSA_OPTION_MESSAGE_DIGEST).
 *                             In case of mode RSAVP1, please set to zero.
 *      <dt>pOutput:</dt>
 *          <dd>In case of mode RSAVP1 this pointer points to the buffer, where the result will be stored in big-endian byte
 *              order. This buffer must have the same byte-length as the modulus. In case of modes RSASSA-PSS-VERIFY and
 *              RSASSA-PKCS1-v1_5-VERIFY please set to NULL.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_verify operation (see @ref mcuxClRsa_Status_Protected_t)
 * @retval #MCUXCLRSA_STATUS_VERIFY_OK             Verify operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_VERIFYPRIMITIVE_OK    Verification primitive operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT         The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_VERIFY_FAILED         The signature verification failed.
 * @retval #MCUXCLRSA_STATUS_ERROR                 An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_verify)
mcuxClRsa_Status_Protected_t mcuxClRsa_verify(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  const uint8_t * const           pMessageOrDigest,
  const uint32_t                  messageLength,
  uint8_t * const                 pSignature,
  const mcuxClRsa_SignVerifyMode   pVerifyMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  uint8_t * const                 pOutput
);


/**
 * @}
 */ /* mcuxClRsa_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_FUNCTIONS_H_ */

