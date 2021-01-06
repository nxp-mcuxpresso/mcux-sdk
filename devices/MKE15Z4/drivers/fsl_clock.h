/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2020, NXP
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
 * Configurations
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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.3.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))
/*@}*/

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

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (72000000UL)
#endif

/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS  \
    {               \
        kCLOCK_Rtc0 \
    }

/*! @brief Clock ip name array for PORT. */
#define PORT_CLOCKS                                                          \
    {                                                                        \
        kCLOCK_PortA, kCLOCK_PortB, kCLOCK_PortC, kCLOCK_PortD, kCLOCK_PortE \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS  \
    {                 \
        kCLOCK_Lpi2c0 \
    }

/*! @brief Clock ip name array for TSI. */
#define TSI_CLOCKS  \
    {               \
        kCLOCK_Tsi0 \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                  \
    {                                                  \
        kCLOCK_Lpuart0, kCLOCK_Lpuart1, kCLOCK_Lpuart2 \
    }

/*! @brief Clock ip name array for LPTMR. */
#define LPTMR_CLOCKS  \
    {                 \
        kCLOCK_Lptmr0 \
    }

/*! @brief Clock ip name array for ADC12. */
#define ADC12_CLOCKS \
    {                \
        kCLOCK_Adc0  \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS  \
    {                 \
        kCLOCK_Lpspi0 \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS  \
    {                \
        kCLOCK_Lpit0 \
    }

/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc0 \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS  \
    {               \
        kCLOCK_Cmp0 \
    }

/*! @brief Clock ip name array for FLASH. */
#define FLASH_CLOCKS  \
    {                 \
        kCLOCK_Flash0 \
    }

/*! @brief Clock ip name array for EWM. */
#define EWM_CLOCKS  \
    {               \
        kCLOCK_Ewm0 \
    }

/*! @brief Clock ip name array for FLEXTMR. */
#define FTM_CLOCKS               \
    {                            \
        kCLOCK_Ftm0, kCLOCK_Ftm1 \
    }

/*! @brief Clock ip name array for PDB. */
#define PDB_CLOCKS  \
    {               \
        kCLOCK_Pdb0 \
    }

/*! @brief Clock ip name array for PWT. */
#define PWT_CLOCKS  \
    {               \
        kCLOCK_Pwt0 \
    }
/*! @brief Clock ip name array for MSCAN. */

/*!
 * @brief LPO clock frequency.
 */
#define LPO_CLK_FREQ 128000U

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    /* ----------------------------- System layer clock -------------------------------*/
    kCLOCK_CoreSysClk, /*!< Core/system clock                                   */
    kCLOCK_BusClk,     /*!< Bus clock                                           */
    kCLOCK_FlashClk,   /*!< Flash clock                                         */

    /* ------------------------------------ SCG clock ---------------------------------*/
    kCLOCK_ScgSysOscClk, /*!< SCG system OSC clock. (SYSOSC)                      */
    kCLOCK_ScgSircClk,   /*!< SCG SIRC clock.                                     */
    kCLOCK_ScgFircClk,   /*!< SCG FIRC clock.                                     */
    kCLOCK_ScgLpFllClk,  /*!< SCG low power FLL clock. (LPFLL)                    */

    kCLOCK_ScgSysOscAsyncDiv2Clk, /*!< SOSCDIV2_CLK.                                   */

    kCLOCK_ScgSircAsyncDiv2Clk, /*!< SIRCDIV2_CLK.                                   */

    kCLOCK_ScgFircAsyncDiv2Clk, /*!< FIRCDIV2_CLK.                                   */

    kCLOCK_ScgLpFllAsyncDiv2Clk, /*!< LPFLLDIV2_CLK.                                   */

    /* --------------------------------- Other clock ----------------------------------*/
    kCLOCK_LpoClk, /*!< LPO clock                                           */
    kCLOCK_ErClk,  /*!< ERCLK. The external reference clock from SCG.       */
} clock_name_t;

#define kCLOCK_Osc0ErClk       kCLOCK_ErClk
#define CLOCK_GetOsc0ErClkFreq CLOCK_GetErClkFreq /*!< For compatible with other MCG platforms. */

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum _clock_ip_src
{
    kCLOCK_IpSrcNoneOrExt   = 0U, /*!< Clock is off or external clock is used. */
    kCLOCK_IpSrcSysOscAsync = 1U, /*!< System Oscillator async clock.          */
    kCLOCK_IpSrcSircAsync   = 2U, /*!< Slow IRC async clock.                   */
    kCLOCK_IpSrcFircAsync   = 3U, /*!< Fast IRC async clock.                   */
    kCLOCK_IpSrcLpFllAsync  = 5U  /*!< LPFLL async clock.                      */
} clock_ip_src_t;

/*!
 * @brief Peripheral clock name difinition used for clock gate, clock source
 * and clock divider setting. It is defined as the corresponding register address.
 */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,

    /* PCC 0 */
    kCLOCK_Flash0  = 0x40065080U,
    kCLOCK_Lpspi0  = 0x400650B0U,
    kCLOCK_Crc0    = 0x400650C8U,
    kCLOCK_Pdb0    = 0x400650D8U,
    kCLOCK_Lpit0   = 0x400650DCU,
    kCLOCK_Ftm0    = 0x400650E0U,
    kCLOCK_Ftm1    = 0x400650E4U,
    kCLOCK_Adc0    = 0x400650ECU,
    kCLOCK_Rtc0    = 0x400650F4U,
    kCLOCK_Lptmr0  = 0x40065100U,
    kCLOCK_Tsi0    = 0x40065114U,
    kCLOCK_PortA   = 0x40065124U,
    kCLOCK_PortB   = 0x40065128U,
    kCLOCK_PortC   = 0x4006512CU,
    kCLOCK_PortD   = 0x40065130U,
    kCLOCK_PortE   = 0x40065134U,
    kCLOCK_Pwt0    = 0x40065158U,
    kCLOCK_Ewm0    = 0x40065184U,
    kCLOCK_Lpi2c0  = 0x40065198U,
    kCLOCK_Lpuart0 = 0x400651A8U,
    kCLOCK_Lpuart1 = 0x400651ACU,
    kCLOCK_Lpuart2 = 0x400651B0U,
    kCLOCK_Cmp0    = 0x400651CCU,
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
    kSCG_SysClkSrcLpFll  = 5U, /*!< Low power FLL. */
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
    uint32_t : 4;         /*!< Reserved. */
    uint32_t : 4;         /*!< Reserved. */
    uint32_t : 4;         /*!< Reserved. */
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
    kClockClkoutSelScgSlow = 0U, /*!< SCG slow clock. */
    kClockClkoutSelSysOsc  = 1U, /*!< System OSC.     */
    kClockClkoutSelSirc    = 2U, /*!< Slow IRC.       */
    kClockClkoutSelFirc    = 3U, /*!< Fast IRC.       */
    kClockClkoutSelLpFll   = 5U, /*!< Low power FLL.  */
} clock_clkout_src_t;

/*!
 * @brief SCG asynchronous clock type.
 */
typedef enum _scg_async_clk
{
    kSCG_AsyncDiv2Clk, /*!< The async clock by DIV2, e.g. SOSCDIV2_CLK, SIRCDIV2_CLK. */
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
enum
{
    kSCG_SysOscEnable           = SCG_SOSCCSR_SOSCEN_MASK,     /*!< Enable OSC clock. */
    kSCG_SysOscEnableInStop     = SCG_SOSCCSR_SOSCSTEN_MASK,   /*!< Enable OSC in stop mode. */
    kSCG_SysOscEnableInLowPower = SCG_SOSCCSR_SOSCLPEN_MASK,   /*!< Enable OSC in low power mode. */
    kSCG_SysOscEnableErClk      = SCG_SOSCCSR_SOSCERCLKEN_MASK /*!< Enable OSCERCLK. */
};

/*!
 * @brief SCG system OSC configuration.
 */
typedef struct _scg_sosc_config
{
    uint32_t freq;                       /*!< System OSC frequency.                    */
    scg_sosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.     */
    uint8_t enableMode;                  /*!< Enable mode, OR'ed value of _scg_sosc_enable_mode.  */

    scg_async_clk_div_t div2; /*!< SOSCDIV2 value.                          */

    scg_sosc_mode_t workMode; /*!< OSC work mode.                           */
} scg_sosc_config_t;

/*!
 * @brief SCG slow IRC clock frequency range.
 */
typedef enum _scg_sirc_range
{
    kSCG_SircRangeLow, /*!< Slow IRC low range clock (2 MHz, 4 MHz for i.MX 7 ULP).  */
    kSCG_SircRangeHigh /*!< Slow IRC high range clock (8 MHz, 16 MHz for i.MX 7 ULP). */
} scg_sirc_range_t;

/*! @brief SIRC enable mode. */
enum
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
    scg_async_clk_div_t div2; /*!< SIRCDIV2 value.                          */

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
    kSCG_FircTrimSrcSysOsc = 2U, /*!< System OSC.                 */
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
} scg_firc_range_t;

/*! @brief FIRC enable mode. */
enum
{
    kSCG_FircEnable           = SCG_FIRCCSR_FIRCEN_MASK,    /*!< Enable FIRC clock.             */
    kSCG_FircEnableInStop     = SCG_FIRCCSR_FIRCSTEN_MASK,  /*!< Enable FIRC in stop mode.      */
    kSCG_FircEnableInLowPower = SCG_FIRCCSR_FIRCLPEN_MASK,  /*!< Enable FIRC in low power mode. */
    kSCG_FircDisableRegulator = SCG_FIRCCSR_FIRCREGOFF_MASK /*!< Disable regulator.             */
};

/*!
 * @brief SCG fast IRC clock configuration.
 */
typedef struct _scg_firc_config_t
{
    uint32_t enableMode; /*!< Enable mode, OR'ed value of _scg_firc_enable_mode. */

    scg_async_clk_div_t div2; /*!< FIRCDIV2 value.                          */

    scg_firc_range_t range; /*!< Fast IRC frequency range.                 */

    const scg_firc_trim_config_t *trimConfig; /*!< Pointer to the FIRC trim configuration; set NULL to disable trim. */
} scg_firc_config_t;

/*! @brief LPFLL enable mode. */
enum
{
    kSCG_LpFllEnable = SCG_LPFLLCSR_LPFLLEN_MASK, /*!< Enable LPFLL clock.             */
};

/*!
 * @brief SCG LPFLL clock frequency range.
 */
typedef enum _scg_lpfll_range
{
    kSCG_LpFllRange48M, /*!< LPFLL is trimmed to 48MHz.  */
} scg_lpfll_range_t;

/*!
 * @brief SCG LPFLL trim mode.
 */
typedef enum _scg_lpfll_trim_mode
{
    kSCG_LpFllTrimNonUpdate = SCG_LPFLLCSR_LPFLLTREN_MASK,
    /*!< LPFLL trim is enabled but the trim value update is not enabled. In this mode, the
     trim value is fixed to the initialized value, which is defined by the Member variable trimValue
     in the structure @ref scg_lpfll_trim_config_t.*/

    kSCG_LpFllTrimUpdate = SCG_LPFLLCSR_LPFLLTREN_MASK | SCG_LPFLLCSR_LPFLLTRUP_MASK
    /*!< FIRC trim is enabled and trim value update is enabled. In this mode, the trim
     value is automatically updated. */
} scg_lpfll_trim_mode_t;

/*!
 * @brief SCG LPFLL trim source.
 */
typedef enum _scg_lpfll_trim_src
{
    kSCG_LpFllTrimSrcSirc   = 0U, /*!< SIRC.                 */
    kSCG_LpFllTrimSrcFirc   = 1U, /*!< FIRC.                 */
    kSCG_LpFllTrimSrcSysOsc = 2U, /*!< System OSC.           */
    kSCG_LpFllTrimSrcRtcOsc = 3U, /*!< RTC OSC (32.768 kHz). */
} scg_lpfll_trim_src_t;

/*!
 * @brief SCG LPFLL lock mode.
 */
typedef enum _scg_lpfll_lock_mode
{
    kSCG_LpFllLock1Lsb = 0U, /*!< Lock with 1 LSB. */
    kSCG_LpFllLock2Lsb = 1U  /*!< Lock with 2 LSB. */
} scg_lpfll_lock_mode_t;

/*!
 * @brief SCG LPFLL clock trim configuration.
 */
typedef struct _scg_lpfll_trim_config
{
    scg_lpfll_trim_mode_t trimMode; /*!< Trim mode.            */
    scg_lpfll_lock_mode_t lockMode; /*!< Lock mode; Irrelevant if the trimMode is kSCG_LpFllTrimNonUpdate. */

    scg_lpfll_trim_src_t trimSrc; /*!< Trim source.          */
    uint8_t trimDiv;              /*!< Trim predivideds value, which can be 0 ~ 31.
                                    [ Trim source frequency / (trimDiv + 1) ] must be 2 MHz or 32768 Hz. */

    uint8_t trimValue; /*!< Trim value; Irrelevant if trimMode is the kSCG_LpFllTrimUpdate. */
} scg_lpfll_trim_config_t;

/*!
 * @brief SCG low power FLL configuration.
 */
typedef struct _scg_lpfll_config
{
    uint8_t enableMode; /*!< Enable mode, OR'ed value of _scg_lpfll_enable_mode */

    scg_async_clk_div_t div2; /*!< LPFLLDIV2 value.                          */

    scg_lpfll_range_t range; /*!< LPFLL frequency range.                     */

    const scg_lpfll_trim_config_t *trimConfig; /*!< Trim configuration; set NULL to disable trim. */
} scg_lpfll_config_t;

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
    assert(((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_PR_MASK) != 0UL);

    (*(volatile uint32_t *)(uint32_t)name) |= PCC_CLKCFG_CGC_MASK;
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    assert(((*(volatile uint32_t *)(uint32_t)name) & PCC_CLKCFG_PR_MASK) != 0UL);

    (*(volatile uint32_t *)(uint32_t)name) &= ~PCC_CLKCFG_CGC_MASK;
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

    reg = (reg & ~PCC_CLKCFG_PCS_MASK) | PCC_CLKCFG_PCS(src);

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
 * @brief Get the bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void);

/*!
 * @brief Get the flash clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void);

/*!
 * @brief Get the external reference clock frequency (ERCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetErClkFreq(void);

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
    union
    {
        const uint32_t *configInt;
        const scg_sys_clk_config_t *configPtr;
    } Config;

    Config.configPtr = config;
    SCG->VCCR        = *(Config.configInt);
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
    union
    {
        const uint32_t *configInt;
        const scg_sys_clk_config_t *configPtr;
    } Config;

    Config.configPtr = config;
    SCG->RCCR        = *(Config.configInt);
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
    union
    {
        uint32_t *configInt;
        scg_sys_clk_config_t *configPtr;
    } Config;

    Config.configPtr    = config;
    *(Config.configInt) = SCG->CSR;
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
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_SOSCDIV_SOSCDIV2_MASK) | SCG_SOSCDIV_SOSCDIV2(divider);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
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
    return (bool)(SCG->SOSCCSR & SCG_SOSCCSR_SOSCERR_MASK);
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
    return (bool)(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK);
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
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_SIRCDIV_SIRCDIV2_MASK) | SCG_SIRCDIV_SIRCDIV2(divider);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    SCG->SIRCDIV = reg;
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
    return (bool)(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK);
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
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_FIRCDIV_FIRCDIV2_MASK) | SCG_FIRCDIV_FIRCDIV2(divider);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
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
    return (bool)(SCG->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK);
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
    return (bool)(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK);
}
/* @} */

/*!
 * @name SCG Low Power FLL Clock.
 * @{
 */
/*!
 * @brief Initializes the SCG LPFLL clock.
 *
 * This function enables the SCG LPFLL clock according to the configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success LPFLL is initialized.
 * @retval kStatus_SCG_Busy LPFLL has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly LPFLL control register is locked.
 *
 * @note This function can't detect whether the LPFLL has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitLpFll(const scg_lpfll_config_t *config);

/*!
 * @brief De-initializes the SCG LPFLL.
 *
 * This function disables the SCG LPFLL.
 *
 * @retval kStatus_Success LPFLL is deinitialized.
 * @retval kStatus_SCG_Busy LPFLL is used by the system clock.
 * @retval kStatus_ReadOnly LPFLL control register is locked.
 *
 * @note This function can't detect whether the LPFLL is used by an IP.
 */
status_t CLOCK_DeinitLpFll(void);

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
static inline void CLOCK_SetLpFllAsyncClkDiv(scg_async_clk_t asyncClk, scg_async_clk_div_t divider)
{
    uint32_t reg = SCG->LPFLLDIV;

    switch (asyncClk)
    {
        case kSCG_AsyncDiv2Clk:
            reg = (reg & ~SCG_LPFLLDIV_LPFLLDIV2_MASK) | SCG_LPFLLDIV_LPFLLDIV2(divider);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    SCG->LPFLLDIV = reg;
}

/*!
 * @brief Gets the SCG LPFLL clock frequency.
 *
 * @return  Clock frequency in Hz; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpFllFreq(void);

/*!
 * @brief Gets the SCG asynchronous clock frequency from the LPFLL.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency in Hz; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpFllAsyncFreq(scg_async_clk_t type);

/*!
 * @brief Checks whether the LPFLL clock is valid.
 *
 * @return  True if the clock is valid, false if not.
 */
static inline bool CLOCK_IsLpFllValid(void)
{
    return (bool)(SCG->LPFLLCSR & SCG_LPFLLCSR_LPFLLVLD_MASK);
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

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
