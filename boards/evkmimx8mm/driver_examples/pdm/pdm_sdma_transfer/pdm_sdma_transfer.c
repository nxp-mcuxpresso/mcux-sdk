/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pdm.h"
#include "fsl_debug_console.h"
#include "fsl_pdm_sdma.h"
#include "fsl_sdma.h"
#include "fsl_sdma_script.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDM PDM
#define DEMO_PDM_CLK_FREQ \
    (24000000U) / (CLOCK_GetRootPreDivider(kCLOCK_RootPdm)) / (CLOCK_GetRootPostDivider(kCLOCK_RootPdm))
#define DEMO_PDM_FIFO_WATERMARK       (4U)
#define DEMO_PDM_QUALITY_MODE         kPDM_QualityModeHigh
#define DEMO_PDM_CIC_OVERSAMPLE_RATE  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_LEFT  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_RIGHT (1U)
#define DEMO_PDM_SAMPLE_CLOCK_RATE    (640000U) /* 640KHZ */
#define DEMO_PDM_DMA_REQUEST_SOURCE   (24U)
#define DEMO_PDM_HWVAD_SIGNAL_GAIN    0

#define DEMO_DMA         SDMAARM2
#define DEMO_DMA_CHANNEL (1U)
#define BUFFER_SIZE (256)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void pdmSdmallback(PDM_Type *base, pdm_sdma_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(pdm_sdma_handle_t pdmRxHandle, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_handle_t dmaHandle, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t sdma_context, 4);
AT_NONCACHEABLE_SECTION_ALIGN(static int16_t rxBuff[BUFFER_SIZE], 4);

static volatile bool s_lowFreqFlag   = false;
static volatile bool s_fifoErrorFlag = false;
static volatile bool s_pdmRxFinished = false;

static const pdm_config_t pdmConfig = {
    .enableDoze        = false,
    .fifoWatermark     = DEMO_PDM_FIFO_WATERMARK,
    .qualityMode       = DEMO_PDM_QUALITY_MODE,
    .cicOverSampleRate = DEMO_PDM_CIC_OVERSAMPLE_RATE,
};
static const pdm_channel_config_t channelConfig = {
    .cutOffFreq = kPDM_DcRemoverCutOff152Hz,
    .gain       = kPDM_DfOutputGain4,
};
const short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void pdmSdmallback(PDM_Type *base, pdm_sdma_handle_t *handle, status_t status, void *userData)
{
    s_pdmRxFinished = true;
}

void PDM_ERROR_IRQHandler(void)
{
    uint32_t status = 0U;
    if (PDM_GetStatus(DEMO_PDM) & PDM_STAT_LOWFREQF_MASK)
    {
        PDM_ClearStatus(DEMO_PDM, PDM_STAT_LOWFREQF_MASK);
        s_lowFreqFlag = true;
    }

    status = PDM_GetFifoStatus(DEMO_PDM);
    if (status)
    {
        PDM_ClearFIFOStatus(DEMO_PDM, status);
        s_fifoErrorFlag = true;
    }

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
    status = PDM_GetRangeStatus(DEMO_PDM);
    if (status != 0U)
    {
        PDM_ClearRangeStatus(DEMO_PDM, status);
    }
#else
    status = PDM_GetOutputStatus(DEMO_PDM);
    if (status != 0U)
    {
        PDM_ClearOutputStatus(DEMO_PDM, status);
    }
#endif

    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0U, j = 0U;
    pdm_transfer_t xfer;
    sdma_config_t dmaConfig = {0};

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    CLOCK_SetRootMux(kCLOCK_RootPdm, kCLOCK_PdmRootmuxOsc24M); /* Set PDM source from OSC 25MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootPdm, 1U, 1U);              /* Set root clock to 25MHZ */

    PRINTF("PDM sdma example started!\n\r");

    memset(rxBuff, 0, sizeof(rxBuff));

    /* Create SDMA handle */
    SDMA_GetDefaultConfig(&dmaConfig);
    dmaConfig.ratio = kSDMA_ARMClockFreq;
    SDMA_Init(DEMO_DMA, &dmaConfig);
    SDMA_CreateHandle(&dmaHandle, DEMO_DMA, DEMO_DMA_CHANNEL, &sdma_context);
    SDMA_SetChannelPriority(DEMO_DMA, DEMO_DMA_CHANNEL, 2);
    SDMA_LoadScript(DEMO_DMA, FSL_SDMA_SCRIPT_CODE_START_ADDR, (void *)g_sdma_multi_fifo_script,
                    FSL_SDMA_SCRIPT_CODE_SIZE);
    /* Set up pdm */
    PDM_Init(DEMO_PDM, &pdmConfig);
    PDM_TransferCreateHandleSDMA(DEMO_PDM, &pdmRxHandle, pdmSdmallback, NULL, &dmaHandle, DEMO_PDM_DMA_REQUEST_SOURCE);
    PDM_SetChannelConfigSDMA(DEMO_PDM, &pdmRxHandle, DEMO_PDM_ENABLE_CHANNEL_LEFT, &channelConfig);
    PDM_SetChannelConfigSDMA(DEMO_PDM, &pdmRxHandle, DEMO_PDM_ENABLE_CHANNEL_RIGHT, &channelConfig);
    PDM_SetSampleRate(DEMO_PDM, (1U << DEMO_PDM_ENABLE_CHANNEL_LEFT) | (1U << DEMO_PDM_ENABLE_CHANNEL_RIGHT),
                      pdmConfig.qualityMode, pdmConfig.cicOverSampleRate,
                      DEMO_PDM_CLK_FREQ / DEMO_PDM_SAMPLE_CLOCK_RATE);
    PDM_Reset(DEMO_PDM);
    PDM_EnableInterrupts(DEMO_PDM, kPDM_ErrorInterruptEnable);
    EnableIRQ(PDM_ERROR_IRQn);

    xfer.data     = (uint8_t *)rxBuff;
    xfer.dataSize = BUFFER_SIZE * 2U;

    PDM_TransferReceiveSDMA(DEMO_PDM, &pdmRxHandle, &xfer);
    /* wait data read finish */
    while (!s_pdmRxFinished)
    {
    }

    PRINTF("PDM recieve two channel data:\n\r");
    for (i = 0U; i < BUFFER_SIZE; i++)
    {
        PRINTF("%6x ", rxBuff[i]);
        if (++j > 32U)
        {
            j = 0U;
            PRINTF("\r\n");
        }
    }

    PDM_Deinit(DEMO_PDM);

    PRINTF("\r\nPDM sdma example finished!\n\r ");
    while (1)
    {
    }
}
