/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_sai.h"
#include "music.h"
#include "fsl_codec_common.h"

#include "fsl_wm8960.h"
#include "main/imx8qm_pads.h"
#include "svc/pad/pad_api.h"
#include "fsl_gpio.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SAI and I2C instance and clock */
#define DEMO_CODEC_WM8960
#define DEMO_SAI          AUDIO__SAI1
#define DEMO_SAI_CHANNEL  (0)
#define DEMO_I2C          DMA__LPI2C1
#define DEMO_SAI_CLK_FREQ 24576000 /* Use Audio PLL 0 DIV clock */
#define CODEC_CYCLE       (30000000U)

#define DEMO_AUDIO_DATA_CHANNEL (2U)
#define DEMO_AUDIO_BIT_WIDTH    kSAI_WordWidth16bits
#define DEMO_AUDIO_SAMPLE_RATE  kSAI_SampleRate16KHz
#define DEMO_AUDIO_MASTER_CLOCK DEMO_SAI_CLK_FREQ

#define DEMO_SAI_TX_SYNC_MODE kSAI_ModeAsync
#define DEMO_SAI_RX_SYNC_MODE kSAI_ModeSync
#define DEMO_SAI_MASTER_SLAVE kSAI_Master

#define I2C_RELEASE_SDA_GPIO  LSIO__GPIO0
#define I2C_RELEASE_SDA_PIN   14U
#define I2C_RELEASE_SCL_GPIO  LSIO__GPIO0
#define I2C_RELEASE_SCL_PIN   15U
#define I2C_RELEASE_BUS_COUNT 100U

#define BOARD_MASTER_CLOCK_CONFIG()
#define BOARD_SAI_RXCONFIG(config, mode)
#ifndef DEMO_CODEC_INIT_DELAY_MS
#define DEMO_CODEC_INIT_DELAY_MS (1000U)
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);
extern void BOARD_SAI_RXConfig(sai_transceiver_t *config, sai_sync_mode_t sync);
/*******************************************************************************
 * Variables
 ******************************************************************************/
wm8960_config_t wm8960Config = {
    .i2cConfig        = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE, .codecI2CSourceClock = SC_24MHZ},
    .route            = kWM8960_RoutePlaybackandRecord,
    .rightInputSource = kWM8960_InputDifferentialMicInput2,
    .playSource       = kWM8960_PlaySourceDAC,
    .slaveAddress     = WM8960_I2C_ADDR,
    .bus              = kWM8960_BusI2S,
    .format           = {.mclk_HZ    = 24576000U,
               .sampleRate = kWM8960_AudioSampleRate16KHz,
               .bitWidth   = kWM8960_AudioBitWidth16bit},
    .master_slave     = false,
};
codec_config_t boardCodecConfig = {.codecDevType = kCODEC_WM8960, .codecDevConfig = &wm8960Config};
sai_handle_t txHandle           = {0};
static volatile bool isFinished = false;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    sc_ipc_t ipc;
    gpio_pin_config_t pin_config;

    pin_config.direction     = kGPIO_DigitalOutput;
    pin_config.outputLogic   = 1U;
    pin_config.interruptMode = kGPIO_NoIntmode;

    ipc = SystemGetScfwIpcHandle();

    /* Initialize GPT0_CLK/GPT0_CAPTURE as GPIO */
    if (sc_pad_set_mux(ipc, SC_P_GPT0_CLK, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to configure SC_P_GPT0_CLK mux\r\n");
    }
    if (sc_pad_set_mux(ipc, SC_P_GPT0_CAPTURE, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to configure SC_P_GPT0_CAPTURE mux\r\n");
    }

    /* Power on GPIO. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_GPIO_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on GPIO0\r\n");
    }

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA low */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}
static void callback(I2S_Type *base, sai_handle_t *handle, status_t status, void *userData)
{
    isFinished = true;
}

void DelayMS(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        SDK_DelayAtLeastUs(1000, SystemCoreClock);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    sai_transfer_t xfer;
    uint32_t temp = 0;
    sai_transceiver_t saiConfig;

    sc_ipc_t ipc;
    uint32_t freq;
    /* set mclk 24.576M */
    uint32_t misc_src_rate = 24576000U;
    /* set pll clock,to get accurate mclk freq,it is recommended to set this integer multiple of misc_src_rate,but
     * should in [650MHz-1300MHz] */
    uint32_t pll_src_rate = 1228800000U;

    ipc = BOARD_InitRpc();

    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins(ipc);

    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    /* Power on LPI2C. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_I2C_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on LPI2C\r\n");
    }
    /* Set LPI2C clock */
    freq = CLOCK_SetIpFreq(kCLOCK_DMA_Lpi2c1, SC_24MHZ);
    if (freq == 0)
    {
        PRINTF("Error: Failed to set LPI2C frequency\r\n");
    }

    /* Power on SAI. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_SAI_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SAI\r\n");
    }

    /* Power on AUDIO PLL0 clocks */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_AUDIO_PLL_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0\r\n");
    }
    /* Set SC_PM_CLK_PLL clock freq and enable */
    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_PLL, &pll_src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_PM_CLK_PLL clock rate\r\n");
    }
    if (sc_pm_clock_enable(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_PLL, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable SC_PM_CLK_PLL clock\r\n");
    }
    /* Set AUDIO PLL0 DIV clock freq and enable */
    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC0, &misc_src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set Audio PLL0 DIV clock rate\r\n");
    }
    if (sc_pm_clock_enable(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC0, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0 DIV clock\r\n");
    }
    /* Enable AUD_REC_CLK0 used for MCLKOUT0 */
    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC1, &misc_src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set Audio PLL0 REC clock rate\r\n");
    }
    if (sc_pm_clock_enable(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC1, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0 REC clock\r\n");
    }
    if (sc_pm_set_resource_power_mode(ipc, SC_R_MCLK_OUT_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on MCLKOUT0\r\n");
    }

    /* Enable interrupt in irqsteer */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTEER!\r\n");
    }
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, DMA_I2C1_INT_IRQn);
    IRQSTEER_EnableInterrupt(IRQSTEER, AUDIO_SAI1_INT_IRQn);

    PRINTF("SAI example started!\n\r");

    /* SAI init */
    SAI_Init(DEMO_SAI);
    SAI_TransferTxCreateHandle(DEMO_SAI, &txHandle, callback, NULL);
    /* I2S mode configurations */
    SAI_GetClassicI2SConfig(&saiConfig, DEMO_AUDIO_BIT_WIDTH, kSAI_Stereo, 1U << DEMO_SAI_CHANNEL);
    saiConfig.syncMode    = DEMO_SAI_TX_SYNC_MODE;
    saiConfig.masterSlave = DEMO_SAI_MASTER_SLAVE;
    SAI_TransferTxSetConfig(DEMO_SAI, &txHandle, &saiConfig);

    /* set bit clock divider */
    SAI_TxSetBitClockRate(DEMO_SAI, DEMO_AUDIO_MASTER_CLOCK, DEMO_AUDIO_SAMPLE_RATE, DEMO_AUDIO_BIT_WIDTH,
                          DEMO_AUDIO_DATA_CHANNEL);
    /* sai rx configurations */
    BOARD_SAI_RXCONFIG(&saiConfig, DEMO_SAI_RX_SYNC_MODE);
    /* master clock configurations */
    BOARD_MASTER_CLOCK_CONFIG();

    /* Use default setting to init codec */
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        assert(false);
    }
    /* delay for codec output stable */
    DelayMS(DEMO_CODEC_INIT_DELAY_MS);

    /*  xfer structure */
    temp          = (uint32_t)music;
    xfer.data     = (uint8_t *)temp;
    xfer.dataSize = MUSIC_LEN;
    SAI_TransferSendNonBlocking(DEMO_SAI, &txHandle, &xfer);
    /* Wait until finished */
    while (isFinished != true)
    {
    }

    PRINTF("\n\r SAI example finished!\n\r ");
    while (1)
    {
    }
}
