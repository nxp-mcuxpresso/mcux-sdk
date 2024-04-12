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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_PERF

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerfProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerfProtocolAttributes(uint32_t channel, uint32_t *attributes,
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
    } msg_rperfd1_t;

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
        status = SCMI_A2pRx(channel, sizeof(msg_rperfd1_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rperfd1_t *msgRx = (const msg_rperfd1_t*) msg;

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
int32_t SCMI_PerfProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get performance domain attributes                                        */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceDomainAttributes(uint32_t channel,
    uint32_t domainId, uint32_t *attributes, uint32_t *rateLimit,
    uint32_t *sustainedFreq, uint32_t *sustainedPerfLevel, uint8_t *name)
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
        uint32_t rateLimit;
        uint32_t sustainedFreq;
        uint32_t sustainedPerfLevel;
        uint8_t name[SCMI_PERF_MAX_NAME];
    } msg_rperfd3_t;

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
        } msg_tperfd3_t;
        msg_tperfd3_t *msgTx = (msg_tperfd3_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_DOMAIN_ATTRIBUTES, sizeof(msg_tperfd3_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rperfd3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rperfd3_t *msgRx = (const msg_rperfd3_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract rateLimit */
        if (rateLimit != NULL)
        {
            *rateLimit = msgRx->rateLimit;
        }

        /* Extract sustainedFreq */
        if (sustainedFreq != NULL)
        {
            *sustainedFreq = msgRx->sustainedFreq;
        }

        /* Extract sustainedPerfLevel */
        if (sustainedPerfLevel != NULL)
        {
            *sustainedPerfLevel = msgRx->sustainedPerfLevel;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_PERF_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get performance level descriptions                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceDescribeLevels(uint32_t channel, uint32_t domainId,
    uint32_t skipIndex, uint32_t *numLevels, scmi_perf_level_t *perfLevels)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numLevels;
        scmi_perf_level_t perfLevels[SCMI_PERF_MAX_PERFLEVELS];
    } msg_rperfd4_t;

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
            uint32_t skipIndex;
        } msg_tperfd4_t;
        msg_tperfd4_t *msgTx = (msg_tperfd4_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;
        msgTx->skipIndex = skipIndex;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_DESCRIBE_LEVELS, sizeof(msg_tperfd4_t),
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
        const msg_rperfd4_t *msgRx = (const msg_rperfd4_t*) msg;

        /* Extract numLevels */
        if (numLevels != NULL)
        {
            *numLevels = msgRx->numLevels;
        }

        /* Extract perfLevels */
        if (perfLevels != NULL)
        {
            SCMI_MemCpy((uint8_t*) perfLevels, (uint8_t*) &msgRx->perfLevels,
                (SCMI_PERF_NUM_PERFLEVELS * sizeof(scmi_perf_level_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set performance limits                                                   */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceLimitsSet(uint32_t channel, uint32_t domainId,
    uint32_t rangeMax, uint32_t rangeMin)
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
            uint32_t domainId;
            uint32_t rangeMax;
            uint32_t rangeMin;
        } msg_tperfd5_t;
        msg_tperfd5_t *msgTx = (msg_tperfd5_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;
        msgTx->rangeMax = rangeMax;
        msgTx->rangeMin = rangeMin;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_LIMITS_SET, sizeof(msg_tperfd5_t),
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
/* Get performance limits                                                   */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceLimitsGet(uint32_t channel, uint32_t domainId,
    uint32_t *rangeMax, uint32_t *rangeMin)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t rangeMax;
        uint32_t rangeMin;
    } msg_rperfd6_t;

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
        } msg_tperfd6_t;
        msg_tperfd6_t *msgTx = (msg_tperfd6_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_LIMITS_GET, sizeof(msg_tperfd6_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rperfd6_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rperfd6_t *msgRx = (const msg_rperfd6_t*) msg;

        /* Extract rangeMax */
        if (rangeMax != NULL)
        {
            *rangeMax = msgRx->rangeMax;
        }

        /* Extract rangeMin */
        if (rangeMin != NULL)
        {
            *rangeMin = msgRx->rangeMin;
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Set performance level                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceLevelSet(uint32_t channel, uint32_t domainId,
    uint32_t performanceLevel)
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
            uint32_t domainId;
            uint32_t performanceLevel;
        } msg_tperfd7_t;
        msg_tperfd7_t *msgTx = (msg_tperfd7_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;
        msgTx->performanceLevel = performanceLevel;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_LEVEL_SET, sizeof(msg_tperfd7_t),
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
/* Get performance level                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_PerformanceLevelGet(uint32_t channel, uint32_t domainId,
    uint32_t *performanceLevel)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t performanceLevel;
    } msg_rperfd8_t;

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
        } msg_tperfd8_t;
        msg_tperfd8_t *msgTx = (msg_tperfd8_t*) msg;

        /* Fill in parameters */
        msgTx->domainId = domainId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_PERFORMANCE_LEVEL_GET, sizeof(msg_tperfd8_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rperfd8_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rperfd8_t *msgRx = (const msg_rperfd8_t*) msg;

        /* Extract performanceLevel */
        if (performanceLevel != NULL)
        {
            *performanceLevel = msgRx->performanceLevel;
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
int32_t SCMI_PerfNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

