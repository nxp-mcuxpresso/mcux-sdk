/*
 * Copyright 2017-2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_i2c_codec_adapter.h"
#include "srtm_heap.h"
#include "fsl_codec_i2c.h"
#include "srtm_audio_service.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Codec adapter */
typedef struct _srtm_i2c_codec_adapter
{
    struct _srtm_codec_adapter adapter;
    srtm_i2c_codec_config_t config;
    codec_handle_t *driver;
    uint32_t srate;
    uint8_t format;
} *srtm_i2c_codec_adapter_t;

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
static srtm_status_t SRTM_I2CCodecAdapter_SetParam(srtm_codec_adapter_t adapter,
                                                   uint8_t index,
                                                   uint8_t format,
                                                   uint32_t srate)
{
    srtm_i2c_codec_adapter_t handle = (srtm_i2c_codec_adapter_t)(void *)adapter;
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d. fmt %d, srate %d\r\n", __func__, index, format, srate);
    uint32_t bitWidth = 0U;

    if (format > (uint8_t)SRTM_Audio_DSD32bits)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: unsupported format %d!\r\n", __func__, format);
        return SRTM_Status_InvalidParameter;
    }

    if (handle->srate != srate || handle->format != format)
    {
        handle->format = format;

        if (format >= (uint8_t)SRTM_Audio_DSD8bits)
        {
            (void)CODEC_ModuleControl(handle->driver, kCODEC_ModuleSwitchI2SInInterface,
                                      kCODEC_ModuleI2SInInterfaceDSD);
        }
        else
        {
            (void)CODEC_ModuleControl(handle->driver, kCODEC_ModuleSwitchI2SInInterface,
                                      kCODEC_ModuleI2SInInterfacePCM);
        }

        if ((format >= (uint8_t)SRTM_Audio_DSD8bits) && (format <= (uint8_t)SRTM_Audio_DSD32bits))
        {
            bitWidth = saiFormatMap[format - 45U].bitwidth;
        }
        else if (format <= (uint8_t)SRTM_Audio_Stereo32Bits)
        {
            bitWidth = saiFormatMap[format].bitwidth;
        }
        else
        {
            return SRTM_Status_Error;
        }

        /* Only set codec when configuration changes. */
        (void)CODEC_SetFormat(handle->driver, handle->config.mclk, srate, bitWidth);
        handle->srate = srate;
    }

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_I2CCodecAdapter_SetReg(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t regVal)
{
    srtm_i2c_codec_adapter_t handle = (srtm_i2c_codec_adapter_t)(void *)adapter;
    status_t status;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d, %d\r\n", __func__, reg, regVal);

    if (handle->config.writeRegMap != NULL)
    {
        status = handle->config.writeRegMap(handle->driver, reg, regVal);
    }
    else
    {
        status =
            CODEC_I2C_Send(handle->config.i2cHandle, handle->config.slaveAddr, reg, (uint8_t)handle->config.addrType,
                           (uint8_t *)(&regVal), (uint8_t)handle->config.regWidth);
    }
    return status == kStatus_Success ? SRTM_Status_Success : SRTM_Status_Error;
}

static srtm_status_t SRTM_I2CCodecAdapter_GetReg(srtm_codec_adapter_t adapter, uint32_t reg, uint32_t *pRegVal)
{
    srtm_i2c_codec_adapter_t handle = (srtm_i2c_codec_adapter_t)(void *)adapter;
    status_t status;

    assert(pRegVal != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d\r\n", __func__, reg);

    *pRegVal = 0; /* Clear high bytes. */
    if (handle->config.readRegMap != NULL)
    {
        status = handle->config.readRegMap(handle->driver, reg, pRegVal);
    }
    else
    {
        status = CODEC_I2C_Receive(handle->config.i2cHandle, handle->config.slaveAddr, reg,
                                   (uint8_t)handle->config.addrType, (void *)pRegVal, (uint8_t)handle->config.regWidth);
    }
    return status == kStatus_Success ? SRTM_Status_Success : SRTM_Status_Error;
}

srtm_codec_adapter_t SRTM_I2CCodecAdapter_Create(codec_handle_t *driver, srtm_i2c_codec_config_t *config)
{
    srtm_i2c_codec_adapter_t handle;

    assert((driver != NULL) && (config != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_i2c_codec_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_i2c_codec_adapter));
    assert(handle != NULL);

    handle->driver = driver;
    (void)memcpy(&handle->config, config, sizeof(struct _srtm_i2c_codec_config));
    handle->srate  = 0;
    handle->format = 0;

    /* Adapter interfaces. */
    handle->adapter.setParam = SRTM_I2CCodecAdapter_SetParam;
    handle->adapter.setReg   = SRTM_I2CCodecAdapter_SetReg;
    handle->adapter.getReg   = SRTM_I2CCodecAdapter_GetReg;

    return &handle->adapter;
}

void SRTM_I2CCodecAdapter_Destroy(srtm_codec_adapter_t adapter)
{
    srtm_i2c_codec_adapter_t handle = (srtm_i2c_codec_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    SRTM_Heap_Free(handle);
}
