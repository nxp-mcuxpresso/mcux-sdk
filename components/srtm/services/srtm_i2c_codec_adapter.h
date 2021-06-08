/*
 * Copyright 2017-2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_I2C_CODEC_ADAPTER_H__
#define __SRTM_I2C_CODEC_ADAPTER_H__

#include "srtm_audio_service.h"
#include "fsl_codec_common.h"
#include "fsl_codec_i2c.h"
/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef status_t (*srtm_i2c_read_reg_map_t)(void *handle, uint32_t reg, uint32_t *val);
typedef status_t (*srtm_i2c_write_reg_map_t)(void *handle, uint32_t reg, uint32_t val);

typedef struct _srtm_i2c_codec_config
{
    uint32_t mclk;
    uint8_t slaveAddr;
    codec_reg_addr_t addrType;
    codec_reg_width_t regWidth;
    srtm_i2c_read_reg_map_t readRegMap;
    srtm_i2c_write_reg_map_t writeRegMap;
    void *i2cHandle;
} srtm_i2c_codec_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create I2C Codec adapter.
 *
 * @param driver Codec driver handle.
 * @param config Codec driver configuration.
 * @return SRTM Codec adapter on success or NULL on failure.
 */
srtm_codec_adapter_t SRTM_I2CCodecAdapter_Create(codec_handle_t *driver, srtm_i2c_codec_config_t *config);

/*!
 * @brief Destroy I2C Codec adapter.
 *
 * @param adapter Codec adapter to destroy.
 */
void SRTM_I2CCodecAdapter_Destroy(srtm_codec_adapter_t adapter);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_I2C_CODEC_ADAPTER_H__ */
