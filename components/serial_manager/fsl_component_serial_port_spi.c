/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_component_serial_manager.h"
#include "fsl_component_serial_port_internal.h"

#if (defined(SERIAL_PORT_TYPE_SPI) && (SERIAL_PORT_TYPE_SPI > 0U))
#include "fsl_adapter_spi.h"
#include "fsl_component_serial_port_spi.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef NDEBUG
#if (defined(DEBUG_CONSOLE_ASSERT_DISABLE) && (DEBUG_CONSOLE_ASSERT_DISABLE > 0U))
#undef assert
#define assert(n)
#else
/* MISRA C-2012 Rule 17.2 */
#undef assert
#define assert(n) \
    while (!(n))  \
    {             \
        ;         \
    }
#endif
#endif

#define SERIAL_PORT_SPI_RECEIVE_DATA_LENGTH 1U
#define SERIAL_MANAGER_BLOCK_OFFSET         (12U)

typedef struct _serial_spi_master_send_state
{
    uint8_t *buffer;
    uint32_t length;
    serial_manager_callback_t callback;
    void *callbackParam;
} serial_spi_master_send_state_t;

typedef struct _serial_spi_master_recv_state
{
    uint8_t *buffer;
    uint32_t length;
    serial_manager_callback_t callback;
    void *callbackParam;
} serial_spi_master_recv_state_t;

typedef struct _serial_spi_master_state
{
    HAL_SPI_MASTER_HANDLE_DEFINE(spiMasterHandleBuffer);
    uint32_t configFlags;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serial_spi_master_send_state_t tx;
    serial_spi_master_recv_state_t rx;
#endif
} serial_spi_master_state_t;

typedef struct _serial_spi_slave_send_state
{
    uint8_t *buffer;
    uint32_t length;
    serial_manager_callback_t callback;
    void *callbackParam;
} serial_spi_slave_send_state_t;

typedef struct _serial_spi_slave_recv_state
{
    uint8_t *buffer;
    uint32_t length;
    serial_manager_callback_t callback;
    void *callbackParam;
} serial_spi_slave_recv_state_t;

typedef struct _serial_spi_slave_state
{
    HAL_SPI_SLAVE_HANDLE_DEFINE(spiSlaveHandleBuffer);
    uint32_t configFlags;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serial_spi_slave_send_state_t tx;
    serial_spi_slave_recv_state_t rx;
#endif
} serial_spi_slave_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
void Serial_SpiMasterTxCallback(hal_spi_master_handle_t handle, hal_spi_status_t status, void *callbackParam)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    serial_manager_callback_message_t msg;

    if (NULL != callbackParam)
    {
        serialSpiMasterHandle = (serial_spi_master_state_t *)callbackParam;
        if (NULL != serialSpiMasterHandle->tx.callback)
        {
            serial_manager_status_t serialManagerStatus = kStatus_SerialManager_Success;
            msg.buffer                                  = serialSpiMasterHandle->tx.buffer;
            msg.length                                  = serialSpiMasterHandle->tx.length;
            if (NULL != serialSpiMasterHandle->tx.callback)
            {
                serialSpiMasterHandle->tx.callback(serialSpiMasterHandle->tx.callbackParam, &msg, serialManagerStatus);
            }
        }
    }
}

void Serial_SpiMasterRxCallback(hal_spi_master_handle_t handle, hal_spi_status_t status, void *callbackParam)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    serial_manager_callback_message_t msg;

    if (NULL != callbackParam)
    {
        serialSpiMasterHandle                       = (serial_spi_master_state_t *)callbackParam;
        serial_manager_status_t serialManagerStatus = kStatus_SerialManager_Success;
        msg.buffer                                  = serialSpiMasterHandle->rx.buffer;
        msg.length                                  = serialSpiMasterHandle->rx.length;
        if (NULL != serialSpiMasterHandle->rx.callback)
        {
            serialSpiMasterHandle->rx.callback(serialSpiMasterHandle->rx.callbackParam, &msg, serialManagerStatus);
        }
    }
}

void Serial_SpiSlaveTxCallback(hal_spi_slave_handle_t handle, hal_spi_status_t status, void *callbackParam)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;
    serial_manager_callback_message_t msg;

    if (NULL != callbackParam)
    {
        serialSpiSlaveHandle                        = (serial_spi_slave_state_t *)callbackParam;
        serial_manager_status_t serialManagerStatus = kStatus_SerialManager_Success;
        msg.buffer                                  = serialSpiSlaveHandle->tx.buffer;
        msg.length                                  = serialSpiSlaveHandle->tx.length;
        if (NULL != serialSpiSlaveHandle->tx.callback)
        {
            serialSpiSlaveHandle->tx.callback(serialSpiSlaveHandle->tx.callbackParam, &msg, serialManagerStatus);
        }
    }
}

void Serial_SpiSlaveRxCallback(hal_spi_slave_handle_t handle, hal_spi_status_t status, void *callbackParam)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;
    serial_manager_callback_message_t msg;
    if (NULL != callbackParam)
    {
        serialSpiSlaveHandle                        = (serial_spi_slave_state_t *)callbackParam;
        serial_manager_status_t serialManagerStatus = kStatus_SerialManager_Success;
        msg.buffer                                  = serialSpiSlaveHandle->rx.buffer;
        msg.length                                  = serialSpiSlaveHandle->rx.length;
        if (NULL != serialSpiSlaveHandle->rx.callback)
        {
            serialSpiSlaveHandle->rx.callback(serialSpiSlaveHandle->rx.callbackParam, &msg, serialManagerStatus);
        }
    }
}
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */
serial_manager_status_t Serial_SpiMasterInit(serial_handle_t serialHandle, void *serialConfig)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    serial_spi_master_config_t *serialSpiMasterConfig;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_dma_config_t *spi_dma_config;
#endif

    assert(serialHandle);
    assert(serialConfig);
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    assert((SERIAL_PORT_SPI_MASTER_HANDLE_SIZE - HAL_SPI_MASTER_DMA_HANDLE_SIZE) >= sizeof(serial_spi_master_state_t));
#else
    assert(SERIAL_PORT_SPI_MASTER_HANDLE_SIZE >= sizeof(serial_spi_master_state_t));
#endif
    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;
    serialSpiMasterConfig = (serial_spi_master_config_t *)serialConfig;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiMasterInit((hal_spi_master_handle_t)serialSpiMasterHandle->spiMasterHandleBuffer,
                          (const hal_spi_master_config_t *)serialSpiMasterConfig))
    {
        return kStatus_SerialManager_Error;
    }
    serialSpiMasterHandle->configFlags = serialSpiMasterConfig->configFlags;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    if (serialSpiMasterConfig->enableDMA == 1)
    {
        spi_dma_config = (hal_spi_dma_config_t *)serialSpiMasterConfig->dmaConfig;
        HAL_SpiMasterDMAInit((hal_spi_master_handle_t)serialSpiMasterHandle->spiMasterHandleBuffer,
                             (uint8_t *)serialSpiMasterHandle->spiMasterHandleBuffer +
                                 (SERIAL_PORT_SPI_MASTER_HANDLE_SIZE - HAL_SPI_MASTER_DMA_HANDLE_SIZE),
                             spi_dma_config);
    }

#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiMasterDeinit(serial_handle_t serialHandle)
{
    serial_spi_master_state_t *serialSpiMasterHandle;

    assert(serialHandle);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;

    (void)HAL_SpiMasterDeinit((hal_spi_master_handle_t)serialSpiMasterHandle->spiMasterHandleBuffer);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiSlaveInit(serial_handle_t serialHandle, void *serialConfig)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;
    serial_spi_slave_config_t *serialSpiSlaveConfig;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_dma_config_t *spi_dma_config;
#endif

    assert(serialHandle);
    assert(serialConfig);

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    assert((SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE - HAL_SPI_SLAVE_DMA_HANDLE_SIZE) >= sizeof(serial_spi_slave_state_t));
#else
    assert(SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE >= sizeof(serial_spi_slave_state_t));
#endif

    serialSpiSlaveHandle = (serial_spi_slave_state_t *)serialHandle;
    serialSpiSlaveConfig = (serial_spi_slave_config_t *)serialConfig;

    if (kStatus_HAL_SpiSuccess != HAL_SpiSlaveInit((hal_spi_slave_handle_t)serialSpiSlaveHandle->spiSlaveHandleBuffer,
                                                   (hal_spi_slave_config_t *)serialSpiSlaveConfig))
    {
        return kStatus_SerialManager_Error;
    }
    serialSpiSlaveHandle->configFlags = serialSpiSlaveConfig->configFlags;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    if (serialSpiSlaveConfig->enableDMA == 1)
    {
        spi_dma_config = (hal_spi_dma_config_t *)serialSpiSlaveConfig->dmaConfig;
        HAL_SpiSlaveDMAInit((hal_spi_slave_handle_t)serialSpiSlaveHandle->spiSlaveHandleBuffer,
                            (uint8_t *)serialSpiSlaveHandle->spiSlaveHandleBuffer +
                                (SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE - HAL_SPI_SLAVE_DMA_HANDLE_SIZE),
                            spi_dma_config);
    }

#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiSlaveDeinit(serial_handle_t serialHandle)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;

    assert(serialHandle);

    serialSpiSlaveHandle = (serial_spi_slave_state_t *)serialHandle;

    (void)HAL_SpiSlaveDeinit((hal_spi_slave_handle_t)serialSpiSlaveHandle->spiSlaveHandleBuffer);

    return kStatus_SerialManager_Success;
}

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

serial_manager_status_t Serial_SpiMasterWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    hal_spi_transfer_t mastetTransfer;

    assert(serialHandle);
    assert(buffer);
    assert(length);
    serialSpiMasterHandle            = (serial_spi_master_state_t *)serialHandle;
    serialSpiMasterHandle->tx.buffer = buffer;
    serialSpiMasterHandle->tx.length = (size_t)length;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiMasterTransferInstallCallback((hal_spi_master_handle_t)serialSpiMasterHandle->spiMasterHandleBuffer,
                                             Serial_SpiMasterTxCallback, serialHandle))
    {
        return kStatus_SerialManager_Error;
    }
    serialSpiMasterHandle   = (serial_spi_master_state_t *)serialHandle;
    mastetTransfer.txData   = buffer;
    mastetTransfer.rxData   = NULL;
    mastetTransfer.dataSize = (size_t)length;
    mastetTransfer.flags    = serialSpiMasterHandle->configFlags;

    return (serial_manager_status_t)HAL_SpiMasterTransferNonBlocking(
        ((hal_spi_master_handle_t)&serialSpiMasterHandle->spiMasterHandleBuffer[0]), &mastetTransfer);
}

serial_manager_status_t Serial_SpiSlaveWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;
    hal_spi_transfer_t slaveTransfer;
    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiSlaveHandle            = (serial_spi_slave_state_t *)serialHandle;
    serialSpiSlaveHandle->tx.buffer = buffer;
    serialSpiSlaveHandle->tx.length = (size_t)length;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiSlaveTransferInstallCallback((hal_spi_slave_handle_t)serialSpiSlaveHandle->spiSlaveHandleBuffer,
                                            Serial_SpiSlaveTxCallback, serialHandle))
    {
        return kStatus_SerialManager_Error;
    }
    slaveTransfer.txData   = buffer;
    slaveTransfer.rxData   = NULL;
    slaveTransfer.dataSize = (size_t)length;
    slaveTransfer.flags    = serialSpiSlaveHandle->configFlags;
    return (serial_manager_status_t)HAL_SpiSlaveTransferNonBlocking(
        ((hal_spi_slave_handle_t)&serialSpiSlaveHandle->spiSlaveHandleBuffer[0]), &slaveTransfer);
}

// read Serial_SpiMasterRead
serial_manager_status_t Serial_SpiMasterRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    hal_spi_transfer_t masterReceiver;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;

    serialSpiMasterHandle->rx.buffer = buffer;
    serialSpiMasterHandle->rx.length = (size_t)length;
    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiMasterTransferInstallCallback((hal_spi_master_handle_t)serialSpiMasterHandle->spiMasterHandleBuffer,
                                             Serial_SpiMasterRxCallback, serialHandle))
    {
        return kStatus_SerialManager_Error;
    }

    masterReceiver.txData   = NULL;
    masterReceiver.rxData   = buffer;
    masterReceiver.dataSize = (size_t)length;
    masterReceiver.flags    = serialSpiMasterHandle->configFlags;
    return (serial_manager_status_t)HAL_SpiMasterTransferNonBlocking(
        ((hal_spi_master_handle_t)&serialSpiMasterHandle->spiMasterHandleBuffer[0]), &masterReceiver);
}

serial_manager_status_t Serial_SpiSlaveRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;
    hal_spi_transfer_t slaveReceiver;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiSlaveHandle            = (serial_spi_slave_state_t *)serialHandle;
    serialSpiSlaveHandle->rx.buffer = buffer;
    serialSpiSlaveHandle->rx.length = (size_t)length;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiSlaveTransferInstallCallback((hal_spi_slave_handle_t)serialSpiSlaveHandle->spiSlaveHandleBuffer,
                                            Serial_SpiSlaveRxCallback, serialHandle))
    {
        return kStatus_SerialManager_Error;
    }
    slaveReceiver.txData   = NULL;
    slaveReceiver.rxData   = buffer;
    slaveReceiver.dataSize = (size_t)length;
    slaveReceiver.flags    = serialSpiSlaveHandle->configFlags;
    return (serial_manager_status_t)HAL_SpiSlaveTransferNonBlocking(
        ((hal_spi_slave_handle_t)&serialSpiSlaveHandle->spiSlaveHandleBuffer[0]), &slaveReceiver);
}

#else /* SERIAL_MANAGER_NON_BLOCKING_MODE */
serial_manager_status_t Serial_SpiMasterWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    hal_spi_transfer_t mastetTransfer;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;

    mastetTransfer.txData = buffer;
    mastetTransfer.rxData = NULL;
    mastetTransfer.dataSize = (size_t)length;
    return (serial_manager_status_t)HAL_SpiMasterTransferBlocking(
        ((hal_spi_master_handle_t)&serialSpiMasterHandle->spiMasterHandleBuffer[0]), &mastetTransfer);
}

serial_manager_status_t Serial_SpiMasterRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiMasterHandle;
    hal_spi_transfer_t masterReceiver;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;
    masterReceiver.txData = NULL;
    masterReceiver.rxData = buffer;
    masterReceiver.dataSize = (size_t)length;
    return (serial_manager_status_t)HAL_SpiMasterTransferBlocking(
        ((hal_spi_master_handle_t)&serialSpiMasterHandle->spiMasterHandleBuffer[0]), &masterReceiver);
}
#if 0
serial_manager_status_t Serial_SpiSlaveWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiSlaveHandle;
    hal_spi_transfer_t slaveTransfer;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiSlaveHandle      = (serial_spi_master_state_t *)serialHandle;

    slaveTransfer.txData   = buffer;
    slaveTransfer.rxData   = NULL;
    slaveTransfer.dataSize = (size_t)length;
    return (serial_manager_status_t)HAL_SpiSlaveTransferBlocking(
        ((hal_spi_master_handle_t)&serialSpiSlaveHandle->spiSlaveHandleBuffer[0]), &slaveTransfer);
}

serial_manager_status_t Serial_SpiSlaveRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_spi_master_state_t *serialSpiSlaveHandle;
    hal_spi_transfer_t slaveReceiver;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialSpiSlaveHandle    = (serial_spi_master_state_t *)serialHandle;
    slaveReceiver.txData   = NULL;
    slaveReceiver.rxData   = buffer;
    slaveReceiver.dataSize = (size_t)length;
    return (serial_manager_status_t)HAL_SpiSlaveTransferBlocking(
        ((hal_spi_master_handle_t)&serialSpiSlaveHandle->spiSlaveHandleBuffer[0]), &slaveReceiver);
}
#endif
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

serial_manager_status_t Serial_SpiMasterInstallTxCallback(serial_handle_t serialHandle,
                                                          serial_manager_callback_t callback,
                                                          void *callbackParam)
{
    serial_spi_master_state_t *serialSpiMasterHandle;

    assert(serialHandle);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;

    serialSpiMasterHandle->tx.callback      = callback;
    serialSpiMasterHandle->tx.callbackParam = callbackParam;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiMasterInstallRxCallback(serial_handle_t serialHandle,
                                                          serial_manager_callback_t callback,
                                                          void *callbackParam)
{
    serial_spi_master_state_t *serialSpiMasterHandle;

    assert(serialHandle);

    serialSpiMasterHandle = (serial_spi_master_state_t *)serialHandle;

    serialSpiMasterHandle->rx.callback      = callback;
    serialSpiMasterHandle->rx.callbackParam = callbackParam;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiSlaveInstallTxCallback(serial_handle_t serialHandle,
                                                         serial_manager_callback_t callback,
                                                         void *callbackParam)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;

    assert(serialHandle);

    serialSpiSlaveHandle = (serial_spi_slave_state_t *)serialHandle;

    serialSpiSlaveHandle->tx.callback      = callback;
    serialSpiSlaveHandle->tx.callbackParam = callbackParam;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiSlaveInstallRxCallback(serial_handle_t serialHandle,
                                                         serial_manager_callback_t callback,
                                                         void *callbackParam)
{
    serial_spi_slave_state_t *serialSpiSlaveHandle;

    assert(serialHandle);

    serialSpiSlaveHandle = (serial_spi_slave_state_t *)serialHandle;

    serialSpiSlaveHandle->rx.callback      = callback;
    serialSpiSlaveHandle->rx.callbackParam = callbackParam;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiMasterCancelWrite(serial_handle_t serialHandle)
{
    serial_spi_master_state_t *serialSpiMaster;

    assert(serialHandle);

    serialSpiMaster = (serial_spi_master_state_t *)serialHandle;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiMasterTransferAbort((hal_spi_master_handle_t)serialSpiMaster->spiMasterHandleBuffer))

    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_SpiSlaveCancelWrite(serial_handle_t serialHandle)
{
    serial_spi_slave_state_t *serialSpiSlave;

    assert(serialHandle);

    serialSpiSlave = (serial_spi_slave_state_t *)serialHandle;

    if (kStatus_HAL_SpiSuccess !=
        HAL_SpiSlaveTransferAbort((hal_spi_slave_handle_t)serialSpiSlave->spiSlaveHandleBuffer))

    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

#endif
