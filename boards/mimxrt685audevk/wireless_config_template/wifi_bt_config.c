/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_pca9420.h"
#include "wifi_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
extern uint32_t BOARD_USDHC0ClockConfiguration(void);
extern void BOARD_SDCardIoVoltageControlInit(void);
extern void BOARD_SDCardIoVoltageControl(sdmmc_operation_voltage_t voltage);
extern void BOARD_SDCardPowerResetInit(void);
extern void BOARD_SDCardPowerControl(bool enable);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
static sd_io_voltage_t s_ioVoltage = {
    .type = BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE,
    .func = BOARD_SDCardIoVoltageControl,
};

static sdmmchost_t s_host;
static sdio_card_int_t s_sdioInt;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_WIFI_BT_Enable(bool enable)
{
    if (enable)
    {
        /* Enable module */
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Enable power supply for M.2 */
        GPIO_PortSet(BOARD_INITPINSM2_SD_RST_N_GPIO, BOARD_INITPINSM2_SD_RST_N_PORT,
                     BOARD_INITPINSM2_SD_RST_N_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Set WL_REG_ON to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_WL_REG_ON_GPIO, BOARD_INITPINSM2_WL_REG_ON_PORT,
                     BOARD_INITPINSM2_WL_REG_ON_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));
#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Enable power supply for SD */
        GPIO_PortSet(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PORT,
                     1U << BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN);
        vTaskDelay(pdMS_TO_TICKS(100));
#endif /* WIFI_BT_USE_M2_INTERFACE */
    }
    else
    {
        /* Disable module */
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Set WL_REG_ON to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_WL_REG_ON_GPIO, BOARD_INITPINSM2_WL_REG_ON_PORT,
                       BOARD_INITPINSM2_WL_REG_ON_PIN_MASK);
        /* Disable power supply for M.2 */
        GPIO_PortClear(BOARD_INITPINSM2_SD_RST_N_GPIO, BOARD_INITPINSM2_SD_RST_N_PORT,
                       BOARD_INITPINSM2_SD_RST_N_PIN_MASK);

#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Disable power supply for SD */
        GPIO_PortClear(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PORT,
                       1U << BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN);
#endif /* WIFI_BT_USE_M2_INTERFACE */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void BOARD_WIFI_BT_Config(void *card, sdio_int_t cardInt)
{
#ifdef WIFI_BT_USE_M2_INTERFACE
    assert(card);

    s_host.dmaDesBuffer                                        = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum                                = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    ((sdio_card_t *)card)->host                                = &s_host;
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SDIO_HOST_BASEADDR;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC0ClockConfiguration();

    ((sdio_card_t *)card)->usrParam.cd = NULL;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    ((sdio_card_t *)card)->usrParam.pwr       = BOARD_SDCardPowerControl;
    ((sdio_card_t *)card)->usrParam.ioVoltage = &s_ioVoltage;

    BOARD_SDCardPowerResetInit();
    BOARD_SDCardIoVoltageControlInit();

    NVIC_SetPriority(BOARD_SDMMC_SDIO_HOST_IRQ, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY);
#elif defined(WIFI_BT_USE_USD_INTERFACE)
    BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, cardInt);
#endif

    BOARD_WIFI_BT_Enable(false);
}
