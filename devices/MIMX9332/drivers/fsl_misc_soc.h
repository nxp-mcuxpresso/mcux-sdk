/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MISC_SOC_H_
#define _FSL_MISC_SOC_H_
#include "fsl_common.h"
/*!
 * @addtogroup misc_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_MISC_SOC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#ifndef BIT
#define BIT(x) (1U << x)
#endif

#define SOC_SRC_IPS_BASE_ADDR (0x44460000)
#define SOC_SRC_GLOBAL_RBASE  (SOC_SRC_IPS_BASE_ADDR + 0x0000)

typedef enum
{
    SOC_MIX_PD_MEDIAMIX,
    SOC_MIX_PD_MLMIX,
    SOC_MIX_PD_DDRMIX,
} soc_mix_power_domain_e;

typedef enum
{
    SOC_SRC_MIX_EDGELOCK    = 0,
    SOC_SRC_MIX_AONMIX      = 1,
    SOC_SRC_MIX_WAKEUPMIX   = 2,
    SOC_SRC_MIX_DDRMIX      = 3,
    SOC_SRC_MIX_DDRPHY      = 4,
    SOC_SRC_MIX_ML          = 5,
    SOC_SRC_MIX_NIC         = 6,
    SOC_SRC_MIX_HSIO        = 7,
    SOC_SRC_MIX_MEDIA       = 8,
    SOC_SRC_MIX_CM33        = 9,
    SOC_SRC_MIX_CA55C0      = 10,
    SOC_SRC_MIX_CA55C1      = 11,
    SOC_SRC_MIX_CA55CLUSTER = 12,
} soc_src_mix_slice_id_e;

typedef enum
{
    SOC_SRC_MEM_AONMIX      = 0,
    SOC_SRC_MEM_WAKEUPMIX   = 1,
    SOC_SRC_MEM_DDRMIX      = 2,
    SOC_SRC_MEM_DDRPHY      = 3,
    SOC_SRC_MEM_ML          = 4,
    SOC_SRC_MEM_NIC         = 5,
    SOC_SRC_MEM_OCRAM       = 6,
    SOC_SRC_MEM_HSIO        = 7,
    SOC_SRC_MEM_MEDIA       = 8,
    SOC_SRC_MEM_CA55C0      = 9,
    SOC_SRC_MEM_CA55C1      = 10,
    SOC_SRC_MEM_CA55CLUSTER = 11,
    SOC_SRC_MEM_L3          = 12,
} soc_src_mem_slice_id_e;

typedef struct
{
    uint32_t reserved[1];
    uint32_t authen_ctrl;
    uint32_t reserved1[2];
    uint32_t scr;
    uint32_t srtmr;
    uint32_t srmask;
    uint32_t reserved2[1];
    uint32_t srmr[6];
    uint32_t reserved3[2];
    uint32_t sbmr[2];
    uint32_t reserved4[2];
    uint32_t srsr;
    uint32_t gpr[19];
    uint32_t reserved5[24];
    uint32_t gpr20;
    uint32_t cm_quiesce;
    uint32_t cold_reset_ssar_ack_ctrl;
    uint32_t sp_iso_ctrl;
    uint32_t rom_lp_ctrl;
    uint32_t a55_deny_stat;
} soc_src_general_regs_t;

typedef struct
{
    uint32_t reserved[1];
    uint32_t mem_ctrl;
    uint32_t memlp_ctrl_0;
    uint32_t reserved1[1];
    uint32_t memlp_ctrl_1;
    uint32_t memlp_ctrl_2;
    uint32_t mem_stat;
} soc_src_mem_slice_regs_t;
#endif /* _FSL_CLOCK_H_ */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int SOC_MixPowerInit(soc_mix_power_domain_e pwr_dom);
void SOC_DisableIsolation(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */
