/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdlib.h>
#include <string.h>
#include "fsl_debug_console.h"
#include "fsl_enet.h"
#include "fsl_phy.h"

#include "fsl_enet_mdio.h"
#include "fsl_phylan8720a.h"
#include "pin_mux.h"
#include "board.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_ENET_BASE    ENET
#define EXAMPLE_PHY_ADDRESS  (0x00U)

/* MDIO operations. */
#define EXAMPLE_MDIO_OPS lpc_enet_ops
/* PHY operations. */
#define EXAMPLE_PHY_OPS phylan8720a_ops
#define ENET_RXBD_NUM               (4)
#define ENET_TXBD_NUM               (4)
#define ENET_RXBUFF_SIZE            (ENET_FRAME_MAX_FRAMELEN)
#define ENET_BuffSizeAlign(n)       ENET_ALIGN(n, ENET_BUFF_ALIGNMENT)
#define ENET_ALIGN(x, align)        ((unsigned int)((x) + ((align)-1)) & (unsigned int)(~(unsigned int)((align)-1)))
#define ENET_EXAMPLE_FRAME_HEADSIZE (14U)
#define ENET_EXAMPLE_DATA_LENGTH    (1000U)
#define ENET_EXAMPLE_FRAME_SIZE     (ENET_EXAMPLE_DATA_LENGTH + ENET_EXAMPLE_FRAME_HEADSIZE)
#define ENET_EXAMPLE_PACKAGETYPE    (4U)
#define ENET_EXAMPLE_SEND_COUNT     (20U)
#define ENET_PTP_SYNC_MSG           (0x00U)
#ifndef PHY_AUTONEGO_TIMEOUT_COUNT
#define PHY_AUTONEGO_TIMEOUT_COUNT (500000U)
#endif

#if defined(__GNUC__)
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(ENET_BUFF_ALIGNMENT)))
#endif
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif
#ifndef __ALIGN_BEGIN
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __ALIGN_BEGIN __attribute__((aligned(ENET_BUFF_ALIGNMENT)))
#elif defined(__ICCARM__)
#define __ALIGN_BEGIN
#endif
#endif
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ENET_BuildPtpEventFrame(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(__ICCARM__)
#pragma data_alignment = ENET_BUFF_ALIGNMENT
#endif
__ALIGN_BEGIN enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM] __ALIGN_END;
#if defined(__ICCARM__)
#pragma data_alignment = ENET_BUFF_ALIGNMENT
#endif
__ALIGN_BEGIN enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM] __ALIGN_END;

/* Buffers for store receive and transmit timestamp. */
enet_ptp_time_data_t g_rxPtpTsBuff[ENET_RXBD_NUM];
enet_ptp_time_data_t g_txPtpTsBuff[ENET_TXBD_NUM];

enet_handle_t g_handle = {0};
/* The MAC address for ENET device. */
uint8_t g_macAddr[6]     = {0xd4, 0xbe, 0xd9, 0x45, 0x22, 0x60};
uint8_t multicastAddr[6] = {0x01, 0x00, 0x5e, 0x00, 0x01, 0x81};
uint8_t g_frame[ENET_EXAMPLE_PACKAGETYPE][ENET_EXAMPLE_FRAME_SIZE];
uint8_t *g_txbuff[ENET_TXBD_NUM];
uint32_t g_txIdx     = 0;
uint8_t g_txbuffIdx  = 0;
uint8_t g_txCosumIdx = 0;
uint32_t g_testIdx   = 0;

/*! @brief Enet PHY and MDIO interface handler. */
static mdio_handle_t mdioHandle = {.ops = &EXAMPLE_MDIO_OPS};
static phy_handle_t phyHandle   = {.phyAddr = EXAMPLE_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &EXAMPLE_PHY_OPS};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void ENET_BuildPtpEventFrame(void)
{
    uint8_t index;
    uint8_t mGAddr[6] = {0x01, 0x00, 0x5e, 0x01, 0x01, 0x1};

    for (index = 0; index < ENET_EXAMPLE_PACKAGETYPE; index++)
    {
        /* Build for PTP event message frame. */
        memcpy(&g_frame[index][0], &mGAddr[0], 6);
        /* The six-byte source MAC address. */
        memcpy(&g_frame[index][6], &g_macAddr[0], 6);
        /* The type/length: if data length is used make sure it's smaller than 1500 */
        g_frame[index][12]    = 0x08U;
        g_frame[index][13]    = 0x00U;
        g_frame[index][0x0EU] = 0x40;
        g_frame[index][0x24U] = (kENET_PtpEventPort >> 8) & 0xFFU;
        g_frame[index][0x25U] = kENET_PtpEventPort & 0xFFU;
        g_frame[index][0x17U] = 0x11U;
        /* Add ptp event message type: sync message. */
        g_frame[index][0x2AU - 12U] = ENET_PTP_SYNC_MSG;
        /* Add sequence id. */
        g_frame[index][0x48U - 12U] = 0;
        g_frame[index][0x48U - 11U] = 0;

        g_frame[index][ENET_EXAMPLE_FRAME_SIZE - 1] = index % 0xFFU;
    }
}

void ENET_IntCallback(ENET_Type *base, enet_handle_t *handle, enet_event_t event, uint8_t channel, void *param)
{
    switch (event)
    {
        case kENET_TxIntEvent:
            /* Free tx buffers. */
            free(g_txbuff[g_txCosumIdx]);
            g_txCosumIdx = (g_txCosumIdx + 1) % ENET_TXBD_NUM;
            break;
        default:
            break;
    }
}

int main(void)
{
    enet_config_t config;
    phy_config_t phyConfig      = {0};
    enet_ptp_config_t ptpConfig = {0};
    uint32_t rxbuffer[ENET_RXBD_NUM];
    uint8_t index;
    void *buff;
    uint32_t refClock = 50000000; /* 50MHZ for rmii reference clock. */
    phy_speed_t speed;
    phy_duplex_t duplex;
    uint32_t length = 0;
    uint8_t *buffer;
    uint32_t count = 0;
    uint32_t timedelay;
    status_t status;
    uint64_t second;
    uint32_t nanosecond;
    enet_ptp_time_data_t ptpData;
    bool link     = false;
    bool autonego = false;

    for (index = 0; index < ENET_RXBD_NUM; index++)
    {
        /* This is for rx buffers, static alloc and dynamic alloc both ok. use as your wish. */
        buff = malloc(ENET_RXBUFF_SIZE);
        if (buff)
        {
            rxbuffer[index] = (uint32_t)buff;
        }
        else
        {
            PRINTF("Mem Alloc fail\r\n");
        }
    }

    /* prepare the buffer configuration. */
    enet_buffer_config_t buffConfig[1] = {{
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        &g_txBuffDescrip[0],
        &g_txBuffDescrip[0],
        &g_rxBuffDescrip[0],
        &g_rxBuffDescrip[ENET_RXBD_NUM],
        &rxbuffer[0],
        ENET_BuffSizeAlign(ENET_RXBUFF_SIZE),
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        &g_rxPtpTsBuff[0],
        &g_txPtpTsBuff[0],
    }};

    /* Hardware Initialization. */
    CLOCK_EnableClock(kCLOCK_InputMux);
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitPins();
    BOARD_BootClockPLL180M();
    BOARD_InitDebugConsole();

    PRINTF("\r\nENET example start.\r\n");

    phyConfig.phyAddr        = EXAMPLE_PHY_ADDRESS;
    phyConfig.autoNeg        = true;
    mdioHandle.resource.base = EXAMPLE_ENET_BASE;

    /* Initialize PHY and wait auto-negotiation over. */
    PRINTF("Wait for PHY init...\r\n");
    do
    {
        status = PHY_Init(&phyHandle, &phyConfig);
        if (status == kStatus_Success)
        {
            PRINTF("Wait for PHY link up...\r\n");
            /* Wait for auto-negotiation success and link up */
            count = PHY_AUTONEGO_TIMEOUT_COUNT;
            do
            {
                PHY_GetAutoNegotiationStatus(&phyHandle, &autonego);
                PHY_GetLinkStatus(&phyHandle, &link);
                if (autonego && link)
                {
                    break;
                }
            } while (--count);
            if (!autonego)
            {
                PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
            }
        }
    } while (!(link && autonego));

    /* Get default configuration 100M RMII. */
    ENET_GetDefaultConfig(&config);

    /* Use the actual speed and duplex when phy success to finish the autonegotiation. */
    PHY_GetLinkSpeedDuplex(&phyHandle, &speed, &duplex);
    config.miiSpeed  = (enet_mii_speed_t)speed;
    config.miiDuplex = (enet_mii_duplex_t)duplex;

    /* Initialize ENET. */
    /* Shoule enable the multicast receive and enable the store and forward
     * to make the timestamp is always updated correclty in the descriptors. */
    config.specialControl = kENET_MulticastAllEnable | kENET_StoreAndForward;
    ptpConfig.tsRollover  = kENET_BinaryRollover;
    config.ptpConfig      = &ptpConfig;
    ENET_Init(EXAMPLE_ENET_BASE, &config, &g_macAddr[0], refClock);

    /* Initialize Descriptor. */
    ENET_DescriptorInit(EXAMPLE_ENET_BASE, &config, &buffConfig[0]);

    /* Create the handler. */
    ENET_CreateHandler(EXAMPLE_ENET_BASE, &g_handle, &config, &buffConfig[0], ENET_IntCallback, NULL);
    /* Active TX/RX. */
    ENET_StartRxTx(EXAMPLE_ENET_BASE, 1, 1);

    /* Build ptp message for sending and active for receiving. */
    ENET_BuildPtpEventFrame();

    for (index = 1; index <= 10; index++)
    {
        ENET_Ptp1588GetTimer(EXAMPLE_ENET_BASE, &second, &nanosecond);
        PRINTF(" Get the %d-th time", index);
        PRINTF(" %d second,", (uint32_t)second);
        PRINTF(" %d nanosecond  \r\n", nanosecond);
        for (timedelay = 0; timedelay < 0xFFFFFU; timedelay++)
        {
        }
    }

    PRINTF("\r\nTransmission start now!\r\n");

    while (1)
    {
        /* Get the Frame size */
        length = 0;
        status = ENET_GetRxFrameSize(EXAMPLE_ENET_BASE, &g_handle, &length, 0);
        /* Call ENET_ReadFrame when there is a received frame. */
        if ((status == kStatus_Success) && (length != 0))
        {
            /* Received valid frame. Deliver the rx buffer with the size equal to length. */
            uint8_t *data = (uint8_t *)malloc(length);
            if (data)
            {
                status = ENET_ReadFrame(EXAMPLE_ENET_BASE, &g_handle, data, length, 0);
                if (status == kStatus_Success)
                {
                    PRINTF(" One frame received. the length %d \r\n", length);
                    memset((void *)&ptpData, 0, sizeof(enet_ptp_time_data_t));
                    ptpData.messageType = ENET_PTP_SYNC_MSG;
                    if (ENET_GetRxFrameTime(&g_handle, &ptpData) == kStatus_Success)
                    {
                        PRINTF(" the timestamp is %d second,", (uint32_t)ptpData.timeStamp.second);
                        PRINTF(" %d nanosecond  \r\n", ptpData.timeStamp.nanosecond);
                    }
                }

                free(data);
            }
            else
            {
                /* Discard due to the lack of buffers. */
                ENET_ReadFrame(EXAMPLE_ENET_BASE, &g_handle, NULL, 0, 0);
                PRINTF("No availabe memory.\r\n");
            }
        }
        else if (status == kStatus_ENET_RxFrameError)
        {
            /* update the receive buffer. */
            ENET_ReadFrame(EXAMPLE_ENET_BASE, &g_handle, NULL, 0, 0);
        }

        if (g_testIdx < ENET_EXAMPLE_SEND_COUNT)
        {
            /* Send a multicast frame when the PHY is link up. */
            PHY_GetLinkStatus(&phyHandle, &link);
            if (link)
            {
                /* Create the frame to be send. */
                buffer = (uint8_t *)malloc(ENET_EXAMPLE_FRAME_SIZE);
                if (buffer)
                {
                    memcpy(buffer, &g_frame[g_txIdx], ENET_EXAMPLE_FRAME_SIZE);
                    /* Make each transmit different.*/
                    g_txIdx = (g_txIdx + 1) % ENET_EXAMPLE_PACKAGETYPE;
                    /* Store the buffer for mem free.*/
                    g_txbuff[g_txbuffIdx] = buffer;
                    g_txbuffIdx           = (g_txbuffIdx + 1) % ENET_TXBD_NUM;

                    if (kStatus_Success ==
                        ENET_SendFrame(EXAMPLE_ENET_BASE, &g_handle, buffer, ENET_EXAMPLE_FRAME_SIZE))
                    {
                        g_testIdx++;
                        PRINTF("The %d frame transmitted success!\r\n", g_testIdx);
                        memset((void *)&ptpData, 0, sizeof(enet_ptp_time_data_t));
                        ptpData.messageType = ENET_PTP_SYNC_MSG;
                        if (ENET_GetTxFrameTime(&g_handle, &ptpData) == kStatus_Success)
                        {
                            PRINTF(" the timestamp is %d second,", (uint32_t)ptpData.timeStamp.second);
                            PRINTF(" %d nanosecond  \r\n", ptpData.timeStamp.nanosecond);
                        }
                    }
                }
                else
                {
                    PRINTF("No avail tx buffers\r\n");
                }
            }
            else
            {
                PRINTF(" \r\nThe PHY link down!\r\n");
            }
        }
    }
}
