/*
 * Copyright 2020-2021 NXP
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
#if defined(FSL_FEATURE_ENET_HAS_EXTEND_MDIO) && FSL_FEATURE_ENET_HAS_EXTEND_MDIO
static status_t ENET_MDIO_WriteExt(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t data);
static status_t ENET_MDIO_ReadExt(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t *dataPtr);
#endif
static status_t ENET_MDIO_WaitTransferOver(ENET_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

const mdio_operations_t enet_ops = {.mdioInit  = ENET_MDIO_Init,
                                    .mdioWrite = ENET_MDIO_Write,
                                    .mdioRead  = ENET_MDIO_Read,
#if defined(FSL_FEATURE_ENET_HAS_EXTEND_MDIO) && FSL_FEATURE_ENET_HAS_EXTEND_MDIO
                                    .mdioWriteExt = ENET_MDIO_WriteExt,
                                    .mdioReadExt  = ENET_MDIO_ReadExt};
#else
                                    .mdioWriteExt = NULL,
                                    .mdioReadExt  = NULL};
#endif

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
    ENET_SetSMI(base, resource->csrClock_Hz, false);
}

static status_t ENET_MDIO_Write(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t data)
{
    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, devAddr, kENET_MiiWriteValidFrame, data);

    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Clear SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return result;
}

static status_t ENET_MDIO_Read(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t *dataPtr)
{
    assert(dataPtr != NULL);

    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, devAddr, kENET_MiiReadValidFrame);

    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Get data from SMI register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return result;
}

#if defined(FSL_FEATURE_ENET_HAS_EXTEND_MDIO) && FSL_FEATURE_ENET_HAS_EXTEND_MDIO
static status_t ENET_MDIO_WriteExt(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t data)
{
    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;

    /* Write the register address */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
    ENET_StartExtC45SMIWriteReg(base, phyAddr, devAddr);
    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Write data to the specified register address */
    ENET_StartExtC45SMIWriteData(base, phyAddr, devAddr, data);
    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return result;
}

static status_t ENET_MDIO_ReadExt(mdio_handle_t *handle, uint32_t phyAddr, uint32_t devAddr, uint32_t *dataPtr)
{
    assert(dataPtr != NULL);

    mdio_resource_t *resource = (mdio_resource_t *)&handle->resource;
    ENET_Type *base           = (ENET_Type *)resource->base;
    status_t result           = kStatus_Success;

    /* Write the register address */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
    ENET_StartExtC45SMIWriteReg(base, phyAddr, devAddr);
    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Read data from the specified register address */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
    ENET_StartExtC45SMIReadData(base, phyAddr, devAddr);
    result = ENET_MDIO_WaitTransferOver(base);
    if (result != kStatus_Success)
    {
        return result;
    }
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
    *dataPtr = ENET_ReadSMIData(base);
    return result;
}
#endif

static status_t ENET_MDIO_WaitTransferOver(ENET_Type *base)
{
    status_t result = kStatus_Success;
#ifdef MDIO_TIMEOUT_COUNT
    uint32_t counter;
#endif

    /* Wait for SMI complete. */
#ifdef MDIO_TIMEOUT_COUNT
    for (counter = MDIO_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if (ENET_EIR_MII_MASK == (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK))
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
    while (ENET_EIR_MII_MASK != (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK))
    {
    }
#endif
    return result;
}
