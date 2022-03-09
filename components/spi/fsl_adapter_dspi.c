/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_dspi.h"

#include "fsl_adapter_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief hal_spi master state structure. */
typedef struct _hal_spi_master
{
    hal_spi_master_transfer_callback_t callback;
    void *callbackParam;
    dspi_master_handle_t hardwareHandle;
    uint8_t instance;
} hal_spi_master_t;

/*! @brief hal_spi slave state structure. */
typedef struct _hal_spi_slave
{
    hal_spi_slave_transfer_callback_t callback;
    void *callbackParam;
    dspi_slave_handle_t hardwareHandle;
    uint8_t instance;
} hal_spi_slave_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Base pointer array */
static SPI_Type *const s_spiBases[] = SPI_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

static hal_spi_status_t HAL_SpiGetStatus(status_t status)
{
    hal_spi_status_t returnStatus;
    switch (status)
    {
        case kStatus_Success:
        {
            returnStatus = kStatus_HAL_SpiSuccess;
            break;
        }
        case kStatus_DSPI_Busy:
        {
            returnStatus = kStatus_HAL_SpiBusy;
            break;
        }
        default:
        {
            returnStatus = kStatus_HAL_SpiError;
            break;
        }
    }
    return returnStatus;
}

static void HAL_SpiMasterCallback(SPI_Type *base, dspi_master_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_master_t *spiMasterHandle;

    assert(callbackParam);

    spiMasterHandle = (hal_spi_master_t *)callbackParam;

    if (spiMasterHandle->callback != NULL)
    {
        spiMasterHandle->callback(spiMasterHandle, HAL_SpiGetStatus(status), spiMasterHandle->callbackParam);
    }
}

static void HAL_SpiSlaveCallback(SPI_Type *base, dspi_slave_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_slave_t *spiSlaveHandle;

    assert(callbackParam);

    spiSlaveHandle = (hal_spi_slave_t *)callbackParam;

    if (spiSlaveHandle->callback != NULL)
    {
        spiSlaveHandle->callback(spiSlaveHandle, HAL_SpiGetStatus(status), spiSlaveHandle->callbackParam);
    }
}

hal_spi_status_t HAL_SpiMasterInit(hal_spi_master_handle_t handle, const hal_spi_master_config_t *config)
{
    hal_spi_master_t *masterHandle;
    dspi_master_config_t dspiConfig;
    assert(handle);
    assert(config);
    assert(HAL_SPI_MASTER_HANDLE_SIZE >= sizeof(hal_spi_master_t));

    masterHandle = (hal_spi_master_t *)handle;

    DSPI_MasterGetDefaultConfig(&dspiConfig);

    dspiConfig.ctarConfig.cpol = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kDSPI_ClockPolarityActiveHigh :
                                                                                         kDSPI_ClockPolarityActiveLow;
    dspiConfig.ctarConfig.cpha =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kDSPI_ClockPhaseFirstEdge : kDSPI_ClockPhaseSecondEdge;
    dspiConfig.ctarConfig.direction = (kHAL_SpiMsbFirst == config->direction) ? kDSPI_MsbFirst : kDSPI_LsbFirst;
    dspiConfig.ctarConfig.baudRate  = config->baudRate_Bps;

    masterHandle->instance = config->instance;

    DSPI_MasterInit((SPI_Type *)s_spiBases[masterHandle->instance], (void *)&dspiConfig, config->srcClock_Hz);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveInit(hal_spi_slave_handle_t handle, const hal_spi_slave_config_t *config)
{
    hal_spi_slave_t *slaveHandle;
    dspi_slave_config_t dspiConfig;
    assert(handle);
    assert(config);
    assert(HAL_SPI_SLAVE_HANDLE_SIZE >= sizeof(hal_spi_slave_t));

    slaveHandle = (hal_spi_slave_t *)handle;

    DSPI_SlaveGetDefaultConfig(&dspiConfig);

    dspiConfig.ctarConfig.cpol = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kDSPI_ClockPolarityActiveHigh :
                                                                                         kDSPI_ClockPolarityActiveLow;
    dspiConfig.ctarConfig.cpha =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kDSPI_ClockPhaseFirstEdge : kDSPI_ClockPhaseSecondEdge;

    slaveHandle->instance = config->instance;

    DSPI_SlaveInit((SPI_Type *)s_spiBases[slaveHandle->instance], (void *)&dspiConfig);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterDeinit(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;

    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
    DSPI_Deinit((SPI_Type *)s_spiBases[masterHandle->instance]);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveDeinit(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;

    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;

    DSPI_Deinit((SPI_Type *)s_spiBases[slaveHandle->instance]);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterTransferInstallCallback(hal_spi_master_handle_t handle,
                                                      hal_spi_master_transfer_callback_t callback,
                                                      void *callbackParam)
{
    hal_spi_master_t *masterHandle;

    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;

    masterHandle->callback      = callback;
    masterHandle->callbackParam = callbackParam;

    DSPI_MasterTransferCreateHandle((SPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle,
                                    HAL_SpiMasterCallback, masterHandle);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterTransferBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_master_t *masterHandle;
    dspi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    masterHandle = (hal_spi_master_t *)handle;

    transfer.txData   = xfer->txData;
    transfer.rxData   = xfer->rxData;
    transfer.dataSize = xfer->dataSize;
    transfer.configFlags =
        (uint32_t)kDSPI_MasterCtar0 | (uint32_t)kDSPI_MasterPcs0 | (uint32_t)kDSPI_MasterPcsContinuous;

    return HAL_SpiGetStatus(DSPI_MasterTransferBlocking((SPI_Type *)s_spiBases[masterHandle->instance], &transfer));
}

hal_spi_status_t HAL_SpiMasterTransferNonBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_master_t *masterHandle;
    dspi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    masterHandle      = (hal_spi_master_t *)handle;
    transfer.txData   = xfer->txData;
    transfer.rxData   = xfer->rxData;
    transfer.dataSize = xfer->dataSize;
    transfer.configFlags =
        (uint32_t)kDSPI_MasterCtar0 | (uint32_t)kDSPI_MasterPcs0 | (uint32_t)kDSPI_MasterPcsContinuous;
    return HAL_SpiGetStatus(DSPI_MasterTransferNonBlocking((SPI_Type *)s_spiBases[masterHandle->instance],
                                                           &masterHandle->hardwareHandle, &transfer));
}

hal_spi_status_t HAL_SpiMasterTransferGetCount(hal_spi_master_handle_t handle, size_t *spiCount)
{
    hal_spi_master_t *masterHandle;
    assert(handle);
    assert(spiCount);

    masterHandle = (hal_spi_master_t *)handle;
    return HAL_SpiGetStatus(DSPI_MasterTransferGetCount((SPI_Type *)s_spiBases[masterHandle->instance],
                                                        &masterHandle->hardwareHandle, spiCount));
}

hal_spi_status_t HAL_SpiMasterTransferAbort(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;
    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
    DSPI_MasterTransferAbort((SPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle);
    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveTransferInstallCallback(hal_spi_slave_handle_t handle,
                                                     hal_spi_slave_transfer_callback_t callback,
                                                     void *callbackParam)
{
    hal_spi_slave_t *slaveHandle;

    assert(handle);

    slaveHandle                = (hal_spi_slave_t *)handle;
    slaveHandle->callback      = callback;
    slaveHandle->callbackParam = callbackParam;

    DSPI_SlaveTransferCreateHandle((SPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle,
                                   HAL_SpiSlaveCallback, slaveHandle);
    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveTransferNonBlocking(hal_spi_slave_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_slave_t *slaveHandle;
    dspi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    slaveHandle       = (hal_spi_slave_t *)handle;
    transfer.txData   = xfer->txData;
    transfer.rxData   = xfer->rxData;
    transfer.dataSize = xfer->dataSize;
    transfer.configFlags =
        (uint32_t)kDSPI_MasterCtar0 | (uint32_t)kDSPI_MasterPcs0 | (uint32_t)kDSPI_MasterPcsContinuous;
    return HAL_SpiGetStatus(DSPI_SlaveTransferNonBlocking((SPI_Type *)s_spiBases[slaveHandle->instance],
                                                          &slaveHandle->hardwareHandle, &transfer));
}

hal_spi_status_t HAL_SpiSlaveTransferGetCount(hal_spi_slave_handle_t handle, size_t *spiCount)
{
    hal_spi_slave_t *slaveHandle;
    assert(handle);
    assert(spiCount);

    slaveHandle = (hal_spi_slave_t *)handle;
    return HAL_SpiGetStatus(DSPI_SlaveTransferGetCount((SPI_Type *)s_spiBases[slaveHandle->instance],
                                                       &slaveHandle->hardwareHandle, spiCount));
}

hal_spi_status_t HAL_SpiSlaveTransferAbort(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;
    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;
    DSPI_SlaveTransferAbort((SPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle);
    return kStatus_HAL_SpiSuccess;
}
