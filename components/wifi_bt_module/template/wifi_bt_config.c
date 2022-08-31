/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "wifi_bt_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Set SDIO_RST to 1 */

        /* Set WL_RST to 1 */

#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Enable power supply for SD */

#endif /* WIFI_BT_USE_M2_INTERFACE */
    }
    else
    {
        /* Disable module */
#ifdef WIFI_BT_USE_M2_INTERFACE
        /* Set WL_RST to 0 */

        /* Set SDIO_RST to 0 */

#elif defined(WIFI_BT_USE_USD_INTERFACE)
        /* Disable power supply for SD */

#endif /* WIFI_BT_USE_M2_INTERFACE */
    }
}

void BOARD_WIFI_BT_Config(void *card, sdio_int_t cardInt)
{
    BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, cardInt);

#ifdef WIFI_BT_USE_M2_INTERFACE
    ((sdio_card_t *)card)->usrParam.pwr = NULL;

#endif
    BOARD_WIFI_BT_Enable(false);
}
