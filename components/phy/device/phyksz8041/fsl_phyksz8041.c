/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyksz8041.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY8041 vendor defined registers. */
#define PHY_CONTROL1_REG 0x1EU /*!< The PHY control one register. */
#define PHY_CONTROL2_REG 0x1FU /*!< The PHY control two register. */

/*! @brief Defines the PHY KSZ8041 ID number. */
#define PHY_CONTROL_ID1 0x22U /*!< The PHY ID1*/

/*! @brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL1_REMOTELOOP_MASK    0x0008U /*!< The PHY remote loopback mask. */
#define PHY_CTL2_10HALFDUPLEX_MASK  0x0004U /*!< The PHY 10M half duplex mask. */
#define PHY_CTL2_100HALFDUPLEX_MASK 0x0008U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL2_10FULLDUPLEX_MASK  0x0014U /*!< The PHY 10M full duplex mask. */
#define PHY_CTL2_100FULLDUPLEX_MASK 0x0018U /*!< The PHY 100M full duplex mask. */

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phyksz8041_ops = {.phyInit            = PHY_KSZ8041_Init,
                                         .phyWrite           = PHY_KSZ8041_Write,
                                         .phyRead            = PHY_KSZ8041_Read,
                                         .getAutoNegoStatus  = PHY_KSZ8041_GetAutoNegotiationStatus,
                                         .getLinkStatus      = PHY_KSZ8041_GetLinkStatus,
                                         .getLinkSpeedDuplex = PHY_KSZ8041_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex = PHY_KSZ8041_SetLinkSpeedDuplex,
                                         .enableLoopback     = PHY_KSZ8041_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_KSZ8041_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter  = PHY_READID_TIMEOUT_COUNT;
    status_t result   = kStatus_Success;
    uint32_t regValue = 0;

    /* Init MDIO interface. */
    MDIO_Init(handle->mdioHandle);

    /* Assign phy address. */
    handle->phyAddr = config->phyAddr;

    /* Check PHY ID. */
    do
    {
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_ID1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        counter--;
    } while ((regValue != PHY_CONTROL_ID1) && (counter != 0U));

    if (counter == 0U)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
        if (config->autoNeg)
        {
            /* Set the negotiation. */
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | PHY_IEEE802_3_SELECTOR_MASK));
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                    (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* This PHY only supports 10/100M speed. */
            assert(config->speed <= kPHY_Speed100M);

            /* Disable isolate mode */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
            if (result != kStatus_Success)
            {
                return result;
            }
            regValue &= ~PHY_BCTL_ISOLATE_MASK;
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
            if (result != kStatus_Success)
            {
                return result;
            }

            /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
            result = PHY_KSZ8041_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
        }
    }

    return result;
}

status_t PHY_KSZ8041_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, phyReg, data);
}

status_t PHY_KSZ8041_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, phyReg, dataPtr);
}

status_t PHY_KSZ8041_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint32_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_KSZ8041_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint32_t regValue;

    /* Read the basic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((PHY_BSTATUS_LINKSTATUS_MASK & regValue) != 0U)
        {
            /* Link up. */
            *status = true;
        }
        else
        {
            /* Link down. */
            *status = false;
        }
    }
    return result;
}

status_t PHY_KSZ8041_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result = kStatus_Success;
    uint32_t regValue;
    uint32_t flag;

    /* Read the real time speed/duplex. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_CONTROL2_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            flag = regValue & PHY_BSTATUS_SPEEDUPLX_MASK;
            if ((PHY_CTL2_100HALFDUPLEX_MASK == flag) || (PHY_CTL2_100FULLDUPLEX_MASK == flag))
            {
                *speed = kPHY_Speed100M;
            }
            else
            {
                *speed = kPHY_Speed10M;
            }
        }

        if (duplex != NULL)
        {
            flag = regValue & PHY_BSTATUS_SPEEDUPLX_MASK;
            if ((PHY_CTL2_10FULLDUPLEX_MASK == flag) || (PHY_CTL2_100FULLDUPLEX_MASK == flag))
            {
                *duplex = kPHY_FullDuplex;
            }
            else
            {
                *duplex = kPHY_HalfDuplex;
            }
        }
    }

    return result;
}

status_t PHY_KSZ8041_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    /* This PHY only supports 10/100M speed. */
    assert(speed <= kPHY_Speed100M);

    status_t result;
    uint32_t regValue;

    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        /* Disable the auto-negotiation and set according to user-defined configuration. */
        regValue &= ~PHY_BCTL_AUTONEG_MASK;
        if (speed == kPHY_Speed100M)
        {
            regValue |= PHY_BCTL_SPEED0_MASK;
        }
        else
        {
            regValue &= ~PHY_BCTL_SPEED0_MASK;
        }
        if (duplex == kPHY_FullDuplex)
        {
            regValue |= PHY_BCTL_DUPLEX_MASK;
        }
        else
        {
            regValue &= ~PHY_BCTL_DUPLEX_MASK;
        }
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_KSZ8041_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    /* This PHY only supports local/remote loopback and 10/100M speed. */
    assert(mode <= kPHY_RemoteLoop);
    assert(speed <= kPHY_Speed100M);

    status_t result;
    uint32_t regValue;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed100M)
            {
                regValue = PHY_BCTL_SPEED0_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                regValue = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
        }
        else
        {
            /* First read the current status in control register. */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_CONTROL1_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_CONTROL1_REG,
                                    (regValue | PHY_CTL1_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                regValue &= ~PHY_BCTL_LOOP_MASK;
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                    (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_CONTROL1_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_CONTROL1_REG,
                                    (regValue & ~PHY_CTL1_REMOTELOOP_MASK));
            }
        }
    }
    return result;
}
