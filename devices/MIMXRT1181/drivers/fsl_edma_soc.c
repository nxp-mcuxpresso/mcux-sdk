/*
 * Copyright 2022-2023 NXP
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
extern void DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler(void);
extern void DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler(void);
extern void DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler(void);
extern void DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler(void);
extern void DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler(void);
extern void DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler(void);
extern void DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler(void);
extern void DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler(void);
extern void DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler(void);
extern void DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler(void);
extern void DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler(void);
extern void DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler(void);
extern void DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler(void);
extern void DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler(void);
extern void DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler(void);
extern void DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler(void);
extern void DMA3_CH0_DriverIRQHandler(void);
extern void DMA3_CH1_DriverIRQHandler(void);
extern void DMA3_CH2_DriverIRQHandler(void);
extern void DMA3_CH3_DriverIRQHandler(void);
extern void DMA3_CH4_DriverIRQHandler(void);
extern void DMA3_CH5_DriverIRQHandler(void);
extern void DMA3_CH6_DriverIRQHandler(void);
extern void DMA3_CH7_DriverIRQHandler(void);
extern void DMA3_CH8_DriverIRQHandler(void);
extern void DMA3_CH9_DriverIRQHandler(void);
extern void DMA3_CH10_DriverIRQHandler(void);
extern void DMA3_CH11_DriverIRQHandler(void);
extern void DMA3_CH12_DriverIRQHandler(void);
extern void DMA3_CH13_DriverIRQHandler(void);
extern void DMA3_CH14_DriverIRQHandler(void);
extern void DMA3_CH15_DriverIRQHandler(void);
extern void DMA3_CH16_DriverIRQHandler(void);
extern void DMA3_CH17_DriverIRQHandler(void);
extern void DMA3_CH18_DriverIRQHandler(void);
extern void DMA3_CH19_DriverIRQHandler(void);
extern void DMA3_CH20_DriverIRQHandler(void);
extern void DMA3_CH21_DriverIRQHandler(void);
extern void DMA3_CH22_DriverIRQHandler(void);
extern void DMA3_CH23_DriverIRQHandler(void);
extern void DMA3_CH24_DriverIRQHandler(void);
extern void DMA3_CH25_DriverIRQHandler(void);
extern void DMA3_CH26_DriverIRQHandler(void);
extern void DMA3_CH27_DriverIRQHandler(void);
extern void DMA3_CH28_DriverIRQHandler(void);
extern void DMA3_CH29_DriverIRQHandler(void);
extern void DMA3_CH30_DriverIRQHandler(void);
extern void DMA3_CH31_DriverIRQHandler(void);
extern void EDMA_DriverIRQHandler(uint32_t instance, uint32_t channel);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief DMA instance 1, channel 0~1, 32~33 IRQ handler.
 *
 */
void DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler(void)
{
    /* Instance 1 channel 0 */
    EDMA_DriverIRQHandler(1U, 0U);
    /* Instance 1 channel 1 */
    EDMA_DriverIRQHandler(1U, 1U);
    /* Instance 1 channel 32 */
    EDMA_DriverIRQHandler(1U, 32U);
    /* Instance 1 channel 33 */
    EDMA_DriverIRQHandler(1U, 33U);
}

/*!
 * brief DMA instance 1, channel 2~3, 34~35 IRQ handler.
 *
 */
void DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler(void)
{
    /* Instance 1 channel 2 */
    EDMA_DriverIRQHandler(1U, 2U);
    /* Instance 1 channel 3 */
    EDMA_DriverIRQHandler(1U, 3U);
    /* Instance 1 channel 34 */
    EDMA_DriverIRQHandler(1U, 34U);
    /* Instance 1 channel 35 */
    EDMA_DriverIRQHandler(1U, 35U);
}

/*!
 * brief DMA instance 1, channel 4~5, 36~37 IRQ handler.
 *
 */
void DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler(void)
{
    /* Instance 1 channel 4 */
    EDMA_DriverIRQHandler(1U, 4U);
    /* Instance 1 channel 5 */
    EDMA_DriverIRQHandler(1U, 5U);
    /* Instance 1 channel 36 */
    EDMA_DriverIRQHandler(1U, 36U);
    /* Instance 1 channel 37 */
    EDMA_DriverIRQHandler(1U, 37U);
}

/*!
 * brief DMA instance 1, channel 6~7, 38~39 IRQ handler.
 *
 */
void DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler(void)
{
    /* Instance 1 channel 6 */
    EDMA_DriverIRQHandler(1U, 6U);
    /* Instance 1 channel 7 */
    EDMA_DriverIRQHandler(1U, 7U);
    /* Instance 1 channel 38 */
    EDMA_DriverIRQHandler(1U, 38U);
    /* Instance 1 channel 39 */
    EDMA_DriverIRQHandler(1U, 39U);
}

/*!
 * brief DMA instance 1, channel 8~9, 40~41 IRQ handler.
 *
 */
void DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler(void)
{
    /* Instance 1 channel 8 */
    EDMA_DriverIRQHandler(1U, 8U);
    /* Instance 1 channel 9 */
    EDMA_DriverIRQHandler(1U, 9U);
    /* Instance 1 channel 40 */
    EDMA_DriverIRQHandler(1U, 40U);
    /* Instance 1 channel 41 */
    EDMA_DriverIRQHandler(1U, 41U);
}

/*!
 * brief DMA instance 1, channel 10~11, 42~43 IRQ handler.
 *
 */
void DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler(void)
{
    /* Instance 1 channel 10 */
    EDMA_DriverIRQHandler(1U, 10U);
    /* Instance 1 channel 11 */
    EDMA_DriverIRQHandler(1U, 11U);
    /* Instance 1 channel 42 */
    EDMA_DriverIRQHandler(1U, 42U);
    /* Instance 1 channel 43 */
    EDMA_DriverIRQHandler(1U, 43U);
}

/*!
 * brief DMA instance 1, channel 12~13, 44~45 IRQ handler.
 *
 */
void DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler(void)
{
    /* Instance 1 channel 12 */
    EDMA_DriverIRQHandler(1U, 12U);
    /* Instance 1 channel 13 */
    EDMA_DriverIRQHandler(1U, 13U);
    /* Instance 1 channel 44 */
    EDMA_DriverIRQHandler(1U, 44U);
    /* Instance 1 channel 45 */
    EDMA_DriverIRQHandler(1U, 45U);
}

/*!
 * brief DMA instance 1, channel 14~15, 46~47 IRQ handler.
 *
 */
void DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler(void)
{
    /* Instance 1 channel 14 */
    EDMA_DriverIRQHandler(1U, 14U);
    /* Instance 1 channel 15 */
    EDMA_DriverIRQHandler(1U, 15U);
    /* Instance 1 channel 46 */
    EDMA_DriverIRQHandler(1U, 46U);
    /* Instance 1 channel 47 */
    EDMA_DriverIRQHandler(1U, 47U);
}

/*!
 * brief DMA instance 1, channel 16~17, 48~49 IRQ handler.
 *
 */
void DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler(void)
{
    /* Instance 1 channel 16 */
    EDMA_DriverIRQHandler(1U, 16U);
    /* Instance 1 channel 17 */
    EDMA_DriverIRQHandler(1U, 17U);
    /* Instance 1 channel 48 */
    EDMA_DriverIRQHandler(1U, 48U);
    /* Instance 1 channel 49 */
    EDMA_DriverIRQHandler(1U, 49U);
}

/*!
 * brief DMA instance 1, channel 18~19, 50~51 IRQ handler.
 *
 */
void DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler(void)
{
    /* Instance 1 channel 18 */
    EDMA_DriverIRQHandler(1U, 18U);
    /* Instance 1 channel 19 */
    EDMA_DriverIRQHandler(1U, 19U);
    /* Instance 1 channel 50 */
    EDMA_DriverIRQHandler(1U, 50U);
    /* Instance 1 channel 51 */
    EDMA_DriverIRQHandler(1U, 51U);
}

/*!
 * brief DMA instance 1, channel 20~21, 52~53 IRQ handler.
 *
 */
void DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler(void)
{
    /* Instance 1 channel 20 */
    EDMA_DriverIRQHandler(1U, 20U);
    /* Instance 1 channel 21 */
    EDMA_DriverIRQHandler(1U, 21U);
    /* Instance 1 channel 52 */
    EDMA_DriverIRQHandler(1U, 52U);
    /* Instance 1 channel 53 */
    EDMA_DriverIRQHandler(1U, 53U);
}

/*!
 * brief DMA instance 1, channel 22~23, 54~55 IRQ handler.
 *
 */
void DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler(void)
{
    /* Instance 1 channel 22 */
    EDMA_DriverIRQHandler(1U, 22U);
    /* Instance 1 channel 23 */
    EDMA_DriverIRQHandler(1U, 23U);
    /* Instance 1 channel 54 */
    EDMA_DriverIRQHandler(1U, 54U);
    /* Instance 1 channel 55 */
    EDMA_DriverIRQHandler(1U, 55U);
}

/*!
 * brief DMA instance 1, channel 24~25, 56~57 IRQ handler.
 *
 */
void DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler(void)
{
    /* Instance 1 channel 24 */
    EDMA_DriverIRQHandler(1U, 24U);
    /* Instance 1 channel 25 */
    EDMA_DriverIRQHandler(1U, 25U);
    /* Instance 1 channel 56 */
    EDMA_DriverIRQHandler(1U, 56U);
    /* Instance 1 channel 57 */
    EDMA_DriverIRQHandler(1U, 57U);
}

/*!
 * brief DMA instance 1, channel 26~27, 58~59 IRQ handler.
 *
 */
void DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler(void)
{
    /* Instance 1 channel 26 */
    EDMA_DriverIRQHandler(1U, 26U);
    /* Instance 1 channel 27 */
    EDMA_DriverIRQHandler(1U, 27U);
    /* Instance 1 channel 58 */
    EDMA_DriverIRQHandler(1U, 58U);
    /* Instance 1 channel 59 */
    EDMA_DriverIRQHandler(1U, 59U);
}

/*!
 * brief DMA instance 1, channel 28~29, 60~61 IRQ handler.
 *
 */
void DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler(void)
{
    /* Instance 1 channel 28 */
    EDMA_DriverIRQHandler(1U, 28U);
    /* Instance 1 channel 29 */
    EDMA_DriverIRQHandler(1U, 29U);
    /* Instance 1 channel 60 */
    EDMA_DriverIRQHandler(1U, 60U);
    /* Instance 1 channel 61 */
    EDMA_DriverIRQHandler(1U, 61U);
}

/*!
 * brief DMA instance 1, channel 30~31, 62~63 IRQ handler.
 *
 */
void DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler(void)
{
    /* Instance 1 channel 30 */
    EDMA_DriverIRQHandler(1U, 30U);
    /* Instance 1 channel 31 */
    EDMA_DriverIRQHandler(1U, 31U);
    /* Instance 1 channel 62 */
    EDMA_DriverIRQHandler(1U, 62U);
    /* Instance 1 channel 63 */
    EDMA_DriverIRQHandler(1U, 63U);
}

/*!
 * brief DMA instance 0, channel 0 IRQ handler.
 *
 */
void DMA3_CH0_DriverIRQHandler(void)
{
    /* Instance 0 channel 0 */
    EDMA_DriverIRQHandler(0U, 0U);
}

/*!
 * brief DMA instance 0, channel 1 IRQ handler.
 *
 */
void DMA3_CH1_DriverIRQHandler(void)
{
    /* Instance 0 channel 1 */
    EDMA_DriverIRQHandler(0U, 1U);
}

/*!
 * brief DMA instance 0, channel 2 IRQ handler.
 *
 */
void DMA3_CH2_DriverIRQHandler(void)
{
    /* Instance 0 channel 2 */
    EDMA_DriverIRQHandler(0U, 2U);
}

/*!
 * brief DMA instance 0, channel 3 IRQ handler.
 *
 */
void DMA3_CH3_DriverIRQHandler(void)
{
    /* Instance 0 channel 3 */
    EDMA_DriverIRQHandler(0U, 3U);
}

/*!
 * brief DMA instance 0, channel 4 IRQ handler.
 *
 */
void DMA3_CH4_DriverIRQHandler(void)
{
    /* Instance 0 channel 4 */
    EDMA_DriverIRQHandler(0U, 4U);
}

/*!
 * brief DMA instance 0, channel 5 IRQ handler.
 *
 */
void DMA3_CH5_DriverIRQHandler(void)
{
    /* Instance 0 channel 5 */
    EDMA_DriverIRQHandler(0U, 5U);
}

/*!
 * brief DMA instance 0, channel 6 IRQ handler.
 *
 */
void DMA3_CH6_DriverIRQHandler(void)
{
    /* Instance 0 channel 6 */
    EDMA_DriverIRQHandler(0U, 6U);
}

/*!
 * brief DMA instance 0, channel 7 IRQ handler.
 *
 */
void DMA3_CH7_DriverIRQHandler(void)
{
    /* Instance 0 channel 7 */
    EDMA_DriverIRQHandler(0U, 7U);
}

/*!
 * brief DMA instance 0, channel 8 IRQ handler.
 *
 */
void DMA3_CH8_DriverIRQHandler(void)
{
    /* Instance 0 channel 8 */
    EDMA_DriverIRQHandler(0U, 8U);
}

/*!
 * brief DMA instance 0, channel 9 IRQ handler.
 *
 */
void DMA3_CH9_DriverIRQHandler(void)
{
    /* Instance 0 channel 9 */
    EDMA_DriverIRQHandler(0U, 9U);
}

/*!
 * brief DMA instance 0, channel 10 IRQ handler.
 *
 */
void DMA3_CH10_DriverIRQHandler(void)
{
    /* Instance 0 channel 10 */
    EDMA_DriverIRQHandler(0U, 10U);
}

/*!
 * brief DMA instance 0, channel 11 IRQ handler.
 *
 */
void DMA3_CH11_DriverIRQHandler(void)
{
    /* Instance 0 channel 11 */
    EDMA_DriverIRQHandler(0U, 11U);
}

/*!
 * brief DMA instance 0, channel 12 IRQ handler.
 *
 */
void DMA3_CH12_DriverIRQHandler(void)
{
    /* Instance 0 channel 12 */
    EDMA_DriverIRQHandler(0U, 12U);
}

/*!
 * brief DMA instance 0, channel 13 IRQ handler.
 *
 */
void DMA3_CH13_DriverIRQHandler(void)
{
    /* Instance 0 channel 13 */
    EDMA_DriverIRQHandler(0U, 13U);
}

/*!
 * brief DMA instance 0, channel 14 IRQ handler.
 *
 */
void DMA3_CH14_DriverIRQHandler(void)
{
    /* Instance 0 channel 14 */
    EDMA_DriverIRQHandler(0U, 14U);
}

/*!
 * brief DMA instance 0, channel 15 IRQ handler.
 *
 */
void DMA3_CH15_DriverIRQHandler(void)
{
    /* Instance 0 channel 15 */
    EDMA_DriverIRQHandler(0U, 15U);
}

/*!
 * brief DMA instance 0, channel 16 IRQ handler.
 *
 */
void DMA3_CH16_DriverIRQHandler(void)
{
    /* Instance 0 channel 16 */
    EDMA_DriverIRQHandler(0U, 16U);
}

/*!
 * brief DMA instance 0, channel 17 IRQ handler.
 *
 */
void DMA3_CH17_DriverIRQHandler(void)
{
    /* Instance 0 channel 17 */
    EDMA_DriverIRQHandler(0U, 17U);
}

/*!
 * brief DMA instance 0, channel 18 IRQ handler.
 *
 */
void DMA3_CH18_DriverIRQHandler(void)
{
    /* Instance 0 channel 18 */
    EDMA_DriverIRQHandler(0U, 18U);
}

/*!
 * brief DMA instance 0, channel 19 IRQ handler.
 *
 */
void DMA3_CH19_DriverIRQHandler(void)
{
    /* Instance 0 channel 19 */
    EDMA_DriverIRQHandler(0U, 19U);
}

/*!
 * brief DMA instance 0, channel 20 IRQ handler.
 *
 */
void DMA3_CH20_DriverIRQHandler(void)
{
    /* Instance 0 channel 20 */
    EDMA_DriverIRQHandler(0U, 20U);
}

/*!
 * brief DMA instance 0, channel 21 IRQ handler.
 *
 */
void DMA3_CH21_DriverIRQHandler(void)
{
    /* Instance 0 channel 21 */
    EDMA_DriverIRQHandler(0U, 21U);
}

/*!
 * brief DMA instance 0, channel 22 IRQ handler.
 *
 */
void DMA3_CH22_DriverIRQHandler(void)
{
    /* Instance 0 channel 22 */
    EDMA_DriverIRQHandler(0U, 22U);
}

/*!
 * brief DMA instance 0, channel 23 IRQ handler.
 *
 */
void DMA3_CH23_DriverIRQHandler(void)
{
    /* Instance 0 channel 23 */
    EDMA_DriverIRQHandler(0U, 23U);
}

/*!
 * brief DMA instance 0, channel 24 IRQ handler.
 *
 */
void DMA3_CH24_DriverIRQHandler(void)
{
    /* Instance 0 channel 24 */
    EDMA_DriverIRQHandler(0U, 24U);
}

/*!
 * brief DMA instance 0, channel 25 IRQ handler.
 *
 */
void DMA3_CH25_DriverIRQHandler(void)
{
    /* Instance 0 channel 25 */
    EDMA_DriverIRQHandler(0U, 25U);
}

/*!
 * brief DMA instance 0, channel 26 IRQ handler.
 *
 */
void DMA3_CH26_DriverIRQHandler(void)
{
    /* Instance 0 channel 26 */
    EDMA_DriverIRQHandler(0U, 26U);
}

/*!
 * brief DMA instance 0, channel 27 IRQ handler.
 *
 */
void DMA3_CH27_DriverIRQHandler(void)
{
    /* Instance 0 channel 27 */
    EDMA_DriverIRQHandler(0U, 27U);
}

/*!
 * brief DMA instance 0, channel 28 IRQ handler.
 *
 */
void DMA3_CH28_DriverIRQHandler(void)
{
    /* Instance 0 channel 28 */
    EDMA_DriverIRQHandler(0U, 28U);
}

/*!
 * brief DMA instance 0, channel 29 IRQ handler.
 *
 */
void DMA3_CH29_DriverIRQHandler(void)
{
    /* Instance 0 channel 29 */
    EDMA_DriverIRQHandler(0U, 29U);
}

/*!
 * brief DMA instance 0, channel 30 IRQ handler.
 *
 */
void DMA3_CH30_DriverIRQHandler(void)
{
    /* Instance0 channel 30 */
    EDMA_DriverIRQHandler(0U, 30U);
}

/*!
 * brief DMA instance 0, channel 31 IRQ handler.
 *
 */
void DMA3_CH31_DriverIRQHandler(void)
{
    /* Instance 0 channel 31 */
    EDMA_DriverIRQHandler(0U, 31U);
}
