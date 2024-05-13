/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_hw.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.netc"
#endif

#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
#define NETC_KC_CFG(x)                                                                   \
    (NETC_SW_ENETC_ISIDKC0CR0_ETP(x.etp) | NETC_SW_ENETC_ISIDKC0CR0_SQTP(x.sqtp) |       \
     NETC_SW_ENETC_ISIDKC0CR0_IPCPP(x.ipcpp) | NETC_SW_ENETC_ISIDKC0CR0_IVIDP(x.ividp) | \
     NETC_SW_ENETC_ISIDKC0CR0_OPCPP(x.opcpp) | NETC_SW_ENETC_ISIDKC0CR0_OVIDP(x.ovidp) | \
     NETC_SW_ENETC_ISIDKC0CR0_SMACP(x.smacp) | NETC_SW_ENETC_ISIDKC0CR0_DMACP(x.dmacp) | \
     NETC_SW_ENETC_ISIDKC0CR0_SPMP(x.spmp) | NETC_SW_ENETC_ISIDKC0CR0_PORTP(x.portp) |   \
     NETC_SW_ENETC_ISIDKC0CR0_VALID(x.valid))
#else
#define NETC_KC_CFG(x)                                                                   \
    (NETC_SW_ENETC_ISIDKC0CR0_ETP(x.etp) | NETC_SW_ENETC_ISIDKC0CR0_SQTP(x.sqtp) |       \
     NETC_SW_ENETC_ISIDKC0CR0_IPCPP(x.ipcpp) | NETC_SW_ENETC_ISIDKC0CR0_IVIDP(x.ividp) | \
     NETC_SW_ENETC_ISIDKC0CR0_OPCPP(x.opcpp) | NETC_SW_ENETC_ISIDKC0CR0_OVIDP(x.ovidp) | \
     NETC_SW_ENETC_ISIDKC0CR0_SMACP(x.smacp) | NETC_SW_ENETC_ISIDKC0CR0_DMACP(x.dmacp) | \
     NETC_SW_ENETC_ISIDKC0CR0_PORTP(x.portp) | \
     NETC_SW_ENETC_ISIDKC0CR0_VALID(x.valid))
#endif

#define NETC_KC_PAYLOAD(x)                                                                                     \
    (NETC_SW_ENETC_ISIDKC0PF0CR_LBMASK(x.lbMask) | NETC_SW_ENETC_ISIDKC0PF0CR_FBMASK(x.fbMask) |               \
     NETC_SW_ENETC_ISIDKC0PF0CR_BYTE_OFFSET(x.byteOffset) | NETC_SW_ENETC_ISIDKC0PF0CR_NUM_BYTES(x.numBytes) | \
     NETC_SW_ENETC_ISIDKC0PF0CR_PFP(x.pfp))

uint16_t NETC_SIGetVsiIndex(netc_vsi_number_t vsi)
{
    uint32_t vsiIdx = (uint32_t)vsi;
    uint16_t index  = 0;

    do
    {
        index++;
        vsiIdx >>= 1U;
    } while ((vsiIdx & 0x1U) == 0U);
    return (index - 1U);
}

void NETC_PSFPKcProfileInit(NETC_SW_ENETC_Type *base, const netc_isi_kc_rule_t *rule, bool enKcPair1)
{
    if (enKcPair1)
    {
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        base->ISIDKC2PF0CR = NETC_KC_PAYLOAD(rule[0].payload[0]);
        base->ISIDKC2PF1CR = NETC_KC_PAYLOAD(rule[0].payload[1]);
        base->ISIDKC2PF2CR = NETC_KC_PAYLOAD(rule[0].payload[2]);
        base->ISIDKC2PF3CR = NETC_KC_PAYLOAD(rule[0].payload[3]);
        base->ISIDKC3PF0CR = NETC_KC_PAYLOAD(rule[1].payload[0]);
        base->ISIDKC3PF1CR = NETC_KC_PAYLOAD(rule[1].payload[1]);
        base->ISIDKC3PF2CR = NETC_KC_PAYLOAD(rule[1].payload[2]);
        base->ISIDKC3PF3CR = NETC_KC_PAYLOAD(rule[1].payload[3]);
        base->ISIDKC2CR0   = NETC_KC_CFG(rule[0]);
        base->ISIDKC3CR0   = NETC_KC_CFG(rule[1]);
#endif
    }
    else
    {
        base->ISIDKC0PF0CR = NETC_KC_PAYLOAD(rule[0].payload[0]);
        base->ISIDKC0PF1CR = NETC_KC_PAYLOAD(rule[0].payload[1]);
        base->ISIDKC0PF2CR = NETC_KC_PAYLOAD(rule[0].payload[2]);
        base->ISIDKC0PF3CR = NETC_KC_PAYLOAD(rule[0].payload[3]);
        base->ISIDKC1PF0CR = NETC_KC_PAYLOAD(rule[1].payload[0]);
        base->ISIDKC1PF1CR = NETC_KC_PAYLOAD(rule[1].payload[1]);
        base->ISIDKC1PF2CR = NETC_KC_PAYLOAD(rule[1].payload[2]);
        base->ISIDKC1PF3CR = NETC_KC_PAYLOAD(rule[1].payload[3]);
        base->ISIDKC0CR0   = NETC_KC_CFG(rule[0]);
        base->ISIDKC1CR0   = NETC_KC_CFG(rule[1]);
    }
}

void NETC_RxVlanCInit(NETC_SW_ENETC_Type *base, const netc_vlan_classify_config_t *config, bool enRtag)
{
    base->CVLANR1 =
        NETC_SW_ENETC_CVLANR1_V(config->enableCustom1) | NETC_SW_ENETC_CVLANR1_ETYPE(config->custom1EtherType);
    base->CVLANR2 =
        NETC_SW_ENETC_CVLANR2_V(config->enableCustom2) | NETC_SW_ENETC_CVLANR2_ETYPE(config->custom2EtherType);
    if (enRtag)
    {
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        base->PSRTAGETR = NETC_SW_ENETC_PSRTAGETR_ETHERTYPE(config->preStandRTAGType);
#endif
    }
}

void NETC_RxQosCInit(NETC_SW_ENETC_Type *base, const netc_qos_classify_profile_t *profile, bool enProfile1)
{
    uint32_t ipv[2] = {0};
    uint32_t dr     = 0;
    for (uint32_t i = 0U; i < 8U; i++)
    {
        ipv[0] |= ((uint32_t)profile->ipv[i] & NETC_SW_ENETC_VLANIPVMPR0_PCP_DEI_0_MASK) << (4U * i);
        ipv[1] |= ((uint32_t)profile->ipv[i + 8U] & NETC_SW_ENETC_VLANIPVMPR0_PCP_DEI_0_MASK) << (4U * i);
    }
    for (uint32_t i = 0U; i < 16U; i++)
    {
        dr |= ((uint32_t)profile->dr[i] & NETC_SW_ENETC_VLANDRMPR_PCP_DEI_0_MASK) << (2U * i);
    }

    if (enProfile1)
    {
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        base->NUM_PROFILE[1].VLANIPVMPR0 = ipv[0];
        base->NUM_PROFILE[1].VLANIPVMPR1 = ipv[1];
        base->NUM_PROFILE[1].VLANDRMPR   = dr;
#endif
    }
    else
    {
        base->NUM_PROFILE[0].VLANIPVMPR0 = ipv[0];
        base->NUM_PROFILE[0].VLANIPVMPR1 = ipv[1];
        base->NUM_PROFILE[0].VLANDRMPR   = dr;
    }
}

status_t NETC_CmdBDRInit(netc_cbdr_hw_t *base, const netc_cmd_bdr_config_t *config)
{
    assert((base != NULL) && (config != NULL));
    status_t status = kStatus_Success;
    uint64_t address;

    if ((0U != ((uint32_t)config->bdBase % 128U)) || (0U != (config->bdLength % 8U)))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* Map function only supports 32-bit now, so here limit 32-bit first */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        address = MEMORY_ConvertMemoryMapAddress((uintptr_t)config->bdBase, kMEMORY_Local2DMA);
#else
        address = (uintptr_t)config->bdBase;
#endif
        base->CBDRBAR0 = NETC_ADDR_LOW_32BIT(address);
        base->CBDRBAR1 = NETC_ADDR_HIGH_32BIT(address);
        base->CBDRPIR  = 0U;
        base->CBDRCIR  = 0U;
        base->CBDRLENR = (uint32_t)config->bdLength & ENETC_SI_SICBDRLENR_LENGTH_MASK;
        base->CBDRMR |= ENETC_SI_SICBDRMR_EN_MASK;
    }
    return status;
}

status_t NETC_CmdBDRDeinit(netc_cbdr_hw_t *base)
{
    assert(base != NULL);

    base->CBDRMR &= ~ENETC_SI_SICBDRMR_EN_MASK;
    base->CBDRBAR0 = 0U;
    base->CBDRBAR1 = 0U;
    base->CBDRPIR  = 0U;
    base->CBDRCIR  = 0U;
    base->CBDRLENR = 0U;

    return kStatus_Success;
}

static void EP_CleanUsedBD(netc_cbdr_hw_t *base, netc_cmd_bdr_t *cbdr)
{
    uint16_t curCleanIndex = cbdr->cleanIndex;

    while (curCleanIndex != base->CBDRCIR)
    {
        (void)memset((void *)&cbdr->bdBase[curCleanIndex], 0, sizeof(netc_cmd_bd_t));
        curCleanIndex = (curCleanIndex + 1U) % cbdr->bdLength;
    }
    cbdr->cleanIndex = curCleanIndex;
}

status_t NETC_CmdBDSendCommand(netc_cbdr_hw_t *base,
                               netc_cmd_bdr_t *cbdr,
                               netc_cmd_bd_t *cbd,
                               netc_cbd_version_t version)
{
    assert((base != NULL) && (cbdr != NULL) && (cbd != NULL));

    status_t status = kStatus_Success;
    uint16_t curIndex;

    if ((!cbdr->bdrEnable) || (cbdr->cleanIndex == (cbdr->producerIndex + 1U) % cbdr->bdLength))
    {
        /* Selected BD ring is disable or full */
        status = kStatus_InvalidArgument;
    }

    if (kStatus_Success == status)
    {
        if (version == kNETC_NtmpV2_0)
        {
            if (((uintptr_t)cbd->req.addr % 16U) != 0U)
            {
                /* The request and response data buffers start address must be 16-byte aligned */
                return kStatus_InvalidArgument;
            }
            else
            {
                cbd->req.version = 0x2;
                cbd->req.npf     = 1;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                cbd->req.addr = (uintptr_t)MEMORY_ConvertMemoryMapAddress((uint32_t)cbd->req.addr, kMEMORY_Local2DMA);
#endif
            }
        }
        curIndex = cbdr->producerIndex;
        /* Copy command data to ring */
        cbdr->bdBase[curIndex] = *cbd;
        /* Update BD ring producer index */
        cbdr->producerIndex = (curIndex + 1U) % cbdr->bdLength;

        /* Make sure all data in the command BD is ready. */
        __DSB();
        /* Let hardware know command BD has been added */
        base->CBDRPIR = ((uint32_t)curIndex + 1U) % cbdr->bdLength;

        /* Wait until the command is execution completed */
        while (cbdr->producerIndex != base->CBDRCIR)
        {
        }

        /* Copy command BD responses data */
        *cbd = cbdr->bdBase[curIndex];
        /* Clean the unused BDs */
        EP_CleanUsedBD(base, cbdr);
        /* Return detail error status if not run success */
        if (version == kNETC_NtmpV2_0)
        {
            if (cbd->resp.error != 0U)
            {
                status = (status_t)cbd->resp.error;
            }
        }
        else
        {
            if (cbd->generic.status != 0U)
            {
                status = (status_t)cbd->generic.status;
            }
        }
    }

    return status;
}

status_t NETC_AddIPFTableEntry(netc_cbdr_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    /* Add entry to IPF Table and query the ENTRY_ID */
    handle->buffer->ipf.request.cfge = config->cfge;
    handle->buffer->ipf.request.keye = config->keye;
    handle->buffer->ipf.request.commonHeader.updateActions =
        (uint16_t)kNETC_IPFStsEUpdate | (uint16_t)kNETC_IPFCfgEUpdate;
    handle->buffer->ipf.request.commonHeader.queryActions = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_ipf_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_ipf_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_IPFTable;
    cmdBd.req.cmd                                         = kNETC_AddAndQueryEntry;
    /* Add operation only support Ternary Match Key Element Match */
    cmdBd.req.accessType = kNETC_TernaryKeyMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *entryID = handle->buffer->ipf.response.entryID;
    }
    return status;
}

status_t NETC_UpdateIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    /* Update entry in IPF Table base on the ENTRY_ID */
    handle->buffer->ipf.request.cfge    = *cfg;
    handle->buffer->ipf.request.entryID = entryID;
    handle->buffer->ipf.request.commonHeader.updateActions =
        (uint16_t)kNETC_IPFStsEUpdate | (uint16_t)kNETC_IPFCfgEUpdate;
    handle->buffer->ipf.request.commonHeader.queryActions = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_ipf_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_ipf_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_IPFTable;
    cmdBd.req.cmd                                         = kNETC_UpdateEntry;
    cmdBd.req.accessType                                  = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_QueryIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_ipf_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    handle->buffer->ipf.request.entryID                    = entryID;
    handle->buffer->ipf.request.commonHeader.updateActions = 0U;
    handle->buffer->ipf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_ipf_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_ipf_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_IPFTable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        config->keye = handle->buffer->ipf.response.keye;
        config->cfge = handle->buffer->ipf.response.cfge;
    }

    return status;
}

status_t NETC_DelIPFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    handle->buffer->ipf.request.entryID                    = entryID;
    handle->buffer->ipf.request.commonHeader.updateActions = 0;
    handle->buffer->ipf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_ipf_req_data_t);
    cmdBd.req.resLength                                    = 4U;
    cmdBd.req.tableId                                      = kNETC_IPFTable;
    cmdBd.req.cmd                                          = kNETC_DeleteEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_ResetIPFMatchCounter(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    handle->buffer->ipf.request.entryID                    = entryID;
    handle->buffer->ipf.request.commonHeader.updateActions = (uint16_t)kNETC_IPFStsEUpdate;
    handle->buffer->ipf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_ipf_req_data_t);
    cmdBd.req.resLength                                    = 4U;
    cmdBd.req.tableId                                      = kNETC_IPFTable;
    cmdBd.req.cmd                                          = kNETC_UpdateEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_GetIPFMatchedCount(netc_cbdr_handle_t *handle, uint32_t entryID, uint64_t *count)
{
    status_t status     = kStatus_Success;
    netc_cmd_bd_t cmdBd = {0};

    (void)memset(handle->buffer, 0, sizeof(netc_tb_ipf_req_data_t));
    handle->buffer->ipf.request.entryID                    = entryID;
    handle->buffer->ipf.request.commonHeader.updateActions = 0U;
    handle->buffer->ipf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_ipf_keye_t) + 4U;
    cmdBd.req.resLength                                    = sizeof(netc_tb_ipf_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_IPFTable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *count = ((uint64_t)handle->buffer->ipf.response.stse.matchCount[1] << 32U) |
                 handle->buffer->ipf.response.stse.matchCount[0];
    }
    return status;
}

status_t NETC_AddISITableEntry(netc_cbdr_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    /* Add entry to ISI Table and query the ENTRY_ID */
    handle->buffer->isi.request.cfge                       = config->cfge;
    handle->buffer->isi.request.keye                       = config->keye;
    handle->buffer->isi.request.commonHeader.updateActions = 1U;
    /* Query ENTRY_ID only */
    handle->buffer->isi.request.commonHeader.queryActions = 1U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_isi_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_isi_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_ISITable;
    cmdBd.req.cmd                                         = kNETC_AddAndQueryEntry;
    /* Add operation only support Exact Match Key Element Match */
    cmdBd.req.accessType = kNETC_ExactKeyMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *entryID = handle->buffer->isi.response.entryID;
    }

    return status;
}

status_t NETC_QueryISITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isi_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    handle->buffer->isi.request.entryID                    = entryID;
    handle->buffer->isi.request.commonHeader.updateActions = 0U;
    handle->buffer->isi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isi_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isi_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISITable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (0U != cmdBd.resp.numMatched)
        {
            config->keye = handle->buffer->isi.response.keye;
            config->cfge = handle->buffer->isi.response.cfge;
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }

    return status;
}

status_t NETC_QueryISITableEntryWithKey(netc_cbdr_handle_t *handle, netc_tb_isi_keye_t *keye, netc_tb_isi_rsp_data_t *rsp)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    handle->buffer->isi.request.keye                       = *keye;
    handle->buffer->isi.request.commonHeader.updateActions = 0U;
    handle->buffer->isi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isi_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isi_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISITable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType                                   = kNETC_ExactKeyMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (0U != cmdBd.resp.numMatched)
        {
            *rsp = handle->buffer->isi.response;
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }

    return status;
}

status_t NETC_DelISITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    handle->buffer->isi.request.entryID                    = entryID;
    handle->buffer->isi.request.commonHeader.updateActions = 0;
    handle->buffer->isi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = 24U;
    cmdBd.req.resLength                                    = 4U;
    cmdBd.req.tableId                                      = kNETC_ISITable;
    cmdBd.req.cmd                                          = kNETC_DeleteEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_AddOrUpdateISTableEntry(netc_cbdr_handle_t *handle, netc_tb_is_config_t *config, bool isAdd)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    /* Add or Update entry in IS Table */
    handle->buffer->is.request.cfge                       = config->cfge;
    handle->buffer->is.request.entryID                    = config->entryID;
    handle->buffer->is.request.commonHeader.updateActions = 1U;
    handle->buffer->is.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_is_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_is_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_ISTable;
    if (isAdd)
    {
        cmdBd.req.cmd = kNETC_AddEntry;
    }
    else
    {
        cmdBd.req.cmd = kNETC_UpdateEntry;
    }
    /* Only support ID Match Key Element Match */
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_QueryISTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_is_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_is_req_data_t));
    handle->buffer->is.request.entryID                    = entryID;
    handle->buffer->is.request.commonHeader.updateActions = 0U;
    handle->buffer->is.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_is_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_is_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_ISTable;
    cmdBd.req.cmd                                         = kNETC_QueryEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (0U != cmdBd.resp.numMatched)
        {
            config->entryID = handle->buffer->is.response.entryID;
            config->cfge = handle->buffer->is.response.cfge;
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }

    return status;
}

status_t NETC_DelISTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_is_req_data_t));
    handle->buffer->is.request.entryID                    = entryID;
    handle->buffer->is.request.commonHeader.updateActions = 0;
    handle->buffer->is.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = 8U;
    cmdBd.req.resLength                                   = 0U;
    cmdBd.req.tableId                                     = kNETC_ISTable;
    cmdBd.req.cmd                                         = kNETC_DeleteEntry;
    cmdBd.req.accessType                                  = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_AddISFTableEntry(netc_cbdr_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    /* Add entry to ISF Table and query the ENTRY_ID */
    handle->buffer->isf.request.cfge                       = config->cfge;
    handle->buffer->isf.request.keye                       = config->keye;
    handle->buffer->isf.request.commonHeader.updateActions = 1U;
    /* Query ENTRY_ID only */
    handle->buffer->isi.request.commonHeader.queryActions = 1U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_isf_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_isf_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_ISFTable;
    cmdBd.req.cmd                                         = kNETC_AddAndQueryEntry;
    /* Add operation only support Exact Match Key Element Match */
    cmdBd.req.accessType = kNETC_ExactKeyMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *entryID = handle->buffer->isf.response.entryID;
    }

    return status;
}

status_t NETC_UpdateISFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    /* Update entry in ISF Table base on the ENTRY_ID */
    handle->buffer->isf.request.cfge                       = *cfg;
    handle->buffer->isf.request.entryID                    = entryID;
    handle->buffer->isf.request.commonHeader.updateActions = 1U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isf_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isf_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISFTable;
    cmdBd.req.cmd                                          = kNETC_UpdateEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_DelISFTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isf_req_data_t));
    handle->buffer->isf.request.entryID                    = entryID;
    handle->buffer->isf.request.commonHeader.updateActions = 0;
    handle->buffer->isf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = 12U;
    cmdBd.req.resLength                                    = 4U;
    cmdBd.req.tableId                                      = kNETC_ISFTable;
    cmdBd.req.cmd                                          = kNETC_DeleteEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_QueryISFTableEntry(netc_cbdr_handle_t *handle, netc_tb_isf_keye_t *keye, netc_tb_isf_rsp_data_t *rsp)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isf_req_data_t));
    handle->buffer->isf.request.keye                       = *keye;
    handle->buffer->isf.request.commonHeader.updateActions = 0U;
    handle->buffer->isf.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isf_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isf_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISFTable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType                                   = kNETC_ExactKeyMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (0U != cmdBd.resp.numMatched)
        {
            *rsp = handle->buffer->isf.response;
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }
    return status;
}

status_t NETC_AddISCTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isi_req_data_t));
    /* Add entry to ISC Table according to the ENTRY_ID (ISC_EID) */
    handle->buffer->isc.request.entryID                    = entryID;
    handle->buffer->isc.request.commonHeader.updateActions = 0U;
    handle->buffer->isc.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isc_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isc_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISCTable;
    cmdBd.req.cmd                                          = kNETC_AddEntry;
    /* Only support ID Match Key Element Match */
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_GetISCStatistic(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isc_req_data_t));
    handle->buffer->isc.request.entryID                    = entryID;
    handle->buffer->isc.request.commonHeader.updateActions = 0U;
    handle->buffer->isc.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isc_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isc_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISCTable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    /* Only support ID Match Key Element Match */
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *statistic = handle->buffer->isc.response.stse;
    }
    return status;
}

status_t NETC_ResetISCStatistic(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_isc_req_data_t));
    /* Reset ISC Table according to the ENTRY_ID (ISC_EID) */
    handle->buffer->isc.request.entryID                    = entryID;
    handle->buffer->isc.request.commonHeader.updateActions = 1U;
    handle->buffer->isc.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_isc_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_isc_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_ISCTable;
    cmdBd.req.cmd                                          = kNETC_UpdateEntry;
    /* Only support ID Match Key Element Match */
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_AddOrUpdateSGITableEntry(netc_cbdr_handle_t *handle, netc_tb_sgi_config_t *config, bool isAdd)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgi_req_data_t));
    /* Add entry to SGI Table */
    handle->buffer->sgi.request.acfge   = config->acfge;
    handle->buffer->sgi.request.cfge    = config->cfge;
    handle->buffer->sgi.request.icfge   = config->icfge;
    handle->buffer->sgi.request.entryID = config->entryID;
    handle->buffer->sgi.request.commonHeader.updateActions =
        (uint16_t)kNETC_SGIAcfEUpdate | (uint16_t)kNETC_SGICfgEUpdate | (uint16_t)kNETC_SGISgisEUpdate;
    handle->buffer->sgi.request.commonHeader.queryActions = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_sgi_req_data_t);
    cmdBd.req.resLength                                   = sizeof(netc_tb_sgi_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_SGITable;
    if (isAdd)
    {
        cmdBd.req.cmd = kNETC_AddEntry;
    }
    else
    {
        cmdBd.req.cmd = kNETC_UpdateEntry;
    }
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_DelSGITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgi_req_data_t));
    /* Delete entry in SGI Table */
    handle->buffer->sgi.request.entryID                    = entryID;
    handle->buffer->sgi.request.commonHeader.updateActions = 0U;
    handle->buffer->sgi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = sizeof(netc_tb_sgi_req_data_t);
    cmdBd.req.resLength                                    = sizeof(netc_tb_sgi_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_SGITable;
    cmdBd.req.cmd                                          = kNETC_DeleteEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_GetSGIState(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *statis)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgi_rsp_data_t));
    handle->buffer->sgi.request.entryID                    = entryID;
    handle->buffer->sgi.request.commonHeader.updateActions = 0U;
    handle->buffer->sgi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = 8U;
    cmdBd.req.resLength                                    = sizeof(netc_tb_sgi_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_SGITable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *statis = handle->buffer->sgi.response.sgise;
    }
    return status;
}

status_t NETC_QuerySGITableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgi_rsp_data_t *rsp)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgi_rsp_data_t));
    handle->buffer->sgi.request.entryID                    = entryID;
    handle->buffer->sgi.request.commonHeader.updateActions = 0U;
    handle->buffer->sgi.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = 8U;
    cmdBd.req.resLength                                    = sizeof(netc_tb_sgi_rsp_data_t);
    cmdBd.req.tableId                                      = kNETC_SGITable;
    cmdBd.req.cmd                                          = kNETC_QueryEntry;
    cmdBd.req.accessType                                   = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (cmdBd.resp.numMatched != 0U)
        {
            *rsp = handle->buffer->sgi.response;
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }

    return status;
}

status_t NETC_AddSGCLTableEntry(netc_cbdr_handle_t *handle, netc_tb_sgcl_gcl_t *config)
{
    netc_cmd_bd_t cmdBd = {0};

    if ((config->numEntries > NETC_TB_SGCL_MAX_ENTRY) || (config->numEntries == 0U) || (config->gcList == NULL))
    {
        return kStatus_InvalidArgument;
    }
    (void)memset(handle->buffer, 0, 24U + config->numEntries * 8U);
    handle->buffer->sgcl.request.entryID                    = config->entryID;
    handle->buffer->sgcl.request.commonHeader.updateActions = 0U;
    handle->buffer->sgcl.request.commonHeader.queryActions  = 0U;
    /* Initialize Stream Gate Control List entry */
    handle->buffer->sgcl.request.cfge.cycleTime = config->cycleTime;
    /* The entry numbers is LIST_LENGTH -1 */
    handle->buffer->sgcl.request.cfge.listLength = (uint8_t)(config->numEntries - 1U);
    handle->buffer->sgcl.request.cfge.extOipv    = config->extOipv;
    handle->buffer->sgcl.request.cfge.extIpv     = config->extIpv;
    handle->buffer->sgcl.request.cfge.extCtd     = config->extCtd;
    handle->buffer->sgcl.request.cfge.extGtst    = config->extGtst;
    (void)memcpy(&handle->buffer->sgcl.request.cfge.ges[0], config->gcList, config->numEntries * 8U);
    cmdBd.req.addr       = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength  = 24U + config->numEntries * 8U;
    cmdBd.req.resLength  = 0U;
    cmdBd.req.tableId    = kNETC_SGCLTable;
    cmdBd.req.cmd        = kNETC_AddEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_DelSGCLTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgcl_req_data_t));
    handle->buffer->sgcl.request.entryID                    = entryID;
    handle->buffer->sgcl.request.commonHeader.updateActions = 0U;
    handle->buffer->sgcl.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                          = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                     = 8U;
    cmdBd.req.resLength                                     = 0U;
    cmdBd.req.tableId                                       = kNETC_SGCLTable;
    cmdBd.req.cmd                                           = kNETC_DeleteEntry;
    cmdBd.req.accessType                                    = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_GetSGCLGateList(netc_cbdr_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length)
{
    status_t status     = kStatus_Success;
    netc_cmd_bd_t cmdBd = {0};
    if (gcl->gcList == NULL)
    {
        return kStatus_InvalidArgument;
    }
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgcl_req_data_t));
    handle->buffer->sgcl.request.entryID                    = gcl->entryID;
    handle->buffer->sgcl.request.commonHeader.updateActions = 0U;
    handle->buffer->sgcl.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                          = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                     = 8U;
    cmdBd.req.resLength                                     = sizeof(netc_tb_sgcl_data_t);
    cmdBd.req.tableId                                       = kNETC_SGCLTable;
    cmdBd.req.cmd                                           = kNETC_QueryEntry;
    cmdBd.req.accessType                                    = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (cmdBd.resp.numMatched != 0U)
        {
            if (((uint32_t)handle->buffer->sgcl.request.cfge.listLength + 1U) > length)
            {
                status = kStatus_InvalidArgument;
            }
            else
            {
                gcl->cycleTime = handle->buffer->sgcl.request.cfge.cycleTime;
                /* The entry numbers is LIST_LENGTH -1 */
                gcl->numEntries = (uint32_t)handle->buffer->sgcl.request.cfge.listLength + 1U;
                gcl->extOipv    = handle->buffer->sgcl.request.cfge.extOipv;
                gcl->extIpv     = handle->buffer->sgcl.request.cfge.extIpv;
                gcl->extCtd     = handle->buffer->sgcl.request.cfge.extCtd;
                gcl->extGtst    = handle->buffer->sgcl.request.cfge.extGtst;
                (void)memcpy(gcl->gcList, &handle->buffer->sgcl.request.cfge.ges[0], gcl->numEntries * 8U);
            }
        }
        else
        {
            status = kStatus_NETC_NotFound;
        }
    }
    return status;
}
status_t NETC_GetSGCLState(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state)
{
    status_t status     = kStatus_Success;
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_sgcl_req_data_t));
    handle->buffer->sgcl.request.entryID                    = entryID;
    handle->buffer->sgcl.request.commonHeader.updateActions = 0U;
    handle->buffer->sgcl.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                          = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                     = 8U;
    cmdBd.req.resLength                                     = sizeof(netc_tb_sgcl_data_t);
    cmdBd.req.tableId                                       = kNETC_SGCLTable;
    cmdBd.req.cmd                                           = kNETC_QueryEntry;
    cmdBd.req.accessType                                    = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *state = handle->buffer->sgcl.response.sgclse;
    }
    return status;
}

status_t NETC_AddOrUpdateRPTableEntry(netc_cbdr_handle_t *handle, netc_tb_rp_config_t *config, netc_tb_cmd_t cmd)
{
    status_t status;
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_rp_req_data_t));
    /* Add or Update entry to Rate Policer Table */
    handle->buffer->rp.request.entryID                    = config->entryID;
    handle->buffer->rp.request.cfge                       = config->cfge;
    handle->buffer->rp.request.fee                        = config->fee;
    handle->buffer->rp.request.commonHeader.updateActions = (uint16_t)kNETC_RPCfgEUpdate | (uint16_t)kNETC_RPFeEUpdate;
    handle->buffer->rp.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = sizeof(netc_tb_rp_req_data_t);
    cmdBd.req.resLength                                   = 0U;
    cmdBd.req.tableId                                     = kNETC_RPTable;
    cmdBd.req.cmd                                         = cmd;

    /* Only support Entry ID Match */
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if ((cmd == kNETC_AddEntry) && (cmdBd.resp.numMatched > 0U))
        {
            status = kStatus_NETC_EntryExists;
        }
        else if ((cmd == kNETC_UpdateEntry) && (cmdBd.resp.numMatched == 0U))
        {
            status = kStatus_NETC_NotFound;
        }
        else
        {
            /* Intentional empty */
        }
    }

    return status;
}

status_t NETC_DelRPTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    (void)memset(handle->buffer, 0, sizeof(netc_tb_rp_req_data_t));
    handle->buffer->rp.request.entryID                    = entryID;
    handle->buffer->rp.request.commonHeader.updateActions = 0;
    handle->buffer->rp.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = 8U;
    cmdBd.req.resLength                                   = 0U;
    cmdBd.req.tableId                                     = kNETC_RPTable;
    cmdBd.req.cmd                                         = kNETC_DeleteEntry;
    cmdBd.req.accessType                                  = kNETC_EntryIDMatch;
    return NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
}

status_t NETC_QueryRPTableEntry(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_rp_rsp_data_t *rsp)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_rp_rsp_data_t));
    handle->buffer->rp.request.entryID                    = entryID;
    handle->buffer->rp.request.commonHeader.updateActions = 0;
    handle->buffer->rp.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = 8U;
    cmdBd.req.resLength                                   = sizeof(netc_tb_rp_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_RPTable;
    cmdBd.req.cmd                                         = kNETC_QueryEntry;
    cmdBd.req.accessType                                  = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        if (cmdBd.resp.numMatched != 0U)
        {
            *rsp = handle->buffer->rp.response;
        }
        else 
        {
            status = kStatus_NETC_NotFound;
        }
    }
    return status;
}

status_t NETC_GetRPStatistic(netc_cbdr_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_Success;
    (void)memset(handle->buffer, 0, sizeof(netc_tb_rp_req_data_t));
    handle->buffer->rp.request.entryID                    = entryID;
    handle->buffer->rp.request.commonHeader.updateActions = 0;
    handle->buffer->rp.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                        = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                   = 8U;
    cmdBd.req.resLength                                   = sizeof(netc_tb_rp_rsp_data_t);
    cmdBd.req.tableId                                     = kNETC_RPTable;
    cmdBd.req.cmd                                         = kNETC_QueryEntry;
    cmdBd.req.accessType                                  = kNETC_EntryIDMatch;
    status = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        *statis = handle->buffer->rp.response.stse;
    }
    return status;
}

status_t NETC_ConfigTGSAdminList(netc_cbdr_handle_t *handle, netc_tb_tgs_gcl_t *config)
{
    status_t status     = kStatus_Success;
    netc_cmd_bd_t cmdBd = {0};

    if ((config->numEntries > NETC_TB_TGS_MAX_ENTRY) || ((config->numEntries != 0U) && (config->gcList == NULL)))
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle->buffer, 0, 28U);
    handle->buffer->tgs.request.entryID                    = config->entryID;
    handle->buffer->tgs.request.commonHeader.updateActions = 1U;
    handle->buffer->tgs.request.commonHeader.queryActions  = 0U;
    /* Initialize port Time Gate Scheduling entry administrative gate control list */
    (void)memcpy((void *)&handle->buffer->tgs.request.cfge, (void *)&config->baseTime, 20);
    if (0U != config->numEntries)
    {
        (void)memcpy((void *)&handle->buffer->tgs.request.cfge.adminGcl[0], (void *)config->gcList,
                     config->numEntries * 8U);
    }
    cmdBd.req.addr       = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength  = 28U + config->numEntries * 8U;
    cmdBd.req.resLength  = 12U;
    cmdBd.req.tableId    = kNETC_TGSTable;
    cmdBd.req.cmd        = kNETC_UpdateEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);

#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051254) && FSL_FEATURE_NETC_HAS_ERRATA_051254
    if (cmdBd.resp.error == 0xd6U)
    {
        /* If a command response with an error code set to 0x0D6 is returned in response to an update command request
         * against an Time Gate Scheduling table entry, software must issue another update command request against the
         * same Time Gate Scheduling table entry, to remove the administrative gate control list from the Time Gate
         * Scheduling table entry. */
        (void)memset(handle->buffer, 0, 28U);
        handle->buffer->tgs.request.cfge.adminControlListLength = 0U;
        handle->buffer->tgs.request.entryID                     = config->entryID;
        handle->buffer->tgs.request.commonHeader.updateActions  = 1U;
        handle->buffer->tgs.request.commonHeader.queryActions   = 0U;
        cmdBd.req.addr                                          = (uintptr_t)handle->buffer;
        cmdBd.req.reqLength                                     = 28U;
        cmdBd.req.resLength                                     = 12U;
        cmdBd.req.tableId                                       = kNETC_TGSTable;
        cmdBd.req.cmd                                           = kNETC_UpdateEntry;
        cmdBd.req.accessType                                    = kNETC_EntryIDMatch;
        (void)NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
#endif
    return status;
}

status_t NETC_GetTGSOperationList(netc_cbdr_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length)
{
    status_t status     = kStatus_Success;
    netc_cmd_bd_t cmdBd = {0};
    uint32_t adminLen;
    netc_tb_tgs_olse_t *resOlseBase;
    if (gcl->gcList == NULL)
    {
        return kStatus_InvalidArgument;
    }
    (void)memset(handle->buffer, 0, sizeof(netc_tb_tgs_data_t));
    handle->buffer->tgs.request.entryID                    = gcl->entryID;
    handle->buffer->tgs.request.commonHeader.updateActions = 0U;
    handle->buffer->tgs.request.commonHeader.queryActions  = 0U;
    cmdBd.req.addr                                         = (uintptr_t)handle->buffer;
    cmdBd.req.reqLength                                    = 8U;
    /* Set Response Data Buffer length to MAX */
    cmdBd.req.resLength  = sizeof(netc_tb_tgs_data_t);
    cmdBd.req.tableId    = kNETC_TGSTable;
    cmdBd.req.cmd        = kNETC_QueryEntry;
    cmdBd.req.accessType = kNETC_EntryIDMatch;
    status               = NETC_CmdBDSendCommand(handle->base, handle->cmdr, &cmdBd, kNETC_NtmpV2_0);
    if (kStatus_Success == status)
    {
        /* Get the administrative gate control list length from Response Data Buffer */
        adminLen    = handle->buffer->tgs.response.cfge.adminControlListLength;
        resOlseBase = (netc_tb_tgs_olse_t *)(uintptr_t)(&((uint8_t *)handle->buffer)[36U + 8U * adminLen]);
        if (resOlseBase->operControlListLength > length)
        {
            status = kStatus_InvalidArgument;
        }
        else
        {
            gcl->baseTime   = resOlseBase->operBaseTime;
            gcl->cycleTime  = resOlseBase->operCycleTime;
            gcl->extTime    = resOlseBase->operCycleTimeExt;
            gcl->numEntries = resOlseBase->operControlListLength;
            /* Copy the Operational gate control list length */
            (void)memcpy(gcl->gcList, &resOlseBase->operGcl[0], (gcl->numEntries * 8U));
        }
    }
    return status;
}
