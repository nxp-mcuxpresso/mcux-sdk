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

/** 
 * @file  mcuxClRsa_Functions.h
 * @brief Top-level API of the mcuxClRsa component
 */

#ifndef MCUXCLRSA_FUNCTIONS_H_
#define MCUXCLRSA_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClKey.h>
#include <mcuxClRsa_Types.h>
#include <mcuxClCore_Buffer.h>

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
 * @return Status of the mcuxClRsa_sign operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t))
 * @retval #MCUXCLRSA_STATUS_SIGN_OK               Sign operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT         The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_ERROR                 An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_sign)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_sign(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  mcuxCl_InputBuffer_t             pMessageOrDigest,
  const uint32_t                  messageLength,
  const mcuxClRsa_SignVerifyMode   pPaddingMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  mcuxCl_Buffer_t                  pSignature
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
 * @return Status of the mcuxClRsa_verify operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t))
 * @retval #MCUXCLRSA_STATUS_VERIFY_OK             Verify operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_VERIFYPRIMITIVE_OK    Verification primitive operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT         The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_VERIFY_FAILED         The signature verification failed.
 * @retval #MCUXCLRSA_STATUS_ERROR                 An error occurred during the execution. In that case, expectations for the flow protection are not balanced.
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_verify(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  mcuxCl_InputBuffer_t             pMessageOrDigest,
  const uint32_t                  messageLength,
  mcuxCl_Buffer_t                  pSignature,
  const mcuxClRsa_SignVerifyMode   pVerifyMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  mcuxCl_Buffer_t                  pOutput
);




/**
 * @brief Generates an RSA key in CRT format
 *
 * This function for given public exponent and key size generates an RSA private key
 * in CRT representation (p, q, dp, dq, qInv) and computes the modulus n.
 *
 * Primes p and q are generated based on the method specified in the FIPS 186-4, Appendix B.3.3 using probabilistic
 * primality test with the probability of not being prime less than 2^(-125).
 * The public exponent is restricted to (FIPS compliant) odd values in the range 2^16 < e < 2^256 (i.e. including 0x10001).
 * The bit-length of the key size is limited to 2048, 3072 and 4096.
 * The keys generated by this function are FIPS 186-4 compliant provided their length is either 2048 or 3072 bits
 * and the exponent value is an odd integer between 2^16 and 2^256.
 *
 * The two key handles are linked with each other using mcuxClKey_linkKeyPair.
 * 
 * @param[in]      pSession              Pointer to #mcuxClSession_Descriptor
 * @param[in]      type                  Type of the key
 * @param[in]      protection            Protection and flush mechanism that must be applied to the generated key.
 * @param[out]     privKey               Key handle for the generated private key
 * @param[out]     pPrivData             Pointer to the buffer where the generated private CRT key data needs to be written
 * @param[out]     pPrivDataLength       Will be set by the number of bytes of data that have been written to the \p pPrivData buffer
 * @param[out]     pubKey                Key handle for the generated public key
 * @param[out]     pPubData              Pointer to the buffer where the generated public key data needs to be written
 * @param[out]     pPubDataLength        Will be set by the number of bytes of data that have been written to the \p pPubData buffer
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function. The RNG shall be initialized
 *              with the entropy level (security strength) in accordance with the value of type.size, as specified in SP 800-57, Part 1.
 *      <dt>type:</dt>
 *          <dd>Type of the key. It contains information about the input parameters:
 *           - type.size - length of the generated key
 *           - type.info - pointer to key entry i.e. public exponent. It points to data type mcuxClRsa_KeyEntry_t* (i.e. pointer to buffer containing
 *           the public exponent data and byte-length of the public exponent).
 *      <dt>protection :</dt>
 *          <dd>Protection and flush mechanism that must be applied to the generated key.
 *      <dt>privKey:</dt>
 *          <dd>Key handle for the generated private key.
 *      <dt>pPrivData:</dt>
 *          <dd>Pointer to the buffer where the generated private CRT key (p, q, qInv, dp, dq) data needs to be written.
 *              This buffer contains key type and key entries (mcuxClRsa_Key data type) followed by the key data, i.e.: p, q, qInv, dp, dq.
 *              Buffer is allocated by the caller.
 *      <dt>pPrivDataLength:</dt>
 *          <dd>Number of bytes of data that have been written to the \p pPrivData buffer.
 *      <dt>pubKey:</dt>
 *          <dd>Key handle for the generated public key.
 *      <dt>pPubData:</dt>
 *          <dd>Pointer to the buffer where the generated public key (n, e) data needs to be written.
 *              This buffer contains key type and key entries (mcuxClRsa_Key data type) followed by the key data, i.e.: n, e.
 *              Buffer is allocated by the caller.
 *      <dt>pPubDataLength:</dt>
 *          <dd>Number of bytes of data that have been written to the \p pPubData buffer.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_KeyGeneration_Crt operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t))
 * @retval #MCUXCLRSA_STATUS_KEYGENERATION_OK                    RSA key generation operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT                       The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED    RSA key generation exceeds the limit of iterations to generate a prime.
 * @retval #MCUXCLRSA_STATUS_ERROR                               An error occurred during the execution. In that case, expectations for
 *                                                              the flow protection are not balanced.
 *
 * @attention This function uses DRBG and PRNG which have to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_KeyGeneration_Crt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_KeyGeneration_Crt(
   mcuxClSession_Handle_t pSession,
   mcuxClKey_Type_t type,
   mcuxClKey_Protection_t protection,
   mcuxClKey_Handle_t privKey,
   uint8_t * pPrivData,
   uint32_t * const pPrivDataLength,
   mcuxClKey_Handle_t pubKey,
   uint8_t * pPubData,
   uint32_t * const pPubDataLength
 );


/**
 * @brief RSA key generation of private plain key operation.
 *
 * This function for given public exponent and key size generates RSA private key in in plain from (d, n).
 *
 * Private exponent d is computed with the requirements specified in the FIPS 186-4, Appendix B.3.1.
 * Primes p and q are generated based on the method specified in the FIPS 186-4, Appendix B.3.3 using probabilistic
 * primality test with the probability of not being prime less than 2^(-125).
 * The public exponent is restricted to (FIPS compliant) odd values in the range 2^16 < e < 2^256 (i.e. including 0x10001).
 * The bit-length of the key size is limited to 2048, 3072 and 4096.
 * The keys generated by this function are FIPS 186-4 compliant provided their length is either 2048 or 3072 bits
 * and the exponent value is an odd integer between 2^16 and 2^256.
 * 
 * The two key handles are linked with each other using mcuxClKey_linkKeyPair.
 *
 * @param[in]      pSession              Pointer to #mcuxClSession_Descriptor
 * @param[in]      type                  Type of the key
 * @param[in]      protection            Protection and flush mechanism that must be applied to the generated key
 * @param[out]     privKey               Key handle for the generated private key
 * @param[out]     pPrivData             Pointer to the buffer where the generated private plain key data needs to be written
 * @param[out]     pPrivDataLength       Will be set by the number of bytes of data that have been written to the \p pPrivData buffer
 * @param[out]     pubKey                Key handle for the generated public key
 * @param[out]     pPubData              Pointer to the buffer where the generated public key data needs to be written
 * @param[out]     pPubDataLength        Will be set by the number of bytes of data that have been written to the \p pPubData buffer
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>pSession:</dt>
 *          <dd>The session pointed to by pSession has to be initialized prior to a call to this function. The RNG shall be initialized
 *              with the entropy level (security strength) in accordance with the value of type.size, as specified in SP 800-57, Part 1.
 *      <dt>type:</dt>
 *          <dd>Type of the key. It contains information about the input parameters:
 *           - type.size - length of the generated key
 *           - type.info - pointer to key entry i.e. public exponent. It points to data type mcuxClRsa_KeyEntry_t*(i.e. pointer to buffer containing
 *           the public exponent data and byte-length of the public exponent).
 *      <dt>protection :</dt>
 *          <dd>Protection and flush mechanism that must be applied to the generated key.
 *      <dt>privKey:</dt>
 *          <dd>Key handle for the generated private key.
 *      <dt>pPrivData:</dt>
 *          <dd>Pointer to the buffer where the generated private plain key (n, d) data needs to be written.
 *              This buffer contains key type and key entries (mcuxClRsa_Key data type) followed by the key data, i.e.: n, d.
 *              Buffer is allocated by the caller.
 *      <dt>pPrivDataLength:</dt>
 *          <dd>Number of bytes of data that have been written to the \p pPrivData buffer.
 *      <dt>pubKey:</dt>
 *          <dd>Key handle for the generated public key.
 *      <dt>pPubData:</dt>
 *          <dd>Pointer to the buffer where the generated public key (n, e) data needs to be written.
 *              This buffer contains key type and key entries (mcuxClRsa_Key data type) followed by the key data, i.e.: n, e.
 *              Buffer is allocated by the caller.
 *      <dt>pPubDataLength:</dt>
 *          <dd>Number of bytes of data that have been written to the \p pPubData buffer.
 *  </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClRsa_KeyGeneration_Plain operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t))
 * @retval #MCUXCLRSA_STATUS_KEYGENERATION_OK                    RSA key generation operation executed successfully.
 * @retval #MCUXCLRSA_STATUS_INVALID_INPUT                       The input parameters are not valid.
 * @retval #MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED    RSA key generation exceeds the limit of iterations to generate a prime.
 * @retval #MCUXCLRSA_STATUS_ERROR                               An error occurred during the execution. In that case, expectations for
 *                                                              the flow protection are not balanced.
 *
 * @attention This function uses DRBG and PRNG which have to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRsa_KeyGeneration_Plain)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_KeyGeneration_Plain(
   mcuxClSession_Handle_t pSession,
   mcuxClKey_Type_t type,
   mcuxClKey_Protection_t protection,
   mcuxClKey_Handle_t privKey,
   uint8_t * pPrivData,
   uint32_t * const pPrivDataLength,
   mcuxClKey_Handle_t pubKey,
   uint8_t * pPubData,
   uint32_t * const pPubDataLength
 );


/**
 * @}
 */ /* mcuxClRsa_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_FUNCTIONS_H_ */

