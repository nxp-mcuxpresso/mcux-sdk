/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_adapter_flash.h"
#include "fsl_flexspi.h"
#include "fsl_adapter_flexspi_hyper_flash_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* * @brief Flexspi clock update.
 *
 * This function speeds up/down flexspi clock frequency.
 *
 * @param clockSelect internal flexspi clock in DDR mode.
 */
void flexspi_clock_update(flexspi_clock_t clockSelect, FLEXSPI_Type *base)
{
    if (kHAL_Flash_Flexspi_Clock_High166M == clockSelect)
    {
        /* Program finished, speed up the clock to 166M. */
        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(base))
        {
        }
        FLEXSPI_Enable(base, false);
        CLOCK_DisableClock(kCLOCK_FlexSpi);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0); /* flexspi clock 332M, DDR mode, internal clock 166M. */
        CLOCK_EnableClock(kCLOCK_FlexSpi);
        FLEXSPI_Enable(base, true);
        /* Do software reset. */
        FLEXSPI_SoftwareReset(base);
    }
    else if (kHAL_Flash_Flexspi_Clock_Low42M == clockSelect)
    {
        /* Before program, speed down the clock to 42M. */
        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(base))
        {
        }
        FLEXSPI_Enable(base, false);
        CLOCK_DisableClock(kCLOCK_FlexSpi);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, 3); /* flexspi clock 332M, DDR mode, internal clock 42M. */
        CLOCK_EnableClock(kCLOCK_FlexSpi);
        FLEXSPI_Enable(base, true);
        /* Do software reset. */
        FLEXSPI_SoftwareReset(base);
    }
    else
    {
        ;
    }
}

uint32_t flexspi_get_frequency(void)
{
    uint32_t div;
    uint32_t fre;

    /* Clock divider:
       000 divided by 1
       001 divided by 2
       010 divided by 3
       011 divided by 4
       100 divided by 5
       101 divided by 6
       110 divided by 7
       111 divided by 8
     */
    div = CLOCK_GetDiv(kCLOCK_FlexspiDiv);
    /* Get frequency */
    fre = CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk) / (div + 0x01U);

    return fre;
}
void flexspi_clock_init(void)
{
    /*Set flexspi root clock to 166MHZ.*/
    const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};

    CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 26);   /* Set PLL3 PFD0 clock 332MHZ. */
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 3);   /* flexspi clock 83M, DDR mode, internal clock 42M. */
}
