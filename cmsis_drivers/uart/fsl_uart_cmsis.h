/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2023 NXP. Not a Contribution.
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
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_uart_dma.h"
#endif
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
#include "fsl_uart_edma.h"
#endif

#if defined(UART0) && defined(RTE_USART0) && RTE_USART0
extern ARM_DRIVER_USART Driver_USART0;
#endif /* UART0 */

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

#if defined(UART5) && defined(RTE_USART5) && RTE_USART5
extern ARM_DRIVER_USART Driver_USART5;
#endif /* UART5 */

#if (FSL_FEATURE_SOC_LPUART_COUNT == 3) && (FSL_FEATURE_SOC_UART_COUNT == 2)
#if defined(UART0) && defined(RTE_USART3) && RTE_USART3
extern ARM_DRIVER_USART Driver_USART3;
#endif /* UART0 */
#if defined(UART1) && defined(RTE_USART4) && RTE_USART4
extern ARM_DRIVER_USART Driver_USART4;
#endif /* UART1 */
#endif

/* USART Driver state flags */
#define USART_FLAG_UNINIT     (0UL)
#define USART_FLAG_INIT       (1UL << 0)
#define USART_FLAG_POWER      (1UL << 1)
#define USART_FLAG_CONFIGURED (1UL << 2)

#endif /* FSL_UART_CMSIS_H_ */
