/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ASRC_SDMA_H_
#define _FSL_ASRC_SDMA_H_

#include "fsl_asrc.h"
#include "fsl_sdma.h"

/*!
 * @addtogroup asrc_sdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_ASRC_SDMA_DRIVER_VERSION (MAKE_VERSION(2, 0, 3)) /*!< Version 2.0.3 */
/*@}*/
/*! @brief ASRC xfer queue size */
#ifndef ASRC_XFER_IN_QUEUE_SIZE
#define ASRC_XFER_IN_QUEUE_SIZE 4U
#endif
#ifndef ASRC_XFER_OUT_QUEUE_SIZE
#define ASRC_XFER_OUT_QUEUE_SIZE (ASRC_XFER_IN_QUEUE_SIZE * 2U)
#endif

/*! @brief ASRC sdma handle prototype */
typedef struct _asrc_sdma_handle asrc_sdma_handle_t;

/*! @brief ASRC SDMA transfer callback function for finish and error */
typedef void (*asrc_sdma_callback_t)(ASRC_Type *base, asrc_sdma_handle_t *handle, status_t status, void *userData);
/*! @brief ASRC trigger peripheral function pointer */
typedef void (*asrc_start_peripheral_t)(bool start);
/*! @brief destination peripheral configuration */
typedef struct _asrc_p2p_sdma_config
{
    uint32_t eventSource;  /*!< peripheral event source */
    uint8_t watermark;     /*!< peripheral watermark */
    uint8_t channel;       /*!< peripheral channel number */
    uint8_t fifoWidth;     /*!< peripheral fifo width */
    bool enableContinuous; /*!< true is the amount of samples to be transferred is unknown and script will keep on
                            transferring as long as both events are detected and script must be stopped by
                            application, false is The amount of samples to be transferred is equal to the count
                            field of mode word */
    asrc_start_peripheral_t startPeripheral; /*!< trigger peripheral start */
} asrc_p2p_sdma_config_t;

/*! @brief ASRC sdma in handle */
typedef struct _asrc_sdma_in_handle
{
    sdma_handle_t *sdmaHandle;     /*!< DMA handler for ASRC */
    uint32_t eventSource;          /*!< ASRC event source number */
    asrc_sdma_callback_t callback; /*!< Callback for users while transfer finish or error occurs */
    void *userData;                /*!< User callback parameter */
    sdma_buffer_descriptor_t bdPool[ASRC_XFER_IN_QUEUE_SIZE]; /*!< BD pool for SDMA transfer. */
    uint8_t asrcInWatermark;                                  /*!< The transfer data count in a DMA request */
    uint8_t bytesPerSample;                                   /*!< Bytes in a sample */
    uint32_t *asrcQueue[ASRC_XFER_IN_QUEUE_SIZE];             /*!< Transfer queue storing queued transfer. */
    size_t sdmaTransferSize[ASRC_XFER_IN_QUEUE_SIZE];         /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                               /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                             /*!< Index for driver to get the transfer data and size */
    const asrc_p2p_sdma_config_t *peripheralConfig;           /*!< peripheral configuration */
    uint32_t state;                                           /*!< Internal state for ASRC SDMA transfer */
} asrc_sdma_in_handle_t;

/*! @brief ASRC sdma out handle */
typedef struct _asrc_sdma_out_handle
{
    sdma_handle_t *sdmaHandle;     /*!< DMA handler for ASRC */
    void *userData;                /*!< User callback parameter */
    uint32_t state;                /*!< Internal state for ASRC SDMA transfer */
    uint8_t bytesPerSample;        /*!< Bytes in a sample */
    uint32_t eventSource;          /*!< ASRC event source number */
    asrc_sdma_callback_t callback; /*!< Callback for users while transfer finish or error occurs */
    uint8_t asrcOutWatermark;      /*!< The transfer data count in a DMA request */
    sdma_buffer_descriptor_t bdPool[ASRC_XFER_OUT_QUEUE_SIZE]; /*!< BD pool for SDMA transfer. */
    uint32_t *asrcQueue[ASRC_XFER_OUT_QUEUE_SIZE];             /*!< Transfer queue storing queued transfer. */
    size_t sdmaTransferSize[ASRC_XFER_OUT_QUEUE_SIZE];         /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                                /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                   /*!< Index for driver to get the transfer data and size */
    const asrc_p2p_sdma_config_t *peripheralConfig; /*!< peripheral configuration */
    uint32_t nonAlignSize;                          /*!< non align size */
    void *nonAlignAddr;                             /*!< non align address */

} asrc_sdma_out_handle_t;

/*! @brief ASRC DMA transfer handle, users should not touch the content of the handle. */
struct _asrc_sdma_handle
{
    asrc_sdma_in_handle_t inDMAHandle;   /*!< input dma handle */
    asrc_sdma_out_handle_t outDMAHandle; /*!< output dma handle */

    asrc_context_t context; /*!< ASRC context number */
    uint8_t dataChannels;   /*!< ASRC process data channel number */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @name ASRC SDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the ASRC input SDMA handle.
 *
 * This function initializes the ASRC input DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC context, call this API once to get the initialized handle.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC SDMA handle pointer.
 * @param base ASRC peripheral base address.
 * @param callback Pointer to user callback function.
 * @param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 * @param eventSource ASRC input sdma event source.
 * @param context ASRC context number.
 * @param periphConfig peripheral configurations, used for  case.
 * @param userData User parameter passed to the callback function.
 */
void ASRC_TransferInCreateHandleSDMA(ASRC_Type *base,
                                     asrc_sdma_handle_t *handle,
                                     asrc_sdma_callback_t callback,
                                     sdma_handle_t *dmaHandle,
                                     uint32_t eventSource,
                                     asrc_context_t context,
                                     const asrc_p2p_sdma_config_t *periphConfig,
                                     void *userData);

/*!
 * @brief Initializes the ASRC output  SDMA handle.
 *
 * This function initializes the ASRC out DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC context, call this API once to get the initialized handle.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC SDMA handle pointer.
 * @param callback ASRC outcallback.
 * @param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 * @param eventSource ASRC output event source.
 * @param context ASRC context number.
 * @param periphConfig peripheral configurations, used for  case.
 * @param userData User parameter passed to the callback function.
 */
void ASRC_TransferOutCreateHandleSDMA(ASRC_Type *base,
                                      asrc_sdma_handle_t *handle,
                                      asrc_sdma_callback_t callback,
                                      sdma_handle_t *dmaHandle,
                                      uint32_t eventSource,
                                      asrc_context_t context,
                                      const asrc_p2p_sdma_config_t *periphConfig,
                                      void *userData);

/*!
 * @brief Configures the ASRC context.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC SDMA handle pointer.
 * @param asrcConfig asrc context configurations.
 */
status_t ASRC_TransferSetContextConfigSDMA(ASRC_Type *base,
                                           asrc_sdma_handle_t *handle,
                                           asrc_context_config_t *asrcConfig);
/*!
 * @brief Performs a non-blocking ASRC transfer using DMA.
 *
 *
 * @param base ASRC base pointer.
 * @param handle ASRC SDMA handle pointer.
 * @param xfer ASRC xfer configurations pointer.
 * @retval kStatus_Success Start a ASRC SDMA send successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_TxBusy ASRC is busy sending data.
 */
status_t ASRC_TransferSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle, asrc_transfer_t *xfer);

/*!
 * @brief Aborts a ASRC in transfer using SDMA.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC SDMA handle pointer.
 */
void ASRC_TransferAbortInSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle);

/*!
 * brief Aborts a ASRC out transfer using SDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 */
void ASRC_TransferAbortOutSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /*_FSL_ASRC_SDMA_H_*/
