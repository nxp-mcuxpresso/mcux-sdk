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

/**
 * @file  mcuxClKey_Protections.h
 * @brief Provide API of the mcuxClKey_Protection functions
 */

#ifndef MCUXCLKEY_PROTECTIONMECHANISMS_H_
#define MCUXCLKEY_PROTECTIONMECHANISMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClKey_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @addtogroup mcuxClKey Key API
 * @brief Key handling operations.
 * @ingroup mcuxClAPI
 */

/**
 * @defgroup clKeyProtectionMechanisms Key protection mechanism definitions
 * @brief Mechanisms used by the Key operations.
 * @ingroup mcuxClKey
 * @{
 */

/**
 * @brief Key protection descriptor for using no key protection
 */
extern const mcuxClKey_ProtectionDescriptor_t mcuxClKey_ProtectionDescriptor_None;

/**
 * @brief No key protection
 */
static const mcuxClKey_Protection_t mcuxClKey_Protection_None =
  &mcuxClKey_ProtectionDescriptor_None;

/**
 * @brief Key protection descriptor for using CKDF based key protection
 *        This protection mechanism cannot be used for #mcuxClKey_loadMemory
 */
extern const mcuxClKey_ProtectionDescriptor_t mcuxClKey_ProtectionDescriptor_Ckdf;

/**
 * @brief CKDF key protection
 */
static const mcuxClKey_Protection_t mcuxClKey_Protection_Ckdf =
  &mcuxClKey_ProtectionDescriptor_Ckdf;

/**
 * @brief Key protection descriptor for using XOR masking
 */
extern const mcuxClKey_ProtectionDescriptor_t mcuxClKey_ProtectionDescriptor_XorMasked;

/**
 * @brief Key protection using XOR masking
 */
static const mcuxClKey_Protection_t mcuxClKey_Protection_XorMasked =
  &mcuxClKey_ProtectionDescriptor_XorMasked;

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_PROTECTIONMECHANISMS_H_ */

