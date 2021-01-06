/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DMAMUX0 DMAMUX
#define BUFF_LENGTH   4
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_SOURCE    63
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
dma_handle_t g_DMA_Handle_0;
dma_handle_t g_DMA_Handle_1;
volatile bool g_Transfer_Done                    = false;
uint32_t srcAddr[BUFF_LENGTH]                    = {0x01, 0x02, 0x03, 0x04};
uint32_t srcAddr1[BUFF_LENGTH]                   = {0x05, 0x06, 0x07, 0x08};
uint32_t destAddr[BUFF_LENGTH]                   = {0x00, 0x00, 0x00, 0x00};
uint32_t destAddr1[BUFF_LENGTH]                  = {0x00, 0x00, 0x00, 0x00};
const dma_channel_link_config_t dma_channel_link = {
    .linkType = kDMA_ChannelLinkChannel1,
    .channel1 = DMA_CHANNEL_1,
};
/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}

/* Main function. Excuate DMA transfer with transactional APIs. */
int main(void)
{
    uint32_t i = 0;
    dma_transfer_config_t transferConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Print source buffer */
    PRINTF("DMA channel link example begin.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL_0, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL_0);
    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle_0, DMA0, DMA_CHANNEL_0);
    DMA_CreateHandle(&g_DMA_Handle_1, DMA0, DMA_CHANNEL_1);

    DMA_SetCallback(&g_DMA_Handle_1, DMA_Callback, NULL);
    DMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]), sizeof(srcAddr),
                        kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle_0, &transferConfig, kDMA_EnableInterrupt);
    DMA_SetChannelLinkConfig(DMA0, DMA_CHANNEL_0, &dma_channel_link);

    memset(&transferConfig, 0U, sizeof(dma_transfer_config_t));
    DMA_PrepareTransfer(&transferConfig, srcAddr1, sizeof(srcAddr1[0]), destAddr1, sizeof(destAddr1[0]),
                        sizeof(srcAddr1), kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle_1, &transferConfig, kDMA_EnableInterrupt);

    DMA_StartTransfer(&g_DMA_Handle_0);
    /* Wait for DMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\n\r\nDMA channel link example finish.\r\n\r\n");
    PRINTF("Destination Buffer 0:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    PRINTF("\r\nDestination Buffer 1:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    while (1)
    {
    }
}
