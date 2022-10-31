/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_edma_soc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.edma_soc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void EDMA_DriverIRQHandler(uint32_t instance, uint32_t channel);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief DMA instance 1, channel 0~1 IRQ handler.
 *
 */
void DMA4_0_1_DriverIRQHandler(void)
{
    /* Instance 1 channel 0 */
    EDMA_DriverIRQHandler(1U, 0U);
    /* Instance 1 channel 1 */
    EDMA_DriverIRQHandler(1U, 1U);
}

/*!
 * brief DMA instance 1, channel 2~3 IRQ handler.
 *
 */
void DMA4_2_3_DriverIRQHandler(void)
{
    /* Instance 1 channel 2 */
    EDMA_DriverIRQHandler(1U, 2U);
    /* Instance 1 channel 3 */
    EDMA_DriverIRQHandler(1U, 3U);
}

/*!
 * brief DMA instance 1, channel 4~5 IRQ handler.
 *
 */
void DMA4_4_5_DriverIRQHandler(void)
{
    /* Instance 1 channel 4 */
    EDMA_DriverIRQHandler(1U, 4U);
    /* Instance 1 channel 5 */
    EDMA_DriverIRQHandler(1U, 5U);
}

/*!
 * brief DMA instance 1, channel 6~7 IRQ handler.
 *
 */
void DMA4_6_7_DriverIRQHandler(void)
{
    /* Instance 1 channel 6 */
    EDMA_DriverIRQHandler(1U, 6U);
    /* Instance 1 channel 7 */
    EDMA_DriverIRQHandler(1U, 7U);
}

/*!
 * brief DMA instance 1, channel 8~9 IRQ handler.
 *
 */
void DMA4_8_9_DriverIRQHandler(void)
{
    /* Instance 1 channel 8 */
    EDMA_DriverIRQHandler(1U, 8U);
    /* Instance 1 channel 9 */
    EDMA_DriverIRQHandler(1U, 9U);
}

/*!
 * brief DMA instance 1, channel 10~11 IRQ handler.
 *
 */
void DMA4_10_11_DriverIRQHandler(void)
{
    /* Instance 1 channel 10 */
    EDMA_DriverIRQHandler(1U, 10U);
    /* Instance 1 channel 11 */
    EDMA_DriverIRQHandler(1U, 11U);
}

/*!
 * brief DMA instance 1, channel 12~13 IRQ handler.
 *
 */
void DMA4_12_13_DriverIRQHandler(void)
{
    /* Instance 1 channel 12 */
    EDMA_DriverIRQHandler(1U, 12U);
    /* Instance 1 channel 13 */
    EDMA_DriverIRQHandler(1U, 13U);
}

/*!
 * brief DMA instance 1, channel 14~15 IRQ handler.
 *
 */
void DMA4_14_15_DriverIRQHandler(void)
{
    /* Instance 1 channel 14 */
    EDMA_DriverIRQHandler(1U, 14U);
    /* Instance 1 channel 15 */
    EDMA_DriverIRQHandler(1U, 15U);
}

/*!
 * brief DMA instance 1, channel 16~17 IRQ handler.
 *
 */
void DMA4_16_17_DriverIRQHandler(void)
{
    /* Instance 1 channel 16 */
    EDMA_DriverIRQHandler(1U, 16U);
    /* Instance 1 channel 17 */
    EDMA_DriverIRQHandler(1U, 17U);
}

/*!
 * brief DMA instance 1, channel 18~19 IRQ handler.
 *
 */
void DMA4_18_19_DriverIRQHandler(void)
{
    /* Instance 1 channel 18 */
    EDMA_DriverIRQHandler(1U, 18U);
    /* Instance 1 channel 19 */
    EDMA_DriverIRQHandler(1U, 19U);
}

/*!
 * brief DMA instance 1, channel 20~21 IRQ handler.
 *
 */
void DMA4_20_21_DriverIRQHandler(void)
{
    /* Instance 1 channel 20 */
    EDMA_DriverIRQHandler(1U, 20U);
    /* Instance 1 channel 21 */
    EDMA_DriverIRQHandler(1U, 21U);
}

/*!
 * brief DMA instance 1, channel 22~23 IRQ handler.
 *
 */
void DMA4_22_23_DriverIRQHandler(void)
{
    /* Instance 1 channel 22 */
    EDMA_DriverIRQHandler(1U, 22U);
    /* Instance 1 channel 23 */
    EDMA_DriverIRQHandler(1U, 23U);
}

/*!
 * brief DMA instance 1, channel 24~25 IRQ handler.
 *
 */
void DMA4_24_25_DriverIRQHandler(void)
{
    /* Instance 1 channel 24 */
    EDMA_DriverIRQHandler(1U, 24U);
    /* Instance 1 channel 25 */
    EDMA_DriverIRQHandler(1U, 25U);
}

/*!
 * brief DMA instance 1, channel 26~27 IRQ handler.
 *
 */
void DMA4_26_27_DriverIRQHandler(void)
{
    /* Instance 1 channel 26 */
    EDMA_DriverIRQHandler(1U, 26U);
    /* Instance 1 channel 27 */
    EDMA_DriverIRQHandler(1U, 27U);
}

/*!
 * brief DMA instance 1, channel 28~29 IRQ handler.
 *
 */
void DMA4_28_29_DriverIRQHandler(void)
{
    /* Instance 1 channel 28 */
    EDMA_DriverIRQHandler(1U, 28U);
    /* Instance 1 channel 29 */
    EDMA_DriverIRQHandler(1U, 29U);
}

/*!
 * brief DMA instance 1, channel 30~31 IRQ handler.
 *
 */
void DMA4_30_31_DriverIRQHandler(void)
{
    /* Instance 1 channel 30 */
    EDMA_DriverIRQHandler(1U, 30U);
    /* Instance 1 channel 31 */
    EDMA_DriverIRQHandler(1U, 31U);
}

/*!
 * brief DMA instance 0, channel 0 IRQ handler.
 *
 */
void DMA_0_DriverIRQHandler(void)
{
    /* Instance 0 channel 0 */
    EDMA_DriverIRQHandler(0U, 0U);
}

/*!
 * brief DMA instance 0, channel 1 IRQ handler.
 *
 */
void DMA_1_DriverIRQHandler(void)
{
    /* Instance 0 channel 1 */
    EDMA_DriverIRQHandler(0U, 1U);
}

/*!
 * brief DMA instance 0, channel 2 IRQ handler.
 *
 */
void DMA_2_DriverIRQHandler(void)
{
    /* Instance 0 channel 2 */
    EDMA_DriverIRQHandler(0U, 2U);
}

/*!
 * brief DMA instance 0, channel 3 IRQ handler.
 *
 */
void DMA_3_DriverIRQHandler(void)
{
    /* Instance 0 channel 3 */
    EDMA_DriverIRQHandler(0U, 3U);
}

/*!
 * brief DMA instance 0, channel 4 IRQ handler.
 *
 */
void DMA_4_DriverIRQHandler(void)
{
    /* Instance 0 channel 4 */
    EDMA_DriverIRQHandler(0U, 4U);
}

/*!
 * brief DMA instance 0, channel 5 IRQ handler.
 *
 */
void DMA_5_DriverIRQHandler(void)
{
    /* Instance 0 channel 5 */
    EDMA_DriverIRQHandler(0U, 5U);
}

/*!
 * brief DMA instance 0, channel 6 IRQ handler.
 *
 */
void DMA_6_DriverIRQHandler(void)
{
    /* Instance 0 channel 6 */
    EDMA_DriverIRQHandler(0U, 6U);
}

/*!
 * brief DMA instance 0, channel 7 IRQ handler.
 *
 */
void DMA_7_DriverIRQHandler(void)
{
    /* Instance 0 channel 7 */
    EDMA_DriverIRQHandler(0U, 7U);
}

/*!
 * brief DMA instance 0, channel 8 IRQ handler.
 *
 */
void DMA_8_DriverIRQHandler(void)
{
    /* Instance 0 channel 8 */
    EDMA_DriverIRQHandler(0U, 8U);
}

/*!
 * brief DMA instance 0, channel 9 IRQ handler.
 *
 */
void DMA_9_DriverIRQHandler(void)
{
    /* Instance 0 channel 9 */
    EDMA_DriverIRQHandler(0U, 9U);
}

/*!
 * brief DMA instance 0, channel 10 IRQ handler.
 *
 */
void DMA_10_DriverIRQHandler(void)
{
    /* Instance 0 channel 10 */
    EDMA_DriverIRQHandler(0U, 10U);
}

/*!
 * brief DMA instance 0, channel 11 IRQ handler.
 *
 */
void DMA_11_DriverIRQHandler(void)
{
    /* Instance 0 channel 11 */
    EDMA_DriverIRQHandler(0U, 11U);
}

/*!
 * brief DMA instance 0, channel 12 IRQ handler.
 *
 */
void DMA_12_DriverIRQHandler(void)
{
    /* Instance 0 channel 12 */
    EDMA_DriverIRQHandler(0U, 12U);
}

/*!
 * brief DMA instance 0, channel 13 IRQ handler.
 *
 */
void DMA_13_DriverIRQHandler(void)
{
    /* Instance 0 channel 13 */
    EDMA_DriverIRQHandler(0U, 13U);
}

/*!
 * brief DMA instance 0, channel 14 IRQ handler.
 *
 */
void DMA_14_DriverIRQHandler(void)
{
    /* Instance 0 channel 14 */
    EDMA_DriverIRQHandler(0U, 14U);
}

/*!
 * brief DMA instance 0, channel 15 IRQ handler.
 *
 */
void DMA_15_DriverIRQHandler(void)
{
    /* Instance 0 channel 15 */
    EDMA_DriverIRQHandler(0U, 15U);
}

/*!
 * brief DMA instance 0, channel 16 IRQ handler.
 *
 */
void DMA_16_DriverIRQHandler(void)
{
    /* Instance 0 channel 16 */
    EDMA_DriverIRQHandler(0U, 16U);
}

/*!
 * brief DMA instance 0, channel 17 IRQ handler.
 *
 */
void DMA_17_DriverIRQHandler(void)
{
    /* Instance 0 channel 17 */
    EDMA_DriverIRQHandler(0U, 17U);
}

/*!
 * brief DMA instance 0, channel 18 IRQ handler.
 *
 */
void DMA_18_DriverIRQHandler(void)
{
    /* Instance 0 channel 18 */
    EDMA_DriverIRQHandler(0U, 18U);
}

/*!
 * brief DMA instance 0, channel 19 IRQ handler.
 *
 */
void DMA_19_DriverIRQHandler(void)
{
    /* Instance 0 channel 19 */
    EDMA_DriverIRQHandler(0U, 19U);
}

/*!
 * brief DMA instance 0, channel 20 IRQ handler.
 *
 */
void DMA_20_DriverIRQHandler(void)
{
    /* Instance 0 channel 20 */
    EDMA_DriverIRQHandler(0U, 20U);
}

/*!
 * brief DMA instance 0, channel 21 IRQ handler.
 *
 */
void DMA_21_DriverIRQHandler(void)
{
    /* Instance 0 channel 21 */
    EDMA_DriverIRQHandler(0U, 21U);
}

/*!
 * brief DMA instance 0, channel 22 IRQ handler.
 *
 */
void DMA_22_DriverIRQHandler(void)
{
    /* Instance 0 channel 22 */
    EDMA_DriverIRQHandler(0U, 22U);
}

/*!
 * brief DMA instance 0, channel 23 IRQ handler.
 *
 */
void DMA_23_DriverIRQHandler(void)
{
    /* Instance 0 channel 23 */
    EDMA_DriverIRQHandler(0U, 23U);
}

/*!
 * brief DMA instance 0, channel 24 IRQ handler.
 *
 */
void DMA_24_DriverIRQHandler(void)
{
    /* Instance 0 channel 24 */
    EDMA_DriverIRQHandler(0U, 24U);
}

/*!
 * brief DMA instance 0, channel 25 IRQ handler.
 *
 */
void DMA_25_DriverIRQHandler(void)
{
    /* Instance 0 channel 25 */
    EDMA_DriverIRQHandler(0U, 25U);
}

/*!
 * brief DMA instance 0, channel 26 IRQ handler.
 *
 */
void DMA_26_DriverIRQHandler(void)
{
    /* Instance 0 channel 26 */
    EDMA_DriverIRQHandler(0U, 26U);
}

/*!
 * brief DMA instance 0, channel 27 IRQ handler.
 *
 */
void DMA_27_DriverIRQHandler(void)
{
    /* Instance 0 channel 27 */
    EDMA_DriverIRQHandler(0U, 27U);
}

/*!
 * brief DMA instance 0, channel 28 IRQ handler.
 *
 */
void DMA_28_DriverIRQHandler(void)
{
    /* Instance 0 channel 28 */
    EDMA_DriverIRQHandler(0U, 28U);
}

/*!
 * brief DMA instance 0, channel 29 IRQ handler.
 *
 */
void DMA_29_DriverIRQHandler(void)
{
    /* Instance 0 channel 29 */
    EDMA_DriverIRQHandler(0U, 29U);
}

/*!
 * brief DMA instance 0, channel 30 IRQ handler.
 *
 */
void DMA_30_DriverIRQHandler(void)
{
    /* Instance0 channel 30 */
    EDMA_DriverIRQHandler(0U, 30U);
}
