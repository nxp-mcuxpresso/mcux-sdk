/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

/** @file  mcuxClAeadModes_Modes.h
 *  @brief This file defines the modes for the mcuxClAeadModes component */

#ifndef MCUXCLAEADMODES_MODES_H_
#define MCUXCLAEADMODES_MODES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClAead_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @addtogroup mcuxClAead Aead API
 * @brief Authenticated Encryption with Associated Data (AEAD) operations.
 * @ingroup mcuxClAPI
 */

/**
 * @defgroup clAeadModes AEAD mode definitions
 * @brief Modes used by the AEAD operations.
 * @ingroup mcuxClAead
 */



/**
 * @brief AES CCM encrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_CCM_ENC;

/**
 * @brief AES CCM encrypt mode
 */
static mcuxClAead_Mode_t mcuxClAead_Mode_AES_CCM_ENC =
  &mcuxClAead_ModeDescriptor_AES_CCM_ENC;

/**
 * @brief AES CCM decrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_CCM_DEC;

/**
 * @brief AES CCM decrypt mode
 */
static mcuxClAead_Mode_t mcuxClAead_Mode_AES_CCM_DEC =
  &mcuxClAead_ModeDescriptor_AES_CCM_DEC;

/**
 * @brief AES GCM encrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_GCM_ENC;

/**
 * @brief AES GCM encrypt mode
 */
static mcuxClAead_Mode_t mcuxClAead_Mode_AES_GCM_ENC =
  &mcuxClAead_ModeDescriptor_AES_GCM_ENC;

/**
 * @brief AES GCM decrypt mode descriptor
 */
extern const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_GCM_DEC;

/**
 * @brief AES GCM decrypt mode
 */
static mcuxClAead_Mode_t mcuxClAead_Mode_AES_GCM_DEC =
  &mcuxClAead_ModeDescriptor_AES_GCM_DEC;
/** @} */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEADMODES_MODES_H_ */
