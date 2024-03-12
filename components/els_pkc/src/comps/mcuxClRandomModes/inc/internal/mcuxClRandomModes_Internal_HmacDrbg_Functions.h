/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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
 *
 * @file:   mcuxClRandomModes_Internal_HmacDrbg_Functions.h
 * @brief:  This file contains function declarations and size definitions for HMAC_DRBG functionality to be used by other components.
 *
 */

#ifndef MCUXCLRANDOMMODES_INTERNAL_HMACDRBG_FUNCTIONS_H
#define MCUXCLRANDOMMODES_INTERNAL_HMACDRBG_FUNCTIONS_H

#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClKey_Types_Internal.h>
#include <mcuxClCore_Macros.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <mcuxClHashModes_Constants.h>
#include <mcuxClMac.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClRandomModes_Private_HmacDrbg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* As HMAC DRBG has no public visibility at the moment, size definitions are included here. */
#define MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE          (sizeof(mcuxClRandom_ModeDescriptor_t) + sizeof(mcuxClRandomModes_DrbgModeDescriptor_t) + sizeof(mcuxClRandomModes_DrbgVariantDescriptor_t))
#define MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS (MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE))
#define MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE              (sizeof(mcuxClRandomModes_Context_HmacDrbg_Generic_t))
#define MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS     (MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE))
#define MCUXCLRANDOMMODES_HMAC_DRBG_GENERATE_WACPU_SIZE           (sizeof(mcuxClKey_Descriptor_t) + MCUXCLCORE_ALIGN_TO_CPU_WORDSIZE(MCUXCLHMAC_INTERNAL_MAX_CONTEXT_SIZE))
#define MCUXCLRANDOMMODES_HMAC_DRBG_GENERATE_WACPU_SIZE_IN_WORDS  (MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLRANDOMMODES_HMAC_DRBG_GENERATE_WACPU_SIZE))

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_createCustomHmacDrbgMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_createCustomHmacDrbgMode(
    mcuxClRandom_ModeDescriptor_t *randomMode,
    mcuxClMac_Mode_t hmacMode,
    uint32_t initSeedSize,
    uint32_t reseedSeedSize);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_INTERNAL_HMACDRBG_FUNCTIONS_H */
