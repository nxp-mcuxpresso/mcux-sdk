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
 * @file  mcuxClKey_KeyTypes.h
 * @brief Definition of supported key types in mcuxClKey component
 */

#ifndef MCUXCLKEY_KEYTYPES_H_
#define MCUXCLKEY_KEYTYPES_H_

#include <stdint.h>
#include <stdbool.h>

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClKey_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClKey_KeyTypes mcuxClKey_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**********************************************
 * TYPEDEFS
 **********************************************/


/**
 * \brief Key type structure for HMAC-SHA256 based keys with variable length.
 *
 */
/* MISRA Ex. 20 - Rule 5.1 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256_variableLength;

/**
 * \brief Key type pointer for HMAC-SHA256 based keys with variable length.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_HmacSha256_variableLength = &mcuxClKey_TypeDescriptor_HmacSha256_variableLength;

/**
 * @brief Key type structure for HMAC-SHA256 based keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256;

/**
 * @brief Key type pointer for HMAC-SHA256 based keys.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_HmacSha256 = &mcuxClKey_TypeDescriptor_HmacSha256;

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * @}
 */ /* mcuxClKey_KeyTypes */

#endif /* MCUXCLKEY_KEYTYPES_H_ */
