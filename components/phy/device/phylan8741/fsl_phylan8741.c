/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phylan8741.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY LAN8741 vendor defined registers. */
#define PHY_CONTROL_REG         0x11U /*!< The PHY control/status register. */
#define PHY_SEPCIAL_CONTROL_REG 0x1FU /*!< The PHY special control/status register. */

/*! @brief Defines the PHY LAN8741 device ID information. */
#define PHY_OUI       0x1F0U /*!< The PHY organizationally unique identifier. */
#define PHY_MODEL_NUM 0x12U  /*!< The PHY model number, 6-bit. */
#define PHY_DEVICE_ID ((PHY_OUI << 10U) | (PHY_MODEL_NUM << 4U))

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

/*! @brief Defines the PHY resource interface. */
#define PHY_LAN8741_WRITE(handle, regAddr, data) \
    ((phy_lan8741_resource_t *)(handle)->resource)->write((handle)->phyAddr, regAddr, data)
#define PHY_LAN8741_READ(handle, regAddr, pData) \
    ((phy_lan8741_resource_t *)(handle)->resource)->read((handle)->phyAddr, regAddr, pData)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phylan8741_ops = {.phyInit            = PHY_LAN8741_Init,
                                         .phyWrite           = PHY_LAN8741_Write,
                                         .phyRead            = PHY_LAN8741_Read,
                                         .getAutoNegoStatus  = PHY_LAN8741_GetAutoNegotiationStatus,
                                         .getLinkStatus      = PHY_LAN8741_GetLinkStatus,
                                         .getLinkSpeedDuplex = PHY_LAN8741_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex = PHY_LAN8741_SetLinkSpeedDuplex,
                                         .enableLoopback     = PHY_LAN8741_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_LAN8741_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter  = PHY_TIMEOUT_COUNT;
    status_t result   = kStatus_Success;
    uint16_t regValue = 0U;
    uint32_t devId    = 0U;

    /* Assign PHY address and operation resource. */
    handle->phyAddr  = config->phyAddr;
    handle->resource = config->resource;

    /* Check PHY ID. */
    do
    {
        result = PHY_LAN8741_READ(handle, PHY_ID1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        devId = (uint32_t)regValue << 16U;

        result = PHY_LAN8741_READ(handle, PHY_ID2_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        devId += regValue;

        /* The default revision number field(4-bit) may vary dependent on the silicon revision number. */
        devId &= ~((uint32_t)0xF);

        counter--;
    } while ((devId != PHY_DEVICE_ID) && (counter != 0U));

    if (counter == 0U)
    {
        return kStatus_Fail;
    }
    counter = PHY_TIMEOUT_COUNT;

    /* Reset PHY and wait until completion. */
    result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != kStatus_Success)
    {
        return result;
    }
    do
    {
        result = PHY_LAN8741_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result =
            PHY_LAN8741_WRITE(handle, PHY_AUTONEG_ADVERTISE_REG, (PHY_ALL_CAPABLE_MASK | PHY_IEEE802_3_SELECTOR_MASK));
        if (result == kStatus_Success)
        {
            /* Start Auto negotiation and wait until auto negotiation completion */
            result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG,
                                       (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }
    else
    {
        /* This PHY only supports 10/100M speed. */
        assert(config->speed <= kPHY_Speed100M);

        /* Disable isolate mode */
        result = PHY_LAN8741_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        regValue &= PHY_BCTL_ISOLATE_MASK;
        result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
        result = PHY_LAN8741_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }

    return result;
}

status_t PHY_LAN8741_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return PHY_LAN8741_WRITE(handle, phyReg, data);
}

status_t PHY_LAN8741_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return PHY_LAN8741_READ(handle, phyReg, pData);
}

status_t PHY_LAN8741_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = PHY_LAN8741_READ(handle, PHY_SEPCIAL_CONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_SPECIALCTL_AUTONEGDONE_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_LAN8741_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    uint16_t regValue;
    status_t result;

    /* Read the basic status register. */
    result = PHY_LAN8741_READ(handle, PHY_BASICSTATUS_REG, &regValue);
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

status_t PHY_LAN8741_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    uint16_t regValue;
    status_t result;

    /* Read the control register. */
    result = PHY_LAN8741_READ(handle, PHY_SEPCIAL_CONTROL_REG, &regValue);
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

status_t PHY_LAN8741_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    /* This PHY only supports 10/100M speed. */
    assert(speed <= kPHY_Speed100M);

    status_t result;
    uint16_t regValue;

    result = PHY_LAN8741_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_LAN8741_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
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
            result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        }
        else
        {
            result = PHY_LAN8741_READ(handle, PHY_CONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = PHY_LAN8741_WRITE(handle, PHY_CONTROL_REG, regValue | PHY_CTL_FARLOOPBACK_MASK);
            }
        }
    }
    else
    {
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = PHY_LAN8741_READ(handle, PHY_BASICCONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                regValue &= ~PHY_BCTL_LOOP_MASK;
                result = PHY_LAN8741_WRITE(handle, PHY_BASICCONTROL_REG, regValue | PHY_BCTL_RESTART_AUTONEG_MASK);
            }
        }
        else
        {
            result = PHY_LAN8741_READ(handle, PHY_CONTROL_REG, &regValue);
            if (result == kStatus_Success)
            {
                result = PHY_LAN8741_WRITE(handle, PHY_CONTROL_REG, regValue & ~PHY_CTL_FARLOOPBACK_MASK);
            }
        }
    }
    return result;
}
