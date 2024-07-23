/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"
#include "fsl_power.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "wifi_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
static sdmmchost_t s_host;
static sdio_card_int_t s_sdioInt;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t BOARD_USDHC1ClockConfiguration(void)
{
    /* Make sure USDHC ram buffer has power up */
    POWER_DisablePD(kPDRUNCFG_APD_USDHC1_SRAM);
    POWER_DisablePD(kPDRUNCFG_PPD_USDHC1_SRAM);
    POWER_DisablePD(kPDRUNCFG_PD_LPOSC);
    POWER_ApplyPD();

    /* SDIO1 */
    /* usdhc depend on 32K clock also */
    CLOCK_AttachClk(kLPOSC_DIV32_to_32KHZWAKE_CLK);
    CLOCK_AttachClk(kAUX0_PLL_to_SDIO1_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivSdio1Clk, 1);

    return CLOCK_GetSdioClkFreq(1);
}

void BOARD_WIFI_BT_Enable(bool enable)
{
    if (enable)
    {
        /* Enable module */
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Enable power supply for M.2 */
        GPIO_PortSet(BOARD_INITPINSM2_M2_3V3_GPIO, BOARD_INITPINSM2_M2_3V3_PORT, BOARD_INITPINSM2_M2_3V3_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Set SDIO_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_PORT,
                     BOARD_INITPINSM2_SDIO_RST_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Set WL_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_PORT, BOARD_INITPINSM2_WL_RST_PIN_MASK);
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
        /* Set WL_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_PORT, BOARD_INITPINSM2_WL_RST_PIN_MASK);
        /* Set SDIO_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_PORT,
                       BOARD_INITPINSM2_SDIO_RST_PIN_MASK);
        /* Disable power supply for M.2 */
        GPIO_PortClear(BOARD_INITPINSM2_M2_3V3_GPIO, BOARD_INITPINSM2_M2_3V3_PORT, BOARD_INITPINSM2_M2_3V3_PIN_MASK);
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
    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    ((sdio_card_t *)card)->host = &s_host;
    /* M.2 interface is using USDHC1 */
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_WIFI_BT_M2_SLOT_HOST_BASE;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();
    ((sdio_card_t *)card)->host->tuningType                    = BOARD_SDMMC_SD_TUNING_TYPE;

    ((sdio_card_t *)card)->usrParam.cd        = NULL;
    ((sdio_card_t *)card)->usrParam.pwr       = NULL;
    ((sdio_card_t *)card)->usrParam.ioVoltage = NULL;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    NVIC_SetPriority(BOARD_WIFI_BT_M2_SLOT_HOST_IRQ, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY);

#elif defined(WIFI_BT_USE_USD_INTERFACE)
    BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, cardInt);
#endif

    BOARD_WIFI_BT_Enable(false);
}
