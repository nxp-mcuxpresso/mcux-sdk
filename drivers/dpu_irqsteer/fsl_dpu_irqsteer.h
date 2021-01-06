/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DPU_IRQSTEER_H_
#define _FSL_DPU_IRQSTEER_H_

#include "fsl_common.h"

/*!
 * @addtogroup dpu_irqsteer
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dpu_irqsteer"
#endif

/*! @name Driver version */
/*@{*/
#define FSL_DPU_IRQSTEER_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/* Convert the IRQn to IRQSTEER channel number. */
#define DPU_IRQSTEER_INT_SRC_REG_INDEX(irq) (FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT - 1U - (((uint32_t)(irq)) >> 5U))

/* Convert the IRQn to control bit index in IRQSTEER channel. */
#define DPU_IRQSTEER_INT_SRC_BIT_OFFSET(irq) (((uint32_t)(irq)) & 0x1FU)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables an interrupt source.
 *
 * @param base DPU IRQSTEER peripheral base address.
 * @param irq Interrupt to be enabled.
 */
static inline void DPU_IRQSTEER_EnableInterrupt(IRQSTEER_Type *base, DPU_IRQSTEER_IRQn_Type irq)
{
    base->CHn_MASK[DPU_IRQSTEER_INT_SRC_REG_INDEX(irq)] |= (1U << ((uint32_t)DPU_IRQSTEER_INT_SRC_BIT_OFFSET(irq)));
}

/*!
 * @brief Disables an interrupt source.
 *
 * @param base DPU IRQSTEER peripheral base address.
 * @param irq Interrupt to be disabled.
 */
static inline void DPU_IRQSTEER_DisableInterrupt(IRQSTEER_Type *base, DPU_IRQSTEER_IRQn_Type irq)
{
    base->CHn_MASK[DPU_IRQSTEER_INT_SRC_REG_INDEX(irq)] &= ~(1U << ((uint32_t)DPU_IRQSTEER_INT_SRC_BIT_OFFSET(irq)));
}

/*!
 * @brief Checks the status of one specific DPU IRQSTEER interrupt.
 *
 * @param base DPU IRQSTEER peripheral base address.
 * @param irq Interrupt source status to be checked. The interrupt must be an IRQSTEER source.
 * @return The interrupt status. "true" means interrupt set. "false" means not.
 */
static inline bool DPU_IRQSTEER_IsInterruptSet(IRQSTEER_Type *base, DPU_IRQSTEER_IRQn_Type irq)
{
    if ((base->CHn_STATUS[DPU_IRQSTEER_INT_SRC_REG_INDEX(irq)] &
         (1U << ((uint32_t)DPU_IRQSTEER_INT_SRC_BIT_OFFSET(irq)))) != 0U)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DPU_IRQSTEER_H_ */
