/*
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyvsc8541.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY VSC8541 vendor defined registers. */
#define PHY_AUXILIARY_CTRL_STATUS_REG 0x1CU /*!< The PHY auxiliary control and status register. */
#define PHY_PAGE_SELECT_REG           0x1FU /*!< The PHY page select register. */

/*! @brief Defines the PHY VSC8541 device ID information. */
#define PHY_OUI                 0x1C1U /*!< The PHY organizationally unique identifier. */
#define PHY_MODEL_NUM           0x37U  /*!< The PHY organizationally unique identifier. */
#define PHY_DEVICE_REVISION_NUM 0x2U   /*!< The PHY organizationally unique identifier. */
#define PHY_DEVICE_ID           ((PHY_OUI << 10U) | (PHY_MODEL_NUM << 4U) | (PHY_DEVICE_REVISION_NUM))

/*! @brief Defines the mask flag in specific status register. */
#define PHY_AUXILIARY_CTRL_STATUS_LINKSPEED_MASK  0x18U /*!< The PHY link speed mask. */
#define PHY_AUXILIARY_CTRL_STATUS_LINKDUPLEX_MASK 0x20U /*!< The PHY link duplex mask. */
#define PHY_AUXILIARY_CTRL_STATUS_LINKSPEED_SHIFT 3U    /*!< The link speed shift */

/*! @brief Defines the PHY VSC8541 extra page and the registers in specified page. */
#define PHY_RGMII_TXRX_DELAY_REG 0x14U /*!< The RGMII TXC/RXC delay register. */
#define PHY_RGMII_TX_DELAY_SHIFT 0U    /*!< The RGMII TXC delay mask. */
#define PHY_RGMII_RX_DELAY_SHIFT 4U    /*!< The RGMII RXC delay mask. */

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/*! @brief Defines the PHY resource interface. */
#define PHY_VSC8541_WRITE(handle, regAddr, data) \
    ((phy_vsc8541_resource_t *)(handle)->resource)->write((handle)->phyAddr, regAddr, data)
#define PHY_VSC8541_READ(handle, regAddr, pData) \
    ((phy_vsc8541_resource_t *)(handle)->resource)->read((handle)->phyAddr, regAddr, pData)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if 0
static status_t PHY_VSC8541_MMD_SetDevice(phy_handle_t *handle,
                                          uint8_t device,
                                          uint16_t addr,
                                          phy_mmd_access_mode_t mode);
static inline status_t PHY_VSC8541_MMD_ReadData(phy_handle_t *handle, uint16_t *pData);
static inline status_t PHY_VSC8541_MMD_WriteData(phy_handle_t *handle, uint16_t data);
static status_t PHY_VSC8541_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData);
static status_t PHY_VSC8541_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phyvsc8541_ops = {.phyInit            = PHY_VSC8541_Init,
                                         .phyWrite           = PHY_VSC8541_Write,
                                         .phyRead            = PHY_VSC8541_Read,
                                         .getAutoNegoStatus  = PHY_VSC8541_GetAutoNegotiationStatus,
                                         .getLinkStatus      = PHY_VSC8541_GetLinkStatus,
                                         .getLinkSpeedDuplex = PHY_VSC8541_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex = PHY_VSC8541_SetLinkSpeedDuplex,
                                         .enableLoopback     = PHY_VSC8541_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_VSC8541_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter = PHY_READID_TIMEOUT_COUNT;
    status_t result;
    uint16_t regValue = 0U;
    uint32_t devId    = 0U;

    handle->phyAddr  = config->phyAddr;
    handle->resource = config->resource;

    /* Check PHY ID. */
    do
    {
        result = PHY_VSC8541_READ(handle, PHY_ID1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        devId = regValue << 16U;

        result = PHY_VSC8541_READ(handle, PHY_ID2_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        devId += regValue;

        counter--;
    } while ((devId != PHY_DEVICE_ID) && (counter != 0U));

    if (counter == 0U)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (config->autoNeg)
    {
        /* Set the auto-negotiation. */
        result = PHY_VSC8541_WRITE(handle, PHY_AUTONEG_ADVERTISE_REG,
                                   PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                                       PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK |
                                       PHY_IEEE802_3_SELECTOR_MASK);
        if (result == kStatus_Success)
        {
            result = PHY_VSC8541_WRITE(handle, PHY_1000BASET_CONTROL_REG, PHY_1000BASET_FULLDUPLEX_MASK);
            if (result == kStatus_Success)
            {
                result = PHY_VSC8541_READ(handle, PHY_BASICCONTROL_REG, &regValue);
                if (result == kStatus_Success)
                {
                    result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG,
                                               (regValue | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
                }
            }
        }
    }
    else
    {
        /* Disable isolate mode */
        result = PHY_VSC8541_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        regValue &= PHY_BCTL_ISOLATE_MASK;
        result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
        result = PHY_VSC8541_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }
    return result;
}

status_t PHY_VSC8541_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return PHY_VSC8541_WRITE(handle, phyReg, data);
}

status_t PHY_VSC8541_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return PHY_VSC8541_READ(handle, phyReg, pData);
}

status_t PHY_VSC8541_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = PHY_VSC8541_READ(handle, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_VSC8541_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    /* Read the basic status register. */
    result = PHY_VSC8541_READ(handle, PHY_BASICSTATUS_REG, &regValue);
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

status_t PHY_VSC8541_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint16_t regValue;

    /* Read the status register. */
    result = PHY_VSC8541_READ(handle, PHY_AUXILIARY_CTRL_STATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            switch ((regValue & PHY_AUXILIARY_CTRL_STATUS_LINKSPEED_MASK) >> PHY_AUXILIARY_CTRL_STATUS_LINKSPEED_SHIFT)
            {
                case (uint16_t)kPHY_Speed10M:
                    *speed = kPHY_Speed10M;
                    break;
                case (uint16_t)kPHY_Speed100M:
                    *speed = kPHY_Speed100M;
                    break;
                case (uint16_t)kPHY_Speed1000M:
                    *speed = kPHY_Speed1000M;
                    break;
                default:
                    *speed = kPHY_Speed10M;
                    break;
            }
        }

        if (duplex != NULL)
        {
            if ((regValue & PHY_AUXILIARY_CTRL_STATUS_LINKDUPLEX_MASK) != 0U)
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

status_t PHY_VSC8541_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    status_t result;
    uint16_t regValue;

    result = PHY_VSC8541_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_VSC8541_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    /* This PHY only supports local loopback. */
    assert(mode == kPHY_LocalLoop);

    status_t result;
    uint16_t regValue;

    /* Set the loop mode. */
    if (enable)
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
        result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    else
    {
        /* First read the current status in control register. */
        result = PHY_VSC8541_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result == kStatus_Success)
        {
            regValue &= ~PHY_BCTL_LOOP_MASK;
            result = PHY_VSC8541_WRITE(handle, PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }
    return result;
}

#if 0
static status_t PHY_VSC8541_MMD_SetDevice(phy_handle_t *handle,
                                          uint8_t device,
                                          uint16_t addr,
                                          phy_mmd_access_mode_t mode)
{
    status_t result = kStatus_Success;

    /* Set Function mode of address access(b00) and device address. */
    result = PHY_VSC8541_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, device);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set register address. */
    result = PHY_VSC8541_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, addr);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set Function mode of data access(b01~11) and device address. */
    result = PHY_VSC8541_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, (uint16_t)mode | (uint16_t)device);
    return result;
}

static inline status_t PHY_VSC8541_MMD_ReadData(phy_handle_t *handle, uint16_t *pData)
{
    return PHY_VSC8541_READ(handle, PHY_MMD_ACCESS_DATA_REG, pData);
}

static inline status_t PHY_VSC8541_MMD_WriteData(phy_handle_t *handle, uint16_t data)
{
    return PHY_VSC8541_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, data);
}

static status_t PHY_VSC8541_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData)
{
    status_t result = kStatus_Success;
    result          = PHY_VSC8541_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_VSC8541_MMD_ReadData(handle, pData);
    }
    return result;
}

static status_t PHY_VSC8541_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data)
{
    status_t result = kStatus_Success;

    result = PHY_VSC8541_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_VSC8541_MMD_WriteData(handle, data);
    }
    return result;
}
#endif
