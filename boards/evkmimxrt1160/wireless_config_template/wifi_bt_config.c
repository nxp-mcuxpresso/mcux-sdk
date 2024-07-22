/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "wifi_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
extern uint32_t BOARD_USDHC1ClockConfiguration(void);
#if __CORTEX_M == 7
extern void BOARD_USDHC_Errata(void);
#endif
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
/* two cache line length for sdmmc host driver maintain unalign transfer */
SDK_ALIGN(static uint8_t s_sdmmcCacheLineAlignBuffer[BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U],
          BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
#endif

static sd_io_voltage_t s_ioVoltage = {
    .type = BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE,
    .func = NULL,
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
        /* Set SDIO_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_GPIO_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Set WL_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_GPIO_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));
#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Enable power supply for SD */
        GPIO_PinWrite(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
#endif /* WIFI_BT_USE_M2_INTERFACE */
    }
    else
    {
        /* Disable module */
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Set WL_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_GPIO_PIN_MASK);
        /* Set SDIO_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_GPIO_PIN_MASK);
#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Disable power supply for SD */
        GPIO_PinWrite(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN, 1);
#endif /* WIFI_BT_USE_M2_INTERFACE */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void BOARD_WIFI_BT_Config(void *card, sdio_int_t cardInt)
{
#ifdef WIFI_BT_USE_M2_INTERFACE
    assert(card);

    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
#if ((defined __DCACHE_PRESENT) && __DCACHE_PRESENT) || (defined FSL_FEATURE_HAS_L1CACHE && FSL_FEATURE_HAS_L1CACHE)
    s_host.enableCacheControl = BOARD_SDMMC_HOST_CACHE_CONTROL;
#endif
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
    s_host.cacheAlignBuffer     = s_sdmmcCacheLineAlignBuffer;
    s_host.cacheAlignBufferSize = BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U;
#endif

    ((sdio_card_t *)card)->host                                = &s_host;
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SDIO_HOST_BASEADDR;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sdio_card_t *)card)->usrParam.cd         = NULL;
    ((sdio_card_t *)card)->usrParam.pwr        = NULL;
    ((sdio_card_t *)card)->usrParam.ioStrength = NULL;
    ((sdio_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sdio_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    NVIC_SetPriority(BOARD_SDMMC_SDIO_HOST_IRQ, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY);

#if __CORTEX_M == 7
    BOARD_USDHC_Errata();
#endif

#elif defined(WIFI_BT_USE_USD_INTERFACE)
    BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, cardInt);
#endif

    BOARD_WIFI_BT_Enable(false);
}
