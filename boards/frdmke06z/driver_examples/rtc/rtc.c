/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_rtc.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool alarmFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* RTC user callback */
static void RTC_UserCallback(void)
{
    alarmFlag = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t sec;
    uint8_t index;
    rtc_datetime_t date;
    rtc_config_t rtcConfig;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Init RTC */
    /*
     * config->clockSource = kRTC_BusClock;
     * config->prescaler = kRTC_ClockDivide_16_2048;
     * config->time_us = 1000000U;
     */
    RTC_GetDefaultConfig(&rtcConfig);
    RTC_Init(RTC, &rtcConfig);

    PRINTF("RTC example: set up time to wake up an alarm.\r\n");

    /* Set a start date time and start RT */
    date.year   = 2014U;
    date.month  = 12U;
    date.day    = 25U;
    date.hour   = 19U;
    date.minute = 0;
    date.second = 0;

    /* Set RTC time to default */
    RTC_SetDatetime(&date);

    RTC_SetAlarmCallback(RTC_UserCallback);
    /* Enable RTC Interrupt */
    RTC_EnableInterrupts(RTC, kRTC_InterruptEnable);
    NVIC_EnableIRQ(RTC_IRQn);
    while (1)
    {
        index     = 0;
        sec       = 0;
        alarmFlag = false;
        /* Get date time */
        RTC_GetDatetime(&date);

        /* print default time */
        PRINTF("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", date.year, date.month, date.day, date.hour,
               date.minute, date.second);

        /* Get alarm time from user */
        PRINTF("Please input the number of second to wait for alarm \r\n");
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

        /* Set alarm time in seconds */
        RTC_SetAlarm(sec);

        /* Get alarm time */
        RTC_GetAlarm(&date);

        /* Print alarm time */
        PRINTF("Alarm will occur at: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", date.year, date.month, date.day,
               date.hour, date.minute, date.second);

        /* Wait until alarm occurs */
        while (alarmFlag == false)
        {
        }

        PRINTF("\r\n Alarm occurs !!!! ");
    }
}
