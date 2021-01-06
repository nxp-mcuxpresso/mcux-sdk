/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_esai.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.esai"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*!@brief _esai_transfer_state */
enum
{
    kESAI_Busy = 0x0U, /*!< ESAI is busy */
    kESAI_Idle,        /*!< Transfer is done. */
    kESAI_Error        /*!< Transfer error occurred. */
};

/*! @brief Typedef for esai tx interrupt handler. */
typedef void (*esai_tx_isr_t)(ESAI_Type *base, esai_handle_t *esaiHandle);

/*! @brief Typedef for esai rx interrupt handler. */
typedef void (*esai_rx_isr_t)(ESAI_Type *base, esai_handle_t *esaiHandle);

/*! @brief Slot number to slot mask number */
#define SLOT_TO_MASK(slot) ((1UL << (slot)) - 1U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Set customer defined audio protocol for tx section.
 *
 * This API sets the audio protocol defined by users.
 *
 * @param base ESAI base pointer.
 * @param protocol ESAI protocol define structure pointer.
 */
static void ESAI_SetCustomerProtocol(ESAI_Type *base,
                                     esai_protocol_t fmt,
                                     esai_customer_protocol_t *protocol,
                                     bool isTx);

/*!
 * @brief sends a piece of data in non-blocking way.
 *
 * @param base ESAI base pointer
 * @param channel Data channel used.
 * @param bitWidth How many bits in a audio word, usually 8/16/24/32 bits.
 * @param buffer Pointer to the data to be written.
 * @param size Bytes to be written.
 */
static void ESAI_WriteNonBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size);

/*!
 * @brief Receive a piece of data in non-blocking way.
 *
 * @param base ESAI base pointer
 * @param channel Data channel used.
 * @param bitWidth How many bits in a audio word, usually 8/16/24/32 bits.
 * @param buffer Pointer to the data to be read.
 * @param size Bytes to be read.
 */
static void ESAI_ReadNonBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!@brief ESAI handle pointer */
static esai_handle_t *s_esaiHandle[FSL_FEATURE_SOC_ESAI_COUNT][2];
/* Base pointer array */
static ESAI_Type *const s_esaiBases[] = ESAI_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_esaiClock[] = ESAI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/* IRQ number array */
static const IRQn_Type s_esaiTxIRQ[] = ESAI_IRQS;
static const IRQn_Type s_esaiRxIRQ[] = ESAI_IRQS;
/*! @brief Pointer to tx IRQ handler for each instance. */
static esai_tx_isr_t s_esaiTxIsr;
/*! @brief Pointer to tx IRQ handler for each instance. */
static esai_rx_isr_t s_esaiRxIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void ESAI_SetCustomerProtocol(ESAI_Type *base,
                                     esai_protocol_t fmt,
                                     esai_customer_protocol_t *protocol,
                                     bool isTx)
{
    switch (fmt)
    {
        case kESAI_BusLeftJustified:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = false;
            protocol->fsEarly        = false;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            protocol->slotNum        = 2;
            break;
        case kESAI_BusRightJustified:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = true;
            protocol->fsEarly        = false;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            protocol->slotNum        = 2;
            break;
        case kESAI_BusI2S:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = false;
            protocol->fsEarly        = true;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            protocol->slotNum        = 2;
            break;
        case kESAI_BusPCMA:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = false;
            protocol->fsEarly        = true;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            protocol->slotNum        = 2;
            break;
        case kESAI_BusPCMB:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = false;
            protocol->fsEarly        = false;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            protocol->slotNum        = 2;
            break;
        case kESAI_BusTDM:
            protocol->mode           = kESAI_NetworkMode;
            protocol->dataAlign      = false;
            protocol->fsEarly        = true;
            protocol->shiftDirection = kESAI_ShifterMSB;
            protocol->fsOneBit       = false;
            protocol->ifZeroPading   = true;
            break;
        default:
            assert(false);
            break;
    }

    if (isTx)
    {
        base->TCR &= ~(ESAI_TCR_PADC_MASK | ESAI_TCR_TFSR_MASK | ESAI_TCR_TFSL_MASK | ESAI_TCR_TWA_MASK |
                       ESAI_TCR_TMOD_MASK | ESAI_TCR_TSHFD_MASK);
        /* Set the direction for shifter */
        base->TCR |= ESAI_TCR_PADC(protocol->ifZeroPading) | ESAI_TCR_TFSR(protocol->fsEarly) |
                     ESAI_TCR_TFSL(protocol->fsOneBit) | ESAI_TCR_TWA(protocol->dataAlign) |
                     ESAI_TCR_TMOD(protocol->mode) | ESAI_TCR_TSHFD(protocol->shiftDirection);

        base->TCCR &= ~ESAI_TCCR_TDC_MASK;
        base->TCCR |= ESAI_TCCR_TDC((uint32_t)protocol->slotNum - 1U);

        /* Set slot mask */
        ESAI_TxSetSlotMask(base, SLOT_TO_MASK(protocol->slotNum));
    }
    else
    {
        base->RCR &=
            ~(ESAI_RCR_RFSR_MASK | ESAI_RCR_RFSL_MASK | ESAI_RCR_RWA_MASK | ESAI_RCR_RMOD_MASK | ESAI_RCR_RSHFD_MASK);
        /* Set the direction for shifter */
        base->RCR |= ESAI_RCR_RFSR(protocol->fsEarly) | ESAI_RCR_RFSL(protocol->fsOneBit) |
                     ESAI_RCR_RWA(protocol->dataAlign) | ESAI_RCR_RMOD(protocol->mode) |
                     ESAI_RCR_RSHFD(protocol->shiftDirection);

        base->RCCR &= ~ESAI_RCCR_RDC_MASK;
        base->RCCR |= ESAI_RCCR_RDC(protocol->slotNum - 1UL);

        /* Set slot mask */
        EASI_RxSetSlotMask(base, SLOT_TO_MASK(protocol->slotNum));
    }
}

void ESAI_AnalysisSlot(esai_slot_format_t slotFormat, uint8_t *slotLen, uint8_t *dataLen)
{
    assert((slotLen != NULL) && (dataLen != NULL));

    switch (slotFormat)
    {
        case kESAI_SlotLen8WordLen8:
            *slotLen = 8U;
            *dataLen = 8U;
            break;
        case kESAI_SlotLen12WordLen12:
            *slotLen = 12U;
            *dataLen = 12U;
            break;
        case kESAI_SlotLen16WordLen8:
            *slotLen = 16U;
            *dataLen = 8U;
            break;
        case kESAI_SlotLen16WordLen12:
            *slotLen = 16U;
            *dataLen = 12U;
            break;
        case kESAI_SlotLen16WordLen16:
            *slotLen = 16U;
            *dataLen = 16U;
            break;
        case kESAI_SlotLen20WordLen8:
            *slotLen = 20U;
            *dataLen = 8U;
            break;
        case kESAI_SlotLen20WordLen12:
            *slotLen = 20U;
            *dataLen = 12U;
            break;
        case kESAI_SlotLen20WordLen16:
            *slotLen = 20U;
            *dataLen = 16U;
            break;
        case kESAI_SlotLen24WordLen8:
            *slotLen = 24U;
            *dataLen = 8U;
            break;
        case kESAI_SlotLen24WordLen12:
            *slotLen = 24U;
            *dataLen = 12U;
            break;
        case kESAI_SlotLen24WordLen16:
            *slotLen = 24U;
            *dataLen = 16U;
            break;
        case kESAI_SlotLen24WordLen20:
            *slotLen = 24U;
            *dataLen = 20U;
            break;
        case kESAI_SlotLen24WordLen24:
            *slotLen = 24U;
            *dataLen = 24U;
            break;
        case kESAI_SlotLen32WordLen8:
            *slotLen = 32U;
            *dataLen = 8U;
            break;
        case kESAI_SlotLen32WordLen12:
            *slotLen = 32U;
            *dataLen = 12U;
            break;
        case kESAI_SlotLen32WordLen16:
            *slotLen = 32U;
            *dataLen = 16U;
            break;
        case kESAI_SlotLen32WordLen20:
            *slotLen = 32U;
            *dataLen = 20U;
            break;
        case kESAI_SlotLen32WordLen24:
            *slotLen = 32U;
            *dataLen = 24U;
            break;
        default:
            assert(false);
            break;
    }
}

uint32_t ESAI_GetInstance(ESAI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < (uint32_t)FSL_FEATURE_SOC_ESAI_COUNT; instance++)
    {
        if (s_esaiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < (uint32_t)FSL_FEATURE_SOC_ESAI_COUNT);

    return instance;
}

static void ESAI_WriteNonBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size)
{
    uint32_t i           = 0;
    uint8_t j            = 0;
    uint8_t bytesPerWord = (uint8_t)(bitWidth / 8U);
    uint32_t data        = 0;
    uint32_t temp        = 0;

    for (i = 0; i < size / bytesPerWord; i++)
    {
        for (j = 0; j < bytesPerWord; j++)
        {
            temp = (uint32_t)(*buffer);
            data |= (temp << (8U * j));
            buffer++;
        }
        base->ETDR = data;
        data       = 0;
    }
}

static void ESAI_ReadNonBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size)
{
    uint32_t i           = 0;
    uint8_t j            = 0;
    uint8_t bytesPerWord = (uint8_t)(bitWidth / 8U);
    uint32_t data        = 0;

    for (i = 0; i < size / bytesPerWord; i++)
    {
        data = base->ERDR;
        for (j = 0; j < bytesPerWord; j++)
        {
            *buffer = (uint8_t)(data >> (8U * j)) & 0xFFU;
            buffer++;
        }
    }
}

/*!
 * brief Initializes the ESAI peripheral.
 *
 * Ungates the ESAI clock, resets the module, and configures ESAI with a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * ESAI_GetDefaultConfig().
 *
 * note  This API should be called at the beginning of the application to use
 * the ESAI driver. Otherwise, accessing the ESAI module can cause a hard fault
 * because the clock is not enabled.
 *
 * param base ESAI base pointer
 * param config ESAI configuration structure.
 */
void ESAI_Init(ESAI_Type *base, esai_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    (void)CLOCK_EnableClock(s_esaiClock[ESAI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable ESAI logic */
    ESAI_Enable(base, true);

    /* Reset ESAI internal logic */
    ESAI_Reset(base);

    /* ESAI section personal reset, this reset Tx and Rx section at the same time */
    base->PCRC = 0U;
    base->PRRC = 0U;

    /* Automatically init while FIFO enabled */
    base->TFCR |= ESAI_TFCR_TIEN_MASK;

    /* Reset ESAI tx and rx FIFO */
    ESAI_TxReset(base);
    ESAI_RxReset(base);

    /* Clear the Transmit and Rececive Slot Mask */
    ESAI_TxSetSlotMask(base, 0U);
    EASI_RxSetSlotMask(base, 0U);

    /* Set sync mode */
    base->SAICR &= ~ESAI_SAICR_SYN_MASK;
    base->SAICR |= ESAI_SAICR_SYN(config->syncMode);

    /* Set master or slave */
    if (config->master == kESAI_Master)
    {
        base->TCCR |= (ESAI_TCCR_TFSD_MASK | ESAI_TCCR_TCKD_MASK);
        if (config->syncMode == kESAI_ModeAsync)
        {
            base->RCCR |= (ESAI_RCCR_RFSD_MASK | ESAI_RCCR_RCKD_MASK);
        }
    }
    else
    {
        base->TCCR &= ~(ESAI_TCCR_TFSD_MASK | ESAI_TCCR_TCKD_MASK);
        if (config->syncMode == kESAI_ModeAsync)
        {
            base->RCCR &= ~(ESAI_RCCR_RFSD_MASK | ESAI_RCCR_RCKD_MASK);
        }
    }

    /* Set HCLK direction */
    base->TCCR |= ESAI_TCCR_THCKD(config->txHckDirection);
    if (config->syncMode == kESAI_ModeAsync)
    {
        base->RCCR |= ESAI_RCCR_RHCKD(config->rxHckDirection);
        base->ECR |= ESAI_ECR_ERI_MASK;
    }

    /* Set HCLK input and output source */
    base->ECR &= 0xFFF0FFFFU;
    base->ECR |=
        (((uint32_t)config->txHckSource << ESAI_ECR_ETI_SHIFT) | ((uint32_t)config->rxHckSource << ESAI_ECR_ERI_SHIFT) |
         ((uint32_t)config->txHckOutputSource << ESAI_ECR_ETO_SHIFT) |
         ((uint32_t)config->rxHckOutputSource << ESAI_ECR_ERO_SHIFT));

    /* Set the audio protocol */
    ESAI_SetCustomerProtocol(base, config->txProtocol, &config->txCustomer, true);
    if (config->txProtocol == kESAI_BusI2S)
    {
        config->txFsPolarity = kESAI_ClockActiveLow;
    }
    base->TCCR &= ~(ESAI_TCCR_THCKP_MASK | ESAI_TCCR_TFSP_MASK | ESAI_TCCR_TCKP_MASK);
    base->TCCR |= (ESAI_TCCR_THCKP(config->txHckPolarity) | ESAI_TCCR_TFSP(config->txFsPolarity) |
                   ESAI_TCCR_TCKP(config->txSckPolarity));

    ESAI_SetCustomerProtocol(base, config->rxProtocol, &config->rxCustomer, false);
    if (config->rxProtocol == kESAI_BusI2S)
    {
        config->rxFsPolarity = kESAI_ClockActiveLow;
    }
    base->RCCR &= ~(ESAI_RCCR_RHCKP_MASK | ESAI_RCCR_RFSP_MASK | ESAI_RCCR_RCKP_MASK);
    base->RCCR |= (ESAI_RCCR_RHCKP(config->rxHckPolarity) | ESAI_RCCR_RFSP(config->rxFsPolarity) |
                   ESAI_RCCR_RCKP(config->rxSckPolarity));

    /* Set watermark */
    base->TFCR &= ~ESAI_TFCR_TFWM_MASK;
    base->TFCR |= ESAI_TFCR_TFWM(config->txWatermark);
    base->RFCR &= ~ESAI_RFCR_RFWM_MASK;
    base->RFCR |= ESAI_RFCR_RFWM(config->rxWatermark);

    /* Set the pin connection */
    base->PCRC = 0xFFFU;
    base->PRRC = 0xFFFU;
}

/*!
 * brief De-initializes the ESAI peripheral.
 *
 * This API gates the ESAI clock. The ESAI module can't operate unless ESAI_Init
 * is called to enable the clock.
 *
 * param base ESAI base pointer
 */
void ESAI_Deinit(ESAI_Type *base)
{
    ESAI_TxEnable(base, 0U);
    ESAI_RxEnable(base, 0U);

    /* Disconnect all pins */
    base->PCRC = 0U;
    base->PRRC = 0U;
    ESAI_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    (void)CLOCK_DisableClock(s_esaiClock[ESAI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Sets the ESAI configuration structure to default values.
 *
 * This API initializes the configuration structure for use in ESAI_TxConfig().
 * The initialized structure can remain unchanged in ESAI_Init(), or it can be modified
 *  before calling ESAI_Init().
 *
 * param config pointer to master configuration structure
 */
void ESAI_GetDefaultConfig(esai_config_t *config)
{
    (void)memset(config, 0, sizeof(esai_config_t));

    config->syncMode          = kESAI_ModeSync;
    config->txProtocol        = kESAI_BusLeftJustified;
    config->rxProtocol        = kESAI_BusLeftJustified;
    config->master            = kESAI_Master;
    config->txHckDirection    = kESAI_ClockOutput;
    config->rxHckDirection    = kESAI_ClockOutput;
    config->txHckSource       = kESAI_HckSourceExternal;
    config->rxHckSource       = kESAI_HckSourceExternal;
    config->txHckOutputSource = kESAI_HckSourceInternal;
    config->rxHckOutputSource = kESAI_HckSourceInternal;
    config->txHckPolarity     = kESAI_ClockActiveHigh;
    config->txFsPolarity      = kESAI_ClockActiveHigh;
    config->txSckPolarity     = kESAI_ClockActiveLow;
    config->rxHckPolarity     = kESAI_ClockActiveHigh;
    config->rxFsPolarity      = kESAI_ClockActiveHigh;
    config->rxSckPolarity     = kESAI_ClockActiveLow;
    config->txWatermark       = 64;
    config->rxWatermark       = 64;
}

/*!
 * brief Reset ESAI all tx sections.
 *
 * This API only resets the core logic of tx and all tx sections.
 *
 * param base ESAI base pointer
 */
void ESAI_TxReset(ESAI_Type *base)
{
    uint32_t val = 0;

    val = base->TFCR;

    /*disable transmit FIFO*/
    val &= ~ESAI_TFCR_TFE_MASK;

    /* Disable Tx FIFOs */
    val &= ~(ESAI_TFCR_TE0_MASK | ESAI_TFCR_TE1_MASK | ESAI_TFCR_TE2_MASK | ESAI_TFCR_TE3_MASK | ESAI_TFCR_TE4_MASK |
             ESAI_TFCR_TE5_MASK);

    /* Reset Tx FIFO */
    val |= ESAI_TFCR_TFR_MASK;
    base->TFCR = val;

    /* Clear the tx FIFO reset */
    base->TFCR &= ~ESAI_TFCR_TFR_MASK;

    /* Set ESAI Tx to personal reset */
    base->TCR &= ~(ESAI_TCR_TE0_MASK | ESAI_TCR_TE1_MASK | ESAI_TCR_TE2_MASK | ESAI_TCR_TE3_MASK | ESAI_TCR_TE4_MASK |
                   ESAI_TCR_TE5_MASK);
    base->TCR |= ESAI_TCR_TPR_MASK;

    /* Clear ESAI Rx */
    base->TCR &= ~ESAI_TCR_TPR_MASK;
}

/*!
 * brief Reset ESAI all rx sections.
 *
 * This API only resets the core logic of rx and all rx sections.
 *
 * param base ESAI base pointer
 */
void ESAI_RxReset(ESAI_Type *base)
{
    uint32_t val = 0;

    val = base->RFCR;

    /*disable transmit FIFO*/
    val &= ~ESAI_RFCR_RFE_MASK;

    /* Disable Tx FIFOs */
    val &= ~(ESAI_RFCR_RE0_MASK | ESAI_RFCR_RE1_MASK | ESAI_RFCR_RE2_MASK | ESAI_RFCR_RE3_MASK);

    /* Reset Tx FIFO */
    val |= ESAI_RFCR_RFR_MASK;
    base->RFCR = val;

    /* Clear the tx FIFO reset */
    base->RFCR &= ~ESAI_RFCR_RFR_MASK;

    /* Set ESAI Tx to personal reset */
    base->RCR &= ~(ESAI_RCR_RE0_MASK | ESAI_RCR_RE1_MASK | ESAI_RCR_RE2_MASK | ESAI_RCR_RE3_MASK);
    base->RCR |= ESAI_RCR_RPR_MASK;
    base->RCR &= ~ESAI_RCR_RPR_MASK;
}

/*!
 * brief Enables/disables ESAI Tx.
 *
 * param base ESAI base pointer
 * param sectionMap Which sections need to be enabled. 0 means all section disabled. This parameter can be a
 * combination of each sections, every section N is 2^N in section map.
 */
void ESAI_TxEnable(ESAI_Type *base, uint8_t sectionMap)
{
    uint32_t val = 0;

    /* Wait for Tx initialized */
    if ((base->TFCR & ESAI_TFCR_TIEN_MASK) != 0U)
    {
        while ((base->ESR & ESAI_ESR_TINIT_MASK) != 0U)
        {
        }
    }

    /* Set TCR regsiter */
    val = base->TCR & ~(ESAI_TCR_TE5_MASK | ESAI_TCR_TE4_MASK | ESAI_TCR_TE3_MASK | ESAI_TCR_TE2_MASK |
                        ESAI_TCR_TE1_MASK | ESAI_TCR_TE0_MASK);
    val |= (sectionMap & 0x3FUL) << ESAI_TCR_TE0_SHIFT;
    base->TCR = val;

    /* Set TFCR register */
    val = base->TFCR & ~(ESAI_TFCR_TE5_MASK | ESAI_TFCR_TE4_MASK | ESAI_TFCR_TE3_MASK | ESAI_TFCR_TE2_MASK |
                         ESAI_TFCR_TE1_MASK | ESAI_TFCR_TE0_MASK);
    val |= ((sectionMap & 0x3FUL) << ESAI_TFCR_TE0_SHIFT);
    base->TFCR = val;
    base->TFCR |= ESAI_TFCR_TFE_MASK;
}

/*!
 * brief Enables/disables ESAI Rx.
 *
 * param base ESAI base pointer
 * param sectionMap Which sections need to be enabled. 0 means all section disabled. This parameter can be a
 * combination of each sections, every section N is 2^N in section map.
 */
void ESAI_RxEnable(ESAI_Type *base, uint8_t sectionMap)
{
    uint32_t val = 0;

    /* Set RCR register */
    val = base->RCR & ~(ESAI_RCR_RE3_MASK | ESAI_RCR_RE2_MASK | ESAI_RCR_RE1_MASK | ESAI_RCR_RE0_MASK);
    val |= (sectionMap & 0xFUL) << ESAI_RCR_RE0_SHIFT;
    base->RCR = val;

    /* Set RFCR regsiter */
    val = base->RFCR & ~(ESAI_RFCR_RE3_MASK | ESAI_RFCR_RE2_MASK | ESAI_RFCR_RE1_MASK | ESAI_RFCR_RE0_MASK);
    val |= ((sectionMap & 0xFUL) << ESAI_RFCR_RE0_SHIFT);
    base->RFCR = val;
    base->RFCR |= ESAI_RFCR_RFE_MASK;
}

/*!
 * brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * param base ESAI base pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hckSourceClockHz HCK source clock frequency in Hz.
 */
void ESAI_TxSetFormat(ESAI_Type *base, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz)
{
    uint8_t slotNum = (uint8_t)((base->TCCR & ESAI_TCCR_TDC_MASK) >> ESAI_TCCR_TDC_SHIFT) + 1U;
    uint8_t dataLen = 0U, slotLen = 0U;
    uint32_t sck  = 0U;
    uint32_t temp = hckSourceClockHz / (hckClockHz * 2U);

    /* Get ESAI slot length and data length */
    ESAI_AnalysisSlot(format->slotType, &slotLen, &dataLen);
    sck = (uint32_t)format->sampleRate_Hz * slotLen * slotNum;

    /* Set MSB bit of the audio data */
    base->TCR &= ~ESAI_TCR_TSWS_MASK;
    base->TCR |= ESAI_TCR_TSWS(format->slotType);

    /* Set word length and slot length */
    base->TFCR &= ~ESAI_TFCR_TWA_MASK;
    base->TFCR |= ESAI_TFCR_TWA((32UL - dataLen) / 4UL);

    /* Set clock divider */
    base->TCCR &= ~(ESAI_TCCR_TFP_MASK | ESAI_TCCR_TPM_MASK);
    base->TCCR |= ESAI_TCCR_TFP(hckClockHz / sck - 1U);

    /* Set HCKT clock divider */
    if (temp > 256U)
    {
        base->TCCR &= ~ESAI_TCCR_TPSR_MASK;
        base->TCCR |= ESAI_TCCR_TPM((temp >> 3U) - 1U);
    }
    else
    {
        base->TCCR |= ESAI_TCCR_TPSR_MASK;
        base->TCCR |= ESAI_TCCR_TPM(temp - 1U);
    }
}

/*!
 * brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * param base ESAI base pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hckSourceClockHz HCK source clock frequency in Hz.
 */
void ESAI_RxSetFormat(ESAI_Type *base, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz)

{
    uint8_t slotNum = (uint8_t)((base->RCCR & ESAI_RCCR_RDC_MASK) >> ESAI_RCCR_RDC_SHIFT) + 1U;
    uint8_t dataLen = 0U, slotLen = 0U;
    uint32_t sck  = 0U;
    uint32_t temp = hckSourceClockHz / (hckClockHz * 2U);

    /* Get ESAI slot length and data length */
    ESAI_AnalysisSlot(format->slotType, &slotLen, &dataLen);
    sck = (uint32_t)format->sampleRate_Hz * slotLen * slotNum;

    /* MSB bit of the audio data */
    base->RCR &= ~ESAI_RCR_RSWS_MASK;
    base->RCR |= ESAI_RCR_RSWS(format->slotType);

    /* Set word length and slot length */
    base->RFCR &= ~ESAI_RFCR_RWA_MASK;
    base->RFCR |= ESAI_RFCR_RWA((32UL - dataLen) / 4UL);

    /* Only async mode needs to set the clock divider */
    if ((base->SAICR & ESAI_SAICR_SYN_MASK) == 0U)
    {
        /* Set clock divider */
        base->RCCR &= ~(ESAI_RCCR_RFSP_MASK | ESAI_RCCR_RPM_MASK);
        base->RCCR |= ESAI_RCCR_RFP(hckClockHz / sck - 1U);

        /* Set HCKT clock divider */
        if (temp > 256U)
        {
            base->RCCR &= ~ESAI_RCCR_RPSR_MASK;
            base->RCCR |= ESAI_RCCR_RPM((temp >> 3U) - 1U);
        }
        else
        {
            base->RCCR |= ESAI_RCCR_RPSR_MASK;
            base->RCCR |= ESAI_RCCR_RPM(temp - 1U);
        }
    }
}

/*!
 * brief Sends data using a blocking method.
 *
 * note This function blocks by polling until data is ready to be sent.
 *
 * param base ESAI base pointer.
 * param bitWidth How many bits in a audio word, usually 8/16/24 bits.
 * param buffer Pointer to the data to be written.
 * param size Bytes to be written.
 */
void ESAI_WriteBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size)
{
    uint32_t i           = 0;
    uint8_t bytesPerWord = (uint8_t)bitWidth / 8U;

    while (i < size)
    {
        /* Wait until it can write data */
        while ((ESAI_GetStatusFlag(base) & (uint32_t)kESAI_TransmitFIFOEmptyFlag) == 0U)
        {
        }

        ESAI_WriteNonBlocking(base, bitWidth, buffer, bytesPerWord);
        buffer = (uint8_t *)((uint32_t)(buffer) + bytesPerWord);
        i += bytesPerWord;
    }

    /* Wait until the last data is sent */
    while ((base->SAISR & ESAI_SAISR_TDE_MASK) == 0U)
    {
    }
}

/*!
 * brief Receives data using a blocking method.
 *
 * note This function blocks by polling until data is ready to be sent.
 *
 * param base ESAI base pointer.
 * param bitWidth How many bits in a audio word, usually 8/16/24 bits.
 * param buffer Pointer to the data to be read.
 * param size Bytes to be read.
 */
void ESAI_ReadBlocking(ESAI_Type *base, uint32_t bitWidth, uint8_t *buffer, uint32_t size)
{
    uint32_t i           = 0;
    uint8_t bytesPerWord = (uint8_t)bitWidth / 8U;

    while (i < size)
    {
        /* Wait until data is received */
        while ((ESAI_GetStatusFlag(base) & (uint32_t)kESAI_ReceiveFIFOFullFlag) == 0U)
        {
        }

        ESAI_ReadNonBlocking(base, bitWidth, buffer, bytesPerWord);
        buffer = (uint8_t *)((uint32_t)(buffer) + bytesPerWord);
        i += bytesPerWord;
    }
}

/*!
 * brief Initializes the ESAI Tx handle.
 *
 * This function initializes the Tx handle for ESAI Tx transactional APIs. Call
 * this function one time to get the handle initialized.
 *
 * param base ESAI base pointer
 * param handle ESAI handle pointer.
 * param callback pointer to user callback function
 * param userData user parameter passed to the callback function
 */
void ESAI_TransferTxCreateHandle(ESAI_Type *base,
                                 esai_handle_t *handle,
                                 esai_transfer_callback_t callback,
                                 void *userData)
{
    assert(handle != NULL);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    s_esaiHandle[ESAI_GetInstance(base)][0] = handle;

    handle->callback  = callback;
    handle->userData  = userData;
    handle->watermark = (uint8_t)((base->TFCR & ESAI_TFCR_TFWM_MASK) >> ESAI_TFCR_TFWM_SHIFT);

    /* Set the isr pointer */
    s_esaiTxIsr = ESAI_TransferTxHandleIRQ;

    /* Enable Tx irq */
    (void)EnableIRQ(s_esaiTxIRQ[ESAI_GetInstance(base)]);
}

/*!
 * brief Initializes the ESAI Rx handle.
 *
 * This function initializes the Rx handle for ESAI Rx transactional APIs. Call
 * this function one time to get the handle initialized.
 *
 * param base ESAI base pointer.
 * param handle ESAI handle pointer.
 * param callback pointer to user callback function
 * param userData user parameter passed to the callback function
 */
void ESAI_TransferRxCreateHandle(ESAI_Type *base,
                                 esai_handle_t *handle,
                                 esai_transfer_callback_t callback,
                                 void *userData)
{
    assert(handle != NULL);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    s_esaiHandle[ESAI_GetInstance(base)][1] = handle;

    handle->callback  = callback;
    handle->userData  = userData;
    handle->watermark = (uint8_t)((base->RFCR & ESAI_RFCR_RFWM_MASK) >> ESAI_RFCR_RFWM_SHIFT);

    /* Set the isr pointer */
    s_esaiRxIsr = ESAI_TransferRxHandleIRQ;

    /* Enable Rx irq */
    (void)EnableIRQ(s_esaiRxIRQ[ESAI_GetInstance(base)]);
}

/*!
 * brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * param base ESAI base pointer.
 * param handle ESAI handle pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hckSourceClockHz HCK clock source frequency in Hz.
 * return Status of this function. Return value is one of status_t.
 */
status_t ESAI_TransferTxSetFormat(
    ESAI_Type *base, esai_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz)
{
    assert(handle != NULL);

    if ((hckClockHz < (uint32_t)format->sampleRate_Hz) || (hckSourceClockHz < (uint32_t)format->sampleRate_Hz))
    {
        return kStatus_InvalidArgument;
    }

    /* Copy format to handle */
    ESAI_AnalysisSlot(format->slotType, &handle->slotLen, &handle->bitWidth);
    handle->sectionMap = format->sectionMap;

    ESAI_TxSetFormat(base, format, hckClockHz, hckSourceClockHz);

    return kStatus_Success;
}

/*!
 * brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred.
 *
 * param base ESAI base pointer.
 * param handle ESAI handle pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hckSourceClockHz HCK clock source frequency in Hz.
 * return Status of this function. Return value is one of status_t.
 */
status_t ESAI_TransferRxSetFormat(
    ESAI_Type *base, esai_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hckSourceClockHz)
{
    assert(handle != NULL);

    if ((hckClockHz < (uint32_t)format->sampleRate_Hz) || (hckSourceClockHz < (uint32_t)format->sampleRate_Hz))
    {
        return kStatus_InvalidArgument;
    }

    /* Copy format to handle */
    ESAI_AnalysisSlot(format->slotType, &handle->slotLen, &handle->bitWidth);
    handle->sectionMap = format->sectionMap;

    ESAI_RxSetFormat(base, format, hckClockHz, hckSourceClockHz);

    return kStatus_Success;
}

/*!
 * brief Performs an interrupt non-blocking send transfer on ESAI.
 *
 * note This API returns immediately after the transfer initiates.
 * Call the ESAI_TxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_ESAI_Busy, the transfer
 * is finished.
 *
 * param base ESAI base pointer
 * param handle pointer to esai_handle_t structure which stores the transfer state
 * param xfer pointer to esai_transfer_t structure
 * retval kStatus_Success Successfully started the data receive.
 * retval kStatus_ESAI_TxBusy Previous receive still not finished.
 * retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t ESAI_TransferSendNonBlocking(ESAI_Type *base, esai_handle_t *handle, esai_transfer_t *xfer)
{
    assert(handle != NULL);

    uint32_t i = 0;

    /* Check if the queue is full */
    if (handle->esaiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_ESAI_QueueFull;
    }

    /* Add into queue */
    handle->transferSize[handle->queueUser]       = xfer->dataSize;
    handle->esaiQueue[handle->queueUser].data     = xfer->data;
    handle->esaiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                             = (handle->queueUser + 1U) % ESAI_XFER_QUEUE_SIZE;

    /* Set the state to busy */
    handle->state = kESAI_Busy;

    /* Use FIFO request interrupt and fifo error*/
    ESAI_TxEnableInterrupts(base, kESAI_TransmitInterruptEnable);

    if ((base->TFSR & ESAI_TFSR_TFCNT_MASK) == 0U)
    {
        /* Write first word for all channels*/
        for (i = 0; i < 12U; i++)
        {
            ESAI_WriteData(base, 0);
            ESAI_WriteData(base, 0);
        }
    }

    /* Enable Tx transfer */
    ESAI_TxEnable(base, handle->sectionMap);

    return kStatus_Success;
}

/*!
 * brief Performs an interrupt non-blocking receive transfer on ESAI.
 *
 * note This API returns immediately after the transfer initiates.
 * Call the ESAI_RxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_ESAI_Busy, the transfer
 * is finished.
 *
 * param base ESAI base pointer
 * param handle pointer to esai_handle_t structure which stores the transfer state
 * param xfer pointer to esai_transfer_t structure
 * retval kStatus_Success Successfully started the data receive.
 * retval kStatus_ESAI_RxBusy Previous receive still not finished.
 * retval kStatus_InvalidArgument The input parameter is invalid.
 */
status_t ESAI_TransferReceiveNonBlocking(ESAI_Type *base, esai_handle_t *handle, esai_transfer_t *xfer)
{
    assert(handle != NULL);

    /* Check if the queue is full */
    if (handle->esaiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_ESAI_QueueFull;
    }

    /* Add into queue */
    handle->transferSize[handle->queueUser]       = xfer->dataSize;
    handle->esaiQueue[handle->queueUser].data     = xfer->data;
    handle->esaiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                             = (handle->queueUser + 1U) % ESAI_XFER_QUEUE_SIZE;

    /* Set state to busy */
    handle->state = kESAI_Busy;

    /* Use FIFO request interrupt and fifo error*/
    ESAI_RxEnableInterrupts(base, kESAI_TransmitInterruptEnable);

    /* Enable Rx transfer */
    ESAI_RxEnable(base, handle->sectionMap);

    return kStatus_Success;
}

/*!
 * brief Gets a set byte count.
 *
 * param base ESAI base pointer.
 * param handle pointer to esai_handle_t structure which stores the transfer state.
 * param count Bytes count sent.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ESAI_TransferGetSendCount(ESAI_Type *base, esai_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kESAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] - handle->esaiQueue[handle->queueDriver].dataSize);
    }

    return status;
}

/*!
 * brief Gets a received byte count.
 *
 * param base ESAI base pointer.
 * param handle pointer to esai_handle_t structure which stores the transfer state.
 * param count Bytes count received.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ESAI_TransferGetReceiveCount(ESAI_Type *base, esai_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kESAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] - handle->esaiQueue[handle->queueDriver].dataSize);
    }

    return status;
}

/*!
 * brief Aborts the current send.
 *
 * note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base ESAI base pointer.
 * param handle pointer to esai_handle_t structure which stores the transfer state.
 */
void ESAI_TransferAbortSend(ESAI_Type *base, esai_handle_t *handle)
{
    assert(handle != NULL);

    /* Stop Tx transfer and disable interrupt */
    ESAI_TxEnable(base, 0U);

    /* Use FIFO request interrupt and fifo error */
    ESAI_TxDisableInterrupts(base, kESAI_TransmitInterruptEnable);

    handle->state = kESAI_Idle;

    /* Clear the queue */
    (void)memset(handle->esaiQueue, 0, sizeof(esai_transfer_t) * ESAI_XFER_QUEUE_SIZE);
    handle->queueDriver = 0;
    handle->queueUser   = 0;
}

/*!
 * brief Aborts the current IRQ receive.
 *
 * note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base ESAI base pointer
 * param handle pointer to esai_handle_t structure which stores the transfer state.
 */
void ESAI_TransferAbortReceive(ESAI_Type *base, esai_handle_t *handle)
{
    assert(handle != NULL);

    /* Stop Tx transfer and disable interrupt */
    ESAI_RxEnable(base, 0U);

    /* Use FIFO request interrupt and fifo error */
    ESAI_RxDisableInterrupts(base, kESAI_TransmitInterruptEnable);

    handle->state = kESAI_Idle;

    /* Clear the queue */
    (void)memset(handle->esaiQueue, 0, sizeof(esai_transfer_t) * ESAI_XFER_QUEUE_SIZE);
    handle->queueDriver = 0;
    handle->queueUser   = 0;
}

/*!
 * brief Tx interrupt handler.
 *
 * param base ESAI base pointer.
 * param handle pointer to esai_handle_t structure.
 */
void ESAI_TransferTxHandleIRQ(ESAI_Type *base, esai_handle_t *handle)
{
    assert(handle != NULL);

    uint8_t *buffer  = handle->esaiQueue[handle->queueDriver].data;
    uint8_t dataSize = handle->bitWidth / 8U;

    /* Handle transfer */
    if ((ESAI_GetStatusFlag(base) & (uint32_t)kESAI_TransmitFIFOEmptyFlag) != 0U)
    {
        /* Judge if the data need to transmit is less than space */
        size_t size = MIN((handle->esaiQueue[handle->queueDriver].dataSize),
                          (size_t)(((uint32_t)FSL_FEATURE_ESAI_FIFO_SIZEn(base) - handle->watermark) * dataSize));

        /* Copy the data from esai buffer to FIFO */
        ESAI_WriteNonBlocking(base, handle->bitWidth, buffer, size);

        /* Update the internal counter */
        handle->esaiQueue[handle->queueDriver].dataSize -= size;
        handle->esaiQueue[handle->queueDriver].data =
            (uint8_t *)((uint32_t)handle->esaiQueue[handle->queueDriver].data + size);
    }

    /* If finished a block, call the callback function */
    if (handle->esaiQueue[handle->queueDriver].dataSize == 0U)
    {
        (void)memset(&handle->esaiQueue[handle->queueDriver], 0, sizeof(esai_transfer_t));
        handle->queueDriver = (handle->queueDriver + 1U) % ESAI_XFER_QUEUE_SIZE;
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_ESAI_TxIdle, handle->userData);
        }
    }

    /* If all data finished, just stop the transfer */
    if (handle->esaiQueue[handle->queueDriver].data == NULL)
    {
        /* Only async mode shall disable Tx */
        if ((base->SAICR & ESAI_SAICR_SYN_MASK) == 0U)
        {
            ESAI_TransferAbortSend(base, handle);
        }
    }
}

/*!
 * brief Tx interrupt handler.
 *
 * param base ESAI base pointer.
 * param handle pointer to esai_handle_t structure.
 */
void ESAI_TransferRxHandleIRQ(ESAI_Type *base, esai_handle_t *handle)
{
    assert(handle != NULL);

    uint8_t *buffer  = handle->esaiQueue[handle->queueDriver].data;
    uint8_t dataSize = handle->bitWidth / 8U;

    /* Handle transfer */
    if ((ESAI_GetStatusFlag(base) & (uint32_t)kESAI_ReceiveFIFOFullFlag) != 0U)
    {
        /* Judge if the data need to transmit is less than space */
        size_t size = MIN((handle->esaiQueue[handle->queueDriver].dataSize), (handle->watermark * (uint32_t)dataSize));

        /* Copy the data from esai buffer to FIFO */
        ESAI_ReadNonBlocking(base, handle->bitWidth, buffer, size);

        /* Update the internal counter */
        handle->esaiQueue[handle->queueDriver].dataSize -= size;
        handle->esaiQueue[handle->queueDriver].data =
            (uint8_t *)((uint32_t)handle->esaiQueue[handle->queueDriver].data + size);
    }

    /* If finished a block, call the callback function */
    if (handle->esaiQueue[handle->queueDriver].dataSize == 0U)
    {
        (void)memset(&handle->esaiQueue[handle->queueDriver], 0, sizeof(esai_transfer_t));
        handle->queueDriver = (handle->queueDriver + 1U) % ESAI_XFER_QUEUE_SIZE;
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_ESAI_RxIdle, handle->userData);
        }
    }

    /* If all data finished, just stop the transfer */
    if (handle->esaiQueue[handle->queueDriver].data == NULL)
    {
        ESAI_TransferAbortReceive(base, handle);
    }
}

#ifdef AUDIO__ESAI0
#define ESAI AUDIO__ESAI0
#endif
#ifdef ADMA__ESAI0
#define ESAI ADMA__ESAI0
#endif
#if defined(ESAI)
#define ESAI_DriverIRQHandler AUDIO_ESAI0_INT_IRQHandler
void ESAI_DriverIRQHandler(void);
void ESAI_DriverIRQHandler(void)
{
    /* Handle Rx operation */
    if (((ESAI_GetStatusFlag(ESAI) & (uint32_t)kESAI_ReceiveFIFOFullFlag) != 0U) &&
        ((ESAI->RCR & (uint32_t)kESAI_TransmitInterruptEnable) != 0U))
    {
        s_esaiRxIsr(ESAI, s_esaiHandle[0][1]);
    }

    /* Handle Tx operation */
    if (((ESAI_GetStatusFlag(ESAI) & (uint32_t)kESAI_TransmitFIFOEmptyFlag) != 0U) &&
        ((ESAI->TCR & (uint32_t)kESAI_TransmitInterruptEnable) != 0U))
    {
        s_esaiTxIsr(ESAI, s_esaiHandle[0][0]);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(AUDIO__ESAI1)
#define ESAI1 AUDIO__ESAI1
void AUDIO_ESAI1_INT_IRQHandler(void)
{
    /* Handle Rx operation */
    if (((ESAI_GetStatusFlag(ESAI1) & (uint32_t)kESAI_ReceiveFIFOFullFlag) != 0U) &&
        ((ESAI1->RCR & (uint32_t)kESAI_TransmitInterruptEnable) != 0U))
    {
        s_esaiRxIsr(ESAI1, s_esaiHandle[1][1]);
    }

    /* Handle Tx operation */
    if (((ESAI_GetStatusFlag(ESAI1) & (uint32_t)kESAI_TransmitFIFOEmptyFlag) != 0U) &&
        ((ESAI1->TCR & (uint32_t)kESAI_TransmitInterruptEnable) != 0U))
    {
        s_esaiTxIsr(ESAI1, s_esaiHandle[1][0]);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
