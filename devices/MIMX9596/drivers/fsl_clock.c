/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_clock.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
volatile uint32_t g_clockSourceFreq[kCLOCK_LdbPll + 1];

uint32_t CLOCK_GetIpFreq(clock_root_t name)
{
    hal_clk_id_e clk_id = (hal_clk_id_e)(name + HAL_CLOCK_PLATFORM_SOURCE_NUM);
    return HAL_ClockGetIpFreq(clk_id);
}

/*!
 * @brief Get CCM Root Clock Source.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @param src Clock mux value to get, see \ref clock_root_mux_source_t.
 * @return Clock source
 */
clock_name_t CLOCK_GetRootClockSource(clock_root_t root, uint32_t src)
{
    return s_clockSourceName[root][src];
}


/*!
 * @brief Power Off Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
void CLOCK_PowerOffRootClock(clock_root_t root)
{
    hal_clk_t hal_ClkCfg = {
        .clk_id = (hal_clk_id_e)(HAL_CLOCK_PLATFORM_SOURCE_NUM + root),
        .enable_clk = false,
    };
    HAL_ClockSetRootClk(&hal_ClkCfg);
}

/*!
 * @brief Power On Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
void CLOCK_PowerOnRootClock(clock_root_t root)
{
    hal_clk_t hal_ClkCfg = {
        .clk_id = (hal_clk_id_e)(HAL_CLOCK_PLATFORM_SOURCE_NUM + root),
        .enable_clk = true,
    };
    HAL_ClockSetRootClk(&hal_ClkCfg);
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    hal_clk_id_e pclk_id = (hal_clk_id_e)(CLOCK_GetRootClockSource(root, config->mux));
    hal_clk_t hal_ClkCfg = {
        .clk_id = (hal_clk_id_e)(HAL_CLOCK_PLATFORM_SOURCE_NUM + root),
        .pclk_id = pclk_id,
        .div = config->div,
        .enable_clk = true,
        .clk_round_opt = hal_clk_round_auto,
    };
    HAL_ClockSetRootClk(&hal_ClkCfg);
}

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 */
void CLOCK_EnableClock(clock_ip_name_t name)
{
    hal_clk_t hal_ClkCfg = {
        .clk_id = (hal_clk_id_e)(HAL_CLOCK_PLATFORM_SOURCE_NUM + name),
        .enable_clk = true,
    };
    HAL_ClockSetRootClk(&hal_ClkCfg);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_lpcg_t.
 */
void CLOCK_DisableClock(clock_ip_name_t name)
{
    hal_clk_t hal_ClkCfg = {
        .clk_id = (hal_clk_id_e)(HAL_CLOCK_PLATFORM_SOURCE_NUM + name),
        .enable_clk = false,
    };
    HAL_ClockSetRootClk(&hal_ClkCfg);
}
