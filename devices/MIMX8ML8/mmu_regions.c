/*
 * Copyright 2020-2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "fsl_common.h"
//#include <soc.h>

#include "arm_mmu.h"

static const struct arm_mmu_region mmu_regions[] = {

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

const struct arm_mmu_config mmu_config = {
	.num_regions = ARRAY_SIZE(mmu_regions),
	.mmu_regions = mmu_regions,
};
