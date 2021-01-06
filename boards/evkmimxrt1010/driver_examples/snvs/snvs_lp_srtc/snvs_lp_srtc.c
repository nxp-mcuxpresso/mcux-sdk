/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_snvs_hp.h"
#include "fsl_snvs_lp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define kCLOCK_SnvsHp0          kCLOCK_SnvsHp
#define EXAMPLE_SNVS_IRQn       SNVS_HP_WRAPPER_IRQn
#define EXAMPLE_SNVS_IRQHandler SNVS_HP_WRAPPER_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool busyWait;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */

void EXAMPLE_SNVS_IRQHandler(void)
{
    if (SNVS_HP_RTC_GetStatusFlags(SNVS) & kSNVS_RTC_AlarmInterruptFlag)
    {
        busyWait = false;

        /* Clear alarm flag */
        SNVS_HP_RTC_ClearStatusFlags(SNVS, kSNVS_RTC_AlarmInterruptFlag);
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    uint32_t sec;
    uint32_t min;
    uint32_t hour;
    uint8_t index;
    snvs_hp_rtc_datetime_t rtcDate;
    snvs_lp_srtc_datetime_t srtcDate;
    snvs_hp_rtc_config_t snvsRtcConfig;
    snvs_lp_srtc_config_t snvsSrtcConfig;

    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Init SNVS_HP */
    /*
     * config->rtcCalEnable = false;
     * config->rtcCalValue = 0U;
     * config->periodicInterruptFreq = 0U;
     */
    SNVS_HP_RTC_GetDefaultConfig(&snvsRtcConfig);
    SNVS_HP_RTC_Init(SNVS, &snvsRtcConfig);

    /* Init SNVS_LP */
    /*
     * config->srtcCalEnable = false;
     * config->srtcCalValue = 0U;
     */
    SNVS_LP_SRTC_GetDefaultConfig(&snvsSrtcConfig);
    SNVS_LP_SRTC_Init(SNVS, &snvsSrtcConfig);

    PRINTF("SNVS LP SRTC example:\r\n");

    /* Set a start date time and start RT */
    srtcDate.year   = 2014U;
    srtcDate.month  = 12U;
    srtcDate.day    = 25U;
    srtcDate.hour   = 19U;
    srtcDate.minute = 0;
    srtcDate.second = 0;

    /* Set SRTC time to default time and date and start the SRTC */
    SNVS_LP_SRTC_SetDatetime(SNVS, &srtcDate);
    SNVS_LP_SRTC_StartTimer(SNVS);

    /* Synchronize RTC time and date with SRTC and start RTC */
    SNVS_HP_RTC_TimeSynchronize(SNVS);
    SNVS_HP_RTC_StartTimer(SNVS);

    PRINTF("RTC date and time has been synchronized with SRTC\r\n");

    /* Enable SNVS alarm interrupt */
    SNVS_HP_RTC_EnableInterrupts(SNVS, kSNVS_RTC_AlarmInterrupt);

    /* Enable at the NVIC */
    EnableIRQ(EXAMPLE_SNVS_IRQn);

    PRINTF("Set up time to wake up an alarm.\r\n");
    /* This loop will set the SNVS alarm */
    while (1)
    {
        busyWait = true;
        index    = 0;
        sec      = 0;
        min      = 0;
        hour     = 0;

        /* Get date time */
        SNVS_HP_RTC_GetDatetime(SNVS, &rtcDate);

        /* print default time */
        PRINTF("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", rtcDate.year, rtcDate.month, rtcDate.day,
               rtcDate.hour, rtcDate.minute, rtcDate.second);

        /* Get alarm time from user */
        PRINTF("Please input the number of second to wait for alarm and press enter \r\n");
        PRINTF("The second must be positive value\r\n");

        while (index != 0x0D)
        {
            index = GETCHAR();
            if ((index >= '0') && (index <= '9'))
            {
                PUTCHAR(index);
                sec = sec * 10 + (index - 0x30U);
            }
        }
        PRINTF("\r\n");

        /* Alarm can be set only for one day*/
        if (sec > (24 * 60 * 60))
        {
            PRINTF("Please input the number below 86000 and press enter \r\n");
            continue;
        }
        SNVS_HP_RTC_GetDatetime(SNVS, &rtcDate);
        if ((rtcDate.second + sec) < 60)
        {
            rtcDate.second += sec;
        }
        else
        {
            min += (rtcDate.second + sec) / 60U;
            rtcDate.second = (rtcDate.second + sec) % 60U;
        }

        if ((rtcDate.minute + min) < 60)
        {
            rtcDate.minute += min;
        }
        else
        {
            rtcDate.hour += (rtcDate.minute + min) / 60U;
            rtcDate.minute = (rtcDate.minute + min) % 60U;
        }

        if ((rtcDate.hour + hour) < 24)
        {
            rtcDate.hour += hour;
        }
        else
        {
            rtcDate.day += (rtcDate.hour + hour) / 24U;
            rtcDate.hour = (rtcDate.hour + hour) % 24U;
        }

        SNVS_HP_RTC_SetAlarm(SNVS, &rtcDate);

        /* Get alarm time */
        SNVS_HP_RTC_GetAlarm(SNVS, &rtcDate);

        /* Print alarm time */
        PRINTF("Alarm will occur at: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", rtcDate.year, rtcDate.month, rtcDate.day,
               rtcDate.hour, rtcDate.minute, rtcDate.second);

        /* Wait until alarm occurs */
        while (busyWait)
        {
        }

        PRINTF("\r\n Alarm occurs !!!! ");
    }
}
