/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#if defined(RW610)

#include <stdint.h>

#if CONFIG_MONOLITHIC_BLE_15_4
const uint8_t fw_cpu2_combo[] __attribute__ ((aligned(4))) = {
#if CONFIG_SOC_SERIES_RW6XX_REVISION_A2
#if CONFIG_MFG_MONOLITHIC
    #include <rw61xn_sb_mfg_fw_cpu2_combo_a2.bin.inc>
#else
    #include <rw61x_sb_ble_15d4_combo_a2.bin.inc>
#endif
#else
#error "Couldn't determine soc revision, please define CONFIG_SOC_SERIES_RW6XX_REVISION_A2"
#endif
};

#elif CONFIG_MONOLITHIC_BLE 

const uint8_t fw_cpu2_ble[] __attribute__ ((aligned(4))) = {
#if CONFIG_SOC_SERIES_RW6XX_REVISION_A2
#if CONFIG_MFG_MONOLITHIC
    #include <rw61xn_sb_mfg_fw_cpu2_ble_a2.bin.inc>
#else
    #include <rw61x_sb_ble_a2.bin.inc>
#endif
#else
#error "Couldn't determine soc revision, please define CONFIG_SOC_SERIES_RW6XX_REVISION_A2"
#endif
};

#endif /* CONFIG_MONOLITHIC_IEEE802154 */

#endif /* RW610 */