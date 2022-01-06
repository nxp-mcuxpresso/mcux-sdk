/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_QSPI_H_
#define _FSL_QSPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup qspi_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief QSPI driver version 2.2.3. */
#define FSL_QSPI_DRIVER_VERSION (MAKE_VERSION(2, 2, 3))
/*@}*/

/*! @brief Macro functions for LUT table */
#define QSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                                        \
    (QuadSPI_LUT_INSTR0(cmd0) | QuadSPI_LUT_PAD0(pad0) | QuadSPI_LUT_OPRND0(op0) | QuadSPI_LUT_INSTR1(cmd1) | \
     QuadSPI_LUT_PAD1(pad1) | QuadSPI_LUT_OPRND1(op1))

/*! @brief Macro for QSPI LUT command */
#define QSPI_CMD        (0x1U)
#define QSPI_ADDR       (0x2U)
#define QSPI_DUMMY      (0x3U)
#define QSPI_MODE       (0x4U)
#define QSPI_MODE2      (0x5U)
#define QSPI_MODE4      (0x6U)
#define QSPI_READ       (0x7U)
#define QSPI_WRITE      (0x8U)
#define QSPI_JMP_ON_CS  (0x9U)
#define QSPI_ADDR_DDR   (0xAU)
#define QSPI_MODE_DDR   (0xBU)
#define QSPI_MODE2_DDR  (0xCU)
#define QSPI_MODE4_DDR  (0xDU)
#define QSPI_READ_DDR   (0xEU)
#define QSPI_WRITE_DDR  (0xFU)
#define QSPI_DATA_LEARN (0x10U)
#define QSPI_CMD_DDR    (0x11U)
#define QSPI_CADDR      (0x12U)
#define QSPI_CADDR_DDR  (0x13U)
#define QSPI_STOP       (0x0U)

/*! @brief Macro for QSPI PAD */
#define QSPI_PAD_1 (0x0U)
#define QSPI_PAD_2 (0x1U)
#define QSPI_PAD_4 (0x2U)
#define QSPI_PAD_8 (0x3U)

/*! @brief Status structure of QSPI.*/
enum
{
    kStatus_QSPI_Idle  = MAKE_STATUS(kStatusGroup_QSPI, 0), /*!< QSPI is in idle state  */
    kStatus_QSPI_Busy  = MAKE_STATUS(kStatusGroup_QSPI, 1), /*!< QSPI is busy */
    kStatus_QSPI_Error = MAKE_STATUS(kStatusGroup_QSPI, 2), /*!< Error occurred during QSPI transfer */
};

/*! @brief QSPI read data area, from IP FIFO or AHB buffer.*/
typedef enum _qspi_read_area
{
    kQSPI_ReadAHB = 0x0U, /*!< QSPI read from AHB buffer. */
    kQSPI_ReadIP          /*!< QSPI read from IP FIFO. */
} qspi_read_area_t;

/*! @brief QSPI command sequence type */
typedef enum _qspi_command_seq
{
    kQSPI_IPSeq     = QuadSPI_SPTRCLR_IPPTRC_MASK,                              /*!< IP command sequence */
    kQSPI_BufferSeq = QuadSPI_SPTRCLR_BFPTRC_MASK,                              /*!< Buffer command sequence */
    kQSPI_AllSeq    = QuadSPI_SPTRCLR_IPPTRC_MASK | QuadSPI_SPTRCLR_BFPTRC_MASK /* All command sequence */
} qspi_command_seq_t;

/*! @brief QSPI buffer type */
typedef enum _qspi_fifo
{
    kQSPI_TxFifo  = QuadSPI_MCR_CLR_TXF_MASK,                           /*!< QSPI Tx FIFO */
    kQSPI_RxFifo  = QuadSPI_MCR_CLR_RXF_MASK,                           /*!< QSPI Rx FIFO */
    kQSPI_AllFifo = QuadSPI_MCR_CLR_TXF_MASK | QuadSPI_MCR_CLR_RXF_MASK /*!< QSPI all FIFO, including Tx and Rx */
} qspi_fifo_t;

/*! @brief QSPI transfer endianess*/
typedef enum _qspi_endianness
{
    kQSPI_64BigEndian = 0x0U, /*!< 64 bits big endian */
    kQSPI_32LittleEndian,     /*!< 32 bit little endian */
    kQSPI_32BigEndian,        /*!< 32 bit big endian */
    kQSPI_64LittleEndian      /*!< 64 bit little endian */
} qspi_endianness_t;

/*! @brief QSPI error flags */
enum _qspi_error_flags
{
    kQSPI_DataLearningFail   = (int)QuadSPI_FR_DLPFF_MASK, /*!< Data learning pattern failure flag */
    kQSPI_TxBufferFill       = QuadSPI_FR_TBFF_MASK,       /*!< Tx buffer fill flag */
    kQSPI_TxBufferUnderrun   = QuadSPI_FR_TBUF_MASK,       /*!< Tx buffer underrun flag */
    kQSPI_IllegalInstruction = QuadSPI_FR_ILLINE_MASK,     /*!< Illegal instruction error flag */
    kQSPI_RxBufferOverflow   = QuadSPI_FR_RBOF_MASK,       /*!< Rx buffer overflow flag */
    kQSPI_RxBufferDrain      = QuadSPI_FR_RBDF_MASK,       /*!< Rx buffer drain flag */
    kQSPI_AHBSequenceError   = QuadSPI_FR_ABSEF_MASK,      /*!< AHB sequence error flag */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_AITEF) || (!FSL_FEATURE_QSPI_HAS_NO_AITEF)
    kQSPI_AHBIllegalTransaction = QuadSPI_FR_AITEF_MASK, /*!< AHB illegal transaction error flag */
#endif                                                   /* FSL_FEATURE_QSPI_HAS_NO_AITEF */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_AIBSEF) || (!FSL_FEATURE_QSPI_HAS_NO_AIBSEF)
    kQSPI_AHBIllegalBurstSize = QuadSPI_FR_AIBSEF_MASK, /*!< AHB illegal burst error flag */
#endif                                                  /* FSL_FEATURE_QSPI_HAS_NO_AIBSEF */
    kQSPI_AHBBufferOverflow = QuadSPI_FR_ABOF_MASK,     /*!< AHB buffer overflow flag */
#if defined(FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR) && (FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR)
    kQSPI_IPCommandUsageError = QuadSPI_FR_IUEF_MASK,              /*!< IP command usage error flag */
#endif                                                             /* FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR */
    kQSPI_IPCommandTriggerDuringAHBAccess = QuadSPI_FR_IPAEF_MASK, /*!< IP command trigger during AHB access error */
    kQSPI_IPCommandTriggerDuringIPAccess  = QuadSPI_FR_IPIEF_MASK, /*!< IP command trigger cannot be executed */
    kQSPI_IPCommandTriggerDuringAHBGrant  = QuadSPI_FR_IPGEF_MASK, /*!< IP command trigger during AHB grant error */
    kQSPI_IPCommandTransactionFinished    = QuadSPI_FR_TFF_MASK,   /*!< IP command transaction finished flag */
    kQSPI_FlagAll                         = (int)0x8C83F8D1U       /*!< All error flag */
};

/*! @brief QSPI state bit */
enum _qspi_flags
{
    kQSPI_DataLearningSamplePoint = (int)QuadSPI_SR_DLPSMP_MASK, /*!< Data learning sample point */
    kQSPI_TxBufferFull            = QuadSPI_SR_TXFULL_MASK,      /*!< Tx buffer full flag */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_TXDMA) || (!FSL_FEATURE_QSPI_HAS_NO_TXDMA)
    kQSPI_TxDMA       = QuadSPI_SR_TXDMA_MASK,                 /*!< Tx DMA is requested or running */
    kQSPI_TxWatermark = QuadSPI_SR_TXWA_MASK,                  /*!< Tx buffer watermark available */
#endif                                                         /* FSL_FEATURE_QSPI_HAS_NO_TXDMA */
    kQSPI_TxBufferEnoughData        = QuadSPI_SR_TXEDA_MASK,   /*!< Tx buffer enough data available */
    kQSPI_RxDMA                     = QuadSPI_SR_RXDMA_MASK,   /*!< Rx DMA is requesting or running */
    kQSPI_RxBufferFull              = QuadSPI_SR_RXFULL_MASK,  /*!< Rx buffer full */
    kQSPI_RxWatermark               = QuadSPI_SR_RXWE_MASK,    /*!< Rx buffer watermark exceeded */
    kQSPI_AHB3BufferFull            = QuadSPI_SR_AHB3FUL_MASK, /*!< AHB buffer 3 full*/
    kQSPI_AHB2BufferFull            = QuadSPI_SR_AHB2FUL_MASK, /*!< AHB buffer 2 full */
    kQSPI_AHB1BufferFull            = QuadSPI_SR_AHB1FUL_MASK, /*!< AHB buffer 1 full */
    kQSPI_AHB0BufferFull            = QuadSPI_SR_AHB0FUL_MASK, /*!< AHB buffer 0 full */
    kQSPI_AHB3BufferNotEmpty        = QuadSPI_SR_AHB3NE_MASK,  /*!< AHB buffer 3 not empty */
    kQSPI_AHB2BufferNotEmpty        = QuadSPI_SR_AHB2NE_MASK,  /*!< AHB buffer 2 not empty */
    kQSPI_AHB1BufferNotEmpty        = QuadSPI_SR_AHB1NE_MASK,  /*!< AHB buffer 1 not empty */
    kQSPI_AHB0BufferNotEmpty        = QuadSPI_SR_AHB0NE_MASK,  /*!< AHB buffer 0 not empty */
    kQSPI_AHBTransactionPending     = QuadSPI_SR_AHBTRN_MASK,  /*!< AHB access transaction pending */
    kQSPI_AHBCommandPriorityGranted = QuadSPI_SR_AHBGNT_MASK,  /*!< AHB command priority granted */
    kQSPI_AHBAccess                 = QuadSPI_SR_AHB_ACC_MASK, /*!< AHB access */
    kQSPI_IPAccess                  = QuadSPI_SR_IP_ACC_MASK,  /*!< IP access */
    kQSPI_Busy                      = QuadSPI_SR_BUSY_MASK,    /*!< Module busy */
    kQSPI_StateAll                  = (int)0xEF897FE7U         /*!< All flags */
};

/*! @brief QSPI interrupt enable */
enum _qspi_interrupt_enable
{
    kQSPI_DataLearningFailInterruptEnable =
        (int)QuadSPI_RSER_DLPFIE_MASK, /*!< Data learning pattern failure interrupt enable */
    kQSPI_TxBufferFillInterruptEnable     = QuadSPI_RSER_TBFIE_MASK, /*!< Tx buffer fill interrupt enable */
    kQSPI_TxBufferUnderrunInterruptEnable = QuadSPI_RSER_TBUIE_MASK, /*!< Tx buffer underrun interrupt enable */
    kQSPI_IllegalInstructionInterruptEnable =
        QuadSPI_RSER_ILLINIE_MASK,                                    /*!< Illegal instruction error interrupt enable */
    kQSPI_RxBufferOverflowInterruptEnable = QuadSPI_RSER_RBOIE_MASK,  /*!< Rx buffer overflow interrupt enable */
    kQSPI_RxBufferDrainInterruptEnable    = QuadSPI_RSER_RBDIE_MASK,  /*!< Rx buffer drain interrupt enable */
    kQSPI_AHBSequenceErrorInterruptEnable = QuadSPI_RSER_ABSEIE_MASK, /*!< AHB sequence error interrupt enable */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_AITEF) || (!FSL_FEATURE_QSPI_HAS_NO_AITEF)
    kQSPI_AHBIllegalTransactionInterruptEnable =
        QuadSPI_RSER_AITIE_MASK, /*!< AHB illegal transaction error interrupt enable */
#endif                           /* FSL_FEATURE_QSPI_HAS_NO_AITEF */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_AIBSEF) || (!FSL_FEATURE_QSPI_HAS_NO_AIBSEF)
    kQSPI_AHBIllegalBurstSizeInterruptEnable =
        QuadSPI_RSER_AIBSIE_MASK,                                     /*!< AHB illegal burst error interrupt enable */
#endif                                                                /* FSL_FEATURE_QSPI_HAS_NO_AIBSEF */
    kQSPI_AHBBufferOverflowInterruptEnable = QuadSPI_RSER_ABOIE_MASK, /*!< AHB buffer overflow interrupt enable */
#if defined(FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR) && (FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR)
    kQSPI_IPCommandUsageErrorInterruptEnable = QuadSPI_RSER_IUEIE_MASK, /*!< IP command usage error interrupt enable */
#endif /* FSL_FEATURE_QSPI_HAS_IP_COMMAND_USAGE_ERROR */
    kQSPI_IPCommandTriggerDuringAHBAccessInterruptEnable =
        QuadSPI_RSER_IPAEIE_MASK, /*!< IP command trigger during AHB access error */
    kQSPI_IPCommandTriggerDuringIPAccessInterruptEnable =
        QuadSPI_RSER_IPIEIE_MASK, /*!< IP command trigger cannot be executed */
    kQSPI_IPCommandTriggerDuringAHBGrantInterruptEnable =
        QuadSPI_RSER_IPGEIE_MASK, /*!< IP command trigger during AHB grant error */
    kQSPI_IPCommandTransactionFinishedInterruptEnable =
        QuadSPI_RSER_TFIE_MASK,                 /*!< IP command transaction finished interrupt enable */
    kQSPI_AllInterruptEnable = (int)0x8C83F8D1U /*!< All error interrupt enable */
};

/*! @brief QSPI DMA request flag */
enum _qspi_dma_enable
{
#if !defined(FSL_FEATURE_QSPI_HAS_NO_TXDMA) || (!FSL_FEATURE_QSPI_HAS_NO_TXDMA)
    kQSPI_TxBufferFillDMAEnable = QuadSPI_RSER_TBFDE_MASK,  /*!< Tx buffer fill DMA */
#endif                                                      /* FSL_FEATURE_QSPI_HAS_NO_TXDMA */
    kQSPI_RxBufferDrainDMAEnable = QuadSPI_RSER_RBDDE_MASK, /*!< Rx buffer drain DMA */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_TXDMA) || (!FSL_FEATURE_QSPI_HAS_NO_TXDMA)
    kQSPI_AllDDMAEnable = QuadSPI_RSER_TBFDE_MASK | QuadSPI_RSER_RBDDE_MASK /*!< All DMA source */
#else
    kQSPI_AllDDMAEnable = QuadSPI_RSER_RBDDE_MASK /* All DMA source */
#endif /* FSL_FEATURE_QSPI_HAS_NO_TXDMA */
};

/*! @brief Phrase shift number for DQS mode. */
typedef enum _qspi_dqs_phrase_shift
{
    kQSPI_DQSNoPhraseShift = 0x0U, /*!< No phase shift */
    kQSPI_DQSPhraseShift45Degree,  /*!< Select 45 degree phase shift*/
    kQSPI_DQSPhraseShift90Degree,  /*!< Select 90 degree phase shift */
    kQSPI_DQSPhraseShift135Degree  /*!< Select 135 degree phase shift */
} qspi_dqs_phrase_shift_t;

/*! @brief Qspi read sampling option. */
typedef enum _qspi_dqs_read_sample_clock
{
    kQSPI_ReadSampleClkInternalLoopback   = 0x0U,      /*!< Read sample clock adopts internal loopback mode. */
    kQSPI_ReadSampleClkLoopbackFromDqsPad = 0x1U,      /*!< Dummy Read strobe generated by QSPI Controller
                                                             and loopback from DQS pad. */
    kQSPI_ReadSampleClkExternalInputFromDqsPad = 0x2U, /*!< Flash provided Read strobe and input from DQS pad. */
} qspi_dqs_read_sample_clock_t;

/*! @brief DQS configure features*/
typedef struct QspiDQSConfig
{
    uint32_t portADelayTapNum; /*!< Delay chain tap number selection for QSPI port A DQS */
#if defined(QuadSPI_SOCCR_DQS_IFB_DELAY_CHAIN_SEL_MASK)
    uint32_t portBDelayTapNum; /*!< Delay chain tap number selection for QSPI port B DQS*/
#endif
    qspi_dqs_phrase_shift_t shift;              /*!< Phase shift for internal DQS generation */
    qspi_dqs_read_sample_clock_t rxSampleClock; /*!< Read sample clock for Dqs. */
    bool enableDQSClkInverse;                   /*!< Enable inverse clock for internal DQS generation */
} qspi_dqs_config_t;

/*! @brief Flash timing configuration. */
typedef struct QspiFlashTiming
{
    uint32_t dataHoldTime; /*!< Serial flash data in hold time */
    uint32_t CSHoldTime;   /*!< Serial flash CS hold time in terms of serial flash clock cycles */
    uint32_t CSSetupTime;  /*!< Serial flash CS setup time in terms of serial flash clock cycles */
} qspi_flash_timing_t;

/*! @brief QSPI configuration structure*/
typedef struct QspiConfig
{
    uint32_t clockSource;                                       /*!< Clock source for QSPI module */
    uint32_t baudRate;                                          /*!< Serial flash clock baud rate */
    uint8_t txWatermark;                                        /*!< QSPI transmit watermark value */
    uint8_t rxWatermark;                                        /*!< QSPI receive watermark value. */
    uint32_t AHBbufferSize[FSL_FEATURE_QSPI_AHB_BUFFER_COUNT];  /*!< AHB buffer size. */
    uint8_t AHBbufferMaster[FSL_FEATURE_QSPI_AHB_BUFFER_COUNT]; /*!< AHB buffer master.  */
    bool enableAHBbuffer3AllMaster;                             /*!< Is AHB buffer3 for all master.*/
    qspi_read_area_t area;                                      /*!< Which area Rx data readout */
    bool enableQspi;                                            /*!< Enable QSPI after initialization */
} qspi_config_t;

/*! @brief External flash configuration items*/
typedef struct _qspi_flash_config
{
    uint32_t flashA1Size; /*!< Flash A1 size */
    uint32_t flashA2Size; /*!< Flash A2 size */
#if defined(FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE) && (FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE)
    uint32_t flashB1Size;                             /*!< Flash B1 size */
    uint32_t flashB2Size;                             /*!< Flash B2 size */
#endif                                                /* FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE */
    uint32_t lookuptable[FSL_FEATURE_QSPI_LUT_DEPTH]; /*!< Flash command in LUT */
#if !defined(FSL_FEATURE_QSPI_HAS_NO_TDH) || (!FSL_FEATURE_QSPI_HAS_NO_TDH)
    uint32_t dataHoldTime;    /*!< Data line hold time. */
#endif                        /* FSL_FEATURE_QSPI_HAS_NO_TDH */
    uint32_t CSHoldTime;      /*!< CS line hold time */
    uint32_t CSSetupTime;     /*!< CS line setup time*/
    uint32_t cloumnspace;     /*!< Column space size */
    uint32_t dataLearnValue;  /*!< Data Learn value if enable data learn */
    qspi_endianness_t endian; /*!< Flash data endianess. */
    bool enableWordAddress;   /*!< If enable word address.*/
} qspi_flash_config_t;

/*! @brief Transfer structure for QSPI */
typedef struct _qspi_transfer
{
    uint32_t *data;  /*!< Pointer to data to transmit */
    size_t dataSize; /*!< Bytes to be transmit */
} qspi_transfer_t;

/*! @brief 16-bit access reg for IPCR register */
typedef struct _ip_command_config
{
    union
    {
        __IO uint32_t IPCR; /*!< IP Configuration Register */
        struct
        {
            __IO uint16_t IDATZ;     /*!< 16-bit access for IDATZ field in IPCR register */
            __IO uint8_t RESERVED_0; /*!< 8-bit access for RESERVED_0 field in IPCR register */
            __IO uint8_t SEQID;      /*!< 8-bit access for SEQID field in IPCR register */
        } BITFIELD;
    } IPCR_REG;
} ip_command_config_t;

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
 * @brief Get the instance number for QSPI.
 *
 * @param base QSPI base pointer.
 */
uint32_t QSPI_GetInstance(QuadSPI_Type *base);

/*!
 * @brief Initializes the QSPI module and internal state.
 *
 * This function enables the clock for QSPI and also configures the QSPI with the
 * input configure parameters. Users should call this function before any QSPI operations.
 *
 * @param base Pointer to QuadSPI Type.
 * @param config QSPI configure structure.
 * @param srcClock_Hz QSPI source clock frequency in Hz.
 */
void QSPI_Init(QuadSPI_Type *base, qspi_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief Gets default settings for QSPI.
 *
 * @param config QSPI configuration structure.
 */
void QSPI_GetDefaultQspiConfig(qspi_config_t *config);

/*!
 * @brief Deinitializes the QSPI module.
 *
 * Clears the QSPI state and  QSPI module registers.
 * @param base Pointer to QuadSPI Type.
 */
void QSPI_Deinit(QuadSPI_Type *base);

/*!
 * @brief Configures the serial flash parameter.
 *
 * This function configures the serial flash relevant parameters, such as the size, command, and so on.
 * The flash configuration value cannot have a default value. The user needs to configure it according to the
 * QSPI features.
 *
 * @param base Pointer to QuadSPI Type.
 * @param config Flash configuration parameters.
 */
void QSPI_SetFlashConfig(QuadSPI_Type *base, qspi_flash_config_t *config);

#if (!defined(FSL_FEATURE_QSPI_HAS_NO_SOCCR_REG)) || !FSL_FEATURE_QSPI_HAS_NO_SOCCR_REG
/*!
 * @brief Configures the serial flash DQS parameter.
 *
 * This function configures the serial flash DQS relevant parameters, such as the delay chain tap number, .
 * DQS shift phase, whether need to inverse and the rxc sample clock selection.
 *
 * @param base Pointer to QuadSPI Type.
 * @param config Dqs configuration parameters.
 */
void QSPI_SetDqsConfig(QuadSPI_Type *base, qspi_dqs_config_t *config);
#endif

/*!
 * @brief Software reset for the QSPI logic.
 *
 * This function sets the software reset flags for both AHB and buffer domain and
 * resets both AHB buffer and also IP FIFOs.
 *
 * @param base Pointer to QuadSPI Type.
 */
void QSPI_SoftwareReset(QuadSPI_Type *base);

/*!
 * @brief Enables or disables the QSPI module.
 *
 * @param base Pointer to QuadSPI Type.
 * @param enable True means enable QSPI, false means disable.
 */
static inline void QSPI_Enable(QuadSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR &= ~QuadSPI_MCR_MDIS_MASK;
    }
    else
    {
        base->MCR |= QuadSPI_MCR_MDIS_MASK;
    }
}

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the state value of QSPI.
 *
 * @param base Pointer to QuadSPI Type.
 * @return status flag, use status flag to AND #_qspi_flags could get the related status.
 */
static inline uint32_t QSPI_GetStatusFlags(QuadSPI_Type *base)
{
    return base->SR;
}

/*!
 * @brief Gets QSPI error status flags.
 *
 * @param base Pointer to QuadSPI Type.
 * @return status flag, use status flag to AND #_qspi_error_flags could get the related status.
 */
static inline uint32_t QSPI_GetErrorStatusFlags(QuadSPI_Type *base)
{
    return base->FR;
}

/*! @brief Clears the QSPI error flags.
 *
 * @param base Pointer to QuadSPI Type.
 * @param mask Which kind of QSPI flags to be cleared, a combination of _qspi_error_flags.
 */
static inline void QSPI_ClearErrorFlag(QuadSPI_Type *base, uint32_t mask)
{
    base->FR = mask;
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the QSPI interrupts.
 *
 * @param base Pointer to QuadSPI Type.
 * @param mask QSPI interrupt source.
 */
static inline void QSPI_EnableInterrupts(QuadSPI_Type *base, uint32_t mask)
{
    base->RSER |= mask;
}

/*!
 * @brief Disables the QSPI interrupts.
 *
 * @param base Pointer to QuadSPI Type.
 * @param mask QSPI interrupt source.
 */
static inline void QSPI_DisableInterrupts(QuadSPI_Type *base, uint32_t mask)
{
    base->RSER &= ~mask;
}

/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enables the QSPI DMA source.
 *
 * @param base Pointer to QuadSPI Type.
 * @param mask QSPI DMA source.
 * @param enable True means enable DMA, false means disable.
 */
static inline void QSPI_EnableDMA(QuadSPI_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->RSER |= mask;
    }
    else
    {
        base->RSER &= ~mask;
    }
}

/*!
 * @brief Gets the Tx data register address. It is used for DMA operation.
 *
 * @param base Pointer to QuadSPI Type.
 * @return QSPI Tx data register address.
 */
static inline uint32_t QSPI_GetTxDataRegisterAddress(QuadSPI_Type *base)
{
    return (uint32_t)(&base->TBDR);
}

/*!
 * @brief Gets the Rx data register address used for DMA operation.
 *
 * This function returns the Rx data register address or Rx buffer address
 * according to the Rx read area settings.
 *
 * @param base Pointer to QuadSPI Type.
 * @return QSPI Rx data register address.
 */
uint32_t QSPI_GetRxDataRegisterAddress(QuadSPI_Type *base);

/* @} */

/*!
 * @name Bus Operations
 * @{
 */

/*! @brief Sets the IP command address.
 *
 * @param base Pointer to QuadSPI Type.
 * @param addr IP command address.
 */
static inline void QSPI_SetIPCommandAddress(QuadSPI_Type *base, uint32_t addr)
{
    base->SFAR = addr;
}

/*! @brief Sets the IP command size.
 *
 * @param base Pointer to QuadSPI Type.
 * @param size IP command size.
 */
static inline void QSPI_SetIPCommandSize(QuadSPI_Type *base, uint32_t size)
{
    union
    {
        volatile uint32_t *commandRegBase;
        ip_command_config_t *commandConfigPtr;
    } command;
    command.commandRegBase             = &(base->IPCR);
    ip_command_config_t *ipCommand     = command.commandConfigPtr;
    size                               = QuadSPI_IPCR_IDATSZ(size);
    ipCommand->IPCR_REG.BITFIELD.IDATZ = (uint16_t)size;
}

/*! @brief Executes IP commands located in LUT table.
 *
 * @param base Pointer to QuadSPI Type.
 * @param index IP command located in which LUT table index.
 */
void QSPI_ExecuteIPCommand(QuadSPI_Type *base, uint32_t index);

/*! @brief Executes AHB commands located in LUT table.
 *
 * @param base Pointer to QuadSPI Type.
 * @param index AHB command located in which LUT table index.
 */
void QSPI_ExecuteAHBCommand(QuadSPI_Type *base, uint32_t index);

#if defined(FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE) && (FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE)
/*! @brief Enables/disables the QSPI IP command parallel mode.
 *
 * @param base Pointer to QuadSPI Type.
 * @param enable True means enable parallel mode, false means disable parallel mode.
 */
static inline void QSPI_EnableIPParallelMode(QuadSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->IPCR |= QuadSPI_IPCR_PAR_EN_MASK;
    }
    else
    {
        base->IPCR &= ~QuadSPI_IPCR_PAR_EN_MASK;
    }
}

/*! @brief Enables/disables the QSPI AHB command parallel mode.
 *
 * @param base Pointer to QuadSPI Type.
 * @param enable True means enable parallel mode, false means disable parallel mode.
 */
static inline void QSPI_EnableAHBParallelMode(QuadSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->BFGENCR |= QuadSPI_BFGENCR_PAR_EN_MASK;
    }
    else
    {
        base->BFGENCR &= ~QuadSPI_BFGENCR_PAR_EN_MASK;
    }
}
#endif /* FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE */

/*! @brief Updates the LUT table.
 *
 * @param base Pointer to QuadSPI Type.
 * @param index Which LUT index needs to be located. It should be an integer divided by 4.
 * @param cmd Command sequence array.
 */
void QSPI_UpdateLUT(QuadSPI_Type *base, uint32_t index, uint32_t *cmd);

/*! @brief Clears the QSPI FIFO logic.
 *
 * @param base Pointer to QuadSPI Type.
 * @param mask Which kind of QSPI FIFO to be cleared.
 */
static inline void QSPI_ClearFifo(QuadSPI_Type *base, uint32_t mask)
{
    base->MCR |= mask;
}

/*!@ brief Clears the command sequence for the IP/buffer command.
 *
 * This function can reset the command sequence.
 * @param base QSPI base address.
 * @param seq Which command sequence need to reset, IP command, buffer command or both.
 */
static inline void QSPI_ClearCommandSequence(QuadSPI_Type *base, qspi_command_seq_t seq)
{
    base->SPTRCLR = (uint32_t)seq;
}

/*!
 * @brief Enable or disable DDR mode.
 *
 * @param base QSPI base pointer
 * @param enable True means enable DDR mode, false means disable DDR mode.
 */
static inline void QSPI_EnableDDRMode(QuadSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR |= QuadSPI_MCR_DDR_EN_MASK;
    }
    else
    {
        base->MCR &= ~QuadSPI_MCR_DDR_EN_MASK;
    }
}

#if defined(FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC) && (FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC)

/*! @brief Clears the QSPI cache.
 *
 * @param base Pointer to QuadSPI Type.
 */
void QSPI_ClearCache(QuadSPI_Type *base);
#endif

/*!@ brief Set the RX buffer readout area.
 *
 * This function can set the RX buffer readout, from AHB bus or IP Bus.
 * @param base QSPI base address.
 * @param area QSPI Rx buffer readout area. AHB bus buffer or IP bus buffer.
 */
void QSPI_SetReadDataArea(QuadSPI_Type *base, qspi_read_area_t area);

/*!
 * @brief Sends a buffer of data bytes using a  blocking method.
 * @note This function blocks via polling until all bytes have been sent.
 * @param base QSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
void QSPI_WriteBlocking(QuadSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Writes data into FIFO.
 *
 * @param base QSPI base pointer
 * @param data The data bytes to send
 */
static inline void QSPI_WriteData(QuadSPI_Type *base, uint32_t data)
{
    base->TBDR = data;
}

/*!
 * @brief Receives a buffer of data bytes using a blocking method.
 * @note This function blocks via polling until all bytes have been sent. Users shall notice that
 * this receive size shall not bigger than 64 bytes. As this interface is used to read flash status registers.
 * For flash contents read, please use AHB bus read, this is much more efficiency.
 *
 * @param base QSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to receive
 */
void QSPI_ReadBlocking(QuadSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Receives data from data FIFO.
 *
 * @param base QSPI base pointer
 * @return The data in the FIFO.
 */
uint32_t QSPI_ReadData(QuadSPI_Type *base);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Writes data to the QSPI transmit buffer.
 *
 * This function writes a continuous data to the QSPI transmit FIFO. This function is a block function
 * and can return only when finished. This function uses polling methods.
 *
 * @param base Pointer to QuadSPI Type.
 * @param xfer QSPI transfer structure.
 */
static inline void QSPI_TransferSendBlocking(QuadSPI_Type *base, qspi_transfer_t *xfer)
{
    QSPI_WriteBlocking(base, xfer->data, xfer->dataSize);
}

/*!
 * @brief Reads data from the QSPI receive buffer in polling way.
 *
 * This function reads continuous data from the QSPI receive buffer/FIFO. This function is a blocking
 * function and can return only when finished. This function uses polling methods. Users shall notice that
 * this receive size shall not bigger than 64 bytes. As this interface is used to read flash status registers.
 * For flash contents read, please use AHB bus read, this is much more efficiency.
 *
 * @param base Pointer to QuadSPI Type.
 * @param xfer QSPI transfer structure.
 */
static inline void QSPI_TransferReceiveBlocking(QuadSPI_Type *base, qspi_transfer_t *xfer)
{
    QSPI_ReadBlocking(base, xfer->data, xfer->dataSize);
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/* @}*/

#endif /* _FSL_QSPI_H_*/
