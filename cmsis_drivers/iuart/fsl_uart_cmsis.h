/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017 NXP. Not a Contribution.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FSL_UART_CMSIS_H_
#define FSL_UART_CMSIS_H_

#include "fsl_common.h"
#include "Driver_USART.h"
#include "RTE_Device.h"
#include "fsl_uart.h"
#if (defined(FSL_FEATURE_SOC_SDMA_COUNT) && FSL_FEATURE_SOC_SDMA_COUNT)
#include "fsl_uart_sdma.h"
#endif
#if defined(UART1) && defined(RTE_USART1) && RTE_USART1
extern ARM_DRIVER_USART Driver_USART1;
#endif /* UART1 */

#if defined(UART2) && defined(RTE_USART2) && RTE_USART2
extern ARM_DRIVER_USART Driver_USART2;
#endif /* UART2 */

#if defined(UART3) && defined(RTE_USART3) && RTE_USART3
extern ARM_DRIVER_USART Driver_USART3;
#endif /* UART3 */

#if defined(UART4) && defined(RTE_USART4) && RTE_USART4
extern ARM_DRIVER_USART Driver_USART4;
#endif /* UART4 */

/* USART Driver state flags */
#define USART_FLAG_UNINIT     (0U)
#define USART_FLAG_INIT       (1U << 0)
#define USART_FLAG_POWER      (1U << 1)
#define USART_FLAG_CONFIGURED (1U << 2)

#endif /* FSL_UART_CMSIS_H_ */
