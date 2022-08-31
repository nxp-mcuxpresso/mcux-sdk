/** @file wlan_txpwrlimit_cfg_murata_2DS_WW
 *
 *  @brief  This file provides Murata 2DS WLAN World Wide Safe Mode Tx Power Limit APIs.
 *
 *  Copyright 2008-2020 NXP
 *
 *  NXP CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Materials") are owned by NXP, its
 *  suppliers and/or its licensors. Title to the Materials remains with NXP,
 *  its suppliers and/or its licensors. The Materials contain
 *  trade secrets and proprietary and confidential information of NXP, its
 *  suppliers and/or its licensors. The Materials are protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Materials may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without NXP's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by NXP in writing.
 *
 */

static wlan_chanlist_t chanlist_2g_cfg = {
    .num_chans = 14,
    .chan_info[0] =
        {
            .chan_num                     = 1,
            .chan_freq                    = 2412,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[1] =
        {
            .chan_num                     = 2,
            .chan_freq                    = 2417,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[2] =
        {
            .chan_num                     = 3,
            .chan_freq                    = 2422,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[3] =
        {
            .chan_num                     = 4,
            .chan_freq                    = 2427,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[4] =
        {
            .chan_num                     = 5,
            .chan_freq                    = 2432,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[5] =
        {
            .chan_num                     = 6,
            .chan_freq                    = 2437,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[6] =
        {
            .chan_num                     = 7,
            .chan_freq                    = 2442,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[7] =
        {
            .chan_num                     = 8,
            .chan_freq                    = 2447,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[8] =
        {
            .chan_num                     = 9,
            .chan_freq                    = 2452,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[9] =
        {
            .chan_num                     = 10,
            .chan_freq                    = 2457,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[10] =
        {
            .chan_num                     = 11,
            .chan_freq                    = 2462,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[11] =
        {
            .chan_num                     = 12,
            .chan_freq                    = 2467,
            .passive_scan_or_radar_detect = true,
        },
    .chan_info[12] =
        {
            .chan_num                     = 13,
            .chan_freq                    = 2472,
            .passive_scan_or_radar_detect = true,
        },
    .chan_info[13] =
        {
            .chan_num                     = 14,
            .chan_freq                    = 2484,
            .passive_scan_or_radar_detect = true,
        },
};

#ifdef CONFIG_5GHz_SUPPORT
static wlan_chanlist_t chanlist_5g_cfg = {
    .num_chans = 7,
    .chan_info[0] =
        {
            .chan_num                     = 36,
            .chan_freq                    = 5180,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[1] =
        {
            .chan_num                     = 40,
            .chan_freq                    = 5200,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[2] =
        {
            .chan_num                     = 44,
            .chan_freq                    = 5220,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[3] =
        {
            .chan_num                     = 48,
            .chan_freq                    = 5240,
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[4] =
        {
            .chan_num                     = 52,
            .chan_freq                    = 5260,
            .passive_scan_or_radar_detect = true,
        },
    .chan_info[5] =
        {
            .chan_num                     = 56,
            .chan_freq                    = 5280,
            .passive_scan_or_radar_detect = true,
        },
    .chan_info[6] =
        {
            .chan_num                     = 100,
            .chan_freq                    = 5500,
            .passive_scan_or_radar_detect = true,
        },
};
#endif

#ifndef CONFIG_11AC
static wifi_txpwrlimit_t tx_pwrlimit_2g_cfg =
    {
        .subband   = (wifi_SubBand_t)0x00,
        .num_chans = 14,
        .txpwrlimit_config[0] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 1,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[1] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 2,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[2] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 3,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[3] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 4,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[4] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 5,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[5] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 6,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[6] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 7,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[7] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 8,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[8] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 9,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[9] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 10,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[10] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 11,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[11] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 12,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[12] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2407,
                        .chan_width = 20,
                        .chan_num   = 13,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
            },
        .txpwrlimit_config[13] =
            {
                .num_mod_grps = 10,
                .chan_desc =
                    {
                        .start_freq = 2414,
                        .chan_width = 20,
                        .chan_num   = 14,
                    },
                .txpwrlimit_entry = {{0, 8}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}},
            },
};

#ifdef CONFIG_5GHz_SUPPORT
static wifi_txpwrlimit_t
    tx_pwrlimit_5g_cfg =
        {
            .subband   = (wifi_SubBand_t)0x00,
            .num_chans = 39,
            .txpwrlimit_config[0] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 36,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[1] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 40,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[2] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 44,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[3] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 48,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[4] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 52,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[5] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 56,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[6] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 60,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[7] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 64,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[8] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 100,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[9] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 104,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[10] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 108,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[11] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 112,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[12] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 116,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[13] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 120,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[14] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 124,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[15] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 128,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[16] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 132,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[17] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 136,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[18] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 140,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[19] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 144,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[20] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 149,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[21] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 153,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[22] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 157,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[23] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 161,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[24] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 165,
                        },
                    .txpwrlimit_entry = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}},
                },
            .txpwrlimit_config[25] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 183,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[26] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 184,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[27] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 185,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[28] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 187,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[29] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 188,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[30] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 189,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[31] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 192,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[32] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 196,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[33] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 7,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[34] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 8,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[35] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 11,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[36] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 12,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[37] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 16,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
            .txpwrlimit_config[38] =
                {
                    .num_mod_grps = 9,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 34,
                        },
                    .txpwrlimit_entry =
                        {{1, 17}, {2, 16}, {3, 14}, {4, 17}, {5, 16}, {6, 14}, {7, 17}, {8, 16}, {9, 14}},
                },
};
#endif
#else
static wifi_txpwrlimit_t
    tx_pwrlimit_2g_cfg =
        {
            .subband   = (wifi_SubBand_t)0x00,
            .num_chans = 14,
            .txpwrlimit_config[0] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 1,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[1] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 2,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[2] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 3,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[3] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 4,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[4] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 5,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[5] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 6,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[6] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 7,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[7] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 8,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[8] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 9,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[9] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 10,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[10] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 11,
                        },
                    .txpwrlimit_entry = {{0, 18},
                                         {1, 18},
                                         {2, 16},
                                         {3, 14},
                                         {4, 18},
                                         {5, 16},
                                         {6, 14},
                                         {7, 18},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[11] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 12,
                        },
                    .txpwrlimit_entry = {{0, 16},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[12] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2407,
                            .chan_width = 20,
                            .chan_num   = 13,
                        },
                    .txpwrlimit_entry = {{0, 16},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 16},
                                         {11, 16}},
                },
            .txpwrlimit_config[13] =
                {
                    .num_mod_grps = 12,
                    .chan_desc =
                        {
                            .start_freq = 2414,
                            .chan_width = 20,
                            .chan_num   = 14,
                        },
                    .txpwrlimit_entry = {{0, 12},
                                         {1, 12},
                                         {2, 12},
                                         {3, 12},
                                         {4, 12},
                                         {5, 12},
                                         {6, 12},
                                         {7, 12},
                                         {8, 12},
                                         {9, 12},
                                         {10, 12},
                                         {11, 12}},
                },
};

#ifdef CONFIG_5GHz_SUPPORT
static wifi_txpwrlimit_t
    tx_pwrlimit_5g_cfg =
        {
            .subband   = (wifi_SubBand_t)0x00,
            .num_chans = 39,
            .txpwrlimit_config[0] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 36,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[1] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 40,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[2] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 44,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[3] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 48,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 16},
                                         {2, 16},
                                         {3, 14},
                                         {4, 16},
                                         {5, 16},
                                         {6, 14},
                                         {7, 16},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[4] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 52,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 17},
                                         {2, 16},
                                         {3, 14},
                                         {4, 17},
                                         {5, 16},
                                         {6, 14},
                                         {7, 17},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[5] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 56,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 17},
                                         {2, 16},
                                         {3, 14},
                                         {4, 17},
                                         {5, 16},
                                         {6, 14},
                                         {7, 17},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[6] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 60,
                        },
                    .txpwrlimit_entry = {{0, 0},
                                         {1, 17},
                                         {2, 16},
                                         {3, 14},
                                         {4, 17},
                                         {5, 16},
                                         {6, 14},
                                         {7, 17},
                                         {8, 16},
                                         {9, 14},
                                         {10, 15},
                                         {11, 14},
                                         {12, 15},
                                         {13, 15},
                                         {14, 14},
                                         {15, 13}},
                },
            .txpwrlimit_config[7] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 64,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[8] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 100,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[9] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 104,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[10] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 108,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[11] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 112,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[12] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 116,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[13] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 120,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[14] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 124,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[15] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 128,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[16] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 132,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[17] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 136,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[18] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 140,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[19] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 144,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[20] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 149,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[21] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 153,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[22] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 157,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[23] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 161,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[24] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 165,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[25] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 183,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[26] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 184,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[27] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 185,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[28] =
                {
                    .num_mod_grps = 16,
                    .chan_desc    = {.start_freq = 5000, .chan_width = 20, .chan_num = 187},
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[29] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 188,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[30] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 189,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[31] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 192,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[32] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 196,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[33] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 7,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[34] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 8,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[35] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 11,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[36] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 12,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[37] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 16,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
            .txpwrlimit_config[38] =
                {
                    .num_mod_grps = 16,
                    .chan_desc =
                        {
                            .start_freq = 5000,
                            .chan_width = 20,
                            .chan_num   = 34,
                        },
                    .txpwrlimit_entry =
                        {{0, 0},
                         {1, 17},
                         {2, 16},
                         {3, 14},
                         {4, 17},
                         {5, 16},
                         {6, 14},
                         {7, 17},
                         {8, 16},
                         {9, 14},
                         {10, 15},
                         {11, 14},
                         {12, 15},
                         {13, 15},
                         {14, 14},
                         {15, 13}},
                },
};
#endif /* CONFIG_5GHz_SUPPORT */
#endif /* CONFIG_11AC */
