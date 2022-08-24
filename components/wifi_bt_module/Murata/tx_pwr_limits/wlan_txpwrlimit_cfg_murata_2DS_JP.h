/** @file wlan_txpwrlimit_cfg_murata_2DS_JP.h
 *
 *  @brief  This file provides Murata 2DS WLAN JP Tx Power Limit APIs.
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
    .num_chans = 13,
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
            .passive_scan_or_radar_detect = false,
        },
    .chan_info[12] =
        {
            .chan_num                     = 13,
            .chan_freq                    = 2472,
            .passive_scan_or_radar_detect = false,
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

static wifi_txpwrlimit_t tx_pwrlimit_2g_cfg = {
    .subband   = (wifi_SubBand_t)0x00,
    .num_chans = 13,
    .txpwrlimit_config[0] =
        {
            .num_mod_grps = 10,
            .chan_desc =
                {
                    .start_freq = 2407,
                    .chan_width = 20,
                    .chan_num   = 1,
                },
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
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
            .txpwrlimit_entry = {{0, 14}, {1, 15}, {2, 14}, {3, 14}, {4, 15}, {5, 15}, {6, 14}, {7, 0}, {8, 0}, {9, 0}},
        },
};
