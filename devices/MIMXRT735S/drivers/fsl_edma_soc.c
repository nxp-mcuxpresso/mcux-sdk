/*
 * Copyright 2023 NXP
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

#if defined(MIMXRT798S_hifi4_SERIES) || defined(MIMXRT798S_cm33_core0_SERIES) || \
    defined(MIMXRT758S_cm33_core0_SERIES) || defined(MIMXRT735S_cm33_core0_SERIES)
#define SYSCON_BASE SYSCON0
#else
#define SYSCON_BASE SYSCON1
#endif

#define DMAC_EN_REG_OFFSET 0x420U
#define DMAC_EN_REG(instance, idx) \
    ((volatile uint32_t *)((uint32_t)(SYSCON_BASE) + (DMAC_EN_REG_OFFSET) + 0x10U * (instance) + 4U * (idx)))
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void EDMA_DriverIRQHandler(uint32_t instance, uint32_t channel);
static DMA_Type *const s_edmaBases[] = EDMA_BASE_PTRS;
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EDMA_GetInstance(DMA_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_edmaBases); instance++)
    {
        if (s_edmaBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_edmaBases));

    return instance;
}

void EDMA_EnableRequest(DMA_Type *base, dma_request_source_t requestSource)
{
    volatile uint32_t *reg;
    uint32_t regIdx = (uint32_t)requestSource / 32U;

    reg = DMAC_EN_REG(EDMA_GetInstance(base), regIdx);
    *reg |= 0x1UL << ((uint32_t)requestSource % 32U);
}

void EDMA_DisableRequest(DMA_Type *base, dma_request_source_t requestSource)
{
    volatile uint32_t *reg;
    uint32_t regIdx = (uint32_t)requestSource / 32U;

    reg = DMAC_EN_REG(EDMA_GetInstance(base), regIdx);
    *reg &= ~(0x1UL << ((uint32_t)requestSource % 32U));
}

#if defined(DMA0)
/*!
 * brief DMA instance 0, channel 0 IRQ handler.
 *
 */
extern void EDMA0_CH0_DriverIRQHandler(void);
void EDMA0_CH0_DriverIRQHandler(void)
{
    /* Instance 0 channel 0 */
    EDMA_DriverIRQHandler(0U, 0U);
}

/*!
 * brief DMA instance 0, channel 1 IRQ handler.
 *
 */
extern void EDMA0_CH1_DriverIRQHandler(void);
void EDMA0_CH1_DriverIRQHandler(void)
{
    /* Instance 0 channel 1 */
    EDMA_DriverIRQHandler(0U, 1U);
}

/*!
 * brief DMA instance 0, channel 2 IRQ handler.
 *
 */
extern void EDMA0_CH2_DriverIRQHandler(void);
void EDMA0_CH2_DriverIRQHandler(void)
{
    /* Instance 0 channel 2 */
    EDMA_DriverIRQHandler(0U, 2U);
}

/*!
 * brief DMA instance 0, channel 3 IRQ handler.
 *
 */
extern void EDMA0_CH3_DriverIRQHandler(void);
void EDMA0_CH3_DriverIRQHandler(void)
{
    /* Instance 0 channel 3 */
    EDMA_DriverIRQHandler(0U, 3U);
}

/*!
 * brief DMA instance 0, channel 4 IRQ handler.
 *
 */
extern void EDMA0_CH4_DriverIRQHandler(void);
void EDMA0_CH4_DriverIRQHandler(void)
{
    /* Instance 0 channel 4 */
    EDMA_DriverIRQHandler(0U, 4U);
}

/*!
 * brief DMA instance 0, channel 5 IRQ handler.
 *
 */
extern void EDMA0_CH5_DriverIRQHandler(void);
void EDMA0_CH5_DriverIRQHandler(void)
{
    /* Instance 0 channel 5 */
    EDMA_DriverIRQHandler(0U, 5U);
}

/*!
 * brief DMA instance 0, channel 6 IRQ handler.
 *
 */
extern void EDMA0_CH6_DriverIRQHandler(void);
void EDMA0_CH6_DriverIRQHandler(void)
{
    /* Instance 0 channel 6 */
    EDMA_DriverIRQHandler(0U, 6U);
}

/*!
 * brief DMA instance 0, channel 7 IRQ handler.
 *
 */
extern void EDMA0_CH7_DriverIRQHandler(void);
void EDMA0_CH7_DriverIRQHandler(void)
{
    /* Instance 0 channel 7 */
    EDMA_DriverIRQHandler(0U, 7U);
}

/*!
 * brief DMA instance 0, channel 8 IRQ handler.
 *
 */
extern void EDMA0_CH8_DriverIRQHandler(void);
void EDMA0_CH8_DriverIRQHandler(void)
{
    /* Instance 0 channel 8 */
    EDMA_DriverIRQHandler(0U, 8U);
}

/*!
 * brief DMA instance 0, channel 9 IRQ handler.
 *
 */
extern void EDMA0_CH9_DriverIRQHandler(void);
void EDMA0_CH9_DriverIRQHandler(void)
{
    /* Instance 0 channel 9 */
    EDMA_DriverIRQHandler(0U, 9U);
}

/*!
 * brief DMA instance 0, channel 10 IRQ handler.
 *
 */
extern void EDMA0_CH10_DriverIRQHandler(void);
void EDMA0_CH10_DriverIRQHandler(void)
{
    /* Instance 0 channel 10 */
    EDMA_DriverIRQHandler(0U, 10U);
}

/*!
 * brief DMA instance 0, channel 11 IRQ handler.
 *
 */
extern void EDMA0_CH11_DriverIRQHandler(void);
void EDMA0_CH11_DriverIRQHandler(void)
{
    /* Instance 0 channel 11 */
    EDMA_DriverIRQHandler(0U, 11U);
}

/*!
 * brief DMA instance 0, channel 12 IRQ handler.
 *
 */
extern void EDMA0_CH12_DriverIRQHandler(void);
void EDMA0_CH12_DriverIRQHandler(void)
{
    /* Instance 0 channel 12 */
    EDMA_DriverIRQHandler(0U, 12U);
}

/*!
 * brief DMA instance 0, channel 13 IRQ handler.
 *
 */
extern void EDMA0_CH13_DriverIRQHandler(void);
void EDMA0_CH13_DriverIRQHandler(void)
{
    /* Instance 0 channel 13 */
    EDMA_DriverIRQHandler(0U, 13U);
}

/*!
 * brief DMA instance 0, channel 14 IRQ handler.
 *
 */
extern void EDMA0_CH14_DriverIRQHandler(void);
void EDMA0_CH14_DriverIRQHandler(void)
{
    /* Instance 0 channel 14 */
    EDMA_DriverIRQHandler(0U, 14U);
}

/*!
 * brief DMA instance 0, channel 15 IRQ handler.
 *
 */
extern void EDMA0_CH15_DriverIRQHandler(void);
void EDMA0_CH15_DriverIRQHandler(void)
{
    /* Instance 0 channel 15 */
    EDMA_DriverIRQHandler(0U, 15U);
}
#endif
#if defined(DMA1)
/*!
 * brief DMA instance 1, channel 0 IRQ handler.
 *
 */
extern void EDMA1_CH0_DriverIRQHandler(void);
void EDMA1_CH0_DriverIRQHandler(void)
{
    /* Instance 1 channel 0 */
    EDMA_DriverIRQHandler(1U, 0U);
}

/*!
 * brief DMA instance 1, channel 1 IRQ handler.
 *
 */
extern void EDMA1_CH1_DriverIRQHandler(void);
void EDMA1_CH1_DriverIRQHandler(void)
{
    /* Instance 1 channel 1 */
    EDMA_DriverIRQHandler(1U, 1U);
}

/*!
 * brief DMA instance 1, channel 2 IRQ handler.
 *
 */
extern void EDMA1_CH2_DriverIRQHandler(void);
void EDMA1_CH2_DriverIRQHandler(void)
{
    /* Instance 1 channel 2 */
    EDMA_DriverIRQHandler(1U, 2U);
}

/*!
 * brief DMA instance 1, channel 3 IRQ handler.
 *
 */
extern void EDMA1_CH3_DriverIRQHandler(void);
void EDMA1_CH3_DriverIRQHandler(void)
{
    /* Instance 1 channel 3 */
    EDMA_DriverIRQHandler(1U, 3U);
}

/*!
 * brief DMA instance 1, channel 4 IRQ handler.
 *
 */
extern void EDMA1_CH4_DriverIRQHandler(void);
void EDMA1_CH4_DriverIRQHandler(void)
{
    /* Instance 1 channel 4 */
    EDMA_DriverIRQHandler(1U, 4U);
}

/*!
 * brief DMA instance 1, channel 5 IRQ handler.
 *
 */
extern void EDMA1_CH5_DriverIRQHandler(void);
void EDMA1_CH5_DriverIRQHandler(void)
{
    /* Instance 1 channel 5 */
    EDMA_DriverIRQHandler(1U, 5U);
}

/*!
 * brief DMA instance 1, channel 6 IRQ handler.
 *
 */
extern void EDMA1_CH6_DriverIRQHandler(void);
void EDMA1_CH6_DriverIRQHandler(void)
{
    /* Instance 1 channel 6 */
    EDMA_DriverIRQHandler(1U, 6U);
}

/*!
 * brief DMA instance 1, channel 7 IRQ handler.
 *
 */
extern void EDMA1_CH7_DriverIRQHandler(void);
void EDMA1_CH7_DriverIRQHandler(void)
{
    /* Instance 1 channel 7 */
    EDMA_DriverIRQHandler(1U, 7U);
}

/*!
 * brief DMA instance 1, channel 8 IRQ handler.
 *
 */
extern void EDMA1_CH8_DriverIRQHandler(void);
void EDMA1_CH8_DriverIRQHandler(void)
{
    /* Instance 1 channel 8 */
    EDMA_DriverIRQHandler(1U, 8U);
}

/*!
 * brief DMA instance 1, channel 9 IRQ handler.
 *
 */
extern void EDMA1_CH9_DriverIRQHandler(void);
void EDMA1_CH9_DriverIRQHandler(void)
{
    /* Instance 1 channel 9 */
    EDMA_DriverIRQHandler(1U, 9U);
}

/*!
 * brief DMA instance 1, channel 10 IRQ handler.
 *
 */
extern void EDMA1_CH10_DriverIRQHandler(void);
void EDMA1_CH10_DriverIRQHandler(void)
{
    /* Instance 1 channel 10 */
    EDMA_DriverIRQHandler(1U, 10U);
}

/*!
 * brief DMA instance 1, channel 11 IRQ handler.
 *
 */
extern void EDMA1_CH11_DriverIRQHandler(void);
void EDMA1_CH11_DriverIRQHandler(void)
{
    /* Instance 1 channel 11 */
    EDMA_DriverIRQHandler(1U, 11U);
}

/*!
 * brief DMA instance 1, channel 12 IRQ handler.
 *
 */
extern void EDMA1_CH12_DriverIRQHandler(void);
void EDMA1_CH12_DriverIRQHandler(void)
{
    /* Instance 1 channel 12 */
    EDMA_DriverIRQHandler(1U, 12U);
}

/*!
 * brief DMA instance 1, channel 13 IRQ handler.
 *
 */
extern void EDMA1_CH13_DriverIRQHandler(void);
void EDMA1_CH13_DriverIRQHandler(void)
{
    /* Instance 1 channel 13 */
    EDMA_DriverIRQHandler(1U, 13U);
}

/*!
 * brief DMA instance 1, channel 14 IRQ handler.
 *
 */
extern void EDMA1_CH14_DriverIRQHandler(void);
void EDMA1_CH14_DriverIRQHandler(void)
{
    /* Instance 1 channel 14 */
    EDMA_DriverIRQHandler(1U, 14U);
}

/*!
 * brief DMA instance 1, channel 15 IRQ handler.
 *
 */
extern void EDMA1_CH15_DriverIRQHandler(void);
void EDMA1_CH15_DriverIRQHandler(void)
{
    /* Instance 1 channel 15 */
    EDMA_DriverIRQHandler(1U, 15U);
}
#endif
#if defined(DMA2)
/*!
 * brief DMA instance 0, channel 0 IRQ handler.
 *
 */
extern void EDMA2_CH0_DriverIRQHandler(void);
void EDMA2_CH0_DriverIRQHandler(void)
{
    /* Instance 0 channel 0 */
    EDMA_DriverIRQHandler(0U, 0U);
}

/*!
 * brief DMA instance 0, channel 1 IRQ handler.
 *
 */
extern void EDMA2_CH1_DriverIRQHandler(void);
void EDMA2_CH1_DriverIRQHandler(void)
{
    /* Instance 0 channel 1 */
    EDMA_DriverIRQHandler(0U, 1U);
}

/*!
 * brief DMA instance 0, channel 2 IRQ handler.
 *
 */
extern void EDMA2_CH2_DriverIRQHandler(void);
void EDMA2_CH2_DriverIRQHandler(void)
{
    /* Instance 0 channel 2 */
    EDMA_DriverIRQHandler(0U, 2U);
}

/*!
 * brief DMA instance 0, channel 3 IRQ handler.
 *
 */
extern void EDMA2_CH3_DriverIRQHandler(void);
void EDMA2_CH3_DriverIRQHandler(void)
{
    /* Instance 0 channel 3 */
    EDMA_DriverIRQHandler(0U, 3U);
}

/*!
 * brief DMA instance 0, channel 4 IRQ handler.
 *
 */
extern void EDMA2_CH4_DriverIRQHandler(void);
void EDMA2_CH4_DriverIRQHandler(void)
{
    /* Instance 0 channel 4 */
    EDMA_DriverIRQHandler(0U, 4U);
}

/*!
 * brief DMA instance 0, channel 5 IRQ handler.
 *
 */
extern void EDMA2_CH5_DriverIRQHandler(void);
void EDMA2_CH5_DriverIRQHandler(void)
{
    /* Instance 0 channel 5 */
    EDMA_DriverIRQHandler(0U, 5U);
}

/*!
 * brief DMA instance 0, channel 6 IRQ handler.
 *
 */
extern void EDMA2_CH6_DriverIRQHandler(void);
void EDMA2_CH6_DriverIRQHandler(void)
{
    /* Instance 0 channel 6 */
    EDMA_DriverIRQHandler(0U, 6U);
}

/*!
 * brief DMA instance 0, channel 7 IRQ handler.
 *
 */
extern void EDMA2_CH7_DriverIRQHandler(void);
void EDMA2_CH7_DriverIRQHandler(void)
{
    /* Instance 0 channel 7 */
    EDMA_DriverIRQHandler(0U, 7U);
}
#endif
#if defined(DMA3)
/*!
 * brief DMA instance 1, channel 0 IRQ handler.
 *
 */
extern void EDMA3_CH0_DriverIRQHandler(void);
void EDMA3_CH0_DriverIRQHandler(void)
{
    /* Instance 1 channel 0 */
    EDMA_DriverIRQHandler(1U, 0U);
}

/*!
 * brief DMA instance 1, channel 1 IRQ handler.
 *
 */
extern void EDMA3_CH1_DriverIRQHandler(void);
void EDMA3_CH1_DriverIRQHandler(void)
{
    /* Instance 1 channel 1 */
    EDMA_DriverIRQHandler(1U, 1U);
}

/*!
 * brief DMA instance 1, channel 2 IRQ handler.
 *
 */
extern void EDMA3_CH2_DriverIRQHandler(void);
void EDMA3_CH2_DriverIRQHandler(void)
{
    /* Instance 1 channel 2 */
    EDMA_DriverIRQHandler(1U, 2U);
}

/*!
 * brief DMA instance 1, channel 3 IRQ handler.
 *
 */
extern void EDMA3_CH3_DriverIRQHandler(void);
void EDMA3_CH3_DriverIRQHandler(void)
{
    /* Instance 1 channel 3 */
    EDMA_DriverIRQHandler(1U, 3U);
}

/*!
 * brief DMA instance 1, channel 4 IRQ handler.
 *
 */
extern void EDMA3_CH4_DriverIRQHandler(void);
void EDMA3_CH4_DriverIRQHandler(void)
{
    /* Instance 1 channel 4 */
    EDMA_DriverIRQHandler(1U, 4U);
}

/*!
 * brief DMA instance 1, channel 5 IRQ handler.
 *
 */
extern void EDMA3_CH5_DriverIRQHandler(void);
void EDMA3_CH5_DriverIRQHandler(void)
{
    /* Instance 1 channel 5 */
    EDMA_DriverIRQHandler(1U, 5U);
}

/*!
 * brief DMA instance 1, channel 6 IRQ handler.
 *
 */
extern void EDMA3_CH6_DriverIRQHandler(void);
void EDMA3_CH6_DriverIRQHandler(void)
{
    /* Instance 1 channel 6 */
    EDMA_DriverIRQHandler(1U, 6U);
}

/*!
 * brief DMA instance 1, channel 7 IRQ handler.
 *
 */
extern void EDMA3_CH7_DriverIRQHandler(void);
void EDMA3_CH7_DriverIRQHandler(void)
{
    /* Instance 1 channel 7 */
    EDMA_DriverIRQHandler(1U, 7U);
}
#endif
