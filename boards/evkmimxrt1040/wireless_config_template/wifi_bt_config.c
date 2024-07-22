/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "sdmmc_config.h"
#include "fsl_iomuxc.h"
#include "wifi_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifdef WIFI_BT_USE_USD_INTERFACE
#warning "uSD interface is not supported"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void BOARD_SD_Pin_Config(uint32_t freq);
extern uint32_t BOARD_USDHC1ClockConfiguration(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
/* two cache line length for sdmmc host driver maintain unalign transfer */
SDK_ALIGN(static uint8_t s_sdmmcCacheLineAlignBuffer[BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U],
          BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
#endif
static sdmmchost_t s_host;
static sd_io_voltage_t s_ioVoltage = {
    .type = BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE,
    .func = NULL,
};
static sdio_card_int_t s_sdioInt;

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_WIFI_BT_Enable(bool enable)
{
    if (enable)
    {
        /* Enable module */

        /* Set SDIO_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Set WL_RST to 1 */
        GPIO_PortSet(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_PIN_MASK);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    else
    {
        /* Disable module */

        /* Set WL_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_WL_RST_GPIO, BOARD_INITPINSM2_WL_RST_PIN_MASK);
        /* Set SDIO_RST to 0 */
        GPIO_PortClear(BOARD_INITPINSM2_SDIO_RST_GPIO, BOARD_INITPINSM2_SDIO_RST_PIN_MASK);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void BOARD_WIFI_BT_Config(void *card, sdio_int_t cardInt)
{
    assert(card);

    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    s_host.enableCacheControl   = BOARD_SDMMC_HOST_CACHE_CONTROL;
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
    s_host.cacheAlignBuffer     = s_sdmmcCacheLineAlignBuffer;
    s_host.cacheAlignBufferSize = BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U;
#endif

    ((sdio_card_t *)card)->host                                = &s_host;
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SDIO_HOST_BASEADDR;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sdio_card_t *)card)->usrParam.ioStrength = BOARD_SD_Pin_Config;
    ((sdio_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sdio_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    NVIC_SetPriority(BOARD_SDMMC_SDIO_HOST_IRQ, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY);

    BOARD_WIFI_BT_Enable(false);
}
