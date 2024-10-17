/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#if defined(RW610)

#include <stdint.h>

#if CONFIG_MONOLITHIC_WIFI
const uint8_t fw_cpu1[] __attribute__ ((aligned(4))) = {
#if CONFIG_SOC_SERIES_RW6XX_REVISION_A2
#if CONFIG_MFG_MONOLITHIC
    #include <rw61xw_sb_mfg_fw_cpu1_a2.bin.inc>
#else
    #include <rw61x_sb_wifi_a2.bin.inc>
#endif
#else
#error "Couldn't determine soc revision, please define CONFIG_SOC_SERIES_RW6XX_REVISION_A2"
#endif
};

const unsigned char *wlan_fw_bin = (const unsigned char *)(void *)&fw_cpu1[0];
const unsigned int wlan_fw_bin_len = sizeof(fw_cpu1);
#endif /* CONFIG_MONOLITHIC_WIFI */

#endif /* RW610 */