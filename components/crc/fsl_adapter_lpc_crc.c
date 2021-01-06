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
    CRC_Type *const s_CrcList[] = CRC_BASE_PTRS;
    crc_config_t config;
    uint32_t result;

    config.seed          = crcConfig->crcSeed;
    config.reverseIn     = (bool)crcConfig->crcRefIn;
    config.complementIn  = false;
    config.complementOut = (bool)crcConfig->complementChecksum;
    config.reverseOut    = (bool)crcConfig->crcRefOut;

    assert((crcConfig->crcSize == 2U) || (crcConfig->crcSize == 4U));

    if (crcConfig->crcSize == 2U)
    {
        config.polynomial = kCRC_Polynomial_CRC_CCITT;
    }
    else
    {
        config.polynomial = kCRC_Polynomial_CRC_32;
    }

    CRC_Init(s_CrcList[0], &config);
    CRC_WriteData(s_CrcList[0], dataIn, length);

    if (crcConfig->crcSize == 2U)
    {
        result = (uint32_t)CRC_Get16bitResult(s_CrcList[0]);
    }
    else
    {
        result = CRC_Get32bitResult(s_CrcList[0]);
    }

    return result;
}
