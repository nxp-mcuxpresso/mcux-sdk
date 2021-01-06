/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_crc.h"
#include "fsl_crc.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t HAL_CrcCompute(hal_crc_config_t *crcConfig, uint8_t *dataIn, uint32_t length)
{
    crc_config_t config;
    uint32_t result;

    config.polynomial         = crcConfig->crcPoly;
    config.seed               = crcConfig->crcSeed;
    config.reflectIn          = (bool)crcConfig->crcRefIn;
    config.reflectOut         = (bool)crcConfig->crcRefOut;
    config.complementChecksum = (bool)crcConfig->complementChecksum;

    assert((crcConfig->crcSize == 2U) || (crcConfig->crcSize == 4U));

    if (crcConfig->crcSize == 2U)
    {
        config.crcBits = kCrcBits16;
    }
    else
    {
        config.crcBits = kCrcBits32;
    }

    config.crcResult = kCrcFinalChecksum;

    CRC_Init(CRC0, &config);
    CRC_WriteData(CRC0, dataIn, length);

    if (crcConfig->crcSize == 2U)
    {
        result = (uint32_t)CRC_Get16bitResult(CRC0);
    }
    else
    {
        result = CRC_Get32bitResult(CRC0);
    }

    return result;
}
