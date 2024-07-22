/*
 * Copyright 2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"
#include "fsl_upower.h"

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);


/*******************************************************************************
 * DEFINITION
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ 24000000U
#define BOARD_XTAL32K_CLK_HZ 32768U
#define SWITCH_DRIVE_MODE_INIT_STATE (0)
#define SWITCH_DRIVE_MODE_FROM_ND_TO_OD (1)
#define SWITCH_DRIVE_MODE_FROM_ND_TO_UD (2)
#define SWITCH_DRIVE_MODE_FROM_UD_TO_ND (3)
#define SWITCH_DRIVE_MODE_FROM_OD_TO_ND (4)

/* clock freqeuncy */
#define FREQ_12_5_MHZ (125000000U)
#define FREQ_20_MHZ (20000000U)
#define FREQ_24_MHZ (24000000U)
#define FREQ_38_4_MHZ (38400000U)
#define FREQ_65_MHZ (65000000U)
#define FREQ_108_MHZ (108000000U)
#define FREQ_160_MHZ (160000000U)
#define FREQ_216_MHZ (216000000U)

/*
 * m33 core frequency
 * OD: Over Drive Mode(1.1 V)
 * ND: Nominal Drive Mode(1.0 V)
 * UD: Under Drive Mode(0.9 V)
 */
#define CM33_CORE_MAX_FREQ_OD     (FREQ_216_MHZ)
#define CM33_CORE_MAX_FREQ_ND     (FREQ_160_MHZ)
#define CM33_CORE_MAX_FREQ_UD     (FREQ_38_4_MHZ)
#define CM33_BUS_MAX_FREQ_OD      (FREQ_108_MHZ)
#define CM33_BUS_MAX_FREQ_ND      (FREQ_65_MHZ)
#define CM33_BUS_MAX_FREQ_UD      (FREQ_20_MHZ)
#define CM33_SLOW_MAX_FREQ_OD     (FREQ_24_MHZ)
#define CM33_SLOW_MAX_FREQ_ND     (FREQ_20_MHZ)
#define CM33_SLOW_MAX_FREQ_UD     (FREQ_12_5_MHZ)

typedef struct
{
    cgc_rtd_sys_clk_src_t clk_src;
    clock_name_t clk_name;
} rtd_sys_clk_src_and_clk_name_t;

typedef struct
{
    drive_mode_e drive_mode;
    uint32_t max_core_clk_freq;
    uint32_t max_bus_clk_freq;
    uint32_t max_slow_clk_freq;
} drive_mode_and_clk_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

void BOARD_InitClock(void);

void BOARD_BootClockRUN(void);

void BOARD_ResumeClockInit(void);

void BOARD_CalculateDivider(uint32_t src_freq, uint32_t dest_freq, int * divider);

drive_mode_e BOARD_CalculateCoreClkDivider(cgc_rtd_sys_clk_src_t clk_src, int *core_clk_divider, int *bus_clk_divider, int *slow_clk_divider, drive_mode_e drive_mode);


void BOARD_InitPlls(void);
drive_mode_e BOARD_SwitchToFROClk(drive_mode_e drive_mode);
void BOARD_DisablePlls(void);
drive_mode_e BOARD_GetRtdDriveMode(void);
drive_mode_e BOARD_GetDriveModeByCoreFreq(uint32_t freq);
int32_t BOARD_UpdateM33CoreFreq(cgc_rtd_sys_clk_config_t *config);
void BOARD_SwitchDriveMode(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */
