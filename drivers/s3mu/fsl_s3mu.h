/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __S3MU_DRIVER_H__
#define __S3MU_DRIVER_H__

#include "fsl_common.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup s3mu
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Defines S3MU driver version 2.0.1.
 *
 * Change log:
 * - Version 2.0.1
 *   - Update kStatusGroup_SNT to kStatusGroup_ELEMU
 *
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_S3MU_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

#define MU_MSG_HEADER_SIZE (1U)

#define MESSAGING_TAG_COMMAND (0x17u)
#define MESSAGING_TAG_REPLY   (0xE1u)

enum
{
    kStatus_S3MU_AgumentOutOfRange = MAKE_STATUS(kStatusGroup_ELEMU, 0x1u), /*!< S3MU status for out of range access. */
    kStatus_S3MU_InvalidArgument = MAKE_STATUS(kStatusGroup_ELEMU, 0x2u), /*!< S3MU status for invalid argument check. */
    kStatus_S3MU_RequestTimeout  = MAKE_STATUS(kStatusGroup_ELEMU, 0x3u), /*!< S3MU status for timeout. */
    kStatus_S3MU_Busy = MAKE_STATUS(kStatusGroup_ELEMU, 0x4u), /*!< S3MU status for reservation by other core. */
};

typedef struct
{
    union
    {
        uint32_t value;
        struct
        {
            uint8_t ver;
            uint8_t size;
            uint8_t command;
            uint8_t tag;
        } hdr_byte;
    };
} mu_hdr_t;

/*******************************************************************************
 * API
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Send message to MU
 *
 * This function writes messgae into MU regsters and send message to EdgeLock Enclave.
 *
 * @param base MU peripheral base address
 * @param buf buffer to store read data
 * @param wordCount size of data in words
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_SendMessage(S3MU_Type *mu, void *buf, size_t wordCount);

/*!
 * @brief Get response from MU
 *
 * This function reads response data from EdgeLock Enclave if available.
 *
 * @param base MU peripheral base address
 * @param buf buffer to store read data
 *
 * Note: number of read response word is obtained by header,
 * so user need to prepare buffer with enough space for expected response
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_GetResponse(S3MU_Type *mu, void *buf);

/*!
 * @brief Wait and Read data from MU
 *
 * This function waits limited time (ticks) and tests if data are ready to be read.
 * When data are ready, reads them into buffer, timeout otherwise.
 *
 * @param base MU peripheral base address
 * @param buf buffer to store read data
 * @param wordCount size of data in words
 * @param wait number of iterations to wait
 *
 * @return Status kStatus_Success if success, kStatus_S3MU_RequestTimeout if timeout
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_WaitForData(S3MU_Type *mu, uint32_t *buf, size_t wordCount, uint32_t wait);

/*!
 * @brief Read message from MU
 *
 * This function reads message date from EdgeLock Enclave if available.
 *
 * @param base MU peripheral base address
 * @param buf buffer to store read data
 * @param size lenght of data in words. If read_header equal MU_READ_HEADER, size is read from response header.
 * @param read_header specifies if size is obtained by response header or provided in parameter.
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t S3MU_ReadMessage(S3MU_Type *mu, uint32_t *buf, size_t *size, uint8_t read_header);

/*!
 * @brief Init MU
 *
 * This function does nothing. MU is initialized after leaving ROM.
 *
 * @param base MU peripheral base address
 */
void S3MU_Init(S3MU_Type *mu);

/*!
 * @brief Computes CRC
 *
 * This function computes CRC of input message.
 *
 * @param msg pointer to message
 * @param msg_len size of message in words
 *
 * @return CRC32 checksum value
 */
uint32_t S3MU_ComputeMsgCrc(uint32_t *msg, uint32_t msg_len);

#if defined(__cplusplus)
}
#endif

/*! @} */ /* end of group s3mu */

#endif /* __S3MU_DRIVER_H__ */
