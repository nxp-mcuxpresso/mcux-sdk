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

#define COMMAND_PROTOCOL    SCMI_PROTOCOL_MISC

/*--------------------------------------------------------------------------*/
/* Get protocol version                                                     */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscProtocolVersion(uint32_t channel, uint32_t *version)
{
    /* Get version */
    return SCMI_ProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Get protocol attributes                                                  */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscProtocolAttributes(uint32_t channel, uint32_t *attributes)
{
    /* Get protocol attributes */
    return SCMI_ProtocolAttributes(channel, COMMAND_PROTOCOL,
        attributes);
}

/*--------------------------------------------------------------------------*/
/* Get protocol message attributes                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes)
{
    /* Get message attributes */
    return SCMI_ProtocolMessageAttributes(channel, COMMAND_PROTOCOL,
        messageId, attributes);
}

/*--------------------------------------------------------------------------*/
/* Set a control value                                                      */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscControlSet(uint32_t channel, uint32_t ctrlId,
    uint32_t numVal, const uint32_t *val)
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
            uint32_t ctrlId;
            uint32_t numVal;
            uint32_t val[SCMI_MISC_MAX_VAL_T];
        } msg_tmiscd3_t;
        msg_tmiscd3_t *msgTx = (msg_tmiscd3_t*) msg;

        /* Fill in parameters */
        msgTx->ctrlId = ctrlId;
        msgTx->numVal = numVal;

        SCMI_MemCpy((uint8_t*) &msgTx->val, (const uint8_t*) val,
            (SCMI_MISC_NUM_VAL_T * sizeof(uint32_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CONTROL_SET, sizeof(msg_tmiscd3_t), &header);
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
/* Get a control value                                                      */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscControlGet(uint32_t channel, uint32_t ctrlId,
    uint32_t *numVal, uint32_t *val)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numVal;
        uint32_t val[SCMI_MISC_MAX_VAL];
    } msg_rmiscd4_t;

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
            uint32_t ctrlId;
        } msg_tmiscd4_t;
        msg_tmiscd4_t *msgTx = (msg_tmiscd4_t*) msg;

        /* Fill in parameters */
        msgTx->ctrlId = ctrlId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CONTROL_GET, sizeof(msg_tmiscd4_t), &header);
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
        const msg_rmiscd4_t *msgRx = (const msg_rmiscd4_t*) msg;

        /* Extract numVal */
        if (numVal != NULL)
        {
            *numVal = msgRx->numVal;
        }

        /* Extract val */
        if (val != NULL)
        {
            SCMI_MemCpy((uint8_t*) val, (uint8_t*) &msgRx->val,
                (SCMI_MISC_NUM_VAL * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Initiate an action on a control value                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscControlAction(uint32_t channel, uint32_t ctrlId,
    uint32_t action, uint32_t numArg, const uint32_t *arg, uint32_t *numRtn,
    uint32_t *rtn)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numRtn;
        uint32_t rtn[SCMI_MISC_MAX_RTN];
    } msg_rmiscd5_t;

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
            uint32_t ctrlId;
            uint32_t action;
            uint32_t numArg;
            uint32_t arg[SCMI_MISC_MAX_ARG_T];
        } msg_tmiscd5_t;
        msg_tmiscd5_t *msgTx = (msg_tmiscd5_t*) msg;

        /* Fill in parameters */
        msgTx->ctrlId = ctrlId;
        msgTx->action = action;
        msgTx->numArg = numArg;

        SCMI_MemCpy((uint8_t*) &msgTx->arg, (const uint8_t*) arg,
            (SCMI_MISC_NUM_ARG_T * sizeof(uint32_t)));

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CONTROL_ACTION, sizeof(msg_tmiscd5_t), &header);
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
        const msg_rmiscd5_t *msgRx = (const msg_rmiscd5_t*) msg;

        /* Extract numRtn */
        if (numRtn != NULL)
        {
            *numRtn = msgRx->numRtn;
        }

        /* Extract rtn */
        if (rtn != NULL)
        {
            SCMI_MemCpy((uint8_t*) rtn, (uint8_t*) &msgRx->rtn,
                (SCMI_MISC_NUM_RTN * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get implementation build info                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscDiscoverBuildInfo(uint32_t channel, uint32_t *buildNum,
    uint32_t *buildCommit, uint8_t *buildDate, uint8_t *buildTime)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t buildNum;
        uint32_t buildCommit;
        uint8_t buildDate[SCMI_MISC_MAX_BUILDDATE];
        uint8_t buildTime[SCMI_MISC_MAX_BUILDTIME];
    } msg_rmiscd6_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_DISCOVER_BUILD_INFO, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rmiscd6_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rmiscd6_t *msgRx = (const msg_rmiscd6_t*) msg;

        /* Extract buildNum */
        if (buildNum != NULL)
        {
            *buildNum = msgRx->buildNum;
        }

        /* Extract buildCommit */
        if (buildCommit != NULL)
        {
            *buildCommit = msgRx->buildCommit;
        }

        /* Extract buildDate */
        if (buildDate != NULL)
        {
            SCMI_StrCpy(buildDate, msgRx->buildDate, SCMI_MISC_MAX_BUILDDATE);
        }

        /* Extract buildTime */
        if (buildTime != NULL)
        {
            SCMI_StrCpy(buildTime, msgRx->buildTime, SCMI_MISC_MAX_BUILDTIME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get ROM passover data                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscRomPassoverGet(uint32_t channel, uint32_t *numPassover,
    uint32_t *passover)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numPassover;
        uint32_t passover[SCMI_MISC_MAX_PASSOVER];
    } msg_rmiscd7_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_ROM_PASSOVER_GET, sizeof(header), &header);
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
        const msg_rmiscd7_t *msgRx = (const msg_rmiscd7_t*) msg;

        /* Extract numPassover */
        if (numPassover != NULL)
        {
            *numPassover = msgRx->numPassover;
        }

        /* Extract passover */
        if (passover != NULL)
        {
            SCMI_MemCpy((uint8_t*) passover, (uint8_t*) &msgRx->passover,
                (SCMI_MISC_NUM_PASSOVER * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Configure control notifications                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscControlNotify(uint32_t channel, uint32_t ctrlId,
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
            uint32_t ctrlId;
            uint32_t flags;
        } msg_tmiscd8_t;
        msg_tmiscd8_t *msgTx = (msg_tmiscd8_t*) msg;

        /* Fill in parameters */
        msgTx->ctrlId = ctrlId;
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CONTROL_NOTIFY, sizeof(msg_tmiscd8_t), &header);
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
/* Get (reset) reason attributes                                            */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscReasonAttributes(uint32_t channel, uint32_t reasonId,
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
        uint8_t name[SCMI_MISC_MAX_NAME];
    } msg_rmiscd9_t;

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
            uint32_t reasonId;
        } msg_tmiscd9_t;
        msg_tmiscd9_t *msgTx = (msg_tmiscd9_t*) msg;

        /* Fill in parameters */
        msgTx->reasonId = reasonId;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_REASON_ATTRIBUTES, sizeof(msg_tmiscd9_t),
            &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rmiscd9_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rmiscd9_t *msgRx = (const msg_rmiscd9_t*) msg;

        /* Extract attributes */
        if (attributes != NULL)
        {
            *attributes = msgRx->attributes;
        }

        /* Extract name */
        if (name != NULL)
        {
            SCMI_StrCpy(name, msgRx->name, SCMI_MISC_MAX_NAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Read the reason the LM/system last booted/shutdown/reset                 */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscResetReason(uint32_t channel, uint32_t flags,
    uint32_t *bootFlags, uint32_t *shutdownFlags, uint32_t *extInfo)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t bootFlags;
        uint32_t shutdownFlags;
        uint32_t extInfo[SCMI_MISC_MAX_EXTINFO];
    } msg_rmiscd10_t;

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
        } msg_tmiscd10_t;
        msg_tmiscd10_t *msgTx = (msg_tmiscd10_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_RESET_REASON, sizeof(msg_tmiscd10_t), &header);
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
        const msg_rmiscd10_t *msgRx = (const msg_rmiscd10_t*) msg;

        /* Extract bootFlags */
        if (bootFlags != NULL)
        {
            *bootFlags = msgRx->bootFlags;
        }

        /* Extract shutdownFlags */
        if (shutdownFlags != NULL)
        {
            *shutdownFlags = msgRx->shutdownFlags;
        }

        /* Extract extInfo */
        if (extInfo != NULL)
        {
            SCMI_MemCpy((uint8_t*) extInfo, (uint8_t*) &msgRx->extInfo,
                (SCMI_MISC_NUM_EXTINFO * sizeof(uint32_t)));
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get silicon info                                                         */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscSiInfo(uint32_t channel, uint32_t *deviceId,
    uint32_t *siRev, uint32_t *partNum, uint8_t *siName)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t deviceId;
        uint32_t siRev;
        uint32_t partNum;
        uint8_t siName[SCMI_MISC_MAX_SINAME];
    } msg_rmiscd11_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_SI_INFO, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rmiscd11_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rmiscd11_t *msgRx = (const msg_rmiscd11_t*) msg;

        /* Extract deviceId */
        if (deviceId != NULL)
        {
            *deviceId = msgRx->deviceId;
        }

        /* Extract siRev */
        if (siRev != NULL)
        {
            *siRev = msgRx->siRev;
        }

        /* Extract partNum */
        if (partNum != NULL)
        {
            *partNum = msgRx->partNum;
        }

        /* Extract siName */
        if (siName != NULL)
        {
            SCMI_StrCpy(siName, msgRx->siName, SCMI_MISC_MAX_SINAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get build config name                                                    */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscCfgInfo(uint32_t channel, uint32_t *mSel,
    uint8_t *cfgName)
{
    int32_t status;
    uint32_t header;
    const void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t mSel;
        uint8_t cfgName[SCMI_MISC_MAX_CFGNAME];
    } msg_rmiscd12_t;

    /* Acquire lock */
    SCMI_A2P_LOCK(channel);

    /* Init buffer */
    status = SCMI_BufInitC(channel, &msg);

    /* Send request */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CFG_INFO, sizeof(header), &header);
    }

    /* Receive response */
    if (status == SCMI_ERR_SUCCESS)
    {
        status = SCMI_A2pRx(channel, sizeof(msg_rmiscd12_t), header);
    }

    /* Copy out if no error */
    if (status == SCMI_ERR_SUCCESS)
    {
        const msg_rmiscd12_t *msgRx = (const msg_rmiscd12_t*) msg;

        /* Extract mSel */
        if (mSel != NULL)
        {
            *mSel = msgRx->mSel;
        }

        /* Extract cfgName */
        if (cfgName != NULL)
        {
            SCMI_StrCpy(cfgName, msgRx->cfgName, SCMI_MISC_MAX_CFGNAME);
        }
    }

    /* Release lock */
    SCMI_A2P_UNLOCK(channel);

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get system log                                                           */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscSyslog(uint32_t channel, uint32_t flags, uint32_t logIndex,
    uint32_t *numLogFlags, uint32_t *syslog)
{
    int32_t status;
    uint32_t header;
    void *msg;

    /* Response message structure */
    typedef struct
    {
        uint32_t header;
        int32_t status;
        uint32_t numLogFlags;
        uint32_t syslog[SCMI_MISC_MAX_SYSLOG];
    } msg_rmiscd13_t;

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
            uint32_t logIndex;
        } msg_tmiscd13_t;
        msg_tmiscd13_t *msgTx = (msg_tmiscd13_t*) msg;

        /* Fill in parameters */
        msgTx->flags = flags;
        msgTx->logIndex = logIndex;

        /* Send message */
        status = SCMI_A2pTx(channel, COMMAND_PROTOCOL, SCMI_MSG_MISC_SYSLOG,
            sizeof(msg_tmiscd13_t), &header);
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
        const msg_rmiscd13_t *msgRx = (const msg_rmiscd13_t*) msg;

        /* Extract numLogFlags */
        if (numLogFlags != NULL)
        {
            *numLogFlags = msgRx->numLogFlags;
        }

        /* Extract syslog */
        if (syslog != NULL)
        {
            SCMI_MemCpy((uint8_t*) syslog, (uint8_t*) &msgRx->syslog,
                (SCMI_MISC_NUM_SYSLOG * sizeof(uint32_t)));
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
int32_t SCMI_MiscNegotiateProtocolVersion(uint32_t channel,
    uint32_t version)
{
    /* Negotiate protocol version */
    return SCMI_NegotiateProtocolVersion(channel, COMMAND_PROTOCOL, version);
}

/*--------------------------------------------------------------------------*/
/* Read control notification event                                          */
/*--------------------------------------------------------------------------*/
int32_t SCMI_MiscControlEvent(uint32_t channel, uint32_t *ctrlId,
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
            uint32_t ctrlId;
            uint32_t flags;
        } msg_rmisced32_t;
        const msg_rmisced32_t *msgRx = (const msg_rmisced32_t*) msg;

        /* Receive message */
        status = SCMI_P2aRx(channel, COMMAND_PROTOCOL,
            SCMI_MSG_MISC_CONTROL_EVENT, sizeof(msg_rmisced32_t), &header);

        /* Copy out if no error */
        if (status == SCMI_ERR_SUCCESS)
        {
            /* Extract ctrlId */
            if (ctrlId != NULL)
            {
                *ctrlId = msgRx->ctrlId;
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

