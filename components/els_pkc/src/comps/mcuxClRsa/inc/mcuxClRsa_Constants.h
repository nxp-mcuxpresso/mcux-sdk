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
 * @file  mcuxClRsa_Constants.h
 * @brief Constant definitions for the mcuxClRsa component
 */

#ifndef MCUXCLRSA_CONSTANTS_H_
#define MCUXCLRSA_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

/* TODO:
 * Using defines for SGI Hashes is a workaround to enable testing of internal padding functions. This should not be in the CL, as mode constructors are used for S5xy.
 * CL artifact to remove this workaround: CLNS-6116
 * TT artifact to adapt the tests: CLNS-6117
 */

/**
 * @defgroup mcuxClRsa_Constants mcuxClRsa_Constants
 * @brief Constants of @ref mcuxClRsa component
 * @ingroup mcuxClRsa
 * @{
 */

/**
* @defgroup mcuxClRsa_Sign_Modes mcuxClRsa_Sign_Modes
* @brief Signing modes of the @ref mcuxClRsa component
* @ingroup mcuxClRsa_Constants
* @{
*/

/**
 * @brief Mode definition for RSASP1
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_NoEncode;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-SIGN using SHA-2/224
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_224;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-SIGN using SHA-2/256
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_256;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-SIGN using SHA-2/384
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_384;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-SIGN using SHA-2/512
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_512;

/**
 * @brief Mode definition for RSASSA-PSS-SIGN using SHA-2/224
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_224;

/**
 * @brief Mode definition for RSASSA-PSS-SIGN using SHA-2/256
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_256;

/**
 * @brief Mode definition for RSASSA-PSS-SIGN using SHA-2/384
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_384;

/**
 * @brief Mode definition for RSASSA-PSS-SIGN using SHA-2/512
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_512;

/**
 * @}
 */

/**
* @defgroup mcuxClRsa_Verify_Modes mcuxClRsa_Verify_Modes
* @brief Verify modes of the @ref mcuxClRsa component
* @ingroup mcuxClRsa_Constants
* @{
*/

/**
 * @brief Mode definition for RSAVP1
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_NoVerify;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-VERIFY using SHA-2/224
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_224;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-VERIFY using SHA-2/256
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_256;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-VERIFY using SHA-2/384
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_384;

/**
 * @brief Mode definition for RSASSA-PKCS1-v1_5-VERIFY using SHA-2/512
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_512;

/**
 * @brief Mode definition for RSASSA-PSS-VERIFY using SHA-2/224
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_224;

/**
 * @brief Mode definition for RSASSA-PSS-VERIFY using SHA-2/256
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_256;

/**
 * @brief Mode definition for RSASSA-PSS-VERIFY using SHA-2/384
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_384;

/**
 * @brief Mode definition for RSASSA-PSS-VERIFY using SHA-2/512
 */
extern const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_512;

/**
 * @}
 * @}
 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_CONSTANTS_H_ */
