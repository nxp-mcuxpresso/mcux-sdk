/*
 * Copyright 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, NXP
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
/*! @brief CLOCK driver version 2.3.1. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (192000000UL)
#endif

/*!
 * @brief Re-map the SCG peripheral base address for i.MX 7ULP.
 * This driver is for SCG 0 on Core 0 of i.MX 7ULP only.
 */
#define SCG SCG0

/*!
 * @brief SCG (A/S)PLLPFD[PFDx] value.
 */
#define SCG_PLLPFD_PFD_VAL(pfdClkout, fracValue) ((uint32_t)((uint32_t)(fracValue) << (uint32_t)(pfdClkout)))
/*!
 * @brief SCG (A/S)PLLPFD[PFD] mask.
 */
#define SCG_PLLPFD_PFD_MASK(pfdClkout) ((uint32_t)((uint32_t)(SCG_APLLPFD_PFD0_MASK) << (uint32_t)(pfdClkout)))
/*!
 * @brief SCG (A/S)PLLPFD[PFDx_VALID] mask.
 */
#define SCG_PLLPFD_PFD_VALID_MASK(pfdClkout) \
    ((uint32_t)((uint32_t)SCG_APLLPFD_PFD0_VALID_MASK << (uint32_t)(pfdClkout)))
/*!
 * @brief SCG (A/S)PLLPFD[PFDx_CLKGATE] mask.
 */
#define SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout) \
    ((uint32_t)((uint32_t)SCG_APLLPFD_PFD0_CLKGATE_MASK << (uint32_t)(pfdClkout)))

/*! @brief External XTAL0 (OSC0/SYSOSC) clock frequency.
 *
 * The XTAL0/EXTAL0 (OSC0/SYSOSC) clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtal0Freq to set the value in the clock driver. For example,
 * if XTAL0 is 8 MHz:
 * @code
 * CLOCK_InitSysOsc(...);
 * CLOCK_SetXtal0Freq(80000000);
 * @endcode
 *
 * This is important for the multicore platforms where only one core needs to set up the
 * OSC0/SYSOSC using CLOCK_InitSysOsc. All other cores need to call the CLOCK_SetXtal0Freq
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

/*!
 * @brief Re-define PCC register masks and bitfield operations to unify
 * the different namings in the soc header file.
 */
#define PCC_CLKCFG_PCD_MASK (0x7U)
#define PCC_CLKCFG_PCD_SHIFT (0U)
#define PCC_CLKCFG_PCD(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCD_SHIFT)) & PCC_CLKCFG_PCD_MASK)
#define PCC_CLKCFG_FRAC_MASK (0x8U)
#define PCC_CLKCFG_FRAC_SHIFT (3U)
#define PCC_CLKCFG_FRAC(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_FRAC_SHIFT)) & PCC_CLKCFG_FRAC_MASK)
#define PCC_CLKCFG_PCS_MASK (0x7000000U)
#define PCC_CLKCFG_PCS_SHIFT (24U)
#define PCC_CLKCFG_PCS(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCS_SHIFT)) & PCC_CLKCFG_PCS_MASK)
#define PCC_CLKCFG_INUSE_MASK (0x20000000U)
#define PCC_CLKCFG_CGC_MASK (0x40000000U)
#define PCC_CLKCFG_PR_MASK (0x80000000U)

/*! @brief Clock ip name array for DMAMUX. */
#define DMAMUX_CLOCKS                  \
    {                                  \
        kCLOCK_Dmamux0, kCLOCK_Dmamux1 \
    }

/*! @brief Clock ip name array for RGPIO2P. */
#define RGPIO2P_CLOCKS                                                                                       \
    {                                                                                                        \
        kCLOCK_Rgpio2p0, kCLOCK_Rgpio2p0, kCLOCK_Rgpio2p1, kCLOCK_Rgpio2p1, kCLOCK_Rgpio2p1, kCLOCK_Rgpio2p1 \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS               \
    {                            \
        kCLOCK_Sai0, kCLOCK_Sai1 \
    }

/*! @brief Clock ip name array for PCTL. */
#define PCTL_CLOCKS                                                                        \
    {                                                                                      \
        kCLOCK_PctlA, kCLOCK_PctlB, kCLOCK_PctlC, kCLOCK_PctlD, kCLOCK_PctlE, kCLOCK_PctlF \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                             \
    {                                                                                                            \
        kCLOCK_Lpi2c0, kCLOCK_Lpi2c1, kCLOCK_Lpi2c2, kCLOCK_Lpi2c3, kCLOCK_Lpi2c4, kCLOCK_Lpi2c5, kCLOCK_Lpi2c6, \
            kCLOCK_Lpi2c7                                                                                        \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                  \
    {                                  \
        kCLOCK_Flexio0, kCLOCK_Flexio1 \
    }

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS              \
    {                            \
        kCLOCK_Dma0, kCLOCK_Dma1 \
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

/*! @brief Clock ip name array for DAC. */
#define SNVS_HP_CLOCKS \
    {                  \
        kCLOCK_Snvs    \
    }

#define SNVS_LP_CLOCKS \
    {                  \
        kCLOCK_Snvs    \
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

/*! @brief Clock ip name array for TRNG. */
#define TRNG_CLOCKS  \
    {                \
        kCLOCK_Trng0 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                               \
    {                                                              \
        kCLOCK_Lpspi0, kCLOCK_Lpspi1, kCLOCK_Lpspi2, kCLOCK_Lpspi3 \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                                                                             \
    {                                                                                                          \
        kCLOCK_Tpm0, kCLOCK_Tpm1, kCLOCK_Tpm2, kCLOCK_Tpm3, kCLOCK_Tpm4, kCLOCK_Tpm5, kCLOCK_Tpm6, kCLOCK_Tpm7 \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS                \
    {                              \
        kCLOCK_Lpit0, kCLOCK_Lpit1 \
    }

/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc0 \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS               \
    {                            \
        kCLOCK_Cmp0, kCLOCK_Cmp1 \
    }

/*! @brief Clock ip name array for XRDC. */
#define XRDC_CLOCKS  \
    {                \
        kCLOCK_Xrdc0 \
    }

/*! @brief Clock ip name array for MU. */
#define MU_CLOCKS  \
    {              \
        kCLOCK_MuA \
    }

/*! @brief Clock ip name array for WDOG. */
#define WDOG_CLOCKS                              \
    {                                            \
        kCLOCK_Wdog0, kCLOCK_Wdog1, kCLOCK_Wdog2 \
    }

/*! @brief Clock ip name array for LTC. */
#define LTC_CLOCKS  \
    {               \
        kCLOCK_Ltc0 \
    }

/*! @brief Clock ip name array for DPM. */
#define DPM_CLOCKS \
    {              \
        kCLOCK_Dpm \
    }

/*! @brief Clock ip name array for SEMA42. */
#define SEMA42_CLOCKS                  \
    {                                  \
        kCLOCK_Sema420, kCLOCK_Sema421 \
    }

/*! @brief Clock ip name array for TPIU. */
#define TPIU_CLOCKS \
    {               \
        kCLOCK_Tpiu \
    }

/*! @brief Clock ip name array for QSPI. */
#define QSPI_CLOCKS \
    {               \
        kCLOCK_Qspi \
    }

/*!
 * @brief LPO clock frequency.
 */
#define LPO_CLK_FREQ 1000U

/*!
 * @brief TPIU clock frequency.
 */
#define TPIU_CLK_FREQ 100000000U

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{

    /* ---------------------------- System layer clock -----------------------*/
    kCLOCK_CoreSysClk, /*!< Core/system clock                                 */
    kCLOCK_PlatClk,    /*!< Platform clock                                    */
    kCLOCK_ExtClk,     /*!< External clock                                    */
    kCLOCK_BusClk,     /*!< Bus clock                                         */
    kCLOCK_SlowClk,    /*!< Slow clock                                         */

    /* ------------------------------------ SCG clock ------------------------*/
    kCLOCK_ScgSysOscClk, /*!< SCG system OSC clock. (SYSOSC)                  */
    kCLOCK_ScgSircClk,   /*!< SCG SIRC clock.                                 */
    kCLOCK_ScgFircClk,   /*!< SCG FIRC clock.                                 */
    kCLOCK_ScgRtcOscClk, /*!< SCG RTC OSC clock. (ROSC)                  */
    kCLOCK_ScgAuxPllClk, /*!< SCG auxiliary PLL clock. (AUXPLL)                  */
    kCLOCK_ScgSysPllClk, /*!< SCG system PLL clock. (SYSPLL)                  */

    kCLOCK_ScgSysOscAsyncDiv1Clk, /*!< SOSCDIV1_CLK.                          */
    kCLOCK_ScgSysOscAsyncDiv2Clk, /*!< SOSCDIV2_CLK.                          */
    kCLOCK_ScgSysOscAsyncDiv3Clk, /*!< SOSCDIV3_CLK.                          */

    kCLOCK_ScgSircAsyncDiv1Clk, /*!< SIRCDIV1_CLK.                            */
    kCLOCK_ScgSircAsyncDiv2Clk, /*!< SIRCDIV2_CLK.                            */
    kCLOCK_ScgSircAsyncDiv3Clk, /*!< SIRCDIV3_CLK.                            */

    kCLOCK_ScgFircAsyncDiv1Clk, /*!< FIRCDIV1_CLK.                            */
    kCLOCK_ScgFircAsyncDiv2Clk, /*!< FIRCDIV2_CLK.                            */
    kCLOCK_ScgFircAsyncDiv3Clk, /*!< FIRCDIV3_CLK.                            */

    kCLOCK_ScgSysPllPfd0Clk, /*!< spll pfd0.                            */
    kCLOCK_ScgSysPllPfd1Clk, /*!< spll pfd1.                            */
    kCLOCK_ScgSysPllPfd2Clk, /*!< spll pfd2.                            */
    kCLOCK_ScgSysPllPfd3Clk, /*!< spll pfd3.                            */

    kCLOCK_ScgAuxPllPfd0Clk, /*!< apll pfd0.                            */
    kCLOCK_ScgAuxPllPfd1Clk, /*!< apll pfd1.                            */
    kCLOCK_ScgAuxPllPfd2Clk, /*!< apll pfd2.                            */
    kCLOCK_ScgAuxPllPfd3Clk, /*!< apll pfd3.                            */

    kCLOCK_ScgSysPllAsyncDiv1Clk, /*!< SPLLDIV1_CLK.                          */
    kCLOCK_ScgSysPllAsyncDiv2Clk, /*!< SPLLDIV2_CLK.                          */
    kCLOCK_ScgSysPllAsyncDiv3Clk, /*!< SPLLDIV3_CLK.                          */

    kCLOCK_ScgAuxPllAsyncDiv1Clk, /*!< APLLDIV1_CLK.                          */
    kCLOCK_ScgAuxPllAsyncDiv2Clk, /*!< APLLDIV2_CLK.                          */
    kCLOCK_ScgAuxPllAsyncDiv3Clk, /*!< APLLDIV3_CLK.                          */

    /* -------------------------------- Other clock --------------------------*/
    kCLOCK_LpoClk,    /*!< LPO clock                                          */
    kCLOCK_Osc32kClk, /*!< External OSC 32K clock (OSC32KCLK)                 */
    kCLOCK_ErClk,     /*!< ERCLK. The external reference clock from SCG.      */
    kCLOCK_LvdsClk,   /*!< LVDS pad input clock frequency.                    */
} clock_name_t;

#define kCLOCK_Osc0ErClk kCLOCK_ErClk                /*!< For compatible with other MCG platforms. */
#define kCLOCK_Er32kClk kCLOCK_Osc32kClk             /*!< For compatible with other MCG platforms. */
#define CLOCK_GetOsc0ErClkFreq CLOCK_GetErClkFreq    /*!< For compatible with other MCG platforms. */
#define CLOCK_GetEr32kClkFreq CLOCK_GetOsc32kClkFreq /*!< For compatible with other MCG platforms. */

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum _clock_ip_src
{
    kCLOCK_IpSrcNone           = 0U, /*!< Clock is off.                                              */
    kCLOCK_IpSrcSysOscAsync    = 1U, /*!< SYSOSC platform or bus clock, depending on clock IP.       */
    kCLOCK_IpSrcSircAsync      = 2U, /*!< SIRC platform or bus clock, depending on clock IP.         */
    kCLOCK_IpSrcFircAsync      = 3U, /*!< FIRC platform or bus clock, depending on clock IP.         */
    kCLOCK_IpSrcRtcAuxPllAsync = 4U, /*!< RTC OSC clock or AUXPLL main clock, depending on clock IP. */
    kCLOCK_IpSrcSystem         = 5U, /*!< System platform or bus clock, depending on clock IP.       */
    kCLOCK_IpSrcSysPllAsync    = 6U, /*!< SYSPLL platform or bus clock, depending on clock IP.       */
    kCLOCK_IpSrcPllPfdAsync    = 7U, /*!< SYSPLL PFD3 or AUXPLL PFD0 clock, depending on clock IP.   */
} clock_ip_src_t;

/*!
 * @brief Clock source for LPTMR.
 */
typedef enum _clock_lptmr_src
{
    kCLOCK_LptmrSrcSircAsync = 0U, /*!< SIRC clock.                                            */
    kCLOCK_LptmrSrcLPO1K     = 1U, /*!< LPO 1KHz clock.                                        */
    kCLOCK_LptmrSrcXTAL32K   = 2U, /*!< RTC XTAL clock.                                        */
    kCLOCK_LptmrSrcExternal  = 3U, /*!< External clock.                                        */
} clock_lptmr_src_t;

/*!
 * @brief Peripheral clock name difinition used for clock gate, clock source
 * and clock divider setting. It is defined as the corresponding register address.
 */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,
    /* PCC 0 */
    kCLOCK_Dma0     = 0x41026020U,
    kCLOCK_Rgpio2p0 = 0x4102603CU,
    kCLOCK_Xrdc0    = 0x41026050U,
    kCLOCK_Sema420  = 0x4102606CU,
    kCLOCK_Dmamux0  = 0x41026080U,
    kCLOCK_MuA      = 0x41026088U,
    kCLOCK_Wdog0    = 0x41026094U,
    kCLOCK_Crc0     = 0x410260A4U,
    kCLOCK_Ltc0     = 0x410260A8U,
    kCLOCK_Trng0    = 0x410260B0U,
    kCLOCK_Lpit0    = 0x410260B4U,
    kCLOCK_Lptmr0   = 0x410260B8U,
    kCLOCK_Lptmr1   = 0x410260BCU,
    kCLOCK_Tpm0     = 0x410260C0U,
    kCLOCK_Tpm1     = 0x410260C4U,
    kCLOCK_Flexio0  = 0x410260C8U,
    kCLOCK_Lpi2c0   = 0x410260CCU,
    kCLOCK_Lpi2c1   = 0x410260D0U,
    kCLOCK_Lpi2c2   = 0x410260D4U,
    kCLOCK_Lpi2c3   = 0x410260D8U,
    kCLOCK_Sai0     = 0x410260DCU,
    kCLOCK_Lpspi0   = 0x410260E0U,
    kCLOCK_Lpspi1   = 0x410260E4U,
    kCLOCK_Lpuart0  = 0x410260E8U,
    kCLOCK_Lpuart1  = 0x410260ECU,
    kCLOCK_PctlA    = 0x410260FCU,
    kCLOCK_PctlB    = 0x41026100U,
    kCLOCK_Adc0     = 0x41026104U,
    kCLOCK_Cmp0     = 0x41026108U,
    kCLOCK_Cmp1     = 0x4102610CU,
    kCLOCK_Dac0     = 0x41026110U,
    kCLOCK_Dac1     = 0x41026114U,
    kCLOCK_Snvs     = 0x410261C0U,

    /* PCC 1 */
    kCLOCK_Tpiu    = 0x410B2050U,
    kCLOCK_Qspi    = 0x410B2094U,
    kCLOCK_Tpm2    = 0x410B20A0U,
    kCLOCK_Tpm3    = 0x410B20A4U,
    kCLOCK_Sai1    = 0x410B20A8U,
    kCLOCK_Lpuart2 = 0x410B20ACU,
    kCLOCK_Lpuart3 = 0x410B20B0U,
    kCLOCK_Adc1    = 0x410B20B4U,

    /* PCC 2 */
    kCLOCK_Dma1     = 0x403F0020U,
    kCLOCK_Rgpio2p1 = 0x403F003CU,
    kCLOCK_Flexbus  = 0x403F0040U,
    kCLOCK_Sema421  = 0x403F006CU,
    kCLOCK_Dmamux1  = 0x403F0084U,
    kCLOCK_Caam     = 0x403F0090U,
    kCLOCK_Tpm4     = 0x403F0094U,
    kCLOCK_Tpm5     = 0x403F0098U,
    kCLOCK_Lpit1    = 0x403F009CU,
    kCLOCK_Lpspi2   = 0x403F00A4U,
    kCLOCK_Lpspi3   = 0x403F00A8U,
    kCLOCK_Lpi2c4   = 0x403F00ACU,
    kCLOCK_Lpi2c5   = 0x403F00B0U,
    kCLOCK_Lpuart4  = 0x403F00B4U,
    kCLOCK_Lpuart5  = 0x403F00B8U,
    kCLOCK_Flexio1  = 0x403F00C4U,
    kCLOCK_Usb0     = 0x403F00CCU,
    kCLOCK_Usb1     = 0x403F00D0U,
    kCLOCK_UsbPhy   = 0x403F00D4U,
    kCLOCK_UsbPl301 = 0x403F00D8U,
    kCLOCK_Usdhc0   = 0x403F00DCU,
    kCLOCK_Usdhc1   = 0x403F00E0U,
    kCLOCK_Wdog1    = 0x403F00F4U,
    kCLOCK_Wdog2    = 0x403F010CU,

    /* PCC 3 */
    kCLOCK_Tpm6    = 0x40B30084U,
    kCLOCK_Tpm7    = 0x40B30088U,
    kCLOCK_Lpi2c6  = 0x40B30090U,
    kCLOCK_Lpi2c7  = 0x40B30094U,
    kCLOCK_Lpuart6 = 0x40B30098U,
    kCLOCK_Lpuart7 = 0x40B3009CU,
    kCLOCK_Viu     = 0x40B300A0U,
    kCLOCK_Dsi     = 0x40B300A4U,
    kCLOCK_Lcdif   = 0x40B300A8U,
    kCLOCK_Mmdc    = 0x40B300ACU,
    kCLOCK_PctlC   = 0x40B300B8U,
    kCLOCK_PctlD   = 0x40B300BCU,
    kCLOCK_PctlE   = 0x40B300C0U,
    kCLOCK_PctlF   = 0x40B300C4U,
    kCLOCK_Gpu3D   = 0x40B30140U,
    kCLOCK_Gpu2D   = 0x40B30144U,
} clock_ip_name_t;

/*!
 * @brief SCG status return codes.
 */
enum
{
    kStatus_SCG_Busy       = MAKE_STATUS(kStatusGroup_SCG, 1), /*!< Clock is busy.  */
    kStatus_SCG_InvalidSrc = MAKE_STATUS(kStatusGroup_SCG, 2)  /*!< Invalid source. */
};

/*!
 * @brief SCG system clock type.
 */
typedef enum _scg_sys_clk
{
    kSCG_SysClkSlow, /*!< System slow clock. */
    kSCG_SysClkBus,  /*!< Bus clock.         */
    kSCG_SysClkExt,  /*!< External clock.    */
    kSCG_SysClkPlat, /*!< Platform clock.    */
    kSCG_SysClkCore, /*!< Core clock.        */
} scg_sys_clk_t;

/*!
 * @brief SCG system clock source.
 */
typedef enum _scg_sys_clk_src
{
    kSCG_SysClkSrcSysOsc = 1U, /*!< System OSC. */
    kSCG_SysClkSrcSirc   = 2U, /*!< Slow IRC.   */
    kSCG_SysClkSrcFirc   = 3U, /*!< Fast IRC.   */
    kSCG_SysClkSrcRosc   = 4U, /*!< RTC OSC. */
    kSCG_SysClkSrcAuxPll = 5U, /*!< Auxiliary PLL. */
    kSCG_SysClkSrcSysPll = 6U  /*!< System PLL. */
} scg_sys_clk_src_t;

/*!
 * @brief SCG system clock divider value.
 */
typedef enum _scg_sys_clk_div
{
    kSCG_SysClkDivBy1  = 0U,  /*!< Divided by 1.  */
    kSCG_SysClkDivBy2  = 1U,  /*!< Divided by 2.  */
    kSCG_SysClkDivBy3  = 2U,  /*!< Divided by 3.  */
    kSCG_SysClkDivBy4  = 3U,  /*!< Divided by 4.  */
    kSCG_SysClkDivBy5  = 4U,  /*!< Divided by 5.  */
    kSCG_SysClkDivBy6  = 5U,  /*!< Divided by 6.  */
    kSCG_SysClkDivBy7  = 6U,  /*!< Divided by 7.  */
    kSCG_SysClkDivBy8  = 7U,  /*!< Divided by 8.  */
    kSCG_SysClkDivBy9  = 8U,  /*!< Divided by 9.  */
    kSCG_SysClkDivBy10 = 9U,  /*!< Divided by 10. */
    kSCG_SysClkDivBy11 = 10U, /*!< Divided by 11. */
    kSCG_SysClkDivBy12 = 11U, /*!< Divided by 12. */
    kSCG_SysClkDivBy13 = 12U, /*!< Divided by 13. */
    kSCG_SysClkDivBy14 = 13U, /*!< Divided by 14. */
    kSCG_SysClkDivBy15 = 14U, /*!< Divided by 15. */
    kSCG_SysClkDivBy16 = 15U  /*!< Divided by 16. */
} scg_sys_clk_div_t;

/*!
 * @brief SCG system clock configuration.
 */
typedef struct _scg_sys_clk_config
{
    uint32_t divSlow : 4; /*!< Slow clock divider, see @ref scg_sys_clk_div_t. */
    uint32_t divBus : 4;  /*!< Bus clock divider, see @ref scg_sys_clk_div_t.  */
    uint32_t : 4;         /*!< Reserved.  */
    uint32_t divPlat : 4; /*!< Platform clock divider, which can only be divided by 1. See @ref kSCG_SysClkDivBy1.*/
    uint32_t divCore : 4; /*!< Core clock divider, see @ref scg_sys_clk_div_t. */
    uint32_t : 4;         /*!< Reserved. */
    uint32_t src : 4;     /*!< System clock source, see @ref scg_sys_clk_src_t. */
    uint32_t : 4;         /*!< reserved. */
} scg_sys_clk_config_t;

/*!
 * @brief SCG clock out configuration (CLKOUTSEL).
 */
typedef enum _clock_clkout_src
{
    kClockClkoutSelScgExt    = 0U, /*!< SCG external clock. */
    kClockClkoutSelSysOsc    = 1U, /*!< System OSC.     */
    kClockClkoutSelSirc      = 2U, /*!< Slow IRC.       */
    kClockClkoutSelFirc      = 3U, /*!< Fast IRC.       */
    kClockClkoutSelScgRtcOsc = 4U, /*!< SCG RTC OSC clock. */
    kClockClkoutSelScgAuxPll = 5U, /*!< SCG Auxiliary PLL clock. */
    kClockClkoutSelSysPll    = 6U  /*!< System PLL.     */
} clock_clkout_src_t;

/*!
 * @brief SCG asynchronous clock type.
 */
typedef enum _scg_async_clk
{
    kSCG_AsyncDiv1Clk, /*!< The async clock by DIV1, e.g. SOSCDIV1_CLK, SIRCDIV1_CLK. */
    kSCG_AsyncDiv2Clk, /*!< The async clock by DIV2, e.g. SOSCDIV2_CLK, SIRCDIV2_CLK. */
    kSCG_AsyncDiv3Clk  /*!< The async clock by DIV3, e.g. SOSCDIV3_CLK, SIRCDIV3_CLK. */
} scg_async_clk_t;

/*!
 * @brief SCG asynchronous clock divider value.
 */
typedef enum scg_async_clk_div
{
    kSCG_AsyncClkDisable = 0U, /*!< Clock output is disabled.  */
    kSCG_AsyncClkDivBy1  = 1U, /*!< Divided by 1.              */
    kSCG_AsyncClkDivBy2  = 2U, /*!< Divided by 2.              */
    kSCG_AsyncClkDivBy4  = 3U, /*!< Divided by 4.              */
    kSCG_AsyncClkDivBy8  = 4U, /*!< Divided by 8.              */
    kSCG_AsyncClkDivBy16 = 5U, /*!< Divided by 16.             */
    kSCG_AsyncClkDivBy32 = 6U, /*!< Divided by 32.             */
    kSCG_AsyncClkDivBy64 = 7U  /*!< Divided by 64.             */
} scg_async_clk_div_t;

/*!
 * @brief SCG system OSC monitor mode.
 */
typedef enum _scg_sosc_monitor_mode
{
    kSCG_SysOscMonitorDisable = 0U,                      /*!< Monitor disabled.                          */
    kSCG_SysOscMonitorInt     = SCG_SOSCCSR_SOSCCM_MASK, /*!< Interrupt when the system OSC error is detected. */
    kSCG_SysOscMonitorReset =
        SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK /*!< Reset when the system OSC error is detected.     */
} scg_sosc_monitor_mode_t;

/*! @brief OSC work mode. */
typedef enum _scg_sosc_mode
{
    kSCG_SysOscModeExt         = 0U,                                           /*!< Use external clock.   */
    kSCG_SysOscModeOscLowPower = SCG_SOSCCFG_EREFS_MASK,                       /*!< Oscillator low power. */
    kSCG_SysOscModeOscHighGain = SCG_SOSCCFG_EREFS_MASK | SCG_SOSCCFG_HGO_MASK /*!< Oscillator high gain. */
} scg_sosc_mode_t;

/*! @brief OSC enable mode. */
enum _scg_sosc_enable_mode
{
    kSCG_SysOscEnable           = SCG_SOSCCSR_SOSCEN_MASK,   /*!< Enable OSC clock. */
    kSCG_SysOscEnableInStop     = SCG_SOSCCSR_SOSCSTEN_MASK, /*!< Enable OSC in stop mode. */
    kSCG_SysOscEnableInLowPower = SCG_SOSCCSR_SOSCLPEN_MASK, /*!< Enable OSC in low power mode. */
};

/*!
 * @brief SCG system OSC configuration.
 */
typedef struct _scg_sosc_config
{
    uint32_t freq;                       /*!< System OSC frequency.                    */
    scg_sosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.     */
    uint8_t enableMode;                  /*!< Enable mode, OR'ed value of _scg_sosc_enable_mode.  */

    scg_async_clk_div_t div1; /*!< SOSCDIV1 value.                          */
    scg_async_clk_div_t div2; /*!< SOSCDIV2 value.                          */
    scg_async_clk_div_t div3; /*!< SOSCDIV3 value.                          */

    scg_sosc_mode_t workMode; /*!< OSC work mode.                           */
} scg_sosc_config_t;

/*!
 * @brief SCG slow IRC clock frequency range.
 */
typedef enum _scg_sirc_range
{
    kSCG_SircRangeLow, /*!< Slow IRC low range clock (2 MHz, 4 MHz for i.MX 7ULP).  */
    kSCG_SircRangeHigh /*!< Slow IRC high range clock (8 MHz, 16 MHz for i.MX 7ULP). */
} scg_sirc_range_t;

/*! @brief SIRC enable mode. */
enum _scg_sirc_enable_mode
{
    kSCG_SircEnable           = SCG_SIRCCSR_SIRCEN_MASK,   /*!< Enable SIRC clock.             */
    kSCG_SircEnableInStop     = SCG_SIRCCSR_SIRCSTEN_MASK, /*!< Enable SIRC in stop mode.      */
    kSCG_SircEnableInLowPower = SCG_SIRCCSR_SIRCLPEN_MASK  /*!< Enable SIRC in low power mode. */
};

/*!
 * @brief SCG slow IRC clock configuration.
 */
typedef struct _scg_sirc_config
{
    uint32_t enableMode;      /*!< Enable mode, OR'ed value of _scg_sirc_enable_mode. */
    scg_async_clk_div_t div1; /*!< SIRCDIV1 value.                          */
    scg_async_clk_div_t div2; /*!< SIRCDIV2 value.                          */
    scg_async_clk_div_t div3; /*!< SIRCDIV3 value.                          */

    scg_sirc_range_t range; /*!< Slow IRC frequency range.                */
} scg_sirc_config_t;

/*!
 * @brief SCG fast IRC trim mode.
 */
typedef enum _scg_firc_trim_mode
{
    kSCG_FircTrimNonUpdate = SCG_FIRCCSR_FIRCTREN_MASK,
    /*!< FIRC trim enable but not enable trim value update. In this mode, the
     trim value is fixed to the initialized value which is defined by
     trimCoar and trimFine in configure structure \ref scg_firc_trim_config_t.*/

    kSCG_FircTrimUpdate = SCG_FIRCCSR_FIRCTREN_MASK | SCG_FIRCCSR_FIRCTRUP_MASK
    /*!< FIRC trim enable and trim value update enable. In this mode, the trim
     value is auto update. */

} scg_firc_trim_mode_t;

/*!
 * @brief SCG fast IRC trim predivided value for system OSC.
 */
typedef enum _scg_firc_trim_div
{
    kSCG_FircTrimDivBy1,    /*!< Divided by 1.    */
    kSCG_FircTrimDivBy128,  /*!< Divided by 128.  */
    kSCG_FircTrimDivBy256,  /*!< Divided by 256.  */
    kSCG_FircTrimDivBy512,  /*!< Divided by 512.  */
    kSCG_FircTrimDivBy1024, /*!< Divided by 1024. */
    kSCG_FircTrimDivBy2048  /*!< Divided by 2048. */
} scg_firc_trim_div_t;

/*!
 * @brief SCG fast IRC trim source.
 */
typedef enum _scg_firc_trim_src
{
    kSCG_FircTrimSrcUsb0   = 0U, /*!< USB0 start of frame (1kHz). */
    kSCG_FircTrimSrcUsb1   = 1U, /*!< USB1 start of frame (1kHz). */
    kSCG_FircTrimSrcSysOsc = 2U, /*!< System OSC.                 */
    kSCG_FircTrimSrcRtcOsc = 3U, /*!< RTC OSC (32.768 kHz).       */
} scg_firc_trim_src_t;

/*!
 * @brief SCG fast IRC clock trim configuration.
 */
typedef struct _scg_firc_trim_config
{
    scg_firc_trim_mode_t trimMode; /*!< FIRC trim mode.                       */
    scg_firc_trim_src_t trimSrc;   /*!< Trim source.                          */
    scg_firc_trim_div_t trimDiv;   /*!< Trim predivided value for the system OSC.  */

    uint8_t trimCoar; /*!< Trim coarse value; Irrelevant if trimMode is kSCG_FircTrimUpdate. */
    uint8_t trimFine; /*!< Trim fine value; Irrelevant if trimMode is kSCG_FircTrimUpdate. */
} scg_firc_trim_config_t;

/*!
 * @brief SCG fast IRC clock frequency range.
 */
typedef enum _scg_firc_range
{
    kSCG_FircRange48M, /*!< Fast IRC is trimmed to 48 MHz.  */
    kSCG_FircRange52M, /*!< Fast IRC is trimmed to 52 MHz.  */
    kSCG_FircRange56M, /*!< Fast IRC is trimmed to 56 MHz.  */
    kSCG_FircRange60M  /*!< Fast IRC is trimmed to 60 MHz.  */
} scg_firc_range_t;

/*! @brief FIRC enable mode. */
enum _scg_firc_enable_mode
{
    kSCG_FircEnable       = SCG_FIRCCSR_FIRCEN_MASK,   /*!< Enable FIRC clock.             */
    kSCG_FircEnableInStop = SCG_FIRCCSR_FIRCSTEN_MASK, /*!< Enable FIRC in stop mode.      */
};

/*!
 * @brief SCG fast IRC clock configuration.
 */
typedef struct _scg_firc_config_t
{
    uint32_t enableMode; /*!< Enable mode, OR'ed value of _scg_firc_enable_mode. */

    scg_async_clk_div_t div1; /*!< FIRCDIV1 value.                          */
    scg_async_clk_div_t div2; /*!< FIRCDIV2 value.                          */
    scg_async_clk_div_t div3; /*!< FIRCDIV3 value.                          */

    scg_firc_range_t range; /*!< Fast IRC frequency range.                 */

    const scg_firc_trim_config_t *trimConfig; /*!< Pointer to the FIRC trim configuration; set NULL to disable trim. */
} scg_firc_config_t;

/*!
 * @brief SCG system PLL clock source.
 */
typedef enum _scg_spll_src
{
    kSCG_SysPllSrcSysOsc, /*!< System PLL clock source is system OSC. */
    kSCG_SysPllSrcFirc    /*!< System PLL clock source is fast IRC.   */
} scg_spll_src_t;

/*! @brief SPLL enable mode. */
enum _scg_spll_enable_mode
{
    kSCG_SysPllEnable       = SCG_SPLLCSR_SPLLEN_MASK,  /*!< Enable SPLL clock.             */
    kSCG_SysPllEnableInStop = SCG_SPLLCSR_SPLLSTEN_MASK /*!< Enable SPLL in stop mode.      */
};

/*!
 * @brief SCG system PLL PFD clouk out select.
 */
typedef enum _scg_spll_pfd_clkout
{
    kSCG_SysPllPfd0Clk = 0U,  /*!< PFD0 output clock selected. */
    kSCG_SysPllPfd1Clk = 8U,  /*!< PFD1 output clock selected. */
    kSCG_SysPllPfd2Clk = 16U, /*!< PFD2 output clock selected. */
    kSCG_SysPllPfd3Clk = 24U  /*!< PFD3 output clock selected. */
} scg_spll_pfd_clkout_t;

/*!
 * @brief SCG system PLL configuration.
 */
typedef struct _scg_spll_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _scg_spll_enable_mode */

    scg_async_clk_div_t div1; /*!< SPLLDIV1 value.                          */
    scg_async_clk_div_t div2; /*!< SPLLDIV2 value.                          */
    scg_async_clk_div_t div3; /*!< SPLLDIV3 value.                          */

    scg_spll_src_t src;              /*!< Clock source.                        */
    bool isPfdSelected;              /*!< SPLL PFD output clock selected.      */
    uint8_t prediv;                  /*!< PLL reference clock divider.         */
    scg_spll_pfd_clkout_t pfdClkout; /*!< PLL PFD clouk out select.            */
    uint8_t mult;                    /*!< System PLL multiplier.               */
} scg_spll_config_t;

/*!
 * @brief SCG RTC OSC monitor mode.
 */
typedef enum _scg_rosc_monitor_mode
{
    kSCG_rtcOscMonitorDisable = 0U,                      /*!< Monitor disable.                          */
    kSCG_rtcOscMonitorInt     = SCG_ROSCCSR_ROSCCM_MASK, /*!< Interrupt when the RTC OSC error is detected. */
    kSCG_rtcOscMonitorReset =
        SCG_ROSCCSR_ROSCCM_MASK | SCG_ROSCCSR_ROSCCMRE_MASK /*!< Reset when the RTC OSC error is detected.     */
} scg_rosc_monitor_mode_t;

/*!
 * @brief SCG RTC OSC configuration.
 */
typedef struct _scg_rosc_config
{
    scg_rosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.     */
} scg_rosc_config_t;

/*!
 * @brief SCG auxiliary PLL clock source.
 */
typedef enum _scg_apll_src
{
    kSCG_AuxPllSrcSysOsc, /*!< Auxiliary PLL clock source is the system OSC. */
    kSCG_AuxPllSrcFirc    /*!< Auxiliary PLL clock source is the fast IRC.   */
} scg_apll_src_t;

/*! @brief APLL enable mode. */
enum _scg_apll_enable_mode
{
    kSCG_AuxPllEnable       = SCG_APLLCSR_APLLEN_MASK,  /*!< Enable APLL clock.             */
    kSCG_AuxPllEnableInStop = SCG_APLLCSR_APLLSTEN_MASK /*!< Enable APLL in stop mode.      */
};

/*!
 * @brief SCG auxiliary PLL PFD clouk out select.
 */
typedef enum _scg_apll_pfd_clkout
{
    kSCG_AuxPllPfd0Clk = 0U,  /*!< PFD0 output clock selected. */
    kSCG_AuxPllPfd1Clk = 8U,  /*!< PFD1 output clock selected. */
    kSCG_AuxPllPfd2Clk = 16U, /*!< PFD2 output clock selected. */
    kSCG_AuxPllPfd3Clk = 24U  /*!< PFD3 output clock selected. */
} scg_apll_pfd_clkout_t;

/*!
 * @brief SCG auxiliary PLL configuration.
 */
typedef struct _scg_apll_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _scg_apll_enable_mode */

    scg_async_clk_div_t div1; /*!< APLLDIV1 value.                          */
    scg_async_clk_div_t div2; /*!< APLLDIV2 value.                          */
    scg_async_clk_div_t div3; /*!< APLLDIV3 value.                          */

    scg_apll_src_t src;              /*!< Clock source.                            */
    bool isPfdSelected;              /*!< APLL PFD output clock selected.             */
    uint8_t prediv;                  /*!< PLL reference clock divider.             */
    scg_apll_pfd_clkout_t pfdClkout; /*!< SCG auxiliary PLL PFD clouk out select.   */
    uint8_t mult;                    /*!< Auxiliary PLL multiplier.                   */
    scg_sys_clk_div_t pllPostdiv1;   /*!< Auxiliary PLL Post Clock Divide1 Ratio.     */
    scg_sys_clk_div_t pllPostdiv2;   /*!< Auxiliary PLL Post Clock Divide2 Ratio.     */

    uint32_t num : 30;   /*!< 30-bit numerator of the Auxiliary PLL Fractional-Loop divider. */
    uint32_t denom : 30; /*!< 30-bit denominator of the Auxiliary PLL Fractional-Loop divider. */
} scg_apll_config_t;

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
    assert((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_PR_MASK);

    (*(volatile uint32_t *)(uint32_t)name) |= PCC_CLKCFG_CGC_MASK;
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    assert((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_PR_MASK);

    (*(volatile uint32_t *)(uint32_t)name) &= ~PCC_CLKCFG_CGC_MASK;
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
    assert((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_PR_MASK);

    return (((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_INUSE_MASK) != 0UL) ? true : false;
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
static inline void CLOCK_SetIpSrc(clock_ip_name_t name, clock_ip_src_t src)
{
    uint32_t reg = (*(volatile uint32_t *)(uint32_t)name);

    assert(reg & PCC_CLKCFG_PR_MASK);
    assert(0UL == (reg & PCC_CLKCFG_INUSE_MASK)); /* Should not change if clock has been enabled by other core. */

    reg = (reg & ~PCC_CLKCFG_PCS_MASK) | PCC_CLKCFG_PCS(src);

    /*
     * If clock is already enabled, first disable it, then set the clock
     * source and re-enable it.
     */
    (*(volatile uint32_t *)(uint32_t)name) = reg & ~PCC_CLKCFG_CGC_MASK;
    (*(volatile uint32_t *)(uint32_t)name) = reg;
}

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
static inline void CLOCK_SetIpSrcDiv(clock_ip_name_t name, clock_ip_src_t src, uint8_t divValue, uint8_t fracValue)
{
    uint32_t reg = (*(volatile uint32_t *)(uint32_t)name);

    assert(reg & PCC_CLKCFG_PR_MASK);
    assert(0UL == (reg & PCC_CLKCFG_INUSE_MASK)); /* Should not change if clock has been enabled by other core. */

    if ((kCLOCK_Sai0 == name) || (kCLOCK_Sai1 == name))
    {
        reg =
            (reg & ~(PCC_CLKCFG_PCS_MASK | PCC1_PCC_SAI1_PCD_MASK)) | PCC_CLKCFG_PCS(src) | PCC1_PCC_SAI1_PCD(divValue);
    }
    else
    {
        reg = (reg & ~(PCC_CLKCFG_PCS_MASK | PCC_CLKCFG_FRAC_MASK | PCC_CLKCFG_PCD_MASK)) | PCC_CLKCFG_PCS(src) |
              PCC_CLKCFG_PCD(divValue) | PCC_CLKCFG_FRAC(fracValue);
    }

    /*
     * If clock is already enabled, first disable it, then set the clock
     * source and re-enable it.
     */
    (*(volatile uint32_t *)(uint32_t)name) = reg & ~PCC_CLKCFG_CGC_MASK;
    (*(volatile uint32_t *)(uint32_t)name) = reg;
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
 * @brief Get the core clock or system clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);

/*!
 * @brief Get the platform clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void);

/*!
 * @brief Get the external clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetExtClkFreq(void);

/*!
 * @brief Get the bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void);

/*!
 * @brief Get the slow clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetSlowClkFreq(void);

/*!
 * @brief Get the OSC 32K clock frequency (OSC32KCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc32kClkFreq(void);

/*!
 * @brief Get the external reference clock frequency (ERCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetErClkFreq(void);

/*!
 * @brief Get the external LVDS pad clock frequency (LVDS).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetLvdsClkFreq(void);

/*!
 * @brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency based on PCC registers. It is
 * only used for the IP modules which could select clock source by PCC[PCS].
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
 * @brief Gets the SCG system clock frequency.
 *
 * This function gets the SCG system clock frequency. These clocks are used for
 * core, platform, external, and bus clock domains.
 *
 * @param type     Which type of clock to get, core clock or slow clock.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetSysClkFreq(scg_sys_clk_t type);

/*!
 * @brief Sets the system clock configuration for VLPR mode.
 *
 * This function sets the system clock configuration for VLPR mode.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetVlprModeSysClkConfig(const scg_sys_clk_config_t *config)
{
    assert(config);

    SCG->VCCR = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Sets the system clock configuration for RUN mode.
 *
 * This function sets the system clock configuration for RUN mode.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetRunModeSysClkConfig(const scg_sys_clk_config_t *config)
{
    assert(config);

    SCG->RCCR = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Sets the system clock configuration for HSRUN mode.
 *
 * This function sets the system clock configuration for HSRUN mode.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_SetHsrunModeSysClkConfig(const scg_sys_clk_config_t *config)
{
    assert(config);

    SCG->HCCR = *(const uint32_t *)(uint32_t)config;
}

/*!
 * @brief Gets the system clock configuration in the current power mode.
 *
 * This function gets the system configuration in the current power mode.
 *
 * @param config Pointer to the configuration.
 */
static inline void CLOCK_GetCurSysClkConfig(scg_sys_clk_config_t *config)
{
    assert(config);

    *(uint32_t *)(uint32_t)config = SCG->CSR;
}

/*!
 * @brief Sets the clock out selection.
 *
 * This function sets the clock out selection (CLKOUTSEL).
 *
 * @param setting The selection to set.
 * @return  The current clock out selection.
 */
static inline void CLOCK_SetClkOutSel(clock_clkout_src_t setting)
{
    SCG->CLKOUTCNFG = SCG_CLKOUTCNFG_CLKOUTSEL(setting);
}
/* @} */

/*!
 * @name SCG System OSC Clock.
 * @{
 */

/*!
 * @brief Initializes the SCG system OSC.
 *
 * This function enables the SCG system OSC clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success System OSC is initialized.
 * @retval kStatus_SCG_Busy System OSC has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly System OSC control register is locked.
 *
 * @note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysOsc(const scg_sosc_config_t *config);

/*!
 * @brief De-initializes the SCG system OSC.
 *
 * This function disables the SCG system OSC clock.
 *
 * @retval kStatus_Success System OSC is deinitialized.
 * @retval kStatus_SCG_Busy System OSC is used by the system clock.
 * @retval kStatus_ReadOnly System OSC control register is locked.
 *
 * @note This function can't detect whether the system OSC is used by an IP.
 */
status_t CLOCK_DeinitSysOsc(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetSysOscAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->SOSCDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv3Clk:
            reg = (reg & ~SCG_SOSCDIV_SOSCDIV3_MASK) | SCG_SOSCDIV_SOSCDIV3(divider);
            break;
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_SOSCDIV_SOSCDIV2_MASK) | SCG_SOSCDIV_SOSCDIV2(divider);
            break;
        default:
            reg = (reg & ~SCG_SOSCDIV_SOSCDIV1_MASK) | SCG_SOSCDIV_SOSCDIV1(divider);
            break;
    }

    SCG->SOSCDIV = reg;
}

/*!
 * @brief Gets the SCG system OSC clock frequency (SYSOSC).
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the system OSC.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Checks whether the system OSC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsSysOscErr(void)
{
    return ((SCG->SOSCCSR & SCG_SOSCCSR_SOSCERR_MASK) == SCG_SOSCCSR_SOSCERR_MASK);
}

/*!
 * @brief Clears the system OSC clock error.
 */
static inline void CLOCK_ClearSysOscErr(void)
{
    SCG->SOSCCSR |= SCG_SOSCCSR_SOSCERR_MASK;
}

/*!
 * @brief Sets the system OSC monitor mode.
 *
 * This function sets the system OSC monitor mode. The mode can be disabled,
 * it can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
static inline void CLOCK_SetSysOscMonitorMode(scg_sosc_monitor_mode_t mode)
{
    uint32_t reg = SCG->SOSCCSR;

    reg &= ~(SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK);

    reg |= (uint32_t)mode;

    SCG->SOSCCSR = reg;
}

/*!
 * @brief Checks whether the system OSC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsSysOscValid(void)
{
    return ((SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) == SCG_SOSCCSR_SOSCVLD_MASK);
}
/* @} */

/*!
 * @name SCG Slow IRC Clock.
 * @{
 */

/*!
 * @brief Initializes the SCG slow IRC clock.
 *
 * This function enables the SCG slow IRC clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success SIRC is initialized.
 * @retval kStatus_SCG_Busy SIRC has been enabled and is used by system clock.
 * @retval kStatus_ReadOnly SIRC control register is locked.
 *
 * @note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSirc(const scg_sirc_config_t *config);

/*!
 * @brief De-initializes the SCG slow IRC.
 *
 * This function disables the SCG slow IRC.
 *
 * @retval kStatus_Success SIRC is deinitialized.
 * @retval kStatus_SCG_Busy SIRC is used by system clock.
 * @retval kStatus_ReadOnly SIRC control register is locked.
 *
 * @note This function can't detect whether the SIRC is used by an IP.
 */
status_t CLOCK_DeinitSirc(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetSircAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->SIRCDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv3Clk:
            reg = (reg & ~SCG_SIRCDIV_SIRCDIV3_MASK) | SCG_SIRCDIV_SIRCDIV3(divider);
            break;
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_SIRCDIV_SIRCDIV2_MASK) | SCG_SIRCDIV_SIRCDIV2(divider);
            break;
        default:
            reg = (reg & ~SCG_SIRCDIV_SIRCDIV1_MASK) | SCG_SIRCDIV_SIRCDIV1(divider);
            break;
    }

    SCG->SIRCDIV = reg;
}

/*!
 * @brief Enables/disables the SCG slow IRC 1khz LPO clock in LLS/VLLSx modes.
 *
 * This function enables/disables the SCG slow IRC 1khz LPO clock in LLS/VLLSx modes.
 *
 * @param enable   Switcher of LPO Power Option which controls whether the 1 kHz LPO clock is enabled in LLS/VLLSx
 * modes.
 *                 "true" means to enable, "false" means not enabled.
 */
static inline void CLOCK_EnableLpoPowerOption(bool enable)
{
    if (enable)
    {
        SCG->SIRCCSR &= ~SCG_SIRCCSR_LPOPO_MASK;
    }
    else
    {
        SCG->SIRCCSR |= SCG_SIRCCSR_LPOPO_MASK;
    }
}

/*!
 * @brief Gets the SCG SIRC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the SIRC.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Checks whether the SIRC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsSircValid(void)
{
    return ((SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) == SCG_SIRCCSR_SIRCVLD_MASK);
}
/* @} */

/*!
 * @name SCG Fast IRC Clock.
 * @{
 */

/*!
 * @brief Initializes the SCG fast IRC clock.
 *
 * This function enables the SCG fast IRC clock according to the configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success FIRC is initialized.
 * @retval kStatus_SCG_Busy FIRC has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly FIRC control register is locked.
 *
 * @note This function can't detect whether the FIRC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitFirc(const scg_firc_config_t *config);

/*!
 * @brief De-initializes the SCG fast IRC.
 *
 * This function disables the SCG fast IRC.
 *
 * @retval kStatus_Success FIRC is deinitialized.
 * @retval kStatus_SCG_Busy FIRC is used by the system clock.
 * @retval kStatus_ReadOnly FIRC control register is locked.
 *
 * @note This function can't detect whether the FIRC is used by an IP.
 */
status_t CLOCK_DeinitFirc(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetFircAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->FIRCDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv3Clk:
            reg = (reg & ~SCG_FIRCDIV_FIRCDIV3_MASK) | SCG_FIRCDIV_FIRCDIV3(divider);
            break;
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_FIRCDIV_FIRCDIV2_MASK) | SCG_FIRCDIV_FIRCDIV2(divider);
            break;
        default:
            reg = (reg & ~SCG_FIRCDIV_FIRCDIV1_MASK) | SCG_FIRCDIV_FIRCDIV1(divider);
            break;
    }

    SCG->FIRCDIV = reg;
}

/*!
 * @brief Gets the SCG FIRC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the FIRC.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Checks whether the FIRC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsFircErr(void)
{
    return ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) == SCG_FIRCCSR_FIRCERR_MASK);
}

/*!
 * @brief Clears the FIRC clock error.
 */
static inline void CLOCK_ClearFircErr(void)
{
    SCG->FIRCCSR |= SCG_FIRCCSR_FIRCERR_MASK;
}

/*!
 * @brief Checks whether the FIRC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsFircValid(void)
{
    return ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) == SCG_FIRCCSR_FIRCVLD_MASK);
}
/* @} */

/*!
 * @brief Gets the SCG RTC OSC clock frequency.
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
    return ((SCG->ROSCCSR & SCG_ROSCCSR_ROSCERR_MASK) == SCG_ROSCCSR_ROSCERR_MASK);
}

/*!
 * @brief Clears the RTC OSC clock error.
 */
static inline void CLOCK_ClearRtcOscErr(void)
{
    SCG->ROSCCSR |= SCG_ROSCCSR_ROSCERR_MASK;
}

/*!
 * @brief Sets the RTC OSC monitor mode.
 *
 * This function sets the RTC OSC monitor mode. The mode can be disabled.
 * It can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
static inline void CLOCK_SetRtcOscMonitorMode(scg_rosc_monitor_mode_t mode)
{
    uint32_t reg = SCG->ROSCCSR;

    reg &= ~(SCG_ROSCCSR_ROSCCM_MASK | SCG_ROSCCSR_ROSCCMRE_MASK);

    reg |= (uint32_t)mode;

    SCG->ROSCCSR = reg;
}

/*!
 * @brief Checks whether the RTC OSC clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsRtcOscValid(void)
{
    return ((SCG->ROSCCSR & SCG_ROSCCSR_ROSCVLD_MASK) == SCG_ROSCCSR_ROSCVLD_MASK);
}
/* @} */

/* @} */
/*!
 * @brief Initializes the SCG auxiliary PLL.
 *
 * This function enables the SCG auxiliary PLL clock according to the
 * configuration. The auxiliary PLL can use the system OSC or FIRC as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing APLL clock output:
 * @code
 * const scg_apll_config_t g_scgAuxPllConfig = {.enableMode = kSCG_AuxPllEnable,
 *                                            .div1 = kSCG_AsyncClkDisable,
 *                                            .div2 = kSCG_AsyncClkDisable,
 *                                            .div3 = kSCG_AsyncClkDisable,
 *                                            .src = kSCG_SysPllSrcFirc,
 *                                            .isPfdSelected = false,
 *                                            .prediv = 5U,
 *                                            .pfdClkout = kSCG_AuxPllPfd0Clk,
 *                                            .mult = 20U,
 *                                            .pllPostdiv1 = kSCG_SysClkDivBy3,
 *                                            .pllPostdiv2 = kSCG_SysClkDivBy4,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitAuxPll(&g_scgAuxPllConfig);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success auxiliary PLL is initialized.
 * @retval kStatus_SCG_Busy auxiliary PLL has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly auxiliary PLL control register is locked.
 *
 * @note This function can't detect whether the auxiliary PLL has been enabled and
 * is used by an IP.
 */
status_t CLOCK_InitAuxPll(const scg_apll_config_t *config);

/*!
 * @brief De-initializes the SCG auxiliary PLL.
 *
 * This function disables the SCG auxiliary PLL.
 *
 * @retval kStatus_Success auxiliary PLL is deinitialized.
 * @retval kStatus_SCG_Busy auxiliary PLL is used by the system clock.
 * @retval kStatus_ReadOnly auxiliary PLL control register is locked.
 *
 * @note This function can't detect whether the auxiliary PLL is used by an IP.
 */
status_t CLOCK_DeinitAuxPll(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetAuxPllAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->APLLDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv1Clk:
            reg = (reg & ~SCG_APLLDIV_APLLDIV1_MASK) | SCG_APLLDIV_APLLDIV1(divider);
            break;
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_APLLDIV_APLLDIV2_MASK) | SCG_APLLDIV_APLLDIV2(divider);
            break;
        default:
            reg = (reg & ~SCG_APLLDIV_APLLDIV1_MASK) | SCG_APLLDIV_APLLDIV1(divider);
            break;
    }

    SCG->APLLDIV = reg;
}

/*!
 * @brief Gets the SCG auxiliary PLL clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the auxiliary PLL.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Gets the SCG auxiliary PLL PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clocks out. See "scg_apll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllPfdFreq(scg_apll_pfd_clkout_t pfdClkout);

/*!
 * @brief Enables the SCG auxiliary PLL Fractional Divide (PFD) clock out with configurations.
 *
 * APLL Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * Example code for configuring APLL as APLL PFD clock output:
 * @code
 * const scg_apll_config_t g_scgAuxPllConfig = {.enableMode = kSCG_AuxPllEnable,
 *                                              .div1 = kSCG_AsyncClkDisable,
 *                                              .div2 = kSCG_AsyncClkDisable,
 *                                              .div3 = kSCG_AsyncClkDisable,
 *                                              .src = kSCG_SysPllSrcFirc,
 *                                              .isPfdSelected = true,
 *                                              .prediv = 5U,
 *                                              .pfdClkout = kSCG_AuxPllPfd3Clk,
 * clock
 *                                              .mult = 20U,
 *                                              .pllPostdiv1 = kSCG_SysClkDivBy1,
 *                                              .pllPostdiv2 = kSCG_SysClkDivBy1,
 *                                              .num = 578,
 *                                              .denom = 1000};
 * CLOCK_InitAuxPll(&g_scgAuxPllConfig);
 * CLOCK_EnableAuxPllPfdClkout(g_scgAuxPllConfig.pfdClkout, 15U);
 * @endcode
 *
 * @param pfdClkout  APLL PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnableAuxPllPfdClkout(scg_apll_pfd_clkout_t pfdClkout, uint8_t fracValue);

/*!
 * @brief Disables the SCG auxiliary PLL Fractional Divide (PFD) clock out.
 */
static inline void CLOCK_DisableAuxPllPfdClkout(scg_apll_pfd_clkout_t pfdClkout)
{
    SCG->APLLPFD |= SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);
}

/*!
 * @brief Enables the SCG auxiliary PLL spread spectrum modulation feature with configurations.
 *
 * This function sets the SCG auxiliary PLL spread spectrum modulation configurations.
 * STOP and STEP together control the modulation depth (maximum frequency change)
 * and modulation frequency.
 *
 * Modulation Depth = (STOP/MFD)*Fref where MFD is the DENOM field value in DENOM register.
 * Modulation Frequency = (STEP/(2*STOP))*Fref.
 *
 * @param step  APLL Spread Spectrum STEP.
 * @param stop  APLL Spread Spectrum STOP.
 */
static inline void CLOCK_EnableAuxPllSpectrumModulation(uint16_t step, uint16_t stop)
{
    SCG->APLLSS = (SCG->APLLSS & ~(SCG_APLLSS_STEP_MASK | SCG_APLLSS_STOP_MASK)) |
                  (SCG_APLLSS_STEP(step) | SCG_APLLSS_STOP(stop) | SCG_APLLSS_ENABLE_MASK);
}

/*!
 * @brief Disables the SCG auxiliary PLL spread spectrum modulation.
 *
 */
static inline void CLOCK_DisableAuxPllSpectrumModulation(void)
{
    SCG->APLLSS &= ~SCG_APLLSS_ENABLE_MASK;
}

/*!
 * @brief Sets the SCG auxiliary PLL lock time.
 *
 * @param lockTime  Reference clocks to count before APLL is considered locked and valid.
 */
static inline void CLOCK_SetAuxPllLockTime(uint16_t lockTime)
{
    SCG->APLLLOCK_CNFG = SCG_APLLLOCK_CNFG_LOCK_TIME(lockTime);
}

/*!
 * @brief Checks whether the auxiliary PLL clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsAuxPllValid(void)
{
    return ((SCG->APLLCSR & SCG_APLLCSR_APLLVLD_MASK) == SCG_APLLCSR_APLLVLD_MASK);
}
/* @} */

/*!
 * @brief Initializes the SCG system PLL.
 *
 * This function enables the SCG system PLL clock according to the
 * configuration. The system PLL can use the system OSC or FIRC as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing SPLL clock output:
 * @code
 * const scg_spll_config_t g_scgSysPllConfig = {.enableMode = kSCG_SysPllEnable,
 *                                              .div1 = kSCG_AsyncClkDivBy1,
 *                                              .div2 = kSCG_AsyncClkDisable,
 *                                              .div3 = kSCG_AsyncClkDivBy2,
 *                                              .src = kSCG_SysPllSrcFirc,
 *                                              .isPfdSelected = false,
 *                                              .prediv = 0U,
 *                                              .pfdClkout = kSCG_SysPllPfd0Clk,
 *                                              .mult = 3U};
 * CLOCK_InitSysPll(&g_scgSysPllConfig);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success System PLL is initialized.
 * @retval kStatus_SCG_Busy System PLL has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly System PLL control register is locked.
 *
 * @note This function can't detect whether the system PLL has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysPll(const scg_spll_config_t *config);

/*!
 * @brief De-initializes the SCG system PLL.
 *
 * This function disables the SCG system PLL.
 *
 * @retval kStatus_Success system PLL is deinitialized.
 * @retval kStatus_SCG_Busy system PLL is used by the system clock.
 * @retval kStatus_ReadOnly System PLL control register is locked.
 *
 * @note This function can't detect whether the system PLL is used by an IP.
 */
status_t CLOCK_DeinitSysPll(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetSysPllAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->SPLLDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv3Clk:
            reg = (reg & ~SCG_SPLLDIV_SPLLDIV3_MASK) | SCG_SPLLDIV_SPLLDIV3(divider);
            break;
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_SPLLDIV_SPLLDIV2_MASK) | SCG_SPLLDIV_SPLLDIV2(divider);
            break;
        default:
            reg = (reg & ~SCG_SPLLDIV_SPLLDIV1_MASK) | SCG_SPLLDIV_SPLLDIV1(divider);
            break;
    }

    SCG->SPLLDIV = reg;
}

/*!
 * @brief Gets the SCG system PLL clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the system PLL.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Gets the SCG system PLL PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clock out. See "scg_spll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllPfdFreq(scg_spll_pfd_clkout_t pfdClkout);

/*!
 * @brief Enables the SCG system PLL Fractional Divide (PFD) clock out with configurations.
 *
 * SPLL Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * @code
 * Example code for configuring SPLL as SPLL PFD clock output:
 * const scg_spll_config_t g_scgSysPllConfig = {.enableMode = kSCG_SysPllEnable,
 *                                            .div1 = kSCG_AsyncClkDisable,
 *                                            .div2 = kSCG_AsyncClkDisable,
 *                                            .div3 = kSCG_AsyncClkDisable,
 *                                            .src = kSCG_SysPllSrcFirc,
 *                                            .isPfdSelected = true,
 *                                            .prediv = 5U,
 *                                            .pfdClkout = kSCG_AuxPllPfd3Clk,
 * clock
 *                                            .mult = 20U};
 * CLOCK_InitSysPll(&g_scgSysPllConfig);
 * CLOCK_EnableSysPllPfdClkout(g_scgSysPllConfig.pfdClkout, 15U);
 * @endcode
 *
 * @param pfdClkout  SPLL PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnableSysPllPfdClkout(scg_spll_pfd_clkout_t pfdClkout, uint8_t fracValue);

/*!
 * @brief Disables the SCG system PLL Fractional Divide (PFD) clock out.
 */
static inline void CLOCK_DisableSysPllPfdClkout(scg_spll_pfd_clkout_t pfdClkout)
{
    SCG->SPLLPFD |= SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);
}

/*!
 * @brief Checks whether the system PLL clock error occurs.
 *
 * @return  True if an error occurs, false if not.
 */
static inline bool CLOCK_IsSysPllErr(void)
{
    return ((SCG->SPLLCSR & SCG_SPLLCSR_SPLLERR_MASK) == SCG_SPLLCSR_SPLLERR_MASK);
}

/*!
 * @brief Clears the system PLL clock error.
 */
static inline void CLOCK_ClearSysPllErr(void)
{
    SCG->SPLLCSR |= SCG_SPLLCSR_SPLLERR_MASK;
}

/*!
 * @brief Checks whether the system PLL clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsSysPllValid(void)
{
    return ((SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK) == SCG_SPLLCSR_SPLLVLD_MASK);
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

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
