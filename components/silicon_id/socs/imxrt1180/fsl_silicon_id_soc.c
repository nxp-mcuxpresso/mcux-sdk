/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_silicon_id_soc.h"

status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen)
{
    uint32_t readBytes = *idLen;
    uint8_t uid[16];

    *((uint32_t *)(uintptr_t)&uid[0]) = OCOTP_FSB->OTP_SHADOW_PARTA[15];
    *((uint32_t *)(uintptr_t)&uid[4]) = OCOTP_FSB->OTP_SHADOW_PARTA[14];
    *((uint32_t *)(uintptr_t)&uid[8]) = OCOTP_FSB->OTP_SHADOW_PARTA[13];
    *((uint32_t *)(uintptr_t)&uid[12]) = OCOTP_FSB->OTP_SHADOW_PARTA[12];

    readBytes = (readBytes > 16U) ? 16U : readBytes;
    (void)memcpy((void *)&siliconId[0], (void *)&uid[0], readBytes);
    *idLen = readBytes;

    return kStatus_Success;
}
