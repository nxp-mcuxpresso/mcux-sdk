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
#define DEMO_RING_BUFFER_TRANSFER_TIMES 3U /* determine the transfer times between source/destination buffer */
#define BUFF_LENGTH   4
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void demo_restart_channel_config(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static dma_handle_t s_DMA_Handle_0;
static dma_handle_t s_DMA_Handle_1;
uint32_t srcAddr[BUFF_LENGTH] = {0x00};
SDK_ALIGN(uint32_t destAddr[BUFF_LENGTH], 16U);
const dma_channel_link_config_t dma_channel_link = {
    .linkType = kDMA_ChannelLinkChannel1AfterBCR0,
    .channel1 = DMA_CHANNEL_1,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/* User callback function for DMA transfer. */
void DMA_Callback_1(dma_handle_t *handle, void *param)
{
    /*
     * reconfigure the channel 1
     * The channel 1 reconfiguration should be done before channel 0 transfer exhaust, otherwise the ring buffer will
     * halt, if such issue happen, suggest to increase the channel 0 transfer size
     */
    demo_restart_channel_config();
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
    PRINTF("DMA ring buffer example begin.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&s_DMA_Handle_0, DMA0, DMA_CHANNEL_0);
    DMA_CreateHandle(&s_DMA_Handle_1, DMA0, DMA_CHANNEL_1);

    DMA_SetCallback(&s_DMA_Handle_1, DMA_Callback_1, NULL);

    /* channel 0 handling the ring buffer
     *
     * 1. source/dest address will wrap back after the transfer exhaust
     * 2. channel 1 will be triggered after channel 0 transfer exhaust, then channel 1 will clear the channel 0 DONE
     * flag and reconfigure the BCR field, after that channel 0 is in ready state again, transfer between srcAddr and
     * destAddr will be restarted.
     */
    DMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]), sizeof(srcAddr),
                        kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&s_DMA_Handle_0, &transferConfig, 0);
    DMA_SetModulo(DMA0, DMA_CHANNEL_0, kDMA_Modulo16Bytes, kDMA_Modulo16Bytes);
    DMA_SetChannelLinkConfig(DMA0, DMA_CHANNEL_0, &dma_channel_link);
    DMA_EnableAutoStopRequest(DMA0, DMA_CHANNEL_0, false);

    /* channel 1 configuration for channel 0 restart */
    demo_restart_channel_config();

    DMA_StartTransfer(&s_DMA_Handle_0);

    /* Software fill the srcAddr to simulate peripheral -> fifo
     *  Trigger the channel 0 transfer one by one to simulate the perpheral fifo -> ring buffer.
     */
    for (i = 0U; i < DEMO_RING_BUFFER_TRANSFER_TIMES * BUFF_LENGTH; i++)
    {
        srcAddr[i % BUFF_LENGTH] = i;
        DMA_TriggerChannelStart(DMA0, DMA_CHANNEL_0);
    }

    /* Print destination buffer */
    PRINTF("\r\n\r\nDMA ring buffer example finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", destAddr[i]);
    }
    while (1)
    {
    }
}

/*
 * This function will enable another DMA channel which is used for update the BCR of the channel 0(the channel used for
 * ring buffer data transfer) after the channel 0 transfer exhaust, that is to say the channel 0 will be restarted
 * immediately after the DONE bit is cleared and BCR is reloaded
 */
void demo_restart_channel_config(void)
{
    dma_transfer_config_t transferConfig;
    uint32_t bcr[2] = {0U};

    bcr[0] = sizeof(destAddr) | DMA_DSR_BCR_DONE_MASK; /* clear DONE bit firstly */
    bcr[1] = sizeof(destAddr);                         /* reconfiure the BCR field */
    DMA_PrepareTransferConfig(&transferConfig, bcr, 4U, (void *)&(DMA0->DMA[DMA_CHANNEL_0].DSR_BCR), 4U, 8U,
                              kDMA_AddrIncrementPerTransferWidth, kDMA_AddrNoIncrement);
    DMA_SubmitTransfer(&s_DMA_Handle_1, &transferConfig, kDMA_EnableInterrupt);
    DMA_EnableCycleSteal(DMA0, DMA_CHANNEL_1, false);
}
