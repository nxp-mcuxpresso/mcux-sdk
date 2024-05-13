/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyrtl8201.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the PHY RTL8201 device ID information. */
#define PHY_OUI                 0x732U /*!< The PHY organizationally unique identifier. */
#define PHY_MODEL_NUM           0x1U   /*!< The PHY organizationally unique identifier. */
#define PHY_DEVICE_REVISION_NUM 0x6U   /*!< The PHY organizationally unique identifier. */
#define PHY_DEVICE_ID           ((PHY_OUI << 10U) | (PHY_MODEL_NUM << 4U) | (PHY_DEVICE_REVISION_NUM))

/*! @brief Defines the PHY RTL8201 registers. */
#define PHY_INSR_REG        (30U)
#define PHY_PAGE_SELECT_REG (31U)
#define PHY_PAGE_INTR_ADDR  (7U)
#define PHY_INER_REG        (19U)

#define PHY_INER_LINKSTATUS_CHANGE_MASK ((uint16_t)1U << 13)

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/*! @brief Defines the PHY resource interface. */
#define PHY_RTL8201_WRITE(handle, regAddr, data) \
    ((phy_rtl8201_resource_t *)(handle)->resource)->write((handle)->phyAddr, regAddr, data)
#define PHY_RTL8201_READ(handle, regAddr, pData) \
    ((phy_rtl8201_resource_t *)(handle)->resource)->read((handle)->phyAddr, regAddr, pData)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if 0
static status_t PHY_RTL8201_MMD_SetDevice(phy_handle_t *handle,
                                          uint8_t device,
                                          uint16_t addr,
                                          phy_mmd_access_mode_t mode);
static inline status_t PHY_RTL8201_MMD_ReadData(phy_handle_t *handle, uint16_t *pData);
static inline status_t PHY_RTL8201_MMD_WriteData(phy_handle_t *handle, uint16_t data);
static status_t PHY_RTL8201_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData);
static status_t PHY_RTL8201_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phyrtl8201_ops = {.phyInit             = PHY_RTL8201_Init,
                                         .phyWrite            = PHY_RTL8201_Write,
                                         .phyRead             = PHY_RTL8201_Read,
                                         .getAutoNegoStatus   = PHY_RTL8201_GetAutoNegotiationStatus,
                                         .getLinkStatus       = PHY_RTL8201_GetLinkStatus,
                                         .getLinkSpeedDuplex  = PHY_RTL8201_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex  = PHY_RTL8201_SetLinkSpeedDuplex,
                                         .enableLoopback      = PHY_RTL8201_EnableLoopback,
                                         .enableLinkInterrupt = PHY_RTL8201_EnableLinkInterrupt,
                                         .clearInterrupt      = PHY_RTL8201_ClearInterrupt};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_RTL8201_Init(phy_handle_t *handle, const phy_config_t *config)
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
        result = PHY_RTL8201_READ(handle, PHY_ID1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        devId = (uint32_t)regValue << 16U;

        result = PHY_RTL8201_READ(handle, PHY_ID2_REG, &regValue);
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
    result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != kStatus_Success)
    {
        return result;
    }

    do
    {
        result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    } while ((regValue & PHY_BCTL_RESET_MASK) != 0U);

    result = PHY_RTL8201_EnableLinkInterrupt(handle, config->intrType);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (config->autoNeg)
    {
        /* Set the auto-negotiation. */
        result = PHY_RTL8201_WRITE(handle, PHY_AUTONEG_ADVERTISE_REG,
                                   PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                                       PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK |
                                       PHY_IEEE802_3_SELECTOR_MASK);
        if (result == kStatus_Success)
        {
            result = PHY_RTL8201_WRITE(handle, PHY_1000BASET_CONTROL_REG, PHY_1000BASET_FULLDUPLEX_MASK);
            if (result == kStatus_Success)
            {
                result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
                if (result == kStatus_Success)
                {
                    result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG,
                                               (regValue | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
                }
            }
        }
    }
    else
    {
        /* Disable isolate mode */
        result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        regValue &= ~PHY_BCTL_ISOLATE_MASK;
        result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
        result = PHY_RTL8201_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }
    return result;
}

status_t PHY_RTL8201_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return PHY_RTL8201_WRITE(handle, phyReg, data);
}

status_t PHY_RTL8201_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return PHY_RTL8201_READ(handle, phyReg, pData);
}

status_t PHY_RTL8201_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = PHY_RTL8201_READ(handle, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_RTL8201_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    /* Datasheet: This bit indicates whether the link was lost since the last read.
     * For the current link status, read this register twice. */
    result = PHY_RTL8201_READ(handle, PHY_BASICSTATUS_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }
    result = PHY_RTL8201_READ(handle, PHY_BASICSTATUS_REG, &regValue);
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

status_t PHY_RTL8201_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint16_t regValue;

    /* Read the status register. */
    result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            if ((regValue & PHY_BCTL_SPEED0_MASK) != 0U)
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
            if ((regValue & PHY_BCTL_DUPLEX_MASK) != 0U)
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

status_t PHY_RTL8201_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    status_t result;
    uint16_t regValue;

    result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_RTL8201_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
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
        result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    else
    {
        /* First read the current status in control register. */
        result = PHY_RTL8201_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result == kStatus_Success)
        {
            regValue &= ~PHY_BCTL_LOOP_MASK;
            result = PHY_RTL8201_WRITE(handle, PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }
    return result;
}

status_t PHY_RTL8201_EnableLinkInterrupt(phy_handle_t *handle, phy_interrupt_type_t type)
{
    assert(type != kPHY_IntrActiveHigh);

    status_t result;
    uint16_t regValue;

    result = PHY_Write(handle, PHY_PAGE_SELECT_REG, PHY_PAGE_INTR_ADDR);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Read operation will clear pending interrupt before enable interrupt. */
    result = PHY_RTL8201_READ(handle, PHY_INER_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Enable/Disable link up+down interrupt. */
    if (type != kPHY_IntrDisable)
    {
        regValue |= PHY_INER_LINKSTATUS_CHANGE_MASK;
    }
    else
    {
        regValue &= ~PHY_INER_LINKSTATUS_CHANGE_MASK;
    }
    result = PHY_RTL8201_WRITE(handle, PHY_INER_REG, regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Restore to default page 0 */
    result = PHY_Write(handle, PHY_PAGE_SELECT_REG, 0);
    if (result != kStatus_Success)
    {
        return result;
    }

    return result;
}

status_t PHY_RTL8201_ClearInterrupt(phy_handle_t *handle)
{
    uint16_t regValue;

    return PHY_RTL8201_READ(handle, PHY_INSR_REG, &regValue);
}

#if 0
static status_t PHY_RTL8201_MMD_SetDevice(phy_handle_t *handle,
                                          uint8_t device,
                                          uint16_t addr,
                                          phy_mmd_access_mode_t mode)
{
    status_t result = kStatus_Success;

    /* Set Function mode of address access(b00) and device address. */
    result = PHY_RTL8201_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, device);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set register address. */
    result = PHY_RTL8201_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, addr);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set Function mode of data access(b01~11) and device address. */
    result = PHY_RTL8201_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, (uint16_t)mode | (uint16_t)device);
    return result;
}

static inline status_t PHY_RTL8201_MMD_ReadData(phy_handle_t *handle, uint16_t *pData)
{
    return PHY_RTL8201_READ(handle, PHY_MMD_ACCESS_DATA_REG, pData);
}

static inline status_t PHY_RTL8201_MMD_WriteData(phy_handle_t *handle, uint16_t data)
{
    return PHY_RTL8201_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, data);
}

static status_t PHY_RTL8201_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData)
{
    status_t result = kStatus_Success;
    result          = PHY_RTL8201_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_RTL8201_MMD_ReadData(handle, pData);
    }
    return result;
}

static status_t PHY_RTL8201_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data)
{
    status_t result = kStatus_Success;

    result = PHY_RTL8201_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_RTL8201_MMD_WriteData(handle, data);
    }
    return result;
}
#endif
