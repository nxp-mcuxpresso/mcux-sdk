/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2019, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ili9341.h"

void FT9341_Init(ili9341_send_byte_t _writeData, ili9341_send_byte_t _writeCommand)
{
    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    _writeCommand(ILI9341_CMD_PWRA);
    _writeData(0x39);
    _writeData(0x2C);
    _writeData(0x00);
    _writeData(0x34);
    _writeData(0x02);
    _writeCommand(ILI9341_CMD_PWRB);
    _writeData(0x00);
    _writeData(0xC1);
    _writeData(0x30);
    _writeCommand(ILI9341_CMD_DTCA);
    _writeData(0x85);
    _writeData(0x00);
    _writeData(0x78);
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
    _writeData(0x23);
    _writeCommand(ILI9341_CMD_PWR2);
    _writeData(0x10);
    _writeCommand(ILI9341_CMD_VCOM1);
    _writeData(0x3E);
    _writeData(0x28);
    _writeCommand(ILI9341_CMD_VCOM2);
    _writeData(0x86);
    _writeCommand(ILI9341_CMD_MAC);
    _writeData(0x40);
    _writeCommand(ILI9341_CMD_PIXELFORMAT);
    _writeData(0x55);
    _writeCommand(ILI9341_CMD_FRC);
    _writeData(0x00);
    _writeData(0x18);
    _writeCommand(ILI9341_CMD_DFC);
    _writeData(0x08);
    _writeData(0x82);
    _writeData(0x27);
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
    _writeData(0x0F);
    _writeData(0x31);
    _writeData(0x2B);
    _writeData(0x0C);
    _writeData(0x0E);
    _writeData(0x08);
    _writeData(0x4E);
    _writeData(0xF1);
    _writeData(0x37);
    _writeData(0x07);
    _writeData(0x10);
    _writeData(0x03);
    _writeData(0x0E);
    _writeData(0x09);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_NGAMMA);
    _writeData(0x00);
    _writeData(0x0E);
    _writeData(0x14);
    _writeData(0x03);
    _writeData(0x11);
    _writeData(0x07);
    _writeData(0x31);
    _writeData(0xC1);
    _writeData(0x48);
    _writeData(0x08);
    _writeData(0x0F);
    _writeData(0x0C);
    _writeData(0x31);
    _writeData(0x36);
    _writeData(0x0F);
    _writeCommand(ILI9341_CMD_SLEEPOUT);
    _writeCommand(ILI9341_CMD_DISPLAYON);
}

void FT9341_Init1(ili9341_send_cmd_data_t sendCmdData)
{
    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    sendCmdData(ILI9341_CMD_PWRA, (const uint8_t[]){0x39U, 0x2CU, 0x00U, 0x34U, 0x02U}, 5u);
    sendCmdData(ILI9341_CMD_PWRB, (const uint8_t[]){0x00U, 0xc1U, 0x30U}, 3u);
    sendCmdData(ILI9341_CMD_DTCA, (const uint8_t[]){0x85U, 0x00U, 0x78U}, 3u);
    sendCmdData(ILI9341_CMD_DTCB, (const uint8_t[]){0x00U, 0x00U}, 2u);
    sendCmdData(ILI9341_CMD_PWRSEQ, (const uint8_t[]){0x64U, 0x03U, 0x12U, 0x81U}, 4u);
    sendCmdData(ILI9341_CMD_PRC, (const uint8_t[]){0x20U}, 1u);
    sendCmdData(ILI9341_CMD_PWR1, (const uint8_t[]){0x23U}, 1u);
    sendCmdData(ILI9341_CMD_PWR2, (const uint8_t[]){0x10U}, 1u);
    sendCmdData(ILI9341_CMD_VCOM1, (const uint8_t[]){0x3EU, 0x28U}, 2u);
    sendCmdData(ILI9341_CMD_VCOM2, (const uint8_t[]){0x86U}, 1u);
    sendCmdData(ILI9341_CMD_MAC, (const uint8_t[]){0x40U}, 1u);
    sendCmdData(ILI9341_CMD_PIXELFORMAT, (const uint8_t[]){0x55U}, 1u);
    sendCmdData(ILI9341_CMD_FRC, (const uint8_t[]){0x00U, 0x18U}, 2u);
    sendCmdData(ILI9341_CMD_DFC, (const uint8_t[]){0x08U, 0x82U, 0x27U}, 3u);
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
