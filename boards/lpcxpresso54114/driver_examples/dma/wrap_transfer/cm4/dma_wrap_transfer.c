/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"

#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SOURCE_BUFFER_LENGTH 8U
#define DEST_BUFFER_LENGTH   8U
#define DEMO_TRANSFER_WIDTH  uint32_t
#define DMA_DESCRIPTOR_NUM   2U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static dma_handle_t s_DMA_Handle;
static volatile bool s_Transfer_Done = false;
DMA_ALLOCATE_LINK_DESCRIPTORS(s_dma_table, DMA_DESCRIPTOR_NUM);

DMA_ALLOCATE_DATA_TRANSFER_BUFFER(static DEMO_TRANSFER_WIDTH s_srcBuffer[SOURCE_BUFFER_LENGTH], sizeof(uint32_t)) = {
    1, 2, 3, 4, 5, 6, 7, 8};
DMA_ALLOCATE_DATA_TRANSFER_BUFFER(static DEMO_TRANSFER_WIDTH s_destBuffer[DEST_BUFFER_LENGTH],
                                  sizeof(uint32_t)) = {0x00};
static dma_channel_trigger_t channelTrigger         = {
    .type  = kDMA_NoTrigger,
    .burst = kDMA_EdgeBurstTransfer4,
    .wrap  = kDMA_DstWrap,
};
/*******************************************************************************
 * Code
 ******************************************************************************/

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        s_Transfer_Done = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i = 0;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    BOARD_InitPins();
    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();

    /* Print source buffer */
    PRINTF("DMA wrap transfer example begin.\r\n\r\n");

    DMA_Init(DMA0);
    DMA_CreateHandle(&s_DMA_Handle, DMA0, 0);
    DMA_EnableChannel(DMA0, 0);
    DMA_SetCallback(&s_DMA_Handle, DMA_Callback, NULL);

    DMA_SetupChannelDescriptor(
        &(s_dma_table[0]),
        DMA_CHANNEL_XFER(true, false, false, true, sizeof(DEMO_TRANSFER_WIDTH), kDMA_AddressInterleave1xWidth,
                         kDMA_AddressInterleave1xWidth, sizeof(DEMO_TRANSFER_WIDTH) * SOURCE_BUFFER_LENGTH),
        s_srcBuffer, s_destBuffer, NULL, kDMA_DstWrap, kDMA_BurstSize4);

    DMA_SubmitChannelDescriptor(&s_DMA_Handle, &(s_dma_table[0]));

    DMA_SetChannelConfig(DMA0, 0U, &channelTrigger, false);
    DMA_DoChannelSoftwareTrigger(DMA0, 0U);
    /* Delay between two triggers. */
    for (i = 0; i < 0xFFU; i++)
    {
        __NOP();
    }
    DMA_DoChannelSoftwareTrigger(DMA0, 0U);

    while (s_Transfer_Done != true)
    {
    }

    /* Print destination buffer */
    PRINTF("Destination address wrap transfer:\r\n");
    for (i = 0; i < DEST_BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", s_destBuffer[i]);
    }
    s_Transfer_Done = false;

    DMA_SetupChannelDescriptor(
        &(s_dma_table[0]),
        DMA_CHANNEL_XFER(true, false, false, true, sizeof(DEMO_TRANSFER_WIDTH), kDMA_AddressInterleave1xWidth,
                         kDMA_AddressInterleave1xWidth, sizeof(DEMO_TRANSFER_WIDTH) * SOURCE_BUFFER_LENGTH),
        s_srcBuffer, s_destBuffer, NULL, kDMA_SrcWrap, kDMA_BurstSize4);

    DMA_SubmitChannelDescriptor(&s_DMA_Handle, &(s_dma_table[0]));

    channelTrigger.wrap = kDMA_SrcWrap;
    DMA_SetChannelConfig(DMA0, 0U, &channelTrigger, false);
    DMA_DoChannelSoftwareTrigger(DMA0, 0U);
    /* Delay between two triggers. */
    for (i = 0; i < 0xFFU; i++)
    {
        __NOP();
    }
    DMA_DoChannelSoftwareTrigger(DMA0, 0U);

    /* Wait for DMA transfer finish */
    while (s_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\nSource address wrap transfer:\r\n");
    for (i = 0; i < DEST_BUFFER_LENGTH; i++)
    {
        PRINTF("%d\t", s_destBuffer[i]);
    }
    PRINTF("\r\n\r\nDMA wrap transfer example finish.\r\n\r\n");

    while (1)
    {
    }
}
