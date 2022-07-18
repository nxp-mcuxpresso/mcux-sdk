/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  systick_utils.c
 * @brief Encapsulates the ARM sysTick counter, which is used for computing delays.
 *         ARM-core specific function that enables the ARM systick timer on Kinetis uCs.
 *         the timer is 24 bit so allows measurement of intervals up to 2^24/CORE_SYSTICK_HZ secs=0.35s for a 48MHz uC.
*/

#include "issdk_hal.h"

// SysTick register definitions based on CMSIS definitions.
#define SYST_CSR SysTick->CTRL // SysTick Control & Status Register
#define SYST_RVR SysTick->LOAD // SysTick Reload Value Register
#define SYST_CVR SysTick->VAL  // SysTick Current Value Register

uint32_t g_ovf_stamp;
volatile uint32_t g_ovf_counter = 0;

#ifndef SDK_OS_FREE_RTOS
// SDK specific SysTick Interrupt Handler
void SysTick_Handler(void)
{
    g_ovf_counter += 1;
}
#endif

// ARM-core specific function to enable systicks.
void BOARD_SystickEnable(void)
{
    SYST_CSR = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
               SysTick_CTRL_ENABLE_Msk; // Enable systick from internal clock with Interrupts.
    SYST_RVR = 0x00FFFFFFu;             // Set reload to maximum 24 bit value.
    return;
}

// ARM-core specific function to store the current systick timer ticks.
void BOARD_SystickStart(int32_t *pStart)
{
    // Store the 24 bit systick timer.
    g_ovf_stamp = g_ovf_counter;
    *pStart = SYST_CVR & 0x00FFFFFF;
}

// ARM-core specific function to compute the elapsed systick timer ticks.
int32_t BOARD_SystickElapsedTicks(int32_t *pStart)
{
    int32_t elapsed;

    // Subtract the stored start ticks and check for wraparound down through zero.
    elapsed = *pStart - (SYST_CVR & 0x00FFFFFF);
    elapsed += SYST_RVR * (g_ovf_counter - g_ovf_stamp);

    return elapsed;
}

// ARM-core specific function to compute the elapsed time in micro seconds.
uint32_t BOARD_SystickElapsedTime_us(int32_t *pStart)
{
    uint32_t time_us, elapsed;
    uint32_t systemCoreClock;

    elapsed = BOARD_SystickElapsedTicks(pStart);
    systemCoreClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    time_us = COUNT_TO_USEC(elapsed, systemCoreClock);

    // Update the 24 bit systick timer.
    BOARD_SystickStart(pStart);

    return time_us;
}

// ARM-core specific function to insert delays in milli seconds.
void BOARD_DELAY_ms(uint32_t delay_ms)
{
    int32_t start, elapsed;
    uint32_t systemCoreClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    BOARD_SystickStart(&start);
    do // Loop for requested number of ms.
    {
        elapsed = BOARD_SystickElapsedTicks(&start);
    } while(COUNT_TO_MSEC(elapsed, systemCoreClock) < delay_ms);
}
