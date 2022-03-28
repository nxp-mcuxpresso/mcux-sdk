/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClCss.h
 * @brief Top-level include file for the CSSv2 driver
 *
 * This includes headers for all of the functionality provided by the CSSv2 IP.
 *
 * @defgroup mcuxClCss mcuxClCss
 * @brief Css driver
 *
 * This component abstracts the hardware access to the CSSv2 IP.
 * The library exposes the following hardware functionality:
 * <ol>
 *      <li> COMMON
 *          <ul>
 *              <li> CSSv2 Software Reset
 *                  <ul> <li> #mcuxClCss_Reset_Async </ul>
 *          </ul>
 *      <li> HASH
 *          <ul>
 *              <li> SHA-2 hashing
 *                  <ul> <li> #mcuxClCss_Hash_Async </ul>
 *              <li> SHA-2 hashing in direct mode
 *                  <ul> <li> #mcuxClCss_Hash_ShaDirect </ul>
 *          </ul>
 *      <li> HMAC (Keyed-Hash Message Authentication Code)
 *          <ul>
 *              <li> HMAC
 *                  <ul> <li> #mcuxClCss_Hmac_Async </ul>
 *          </ul>
 *      <li> CMAC (Cipher-Based Message Authentication Code)
 *          <ul>
 *              <li> CMAC
 *                  <ul> <li> #mcuxClCss_Cmac_Async </ul>
 *          </ul>
 *      <li> CIPHER (Symmetric Encryption)
 *          <ul>
 *              <li> AES
 *                  <ul> <li> #mcuxClCss_Cipher_Async </ul>
 *          </ul>
 *      <li> AEAD (Authenticated Encryption with Associated Data)
 *          <ul>
 *              <li> Authenticated Encryption with Associated Data
 *                  <ul>
 *                      <li> #mcuxClCss_Aead_Init_Async
 *                      <li> #mcuxClCss_Aead_UpdateAad_Async
 *                      <li> #mcuxClCss_Aead_UpdateData_Async
 *                      <li> #mcuxClCss_Aead_Finalize_Async
 *                  </ul>
 *          </ul>
 *      <li> KEY MANAGEMENT
 *          <ul>
 *              <li> Key deletion
 *                  <ul> <li> #mcuxClCss_KeyDelete_Async </ul>
 *              <li> Key import
 *                  <ul> <li> #mcuxClCss_KeyImport_Async </ul>
 *              <li> Key export
 *                  <ul> <li> #mcuxClCss_KeyExport_Async </ul>
 *          </ul>
 *      <li> RNG
 *          <ul>
 *              <li> Random data generation using DRBG
 *                  <ul> <li> #mcuxClCss_Rng_DrbgRequest_Async </ul>
 *              <li> Configuration of the DTRNG
 *                  <ul> <li> #mcuxClCss_Rng_Dtrng_ConfigLoad_Async </ul>
 *          </ul>
 *      <li> ECC (Elliptic Curve Cryptography)
 *          <ul>
 *              <li> ECC Key generation
 *                  <ul> <li> #mcuxClCss_EccKeyGen_Async </ul>
 *              <li> ECC key exchange
 *                  <ul> <li> #mcuxClCss_EccKeyExchange_Async </ul>
 *              <li> ECC signature generation
 *                  <ul> <li> #mcuxClCss_EccSign_Async </ul>
 *              <li> ECC signature verification
 *                  <ul> <li> #mcuxClCss_EccVerify_Async </ul>
 *          </ul>
 *      <li> KEY DERIVATION
 *          <ul>
 *              <li> Key derivation
 *                  <ul>
 *                      <li> #mcuxClCss_Ckdf_Sp800108_Async
 *                      <li> #mcuxClCss_Hkdf_Rfc5869_Async
 *                      <li> #mcuxClCss_Hkdf_Sp80056c_Async
 *                  </ul>
 *              <li> Master Key and Session Key derivation
 *                  <ul>
 *                      <li> #mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async
 *                      <li> #mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async
 *                  </ul>
 *          </ul>
 *  </ol>
 *
 *  After each call to a function ending in <tt>_Async</tt>, one of the waiting functions #mcuxClCss_WaitForOperation or #mcuxClCss_LimitedWaitForOperation must be called to ensure completion.
 *  The waiting functions may fail, e.g., when the CSSv2 enters an error state.
 */

#ifndef MCUXCLCSS_H_
#define MCUXCLCSS_H_

#include <mcuxClCss_Types.h>
#include <mcuxClCss_Common.h>
#include <mcuxClCss_Hash.h>
#include <mcuxClCss_Hmac.h>
#include <mcuxClCss_Cmac.h>
#include <mcuxClCss_Cipher.h>
#include <mcuxClCss_Aead.h>
#include <mcuxClCss_KeyManagement.h>
#include <mcuxClCss_Rng.h>
#include <mcuxClCss_Ecc.h>
#include <mcuxClCss_Kdf.h>

#endif /* MCUXCLCSS_H_ */
