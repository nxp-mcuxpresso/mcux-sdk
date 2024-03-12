/*
 * Copyright 2016, 2022,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_LOADER_H__
#define __FSL_LOADER_H__

#include <stdint.h>
#include "fsl_common.h"

typedef enum
{
    LOAD_WIFI_FIRMWARE = 1,
    LOAD_BLE_FIRMWARE,
    LOAD_15D4_FIRMWARE,
#ifdef CONFIG_FW_VDLLV2
    LOAD_WIFI_VDLL_FIRMWARE,
#endif
    LOAD_TYPE_MAX,
} LOAD_Target_Type;

void power_on_device(LOAD_Target_Type loadTarget);
void power_off_device(LOAD_Target_Type loadTarget);

status_t sb3_fw_download(LOAD_Target_Type loadTarget, uint32_t flag, uint32_t sourceAddr);
status_t sb3_fw_reset(LOAD_Target_Type loadTarget, uint32_t flag, uint32_t sourceAddr);

//! @}

#endif
