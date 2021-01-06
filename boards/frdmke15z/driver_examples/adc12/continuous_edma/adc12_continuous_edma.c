/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_adc12.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC12_BASEADDR      ADC0
#define DEMO_ADC12_CLOCK_NAME    kCLOCK_Adc0
#define DEMO_ADC12_CLOCK_SOURCE  kADC12_ClockSourceAlt0
#define DEMO_ADC12_USER_CHANNEL  0U
#define DEMO_ADC12_CHANNEL_GROUP 0U
#define DEMO_DMAMUX_BASEADDR     DMAMUX
#define DEMO_DMA_CHANNEL         0U
#define DEMO_DMA_ADC_SOURCE      40U
#define DEMO_DMA_BASEADDR        DMA0
#define ADC12_RESULT_REG_ADDR    0x4003b048U
#define DEMO_DMA_IRQ_ID          DMA0_IRQn
#define DEMO_ADC12_SAMPLE_COUNT 16U /* The ADC12 sample count. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the EDMA.
 */
static void EDMA_Configuration(void);

/*!
 * @brief Initialize the DMAMUX.
 */
static void DMAMUX_Configuration(void);

/*!
 * @brief Initialize the ADC12.
 */
static void ADC12_Configuration(void);

/*!
 * @brief Process ADC values.
 */
static void ProcessSampleData(void);

/*!
 * @brief Callback function for EDMA.
 */
static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_Transfer_Done = false;                           /* DMA transfer completion flag. */
static uint32_t g_adc12SampleDataArray[DEMO_ADC12_SAMPLE_COUNT]; /* ADC value array. */
static uint32_t g_avgADCValue = 0U;                              /* Average ADC value. */
edma_handle_t g_EDMA_Handle;                                     /* Edma handler. */
edma_transfer_config_t g_transferConfig;
const uint32_t g_Adc12_12bitFullRange = 4096U;
SDK_ALIGN(edma_tcd_t g_edmaTcd[2], 32U);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    adc12_channel_config_t adcChnConfig;

    /* Initialize board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Set ADC12's clock source to be Slow IRC async clock. */
    CLOCK_SetIpSrc(DEMO_ADC12_CLOCK_NAME, kCLOCK_IpSrcSircAsync);

    PRINTF("ADC12 CONTINUOUS EDMA DEMO\r\n");

    ADC12_Configuration();  /* Initialize ADC12. */
    EDMA_Configuration();   /* Initialize EDMA. */
    DMAMUX_Configuration(); /* Initialize DMAMUX. */

    /* Configure channel and SW trigger ADC12. */
    adcChnConfig.channelNumber                        = DEMO_ADC12_USER_CHANNEL;
    adcChnConfig.enableInterruptOnConversionCompleted = false;
    ADC12_SetChannelConfig(DEMO_ADC12_BASEADDR, DEMO_ADC12_CHANNEL_GROUP, &adcChnConfig);

    PRINTF("ADC Full Range: %d\r\n", g_Adc12_12bitFullRange);
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
    /* Configure DMAMUX */
    DMAMUX_Init(DEMO_DMAMUX_BASEADDR);
    DMAMUX_SetSource(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL, DEMO_DMA_ADC_SOURCE); /* Map ADC source to channel 0. */
    DMAMUX_EnableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);
}

static void EDMA_Configuration(void)
{
    edma_config_t userConfig;

    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DEMO_DMA_BASEADDR, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    EDMA_SetCallback(&g_EDMA_Handle, Edma_Callback, NULL);
    EDMA_PrepareTransfer(&g_transferConfig, (void *)ADC12_RESULT_REG_ADDR, sizeof(uint32_t),
                         (void *)g_adc12SampleDataArray, sizeof(uint32_t), sizeof(uint32_t),
                         sizeof(g_adc12SampleDataArray), kEDMA_PeripheralToMemory);
    /* Setup EDMA TCDs. */
    EDMA_TcdSetTransferConfig(&g_edmaTcd[0], &g_transferConfig, &g_edmaTcd[1]);
    EDMA_TcdSetTransferConfig(&g_edmaTcd[1], &g_transferConfig, &g_edmaTcd[0]);
    EDMA_InstallTCD(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, &g_edmaTcd[0]);
    EDMA_EnableChannelRequest(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    EDMA_TcdEnableInterrupts(&g_edmaTcd[0], kEDMA_MajorInterruptEnable);

#if defined(FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT) && FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT
    /* Enable async DMA request. */
    EDMA_EnableAsyncRequest(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, true);
#endif /* FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT. */
    /* Enable transfer. */
    EDMA_StartTransfer(&g_EDMA_Handle);
}

static void ADC12_Configuration(void)
{
    adc12_config_t adc12ConfigStruct;

    /* Initialize ADC. */
    ADC12_GetDefaultConfig(&adc12ConfigStruct);
    adc12ConfigStruct.enableContinuousConversion = true;
    adc12ConfigStruct.resolution                 = kADC12_Resolution12Bit;
    ADC12_Init(DEMO_ADC12_BASEADDR, &adc12ConfigStruct);

    /* Enable DMA. */
    ADC12_EnableDMA(DEMO_ADC12_BASEADDR, true);
    /* Set to software trigger mode. */
    ADC12_EnableHardwareTrigger(DEMO_ADC12_BASEADDR, false);

    /* Calibrate ADC. */
    if (kStatus_Success != ADC12_DoAutoCalibration(DEMO_ADC12_BASEADDR))
    {
        PRINTF("ADC calibration failed!\r\n");
    }
    else
    {
        PRINTF("ADC calibration is done!\r\n");
    }
}

static void ProcessSampleData(void)
{
    uint32_t i = 0U;

    g_avgADCValue = 0;
    /* Get average adc value. */
    for (i = 0; i < DEMO_ADC12_SAMPLE_COUNT; i++)
    {
        g_avgADCValue += g_adc12SampleDataArray[i];
    }
    g_avgADCValue = g_avgADCValue / DEMO_ADC12_SAMPLE_COUNT;

    /* Reset old value. */
    for (i = 0; i < DEMO_ADC12_SAMPLE_COUNT; i++)
    {
        g_adc12SampleDataArray[i] = 0U;
    }
}

static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    g_Transfer_Done = true;
}
