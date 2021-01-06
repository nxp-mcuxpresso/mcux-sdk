/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "fsl_kbi.h"
/*
 * This case tests the necessary API to enable the ENET transmission. It would call the functions sequentially in
 * polling mode.
 *
 */

#include "fsl_gpio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_KBI                             KBI0
#define EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO       kGPIO_PORTH
#define EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO_INDEX 0
#define EXAMPLE_KBI_PINS                        (10)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_keypress = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void KBI0_IRQHandler(void)
{
    if (KBI_IsInterruptRequestDetected(EXAMPLE_KBI))
    {
        /* Disable interrupts. */
        KBI_DisableInterrupts(EXAMPLE_KBI);
        /* Clear status. */
        KBI_ClearInterruptFlag(EXAMPLE_KBI);
        g_keypress = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    kbi_config_t kbiConfig;

    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        0,
    };

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Initialize for the output gpio signal. */
    GPIO_PinInit(EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO, EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO_INDEX, &config);
    // GPIOB->PDDR |= 0x01000000;
    // GPIOB->PCOR |= 0x01000000;

    PRINTF("\r\n KBI Driver Example Start.\r\n");

    kbiConfig.mode        = kKBI_EdgesDetect;
    kbiConfig.pinsEnabled = 1 << EXAMPLE_KBI_PINS;
    kbiConfig.pinsEdge    = 1 << EXAMPLE_KBI_PINS; /* Raising edge.*/
    KBI_Init(EXAMPLE_KBI, &kbiConfig);

    while (1)
    {
        /* Toggle to generate the edge which will trigger the KBI interrupt. */
        GPIO_PortToggle(EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO, 1u << EXAMPLE_KBI_SIGNAL_INPUT_REF_GPIO_INDEX);

        if (g_keypress)
        {
            PRINTF("\r\n The KBI keyboard interrupt has happened!\r\n");
            break;
        }
    }

    /* Deinitialize the module. */
    KBI_Deinit(EXAMPLE_KBI);

    PRINTF("\r\n KBI Driver Example End.\r\n");

    while (1)
    {
    }
}
