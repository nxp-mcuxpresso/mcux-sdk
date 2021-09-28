/*
 * Copyright 2020-2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "fsl_common.h"
//#include <soc.h>

#include "arm_mmu.h"

/* symbols defined in linker script: */
extern uintptr_t __text[];
extern uintptr_t __etext[];
extern uintptr_t __data_start__[];
extern uintptr_t __data_end__[];
extern uintptr_t __stacks_limit__[];
extern uintptr_t __stacks_top__[];
extern uintptr_t __noncachedata_start__[];
extern uintptr_t __noncachedata_end__[];
extern uintptr_t __ocramtext_start__[];
extern uintptr_t __ocramtext_end__[];
extern uintptr_t __ocramdata_start__[];
extern uintptr_t __ocramdata_end__[];
extern uintptr_t __itcm_start__[];
extern uintptr_t __itcm_end__[];
extern uintptr_t __dtcm_start__[];
extern uintptr_t __dtcm_end__[];

static const struct ARM_MMU_flat_range mmu_os_ranges[] = {

	/* Mark text/rodata segments cacheable, read only and executable */
	{ .name  = "code",
	  .start = __text,
	  .end   = __etext,
	  .attrs = MT_NORMAL | MT_P_RX_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark the execution regions (data, bss, noinit, etc.)
	 * cacheable, read-write
	 * Note: read-write region is marked execute-never internally
	 */
	{ .name  = "data",
	  .start = __data_start__,
	  .end   = __data_end__,
	  .attrs = MT_NORMAL | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark the stack regions (_el0_stack, _el1_stack)
	 * cacheable, read-write
	 * Note: read-write region is marked execute-never internally
	 */
	{ .name  = "stacks",
	  .start = __stacks_limit__,
	  .end   = __stacks_top__,
	  .attrs = MT_NORMAL | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark the shared regions (non-cacheable data)
	 * noncacheable, read-write
	 * Note: read-write region is marked execute-never internally
	 */
	{ .name  = "data_nc",
	  .start = __noncachedata_start__,
	  .end   = __noncachedata_end__,
	  .attrs = MT_NORMAL_NC	| MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark text/rodata segments cacheable, read only and executable */
	{ .name  = "ocram_code",
	  .start = __ocramtext_start__,
	  .end   = __ocramtext_end__,
	  .attrs = MT_NORMAL | MT_P_RX_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark the data regions cacheable, read-write
	 * Note: read-write region is marked execute-never internally
	 */
	{ .name  = "ocram_data",
	  .start = __ocramdata_start__,
	  .end   = __ocramdata_end__,
	  .attrs = MT_NORMAL | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark text/rodata segments cacheable, read only and executable */
	{ .name  = "itcm",
	  .start = __itcm_start__,
	  .end   = __itcm_end__,
	  .attrs = MT_NORMAL | MT_P_RX_U_NA | MT_DEFAULT_SECURE_STATE },

	/* Mark the data regions cacheable, read-write
	 * Note: read-write region is marked execute-never internally
	 */
	{ .name  = "dtcm",
	  .start = __dtcm_start__,
	  .end   = __dtcm_end__,
	  .attrs = MT_NORMAL | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE },
};

static const struct ARM_MMU_region mmu_regions[] = {

	MMU_REGION_FLAT_ENTRY("GPT1",
			      0x302d0000, KB(64),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("GPT2",
			      0x302e0000, KB(64),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("ANA_PLL",
			      0x30360000, KB(64),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("CCM",
			      0x30380000, KB(64),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("UART2",
			      0x30890000, KB(4),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("UART4",
			      0x30a60000, KB(4),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("GIC",
			      0x38800000, MB(1),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

};

const struct ARM_MMU_config MMU_config = {
	.num_regions = ARRAY_SIZE(mmu_regions),
	.mmu_regions = mmu_regions,
	.num_os_ranges = ARRAY_SIZE(mmu_os_ranges),
	.mmu_os_ranges = mmu_os_ranges,
};
