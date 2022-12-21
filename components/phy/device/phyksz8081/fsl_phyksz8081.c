/*
 * Copyright 2020-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyksz8081.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY KSZ8081 vendor defined registers. */
#define PHY_INTR_CONTROL_STATUS_REG (0x1BU) /*!< The PHY interrupt control/status register. */
#define PHY_CONTROL1_REG            (0x1EU) /*!< The PHY control one register. */
#define PHY_CONTROL2_REG            (0x1FU) /*!< The PHY control two register. */

/*! @brief Defines the PHY KSZ8081 ID number. */
#define PHY_CONTROL_ID1 0x22U /*!< The PHY ID1 */

/*! @brief Defines the mask flag of operation mode in interrupt control/status registers */
#define PHY_INTR_CONTROL_STATUS_LINK_UP_MASK   ((uint16_t)0x0100U) /*!< The PHY link up interrupt mask. */
#define PHY_INTR_CONTROL_STATUS_LINK_DOWN_MASK ((uint16_t)0x0400U) /*!< The PHY link down interrupt mask. */

/*! @brief Defines the mask flag of operation mode in control registers */
#define PHY_CTL2_REMOTELOOP_MASK    ((uint16_t)0x0004U) /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK ((uint16_t)0x0080U) /*!< The PHY RMII reference clock select. */
#define PHY_CTL2_INTR_LEVEL_MASK    ((uint16_t)0x0200U) /*!< The PHY interrupt level mask. */
#define PHY_CTL1_10HALFDUPLEX_MASK  ((uint16_t)0x0001U) /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK ((uint16_t)0x0002U) /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK  ((uint16_t)0x0005U) /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK ((uint16_t)0x0006U) /*!< The PHY 100M full duplex mask. */
#define PHY_CTL1_SPEEDUPLX_MASK     ((uint16_t)0x0007U) /*!< The PHY speed and duplex mask. */
#define PHY_CTL1_ENERGYDETECT_MASK  ((uint16_t)0x0010U) /*!< The PHY signal present on rx differential pair. */
#define PHY_CTL1_LINKUP_MASK        ((uint16_t)0x0100U) /*!< The PHY link up. */
#define PHY_LINK_READY_MASK         (PHY_CTL1_ENERGYDETECT_MASK | PHY_CTL1_LINKUP_MASK)

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT (1000U)

/*! @brief Defines the PHY resource interface. */
#define PHY_KSZ8081_WRITE(handle, regAddr, data) \
    (((phy_ksz8081_resource_t *)(handle)->resource)->write((handle)->phyAddr, regAddr, data))
#define PHY_KSZ8081_READ(handle, regAddr, pData) \
    (((phy_ksz8081_resource_t *)(handle)->resource)->read((handle)->phyAddr, regAddr, pData))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const phy_operations_t phyksz8081_ops = {.phyInit             = PHY_KSZ8081_Init,
                                         .phyWrite            = PHY_KSZ8081_Write,
                                         .phyRead             = PHY_KSZ8081_Read,
                                         .getAutoNegoStatus   = PHY_KSZ8081_GetAutoNegotiationStatus,
                                         .getLinkStatus       = PHY_KSZ8081_GetLinkStatus,
                                         .getLinkSpeedDuplex  = PHY_KSZ8081_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex  = PHY_KSZ8081_SetLinkSpeedDuplex,
                                         .enableLoopback      = PHY_KSZ8081_EnableLoopback,
                                         .enableLinkInterrupt = PHY_KSZ8081_EnableLinkInterrupt,
                                         .clearInterrupt      = PHY_KSZ8081_ClearInterrupt};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_KSZ8081_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter  = PHY_READID_TIMEOUT_COUNT;
    status_t result   = kStatus_Success;
    uint16_t regValue = 0;

    /* Assign PHY address and operation resource. */
    handle->phyAddr  = config->phyAddr;
    handle->resource = config->resource;

    /* Check PHY ID. */
    do
    {
        result = PHY_KSZ8081_READ(handle, PHY_ID1_REG, &regValue);
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
    result = PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        result = PHY_KSZ8081_READ(handle, PHY_CONTROL2_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = PHY_KSZ8081_WRITE(handle, PHY_CONTROL2_REG, (regValue | PHY_CTL2_REFCLK_SELECT_MASK));
        if (result != kStatus_Success)
        {
            return result;
        }
#endif /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */

        /* Set PHY link status management interrupt. */
        result = PHY_KSZ8081_EnableLinkInterrupt(handle, config->intrType, config->enableLinkIntr);
        if (result != kStatus_Success)
        {
            return result;
        }

        if (config->autoNeg)
        {
            /* Set the auto-negotiation then start it. */
            result = PHY_KSZ8081_WRITE(
                handle, PHY_AUTONEG_ADVERTISE_REG,
                (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK | PHY_10BASETX_FULLDUPLEX_MASK |
                 PHY_10BASETX_HALFDUPLEX_MASK | PHY_IEEE802_3_SELECTOR_MASK));
            if (result == kStatus_Success)
            {
                result = PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG,
                                           (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* This PHY only supports 10/100M speed. */
            assert(config->speed <= kPHY_Speed100M);

            /* Disable isolate mode */
            result = PHY_KSZ8081_READ(handle, PHY_BASICCONTROL_REG, &regValue);
            if (result != kStatus_Success)
            {
                return result;
            }
            regValue &= ~PHY_BCTL_ISOLATE_MASK;
            result = PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
            if (result != kStatus_Success)
            {
                return result;
            }

            /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
            result = PHY_KSZ8081_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
        }
    }
    return result;
}

status_t PHY_KSZ8081_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return PHY_KSZ8081_WRITE(handle, phyReg, data);
}

status_t PHY_KSZ8081_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return PHY_KSZ8081_READ(handle, phyReg, pData);
}

status_t PHY_KSZ8081_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = PHY_KSZ8081_READ(handle, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_KSZ8081_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    /* Read the basic status register. */
    result = PHY_KSZ8081_READ(handle, PHY_BASICSTATUS_REG, &regValue);
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

status_t PHY_KSZ8081_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint16_t regValue;
    uint16_t flag;

    /* Read the control register. */
    result = PHY_KSZ8081_READ(handle, PHY_CONTROL1_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            flag = regValue & PHY_CTL1_SPEEDUPLX_MASK;
            if ((PHY_CTL1_100HALFDUPLEX_MASK == flag) || (PHY_CTL1_100FULLDUPLEX_MASK == flag))
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
            flag = regValue & PHY_CTL1_SPEEDUPLX_MASK;
            if ((PHY_CTL1_10FULLDUPLEX_MASK == flag) || (PHY_CTL1_100FULLDUPLEX_MASK == flag))
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

status_t PHY_KSZ8081_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    /* This PHY only supports 10/100M speed. */
    assert(speed <= kPHY_Speed100M);

    status_t result;
    uint16_t regValue;

    result = PHY_KSZ8081_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result = PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_KSZ8081_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    /* This PHY only supports local/remote loopback and 10/100M speed. */
    assert(mode <= kPHY_RemoteLoop);
    assert(speed <= kPHY_Speed100M);

    status_t result;
    uint16_t regValue;

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
            return PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        }
        else
        {
            /* Remote loopback only supports 100M full-duplex. */
            assert(speed == kPHY_Speed100M);

            regValue = PHY_BCTL_SPEED0_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            result   = PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
            if (result != kStatus_Success)
            {
                return result;
            }
            /* Set the remote loopback bit. */
            result = PHY_KSZ8081_READ(handle, PHY_CONTROL2_REG, &regValue);
            if (result == kStatus_Success)
            {
                return PHY_KSZ8081_WRITE(handle, PHY_CONTROL2_REG, (regValue | PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = PHY_KSZ8081_READ(handle, PHY_BASICCONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                regValue &= ~PHY_BCTL_LOOP_MASK;
                return PHY_KSZ8081_WRITE(handle, PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = PHY_KSZ8081_READ(handle, PHY_CONTROL2_REG, &regValue);
            if (result == kStatus_Success)
            {
                return PHY_KSZ8081_WRITE(handle, PHY_CONTROL2_REG, regValue & ~PHY_CTL2_REMOTELOOP_MASK);
            }
        }
    }
    return result;
}

status_t PHY_KSZ8081_EnableLinkInterrupt(phy_handle_t *handle, phy_interrupt_type_t type, bool enable)
{
    assert((type == kPHY_IntrActiveLow) || (type == kPHY_IntrActiveHigh));

    status_t result;
    uint16_t regValue;

    /* Read operation will clear pending interrupt before enable interrupt. */
    result = PHY_KSZ8081_READ(handle, PHY_INTR_CONTROL_STATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        /* Enable/Disable link up+down interrupt. */
        if (enable)
        {
            regValue |= (PHY_INTR_CONTROL_STATUS_LINK_UP_MASK | PHY_INTR_CONTROL_STATUS_LINK_DOWN_MASK);
        }
        else
        {
            regValue &= ~(PHY_INTR_CONTROL_STATUS_LINK_UP_MASK | PHY_INTR_CONTROL_STATUS_LINK_DOWN_MASK);
        }
        result = PHY_KSZ8081_WRITE(handle, PHY_INTR_CONTROL_STATUS_REG, regValue);
    }
    if (result != kStatus_Success)
    {
        return result;
    }

    if (enable)
    {
        /* Set link interrupt type. */
        result = PHY_KSZ8081_READ(handle, PHY_CONTROL2_REG, &regValue);
        if (result == kStatus_Success)
        {
            if (type == kPHY_IntrActiveLow)
            {
                regValue &= ~PHY_CTL2_INTR_LEVEL_MASK;
            }
            else
            {
                regValue |= PHY_CTL2_INTR_LEVEL_MASK;
            }
            result = PHY_KSZ8081_WRITE(handle, PHY_CONTROL2_REG, regValue);
        }
    }

    return result;
}

status_t PHY_KSZ8081_ClearInterrupt(phy_handle_t *handle)
{
    uint16_t regValue;

    return PHY_KSZ8081_READ(handle, PHY_INTR_CONTROL_STATUS_REG, &regValue);
}
