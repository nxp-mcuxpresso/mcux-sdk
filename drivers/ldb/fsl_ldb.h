/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_LDB_H_
#define _FSL_LDB_H_

#include "fsl_common.h"

/*!
 * @addtogroup ldb
 * @{
 */

/*! @file */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LDB driver version. */
#define FSL_LDB_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

/*! @brief LDB output bus format. */
typedef enum _ldb_output_bus
{
    kLDB_OutputRGB666_7Bit_SPWG = 0U,
#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    kLDB_OutputRGB888_7Bit_SPWG  = LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK,
    kLDB_OutputRGB888_7Bit_JEIDA = LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK | LDB_PM_CTRL_REG_CH0_BIT_MAPPING_MASK,
#else
    kLDB_OutputRGB888_7Bit_SPWG = LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK | LDB_PM_CTRL_REG_DI0_DATA_WIDTH(1),
    kLDB_OutputRGB888_7Bit_JEIDA =
        LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK | LDB_PM_CTRL_REG_DI0_DATA_WIDTH(1) | LDB_PM_CTRL_REG_CH0_BIT_MAPPING_MASK,
    kLDB_OutputRGB101010_10Bit_SPWG = LDB_PM_CTRL_REG_CH0_10B_EN_MASK | LDB_PM_CTRL_REG_DI0_DATA_WIDTH(2),
    kLDB_OutputRGB101010_10Bit_JEIDA =
        LDB_PM_CTRL_REG_CH0_10B_EN_MASK | LDB_PM_CTRL_REG_DI0_DATA_WIDTH(2) | LDB_PM_CTRL_REG_CH0_BIT_MAPPING_MASK,
#endif /* FSL_FEATURE_LDB_COMBO_PHY */
} ldb_output_bus_t;

/*! @brief LDB input signal priority. */
enum _ldb_input_flag
{
    kLDB_InputVsyncActiveLow         = 0U,       /*!< VSYNC active low. */
    kLDB_InputVsyncActiveHigh        = 1U << 0U, /*!< VSYNC active high. */
    kLDB_InputHsyncActiveLow         = 0U,       /*!< HSYNC active low. */
    kLDB_InputHsyncActiveHigh        = 1U << 1U, /*!< HSYNC active high. */
    kLDB_InputDataLatchOnFallingEdge = 0U,       /*!< Latch data on falling clock edge. */
    kLDB_InputDataLatchOnRisingEdge  = 1U << 2U, /*!< Latch data on rising clock edge. */
};

/*! @brief LDB channel configuration. */
typedef struct _ldb_channel_config
{
    ldb_output_bus_t outputBus; /*!< Output bus format.   */
    uint32_t inputFlag;         /*!< Input flag, OR'ed value of _ldb_input_flag. */
    uint32_t pixelClock_Hz;     /*!< Pixel clock in HZ.   */
} ldb_channel_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initializes the LDB module.
 *
 * @param base LDB peripheral base address.
 */
void LDB_Init(LDB_Type *base);

/*!
 * @brief De-initializes the LDB module.
 *
 * @param base LDB peripheral base address.
 */
void LDB_Deinit(LDB_Type *base);

/*!
 * @brief Initializes the LDB channel.
 *
 * @param base LDB peripheral base address.
 * @param channel Channel index.
 * @param config Pointer to the configuration.
 * @return Return kStatus_Success if success.
 */
status_t LDB_InitChannel(LDB_Type *base, uint8_t channel, const ldb_channel_config_t *config);

/*!
 * @brief De-initializes the LDB channel.
 *
 * @param base LDB peripheral base address.
 * @param channel Channel index.
 */
void LDB_DeinitChannel(LDB_Type *base, uint8_t channel);

#if defined(__cplusplus)
}
#endif /*_cplusplus*/
/*@}*/

#endif /* _FSL_LDB_H_ */
