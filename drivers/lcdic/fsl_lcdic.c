/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdic.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdic"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Typedef for ISR. */
typedef void (*lcdic_isr_t)(uint32_t instance);

/* TRX command to send command without done interrupt. */
#define LCDIC_TRX_CMD_NO_DONE_INT (1UL << 31U)
/* TRX command to send command with done interrupt. */
#define LCDIC_TRX_CMD_WITH_DONE_INT ((1UL << 29U) | (1UL << 31U))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Short wait for LCDIC state reset.
 *
 * After clear or set LCDIC_EN, there should be delay longer than 4 LCDIC
 * functional clock.
 */
static void LCDIC_ResetStateDelay(void)
{
    /* clang-format off */
    __asm volatile(
        "    MOV    r0, %0              \n"
        "loop%=:                        \n"
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
        "    SUB    R0, R0, #1          \n"
#else
        "    SUBS   R0, R0, #1          \n"
#endif
        "    CMP    R0, #0              \n"
        "    BNE    loop%=              \n"
        ::"i" ( LCDIC_RESET_STATE_DELAY / 4U )
        : "r0");
    /* clang-format on */
}

/*!
 * @brief Wait TRX command done.
 *
 * @param base LCDIC peripheral base address.
 * @retval kStatus_Success Command done.
 * @retval kStatus_Timeout Timeout happened.
 */
static status_t LCDIC_WaitCmdComplete(LCDIC_Type *base);

/*!
 * @brief Handle send data array in IRQ.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
static void LCDIC_TransferHandleIRQSendArray(LCDIC_Type *base, lcdic_handle_t *lcdicHandle);

/*!
 * @brief Handle receive data array in IRQ.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
static void LCDIC_TransferHandleIRQReceiveArray(LCDIC_Type *base, lcdic_handle_t *lcdicHandle);

/*!
 * @brief LCDIC ISR.
 *
 * This function handles the reset sequence sent done interupt, and also calls
 * the transfer interupt handler to handle transfer interrupts.
 *
 * @param instance LCDIC peripheral instance.
 */
static void LCDIC_DriverISR(uint32_t instance);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to LCDIC bases for each instance. */
static LCDIC_Type *const s_lcdicBases[] = LCDIC_BASE_PTRS;

/*! @brief Array to map LCDIC instance number to IRQ number. */
static IRQn_Type const s_lcdicIRQ[] = LCDIC_IRQS;

/*! @brief Pointers to handles for each instance. */
static void *s_lcdicHandles[ARRAY_SIZE(s_lcdicBases)];

/*! @brief Pointers to handles for each instance. */
static lcdic_transfer_irq_handler_t s_lcdicIRQHandler[ARRAY_SIZE(s_lcdicBases)];

/* LCDIC ISR. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static lcdic_isr_t s_lcdicIsr = (lcdic_isr_t)DefaultISR;
#else
static lcdic_isr_t s_lcdicIsr = NULL;
#endif

/* LCDIC reset sequence sent done callback. */
static lcdic_reset_done_callback_t s_lcdicResetSendDoneCallback = NULL;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LCDIC clocks for each LCDIC submodule. */
static const clock_ip_name_t s_lcdicClocks[] = LCDIC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * brief Get the instance from the base address
 *
 * param base LCDIC peripheral base address
 * return The LCDIC module instance
 */
uint32_t LCDIC_GetInstance(LCDIC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdicBases); instance++)
    {
        if (s_lcdicBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdicBases));

    return instance;
}

/*
 * brief Get IRQn for specific instance.
 *
 * param instance LCDIC instance.
 * return The LCDIC IRQn.
 */
IRQn_Type LCDIC_GetIRQn(uint32_t instance)
{
    assert(instance < ARRAY_SIZE(s_lcdicIRQ));

    return s_lcdicIRQ[instance];
}

/*!
 * brief Initialize the LCDIC.
 *
 * This function initializes the LCDIC to work.
 *
 * param base LCDIC peripheral base address.
 *
 * retval kStatus_Success Initialize successfully.
 */
status_t LCDIC_Init(LCDIC_Type *base, const lcdic_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIC_GetInstance(base);
    CLOCK_EnableClock(s_lcdicClocks[instance]);
#endif

    base->CTRL = (uint32_t)config->mode | LCDIC_CTRL_DAT_ENDIAN(config->endian);

    base->FIFO_CTRL =
        LCDIC_FIFO_CTRL_RFIFO_THRES(config->rxThreshold) | LCDIC_FIFO_CTRL_TFIFO_THRES(config->txThreshold);

    base->TIMER_CTRL =
        LCDIC_TIMER_CTRL_TIMER_RATIO0(config->timerRatio0) | LCDIC_TIMER_CTRL_TIMER_RATIO1(config->timerRatio1);

    base->RST_CTRL =
        LCDIC_RST_CTRL_RST_POL(config->resetPolarity) | LCDIC_RST_CTRL_RST_SEQ_NUM(config->resetSequencePulseNum) |
        LCDIC_RST_CTRL_RST_SEQ(config->resetSequence) | LCDIC_RST_CTRL_RST_WIDTH(config->resetPulseWidth_Timer0);

    base->I8080_CTRL0 = (uint32_t)config->i8080CtrlFlags | LCDIC_I8080_CTRL0_TCSW(config->csWaitTime) |
                        LCDIC_I8080_CTRL0_TCSS(config->csSetupTime) | LCDIC_I8080_CTRL0_TCSH(config->csHoldTime) |
                        LCDIC_I8080_CTRL0_TDCS(config->dcSetupTime) | LCDIC_I8080_CTRL0_TDCH(config->dcHoldTime) |
                        LCDIC_I8080_CTRL0_TWDS(config->writeDataSetupTime) |
                        LCDIC_I8080_CTRL0_TWDH(config->writeDataHoldTime);

    base->I8080_CTRL1 = LCDIC_I8080_CTRL1_TWAW(config->writeEnableActiveWidth) |
                        LCDIC_I8080_CTRL1_TWIW(config->writeEnableInactiveWidth) |
                        LCDIC_I8080_CTRL1_TRAW(config->readEnableActiveWidth) |
                        LCDIC_I8080_CTRL1_TRIW(config->readEnableInactiveWidth);

    base->SPI_CTRL = config->spiCtrlFlags;

    base->TE_CTRL =
        LCDIC_TE_CTRL_TTEW(config->teSyncWaitTime_Timer1) | LCDIC_TE_CTRL_TE_TO(config->teTimeoutTime_Timer1);

    base->TO_CTRL = LCDIC_TO_CTRL_CMD_SHORT_TO(config->cmdShortTimeout_Timer0) |
                    LCDIC_TO_CTRL_CMD_LONG_TO(config->cmdLongTimeout_Timer1);

    LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_AllInterrupt);
    LCDIC_DisableInterrupts(base, (uint32_t)kLCDIC_AllInterrupt);

    /* Enable the module. */
    base->CTRL |= LCDIC_CTRL_LCDIC_EN_MASK;

    LCDIC_ResetStateDelay();

    return kStatus_Success;
}

/*!
 * brief De-initialize the LCDIC.
 *
 * This function disables the LCDIC peripheral clock.
 *
 * param base LCDIC peripheral base address.
 */
void LCDIC_Deinit(LCDIC_Type *base)
{
    /* Disable the module */
    base->CTRL = 0UL;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIC_GetInstance(base);
    CLOCK_DisableClock(s_lcdicClocks[instance]);
#endif
}

/*!
 * brief Get the default configuration.
 *
 * param config Pointer to the LCDIC configuration.
 */
void LCDIC_GetDefaultConfig(lcdic_config_t *config)
{
    assert(NULL != config);

    config->mode        = kLCDIC_3WireSPI;
    config->endian      = kLCDIC_BigEndian;
    config->rxThreshold = kLCDIC_RxThreshold0Word;
    config->txThreshold = kLCDIC_TxThreshold3Word;

    config->timerRatio0 = 8;
    config->timerRatio1 = 9;

    /* Reset signal. */
    config->resetPulseWidth_Timer0 = 20;
    config->resetSequence          = 0;
    config->resetSequencePulseNum  = 1;
    config->resetPolarity          = kLCDIC_ResetActiveLow;

    /* I8080 */
    config->i8080CtrlFlags = (uint8_t)kLCDIC_I8080_CsActiveLow | (uint8_t)kLCDIC_I8080_DcCmdLow |
                             (uint8_t)kLCDIC_I8080_RdActiveLow | (uint8_t)kLCDIC_I8080_WrActiveLow |
                             (uint8_t)kLCDIC_I8080_CsEnableIdleOff;

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

    /* SPI */
    config->spiCtrlFlags = (uint8_t)kLCDIC_SPI_MsbFirst | (uint8_t)kLCDIC_SPI_ClkActiveHigh |
                           (uint8_t)kLCDIC_SPI_ClkPhaseFirstEdge | (uint8_t)kLCDIC_SPI_DcCmdLow;

    /* TE. */
    config->teTimeoutTime_Timer1  = 16;
    config->teSyncWaitTime_Timer1 = 0;

    /* Command. */
    config->cmdShortTimeout_Timer0 = 1;
    config->cmdLongTimeout_Timer1  = 16;
}

/*
 * brief Set the callback called when reset sequence sent done.
 *
 * param callback The callback to set.
 */
void LCDIC_SetResetSequenceDoneCallback(lcdic_reset_done_callback_t callback)
{
    s_lcdicResetSendDoneCallback = callback;
    s_lcdicIsr                   = LCDIC_DriverISR;
}

/*
 * brief Write the TX FIFO using blocking way.
 *
 * This function waits for empty slot in TX FIFO and fill the data to TX FIFO.
 *
 * param base LCDIC peripheral base address.
 * param data Data to send, the data length must be dividable by 4.
 * param dataLen_Word Data length in word.
 * retval kStatus_Success Write successfully.
 * retval kStatus_Timeout Timeout happened.
 */
status_t LCDIC_WriteTxFifoBlocking(LCDIC_Type *base, const uint32_t *data, uint32_t dataLen_Word)
{
    assert(NULL != data);

    status_t status = kStatus_Success;
    uint32_t intStatus;

    while (dataLen_Word > 0u)
    {
        base->TFIFO_WDATA = *data;

        intStatus = LCDIC_GetInterruptRawStatus(base);

        if (0U != (((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt) & intStatus))
        {
            LCDIC_ClearInterruptStatus(base,
                                       ((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt));
            status = kStatus_Timeout;
            break;
        }

        if (0U != ((uint32_t)kLCDIC_TxOverflowInterrupt & intStatus))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_TxOverflowInterrupt);
        }
        else
        {
            data++;
            dataLen_Word--;
        }
    }

    return status;
}

/*
 * brief Read the RX FIFO using blocking way.
 *
 * This function waits for valid data in RX FIFO and read them.
 *
 * param base LCDIC peripheral base address.
 * param data Array for received data, the data length must be dividable by 4.
 * param dataLen_Word Data length in word.
 * retval kStatus_Success Read successfully.
 * retval kStatus_Timeout Timeout happened.
 */
status_t LCDIC_ReadRxFifoBlocking(LCDIC_Type *base, uint32_t *data, uint32_t dataLen_Word)
{
    assert(NULL != data);

    status_t status = kStatus_Success;
    uint32_t intStatus;

    while (dataLen_Word > 0u)
    {
        *data = base->RFIFO_RDATA;

        intStatus = LCDIC_GetInterruptRawStatus(base);

        if (0U != (((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt) & intStatus))
        {
            LCDIC_ClearInterruptStatus(base,
                                       (uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt);
            status = kStatus_Timeout;
            break;
        }

        if (0U != ((uint32_t)kLCDIC_RxUnderflowInterrupt & intStatus))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_RxUnderflowInterrupt);
        }
        else
        {
            data++;
            dataLen_Word--;
        }
    }

    return status;
}

/*
 * brief Get data from byte array, and fill to 4-byte word.
 *
 * LCDIC data registers only accept 4-byte data, but the user passed data might
 * be not 4-byte size aligned. This function is used to construct the unaligned
 * part to a word, to write to LCDIC register.
 *
 * param bytes The byte array.
 * param len Length of the byte array.
 * return The construct word.
 */
uint32_t LCDIC_FillByteToWord(const uint8_t *bytes, uint8_t len)
{
    uint32_t word = 0U;

    while ((len--) > 0u)
    {
        word <<= 8U;
        word |= bytes[len];
    }

    return word;
}

/*
 * brief Get data from 4-byte, and fill to byte array.
 *
 * LCDIC data registers only accept 4-byte data, but the user passed data might
 * be not 4-byte size aligned. This function is used to get desired bytes from
 * the word read from LCDIC register, and save to the user data array.
 *
 * param word Word data read from LCDIC register.
 * param bytes The byte array.
 * param len Length of the byte array.
 */
void LCDIC_ExtractByteFromWord(uint32_t word, uint8_t *bytes, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        bytes[i] = (uint8_t)word;
        word >>= 8U;
    }
}

/*
 * brief Wait TRX command done.
 *
 * param base LCDIC peripheral base address.
 * retval kStatus_Success Command done.
 * retval kStatus_Timeout Timeout happened.
 */
static status_t LCDIC_WaitCmdComplete(LCDIC_Type *base)
{
    status_t status;
    uint32_t intStat;

    while (true)
    {
        intStat = LCDIC_GetInterruptRawStatus(base);

        if (0U != (((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt) & intStat))
        {
            status = kStatus_Timeout;
            break;
        }

        if (0U != ((uint32_t)kLCDIC_CmdDoneInterrupt & intStat))
        {
            status = kStatus_Success;
            break;
        }
    }

    LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_CmdTimeoutInterrupt |
                                         (uint32_t)kLCDIC_TeTimeoutInterrupt);

    return status;
}

/*
 * brief Prepare the command sending.
 *
 * Fill the TRX command and command to TX FIFO, after calling this function, user
 * should wait for transfer done by checking status or IRQ.
 *
 * param base LCDIC peripheral base address.
 * param cmd Command to send.
 * retval kStatus_Success Operation successed.
 */
status_t LCDIC_PrepareSendCommand(LCDIC_Type *base, uint8_t cmd)
{
    LCDIC_ResetState(base);
    /*
     * The TX FIFO is empty, fill directly.
     */
    base->TFIFO_WDATA = LCDIC_TRX_CMD_WITH_DONE_INT;
    base->TFIFO_WDATA = cmd;

    return kStatus_Success;
}

/*
 * brief Prepare the repeat data sending.
 *
 * Fill the required data to TX FIFO, after calling this function, user
 * should wait for transfer done by checking status or IRQ.
 *
 * param base LCDIC peripheral base address.
 * param xfer Transfer structure.
 * retval kStatus_Success Operation successed.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareSendRepeatData(LCDIC_Type *base, const lcdic_repeat_tx_xfer_t *xfer)
{
    status_t status;
    lcdic_trx_cmd_t trxCmd = {0};

    if (0U == xfer->dataLen)
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        LCDIC_ResetState(base);

        /*
         * The TX FIFO is empty, fill directly.
         */
        base->TFIFO_WDATA = LCDIC_TRX_CMD_WITH_DONE_INT;
        base->TFIFO_WDATA = xfer->cmd;

        trxCmd.bits.trx              = kLCDIC_TX;
        trxCmd.bits.teSyncMode       = xfer->teSyncMode;
        trxCmd.bits.trxTimeoutMode   = xfer->trxTimeoutMode;
        trxCmd.bits.dataFormat       = xfer->dataFormat;
        trxCmd.bits.dataLen          = xfer->dataLen - 1U;
        trxCmd.bits.cmdOrData        = kLCDIC_Data;
        trxCmd.bits.enableCmdDoneInt = 1U;
        trxCmd.bits.useAutoRepeat    = 1U;

        /* Must wait previous command done. */
        (void)LCDIC_WaitCmdComplete(base);

        base->TFIFO_WDATA = trxCmd.u32;
        base->TFIFO_WDATA = xfer->txRepeatData;

        status = kStatus_Success;
    }

    return status;
}

/*
 * brief Prepare sending data array.
 *
 * Fill the required command data to TX FIFO, after calling this function, user
 * should fill the xfer->txData to TX FIFO based on FIFO status.
 *
 * param base LCDIC peripheral base address.
 * param xfer Transfer structure.
 * param xferSizeWordAligned The word size aligned part of the transfer data.
 * param xferSizeWordUnaligned The word size unaligned part of the transfer data.
 * param wordUnalignedData Word to save the word size unaligned data, it should
 * be sent after all word size aligned data write finished.
 * retval kStatus_Success Operation successed.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareSendDataArray(LCDIC_Type *base,
                                    const lcdic_tx_xfer_t *xfer,
                                    uint32_t *xferSizeWordAligned,
                                    uint8_t *xferSizeWordUnaligned,
                                    uint32_t *wordUnalignedData)
{
    status_t status;
    lcdic_trx_cmd_t trxCmd = {0};
    uint32_t dataLen       = xfer->dataLen;

    if (0u == dataLen)
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        LCDIC_ResetState(base);

        /*
         * Export some data information. If the data size is not 4-byte aligned,
         * the unaligned part will be saved as word in wordUnalignedData, and sent out at last.
         */
        *xferSizeWordAligned   = dataLen & ~0x03U;
        *xferSizeWordUnaligned = (uint8_t)dataLen & 0x03U;

        if (*xferSizeWordUnaligned != 0U)
        {
            *wordUnalignedData = LCDIC_FillByteToWord(xfer->txData + *xferSizeWordAligned, *xferSizeWordUnaligned);
        }

        /*
         * The TX FIFO is empty, fill directly.
         */

        /* Send command. */
        base->TFIFO_WDATA = LCDIC_TRX_CMD_WITH_DONE_INT;
        base->TFIFO_WDATA = xfer->cmd;

        /* trxCmd for data array. */
        trxCmd.bits.trx              = kLCDIC_TX;
        trxCmd.bits.teSyncMode       = xfer->teSyncMode;
        trxCmd.bits.trxTimeoutMode   = xfer->trxTimeoutMode;
        trxCmd.bits.dataFormat       = xfer->dataFormat;
        trxCmd.bits.dataLen          = dataLen - 1U;
        trxCmd.bits.cmdOrData        = kLCDIC_Data;
        trxCmd.bits.enableCmdDoneInt = 1U;

        /* Must wait previous command done. */
        (void)LCDIC_WaitCmdComplete(base);

        base->TFIFO_WDATA = trxCmd.u32;

        status = kStatus_Success;
    }

    return status;
}

/*
 * brief Prepare reading data array.
 *
 * Fill the required command data to TX FIFO, after calling this function, user
 * should read RX FIFO to xfer->rxData based on FIFO status.
 *
 * param base LCDIC peripheral base address.
 * param xfer Transfer structure.
 * param xferSizeWordAligned The word size aligned part of the transfer data.
 * param xferSizeWordUnaligned The word size unaligned part of the transfer data.
 * retval kStatus_Success Operation successed.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_PrepareReadDataArray(LCDIC_Type *base,
                                    const lcdic_rx_xfer_t *xfer,
                                    uint32_t *xferSizeWordAligned,
                                    uint8_t *xferSizeWordUnaligned)
{
    status_t status;
    lcdic_trx_cmd_t trxCmd = {0};
    uint32_t dataLen       = xfer->dataLen;

    if (0u == dataLen)
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        LCDIC_ResetState(base);

        /*
         * Export data information. If the data size is not 4-byte aligned,
         * the unaligned length will be saved xferSizeWordUnaligned.
         */
        *xferSizeWordAligned   = dataLen & ~0x03U;
        *xferSizeWordUnaligned = (uint8_t)dataLen & 0x03U;

        /*
         * The TX FIFO is empty, fill directly.
         */
        base->TFIFO_WDATA = LCDIC_TRX_CMD_WITH_DONE_INT;
        base->TFIFO_WDATA = xfer->cmd;

        trxCmd.bits.trx            = kLCDIC_TX;
        trxCmd.bits.dummyCount     = xfer->dummyCount;
        trxCmd.bits.trxTimeoutMode = xfer->trxTimeoutMode;
        trxCmd.bits.dataFormat     = xfer->dataFormat;
        trxCmd.bits.dataLen        = dataLen - 1U;
        trxCmd.bits.cmdOrData      = kLCDIC_Data;
        trxCmd.bits.trx            = kLCDIC_RX;

        /* Must wait previous command done. */
        (void)LCDIC_WaitCmdComplete(base);

        base->TFIFO_WDATA = trxCmd.u32;

        status = kStatus_Success;
    }

    return status;
}

/*
 * brief Send command using blocking way.
 *
 * This function sends out command and waits until send finished.
 *
 * param base LCDIC peripheral base address.
 * param cmd Command to send.
 * retval kStatus_Success Command sent successfully.
 */
status_t LCDIC_SendCommandBlocking(LCDIC_Type *base, uint8_t cmd)
{
    (void)LCDIC_PrepareSendCommand(base, cmd);
    return LCDIC_WaitCmdComplete(base);
}

/*
 * brief Send repeat data using blocking way.
 *
 * This function sends out command and the repeat data, then waits until
 * send finished or timeout happened.
 *
 * param base LCDIC peripheral base address.
 * param xfer Pointer to the transfer configuration.
 * retval kStatus_Success Sent successfully.
 * retval kStatus_Timeout Timeout happened.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_SendRepeatDataBlocking(LCDIC_Type *base, const lcdic_repeat_tx_xfer_t *xfer)
{
    status_t status = LCDIC_PrepareSendRepeatData(base, xfer);

    if (kStatus_Success == status)
    {
        status = LCDIC_WaitCmdComplete(base);
    }

    return status;
}

/*
 * brief Send data array using blocking way.
 *
 * This function sends out command and the data array, then waits until
 * send finished or timeout happened.
 *
 * param base LCDIC peripheral base address.
 * param xfer Pointer to the transfer configuration.
 * retval kStatus_Success Sent successfully.
 * retval kStatus_Timeout Timeout happened.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_SendDataArrayBlocking(LCDIC_Type *base, const lcdic_tx_xfer_t *xfer)
{
    status_t status;

    uint32_t xferSizeWordAligned;
    uint8_t xferSizeWordUnaligned;
    uint32_t wordUnalignedData;

    status = LCDIC_PrepareSendDataArray(base, xfer, &xferSizeWordAligned, &xferSizeWordUnaligned, &wordUnalignedData);

    if (kStatus_Success == status)
    {
        status = LCDIC_WriteTxFifoBlocking(base, (const uint32_t *)(uintptr_t)xfer->txData, xferSizeWordAligned / 4U);

        /* Fill the left data to TX FIFO. */
        if ((kStatus_Success == status) && (0U != xferSizeWordUnaligned))
        {
            status = LCDIC_WriteTxFifoBlocking(base, &wordUnalignedData, 1);
        }

        /* Wait for time complete. */
        if (kStatus_Success == status)
        {
            status = LCDIC_WaitCmdComplete(base);
        }
    }

    return status;
}

/*
 * brief Read data array using blocking way.
 *
 * This function sends out command and read the data array, then waits until
 * send finished or timeout happened.
 *
 * param base LCDIC peripheral base address.
 * param xfer Pointer to the transfer configuration.
 * retval kStatus_Success Sent successfully.
 * retval kStatus_Timeout Timeout happened.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDIC_ReadDataArrayBlocking(LCDIC_Type *base, const lcdic_rx_xfer_t *xfer)
{
    status_t status;
    uint32_t xferSizeWordAligned;
    uint8_t xferSizeWordUnaligned;
    uint32_t wordUnalignedData;

    status = LCDIC_PrepareReadDataArray(base, xfer, &xferSizeWordAligned, &xferSizeWordUnaligned);

    if (kStatus_Success == status)
    {
        status = LCDIC_ReadRxFifoBlocking(base, (uint32_t *)(uintptr_t)xfer->rxData, xferSizeWordAligned / 4U);

        if ((kStatus_Success == status) && (0U != xferSizeWordUnaligned))
        {
            status = LCDIC_ReadRxFifoBlocking(base, &wordUnalignedData, 1U);

            if (kStatus_Success == status)
            {
                LCDIC_ExtractByteFromWord(wordUnalignedData, xfer->rxData + xferSizeWordAligned, xferSizeWordUnaligned);
            }
        }
    }

    return status;
}

/*
 * brief LCDIC data transfer using blocking way.
 *
 * This function sends command only, or sends repeat data, or sends data array,
 * or reads data array based on the transfer structure. It uses blocking way,
 * only returns when transfer successed or failed.
 *
 * param base LCDIC peripheral base address.
 * param xfer Pointer to the transfer configuration.
 * retval kStatus_Success Sent successfully.
 * retval kStatus_Timeout Timeout happened.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t LCDC_TransferBlocking(LCDIC_Type *base, const lcdic_xfer_t *xfer)
{
    status_t status;

    switch (xfer->mode)
    {
        case kLCDIC_XferCmdOnly:
            status = LCDIC_SendCommandBlocking(base, xfer->cmdToSendOnly);
            break;

        case kLCDIC_XferSendRepeatData:
            status = LCDIC_SendRepeatDataBlocking(base, &xfer->repeatTxXfer);
            break;

        case kLCDIC_XferSendDataArray:
            status = LCDIC_SendDataArrayBlocking(base, &xfer->txXfer);
            break;

        case kLCDIC_XferReceiveDataArray:
            status = LCDIC_ReadDataArrayBlocking(base, &xfer->rxXfer);
            break;

        default:
            /* Should not reach here. */
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

/*
 * brief Initializes the LCDIC driver handle, which is used in transactional
 * functions.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 * retval kStatus_Success Successfully created the handle.
 */
status_t LCDIC_TransferCreateHandle(LCDIC_Type *base,
                                    lcdic_handle_t *handle,
                                    lcdic_transfer_callback_t callback,
                                    void *userData)
{
    assert(NULL != handle);

    uint32_t instance;

    (void)memset(handle, 0, sizeof(*handle));

    handle->callback = callback;
    handle->userData = userData;

    instance = LCDIC_GetInstance(base);

    s_lcdicIsr = LCDIC_DriverISR;

    LCDIC_TransferInstallIRQHandler(instance, handle, LCDIC_TransferHandleIRQ);

    NVIC_ClearPendingIRQ(s_lcdicIRQ[instance]);

    (void)EnableIRQ(s_lcdicIRQ[instance]);

    return kStatus_Success;
}

/*
 * brief Transfer data using IRQ.
 *
 * This function transfer data using IRQ. This is a non-blocking function, which
 * returns right away. When all data is sent out/received, or timeout happened,
 * the callback function is called.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * param xfer LCDIC transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_Busy LCDIC driver is busy with another transfer.
 */
status_t LCDIC_TransferNonBlocking(LCDIC_Type *base, lcdic_handle_t *handle, lcdic_xfer_t *xfer)
{
    status_t status = kStatus_Success;
    uint32_t interrupts;
    uint32_t xferSizeWordAligned  = 0U;
    uint8_t xferSizeWordUnaligned = 0U;
    uint32_t wordUnalignedData    = 0U;

    if (handle->xferInProgress)
    {
        return kStatus_Busy;
    }

    handle->xferInProgress = true;
    handle->xferMode       = xfer->mode;

    switch (xfer->mode)
    {
        case kLCDIC_XferCmdOnly:
            status     = LCDIC_PrepareSendCommand(base, xfer->cmdToSendOnly);
            interrupts = (uint32_t)kLCDIC_CmdDoneInterrupt;
            break;

        case kLCDIC_XferSendRepeatData:
            status     = LCDIC_PrepareSendRepeatData(base, &xfer->repeatTxXfer);
            interrupts = (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                         (uint32_t)kLCDIC_CmdTimeoutInterrupt;
            break;

        case kLCDIC_XferSendDataArray:
            status = LCDIC_PrepareSendDataArray(base, &xfer->txXfer, &xferSizeWordAligned, &xferSizeWordUnaligned,
                                                &wordUnalignedData);
            handle->txData                = xfer->txXfer.txData;
            handle->xferSizeWordUnaligned = xferSizeWordUnaligned;
            handle->xferSizeWordAligned   = xferSizeWordAligned;
            handle->tmpData               = wordUnalignedData;
            interrupts                    = (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                         (uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TxThresholdInterrupt;
            break;

        case kLCDIC_XferReceiveDataArray:
            status = LCDIC_PrepareReadDataArray(base, &xfer->rxXfer, &xferSizeWordAligned, &xferSizeWordUnaligned);
            handle->rxData                = xfer->rxXfer.rxData;
            handle->xferSizeWordUnaligned = xferSizeWordUnaligned;
            handle->xferSizeWordAligned   = xferSizeWordAligned;
            interrupts                    = (uint32_t)kLCDIC_TeTimeoutInterrupt | (uint32_t)kLCDIC_CmdTimeoutInterrupt |
                         (uint32_t)kLCDIC_RxThresholdInterrupt;
            break;

        default:
            /* Should not reach here. */
            status = kStatus_InvalidArgument;
            break;
    }

    if (status == kStatus_Success)
    {
        LCDIC_EnableInterrupts(base, interrupts);
    }
    else
    {
        handle->xferInProgress = false;
    }

    return status;
}

/*
 * brief Handle send data array in IRQ.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
static void LCDIC_TransferHandleIRQSendArray(LCDIC_Type *base, lcdic_handle_t *lcdicHandle)
{
    /* Fill data to TX FIFO until TX FIFO full or data finished. */

    while (lcdicHandle->xferSizeWordAligned > 0U)
    {
        base->TFIFO_WDATA = *(const uint32_t *)(uintptr_t)(lcdicHandle->txData);

        if (0U != ((uint32_t)kLCDIC_TxOverflowInterrupt & LCDIC_GetInterruptRawStatus(base)))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_TxOverflowInterrupt);
            return;
        }

        lcdicHandle->xferSizeWordAligned -= 4U;
        lcdicHandle->txData += 4U;
    }

    if ((lcdicHandle->xferSizeWordAligned == 0U) && (lcdicHandle->xferSizeWordUnaligned > 0U))
    {
        base->TFIFO_WDATA = lcdicHandle->tmpData;

        if (0U != ((uint32_t)kLCDIC_TxOverflowInterrupt & LCDIC_GetInterruptRawStatus(base)))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_TxOverflowInterrupt);
            return;
        }

        lcdicHandle->xferSizeWordUnaligned = 0U;
    }
}

/*
 * brief Handle receive data array in IRQ.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
static void LCDIC_TransferHandleIRQReceiveArray(LCDIC_Type *base, lcdic_handle_t *lcdicHandle)
{
    uint32_t tmpData;

    /* Read data from RX FIFO until RX FIFO empty. */
    while (lcdicHandle->xferSizeWordAligned > 0U)
    {
        *(uint32_t *)(uintptr_t)(lcdicHandle->rxData) = base->RFIFO_RDATA;

        if (0U != ((uint32_t)kLCDIC_RxUnderflowInterrupt & LCDIC_GetInterruptRawStatus(base)))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_RxUnderflowInterrupt);
            return;
        }

        lcdicHandle->xferSizeWordAligned -= 4U;
        lcdicHandle->rxData += 4U;
    }

    if ((lcdicHandle->xferSizeWordAligned == 0U) && (lcdicHandle->xferSizeWordUnaligned > 0U))
    {
        tmpData = base->RFIFO_RDATA;

        if (0U != ((uint32_t)kLCDIC_RxUnderflowInterrupt & LCDIC_GetInterruptRawStatus(base)))
        {
            LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_RxUnderflowInterrupt);
            return;
        }

        LCDIC_ExtractByteFromWord(tmpData, lcdicHandle->rxData, lcdicHandle->xferSizeWordUnaligned);
        lcdicHandle->xferSizeWordUnaligned = 0U;
    }

    return;
}

/*
 * brief LCDIC IRQ handler function.
 *
 * IRQ handler to work with LCDIC_TransferNonBlocking.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 */
void LCDIC_TransferHandleIRQ(LCDIC_Type *base, void *handle)
{
    assert(NULL != handle);

    uint32_t intStat;
    status_t status             = kStatus_Success;
    bool xferDone               = false;
    lcdic_handle_t *lcdicHandle = (lcdic_handle_t *)handle;

    if (lcdicHandle->xferInProgress)
    {
        intStat = LCDIC_GetInterruptStatus(base);
        LCDIC_ClearInterruptStatus(base, intStat);

        /* Timeout. */
        if (0U != (intStat & ((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt)))
        {
            xferDone = true;
            status   = kStatus_Timeout;
        }

        /*
         * For TX, when command done interrupt happens, TX finished.
         * For RX, when software has received desired data, RX finished.
         */
        else if (0U != (intStat & ((uint32_t)kLCDIC_CmdDoneInterrupt)))
        {
            if (lcdicHandle->xferMode != kLCDIC_XferReceiveDataArray)
            {
                xferDone = true;
            }
        }
        else
        {
            if (kLCDIC_XferSendDataArray == lcdicHandle->xferMode)
            {
                LCDIC_TransferHandleIRQSendArray(base, lcdicHandle);
            }
            else if (kLCDIC_XferReceiveDataArray == lcdicHandle->xferMode)
            {
                LCDIC_TransferHandleIRQReceiveArray(base, lcdicHandle);
                xferDone = ((lcdicHandle->xferSizeWordAligned == 0U) && ((lcdicHandle->xferSizeWordUnaligned == 0U)));
            }
            else
            {
                /* Empty. */
            }
        }

        if (xferDone)
        {
            LCDIC_DisableInterrupts(base, (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                                              (uint32_t)kLCDIC_CmdTimeoutInterrupt |
                                              (uint32_t)kLCDIC_TxThresholdInterrupt |
                                              (uint32_t)kLCDIC_RxThresholdInterrupt);

            lcdicHandle->xferInProgress = false;

            if (NULL != lcdicHandle->callback)
            {
                lcdicHandle->callback(base, lcdicHandle, status, lcdicHandle->userData);
            }
        }
    }
}

/*
 * brief Install the IRQ handler.
 *
 * Install IRQ handler for specific instance.
 *
 * param instance LCDIC instance.
 * param handle Driver handle, it will be used as IRQ handler parameter.
 * param handler IRQ handler to instance.
 */
void LCDIC_TransferInstallIRQHandler(uint32_t instance, void *handle, lcdic_transfer_irq_handler_t handler)
{
    assert(instance < ARRAY_SIZE(s_lcdicIRQHandler));

    s_lcdicHandles[instance]    = handle;
    s_lcdicIRQHandler[instance] = handler;
    s_lcdicIsr                  = LCDIC_DriverISR;
}

/*
 * brief LCDIC ISR.
 *
 * This function handles the reset sequence sent done interupt, and also calls
 * the transfer interupt handler to handle transfer interrupts.
 *
 * param instance LCDIC peripheral instance.
 */
static void LCDIC_DriverISR(uint32_t instance)
{
    LCDIC_Type *base = s_lcdicBases[instance];
    uint32_t intStat = LCDIC_GetInterruptStatus(base);

    /* Handle reset sequence sent done. */
    if (0U != (intStat & (uint32_t)kLCDIC_ResetDoneInterrupt))
    {
        LCDIC_ClearInterruptStatus(base, (uint32_t)kLCDIC_ResetDoneInterrupt);

        if (NULL != s_lcdicResetSendDoneCallback)
        {
            s_lcdicResetSendDoneCallback(base);
        }
    }

    if (NULL != s_lcdicIRQHandler[instance])
    {
        s_lcdicIRQHandler[instance](base, s_lcdicHandles[instance]);
    }
}

void LCDIC_ResetState(LCDIC_Type *base)
{
    /* Clear and set the CTRL[LCDIC_EN] to reset the LCDIC state. */
    base->CTRL &= (~LCDIC_CTRL_LCDIC_EN_MASK);

    LCDIC_ResetStateDelay();

    base->CTRL |= LCDIC_CTRL_LCDIC_EN_MASK;

    LCDIC_ResetStateDelay();
}

#if defined(LCDIC)
void LCDIC_DriverIRQHandler(void);
void LCDIC_DriverIRQHandler(void)
{
    s_lcdicIsr(0);
}
#endif
