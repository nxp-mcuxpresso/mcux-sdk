/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_sdram.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SDRAMC      SDRAM
#define SDRAM_START_ADDRESS (0x70000000U)
#define BUS_CLK_FREQ        CLOCK_GetFreq(kCLOCK_FlexBusClk)

#define SDRAM_EXAMPLE_DATALEN    (0x1000U)
#define SDRAM_EXAMPLE_WRITETIMES (1000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint32_t sdram_writeBuffer[SDRAM_EXAMPLE_DATALEN];
uint32_t sdram_readBuffer[SDRAM_EXAMPLE_DATALEN];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t index;
    uint32_t clockSrc;
    uint32_t datalen = SDRAM_EXAMPLE_DATALEN;
    uint32_t *sdram  = (uint32_t *)SDRAM_START_ADDRESS; /* SDRAM start address. */
    bool result      = true;

    /* Hardware initialize. */
    uint32_t soptReg;
    uint32_t fbReg;
    BOARD_InitPins();
    BOARD_InitPinsForUart();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Set clock out to flexbus CLKOUT. */
    CLOCK_SetClkOutClock(0);

    /* Sets the Flexbus security level*/
    soptReg    = SIM->SOPT2 & ~SIM_SOPT2_FBSL_MASK;
    SIM->SOPT2 = soptReg | SIM_SOPT2_FBSL(3);

    /* Enable the FB_BE_xx_yy signal in Flexbus */
    CLOCK_EnableClock(kCLOCK_Flexbus0);

    fbReg      = FB->CSPMCR & ~FB_CSPMCR_GROUP2_MASK;
    FB->CSPMCR = fbReg | FB_CSPMCR_GROUP2(2);
    fbReg      = FB->CSPMCR & ~FB_CSPMCR_GROUP3_MASK;
    FB->CSPMCR = fbReg | FB_CSPMCR_GROUP3(2);
    fbReg      = FB->CSPMCR & ~FB_CSPMCR_GROUP4_MASK;
    FB->CSPMCR = fbReg | FB_CSPMCR_GROUP4(2);
    fbReg      = FB->CSPMCR & ~FB_CSPMCR_GROUP5_MASK;
    FB->CSPMCR = fbReg | FB_CSPMCR_GROUP5(2);
    /* SDRAM initialize. */
    clockSrc = BUS_CLK_FREQ;
    PRINTF("\r\n SDRAM Example Start!\r\n");
    if (SDRAM_Init(EXAMPLE_SDRAMC, SDRAM_START_ADDRESS, clockSrc) != kStatus_Success)
    {
        PRINTF("\r\n SDRAM Init Failed\r\n");
    }

    PRINTF("\r\n SDRAM Memory Write Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);
    /* Prepare data and write to SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_writeBuffer[index]     = index;
        *(uint32_t *)(sdram + index) = sdram_writeBuffer[index];
    }
    PRINTF("\r\n SDRAM Write finished!\r\n");

    PRINTF("\r\n SDRAM Read Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);
    /* Read data from the SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_readBuffer[index] = *(uint32_t *)(sdram + index);
    }
    PRINTF("\r\n SDRAM Read finished!\r\n");

    PRINTF("\r\n SDRAM Write Data and Read Data Compare Start!\r\n");
    /* Compare the two buffers. */
    while (datalen--)
    {
        if (sdram_writeBuffer[datalen] != sdram_readBuffer[datalen])
        {
            result = false;
            PRINTF("\r\n SDRAM Write Data and Read Data Check Error!\r\n");
            break;
        }
    }

#if (defined TWR_K81F150M) || (defined TWR_K80F150M)
    /* For K80 serial board debug console, the sdramc pin is conflict with the uart pin
     so configure uart pin to enable the log print at the end of the example. */
    BOARD_InitPinsForUart();
#endif
    if (result)
    {
        PRINTF("\r\n SDRAM Write Data and Read Data Succeed.\r\n");
    }
    else
    {
        PRINTF("\r\n SDRAM Write Data and Read Data Failed.\r\n");
    }
    PRINTF("\r\n SDRAM Example End.\r\n");
    while (1)
    {
    }
}
