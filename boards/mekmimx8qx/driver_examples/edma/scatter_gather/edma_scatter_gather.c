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
#include "fsl_edma.h"
#include <stdlib.h>

#include "fsl_lpuart.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DMA_CHANNEL  30U
#define EXAMPLE_DMA_BASEADDR ADMA__EDMA2

#define BUFF_LENGTH      8U
#define HALF_BUFF_LENGTH (BUFF_LENGTH / 2U)
#define TCD_QUEUE_SIZE   2U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;
volatile bool g_Transfer_Done[TCD_QUEUE_SIZE] = {0};

AT_NONCACHEABLE_SECTION_INIT(uint32_t srcAddr[BUFF_LENGTH])  = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U};
AT_NONCACHEABLE_SECTION_INIT(uint32_t destAddr[BUFF_LENGTH]) = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Allocate TCD memory poll */
AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE], sizeof(edma_tcd_t));
static volatile uint32_t count = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for EDMA transfer. */
void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done[count] = true;
    }
    count++;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0;
    edma_transfer_config_t transferConfig;
    edma_config_t userConfig;

    sc_ipc_t ipc = BOARD_InitRpc();

    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on Local EDMA for M4 Core. */
    sc_pm_set_resource_power_mode(ipc, SC_R_DMA_2_CH30, SC_PM_PW_MODE_ON);
    sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON);

    /* Enable irqsteer */
    IRQSTEER_Init(IRQSTEER);

    /* Enable EDMA irqsteer */
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_EDMA2_INT_IRQn);
    /* Print source buffer */
    PRINTF("\r\nEDMA scatter gather transfer example begin.\r\n\r\n");
    PRINTF("\r\nDestination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Configure EDMA one shot transfer */
    /*
     * userConfig.enableMasterIdReplication = true;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableDebugMode = false;
     * userConfig.enableBufferedWrites = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DMA_BASEADDR, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA_BASEADDR, EXAMPLE_DMA_CHANNEL);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

    EDMA_InstallTCDMemory(&g_EDMA_Handle, tcdMemoryPoolPtr, TCD_QUEUE_SIZE);
    /* Configure and submit transfer structure 1 */
    EDMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]),
                         sizeof(srcAddr[0]) * HALF_BUFF_LENGTH, sizeof(srcAddr[0]) * HALF_BUFF_LENGTH,
                         kEDMA_MemoryToMemory);
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    /* Configure and submit transfer structure 2 */
    EDMA_PrepareTransfer(&transferConfig, &srcAddr[4], sizeof(srcAddr[0]), &destAddr[4], sizeof(destAddr[0]),
                         sizeof(srcAddr[0]) * HALF_BUFF_LENGTH, sizeof(srcAddr[0]) * HALF_BUFF_LENGTH,
                         kEDMA_MemoryToMemory);
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);

    /* Trigger transfer start */
    EDMA_TriggerChannelStart(EXAMPLE_DMA_BASEADDR, EXAMPLE_DMA_CHANNEL);
    /* Wait for the first TCD finished */
    while (g_Transfer_Done[0] != true)
    {
    }

    /* Trigger the second tcd */
    EDMA_TriggerChannelStart(EXAMPLE_DMA_BASEADDR, EXAMPLE_DMA_CHANNEL);
    /* Wait for the second TCD finished */
    while (g_Transfer_Done[1] != true)
    {
    }

    /* Print destination buffer */
    PRINTF("\r\n\r\nEDMA scatter gather transfer example finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Free the memory space allocated */
    while (1)
    {
    }
}
