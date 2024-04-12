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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_BASE

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get vendor identifier                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseDiscoverVendor(uint32_t channel,
    uint8_t *vendorIdentifier)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint8_t vendorIdentifier[SCMI_BASE_MAX_VENDORIDENTIFIER];
    } msg_rbased3_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_DISCOVER_VENDOR, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbased3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbased3_t *msgRx = (const msg_rbased3_t*) msg;

        /* Extract vendorIdentifier */
        if (vendorIdentifier != NULL)
        {
            SCMI_StrCpy(vendorIdentifier, msgRx->vendorIdentifier,
                SCMI_BASE_MAX_VENDORIDENTIFIER);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get sub-vendor identifier                                                */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseDiscoverSubVendor(uint32_t channel,
    uint8_t *vendorIdentifier)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint8_t vendorIdentifier[SCMI_BASE_MAX_VENDORIDENTIFIER];
    } msg_rbased4_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_DISCOVER_SUB_VENDOR, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbased4_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbased4_t *msgRx = (const msg_rbased4_t*) msg;

        /* Extract vendorIdentifier */
        if (vendorIdentifier != NULL)
        {
            SCMI_StrCpy(vendorIdentifier, msgRx->vendorIdentifier,
                SCMI_BASE_MAX_VENDORIDENTIFIER);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get implementation version                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseDiscoverImplementationVersion(uint32_t channel,
    uint32_t *implementationVersion)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t implementationVersion;
    } msg_rbased5_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_DISCOVER_IMPLEMENTATION_VERSION, sizeof(header),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbased5_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbased5_t *msgRx = (const msg_rbased5_t*) msg;

        /* Extract implementationVersion */
        if (implementationVersion != NULL)
        {
            *implementationVersion = msgRx->implementationVersion;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Discover protocols                                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseDiscoverListProtocols(uint32_t channel, uint32_t skip,
    uint32_t *numProtocols, uint32_t *protocols)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numProtocols;
        uint32_t protocols[SCMI_BASE_MAX_PROTOCOLS];
    } msg_rbased6_t;

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
            uint32_t skip;
        } msg_tbased6_t;
        msg_tbased6_t *msgTx = (msg_tbased6_t*) msg;

        /* Fill in parameters */
        msgTx->skip = skip;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_DISCOVER_LIST_PROTOCOLS, sizeof(msg_tbased6_t),
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
        const msg_rbased6_t *msgRx = (const msg_rbased6_t*) msg;

        /* Extract numProtocols */
        if (numProtocols != NULL)
        {
            *numProtocols = msgRx->numProtocols;
        }

        /* Extract protocols */
        if (protocols != NULL)
        {
            SCMI_MemCpy((uint8_t*) protocols, (uint8_t*) &msgRx->protocols,
                (SCMI_BASE_NUM_PROTOCOLS * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get agent information                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseDiscoverAgent(uint32_t channel, uint32_t *agentId,
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
        uint32_t agentId;
        uint8_t name[SCMI_BASE_MAX_NAME];
    } msg_rbased7_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInit(channel, &msg);

    /* Check agentId pointer */
    if ((status == SCMI_ERR_SUCCESS) && (agentId == NULL))
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
            uint32_t agentId;
        } msg_tbased7_t;
        msg_tbased7_t *msgTx = (msg_tbased7_t*) msg;

        /* Fill in parameters */
        msgTx->agentId = *agentId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_DISCOVER_AGENT, sizeof(msg_tbased7_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rbased7_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rbased7_t *msgRx = (const msg_rbased7_t*) msg;

        /* Extract agentId */
        *agentId = msgRx->agentId;

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_BASE_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set device permissions                                                   */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseSetDevicePermissions(uint32_t channel, uint32_t agentId,
    uint32_t deviceId, uint32_t flags)
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
            uint32_t agentId;
            uint32_t deviceId;
            uint32_t flags;
        } msg_tbased9_t;
        msg_tbased9_t *msgTx = (msg_tbased9_t*) msg;

        /* Fill in parameters */
        msgTx->agentId = agentId;
        msgTx->deviceId = deviceId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_SET_DEVICE_PERMISSIONS, sizeof(msg_tbased9_t),
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
/* Reset platform resource settings for an agent                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BaseResetAgentConfiguration(uint32_t channel, uint32_t agentId,
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
            uint32_t agentId;
            uint32_t flags;
        } msg_tbased11_t;
        msg_tbased11_t *msgTx = (msg_tbased11_t*) msg;

        /* Fill in parameters */
        msgTx->agentId = agentId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_BASE_RESET_AGENT_CONFIGURATION, sizeof(msg_tbased11_t),
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
int32_t SCMI_BaseNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

