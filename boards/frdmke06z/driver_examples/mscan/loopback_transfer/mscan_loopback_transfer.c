/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_mscan.h"
#include "pin_mux.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */
#define EXAMPLE_MSCAN          MSCAN
#define EXAMPLE_MSCAN_CLK_FREQ CLOCK_GetFreq(kCLOCK_Osc0ErClk)

#define NODE_ID1    0x801
#define MSCAN_IDMR0 (MSCAN_REIDR3_RERTR_MASK | (MSCAN_REIDR1_RSRR_MASK | MSCAN_REIDR1_REIDE_MASK) << 16U)
#define MSCAN_IDMR1 (MSCAN_REIDR3_RERTR_MASK | (MSCAN_REIDR1_RSRR_MASK | MSCAN_REIDR1_REIDE_MASK) << 16U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool txComplete = false;
volatile bool rxComplete = false;
mscan_handle_t mscanHandle;
mscan_mb_transfer_t txXfer, rxXfer;
mscan_frame_t txFrame, rxFrame;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief MSCAN Call Back function
 */
static void mscan_callback(MSCAN_Type *base, mscan_handle_t *handle, status_t status, void *userData)
{
    switch (status)
    {
        /* Process MSCAN Rx event. */
        case kStatus_MSCAN_RxIdle:
            rxComplete = true;
            break;

        /* Process MSCAN Tx event. */
        case kStatus_MSCAN_TxIdle:
            txComplete = true;
            break;

        default:
            break;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    mscan_config_t mscanConfig;

    /* Initialize board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n==MSCAN loopback example -- Start.==\r\n\r\n");

    MSCAN_GetDefaultConfig(&mscanConfig);

    /* Acceptance filter configuration. */
    mscanConfig.filterConfig.u32IDAR0 = MSCAN_RX_MB_EXT_MASK(NODE_ID1);
    mscanConfig.filterConfig.u32IDAR1 = MSCAN_RX_MB_EXT_MASK(NODE_ID1);
    mscanConfig.filterConfig.u32IDMR0 = MSCAN_IDMR0;
    mscanConfig.filterConfig.u32IDMR1 = MSCAN_IDMR1;

    /* Enable loopback mode. */
    mscanConfig.enableLoopBack = true;

    /* Initialize MSCAN module. */
    MSCAN_Init(EXAMPLE_MSCAN, &mscanConfig, EXAMPLE_MSCAN_CLK_FREQ);

    /* Create MSCAN handle structure and set call back function. */
    MSCAN_TransferCreateHandle(EXAMPLE_MSCAN, &mscanHandle, mscan_callback, NULL);

    /* Start receive data through Rx Message Buffer. */
    rxXfer.frame = &rxFrame;
    rxXfer.mask  = kMSCAN_RxFullInterruptEnable;
    MSCAN_TransferReceiveNonBlocking(EXAMPLE_MSCAN, &mscanHandle, &rxXfer);

    /* Prepare Tx Frame for sending. */
    txFrame.ID_Type.ID = NODE_ID1;
    txFrame.format     = kMSCAN_FrameFormatExtend;
    txFrame.type       = kMSCAN_FrameTypeData;
    txFrame.DLR        = 8;
    txFrame.dataWord0  = 0x44332211;
    txFrame.dataWord1  = 0x88776655;

    PRINTF("Send message!\r\n");
    PRINTF("tx word0 = 0x%x\r\n", txFrame.dataWord0);
    PRINTF("tx word1 = 0x%x\r\n", txFrame.dataWord1);

    /* Send data through Tx Message Buffer. */
    txXfer.frame = &txFrame;
    txXfer.mask  = kMSCAN_TxEmptyInterruptEnable;
    MSCAN_TransferSendNonBlocking(EXAMPLE_MSCAN, &mscanHandle, &txXfer);

    /* Waiting for Rx Message finish. */
    while ((!rxComplete) || (!txComplete))
    {
    };

    PRINTF("\r\nReceived message!\r\n");
    PRINTF("rx word0 = 0x%x\r\n", rxFrame.dataWord0);
    PRINTF("rx word1 = 0x%x\r\n", rxFrame.dataWord1);

    PRINTF("\r\n==MSCAN loopback example -- Finish.==\r\n");

    while (1)
    {
        __WFI();
    }
}
