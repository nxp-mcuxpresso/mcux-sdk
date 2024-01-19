/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_FMC_H_
#define FSL_FMC_H_

#include "fsl_common.h"

/*!
 * @addtogroup fmc
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Driver version 2.0.2. */
#define FSL_FMC_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 2U))
/*! @} */

/*!
 * @addtogroup fmc_driver
 * @{
 */

/*!
 * @brief fmc peripheral flag.
 *
 */
enum
{
    kFMC_SignatureGenerationDoneFlag = FMC_FMSTAT_SIG_DONE_MASK, /*!< Flash signature generation done. */
};

/*! @brief Defines the generated 128-bit signature. */
typedef struct _fmc_flash_signature
{
    uint32_t word0; /* Signature bits [31:0]. */
    uint32_t word1; /* Signature bits [63:32]. */
    uint32_t word2; /* Signature bits [95:64]. */
    uint32_t word3; /* Signature bits [127:96]. */
} fmc_flash_signature_t;

/*! @brief fmc config structure. */
typedef struct _fmc_config
{
    uint8_t waitStates; /* flash timing value for flash signature generation. */
} fmc_config_t;

/*! @} */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize FMC module.
 *
 * This function initialize FMC module with user configuration
 *
 * @param base The FMC peripheral base address.
 * @param config pointer to user configuration structure.
 */
void FMC_Init(FMC_Type *base, fmc_config_t *config);

/*!
 * @brief Deinit FMC module.
 *
 * This function De-initialize FMC module.
 *
 * @param base The FMC peripheral base address.
 */
void FMC_Deinit(FMC_Type *base);

/*!
 * @brief Provides default configuration for fmc module.
 *
 * This function provides default configuration for fmc module, the default wait states value is
 * 5.
 *
 * @param config pointer to user configuration structure.
 */
void FMC_GetDefaultConfig(fmc_config_t *config);

/*!
 * @brief Generate hardware flash signature.
 *
 * This function generates hardware flash signature for specified address range.
 *
 * @note This function needs to be excuted out of flash memory.
 * @param base The FMC peripheral base address.
 * @param startAddress Flash start address for signature generation.
 * @param length Length of address range.
 * @param flashSignature Pointer which stores the generated flash signarue.
 */
void FMC_GenerateFlashSignature(FMC_Type *base,
                                uint32_t startAddress,
                                uint32_t length,
                                fmc_flash_signature_t *flashSignature);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
