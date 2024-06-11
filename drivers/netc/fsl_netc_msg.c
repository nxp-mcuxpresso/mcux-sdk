/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_msg.h"
#include "netc_hw/fsl_netc_hw.h"
#include "netc_hw/fsl_netc_hw_enetc.h"
#include "fsl_adapter_crc.h"

#ifndef NUM_MAC_FILTER_ENTRY
#define NUM_MAC_FILTER_ENTRY 4U
#endif
#ifndef NUM_VLAN_FILTER_ENTRY
#define NUM_VLAN_FILTER_ENTRY 4U
#endif

/* MAC filter Operations */

static uint8_t EP_RxL2MFFreeNum(ep_handle_t *handle)
{
    uint8_t n = 0;
    uint8_t i;

    for (i = 0; i < NUM_MAC_FILTER_ENTRY; i++)
    {
        if (handle->macFilterCount[i] == 0U)
        {
            n++;
        }
    }

    return n;
}

static status_t EP_RxL2MFFreeIndex(ep_handle_t *handle, uint16_t *idx)
{
    uint8_t i;

    for (i = 0; i < NUM_MAC_FILTER_ENTRY; i++)
    {
        if (handle->macFilterCount[i] == 0U)
        {
            *idx = i;
            return kStatus_Success;
        }
    }

    return kStatus_Fail;
}

static void EP_RxL2MFQueryEMTableEntry(ep_handle_t *handle, uint8_t *macAddr, emtable_query_result_t *result)
{
    uint64_t address =
        ((uint64_t)macAddr[4U] << 32U) + ((uint64_t)macAddr[5U] << 40U) + *(uint32_t *)(uintptr_t)&macAddr[0];
    ENETC_SI_Type *base = handle->hw.si;
    netc_cmd_bd_t cmdBd = {0};
    status_t ret;
    uint8_t i;

    (void)memset(result, 0, sizeof(*result));

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return;
    }

    /* Query each entry */
    for (i = 0U; i < NUM_MAC_FILTER_ENTRY; i++)
    {
        /* entry not in use */
        if (handle->macFilterCount[i] == 0U)
        {
            continue;
        }

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 1U;
        cmdBd.generic.class = 1U;
        cmdBd.generic.ci    = 0U;
        cmdBd.generic.sf    = 1U;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            result->valid = 0U;
            return;
        }

        if (cmdBd.generic.addr == address)
        {
            result->valid    = 1U;
            result->match    = 1U;
            result->siBitMap = (uint16_t)cmdBd.generic.siBitMap;
            result->index    = i;
            return;
        }
    }

    result->valid = 1U;
    return;
}

static uint16_t EP_RxL2MFQueryAddEMTableEntry(ep_handle_t *handle, uint8_t si, uint8_t count, uint8_t *macAddr)
{
    emtable_query_result_t result[NUM_MAC_FILTER_ENTRY] = {0};
    ENETC_SI_Type *base                                 = handle->hw.si;
    netc_cmd_bd_t cmdBd                                 = {0};
    uint8_t free_num                                    = EP_RxL2MFFreeNum(handle);
    uint8_t match_num                                   = 0U;
    uint8_t i, m;
    status_t ret;
    uint64_t address;
    uint16_t index = 0U;

    /* Count 0 means only macAddr0 is considered. Treat as same case with array size 1. */
    if (count == 0U)
    {
        count = 1U;
    }

    if (count > NUM_MAC_FILTER_ENTRY)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassMacFilter, kNETC_MsgMacFilterNoResource, 0U);
    }

    /* Query for each MAC address */
    for (i = 0U; i < count; i++)
    {
        EP_RxL2MFQueryEMTableEntry(handle, &macAddr[i * 6U], &result[i]);
        if (result[i].valid == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }
        if (result[i].match == 1U)
        {
            match_num++;
        }
    }

    /* Check resource */
    if ((count - match_num) > free_num)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassMacFilter, kNETC_MsgMacFilterNoResource, 0U);
    }

    for (i = 0U; i < count; i++)
    {
        m       = 6U * i;
        address = ((uint64_t)macAddr[m + 4U] << 32U) + ((uint64_t)macAddr[m + 5U] << 40U) +
                  *(uint32_t *)(uintptr_t)&macAddr[m];

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.addr  = address;
        cmdBd.generic.en    = 1;
        cmdBd.generic.cmd   = 0;
        cmdBd.generic.class = 1;
        cmdBd.generic.ci    = 0;
        cmdBd.generic.sf    = 1;

        /* For matched */
        if (result[i].match == 1U)
        {
            cmdBd.generic.index    = result[i].index;
            cmdBd.generic.siBitMap = (result[i].siBitMap | ((uint32_t)1U << si));
        }
        /* For new added */
        else
        {
            if (EP_RxL2MFFreeIndex(handle, &index) != kStatus_Success)
            {
                return NETC_MSG_RETURN_CODE(kNETC_MsgClassMacFilter, kNETC_MsgMacFilterNoResource, 0U);
            }
            cmdBd.generic.index    = index;
            cmdBd.generic.siBitMap = ((uint32_t)1U << si);
        }

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update macFilterCount */
        handle->macFilterCount[cmdBd.generic.index] = 1U;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2MFQueryDeleteEMTableEntry(ep_handle_t *handle, uint8_t si, uint8_t count, uint8_t *macAddr)
{
    emtable_query_result_t result[NUM_MAC_FILTER_ENTRY] = {0};
    ENETC_SI_Type *base                                 = handle->hw.si;
    netc_cmd_bd_t cmdBd                                 = {0};
    uint8_t i;
    status_t ret;

    /* Count 0 means only macAddr0 is considered. Treat as same case with array size 1. */
    if (count == 0U)
    {
        count = 1U;
    }

    /* Query for each MAC address */
    for (i = 0U; i < count; i++)
    {
        EP_RxL2MFQueryEMTableEntry(handle, &macAddr[i * 6U], &result[i]);
        if (result[i].valid == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }
        if (result[i].match == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassMacFilter, kNETC_MsgMacFilterAddrNotFound, 0U);
        }
    }

    for (i = 0U; i < count; i++)
    {
        (void)memset(&cmdBd, 0, sizeof(cmdBd));

        cmdBd.generic.addr     = 0;
        cmdBd.generic.en       = 1;
        cmdBd.generic.siBitMap = 0;
        cmdBd.generic.index    = result[i].index;
        cmdBd.generic.cmd      = 0;
        cmdBd.generic.class    = 1;
        cmdBd.generic.ci       = 0;
        cmdBd.generic.sf       = 1;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update macFilterCount */
        handle->macFilterCount[result[i].index] = 0U;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2MFSetHashTable(ep_handle_t *handle, uint8_t si, uint8_t typeSize, uint8_t *HTWord)
{
    NETC_ENETC_Type *base = handle->hw.base;
    uint32_t HT0Word0     = *(uint32_t *)((uint32_t)HTWord);
    uint32_t HT0Word1     = *(uint32_t *)((uint32_t)HTWord + 0x4U);
    uint32_t HT1Word0     = *(uint32_t *)((uint32_t)HTWord + 0x8U);
    uint32_t HT1Word1     = *(uint32_t *)((uint32_t)HTWord + 0xcU);

    /* 64bits addr supported only */
    if ((typeSize & 0x03U) != 0U)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassMacFilter, kNETC_MsgMacFilterNotSupported, 0U);
    }

    /* UC hash table (HT) only */
    if ((typeSize & 0xc0U) == 0x40U)
    {
        base->NUM_SI[si].PSIUMHFR0 = HT0Word0;
        base->NUM_SI[si].PSIUMHFR1 = HT0Word1;
    }
    /* MC hash table (HT) only */
    else if ((typeSize & 0xc0U) == 0x80U)
    {
        base->NUM_SI[si].PSIMMHFR0 = HT0Word0;
        base->NUM_SI[si].PSIMMHFR1 = HT0Word1;
    }
    /* UC and MC hash tables */
    else
    {
        base->NUM_SI[si].PSIUMHFR0 = HT0Word0;
        base->NUM_SI[si].PSIUMHFR1 = HT0Word1;
        base->NUM_SI[si].PSIMMHFR0 = HT1Word0;
        base->NUM_SI[si].PSIMMHFR1 = HT1Word1;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
    ;
}

static uint16_t EP_RxL2MFFlush(ep_handle_t *handle, uint8_t si, uint8_t type)
{
    NETC_ENETC_Type *enetc = handle->hw.base;
    ENETC_SI_Type *base    = handle->hw.si;
    netc_cmd_bd_t cmdBd    = {0};
    bool uc                = ((type == 0x40U) || (type == 0x00U) || (type == 0xc0U));
    bool mc                = ((type == 0x80U) || (type == 0x00U) || (type == 0xc0U));
    bool ucAddr;
    bool delete;
    uint8_t i;
    status_t ret;

    /* Flush exact match table */
    for (i = 0U; i < NUM_MAC_FILTER_ENTRY; i++)
    {
        /* entry not in use */
        if (handle->macFilterCount[i] == 0U)
        {
            continue;
        }

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 1U;
        cmdBd.generic.class = 1U;
        cmdBd.generic.ci    = 0U;
        cmdBd.generic.sf    = 1U;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        ucAddr = ((cmdBd.generic.addr & 0x1U) == 0U);
        delete = ((uc && ucAddr) || (mc && (!ucAddr)));

        if (!delete)
        {
            continue;
        }

        if ((cmdBd.generic.siBitMap & ((uint32_t)1U << si)) == 0U)
        {
            continue;
        }

        if (cmdBd.generic.siBitMap == ((uint32_t)1U << si))
        {
            cmdBd.generic.addr     = 0;
            cmdBd.generic.siBitMap = 0;
        }
        else
        {
            cmdBd.generic.siBitMap &= ~((uint32_t)1U << si);
        }
        cmdBd.generic.en    = 1;
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 0;
        cmdBd.generic.class = 1;
        cmdBd.generic.ci    = 0;
        cmdBd.generic.sf    = 1;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update macFilterCount */
        if (cmdBd.generic.siBitMap == ((uint32_t)1U << si))
        {
            handle->macFilterCount[i] = 0U;
        }
    }

    /* Flush hash table */
    if (uc)
    {
        enetc->NUM_SI[si].PSIUMHFR0 = 0x0U;
        enetc->NUM_SI[si].PSIUMHFR1 = 0x0U;
    }

    if (mc)
    {
        enetc->NUM_SI[si].PSIMMHFR0 = 0x0U;
        enetc->NUM_SI[si].PSIMMHFR1 = 0x0U;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2MFSetPromisc(ep_handle_t *handle, uint8_t si, uint8_t typeOp)
{
    NETC_ENETC_Type *base = handle->hw.base;
    bool enable           = ((typeOp & 0x2U) == 0x2U);
    bool flush            = ((typeOp & 0x1U) == 0x1U);
    uint8_t type          = (typeOp & 0xc0U);

    /* UC addresses */
    if ((type == 0x40U) || (type == 0x00U) || (type == 0xc0U))
    {
        if (enable)
        {
            base->PSIPMMR |= ((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_UP_MASK << si);
        }
        else
        {
            base->PSIPMMR &= ~((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_UP_MASK << si);
        }
    }

    /* MC addresses */
    if (type == 0x80U || (type == 0x00U) || (type == 0xc0U))
    {
        if (enable)
        {
            base->PSIPMMR |= ((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_MP_MASK << si);
        }
        else
        {
            base->PSIPMMR &= ~((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_MP_MASK << si);
        }
    }

    if (flush)
    {
        return EP_RxL2MFFlush(handle, si, type);
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_PsiHandleMacFilter(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    NETC_ENETC_Type *base     = handle->hw.base;
    netc_msg_header_t *header = (netc_msg_header_t *)(uint32_t)(msgInfo->msgBuff);
    /* For exact table */
    uint8_t count    = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint8_t *macAddr = (uint8_t *)((uint32_t)msgInfo->msgBuff + 0x14U);
    /* For hash table */
    uint8_t typeSize = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint8_t *HTWord  = (uint8_t *)((uint32_t)msgInfo->msgBuff + 0x14U);
    /* For flush */
    uint8_t type = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    /* For promisc */
    uint8_t typeOp = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint16_t ret   = NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);

    switch (header->cmdId)
    {
        case (uint8_t)kNETC_MsgMacFilterSetMacAddr:
            NETC_EnetcSetSIMacAddr(base, vsi, macAddr);
            ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
            break;
        case (uint8_t)kNETC_MsgMacFilterAdd:
            ret = EP_RxL2MFQueryAddEMTableEntry(handle, vsi, count, macAddr);
            break;
        case (uint8_t)kNETC_MsgMacFilterDelete:
            ret = EP_RxL2MFQueryDeleteEMTableEntry(handle, vsi, count, macAddr);
            break;
        case (uint8_t)kNETC_MsgMacFilterSet:
            ret = EP_RxL2MFSetHashTable(handle, vsi, typeSize, HTWord);
            break;
        case (uint8_t)kNETC_MsgMacFilterFlush:
            ret = EP_RxL2MFFlush(handle, vsi, type);
            break;
        case (uint8_t)kNETC_MsgMacFilterSetMacPromisc:
            ret = EP_RxL2MFSetPromisc(handle, vsi, typeOp);
            break;
        default:
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }

    return ret;
}

/* VLAN filter Operations */

static uint8_t EP_RxL2VFFreeNum(ep_handle_t *handle)
{
    uint8_t n = 0;
    uint8_t i;

    for (i = 0; i < NUM_VLAN_FILTER_ENTRY; i++)
    {
        if (handle->vlanFilterCount[i] == 0U)
        {
            n++;
        }
    }

    return n;
}

static status_t EP_RxL2VFFreeIndex(ep_handle_t *handle, uint16_t *idx)
{
    uint8_t i;

    for (i = 0; i < NUM_VLAN_FILTER_ENTRY; i++)
    {
        if (handle->vlanFilterCount[i] == 0U)
        {
            *idx = i;
            return kStatus_Success;
        }
    }

    return kStatus_Fail;
}

static void EP_RxL2VFQueryEMTableEntry(ep_handle_t *handle, uint8_t *vlanId, emtable_query_result_t *result)
{
    uint64_t address    = *(uint32_t *)(uintptr_t)&vlanId[0];
    ENETC_SI_Type *base = handle->hw.si;
    netc_cmd_bd_t cmdBd = {0};
    status_t ret;
    uint8_t i;

    (void)memset(result, 0, sizeof(*result));

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return;
    }

    /* Query each entry */
    for (i = 0U; i < NUM_VLAN_FILTER_ENTRY; i++)
    {
        /* entry not in use */
        if (handle->vlanFilterCount[i] == 0U)
        {
            continue;
        }

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 1U;
        cmdBd.generic.class = 2U;
        cmdBd.generic.ci    = 0U;
        cmdBd.generic.sf    = 1U;
        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            result->valid = 0U;
            return;
        }

        if (cmdBd.generic.addr == address)
        {
            result->valid    = 1U;
            result->match    = 1U;
            result->siBitMap = (uint16_t)cmdBd.generic.siBitMap;
            result->index    = i;
            return;
        }
    }

    result->valid = 1U;
    return;
}

static uint16_t EP_RxL2VFQueryAddEMTableEntry(ep_handle_t *handle, uint8_t si, uint8_t count, uint8_t *vlanId)
{
    emtable_query_result_t result[NUM_VLAN_FILTER_ENTRY] = {0};
    ENETC_SI_Type *base                                  = handle->hw.si;
    netc_cmd_bd_t cmdBd                                  = {0};
    uint8_t free_num                                     = EP_RxL2VFFreeNum(handle);
    uint8_t match_num                                    = 0U;
    uint8_t i, m;
    status_t ret;
    uint64_t address;
    uint16_t index = 0U;

    /* Check count */
    if (count == 0U)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterInvalidVlan, 0U);
    }

    if (count > NUM_VLAN_FILTER_ENTRY)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterNoResource, 0U);
    }

    /* Query for each VLAN ID */
    for (i = 0U; i < count; i++)
    {
        EP_RxL2VFQueryEMTableEntry(handle, &vlanId[i * 4U], &result[i]);
        if (result[i].valid == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }
        if (result[i].match == 1U)
        {
            match_num++;
        }
    }

    /* Check resource */
    if ((count - match_num) > free_num)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterNoResource, 0U);
    }

    for (i = 0U; i < count; i++)
    {
        m       = 4U * i;
        address = *(uint32_t *)(uintptr_t)&vlanId[m];

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.addr  = address;
        cmdBd.generic.en    = 1;
        cmdBd.generic.cmd   = 0;
        cmdBd.generic.class = 1;
        cmdBd.generic.ci    = 0;
        cmdBd.generic.sf    = 1;

        /* For matched */
        if (result[i].match == 1U)
        {
            cmdBd.generic.index    = result[i].index;
            cmdBd.generic.siBitMap = (result[i].siBitMap | ((uint32_t)1U << si));
        }
        /* For new added */
        else
        {
            if (EP_RxL2VFFreeIndex(handle, &index) != kStatus_Success)
            {
                return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterNoResource, 0U);
            }
            cmdBd.generic.index    = index;
            cmdBd.generic.siBitMap = ((uint32_t)1U << si);
        }

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update vlanFilterCount */
        handle->vlanFilterCount[cmdBd.generic.index] = 1U;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2VFQueryDeleteEMTableEntry(ep_handle_t *handle, uint8_t si, uint8_t count, uint8_t *vlanId)
{
    emtable_query_result_t result[NUM_VLAN_FILTER_ENTRY] = {0};
    ENETC_SI_Type *base                                  = handle->hw.si;
    netc_cmd_bd_t cmdBd                                  = {0};
    uint8_t i;
    status_t ret;

    if (count == 0U)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterInvalidVlan, 0U);
    }

    /* Query for each VLAN ID */
    for (i = 0U; i < count; i++)
    {
        EP_RxL2VFQueryEMTableEntry(handle, &vlanId[i * 4U], &result[i]);
        if (result[i].valid == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }
        if (result[i].match == 0U)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterAddrNotFound, 0U);
        }
    }

    for (i = 0U; i < count; i++)
    {
        (void)memset(&cmdBd, 0, sizeof(cmdBd));

        cmdBd.generic.addr     = 0;
        cmdBd.generic.en       = 1;
        cmdBd.generic.siBitMap = 0;
        cmdBd.generic.index    = result[i].index;
        cmdBd.generic.cmd      = 0;
        cmdBd.generic.class    = 2;
        cmdBd.generic.ci       = 0;
        cmdBd.generic.sf       = 1;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update vlanFilterCount */
        handle->vlanFilterCount[result[i].index] = 0U;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2VFSetHashTable(ep_handle_t *handle, uint8_t si, uint8_t size, uint8_t *HTWord)
{
    NETC_ENETC_Type *base = handle->hw.base;
    uint32_t HTWord0      = *(uint32_t *)((uint32_t)HTWord);
    uint32_t HTWord1      = *(uint32_t *)((uint32_t)HTWord + 0x4U);

    /* 64bits addr supported only */
    if (size != 0U)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassVlanFilter, kNETC_MsgVlanFilterNotSupported, 0U);
    }

    base->NUM_SI[si].PSIVHFR0 = HTWord0;
    base->NUM_SI[si].PSIVHFR1 = HTWord1;

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2VFFlush(ep_handle_t *handle, uint8_t si)
{
    NETC_ENETC_Type *enetc = handle->hw.base;
    ENETC_SI_Type *base    = handle->hw.si;
    netc_cmd_bd_t cmdBd    = {0};
    uint8_t i;
    status_t ret;

    /* Flush exact match table */
    for (i = 0U; i < NUM_MAC_FILTER_ENTRY; i++)
    {
        /* entry not in use */
        if (handle->macFilterCount[i] == 0U)
        {
            continue;
        }

        (void)memset(&cmdBd, 0, sizeof(cmdBd));
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 1U;
        cmdBd.generic.class = 2U;
        cmdBd.generic.ci    = 0U;
        cmdBd.generic.sf    = 1U;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        if ((cmdBd.generic.siBitMap & ((uint32_t)1U << si)) == 0U)
        {
            continue;
        }

        if (cmdBd.generic.siBitMap == ((uint32_t)1U << si))
        {
            cmdBd.generic.addr     = 0;
            cmdBd.generic.siBitMap = 0;
        }
        else
        {
            cmdBd.generic.siBitMap &= ~((uint32_t)1U << si);
        }
        cmdBd.generic.en    = 1;
        cmdBd.generic.index = i;
        cmdBd.generic.cmd   = 0;
        cmdBd.generic.class = 2;
        cmdBd.generic.ci    = 0;
        cmdBd.generic.sf    = 1;

        ret = NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&base->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                    kNETC_NtmpV1_0);
        if (ret != kStatus_Success)
        {
            return NETC_MSG_RETURN_CODE(kNETC_MsgClassTimeout, 0U, 0U);
        }

        /* Update vlanFilterCount */
        if (cmdBd.generic.siBitMap == ((uint32_t)1U << si))
        {
            handle->vlanFilterCount[i] = 0U;
        }
    }

    /* Flush hash table */
    enetc->NUM_SI[si].PSIVHFR0 = 0x0U;
    enetc->NUM_SI[si].PSIVHFR1 = 0x0U;

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_RxL2VFSetPromisc(ep_handle_t *handle, uint8_t si, uint8_t op)
{
    NETC_ENETC_Type *base = handle->hw.base;
    bool enable           = ((op & 0x1U) == 0x1U);
    bool flush            = ((op & 0x2U) == 0x2U);

    if (enable)
    {
        base->PSIPVMR |= ((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_P_MASK << si);
    }
    else
    {
        base->PSIPVMR &= ~((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_P_MASK << si);
    }

    if (flush)
    {
        return EP_RxL2VFFlush(handle, si);
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
}

static uint16_t EP_PsiHandleVlanFilter(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    netc_msg_header_t *header = (netc_msg_header_t *)(uint32_t)(msgInfo->msgBuff);
    /* For exact table */
    uint8_t count   = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint8_t *vlanId = (uint8_t *)((uint32_t)msgInfo->msgBuff + 0x14U);
    /* For hash table */
    uint8_t size    = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint8_t *HTWord = (uint8_t *)((uint32_t)msgInfo->msgBuff + 0x14U);
    /* For promisc */
    uint8_t op   = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x10U);
    uint16_t ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);

    switch (header->cmdId)
    {
        case (uint8_t)kNETC_MsgVlanFilterAdd:
            ret = EP_RxL2VFQueryAddEMTableEntry(handle, vsi, count, vlanId);
            break;
        case (uint8_t)kNETC_MsgVlanFilterDelete:
            ret = EP_RxL2VFQueryDeleteEMTableEntry(handle, vsi, count, vlanId);
            break;
        case (uint8_t)kNETC_MsgVlanFilterSet:
            ret = EP_RxL2VFSetHashTable(handle, vsi, size, HTWord);
            break;
        case (uint8_t)kNETC_MsgVlanFilterFlush:
            ret = EP_RxL2VFFlush(handle, vsi);
            break;
        case (uint8_t)kNETC_MsgVlanFilterSetVlanPromisc:
            ret = EP_RxL2VFSetPromisc(handle, vsi, op);
            break;
        default:
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }

    return ret;
}

/* Link status operations */

static uint16_t EP_GetLinkStatus(ep_handle_t *handle)
{
    uint8_t link = 0U;
    status_t status;

    if (handle->getLinkStatus == NULL)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);
    }

    status = handle->getLinkStatus(handle, &link);
    if (status != kStatus_Success)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassLinkStatus, (link == 0U ? 0x1U : 0x0U), 0U);
}

static uint16_t EP_PsiHandleLinkStatus(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    netc_msg_header_t *header = (netc_msg_header_t *)(uint32_t)(msgInfo->msgBuff);
    uint16_t ret              = NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);

    switch (header->cmdId)
    {
        case (uint8_t)kNETC_MsgLinkStatusGet:
            ret = EP_GetLinkStatus(handle);
            break;
        case (uint8_t)kNETC_MsgLinkStatusEnableNotify:
            handle->vsiBitMapNotifyLinkStatus |= ((uint16_t)1U << vsi);
            ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
            break;
        case (uint8_t)kNETC_MsgLinkStatusCancelNotify:
            handle->vsiBitMapNotifyLinkStatus &= ~((uint16_t)1U << vsi);
            ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
            break;
        default:
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }

    return ret;
}

/* Link speed operations */

static uint16_t EP_GetLinkSpeed(ep_handle_t *handle)
{
    netc_hw_mii_speed_t speed;
    netc_hw_mii_duplex_t duplex;
    netc_msg_link_speed_code_t code;

    status_t status;

    if (handle->getLinkSpeed == NULL)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);
    }

    status = handle->getLinkSpeed(handle, &speed, &duplex);
    if (status != kStatus_Success)
    {
        return NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);
    }

    switch (speed)
    {
        case (kNETC_MiiSpeed10M):
            code = ((duplex == kNETC_MiiHalfDuplex) ? kNETC_MsgLinkSpeed10HD : kNETC_MsgLinkSpeed10FD);
            break;
        case (kNETC_MiiSpeed100M):
            code = ((duplex == kNETC_MiiHalfDuplex) ? kNETC_MsgLinkSpeed100HD : kNETC_MsgLinkSpeed100FD);
            break;
        case (kNETC_MiiSpeed1000M):
            code = kNETC_MsgLinkSpeed1000;
            break;
        case (kNETC_MiiSpeed2500M):
            code = kNETC_MsgLinkSpeed2500;
            break;
        case (kNETC_MiiSpeed5G):
            code = kNETC_MsgLinkSpeed5000;
            break;
        case (kNETC_MiiSpeed10G):
            code = kNETC_MsgLinkSpeed10G;
            break;
        default:
            code = kNETC_MsgLinkSpeedNotSupport;
            break;
    }

    return NETC_MSG_RETURN_CODE(kNETC_MsgClassLinkSpeed, code, 0U);
}

static uint16_t EP_PsiHandleLinkSpeed(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    netc_msg_header_t *header = (netc_msg_header_t *)(uint32_t)(msgInfo->msgBuff);
    uint16_t ret              = NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);

    switch (header->cmdId)
    {
        case (uint8_t)kNETC_MsgLinkSpeedGet:
            ret = EP_GetLinkSpeed(handle);
            break;
        case (uint8_t)kNETC_MsgLinkSpeedEnableNotify:
            handle->vsiBitMapNotifyLinkSpeed |= ((uint16_t)1U << vsi);
            ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
            break;
        case (uint8_t)kNETC_MsgLinkSpeedCancelNotify:
            handle->vsiBitMapNotifyLinkSpeed &= ~((uint16_t)1U << vsi);
            ret = NETC_MSG_RETURN_CODE(kNETC_MsgClassDone, 0U, 0U);
            break;
        default:
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }

    return ret;
}

void EP_PsiNotifyLink(ep_handle_t *handle)
{
    ENETC_SI_Type *base = handle->hw.si;
    uint16_t code;

    if (handle->vsiBitMapNotifyLinkStatus != 0U)
    {
        code = EP_GetLinkStatus(handle);
        if (code != NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U))
        {
            base->PSI_A.PSIMSGSR = (uint32_t)handle->vsiBitMapNotifyLinkStatus | ((uint32_t)code << 16U);
        }
    }

    if (handle->vsiBitMapNotifyLinkSpeed != 0U)
    {
        code = EP_GetLinkSpeed(handle);
        if (code != NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U))
        {
            base->PSI_A.PSIMSGSR = (uint32_t)handle->vsiBitMapNotifyLinkSpeed | ((uint32_t)code << 16U);
        }
    }
}

status_t EP_PsiRxMsg(ep_handle_t *handle, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    ENETC_SI_Type *base = handle->hw.si;
    status_t result     = kStatus_Fail;
    uint16_t siBitMap   = (uint16_t)base->PSI_A.PSIMSGRR;
    uint8_t vsiIdx      = (uint8_t)NETC_SIGetVsiIndex(vsi);
    uint64_t address;
    uint8_t msgSize;
    uint32_t addrH;
    uint32_t addrL;

    if ((siBitMap & (uint16_t)vsi) != 0U)
    {
        addrH   = base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR1;
        addrL   = base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR0 & ENETC_SI_PSIVMSGRCVAR0_ADDRL_MASK;
        address = ((uint64_t)addrH << 32U) + addrL;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_DMA2Local);
#endif
        msgInfo->msgBuff = (uint8_t *)(uintptr_t)address;
        msgSize          = (uint8_t)(base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR0 & ENETC_SI_PSIVMSGRCVAR0_MSIZE_MASK);
        msgInfo->msgLen  = (msgSize == 0U) ? 1024U : (32U * (uint32_t)msgSize);

        result = kStatus_Success;
    }
    return result;
}

void EP_PsiHandleRxMsg(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    netc_msg_header_t *header = (netc_msg_header_t *)(uint32_t)(msgInfo->msgBuff);
    uint8_t crc0              = *(uint8_t *)(msgInfo->msgBuff);
    uint8_t crc1              = *(uint8_t *)((uint32_t)msgInfo->msgBuff + 0x1U);
    uint16_t code             = NETC_MSG_RETURN_CODE(kNETC_MsgClassNotSupport, 0U, 0U);
    ENETC_SI_Type *base       = handle->hw.si;
    bool notify               = false;
    uint32_t crc;
    hal_crc_config_t config   = {
        .crcSize            = 2U,
        .crcStartByte       = 2U,
        .crcRefIn           = KHAL_CrcInputNoRef,
        .crcRefOut          = KHAL_CrcOutputNoRef,
        .crcByteOrder       = KHAL_CrcMSByteFirst,
        .complementChecksum = 0U,
        .crcSeed            = 0xFFFFU,
        .crcPoly            = (uint32_t)KHAL_CrcPolynomial_CRC_16,
        .crcXorOut          = 0x0000U,
    };

    if (msgInfo->msgLen != (((uint32_t)header->len + 1U) * 32U))
    {
        code = NETC_MSG_RETURN_CODE(kNETC_MsgClassLenError, 0U, 0U);
        goto out;
    }

    crc = HAL_CrcCompute(&config, (uint8_t *)msgInfo->msgBuff, msgInfo->msgLen);
    if (((crc & 0xffU) != (uint32_t)crc1) || (((crc >> 8U) & 0xffU) != (uint32_t)crc0))
    {
        code = NETC_MSG_RETURN_CODE(kNETC_MsgClassCsumError, 0U, 0U);
        goto out;
    }

    switch (header->classId)
    {
        case (uint8_t)kNETC_MsgClassMacFilter:
            code = EP_PsiHandleMacFilter(handle, vsi, msgInfo);
            break;
        case (uint8_t)kNETC_MsgClassVlanFilter:
            code = EP_PsiHandleVlanFilter(handle, vsi, msgInfo);
            break;
        case (uint8_t)kNETC_MsgClassLinkStatus:
            code = EP_PsiHandleLinkStatus(handle, vsi, msgInfo);
            if (header->cmdId == (uint8_t)kNETC_MsgLinkStatusEnableNotify)
            {
                notify = true;
            }
            break;
        case (uint8_t)kNETC_MsgClassLinkSpeed:
            code = EP_PsiHandleLinkSpeed(handle, vsi, msgInfo);
            if (header->cmdId == (uint8_t)kNETC_MsgLinkSpeedEnableNotify)
            {
                notify = true;
            }
            break;
        case (uint8_t)kNETC_MsgClassTimerSyncStatus:
            break;
        case (uint8_t)kNETC_MsgClassIpVersion:
            break;
        default:
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }

out:
    base->PSI_A.PSIMSGRR = ((uint32_t)vsi << 1U) | ((uint32_t)code << 16U);

    if (notify)
    {
        EP_PsiNotifyLink(handle);
    }
}
