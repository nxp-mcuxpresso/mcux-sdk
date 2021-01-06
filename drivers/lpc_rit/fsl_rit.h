/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_RIT_H_
#define _FSL_RIT_H_

#include "fsl_common.h"

/*!
 * @addtogroup rit
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_RIT_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1 */
/*@}*/

/*! @brief List of RIT status flags */
typedef enum _rit_status_flags
{
    kRIT_TimerFlag = RIT_CTRL_RITINT_MASK, /*!< Timer flag */
} rit_status_flags_t;

/*!
 * @brief RIT config structure
 *
 * This structure holds the configuration settings for the RIT peripheral. To initialize this
 * structure to reasonable defaults, call the RIT_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _rit_config
{
    bool enableRunInDebug; /*!< true: The timer is halted when the processor is halted for debugging.; false: Debug has
                              no effect on the timer operation. */
} rit_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the RIT clock, enables the RIT module, and configures the peripheral for basic operations.
 *
 * @note This API should be called at the beginning of the application using the RIT driver.
 *
 * @param base   RIT peripheral base address
 * @param config Pointer to the user's RIT config structure
 */
void RIT_Init(RIT_Type *base, const rit_config_t *config);

/*!
 * @brief Gates the RIT clock and disables the RIT module.
 *
 * @param base RIT peripheral base address
 */
void RIT_Deinit(RIT_Type *base);

/*!
 * @brief Fills in the RIT configuration structure with the default settings.
 *
 * The default values are as follows.
 * @code
 *     config->enableRunInDebug = false;
 * @endcode
 * @param config Pointer to the onfiguration structure.
 */
void RIT_GetDefaultConfig(rit_config_t *config);

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the RIT status flags.
 *
 * @param base    RIT peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::rit_status_flags_t
 */
static inline uint32_t RIT_GetStatusFlags(RIT_Type *base)
{
    return (base->CTRL);
}

/*!
 * @brief  Clears the RIT status flags.
 *
 * @param base    RIT peripheral base address
 * @param mask    The status flags to clear. This is a logical OR of members of the
 *                enumeration ::rit_status_flags_t
 */
static inline void RIT_ClearStatusFlags(RIT_Type *base, uint32_t mask)
{
    base->CTRL |= mask;
}

/*! @}*/

/*!
 * @name Read and Write the timer period
 * @{
 */

/*!
 * @brief Sets the timer period in units of count.
 *
 * This function sets the RI compare value. If the counter value equals to the compare value,
 * it will generate an interrupt.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base    RIT peripheral base address
 * @param count   Timer period in units of ticks
 */
void RIT_SetTimerCompare(RIT_Type *base, uint64_t count);

/*!
 * @brief Sets the mask bit of count compare.
 *
 * This function sets the RI mask value. A 1 written to any bit will force the compare to
 * be true for the corresponding bit of the counter and compare register (causes the comparison of
 * the register bits to be always true).
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base    RIT peripheral base address
 * @param count   Timer period in units of ticks
 */
void RIT_SetMaskBit(RIT_Type *base, uint64_t count);

/*!
 * @brief Reads the current value of compare register.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current RI compare value
 */
uint64_t RIT_GetCompareTimerCount(RIT_Type *base);

/*!
 * @brief Reads the current timer counting value of counter register.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current timer counting value in ticks
 */
uint64_t RIT_GetCounterTimerCount(RIT_Type *base);

/*!
 * @brief Reads the current value of mask register.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current RI mask value
 */
uint64_t RIT_GetMaskTimerCount(RIT_Type *base);

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timers load initial value(0U), count up to desired value or over-flow
 * then the counter will count up again.
 *
 * @param base    RIT peripheral base address
 */
static inline void RIT_StartTimer(RIT_Type *base)
{
    base->CTRL |= RIT_CTRL_RITEN_MASK;
}

/*!
 * @brief Stops the timer counting.
 *
 * This function stop timer counting. Timer reload their new value
 * after the next time they call the RIT_StartTimer.
 *
 * @param base    RIT peripheral base address
 */
static inline void RIT_StopTimer(RIT_Type *base)
{
    /* Disable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;
}

/*! @}*/
/*!
 * @brief Sets the Timer Counter auto clear or not
 *
 * This function set the counter auto clear or not whenever the counter value equals the masked
 * compare value specified by the contents of COMPVAL/COMPVAL_H and MASK/MASK_H registers..

 * @deprecated Do not use this function.  It has been superceded by @ref RIT_SetCountAutoClear.
 */
static inline void RIT_ClearCounter(RIT_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RIT_CTRL_RITENCLR_MASK;
    }
    else
    {
        base->CTRL &= ~RIT_CTRL_RITENCLR_MASK;
    }
}

/*!
 * @brief Sets the Timer Counter auto clear or not
 *
 * This function set the counter auto clear or not whenever the counter value equals the masked
 * compare value specified by the contents of COMPVAL/COMPVAL_H and MASK/MASK_H registers..
 *
 * @param base    RIT peripheral base address
 * @param enable Enable/disable Counter auto clear when value equals the compare value.
 *               - true: Enable Counter auto clear.
 *               - false: Disable Counter auto clear.
 */
static inline void RIT_SetCountAutoClear(RIT_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RIT_CTRL_RITENCLR_MASK;
    }
    else
    {
        base->CTRL &= ~RIT_CTRL_RITENCLR_MASK;
    }
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_RIT_H_ */
