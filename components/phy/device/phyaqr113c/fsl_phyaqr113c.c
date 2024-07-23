/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyaqr113c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY AQR113C registers. */

/*
 * Auto-Negotiation device registers
 */
#define PHY_MMD_AN_CTRL1_REG      (0x0000U)
#define PHY_MMD_AN_STATUS1_REG    (0x0001U)
#define PHY_MMD_AN_ADV_REG        (0x0010U)
#define PHY_MMD_AN_10GBT_CTRL_REG (0x0020U)
#define PHY_MMD_AN_EEE_ADV_REG    (0x003CU)
#define PHY_MMD_AN_VEND_PROV1_REG (0x400U)

/* Control 1 register */
#define AN_CTRL1_ENABLE_MASK  (0x1000U)
#define AN_CTRL1_RESTART_MASK (0x0200U)

/* Status 1 register */
#define AN_STATUS1_COMPLETE (0x0020U)

/* Advertisement Register */
#define AN_ADV_TECH_ABILITY_ALL (0x0DE0U)

/* 10GBASE-T Control Register */
#define AN_10GBT_CTRL_ADV_ALL (0x11A0U)

/* EEE Advertisement Register */
#define AN_EEE_ADV_100BT_MASK   (0x0002U)
#define AN_EEE_ADV_1000BT_MASK  (0x0004U)
#define AN_EEE_ADV_10GBT_MASK   (0x0008U)
#define AN_EEE_ADV_100BKX_MASK  (0x0008U)
#define AN_EEE_ADV_1000BKX_MASK (0x0010U)
#define AN_EEE_ADV_10GBKX4_MASK (0x0020U)
#define AN_EEE_ADV_10GBKR_MASK  (0x0040U)

/* Vendor Provisioning 1 register */
#define AN_VEND_PROV1_ADV_ALL (0xCC00U)

/*
 * Vendor specific 1 device registers
 */
#define PHY_MMD_VEND1_ID1_REG   (0x2U)
#define PHY_MMD_VEND1_ID2_REG   (0x3U)
#define PHY_MMD_VEND1_FW_ID_REG (0x20)

/* firmware id register */
#define VEND1_FW_ID1 (0x31c3U) /*!< The PHY ID1 . */
#define VEND1_FW_ID2 (0x1c13U) /*!< The PHY ID2 . */

/*
 * PMA/PMD device registers
 */
#define PHY_MMD_PMAPMD_CTRL1_REG   (0x0U)
#define PHY_MMD_PMAPMD_STATUS1_REG (0x1U)
#define PHY_MMD_PMAPMD_CTRL2_REG   (0x7U)

/* control 1 register */
#define CTRL1_LOOPBACK_MASK   (0x0001U)
#define CTRL1_SPEED_SEL_MASK  (0x207CU)
#define CTRL1_SPEED_SEL_10M   (0x0000U)
#define CTRL1_SPEED_SEL_100M  (0x2000U)
#define CTRL1_SPEED_SEL_1000M (0x0040U)
#define CTRL1_SPEED_SEL_2500M (0x2058U)
#define CTRL1_SPEED_SEL_5G    (0x205CU)
#define CTRL1_SPEED_SEL_10G   (0x2040U)

/* status 1 register */
#define STATUS1_LINK_MASK (0x0004U)

/* control 2 register */
#define CTRL2_TYPE_MASK (0x003FU)
#define CTRL2_10GBCX4   (0x0000U) /* 10GBASE-CX4 type */
#define CTRL2_10GBEW    (0x0001U) /* 10GBASE-EW type */
#define CTRL2_10GBLW    (0x0002U) /* 10GBASE-LW type */
#define CTRL2_10GBSW    (0x0003U) /* 10GBASE-SW type */
#define CTRL2_10GBLX4   (0x0004U) /* 10GBASE-LX4 type */
#define CTRL2_10GBER    (0x0005U) /* 10GBASE-ER type */
#define CTRL2_10GBLR    (0x0006U) /* 10GBASE-LR type */
#define CTRL2_10GBSR    (0x0007U) /* 10GBASE-SR type */
#define CTRL2_10GBLRM   (0x0008U) /* 10GBASE-LRM type */
#define CTRL2_10GBT     (0x0009U) /* 10GBASE-T type */
#define CTRL2_10GBKX4   (0x000aU) /* 10GBASE-KX4 type */
#define CTRL2_10GBKR    (0x000bU) /* 10GBASE-KR type */
#define CTRL2_1000BT    (0x000cU) /* 1000BASE-T type */
#define CTRL2_1000BKX   (0x000dU) /* 1000BASE-KX type */
#define CTRL2_100BTX    (0x000eU) /* 100BASE-TX type */
#define CTRL2_10BT      (0x000fU) /* 10BASE-T type */
#define CTRL2_2_5GBT    (0x0030U) /* 2.5GBaseT type */
#define CTRL2_5GBT      (0x0031U) /* 5GBaseT type */

/*
 * PCS device registers
 */
#define PHY_MMD_PCS_CTRL1_REG   (0x0U)
#define PHY_MMD_PCS_STATUS1_REG (0x1U)

/* Control 1 register */
#define PCS_CTRL1_LOOPBACK_MASK (0x4000U)

/* Status 1 register */
#define PCS_STATUS1_LINK_MASK (0x0004U)

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT   1000U
#define PHY_FIRMWARE_TIMEOUT_COUNT 1000U

/*! @brief Defines the PHY resource interface. */
#define PHY_AQR113C_WRITE(handle, devAddr, regAddr, data) \
    ((phy_aqr113c_resource_t *)(handle)->resource)->write((handle)->phyAddr, devAddr, regAddr, data)
#define PHY_AQR113C_READ(handle, devAddr, regAddr, pData) \
    ((phy_aqr113c_resource_t *)(handle)->resource)->read((handle)->phyAddr, devAddr, regAddr, pData)

/*******************************************************************************
 * Variables
 ******************************************************************************/

const phy_operations_t phyaqr113c_ops = {.phyInit             = PHY_AQR113C_Init,
                                         .phyWrite            = NULL,
                                         .phyRead             = NULL,
                                         .phyWriteC45         = PHY_AQR113C_Write,
                                         .phyReadC45          = PHY_AQR113C_Read,
                                         .getAutoNegoStatus   = PHY_AQR113C_GetAutoNegotiationStatus,
                                         .getLinkStatus       = PHY_AQR113C_GetLinkStatus,
                                         .getLinkSpeedDuplex  = PHY_AQR113C_GetLinkSpeedDuplex,
                                         .setLinkSpeedDuplex  = PHY_AQR113C_SetLinkSpeedDuplex,
                                         .enableLoopback      = PHY_AQR113C_EnableLoopback,
                                         .enableLinkInterrupt = NULL,
                                         .clearInterrupt      = NULL};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_AQR113C_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t counter   = PHY_READID_TIMEOUT_COUNT;
    uint16_t regValue1 = 0U;
    uint16_t regValue2 = 0U;
    status_t result;

    /* Assign PHY address and operation resource. */
    handle->phyAddr  = config->phyAddr;
    handle->resource = config->resource;

    /* Check PHY ID. */
    do
    {
        result = PHY_AQR113C_READ(handle, PHY_MMD_VEND1, PHY_MMD_VEND1_ID1_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = PHY_AQR113C_READ(handle, PHY_MMD_VEND1, PHY_MMD_VEND1_ID2_REG, &regValue2);
        if (result != kStatus_Success)
        {
            return result;
        }
        counter--;
    } while (((regValue1 != VEND1_FW_ID1) || (regValue2 != VEND1_FW_ID2)) && (counter != 0U));

    if (counter == 0U)
    {
        return kStatus_Fail;
    }

    /* Poll until firmware loaded */
    counter = PHY_FIRMWARE_TIMEOUT_COUNT;
    do
    {
        result = PHY_AQR113C_READ(handle, PHY_MMD_VEND1, PHY_MMD_VEND1_FW_ID_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }
    } while ((regValue1 == 0x0U) && (counter != 0));

    if (counter == 0U)
    {
        return kStatus_Fail;
    }

    if (config->autoNeg)
    {
        /* EEE */
        if (config->enableEEE)
        {
            regValue1 |=
                (AN_EEE_ADV_100BT_MASK | AN_EEE_ADV_1000BT_MASK | AN_EEE_ADV_10GBT_MASK | AN_EEE_ADV_100BKX_MASK |
                 AN_EEE_ADV_1000BKX_MASK | AN_EEE_ADV_10GBKX4_MASK | AN_EEE_ADV_10GBKR_MASK);
        }
        else
        {
            regValue1 &=
                ~(AN_EEE_ADV_100BT_MASK | AN_EEE_ADV_1000BT_MASK | AN_EEE_ADV_10GBT_MASK | AN_EEE_ADV_100BKX_MASK |
                  AN_EEE_ADV_1000BKX_MASK | AN_EEE_ADV_10GBKX4_MASK | AN_EEE_ADV_10GBKR_MASK);
        }
        result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_EEE_ADV_REG, regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Configure Auto-Negotiation */
        result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_ADV_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_ADV_REG, (regValue1 | AN_ADV_TECH_ABILITY_ALL));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Configure 10G */
        result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_10GBT_CTRL_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_10GBT_CTRL_REG, (regValue1 | AN_10GBT_CTRL_ADV_ALL));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Vendor registers */
        result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_VEND_PROV1_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_VEND_PROV1_REG, (regValue1 | AN_VEND_PROV1_ADV_ALL));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable Auto-Negotiation */
        result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_CTRL1_REG, &regValue1);
        if (result != kStatus_Success)
        {
            return result;
        }

        regValue1 |= (AN_CTRL1_ENABLE_MASK | AN_CTRL1_RESTART_MASK);
        result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_CTRL1_REG, regValue1);
    }
    else
    {
        result = PHY_AQR113C_SetLinkSpeedDuplex(handle, config->speed, config->duplex);
    }

    return result;
}

status_t PHY_AQR113C_Write(phy_handle_t *handle, uint8_t devAddr, uint16_t phyReg, uint16_t data)
{
    return PHY_AQR113C_WRITE(handle, devAddr, phyReg, data);
}

status_t PHY_AQR113C_Read(phy_handle_t *handle, uint8_t devAddr, uint16_t phyReg, uint16_t *pData)
{
    return PHY_AQR113C_READ(handle, devAddr, phyReg, pData);
}

status_t PHY_AQR113C_GetAutoNegotiationStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_STATUS1_REG, &regValue);
    if (result == kStatus_Success)
    {
        if ((AN_STATUS1_COMPLETE & regValue) != 0U)
        {
            *status = true;
        }
        else
        {
            *status = false;
        }
    }
    return result;
}

status_t PHY_AQR113C_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result;
    uint16_t regValue;

    result = PHY_AQR113C_READ(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_STATUS1_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* back-to-back read */
    if ((STATUS1_LINK_MASK & regValue) == 0x0U)
    {
        result = PHY_AQR113C_READ(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_STATUS1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    if ((STATUS1_LINK_MASK & regValue) != 0U)
    {
        /* Link up. */
        *status = true;
        return result;
    }

    /* If no link, also read PCS device */
    result = PHY_AQR113C_READ(handle, PHY_MMD_PCS, PHY_MMD_PCS_STATUS1_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* back-to-back read */
    if ((PCS_STATUS1_LINK_MASK & regValue) == 0x0U)
    {
        result = PHY_AQR113C_READ(handle, PHY_MMD_PCS, PHY_MMD_PCS_STATUS1_REG, &regValue);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    if ((PCS_STATUS1_LINK_MASK & regValue) != 0U)
    {
        /* Link up. */
        *status = true;
    }
    else
    {
        /* Link down. */
        *status = false;
    }

    return result;
}

status_t PHY_AQR113C_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint16_t regValue;

    result = PHY_AQR113C_READ(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_CTRL1_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    switch (regValue & CTRL1_SPEED_SEL_MASK)
    {
        case CTRL1_SPEED_SEL_10M:
            *speed = kPHY_Speed10M;
            break;
        case CTRL1_SPEED_SEL_100M:
            *speed = kPHY_Speed100M;
            break;
        case CTRL1_SPEED_SEL_1000M:
            *speed = kPHY_Speed1000M;
            break;
        case CTRL1_SPEED_SEL_2500M:
            *speed = kPHY_Speed2500M;
            break;
        case CTRL1_SPEED_SEL_5G:
            *speed = kPHY_Speed5G;
            break;
        case CTRL1_SPEED_SEL_10G:
            *speed = kPHY_Speed10G;
            break;
        default:
            *speed = kPHY_Speed10M;
            break;
    }

    *duplex = kPHY_FullDuplex;
    return result;
}

status_t PHY_AQR113C_SetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t speed, phy_duplex_t duplex)
{
    status_t result;
    uint16_t regValue1;
    uint16_t regValue2;

    /* Half duplex not supported */
    if (duplex == kPHY_HalfDuplex)
    {
        return kStatus_Fail;
    }

    /* Set speed */
    result = PHY_AQR113C_READ(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_CTRL1_REG, &regValue1);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = PHY_AQR113C_READ(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_CTRL2_REG, &regValue2);
    if (result != kStatus_Success)
    {
        return result;
    }

    regValue1 &= ~CTRL1_SPEED_SEL_MASK;
    regValue2 &= ~CTRL2_TYPE_MASK;

    switch (speed)
    {
        case kPHY_Speed10M:
            regValue1 |= CTRL1_SPEED_SEL_10M;
            regValue2 |= CTRL2_10BT;
            break;
        case kPHY_Speed100M:
            regValue1 |= CTRL1_SPEED_SEL_100M;
            regValue2 |= CTRL2_100BTX;
            break;
        case kPHY_Speed1000M:
            regValue1 |= CTRL1_SPEED_SEL_1000M;
            regValue2 |= CTRL2_1000BT;
            break;
        case kPHY_Speed2500M:
            regValue1 |= CTRL1_SPEED_SEL_2500M;
            regValue2 |= CTRL2_2_5GBT;
            break;
        case kPHY_Speed5G:
            regValue1 |= CTRL1_SPEED_SEL_5G;
            regValue2 |= CTRL2_5GBT;
            break;
        case kPHY_Speed10G:
            regValue1 |= CTRL1_SPEED_SEL_10G;
            regValue2 |= CTRL2_10GBT;
            break;
        default:
            regValue1 |= CTRL1_SPEED_SEL_10M;
            regValue2 |= CTRL2_10BT;
            break;
    }

    result = PHY_AQR113C_WRITE(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_CTRL1_REG, regValue1);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = PHY_AQR113C_WRITE(handle, PHY_MMD_PMAPMD, PHY_MMD_PMAPMD_CTRL2_REG, regValue2);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Disable Autonegotiation */
    result = PHY_AQR113C_READ(handle, PHY_MMD_AN, PHY_MMD_AN_CTRL1_REG, &regValue1);
    if (result != kStatus_Success)
    {
        return result;
    }

    regValue1 &= ~(AN_CTRL1_ENABLE_MASK | AN_CTRL1_RESTART_MASK);

    result = PHY_AQR113C_WRITE(handle, PHY_MMD_AN, PHY_MMD_AN_CTRL1_REG, regValue1);

    return result;
}

status_t PHY_AQR113C_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint16_t regValue;

    result = PHY_AQR113C_READ(handle, PHY_MMD_PCS, PHY_MMD_PCS_CTRL1_REG, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (enable)
    {
        regValue |= PCS_CTRL1_LOOPBACK_MASK;
    }
    else
    {
        regValue &= ~PCS_CTRL1_LOOPBACK_MASK;
    }

    result = PHY_AQR113C_WRITE(handle, PHY_MMD_PCS, PHY_MMD_PCS_CTRL1_REG, regValue);
    return result;
}
