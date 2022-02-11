/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phy.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 500000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t reg;
    uint32_t idReg    = 0;
    uint32_t delay    = PHY_TIMEOUT_COUNT;
    uint32_t instance = ENET_GetInstance(base);
    bool status       = false;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    (void)CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
    ENET_SetSMI(base, srcClock_Hz, false);
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_SetSMI(base);
#endif
    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (delay != 0U))
    {
        (void)PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        delay--;
    }

    if (delay == 0U)
    {
        return kStatus_Fail;
    }
    delay = PHY_TIMEOUT_COUNT;

    /* Reset PHY and wait until completion. */
    (void)PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    do
    {
        (void)PHY_Read(base, phyAddr, PHY_BASICCONTROL_REG, &reg);
    } while ((delay-- != 0U) && ((reg & PHY_BCTL_RESET_MASK) != 0U));

    if (delay == 0U)
    {
        return kStatus_Fail;
    }

    /* Set the ability. */
    (void)PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG, (PHY_ALL_CAPABLE_MASK | 0x1U));

    /* Start Auto negotiation and wait until auto negotiation completion */
    (void)PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
    delay = PHY_TIMEOUT_COUNT;
    do
    {
        (void)PHY_Read(base, phyAddr, PHY_SEPCIAL_CONTROL_REG, &reg);
        delay--;
    } while ((delay != 0U) && ((reg & PHY_SPECIALCTL_AUTONEGDONE_MASK) == 0U));

    if (delay == 0U)
    {
        return kStatus_PHY_AutoNegotiateFail;
    }

    /* Waiting a moment for phy stable. */
    for (delay = 0U; delay < PHY_TIMEOUT_COUNT; delay++)
    {
        __ASM("nop");
        (void)PHY_GetLinkStatus(base, phyAddr, &status);
        if (status)
        {
            break;
        }
    }

    return kStatus_Success;
}

status_t PHY_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (counter == 0U)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_StartSMIWrite(base, phyAddr, phyReg, data);
    while (ENET_IsSMIBusy(base))
    {
    }
#endif
    return kStatus_Success;
}

status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
    assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) != 0U)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (counter == 0U)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_StartSMIRead(base, phyAddr, phyReg);
    while (ENET_IsSMIBusy(base))
    {
    }
    *dataPtr = ENET_ReadSMIData(base);
#endif
    return kStatus_Success;
}

status_t PHY_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    uint32_t reg;
    status_t result = kStatus_Success;

    /* Read the basic status register. */
    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &reg);
    if (result == kStatus_Success)
    {
        if ((reg & PHY_BSTATUS_LINKSTATUS_MASK) != 0U)
        {
            /* link up. */
            *status = true;
        }
        else
        {
            *status = false;
        }
    }
    return result;
}

status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);
    assert(speed);

    uint32_t reg;
    status_t result = kStatus_Success;

    /* Read the control two register. */
    result = PHY_Read(base, phyAddr, PHY_SEPCIAL_CONTROL_REG, &reg);
    if (result == kStatus_Success)
    {
        if ((reg & PHY_SPECIALCTL_DUPLEX_MASK) != 0U)
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        if ((reg & PHY_SPECIALCTL_100SPEED_MASK) != 0U)
        {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
        else
        { /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }
    return result;
}
