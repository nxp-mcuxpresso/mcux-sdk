/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DPR_H_
#define _FSL_DPR_H_

#include "fsl_common.h"

/*!
 * @addtogroup dpr
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Driver version. */
#define FSL_DPR_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))

/*!
 * @brief Data type of the frame buffer.
 */
typedef enum _dpr_data_type
{
    kDPR_DataType16Bpp = 1U, /*!< 16 bits per pixel. */
    kDPR_DataType32Bpp = 2U, /*!< 32 bits per pixel. */
} dpr_data_type_t;

/*!
 * @brief Frame buffer configuration.
 */
typedef struct _dpr_buffer_config
{
    uint16_t width;           /*!< Frame buffer width, how many pixels per line. */
    uint16_t height;          /*!< Frame buffer height. */
    uint16_t strideBytes;     /*!< Stride in bytes. */
    dpr_data_type_t dataType; /*!< Data type. */
} dpr_buffer_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables and configures the DPR peripheral module.
 *
 * @param base DPR peripheral address.
 */
void DPR_Init(DPR_Type *base);

/*!
 * @brief Disables the DPR peripheral module.
 *
 * @param base DPR peripheral address.
 */
void DPR_Deinit(DPR_Type *base);

/*!
 * @brief Set the input frame buffer configuration.
 *
 * @param base DPR peripheral address.
 * @param config Pointer to the configuration.
 */
void DPR_SetBufferConfig(DPR_Type *base, const dpr_buffer_config_t *config);

/*!
 * @brief Get the input frame buffer default configuration.
 *
 * The default configuration is
 * @code
    config->width = 1080U;
    config->height = 1920U;
    config->strideBytes = 4U * 1080U;
    config->dataType = kDPR_DataType32Bpp;
   @endcode
 *
 * @param config Pointer to the configuration.
 */
void DPR_BufferGetDefaultConfig(dpr_buffer_config_t *config);

/*!
 * @brief Starts the DPR
 *
 * This function trigers the DPR to load the new configuration and start
 * processing the next frame. It should be called before display started.
 *
 * @param base DPR peripheral address.
 */
static inline void DPR_Start(DPR_Type *base)
{
    base->SYSTEM_CTRL0.RW = DPR_SYSTEM_CTRL0_SW_SHADOW_LOAD_SEL_MASK | DPR_SYSTEM_CTRL0_SHADOW_LOAD_EN_MASK;

    base->SYSTEM_CTRL0.RW =
        DPR_SYSTEM_CTRL0_SW_SHADOW_LOAD_SEL_MASK | DPR_SYSTEM_CTRL0_SHADOW_LOAD_EN_MASK | DPR_SYSTEM_CTRL0_RUN_EN_MASK;
}

/*!
 * @brief Starts the DPR to run repeatly.
 *
 * This function should be called after display started. The display signal trigers
 * the new configuration loading repeatly.
 *
 * @param base DPR peripheral address.
 */
static inline void DPR_StartRepeat(DPR_Type *base)
{
    base->SYSTEM_CTRL0.RW =
        DPR_SYSTEM_CTRL0_REPEAT_EN_MASK | DPR_SYSTEM_CTRL0_SHADOW_LOAD_EN_MASK | DPR_SYSTEM_CTRL0_RUN_EN_MASK;
}

/*!
 * @brief Stops the DPR
 *
 * @param base DPR peripheral address.
 */
static inline void DPR_Stop(DPR_Type *base)
{
    base->SYSTEM_CTRL0.RW = DPR_SYSTEM_CTRL0_SW_SHADOW_LOAD_SEL_MASK | DPR_SYSTEM_CTRL0_SHADOW_LOAD_EN_MASK;
}

/*!
 * @brief Set the frame buffer address.
 *
 * @param base DPR peripheral address.
 * @param addr Frame buffer address.
 */
static inline void DPR_SetBufferAddr(DPR_Type *base, uint32_t addr)
{
    base->FRAME_1P_BASE_ADDR_CTRL0.RW = addr;
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _FSL_DPR_H_ */
