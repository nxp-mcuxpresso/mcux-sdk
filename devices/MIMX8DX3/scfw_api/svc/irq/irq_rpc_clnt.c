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
 * File containing client-side RPC functions for the IRQ service. These
 * functions are ported to clients that communicate to the SC.
 *
 * @addtogroup IRQ_SVC
 * @{
 */

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"
#include "svc/irq/irq_api.h"
#include "../../main/rpc.h"
#include "svc/irq/irq_rpc.h"

/* Local Defines */

/* Local Types */

/* Local Functions */

sc_err_t sc_irq_enable(sc_ipc_t ipc, sc_rsrc_t resource, sc_irq_group_t group,
    uint32_t mask, sc_bool_t enable)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 3U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_IRQ);
    RPC_FUNC(&msg) = U8(IRQ_FUNC_ENABLE);

    RPC_U32(&msg, 0U) = U32(mask);
    RPC_U16(&msg, 4U) = U16(resource);
    RPC_U8(&msg, 6U) = U8(group);
    RPC_U8(&msg, 7U) = B2U8(enable);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    return err;
}

sc_err_t sc_irq_status(sc_ipc_t ipc, sc_rsrc_t resource, sc_irq_group_t group,
    uint32_t *status)
{
    sc_rpc_msg_t msg;
    sc_err_t err;

    RPC_VER(&msg) = SC_RPC_VERSION;
    RPC_SIZE(&msg) = 2U;
    RPC_SVC(&msg) = U8(SC_RPC_SVC_IRQ);
    RPC_FUNC(&msg) = U8(IRQ_FUNC_STATUS);

    RPC_U16(&msg, 0U) = U16(resource);
    RPC_U8(&msg, 2U) = U8(group);

    sc_call_rpc(ipc, &msg, SC_FALSE);

    err = (sc_err_t) RPC_R8(&msg);

    if (status != NULL)
    {
        *status = (uint32_t) RPC_U32(&msg, 0U);
    }

    return err;
}

/**@}*/

