/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "sm_pinctrl.h"
#include "scmi_pinctrl.h"
#include "scmi_common.h"

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
void SM_PINCTRL_SetPinMux(sm_pinctrl_t *sm_pinctrl)
{
    scmi_pin_config_t configs[3];
    uint32_t numConfigs    = 0;
    uint32_t channel       = sm_pinctrl->channel;
    uint32_t muxRegister   = sm_pinctrl->mux_register;
    uint32_t muxMode       = sm_pinctrl->mux_mode;
    uint32_t inputRegister = sm_pinctrl->input_register;
    uint32_t inputDaisy    = sm_pinctrl->input_daisy;
    uint32_t inputOnfield  = sm_pinctrl->input_on_field;

    if (muxRegister)
    {
        configs[numConfigs].type  = SCMI_PINCTRL_TYPE_MUX;
        configs[numConfigs].value = SM_PLATFORM_PINCTRL_MUX_MODE(muxMode) | SM_PLATFORM_PINCTRL_SION(inputOnfield);
        numConfigs++;
    }

    if (inputRegister & 0xFFFF)
    {
        configs[numConfigs].type  = SCMI_PINCTRL_TYPE_DAISY_ID;
        configs[numConfigs].value = (inputRegister - SM_PLATFORM_PINCTRL_DAISYREG_OFF) / 4;
        numConfigs++;
        configs[numConfigs].type  = SCMI_PINCTRL_TYPE_DAISY_CFG;
        configs[numConfigs].value = inputDaisy;
        numConfigs++;
    }

    if (muxRegister || inputRegister)
    {
        uint32_t status = SCMI_ERR_SUCCESS;
        uint32_t attributes =
            SCMI_PINCTRL_SET_ATTR_SELECTOR(SCMI_PINCTRL_SEL_PIN) | SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS(numConfigs);

        status = SCMI_PinctrlSettingsConfigure(channel, (muxRegister - SM_PLATFORM_PINCTRL_MUXREG_OFF) / 4, 0U, attributes, configs);
        /* Find something wrong ASAP(components/scmi/scmi_common.h: scmi error code) */
        while (status != SCMI_ERR_SUCCESS);
    }
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
void SM_PINCTRL_SetPinCfg(sm_pinctrl_t *sm_pinctrl)
{
    uint32_t channel        = sm_pinctrl->channel;
    uint32_t configRegister = sm_pinctrl->config_register;
    uint32_t configValue    = sm_pinctrl->config_value;

    if (configRegister)
    {
        uint32_t status = SCMI_ERR_SUCCESS;
        uint32_t attributes =
            SCMI_PINCTRL_SET_ATTR_SELECTOR(SCMI_PINCTRL_SEL_PIN) | SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS(1);
        scmi_pin_config_t configs;

        configs.type  = SCMI_PINCTRL_TYPE_CONFIG;
        configs.value = configValue;

        status = SCMI_PinctrlSettingsConfigure(channel, (configRegister - SM_PLATFORM_PINCTRL_CFGREG_OFF) / 4, 0U, attributes, &configs);
        /* Find something wrong ASAP(components/scmi/scmi_common.h: scmi error code) */
        while (status != SCMI_ERR_SUCCESS);
    }
}
