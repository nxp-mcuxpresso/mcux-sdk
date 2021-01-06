/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_IRTC_H_
#define _FSL_IRTC_H_

#include "fsl_common.h"

/*!
 * @addtogroup irtc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_IRTC_DRIVER_VERSION (MAKE_VERSION(2, 0, 2)) /*!< Version. */
/*@}*/

/*! @brief IRTC filter clock source options. */
typedef enum _irtc_filter_clock_source
{
    kIRTC_32K = 0x0, /*!< Use 32 kHz clock source for the tamper filter.*/
    kIRTC_512 = 0x1, /*!< Use 512 Hz clock source for the tamper filter.*/
    kIRTC_128 = 0x2, /*!< Use 128 Hz clock source for the tamper filter.*/
    kIRTC_64  = 0x3, /*!< Use 64 Hz clock source for the tamper filter.*/
    kIRTC_16  = 0x4, /*!< Use 16 Hz clock source for the tamper filter.*/
    kIRTC_8   = 0x5, /*!< Use 8 Hz clock source for the tamper filter.*/
    kIRTC_4   = 0x6, /*!< Use 4 Hz clock source for the tamper filter.*/
    kIRTC_2   = 0x7  /*!< Use 2 Hz clock source for the tamper filter.*/
} irtc_filter_clock_source_t;

/*! @brief IRTC Tamper pins. */
typedef enum _irtc_tamper_pins
{
    kIRTC_Tamper_0 = 0U, /*!< External Tamper 0 */
    kIRTC_Tamper_1,      /*!< External Tamper 1 */
    kIRTC_Tamper_2,      /*!< External Tamper 2 */
    kIRTC_Tamper_3       /*!< Internal tamper, does not have filter configuration */
} irtc_tamper_pins_t;

/*! @brief List of IRTC interrupts */
typedef enum _irtc_interrupt_enable
{
    kIRTC_TamperInterruptEnable = RTC_IER_TAMPER_IE_MASK, /*!< Tamper Interrupt Enable */
    kIRTC_AlarmInterruptEnable  = RTC_IER_ALM_IE_MASK,    /*!< Alarm Interrupt Enable */
    kIRTC_DayInterruptEnable    = RTC_IER_DAY_IE_MASK,    /*!< Days Interrupt Enable */
    kIRTC_HourInterruptEnable   = RTC_IER_HOUR_IE_MASK,   /*!< Hours Interrupt Enable */
    kIRTC_MinInterruptEnable    = RTC_IER_MIN_IE_MASK,    /*!< Minutes Interrupt Enable */
    kIRTC_1hzInterruptEnable    = RTC_IER_IE_1HZ_MASK,    /*!< 1 Hz interval Interrupt Enable */
    kIRTC_2hzInterruptEnable    = RTC_IER_IE_2HZ_MASK,    /*!< 2 Hz interval Interrupt Enable */
    kIRTC_4hzInterruptEnable    = RTC_IER_IE_4HZ_MASK,    /*!< 4 Hz interval Interrupt Enable */
    kIRTC_8hzInterruptEnable    = RTC_IER_IE_8HZ_MASK,    /*!< 8 Hz interval Interrupt Enable */
    kIRTC_16hzInterruptEnable   = RTC_IER_IE_16HZ_MASK,   /*!< 16 Hz interval Interrupt Enable */
    kIRTC_32hzInterruptEnable   = RTC_IER_IE_32HZ_MASK,   /*!< 32 Hz interval Interrupt Enable */
    kIRTC_64hzInterruptEnable   = RTC_IER_IE_64HZ_MASK,   /*!< 64 Hz interval Interrupt Enable */
    kIRTC_128hzInterruptEnable  = RTC_IER_IE_128HZ_MASK,  /*!< 128 Hz interval Interrupt Enable */
    kIRTC_256hzInterruptEnable  = RTC_IER_IE_256HZ_MASK,  /*!< 256 Hz interval Interrupt Enable */
    kIRTC_512hzInterruptEnable  = RTC_IER_IE_512HZ_MASK   /*!< 512 Hz interval Interrupt Enable */
} irtc_interrupt_enable_t;

/*! @brief List of IRTC flags */
typedef enum _irtc_status_flags
{
    kIRTC_TamperFlag     = RTC_ISR_TAMPER_IS_MASK,                /*!< Tamper Status flag*/
    kIRTC_AlarmFlag      = RTC_ISR_ALM_IS_MASK,                   /*!< Alarm Status flag */
    kIRTC_DayFlag        = RTC_ISR_DAY_IS_MASK,                   /*!< Days Status flag */
    kIRTC_HourFlag       = RTC_ISR_HOUR_IS_MASK,                  /*!< Hour Status flag */
    kIRTC_MinFlag        = RTC_ISR_MIN_IS_MASK,                   /*!< Minutes Status flag */
    kIRTC_1hzFlag        = RTC_ISR_IS_1HZ_MASK,                   /*!< 1 Hz interval status flag */
    kIRTC_2hzFlag        = RTC_ISR_IS_2HZ_MASK,                   /*!< 2 Hz interval status flag*/
    kIRTC_4hzFlag        = RTC_ISR_IS_4HZ_MASK,                   /*!< 4 Hz interval status flag*/
    kIRTC_8hzFlag        = RTC_ISR_IS_8HZ_MASK,                   /*!< 8 Hz interval status flag*/
    kIRTC_16hzFlag       = RTC_ISR_IS_16HZ_MASK,                  /*!< 16 Hz interval status flag*/
    kIRTC_32hzFlag       = RTC_ISR_IS_32HZ_MASK,                  /*!< 32 Hz interval status flag*/
    kIRTC_64hzFlag       = RTC_ISR_IS_64HZ_MASK,                  /*!< 64 Hz interval status flag*/
    kIRTC_128hzFlag      = RTC_ISR_IS_128HZ_MASK,                 /*!< 128 Hz interval status flag*/
    kIRTC_256hzFlag      = RTC_ISR_IS_256HZ_MASK,                 /*!< 256 Hz interval status flag*/
    kIRTC_512hzFlag      = RTC_ISR_IS_512HZ_MASK,                 /*!< 512 Hz interval status flag*/
    kIRTC_InvalidFlag    = (RTC_STATUS_INVAL_BIT_MASK << 16),     /*!< Indicates if time/date counters are invalid */
    kIRTC_WriteProtFlag  = (RTC_STATUS_WRITE_PROT_EN_MASK << 16), /*!< Write protect enable status flag */
    kIRTC_CpuLowVoltFlag = (RTC_STATUS_CPU_LOW_VOLT_MASK << 16),  /*!< CPU low voltage warning flag */
    kIRTC_ResetSrcFlag   = (RTC_STATUS_RST_SRC_MASK << 16),       /*!< Reset source flag */
    kIRTC_CmpIntFlag     = (RTC_STATUS_CMP_INT_MASK << 16),       /*!< Compensation interval status flag */
    kIRTC_BusErrFlag     = (RTC_STATUS_BUS_ERR_MASK << 16),       /*!< Bus error flag */
    kIRTC_CmpDoneFlag    = (RTC_STATUS_CMP_DONE_MASK << 16)       /*!< Compensation done flag */
} irtc_status_flags_t;

/*! @brief IRTC alarm match options */
typedef enum _irtc_alarm_match
{
    kRTC_MatchSecMinHr          = 0, /*!< Only match second, minute and hour */
    kRTC_MatchSecMinHrDay       = 1, /*!< Only match second, minute, hour and day */
    kRTC_MatchSecMinHrDayMnth   = 2, /*!< Only match second, minute, hour, day and month */
    kRTC_MatchSecMinHrDayMnthYr = 3  /*!< Only match second, minute, hour, day, month and year */
} irtc_alarm_match_t;

/*! @brief List of RTC Oscillator capacitor load settings */
typedef enum _irtc_osc_cap_load
{
    kIRTC_Capacitor2p  = (1U << 1), /*!< 2pF capacitor load */
    kIRTC_Capacitor4p  = (1U << 2), /*!< 4pF capacitor load */
    kIRTC_Capacitor8p  = (1U << 3), /*!< 8pF capacitor load */
    kIRTC_Capacitor16p = (1U << 4)  /*!< 16pF capacitor load */
} irtc_osc_cap_load_t;

/*! @brief Structure is used to hold the date and time */
typedef struct _irtc_datetime
{
    uint16_t year;   /*!< Range from 1984 to 2239.*/
    uint8_t month;   /*!< Range from 1 to 12.*/
    uint8_t day;     /*!< Range from 1 to 31 (depending on month).*/
    uint8_t weekDay; /*!< Range from 0(Sunday) to 6(Saturday). */
    uint8_t hour;    /*!< Range from 0 to 23.*/
    uint8_t minute;  /*!< Range from 0 to 59.*/
    uint8_t second;  /*!< Range from 0 to 59.*/
} irtc_datetime_t;

/*! @brief Structure is used to hold the daylight saving time */
typedef struct _irtc_daylight_time
{
    uint8_t startMonth; /*!< Range from 1 to 12 */
    uint8_t endMonth;   /*!< Range from 1 to 12 */
    uint8_t startDay;   /*!< Range from 1 to 31 (depending on month) */
    uint8_t endDay;     /*!< Range from 1 to 31 (depending on month) */
    uint8_t startHour;  /*!< Range from 0 to 23 */
    uint8_t endHour;    /*!< Range from 0 to 23 */
} irtc_daylight_time_t;

/*! @brief Structure is used to define the parameters to configure a RTC tamper event. */
typedef struct _irtc_tamper_config
{
#if FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION
    bool activePassive; /*!< true: configure tamper as active; false: passive tamper */
    bool direction;     /*!< true: configure tamper direction as output; false: configure as input;
                             this is only used if a tamper pin is defined as active */
#endif
    bool pinPolarity;                     /*!< true: tamper has active low polarity;
                                               false: active high polarity */
    irtc_filter_clock_source_t filterClk; /*!< Clock source for the tamper filter */
    uint8_t filterDuration;               /*!< Tamper filter duration.*/
} irtc_tamper_config_t;

/*!
 * @brief RTC config structure
 *
 * This structure holds the configuration settings for the RTC peripheral. To initialize this
 * structure to reasonable defaults, call the IRTC_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _irtc_config
{
    bool wakeupSelect;            /*!< true: Tamper pin 0 is used to wakeup the chip;
                                       false: Tamper pin 0 is used as the tamper pin */
    bool timerStdMask;            /*!< true: Sampling clocks gated in standby mode;
                                       false: Sampling clocks not gated */
    irtc_alarm_match_t alrmMatch; /*!< Pick one option from enumeration :: irtc_alarm_match_t */
} irtc_config_t;

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
 * @brief Ungates the IRTC clock and configures the peripheral for basic operation.
 *
 * This function initiates a soft-reset of the IRTC module, this has not effect on DST,
 * calendaring, standby time and tamper detect registers.
 *
 * @note This API should be called at the beginning of the application using the IRTC driver.
 *
 * @param base   IRTC peripheral base address
 * @param config Pointer to user's IRTC config structure.
 *
 * @return kStatus_Fail if we cannot disable register write protection
 */
status_t IRTC_Init(RTC_Type *base, const irtc_config_t *config);

/*!
 * @brief Gate the IRTC clock
 *
 * @param base IRTC peripheral base address
 */
static inline void IRTC_Deinit(RTC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * @brief Fill in the IRTC config struct with the default settings
 *
 * The default values are:
 * @code
 *    config->wakeupSelect = true;
 *    config->timerStdMask = false;
 *    config->alrmMatch = kRTC_MatchSecMinHr;
 * @endcode
 * @param config Pointer to user's IRTC config structure.
 */
void IRTC_GetDefaultConfig(irtc_config_t *config);

/*! @}*/

/*!
 * @name Current Time & Alarm
 * @{
 */

/*!
 * @brief Sets the IRTC date and time according to the given time structure.
 *
 * The IRTC counter is started after the time is set.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to structure where the date and time details to set are stored
 *
 * @return kStatus_Success: success in setting the time and starting the IRTC
 *         kStatus_InvalidArgument: failure. An error occurs because the datetime format is incorrect.
 */
status_t IRTC_SetDatetime(RTC_Type *base, const irtc_datetime_t *datetime);

/*!
 * @brief Gets the IRTC time and stores it in the given time structure.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to structure where the date and time details are stored.
 */
void IRTC_GetDatetime(RTC_Type *base, irtc_datetime_t *datetime);

/*!
 * @brief Sets the IRTC alarm time
 *
 * @param base      RTC peripheral base address
 * @param alarmTime Pointer to structure where the alarm time is stored.
 *
 * @note weekDay field of alarmTime is not used during alarm match and should be set to 0
 *
 * @return kStatus_Success: success in setting the alarm
 *         kStatus_InvalidArgument: error in setting the alarm. Error occurs because the alarm
 *                                  datetime format is incorrect.
 */
status_t IRTC_SetAlarm(RTC_Type *base, const irtc_datetime_t *alarmTime);

/*!
 * @brief Returns the IRTC alarm time.
 *
 * @param base     RTC peripheral base address
 * @param datetime Pointer to structure where the alarm date and time details are stored.
 */
void IRTC_GetAlarm(RTC_Type *base, irtc_datetime_t *datetime);

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::irtc_interrupt_enable_t
 */
static inline void IRTC_EnableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->IER |= (uint16_t)mask;
}

/*!
 * @brief Disables the selected IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::irtc_interrupt_enable_t
 */
static inline void IRTC_DisableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->IER &= ~(uint16_t)mask;
}

/*!
 * @brief Gets the enabled IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::irtc_interrupt_enable_t
 */
static inline uint16_t IRTC_GetEnabledInterrupts(RTC_Type *base)
{
    return base->IER;
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the IRTC status flags
 *
 * @param base IRTC peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::irtc_status_flags_t
 */
static inline uint32_t IRTC_GetStatusFlags(RTC_Type *base)
{
    return (base->ISR | ((uint32_t)base->STATUS << 16U));
}

/*!
 * @brief Clears the IRTC status flags.
 *
 * @param base IRTC peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::irtc_status_flags_t
 */
static inline void IRTC_ClearStatusFlags(RTC_Type *base, uint32_t mask)
{
    base->ISR    = (uint16_t)mask;
    base->STATUS = (base->STATUS & ~((uint16_t)RTC_STATUS_BUS_ERR_MASK | (uint16_t)RTC_STATUS_CMP_DONE_MASK)) |
                   ((uint16_t)(mask >> 16U));
}

/*! @}*/

/*!
 * @brief This function sets the specified capacitor configuration for the RTC oscillator.
 *
 * @param base    IRTC peripheral base address
 * @param capLoad Oscillator loads to enable. This is a logical OR of members of the
 *                enumeration ::irtc_osc_cap_load_t
 */
static inline void IRTC_SetOscCapLoad(RTC_Type *base, uint16_t capLoad)
{
    uint16_t reg = base->GP_DATA_REG;

    reg &= ~((uint16_t)kIRTC_Capacitor2p | (uint16_t)kIRTC_Capacitor4p | (uint16_t)kIRTC_Capacitor8p |
             (uint16_t)kIRTC_Capacitor16p);
    reg |= capLoad;

    base->GP_DATA_REG = reg;
}

/*!
 * @brief Locks or unlocks IRTC registers for write access.
 *
 * @note When the registers are unlocked, they remain in unlocked state for
 * 2 seconds, after which they are locked automatically. After
 * power-on-reset, the registers come out unlocked and they are locked
 * automatically 15 seconds after power on.
 *
 * @param base IRTC peripheral base address
 * @param lock true: Lock IRTC registers; false: Unlock IRTC registers.
 *
 * @return kStatus_Success: if lock or unlock operation is successful
 *         kStatus_Fail: if lock or unlock operation fails even after multiple retry attempts
 */
status_t IRTC_SetWriteProtection(RTC_Type *base, bool lock);

/*!
 * @brief Performs a software reset on the IRTC module.
 *
 * Clears contents of alarm, interrupt (status and enable except tamper interrupt enable bit)
 * registers, STATUS[CMP_DONE] and STATUS[BUS_ERR]. This has no effect on DST, calendaring, standby time
 * and tamper detect registers.
 *
 * @param base IRTC peripheral base address
 */
static inline void IRTC_Reset(RTC_Type *base)
{
    base->CTRL |= RTC_CTRL_SWR_MASK;
}

/*!
 * @name Daylight Savings Interface
 * @{
 */

/*!
 * @brief Sets the IRTC daylight savings start and stop date and time.
 *
 * It also enables the daylight saving bit in the IRTC control register
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_SetDaylightTime(RTC_Type *base, const irtc_daylight_time_t *datetime);

/*!
 * @brief Gets the IRTC daylight savings time and stores it in the given time structure.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_GetDaylightTime(RTC_Type *base, irtc_daylight_time_t *datetime);

/*! @}*/

/*!
 * @name Time Compensation Interface
 * @{
 */

/*!
 * @brief Enables the coarse compensation and sets the value in the IRTC compensation register.
 *
 * @param base                 IRTC peripheral base address
 * @param compensationValue    Compensation value is a 2's complement value.
 * @param compensationInterval Compensation interval.
 */
void IRTC_SetCoarseCompensation(RTC_Type *base, uint8_t compensationValue, uint8_t compensationInterval);

/*!
 * @brief Enables the fine compensation and sets the value in the IRTC compensation register.
 *
 * @param base                 The IRTC peripheral base address
 * @param integralValue        Compensation integral value; twos complement value of the integer part
 * @param fractionValue        Compensation fraction value expressed as number of clock cycles of a
 *                             fixed 4.194304Mhz clock that have to be added.
 * @param accumulateFractional Flag indicating if we want to add to previous fractional part;
 *                             true: Add to previously accumulated fractional part,
 *                             false: Start afresh and overwrite current value
 */
void IRTC_SetFineCompensation(RTC_Type *base, uint8_t integralValue, uint8_t fractionValue, bool accumulateFractional);

/*! @}*/

/*!
 * @name Tamper Interface
 * @{
 */

/*!
 * @brief This function allows configuring the four tamper inputs.
 *
 * The function configures the filter properties for the three external tampers.
 * It also sets up active/passive and direction of the tamper bits, which are not available
 * on all platforms.
 * @note This function programs the tamper filter parameters. The user must gate the 32K clock to
 * the RTC before calling this function. It is assumed that the time and date are set after this
 * and the tamper parameters do not require to be changed again later.
 *
 * @param base         The IRTC peripheral base address
 * @param tamperNumber The IRTC tamper input to configure
 * @param tamperConfig The IRTC tamper properties
 */
void IRTC_SetTamperParams(RTC_Type *base, irtc_tamper_pins_t tamperNumber, const irtc_tamper_config_t *tamperConfig);

#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)

/*!
 * @brief This function reads the tamper timestamp and returns the associated tamper pin.
 *
 * The tamper timestamp has month, day, hour, minutes, and seconds. Ignore the year field as this
 * information is not available in the tamper queue. The user should look at the RTC_YEARMON register
 * for this because the expectation is that the queue is read at least once a year.
 * Return the tamper pin number associated with the timestamp.
 *
 * @param base             The IRTC peripheral base address
 * @param tamperTimestamp  The tamper timestamp
 *
 * @return The tamper pin number
 */
uint8_t IRTC_ReadTamperQueue(RTC_Type *base, irtc_datetime_t *tamperTimestamp);

#endif /* FSL_FEATURE_RTC_HAS_TAMPER_QUEUE */

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_IRTC_H_ */
