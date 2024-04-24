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

/*==========================================================================*/
/* File containing the implementation of the Shared Memory Transport (SMT). */
/*==========================================================================*/

/* Includes */

#include "smt.h"
#ifndef SMT_LOOPBACK
#include "fsl_device_registers.h"
#include "fsl_mu.h"
#else
#include "mb_loopback.h"
#endif
#include "crc.h"

/* Local defines */

#define SMT_FREE      (1UL << 0U)
#define SMT_ERROR     (1UL << 1U)
#define SMT_COMP_INT  (1UL << 0U)

/* Local types */

typedef struct
{
    bool valid;          /*! Channel configured and valid */
    uint8_t mbInst;      /*!< Mailbox instance */
    uint8_t mbDoorbell;  /*!< Mailbox doorbell */
    uint32_t sma;        /*!< Shared memory address */
} smt_chn_config_t;

typedef struct
{
    uint32_t resv;
    volatile uint32_t channelStatus;
    uint32_t impStatus;
    uint32_t impCrc;
    uint32_t channelFlags;
    uint32_t length;
    uint32_t header;
    uint32_t payload[SMT_BUFFER_PAYLOAD / 4U];
} smt_buf_t;

/* Local variables */

static smt_chn_config_t s_smtConfig[SMT_MAX_CHN];

#ifndef SMT_LOOPBACK
static MU_Type *const s_muBases[] = MU_BASE_PTRS;
#endif

/* Local functions */

static smt_buf_t *SMT_SmaGet(uint32_t smtChannel);

/*--------------------------------------------------------------------------*/
/* Configure an SMT channel                                                 */
/*--------------------------------------------------------------------------*/
int32_t SMT_ChannelConfig(uint32_t smtChannel, uint8_t mbInst,
    uint8_t mbDoorbell, uint32_t sma)
{
    int32_t status = SMT_ERR_SUCCESS;

    if (smtChannel < SMT_MAX_CHN)
    {
        s_smtConfig[smtChannel].mbInst = mbInst;
        s_smtConfig[smtChannel].mbDoorbell = mbDoorbell;
        s_smtConfig[smtChannel].sma = sma;
        s_smtConfig[smtChannel].valid = true;
    }
    else
    {
        status = SMT_ERR_INVALID_PARAMETERS;
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* Get SMT header address                                                   */
/*--------------------------------------------------------------------------*/
void *SMT_HdrAddrGet(uint32_t smtChannel)
{
    void *rtn = NULL;
    smt_buf_t *buf = SMT_SmaGet(smtChannel);

    /* Get address of header */
    if (buf != NULL)
    {
        rtn = (void*) &buf->header;
    }

    /* Return address */
    return rtn;
}

/*--------------------------------------------------------------------------*/
/* Get SMT channel free status                                              */
/*--------------------------------------------------------------------------*/
bool SMT_ChannelFree(uint32_t smtChannel)
{
    const smt_buf_t *buf = (const smt_buf_t*) SMT_SmaGet(smtChannel);
    bool freeState = true;

    /* Check for valid buffer */
    if (buf != NULL)
    {
        freeState = ((buf->channelStatus & SMT_FREE) != 0U);
    }

    /* Return state */
    return freeState;
}

/*--------------------------------------------------------------------------*/
/* Set abort state                                                          */
/*--------------------------------------------------------------------------*/
int32_t SMT_AbortSet(uint32_t smtChannel, bool state)
{
    int32_t status = SMT_ERR_SUCCESS;
    uint8_t inst = s_smtConfig[smtChannel].mbInst;

#ifndef SMT_LOOPBACK
    /* Get base */
    MU_Type *base = s_muBases[inst];

    /* Set flag F0 (bit 0) */
    if (state)
    {
        MU_SetFlags(base, 1U);
    }
    else
    {
        MU_SetFlags(base, 0U);
    }
#else
    /* Call SMT server */
    status = MB_LOOPBACK_AbortSet(inst, state);
#endif

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* SMT send                                                                 */
/*--------------------------------------------------------------------------*/
int32_t SMT_Tx(uint32_t smtChannel, uint32_t len, bool callee,
    bool compInt)
{
    int32_t status = SMT_ERR_SUCCESS;
    uint8_t inst = s_smtConfig[smtChannel].mbInst;
    uint8_t db = s_smtConfig[smtChannel].mbDoorbell;
    smt_buf_t *buf = (smt_buf_t*) SMT_SmaGet(smtChannel);

    /* Check length */
    if (len > (SMT_BUFFER_SIZE - SMT_BUFFER_HEADER))
    {
        status = SMT_ERR_PROTOCOL_ERROR;
    }
    else
    {
        uint32_t impStatus = buf->impStatus;

        if (callee)
        {
            /* Wait until channel is busy */
            while (SMT_ChannelFree(smtChannel))
            {
                ; /* Intentional empty while */
            }
        }
        else
        {
            /* Wait until channel is free */
            while (!SMT_ChannelFree(smtChannel))
            {
                ; /* Intentional empty while */
            }
        }

        /* Fill in reserved */
        buf->resv = 0U;

        /* Completion interrupt if caller wants */
        if (!callee)
        {
            if (compInt)
            {
                buf->channelFlags = SMT_COMP_INT;
            }
            else
            {
                buf->channelFlags = 0U;
            }
        }

        /* Fill in length */
        buf->length = len;

        /* Calculate CRC */
        switch (impStatus)
        {
            case SMT_CRC_XOR:
                buf->impCrc = CRC_Xor((const uint32_t*) &buf->header,
                    len / 4U);
                break;
            case SMT_CRC_CRC32:
                buf->impCrc = CRC_Crc32((const uint8_t*) &buf->header,
                    len);
                break;
            default:
                ; /* Intentional empty while */
                break;
        }

        if (callee)
        {
            /* Mark as free */
            buf->channelStatus |= SMT_FREE;
        }
        else
        {
            /* Mark as busy */
            buf->channelStatus &= ~SMT_FREE;
        }

#ifndef SMT_LOOPBACK
        /* Get base */
        MU_Type *base = s_muBases[inst];

        /* Trigger GI interrupt */
        (void) MU_TriggerInterrupts(base,
            ((uint32_t) kMU_GenInt0InterruptTrigger) << db);
#else
        /* Call SMT server */
        status = MB_LOOPBACK_DoorbellRing(inst, db);
#endif
    }

    /* Return status */
    return status;
}

/*--------------------------------------------------------------------------*/
/* SMT receive                                                              */
/*--------------------------------------------------------------------------*/
int32_t SMT_Rx(uint32_t smtChannel, uint32_t *len, bool callee)
{
    int32_t status = SMT_ERR_SUCCESS;
    const smt_buf_t *buf = (const smt_buf_t*) SMT_SmaGet(smtChannel);

    /* Check buffer */
    if (buf == NULL)
    {
        status = SMT_ERR_INVALID_PARAMETERS;
    }
    else
    {
        uint32_t impStatus = buf->impStatus;
        const void *msgRx = SMT_HdrAddrGet(smtChannel);

        if (callee)
        {
            /* Wait until channel is busy */
            while (SMT_ChannelFree(smtChannel))
            {
                ; /* Intentional empty while */
            }
        }
        else
        {
            /* Wait until channel is free */
            while (!SMT_ChannelFree(smtChannel))
            {
                ; /* Intentional empty while */
            }
        }

        /* Record the length */
        *len = buf->length;

        /* Check the CRC */
        switch (impStatus)
        {
            case SMT_CRC_XOR:
                if (buf->impCrc != CRC_Xor((const uint32_t*) msgRx,
                    *len / 4U))
                {
                    status = SMT_ERR_CRC_ERROR;
                }
                break;
            case SMT_CRC_CRC32:
                if (buf->impCrc != CRC_Crc32((const uint8_t*) msgRx, *len))
                {
                    status = SMT_ERR_CRC_ERROR;
                }
                break;
            default:
                ; /* Intentional empty while */
                break;
        }
    }

    /* Return status */
    return status;
}

/*==========================================================================*/

/*--------------------------------------------------------------------------*/
/* Get SMT SMA                                                              */
/*--------------------------------------------------------------------------*/
static smt_buf_t *SMT_SmaGet(uint32_t smtChannel)
{
    smt_buf_t *rtn = NULL;

    /* Check channel */
    if ((smtChannel < SMT_MAX_CHN) && (s_smtConfig[smtChannel].valid))
    {
        uint8_t inst = s_smtConfig[smtChannel].mbInst;
        uint8_t db = s_smtConfig[smtChannel].mbDoorbell;

#ifndef SMT_LOOPBACK
        uint32_t sma = s_smtConfig[smtChannel].sma;

        /* Allow use of internal MU SRAM */
        if (sma == 0U)
        {
            sma = ((uint32_t)(uintptr_t) s_muBases[inst]) + 0x1000U;
        }

        /* Apply channel spacing */
        sma += ((uint32_t) db) * SMT_BUFFER_SIZE;

        /* Set return */
        rtn = (smt_buf_t*)(uintptr_t) sma;
#else
        /* Set return */
        rtn = (smt_buf_t*) MB_LOOPBACK_SmaGet(inst, db);
#endif
    }

    return rtn;
}

