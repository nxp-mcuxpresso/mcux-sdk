/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_sdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SDMAARM SDMAARM1
#define BUFF_LENGTH 4U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
sdma_handle_t g_SDMA_Handle = {0};

volatile bool g_Transfer_Done = false;
AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t context, 4);

AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint32_t srcAddr[BUFF_LENGTH], 4) = {0x01, 0x02, 0x03, 0x04};
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t destAddr[BUFF_LENGTH], 16);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for SDMA transfer. */
void SDMA_Callback(sdma_handle_t *handle, void *param, bool transferDone, uint32_t bds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i                            = 0;
    sdma_transfer_config_t transferConfig = {0U};
    sdma_config_t userConfig;

    /* M7 has its local cache and enabled by default,
     * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
     * non-cacheable before accessing this address region */
    BOARD_InitMemory();

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print source buffer */
    PRINTF("\r\nSDMA memory to memory transfer example begin.\r\n");
    PRINTF("\r\nDestination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    /* Configure SDMA one shot transfer */
    SDMA_GetDefaultConfig(&userConfig);
    SDMA_Init(EXAMPLE_SDMAARM, &userConfig);
    SDMA_CreateHandle(&g_SDMA_Handle, EXAMPLE_SDMAARM, 1, &context);
    SDMA_SetCallback(&g_SDMA_Handle, SDMA_Callback, NULL);
    SDMA_PrepareTransfer(&transferConfig, (uint32_t)srcAddr, (uint32_t)destAddr, sizeof(srcAddr[0]),
                         sizeof(destAddr[0]), sizeof(srcAddr[0]), sizeof(srcAddr), 0, kSDMA_PeripheralTypeMemory,
                         kSDMA_MemoryToMemory);
    SDMA_SubmitTransfer(&g_SDMA_Handle, &transferConfig);
    SDMA_SetChannelPriority(EXAMPLE_SDMAARM, 1, 2U);
    SDMA_StartTransfer(&g_SDMA_Handle);
    /* Wait for SDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\nSDMA memory to memory transfer example finish.\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    while (1)
    {
    }
}
