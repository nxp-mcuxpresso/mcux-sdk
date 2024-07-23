/*
 * Copyright 2019-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_elemu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.elemu"
#endif

#define ELEMU_READY_WAIT_TIME 0xFFFFFFFFU
#define ELEMU_RESET_COMPLETED (0x1B00803Cu)
#define ELEMU_RESET_STARTED   (0x1700D03Cu)

static status_t ELEMU_StartupWait(ELEMU_Type *mu);

#if (defined(ELEMU_HAS_LOADABLE_FW) && ELEMU_HAS_LOADABLE_FW)
#include "fsl_sss_mgmt.h"
#include "fsl_sss_sscp.h"
#include "fsl_sscp_mu.h"

#endif
/* ELEMU driver */

#define BIT(x)         (((uint32_t)1u << (x)))
#define MU_READ_HEADER (0x01u)
#define READ_RETRIES   (0x5u)

#define MU_SEMA4_RESERVED_BY_OTHER (0xFFFFFFAAu)
#define MU_SEMA4_LOCKED_TO_CURRENT (0x00000055u)
#define MU_SEMA4_FREE              (0x0u)

typedef struct mu_message
{
    mu_hdr_t header;
    uint32_t payload[ELEMU_TR_COUNT - MU_MSG_HEADER_SIZE];
} mu_message_t;

void ELEMU_mu_hal_send_data(ELEMU_Type *mu, uint8_t regid, uint32_t *data)
{
    uint32_t mask = (BIT(regid));
    while ((mu->TSR & mask) == 0u)
    {
    }
    mu->TR[regid] = *data;
}

void ELEMU_mu_hal_receive_data(ELEMU_Type *mu, uint8_t regid, uint32_t *data)
{
    uint32_t mask        = BIT(regid);
    uint8_t read_retries = READ_RETRIES;
    while ((mu->RSR & mask) == 0u)
    {
    }
    *data = mu->RR[regid];
    while (((mu->RSR & mask) != 0u) && (read_retries != 0u))
    {
        *data = mu->RR[regid];
        read_retries--;
    }
}

status_t ELEMU_mu_hal_receive_data_wait(ELEMU_Type *mu, uint8_t regid, uint32_t *data, uint32_t wait)
{
    uint32_t mask        = BIT(regid);
    uint8_t read_retries = READ_RETRIES;
    status_t ret         = 0;
    while ((mu->RSR & mask) == 0u)
    {
        if (--wait == 0u)
        {
            ret = kStatus_ELEMU_RequestTimeout;
            break;
        }
    }
    if (ret != kStatus_ELEMU_RequestTimeout)
    {
        *data = mu->RR[regid];
        while (((mu->RSR & mask) != 0u) && (read_retries != 0u))
        {
            *data = mu->RR[regid];
            read_retries--;
        }
        ret = kStatus_Success;
    }
    return ret;
}

status_t ELEMU_mu_send_message(ELEMU_Type *mu, uint32_t buf[], size_t wordCount)
{
    uint8_t tx_reg_idx = 0u;
    uint8_t counter    = 0u;
    status_t ret       = kStatus_Fail;
    if (buf == NULL)
    {
        ret = kStatus_ELEMU_InvalidArgument;
    }
    else if (wordCount > ELEMU_TR_COUNT)
    {
        ret = kStatus_ELEMU_AgumentOutOfRange;
    }
    else
    {
        while (wordCount > 0u)
        {
            tx_reg_idx = tx_reg_idx % ELEMU_TR_COUNT;
            ELEMU_mu_hal_send_data(mu, tx_reg_idx, &buf[counter]);
            tx_reg_idx++;
            counter++;
            wordCount--;
        }
        ret = kStatus_Success;
    }
    return ret;
}

status_t ELEMU_mu_wait_for_ready(ELEMU_Type *mu, uint32_t wait)
{
    if (kStatus_Success != ELEMU_LP_WakeupPathInit(mu))
    {
        return kStatus_ELEMU_RequestTimeout;
    }

#if (defined(FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER) && FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER)
    status_t ret = kStatus_ELEMU_RequestTimeout;
    if (wait == 0u)
    {
        if ((ELEMUA->SEMA4_SR & (ELEMU_SEMA4_SR_MISC_BSY(0x30) | ELEMU_SEMA4_SR_SSS_CIP1_MASK)) == 0u)
        {
            ret = kStatus_Success;
        }
    }
    else
    {
        do
        {
            if ((ELEMUA->SEMA4_SR & (ELEMU_SEMA4_SR_MISC_BSY(0x30) | ELEMU_SEMA4_SR_SSS_CIP1_MASK)) == 0u)
            {
                ret = kStatus_Success;
                break;
            }
            wait--;
        } while (wait != 0u);
    }
    return ret;
#else /* FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER */
    return kStatus_Success;
#endif
}
#if (defined(FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER) && FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER)
elemu_ownership_status_t ELEMU_mu_get_ownership_status(ELEMU_Type *mu)
{
    elemu_ownership_status_t ret = kStatus_ELEMU_Unknown;
    uint32_t result              = mu->SEMA4_OWNR;
    if (result == MU_SEMA4_LOCKED_TO_CURRENT)
    {
        ret = kStatus_ELEMU_LockedByMe;
    }
    else if (result == MU_SEMA4_RESERVED_BY_OTHER)
    {
        ret = kStatus_ELEMU_LockedByOther;
    }
    else if (result == MU_SEMA4_FREE)
    {
        ret = kStatus_ELEMU_Free;
    }
    else
    {
        ret = kStatus_ELEMU_Unknown;
    }
    return ret;
}

status_t ELEMU_mu_get_ownership(ELEMU_Type *mu)
{
    status_t ret    = kStatus_Fail;
    uint32_t result = mu->SEMA4_ACQ;
    if (result == MU_SEMA4_LOCKED_TO_CURRENT)
    {
        ret = kStatus_Success;
    }
    else if (result == MU_SEMA4_RESERVED_BY_OTHER)
    {
        ret = kStatus_ELEMU_Busy;
    }
    else
    {
        ret = kStatus_Fail;
    }
    return ret;
}

status_t ELEMU_mu_release_ownership(ELEMU_Type *mu)
{
    status_t ret    = kStatus_Fail;
    uint32_t result = mu->SEMA4_REL;
    if (result == MU_SEMA4_FREE)
    {
        ret = kStatus_Success;
    }
    else if (result == MU_SEMA4_RESERVED_BY_OTHER)
    {
        ret = kStatus_ELEMU_Busy;
    }
    else
    {
        ret = kStatus_Fail;
    }
    return ret;
}

status_t ELEMU_mu_release_ownership_force(ELEMU_Type *mu)
{
    status_t ret    = kStatus_Fail;
    uint32_t result = mu->SEMA4_FREL;
    if (result == MU_SEMA4_FREE)
    {
        ret = kStatus_Success;
    }
    else if (result == MU_SEMA4_RESERVED_BY_OTHER)
    {
        ret = kStatus_ELEMU_Busy;
    }
    else
    {
        ret = kStatus_Fail;
    }
    return ret;
}
#endif /* FSL_FEATURE_ELEMU_HAS_SEMA4_STATUS_REGISTER */

status_t ELEMU_mu_read_message(ELEMU_Type *mu, uint32_t *buf, uint8_t *size, uint8_t read_header)
{
    uint8_t msg_size   = 0u;
    uint8_t rx_reg_idx = 0u;
    mu_message_t *msg  = (mu_message_t *)(uintptr_t)buf;
    uint32_t counter   = 0u;
    status_t ret       = kStatus_Fail;

    if ((buf == NULL) || (size == NULL))
    {
        ret = kStatus_ELEMU_InvalidArgument;
    }
    else
    {
        if (read_header == MU_READ_HEADER)
        {
            ELEMU_mu_hal_receive_data(mu, rx_reg_idx, (uint32_t *)(uintptr_t)&msg->header);
            msg_size = msg->header.size;
            rx_reg_idx++;
            *size = msg_size + 1u;
        }
        else
        {
            msg_size = *size;
        }

        while (msg_size > 0u)
        {
            rx_reg_idx = rx_reg_idx % ELEMU_RR_COUNT;
            ELEMU_mu_hal_receive_data(mu, rx_reg_idx, &msg->payload[counter]);
            rx_reg_idx++;
            counter++;
            msg_size--;
        }
        ret = kStatus_Success;
    }
    return ret;
}

status_t ELEMU_mu_read_data_wait(ELEMU_Type *mu, uint32_t buf[], uint8_t *size, uint32_t wait)
{
    uint8_t msg_size   = 0u;
    uint8_t counter    = 0u;
    uint8_t rx_reg_idx = 0u;
    status_t ret       = kStatus_Success;

    if ((buf == NULL) || (size == NULL))
    {
        ret = kStatus_ELEMU_InvalidArgument;
    }
    else
    {
        msg_size = *size;
        while (msg_size > 0u)
        {
            rx_reg_idx = rx_reg_idx % ELEMU_RR_COUNT;
            if (wait > 0u)
            {
                if ((ret = ELEMU_mu_hal_receive_data_wait(mu, rx_reg_idx, &buf[counter], wait)) != kStatus_Success)
                {
                    break;
                }
            }
            else
            {
                ELEMU_mu_hal_receive_data(mu, rx_reg_idx, &buf[counter]);
            }
            rx_reg_idx++;
            counter++;
            msg_size--;
        }
    }
    return ret;
}

status_t ELEMU_mu_get_response(ELEMU_Type *mu, uint32_t *buf, size_t wordCount)
{
    uint8_t size = (uint8_t)wordCount;
    status_t ret;
    if (buf == NULL)
    {
        ret = kStatus_ELEMU_InvalidArgument;
    }
    else if (wordCount > ELEMU_RR_COUNT)
    {
        ret = kStatus_ELEMU_AgumentOutOfRange;
    }
    else
    {
        ret = ELEMU_mu_read_message(mu, buf, &size, MU_READ_HEADER);
    }
    return ret;
}

status_t ELEMU_mu_wait_for_data(ELEMU_Type *mu, uint32_t *buf, size_t wordCount, uint32_t wait)
{
    uint8_t size = (uint8_t)wordCount;
    status_t ret;
    if (buf == NULL)
    {
        ret = kStatus_ELEMU_InvalidArgument;
    }
    else if (wordCount > ELEMU_RR_COUNT)
    {
        ret = kStatus_ELEMU_AgumentOutOfRange;
    }
    else
    {
        ret = ELEMU_mu_read_data_wait(mu, buf, &size, wait);
    }
    return ret;
}

void ELEMU_mu_init(ELEMU_Type *mu)
{
    /* nothing to do for initialization */
}

static status_t ELEMU_StartupWait(ELEMU_Type *mu)
{
    uint32_t msg[2] = {0};
    status_t status = kStatus_Fail;

    if (kStatus_Success != ELEMU_mu_wait_for_data(mu, msg, 2u, ELEMU_READY_WAIT_TIME))
    {
    }
    else if (msg[0] != ELEMU_RESET_STARTED)
    {
        status = kStatus_Fail;
    }
    else if (msg[1] != ELEMU_RESET_COMPLETED)
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

status_t ELEMU_LP_WakeupPathInit(ELEMU_Type *mu)
{
    status_t status = kStatus_Fail;

    do
    {
        /* read current value of the MRCC_SECSUBSYS register */
        uint32_t mrcc_secsubsys = CLOCK_REG(kCLOCK_Secsubsys);

        /* test if the module is released from reset and clocks are enabled */
        if (((mrcc_secsubsys & MRCC_RSTB_MASK) == MRCC_RSTB_MASK) && ((mrcc_secsubsys & MRCC_CC_MASK) != 0x0u))
        {
            status = kStatus_Success;
        }

        /* apply the requested MRCC_SECSUBSYS[CC] (control) */
        /* the actual non-zero CC value might be different from the setting configured by ROM bootloader */
        /* the MRCC_SECSUBSYS[CC] is set to 2'b11  */
        CLOCK_EnableClockLPMode(kCLOCK_Secsubsys, kCLOCK_IpClkControl_fun3);

        /* the module is running and the CC is configured, return */
        if (kStatus_Success == status)
        {
            break;
        }

        /* the module is NOT running at the time when this function is entered. */
        /* therefore, wait for its startup sequence to complete */
        status = ELEMU_StartupWait(mu);
    } while (false);

    return status;
}

#if (defined(ELEMU_HAS_LOADABLE_FW) && ELEMU_HAS_LOADABLE_FW)

/* Tunnel type is EdgeLock Firmware upload */
#define TUNNEL_TYPE_SB3_ELE_FW   0x22u
#define SB3_BLOCK0_SIZE_IN_BYTES 0x60u

status_t ELEMU_loadFw(ELEMU_Type *mu, uint32_t image[])
{
    uint32_t resultState = 0u;
    sss_sscp_tunnel_t tunnelCtx;
    sss_sscp_session_t sssSession;
    sscp_context_t sscpContext;
    status_t status = kStatus_Fail;
    do
    {
        if (sscp_mu_init(&(sscpContext), (ELEMU_Type *)mu) != kStatus_SSCP_Success)
        {
            break;
        }
        /* OPEN SESSION */
        if (sss_sscp_open_session(&sssSession, 0u, kType_SSS_Ele200, &sscpContext) != kStatus_SSS_Success)
        {
            break;
        }

        /* OPEN TUNNEL */
        if (sss_sscp_tunnel_context_init(&tunnelCtx, &sssSession, TUNNEL_TYPE_SB3_ELE_FW) != kStatus_SSS_Success)
        {
            break;
        }

        /* Pass loadable ELE FW */
        if (sss_sscp_tunnel(&tunnelCtx, (uint8_t *)image, SB3_BLOCK0_SIZE_IN_BYTES, &resultState) !=
            kStatus_SSS_Success)
        {
            break;
        }

        /* If all steps before passes without break, then consider it as success*/
        status = kStatus_Success;

    } while (false);
    /* FREE TUNNEL CONTEXT */
    sss_sscp_tunnel_context_free(&tunnelCtx);
    /* CLOSE SESSION */
    sss_sscp_close_session(&sssSession);

    return status;
}

#endif /* ELEMU_HAS_LOADABLE_FW */
