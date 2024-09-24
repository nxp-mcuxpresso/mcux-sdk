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
    data[0] = (startX >> 8) & 0xFF;
    data[1] = startX & 0xFF;
    data[2] = (endX >> 8) & 0xFF;
    data[3] = endX & 0xFF;

    status = DBI_IFACE_WriteCmdData(dbiIface, kMIPI_DBI_SetColumnAddress, data, 4);

    if (status != kStatus_Success)
    {
        return status;
    }

    /*Page addresses*/
    data[0] = (startY >> 8) & 0xFF;
    data[1] = startY & 0xFF;
    data[2] = (endY >> 8) & 0xFF;
    data[3] = endY & 0xFF;

    status = DBI_IFACE_WriteCmdData(dbiIface, kMIPI_DBI_SetPageAddress, data, 4);

    return status;
}

void DBI_IFACE_SetMemoryDoneCallback(dbi_iface_t *dbiIface, dbi_mem_done_callback_t callback, void *userData)
{
    dbiIface->memDoneCallback      = callback;
    dbiIface->memDoneCallbackParam = userData;
}
#endif /* !MCUX_DBI_LEGACY */
