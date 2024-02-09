/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_irqsteer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.irqsteer"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for IRQSTEER.
 *
 * @param base IRQSTEER peripheral base address.
 */
static uint32_t IRQSTEER_GetInstance(IRQSTEER_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map IRQSTEER instance number to base pointer. */
static IRQSTEER_Type *const s_irqsteerBases[] = IRQSTEER_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map IRQSTEER instance number to clock name. */
static const clock_ip_name_t s_irqsteerClockName[] = IRQSTEER_CLOCKS;
#endif

#if FSL_IRQSTEER_ENABLE_MASTER_INT
/*! @brief Array to map IRQSTEER instance number to IRQ number. */
static const IRQn_Type s_irqsteerIRQNumber[] = IRQSTEER_IRQS;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t IRQSTEER_GetInstance(IRQSTEER_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_irqsteerBases); instance++)
    {
        if (s_irqsteerBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_irqsteerBases));

    return instance;
}

/*!
 * brief Initializes the IRQSTEER module.
 *
 * This function enables the clock gate for the specified IRQSTEER.
 *
 * param base IRQSTEER peripheral base address.
 */
void IRQSTEER_Init(IRQSTEER_Type *base)
{
    uint32_t i;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable clock. */
    (void)CLOCK_EnableClock(s_irqsteerClockName[IRQSTEER_GetInstance(base)]);
#endif
    /* Mask all interrupts. */
    for (i = 0; i < (uint32_t)FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT; i++)
    {
        base->CHn_MASK[i] &= ~IRQSTEER_CHn_MASK_MASKFLD_MASK;
    }

#if FSL_IRQSTEER_ENABLE_MASTER_INT
    /* Enable NVIC vectors for all IRQSTEER master. */
    for (i = 0; i < (uint32_t)FSL_FEATURE_IRQSTEER_MASTER_COUNT; i++)
    {
        (void)EnableIRQ(s_irqsteerIRQNumber[i]);
    }
#endif
}

/*!
 * brief Deinitializes an IRQSTEER instance for operation.
 *
 * The clock gate for the specified IRQSTEER is disabled.
 *
 * param base IRQSTEER peripheral base address.
 */
void IRQSTEER_Deinit(IRQSTEER_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock. */
    (void)CLOCK_DisableClock(s_irqsteerClockName[IRQSTEER_GetInstance(base)]);
#endif

#if FSL_IRQSTEER_ENABLE_MASTER_INT
    uint32_t master;

    /* Disable NVIC vectors for all IRQSTEER master. */
    for (master = 0; master < (uint32_t)FSL_FEATURE_IRQSTEER_MASTER_COUNT; master++)
    {
        (void)DisableIRQ(s_irqsteerIRQNumber[master]);
    }
#endif
}

/*
 * brief Get the number of interrupt for a given master.
 *
 * param base IRQSTEER peripheral base address.
 * param intMasterIndex Master index of interrupt sources, options available in
 * enumeration ::irqsteer_int_master_t.
 * return Number of interrupts for a given master.
 */
uint32_t IRQSTEER_GetMasterIrqCount(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    uint32_t count;

    /*
     * With IRQSTEER, each interrupt group has 32 interrupt sources. How many
     * interrupt groups are connected to one interrupt master, it relates to
     * the SOC integration.
     *
     * There are two cases based on SOC integration:
     *
     * 1. The interrupt group count (number of CHn_MASKx registers) is even number.
     *    In this case, every two interrupt groups are connected to one interrupt master.
     *    So each master has 64 interrupt sources connected.
     * 2. The interrupt group count (number of CHn_MASKx registers) is odd number.
     *    In this case, master 0 is connected to one interrupt group, while other masters
     *    are all connected to two interrupt groups.
     *    So each master 0 has 32 interrupt sources connected, and for other masters,
     *    every master has 64 interrupt sources connected.
     */
    if ((FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT % 2U) == 0U)
    {
        count = IRQSTEER_INT_MASTER_AGGREGATED_INT_NUM;
    }
    else
    {
        if (intMasterIndex == 0U)
        {
            count = IRQSTEER_INT_SRC_REG_WIDTH;
        }
        else
        {
            count = IRQSTEER_INT_MASTER_AGGREGATED_INT_NUM;
        }
    }

    return count;
}

static uint32_t IRQSTEER_GetRegIndex(irqsteer_int_master_t intMasterIndex, uint32_t slice)
{
    uint32_t base = FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT - 1 - intMasterIndex * 2;

    if (FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT % 2) {
        return base + slice;
    } else {
        return base - slice;
    }
}

/*!
 * brief Gets the next interrupt source (currently set) of one specific master.
 *
 * param base IRQSTEER peripheral base address.
 * param intMasterIndex Master index of interrupt sources. ref "irqsteer_int_master_t".
 * return The current set next interrupt source number of one specific master.
 *         Return IRQSTEER_INT_Invalid if no interrupt set.
 */
#if defined(__CORTEX_M)
IRQn_Type IRQSTEER_GetMasterNextInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    uint32_t regIndex = (uint32_t)FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT - 1U - ((uint32_t)intMasterIndex) * 2U;
    uint32_t bitOffset;
    uint32_t irqNum;

    bitOffset = __CLZ(__RBIT(base->CHn_STATUS[regIndex]));
    /* When no result found, continue the loop to parse the next CHn_STATUS register. */
    if (IRQSTEER_INT_SRC_REG_WIDTH == bitOffset)
    {
        regIndex--;
        bitOffset = __CLZ(__RBIT(base->CHn_STATUS[regIndex]));
    }

    if (IRQSTEER_INT_SRC_REG_WIDTH == bitOffset)
    {
        return NotAvail_IRQn;
    }
    else
    {
        irqNum = (uint32_t)IRQSTEER_INT_SRC_NUM(regIndex, bitOffset) + (uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX;
        return (IRQn_Type)irqNum;
    }
}
#else  /* **not** __CORTEX_M */
IRQn_Type IRQSTEER_GetMasterNextInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    uint32_t bitOffset, regIndex, chanStatus, sliceNum;
    int i, j;

    sliceNum = IRQSTEER_GetMasterIrqCount(base, intMasterIndex) / 32 - 1;

    for (i = 0; i <= sliceNum; i++)
    {
        bitOffset = 0;

        /* compute the index of the register to be queried */
        regIndex = IRQSTEER_GetRegIndex(intMasterIndex, i);

        /* get register's value */
        chanStatus = base->CHn_STATUS[regIndex];

        for (j = 0; j < IRQSTEER_INT_SRC_REG_WIDTH; j++)
        {
            if ((chanStatus & 1U) != 0U)
            {
                return (IRQn_Type)(uint32_t)IRQSTEER_INT_SRC_NUM(regIndex, bitOffset);
            }

            bitOffset++;
            chanStatus = chanStatus >> 1U;
        }
    }

    return NotAvail_IRQn;
}
#endif /* __CORTEX_M */

uint64_t IRQSTEER_GetMasterInterruptsStatus(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    uint32_t sliceNum, i, regIndex, chanStatus;
    uint64_t interrupts;

    interrupts = 0;
    sliceNum = IRQSTEER_GetMasterIrqCount(base, intMasterIndex) / 32 - 1;

    for (i = 0; i <= sliceNum; i++) {
        regIndex = IRQSTEER_GetRegIndex(intMasterIndex, i);

        chanStatus = base->CHn_STATUS[regIndex];

        interrupts |= ((uint64_t)chanStatus << (32 * i));
    }

    return interrupts;
}

#if FSL_IRQSTEER_USE_DRIVER_IRQ_HANDLER
static void IRQSTEER_CommonIRQHandler(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    IRQn_Type intSource;
    uint32_t isr;

    intSource = IRQSTEER_GetMasterNextInterrupt(base, intMasterIndex);
    if (NotAvail_IRQn != intSource)
    {
        isr = *(uint32_t *)(SCB->VTOR + (((uint32_t)intSource + 16UL) << 2U));

        ((void (*)(void))isr)();
    }
#if defined(FSL_FEATURE_EDMA_IRQSTEER_INTERRUPT_PATCH)
    /*This is used for ESAI Interrupt IRQSTEER triggering*/
    else
    {
        if ((intMasterIndex == 6) && ((base->CHn_MASK[2]) & 0x10))
        {
            isr = *(uint32_t *)(SCB->VTOR + (((uint32_t)ADMA_ESAI0_INT_IRQn + 16UL) << 2U));
            ((void (*)(void))isr)();
        }
    }
#endif
    SDK_ISR_EXIT_BARRIER;
}

#if defined(IRQSTEER)
void IRQSTEER_0_DriverIRQHandler(void);
void IRQSTEER_0_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster0);
}

void IRQSTEER_1_DriverIRQHandler(void);
void IRQSTEER_1_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster1);
}

void IRQSTEER_2_DriverIRQHandler(void);
void IRQSTEER_2_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster2);
}

void IRQSTEER_3_DriverIRQHandler(void);
void IRQSTEER_3_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster3);
}

void IRQSTEER_4_DriverIRQHandler(void);
void IRQSTEER_4_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster4);
}

void IRQSTEER_5_DriverIRQHandler(void);
void IRQSTEER_5_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster5);
}

void IRQSTEER_6_DriverIRQHandler(void);
void IRQSTEER_6_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster6);
}

void IRQSTEER_7_DriverIRQHandler(void);
void IRQSTEER_7_DriverIRQHandler(void)
{
    IRQSTEER_CommonIRQHandler(IRQSTEER, kIRQSTEER_InterruptMaster7);
}
#endif /* defined(IRQSTEER) */
#endif /* FSL_IRQSTEER_USE_DRIVER_IRQ_HANDLER */
