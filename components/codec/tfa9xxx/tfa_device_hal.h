/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TFA_DEVICE_HAL_H_
#define TFA_DEVICE_HAL_H_

#include "stdint.h"
#include "stdio.h"
#include "fsl_tfa9xxx.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
// #define TFA_HAL_DEBUG
#define TFA_BUFFERSIZE (4 * 1024)

enum _tfa_hal_msg_cmd
{
    TFA_HAL_MSG_VERSION  = 'V', /** < version command > */
    TFA_HAL_MSG_RESET    = 'R', /** < reset command > */
    TFA_HAL_MSG_I2C      = 'I', /** < I2C write  read command > */
    TFA_HAL_MSG_DSP      = 'D', /** < RPC write  read command > */
    TFA_HAL_MSG_PIN      = 'P', /** < PIN write  read command > */
    TFA_HAL_MSG_PLAYBACK = 'S', /** < playback start stop command > */
};

#pragma pack(push, 1)
struct _tfa_hal_msg
{
    uint8_t cmd;     /** < command msb byte */
    uint8_t cmd_lsb; /** < command lsb byte */
    int16_t seq;     /** < sequence number  */
    int32_t index;   /** < remote address or  index */
    int32_t crc32;   /** < payload crc */
    int16_t error;   /** < error code returned */
    int16_t wlength; /** < write length */
    int16_t rlength; /** < read length */
    uint8_t data[];  /** < data payload */
};
#pragma pack(pop)

typedef struct _tfa_hal_msg_status
{
    uint8_t sndBuffer[TFA_BUFFERSIZE];
    uint8_t msgComplete;
    uint32_t totalSend;
} tfa_hal_msg_status_t;

/*******************************************************************************
 * API
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
uint8_t TFA_Hal_CollectMsg(tfa9xxx_handle_t *handle, uint8_t *chunk, uint32_t length);

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
int32_t TFA_Hal_ProcessMsg(tfa9xxx_handle_t *handle, void *inBuffer, void *outBuffer);

/*!
 * @brief Get the length of the next message chunk for the device to sent. If the length is 0, it means the whole
 * message has been sent.
 *
 * @param maxChunkLength Max length to be sent.
 * @return uint32_t The length of next message chunk to be sent.
 */
uint32_t TFA_Hal_GetNextChunkLength(uint32_t maxChunkLength);

/*!
 * @brief Check the CRC of the returned message.
 *
 * @param msg Message.
 * @param msgSize Message size
 * @retval 0 if CRC matches otherwise -EINVAL.
 * @retval EINVAL if CRC does not match.
 */
int32_t TFA_Hal_CheckMsgCRC(struct _tfa_hal_msg *msg, uint32_t msgSize);

/*!
 * @brief Calculate CRC of the message and add it to the message structure.
 *
 * @param msg Message.
 * @param msgSize Message size.
 */
void TFA_Hal_AddMsgCRC(struct _tfa_hal_msg *msg, uint32_t msgSize);

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
    tfa9xxx_handle_t *handle, uint8_t slave, uint32_t wrLength, uint8_t *wrData, uint32_t rdLength, uint8_t *rdData);

/*!
 * @brief I2C write only function to control TFA. It's a wrapper over TFA_I2C_WriteReadRaw().
 *
 * @param handle TFA9XXX handle structure.
 * @param slave Slave address
 * @param len Length of data to write.
 * @param data Data to write.
 * @return int32_t
 */
int32_t TFA_I2C_WriteRaw(tfa9xxx_handle_t *handle, uint8_t slave, uint32_t len, const uint8_t *data);

/*!
 * @brief Display the contents of the message buffer.
 *
 * @param msg Message.
 * @param rcv Received message or sent message.
 */
void TFA_Hal_DumpMsg(struct _tfa_hal_msg *msg, uint8_t rcv);

/*!
 * @brief Display the data in hex with certain length.
 *
 * @param str str to print
 * @param data data to print
 * @param length data size
 */
void TFA_Hal_DumpHex(char *str, uint8_t *data, uint32_t length);

#endif /* TFA_DEVICE_HAL_H_ */
