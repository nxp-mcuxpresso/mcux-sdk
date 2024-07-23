/*
 * Copyright  2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LIN_LPUART_H_
#define FSL_LIN_LPUART_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

#if defined(FSL_SDK_LIN_STACK_ENABLE) && (FSL_SDK_LIN_STACK_ENABLE)
#include "lin.h"
#else
#include "fsl_lin.h"
#endif

/*!
 * @addtogroup lin_lpuart_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _lin_lpuart_stop_bit_count
{
    kLPUART_OneStopBit = 0U, /*!< One stop bit */
    kLPUART_TwoStopBit = 1U, /*!< Two stop bits */
} lin_lpuart_stop_bit_count_t;

enum _lin_lpuart_flags
{
    kLPUART_TxDataRegEmptyFlag =
        (LPUART_STAT_TDRE_MASK), /*!< Transmit data register empty flag, sets when transmit buffer is empty */
    kLPUART_TransmissionCompleteFlag =
        (LPUART_STAT_TC_MASK), /*!< Transmission complete flag, sets when transmission activity complete */
    kLPUART_RxDataRegFullFlag =
        (LPUART_STAT_RDRF_MASK), /*!< Receive data register full flag, sets when the receive data buffer is full */
    kLPUART_IdleLineFlag  = (LPUART_STAT_IDLE_MASK), /*!< Idle line detect flag, sets when idle line detected */
    kLPUART_RxOverrunFlag = (LPUART_STAT_OR_MASK),   /*!< Receive Overrun, sets when new data is received before data is
                                                        read from receive register */
    kLPUART_NoiseErrorFlag = (LPUART_STAT_NF_MASK),  /*!< Receive takes 3 samples of each received bit.  If any of these
                                                        samples differ, noise flag sets */
    kLPUART_FramingErrorFlag =
        (LPUART_STAT_FE_MASK), /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kLPUART_ParityErrorFlag = (LPUART_STAT_PF_MASK), /*!< If parity enabled, sets upon parity error detection */
#if defined(FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT
    kLPUART_LinBreakFlag = (int)(LPUART_STAT_LBKDIF_MASK), /*!< LIN break detect interrupt flag, sets when LIN break
                                                         char detected and LIN circuit enabled */
#endif
    kLPUART_RxActiveEdgeFlag =
        (LPUART_STAT_RXEDGIF_MASK), /*!< Receive pin active edge interrupt flag, sets when active edge detected */
    kLPUART_RxActiveFlag =
        (LPUART_STAT_RAF_MASK), /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if defined(FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING) && FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
    kLPUART_DataMatch1Flag = LPUART_STAT_MA1F_MASK, /*!< The next character to be read from LPUART_DATA matches MA1*/
    kLPUART_DataMatch2Flag = LPUART_STAT_MA2F_MASK, /*!< The next character to be read from LPUART_DATA matches MA2*/
#endif
#if defined(FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS) && FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kLPUART_NoiseErrorInRxDataRegFlag =
        (LPUART_DATA_NOISY_MASK >> 10), /*!< NOISY bit, sets if noise detected in current data word */
    kLPUART_ParityErrorInRxDataRegFlag =
        (LPUART_DATA_PARITYE_MASK >> 10), /*!< PARITY bit, sets if noise detected in current data word */
#endif
#if defined(FSL_FEATURE_LPUART_HAS_FIFO) && FSL_FEATURE_LPUART_HAS_FIFO
    kLPUART_TxFifoEmptyFlag = (LPUART_FIFO_TXEMPT_MASK >> 16), /*!< TXEMPT bit, sets if transmit buffer is empty */
    kLPUART_RxFifoEmptyFlag = (LPUART_FIFO_RXEMPT_MASK >> 16), /*!< RXEMPT bit, sets if receive buffer is empty */
    kLPUART_TxFifoOverflowFlag =
        (LPUART_FIFO_TXOF_MASK >> 16), /*!< TXOF bit, sets if transmit buffer overflow occurred */
    kLPUART_RxFifoUnderflowFlag =
        (LPUART_FIFO_RXUF_MASK >> 16), /*!< RXUF bit, sets if receive buffer underflow occurred */
#endif
};

enum _lin_lpuart_interrupt_enable
{
#if defined(FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT
    kLPUART_LinBreakInterruptEnable = (LPUART_BAUD_LBKDIE_MASK >> 8), /*!< LIN break detect. */
#endif
    kLPUART_RxActiveEdgeInterruptEnable         = (LPUART_BAUD_RXEDGIE_MASK >> 8), /*!< Receive Active Edge. */
    kLPUART_TxDataRegEmptyInterruptEnable       = (LPUART_CTRL_TIE_MASK),          /*!< Transmit data register empty. */
    kLPUART_TransmissionCompleteInterruptEnable = (LPUART_CTRL_TCIE_MASK),         /*!< Transmission complete. */
    kLPUART_RxDataRegFullInterruptEnable        = (LPUART_CTRL_RIE_MASK),          /*!< Receiver data register full. */
    kLPUART_IdleLineInterruptEnable             = (LPUART_CTRL_ILIE_MASK),         /*!< Idle line. */
    kLPUART_RxOverrunInterruptEnable            = (LPUART_CTRL_ORIE_MASK),         /*!< Receiver Overrun. */
    kLPUART_NoiseErrorInterruptEnable           = (LPUART_CTRL_NEIE_MASK),         /*!< Noise error flag. */
    kLPUART_FramingErrorInterruptEnable         = (LPUART_CTRL_FEIE_MASK),         /*!< Framing error flag. */
    kLPUART_ParityErrorInterruptEnable          = (LPUART_CTRL_PEIE_MASK),         /*!< Parity error flag. */
#if defined(FSL_FEATURE_LPUART_HAS_FIFO) && FSL_FEATURE_LPUART_HAS_FIFO
    kLPUART_TxFifoOverflowInterruptEnable  = (LPUART_FIFO_TXOFE_MASK >> 8), /*!< Transmit FIFO Overflow. */
    kLPUART_RxFifoUnderflowInterruptEnable = (LPUART_FIFO_RXUFE_MASK >> 8), /*!< Receive FIFO Underflow. */
#endif
};

enum _lin_lpuart_status
{
    kStatus_LPUART_TxBusy                  = MAKE_STATUS(kStatusGroup_LPUART, 0), /*!< TX busy */
    kStatus_LPUART_RxBusy                  = MAKE_STATUS(kStatusGroup_LPUART, 1), /*!< RX busy */
    kStatus_LPUART_TxIdle                  = MAKE_STATUS(kStatusGroup_LPUART, 2), /*!< LPUART transmitter is idle. */
    kStatus_LPUART_RxIdle                  = MAKE_STATUS(kStatusGroup_LPUART, 3), /*!< LPUART receiver is idle. */
    kStatus_LPUART_TxWatermarkTooLarge     = MAKE_STATUS(kStatusGroup_LPUART, 4), /*!< TX FIFO watermark too large  */
    kStatus_LPUART_RxWatermarkTooLarge     = MAKE_STATUS(kStatusGroup_LPUART, 5), /*!< RX FIFO watermark too large  */
    kStatus_LPUART_FlagCannotClearManually = MAKE_STATUS(kStatusGroup_LPUART, 6), /*!< Some flag can't manually clear */
    kStatus_LPUART_Error                   = MAKE_STATUS(kStatusGroup_LPUART, 7), /*!< Error happens on LPUART. */
    kStatus_LPUART_RxRingBufferOverrun =
        MAKE_STATUS(kStatusGroup_LPUART, 8), /*!< LPUART RX software ring buffer overrun. */
    kStatus_LPUART_RxHardwareOverrun = MAKE_STATUS(kStatusGroup_LPUART, 9),  /*!< LPUART RX receiver overrun. */
    kStatus_LPUART_NoiseError        = MAKE_STATUS(kStatusGroup_LPUART, 10), /*!< LPUART noise error. */
    kStatus_LPUART_FramingError      = MAKE_STATUS(kStatusGroup_LPUART, 11), /*!< LPUART framing error. */
    kStatus_LPUART_ParityError       = MAKE_STATUS(kStatusGroup_LPUART, 12), /*!< LPUART parity error. */
};

typedef enum
{
    LPUART_8_BITS_PER_CHAR  = 0x0U, /*!< 8-bit data characters */
    LPUART_9_BITS_PER_CHAR  = 0x1U, /*!< 9-bit data characters */
    LPUART_10_BITS_PER_CHAR = 0x2U  /*!< 10-bit data characters */
} lin_lpuart_bit_count_per_char_t;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Accept Master baudrate deviation from the slave baudrate to be 2% */
#define AUTOBAUD_BAUDRATE_TOLERANCE (uint32_t)2U
#define BIT_RATE_TOLERANCE_UNSYNC   (uint32_t)14U
/* calculate range of one bit time with baudrate 19200 by formula {1000000/19200*(100 +
 * AUTOBAUD_BAUDRATE_TOLERANCE))/100} */
#define BIT_DURATION_MAX_19200 (uint32_t)(100000U * (100U + AUTOBAUD_BAUDRATE_TOLERANCE) / 192U)
#define BIT_DURATION_MIN_19200 (uint32_t)(100000U * (100U - AUTOBAUD_BAUDRATE_TOLERANCE) / 192U)
/* calculate range of one bit time with baudrate 14400 by formula {1000000/19200*(100 +
 * AUTOBAUD_BAUDRATE_TOLERANCE))/100} */
#define BIT_DURATION_MAX_14400 (uint32_t)(100000U * (100U + AUTOBAUD_BAUDRATE_TOLERANCE) / 144U)
#define BIT_DURATION_MIN_14400 (uint32_t)(100000U * (100U - AUTOBAUD_BAUDRATE_TOLERANCE) / 144U)
/* calculate range of one bit time with baudrate 9600 by formula {1000000/19200*(100 +
 * AUTOBAUD_BAUDRATE_TOLERANCE))/100} */
#define BIT_DURATION_MAX_9600 (uint32_t)(100000U * (100U + AUTOBAUD_BAUDRATE_TOLERANCE) / 96U)
#define BIT_DURATION_MIN_9600 (uint32_t)(100000U * (100U - AUTOBAUD_BAUDRATE_TOLERANCE) / 96U)
/* calculate range of one bit time with baudrate 4800 by formula {1000000/19200*(100 +
 * AUTOBAUD_BAUDRATE_TOLERANCE))/100} */
#define BIT_DURATION_MAX_4800 (uint32_t)(100000U * (100U + AUTOBAUD_BAUDRATE_TOLERANCE) / 48U)
#define BIT_DURATION_MIN_4800 (uint32_t)(100000U * (100U - AUTOBAUD_BAUDRATE_TOLERANCE) / 48U)
/* calculate range of one bit time with baudrate 2400 by formula {1000000/19200*(100 +
 * AUTOBAUD_BAUDRATE_TOLERANCE))/100} */
#define BIT_DURATION_MAX_2400 (uint32_t)(100000U * (100U + AUTOBAUD_BAUDRATE_TOLERANCE) / 24U)
#define BIT_DURATION_MIN_2400 (uint32_t)(100000U * (100U - AUTOBAUD_BAUDRATE_TOLERANCE) / 24U)

/* calculate range of two bit time with baudrate 19200 */
#define TWO_BIT_DURATION_MAX_19200 (2U * BIT_DURATION_MAX_19200)
#define TWO_BIT_DURATION_MIN_19200 (2U * BIT_DURATION_MIN_19200)
/* calculate range of two bit time with baudrate 14400 */
#define TWO_BIT_DURATION_MAX_14400 (2U * BIT_DURATION_MAX_14400)
#define TWO_BIT_DURATION_MIN_14400 (2U * BIT_DURATION_MIN_14400)
/* calculate range of two bit time with baudrate 9600 */
#define TWO_BIT_DURATION_MAX_9600 (2U * BIT_DURATION_MAX_9600)
#define TWO_BIT_DURATION_MIN_9600 (2U * BIT_DURATION_MIN_9600)
/* calculate range of two bit time with baudrate 4800 */
#define TWO_BIT_DURATION_MAX_4800 (2U * BIT_DURATION_MAX_4800)
#define TWO_BIT_DURATION_MIN_4800 (2U * BIT_DURATION_MIN_4800)
/* calculate range of two bit time with baudrate 2400 */
#define TWO_BIT_DURATION_MAX_2400 (2U * BIT_DURATION_MAX_2400)
#define TWO_BIT_DURATION_MIN_2400 (2U * BIT_DURATION_MIN_2400)

/* calculate range of 13 bit time minimum with baudrate 19200 for autobaud feature */
#define AUTOBAUD_BREAK_TIME_MIN (13U * BIT_DURATION_MIN_19200)
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

static inline bool LIN_LPUART_GetRxDataPolarity(const LPUART_Type *base)
{
    return (((base->STAT >> LPUART_STAT_RXINV_SHIFT) & 1U) > 0U);
}

static inline void LIN_LPUART_SetRxDataPolarity(LPUART_Type *base, bool polarity)
{
    base->STAT = (base->STAT & ~LPUART_STAT_RXINV_MASK) | ((polarity ? 1UL : 0UL) << LPUART_STAT_RXINV_SHIFT);
}

static inline void LIN_LPUART_WriteByte(LPUART_Type *base, uint8_t data)
{
    volatile uint8_t *dataRegBytes = (volatile uint8_t *)(&(base->DATA));
    dataRegBytes[0]                = data;
}

static inline void LIN_LPUART_ReadByte(const LPUART_Type *base, uint8_t *readData)
{
    *readData = (uint8_t)base->DATA;
}

/*!
 * @brief Calculates the best osr and sbr value for configured baudrate
 *
 * @param base LPUART peripheral base address
 * @param baudRate_Bps user configuration structure of type #lin_user_config_t
 * @param srcClock_Hz pointer to the LIN_LPUART driver state structure
 * @param osr pointer to osr value
 * @param sbr pointer to sbr value
 * @return An error code or lin_status_t
 */
status_t LIN_LPUART_CalculateBaudRate(
    LPUART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz, uint32_t *osr, uint16_t *sbr);

/*!
 * @brief Configure baudrate according to osr and sbr value
 *
 * @param base LPUART peripheral base address
 * @param osr pointer to osr value
 * @param sbr pointer to sbr value
 */
void LIN_LPUART_SetBaudRate(LPUART_Type *base, uint32_t *osr, uint16_t *sbr);

/*!
 * @brief Initializes an LIN_LPUART instance for LIN Network.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LIN_LPUART clock source in the application to initialize the LIN_LPUART.
 * This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, initialize the module to user defined settings and
 * default settings, set break field length to be 13 bit times minimum, enable
 * the break detect interrupt, Rx complete interrupt, frame error detect interrupt,
 * and enable the LPUART module transmitter and receiver
 *
 * @param base LPUART peripheral base address
 * @param linUserConfig user configuration structure of type #lin_user_config_t
 * @param linCurrentState pointer to the LIN_LPUART driver state structure
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_Init(LPUART_Type *base,
                             lin_user_config_t *linUserConfig,
                             lin_state_t *linCurrentState,
                             uint32_t linSourceClockFreq);

/*!
 * @brief Shuts down the LIN_LPUART by disabling interrupts and transmitter/receiver.
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_Deinit(LPUART_Type *base);

/*!
 * @brief Sends Frame data out through the LIN_LPUART module using blocking method.
 *  This function will calculate the checksum byte and send it with the frame data.
 *  Blocking means that the function does not return until the transmission is complete.
 *
 * @param base LPUART peripheral base address
 * @param txBuff  source buffer containing 8-bit data chars to send
 * @param txSize the number of bytes to send
 * @param timeoutMSec timeout value in milli seconds
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_SendFrameDataBlocking(LPUART_Type *base,
                                              const uint8_t *txBuff,
                                              uint8_t txSize,
                                              uint32_t timeoutMSec);

/*!
 * @brief Sends frame data out through the LIN_LPUART module using non-blocking method.
 *  This enables an a-sync method for transmitting data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the transmit status to know when the transmit is complete.
 *  This function will calculate the checksum byte and send it with the frame data.
 *
 * @param base LPUART peripheral base address
 * @param txBuff  source buffer containing 8-bit data chars to send
 * @param txSize  the number of bytes to send
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_SendFrameData(LPUART_Type *base, const uint8_t *txBuff, uint8_t txSize);

/*!
 * @brief Get status of an on-going non-blocking transmission
 *  While sending frame data using non-blocking method, users can
 *  use this function to get status of that transmission.
 *  This function return LIN_TX_BUSY while sending, or LIN_TIMEOUT
 *  if timeout has occurred, or return LIN_SUCCESS when the transmission is complete.
 *  The bytesRemaining shows number of bytes that still needed to transmit.
 *
 * @param base LPUART peripheral base address
 * @param bytesRemaining  Number of bytes still needed to transmit
 * @return lin_status_t LIN_TX_BUSY, LIN_SUCCESS or LIN_TIMEOUT
 */
lin_status_t LIN_LPUART_GetTransmitStatus(LPUART_Type *base, uint8_t *bytesRemaining);

/*!
 * @brief Receives frame data through the LIN_LPUART module using blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it
 *  will receive the frame data. Blocking means that the function does
 *  not return until the reception is complete.
 *
 * @param base LPUART peripheral base address
 * @param rxBuff  buffer containing 8-bit received data
 * @param rxSize the number of bytes to receive
 * @param timeoutMSec timeout value in milli seconds
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_RecvFrmDataBlocking(LPUART_Type *base, uint8_t *rxBuff, uint8_t rxSize, uint32_t timeoutMSec);

/*!
 * @brief Receives frame data through the LIN_LPUART module using non-blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it will receive it with the frame data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the receive status to know when the reception is complete.
 *
 * @param base LPUART peripheral base address
 * @param rxBuff  buffer containing 8-bit received data
 * @param rxSize the number of bytes to receive
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_RecvFrmData(LPUART_Type *base, uint8_t *rxBuff, uint8_t rxSize);

/*!
 * @brief Aborts an on-going non-blocking transmission/reception.
 *  While performing a non-blocking transferring data, users can call this function
 *  to terminate immediately the transferring.
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_AbortTransferData(LPUART_Type *base);

/*!
 * @brief Get status of an on-going non-blocking reception
 *  While receiving frame data using non-blocking method, users can
 *  use this function to get status of that receiving.
 *  This function return the current event ID, LIN_RX_BUSY while receiving
 *  and return LIN_SUCCESS, or timeout (LIN_TIMEOUT) when the reception is complete.
 *  The bytesRemaining shows number of bytes that still needed to receive.
 *
 * @param base LPUART peripheral base address
 * @param bytesRemaining  Number of bytes still needed to receive
 * @return lin_status_t LIN_RX_BUSY, LIN_TIMEOUT or LIN_SUCCESS
 */
lin_status_t LIN_LPUART_GetReceiveStatus(LPUART_Type *base, uint8_t *bytesRemaining);

/*!
 * @brief This function puts current node to sleep mode
 * This function changes current node state to LIN_NODE_STATE_SLEEP_MODE
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_GoToSleepMode(LPUART_Type *base);

/*!
 * @brief Puts current LIN node to Idle state
 * This function changes current node state to LIN_NODE_STATE_IDLE
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_GotoIdleState(LPUART_Type *base);

/*!
 * @brief Sends a wakeup signal through the LIN_LPUART interface
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_SendWakeupSignal(LPUART_Type *base);

/*!
 * @brief Sends frame header out through the LIN_LPUART module using a non-blocking method.
 *  This function sends LIN Break field, sync field then the ID with
 *  correct parity.
 *
 * @param base LPUART peripheral base address
 * @param id  Frame Identifier
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_MasterSendHeader(LPUART_Type *base, uint8_t id);

/*!
 * @brief Enables LIN_LPUART hardware interrupts.
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_EnableIRQ(LPUART_Type *base);

/*!
 * @brief Disables LIN_LPUART hardware interrupts.
 *
 * @param base LPUART peripheral base address
 * @return An error code or lin_status_t
 */
lin_status_t LIN_LPUART_DisableIRQ(LPUART_Type *base);

/*!
 * @brief This function capture bits time to detect break char, calculate
 * baudrate from sync bits and enable transceiver if autobaud successful.
 * This function should only be used in Slave.
 * The timer should be in mode input capture of both rising and falling edges.
 * The timer input capture pin should be externally connected to RXD pin.
 *
 * @param instance LPUART instance
 * @return lin_status_t
 */
lin_status_t LIN_LPUART_AutoBaudCapture(uint32_t instance);
/*!
 * @brief LIN_LPUART RX TX interrupt handler
 *
 * @param base LPUART peripheral base address
 * @return void
 */
void LIN_LPUART_IRQHandler(LPUART_Type *base);

#if defined(__cplusplus)
}
#endif

#endif /* FSL_LIN_LPUART_H_ */
