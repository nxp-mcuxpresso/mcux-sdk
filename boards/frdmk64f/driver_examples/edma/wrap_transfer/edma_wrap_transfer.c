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

#define BUFFER_LENGTH       8
#define TCD_QUEUE_SIZE      2U
#define DEMO_EDMA_CHANNEL_0 0
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;
volatile bool g_Transfer_Done = false;
/* must align with the modulo range */
AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint32_t srcAddr[BUFFER_LENGTH], 16)  = {0x01U, 0x02U, 0x03U, 0x04U,
                                                                           0x05U, 0x06U, 0x07U, 0x08U};
AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint32_t destAddr[BUFFER_LENGTH], 16) = {0x00U, 0x00U, 0x00U, 0x00U,
                                                                            0x00U, 0x00U, 0x00U, 0x00U};
/* Allocate TCD memory poll */
AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for EDMA transfer. */
void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }
}

void edma_major_loop_wrap(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;
    g_Transfer_Done = false;

    memset(destAddr, 0U, sizeof(destAddr));

    PRINTF("\r\nedma major loop wrap start\r\n");
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
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransferConfig(&transferConfig, &srcAddr[0], sizeof(srcAddr[0]), sizeof(srcAddr[0]), /* source offset */
                               &destAddr[0], sizeof(destAddr[0]), sizeof(destAddr[0]),               /* dest offset */
                               sizeof(srcAddr[0]) * 2U,             /* minor loop bytes: 8*/
                               sizeof(srcAddr[0]) * BUFFER_LENGTH); /* major loop counts : 4 */
    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_TcdSetMajorOffsetConfig(tcdMemoryPoolPtr, -BUFFER_LENGTH * 4, -BUFFER_LENGTH * 4);
    EDMA_TcdEnableAutoStopRequest(tcdMemoryPoolPtr, true);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    EDMA_StartTransfer(&g_EDMA_Handle);

    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }

    memset(destAddr, 0U, sizeof(destAddr));
    g_Transfer_Done = false;
    EDMA_StartTransfer(&g_EDMA_Handle);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }

    PRINTF("\r\nedma major loop wrap finished\r\n");
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }

    EDMA_Deinit(EXAMPLE_DMA);
}

void edma_modulo_wrap(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;

    PRINTF("\r\nedma modulo wrap start\r\n");
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
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
    /* Configure and submit transfer structure 1 */
    EDMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]),
                         sizeof(srcAddr[0]),                 /* minor loop bytes : 4 */
                         sizeof(srcAddr[0]) * BUFFER_LENGTH, /* major loop counts : 8 */
                         kEDMA_MemoryToMemory);

    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);
    EDMA_TcdSetModulo(tcdMemoryPoolPtr, kEDMA_Modulo16bytes, kEDMA_ModuloDisable);
    EDMA_TcdEnableInterrupts(tcdMemoryPoolPtr, kEDMA_MajorInterruptEnable);
    EDMA_TcdEnableAutoStopRequest(tcdMemoryPoolPtr, true);
    EDMA_InstallTCD(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0, tcdMemoryPoolPtr);

    EDMA_EnableChannelRequest(EXAMPLE_DMA, DEMO_EDMA_CHANNEL_0);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\nEDMA modulo wrap finished.\r\n");
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
    PRINTF("EDMA wrap transfer example.\r\n");

    /* Configure DMAMUX */
    DMAMUX_Init(EXAMPLE_DMAMUX);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, true);
#else
    DMAMUX_SetSource(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, DEMO_EDMA_CHANNEL_0);

    /*
     * The modulo feature of the eDMA provides the ability to implement a circular data queue
     * in which the size of the queue is a power of 2. MOD is a 5-bit field for the source and
     * destination in the TCD, and it specifies which lower address bits increment from their
     * original value after the address+offset calculation. All upper address bits remain the same
     * as in the original value.
     *
     * This case demostrate a 2^4 byte (16-byte) size source buffer queue, the transfer between source and dest will be:
     * origin source address + 0  -> dest + 0
     * origin sourceaddress + 4   -> dest + 4
     * origin source address + 8  -> dest + 8
     * origin source address + 16 -> dest + 12
     * origin source address + 0  -> dest + 16
     * origin source address + 4  -> dest + 20
     * origin source address + 8  -> dest + 24
     * origin source address + 16 -> dest + 28
     *'
     */
    edma_modulo_wrap();

    /*
     * The case desmostrate a wrap transfer using the major loop address offset feature that is when the major loop
     * finished, a configured offset can applied to the source and dest address.
     */
    edma_major_loop_wrap();

    /* Free the memory space allocated */
    while (1)
    {
    }
}
