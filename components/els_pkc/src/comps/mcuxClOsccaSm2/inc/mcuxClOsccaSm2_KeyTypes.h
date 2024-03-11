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
 * @file  mcuxClOsccaSm2_KeyTypes.h
 * @brief Definition of supported key types in mcuxClOsccaSm2 component, see also @ref mcuxClKey component
 */

#ifndef MCUXCLOSCCASM2_KEYTYPES_H_
#define MCUXCLOSCCASM2_KEYTYPES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClKey_Types.h>

/**
 * @defgroup mcuxClOsccaSm2_KeyTypes mcuxClOsccaSm2_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClOsccaSm2, see @ref mcuxClKey
 * @ingroup mcuxClOsccaSm2
 * @{
 */

/**********************************************
 * KEY TYPE DEFS
 **********************************************/
/**
 * @brief Key type structures for public SM2 standard keys and modulus sizes 256 bits.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Std_Public;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Key type pointers for public SM2 standard keys and modulus sizes 256 bits.
 *
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClKey_Type_t mcuxClKey_Type_SM2P256_Std_Public = &mcuxClKey_TypeDescriptor_SM2P256_Std_Public;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

/**
 * @brief Key type structures for private SM2 standard keys and modulus sizes 256 bits.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Std_Private;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Key type pointers for private SM2 standard keys and modulus sizes 256 bits.
 *
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClKey_Type_t mcuxClKey_Type_SM2P256_Std_Private = &mcuxClKey_TypeDescriptor_SM2P256_Std_Private;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

/**
 * @brief Key type structures for public SM2 extend keys and modulus sizes 256 bits.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Ext_Public;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Key type pointers for public SM2 extend keys and modulus sizes 256 bits.
 *
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClKey_Type_t mcuxClKey_Type_SM2P256_Ext_Public = &mcuxClKey_TypeDescriptor_SM2P256_Ext_Public;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

/**
 * @brief Key type structures for private SM2 extend keys and modulus sizes 256 bits.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM2P256_Ext_Private;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Key type pointers for private SM2 extend keys and modulus sizes 256 bits.
 *
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClKey_Type_t mcuxClKey_Type_SM2P256_Ext_Private = &mcuxClKey_TypeDescriptor_SM2P256_Ext_Private;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

/**
 * @}
 */ /* mcuxClOsccaSm2_KeyTypes */

#endif /* MCUXCLOSCCASM2_KEYTYPES_H_ */
