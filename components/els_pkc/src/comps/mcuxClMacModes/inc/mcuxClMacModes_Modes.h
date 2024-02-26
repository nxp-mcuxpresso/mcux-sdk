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

#ifndef MCUXCLMACMODES_MODES_H_
#define MCUXCLMACMODES_MODES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClMac_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @addtogroup mcuxClMacModes MAC Modes API
 * @brief Message Authentication Code (MAC) mode operations.
 * @ingroup mcuxClAPI
 */

/**
 * @defgroup mcuxClMacModes_Modes MAC mode definitions
 * @brief Modes used by the MAC operations.
 * @ingroup mcuxClMacModes
 */


/**
 * @brief CMAC mode descriptor
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CMAC;

/**
 * @brief CMAC mode
 * @ingroup mcuxClMacModes_Modes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CMAC =
  &mcuxClMac_ModeDescriptor_CMAC;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()



/**
 * @brief CBC-MAC mode descriptor without padding
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_NoPadding;

/**
 * @brief CBC-MAC mode without padding
 * @ingroup mcuxClMacModes_Modes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_NoPadding =
  &mcuxClMac_ModeDescriptor_CBCMAC_NoPadding;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClMacModes_Modes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method1 =
  &mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClMacModes_Modes
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method2 =
  &mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with PKCS7 padding padding
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_Padding_PKCS7;

/**
 * @brief CBC-MAC mode with PKCS7 padding
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_Padding_PKCS7 =
  &mcuxClMac_ModeDescriptor_CBCMAC_Padding_PKCS7;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_MODES_H_ */
