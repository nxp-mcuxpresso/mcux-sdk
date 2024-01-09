/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SMARTCARD_USIM_H_
#define _FSL_SMARTCARD_USIM_H_

#include "fsl_smartcard.h"

/*!
 * @addtogroup smartcard_usim_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SMARTCARD_Control(base, handle, control, param)   SMARTCARD_USIM_Control(base, handle, control, 0)
#define SMARTCARD_TransferNonBlocking(base, handle, xfer) SMARTCARD_USIM_TransferNonBlocking(base, handle, xfer)
#define SMARTCARD_Init(base, handle, sourceClockHz)       SMARTCARD_USIM_Init(base, handle, sourceClockHz)
#define SMARTCARD_Deinit(base)                            SMARTCARD_USIM_Deinit(base)
#define SMARTCARD_GetTransferRemainingBytes(base, handle) SMARTCARD_USIM_GetTransferRemainingBytes(base, handle)
#define SMARTCARD_AbortTransfer(base, handle)             SMARTCARD_USIM_AbortTransfer(base, handle)

/*! @brief EMV RX NACK interrupt generation threshold */
#define SMARTCARD_EMV_RX_NACK_THRESHOLD (4U)

/*! @brief EMV TX NACK interrupt generation threshold */
#define SMARTCARD_EMV_TX_NACK_THRESHOLD (4U)

/*! @brief Smart card T0 Character Wait Timer adjustment value */
#define SMARTCARD_T0_CWT_ADJUSTMENT (12U)

/*! @brief Smart card T1 Character Wait Timer adjustment value */
#define SMARTCARD_T1_CWT_ADJUSTMENT (11U)

/*! @brief Smart card T0 Block Wait Timer adjustment value */
#define SMARTCARD_T0_BWT_ADJUSTMENT (12U)

/*! @brief Smart card T1 Block Wait Timer adjustment value */
#define SMARTCARD_T1_BWT_ADJUSTMENT (11U)

/*! @brief Rx FIFO max receive trigger level */
#define SMARTCARD_MAX_RX_TRIGGER_LEVEL (12U)

/*! @brief USIM Rx FIFO receiver trigger level enumeration. */
typedef enum _usim_rx_fifo_trigger_level
{
    kUSIM_1ByteOrMore  = 0u, /*!< 1 byte or more in the RX-FIFO can trigger receiver data ready interrupt. */
    kUSIM_4ByteOrMore  = 1u, /*!< 4 byte or more in the RX-FIFO can trigger receiver data ready interrupt. */
    kUSIM_8ByteOrMore  = 2u, /*!< 8 byte or more in the RX-FIFO can trigger receiver data ready interrupt. */
    kUSIM_12ByteOrMore = 3u, /*!< 12 byte or more in the RX-FIFO can trigger receiver data ready interrupt. */
} usim_rx_fifo_trigger_level_t;

/*! @brief USIM Find max Rx FIFO receiver trigger level according to bytes numbers. */
#define USIM_FIND_RX_FIFO_TRIGGER_LEVEL(x)      \
    (uint32_t)(((x) < 4U) ? kUSIM_1ByteOrMore : \
                            (((x) < 8U) ? kUSIM_4ByteOrMore : (((x) < 12U) ? kUSIM_8ByteOrMore : kUSIM_12ByteOrMore)))
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Smart card USIM Driver
 * @{
 */

/*!
 * @brief Fills in the smartcard_card_params structure with default values according to the EMV 4.3 specification.
 *
 * @param cardParams The configuration structure of type @ref smartcard_interface_config_t.
 * Function fill in members:
 *        Fi = 372;
 *        Di = 1;
 *        currentD = 1;
 *        WI = 0x0A;
 *        GTN = 0x00;
 * with default values.
 */
void SMARTCARD_USIM_GetDefaultConfig(smartcard_card_params_t *cardParams);

/*!
 * @brief Initializes an USIM peripheral for the Smart card/ISO-7816 operation.
 *
 * This function un-gates the USIM clock, initializes the module to EMV default settings,
 * configures the IRQ, enables the module-level interrupt to the core and, initializes the driver context.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to the smart card driver context structure.
 * @param srcClock_Hz Smart card clock generation module source clock.
 *
 * @return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_USIM_Init(USIM_Type *base, smartcard_context_t *context, uint32_t srcClock_Hz);

/*!
 * @brief This function disables the USIM interrupts, disables the transmitter and receiver,
 * flushes the FIFOs, and gates USIM clock in SIM.
 *
 * @param base The USIM module base address.
 */
void SMARTCARD_USIM_Deinit(USIM_Type *base);

/*!
 * @brief Returns whether the previous USIM transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the context of the
 * current transfer: in progress (or busy) or complete (success). If the
 * transfer is still in progress, the user can obtain the number of words that have not been
 * transferred.
 *
 * @param base The USIM module base address.
 * @param context A pointer to a smart card driver context structure.
 *
 * @return The number of bytes not transferred.
 */
int32_t SMARTCARD_USIM_GetTransferRemainingBytes(USIM_Type *base, smartcard_context_t *context);

/*!
 * @brief Terminates an asynchronous USIM transfer early.
 *
 * During an async USIM transfer, the user can terminate the transfer early
 * if the transfer is still in progress.
 *
 * @param base The USIM peripheral address.
 * @param context A pointer to a smart card driver context structure.
 * @return kStatus_SMARTCARD_Success The transmit abort was successful.
 * @return kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
status_t SMARTCARD_USIM_AbortTransfer(USIM_Type *base, smartcard_context_t *context);

/*!
 * @brief Transfer data using interrupts.
 *
 * A non-blocking (also known as asynchronous) function means that the function returns
 * immediately after initiating the transfer function. The application has to get the
 * transfer status to see when the transfer is complete. In other words, after calling the non-blocking
 * (asynchronous) transfer function, the application must get the transfer status to check if the transmit
 * is completed or not.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 * @param xfer A pointer to the smart card transfer structure where the linked buffers and sizes are stored.
 *
 * @return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_USIM_TransferNonBlocking(USIM_Type *base, smartcard_context_t *context, smartcard_xfer_t *xfer);

/*!
 * @brief Controls the USIM module per different user request.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 * @param control Control type.
 * @param param Integer value of specific to control command.
 *
 * @return kStatus_SMARTCARD_Success in success.
 * @return kStatus_SMARTCARD_OtherError in case of error.
 */
status_t SMARTCARD_USIM_Control(USIM_Type *base,
                                smartcard_context_t *context,
                                smartcard_control_t control,
                                uint32_t param);

/*!
 * @brief Handles USIM module interrupts.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a smart card driver context structure.
 */
void SMARTCARD_USIM_IRQHandler(USIM_Type *base, smartcard_context_t *context);

/*!
 * @brief Handles initial TS character timer time-out event.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a Smart card driver context structure.
 */
void SMARTCARD_USIM_TSExpiryCallback(USIM_Type *base, smartcard_context_t *context);

#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && (FSL_FEATURE_SOC_CTIMER_COUNT)
/*!
 * @brief Initializes timer with input period, enable interrupt and start counter.
 *
 * @param time The time period.
 */
void SMARTCARD_USIM_TimerStart(uint32_t time);
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_SMARTCARD_USIM_H_*/
