/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_SPI_ADAPTER_H__
#define __HAL_SPI_ADAPTER_H__

/*!
 * @addtogroup SPI_Adapter
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Enable or disable Slave SPI DMA adapter mode (1 - enable, 0 - disable) */
#ifndef HAL_SPI_SLAVE_DMA_ENABLE
#define HAL_SPI_SLAVE_DMA_ENABLE (0U)
#endif /* HAL_SPI_SLAVE_DMA_ENABLE */

/*! @brief Enable or disable master SPI DMA adapter mode (1 - enable, 0 - disable) */
#ifndef HAL_SPI_MASTER_DMA_ENABLE
#define HAL_SPI_MASTER_DMA_ENABLE (0U)
#endif /* HAL_SPI_SLAVE_DMA_ENABLE */

/*! @brief Enable or disable slave SPI DMA adapter int mode (1 - enable, 0 - disable) */
#ifndef HAL_SPI_SLAVE_DMA_INIT_ENABLE
#define HAL_SPI_SLAVE_DMA_INIT_ENABLE (0U)
#endif /* HAL_SPI_SLAVE_DMA_INIT_ENABLE */

/*! @brief Enable or disable master SPI DMA adapter int mode (1 - enable, 0 - disable) */
#ifndef HAL_SPI_MASTER_DMA_INIT_ENABLE
#define HAL_SPI_MASTER_DMA_INIT_ENABLE (0U)
#endif /* HAL_SPI_MASTER_DMA_INIT_ENABLE */

/*! @brief spi master handle size.*/
#define HAL_SPI_MASTER_HANDLE_SIZE (80U)

/*! @brief spi slave handle size.*/
#define HAL_SPI_SLAVE_HANDLE_SIZE (80U)

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
/*! @brief spi master handle size.*/
#define HAL_SPI_SLAVE_DMA_HANDLE_SIZE (192U)
/*!
 * @brief Defines the SPI slave handle
 *
 * This macro is used to define the SPI slave handle.
 * Then use "(hal_spi_slave_handle_t)name" to get the SPI slave handle.
 *
 * The macro should be global and could be optional. You could also define SPI slave handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_SPI_SLAVE_HANDLE_DEFINE(spiMasterHandle);
 * @endcode
 *
 * @param name The name string of the SPI slave handle.
 */
#define HAL_SPI_SLAVE_DMA_HANDLE_DEFINE(name) \
    uint32_t name[(HAL_SPI_SLAVE_DMA_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

typedef void *hal_spi_slave_dma_handle_t;

#endif

#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
/*! @brief spi master handle size.*/
#define HAL_SPI_MASTER_DMA_HANDLE_SIZE (224U)

/*!
 * @brief Defines the SPI master handle
 *
 * This macro is used to define the SPI master handle.
 * Then use "(hal_spi_master_handle_t)name" to get the SPI master handle.
 *
 * The macro should be global and could be optional. You could also define SPI master handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(spiMasterHandle);
 * @endcode
 *
 * @param name The name string of the SPI master handle.
 */
#define HAL_SPI_MASTER_DMA_HANDLE_DEFINE(name) \
    uint32_t name[(HAL_SPI_MASTER_DMA_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

typedef void *hal_spi_master_dma_handle_t;

#endif

/*! @brief Return status for the spi driver.*/
typedef enum _hal_spi_status
{
    kStatus_HAL_SpiSuccess = kStatus_Success,                      /*!< Successfully */
    kStatus_HAL_SpiError   = MAKE_STATUS(kStatusGroup_HAL_SPI, 1), /*!< spi error */
    kStatus_HAL_SpiBusy    = MAKE_STATUS(kStatusGroup_HAL_SPI, 2), /*!< spi bus is busy */
    kStatus_HAL_SpiIdle    = MAKE_STATUS(kStatusGroup_HAL_SPI, 3), /*!< spi is idle */
} hal_spi_status_t;

/*! @brief spi clock polarity configuration.*/
typedef enum _hal_spi_clock_polarity
{
    kHAL_SpiClockPolarityActiveHigh = 0x0U, /*!< Active-high spi clock (idles low). */
    kHAL_SpiClockPolarityActiveLow          /*!< Active-low spi clock (idles high). */
} hal_spi_clock_polarity_t;

/*! @brief spi clock phase configuration.*/
typedef enum _hal_spi_clock_phase
{
    kHAL_SpiClockPhaseFirstEdge = 0x0U, /*!< First edge on SPSCK occurs at the middle of the first
                                         *   cycle of a data transfer. */
    kHAL_SpiClockPhaseSecondEdge        /*!< First edge on SPSCK occurs at the start of the
                                         *   first cycle of a data transfer. */
} hal_spi_clock_phase_t;

/*! @brief spi data shifter direction options.*/
typedef enum _hal_spi_shift_direction
{
    kHAL_SpiMsbFirst = 0x0U, /*!< Data transfers start with most significant bit. */
    kHAL_SpiLsbFirst         /*!< Data transfers start with least significant bit. */
} hal_spi_shift_direction_t;

/*! @brief spi master user configure structure.*/
typedef struct _hal_spi_master_config
{
    uint32_t srcClock_Hz;                /*!< Clock source for spi in Hz */
    uint32_t baudRate_Bps;               /*!< Baud Rate for spi in Hz */
    hal_spi_clock_polarity_t polarity;   /*!< Clock polarity */
    hal_spi_clock_phase_t phase;         /*!< Clock phase */
    hal_spi_shift_direction_t direction; /*!< MSB or LSB */
    uint8_t instance;                    /*!< Instance of the spi */
    bool enableMaster;                   /*!< Enable spi at initialization time */
} hal_spi_master_config_t;

/*! @brief spi slave user configure structure.*/
typedef struct _hal_spi_slave_config
{
    hal_spi_clock_polarity_t polarity;   /*!< Clock polarity */
    hal_spi_clock_phase_t phase;         /*!< Clock phase */
    hal_spi_shift_direction_t direction; /*!< MSB or LSB */
    uint8_t instance;                    /*!< Instance of the spi */
    bool enableSlave;                    /*!< Enable spi at initialization time */
} hal_spi_slave_config_t;

/*! @brief spi transfer structure */
typedef struct _hal_spi_transfer
{
    uint8_t *txData; /*!< Send buffer */
    uint8_t *rxData; /*!< Receive buffer */
    size_t dataSize; /*!< Transfer bytes */
    uint32_t flags;  /*!< spi control flag.*/
} hal_spi_transfer_t;

/*! @brief spi master handle.*/
typedef void *hal_spi_master_handle_t;

/*! @brief spi slave handle.*/
typedef void *hal_spi_slave_handle_t;

/*!
 * @brief Defines the SPI master handle
 *
 * This macro is used to define the SPI master handle.
 * Then use "(hal_spi_master_handle_t)name" to get the SPI master handle.
 *
 * The macro should be global and could be optional. You could also define SPI master handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(spiMasterHandle);
 * @endcode
 *
 * @param name The name string of the SPI master handle.
 */
#define HAL_SPI_MASTER_HANDLE_DEFINE(name) \
    uint32_t name[(HAL_SPI_MASTER_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/*!
 * @brief Defines the SPI slave handle
 *
 * This macro is used to define the SPI slave handle.
 * Then use "(hal_spi_slave_handle_t)name" to get the SPI slave handle.
 *
 * The macro should be global and could be optional. You could also define SPI slave handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_SPI_SLAVE_HANDLE_DEFINE(spiSlaveHandle);
 * @endcode
 *
 * @param name The name string of the SPI slave handle.
 */
#define HAL_SPI_SLAVE_HANDLE_DEFINE(name) \
    uint32_t name[(HAL_SPI_SLAVE_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/*! @brief spi master callback for finished transmit */
typedef void (*hal_spi_master_transfer_callback_t)(hal_spi_master_handle_t handle,
                                                   hal_spi_status_t status,
                                                   void *callbackParam);

/*! @brief spi slave callback for finished transmit */
typedef void (*hal_spi_slave_transfer_callback_t)(hal_spi_slave_handle_t handle,
                                                  hal_spi_status_t status,
                                                  void *callbackParam);
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U)) || \
    (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
typedef struct _dma_mux_configure_t
{
    union
    {
        struct
        {
            uint8_t dma_mux_instance;
            uint32_t rx_request;
            uint32_t tx_request;
        } dma_dmamux_configure;
    };
} dma_mux_configure_t;
typedef struct _dma_channel_mux_configure_t
{
    union
    {
        struct
        {
            uint32_t dma_rx_channel_mux;
            uint32_t dma_tx_channel_mux;
        } dma_dmamux_configure;
    };
} dma_channel_mux_configure_t;

typedef struct _hal_spi_dma_config_t
{
    uint8_t spi_instance;
    uint8_t dma_instance;
    uint8_t rx_channel;
    uint8_t tx_channel;
    void *dma_mux_configure;
    void *dma_channel_mux_configure;
} hal_spi_dma_config_t;
#endif /* HAL_SPI_SLAVET_DMA_ENABLE */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @name Initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the spi with master configuration.
 *
 * This function configures the spi master with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space of size #HAL_SPI_MASTER_HANDLE_SIZE
 * allocated by the caller.
 *
 * Example below shows how to use this API to configure the SPI master.
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(masterHandle);
 *   hal_spi_master_config_t userConfig;
 *   userConfig.polarity      = kHAL_SpiClockPolarityActiveHigh;
 *   userConfig.phase         = kHAL_SpiClockPhaseFirstEdge;
 *   userConfig.direction     = kHAL_SpiMsbFirst;
 *   userConfig.baudRate_Bps  = 500000U;
 *   userConfig.enableMaster  = true;
 *   userConfig.srcClock_Hz   = 48000000;
 *   userConfig.instance      = 0;
 *   HAL_SpiMasterInit((hal_spi_master_handle_t)masterHandle, &userConfig);
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_SPI_MASTER_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_SPI_MASTER_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_SPI_MASTER_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config pointer to master configuration structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess spi master initialization succeed
 *
 */
hal_spi_status_t HAL_SpiMasterInit(hal_spi_master_handle_t handle, const hal_spi_master_config_t *config);

/*!
 * @brief Initializes the spi with slave configuration.
 *
 * This function configures the spi slave with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space of size #HAL_SPI_SLAVE_HANDLE_SIZE
 * allocated by the caller.
 * After calling this API, the slave is ready to transfer.
 *
 * Example below shows how to use this API to configure the SPI slave.
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(slaveHandle);
 *   hal_spi_slave_config_t userConfig;
 *   userConfig.polarity      = kHAL_SpiClockPolarityActiveHigh;
 *   userConfig.phase         = kHAL_SpiClockPhaseFirstEdge;
 *   userConfig.direction     = kHAL_SpiMsbFirst;
 *   userConfig.instance      = 0;
 *   userConfig.enableSlave   = true;
 *   HAL_SpiSlaveInit((hal_spi_slave_handle_t)slaveHandle, &userConfig);
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_SPI_SLAVE_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_SPI_MASTER_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_SPI_SLAVE_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config pointer to slave configuration structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess spi slave initialization succeed
 */
hal_spi_status_t HAL_SpiSlaveInit(hal_spi_slave_handle_t handle, const hal_spi_slave_config_t *config);

/*!
 * @brief De-initializes the spi master.
 *
 * De-initializes the spi master.
 * The spi master can't work unless calling the HAL_SpiMasterInit to initialize module.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @retval kStatus_HAL_SpiSuccess spi master de-initialization succeed
 */
hal_spi_status_t HAL_SpiMasterDeinit(hal_spi_master_handle_t handle);

/*!
 * @brief De-initializes the spi slave.
 *
 * De-initializes the spi slave.
 * The spi slave can't work unless calling the HAL_SpiSlaveInit to initialize module.
 *
 * @param handle spi slave handle pointer, this should be a static variable.
 * @retval kStatus_HAL_SpiSuccess spi slave de-initialization succeed
 */
hal_spi_status_t HAL_SpiSlaveDeinit(hal_spi_slave_handle_t handle);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for spi master module.
 * When any status of the spi master changed, the driver will notify the upper layer by the installed callback
 * function. And the status is also passed as status parameter when the callback is called.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @param callback Callback function.
 * @param callbackParam The parameter of the callback function.
 * @retval kStatus_HAL_SpiSuccess spi master handle created
 */
hal_spi_status_t HAL_SpiMasterTransferInstallCallback(hal_spi_master_handle_t handle,
                                                      hal_spi_master_transfer_callback_t callback,
                                                      void *callbackParam);

/*!
 * @brief Transfers a block of data using a polling method.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @param xfer pointer to hal_spi_transfer_t structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess Successfully sent all data.
 */
hal_spi_status_t HAL_SpiMasterTransferBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking spi interrupt transfer.
 *
 * @note If spi transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @param xfer pointer to hal_spi_transfer_t structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiBusy spi is not idle, is running another transfer.
 * @retval kStatus_HAL_SpiSuccess Successfully start the data transmission.
 */
hal_spi_status_t HAL_SpiMasterTransferNonBlocking(hal_spi_master_handle_t handle, hal_spi_transfer_t *xfer);

/*!
 * @brief Gets the bytes of the spi interrupt transferred.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @param spiCount Transferred bytes of spi master.
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess Succeed get the transfer count.
 */
hal_spi_status_t HAL_SpiMasterTransferGetCount(hal_spi_master_handle_t handle, size_t *spiCount);

/*!
 * @brief Aborts an spi transfer using interrupt.
 *
 * @param handle spi master handle pointer, this should be a static variable.
 * @retval kStatus_HAL_SpiSuccess Succeed abort the transfer.
 */
hal_spi_status_t HAL_SpiMasterTransferAbort(hal_spi_master_handle_t handle);

/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for spi slave module.
 * When any status of the spi slave changed, the driver will notify the upper layer by the installed callback
 * function. And the status is also passed as status parameter when the callback is called.
 *
 * @param handle spi slave handle pointer, this should be a static variable.
 * @param callback Callback function.
 * @param callbackParam The parameter of the callback function.
 * @retval kStatus_HAL_SpiSuccess spi slave handle created
 */
hal_spi_status_t HAL_SpiSlaveTransferInstallCallback(hal_spi_slave_handle_t handle,
                                                     hal_spi_slave_transfer_callback_t callback,
                                                     void *callbackParam);

/*!
 * @brief Performs a non-blocking spi slave interrupt transfer.
 *
 * @note If spi transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * @param handle spi slave handle pointer, this should be a static variable.
 * @param xfer pointer to hal_spi_xfer_config_t structure
 * @retval kStatus_HAL_SpiSuccess Successfully start a transfer.
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiBusy spi is not idle, is running another transfer.
 */
hal_spi_status_t HAL_SpiSlaveTransferNonBlocking(hal_spi_slave_handle_t handle, hal_spi_transfer_t *xfer);

/*!
 * @brief Gets the bytes of the spi interrupt transferred.
 *
 * @param handle spi slave handle pointer, this should be a static variable.
 * @param spiCount Transferred bytes of spi slave.
 * @retval kStatus_HAL_SpiSuccess Succeed get the transfer count.
 * @retval kStatus_HAL_SpiError An error occurred.
 */
hal_spi_status_t HAL_SpiSlaveTransferGetCount(hal_spi_slave_handle_t handle, size_t *spiCount);

/*!
 * @brief Aborts an spi slave transfer using interrupt.
 *
 * @param handle spi slave handle pointer, this should be a static variable.
 * @retval kStatus_HAL_SpiSuccess Succeed abort the transfer.
 */
hal_spi_status_t HAL_SpiSlaveTransferAbort(hal_spi_slave_handle_t handle);

#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
/*!
 * @brief Initializes the spi with slave configuration.
 *
 * This function configures the spi slave with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space of size #HAL_SPI_SLAVE_HANDLE_SIZE
 * allocated by the caller.
 * After calling this API, the slave is ready to transfer.
 *
 * Example below shows how to use this API to configure the SPI slave.
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(slaveHandle);
 *   hal_spi_slave_config_t userConfig;
 *   userConfig.polarity      = kHAL_SpiClockPolarityActiveHigh;
 *   userConfig.phase         = kHAL_SpiClockPhaseFirstEdge;
 *   userConfig.direction     = kHAL_SpiMsbFirst;
 *   userConfig.instance      = 0;
 *   userConfig.enableSlave   = true;
 *   HAL_SpiSlaveInit((hal_spi_slave_handle_t)slaveHandle, &userConfig);
 *   Configure spi_slave dma settings
 *   hal_spi_slave_dma_config_t dmaConfig;
 *   dmaConfig.spi_slave_instance = 0;
 *   dmaConfig.dma_instance  = 0;
 *   dmaConfig.rx_channel    = 0;
 *   dmaConfig.tx_channel    = 1;
 *   dma_mux_configure_t  dma_mux;
 *   dma_mux.dma_dmamux_configure.dma_mux_instance = 0;
 *   dma_mux.dma_dmamux_configure.rx_request =  kDmaRequestMuxLPSPI1Rx;
 *   dma_mux.dma_dmamux_configure.tx_request = kDmaRequestMuxLPSPI1Tx;
 *   dmaConfig.dma_mux_configure = &dma_mux;
 *
 *  Init spi_slave dma
 *  HAL_UartDMAInit((hal_spi_slave_handle_t *)g_spi_slaveHandle, (hal_spi_slave_dma_handle_t *)g_spi_slaveDmaHandle,
 * &dmaConfig);
 *  @endcode
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_SPI_SLAVE_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_SPI_SLAVE_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_SPI_SLAVE_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config pointer to spi slave configuration structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess spi slave initialization succeed
 */

hal_spi_status_t HAL_SpiSlaveDMAInit(hal_spi_slave_handle_t handle,
                                     hal_spi_slave_dma_handle_t dmaHandle,
                                     hal_spi_dma_config_t *dmaConfig);

/*!
 * @brief Deinitializes a SPI DMA instance.
 *
 * This function will abort spi slave dma receive/send transfer and deinitialize SPI.
 *
 * @param handle SPI handle pointer.
 * @retval kStatus_HAL_UartDmaSuccess SPI DMA de-initialization succeed
 */
hal_spi_status_t HAL_SpiSlaveDMADeinit(hal_spi_slave_handle_t handle);
#endif
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
/*!
 * @brief Initializes the spi with master configuration.
 *
 * This function configures the spi master with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space of size #HAL_SPI_MASTER_HANDLE_SIZE
 * allocated by the caller.
 * After calling this API, the master is ready to transfer.
 *
 * Example below shows how to use this API to configure the SPI master.
 * @code
 *   HAL_SPI_MASTER_HANDLE_DEFINE(masterHandle);
 *   hal_spi_master_config_t userConfig;
 *   userConfig.polarity      = kHAL_SpiClockPolarityActiveHigh;
 *   userConfig.phase         = kHAL_SpiClockPhaseFirstEdge;
 *   userConfig.direction     = kHAL_SpiMsbFirst;
 *   userConfig.instance      = 0;
 *   userConfig.enableMastere   = true;
 *   HAL_SpiMastereInit((hal_spi_master_handle_t)masterHandle, &userConfig);
 *   Configure spi_master dma settings
 *   hal_spi_master_dma_config_t dmaConfig;
 *   dmaConfig.spi_master_instance = 0;
 *   dmaConfig.dma_instance  = 0;
 *   dmaConfig.rx_channel    = 0;
 *   dmaConfig.tx_channel    = 1;
 *   dma_mux_configure_t  dma_mux;
 *   dma_mux.dma_dmamux_configure.dma_mux_instance = 0;
 *   dma_mux.dma_dmamux_configure.rx_request =  kDmaRequestMuxLPSPI1Rx;
 *   dma_mux.dma_dmamux_configure.tx_request = kDmaRequestMuxLPSPI1Tx;
 *   dmaConfig.dma_mux_configure = &dma_mux;
 *
 *  Init spi_master dma
 *  HAL_SpiMasterDMAInit((hal_spi_master_handle_t *)g_spi_masterHandle, (hal_spi_master_dma_handle_t
 * *)g_spi_masterDmaHandle, &dmaConfig);
 *  @endcode
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_SPI_MASTER_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_SPI_MASTER_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_SPI_MASTER_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config pointer to master configuration structure
 * @retval kStatus_HAL_SpiError An error occurred.
 * @retval kStatus_HAL_SpiSuccess spi master initialization succeed
 */

hal_spi_status_t HAL_SpiMasterDMAInit(hal_spi_master_handle_t handle,
                                      hal_spi_master_dma_handle_t dmaHandle,
                                      hal_spi_dma_config_t *dmaConfig);

/*!
 * @brief Deinitializes a SPI DMA instance.
 *
 * This function will abort spi_master dma receive/send transfer and deinitialize SPI.
 *
 * @param handle SPI handle pointer.
 * @retval kStatus_HAL_UartDmaSuccess SPI DMA de-initialization succeed
 */
hal_spi_status_t HAL_SpiMasterDMADeinit(hal_spi_master_handle_t handle);
#endif

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __HAL_SPI_ADAPTER_H__ */
