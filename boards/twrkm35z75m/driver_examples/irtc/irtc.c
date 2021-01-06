/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include "fsl_irtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile static bool alarmHappen = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief ISR for Alarm interrupt
 *
 * This function change state of busyWait.
 */
void RTC_IRQHandler(void)
{
    if (IRTC_GetStatusFlags(RTC) & kIRTC_AlarmFlag)
    {
        alarmHappen = true;
        /* Unlock to allow register write operation */
        IRTC_SetWriteProtection(RTC, false);
        /*Clear alarm flag */
        IRTC_ClearStatusFlags(RTC, kIRTC_AlarmInterruptEnable);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    irtc_datetime_t datetime, alarmDatetime, datetimeGet;
    irtc_config_t irtcConfig;

    datetime.year    = 2015;
    datetime.month   = 1;
    datetime.day     = 21;
    datetime.weekDay = 3;
    datetime.hour    = 18;
    datetime.minute  = 55;
    datetime.second  = 30;

    alarmDatetime.year    = 2015;
    alarmDatetime.month   = 1;
    alarmDatetime.day     = 21;
    alarmDatetime.hour    = 18;
    alarmDatetime.minute  = 55;
    alarmDatetime.second  = 33;
    alarmDatetime.weekDay = 0; /* Don't care for alarm, however this should be set to a valid value */

    /* Init the IRTC module */
    /*
     * irtcConfig.wakeupSelect = true;
     * irtcConfig.timerStdMask = false;
     * irtcConfig.alrmMatch = kRTC_MatchSecMinHr;
     */
    IRTC_GetDefaultConfig(&irtcConfig);
    if (IRTC_Init(RTC, &irtcConfig) == kStatus_Fail)
    {
        return 1;
    }

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Enable the RTC 32KHz oscillator at CFG0 by writing a 0 */
    RTC->GP_DATA_REG &= ~1U;

    /* Clear all Tamper events by writing a 1 to the bits */
    RTC->TAMPER_SCR |= RTC_TAMPER_SCR_TMPR_STS_MASK;

    PRINTF("RTC Example START:\r\n");

    IRTC_SetDatetime(RTC, &datetime);
    IRTC_GetDatetime(RTC, &datetimeGet);
    PRINTF("\r\nStart Time is %d/%d/%d %d:%d:%2d\r\n", datetimeGet.year, datetimeGet.month, datetimeGet.day,
           datetimeGet.hour, datetimeGet.minute, datetimeGet.second);
    IRTC_SetAlarm(RTC, &alarmDatetime);

    /* Enable RTC alarm interrupt */
    IRTC_EnableInterrupts(RTC, kIRTC_AlarmInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(RTC_IRQn);

    while (!alarmHappen)
    {
    }

    PRINTF("\r\nRing, ring, ring");
    IRTC_GetDatetime(RTC, &datetimeGet);
    PRINTF("\r\nAlarm Time is %d/%d/%d %d:%d:%2d\r\n", datetimeGet.year, datetimeGet.month, datetimeGet.day,
           datetimeGet.hour, datetimeGet.minute, datetimeGet.second);
    PRINTF("\r\nRTC Example END.\r\n");

    for (;;)
    {
    }
}
