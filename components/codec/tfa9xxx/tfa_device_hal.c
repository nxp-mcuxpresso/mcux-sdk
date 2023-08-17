/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "tfa_device_hal.h"
#include "usb.h"
#include "usb_device_descriptor.h"

/*******************************************************************************
 * Variables
 *******************************************************************************/
tfa_hal_msg_status_t g_TfaDeviceMessageStatus = {.msgComplete = 0, .totalSend = 0};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Collect a message chuck into a internal buffer.
 *
 * @param handle TFA9XXX handle structure.
 * @param chunk The message chunk.
 * @param length Length of the message to be collected.
 * @return uint8_t returns 1 when a complete message is collected, returns 0 when there is still remaining to be
 * collected.
 */
uint8_t TFA_Hal_CollectMsg(tfa9xxx_handle_t *handle, uint8_t *chunk, uint32_t length)
{
    static uint8_t rcvBuffer[TFA_BUFFERSIZE];
    struct _tfa_hal_msg *msg = (struct _tfa_hal_msg *)rcvBuffer;
    static uint32_t totalRcv = 0;
    uint8_t *prcv            = &rcvBuffer[totalRcv];

    if (length > USB_HID_GENERIC_OUT_BUFFER_LENGTH)
        return 0;

    // collect msg chunks
    memcpy(prcv, chunk, length);
    totalRcv += length;
    prcv += length;
    if (totalRcv < sizeof(struct _tfa_hal_msg))
    {
        // TODO validate msg here
        // get the rest, if needed
        return 0;
    }
    else if (totalRcv < sizeof(struct _tfa_hal_msg) + msg->wlength)
    {
        return 0;
    }
    else
    {
        memcpy(g_TfaDeviceMessageStatus.sndBuffer, msg, totalRcv);
        TFA_Hal_ProcessMsg(handle, msg, g_TfaDeviceMessageStatus.sndBuffer);
        totalRcv                             = 0;
        g_TfaDeviceMessageStatus.totalSend   = USB_HID_GENERIC_OUT_BUFFER_LENGTH; // TODO errorcheck
        g_TfaDeviceMessageStatus.msgComplete = 1;
        return 1;
    }

    return 0;
}

/*!
 * @brief Process the message collected.
 *
 * @param handle TFA9XXX handle structure.
 * @param inBuffer Input message buffer.
 * @param outBuffer Output (return) message buffer.
 * @retval 0 Message is processed successfully.
 * @retval EIO I2C error.
 * @retval EINVAL Message CRC check failed or command inside the message is invalid.
 */
int32_t TFA_Hal_ProcessMsg(tfa9xxx_handle_t *handle, void *inBuffer, void *outBuffer)
{
    struct _tfa_hal_msg *msg  = (struct _tfa_hal_msg *)inBuffer;
    struct _tfa_hal_msg *rmsg = (struct _tfa_hal_msg *)outBuffer;
    int32_t ret;
    uint32_t msgSize;
    uint8_t address = 0;

#ifdef TFA_HAL_DEBUG
    TFA_Hal_DumpMsg(msg, 1);
#endif

    /* crc32 check of arrived message, only a write message contains a payload */
    msgSize = (int16_t)msg->wlength + sizeof(struct _tfa_hal_msg);
    ret     = TFA_Hal_CheckMsgCRC(msg, msgSize);
    memcpy(rmsg, msg, sizeof(struct _tfa_hal_msg));

    if (ret >= 0)
    {
        switch (msg->cmd)
        {
            case TFA_HAL_MSG_I2C:
            {
                address          = msg->data[0] >> 1;
                uint8_t *in_buf  = &msg->data[1];
                size_t in_bytes  = msg->wlength - 1;
                uint8_t *out_buf = rmsg->data;
                size_t out_bytes = rmsg->rlength;
                ret = TFA_I2C_WriteReadRaw(handle, address, in_bytes, in_buf, out_bytes, out_buf) ? -EIO : 0;
            }
            break;
            case TFA_HAL_MSG_VERSION:
                break;
            default:
                /* Unsupported command */
                ret = -EINVAL;
                break;
        }
    }

    /* set return message ID + server error code */
    rmsg->cmd_lsb = 'r';
    rmsg->error   = ret;

    /* add crc32 to outgoing message, only a read contains extra bytes */
    msgSize = (int16_t)msg->rlength + sizeof(struct _tfa_hal_msg);

    TFA_Hal_AddMsgCRC(rmsg, msgSize);

#ifdef TFA_HAL_DEBUG
    TFA_Hal_DumpMsg(rmsg, 0);
#endif

    return ret;
}

/*!
 * @brief Get the length of the next message chunk for the device to sent. If the length is 0, it means the whole
 * message has been sent.
 *
 * @param maxChunkLength Max length to be sent.
 * @return uint32_t The length of next message chunk to be sent.
 */
uint32_t TFA_Hal_GetNextChunkLength(uint32_t maxChunkLength)
{
    struct _tfa_hal_msg *rmsg = (struct _tfa_hal_msg *)(g_TfaDeviceMessageStatus.sndBuffer);
    int32_t remaining         = rmsg->rlength + sizeof(struct _tfa_hal_msg) - g_TfaDeviceMessageStatus.totalSend;
    uint32_t chunkLength      = remaining > maxChunkLength ? maxChunkLength : remaining;

    if (chunkLength)
    {
        g_TfaDeviceMessageStatus.totalSend += chunkLength;
    }
    else
    {
        g_TfaDeviceMessageStatus.totalSend = 0; // done
    }

    // return max or the tail
    return chunkLength;
}

/*!
 * @brief I2C write read function. It's a wrapper over tfa9xxx driver I2C function.
 *
 * @param handle TFA9XXX handle structure.
 * @param slave Slave address.
 * @param wrLength Length of data to write.
 * @param wrData Data to write.
 * @param rdLength Length of data to read.
 * @param rdData Pointer to read data buffer.
 * @return int32_t It returns kStatus_Success if I2C operation finishes successfully. It returns negative value of
 * _lpi2c_status error code if I2C operation fails.
 */
int32_t TFA_I2C_WriteReadRaw(
    tfa9xxx_handle_t *handle, uint8_t slave, uint32_t wrLength, uint8_t *wrData, uint32_t rdLength, uint8_t *rdData)
{
    struct i2c_client i2cClient = {
        .addr = slave,
        .hal  = &(handle->i2cHandle),
    };
    return tfa2_i2c_write_read_raw(&i2cClient, wrLength, wrData, rdLength, rdData);
}

/*!
 * @brief I2C write only function to control TFA. It's a wrapper over TFA_I2C_WriteReadRaw().
 *
 * @param handle TFA9XXX handle structure.
 * @param slave Slave address
 * @param length Length of data to write.
 * @param data Data to write.
 * @return int32_t
 */
int32_t TFA_I2C_WriteRaw(tfa9xxx_handle_t *handle, uint8_t slave, uint32_t len, const uint8_t *data)
{
    return TFA_I2C_WriteReadRaw(handle, slave, len, (uint8_t *)data, 0, NULL);
}

/*!
 * @brief Display the data in hex with certain length.
 *
 * @param str str to print
 * @param data data to print
 * @param length data size
 */
void TFA_Hal_DumpHex(char *str, uint8_t *data, uint32_t length)
{
    int i;

    if (str == NULL)
        str = "";

    TFA9XXX_Printf("%s [%d]:", str, length);
    for (i = 0; i < length; i++)
    {
        TFA9XXX_Printf("%02x ", data[i]);
    }
    TFA9XXX_Printf("\n\r");
}

/*!
 * @brief Display the contents of the message buffer.
 *
 * @param msg Message.
 * @param rcv Received message or sent message.
 */
void TFA_Hal_DumpMsg(struct _tfa_hal_msg *msg, uint8_t rcv)
{
    /* header */
    TFA9XXX_Printf(
        "cmd(1) = %c, cmd_lsb(1) = 0x%x, seq(2) = %d, index(4) = %d, crc32(4) = 0x%x, error(2) = 0x%x, wlength(2) = "
        "%d, rlength(2) = %d",
        msg->cmd, msg->cmd_lsb, msg->seq, msg->index, msg->crc32, msg->error, msg->wlength, msg->rlength);

    /* data depends in rcv=write or sdn=read */
    if (rcv)
        TFA_Hal_DumpHex(", wdata", (uint8_t *)&msg->data, msg->wlength);
    else
        TFA_Hal_DumpHex(", rdata", (uint8_t *)&msg->data, msg->rlength);
    TFA9XXX_Printf("\n");
}

int32_t TFA_Hal_CheckMsgCRC(struct _tfa_hal_msg *msg, uint32_t msgSize)
{
    uint8_t *base;
    uint32_t size;
    uint32_t crc_in = 0;

    /* store, calculate and compare crc32 */
    crc_in     = msg->crc32;
    msg->crc32 = 0x0;
    base       = (uint8_t *)msg;
    size       = msgSize;

    if (crc_in != ~crc32_le(~0u, base, size))
        return -EINVAL; // EPROTO;

    return 0;
}

/*!
 * @brief Calculate CRC of the message and add it to the message structure.
 *
 * @param msg Message.
 * @param msgSize Message size.
 */
void TFA_Hal_AddMsgCRC(struct _tfa_hal_msg *msg, uint32_t msgSize)
{
    uint8_t *base;
    uint32_t size;

    msg->crc32 = 0x0;
    base       = (uint8_t *)msg;
    size       = msgSize;
    msg->crc32 = ~crc32_le(~0u, base, size);

    return;
}
