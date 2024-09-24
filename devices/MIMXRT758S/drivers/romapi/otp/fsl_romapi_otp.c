/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_otp.h"
#include "fsl_romapi.h"

#define OCOTP_API_TREE ((ocotp_driver_t *)(((uint32_t *)ROM_API_TREE_ADDR)[12]))

/*!
 * @brief Initialize OCOTP controller
 */
uint32_t otp_version(void)
{
    return (OCOTP_API_TREE->version);
}

/*!
 * @brief Initialize OCOTP controller
 */
void otp_init(void)
{
    assert(OCOTP_API_TREE);
    OCOTP_API_TREE->init();
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
 * @brief Reads a efuse word
 */
status_t otp_fuse_read(uint32_t addr, uint32_t *data)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->p_efuse_read(addr, data);
}

/*!
 * @brief Programs a efuse word
 */
status_t otp_fuse_program(uint32_t addr, uint32_t data)
{
    assert(OCOTP_API_TREE);
    return OCOTP_API_TREE->p_efuse_program(addr, data);
}
