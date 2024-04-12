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

#include <string.h>
#include "scmi.h"
#include "scmi_internal.h"
#include "smt.h"

/* Local macros */

/*!
 * @name SCMI header creation
 */
/** @{ */
#define SCMI_HEADER_TOKEN_MASK  0x3FFU
#define SCMI_HEADER_MSG(x)  (((x) & 0xFFU) << 0U)
#define SCMI_HEADER_TYPE(x)  (((x) & 0x3U) << 8U)
#define SCMI_HEADER_PROTOCOL(x)  (((x) & 0xFFU) << 10U)
#define SCMI_HEADER_TOKEN(x)  (((x) & SCMI_HEADER_TOKEN_MASK) << 18U)
/** @} */

/*!
 * @name SCMI header extraction
 */
/** @{ */
#define SCMI_HEADER_MSG_EX(x)  (((x) & 0xFFU) >> 0U)
#define SCMI_HEADER_TYPE_EX(x)  (((x) & 0x300U) >> 8U)
#define SCMI_HEADER_PROTOCOL_EX(x)  (((x) & 0x3FC00U) >> 10U)
#define SCMI_HEADER_TOKEN_EX(x)  (((x) & 0x0FFC0000U) >> 18U)
/** @} */

/* Local types */

typedef struct
{
    uint32_t header;
    int32_t status;
} drv_scmi_msg_status_t;

/* Local variables */

static bool s_tokenCheck[SMT_MAX_CHN] = { 0U };
static uint32_t s_token[SMT_MAX_CHN] = { 0U };

/*--------------------------------------------------------------------------*/
/* Get transport buffer address                                             */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BufInit(uint32_t channel, void **msg)
{
    int32_t status = SCMI_ERR_SUCCESS;

    /* Wait until channel is free */
    while (!SMT_ChannelFree(channel))
    {
        ; /* Intentional empty while */
    }

    /* Get header address */
    *msg = SCMI_HdrAddrGet(channel);
    if (*msg == NULL)
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get transport buffer address (constant)                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_BufInitC(uint32_t channel, const void **msg)
{
    int32_t status = SCMI_ERR_SUCCESS;

    /* Wait until channel is free */
    while (!SMT_ChannelFree(channel))
    {
        ; /* Intentional empty while */
    }

    /* Get header address */
    *msg = SCMI_HdrAddrGet(channel);
    if (*msg == NULL)
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get transport buffer address                                             */
/*--------------------------------------------------------------------------*/
void *SCMI_HdrAddrGet(uint32_t channel)
{
    return SMT_HdrAddrGet(channel);
}

/*--------------------------------------------------------------------------*/
/* Set abort state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_AbortSet(uint32_t channel, bool state)
{
    /* Set SMT abort state */
    return SMT_AbortSet(channel, state);
}

/*--------------------------------------------------------------------------*/
/* Send A2P command                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_A2pTx(uint32_t channel, uint32_t protocolId,
    uint32_t messageId, uint32_t len, uint32_t *header)
{
    int32_t status;
    drv_scmi_msg_status_t *msg;

    /* Get transport buffer address */
    msg = (drv_scmi_msg_status_t*) SCMI_HdrAddrGet(channel);

    /* Valid channel and buffer? */
    if (msg != NULL)
    {
        /* Generate header */
        *header = SCMI_HEADER_MSG(messageId)
            | SCMI_HEADER_PROTOCOL(protocolId)
            | SCMI_HEADER_TYPE(0UL)
            | SCMI_HEADER_TOKEN(s_token[channel]);
        msg->header = *header;

        /* Increment token */
        s_token[channel]++;
        s_token[channel] &= SCMI_HEADER_TOKEN_MASK;

        /* Send message via transport */
        status = SMT_Tx(channel, len, false, false);
    }
    else
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Receive A2P response                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_A2pRx(uint32_t channel, uint32_t minLen, uint32_t header)
{
    int32_t status;
    const drv_scmi_msg_status_t *msg;
    uint32_t len;

    /* Get transport buffer address */
    msg = (drv_scmi_msg_status_t*) SCMI_HdrAddrGet(channel);

    /* Valid channel and buffer? */
    if (msg != NULL)
    {
        /* Receive message via transport */
        status = SMT_Rx(channel, &len, false);

        /* Check header */
        if ((status == SCMI_ERR_SUCCESS) && (header != msg->header))
        {
            status = SCMI_ERR_PROTOCOL_ERROR;
        }

        /* Check status */
        if ((status == SCMI_ERR_SUCCESS) && (len >= 8U))
        {
            status = msg->status;
        }

        /* Check size */
        if ((status == SCMI_ERR_SUCCESS) && (len < minLen))
        {
            status = SCMI_ERR_PROTOCOL_ERROR;
        }
    }
    else
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Check P2A channel state                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_P2aPending(uint32_t channel, uint32_t *protocolId,
    uint32_t *messageId)
{
    int32_t status = SCMI_ERR_SUCCESS;

    /* Acquire lock */
    SCMI_P2A_LOCK(channel);

    /* Check if message pending? */
    if (!SMT_ChannelFree(channel))
    {
        const drv_scmi_msg_status_t *msg;

        /* Get transport buffer address */
        msg = (const drv_scmi_msg_status_t*) SCMI_HdrAddrGet(channel);

        if (msg != NULL)
        {
            /* Extract header */
            uint32_t header = msg->header;

            /* Extract return parameters */
            *protocolId = SCMI_HEADER_PROTOCOL_EX(header);
            *messageId = SCMI_HEADER_MSG_EX(header);
        }
        else
        {
            status = SCMI_ERR_INVALID_PARAMETERS;
        }
    }
    else
    {
        status = SCMI_ERR_PROTOCOL_ERROR;
    }

    /* Release lock */
    SCMI_P2A_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Receive P2A message                                                      */
/*--------------------------------------------------------------------------*/
int32_t SCMI_P2aRx(uint32_t channel, uint32_t protocolId,
    uint32_t messageId, uint32_t minLen, uint32_t *header)
{
    int32_t status;
    const drv_scmi_msg_status_t *msg;
    uint32_t len = 0U;

    /* Get transport buffer address */
    msg = (const drv_scmi_msg_status_t*) SCMI_HdrAddrGet(channel);

    /* Receive message via transport */
    status = SMT_Rx(channel, &len, true);

    /* Check size */
    if ((status == SCMI_ERR_SUCCESS) && (len < minLen))
    {
        status = SCMI_ERR_PROTOCOL_ERROR;
    }

    /* Extract header */
    if (status == SCMI_ERR_SUCCESS)
    {
        *header = msg->header;

        /* Check message type */
        if (SCMI_HEADER_TYPE_EX(*header) != 3U)
        {
            status = SCMI_ERR_PROTOCOL_ERROR;
        }
    }

    /* Check sequence */
    if (status == SCMI_ERR_SUCCESS)
    {
        uint32_t token = SCMI_HEADER_TOKEN_EX(*header);

        /* Check token */
        if (s_tokenCheck[channel] && (token != s_token[channel]))
        {
            status = SCMI_ERR_SEQ_ERROR;
        }

        /* Increment token */
        s_token[channel]++;
        s_token[channel] &= SCMI_HEADER_TOKEN_MASK;
    }

    /* Check protocol and message IDs */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Check parameters */
        if ((SCMI_HEADER_PROTOCOL_EX(*header) != protocolId)
            || (SCMI_HEADER_MSG_EX(*header) != messageId))
        {
            status = SCMI_ERR_PROTOCOL_ERROR;
        }
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Send P2A response                                                        */
/*--------------------------------------------------------------------------*/
int32_t SCMI_P2aTx(uint32_t channel, uint32_t len, uint32_t header)
{
    int32_t status;
    drv_scmi_msg_status_t *msg;

    /* Get transport buffer address */
    msg = (drv_scmi_msg_status_t*) SCMI_HdrAddrGet(channel);

    /* Fill in header */
    msg->header = header;

    /* Send message via transport */
    status = SMT_Tx(channel, len, true, false);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Memory copy shim                                                         */
/*--------------------------------------------------------------------------*/
void SCMI_MemCpy(uint8_t *dst, const uint8_t *src, uint32_t len)
{
    (void) memcpy((void*) dst, (const void*) src, len);
}

/*--------------------------------------------------------------------------*/
/* Bounded string copy                                                      */
/*--------------------------------------------------------------------------*/
void SCMI_StrCpy(uint8_t *dst, const uint8_t *src, uint32_t maxLen)
{
    uint8_t *pDst = dst;
    const uint8_t *pSrc = src;
    uint8_t len = 1U;

    while ((len < maxLen) && (*pSrc != 0U))
    {
        *pDst = *pSrc;
        pDst++;
        pSrc++;
        len++;
    }
    *pDst = 0U;
}

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ProtocolVersion(uint32_t channel, uint32_t protocolId,
    uint32_t *version)
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
        status = SCMI_A2pTx(channel, protocolId,
            SCMI_MSG_PROTOCOL_VERSION, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Response message structure */
        typedef struct
        {
            uint32_t header;
            int32_t status;
            uint32_t version;
        } msg_rd0_t;
        const msg_rd0_t *msgRx = (const msg_rd0_t*) msg;

        /* Receive message */
        status = SCMI_A2pRx(channel, sizeof(msg_rd0_t), header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract version */
            if (version != NULL)
            {
                *version = msgRx->version;
            }
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_ProtocolAttributes(uint32_t channel, uint32_t protocolId,
    uint32_t *attributes)
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
        status = SCMI_A2pTx(channel, protocolId,
            SCMI_MSG_PROTOCOL_ATTRIBUTES, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Response message structure */
        typedef struct
        {
            uint32_t header;
            int32_t status;
            uint32_t attributes;
        } msg_rd1_t;
        const msg_rd1_t *msgRx = (const msg_rd1_t*) msg;

        /* Receive message */
        status = SCMI_A2pRx(channel, sizeof(msg_rd1_t), header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract attributes */
            if (attributes != NULL)
            {
                *attributes = msgRx->attributes;
            }
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
int32_t SCMI_ProtocolMessageAttributes(uint32_t channel,
    uint32_t protocolId, uint32_t messageId, uint32_t *attributes)
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
            uint32_t messageId;
        } msg_td2_t;
        msg_td2_t *msgTx = (msg_td2_t*) msg;

        /* Fill in parameters */
        if (msgTx != NULL)
        {
            msgTx->messageId = messageId;
        }

        /* Send message */
        status = SCMI_A2pTx(channel, protocolId,
            SCMI_MSG_PROTOCOL_MESSAGE_ATTRIBUTES, sizeof(msg_td2_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        /* Response message structure */
        typedef struct
        {
            uint32_t header;
            int32_t status;
            uint32_t attributes;
        } msg_rd2_t;
        const msg_rd2_t *msgRx = (const msg_rd2_t*) msg;

        /* Receive message */
        status = SCMI_A2pRx(channel, sizeof(msg_rd2_t), header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract attributes */
            if (attributes != NULL)
            {
                *attributes = msgRx->attributes;
            }
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
int32_t SCMI_NegotiateProtocolVersion(uint32_t channel, uint32_t protocolId,
    uint32_t version)
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
            uint32_t version;
        } msg_td16_t;
        msg_td16_t *msgTx = (msg_td16_t*) msg;

        /* Fill in parameters */
        msgTx->version = version;

        /* Send message */
        status = SCMI_A2pTx(channel, protocolId,
            SCMI_MSG_NEGOTIATE_PROTOCOL_VERSION, sizeof(msg_td16_t),
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
/* Configure sequence checking                                              */
/*--------------------------------------------------------------------------*/
int32_t SCMI_SequenceConfig(uint32_t channel, bool enb)
{
    int32_t status = SCMI_ERR_SUCCESS;

    /* Check channel */
    if (channel < SMT_MAX_CHN)
    {
        s_tokenCheck[channel] = enb;
    }
    else
    {
        status = SCMI_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Save all channel sequences                                               */
/*--------------------------------------------------------------------------*/
void SCMI_SequenceSave(uint32_t *sequences)
{
    uint32_t *ptrSequence = sequences;

    /* Loop over */
    for (uint32_t idx = 0U; idx < SMT_MAX_CHN; idx++)
    {
        *ptrSequence = s_token[idx];
        ptrSequence++;
    }
}

/*--------------------------------------------------------------------------*/
/* Restore all channel sequences                                            */
/*--------------------------------------------------------------------------*/
void SCMI_SequenceRestore(const uint32_t *sequences)
{
    const uint32_t *ptrSequence = sequences;

    /* Loop over */
    for (uint32_t idx = 0U; idx < SMT_MAX_CHN; idx++)
    {
        s_token[idx] = *ptrSequence;
        ptrSequence++;
    }
}

