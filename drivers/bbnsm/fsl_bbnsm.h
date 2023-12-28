/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_BBNSM_H_
#define FSL_BBNSM_H_

#include "fsl_common.h"

/*!
 * @addtogroup bbnsm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_BBNSM_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0 */
/*! @} */

/*! @brief List of BBNSM interrupts */
typedef enum _bbnsm_interrupts
{
    kBBNSM_RTC_AlarmInterrupt    = BBNSM_BBNSM_INT_EN_TA_INT_EN(0x2),  /*!< RTC time alarm interrupt */
    kBBNSM_RTC_RolloverInterrupt = BBNSM_BBNSM_INT_EN_RTC_INT_EN(0x2), /*!< RTC rollover interrupt */
} bbnsm_interrupts_t;

/*! @brief List of BBNSM flags */
typedef enum _bbnsm_status_flags
{
    kBBNSM_RTC_AlarmInterruptFlag    = BBNSM_BBNSM_EVENTS_TA(0x2),       /*!< RTC time alarm interrupt flag */
    kBBNSM_RTC_RolloverInterruptFlag = BBNSM_BBNSM_EVENTS_RTC_ROLL(0x2), /*!< RTC rollover interrupt flag */
    kBBNSM_PWR_ON_InterruptFlag      = BBNSM_BBNSM_EVENTS_PWR_ON(0x1),   /*!< power on interrupt flag */
    kBBNSM_PWR_OFF_InterruptFlag     = BBNSM_BBNSM_EVENTS_PWR_OFF(0x1),  /*!< power off interrupt flag */
    kBBNSM_EMG_OFF_InterruptFlag     = BBNSM_BBNSM_EVENTS_EMG_OFF(0x1),  /*!< emergency power off interrupt flag */
} bbnsm_status_flags_t;

/*!
 * @brief BBNSM config structure
 *
 * This structure holds the configuration settings for the BBNSM peripheral. To initialize this
 * structure to reasonable defaults, call the BBNSM_RTC_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _bbnsm_rtc_config
{
    bool rtcCalEnable;    /*!< true: RTC calibration mechanism is enabled;
                                false: No calibration is used */
    uint32_t rtcCalValue; /*!< Defines signed calibration value for RTC;
                                This is a 5-bit 2's complement value, range from -16 to +15 */
} bbnsm_rtc_config_t;

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
 * @brief Init the BBNSM section.
 *
 * @param base BBNSM peripheral base address
 */
void BBNSM_Init(BBNSM_Type *base);

/*!
 * @brief Deinit the BBNSM section.
 *
 * @param base BBNSM peripheral base address
 */
void BBNSM_Deinit(BBNSM_Type *base);

/*! @}*/

/*!
 * @brief Ungates the BBNSM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the BBNSM driver.
 *
 * @param base   BBNSM peripheral base address
 * @param config Pointer to the user's BBNSM rtc configuration structure.
 */
void BBNSM_RTC_Init(BBNSM_Type *base, const bbnsm_rtc_config_t *config);

/*!
 * @brief Stops the RTC timer.
 *
 * @param base BBNSM peripheral base address
 */
void BBNSM_RTC_Deinit(BBNSM_Type *base);

/*!
 * @brief Fills in the BBNSM RTC config struct with the default settings.
 *
 * The default values are as follows.
 * @code
 *    config->rtccalenable = false;
 *    config->rtccalvalue = 0U;
 * @endcode
 * @param config Pointer to the user's BBNSM configuration structure.
 */
void BBNSM_RTC_GetDefaultConfig(bbnsm_rtc_config_t *config);

/*!
 * @brief Sets the BBNSM RTC alarm time.
 *
 * The function sets the RTC alarm. It also checks whether the specified alarm
 * time is greater than the present time. If not, the function does not set the alarm
 * and returns an error.
 * Please note, that RTC alarm has limited resolution because only 32 most
 * significant bits of RTC counter are compared to RTC Alarm register.
 * If the alarm time is beyond RTC resolution, the function does not set the alarm
 * and returns an error.
 *
 * @param base      BBNSM peripheral base address
 * @param alarmSeconds
 *
 * @return kStatus_Success: success in setting the BBNSM RTC alarm
 *         kStatus_InvalidArgument: Error because the alarm datetime format is incorrect
 *         kStatus_Fail: Error because the alarm time has already passed or is beyond resolution
 */
status_t BBNSM_RTC_SetAlarm(BBNSM_Type *base, uint32_t alarmSeconds);

/*!
 * @brief Returns the BBNSM RTC alarm time.
 *
 * @param base     BBNSM peripheral base address
 */
uint32_t BBNSM_RTC_GetAlarm(BBNSM_Type *base);

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected BBNSM interrupts.
 *
 * @param base BBNSM peripheral base address
 * @param flags The interrupts to enable. This is a logical OR of members of the
 *             enumeration :: _bbnsm_interrupts
 */
static inline void BBNSM_EnableInterrupts(BBNSM_Type *base, uint32_t flags)
{
    uint32_t tmp = base->BBNSM_INT_EN;

    if ((tmp & BBNSM_BBNSM_INT_EN_TA_INT_EN(1)) != 0U)
    {
        tmp &= ~BBNSM_BBNSM_INT_EN_TA_INT_EN(
            0x3); /* Clear TA_INT_EN field to avoid writing an invliad value(0b00) to the TA_INT_EN field */
    }

    if ((tmp & BBNSM_BBNSM_INT_EN_RTC_INT_EN(1)) != 0U)
    {
        tmp &= ~BBNSM_BBNSM_INT_EN_RTC_INT_EN(
            0x3); /* Clear RTC_INT_EN field to avoid writing an invliad value(0b00) to the RTC_INT_EN field */
    }

    base->BBNSM_INT_EN = tmp | flags;
}

/*!
 * @brief Disables the selected BBNSM interrupts.
 *
 * @param base BBNSM peripheral base address
 * @param flags The interrupts to disable. This is a logical AND of members of the
 *             enumeration :: _bbnsm_interrupts
 */
static inline void BBNSM_DisableInterrupts(BBNSM_Type *base, uint32_t flags)
{
    uint32_t tmp = base->BBNSM_INT_EN;

    if ((tmp & kBBNSM_RTC_AlarmInterrupt) != 0U)
    {
        tmp &= ~BBNSM_BBNSM_INT_EN_TA_INT_EN(
            0x3); /* Clear TA_INT_EN field to avoid writing an invliad value(0b00) to the TA_INT_EN field */
    }

    if ((tmp & kBBNSM_RTC_RolloverInterrupt) != 0U)
    {
        tmp &= ~BBNSM_BBNSM_INT_EN_RTC_INT_EN(
            0x3); /* Clear RTC_INT_EN field to avoid writing an invliad value(0b00) to the RTC_INT_EN field */
    }

    base->BBNSM_INT_EN = tmp | ~flags;
}

/*!
 * @brief Gets the enabled BBNSM interrupts.
 *
 * @param base BBNSM peripheral base address
 *
 * @return The enabled interrupts.
 */
uint32_t BBNSM_GetEnabledInterrupts(BBNSM_Type *base);

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the BBNSM status flags.
 *
 * @param base BBNSM peripheral base address
 *
 * @return The status flags.
 */
uint32_t BBNSM_GetStatusFlags(BBNSM_Type *base);

/*!
 * @brief  Clears the BBNSM status flags.
 *
 * @param base BBNSM peripheral base address
 * @param flags The status flags to clear.(W1C)
 */
static inline void BBNSM_ClearStatusFlags(BBNSM_Type *base, uint32_t flags)
{
    base->BBNSM_EVENTS = flags;
}

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the BBNSM RTC time counter.
 *
 * @param base BBNSM peripheral base address
 */
static inline void BBNSM_RTC_StartTimer(BBNSM_Type *base)
{
    uint32_t tmp = base->BBNSM_CTRL;

    if ((tmp & BBNSM_BBNSM_CTRL_RTC_EN(0x1)) != 0U)
    {
        tmp &=
            ~BBNSM_BBNSM_CTRL_RTC_EN(0x3); /* Clear the field of RTC_EN to avoid writing 0b11 to the field of RTC_EN */
    }

    base->BBNSM_CTRL = tmp | BBNSM_BBNSM_CTRL_RTC_EN(0x2);
    while ((0U == (base->BBNSM_CTRL & BBNSM_BBNSM_CTRL_RTC_EN(0x2))))
    {
    }
}

/*!
 * @brief Stops the BBNSM RTC time counter.
 *
 * @param base BBNSM peripheral base address
 */
static inline void BBNSM_RTC_StopTimer(BBNSM_Type *base)
{
    uint32_t tmp = base->BBNSM_CTRL;

    if ((tmp & BBNSM_BBNSM_CTRL_RTC_EN(0x2)) != 0U)
    {
        tmp &= ~BBNSM_BBNSM_CTRL_RTC_EN(
            0x3); /* Clear RTC_EN field to avoid writing invalid value(0b11) to the RTC_EN field */
    }

    base->BBNSM_CTRL = tmp | BBNSM_BBNSM_CTRL_RTC_EN(0x1);
    while ((base->BBNSM_CTRL & (BBNSM_BBNSM_CTRL_RTC_EN(0x1))) == 0U)
    {
    }
}

/*!
 * @brief Sets the BBNSM RTC time counter.
 *
 * @param base BBNSM peripheral base address
 * @param seconds RTC time in seconds
 */

void BBNSM_RTC_SetSeconds(BBNSM_Type *base, uint32_t seconds);

/*!
 * @brief Returns RTC time in seconds.
 *
 * This function is used internally to get actual RTC time in seconds.
 *
 * @param base BBNSM peripheral base address
 *
 * @return RTC time in seconds
 */
uint32_t BBNSM_RTC_GetSeconds(BBNSM_Type *base);

#if defined(__cplusplus)
}
#endif

#endif /* FSL_BBNSM_H_ */
