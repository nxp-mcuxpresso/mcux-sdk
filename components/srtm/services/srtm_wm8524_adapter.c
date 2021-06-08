/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_wm8524_adapter.h"
#include "srtm_heap.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* WM8524 adapter */
typedef struct _srtm_wm8524_adapter
{
    struct _srtm_codec_adapter adapter;
    srtm_wm8524_config_t config;
    codec_handle_t *driver;
} * srtm_wm8524_adapter_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Currently only 1 audio instance is adequate, so index is just ignored */
static srtm_status_t SRTM_CodecAdapter_SetParam(srtm_codec_adapter_t adapter,
                                                uint8_t index,
                                                uint8_t format,
                                                uint32_t srate)
{
    return SRTM_Status_Success;
}
static srtm_status_t SRTM_CodecAdapter_SetReg(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t regVal)
{
    return SRTM_Status_Success;
}

static srtm_status_t SRTM_CodecAdapter_GetReg(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t *pRegVal)
{
    return SRTM_Status_Success;
}
srtm_codec_adapter_t SRTM_Wm8524Adapter_Create(codec_handle_t *driver, srtm_wm8524_config_t *config)
{
    srtm_wm8524_adapter_t handle;

    assert((driver != NULL) && (config != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_wm8524_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_wm8524_adapter));
    assert(handle != NULL);

    handle->driver = driver;
    (void)memcpy(&handle->config, config, sizeof(struct _srtm_wm8524_config));

    /* Adapter interfaces. */
    handle->adapter.setParam = SRTM_CodecAdapter_SetParam;
    handle->adapter.setReg   = SRTM_CodecAdapter_SetReg;
    handle->adapter.getReg   = SRTM_CodecAdapter_GetReg;

    return &handle->adapter;
}

void SRTM_Wm8524Adapter_Destroy(srtm_codec_adapter_t adapter)
{
    srtm_wm8524_adapter_t handle = (srtm_wm8524_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    SRTM_Heap_Free(handle);
}
