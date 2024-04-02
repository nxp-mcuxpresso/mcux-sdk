/*
 * Copyright 2023-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SM_H_
#define FSL_SM_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

/*!
 * @brief Initialize MU interface for SM access.
 */
void SM_Init(void);

/*!
 * @brief Deinitialize MU interface for SM access.
 */
void SM_Deinit(void);

/*!
 * @brief  MU interrupt handler.
 */
void SM_Handler(void);

void IOMUXC_SetPinMux_SM(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield);

void IOMUXC_SetPinConfig_SM(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue);

void CLOCK_SetRootClock_SM(clock_root_t root, const clock_root_config_t *config);
uint32_t CLOCK_GetIpFreq_SM(clock_root_t name);
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* FSL_SM_H_ */
