/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BUFF_LENGTH 4U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
dma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done                                                           = false;
DMA_ALLOCATE_DATA_TRANSFER_BUFFER(uint32_t s_srcBuffer[BUFF_LENGTH], sizeof(uint32_t))  = {0x01, 0x02, 0x03, 0x04};
DMA_ALLOCATE_DATA_TRANSFER_BUFFER(uint32_t s_destBuffer[BUFF_LENGTH], sizeof(uint32_t)) = {0x00, 0x00, 0x00, 0x00};
/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
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
    uint32_t i = 0;
    dma_channel_config_t transferConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Print source buffer */
    PRINTF("DMA memory to memory transfer example begin.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", s_destBuffer[i]);
    }
    /* Configure DMA one shot transfer */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, 0);
    DMA_EnableChannel(DMA0, 0);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareChannelTransfer(&transferConfig, s_srcBuffer, &s_destBuffer[0],
                               DMA_CHANNEL_XFER(false, false, true, false, 4, kDMA_AddressInterleave1xWidth,
                                                kDMA_AddressInterleave1xWidth, 16),
                               kDMA_MemoryToMemory, NULL, NULL);
    DMA_SubmitChannelTransfer(&g_DMA_Handle, &transferConfig);

    DMA_StartTransfer(&g_DMA_Handle);
    /* Wait for DMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\n\r\nDMA memory to memory transfer example finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", s_destBuffer[i]);
    }
    while (1)
    {
    }
}
