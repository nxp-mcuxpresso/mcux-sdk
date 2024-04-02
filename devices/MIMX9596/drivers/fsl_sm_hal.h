/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


void Hal_SM_Init(void);
void Hal_SM_Handler(void);
void Hal_CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config);
uint32_t Hal_CLOCK_GetIpFreq(clock_root_t name);
void Hal_IOMUXC_SetPinMux(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield);
void Hal_IOMUXC_SetPinConfig(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue);
