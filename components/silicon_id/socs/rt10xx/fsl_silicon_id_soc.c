/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_silicon_id_soc.h"

status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen)
{
    uint32_t readBytes = *idLen;
    uint8_t uid[8];

    *((uint32_t *)(uintptr_t)&uid[0]) = OCOTP->CFG0;
    *((uint32_t *)(uintptr_t)&uid[4]) = OCOTP->CFG1;

    readBytes = (readBytes > 8U) ? 8U : readBytes;
    (void)memcpy((void *)&siliconId[0], (void *)&uid[0], readBytes);
    *idLen = readBytes;

    return kStatus_Success;
}
