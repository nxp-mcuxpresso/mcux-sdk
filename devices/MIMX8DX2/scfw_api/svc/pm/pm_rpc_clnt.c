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
 * File containing client-side RPC functions for the PM service. These
 * functions are ported to clients that communicate to the SC.
 *
 * @addtogroup PM_SVC
 * @{
 */

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"
#include "svc/pm/pm_api.h"
#include "../../main/rpc.h"
#include "svc/pm/pm_rpc.h"

/* Local Defines */

/* Local Types */

/* Local Functions */

sc_err_t sc_pm_set_sys_power_mode(sc_ipc_t ipc, sc_pm_power_mode_t mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_SYS_POWER_MODE);

    RPC_U8(&msg, 0U) = U8(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_partition_power_mode(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_power_mode_t mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_PARTITION_POWER_MODE);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = U8(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_get_sys_power_mode(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_power_mode_t *mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_GET_SYS_POWER_MODE);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mode != NULL)
    {
        *mode = (sc_pm_power_mode_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_partition_wake(sc_ipc_t ipc, sc_rm_pt_t pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_PARTITION_WAKE);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_resource_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_RESOURCE_POWER_MODE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_resource_power_mode_all(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_power_mode_t mode, sc_rsrc_t exclude)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_RESOURCE_POWER_MODE_ALL);

    RPC_U16(&msg, 0U) = U16(exclude);
    RPC_U8(&msg, 2U) = U8(pt);
    RPC_U8(&msg, 3U) = U8(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_get_resource_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t *mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_GET_RESOURCE_POWER_MODE);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (mode != NULL)
    {
        *mode = (sc_pm_power_mode_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_req_low_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REQ_LOW_POWER_MODE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(mode);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_req_cpu_low_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode, sc_pm_wake_src_t wake_src)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REQ_CPU_LOW_POWER_MODE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(mode);
    RPC_U8(&msg, 3U) = U8(wake_src);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_cpu_resume_addr(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_faddr_t address)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_CPU_RESUME_ADDR);

    RPC_U32(&msg, 0U) = U32(address >> 32ULL);
    RPC_U32(&msg, 4U) = U32(address);
    RPC_U16(&msg, 8U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_cpu_resume(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_bool_t isPrimary, sc_faddr_t address)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_CPU_RESUME);

    RPC_U32(&msg, 0U) = U32(address >> 32ULL);
    RPC_U32(&msg, 4U) = U32(address);
    RPC_U16(&msg, 8U) = U16(resource);
    RPC_U8(&msg, 10U) = B2U8(isPrimary);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_req_sys_if_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_sys_if_t sys_if, sc_pm_power_mode_t hpm, sc_pm_power_mode_t lpm)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REQ_SYS_IF_POWER_MODE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(sys_if);
    RPC_U8(&msg, 3U) = U8(hpm);
    RPC_U8(&msg, 4U) = U8(lpm);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_clock_rate(sc_ipc_t ipc, sc_rsrc_t resource, sc_pm_clk_t clk,
    sc_pm_clock_rate_t *rate)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_CLOCK_RATE);

    RPC_U32(&msg, 0U) = U32(*rate);
    RPC_U16(&msg, 4U) = U16(resource);
    RPC_U8(&msg, 6U) = U8(clk);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    *rate = (sc_pm_clock_rate_t) RPC_U32(&msg, 0U);

    return err;
}

sc_err_t sc_pm_get_clock_rate(sc_ipc_t ipc, sc_rsrc_t resource, sc_pm_clk_t clk,
    sc_pm_clock_rate_t *rate)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_GET_CLOCK_RATE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(clk);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (rate != NULL)
    {
        *rate = (sc_pm_clock_rate_t) RPC_U32(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_clock_enable(sc_ipc_t ipc, sc_rsrc_t resource, sc_pm_clk_t clk,
    sc_bool_t enable, sc_bool_t autog)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_CLOCK_ENABLE);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(clk);
    RPC_U8(&msg, 3U) = B2U8(enable);
    RPC_U8(&msg, 4U) = B2U8(autog);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_clock_parent(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clk_parent_t parent)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_CLOCK_PARENT);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(clk);
    RPC_U8(&msg, 3U) = U8(parent);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_get_clock_parent(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clk_parent_t *parent)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_GET_CLOCK_PARENT);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(clk);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (parent != NULL)
    {
        *parent = (sc_pm_clk_parent_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_reset(sc_ipc_t ipc, sc_pm_reset_type_t type)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_RESET);

    RPC_U8(&msg, 0U) = U8(type);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_reset_reason(sc_ipc_t ipc, sc_pm_reset_reason_t *reason)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_RESET_REASON);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (reason != NULL)
    {
        *reason = (sc_pm_reset_reason_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_get_reset_part(sc_ipc_t ipc, sc_rm_pt_t *pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 1U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_GET_RESET_PART);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (pt != NULL)
    {
        *pt = (sc_rm_pt_t) RPC_U8(&msg, 0U);
    }

    return err;
}

sc_err_t sc_pm_boot(sc_ipc_t ipc, sc_rm_pt_t pt, sc_rsrc_t resource_cpu,
    sc_faddr_t boot_addr, sc_rsrc_t resource_mu, sc_rsrc_t resource_dev)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 5U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_BOOT);

    RPC_U32(&msg, 0U) = U32(boot_addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(boot_addr);
    RPC_U16(&msg, 8U) = U16(resource_cpu);
    RPC_U16(&msg, 10U) = U16(resource_mu);
    RPC_U16(&msg, 12U) = U16(resource_dev);
    RPC_U8(&msg, 14U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_set_boot_parm(sc_ipc_t ipc, sc_rsrc_t resource_cpu,
    sc_faddr_t boot_addr, sc_rsrc_t resource_mu, sc_rsrc_t resource_dev)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 5U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_SET_BOOT_PARM);

    RPC_U32(&msg, 0U) = U32(boot_addr >> 32ULL);
    RPC_U32(&msg, 4U) = U32(boot_addr);
    RPC_U16(&msg, 8U) = U16(resource_cpu);
    RPC_U16(&msg, 10U) = U16(resource_mu);
    RPC_U16(&msg, 12U) = U16(resource_dev);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

void sc_pm_reboot(sc_ipc_t ipc, sc_pm_reset_type_t type)
{
    sc_rpc_msg_t msg;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REBOOT);

    RPC_U8(&msg, 0U) = U8(type);

    sc_call_rpc(ipc, &msg, SC_TRUE);
}

sc_err_t sc_pm_reboot_partition(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_reset_type_t type)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REBOOT_PARTITION);

    RPC_U8(&msg, 0U) = U8(pt);
    RPC_U8(&msg, 1U) = U8(type);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_reboot_continue(sc_ipc_t ipc, sc_rm_pt_t pt)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_REBOOT_CONTINUE);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_pm_cpu_start(sc_ipc_t ipc, sc_rsrc_t resource, sc_bool_t enable,
    sc_faddr_t address)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_CPU_START);

    RPC_U32(&msg, 0U) = U32(address >> 32ULL);
    RPC_U32(&msg, 4U) = U32(address);
    RPC_U16(&msg, 8U) = U16(resource);
    RPC_U8(&msg, 10U) = B2U8(enable);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

void sc_pm_cpu_reset(sc_ipc_t ipc, sc_rsrc_t resource, sc_faddr_t address)
{
    sc_rpc_msg_t msg;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 4U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_CPU_RESET);

    RPC_U32(&msg, 0U) = U32(address >> 32ULL);
    RPC_U32(&msg, 4U) = U32(address);
    RPC_U16(&msg, 8U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_TRUE);
}

sc_err_t sc_pm_resource_reset(sc_ipc_t ipc, sc_rsrc_t resource)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_RESOURCE_RESET);

    RPC_U16(&msg, 0U) = U16(resource);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_bool_t sc_pm_is_partition_started(sc_ipc_t ipc, sc_rm_pt_t pt)
{
    sc_rpc_msg_t msg;
    sc_bool_t result;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_PM);
    RPC_FUNC(&msg) = U8(PM_FUNC_IS_PARTITION_STARTED);

    RPC_U8(&msg, 0U) = U8(pt);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    result = (sc_bool_t) U2B(RPC_R8(&msg));

    return result;
}

/**@}*/

