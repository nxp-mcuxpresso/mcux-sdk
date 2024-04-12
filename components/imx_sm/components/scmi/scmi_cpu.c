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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_CPU

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Get CPU attributes                                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuAttributes(uint32_t channel, uint32_t cpuId,
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
        uint8_t name[SCMI_CPU_MAX_NAME];
    } msg_rcpud3_t;

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
            uint32_t cpuId;
        } msg_tcpud3_t;
        msg_tcpud3_t *msgTx = (msg_tcpud3_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_ATTRIBUTES, sizeof(msg_tcpud3_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rcpud3_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rcpud3_t *msgRx = (const msg_rcpud3_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_CPU_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Start a CPU                                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuStart(uint32_t channel, uint32_t cpuId)
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
            uint32_t cpuId;
        } msg_tcpud4_t;
        msg_tcpud4_t *msgTx = (msg_tcpud4_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_CPU_START,
            sizeof(msg_tcpud4_t), &header);
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
/* Stop a CPU                                                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuStop(uint32_t channel, uint32_t cpuId)
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
            uint32_t cpuId;
        } msg_tcpud5_t;
        msg_tcpud5_t *msgTx = (msg_tcpud5_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_CPU_STOP,
            sizeof(msg_tcpud5_t), &header);
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
/* Set reset vector                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuResetVectorSet(uint32_t channel, uint32_t cpuId,
    uint32_t flags, uint32_t resetVectorLow, uint32_t resetVectorHigh)
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
            uint32_t cpuId;
            uint32_t flags;
            uint32_t resetVectorLow;
            uint32_t resetVectorHigh;
        } msg_tcpud6_t;
        msg_tcpud6_t *msgTx = (msg_tcpud6_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->flags = flags;
        msgTx->resetVectorLow = resetVectorLow;
        msgTx->resetVectorHigh = resetVectorHigh;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_RESET_VECTOR_SET, sizeof(msg_tcpud6_t), &header);
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
/* Set a CPU sleep target mode                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuSleepModeSet(uint32_t channel, uint32_t cpuId,
    uint32_t flags, uint32_t sleepMode)
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
            uint32_t cpuId;
            uint32_t flags;
            uint32_t sleepMode;
        } msg_tcpud7_t;
        msg_tcpud7_t *msgTx = (msg_tcpud7_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->flags = flags;
        msgTx->sleepMode = sleepMode;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_SLEEP_MODE_SET, sizeof(msg_tcpud7_t), &header);
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
/* Set a CPU IRQ wake mask                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuIrqWakeSet(uint32_t channel, uint32_t cpuId,
    uint32_t maskIdx, uint32_t numMask, const uint32_t *mask)
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
            uint32_t cpuId;
            uint32_t maskIdx;
            uint32_t numMask;
            uint32_t mask[SCMI_CPU_MAX_MASK_T];
        } msg_tcpud8_t;
        msg_tcpud8_t *msgTx = (msg_tcpud8_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->maskIdx = maskIdx;
        msgTx->numMask = numMask;

        SCMI_MemCpy((uint8_t*) &msgTx->mask, (const uint8_t*) mask,
            (SCMI_CPU_NUM_MASK_T * sizeof(uint32_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_IRQ_WAKE_SET, sizeof(msg_tcpud8_t), &header);
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
/* Set a CPU non-IRQ wake mask                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuNonIrqWakeSet(uint32_t channel, uint32_t cpuId,
    uint32_t maskIdx, uint32_t numMask, const uint32_t *mask)
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
            uint32_t cpuId;
            uint32_t maskIdx;
            uint32_t numMask;
            uint32_t mask[SCMI_CPU_MAX_MASK_T];
        } msg_tcpud9_t;
        msg_tcpud9_t *msgTx = (msg_tcpud9_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->maskIdx = maskIdx;
        msgTx->numMask = numMask;

        SCMI_MemCpy((uint8_t*) &msgTx->mask, (const uint8_t*) mask,
            (SCMI_CPU_NUM_MASK_T * sizeof(uint32_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_NON_IRQ_WAKE_SET, sizeof(msg_tcpud9_t), &header);
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
/* Configure a list of power domain LPM configs                             */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuPdLpmConfigSet(uint32_t channel, uint32_t cpuId,
    uint32_t numConfigs, const scmi_pd_lpm_config_t *pdConfigs)
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
            uint32_t cpuId;
            uint32_t numConfigs;
            scmi_pd_lpm_config_t pdConfigs[SCMI_CPU_MAX_PDCONFIGS_T];
        } msg_tcpud10_t;
        msg_tcpud10_t *msgTx = (msg_tcpud10_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->numConfigs = numConfigs;

        SCMI_MemCpy((uint8_t*) &msgTx->pdConfigs,
            (const uint8_t*) pdConfigs,
            (SCMI_CPU_NUM_PDCONFIGS_T * sizeof(scmi_pd_lpm_config_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_PD_LPM_CONFIG_SET, sizeof(msg_tcpud10_t),
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
/* Configure a list of peripheral LPM configs                               */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuPerLpmConfigSet(uint32_t channel, uint32_t cpuId,
    uint32_t numConfigs, const scmi_per_lpm_config_t *perConfigs)
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
            uint32_t cpuId;
            uint32_t numConfigs;
            scmi_per_lpm_config_t perConfigs[SCMI_CPU_MAX_PERCONFIGS_T];
        } msg_tcpud11_t;
        msg_tcpud11_t *msgTx = (msg_tcpud11_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;
        msgTx->numConfigs = numConfigs;

        SCMI_MemCpy((uint8_t*) &msgTx->perConfigs,
            (const uint8_t*) perConfigs,
            (SCMI_CPU_NUM_PERCONFIGS_T * sizeof(scmi_per_lpm_config_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_PER_LPM_CONFIG_SET, sizeof(msg_tcpud11_t),
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
/* Get info for a CPU                                                       */
/*--------------------------------------------------------------------------*/
int32_t SCMI_CpuInfoGet(uint32_t channel, uint32_t cpuId, uint32_t *runMode,
    uint32_t *sleepMode, uint32_t *resetVectorLow,
    uint32_t *resetVectorHigh)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t runMode;
        uint32_t sleepMode;
        uint32_t resetVectorLow;
        uint32_t resetVectorHigh;
    } msg_rcpud12_t;

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
            uint32_t cpuId;
        } msg_tcpud12_t;
        msg_tcpud12_t *msgTx = (msg_tcpud12_t*) msg;

        /* Fill in parameters */
        msgTx->cpuId = cpuId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_CPU_INFO_GET, sizeof(msg_tcpud12_t), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rcpud12_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rcpud12_t *msgRx = (const msg_rcpud12_t*) msg;

        /* Extract runMode */
        if (runMode != NULL)
        {
            *runMode = msgRx->runMode;
        }

        /* Extract sleepMode */
        if (sleepMode != NULL)
        {
            *sleepMode = msgRx->sleepMode;
        }

        /* Extract resetVectorLow */
        if (resetVectorLow != NULL)
        {
            *resetVectorLow = msgRx->resetVectorLow;
        }

        /* Extract resetVectorHigh */
        if (resetVectorHigh != NULL)
        {
            *resetVectorHigh = msgRx->resetVectorHigh;
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
int32_t SCMI_CpuNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

