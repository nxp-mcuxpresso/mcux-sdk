/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FSL_EDMA_SOC_REV2_H_
#define _FSL_EDMA_SOC_REV2_H_

#include "fsl_edma_rev2.h"

#if defined(__cplusplus)
extern "C" {
#endif

static const uint32_t s_edma2RegisterLayout[] = {
    /* MP-related layout */
    [EDMA_MP_CS_INDEX] = 0x0,
    [EDMA_MP_ES_INDEX] = 0x4,
    [EDMA_MP_INT_INDEX] = 0x8,
    [EDMA_MP_HRS_INDEX] = 0xc,
    [EDMA_MP_CH_GRPRI_INDEX] = 0x100,

    /* TCD-related layout */
    [EDMA_TCD_CH_CSR_INDEX] = 0x0,
    [EDMA_TCD_CH_ES_INDEX] = 0x4,
    [EDMA_TCD_CH_INT_INDEX] = 0x8,
    [EDMA_TCD_CH_SBR_INDEX] = 0xc,
    [EDMA_TCD_CH_PRI_INDEX] = 0x10,
    [EDMA_TCD_CH_MUX_INDEX] = 0x14,
    [EDMA_TCD_SADDR_INDEX] = 0x20,
    [EDMA_TCD_SOFF_INDEX] = 0x24,
    [EDMA_TCD_ATTR_INDEX] = 0x26,
    [EDMA_TCD_NBYTES_INDEX] = 0x28,

    [EDMA_TCD_SLAST_SDA_INDEX] = 0x2c,
    [EDMA_TCD_DADDR_INDEX] = 0x30,
    [EDMA_TCD_DOFF_INDEX] = 0x34,
    [EDMA_TCD_CITER_INDEX] = 0x36,
    [EDMA_TCD_DLAST_SGA_INDEX] = 0x38,
    [EDMA_TCD_CSR_INDEX] = 0x3c,
    [EDMA_TCD_BITER_INDEX] = 0x3e,
};

static edma_config_t s_edmaConfigs[] = {
    {
        .registerLayout = s_edma2RegisterLayout,
        .regmap = 0x2d800000,
        .channels = 32,
        .channelOffset = 0x10000,
        .channelWidth = 0x10000,
        .flags = EDMA_HAS_CH_MUX_FLAG,
    },
};

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_EDMA_SOC_REV2_H_ */
