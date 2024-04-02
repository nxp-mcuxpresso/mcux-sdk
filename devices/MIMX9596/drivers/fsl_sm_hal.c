/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "fsl_sm.h"
#include "fsl_sm_hal.h"
#include "clock_config.h"
#include "fsl_iomuxc.h"

static uint32_t SM_GetSMUsingFlg()
{
#if defined(USING_SM) && USING_SM
    return 1;
#else
    return 0;
#endif
}

void Hal_SM_Handler(void)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        SM_Handler();
}

void Hal_SM_Init(void)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        SM_Init();
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
void Hal_CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        CLOCK_SetRootClock_SM(root, config);
    else
        CLOCK_SetRootClock(root, config);

}

uint32_t Hal_CLOCK_GetIpFreq(clock_root_t name)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        return CLOCK_GetIpFreq_SM(name);
    else
        return CLOCK_GetIpFreq(name);
}
/*!
 * @brief Sets the IOMUXC pin mux mode.
 * @note The first five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param inputOn        The software input on
 */
void Hal_IOMUXC_SetPinMux(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        IOMUXC_SetPinMux_SM(muxRegister, muxMode, inputRegister, inputDaisy, 
                configRegister, inputOnfield);
    else
        IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy, 
                configRegister, inputOnfield);
}

/*!
 * @brief Sets the IOMUXC pin configuration.
 * @note The previous five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param configValue    The pin config value
 */
void Hal_IOMUXC_SetPinConfig(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue)
{
    uint32_t flg = SM_GetSMUsingFlg();

    if(flg)
        IOMUXC_SetPinConfig_SM(muxRegister, muxMode, inputRegister, inputDaisy, 
                configRegister, configValue);
    else
        IOMUXC_SetPinConfig(muxRegister, muxMode, inputRegister, inputDaisy, 
                configRegister, configValue);
}
