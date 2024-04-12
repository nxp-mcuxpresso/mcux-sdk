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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_FUSA

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaProtocolAttributes(uint32_t channel, uint32_t *attributes1,
    uint32_t *attributes2)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t attributes1;
        uint32_t attributes2;
    } msg_rfusad1_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PROTOCOL_ATTRIBUTES, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rfusad1_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rfusad1_t *msgRx = (const msg_rfusad1_t*) msg;

        /* Extract attributes1 */
        if (attributes1 != NULL)
        {
            *attributes1 = msgRx->attributes1;
        }

        /* Extract attributes2 */
        if (attributes2 != NULL)
        {
            *attributes2 = msgRx->attributes2;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get current FuSa system state                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFeenvStateGet(uint32_t channel, uint32_t *feenvState,
    uint32_t *mselMode)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t feenvState;
        uint32_t mselMode;
    } msg_rfusad3_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FEENV_STATE_GET, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rfusad3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rfusad3_t *msgRx = (const msg_rfusad3_t*) msg;

        /* Extract feenvState */
        if (feenvState != NULL)
        {
            *feenvState = msgRx->feenvState;
        }

        /* Extract mselMode */
        if (mselMode != NULL)
        {
            *mselMode = msgRx->mselMode;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Configure F-EENV notifications                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFeenvStateNotify(uint32_t channel, uint32_t notifyEnable)
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
        } msg_tfusad5_t;
        msg_tfusad5_t *msgTx = (msg_tfusad5_t*) msg;

        /* Fill in parameters */
        msgTx->notifyEnable = notifyEnable;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FEENV_STATE_NOTIFY, sizeof(msg_tfusad5_t),
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
/* Get S-EENV state                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaSeenvStateGet(uint32_t channel, uint32_t *seenvId,
    uint32_t *lmId, uint32_t *seenvState)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t seenvId;
        uint32_t lmId;
        uint32_t seenvState;
    } msg_rfusad6_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInit(channel, &msg);

    /* Check seenvId pointer */
    if ((status == SCMI_ERR_SUCCESS) && (seenvId == NULL))
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
            uint32_t seenvId;
        } msg_tfusad6_t;
        msg_tfusad6_t *msgTx = (msg_tfusad6_t*) msg;

        /* Fill in parameters */
        msgTx->seenvId = *seenvId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_SEENV_STATE_GET, sizeof(msg_tfusad6_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rfusad6_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rfusad6_t *msgRx = (const msg_rfusad6_t*) msg;

        /* Extract seenvId */
        *seenvId = msgRx->seenvId;

        /* Extract lmId */
        if (lmId != NULL)
        {
            *lmId = msgRx->lmId;
        }

        /* Extract seenvState */
        if (seenvState != NULL)
        {
            *seenvState = msgRx->seenvState;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set S-EENV state                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaSeenvStateSet(uint32_t channel, uint32_t seenvState,
    uint32_t pingCookie)
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
            uint32_t seenvState;
            uint32_t pingCookie;
        } msg_tfusad7_t;
        msg_tfusad7_t *msgTx = (msg_tfusad7_t*) msg;

        /* Fill in parameters */
        msgTx->seenvState = seenvState;
        msgTx->pingCookie = pingCookie;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_SEENV_STATE_SET, sizeof(msg_tfusad7_t), &header);
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
/* Get fault state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFaultGet(uint32_t channel, uint32_t faultId,
    uint32_t *flags)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t flags;
    } msg_rfusad8_t;

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
            uint32_t faultId;
        } msg_tfusad8_t;
        msg_tfusad8_t *msgTx = (msg_tfusad8_t*) msg;

        /* Fill in parameters */
        msgTx->faultId = faultId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FAULT_GET, sizeof(msg_tfusad8_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rfusad8_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rfusad8_t *msgRx = (const msg_rfusad8_t*) msg;

        /* Extract flags */
        if (flags != NULL)
        {
            *flags = msgRx->flags;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set fault state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFaultSet(uint32_t channel, uint32_t faultId,
    uint32_t flags)
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
            uint32_t faultId;
            uint32_t flags;
        } msg_tfusad9_t;
        msg_tfusad9_t *msgTx = (msg_tfusad9_t*) msg;

        /* Fill in parameters */
        msgTx->faultId = faultId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FAULT_SET, sizeof(msg_tfusad9_t), &header);
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
/* Enable/disable fault notifications                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFaultGroupNotify(uint32_t channel, uint32_t faultIdFirst,
    uint32_t faultMask, uint32_t notifyEnable, uint32_t *faultIdFirstGet,
    uint32_t *notifyEnabled)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t faultIdFirstGet;
        uint32_t notifyEnabled;
    } msg_rfusad10_t;

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
            uint32_t faultIdFirst;
            uint32_t faultMask;
            uint32_t notifyEnable;
        } msg_tfusad10_t;
        msg_tfusad10_t *msgTx = (msg_tfusad10_t*) msg;

        /* Fill in parameters */
        msgTx->faultIdFirst = faultIdFirst;
        msgTx->faultMask = faultMask;
        msgTx->notifyEnable = notifyEnable;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FAULT_GROUP_NOTIFY, sizeof(msg_tfusad10_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rfusad10_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rfusad10_t *msgRx = (const msg_rfusad10_t*) msg;

        /* Extract faultIdFirstGet */
        if (faultIdFirstGet != NULL)
        {
            *faultIdFirstGet = msgRx->faultIdFirstGet;
        }

        /* Extract notifyEnabled */
        if (notifyEnabled != NULL)
        {
            *notifyEnabled = msgRx->notifyEnabled;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Temporarily disable fault handling                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaScheckEvntrig(uint32_t channel)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_SCHECK_EVNTRIG, sizeof(header), &header);
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
/* Request manually-triggered execution of sCheck test                      */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaScheckTestExec(uint32_t channel, uint32_t targetTestId)
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
            uint32_t targetTestId;
        } msg_tfusad14_t;
        msg_tfusad14_t *msgTx = (msg_tfusad14_t*) msg;

        /* Fill in parameters */
        msgTx->targetTestId = targetTestId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_SCHECK_TEST_EXEC, sizeof(msg_tfusad14_t),
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
int32_t SCMI_FusaNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read F-EENV state change notification event                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFeenvStateEvent(uint32_t channel, uint32_t *feenvState,
    uint32_t *mselMode)
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
            uint32_t feenvState;
            uint32_t mselMode;
        } msg_rfusaed32_t;
        const msg_rfusaed32_t *msgRx = (const msg_rfusaed32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FEENV_STATE_EVENT, sizeof(msg_rfusaed32_t),
            &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract feenvState */
            if (feenvState != NULL)
            {
                *feenvState = msgRx->feenvState;
            }

            /* Extract mselMode */
            if (mselMode != NULL)
            {
                *mselMode = msgRx->mselMode;
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

/*--------------------------------------------------------------------------*/
/* Read S-EENV state request notification event                             */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaSeenvStateReqEvent(uint32_t channel, uint32_t *pingCookie)
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
            uint32_t pingCookie;
        } msg_rfusaed33_t;
        const msg_rfusaed33_t *msgRx = (const msg_rfusaed33_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_SEENV_STATE_REQ_EVENT, sizeof(msg_rfusaed33_t),
            &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract pingCookie */
            if (pingCookie != NULL)
            {
                *pingCookie = msgRx->pingCookie;
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

/*--------------------------------------------------------------------------*/
/* Read fault notification event                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_FusaFaultEvent(uint32_t channel, uint32_t *faultId,
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
            uint32_t faultId;
            uint32_t flags;
        } msg_rfusaed34_t;
        const msg_rfusaed34_t *msgRx = (const msg_rfusaed34_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_FUSA_FAULT_EVENT, sizeof(msg_rfusaed34_t), &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract faultId */
            if (faultId != NULL)
            {
                *faultId = msgRx->faultId;
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

