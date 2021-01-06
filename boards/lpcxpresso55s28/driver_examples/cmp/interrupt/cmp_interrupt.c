/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_cmp.h"
#include "fsl_inputmux.h"

#include "fsl_power.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_USART         USART0
#define DEMO_USART_CLK_SRC kCLOCK_Fro32M

#define DEMO_CMP_P_CHANNEL   1U
#define DEMO_CMP_N_CHANNEL   0U
#define DEMO_CMP_VREF_SOURCE KCMP_VREFSourceVDDA

#define DEMO_GPIO_BASE GPIO
#define DEMO_GPIO_PORT 1U
#define DEMO_GPIO_PIN  7U
#define DEMO_LED_ON    0U
#define DEMO_LED_OFF   1U


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_CmpInterruptFlag = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void ACMP_IRQHandler(void)
{
    CMP_ClearInterrupt();
    if (true == CMP_GetOutput())
    {
        /* Turn on LED when P-side voltage is greater than that of N-side. */
        GPIO_PinWrite(DEMO_GPIO_BASE, DEMO_GPIO_PORT, DEMO_GPIO_PIN, DEMO_LED_ON);
    }
    else
    {
        /* Turn off LED when P-side voltage is lower than that of N-side. */
        GPIO_PinWrite(DEMO_GPIO_BASE, DEMO_GPIO_PORT, DEMO_GPIO_PIN, DEMO_LED_OFF);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    cmp_config_t mCmpConfigStruct;
    cmp_vref_config_t mCmpVrefConfigStruct;

    /* Initialize hardware. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach clock for USART(debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* reset FLEXCOMM for USART */
    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);

    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();
    BOARD_InitPins();

    POWER_DisablePD(kPDRUNCFG_PD_COMP);
    EnableIRQ(ACMP_IRQn);

    PRINTF("CMP interrupt driver example\r\n");

    /*
     * config->enableHysteresis    = true;
     * config->enableLowPower      = true;
     * config->filterClockDivider  = kCMP_FilterClockDivide1;
     * config->filterSampleMode    = kCMP_FilterSampleMode0;
     */
    CMP_GetDefaultConfig(&mCmpConfigStruct);
    CMP_Init(&mCmpConfigStruct);

    /* Set VREF source. */
    mCmpVrefConfigStruct.vrefSource = KCMP_VREFSourceVDDA;
    mCmpVrefConfigStruct.vrefValue  = 15U; /* Select half of the reference voltage. */
    CMP_SetVREF(&mCmpVrefConfigStruct);

    /* Set P-side and N-side input channels. */
    CMP_SetInputChannels(DEMO_CMP_P_CHANNEL, DEMO_CMP_N_CHANNEL);

    /* Enable CMP interrupt. */
    CMP_EnableInterrupt(kCMP_EdgeRisingFalling);

    while (1)
    {
    }
}
