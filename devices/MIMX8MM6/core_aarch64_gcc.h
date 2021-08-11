/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CORE_AARCH64_GCC_H
#define __CORE_AARCH64_GCC_H

#define CORE_SYSREG(op1, crn, crm, op2) s3_##op1 ##_##crn ##_##crm ##_##op2

#ifndef MPIDR_EL1
#define MPIDR_EL1        CORE_SYSREG(0, c0, c0, 5)
#endif
#ifndef TTBR0_EL1
#define TTBR0_EL1        CORE_SYSREG(0, c2, c0, 0)
#endif
#ifndef TTBR1_EL1
#define TTBR1_EL1        CORE_SYSREG(0, c2, c0, 1)
#endif
#ifndef TCR_EL1
#define TCR_EL1          CORE_SYSREG(0, c2, c0, 2)
#endif
#ifndef SCTLR_EL1
#define SCTLR_EL1        CORE_SYSREG(0, c1, c0, 0)
#endif
#ifndef MAIR_EL1
#define MAIR_EL1         CORE_SYSREG(0, c10, c2, 0)
#endif

#ifndef ICC_IAR1_EL1
#define ICC_IAR1_EL1     CORE_SYSREG(0, c12, c12, 0)
#endif
#ifndef ICC_EOIR1_EL1
#define ICC_EOIR1_EL1    CORE_SYSREG(0, c12, c12, 1)
#endif
#ifndef ICC_HPPIR1_EL1
#define ICC_HPPIR1_EL1   CORE_SYSREG(0, c12, c12, 2)
#endif
#ifndef ICC_BPR1_EL1
#define ICC_BPR1_EL1     CORE_SYSREG(0, c12, c12, 3)
#endif
#ifndef ICC_DIR_EL1
#define ICC_DIR_EL1      CORE_SYSREG(0, c12, c11, 1)
#endif
#ifndef ICC_PMR_EL1
#define ICC_PMR_EL1      CORE_SYSREG(0, c4, c6, 0)
#endif
#ifndef ICC_RPR_EL1
#define ICC_RPR_EL1      CORE_SYSREG(0, c12, c11, 3)
#endif
#ifndef ICC_CTLR_EL1
#define ICC_CTLR_EL1     CORE_SYSREG(0, c12, c12, 4)
#endif
#ifndef ICC_SRE_EL1
#define ICC_SRE_EL1      CORE_SYSREG(0, c12, c12, 5)
#endif
#ifndef ICC_SRE_EL2
#define ICC_SRE_EL2      CORE_SYSREG(4, c12, c9, 5)
#endif
#ifndef ICC_IGRPEN1_EL1
#define ICC_IGRPEN1_EL1  CORE_SYSREG(0, c12, c12, 7)
#endif
#ifndef ICC_AP1R0_EL1
#define ICC_AP1R0_EL1    CORE_SYSREG(0, c12, c9, 0)
#endif
#ifndef ICC_AP1R1_EL1
#define ICC_AP1R1_EL1    CORE_SYSREG(0, c12, c9, 1)
#endif
#ifndef ICC_AP1R2_EL1
#define ICC_AP1R2_EL1    CORE_SYSREG(0, c12, c9, 2)
#endif
#ifndef ICC_AP1R3_EL1
#define ICC_AP1R3_EL1    CORE_SYSREG(0, c12, c9, 3)
#endif

#define __CORE_stringify_1(x...)     #x
#define __CORE_stringify(x...)       __CORE_stringify_1(x)

#ifndef __MSR
#define __MSR(sysreg, val) \
  __asm volatile ("msr "__CORE_stringify(sysreg)", %0\n" : : "r"((uint64_t)(val)))
#endif

#ifndef __MRS
#define __MRS(sysreg, val) \
  __asm volatile ("mrs  %0, "__CORE_stringify(sysreg)"\n" : "=r"((val)))
#endif

#ifndef __DSB_SY
#define __DSB_SY() \
  __asm volatile ("dsb sy")
#endif

#ifndef __ISB
#define __ISB() \
  __asm volatile ("isb")
#endif

#ifndef __NOP
#define __NOP() \
  __asm volatile ("nop")
#endif

#ifndef __B
#define __B() \
  __asm volatile ("b .")
#endif

#ifndef __TLBI
#define __TLBI() \
  __asm volatile("dsb ishst\n"     \
               "tlbi vmalle1\n"  \
               "dsb sy\n"        \
               "isb\n")
#endif


FORCEDINLINE __STATIC_INLINE uint32_t __get_MPIDR_EL1(void)
{
    uint32_t result;
    __MRS(MPIDR_EL1, result);
    return result;
}

/* backward compatibility */
#define MPIDR_GetCoreID() (__get_MPIDR_EL1() & 0xff)

#endif /* __CORE_AARCH64_GCC_H */
