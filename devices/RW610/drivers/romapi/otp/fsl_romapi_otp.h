/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ROMAPI_OTP_H_
#define _FSL_ROMAPI_OTP_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"

//!@brief OTP driver API Interface
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t src_clk_freq);
    status_t (*deinit)(void);
    status_t (*fuse_read)(uint32_t addr, uint32_t *data, uint32_t argChk);
    status_t (*fuse_program)(uint32_t addr, uint32_t data, bool lock);
    status_t (*reload)(void);
    status_t (*crc_check)(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr);
    status_t (*crc_calc)(uint32_t *src, uint32_t numberOfWords, uint32_t *crcChecksum);
    status_t (*crc_check_sw)(uint32_t *src, uint32_t numberOfWords, uint32_t crc_fuse_idx);
} ocotp_driver_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * @brief Initialize OTP controller
 *
 * This function enables OTP Controller clock.
 *
 * @param src_clk_freq The Frequency of the source clock of OTP controller
 *
 * @return
 *      kStatus_Success
 */
status_t otp_init(uint32_t src_clk_freq);

/*
 * @brief De-Initialize OTP controller
 *
 * This functin disables OTP Controller Clock.
 *
 * @return
 *      kStatus_Success
 */
status_t otp_deinit(void);

/*
 * @brief Read Fuse value from OTP Fuse Block
 *
 * This function read fuse data from OTP Fuse block to specified data buffer.
 *
 * @param addr Fuse address
 * @param data Buffer to hold the data read from OTP Fuse block
 *
 * @return kStatus_Success - Data read from OTP Fuse block successfully
 *         kStatus_InvalidArgument - data pointer is invalid
 *         kStatus_OTP_EccCheckFail - Ecc Check Failed
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_fuse_read(uint32_t addr, uint32_t *data);

/*
 * @brief Program value to OTP Fuse block
 *
 * This function program data to specified OTP Fuse address.
 *
 * @param addr Fuse address
 * @param data data to be programmed into OTP Fuse block
 * @param lock lock the fuse field or not
 * @return kStatus_Success - Data has been programmed into OTP Fuse block successfully
 *         kStatus_OTP_ProgramFail - Fuse programming failed
 *         kStatus_OTP_Locked - The address to be programmed into is locked
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_fuse_program(uint32_t addr, uint32_t data);

/*
 * @brief Reload all shadow registers from OTP fuse block
 *
 * This function reloads all the shadow registers from OTP Fuse block
 *
 * @return kStatus_Success - Shadow registers' reloadding succeeded.
 *         kStatus_OTP_EccCheckFail - Ecc Check Failed
 *         kStatus_OTP_Error - Other Errors
 */
status_t otp_shadow_register_reload(void);

/*
 * @brief Do CRC Check via OTP controller
 *
 * This function checks whether data in specified fuse address ranges match the crc value in the specified CRC address
 *  and return the actual crc value as needed.
 *
 * @param start_addr Start address of selected Fuse address range
 * @param end_addr   End address of selected Fuse address range
 * @param crc_addr   Address that hold CRC data
 *
 * @return kStatus_Success CRC check succeeded, CRC value matched.
 *         kStatus_InvalidArgument - Invalid Argument
 *         kStatus_OTP_EccCheckFail Ecc Check Failed
 *         kStatus_OTP_CrcFail CRC Check Failed
 */
status_t otp_crc_check(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr);

/*
 * @brief Calculate the CRC checksum for specified data for OTP
 *
 * This function calculates the CRC checksum for specified data for OTP
 *
 * @param src the source address of data
 * @param numberOfWords number of Fuse words
 * @param crcChecksum   Buffer to store the CRC checksum
 *
 * @return kStatus_Success CRC checksum is computed successfully.
 *         kStatus_InvalidArgument - Invalid Argument
 */
status_t otp_crc_calc(uint32_t *src, uint32_t numberOfWords, uint32_t *crcChecksum);

/*
 * @brief Perform CRC Check via SW CRC controller
 *
 * This function checks whether CRC over given data match the crc value in the specified CRC address
 *  and return the status.
 *
 * @param src the source address of data
 * @param numberOfWords number of Fuse words
 * @param crc_fuse_idx  Fuseword index that hold CRC data
 *
 * @return kStatus_Success CRC checksum is computed successfully.
 *         kStatus_OTP_CrcFail - CRC Check Failed
 *         kStatus_InvalidArgument - Invalid Argument
 *         kStatus_OTP_Error - OTP read error
 */
status_t otp_crc_check_sw(uint32_t *src, uint32_t numberOfWords, uint32_t crc_fuse_idx);

/*
 * @brief Return OTP controller version
 *
 * @return Version of the OCOTP controller
 */
uint32_t otp_version(void);
#endif /* _FSL_ROMAPI_OTP_H_ */
