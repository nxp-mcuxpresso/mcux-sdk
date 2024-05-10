/*
 * Copyright 2018-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "evkmimxrt1180_flexspi_nor_config.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xip_board"
#endif

/* clang-format off */
#if defined(XIP_EXTERNAL_FLASH) && (XIP_BOOT_HEADER_ENABLE == 1) && \
    defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
/* clang-format on */

#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.container"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.container"
#endif

/* clang-format off */
const container container_data = 
{
    {
        CNT_VERSION,
        CNT_SIZE,
        CNT_TAG_HEADER,
        CNT_FLAGS,
        CNT_SW_VER,
        CNT_FUSE_VER,
        CNT_NUM_IMG,
        sizeof(cnt_hdr) + CNT_NUM_IMG * sizeof(image_entry),
        0
    },
    {{
        IMAGE_OFFSET,
        IMAGE_SIZE,
        IMAGE_LOAD_ADDRESS,
        0x00000000,
        IMAGE_ENTRY_ADDRESS,
        0x00000000,
        IMG_FLAGS,
        0x0,
        {0},
        {0}
    }},
    {
        SGNBK_VERSION,
        SGNBK_SIZE,
        SGNBK_TAG,
        0x0,
        0x0,
        0x0,
        0x0
    }
};
/* clang-format on */

#if defined(USE_HYPERRAM)

#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.xmcd_data"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.xmcd_data"
#endif

const uint32_t xmcd_data[] = {
    0xC002000C, /* FlexSPI instance 2 */
    0xC1000800, /* Option words = 2 */
    0x00010000  /* PINMUX Secondary group */
};

#endif

#if defined(USE_SDRAM)

#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.xmcd_data"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.xmcd_data"
#endif

const uint32_t xmcd_data[] = {
    0xC010000D, /* SEMC -> SDRAM */
    0xA60001A1, /* SDRAM config */
    0x00008000, /* SDRAM config */
    0X00000001  /* SDRAM config */
};

#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.conf"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.conf"
#endif

/*
 * FlexSPI nor flash configuration block
 * Note:
 *    Below setting is special for EVK board flash, to achieve maximum access performance.
 *    For other boards or flash, may leave it 0 or delete fdcb_data, which means auto probe.
 */

/* clang-format off */
const uint32_t fdcb_data[] = {
    0x42464346, 0x56010400, 0x00000000, 0x00030301, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000010, 0x00070401, 0x00000000, 0x00000000, 0x01000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0a1804eb, 0x26043206, 0x00000000, 0x00000000, 0x24040405, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000406, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08180420, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x081804d8, 0x00000000, 0x00000000, 0x00000000, 0x08180402, 0x00002004, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000460, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000100, 0x00001000, 0x00000001, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};
/* clang-format on */

#endif
