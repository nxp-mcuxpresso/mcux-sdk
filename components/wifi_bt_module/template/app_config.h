/*
 *  Copyright 2021-2022 NXP
 *  All rights reserved.
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Supported Wi-Fi boards (modules):
 *     WIFI_88W8801_BOARD_AW_NM191_USD
 *     WIFI_88W8801_BOARD_AW_NM191MA
 *     WIFI_IW416_BOARD_AW_AM457_USD
 *     WIFI_IW416_BOARD_AW_AM457MA
 *     WIFI_IW416_BOARD_AW_AM510_USD
 *     WIFI_IW416_BOARD_AW_AM510MA
 *     WIFI_88W8987_BOARD_AW_CM358_USD
 *     WIFI_88W8987_BOARD_AW_CM358MA
 *     WIFI_88W8801_BOARD_MURATA_2DS_USD
 *     WIFI_88W8801_BOARD_MURATA_2DS_M2
 *     WIFI_IW416_BOARD_MURATA_1XK_USD
 *     WIFI_IW416_BOARD_MURATA_1XK_M2
 *     WIFI_88W8987_BOARD_MURATA_1ZM_USD
 *     WIFI_88W8987_BOARD_MURATA_1ZM_M2
 */
#ifndef NOT_DEFINE_DEFAULT_WIFI_MODULE
#define WIFI_IW416_BOARD_AW_AM510_USD
#endif

/* Wi-Fi boards configuration list */

/* AzureWave AW-NM191-uSD */
#if defined(WIFI_88W8801_BOARD_AW_NM191_USD)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8801
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                        \
    {                                           \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x1B \
    }

/* AzureWave AW-NM191MA */
#elif defined(WIFI_88W8801_BOARD_AW_NM191MA)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8801
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                        \
    {                                           \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x1B \
    }

/* AzureWave AW-AM457-uSD */
#elif defined(WIFI_IW416_BOARD_AW_AM457_USD)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_USD_INTERFACE
#define OVERRIDE_CALIBRATION_DATA "WIFI_IW416_BOARD_AW_AM457_CAL_DATA_EXT.h"
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* AzureWave AW-AM457MA */
#elif defined(WIFI_IW416_BOARD_AW_AM457MA)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_M2_INTERFACE
#define OVERRIDE_CALIBRATION_DATA "WIFI_IW416_BOARD_AW_AM457_CAL_DATA_EXT.h"
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* AzureWave AW-AM510-uSD */
#elif defined(WIFI_IW416_BOARD_AW_AM510_USD)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* AzureWave AW-AM510MA */
#elif defined(WIFI_IW416_BOARD_AW_AM510MA)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* AzureWave AW-CM358-uSD */
#elif defined(WIFI_88W8987_BOARD_AW_CM358_USD)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8987
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* AzureWave AW-CM358MA */
#elif defined(WIFI_88W8987_BOARD_AW_CM358MA)
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_WW.h"
#define SD8987
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x9, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0xC \
    }

/* Murata 2DS + Murata uSD-M.2 adapter */
#elif defined(WIFI_88W8801_BOARD_MURATA_2DS_USD)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_WW.h"
#define SD8801
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingSDR25HighSpeedMode
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                        \
    {                                           \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x0E \
    }

/* Murata 2DS */
#elif defined(WIFI_88W8801_BOARD_MURATA_2DS_M2)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_2DS_WW.h"
#define SD8801
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingSDR25HighSpeedMode
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                        \
    {                                           \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x0E \
    }

/* Murata 1XK + Murata uSD-M.2 adapter */
#elif defined(WIFI_IW416_BOARD_MURATA_1XK_USD)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x0, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0x6 \
    }

/* Murata 1XK */
#elif defined(WIFI_IW416_BOARD_MURATA_1XK_M2)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1XK_WW.h"
#define SD8978
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x0, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0x6 \
    }

/* Murata 1ZM + Murata uSD-M.2 adapter */
#elif defined(WIFI_88W8987_BOARD_MURATA_1ZM_USD)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_WW.h"
#define SD8987
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_USD_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x6, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0x6 \
    }

/* Murata 1ZM */
#elif defined(WIFI_88W8987_BOARD_MURATA_1ZM_M2)
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_CA.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_EU.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_JP.h"
// #define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_US.h"
#define WIFI_BT_TX_PWR_LIMITS "wlan_txpwrlimit_cfg_murata_1ZM_WW.h"
#define SD8987
#define SDMMCHOST_OPERATION_VOLTAGE_1V8
#define SD_TIMING_MAX kSD_TimingDDR50Mode
#define WIFI_BT_USE_M2_INTERFACE
#define WLAN_ED_MAC_CTRL                                                               \
    {                                                                                  \
        .ed_ctrl_2g = 0x1, .ed_offset_2g = 0x6, .ed_ctrl_5g = 0x1, .ed_offset_5g = 0x6 \
    }

#else
#error "Please define macro related to wifi board"
#endif

#include "wifi_config.h"
