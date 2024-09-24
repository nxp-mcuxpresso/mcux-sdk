/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gdet.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gdet"
#endif

#define ISOLATE_ON  (0x2u << 2u)
#define ISOLATE_OFF (0x3u << 2u)

#define SYSCON_GDET_ISOLATION_SW_MASK (0xCu)

/* Array of GDET peripheral base address */
static const GDET_Type *s_gdetBases[] = GDET_BASE_PTRS;

/* Array of GDET peripheral clocks */
static const clock_ip_name_t s_gdetClocks[] = GDET_CLOCKS;

#if defined(GDET_REF_CLOCKS)
/* Array of GDET peripheral clocks */
static const clock_ip_name_t s_gdetRefClocks[] = GDET_REF_CLOCKS;
#endif

/* Array of GDET peripheral IRQs */
static const IRQn_Type s_gdetIrqs[] = GDET_IRQS;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t GDET_GetInstance(GDET_Type *base);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Get the GDET instance from peripheral base address.
 *
 * param base GDET peripheral base address.
 * return GDET instance.
 */
static uint32_t GDET_GetInstance(GDET_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_gdetBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_gdetBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_gdetBases));

    return instance;
}

/*!
 * brief Initialize GDET
 *
 * This function initializes GDET clocks.
 *
 * param base GDET peripheral base address
 * return Status of the init operation
 */
status_t GDET_Init(GDET_Type *base)
{
    /* Ungate clock to GDET engine */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_gdetClocks[GDET_GetInstance(base)]);
#if defined(GDET_REF_CLOCKS)
    CLOCK_EnableClock(s_gdetRefClocks[GDET_GetInstance(base)]);
#endif /* GDET_REF_CLOCKS */
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    return kStatus_Success;
}

/*!
 * brief Deinitialize GDET
 *
 * This function stops GDET clocs.
 *
 * param base GDET peripheral base address
 */
void GDET_Deinit(GDET_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_gdetClocks[GDET_GetInstance(base)]);
#if defined(GDET_REF_CLOCKS)
    CLOCK_DisableClock(s_gdetRefClocks[GDET_GetInstance(base)]);
#endif /* GDET_REF_CLOCKS */
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Enable GDET
 *
 * This function enables GDET and interrupts.
 *
 * param base GDET peripheral base address
 * return Status of the enable operation
 */
status_t GDET_Enable(GDET_Type *base)
{
    base->GDET_ENABLE1 = GDET_GDET_ENABLE1_EN1(1u);
    NVIC_EnableIRQ(s_gdetIrqs[GDET_GetInstance(base)]);

    return kStatus_Success;
}

/*!
 * brief Disable GDET
 *
 * This function disables GDET and interrupts.
 *
 * param base GDET peripheral base address
 * return Status of the disable operation
 */
status_t GDET_Disable(GDET_Type *base)
{
    base->GDET_ENABLE1 = GDET_GDET_ENABLE1_EN1(0u);
    NVIC_DisableIRQ(s_gdetIrqs[GDET_GetInstance(base)]);

    return kStatus_Success;
}

/*!
 * brief Turn on GDET isolation
 *
 * This function turns on isolation of GDET peripheral
 *
 * param base GDET peripheral base address
 */
status_t GDET_IsolateOn(GDET_Type *base)
{
    status_t status = kStatus_Fail;
    uint32_t instance;
    uint32_t syscon_tmp = 0u;

    instance = GDET_GetInstance(base);
#if defined(SYSCON0_GDET_CTRL_GDET_ISO_SW_MASK)
    if (instance < 2u)
    {
        syscon_tmp = SYSCON0->GDET_CTRL[instance] & ~(SYSCON_GDET_ISOLATION_SW_MASK);
        syscon_tmp |= ISOLATE_ON;
        SYSCON0->GDET_CTRL[instance] = syscon_tmp;

        if ((SYSCON0->GDET_CTRL[instance] & SYSCON_GDET_ISOLATION_SW_MASK) != ISOLATE_ON)
        {
            return kStatus_Fail;
        }
    }
#elif defined(SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK)
    if (instance >= 2u && instance < 4u)
    {
        syscon_tmp = SYSCON3->GDET_CTRL[instance - 2u] & ~(SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK);
        syscon_tmp |= ISOLATE_ON;
        SYSCON3->GDET_CTRL[instance - 2u] = syscon_tmp;

        if ((SYSCON3->GDET_CTRL[instance - 2u] & SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK) != ISOLATE_ON)
        {
            return kStatus_Fail;
        }
    }
#endif /* SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK */
    else
    {
        return kStatus_Fail;
    }
    status = kStatus_Success;

    return status;
}

/*!
 * brief Turn off GDET isolation
 *
 * This function turns off isolation of GDET peripheral
 *
 * param base GDET peripheral base address
 */
status_t GDET_IsolateOff(GDET_Type *base)
{
    status_t status = kStatus_Fail;
    uint32_t instance;
    uint32_t syscon_tmp = 0u;

    instance = GDET_GetInstance(base);
#if defined(SYSCON0_GDET_CTRL_GDET_ISO_SW_MASK)
    if (instance < 2u)
    {
        syscon_tmp = SYSCON0->GDET_CTRL[instance] & ~(SYSCON_GDET_ISOLATION_SW_MASK);
        syscon_tmp |= ISOLATE_OFF;
        SYSCON0->GDET_CTRL[instance] = syscon_tmp;

        if ((SYSCON0->GDET_CTRL[instance] & SYSCON_GDET_ISOLATION_SW_MASK) != ISOLATE_OFF)
        {
            return kStatus_Fail;
        }
    }
#elif defined(SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK)
    if (instance >= 2u && instance < 4u)
    {
        syscon_tmp = SYSCON3->GDET_CTRL[instance - 2u] & ~(SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK);
        syscon_tmp |= ISOLATE_OFF;
        SYSCON3->GDET_CTRL[instance - 2u] = syscon_tmp;

        if ((SYSCON3->GDET_CTRL[instance - 2u] & SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK) != ISOLATE_OFF)
        {
            return kStatus_Fail;
        }
    }
#endif /* SYSCON3_GDET_CTRL_GDET_ISO_SW_MASK */
    else
    {
        return kStatus_Fail;
    }

    status = kStatus_Success;

    return status;
}

/*!
 * brief Change expected core voltage
 *
 * This function changes core voltage which Glitch detector expect.
 *
 * param base GDET peripheral base address
 * param voltage Expected core voltage
 * return Status of the GDET reconfiguration operation
 */
status_t GDET_ReconfigureVoltageMode(GDET_Type *base, gdet_core_voltage_t voltage)
{
    uint32_t tmp0   = 0;
    status_t status = kStatus_Fail;

    /* Change the GDET_DLY_CTRL to select the new drive mode (and set high also GDET_DLY_CTRL[SW_VOL_CTRL] for a SW
     * control)*/
    tmp0 = (((uint32_t)voltage) << GDET_GDET_DLY_CTRL_VOL_SEL_SHIFT);
    tmp0 |= GDET_GDET_DLY_CTRL_SW_VOL_CTRL_MASK;
    base->GDET_DLY_CTRL = tmp0;

#if defined(GDET_GDET_RESET_SFT_RST)
    /* Write high the GDET_RESET[SFT_RST] to issue a fast update of the detector to the new voltage level.*/
    base->GDET_RESET = GDET_GDET_RESET_SFT_RST(1u);

    /* according to the GDET module documentation, the GDET_CFG[SFT_RST] reads as 0 */
    if (0u == (GDET_GDET_RESET_SFT_RST_MASK & base->GDET_RESET))
    {
        status = kStatus_Success;
    }
#elif defined(GDET_GDET_CTRL_CLR_SFT_RST)
    /* Write high the GDET_RESET[SFT_RST] to issue a fast update of the detector to the new voltage level.*/
    base->GDET_CTRL_CLR = GDET_GDET_CTRL_CLR_SFT_RST(1u);

    /* according to the GDET module documentation, the GDET_CTRL_CLR[SFT_RST] reads as 0 */
    if (0u == (GDET_GDET_CTRL_CLR_SFT_RST_MASK & base->GDET_CTRL_CLR))
    {
        status = kStatus_Success;
    }
#endif

    return status;
}
