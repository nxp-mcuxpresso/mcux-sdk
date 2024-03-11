/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClOsccaSm4_KeyTypes.h
 * @brief Definition of supported key types in mcuxClOsccaSm4 component, see also @ref mcuxClKey component
 */

#ifndef MCUXCLOSCCASM4_KEYTYPES_H_
#define MCUXCLOSCCASM4_KEYTYPES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClKey_Types.h>

/**
 * @defgroup mcuxClOsccaSm4_KeyTypes mcuxClOsccaSm4_KeyTypes
 * @brief Defines of supported key types of @ref mcuxClOsccaSm4, see @ref mcuxClKey
 * @ingroup mcuxClOsccaSm4
 * @{
 */

/**
 * @brief Key type structure for OSCCA SM4 based keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM4;

/**
 * @brief Key type pointer for OSCCA SM4 keys.
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
static const mcuxClKey_Type_t mcuxClKey_Type_SM4 = &mcuxClKey_TypeDescriptor_SM4;
MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

/**
 * @}
 */ /* mcuxClOsccaSm4_KeyTypes */


#endif /* #ifndef MCUXCLOSCCASM4_KEYTYPES_H_ */
