/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_cache.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MEM_DMATRANSFER_LEN         10U * FSL_FEATURE_L1DCACHE_LINESIZE_BYTE
#define DMA0_DMA16_DriverIRQHandler DMA_CH_0_16_DriverIRQHandler

/* DMA Timtout. */
#define DMA_TRANSFER_TIMEOUT 0xFFFFU

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void APP_CacheConfig(bool enable);
uint32_t APP_MemoryInit(void);
void APP_DMAInit(void *userData);
void APP_DMAMem2memTransfer(uint8_t *srcAddr, uint32_t srcWidth, uint8_t *dstAddr, uint32_t dstWidth, uint32_t size);

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint32_t g_count = 0;
extern volatile bool g_Transfer_Done;
AT_NONCACHEABLE_SECTION(uint8_t g_data[MEM_DMATRANSFER_LEN]);
/*******************************************************************************
 * Code
 ******************************************************************************/
/* DATA write test length. */
edma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done = false;

void APP_CacheConfig(bool enable)
{
    if (enable)
    {
        /* Enable the l1 data cache. */
        L1CACHE_EnableDCache();
    }
    else
    {
        L1CACHE_DisableDCache();
    }
}


uint32_t APP_MemoryInit(void)
{
    return 0x20200000;
}

void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }
}

void APP_DMAInit(void *userData)
{
    edma_config_t config;

    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX);
    DMAMUX_EnableAlwaysOn(DMAMUX, 0, true);
    DMAMUX_EnableChannel(DMAMUX, 0);
    /* Configure DMA one shot transfer */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(DMA0, &config);
    EDMA_CreateHandle(&g_DMA_Handle, DMA0, 0);
    EDMA_SetCallback(&g_DMA_Handle, EDMA_Callback, userData);
}

void APP_DMAMem2memTransfer(uint8_t *srcAddr, uint32_t srcWidth, uint8_t *dstAddr, uint32_t dstWidth, uint32_t size)
{
    edma_transfer_config_t transferConfig;

    EDMA_PrepareTransfer(&transferConfig, srcAddr, srcWidth, dstAddr, dstWidth, srcWidth, size, kEDMA_MemoryToMemory);
    EDMA_SubmitTransfer(&g_DMA_Handle, &transferConfig);
    EDMA_StartTransfer(&g_DMA_Handle);
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t count;
    uint32_t startAddr;
    bool transferDone     = false;
    bool invalidateResult = false;
    bool pushResult       = false;
    volatile uint32_t readDummy;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n Cache example start.\r\n");

    /* Application memory region related initialization. */
    startAddr = APP_MemoryInit();
    /* Data initialize. */
    for (count = 0; count < MEM_DMATRANSFER_LEN; count++)
    {
        g_data[count]                   = 0xaa;
        *(uint8_t *)(startAddr + count) = 0;
    }
    /* Configure Cache. */
    APP_CacheConfig(true);
    /* Initialize DMA. */
    APP_DMAInit(&transferDone);

    for (count = 0; count < MEM_DMATRANSFER_LEN; count++)
    {
        /* Access the memory first. */
        readDummy = *(uint8_t *)(startAddr + count);
        (void)readDummy;
    }

    /* Update the new data in sdram with EDMA transfer. */
    APP_DMAMem2memTransfer(&g_data[0], sizeof(g_data[0]), (void *)startAddr, sizeof(g_data[0]), sizeof(g_data));

    /* Wait for EDMA transfer finished. */
    while ((g_Transfer_Done != true) && (g_count < DMA_TRANSFER_TIMEOUT))
    {
        g_count++;
    }

    if (g_count != DMA_TRANSFER_TIMEOUT)
    {
        /* Invalidate the cache to update the new data of the test memory
         * when we wants to get the real data in the test memory.
         * Note:
         L2CACHE_InvalidateByRange(startAddr, MEM_DMATRANSFER_LEN);
         L1CACHE_InvalidateDCacheByRange(startAddr, MEM_DMATRANSFER_LEN);
         *  can be replaced by using DCACHE_InvalidateByRange(startAddr, MEM_DMATRANSFER_LEN)
         */
#if (FSL_FEATURE_SOC_L2CACHEC_COUNT > 0)
#if defined(FSL_SDK_DISBLE_L2CACHE_PRESENT) && !FSL_SDK_DISBLE_L2CACHE_PRESENT
        L2CACHE_InvalidateByRange(startAddr, MEM_DMATRANSFER_LEN);
#endif /* !FSL_SDK_DISBLE_L2CACHE_PRESENT */
#endif /* FSL_FEATURE_SOC_L2CACHEC_COUNT > 0 */
        if (memcmp((void *)&g_data[0], (void *)startAddr, MEM_DMATRANSFER_LEN) != 0)
        {
            L1CACHE_InvalidateDCacheByRange(startAddr, MEM_DMATRANSFER_LEN);

            /* Now the data in cache is align with the real data in test memory. */
            if (memcmp((void *)&g_data[0], (void *)startAddr, MEM_DMATRANSFER_LEN) == 0)
            {
                invalidateResult = true;
            }
        }

        /* Verify data by CPU, but now the data in cache is not sync the real memory. */
        for (count = 0; count < MEM_DMATRANSFER_LEN; count++)
        {
            *(uint8_t *)(startAddr + count) = 0xffu;
        }

        /* Reset to zero. */
        g_Transfer_Done = false;
        g_count         = 0;
        /* Get the real data in the memory . */
        APP_DMAMem2memTransfer((void *)startAddr, sizeof(g_data[0]), &g_data[0], sizeof(g_data[0]), sizeof(g_data));

        /* Wait for EDMA transfer finished. */
        while ((g_Transfer_Done != true) && (g_count < DMA_TRANSFER_TIMEOUT))
        {
            g_count++;
        }

        if (g_count != DMA_TRANSFER_TIMEOUT)
        {
            if (memcmp((void *)&g_data[0], (void *)startAddr, MEM_DMATRANSFER_LEN) != 0)
            {
                /* Push the memory to update the data in physical sdram address
                 * at this moment, the real sdram data will be align with the
                 * data in cache. Note:
                 L1CACHE_CleanDCacheByRange(startAddr, MEM_DMATRANSFER_LEN);
                 L2CACHE_CleanByRange(startAddr, MEM_DMATRANSFER_LEN);
                 *  can be replaced by using DCACHE_CleanByRange(startAddr, MEM_DMATRANSFER_LEN)
                 */
                L1CACHE_CleanDCacheByRange(startAddr, MEM_DMATRANSFER_LEN);
#if (FSL_FEATURE_SOC_L2CACHEC_COUNT > 0)
#if defined(FSL_SDK_DISBLE_L2CACHE_PRESENT) && !FSL_SDK_DISBLE_L2CACHE_PRESENT
                L2CACHE_CleanByRange(startAddr, MEM_DMATRANSFER_LEN);
#endif /* !FSL_SDK_DISBLE_L2CACHE_PRESENT */
#endif /* FSL_FEATURE_SOC_L2CACHEC_COUNT > 0 */

                /* Transfer from the sdram to data[]. */
                g_Transfer_Done = false;
                g_count         = 0;
                APP_DMAMem2memTransfer((void *)startAddr, sizeof(g_data[0]), &g_data[0], sizeof(g_data[0]),
                                       sizeof(g_data));

                /* Wait for EDMA transfer finished. */
                while ((g_Transfer_Done != true) && (g_count < DMA_TRANSFER_TIMEOUT))
                {
                    g_count++;
                }

                if (g_count != DMA_TRANSFER_TIMEOUT)
                {
                    if (memcmp((void *)&g_data[0], (void *)startAddr, MEM_DMATRANSFER_LEN) == 0)
                    {
                        pushResult = true;
                    }
                }
            }
        }
    }

    /* Wait for last UART output finish. */
    count = DMA_TRANSFER_TIMEOUT;
    while (count--)
    {
        __NOP();
    }

    APP_CacheConfig(false);

    if (invalidateResult)
    {
        PRINTF("\r\n Cache Invalidate success! \r\n");
    }
    else
    {
        PRINTF("\r\n The memory cache invalidate failed!\r\n");
    }

    if (pushResult)
    {
        PRINTF("\r\n Cache Clean success! \r\n");
    }
    else
    {
        PRINTF("\r\n The memory cache clean failure!\r\n");
    }

    PRINTF(" \r\n Cache example end. \r\n");

    while (1)
    {
    }
}
