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

#define BUFFER_LENGTH      8 * 2
#define HALF_BUFFER_LENGTH (BUFFER_LENGTH / 2)
#define TCD_QUEUE_SIZE     1U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;
volatile bool g_Transfer_Done = false;
/*
 * The total buffer length is 16+8 words,
 * since the minor loop interleave case require 8 minor loop counts,
 * each minor loop transfer 2 words and each minor loop will offset 1 word.
 */
AT_NONCACHEABLE_SECTION_INIT(uint32_t srcAddr[BUFFER_LENGTH + HALF_BUFFER_LENGTH]) = {
    0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU, 0x00U,
};
/*
 * The total buffer length is 16+8 words,
 * since the minor loop interleave case require 8 minor loop counts,
 * each minor loop transfer 2 words and each minor loop will offset 1 word.
 */
AT_NONCACHEABLE_SECTION_INIT(uint32_t destAddr[BUFFER_LENGTH + HALF_BUFFER_LENGTH]) = {0x00U, 0x00U, 0x00U, 0x00U,
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
        g_Transfer_Done = true;
    }
}

void edma_single_transfer_interleave(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;
    g_Transfer_Done = false;

    memset(destAddr, 0U, sizeof(destAddr));

    PRINTF("\r\nedma signle transfer interleave start\r\n");
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
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback_0, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransferConfig(&transferConfig, &srcAddr[0], sizeof(srcAddr[0]), sizeof(srcAddr[0]), /* source offset */
                               &destAddr[0], sizeof(destAddr[0]), sizeof(destAddr[0]) * 2,           /* dest offset */
                               sizeof(srcAddr[0]),                       /* minor loop bytes : 4 */
                               sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH); /* major loop counts : 8 */
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    EDMA_StartTransfer(&g_EDMA_Handle);

    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }

    PRINTF("\r\nedma signle transfer interleave finished\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    EDMA_Deinit(EXAMPLE_DMA);
}

void edma_minor_loop_interleave(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;
    g_Transfer_Done = false;

    edma_minor_offset_config_t minorOffset = {
        .enableSrcMinorOffset = true, .enableDestMinorOffset = true, .minorOffset = 4};

    memset(destAddr, 0U, sizeof(destAddr));

    PRINTF("\r\nedma minor loop interleave start\r\n");
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
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback_0, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransferConfig(&transferConfig, &srcAddr[0], sizeof(srcAddr[0]), sizeof(srcAddr[0]), /* source offset */
                               &destAddr[0], sizeof(destAddr[0]), sizeof(destAddr[0]),               /* dest offset */
                               sizeof(srcAddr[0]) * 2U,             /* minor loop bytes : 8 */
                               sizeof(srcAddr[0]) * BUFFER_LENGTH); /* major loop counts : 8 */
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdSetMinorOffsetConfig(tcdMemoryPoolPtr, &minorOffset);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_TcdEnableAutoStopRequest(tcdMemoryPoolPtr, true);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    EDMA_StartTransfer(&g_EDMA_Handle);

    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }

    PRINTF("\r\nedma minor loop interleave finished\r\n");
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
    PRINTF("EDMA interleave transfer example.\r\n");

    /* Configure DMAMUX */
    DMAMUX_Init(EXAMPLE_DMAMUX);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, true);
#else
    DMAMUX_SetSource(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0);

    /*
     * The case demostrate interleave transfer using the source/dest offset applied to every single transfer between
     * source and destination address.
     */
    edma_single_transfer_interleave();

    /*
     * The case demostrate interleave transfer using minor loop offset feature, that is a configurable offset can be
     * applied to source/dest address will minor loop finished.
     */
    edma_minor_loop_interleave();
    while (1)
    {
    }
}
