/*
 * Copyright 2019-2020 NXP
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
#define FSL_LDB_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

typedef MIPI_DSI_LVDS_COMBO_CSR_Type LDB_Type;

/*! @brief LDB output bus format. */
typedef enum _ldb_output_bus
{
    kLDB_OutputRGB666_7Bit_SPWG = 0U,
    kLDB_OutputRGB888_7Bit_SPWG = MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_DATA_WIDTH_MASK,
    kLDB_OutputRGB888_7Bit_JEIDA =
        MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_DATA_WIDTH_MASK | MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_BIT_MAPPING_MASK,
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
