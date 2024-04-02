/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_config.h"
#include "hal_pinctrl.h"
#if SM_PINCTRL
#include "sm_pinctrl.h"
#elif IOMUXC_PINCTRL
#include "fsl_iomuxc.h"
#endif

#if SM_PINCTRL && IOMUXC_PINCTRL
#error "Pls not define them as 1 at the same time in hal_config.h!!!"
#endif

#if SM_PINCTRL
void HAL_PinctrlSetPinMux(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t inputOnfield)
{
    sm_pinctrl_t sm_pinctrl = {0};

    sm_pinctrl.channel         = SM_PLATFORM_A2P;
    sm_pinctrl.mux_register    = muxRegister;
    sm_pinctrl.mux_mode        = muxMode;
    sm_pinctrl.input_register  = inputRegister;
    sm_pinctrl.input_daisy     = inputDaisy;
    sm_pinctrl.config_register = configRegister;
    sm_pinctrl.config_value    = 0U;
    sm_pinctrl.input_on_field  = inputOnfield;

    SM_PINCTRL_SetPinMux(&sm_pinctrl);
}

void HAL_PinctrlSetPinCfg(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t configValue)
{
    sm_pinctrl_t sm_pinctrl = {0};

    sm_pinctrl.channel         = SM_PLATFORM_A2P;
    sm_pinctrl.mux_register    = muxRegister;
    sm_pinctrl.mux_mode        = muxMode;
    sm_pinctrl.input_register  = inputRegister;
    sm_pinctrl.input_daisy     = inputDaisy;
    sm_pinctrl.config_register = configRegister;
    sm_pinctrl.config_value    = configValue;
    sm_pinctrl.input_on_field  = 0U;

    SM_PINCTRL_SetPinCfg(&sm_pinctrl);
}


void HAL_PinctrlSetMiscCfg(hal_pinctrl_t *hal_pinctrl)
{

}

#elif IOMUXC_PINCTRL
void HAL_PinctrlSetPinMux(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t inputOnfield)
{
    IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, inputOnfield);
}

void HAL_PinctrlSetPinCfg(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t configValue)
{
    IOMUXC_SetPinConfig(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, configValue);
}

void HAL_PinctrlSetMiscCfg(hal_pinctrl_t *hal_pinctrl)
{
    if ((hal_pinctrl != NULL) && (hal_pinctrl->set_gpr == true))
    {
        IOMUXC_SetGpr(hal_pinctrl->gpr_instance, hal_pinctrl->gpr_val);
    }
}
#else
#error "Pls define macro SM_PINCTRL or IOMUXC_PINCTRL in hal_config.h.!!!"
#endif
