/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iuart"
#endif

/* UART transfer state. */
enum _uart_tansfer_states
{
    kUART_TxIdle,         /* TX idle. */
    kUART_TxBusy,         /* TX busy. */
    kUART_RxIdle,         /* RX idle. */
    kUART_RxBusy,         /* RX busy. */
    kUART_RxFramingError, /* Rx framing error */
    kUART_RxParityError   /* Rx parity error */
};

/* Typedef for interrupt handler. */
typedef void (*uart_isr_t)(UART_Type *base, uart_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Check whether the RX ring buffer is full.
 *
 * @param handle UART handle pointer.
 * @retval true  RX ring buffer is full.
 * @retval false RX ring buffer is not full.
 */
static bool UART_TransferIsRxRingBufferFull(uart_handle_t *handle);

/*!
 * @brief Read RX register using non-blocking method.
 *
 * This function reads data from the TX register directly, upper layer must make
 * sure the RX register is full or TX FIFO has data before calling this function.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the buffer to store the received data.
 * @param length Size of the buffer.
 */
static void UART_ReadNonBlocking(UART_Type *base, uint8_t *data, size_t length);

/*!
 * @brief Write to TX register using non-blocking method.
 *
 * This function writes data to the TX register directly, upper layer must make
 * sure the TX register is empty or TX FIFO has empty room before calling this function.
 *
 * @note This function does not check whether all the data has been sent out to bus,
 * so before disable TX, check kUART_TransmissionCompleteFlag to ensure the TX is
 * finished.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the data to write.
 * @param length Size of the buffer to be sent.
 */
static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of UART peripheral base address. */
static UART_Type *const s_uartBases[] = UART_BASE_PTRS;

/* Array of UART IRQ number. */
static const IRQn_Type s_uartIRQ[] = UART_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of UART clock name. */
static const clock_ip_name_t s_uartClock[] = UART_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* UART ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static uart_isr_t s_uartIsr = (uart_isr_t)DefaultISR;
#else
static uart_isr_t s_uartIsr;
#endif

static uart_handle_t *s_uartHandle[ARRAY_SIZE(s_uartBases)];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Get the UART instance from peripheral base address.
 *
 * param base UART peripheral base address.
 * return UART instance.
 */
uint32_t UART_GetInstance(UART_Type *base)
{
    uint32_t instance;
    uint32_t uartArrayCount = (sizeof(s_uartBases) / sizeof(s_uartBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < uartArrayCount; instance++)
    {
        if (s_uartBases[instance] == base)
        {
            break;
        }
    }
    assert(instance < uartArrayCount);

    return instance;
}

/*!
 * brief Get the length of received data in RX ring buffer.
 *
 * param handle UART handle pointer.
 * return Length of received data in RX ring buffer.
 */
size_t UART_TransferGetRxRingBufferLength(uart_handle_t *handle)
{
    assert(handle != NULL);

    size_t size;

    if (handle->rxRingBufferTail > handle->rxRingBufferHead)
    {
        size = (size_t)handle->rxRingBufferHead + handle->rxRingBufferSize - (size_t)handle->rxRingBufferTail;
    }
    else
    {
        size = (size_t)handle->rxRingBufferHead - (size_t)handle->rxRingBufferTail;
    }

    return size;
}

static bool UART_TransferIsRxRingBufferFull(uart_handle_t *handle)
{
    assert(handle != NULL);

    bool full;

    if (UART_TransferGetRxRingBufferLength(handle) == (handle->rxRingBufferSize - 1U))
    {
        full = true;
    }
    else
    {
        full = false;
    }

    return full;
}

/*!
 * brief Initializes an UART instance with the user configuration structure and the peripheral clock.
 *
 * This function configures the UART module with user-defined settings. Call the UART_GetDefaultConfig() function
 * to configure the configuration structure and get the default configuration.
 * The example below shows how to use this API to configure the UART.
 * code
 *  uart_config_t uartConfig;
 *  uartConfig.baudRate_Bps = 115200U;
 *  uartConfig.parityMode = kUART_ParityDisabled;
 *  uartConfig.dataBitsCount = kUART_EightDataBits;
 *  uartConfig.stopBitCount = kUART_OneStopBit;
 *  uartConfig.txFifoWatermark = 2;
 *  uartConfig.rxFifoWatermark = 1;
 *  uartConfig.rxRTSWatermark = 16;
 *  uartConfig.enableAutoBaudrate = false;
 *  uartConfig.enableTx = true;
 *  uartConfig.enableRx = true;
 *  uartConfig.enableRxRTS = false;
 *  uartConfig.enableTxCTS = false;
 *  UART_Init(UART1, &uartConfig, 24000000U);
 * endcode
 *
 * param base UART peripheral base address.
 * param config Pointer to a user-defined configuration structure.
 * param srcClock_Hz UART clock source frequency in HZ.
 * retval kStatus_Success UART initialize succeed
 */
status_t UART_Init(UART_Type *base, const uart_config_t *config, uint32_t srcClock_Hz)
{
    /* Check argument */
    assert(!((NULL == base) || (NULL == config) || (0U == srcClock_Hz)));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable uart clock */
    CLOCK_EnableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable UART Module. */
    UART_Disable(base);
    /* Reset the transmit and receive state machines, all FIFOs and register
     * USR1, USR2, UBIR, UBMR, UBRC, URXD, UTXD and UTS[6-3]. */
    UART_SoftwareReset(base);

    /* Set UART Module Register content to default value */
    base->UCR1  = 0x0;
    base->UCR2  = UART_UCR2_SRST_MASK;
    base->UCR3  = UART_UCR3_DSR_MASK | UART_UCR3_DCD_MASK | UART_UCR3_RI_MASK;
    base->UCR4  = UART_UCR4_CTSTL(32);
    base->UFCR  = UART_UFCR_TXTL(2) | UART_UFCR_RXTL(1);
    base->UESC  = UART_UESC_ESC_CHAR(0x2B);
    base->UTIM  = 0x0;
    base->ONEMS = 0x0;
    base->UTS   = UART_UTS_TXEMPTY_MASK | UART_UTS_RXEMPTY_MASK;
    base->UMCR  = 0x0;

    /* Set UART data word length, stop bit count, parity mode and communication
     * direction according to uart init struct, disable RTS hardware flow control.
     */
    base->UCR2 |=
        ((uint32_t)UART_UCR2_WS(config->dataBitsCount) | (uint32_t)UART_UCR2_STPB(config->stopBitCount) |
         (((uint32_t)(config->parityMode) << UART_UCR2_PROE_SHIFT) & (UART_UCR2_PREN_MASK | UART_UCR2_PROE_MASK)) |
         (uint32_t)UART_UCR2_TXEN(config->enableTx) | (uint32_t)UART_UCR2_RXEN(config->enableRx) |
         (uint32_t)UART_UCR2_IRTS(!config->enableTxCTS) | (uint32_t)UART_UCR2_CTSC(config->enableRxRTS));

#if (defined(FSL_FEATURE_IUART_RXDMUXSEL) && FSL_FEATURE_IUART_RXDMUXSEL)
    /* For imx family device, UARTs are used in MUXED mode, so that this bit should always be set.*/
    base->UCR3 |= UART_UCR3_RXDMUXSEL_MASK;
#endif /* FSL_FEATURE_IUART_RXDMUXSEL */

    /* Set TX/RX fifo water mark */
    UART_SetTxFifoWatermark(base, config->txFifoWatermark);
    UART_SetRxFifoWatermark(base, config->rxFifoWatermark);
    UART_SetRxRTSWatermark(base, config->rxRTSWatermark);

    if (config->enableAutoBaudRate)
    {
        /* Start automatic baud rate detection */
        UART_EnableAutoBaudRate(base, true);
    }
    else if (config->baudRate_Bps != 0U)
    {
        /* Stop automatic baud rate detection */
        UART_EnableAutoBaudRate(base, false);
        /* Set BaudRate according to uart initialize struct. Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)) */
        if (kStatus_Success != UART_SetBaudRate(base, config->baudRate_Bps, srcClock_Hz))
        {
            return kStatus_UART_BaudrateNotSupport;
        }
    }
    else
    {
        /* Stop automatic baud rate detection */
        UART_EnableAutoBaudRate(base, false);
    }

    /* Enable UART module */
    UART_Enable(base);

    return kStatus_Success;
}

/*!
 * brief Deinitializes a UART instance.
 *
 * This function waits for transmit to complete, disables TX and RX, and disables the UART clock.
 *
 * param base UART peripheral base address.
 */
void UART_Deinit(UART_Type *base)
{
    /* Wait transmit FIFO buffer and shift register empty */
    while (UART_USR2_TXDC_MASK != (base->USR2 & UART_USR2_TXDC_MASK))
    {
    }
    /* Disable UART Module */
    UART_Disable(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable uart clock */
    CLOCK_DisableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!l
 * brief Gets the default configuration structure.
 *
 * This function initializes the UART configuration structure to a default value. The default
 * values are:
 *   uartConfig->baudRate_Bps = 115200U;
 *   uartConfig->parityMode = kUART_ParityDisabled;
 *   uartConfig->dataBitsCount = kUART_EightDataBits;
 *   uartConfig->stopBitCount = kUART_OneStopBit;
 *   uartConfig->txFifoWatermark = 2;
 *   uartConfig->rxFifoWatermark = 1;
 *   uartConfig->rxRTSWatermark = 16;
 *   uartConfig->enableAutoBaudrate = flase;
 *   uartConfig->enableTx = false;
 *   uartConfig->enableRx = false;
 *   uartConfig->enableRxRTS = false;
 *   uartConfig->enableTxCTS = false;
 *
 * param config Pointer to a configuration structure.
 */
void UART_GetDefaultConfig(uart_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->baudRate_Bps       = 115200U;
    config->parityMode         = kUART_ParityDisabled;
    config->dataBitsCount      = kUART_EightDataBits;
    config->stopBitCount       = kUART_OneStopBit;
    config->txFifoWatermark    = 2;
    config->rxFifoWatermark    = 1;
    config->rxRTSWatermark     = 16;
    config->enableAutoBaudRate = false;
    config->enableTx           = false;
    config->enableRx           = false;
    config->enableRxRTS        = false;
    config->enableTxCTS        = false;
}

/* This UART instantiation uses a slightly different baud rate calculation.
 * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
 * To get a baud rate, three register need to be writen, UFCR,UBMR and UBIR
 * At first, find the approximately maximum divisor of src_Clock and baudRate_Bps.
 * If the numerator and denominator are larger then register maximum value(0xFFFF),
 * both of numerator and denominator will be divided by the same value, which
 * will ensure numerator and denominator range from 0~maximum value(0xFFFF).
 * Then calculate UFCR and UBIR value from numerator, and get UBMR value from denominator.
 */
/*!
 * brief Sets the UART instance baud rate.
 *
 * This function configures the UART module baud rate. This function is used to update
 * the UART module baud rate after the UART module is initialized by the UART_Init.
 * code
 *  UART_SetBaudRate(UART1, 115200U, 20000000U);
 * endcode
 *
 * param base UART peripheral base address.
 * param baudRate_Bps UART baudrate to be set.
 * param srcClock_Hz UART clock source frequency in Hz.
 * retval kStatus_UART_BaudrateNotSupport Baudrate is not support in the current clock source.
 * retval kStatus_Success Set baudrate succeeded.
 */
status_t UART_SetBaudRate(UART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t numerator       = 0u;
    uint32_t denominator     = 0U;
    uint32_t divisor         = 0U;
    uint32_t refFreqDiv      = 0U;
    uint32_t divider         = 1U;
    uint64_t baudDiff        = 0U;
    uint64_t tempNumerator   = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator   = srcClock_Hz;
    denominator = baudRate_Bps << 4U;
    divisor     = 1U;

    while (denominator != 0U)
    {
        divisor     = denominator;
        denominator = numerator % denominator;
        numerator   = divisor;
    }

    numerator   = srcClock_Hz / divisor;
    denominator = (baudRate_Bps << 4U) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7U)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m   = (numerator - 1U) / (UART_UBIR_INC_MASK * 7U) + 1U;
        uint32_t n   = (denominator - 1U) / UART_UBIR_INC_MASK + 1U;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0U == numerator)
        {
            numerator = 1U;
        }
        if (0U == denominator)
        {
            denominator = 1U;
        }
    }
    divider = (numerator - 1U) / UART_UBIR_INC_MASK + 1U;

    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05U;
            break;
        case 2:
            refFreqDiv = 0x04U;
            break;
        case 3:
            refFreqDiv = 0x03U;
            break;
        case 4:
            refFreqDiv = 0x02U;
            break;
        case 5:
            refFreqDiv = 0x01U;
            break;
        case 6:
            refFreqDiv = 0x00U;
            break;
        case 7:
            refFreqDiv = 0x06U;
            break;
        default:
            refFreqDiv = 0x05U;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator   = (uint64_t)srcClock_Hz;
    tempDenominator = (numerator << 4U);
    divisor         = 1U;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0U)
    {
        divisor         = tempDenominator;
        tempDenominator = (uint32_t)(tempNumerator % tempDenominator);
        tempNumerator   = (uint64_t)divisor;
    }
    tempNumerator   = (uint64_t)srcClock_Hz / (uint64_t)divisor;
    tempDenominator = (numerator << 4U) / divisor;
    baudDiff        = (tempNumerator * (uint64_t)denominator) / (uint64_t)tempDenominator;
    baudDiff        = (baudDiff >= (uint64_t)baudRate_Bps) ? (baudDiff - (uint64_t)baudRate_Bps) :
                                                      ((uint64_t)baudRate_Bps - baudDiff);

    if (baudDiff < ((uint64_t)baudRate_Bps / 100UL * 3UL))
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR  = UART_UBIR_INC(denominator - 1U);
        base->UBMR  = UART_UBMR_MOD(numerator / divider - 1U);
        base->ONEMS = UART_ONEMS_ONEMS(srcClock_Hz / (1000U * divider));

        return kStatus_Success;
    }
    else
    {
        return kStatus_UART_BaudrateNotSupport;
    }
}

/*!
 * brief Enables UART interrupts according to the provided mask.
 *
 * This function enables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See ref _uart_interrupt_enable.
 * For example, to enable TX empty interrupt and RX data ready interrupt, do the following.
 * code
 *     UART_EnableInterrupts(UART1,kUART_TxEmptyEnable | kUART_RxDataReadyEnable);
 * endcode
 *
 * param base UART peripheral base address.
 * param mask The interrupts to enable. Logical OR of ref _uart_interrupt_enable.
 */
void UART_EnableInterrupts(UART_Type *base, uint32_t mask)
{
    assert((0x7F3FF73FU & mask) != 0U);

    if ((0X3FU & mask) != 0U)
    {
        base->UCR1 |= ((mask << UART_UCR1_ADEN_SHIFT) & UART_UCR1_ADEN_MASK) |
                      (((mask >> 1) << UART_UCR1_TRDYEN_SHIFT) & UART_UCR1_TRDYEN_MASK) |
                      (((mask >> 2) << UART_UCR1_IDEN_SHIFT) & UART_UCR1_IDEN_MASK) |
                      (((mask >> 3) << UART_UCR1_RRDYEN_SHIFT) & UART_UCR1_RRDYEN_MASK) |
                      (((mask >> 4) << UART_UCR1_TXMPTYEN_SHIFT) & UART_UCR1_TXMPTYEN_MASK) |
                      (((mask >> 5) << UART_UCR1_RTSDEN_SHIFT) & UART_UCR1_RTSDEN_MASK);
    }
    if ((0X700U & mask) != 0U)
    {
        base->UCR2 |= (((mask >> 8) << UART_UCR2_ESCI_SHIFT) & UART_UCR2_ESCI_MASK) |
                      (((mask >> 9) << UART_UCR2_RTSEN_SHIFT) & UART_UCR2_RTSEN_MASK) |
                      (((mask >> 10) << UART_UCR2_ATEN_SHIFT) & UART_UCR2_ATEN_MASK);
    }
    if ((0x3FF000U & mask) != 0U)
    {
        base->UCR3 |= (((mask >> 12) << UART_UCR3_DTREN_SHIFT) & UART_UCR3_DTREN_MASK) |
                      (((mask >> 13) << UART_UCR3_PARERREN_SHIFT) & UART_UCR3_PARERREN_MASK) |
                      (((mask >> 14) << UART_UCR3_FRAERREN_SHIFT) & UART_UCR3_FRAERREN_MASK) |
                      (((mask >> 15) << UART_UCR3_DCD_SHIFT) & UART_UCR3_DCD_MASK) |
                      (((mask >> 16) << UART_UCR3_RI_SHIFT) & UART_UCR3_RI_MASK) |
                      (((mask >> 17) << UART_UCR3_RXDSEN_SHIFT) & UART_UCR3_RXDSEN_MASK) |
                      (((mask >> 18) << UART_UCR3_AIRINTEN_SHIFT) & UART_UCR3_AIRINTEN_MASK) |
                      (((mask >> 19) << UART_UCR3_AWAKEN_SHIFT) & UART_UCR3_AWAKEN_MASK) |
                      (((mask >> 20) << UART_UCR3_DTRDEN_SHIFT) & UART_UCR3_DTRDEN_MASK) |
                      (((mask >> 21) << UART_UCR3_ACIEN_SHIFT) & UART_UCR3_ACIEN_MASK);
    }
    if ((0x7F000000U & mask) != 0U)
    {
        base->UCR4 |= (((mask >> 24) << UART_UCR4_ENIRI_SHIFT) & UART_UCR4_ENIRI_MASK) |
                      (((mask >> 25) << UART_UCR4_WKEN_SHIFT) & UART_UCR4_WKEN_MASK) |
                      (((mask >> 26) << UART_UCR4_TCEN_SHIFT) & UART_UCR4_TCEN_MASK) |
                      (((mask >> 27) << UART_UCR4_BKEN_SHIFT) & UART_UCR4_BKEN_MASK) |
                      (((mask >> 28) << UART_UCR4_OREN_SHIFT) & UART_UCR4_OREN_MASK) |
                      (((mask >> 29) << UART_UCR4_DREN_SHIFT) & UART_UCR4_DREN_MASK) |
                      (((mask >> 30) << UART_UCR4_IDDMAEN_SHIFT) & UART_UCR4_IDDMAEN_MASK);
    }
}

/*!
 * brief Disables the UART interrupts according to the provided mask.
 *
 * This function disables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See ref _uart_interrupt_enable.
 * For example, to disable TX empty interrupt and RX data ready interrupt do the following.
 * code
 *     UART_EnableInterrupts(UART1,kUART_TxEmptyEnable | kUART_RxDataReadyEnable);
 * endcode
 *
 * param base UART peripheral base address.
 * param mask The interrupts to disable. Logical OR of ref _uart_interrupt_enable.
 */
void UART_DisableInterrupts(UART_Type *base, uint32_t mask)
{
    assert((0x7F3FF73FU & mask) != 0U);

    if ((0X3FU & mask) != 0U)
    {
        base->UCR1 &= ~(((mask << UART_UCR1_ADEN_SHIFT) & UART_UCR1_ADEN_MASK) |
                        (((mask >> 1) << UART_UCR1_TRDYEN_SHIFT) & UART_UCR1_TRDYEN_MASK) |
                        (((mask >> 2) << UART_UCR1_IDEN_SHIFT) & UART_UCR1_IDEN_MASK) |
                        (((mask >> 3) << UART_UCR1_RRDYEN_SHIFT) & UART_UCR1_RRDYEN_MASK) |
                        (((mask >> 4) << UART_UCR1_TXMPTYEN_SHIFT) & UART_UCR1_TXMPTYEN_MASK) |
                        (((mask >> 5) << UART_UCR1_RTSDEN_SHIFT) & UART_UCR1_RTSDEN_MASK));
    }
    if ((0X700U & mask) != 0U)
    {
        base->UCR2 &= ~((((mask >> 8) << UART_UCR2_ESCI_SHIFT) & UART_UCR2_ESCI_MASK) |
                        (((mask >> 9) << UART_UCR2_RTSEN_SHIFT) & UART_UCR2_RTSEN_MASK) |
                        (((mask >> 10) << UART_UCR2_ATEN_SHIFT) & UART_UCR2_ATEN_MASK));
    }
    if ((0x3FF000U & mask) != 0U)
    {
        base->UCR3 &= ~((((mask >> 12) << UART_UCR3_DTREN_SHIFT) & UART_UCR3_DTREN_MASK) |
                        (((mask >> 13) << UART_UCR3_PARERREN_SHIFT) & UART_UCR3_PARERREN_MASK) |
                        (((mask >> 14) << UART_UCR3_FRAERREN_SHIFT) & UART_UCR3_FRAERREN_MASK) |
                        (((mask >> 15) << UART_UCR3_DCD_SHIFT) & UART_UCR3_DCD_MASK) |
                        (((mask >> 16) << UART_UCR3_RI_SHIFT) & UART_UCR3_RI_MASK) |
                        (((mask >> 17) << UART_UCR3_RXDSEN_SHIFT) & UART_UCR3_RXDSEN_MASK) |
                        (((mask >> 18) << UART_UCR3_AIRINTEN_SHIFT) & UART_UCR3_AIRINTEN_MASK) |
                        (((mask >> 19) << UART_UCR3_AWAKEN_SHIFT) & UART_UCR3_AWAKEN_MASK) |
                        (((mask >> 20) << UART_UCR3_DTRDEN_SHIFT) & UART_UCR3_DTRDEN_MASK) |
                        (((mask >> 21) << UART_UCR3_ACIEN_SHIFT) & UART_UCR3_ACIEN_MASK));
    }
    if ((0x7F000000U & mask) != 0U)
    {
        base->UCR4 &= ~((((mask >> 24) << UART_UCR4_ENIRI_SHIFT) & UART_UCR4_ENIRI_MASK) |
                        (((mask >> 25) << UART_UCR4_WKEN_SHIFT) & UART_UCR4_WKEN_MASK) |
                        (((mask >> 26) << UART_UCR4_TCEN_SHIFT) & UART_UCR4_TCEN_MASK) |
                        (((mask >> 27) << UART_UCR4_BKEN_SHIFT) & UART_UCR4_BKEN_MASK) |
                        (((mask >> 28) << UART_UCR4_OREN_SHIFT) & UART_UCR4_OREN_MASK) |
                        (((mask >> 29) << UART_UCR4_DREN_SHIFT) & UART_UCR4_DREN_MASK) |
                        (((mask >> 30) << UART_UCR4_IDDMAEN_SHIFT) & UART_UCR4_IDDMAEN_MASK));
    }
}

/*!
 * brief Gets enabled UART interrupts.
 *
 * This function gets the enabled UART interrupts. The enabled interrupts are returned
 * as the logical OR value of the enumerators ref _uart_interrupt_enable. To check
 * a specific interrupt enable status, compare the return value with enumerators
 * in ref _uart_interrupt_enable.
 * For example, to check whether the TX empty interrupt is enabled:
 * code
 *     uint32_t enabledInterrupts = UART_GetEnabledInterrupts(UART1);
 *
 *     if (kUART_TxEmptyEnable & enabledInterrupts)
 *     {
 *         ...
 *     }
 * endcode
 *
 * param base UART peripheral base address.
 * return UART interrupt flags which are logical OR of the enumerators in ref _uart_interrupt_enable.
 */
uint32_t UART_GetEnabledInterrupts(UART_Type *base)
{
    assert(base != NULL);
    uint32_t temp = 0U;
    /* Get enabled interrupts from UCR1 */
    temp |= ((base->UCR1 & UART_UCR1_ADEN_MASK) >> UART_UCR1_ADEN_SHIFT) |
            (((base->UCR1 & UART_UCR1_TRDYEN_MASK) >> UART_UCR1_TRDYEN_SHIFT) << 1) |
            (((base->UCR1 & UART_UCR1_IDEN_MASK) >> UART_UCR1_IDEN_SHIFT) << 2) |
            (((base->UCR1 & UART_UCR1_RRDYEN_MASK) >> UART_UCR1_RRDYEN_SHIFT) << 3) |
            (((base->UCR1 & UART_UCR1_TXMPTYEN_MASK) >> UART_UCR1_TXMPTYEN_SHIFT) << 4) |
            (((base->UCR1 & UART_UCR1_RTSDEN_MASK) >> UART_UCR1_RTSDEN_SHIFT) << 5);
    /* Get enabled interrupts from UCR2 */
    temp |= (((base->UCR2 & UART_UCR2_ESCI_MASK) >> UART_UCR2_ESCI_SHIFT) << 8) |
            (((base->UCR2 & UART_UCR2_RTSEN_MASK) >> UART_UCR2_RTSEN_SHIFT) << 9) |
            (((base->UCR2 & UART_UCR2_ATEN_MASK) >> UART_UCR2_ATEN_SHIFT) << 10);
    /* Get enabled interrupts from UCR3 */
    temp |= (((base->UCR3 & UART_UCR3_DTREN_MASK) >> UART_UCR3_DTREN_SHIFT) << 12) |
            (((base->UCR3 & UART_UCR3_PARERREN_MASK) >> UART_UCR3_PARERREN_SHIFT) << 13) |
            (((base->UCR3 & UART_UCR3_FRAERREN_MASK) >> UART_UCR3_FRAERREN_SHIFT) << 14) |
            (((base->UCR3 & UART_UCR3_DCD_MASK) >> UART_UCR3_DCD_SHIFT) << 15) |
            (((base->UCR3 & UART_UCR3_RI_MASK) >> UART_UCR3_RI_SHIFT) << 16) |
            (((base->UCR3 & UART_UCR3_RXDSEN_MASK) >> UART_UCR3_RXDSEN_SHIFT) << 17) |
            (((base->UCR3 & UART_UCR3_AIRINTEN_MASK) >> UART_UCR3_AIRINTEN_SHIFT) << 18) |
            (((base->UCR3 & UART_UCR3_AWAKEN_MASK) >> UART_UCR3_AWAKEN_SHIFT) << 19) |
            (((base->UCR3 & UART_UCR3_DTRDEN_MASK) >> UART_UCR3_DTRDEN_SHIFT) << 20) |
            (((base->UCR3 & UART_UCR3_ACIEN_MASK) >> UART_UCR3_ACIEN_SHIFT) << 21);
    /* Get enabled interrupts from UCR4 */
    temp |= (((base->UCR4 & UART_UCR4_ENIRI_MASK) >> UART_UCR4_ENIRI_SHIFT) << 24) |
            (((base->UCR4 & UART_UCR4_WKEN_MASK) >> UART_UCR4_WKEN_SHIFT) << 25) |
            (((base->UCR4 & UART_UCR4_TCEN_MASK) >> UART_UCR4_TCEN_SHIFT) << 26) |
            (((base->UCR4 & UART_UCR4_BKEN_MASK) >> UART_UCR4_BKEN_SHIFT) << 27) |
            (((base->UCR4 & UART_UCR4_OREN_MASK) >> UART_UCR4_OREN_SHIFT) << 28) |
            (((base->UCR4 & UART_UCR4_DREN_MASK) >> UART_UCR4_DREN_SHIFT) << 29) |
            (((base->UCR4 & UART_UCR4_IDDMAEN_MASK) >> UART_UCR4_IDDMAEN_SHIFT) << 30);

    return temp;
}

/*!
 * brief This function is used to get the current status of specific
 *        UART status flag(including interrupt flag). The available
 *        status flag can be select from ref uart_status_flag_t enumeration.
 *
 * param base UART base pointer.
 * param flag Status flag to check.
 * retval current state of corresponding status flag.
 */
bool UART_GetStatusFlag(UART_Type *base, uint32_t flag)
{
    volatile uint32_t *uart_reg;

    uart_reg = (uint32_t *)((uint32_t)base + (flag >> 16));
    return (bool)(((*uart_reg) >> (flag & 0x1FU)) & 0x1U);
}

/*!
 * brief This function is used to clear the current status
 *        of specific UART status flag. The available status
 *        flag can be select from ref uart_status_flag_t enumeration.
 *
 * param base UART base pointer.
 * param flag Status flag to clear.
 */
void UART_ClearStatusFlag(UART_Type *base, uint32_t flag)
{
    volatile uint32_t *uart_reg = NULL;
    uint32_t uart_mask          = 0;

    uart_reg  = (uint32_t *)((uint32_t)base + (flag >> 16));
    uart_mask = (1UL << (flag & 0x0000001FU));

    *uart_reg = uart_mask;
}

/*!
 * brief Writes to the TX register using a blocking method.
 *
 * This function polls the TX register, waits for the TX register to be empty or for the TX FIFO
 * to have room and writes data to the TX buffer.
 *
 * param base UART peripheral base address.
 * param data Start address of the data to write.
 * param length Size of the data to write.
 * retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully wrote all data.
 */
status_t UART_WriteBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
    assert(data != NULL);
#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (length-- != 0U)
    {
        /* Wait for TX fifo valid. */
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
        while ((0U == (base->USR1 & UART_USR1_TRDY_MASK)) && (0U != --waitTimes))
#else
        while (0U == (base->USR1 & UART_USR1_TRDY_MASK))
#endif
        {
        }
#if UART_RETRY_TIMES
        if (0U == waitTimes)
        {
            return kStatus_UART_Timeout;
        }
#endif
        UART_WriteByte(base, *(data++));
    }
#if UART_RETRY_TIMES
    waitTimes = UART_RETRY_TIMES;
    while ((0U == (base->USR2 & UART_USR2_TXDC_MASK)) && (0U != --waitTimes))
#else
    while (0U == (base->USR2 & UART_USR2_TXDC_MASK))
#endif
    {
    }
#if UART_RETRY_TIMES
    if (0U == waitTimes)
    {
        return kStatus_UART_Timeout;
    }
#endif
    return kStatus_Success;
}

/*!
 * brief Read RX data register using a blocking method.
 *
 * This function polls the RX register, waits for the RX register to be full or for RX FIFO to
 * have data, and reads data from the TX register.
 *
 * param base UART peripheral base address.
 * param data Start address of the buffer to store the received data.
 * param length Size of the buffer.
 * retval kStatus_UART_RxHardwareOverrun Receiver overrun occurred while receiving data.
 * retval kStatus_UART_NoiseError A noise error occurred while receiving data.
 * retval kStatus_UART_FramingError A framing error occurred while receiving data.
 * retval kStatus_UART_ParityError A parity error occurred while receiving data.
 * retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully received all data.
 */
status_t UART_ReadBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data != NULL);
    status_t status = kStatus_Success;
#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (length-- != 0U)
    {
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
#endif
        /* Wait for receive data in URXD register is ready */
        while ((base->USR2 & UART_USR2_RDR_MASK) == 0U)
        {
#if UART_RETRY_TIMES
            if (--waitTimes == 0U)
            {
                status = kStatus_UART_Timeout;
                break;
            }
#endif
            /* Over run check for receiving character */
            if ((base->USR2 & UART_USR2_ORE_MASK) != 0U)
            {
                UART_ClearStatusFlag(base, (uint32_t)kUART_RxOverrunFlag);
                status = kStatus_UART_RxHardwareOverrun;
                break;
            }
            /* Parity error check for receiving character */
            if ((base->USR1 & UART_USR1_PARITYERR_MASK) != 0U)
            {
                UART_ClearStatusFlag(base, (uint32_t)kUART_ParityErrorFlag);
                status = kStatus_UART_ParityError;
            }
            /* Framing error check for receiving character */
            if ((base->USR1 & UART_USR1_FRAMERR_MASK) != 0U)
            {
                UART_ClearStatusFlag(base, (uint32_t)kUART_FrameErrorFlag);
                status = kStatus_UART_FramingError;
            }
            if (status != kStatus_Success)
            {
                break;
            }
        }
        if (kStatus_Success == status)
        {
            /* Read data from URXD */
            *(data++) = UART_ReadByte(base);
        }
        else
        {
            break;
        }
    }

    return status;
}

static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
    assert(data != NULL);

    size_t i;

    /* The Non Blocking write data API assume user have ensured there is enough space in
     * peripheral to write. UTXD register holds the parallel transmit data inputs. In 7-bit mode,
     * D7 is ignored. In 8-bit mode, all bits are used.
     */
    for (i = 0; i < length; i++)
    {
        base->UTXD = (uint32_t)data[i] & UART_UTXD_TX_DATA_MASK;
    }
}

static void UART_ReadNonBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data != NULL);

    size_t i;

    /* The Non Blocking read data API assume user have ensured there is enough space in
     * peripheral to write. The URXD holds the received character,In 7-bit mode,
     * the most significant bit (MSB) is forced to 0.In 8-bit mode, all bits are active.
     */
    for (i = 0; i < length; i++)
    {
        data[i] = (uint8_t)((base->URXD & UART_URXD_RX_DATA_MASK) >> UART_URXD_RX_DATA_SHIFT);
    }
}

/*!
 * brief Initializes the UART handle.
 *
 * This function initializes the UART handle which can be used for other UART
 * transactional APIs. Usually, for a specified UART instance,
 * call this API once to get the initialized handle.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 */
void UART_TransferCreateHandle(UART_Type *base,
                               uart_handle_t *handle,
                               uart_transfer_callback_t callback,
                               void *userData)
{
    assert(handle != NULL);

    uint32_t instance;

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set the TX/RX state. */
    handle->rxState = (uint8_t)kUART_RxIdle;
    handle->txState = (uint8_t)kUART_TxIdle;

    /* Set the callback and user data. */
    handle->callback = callback;
    handle->userData = userData;

    /* Get instance from peripheral base address. */
    instance = UART_GetInstance(base);

    /* Save the handle in global variables to support the double weak mechanism. */
    s_uartHandle[instance] = handle;

    s_uartIsr = UART_TransferHandleIRQ;

    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(s_uartIRQ[instance]);
}

/*!
 * brief Sets up the RX ring buffer.
 *
 * This function sets up the RX ring buffer to a specific UART handle.
 *
 * When the RX ring buffer is used, data received are stored into the ring buffer even when the
 * user doesn't call the UART_TransferReceiveNonBlocking() API. If data is already received
 * in the ring buffer, the user can get the received data from the ring buffer directly.
 *
 * note When using the RX ring buffer, one byte is reserved for internal use. In other
 * words, if p ringBufferSize is 32, only 31 bytes are used for saving data.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param ringBuffer Start address of the ring buffer for background receiving. Pass NULL to disable the ring buffer.
 * param ringBufferSize Size of the ring buffer.
 */
void UART_TransferStartRingBuffer(UART_Type *base, uart_handle_t *handle, uint8_t *ringBuffer, size_t ringBufferSize)
{
    assert(handle != NULL);
    assert(ringBuffer != NULL);

    /* Setup the ringbuffer address */
    handle->rxRingBuffer     = ringBuffer;
    handle->rxRingBufferSize = ringBufferSize;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;

    /* Enable the interrupt to accept the data when user need the ring buffer. */
    UART_EnableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                    (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                    (uint32_t)kUART_FrameErrorEnable);
}

/*!
 * brief Aborts the background transfer and uninstalls the ring buffer.
 *
 * This function aborts the background transfer and uninstalls the ring buffer.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferStopRingBuffer(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    if (handle->rxState == (uint8_t)kUART_RxIdle)
    {
        UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                         (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                         (uint32_t)kUART_FrameErrorEnable);
    }

    handle->rxRingBuffer     = NULL;
    handle->rxRingBufferSize = 0U;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;
}

/*!
 * brief Transmits a buffer of data using the interrupt method.
 *
 * This function sends data using an interrupt method. This is a non-blocking function, which
 * returns directly without waiting for all data to be written to the TX register. When
 * all data is written to the TX register in the ISR, the UART driver calls the callback
 * function and passes the ref kStatus_UART_TxIdle as status parameter.
 *
 * note The kStatus_UART_TxIdle is passed to the upper layer when all data is written
 * to the TX register. However, it does not ensure that all data is sent out. Before disabling the TX,
 * check the kUART_TransmissionCompleteFlag to ensure that the TX is finished.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART transfer structure. See  #uart_transfer_t.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_UART_TxBusy Previous transmission still not finished; data not all written to TX register yet.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferSendNonBlocking(UART_Type *base, uart_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);
    assert(xfer->dataSize != 0U);
    assert(xfer->data != NULL);

    status_t status;

    /* Return error if current TX busy. */
    if ((uint8_t)kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txData        = xfer->data;
        handle->txDataSize    = xfer->dataSize;
        handle->txDataSizeAll = xfer->dataSize;
        handle->txState       = (uint8_t)kUART_TxBusy;

        /* Enable transmiter interrupt. */
        UART_EnableInterrupts(base, (uint32_t)kUART_TxReadyEnable);
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the interrupt-driven data transmit.
 *
 * This function aborts the interrupt-driven data sending. The user can get the remainBytes to find out
 * how many bytes are not sent out.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferAbortSend(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    UART_DisableInterrupts(base, (uint32_t)kUART_TxEmptyEnable);

    handle->txDataSize = 0;
    handle->txState    = (uint8_t)kUART_TxIdle;
}

/*!
 * brief Gets the number of bytes written to the UART TX register.
 *
 * This function gets the number of bytes written to the UART TX
 * register by using the interrupt method.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Send bytes count.
 * retval kStatus_NoTransferInProgress No send in progress.
 * retval kStatus_InvalidArgument The parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetSendCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - handle->txDataSize;

    return kStatus_Success;
}

/*!
 * brief Receives a buffer of data using an interrupt method.
 *
 * This function receives data using an interrupt method. This is a non-blocking function, which
 *  returns without waiting for all data to be received.
 * If the RX ring buffer is used and not empty, the data in the ring buffer is copied and
 * the parameter p receivedBytes shows how many bytes are copied from the ring buffer.
 * After copying, if the data in the ring buffer is not enough to read, the receive
 * request is saved by the UART driver. When the new data arrives, the receive request
 * is serviced first. When all data is received, the UART driver notifies the upper layer
 * through a callback function and passes the status parameter ref kStatus_UART_RxIdle.
 * For example, the upper layer needs 10 bytes but there are only 5 bytes in the ring buffer.
 * The 5 bytes are copied to the xfer->data and this function returns with the
 * parameter p receivedBytes set to 5. For the left 5 bytes, newly arrived data is
 * saved from the xfer->data[5]. When 5 bytes are received, the UART driver notifies the upper layer.
 * If the RX ring buffer is not enabled, this function enables the RX and RX interrupt
 * to receive data to the xfer->data. When all data is received, the upper layer is notified.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART transfer structure, see #uart_transfer_t.
 * param receivedBytes Bytes received from the ring buffer directly.
 * retval kStatus_Success Successfully queue the transfer into transmit queue.
 * retval kStatus_UART_RxBusy Previous receive request is not finished.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferReceiveNonBlocking(UART_Type *base,
                                         uart_handle_t *handle,
                                         uart_transfer_t *xfer,
                                         size_t *receivedBytes)
{
    assert(handle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    uint32_t i;
    status_t status;
    /* How many bytes to copy from ring buffer to user memory. */
    size_t bytesToCopy = 0U;
    /* How many bytes to receive. */
    size_t bytesToReceive;
    /* How many bytes currently have received. */
    size_t bytesCurrentReceived;

    /* How to get data:
       1. If RX ring buffer is not enabled, then save xfer->data and xfer->dataSize
          to uart handle, enable interrupt to store received data to xfer->data. When
          all data received, trigger callback.
       2. If RX ring buffer is enabled and not empty, get data from ring buffer first.
          If there are enough data in ring buffer, copy them to xfer->data and return.
          If there are not enough data in ring buffer, copy all of them to xfer->data,
          save the xfer->data remained empty space to uart handle, receive data
          to this empty space and trigger callback when finished. */

    if ((uint8_t)kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        bytesToReceive       = xfer->dataSize;
        bytesCurrentReceived = 0U;

        /* If RX ring buffer is used. */
        if (handle->rxRingBuffer != NULL)
        {
            /* Disable UART RX IRQ, protect ring buffer. */
            UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable);

            /* How many bytes in RX ring buffer currently. */
            bytesToCopy = UART_TransferGetRxRingBufferLength(handle);

            if (bytesToCopy != 0U)
            {
                bytesToCopy = MIN(bytesToReceive, bytesToCopy);

                bytesToReceive -= bytesToCopy;

                /* Copy data from ring buffer to user memory. */
                for (i = 0U; i < bytesToCopy; i++)
                {
                    xfer->data[bytesCurrentReceived++] = handle->rxRingBuffer[handle->rxRingBufferTail];

                    /* Wrap to 0. Not use modulo (%) because it might be large and slow. */
                    if (handle->rxRingBufferTail + 1U == (uint16_t)handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }
            }

            /* If ring buffer does not have enough data, still need to read more data. */
            if (bytesToReceive != 0U)
            {
                /* No data in ring buffer, save the request to UART handle. */
                handle->rxData        = xfer->data + bytesCurrentReceived;
                handle->rxDataSize    = bytesToReceive;
                handle->rxDataSizeAll = bytesToReceive;
                handle->rxState       = (uint8_t)kUART_RxBusy;
            }

            /* Enable UART RX IRQ if previously enabled. */
            UART_EnableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable);

            /* Call user callback since all data are received. */
            if (0U == bytesToReceive)
            {
                if ((handle->callback) != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }
        /* Ring buffer not used. */
        else
        {
            handle->rxData        = xfer->data + bytesCurrentReceived;
            handle->rxDataSize    = bytesToReceive;
            handle->rxDataSizeAll = bytesToReceive;
            handle->rxState       = (uint8_t)kUART_RxBusy;

            /* Enable RX/Rx overrun/framing error interrupt. */
            UART_EnableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                            (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                            (uint32_t)kUART_FrameErrorEnable);
        }

        /* Return the how many bytes have read. */
        if (receivedBytes != NULL)
        {
            *receivedBytes = bytesCurrentReceived;
        }

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the interrupt-driven data receiving.
 *
 * This function aborts the interrupt-driven data receiving. The user can get the remainBytes to know
 * how many bytes are not received yet.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferAbortReceive(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    /* Only abort the receive to handle->rxData, the RX ring buffer is still working. */
    if (handle->rxRingBuffer == NULL)
    {
        /* Disable RX interrupt. */
        UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                         (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                         (uint32_t)kUART_FrameErrorEnable);
    }

    handle->rxDataSize = 0U;
    handle->rxState    = (uint8_t)kUART_RxIdle;
}

/*!
 * brief Gets the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetReceiveCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    if (count == NULL)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->rxDataSizeAll - handle->rxDataSize;

    return kStatus_Success;
}

/*!
 * brief UART IRQ handle function.
 *
 * This function handles the UART transmit and receive IRQ request.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferHandleIRQ(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    uint8_t count;
    uint8_t tempCount;

    /* If RX framing error */
    if ((UART_USR1_FRAMERR_MASK & base->USR1) != 0U)
    {
        /* Write 1 to clear framing error flag */
        base->USR1 |= UART_USR1_FRAMERR_MASK;

        handle->rxState    = (uint8_t)kUART_RxFramingError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if ((handle->callback) != NULL)
        {
            handle->callback(base, handle, kStatus_UART_FramingError, handle->userData);
        }
    }

    /* If RX parity error */
    if ((UART_USR1_PARITYERR_MASK & base->USR1) != 0U)
    {
        /* Write 1 to clear parity error flag. */
        base->USR1 |= UART_USR1_PARITYERR_MASK;

        handle->rxState    = (uint8_t)kUART_RxParityError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if ((handle->callback) != NULL)
        {
            handle->callback(base, handle, kStatus_UART_ParityError, handle->userData);
        }
    }

    /* If RX overrun. */
    if ((UART_USR2_ORE_MASK & base->USR2) != 0U)
    {
        /* Write 1 to clear overrun flag. */
        base->USR2 |= UART_USR2_ORE_MASK;
        /* Trigger callback. */
        if ((handle->callback) != NULL)
        {
            handle->callback(base, handle, kStatus_UART_RxHardwareOverrun, handle->userData);
        }
    }

    /* Receive data FIFO buffer reach the trigger level */
    if (((UART_USR1_RRDY_MASK & base->USR1) != 0U) && ((UART_UCR1_RRDYEN_MASK & base->UCR1) != 0U))
    {
        /* Get the size that stored in receive FIFO buffer for this interrupt. */
        count = (uint8_t)((base->UFCR & UART_UFCR_RXTL_MASK) >> UART_UFCR_RXTL_SHIFT);

        /* If count and handle->rxDataSize are not 0, first save data to handle->rxData. */
        while ((count != 0U) && (handle->rxDataSize != 0U))
        {
            tempCount = (uint8_t)MIN(handle->rxDataSize, count);
            /* Using non block API to read the data from the registers. */
            UART_ReadNonBlocking(base, handle->rxData, tempCount);
            handle->rxData += tempCount;
            handle->rxDataSize -= tempCount;
            count -= tempCount;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (handle->rxDataSize == 0U)
            {
                handle->rxState = (uint8_t)kUART_RxIdle;

                if ((handle->callback) != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }

        /* If use RX ring buffer, receive data to ring buffer. */
        if (handle->rxRingBuffer != NULL)
        {
            while (count-- != 0U)
            {
                /* If RX ring buffer is full, trigger callback to notify over run. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    if ((handle->callback) != NULL)
                    {
                        handle->callback(base, handle, kStatus_UART_RxRingBufferOverrun, handle->userData);
                    }
                }

                /* If ring buffer is still full after callback function, the oldest data is overridden. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if (handle->rxRingBufferTail + 1U == (uint16_t)handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }

                /* Read data. */
                handle->rxRingBuffer[handle->rxRingBufferHead] =
                    (uint8_t)((base->URXD & UART_URXD_RX_DATA_MASK) >> UART_URXD_RX_DATA_SHIFT);

                /* Increase handle->rxRingBufferHead. */
                if (handle->rxRingBufferHead + 1U == (uint16_t)handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }

        else if (handle->rxDataSize == 0U)
        {
            /* Disable RX interrupt/overrun interrupt/framing error interrupt */
            UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                             (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                             (uint32_t)kUART_FrameErrorEnable);
        }
        else
        {
        }
    }
    /* Receive FIFO buffer has been idle for a time of 8 characters, and FIFO data level
     * is less than RxFIFO threshold level.
     */
    if (((UART_USR1_AGTIM_MASK & base->USR1) != 0U) && ((UART_UCR2_ATEN_MASK & base->UCR2) != 0U))
    {
        /* If count and handle->rxDataSize are not 0, first save data to handle->rxData. */
        while (((base->USR2 & UART_USR2_RDR_MASK) != 0U) && (handle->rxDataSize != 0U))
        {
            /* Read one data from the URXD registers. */
            *handle->rxData = UART_ReadByte(base);
            handle->rxData += 1U;
            handle->rxDataSize -= 1U;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (handle->rxDataSize == 0U)
            {
                handle->rxState = (uint8_t)kUART_RxIdle;

                if ((handle->callback) != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }

        /* If use RX ring buffer, receive data to ring buffer. */
        if (handle->rxRingBuffer != NULL)
        {
            while ((base->USR2 & UART_USR2_RDR_MASK) != 0U)
            {
                /* If RX ring buffer is full, trigger callback to notify over run. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    if ((handle->callback) != NULL)
                    {
                        handle->callback(base, handle, kStatus_UART_RxRingBufferOverrun, handle->userData);
                    }
                }

                /* If ring buffer is still full after callback function, the oldest data is overridden. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if (handle->rxRingBufferTail + 1U == (uint16_t)handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }
                /* Read one data from URXD register. */
                handle->rxRingBuffer[handle->rxRingBufferHead] = UART_ReadByte(base);

                /* Increase handle->rxRingBufferHead. */
                if (handle->rxRingBufferHead + 1U == (uint16_t)handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }
        /* If ring buffer is not used and rxDataSize is 0 */
        else if (handle->rxDataSize == 0U)
        {
            /* Disable RX interrupt/overrun interrupt/framing error interrupt */
            UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                             (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                             (uint32_t)kUART_FrameErrorEnable);
        }
        else
        {
        }
        /* Clear aging timer flag for next interrupt */
        UART_ClearStatusFlag(base, (uint32_t)kUART_AgingTimerFlag);
    }
    /* If frame error or parity error happened, stop the RX interrupt when use no ring buffer */
    if (((handle->rxState == (uint8_t)kUART_RxFramingError) || (handle->rxState == (uint8_t)kUART_RxParityError)) &&
        (handle->rxRingBuffer == NULL))
    {
        /* Disable Receive ready interrupt, aging timer interrupt, receive over run interrupt,
         * parity error interrupt and frame error interrupt.
         */
        UART_DisableInterrupts(base, (uint32_t)kUART_RxReadyEnable | (uint32_t)kUART_AgingTimerEnable |
                                         (uint32_t)kUART_RxOverrunEnable | (uint32_t)kUART_ParityErrorEnable |
                                         (uint32_t)kUART_FrameErrorEnable);
    }

    /* Send data register empty and the interrupt is enabled. */
    if (((UART_USR1_TRDY_MASK & base->USR1) != 0U) && ((UART_UCR1_TRDYEN_MASK & base->UCR1) != 0U))
    {
        /* Get the bytes that available at this moment. */
        if (0U != ((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT))
        {
            if ((UART_UTS_TXEMPTY_MASK & base->UTS) != 0U)
            {
                count = FSL_FEATURE_IUART_FIFO_SIZEn(base);
            }
            else
            {
                count = (uint8_t)FSL_FEATURE_IUART_FIFO_SIZEn(base) -
                        (uint8_t)((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT);
            }
        }
        else
        {
            count = 1U;
        }

        while ((count != 0U) && (handle->txDataSize != 0U))
        {
            if (0U != ((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT))
            {
                tempCount = (uint8_t)MIN(handle->txDataSize, count);
            }
            else
            {
                tempCount = 1U;
            }
            /* Using non block API to write the data to the registers. */
            UART_WriteNonBlocking(base, handle->txData, tempCount);
            handle->txData += tempCount;
            handle->txDataSize -= tempCount;
            count -= tempCount;

            /* If all the data are written to data register, TX finished. */
            if (handle->txDataSize == 0U)
            {
                handle->txState = (uint8_t)kUART_TxIdle;
                /* Disable TX FIFO buffer empty interrupt. */
                UART_DisableInterrupts(base, (uint32_t)kUART_TxReadyEnable);
                /* Enable TX complete interrupt. */
                UART_EnableInterrupts(base, (uint32_t)kUART_TxCompleteEnable);
            }
        }
    }

    /* TX complete and the interrupt is enabled. */
    if ((0U != (UART_USR2_TXDC_MASK & base->USR2)) && (0U != (UART_UCR4_TCEN_MASK & base->UCR4)) &&
        (handle->txState == (uint8_t)kUART_TxIdle))
    {
        /* Disable TX complete interrupt. */
        UART_DisableInterrupts(base, (uint32_t)kUART_TxCompleteEnable);

        /* Trigger callback. */
        if ((handle->callback) != NULL)
        {
            handle->callback(base, handle, kStatus_UART_TxIdle, handle->userData);
        }
    }
}

#if defined(UART1)
void UART1_DriverIRQHandler(void);
void UART1_DriverIRQHandler(void)
{
    s_uartIsr(UART1, s_uartHandle[1]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART2)
void UART2_DriverIRQHandler(void);
void UART2_DriverIRQHandler(void)
{
    s_uartIsr(UART2, s_uartHandle[2]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART3)
void UART3_DriverIRQHandler(void);
void UART3_DriverIRQHandler(void)
{
    s_uartIsr(UART3, s_uartHandle[3]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART4)
void UART4_DriverIRQHandler(void);
void UART4_DriverIRQHandler(void)
{
    s_uartIsr(UART4, s_uartHandle[4]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART5)
void UART5_DriverIRQHandler(void);
void UART5_DriverIRQHandler(void)
{
    s_uartIsr(UART5, s_uartHandle[5]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART6)
void UART6_DriverIRQHandler(void);
void UART6_DriverIRQHandler(void)
{
    s_uartIsr(UART6, s_uartHandle[6]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART7)
void UART7_DriverIRQHandler(void);
void UART7_DriverIRQHandler(void)
{
    s_uartIsr(UART7, s_uartHandle[7]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART8)
void UART8_DriverIRQHandler(void);
void UART8_DriverIRQHandler(void)
{
    s_uartIsr(UART8, s_uartHandle[8]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
