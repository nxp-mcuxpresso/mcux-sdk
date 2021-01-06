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

#define BUFFER_LENGTH              8U
#define HALF_BUFFER_LENGTH         (BUFFER_LENGTH / 2U)
#define TCD_QUEUE_SIZE             2U
#define DEMO_DMA_PING_PONG_COUNTER 5
#define DEMO_EDMA_CHANNEL_0        0
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;
volatile uint32_t g_TransferCounter;
volatile bool g_transferDone                                   = false;
AT_NONCACHEABLE_SECTION_INIT(uint32_t srcAddr[BUFFER_LENGTH])  = {0x01U, 0x02U, 0x03U, 0x04U,
                                                                 0x05U, 0x06U, 0x07U, 0x08U};
AT_NONCACHEABLE_SECTION_INIT(uint32_t destAddr[BUFFER_LENGTH]) = {0x00U, 0x00U, 0x00U, 0x00U,
                                                                  0x00U, 0x00U, 0x00U, 0x00U};
/* Allocate TCD memory poll */
AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for EDMA transfer. */
void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    g_TransferCounter++;

    if (g_TransferCounter > DEMO_DMA_PING_PONG_COUNTER)
    {
        g_transferDone = true;
        EDMA_AbortTransfer(&g_EDMA_Handle);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Print source buffer */
    PRINTF("EDMA ping pong transfer example begin.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Configure DMAMUX */
    DMAMUX_Init(EXAMPLE_DMAMUX);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, true);
#else
    DMAMUX_SetSource(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0);
    /* Configure EDMA one shot transfer */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DMA, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

    /* prepare descroptor 0 */
    EDMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                      /* minor loop bytes: 4 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts : 4 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, &tcdMemoryPoolPtr[1]);

    /* prepare descriptor 1 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[4], sizeof(srcAddr[0]), &destAddr[4], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                      /* minor loop bytes: 4 */
                         sizeof(srcAddr[0]) * HALF_BUFFER_LENGTH, /* major loop counts : 4 */
                         kEDMA_MemoryToMemory);
    EDMA_TcdSetTransferConfig(&tcdMemoryPoolPtr[1], &transferConfig, &tcdMemoryPoolPtr[0]);
    EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[1], kEDMA_MajorInterruptEnable);

    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    EDMA_StartTransfer(&g_EDMA_Handle);

    /* Wait for EDMA transfer finish */
    while (!g_transferDone)
    {
    }

    /* Print destination buffer */
    PRINTF("\r\n\r\nEDMA ping pong transfer example finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Free the memory space allocated */
    while (1)
    {
    }
}
