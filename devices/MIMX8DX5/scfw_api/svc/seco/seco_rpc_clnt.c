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
 * File containing client-side RPC functions for the SECO service. These
 * functions are ported to clients that communicate to the SC.
 *
 * @addtogroup SECO_SVC
 * @{
 */

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"
#include "svc/seco/seco_api.h"
#include "../../main/rpc.h"
#include "svc/seco/seco_rpc.h"

/* Local Defines */

/* Local Types */

/* Local Functions */

sc_err_t sc_seco_image_load(sc_ipc_t ipc, sc_faddr_t addr_src,
    sc_faddr_t addr_dst, uint32_t len, sc_bool_t fw)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 7U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_IMAGE_LOAD);

    RPC_U32(&msg, 0U) = U32(addr_src >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr_src);
    RPC_U32(&msg, 8U) = U32(addr_dst >> 32ULL);
    RPC_U32(&msg, 12U) = U32(addr_dst);
    RPC_U32(&msg, 16U) = U32(len);
    RPC_U8(&msg, 20U) = B2U8(fw);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_authenticate(sc_ipc_t ipc, sc_seco_auth_cmd_t cmd,
    sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_AUTHENTICATE);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);
    RPC_U8(&msg, 8U) = U8(cmd);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_enh_authenticate(sc_ipc_t ipc, sc_seco_auth_cmd_t cmd,
    sc_faddr_t addr, uint32_t mask1, uint32_t mask2)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 6U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_ENH_AUTHENTICATE);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);
    RPC_U32(&msg, 8U) = U32(mask1);
    RPC_U32(&msg, 12U) = U32(mask2);
    RPC_U8(&msg, 16U) = U8(cmd);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_forward_lifecycle(sc_ipc_t ipc, uint32_t change)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_FORWARD_LIFECYCLE);

    RPC_U32(&msg, 0U) = U32(change);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_return_lifecycle(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_RETURN_LIFECYCLE);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_commit(sc_ipc_t ipc, uint32_t *info)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_COMMIT);

    RPC_U32(&msg, 0U) = U32(*info);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    *info = (uint32_t) RPC_U32(&msg, 0U);

    return err;
}

sc_err_t sc_seco_attest_mode(sc_ipc_t ipc, uint32_t mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_ATTEST_MODE);

    RPC_U32(&msg, 0U) = U32(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_attest(sc_ipc_t ipc, uint64_t nonce)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_ATTEST);

    RPC_U32(&msg, 0U) = U32(nonce >> 32ULL);
    RPC_U32(&msg, 4U) = U32(nonce);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_get_attest_pkey(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GET_ATTEST_PKEY);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_get_attest_sign(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GET_ATTEST_SIGN);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_attest_verify(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_ATTEST_VERIFY);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_gen_key_blob(sc_ipc_t ipc, uint32_t id, sc_faddr_t load_addr,
    sc_faddr_t export_addr, uint16_t max_size)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 7U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GEN_KEY_BLOB);

    RPC_U32(&msg, 0U) = U32(load_addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(load_addr);
    RPC_U32(&msg, 8U) = U32(export_addr >> 32ULL);
    RPC_U32(&msg, 12U) = U32(export_addr);
    RPC_U32(&msg, 16U) = U32(id);
    RPC_U16(&msg, 20U) = U16(max_size);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_load_key(sc_ipc_t ipc, uint32_t id, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_LOAD_KEY);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);
    RPC_U32(&msg, 8U) = U32(id);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_get_mp_key(sc_ipc_t ipc, sc_faddr_t dst_addr,
    uint16_t dst_size)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GET_MP_KEY);

    RPC_U32(&msg, 0U) = U32(dst_addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(dst_addr);
    RPC_U16(&msg, 8U) = U16(dst_size);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_update_mpmr(sc_ipc_t ipc, sc_faddr_t addr, uint8_t size,
    uint8_t lock)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_UPDATE_MPMR);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);
    RPC_U8(&msg, 8U) = U8(size);
    RPC_U8(&msg, 9U) = U8(lock);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_get_mp_sign(sc_ipc_t ipc, sc_faddr_t msg_addr,
    uint16_t msg_size, sc_faddr_t dst_addr, uint16_t dst_size)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 6U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GET_MP_SIGN);

    RPC_U32(&msg, 0U) = U32(msg_addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(msg_addr);
    RPC_U32(&msg, 8U) = U32(dst_addr >> 32ULL);
    RPC_U32(&msg, 12U) = U32(dst_addr);
    RPC_U16(&msg, 16U) = U16(msg_size);
    RPC_U16(&msg, 18U) = U16(dst_size);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

void sc_seco_build_info(sc_ipc_t ipc, uint32_t *version, uint32_t *commit)
{
    sc_rpc_msg_t msg;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_BUILD_INFO);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    if (version != NULL)
    {
        *version = (uint32_t) RPC_U32(&msg, 0U);
    }
    if (commit != NULL)
    {
        *commit = (uint32_t) RPC_U32(&msg, 4U);
    }
}

sc_err_t sc_seco_chip_info(sc_ipc_t ipc, uint16_t *lc, uint16_t *monotonic,
    uint32_t *uid_l, uint32_t *uid_h)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_CHIP_INFO);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (uid_l != NULL)
    {
        *uid_l = (uint32_t) RPC_U32(&msg, 0U);
    }
    if (uid_h != NULL)
    {
        *uid_h = (uint32_t) RPC_U32(&msg, 4U);
    }
    if (lc != NULL)
    {
        *lc = (uint16_t) RPC_U16(&msg, 8U);
    }
    if (monotonic != NULL)
    {
        *monotonic = (uint16_t) RPC_U16(&msg, 10U);
    }

    return err;
}

sc_err_t sc_seco_enable_debug(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_ENABLE_DEBUG);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_get_event(sc_ipc_t ipc, uint8_t idx, uint32_t *event)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_GET_EVENT);

    RPC_U8(&msg, 0U) = U8(idx);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (event != NULL)
    {
        *event = (uint32_t) RPC_U32(&msg, 0U);
    }

    return err;
}

sc_err_t sc_seco_fuse_write(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_FUSE_WRITE);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_patch(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_PATCH);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_start_rng(sc_ipc_t ipc, sc_seco_rng_stat_t *status)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_START_RNG);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (status != NULL)
    {
        *status = (sc_seco_rng_stat_t) RPC_U32(&msg, 0U);
    }

    return err;
}

sc_err_t sc_seco_sab_msg(sc_ipc_t ipc, sc_faddr_t addr)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_SAB_MSG);

    RPC_U32(&msg, 0U) = U32(addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(addr);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_secvio_enable(sc_ipc_t ipc)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_SECVIO_ENABLE);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_seco_secvio_config(sc_ipc_t ipc, uint8_t id, uint8_t access,
    uint32_t *data0, uint32_t *data1, uint32_t *data2, uint32_t *data3,
    uint32_t *data4, uint8_t size)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 7U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_SECVIO_CONFIG);

    RPC_U32(&msg, 0U) = U32(*data0);
    RPC_U32(&msg, 4U) = U32(*data1);
    RPC_U32(&msg, 8U) = U32(*data2);
    RPC_U32(&msg, 12U) = U32(*data3);
    RPC_U32(&msg, 16U) = U32(*data4);
    RPC_U8(&msg, 20U) = U8(id);
    RPC_U8(&msg, 21U) = U8(access);
    RPC_U8(&msg, 22U) = U8(size);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    *data0 = (uint32_t) RPC_U32(&msg, 0U);
    *data1 = (uint32_t) RPC_U32(&msg, 4U);
    *data2 = (uint32_t) RPC_U32(&msg, 8U);
    *data3 = (uint32_t) RPC_U32(&msg, 12U);
    *data4 = (uint32_t) RPC_U32(&msg, 16U);

    return err;
}

sc_err_t sc_seco_secvio_dgo_config(sc_ipc_t ipc, uint8_t id, uint8_t access,
    uint32_t *data)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_SECO);
    RPC_FUNC(&msg) = U8(SECO_FUNC_SECVIO_DGO_CONFIG);

    RPC_U32(&msg, 0U) = U32(*data);
    RPC_U8(&msg, 4U) = U8(id);
    RPC_U8(&msg, 5U) = U8(access);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    *data = (uint32_t) RPC_U32(&msg, 0U);

    return err;
}

/**@}*/

