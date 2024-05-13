/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_soc.h"

#define NETC_FEATURE_ENETC_ETH_PORT_NUM (1U)

/*! @brief Pointers to netc bases for each instance. */
static ENETC_PCI_TYPE0_Type *const s_netcBases[] = ENETC_PCI_TYPE0_BASE_PTRS;

/*! @brief Pointers to enetc bases for each instance. */
static NETC_ENETC_Type *const s_netcEnetcBases[] = NETC_ENETC_BASE_PTRS;

status_t NETC_SocSetMiiMode(netc_soc_link_t link, netc_hw_mii_mode_t miiMode)
{
    status_t result = kStatus_Success;
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;
    uint8_t miiSel;

    switch (miiMode)
    {
        case kNETC_MiiMode:
            miiSel = 0;
            break;
        case kNETC_RmiiMode:
            miiSel = 1;
            break;
        case kNETC_RgmiiMode:
            miiSel = 2;
            break;
        case kNETC_GmiiMode:
            miiSel = 3;
            break;
        default:
            result = kStatus_Fail;
            break;
    }

    if (result == kStatus_Success)
    {
        base->NETC_LINK_CFG[link] &= ~BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_MII_PROT_MASK;
        base->NETC_LINK_CFG[link] |= BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_MII_PROT(miiSel);
    }

    return result;
}

status_t NETC_SocEnableRevmii(netc_soc_link_t link, bool enable)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    if (enable)
    {
        base->NETC_LINK_CFG[link] |= BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_REVMII_MASK;
    }
    else
    {
        base->NETC_LINK_CFG[link] &= ~BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_REVMII_MASK;
    }

    return kStatus_Success;
}

status_t NETC_SocSetRevmiiMiiRate(netc_soc_link_t link, netc_soc_revmii_mii_speed_t miiRate)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    base->NETC_LINK_CFG[link] &= ~BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_REVMII_RATE_MASK;
    base->NETC_LINK_CFG[link] |= BLK_CTRL_WAKEUPMIX_NETC_LINK_CFG_REVMII_RATE(miiRate);

    return kStatus_Success;
}

status_t NETC_SocSetRevmiiRgmiiDelay(netc_soc_link_t link, uint8_t delayTarget)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    if (delayTarget <= 0xFU)
    {
        base->NETC_REVMII_DLL[link] &= ~BLK_CTRL_WAKEUPMIX_NETC_REVMII_DLL_DLY_TARGET_MASK;
        base->NETC_REVMII_DLL[link] |= BLK_CTRL_WAKEUPMIX_NETC_REVMII_DLL_DLY_TARGET(delayTarget);

        return kStatus_Success;
    }
    else
    {
        return kStatus_InvalidArgument;
    }
}

status_t NETC_SocTimerClkSel(netc_soc_timer_clk_sel_t clkSel)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    if (clkSel == kNETC_SocTimerCcmClk)
    {
        base->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_TMR_EXT_CLK_SEL_MASK;
    }
    else
    {
        base->NETC_PORT_MISC_CFG |= BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_TMR_EXT_CLK_SEL_MASK;
    }

    return kStatus_Success;
}

status_t NETC_SocSetTimer(netc_timer_exttrig_index_t timerTrigger, netc_soc_timer_trig_input_t inputSel)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    base->NETC_PORT_MISC_CFG &= ~(BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_TMR_TRIG1_SEL_MASK << (uint32_t)timerTrigger);
    base->NETC_PORT_MISC_CFG |= (BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_TMR_TRIG1_SEL(inputSel) << (uint32_t)timerTrigger);

    return kStatus_Success;
}

status_t NETC_SocSetRmiiRefClk(netc_soc_link_t link, bool output)
{
    BLK_CTRL_WAKEUPMIX_Type *base = BLK_CTRL_WAKEUPMIX;

    if (output)
    {
        base->NETC_PORT_MISC_CFG |= ((uint32_t)BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT0_RMII_REF_CLK_DIR_MASK << (uint32_t)link);
    }
    else
    {
        base->NETC_PORT_MISC_CFG &= ~((uint32_t)BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT0_RMII_REF_CLK_DIR_MASK << (uint32_t)link);
    }

    return kStatus_Success;
}

void NETC_SocGetBaseResource(netc_enetc_hw_t *hw, netc_hw_si_idx_t si)
{
    uint8_t instance = getSiInstance(si);
    uint8_t siNum    = getSiNum(si);
    uint8_t siIdx    = getSiIdx(si);

    hw->base           = s_netcEnetcBases[instance];
    hw->common         = (NETC_SW_ENETC_Type *)((uintptr_t)hw->base);
    hw->portGroup.port = (NETC_PORT_Type *)((uintptr_t)hw->base + NETC_ENETC_PORT_GROUP_BASE_OFFSET);
    hw->portGroup.eth  = (NETC_ETH_LINK_Type *)((uintptr_t)hw->portGroup.port + 0x1000U);
    hw->global         = (ENETC_GLOBAL_Type *)((uintptr_t)hw->base + NETC_ENETC_GLOBAL_BASE_OFFSET);
    if (siNum == 0U)
    {
        hw->func.pf = s_netcBases[NETC_ENETC_PCIE_FUNC_OFFSET + instance];
        hw->si      = (ENETC_SI_Type *)((uintptr_t)hw->base - 0x10000U);
        hw->msixTable =
            (netc_msix_entry_t *)((uint32_t)FSL_FEATURE_NETC_MSIX_TABLE_BASE + NETC_MSIX_TABLE_OFFSET * (3U + (uint32_t)siIdx));
    }
    else
    {
        hw->func.vf   = NETC_VF1_PCI_HDR_TYPE0;
        hw->si        = (ENETC_SI_Type *)((uintptr_t)hw->base + 0xC0000U);
        hw->msixTable = (netc_msix_entry_t *)(0x60C20000U);
    }
}

uint32_t NETC_SocGetFuncInstance(netc_hw_eth_port_idx_t port)
{
    uint32_t instance;

    if ((uint32_t)port > NETC_FEATURE_ENETC_ETH_PORT_NUM - 1U)
    {
        instance = 2;
    }
    else
    {
        instance = 3U + (uint32_t)port;
    }

    return instance;
}

status_t NETC_SocSetLinkAddr(netc_soc_link_t link, uint8_t phyAddr)
{
    status_t result = kStatus_Success;

    switch (link)
    {
        case kNETC_SocLinkSwitchPort0:
            NETC_IERB->L0BCR = NETC_IERB_L0BCR_MDIO_PHYAD_PRTAD(phyAddr);
            break;
        case kNETC_SocLinkSwitchPort1:
            NETC_IERB->L1BCR = NETC_IERB_L1BCR_MDIO_PHYAD_PRTAD(phyAddr);
            break;
        case kNETC_SocLinkSwitchPort2:
            NETC_IERB->L2BCR = NETC_IERB_L2BCR_MDIO_PHYAD_PRTAD(phyAddr);
            break;
        case kNETC_SocLinkSwitchPort3:
            NETC_IERB->L3BCR = NETC_IERB_L3BCR_MDIO_PHYAD_PRTAD(phyAddr);
            break;
        case kNETC_SocLinkEp0:
            NETC_IERB->L4BCR = NETC_IERB_L4BCR_MDIO_PHYAD_PRTAD(phyAddr);
            break;
        default:
            result = kStatus_Fail;
            break;
    }

    return result;
}
