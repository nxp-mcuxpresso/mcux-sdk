/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartcard_usim.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smartcard_usim"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to usim bases for each instance. */
static USIM_Type *const s_usimBases[] = USIM_BASE_PTRS;

/*! @brief Pointers to usim IRQ number for each instance. */
static const IRQn_Type s_usimIRQ[] = USIM_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to usim clocks for each instance. */
static const clock_ip_name_t s_usimClock[] = USIM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_USIM_HAS_NO_RESET) && FSL_FEATURE_USIM_HAS_NO_RESET)
/*! @brief Pointers to usim resets for each instance. */
static const reset_ip_name_t s_usimResets[] = USIM_RSTS;
#endif

/* #define CARDSIM_EXTRADELAY_USED */

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void SMARTCARD_USIM_CompleteSendData(USIM_Type *base, smartcard_context_t *context);
static void SMARTCARD_USIM_StartSendData(USIM_Type *base, smartcard_context_t *context);
static void SMARTCARD_USIM_CompleteReceiveData(USIM_Type *base, smartcard_context_t *context);
static void SMARTCARD_USIM_StartReceiveData(USIM_Type *base, smartcard_context_t *context);
static bool SMARTCARD_USIM_SetTransferType(USIM_Type *base, smartcard_context_t *context, smartcard_control_t control);
static void SMARTCARD_USIM_TimerInit(void);
static void SMARTCARD_USIM_TimerDeinit(void);
static void SMARTCARD_USIM_TimerStop(void);
static uint32_t SMARTCARD_USIM_GetInstance(USIM_Type *base);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Get the USIM instance from peripheral base address.
 *
 * @param base USIM peripheral base address.
 * @return USIM instance.
 */
static uint32_t SMARTCARD_USIM_GetInstance(USIM_Type *base)
{
    uint8_t instance        = 0;
    uint32_t usimArrayCount = (sizeof(s_usimBases) / sizeof(s_usimBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < usimArrayCount; instance++)
    {
        if (s_usimBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < usimArrayCount);

    return instance;
}

/*!
 * @brief Calculate FACTOR and DIVISOR value according to given Fi/Di.
 *
 * @param base The USIM peripheral base address.
 * @param fi clock rate conversion integer.
 * @param di baud rate divisor.
 */
static bool SMARTCARD_USIM_SetBaudRate(USIM_Type *base, uint32_t fi, uint32_t di)
{
    uint32_t clkDivisor = (base->CLKR & USIM_CLKR_DIVISOR_MASK) * 2UL * fi;
    uint32_t facTmp, divTmp;

    for (facTmp = 6; facTmp < (uint32_t)USIM_FLR_FACTOR_MASK; facTmp++)
    {
        for (divTmp = 1; divTmp < (uint32_t)USIM_DLR_DIVISOR_MASK; divTmp++)
        {
            if (clkDivisor == (divTmp * facTmp * di))
            {
                base->DLR = divTmp;
                base->FLR = facTmp - 1U;
                return true;
            }
            else if (clkDivisor < (divTmp * facTmp * di))
            {
                return false;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}
/*!
 * @brief Finish up a transmit by completing the process of sending data and disabling the interrupt.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void SMARTCARD_USIM_CompleteSendData(USIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Disable TDR interrupt */
    base->IER &= ~USIM_IER_TDR_MASK;

    /* Wait until Tx fifo empty */
    while ((base->FSR & USIM_FSR_TX_LENGTH_MASK) != 0u)
    {
    }
    /* Update the information of the module driver context */
    context->xIsBusy       = false;
    context->transferState = kSMARTCARD_IdleState;
    /* Clear txSize to avoid any spurious transmit from ISR */
    context->xSize = 0u;
    /* Invoke user call-back */
    if (NULL != context->transferCallback)
    {
        context->transferCallback(context, context->transferCallbackParam);
    }
}

/*!
 * @brief Finish up a receive by completing the process of receiving data and disabling the interrupt.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void SMARTCARD_USIM_CompleteReceiveData(USIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Disable RDR interrupt */
    base->IER &= ~USIM_IER_RDR_MASK;

    /* Read data from fifo */
    while (((base->FSR & USIM_FSR_RX_LENGTH_MASK) != 0u) && ((context->xSize) > 0u))
    {
        /* Get data and put into receive buffer */
        *context->xBuff = (uint8_t)(base->RBR);
        ++context->xBuff;
        --context->xSize;
    }

    /* Update the information of the module driver context */
    context->xIsBusy = false;
    /* Invoke user call-back */
    if (NULL != context->transferCallback)
    {
        context->transferCallback(context, context->transferCallbackParam);
    }
}

/*!
 * @brief Initiate (start) a transmit by beginning the process of sending data and enabling the interrupt.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void SMARTCARD_USIM_StartSendData(USIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Update transferState */
    context->transferState = kSMARTCARD_TransmittingState;
    context->xIsBusy       = true;

    /* Reset transmitter FIFO */
    base->FCR |= USIM_FCR_RESETTF_MASK;

    /* Clear transmitter hold bit. */
    base->FCR &= ~USIM_FCR_TX_HOLD_MASK;

    /* Re-write DLR to restarts all waiting timers. */
    base->DLR = base->DLR;

    /* Set transmitter data trigger level to 0 - TDR is set when the fifo is empty. */
    base->FCR &= ~USIM_FCR_TX_TL_MASK;

    /* Enable TDR interrupt. */
    base->IER |= USIM_IER_TDR_MASK;
}

/*!
 * @brief Initiate (start) a receive by beginning the process of receiving data and enabling the interrupt.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void SMARTCARD_USIM_StartReceiveData(USIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Initialize the module driver context structure to indicate transfer in progress. */
    context->xIsBusy = true;

    /* Set rx trigger value - number of bytes that must exist in the Receive FIFO to trigger the receive data
     * ready interrupt flag (RDR).*/
    if (context->tType == kSMARTCARD_T0Transport)
    {
        if (context->xSize < context->rxFifoThreshold)
        {
            base->FCR = (base->FCR & ~USIM_FCR_RX_TL_MASK) | USIM_FIND_RX_FIFO_TRIGGER_LEVEL(context->xSize);
        }
        else
        {
            /* Set receiver Trigger level to max value. */
            base->FCR |= USIM_FCR_RX_TL_MASK;
        }
    }
    else
    {
        /* Enable interrupt when new byte is received - in T=1 is necessary to disable BWT interrupt and enable CWT
         * interrupt after receiving the first byte */
        base->FCR &= ~USIM_FCR_RX_TL_MASK;
    }

    /* Enable RDR interrupt - count of bytes in rx fifo is equal or greater than Receiver Trigger Level */
    base->IER |= USIM_IER_RDR_MASK;
}

/*!
 * @brief Sets up the USIM hardware for T=0 or T=1 protocol data exchange and initialize timer values.
 *
 * @param base The USIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static bool SMARTCARD_USIM_SetTransferType(USIM_Type *base, smartcard_context_t *context, smartcard_control_t control)
{
    assert((NULL != context));
    assert((control == kSMARTCARD_SetupATRMode) || (control == kSMARTCARD_SetupT0Mode) ||
           (control == kSMARTCARD_SetupT1Mode));

    uint16_t temp16 = 0u;
    uint32_t bwiVal = 0u;

    if (control == kSMARTCARD_SetupATRMode)
    {
        /* Select T=0 protocol for transmitter and receiver. */
        base->LCR &= ~(USIM_LCR_TX_T1_MASK | USIM_LCR_RX_T1_MASK);
        /* Set default values as per EMV specification */
        context->cardParams.Fi       = 372u;
        context->cardParams.Di       = 1u;
        context->cardParams.currentD = 1u;
        context->cardParams.WI       = 0x0Au;
        context->cardParams.GTN      = 0x00u;
        /* Set default baudrate/ETU time based on EMV parameters */
        if (!SMARTCARD_USIM_SetBaudRate(base, (uint32_t)context->cardParams.Fi, (uint32_t)context->cardParams.currentD))
        {
            return false;
        }

        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
         * USIM formula under T=0: CWTR[15:0] = WWT -12 */
        temp16 = (960u * context->cardParams.currentD * context->cardParams.WI) + (context->cardParams.currentD * 480u);
        base->CWTR = (uint32_t)temp16 - SMARTCARD_T0_CWT_ADJUSTMENT;
        base->BWTR = (uint32_t)temp16 - SMARTCARD_T0_BWT_ADJUSTMENT;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = (12 + GTN) etu or 12 etu
         * USIM formula under T=0: EGTR[EGTM] = GT - 12*/
        context->cardParams.GTN = (context->cardParams.GTN == 0xFFu) ? 0x00u : context->cardParams.GTN;
        base->EGTR              = context->cardParams.GTN;
        /* Setting Parity Error level and T0 error level so that an interrupt is generated when parity/T0 error
         * reach threshold.  */
        base->ECR = (base->ECR & ~(USIM_ECR_T0ERR_TL_MASK | USIM_ECR_PE_TL_MASK)) |
                    USIM_ECR_T0ERR_TL(SMARTCARD_EMV_TX_NACK_THRESHOLD - 1UL) |
                    USIM_ECR_PE_TL(SMARTCARD_EMV_RX_NACK_THRESHOLD - 1UL);
        /* Clear all pending interrupts */
        base->IIR = 0x37u;
        /* Enable T0 Error and Parity Error interrupts to occur */
        base->IER |= USIM_IER_T0ERR_MASK | USIM_IER_PERR_MASK;
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else if (control == kSMARTCARD_SetupT0Mode)
    {
        /* Select T=0 protocol for transmitter and receiver. */
        base->LCR &= ~(USIM_LCR_TX_T1_MASK | USIM_LCR_RX_T1_MASK);
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
         * USIM formula under T=0: CWTR[15:0] = WWT -12 */
        temp16 = (960u * context->cardParams.currentD * context->cardParams.WI) + (context->cardParams.currentD * 480u);
        base->CWTR = (uint32_t)temp16 - SMARTCARD_T0_CWT_ADJUSTMENT;
        base->BWTR = (uint32_t)temp16 - SMARTCARD_T0_BWT_ADJUSTMENT;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = (12 + GTN) etu or 12 etu
         * USIM formula under T=0: EGTR[EGTM] = GT - 12*/
        context->cardParams.GTN = (context->cardParams.GTN == 0xFFu) ? 0x00u : context->cardParams.GTN;
        base->EGTR              = context->cardParams.GTN;
        /* Setting Parity Error level and T0 error level so that an interrupt is generated when parity/T0 error
         * reach threshold.  */
        base->ECR = (base->ECR & ~(USIM_ECR_T0ERR_TL_MASK | USIM_ECR_PE_TL_MASK)) |
                    USIM_ECR_T0ERR_TL(SMARTCARD_EMV_TX_NACK_THRESHOLD - 1UL) |
                    USIM_ECR_PE_TL(SMARTCARD_EMV_RX_NACK_THRESHOLD - 1UL);
        /* Clear all pending interrupts */
        base->IIR = 0x37u;
        /* Enable T0 Error and Parity Error interrupts to occur */
        base->IER |= USIM_IER_T0ERR_MASK | USIM_IER_PERR_MASK;
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else
    {
        /* Select T=1 protocol for transmitter and receiver. */
        base->LCR |= USIM_LCR_TX_T1_MASK | USIM_LCR_RX_T1_MASK;
        /* Calculate and set Block Wait Timer (BWT) value
         * EMV expectation: BWT = 11 + (2^BWI x 960 x D) + (D x 960) = 11 + (2^BWI + 1) x 960 x D
         * USIM formula: BWTR[15:0] = BWT - 11 */
        bwiVal     = 11u + ((((uint32_t)1u << context->cardParams.BWI) + 1u) * 960u * context->cardParams.currentD);
        base->BWTR = bwiVal - SMARTCARD_T1_BWT_ADJUSTMENT;
        /* Calculate and set Character Wait Timer (CWT) value
         * EMV expectation: CWT = ((2^CWI + 11) + 4)
         * USIM formula: CWTR[15:0] = CWT -11 */
        temp16     = ((uint16_t)1u << context->cardParams.CWI) + 15u;
        base->CWTR = (uint32_t)temp16 - SMARTCARD_T1_CWT_ADJUSTMENT;
        /* EMV expectation: BGT = 22
         * USIM formula: BGTR = BGT - 11 */
        context->cardParams.BGI = 22u;
        base->BGTR              = (uint32_t)context->cardParams.BGI - 11U;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = (12 + GTN) etu or 11 etu
         * USIM formula under T=0: EGTR[EGTM] = GT - 11*/
        context->cardParams.GTN = (context->cardParams.GTN == 0xFFu) ? 0x00u : (context->cardParams.GTN + 1U);
        base->EGTR              = context->cardParams.GTN;
        /* Clear all pending interrupts */
        base->IIR = 0x37u;
        /* Enable Framing Error interrupts to occur */
        base->IER |= USIM_IER_FRAMERR_MASK;
        /* Set transport type to T=1 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T1Transport;
    }
    return true;
}

#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && (FSL_FEATURE_SOC_CTIMER_COUNT)
/*!
 * @brief Function un-gates peripheral clock of CTIMER0.
 */
static void SMARTCARD_USIM_TimerInit(void)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate the CTIMER timer clock*/
    CLOCK_EnableClock(kCLOCK_Ct32b0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_RESET) && (FSL_FEATURE_CTIMER_HAS_NO_RESET))
    RESET_PeripheralReset(kCT32B0_RST_SHIFT_RSTn);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
    /* Setup the cimer mode */
    CTIMER0->CTCR = 0U;
    /* Setup the timer prescale value */
    CTIMER0->PR = 0U;
    /* Stop timer */
    CTIMER0->TCR &= ~CTIMER_TCR_CEN_MASK;
    /* Enable timer interrupt to occur */
    NVIC_EnableIRQ(CTIMER0_IRQn);
}

/*!
 * @brief Function gates peripheral clock of CTIMER0.
 */
static void SMARTCARD_USIM_TimerDeinit(void)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the CTIMER timer clock*/
    CLOCK_DisableClock(kCLOCK_Ct32b0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable CTIMER IRQ interrupt to occur */
    NVIC_DisableIRQ(CTIMER0_IRQn);
}

/*!
 * brief Initializes timer with input period, enable interrupt and start counter.
 *
 * param channel The timer channel.
 * param time The time period.
 */
void SMARTCARD_USIM_TimerStart(uint32_t time)
{
    /* Set timer period */
    CTIMER0->MR[0] = time;
    /* Enable timer interrupt and timer */
    CTIMER0->MCR = CTIMER_MCR_MR0I_MASK | CTIMER_MCR_MR0R_MASK | CTIMER_MCR_MR0S_MASK;
    CTIMER0->TCR |= CTIMER_TCR_CEN_MASK;
}

/*!
 * @brief Stop timer specific channel, disable channel interrupts and stops counter.
 */
static void SMARTCARD_USIM_TimerStop(void)
{
    /* Stop timer*/
    CTIMER0->TCR &= ~CTIMER_TCR_CEN_MASK;
}
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */

/*!
 * brief Fills in the smartcard_card_params structure with default values according to the EMV 4.3 specification.
 *
 * param cardParams The configuration structure of type smartcard_interface_config_t.
 * Function fill in members:
 *        Fi = 372;
 *        Di = 1;
 *        currentD = 1;
 *        WI = 0x0A;
 *        GTN = 0x00;
 * with default values.
 */
void SMARTCARD_USIM_GetDefaultConfig(smartcard_card_params_t *cardParams)
{
    /* Initializes the configure structure to zero. */
    (void)memset(cardParams, 0, sizeof(*cardParams));

    /* EMV default values */
    cardParams->Fi       = 372u;
    cardParams->Di       = 1u;
    cardParams->currentD = 1u;
    cardParams->WI       = 0x0Au;
    cardParams->GTN      = 0x00u;
}

/*!
 * brief Initializes an USIM peripheral for the Smart card/ISO-7816 operation.
 *
 * This function un-gates the USIM clock, initializes the module to EMV default settings,
 * configures the IRQ, enables the module-level interrupt to the core and, initializes the driver context.
 *
 * param base The USIM peripheral base address.
 * param context A pointer to the smart card driver context structure.
 * param srcClock_Hz Smart card clock generation module source clock.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_USIM_Init(USIM_Type *base, smartcard_context_t *context, uint32_t srcClock_Hz)
{
    assert((NULL != base));

    if ((NULL == context) || (0UL == srcClock_Hz) || (0UL != (srcClock_Hz % context->interfaceConfig.smartCardClock)))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    uint32_t instance = SMARTCARD_USIM_GetInstance(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable usim clock */
    CLOCK_EnableClock(s_usimClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_USIM_HAS_NO_RESET) && FSL_FEATURE_USIM_HAS_NO_RESET)
    /* Reset the usim module */
    RESET_PeripheralReset(s_usimResets[instance]);
#endif /* FSL_FEATURE_USIM_HAS_NO_RESET */

    context->base = base;
    /* Initialize USIM to a known context. */
    /* Starts the USIM_IF's clock, stop Card Clock and set card's clock divisor. */
    base->CLKR =
        USIM_CLKR_STOP_UCLK_MASK | USIM_CLKR_DIVISOR(srcClock_Hz / context->interfaceConfig.smartCardClock / 2U);
    base->USCCR |= USIM_USCCR_TXD_FORCE_MASK;
    /* Clears FIFOs. */
    base->FCR |= USIM_FCR_RESETTF_MASK | USIM_FCR_RESETRF_MASK;
    /* Initialize USIM module for SMARTCARD mode of default operation */
    if (!SMARTCARD_USIM_SetTransferType(base, context, kSMARTCARD_SetupATRMode))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    /* Store information about tx fifo depth */
    context->txFifoEntryCount = FSL_FEATURE_USIM_FIFO_DEPTH;
    /* Compute max value of rx fifo threshold */
    context->rxFifoThreshold = SMARTCARD_MAX_RX_TRIGGER_LEVEL;
    /* Enable USIM interrupt on NVIC level. */
    NVIC_EnableIRQ(s_usimIRQ[instance]);
#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && (FSL_FEATURE_SOC_CTIMER_COUNT)
    /* Initialize HW timer for the initial character (TS) delay measurement */
    SMARTCARD_USIM_TimerInit();
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */
    /* Finally, disable the USIM transmitter */
    base->FCR |= USIM_FCR_TX_HOLD_MASK;

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief This function disables the USIM interrupts, disables the transmitter and receiver,
 * flushes the FIFOs, and gates USIM clock in SIM.
 *
 * param base The USIM module base address.
 */
void SMARTCARD_USIM_Deinit(USIM_Type *base)
{
    uint32_t instance = 0u;
    /* In case there is still data in the TX FIFO that is being transmitted wait till transmit is complete. */
    while ((base->FSR & USIM_FSR_TX_LENGTH_MASK) != 0u)
    {
    }
    while ((base->LSR & USIM_LSR_TX_WORKING_MASK) != 0u)
    {
    }
    instance = SMARTCARD_USIM_GetInstance(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate USIM module clock */
    CLOCK_DisableClock(s_usimClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Disable usim interrupt in NVIC */
    NVIC_DisableIRQ(s_usimIRQ[instance]);
/* De-initialize also external CTIMER timer */
#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && (FSL_FEATURE_SOC_CTIMER_COUNT)
    SMARTCARD_USIM_TimerDeinit();
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */
}

/*!
 * brief Transfer data using interrupts.
 *
 * A non-blocking (also known as asynchronous) function means that the function returns
 * immediately after initiating the transfer function. The application has to get the
 * transfer status to see when the transfer is complete. In other words, after calling the non-blocking
 * (asynchronous) transfer function, the application must get the transfer status to check if the transmit
 * is completed or not.
 *
 * param base The USIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param xfer A pointer to the smart card transfer structure where the linked buffers and sizes are stored.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_USIM_TransferNonBlocking(USIM_Type *base, smartcard_context_t *context, smartcard_xfer_t *xfer)
{
    if ((NULL == context) || (NULL == xfer) || (xfer->buff == NULL))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    /* Check input parameters */
    if ((0u == xfer->size))
    {
        return kStatus_SMARTCARD_Success;
    }
    /* Check if some transfer is in progress */
    if (0 != SMARTCARD_USIM_GetTransferRemainingBytes(base, context))
    {
        if (kSMARTCARD_Receive == context->direction)
        {
            return kStatus_SMARTCARD_RxBusy;
        }
        else
        {
            return kStatus_SMARTCARD_TxBusy;
        }
    }
    /* Initialize error check flags */
    context->rxtCrossed  = false;
    context->txtCrossed  = false;
    context->parityError = false;
    /* Initialize SMARTCARD context structure to start transfer */
    context->xBuff = xfer->buff;
    context->xSize = xfer->size;

    if (kSMARTCARD_Receive == xfer->direction)
    {
        context->direction     = xfer->direction;
        context->transferState = kSMARTCARD_ReceivingState;
        /* Start transfer */
        SMARTCARD_USIM_StartReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == xfer->direction)
    {
        context->direction     = xfer->direction;
        context->transferState = kSMARTCARD_TransmittingState;
        /* Start transfer */
        SMARTCARD_USIM_StartSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Returns whether the previous USIM transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the context of the
 * current transfer: in progress (or busy) or complete (success). If the
 * transfer is still in progress, the user can obtain the number of words that have not been
 * transferred.
 *
 * param base The USIM module base address.
 * param context A pointer to a smart card driver context structure.
 *
 * return The number of bytes not transferred.
 */
int32_t SMARTCARD_USIM_GetTransferRemainingBytes(USIM_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return -1;
    }
    if (context->xIsBusy)
    {
        if (context->direction == kSMARTCARD_Transmit)
        {
            /* Count of bytes in buffer + data in fifo */
            uint32_t count;
            count = context->xSize;
            count += ((base->FSR & USIM_FSR_TX_LENGTH_MASK) >> USIM_FSR_TX_LENGTH_SHIFT);
            return (int32_t)count;
        }
        return (int32_t)context->xSize;
    }

    return 0;
}

/*!
 * brief Terminates an asynchronous USIM transfer early.
 *
 * During an async USIM transfer, the user can terminate the transfer early
 * if the transfer is still in progress.
 *
 * param base The USIM peripheral address.
 * param context A pointer to a smart card driver context structure.
 * retval kStatus_SMARTCARD_Success The transmit abort was successful.
 * retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
status_t SMARTCARD_USIM_AbortTransfer(USIM_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    context->abortTransfer = true;

    /* Check if a transfer is running. */
    if ((!context->xIsBusy))
    {
        return kStatus_SMARTCARD_NoTransferInProgress;
    }
    /* Call transfer complete to abort transfer */
    if (kSMARTCARD_Receive == context->direction)
    { /* Finish up current running transfer. */
        SMARTCARD_USIM_CompleteReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == context->direction)
    { /* Finish up current running transfer. */
        SMARTCARD_USIM_CompleteSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Handles USIM module interrupts.
 *
 * param base The USIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 */
void SMARTCARD_USIM_IRQHandler(USIM_Type *base, smartcard_context_t *context)
{
    if (NULL == context)
    {
        return;
    }

    /* Check if Character Waiting Time has expired */
    if (((base->IIR & USIM_IIR_CWT_MASK) != 0u) && ((base->IER & USIM_IER_CWT_MASK) != 0u))
    {
        /*Clear Character Wait Timer interrupt status. */
        base->IIR |= USIM_IIR_CWT_MASK;
        /*Restart Character Wait Timer. */
        base->DLR = base->DLR;

        if (kSMARTCARD_T0Transport == context->tType)
        { /* Indicate WWT expired */
            context->timersState.wwtExpired = true;
        }
        else
        { /* Indicate CWT expired */
            context->timersState.cwtExpired = true;
        }

        if (context->xIsBusy)
        {
            if (kSMARTCARD_Receive == context->direction)
            { /* Terminate and un-block any caller */
                SMARTCARD_USIM_CompleteReceiveData(base, context);
            }
            else
            { /* Terminate and un-block any caller */
                SMARTCARD_USIM_CompleteSendData(base, context);
            }
        }
    }

    /* Check if a Block Wait Timer expired */
    if (((base->IIR & USIM_IIR_BWT_MASK) != 0u) && ((base->IER & USIM_IER_BWT_MASK) != 0u))
    {
        /* Clear Block Wait Timer interrupt status flag. */
        base->IIR |= USIM_IIR_BWT_MASK;
        /*Restart Block Wait Timer. */
        base->DLR = base->DLR;

        if (kSMARTCARD_T0Transport == context->tType)
        { /* Indicate WWT expired */
            context->timersState.wwtExpired = true;
        }
        else
        { /* Indicate BWT expired */
            context->timersState.bwtExpired = true;
        }
        /* Check if Wait Time Extension(WTX) was requested */
        if (context->wtxRequested)
        { /* Reset WTX to default */
            (void)SMARTCARD_USIM_Control(base, context, kSMARTCARD_ResetWaitTimeMultiplier, 1u);
        }
        if (context->xIsBusy)
        {
            if (kSMARTCARD_Receive == context->direction)
            { /* Terminate and un-block any caller */
                SMARTCARD_USIM_CompleteReceiveData(base, context);
            }
            else
            { /* Terminate and un-block any caller */
                SMARTCARD_USIM_CompleteSendData(base, context);
            }
        }
    }

    /* Check if parity error trigger level was reached */
    if ((base->IIR & USIM_IIR_PERR_MASK) != 0u)
    {
        /* Clear parity error interrupt status. */
        base->IIR |= USIM_IIR_PERR_MASK;
        if (kSMARTCARD_WaitingForTSState == context->transferState)
        {
            /* A parity error detected during initial character (TS) detection phase */
            context->transferState = kSMARTCARD_InvalidTSDetecetedState;
            /* Un-block any caller waiting for initial character detection */
            if ((context->xIsBusy) && (context->direction == kSMARTCARD_Receive))
            {
                SMARTCARD_USIM_CompleteReceiveData(base, context);
            }
        }
        else
        { /* Parity error detected after initial character detection phase */
            context->parityError = true;
            if (context->tType == kSMARTCARD_T0Transport)
            {
                /* Indicate T=0 Rx parity error trigger level expired. */
                context->rxtCrossed = true;
                SMARTCARD_USIM_CompleteReceiveData(base, context);
            }
        }
    }

    /* Check if framing error trigger level was reached */
    if ((base->IIR & USIM_IIR_FRAMERR_MASK) != 0u)
    {
        /* Indicate framing Rx error trigger level expired. */
        context->rxtCrossed = true;
        /* Clear framing error interrupt status. */
        base->IIR |= USIM_IIR_FRAMERR_MASK;
        if (context->xIsBusy)
        { /* Unblock the caller */
            SMARTCARD_USIM_CompleteReceiveData(base, context);
        }
    }

    /* Check if T=0 error trigger level was reached */
    if ((base->IIR & USIM_IIR_T0ERR_MASK) != 0u)
    {
        /* Indicate T=0 Tx error trigger level expired. */
        context->txtCrossed = true;
        /* Clear T=0 error interrupt status. */
        base->IIR |= USIM_IIR_T0ERR_MASK;
        if (context->xIsBusy)
        { /* Unblock the caller */
            SMARTCARD_USIM_CompleteSendData(base, context);
        }
    }

    /* RDR IRQ - count of bytes in rx fifo is equal to or greater than FCR[RX_TL]. */
    if (((base->IIR & USIM_IIR_RDR_MASK) != 0u) && ((base->IER & USIM_IER_RDR_MASK) != 0u))
    {
        /* IF in T=1 after receive 1st byte - disable BWT and enable CWT interrupt */
        if ((context->tType == kSMARTCARD_T1Transport) && (context->xSize > 0u) &&
            ((base->IER & USIM_IER_BWT_MASK) != 0u))
        {
            context->timersState.cwtExpired = false;
            /* Clear CWT error flag */
            base->IIR = USIM_IIR_CWT_MASK;

            /* Disable BWT interrupt and enable CWT interrupt. */
            base->IER = (base->IER & ~USIM_IER_BWT_MASK) | USIM_IER_CWT_MASK;
        }
        if (kSMARTCARD_WaitingForTSState == context->transferState)
        {
#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && (FSL_FEATURE_SOC_CTIMER_COUNT)
            /* Stop TS timer */
            SMARTCARD_USIM_TimerStop();
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */
            /* Read TS byte */
            uint8_t ts = (uint8_t)base->RBR;
            if (ts == SMARTCARD_TS_INVERSE_CONVENTION)
            {
                /* Received valid TS */
                context->transferState = kSMARTCARD_ReceivingState;
                /* Card encodes/decodes data in the inverse convention. */
                context->cardParams.convention = kSMARTCARD_InverseConvention;
                base->LCR |= USIM_LCR_ORDER_MASK;
                base->LCR &= ~USIM_LCR_EPS_MASK;
            }
            else if (ts == SMARTCARD_TS_DIRECT_CONVENTION)
            {
                /* Received valid TS */
                context->transferState = kSMARTCARD_ReceivingState;
                /* Card encodes/decodes data in the direct convention. */
                context->cardParams.convention = kSMARTCARD_DirectConvention;
                base->LCR &= ~USIM_LCR_ORDER_MASK;
                base->LCR |= USIM_LCR_EPS_MASK;
            }
            else
            {
                context->transferState = kSMARTCARD_InvalidTSDetecetedState;
            }
            /* Complete receive transfer */
            SMARTCARD_USIM_CompleteReceiveData(base, context);
        }
        else
        {
            while (((base->FSR & USIM_FSR_RX_LENGTH_MASK) != 0u) && ((context->xSize) > 0u))
            {
                /* Get data and put into receive buffer */
                *context->xBuff = (uint8_t)(base->RBR);
                ++context->xBuff;
                --context->xSize;
            }

            /* Check if the last byte was received */
            if (context->xSize == 0u)
            {
                SMARTCARD_USIM_CompleteReceiveData(base, context);
            }
            else
            {
                /* If the count of remaining bytes to receive is less than depth of fifo, update the value of the
                 * receiver data trigger level. */
                if (context->xSize < context->rxFifoThreshold)
                {
                    /* Set receiver data trigger level to the value closest to the number of bytes remaining. */
                    base->FCR = (base->FCR & ~USIM_FCR_RX_TL_MASK) | USIM_FIND_RX_FIFO_TRIGGER_LEVEL(context->xSize);
                }
            }
        }
    }

    /* TDR IRQ -  the number of bytes in the TX-FIFO is less than FCR[TX_TL]. */
    if (((base->IIR & USIM_IIR_TDR_MASK) != 0u) && ((base->IER & USIM_IER_TDR_MASK) != 0u))
    {
        if (context->xSize == 0u)
        {
            SMARTCARD_USIM_CompleteSendData(base, context);
        }
        else
        {
            while (((context->txFifoEntryCount -
                     (uint8_t)((base->FSR & USIM_FSR_TX_LENGTH_MASK) >> USIM_FSR_TX_LENGTH_SHIFT)) > 0u) &&
                   (context->xSize > 0u))
            {
                /* Write data to fifo */
                base->THR = *(context->xBuff);
                ++context->xBuff;
                --context->xSize;
            }
        }
    }

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * brief Controls the USIM module per different user request.
 *
 * param base The USIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param control Control type.
 * param param Integer value of specific to control command.
 *
 * return kStatus_SMARTCARD_Success in success.
 * return kStatus_SMARTCARD_OtherError in case of error.
 */
status_t SMARTCARD_USIM_Control(USIM_Type *base,
                                smartcard_context_t *context,
                                smartcard_control_t control,
                                uint32_t param)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    status_t status = kStatus_SMARTCARD_Success;
    uint32_t temp32 = 0u;

    switch (control)
    {
        case kSMARTCARD_EnableADT:
            break;
        case kSMARTCARD_DisableADT:
            break;
        case kSMARTCARD_EnableGTV:
            break;
        case kSMARTCARD_DisableGTV:
            break;
        case kSMARTCARD_ResetWWT:
            /* Re-write DLR to reset WWT Timer. */
            base->DLR = base->DLR;
            break;
        case kSMARTCARD_EnableWWT:
            /* Enable BWT/CWT Timer interrupt to occur. */
            base->IER |= USIM_IER_BWT_MASK | USIM_IER_CWT_MASK;
            break;
        case kSMARTCARD_DisableWWT:
            /* Disable BWT/CWT Timer interrupt to occur. */
            base->IER &= ~(USIM_IER_BWT_MASK | USIM_IER_CWT_MASK);
            break;
        case kSMARTCARD_ResetCWT:
            /* Re-write DLR to reset CWT Timer. */
            base->DLR = base->DLR;
            break;
        case kSMARTCARD_EnableCWT:
            /* Enable CWT Timer interrupt to occur. */
            base->IER |= USIM_IER_CWT_MASK;
            break;
        case kSMARTCARD_DisableCWT:
            /* Disable CWT Timer interrupt to occur. */
            base->IER &= ~USIM_IER_CWT_MASK;
            break;
        case kSMARTCARD_ResetBWT:
            /* Re-write DLR to reset BWT Timer. */
            base->DLR = base->DLR;
            break;
        case kSMARTCARD_EnableBWT:
            /* Enable BWT Timer interrupt to occur. */
            base->IER |= USIM_IER_BWT_MASK;
            break;
        case kSMARTCARD_DisableBWT:
            /* Disable BWT Timer interrupt to occur. */
            base->IER &= ~USIM_IER_BWT_MASK;
            break;
        case kSMARTCARD_EnableInitDetect:
            /* Enable initial character detection : hardware method. */
            context->transferState = kSMARTCARD_WaitingForTSState;
            /* Set receiver triggrt level to 1 byte. */
            base->FCR &= ~USIM_FCR_RX_TL_MASK;
            /* Enable RDT interrupt. */
            base->IER |= USIM_IER_RDR_MASK;
            break;
        case kSMARTCARD_EnableAnack:
            /* Enable all error interrupt. */
            base->IER |= USIM_IER_T0ERR_MASK | USIM_IER_PERR_MASK | USIM_IER_FRAMERR_MASK;
            break;
        case kSMARTCARD_DisableAnack:
            /* Disable error interrupt to occur. */
            base->IER &= ~(USIM_IER_T0ERR_MASK | USIM_IER_PERR_MASK | USIM_IER_FRAMERR_MASK);
            break;
        case kSMARTCARD_ConfigureBaudrate:
            /* Set baudrate/ETU time based on Fi/Di parameters. */
            if (!SMARTCARD_USIM_SetBaudRate(base, (uint32_t)context->cardParams.Fi,
                                            (uint32_t)context->cardParams.currentD))
            {
                status = kStatus_SMARTCARD_InvalidInput;
            }
            break;
        case kSMARTCARD_SetupATRMode:
            /* Set in default ATR mode. */
            if (!SMARTCARD_USIM_SetTransferType(base, context, kSMARTCARD_SetupATRMode))
            {
                status = kStatus_SMARTCARD_InvalidInput;
            }
            break;
        case kSMARTCARD_SetupT0Mode:
            /* Set transport protocol type to T=0. */
            if (!SMARTCARD_USIM_SetTransferType(base, context, kSMARTCARD_SetupT0Mode))
            {
                status = kStatus_SMARTCARD_InvalidInput;
            }
            break;
        case kSMARTCARD_SetupT1Mode:
            /* Set transport protocol type to T=1. */
            if (!SMARTCARD_USIM_SetTransferType(base, context, kSMARTCARD_SetupT1Mode))
            {
                status = kStatus_SMARTCARD_InvalidInput;
            }
            break;
        case kSMARTCARD_EnableReceiverMode:
            /* Enable RDT interrupt */
            base->IER |= USIM_IER_RDR_MASK;
            break;
        case kSMARTCARD_DisableReceiverMode:
            /* Disable RDT interrupt */
            base->IER &= ~USIM_IER_RDR_MASK;
            break;
        case kSMARTCARD_EnableTransmitterMode:
            /* Enable TDR interrupt */
            base->IER |= USIM_IER_TDR_MASK;
            break;
        case kSMARTCARD_DisableTransmitterMode:
            /* Disable TDR interrupt */
            base->IER &= ~USIM_IER_TDR_MASK;
            break;
        case kSMARTCARD_ResetWaitTimeMultiplier:
            /* Reset Wait Timer Multiplier
             * EMV Formula : WTX x (11 + ((2^BWI + 1) x 960 x D)) */
            temp32 = ((uint8_t)param) *
                     (11u + ((((uint32_t)1u << context->cardParams.BWI) + 1u) * 960u * context->cardParams.currentD));
            base->BWTR = temp32 - SMARTCARD_T1_BWT_ADJUSTMENT;
            /* Set flag to SMARTCARD context accordingly */
            if (param > 1u)
            {
                context->wtxRequested = true;
            }
            else
            {
                context->wtxRequested = false;
            }
            break;
        default:
            status = kStatus_SMARTCARD_InvalidInput;
            break;
    }
    return status;
}

/*!
 * brief Handles initial TS character timer time-out event.
 *
 * param base The USIM peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 */
void SMARTCARD_USIM_TSExpiryCallback(USIM_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return;
    }
#if defined(FSL_FEATURE_SOC_CTIMER_COUNT) && FSL_FEATURE_SOC_CTIMER_COUNT
    /* Clear the status flags that were set */
    CTIMER0->IR = CTIMER0->IR;
    /* Stop TS timer */
    SMARTCARD_USIM_TimerStop();
#endif /* FSL_FEATURE_SOC_CTIMER_COUNT */
    /* Set timer has expired */
    context->timersState.initCharTimerExpired = true;
    context->transferState                    = kSMARTCARD_IdleState;
    /* Un-block the caller */
    SMARTCARD_USIM_CompleteReceiveData(base, context);

    return;
}
