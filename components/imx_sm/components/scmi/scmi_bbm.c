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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_BBM

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Write a GPR value                                                        */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmGprSet(uint32_t channel, uint32_t index, uint32_t value)
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
            uint32_t index;
            uint32_t value;
        } msg_tbbmd3_t;
        msg_tbbmd3_t *msgTx = (msg_tbbmd3_t*) msg;

        /* Fill in parameters */
        msgTx->index = index;
        msgTx->value = value;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_BBM_GPR_SET,
            sizeof(msg_tbbmd3_t), &header);
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
/* Read a GPR value                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmGprGet(uint32_t channel, uint32_t index, uint32_t *value)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t value;
    } msg_rbbmd4_t;

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
            uint32_t index;
        } msg_tbbmd4_t;
        msg_tbbmd4_t *msgTx = (msg_tbbmd4_t*) msg;

        /* Fill in parameters */
        msgTx->index = index;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_BBM_GPR_GET,
            sizeof(msg_tbbmd4_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbbmd4_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbbmd4_t *msgRx = (const msg_rbbmd4_t*) msg;

        /* Extract value */
        if (value != NULL)
        {
            *value = msgRx->value;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get attributes for an RTC                                                */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcAttributes(uint32_t channel, uint32_t rtcId,
    uint32_t *attributes, uint8_t *name)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t attributes;
        uint8_t name[SCMI_BBM_MAX_NAME];
    } msg_rbbmd5_t;

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
            uint32_t rtcId;
        } msg_tbbmd5_t;
        msg_tbbmd5_t *msgTx = (msg_tbbmd5_t*) msg;

        /* Fill in parameters */
        msgTx->rtcId = rtcId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_ATTRIBUTES, sizeof(msg_tbbmd5_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbbmd5_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbbmd5_t *msgRx = (const msg_rbbmd5_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_BBM_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set an RTC time                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcTimeSet(uint32_t channel, uint32_t rtcId, uint32_t flags,
    scmi_rtc_time_t val)
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
            uint32_t rtcId;
            uint32_t flags;
            scmi_rtc_time_t val;
        } msg_tbbmd6_t;
        msg_tbbmd6_t *msgTx = (msg_tbbmd6_t*) msg;

        /* Fill in parameters */
        msgTx->rtcId = rtcId;
        msgTx->flags = flags;
        msgTx->val = val;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_TIME_SET, sizeof(msg_tbbmd6_t), &header);
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
/* Get an RTC time                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcTimeGet(uint32_t channel, uint32_t rtcId, uint32_t flags,
    scmi_rtc_time_t *val)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        scmi_rtc_time_t val;
    } msg_rbbmd7_t;

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
            uint32_t rtcId;
            uint32_t flags;
        } msg_tbbmd7_t;
        msg_tbbmd7_t *msgTx = (msg_tbbmd7_t*) msg;

        /* Fill in parameters */
        msgTx->rtcId = rtcId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_TIME_GET, sizeof(msg_tbbmd7_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbbmd7_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbbmd7_t *msgRx = (const msg_rbbmd7_t*) msg;

        /* Extract val */
        if (val != NULL)
        {
            *val = msgRx->val;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set an RTC alarm                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcAlarmSet(uint32_t channel, uint32_t rtcId,
    uint32_t flags, scmi_rtc_time_t val)
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
            uint32_t rtcId;
            uint32_t flags;
            scmi_rtc_time_t val;
        } msg_tbbmd8_t;
        msg_tbbmd8_t *msgTx = (msg_tbbmd8_t*) msg;

        /* Fill in parameters */
        msgTx->rtcId = rtcId;
        msgTx->flags = flags;
        msgTx->val = val;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_ALARM_SET, sizeof(msg_tbbmd8_t), &header);
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
/* Read the button state                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmButtonGet(uint32_t channel, uint32_t *buttonState)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t buttonState;
    } msg_rbbmd9_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_BUTTON_GET, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbbmd9_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbbmd9_t *msgRx = (const msg_rbbmd9_t*) msg;

        /* Extract buttonState */
        if (buttonState != NULL)
        {
            *buttonState = msgRx->buttonState;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Configure BBM RTC notifications                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcNotify(uint32_t channel, uint32_t rtcId, uint32_t flags)
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
            uint32_t rtcId;
            uint32_t flags;
        } msg_tbbmd10_t;
        msg_tbbmd10_t *msgTx = (msg_tbbmd10_t*) msg;

        /* Fill in parameters */
        msgTx->rtcId = rtcId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_NOTIFY, sizeof(msg_tbbmd10_t), &header);
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
/* Configure BBM button notifications                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmButtonNotify(uint32_t channel, uint32_t flags)
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
        } msg_tbbmd11_t;
        msg_tbbmd11_t *msgTx = (msg_tbbmd11_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_BUTTON_NOTIFY, sizeof(msg_tbbmd11_t), &header);
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
int32_t SCMI_BbmNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read BBM RTC notification events                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmRtcEvent(uint32_t channel, uint32_t *flags)
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
            uint32_t flags;
        } msg_rbbmed32_t;
        const msg_rbbmed32_t *msgRx = (const msg_rbbmed32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_RTC_EVENT, sizeof(msg_rbbmed32_t), &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
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

/*--------------------------------------------------------------------------*/
/* Read BBM button notification event                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BbmButtonEvent(uint32_t channel, uint32_t *flags)
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
            uint32_t flags;
        } msg_rbbmed33_t;
        const msg_rbbmed33_t *msgRx = (const msg_rbbmed33_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BBM_BUTTON_EVENT, sizeof(msg_rbbmed33_t), &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
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

