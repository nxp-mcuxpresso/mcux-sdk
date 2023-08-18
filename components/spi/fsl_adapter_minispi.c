/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adapter_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

hal_spi_status_t HAL_SpiMasterInit(hal_spi_master_handle_t handle, const hal_spi_master_config_t *config)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveInit(hal_spi_slave_handle_t handle, const hal_spi_slave_config_t *config)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterDeinit(hal_spi_master_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveDeinit(hal_spi_slave_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterTransferInstallCallback(hal_spi_master_handle_t handle,
                                                      hal_spi_master_transfer_callback_t callback,
                                                      void *callbackParam)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterTransferBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterTransferNonBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterTransferGetCount(hal_spi_master_handle_t handle, size_t *count)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiMasterTransferAbort(hal_spi_master_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveTransferInstallCallback(hal_spi_slave_handle_t handle,
                                                     hal_spi_slave_transfer_callback_t callback,
                                                     void *callbackParam)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveTransferNonBlocking(hal_spi_slave_handle_t handle, hal_spi_transfer_t *xfer)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveTransferGetCount(hal_spi_slave_handle_t handle, size_t *count)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}

hal_spi_status_t HAL_SpiSlaveTransferAbort(hal_spi_slave_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_SpiError;
}
