/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_spi.h"

#include "fsl_adapter_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief hal_spi master state structure. */
typedef struct _hal_spi_master
{
    hal_spi_master_transfer_callback_t callback;
    void *callbackParam;
    spi_master_handle_t hardwareHandle;
    uint8_t instance;
} hal_spi_master_t;

/*! @brief hal_spi slave state structure. */
typedef struct _hal_spi_slave
{
    hal_spi_slave_transfer_callback_t callback;
    void *callbackParam;
    spi_slave_handle_t hardwareHandle;
    uint8_t instance;
} hal_spi_slave_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map SPI instance number to base address. */
static const SPI_Type *s_spiBases[] = SPI_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

hal_spi_status_t HAL_SpiGetStatus(status_t status)
{
    hal_spi_status_t returnStatus;
    switch (status)
    {
        case kStatus_Success:
        {
            returnStatus = kStatus_HAL_SpiSuccess;
            break;
        }
        case kStatus_SPI_Busy:
        {
            returnStatus = kStatus_HAL_SpiBusy;
            break;
        }
        case kStatus_SPI_Idle:
        {
            returnStatus = kStatus_HAL_SpiIdle;
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

static void HAL_SpiMasterCallback(SPI_Type *base, spi_master_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_master_t *spiMasterHandle;
    assert(callbackParam);

    spiMasterHandle = (hal_spi_master_t *)callbackParam;

    if (spiMasterHandle->callback)
    {
        spiMasterHandle->callback(spiMasterHandle, HAL_SpiGetStatus(status), spiMasterHandle->callbackParam);
    }
}

static void HAL_SpiSlaveCallback(SPI_Type *base, spi_slave_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_slave_t *spiSlaveHandle;
    assert(callbackParam);

    spiSlaveHandle = (hal_spi_slave_t *)callbackParam;

    if (spiSlaveHandle->callback)
    {
        spiSlaveHandle->callback(spiSlaveHandle, HAL_SpiGetStatus(status), spiSlaveHandle->callbackParam);
    }
}

hal_spi_status_t HAL_SpiMasterInit(hal_spi_master_handle_t handle, const hal_spi_master_config_t *config)
{
    hal_spi_master_t *masterHandle;
    spi_master_config_t spiConfig;
    assert(handle);
    assert(config);

    if (HAL_SPI_MASTER_HANDLE_SIZE < sizeof(hal_spi_master_t))
    {
        return kStatus_HAL_SpiError;
    }

    masterHandle = (hal_spi_master_t *)handle;

    SPI_MasterGetDefaultConfig(&spiConfig);

    spiConfig.polarity = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kSPI_ClockPolarityActiveHigh :
                                                                                 kSPI_ClockPolarityActiveLow;
    spiConfig.phase =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kSPI_ClockPhaseFirstEdge : kSPI_ClockPhaseSecondEdge;
    spiConfig.direction    = (kHAL_SpiMsbFirst == config->direction) ? kSPI_MsbFirst : kSPI_LsbFirst;
    spiConfig.baudRate_Bps = config->baudRate_Bps;
    spiConfig.enableMaster = config->enableMaster;

    masterHandle->instance = config->instance;

    SPI_MasterInit((SPI_Type *)s_spiBases[masterHandle->instance], &spiConfig, config->srcClock_Hz);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveInit(hal_spi_slave_handle_t handle, const hal_spi_slave_config_t *config)
{
    hal_spi_slave_t *slaveHandle;
    spi_slave_config_t spiConfig;
    assert(handle);
    assert(config);

    if (HAL_SPI_SLAVE_HANDLE_SIZE < sizeof(hal_spi_slave_t))
    {
        return kStatus_HAL_SpiError;
    }

    slaveHandle = (hal_spi_slave_t *)handle;

    SPI_SlaveGetDefaultConfig(&spiConfig);

    spiConfig.polarity = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kSPI_ClockPolarityActiveHigh :
                                                                                 kSPI_ClockPolarityActiveLow;
    spiConfig.phase =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kSPI_ClockPhaseFirstEdge : kSPI_ClockPhaseSecondEdge;
    spiConfig.direction = (kHAL_SpiMsbFirst == config->direction) ? kSPI_MsbFirst : kSPI_LsbFirst;

    slaveHandle->instance = config->instance;

    SPI_SlaveInit((SPI_Type *)s_spiBases[slaveHandle->instance], &spiConfig);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterDeinit(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;

    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
    SPI_Deinit((SPI_Type *)s_spiBases[masterHandle->instance]);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveDeinit(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;

    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;

    SPI_Deinit((SPI_Type *)s_spiBases[slaveHandle->instance]);

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

    SPI_MasterTransferCreateHandle((SPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle,
                                   HAL_SpiMasterCallback, masterHandle);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterTransferBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_master_t *masterHandle;
    spi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    masterHandle = (hal_spi_master_t *)handle;

    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;

    return HAL_SpiGetStatus(SPI_MasterTransferBlocking((SPI_Type *)s_spiBases[masterHandle->instance], &transfer));
}

hal_spi_status_t HAL_SpiMasterTransferNonBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_master_t *masterHandle;
    spi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    masterHandle         = (hal_spi_master_t *)handle;
    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;
    return HAL_SpiGetStatus(SPI_MasterTransferNonBlocking((SPI_Type *)s_spiBases[masterHandle->instance],
                                                          &masterHandle->hardwareHandle, &transfer));
}

hal_spi_status_t HAL_SpiMasterTransferGetCount(hal_spi_master_handle_t handle, size_t *count)
{
    hal_spi_master_t *masterHandle;
    assert(handle);
    assert(count);

    masterHandle = (hal_spi_master_t *)handle;
    return HAL_SpiGetStatus(SPI_MasterTransferGetCount((SPI_Type *)s_spiBases[masterHandle->instance],
                                                       &masterHandle->hardwareHandle, count));
}

hal_spi_status_t HAL_SpiMasterTransferAbort(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;
    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
    SPI_MasterTransferAbort((SPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle);
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

    SPI_SlaveTransferCreateHandle((SPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle,
                                  HAL_SpiSlaveCallback, slaveHandle);
    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveTransferNonBlocking(hal_spi_slave_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_slave_t *slaveHandle;
    spi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    slaveHandle          = (hal_spi_slave_t *)handle;
    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;
    return HAL_SpiGetStatus(SPI_SlaveTransferNonBlocking((SPI_Type *)s_spiBases[slaveHandle->instance],
                                                         &slaveHandle->hardwareHandle, &transfer));
}

hal_spi_status_t HAL_SpiSlaveTransferGetCount(hal_spi_slave_handle_t handle, size_t *count)
{
    hal_spi_slave_t *slaveHandle;
    assert(handle);
    assert(count);

    slaveHandle = (hal_spi_slave_t *)handle;
    return HAL_SpiGetStatus(
        SPI_SlaveTransferGetCount((SPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle, count));
}

hal_spi_status_t HAL_SpiSlaveTransferAbort(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;
    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;
    SPI_SlaveTransferAbort((SPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle);
    return kStatus_HAL_SpiSuccess;
}
