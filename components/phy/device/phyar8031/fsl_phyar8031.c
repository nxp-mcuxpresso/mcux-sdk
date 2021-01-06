/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyar8031.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY AR8031 vendor defined registers. */
#define PHY_SPECIFIC_STATUS_REG    0x11U /*!< The PHY specific status register. */
#define PHY_COPPERFIBER_STATUS_REG 0x1BU /*!< The PHY copper/fiber status register. */
#define PHY_DEBUGPORT_ADDR_REG     0x1DU /*!< The PHY Debug port address register.*/
#define PHY_DEBUGPORT_DATA_REG     0x1EU /*!< The PHY Debug port data register.*/
#define PHY_CHIP_CFG_REG           0x1FU /*!< The PHY chip configure register. */

/*! @brief Defines the Debug register offset. */
#define PHY_DEBUG_HIBECTL_REG_OFFSET 0x0BU /*!< The PHY Debug register offset 0xB.*/
#define PHY_DEBUG_EXTLOOP_REG_OFFSET 0x11U /*!< The PHY Debug register offset 0x11.*/

/*! @brief Defines the PHY AR8031 ID number. */
#define PHY_CONTROL_ID1 0x004DU /*!< The PHY ID1 is 0x004D. */

/*!@brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL2_REMOTELOOP_MASK    0x0004U /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK 0x0080U /*!< The PHY RMII reference clock select. */
#define PHY_CTL1_10HALFDUPLEX_MASK  0x0001U /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK 0x0002U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK  0x0005U /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK 0x0006U /*!< The PHY 100M full duplex mask. */

/*! @brief Defines the mask flag in specific status register. */
#define PHY_SSTATUS_LINKSTATUS_MASK 0x0400U /*!< The PHY link status mask. */
#define PHY_SSTATUS_LINKSPEED_MASK  0xC000U /*!< The PHY link speed mask. */
#define PHY_SSTATUS_LINKDUPLEX_MASK 0x2000U /*!< The PHY link duplex mask. */
#define PHY_SSTATUS_LINKSPEED_SHIFT 14U     /*!< The link speed shift */

/*! @brief Defines the mask flag in PHY debug register- hibernate control register. */
#define PHY_DEBUG_HIBERNATECTL_REG 0x8000U /*!< The power hibernate control mask. */

/*! @brief Defines the PHY MMD access. */
#define PHY_MMD_DEVICEID3             3U     /*!< The PHY device id 3. */
#define PHY_MMD_REMOTEPHY_LOOP_OFFSET 0x805A /*!< The PHY MMD phy register */
#define PHY_MMD_SMARTEEE_CTL_OFFSET   0x805D /*!< The PHY MMD smartEEE register */
#define PHY_MMD_SMARTEEE_LPI_EN_SHIFT 8U     /*!< The SmartEEE enable/disable bit shift */
/*! @brief Defines the chip configure register. */
#define PHY_MODE_CFG_MASK 0xFU /*!< The PHY mode configure mask. */

/*! @brief MDIO MMD Devices .*/
#define PHY_MDIO_MMD_PCS 3U
#define PHY_MDIO_MMD_AN  7U

/*! @brief MDIO MMD Physical Coding layer device registers .*/
#define PHY_MDIO_PCS_EEE_CAP 0x14U /* EEE capability */

/*! @brief MDIO MMD AutoNegotiation device registers .*/
#define PHY_MDIO_AN_EEE_ADV 0x3CU /* EEE advertisement */

/*! @brief MDIO MMD EEE mask flags. (common for adv and cap) */
#define PHY_MDIO_EEE_100TX 0x2U
#define PHY_MDIO_EEE_1000T 0x4U

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static status_t PHY_AR8031_MMD_SetDevice(phy_handle_t *handle,
                                         uint8_t device,
                                         uint16_t addr,
                                         phy_mmd_access_mode_t mode);
static inline status_t PHY_AR8031_MMD_ReadData(phy_handle_t *handle, uint32_t *data);
static inline status_t PHY_AR8031_MMD_WriteData(phy_handle_t *handle, uint32_t data);
static status_t PHY_AR8031_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint32_t *data);
static status_t PHY_AR8031_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint32_t data);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const phy_operations_t phyar8031_ops = {.phyInit            = PHY_AR8031_Init,
                                        .phyWrite           = PHY_AR8031_Write,
                                        .phyRead            = PHY_AR8031_Read,
                                        .getAutoNegoStatus  = PHY_AR8031_GetAutoNegotiationStatus,
                                        .getLinkStatus      = PHY_AR8031_GetLinkStatus,
                                        .getLinkSpeedDuplex = PHY_AR8031_GetLinkSpeedDuplex,
                                        .setLinkSpeedDuplex = PHY_AR8031_SetLinkSpeedDuplex,
                                        .enableLoopback     = PHY_AR8031_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_AR8031_Init(phy_handle_t *handle, const phy_config_t *config)
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

    /* Configure RMII voltage 1.8V */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x1F);
    if (result != kStatus_Success)
    {
        return result;
    }
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0x8);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Reset PHY. */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
        /* Close smartEEE. */
        result = PHY_AR8031_MMD_SetDevice(handle, PHY_MMD_DEVICEID3, PHY_MMD_SMARTEEE_CTL_OFFSET,
                                          kPHY_MMDAccessNoPostIncrement);
        if (result == kStatus_Success)
        {
            result = PHY_AR8031_MMD_ReadData(handle, &regValue);
            if (result == kStatus_Success)
            {
                result = PHY_AR8031_MMD_WriteData(handle, (regValue & ~((uint32_t)1 << PHY_MMD_SMARTEEE_LPI_EN_SHIFT)));
            }
        }
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable Tx clock delay */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x5);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, (regValue | 0x0100U));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable Rx clock delay */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x0);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, (regValue | 0x8000U));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Energy Efficient Ethernet config */
        if (config->enableEEE)
        {
            /* Get capabilities */
            result = PHY_AR8031_MMD_Read(handle, PHY_MDIO_MMD_PCS, PHY_MDIO_PCS_EEE_CAP, &regValue);
            if (result == kStatus_Success)
            {
                /* Enable EEE for 100TX and 1000T */
                result = PHY_AR8031_MMD_Write(handle, PHY_MDIO_MMD_AN, PHY_MDIO_AN_EEE_ADV,
                                              regValue & (PHY_MDIO_EEE_1000T | PHY_MDIO_EEE_100TX));
            }
        }
        else
        {
            result = PHY_AR8031_MMD_Write(handle, PHY_MDIO_MMD_AN, PHY_MDIO_AN_EEE_ADV, 0);
        }
        if (result != kStatus_Success)
        {
            return result;
        }

        if (config->autoNeg)
        {
            /* Set the negotiation. */
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | PHY_IEEE802_3_SELECTOR_MASK));
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_1000BASET_CONTROL_REG,
                                    PHY_1000BASET_FULLDUPLEX_MASK | PHY_1000BASET_HALFDUPLEX_MASK);
                if (result == kStatus_Success)
                {
                    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
                    if (result != kStatus_Success)
                    {
                        return result;
                    }
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                        (regValue | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
                }
            }
        }
        else
        {
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
            result = PHY_AR8031_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
        }
    }

    return result;
}

status_t PHY_AR8031_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, phyReg, data);
}

status_t PHY_AR8031_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, phyReg, dataPtr);
}

status_t PHY_AR8031_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
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

status_t PHY_AR8031_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t regValue;

    /* Read the basic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SPECIFIC_STATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((PHY_SSTATUS_LINKSTATUS_MASK & regValue) != 0U)
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

status_t PHY_AR8031_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint32_t regValue;

    /* Read the specfic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SPECIFIC_STATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            switch ((regValue & PHY_SSTATUS_LINKSPEED_MASK) >> PHY_SSTATUS_LINKSPEED_SHIFT)
            {
                case (uint32_t)kPHY_Speed10M:
                    *speed = kPHY_Speed10M;
                    break;
                case (uint32_t)kPHY_Speed100M:
                    *speed = kPHY_Speed100M;
                    break;
                case (uint32_t)kPHY_Speed1000M:
                    *speed = kPHY_Speed1000M;
                    break;
                default:
                    *speed = kPHY_Speed10M;
                    break;
            }
        }

        if (duplex != NULL)
        {
            if ((regValue & PHY_SSTATUS_LINKDUPLEX_MASK) != 0U)
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

status_t PHY_AR8031_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    status_t result;
    uint32_t regValue;

    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        /* Disable the auto-negotiation and set according to user-defined configuration. */
        regValue &= ~PHY_BCTL_AUTONEG_MASK;
        if (speed == kPHY_Speed1000M)
        {
            regValue &= PHY_BCTL_SPEED0_MASK;
            regValue |= PHY_BCTL_SPEED1_MASK;
        }
        else if (speed == kPHY_Speed100M)
        {
            regValue |= PHY_BCTL_SPEED0_MASK;
            regValue &= ~PHY_BCTL_SPEED1_MASK;
        }
        else
        {
            regValue &= ~PHY_BCTL_SPEED0_MASK;
            regValue &= ~PHY_BCTL_SPEED1_MASK;
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

status_t PHY_AR8031_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint32_t regValue;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed1000M)
            {
                regValue = PHY_BCTL_SPEED1_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else if (speed == kPHY_Speed100M)
            {
                regValue = PHY_BCTL_SPEED0_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                regValue = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
        }
        else if (mode == kPHY_RemoteLoop)
        {
            result = PHY_AR8031_MMD_Write(handle, PHY_MMD_DEVICEID3, PHY_MMD_REMOTEPHY_LOOP_OFFSET, 1);
        }
        else
        {
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, PHY_DEBUG_HIBECTL_REG_OFFSET);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG,
                                        PHY_DEBUG_EXTLOOP_REG_OFFSET);
                    if (result == kStatus_Success)
                    {
                        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 1);
                        if (result == kStatus_Success)
                        {
                            if (speed == kPHY_Speed1000M)
                            {
                                regValue = PHY_BCTL_SPEED1_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            else if (speed == kPHY_Speed100M)
                            {
                                regValue = PHY_BCTL_SPEED0_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            else
                            {
                                regValue = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
                        }
                    }
                }
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
        else if (mode == kPHY_RemoteLoop)
        {
            result = PHY_AR8031_MMD_Write(handle, PHY_MMD_DEVICEID3, PHY_MMD_REMOTEPHY_LOOP_OFFSET, 0);
        }
        else
        {
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, PHY_DEBUG_HIBECTL_REG_OFFSET);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG,
                                        PHY_DEBUG_EXTLOOP_REG_OFFSET);
                    if (result == kStatus_Success)
                    {
                        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                        if (result == kStatus_Success)
                        {
                            regValue = PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESET_MASK;
                            result   = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, regValue);
                        }
                    }
                }
            }
        }
    }
    return result;
}

static status_t PHY_AR8031_MMD_SetDevice(phy_handle_t *handle,
                                         uint8_t device,
                                         uint16_t addr,
                                         phy_mmd_access_mode_t mode)
{
    status_t result = kStatus_Success;

    /* Set Function mode of address access(b00) and device address. */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG, device);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set register address. */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, addr);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set Function mode of data access(b01~11) and device address. */
    result =
        MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG, (uint32_t)mode | (uint32_t)device);
    return result;
}

static inline status_t PHY_AR8031_MMD_ReadData(phy_handle_t *handle, uint32_t *data)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, data);
}

static inline status_t PHY_AR8031_MMD_WriteData(phy_handle_t *handle, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, data);
}

static status_t PHY_AR8031_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint32_t *data)
{
    status_t result = kStatus_Success;
    result          = PHY_AR8031_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_AR8031_MMD_ReadData(handle, data);
    }
    return result;
}

static status_t PHY_AR8031_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint32_t data)
{
    status_t result = kStatus_Success;

    result = PHY_AR8031_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_AR8031_MMD_WriteData(handle, data);
    }
    return result;
}
