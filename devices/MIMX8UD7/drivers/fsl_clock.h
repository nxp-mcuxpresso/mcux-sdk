/*
 * Copyright 2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Configure whether driver controls clock
 *
 * When set to 0, peripheral drivers will enable clock in initialize function
 * and disable clock in de-initialize function. When set to 1, peripheral
 * driver will not control the clock, application could control the clock out of
 * the driver.
 *
 * @note All drivers share this feature switcher. If it is set to 1, application
 * should handle clock enable and disable for all drivers.
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 0
#endif

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.0.5. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 0, 5))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (160000000UL)
#endif

/*!
 * @brief CGC (A/S)PLLPFD[PFDx] value.
 */
#define CGC_PLLPFD_PFD_VAL(pfdClkout, fracValue) ((uint32_t)((uint32_t)(fracValue) << (uint32_t)(pfdClkout)))
/*!
 * @brief CGC (A/S)PLLPFD[PFD] mask.
 */
#define CGC_PLLPFD_PFD_MASK(pfdClkout) ((uint32_t)((uint32_t)(CGC_PLL0PFDCFG_PFD0_MASK) << (uint32_t)(pfdClkout)))
/*!
 * @brief CGC (A/S)PLLPFD[PFDx_VALID] mask.
 */
#define CGC_PLLPFD_PFD_VALID_MASK(pfdClkout) \
    ((uint32_t)((uint32_t)CGC_PLL0PFDCFG_PFD0_VALID_MASK << (uint32_t)(pfdClkout)))
/*!
 * @brief CGC (A/S)PLLPFD[PFDx_CLKGATE] mask.
 */
#define CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout) \
    ((uint32_t)((uint32_t)CGC_PLL0PFDCFG_PFD0_CLKGATE_MASK << (uint32_t)(pfdClkout)))

/*! @brief External XTAL (SYSOSC) clock frequency.
 *
 * The XTAL (SYSOSC) clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtalFreq to set the value in the clock driver. For example,
 * if XTAL is 24 MHz:
 * @code
 * CLOCK_InitSysOsc(...);
 * CLOCK_SetXtalFreq(24000000);
 * @endcode
 *
 * This is important for the multicore platforms where only one core needs to set up the
 * OSC/SYSOSC using CLOCK_InitSysOsc. All other cores need to call the CLOCK_SetXtalFreq
 * to get a valid clock frequency.
 */
extern volatile uint32_t g_xtal0Freq;

/*! @brief External XTAL32/EXTAL32 clock frequency.
 *
 * The XTAL32/EXTAL32 clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtal32Freq to set the value in the clock driver.
 *
 * This is important for the multicore platforms where only one core needs to set up
 * the clock. All other cores need to call the CLOCK_SetXtal32Freq
 * to get a valid clock frequency.
 */
extern volatile uint32_t g_xtal32Freq;

/*! @brief External LVDS pad clock frequency.
 *
 * The LVDS pad clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetLvdsFreq to set the value in the clock driver.
 *
 */
extern volatile uint32_t g_lvdsFreq;

/*! @brief External MCLK pad clock frequency.
 *
 * The MCLK pad clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetMclkFreq to set the value in the clock driver.
 *
 */
extern volatile uint32_t g_mclkFreq[4];

/*! @brief External RX_BCLK pad clock frequency.
 *
 * The RX_BCLK pad clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetRxBclkFreq to set the value in the clock driver.
 *
 */
extern volatile uint32_t g_rxBclkFreq[8];

/*! @brief External TX_BCLK pad clock frequency.
 *
 * The TX_BCLK pad clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetTxBclkFreq to set the value in the clock driver.
 *
 */
extern volatile uint32_t g_txBclkFreq[8];

/*! @brief Recovered SPDIF_RX clock frequency.
 *
 * The SPDIF_RX clock frequency in Hz. When the clock is sampled, use the
 * function CLOCK_SetSpdifRxFreq to set the value in the clock driver.
 *
 */
extern volatile uint32_t g_spdifRxFreq;

/*!
 * @brief Re-define PCC register masks and bitfield operations to unify
 * the different namings in the soc header file.
 */
#define PCC_CLKCFG_PCD_MASK   (0x7U)
#define PCC_CLKCFG_PCD_SHIFT  (0U)
#define PCC_CLKCFG_PCD(x)     (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCD_SHIFT)) & PCC_CLKCFG_PCD_MASK)
#define PCC_CLKCFG_FRAC_MASK  (0x8U)
#define PCC_CLKCFG_FRAC_SHIFT (3U)
#define PCC_CLKCFG_FRAC(x)    (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_FRAC_SHIFT)) & PCC_CLKCFG_FRAC_MASK)
#define PCC_CLKCFG_PCS_MASK   (0x7000000U)
#define PCC_CLKCFG_PCS_SHIFT  (24U)
#define PCC_CLKCFG_PCS(x)     (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCS_SHIFT)) & PCC_CLKCFG_PCS_MASK)
#define PCC_CLKCFG_INUSE_MASK (0x20000000U)
#define PCC_CLKCFG_CGC_MASK   (0x40000000U)
#define PCC_CLKCFG_PR_MASK    (0x80000000U)

/*! @brief Bitfield values for general PCC registers. */
#define PCC_PCS_VAL(reg)  (((reg)&PCC_CLKCFG_PCS_MASK) >> PCC_CLKCFG_PCS_SHIFT)
#define PCC_FRAC_VAL(reg) (((reg)&PCC_CLKCFG_FRAC_MASK) >> PCC_CLKCFG_FRAC_SHIFT)
#define PCC_PCD_VAL(reg)  (((reg)&PCC_CLKCFG_PCD_MASK) >> PCC_CLKCFG_PCD_SHIFT)

/*!
 * @brief Clock source index macros for clock_ip_src_t.
 */
#define CLOCK_IP_SOURCE_PCC_INDEX(idx)         ((idx) << 8U)
#define CLOCK_IP_SOURCE_NON_PCC_INDEX(idx)     ((idx) << 16U)
#define CLOCK_IP_SOURCE_PCC_INDEX_VAL(src)     ((uint32_t)(src) >> 8U)
#define CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) ((uint32_t)(src) >> 16U)

/*!
 * @brief Define PCC bit available mask for clock_ip_name_t.
 */
#define PCC_PCS_AVAIL_MASK      (0x2U)
#define PCC_PCD_FRAC_AVAIL_MASK (0x1U)
/*!
 * @brief Define Non-PCC register flag mask for clock_ip_name_t.
 */
#define IP_NAME_NON_PCC_FLAG_MASK ((uint32_t)1U << 30)

/*!
 * @brief Define PCC register content for clock_ip_name_t.
 */
#define PCC_REG(name) (*(volatile uint32_t *)((uint32_t)(name) & ~(PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK)))

/*! @brief Clock ip name array for RGPIO2P. */
#define RGPIO_CLOCKS                                                                             \
    {                                                                                            \
        kCLOCK_RgpioA, kCLOCK_RgpioB, kCLOCK_RgpioC, kCLOCK_RgpioD, kCLOCK_RgpioE, kCLOCK_RgpioF \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                                                             \
    {                                                                                                          \
        kCLOCK_Sai0, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, kCLOCK_Sai4, kCLOCK_Sai5, kCLOCK_Sai6, kCLOCK_Sai7 \
    }

/*! @brief Clock ip name array for PCTL. */
#define PCTL_CLOCKS                                                                                \
    {                                                                                              \
        kCLOCK_PctlA, kCLOCK_PctlB, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_PctlE, kCLOCK_PctlF \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                             \
    {                                                                                                            \
        kCLOCK_Lpi2c0, kCLOCK_Lpi2c1, kCLOCK_Lpi2c2, kCLOCK_Lpi2c3, kCLOCK_Lpi2c4, kCLOCK_Lpi2c5, kCLOCK_Lpi2c6, \
            kCLOCK_Lpi2c7                                                                                        \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS                            \
    {                                         \
        kCLOCK_I3c0, kCLOCK_I3c1, kCLOCK_I3c2 \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                  \
    {                                  \
        kCLOCK_Flexio0, kCLOCK_Flexio1 \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS \
    {                  \
        kCLOCK_Flexcan \
    }

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS    \
    {                 \
        kCLOCK_Micfil \
    }

/*! @brief Clock ip name array for LCDIF/DCNANO. */
#define LCDIF_CLOCKS  \
    {                 \
        kCLOCK_Dcnano \
    }

/*! @brief Clock ip name array for MIPI DSI. */
#define MIPI_DSI_HOST_CLOCKS \
    {                        \
        kCLOCK_Dsi           \
    }

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS                           \
    {                                         \
        kCLOCK_Dma0, kCLOCK_Dma1, kCLOCK_Dma2 \
    }

/*! @brief Clock ip name array for EDMA Channels. */
#define EDMA_CHAN_CLOCKS                               \
    {                                                  \
        kCLOCK_Dma0Ch0, kCLOCK_Dma1Ch0, kCLOCK_Dma2Ch0 \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                   \
    {                                                                                                   \
        kCLOCK_Lpuart0, kCLOCK_Lpuart1, kCLOCK_Lpuart2, kCLOCK_Lpuart3, kCLOCK_Lpuart4, kCLOCK_Lpuart5, \
            kCLOCK_Lpuart6, kCLOCK_Lpuart7                                                              \
    }

/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS               \
    {                            \
        kCLOCK_Dac0, kCLOCK_Dac1 \
    }

/*! @brief Clock ip name array for LPTMR. */
#define LPTMR_CLOCKS                 \
    {                                \
        kCLOCK_Lptmr0, kCLOCK_Lptmr1 \
    }

/*! @brief Clock ip name array for LPADC. */
#define LPADC_CLOCKS             \
    {                            \
        kCLOCK_Adc0, kCLOCK_Adc1 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                             \
    {                                                                                            \
        kCLOCK_Lpspi0, kCLOCK_Lpspi1, kCLOCK_Lpspi2, kCLOCK_Lpspi3, kCLOCK_Lpspi4, kCLOCK_Lpspi5 \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                                                                              \
    {                                                                                                           \
        kCLOCK_Tpm0, kCLOCK_Tpm1, kCLOCK_Tpm2, kCLOCK_Tpm3, kCLOCK_Tpm4, kCLOCK_Tpm5, kCLOCK_Tpm6, kCLOCK_Tpm7, \
            kCLOCK_Tpm8                                                                                         \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS                \
    {                              \
        kCLOCK_Lpit0, kCLOCK_Lpit1 \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS               \
    {                            \
        kCLOCK_Cmp0, kCLOCK_Cmp1 \
    }

/*! @brief Clock ip name array for MU. */
#if defined(MIMX8UD7_cm33_SERIES)
#define MU_CLOCKS                             \
    {                                         \
        kCLOCK_Mu0A, kCLOCK_Mu1A, kCLOCK_Mu2A \
    }
#elif defined(MIMX8UD7_dsp0_SERIES)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu1B \
    }
#elif defined(MIMX8UD7_dsp1_SERIES)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu2B, kCLOCK_Mu3B \
    }
#elif defined(MIMX8UD5_cm33_SERIES)
#define MU_CLOCKS                             \
    {                                         \
        kCLOCK_Mu0A, kCLOCK_Mu1A, kCLOCK_Mu2A \
    }
#elif defined(MIMX8UD5_dsp0_SERIES)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu1B \
    }
#elif defined(MIMX8UD5_dsp1_SERIES)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu2B, kCLOCK_Mu3B \
    }
#elif defined(MIMX8UD3_cm33_SERIES)
#define MU_CLOCKS                             \
    {                                         \
        kCLOCK_Mu0A, kCLOCK_Mu1A, kCLOCK_Mu2A \
    }
#elif defined(MIMX8UD3_dsp0_SERIES)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu1B \
    }
#elif defined(MIMX8UD3_dsp1_SERIES)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu2B, kCLOCK_Mu3B \
    }
#elif defined(MIMX8US5_cm33_SERIES)
#define MU_CLOCKS                             \
    {                                         \
        kCLOCK_Mu0A, kCLOCK_Mu1A, kCLOCK_Mu2A \
    }
#elif defined(MIMX8US5_dsp0_SERIES)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu1B \
    }
#elif defined(MIMX8US5_dsp1_SERIES)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu2B, kCLOCK_Mu3B \
    }
#elif defined(MIMX8US3_cm33_SERIES)
#define MU_CLOCKS                             \
    {                                         \
        kCLOCK_Mu0A, kCLOCK_Mu1A, kCLOCK_Mu2A \
    }
#elif defined(MIMX8US3_dsp0_SERIES)
#define MU_CLOCKS   \
    {               \
        kCLOCK_Mu1B \
    }
#elif defined(MIMX8US3_dsp1_SERIES)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu2B, kCLOCK_Mu3B \
    }
#else
#error "Unsupport core by the driver."
#endif

/*! @brief Clock ip name array for WDOG. */
#define WDOG_CLOCKS                                                                        \
    {                                                                                      \
        kCLOCK_Wdog0, kCLOCK_Wdog1, kCLOCK_Wdog2, kCLOCK_Wdog3, kCLOCK_Wdog4, kCLOCK_Wdog5 \
    }

/*! @brief Clock ip name array for SEMA42. */
#define SEMA42_CLOCKS                                  \
    {                                                  \
        kCLOCK_Sema420, kCLOCK_Sema421, kCLOCK_Sema422 \
    }

/*! @brief Clock ip name array for TPIU. */
#define TPIU_CLOCKS \
    {               \
        kCLOCK_Tpiu \
    }

/*! @brief Clock ip name array for QSPI. */
#define FLEXSPI_CLOCKS                                    \
    {                                                     \
        kCLOCK_Flexspi0, kCLOCK_Flexspi1, kCLOCK_Flexspi2 \
    }

/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS \
    {              \
        kCLOCK_Mrt \
    }

/*! @brief Clock ip name array for BBNSM. */
#define BBNSM_CLOCKS \
    {                \
        kCLOCK_Bbnsm \
    }

/*! @brief Clock ip name array for PXP. */
#define PXP_CLOCKS \
    {              \
        kCLOCK_Pxp \
    }

/*! @brief Clock ip name array for EPDC. */
#define EPDC_CLOCKS \
    {               \
        kCLOCK_Epdc \
    }

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{

    /* ---------------------------- System layer clock -----------------------*/
    kCLOCK_Cm33CorePlatClk,      /*!< RTD : CM33 Core/Platform clock */
    kCLOCK_Cm33BusClk,           /*!< RTD : CM33 Bus clock */
    kCLOCK_Cm33SlowClk,          /*!< RTD : CM33 Slow clock */
    kCLOCK_FusionDspCorePlatClk, /*!< RTD : FusionF1 DSP Core/Platform clock */
    kCLOCK_FusionDspBusClk,      /*!< RTD : FusionF1 DSP Bus clock */
    kCLOCK_FusionDspSlowClk,     /*!< RTD : FusionF1 DSP Slow clock */
    kCLOCK_XbarBusClk,           /*!< AD  : XBAR Bus clock */
    kCLOCK_HifiDspClk,           /*!< LPAV: HIFI4 clock */
    kCLOCK_HifiNicPlatClk,       /*!< LPAV: NIC HIFI clock */
    kCLOCK_NicLpavAxiClk,        /*!< LPAV: NIC LPAV AXI clock */
    kCLOCK_NicLpavAhbClk,        /*!< LPAV: NIC LPAV AHB clock */
    kCLOCK_NicLpavBusClk,        /*!< LPAV: LPAV Bus clock */
    kCLOCK_DdrClk,               /*!< LPAV: DDR clock */

    /* ------------------------------------ CGC clock ------------------------*/
    kCLOCK_SysOscClk, /*!< CGC system OSC clock. (SYSOSC) */
    kCLOCK_FroClk,    /*!< CGC FRO 192MHz clock. */
    kCLOCK_LpOscClk,  /*!< CGC LPOSC clock. (LPOSC) */
    kCLOCK_RtcOscClk, /*!< CGC RTC OSC clock. (RTCOSC) */
    kCLOCK_LvdsClk,   /*!< LVDS pad input clock frequency. */

    kCLOCK_RtdFroDiv1Clk, /*!< FRODIV1_CLK in RTD. */
    kCLOCK_RtdFroDiv2Clk, /*!< FRODIV2_CLK in RTD. */
    kCLOCK_RtdFroDiv3Clk, /*!< FRODIV3_CLK in RTD. */

    kCLOCK_RtdSysOscDiv1Clk, /*!< SOSCDIV1_CLK in RTD. */
    kCLOCK_RtdSysOscDiv2Clk, /*!< SOSCDIV2_CLK in RTD. */
    kCLOCK_RtdSysOscDiv3Clk, /*!< SOSCDIV3_CLK in RTD. */

    kCLOCK_AdFroDiv1Clk, /*!< FRODIV1_CLK in AD. */
    kCLOCK_AdFroDiv2Clk, /*!< FRODIV2_CLK in AD. */
    kCLOCK_AdFroDiv3Clk, /*!< FRODIV3_CLK in AD. */

    kCLOCK_AdSysOscDiv1Clk, /*!< SOSCDIV1_CLK in AD. */
    kCLOCK_AdSysOscDiv2Clk, /*!< SOSCDIV2_CLK in AD. */
    kCLOCK_AdSysOscDiv3Clk, /*!< SOSCDIV3_CLK in AD. */

    kCLOCK_LpavFroDiv1Clk, /*!< FRODIV1_CLK in LPAV. */
    kCLOCK_LpavFroDiv2Clk, /*!< FRODIV2_CLK in LPAV. */
    kCLOCK_LpavFroDiv3Clk, /*!< FRODIV3_CLK in LPAV. */

    kCLOCK_LpavSysOscDiv1Clk, /*!< SOSCDIV1_CLK in LPAV. */
    kCLOCK_LpavSysOscDiv2Clk, /*!< SOSCDIV2_CLK in LPAV. */
    kCLOCK_LpavSysOscDiv3Clk, /*!< SOSCDIV3_CLK in LPAV. */

    kCLOCK_Pll0Clk, /*!< CGC PLL0 clock. (PLL0CLK) */
    kCLOCK_Pll1Clk, /*!< CGC PLL1 clock. (PLL1CLK) */
    kCLOCK_Pll3Clk, /*!< CGC PLL3 clock. (PLL3CLK) */
    kCLOCK_Pll4Clk, /*!< CGC PLL4 clock. (PLL4CLK) */

    kCLOCK_Pll0Pfd0Clk, /*!< pll0 pfd0. */
    kCLOCK_Pll0Pfd1Clk, /*!< pll0 pfd1. */
    kCLOCK_Pll0Pfd2Clk, /*!< pll0 pfd2. */
    kCLOCK_Pll0Pfd3Clk, /*!< pll0 pfd3. */

    kCLOCK_Pll1Pfd0Clk, /*!< pll1 pfd0. */
    kCLOCK_Pll1Pfd1Clk, /*!< pll1 pfd1. */
    kCLOCK_Pll1Pfd2Clk, /*!< pll1 pfd2. */
    kCLOCK_Pll1Pfd3Clk, /*!< pll1 pfd3. */

    kCLOCK_Pll3Pfd0Clk, /*!< pll3 pfd0. */
    kCLOCK_Pll3Pfd1Clk, /*!< pll3 pfd1. */
    kCLOCK_Pll3Pfd2Clk, /*!< pll3 pfd2. */
    kCLOCK_Pll3Pfd3Clk, /*!< pll3 pfd3. */

    kCLOCK_Pll4Pfd0Clk, /*!< pll4 pfd0. */
    kCLOCK_Pll4Pfd1Clk, /*!< pll4 pfd1. */
    kCLOCK_Pll4Pfd2Clk, /*!< pll4 pfd2. */
    kCLOCK_Pll4Pfd3Clk, /*!< pll4 pfd3. */

    kCLOCK_Pll0VcoDivClk,  /*!< PLL0VCODIV. */
    kCLOCK_Pll0Pfd1DivClk, /*!< PLL0PFD1DIV. */
    kCLOCK_Pll0Pfd2DivClk, /*!< PLL0PFD2DIV. */

    kCLOCK_Pll1VcoDivClk,  /*!< PLL1VCODIV. */
    kCLOCK_Pll1Pfd1DivClk, /*!< PLL1PFD1DIV. */
    kCLOCK_Pll1Pfd2DivClk, /*!< PLL1PFD2DIV. */

    kCLOCK_Pll3VcoDivClk,   /*!< PLL3VCODIV. */
    kCLOCK_Pll3Pfd0Div1Clk, /*!< PLL3PFD0DIV1. */
    kCLOCK_Pll3Pfd0Div2Clk, /*!< PLL3PFD0DIV2. */
    kCLOCK_Pll3Pfd1Div1Clk, /*!< PLL3PFD1DIV1. */
    kCLOCK_Pll3Pfd1Div2Clk, /*!< PLL3PFD1DIV2. */
    kCLOCK_Pll3Pfd2Div1Clk, /*!< PLL3PFD2DIV1. */
    kCLOCK_Pll3Pfd2Div2Clk, /*!< PLL3PFD2DIV2. */
    kCLOCK_Pll3Pfd3Div1Clk, /*!< PLL3PFD3DIV1. */
    kCLOCK_Pll3Pfd3Div2Clk, /*!< PLL3PFD3DIV2. */

    kCLOCK_Pll4VcoDivClk,   /*!< PLL4VCODIV. */
    kCLOCK_Pll4Pfd0Div1Clk, /*!< PLL4PFD0DIV1. */
    kCLOCK_Pll4Pfd0Div2Clk, /*!< PLL4PFD0DIV2. */
    kCLOCK_Pll4Pfd1Div1Clk, /*!< PLL4PFD1DIV1. */
    kCLOCK_Pll4Pfd1Div2Clk, /*!< PLL4PFD1DIV2. */
    kCLOCK_Pll4Pfd2Div1Clk, /*!< PLL4PFD2DIV1. */
    kCLOCK_Pll4Pfd2Div2Clk, /*!< PLL4PFD2DIV2. */
    kCLOCK_Pll4Pfd3Div1Clk, /*!< PLL4PFD3DIV1. */
    kCLOCK_Pll4Pfd3Div2Clk, /*!< PLL4PFD3DIV2. */
} clock_name_t;

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum _clock_ip_src
{
    kCLOCK_IpSrcNone = 0U, /*!< Clock is off. */

    /* PCC0 platform PCS */
    kCLOCK_Pcc0PlatIpSrcSysOscDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 3U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_RtdSysOscDiv1Clk */
    kCLOCK_Pcc0PlatIpSrcFroDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 4U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_RtdFroDiv1Clk */
    kCLOCK_Pcc0PlatIpSrcCm33Plat =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 5U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_Cm33CorePlatClk */
    kCLOCK_Pcc0PlatIpSrcFro =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 6U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_FroClk */
    kCLOCK_Pcc0PlatIpSrcPll0Pfd3 =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 7U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_Pll0Pfd3Clk */

    /* PCC0 bus PCS */
    kCLOCK_Pcc0BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(0U) | 1U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc0BusIpSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 2U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_RtdSysOscDiv2Clk */
    kCLOCK_Pcc0BusIpSrcFroDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 3U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_RtdFroDiv2Clk */
    kCLOCK_Pcc0BusIpSrcCm33Bus =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 4U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Cm33BusClk */
    kCLOCK_Pcc0BusIpSrcPll1Pfd1Div =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 5U, /*!< PCC0 Bus clock selection: kCLOCK_Pll1Pfd1DivClk */
    kCLOCK_Pcc0BusIpSrcPll0Pfd2Div =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 6U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Pll0Pfd2DivClk */
    kCLOCK_Pcc0BusIpSrcPll0Pfd1Div =
        CLOCK_IP_SOURCE_PCC_INDEX(0U) | 7U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Pll0Pfd1DivClk */

    /* PCC1 platform PCS */
    kCLOCK_Pcc1PlatIpSrcSysOscDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 3U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_RtdSysOscDiv1Clk */
    kCLOCK_Pcc1PlatIpSrcFroDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 4U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_RtdFroDiv1Clk */
    kCLOCK_Pcc1PlatIpSrcCm33Plat =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 5U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_Cm33CorePlatClk */
    kCLOCK_Pcc1PlatIpSrcFro =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 6U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_FroClk */
    kCLOCK_Pcc1PlatIpSrcPll0Pfd3 =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 7U, /*!< PCC0, PCC1 Platform clock selection: kCLOCK_Pll0Pfd3Clk */

    /* PCC1 bus PCS */
    kCLOCK_Pcc1BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(1U) | 1U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc1BusIpSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 2U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_RtdSysOscDiv2Clk */
    kCLOCK_Pcc1BusIpSrcFroDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 3U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_RtdFroDiv2Clk */
    kCLOCK_Pcc1BusIpSrcCm33Bus =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 4U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Cm33BusClk */
    kCLOCK_Pcc1BusIpSrcPll1VcoDiv =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 5U, /*!< PCC1 Bus clock selection: kCLOCK_Pll1VcoDivClk */
    kCLOCK_Pcc1BusIpSrcPll0Pfd2Div =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 6U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Pll0Pfd2DivClk */
    kCLOCK_Pcc1BusIpSrcPll0Pfd1Div =
        CLOCK_IP_SOURCE_PCC_INDEX(1U) | 7U, /*!< PCC0, PCC1 Bus clock selection: kCLOCK_Pll0Pfd1DivClk */

    /* PCC2 has no platform PCS, only bus PCS */
    kCLOCK_Pcc2BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(2U) | 1U, /*!< PCC2 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc2BusIpSrcSysOscDiv3 =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 2U, /*!< PCC2 Bus clock selection: kCLOCK_RtdSysOscDiv3Clk */
    kCLOCK_Pcc2BusIpSrcFroDiv3 =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 3U, /*!< PCC2 Bus clock selection: kCLOCK_RtdFroDiv3Clk */
    kCLOCK_Pcc2BusIpSrcFusionDspBus =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 4U, /*!< PCC2 Bus clock selection: kCLOCK_FusionDspBusClk */
    kCLOCK_Pcc2BusIpSrcPll1VcoDiv =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 5U, /*!< PCC2 Bus clock selection: kCLOCK_Pll1VcoDivClk */
    kCLOCK_Pcc2BusIpSrcPll0Pfd2Div =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 6U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd2DivClk */
    kCLOCK_Pcc2BusIpSrcPll0Pfd1Div =
        CLOCK_IP_SOURCE_PCC_INDEX(2U) | 7U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd1DivClk */

    /* PCC3 has no platform PCS, only bus PCS */
    kCLOCK_Pcc3BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(3U) | 1U, /*!< PCC3 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc3BusIpSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(3U) | 2U, /*!< PCC3 Bus clock selection: kCLOCK_AdSysOscDiv2Clk */
    kCLOCK_Pcc3BusIpSrcFroDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(3U) | 3U, /*!< PCC3 Bus clock selection: kCLOCK_AdFroDiv2Clk */
    kCLOCK_Pcc3BusIpSrcXbarBus = CLOCK_IP_SOURCE_PCC_INDEX(3U) | 4U, /*!< PCC3 Bus clock selection: kCLOCK_XbarBusClk */
    kCLOCK_Pcc3BusIpSrcPll3Pfd1Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(3U) | 5U, /*!< PCC3 Bus clock selection: kCLOCK_Pll3Pfd1Div1Clk */
    kCLOCK_Pcc3BusIpSrcPll3Pfd0Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(3U) | 6U, /*!< PCC3 Bus clock selection: kCLOCK_Pll3Pfd0Div2Clk */
    kCLOCK_Pcc3BusIpSrcPll3Pfd0Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(3U) | 7U, /*!< PCC3 Bus clock selection: kCLOCK_Pll3Pfd0Div1Clk */

    /* PCC4 platform PCS */
    kCLOCK_Pcc4PlatIpSrcSysOscDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 1U, /*!< PCC4 Platform clock selection: kCLOCK_AdSysOscDiv1Clk */
    kCLOCK_Pcc4PlatIpSrcFroDiv1 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 2U, /*!< PCC4 Platform clock selection: kCLOCK_AdFroDiv1Clk */
    kCLOCK_Pcc4PlatIpSrcPll3Pfd3Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 3U, /*!< PCC4 Platform clock selection: kCLOCK_Pll3Pfd3Div2Clk */
    kCLOCK_Pcc4PlatIpSrcPll3Pfd3Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 4U, /*!< PCC4 Platform clock selection: kCLOCK_Pll3Pfd3Div1Clk */
    kCLOCK_Pcc4PlatIpSrcPll3Pfd2Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 5U, /*!< PCC4 Platform clock selection: kCLOCK_Pll3Pfd2Div2Clk */
    kCLOCK_Pcc4PlatIpSrcPll3Pfd2Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 6U, /*!< PCC4 Platform clock selection: kCLOCK_Pll3Pfd2Div1Clk */
    kCLOCK_Pcc4PlatIpSrcPll3Pfd1Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 7U, /*!< PCC4 Platform clock selection: kCLOCK_Pll3Pfd1Div2Clk */

    /* PCC4 bus PCS */
    kCLOCK_Pcc4BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(4U) | 2U, /*!< PCC4 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc4BusIpSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 3U, /*!< PCC4 Bus clock selection: kCLOCK_AdSysOscDiv2Clk */
    kCLOCK_Pcc4BusIpSrcFroDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 4U, /*!< PCC4 Bus clock selection: kCLOCK_AdFroDiv2Clk */
    kCLOCK_Pcc4BusIpSrcXbarBus = CLOCK_IP_SOURCE_PCC_INDEX(4U) | 5U, /*!< PCC4 Bus clock selection: kCLOCK_XbarBusClk */
    kCLOCK_Pcc4BusIpSrcPll3VcoDiv =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 6U, /*!< PCC4 Bus clock selection: kCLOCK_Pll3VcoDivClk */
    kCLOCK_Pcc4BusIpSrcPll3Pfd0Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(4U) | 7U, /*!< PCC4 Bus clock selection: kCLOCK_Pll3Pfd0Div1Clk */

    /* PCC5 platform PCS */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd3Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 1U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd3Div2Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd2Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 2U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd2Div2Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd2Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 3U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd2Div1Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd1Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 4U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd1Div2Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd1Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 5U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd1Div1Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd0Div2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 6U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd0Div2Clk */
    kCLOCK_Pcc5PlatIpSrcPll4Pfd0Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 7U, /*!< PCC5 Platform clock selection: kCLOCK_Pll4Pfd0Div1Clk */

    /* PCC5 bus PCS */
    kCLOCK_Pcc5BusIpSrcLpo = CLOCK_IP_SOURCE_PCC_INDEX(5U) | 2U, /*!< PCC5 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_Pcc5BusIpSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 3U, /*!< PCC5 Bus clock selection: kCLOCK_LpavSysOscDiv2Clk */
    kCLOCK_Pcc5BusIpSrcFroDiv2 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 4U, /*!< PCC5 Bus clock selection: kCLOCK_LpavFroDiv2Clk */
    kCLOCK_Pcc5BusIpSrcLpavBus =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 5U, /*!< PCC5 Bus clock selection: kCLOCK_NicLpavBusClk */
    kCLOCK_Pcc5BusIpSrcPll4VcoDiv =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 6U, /*!< PCC5 Bus clock selection: kCLOCK_Pll4VcoDivClk */
    kCLOCK_Pcc5BusIpSrcPll4Pfd3Div1 =
        CLOCK_IP_SOURCE_PCC_INDEX(5U) | 7U, /*!< PCC5 Bus clock selection: kCLOCK_Pll4Pfd3Div1Clk */

    /* SAI0-1/MQS0 clock source */
    kCLOCK_Cm33SaiClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(1U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_Cm33SaiClkSrcRtdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(1U) | 1U, /*!< Common audio clock in RTD, see cgc_rtd_audclk_src_t. */
    kCLOCK_Cm33SaiClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(1U) | 2U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_Cm33SaiClkSrcSysOsc =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(1U) | 3U, /*!< SYSOSC main reference clock to the chip: kCLOCK_SysOscClk. */

    /* SAI2-3 clock source */
    kCLOCK_FusionSaiClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(2U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_FusionSaiClkSrcExtMclk1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(2U) | 1U, /*!< External audio master clock input 1. */
    kCLOCK_FusionSaiClkSrcSai3Rx =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(2U) | 2U, /*!< SAI3 receiver serial bit clock. Only for SAI2. */
    kCLOCK_FusionSaiClkSrcSai2Tx =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(2U) | 2U, /*!< SAI2 transmitter serial bit clock. Only for SAI3. */
    kCLOCK_FusionSaiClkSrcSysOsc =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(2U) | 3U, /*!< SYSOSC main reference clock to the chip: kCLOCK_SysOscClk. */
    /* MICFIL clock source */
    kCLOCK_FusionMicfilClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk */
    kCLOCK_FusionMicfilClkSrcFro24 = CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 1U, /*!< FRO24: kCLOCK_FroClk/8. */
    kCLOCK_FusionMicfilClkSrcSysOsc =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 2U, /*!< SYSOSC main reference clock to the chip: kCLOCK_SysOscClk. */
    kCLOCK_FusionMicfilClkSrcExtMclk1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 3U, /*!< External audio master clock input 1. */
    kCLOCK_FusionMicfilClkSrcRtcOsc = CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 4U, /*!< kCLOCK_RtcOscClk. */
    kCLOCK_FusionMicfilClkSrcLpo    = CLOCK_IP_SOURCE_NON_PCC_INDEX(3U) | 5U, /*!< kCLOCK_LpOscClk. */
    /* TPM2 clock source */
    kCLOCK_FusionTpm2ClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_FusionTpm2ClkSrcExtMclk1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 1U, /*!< External audio master clock input 1. */
    kCLOCK_FusionTpm2ClkSrcLpo =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x11U, /*!< PCC2 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_FusionTpm2ClkSrcSysOscDiv3 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x12U, /*!< PCC2 Bus clock selection: kCLOCK_RtdSysOscDiv3Clk */
    kCLOCK_FusionTpm2ClkSrcFroDiv3 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x13U, /*!< PCC2 Bus clock selection: kCLOCK_RtdFroDiv3Clk */
    kCLOCK_FusionTpm2ClkSrcFusionDspBus =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x14U, /*!< PCC2 Bus clock selection: kCLOCK_FusionDspBusClk */
    kCLOCK_FusionTpm2ClkSrcPll1VcoDiv =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x15U, /*!< PCC2 Bus clock selection: kCLOCK_Pll1VcoDivClk */
    kCLOCK_FusionTpm2ClkSrcPll0Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x16U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd2DivClk */
    kCLOCK_FusionTpm2ClkSrcPll0Pfd1Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(4U) | 0x17U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd1DivClk */
    /* TPM3 clock source */
    kCLOCK_FusionTpm3ClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_FusionTpm3ClkSrcRtdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 1U, /*!< Common audio clock in RTD, see cgc_rtd_audclk_src_t. */
    kCLOCK_FusionTpm3ClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 2U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_FusionTpm3ClkSrcLpo =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x11U, /*!< PCC2 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_FusionTpm3ClkSrcSysOscDiv3 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x12U, /*!< PCC2 Bus clock selection: kCLOCK_RtdSysOscDiv3Clk */
    kCLOCK_FusionTpm3ClkSrcFroDiv3 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x13U, /*!< PCC2 Bus clock selection: kCLOCK_RtdFroDiv3Clk */
    kCLOCK_FusionTpm3ClkSrcFusionDspBus =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x14U, /*!< PCC2 Bus clock selection: kCLOCK_FusionDspBusClk */
    kCLOCK_FusionTpm3ClkSrcPll1VcoDiv =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x15U, /*!< PCC2 Bus clock selection: kCLOCK_Pll1VcoDivClk */
    kCLOCK_FusionTpm3ClkSrcPll0Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x16U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd2DivClk */
    kCLOCK_FusionTpm3ClkSrcPll0Pfd1Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(5U) | 0x17U, /*!< PCC2 Bus clock selection: kCLOCK_Pll0Pfd1DivClk */

    /* SAI4-5/MQS1 clock source */
    kCLOCK_AdSaiClkSrcPll3Pfd1Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(6U) | 0U, /*!< PLL3 PFD1 DIV1 in AD: kCLOCK_Pll3Pfd1Div2Clk. */
    kCLOCK_AdSaiClkSrcAdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(6U) | 1U, /*!< Common audio clock in AD, see cgc_ad_audclk_src_t. */
    kCLOCK_AdSaiClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(6U) | 2U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_AdSaiClkSrcSysOsc =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(6U) | 3U, /*!< SYSOSC main reference clock to the chip: kCLOCK_SysOscClk. */
    /* TPM6-7 clock source */
    kCLOCK_AdTpm67ClkSrcPll3Pfd1Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0U, /*!< PLL3 PFD1 DIV1 in AD: kCLOCK_Pll3Pfd1Div2Clk. */
    kCLOCK_AdTpm67ClkSrcAdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 1U, /*!< Common audio clock in AD, see cgc_ad_audclk_src_t. */
    kCLOCK_AdTpm67ClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 2U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_AdTpm67ClkSrcLpo =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x12U, /*!< PCC4 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_AdTpm67ClkSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x13U, /*!< PCC4 Bus clock selection: kCLOCK_AdSysOscDiv2Clk */
    kCLOCK_AdTpm67ClkSrcFroDiv2 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x14U, /*!< PCC4 Bus clock selection: kCLOCK_AdFroDiv2Clk */
    kCLOCK_AdTpm67ClkSrcXbarBus =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x15U, /*!< PCC4 Bus clock selection: kCLOCK_XbarBusClk */
    kCLOCK_AdTpm67ClkSrcPll3VcoDiv =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x16U, /*!< PCC4 Bus clock selection: kCLOCK_Pll3VcoDivClk */
    kCLOCK_AdTpm67ClkSrcPll3Pfd0Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(7U) | 0x17U, /*!< PCC4 Bus clock selection: kCLOCK_Pll3Pfd0Div1Clk */

    /* SAI6-7/SPDIF clock source */
    kCLOCK_LpavSaiClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_LpavSaiClkSrcPll3Pfd1Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 1U, /*!< PLL3 PFD1 DIV1 in AD: kCLOCK_Pll3Pfd1Div1Clk. */
    kCLOCK_LpavSaiClkSrcRtdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 2U, /*!< Common audio clock in RTD, see cgc_rtd_audclk_src_t. */
    kCLOCK_LpavSaiClkSrcAdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 3U, /*!< Common audio clock in AD, see cgc_ad_audclk_src_t. */
    kCLOCK_LpavSaiClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 4U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_LpavSaiClkSrcSysOsc =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(8U) | 5U, /*!< SYSOSC main reference clock to the chip. */
    /* TPM8 clock source */
    kCLOCK_LpavTpm8ClkSrcPll1Pfd2Div =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0U, /*!< PLL1 PFD2 DIV in RTD: kCLOCK_Pll1Pfd2DivClk. */
    kCLOCK_LpavTpm8ClkSrcPll3Pfd1Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 1U, /*!< PLL3 PFD1 DIV1 in AD: kCLOCK_Pll3Pfd1Div1Clk. */
    kCLOCK_LpavTpm8ClkSrcRtdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 2U, /*!< Common audio clock in RTD, see cgc_rtd_audclk_src_t. */
    kCLOCK_LpavTpm8ClkSrcAdAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 3U, /*!< Common audio clock in AD, see cgc_ad_audclk_src_t. */
    kCLOCK_LpavTpm8ClkSrcLpavAudClk =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 4U, /*!< Common audio clock in LPAV, see cgc_lpav_audclk_src_t. */
    kCLOCK_LpavTpm8ClkSrcLpo =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x12U, /*!< PCC5 Bus clock selection: kCLOCK_LpOscClk */
    kCLOCK_LpavTpm8ClkSrcSysOscDiv2 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x13U, /*!< PCC5 Bus clock selection: kCLOCK_LpavSysOscDiv2Clk */
    kCLOCK_LpavTpm8ClkSrcFroDiv2 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x14U, /*!< PCC5 Bus clock selection: kCLOCK_LpavFroDiv2Clk */
    kCLOCK_LpavTpm8ClkSrcLpavBus =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x15U, /*!< PCC5 Bus clock selection: kCLOCK_NicLpavBusClk */
    kCLOCK_LpavTpm8ClkSrcPll4VcoDiv =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x16U, /*!< PCC5 Bus clock selection: kCLOCK_Pll4VcoDivClk */
    kCLOCK_LpavTpm8ClkSrcPll4Pfd3Div1 =
        CLOCK_IP_SOURCE_NON_PCC_INDEX(9U) | 0x17U, /*!< PCC5 Bus clock selection: kCLOCK_Pll4Pfd3Div1Clk */
} clock_ip_src_t;

/*!
 * @brief Clock source for LPTMR.
 */
typedef enum _clock_lptmr_src
{
    kCLOCK_LptmrSrcLPO1M  = 0U, /*!< LPO 1MHz clock. */
    kCLOCK_LptmrSrcRtc1K  = 1U, /*!< RTC 1KHz clock. */
    kCLOCK_LptmrSrcRtc32K = 2U, /*!< RTC 32KHz clock. */
    kCLOCK_LptmrSrcSysOsc = 3U, /*!< system OSC clock. */
} clock_lptmr_src_t;

/*!
 * @brief Peripheral clock name difinition used for clock gate, clock source
 * and clock divider setting.
 * [31:2] is defined as the corresponding register address.
 * [ 1:1] is used as indicator of existing of PCS.
 * [ 0:0] is used as indicator of existing of PCD/FRAC.
 */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,
    /* PCC 0 for CM33 */
    kCLOCK_Dma0           = (uint32_t)(PCC0_BASE + 0x4),
    kCLOCK_Dma0Ch0        = (uint32_t)(PCC0_BASE + 0x8),
    kCLOCK_Dma0Ch1        = (uint32_t)(PCC0_BASE + 0xc),
    kCLOCK_Dma0Ch2        = (uint32_t)(PCC0_BASE + 0x10),
    kCLOCK_Dma0Ch3        = (uint32_t)(PCC0_BASE + 0x14),
    kCLOCK_Dma0Ch4        = (uint32_t)(PCC0_BASE + 0x18),
    kCLOCK_Dma0Ch5        = (uint32_t)(PCC0_BASE + 0x1c),
    kCLOCK_Dma0Ch6        = (uint32_t)(PCC0_BASE + 0x20),
    kCLOCK_Dma0Ch7        = (uint32_t)(PCC0_BASE + 0x24),
    kCLOCK_Dma0Ch8        = (uint32_t)(PCC0_BASE + 0x28),
    kCLOCK_Dma0Ch9        = (uint32_t)(PCC0_BASE + 0x2c),
    kCLOCK_Dma0Ch10       = (uint32_t)(PCC0_BASE + 0x30),
    kCLOCK_Dma0Ch11       = (uint32_t)(PCC0_BASE + 0x34),
    kCLOCK_Dma0Ch12       = (uint32_t)(PCC0_BASE + 0x38),
    kCLOCK_Dma0Ch13       = (uint32_t)(PCC0_BASE + 0x3c),
    kCLOCK_Dma0Ch14       = (uint32_t)(PCC0_BASE + 0x40),
    kCLOCK_Dma0Ch15       = (uint32_t)(PCC0_BASE + 0x44),
    kCLOCK_Dma0Ch16       = (uint32_t)(PCC0_BASE + 0x48),
    kCLOCK_Dma0Ch17       = (uint32_t)(PCC0_BASE + 0x4c),
    kCLOCK_Dma0Ch18       = (uint32_t)(PCC0_BASE + 0x50),
    kCLOCK_Dma0Ch19       = (uint32_t)(PCC0_BASE + 0x54),
    kCLOCK_Dma0Ch20       = (uint32_t)(PCC0_BASE + 0x58),
    kCLOCK_Dma0Ch21       = (uint32_t)(PCC0_BASE + 0x5c),
    kCLOCK_Dma0Ch22       = (uint32_t)(PCC0_BASE + 0x60),
    kCLOCK_Dma0Ch23       = (uint32_t)(PCC0_BASE + 0x64),
    kCLOCK_Dma0Ch24       = (uint32_t)(PCC0_BASE + 0x68),
    kCLOCK_Dma0Ch25       = (uint32_t)(PCC0_BASE + 0x6c),
    kCLOCK_Dma0Ch26       = (uint32_t)(PCC0_BASE + 0x70),
    kCLOCK_Dma0Ch27       = (uint32_t)(PCC0_BASE + 0x74),
    kCLOCK_Dma0Ch28       = (uint32_t)(PCC0_BASE + 0x78),
    kCLOCK_Dma0Ch29       = (uint32_t)(PCC0_BASE + 0x7c),
    kCLOCK_Dma0Ch30       = (uint32_t)(PCC0_BASE + 0x80),
    kCLOCK_Dma0Ch31       = (uint32_t)(PCC0_BASE + 0x84),
    kCLOCK_Mu0A           = (uint32_t)(PCC0_BASE + 0x88),
    kCLOCK_Mu1A           = (uint32_t)(PCC0_BASE + 0x8c),
    kCLOCK_Mu2A           = (uint32_t)(PCC0_BASE + 0x90),
    kCLOCK_Syspm0         = (uint32_t)(PCC0_BASE + 0x98),
    kCLOCK_Wuu0           = (uint32_t)(PCC0_BASE + 0xa0),
    kCLOCK_UpowerMuARtd   = (uint32_t)(PCC0_BASE + 0xa4),
    kCLOCK_Wdog0          = (uint32_t)(PCC0_BASE + 0xb0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Wdog1          = (uint32_t)(PCC0_BASE + 0xb4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_TrdcMgr        = (uint32_t)(PCC0_BASE + 0xc4),
    kCLOCK_TrdcMbc0       = (uint32_t)(PCC0_BASE + 0xc8),
    kCLOCK_TrdcMbc1       = (uint32_t)(PCC0_BASE + 0xcc),
    kCLOCK_TrdcMbc2       = (uint32_t)(PCC0_BASE + 0xd0),
    kCLOCK_TrdcMbc3       = (uint32_t)(PCC0_BASE + 0xd4),
    kCLOCK_TrdcMrc        = (uint32_t)(PCC0_BASE + 0xd8),
    kCLOCK_Sema420        = (uint32_t)(PCC0_BASE + 0xdc),
    kCLOCK_Bbnsm          = (uint32_t)(PCC0_BASE + 0xe0),
    kCLOCK_Flexspi0       = (uint32_t)(PCC0_BASE + 0xe4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpit0          = (uint32_t)(PCC0_BASE + 0xec) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Flexio0        = (uint32_t)(PCC0_BASE + 0xf0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_I3c0           = (uint32_t)(PCC0_BASE + 0xf4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi0         = (uint32_t)(PCC0_BASE + 0xf8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi1         = (uint32_t)(PCC0_BASE + 0xfc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Adc0           = (uint32_t)(PCC0_BASE + 0x100) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Cmp0           = (uint32_t)(PCC0_BASE + 0x104),
    kCLOCK_Cmp1           = (uint32_t)(PCC0_BASE + 0x108),
    kCLOCK_Dac0           = (uint32_t)(PCC0_BASE + 0x10c) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Dac1           = (uint32_t)(PCC0_BASE + 0x110) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Cm33Cache      = (uint32_t)(PCC0_BASE + 0x118),
    kCLOCK_SentinelLpuart = (uint32_t)(PCC0_BASE + 0x130) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_PowersysWdog   = (uint32_t)(PCC0_BASE + 0x138) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Ocotp          = (uint32_t)(PCC0_BASE + 0x13c),

    /* PCC 1 for CM33 */
    kCLOCK_Tpiu     = (uint32_t)(PCC1_BASE + 0xc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Swo      = (uint32_t)(PCC1_BASE + 0x18) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Flexspi1 = (uint32_t)(PCC1_BASE + 0x48) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lptmr0   = (uint32_t)(PCC1_BASE + 0x4c),
    kCLOCK_Lptmr1   = (uint32_t)(PCC1_BASE + 0x50),
    kCLOCK_Tpm0     = (uint32_t)(PCC1_BASE + 0x54) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm1     = (uint32_t)(PCC1_BASE + 0x58) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c0   = (uint32_t)(PCC1_BASE + 0x60) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c1   = (uint32_t)(PCC1_BASE + 0x64) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart0  = (uint32_t)(PCC1_BASE + 0x68) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart1  = (uint32_t)(PCC1_BASE + 0x6c) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Sai0     = (uint32_t)(PCC1_BASE + 0x70),
    kCLOCK_Sai1     = (uint32_t)(PCC1_BASE + 0x74),
    kCLOCK_DigFiltA = (uint32_t)(PCC1_BASE + 0x78),
    kCLOCK_DigFiltB = (uint32_t)(PCC1_BASE + 0x7c),
    kCLOCK_Adc1     = (uint32_t)(PCC1_BASE + 0x88) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Flexcan  = (uint32_t)(PCC1_BASE + 0xa0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_RgpioA   = (uint32_t)(PCC1_BASE + 0xb4),
    kCLOCK_RgpioB   = (uint32_t)(PCC1_BASE + 0xb8),
    kCLOCK_RgpioC   = (uint32_t)(PCC1_BASE + 0xbc),

    /* PCC 2 for FusionF1 */
    kCLOCK_Mu1B    = (uint32_t)(PCC2_BASE + 0x0),
    kCLOCK_Wdog2   = (uint32_t)(PCC2_BASE + 0x4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm2    = (uint32_t)(PCC2_BASE + 0x14) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm3    = (uint32_t)(PCC2_BASE + 0x18) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Mrt     = (uint32_t)(PCC2_BASE + 0x1c),
    kCLOCK_Lpi2c2  = (uint32_t)(PCC2_BASE + 0x20) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c3  = (uint32_t)(PCC2_BASE + 0x24) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_I3c1    = (uint32_t)(PCC2_BASE + 0x28) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart2 = (uint32_t)(PCC2_BASE + 0x2c) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart3 = (uint32_t)(PCC2_BASE + 0x30) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi2  = (uint32_t)(PCC2_BASE + 0x34) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi3  = (uint32_t)(PCC2_BASE + 0x38) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Sai2    = (uint32_t)(PCC2_BASE + 0x3c),
    kCLOCK_Sai3    = (uint32_t)(PCC2_BASE + 0x40),
    kCLOCK_Micfil  = (uint32_t)(PCC2_BASE + 0x44),

    /* PCC 3 for CA35 */
    kCLOCK_Dma1         = (uint32_t)(PCC3_BASE + 0x4),
    kCLOCK_Dma1Ch0      = (uint32_t)(PCC3_BASE + 0x8),
    kCLOCK_Dma1Ch1      = (uint32_t)(PCC3_BASE + 0xc),
    kCLOCK_Dma1Ch2      = (uint32_t)(PCC3_BASE + 0x10),
    kCLOCK_Dma1Ch3      = (uint32_t)(PCC3_BASE + 0x14),
    kCLOCK_Dma1Ch4      = (uint32_t)(PCC3_BASE + 0x18),
    kCLOCK_Dma1Ch5      = (uint32_t)(PCC3_BASE + 0x1c),
    kCLOCK_Dma1Ch6      = (uint32_t)(PCC3_BASE + 0x20),
    kCLOCK_Dma1Ch7      = (uint32_t)(PCC3_BASE + 0x24),
    kCLOCK_Dma1Ch8      = (uint32_t)(PCC3_BASE + 0x28),
    kCLOCK_Dma1Ch9      = (uint32_t)(PCC3_BASE + 0x2c),
    kCLOCK_Dma1Ch10     = (uint32_t)(PCC3_BASE + 0x30),
    kCLOCK_Dma1Ch11     = (uint32_t)(PCC3_BASE + 0x34),
    kCLOCK_Dma1Ch12     = (uint32_t)(PCC3_BASE + 0x38),
    kCLOCK_Dma1Ch13     = (uint32_t)(PCC3_BASE + 0x3c),
    kCLOCK_Dma1Ch14     = (uint32_t)(PCC3_BASE + 0x40),
    kCLOCK_Dma1Ch15     = (uint32_t)(PCC3_BASE + 0x44),
    kCLOCK_Dma1Ch16     = (uint32_t)(PCC3_BASE + 0x48),
    kCLOCK_Dma1Ch17     = (uint32_t)(PCC3_BASE + 0x4c),
    kCLOCK_Dma1Ch18     = (uint32_t)(PCC3_BASE + 0x50),
    kCLOCK_Dma1Ch19     = (uint32_t)(PCC3_BASE + 0x54),
    kCLOCK_Dma1Ch20     = (uint32_t)(PCC3_BASE + 0x58),
    kCLOCK_Dma1Ch21     = (uint32_t)(PCC3_BASE + 0x5c),
    kCLOCK_Dma1Ch22     = (uint32_t)(PCC3_BASE + 0x60),
    kCLOCK_Dma1Ch23     = (uint32_t)(PCC3_BASE + 0x64),
    kCLOCK_Dma1Ch24     = (uint32_t)(PCC3_BASE + 0x68),
    kCLOCK_Dma1Ch25     = (uint32_t)(PCC3_BASE + 0x6c),
    kCLOCK_Dma1Ch26     = (uint32_t)(PCC3_BASE + 0x70),
    kCLOCK_Dma1Ch27     = (uint32_t)(PCC3_BASE + 0x74),
    kCLOCK_Dma1Ch28     = (uint32_t)(PCC3_BASE + 0x78),
    kCLOCK_Dma1Ch29     = (uint32_t)(PCC3_BASE + 0x7c),
    kCLOCK_Dma1Ch30     = (uint32_t)(PCC3_BASE + 0x80),
    kCLOCK_Dma1Ch31     = (uint32_t)(PCC3_BASE + 0x84),
    kCLOCK_Mu0B         = (uint32_t)(PCC3_BASE + 0x88),
    kCLOCK_Mu3A         = (uint32_t)(PCC3_BASE + 0x8c),
    kCLOCK_Wuu1         = (uint32_t)(PCC3_BASE + 0x98),
    kCLOCK_Syspm1       = (uint32_t)(PCC3_BASE + 0x9c),
    kCLOCK_UpowerMuAApd = (uint32_t)(PCC3_BASE + 0xa0),
    kCLOCK_Wdog3        = (uint32_t)(PCC3_BASE + 0xa8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Wdog4        = (uint32_t)(PCC3_BASE + 0xac) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Caam         = (uint32_t)(PCC3_BASE + 0xb8),
    kCLOCK_XrdcMgr      = (uint32_t)(PCC3_BASE + 0xbc),
    kCLOCK_Sema421      = (uint32_t)(PCC3_BASE + 0xc0),
    kCLOCK_Lpit1        = (uint32_t)(PCC3_BASE + 0xc8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm4         = (uint32_t)(PCC3_BASE + 0xcc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm5         = (uint32_t)(PCC3_BASE + 0xd0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Flexio1      = (uint32_t)(PCC3_BASE + 0xd4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_I3c2         = (uint32_t)(PCC3_BASE + 0xd8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c4       = (uint32_t)(PCC3_BASE + 0xdc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c5       = (uint32_t)(PCC3_BASE + 0xe0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart4      = (uint32_t)(PCC3_BASE + 0xe4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart5      = (uint32_t)(PCC3_BASE + 0xe8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi4       = (uint32_t)(PCC3_BASE + 0xec) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpspi5       = (uint32_t)(PCC3_BASE + 0xf0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,

    /* PCC 4 for CA35 */
    kCLOCK_Flexspi2 = (uint32_t)(PCC4_BASE + 0x4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm6     = (uint32_t)(PCC4_BASE + 0x8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Tpm7     = (uint32_t)(PCC4_BASE + 0xc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c6   = (uint32_t)(PCC4_BASE + 0x10) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpi2c7   = (uint32_t)(PCC4_BASE + 0x14) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart6  = (uint32_t)(PCC4_BASE + 0x18) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpuart7  = (uint32_t)(PCC4_BASE + 0x1c) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Sai4     = (uint32_t)(PCC4_BASE + 0x20),
    kCLOCK_Sai5     = (uint32_t)(PCC4_BASE + 0x24),
    kCLOCK_DigFiltE = (uint32_t)(PCC4_BASE + 0x28),
    kCLOCK_DigFiltF = (uint32_t)(PCC4_BASE + 0x2c),
    kCLOCK_Usdhc0   = (uint32_t)(PCC4_BASE + 0x34) | PCC_PCS_AVAIL_MASK,
    kCLOCK_Usdhc1   = (uint32_t)(PCC4_BASE + 0x38) | PCC_PCS_AVAIL_MASK,
    kCLOCK_Usdhc2   = (uint32_t)(PCC4_BASE + 0x3c) | PCC_PCS_AVAIL_MASK,
    kCLOCK_Usb0     = (uint32_t)(PCC4_BASE + 0x40),
    kCLOCK_Usb0Phy  = (uint32_t)(PCC4_BASE + 0x44),
    kCLOCK_Usb1     = (uint32_t)(PCC4_BASE + 0x48),
    kCLOCK_Usb1Phy  = (uint32_t)(PCC4_BASE + 0x4c),
    kCLOCK_UsbXbar  = (uint32_t)(PCC4_BASE + 0x50),
    kCLOCK_Enet     = (uint32_t)(PCC4_BASE + 0x54),
    kCLOCK_RgpioE   = (uint32_t)(PCC4_BASE + 0x78),
    kCLOCK_RgpioF   = (uint32_t)(PCC4_BASE + 0x7c),

    /* PCC 5 for HiFi4 */
    kCLOCK_Dma2      = (uint32_t)(PCC5_BASE + 0x0),
    kCLOCK_Dma2Ch0   = (uint32_t)(PCC5_BASE + 0x4),
    kCLOCK_Dma2Ch1   = (uint32_t)(PCC5_BASE + 0x8),
    kCLOCK_Dma2Ch2   = (uint32_t)(PCC5_BASE + 0xc),
    kCLOCK_Dma2Ch3   = (uint32_t)(PCC5_BASE + 0x10),
    kCLOCK_Dma2Ch4   = (uint32_t)(PCC5_BASE + 0x14),
    kCLOCK_Dma2Ch5   = (uint32_t)(PCC5_BASE + 0x18),
    kCLOCK_Dma2Ch6   = (uint32_t)(PCC5_BASE + 0x1c),
    kCLOCK_Dma2Ch7   = (uint32_t)(PCC5_BASE + 0x20),
    kCLOCK_Dma2Ch8   = (uint32_t)(PCC5_BASE + 0x24),
    kCLOCK_Dma2Ch9   = (uint32_t)(PCC5_BASE + 0x28),
    kCLOCK_Dma2Ch10  = (uint32_t)(PCC5_BASE + 0x2c),
    kCLOCK_Dma2Ch11  = (uint32_t)(PCC5_BASE + 0x30),
    kCLOCK_Dma2Ch12  = (uint32_t)(PCC5_BASE + 0x34),
    kCLOCK_Dma2Ch13  = (uint32_t)(PCC5_BASE + 0x38),
    kCLOCK_Dma2Ch14  = (uint32_t)(PCC5_BASE + 0x3c),
    kCLOCK_Dma2Ch15  = (uint32_t)(PCC5_BASE + 0x40),
    kCLOCK_Dma2Ch16  = (uint32_t)(PCC5_BASE + 0x44),
    kCLOCK_Dma2Ch17  = (uint32_t)(PCC5_BASE + 0x48),
    kCLOCK_Dma2Ch18  = (uint32_t)(PCC5_BASE + 0x4c),
    kCLOCK_Dma2Ch19  = (uint32_t)(PCC5_BASE + 0x50),
    kCLOCK_Dma2Ch20  = (uint32_t)(PCC5_BASE + 0x54),
    kCLOCK_Dma2Ch21  = (uint32_t)(PCC5_BASE + 0x58),
    kCLOCK_Dma2Ch22  = (uint32_t)(PCC5_BASE + 0x5c),
    kCLOCK_Dma2Ch23  = (uint32_t)(PCC5_BASE + 0x60),
    kCLOCK_Dma2Ch24  = (uint32_t)(PCC5_BASE + 0x64),
    kCLOCK_Dma2Ch25  = (uint32_t)(PCC5_BASE + 0x68),
    kCLOCK_Dma2Ch26  = (uint32_t)(PCC5_BASE + 0x6c),
    kCLOCK_Dma2Ch27  = (uint32_t)(PCC5_BASE + 0x70),
    kCLOCK_Dma2Ch28  = (uint32_t)(PCC5_BASE + 0x74),
    kCLOCK_Dma2Ch29  = (uint32_t)(PCC5_BASE + 0x78),
    kCLOCK_Dma2Ch30  = (uint32_t)(PCC5_BASE + 0x7c),
    kCLOCK_Dma2Ch31  = (uint32_t)(PCC5_BASE + 0x80),
    kCLOCK_Mu2B      = (uint32_t)(PCC5_BASE + 0x84),
    kCLOCK_Mu3B      = (uint32_t)(PCC5_BASE + 0x88),
    kCLOCK_Sema422   = (uint32_t)(PCC5_BASE + 0x8c),
    kCLOCK_Tpm8      = (uint32_t)(PCC5_BASE + 0xa0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Sai6      = (uint32_t)(PCC5_BASE + 0xa4),
    kCLOCK_Sai7      = (uint32_t)(PCC5_BASE + 0xa8),
    kCLOCK_Spdif     = (uint32_t)(PCC5_BASE + 0xac),
    kCLOCK_Isi       = (uint32_t)(PCC5_BASE + 0xb0),
    kCLOCK_CsiRegs   = (uint32_t)(PCC5_BASE + 0xb4),
    kCLOCK_Csi       = (uint32_t)(PCC5_BASE + 0xbc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Dsi       = (uint32_t)(PCC5_BASE + 0xc0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Wdog5     = (uint32_t)(PCC5_BASE + 0xc8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Epdc      = (uint32_t)(PCC5_BASE + 0xcc) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Pxp       = (uint32_t)(PCC5_BASE + 0xd0),
    kCLOCK_Gpu2d     = (uint32_t)(PCC5_BASE + 0xf0) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Gpu3d     = (uint32_t)(PCC5_BASE + 0xf4) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Dcnano    = (uint32_t)(PCC5_BASE + 0xf8) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_Lpddr4    = (uint32_t)(PCC5_BASE + 0x108),
    kCLOCK_CsiClkUi  = (uint32_t)(PCC5_BASE + 0x10c) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_CsiClkEsc = (uint32_t)(PCC5_BASE + 0x110) | PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK,
    kCLOCK_RgpioD    = (uint32_t)(PCC5_BASE + 0x114),

    /* Non-PCC IPs */
    kCLOCK_Mqs0 = (uint32_t)(CGC_RTD_BASE + 0x90c) | IP_NAME_NON_PCC_FLAG_MASK,
    kCLOCK_Mqs1 = (uint32_t)(CGC_AD_BASE + 0x90c) | IP_NAME_NON_PCC_FLAG_MASK,
} clock_ip_name_t;

/*!
 * @brief CGC status return codes.
 */
enum
{
    kStatus_CGC_Busy       = MAKE_STATUS(kStatusGroup_SCG, 1), /*!< Clock is busy. */
    kStatus_CGC_InvalidSrc = MAKE_STATUS(kStatusGroup_SCG, 2)  /*!< Invalid source. */
};

/*!
 * @brief CGC system clock type.
 */
typedef enum _cgc_sys_clk
{
    /* RTD */
    kCGC_SysClkSlow,     /*!< System slow clock. */
    kCGC_SysClkBus,      /*!< Bus clock. */
    kCGC_SysClkCorePlat, /*!< Core/Platform clock. */

    /* LPAV HIFI */
    kCGC_SysClkHifi4,   /*!< Hifi4 core clock. */
    kCGC_SysClkNicHifi, /*!< Hifi4 platform clock. */
    /* NIC LPAV */
    kCGC_SysClkLpavAxi, /*!< LPAV AXI clock. */
    kCGC_SysClkLpavAhb, /*!< LPAV AHB clock. */
    kCGC_SysClkLpavBus, /*!< LPAV Bus clock. */
} cgc_sys_clk_t;

/*!
 * @brief CGC system clock source for RTD.
 */
typedef enum _cgc_rtd_sys_clk_src
{
    kCGC_RtdSysClkSrcFro      = 0U, /*!< FRO192. */
    kCGC_RtdSysClkSrcPll0Pfd0 = 1U, /*!< PLL0 PFD0. */
    kCGC_RtdSysClkSrcPll1Pfd0 = 2U, /*!< PLL1 PFD0. */
    kCGC_RtdSysClkSrcSysOsc   = 3U, /*!< System OSC. */
    kCGC_RtdSysClkSrcRtcOsc   = 4U, /*!< RTC OSC. */
    kCGC_RtdSysClkSrcLvds     = 5U, /*!< LVDS XCVR. */
    kCGC_RtdSysClkSrcPll0     = 6U, /*!< PLL0. */
} cgc_rtd_sys_clk_src_t;

/*!
 * @brief CGC system clock source for NIC in AD.
 */
typedef enum _cgc_nic_sys_clk_src
{
    kCGC_NicSysClkSrcFro      = 0U, /*!< FRO192. */
    kCGC_NicSysClkSrcPll3Pfd0 = 1U, /*!< PLL0 PFD0. */
    kCGC_NicSysClkSrcSysOsc   = 2U, /*!< System OSC. */
    kCGC_NicSysClkSrcLvds     = 3U, /*!< LVDS XCVR. */
} cgc_nic_sys_clk_src_t;

/*!
 * @brief CGC system clock source for HIFI4 in LPAV.
 */
typedef enum _cgc_hifi_sys_clk_src
{
    kCGC_HifiSysClkSrcFro      = 0U, /*!< FRO192. */
    kCGC_HifiSysClkSrcPll4     = 1U, /*!< PLL4. */
    kCGC_HifiSysClkSrcPll4Pfd0 = 2U, /*!< PLL4 PFD0. */
    kCGC_HifiSysClkSrcSysOsc   = 3U, /*!< System OSC. */
    kCGC_HifiSysClkSrcLvds     = 4U, /*!< LVDS XCVR. */
} cgc_hifi_sys_clk_src_t;

/*!
 * @brief CGC system clock source for LPAV.
 */
typedef enum _cgc_lpav_sys_clk_src
{
    kCGC_LpavSysClkSrcFro      = 0U, /*!< FRO192. */
    kCGC_LpavSysClkSrcPll4Pfd1 = 1U, /*!< PLL4 PFD1. */
    kCGC_LpavSysClkSrcSysOsc   = 2U, /*!< System OSC. */
    kCGC_LpavSysClkSrcLvds     = 3U, /*!< LVDS XCVR. */
} cgc_lpav_sys_clk_src_t;

/*!
 * @brief CGC system clock source for DDR.
 */
typedef enum _cgc_ddr_sys_clk_src
{
    kCGC_DdrSysClkSrcFro      = 0U, /*!< FRO192. */
    kCGC_DdrSysClkSrcPll4Pfd1 = 1U, /*!< PLL4 PFD1. */
    kCGC_DdrSysClkSrcSysOsc   = 2U, /*!< System OSC. */
    kCGC_DdrSysClkSrcLvds     = 3U, /*!< LVDS XCVR. */
} cgc_ddr_sys_clk_src_t;

/*!
 * @brief CGC system clock configuration for RTD.
 */
typedef struct _cgc_rtd_sys_clk_config
{
    uint32_t divSlow : 6;   /*!< Slow clock divider, selected division is the value of the field + 1 */
    uint32_t : 1;           /*!< Reserved. */
    uint32_t divBus : 6;    /*!< Bus clock divider, selected division is the value of the field + 1. */
    uint32_t : 8;           /*!< Reserved. */
    uint32_t divCore : 6;   /*!< Core/Platform clock divider, selected division is the value of the field + 1. */
    uint32_t switchFin : 1; /*!< 1: Clock is running. 0: Clock is not running. */
    uint32_t src : 3;       /*!< System clock source, see @ref cgc_rtd_sys_clk_src_t. */
    uint32_t locked : 1;    /*!< Clock register locked. */
} cgc_rtd_sys_clk_config_t;

/*!
 * @brief CGC system clock configuration for HIFI4 DSP.
 */
typedef struct _cgc_hifi_sys_clk_config
{
    uint32_t : 14;          /*!< Reserved. */
    uint32_t divPlat : 6;   /*!< Platform clock divider, selected division is the value of the field + 1. */
    uint32_t : 1;           /*!< Reserved. */
    uint32_t divCore : 6;   /*!< Core clock divider, selected division is the value of the field + 1. */
    uint32_t switchFin : 1; /*!< 1: Clock is running. 0: Clock is not running. */
    uint32_t src : 3;       /*!< System clock source, see @ref cgc_hifi_sys_clk_src_t. */
    uint32_t locked : 1;    /*!< Clock register locked. */
} cgc_hifi_sys_clk_config_t;

/*!
 * @brief CGC system clock configuration for LPAV.
 */
typedef struct _cgc_lpav_sys_clk_config
{
    uint32_t : 7;           /*!< Reserved. */
    uint32_t divBus : 6;    /*!< Platform clock divider, selected division is the value of the field + 1. */
    uint32_t : 1;           /*!< Reserved. */
    uint32_t divAhb : 6;    /*!< Platform clock divider, selected division is the value of the field + 1. */
    uint32_t : 1;           /*!< Reserved. */
    uint32_t divAxi : 6;    /*!< Core clock divider, selected division is the value of the field + 1. */
    uint32_t switchFin : 1; /*!< 1: Clock is running. 0: Clock is not running. */
    uint32_t src : 2;       /*!< System clock source, see @ref cgc_lpav_sys_clk_src_t. */
    uint32_t : 1;           /*!< Reserved. */
    uint32_t locked : 1;    /*!< Clock register locked. */
} cgc_lpav_sys_clk_config_t;

/*!
 * @brief CGC system clock configuration for DDR in LPAV.
 */
typedef struct _cgc_ddr_sys_clk_config
{
    uint32_t : 21;          /*!< Reserved. */
    uint32_t divDdr : 6;    /*!< DDR clock divider, selected division is the value of the field + 1. */
    uint32_t switchFin : 1; /*!< 1: Clock is running. 0: Clock is not running. */
    uint32_t src : 3;       /*!< System clock source, see @ref cgc_lpav_sys_clk_src_t. */
    uint32_t locked : 1;    /*!< Clock register locked. */
} cgc_ddr_sys_clk_config_t;

/*!
 * @brief CGC clock out configuration (CLKOUTCFG) in RTD.
 */
typedef enum _clock_rtd_clkout_src
{
    kClockRtdClkoutSelCm33Core      = 0U,  /*!< CGC CM33 Core/Platform clock. */
    kClockRtdClkoutSelCm33Bus       = 1U,  /*!< CGC CM33 Bus clock. */
    kClockRtdClkoutSelCm33Slow      = 2U,  /*!< CGC CM33 Slow clock. */
    kClockRtdClkoutSelFusionDspCore = 3U,  /*!< CGC Fusion DSP Core/Platform clock. */
    kClockRtdClkoutSelFusionDspBus  = 4U,  /*!< CGC Fusion DSP Bus clock. */
    kClockRtdClkoutSelFusionDspSlow = 5U,  /*!< CGC Fusion DSP Slow clock. */
    kClockRtdClkoutSelFro48         = 6U,  /*!< FRO48: kCLOCK_FroClk/4. */
    kClockRtdClkoutSelPll0VcoDiv    = 7U,  /*!< PLL0 VCO DIV: kCLOCK_Pll0VcoDivClk. */
    kClockRtdClkoutSelPll1VcoDiv    = 8U,  /*!< PLL1 VCO DIV: kCLOCK_Pll1VcoDivClk. */
    kClockRtdClkoutSelSysOsc        = 9U,  /*!< System OSC. */
    kClockRtdClkoutSelLpOsc         = 10U, /*!< CGC LPOSC clock. */
} clock_rtd_clkout_src_t;

/*!
 * @brief CGC clock out configuration (CLKOUTCFG) in LPAV.
 */
typedef enum _clock_lpav_clkout_src
{
    kClockLpavClkoutSelHifi4      = 0U,  /*!< CGC HIFI4 core clock. */
    kClockLpavClkoutSelNicHifi    = 1U,  /*!< CGC HIFI4 platform clock. */
    kClockLpavClkoutSelLpavAxi    = 2U,  /*!< CGC NIC LPAV AXI clock. */
    kClockLpavClkoutSelLpavAhb    = 3U,  /*!< CGC NIC LPAV AHB clock. */
    kClockLpavClkoutSelLpavBus    = 4U,  /*!< CGC LPAV Bus clock. */
    kClockLpavClkoutSelDdr        = 5U,  /*!< CGC DDR clock. */
    kClockLpavClkoutSelFro48      = 6U,  /*!< FRO48: kCLOCK_FroClk/4. */
    kClockLpavClkoutSelPll4VcoDiv = 7U,  /*!< PLL4 VCO DIV: kCLOCK_Pll4VcoDivClk. */
    kClockLpavClkoutSelSysOsc     = 9U,  /*!< System OSC. */
    kClockLpavClkoutSelLpOsc      = 10U, /*!< CGC LPOSC clock. */
} clock_lpav_clkout_src_t;

/*!
 * @brief CGC asynchronous clock type.
 */
typedef enum _cgc_async_clk
{
    kCGC_AsyncDiv1Clk     = 1U,  /*!< The async clock by DIV1, e.g. SOSCDIV1_CLK, FRODIV1_CLK. */
    kCGC_AsyncDiv2Clk     = 2U,  /*!< The async clock by DIV2, e.g. SOSCDIV2_CLK, FRODIV2_CLK. */
    kCGC_AsyncDiv3Clk     = 3U,  /*!< The async clock by DIV3, e.g. SOSCDIV3_CLK, FRODIV3_CLK. */
    kCGC_AsyncVcoClk      = 4U,  /*!< The async clock by PLL VCO DIV. */
    kCGC_AsyncPfd0Div1Clk = 5U,  /*!< The async clock by PLL PFD0 DIV1. */
    kCGC_AsyncPfd0Div2Clk = 6U,  /*!< The async clock by PLL PFD0 DIV2. */
    kCGC_AsyncPfd1Div1Clk = 7U,  /*!< The async clock by PLL PFD1 DIV or DIV1. */
    kCGC_AsyncPfd1Div2Clk = 8U,  /*!< The async clock by PLL PFD1 DIV2. */
    kCGC_AsyncPfd2Div1Clk = 9U,  /*!< The async clock by PLL PFD2 DIV or DIV1. */
    kCGC_AsyncPfd2Div2Clk = 10U, /*!< The async clock by PLL PFD2 DIV2. */
    kCGC_AsyncPfd3Div1Clk = 11U, /*!< The async clock by PLL PFD3 DIV1. */
    kCGC_AsyncPfd3Div2Clk = 12U, /*!< The async clock by PLL PFD3 DIV2. */
} cgc_async_clk_t;

/*!
 * @brief CGC system OSC monitor mode.
 */
typedef enum _cgc_sosc_monitor_mode
{
    kCGC_SysOscMonitorDisable = 0U,                      /*!< Monitor disabled. */
    kCGC_SysOscMonitorInt     = CGC_SOSCCSR_SOSCCM_MASK, /*!< Interrupt when the system OSC error is detected. */
    kCGC_SysOscMonitorReset =
        CGC_SOSCCSR_SOSCCM_MASK | CGC_SOSCCSR_SOSCCMRE_MASK /*!< Reset when the system OSC error is detected. */
} cgc_sosc_monitor_mode_t;

/*! @brief OSC work mode. */
typedef enum _cgc_sosc_mode
{
    kCGC_SysOscModeExt         = CGC_SOSCCFG_SYSOSC_BYPASS_EN_MASK, /*!< Use external clock. */
    kCGC_SysOscModeOscLowPower = 0,                                 /*!< Oscillator low power. */
    kCGC_SysOscModeOscHighGain = CGC_SOSCCFG_HGO_MASK               /*!< Oscillator high gain. */
} cgc_sosc_mode_t;

/*! @brief OSC enable mode. */
enum _cgc_sosc_enable_mode
{
    kCGC_SysOscEnableInDeepSleep = CGC_SOSCCSR_SOSCDSEN_MASK, /*!< Enable OSC in deep sleep mode. */
    kCGC_SysOscEnableInPowerDown = CGC_SOSCCSR_SOSCPDEN_MASK, /*!< Enable OSC in low power mode. */
};

/*!
 * @brief CGC system OSC configuration.
 */
typedef struct _cgc_sosc_config
{
    uint32_t freq;                       /*!< System OSC frequency. */
    cgc_sosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected. */
    uint8_t enableMode;                  /*!< Enable mode, OR'ed value of _cgc_sosc_enable_mode. */

    cgc_sosc_mode_t workMode; /*!< OSC work mode. */
} cgc_sosc_config_t;

/*! @brief FRO enable mode. */
enum _cgc_fro_enable_mode
{
    kCGC_FroEnableInDeepSleep = CGC_FROCSR_FRODSEN_MASK, /*!< Enable FRO in deep sleep mode. */
};

/*!
 * @brief CGC FRO clock configuration.
 */
typedef struct _cgc_fro_config
{
    uint32_t enableMode; /*!< Enable mode, OR'ed value of _cgc_fro_enable_mode. */
} cgc_fro_config_t;

/*! @brief LPOSC enable mode. */
enum _cgc_lposc_enable_mode
{
    kCGC_LposcEnableInDeepSleep = CGC_LPOSCCSR_LPOSCDSEN_MASK, /*!< Enable OSC in deep sleep mode. */
    kCGC_LposcEnableInPowerDown = CGC_LPOSCCSR_LPOSCPDEN_MASK, /*!< Enable OSC in low power mode. */
};

/*!
 * @brief CGC LPOSC clock configuration.
 */
typedef struct _cgc_lposc_config
{
    uint32_t enableMode; /*!< Enable mode, OR'ed value of _cgc_lposc_enable_mode. */
} cgc_lposc_config_t;

/*!
 * @brief CGC PLL clock source.
 */
typedef enum _cgc_pll_src
{
    kCGC_PllSrcSysOsc, /*!< PLL clock source is system OSC. */
    kCGC_PllSrcFro24M, /*!< PLL clock source is FRO 24M. */
} cgc_pll_src_t;

/*! @brief PLL enable mode. */
enum _cgc_pll_enable_mode
{
    kCGC_PllEnable            = CGC_PLL0CSR_PLL0EN_MASK,  /*!< Enable PLL clock. */
    kCGC_PllEnableInDeepSleep = CGC_PLL0CSR_PLL0DSEN_MASK /*!< Enable PLL in deep sleep mode. */
};

/*!
 * @brief CGC PLL PFD clouk out select.
 */
typedef enum _cgc_pll_pfd_clkout
{
    kCGC_PllPfd0Clk = 0U,  /*!< PFD0 output clock selected. */
    kCGC_PllPfd1Clk = 8U,  /*!< PFD1 output clock selected. */
    kCGC_PllPfd2Clk = 16U, /*!< PFD2 output clock selected. */
    kCGC_PllPfd3Clk = 24U  /*!< PFD3 output clock selected. */
} cgc_pll_pfd_clkout_t;

/*! @brief PLL0 Multiplication Factor */
typedef enum _cgc_pll0_mult
{
    kCGC_Pll0Mult15 = 1U, /*!< Divide by 15 */
    kCGC_Pll0Mult16 = 2U, /*!< Divide by 16 */
    kCGC_Pll0Mult20 = 3U, /*!< Divide by 20 */
    kCGC_Pll0Mult22 = 4U, /*!< Divide by 22 */
    kCGC_Pll0Mult25 = 5U, /*!< Divide by 25 */
    kCGC_Pll0Mult30 = 6U, /*!< Divide by 30 */
} cgc_pll0_mult_t;

/*!
 * @brief CGC PLL0 configuration.
 */
typedef struct _cgc_pll0_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _cgc_pll_enable_mode */

    uint8_t div1;    /*!< PLLDIV_VCO divider value. Disabled when div1 == 0. */
    uint8_t pfd1Div; /*!< PLLDIV_PFD_0 DIV1 divider value. Disabled when pfd1Div == 0. */
    uint8_t pfd2Div; /*!< PLLDIV_PFD_0 DIV2 divider value. Disabled when pfd2Div == 0. */

    cgc_pll_src_t src;    /*!< Clock source. */
    cgc_pll0_mult_t mult; /*!< PLL multiplier. */
} cgc_pll0_config_t;

/*!
 * @brief CGC RTC OSC monitor mode.
 */
typedef enum _cgc_rosc_monitor_mode
{
    kCGC_RtcOscMonitorDisable = 0U,                       /*!< Monitor disabled. */
    kCGC_RtcOscMonitorInt     = CGC_ROSCCTRL_ROSCCM_MASK, /*!< Interrupt when the RTC OSC error is detected. */
    kCGC_RtcOscMonitorReset =
        CGC_ROSCCTRL_ROSCCM_MASK | CGC_ROSCCTRL_ROSCCMRE_MASK /*!< Reset when the RTC OSC error is detected. */
} cgc_rosc_monitor_mode_t;

/*!
 * @brief CGC RTC OSC configuration.
 */
typedef struct _cgc_rosc_config
{
    cgc_rosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected. */
} cgc_rosc_config_t;

/*! @brief PLL1 Multiplication Factor */
typedef enum _cgc_pll1_mult
{
    kCGC_Pll1Mult16 = 16U, /*!< Divide by 16 */
    kCGC_Pll1Mult17 = 17U, /*!< Divide by 17 */
    kCGC_Pll1Mult20 = 20U, /*!< Divide by 20 */
    kCGC_Pll1Mult22 = 22U, /*!< Divide by 22 */
    kCGC_Pll1Mult27 = 27U, /*!< Divide by 27 */
    kCGC_Pll1Mult33 = 33U, /*!< Divide by 33 */
} cgc_pll1_mult_t;

/*!
 * @brief CGC PLL1 configuration.
 */
typedef struct _cgc_pll1_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _cgc_pll_enable_mode */

    uint8_t div1;    /*!< PLLDIV_VCO divider value. Disabled when div1 == 0. */
    uint8_t pfd1Div; /*!< PLLDIV_PFD_0 DIV1 divider value. Disabled when pfd1Div == 0. */
    uint8_t pfd2Div; /*!< PLLDIV_PFD_0 DIV2 divider value. Disabled when pfd2Div == 0. */

    cgc_pll_src_t src;    /*!< Clock source. */
    cgc_pll1_mult_t mult; /*!< PLL1 multiplier. */

    uint32_t num : 30;   /*!< 30-bit numerator of the PLL1 Fractional-Loop divider. */
    uint32_t denom : 30; /*!< 30-bit denominator of the PLL1 Fractional-Loop divider. */
} cgc_pll1_config_t;

/*! @brief PLL4 Multiplication Factor */
typedef enum _cgc_pll4_mult
{
    kCGC_Pll4Mult16 = 16U, /*!< Divide by 16 */
    kCGC_Pll4Mult17 = 17U, /*!< Divide by 17 */
    kCGC_Pll4Mult20 = 20U, /*!< Divide by 20 */
    kCGC_Pll4Mult22 = 22U, /*!< Divide by 22 */
    kCGC_Pll4Mult27 = 27U, /*!< Divide by 27 */
    kCGC_Pll4Mult33 = 33U, /*!< Divide by 33 */
} cgc_pll4_mult_t;

/*!
 * @brief CGC PLL4 configuration.
 */
typedef struct _cgc_pll4_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _cgc_pll_enable_mode */

    uint8_t div1;     /*!< PLLDIV_VCO divider value. Disabled when div1 == 0. */
    uint8_t pfd0Div1; /*!< PLLDIV_PFD_0 DIV1 divider value. Disabled when pfd0Div1 == 0. */
    uint8_t pfd0Div2; /*!< PLLDIV_PFD_0 DIV2 divider value. Disabled when pfd0Div2 == 0. */
    uint8_t pfd1Div1; /*!< PLLDIV_PFD_0 DIV3 divider value. Disabled when pfd1Div1 == 0. */
    uint8_t pfd1Div2; /*!< PLLDIV_PFD_0 DIV4 divider value. Disabled when pfd1Div2 == 0. */
    uint8_t pfd2Div1; /*!< PLLDIV_PFD_1 DIV1 divider value. Disabled when pfd2Div1 == 0. */
    uint8_t pfd2Div2; /*!< PLLDIV_PFD_1 DIV2 divider value. Disabled when pfd2Div2 == 0. */
    uint8_t pfd3Div1; /*!< PLLDIV_PFD_2 DIV3 divider value. Disabled when pfd3Div1 == 0. */
    uint8_t pfd3Div2; /*!< PLLDIV_PFD_2 DIV4 divider value. Disabled when pfd3Div2 == 0. */

    cgc_pll_src_t src;    /*!< Clock source. */
    cgc_pll4_mult_t mult; /*!< PLL4 multiplier. */

    uint32_t num : 30;   /*!< 30-bit numerator of the PLL4 Fractional-Loop divider. */
    uint32_t denom : 30; /*!< 30-bit denominator of the PLL4 Fractional-Loop divider. */
} cgc_pll4_config_t;

/*! @brief AUD_CLK0 source in RTD */
typedef enum _cgc_rtd_audclk_src
{
    kCGC_RtdAudClkSrcExtMclk0   = 0, /*!< External audio master clock input 0 from pin. */
    kCGC_RtdAudClkSrcExtMclk1   = 1, /*!< External audio master clock input 1 from pin. */
    kCGC_RtdAudClkSrcSai0RxBclk = 2, /*!< SAI0 receiver serial bit clock. */
    kCGC_RtdAudClkSrcSai0TxBclk = 3, /*!< SAI0 transmitter serial bit clock. */
    kCGC_RtdAudClkSrcSai1RxBclk = 4, /*!< SAI1 receiver serial bit clock. */
    kCGC_RtdAudClkSrcSai1TxBclk = 5, /*!< SAI1 transmitter serial bit clock. */
    kCGC_RtdAudClkSrcSai2RxBclk = 6, /*!< SAI2 receiver serial bit clock. */
    kCGC_RtdAudClkSrcSai2TxBclk = 7, /*!< SAI2 transmitter serial bit clock. */
    kCGC_RtdAudClkSrcSai3RxBclk = 8, /*!< SAI3 receiver serial bit clock. */
    kCGC_RtdAudClkSrcSai3TxBclk = 9, /*!< SAI3 transmitter serial bit clock. */
} cgc_rtd_audclk_src_t;

/*! @brief AUD_CLK1 source in AD */
typedef enum _cgc_ad_audclk_src
{
    kCGC_AdAudClkSrcExtMclk2   = 0, /*!< External audio master clock input 2 from pin. */
    kCGC_AdAudClkSrcSai4RxBclk = 1, /*!< SAI4 receiver serial bit clock. */
    kCGC_AdAudClkSrcSai4TxBclk = 2, /*!< SAI4 transmitter serial bit clock. */
    kCGC_AdAudClkSrcSai5RxBclk = 3, /*!< SAI5 receiver serial bit clock. */
    kCGC_AdAudClkSrcSai5TxBclk = 4, /*!< SAI5 transmitter serial bit clock. */
} cgc_ad_audclk_src_t;

/*! @brief AUD_CLK2 source in LPAV */
typedef enum _cgc_lpav_audclk_src
{
    kCGC_LpavAudClkSrcExtMclk3   = 0, /*!< External audio master clock input 3 from pin. */
    kCGC_LpavAudClkSrcSai6RxBclk = 1, /*!< SAI6 receiver serial bit clock. */
    kCGC_LpavAudClkSrcSai6TxBclk = 2, /*!< SAI6 transmitter serial bit clock. */
    kCGC_LpavAudClkSrcSai7RxBclk = 3, /*!< SAI7 receiver serial bit clock. */
    kCGC_LpavAudClkSrcSai7TxBclk = 4, /*!< SAI7 transmitter serial bit clock. */
    kCGC_LpavAudClkSrcSpdifRx    = 5, /*!< SPDIF receiver clock. */
} cgc_lpav_audclk_src_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    assert(((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0U);
    assert(PCC_REG(name) & PCC_CLKCFG_PR_MASK);

    PCC_REG(name) |= PCC_CLKCFG_CGC_MASK;
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    assert(((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0U);
    assert(PCC_REG(name) & PCC_CLKCFG_PR_MASK);

    PCC_REG(name) &= ~PCC_CLKCFG_CGC_MASK;
}

/*!
 * @brief Check whether the clock is already enabled and configured by
 * any other core.
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @return True if clock is already enabled, otherwise false.
 */
static inline bool CLOCK_IsEnabledByOtherCore(clock_ip_name_t name)
{
    assert(((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0U);
    assert(PCC_REG(name) & PCC_CLKCFG_PR_MASK);

    return ((PCC_REG(name) & PCC_CLKCFG_INUSE_MASK) != 0UL) ? true : false;
}

/*!
 * @brief Set the clock source for specific IP module.
 *
 * Set the clock source for specific IP, not all modules need to set the
 * clock source, should only use this function for the modules need source
 * setting.
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param src Clock source to set.
 */
void CLOCK_SetIpSrc(clock_ip_name_t name, clock_ip_src_t src);

/*!
 * @brief Set the clock source and divider for specific IP module.
 *
 * Set the clock source and divider for specific IP, not all modules need to
 * set the clock source and divider, should only use this function for the
 * modules need source and divider setting.
 *
 * Divider output clock = Divider input clock x [(fracValue+1)/(divValue+1)]).
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param src Clock source to set.
 * @param divValue  The divider value.
 * @param fracValue The fraction multiply value.
 */
void CLOCK_SetIpSrcDiv(clock_ip_name_t name, clock_ip_src_t src, uint8_t divValue, uint8_t fracValue);

/*!
 * @brief Set the AUD_CLK0 source in RTD.
 * NOTE: The audio clock pin frequency is decided by SAI, but clock driver cannot depend on
 *       SAI driver to get its pin frequencies, user need to explicitly set the MCLK/BCLK
 *       frequencies if other modules use the AUD_CLK0 source and need to get correct frequency.
 *
 * @param src Clock source to set.
 */
static inline void CLOCK_SetRtdAudClkSrc(cgc_rtd_audclk_src_t src)
{
    CGC_RTD->AUD_CLK0 = CGC_AUD_CLK0_AUD_CLK0(src);
}

/*!
 * @brief Set the AUD_CLK1 source in AD.
 * NOTE: The audio clock pin frequency is decided by SAI, but clock driver cannot depend on
 *       SAI driver to get its pin frequencies, user need to explicitly set the MCLK/BCLK
 *       frequencies if other modules use the AUD_CLK1 source and need to get correct frequency.
 *
 * @param src Clock source to set.
 */
static inline void CLOCK_SetAdAudClkSrc(cgc_ad_audclk_src_t src)
{
    CGC_AD->AUD_CLK1 = CGC_AD_AUD_CLK1_AUD_CLK1(src);
}

/*!
 * @brief Set the AUD_CLK2 source in LPAV.
 * NOTE: The audio clock pin frequency is decided by SAI, but clock driver cannot depend on
 *       SAI driver to get its pin frequencies, user need to explicitly set the MCLK/BCLK
 *       frequencies if other modules use the AUD_CLK2 source and need to get correct frequency.
 *
 * @param src Clock source to set.
 */
static inline void CLOCK_SetLpavAudClkSrc(cgc_lpav_audclk_src_t src)
{
    CGC_LPAV->AUD_CLK2 = CGC_LPAV_AUD_CLK2_AUD_CLK2(src);
}

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * @param clockName Clock names defined in clock_name_t
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*!
 * @brief Get the CM33 core/platform clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33CorePlatClkFreq(void);

/*!
 * @brief Get the CM33 bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33BusClkFreq(void);

/*!
 * @brief Get the CM33 slow clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33SlowClkFreq(void);

/*!
 * @brief Get the Fusion DSP core/platform clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspCorePlatClkFreq(void);

/*!
 * @brief Get the Fusion DSP bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspBusClkFreq(void);

/*!
 * @brief Get the Fusion DSP slow clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspSlowClkFreq(void);

/*!
 * @brief Get the external LVDS pad clock frequency (LVDS).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetLvdsClkFreq(void);

/*!
 * @brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency. It is only used for the IP
 * modules which could select clock source by CLOCK_SetIpSrc().
 *
 * @param name Which peripheral to get, see \ref clock_ip_name_t.
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name);

/*!
 * @name MCU System Clock.
 * @{
 */

/*!
 * @brief Gets the CGC CM33 system clock frequency.
 *
 * This function gets the CGC CM33 system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetCm33SysClkFreq(cgc_sys_clk_t type);

/*!
 * @brief Sets the system clock configuration for CM33 domain.
 *
 * This function sets the system clock configuration for CM33 domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetCm33SysClkConfig(cgc_rtd_sys_clk_config_t *config)
{
    assert(config);
    /* CM33 slow clock must be slower and an integer division of CM33 system IP bus. */
    assert(config->divSlow > config->divBus);
    assert((config->divSlow + 1U) % (config->divBus + 1U) == 0U);

    CGC_RTD->CM33CLK = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Gets the CGC Fusion DSP system clock frequency.
 *
 * This function gets the CGC Fusion DSP system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetFusionDspSysClkFreq(cgc_sys_clk_t type);

/*!
 * @brief Sets the system clock configuration for FusionF1 DSP domain.
 *
 * This function sets the system clock configuration for FusionF1 DSP domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetFusionSysClkConfig(const cgc_rtd_sys_clk_config_t *config)
{
    assert(config);
    /* Fusion DSP slow clock must be slower and an integer division of DSP system IP bus. */
    assert(config->divSlow > config->divBus);
    assert((config->divSlow + 1U) % (config->divBus + 1U) == 0U);
    CGC_RTD->FUSIONCLK = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Gets the system clock configuration for CM33 domain.
 *
 * This function gets the system configuration for CM33 domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_GetCm33SysClkConfig(cgc_rtd_sys_clk_config_t *config)
{
    assert(config);

    *(uint32_t *)(uint32_t)config = CGC_RTD->CM33CLK;
}

/*!
 * @brief Gets the system clock configuration for FusionF1 DSP domain.
 *
 * This function gets the system configuration for FusionF1 DSP domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_GetFusionDspSysClkConfig(cgc_rtd_sys_clk_config_t *config)
{
    assert(config);

    *(uint32_t *)(uint32_t)config = CGC_RTD->FUSIONCLK;
}

/*!
 * @brief Sets the clock out configuration in RTD.
 *
 * This function sets the clock out configuration.
 *
 * @param setting The selection to set.
 * @param div The divider to set (div > 0).
 * @param enable Enable clock out.
 */
static inline void CLOCK_SetRtdClkOutConfig(clock_rtd_clkout_src_t setting, uint8_t div, bool enable)
{
    assert(div > 0U);

    CGC_RTD->CLKOUTCFG = CGC_CLKOUTCFG_CLKOUT_SEL(setting) | CGC_CLKOUTCFG_CLKOUT_DIV((uint32_t)div - 1U) |
                         (enable ? CGC_CLKOUTCFG_CLKOUT_EN_MASK : 0U);
}

/*!
 * @brief Sets the RTC_CLOCKOUT configuration.
 *
 * This function sets the RTC_CLOCKOUT configuration.
 *
 * @param div The divider to set (div > 0).
 */
static inline void CLOCK_SetRtcClkOutConfig(uint8_t div)
{
    assert(div > 0U);

    CGC_RTD->RTCDIV = CGC_RTCDIV_DIV1((uint32_t)div - 1U);
}

/*!
 * @brief Gets the CGC XBAR bus clock frequency in AD.
 *
 * This function gets the CGC XBAR bus clock frequency.
 *
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetXbarBusClkFreq(void);

/*!
 * @brief Gets the CGC HIFI DSP system clock frequency in LPAV.
 *
 * This function gets the CGC HIFI DSP system clock frequency. These clocks are used for
 * core, platform domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetHifiDspSysClkFreq(cgc_sys_clk_t type);

/*!
 * @brief Sets the system clock configuration for HIFI4 DSP domain.
 *
 * This function sets the system clock configuration for HIFI4 DSP domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetHifiDspSysClkConfig(const cgc_hifi_sys_clk_config_t *config)
{
    assert(config);

    CGC_LPAV->HIFICLK = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Gets the system clock configuration for HIFI4 DSP domain.
 *
 * This function gets the system configuration for HIFI4 DSP domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_GetHifiDspSysClkConfig(cgc_hifi_sys_clk_config_t *config)
{
    assert(config);

    *(uint32_t *)(uint32_t)config = CGC_LPAV->HIFICLK;
}

/*!
 * @brief Gets the CGC NIC LPAV system clock frequency in LPAV.
 *
 * This function gets the CGC NIC LPAV system clock frequency. These clocks are used for
 * AXI, AHB, Bus domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetLpavSysClkFreq(cgc_sys_clk_t type);

/*!
 * @brief Sets the system clock configuration for NIC LPAV domain.
 *
 * This function sets the system clock configuration for NIC LPAV domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetLpavSysClkConfig(const cgc_lpav_sys_clk_config_t *config)
{
    assert(config);
    /* Clock ratio must be integers between NIC_LPAV_AHB_CLK and LPAV_BUS_CLK */
    assert((config->divBus + 1U) % (config->divAhb + 1U) == 0U);

    CGC_LPAV->NICLPAVCLK = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Gets the system clock configuration for NIC LPAV domain.
 *
 * This function gets the system configuration for NIC LPAV domain.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_GetLpavSysClkConfig(cgc_lpav_sys_clk_config_t *config)
{
    assert(config);

    *(uint32_t *)(uint32_t)config = CGC_LPAV->NICLPAVCLK;
}

/*!
 * @brief Gets the CGC DDR clock frequency in LPAV.
 *
 * This function gets the CGC DDR clock frequency.
 *
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetDdrClkFreq(void);

/*!
 * @brief Sets the clock out configuration in LPAV.
 *
 * This function sets the clock out configuration.
 *
 * @param setting The selection to set.
 * @param div The divider to set (div > 0).
 * @param enable Enable clock out.
 */
static inline void CLOCK_SetLpavClkOutConfig(clock_lpav_clkout_src_t setting, uint8_t div, bool enable)
{
    assert(div > 0U);

    CGC_LPAV->CLKOUTCFG = CGC_LPAV_CLKOUTCFG_CLKOUT_SEL(setting) | CGC_LPAV_CLKOUTCFG_CLKOUT_DIV((uint32_t)div - 1U) |
                          (enable ? CGC_LPAV_CLKOUTCFG_CLKOUT_EN_MASK : 0U);
}
/* @} */

/*!
 * @name CGC System OSC Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC system OSC.
 *
 * This function enables the CGC system OSC clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success System OSC is initialized.
 * @retval kStatus_CGC_Busy System OSC has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly System OSC control register is locked.
 *
 * @note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysOsc(const cgc_sosc_config_t *config);

/*!
 * @brief De-initializes the CGC system OSC.
 *
 * This function disables the CGC system OSC clock.
 *
 * @retval kStatus_Success System OSC is deinitialized.
 * @retval kStatus_CGC_Busy System OSC is used by the system clock.
 * @retval kStatus_ReadOnly System OSC control register is locked.
 *
 * @note This function can't detect whether the system OSC is used by an IP.
 */
status_t CLOCK_DeinitSysOsc(void);

/*!
 * @brief Set the asynchronous clock divider in RTD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetRtdSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Set the asynchronous clock divider in AD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetAdSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Set the asynchronous clock divider in LPAV.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetLpavSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Gets the CGC system OSC clock frequency (SYSOSC).
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the system OSC in RTD.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdSysOscAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the system OSC in AD.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdSysOscAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the system OSC in LPAV.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavSysOscAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Checks whether the system OSC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsSysOscErr(void)
{
    return ((CGC_RTD->SOSCCSR & CGC_SOSCCSR_SOSCERR_MASK) == CGC_SOSCCSR_SOSCERR_MASK);
}

/*!
 * @brief Clears the system OSC clock error.
 */
static inline void CLOCK_ClearSysOscErr(void)
{
    CGC_RTD->SOSCCSR |= CGC_SOSCCSR_SOSCERR_MASK;
}

/*!
 * @brief Sets the system OSC monitor mode.
 *
 * This function sets the system OSC monitor mode. The mode can be disabled,
 * it can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
static inline void CLOCK_SetSysOscMonitorMode(cgc_sosc_monitor_mode_t mode)
{
    uint32_t reg = CGC_RTD->SOSCCSR;

    reg &= ~(CGC_SOSCCSR_SOSCCM_MASK | CGC_SOSCCSR_SOSCCMRE_MASK);

    reg |= (uint32_t)mode;

    CGC_RTD->SOSCCSR = reg;
}

/*!
 * @brief Checks whether the system OSC clock is used as clock source.
 *
 * @return  True if system OSC is used as clock source, false if not.
 */
static inline bool CLOCK_IsSysOscSelected(void)
{
    return ((CGC_RTD->SOSCCSR & CGC_SOSCCSR_SOSCSEL_MASK) == CGC_SOSCCSR_SOSCSEL_MASK);
}

/*!
 * @brief Checks whether the system OSC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsSysOscValid(void)
{
    return ((CGC_RTD->SOSCCSR & CGC_SOSCCSR_SOSCVLD_MASK) == CGC_SOSCCSR_SOSCVLD_MASK);
}
/* @} */

/*!
 * @name CGC FRO Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC FRO clock.
 *
 * This function initializes the CGC FRO clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success FRO is initialized.
 * @retval kStatus_CGC_Busy FRO has been enabled and is used by system clock.
 * @retval kStatus_ReadOnly FRO control register is locked.
 *
 * @note This function can't detect whether the FRO has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitFro(const cgc_fro_config_t *config);

/*!
 * @brief De-initializes the CGC FRO.
 *
 * This function deinitializes the CGC FRO.
 *
 * @retval kStatus_Success FRO is deinitialized.
 * @retval kStatus_CGC_Busy FRO is used by system clock.
 * @retval kStatus_ReadOnly FRO control register is locked.
 *
 * @note This function can't detect whether the FRO is used by an IP.
 */
status_t CLOCK_DeinitFro(void);

/*!
 * @brief Set the asynchronous clock divider in RTD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetRtdFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Set the asynchronous clock divider in AD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetAdFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Set the asynchronous clock divider in LPAV.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetLpavFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*! @brief  Enable/Disable FRO tuning.
 *   On enable, the function will wait until FRO is close to the target frequency.
 */
void CLOCK_EnableFroTuning(bool enable);

/*!
 * @brief Gets the CGC FRO clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFroFreq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the FRO in RTD.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdFroAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the FRO in AD.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdFroAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the FRO in LPAV.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavFroAsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Checks whether the FRO clock is used as clock source.
 *
 * @return  True if FRO is used as clock source, false if not.
 */
static inline bool CLOCK_IsFroSelected(void)
{
    return ((CGC_RTD->FROCSR & CGC_FROCSR_FROSEL_MASK) == CGC_FROCSR_FROSEL_MASK);
}

/*!
 * @brief Checks whether the FRO clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsFroValid(void)
{
    return ((CGC_RTD->FROCSR & CGC_FROCSR_FROVLD_MASK) == CGC_FROCSR_FROVLD_MASK);
}
/* @} */

/*!
 * @name CGC LPOSC Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC LPOSC clock.
 *
 * This function initializes the CGC LPOSC clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success LPOSC is initialized.
 * @retval kStatus_ReadOnly FRO control register is locked.
 *
 * @note This function can't detect whether the LPOSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitLposc(const cgc_lposc_config_t *config);

/*!
 * @brief De-initializes the CGC LPOSC.
 *
 * This function deinitializes the CGC LPOSC.
 *
 * @retval kStatus_Success LPOSC is deinitialized.
 * @retval kStatus_ReadOnly LPOSC control register is locked.
 *
 * @note This function can't detect whether the LPOSC is used by an IP.
 */
status_t CLOCK_DeinitLposc(void);

/*!
 * @brief Checks whether the LPOSC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsLpOscValid(void)
{
    return ((CGC_RTD->LPOSCCSR & CGC_LPOSCCSR_LPOSCVLD_MASK) == CGC_LPOSCCSR_LPOSCVLD_MASK);
}

/*!
 * @brief Gets the CGC LPOSC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpOscFreq(void);
/* @} */

/*!
 * @name CGC RTCOSC Clock.
 * @{
 */

/*!
 * @brief Gets the CGC RTC OSC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void);

/*!
 * @brief Checks whether the RTC OSC clock error occurs.
 *
 * @return  True if error occurs, false if not.
 */
static inline bool CLOCK_IsRtcOscErr(void)
{
    return ((CGC_RTD->ROSCCTRL & CGC_ROSCCTRL_ROSCERR_MASK) == CGC_ROSCCTRL_ROSCERR_MASK);
}

/*!
 * @brief Clears the RTC OSC clock error.
 */
static inline void CLOCK_ClearRtcOscErr(void)
{
    CGC_RTD->ROSCCTRL |= CGC_ROSCCTRL_ROSCERR_MASK;
}

/*!
 * @brief Sets the RTC OSC monitor mode.
 *
 * This function sets the RTC OSC monitor mode. The mode can be disabled.
 * It can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
void CLOCK_SetRtcOscMonitorMode(cgc_rosc_monitor_mode_t mode);

/*!
 * @brief Checks whether the RTCOSC clock is used as clock source.
 *
 * @return  True if RTCOSC is used as clock source, false if not.
 */
static inline bool CLOCK_IsRtcOscSelected(void)
{
    return ((CGC_RTD->ROSCCTRL & CGC_ROSCCTRL_ROSCSEL_MASK) == CGC_ROSCCTRL_ROSCSEL_MASK);
}

/*!
 * @brief Checks whether the RTC OSC clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsRtcOscValid(void)
{
    return ((CGC_RTD->ROSCCTRL & CGC_ROSCCTRL_ROSCVLD_MASK) == CGC_ROSCCTRL_ROSCVLD_MASK);
}
/* @} */

/*!
 * @name CGC PLL0 Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC PLL0.
 *
 * This function enables the CGC PLL0 clock according to the
 * configuration. The PLL0 can use the OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL0 clock output:
 * @code
 * const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 1U,
 *                                            .pfd1Div = 2U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcSysOsc,
 *                                            .mult = kCGC_Pll0Mult20};
 * CLOCK_InitPll0(&g_cgcPll0Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL0 is initialized.
 * @retval kStatus_CGC_Busy PLL0 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL0 control register is locked.
 *
 * @note This function can't detect whether the PLL0 has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitPll0(const cgc_pll0_config_t *config);

/*!
 * @brief De-initializes the CGC PLL0.
 *
 * This function disables the CGC PLL0.
 *
 * @retval kStatus_Success PLL0 is deinitialized.
 * @retval kStatus_CGC_Busy PLL0 is used by the system clock.
 * @retval kStatus_ReadOnly PLL0 control register is locked.
 *
 * @note This function can't detect whether the PLL0 is used by an IP.
 */
status_t CLOCK_DeinitPll0(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll0AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Gets the CGC PLL0 clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0Freq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the PLL0.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0AsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC PLL0 PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clock out. See "cgc_pll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0PfdFreq(cgc_pll_pfd_clkout_t pfdClkout);

/*!
 * @brief Enables the CGC PLL0 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL Frequency = Fref * MULT
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * @code
 * Example code for configuring PLL0 PFD0 clock output:
 * const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
 *                                           .div1 = 1U,
 *                                           .pfd1Div = 2U,
 *                                           .pfd2Div = 0U,
 *                                           .src = kCGC_PllSrcSysOsc,
 *                                           .mult = kCGC_Pll0Mult20};
 * CLOCK_InitPll0(&g_cgcPll0Config);
 * CLOCK_EnablePll0PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL0 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll0PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue);

/*!
 * @brief Disables the CGC PLL0 Fractional Divide (PFD) clock out.
 */
static inline void CLOCK_DisablePll0PfdClkout(cgc_pll_pfd_clkout_t pfdClkout)
{
    CGC_RTD->PLL0PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);
}

/*!
 * @brief Sets the CGC PLL0 lock time.
 *
 * @param lockTime  Reference clocks to count before PLL0 is considered locked and valid.
 */
static inline void CLOCK_SetPll0LockTime(uint16_t lockTime)
{
    CGC_RTD->PLL0LOCK = CGC_PLL0LOCK_LOCK_TIME(lockTime);
}

/*!
 * @brief Checks whether the PLL0 clock is used as clock source.
 *
 * @return  True if PLL0 is used as clock source, false if not.
 */
static inline bool CLOCK_IsPll0Selected(void)
{
    return ((CGC_RTD->PLL0CSR & CGC_PLL0CSR_PLLSEL_MASK) == CGC_PLL0CSR_PLLSEL_MASK);
}

/*!
 * @brief Checks whether the PLL0 clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsPll0Valid(void)
{
    return ((CGC_RTD->PLL0CSR & CGC_PLL0CSR_PLLVLD_MASK) == CGC_PLL0CSR_PLLVLD_MASK);
}
/* @} */

/*!
 * @name CGC PLL1 Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC PLL1.
 *
 * This function enables the CGC PLL1 clock according to the
 * configuration. The PLL1 can use the system OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL1 clock output:
 * @code
 * const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd1Div = 0U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll1Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll1(&g_cgcPll1Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL1 is initialized.
 * @retval kStatus_CGC_Busy PLL1 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL1 control register is locked.
 *
 * @note This function can't detect whether the PLL1 has been enabled and
 * is used by an IP.
 */
status_t CLOCK_InitPll1(const cgc_pll1_config_t *config);

/*!
 * @brief De-initializes the CGC PLL1.
 *
 * This function disables the CGC PLL1.
 *
 * @retval kStatus_Success PLL1 is deinitialized.
 * @retval kStatus_CGC_Busy PLL1 is used by the system clock.
 * @retval kStatus_ReadOnly PLL1 control register is locked.
 *
 * @note This function can't detect whether the PLL1 is used by an IP.
 */
status_t CLOCK_DeinitPll1(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll1AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Gets the CGC PLL1 clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1Freq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the PLL1.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1AsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC PLL1 PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clocks out. See "cgc_pll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1PfdFreq(cgc_pll_pfd_clkout_t pfdClkout);

/*!
 * @brief Enables the CGC PLL1 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL1 Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * Example code for configuring PLL1 as PLL1 PFD clock output:
 * @code
 * const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd1Div = 0U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll1Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll1(&g_cgcPll1Config);
 * CLOCK_EnablePll1PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL1 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll1PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue);

/*!
 * @brief Disables the CGC PLL1 Fractional Divide (PFD) clock out.
 */
static inline void CLOCK_DisablePll1PfdClkout(cgc_pll_pfd_clkout_t pfdClkout)
{
    CGC_RTD->PLL1PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);
}

/*!
 * @brief Enables the CGC PLL1 spread spectrum modulation feature with configurations.
 *
 * This function sets the CGC PLL1 spread spectrum modulation configurations.
 * STOP and STEP together control the modulation depth (maximum frequency change)
 * and modulation frequency.
 *
 * Modulation Depth = (STOP/MFD)*Fref where MFD is the DENOM field value in DENOM register.
 * Modulation Frequency = (STEP/(2*STOP))*Fref.
 *
 * @param step  PLL1 Spread Spectrum STEP.
 * @param stop  PLL1 Spread Spectrum STOP.
 */
static inline void CLOCK_EnablePll1SpectrumModulation(uint16_t step, uint16_t stop)
{
    CGC_RTD->PLL1SS = (CGC_RTD->PLL1SS & ~(CGC_PLL1SS_STEP_MASK | CGC_PLL1SS_STOP_MASK)) |
                      (CGC_PLL1SS_STEP(step) | CGC_PLL1SS_STOP(stop) | CGC_PLL1SS_ENABLE_MASK);
}

/*!
 * @brief Disables the CGC PLL1 spread spectrum modulation.
 *
 */
static inline void CLOCK_DisablePll1SpectrumModulation(void)
{
    CGC_RTD->PLL1SS &= ~CGC_PLL1SS_ENABLE_MASK;
}

/*!
 * @brief Sets the CGC PLL1 lock time.
 *
 * @param lockTime  Reference clocks to count before PLL1 is considered locked and valid.
 */
static inline void CLOCK_SetPll1LockTime(uint16_t lockTime)
{
    CGC_RTD->PLL1LOCK = CGC_PLL1LOCK_LOCK_TIME(lockTime);
}

/*!
 * @brief Checks whether the PLL1 clock is used as clock source.
 *
 * @return  True if PLL1 is used as clock source, false if not.
 */
static inline bool CLOCK_IsPll1Selected(void)
{
    return ((CGC_RTD->PLL1CSR & CGC_PLL1CSR_PLLSEL_MASK) == CGC_PLL1CSR_PLLSEL_MASK);
}

/*!
 * @brief Checks whether the PLL1 clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsPll1Valid(void)
{
    return ((CGC_RTD->PLL1CSR & CGC_PLL1CSR_PLLVLD_MASK) == CGC_PLL1CSR_PLLVLD_MASK);
}
/* @} */

/*!
 * @name CGC PLL3 Clock.
 * @{
 */

/*!
 * @brief Gets the CGC PLL3 clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3Freq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the PLL3.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3AsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC PLL3 PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clock out. See "cgc_pll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3PfdFreq(cgc_pll_pfd_clkout_t pfdClkout);
/* @} */

/*!
 * @name CGC PLL4 Clock.
 * @{
 */

/*!
 * @brief Initializes the CGC PLL4.
 *
 * This function enables the CGC PLL4 clock according to the
 * configuration. The PLL4 can use the OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL4 clock output:
 * @code
 * const cgc_pll4_config_t g_cgcPll4Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd0Div1 = 0U,
 *                                            .pfd0Div2 = 0U,
 *                                            .pfd1Div1 = 0U,
 *                                            .pfd1Div2 = 0U,
 *                                            .pfd2Div1 = 0U,
 *                                            .pfd2Div2 = 0U,
 *                                            .pfd3Div1 = 0U,
 *                                            .pfd3Div2 = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll4Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll4(&g_cgcPll4Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL4 is initialized.
 * @retval kStatus_CGC_Busy PLL4 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL4 control register is locked.
 *
 * @note This function can't detect whether the PLL4 has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitPll4(const cgc_pll4_config_t *config);

/*!
 * @brief De-initializes the CGC PLL4.
 *
 * This function disables the CGC PLL4.
 *
 * @retval kStatus_Success PLL4 is deinitialized.
 * @retval kStatus_CGC_Busy PLL4 is used by the system clock.
 * @retval kStatus_ReadOnly PLL4 control register is locked.
 *
 * @note This function can't detect whether the PLL4 is used by an IP.
 */
status_t CLOCK_DeinitPll4(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll4AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider);

/*!
 * @brief Gets the CGC PLL4 clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4Freq(void);

/*!
 * @brief Gets the CGC asynchronous clock frequency from the PLL4.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4AsyncFreq(cgc_async_clk_t type);

/*!
 * @brief Gets the CGC PLL4 PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clock out. See "cgc_pll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4PfdFreq(cgc_pll_pfd_clkout_t pfdClkout);

/*!
 * @brief Enables the CGC PLL4 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL Frequency = Fref * MULT
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * @code
 * Example code for configuring PLL4 PFD0 clock output:
 * const cgc_pll4_config_t g_cgcPll4Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd0Div1 = 0U,
 *                                            .pfd0Div2 = 0U,
 *                                            .pfd1Div1 = 0U,
 *                                            .pfd1Div2 = 0U,
 *                                            .pfd2Div1 = 0U,
 *                                            .pfd2Div2 = 0U,
 *                                            .pfd3Div1 = 0U,
 *                                            .pfd3Div2 = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll4Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll4(&g_cgcPll4Config);
 * CLOCK_EnablePll4PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL4 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll4PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue);

/*!
 * @brief Disables the CGC PLL4 Fractional Divide (PFD) clock out.
 */
static inline void CLOCK_DisablePll4PfdClkout(cgc_pll_pfd_clkout_t pfdClkout)
{
    CGC_LPAV->PLL4PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);
}

/*!
 * @brief Enables the CGC PLL4 spread spectrum modulation feature with configurations.
 *
 * This function sets the CGC PLL4 spread spectrum modulation configurations.
 * STOP and STEP together control the modulation depth (maximum frequency change)
 * and modulation frequency.
 *
 * Modulation Depth = (STOP/MFD)*Fref where MFD is the DENOM field value in DENOM register.
 * Modulation Frequency = (STEP/(2*STOP))*Fref.
 *
 * @param step  PLL4 Spread Spectrum STEP.
 * @param stop  PLL4 Spread Spectrum STOP.
 */
static inline void CLOCK_EnablePll4SpectrumModulation(uint16_t step, uint16_t stop)
{
    CGC_LPAV->PLL4SS = (CGC_LPAV->PLL4SS & ~(CGC_LPAV_PLL4SS_STEP_MASK | CGC_LPAV_PLL4SS_STOP_MASK)) |
                       (CGC_LPAV_PLL4SS_STEP(step) | CGC_LPAV_PLL4SS_STOP(stop) | CGC_LPAV_PLL4SS_ENABLE_MASK);
}
/*!
 * @brief Sets the CGC PLL4 lock time.
 *
 * @param lockTime  Reference clocks to count before PLL4 is considered locked and valid.
 */
static inline void CLOCK_SetPll4LockTime(uint16_t lockTime)
{
    CGC_LPAV->PLL4LOCK = CGC_LPAV_PLL4LOCK_LOCK_TIME(lockTime);
}

/*!
 * @brief Checks whether the PLL4 clock is used as clock source.
 *
 * @return  True if PLL4 is used as clock source, false if not.
 */
static inline bool CLOCK_IsPll4Selected(void)
{
    return ((CGC_LPAV->PLL4CSR & CGC_LPAV_PLL4CSR_PLLSEL_MASK) == CGC_LPAV_PLL4CSR_PLLSEL_MASK);
}

/*!
 * @brief Checks whether the PLL4 clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsPll4Valid(void)
{
    return ((CGC_LPAV->PLL4CSR & CGC_LPAV_PLL4CSR_PLLVLD_MASK) == CGC_LPAV_PLL4CSR_PLLVLD_MASK);
}
/* @} */

/*!
 * @name External clock frequency
 * @{
 */

/*!
 * @brief Sets the XTAL0 frequency based on board settings.
 *
 * @param freq The XTAL0/EXTAL0 input clock frequency in Hz.
 */
static inline void CLOCK_SetXtal0Freq(uint32_t freq)
{
    g_xtal0Freq = freq;
}

/*!
 * @brief Sets the XTAL32 frequency based on board settings.
 *
 * @param freq The XTAL32/EXTAL32 input clock frequency in Hz.
 */
static inline void CLOCK_SetXtal32Freq(uint32_t freq)
{
    g_xtal32Freq = freq;
}

/*!
 * @brief Sets the LVDS pad frequency based on board settings.
 *
 * @param freq The LVDS pad input clock frequency in Hz.
 */
static inline void CLOCK_SetLvdsFreq(uint32_t freq)
{
    g_lvdsFreq = freq;
}

/*!
 * @brief Sets the MCLK pad frequency based on Audio settings.
 *
 * @param index The MCLK index.
 * @param freq The MCLK pad input clock frequency in Hz.
 */
static inline void CLOCK_SetMclkFreq(uint32_t index, uint32_t freq)
{
    assert(index < ARRAY_SIZE(g_mclkFreq));

    g_mclkFreq[index] = freq;
}

/*!
 * @brief Sets the RX_BCLK pad frequency based on Audio settings.
 *
 * @param instance The SAI instance to contribute to this RX_BCLK pad.
 * @param freq The RX_BCLK pad input clock frequency in Hz.
 */
static inline void CLOCK_SetRxBclkFreq(uint32_t instance, uint32_t freq)
{
    assert(instance < ARRAY_SIZE(g_rxBclkFreq));

    g_rxBclkFreq[instance] = freq;
}

/*!
 * @brief Sets the TX_BCLK pad frequency based on Audio settings.
 *
 * @param instance The SAI instance to contribute to this TX_BCLK pad.
 * @param freq The TX_BCLK pad input clock frequency in Hz.
 */
static inline void CLOCK_SetTxBclkFreq(uint32_t instance, uint32_t freq)
{
    assert(instance < ARRAY_SIZE(g_txBclkFreq));

    g_txBclkFreq[instance] = freq;
}

/*!
 * @brief Sets the SPDIF_RX frequency based on Audio settings.
 *
 * @param freq The SPDIF_RX input clock frequency in Hz.
 */
static inline void CLOCK_SetSpdifRxFreq(uint32_t freq)
{
    g_spdifRxFreq = freq;
}

/* @} */

/*!
 * @name Get peripheral frequency
 * @{
 */

/*!
 * @brief Gets the WDOG clock frequency in RTD and LPAV.
 *
 * @param instance The WDOG instance (0-2,5).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetWdogClkFreq(uint32_t instance);

/*!
 * @brief Gets the FlexSPI clock frequency in RTD.
 *
 * @param instance The FlexSPI instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexspiClkFreq(uint32_t instance);

/*!
 * @brief Gets the LPIT clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpitClkFreq(void);

/*!
 * @brief Gets the FlexIO clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexioClkFreq(void);

/*!
 * @brief Gets the I3C clock frequency in RTD and LPAV.
 *
 * @param instance The I3C instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetI3cClkFreq(uint32_t instance);

/*!
 * @brief Gets the LPSPI clock frequency in RTD.
 *
 * @param instance The LPSPI instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpspiClkFreq(uint32_t instance);

/*!
 * @brief Gets the ADC clock frequency.
 *
 * @param instance The ADC instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdcClkFreq(uint32_t instance);

/*!
 * @brief Gets the DAC clock frequency.
 *
 * @param instance The DAC instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDacClkFreq(uint32_t instance);

/*!
 * @brief Gets the TPIU clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetTpiuClkFreq(void);

/*!
 * @brief Gets the SWO clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSwoClkFreq(void);

/*!
 * @brief Gets the TPM clock frequency.
 *
 * @param instance The TPM instance (0-8).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetTpmClkFreq(uint32_t instance);

/*!
 * @brief Gets the LPI2C clock frequency in RTD.
 *
 * @param instance The LPI2C instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpi2cClkFreq(uint32_t instance);

/*!
 * @brief Gets the LPUART clock frequency in RTD.
 *
 * @param instance The LPUART instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpuartClkFreq(uint32_t instance);

/*!
 * @brief Gets the FlexCAN clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexcanClkFreq(void);

/*!
 * @brief Gets the CSI clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiClkFreq(void);

/*!
 * @brief Gets the DSI clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDsiClkFreq(void);

/*!
 * @brief Gets the EPDC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetEpdcClkFreq(void);

/*!
 * @brief Gets the GPU2D clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetGpu2dClkFreq(void);

/*!
 * @brief Gets the GPU3D clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetGpu3dClkFreq(void);

/*!
 * @brief Gets the DC Nano clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDcnanoClkFreq(void);

/*!
 * @brief Gets the CSI clk_ui clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiUiClkFreq(void);

/*!
 * @brief Gets the CSI clk_esc clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiEscClkFreq(void);

/*!
 * @brief Gets the audio clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdAudClkFreq(void);

/*!
 * @brief Gets the audio clock frequency in AD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdAudClkFreq(void);

/*!
 * @brief Gets the audio clock frequency in LPAV.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavAudClkFreq(void);

/*!
 * @brief Gets the SAI clock frequency.
 *
 * @param instance The SAI instance (0-7).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSaiFreq(uint32_t instance);

/*!
 * @brief Gets the SPDIF clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSpdifFreq(void);

/*!
 * @brief Gets the MQS clock frequency.
 *
 * @param instance The MQS instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMqsFreq(uint32_t instance);

/*!
 * @brief Gets the EMICFIL clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMicfilFreq(void);

/*!
 * @brief Gets the MRT clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMrtFreq(void);
/* @} */

/*!
 * @brief Gets the CGC system clock frequency in RTD.
 *
 * This function gets the CGC system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param config   Config value from CGC register.
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetRtdSysClkFreq(uint32_t config, cgc_sys_clk_t type);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
