/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_WM8524_ADAPTER_H__
#define __SRTM_WM8524_ADAPTER_H__

#include "srtm_audio_service.h"
#include "fsl_wm8524.h"
#include "fsl_codec_common.h"
/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _srtm_wm8524_config
{
    wm8524_config_t config;
} srtm_wm8524_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create WM8524 adapter.
 *
 * @param driver WM8524 driver handle.
 * @param config WM8524 driver configuration.
 * @return SRTM WM8524 adapter on success or NULL on failure.
 */
srtm_codec_adapter_t SRTM_Wm8524Adapter_Create(codec_handle_t *driver, srtm_wm8524_config_t *config);

/*!
 * @brief Destroy WM8524 adapter.
 *
 * @param adapter WM8524 adapter to destroy.
 */
void SRTM_Wm8524Adapter_Destroy(srtm_codec_adapter_t adapter);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_WM8524_ADAPTER_H__ */
