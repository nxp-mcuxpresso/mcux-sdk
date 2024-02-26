/*
 * Copyright 2020-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyrtl8211f.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY RTL8211F vendor defined registers. */
#define PHY_SPECIFIC_STATUS_REG (0x1AU) /*!< The PHY specific status register. */
#define PHY_PAGE_SELECT_REG     (0x1FU) /*!< The PHY page select register. */

/*! @brief Defines the PHY RTL8211F ID number. */
#define PHY_CONTROL_ID1 (0x001CU) /*!< The PHY ID1 . */

/*! @brief Defines the mask flag in interrupt enable register. */
#define PHY_INER_LINKSTATUS_CHANGE_MASK ((uint16_t)0x0010U) /*!< The PHY link status change interrupt mask. */

/*! @brief Defines the mask flag in specific status register. */
#define PHY_SSTATUS_LINKSTATUS_MASK ((uint16_t)0x0004U) /*!< The PHY link status mask. */
#define PHY_SSTATUS_LINKSPEED_MASK  ((uint16_t)0x0030U) /*!< The PHY link speed mask. */
#define PHY_SSTATUS_LINKDUPLEX_MASK ((uint16_t)0x0008U) /*!< The PHY link duplex mask. */
#define PHY_SSTATUS_LINKSPEED_SHIFT (4U)                /*!< The link speed shift */

/*! @brief Defines the PHY RTL8211F extra page and the registers in specified page. */
#define PHY_PAGE_RGMII_TXRX_DELAY_ADDR (0xD08U) /*!< The register page including RGMII TX/RX delay setting. */
#define PHY_RGMII_TX_DELAY_REG         (0x11U)  /*!< The RGMII TXC delay register. */
#define PHY_RGMII_RX_DELAY_REG         (0x15U)  /*!< The RGMII RXC delay register. */
#define PHY_RGMII_TX_DELAY_MASK        ((uint16_t)0x0100U) /*!< The RGMII TXC delay mask. */
#define PHY_RGMII_RX_DELAY_MASK        ((uint16_t)0x0008U) /*!< The RGMII RXC delay mask. */

#define PHY_PAGE_INTR_PIN_ADDR (0xD40U)            /*!< The register page including PHY interrupt pin setting. */
#define PHY_PAGE_INTR_PIN_REG  (0x16U)             /*!< The PHY interrupt pin setting register. */
#define PHY_PAGE_INTR_PIN_MASK ((uint16_t)0x0020U) /*!< The PHY interrupt pin setting mask. */

#define PHY_PAGE_INTR_ADDR (0xA42U)                /*!< The register page including interrupt control setting. */
#define PHY_INER_REG       (0x12U)                 /*!< The PHY interrupt enable register. */
#define PHY_INSR_REG       (0x1DU)                 /*!< The PHY interrupt status register. */

/*! @brief MDIO MMD Devices .*/
#define PHY_MDIO_MMD_PCS 3U
#define PHY_MDIO_MMD_AN  7U

/*! @brief MDIO MMD Physical Coding layer device registers .*/
#define PHY_MDIO_PCS_EEE_CAP 0x14U /*!< EEE capability */

/*! @brief MDIO MMD AutoNegotiation device registers .*/
#define PHY_MDIO_AN_EEE_ADV 0x3CU /*!< EEE advertisement */

/*! @brief MDIO MMD EEE mask flags. (common for adv and cap) */
#define PHY_MDIO_EEE_100TX 0x2U
#define PHY_MDIO_EEE_1000T 0x4U

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/*! @brief Defines the PHY resource interface. */
#define PHY_RTL8211F_WRITE(handle, regAddr, data) \
    ((phy_rtl8211f_resource_t *)(handle)->resource)->write((handle)->phyAddr, regAddr, data)
#define PHY_RTL8211F_READ(handle, regAddr, pData) \
    ((phy_rtl8211f_resource_t *)(handle)->resource)->read((handle)->phyAddr, regAddr, pData)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static status_t PHY_RTL8211F_MMD_SetDevice(phy_handle_t *handle,
                                           uint8_t device,
                                           uint16_t addr,
                                           phy_mmd_access_mode_t mode);
static inline status_t PHY_RTL8211F_MMD_ReadData(phy_handle_t *handle, uint16_t *pData);
static inline status_t PHY_RTL8211F_MMD_WriteData(phy_handle_t *handle, uint16_t data);
static status_t PHY_RTL8211F_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData);
static status_t PHY_RTL8211F_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data);

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phyrtl8211f_ops = {.phyInit             = PHY_RTL8211F_Init,
                                          .phyWrite            = PHY_RTL8211F_Write,
                                          .phyRead             = PHY_RTL8211F_Read,
                                          .getAutoNegoStatus   = PHY_RTL8211F_GetAutoNegotiationStatus,
                                          .getLinkStatus       = PHY_RTL8211F_GetLinkStatus,
                                          .getLinkSpeedDuplex  = PHY_RTL8211F_GetLinkSpeedDuplex,
                                          .setLinkSpeedDuplex  = PHY_RTL8211F_SetLinkSpeedDuplex,
                                          .enableLoopback      = PHY_RTL8211F_EnableLoopback,
                                          .enableLinkInterrupt = PHY_RTL8211F_EnableLinkInterrupt,
                                          .clearInterrupt      = PHY_RTL8211F_ClearInterrupt};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_RTL8211F_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter  = PHY_READID_TIMEOUT_COUNT;
    uint16_t regValue = 0U;
    status_t result;

    /* Assign PHY address and operation resource. */
    handle->phyAddr  = config->phyAddr;
    handle->resource = config->resource;

    /* Check PHY ID. */
    do
    {
        result = PHY_RTL8211F_READ(handle, PHY_ID1_REG, &regValue);
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
    result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != kStatus_Success)
    {
        return result;
    }

    do
    {
        result = PHY_RTL8211F_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    } while ((regValue & PHY_BCTL_RESET_MASK) != 0U);

    /* The RGMII specifies output TXC/RXC and TXD/RXD without any clock skew. Need to add skew on clock line
       to make sure the other side sample right data. This can also be done in PCB traces. */
    result = PHY_RTL8211F_WRITE(handle, PHY_PAGE_SELECT_REG, PHY_PAGE_RGMII_TXRX_DELAY_ADDR);
    if (result != kStatus_Success)
    {
        return result;
    }
    /* Set Tx Delay. */
    result = PHY_RTL8211F_READ(handle, PHY_RGMII_TX_DELAY_REG, &regValue);
    if (result == kStatus_Success)
    {
        regValue |= PHY_RGMII_TX_DELAY_MASK;
        result = PHY_RTL8211F_WRITE(handle, PHY_RGMII_TX_DELAY_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    }
    else
    {
        return result;
    }

    /* Set Rx Delay. */
    result = PHY_RTL8211F_READ(handle, PHY_RGMII_RX_DELAY_REG, &regValue);
    if (result == kStatus_Success)
    {
        regValue |= PHY_RGMII_RX_DELAY_MASK;
        result = PHY_RTL8211F_WRITE(handle, PHY_RGMII_RX_DELAY_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    }
    else
    {
        return result;
    }
    /* Restore to default page 0 */
    result = PHY_RTL8211F_WRITE(handle, PHY_PAGE_SELECT_REG, 0x0);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Energy Efficient Ethernet configuration */
    if (config->enableEEE)
    {
        /* Get capabilities */
        result = PHY_RTL8211F_MMD_Read(handle, PHY_MDIO_MMD_PCS, PHY_MDIO_PCS_EEE_CAP, &regValue);
        if (result == kStatus_Success)
        {
            /* Enable EEE for 100TX and 1000T */
            result = PHY_RTL8211F_MMD_Write(handle, PHY_MDIO_MMD_AN, PHY_MDIO_AN_EEE_ADV,
                                            regValue & (PHY_MDIO_EEE_1000T | PHY_MDIO_EEE_100TX));
        }
    }
    else
    {
        result = PHY_RTL8211F_MMD_Write(handle, PHY_MDIO_MMD_AN, PHY_MDIO_AN_EEE_ADV, 0);
    }
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set INT pin as interrupt mode. */
    result = PHY_RTL8211F_WRITE(handle, PHY_PAGE_SELECT_REG, PHY_PAGE_INTR_PIN_ADDR);
    if (result != kStatus_Success)
    {
        return result;
    }
    result = PHY_RTL8211F_READ(handle, PHY_PAGE_INTR_PIN_REG, &regValue);
    if (result == kStatus_Success)
    {
        regValue &= ~PHY_PAGE_INTR_PIN_MASK;
        result = PHY_RTL8211F_WRITE(handle, PHY_PAGE_INTR_PIN_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    }
    else
    {
        return result;
    }
    /* Restore to default page 0 */
    result = PHY_RTL8211F_WRITE(handle, PHY_PAGE_SELECT_REG, 0);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = PHY_RTL8211F_ClearInterrupt(handle);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (config->autoNeg)
    {
        /* Set the auto-negotiation. */
        result = PHY_RTL8211F_WRITE(handle, PHY_AUTONEG_ADVERTISE_REG,
                                    PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                                        PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK |
                                        PHY_IEEE802_3_SELECTOR_MASK);
        if (result == kStatus_Success)
        {
            result = PHY_RTL8211F_WRITE(handle, PHY_1000BASET_CONTROL_REG, PHY_1000BASET_FULLDUPLEX_MASK);
            if (result == kStatus_Success)
            {
                result = PHY_RTL8211F_READ(handle, PHY_BASICCONTROL_REG, &regValue);
                if (result == kStatus_Success)
                {
                    result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG,
                                                (regValue | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
                }
            }
        }
    }
    else
    {
        /* Disable isolate mode */
        result = PHY_RTL8211F_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
        regValue &= ~PHY_BCTL_ISOLATE_MASK;
        result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Disable the auto-negotiation and set user-defined speed/duplex configuration. */
        result = PHY_RTL8211F_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }
    if (result != kStatus_Success)
    {
        return result;
    }

    result = PHY_RTL8211F_EnableLinkInterrupt(handle, config->intrType);

    return result;
}

status_t PHY_RTL8211F_Write(phy_handle_t *handle, uint8_t phyReg, uint16_t data)
{
    return PHY_RTL8211F_WRITE(handle, phyReg, data);
}

status_t PHY_RTL8211F_Read(phy_handle_t *handle, uint8_t phyReg, uint16_t *pData)
{
    return PHY_RTL8211F_READ(handle, phyReg, pData);
}

status_t PHY_RTL8211F_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    *status = false;

    /* Check auto negotiation complete. */
    result = PHY_RTL8211F_READ(handle, PHY_BASICSTATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((regValue & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0U)
        {
            *status = true;
        }
    }
    return result;
}

status_t PHY_RTL8211F_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    /* Read the basic status register. */
    result = PHY_RTL8211F_READ(handle, PHY_SPECIFIC_STATUS_REG, &regValue);
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

status_t PHY_RTL8211F_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint16_t regValue;

    /* Read the status register. */
    result = PHY_RTL8211F_READ(handle, PHY_SPECIFIC_STATUS_REG, &regValue);
    if (result == kStatus_Success)
    {
        if (speed != NULL)
        {
            switch ((regValue & PHY_SSTATUS_LINKSPEED_MASK) >> PHY_SSTATUS_LINKSPEED_SHIFT)
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

status_t PHY_RTL8211F_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    status_t result;
    uint16_t regValue;

    result = PHY_RTL8211F_READ(handle, PHY_BASICCONTROL_REG, &regValue);
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
        result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    return result;
}

status_t PHY_RTL8211F_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
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
        result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG, regValue);
    }
    else
    {
        /* First read the current status in control register. */
        result = PHY_RTL8211F_READ(handle, PHY_BASICCONTROL_REG, &regValue);
        if (result == kStatus_Success)
        {
            regValue &= ~PHY_BCTL_LOOP_MASK;
            result = PHY_RTL8211F_WRITE(handle, PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }
    return result;
}

status_t PHY_RTL8211F_EnableLinkInterrupt(phy_handle_t *handle, phy_interrupt_type_t type)
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
    result = PHY_RTL8211F_READ(handle, PHY_INER_REG, &regValue);
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
    result = PHY_RTL8211F_WRITE(handle, PHY_INER_REG, regValue);
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

status_t PHY_RTL8211F_ClearInterrupt(phy_handle_t *handle)
{
    uint16_t regValue;

    /* Found both read reg 0x1D from page 0 or page 0xA42 are useful. But datasheet
       describes it's in page 0xA42. Here use simpler implementation. */
    return PHY_RTL8211F_READ(handle, PHY_INSR_REG, &regValue);
}

static status_t PHY_RTL8211F_MMD_SetDevice(phy_handle_t *handle,
                                           uint8_t device,
                                           uint16_t addr,
                                           phy_mmd_access_mode_t mode)
{
    status_t result = kStatus_Success;

    /* Set Function mode of address access(b00) and device address. */
    result = PHY_RTL8211F_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, device);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set register address. */
    result = PHY_RTL8211F_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, addr);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set Function mode of data access(b01~11) and device address. */
    result = PHY_RTL8211F_WRITE(handle, PHY_MMD_ACCESS_CONTROL_REG, (uint16_t)mode | (uint16_t)device);
    return result;
}

static inline status_t PHY_RTL8211F_MMD_ReadData(phy_handle_t *handle, uint16_t *pData)
{
    return PHY_RTL8211F_READ(handle, PHY_MMD_ACCESS_DATA_REG, pData);
}

static inline status_t PHY_RTL8211F_MMD_WriteData(phy_handle_t *handle, uint16_t data)
{
    return PHY_RTL8211F_WRITE(handle, PHY_MMD_ACCESS_DATA_REG, data);
}

static status_t PHY_RTL8211F_MMD_Read(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t *pData)
{
    status_t result = kStatus_Success;
    result          = PHY_RTL8211F_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_RTL8211F_MMD_ReadData(handle, pData);
    }
    return result;
}

static status_t PHY_RTL8211F_MMD_Write(phy_handle_t *handle, uint8_t device, uint16_t addr, uint16_t data)
{
    status_t result = kStatus_Success;

    result = PHY_RTL8211F_MMD_SetDevice(handle, device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == kStatus_Success)
    {
        result = PHY_RTL8211F_MMD_WriteData(handle, data);
    }
    return result;
}
