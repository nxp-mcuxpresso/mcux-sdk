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
#include "fsl_sai.h"
#include "fsl_debug_console.h"
#include "fsl_codec_common.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_wm8524.h"
#include "fsl_codec_adapter.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDM                      PDM
#define DEMO_PDM_CLK_FREQ             (24576000U)
#define DEMO_PDM_FIFO_WATERMARK       (4U)
#define DEMO_PDM_QUALITY_MODE         kPDM_QualityModeHigh
#define DEMO_PDM_CIC_OVERSAMPLE_RATE  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_LEFT  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_RIGHT (1U)
#define DEMO_PDM_SAMPLE_CLOCK_RATE    (1536000U * 4U) /* 6.144MHZ */
#define DEMO_PDM_HWVAD_SIGNAL_GAIN    0

#define DEMO_SAI                 (I2S3)
#define DEMO_SAI_CLK_FREQ        (24576000U)
#define DEMO_SAI_FIFO_WATER_MARK (FSL_FEATURE_SAI_FIFO_COUNT / 2U)
#define DEMO_SAI_CLOCK_SOURCE    (kSAI_BclkSourceMclkDiv)
#define DEMO_SAI_MASTER_SLAVE    kSAI_Master
#define DEMO_SAI_CHANNEL         0U

#define DEMO_CODEC_WM8524       1
#define DEMO_CODEC_BUS_PIN      (NULL)
#define DEMO_CODEC_BUS_PIN_NUM  (0)
#define DEMO_CODEC_MUTE_PIN     (GPIO5)
#define DEMO_CODEC_MUTE_PIN_NUM (21)

#define DEMO_AUDIO_SAMPLE_RATE  (kSAI_SampleRate48KHz)
#define DEMO_AUDIO_MASTER_CLOCK DEMO_SAI_CLK_FREQ
#define DEMO_AUDIO_DATA_CHANNEL (2U)
#define DEMO_AUDIO_BIT_WIDTH    kSAI_WordWidth16bits
#define BUFFER_SIZE   (1024U)
#define BUFFER_NUMBER (4U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_WM8524_Mute_GPIO(uint32_t output);
void BOARD_MasterClockConfig(void);
static void saiCallback(I2S_Type *base, sai_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static wm8524_config_t wm8524Config = {
    .setMute     = BOARD_WM8524_Mute_GPIO,
    .setProtocol = NULL,
    .protocol    = kWM8524_ProtocolI2S,
};
codec_config_t boardCodecConfig = {.codecDevType = kCODEC_WM8524, .codecDevConfig = &wm8524Config};
sai_master_clock_t mclkConfig;
static sai_handle_t s_saiTxHandle = {0};
static pdm_handle_t s_pdmHandle;
SDK_ALIGN(static uint8_t s_buffer[BUFFER_SIZE * BUFFER_NUMBER], 4);
static volatile uint32_t s_readIndex        = 0U;
static volatile uint32_t s_writeIndex       = 0U;
static volatile uint32_t s_bufferValidBlock = BUFFER_NUMBER;
static const pdm_config_t pdmConfig         = {
    .enableDoze        = false,
    .fifoWatermark     = DEMO_PDM_FIFO_WATERMARK,
    .qualityMode       = DEMO_PDM_QUALITY_MODE,
    .cicOverSampleRate = DEMO_PDM_CIC_OVERSAMPLE_RATE,
};
static pdm_channel_config_t channelConfig = {
    .cutOffFreq = kPDM_DcRemoverCutOff152Hz,
    .gain       = kPDM_DfOutputGain7,
};

codec_handle_t codecHandle;

extern codec_config_t boardCodecConfig;
/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_WM8524_Mute_GPIO(uint32_t output)
{
    GPIO_PinWrite(DEMO_CODEC_MUTE_PIN, DEMO_CODEC_MUTE_PIN_NUM, output);
}

void BOARD_MasterClockConfig(void)
{
    mclkConfig.mclkOutputEnable = true, mclkConfig.mclkHz = DEMO_AUDIO_MASTER_CLOCK;
    mclkConfig.mclkSourceClkHz = DEMO_SAI_CLK_FREQ;
    SAI_SetMasterClockConfig(DEMO_SAI, &mclkConfig);
}
static void saiCallback(I2S_Type *base, sai_handle_t *handle, status_t status, void *userData)
{
    if (kStatus_SAI_TxError == status)
    {
        /* Handle the error. */
    }
    else
    {
        s_bufferValidBlock++;
    }
}

static void pdmCallback(PDM_Type *base, pdm_handle_t *handle, status_t status, void *userData)
{
    if ((status == kStatus_PDM_FIFO_ERROR) || (status == kStatus_PDM_Output_ERROR) || (status == kStatus_PDM_CLK_LOW))
    {
        /* handle error */
    }
    else
    {
        if (s_bufferValidBlock)
        {
            s_bufferValidBlock--;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    sai_transfer_t saiXfer;
    pdm_transfer_t pdmXfer;
    sai_transceiver_t config;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    CLOCK_SetRootMux(kCLOCK_RootPdm, kCLOCK_PdmRootmuxAudioPll1); /* Set PDM source to AUDIO PLL1 393215996HZ */
    CLOCK_SetRootDivider(kCLOCK_RootPdm, 1U, 16U);                /* Set root clock to 393215996HZ / 16 = 24.575999M */

    CLOCK_SetRootMux(kCLOCK_RootSai3, kCLOCK_SaiRootmuxAudioPll1); /* Set SAI source to Audio PLL1 Div6 393215996HZ */
    CLOCK_SetRootDivider(kCLOCK_RootSai3, 1U, 16U);                /* Set root clock to 393215996HZ / 16 = 24.575999M */
    /* gpio initialization */
    gpio_pin_config_t gpioConfig = {kGPIO_DigitalOutput, 1};
    GPIO_PinInit(DEMO_CODEC_MUTE_PIN, DEMO_CODEC_MUTE_PIN_NUM, &gpioConfig);

    PRINTF("PDM SAI interrupt transfer example started!\n\r");

    memset(s_buffer, 0U, sizeof(s_buffer));

    /* SAI init */
    SAI_Init(DEMO_SAI);
    SAI_TransferTxCreateHandle(DEMO_SAI, &s_saiTxHandle, saiCallback, NULL);
    /* I2S mode configurations */
    SAI_GetClassicI2SConfig(&config, DEMO_AUDIO_BIT_WIDTH, kSAI_Stereo, 1U << DEMO_SAI_CHANNEL);

    config.bitClock.bclkSource = DEMO_SAI_CLOCK_SOURCE;
    config.masterSlave         = DEMO_SAI_MASTER_SLAVE;

    SAI_TransferTxSetConfig(DEMO_SAI, &s_saiTxHandle, &config);

    /* set bit clock divider */
    SAI_TxSetBitClockRate(DEMO_SAI, DEMO_AUDIO_MASTER_CLOCK, DEMO_AUDIO_SAMPLE_RATE, DEMO_AUDIO_BIT_WIDTH,
                          DEMO_AUDIO_DATA_CHANNEL);

    /* master clock configurations */
    BOARD_MasterClockConfig();

    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        assert(false);
    }

    /* Set up pdm */
    PDM_Init(DEMO_PDM, &pdmConfig);
    if (PDM_SetSampleRateConfig(DEMO_PDM, DEMO_PDM_CLK_FREQ, DEMO_AUDIO_SAMPLE_RATE) != kStatus_Success)
    {
        PRINTF("PDM configure sample rate failed.\r\n");
        return -1;
    }
    PDM_TransferCreateHandle(DEMO_PDM, &s_pdmHandle, pdmCallback, NULL);
    PDM_TransferSetChannelConfig(DEMO_PDM, &s_pdmHandle, DEMO_PDM_ENABLE_CHANNEL_LEFT, &channelConfig,
                                 FSL_FEATURE_PDM_FIFO_WIDTH);
    PDM_TransferSetChannelConfig(DEMO_PDM, &s_pdmHandle, DEMO_PDM_ENABLE_CHANNEL_RIGHT, &channelConfig,
                                 FSL_FEATURE_PDM_FIFO_WIDTH);
    PDM_Reset(DEMO_PDM);

    while (1)
    {
        if (s_bufferValidBlock > 0)
        {
            pdmXfer.data     = (uint8_t *)((uint32_t)s_buffer + s_readIndex * BUFFER_SIZE);
            pdmXfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == PDM_TransferReceiveNonBlocking(DEMO_PDM, &s_pdmHandle, &pdmXfer))
            {
                s_readIndex++;
            }
            if (s_readIndex == BUFFER_NUMBER)
            {
                s_readIndex = 0U;
            }
        }
        if (s_bufferValidBlock < BUFFER_NUMBER)
        {
            saiXfer.data     = (uint8_t *)((uint32_t)s_buffer + s_writeIndex * BUFFER_SIZE);
            saiXfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == SAI_TransferSendNonBlocking(DEMO_SAI, &s_saiTxHandle, &saiXfer))
            {
                s_writeIndex++;
            }
            if (s_writeIndex == BUFFER_NUMBER)
            {
                s_writeIndex = 0U;
            }
        }
    }
}
