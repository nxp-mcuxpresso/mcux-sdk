/**************************************************************************//**
 * @file     cmsis_gcc.h
 * @brief    CMSIS compiler specific macros, functions, instructions
 * @version  V1.0.0
 * @date     05. october 2021
 ******************************************************************************/
/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __FORCEINLINE
  #define __FORCEINLINE                          __attribute__((always_inline))
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif

#ifndef __STRINGIFY
  #define __STRINGIFY(x)                         #x
#endif

#ifndef __MSR
  #define __MSR(sysreg, val) \
    __asm volatile ("msr "__STRINGIFY(sysreg)", %0\n" : : "r"((uint64_t)(val)))
#endif

#ifndef __MRS
#define __MRS(sysreg, pVal) \
  __asm volatile ("mrs  %0, "__STRINGIFY(sysreg)"\n" : "=r"((*pVal)))
#endif


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */


/**
  \brief   Get Interrupt Mask Bits
  \details Returns the current state of the interrupt mask bits from the DAIF register.
  \return  Interrupt Mask value
 */
__STATIC_FORCEINLINE uint64_t __get_DAIF(void)
{
    uint64_t result;
    __MRS(DAIF, &result);
    return result;
}


/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by clearing the I-bit in the DAIF.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("msr daifclr, #2" : : : "memory");
}


/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by setting the I-bit in the DAIF.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("msr daifset, #2" : : : "memory");
}


/*@} end of CMSIS_Core_RegAccFunctions */


/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
  Access to dedicated instructions
  @{
*/


/**
  \brief   Multiprocessor Affinity
  \details Indicates the core number in the Cortex-Axx processor.
 */
__STATIC_FORCEINLINE uint32_t __get_MPIDR_EL1(void)
{
    uint32_t result;
    __MRS(MPIDR_EL1, &result);
    return result;
}

#define MPIDR_GetCoreID() (__get_MPIDR_EL1() & 0xff)

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
#ifndef __ISB
__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile ("isb":::"memory");
}
#endif

/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
#ifndef __DSB
__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb sy":::"memory");
}
#endif

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
#ifndef __DMB
__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile ("dmb sy":::"memory");
}
#endif


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state.
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
  \param [in]    value  is ignored by the processor.
                 If required, a debugger can use it to store additional information about the breakpoint.
 */
#define __BKPT(value)                       __ASM volatile ("brk "#value)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */

__STATIC_FORCEINLINE void __NOP(void)
{
  __ASM volatile ("nop");
}


/*@}*/ /* end of group CMSIS_Core_InstructionInterface */


#endif /* __CMSIS_GCC_H */
