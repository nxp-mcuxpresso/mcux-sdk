/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ROMAPI_OTP_H_
#define FSL_ROMAPI_OTP_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"

//!@brief OTP driver API Interface
typedef struct
{
    uint32_t version;
    void (*init)(void);
    status_t (*deinit)(void);
    status_t (*p_efuse_read)(uint32_t addr, uint32_t *data);
    status_t (*p_efuse_program)(uint32_t addr, uint32_t data);
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
 */
void otp_init(void);

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
 * @brief Read Fuse value from OTP eFuse Block
 *
 * This function read fuse data from OTP Fuse block to specified data buffer.
 *
 * @param addr Fuse address
 * @param data Buffer to hold the data read from OTP Fuse block
 *
 * @return kStatus_Success - Operation succeeded without error.
 *         kStatus_Fail - The operation failed with a generic error.
 *         kStatus_ReadOnly - Requested value cannot be changed because it is read-only.
 *         kStatus_OutOfRange - Requested value is out of range.
 *         kStatus_InvalidArgument - The requested command's argument is undefined.
 *         kStatus_Timeout - A timeout occurred.
 */
status_t otp_fuse_read(uint32_t addr, uint32_t *data);

/*
 * @brief Program value to OTP eFuse block
 *
 * This function program data to specified OTP Fuse address.
 *
 * @return kStatus_Success - Operation succeeded without error.
 *         kStatus_Fail - The operation failed with a generic error.
 *         kStatus_ReadOnly - Requested value cannot be changed because it is read-only.
 *         kStatus_OutOfRange - Requested value is out of range.
 *         kStatus_InvalidArgument - The requested command's argument is undefined.
 *         kStatus_Timeout - A timeout occurred.
 */
status_t otp_fuse_program(uint32_t addr, uint32_t data);

/*
 * @brief Return OTP controller version
 *
 * @return Version of the OCOTP controller
 */
uint32_t otp_version(void);
#endif /* FSL_ROMAPI_OTP_H_ */
