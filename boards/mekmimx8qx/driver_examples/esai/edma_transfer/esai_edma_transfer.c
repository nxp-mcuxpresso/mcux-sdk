/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_esai_edma.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_codec_common.h"
#include "fsl_cs42888.h"
#include "fsl_lpuart.h"
#include "fsl_irqsteer.h"
#include "fsl_gpio.h"
#include "fsl_codec_adapter.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_ESAI           ADMA__ESAI0
#define ESAI_SOURCE_CLOCK_FREQ (49152000)
#define ESAI_MASTER_CLOCK_FREQ (12288000)
#define EXAMPLE_I2C            (CM4__LPI2C)                       /*Should change to MIPI_CSI_I2C0*/
#define I2C_SOURCE_CLOCK_FREQ  CLOCK_GetIpFreq(kCLOCK_M4_0_Lpi2c) /*MIPI_CSI*/
#define EXAMPLE_DMA            (ADMA__EDMA0)
#define EXAMPLE_TX_CHANNEL     (7)
#define EXAMPLE_RX_CHANNEL     (6)
#define CODEC_CS42888          (1)
#define ESAI_TX_CHANNEL        (2)

#define EXAMPLE_IOEXP_LPI2C_BAUDRATE               (400000)
#define EXAMPLE_IOEXP_LPI2C_MASTER_CLOCK_FREQUENCY SC_133MHZ
#define EXAMPLE_IOEXP_LPI2C_MASTER                 ADMA__LPI2C1
#define EXAMPLE_I2C_EXPANSION_B_ADDR               (0x1D)

/*! @brief PCA9557 Registers address definition. */
#define PCA9557_REG_INTPUT_PORT        (0x00)
#define PCA9557_REG_OUTPUT_PORT        (0x01)
#define PCA9557_REG_POLARITY_INVERSION (0x02)
#define PCA9557_REG_CONFIGURATION      (0x03)

#define EXAMPLE_I2C_SWITCH_ADDR (0x71)
#define OVER_SAMPLE_RATE (256U)
#define SAMPLE_RATE      (kESAI_SampleRate48KHz)
#define BUFFER_SIZE      (1024)
#define BUFFER_NUM       (4)
#define PLAY_COUNT       (5000)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_CodecReset(bool state);
static void txCallback(ESAI_Type *base, esai_edma_handle_t *handle, status_t status, void *userData);
static void rxCallback(ESAI_Type *base, esai_edma_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/

cs42888_config_t cs42888Config = {
    .DACMode      = kCS42888_ModeSlave,
    .ADCMode      = kCS42888_ModeSlave,
    .reset        = BOARD_CodecReset,
    .master       = false,
    .i2cConfig    = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE, .codecI2CSourceClock = SC_24MHZ},
    .format       = {.mclk_HZ = ESAI_MASTER_CLOCK_FREQ, .sampleRate = 48000U, .bitWidth = 16U},
    .bus          = kCS42888_BusI2S,
    .slaveAddress = CS42888_I2C_ADDR,
};

codec_config_t boardCodecConfig = {.codecDevType = kCODEC_CS42888, .codecDevConfig = &cs42888Config};
AT_NONCACHEABLE_SECTION_INIT(esai_edma_handle_t txHandle)                                 = {0};
AT_NONCACHEABLE_SECTION_INIT(esai_edma_handle_t rxHandle)                                 = {0};
AT_NONCACHEABLE_SECTION_INIT(edma_handle_t txDmaHandle)                                   = {0};
AT_NONCACHEABLE_SECTION_INIT(edma_handle_t rxDmaHandle)                                   = {0};
AT_NONCACHEABLE_SECTION_ALIGN_INIT(static uint8_t audioBuff[BUFFER_SIZE * BUFFER_NUM], 4) = {0};
volatile bool istxFinished                                                                = false;
volatile bool isrxFinished                                                                = false;
volatile uint32_t beginCount                                                              = 0;
volatile uint32_t sendCount                                                               = 0;
volatile uint32_t receiveCount                                                            = 0;
codec_handle_t codecHandle;
extern codec_config_t boardCodecConfig;
/*******************************************************************************
 * Code
 ******************************************************************************/
static sc_ipc_t ipc;

static bool PCA9557_WriteReg(
    LPI2C_Type *base, const uint8_t dev_addr, uint8_t reg_offset, uint8_t *txBuff, uint32_t txSize)
{
    status_t reVal = kStatus_Fail;

    if (kStatus_Success == LPI2C_MasterStart(base, dev_addr, kLPI2C_Write))
    {
        while (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
        }

        reVal = LPI2C_MasterSend(base, &reg_offset, 1);
        if (reVal != kStatus_Success)
        {
            return -1;
        }

        reVal = LPI2C_MasterSend(base, txBuff, txSize);
        if (reVal != kStatus_Success)
        {
            return -1;
        }

        reVal = LPI2C_MasterStop(base);
        if (reVal != kStatus_Success)
        {
            return -1;
        }
    }
    return kStatus_Success;
}

static bool PCA9646_WriteReg(LPI2C_Type *base, const uint8_t dev_addr, uint8_t *txBuff, uint32_t txSize)
{
    status_t reVal = kStatus_Fail;

    if (kStatus_Success == LPI2C_MasterStart(base, dev_addr, kLPI2C_Write))
    {
        while (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
        }

        reVal = LPI2C_MasterSend(base, txBuff, txSize);
        if (reVal != kStatus_Success)
        {
            return -1;
        }

        reVal = LPI2C_MasterStop(base);
        if (reVal != kStatus_Success)
        {
            return -1;
        }
    }
    return kStatus_Success;
}

void BOARD_CodecReset(bool state)
{
    lpi2c_master_config_t masterConfig;
    uint8_t txBuffer[4] = {0};

    /* lpi2c init */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = EXAMPLE_IOEXP_LPI2C_BAUDRATE;

    LPI2C_MasterInit(EXAMPLE_IOEXP_LPI2C_MASTER, &masterConfig, EXAMPLE_IOEXP_LPI2C_MASTER_CLOCK_FREQUENCY);
    /*Configure Expansion Pin*/

    if (state == true)
    {
        /* Output '1' to remove reset pin */
        txBuffer[0] = 0x2;
        PCA9557_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_EXPANSION_B_ADDR, PCA9557_REG_OUTPUT_PORT, txBuffer,
                         1);
    }
    else
    {
        /*
         * U191 Initialization
         *  U191 has I2C Address of 0x71, enable channel 3
         */
        txBuffer[0] = 0x8;
        PCA9646_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_SWITCH_ADDR, txBuffer, 1);

        /* Set BB_AUDIN_RST_B */
        txBuffer[0] = 0;
        PCA9557_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_EXPANSION_B_ADDR, PCA9557_REG_CONFIGURATION, txBuffer,
                         1);
    }

    LPI2C_MasterDeinit(EXAMPLE_IOEXP_LPI2C_MASTER);
}

static void txCallback(ESAI_Type *base, esai_edma_handle_t *handle, status_t status, void *userData)
{
    esai_transfer_t xfer = {0};

    sendCount++;

    if (sendCount == beginCount)
    {
        istxFinished = true;
        ESAI_TransferAbortSendEDMA(base, handle);
        sendCount = 0;
    }
    else
    {
        xfer.data     = audioBuff + ((sendCount - 1U) % BUFFER_NUM) * BUFFER_SIZE;
        xfer.dataSize = BUFFER_SIZE;
        ESAI_TransferSendEDMA(base, handle, &xfer);
    }
}

static void rxCallback(ESAI_Type *base, esai_edma_handle_t *handle, status_t status, void *userData)
{
    esai_transfer_t xfer = {0};

    receiveCount++;

    if (receiveCount == beginCount)
    {
        isrxFinished = true;
        ESAI_TransferAbortReceiveEDMA(base, handle);
        receiveCount = 0;
    }
    else
    {
        xfer.data     = audioBuff + ((receiveCount - 1U) % BUFFER_NUM) * BUFFER_SIZE;
        xfer.dataSize = BUFFER_SIZE;
        ESAI_TransferReceiveEDMA(base, handle, &xfer);
    }
}

int main(void)
{
    edma_config_t dmaConfig = {0};
    esai_config_t config;
    uint32_t hclkSourceClockHz = 0U;
    esai_transfer_t txfer;
    esai_transfer_t rxfer;
    esai_format_t format;

    uint32_t freq               = ESAI_SOURCE_CLOCK_FREQ;
    uint32_t mst_freq           = ESAI_MASTER_CLOCK_FREQ;
    sc_pm_clock_rate_t src_rate = SC_133MHZ;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_PowerOnBaseBoard();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power up the clock */
    sc_pm_set_resource_power_mode(ipc, SC_R_ESAI_0, SC_PM_PW_MODE_ON);

    /* open the lpi2c power and clock */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_I2C_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SC_R_I2C_1\r\n");
    }

    if (sc_pm_clock_enable(ipc, SC_R_I2C_1, SC_PM_CLK_PER, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable SC_R_I2C_1 clock \r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_I2C_1, SC_PM_CLK_PER, &src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_I2C_1 clock rate\r\n");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_M4_0_I2C, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on LPI2C\r\n");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_DMA_0_CH6, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on DMA0 Channel 6\r\n");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_DMA_0_CH7, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on DMA0 Channel 7\r\n");
    }

    if (CLOCK_SetIpFreq(kCLOCK_M4_0_Lpi2c, SC_24MHZ) == 0)
    {
        PRINTF("Error: Failed to set LPI2C frequency\r\n");
    }
    if (!CLOCK_EnableClockExt(kCLOCK_M4_0_Lpi2c, 0))
        PRINTF("Error: sc_pm_clock_enable failed\r\n");

    /* Power on ESAI and clocks */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_ESAI_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable ESAI0\r\n");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_AUDIO_PLL_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0\r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_PLL, &mst_freq) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_AUDIO_PLL_0 clock rate\r\n");
    }
    if (mst_freq == 0)
    {
        PRINTF("Error: Failed to set Audio PLL 0 master frequency\r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC0, &freq) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_AUDIO_PLL_0 clock rate\r\n");
    }
    if (freq == 0)
    {
        PRINTF("Error: Failed to set Audio PLL 0 frequency\r\n");
    }
    if (sc_pm_clock_enable(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC0, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0 DIV clock\r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC1, &freq) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_AUDIO_PLL_0 clock rate\r\n");
    }
    if (freq == 0)
    {
        PRINTF("Error: Failed to set Audio PLL 0 frequency\r\n");
    }
    if (sc_pm_clock_enable(ipc, SC_R_AUDIO_PLL_0, SC_PM_CLK_MISC1, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable Audio PLL0 REC clock\r\n");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }

    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_ESAI0_DMA_INT_IRQn);

    /*
     * pads configuration
     * QX B0 ESAI Pads are default at 2.5V, the following code configures them to 3.3V/1.8V
     */
    sc_pad_set(ipc, SC_P_COMP_CTL_GPIO_1V8_3V3_ENET_ENETB0, 0x400014a0);
    sc_pad_set(ipc, SC_P_COMP_CTL_GPIO_1V8_3V3_ENET_ENETB1, 0x400014a0);
    sc_pad_set(ipc, SC_P_COMP_CTL_GPIO_1V8_3V3_GPIORHB, 0x400514a0);

    PRINTF("\r\nESAI EDMA example started! \r\n");

    /* Init codec */
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        PRINTF("CODEC_Init failed!\r\n");
        return -1;
    }

    /* Initialize EDMA */
    EDMA_GetDefaultConfig(&dmaConfig);
    EDMA_Init(EXAMPLE_DMA, &dmaConfig);

    /* Create handle for dma channels */
    EDMA_CreateHandle(&txDmaHandle, EXAMPLE_DMA, EXAMPLE_TX_CHANNEL);
    EDMA_CreateHandle(&rxDmaHandle, EXAMPLE_DMA, EXAMPLE_RX_CHANNEL);

    ESAI_GetDefaultConfig(&config);
#if defined(CODEC_CS42888)
    config.syncMode = kESAI_ModeAsync;
#endif
    ESAI_Init(EXAMPLE_ESAI, &config);

    /* Configure the audio format */
    format.slotType      = kESAI_SlotLen32WordLen16;
    format.sampleRate_Hz = SAMPLE_RATE;
    format.sectionMap    = 0x1;

    ESAI_TransferTxCreateHandleEDMA(EXAMPLE_ESAI, &txHandle, txCallback, NULL, &txDmaHandle);
    ESAI_TransferRxCreateHandleEDMA(EXAMPLE_ESAI, &rxHandle, rxCallback, NULL, &rxDmaHandle);

    hclkSourceClockHz = ESAI_SOURCE_CLOCK_FREQ;
#if defined ESAI_TX_CHANNEL
    format.sectionMap = (1U << ESAI_TX_CHANNEL);
#endif
    ESAI_TransferTxSetFormatEDMA(EXAMPLE_ESAI, &txHandle, &format, format.sampleRate_Hz * 256U, hclkSourceClockHz);
#if defined ESAI_RX_CHANNEL
    format.sectionMap = (1U << ESAI_RX_CHANNEL);
#else
    format.sectionMap = 1U;
#endif
    ESAI_TransferRxSetFormatEDMA(EXAMPLE_ESAI, &rxHandle, &format, format.sampleRate_Hz * 256U, hclkSourceClockHz);

    /*  xfer structure */
    rxfer.data     = audioBuff;
    rxfer.dataSize = BUFFER_SIZE;
    txfer.data     = audioBuff;
    txfer.dataSize = BUFFER_SIZE;

    /* Set the time to record and playback */
    beginCount = PLAY_COUNT;

    ESAI_TransferSendEDMA(EXAMPLE_ESAI, &txHandle, &txfer);
    ESAI_TransferReceiveEDMA(EXAMPLE_ESAI, &rxHandle, &rxfer);

    /* Waiting for transfer finished */
    while ((isrxFinished == false) || (istxFinished == false))
    {
    }

    ESAI_TransferAbortReceiveEDMA(EXAMPLE_ESAI, &rxHandle);
    ESAI_TransferAbortSendEDMA(EXAMPLE_ESAI, &txHandle);

    PRINTF("\r\nESAI EDMA example succeed! \r\n");

    while (1)
    {
    }
}
