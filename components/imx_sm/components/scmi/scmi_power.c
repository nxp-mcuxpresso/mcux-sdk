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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_POWER

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerProtocolAttributes(uint32_t channel, uint32_t *attributes,
    uint32_t *statisticsAddressLow, uint32_t *statisticsAddressHigh,
    uint32_t *statisticsLen)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t attributes;
        uint32_t statisticsAddressLow;
        uint32_t statisticsAddressHigh;
        uint32_t statisticsLen;
    } msg_rpowerd1_t;

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
        status = SCMI_A2pRx(channel, sizeof(msg_rpowerd1_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rpowerd1_t *msgRx = (const msg_rpowerd1_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract statisticsAddressLow */
        if (statisticsAddressLow != NULL)
        {
            *statisticsAddressLow = msgRx->statisticsAddressLow;
        }

        /* Extract statisticsAddressHigh */
        if (statisticsAddressHigh != NULL)
        {
            *statisticsAddressHigh = msgRx->statisticsAddressHigh;
        }

        /* Extract statisticsLen */
        if (statisticsLen != NULL)
        {
            *statisticsLen = msgRx->statisticsLen;
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
int32_t SCMI_PowerProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get power domain attributes                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerDomainAttributes(uint32_t channel, uint32_t domainId,
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
        uint8_t name[SCMI_POWER_MAX_NAME];
    } msg_rpowerd3_t;

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
            uint32_t domainId;
        } msg_tpowerd3_t;
        msg_tpowerd3_t *msgTx = (msg_tpowerd3_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_POWER_DOMAIN_ATTRIBUTES, sizeof(msg_tpowerd3_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rpowerd3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rpowerd3_t *msgRx = (const msg_rpowerd3_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_POWER_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set power state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerStateSet(uint32_t channel, uint32_t domainId,
    uint32_t flags, uint32_t powerState)
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
            uint32_t domainId;
            uint32_t powerState;
        } msg_tpowerd4_t;
        msg_tpowerd4_t *msgTx = (msg_tpowerd4_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;
        msgTx->domainId = domainId;
        msgTx->powerState = powerState;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_POWER_STATE_SET, sizeof(msg_tpowerd4_t), &header);
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
/* Get power state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerStateGet(uint32_t channel, uint32_t domainId,
    uint32_t *powerState)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t powerState;
    } msg_rpowerd5_t;

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
            uint32_t domainId;
        } msg_tpowerd5_t;
        msg_tpowerd5_t *msgTx = (msg_tpowerd5_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_POWER_STATE_GET, sizeof(msg_tpowerd5_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rpowerd5_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rpowerd5_t *msgRx = (const msg_rpowerd5_t*) msg;

        /* Extract powerState */
        if (powerState != NULL)
        {
            *powerState = msgRx->powerState;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Negotiate the protocol version                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PowerNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

