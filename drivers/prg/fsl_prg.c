/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_prg.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.prg"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PRG_ALIGN_UP(x, align) ((((x)-1U) | ((align)-1U)) + 1U)

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
 * brief Initialize PRG peripheral module.
 *
 * param base PRG peripheral address.
 */
void PRG_Init(PRG_Type *base)
{
}

/*!
 * brief Deinitialize the PRG peripheral module.
 *
 * param base PRG peripheral address.
 */
void PRG_Deinit(PRG_Type *base)
{
}

/*!
 * brief Set the frame buffer configuration.
 *
 * param base PRG peripheral address.
 * param addr Frame buffer address.
 */
void PRG_SetBufferConfig(PRG_Type *base, const prg_buffer_config_t *config)
{
    assert(config != NULL);

    base->PRG_HEIGHT.RW = (uint32_t)config->height - 1U;
    base->PRG_WIDTH.RW  = (uint32_t)config->width - 1U;
    base->PRG_STRIDE.RW = (uint32_t)config->strideBytes - 1U;
    base->PRG_OFFSET.RW = 0U;
    base->PRG_CTRL.RW   = (base->PRG_CTRL.RW & ~PRG_PRG_CTRL_DES_DATA_TYPE_MASK) |
                        (PRG_PRG_CTRL_DES_DATA_TYPE(config->dataType) | PRG_PRG_CTRL_SHADOW_LOAD_MODE_MASK);
}

/*!
 * brief Get the frame buffer default configuration.
 *
 * param config Pointer to the configuration.
 */
void PRG_BufferGetDefaultConfig(prg_buffer_config_t *config)
{
    assert(config != NULL);

    config->width       = 1080U;
    config->height      = 1920U;
    config->strideBytes = 4U * 1080U;
    config->dataType    = kPRG_DataType32Bpp;
}
