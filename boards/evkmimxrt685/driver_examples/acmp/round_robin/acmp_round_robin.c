/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_rtc.h"
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ACMP_BASEADDR CMP

#define DEMO_ACMP_IRQ_ID           ACMP_IRQn
#define DEMO_ACMP_IRQ_HANDLER_FUNC ACMP_IRQHandler

/* Select which channels is used to do round robin checker.
 * Example sets positive port as fixed port with DAC output as comparison reference. So Pre-state mask bit high
 * represents the pre-state of corresponding channel's input voltage is higher than DAC output voltage. If the round
 * robin check result shows that corresponding channel's actual input voltage is lower than DAC output voltage, wakeup
 * event will be generated. The case of pre-state mask bit low is contrary to the case of pre-state mask bit high.
 */
#define DEMO_ACMP_ROUND_ROBIN_CHANNELS_CHECKER_MASK   0x01U /* ACMP CHAN-A. */
#define DEMO_ACMP_ROUND_ROBIN_CHANNELS_PRE_STATE_MASK 0x01U /* ACMP CHAN-A. */
#define DEMO_ACMP_ROUND_ROBIN_PERIOD_MILLISECONDS     1000U
#define DEMO_ACMP_ROUND_ROBIN_FIXED_CHANNEL           0x07U /* DAC output */

/*!< Power down all unnecessary blocks and enable RBB during deep sleep. */
#define EXAMPLE_DEEPSLEEP_RUNCFG0 (SYSCTL0_PDRUNCFG0_ACMP_PD_MASK | SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK)
#define EXAMPLE_DEEPSLEEP_RAM_APD 0xFFFFF8U
#define EXAMPLE_DEEPSLEEP_RAM_PPD 0x0U
#define EXAMPLE_EXCLUDE_FROM_DEEPSLEEP                                                                            \
    (((const uint32_t[]){EXAMPLE_DEEPSLEEP_RUNCFG0,                                                               \
                         (SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_APD_MASK | SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_PPD_MASK), \
                         EXAMPLE_DEEPSLEEP_RAM_APD, EXAMPLE_DEEPSLEEP_RAM_PPD}))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitAcmpRoundRobinTrigger(uint32_t triggerPeroid_Ms);
void BOARD_ClearAcmpRoundRobinTrigger(void);
void BOARD_EnterStopMode(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_InitAcmpRoundRobinTrigger(uint32_t triggerPeroid_Ms)
{
    uint32_t cycles = MSEC_TO_COUNT(triggerPeroid_Ms, CLOCK_GetOsc32KFreq());
    acmp_discrete_mode_config_t config;

    ACMP_GetDefaultDiscreteModeConfig(&config);
    /* In the example, DAC is selected on positve port. It need to be continuous mode.
     * The other port should be discrete mode. */
    config.enablePositiveChannelDiscreteMode = false;
    config.enableNegativeChannelDiscreteMode = true;
    /* Both port under 1.8V, no divider needed */
    config.enableResistorDivider = false;
    ACMP_SetDiscreteModeConfig(DEMO_ACMP_BASEADDR, &config);

    /* Set up trigger timer */
    if (cycles == 0)
    {
        cycles = 2; /* Set RR_TIMER_RELOAD to 1 */
    }
    cycles = cycles > CMP_RR_TIMER_CR_RR_TIMER_RELOAD_MASK ? CMP_RR_TIMER_CR_RR_TIMER_RELOAD_MASK : cycles - 1;
    /* Set RR_TIMER_RELOAD and start counting. */
    DEMO_ACMP_BASEADDR->RR_TIMER_CR = CMP_RR_TIMER_CR_RR_TIMER_RELOAD(cycles) | CMP_RR_TIMER_CR_RR_TIMER_ENA_MASK;

    /* Enable round robin mode. */
    DEMO_ACMP_BASEADDR->C0 = (DEMO_ACMP_BASEADDR->C0 | CMP_C0_SE_MASK | CMP_C0_WE_MASK) & ~CMP_C0_CFx_MASK;
}

void BOARD_ClearAcmpRoundRobinTrigger(void)
{
    DEMO_ACMP_BASEADDR->RR_TIMER_CR = 0;
}

void BOARD_EnterStopMode(void)
{
    /* Enable deep sleep IRQ. */
    EnableDeepSleepIRQ(DEMO_ACMP_IRQ_ID);
    /* Enter deep sleep mode by using power API. */
    POWER_EnterDeepSleep(EXAMPLE_EXCLUDE_FROM_DEEPSLEEP);
}
void DEMO_ACMP_IRQ_HANDLER_FUNC(void)
{
    uint32_t statusFlags;

    statusFlags = ACMP_GetStatusFlags(DEMO_ACMP_BASEADDR);
    ACMP_ClearStatusFlags(DEMO_ACMP_BASEADDR, statusFlags);

    statusFlags = ACMP_GetRoundRobinStatusFlags(DEMO_ACMP_BASEADDR);
    ACMP_ClearRoundRobinStatusFlags(DEMO_ACMP_BASEADDR, statusFlags);

    BOARD_ClearAcmpRoundRobinTrigger();
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    acmp_config_t acmpConfigStruct;
    acmp_channel_config_t channelConfigStruct;
    acmp_dac_config_t dacConfigStruct;
    acmp_round_robin_config_t roundRobinConfigStruct;
    uint8_t ch;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Let acmp run on main clock with divider 2 (250Mhz). */
    CLOCK_AttachClk(kMAIN_CLK_to_ACMP_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivAcmpClk, 2);

    POWER_DisablePD(kPDRUNCFG_PD_ACMP);
    RESET_PeripheralReset(kACMP0_RST_SHIFT_RSTn);
    /* Make sure ACMP voltage reference available*/
    POWER_SetAnalogBuffer(true);

    /* Enable OSC32K */
    CLOCK_EnableOsc32K(true);
    RTC_Init(RTC);
    CLOCK_AttachClk(kOSC32K_to_32KHZWAKE_CLK);

    /* Configure ACMP. */
    /*
     * acmpConfigStruct.enableHighSpeed = false;
     * acmpConfigStruct.enableInvertOutput = false;
     * acmpConfigStruct.useUnfilteredOutput = false;
     * acmpConfigStruct.enablePinOut = false;
     * acmpConfigStruct.offsetMode = kACMP_OffsetLevel0;
     * acmpConfigStruct.hysteresisMode = kACMP_HysteresisLevel0;
     */
    ACMP_GetDefaultConfig(&acmpConfigStruct);
    ACMP_Init(DEMO_ACMP_BASEADDR, &acmpConfigStruct);

#if defined(FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT) && (FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT == 1U)
    /* Configure channel. Select the positive port input from DAC and negative port input from minus mux input. */
    channelConfigStruct.positivePortInput = kACMP_PortInputFromDAC;
    channelConfigStruct.negativePortInput = kACMP_PortInputFromMux;
#endif
    /* Plus mux input must be different from minus mux input in round robin mode although they aren't functional.
     * Please refer to the reference manual to get detail description.
     */
    channelConfigStruct.plusMuxInput  = 0U;
    channelConfigStruct.minusMuxInput = 1U;
    ACMP_SetChannelConfig(DEMO_ACMP_BASEADDR, &channelConfigStruct);

    /* Configure DAC. */
    dacConfigStruct.referenceVoltageSource = kACMP_VrefSourceVin1;
    dacConfigStruct.DACValue               = 0x7FU; /* Half of referene voltage. */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT == 1U)
    dacConfigStruct.enableOutput = true;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT == 1U)
    dacConfigStruct.workMode = kACMP_DACWorkLowSpeedMode;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT */
    ACMP_SetDACConfig(DEMO_ACMP_BASEADDR, &dacConfigStruct);

    /* Configure round robin mode. */
    roundRobinConfigStruct.fixedPort          = kACMP_FixedPlusPort;
    roundRobinConfigStruct.fixedChannelNumber = DEMO_ACMP_ROUND_ROBIN_FIXED_CHANNEL;
    roundRobinConfigStruct.checkerChannelMask = DEMO_ACMP_ROUND_ROBIN_CHANNELS_CHECKER_MASK;
    roundRobinConfigStruct.sampleClockCount   = 0U;
    roundRobinConfigStruct.delayModulus       = 0U;
    ACMP_SetRoundRobinConfig(DEMO_ACMP_BASEADDR, &roundRobinConfigStruct);

    ACMP_EnableInterrupts(DEMO_ACMP_BASEADDR, kACMP_RoundRobinInterruptEnable);
    EnableIRQ(DEMO_ACMP_IRQ_ID);

    ACMP_SetRoundRobinPreState(DEMO_ACMP_BASEADDR, DEMO_ACMP_ROUND_ROBIN_CHANNELS_PRE_STATE_MASK);

    /* Set round robin comparison trigger period in STOP mode. */
    BOARD_InitAcmpRoundRobinTrigger(DEMO_ACMP_ROUND_ROBIN_PERIOD_MILLISECONDS);

    ACMP_Enable(DEMO_ACMP_BASEADDR, true);

    PRINTF(
        "\r\nExample to demonstrate low power wakeup by round robin comparison! \
           \r\nIn order to wakeup the MCU, please change the analog input voltage to be different from original pre-state setting.\r\n");

    while (1)
    {
        PRINTF("\r\nPress %c for enter: Stop Mode\r\n", 'S');

        ch = GETCHAR();

        if ((ch >= 'a') && (ch <= 'z'))
        {
            ch -= 'a' - 'A';
        }
        if (ch == 'S')
        {
            PRINTF("\r\nThe system entered into stop mode.\r\n");
            BOARD_EnterStopMode();

            /* Wakeup and print information. */
            PRINTF("\r\nThe system exited from stop mode!\r\n");
            while (true)
            {
            }
        }
        else
        {
            PRINTF("Wrong value!\r\n");
        }
    }
}
