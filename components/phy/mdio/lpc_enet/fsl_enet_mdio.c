/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_enet_mdio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void ENET_MDIO_Init(mdio_handle_t *handle);

static status_t ENET_MDIO_Write(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t data);

static status_t ENET_MDIO_Read(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t *dataPtr);

/*******************************************************************************
 * Variables
 ******************************************************************************/

const mdio_operations_t lpc_enet_ops = {.mdioInit     = ENET_MDIO_Init,
                                        .mdioWrite    = ENET_MDIO_Write,
                                        .mdioRead     = ENET_MDIO_Read,
                                        .mdioWriteExt = NULL,
                                        .mdioReadExt  = NULL};

/*******************************************************************************
 * Code
 ******************************************************************************/

static void ENET_MDIO_Init(mdio_handle_t *handle)
{
    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    uint32_t instance         = ENET_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    (void)CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI(base);
}

static status_t ENET_MDIO_Write(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t data)
{
    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;
#ifdef MDIO_TIMEOUT_COUNT
    uint32_t counter;
#endif

    ENET_StartSMIWrite(base, phyAddr, devAddr, data);
#ifdef MDIO_TIMEOUT_COUNT
    for (counter = MDIO_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if (!ENET_IsSMIBusy(base))
        {
            break;
        }
    }
    /* Check for timeout. */
    if (0U == counter)
    {
        result = kStatus_PHY_SMIVisitTimeout;
    }
#else
    while (ENET_IsSMIBusy(base))
    {
    }
#endif

    return result;
}

static status_t ENET_MDIO_Read(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t *dataPtr)
{
    assert(dataPtr);

    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;
#ifdef MDIO_TIMEOUT_COUNT
    uint32_t counter;
#endif

    ENET_StartSMIRead(base, phyAddr, devAddr);
#ifdef MDIO_TIMEOUT_COUNT
    for (counter = MDIO_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if (!ENET_IsSMIBusy(base))
        {
            break;
        }
    }
    /* Check for timeout. */
    if (0U == counter)
    {
        result = kStatus_PHY_SMIVisitTimeout;
    }
#else
    while (ENET_IsSMIBusy(base))
    {
    }
#endif
    *dataPtr = ENET_ReadSMIData(base);

    return result;
}
