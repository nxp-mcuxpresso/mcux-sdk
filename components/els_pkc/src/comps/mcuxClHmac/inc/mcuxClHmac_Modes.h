/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                      */
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
 * @file  mcuxClHmac_Modes.h
 * @brief Mode descriptors for the mcuxClHmac component
 */

#ifndef MCUXCLHMAC_MODES_H_
#define MCUXCLHMAC_MODES_H_

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
 * @addtogroup mcuxClHmac HMAC Modes API
 * @brief HMAC mode operations
 * @ingroup mcuxClAPI
 */

/**
 * @defgroup mcuxClHmac_Modes HMAC mode definitions
 * @brief Modes used by the HMAC operations.
 * @ingroup mcuxClHmac
 */

/**
 * @brief HMAC-SHA2-256 mode descriptor using ELS HW
 */
extern const mcuxClMac_ModeDescriptor_t mcuxClHmac_ModeDescriptor_SHA2_256_ELS;

/**
 * @brief HMAC-SHA2-256 mode using ELS HW
 *
 * The input buffer @p in will be modified by applying padding to it. The caller
 * must ensure that the input buffer is large enough to hold this padding.
 * The total buffer size including padding can be calculated using the macro
 * #MCUXCLHMAC_ELS_INPUTBUFFER_LENGTH on the data size @p inLength.
 *
 * Also note that #mcuxClMac_Mode_HMAC_SHA2_256_ELS only works with keys loaded
 * into coprocessor (see @ref mcuxClKey for details).
 *
 */
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Declaration provided for externally accessible API")
static mcuxClMac_Mode_t mcuxClMac_Mode_HMAC_SHA2_256_ELS =
    &mcuxClHmac_ModeDescriptor_SHA2_256_ELS;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHMAC_MODES_H_ */
