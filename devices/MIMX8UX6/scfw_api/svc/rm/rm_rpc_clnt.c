/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * File containing client-side RPC functions for the RM service. These
 * functions are ported to clients that communicate to the SC.
 *
 * @addtogroup RM_SVC
 * @{
 */

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"
#include "../../main/rpc.h"
#include "svc/rm/rm_rpc.h"

/* Local Defines */

/* Local Types */

/* Local Functions */

sc_err_t sc_rm_partition_alloc(sc_ipc_t ipc, sc_rm_pt_t *pt, sc_bool_t secure,
    sc_bool_t isolated, sc_bool_t restricted, sc_bool_t grant,
    sc_bool_t coherent)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_PARTITION_ALLOC);

    RPC_U8(&msg, 0U) = B2U8(secure);
    RPC_U8(&msg, 1U) = B2U8(isolated);
    RPC_U8(&msg, 2U) = B2U8(restricted);
    RPC_U8(&msg, 3U) = B2U8(grant);
    RPC_U8(&msg, 4U) = B2U8(coherent);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (pt != NULL)
    {
        *pt = (sc_rm_pt_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_set_confidential(sc_ipc_t ipc, sc_rm_pt_t pt, sc_bool_t retro)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_CONFIDENTIAL);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = B2U8(retro);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_partition_free(sc_ipc_t ipc, sc_rm_pt_t pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_PARTITION_FREE);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_rm_did_t sc_rm_get_did(sc_ipc_t ipc)
{
    sc_rpc_msg_t msg;
    sc_rm_did_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_GET_DID);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_rm_did_t) RPC_R8(&msg);

    return result;
}

sc_err_t sc_rm_partition_static(sc_ipc_t ipc, sc_rm_pt_t pt, sc_rm_did_t did)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_PARTITION_STATIC);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = U8(did);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_partition_lock(sc_ipc_t ipc, sc_rm_pt_t pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_PARTITION_LOCK);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_get_partition(sc_ipc_t ipc, sc_rm_pt_t *pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_GET_PARTITION);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (pt != NULL)
    {
        *pt = (sc_rm_pt_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_set_parent(sc_ipc_t ipc, sc_rm_pt_t pt, sc_rm_pt_t pt_parent)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_PARENT);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = U8(pt_parent);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_move_all(sc_ipc_t ipc, sc_rm_pt_t pt_src, sc_rm_pt_t pt_dst,
    sc_bool_t move_rsrc, sc_bool_t move_pads)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_MOVE_ALL);

    RPC_U8(&msg, 0U) = U8(pt_src);
    RPC_U8(&msg, 1U) = U8(pt_dst);
    RPC_U8(&msg, 2U) = B2U8(move_rsrc);
    RPC_U8(&msg, 3U) = B2U8(move_pads);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_assign_resource(sc_ipc_t ipc, sc_rm_pt_t pt, sc_rsrc_t resource)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_ASSIGN_RESOURCE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_resource_movable(sc_ipc_t ipc, sc_rsrc_t resource_fst,
    sc_rsrc_t resource_lst, sc_bool_t movable)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_RESOURCE_MOVABLE);

    RPC_U16(&msg, 0U) = U16(resource_fst);
    RPC_U16(&msg, 2U) = U16(resource_lst);
    RPC_U8(&msg, 4U) = B2U8(movable);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_subsys_rsrc_movable(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_bool_t movable)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_SUBSYS_RSRC_MOVABLE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = B2U8(movable);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_master_attributes(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_rm_spa_t sa, sc_rm_spa_t pa, sc_bool_t smmu_bypass)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_MASTER_ATTRIBUTES);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(sa);
    RPC_U8(&msg, 3U) = U8(pa);
    RPC_U8(&msg, 4U) = B2U8(smmu_bypass);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_master_sid(sc_ipc_t ipc, sc_rsrc_t resource, sc_rm_sid_t sid)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_MASTER_SID);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U16(&msg, 2U) = U16(sid);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_peripheral_permissions(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_rm_pt_t pt, sc_rm_perm_t perm)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_PERIPHERAL_PERMISSIONS);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(pt);
    RPC_U8(&msg, 3U) = U8(perm);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_bool_t sc_rm_is_resource_owned(sc_ipc_t ipc, sc_rsrc_t resource)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_IS_RESOURCE_OWNED);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

sc_err_t sc_rm_get_resource_owner(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_rm_pt_t *pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_GET_RESOURCE_OWNER);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (pt != NULL)
    {
        *pt = (sc_rm_pt_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_bool_t sc_rm_is_resource_master(sc_ipc_t ipc, sc_rsrc_t resource)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_IS_RESOURCE_MASTER);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

sc_bool_t sc_rm_is_resource_peripheral(sc_ipc_t ipc, sc_rsrc_t resource)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_IS_RESOURCE_PERIPHERAL);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

sc_err_t sc_rm_get_resource_info(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_rm_sid_t *sid)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_GET_RESOURCE_INFO);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (sid != NULL)
    {
        *sid = (sc_rm_sid_t) RPC_U16(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_memreg_alloc(sc_ipc_t ipc, sc_rm_mr_t *mr, sc_faddr_t addr_start,
    sc_faddr_t addr_end)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 5U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_MEMREG_ALLOC);

    RPC_U32(&msg, 0U) = U32(addr_start >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr_start);
    RPC_U32(&msg, 8U) = U32(addr_end >> 32ULL);
    RPC_U32(&msg, 12U) = U32(addr_end);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mr != NULL)
    {
        *mr = (sc_rm_mr_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_memreg_split(sc_ipc_t ipc, sc_rm_mr_t mr, sc_rm_mr_t *mr_ret,
    sc_faddr_t addr_start, sc_faddr_t addr_end)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 6U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_MEMREG_SPLIT);

    RPC_U32(&msg, 0U) = U32(addr_start >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr_start);
    RPC_U32(&msg, 8U) = U32(addr_end >> 32ULL);
    RPC_U32(&msg, 12U) = U32(addr_end);
    RPC_U8(&msg, 16U) = U8(mr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mr_ret != NULL)
    {
        *mr_ret = (sc_rm_mr_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_memreg_frag(sc_ipc_t ipc, sc_rm_mr_t *mr_ret,
    sc_faddr_t addr_start, sc_faddr_t addr_end)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 5U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_MEMREG_FRAG);

    RPC_U32(&msg, 0U) = U32(addr_start >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr_start);
    RPC_U32(&msg, 8U) = U32(addr_end >> 32ULL);
    RPC_U32(&msg, 12U) = U32(addr_end);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mr_ret != NULL)
    {
        *mr_ret = (sc_rm_mr_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_memreg_free(sc_ipc_t ipc, sc_rm_mr_t mr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_MEMREG_FREE);

    RPC_U8(&msg, 0U) = U8(mr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_find_memreg(sc_ipc_t ipc, sc_rm_mr_t *mr, sc_faddr_t addr_start,
    sc_faddr_t addr_end)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 5U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_FIND_MEMREG);

    RPC_U32(&msg, 0U) = U32(addr_start >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr_start);
    RPC_U32(&msg, 8U) = U32(addr_end >> 32ULL);
    RPC_U32(&msg, 12U) = U32(addr_end);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mr != NULL)
    {
        *mr = (sc_rm_mr_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_rm_assign_memreg(sc_ipc_t ipc, sc_rm_pt_t pt, sc_rm_mr_t mr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_ASSIGN_MEMREG);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = U8(mr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_memreg_permissions(sc_ipc_t ipc, sc_rm_mr_t mr, sc_rm_pt_t pt,
    sc_rm_perm_t perm)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_MEMREG_PERMISSIONS);

    RPC_U8(&msg, 0U) = U8(mr);
    RPC_U8(&msg, 1U) = U8(pt);
    RPC_U8(&msg, 2U) = U8(perm);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_bool_t sc_rm_is_memreg_owned(sc_ipc_t ipc, sc_rm_mr_t mr)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_IS_MEMREG_OWNED);

    RPC_U8(&msg, 0U) = U8(mr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

sc_err_t sc_rm_get_memreg_info(sc_ipc_t ipc, sc_rm_mr_t mr,
    sc_faddr_t *addr_start, sc_faddr_t *addr_end)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_GET_MEMREG_INFO);

    RPC_U8(&msg, 0U) = U8(mr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (addr_start != NULL)
    {
        *addr_start = (sc_faddr_t) RPC_U64(&msg, 0U);
    }
    if (addr_end != NULL)
    {
        *addr_end = (sc_faddr_t) RPC_U64(&msg, 8U);
    }

    return err;
}

sc_err_t sc_rm_assign_pad(sc_ipc_t ipc, sc_rm_pt_t pt, sc_pad_t pad)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_ASSIGN_PAD);

    RPC_U16(&msg, 0U) = U16(pad);
    RPC_U8(&msg, 2U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_rm_set_pad_movable(sc_ipc_t ipc, sc_pad_t pad_fst, sc_pad_t pad_lst,
    sc_bool_t movable)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_SET_PAD_MOVABLE);

    RPC_U16(&msg, 0U) = U16(pad_fst);
    RPC_U16(&msg, 2U) = U16(pad_lst);
    RPC_U8(&msg, 4U) = B2U8(movable);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_bool_t sc_rm_is_pad_owned(sc_ipc_t ipc, sc_pad_t pad)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_IS_PAD_OWNED);

    RPC_U8(&msg, 0U) = U8(pad);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

void sc_rm_dump(sc_ipc_t ipc)
{
    sc_rpc_msg_t msg;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_RM);
    RPC_FUNC(&msg) = U8(RM_FUNC_DUMP);

    sc_call_rpc(ipc, &msg, SC_FALSE);
}

/**@}*/

