/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sdmmc_config.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_SDCardPowerControl(bool enable);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
#if defined(SDIO_ENABLED) || defined(SD_ENABLED)
static sd_detect_card_t s_cd;
static sd_io_voltage_t s_ioVoltage = {
    .type = BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE,
    .func = NULL,
};
#endif
static sdmmchost_t s_host;

#ifdef SDIO_ENABLED
static sdio_card_int_t s_sdioInt;
#endif

GPIO_HANDLE_DEFINE(s_CardDetectGpioHandle);
GPIO_HANDLE_DEFINE(s_PowerResetGpioHandle);

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t BOARD_USDHC1ClockConfiguration(void)
{
    /* attach FRO HF to USDHC */
    CLOCK_SetClkDiv(kCLOCK_DivUSdhcClk, 1u);
    CLOCK_AttachClk(kFRO_HF_to_USDHC);

    return CLOCK_GetUsdhcClkFreq();
}

#if defined(SDIO_ENABLED) || defined(SD_ENABLED)
bool BOARD_SDCardGetDetectStatus(void)
{
    uint8_t pinState;

    if (HAL_GpioGetInput(s_CardDetectGpioHandle, &pinState) == kStatus_HAL_GpioSuccess)
    {
        if (pinState == BOARD_SDMMC_SD_CD_INSERT_LEVEL)
        {
            return true;
        }
    }

    return false;
}

void SDMMC_SD_CD_Callback(void *param)
{
    if (s_cd.callback != NULL)
    {
        s_cd.callback(BOARD_SDCardGetDetectStatus(), s_cd.userData);
    }
}

void BOARD_SDCardDAT3PullFunction(uint32_t status)
{
    if (status == kSD_DAT3PullDown)
    {
        const port_pin_config_t port2_6_pinK2_config = {/* Internal pull-up/down resistor is disabled */
                                                        kPORT_PullDisable,
                                                        /* Low internal pull resistor value is selected. */
                                                        kPORT_LowPullResistor,
                                                        /* Fast slew rate is configured */
                                                        kPORT_FastSlewRate,
                                                        /* Passive input filter is disabled */
                                                        kPORT_PassiveFilterDisable,
                                                        /* Open drain output is disabled */
                                                        kPORT_OpenDrainDisable,
                                                        /* Low drive strength is configured */
                                                        kPORT_LowDriveStrength,
                                                        /* Pin is configured as SDHC0_D3 */
                                                        kPORT_MuxAlt3,
                                                        /* Digital input enabled */
                                                        kPORT_InputBufferEnable,
                                                        /* Digital input is not inverted */
                                                        kPORT_InputNormal,
                                                        /* Pin Control Register fields [15:0] are not locked */
                                                        kPORT_UnlockRegister};
        /* PORT2_6 (pin K2) is configured as SDHC0_D3 */
        PORT_SetPinConfig(PORT2, 6U, &port2_6_pinK2_config);
    }
    else
    {
        const port_pin_config_t port2_6_pinK2_config = {/* Internal pull-up resistor is enabled */
                                                        kPORT_PullUp,
                                                        /* Low internal pull resistor value is selected. */
                                                        kPORT_LowPullResistor,
                                                        /* Fast slew rate is configured */
                                                        kPORT_FastSlewRate,
                                                        /* Passive input filter is disabled */
                                                        kPORT_PassiveFilterDisable,
                                                        /* Open drain output is disabled */
                                                        kPORT_OpenDrainDisable,
                                                        /* Low drive strength is configured */
                                                        kPORT_LowDriveStrength,
                                                        /* Pin is configured as SDHC0_D3 */
                                                        kPORT_MuxAlt3,
                                                        /* Digital input enabled */
                                                        kPORT_InputBufferEnable,
                                                        /* Digital input is not inverted */
                                                        kPORT_InputNormal,
                                                        /* Pin Control Register fields [15:0] are not locked */
                                                        kPORT_UnlockRegister};
        /* PORT2_6 (pin K2) is configured as SDHC0_D3 */
        PORT_SetPinConfig(PORT2, 6U, &port2_6_pinK2_config);
    }
}

void BOARD_SDCardDetectInit(sd_cd_t cd, void *userData)
{
    uint8_t pinState;

    /* install card detect callback */
    s_cd.cdDebounce_ms = BOARD_SDMMC_SD_CARD_DETECT_DEBOUNCE_DELAY_MS;
    s_cd.type          = BOARD_SDMMC_SD_CD_TYPE;
    s_cd.cardDetected  = BOARD_SDCardGetDetectStatus;
    s_cd.callback      = cd;
    s_cd.userData      = userData;

    if (BOARD_SDMMC_SD_CD_TYPE == kSD_DetectCardByGpioCD)
    {
        hal_gpio_pin_config_t sw_config = {
            kHAL_GpioDirectionIn,
            0,
            BOARD_SDMMC_SD_CD_GPIO_PORT,
            BOARD_SDMMC_SD_CD_GPIO_PIN,
        };
        HAL_GpioInit(s_CardDetectGpioHandle, &sw_config);
        HAL_GpioSetTriggerMode(s_CardDetectGpioHandle, BOARD_SDMMC_SD_CD_INTTERUPT_TYPE);
        HAL_GpioInstallCallback(s_CardDetectGpioHandle, SDMMC_SD_CD_Callback, NULL);

        if (HAL_GpioGetInput(s_CardDetectGpioHandle, &pinState) == kStatus_HAL_GpioSuccess)
        {
            if (pinState == BOARD_SDMMC_SD_CD_INSERT_LEVEL)
            {
                if (cd != NULL)
                {
                    cd(true, userData);
                }
            }
        }
    }

    /* register DAT3 pull function switch function pointer */
    if (BOARD_SDMMC_SD_CD_TYPE == kSD_DetectCardByHostDATA3)
    {
        s_cd.dat3PullFunc = BOARD_SDCardDAT3PullFunction;
        BOARD_SDCardPowerControl(true);
    }
}

void BOARD_SDCardPowerResetInit(void)
{
    hal_gpio_pin_config_t sw_config = {
        kHAL_GpioDirectionOut,
        1,
        BOARD_SDMMC_SD_POWER_RESET_GPIO_PORT,
        BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN,
    };
    HAL_GpioInit(s_PowerResetGpioHandle, &sw_config);
}

void BOARD_SDCardPowerControl(bool enable)
{
    if (enable)
    {
        HAL_GpioSetOutput(s_PowerResetGpioHandle, 1);
    }
    else
    {
        HAL_GpioSetOutput(s_PowerResetGpioHandle, 0);
    }
}
#endif

#ifdef SD_ENABLED
void BOARD_SD_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, void *userData)
{
    assert(card);

    s_host.dmaDesBuffer                                      = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum                              = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    ((sd_card_t *)card)->host                                = &s_host;
    ((sd_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SD_HOST_BASEADDR;
    ((sd_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sd_card_t *)card)->usrParam.cd         = &s_cd;
    ((sd_card_t *)card)->usrParam.pwr        = BOARD_SDCardPowerControl;
    ((sd_card_t *)card)->usrParam.ioStrength = NULL;
    ((sd_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sd_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;

    BOARD_SDCardPowerResetInit();

    BOARD_SDCardDetectInit(cd, userData);

    NVIC_SetPriority(BOARD_SDMMC_SD_HOST_IRQ, hostIRQPriority);
}
#endif

#ifdef SDIO_ENABLED
void BOARD_SDIO_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, sdio_int_t cardInt)
{
    assert(card);

    s_host.dmaDesBuffer                                        = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum                                = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    ((sdio_card_t *)card)->host                                = &s_host;
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SDIO_HOST_BASEADDR;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sdio_card_t *)card)->usrParam.cd         = &s_cd;
    ((sdio_card_t *)card)->usrParam.pwr        = BOARD_SDCardPowerControl;
    ((sdio_card_t *)card)->usrParam.ioStrength = NULL;
    ((sdio_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sdio_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    BOARD_SDCardPowerResetInit();
    BOARD_SDCardDetectInit(cd, NULL);

    NVIC_SetPriority(BOARD_SDMMC_SDIO_HOST_IRQ, hostIRQPriority);
}
#endif

#ifdef MMC_ENABLED
void BOARD_MMC_Config(void *card, uint32_t hostIRQPriority)
{
    assert(card);

    s_host.dmaDesBuffer                                       = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum                               = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    ((mmc_card_t *)card)->host                                = &s_host;
    ((mmc_card_t *)card)->host->hostController.base           = BOARD_SDMMC_MMC_HOST_BASEADDR;
    ((mmc_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();
    ((mmc_card_t *)card)->host->tuningType                    = BOARD_SDMMC_MMC_TUNING_TYPE;
    ((mmc_card_t *)card)->usrParam.ioStrength                 = NULL;
    ((mmc_card_t *)card)->usrParam.maxFreq                    = BOARD_SDMMC_MMC_HOST_SUPPORT_HS200_FREQ;

    ((mmc_card_t *)card)->usrParam.capability |= BOARD_SDMMC_MMC_SUPPORT_8_BIT_DATA_WIDTH;

    ((mmc_card_t *)card)->hostVoltageWindowVCC  = BOARD_SDMMC_MMC_VCC_SUPPLY;
    ((mmc_card_t *)card)->hostVoltageWindowVCCQ = BOARD_SDMMC_MMC_VCCQ_SUPPLY;

    NVIC_SetPriority(BOARD_SDMMC_MMC_HOST_IRQ, hostIRQPriority);
}
#endif
