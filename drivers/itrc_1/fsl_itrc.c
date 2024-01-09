/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_itrc.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.itrc_1"
#endif

#define b11 0x3UL
#define b10 0x2UL
#define b01 0x1UL

/* Value used to trigger SW Events */
#define SW_EVENT_VAL 0x5AA55AA5u

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * Weak implementation of ITRC IRQ, should be re-defined by user when using ITRC IRQ
 */
__WEAK void ITRC_DriverIRQHandler(void)
{
    /* ITRC generates IRQ until corresponding bit in STATUS is cleared by calling
     * ITRC_ClearStatus(ITRC,((uint32_t)kITRC_Irq)
     */
}

/*!
 * @brief Clear input ITRC status
 *
 * This function clears corresponding ITRC event in STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param word 32bit word represent corresponding event/action in STATUS register to be cleared
 * (see ITRC_STATUS_INx)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearInEventStatus(ITRC_Type *base, itrc_in_signals_t event)
{
    /* If reserved/unused bits in STATUS register are set in 'event' parameter, return kStatus_InvalidArgument */
    if (event < ITRC_INPUT_SIGNALS_NUM)
    {
        if (event < 16u)
        {
            const uint32_t shifted = (uint32_t)1U << event;
            if ((shifted & ~(IN_STATUS0_EVENTS_MASK)) != 0u)
            {
                return kStatus_InvalidArgument;
            }

            base->STATUS0 = shifted;
        }
        else
        {
            const uint32_t shifted = (uint32_t)1U << (event - 16u);
            if ((shifted & ~(IN_STATUS1_EVENTS_MASK)) != 0u)
            {
                return kStatus_InvalidArgument;
            }

            base->STATUS1 = shifted;
        }
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

/*!
 * brief Clear output action ITRC status
 *
 * This function clears corresponding ITRC action in STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param word 32bit word represent corresponding event/action in STATUS register to be cleared
 * (see OUTx_STATUS)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearOutActionStatus(ITRC_Type *base, itrc_out_signals_t action)
{
    /* If reserved/unused bits in STATUS register are set in 'action' parameter, return kStatus_InvalidArgument */
    const uint32_t shifted = (uint32_t)1U << action;
    if ((shifted & ~(OUT_ACTIONS_MASK)) != 0u)
    {
        return kStatus_InvalidArgument;
    }

    base->STATUS0 = shifted;

    return kStatus_Success;
}

/*!
 * @brief Clear all ITRC status
 *
 * This clears all event and action status.
 *
 * @param base ITRC peripheral base address
 * @return Status of the ITRC
 */
status_t ITRC_ClearAllStatus(ITRC_Type *base)
{
    base->STATUS0 = (IN_STATUS0_EVENTS_MASK | OUT_ACTIONS_MASK);
    base->STATUS1 = IN_STATUS1_EVENTS_MASK;

    return kStatus_Success;
}

/*!
 * @brief Trigger ITRC SW Event 0
 *
 * This funciton set SW_EVENT0 register with value !=0 which triggers ITRC SW Event 0.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent0(ITRC_Type *base)
{
    base->SW_EVENT0 = SW_EVENT_VAL;
}

/*!
 * @brief Trigger ITRC SW Event 1
 *
 * This funciton set SW_EVENT1 register with value !=0 which triggers ITRC SW Event 1.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent1(ITRC_Type *base)
{
    base->SW_EVENT1 = SW_EVENT_VAL;
}

/*!
 * @brief Set ITRC Action to Event
 *
 * This function sets input Event signal to corresponding output Action response signal.
 *
 * @param base ITRC peripheral base address
 * @param out ITRC OUT signal action
 * @param in ITRC IN signal event
 * @param lock if set locks INx_SEL configuration. This can be cleared only by PMC Core reset.
 * @param enable if set input Event will be selected for output Action, otherwise disable (if not already locked).
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_SetActionToEvent(
    ITRC_Type *base, itrc_out_signals_t out, itrc_in_signals_t in, itrc_lock_t lock, itrc_enable_t enable)
{
    uint32_t sel0, sel1, index, select_AND_mask;

    /*   prepare values for INx_SEL0/1 bit-field according to secure techniques and register behavior
     *    +------------+------------+------------------+---------------------------+
     *    |  INx_SEL0  |  INx_SEL1  | Signal selected? |      Writable field?      |
     *    +------------+------------+------------------+---------------------------+
     *    | 10         | 10         | No               | Yes (default after reset) |
     *    | 01         | 10         | Yes              | Yes                       |
     *    | don't care | !="10"     | Yes              | No                        |
     *    | 00 or 11   | don't care | Yes              | No                        |
     *    +------------+------------+------------------+---------------------------+
     */
    if ((lock == kITRC_Unlock) && (enable == kITRC_Disable))
    {
        sel0 = b10;
        sel1 = b10;
    }
    else if ((lock == kITRC_Unlock) && (enable == kITRC_Enable))
    {
        sel0 = b01;
        sel1 = b10;
    }
    else
    {
        sel0 = b11;
        sel1 = b11;
    }

    /* Compute index for INx_SEL0/1 bit-field within OUTy_SEL0/1 registers */
    index = 2UL * (uint32_t)in;

    /* Eeach signal is encoded by two bits */
    if (index > 2UL * ITRC_INPUT_SIGNALS_NUM)
    {
        return kStatus_InvalidArgument;
    }

    if (index < 32UL)
    {
        /* Prepare AND mask to set INx_SEL0 accordingly */
        select_AND_mask = ~(b11 << index);

        switch (out)
        {
            case kITRC_Irq:
                base->OUT0_SEL0 = (base->OUT0_SEL0 & select_AND_mask) | (sel0 << index);
                base->OUT0_SEL1 |= sel1 << index;
                break;

            case kITRC_ChipReset:
                base->OUT1_SEL0 = (base->OUT1_SEL0 & select_AND_mask) | (sel0 << index);
                base->OUT1_SEL1 |= sel1 << index;
                break;

            default:
                /* This case shouldn't be reached. */
                return kStatus_InvalidArgument;
        }
    }
    else
    {
        index -= 32UL;
        /* Prepare AND mask to set INx_SEL0 accordingly */
        select_AND_mask = ~(b11 << index);

        switch (out)
        {
            case kITRC_Irq:
                base->OUT0_SEL0_EVENT16_31 = (base->OUT0_SEL0_EVENT16_31 & select_AND_mask) | (sel0 << index);
                base->OUT0_SEL1_EVENT16_31 |= sel1 << index;
                break;

            case kITRC_ChipReset:
                base->OUT1_SEL0_EVENT16_31 = (base->OUT1_SEL0_EVENT16_31 & select_AND_mask) | (sel0 << index);
                base->OUT1_SEL1_EVENT16_31 |= sel1 << index;
                break;

            default:
                /* This case shouldn't be reached. */
                return kStatus_InvalidArgument;
        }
    }

    return kStatus_Success;
}

/*!
 * @brief Get ITRC input event status
 *
 * This function returns ITRC status corresponding to provided input event.
 *
 * @param base ITRC peripheral base address
 * @param event represents input event in STATUS register to get
 * (see ITRC_STATUS_INx)
 * @return boolean TRUE if corresponding event occured
 *                 FALSE otherwise
 */
bool ITRC_GetInEventStatus(ITRC_Type *base, itrc_in_signals_t event)
{
    if (event < 16UL)
    {
        return (base->STATUS0 & (1UL << event)) != 0UL;
    }
    else
    {
        return (base->STATUS1 & (1UL << (event - 16UL))) != 0UL;
    }
}

/*!
 * @brief Get ITRC output action status
 *
 * This function returns ITRC register output status.
 *
 * @param base ITRC peripheral base address
 * @param action represents output action in STATUS register to get
 * (see ITRC_STATUS_OUTx)
 * @return boolean TRUE if corresponding action occured
 *                 FALSE otherwise
 */
bool ITRC_GetOutActionStatus(ITRC_Type *base, itrc_out_signals_t action)
{
    return ((base->STATUS0 & (1UL << action)) != 0UL);
}

/*!
 * @brief Initialize ITRC
 *
 * This function initializes ITRC by enabling IRQ.
 *
 * @param base ITRC peripheral base address
 * @return Status of the init operation
 */
status_t ITRC_Init(ITRC_Type *base)
{
    status_t status  = IRQ_ClearPendingIRQ(ITRC_IRQn);

    if ( status != kStatus_Success)
    {
        return status;
    }
    return EnableIRQ(ITRC_IRQn);
}

/*!
 * @brief Deinitialize ITRC
 *
 * This function just disable ITRC IRQ.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_Deinit(ITRC_Type *base)
{
    (void)DisableIRQ(ITRC_IRQn);
}
