/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_msgintr.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.msgintr"
#endif

#ifndef MSGINTR_IRQS
#define MSGINTR_IRQS                                                                                            \
    {                                                                                                           \
        NotAvail_IRQn, MSGINTR1_IRQn, MSGINTR2_IRQn, MSGINTR3_IRQn, MSGINTR4_IRQn, MSGINTR5_IRQn, MSGINTR6_IRQn \
    }
#endif

/*! @brief Pointers to MSGINTR bases for each instance. */
static MSGINTR_Type *const s_msgintrBases[] = MSGINTR_BASE_PTRS;

/*! @brief Pointers to MSGINTR IRQ number for each instance. */
static const IRQn_Type s_msgintrIrqId[] = MSGINTR_IRQS;

/*! @brief Pointers to MSGINTR callbacks for each instance. */
static msgintr_cb_t s_msgintrCallback[ARRAY_SIZE(s_msgintrBases)] = {0};

static uint32_t MSGINTR_GetInstance(MSGINTR_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_msgintrBases); instance++)
    {
        if (s_msgintrBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_msgintrBases));

    return instance;
}

status_t MSGINTR_Init(MSGINTR_Type *base, msgintr_cb_t callback)
{
    uint32_t instance = MSGINTR_GetInstance(base);

    (void)EnableIRQ(s_msgintrIrqId[instance]);
    s_msgintrCallback[instance] = callback;

    return kStatus_Success;
}

status_t MSGINTR_Deinit(MSGINTR_Type *base)
{
    uint32_t instance = MSGINTR_GetInstance(base);

    (void)DisableIRQ(s_msgintrIrqId[instance]);
    s_msgintrCallback[instance] = NULL;

    /* Read and clean the pending bits. */
    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        (void)base->MSI[channel].MSIR;
    }

    return kStatus_Success;
}

#if defined(MSGINTR1)
void MSGINTR1_IRQHandler(void);
void MSGINTR1_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR1->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[1] != NULL))
        {
            s_msgintrCallback[1](MSGINTR1, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(MSGINTR2)
void MSGINTR2_IRQHandler(void);
void MSGINTR2_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR2->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[2] != NULL))
        {
            s_msgintrCallback[2](MSGINTR2, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(MSGINTR3)
void MSGINTR3_IRQHandler(void);
void MSGINTR3_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR2->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[3] != NULL))
        {
            s_msgintrCallback[3](MSGINTR3, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(MSGINTR4)
void MSGINTR4_IRQHandler(void);
void MSGINTR4_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR2->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[4] != NULL))
        {
            s_msgintrCallback[4](MSGINTR4, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(MSGINTR5)
void MSGINTR5_IRQHandler(void);
void MSGINTR5_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR2->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[5] != NULL))
        {
            s_msgintrCallback[5](MSGINTR5, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(MSGINTR6)
void MSGINTR6_IRQHandler(void);
void MSGINTR6_IRQHandler(void)
{
    uint32_t pendingIntr;

    for (uint8_t channel = 0; channel < FSL_MSGINTR_CHANNEL_NUM; channel++)
    {
        pendingIntr = MSGINTR2->MSI[channel].MSIR;
        if ((pendingIntr != 0U) && (s_msgintrCallback[6] != NULL))
        {
            s_msgintrCallback[6](MSGINTR6, channel, pendingIntr);
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
