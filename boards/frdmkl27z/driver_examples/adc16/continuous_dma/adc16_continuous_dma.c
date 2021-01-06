/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_adc16.h"
#include "fsl_dmamux.h"
#include "fsl_dma.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_CHANNEL       1U
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_BASEADDR      ADC0
#define DEMO_DMAMUX_BASEADDR     DMAMUX0
#define DEMO_DMA_CHANNEL         0U
#define DEMO_DMA_ADC_SOURCE      40U
#define DEMO_DMA_BASEADDR        DMA0
#define ADC16_RESULT_REG_ADDR    0x4003b010U
#define DEMO_DMA_IRQ_ID          DMA0_IRQn
#define DEMO_ADC16_SAMPLE_COUNT 16U /* The ADC16 sample count. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the DMA.
 */
static void DMA_Configuration(void);

/*!
 * @brief Initialize the DMAMUX.
 */
static void DMAMUX_Configuration(void);

/*!
 * @brief Initialize the ADC16.
 */
static void ADC16_Configuration(void);

/*!
 * @brief Process ADC values.
 */
static void ProcessSampleData(void);

/*!
 * @brief Callback function for DMA.
 */
static void DMA_Callback(struct _dma_handle *handle, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_Transfer_Done = false;                           /* DMA transfer completion flag. */
static uint32_t g_adc16SampleDataArray[DEMO_ADC16_SAMPLE_COUNT]; /* ADC value array. */
static uint32_t g_avgADCValue = 0U;                              /* Average ADC value. */
dma_handle_t g_DMA_Handle;                                       /* DMA handler. */
dma_transfer_config_t g_transferConfig;
const uint32_t g_Adc16_16bitFullRange = 65536U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    adc16_channel_config_t adcChnConfig;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("ADC16 CONTINUOUS DMA DEMO\r\n");

    DMA_Configuration();    /* Initialize DMA. */
    DMAMUX_Configuration(); /* Initialize DMAMUX. */
    ADC16_Configuration();  /* Initialize ADC16. */

    /* Configure channel and SW trigger ADC16. */
    adcChnConfig.channelNumber = DEMO_ADC16_CHANNEL;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcChnConfig.enableDifferentialConversion = false;
#endif
    adcChnConfig.enableInterruptOnConversionCompleted = false;
    ADC16_SetChannelConfig(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP, &adcChnConfig);

    PRINTF("ADC Full Range: %d\r\n", g_Adc16_16bitFullRange);
    PRINTF("Press any key to get user channel's ADC value ...\r\n");
    while (1)
    {
        GETCHAR();
        g_Transfer_Done = false;
        while (!g_Transfer_Done)
        {
        }
        ProcessSampleData();
        PRINTF("ADC value: %d\r\n", g_avgADCValue);
    }
}

static void DMAMUX_Configuration(void)
{
    /* Configure DMAMUX. */
    DMAMUX_Init(DEMO_DMAMUX_BASEADDR);
    DMAMUX_SetSource(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL, DEMO_DMA_ADC_SOURCE); /* Map ADC source to channel 0. */
    DMAMUX_EnableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);
}

static void DMA_Configuration(void)
{
    DMA_Init(DEMO_DMA_BASEADDR);
    DMA_CreateHandle(&g_DMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareTransfer(&g_transferConfig, (void *)ADC16_RESULT_REG_ADDR, sizeof(uint32_t),
                        (void *)g_adc16SampleDataArray, sizeof(uint32_t), sizeof(g_adc16SampleDataArray),
                        kDMA_PeripheralToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &g_transferConfig, kDMA_EnableInterrupt);
    /* Enable transfer. */
    DMA_StartTransfer(&g_DMA_Handle);
}

static void ADC16_Configuration(void)
{
    adc16_config_t adcUserConfig;

    /*
     * Initialization ADC for 16bit resolution, DMA mode, normal convert speed, VREFH/L as reference,
     * enable continuous convert mode.
     */
    ADC16_GetDefaultConfig(&adcUserConfig);
    adcUserConfig.resolution                 = kADC16_Resolution16Bit;
    adcUserConfig.enableContinuousConversion = true;
    adcUserConfig.clockSource                = kADC16_ClockSourceAlt1;

    adcUserConfig.longSampleMode = kADC16_LongSampleCycle24;
    adcUserConfig.enableLowPower = true;
#if ((defined BOARD_ADC_USE_ALT_VREF) && BOARD_ADC_USE_ALT_VREF)
    adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(DEMO_ADC16_BASEADDR, &adcUserConfig);

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    /* Auto calibration */
    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASEADDR))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif

    /* Enable software trigger.  */
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASEADDR, false);
    /* Enable DMA. */
    ADC16_EnableDMA(DEMO_ADC16_BASEADDR, true);
}

static void ProcessSampleData(void)
{
    uint32_t i = 0U;

    g_avgADCValue = 0;
    /* Get average adc value. */
    for (i = 0; i < DEMO_ADC16_SAMPLE_COUNT; i++)
    {
        g_avgADCValue += g_adc16SampleDataArray[i];
    }
    g_avgADCValue = g_avgADCValue / DEMO_ADC16_SAMPLE_COUNT;

    /* Reset old value. */
    for (i = 0; i < DEMO_ADC16_SAMPLE_COUNT; i++)
    {
        g_adc16SampleDataArray[i] = 0U;
    }
}

static void DMA_Callback(struct _dma_handle *handle, void *userData)
{
    /* Clear DMA interrupt flag. */
    DMA_ClearChannelStatusFlags(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, kDMA_TransactionsDoneFlag);
    /* Setup transfer. */
    DMA_Init(DEMO_DMA_BASEADDR);
    DMA_CreateHandle(&g_DMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareTransfer(&g_transferConfig, (void *)ADC16_RESULT_REG_ADDR, sizeof(uint32_t),
                        (void *)g_adc16SampleDataArray, sizeof(uint32_t), sizeof(g_adc16SampleDataArray),
                        kDMA_PeripheralToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &g_transferConfig, kDMA_EnableInterrupt);
    /* Enable transfer. */
    DMA_StartTransfer(&g_DMA_Handle);
    g_Transfer_Done = true;
}
