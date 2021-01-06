/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_MSCAN_H_
#define _FSL_MSCAN_H_

#include "fsl_common.h"

/*!
 * @addtogroup mscan_driver
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief MsCAN driver version. */
#define FSL_MSCAN_DRIVER_VERSION (MAKE_VERSION(2, 0, 6))
/*@}*/

/*! @brief MsCAN Rx Message Buffer Mask helper macro. */
#define MSCAN_RX_MB_STD_MASK(id)               \
    ((uint32_t)((((uint32_t)(id)&0x7) << 21) | \
                ((((uint32_t)(id) >> 3) & 0xFF) << 24))) /*!< Standard Rx Message Buffer Mask helper macro. */
#define MSCAN_RX_MB_EXT_MASK(id)                                                                   \
    ((uint32_t)(((((uint32_t)(id) >> 21) & 0xFF) << 24) | ((((uint32_t)(id) >> 18) & 0x7) << 21) | \
                ((((uint32_t)(id) >> 15) & 0x7) << 16) | (((((uint32_t)(id) >> 7) & 0xFF)) << 8) | \
                (((uint32_t)(id)&0x7F) << 1))) /*!< Extend Rx Message Buffer Mask helper macro. */

/*! @brief FlexCAN transfer status. */
enum
{
    kStatus_MSCAN_TxBusy       = MAKE_STATUS(kStatusGroup_MSCAN, 0), /*!< Tx Message Buffer is Busy. */
    kStatus_MSCAN_TxIdle       = MAKE_STATUS(kStatusGroup_MSCAN, 1), /*!< Tx Message Buffer is Idle. */
    kStatus_MSCAN_TxSwitchToRx = MAKE_STATUS(
        kStatusGroup_MSCAN, 2), /*!< Remote Message is send out and Message buffer changed to Receive one. */
    kStatus_MSCAN_RxBusy         = MAKE_STATUS(kStatusGroup_MSCAN, 3),  /*!< Rx Message Buffer is Busy. */
    kStatus_MSCAN_RxIdle         = MAKE_STATUS(kStatusGroup_MSCAN, 4),  /*!< Rx Message Buffer is Idle. */
    kStatus_MSCAN_RxOverflow     = MAKE_STATUS(kStatusGroup_MSCAN, 5),  /*!< Rx Message Buffer is Overflowed. */
    kStatus_MSCAN_RxFifoBusy     = MAKE_STATUS(kStatusGroup_MSCAN, 6),  /*!< Rx Message FIFO is Busy. */
    kStatus_MSCAN_RxFifoIdle     = MAKE_STATUS(kStatusGroup_MSCAN, 7),  /*!< Rx Message FIFO is Idle. */
    kStatus_MSCAN_RxFifoOverflow = MAKE_STATUS(kStatusGroup_MSCAN, 8),  /*!< Rx Message FIFO is overflowed. */
    kStatus_MSCAN_RxFifoWarning  = MAKE_STATUS(kStatusGroup_MSCAN, 9),  /*!< Rx Message FIFO is almost overflowed. */
    kStatus_MSCAN_ErrorStatus    = MAKE_STATUS(kStatusGroup_MSCAN, 10), /*!< FlexCAN Module Error and Status. */
    kStatus_MSCAN_UnHandled      = MAKE_STATUS(kStatusGroup_MSCAN, 11), /*!< UnHadled Interrupt asserted. */
};

/*! @brief MsCAN frame format. */
typedef enum _mscan_frame_format
{
    kMSCAN_FrameFormatStandard = 0x0U, /*!< Standard frame format attribute. */
    kMSCAN_FrameFormatExtend   = 0x1U, /*!< Extend frame format attribute. */
} mscan_frame_format_t;

/*! @brief MsCAN frame type. */
typedef enum _mscan_frame_type
{
    kMSCAN_FrameTypeData   = 0x0U, /*!< Data frame type attribute. */
    kMSCAN_FrameTypeRemote = 0x1U, /*!< Remote frame type attribute. */
} mscan_frame_type_t;

/*! @brief MsCAN clock source. */
typedef enum _mscan_clock_source
{
    kMSCAN_ClkSrcOsc = 0x0U, /*!< MsCAN Protocol Engine clock from Oscillator. */
    kMSCAN_ClkSrcBus = 0x1U, /*!< MsCAN Protocol Engine clock from Bus Clock. */
} mscan_clock_source_t;

/*! @brief MsCAN bus-off recovery mode. */
typedef enum _mscan_busoffrec_mode
{
    kMSCAN_BusoffrecAuto = 0x0U, /*!< MsCAN automatic bus-off recovery. */
    kMSCAN_BusoffrecUsr  = 0x1U, /*!< MsCAN bus-off recovery upon user request. */
} mscan_busoffrec_mode_t;

/*! @brief MsCAN Tx buffer empty flag. */
enum _mscan_tx_buffer_empty_flag
{
    kMSCAN_TxBuf0Empty = 0x1U, /*!< MsCAN Tx Buffer 0 empty. */
    kMSCAN_TxBuf1Empty = 0x2U, /*!< MsCAN Tx Buffer 1 empty. */
    kMSCAN_TxBuf2Empty = 0x4U, /*!< MsCAN Tx Buffer 2 empty. */
    kMSCAN_TxBufFull   = 0x0U, /*!< MsCAN Tx Buffer all not empty. */
};

/*! @brief MsCAN id filter mode. */
typedef enum _mscan_id_filter_mode
{
    kMSCAN_Filter32Bit = 0x0U, /*!< Two 32-bit acceptance filters. */
    kMSCAN_Filter16Bit = 0x1U, /*!< Four 16-bit acceptance filters. */
    kMSCAN_Filter8Bit  = 0x2U, /*!< Eight 8-bit acceptance filters. */
    kMSCAN_FilterClose = 0x3U, /*!< Filter closed. */
} mscan_id_filter_mode_t;

/*!
 * @brief MsCAN interrupt configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the MsCAN Module interrupt configurations.
 */
enum _mscan_interrupt_enable
{
    kMSCAN_WakeUpInterruptEnable         = MSCAN_CANRIER_WUPIE_MASK,  /*!< Wake Up interrupt. */
    kMSCAN_StatusChangeInterruptEnable   = MSCAN_CANRIER_CSCIE_MASK,  /*!< Status change interrupt. */
    kMSCAN_RxStatusChangeInterruptEnable = MSCAN_CANRIER_RSTATE_MASK, /*!< Rx status change interrupt. */
    kMSCAN_TxStatusChangeInterruptEnable = MSCAN_CANRIER_TSTATE_MASK, /*!< Tx status change interrupt. */
    kMSCAN_OverrunInterruptEnable        = MSCAN_CANRIER_OVRIE_MASK,  /*!< Overrun interrupt. */
    kMSCAN_RxFullInterruptEnable         = MSCAN_CANRIER_RXFIE_MASK,  /*!< Rx buffer full interrupt. */
    kMSCAN_TxEmptyInterruptEnable        = MSCAN_CANTIER_TXEIE_MASK,  /*!< Tx buffer empty interrupt. */
};

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/*! @brief MSCAN IDR1 struct. */
typedef struct
{
    uint8_t EID17_15 : 3;           /*!< Extended Format Identifier 17-15*/
    uint8_t R_TEIDE : 1;            /*!< ID Extended */
    uint8_t R_TSRR : 1;             /*!< Substitute Remote Request */
    uint8_t EID20_18_OR_SID2_0 : 3; /*!< Extended Format Identifier 18-20 or standard format bit 0-2*/
} MSCAN_IDR1Type;

/*! @brief MSCAN IDR3 struct. */
typedef struct
{
    uint8_t ERTR : 1;   /*!< Remote Transmission Request*/
    uint8_t EID6_0 : 7; /*!< Extended Format Identifier 6-0*/
} MSCAN_IDR3Type;

/*! @brief MSCAN idr1 and idr3 union. */
typedef union
{
    MSCAN_IDR1Type IDR1; /*!< structure for identifier 1 */
    MSCAN_IDR3Type IDR3; /*!< structure for identifier 3 */
    uint8_t Bytes;       /*!< bytes */
} IDR1_3_UNION;

/*! @brief MSCAN extend ID struct. */
typedef struct
{
    uint32_t EID6_0 : 7;   /*!< ID[0:6] */
    uint32_t EID14_7 : 8;  /*!< ID[14:7] */
    uint32_t EID17_15 : 3; /*!< ID[17:15] */
    uint32_t EID20_18 : 3; /*!< ID[20:18] */
    uint32_t EID28_21 : 8; /*!< ID[28:21] */
    uint32_t rsvd : 3;
} MSCAN_ExtendIDType;

/*! @brief MSCAN standard ID struct. */
typedef struct
{
    uint32_t EID2_0 : 3;  /*!< ID[0:2] */
    uint32_t EID10_3 : 8; /*!< ID[10:3] */
    uint32_t rsvd : 21;
} MSCAN_StandardIDType;

/*! @brief MsCAN message buffer structure. */
typedef struct _mscan_mb
{
    uint8_t EIDR0;   /*!< Extended Identifier Register 0 */
    uint8_t EIDR1;   /*!< Extended Identifier Register 1 */
    uint8_t EIDR2;   /*!< Extended Identifier Register 2 */
    uint8_t EIDR3;   /*!< Extended Identifier Register 3 */
    uint8_t EDSR[8]; /*!< Extended Data Segment Register */
    uint8_t DLR;     /*!< data length field */
    uint8_t BPR;     /*!< Buffer Priority Register */
    uint8_t TSRH;    /*!< Time Stamp Register High */
    uint8_t TSRL;    /*!< Time Stamp Register Low */
} mscan_mb_t;

/*! @brief MsCAN frame structure. */
typedef struct _mscan_frame
{
    union
    {
        MSCAN_StandardIDType StdID; /*!< standard format */
        MSCAN_ExtendIDType ExtID;   /*!< extend format */
        uint32_t ID;                /*!< Identifire with 32 bit format */
    } ID_Type;                      /*!< identifier union */
    union
    {
        uint8_t DSR[8]; /*!< data segment */
        struct
        {
            uint32_t dataWord0; /*!< MSCAN Frame payload word0. */
            uint32_t dataWord1; /*!< MSCAN Frame payload word1. */
        };
        struct
        {
            uint8_t dataByte0; /*!< MSCAN Frame payload byte0. */
            uint8_t dataByte1; /*!< MSCAN Frame payload byte1. */
            uint8_t dataByte2; /*!< MSCAN Frame payload byte2. */
            uint8_t dataByte3; /*!< MSCAN Frame payload byte3. */
            uint8_t dataByte4; /*!< MSCAN Frame payload byte4. */
            uint8_t dataByte5; /*!< MSCAN Frame payload byte5. */
            uint8_t dataByte6; /*!< MSCAN Frame payload byte6. */
            uint8_t dataByte7; /*!< MSCAN Frame payload byte7. */
        };
    };
    uint8_t DLR;                 /*!< data length */
    uint8_t BPR;                 /*!< transmit buffer priority */
    mscan_frame_type_t type;     /*!< remote frame or data frame */
    mscan_frame_format_t format; /*!< extend frame or standard frame */
    uint8_t TSRH;                /*!< time stamp high byte */
    uint8_t TSRL;                /*!< time stamp low byte */
} mscan_frame_t;

/*! @brief MsCAN module acceptance filter configuration structure. */
typedef struct _mscan_idfilter_config
{
    mscan_id_filter_mode_t filterMode; /*!< MSCAN Identifier Acceptance Filter Mode */
    uint32_t u32IDAR0;                 /*!< MSCAN Identifier Acceptance Register n of First Bank */
    uint32_t u32IDAR1;                 /*!< MSCAN Identifier Acceptance Register n of Second Bank */
    uint32_t u32IDMR0;                 /*!< MSCAN Identifier Mask Register n of First Bank */
    uint32_t u32IDMR1;                 /*!< MSCAN Identifier Mask Register n of Second Bank */
} mscan_idfilter_config_t;

/*! @brief MsCAN module configuration structure. */
typedef struct _mscan_config
{
    uint32_t baudRate;                    /*!< MsCAN baud rate in bps. */
    bool enableTimer;                     /*!< Enable or Disable free running timer. */
    bool enableWakeup;                    /*!< Enable or Disable Wakeup Mode. */
    mscan_clock_source_t clkSrc;          /*!< Clock source for MsCAN Protocol Engine. */
    bool enableLoopBack;                  /*!< Enable or Disable Loop Back Self Test Mode. */
    bool enableListen;                    /*!< Enable or Disable Listen Only Mode. */
    mscan_busoffrec_mode_t busoffrecMode; /*!< Bus-Off Recovery Mode. */
    mscan_idfilter_config_t filterConfig;
} mscan_config_t;

/*! @brief MsCAN protocol timing characteristic configuration structure. */
typedef struct _mscan_timing_config
{
    uint8_t priDiv;     /*!< Baud rate prescaler. */
    uint8_t sJumpwidth; /*!< Sync Jump Width. */
    uint8_t timeSeg1;   /*!< Time Segment 1. */
    uint8_t timeSeg2;   /*!< Time Segment 2. */
    uint8_t samp;       /*!< Number of samples per bit time. */
} mscan_timing_config_t;

/*! @brief MSCAN Message Buffer transfer. */
typedef struct _mscan_mb_transfer
{
    mscan_frame_t *frame; /*!< The buffer of CAN Message to be transfer. */
    uint8_t mask;         /*!< The mask of Tx buffer. */
} mscan_mb_transfer_t;

/*! @brief MsCAN handle structure definition. */
typedef struct _mscan_handle mscan_handle_t;

/*! @brief MsCAN transfer callback function.
 *
 *  The MsCAN transfer callback returns a value from the underlying layer.
 *  If the status equals to kStatus_MSCAN_ErrorStatus, the result parameter is the Content of
 *  MsCAN status register which can be used to get the working status(or error status) of MsCAN module.
 *  If the status equals to other MsCAN Message Buffer transfer status, the result is the index of
 *  Message Buffer that generate transfer event.
 *  If the status equals to other MsCAN Message Buffer transfer status, the result is meaningless and should be
 *  Ignored.
 */
typedef void (*mscan_transfer_callback_t)(MSCAN_Type *base, mscan_handle_t *handle, status_t status, void *userData);

/*! @brief MsCAN handle structure. */
struct _mscan_handle
{
    mscan_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                     /*!< MsCAN callback function parameter.*/
    mscan_frame_t *volatile mbFrameBuf;
    /*!< The buffer for received data from Message Buffers. */
    volatile uint8_t mbStateTx; /*!< Message Buffer transfer state. */
    volatile uint8_t mbStateRx; /*!< Message Buffer transfer state. */
};

/******************************************************************************
 * API
 *****************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes a MsCAN instance.
 *
 * This function initializes the MsCAN module with user-defined settings.
 * This example shows how to set up the mscan_config_t parameters and how
 * to call the MSCAN_Init function by passing in these parameters.
 *  @code
 *   mscan_config_t mscanConfig;
 *   mscanConfig.clkSrc            = kMSCAN_ClkSrcOsc;
 *   mscanConfig.baudRate          = 1250000U;
 *   mscanConfig.enableTimer       = false;
 *   mscanConfig.enableLoopBack    = false;
 *   mscanConfig.enableWakeup      = false;
 *   mscanConfig.enableListen      = false;
 *   mscanConfig.busoffrecMode     = kMSCAN_BusoffrecAuto;
 *   mscanConfig.filterConfig.filterMode = kMSCAN_Filter32Bit;
 *   MSCAN_Init(MSCAN, &mscanConfig, 8000000UL);
 *   @endcode
 *
 * @param base MsCAN peripheral base address.
 * @param config Pointer to the user-defined configuration structure.
 * @param sourceClock_Hz MsCAN Protocol Engine clock source frequency in Hz.
 */
void MSCAN_Init(MSCAN_Type *base, const mscan_config_t *config, uint32_t sourceClock_Hz);

/*!
 * @brief De-initializes a MsCAN instance.
 *
 * This function disables the MsCAN module clock and sets all register values
 * to the reset value.
 *
 * @param base MsCAN peripheral base address.
 */
void MSCAN_Deinit(MSCAN_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the MsCAN configuration structure to default values.
 *
 * @param config Pointer to the MsCAN configuration structure.
 */
void MSCAN_GetDefaultConfig(mscan_config_t *config);

/* @} */

/*!
 * @name Configuration.
 * @{
 */

/*!
 * @brief Get the transmit buffer empty status.
 *
 * This flag indicates that the associated transmit message buffer is empty.
 *
 * @param base MsCAN peripheral base address.
 */
static inline uint8_t MSCAN_GetTxBufferEmptyFlag(MSCAN_Type *base)
{
    return base->CANTFLG & MSCAN_CANTFLG_TXE_MASK;
}

/*!
 * @brief The selection of the actual transmit message buffer.
 *
 * To get the next available transmit buffer, read the CANTFLG
 * register and write its value back into the CANTBSEL register.
 *
 * @param base MsCAN peripheral base address.
 * @param txBuf The value read from CANTFLG.
 */
static inline void MSCAN_TxBufferSelect(MSCAN_Type *base, uint8_t txBuf)
{
    base->CANTBSEL = MSCAN_CANTBSEL_TX(txBuf);
}

/*!
 * @brief Get the actual transmit message buffer.
 *
 * After write TFLG value back into the CANTBSEL register, read again CANBSEL
 * to get the actual trasnsmit message buffer.
 *
 * @param base MsCAN peripheral base address.
 */
static inline uint8_t MSCAN_GetTxBufferSelect(MSCAN_Type *base)
{
    return base->CANTBSEL & MSCAN_CANTBSEL_TX_MASK;
}

/*!
 * @brief Clear TFLG to schedule for transmission.
 *
 * The CPU must clear the flag after a message is set up in the
 * transmit buffer and is due for transmission.
 *
 * @param base MsCAN peripheral base address.
 * @param txBuf Message buffer(s) to be cleared.
 */
static inline void MSCAN_TxBufferLaunch(MSCAN_Type *base, uint8_t txBuf)
{
    base->CANTFLG = MSCAN_CANTFLG_TXE_MASK & txBuf;
}

/*!
 * @brief Get Tx buffer status flag.
 *
 * The bit is set after successful transmission.
 *
 * @param base MsCAN peripheral base address.
 * @param mask Message buffer(s) mask.
 */
static inline uint8_t MSCAN_GetTxBufferStatusFlags(MSCAN_Type *base, uint8_t mask)
{
    return base->CANTFLG & mask;
}

/*!
 * @brief Check Receive Buffer Full Flag.
 *
 * RXF is set by the MSCAN when a new message is shifted in the receiver FIFO.
 * This flag indicates whether the shifted buffer is loaded with a correctly received message.
 *
 * @param base MsCAN peripheral base address.
 */
static inline uint8_t MSCAN_GetRxBufferFullFlag(MSCAN_Type *base)
{
    return base->CANRFLG & MSCAN_CANRFLG_RXF_MASK;
}

/*!
 * @brief Clear Receive buffer Full flag.
 *
 * After the CPU has read that message from the RxFG buffer in the receiver FIFO
 * The RXF flag must be cleared to release the buffer.
 *
 * @param base MsCAN peripheral base address.
 */
static inline void MSCAN_ClearRxBufferFullFlag(MSCAN_Type *base)
{
    base->CANRFLG |= MSCAN_CANRFLG_RXF_MASK;
}

static inline uint8_t MSCAN_ReadRIDR0(MSCAN_Type *base)
{
    return base->REIDR0;
}

static inline uint8_t MSCAN_ReadRIDR1(MSCAN_Type *base)
{
    return base->REIDR1;
}

static inline uint8_t MSCAN_ReadRIDR2(MSCAN_Type *base)
{
    return base->REIDR2;
}

static inline uint8_t MSCAN_ReadRIDR3(MSCAN_Type *base)
{
    return base->REIDR3;
}

static inline void MSCAN_WriteTIDR0(MSCAN_Type *base, uint8_t id)
{
    base->TEIDR0 = id;
}

static inline void MSCAN_WriteTIDR1(MSCAN_Type *base, uint8_t id)
{
    base->TEIDR1 = id;
}

static inline void MSCAN_WriteTIDR2(MSCAN_Type *base, uint8_t id)
{
    base->TEIDR2 = id;
}

static inline void MSCAN_WriteTIDR3(MSCAN_Type *base, uint8_t id)
{
    base->TEIDR3 = id;
}

static inline void MSCAN_SetIDFilterMode(MSCAN_Type *base, mscan_id_filter_mode_t mode)
{
    base->CANIDAC |= MSCAN_CANIDAC_IDAM((uint8_t)mode);
}

static inline void MSCAN_WriteIDAR0(MSCAN_Type *base, uint8_t *pID)
{
    base->CANIDAR_BANK_1[0] = pID[3];
    base->CANIDAR_BANK_1[1] = pID[2];
    base->CANIDAR_BANK_1[2] = pID[1];
    base->CANIDAR_BANK_1[3] = pID[0];
}

static inline void MSCAN_WriteIDAR1(MSCAN_Type *base, uint8_t *pID)
{
    base->CANIDAR_BANK_2[0] = pID[3];
    base->CANIDAR_BANK_2[1] = pID[2];
    base->CANIDAR_BANK_2[2] = pID[1];
    base->CANIDAR_BANK_2[3] = pID[0];
}

static inline void MSCAN_WriteIDMR0(MSCAN_Type *base, uint8_t *pID)
{
    base->CANIDMR_BANK_1[0] = pID[3];
    base->CANIDMR_BANK_1[1] = pID[2];
    base->CANIDMR_BANK_1[2] = pID[1];
    base->CANIDMR_BANK_1[3] = pID[0];
}

static inline void MSCAN_WriteIDMR1(MSCAN_Type *base, uint8_t *pID)
{
    base->CANIDMR_BANK_2[0] = pID[3];
    base->CANIDMR_BANK_2[1] = pID[2];
    base->CANIDMR_BANK_2[2] = pID[1];
    base->CANIDMR_BANK_2[3] = pID[0];
}

/*!
 * @brief Sets the MsCAN protocol timing characteristic.
 *
 * This function gives user settings to CAN bus timing characteristic.
 * The function is for an experienced user. For less experienced users, call
 * the MSCAN_Init() and fill the baud rate field with a desired value.
 * This provides the default timing characteristics to the module.
 *
 * Note that calling MSCAN_SetTimingConfig() overrides the baud rate set
 * in MSCAN_Init().
 *
 * @param base MsCAN peripheral base address.
 * @param config Pointer to the timing configuration structure.
 */
void MSCAN_SetTimingConfig(MSCAN_Type *base, const mscan_timing_config_t *config);

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the MsCAN Tx buffer empty flags.
 *
 * This function gets MsCAN Tx buffer empty flags. It's returned as the
 * value of the enumerators @ref _mscan_tx_buffer_empty_flag.
 *
 * @param base MsCAN peripheral base address.
 * @return Tx buffer empty flags in the _mscan_tx_buffer_empty_flag.
 */
static inline uint8_t MSCAN_GetTxBufEmptyFlags(MSCAN_Type *base)
{
    return base->CANTFLG & MSCAN_CANTFLG_TXE_MASK;
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables MsCAN Transmitter interrupts according to the provided mask.
 *
 * This function enables the MsCAN Tx empty interrupts according to the mask.
 *
 * @param base MsCAN peripheral base address.
 * @param mask The Tx interrupts mask to enable.
 */
static inline void MSCAN_EnableTxInterrupts(MSCAN_Type *base, uint8_t mask)
{
    base->CANTIER |= mask;
}

/*!
 * @brief Disables MsCAN Transmitter interrupts according to the provided mask.
 *
 * This function disables the MsCAN Tx emtpy interrupts according to the mask.
 *
 * @param base MsCAN peripheral base address.
 * @param mask The Tx interrupts mask to disable.
 */
static inline void MSCAN_DisableTxInterrupts(MSCAN_Type *base, uint8_t mask)
{
    base->CANTIER &= ~mask;
}

/*!
 * @brief Enables MsCAN Receiver interrupts according to the provided mask.
 *
 * This function enables the MsCAN Rx interrupts according to the provided mask
 * which is a logical OR of enumeration members, see @ref _mscan_interrupt_enable.
 *
 * @param base MsCAN peripheral base address.
 * @param mask The interrupts to enable. Logical OR of @ref _mscan_interrupt_enable.
 */
static inline void MSCAN_EnableRxInterrupts(MSCAN_Type *base, uint8_t mask)
{
    base->CANRIER |= mask;
}

/*!
 * @brief Disables MsCAN Receiver interrupts according to the provided mask.
 *
 * This function disables the MsCAN Rx interrupts according to the provided mask
 * which is a logical OR of enumeration members, see @ref _mscan_interrupt_enable.
 *
 * @param base MsCAN peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _mscan_interrupt_enable.
 */
static inline void MSCAN_DisableRxInterrupts(MSCAN_Type *base, uint8_t mask)
{
    base->CANRIER &= ~mask;
}

/*!
 * @brief Abort MsCAN Tx request.
 *
 * This function allows abort request of queued messages.
 *
 * @param base MsCAN peripheral base address.
 * @param mask The Tx mask to abort.
 */
static inline void MSCAN_AbortTxRequest(MSCAN_Type *base, uint8_t mask)
{
    base->CANTARQ |= mask;
}

/* @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Enables or disables the MsCAN module operation.
 *
 * This function enables or disables the MsCAN module.
 *
 * @param base MsCAN base pointer.
 * @param enable true to enable, false to disable.
 */
static inline void MSCAN_Enable(MSCAN_Type *base, bool enable)
{
    if (enable)
    {
        base->CANCTL1 |= MSCAN_CANCTL1_CANE_MASK;
    }
    else
    {
        base->CANCTL1 &= ~((uint8_t)MSCAN_CANCTL1_CANE_MASK);
    }
}

/*!
 * @brief Writes a MsCAN Message to the Transmit Message Buffer.
 *
 * This function writes a CAN Message to the specified Transmit Message Buffer
 * and changes the Message Buffer state to start CAN Message transmit. After
 * that the function returns immediately.
 *
 * @param base MsCAN peripheral base address.
 * @param pTxFrame Pointer to CAN message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_WriteTxMb(MSCAN_Type *base, mscan_frame_t *pTxFrame);

/*!
 * @brief Reads a MsCAN Message from Receive Message Buffer.
 *
 * This function reads a CAN message from a specified Receive Message Buffer.
 * The function fills a receive CAN message frame structure with
 * just received data and activates the Message Buffer again.
 * The function returns immediately.
 *
 * @param base MsCAN peripheral base address.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * @retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t MSCAN_ReadRxMb(MSCAN_Type *base, mscan_frame_t *pRxFrame);

/* @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the MsCAN handle.
 *
 * This function initializes the MsCAN handle, which can be used for other MsCAN
 * transactional APIs. Usually, for a specified MsCAN instance,
 * call this API once to get the initialized handle.
 *
 * @param base MsCAN peripheral base address.
 * @param handle MsCAN handle pointer.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 */
void MSCAN_TransferCreateHandle(MSCAN_Type *base,
                                mscan_handle_t *handle,
                                mscan_transfer_callback_t callback,
                                void *userData);

/*!
 * @brief Performs a polling send transaction on the CAN bus.
 *
 * Note that a transfer handle does not need to be created before calling this API.
 *
 * @param base MsCAN peripheral base pointer.
 * @param pTxFrame Pointer to CAN message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_TransferSendBlocking(MSCAN_Type *base, mscan_frame_t *pTxFrame);

/*!
 * @brief Performs a polling receive transaction on the CAN bus.
 *
 * Note that a transfer handle does not need to be created before calling this API.
 *
 * @param base MsCAN peripheral base pointer.
 * @param pRxFrame Pointer to CAN message frame to be received.
 * @retval kStatus_Success - Read Rx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MSCAN_TransferReceiveBlocking(MSCAN_Type *base, mscan_frame_t *pRxFrame);

/*!
 * @brief Sends a message using IRQ.
 *
 * This function sends a message using IRQ. This is a non-blocking function, which returns
 * right away. When messages have been sent out, the send callback function is called.
 *
 * @param base MsCAN peripheral base address.
 * @param handle MsCAN handle pointer.
 * @param xfer MsCAN Message Buffer transfer structure. See the #mscan_mb_transfer_t.
 * @retval kStatus_Success        Start Tx Message Buffer sending process successfully.
 * @retval kStatus_Fail           Write Tx Message Buffer failed.
 */
status_t MSCAN_TransferSendNonBlocking(MSCAN_Type *base, mscan_handle_t *handle, mscan_mb_transfer_t *xfer);

/*!
 * @brief Receives a message using IRQ.
 *
 * This function receives a message using IRQ. This is non-blocking function, which returns
 * right away. When the message has been received, the receive callback function is called.
 *
 * @param base MsCAN peripheral base address.
 * @param handle MsCAN handle pointer.
 * @param xfer MsCAN Message Buffer transfer structure. See the #mscan_mb_transfer_t.
 * @retval kStatus_Success        - Start Rx Message Buffer receiving process successfully.
 * @retval kStatus_MSCAN_RxBusy - Rx Message Buffer is in use.
 */
status_t MSCAN_TransferReceiveNonBlocking(MSCAN_Type *base, mscan_handle_t *handle, mscan_mb_transfer_t *xfer);

/*!
 * @brief Aborts the interrupt driven message send process.
 *
 * This function aborts the interrupt driven message send process.
 *
 * @param base MsCAN peripheral base address.
 * @param handle MsCAN handle pointer.
 * @param mask The MsCAN Tx Message Buffer mask.
 */
void MSCAN_TransferAbortSend(MSCAN_Type *base, mscan_handle_t *handle, uint8_t mask);

/*!
 * @brief Aborts the interrupt driven message receive process.
 *
 * This function aborts the interrupt driven message receive process.
 *
 * @param base MsCAN peripheral base address.
 * @param handle MsCAN handle pointer.
 * @param mask The MsCAN Rx Message Buffer mask.
 */
void MSCAN_TransferAbortReceive(MSCAN_Type *base, mscan_handle_t *handle, uint8_t mask);

/*!
 * @brief MSCAN IRQ handle function.
 *
 * This function handles the MSCAN Error, the Message Buffer, and the Rx FIFO IRQ request.
 *
 * @param base MSCAN peripheral base address.
 * @param handle MSCAN handle pointer.
 */
void MSCAN_TransferHandleIRQ(MSCAN_Type *base, mscan_handle_t *handle);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_MSCAN_H_ */
