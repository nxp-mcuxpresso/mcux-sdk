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

#ifndef MCUXCLOSCCAMACMODES_MODES_H_
#define MCUXCLOSCCAMACMODES_MODES_H_

#include <mcuxCsslAnalysis.h>
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @addtogroup mcuxClOsccaMacModes MAC API
 * @brief Message Authentication Code (MAC) operations.
 * @ingroup mcuxClAPI
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_API_DECLARATIONS()
/**
 * @defgroup mcuxClOsccaMacModes MAC mode definitions
 * @brief Modes used by the MAC operations.
 * @ingroup mcuxClMac
 */
#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
/**
 * @brief CMAC mode descriptor
 * @ingroup mcuxClOsccaMacModes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CMAC;

/**
 * @brief CMAC mode
 * @ingroup mcuxClOsccaMacModes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClOsccaMac_Mode_CMAC =
  &mcuxClOsccaMacModes_ModeDescriptor_CMAC;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */

#ifdef MCUXCL_FEATURE_MACMODES_CBCMAC_SM4
/**
 * @brief CBC-MAC mode descriptor without padding
 * @ingroup mcuxClOsccaMacModes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_NoPadding;

/**
 * @brief CBC-MAC mode without padding
 * @ingroup mcuxClOsccaMacModes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClOsccaMac_Mode_CBCMAC_NoPadding =
  &mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_NoPadding;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()
/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClOsccaMacModes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClOsccaMacModes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClOsccaMac_Mode_CBCMAC_PaddingISO9797_1_Method1 =
  &mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClOsccaMacModes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClOsccaMacModes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClOsccaMac_Mode_CBCMAC_PaddingISO9797_1_Method2 =
  &mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()
/**
 * @brief CBC-MAC mode descriptor with PKCS7 padding padding
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_Padding_PKCS7;

/**
 * @brief CBC-MAC mode with PKCS7 padding
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClOsccaMac_Mode_CBCMAC_Padding_PKCS7 =
  &mcuxClOsccaMacModes_ModeDescriptor_CBCMAC_Padding_PKCS7;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

#endif /* MCUXCL_FEATURE_MACMODES_CBCMAC_SM4 */


MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_API_DECLARATIONS()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAMACMODES_MODES_H_ */
