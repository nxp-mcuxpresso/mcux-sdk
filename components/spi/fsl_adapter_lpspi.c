/*
 * Copyright 2018 -2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_lpspi.h"

#include "fsl_adapter_spi.h"
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U)) || \
    (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
#include "fsl_lpspi_edma.h"
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#include "fsl_lpspi_dma.h"
#endif
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
#endif /* HAL_UART_DMA_ENABLE */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(__GIC_PRIO_BITS)
#ifndef HAL_SPI_ISR_PRIORITY
#define HAL_SPI_ISR_PRIORITY (25U)
#endif
#else
#if defined(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#ifndef HAL_SPI_ISR_PRIORITY
#define HAL_SPI_ISR_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#endif
#else
/* The default value 3 is used to support different ARM Core, such as CM0P, CM4, CM7, and CM33, etc.
 * The minimum number of priority bits implemented in the NVIC is 2 on these SOCs. The value of mininum
 * priority is 3 (2^2 - 1). So, the default value is 3.
 */
#ifndef HAL_SPI_ISR_PRIORITY
#define HAL_SPI_ISR_PRIORITY (3U)
#endif
#endif
#endif

/*! @brief hal_spi master state structure. */
typedef struct _hal_spi_master
{
    hal_spi_master_transfer_callback_t callback;
    void *callbackParam;
    lpspi_master_handle_t hardwareHandle;
    uint8_t instance;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_master_dma_handle_t *dmaHandle;
#endif

} hal_spi_master_t;

/*! @brief hal_spi slave state structure. */
typedef struct _hal_spi_slave
{
    hal_spi_slave_transfer_callback_t callback;
    void *callbackParam;
    lpspi_slave_handle_t hardwareHandle;
    uint8_t instance;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_slave_dma_handle_t *dmaHandle;
#endif
} hal_spi_slave_t;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
typedef struct _hal_spi_slave_dma_state
{
    uint8_t instance; /* spi instance */
    hal_spi_slave_transfer_callback_t callback;
    void *callbackParam;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    lpspi_slave_edma_handle_t edmaHandle;
    edma_handle_t txEdmaHandle;
    edma_handle_t rxEdmaHandle;
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    lpspi_slave_dma_handle_t dmaHandle;
    dma_handle_t txDmaHandle;
    dma_handle_t rxDmaHandle;
#endif

} hal_spi_slave_dma_state_t;
#endif

#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
typedef struct _hal_spi_master_dma_state
{
    uint8_t instance; /* spi instance */
    hal_spi_master_transfer_callback_t callback;
    void *callbackParam;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    lpspi_master_edma_handle_t edmaHandle;
    edma_handle_t txEdmaHandle;
    edma_handle_t rxEdmaHandle;

#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    lpspi_master_dma_handle_t dmaHandle;
    dma_handle_t txDmaHandle;
    dma_handle_t rxDmaHandle;
#endif

} hal_spi_master_dma_state_t;
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Base pointer array */
static LPSPI_Type *const s_spiBases[] = LPSPI_BASE_PTRS;

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
        case kStatus_LPSPI_Busy:
        {
            returnStatus = kStatus_HAL_SpiBusy;
            break;
        }
        case kStatus_LPSPI_Idle:
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
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
static void HAL_SpiMasterDMACallback(LPSPI_Type *base,
                                     lpspi_master_edma_handle_t *handle,
                                     status_t status,
                                     void *callbackParam)
{
    hal_spi_master_t *spiMasterHandle;

    assert(callbackParam);

    spiMasterHandle = (hal_spi_master_t *)callbackParam;

    if (NULL != spiMasterHandle->callback)
    {
        spiMasterHandle->callback(spiMasterHandle, HAL_SpiGetStatus(status), spiMasterHandle->callbackParam);
    }
}
#else

static void HAL_SpiMasterCallback(LPSPI_Type *base, lpspi_master_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_master_t *spiMasterHandle;

    assert(callbackParam);

    spiMasterHandle = (hal_spi_master_t *)callbackParam;

    if (NULL != spiMasterHandle->callback)
    {
        spiMasterHandle->callback(spiMasterHandle, HAL_SpiGetStatus(status), spiMasterHandle->callbackParam);
    }
}

#endif

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
static void HAL_SpiSlaveDMACallback(LPSPI_Type *base,
                                    lpspi_slave_edma_handle_t *handle,
                                    status_t status,
                                    void *callbackParam)
{
    hal_spi_master_t *spiSlaveHandle;

    assert(callbackParam);

    spiSlaveHandle = (hal_spi_master_t *)callbackParam;

    if (NULL != spiSlaveHandle->callback)
    {
        spiSlaveHandle->callback(spiSlaveHandle, HAL_SpiGetStatus(status), spiSlaveHandle->callbackParam);
    }
}
#else
static void HAL_SpiSlaveCallback(LPSPI_Type *base, lpspi_slave_handle_t *handle, status_t status, void *callbackParam)
{
    hal_spi_slave_t *spiSlaveHandle;

    assert(callbackParam);

    spiSlaveHandle = (hal_spi_slave_t *)callbackParam;

    if (NULL != spiSlaveHandle->callback)
    {
        spiSlaveHandle->callback(spiSlaveHandle, HAL_SpiGetStatus(status), spiSlaveHandle->callbackParam);
    }
}
#endif
hal_spi_status_t HAL_SpiMasterInit(hal_spi_master_handle_t handle, const hal_spi_master_config_t *config)
{
    hal_spi_master_t *masterHandle;
    lpspi_master_config_t lpspiConfig;
    assert(handle);
    assert(config);

    assert(HAL_SPI_MASTER_HANDLE_SIZE >= sizeof(hal_spi_master_t));

    masterHandle = (hal_spi_master_t *)handle;

    LPSPI_MasterGetDefaultConfig(&lpspiConfig);

    lpspiConfig.cpol = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kLPSPI_ClockPolarityActiveHigh :
                                                                               kLPSPI_ClockPolarityActiveLow;
    lpspiConfig.cpha =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kLPSPI_ClockPhaseFirstEdge : kLPSPI_ClockPhaseSecondEdge;
    lpspiConfig.direction = (kHAL_SpiMsbFirst == config->direction) ? kLPSPI_MsbFirst : kLPSPI_LsbFirst;
    lpspiConfig.baudRate  = config->baudRate_Bps;

    masterHandle->instance = config->instance;

    LPSPI_MasterInit((LPSPI_Type *)s_spiBases[masterHandle->instance], &lpspiConfig, config->srcClock_Hz);
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    masterHandle->dmaHandle = NULL;
#endif

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveInit(hal_spi_slave_handle_t handle, const hal_spi_slave_config_t *config)
{
    hal_spi_slave_t *slaveHandle;
    lpspi_slave_config_t lpspiConfig;
    assert(handle);
    assert(config);

    assert(HAL_SPI_SLAVE_HANDLE_SIZE >= sizeof(hal_spi_slave_t));

    slaveHandle = (hal_spi_slave_t *)handle;

    LPSPI_SlaveGetDefaultConfig(&lpspiConfig);

    lpspiConfig.cpol = (kHAL_SpiClockPolarityActiveHigh == config->polarity) ? kLPSPI_ClockPolarityActiveHigh :
                                                                               kLPSPI_ClockPolarityActiveLow;
    lpspiConfig.cpha =
        (kHAL_SpiClockPhaseFirstEdge == config->phase) ? kLPSPI_ClockPhaseFirstEdge : kLPSPI_ClockPhaseSecondEdge;

    slaveHandle->instance = config->instance;

    LPSPI_SlaveInit((LPSPI_Type *)s_spiBases[slaveHandle->instance], &lpspiConfig);
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    slaveHandle->dmaHandle = NULL;
#endif

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterDeinit(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;

    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
    LPSPI_Deinit((LPSPI_Type *)s_spiBases[masterHandle->instance]);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveDeinit(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;

    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;

    LPSPI_Deinit((LPSPI_Type *)s_spiBases[slaveHandle->instance]);

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterTransferInstallCallback(hal_spi_master_handle_t handle,
                                                      hal_spi_master_transfer_callback_t callback,
                                                      void *callbackParam)
{
    hal_spi_master_t *masterHandle;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_master_dma_state_t *spi_masterDmaHandle;
#endif
    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;

    masterHandle->callback      = callback;
    masterHandle->callbackParam = callbackParam;

#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    spi_masterDmaHandle                = (hal_spi_master_dma_state_t *)masterHandle->dmaHandle;
    spi_masterDmaHandle->callback      = callback;
    spi_masterDmaHandle->callbackParam = callbackParam;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))

    LPSPI_MasterTransferCreateHandleEDMA((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                         (lpspi_master_edma_handle_t *)&spi_masterDmaHandle->edmaHandle,
                                         HAL_SpiMasterDMACallback, callbackParam, &spi_masterDmaHandle->rxEdmaHandle,
                                         &spi_masterDmaHandle->txEdmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    LPSPI_MasterTransferCreateHandle((LPSPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle,
                                     HAL_SpiMasterCallback, masterHandle);
#endif

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiMasterTransferBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_master_t *masterHandle;
    lpspi_transfer_t transfer;

    assert(handle);
    assert(xfer);

    masterHandle = (hal_spi_master_t *)handle;

    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    (void)masterHandle;
    return kStatus_HAL_SpiError;
#else

    return HAL_SpiGetStatus(LPSPI_MasterTransferBlocking((LPSPI_Type *)s_spiBases[masterHandle->instance], &transfer));
#endif
}

hal_spi_status_t HAL_SpiMasterTransferNonBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer)

{
    hal_spi_master_t *masterHandle;
    lpspi_transfer_t transfer;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_master_dma_state_t *spi_masterDmaHandle;
#endif
    assert(handle);
    assert(xfer);

    masterHandle         = (hal_spi_master_t *)handle;
    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    spi_masterDmaHandle = (hal_spi_master_dma_state_t *)masterHandle->dmaHandle;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    return HAL_SpiGetStatus(LPSPI_MasterTransferEDMA((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                                     (lpspi_master_edma_handle_t *)&spi_masterDmaHandle->edmaHandle,
                                                     &transfer));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    return HAL_SpiGetStatus(LPSPI_MasterTransferNonBlocking((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                                            &masterHandle->hardwareHandle, &transfer));
#endif
}

hal_spi_status_t HAL_SpiMasterTransferGetCount(hal_spi_master_handle_t handle, size_t *spiCount)
{
    hal_spi_master_t *masterHandle;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_master_dma_state_t *spi_masterDmaHandle;
#endif

    assert(handle);
    assert(spiCount);

    masterHandle = (hal_spi_master_t *)handle;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    spi_masterDmaHandle = (hal_spi_master_dma_state_t *)masterHandle->dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    return HAL_SpiGetStatus(
        LPSPI_MasterTransferGetCountEDMA((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                         (lpspi_master_edma_handle_t *)&spi_masterDmaHandle->edmaHandle, spiCount));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    return HAL_SpiGetStatus(LPSPI_MasterTransferGetCount((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                                         &masterHandle->hardwareHandle, spiCount));
#endif
}

hal_spi_status_t HAL_SpiMasterTransferAbort(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *masterHandle;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    hal_spi_master_dma_state_t *spi_masterDmaHandle;
#endif

    assert(handle);

    masterHandle = (hal_spi_master_t *)handle;
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    spi_masterDmaHandle = (hal_spi_master_dma_state_t *)masterHandle->dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    LPSPI_MasterTransferAbortEDMA((LPSPI_Type *)s_spiBases[masterHandle->instance],
                                  (lpspi_master_edma_handle_t *)&spi_masterDmaHandle->edmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    LPSPI_MasterTransferAbort((LPSPI_Type *)s_spiBases[masterHandle->instance], &masterHandle->hardwareHandle);

#endif

    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveTransferInstallCallback(hal_spi_slave_handle_t handle,
                                                     hal_spi_slave_transfer_callback_t callback,
                                                     void *callbackParam)
{
    hal_spi_slave_t *slaveHandle;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;
#endif
    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;

    slaveHandle->callback      = callback;
    slaveHandle->callbackParam = callbackParam;

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    spi_slaveDmaHandle                = (hal_spi_slave_dma_state_t *)slaveHandle->dmaHandle;
    spi_slaveDmaHandle->callback      = callback;
    spi_slaveDmaHandle->callbackParam = callbackParam;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))

    LPSPI_SlaveTransferCreateHandleEDMA(
        (LPSPI_Type *)s_spiBases[slaveHandle->instance], (lpspi_slave_edma_handle_t *)&spi_slaveDmaHandle->edmaHandle,
        HAL_SpiSlaveDMACallback, callbackParam, &spi_slaveDmaHandle->rxEdmaHandle, &spi_slaveDmaHandle->txEdmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    LPSPI_SlaveTransferCreateHandle((LPSPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle,
                                    HAL_SpiSlaveCallback, slaveHandle);
#endif
    return kStatus_HAL_SpiSuccess;
}

hal_spi_status_t HAL_SpiSlaveTransferNonBlocking(hal_spi_slave_handle_t handle, hal_spi_transfer_t *xfer)
{
    hal_spi_slave_t *slaveHandle;
    lpspi_transfer_t transfer;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;
#endif

    assert(handle);
    assert(xfer);

    slaveHandle          = (hal_spi_slave_t *)handle;
    transfer.txData      = xfer->txData;
    transfer.rxData      = xfer->rxData;
    transfer.dataSize    = xfer->dataSize;
    transfer.configFlags = xfer->flags;

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    spi_slaveDmaHandle = (hal_spi_slave_dma_state_t *)slaveHandle->dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    return HAL_SpiGetStatus(LPSPI_SlaveTransferEDMA((LPSPI_Type *)s_spiBases[slaveHandle->instance],
                                                    (lpspi_slave_edma_handle_t *)&spi_slaveDmaHandle->edmaHandle,
                                                    &transfer));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    return HAL_SpiGetStatus(LPSPI_SlaveTransferNonBlocking((LPSPI_Type *)s_spiBases[slaveHandle->instance],
                                                           &slaveHandle->hardwareHandle, &transfer));
#endif
}

hal_spi_status_t HAL_SpiSlaveTransferGetCount(hal_spi_slave_handle_t handle, size_t *spiCount)
{
    hal_spi_slave_t *slaveHandle;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;
#endif

    assert(handle);
    assert(spiCount);

    slaveHandle = (hal_spi_slave_t *)handle;

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    spi_slaveDmaHandle = (hal_spi_slave_dma_state_t *)slaveHandle->dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    return HAL_SpiGetStatus(
        LPSPI_SlaveTransferGetCountEDMA((LPSPI_Type *)s_spiBases[slaveHandle->instance],
                                        (lpspi_slave_edma_handle_t *)&spi_slaveDmaHandle->edmaHandle, spiCount));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    return HAL_SpiGetStatus(LPSPI_SlaveTransferGetCount((LPSPI_Type *)s_spiBases[slaveHandle->instance],
                                                        &slaveHandle->hardwareHandle, spiCount));
#endif
}

hal_spi_status_t HAL_SpiSlaveTransferAbort(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *slaveHandle;
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;
#endif

    assert(handle);

    slaveHandle = (hal_spi_slave_t *)handle;

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    spi_slaveDmaHandle = (hal_spi_slave_dma_state_t *)slaveHandle->dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    LPSPI_SlaveTransferAbortEDMA((LPSPI_Type *)s_spiBases[slaveHandle->instance],
                                 (lpspi_slave_edma_handle_t *)&spi_slaveDmaHandle->edmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#else
    LPSPI_SlaveTransferAbort((LPSPI_Type *)s_spiBases[slaveHandle->instance], &slaveHandle->hardwareHandle);

#endif

    return kStatus_HAL_SpiSuccess;
}

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
hal_spi_status_t HAL_SpiSlaveDMAInit(hal_spi_slave_handle_t handle,
                                     hal_spi_slave_dma_handle_t dmaHandle,
                                     hal_spi_dma_config_t *dmaConfig)
{
    hal_spi_slave_t *spi_slaveHandle;
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;
#if (defined(HAL_SPI_SLAVE_DMA_INIT_ENABLE) && (HAL_SPI_SLAVE_DMA_INIT_ENABLE > 0U))
    edma_config_t config;
#endif

    assert(handle);
    assert(HAL_SPI_SLAVE_DMA_HANDLE_SIZE >= sizeof(hal_spi_slave_dma_state_t));

    spi_slaveHandle            = (hal_spi_slave_t *)handle;
    spi_slaveDmaHandle         = (hal_spi_slave_dma_state_t *)dmaHandle;
    spi_slaveHandle->dmaHandle = dmaHandle;

    /* DMA init process. */
    spi_slaveDmaHandle->instance = dmaConfig->spi_instance;
    spi_slaveHandle->dmaHandle   = dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    dma_mux_configure_t *dmaMux = dmaConfig->dma_mux_configure;
    /* Set channel for LPUART */
    DMAMUX_Type *dmaMuxBases[] = DMAMUX_BASE_PTRS;
#if (defined(HAL_SPI_SLAVE_DMA_INIT_ENABLE) && (HAL_SPI_SLAVE_DMA_INIT_ENABLE > 0U))
    DMAMUX_Init(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance]);
#endif

    DMAMUX_SetSource(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->tx_channel,
                     dmaMux->dma_dmamux_configure.tx_request);
    DMAMUX_SetSource(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->rx_channel,
                     dmaMux->dma_dmamux_configure.rx_request);
    DMAMUX_EnableChannel(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->tx_channel);
    DMAMUX_EnableChannel(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->rx_channel);
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
    /* Init the EDMA module */
    DMA_Type *dmaBases[]                                          = DMA_BASE_PTRS;
    IRQn_Type s_edmaIRQNumbers[][FSL_FEATURE_EDMA_MODULE_CHANNEL] = DMA_CHN_IRQS;
#if (defined(HAL_SPI_SLAVE_DMA_INIT_ENABLE) && (HAL_SPI_SLAVE_DMA_INIT_ENABLE > 0U))
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(dmaBases[dmaConfig->dma_instance], &config);
#endif

    EDMA_CreateHandle(&spi_slaveDmaHandle->txEdmaHandle, dmaBases[dmaConfig->dma_instance], dmaConfig->tx_channel);
    EDMA_CreateHandle(&spi_slaveDmaHandle->rxEdmaHandle, dmaBases[dmaConfig->dma_instance], dmaConfig->rx_channel);
#if (defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && (FSL_FEATURE_EDMA_HAS_CHANNEL_MUX > 0U))
    dma_channel_mux_configure_t *dmaChannelMux = dmaConfig->dma_channel_mux_configure;
    EDMA_SetChannelMux(dmaBases[dmaConfig->dma_instance], dmaConfig->tx_channel,
                       dmaChannelMux->dma_dmamux_configure.dma_tx_channel_mux);
    EDMA_SetChannelMux(dmaBases[dmaConfig->dma_instance], dmaConfig->rx_channel,
                       dmaChannelMux->dma_dmamux_configure.dma_rx_channel_mux);
#endif /* FSL_FEATURE_EDMA_HAS_CHANNEL_MUX */
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

    NVIC_SetPriority(s_edmaIRQNumbers[dmaConfig->dma_instance][dmaConfig->tx_channel], HAL_SPI_ISR_PRIORITY);
    NVIC_SetPriority(s_edmaIRQNumbers[dmaConfig->dma_instance][dmaConfig->rx_channel], HAL_SPI_ISR_PRIORITY);

    return kStatus_HAL_SpiSuccess;
}
hal_spi_status_t HAL_SpiSlaveDMADeinit(hal_spi_slave_handle_t handle)
{
    hal_spi_slave_t *spi_slaveHandle;
    hal_spi_slave_dma_state_t *spi_slaveDmaHandle;

    assert(handle);

    spi_slaveHandle            = (hal_spi_slave_t *)handle;
    spi_slaveDmaHandle         = (hal_spi_slave_dma_state_t *)spi_slaveHandle->dmaHandle;
    spi_slaveHandle->dmaHandle = NULL;

    assert(spi_slaveDmaHandle);

    /* Abort rx/tx */
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#elif (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    /* Here we should not abort before create transfer handle. */
    if (NULL != spi_slaveDmaHandle->edmaHandle.edmaRxRegToRxDataHandle)
    {
        LPSPI_SlaveTransferAbortEDMA(s_spiBases[spi_slaveHandle->instance],
                                     (lpspi_slave_edma_handle_t *)&spi_slaveDmaHandle->edmaHandle);
    }
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

    return kStatus_HAL_SpiSuccess;
}
#endif
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
hal_spi_status_t HAL_SpiMasterDMAInit(hal_spi_master_handle_t handle,
                                      hal_spi_master_dma_handle_t dmaHandle,
                                      hal_spi_dma_config_t *dmaConfig)
{
    hal_spi_master_t *spi_masterHandle;
    hal_spi_master_dma_state_t *spi_masterDmaHandle;
#if (defined(HAL_SPI_MASTER_DMA_INIT_ENABLE) && (HAL_SPI_MASTER_DMA_INIT_ENABLE > 0U))
    edma_config_t config;
#endif
    assert(handle);
    assert(HAL_SPI_MASTER_DMA_HANDLE_SIZE >= sizeof(hal_spi_master_dma_state_t));

    spi_masterHandle            = (hal_spi_master_t *)handle;
    spi_masterDmaHandle         = (hal_spi_master_dma_state_t *)dmaHandle;
    spi_masterHandle->dmaHandle = dmaHandle;

    /* DMA init process. */
    spi_masterDmaHandle->instance = dmaConfig->spi_instance;
    spi_masterHandle->dmaHandle   = dmaHandle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    dma_mux_configure_t *dmaMux = dmaConfig->dma_mux_configure;
    /* Set channel for LPUART */
    DMAMUX_Type *dmaMuxBases[] = DMAMUX_BASE_PTRS;
#if (defined(HAL_SPI_MASTER_DMA_INIT_ENABLE) && (HAL_SPI_MASTER_DMA_INIT_ENABLE > 0U))
    DMAMUX_Init(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance]);
#endif
    DMAMUX_SetSource(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->tx_channel,
                     dmaMux->dma_dmamux_configure.tx_request);
    DMAMUX_SetSource(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->rx_channel,
                     dmaMux->dma_dmamux_configure.rx_request);
    DMAMUX_EnableChannel(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->tx_channel);
    DMAMUX_EnableChannel(dmaMuxBases[dmaMux->dma_dmamux_configure.dma_mux_instance], dmaConfig->rx_channel);
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
    /* Init the EDMA module */
    DMA_Type *dmaBases[]                                          = DMA_BASE_PTRS;
    IRQn_Type s_edmaIRQNumbers[][FSL_FEATURE_EDMA_MODULE_CHANNEL] = DMA_CHN_IRQS;
#if (defined(HAL_SPI_MASTER_DMA_INIT_ENABLE) && (HAL_SPI_MASTER_DMA_INIT_ENABLE > 0U))
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(dmaBases[dmaConfig->dma_instance], &config);
#endif
    EDMA_CreateHandle(&spi_masterDmaHandle->txEdmaHandle, dmaBases[dmaConfig->dma_instance], dmaConfig->tx_channel);
    EDMA_CreateHandle(&spi_masterDmaHandle->rxEdmaHandle, dmaBases[dmaConfig->dma_instance], dmaConfig->rx_channel);
#if (defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && (FSL_FEATURE_EDMA_HAS_CHANNEL_MUX > 0U))
    dma_channel_mux_configure_t *dmaChannelMux = dmaConfig->dma_channel_mux_configure;
    EDMA_SetChannelMux(dmaBases[dmaConfig->dma_instance], dmaConfig->tx_channel,
                       dmaChannelMux->dma_dmamux_configure.dma_tx_channel_mux);
    EDMA_SetChannelMux(dmaBases[dmaConfig->dma_instance], dmaConfig->rx_channel,
                       dmaChannelMux->dma_dmamux_configure.dma_rx_channel_mux);
#endif /* FSL_FEATURE_EDMA_HAS_CHANNEL_MUX */
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))

#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

    NVIC_SetPriority(s_edmaIRQNumbers[dmaConfig->dma_instance][dmaConfig->tx_channel], HAL_SPI_ISR_PRIORITY);
    NVIC_SetPriority(s_edmaIRQNumbers[dmaConfig->dma_instance][dmaConfig->rx_channel], HAL_SPI_ISR_PRIORITY);

    return kStatus_HAL_SpiSuccess;
}
hal_spi_status_t HAL_SpiMasterDMADeinit(hal_spi_master_handle_t handle)
{
    hal_spi_master_t *spi_masterHandle;
    hal_spi_master_dma_state_t *spi_masterDmaHandle;

    assert(handle);

    spi_masterHandle            = (hal_spi_master_t *)handle;
    spi_masterDmaHandle         = (hal_spi_master_dma_state_t *)spi_masterHandle->dmaHandle;
    spi_masterHandle->dmaHandle = NULL;

    assert(spi_masterDmaHandle);

    /* Abort rx/tx */
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#elif (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U))
    /* Here we should not abort before create transfer handle. */
    if (NULL != spi_masterDmaHandle->edmaHandle.edmaRxRegToRxDataHandle)
    {
        LPSPI_MasterTransferAbortEDMA((LPSPI_Type *)s_spiBases[spi_masterHandle->instance],
                                      (lpspi_master_edma_handle_t *)&spi_masterDmaHandle->edmaHandle);
    }
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

    return kStatus_HAL_SpiSuccess;
}
#endif
