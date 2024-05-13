/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "fsl_s3mu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.s3mu"
#endif

/*******************************************************************************
 * Definitions
 *******************************************************************************/

#define BIT(x)         (uint32_t)(1UL << (x))
#define MU_READ_HEADER (0x01u)
#define GET_HDR_SIZE(x)   (((x) & (uint32_t)0xFF00) >> 8u)

typedef struct mu_message
{
    mu_hdr_t header;
    uint32_t payload[S3MU_TR_COUNT - MU_MSG_HEADER_SIZE];
} mu_message_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void s3mu_hal_send_data(S3MU_Type *mu, uint32_t regid, uint32_t *data);
static void s3mu_hal_receive_data(S3MU_Type *mu, uint32_t regid, uint32_t *data);
static status_t s3mu_read_data_wait(S3MU_Type *mu, uint32_t *buf, uint8_t *size, uint32_t wait);
static status_t s3mu_hal_receive_data_wait(S3MU_Type *mu, uint8_t regid, uint32_t *data, uint32_t wait);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Send message to MU
 *
 * This function writes messgae into MU regsters and send message to EdgeLock Enclave.
 *
 * param base MU peripheral base address
 * param buf buffer to store read data
 * param wordCount size of data in words
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_SendMessage(S3MU_Type *mu, void *buf, size_t wordCount)
{
    uint8_t tx_reg_idx = 0u;
    uint8_t counter    = 0u;
    status_t ret       = kStatus_Fail;
    if (buf == NULL)
    {
        ret = kStatus_S3MU_InvalidArgument;
    }
    else
    {
        while (wordCount != 0u)
        {
            tx_reg_idx = tx_reg_idx % S3MU_TR_COUNT;
            s3mu_hal_send_data(mu, tx_reg_idx, (uint32_t*)buf+counter);
            tx_reg_idx++;
            counter++;
            wordCount--;
        }
        ret = kStatus_Success;
    }
    return ret;
}

/* Static function to write one word to transmit register specified by index */
static void s3mu_hal_send_data(S3MU_Type *mu, uint32_t regid, uint32_t *data)
{
    uint32_t mask = (BIT(regid));
    while ((mu->TSR & mask) == 0u)
    {
    }
    mu->TR[regid] = *data;
}

/*!
 * brief Get response from MU
 *
 * This function reads response data from EdgeLock Enclave if available.
 *
 * param base MU peripheral base address
 * param buf buffer to store read data
 * param wordCount size of data in words
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_GetResponse(S3MU_Type *mu, void *buf)
{
    size_t size;
    (void)size; /* Not used here */

    if (buf == NULL)
    {
        return kStatus_S3MU_InvalidArgument;
    }

    return S3MU_ReadMessage(mu, buf, &size, MU_READ_HEADER);
}

/*!
 * brief Read message from MU
 *
 * This function reads message date from EdgeLock Enclave if available.
 *
 * param base MU peripheral base address
 * param buf buffer to store read data
 * param size If read_header equals MU_READ_HEADER, size represent number of word obtained from header.
 *            If read header not equals MU_READ_HEADER, size is used to determine number of word to be read.
 * param read_header specifies if size is obtained by response header or provided in parameter.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_ReadMessage(S3MU_Type *mu, uint32_t *buf, size_t *size, uint8_t read_header)
{
    uint32_t msg_size   = 0u;
    uint32_t rx_reg_idx = 0u;
    uint32_t *buf_ptr  = buf;
    status_t ret       = kStatus_Fail;

    if ((buf == NULL) || (size == NULL))
    {
        ret = kStatus_S3MU_InvalidArgument;
    }
    else
    {
        if (read_header == MU_READ_HEADER)
        {
            s3mu_hal_receive_data(mu, rx_reg_idx, buf);
            msg_size = (GET_HDR_SIZE(buf[0]));
            *size    = msg_size;
            rx_reg_idx++;
            msg_size--; /* payload size = size - 1 (header) */
        }
        else
        {
            msg_size = *size;
        }

        while (msg_size != 0u)
        {
            rx_reg_idx = rx_reg_idx % S3MU_RR_COUNT;
            buf_ptr++;
            s3mu_hal_receive_data(mu, rx_reg_idx, buf_ptr);
            rx_reg_idx++;
            msg_size--;
        }
        ret = kStatus_Success;
    }
    return ret;
}

/* Static function to retrieve one word from receive register specified by index */
static void s3mu_hal_receive_data(S3MU_Type *mu, uint32_t regid, uint32_t *data)
{
    uint32_t mask = BIT(regid);

    while ((mu->RSR & mask) == 0u)
    {
    }

    *data = mu->RR[regid];
}

/*!
 * brief Wait and Read data from MU
 *
 * This function wait limited time (ticks) and tests if data are ready to be read.
 * When data are ready, reads them into buffer.
 *
 * param base MU peripheral base address
 * param buf buffer to store read data
 * param wordCount size of data in words
 * param wait number of iterations to wait
 *
 * return Status kStatus_Success if success, kStatus_S3MU_RequestTimeout if timeout
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_WaitForData(S3MU_Type *mu, uint32_t *buf, size_t wordCount, uint32_t wait)
{
    uint8_t size = (uint8_t)wordCount;
    status_t ret;
    if (buf == NULL)
    {
        ret = kStatus_S3MU_InvalidArgument;
    }
    else if (wordCount > S3MU_RR_COUNT)
    {
        ret = kStatus_S3MU_AgumentOutOfRange;
    }
    else
    {
        ret = s3mu_read_data_wait(mu, buf, &size, wait);
    }
    return ret;
}

/* Static function to retrieve message form retrieve registers with wait */
static status_t s3mu_read_data_wait(S3MU_Type *mu, uint32_t *buf, uint8_t *size, uint32_t wait)
{
    uint8_t msg_size   = *size;
    uint8_t counter    = 0u;
    uint8_t rx_reg_idx = 0u;
    status_t ret       = kStatus_Success;

    if ((buf == NULL) || (size == NULL))
    {
        ret = kStatus_S3MU_InvalidArgument;
    }
    else
    {
        while (msg_size != 0u)
        {
            rx_reg_idx = rx_reg_idx % S3MU_RR_COUNT;
            if (wait != 0u)
            {
                if ((ret = s3mu_hal_receive_data_wait(mu, rx_reg_idx, &buf[counter], wait)) != kStatus_Success)
                {
                    break;
                }
            }
            else
            {
                s3mu_hal_receive_data(mu, rx_reg_idx, &buf[counter]);
            }
            rx_reg_idx++;
            counter++;
            msg_size--;
        }
    }
    return ret;
}

/* Static function to retrieve one word from receive register specified by index with wait */
static status_t s3mu_hal_receive_data_wait(S3MU_Type *mu, uint8_t regid, uint32_t *data, uint32_t wait)
{
    uint32_t mask = BIT(regid);
    status_t ret = kStatus_Fail;
    while ((mu->RSR & mask) == 0u)
    {
        if (--wait == 0u)
        {
            ret = kStatus_S3MU_RequestTimeout;
            break;
        }
    }
    if (ret != kStatus_S3MU_RequestTimeout)
    {
        *data = mu->RR[regid];
        ret   = kStatus_Success;
    }
    return ret;
}

/*!
 * brief Init MU
 *
 * This function does nothing. MU is initialized after leaving ROM.
 *
 * param base MU peripheral base address
 */
void S3MU_Init(S3MU_Type *mu)
{
    /* nothing to do for initialization */
}

/*!
 * brief Computes CRC
 *
 * This function computes CRC of input message.
 *
 * param msg pointer to message
 * param msg_len size of message in words
 *
 * return CRC32 checksum value
 */
uint32_t S3MU_ComputeMsgCrc(uint32_t *msg, uint32_t msg_len)
{
    uint32_t crc;
    uint32_t i;

    crc = 0u;
    for (i = 0u; i < msg_len; i++)
    {
        crc ^= *(msg + i);
    }
    return crc;
}
