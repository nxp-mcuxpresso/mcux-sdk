/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDXLicense-Identifier: BSD-3-Clause
 */
#include "flash_config.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flash_config"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(BOOT_HEADER_ENABLE) && (BOOT_HEADER_ENABLE == 1)
#if defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".flash_conf"), used))
#elif defined(__ICCARM__)
#pragma location = ".flash_conf"
#endif

const fc_static_platform_config_t flash_config = {
    .xspi_fcb_block = {
        .memConfig =
        {
            .tag                 = FC_XSPI_CFG_BLK_TAG,
            .version             = FC_XSPI_CFG_BLK_VERSION,
            .readSampleClkSrc    = kXSPIReadSampleClk_ExternalInputFromDqsPad,
            .csHoldTime          = 3,
            .csSetupTime         = 3,
            .deviceModeCfgEnable = 1,
            .deviceModeType      = 2,
            .waitTimeCfgCommands = 1,
            .deviceModeSeq =
                {
                    .seqNum   = 1,
                    .seqId    = 6, /* See Lookup table for more details */
                    .reserved = 0,
                },
            .deviceModeArg = 2, /* Enable OPI DDR mode */
            .controllerMiscOption =
                (1u << Fc_XspiMiscOffset_SafeConfigFreqEnable) | (1u << Fc_XspiMiscOffset_DdrModeEnable),
            .deviceType      = 1,
            .sflashPadType   = 8,
            .serialClkFreq   = Fc_XspiSerialClk_200MHz,
            .sflashA1Size    = 64ul * 1024u * 1024u,
            .busyOffset      = 0u,
            .busyBitPolarity = 0u,
            .lookupTable =
            {
                /*Read*/
                [0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0xEE, FC_CMD_DDR, FC_XSPI_8PAD, 0x11),
                [1] =
                    FC_XSPI_LUT_SEQ(FC_CMD_RADDR_DDR, FC_XSPI_8PAD, 0x20, FC_CMD_DUMMY_SDR, FC_XSPI_8PAD, 0x12),
                [2] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DUMMY_SDR, FC_XSPI_8PAD, 0x2, FC_CMD_READ_DDR, FC_XSPI_8PAD, 0x4),
                [3] =
                    FC_XSPI_LUT_SEQ(FC_CMD_STOP, FC_XSPI_8PAD, 0x0, 0, 0, 0),

                /*Read status SPI*/
                [5 * 1 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_SDR, FC_XSPI_1PAD, 0x05, FC_CMD_READ_SDR, FC_XSPI_1PAD, 0x04),

                /* Read Status OPI */
                [5 * 2 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0x05, FC_CMD_DDR, FC_XSPI_8PAD, 0xFA),
                [5 * 2 + 1] =
                    FC_XSPI_LUT_SEQ(FC_CMD_RADDR_DDR, FC_XSPI_8PAD, 0x20, FC_CMD_DUMMY_SDR, FC_XSPI_8PAD, 0x12),
                [5 * 2 + 2] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DUMMY_SDR, FC_XSPI_8PAD, 0x2, FC_CMD_READ_DDR, FC_XSPI_8PAD, 0x4),
                [5 * 2 + 3] =
                    FC_XSPI_LUT_SEQ(FC_CMD_STOP, FC_XSPI_8PAD, 0x0, 0, 0, 0),

                /*Write enable*/
                [5 * 3 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_SDR, FC_XSPI_1PAD, 0x06, FC_CMD_STOP, FC_XSPI_1PAD, 0x04),

                /* Write Enable - OPI */
                [5 * 4 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0x06, FC_CMD_DDR, FC_XSPI_8PAD, 0xF9),

                /* Erase Sector */
                [5 * 5 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0x21, FC_CMD_DDR, FC_XSPI_8PAD, 0xDE),
                [5 * 5 + 1] =
                    FC_XSPI_LUT_SEQ(FC_CMD_RADDR_DDR, FC_XSPI_8PAD, 0x20, FC_CMD_STOP, FC_XSPI_8PAD, 0x0),

                /* Enable OPI DDR mode */
                [5 * 6 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_SDR, FC_XSPI_1PAD, 0x72, FC_CMD_SDR, FC_XSPI_1PAD, 0x00),
                [5 * 6 + 1] =
                    FC_XSPI_LUT_SEQ(FC_CMD_SDR, FC_XSPI_1PAD, 0x00, FC_CMD_SDR, FC_XSPI_1PAD, 0x00),
                [5 * 6 + 2] =
                    FC_XSPI_LUT_SEQ(FC_CMD_SDR, FC_XSPI_1PAD, 0x00, FC_CMD_WRITE_SDR,  FC_XSPI_1PAD, 0x01),

                /* Page program */
                [5 * 9 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0x12, FC_CMD_DDR, FC_XSPI_8PAD, 0xED),
                [5 * 9 + 1] =
                    FC_XSPI_LUT_SEQ(FC_CMD_RADDR_DDR, FC_XSPI_8PAD, 0x20, FC_CMD_WRITE_DDR, FC_XSPI_8PAD, 0x4),

                /* Erase Chip */
                [5 * 11 + 0] =
                    FC_XSPI_LUT_SEQ(FC_CMD_DDR, FC_XSPI_8PAD, 0x60, FC_CMD_DDR, FC_XSPI_8PAD, 0x9F),
            },
        },
        .pageSize           = 256u,
        .sectorSize         = 4u * 1024u,
        .ipcmdSerialClkFreq = 1u,
        .serialNorType      = 2u,
        .blockSize          = 64u * 1024u,
        .flashStateCtx      = 0x07008200u,
    },
#ifdef BOOT_ENABLE_XSPI1_PSRAM
    .psram_config_block = {
        .xmcdHeader = 0xC0010008,
        .xmcdOpt0   = 0xC0000700,
    },
#endif
};

#endif /* BOOT_HEADER_ENABLE */
