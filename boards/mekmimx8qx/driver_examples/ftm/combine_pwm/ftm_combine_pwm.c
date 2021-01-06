/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_ftm.h"

#include "fsl_common.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel pair used for board */
#define BOARD_FTM_BASEADDR ADMA__FTM0
/* FTM channel pair 2 works with FTM channels 0 and 1 */
#define BOARD_FTM_CHANNEL_PAIR kFTM_Chnl_0

/* Interrupt number and interrupt handler for the FTM base address used */
#define FTM_INTERRUPT_NUMBER IRQSTEER_4_IRQn
#define FTM_LED_HANDLER      ADMA_FTM0_INT_IRQHandler

/* Interrupt to enable and flag to read */
#define FTM_CHANNEL_INTERRUPT_ENABLE kFTM_Chnl0InterruptEnable
#define FTM_CHANNEL_FLAG             kFTM_Chnl0Flag

/* System clock source for FTM driver is bus clock fixed to 160M, if user
   selects external clock source, then CLOCK_SetIpFreq(kCLOCK_DMA_Ftm0, xxx)
   could be used to change the external clock rate. */
#define FTM_SOURCE_CLOCK (160000000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool ftmIsrFlag          = false;
volatile bool brightnessUp        = true; /* Indicate LED is brighter or dimmer */
volatile uint8_t updatedDutycycle = 10U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0U;
    for (i = 0U; i < 80000U; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

void FTM_LED_HANDLER(void)
{
    ftmIsrFlag = true;

    if (brightnessUp)
    {
        /* Increase duty cycle until it reach limited value, don't want to go upto 100% duty cycle
         * as channel interrupt will not be set for 100%
         */
        if (++updatedDutycycle >= 99U)
        {
            updatedDutycycle = 99U;
            brightnessUp     = false;
        }
    }
    else
    {
        /* Decrease duty cycle until it reach limited value */
        if (--updatedDutycycle == 1U)
        {
            brightnessUp = true;
        }
    }

    if ((FTM_GetStatusFlags(BOARD_FTM_BASEADDR) & FTM_CHANNEL_FLAG) == FTM_CHANNEL_FLAG)
    {
        /* Clear interrupt flag.*/
        FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, FTM_CHANNEL_FLAG);
    }
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_LowTrue;

    /* Configure ftm params with frequency 24kHZ */
    ftmParam.chnlNumber            = BOARD_FTM_CHANNEL_PAIR;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = updatedDutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = true;
    ftmParam.enableDeadtime        = true;

    /* Board pin, clock, debug console init */
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on FTM */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_FTM_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
        PRINTF("Error: sc_pm_set_resource_power_mode SC_R_FTM_0 failed\r\n");

    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }
    /* Enable interrupt in irqsteer */
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_FTM0_INT_IRQn);

    /* Print a note to terminal */
    PRINTF("\r\nFTM example to output combined complementary PWM signals on two channels\r\n");
    PRINTF("\r\nYou will see a change in LED brightness if an LED is connected to the FTM pin");
    PRINTF("\r\nIf no LED is connected to the FTM pin, then probe the signal using an oscilloscope");

    FTM_GetDefaultConfig(&ftmInfo);
    /* Update deadTimePrescale for fast clock*/
    ftmInfo.deadTimePrescale = kFTM_Deadtime_Prescale_16;
    /* Need a deadtime value of about 650nsec */
    ftmInfo.deadTimeValue = ((uint64_t)FTM_SOURCE_CLOCK * 650) / 1000000000 / 16;

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Setup output of a combined PWM signal */
    FTM_SetupPwm(BOARD_FTM_BASEADDR, &ftmParam, 1U, kFTM_EdgeAlignedCombinedPwm, 24000U, FTM_SOURCE_CLOCK);

    /* Enable interrupt flag on one of the channels from the pair */
    FTM_EnableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);

    /* Enable at the NVIC */
    EnableIRQ(FTM_INTERRUPT_NUMBER);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);

    while (1)
    {
        /* Use interrupt to update the PWM dutycycle */
        if (true == ftmIsrFlag)
        {
            /* Disable interrupt to retain current dutycycle for a few seconds */
            FTM_DisableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);

            ftmIsrFlag = false;

            /* Disable output on each channel of the pair before updating the dutycycle */
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)(BOARD_FTM_CHANNEL_PAIR * 2), 0U);
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)((BOARD_FTM_CHANNEL_PAIR * 2) + 1), 0U);

            /* Update PWM duty cycle on the channel pair */
            FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, BOARD_FTM_CHANNEL_PAIR, kFTM_EdgeAlignedCombinedPwm,
                                   updatedDutycycle);

            /* Software trigger to update registers */
            FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

            /* Start output on each channel of the pair with updated dutycycle */
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)(BOARD_FTM_CHANNEL_PAIR * 2), pwmLevel);
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)((BOARD_FTM_CHANNEL_PAIR * 2) + 1), pwmLevel);

            /* Delay to view the updated PWM dutycycle */
            delay();

            /* Enable interrupt flag to update PWM dutycycle */
            FTM_EnableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);
        }
    }
}
