/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_otp.h"
#include "fsl_romapi.h"

#define OCOTP_API_TREE ((ocotp_driver_t *)(((uint32_t *)ROM_API_TREE_ADDR)[6]))

/*!
 * @brief Initialize OCOTP controller
 */
uint32_t otp_version(void)
{
    return (OCOTP->OTP_VERSION);
}

/*!
 * @brief Initialize OCOTP controller
 */
status_t otp_init(uint32_t src_clk_freq)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->init(src_clk_freq);
}

/*!
 * @brief Deinitialize OCOTP controller
 */
status_t otp_deinit(void)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->deinit();
}

/*!
 * @brief Reload OTP shadow registers
 */
status_t otp_shadow_register_reload(void)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->reload();
}

/*!
 * @brief Reads a fuse word
 */
status_t otp_fuse_read(uint32_t addr, uint32_t *data)
{
    uint32_t argChk;
    assert(OCOTP_API_TREE);
    argChk = addr ^ ((uint32_t) data);
    return OCOTP_API_TREE->fuse_read(addr, data, argChk);
}

/*!
 * @brief Programs a fuse word
 */
status_t otp_fuse_program(uint32_t addr, uint32_t data)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->fuse_program(addr, data, false);
}

/*!
 * @brief Perform CRC check using HW OTP controller
 */
status_t otp_crc_check(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->crc_check(start_addr, end_addr, crc_addr);
}

/*!
 * @brief Perform CRC calculation
 */
status_t otp_crc_calc(uint32_t *src, uint32_t numberOfWords, uint32_t *crcChecksum)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->crc_calc(src, numberOfWords, crcChecksum);
}

/*!
 * @brief Perform CRC check using CRC module.
 */
status_t otp_crc_check_sw(uint32_t *src, uint32_t numberOfWords, uint32_t crc_fuse_idx)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->crc_check_sw(src, numberOfWords, crc_fuse_idx);
}
