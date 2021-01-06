/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phylan8720a.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY LAN8720A vendor defined registers. */
#define PHY_CONTROL_REG         0x11U /*!< The PHY control/status register. */
#define PHY_SEPCIAL_CONTROL_REG 0x1FU /*!< The PHY special control/status register. */

/*! @brief Defines the PHY LAN8720A ID number. */
#define PHY_CONTROL_ID1 0x07U /*!< The PHY ID1*/

/*!@brief Defines the mask flag of operation mode in control register*/
#define PHY_CTL_FARLOOPBACK_MASK 0x200U

/*!@brief Defines the mask flag of operation mode in special control register*/
#define PHY_SPECIALCTL_AUTONEGDONE_MASK 0x1000U /*!< The PHY auto-negotiation complete mask. */
#define PHY_SPECIALCTL_DUPLEX_MASK      0x0010U /*!< The PHY duplex mask. */
#define PHY_SPECIALCTL_100SPEED_MASK    0x0008U /*!< The PHY speed mask. */
#define PHY_SPECIALCTL_10SPEED_MASK     0x0004U /*!< The PHY speed mask. */
#define PHY_SPECIALCTL_SPEEDUPLX_MASK   0x001CU /*!< The PHY speed and duplex mask. */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define PHY_ALL_CAPABLE_MASK 0x1E0U

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 500000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phylan8720a_ops = {.phyInit            = PHY_LAN8720A_Init,
                                          .phyWrite           = PHY_LAN8720A_Write,
                                          .phyRead            = PHY_LAN8720A_Read,
                                          .getAutoNegoStatus  = PHY_LAN8720A_GetAutoNegotiationStatus,
                                          .getLinkStatus      = PHY_LAN8720A_GetLinkStatus,
                                          .getLinkSpeedDuplex = PHY_LAN8720A_GetLinkSpeedDuplex,
                                          .setLinkSpeedDuplex = PHY_LAN8720A_SetLinkSpeedDuplex,
                                          .enableLoopback     = PHY_LAN8720A_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_LAN8720A_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter  = PHY_TIMEOUT_COUNT;
    status_t result   = kStatus_Success;
    uint32_t regValue = 0U;

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
    counter = PHY_TIMEOUT_COUNT;

    /* Reset PHY and wait until completion. */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != kStatus_Success)
    {
        return result;
    }
    do
    {
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    } while ((counter-- != 0U) && (regValue & PHY_BCTL_RESET_MASK) != 0U);

    if (counter == 0U)
    {
        return kStatus_Fail;
    }

    if (config->autoNeg)
    {
        /* Set the ability. */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                            (PHY_ALL_CAPABLE_MASK | PHY_IEEE802_3_SELECTOR_MASK));
        if (result == kStatus_Success)
        {
            /* Start Auto negotiation and wait until auto negotiation completion */
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
        regValue &= PHY_BCTL_ISOLATE_MASK;
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
        result = PHY_LAN8720A_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }

    return result;
}

status_t PHY_LAN8720A_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, phyReg, data);
}

status_t PHY_LAN8720A_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, phyReg, dataPtr);
}

status_t PHY_LAN8720A_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint32_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SEPCIAL_CONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_SPECIALCTL_AUTONEGDONE_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_LAN8720A_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    uint32_t regValue;
    status_t result;

    /* Read the basic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_LINKSTATUS_MASK) != 0U)
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

status_t PHY_LAN8720A_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    uint32_t regValue;
    status_t result;

    /* Read the control register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SEPCIAL_CONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            if ((regValue & PHY_SPECIALCTL_100SPEED_MASK) != 0U)
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
            if ((regValue & PHY_SPECIALCTL_DUPLEX_MASK) != 0U)
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

status_t PHY_LAN8720A_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
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

status_t PHY_LAN8720A_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
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
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_CONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_CONTROL_REG,
                                    (regValue | PHY_CTL_FARLOOPBACK_MASK));
            }
        }
    }
    else
    {
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
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_CONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_CONTROL_REG,
                                    (regValue & ~PHY_CTL_FARLOOPBACK_MASK));
            }
        }
    }
    return result;
}
