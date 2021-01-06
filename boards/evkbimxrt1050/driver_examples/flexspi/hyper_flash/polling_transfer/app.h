/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _APP_H_
#define _APP_H_

/*${header:start}*/
#include "fsl_flexspi.h"
/*${header:end}*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
#define EXAMPLE_FLEXSPI                        FLEXSPI
#define FLASH_SIZE                             0x10000U /* 64*1024 Kbyte */
#define EXAMPLE_FLEXSPI_AMBA_BASE              FlexSPI_AMBA_BASE
#define FLASH_PAGE_SIZE                        512U
#define EXAMPLE_SECTOR                         250U
#define SECTOR_SIZE                            0x40000U /* 256 Kbyte */
#define EXAMPLE_FLEXSPI_CLOCK                  kCLOCK_FlexSpi
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA    0
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA   1
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS  2
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE 4
#define HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR 6
#define HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM 10
#define HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP   12
#define CUSTOM_LUT_LENGTH                      64
#define CACHE_MAINTAIN                         0x01U
/*${macro:end}*/

typedef enum
{
    kFLEXSPI_Clock_High166M, /* Flexspi clock 332M, DDR mode, internal clock 166M. */
    kFLEXSPI_Clock_Low42M,   /* Flexspi clock 83M, DDR mode, internal clock 42M. */
} flexspi_clock_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*${prototype:start}*/
void BOARD_InitHardware(void);

static inline void flexspi_clock_init(void)
{
    // Set flexspi root clock to 166MHZ.
    const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};

    CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 26);   /* Set PLL3 PFD0 clock 332MHZ. */
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 3);   /* flexspi clock 83M, DDR mode, internal clock 42M. */
}

/*!
 * @brief Flexspi clock update.
 *
 * This function speeds up/down flexspi clock frequency.
 *
 * @param clockSelect internal flexspi clock in DDR mode.
 */
static inline void flexspi_clock_update(flexspi_clock_t clockSelect)
{
    if (kFLEXSPI_Clock_High166M == clockSelect)
    {
        /* Program finished, speed up the clock to 166M. */
        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(EXAMPLE_FLEXSPI))
        {
        }
        FLEXSPI_Enable(EXAMPLE_FLEXSPI, false);
        CLOCK_DisableClock(EXAMPLE_FLEXSPI_CLOCK);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0); /* flexspi clock 332M, DDR mode, internal clock 166M. */
        CLOCK_EnableClock(EXAMPLE_FLEXSPI_CLOCK);
        FLEXSPI_Enable(EXAMPLE_FLEXSPI, true);
        /* Do software reset. */
        FLEXSPI_SoftwareReset(EXAMPLE_FLEXSPI);
    }
    else if (kFLEXSPI_Clock_Low42M == clockSelect)
    {
        /* Before program, speed down the clock to 42M. */
        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(EXAMPLE_FLEXSPI))
        {
        }
        FLEXSPI_Enable(EXAMPLE_FLEXSPI, false);
        CLOCK_DisableClock(EXAMPLE_FLEXSPI_CLOCK);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, 3); /* flexspi clock 332M, DDR mode, internal clock 42M. */
        CLOCK_EnableClock(EXAMPLE_FLEXSPI_CLOCK);
        FLEXSPI_Enable(EXAMPLE_FLEXSPI, true);
        /* Do software reset. */
        FLEXSPI_SoftwareReset(EXAMPLE_FLEXSPI);
    }
    else
    {
        ;
    }
}

static inline uint32_t flexspi_get_frequency(void)
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

/*${prototype:end}*/

#endif /* _APP_H_ */
