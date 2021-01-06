/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rit.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rit"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base RIT peripheral base address
 *
 * @return The RIT instance
 */
static uint32_t RIT_GetInstance(RIT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to RIT bases for each instance. */
static RIT_Type *const s_ritBases[] = RIT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PIT clocks for each instance. */
static const clock_ip_name_t s_ritClocks[] = RIT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_RIT_HAS_NO_RESET) && FSL_FEATURE_RIT_HAS_NO_RESET)
/*! @brief Pointers to RIT resets for each instance. */
static const reset_ip_name_t s_ritResets[] = RIT_RSTS;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t RIT_GetInstance(RIT_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_ritBases); instance++)
    {
        if (s_ritBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_ritBases));

    return instance;
}

/*!
 * brief Fills in the RIT configuration structure with the default settings.
 *
 * The default values are as follows.
 * code
 *     config->enableRunInDebug = false;
 * endcode
 * param config Pointer to the onfiguration structure.
 */
void RIT_GetDefaultConfig(rit_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Timer operation are no effect in Debug mode */
    config->enableRunInDebug = false;
}

/*!
 * brief Ungates the RIT clock, enables the RIT module, and configures the peripheral for basic operations.
 *
 * note This API should be called at the beginning of the application using the RIT driver.
 *
 * param base   RIT peripheral base address
 * param config Pointer to the user's RIT config structure
 */
void RIT_Init(RIT_Type *base, const rit_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the RIT clock*/
    CLOCK_EnableClock(s_ritClocks[RIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_RIT_HAS_NO_RESET) && FSL_FEATURE_RIT_HAS_NO_RESET)
    /* Reset the RIT module */
    RESET_PeripheralReset(s_ritResets[RIT_GetInstance(base)]);
#endif

    /* Enable RIT timers */
    base->CTRL |= RIT_CTRL_RITEN_MASK;

    /* Config timer operation is no effect in debug mode */
    if (!config->enableRunInDebug)
    {
        base->CTRL &= ~RIT_CTRL_RITENBR_MASK;
    }
    else
    {
        base->CTRL |= RIT_CTRL_RITENBR_MASK;
    }
}

/*!
 * brief Gates the RIT clock and disables the RIT module.
 *
 * param base RIT peripheral base address
 */
void RIT_Deinit(RIT_Type *base)
{
    /* Disable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the RIT clock*/
    CLOCK_DisableClock(s_ritClocks[RIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Sets the timer period in units of count.
 *
 * This function sets the RI compare value. If the counter value equals to the compare value,
 * it will generate an interrupt.
 *
 * note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * param base    RIT peripheral base address
 * param count   Timer period in units of ticks
 */
void RIT_SetTimerCompare(RIT_Type *base, uint64_t count)
{
    /* Disable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;
    base->COMPVAL   = (uint32_t)count;
    base->COMPVAL_H = (uint16_t)(count >> 32U);
}

/*!
 * brief Sets the mask bit of count compare.
 *
 * This function sets the RI mask value. A 1 written to any bit will force the compare to
 * be true for the corresponding bit of the counter and compare register (causes the comparison of
 * the register bits to be always true).
 *
 * note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * param base    RIT peripheral base address
 * param count   Timer period in units of ticks
 */
void RIT_SetMaskBit(RIT_Type *base, uint64_t count)
{
    base->MASK   = (uint32_t)count;
    base->MASK_H = (uint16_t)(count >> 32U);
}

/*!
 * brief Reads the current value of compare register.
 *
 * note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * param base    RIT peripheral base address
 *
 * return Current RI compare value
 */
uint64_t RIT_GetCompareTimerCount(RIT_Type *base)
{
    uint32_t valueH;
    uint32_t valueL = 0U;

    /* COMPVAL_H should be read before COMPVAL */
    valueH = (base->COMPVAL_H & RIT_COMPVAL_H_RICOMP_MASK);
    valueL = base->COMPVAL;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}

/*!
 * brief Reads the current timer counting value of counter register.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * param base    RIT peripheral base address
 *
 * return Current timer counting value in ticks
 */
uint64_t RIT_GetCounterTimerCount(RIT_Type *base)
{
    uint32_t valueH;
    uint32_t valueL = 0U;

    /* COUNTER_H should be read before COUNTER */
    valueH = (base->COUNTER_H & RIT_COUNTER_H_RICOUNTER_MASK);
    valueL = base->COUNTER;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}

/*!
 * brief Reads the current value of mask register.
 *
 * note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * param base    RIT peripheral base address
 *
 * return Current RI mask value
 */
uint64_t RIT_GetMaskTimerCount(RIT_Type *base)
{
    uint32_t valueH;
    uint32_t valueL = 0U;

    /* MASK_H should be read before MASK */
    valueH = (base->MASK_H & RIT_MASK_H_RIMASK_MASK);
    valueL = base->MASK;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}
