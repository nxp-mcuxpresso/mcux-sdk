/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if !MCUX_DBI_LEGACY
status_t DBI_IFACE_SelectArea(dbi_iface_t *dbiIface, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    uint8_t data[4];
    status_t status;

    /*Column addresses*/
    data[0] = (uint8_t)(startX >> 8U) & 0xFFU;
    data[1] = (uint8_t)startX & 0xFFU;
    data[2] = (uint8_t)(endX >> 8U) & 0xFFU;
    data[3] = (uint8_t)endX & 0xFFU;

    status = DBI_IFACE_WriteCmdData(dbiIface, (uint8_t)kMIPI_DBI_SetColumnAddress, data, 4U);

    if (status != kStatus_Success)
    {
        return status;
    }

    /*Page addresses*/
    data[0] = (uint8_t)(startY >> 8U) & 0xFFU;
    data[1] = (uint8_t)startY & 0xFFU;
    data[2] = (uint8_t)(endY >> 8U) & 0xFFU;
    data[3] = (uint8_t)endY & 0xFFU;

    status = DBI_IFACE_WriteCmdData(dbiIface, (uint8_t)kMIPI_DBI_SetPageAddress, data, 4U);

    return status;
}

void DBI_IFACE_SetMemoryDoneCallback(dbi_iface_t *dbiIface, dbi_mem_done_callback_t callback, void *userData)
{
    dbiIface->memDoneCallback      = callback;
    dbiIface->memDoneCallbackParam = userData;
}
#endif /* !MCUX_DBI_LEGACY */
