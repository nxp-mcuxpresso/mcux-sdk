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
#include <mcuxClCore_Analysis.h>
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
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CMAC =
  &mcuxClMac_ModeDescriptor_CMAC;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()



/**
 * @brief CBC-MAC mode descriptor without padding
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_NoPadding;

/**
 * @brief CBC-MAC mode without padding
 * @ingroup mcuxClMacModes_Modes
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_NoPadding =
  &mcuxClMac_ModeDescriptor_CBCMAC_NoPadding;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 1
 * @ingroup mcuxClMacModes_Modes
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method1 =
  &mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method1;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClMacModes_Modes
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;

/**
 * @brief CBC-MAC mode with ISO/IEC 9797-1 padding method 2
 * @ingroup mcuxClMacModes_Modes
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method2 =
  &mcuxClMac_ModeDescriptor_CBCMAC_PaddingISO9797_1_Method2;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief CBC-MAC mode descriptor with PKCS7 padding padding
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_CBCMAC_Padding_PKCS7;

/**
 * @brief CBC-MAC mode with PKCS7 padding
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_CBCMAC_Padding_PKCS7 =
  &mcuxClMac_ModeDescriptor_CBCMAC_Padding_PKCS7;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/**
 * @brief HMAC-SHA2-256 mode descriptor using ELS HW
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClMac_ModeDescriptor_HMAC_SHA2_256_ELS;

/**
 * @brief HMAC-SHA2-256 mode using ELS HW
 *
 * The input buffer @p in will be modified by applying padding to it. The caller
 * must ensure that the input buffer is large enough to hold this padding.
 * The total buffer size including padding can be calculated using the macro
 * #MCUXCLMACMODES_GET_HMAC_INPUTBUFFER_LENGTH on the data size @p inLength.
 *
 * Also note that #mcuxClMac_Mode_HMAC_SHA2_256_ELS only works with keys loaded
 * into coprocessor (see @ref mcuxClKey for details).
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_HMAC_SHA2_256_ELS =
  &mcuxClMac_ModeDescriptor_HMAC_SHA2_256_ELS;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_MODES_H_ */
