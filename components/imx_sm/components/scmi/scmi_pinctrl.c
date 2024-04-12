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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_PINCTRL

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlProtocolAttributes(uint32_t channel,
    uint32_t *attributesLow, uint32_t *attributesHigh)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t attributesLow;
        uint32_t attributesHigh;
    } msg_rpinctrld1_t;

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
        status = SCMI_A2pRx(channel, sizeof(msg_rpinctrld1_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rpinctrld1_t *msgRx = (const msg_rpinctrld1_t*) msg;

        /* Extract attributesLow */
        if (attributesLow != NULL)
        {
            *attributesLow = msgRx->attributesLow;
        }

        /* Extract attributesHigh */
        if (attributesHigh != NULL)
        {
            *attributesHigh = msgRx->attributesHigh;
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
int32_t SCMI_PinctrlProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get pin attributes                                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlAttributes(uint32_t channel, uint32_t identifier,
    uint32_t flags, uint32_t *attributes, uint8_t *name)
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
        uint8_t name[SCMI_PINCTRL_MAX_NAME];
    } msg_rpinctrld3_t;

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
            uint32_t identifier;
            uint32_t flags;
        } msg_tpinctrld3_t;
        msg_tpinctrld3_t *msgTx = (msg_tpinctrld3_t*) msg;

        /* Fill in parameters */
        msgTx->identifier = identifier;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PINCTRL_ATTRIBUTES, sizeof(msg_tpinctrld3_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rpinctrld3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rpinctrld3_t *msgRx = (const msg_rpinctrld3_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_PINCTRL_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get pin configuration                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlSettingsGet(uint32_t channel, uint32_t identifier,
    uint32_t attributes, uint32_t *functionSelected, uint32_t *numConfigs,
    scmi_pin_config_t *configs)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t functionSelected;
        uint32_t numConfigs;
        scmi_pin_config_t configs[SCMI_PINCTRL_MAX_CONFIGS];
    } msg_rpinctrld5_t;

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
            uint32_t identifier;
            uint32_t attributes;
        } msg_tpinctrld5_t;
        msg_tpinctrld5_t *msgTx = (msg_tpinctrld5_t*) msg;

        /* Fill in parameters */
        msgTx->identifier = identifier;
        msgTx->attributes = attributes;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PINCTRL_SETTINGS_GET, sizeof(msg_tpinctrld5_t),
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
        const msg_rpinctrld5_t *msgRx = (const msg_rpinctrld5_t*) msg;

        /* Extract functionSelected */
        if (functionSelected != NULL)
        {
            *functionSelected = msgRx->functionSelected;
        }

        /* Extract numConfigs */
        if (numConfigs != NULL)
        {
            *numConfigs = msgRx->numConfigs;
        }

        /* Extract configs */
        if (configs != NULL)
        {
            SCMI_MemCpy((uint8_t*) configs, (uint8_t*) &msgRx->configs,
                (SCMI_PINCTRL_NUM_CONFIGS * sizeof(scmi_pin_config_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set pin configuration                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlSettingsConfigure(uint32_t channel, uint32_t identifier,
    uint32_t functionId, uint32_t attributes,
    const scmi_pin_config_t *configs)
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
            uint32_t identifier;
            uint32_t functionId;
            uint32_t attributes;
            scmi_pin_config_t configs[SCMI_PINCTRL_MAX_CONFIGS_T];
        } msg_tpinctrld6_t;
        msg_tpinctrld6_t *msgTx = (msg_tpinctrld6_t*) msg;

        /* Fill in parameters */
        msgTx->identifier = identifier;
        msgTx->functionId = functionId;
        msgTx->attributes = attributes;

        SCMI_MemCpy((uint8_t*) &msgTx->configs, (const uint8_t*) configs,
            (SCMI_PINCTRL_NUM_CONFIGS_T * sizeof(scmi_pin_config_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PINCTRL_SETTINGS_CONFIGURE, sizeof(msg_tpinctrld6_t),
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
/* Request a pin                                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlRequest(uint32_t channel, uint32_t identifier,
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
            uint32_t identifier;
            uint32_t flags;
        } msg_tpinctrld7_t;
        msg_tpinctrld7_t *msgTx = (msg_tpinctrld7_t*) msg;

        /* Fill in parameters */
        msgTx->identifier = identifier;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PINCTRL_REQUEST, sizeof(msg_tpinctrld7_t), &header);
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
/* Release a pin                                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PinctrlRelease(uint32_t channel, uint32_t identifier,
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
            uint32_t identifier;
            uint32_t flags;
        } msg_tpinctrld8_t;
        msg_tpinctrld8_t *msgTx = (msg_tpinctrld8_t*) msg;

        /* Fill in parameters */
        msgTx->identifier = identifier;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PINCTRL_RELEASE, sizeof(msg_tpinctrld8_t), &header);
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
int32_t SCMI_PinctrlNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

