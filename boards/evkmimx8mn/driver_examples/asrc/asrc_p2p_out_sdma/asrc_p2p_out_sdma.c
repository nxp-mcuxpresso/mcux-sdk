/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_sai_sdma.h"
#include "music.h"
#include "fsl_codec_common.h"
#include "fsl_asrc_sdma.h"
#include "fsl_asrc.h"
#include "fsl_sdma_script.h"
#include "fsl_wm8524.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_codec_adapter.h"
#include "fsl_sai.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_SAI  (I2S3)
#define DEMO_ASRC ASRC
#define DEMO_SAI_CLK_FREQ                                                                  \
    (CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootSai3)) / \
     (CLOCK_GetRootPostDivider(kCLOCK_RootSai3)))
#define DEMO_CODEC_WM8524          (1)
#define DEMO_CODEC_BUS_PIN         (NULL)
#define DEMO_CODEC_BUS_PIN_NUM     (0)
#define DEMO_CODEC_MUTE_PIN        (GPIO5)
#define DEMO_CODEC_MUTE_PIN_NUM    (21)
#define DEMO_IRQn                  I2S3_IRQn
#define DEMO_DMA                   SDMAARM2
#define DEMO_ASRC_IN_SDMA_CHANNEL  2
#define DEMO_ASRC_OUT_SDMA_CHANNEL 3
#define DEMO_ASRC_IN_SDMA_SOURCE   16
#define DEMO_ASRC_OUT_SDMA_SOURCE  17
#define DEMO_ASRC_CONTEXT          kASRC_Context0
#define DEMO_SAI_TX_SOURCE         (5)
/*set Bclk source to Mclk clock*/
#define DEMO_SAI_CLOCK_SOURCE   (1U)
#define DEMO_SAI_CHANNEL_NUM    0
#define DEMO_AUDIO_BIT_WIDTH    kSAI_WordWidth16bits
#define DEMO_AUDIO_DATA_CHANNEL (2U)
#define DEMO_AUDIO_MASTER_CLOCK DEMO_SAI_CLK_FREQ

#define SDMA_FREQ_EQUALS_ARM      (1U)
#define DEMO_ASRC_IN_SAMPLE_RATE  44100
#define DEMO_ASRC_OUT_SAMPLE_RATE 16000
/* convert buffer size, please note that the maximum size  of once transfer that SDMA can support is 64k */
#define DEMO_AUDIO_BUFFER_SIZE (16000U)
#define DEMO_AUDIO_SAMPLES     (MUSIC_LEN / 2U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_WM8524_Mute_GPIO(uint32_t output);
void BOARD_MASTER_CLOCK_CONFIG(void);

static void asrcConvertAudio(void *in, uint32_t dataSize);
static void startSai(bool start);
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

volatile bool isConvertFinished = false;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;
/*! @brief ASRC sdma handle */
AT_NONCACHEABLE_SECTION_ALIGN(static asrc_sdma_handle_t s_asrcHandle, 4U);
AT_NONCACHEABLE_SECTION_ALIGN(static sdma_handle_t s_asrcInSDMAHandle, 4U);
AT_NONCACHEABLE_SECTION_ALIGN(static sdma_handle_t s_asrcOutSDMAHandle, 4U);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t s_asrcInSDMAcontext, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t s_asrcOutSDMAcontext, 4);

/*! @brief ASRC context config */
static asrc_context_config_t s_asrcContextConfig;
static const asrc_p2p_sdma_config_t s_asrcSDMAConfig = {
    .eventSource      = DEMO_SAI_TX_SOURCE,
    .watermark        = FSL_FEATURE_SAI_FIFO_COUNT / 2U,
    .channel          = 0U,
    .enableContinuous = true,
    .startPeripheral  = startSai,
};
const short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;
/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_WM8524_Mute_GPIO(uint32_t output)
{
    GPIO_PinWrite(DEMO_CODEC_MUTE_PIN, DEMO_CODEC_MUTE_PIN_NUM, output);
}

void BOARD_MASTER_CLOCK_CONFIG(void)
{
    mclkConfig.mclkOutputEnable = true, mclkConfig.mclkHz = DEMO_AUDIO_MASTER_CLOCK;
    mclkConfig.mclkSourceClkHz = DEMO_SAI_CLK_FREQ;
    SAI_SetMasterClockConfig(DEMO_SAI, &mclkConfig);
}

static void asrcInCallback(ASRC_Type *base, asrc_sdma_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_ASRCQueueIdle)
    {
        isConvertFinished = true;
    }
}

static void startSai(bool start)
{
    if (start)
    {
        SAI_TxEnable(DEMO_SAI, true);
    }
    else
    {
        SAI_TxEnable(DEMO_SAI, false);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t *temp           = (uint8_t *)music;
    sdma_config_t dmaConfig = {0};
    sai_transceiver_t config;

    /* M7 has its local cache and enabled by default,
     * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
     * non-cacheable before accessing this address region */
    BOARD_InitMemory();

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_SetRootMux(kCLOCK_RootSai3, kCLOCK_SaiRootmuxAudioPll1); /* Set SAI source to AUDIO PLL1 393215996HZ*/
    CLOCK_SetRootDivider(kCLOCK_RootSai3, 1U, 16U);                /* Set root clock to 393215996HZ / 16 = 24.575999M */
    /* gpio initialization */
    gpio_pin_config_t gpioConfig = {kGPIO_DigitalOutput, 1};
    GPIO_PinInit(DEMO_CODEC_MUTE_PIN, DEMO_CODEC_MUTE_PIN_NUM, &gpioConfig);

    PRINTF("ASRC peripheral to peripheral SDMA example.\n\r");

    /* Create SDMA handle */
    SDMA_GetDefaultConfig(&dmaConfig);
#ifdef SDMA_FREQ_EQUALS_ARM
    dmaConfig.ratio = kSDMA_ARMClockFreq;
#endif

    SDMA_Init(DEMO_DMA, &dmaConfig);

    SDMA_LoadScript(DEMO_DMA, FSL_SDMA_SCRIPT_CODE_START_ADDR, (void *)g_sdma_multi_fifo_script,
                    FSL_SDMA_SCRIPT_CODE_SIZE);

    /* SAI init */
    SAI_Init(DEMO_SAI);
    /* I2S mode configurations */
    SAI_GetClassicI2SConfig(&config, DEMO_AUDIO_BIT_WIDTH, kSAI_Stereo, kSAI_Channel0Mask);
    config.bitClock.bclkSource = (sai_bclk_source_t)DEMO_SAI_CLOCK_SOURCE;
    SAI_TxSetConfig(DEMO_SAI, &config);

    /* set bit clock divider */
    SAI_TxSetBitClockRate(DEMO_SAI, DEMO_AUDIO_MASTER_CLOCK, DEMO_ASRC_OUT_SAMPLE_RATE, DEMO_AUDIO_BIT_WIDTH,
                          DEMO_AUDIO_DATA_CHANNEL);

    /* master clock configurations */
    BOARD_MASTER_CLOCK_CONFIG();

    /* Enable DMA enable bit */
    SAI_TxEnableDMA(DEMO_SAI, kSAI_FIFORequestDMAEnable, true);

    /* create ASRC sdma handle */
    SDMA_CreateHandle(&s_asrcInSDMAHandle, DEMO_DMA, DEMO_ASRC_IN_SDMA_CHANNEL, &s_asrcInSDMAcontext);
    SDMA_SetChannelPriority(DEMO_DMA, DEMO_ASRC_IN_SDMA_CHANNEL, 4);
    SDMA_CreateHandle(&s_asrcOutSDMAHandle, DEMO_DMA, DEMO_ASRC_OUT_SDMA_CHANNEL, &s_asrcOutSDMAcontext);
    SDMA_SetChannelPriority(DEMO_DMA, DEMO_ASRC_OUT_SDMA_CHANNEL, 3);

    ASRC_Init(DEMO_ASRC);
    ASRC_GetContextDefaultConfig(&s_asrcContextConfig, DEMO_AUDIO_DATA_CHANNEL, DEMO_ASRC_IN_SAMPLE_RATE,
                                 DEMO_ASRC_OUT_SAMPLE_RATE);
    ASRC_TransferInCreateHandleSDMA(DEMO_ASRC, &s_asrcHandle, asrcInCallback, &s_asrcInSDMAHandle,
                                    DEMO_ASRC_IN_SDMA_SOURCE, DEMO_ASRC_CONTEXT, NULL, NULL);
    ASRC_TransferOutCreateHandleSDMA(DEMO_ASRC, &s_asrcHandle, NULL, &s_asrcOutSDMAHandle, DEMO_ASRC_OUT_SDMA_SOURCE,
                                     DEMO_ASRC_CONTEXT, &s_asrcSDMAConfig, NULL);
    if (ASRC_TransferSetContextConfigSDMA(DEMO_ASRC, &s_asrcHandle, &s_asrcContextConfig) != kStatus_Success)
    {
        PRINTF("ASRC context configure failed, please check.\r\n");
        return -1;
    }

    /* Use default setting to init codec */
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        assert(false);
    }

    PRINTF("Playback converted 16K audio data.\n\r");

    asrcConvertAudio(temp, MUSIC_LEN);

    PRINTF("ASRC peripheral to peripheral SDMA example finished.\n\r ");

    ASRC_Deinit(DEMO_ASRC);

    while (1)
    {
    }
}

static void asrcConvertAudio(void *in, uint32_t dataSize)
{
    asrc_transfer_t xfer;

    xfer.inDataAddr  = in;
    xfer.inDataSize  = dataSize;
    xfer.outDataAddr = (uint32_t *)SAI_TxGetDataRegisterAddress(DEMO_SAI, DEMO_SAI_CHANNEL_NUM);
    xfer.outDataSize =
        ASRC_GetContextOutSampleSize(DEMO_ASRC_IN_SAMPLE_RATE, dataSize, 2U, DEMO_ASRC_OUT_SAMPLE_RATE, 2U);
    ASRC_TransferSDMA(DEMO_ASRC, &s_asrcHandle, &xfer);

    /* Wait until finished */
    while (!isConvertFinished)
    {
    }
}

void SAI_UserIRQHandler(void)
{
    SAI_TxClearStatusFlags(DEMO_SAI, kSAI_FIFOErrorFlag);
    __DSB();
}
