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
#define __MRS(sysreg, val) \
  __asm volatile ("mrs  %0, "__STRINGIFY(sysreg)"\n" : "=r"((val)))
#endif

/**
  \brief   Multiprocessor Affinity
  \details Indicates the core number in the Cortex-Axx processor.
 */
__STATIC_FORCEINLINE uint32_t __get_MPIDR_EL1(void)
{
    uint32_t result;
    __MRS(MPIDR_EL1, result);
    return result;
}

#define MPIDR_GetCoreID() (__get_MPIDR_EL1() & 0xff)

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile ("isb":::"memory");
}

/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb sy":::"memory");
}

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile ("dmb sy":::"memory");
}

#endif /* __CMSIS_GCC_H */
