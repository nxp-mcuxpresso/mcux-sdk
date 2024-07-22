/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_mdio.h"

/*! @brief MDC standard frequency. */
#define NETC_MDC_FREQUENCY (2500000U)

/*! @brief MDC frequency max clock divisor. */
#define NETC_MDIO_CLK_MAX_DIV_FIELD (0x1FFU)

/*! @brief MDIO hold time in nanosecond. */
#define NETC_MDIO_HOLD_TIME_NS_MIN (10U)

/*! @brief Pointers to netc function bases for each instance. */
static ENETC_PCI_TYPE0_Type *const s_netcFuncBases[] = ENETC_PCI_TYPE0_BASE_PTRS;

/*! @brief Pointers to eth link bases for each instance. */
static NETC_ETH_LINK_Type *const s_netcEthLinkBases[] = NETC_ETH_LINK_BASE_PTRS;

static netc_mdio_hw_t *NETC_MDIOGetOpBase(netc_mdio_handle_t *handle)
{
    if (handle->mdio.type == kNETC_EMdio)
    {
        return (netc_mdio_hw_t *)(uintptr_t)&EMDIO_BASE->EMDIO_CFG;
    }
    else
    {
        return (netc_mdio_hw_t *)(uintptr_t)&s_netcEthLinkBases[handle->mdio.port]->PEMDIOCR;
    }
}

/*
 * Port external MDIO Access functions
 */

static status_t NETC_PEMDIO_Init(netc_mdio_hw_t *base, netc_mdio_config_t *mdioConfig)
{
    bool eHold = false;
    uint32_t holdCycle;
    uint32_t mdioHold;
    uint32_t config;
    uint32_t div;

    /* Set the divisor MDC. */
    div = mdioConfig->srcClockHz / NETC_MDC_FREQUENCY / 2U;
    if (div > NETC_MDIO_CLK_MAX_DIV_FIELD)
    {
        return kStatus_Fail;
    }

    /* A hold time of 10ns is required. */
    holdCycle = (NETC_MDIO_HOLD_TIME_NS_MIN + NETC_NANOSECOND_ONE_SECOND / mdioConfig->srcClockHz - 1U) /
                (NETC_NANOSECOND_ONE_SECOND / mdioConfig->srcClockHz);

    if ((holdCycle > 57U) || (holdCycle == 0U))
    {
        return kStatus_Fail;
    }
    else if (holdCycle > 15U)
    {
        eHold    = true;
        mdioHold = (holdCycle - 2U) / 8U + 1U;
    }
    else
    {
        mdioHold = holdCycle / 2U;
    }

    config = ENETC_PF_EMDIO_EMDIO_CFG_NEG(mdioConfig->isNegativeDriven) | ENETC_PF_EMDIO_EMDIO_CFG_MDIO_CLK_DIV(div) |
             ENETC_PF_EMDIO_EMDIO_CFG_PRE_DIS(mdioConfig->isPreambleDisable) |
             ENETC_PF_EMDIO_EMDIO_CFG_MDIO_HOLD(mdioHold) | ENETC_PF_EMDIO_EMDIO_CFG_EHOLD(eHold);
    base->EMDIO_CFG = config;

    return kStatus_Success;
}

static bool NETC_PEMDIO_IsSMIBusy(netc_mdio_hw_t *base)
{
    return ((base->EMDIO_CFG & ENETC_PF_EMDIO_EMDIO_CFG_BSY1_MASK) != 0U) ? true : false;
}

static bool NETC_PEMDIO_IsPhyAddrErr(netc_mdio_hw_t *base)
{
    return ((base->EMDIO_CFG & ENETC_PF_EMDIO_EMDIO_CFG_ADDR_ERR_MASK) != 0U);
}

static bool NETC_PEMDIO_IsReadErr(netc_mdio_hw_t *base)
{
    return ((base->EMDIO_CFG & ENETC_PF_EMDIO_EMDIO_CFG_MDIO_RD_ER_MASK) != 0U);
}

static status_t NETC_PEMDIO_Write(netc_mdio_hw_t *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    status_t result = kStatus_Success;

    base->EMDIO_CFG &= ~ENETC_PF_EMDIO_EMDIO_CFG_ENC45_MASK;
    base->EMDIO_CTL  = ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(phyAddr) | ENETC_PF_EMDIO_EMDIO_CTL_DEV_ADDR(regAddr);
    base->EMDIO_DATA = data;

    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    if (NETC_PEMDIO_IsPhyAddrErr(base))
    {
        result = kStatus_Fail;
    }

    return result;
}

static status_t NETC_PEMDIO_Read(netc_mdio_hw_t *base, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    status_t result = kStatus_Success;

    base->EMDIO_CFG &= ~ENETC_PF_EMDIO_EMDIO_CFG_ENC45_MASK;
    base->EMDIO_CTL = ENETC_PF_EMDIO_EMDIO_CTL_READ_MASK | ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(phyAddr) |
                      ENETC_PF_EMDIO_EMDIO_CTL_DEV_ADDR(regAddr);

    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    if (NETC_PEMDIO_IsReadErr(base) || NETC_PEMDIO_IsPhyAddrErr(base))
    {
        result = kStatus_Fail;
    }
    *pData = (uint16_t)base->EMDIO_DATA;

    return result;
}

static status_t NETC_PEMDIO_C45Write(
    netc_mdio_hw_t *base, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t data)
{
    base->EMDIO_CFG |= ENETC_PF_EMDIO_EMDIO_CFG_ENC45_MASK;
    base->EMDIO_CTL  = ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(portAddr) | ENETC_PF_EMDIO_EMDIO_CTL_DEV_ADDR(devAddr);
    base->EMDIO_ADDR = ENETC_PF_EMDIO_EMDIO_ADDR_REGADDR(regAddr);

    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    if (NETC_PEMDIO_IsPhyAddrErr(base))
    {
        return kStatus_Fail;
    }

    base->EMDIO_DATA = data;
    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    return kStatus_Success;
}

static status_t NETC_PEMDIO_C45Read(
    netc_mdio_hw_t *base, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t *pData)
{
    base->EMDIO_CFG |= ENETC_PF_EMDIO_EMDIO_CFG_ENC45_MASK;
    base->EMDIO_CTL  = ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(portAddr) | ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(devAddr);
    base->EMDIO_ADDR = ENETC_PF_EMDIO_EMDIO_ADDR_REGADDR(regAddr);
    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    if (NETC_PEMDIO_IsPhyAddrErr(base))
    {
        return kStatus_Fail;
    }

    base->EMDIO_CTL = ENETC_PF_EMDIO_EMDIO_CTL_READ_MASK | ENETC_PF_EMDIO_EMDIO_CTL_PORT_ADDR(portAddr) |
                      ENETC_PF_EMDIO_EMDIO_CTL_DEV_ADDR(devAddr);
    while (NETC_PEMDIO_IsSMIBusy(base))
    {
    }

    if (NETC_PEMDIO_IsReadErr(base))
    {
        return kStatus_Fail;
    }

    *pData = (uint16_t)base->EMDIO_DATA;
    return kStatus_Success;
}

/*
 * Port internal MDIO Access functions
 */

static status_t NETC_PIMDIO_Init(NETC_ETH_LINK_Type *base, netc_mdio_config_t *mdioConfig)
{
    uint32_t holdCycle;
    uint32_t mdioHold;
    uint32_t div;

    /* Set the divisor MDC. */
    div = mdioConfig->srcClockHz / NETC_MDC_FREQUENCY / 2U;
    if (div > NETC_MDIO_CLK_MAX_DIV_FIELD)
    {
        return kStatus_Fail;
    }

    /* A hold time of 10ns is required. */
    holdCycle = (NETC_MDIO_HOLD_TIME_NS_MIN + NETC_NANOSECOND_ONE_SECOND / mdioConfig->srcClockHz - 1U) /
                (NETC_NANOSECOND_ONE_SECOND / mdioConfig->srcClockHz);

    if ((holdCycle > 15U) || (holdCycle == 0U))
    {
        return kStatus_Fail;
    }
    else
    {
        mdioHold = holdCycle / 2U;
    }

    base->PM0_MDIO_CFG = NETC_ETH_LINK_PM0_MDIO_CFG_MDIO_CLK_DIV(div) |
                         NETC_ETH_LINK_PM0_MDIO_CFG_PRE_DIS(mdioConfig->isPreambleDisable) |
                         NETC_ETH_LINK_PM0_MDIO_CFG_MDIO_HOLD(mdioHold);

    return kStatus_Success;
}

static bool NETC_PIMDIO_IsSMIBusy(NETC_ETH_LINK_Type *base)
{
    return ((base->PM0_MDIO_CTL & NETC_ETH_LINK_PM0_MDIO_CTL_BSY_MASK) != 0U) ? true : false;
}

static void NETC_PIMDIO_Write(NETC_ETH_LINK_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    base->PM0_MDIO_CFG &= ~NETC_ETH_LINK_PM0_MDIO_CFG_ENC45_MASK;
    base->PM0_MDIO_CTL  = NETC_ETH_LINK_PM0_MDIO_CTL_PORT_ADDR(phyAddr) | NETC_ETH_LINK_PM0_MDIO_CTL_DEV_ADDR(regAddr);
    base->PM0_MDIO_DATA = data;
    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }
}

static void NETC_PIMDIO_Read(NETC_ETH_LINK_Type *base, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    base->PM0_MDIO_CFG &= ~NETC_ETH_LINK_PM0_MDIO_CFG_ENC45_MASK;
    base->PM0_MDIO_CTL = NETC_ETH_LINK_PM0_MDIO_CTL_READ_MASK | NETC_ETH_LINK_PM0_MDIO_CTL_PORT_ADDR(phyAddr) |
                         NETC_ETH_LINK_PM0_MDIO_CTL_DEV_ADDR(regAddr);
    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }

    *pData = (uint16_t)base->PM0_MDIO_DATA;
}

/* Internal MDIO supports C45 */
#if defined(NETC_ETH_LINK_PM0_MDIO_ADDR_REGADDR_MASK)
static void NETC_PIMDIO_C45Write(
    NETC_ETH_LINK_Type *base, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t data)
{
    base->PM0_MDIO_CFG |= NETC_ETH_LINK_PM0_MDIO_CFG_ENC45_MASK;
    base->PM0_MDIO_CTL = NETC_ETH_LINK_PM0_MDIO_CTL_PORT_ADDR(portAddr) |
                         NETC_ETH_LINK_PM0_MDIO_CTL_DEV_ADDR(devAddr);
    base->PM0_MDIO_ADDR = NETC_ETH_LINK_PM0_MDIO_ADDR_REGADDR(regAddr);

    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }

    base->PM0_MDIO_DATA = NETC_ETH_LINK_PM0_MDIO_DATA_MDIO_DATA(data);
    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }
}

static status_t NETC_PIMDIO_C45Read(
    NETC_ETH_LINK_Type *base, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t *pData)
{
    base->PM0_MDIO_CFG |= NETC_ETH_LINK_PM0_MDIO_CFG_ENC45_MASK;
    base->PM0_MDIO_CTL = NETC_ETH_LINK_PM0_MDIO_CTL_PORT_ADDR(portAddr) |
                         NETC_ETH_LINK_PM0_MDIO_CTL_DEV_ADDR(devAddr);
    base->PM0_MDIO_ADDR = NETC_ETH_LINK_PM0_MDIO_ADDR_REGADDR(regAddr);

    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }

    base->PM0_MDIO_CTL = NETC_ETH_LINK_PM0_MDIO_CTL_READ(1U) | NETC_ETH_LINK_PM0_MDIO_CTL_PORT_ADDR(portAddr) |
                         NETC_ETH_LINK_PM0_MDIO_CTL_DEV_ADDR(devAddr);

    while (NETC_PIMDIO_IsSMIBusy(base))
    {
    }

    if ((base->PM0_MDIO_CFG & 0x2U) != 0U)
    {
        return kStatus_Fail;
    }

    *pData = (uint16_t)base->PM0_MDIO_DATA;
    return kStatus_Success;
}
#endif

/*
 * MDIO API Layer MDIO Access functions
 */

status_t NETC_MDIOInit(netc_mdio_handle_t *handle, netc_mdio_config_t *config)
{
    assert(config->srcClockHz != 0U);

    uint32_t funcFlags = ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;
    netc_mdio_hw_t *mdioBase;
    NETC_ETH_LINK_Type *base;
    uint32_t instance;
    status_t result;

    handle->mdio = config->mdio;

    /* Port MDIO needs EP/Switch to enable the register access permission. */
    if (handle->mdio.type != kNETC_EMdio)
    {
        instance = NETC_SocGetFuncInstance(handle->mdio.port);
        if ((s_netcFuncBases[instance]->PCI_CFH_CMD & funcFlags) != funcFlags)
        {
            return kStatus_Fail;
        }
    }

    if (handle->mdio.type == kNETC_InternalMdio)
    {
        base   = s_netcEthLinkBases[handle->mdio.port];
        result = NETC_PIMDIO_Init(base, config);
    }
    else
    {
        if (handle->mdio.type == kNETC_EMdio)
        {
            mdioBase = (netc_mdio_hw_t *)(uintptr_t)&EMDIO_BASE->EMDIO_CFG;

            /* Reset EMDIO submodule */
            EMDIO_PCI_HDR_TYPE0->PCI_CFC_PCIE_DEV_CTL |= ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK;
            while ((EMDIO_PCI_HDR_TYPE0->PCI_CFC_PCIE_DEV_CTL & ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK) !=
                   0U)
            {
            }

            /* Enable master bus and memory access for PCIe and MSI-X */
            EMDIO_PCI_HDR_TYPE0->PCI_CFH_CMD |=
                (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
        }
        else
        {
            base     = s_netcEthLinkBases[handle->mdio.port];
            mdioBase = (netc_mdio_hw_t *)(uintptr_t)&base->PEMDIOCR;
        }
        result = NETC_PEMDIO_Init(mdioBase, config);
    }

    return result;
}

status_t NETC_MDIOWrite(netc_mdio_handle_t *handle, uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    NETC_ETH_LINK_Type *base = s_netcEthLinkBases[handle->mdio.port];
    status_t result;

    if (handle->mdio.type == kNETC_InternalMdio)
    {
        NETC_PIMDIO_Write(base, phyAddr, regAddr, data);
        result = kStatus_Success;
    }
    else
    {
        result = NETC_PEMDIO_Write(NETC_MDIOGetOpBase(handle), phyAddr, regAddr, data);
    }

    return result;
}

status_t NETC_MDIORead(netc_mdio_handle_t *handle, uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    NETC_ETH_LINK_Type *base = s_netcEthLinkBases[handle->mdio.port];
    status_t result;

    if (handle->mdio.type == kNETC_InternalMdio)
    {
        NETC_PIMDIO_Read(base, phyAddr, regAddr, pData);
        result = kStatus_Success;
    }
    else
    {
        result = NETC_PEMDIO_Read(NETC_MDIOGetOpBase(handle), phyAddr, regAddr, pData);
    }

    return result;
}

status_t NETC_MDIOC45Write(
    netc_mdio_handle_t *handle, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t data)
{
    status_t result;

    if (handle->mdio.type == kNETC_InternalMdio)
    {
#if defined(NETC_ETH_LINK_PM0_MDIO_ADDR_REGADDR_MASK)
        NETC_PIMDIO_C45Write(s_netcEthLinkBases[handle->mdio.port], portAddr, devAddr, regAddr, data);
        result = kStatus_Success;
#else
        result = kStatus_NETC_Unsupported;
#endif
    }
    else
    {
        result = NETC_PEMDIO_C45Write(NETC_MDIOGetOpBase(handle), portAddr, devAddr, regAddr, data);
    }

    return result;
}

status_t NETC_MDIOC45Read(
    netc_mdio_handle_t *handle, uint8_t portAddr, uint8_t devAddr, uint16_t regAddr, uint16_t *pData)
{
    status_t result;

    if (handle->mdio.type == kNETC_InternalMdio)
    {
#if defined(NETC_ETH_LINK_PM0_MDIO_ADDR_REGADDR_MASK)
        result = NETC_PIMDIO_C45Read(s_netcEthLinkBases[handle->mdio.port], portAddr, devAddr, regAddr, pData);
#else
        result = kStatus_NETC_Unsupported;
#endif
    }
    else
    {
        result = NETC_PEMDIO_C45Read(NETC_MDIOGetOpBase(handle), portAddr, devAddr, regAddr, pData);
    }

    return result;
}

status_t NETC_MDIOSetPhyStatusCheck(netc_mdio_handle_t *handle, netc_mdio_phy_status_t *config)
{
    status_t result = kStatus_Success;
    netc_mdio_hw_t *mdioBase;

    if (handle->mdio.type == kNETC_InternalMdio)
    {
        result = kStatus_NETC_Unsupported;
    }
    else
    {
        mdioBase                 = NETC_MDIOGetOpBase(handle);
        mdioBase->PHY_STATUS_CFG = ENETC_PF_EMDIO_PHY_STATUS_CFG_STATUS_INTERVAL(config->interval);
        mdioBase->PHY_STATUS_CTL = ENETC_PF_EMDIO_PHY_STATUS_CTL_PORT_ADDR(config->phyOrPortAddr) |
                                   ENETC_PF_EMDIO_PHY_STATUS_CTL_DEV_ADDR(config->regiOrDevAddr);
        mdioBase->PHY_STATUS_ADDR = ENETC_PF_EMDIO_PHY_STATUS_ADDR_REGADDR(config->c45RegiAddr);
        mdioBase->PHY_STATUS_MASK = ((uint32_t)config->enableIntrLow2High << 16U) + config->enableIntrHigh2Low;
    }

    return result;
}

void NETC_MDIOPhyStatusGetFlags(netc_mdio_handle_t *handle, uint16_t *low2HighMask, uint16_t *high2LowMask)
{
    assert(handle->mdio.type != kNETC_InternalMdio);
    assert(low2HighMask != NULL);
    assert(high2LowMask != NULL);

    netc_mdio_hw_t *mdioBase = NETC_MDIOGetOpBase(handle);
    uint32_t event           = mdioBase->PHY_STATUS_EVENT;

    *low2HighMask = (uint16_t)((event >> 16U) & 0xFFFFU);
    *high2LowMask = (uint16_t)(event & 0xFFFFU);
}

void NETC_MDIOPhyStatusClearFlags(netc_mdio_handle_t *handle, uint16_t low2HighMask, uint16_t high2LowMask)
{
    assert(handle->mdio.type != kNETC_InternalMdio);

    NETC_ETH_LINK_Type *base = s_netcEthLinkBases[handle->mdio.port];
    netc_mdio_hw_t *mdioBase;

    if (handle->mdio.type == kNETC_EMdio)
    {
        mdioBase = (netc_mdio_hw_t *)(uintptr_t)&EMDIO_BASE->EMDIO_CFG;
    }
    else
    {
        base     = s_netcEthLinkBases[handle->mdio.port];
        mdioBase = (netc_mdio_hw_t *)(uintptr_t)&base->PEMDIOCR;
    }
    mdioBase->PHY_STATUS_EVENT = ((uint32_t)low2HighMask << 16U) + high2LowMask;
}
