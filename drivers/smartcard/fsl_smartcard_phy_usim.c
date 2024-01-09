/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartcard_usim.h"
#include "fsl_smartcard_phy.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smartcard_phy_usim"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void SMARTCARD_PHY_USIM_InterfaceClockInit(USIM_Type *base,
                                                  const smartcard_interface_config_t *config,
                                                  uint32_t srcClock_Hz);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief This function initializes clock module used for card clock generation
 */
static void SMARTCARD_PHY_USIM_InterfaceClockInit(USIM_Type *base,
                                                  const smartcard_interface_config_t *config,
                                                  uint32_t srcClock_Hz)
{
    assert((NULL != config) && (0u != srcClock_Hz));

    uint32_t usimClkMhz = 0u;
    uint8_t usimPRSCValue;

    /* Retrieve USIM clock */
    usimClkMhz = srcClock_Hz / 1000000u;
    /* Calculate MOD value */
    usimPRSCValue = (uint8_t)((usimClkMhz * 1000u) / (config->smartCardClock / 1000u) / 2U);
    while (0UL != (base->CLKR & USIM_CLKR_RQST_MASK))
    {
    }
    /* Set clock prescaler */
    base->CLKR = (base->CLKR & ~USIM_CLKR_DIVISOR_MASK) | USIM_CLKR_DIVISOR(usimPRSCValue);
}

void SMARTCARD_PHY_GetDefaultConfig(smartcard_interface_config_t *config)
{
    assert((NULL != config));

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->clockToResetDelay = SMARTCARD_INIT_DELAY_CLOCK_CYCLES;
    config->vcc               = kSMARTCARD_VoltageClassB3_3V;
}

status_t SMARTCARD_PHY_Init(void *base, smartcard_interface_config_t const *config, uint32_t srcClock_Hz)
{
    if ((NULL == config) || (0u == srcClock_Hz))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    USIM_Type *usimBase = (USIM_Type *)base;

    /* SMARTCARD clock initialization. Clock is still not active after this call */
    SMARTCARD_PHY_USIM_InterfaceClockInit(usimBase, config, srcClock_Hz);

    return kStatus_SMARTCARD_Success;
}

void SMARTCARD_PHY_Deinit(void *base, smartcard_interface_config_t const *config)
{
    assert((NULL != config));
    /* Stop CARD CLOCK */
    while (0U != (((USIM_Type *)base)->CLKR & USIM_CLKR_RQST_MASK))
    {
    }
    ((USIM_Type *)base)->CLKR |= USIM_CLKR_STOP_UCLK_MASK;
    /* Deactivate VCC */
    ((USIM_Type *)base)->USCCR &= ~USIM_USCCR_VCC_MASK;
}

status_t SMARTCARD_PHY_Activate(void *base, smartcard_context_t *context, smartcard_reset_type_t resetType)
{
    if ((NULL == context) || (NULL == context->timeDelay))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    assert(context->interfaceConfig.vcc == kSMARTCARD_VoltageClassB3_3V);

    USIM_Type *usimBase = (USIM_Type *)base;

    context->timersState.initCharTimerExpired = false;
    context->resetType                        = resetType;

    /* Hold Transmission. */
    usimBase->FCR |= USIM_FCR_TX_HOLD_MASK;
    if (resetType == kSMARTCARD_ColdReset)
    {
        /* Set Reset low */
        usimBase->USCCR &= ~USIM_USCCR_RST_CARD_N_MASK;
        /* Enable VCC for SMARTCARD, Enable smart card clock */
        usimBase->USCCR = (usimBase->USCCR & ~USIM_USCCR_VCC_MASK) | USIM_USCCR_VCC(1);
        usimBase->USCCR &= ~USIM_USCCR_TXD_FORCE_MASK;
        usimBase->CLKR &= ~USIM_CLKR_STOP_UCLK_MASK;
        /* Set transfer mode to default(direct convention) */
        usimBase->LCR &= ~(USIM_LCR_ORDER_MASK | USIM_LCR_INVERSE_MASK);
    }
    else if (resetType == kSMARTCARD_WarmReset)
    {
        /* Ensure that card is already active */
        if (!context->cardParams.active)
        { /* Card is not active;hence return */
            return kStatus_SMARTCARD_CardNotActivated;
        }
        /* Set Reset low */
        usimBase->USCCR &= ~USIM_USCCR_RST_CARD_N_MASK;
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    /* Calculate time delay needed for reset */
    uint32_t temp =
        ((((uint32_t)10000u * context->interfaceConfig.clockToResetDelay) / context->interfaceConfig.smartCardClock) *
         100u) +
        1u;
    context->timeDelay(temp);
    /* Pull reset HIGH Now to mark the end of Activation sequence */
    usimBase->USCCR |= USIM_USCCR_RST_CARD_N_MASK;

    /* Enable external timer for TS detection time-out */
    SMARTCARD_USIM_TimerStart((SMARTCARD_INIT_DELAY_CLOCK_CYCLES + SMARTCARD_INIT_DELAY_CLOCK_CYCLES_ADJUSTMENT) *
                              (SystemCoreClock / context->interfaceConfig.smartCardClock));
    /* Here the card was activated */
    context->cardParams.active = true;

    return kStatus_SMARTCARD_Success;
}

status_t SMARTCARD_PHY_Deactivate(void *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    USIM_Type *usimBase = (USIM_Type *)base;

    /* Set Reset low */
    usimBase->USCCR &= ~USIM_USCCR_RST_CARD_N_MASK;
    /* Stop SMARTCARD clock generation */
    while (0UL != (usimBase->CLKR & USIM_CLKR_RQST_MASK))
    {
    }
    usimBase->CLKR &= ~USIM_CLKR_STOP_LEVEL_MASK;
    usimBase->CLKR |= USIM_CLKR_STOP_UCLK_MASK;
    /* Force the I/O line to ground level. */
    usimBase->USCCR |= USIM_USCCR_TXD_FORCE_MASK;
    /* Turn the VCC voltage to ground level. */
    usimBase->USCCR &= ~USIM_USCCR_VCC_MASK;
    /* According EMV 4.3 specification deactivation sequence should be done within 100ms.
     * The period is measured from the time that RST is set to state L to the time that Vcc
     * reaches 0.4 V or less.
     */
    context->timeDelay(100 * 1000);
    /* Here the card was deactivated */
    context->cardParams.active = false;

    return kStatus_SMARTCARD_Success;
}

status_t SMARTCARD_PHY_Control(void *base,
                               smartcard_context_t *context,
                               smartcard_interface_control_t control,
                               uint32_t param)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    status_t status = kStatus_SMARTCARD_Success;

    switch (control)
    {
        case kSMARTCARD_InterfaceSetVcc:
            /* Only 3.3V interface supported by the interface */
            assert((smartcard_card_voltage_class_t)param == kSMARTCARD_VoltageClassB3_3V);
            context->interfaceConfig.vcc = (smartcard_card_voltage_class_t)param;
            break;
        case kSMARTCARD_InterfaceSetClockToResetDelay:
            /* Set interface clock to Reset delay set by caller */
            context->interfaceConfig.clockToResetDelay = param;
            break;
        case kSMARTCARD_InterfaceReadStatus:
            /* Workaround, RW610 board no Card detect PIN */
            context->cardParams.present = true;
            break;
        default:
            status = kStatus_SMARTCARD_InvalidInput;
            break;
    }

    return status;
}
