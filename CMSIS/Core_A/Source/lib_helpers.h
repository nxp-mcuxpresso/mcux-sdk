/*
 * Copyright (c) 2021 Carlo Caione <ccaione@baylibre.com>
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_ARCH_ARM_AARCH64_LIB_HELPERS_H_
#define ZEPHYR_INCLUDE_ARCH_ARM_AARCH64_LIB_HELPERS_H_

#ifndef _ASMLANGUAGE

#include <stdint.h>

#include "core_ca53.h"

/* All the macros need a memory clobber */

#define read_sysreg(reg)						\
({									\
	uint64_t val;							\
	__asm__ volatile ("mrs %0, " __STRINGIFY(reg)			\
			  : "=r" (val) :: "memory");			\
	val;								\
})

#define write_sysreg(val, reg)						\
({									\
	__asm__ volatile ("msr " __STRINGIFY(reg) ", %0"			\
			  :: "r" (val) : "memory");			\
})

#define zero_sysreg(reg)						\
({									\
	__asm__ volatile ("msr " __STRINGIFY(reg) ", xzr"			\
			  ::: "memory");				\
})

#define MAKE_REG_HELPER(reg)						\
	static __INLINE uint64_t read_##reg(void)			\
	{								\
		return read_sysreg(reg);				\
	}								\
	static __INLINE void write_##reg(uint64_t val)		\
	{								\
		write_sysreg(val, reg);					\
	}								\
	static __INLINE void zero_##reg(void)			\
	{								\
		zero_sysreg(reg);					\
	}

#define MAKE_REG_HELPER_EL123(reg) \
	MAKE_REG_HELPER(reg##_el1) \
	MAKE_REG_HELPER(reg##_el2) \
	MAKE_REG_HELPER(reg##_el3)

MAKE_REG_HELPER(cntfrq_el0);
MAKE_REG_HELPER(cnthctl_el2);
MAKE_REG_HELPER(cnthp_ctl_el2);
MAKE_REG_HELPER(cntv_ctl_el0)
MAKE_REG_HELPER(cntv_cval_el0)
MAKE_REG_HELPER(cntvct_el0);
MAKE_REG_HELPER(cntvoff_el2);
MAKE_REG_HELPER(currentel);
MAKE_REG_HELPER(daif)
MAKE_REG_HELPER(hcr_el2);
MAKE_REG_HELPER(id_aa64pfr0_el1);
MAKE_REG_HELPER(scr_el3);

MAKE_REG_HELPER_EL123(actlr)
MAKE_REG_HELPER_EL123(cpacr)
MAKE_REG_HELPER_EL123(cptr)
MAKE_REG_HELPER_EL123(elr)
MAKE_REG_HELPER_EL123(esr)
MAKE_REG_HELPER_EL123(far)
MAKE_REG_HELPER_EL123(mair)
MAKE_REG_HELPER_EL123(sctlr)
MAKE_REG_HELPER_EL123(spsr)
MAKE_REG_HELPER_EL123(tcr)
MAKE_REG_HELPER_EL123(ttbr0)
MAKE_REG_HELPER_EL123(vbar)

#endif /* !_ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_ARCH_ARM_AARCH64_LIB_HELPERS_H_ */
