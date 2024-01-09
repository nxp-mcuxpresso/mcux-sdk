/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClHmac_KeyTypes.h
 * @brief Definition of supported key types in mcuxClHmac component, see also @ref mcuxClKey component
 */

#ifndef MCUXCLHMAC_KEYTYPES_H_
#define MCUXCLHMAC_KEYTYPES_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClKey_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClHmac_KeyTypes mcuxClHmac_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClHmac, see @ref mcuxClKey
 * @ingroup mcuxClHmac
 * @{
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by user / customer. Hence, it is declared but never referenced. ")
/**
 * @brief Key type structure for HMAC-SHA256 based keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_HmacSha256;

/**
 * @brief Key type pointer for HMAC-SHA256 based keys.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_HmacSha256 = &mcuxClKey_TypeDescriptor_HmacSha256;

/**
 * \brief Key type structure for Sw-HMAC based keys with variable length.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Hmac_variableLength;

/**
 * \brief Key type pointer for HMAC-SHA256 based keys with variable length.
 */
static const mcuxClKey_Type_t mcuxClKey_Type_Hmac_variableLength = &mcuxClKey_TypeDescriptor_Hmac_variableLength;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @}
 */ /* mcuxClHmac_KeyTypes */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHMAC_KEYTYPES_H_ */
