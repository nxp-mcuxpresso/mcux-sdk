/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_silicon_id_soc.h"

#if defined(MIMX8ML8_cm7_SERIES) || defined(MIMX8ML6_cm7_SERIES) || defined(MIMX8ML4_cm7_SERIES) || \
    defined(MIMX8ML3_cm7_SERIES)
#define OCOTP_UNIQUE_ID_ADDR_OFFSET (0x2U)
#else
#define OCOTP_UNIQUE_ID_ADDR_OFFSET (0x1U)
#endif

static status_t SILICONID_OcotpReadFuse(OCOTP_Type *base, uint32_t address, uint32_t *data)
{
    /* Make sure the OCOTP is ready, Overlapped accesses are not supported by the controller. */
    while (OCOTP_HW_OCOTP_CTRL_BUSY_MASK == (base->HW_OCOTP_CTRL & OCOTP_HW_OCOTP_CTRL_BUSY_MASK))
    {
    }

    /* If ERROR bit was set, clear access error status bit. */
    if (OCOTP_HW_OCOTP_CTRL_ERROR_MASK == (base->HW_OCOTP_CTRL & OCOTP_HW_OCOTP_CTRL_ERROR_MASK))
    {
        base->HW_OCOTP_CTRL_CLR = OCOTP_HW_OCOTP_CTRL_CLR_ERROR_MASK;
    }

    /* Write requested address to register. */
    base->HW_OCOTP_CTRL_CLR = OCOTP_HW_OCOTP_CTRL_CLR_ADDR_MASK;
    base->HW_OCOTP_CTRL_SET = OCOTP_HW_OCOTP_CTRL_SET_ADDR(address);
    base->HW_OCOTP_READ_CTRL |= OCOTP_HW_OCOTP_READ_CTRL_READ_FUSE_MASK;

    /* Wait for busy bit is cleared, and no error occurred on controller. */
    while (OCOTP_HW_OCOTP_CTRL_BUSY_MASK == (base->HW_OCOTP_CTRL & OCOTP_HW_OCOTP_CTRL_BUSY_MASK))
    {
    }

    /* If ERROR bit was set, this may be mean that the accsee to the register was wrong. */
    if (OCOTP_HW_OCOTP_CTRL_ERROR_MASK == (base->HW_OCOTP_CTRL & OCOTP_HW_OCOTP_CTRL_ERROR_MASK))
    {
        /* Clear access error status bit. */
        base->HW_OCOTP_CTRL_CLR = OCOTP_HW_OCOTP_CTRL_CLR_ERROR_MASK;

        return kStatus_Fail;
    }
    *data = base->HW_OCOTP_READ_FUSE_DATA;
    return kStatus_Success;
}

status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen)
{
    status_t result;
    uint32_t readBytes = *idLen;
    uint8_t uid[8];

    result = SILICONID_OcotpReadFuse(OCOTP, OCOTP_UNIQUE_ID_ADDR_OFFSET, (uint32_t *)(uintptr_t)&uid[0]);
    if (result != kStatus_Success)
    {
        *idLen = 0;
        return result;
    }

    result = SILICONID_OcotpReadFuse(OCOTP, OCOTP_UNIQUE_ID_ADDR_OFFSET + 1U, (uint32_t *)(uintptr_t)&uid[4]);
    if (result != kStatus_Success)
    {
        *idLen = 0;
        return result;
    }

    readBytes = (readBytes > 8U) ? 8U : readBytes;
    (void)memcpy((void *)&siliconId[0], (void *)&uid[0], readBytes);
    *idLen = readBytes;

    return kStatus_Success;
}
