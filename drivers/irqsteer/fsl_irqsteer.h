/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_IRQSTEER_H_
#define _FSL_IRQSTEER_H_

#include "fsl_common.h"

/*!
 * @addtogroup irqsteer
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*!< Version 2.0.2. */
#define FSL_IRQSTEER_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

/*! @brief IRQSTEER interrupt source register width. */
#define IRQSTEER_INT_SRC_REG_WIDTH 32U

/*! @brief IRQSTEER interrupt source mapping register index. */
#define IRQSTEER_INT_SRC_REG_INDEX(irq)                     \
    (((uint32_t)FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT - 1U) - \
     ((irq - (uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX) / IRQSTEER_INT_SRC_REG_WIDTH))

/*! @brief IRQSTEER interrupt source mapping bit offset. */
#define IRQSTEER_INT_SRC_BIT_OFFSET(irq) \
    ((irq - (uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX) % IRQSTEER_INT_SRC_REG_WIDTH)

/*! @brief IRQSTEER interrupt source number. */
#define IRQSTEER_INT_SRC_NUM(regIndex, bitOffset) \
    ((((uint32_t)FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT - 1U - (regIndex)) * (IRQSTEER_INT_SRC_REG_WIDTH)) + (bitOffset))

/*! @brief IRQSTEER interrupt groups. */
typedef enum _irqsteer_int_group
{
    kIRQSTEER_InterruptGroup0,  /*!< Interrupt Group 0: interrupt source 31 - 0 */
    kIRQSTEER_InterruptGroup1,  /*!< Interrupt Group 1: interrupt source 63 - 32 */
    kIRQSTEER_InterruptGroup2,  /*!< Interrupt Group 2: interrupt source 95 - 64 */
    kIRQSTEER_InterruptGroup3,  /*!< Interrupt Group 3: interrupt source 127 - 96 */
    kIRQSTEER_InterruptGroup4,  /*!< Interrupt Group 4: interrupt source 159 - 128 */
    kIRQSTEER_InterruptGroup5,  /*!< Interrupt Group 5: interrupt source 191 - 160 */
    kIRQSTEER_InterruptGroup6,  /*!< Interrupt Group 6: interrupt source 223 - 192 */
    kIRQSTEER_InterruptGroup7,  /*!< Interrupt Group 7: interrupt source 255 - 224 */
    kIRQSTEER_InterruptGroup8,  /*!< Interrupt Group 8: interrupt source 287 - 256 */
    kIRQSTEER_InterruptGroup9,  /*!< Interrupt Group 9: interrupt source 319 - 288 */
    kIRQSTEER_InterruptGroup10, /*!< Interrupt Group 10: interrupt source 351 - 320 */
    kIRQSTEER_InterruptGroup11, /*!< Interrupt Group 11: interrupt source 383 - 352 */
    kIRQSTEER_InterruptGroup12, /*!< Interrupt Group 12: interrupt source 415 - 384 */
    kIRQSTEER_InterruptGroup13, /*!< Interrupt Group 13: interrupt source 447 - 416 */
    kIRQSTEER_InterruptGroup14, /*!< Interrupt Group 14: interrupt source 479 - 448 */
    kIRQSTEER_InterruptGroup15  /*!< Interrupt Group 15: interrupt source 511 - 480 */
} irqsteer_int_group_t;

/*! @brief IRQSTEER master interrupts mapping. */
typedef enum _irqsteer_int_master
{
    kIRQSTEER_InterruptMaster0, /*!< Interrupt Master 0: interrupt source 63 - 0 */
    kIRQSTEER_InterruptMaster1, /*!< Interrupt Master 1: interrupt source 127 - 64 */
    kIRQSTEER_InterruptMaster2, /*!< Interrupt Master 2: interrupt source 191 - 128 */
    kIRQSTEER_InterruptMaster3, /*!< Interrupt Master 3: interrupt source 255 - 192 */
    kIRQSTEER_InterruptMaster4, /*!< Interrupt Master 4: interrupt source 319 - 256 */
    kIRQSTEER_InterruptMaster5, /*!< Interrupt Master 5: interrupt source 383 - 320 */
    kIRQSTEER_InterruptMaster6, /*!< Interrupt Master 6: interrupt source 447 - 384 */
    kIRQSTEER_InterruptMaster7, /*!< Interrupt Master 7: interrupt source 511 - 448 */
} irqsteer_int_master_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name Initialization and deinitialization */
/*@{*/

/*!
 * @brief Initializes the IRQSTEER module.
 *
 * This function enables the clock gate for the specified IRQSTEER.
 *
 * @param base IRQSTEER peripheral base address.
 */
void IRQSTEER_Init(IRQSTEER_Type *base);

/*!
 * @brief Deinitializes an IRQSTEER instance for operation.
 *
 * The clock gate for the specified IRQSTEER is disabled.
 *
 * @param base IRQSTEER peripheral base address.
 */
void IRQSTEER_Deinit(IRQSTEER_Type *base);

/*@}*/

/*! @name Sources */
/*@{*/

/*!
 * @brief Enables an interrupt source.
 *
 * @param base IRQSTEER peripheral base address.
 * @param irq Interrupt to be routed. The interrupt must be an IRQSTEER source.
 */
static inline void IRQSTEER_EnableInterrupt(IRQSTEER_Type *base, IRQn_Type irq)
{
    assert((uint32_t)irq >= (uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX);

    base->CHn_MASK[((uint32_t)IRQSTEER_INT_SRC_REG_INDEX(((uint32_t)irq)))] |=
        (1UL << ((uint32_t)IRQSTEER_INT_SRC_BIT_OFFSET(((uint32_t)irq))));
}

/*!
 * @brief Disables an interrupt source.
 *
 * @param base IRQSTEER peripheral base address.
 * @param irq Interrupt source number. The interrupt must be an IRQSTEER source.
 */
static inline void IRQSTEER_DisableInterrupt(IRQSTEER_Type *base, IRQn_Type irq)
{
    assert(((uint32_t)irq) >= ((uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX));

    base->CHn_MASK[(IRQSTEER_INT_SRC_REG_INDEX(((uint32_t)irq)))] &=
        ~(1UL << ((uint32_t)IRQSTEER_INT_SRC_BIT_OFFSET(((uint32_t)irq))));
}

/*!
 * @brief Sets/Forces an interrupt.
 *
 * @param base IRQSTEER peripheral base address.
 * @param irq Interrupt to be set/forced. The interrupt must be an IRQSTEER source.
 * @param set Switcher of the interrupt set/force function. "true" means to set. "false" means not (normal operation).
 * @note This function is not affected by the function @ref IRQSTEER_DisableInterrupt
 * and @ref IRQSTEER_EnableInterrupt.
 */
static inline void IRQSTEER_SetInterrupt(IRQSTEER_Type *base, IRQn_Type irq, bool set)
{
    assert(((uint32_t)irq) >= ((uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX));

    if (set)
    {
        base->CHn_SET[((uint32_t)IRQSTEER_INT_SRC_REG_INDEX(((uint32_t)irq)))] |=
            (1UL << ((uint32_t)IRQSTEER_INT_SRC_BIT_OFFSET(((uint32_t)irq))));
    }
    else
    {
        base->CHn_SET[((uint32_t)IRQSTEER_INT_SRC_REG_INDEX(((uint32_t)irq)))] &=
            ~(1UL << ((uint32_t)IRQSTEER_INT_SRC_BIT_OFFSET(((uint32_t)irq))));
    }
}

/*!
 * @brief Enables a master interrupt. By default, all the master interrupts are enabled.
 *
 * @param base IRQSTEER peripheral base address.
 * @param intMasterIndex Master index of interrupt sources to be routed, options available in enumeration
 * ::irqsteer_int_master_t.
 *
 * For example, to enable the interrupt sources of master 1:
 * @code
 *     IRQSTEER_EnableMasterInterrupt(IRQSTEER_M4_0, kIRQSTEER_InterruptMaster1);
 * @endcode
 */
static inline void IRQSTEER_EnableMasterInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    base->CHn_MINTDIS &= ~(1UL << ((uint32_t)intMasterIndex));
}

/*!
 * @brief Disables a master interrupt.
 *
 * @param base IRQSTEER peripheral base address.
 * @param intMasterIndex Master index of interrupt sources to be disabled, options available in enumeration
 * ::irqsteer_int_master_t.
 *
 * For example, to disable the interrupt sources of master 1:
 * @code
 *     IRQSTEER_DisableMasterInterrupt(IRQSTEER_M4_0, kIRQSTEER_InterruptMaster1);
 * @endcode
 */
static inline void IRQSTEER_DisableMasterInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex)
{
    base->CHn_MINTDIS |= (1UL << ((uint32_t)intMasterIndex));
}

/*@}*/

/*! @name Status */
/*@{*/

/*!
 * @brief Checks the status of one specific IRQSTEER interrupt.
 *
 * @param base IRQSTEER peripheral base address.
 * @param irq Interrupt source status to be checked. The interrupt must be an IRQSTEER source.
 * @return The interrupt status. "true" means interrupt set. "false" means not.
 *
 * For example, to check whether interrupt from output 0 of Display 1 is set:
 * @code
 *     if (IRQSTEER_IsInterruptSet(IRQSTEER_DISPLAY1_INT_OUT0)
 *     {
 *         ...
 *     }
 * @endcode
 */
static inline bool IRQSTEER_IsInterruptSet(IRQSTEER_Type *base, IRQn_Type irq)
{
    assert(((uint32_t)irq) >= ((uint32_t)FSL_FEATURE_IRQSTEER_IRQ_START_INDEX));

    return (bool)(base->CHn_STATUS[((uint32_t)(IRQSTEER_INT_SRC_REG_INDEX(((uint32_t)irq))))] &
                  (1UL << ((uint32_t)(IRQSTEER_INT_SRC_BIT_OFFSET(((uint32_t)irq))))));
}

/*!
 * @brief Checks the status of IRQSTEER master interrupt.
 *        The master interrupt status represents at least one interrupt is asserted or not among ALL interrupts.
 *
 * @param base IRQSTEER peripheral base address.
 * @return The master interrupt status. "true" means at least one interrupt set. "false" means not.
 * @note The master interrupt status is not affected by the function @ref IRQSTEER_DisableMasterInterrupt.
 */
static inline bool IRQSTEER_IsMasterInterruptSet(IRQSTEER_Type *base)
{
    return (bool)(base->CHn_MSTRSTAT & IRQSTEER_CHn_MSTRSTAT_STATUS_MASK);
}

/*!
 * @brief Gets the status of IRQSTEER group interrupt.
 *        The group interrupt status represents all the interrupt status within the group specified.
 *        This API aims for facilitating the status return of one set of interrupts.
 *
 * @param base IRQSTEER peripheral base address.
 * @param intGroupIndex Index of the interrupt group status to get.
 * @return The mask of the group interrupt status.
 *         Bit[n] set means the source with bit offset n in group intGroupIndex of IRQSTEER is asserted.
 */
static inline uint32_t IRQSTEER_GetGroupInterruptStatus(IRQSTEER_Type *base, irqsteer_int_group_t intGroupIndex)
{
    return (base->CHn_STATUS[intGroupIndex]);
}

/*!
 * @brief Gets the next interrupt source (currently set) of one specific master.
 *
 * @param base IRQSTEER peripheral base address.
 * @param intMasterIndex Master index of interrupt sources, options available in enumeration ::irqsteer_int_master_t.
 * @return The current set next interrupt source number of one specific master.
 *         Return IRQSTEER_INT_Invalid if no interrupt set.
 */
IRQn_Type IRQSTEER_GetMasterNextInterrupt(IRQSTEER_Type *base, irqsteer_int_master_t intMasterIndex);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_INTMUX_H_ */
