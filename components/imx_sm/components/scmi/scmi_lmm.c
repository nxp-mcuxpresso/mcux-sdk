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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_LMM

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get logical machine attributes                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmAttributes(uint32_t channel, uint32_t *lmId,
    uint32_t *attributes, uint32_t *state, int32_t *errStatus,
    uint8_t *name)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t lmId;
        uint32_t attributes;
        uint32_t state;
        int32_t errStatus;
        uint8_t name[SCMI_LMM_MAX_NAME];
    } msg_rlmmd3_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInit(channel, &msg);

    /* Check lmId pointer */
    if ((status == SCMI_ERR_SUCCESS) && (lmId == NULL))
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Request message structure */
        typedef struct
        {
            uint32_t header;
            uint32_t lmId;
        } msg_tlmmd3_t;
        msg_tlmmd3_t *msgTx = (msg_tlmmd3_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = *lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_LMM_ATTRIBUTES, sizeof(msg_tlmmd3_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rlmmd3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rlmmd3_t *msgRx = (const msg_rlmmd3_t*) msg;

        /* Extract lmId */
        *lmId = msgRx->lmId;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract state */
        if (state != NULL)
        {
            *state = msgRx->state;
        }

        /* Extract errStatus */
        if (errStatus != NULL)
        {
            *errStatus = msgRx->errStatus;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_LMM_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Boot (power on and start) an LM                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmBoot(uint32_t channel, uint32_t lmId)
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
            uint32_t lmId;
        } msg_tlmmd4_t;
        msg_tlmmd4_t *msgTx = (msg_tlmmd4_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_BOOT,
            sizeof(msg_tlmmd4_t), &header);
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
/* Reset an LM                                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmReset(uint32_t channel, uint32_t lmId, uint32_t flags)
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
            uint32_t lmId;
            uint32_t flags;
        } msg_tlmmd5_t;
        msg_tlmmd5_t *msgTx = (msg_tlmmd5_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_RESET,
            sizeof(msg_tlmmd5_t), &header);
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
/* Shutdown (power off) an LM                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmShutdown(uint32_t channel, uint32_t lmId, uint32_t flags)
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
            uint32_t lmId;
            uint32_t flags;
        } msg_tlmmd6_t;
        msg_tlmmd6_t *msgTx = (msg_tlmmd6_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_LMM_SHUTDOWN, sizeof(msg_tlmmd6_t), &header);
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
/* Wake (resume) an LM from a low power state                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmWake(uint32_t channel, uint32_t lmId)
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
            uint32_t lmId;
        } msg_tlmmd7_t;
        msg_tlmmd7_t *msgTx = (msg_tlmmd7_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_WAKE,
            sizeof(msg_tlmmd7_t), &header);
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
/* Request an LM gracefully suspend (sleep)                                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmSuspend(uint32_t channel, uint32_t lmId)
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
            uint32_t lmId;
        } msg_tlmmd8_t;
        msg_tlmmd8_t *msgTx = (msg_tlmmd8_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_SUSPEND,
            sizeof(msg_tlmmd8_t), &header);
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
/* Configure LM notifications                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmNotify(uint32_t channel, uint32_t lmId, uint32_t flags)
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
            uint32_t lmId;
            uint32_t flags;
        } msg_tlmmd9_t;
        msg_tlmmd9_t *msgTx = (msg_tlmmd9_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_NOTIFY,
            sizeof(msg_tlmmd9_t), &header);
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
/* Read the reason the LM last booted/shutdown/reset                        */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmResetReason(uint32_t channel, uint32_t lmId,
    uint32_t *bootFlags, uint32_t *shutdownFlags, uint32_t *extInfo)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t bootFlags;
        uint32_t shutdownFlags;
        uint32_t extInfo[SCMI_LMM_MAX_EXTINFO];
    } msg_rlmmd10_t;

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
            uint32_t lmId;
        } msg_tlmmd10_t;
        msg_tlmmd10_t *msgTx = (msg_tlmmd10_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_LMM_RESET_REASON, sizeof(msg_tlmmd10_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel,
            sizeof(msg_status_t) + sizeof(uint32_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rlmmd10_t *msgRx = (const msg_rlmmd10_t*) msg;

        /* Extract bootFlags */
        if (bootFlags != NULL)
        {
            *bootFlags = msgRx->bootFlags;
        }

        /* Extract shutdownFlags */
        if (shutdownFlags != NULL)
        {
            *shutdownFlags = msgRx->shutdownFlags;
        }

        /* Extract extInfo */
        if (extInfo != NULL)
        {
            SCMI_MemCpy((uint8_t*) extInfo, (uint8_t*) &msgRx->extInfo,
                (SCMI_LMM_NUM_EXTINFO * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Power up an LM                                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmPowerOn(uint32_t channel, uint32_t lmId)
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
            uint32_t lmId;
        } msg_tlmmd11_t;
        msg_tlmmd11_t *msgTx = (msg_tlmmd11_t*) msg;

        /* Fill in parameters */
        msgTx->lmId = lmId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_LMM_POWER_ON, sizeof(msg_tlmmd11_t), &header);
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
int32_t SCMI_LmmNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read LM notification event                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_LmmEvent(uint32_t channel, uint32_t *lmId, uint32_t *eventLm,
    uint32_t *flags)
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
            uint32_t lmId;
            uint32_t eventLm;
            uint32_t flags;
        } msg_rlmmed32_t;
        const msg_rlmmed32_t *msgRx = (const msg_rlmmed32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL, SCMI_MSG_LMM_EVENT,
            sizeof(msg_rlmmed32_t), &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract lmId */
            if (lmId != NULL)
            {
                *lmId = msgRx->lmId;
            }

            /* Extract eventLm */
            if (eventLm != NULL)
            {
                *eventLm = msgRx->eventLm;
            }

            /* Extract flags */
            if (flags != NULL)
            {
                *flags = msgRx->flags;
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

