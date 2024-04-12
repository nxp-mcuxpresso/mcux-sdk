/*
** ###################################################################
**
** Copyright 2023-2024 NXP
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** o Redistributions of source code must retain the above copyright notice, this list
**   of conditions and the following disclaimer.
**
** o Redistributions in binary form must reproduce the above copyright notice, this
**   list of conditions and the following disclaimer in the documentation and/or
**   other materials provided with the distribution.
**
** o Neither the name of the copyright holder nor the names of its
**   contributors may be used to endorse or promote products derived from this
**   software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
** ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

/* Includes */

#include "scmi.h"
#include "scmi_internal.h"

/* Local defines */

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_SYS

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SysProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SysProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SysProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Set system power state                                                   */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SystemPowerStateSet(uint32_t channel, uint32_t flags,
    uint32_t systemState)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInit(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Request message structure */
        typedef struct
        {
            uint32_t header;
            uint32_t flags;
            uint32_t systemState;
        } msg_tsysd3_t;
        msg_tsysd3_t *msgTx = (msg_tsysd3_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;
        msgTx->systemState = systemState;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SYSTEM_POWER_STATE_SET, sizeof(msg_tsysd3_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_status_t), header);
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Configure system state notifications                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SystemPowerStateNotify(uint32_t channel,
    uint32_t notifyEnable)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInit(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Request message structure */
        typedef struct
        {
            uint32_t header;
            uint32_t notifyEnable;
        } msg_tsysd5_t;
        msg_tsysd5_t *msgTx = (msg_tsysd5_t*) msg;

        /* Fill in parameters */
        msgTx->notifyEnable = notifyEnable;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SYSTEM_POWER_STATE_NOTIFY, sizeof(msg_tsysd5_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_status_t), header);
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Negotiate the protocol version                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SysNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read system state notification event                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SystemPowerStateNotifier(uint32_t channel, uint32_t *agentId,
    uint32_t *flags, uint32_t *systemState, uint32_t *timeout)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Acquire lock */
    SCMI_P2A_LOCK(channel);

    /* Get transport buffer address */
    msg = SCMI_HdrAddrGet(channel);

    /* Read message */
    {
        /* Read message structure */
        typedef struct
        {
            uint32_t header;
            uint32_t agentId;
            uint32_t flags;
            uint32_t systemState;
            uint32_t timeout;
        } msg_rsysed32_t;
        const msg_rsysed32_t *msgRx = (const msg_rsysed32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SYSTEM_POWER_STATE_NOTIFIER, sizeof(msg_rsysed32_t),
            &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract agentId */
            if (agentId != NULL)
            {
                *agentId = msgRx->agentId;
            }

            /* Extract flags */
            if (flags != NULL)
            {
                *flags = msgRx->flags;
            }

            /* Extract systemState */
            if (systemState != NULL)
            {
                *systemState = msgRx->systemState;
            }

            /* Extract timeout */
            if (timeout != NULL)
            {
                *timeout = msgRx->timeout;
            }
        }
    }

    /* Send response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_P2aTx(channel, sizeof(header), header);
    }

    /* Release lock */
    SCMI_P2A_UNLOCK(channel);

    /* Return status */
    return status;
}

