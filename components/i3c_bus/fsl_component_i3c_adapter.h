/*
 * Copyright 2020, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _I3C_COMPONENT_ADAPTER_H_
#define _I3C_COMPONENT_ADAPTER_H_

#include "fsl_component_i3c.h"
#include "fsl_i3c.h"
/*!
 * @addtogroup I3C_Bus_Component
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief I3C master transfer mode. */
typedef enum _i3c_master_transfer_mode
{
    kI3C_MasterTransferInterruptMode = 0, /*!< I3C master do transfer in interrupt mode. */
    kI3C_MasterTransferInterruptDMAMode,  /*!< I3C master do transfer in DMA mode. */
} i3c_master_transfer_mode_t;

/*! @brief I3C master adapter internal resource*/
typedef struct _i3c_master_adapter_resource
{
    I3C_Type *base;                       /*!< I3C master base address. */
    uint32_t clockInHz;                   /*!< I3C module clock frequency. */
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
    uint32_t slowClockInHz;               /*!< I3C slow clock frequency. */
#endif
    i3c_master_transfer_mode_t transMode; /*!< I3C master transfer mode. */
} i3c_master_adapter_resource_t;

/*! @brief I3C device adapter internal resource*/
typedef struct _i3c_device_adapter_resource
{
    I3C_Type *base;                         /*!< I3C device base address. */
    uint32_t clockInHz;                     /*!< I3C device clock frequency. */
    i3c_slave_transfer_callback_t callback; /*!< I3C device transfer callback function. */
} i3c_device_adapter_resource_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief I3C device master operation pointers structure */
extern const i3c_device_hw_ops_t master_ops;
/*! @brief I3C device slave operation pointers structure */
extern const i3c_device_hw_ops_t slave_ops;

#endif
