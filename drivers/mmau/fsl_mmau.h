/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MMAU_H_
#define _FSL_MMAU_H_

#include "fsl_common.h"

/*!
 * @addtogroup mmau
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_MMAU_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1 */
/*@}*/

/*******************************************************************************
 * MMAU memory map                                                             *
 ******************************************************************************/

/*!
 * @name Registers decorated load/store addresses
 * @{
 */
#define MMAU__X0  0xF0004000UL /*!< Accumulator register X0              */
#define MMAU__X1  0xF0004004UL /*!< Accumulator register X1              */
#define MMAU__X2  0xF0004008UL /*!< Accumulator register X2              */
#define MMAU__X3  0xF000400CUL /*!< Accumulator register X3              */
#define MMAU__A0  0xF0004010UL /*!< Accumulator register A0              */
#define MMAU__A1  0xF0004014UL /*!< Accumulator register A1              */
#define MMAU__A10 0xF0004010UL /*!< Accumulator register pair A10        */

/*! @} */

/*!
 * @name Unsigned integer instructions decorated load/store addresses
 * @{
 */
#define MMAU__REGRW   0xF0004000UL /*!< Registers RW                        */
#define MMAU__UMUL    0xF0004020UL /*!< A10=X2*X3                           */
#define MMAU__UMULD   0xF0004040UL /*!< A10=X21*X3                          */
#define MMAU__UMULDA  0xF0004060UL /*!< A10=A10*X3                          */
#define MMAU__UMAC    0xF00040A0UL /*!< A10=X2*X3+A10                       */
#define MMAU__UMACD   0xF00040C0UL /*!< A10=X21*X3+A10                      */
#define MMAU__UMACDA  0xF00040E0UL /*!< A10=A10*X3+X21                      */
#define MMAU__UDIV    0xF0004120UL /*!< X21/X3=A10                          */
#define MMAU__UDIVD   0xF0004140UL /*!< A10=X2/X3                           */
#define MMAU__UDIVDA  0xF0004160UL /*!< A10=X21/X3                          */
#define MMAU__UDIVDD  0xF0004180UL /*!< A10=A10/X3                          */
#define MMAU__UDIVDDA 0xF00041A0UL /*!< A10=A10/X32                         */
#define MMAU__USQR    0xF0004220UL /*!< A10=SQR(X3)                         */
#define MMAU__USQRD   0xF0004240UL /*!< A10=SQR(X32)                        */
#define MMAU__USQRDA  0xF0004260UL /*!< A10=SQR(A10)                        */

/*! @} */

/*!
 * @name Signed fractional instructions decorated load/store addresses
 * @{
 */
#define MMAU__QSQR   0xF00042A0UL /*!< A10=SQR(X3)                         */
#define MMAU__QSQRD  0xF00042C0UL /*!< A10=SQR(X32)                        */
#define MMAU__QSQRDA 0xF00042E0UL /*!< A10=SQR(A10)                        */
#define MMAU__QDIV   0xF0004320UL /*!< A10=X2/X3                           */
#define MMAU__QDIVD  0xF0004340UL /*!< A10=X21/X3                          */
#define MMAU__QDIVDA 0xF0004360UL /*!< A10=A10/X3                          */
#define MMAU__QMUL   0xF0004420UL /*!< A10=X2*X3                           */
#define MMAU__QMULD  0xF0004440UL /*!< A10=X21*X3                          */
#define MMAU__QMULDA 0xF0004460UL /*!< A10=A10*X3                          */
#define MMAU__QMAC   0xF00044A0UL /*!< A10=X2*X3+A10                       */
#define MMAU__QMACD  0xF00044C0UL /*!< A10=X21*X3+A10                      */
#define MMAU__QMACDA 0xF00044E0UL /*!< A10=A10*X3+X21                      */

/*! @} */

/*!
 * @name Signed integer instructions decorated load/store addresses
 * @{
 */
#define MMAU__SMUL    0xF0004620UL /*!< A10=X2*X3                           */
#define MMAU__SMULD   0xF0004640UL /*!< A10=X21*X3                          */
#define MMAU__SMULDA  0xF0004660UL /*!< A10=A10*X3                          */
#define MMAU__SMAC    0xF00046A0UL /*!< A10=X2*X3+A10                       */
#define MMAU__SMACD   0xF00046C0UL /*!< A10=X21*X3+A10                      */
#define MMAU__SMACDA  0xF00046E0UL /*!< A10=A10*X3+X21                      */
#define MMAU__SDIV    0xF0004720UL /*!< A10=X2/X3                           */
#define MMAU__SDIVD   0xF0004740UL /*!< A10=X21/X3                          */
#define MMAU__SDIVDA  0xF0004760UL /*!< A10=A10/X3                          */
#define MMAU__SDIVDD  0xF0004780UL /*!< A10=X10/X32                         */
#define MMAU__SDIVDDA 0xF00047A0UL /*!< A10=A10/X32                         */

/*! @} */

/*!
 * @name Auxiliary decorated load/store addresses
 * @{
 */
#define MMAU__SAT 0xF0004800UL /*!< Saturation                          */

/*! @} */

/*!
 * @name Fractional Data Type
 * @{
 */
typedef short int frac16_t; /*!< Q0.15  fractional                */
typedef long frac24_t;      /*!< Q8.23  fractional                */
typedef long frac32_t;      /*!< Q0.31  fractional                */
typedef long long frac48_t; /*!< Q16.47 fractional                */
typedef long long frac64_t; /*!< Q0.63  fractional                */

/*! @} */

/*!
 * @brief MMAU interrupt configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the MMAU interrupt configurations.
 */
typedef enum _mmau_interrupt_enable
{
    kMMAU_AccumOverflowInterruptEnable = (MMAU_CSR_QIE_MASK),  /*!< Accumulation Overflow Enable */
    kMMAU_OverflowInterruptEnable      = (MMAU_CSR_VIE_MASK),  /*!< Multiply or Divide overflow Enable */
    kMMAU_DivideByZeroInterruptEnable  = (MMAU_CSR_DZIE_MASK), /*!< Divide by Zero Enable */
} mmau_interrupt_enable_t;

/*! @brief MMAU interrupt and instruction flags */
typedef enum _mmau_interrupt_flag
{
    kMMAU_AccumOverflowInterruptFlag = (MMAU_CSR_QIF_MASK),  /*!< Accumulation Overflow Interrupt Flag */
    kMMAU_OverflowInterruptFlag      = (MMAU_CSR_VIF_MASK),  /*!< Multiply or Divide overflow Interrupt Flag */
    kMMAU_DivideByZeroInterruptFlag  = (MMAU_CSR_DZIF_MASK), /*!< Divide by Zero Interrupt Flag */
} mmau_interrupt_flag_t;

/*! @brief MMAU interrupt and instruction flags */
typedef enum _mmau_instruction_flag
{
    kMMAU_AccumOverflowInstructionFlag = (MMAU_CSR_Q_MASK),  /*!< Accumulation Overflow */
    kMMAU_OverflowInstructionFlag      = (MMAU_CSR_V_MASK),  /*!< Multiply or Divide overflow */
    kMMAU_DivideByZeroInstructionFlag  = (MMAU_CSR_DZ_MASK), /*!< Divide by Zero */
    kMMAU_NegativeInstructionFlag      = (MMAU_CSR_N_MASK),  /*!< Signed calculation result is negative */
} mmau_instruction_flag_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name MMAU Configure
 * @{
 */

/*!
 * @brief Enable DMA for MMAU module.
 *
 * @param base MMAU peripheral address.
 * @param enable Mode of DMA access
 *             - true   Enable DMA access
 *             - false  Disable DMA access
 */
static inline void MMAU_EnableDMA(MMAU_Type *base, bool enable)
{
    if (enable)
    {
        base->CSR |= MMAU_CSR_DRE_MASK;
    }
    else
    {
        base->CSR &= ~(MMAU_CSR_DRE_MASK);
    }
}
/*!
 * @brief Enable supervisor only for MMAU module.
 *
 * @param base MMAU peripheral address.
 * @param enable Mode of MMAU module can be access
 *             - true   MMAU registers can only be access in Supervisor Mode.
 *             - false  MMAU registers can be access in both User Mode or Supervisor Mode.
 */
static inline void MMAU_EnableSupervisorOnly(MMAU_Type *base, bool enable)
{
    if (enable)
    {
        base->CSR |= MMAU_CSR_SO_MASK;
    }
    else
    {
        base->CSR &= ~(MMAU_CSR_SO_MASK);
    }
}

/*!
 * @brief Set control/status register into reset state.
 *
 * This function sets control/status register to a known state. This state is
 * defined in Reference Manual, which is power on reset value. This function must
 * execute in a Supervisor Mode
 * @param base MMAU peripheral address.
 */
void MMAU_Reset(MMAU_Type *base);

/*! @} */

/*!
 * @name MMAU Interrupt
 * @{
 */

/*!
 * @brief Enable MMAU interrupts.
 *
 * This function enables the interrupts related to the mask.
 * Example:
   @code
   MMAU_EnableInterrupts(MMAU, kMMAU_AccumOverflowInterruptEnable | kMMAU_DivideByZeroInterruptEnable);
   @endcode
 *
 * @param base MMAU peripheral address.
 * @param mask Mask of the interrupt enable to be written
 *        (kMMAU_AccumOverflowInterruptEnable|kMMAU_OverflowInterruptEnable|kMMAU_DivideByZeroInterruptEnable).
 */
static inline void MMAU_EnableInterrupts(MMAU_Type *base, uint32_t mask)
{
    base->CSR |= (mask & ((uint32_t)kMMAU_AccumOverflowInterruptEnable | (uint32_t)kMMAU_OverflowInterruptEnable |
                          (uint32_t)kMMAU_DivideByZeroInterruptEnable));
}

/*!
 * @brief Disable MMAU interrupts.
 *
 * This function disables the interrupt related to the mask.
 * Example:
   @code
   MMAU_DisableInterrupts(MMAU, kMMAU_AccumOverflowInterruptEnable | kMMAU_DivideByZeroInterruptEnable);
   @endcode
 *
 * @param base MMAU peripheral address.
 * @param mask Mask of the interrupt enable to be written
 *        (kMMAU_AccumOverflowInterruptEnable|kMMAU_OverflowInterruptEnable|kMMAU_DivideByZeroInterruptEnable).
 */
static inline void MMAU_DisableInterrupts(MMAU_Type *base, uint32_t mask)
{
    base->CSR &= ~(mask & ((uint32_t)kMMAU_AccumOverflowInterruptEnable | (uint32_t)kMMAU_OverflowInterruptEnable |
                           (uint32_t)kMMAU_DivideByZeroInterruptEnable));
}

/*!
 * @brief Gets enabled interrupts.
 *
 * This function gets all interrupt values.
 * Example:
   @code
   uint32_t flags = 0;
   ...
   flags = MMAU_GetEnabledInterrupts(MMAU);
   if (flags & kMMAU_AccumOverflowInterruptEnable)
   {
   ...
   }
   @endcode
 *
 * @param base MMAU peripheral address.
 *
 * @return Combination of enabled interrupt
 */
static inline uint32_t MMAU_GetEnabledInterrupts(MMAU_Type *base)
{
    return base->CSR & ((uint32_t)kMMAU_AccumOverflowInterruptEnable | (uint32_t)kMMAU_OverflowInterruptEnable |
                        (uint32_t)kMMAU_DivideByZeroInterruptEnable);
}

/*!
 * @brief Get interrupt flags.
 *
 * This function gets interrupt flags.
 *
 * @param base MMAU peripheral address.
 *
 * @return the mask of these interrupt flag bits.
 */
static inline uint32_t MMAU_GetInterruptFlags(MMAU_Type *base)
{
    return base->CSR & ((uint32_t)kMMAU_AccumOverflowInterruptFlag | (uint32_t)kMMAU_OverflowInterruptFlag |
                        (uint32_t)kMMAU_DivideByZeroInterruptFlag);
}

/*!
 * @brief Clears interrupt flags.
 *
 * This function clears the interrupt flags.
 * Example, if you want to clear Overflow and DivideByZero interrupt flags:
   @code
   MMAU_ClearInterruptFlags(MMAU, kMMAU_OverflowInterruptFlag|kMMAU_DivideByZeroInterruptFlag);
   @endcode
 *
 * @param base MMAU peripheral address.
 * @param mask Mask of the asserted interrupt flags
 *          (kMMAU_AccumOverflowInterruptFlag|kMMAU_OverflowInterruptFlag|kMMAU_DivideByZeroInterruptFlag).
 */
void MMAU_ClearInterruptFlags(MMAU_Type *base, uint32_t mask);

/*! @} */

/*!
 * @name MMAU Instruction flag
 * @{
 */

/*!
 * @brief Gets the instruction flags.
 *
 * This function gets the instruction flag. Instruction flags are
 * updated by the MMAU after computation of each instruction.
 * Example:
   @code
   uint32_t flags;
   ...
   flags = MMAU_GetInstructionFlags(MMAU);
   if (flags & kMMAU_OverflowInstructionFlag)
   {
    ...
   }
   @endcode
 *
 * @param base MMAU peripheral address.
 *
 * @return Combination of all instruction flags.
 */
static inline uint32_t MMAU_GetInstructionFlags(MMAU_Type *base)
{
    return base->CSR & ((uint32_t)kMMAU_AccumOverflowInstructionFlag | (uint32_t)kMMAU_OverflowInstructionFlag |
                        (uint32_t)kMMAU_DivideByZeroInstructionFlag | (uint32_t)kMMAU_NegativeInstructionFlag);
}

/*!
 * @brief Sets the instruction flags.
 *
 * This function sets the instruction flags.
 * Example:
   @code
   MMAU_SetInstructionFlags(MMAU, kMMAU_AccumOverflowInstructionFlag | kMMAU_NegativeInstructionFlag);
   MMAU_SetInstructionFlags(MMAU, kMMAU_OverflowInstructionFlag | kMMAU_DivideByZeroInstructionFlag);
   @endcode
 *
 * @param base MMAU peripheral address.
 * @param mask Mask of the instruction flags to be written
 *
 (kMMAU_AccumOverflowInstructionFlag|kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag|kMMAU_NegativeInstructionFlag).
 */
void MMAU_SetInstructionFlags(MMAU_Type *base, uint32_t mask);

/*!
 * @brief Clears instruction flags.
 *
 * This function clears the instruction flags.
 * Example, if you want to clear Overflow and DivideByZero instruction flags:
   @code
   MMAU_ClearInstructionFlags(MMAU, kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag);
   @endcode
 *
 * @param base MMAU peripheral address.
 * @param mask Mask of the asserted instruction flags
 *
 (kMMAU_AccumOverflowInstructionFlag|kMMAU_OverflowInstructionFlag|kMMAU_DivideByZeroInstructionFlag|kMMAU_NegativeInstructionFlag).
 */
void MMAU_ClearInstructionFlags(MMAU_Type *base, uint32_t mask);

/*! @} */

/*!
 * @brief Gets hardware revision level.
 *
 * This function gets the hardware revision level of the MMAU. It returns HDR field
 * of the control/status register.
 *
 * @param base MMAU peripheral address.
 * @return uint32_t hardware revision level.
 */
static inline uint32_t MMAU_GetHwRevCmd(MMAU_Type *base)
{
    return ((base->CSR & MMAU_CSR_HDR_MASK) >> MMAU_CSR_HDR_SHIFT);
}

/*!
 * @name Unsigned Integer Operands
 * @{
 */

/*!
 * @brief   Load A10 accumulator register of the MMAU by 64-bit unsigned value.
 *
 * The ulda_d function loads A10 accumulator register of the MMAU
 * by 64-bit unsigned value.
 *
 * @param   dval    uint64_t unsigned load value.
 */
static inline void MMAU_ulda_d(register uint64_t dval)
{
    *((uint64_t volatile *)(MMAU__REGRW | MMAU__A10)) = dval;
}
/*!
 * @brief   Multiply two 32-bit unsigned values returning a 64-bit unsigned
 *          product.
 *
 * The @ref MMAU_d_umul_ll function multiplies two 32-bit unsigned values
 * returning a 64-bit unsigned product.
 * @param   lval1   uint32_t unsigned value.
 * @param   lval2   uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umul_ll(register uint32_t lval1, register uint32_t lval2)
{
    *((uint32_t volatile *)(MMAU__UMUL | MMAU__X2)) = lval1;
    *((uint32_t volatile *)(MMAU__UMUL | MMAU__X3)) = lval2;
    return *((uint64_t volatile *)(MMAU__UMUL | MMAU__A10));
}

/*!
 * @brief   Multiply 64-bit unsigned value with 32-bit unsigned value returning
 *          a 64-bit unsigned product.
 *
 * The @ref MMAU_d_umul_dl function multiplies 64-bit unsigned value with
 * 32-bit unsigned value returning a 64-bit unsigned product.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umul_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMULD | MMAU__X1)) = dval;
    *((uint32_t volatile *)(MMAU__UMULD | MMAU__X3)) = lval;
    return *((uint64_t volatile *)(MMAU__UMULD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit unsigned value with 32-bit unsigned value
 *          returning saturated 64-bit unsigned product.
 *
 * The @ref MMAU_d_umuls_dl function multiplies 64-bit unsigned value with
 * 32-bit unsigned value returning saturated 64-bit unsigned product.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline uint64_t MMAU_d_umuls_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMULD | MMAU__X1 | MMAU__SAT)) = dval;
    *((uint32_t volatile *)(MMAU__UMULD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((uint64_t volatile *)(MMAU__UMULD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit unsigned value with 64-bit unsigned value stored in
 *          the A10 register of the MMAU returning a 64-bit unsigned product.
 *
 * The @ref MMAU_d_umula_l function multiplies 32-bit unsigned value with
 * 64-bit unsigned value stored in the A10 register of the MMAU
 * returning a 64-bit unsigned product.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umula_l(register uint32_t lval)
{
    *((uint32_t volatile *)(MMAU__UMULDA | MMAU__X3)) = lval;
    return *((uint64_t volatile *)(MMAU__UMULDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit unsigned value with 64-bit unsigned value
 *          stored in the A10 register of the MMAU returning saturated 64-bit unsigned
 *          product.
 *
 * The @ref MMAU_d_umulas_l function multiplies 32-bit unsigned value with
 * 64-bit unsigned value stored in the A10 register of the MMAU
 * returning saturated 64-bit unsigned product.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value  after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline uint64_t MMAU_d_umulas_l(register uint32_t lval)
{
    *((uint32_t volatile *)(MMAU__UMULDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((uint64_t volatile *)(MMAU__UMULDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply two 32-bit unsigned values and add product with value
 *          stored in the A10 register of the MMAU returning a 64-bit unsigned
 *          A10 register value.
 *
 * The @ref MMAU_d_umac_ll function multiplies two 32-bit unsigned values
 * and add product with value stored in the A10 register of the MMAU
 * returning a 64-bit unsigned A10 register value.
 * @param   lval1   uint32_t unsigned value.
 * @param   lval2   uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umac_ll(register uint32_t lval1, register uint32_t lval2)
{
    *((uint32_t volatile *)(MMAU__UMAC | MMAU__X2)) = lval1;
    *((uint32_t volatile *)(MMAU__UMAC | MMAU__X3)) = lval2;
    return *((uint64_t volatile *)(MMAU__UMAC | MMAU__A10));
}

/*!
 * @brief   Saturating multiply two 32-bit unsigned values and add product with
 *          value stored in the A10 register of the MMAU returning a 64-bit unsigned
 *          A10 register value.
 *
 * The @ref MMAU_d_umacs_ll function multiplies two 32-bit unsigned values
 * and add product with value stored in the A10 register of the MMAU
 * returning saturated 64-bit unsigned A10 register value.
 * @param   lval1   uint32_t unsigned value.
 * @param   lval2   uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline uint64_t MMAU_d_umacs_ll(register uint32_t lval1, register uint32_t lval2)
{
    *((uint32_t volatile *)(MMAU__UMAC | MMAU__X2 | MMAU__SAT)) = lval1;
    *((uint32_t volatile *)(MMAU__UMAC | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((uint64_t volatile *)(MMAU__UMAC | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit unsigned value with 32-bit unsigned value and add
 *          product with value stored in the A10 register of the MMAU
 *          returning a 64-bit unsigned A10 register value.
 *
 * @details The @ref MMAU_d_umac_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit unsigned A10 register
 *          value.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umac_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMACD | MMAU__X1)) = dval;
    *((uint32_t volatile *)(MMAU__UMACD | MMAU__X3)) = lval;
    return *((uint64_t volatile *)(MMAU__UMACD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit unsigned value with 32-bit unsigned value
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit unsigned A10 register value.
 *
 * @details The @ref MMAU_d_umacs_dl function multiplies 64-bit unsigned value with
 *          32-bit unsigned value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit unsigned A10
 *          register value.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline uint64_t MMAU_d_umacs_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMACD | MMAU__X1 | MMAU__SAT)) = dval;
    *((uint32_t volatile *)(MMAU__UMACD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((uint64_t volatile *)(MMAU__UMACD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit unsigned value by value stored in the A10 register
 *          of the MMAU and add product with 64-bit unsigned value returning
 *          a 64-bit unsigned A10 register value.
 *
 * @details The @ref MMAU_d_umaca_dl function multiplies 32-bit unsigned value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit unsigned value returning a 64-bit unsigned A10 register
 *          value.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_umaca_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMACDA | MMAU__X1)) = dval;
    *((uint32_t volatile *)(MMAU__UMACDA | MMAU__X3)) = lval;
    return *((uint64_t volatile *)(MMAU__UMACDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit unsigned value by value stored in the A10
 *          register of the MMAU and add product with 64-bit unsigned value returning
 *          a saturated 64-bit unsigned A10 register value.
 *
 * @details The @ref MMAU_d_umacas_dl function multiplies 32-bit unsigned value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit unsigned value returning saturated 64-bit unsigned A10
 *          register value.
 * @param   dval    uint64_t unsigned value.
 * @param   lval    uint32_t unsigned value.
 * @return  uint64_t unsigned value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline uint64_t MMAU_d_umacas_dl(register uint64_t dval, register uint32_t lval)
{
    *((uint64_t volatile *)(MMAU__UMACDA | MMAU__X1 | MMAU__SAT)) = dval;
    *((uint32_t volatile *)(MMAU__UMACDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((uint64_t volatile *)(MMAU__UMACDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide two 32-bit unsigned values returning a 32-bit unsigned
 *          quotient.
 *
 * @details The @ref MMAU_l_udiv_ll function divides two 32-bit unsigned values
 *          returning a 32-bit unsigned quotient.
 * @param   lnum    uint32_t unsigned divisor value.
 * @param   lden    uint32_t unsigned dividend value.
 * @return  uint32_t unsigned quotient value.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 */
static inline uint32_t MMAU_l_udiv_ll(register uint32_t lnum, register uint32_t lden)
{
    *((uint32_t volatile *)(MMAU__UDIV | MMAU__X2)) = lnum;
    *((uint32_t volatile *)(MMAU__UDIV | MMAU__X3)) = lden;
    return *((uint32_t volatile *)(MMAU__UDIV | MMAU__A0));
}

/*!
 * @brief   Divide 64-bit unsigned value by 32-bit unsigned value returning a
 *          64-bit unsigned quotient.
 *
 * @details The @ref MMAU_d_udiv_dl function divides 64-bit unsigned value by 32-bit
 *          unsigned value returning a 64-bit unsigned quotient.
 * @param   dnum    uint64_t unsigned divisor value.
 * @param   lden    uint32_t unsigned dividend value.
 * @return  uint64_t unsigned quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_udiv_dl(register uint64_t dnum, register uint32_t lden)
{
    *((uint64_t volatile *)(MMAU__UDIVD | MMAU__X1)) = dnum;
    *((uint32_t volatile *)(MMAU__UDIVD | MMAU__X3)) = lden;
    return *((uint64_t volatile *)(MMAU__UDIVD | MMAU__A10));
}

/*!
 * @brief   Divide two 64-bit unsigned values returning a 64-bit unsigned
 *          quotient.
 *
 * @details The @ref MMAU_d_udiv_dd function divides two 64-bit unsigned values
 *          returning a 64-bit unsigned quotient.
 * @param   dnum    uint64_t unsigned divisor value.
 * @param   dden    uint64_t unsigned dividend value.
 * @return  uint64_t unsigned quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_udiv_dd(register uint64_t dnum, register uint64_t dden)
{
    *((uint64_t volatile *)(MMAU__UDIVDD | MMAU__X0)) = dnum;
    *((uint64_t volatile *)(MMAU__UDIVDD | MMAU__X2)) = dden;
    return *((uint64_t volatile *)(MMAU__UDIVDD | MMAU__A10));
}

/*!
 * @brief   Divide 32-bit unsigned value stored in the A10 register of the MMAU
 *          by 32-bit unsigned value returning a 64-bit unsigned quotient.
 *
 * @details The @ref MMAU_d_udiva_l function divides 64-bit unsigned value stored in
 *          the A10 register of the MMAU by 32-bit unsigned value returning
 *          a 64-bit unsigned quotient.
 * @param   lden1   uint32_t unsigned dividend value.
 * @return  uint64_t unsigned quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_udiva_l(register uint32_t lden1)
{
    *((uint32_t volatile *)(MMAU__UDIVDA | MMAU__X3)) = lden1;
    return *((uint64_t volatile *)(MMAU__UDIVDA | MMAU__A10));
}

/*!
 * @brief   Divide 64-bit unsigned value stored in the A10 register of the MMAU
 *          by 64-bit unsigned value returning a 64-bit unsigned quotient.
 *
 * @details The @ref MMAU_d_udiva_d function divides 64-bit unsigned value stored in
 *          the A10 register of the MMAU by 64-bit unsigned value returning
 *          a 64-bit unsigned quotient.
 * @param   dden1   uint64_t unsigned dividend value.
 * @return  uint64_t unsigned quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline uint64_t MMAU_d_udiva_d(register uint64_t dden1)
{
    *((uint64_t volatile *)(MMAU__UDIVDDA | MMAU__X2)) = dden1;
    return *((uint64_t volatile *)(MMAU__UDIVDDA | MMAU__A10));
}

/*!
 * @brief   Compute and return a 32-bit unsigned square root of the 32-bit
 *          unsigned radicand.
 *
 * @details The @ref MMAU_l_usqr_l function computes and returns a 32-bit unsigned
 *          square root of the 32-bit unsigned radicand.
 * @param   lrad    uint32_t unsigned radicand.
 * @return  uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 */
static inline uint32_t MMAU_l_usqr_l(register uint32_t lrad)
{
    *((uint32_t volatile *)(MMAU__USQR | MMAU__X3)) = lrad;
    return *((uint32_t volatile *)(MMAU__USQR | MMAU__A0));
}

/*!
 * @brief   Compute and return a 32-bit unsigned square root of the 64-bit
 *          unsigned radicand.
 *
 * @details The @ref MMAU_l_usqr_d function computes and returns a 32-bit unsigned
 *          square root of the 64-bit unsigned radicand.
 * @param   drad    uint64_t unsigned radicand.
 * @return  uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 */
static inline uint32_t MMAU_l_usqr_d(register uint64_t drad)
{
    *((uint64_t volatile *)(MMAU__USQRD | MMAU__X2)) = drad;
    return *((uint32_t volatile *)(MMAU__USQRD | MMAU__A0));
}

/*!
 * @brief   Compute and return a 16-bit unsigned square root of the 32-bit
 *          unsigned radicand.
 *
 * @details The @ref MMAU_s_usqr_l function computes and returns a 16-bit unsigned
 *          square root of the 32-bit unsigned radicand.
 * @param   lrad    uint32 unsigned radicand.
 * @return  uint16 unsigned square root.
 * @note    Square root is stored in A0 register of the MMAU for next
 *          computation.
 */
static inline uint16_t MMAU_s_usqr_l(register uint32_t lrad)
{
    *((uint32_t volatile *)(MMAU__USQR | MMAU__X3)) = lrad;
    return (uint16_t)(*((uint32_t volatile *)(MMAU__USQR | MMAU__A0)));
}

/*!
 * @brief   Compute and return a 32-bit unsigned square root of the radicand
 *          stored in the A10 register of the MMAU.
 *
 * @details The @ref MMAU_l_usqra function computes and returns a 32-bit unsigned
 *          square root of the radicand stored in the A10 register of the MMAU.
 * @return  uint32_t unsigned square root.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 */
static inline uint32_t MMAU_l_usqra(void)
{
    return *((uint32_t volatile *)(MMAU__USQRDA | MMAU__A0));
}
/*! @} */

/*!
 * @name Signed Integer Operands
 * @{
 */

/*!
 * @brief   Load A10 accumulator register of the MMAU by 64-bit integer value.
 *
 * @details The @ref MMAU_slda_d function loads A10 accumulator register of the MMAU
 *          by 64-bit integer value.
 * @param   dval    int64_t integer value.
 */
static inline void MMAU_slda_d(register int64_t dval)
{
    *((int64_t volatile *)(MMAU__REGRW | MMAU__A10)) = dval;
}
/*!
 * @brief   Multiply two 32-bit integer values returning a 64-bit integer
 *          product.
 *
 * @details The @ref MMAU_d_smul_ll function multiplies two 32-bit integer values
 *          returning a 64-bit integer product.
 * @param   lval1   int32_t integer value.
 * @param   lval2   int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smul_ll(register int32_t lval1, register int32_t lval2)
{
    *((int32_t volatile *)(MMAU__SMUL | MMAU__X2)) = lval1;
    *((int32_t volatile *)(MMAU__SMUL | MMAU__X3)) = lval2;
    return *((int64_t volatile *)(MMAU__SMUL | MMAU__A10));
}

/*!
 * @brief   Multiply 64-bit integer value with 32-bit integer value returning a
 *          64-bit integer product.
 *
 * @details The @ref MMAU_d_smul_dl function multiplies 64-bit integer value with
 *          32-bit integer value returning a 64-bit integer product.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smul_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMULD | MMAU__X1)) = dval;
    *((int32_t volatile *)(MMAU__SMULD | MMAU__X3)) = lval;
    return *((int64_t volatile *)(MMAU__SMULD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit integer value with 32-bit integer value
 *          returning saturated 64-bit integer product.
 *
 * @details The @ref MMAU_d_smuls_dl function multiplies 64-bit integer value with
 *          32-bit integer value returning saturated 64-bit integer product.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline int64_t MMAU_d_smuls_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMULD | MMAU__X1 | MMAU__SAT)) = dval;
    *((int32_t volatile *)(MMAU__SMULD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((int64_t volatile *)(MMAU__SMULD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit integer value with 64-bit integer value stored in
 *          the A10 register of the MMAU returning a 64-bit integer product.
 *
 * @details The @ref MMAU_d_smula_l function multiplies 32-bit integer value with
 *          64-bit integer value stored in the A10 register of the MMAU
 *          returning a 64-bit integer product.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smula_l(register int32_t lval)
{
    *((int32_t volatile *)(MMAU__SMULDA | MMAU__X3)) = lval;
    return *((int64_t volatile *)(MMAU__SMULDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit integer value with 64-bit integer value
 *          stored in the A10 register of the MMAU returning saturated 64-bit integer
 *          product.
 *
 * @details The @ref MMAU_d_smulas_l function multiplies 32-bit integer value with
 *          64-bit integer value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer product.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline int64_t MMAU_d_smulas_l(register int32_t lval)
{
    *((int32_t volatile *)(MMAU__SMULDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((int64_t volatile *)(MMAU__SMULDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply two 32-bit integer values and add product with value stored
 *          in the A10 register of the MMAU returning a 64-bit integer
 *          A10 register value.
 *
 * @details The @ref MMAU_d_smac_ll function multiplies two 32-bit integer values and
 *          add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit integer A10 register value.
 * @param   lval1   int32_t integer value.
 * @param   lval2   int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smac_ll(register int32_t lval1, register int32_t lval2)
{
    *((int32_t volatile *)(MMAU__SMAC | MMAU__X2)) = lval1;
    *((int32_t volatile *)(MMAU__SMAC | MMAU__X3)) = lval2;
    return *((int64_t volatile *)(MMAU__SMAC | MMAU__A10));
}

/*!
 * @brief   Saturating multiply two 32-bit integer values and add product with
 *          value stored in the A10 register of the MMAU returning a 64-bit integer
 *          A10 register value.
 *
 * @details The @ref MMAU_d_smacs_ll function multiplies two 32-bit integer values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer A10 register value.
 * @param   lval1   int32_t integer value.
 * @param   lval2   int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline int64_t MMAU_d_smacs_ll(register int32_t lval1, register int32_t lval2)
{
    *((int32_t volatile *)(MMAU__SMAC | MMAU__X2 | MMAU__SAT)) = lval1;
    *((int32_t volatile *)(MMAU__SMAC | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((int64_t volatile *)(MMAU__SMAC | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit integer value with 32-bit integer value and add
 *          product with value stored in the A10 register of the MMAU
 *          returning a 64-bit integer A10 register value.
 *
 * @details The @ref MMAU_d_smac_dl function multiplies 64-bit integer value with
 *          32-bit integer value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit integer A10 register
 *          value.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smac_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMACD | MMAU__X1)) = dval;
    *((int32_t volatile *)(MMAU__SMACD | MMAU__X3)) = lval;
    return *((int64_t volatile *)(MMAU__SMACD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit integer value with 32-bit integer value
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit integer A10 register value.
 *
 * @details The @ref MMAU_d_smacs_dl function multiplies 64-bit integer value with
 *          32-bit integer value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit integer A10
 *          register value.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline int64_t MMAU_d_smacs_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMACD | MMAU__X1 | MMAU__SAT)) = dval;
    *((int32_t volatile *)(MMAU__SMACD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((int64_t volatile *)(MMAU__SMACD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit integer value by value stored in the A10 register of
 *          the MMAU and add product with 64-bit integer value returning
 *          a 64-bit integer A10 register value.
 *
 * @details The @ref MMAU_d_smaca_dl function multiplies 32-bit integer value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit integer value returning a 64-bit integer A10 register value.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_smaca_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMACDA | MMAU__X1)) = dval;
    *((int32_t volatile *)(MMAU__SMACDA | MMAU__X3)) = lval;
    return *((int64_t volatile *)(MMAU__SMACDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit integer value by value stored in the A10
 *          register of the MMAU and add product with 64-bit integer value returning
 *          a saturated 64-bit integer A10 register value.
 *
 * @details The @ref MMAU_d_smacas_dl function multiplies 32-bit integer value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit integer value returning saturated 64-bit integer A10 register
 *          value.
 * @param   dval    int64_t integer value.
 * @param   lval    int32_t integer value.
 * @return  int64_t integer value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline int64_t MMAU_d_smacas_dl(register int64_t dval, register int32_t lval)
{
    *((int64_t volatile *)(MMAU__SMACDA | MMAU__X1 | MMAU__SAT)) = dval;
    *((int32_t volatile *)(MMAU__SMACDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((int64_t volatile *)(MMAU__SMACDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide two 32-bit integer values returning a 32-bit integer
 *          quotient.
 *
 * @details The @ref MMAU_l_sdiv_ll function divides two 32-bit integer values
 *          returning a 32-bit integer quotient.
 * @param   lnum    int32_t integer divisor value.
 * @param   lden    int32_t integer dividend value.
 * @return  int32_t integer quotient value.
 * @note    Quotient is stored in A0 register of the MMAU for next computation.
 */
static inline int32_t MMAU_l_sdiv_ll(register int32_t lnum, register int32_t lden)
{
    *((int32_t volatile *)(MMAU__SDIV | MMAU__X2)) = lnum;
    *((int32_t volatile *)(MMAU__SDIV | MMAU__X3)) = lden;
    return *((int32_t volatile *)(MMAU__SDIV | MMAU__A0));
}

/*!
 * @brief   Divide two 32-bit integer values returning a 32-bit integer
 *          quotient.
 *
 * @details The @ref MMAU_l_sdivs_ll function divides two 32-bit integer values
 *          returning a 32-bit integer quotient.
 * @param   lnum    int32_t integer divisor value.
 * @param   lden    int32_t integer dividend value.
 * @return  int32_t integer quotient value.
 * @note    Saturated quotient is  stored in A0 register of the MMAU for
 *          next computation.
 */
static inline int32_t MMAU_l_sdivs_ll(register int32_t lnum, register int32_t lden)
{
    *((int32_t volatile *)(MMAU__SDIV | MMAU__X2 | MMAU__SAT)) = lnum;
    *((int32_t volatile *)(MMAU__SDIV | MMAU__X3 | MMAU__SAT)) = lden;
    return *((int32_t volatile *)(MMAU__SDIV | MMAU__A0 | MMAU__SAT));
}

/*!
 * @brief   Divide 64-bit integer value by 32-bit integer value returning a
 *          64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdiv_dl function divides 64-bit integer value by 32-bit
 *          integer value returning a 64-bit integer quotient.
 * @param   dnum    int64_t integer divisor value.
 * @param   lden    int32_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_sdiv_dl(register int64_t dnum, register int32_t lden)
{
    *((int64_t volatile *)(MMAU__SDIVD | MMAU__X1)) = dnum;
    *((int32_t volatile *)(MMAU__SDIVD | MMAU__X3)) = lden;
    return *((int64_t volatile *)(MMAU__SDIVD | MMAU__A10));
}

/*!
 * @brief   Divide 64-bit integer value by 32-bit integer value returning a
 *          64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdivs_dl function divides 64-bit integer value by 32-bit
 *          integer value returning a 64-bit integer quotient.
 * @param   dnum    int64_t integer divisor value.
 * @param   lden    int32_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation.
 */
static inline int64_t MMAU_d_sdivs_dl(register int64_t dnum, register int32_t lden)
{
    *((int64_t volatile *)(MMAU__SDIVD | MMAU__X1 | MMAU__SAT)) = dnum;
    *((int32_t volatile *)(MMAU__SDIVD | MMAU__X3 | MMAU__SAT)) = lden;
    return *((int64_t volatile *)(MMAU__SDIVD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide two 64-bit integer values returning a 64-bit integer
 *          quotient.
 *
 * @details The @ref MMAU_d_sdiv_dd function divides two 64-bit integer values
 *          returning a 64-bit integer quotient.
 * @param   dnum    int64_t integer divisor value.
 * @param   dden    int64_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_sdiv_dd(register int64_t dnum, register int64_t dden)
{
    *((int64_t volatile *)(MMAU__SDIVDD | MMAU__X0)) = dnum;
    *((int64_t volatile *)(MMAU__SDIVDD | MMAU__X2)) = dden;
    return *((int64_t volatile *)(MMAU__SDIVDD | MMAU__A10));
}

/*!
 * @brief   Divide two 64-bit integer values returning a 64-bit integer
 *          quotient.
 *
 * @details The @ref MMAU_d_sdivs_dd function divides two 64-bit integer values
 *          returning a 64-bit integer quotient.
 * @param   dnum    int64_t integer divisor value.
 * @param   dden    int64_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation.
 */
static inline int64_t MMAU_d_sdivs_dd(register int64_t dnum, register int64_t dden)
{
    *((int64_t volatile *)(MMAU__SDIVDD | MMAU__X0 | MMAU__SAT)) = dnum;
    *((int64_t volatile *)(MMAU__SDIVDD | MMAU__X2 | MMAU__SAT)) = dden;
    return *((int64_t volatile *)(MMAU__SDIVDD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide 32-bit integer value stored in the A10 register of the MMAU
 *          by 32-bit integer value returning a 64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdiva_l function divides 32-bit integer value stored in
 *          the A10 register of the MMAU by 32-bit integer value returning
 *          a 64-bit integer quotient.
 * @param   lden1   int32_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_sdiva_l(register int32_t lden1)
{
    *((int32_t volatile *)(MMAU__SDIVDA | MMAU__X3)) = lden1;
    return *((int64_t volatile *)(MMAU__SDIVDA | MMAU__A10));
}

/*!
 * @brief   Divide 32-bit integer value stored in the A10 register of the MMAU
 *          by 32-bit integer value returning saturated 64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdivas_l function divides 32-bit integer value stored in
 *          the A10 register of the MMAU by 32-bit integer value returning
 *          a saturated 64-bit integer quotient.
 * @param   lden1   int32_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation.
 */
static inline int64_t MMAU_d_sdivas_l(register int32_t lden1)
{
    *((int32_t volatile *)(MMAU__SDIVDA | MMAU__X3 | MMAU__SAT)) = lden1;
    return *((int64_t volatile *)(MMAU__SDIVDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide 64-bit integer value stored in the A10 register of the MMAU
 *          by 64-bit integer value returning a 64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdiva_d function divides 64-bit integer value stored in
 *          the A10 register of the MMAU by 64-bit integer value returning
 *          a 64-bit integer quotient.
 * @param   dden1   int64_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline int64_t MMAU_d_sdiva_d(register int64_t dden1)
{
    *((int64_t volatile *)(MMAU__SDIVDDA | MMAU__X2)) = dden1;
    return *((int64_t volatile *)(MMAU__SDIVDDA | MMAU__A10));
}

/*!
 * @brief   Divide 64-bit integer value stored in the A10 register of the MMAU
 *          by 64-bit integer value returning saturated 64-bit integer quotient.
 *
 * @details The @ref MMAU_d_sdivas_d function divides 64-bit integer value stored in
 *          the A10 register of the MMAU by 64-bit integer value returning
 *          a saturated 64-bit integer quotient.
 * @param   dden1   int64_t integer dividend value.
 * @return  int64_t integer quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation.
 */
static inline int64_t MMAU_d_sdivas_d(register int64_t dden1)
{
    *((int64_t volatile *)(MMAU__SDIVDDA | MMAU__X2 | MMAU__SAT)) = dden1;
    return *((int64_t volatile *)(MMAU__SDIVDDA | MMAU__A10 | MMAU__SAT));
}

/*! @} */

/*!
 * @name Fractional Operands
 * @{
 */

/*!
 * @brief   Load A10 accumulator register of the MMAU by 64-bit fractional
 *          value.
 *
 * @details The @ref MMAU_lda_d function loads A10 accumulator register of the MMAU
 *          by 64-bit fractional value.
 * @param   dval    @ref frac64_t fractional value.
 */
static inline void MMAU_lda_d(register frac64_t dval)
{
    *((frac64_t volatile *)(MMAU__REGRW | MMAU__A10)) = dval;
}
/*!
 * @brief   Multiply two 32-bit fractional values returning a 32-bit fractional
 *          product.
 *
 * @details The @ref MMAU_l_mul_ll function multiplies two 32-bit fractional values
 *          returning a 32-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_mul_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X2)) = lval1;
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X3)) = lval2;
    return *((frac32_t volatile *)(MMAU__QMUL | MMAU__A1));
}

/*!
 * @brief   Saturating multiply two 32-bit fractional values returning saturated
 *          32-bit fractional product.
 *
 * @details The @ref MMAU_l_muls_ll function multiplies two 32-bit fractional values
 *          returning saturated 32-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_muls_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X2 | MMAU__SAT)) = lval1;
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((frac32_t volatile *)(MMAU__QMUL | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Multiply two 32-bit fractional values returning a 64-bit fractional
 *          product.
 *
 * @details The @ref MMAU_d_mul_ll function multiplies two 32-bit fractional values
 *          returning a 64-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_mul_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X2)) = lval1;
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X3)) = lval2;
    return *((frac64_t volatile *)(MMAU__QMUL | MMAU__A10));
}

/*!
 * @brief   Saturating multiply two 32-bit fractional values returning saturated
 *          64-bit fractional product.
 *
 * @details The @ref MMAU_d_muls_ll function multiplies two 32-bit fractional values
 *          returning saturated 64-bit fractional product.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_muls_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X2 | MMAU__SAT)) = lval1;
    *((frac32_t volatile *)(MMAU__QMUL | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((frac64_t volatile *)(MMAU__QMUL | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit fractional value with 32-bit fractional value
 *          returning a 64-bit fractional product.
 *
 * @details The @ref MMAU_d_mul_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning a 64-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_mul_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMULD | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMULD | MMAU__X3)) = lval;
    return *((frac64_t volatile *)(MMAU__QMULD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value returning saturated 64-bit fractional product.
 *
 * @details The @ref MMAU_d_muls_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning saturated 64-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_muls_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMULD | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMULD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac64_t volatile *)(MMAU__QMULD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit fractional value with 64-bit fractional value stored
 *          in the A10 register of the MMAU returning a 64-bit fractional product.
 *
 * @details The @ref MMAU_d_mula_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_mula_l(register frac32_t lval)
{
    *((frac32_t volatile *)(MMAU__QMULDA | MMAU__X3)) = lval;
    return *((frac64_t volatile *)(MMAU__QMULDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit fractional value with 64-bit fractional
 *          value stored in the A10 register of the MMAU returning saturated 64-bit
 *          fractional product.
 *
 * @details The @ref MMAU_d_mulas_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_mulas_l(register frac32_t lval)
{
    *((frac32_t volatile *)(MMAU__QMULDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac64_t volatile *)(MMAU__QMULDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit fractional value with 32-bit fractional value
 *          returning a 32-bit fractional product.
 *
 * @details The @ref MMAU_l_mul_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning a 32-bit fractional product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_mul_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMULD | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMULD | MMAU__X3)) = lval;
    return *((frac32_t volatile *)(MMAU__QMULD | MMAU__A1));
}

/*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value returning saturated 32-bit fractional product.
 *
 * @details The @ref MMAU_l_muls_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value returning saturated 32-bit fractional
 *          product.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_muls_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMULD | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMULD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac32_t volatile *)(MMAU__QMULD | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit fractional value with 64-bit fractional value stored
 *          in the A10 register of the MMAU returning a 32-bit fractional
 *          product.
 *
 * @details The @ref MMAU_l_mula_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_mula_l(register frac32_t lval)
{
    *((frac32_t volatile *)(MMAU__QMULDA | MMAU__X3)) = lval;
    return *((frac32_t volatile *)(MMAU__QMULDA | MMAU__A1));
}

/*!
 * @brief   Saturating multiply 32-bit fractional value with 64-bit fractional
 *          value stored in the A10 register of the MMAU returning saturated
 *          32-bit fractional product.
 *
 * @details The @ref MMAU_l_mulas_l function multiplies 32-bit fractional value with
 *          64-bit fractional value stored in the A10 register of the MMAU
 *          returning saturated 32-bit fractional product.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_mulas_l(register frac32_t lval)
{
    *((frac32_t volatile *)(MMAU__QMULDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac32_t volatile *)(MMAU__QMULDA | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Multiply two 32-bit fractional values and add product with value
 *          stored in the A10 register of the MMAU returning a 64-bit fractional
 *          A10 register value.
 *
 * @details The @ref MMAU_d_mac_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional A10 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_mac_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X2)) = lval1;
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X3)) = lval2;
    return *((frac64_t volatile *)(MMAU__QMAC | MMAU__A10));
}

/*!
 * @brief   Saturating multiply two 32-bit fractional values and add product
 *          with value stored in the A10 register of the MMAU returning a 64-bit fractional
 *          A10 register value.
 *
 * @details The @ref MMAU_d_macs_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional A10 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_macs_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X2 | MMAU__SAT)) = lval1;
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((frac64_t volatile *)(MMAU__QMAC | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit fractional value with 32-bit fractional value and
 *          add product with value stored in the A10 register of the MMAU
 *          returning a 64-bit fractional A10 register value.
 *
 * @details The @ref MMAU_d_mac_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the
 *          A10 register of the MMAU returning a 64-bit fractional A10 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_mac_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACD | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMACD | MMAU__X3)) = lval;
    return *((frac64_t volatile *)(MMAU__QMACD | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value and add product with value stored in the A10 register of the MMAU
 *          returning saturated 64-bit fractional A10 register value.
 *
 * @details The @ref MMAU_d_macs_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the
 *          A10 register of the MMAU returning saturated 64-bit fractional A10
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_macs_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACD | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMACD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac64_t volatile *)(MMAU__QMACD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit fractional value by value stored in the A10 register
 *          of the MMAU and add product with 64-bit fractional value returning
 *          a 64-bit fractional A10 register value.
 *
 * @details The @ref MMAU_d_maca_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning a 64-bit fractional A10 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_maca_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACDA | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMACDA | MMAU__X3)) = lval;
    return *((frac64_t volatile *)(MMAU__QMACDA | MMAU__A10));
}

/*!
 * @brief   Saturating multiply 32-bit fractional value by value stored in the
 *          A10 register of the MMAU and add product with 64-bit fractional value returning
 *          a saturated 64-bit fractional A10 register value.
 *
 * @details The @ref MMAU_d_macas_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning saturated 64-bit fractional A10
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac64_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_macas_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACDA | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMACDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac64_t volatile *)(MMAU__QMACDA | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Multiply two 32-bit fractional values and add product with value
 *          stored in the A10 register of the MMAU returning a 32-bit fractional
 *          A10 register value.
 *
 * @details The @ref MMAU_l_mac_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional A1 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_mac_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X2)) = lval1;
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X3)) = lval2;
    return *((frac32_t volatile *)(MMAU__QMAC | MMAU__A1));
}

/*!
 * @brief   Saturating multiply two 32-bit fractional values and add product
 *          with value stored in the A10 register of the MMAU returning a 32-bit
 *          fractional A10 register value.
 *
 * @details The @ref MMAU_l_macs_ll function multiplies two 32-bit fractional values
 *          and add product with value stored in the A10 register of the MMAU
 *          returning saturated 32-bit fractional A1 register value.
 * @param   lval1   @ref frac32_t fractional value.
 * @param   lval2   @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_macs_ll(register frac32_t lval1, register frac32_t lval2)
{
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X2 | MMAU__SAT)) = lval1;
    *((frac32_t volatile *)(MMAU__QMAC | MMAU__X3 | MMAU__SAT)) = lval2;
    return *((frac32_t volatile *)(MMAU__QMAC | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Multiply 64-bit fractional value with 32-bit fractional value and
 *          add product with value stored in the A10 register of the MMAU
 *          returning a 32-bit fractional A10 register value.
 *
 * @details The @ref MMAU_l_mac_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the A10
 *          register of the MMAU returning a 32-bit fractional A1 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_mac_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACD | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMACD | MMAU__X3)) = lval;
    return *((frac32_t volatile *)(MMAU__QMACD | MMAU__A1));
}

/*!
 * @brief   Saturating multiply 64-bit fractional value with 32-bit fractional
 *          value and add product with value stored in the A10 register of the
 *          MMAU returning saturated 32-bit fractional A10 register value.
 *
 * @details The @ref MMAU_l_macs_dl function multiplies 64-bit fractional value with
 *          32-bit fractional value and add product with value stored in the A10
 *          register of the MMAU returning saturated 32-bit fractional A1
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_macs_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACD | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMACD | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac32_t volatile *)(MMAU__QMACD | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Multiply 32-bit fractional value by value stored in the A10 register
 *          of the MMAU and add product with 64-bit fractional value returning a
 *          32-bit fractional A10 register value.
 *
 * @details The @ref MMAU_l_maca_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning a 32-bit fractional A1 register
 *          value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Product is stored in A10 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_maca_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACDA | MMAU__X1)) = dval;
    *((frac32_t volatile *)(MMAU__QMACDA | MMAU__X3)) = lval;
    return *((frac32_t volatile *)(MMAU__QMACDA | MMAU__A1));
}

/*!
 * @brief   Saturating multiply 32-bit fractional value by value stored in the
 *          A10 register of the MMAU and add product with 64-bit fractional
 *          value returning a saturated 32-bit fractional A10 register value.
 *
 * @details The @ref MMAU_l_macas_dl function multiplies 32-bit fractional value by
 *          value stored in the A10 register of the MMAU and add product with
 *          64-bit fractional value returning saturated 32-bit fractional A1
 *          register value.
 * @param   dval    @ref frac64_t fractional value.
 * @param   lval    @ref frac32_t fractional value.
 * @return  @ref frac32_t fractional value after multiply.
 * @note    Saturated product is stored in A10 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_macas_dl(register frac64_t dval, register frac32_t lval)
{
    *((frac64_t volatile *)(MMAU__QMACDA | MMAU__X1 | MMAU__SAT)) = dval;
    *((frac32_t volatile *)(MMAU__QMACDA | MMAU__X3 | MMAU__SAT)) = lval;
    return *((frac32_t volatile *)(MMAU__QMACDA | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Divide two 32-bit fractional values returning a 32-bit fractional
 *          quotient.
 *
 * @details The @ref MMAU_l_div_ll function divides two 32-bit fractional values
 *          returning a 32-bit fractional quotient.
 * @param   lnum    @ref frac32_t fractional divisor value.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac32_t fractional quotient value.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_div_ll(register frac32_t lnum, register frac32_t lden)
{
    *((frac32_t volatile *)(MMAU__QDIV | MMAU__X2)) = lnum;
    *((frac32_t volatile *)(MMAU__QDIV | MMAU__X3)) = lden;
    return *((frac32_t volatile *)(MMAU__QDIV | MMAU__A1));
}

/*!
 * @brief   Divide two 32-bit fractional values returning a 32-bit fractional
 *          quotient.
 *
 * @details The @ref MMAU_l_divs_ll function divides two 32-bit fractional values
 *          returning a 32-bit fractional quotient.
 * @param   lnum    @ref frac32_t fractional divisor value.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac32_t fractional quotient value.
 * @note    Saturated quotient is  stored in A1 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac32_t MMAU_l_divs_ll(register frac32_t lnum, register frac32_t lden)
{
    *((frac32_t volatile *)(MMAU__QDIV | MMAU__X2 | MMAU__SAT)) = lnum;
    *((frac32_t volatile *)(MMAU__QDIV | MMAU__X3 | MMAU__SAT)) = lden;
    return *((frac32_t volatile *)(MMAU__QDIV | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Divide 64-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning saturated 32-bit
 *          fractional quotient.
 *
 * @details The @ref MMAU_l_divas_l function divides 64-bit fractional value stored
 *          in the A10 register of the MMAU by 32-bit fractional value returning
 *          a saturated 32-bit fractional quotient.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac32_t fractional quotient value.
 * @note    Saturated quotient is stored in A1 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_divas_l(register frac32_t lden)
{
    *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__X3 | MMAU__SAT)) = lden;
    return *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__A1 | MMAU__SAT));
}

/*!
 * @brief   Divide 64-bit fractional value by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 *
 * @details The @ref MMAU_d_div_dl function divides 64-bit fractional value by 32-bit
 *          fractional value returning a 64-bit fractional quotient.
 * @param   dnum    @ref frac64_t fractional divisor value.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac64_t fractional quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_div_dl(register frac64_t dnum, register frac32_t lden)
{
    *((frac64_t volatile *)(MMAU__QDIVD | MMAU__X1)) = dnum;
    *((frac32_t volatile *)(MMAU__QDIVD | MMAU__X3)) = lden;
    return *((frac64_t volatile *)(MMAU__QDIVD | MMAU__A10));
}

/*!
 * @brief   Divide 64-bit fractional value by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 *
 * @details The @ref MMAU_d_divs_dl function divides 64-bit fractional value by
 *          32-bit fractional value returning a 64-bit fractional quotient.
 * @param   dnum    @ref frac64_t fractional divisor value.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac64_t fractional quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_divs_dl(register frac64_t dnum, register frac32_t lden)
{
    *((frac64_t volatile *)(MMAU__QDIVD | MMAU__X1 | MMAU__SAT)) = dnum;
    *((frac32_t volatile *)(MMAU__QDIVD | MMAU__X3 | MMAU__SAT)) = lden;
    return *((frac64_t volatile *)(MMAU__QDIVD | MMAU__A10 | MMAU__SAT));
}

/*!
 * @brief   Divide 32-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning a 64-bit fractional quotient.
 *
 * @details The @ref MMAU_d_diva_l function divides 32-bit fractional value stored in
 *          the A10 register of the MMAU by 32-bit fractional value returning
 *          a 64-bit fractional quotient.
 * @param   lden1   @ref frac32_t fractional dividend value.
 * @return  @ref frac64_t fractional quotient value.
 * @note    Quotient is stored in A10 register of the MMAU for next computation.
 */
static inline frac64_t MMAU_d_diva_l(register frac32_t lden1)
{
    *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__X3)) = lden1;
    return *((frac64_t volatile *)(MMAU__QDIVDA | MMAU__A10));
}

/*!
 * @brief   Divide 32-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning saturated 64-bit fractional quotient.
 *
 * @details The @ref MMAU_d_divas_l function divides 32-bit fractional value stored
 *          in the A10 register of the MMAU by 32-bit fractional value returning
 *          a saturated 64-bit fractional quotient.
 * @param   lden1   @ref frac32_t fractional dividend value.
 * @return  @ref frac64_t fractional quotient value.
 * @note    Saturated quotient is  stored in A10 register of the MMAU for
 *          next computation. If saturation occurs, the instruction sets the
 *          accumulation overflow (Q) and multiply or divide overflow (V) flags
 *          to 1 in the CSR. Otherwise, it clears the Q and V flags.
 */
static inline frac64_t MMAU_d_divas_l(register frac32_t lden1)
{
    *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__X3 | MMAU__SAT)) = lden1;
    return *((frac64_t volatile *)(MMAU__QDIVDA | MMAU__A0 | MMAU__SAT));
}

/*!
 * @brief   Divide 64-bit fractional value stored in the A10 register of the
 *          MMAU by 32-bit fractional value returning a 32-bit fractional
 *          quotient.
 *
 * @details The @ref MMAU_l_diva_l function divides 64-bit fractional value stored in
 *          the A10 register of the MMAU by 32-bit fractional value returning a
 *          32-bit fractional quotient.
 * @param   lden    @ref frac32_t fractional dividend value.
 * @return  @ref frac32_t fractional quotient value.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_diva_l(register frac32_t lden)
{
    *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__X3)) = lden;
    return *((frac32_t volatile *)(MMAU__QDIVDA | MMAU__A1));
}

/*!
 * @brief   Compute and return a 32-bit fractional square root of the 32-bit
 *          fractional radicand.
 *
 * @details The @ref MMAU_l_sqr_l function computes and returns a 32-bit fractional
 *          square root of the 32-bit fractional radicand.
 * @param   lrad    @ref frac32_t fractional radicand.
 * @return  @ref frac32_t fractional square root.
 * @note    Square root is stored in A1 register of the MMAU for next
 *          computation.
 */
static inline frac32_t MMAU_l_sqr_l(register frac32_t lrad)
{
    *((frac32_t volatile *)(MMAU__QSQRD | MMAU__X2)) = 0L;
    *((frac32_t volatile *)(MMAU__QSQRD | MMAU__X3)) = lrad;
    return *((frac32_t volatile *)(MMAU__QSQRD | MMAU__A1));
}

/*!
 * @brief   Compute and return a 32-bit fractional square root of the 64-bit
 *          fractional radicand.
 *
 * @details The @ref MMAU_l_sqr_d function computes and returns a 32-bit fractional
 *          square root of the 64-bit fractional radicand.
 * @param   drad    @ref frac64_t fractional radicand.
 * @return  @ref frac32_t fractional square root.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_sqr_d(register frac64_t drad)
{
    *((frac64_t volatile *)(MMAU__QSQRD | MMAU__X2)) = drad;
    return *((frac32_t volatile *)(MMAU__QSQRD | MMAU__A1));
}

/*!
 * @brief   Compute and return a 32-bit fractional square root of the radicand
 *          stored in the A10 register of the MMAU.
 *
 * @details The @ref MMAU_l_sqra function computes and returns a 32-bit fractional
 *          square root of the radicand stored in the A10 register of the MMAU.
 * @return  @ref frac32_t fractional square root.
 * @note    Quotient is stored in A1 register of the MMAU for next computation.
 */
static inline frac32_t MMAU_l_sqra(void)
{
    return *((frac32_t volatile *)(MMAU__QSQRDA | MMAU__A1));
}
/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_MMAU_H_ */
