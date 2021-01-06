/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_fmc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.fmc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Provides default configuration for fmc module.
 *
 * This function provides default configuration for fmc module, the default wait states value is
 * 5.
 *
 * param config pointer to user configuration structure.
 */
void FMC_GetDefaultConfig(fmc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->waitStates = 0x05;
}

/*!
 * brief Initialize FMC module.
 *
 * This function initialize FMC module with user configuration
 *
 * param base The FMC peripheral base address.
 * param config pointer to user configuration structure.
 */
void FMC_Init(FMC_Type *base, fmc_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable clock to FMC */
    CLOCK_EnableClock(kCLOCK_Fmc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Set control register, FS_RD0 = 0, FS_RD1 = 1. */
    base->FCTR &= ~(FMC_FCTR_FS_RD0_MASK | FMC_FCTR_FS_RD1_MASK);
    base->FCTR |= FMC_FCTR_FS_RD1_MASK;

    /* Set wait state, same as FLASHTIM in SYSCON->FLASHCFG register. */
    base->FBWST &= ~FMC_FBWST_WAITSTATES_MASK;
    base->FBWST |= config->waitStates;
}

/*!
 * brief Deinit FMC module.
 *
 * This function De-initialize FMC module.
 *
 * param base The FMC peripheral base address.
 */
void FMC_Deinit(FMC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kFMC_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable clock to FMC */
    CLOCK_DisableClock(kCLOCK_Fmc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Generate hardware flash signature.
 *
 * This function generates hardware flash signature for specified address range.
 *
 * note This function needs to be excuted out of flash memory.
 * param base The FMC peripheral base address.
 * param startAddress Flash start address for signature generation.
 * param length Length of address range.
 * param flashSignature Pointer which stores the generated flash signarue.
 */
void FMC_GenerateFlashSignature(FMC_Type *base,
                                uint32_t startAddress,
                                uint32_t length,
                                fmc_flash_signature_t *flashSignature)
{
    uint32_t stopAddress;

    /* Clear generation done flag. */
    base->FMSTATCLR = kFMC_SignatureGenerationDoneFlag;

    /* Calculate flash stop address */
    stopAddress = ((startAddress + length - 1UL) >> 4UL) & FMC_FMSSTOP_STOP_MASK;

    /* Calculate flash start address. */
    startAddress = (startAddress >> 4UL) & FMC_FMSSTART_START_MASK;

    /* Start flash signature generation. */
    base->FMSSTART = startAddress;
    base->FMSSTOP  = stopAddress;

    base->FMSSTOP |= FMC_FMSSTOP_SIG_START_MASK;

    /* Wait for signature done. */
    while ((base->FMSTAT & (uint32_t)kFMC_SignatureGenerationDoneFlag) != (uint32_t)kFMC_SignatureGenerationDoneFlag)
    {
    }

    /* Clear generation done flag. */
    base->FMSTATCLR = kFMC_SignatureGenerationDoneFlag;

    /* Get the generated flash signature. */
    flashSignature->word0 = base->FMSW[0];
    flashSignature->word1 = base->FMSW[1];
    flashSignature->word2 = base->FMSW[2];
    flashSignature->word3 = base->FMSW[3];

    return;
}
