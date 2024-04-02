/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef SM_PINCTRL_H_
#define SM_PINCTRL_H_

#include "fsl_common.h"
#include "sm_platform.h"

/*******************************************************************************
 * definition
 ******************************************************************************/
typedef struct
{
    uint32_t channel;
    uint32_t mux_register;
    uint32_t mux_mode;
    uint32_t input_register;
    uint32_t input_daisy;
    uint32_t config_register;
    uint32_t config_value;
    uint32_t input_on_field;
} sm_pinctrl_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void SM_PINCTRL_SetPinMux(sm_pinctrl_t *sm_pinctrl);
void SM_PINCTRL_SetPinCfg(sm_pinctrl_t *sm_pinctrl);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* SM_PINCTRL_H_ */
