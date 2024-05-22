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
 * @file  mcuxClRsa.h
 * @brief Top-level include file for the mcuxClRsa component 
 * 
 * This includes headers for all of the functionality provided by the mcuxClRsa component.
 * 
 * @defgroup mcuxClRsa mcuxClRsa
 * @brief RSA component
 *
 * The mcuxClRsa component implements the RSA functionality supported by CLNS.
 * This includes RSA signature generation and verification according to PKCS#1 v2.2.
 * @if (MCUXCL_FEATURE_RSA_KEYGENERATION)
 * It also provides RSA key generation functionality.
 * @endif
 * The RSA component relies on the mcuxClMath component for modular arithmetic operations as well as the secure and non-secure exponentiation.
 * It further relies on the mcuxHash component for the execution of hashing operations.
 * The component offers the following functionality:
 * - RSA signature generation and verification:
 * <ol>
 *     <li> RSA signature generation using RSA keys in private plain or private CRT format together with the PKCS#1 v1.5 padding or PSS
 *          padding functionality, according to to RSASSA-PSS-SIGN or RSASSA-PKCS1-v1_5-SIGN of PKCS #1 v2.2.
 *     <li> RSA signature verification using RSA keys public format together with the PKCS#1 v1.5 padding or PSS
 *          verification functionality, according to to RSASSA-PSS-VERIFY or RSASSA-PKCS1-v1_5-VERIFY of PKCS #1 v2.2. 
 *     <li> RSA signature generation primitive RSASP1  (exponentiation with public exponent) according to PKCS #1 v2.2.
 *     <li> RSA signature verification primitive RSAVP1  (exponentiation with RSA keys in private plain or private CRT format) according to PKCS #1 v2.2.
 *     <li> The bit-length of the modulus can vary from 512 bits to 4096 bits in multiples of 8.
 *     <li> The bit-length of the public exponent is limited to: of 2 <= e < N.
 *     <li> The bit-length of the private exponent is limited to: d < N.
 * </ol>
 * @if (MCUXCL_FEATURE_RSA_KEYGENERATION)
 * - RSA key generation
 * <ol>
 *     <li> Generation of an RSA key in CRT format {p, q, dp, dq, qInv} and n.
 *     <li> Generation of an RSA key in Plain format {d, n}.
 *     <li> Primes p and q are generated based on the method specified in the FIPS 186-4, Appendix B.3.3.
 *     <li> Private exponent d is computed with the requirements specified in the FIPS 186-4, Appendix B.3.1.
 *     <li> Primes p and q are generated using probabilistic primality test with the probability of not being prime less than 2^(-125).
 *     <li> The bit-length of the key size is limited to 2048, 3072 and 4096.
 *     <li> The public exponent is restricted to (FIPS compliant) odd values in the range 2^16 < e < 2^256 (i.e. including 0x10001).
 *     <li> User shall ensure that if FIPS 186-4 compliance is claimed, the key generation functions are used to generate keys of 2048 or 3072 bits only.
 * </ol>
 * @endif
 */

#ifndef MCUXCLRSA_H_
#define MCUXCLRSA_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClRsa_Functions.h>
#include <mcuxClRsa_MemoryConsumption.h>
#include <mcuxClRsa_Constants.h>
#include <mcuxClRsa_Types.h>
#endif /* MCUXCLRSA_H_ */
