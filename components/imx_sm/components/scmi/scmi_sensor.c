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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_SENSOR

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorProtocolAttributes(uint32_t channel,
    uint32_t *attributes, uint32_t *sensorRegAddressLow,
    uint32_t *sensorRegAddressHigh, uint32_t *sensorRegLen)
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
        uint32_t sensorRegAddressLow;
        uint32_t sensorRegAddressHigh;
        uint32_t sensorRegLen;
    } msg_rsensord1_t;

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
        status = SCMI_A2pRx(channel, sizeof(msg_rsensord1_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rsensord1_t *msgRx = (const msg_rsensord1_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract sensorRegAddressLow */
        if (sensorRegAddressLow != NULL)
        {
            *sensorRegAddressLow = msgRx->sensorRegAddressLow;
        }

        /* Extract sensorRegAddressHigh */
        if (sensorRegAddressHigh != NULL)
        {
            *sensorRegAddressHigh = msgRx->sensorRegAddressHigh;
        }

        /* Extract sensorRegLen */
        if (sensorRegLen != NULL)
        {
            *sensorRegLen = msgRx->sensorRegLen;
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
int32_t SCMI_SensorProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get sensor descriptors                                                   */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorDescriptionGet(uint32_t channel, uint32_t descIndex,
    uint32_t *numSensorFlags, scmi_sensor_desc_t *desc)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numSensorFlags;
        scmi_sensor_desc_t desc[SCMI_SENSOR_MAX_DESC];
    } msg_rsensord3_t;

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
            uint32_t descIndex;
        } msg_tsensord3_t;
        msg_tsensord3_t *msgTx = (msg_tsensord3_t*) msg;

        /* Fill in parameters */
        msgTx->descIndex = descIndex;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_DESCRIPTION_GET, sizeof(msg_tsensord3_t),
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
        const msg_rsensord3_t *msgRx = (const msg_rsensord3_t*) msg;

        /* Extract numSensorFlags */
        if (numSensorFlags != NULL)
        {
            *numSensorFlags = msgRx->numSensorFlags;
        }

        /* Extract desc */
        if (desc != NULL)
        {
            SCMI_MemCpy((uint8_t*) desc, (uint8_t*) &msgRx->desc,
                (SCMI_SENSOR_NUM_DESC * sizeof(scmi_sensor_desc_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Configure sensor trip point notification                                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorTripPointNotify(uint32_t channel, uint32_t sensorId,
    uint32_t sensorEventControl)
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
            uint32_t sensorId;
            uint32_t sensorEventControl;
        } msg_tsensord4_t;
        msg_tsensord4_t *msgTx = (msg_tsensord4_t*) msg;

        /* Fill in parameters */
        msgTx->sensorId = sensorId;
        msgTx->sensorEventControl = sensorEventControl;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_TRIP_POINT_NOTIFY, sizeof(msg_tsensord4_t),
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
/* Configure sensor trip point                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorTripPointConfig(uint32_t channel, uint32_t sensorId,
    uint32_t tripPointEvCtrl, int32_t tripPointValLow,
    int32_t tripPointValHigh)
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
            uint32_t sensorId;
            uint32_t tripPointEvCtrl;
            int32_t tripPointValLow;
            int32_t tripPointValHigh;
        } msg_tsensord5_t;
        msg_tsensord5_t *msgTx = (msg_tsensord5_t*) msg;

        /* Fill in parameters */
        msgTx->sensorId = sensorId;
        msgTx->tripPointEvCtrl = tripPointEvCtrl;
        msgTx->tripPointValLow = tripPointValLow;
        msgTx->tripPointValHigh = tripPointValHigh;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_TRIP_POINT_CONFIG, sizeof(msg_tsensord5_t),
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
/* Read sensor                                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorReadingGet(uint32_t channel, uint32_t sensorId,
    uint32_t flags, scmi_sensor_reading_t *readings)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        scmi_sensor_reading_t readings[SCMI_SENSOR_MAX_READINGS];
    } msg_rsensord6_t;

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
            uint32_t sensorId;
            uint32_t flags;
        } msg_tsensord6_t;
        msg_tsensord6_t *msgTx = (msg_tsensord6_t*) msg;

        /* Fill in parameters */
        msgTx->sensorId = sensorId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_READING_GET, sizeof(msg_tsensord6_t), &header);
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
        const msg_rsensord6_t *msgRx = (const msg_rsensord6_t*) msg;

        /* Extract readings */
        if (readings != NULL)
        {
            SCMI_MemCpy((uint8_t*) readings, (uint8_t*) &msgRx->readings,
                (SCMI_SENSOR_NUM_READINGS * sizeof(scmi_sensor_reading_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get sensor configuration                                                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorConfigGet(uint32_t channel, uint32_t sensorId,
    uint32_t *sensorConfig)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t sensorConfig;
    } msg_rsensord9_t;

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
            uint32_t sensorId;
        } msg_tsensord9_t;
        msg_tsensord9_t *msgTx = (msg_tsensord9_t*) msg;

        /* Fill in parameters */
        msgTx->sensorId = sensorId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_CONFIG_GET, sizeof(msg_tsensord9_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rsensord9_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rsensord9_t *msgRx = (const msg_rsensord9_t*) msg;

        /* Extract sensorConfig */
        if (sensorConfig != NULL)
        {
            *sensorConfig = msgRx->sensorConfig;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set sensor configuration                                                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorConfigSet(uint32_t channel, uint32_t sensorId,
    uint32_t sensorConfig)
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
            uint32_t sensorId;
            uint32_t sensorConfig;
        } msg_tsensord10_t;
        msg_tsensord10_t *msgTx = (msg_tsensord10_t*) msg;

        /* Fill in parameters */
        msgTx->sensorId = sensorId;
        msgTx->sensorConfig = sensorConfig;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_CONFIG_SET, sizeof(msg_tsensord10_t), &header);
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
int32_t SCMI_SensorNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read sensor event                                                        */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SensorTripPointEvent(uint32_t channel, uint32_t *agentId,
    uint32_t *sensorId, uint32_t *tripPointDesc)
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
            uint32_t sensorId;
            uint32_t tripPointDesc;
        } msg_rsensored32_t;
        const msg_rsensored32_t *msgRx = (const msg_rsensored32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_SENSOR_TRIP_POINT_EVENT, sizeof(msg_rsensored32_t),
            &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract agentId */
            if (agentId != NULL)
            {
                *agentId = msgRx->agentId;
            }

            /* Extract sensorId */
            if (sensorId != NULL)
            {
                *sensorId = msgRx->sensorId;
            }

            /* Extract tripPointDesc */
            if (tripPointDesc != NULL)
            {
                *tripPointDesc = msgRx->tripPointDesc;
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

