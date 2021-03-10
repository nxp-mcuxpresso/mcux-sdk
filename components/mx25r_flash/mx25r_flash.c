/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mx25r_flash.h"

#define MX25R_BYTE_ADDR1(address) ((address >> 16) & 0xf)
#define MX25R_BYTE_ADDR2(address) ((address >> 8) & 0xf)
#define MX25R_BYTE_ADDR3(address) (address & 0xf)

/* initialize 'mx25r_instance' */
mx25r_err_t mx25r_init(struct mx25r_instance *instance, transfer_cb_t callback, void *callback_prv)
{
    instance->callback = callback;
    instance->prv      = callback_prv;
    return mx25r_err_ok;
}

/* read 'rdid' to 'result' */
mx25r_err_t mx25r_cmd_rdid(struct mx25r_instance *instance, struct mx25r_rdid_result *result)
{
    instance->cmd[0] = 0x9f;
    instance->callback(instance->prv, instance->cmd, NULL, 1, false);
    instance->callback(instance->prv, NULL, (uint8_t *)result, sizeof(*result), true);
    return mx25r_err_ok;
}

/* read n bytes starting at 'address' */
mx25r_err_t mx25r_cmd_read(struct mx25r_instance *instance, uint32_t address, uint8_t *buffer, uint32_t size)
{
    if (address & 0xFF000000U)
    {
        return mx25r_err_out_of_range;
    }
    instance->cmd[0] = 0x03;
    instance->cmd[1] = MX25R_BYTE_ADDR1(address);
    instance->cmd[2] = MX25R_BYTE_ADDR2(address);
    instance->cmd[3] = MX25R_BYTE_ADDR3(address);
    instance->callback(instance->prv, instance->cmd, NULL, 4, false);
    instance->callback(instance->prv, NULL, (uint8_t *)buffer, size, true);
    return mx25r_err_ok;
}

/* no operation */
mx25r_err_t mx25r_cmd_nop(struct mx25r_instance *instance)
{
    instance->callback(instance->prv, instance->cmd, NULL, 1, true);
    return mx25r_err_ok;
}

/* read status register */
mx25r_err_t mx25r_cmd_rdsr(struct mx25r_instance *instance, struct mx25r_rdsr_result *result)
{
    instance->cmd[0] = 0x05;
    instance->callback(instance->prv, instance->cmd, NULL, 1, false);
    instance->callback(instance->prv, NULL, (uint8_t *)result, sizeof(*result), true);
    return mx25r_err_ok;
}

/* disable write operations */
mx25r_err_t mx25r_cmd_wrdi(struct mx25r_instance *instance)
{
    instance->cmd[0] = 0x04;
    instance->callback(instance->prv, instance->cmd, NULL, 1, true);
    return mx25r_err_ok;
}

/* enable write operations */
mx25r_err_t mx25r_cmd_wren(struct mx25r_instance *instance)
{
    instance->cmd[0] = 0x06;
    instance->callback(instance->prv, instance->cmd, NULL, 1, true);
    return mx25r_err_ok;
}

/* write n bytes (256 max) starting at 'address' aligned to 256 */
mx25r_err_t mx25r_cmd_write(struct mx25r_instance *instance,
                            uint32_t address_256_align,
                            uint8_t *buffer,
                            uint32_t size_256_max)
{
    struct mx25r_rdsr_result result;
    if (address_256_align & 0xFF000000U)
    {
        return mx25r_err_out_of_range;
    }
    if (address_256_align & 0xFFU)
    {
        return mx25r_err_alignement;
    }
    if (size_256_max > 256)
    {
        return mx25r_err_out_of_range;
    }
    /* enable write and wait until WEL is 1 */
    mx25r_cmd_wren(instance);
    do
    {
        mx25r_cmd_rdsr(instance, &result);
    } while (!(result.sr0 & 0x2));
    /* write sequence */
    instance->cmd[0] = 0x02;
    instance->cmd[1] = MX25R_BYTE_ADDR1(address_256_align);
    instance->cmd[2] = MX25R_BYTE_ADDR2(address_256_align);
    instance->cmd[3] = 0;
    instance->callback(instance->prv, instance->cmd, NULL, 4, false);
    instance->callback(instance->prv, (uint8_t *)buffer, NULL, size_256_max, true);
    /* wait until WRI is 0 and WEL is 0 */
    do
    {
        mx25r_cmd_rdsr(instance, &result);
    } while (result.sr0 & 0x3);
    return mx25r_err_ok;
}

/* erase sector at 'address' aligned to sector size = 4kB */
mx25r_err_t mx25r_cmd_sector_erase(struct mx25r_instance *instance, uint32_t address)
{
    struct mx25r_rdsr_result result;
    /* enable write and wait until WEL is 1 */
    mx25r_cmd_wren(instance);
    do
    {
        mx25r_cmd_rdsr(instance, &result);
    } while (!(result.sr0 & 0x2));
    /* write sequence */
    instance->cmd[0] = 0x20;
    instance->cmd[1] = MX25R_BYTE_ADDR1(address);
    instance->cmd[2] = MX25R_BYTE_ADDR2(address);
    instance->cmd[3] = MX25R_BYTE_ADDR3(address);
    instance->callback(instance->prv, instance->cmd, NULL, 4, true);
    /* wait until WRI is 0 and WEL is 0 */
    do
    {
        mx25r_cmd_rdsr(instance, &result);
    } while (result.sr0 & 0x3);
    return mx25r_err_ok;
}
