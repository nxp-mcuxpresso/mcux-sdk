/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_rtc.h"
#include "fsl_rtc.h"

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static bool gRTCInitFlag = false;

static hal_rtc_callback_t rtcCallback;
static void *rtcCbparam;
/*
 * \brief Holds time offset in microseconds, used to calculate the date
 */
static volatile uint64_t gRTCTimeOffset;

/*
 * \brief Holds time prescaler offset in ticks, used to calculate the date
 */
static volatile uint32_t gRTCPrescalerOffset;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
void RTC_IRQHandler(void);
void RTC_IRQHandler(void)
{
    uint32_t status = RTC_GetStatusFlags(RTC);

    if (0U != (status & (uint32_t)kRTC_AlarmFlag))
    {
        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC, (uint32_t)kRTC_AlarmInterruptEnable);
    }
    else if (0U != (status & (uint32_t)kRTC_TimeInvalidFlag))
    {
        /* Clear timer invalid flag */
        RTC_ClearStatusFlags(RTC, (uint32_t)kRTC_TimeInvalidFlag);
    }
    else
    {
        /*MISRA rule 15.7*/
    }

    if (NULL != rtcCallback)
    {
        rtcCallback(rtcCbparam);
    }
    SDK_ISR_EXIT_BARRIER;
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
void HAL_RTCInit(void)
{
    rtc_config_t rtcConfig;
    rtc_datetime_t date;
    const rtc_config_t *rtcConfigure = (void *)&rtcConfig;
    if (!gRTCInitFlag)
    {
        RTC_GetDefaultConfig(&rtcConfig);
        RTC_Init(RTC, rtcConfigure);
        /* Select RTC clock source */
        RTC_SetClockSource(RTC);
        date.year   = 2018U;
        date.month  = 5U;
        date.day    = 30U;
        date.hour   = 19U;
        date.minute = 0;
        date.second = 0;

        const rtc_datetime_t *rtcDate = (void *)&date;
        /* RTC time counter has to be stopped before setting the date & time in the TSR register */
        RTC_StopTimer(RTC);

        /* Set RTC time to default */
        (void)RTC_SetDatetime(RTC, rtcDate);
        RTC_StartTimer(RTC);
        gRTCInitFlag = true;
        /* Enable RTC alarm interrupt */
        RTC_EnableInterrupts(RTC, (uint32_t)kRTC_AlarmInterruptEnable);
        /* Enable at the NVIC */
        (void)EnableIRQ(RTC_IRQn);
    }
}

/*! -------------------------------------------------------------------------
 * \brief  Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t HAL_RTCGetTimestamp(void)
{
    uint32_t seconds1, seconds2, prescaler0, prescaler1, prescaler2;
    uint64_t useconds, offset, prescalerOffset;

    if (!gRTCInitFlag)
    {
        useconds = 0;
        offset   = 0;
    }
    else
    {
        uint32_t regPrimask = DisableGlobalIRQ();
        offset              = gRTCTimeOffset;
        prescalerOffset     = gRTCPrescalerOffset;

        prescaler0 = RTC->TPR;
        seconds1   = RTC->TSR;
        prescaler1 = RTC->TPR;
        seconds2   = RTC->TSR;
        prescaler2 = RTC->TPR;
        EnableGlobalIRQ(regPrimask);

        prescaler0 &= 0x7fffU;
        seconds1 -= 1U;
        prescaler1 &= 0x7fffU;
        seconds2 -= 1U;
        prescaler2 &= 0x7fffU;

        if (seconds1 != seconds2)
        {
            seconds1   = seconds2;
            prescaler1 = prescaler2;
        }
        else
        {
            if (prescaler1 != prescaler2)
            {
                prescaler1 = prescaler0;
            }
        }

        useconds = ((prescaler1 + prescalerOffset + ((uint64_t)seconds1 << 15)) * 15625ULL) >> 9;
    }

    return useconds + offset;
}

#if (defined(RTC_FUNCTIONS_ENABLE) && (RTC_FUNCTIONS_ENABLE > 0))
/*! -------------------------------------------------------------------------
 * \brief     Sets the absolute time.
 * \param[in] microseconds - Time in microseconds.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetTime(uint64_t microseconds)
{
    uint32_t prescaler;
    uint32_t seconds = (uint32_t)(microseconds / 1000000ULL);
    uint32_t ms      = (uint32_t)(microseconds % 1000000ULL);
    /* microseconds = prescaler * 1_000_000 / 32768 = prescaler * 5^6 / 2^9 */
    /* prescaler  = microseconds *2^9 /5^6 */
    prescaler = (ms << 9) / 15625UL;

    RTC_StopTimer(RTC);
    RTC->TSR = seconds;
    RTC->TPR = prescaler;

    RTC_StartTimer(RTC);
}

/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm absolute time in seconds.
 * \param[in] seconds - Time in seconds for the alarm.
 * \param[in] callback - Callback function pointer.
 * \param[in] param - Parameter for callback.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetAlarm(uint64_t microseconds, hal_rtc_callback_t callback, void *param)
{
    /* Set alarm time in seconds */
    RTC->TAR = (uint32_t)(microseconds / 1000000ULL);

    rtcCallback = callback;
    rtcCbparam  = param;
}

/*! -------------------------------------------------------------------------
 * \brief Sets the alarm relative time in seconds.
 * \param[in] seconds - Time in seconds for the alarm.
 * \param[in] callback - Callback function pointer.
 * \param[in] param - Parameter for callback.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetAlarmRelative(uint32_t seconds, hal_rtc_callback_t callback, void *param)
{
    uint32_t newSeconds;
    newSeconds  = RTC->TSR + seconds;
    RTC->TAR    = newSeconds;
    rtcCallback = callback;
    rtcCbparam  = param;
}
#endif /* RTC_FUNCTIONS_ENABLE */
