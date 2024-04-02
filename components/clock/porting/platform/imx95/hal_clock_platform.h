/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HAL_CLOCK_PLATFORM_H_
#define HAL_CLOCK_PLATFORM_H_
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HAL_CLOCK_PLATFORM_SOURCE_NUM 41
/* hal_clock_invalid */
#define HAL_CLOCK_PLATFORM_MAX_ID     (HAL_CLOCK_PLATFORM_SOURCE_NUM + 123)
#define HAL_CLOCK_PLATFORM_MUX_MAX_ID 4U

/*******************************************************************************
 * HAL Clock Identifier
 ******************************************************************************/
/*!
 * @brief hal clock identifier
 */
typedef enum
{
    /* unify clock id for clock sources and ips */
    /* clock id for clock sources */
    hal_clock_ext             = 0,  /* clock id for EXT_CLK */
    hal_clock_osc32k          = 1,  /* clock id for OSC_32K_CLK */
    hal_clock_osc24m          = 2,  /* clock id for OSC_24M_CLK */
    hal_clock_fro             = 3,  /* clock id for FRO_CLK */
    hal_clock_syspll1ctl      = 4,  /* clock id for SYS_PLL1_CTL */
    hal_clock_syspll1dfs0ctl  = 5,  /* clock id for SYS_PLL1_DFS0_CTL */
    hal_clock_syspll1dfs0     = 6,  /* clock id for SYS_PLL1_DFS0_CLK */
    hal_clock_syspll1dfs0div2 = 7,  /* clock id for SYS_PLL1_DFS0_DIV2_CLK */
    hal_clock_syspll1dfs1ctl  = 8,  /* clock id for SYS_PLL1_DFS1_CTL */
    hal_clock_syspll1dfs1     = 9,  /* clock id for SYS_PLL1_DFS1_CLK */
    hal_clock_syspll1dfs1div2 = 10, /* clock id for SYS_PLL1_DFS1_DIV2_CLK */
    hal_clock_syspll1dfs2ctl  = 11, /* clock id for SYS_PLL1_DFS2_CTL */
    hal_clock_syspll1dfs2     = 12, /* clock id for SYS_PLL1_DFS2_CLK */
    hal_clock_syspll1dfs2div2 = 13, /* clock id for SYS_PLL1_DFS2_DIV2_CLK */
    hal_clock_audiopll1ctl    = 14, /* clock id for AUDIO_PLL1_CTL */
    hal_clock_audiopll1       = 15, /* clock id for AUDIO_PLL1_CLK */
    hal_clock_audiopll2ctl    = 16, /* clock id for AUDIO_PLL2_CTL */
    hal_clock_audiopll2       = 17, /* clock id for AUDIO_PLL2_CLK */
    hal_clock_videopll1ctl    = 18, /* clock id for VIDEO_PLL1_CTL */
    hal_clock_videopll1       = 19, /* clock id for VIDEO_PLL1_CLK */
    hal_clock_videopll2ctl    = 20, /* clock id for VIDEO_PLL2_CTL */
    hal_clock_videopll2       = 21, /* clock id for VIDEO_PLL2_CLK */
    hal_clock_videopll3ctl    = 22, /* clock id for VIDEO_PLL3_CTL */
    hal_clock_videopll3       = 23, /* clock id for VIDEO_PLL3_CLK */
    hal_clock_armpllctl       = 24, /* clock id for ARM_PLL_CTL */
    hal_clock_armplldfs0ctl   = 25, /* clock id for ARM_PLL_DFS0_CTL */
    hal_clock_armplldfs0      = 26, /* clock id for ARM_PLL_DFS0_CLK */
    hal_clock_armplldfs1ctl   = 27, /* clock id for ARM_PLL_DFS1_CTL */
    hal_clock_armplldfs1      = 28, /* clock id for ARM_PLL_DFS1_CLK */
    hal_clock_armplldfs2ctl   = 29, /* clock id for ARM_PLL_DFS2_CTL */
    hal_clock_armplldfs2      = 30, /* clock id for ARM_PLL_DFS2_CLK */
    hal_clock_armplldfs3ctl   = 31, /* clock id for ARM_PLL_DFS3_CTL */
    hal_clock_armplldfs3      = 32, /* clock id for ARM_PLL_DFS3_CLK */
    hal_clock_drampllctl      = 33, /* clock id for DRAM_PLL_CTL */
    hal_clock_drampll         = 34, /* clock id for DRAM_PLL_CLK */
    hal_clock_hsiopllctl      = 35, /* clock id for HSIO_PLL_CTL */
    hal_clock_hsiopll         = 36, /* clock id for HSIO_PLL_CLK */
    hal_clock_ldbpllctl       = 37, /* clock id for LDB_PLL_CTL */
    hal_clock_ldbpll          = 38, /* clock id for LDB_PLL_CLK */
    hal_clock_extl            = 39, /* clock id for ext1(from components/imx_sm/devices/MIMX95/drivers/fsl_clock.h) */
    hal_clock_ext2            = 40, /* clock id for ext2(from components/imx_sm/devices/MIMX95/drivers/fsl_clock.h) */

    /* clock id for ips */
    hal_clock_adc              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 0,   /* clock id for Adc */
    hal_clock_tmu              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 1,   /* clock id for Tmu */
    hal_clock_busaon           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 2,   /* clock id for Bus Aon */
    hal_clock_can1             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 3,   /* clock id for Can1 */
    hal_clock_i3c1             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 4,   /* clock id for I3C1 */
    hal_clock_i3c1Slow         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 5,   /* clock id for I3C1 Slow */
    hal_clock_lpi2c1           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 6,   /* clock id for Lpi2C1 */
    hal_clock_lpi2c2           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 7,   /* clock id for Lpi2C2 */
    hal_clock_lpspi1           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 8,   /* clock id for Lpspi1 */
    hal_clock_lpspi2           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 9,   /* clock id for Lpspi2 */
    hal_clock_lptmr1           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 10,  /* clock id for Lptmr1 */
    hal_clock_lpuart1          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 11,  /* clock id for Lpuart1 */
    hal_clock_lpuart2          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 12,  /* clock id for Lpuart2 */
    hal_clock_m33              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 13,  /* clock id for M33 */
    hal_clock_m33systick       = HAL_CLOCK_PLATFORM_SOURCE_NUM + 14,  /* clock id for M33 Systick */
    hal_clock_mqs1             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 15,  /* clock id for Mqs1 */
    hal_clock_pdm              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 16,  /* clock id for Pdm */
    hal_clock_sai1             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 17,  /* clock id for Sai1 */
    hal_clock_sentinel         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 18,  /* clock id for Sentinel */
    hal_clock_tpm2             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 19,  /* clock id for Tpm2 */
    hal_clock_tstmr1           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 20,  /* clock id for Tstmr1 */
    hal_clock_camApb           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 21,  /* clock id for Cam Apb */
    hal_clock_camAxi           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 22,  /* clock id for Cam Axi */
    hal_clock_camCm0           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 23,  /* clock id for Cam Cm0 */
    hal_clock_camIsi           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 24,  /* clock id for Cam Isi */
    hal_clock_mipiPhyCfg       = HAL_CLOCK_PLATFORM_SOURCE_NUM + 25,  /* clock id for Mipi Phy Cfg */
    hal_clock_mipiPhyPllBypass = HAL_CLOCK_PLATFORM_SOURCE_NUM + 26,  /* clock id for Mipi Phy Pll Bypass */
    hal_clock_mipiPhyPllRef    = HAL_CLOCK_PLATFORM_SOURCE_NUM + 27,  /* clock id for Mipi Phy Pll Ref */
    hal_clock_mipiTestByte     = HAL_CLOCK_PLATFORM_SOURCE_NUM + 28,  /* clock id for Mipi Test Byte */
    hal_clock_a55              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 29,  /* clock id for Arm A55 */
    hal_clock_a55mtrbus        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 30,  /* clock id for Arm A55 Mtr Bus  */
    hal_clock_a55periph        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 31,  /* clock id for Arm A55 Periph */
    hal_clock_dramalt          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 32,  /* clock id for Dram Alt */
    hal_clock_dramapb          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 33,  /* clock id for Dram Apb */
    hal_clock_dispapb          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 34,  /* clock id for Disp Apb */
    hal_clock_dispaxi          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 35,  /* clock id for Disp Axi */
    hal_clock_dispdp           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 36,  /* clock id for Disp Dp */
    hal_clock_dispocram        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 37,  /* clock id for Disp Ocram */
    hal_clock_dispusb31        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 38,  /* clock id for Disp Usb31 */
    hal_clock_disp1pix         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 39,  /* clock id for Disp1 Pix */
    hal_clock_disp2pix         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 40,  /* clock id for Disp2 Pix */
    hal_clock_disp3pix         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 41,  /* clock id for Disp3 Pix */
    hal_clock_gpuapb           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 42,  /* clock id for Gpu Apb */
    hal_clock_gpu              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 43,  /* clock id for Gpu */
    hal_clock_hsioacscan480m   = HAL_CLOCK_PLATFORM_SOURCE_NUM + 44,  /* clock id for Hsio Acscan 480M */
    hal_clock_hsioacscan80m    = HAL_CLOCK_PLATFORM_SOURCE_NUM + 45,  /* clock id for Hsio Acscan 80M */
    hal_clock_hsio             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 46,  /* clock id for Hsio */
    hal_clock_hsiopcieaux      = HAL_CLOCK_PLATFORM_SOURCE_NUM + 47,  /* clock id for Hsio Pcie Aux */
    hal_clock_hsiopcietest160m = HAL_CLOCK_PLATFORM_SOURCE_NUM + 48,  /* clock id for Hsio Pcie Test 160M */
    hal_clock_hsiopcieTest400m = HAL_CLOCK_PLATFORM_SOURCE_NUM + 49,  /* clock id for Hsio Pcie Test 400M */
    hal_clock_hsiopcieTest500m = HAL_CLOCK_PLATFORM_SOURCE_NUM + 50,  /* clock id for Hsio Pcie Test 500M */
    hal_clock_hsiousbTest50m   = HAL_CLOCK_PLATFORM_SOURCE_NUM + 51,  /* clock id for Hsio Usb Test 50M */
    hal_clock_hsiousbTest60m   = HAL_CLOCK_PLATFORM_SOURCE_NUM + 52,  /* clock id for Hsio Usb Test 60M */
    hal_clock_busm7            = HAL_CLOCK_PLATFORM_SOURCE_NUM + 53,  /* clock id for Bus M7 */
    hal_clock_m7               = HAL_CLOCK_PLATFORM_SOURCE_NUM + 54,  /* clock id for M7 */
    hal_clock_m7systick        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 55,  /* clock id for M7 Systick */
    hal_clock_busnetcmix       = HAL_CLOCK_PLATFORM_SOURCE_NUM + 56,  /* clock id for Bus Netcmix */
    hal_clock_enet             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 57,  /* clock id for Enet */
    hal_clock_enetphytest200m  = HAL_CLOCK_PLATFORM_SOURCE_NUM + 58,  /* clock id for Enet Phy Test 200M */
    hal_clock_enetphytest500m  = HAL_CLOCK_PLATFORM_SOURCE_NUM + 59,  /* clock id for Enet Phy Test 500M */
    hal_clock_enetphytest667m  = HAL_CLOCK_PLATFORM_SOURCE_NUM + 60,  /* clock id for Enet Phy Test 667M */
    hal_clock_enetref          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 61,  /* clock id for Enet Ref */
    hal_clock_enettimer1       = HAL_CLOCK_PLATFORM_SOURCE_NUM + 62,  /* clock id for Enet Timer1 */
    hal_clock_mqs2             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 63,  /* clock id for Mqs2 */
    hal_clock_sai2             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 64,  /* clock id for Sai2 */
    hal_clock_nocapb           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 65,  /* clock id for Noc Apb */
    hal_clock_noc              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 66,  /* clock id for Noc */
    hal_clock_npuapb           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 67,  /* clock id for Npu Apb */
    hal_clock_npu              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 68,  /* clock id for Npu */
    hal_clock_ccmcko1          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 69,  /* clock id for Ccm Cko1 */
    hal_clock_ccmcko2          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 70,  /* clock id for Ccm Cko2 */
    hal_clock_ccmcko3          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 71,  /* clock id for Ccm Cko3 */
    hal_clock_ccmcko4          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 72,  /* clock id for Ccm Cko4 */
    hal_clock_vpuapb           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 73,  /* clock id for Vpu Apb */
    hal_clock_vpu              = HAL_CLOCK_PLATFORM_SOURCE_NUM + 74,  /* clock id for Vpu */
    hal_clock_vpudsp           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 75,  /* clock id for Vpu Dsp */
    hal_clock_vpujpeg          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 76,  /* clock id for Vpu Jpeg */
    hal_clock_audioxcvr        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 77,  /* clock id for Audio Xcvr */
    hal_clock_buswakeup        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 78,  /* clock id for Bus Wakeup */
    hal_clock_can2             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 79,  /* clock id for Can2 */
    hal_clock_can3             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 80,  /* clock id for Can3 */
    hal_clock_can4             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 81,  /* clock id for Can4 */
    hal_clock_can5             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 82,  /* clock id for Can5 */
    hal_clock_flexio1          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 83,  /* clock id for Flexio1 */
    hal_clock_flexio2          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 84,  /* clock id for Flexio2 */
    hal_clock_flexspi1         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 85,  /* clock id for Flexspi1 */
    hal_clock_i3c2             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 86,  /* clock id for I3C2 */
    hal_clock_i3c2slow         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 87,  /* clock id for I3C2 Slow */
    hal_clock_lpi2c3           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 88,  /* clock id for Lpi2C3 */
    hal_clock_lpi2c4           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 89,  /* clock id for Lpi2C4 */
    hal_clock_lpi2c5           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 90,  /* clock id for Lpi2C5 */
    hal_clock_lpi2c6           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 91,  /* clock id for Lpi2C6 */
    hal_clock_lpi2c7           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 92,  /* clock id for Lpi2C7 */
    hal_clock_lpi2c8           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 93,  /* clock id for Lpi2C8 */
    hal_clock_lpspi3           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 94,  /* clock id for Lpspi3 */
    hal_clock_lpspi4           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 95,  /* clock id for Lpspi4 */
    hal_clock_lpspi5           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 96,  /* clock id for Lpspi5 */
    hal_clock_lpspi6           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 97,  /* clock id for Lpspi6 */
    hal_clock_lpspi7           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 98,  /* clock id for Lpspi7 */
    hal_clock_lpspi8           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 99,  /* clock id for Lpspi8 */
    hal_clock_lptmr2           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 100, /* clock id for Lptmr2 */
    hal_clock_lpuart3          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 101, /* clock id for Lpuart3 */
    hal_clock_lpuart4          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 102, /* clock id for Lpuart4 */
    hal_clock_lpuart5          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 103, /* clock id for Lpuart5 */
    hal_clock_lpuart6          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 104, /* clock id for Lpuart6 */
    hal_clock_lpuart7          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 105, /* clock id for Lpuart7 */
    hal_clock_lpuart8          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 106, /* clock id for Lpuart8 */
    hal_clock_sai3             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 107, /* clock id for Sai3 */
    hal_clock_sai4             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 108, /* clock id for Sai4 */
    hal_clock_sai5             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 109, /* clock id for Sai5 */
    hal_clock_spdif            = HAL_CLOCK_PLATFORM_SOURCE_NUM + 110, /* clock id for Spdif */
    hal_clock_swoTrace         = HAL_CLOCK_PLATFORM_SOURCE_NUM + 111, /* clock id for Swo Trace */
    hal_clock_tpm4             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 112, /* clock id for Tpm4 */
    hal_clock_tpm5             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 113, /* clock id for Tpm5 */
    hal_clock_tpm6             = HAL_CLOCK_PLATFORM_SOURCE_NUM + 114, /* clock id for Tpm6 */
    hal_clock_tstmr2           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 115, /* clock id for Tstmr2 */
    hal_clock_usbPhyBurunin    = HAL_CLOCK_PLATFORM_SOURCE_NUM + 116, /* clock id for Usb Phy Burunin */
    hal_clock_usdhc1           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 117, /* clock id for Usdhc1 */
    hal_clock_usdhc2           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 118, /* clock id for Usdhc2 */
    hal_clock_usdhc3           = HAL_CLOCK_PLATFORM_SOURCE_NUM + 119, /* clock id for Usdhc3 */
    hal_clock_v2xpk            = HAL_CLOCK_PLATFORM_SOURCE_NUM + 120, /* clock id for V2X Pk */
    hal_clock_wakeupaxi        = HAL_CLOCK_PLATFORM_SOURCE_NUM + 121, /* clock id for Wakeup Axi */
    hal_clock_xspislvroot      = HAL_CLOCK_PLATFORM_SOURCE_NUM + 122, /* clock id for Xspi Slv Root */
    hal_clock_invalid          = HAL_CLOCK_PLATFORM_SOURCE_NUM + 123
} hal_clk_id_e;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* HAL_CLOCK_PLATFORM_H_ */
