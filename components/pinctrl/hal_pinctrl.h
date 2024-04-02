/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HAL_PINCTRL_H_
#define HAL_PINCTRL_H_

#include "fsl_common.h"
#include "hal_pinctrl_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct
{
    bool set_gpr;                 /* true: setup IOMUXC_GPR; false: not setup IOMUXC_GPR */
    uint32_t gpr_instance;        /* IOMUXC_GPR instance */
    uint32_t gpr_val;             /* IOMUXC_GPR value */
} hal_pinctrl_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void HAL_PinctrlSetPinMux(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t inputOnfield);

void HAL_PinctrlSetPinCfg(uint32_t muxRegister,
                          uint32_t muxMode,
                          uint32_t inputRegister,
                          uint32_t inputDaisy,
                          uint32_t configRegister,
                          uint32_t configValue);

void HAL_PinctrlSetMiscCfg(hal_pinctrl_t *hal_pinctrl);
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* HAL_PINCTRL_H_ */
