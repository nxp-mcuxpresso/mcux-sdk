/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2019,2022,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ili9341.h"

void FT9341_Init(ili9341_send_byte_t _writeData, ili9341_send_byte_t _writeCommand)
{
    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    _writeCommand(ILI9341_CMD_DISPLAYOFF);

    _writeCommand(ILI9341_CMD_PWRA);
    _writeData(0x39);
    _writeData(0x2C);
    _writeData(0x00);
    _writeData(0x34);
    _writeData(0x02);
    _writeCommand(ILI9341_CMD_PWRB);
    _writeData(0x00);
    _writeData(0x83);
    _writeData(0x30);
    _writeCommand(ILI9341_CMD_DTCA);
    _writeData(0x85);
    _writeData(0x01);
    _writeData(0x79);
    _writeCommand(ILI9341_CMD_DTCB);
    _writeData(0x00);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_PWRSEQ);
    _writeData(0x64);
    _writeData(0x03);
    _writeData(0x12);
    _writeData(0x81);
    _writeCommand(ILI9341_CMD_PRC);
    _writeData(0x20);
    _writeCommand(ILI9341_CMD_PWR1);
    _writeData(0x26);
    _writeCommand(ILI9341_CMD_PWR2);
    _writeData(0x11);
    _writeCommand(ILI9341_CMD_VCOM1);
    _writeData(0x35);
    _writeData(0x3E);
    _writeCommand(ILI9341_CMD_VCOM2);
    _writeData(0xBE);
    _writeCommand(ILI9341_CMD_MAC);
    _writeData(0x28);
    _writeCommand(ILI9341_CMD_PIXELFORMAT);
    _writeData(0x55);
    _writeCommand(ILI9341_CMD_FRC);
    _writeData(0x00);
    _writeData(0x1F);
    _writeCommand(ILI9341_CMD_DFC);
    _writeData(0x0A);
    _writeData(0x82);
    _writeData(0x27);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_3GAMMAEN);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_COLADDR);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0xEF);
    _writeCommand(ILI9341_CMD_PAGEADDR);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0x01);
    _writeData(0x3F);
    _writeCommand(ILI9341_CMD_GAMMA);
    _writeData(0x01);
    _writeCommand(ILI9341_CMD_PGAMMA);
    _writeData(0x0FU);
    _writeData(0x31U);
    _writeData(0x2BU);
    _writeData(0x0CU);
    _writeData(0x0EU);
    _writeData(0x08U);
    _writeData(0x4EU);
    _writeData(0xF1U);
    _writeData(0x37U);
    _writeData(0x07U);
    _writeData(0x10U);
    _writeData(0x03U);
    _writeData(0x0EU);
    _writeData(0x09U);
    _writeData(0x00U);
    _writeCommand(ILI9341_CMD_NGAMMA);
    _writeData(0x00U);
    _writeData(0x0EU);
    _writeData(0x14U);
    _writeData(0x03U);
    _writeData(0x11U);
    _writeData(0x07U);
    _writeData(0x31U);
    _writeData(0xC1U);
    _writeData(0x48U);
    _writeData(0x08U);
    _writeData(0x0FU);
    _writeData(0x0CU);
    _writeData(0x31U);
    _writeData(0x36U);
    _writeData(0x0FU);
    _writeCommand(ILI9341_CMD_SLEEPOUT);
    _writeCommand(ILI9341_CMD_DISPLAYON);
}

void FT9341_Init1(ili9341_send_cmd_data_t sendCmdData)
{
    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    sendCmdData(ILI9341_CMD_DISPLAYOFF, NULL, 0U);
    sendCmdData(ILI9341_CMD_PWRA, (const uint8_t[]){0x39U, 0x2CU, 0x00U, 0x34U, 0x02U}, 5u);
    sendCmdData(ILI9341_CMD_PWRB, (const uint8_t[]){0x00U, 0x83U, 0x30U}, 3u);
    sendCmdData(ILI9341_CMD_DTCA, (const uint8_t[]){0x85U, 0x01U, 0x79U}, 3u);
    sendCmdData(ILI9341_CMD_DTCB, (const uint8_t[]){0x00U, 0x00U}, 2u);
    sendCmdData(ILI9341_CMD_PWRSEQ, (const uint8_t[]){0x64U, 0x03U, 0x12U, 0x81U}, 4u);
    sendCmdData(ILI9341_CMD_PRC, (const uint8_t[]){0x20U}, 1u);
    sendCmdData(ILI9341_CMD_PWR1, (const uint8_t[]){0x26U}, 1u);
    sendCmdData(ILI9341_CMD_PWR2, (const uint8_t[]){0x11U}, 1u);
    sendCmdData(ILI9341_CMD_VCOM1, (const uint8_t[]){0x35U, 0x3eU}, 2u);
    sendCmdData(ILI9341_CMD_VCOM2, (const uint8_t[]){0xBEU}, 1u);
    sendCmdData(ILI9341_CMD_MAC, (const uint8_t[]){0x28U}, 1u);
    sendCmdData(ILI9341_CMD_PIXELFORMAT, (const uint8_t[]){0x55U}, 1u);
    sendCmdData(ILI9341_CMD_FRC, (const uint8_t[]){0x00U, 0x1FU}, 2u);
    sendCmdData(ILI9341_CMD_DFC, (const uint8_t[]){0x0aU, 0x82U, 0x27U, 0x00}, 4u);
    sendCmdData(ILI9341_CMD_3GAMMAEN, (const uint8_t[]){0x00U}, 1u);
    sendCmdData(ILI9341_CMD_COLADDR, (const uint8_t[]){0x00U, 0x00U, 0x00U, 0xEFU}, 4u);
    sendCmdData(ILI9341_CMD_PAGEADDR, (const uint8_t[]){0x00U, 0x00U, 0x01U, 0x3FU}, 4u);
    sendCmdData(ILI9341_CMD_GAMMA, (const uint8_t[]){0x01U}, 1u);
    sendCmdData(ILI9341_CMD_PGAMMA,
                (const uint8_t[]){0x0FU, 0x31U, 0x2BU, 0x0CU, 0x0EU, 0x08U, 0x4EU, 0xF1U, 0x37U, 0x07U, 0x10U, 0x03U,
                                  0x0EU, 0x09U, 0x00U},
                15u);
    sendCmdData(ILI9341_CMD_NGAMMA,
                (const uint8_t[]){0x00U, 0x0EU, 0x14U, 0x03U, 0x11U, 0x07U, 0x31U, 0xC1U, 0x48U, 0x08U, 0x0FU, 0x0CU,
                                  0x31U, 0x36U, 0x0FU},
                15u);

    sendCmdData(ILI9341_CMD_SLEEPOUT, NULL, 0U);
    sendCmdData(ILI9341_CMD_DISPLAYON, NULL, 0U);
}

#if ILI9341_USE_DBI_IFACE
status_t ILI9341_InitDBI(ili9341_handle_t *handle, const ili9341_config_t *config, dbi_iface_t *dbiIface)
{
    handle->dbiIface = dbiIface;

    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_DISPLAYOFF, NULL, 0U);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PWRA, (const uint8_t[]){0x39U, 0x2CU, 0x00U, 0x34U, 0x02U}, 5u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PWRB, (const uint8_t[]){0x00U, 0x83U, 0x30U}, 3u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_DTCA, (const uint8_t[]){0x85U, 0x01U, 0x79U}, 3u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_DTCB, (const uint8_t[]){0x00U, 0x00U}, 2u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PWRSEQ, (const uint8_t[]){0x64U, 0x03U, 0x12U, 0x81U}, 4u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PRC, (const uint8_t[]){0x20U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PWR1, (const uint8_t[]){0x26U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PWR2, (const uint8_t[]){0x11U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_VCOM1, (const uint8_t[]){0x35U, 0x3eU}, 2u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_VCOM2, (const uint8_t[]){0xBEU}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_MAC, (const uint8_t[]){0x28U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PIXELFORMAT, (const uint8_t[]){0x55U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_FRC, (const uint8_t[]){0x00U, 0x1FU}, 2u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_DFC, (const uint8_t[]){0x0aU, 0x82U, 0x27U, 0x00}, 4u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_3GAMMAEN, (const uint8_t[]){0x00U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_COLADDR, (const uint8_t[]){0x00U, 0x00U, 0x00U, 0xEFU}, 4u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PAGEADDR, (const uint8_t[]){0x00U, 0x00U, 0x01U, 0x3FU}, 4u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_GAMMA, (const uint8_t[]){0x01U}, 1u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_PGAMMA,
                           (const uint8_t[]){0x0FU, 0x31U, 0x2BU, 0x0CU, 0x0EU, 0x08U, 0x4EU, 0xF1U, 0x37U, 0x07U,
                                             0x10U, 0x03U, 0x0EU, 0x09U, 0x00U},
                           15u);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_NGAMMA,
                           (const uint8_t[]){0x00U, 0x0EU, 0x14U, 0x03U, 0x11U, 0x07U, 0x31U, 0xC1U, 0x48U, 0x08U,
                                             0x0FU, 0x0CU, 0x31U, 0x36U, 0x0FU},
                           15u);

    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_SLEEPOUT, NULL, 0U);
    DBI_IFACE_WriteCmdData(dbiIface, ILI9341_CMD_DISPLAYON, NULL, 0U);

    return kStatus_Success;
}

#endif
