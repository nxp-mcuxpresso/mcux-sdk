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
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDM                      PDM
#define DEMO_PDM_CLK_FREQ             24576000U
#define DEMO_PDM_FIFO_WATERMARK       (7U)
#define DEMO_PDM_QUALITY_MODE         kPDM_QualityModeMedium
#define DEMO_PDM_CIC_OVERSAMPLE_RATE  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_LEFT  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_RIGHT (1U)
#define DEMO_PDM_SAMPLE_CLOCK_RATE    (1536000U * 2)
#define DEMO_PDM_HWVAD_SIGNAL_GAIN    0
#define DEMO_AUDIO_SAMPLE_RATE        (48000)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_hwvadFlag       = false;
static volatile uint32_t s_readIndex   = 0U;
static volatile uint32_t s_detectTimes = 50U;
static const pdm_config_t pdmConfig    = {
    .enableDoze        = false,
    .fifoWatermark     = DEMO_PDM_FIFO_WATERMARK,
    .qualityMode       = DEMO_PDM_QUALITY_MODE,
    .cicOverSampleRate = DEMO_PDM_CIC_OVERSAMPLE_RATE,
};

static const pdm_channel_config_t channelConfig = {
    .cutOffFreq = kPDM_DcRemoverCutOff83Hz,
    .gain       = kPDM_DfOutputGain7,
};

static const pdm_hwvad_config_t hwvadConfig = {
    .channel           = DEMO_PDM_ENABLE_CHANNEL_LEFT,
    .initializeTime    = 10U,
    .cicOverSampleRate = 0U,
    .inputGain         = 0U,
    .frameTime         = 10U,
    .cutOffFreq        = kPDM_HwvadHpfBypassed,
    .enableFrameEnergy = false,
    .enablePreFilter   = true,
};

static const pdm_hwvad_noise_filter_t noiseFilterConfig = {
    .enableAutoNoiseFilter = false,
    .enableNoiseMin        = true,
    .enableNoiseDecimation = true,
    .noiseFilterAdjustment = 0U,
    .noiseGain             = 7U,
    .enableNoiseDetectOR   = true,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
void PDM_HWVAD_EVENT_IRQHandler(void)
{
    if (PDM_GetHwvadInterruptStatusFlags(DEMO_PDM) & kPDM_HwvadStatusVoiceDetectFlag)
    {
        s_hwvadFlag = true;
        PDM_ClearHwvadInterruptStatusFlags(DEMO_PDM, kPDM_HwvadStatusVoiceDetectFlag);
    }
#if (defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    else
    {
        PDM_ClearHwvadInterruptStatusFlags(DEMO_PDM, kPDM_HwvadStatusInputSaturation);
    }
#endif
}

#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
void PDM_HWVAD_ERROR_IRQHandler(void)
{
    PDM_ClearHwvadInterruptStatusFlags(DEMO_PDM, kPDM_HwvadStatusInputSaturation);
}
#endif

/*!
 * @brief Main function
 */
int main(void)
{
    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    CLOCK_SetRootMux(kCLOCK_RootPdm, kCLOCK_PdmRootmuxAudioPll1); /* Set PDM source from OSC 25MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootPdm, 1U, 32U);                /* Set root clock to 25MHZ */

    PRINTF("PDM hwvad example started!\n\r");

    /* Set up pdm */
    PDM_Init(DEMO_PDM, &pdmConfig);
    PDM_SetChannelConfig(DEMO_PDM, DEMO_PDM_ENABLE_CHANNEL_LEFT, &channelConfig);
    PDM_SetChannelConfig(DEMO_PDM, DEMO_PDM_ENABLE_CHANNEL_RIGHT, &channelConfig);
    if (PDM_SetSampleRateConfig(DEMO_PDM, DEMO_PDM_CLK_FREQ, DEMO_AUDIO_SAMPLE_RATE) != kStatus_Success)
    {
        PRINTF("PDM configure sample rate failed.\r\n");
        return -1;
    }
    /* envelope based mode */
    PDM_SetHwvadInEnvelopeBasedMode(DEMO_PDM, &hwvadConfig, &noiseFilterConfig, NULL, DEMO_PDM_HWVAD_SIGNAL_GAIN);
    PDM_EnableHwvadInterrupts(DEMO_PDM, kPDM_HwvadErrorInterruptEnable | kPDM_HwvadInterruptEnable);
    NVIC_ClearPendingIRQ(PDM_HWVAD_EVENT_IRQn);
#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    NVIC_ClearPendingIRQ(PDM_HWVAD_ERROR_IRQn);
    EnableIRQ(PDM_HWVAD_ERROR_IRQn);
#endif
    EnableIRQ(PDM_HWVAD_EVENT_IRQn);

    while (s_detectTimes)
    {
        /* wait voice detect */
        while (!s_hwvadFlag)
        {
        }
        s_hwvadFlag = false;
        s_detectTimes--;
        PRINTF("\r\nVoice detected\r\n");
    }

    PDM_Deinit(DEMO_PDM);

    PRINTF("\n\rPDM hwvad example finished!\n\r ");
    while (1)
    {
    }
}
