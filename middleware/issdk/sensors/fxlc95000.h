/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FXLC95000_H_
#define FXLC95000_H_

/*! @brief Size of fixed header bytes in sensor commands. */
#define FXLC95000_HDR_SIZE 4

/*! @brief Time stamp and XYZ Data Register Offset. */
#define FXLC95000_SAMPLE_OFFSET 16

/*! @brief Offset of 2-Byte ISF1.1_95k_Build_ID in Device Info Response. */
#define FXLC95000_BUILD_ID_OFFSET 12

/*! @brief The FXLC95000 Size of ISF1.1_95k_Build_ID. */
#define FXLC95000_BUILD_ID_SIZE 2

/*! @brief The FXLC95000 BCD encoded ISF1.1_95k_Build_ID. */
#define FXLC95000_BUILD_ID 0x36C2

/*! @brief The FXLC95000 Reserved filed bytes. */
#define FXLC95000_RESERVED_ID 0xFFFF

/*! @brief Offset of 2-Byte SA95000 Part Number in Device Info Response. */
#define FXLC95000_PART_NUMBER_OFFSET 14

/*! @brief The FXLC95000 Size of Part Number. */
#define FXLC95000_PART_NUMBER_SIZE 2

/*! @brief The FXLC95000 2-byte packed BCD encoded Part Number (BCD for Last 4 characters). */
#define FXLC95000_PART_NUMBER 0x5000

/*! @brief The FXLC95000 I2C Slave Address */
#define FXLC95000_I2C_ADDRESS 0x4C

/*! @brief The FXLC95000 Set Report Rate Command Header Bytes */
#define FXLC95000_SET_ODR_CMD_HDR 0x02, 0x02, 0x03, 0x04

/*! @brief The FXLC95000 Set Resolution Command Header Bytes */
#define FXLC95000_SET_RESOLUTION_CMD_HDR 0x02, 0x02, 0x07, 0x01

/*! @brief The FXLC95000 Set Range Command Header Bytes */
#define FXLC95000_SET_RANGE_CMD_HDR 0x02, 0x02, 0x08, 0x01

/*! @brief The FXLC95000 Set Report Rate Payload Bytes */
#define FXLC95000_SST_ODR_PAYLOAD(x) (x & 0xFF000000) >> 24, (x & 0xFF0000) >> 16, (x & 0xFF00) >> 8, (x & 0xFF)

/*! @brief The FXLC95000 FS Range 2G */
#define FXLC95000_ACCEL_RANGE_2G 0x40

/*! @brief The FXLC95000 FS Range 4G */
#define FXLC95000_ACCEL_RANGE_4G 0x80

/*! @brief The FXLC95000 FS Range 8G */
#define FXLC95000_ACCEL_RANGE_8G 0xC0

/*! @brief The FXLC95000 Resoultion 10-Bit */
#define FXLC95000_ACCEL_RESOLUTION_10_BIT 0x0C

/*! @brief The FXLC95000 Resoultion 12-Bit */
#define FXLC95000_ACCEL_RESOLUTION_12_BIT 0x08

/*! @brief The FXLC95000 Resoultion 14-Bit */
#define FXLC95000_ACCEL_RESOLUTION_14_BIT 0x04

/*! @brief The FXLC95000 Resoultion 16-Bit */
#define FXLC95000_ACCEL_RESOLUTION_16_BIT 0x00

static const uint8_t BootToFlash[] = {0x29, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t GetDeviceInfoCmd[] = {0x00, 0x00};
static const uint8_t ConfigureMBoxCmd[] = {0x01, 0x02, 0x18, 0x14, 0x02, 0x03, 0x02, 0x02, 0x02, 0x01, 0x02, 0x00,
                                           0x02, 0x05, 0x02, 0x04, 0x02, 0x07, 0x02, 0x06, 0x02, 0x09, 0x02, 0x08};
static const uint8_t QuickReadInterruptEnable[] = {0x01, 0x02, 0x38, 0x01, 0x01};
static const uint8_t QuickReadInterruptDisable[] = {0x01, 0x02, 0x38, 0x01, 0x00};
static const uint8_t StartDataCmd[] = {0x02, 0x02, 0x00, 0x01, 0x52};
static const uint8_t StopDataCmd[] = {0x02, 0x02, 0x00, 0x01, 0x51};
static const uint8_t ShutdownCmd[] = {0x02, 0x02, 0x00, 0x01, 0x50};
static const uint8_t UnprotectFlash[] = {0x40, 0x00};
static const uint8_t EraseMainFlashArray[] = {0x12, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF};
static const uint8_t ProtectFlash[] = {0x38, 0x00};

#endif /* FXLC95000_H_ */ 
