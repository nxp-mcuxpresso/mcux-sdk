/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PRG_H_
#define _FSL_PRG_H_

#include "fsl_common.h"

/*!
 * @addtogroup prg
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Driver version. */
#define FSL_PRG_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))

/*!
 * @brief Data type of the frame buffer.
 */
typedef enum _prg_data_type
{
    kPRG_DataType32Bpp = 0x0U, /*!< 32 bits per pixel. */
    kPRG_DataType24Bpp,        /*!< 24 bits per pixel. */
    kPRG_DataType16Bpp,        /*!< 16 bits per pixel. */
    kPRG_DataType8Bpp,         /*!< 8 bits per pixel. */
} prg_data_type_t;

/*!
 * @brief Frame buffer configuration.
 */
typedef struct _prg_buffer_config
{
    uint16_t width;           /*!< Frame buffer width. */
    uint16_t height;          /*!< Frame buffer height. */
    uint16_t strideBytes;     /*!< Stride, must be 8 bytes aligned. */
    prg_data_type_t dataType; /*!< Data type. */
} prg_buffer_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables and configures the PRG peripheral module.
 *
 * @param base PRG peripheral address.
 */
void PRG_Init(PRG_Type *base);

/*!
 * @brief Disables the PRG peripheral module.
 *
 * @param base PRG peripheral address.
 */
void PRG_Deinit(PRG_Type *base);

/*!
 * @brief Enable or disable the PRG.
 *
 * If enabled, display controller fetches data from PRG. If disabled, display
 * controller fetches data from frame buffer.
 *
 * @param base PRG peripheral address.
 * @param enable Pass in true to enable, false to disable
 */
static inline void PRG_Enable(PRG_Type *base, bool enable)
{
    if (enable)
    {
        base->PRG_CTRL.CLR = PRG_PRG_CTRL_BYPASS_MASK;
    }
    else
    {
        base->PRG_CTRL.SET = PRG_PRG_CTRL_BYPASS_MASK;
    }
}

/*!
 * @brief Enable or disable the shadow load.
 *
 * If disabled, the function @ref PRG_UpdateRegister makes the new configurations
 * take effect immediately. If enabled, after calling @ref PRG_UpdateRegister,
 * the new configurations take effect at next frame.
 *
 * @param base PRG peripheral address.
 * @param enable Pass in true to enable, false to disable
 */
static inline void PRG_EnableShadowLoad(PRG_Type *base, bool enable)
{
    if (enable)
    {
        base->PRG_CTRL.SET = PRG_PRG_CTRL_SHADOW_EN_MASK;
    }
    else
    {
        base->PRG_CTRL.CLR = PRG_PRG_CTRL_SHADOW_EN_MASK;
    }
}

/*!
 * @brief Update the registers.
 *
 * New configurations set to PRG registers will not take effect immediately until
 * this function is called. If the shadow is disabled by @ref PRG_EnableShadowLoad,
 * the new configurations take effect immediately after this function is called.
 * If the shadow is enabled by @ref PRG_EnableShadowLoad, the new configurations
 * take effect at next frame after this function is called.
 *
 * @param base PRG peripheral address.
 */
static inline void PRG_UpdateRegister(PRG_Type *base)
{
    base->PRG_REG_UPDATE.RW = PRG_PRG_REG_UPDATE_REG_UPDATE_MASK;
}

/*!
 * @brief Set the frame buffer configuration.
 *
 * @param base PRG peripheral address.
 * @param config Pointer to the configuration.
 */
void PRG_SetBufferConfig(PRG_Type *base, const prg_buffer_config_t *config);

/*!
 * @brief Get the frame buffer default configuration.
 *
 * The default configuration is:
 *
 * @code
    config->width = 1080U;
    config->height = 1920U;
    config->strideBytes = 4U * 1080U;
    config->dataType = kPRG_DataType32Bpp;
   @endcode
 *
 * @param config Pointer to the configuration.
 */
void PRG_BufferGetDefaultConfig(prg_buffer_config_t *config);

/*!
 * @brief Set the frame buffer address.
 *
 * @param base PRG peripheral address.
 * @param addr Frame buffer address.
 */
static inline void PRG_SetBufferAddr(PRG_Type *base, uint32_t addr)
{
    base->PRG_BADDR.RW = addr;
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _FSL_PRG_H_ */
