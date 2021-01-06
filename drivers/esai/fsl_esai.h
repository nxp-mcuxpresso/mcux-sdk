/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ESAI_H_
#define _FSL_ESAI_H_

#include "fsl_common.h"

/*!
 * @addtogroup esai
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_ESAI_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1 */
/*@}*/

/*! @brief ESAI return status, _esai_status_t*/
enum
{
    kStatus_ESAI_TxBusy    = MAKE_STATUS(kStatusGroup_ESAI, 0), /*!< ESAI Tx is busy. */
    kStatus_ESAI_RxBusy    = MAKE_STATUS(kStatusGroup_ESAI, 1), /*!< ESAI Rx is busy. */
    kStatus_ESAI_TxError   = MAKE_STATUS(kStatusGroup_ESAI, 2), /*!< ESAI Tx FIFO error. */
    kStatus_ESAI_RxError   = MAKE_STATUS(kStatusGroup_ESAI, 3), /*!< ESAI Rx FIFO error. */
    kStatus_ESAI_QueueFull = MAKE_STATUS(kStatusGroup_ESAI, 4), /*!< ESAI transfer queue is full. */
    kStatus_ESAI_TxIdle    = MAKE_STATUS(kStatusGroup_ESAI, 5), /*!< ESAI Tx is idle */
    kStatus_ESAI_RxIdle    = MAKE_STATUS(kStatusGroup_ESAI, 6)  /*!< ESAI Rx is idle */
};

/*! @brief Define the ESAI bus type */
typedef enum _esai_mode
{
    kESAI_NormalMode = 0x0U, /*!< Use normal mode.*/
    kESAI_NetworkMode        /*!< Network mode. */
} esai_mode_t;

/*! @brief Define the ESAI bus type */
typedef enum _esai_protocol
{
    kESAI_BusLeftJustified = 0x0U, /*!< Uses left justified format.*/
    kESAI_BusRightJustified,       /*!< Uses right justified format. */
    kESAI_BusI2S,                  /*!< Uses I2S format. */
    kESAI_BusPCMA,                 /*!< Uses I2S PCM A format.*/
    kESAI_BusPCMB,                 /*!< Uses I2S PCM B format. */
    kESAI_BusTDM,                  /*!< Use TDM mode */
    kESAI_BusCustomerNormal,       /*!< Customer defined normal mode */
    kESAI_BusCustomerNetwork       /*!< Customer defined network mode */
} esai_protocol_t;

/*! @brief Master or slave mode */
typedef enum _esai_master_slave
{
    kESAI_Master = 0x0U, /*!< Master mode */
    kESAI_Slave  = 0x1U  /*!< Slave mode */
} esai_master_slave_t;

/*! @brief Synchronous or asynchronous mode */
typedef enum _esai_sync_mode
{
    kESAI_ModeAsync = 0x0U, /*!< Asynchronous mode */
    kESAI_ModeSync,         /*!< Synchronous mode (with receiver or transmit) */
} esai_sync_mode_t;

/*! @brief Mater clock source */
typedef enum _esai_hclk_source
{
    kESAI_HckSourceInternal = 0x0U, /* HCK from ESAI internal clock, gnerally 133Mhz */
    kESAI_HckSourceExternal = 0x1U  /* HCK from external, soc specific, can be an audio PLL. */
} esai_hclk_source_t;

/*! @brief Bit clock source */
typedef enum _esai_clock_polarity
{
    kESAI_ClockActiveHigh = 0x0U, /*!< Clock active while high */
    kESAI_ClockActiveLow,         /*!< Clock actie while low */
} esai_clock_polarity_t;

/*! @brief ESAI shifter register shift direction */
typedef enum _esai_shift_direction
{
    kESAI_ShifterMSB = 0x0, /*!< Data is shifted MSB first */
    kESAI_ShifterLSB = 0x1  /*!< Data is shifted LSB first */
} esai_shift_direction_t;

/*! @brief ESAI clock direction */
typedef enum _esai_clock_direction
{
    kESAI_ClockInput  = 0x0, /*!< Clock direction is input */
    kESAI_ClockOutput = 0x1  /*!< Clock direction is output */
} esai_clock_direction_t;

/*! @brief The ESAI interrupt enable flag, _esai_interrupt_enable_t */
enum
{
    kESAI_LastSlotInterruptEnable =
        ESAI_TCR_TLIE_MASK, /*!< Enable interrupt at the beginning of last slot of frame in network mode */
    kESAI_TransmitInterruptEnable     = ESAI_TCR_TIE_MASK,   /*!< Transmit/receive even slot data interrupt */
    kESAI_EvenSlotDataInterruptEnable = ESAI_TCR_TEDIE_MASK, /*!< Transmit/receive even slot data interrupt */
    kESAI_ExceptionInterruptEnable    = ESAI_TCR_TEIE_MASK,  /*!< FIFO error flag */
};

/*! @brief The ESAI status flag, _esai_flags*/
enum
{
    kESAI_TransmitInitFlag          = ESAI_ESR_TINIT_MASK, /*!< Indicates transmit FIFO is writing the first word */
    kESAI_ReceiveFIFOFullFlag       = ESAI_ESR_RFF_MASK,   /*!< Receive FIFO full flag */
    kESAI_TransmitFIFOEmptyFlag     = ESAI_ESR_TFE_MASK,   /*!< Transmit FIFO empty */
    kESAI_TransmitLastSlotFlag      = ESAI_ESR_TLS_MASK,   /*!< Transmit last slot */
    kESAI_TransmitDataExceptionFlag = ESAI_ESR_TDE_MASK,   /*!< Transmit data exception */
    kESAI_TransmitEvenDataFlag      = ESAI_ESR_TED_MASK,   /*!< Transmit even data */
    kESAI_TransmitDataFlag          = ESAI_ESR_TD_MASK,    /*!< Transmit data */
    kESAI_ReceiveLastSlot           = ESAI_ESR_RLS_MASK,   /*!< Receive last slot */
    kESAI_ReceiveDataException      = ESAI_ESR_RDE_MASK,   /*!< Receive data exception */
    kESAI_ReceiveEvenData           = ESAI_ESR_RED_MASK,   /*!< Receive even data */
    kESAI_ReceiveData               = ESAI_ESR_RD_MASK,    /*!< Receive data */
};

/*! @brief SAI interface port status flag, _esai_sai_flags*/
enum
{
    kESAI_TransmitOddRegEmpty   = ESAI_SAISR_TODFE_MASK, /*!< Enabled transmitter register empty at odd slot */
    kESAI_TransmitEvenRegEmpty  = ESAI_SAISR_TEDE_MASK,  /*!< Enabled transmitter register empty at even slot */
    kESAI_TransmitRegEmpty      = ESAI_SAISR_TDE_MASK,  /*!< All data in enabled transmitter regsiter send to shifter */
    kESAI_TransmitUnderrunError = ESAI_SAISR_TUE_MASK,  /*!< Serial shifter empty  and a transmit slot begins */
    kESAI_TransmitFrameSync     = ESAI_SAISR_TFS_MASK,  /*!< A transmit frame sync occurred in the current time slot */
    kESAI_RecceiveOddRegFull    = ESAI_SAISR_RODF_MASK, /*!< Enabled receiver register full at odd slot */
    kESAI_ReceiveEvenRegFull    = ESAI_SAISR_RDF_MASK,  /*!< Enabled receiver register full at even slot */
    kESAI_RecceiveOverrunError  = ESAI_SAISR_ROE_MASK,  /*!< Receive data register overrun flag */
    kESAI_ReceiveFrameSync      = ESAI_SAISR_RFS_MASK,  /*!< Receive frame sync flag, indicate a frame sync occurs */
    kESAI_SerialInputFlag2      = ESAI_SAISR_IF2_MASK,  /*!< Serial input flag 2 */
    kESAI_SerialInputFlag1      = ESAI_SAISR_IF1_MASK,  /*!< Serial in out flag 1 */
    kESAI_SerialInputFlag0      = ESAI_SAISR_IF0_MASK   /*!< Serial input flag 0 */
};

/*! @brief Audio sample rate */
typedef enum _esai_sample_rate
{
    kESAI_SampleRate8KHz    = 8000U,  /*!< Sample rate 8000 Hz */
    kESAI_SampleRate11025Hz = 11025U, /*!< Sample rate 11025 Hz */
    kESAI_SampleRate12KHz   = 12000U, /*!< Sample rate 12000 Hz */
    kESAI_SampleRate16KHz   = 16000U, /*!< Sample rate 16000 Hz */
    kESAI_SampleRate22050Hz = 22050U, /*!< Sample rate 22050 Hz */
    kESAI_SampleRate24KHz   = 24000U, /*!< Sample rate 24000 Hz */
    kESAI_SampleRate32KHz   = 32000U, /*!< Sample rate 32000 Hz */
    kESAI_SampleRate44100Hz = 44100U, /*!< Sample rate 44100 Hz */
    kESAI_SampleRate48KHz   = 48000U, /*!< Sample rate 48000 Hz */
    kESAI_SampleRate96KHz   = 96000U  /*!< Sample rate 96000 Hz */
} esai_sample_rate_t;

/*! @brief Audio word width */
typedef enum _esai_word_width
{
    kESAI_WordWidth8bits  = 8U,  /*!< Audio data width 8 bits */
    kESAI_WordWidth16bits = 16U, /*!< Audio data width 16 bits */
    kESAI_WordWidth24bits = 24U, /*!< Audio data width 24 bits */
    kESAI_WordWidth32bits = 32U  /*!< Audio data width 32 bits */
} esai_word_width_t;

/*! @brief esai slot word length */
typedef enum _esai_slot_format
{
    kESAI_SlotLen8WordLen8   = 0x0U,  /*!< Slot length 8 bits, word length 8 bits */
    kESAI_SlotLen12WordLen8  = 0x04U, /*!< Slot length 12 bits, word length 8 bits */
    kESAI_SlotLen12WordLen12 = 0x01U, /*!< Slot length 12 bits, word length 12 bits */
    kESAI_SlotLen16WordLen8  = 0x08U, /*!< Slot length 16 bits, word length 8 bits */
    kESAI_SlotLen16WordLen12 = 0x05U, /*!< Slot length 16 bits, word length 12 bits */
    kESAI_SlotLen16WordLen16 = 0x02U, /*!< Slot length 16 bits, word length 16 bits */
    kESAI_SlotLen20WordLen8  = 0x0CU, /*!< Slot length 20 bits, word length 8 bits */
    kESAI_SlotLen20WordLen12 = 0x09U, /*!< Slot length 20 bits, word length 12 bits */
    kESAI_SlotLen20WordLen16 = 0x06U, /*!< Slot length 20 bits, word length 16 bits */
    kESAI_SlotLen20WordLen20 = 0x03U, /*!< Slot length 20 bits, word length 20 bits */
    kESAI_SlotLen24WordLen8  = 0x10U, /*!< Slot length 24 bits, word length 8 bits */
    kESAI_SlotLen24WordLen12 = 0x0DU, /*!< Slot length 24 bits, word length 12 bits */
    kESAI_SlotLen24WordLen16 = 0x0AU, /*!< Slot length 24 bits, word length 16 bits */
    kESAI_SlotLen24WordLen20 = 0x07U, /*!< Slot length 24 bits, word length 20 bits */
    kESAI_SlotLen24WordLen24 = 0x1EU, /*!< Slot length 24 bits, word length 24 bits */
    kESAI_SlotLen32WordLen8  = 0x18U, /*!< Slot length 32 bits, word length 8 bits */
    kESAI_SlotLen32WordLen12 = 0x15U, /*!< Slot length 32 bits, word length 12 bits */
    kESAI_SlotLen32WordLen16 = 0x12U, /*!< Slot length 32 bits, word length 16 bits */
    kESAI_SlotLen32WordLen20 = 0x0FU, /*!< Slot length 32 bits, word length 20 bits */
    kESAI_SlotLen32WordLen24 = 0x1FU  /*!< Slot length 32 bits, word length 24 bits */
} esai_slot_format_t;

/*! @brief ESAI customer defined audio format */
typedef struct _esai_customer_protocol
{
    esai_mode_t mode;                      /*!< ESAI mode, network, normal or on demand mode */
    esai_shift_direction_t shiftDirection; /*!< Data shift direction, MSB or LSB */
    bool fsEarly;                          /*!< If the frame sync one bit early */
    bool ifZeroPading;                     /*!< If padding zero */
    bool dataAlign;                        /*!< Data left aligned or right aligned */
    bool fsOneBit;                         /*!< If the frame sync one word length or one bit length */
    uint8_t slotNum;                       /*!< Slot number for the audio format */
} esai_customer_protocol_t;

/*! @brief ESAI user configuration structure */
typedef struct _esai_config
{
    esai_sync_mode_t syncMode;             /*!< ESAI sync mode, control Tx/Rx clock sync */
    esai_protocol_t txProtocol;            /*!< Use which kind of protocol */
    esai_protocol_t rxProtocol;            /*!< Use which kind of protocol */
    esai_customer_protocol_t txCustomer;   /*!< Audio protocol customer uses for tx */
    esai_customer_protocol_t rxCustomer;   /*!< Audio protocol customer uses for rx */
    esai_master_slave_t master;            /*!< Master or slave */
    esai_clock_direction_t txHckDirection; /*!< Tx HCK direction, input or output */
    esai_clock_direction_t rxHckDirection; /*!< Rx HCK direction, input or output */
    esai_hclk_source_t txHckSource;        /*!< Tx HCK input clock source */
    esai_hclk_source_t rxHckSource;        /*!< Rx HCK input clock source */
    esai_hclk_source_t txHckOutputSource;  /*!< Tx HCK pin output clock source */
    esai_hclk_source_t rxHckOutputSource;  /*!< Rx HCK pin output clock source */
    esai_clock_polarity_t txHckPolarity;   /*!< Tx HCK polarity */
    esai_clock_polarity_t txFsPolarity;    /*!< Tx frame sync polarity */
    esai_clock_polarity_t txSckPolarity;   /*!< Tx bit clock polarity */
    esai_clock_polarity_t rxHckPolarity;   /*!< Rx HCK polarity */
    esai_clock_polarity_t rxFsPolarity;    /*!< Rx frame sync polarity */
    esai_clock_polarity_t rxSckPolarity;   /*!< Rx bit clock polarity */
    uint8_t txWatermark;                   /*!< Tx transfer watermark */
    uint8_t rxWatermark;                   /*!< Rx receive watermark */
} esai_config_t;

/*!@brief ESAI transfer queue size, user can refine it according to use case. */
#define ESAI_XFER_QUEUE_SIZE (4U)

/*! @brief esai transfer format */
typedef struct _esai_format
{
    esai_sample_rate_t sampleRate_Hz; /*!< Sample rate of audio data */
    esai_slot_format_t slotType;      /*!< Slot format for audio format */
    uint8_t sectionMap; /*!< The sections enabled, 0x1 means TE0 enabled, 0x2 means TE1 enabled, 0x4 means TE2, etc  */
} esai_format_t;

/*! @brief ESAI transfer structure */
typedef struct _esai_transfer
{
    uint8_t *data;   /*!< Data start address to transfer. */
    size_t dataSize; /*!< Transfer size. */
} esai_transfer_t;

typedef struct _esai_handle esai_handle_t;

/*! @brief ESAI transfer callback prototype */
typedef void (*esai_transfer_callback_t)(ESAI_Type *base, esai_handle_t *handle, status_t status, void *userData);

/*! @brief ESAI handle structure */
struct _esai_handle
{
    uint32_t state;                                  /*!< Transfer status */
    esai_transfer_callback_t callback;               /*!< Callback function called at transfer event*/
    void *userData;                                  /*!< Callback parameter passed to callback function*/
    uint8_t bitWidth;                                /*!< Bit width for transfer, 8/16/24/32 bits */
    uint8_t slotLen;                                 /*!< Slot length of the audio data */
    uint8_t sectionMap;                              /*!< Enabled section map */
    esai_transfer_t esaiQueue[ESAI_XFER_QUEUE_SIZE]; /*!< Transfer queue storing queued transfer */
    size_t transferSize[ESAI_XFER_QUEUE_SIZE];       /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                      /*!< Index for user to queue transfer */
    volatile uint8_t queueDriver;                    /*!< Index for driver to get the transfer data and size */
    uint8_t watermark;                               /*!< Watermark value */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the ESAI peripheral.
 *
 * Ungates the ESAI clock, resets the module, and configures ESAI with a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * ESAI_GetDefaultConfig().
 *
 * @note  This API should be called at the beginning of the application to use
 * the ESAI driver. Otherwise, accessing the ESAI module can cause a hard fault
 * because the clock is not enabled.
 *
 * @param base ESAI base pointer
 * @param config ESAI configuration structure.
 */
void ESAI_Init(ESAI_Type *base, esai_config_t *config);

/*!
 * @brief  Sets the ESAI configuration structure to default values.
 *
 * This API initializes the configuration structure for use in ESAI_TxConfig().
 * The initialized structure can remain unchanged in ESAI_Init(), or it can be modified
 *  before calling ESAI_Init().
 *
 * @param config pointer to master configuration structure
 */
void ESAI_GetDefaultConfig(esai_config_t *config);

/*!
 * @brief De-initializes the ESAI peripheral.
 *
 * This API gates the ESAI clock. The ESAI module can't operate unless ESAI_Init
 * is called to enable the clock.
 *
 * @param base ESAI base pointer
 */
void ESAI_Deinit(ESAI_Type *base);

/*!
 * @brief Enable/Disable the ESAI peripheral internal logic.
 *
 * @param base ESAI base pointer
 * @param enable True meanse enable, false means disable.
 */
static inline void ESAI_Enable(ESAI_Type *base, bool enable)
{
    if (enable)
    {
        base->ECR |= ESAI_ECR_ESAIEN_MASK;
    }
    else
    {
        base->ECR &= ~ESAI_ECR_ESAIEN_MASK;
    }
}

/*!
 * @brief Reset ESAI internal logic.
 *
 * This API only resets the core logic, including the configuration registers, but not the ESAI FIFOs, users
 * still needs to reset the ESAI fifo by calling ESAI_TxResetFIFO and ESAI_RxResetFIFO.
 *
 * @param base ESAI base pointer
 */
static inline void ESAI_Reset(ESAI_Type *base)
{
    base->ECR |= ESAI_ECR_ERST_MASK;
    base->ECR &= ~ESAI_ECR_ERST_MASK;
}

/*!
 * @brief Reset ESAI all tx sections.
 *
 * This API only resets the core logic of tx and all tx sections.
 *
 * @param base ESAI base pointer
 */
void ESAI_TxReset(ESAI_Type *base);

/*!
 * @brief Reset ESAI all rx sections.
 *
 * This API only resets the core logic of rx and all rx sections.
 *
 * @param base ESAI base pointer
 */
void ESAI_RxReset(ESAI_Type *base);

/*!
 * @brief Resets the ESAI Tx FIFO.
 *
 * This function only resets the ESAI Tx FIFO.
 *
 * @param base ESAI base pointer
 */
static inline void ESAI_TxResetFIFO(ESAI_Type *base)
{
    base->TFCR |= ESAI_TFCR_TFR_MASK;
}

/*!
 * @brief Resets the ESAI Rx FIFO.
 *
 * This function only resets the ESAI Rx FIFO.
 *
 * @param base ESAI base pointer
 */
static inline void ESAI_RxResetFIFO(ESAI_Type *base)
{
    base->RFCR |= ESAI_TFCR_TFR_MASK;
}

/*!
 * @brief Enables/disables ESAI Tx.
 *
 * @param base ESAI base pointer
 * @param sectionMap Which sections need to be enabled. 0 means all section disabled. This parameter can be a
 * combination of each sections, every section N is 2^N in section map.
 */
void ESAI_TxEnable(ESAI_Type *base, uint8_t sectionMap);

/*!
 * @brief Enables/disables ESAI Rx.
 *
 * @param base ESAI base pointer
 * @param sectionMap Which sections need to be enabled. 0 means all section disabled. This parameter can be a
 * combination of each sections, every section N is 2^N in section map.
 */
void ESAI_RxEnable(ESAI_Type *base, uint8_t sectionMap);

/*!
 * @brief Enables/disables ESAI Tx FIFO.
 *
 * @param base ESAI base pointer
 * @param enable True means enable ESAI Tx, false means disable.
 */
static inline void ESAI_TxEnableFIFO(ESAI_Type *base, bool enable)
{
    if (enable)
    {
        base->TFCR |= ESAI_TFCR_TFE_MASK;
    }
    else
    {
        base->TFCR &= ~ESAI_TFCR_TFE_MASK;
    }
}

/*!
 * @brief Enables/disables ESAI Rx FIFO.
 *
 * @param base ESAI base pointer
 * @param enable True means enable ESAI Rx, false means disable.
 */
static inline void ESAI_RxEnableFIFO(ESAI_Type *base, bool enable)
{
    if (enable)
    {
        base->RFCR |= ESAI_RFCR_RFE_MASK;
    }
    else
    {
        base->RFCR &= ~ESAI_RFCR_RFE_MASK;
    }
}

/*!
 * @brief Set ESAI Tx slot mask value.
 *
 * @param base ESAI base pointer
 * @param slot Slot number need to be masked for Tx.
 */
static inline void ESAI_TxSetSlotMask(ESAI_Type *base, uint32_t slot)
{
    base->TSMA = (slot & 0xFFFFU);
    base->TSMB = (slot & 0xFFFF0000U) >> 16U;
}

/*!
 * @brief Set ESAI Rx slot mask value.
 *
 * @param base ESAI base pointer
 * @param slot Slot number need to be masked for Rx
 */
static inline void EASI_RxSetSlotMask(ESAI_Type *base, uint32_t slot)
{
    base->RSMA = (slot & 0xFFFFU);
    base->RSMB = (slot & 0xFFFF0000U) >> 16U;
}

/*!
 * @brief Get the data length and slot length from the input.
 *
 * This API sets the audio protocol defined by users.
 *
 * @param slotFormat Slot type.
 * @param slotLen Pointer to the return slot length value.
 * @param dataLen Pointer to the return data length in a slot.
 */
void ESAI_AnalysisSlot(esai_slot_format_t slotFormat, uint8_t *slotLen, uint8_t *dataLen);

/*!
 * @brief Get the instance number for ESAI.
 *
 * @param base ESAI base pointer.
 */
uint32_t ESAI_GetInstance(ESAI_Type *base);

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the ESAI status flag state.
 *
 * @param base ESAI base pointer
 * @return ESAI staus flag value. Use status flag to AND _esai_flags to get the related status.
 */
static inline uint32_t ESAI_GetStatusFlag(ESAI_Type *base)
{
    return base->ESR;
}

/*!
 * @brief Gets the ESAI SAI port status flag state.
 *
 * @param base ESAI base pointer
 * @return ESAI staus flag value. Use status flag to AND _esai_sai_flags to get the related status.
 */
static inline uint32_t ESAI_GetSAIStatusFlag(ESAI_Type *base)
{
    return base->SAISR;
}

/*!
 * @brief Gets the ESAI Tx FIFO state.
 *
 * @param base ESAI base pointer
 * @return ESAI Tx status flag value.
 */
static inline uint32_t ESAI_GetTxFIFOStatus(ESAI_Type *base)
{
    return base->TFSR;
}

/*!
 * @brief Gets the ESAI Tx status flag state.
 *
 * @param base ESAI base pointer
 * @return ESAI Rx status flag value.
 */
static inline uint32_t ESAI_GetRxFIFOStatus(ESAI_Type *base)
{
    return base->RFSR;
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables ESAI Tx interrupt requests.
 *
 * @param base ESAI base pointer
 * @param mask interrupt source. The parameter can be a combination of elements in _esai_interrupt_enable_t.
 */
static inline void ESAI_TxEnableInterrupts(ESAI_Type *base, uint32_t mask)
{
    base->TCR |= mask;
}

/*!
 * @brief Enables ESAI Rx interrupt requests.
 *
 * @param base ESAI base pointer
 * @param mask interrupt source. The parameter can be a combination of elements in _esai_interrupt_enable_t.
 */
static inline void ESAI_RxEnableInterrupts(ESAI_Type *base, uint32_t mask)
{
    base->RCR |= mask;
}

/*!
 * @brief Disables ESAI Tx interrupt requests.
 *
 * @param base ESAI base pointer
 * @param mask interrupt source. The parameter can be a combination of elements in _esai_interrupt_enable_t.
 */
static inline void ESAI_TxDisableInterrupts(ESAI_Type *base, uint32_t mask)
{
    base->TCR &= (~mask);
}

/*!
 * @brief Disables ESAI Rx interrupt requests.
 *
 * @param base ESAI base pointer
 * @param mask interrupt source. The parameter can be a combination of elements in _esai_interrupt_enable_t.
 */
static inline void ESAI_RxDisableInterrupts(ESAI_Type *base, uint32_t mask)
{
    base->RCR &= (~mask);
}

/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief  Gets the ESAI Tx data register address.
 *
 * This API is used to provide a transfer address for ESAI DMA transfer configuration.
 *
 * @param base ESAI base pointer.
 * @return data register address.
 */
static inline uint32_t ESAI_TxGetDataRegisterAddress(ESAI_Type *base)
{
    return (uint32_t)(&(base->ETDR));
}

/*!
 * @brief  Gets the ESAI Rx data register address.
 *
 * This API is used to provide a transfer address for ESAI DMA transfer configuration.
 *
 * @param base ESAI base pointer.
 * @return data register address.
 */
static inline uint32_t ESAI_RxGetDataRegisterAddress(ESAI_Type *base)
{
    return (uint32_t)(&(base->ERDR));
}

/*! @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * @param base ESAI base pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hckSourceClockHz HCK source clock frequency in Hz.
 */
void ESAI_TxSetFormat(ESAI_Type *base, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz);

/*!
 * @brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * @param base ESAI base pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hckSourceClockHz HCK source clock frequency in Hz.
 */
void ESAI_RxSetFormat(ESAI_Type *base, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz);

/*!
 * @brief Sends data using a blocking method.
 *
 * @note This function blocks by polling until data is ready to be sent.
 *
 * @param base ESAI base pointer.
 * @param bitWidth How many bits in a audio word, usually 8/16/24 bits.
 * @param buffer Pointer to the data to be written.
 * @param size Bytes to be written.
 */
void ESAI_WriteBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size);

/*!
 * @brief Writes data into ESAI FIFO.
 *
 * @param base ESAI base pointer.
 * @param data Data needs to be written.
 */
static inline void ESAI_WriteData(ESAI_Type *base, uint32_t data)
{
    base->ETDR = data;
}

/*!
 * @brief Receives data using a blocking method.
 *
 * @note This function blocks by polling until data is ready to be sent.
 *
 * @param base ESAI base pointer.
 * @param bitWidth How many bits in a audio word, usually 8/16/24 bits.
 * @param buffer Pointer to the data to be read.
 * @param size Bytes to be read.
 */
void ESAI_ReadBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size);

/*!
 * @brief Reads data from ESAI FIFO.
 *
 * @param base ESAI base pointer.
 * @param channel Data channel used.
 * @return Data in ESAI FIFO.
 */
static inline uint32_t ESAI_ReadData(ESAI_Type *base, uint32_t channel)
{
    return base->ERDR;
}

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the ESAI Tx handle.
 *
 * This function initializes the Tx handle for ESAI Tx transactional APIs. Call
 * this function one time to get the handle initialized.
 *
 * @param base ESAI base pointer
 * @param handle ESAI handle pointer.
 * @param callback pointer to user callback function
 * @param userData user parameter passed to the callback function
 */
void ESAI_TransferTxCreateHandle(ESAI_Type *base,
                                 esai_handle_t *handle,
                                 esai_transfer_callback_t callback,
                                 void *userData);

/*!
 * @brief Initializes the ESAI Rx handle.
 *
 * This function initializes the Rx handle for ESAI Rx transactional APIs. Call
 * this function one time to get the handle initialized.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI handle pointer.
 * @param callback pointer to user callback function
 * @param userData user parameter passed to the callback function
 */
void ESAI_TransferRxCreateHandle(ESAI_Type *base,
                                 esai_handle_t *handle,
                                 esai_transfer_callback_t callback,
                                 void *userData);

/*!
 * @brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI handle pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hckSourceClockHz HCK clock source frequency in Hz.
 * @return Status of this function. Return value is one of status_t.
 */
status_t ESAI_TransferTxSetFormat(
    ESAI_Type *base, esai_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz);

/*!
 * @brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI handle pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hckSourceClockHz HCK clock source frequency in Hz.
 * @return Status of this function. Return value is one of status_t.
 */
status_t ESAI_TransferRxSetFormat(
    ESAI_Type *base, esai_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz);

/*!
 * @brief Performs an interrupt non-blocking send transfer on ESAI.
 *
 * @note This API returns immediately after the transfer initiates.
 * Call the ESAI_TxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_ESAI_Busy, the transfer
 * is finished.
 *
 * @param base ESAI base pointer
 * @param handle pointer to esai_handle_t structure which stores the transfer state
 * @param xfer pointer to esai_transfer_t structure
 * @retval kStatus_Success Successfully started the data receive.
 * @retval kStatus_ESAI_TxBusy Previous receive still not finished.
 * @retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t ESAI_TransferSendNonBlocking(ESAI_Type *base, esai_handle_t *handle, esai_transfer_t *xfer);

/*!
 * @brief Performs an interrupt non-blocking receive transfer on ESAI.
 *
 * @note This API returns immediately after the transfer initiates.
 * Call the ESAI_RxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_ESAI_Busy, the transfer
 * is finished.
 *
 * @param base ESAI base pointer
 * @param handle pointer to esai_handle_t structure which stores the transfer state
 * @param xfer pointer to esai_transfer_t structure
 * @retval kStatus_Success Successfully started the data receive.
 * @retval kStatus_ESAI_RxBusy Previous receive still not finished.
 * @retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t ESAI_TransferReceiveNonBlocking(ESAI_Type *base, esai_handle_t *handle, esai_transfer_t *xfer);

/*!
 * @brief Gets a set byte count.
 *
 * @param base ESAI base pointer.
 * @param handle pointer to esai_handle_t structure which stores the transfer state.
 * @param count Bytes count sent.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ESAI_TransferGetSendCount(ESAI_Type *base, esai_handle_t *handle, size_t *count);

/*!
 * @brief Gets a received byte count.
 *
 * @param base ESAI base pointer.
 * @param handle pointer to esai_handle_t structure which stores the transfer state.
 * @param count Bytes count received.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ESAI_TransferGetReceiveCount(ESAI_Type *base, esai_handle_t *handle, size_t *count);

/*!
 * @brief Aborts the current send.
 *
 * @note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param base ESAI base pointer.
 * @param handle pointer to esai_handle_t structure which stores the transfer state.
 */
void ESAI_TransferAbortSend(ESAI_Type *base, esai_handle_t *handle);

/*!
 * @brief Aborts the current IRQ receive.
 *
 * @note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param base ESAI base pointer
 * @param handle pointer to esai_handle_t structure which stores the transfer state.
 */
void ESAI_TransferAbortReceive(ESAI_Type *base, esai_handle_t *handle);

/*!
 * @brief Tx interrupt handler.
 *
 * @param base ESAI base pointer.
 * @param handle pointer to esai_handle_t structure.
 */
void ESAI_TransferTxHandleIRQ(ESAI_Type *base, esai_handle_t *handle);

/*!
 * @brief Tx interrupt handler.
 *
 * @param base ESAI base pointer.
 * @param handle pointer to esai_handle_t structure.
 */
void ESAI_TransferRxHandleIRQ(ESAI_Type *base, esai_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus*/

/*! @} */

#endif /* _FSL_ESAI_H_ */
