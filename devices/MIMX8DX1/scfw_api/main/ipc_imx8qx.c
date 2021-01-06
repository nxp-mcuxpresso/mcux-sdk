/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "MIMX8DX1_cm4.h"
#include "main/ipc.h"
#include "main/rpc.h"
#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.scfwapi"
#endif

/*----------------------------------------------------------------------*/
/* RPC command/response                                                 */
/*----------------------------------------------------------------------*/
void sc_call_rpc(sc_ipc_t ipc, sc_rpc_msg_t *msg, sc_bool_t no_resp)
{
#ifdef FSL_RTOS_FREE_RTOS
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        /* Suspends the scheduler to make sure there's only one rpc call ongoing at a time. */
        vTaskSuspendAll();
    }
#endif
    sc_ipc_write(ipc, msg);
    if (!no_resp)
    {
        sc_ipc_read(ipc, msg);
    }
#ifdef FSL_RTOS_FREE_RTOS
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        (void)xTaskResumeAll();
    }
#endif
}

/*--------------------------------------------------------------------------*/
/* Open an IPC channel                                                      */
/*--------------------------------------------------------------------------*/
sc_err_t sc_ipc_open(sc_ipc_t *ipc, sc_ipc_id_t id)
{
    MU_Type *base = (MU_Type *)id;

    /* get mu base associated with ipc channel */
    if ((ipc == NULL) || (base == NULL))
    {
        return SC_ERR_IPC;
    }

    /* Clear GIEn, RIEn, TIEn, GIRn and ABFn. */
    base->CR &= ~(MU_CR_GIEn_MASK | MU_CR_RIEn_MASK | MU_CR_TIEn_MASK | MU_CR_GIRn_MASK | MU_CR_Fn_MASK);

    /* Return MU address as handle */
    *ipc = (sc_ipc_t)id;

    return SC_ERR_NONE;
}

/*--------------------------------------------------------------------------*/
/* Close an IPC channel                                                     */
/*--------------------------------------------------------------------------*/
void sc_ipc_close(sc_ipc_t ipc)
{
}

/*--------------------------------------------------------------------------*/
/* Read message from an IPC channel                                         */
/*--------------------------------------------------------------------------*/
void sc_ipc_read(sc_ipc_t ipc, void *data)
{
    MU_Type *base     = (MU_Type *)ipc;
    sc_rpc_msg_t *msg = (sc_rpc_msg_t *)data;
    uint8_t count     = 0;

    /* Check parms */
    if ((base == NULL) || (msg == NULL))
    {
        return;
    }

    /* Read first word */
    /* Wait RX register to be full. */
    while ((base->SR & (1UL << (MU_SR_RFn_SHIFT + 3U))) == 0U)
    {
    }
    msg->header = base->RR[0];
    count++;

    /* Check size */
    if (msg->size > SC_RPC_MAX_MSG)
    {
        msg->header = 0;
        return;
    }

    /* Read remaining words */
    while (count < msg->size)
    {
        /* Wait RX register to be full. */
        while ((base->SR & (1UL << (MU_SR_RFn_SHIFT + 3U - count % MU_RR_COUNT))) == 0U)
        {
        }
        msg->DATA.u32[count - 1U] = base->RR[count % MU_RR_COUNT];
        count++;
    }
}

/*--------------------------------------------------------------------------*/
/* Write a message to an IPC channel                                        */
/*--------------------------------------------------------------------------*/
void sc_ipc_write(sc_ipc_t ipc, const void *data)
{
    MU_Type *base           = (MU_Type *)ipc;
    const sc_rpc_msg_t *msg = (const sc_rpc_msg_t *)data;
    uint8_t count           = 0;

    /* Check parms */
    if ((base == NULL) || (msg == NULL))
    {
        return;
    }

    /* Check size */
    if (msg->size > SC_RPC_MAX_MSG)
    {
        return;
    }

    /* Write first word */
    while ((base->SR & (1UL << (MU_SR_TEn_SHIFT + 3U))) == 0U)
    {
    }
    base->TR[0] = msg->header;
    count++;

    /* Write remaining words */
    while (count < msg->size)
    {
        /* Wait Tx register to be empty and send Tx Data. */
        while ((base->SR & (1UL << (MU_SR_TEn_SHIFT + 3U - count % MU_TR_COUNT))) == 0U)
        {
        }
        base->TR[count % MU_TR_COUNT] = msg->DATA.u32[count - 1U];
        count++;
    }
}
