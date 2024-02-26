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
 * @file  mcuxClAes_KeyTypes.h
 * @brief Definition of supported key types in mcuxClAes component, see also @ref mcuxClKey component
 */

#ifndef MCUXCLAES_KEYTYPES_H_
#define MCUXCLAES_KEYTYPES_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <stdint.h>
#include <stdbool.h>

#include <mcuxClKey_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")

/**
 * @defgroup mcuxClAes_KeyTypes mcuxClAes_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClAes, see @ref mcuxClKey
 * @ingroup mcuxClAes
 * @{
 */

/**
 * @brief Key type structure for AES-128 based keys.
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Aes128;

/**
 * @brief Key type pointer for AES-128 based keys.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Aes128 = &mcuxClKey_TypeDescriptor_Aes128;

/**
 * @brief Key type structure for AES-192 based keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Aes192;

/**
 * @brief Key type pointer for AES-192 based keys.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Aes192 = &mcuxClKey_TypeDescriptor_Aes192;

/**
 * @brief Key type structure for AES-256 based keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Aes256;

/**
 * @brief Key type pointer for AES-256 based keys.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Aes256 = &mcuxClKey_TypeDescriptor_Aes256;

/**
 * @}
 */ /* mcuxClAes_KeyTypes */

MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAES_KEYTYPES_H_ */
