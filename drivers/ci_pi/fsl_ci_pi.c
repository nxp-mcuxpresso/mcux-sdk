/*
 * Copyright 2017, 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ci_pi.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ci_pi"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the CI_PI instance from peripheral base address.
 *
 * @param base CI_PI peripheral base address.
 * @return CI_PI instance.
 */
uint32_t CI_PI_GetInstance(CI_PI_CSR_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of CI_PI peripheral base address. */
static CI_PI_CSR_Type *const s_cipiBases[] = CI_PI_CSR_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of CI_PI clock name. */
static const clock_ip_name_t s_cipiClock[] = CI_PI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t CI_PI_GetInstance(CI_PI_CSR_Type *base)
{
    uint32_t instance;
    uint32_t cipiArrayCount = (sizeof(s_cipiBases) / sizeof(s_cipiBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < cipiArrayCount; instance++)
    {
        if (s_cipiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < cipiArrayCount);

    return instance;
}

/*!
 * brief Enables and configures the CI_PI peripheral module.
 *
 * param base CI_PI peripheral address.
 * param config CI_PI module configuration structure.
 */
void CI_PI_Init(CI_PI_CSR_Type *base, const ci_pi_config_t *config)
{
    uint32_t ifCtrl   = 0U;
    uint32_t csiCtrl0 = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable cipi clock */
    (void)CLOCK_EnableClock(s_cipiClock[CI_PI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    CI_PI_Reset(base);

    CI_PI_Stop(base);

    /* Configure the pixel link. */
    ifCtrl = CI_PI_CSR_IF_CTRL_REG_PL_ADDR(config->pixelLinkAddr);

    base->IF_CTRL_REG.RW = ifCtrl;

    /* Enable the pixel link. */
    base->IF_CTRL_REG.SET = CI_PI_CSR_IF_CTRL_REG_PL_ENABLE_MASK | CI_PI_CSR_IF_CTRL_REG_PL_VALID_MASK;

    /* Configure the CSI. */
    csiCtrl0 = CI_PI_CSR_CSI_CTRL_REG_HSYNC_FORCE_EN_MASK | CI_PI_CSR_CSI_CTRL_REG_VSYNC_FORCE_EN_MASK |
               CI_PI_CSR_CSI_CTRL_REG_CCIR_VSYNC_RESET_EN_MASK | config->polarityFlags /* Signal polarity. */
               | CI_PI_CSR_CSI_CTRL_REG_MASK_VSYNC_COUNTER(2)                          /* Mask 2 frames. */
               | CI_PI_CSR_CSI_CTRL_REG_CCIR_ECC_ERR_CORRECT_EN_MASK                   /* Enable ECC correction. */
               | CI_PI_CSR_CSI_CTRL_REG_HSYNC_PULSE(config->hsyncWidth)                /* Set HSYNC pulse. */
               | CI_PI_CSR_CSI_CTRL_REG_DATA_TYPE_IN(config->inputFormat)              /* CSI data format. */
               | (uint32_t)config->workMode;                                           /* CSI work mode. */

    if (config->useExtVsync)
    {
        csiCtrl0 |= CI_PI_CSR_CSI_CTRL_REG_CCIR_EXT_VSYNC_EN_MASK;
    }

    if (config->swapUV)
    {
        csiCtrl0 |= CI_PI_CSR_CSI_CTRL_REG_UV_SWAP_EN_MASK;
    }

    base->CSI_CTRL_REG.RW = csiCtrl0;

    /* CSI_CTRL_REG1[VSYNC_PULSE] means the pixel clock count of VSYNC. */
    base->CSI_CTRL_REG1.RW = CI_PI_CSR_CSI_CTRL_REG1_VSYNC_PULSE(
                                 config->vsyncWidth * ((uint32_t)config->width + (uint32_t)config->hsyncWidth)) |
                             CI_PI_CSR_CSI_CTRL_REG1_PIXEL_WIDTH((uint32_t)config->width - 1U);
}

/*!
 * brief Disables the CI_PI peripheral module.
 *
 * param base CI_PI peripheral address.
 */
void CI_PI_Deinit(CI_PI_CSR_Type *base)
{
    CI_PI_Stop(base);
    CI_PI_Reset(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable cipi clock */
    (void)CLOCK_EnableClock(s_cipiClock[CI_PI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get the default configuration to initialize CI_PI.
 *
 * The default configuration value is:
 *
 * code
    config->width = 0;
    config->vsyncWidth = 3U;
    config->hsyncWidth = 2U;
    config->polarityFlags = 0;
    config->pixelLinkAddr = 0;
    config->inputFormat = kCI_PI_InputUYVY8888_8BitBus;
    config->workMode = kCI_PI_NonGatedClockMode;
    config->useExtVsync = false;
    config->swapUV = false;
    endcode
 *
 * param config Pointer to the configuration.
 */
void CI_PI_GetDefaultConfig(ci_pi_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->width         = 0;
    config->vsyncWidth    = 3U;
    config->hsyncWidth    = 2U;
    config->polarityFlags = 0;
    config->pixelLinkAddr = 0;
    config->inputFormat   = kCI_PI_InputUYVY8888_8BitBus;
    config->workMode      = kCI_PI_NonGatedClockMode;
    config->useExtVsync   = false;
    config->swapUV        = false;
}

/*!
 * brief Starts the CI_PI peripheral module to output captured frame.
 *
 * param base CI_PI peripheral address.
 */
void CI_PI_Start(CI_PI_CSR_Type *base)
{
    /* Enable the CSI. */
    base->CSI_CTRL_REG.SET = CI_PI_CSR_CSI_CTRL_REG_CSI_EN_MASK;
    /* Disable force sync, then the input signal is processed. */
    base->CSI_CTRL_REG.CLR = CI_PI_CSR_CSI_CTRL_REG_HSYNC_FORCE_EN_MASK | CI_PI_CSR_CSI_CTRL_REG_VSYNC_FORCE_EN_MASK;
}

/*!
 * brief Stops the CI_PI peripheral module.
 *
 * param base CI_PI peripheral address.
 */
void CI_PI_Stop(CI_PI_CSR_Type *base)
{
    /* Disable the CSI. */
    base->CSI_CTRL_REG.CLR = CI_PI_CSR_CSI_CTRL_REG_CSI_EN_MASK;
    /* Enable force sync, the signal is latched. */
    base->CSI_CTRL_REG.SET = CI_PI_CSR_CSI_CTRL_REG_HSYNC_FORCE_EN_MASK | CI_PI_CSR_CSI_CTRL_REG_VSYNC_FORCE_EN_MASK;
}
