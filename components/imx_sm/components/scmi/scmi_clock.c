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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_CLOCK

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockProtocolAttributes(uint32_t channel,
    uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get clock attributes                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockAttributes(uint32_t channel, uint32_t clockId,
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
        uint8_t name[SCMI_CLOCK_MAX_NAME];
    } msg_rclockd3_t;

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
            uint32_t clockId;
        } msg_tclockd3_t;
        msg_tclockd3_t *msgTx = (msg_tclockd3_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_ATTRIBUTES, sizeof(msg_tclockd3_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rclockd3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rclockd3_t *msgRx = (const msg_rclockd3_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_CLOCK_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get clock rate description                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockDescribeRates(uint32_t channel, uint32_t clockId,
    uint32_t rateIndex, uint32_t *numRatesFlags, scmi_clock_rate_t *rates)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numRatesFlags;
        scmi_clock_rate_t rates[SCMI_CLOCK_MAX_RATES];
    } msg_rclockd4_t;

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
            uint32_t clockId;
            uint32_t rateIndex;
        } msg_tclockd4_t;
        msg_tclockd4_t *msgTx = (msg_tclockd4_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;
        msgTx->rateIndex = rateIndex;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_DESCRIBE_RATES, sizeof(msg_tclockd4_t),
            &header);
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
        const msg_rclockd4_t *msgRx = (const msg_rclockd4_t*) msg;

        /* Extract numRatesFlags */
        if (numRatesFlags != NULL)
        {
            *numRatesFlags = msgRx->numRatesFlags;
        }

        /* Extract rates */
        if (rates != NULL)
        {
            SCMI_MemCpy((uint8_t*) rates, (uint8_t*) &msgRx->rates,
                (SCMI_CLOCK_NUM_RATES * sizeof(scmi_clock_rate_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set clock rate                                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockRateSet(uint32_t channel, uint32_t clockId,
    uint32_t flags, scmi_clock_rate_t rate)
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
            uint32_t clockId;
            scmi_clock_rate_t rate;
        } msg_tclockd5_t;
        msg_tclockd5_t *msgTx = (msg_tclockd5_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;
        msgTx->clockId = clockId;
        msgTx->rate = rate;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_RATE_SET, sizeof(msg_tclockd5_t), &header);
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
/* Get clock rate                                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockRateGet(uint32_t channel, uint32_t clockId,
    scmi_clock_rate_t *rate)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        scmi_clock_rate_t rate;
    } msg_rclockd6_t;

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
            uint32_t clockId;
        } msg_tclockd6_t;
        msg_tclockd6_t *msgTx = (msg_tclockd6_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_RATE_GET, sizeof(msg_tclockd6_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rclockd6_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rclockd6_t *msgRx = (const msg_rclockd6_t*) msg;

        /* Extract rate */
        if (rate != NULL)
        {
            *rate = msgRx->rate;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set clock configuration                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockConfigSet(uint32_t channel, uint32_t clockId,
    uint32_t attributes, uint32_t extendedConfigVal)
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
            uint32_t clockId;
            uint32_t attributes;
            uint32_t extendedConfigVal;
        } msg_tclockd7_t;
        msg_tclockd7_t *msgTx = (msg_tclockd7_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;
        msgTx->attributes = attributes;
        msgTx->extendedConfigVal = extendedConfigVal;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_CONFIG_SET, sizeof(msg_tclockd7_t), &header);
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
/* Get clock configuration                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockConfigGet(uint32_t channel, uint32_t clockId,
    uint32_t flags, uint32_t *attributes, uint32_t *config,
    uint32_t *extendedConfigVal)
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
        uint32_t config;
        uint32_t extendedConfigVal;
    } msg_rclockd11_t;

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
            uint32_t clockId;
            uint32_t flags;
        } msg_tclockd11_t;
        msg_tclockd11_t *msgTx = (msg_tclockd11_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_CONFIG_GET, sizeof(msg_tclockd11_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rclockd11_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rclockd11_t *msgRx = (const msg_rclockd11_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract config */
        if (config != NULL)
        {
            *config = msgRx->config;
        }

        /* Extract extendedConfigVal */
        if (extendedConfigVal != NULL)
        {
            *extendedConfigVal = msgRx->extendedConfigVal;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get all possible parents                                                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockPossibleParentsGet(uint32_t channel, uint32_t clockId,
    uint32_t skipParents, uint32_t *numParentsFlags, uint32_t *parents)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numParentsFlags;
        uint32_t parents[SCMI_CLOCK_MAX_PARENTS];
    } msg_rclockd12_t;

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
            uint32_t clockId;
            uint32_t skipParents;
        } msg_tclockd12_t;
        msg_tclockd12_t *msgTx = (msg_tclockd12_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;
        msgTx->skipParents = skipParents;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_POSSIBLE_PARENTS_GET, sizeof(msg_tclockd12_t),
            &header);
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
        const msg_rclockd12_t *msgRx = (const msg_rclockd12_t*) msg;

        /* Extract numParentsFlags */
        if (numParentsFlags != NULL)
        {
            *numParentsFlags = msgRx->numParentsFlags;
        }

        /* Extract parents */
        if (parents != NULL)
        {
            SCMI_MemCpy((uint8_t*) parents, (uint8_t*) &msgRx->parents,
                (SCMI_CLOCK_NUM_PARENTS * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set clock parent                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockParentSet(uint32_t channel, uint32_t clockId,
    uint32_t parentId)
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
            uint32_t clockId;
            uint32_t parentId;
        } msg_tclockd13_t;
        msg_tclockd13_t *msgTx = (msg_tclockd13_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;
        msgTx->parentId = parentId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_PARENT_SET, sizeof(msg_tclockd13_t), &header);
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
/* Get clock parent                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockParentGet(uint32_t channel, uint32_t clockId,
    uint32_t *parentId)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t parentId;
    } msg_rclockd14_t;

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
            uint32_t clockId;
        } msg_tclockd14_t;
        msg_tclockd14_t *msgTx = (msg_tclockd14_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_PARENT_GET, sizeof(msg_tclockd14_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rclockd14_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rclockd14_t *msgRx = (const msg_rclockd14_t*) msg;

        /* Extract parentId */
        if (parentId != NULL)
        {
            *parentId = msgRx->parentId;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get clock permissions                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ClockGetPermissions(uint32_t channel, uint32_t clockId,
    uint32_t *permissions)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t permissions;
    } msg_rclockd15_t;

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
            uint32_t clockId;
        } msg_tclockd15_t;
        msg_tclockd15_t *msgTx = (msg_tclockd15_t*) msg;

        /* Fill in parameters */
        msgTx->clockId = clockId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CLOCK_GET_PERMISSIONS, sizeof(msg_tclockd15_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rclockd15_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rclockd15_t *msgRx = (const msg_rclockd15_t*) msg;

        /* Extract permissions */
        if (permissions != NULL)
        {
            *permissions = msgRx->permissions;
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
int32_t SCMI_ClockNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

