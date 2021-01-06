/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mmau.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mmau"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Set control/status register into reset state.
 *
 * This function sets control/status register to a known state. This state is
 * defined in Reference Manual, which is power on reset value. This function must
 * execute in a Supervisor Mode
 * param base MMAU peripheral address.
 */
void MMAU_Reset(MMAU_Type *base)
{
    /* Reset all MMAU register */
    base->X0         = 0U;
    base->X1         = 0U;
    base->X2         = 0U;
    base->X3         = 0U;
    base->A0         = 0U;
    base->A1         = 0U;
    base->CSR        = 0U;
    base->CSR_IF_CLR = 0U;
}

/*!
 * brief Clears interrupt flags.
 *
 * This function clears the interrupt flags.
 * Example, if you want to clear Overflow and DivideByZero interrupt flags:
   code
   MMAU_ClearInterruptFlags(MMAU, kMMAU_OverflowInterruptFlag|kMMAU_DivideByZeroInterruptFlag);
   endcode
 *
 * param base MMAU peripheral address.
 * param mask Mask of the asserted interrupt flags
 *          (kMMAU_AccumOverflowInterruptFlag|kMMAU_OverflowInterruptFlag|kMMAU_DivideByZeroInterruptFlag).
 */
void MMAU_ClearInterruptFlags(MMAU_Type *base, uint32_t mask)
{
    uint32_t regVal;

    /* Assign regVal to MMAU_CSR_IF_CLR register's value */
    regVal = base->CSR_IF_CLR;
    /* Perform this command to avoid writing 1 into interrupt flag bits, which do not corresponding to the mask */
    regVal &= (uint32_t)(~((uint32_t)kMMAU_AccumOverflowInterruptFlag | (uint32_t)kMMAU_OverflowInterruptFlag |
                           (uint32_t)kMMAU_DivideByZeroInterruptFlag));
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= mask & ((uint32_t)kMMAU_AccumOverflowInterruptFlag | (uint32_t)kMMAU_OverflowInterruptFlag |
                      (uint32_t)kMMAU_DivideByZeroInterruptFlag);
    /* Write regVal's value into MMAU_CSR_IF_CLR register */
    base->CSR_IF_CLR = regVal;
}

/*!
 * brief Sets the instruction flags.
 *
 * This function sets the instruction flags.
 * Example:
   code
   MMAU_SetInstructionFlags(MMAU, kMMAU_AccumOverflowInstructionFlag | kMMAU_NegativeInstructionFlag);
   MMAU_SetInstructionFlags(MMAU, kMMAU_OverflowInstructionFlag | kMMAU_DivideByZeroInstructionFlag);
   endcode
 *
 * param base MMAU peripheral address.
 * param mask Mask of the instruction flags to be written
 *
 (kMMAU_AccumOverflowInstructionFlag|kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag|kMMAU_NegativeInstructionFlag).
 */
void MMAU_SetInstructionFlags(MMAU_Type *base, uint32_t mask)
{
    uint32_t regVal;

    /* Assign regVal to MMAU_CSR_IF_CLR register's value */
    regVal = base->CSR_IF_CLR;
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= mask & ((uint32_t)kMMAU_AccumOverflowInstructionFlag | (uint32_t)kMMAU_OverflowInstructionFlag |
                      (uint32_t)kMMAU_DivideByZeroInstructionFlag | (uint32_t)kMMAU_NegativeInstructionFlag);
    /* Perform this command to avoid writing 1 into interrupt flag bits, which do not corresponding to the mask */
    regVal &= (uint32_t)(~((uint32_t)kMMAU_AccumOverflowInterruptFlag | (uint32_t)kMMAU_OverflowInterruptFlag |
                           (uint32_t)kMMAU_DivideByZeroInterruptFlag));
    /* Write regVal's value into MMAU_CSR_IF_CLR register */
    base->CSR_IF_CLR = regVal;
}

/*!
 * brief Clears instruction flags.
 *
 * This function clears the instruction flags.
 * Example, if you want to clear Overflow and DivideByZero instruction flags:
   code
   MMAU_ClearInstructionFlags(MMAU, kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag);
   endcode
 *
 * param base MMAU peripheral address.
 * param mask Mask of the asserted instruction flags
 *
 (kMMAU_AccumOverflowInstructionFlag|kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag|kMMAU_NegativeInstructionFlag).
 */
void MMAU_ClearInstructionFlags(MMAU_Type *base, uint32_t mask)
{
    uint32_t regVal;

    /* Assign regVal to MMAU_CSR_IF_CLR register's value */
    regVal = base->CSR_IF_CLR;
    /* Write 0 to interrupt flag bits corresponding to mask */
    regVal &= ~(mask & ((uint32_t)kMMAU_AccumOverflowInstructionFlag | (uint32_t)kMMAU_OverflowInstructionFlag |
                        (uint32_t)kMMAU_DivideByZeroInstructionFlag | (uint32_t)kMMAU_NegativeInstructionFlag));
    /* Perform this command to avoid writing 1 into interrupt flag bits, which do not corresponding to the mask */
    regVal &= (uint32_t)(~((uint32_t)kMMAU_AccumOverflowInterruptFlag | (uint32_t)kMMAU_OverflowInterruptFlag |
                           (uint32_t)kMMAU_DivideByZeroInterruptFlag));
    /* Write regVal's value into MMAU_CSR_IF_CLR register */
    base->CSR_IF_CLR = regVal;
}
