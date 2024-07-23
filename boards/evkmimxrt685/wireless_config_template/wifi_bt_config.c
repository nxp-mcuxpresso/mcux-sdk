/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"
#include "fsl_gpio.h"
#include "wifi_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifdef WIFI_BT_USE_M2_INTERFACE
#warning "M.2 interface is not supported on this board"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_WIFI_BT_Enable(bool enable)
{
    if (enable)
    {
        /* Enable module */
        /* Enable power supply for SD */
        GPIO_PortSet(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PORT,
                     1 << BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN);
    }
    else
    {
        /* Disable module */
        /* Disable power supply for SD */
        GPIO_PortClear(BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE, BOARD_SDMMC_SD_POWER_RESET_GPIO_PORT,
                       1 << BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
}

void BOARD_WIFI_BT_Config(void *card, sdio_int_t cardInt)
{
    BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, cardInt);
    BOARD_WIFI_BT_Enable(false);
}
