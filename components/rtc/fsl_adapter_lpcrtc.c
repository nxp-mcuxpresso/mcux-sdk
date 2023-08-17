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

static hal_rtc_callback_t rtcCallback;
static void *rtcCbparam;

static uint8_t gRTCInitFlag = false;
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
void RTC_IRQHandler(void)
{
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag)
    {
        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
    }
    rtcCallback(rtcCbparam);
    SDK_ISR_EXIT_BARRIER;
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
void HAL_RTCInit(void)
{
    rtc_datetime_t date;
    if (!gRTCInitFlag)
    {
        RTC_Init(RTC);
        /* Select RTC clock source */
        date.year   = 2018U;
        date.month  = 5U;
        date.day    = 30U;
        date.hour   = 19U;
        date.minute = 0;
        date.second = 0;

        /* RTC time counter has to be stopped before setting the date & time in the TSR register */
        RTC_StopTimer(RTC);

        /* Set RTC time to default */
        RTC_SetDatetime(RTC, &date);

        /* Enable RTC alarm interrupt */
        RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);

        /* Enable at the NVIC */
        EnableIRQ(RTC_IRQn);

        /* Start the RTC time counter */
        RTC_StartTimer(RTC);
        gRTCInitFlag = true;
    }
}

/*! -------------------------------------------------------------------------
 * \brief  Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t HAL_RTCGetTimestamp(void)
{
    uint32_t seconds1, seconds2, prescaler0, prescaler1, prescaler2;
    uint64_t useconds;

    if (!gRTCInitFlag)
    {
        useconds = 0;
    }
    else
    {
        uint32_t regPrimask = DisableGlobalIRQ();
        prescaler0          = RTC->WAKE;
        seconds1            = RTC->COUNT;
        prescaler1          = RTC->WAKE;
        seconds2            = RTC->COUNT;
        prescaler2          = RTC->WAKE;
        EnableGlobalIRQ(regPrimask);

        prescaler0 &= 0x7fff;
        prescaler1 &= 0x7fff;
        prescaler2 &= 0x7fff;

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
        useconds = ((prescaler1 + ((uint64_t)seconds1 << 15)) * 15625) >> 9;
    }

    return useconds;
}

/*! -------------------------------------------------------------------------
 * \brief     Sets the absolute time.
 * \param[in] microseconds - Time in microseconds.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetTime(uint64_t microseconds)
{
    uint32_t prescaler;
    uint32_t seconds = microseconds / 1000000;
    uint32_t ms      = microseconds % 1000000;
    /* microseconds = prescaler * 1_000_000 / 32768 = prescaler * 5^6 / 2^9 */
    /* prescaler  = microseconds *2^9 /5^6 */
    prescaler = (ms << 9) / 15625;

    RTC_StopTimer(RTC);
    RTC->COUNT = seconds;

    RTC->WAKE = prescaler;
    RTC_StartTimer(RTC);
}

/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm absolute time in seconds.
 * \param[in] microseconds - Time in seconds for the alarm.
 * \param[in] callback - Callback function pointer.
 * \param[in] param - Parameter for callback.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetAlarm(uint64_t microseconds, hal_rtc_callback_t callback, void *param)
{
    /* Set alarm time in seconds */
    RTC->MATCH = microseconds / 1000000;

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
    newSeconds  = RTC->COUNT + seconds;
    RTC->MATCH  = newSeconds;
    rtcCallback = callback;
    rtcCbparam  = param;
}
