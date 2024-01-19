/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2020 NXP. Not a Contribution.
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

#ifndef FSL_SPI_CMSIS_H_
#define FSL_SPI_CMSIS_H_

#include "fsl_common.h"
#include "fsl_spi.h"
#include "RTE_Device.h"
#include "Driver_SPI.h"
#include "fsl_clock.h"
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_spi_dma.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif

#if defined(SPI0) && defined(RTE_SPI0) && RTE_SPI0
extern ARM_DRIVER_SPI Driver_SPI0;
#endif /* spi0 */

#if defined(SPI1) && defined(RTE_SPI1) && RTE_SPI1
extern ARM_DRIVER_SPI Driver_SPI1;
#endif /* spi1 */

/* SPI Driver state flags */
#define SPI_FLAG_UNINIT     (0UL)
#define SPI_FLAG_INIT       (1UL << 0)
#define SPI_FLAG_POWER      (1UL << 1)
#define SPI_FLAG_CONFIGURED (1UL << 2)

#endif
