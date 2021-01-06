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
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DMA    DMA0
#define EXAMPLE_DMAMUX DMAMUX0
#define DEMO_EDMA_CHANNEL_0 0
#define DEMO_EDMA_CHANNEL_1 1

#define BUFFER_LENGTH      8U
#define HALF_BUFFER_LENGTH (BUFFER_LENGTH / 2U)
#define TCD_QUEUE_SIZE     1U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle_0;
edma_handle_t g_EDMA_Handle_1;
volatile bool g_Transfer_Done_0 = false;
volatile bool g_Transfer_Done_1 = false;

AT_NONCACHEABLE_SECTION_INIT(uint32_t srcAddr[BUFFER_LENGTH])  = {0x01U, 0x02U, 0x03U, 0x04U,
                                                                 0x05U, 0x06U, 0x07U, 0x08U};
AT_NONCACHEABLE_SECTION_INIT(uint32_t destAddr[BUFFER_LENGTH]) = {0x00U, 0x00U, 0x00U, 0x00U,
                                                                  0x00U, 0x00U, 0x00U, 0x00U};
AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for EDMA transfer. */
void EDMA_Callback_0(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done_0 = true;
    }
}

void EDMA_Callback_1(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done_1 = true;
    }
}

void EDMA_Major_Loop_Link(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;
    g_Transfer_Done_0 = false;
    g_Transfer_Done_1 = false;

    memset(destAddr, 0U, sizeof(destAddr));

    /* Configure DMAMUX */
    DMAMUX_Init(EXAMPLE_DMAMUX);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, true);
#else
    DMAMUX_SetSource(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0);

    PRINTF("\r\nedma major loop link start\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    /* Configure EDMA one shot transfer */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DMA, &userConfig);
    memset(&transferConfig, 0, sizeof(edma_transfer_config_t));
    memset(&tcdMemoryPoolPtr, 0, sizeof(edma_tcd_t));
    EDMA_CreateHandle(&g_EDMA_Handle_0, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle_0, EDMA_Callback_0, NULL);
    EDMA_ResetChannel(g_EDMA_Handle_0.base, g_EDMA_Handle_0.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[0], sizeof(srcAddr[0]), &destAddr[0], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                      /* minor loop bytes :4 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts: 1 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdSetChannelLink(tcdMemoryPoolPtr, kEDMA_MajorLink, DEMO_EDMA_CHANNEL_1);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_TcdEnableAutoStopRequest(tcdMemoryPoolPtr, true);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    memset(&transferConfig, 0, sizeof(edma_transfer_config_t));
    memset(&tcdMemoryPoolPtr, 0, sizeof(edma_tcd_t));
    EDMA_CreateHandle(&g_EDMA_Handle_1, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_1);
    EDMA_SetCallback(&g_EDMA_Handle_1, EDMA_Callback_1, NULL);
    EDMA_ResetChannel(g_EDMA_Handle_1.base, g_EDMA_Handle_1.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[4], sizeof(srcAddr[0]), &destAddr[4], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* minor loop bytes 4 * 4 = 16 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts:1 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    /* channel 1 link to itself, since channel 0 has already finished transfer */
    EDMA_TcdSetChannelLink(tcdMemoryPoolPtr, kEDMA_MinorLink, DEMO_EDMA_CHANNEL_1);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_1, tcdMemoryPoolPtr);

    EDMA_EnableChannelRequest(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done_0 != true)
    {
    }

    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done_1 != true)
    {
    }

    PRINTF("\r\nedma major loop link finished\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    EDMA_Deinit(EXAMPLE_DMA);
}

void EDMA_Minor_Loop_Link(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;
    g_Transfer_Done_0 = false;
    g_Transfer_Done_1 = false;

    memset(destAddr, 0U, sizeof(destAddr));

    PRINTF("edma minor loop link start\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    /* Configure EDMA one shot transfer */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DMA, &userConfig);

    memset(&transferConfig, 0, sizeof(edma_transfer_config_t));
    memset(&tcdMemoryPoolPtr, 0, sizeof(edma_tcd_t));
    EDMA_CreateHandle(&g_EDMA_Handle_0, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle_0, EDMA_Callback_0, NULL);
    EDMA_ResetChannel(g_EDMA_Handle_0.base, g_EDMA_Handle_0.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[0], sizeof(srcAddr[0]), &destAddr[0], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                      /* minor loop bytes: 4 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts : 4 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdSetChannelLink(tcdMemoryPoolPtr, kEDMA_MinorLink, DEMO_EDMA_CHANNEL_1);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    memset(&transferConfig, 0, sizeof(edma_transfer_config_t));
    memset(&tcdMemoryPoolPtr, 0, sizeof(edma_tcd_t));
    EDMA_CreateHandle(&g_EDMA_Handle_1, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_1);
    EDMA_SetCallback(&g_EDMA_Handle_1, EDMA_Callback_1, NULL);
    EDMA_ResetChannel(g_EDMA_Handle_1.base, g_EDMA_Handle_1.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[4], sizeof(srcAddr[0]), &destAddr[4], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                      /* minor loop bytes: 4 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts : 4 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdSetChannelLink(tcdMemoryPoolPtr, kEDMA_MinorLink, DEMO_EDMA_CHANNEL_0);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_1, tcdMemoryPoolPtr);

    EDMA_TriggerChannelStart(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done_0 != true)
    {
    }
    /* mannual trigger channel 1 for last minor loop, since channel 0 last minor loop is finished, no trigger will be
     * sent out */
    EDMA_TriggerChannelStart(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_1);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done_1 != true)
    {
    }

    PRINTF("\r\nedma minor loop link finished\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    EDMA_Deinit(EXAMPLE_DMA);
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Print source buffer */
    PRINTF("EDMA channel link example.\r\n\r\n");

    /* The case demostrate minor loop channel link, that is a channel link happened after minor loop finished */
    EDMA_Minor_Loop_Link();
    /* The case demostrate major loop channel link, that is a channel link happened after major loop finished */
    EDMA_Major_Loop_Link();
    while (1)
    {
    }
}
