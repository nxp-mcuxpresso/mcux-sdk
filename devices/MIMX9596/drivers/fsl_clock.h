/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#ifndef CONFIG_CLOCK_CONTROL_IMX_SCMI
#include "hal_clock.h"
#include "fsl_common.h"

/*!
 * @brief CCM reg macros to map corresponding registers.
 */
#define CCM_REG_OFF(root, off) (*((volatile uint32_t *)((uintptr_t)(root) + (off))))
#define CCM_REG(root)          CCM_REG_OFF(root, 0U)

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY \
    (250000000UL) /* When using Overdrive Voltage, the maximum frequency of cm33 is 250 MHz */
#endif

/*******************************************************************************
 * PLL Definitions
 ******************************************************************************/

/*! @brief PLL initialzation data. */
typedef struct _fracn_pll_init
{
    uint32_t rdiv;
    uint32_t mfi;
    uint32_t mfn;
    uint32_t mfd;
    uint32_t odiv;
} fracn_pll_init_t;

/*! @brief PLL PFD initialzation data. */
typedef struct _fracn_pll_pfd_init
{
    uint32_t mfi;
    uint32_t mfn;
    bool div2_en;
} fracn_pll_pfd_init_t;

/*******************************************************************************
 * Clock Source Definitions
 ******************************************************************************/
#define kCLOCK_IpInvalid 0U

/*!
 * @brief Clock name.
 */
typedef enum _clock_name
{
    kCLOCK_Ext             = 0,  /* EXT_CLK */
    kCLOCK_Osc32K          = 1,  /* OSC_32K_CLK */
    kCLOCK_Osc24M          = 2,  /* OSC_24M_CLK */
    kCLOCK_Fro             = 3,  /* FRO_CLK */
    kCLOCK_SysPll1Ctl      = 4,  /* SYS_PLL1_CTL */
    kCLOCK_SysPll1Dfs0Ctl  = 5,  /* SYS_PLL1_DFS0_CTL */
    kCLOCK_SysPll1Dfs0     = 6,  /* SYS_PLL1_DFS0_CLK */
    kCLOCK_SysPll1Dfs0Div2 = 7,  /* SYS_PLL1_DFS0_DIV2_CLK */
    kCLOCK_SysPll1Dfs1Ctl  = 8,  /* SYS_PLL1_DFS1_CTL */
    kCLOCK_SysPll1Dfs1     = 9,  /* SYS_PLL1_DFS1_CLK */
    kCLOCK_SysPll1Dfs1Div2 = 10, /* SYS_PLL1_DFS1_DIV2_CLK */
    kCLOCK_SysPll1Dfs2Ctl  = 11, /* SYS_PLL1_DFS2_CTL */
    kCLOCK_SysPll1Dfs2     = 12, /* SYS_PLL1_DFS2_CLK */
    kCLOCK_SysPll1Dfs2Div2 = 13, /* SYS_PLL1_DFS2_DIV2_CLK */
    kCLOCK_AudioPll1Ctl    = 14, /* AUDIO_PLL1_CTL */
    kCLOCK_AudioPll1       = 15, /* AUDIO_PLL1_CLK */
    kCLOCK_AudioPll2Ctl    = 16, /* AUDIO_PLL2_CTL */
    kCLOCK_AudioPll2       = 17, /* AUDIO_PLL2_CLK */
    kCLOCK_VideoPll1Ctl    = 18, /* VIDEO_PLL1_CTL */
    kCLOCK_VideoPll1       = 19, /* VIDEO_PLL1_CLK */
    kCLOCK_VideoPll2Ctl    = 20, /* VIDEO_PLL2_CTL */
    kCLOCK_VideoPll2       = 21, /* VIDEO_PLL2_CLK */
    kCLOCK_VideoPll3Ctl    = 22, /* VIDEO_PLL3_CTL */
    kCLOCK_VideoPll3       = 23, /* VIDEO_PLL3_CLK */
    kCLOCK_ArmPllCtl       = 24, /* ARM_PLL_CTL */
    kCLOCK_ArmPllDfs0Ctl   = 25, /* ARM_PLL_DFS0_CTL */
    kCLOCK_ArmPllDfs0      = 26, /* ARM_PLL_DFS0_CLK */
    kCLOCK_ArmPllDfs1Ctl   = 27, /* ARM_PLL_DFS1_CTL */
    kCLOCK_ArmPllDfs1      = 28, /* ARM_PLL_DFS1_CLK */
    kCLOCK_ArmPllDfs2Ctl   = 29, /* ARM_PLL_DFS2_CTL */
    kCLOCK_ArmPllDfs2      = 30, /* ARM_PLL_DFS2_CLK */
    kCLOCK_ArmPllDfs3Ctl   = 31, /* ARM_PLL_DFS3_CTL */
    kCLOCK_ArmPllDfs3      = 32, /* ARM_PLL_DFS3_CLK */
    kCLOCK_DramPllCtl      = 33, /* DRAM_PLL_CTL */
    kCLOCK_DramPll         = 34, /* DRAM_PLL_CLK */
    kCLOCK_HsioPllCtl      = 35, /* HSIO_PLL_CTL */
    kCLOCK_HsioPll         = 36, /* HSIO_PLL_CLK */
    kCLOCK_LdbPllCtl       = 37, /* LDB_PLL_CTL */
    kCLOCK_LdbPll          = 38, /* LDB_PLL_CLK */
} clock_name_t;

static const clock_name_t s_clockSourceName[][4] = {
    /*   SRC0,         SRC1,                   SRC2,                   SRC3,            */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* adc_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* tmu_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* bus_aon_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* can1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* i3c1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* i3c1_slow_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lptmr1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro},     /* m33_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* m33_systick_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* mqs1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* pdm_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* sai1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro},     /* sentinel_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_AudioPll1, kCLOCK_Ext},           /* tpm2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* tstmr1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* cam_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* cam_axi_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* cam_cm0_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* cam_isi_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_VideoPll1},       /* mipi_phy_cfg_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_VideoPll1},       /* mipi_phy_pll_bypass_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_VideoPll1},       /* mipi_phy_pll_ref_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_VideoPll1},       /* mipi_test_byte_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* arm_a55_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* arm_a55_mtr_bus_clk_root  */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* arm_a55_periph_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* dram_alt_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* dram_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* disp_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* disp_axi_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* disp_dp_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* disp_ocram_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* disp_usb31_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_VideoPll1},       /* disp1_pix_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll2, kCLOCK_SysPll1Dfs2},     /* disp2_pix_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll3, kCLOCK_SysPll1Dfs2},     /* disp3_pix_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* gpu_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* gpu_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_VideoPll1, kCLOCK_SysPll1Dfs2},     /* hsio_acscan_480m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* hsio_acscan_80m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* hsio_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* hsio_pcie_aux_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* hsio_pcie_test_160m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* hsio_pcie_test_400m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* hsio_pcie_test_500m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* hsio_usb_test_50m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* hsio_usb_test_60m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* bus_m7_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* m7_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* m7_systick_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* bus_netcmix_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* enet_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro},     /* enet_phy_test_200m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* enet_phy_test_500m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* enet_phy_test_667m_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro},     /* enet_ref_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* enet_timer1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* mqs2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* sai2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* noc_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* noc_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* npu_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* npu_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_Osc32K, kCLOCK_AudioPll1},        /* ccm_cko1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_Osc32K, kCLOCK_VideoPll1},        /* ccm_cko2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_Osc32K, kCLOCK_AudioPll2},        /* ccm_cko3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_Osc32K, kCLOCK_VideoPll1},        /* ccm_cko4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* vpu_apb_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* vpu_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* vpu_dsp_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* vpu_jpeg_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro},     /* audio_xcvr_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* bus_wakeup_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* can2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* can3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* can4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* can5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* flexio1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* flexio2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* flexspi1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* i3c2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* i3c2_slow_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c6_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c7_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpi2c8_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi6_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi7_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpspi8_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lptmr2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart6_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart7_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* lpuart8_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* sai3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* sai4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* sai5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1, kCLOCK_AudioPll2, kCLOCK_Ext},             /* spdif_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* swo_trace_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_AudioPll1, kCLOCK_Ext},           /* tpm4_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_AudioPll1, kCLOCK_Ext},           /* tpm5_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_AudioPll1, kCLOCK_Ext},           /* tpm6_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* tstmr2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0Div2, kCLOCK_SysPll1Dfs1Div2, kCLOCK_Fro}, /* usb_phy_burunin_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* usdhc1_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* usdhc2_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* usdhc3_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* v2x_pk_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}, /* wakeup_axi_clk_root */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Dfs0, kCLOCK_SysPll1Dfs1, kCLOCK_SysPll1Dfs2}  /* xspi_slv_root_clk_root */
};

/*******************************************************************************
 * Clock Root Definitions
 ******************************************************************************/

/*! @brief Clock root configuration */
typedef struct _clock_root_config_t
{
    bool clockOff;
    uint8_t mux; /*!< See #clock_root_mux_source_t for details. */
    uint8_t div; /*!< it's the actual divider */
} clock_root_config_t;

/*!
 * @brief Root clock index
 */
typedef enum _clock_root
{
    kCLOCK_Root_Adc              = 0,   /* CLOCK Root Adc */
    kCLOCK_Root_Tmu              = 1,   /* CLOCK Root Tmu */
    kCLOCK_Root_BusAon           = 2,   /* CLOCK Root Bus Aon */
    kCLOCK_Root_Can1             = 3,   /* CLOCK Root Can1 */
    kCLOCK_Root_I3c1             = 4,   /* CLOCK Root I3C1 */
    kCLOCK_Root_I3c1Slow         = 5,   /* CLOCK Root I3C1 Slow */
    kCLOCK_Root_Lpi2c1           = 6,   /* CLOCK Root Lpi2C1 */
    kCLOCK_Root_Lpi2c2           = 7,   /* CLOCK Root Lpi2C2 */
    kCLOCK_Root_Lpspi1           = 8,   /* CLOCK Root Lpspi1 */
    kCLOCK_Root_Lpspi2           = 9,   /* CLOCK Root Lpspi2 */
    kCLOCK_Root_Lptmr1           = 10,  /* CLOCK Root Lptmr1 */
    kCLOCK_Root_Lpuart1          = 11,  /* CLOCK Root Lpuart1 */
    kCLOCK_Root_Lpuart2          = 12,  /* CLOCK Root Lpuart2 */
    kCLOCK_Root_M33              = 13,  /* CLOCK Root M33 */
    kCLOCK_Root_M33Systick       = 14,  /* CLOCK Root M33 Systick */
    kCLOCK_Root_Mqs1             = 15,  /* CLOCK Root Mqs1 */
    kCLOCK_Root_Pdm              = 16,  /* CLOCK Root Pdm */
    kCLOCK_Root_Sai1             = 17,  /* CLOCK Root Sai1 */
    kCLOCK_Root_Sentinel         = 18,  /* CLOCK Root Sentinel */
    kCLOCK_Root_Tpm2             = 19,  /* CLOCK Root Tpm2 */
    kCLOCK_Root_Tstmr1           = 20,  /* CLOCK Root Tstmr1 */
    kCLOCK_Root_CamApb           = 21,  /* CLOCK Root Cam Apb */
    kCLOCK_Root_CamAxi           = 22,  /* CLOCK Root Cam Axi */
    kCLOCK_Root_CamCm0           = 23,  /* CLOCK Root Cam Cm0 */
    kCLOCK_Root_CamIsi           = 24,  /* CLOCK Root Cam Isi */
    kCLOCK_Root_MipiPhyCfg       = 25,  /* CLOCK Root Mipi Phy Cfg */
    kCLOCK_Root_MipiPhyPllBypass = 26,  /* CLOCK Root Mipi Phy Pll Bypass */
    kCLOCK_Root_MipiPhyPllRef    = 27,  /* CLOCK Root Mipi Phy Pll Ref */
    kCLOCK_Root_MipiTestByte     = 28,  /* CLOCK Root Mipi Test Byte */
    kCLOCK_Root_A55              = 29,  /* CLOCK Root Arm A55 */
    kCLOCK_Root_A55MtrBus        = 30,  /* CLOCK Root Arm A55 Mtr Bus  */
    kCLOCK_Root_A55Periph        = 31,  /* CLOCK Root Arm A55 Periph */
    kCLOCK_Root_DramAlt          = 32,  /* CLOCK Root Dram Alt */
    kCLOCK_Root_DramApb          = 33,  /* CLOCK Root Dram Apb */
    kCLOCK_Root_DispApb          = 34,  /* CLOCK Root Disp Apb */
    kCLOCK_Root_DispAxi          = 35,  /* CLOCK Root Disp Axi */
    kCLOCK_Root_DispDp           = 36,  /* CLOCK Root Disp Dp */
    kCLOCK_Root_DispOcram        = 37,  /* CLOCK Root Disp Ocram */
    kCLOCK_Root_DispUsb31        = 38,  /* CLOCK Root Disp Usb31 */
    kCLOCK_Root_Disp1Pix         = 39,  /* CLOCK Root Disp1 Pix */
    kCLOCK_Root_Disp2Pix         = 40,  /* CLOCK Root Disp2 Pix */
    kCLOCK_Root_Disp3Pix         = 41,  /* CLOCK Root Disp3 Pix */
    kCLOCK_Root_GpuApb           = 42,  /* CLOCK Root Gpu Apb */
    kCLOCK_Root_Gpu              = 43,  /* CLOCK Root Gpu */
    kCLOCK_Root_HsioAcscan480M   = 44,  /* CLOCK Root Hsio Acscan 480M */
    kCLOCK_Root_HsioAcscan80M    = 45,  /* CLOCK Root Hsio Acscan 80M */
    kCLOCK_Root_Hsio             = 46,  /* CLOCK Root Hsio */
    kCLOCK_Root_HsioPcieAux      = 47,  /* CLOCK Root Hsio Pcie Aux */
    kCLOCK_Root_HsioPcieTest160M = 48,  /* CLOCK Root Hsio Pcie Test 160M */
    kCLOCK_Root_HsioPcieTest400M = 49,  /* CLOCK Root Hsio Pcie Test 400M */
    kCLOCK_Root_HsioPcieTest500M = 50,  /* CLOCK Root Hsio Pcie Test 500M */
    kCLOCK_Root_HsioUsbTest50M   = 51,  /* CLOCK Root Hsio Usb Test 50M */
    kCLOCK_Root_HsioUsbTest60M   = 52,  /* CLOCK Root Hsio Usb Test 60M */
    kCLOCK_Root_BusM7            = 53,  /* CLOCK Root Bus M7 */
    kCLOCK_Root_M7               = 54,  /* CLOCK Root M7 */
    kCLOCK_Root_M7Systick        = 55,  /* CLOCK Root M7 Systick */
    kCLOCK_Root_BusNetcmix       = 56,  /* CLOCK Root Bus Netcmix */
    kCLOCK_Root_Enet             = 57,  /* CLOCK Root Enet */
    kCLOCK_Root_EnetPhyTest200M  = 58,  /* CLOCK Root Enet Phy Test 200M */
    kCLOCK_Root_EnetPhyTest500M  = 59,  /* CLOCK Root Enet Phy Test 500M */
    kCLOCK_Root_EnetPhyTest667M  = 60,  /* CLOCK Root Enet Phy Test 667M */
    kCLOCK_Root_EnetRef          = 61,  /* CLOCK Root Enet Ref */
    kCLOCK_Root_EnetTimer1       = 62,  /* CLOCK Root Enet Timer1 */
    kCLOCK_Root_Mqs2             = 63,  /* CLOCK Root Mqs2 */
    kCLOCK_Root_Sai2             = 64,  /* CLOCK Root Sai2 */
    kCLOCK_Root_NocApb           = 65,  /* CLOCK Root Noc Apb */
    kCLOCK_Root_Noc              = 66,  /* CLOCK Root Noc */
    kCLOCK_Root_NpuApb           = 67,  /* CLOCK Root Npu Apb */
    kCLOCK_Root_Npu              = 68,  /* CLOCK Root Npu */
    kCLOCK_Root_CcmCko1          = 69,  /* CLOCK Root Ccm Cko1 */
    kCLOCK_Root_CcmCko2          = 70,  /* CLOCK Root Ccm Cko2 */
    kCLOCK_Root_CcmCko3          = 71,  /* CLOCK Root Ccm Cko3 */
    kCLOCK_Root_CcmCko4          = 72,  /* CLOCK Root Ccm Cko4 */
    kCLOCK_Root_VpuApb           = 73,  /* CLOCK Root Vpu Apb */
    kCLOCK_Root_Vpu              = 74,  /* CLOCK Root Vpu */
    kCLOCK_Root_VpuDsp           = 75,  /* CLOCK Root Vpu Dsp */
    kCLOCK_Root_VpuJpeg          = 76,  /* CLOCK Root Vpu Jpeg */
    kCLOCK_Root_AudioXcvr        = 77,  /* CLOCK Root Audio Xcvr */
    kCLOCK_Root_BusWakeup        = 78,  /* CLOCK Root Bus Wakeup */
    kCLOCK_Root_Can2             = 79,  /* CLOCK Root Can2 */
    kCLOCK_Root_Can3             = 80,  /* CLOCK Root Can3 */
    kCLOCK_Root_Can4             = 81,  /* CLOCK Root Can4 */
    kCLOCK_Root_Can5             = 82,  /* CLOCK Root Can5 */
    kCLOCK_Root_Flexio1          = 83,  /* CLOCK Root Flexio1 */
    kCLOCK_Root_Flexio2          = 84,  /* CLOCK Root Flexio2 */
    kCLOCK_Root_Flexspi1         = 85,  /* CLOCK Root Flexspi1 */
    kCLOCK_Root_I3c2             = 86,  /* CLOCK Root I3C2 */
    kCLOCK_Root_I3c2Slow         = 87,  /* CLOCK Root I3C2 Slow */
    kCLOCK_Root_Lpi2c3           = 88,  /* CLOCK Root Lpi2C3 */
    kCLOCK_Root_Lpi2c4           = 89,  /* CLOCK Root Lpi2C4 */
    kCLOCK_Root_Lpi2c5           = 90,  /* CLOCK Root Lpi2C5 */
    kCLOCK_Root_Lpi2c6           = 91,  /* CLOCK Root Lpi2C6 */
    kCLOCK_Root_Lpi2c7           = 92,  /* CLOCK Root Lpi2C7 */
    kCLOCK_Root_Lpi2c8           = 93,  /* CLOCK Root Lpi2C8 */
    kCLOCK_Root_Lpspi3           = 94,  /* CLOCK Root Lpspi3 */
    kCLOCK_Root_Lpspi4           = 95,  /* CLOCK Root Lpspi4 */
    kCLOCK_Root_Lpspi5           = 96,  /* CLOCK Root Lpspi5 */
    kCLOCK_Root_Lpspi6           = 97,  /* CLOCK Root Lpspi6 */
    kCLOCK_Root_Lpspi7           = 98,  /* CLOCK Root Lpspi7 */
    kCLOCK_Root_Lpspi8           = 99,  /* CLOCK Root Lpspi8 */
    kCLOCK_Root_Lptmr2           = 100, /* CLOCK Root Lptmr2 */
    kCLOCK_Root_Lpuart3          = 101, /* CLOCK Root Lpuart3 */
    kCLOCK_Root_Lpuart4          = 102, /* CLOCK Root Lpuart4 */
    kCLOCK_Root_Lpuart5          = 103, /* CLOCK Root Lpuart5 */
    kCLOCK_Root_Lpuart6          = 104, /* CLOCK Root Lpuart6 */
    kCLOCK_Root_Lpuart7          = 105, /* CLOCK Root Lpuart7 */
    kCLOCK_Root_Lpuart8          = 106, /* CLOCK Root Lpuart8 */
    kCLOCK_Root_Sai3             = 107, /* CLOCK Root Sai3 */
    kCLOCK_Root_Sai4             = 108, /* CLOCK Root Sai4 */
    kCLOCK_Root_Sai5             = 109, /* CLOCK Root Sai5 */
    kCLOCK_Root_Spdif            = 110, /* CLOCK Root Spdif */
    kCLOCK_Root_SwoTrace         = 111, /* CLOCK Root Swo Trace */
    kCLOCK_Root_Tpm4             = 112, /* CLOCK Root Tpm4 */
    kCLOCK_Root_Tpm5             = 113, /* CLOCK Root Tpm5 */
    kCLOCK_Root_Tpm6             = 114, /* CLOCK Root Tpm6 */
    kCLOCK_Root_Tstmr2           = 115, /* CLOCK Root Tstmr2 */
    kCLOCK_Root_UsbPhyBurunin    = 116, /* CLOCK Root Usb Phy Burunin */
    kCLOCK_Root_Usdhc1           = 117, /* CLOCK Root Usdhc1 */
    kCLOCK_Root_Usdhc2           = 118, /* CLOCK Root Usdhc2 */
    kCLOCK_Root_Usdhc3           = 119, /* CLOCK Root Usdhc3 */
    kCLOCK_Root_V2XPk            = 120, /* CLOCK Root V2X Pk */
    kCLOCK_Root_WakeupAxi        = 121, /* CLOCK Root Wakeup Axi */
    kCLOCK_Root_XspiSlvRoot      = 122  /* CLOCK Root Xspi Slv Root */
} clock_root_t;

/*!
 * @brief The enumerator of clock roots' clock source mux value.
 */
typedef enum _clock_root_mux_source
{
    /* adc_clk_root */
    kCLOCK_ADC_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ADC_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_ADC_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_ADC_ClockRoot_MuxFro             = 3U,

    /* tmu_clk_root */
    kCLOCK_TMU_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_TMU_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_TMU_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_TMU_ClockRoot_MuxFro             = 3U,

    /* bus_aon_clk_root */
    kCLOCK_BUSAON_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSAON_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_BUSAON_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_BUSAON_ClockRoot_MuxFro             = 3U,

    /* can1_clk_root */
    kCLOCK_CAN1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAN1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAN1_ClockRoot_MuxFro             = 3U,

    /* i3c1_clk_root */
    kCLOCK_I3C1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_I3C1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_I3C1_ClockRoot_MuxFro             = 3U,

    /* i3c1_slow_clk_root */
    kCLOCK_I3C1SLOW_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_I3C1SLOW_ClockRoot_MuxFro             = 3U,

    /* lpi2c1_clk_root */
    kCLOCK_LPI2C1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C1_ClockRoot_MuxFro             = 3U,

    /* lpi2c2_clk_root */
    kCLOCK_LPI2C2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C2_ClockRoot_MuxFro             = 3U,

    /* lpspi1_clk_root */
    kCLOCK_LPSPI1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI1_ClockRoot_MuxFro             = 3U,

    /* lpspi2_clk_root */
    kCLOCK_LPSPI2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI2_ClockRoot_MuxFro             = 3U,

    /* lptmr1_clk_root */
    kCLOCK_LPTMR1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPTMR1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPTMR1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPTMR1_ClockRoot_MuxFro             = 3U,

    /* lpuart1_clk_root */
    kCLOCK_LPUART1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART1_ClockRoot_MuxFro             = 3U,

    /* lpuart2_clk_root */
    kCLOCK_LPUART2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART2_ClockRoot_MuxFro             = 3U,

    /* m33_clk_root */
    kCLOCK_M33_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_M33_ClockRoot_MuxSysPll1Dfs0     = 1U,
    kCLOCK_M33_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_M33_ClockRoot_MuxFro             = 3U,

    /* m33_systick_clk_root */
    kCLOCK_M33SYSTICK_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_M33SYSTICK_ClockRoot_MuxFro             = 3U,

    /* mqs1_clk_root */
    kCLOCK_MQS1_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MQS1_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MQS1_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_MQS1_ClockRoot_MuxExt       = 3U,

    /* pdm_clk_root */
    kCLOCK_PDM_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_PDM_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_PDM_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_PDM_ClockRoot_MuxExt       = 3U,

    /* sai1_clk_root */
    kCLOCK_SAI1_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SAI1_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SAI1_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SAI1_ClockRoot_MuxExt       = 3U,

    /* sentinel_clk_root */
    kCLOCK_SENTINEL_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_SENTINEL_ClockRoot_MuxSysPll1Dfs0     = 1U,
    kCLOCK_SENTINEL_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_SENTINEL_ClockRoot_MuxFro             = 3U,

    /* tpm2_clk_root */
    kCLOCK_TPM2_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_TPM2_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_TPM2_ClockRoot_MuxAudioPll1   = 2U,
    kCLOCK_TPM2_ClockRoot_MuxExt         = 3U,

    /* tstmr1_clk_root */
    kCLOCK_TSTMR1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_TSTMR1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_TSTMR1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_TSTMR1_ClockRoot_MuxFro             = 3U,

    /* cam_apb_clk_root */
    kCLOCK_CAMAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAMAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAMAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAMAPB_ClockRoot_MuxFro             = 3U,

    /* cam_axi_clk_root */
    kCLOCK_CAMAXI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CAMAXI_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CAMAXI_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_CAMAXI_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* cam_cm0_clk_root */
    kCLOCK_CAMCM0_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CAMCM0_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CAMCM0_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_CAMCM0_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* cam_isi_clk_root */
    kCLOCK_CAMISI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CAMISI_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CAMISI_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_CAMISI_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* mipi_phy_cfg_clk_root */
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MIPIPHYCFG_ClockRoot_MuxVideoPll1 = 2U,

    /* mipi_phy_pll_bypass_clk_root */
    kCLOCK_MIPIPHYPLLBYPASS_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MIPIPHYPLLBYPASS_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MIPIPHYPLLBYPASS_ClockRoot_MuxVideoPll1 = 2U,

    /* mipi_phy_pll_ref_clk_root */
    kCLOCK_MIPIPHYPLLREF_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MIPIPHYPLLREF_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MIPIPHYPLLREF_ClockRoot_MuxVideoPll1 = 2U,

    /* mipi_test_byte_clk_root */
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MIPITESTBYTE_ClockRoot_MuxVideoPll1 = 2U,

    /* arm_a55_clk_root */
    kCLOCK_A55_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_A55_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* arm_a55_mtr_bus_clk_root  */
    kCLOCK_A55MTRBUS_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_A55MTRBUS_ClockRoot_MuxFro             = 3U,

    /* arm_a55_periph_clk_root */
    kCLOCK_A55PERIPH_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_A55PERIPH_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* dram_alt_clk_root */
    kCLOCK_DRAMALT_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_DRAMALT_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* dram_apb_clk_root */
    kCLOCK_DRAMAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_DRAMAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_DRAMAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_DRAMAPB_ClockRoot_MuxFro             = 3U,

    /* disp_apb_clk_root */
    kCLOCK_DISPAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_DISPAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_DISPAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_DISPAPB_ClockRoot_MuxFro             = 3U,

    /* disp_axi_clk_root */
    kCLOCK_DISPAXI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISPAXI_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_DISPAXI_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_DISPAXI_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* disp_dp_clk_root */
    kCLOCK_DISPDP_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISPDP_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_DISPDP_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_DISPDP_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* disp_ocram_clk_root */
    kCLOCK_DISPOCRAM_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISPOCRAM_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_DISPOCRAM_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_DISPOCRAM_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* disp_usb31_clk_root */
    kCLOCK_DISPUSB31_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISPUSB31_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_DISPUSB31_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_DISPUSB31_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* disp1_pix_clk_root */
    kCLOCK_DISP1PIX_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_DISP1PIX_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_DISP1PIX_ClockRoot_MuxVideoPll1 = 2U,

    /* disp2_pix_clk_root */
    kCLOCK_DISP2PIX_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISP2PIX_ClockRoot_MuxAudioPll1   = 1U,
    kCLOCK_DISP2PIX_ClockRoot_MuxVideoPll2   = 2U,
    kCLOCK_DISP2PIX_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* disp3_pix_clk_root */
    kCLOCK_DISP3PIX_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_DISP3PIX_ClockRoot_MuxAudioPll1   = 1U,
    kCLOCK_DISP3PIX_ClockRoot_MuxVideoPll3   = 2U,
    kCLOCK_DISP3PIX_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* gpu_apb_clk_root */
    kCLOCK_GPUAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_GPUAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_GPUAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_GPUAPB_ClockRoot_MuxFro             = 3U,

    /* gpu_clk_root */
    kCLOCK_GPU_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_GPU_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_GPU_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_GPU_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_acscan_480m_clk_root */
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxAudioPll1   = 1U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxVideoPll1   = 2U,
    kCLOCK_HSIOACSCAN480M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_acscan_80m_clk_root */
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_HSIOACSCAN80M_ClockRoot_MuxFro             = 3U,

    /* hsio_clk_root */
    kCLOCK_HSIO_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_HSIO_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_HSIO_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_HSIO_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_pcie_aux_clk_root */
    kCLOCK_HSIOPCIEAUX_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOPCIEAUX_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_HSIOPCIEAUX_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_HSIOPCIEAUX_ClockRoot_MuxFro             = 3U,

    /* hsio_pcie_test_160m_clk_root */
    kCLOCK_HSIOPCIETEST160M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_HSIOPCIETEST160M_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_HSIOPCIETEST160M_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_HSIOPCIETEST160M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_pcie_test_400m_clk_root */
    kCLOCK_HSIOPCIETEST400M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_HSIOPCIETEST400M_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_HSIOPCIETEST400M_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_HSIOPCIETEST400M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_pcie_test_500m_clk_root */
    kCLOCK_HSIOPCIETEST500M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_HSIOPCIETEST500M_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_HSIOPCIETEST500M_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_HSIOPCIETEST500M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* hsio_usb_test_50m_clk_root */
    kCLOCK_HSIOUSBTEST50M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOUSBTEST50M_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_HSIOUSBTEST50M_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_HSIOUSBTEST50M_ClockRoot_MuxFro             = 3U,

    /* hsio_usb_test_60m_clk_root */
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_HSIOUSBTEST60M_ClockRoot_MuxFro             = 3U,

    /* bus_m7_clk_root */
    kCLOCK_BUSM7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSM7_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_BUSM7_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_BUSM7_ClockRoot_MuxFro             = 3U,

    /* m7_clk_root */
    kCLOCK_M7_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_M7_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_M7_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_M7_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* m7_systick_clk_root */
    kCLOCK_M7SYSTICK_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_M7SYSTICK_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_M7SYSTICK_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_M7SYSTICK_ClockRoot_MuxFro             = 3U,

    /* bus_netcmix_clk_root */
    kCLOCK_BUSNETCMIX_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSNETCMIX_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_BUSNETCMIX_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_BUSNETCMIX_ClockRoot_MuxFro             = 3U,

    /* enet_clk_root */
    kCLOCK_ENET_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_ENET_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* enet_phy_test_200m_clk_root */
    kCLOCK_ENETPHYTEST200M_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETPHYTEST200M_ClockRoot_MuxSysPll1Dfs0     = 1U,
    kCLOCK_ENETPHYTEST200M_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_ENETPHYTEST200M_ClockRoot_MuxFro             = 3U,

    /* enet_phy_test_500m_clk_root */
    kCLOCK_ENETPHYTEST500M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_ENETPHYTEST500M_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_ENETPHYTEST500M_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_ENETPHYTEST500M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* enet_phy_test_667m_clk_root */
    kCLOCK_ENETPHYTEST667M_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_ENETPHYTEST667M_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_ENETPHYTEST667M_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_ENETPHYTEST667M_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* enet_ref_clk_root */
    kCLOCK_ENETREF_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETREF_ClockRoot_MuxSysPll1Dfs0     = 1U,
    kCLOCK_ENETREF_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_ENETREF_ClockRoot_MuxFro             = 3U,

    /* enet_timer1_clk_root */
    kCLOCK_ENETTIMER1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_ENETTIMER1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_ENETTIMER1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_ENETTIMER1_ClockRoot_MuxFro             = 3U,

    /* mqs2_clk_root */
    kCLOCK_MQS2_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_MQS2_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_MQS2_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_MQS2_ClockRoot_MuxExt       = 3U,

    /* sai2_clk_root */
    kCLOCK_SAI2_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SAI2_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SAI2_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SAI2_ClockRoot_MuxExt       = 3U,

    /* noc_apb_clk_root */
    kCLOCK_NOCAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_NOCAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_NOCAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_NOCAPB_ClockRoot_MuxFro             = 3U,

    /* noc_clk_root */
    kCLOCK_NOC_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_NOC_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_NOC_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_NOC_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* npu_apb_clk_root */
    kCLOCK_NPUAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_NPUAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_NPUAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_NPUAPB_ClockRoot_MuxFro             = 3U,

    /* npu_clk_root */
    kCLOCK_NPU_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_NPU_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_NPU_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_NPU_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* ccm_cko1_clk_root */
    kCLOCK_CCMCKO1_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CCMCKO1_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CCMCKO1_ClockRoot_MuxOsc32K      = 2U,
    kCLOCK_CCMCKO1_ClockRoot_MuxAudioPll1   = 3U,

    /* ccm_cko2_clk_root */
    kCLOCK_CCMCKO2_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CCMCKO2_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CCMCKO2_ClockRoot_MuxOsc32K      = 2U,
    kCLOCK_CCMCKO2_ClockRoot_MuxVideoPll1   = 3U,

    /* ccm_cko3_clk_root */
    kCLOCK_CCMCKO3_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CCMCKO3_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CCMCKO3_ClockRoot_MuxOsc32K      = 2U,
    kCLOCK_CCMCKO3_ClockRoot_MuxAudioPll2   = 3U,

    /* ccm_cko4_clk_root */
    kCLOCK_CCMCKO4_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_CCMCKO4_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_CCMCKO4_ClockRoot_MuxOsc32K      = 2U,
    kCLOCK_CCMCKO4_ClockRoot_MuxVideoPll1   = 3U,

    /* vpu_apb_clk_root */
    kCLOCK_VPUAPB_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_VPUAPB_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_VPUAPB_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_VPUAPB_ClockRoot_MuxFro             = 3U,

    /* vpu_clk_root */
    kCLOCK_VPU_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_VPU_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_VPU_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_VPU_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* vpu_dsp_clk_root */
    kCLOCK_VPUDSP_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_VPUDSP_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_VPUDSP_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_VPUDSP_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* vpu_jpeg_clk_root */
    kCLOCK_VPUJPEG_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_VPUJPEG_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_VPUJPEG_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_VPUJPEG_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* audio_xcvr_clk_root */
    kCLOCK_AUDIOXCVR_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxSysPll1Dfs0     = 1U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_AUDIOXCVR_ClockRoot_MuxFro             = 3U,

    /* bus_wakeup_clk_root */
    kCLOCK_BUSWAKEUP_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_BUSWAKEUP_ClockRoot_MuxFro             = 3U,

    /* can2_clk_root */
    kCLOCK_CAN2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAN2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAN2_ClockRoot_MuxFro             = 3U,

    /* can3_clk_root */
    kCLOCK_CAN3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN3_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAN3_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAN3_ClockRoot_MuxFro             = 3U,

    /* can4_clk_root */
    kCLOCK_CAN4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN4_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAN4_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAN4_ClockRoot_MuxFro             = 3U,

    /* can5_clk_root */
    kCLOCK_CAN5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_CAN5_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_CAN5_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_CAN5_ClockRoot_MuxFro             = 3U,

    /* flexio1_clk_root */
    kCLOCK_FLEXIO1_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_FLEXIO1_ClockRoot_MuxFro             = 3U,

    /* flexio2_clk_root */
    kCLOCK_FLEXIO2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_FLEXIO2_ClockRoot_MuxFro             = 3U,

    /* flexspi1_clk_root */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* i3c2_clk_root */
    kCLOCK_I3C2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_I3C2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_I3C2_ClockRoot_MuxFro             = 3U,

    /* i3c2_slow_clk_root */
    kCLOCK_I3C2SLOW_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_I3C2SLOW_ClockRoot_MuxFro             = 3U,

    /* lpi2c3_clk_root */
    kCLOCK_LPI2C3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C3_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C3_ClockRoot_MuxFro             = 3U,

    /* lpi2c4_clk_root */
    kCLOCK_LPI2C4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C4_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C4_ClockRoot_MuxFro             = 3U,

    /* lpi2c5_clk_root */
    kCLOCK_LPI2C5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C5_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C5_ClockRoot_MuxFro             = 3U,

    /* lpi2c6_clk_root */
    kCLOCK_LPI2C6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C6_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C6_ClockRoot_MuxFro             = 3U,

    /* lpi2c7_clk_root */
    kCLOCK_LPI2C7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C7_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C7_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C7_ClockRoot_MuxFro             = 3U,

    /* lpi2c8_clk_root */
    kCLOCK_LPI2C8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPI2C8_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPI2C8_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPI2C8_ClockRoot_MuxFro             = 3U,

    /* lpspi3_clk_root */
    kCLOCK_LPSPI3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI3_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI3_ClockRoot_MuxFro             = 3U,

    /* lpspi4_clk_root */
    kCLOCK_LPSPI4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI4_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI4_ClockRoot_MuxFro             = 3U,

    /* lpspi5_clk_root */
    kCLOCK_LPSPI5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI5_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI5_ClockRoot_MuxFro             = 3U,

    /* lpspi6_clk_root */
    kCLOCK_LPSPI6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI6_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI6_ClockRoot_MuxFro             = 3U,

    /* lpspi7_clk_root */
    kCLOCK_LPSPI7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI7_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI7_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI7_ClockRoot_MuxFro             = 3U,

    /* lpspi8_clk_root */
    kCLOCK_LPSPI8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPSPI8_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPSPI8_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPSPI8_ClockRoot_MuxFro             = 3U,

    /* lptmr2_clk_root */
    kCLOCK_LPTMR2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPTMR2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPTMR2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPTMR2_ClockRoot_MuxFro             = 3U,

    /* lpuart3_clk_root */
    kCLOCK_LPUART3_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART3_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART3_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART3_ClockRoot_MuxFro             = 3U,

    /* lpuart4_clk_root */
    kCLOCK_LPUART4_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART4_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART4_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART4_ClockRoot_MuxFro             = 3U,

    /* lpuart5_clk_root */
    kCLOCK_LPUART5_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART5_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART5_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART5_ClockRoot_MuxFro             = 3U,

    /* lpuart6_clk_root */
    kCLOCK_LPUART6_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART6_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART6_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART6_ClockRoot_MuxFro             = 3U,

    /* lpuart7_clk_root */
    kCLOCK_LPUART7_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART7_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART7_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART7_ClockRoot_MuxFro             = 3U,

    /* lpuart8_clk_root */
    kCLOCK_LPUART8_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_LPUART8_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_LPUART8_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_LPUART8_ClockRoot_MuxFro             = 3U,

    /* sai3_clk_root */
    kCLOCK_SAI3_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SAI3_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SAI3_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SAI3_ClockRoot_MuxExt       = 3U,

    /* sai4_clk_root */
    kCLOCK_SAI4_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SAI4_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SAI4_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SAI4_ClockRoot_MuxExt       = 3U,

    /* sai5_clk_root */
    kCLOCK_SAI5_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SAI5_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SAI5_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SAI5_ClockRoot_MuxExt       = 3U,

    /* spdif_clk_root */
    kCLOCK_SPDIF_ClockRoot_MuxOsc24M    = 0U,
    kCLOCK_SPDIF_ClockRoot_MuxAudioPll1 = 1U,
    kCLOCK_SPDIF_ClockRoot_MuxAudioPll2 = 2U,
    kCLOCK_SPDIF_ClockRoot_MuxExt       = 3U,

    /* swo_trace_clk_root */
    kCLOCK_SWOTRACE_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_SWOTRACE_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_SWOTRACE_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_SWOTRACE_ClockRoot_MuxFro             = 3U,

    /* tpm4_clk_root */
    kCLOCK_TPM4_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_TPM4_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_TPM4_ClockRoot_MuxAudioPll1   = 2U,
    kCLOCK_TPM4_ClockRoot_MuxExt         = 3U,

    /* tpm5_clk_root */
    kCLOCK_TPM5_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_TPM5_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_TPM5_ClockRoot_MuxAudioPll1   = 2U,
    kCLOCK_TPM5_ClockRoot_MuxExt         = 3U,

    /* tpm6_clk_root */
    kCLOCK_TPM6_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_TPM6_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_TPM6_ClockRoot_MuxAudioPll1   = 2U,
    kCLOCK_TPM6_ClockRoot_MuxExt         = 3U,

    /* tstmr2_clk_root */
    kCLOCK_TSTMR2_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_TSTMR2_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_TSTMR2_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_TSTMR2_ClockRoot_MuxFro             = 3U,

    /* usb_phy_burunin_clk_root */
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxOsc24M          = 0U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxSysPll1Dfs0Div2 = 1U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxSysPll1Dfs1Div2 = 2U,
    kCLOCK_USBPHYBURUNIN_ClockRoot_MuxFro             = 3U,

    /* usdhc1_clk_root */
    kCLOCK_USDHC1_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_USDHC1_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_USDHC1_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_USDHC1_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* usdhc2_clk_root */
    kCLOCK_USDHC2_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_USDHC2_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_USDHC2_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_USDHC2_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* usdhc3_clk_root */
    kCLOCK_USDHC3_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_USDHC3_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_USDHC3_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_USDHC3_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* v2x_pk_clk_root */
    kCLOCK_V2XPK_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_V2XPK_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_V2XPK_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_V2XPK_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* wakeup_axi_clk_root */
    kCLOCK_WAKEUPAXI_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Dfs2 = 3U,

    /* xspi_slv_root_clk_root */
    kCLOCK_XSPISLVROOT_ClockRoot_MuxOsc24M      = 0U,
    kCLOCK_XSPISLVROOT_ClockRoot_MuxSysPll1Dfs0 = 1U,
    kCLOCK_XSPISLVROOT_ClockRoot_MuxSysPll1Dfs1 = 2U,
    kCLOCK_XSPISLVROOT_ClockRoot_MuxSysPll1Dfs2 = 3U,
} clock_root_mux_source_t;

/*******************************************************************************
 * Clock Gate Definitions
 ******************************************************************************/

/*! @brief Clock gate value */
typedef enum _clock_gate_value
{
    kCLOCK_Off = (int)~CCM_LPCG_DIRECT_ON_MASK, /*!< Clock is off. */
    kCLOCK_On  = CCM_LPCG_DIRECT_ON_MASK,       /*!< Clock is on*/
} clock_gate_value_t;

#define clock_ip_name_t hal_clk_id_e

/*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS                \
    {                              \
        hal_clock_adc \
    }

/*
 * ! @brief Clock ip name array for MU.
 * clock of MU1_MUA, MU2_MUA is enabled by same LPCG42(Gate signal is clk_enable_mu_a)
 */
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu_A, kCLOCK_Mu_A \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                                \
    {                                                                                                               \
        hal_clock_invalid, hal_clock_lpi2c1, hal_clock_lpi2c2, hal_clock_lpi2c3, hal_clock_lpi2c4, hal_clock_lpi2c5, hal_clock_lpi2c6, \
            hal_clock_lpi2c7, hal_clock_lpi2c8                                                                            \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                                                \
    {                                                                                                               \
        hal_clock_invalid, hal_clock_lpspi1, hal_clock_lpspi2, hal_clock_lpspi3, hal_clock_lpspi4, hal_clock_lpspi5, hal_clock_lpspi6, \
            hal_clock_lpspi7, hal_clock_lpspi8                                                                            \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                                                    \
    {                                                                                 \
        hal_clock_tpm1, hal_clock_tpm2, hal_clock_tpm3, hal_clock_tpm4, hal_clock_tpm5, hal_clock_tpm6, \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                                    \
    {                                                    \
        hal_clock_flexio1, hal_clock_flexio2 \
    }

/*! @brief Clock ip name array for FLEXSPI. */
#define FLEXSPI_CLOCKS                    \
    {                                     \
        hal_clock_invalid, hal_clock_flexspi1 \
    }

/*! @brief Clock ip name array for TMU. */
#define TMU_CLOCKS  \
    {               \
        hal_clock_tmu, \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                              \
    {                                               \
        hal_clock_invalid, hal_clock_can1, hal_clock_can2, hal_clock_can3, hal_clock_can4, hal_clock_can5, \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                     \
    {                                                                                                     \
        hal_clock_invalid, hal_clock_lpuart1, hal_clock_lpuart2, hal_clock_lpuart3, hal_clock_lpuart4, hal_clock_lpuart5, \
            hal_clock_lpuart6, hal_clock_lpuart7, hal_clock_lpuart8, \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                               \
    {                                                            \
        hal_clock_invalid, hal_clock_sai1, hal_clock_sai2, hal_clock_sai3, hal_clock_sai4, hal_clock_sai5, \
    }

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS \
    {              \
        hal_clock_pdm \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS  \
    {                \
        hal_clock_enet \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS                                 \
    {                                              \
        hal_clock_invalid, hal_clock_i3c1, hal_clock_i3c2 \
    }

/*******************************************************************************
 * Clock Root APIs
 ******************************************************************************/
/*!
 * @brief Power Off Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
void CLOCK_PowerOffRootClock(clock_root_t root);

/*!
 * @brief Power On Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
void CLOCK_PowerOnRootClock(clock_root_t root);

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config);

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 */
void CLOCK_EnableClock(clock_ip_name_t name);

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_lpcg_t.
 */
void CLOCK_DisableClock(clock_ip_name_t name);

/*******************************************************************************
 * Other APIs
 ******************************************************************************/

/*
 * Setup a variable for clock source frequencies
 */
extern volatile uint32_t g_clockSourceFreq[kCLOCK_LdbPll + 1];

/*!
 * @brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency.
 *
 * @param name Which root clock to get, see \ref clock_root_t.
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetIpFreq(clock_root_t name);

#endif

#endif
