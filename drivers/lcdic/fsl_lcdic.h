/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_LCDIC_H_
#define _FSL_LCDIC_H_

#include "fsl_common.h"

/*!
 * @addtogroup lcdic
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_LCDIC_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))
/*@}*/

/*! @brief Delay used in LCDIC_ResetState
 *
 * This should be larger than 5 * core clock / LCDIC function clock.
 */
#ifndef LCDIC_RESET_STATE_DELAY
#define LCDIC_RESET_STATE_DELAY 130u
#endif

/*! @brief LCDIC mode. */
typedef enum _lcdic_mode
{
    kLCDIC_3WireSPI = 0U,                       /*!< 3-wire SPI mode. */
    kLCDIC_4WireSPI = LCDIC_CTRL_SPI_MD_MASK,   /*!< 4-wire SPI mode. */
    kLCDIC_I8080    = LCDIC_CTRL_LCDIC_MD_MASK, /*!< I8080 mode. */
} lcdic_mode_t;

/*! @brief LCDIC byte order data endian. */
typedef enum _lcdic_endian
{
    kLCDIC_BigEndian = 0U, /*!< Big endian. */
    kLCDIC_LittleEndian,   /*!< Little endian.*/
} lcdic_endian_t;

/*! @brief LCDIC RX FIFO threshold.
 *
 * RX threshold interrupt happens if the occupied word number in RX FIFO is
 * bigger than the threshold value.
 */
typedef enum _lcdic_rx_threshold
{
    kLCDIC_RxThreshold0Word = 0U, /*!< 0 word. */
    kLCDIC_RxThreshold1Word,      /*!< 1 word. */
} lcdic_rx_threshold_t;

/*! @brief LCDIC TX FIFO threshold.
 *
 * TX threshold interrupt happens if the empty word number in TX FIFO is
 * bigger than the threshold value.
 */
typedef enum _lcdic_tx_threshold
{
    kLCDIC_TxThreshold0Word = 0U, /*!< 0 word. */
    kLCDIC_TxThreshold1Word,      /*!< 1 word. */
    kLCDIC_TxThreshold2Word,      /*!< 2 word. */
    kLCDIC_TxThreshold3Word,      /*!< 3 word. */
    kLCDIC_TxThreshold4Word,      /*!< 4 word. */
    kLCDIC_TxThreshold5Word,      /*!< 5 word. */
    kLCDIC_TxThreshold6Word,      /*!< 6 word. */
    kLCDIC_TxThreshold7Word,      /*!< 7 word. */
} lcdic_tx_threshold_t;

/*! @brief LCDIC reset signal polarity.  */
typedef enum _lcdic_reset_polarity
{
    kLCDIC_ResetActiveLow = 0U, /*!< Active low. */
    kLCDIC_ResetActiveHigh,     /*!< Active high. */
} lcdic_reset_polarity_t;

/*! @brief LCDIC I8080 control flags.
 * @anchor _lcdic_i8080_ctrl_flags
 */
enum
{
    kLCDIC_I8080_CsActiveLow         = 0U,                            /*!< CS active low. */
    kLCDIC_I8080_CsActiveHigh        = LCDIC_I8080_CTRL0_CS_POL_MASK, /*!< CS active high. */
    kLCDIC_I8080_DcCmdLow            = 0U,                            /*!< DC 0 means command, while 1 means data. */
    kLCDIC_I8080_DcCmdHigh           = LCDIC_I8080_CTRL0_DC_POL_MASK, /*!< DC 1 means command, while 0 means data. */
    kLCDIC_I8080_RdActiveLow         = 0U,                            /*!< RD active low. */
    kLCDIC_I8080_RdActiveHigh        = LCDIC_I8080_CTRL0_RD_POL_MASK, /*!< RD active high. */
    kLCDIC_I8080_WrActiveLow         = 0U,                            /*!< WR active low. */
    kLCDIC_I8080_WrActiveHigh        = LCDIC_I8080_CTRL0_WR_POL_MASK, /*!< WR active high. */
    kLCDIC_I8080_CsEnableIdleOff     = LCDIC_I8080_CTRL0_EN_IDLE_OFF_MASK, /*!< CS off while no transmission. */
    kLCDIC_I8080_CsEnableDcSwitchOff = LCDIC_I8080_CTRL0_EN_DC_OFF_MASK,   /*!< CS off while DC switches. */
};

/*! @brief LCDIC SPI mode control flags.
 * @anchor _lcdic_spi_ctrl_flags
 */
enum
{
    kLCDIC_SPI_MsbFirst           = 0U,                              /*!< MSB(bit 7) sent and received first. */
    kLCDIC_SPI_LsbFirst           = LCDIC_SPI_CTRL_SDAT_ENDIAN_MASK, /*!< LSB(bit 0) sent and received first. */
    kLCDIC_SPI_ClkActiveHigh      = 0U,                              /*!< CPOL=0. Clock active-high (idle low) */
    kLCDIC_SPI_ClkActiveLow       = LCDIC_SPI_CTRL_CPOL_MASK,        /*!< CPOL=1. Clock active-low (idle high) */
    kLCDIC_SPI_ClkPhaseFirstEdge  = 0U,                              /*!< CPHA=0. Data sample at first clock edge. */
    kLCDIC_SPI_ClkPhaseSecondEdge = LCDIC_SPI_CTRL_CPHA_MASK,        /*!< CPHA=1. Data sample at second clock edge. */
    kLCDIC_SPI_DcCmdLow           = 0U,                              /*!< DC 0 means command, while 1 means data. */
    kLCDIC_SPI_DcCmdHigh          = LCDIC_SPI_CTRL_DC_POL_MASK,      /*!< DC 1 means command, while 0 means data. */
};

/*! @brief LCDIC configuration. */
typedef struct _lcdic_config
{
    lcdic_mode_t mode;                /*!< LCDIC work mode. */
    lcdic_endian_t endian;            /*!< Data endian. */
    lcdic_rx_threshold_t rxThreshold; /*!< RX FIFO threshold. */
    lcdic_tx_threshold_t txThreshold; /*!< TX FIFO threshold. */

    uint8_t timerRatio0; /*!< Valid range: 0~15. freq(timer0) = freq(lcdic_clk) / (2 ^ timerRatio0). */
    uint8_t timerRatio1; /*!< Valid range: 0~15. freq(timer1) = freq(timer0) / (2 ^ timerRatio1). */

    /* Reset signal. */
    uint8_t resetPulseWidth_Timer0;       /*!< Reset pulse width, in the unit of timer0 period. Valid range 1 ~ 64. */
    uint8_t resetSequence;                /*!< Reset sequence, it is a 8-bit value sent to reset pin from LSB. */
    uint8_t resetSequencePulseNum;        /*!< Reset sequence pulse number, valid range is 1 ~ 8. */
    lcdic_reset_polarity_t resetPolarity; /*!< Reset signal polarity. */

    /* I8080 */
    uint8_t i8080CtrlFlags; /*!< I8080 control flags, it is OR'ed value of @ref _lcdic_i8080_ctrl_flags. */
    uint8_t csWaitTime;     /*!< Minimum CS inactive pulse width. T(csw)=T(lcdic_clk)*csWaitTime, valid range 0-7. */
    uint8_t csSetupTime; /*!< Minimum CS setup time before WR/RD. T(css)=T(lcdic_clk)*csSetupTime, valid range 0-255. */
    uint8_t csHoldTime;  /*!< Minimum CS hold time after WR/RD. T(csh)=T(lcdic_clk)*csHoldTime, valid range 0-7. */
    uint8_t
        dcSetupTime;    /*!< Minimum DC setup time before WR/RD/CS. T(dcs)=T(lcdic_clk)*dsSetupTime, valid range 0-7. */
    uint8_t dcHoldTime; /*!< Minimum DC hold time after WR/RD/CS. T(dch)=T(lcdic_clk)*dsHoldTime, valid range 0-7. */
    uint8_t writeDataSetupTime;       /*!< Minimum write data setup time after WR active.
                                         T(wdh)=T(lcdic_clk)*writeDataSetupTime, valid range 0-7. */
    uint8_t writeDataHoldTime;        /*!< Minimum write data setup time before WR active.
                                         T(wds)=T(lcdic_clk)*writeDataHoldTime, valid range 0-7. */
    uint8_t writeEnableActiveWidth;   /*!< Minmum write enable active pulse width.
                                         T(waw)=T(lcdic_clk)*writeEnableActiveWidth, valid range 0-63. */
    uint8_t writeEnableInactiveWidth; /*!< Minmum write enable inactive pulse width.
                                         T(wiw)=T(lcdic_clk)*writeEnableInactiveWidth, valid range 0-63. */
    uint8_t readEnableActiveWidth;    /*!< Minmum read enable active pulse width.
                                         T(raw)=T(lcdic_clk)*readEnableActiveWidth, valid range 0-255. */
    uint8_t readEnableInactiveWidth;  /*!< Minmum read enable inactive pulse width.
                                         T(riw)=T(lcdic_clk)*readEnableInactiveWidth, valid range 0-255. */

    /* SPI */
    uint8_t spiCtrlFlags; /*!< SPI control flags, it is OR'ed value of @ref _lcdic_spi_ctrl_flags. */

    /* TE. */
    uint8_t teTimeoutTime_Timer1;  /*!< Tearing effect timeout time. T(te_to)=T(timer1)*teTimeoutTime_Timer1. */
    uint8_t teSyncWaitTime_Timer1; /*!< Tearing effect signal synchronization wait time.
                                      T(tew)=T(timer1)*teSyncWaitTime_Timer1. */

    /* Command. */
    uint8_t cmdShortTimeout_Timer0; /*!< Command short timeout. T(cmd_short_to)=T(timer0)*cmdShortTimeout_Timer0. */
    uint8_t cmdLongTimeout_Timer1;  /*!< Command long timeout. T(cmd_long_to)=T(timer1)*cmdLongTimeout_Timer1. */
} lcdic_config_t;

/*! @brief LCDIC interrupts. */
enum _lcdic_interrupt
{
    kLCDIC_ResetDoneInterrupt   = LCDIC_ISR_RST_DONE_INTR_MASK,        /*< Reset done interrupt. */
    kLCDIC_CmdDoneInterrupt     = LCDIC_ISR_CMD_DONE_INTR_MASK,        /*< TRX command done interrupt. */
    kLCDIC_CmdTimeoutInterrupt  = LCDIC_ISR_CMD_TO_INTR_MASK,          /*< TRX command timeout interrupt. */
    kLCDIC_TeTimeoutInterrupt   = LCDIC_ISR_TE_TO_INTR_MASK,           /*< TE timeout interrupt. */
    kLCDIC_TxOverflowInterrupt  = LCDIC_ISR_TFIFO_OVERFLOW_INTR_MASK,  /*< TX FIFO overflow interrupt. */
    kLCDIC_TxThresholdInterrupt = LCDIC_ISR_TFIFO_THRES_INTR_MASK,     /*< TX FIFO threshold interrupt. */
    kLCDIC_RxUnderflowInterrupt = LCDIC_ISR_RFIFO_UNDERFLOW_INTR_MASK, /*< RX FIFO underflow interrupt. */
    kLCDIC_RxThresholdInterrupt = LCDIC_ISR_RFIFO_THRES_INTR_MASK,     /*< RX FIFO threshold interrupt. */
    kLCDIC_AllInterrupt         = kLCDIC_ResetDoneInterrupt | kLCDIC_CmdDoneInterrupt | kLCDIC_CmdTimeoutInterrupt |
                          kLCDIC_TeTimeoutInterrupt | kLCDIC_TxOverflowInterrupt | kLCDIC_TxThresholdInterrupt |
                          kLCDIC_RxUnderflowInterrupt | kLCDIC_RxThresholdInterrupt, /*!< All interrupts. */
};

/*! @brief LCDIC status flags.
 * @anchor _lcdic_flags
 */
enum
{
    kLCDIC_IdleFlag        = LCDIC_STATUS0_LCDIC_IDLE_MASK,  /*< LCDIC is idle. */
    kLCDIC_TxThresholdFlag = LCDIC_STATUS0_TFIFO_THRES_MASK, /*< TX FIFO threshold reach. */
    kLCDIC_TxFullFlag      = LCDIC_STATUS0_TFIFO_FULL_MASK,  /*< TX FIFO full. */
    kLCDIC_RxThresholdFlag = LCDIC_STATUS0_RFIFO_THRES_MASK, /*< RX FIFO threshold reach. */
    kLCDIC_RxEmptyFlag     = LCDIC_STATUS0_RFIFO_EMPTY_MASK, /*< RX FIFO empty. */
    kLCDIC_AllFlag         = kLCDIC_IdleFlag | kLCDIC_TxThresholdFlag | kLCDIC_TxFullFlag | kLCDIC_RxThresholdFlag |
                     kLCDIC_RxEmptyFlag, /*!< All flags. */
};

/*! @brief LCDIC TE sync mode
 * @anchor _lcdic_te_sync_mode
 */
enum
{
    kLCDIC_TeNoSync = 0,      /*!< Don't need to sync. */
    kLCDIC_TeRisingEdgeSync,  /*!< Sync to TE rising edge. */
    kLCDIC_TeFallingEdgeSync, /*!< Sync to TE falling edge. */
};

/*! @brief LCDIC TRX command timeout mode
 * @anchor _lcdic_trx_timeout_mode
 */
enum
{
    kLCDIC_ShortTimeout = 0, /*!< Using short timeout. */
    kLCDIC_LongTimeout,      /*!< Using long timeout. */
};

/*! @brief LCDIC data format
 * @anchor _lcdic_data_format
 */
enum
{
    kLCDIC_DataFormatByte = 0, /*!< Byte. */
    kLCDIC_DataFormatHalfWord, /*!< Half word (2-byte). */
    kLCDIC_DataFormatWord,     /*!< Word (4-byte). */
};

/*! @brief LCDIC data or command
 * @anchor _lcdic_dc
 */
enum
{
    kLCDIC_Command = 0, /*!< Command. */
    kLCDIC_Data,        /*!< Data. */
};

/*! @brief LCDIC TX or RX
 * @anchor _lcdic_trx
 */
enum
{
    kLCDIC_RX = 0, /*!< RX */
    kLCDIC_TX,     /*!< TX. */
};

/*! @brief LCDIC TRX command */
typedef union _lcdic_trx_cmd
{
    struct
    {
        uint32_t dataLen : 18;   /*!< Data length in bytes, transfered byte is dataLen + 1. */
        uint32_t dummyCount : 3; /*!< Dummy cycle count between TX and RX  (for SPI only). */
        uint32_t : 2;
        uint32_t useAutoRepeat : 1;    /*!< Use auto repeat mode or not. */
        uint32_t teSyncMode : 2;       /*!< TE sync mode, see @ref _lcdic_te_sync_mode. */
        uint32_t trxTimeoutMode : 1;   /*!< TRX command timeout mode, see @ref _lcdic_trx_timeout_mode. */
        uint32_t dataFormat : 2;       /*!< Data format, see @ref _lcdic_data_format. */
        uint32_t enableCmdDoneInt : 1; /*!< Enable command done interrupt or not. */
        uint32_t cmdOrData : 1;        /*!< Command or data, see @ref _lcdic_dc. */
        uint32_t trx : 1;              /*!< TX or TX, see @ref _lcdic_trx. */
    } bits;
    uint32_t u32;
} lcdic_trx_cmd_t;

/*! @brief LCDIC repeat data TX transfer structure. */
typedef struct _lcdic_repeat_tx_xfer
{
    uint8_t cmd;            /*!< Command. */
    uint8_t teSyncMode;     /*!< TE sync mode, see @ref _lcdic_te_sync_mode. */
    uint8_t trxTimeoutMode; /*!< TRX command timeout mode, see @ref _lcdic_trx_timeout_mode. */
    uint8_t dataFormat;     /*!< Data format, see @ref _lcdic_data_format. */
    uint32_t dataLen;       /*!< Data length. */
    uint32_t txRepeatData;  /*!< The repeat data. */
} lcdic_repeat_tx_xfer_t;

/*! @brief LCDIC data array TX transfer structure. */
typedef struct _lcdic_tx_xfer
{
    uint8_t cmd;            /*!< Command. */
    uint8_t teSyncMode;     /*!< TE sync mode, see @ref _lcdic_te_sync_mode. */
    uint8_t trxTimeoutMode; /*!< TRX command timeout mode, see @ref _lcdic_trx_timeout_mode. */
    uint8_t dataFormat;     /*!< Data format, see @ref _lcdic_data_format. */
    uint32_t dataLen;       /*!< Data length. */
    const uint8_t *txData;  /*!< The data to send. */
} lcdic_tx_xfer_t;

/*! @brief LCDIC data array RX transfer structure. */
typedef struct _lcdic_rx_xfer
{
    uint8_t cmd;            /*!< Command. */
    uint8_t dummyCount;     /*!< Dummy cycle between TX and RX, only used for SPI mode. */
    uint8_t trxTimeoutMode; /*!< TRX command timeout mode, see @ref _lcdic_trx_timeout_mode. */
    uint8_t dataFormat;     /*!< Data format, see @ref _lcdic_data_format. */
    uint32_t dataLen;       /*!< Data length. */
    uint8_t *rxData;        /*!< Pointer to the data receive array. */
} lcdic_rx_xfer_t;

/*! @brief LCDIC transfer mode. */
typedef enum
{
    kLCDIC_XferCmdOnly = 0,      /*!< Only send command. */
    kLCDIC_XferSendRepeatData,   /*!< Send repeat data. */
    kLCDIC_XferSendDataArray,    /*!< Send data array. */
    kLCDIC_XferReceiveDataArray, /*!< Receive data array. */
} lcdic_xfer_mode_t;

/*! @brief LCDIC transfer structure. */
typedef struct _lcdic_xfer
{
    lcdic_xfer_mode_t mode; /*!< Transfer mode. */

    union
    {
        uint8_t cmdToSendOnly;               /*!< Command to send in mode @ref kLCDIC_XferCmdOnly. */
        lcdic_repeat_tx_xfer_t repeatTxXfer; /*!< For mode @ref kLCDIC_XferSendRepeatData. */
        lcdic_tx_xfer_t txXfer;              /*!< For mode @ref kLCDIC_XferSendDataArray. */
        lcdic_rx_xfer_t rxXfer;              /*!< For mode @ref kLCDIC_XferReceiveDataArray. */
    };
} lcdic_xfer_t;

/* Forward declaration of the handle typedef. */
typedef struct _lcdic_handle lcdic_handle_t;

/*!
 * @brief LCDIC transfer callback function.
 *
 * The status is @ref kStatus_Success when transfer finished successfully, it is
 * @ref kStatus_Timeout when timeout happened.
 */
typedef void (*lcdic_transfer_callback_t)(LCDIC_Type *base, lcdic_handle_t *handle, status_t status, void *userData);

/*! @brief LCDIC handle structure. */
struct _lcdic_handle
{
    volatile bool xferInProgress;       /*!< Transfer in progress. */
    lcdic_xfer_mode_t xferMode;         /*!< On-going transfer mode. */
    lcdic_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                     /*!< LCDIC callback function parameter.*/
    union
    {
        const uint8_t *txData; /*!< Data array to send. */
        uint8_t *rxData;       /*!< RX data array. */
    };
    uint32_t xferSizeWordAligned;  /*!< 4-byte aligned part of the transfer size. */
    uint8_t xferSizeWordUnaligned; /*!< 4-byte unaligned part of the transfer size. */
    uint32_t tmpData;              /*!< Temp data for driver internal use. */
};

/*! @brief Typedef for transactional APIs IRQ handler. */
typedef void (*lcdic_transfer_irq_handler_t)(LCDIC_Type *base, void *handle);

/*! @brief Typedef for reset sequence sent done callback. */
typedef void (*lcdic_reset_done_callback_t)(LCDIC_Type *base);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initialize the LCDIC.
 *
 * This function initializes the LCDIC to work, it configues the LCDIC
 * according to the configue structure and enables the module. After
 * calling this function, the peripheral is ready to work.
 *
 * @param base LCDIC peripheral base address.
 * @retval kStatus_Success Initialize successfully.
 */
status_t LCDIC_Init(LCDIC_Type *base, const lcdic_config_t *config);

/*!
 * @brief De-initialize the LCDIC.
 *
 * This function disables the LCDIC, and disables peripheral clock if necessary.
 *
 * @param base LCDIC peripheral base address.
 */
void LCDIC_Deinit(LCDIC_Type *base);

/*!
 * @brief Get the default configuration for to initialize the LCDIC.
 *
 * The default configuration value is:
 *
 * @code
    config->mode        = kLCDIC_3WireSPI;
    config->endian      = kLCDIC_BigEndian;
    config->rxThreshold = kLCDIC_RxThreshold0Word;
    config->txThreshold = kLCDIC_TxThreshold3Word;

    config->timerRatio0 = 8;
    config->timerRatio1 = 9;

    config->resetPulseWidth_Timer0 = 20;
    config->resetSequence          = 0;
    config->resetSequencePulseNum  = 1;
    config->resetPolarity          = kLCDIC_ResetActiveLow;

    config->i8080CtrlFlags = kLCDIC_I8080_CsActiveLow | kLCDIC_I8080_DcCmdLow | kLCDIC_I8080_RdActiveLow |
                             kLCDIC_I8080_WrActiveLow | kLCDIC_I8080_CsEnableIdleOff;

    config->csWaitTime               = 2;
    config->csSetupTime              = 2;
    config->csHoldTime               = 2;
    config->dcSetupTime              = 2;
    config->dcHoldTime               = 2;
    config->writeDataSetupTime       = 2;
    config->writeDataHoldTime        = 2;
    config->writeEnableActiveWidth   = 6;
    config->writeEnableInactiveWidth = 6;
    config->readEnableActiveWidth    = 15;
    config->readEnableInactiveWidth  = 15;

    config->spiCtrlFlags =
        kLCDIC_SPI_MsbFirst | kLCDIC_SPI_ClkActiveHigh | kLCDIC_SPI_ClkPhaseFirstEdge | kLCDIC_SPI_DcCmdLow;

    config->teTimeoutTime_Timer1  = 16;
    config->teSyncWaitTime_Timer1 = 0;

    config->cmdShortTimeout_Timer0 = 1;
    config->cmdLongTimeout_Timer1  = 16;

   @endcode
 *
 * @param config Pointer to the LCDIC configuration.
 */
void LCDIC_GetDefaultConfig(lcdic_config_t *config);

/*!
 * @brief Reset the LCDIC.
 *
 * This function resets the LCDIC state. After calling this function,
 * all data in TX_FIFO and RX_FIFO will be cleared and all transactions
 * on LCD interface will restart despite of formal status.
 *
 * The configurations will not be reset.
 *
 * @param base LCDIC peripheral base address.
 */
void LCDIC_ResetState(LCDIC_Type *base);

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables LCDIC interrupts.
 *
 * @param base LCDIC peripheral base address.
 * @param interrupts The interrupts to enable, pass in as OR'ed value of @ref _lcdic_interrupt.
 */
static inline void LCDIC_EnableInterrupts(LCDIC_Type *base, uint32_t interrupts)
{
    base->IMR &= ~interrupts;
}

/*!
 * @brief Disable LCDIC interrupts.
 *
 * @param base LCDIC peripheral base address.
 * @param interrupts The interrupts to disable, pass in as OR'ed value of @ref _lcdic_interrupt.
 */
static inline void LCDIC_DisableInterrupts(LCDIC_Type *base, uint32_t interrupts)
{
    base->IMR |= interrupts;
}

/*!
 * @brief Get LCDIC interrupt pending status.
 *
 * @param base LCDIC peripheral base address.
 * @return The interrupt pending status.
 *
 * @note The interrupt must be enabled, otherwise the interrupt flags will not assert.
 */
static inline uint32_t LCDIC_GetInterruptStatus(LCDIC_Type *base)
{
    return base->ISR;
}

/*!
 * @brief Get LCDIC raw interrupt status.
 *
 * This function gets the raw interrupt pending flags, it is not affected by
 * interrupt enabled status.
 *
 * @param base LCDIC peripheral base address.
 * @return The raw interrupt status.
 */
static inline uint32_t LCDIC_GetInterruptRawStatus(LCDIC_Type *base)
{
    return base->IRSR;
}

/*!
 * @brief Clear LCDIC interrupt status.
 *
 * @param base LCDIC peripheral base address.
 * @param interrupts The interrupt status to clear , pass in as OR'ed value of @ref _lcdic_interrupt.
 */
static inline void LCDIC_ClearInterruptStatus(LCDIC_Type *base, uint32_t interrupts)
{
    base->ICR = interrupts;
}

/*!
 * @brief Get LCDIC status flags.
 *
 * @note The interval between two times calling this function shall be larger
 * than one LCDIC function clock.
 *
 * @param base LCDIC peripheral base address.
 * @return The status flags, it is OR'ed value of _lcdic_flags.
 */
static inline uint32_t LCDIC_GetStatusFlags(LCDIC_Type *base)
{
    return base->STATUS0 & (uint32_t)kLCDIC_AllFlag;
}

/*!
 * @brief Get current on-going LCDIC TRX-CMD.
 *
 * @note The interval between two times calling this function shall be larger
 * than one LCDIC function clock.
 *
 * @param base LCDIC peripheral base address.
 * @return The TRX-CMD on-going.
 */
static inline uint32_t LCDIC_GetProcessingTrxCmd(LCDIC_Type *base)
{
    return base->STATUS1;
}
/* @} */

/*!
 * @name FIFO
 * @{
 */

/*!
 * @brief Set TX FIFO threshold.
 *
 * @param base LCDIC peripheral base address.
 * @param threshold TX threshold.
 */
static inline void LCDIC_SetTxThreshold(LCDIC_Type *base, lcdic_tx_threshold_t threshold)
{
    base->FIFO_CTRL = (base->FIFO_CTRL & ~LCDIC_FIFO_CTRL_TFIFO_THRES_MASK) | LCDIC_FIFO_CTRL_TFIFO_THRES(threshold);
}

/*!
 * @brief Set RX FIFO threshold.
 *
 * @param base LCDIC peripheral base address.
 * @param threshold RX threshold.
 */
static inline void LCDIC_SetRxThreshold(LCDIC_Type *base, lcdic_rx_threshold_t threshold)
{
    base->FIFO_CTRL = (base->FIFO_CTRL & ~LCDIC_FIFO_CTRL_RFIFO_THRES_MASK) | LCDIC_FIFO_CTRL_RFIFO_THRES(threshold);
}

/*!
 * @brief Write the TX FIFO using blocking way.
 *
 * This function waits for empty slot in TX FIFO and fill the data to TX FIFO.
 *
 * @param base LCDIC peripheral base address.
 * @param data Data to send, the data length must be dividable by 4.
 * @param dataLen_Word Data length in word.
 * @retval kStatus_Success Write successfully.
 * @retval kStatus_Timeout Timeout happened.
 */
status_t LCDIC_WriteTxFifoBlocking(LCDIC_Type *base, const uint32_t *data, uint32_t dataLen_Word);

/*!
 * @brief Read the RX FIFO using blocking way.
 *
 * This function waits for valid data in RX FIFO and read them.
 *
 * @param base LCDIC peripheral base address.
 * @param data Array for received data, the data length must be dividable by 4.
 * @param dataLen_Word Data length in word.
 * @retval kStatus_Success Read successfully.
 * @retval kStatus_Timeout Timeout happened.
 */
status_t LCDIC_ReadRxFifoBlocking(LCDIC_Type *base, uint32_t *data, uint32_t dataLen_Word);

/* @} */

/*!
 * @name Misc Operations
 * @{
 */

/*!
 * @brief Send reset sequence to the reset pin.
 *
 * The function sends reset to reset pin, to reset the external panel.
 * The reset sequence parameters are configued by @ref lcdic_config_t.
 *
 * @param base LCDIC peripheral base address.
 */
static inline void LCDIC_SendResetSequence(LCDIC_Type *base)
{
    base->RST_CTRL |= LCDIC_RST_CTRL_RST_START_MASK;
}

/*!
 * @brief Set the callback called when reset sequence sent done.
 *
 * @param callback The callback to set.
 */
void LCDIC_SetResetSequenceDoneCallback(lcdic_reset_done_callback_t callback);

/*!
 * @brief Enable or disable to trigger DMA.
 *
 * @param base LCDIC peripheral base address.
 * @param enable Use true to enable, false to disable.
 */
static inline void LCDIC_EnableDMA(LCDIC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= LCDIC_CTRL_DMA_EN_MASK;
    }
    else
    {
        base->CTRL &= ~LCDIC_CTRL_DMA_EN_MASK;
    }
}

/* @} */

/*!
 * @name Blocking transfer
 * @{
 */

/*!
 * @brief Send command using blocking way.
 *
 * This function sends out command and waits until send finished.
 *
 * @param base LCDIC peripheral base address.
 * @param cmd Command to send.
 * @retval kStatus_Success Command sent successfully.
 */
status_t LCDIC_SendCommandBlocking(LCDIC_Type *base, uint8_t cmd);

/*!
 * @brief Send repeat data using blocking way.
 *
 * This function sends out command and the repeat data, then waits until
 * send finished or timeout happened.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Pointer to the transfer configuration.
 * @retval kStatus_Success Sent successfully.
 * @retval kStatus_Timeout Timeout happened.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_SendRepeatDataBlocking(LCDIC_Type *base, const lcdic_repeat_tx_xfer_t *xfer);

/*!
 * @brief Send data array using blocking way.
 *
 * This function sends out command and the data array, then waits until
 * send finished or timeout happened.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Pointer to the transfer configuration.
 * @retval kStatus_Success Sent successfully.
 * @retval kStatus_Timeout Timeout happened.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_SendDataArrayBlocking(LCDIC_Type *base, const lcdic_tx_xfer_t *xfer);

/*!
 * @brief Read data array using blocking way.
 *
 * This function sends out command and read the data array, then waits until
 * send finished or timeout happened.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Pointer to the transfer configuration.
 * @retval kStatus_Success Sent successfully.
 * @retval kStatus_Timeout Timeout happened.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_ReadDataArrayBlocking(LCDIC_Type *base, const lcdic_rx_xfer_t *xfer);

/*!
 * @brief LCDIC data transfer using blocking way.
 *
 * This function sends command only, or sends repeat data, or sends data array,
 * or reads data array based on the transfer structure. It uses blocking way,
 * only returns when transfer successed or failed.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Pointer to the transfer configuration.
 * @retval kStatus_Success Sent successfully.
 * @retval kStatus_Timeout Timeout happened.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDC_TransferBlocking(LCDIC_Type *base, const lcdic_xfer_t *xfer);

/* @} */

/*!
 * @name Transactional APIs
 * @{
 */

/*!
 * @brief Initializes the LCDIC driver handle, which is used in transactional
 * functions.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 * @retval kStatus_Success Successfully created the handle.
 */
status_t LCDIC_TransferCreateHandle(LCDIC_Type *base,
                                    lcdic_handle_t *handle,
                                    lcdic_transfer_callback_t callback,
                                    void *userData);

/*!
 * @brief Transfer data using IRQ.
 *
 * This function transfer data using IRQ. This is a non-blocking function, which
 * returns right away. When all data is sent out/received, or timeout happened,
 * the callback function is called.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * @param xfer LCDIC transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_Busy LCDIC driver is busy with another transfer.
 */
status_t LCDIC_TransferNonBlocking(LCDIC_Type *base, lcdic_handle_t *handle, lcdic_xfer_t *xfer);

/*!
 * @brief LCDIC IRQ handler function.
 *
 * IRQ handler to work with @ref LCDIC_TransferNonBlocking.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
void LCDIC_TransferHandleIRQ(LCDIC_Type *base, void *handle);

/*!
 * @brief Install the IRQ handler.
 *
 * Install IRQ handler for specific instance.
 *
 * @param instance LCDIC instance.
 * @param handle Driver handle, it will be used as IRQ handler parameter.
 * @param handler IRQ handler to instance.
 */
void LCDIC_TransferInstallIRQHandler(uint32_t instance, void *handle, lcdic_transfer_irq_handler_t handler);

/* @} */

/*!
 * @name Helper functions
 * @{
 */

/*!
 * @brief Get the instance from the base address
 *
 * @param base LCDIC peripheral base address
 * @return The LCDIC module instance
 */
uint32_t LCDIC_GetInstance(LCDIC_Type *base);

/*!
 * @brief Get IRQn for specific instance.
 *
 * @param instance LCDIC instance.
 * @return The LCDIC IRQn.
 */
IRQn_Type LCDIC_GetIRQn(uint32_t instance);

/*!
 * @brief Get data from byte array, and fill to 4-byte word.
 *
 * LCDIC data registers only accept 4-byte data, but the user passed data might
 * be not 4-byte size aligned. This function is used to construct the unaligned
 * part to a word, to write to LCDIC register.
 *
 * @param bytes The byte array.
 * @param len Length of the byte array.
 * @return The construct word.
 */
uint32_t LCDIC_FillByteToWord(const uint8_t *bytes, uint8_t len);

/*!
 * @brief Get data from 4-byte, and fill to byte array.
 *
 * LCDIC data registers only accept 4-byte data, but the user passed data might
 * be not 4-byte size aligned. This function is used to get desired bytes from
 * the word read from LCDIC register, and save to the user data array.
 *
 * @param word Word data read from LCDIC register.
 * @param bytes The byte array.
 * @param len Length of the byte array.
 */
void LCDIC_ExtractByteFromWord(uint32_t word, uint8_t *bytes, uint8_t len);

/*!
 * @brief Prepare the command sending.
 *
 * Fill the TRX command and command to TX FIFO, after calling this function, user
 * should wait for transfer done by checking status or IRQ.
 *
 * @param base LCDIC peripheral base address.
 * @param cmd Command to send.
 * @retval kStatus_Success Operation successed.
 */
status_t LCDIC_PrepareSendCommand(LCDIC_Type *base, uint8_t cmd);

/*!
 * @brief Prepare the repeat data sending.
 *
 * Fill the required data to TX FIFO, after calling this function, user
 * should wait for transfer done by checking status or IRQ.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Transfer structure.
 * @retval kStatus_Success Operation successed.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareSendRepeatData(LCDIC_Type *base, const lcdic_repeat_tx_xfer_t *xfer);

/*!
 * @brief Prepare sending data array.
 *
 * Fill the required command data to TX FIFO, after calling this function, user
 * should fill the xfer->txData to TX FIFO based on FIFO status.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Transfer structure.
 * @param xferSizeWordAligned The word size aligned part of the transfer data.
 * @param xferSizeWordUnaligned The word size unaligned part of the transfer data.
 * @param wordUnalignedData Word to save the word size unaligned data, it should
 * be sent after all word size aligned data write finished.
 * @retval kStatus_Success Operation successed.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareSendDataArray(LCDIC_Type *base,
                                    const lcdic_tx_xfer_t *xfer,
                                    uint32_t *xferSizeWordAligned,
                                    uint8_t *xferSizeWordUnaligned,
                                    uint32_t *wordUnalignedData);

/*!
 * @brief Prepare reading data array.
 *
 * Fill the required command data to TX FIFO, after calling this function, user
 * should read RX FIFO to xfer->rxData based on FIFO status.
 *
 * @param base LCDIC peripheral base address.
 * @param xfer Transfer structure.
 * @param xferSizeWordAligned The word size aligned part of the transfer data.
 * @param xferSizeWordUnaligned The word size unaligned part of the transfer data.
 * @retval kStatus_Success Operation successed.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareReadDataArray(LCDIC_Type *base,
                                    const lcdic_rx_xfer_t *xfer,
                                    uint32_t *xferSizeWordAligned,
                                    uint8_t *xferSizeWordUnaligned);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_LCDIC_H_ */
