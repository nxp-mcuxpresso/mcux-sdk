/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dpr.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dpr"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DPR_ALIGN_UP(x, align) ((((uint32_t)(x)-1U) | ((align)-1U)) + 1U)

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
 * brief Initialize DPR peripheral module.
 *
 * param base DPR peripheral address.
 */
void DPR_Init(DPR_Type *base)
{
}

/*!
 * brief Deinitialize the DPR peripheral module.
 *
 * param base DPR peripheral address.
 */
void DPR_Deinit(DPR_Type *base)
{
}

/*!
 * brief Set the frame buffer configuration.
 *
 * param base DPR peripheral address.
 * param addr Frame buffer address.
 */
void DPR_SetBufferConfig(DPR_Type *base, const dpr_buffer_config_t *config)
{
    assert(config != NULL);

    /*
     * Current implementation only supports liner type frame buffer, so the
     * configuration could be simplized, including stride, dimension.
     */

    uint32_t modeCtrl        = 0U;
    uint8_t numPixelIn64Byte = 0U; /* How many pixels per 64-byte. */

    /* Pixel format. */
    modeCtrl |= DPR_MODE_CTRL0_PIX_SIZE(config->dataType);

    if (kDPR_DataType32Bpp == config->dataType)
    {
        /* Display controller handles the pixel component order, DPR will not handle it. */
        modeCtrl |= (DPR_MODE_CTRL0_A_COMP_SEL(3U) | DPR_MODE_CTRL0_R_COMP_SEL(2U) | DPR_MODE_CTRL0_G_COMP_SEL(1U) |
                     DPR_MODE_CTRL0_B_COMP_SEL(0U));

        numPixelIn64Byte = 16U;
    }
    else
    {
        numPixelIn64Byte = 32U;
    }

    base->MODE_CTRL0.RW = modeCtrl | DPR_MODE_CTRL0_RTR_4LINE_BUF_EN_MASK;

    /* Stride */
    base->FRAME_CTRL0.RW =
        (base->FRAME_CTRL0.RW & ~DPR_FRAME_CTRL0_PITCH_MASK) | DPR_FRAME_CTRL0_PITCH(config->strideBytes);

    /* Dimension. */
    base->FRAME_1P_PIX_X_CTRL.RW = DPR_ALIGN_UP(config->width, numPixelIn64Byte);

    /* When DPR_MODE_CTRL0_RTR_4LINE_BUF_EN_MASK is set, up aligned to 4,
     * When DPR_MODE_CTRL0_RTR_4LINE_BUF_EN_MASK is clear, up aligned to 8.
     */
    base->FRAME_1P_PIX_Y_CTRL.RW = DPR_ALIGN_UP(config->height, 4U);

    base->RTRAM_CTRL0.RW = DPR_RTRAM_CTRL0_THRES_LOW(3) | DPR_RTRAM_CTRL0_THRES_HIGH(7);
}

/*!
 * brief Get the input frame buffer default configuration.
 *
 * param config Pointer to the configuration.
 */
void DPR_BufferGetDefaultConfig(dpr_buffer_config_t *config)
{
    assert(config != NULL);

    config->width       = 1080U;
    config->height      = 1920U;
    config->strideBytes = 4U * 1080U;
    config->dataType    = kDPR_DataType32Bpp;
}
