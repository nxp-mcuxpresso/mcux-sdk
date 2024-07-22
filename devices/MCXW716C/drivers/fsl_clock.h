/*
 * Copyright 2021-2022 NXP
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
/*! @brief CLOCK driver version 1.0.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (96000000UL)
#endif

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

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS \
    {               \
        kCLOCK_Dma0 \
    }

/*! @brief Clock ip name array for SYSPM. */
#define SYSPM_CLOCKS  \
    {                 \
        kCLOCK_Syspm0 \
    }

/*! @brief Clock ip name array for SFA. */
#define SFA_CLOCKS                 \
    {                              \
        kCLOCK_Sfa0, kCLOCK_NOGATE \
    }

/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc0 \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                              \
    {                                           \
        kCLOCK_Tpm0, kCLOCK_Tpm1, kCLOCK_NOGATE \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                 \
    {                                \
        kCLOCK_Lpi2c0, kCLOCK_Lpi2c1 \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS  \
    {               \
        kCLOCK_I3c0 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                 \
    {                                \
        kCLOCK_Lpspi0, kCLOCK_Lpspi1 \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                  \
    {                                  \
        kCLOCK_Lpuart0, kCLOCK_Lpuart1 \
    }

/*! @brief Clock ip name array for PORT. */
#define PORT_CLOCKS                              \
    {                                            \
        kCLOCK_PortA, kCLOCK_PortB, kCLOCK_PortC \
    }

/*! @brief Clock ip name array for LPADC. */
#define LPADC_CLOCKS  \
    {                 \
        kCLOCK_Lpadc0 \
    }

/*! @brief Clock ip name array for LPCMP. */
#define LPCMP_CLOCKS                 \
    {                                \
        kCLOCK_Lpcmp0, kCLOCK_Lpcmp1 \
    }

/*! @brief Clock ip name array for VREF. */
#define VREF_CLOCKS  \
    {                \
        kCLOCK_Vref0 \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                              \
    {                                            \
        kCLOCK_GpioA, kCLOCK_GpioB, kCLOCK_GpioC \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS  \
    {                \
        kCLOCK_Lpit0 \
    }

/*! @brief Clock ip name array for RF. */
#define RF_CLOCKS             \
    {                         \
        kCLOCK_Rf_2p4ghz_bist \
    }

/*! @brief Clock ip name array for WDOG. */
#define WDOG_CLOCKS                \
    {                              \
        kCLOCK_Wdog0, kCLOCK_Wdog1 \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS \
    {                  \
        kCLOCK_Can0    \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS  \
    {                  \
        kCLOCK_Flexio0 \
    }

/*! @brief Clock ip name array for TSTMR. */
#define TSTMR_CLOCKS  \
    {                 \
        kCLOCK_Tstmr0 \
    }

/*! @brief Clock ip name array for EWM. */
#define EWM_CLOCKS  \
    {               \
        kCLOCK_Ewm0 \
    }

/*! @brief Clock ip name array for SEMA42. */
#define SEMA42_CLOCKS \
    {                 \
        kCLOCK_Sema0  \
    }

/*! @brief Clock name used to get clock frequency.
 *
 * These clocks source would be generated from SCG module.
 */
typedef enum _clock_name
{
    /* ----------------------------- System layer clock -------------------------------*/
    kCLOCK_CoreSysClk, /*!< Cortex M33 clock. */
    kCLOCK_SlowClk,    /*!< SLOW_CLK with DIVSLOW. */
    kCLOCK_PlatClk,    /*!< PLAT_CLK. */
    kCLOCK_SysClk,     /*!< SYS_CLK. */
    kCLOCK_BusClk,     /*!< BUS_CLK with DIVBUS. */

    /* For SCG CLK intput */
    kCLOCK_ScgSysOscClk, /*!< SCG system OSC clock.                               */
    kCLOCK_ScgSircClk,   /*!< SCG SIRC clock.                                     */
    kCLOCK_ScgFircClk,   /*!< SCG FIRC clock.                                     */
    kCLOCK_RtcOscClk,    /*!< RTC OSC clock.                                      */
} clock_name_t;

/*!
 * @brief Clock source for peripherals that support various clock selections.
 *
 * These options are for MRCC->XX[CC]
 */
typedef enum _clock_ip_control
{
    kCLOCK_IpClkControl_fun0 = 0U, /*!< Peripheral clocks are disabled, module does not stall low power mode entry. */
    kCLOCK_IpClkControl_fun1 = 1U, /*!< Peripheral clocks are enabled, module does not stall low power mode entry. */
    kCLOCK_IpClkControl_fun2 = 2U, /*!< Peripherals clocks are enabled unless peripheral is idle, low power mode entry
                                      will stall until peripheral is idle. */
    kCLOCK_IpClkControl_fun3 =
        3U, /*!<  Peripheral clocks are enabled unless in SLEEP mode (or lower), low power mode entry will stall until
               peripheral is idle Peripheral functional clocks that remain enabled in SLEEP mode are enabled and do not
               stall low power mode entry unless entering DEEPSLEEP mode (or lower) */
} clock_ip_control_t;

/*!
 * @brief Clock source for peripherals that support various clock selections.
 *
 * These options are for MRCC->XX[MUX].
 */
typedef enum _clock_ip_src
{
    kCLOCK_IpSrcFro6M   = 2U, /*!< FRO 6M clock. */
    kCLOCK_IpSrcFro192M = 3U, /*!< FRO 192M clock. */
    kCLOCK_IpSrcSoscClk = 4U, /*!< OSC RF clock. */
    kCLOCK_IpSrc32kClk  = 5U, /*!< 32k Clk clock. */
} clock_ip_src_t;

/*!
 * @brief "IP Connector name difinition used for clock gate, clock source
 * and clock divider setting. It is defined as the corresponding register address.
 */
#define MAKE_MRCC_REGADDR(base, offset) ((base) + (offset))

#if defined(FSL_SDK_FORCE_CLK_DRIVER_NS_ACCESS) && FSL_SDK_FORCE_CLK_DRIVER_NS_ACCESS
#define CLOCK_REG(name) ((*(volatile uint32_t *)((uint32_t)(name) & ~0x10000000UL)))
#else
#define CLOCK_REG(name) (*(volatile uint32_t *)((uint32_t)(name)))
#endif

/*!
 * @brief Clock IP name.
 */
typedef enum _clock_ip_name
{
    kCLOCK_NOGATE          = 0U,                                  /*!< No clock gate for the IP in MRCC */
    kCLOCK_Ewm0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0x4C),  /*!< Clock ewm0 */
    kCLOCK_Syspm0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0x5C),  /*!< Clock syspm0 */
    kCLOCK_Wdog0           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x68),  /*!< Clock wdog0 */
    kCLOCK_Wdog1           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x6C),  /*!< Clock wdog1 */
    kCLOCK_Sfa0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0x74),  /*!< Clock sfa0 */
    kCLOCK_Crc0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0x8C),  /*!< Clock crc0 */
    kCLOCK_Secsubsys       = MAKE_MRCC_REGADDR(MRCC_BASE, 0x90),  /*!< Clock secsubsys */
    kCLOCK_Lpit0           = MAKE_MRCC_REGADDR(MRCC_BASE, 0xBC),  /*!< Clock lpit0 */
    kCLOCK_Tstmr0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0xC0),  /*!< Clock tstmr0 */
    kCLOCK_Tpm0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0xC4),  /*!< Clock tpm0 */
    kCLOCK_Tpm1            = MAKE_MRCC_REGADDR(MRCC_BASE, 0xC8),  /*!< Clock tpm1 */
    kCLOCK_Lpi2c0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0xCC),  /*!< Clock lpi2c0 */
    kCLOCK_Lpi2c1          = MAKE_MRCC_REGADDR(MRCC_BASE, 0xD0),  /*!< Clock lpi2c1 */
    kCLOCK_I3c0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0xD4),  /*!< Clock i3c */
    kCLOCK_Lpspi0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0xD8),  /*!< Clock lpspi0 */
    kCLOCK_Lpspi1          = MAKE_MRCC_REGADDR(MRCC_BASE, 0xDC),  /*!< Clock lpspi1 */
    kCLOCK_Lpuart0         = MAKE_MRCC_REGADDR(MRCC_BASE, 0xE0),  /*!< Clock lpuart0 */
    kCLOCK_Lpuart1         = MAKE_MRCC_REGADDR(MRCC_BASE, 0xE4),  /*!< Clock lpuart1 */
    kCLOCK_Flexio0         = MAKE_MRCC_REGADDR(MRCC_BASE, 0xE8),  /*!< Clock Flexio0 */
    kCLOCK_Can0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0xEC),  /*!< Clock Can0 */
    kCLOCK_Sema0           = MAKE_MRCC_REGADDR(MRCC_BASE, 0xFC),  /*!< Clock Sema0 */
    kCLOCK_Data_stream_2p4 = MAKE_MRCC_REGADDR(MRCC_BASE, 0x104), /*!< Clock data_stream_2p4 */
    kCLOCK_PortA           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x108), /*!< Clock portA */
    kCLOCK_PortB           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x10C), /*!< Clock portB */
    kCLOCK_PortC           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x110), /*!< Clock portC */
    kCLOCK_Lpadc0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0x11C), /*!< Clock lpadc0 */
    kCLOCK_Lpcmp0          = MAKE_MRCC_REGADDR(MRCC_BASE, 0x120), /*!< Clock lpcmp0 */
    kCLOCK_Lpcmp1          = MAKE_MRCC_REGADDR(MRCC_BASE, 0x124), /*!< Clock lpcmp1 */
    kCLOCK_Vref0           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x128), /*!< Clock verf0 */
    kCLOCK_Mtr_master      = MAKE_MRCC_REGADDR(MRCC_BASE, 0x134), /*!< Clock mtr_master */
    kCLOCK_GpioA           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x404), /*!< Clock gpioA */
    kCLOCK_GpioB           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x408), /*!< Clock gpioB */
    kCLOCK_GpioC           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x40C), /*!< Clock gpioC */
    kCLOCK_Dma0            = MAKE_MRCC_REGADDR(MRCC_BASE, 0x410), /*!< Clock dma0 */
    kCLOCK_Pflexnvm        = MAKE_MRCC_REGADDR(MRCC_BASE, 0x414), /*!< Clock pflexnvm */
    kCLOCK_Sram0           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x41C), /*!< Clock Sram0 */
    kCLOCK_Sram1           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x420), /*!< Clock Sram1 */
    kCLOCK_Sram2           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x424), /*!< Clock Sram2 */
    kCLOCK_Sram3           = MAKE_MRCC_REGADDR(MRCC_BASE, 0x428), /*!< Clock Sram3 */
    kCLOCK_Rf_2p4ghz_bist  = MAKE_MRCC_REGADDR(MRCC_BASE, 0x42C), /*!< Clock rf_2p4ghz_bist */
} clock_ip_name_t;

/*!
 * @brief SCG status return codes.
 */
enum _scg_status
{
    kStatus_SCG_Busy       = MAKE_STATUS(kStatusGroup_SCG, 1), /*!< Clock is busy.  */
    kStatus_SCG_InvalidSrc = MAKE_STATUS(kStatusGroup_SCG, 2)  /*!< Invalid source. */
};

/*!
 * @brief SCG system clock type.
 */
typedef enum _scg_sys_clk
{
    kSCG_SysClkSlow,     /*!< System slow clock. */
    kSCG_SysClkBus,      /*!< Bus clock.         */
    kSCG_SysClkPlatform, /*!< Platform clock.    */
    kSCG_SysClkCore,     /*!< Core clock.        */
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
    uint32_t : 8;         /*!< Reserved. */
    uint32_t divCore : 4; /*!< Core clock divider, see @ref scg_sys_clk_div_t. */
    uint32_t : 4;         /*!< Reserved. */
    uint32_t src : 3;     /*!< System clock source, see @ref scg_sys_clk_src_t. */
    uint32_t : 5;         /*!< reserved. */
} scg_sys_clk_config_t;

/*!
 * @brief SCG clock out configuration (CLKOUTSEL).
 */
typedef enum _clock_clkout_src
{
    kClockClkoutSelScgSlow   = 0U, /*!< SCG Slow clock. */
    kClockClkoutSelSosc      = 1U, /*!< System OSC.     */
    kClockClkoutSelSirc      = 2U, /*!< Slow IRC.       */
    kClockClkoutSelFirc      = 3U, /*!< Fast IRC.       */
    kClockClkoutSelScgRtcOsc = 4U, /*!< SCG RTC OSC clock. */
} clock_clkout_src_t;

/*!
 * @brief SCG system OSC monitor mode.
 */
typedef enum _scg_sosc_monitor_mode
{
    kSCG_SysOscMonitorDisable = 0U,                      /*!< Monitor disabled. */
    kSCG_SysOscMonitorInt     = SCG_SOSCCSR_SOSCCM_MASK, /*!< Interrupt when the SOSC error is detected. */
    kSCG_SysOscMonitorReset =
        SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK /*!< Reset when the SOSC error is detected.     */
} scg_sosc_monitor_mode_t;

/*! @brief SOSC enable mode. */
enum
{
    kSCG_SoscDisable       = 0,                         /*!< Disable SOSC clock.             */
    kSCG_SoscEnable        = SCG_SOSCCSR_SOSCEN_MASK,   /*!< Enable SOSC clock.              */
    kSCG_SoscEnableInSleep = SCG_SOSCCSR_SOSCSTEN_MASK, /*!< Enable SOSC in sleep mode.      */
};

/*!
 * @brief SCG system OSC configuration.
 */
typedef struct _scg_sosc_config
{
    uint32_t freq;                       /*!< System OSC frequency. */
    uint32_t enableMode;                 /*!< Enable mode, OR'ed value of _scg_sosc_enable_mode.  */
    scg_sosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.     */
} scg_sosc_config_t;

/*!
 * @brief SCG ROSC monitor mode.
 */
typedef enum _scg_rosc_monitor_mode
{
    kSCG_RoscMonitorDisable = 0U,                      /*!< Monitor disabled. */
    kSCG_RoscMonitorInt     = SCG_ROSCCSR_ROSCCM_MASK, /*!< Interrupt when the RTC OSC error is detected. */
    kSCG_RoscMonitorReset =
        SCG_ROSCCSR_ROSCCM_MASK | SCG_ROSCCSR_ROSCCMRE_MASK /*!< Reset when the RTC OSC error is detected. */
} scg_rosc_monitor_mode_t;

/*!
 * @brief SCG ROSC configuration.
 */
typedef struct _scg_rosc_config
{
    scg_rosc_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.     */
} scg_rosc_config_t;

/*! @brief SIRC enable mode. */
typedef enum _scg_sirc_enable_mode
{
    kSCG_SircDisableInSleep = 0,                         /*!< Disable SIRC clock.             */
    kSCG_SircEnableInSleep  = SCG_SIRCCSR_SIRCSTEN_MASK, /*!< Enable SIRC in sleep mode.      */
} scg_sirc_enable_mode_t;

/*!
 * @brief SCG slow IRC clock configuration.
 */
typedef struct _scg_sirc_config
{
    scg_sirc_enable_mode_t enableMode; /*!< Enable mode, OR'ed value of _scg_sirc_enable_mode. */
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
 * @brief SCG fast IRC trim source.
 */
typedef enum _scg_firc_trim_src
{
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
    uint16_t trimDiv;              /*!< Divider of SOSC for FIRC.             */

    uint8_t trimCoar; /*!< Trim coarse value; Irrelevant if trimMode is kSCG_FircTrimUpdate. */
    uint8_t trimFine; /*!< Trim fine value; Irrelevant if trimMode is kSCG_FircTrimUpdate. */
} scg_firc_trim_config_t;

/*! @brief FIRC enable mode. */
enum
{
    kSCG_FircDisable       = 0,                         /*!< Disable FIRC clock.             */
    kSCG_FircEnable        = SCG_FIRCCSR_FIRCEN_MASK,   /*!< Enable FIRC clock.              */
    kSCG_FircEnableInSleep = SCG_FIRCCSR_FIRCSTEN_MASK, /*!< Enable FIRC in sleep mode.      */
};

/*!
 * @brief SCG fast IRC clock frequency range.
 */
typedef enum _scg_firc_range
{
    kSCG_FircRange48M,  /*!< Fast IRC is trimmed to 48 MHz. */
    kSCG_FircRange64M,  /*!< Fast IRC is trimmed to 64 MHz. */
    kSCG_FircRange96M,  /*!< Fast IRC is trimmed to 96 MHz. */
    kSCG_FircRange192M, /*!< Fast IRC is trimmed to 192 MHz. */
} scg_firc_range_t;

/*!
 * @brief SCG fast IRC clock configuration.
 */
typedef struct _scg_firc_config_t
{
    uint32_t enableMode;    /*!< Enable mode. */
    scg_firc_range_t range; /*!< Fast IRC frequency range. */

    const scg_firc_trim_config_t *trimConfig; /*!< Pointer to the FIRC trim configuration; set NULL to disable trim. */
} scg_firc_config_t;

/*!
 * @brief FRO192M RF clock frequency range.
 */
typedef enum _fro192m_rf_range
{
    kFro192M_Range16M, /*!< FRO192M output frequenc 16 MHz. */
    kFro192M_Range24M, /*!< FRO192M output frequenc 24 MHz. */
    kFro192M_Range32M, /*!< FRO192M output frequenc 32 MHz. */
    kFro192M_Range48M, /*!< FRO192M output frequenc 48 MHz. */
    kFro192M_Range64M, /*!< FRO192M output frequenc 64 MHz. */
} fro192m_rf_range_t;

/*!
 * @brief RF Flash APB and RF_CMC clock divide.
 */
typedef enum _fro192m_rf_clk_div
{
    kFro192M_ClkDivBy1 = 0U, /*!< Divided by 1. */
    kFro192M_ClkDivBy2 = 1U, /*!< Divided by 2. */
    kFro192M_ClkDivBy4 = 2U, /*!< Divided by 4. */
    kFro192M_ClkDivBy8 = 3U, /*!< Divided by 8. */
} fro192m_rf_clk_div_t;

/*!
 * @brief FRO192M RF clock configuration.
 */
typedef struct _fro192m_rf_clk_config
{
    fro192m_rf_range_t range;           /*!< FRO192M RF clock frequency range. */
    fro192m_rf_clk_div_t apb_rfcmc_div; /*!< RF Flash APB and RF_CMC clock divide. */
} fro192m_rf_clk_config_t;

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
    if (kCLOCK_NOGATE == name)
    {
        return;
    }

    uint32_t reg = CLOCK_REG(name);

    if (0x0u != (reg & MRCC_CC_MASK))
    {
        return;
    }

    CLOCK_REG(name) &= (~MRCC_CC_MASK);
    CLOCK_REG(name) |= (MRCC_CC_MASK & (uint32_t)kCLOCK_IpClkControl_fun1);

    if ((CLOCK_REG(name) & MRCC_PR_MASK) == MRCC_PR_MASK)
    {
        CLOCK_REG(name) |= MRCC_RSTB_MASK;
    }

    /* Make sure enable clock finished */
    __ISB();
    __DSB();
}

/*!
 * @brief Enable the clock for specific IP in low power mode.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 * @param control  Clock Config, see \ref clock_ip_control_t.
 */
static inline void CLOCK_EnableClockLPMode(clock_ip_name_t name, clock_ip_control_t control)
{
    if (kCLOCK_NOGATE == name)
    {
        return;
    }

    assert(kCLOCK_IpClkControl_fun1 == control || kCLOCK_IpClkControl_fun2 == control ||
           kCLOCK_IpClkControl_fun3 == control);

    CLOCK_REG(name) &= (~MRCC_CC_MASK);
    CLOCK_REG(name) |= (MRCC_CC_MASK & (uint32_t)control);

    if ((CLOCK_REG(name) & MRCC_PR_MASK) == MRCC_PR_MASK)
    {
        CLOCK_REG(name) |= MRCC_RSTB_MASK;
    }

    /* Make sure enable clock finished */
    __ISB();
    __DSB();
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    if (kCLOCK_NOGATE == name)
    {
        return;
    }

    CLOCK_REG(name) &= (uint32_t)kCLOCK_IpClkControl_fun0;

    if ((CLOCK_REG(name) & MRCC_PR_MASK) == MRCC_PR_MASK)
    {
        CLOCK_REG(name) &= ~MRCC_RSTB_MASK;
    }
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
    if (kCLOCK_NOGATE == name)
    {
        return;
    }

    uint32_t reg = CLOCK_REG(name);

    assert(reg & MRCC_PR_MASK);

    reg = (reg & (~MRCC_MUX_MASK)) | MRCC_MUX(src);

    /*
     * If clock is already enabled, first disable it, then set the clock
     * source and re-enable it.
     */
    CLOCK_REG(name) = reg & (~MRCC_CC_MASK);
    CLOCK_REG(name) = reg;
}

/*!
 * @brief Set the clock source and divider for specific IP module.
 *
 * Set the clock source and divider for specific IP, not all modules need to
 * set the clock source and divider, should only use this function for the
 * modules need source and divider setting.
 *
 * Divider output clock = Divider input clock / (divValue+1)]).
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param divValue  The divider value.
 */
static inline void CLOCK_SetIpSrcDiv(clock_ip_name_t name, uint8_t divValue)
{
    if (kCLOCK_NOGATE == name)
    {
        return;
    }

    uint32_t reg = CLOCK_REG(name);

    assert(reg & MRCC_PR_MASK);

    reg = (reg & (~MRCC_DIV_MASK)) | MRCC_DIV(divValue);

    /*
     * If clock is already enabled, first disable it, then set the clock
     * source and re-enable it.
     */
    CLOCK_REG(name) = reg & (~MRCC_CC_MASK);
    CLOCK_REG(name) = reg;
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
 * @brief Gets the functional clock frequency for a specific IP module.
 *
 * This function gets the IP module's functional clock frequency based on MRCC
 * registers. It is only used for the IP modules which could select clock source
 * by MRCC[PCS].
 *
 * @param name Which peripheral to get, see \ref clock_ip_name_t.
 * @return Clock frequency value in Hz
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
        scg_sys_clk_config_t config;
        uint32_t u32;
    } scgSysClkConfig;

    scgSysClkConfig.config = *config;
    CLOCK_REG(&SCG0->RCCR) = scgSysClkConfig.u32;
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
        scg_sys_clk_config_t config;
        uint32_t u32;
    } scgSysClkConfig;

    scgSysClkConfig.u32 = CLOCK_REG(&SCG0->CSR);
    *config             = scgSysClkConfig.config;
}

/*!
 * @brief Sets the clock out selection.
 *
 * This function sets the clock out selection (CLKOUTSEL).
 *
 * @param setting The selection to set.
 */
static inline void CLOCK_SetClkOutSel(clock_clkout_src_t setting)
{
    CLOCK_REG(&SCG0->CLKOUTCNFG) = SCG_CLKOUTCNFG_CLKOUTSEL(setting);
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
 * @brief Gets the SCG system OSC clock frequency (SYSOSC).
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void);

/*!
 * @brief Checks whether the system OSC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsSysOscErr(void)
{
    return (bool)(CLOCK_REG(&SCG0->SOSCCSR) & SCG_SOSCCSR_SOSCERR_MASK);
}

/*!
 * @brief Clears the system OSC clock error.
 */
static inline void CLOCK_ClearSysOscErr(void)
{
    CLOCK_REG(&SCG0->SOSCCSR) |= SCG_SOSCCSR_SOSCERR_MASK;
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
    uint32_t reg = CLOCK_REG(&SCG0->SOSCCSR);

    reg &= ~(SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK);

    reg |= (uint32_t)mode;

    CLOCK_REG(&SCG0->SOSCCSR) = reg;
}

/*!
 * @brief Checks whether the system OSC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsSysOscValid(void)
{
    return (bool)(CLOCK_REG(&SCG0->SOSCCSR) & SCG_SOSCCSR_SOSCVLD_MASK);
}

/*!
 * @brief Unlock the SOSCCSR control status register.
 */
static inline void CLOCK_UnlockSysOscControlStatusReg(void)
{
    CLOCK_REG(&SCG0->SOSCCSR) &= ~(SCG_SOSCCSR_LK_MASK);
}

/*!
 * @brief Lock the SOSCCSR control status register.
 */
static inline void CLOCK_LockSysOscControlStatusReg(void)
{
    CLOCK_REG(&SCG0->SOSCCSR) |= SCG_SOSCCSR_LK_MASK;
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
 * @brief Gets the SCG SIRC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircFreq(void);

/*!
 * @brief Checks whether the SIRC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsSircValid(void)
{
    return (bool)(CLOCK_REG(&SCG0->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK);
}

/*!
 * @brief Unlock the SIRCCSR control status register.
 */
static inline void CLOCK_UnlockSircControlStatusReg(void)
{
    CLOCK_REG(&SCG0->SIRCCSR) &= ~(SCG_SIRCCSR_LK_MASK);
}

/*!
 * @brief Lock the SIRCCSR control status register.
 */
static inline void CLOCK_LockSircControlStatusReg(void)
{
    CLOCK_REG(&SCG0->SIRCCSR) |= SCG_SIRCCSR_LK_MASK;
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
 * @brief Gets the SCG FIRC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircFreq(void);

/*!
 * @brief Checks whether the FIRC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsFircErr(void)
{
    return (bool)(CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCERR_MASK);
}

/*!
 * @brief Clears the FIRC clock error.
 */
static inline void CLOCK_ClearFircErr(void)
{
    CLOCK_REG(&SCG0->FIRCCSR) |= SCG_FIRCCSR_FIRCERR_MASK;
}

/*!
 * @brief Checks whether the FIRC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsFircValid(void)
{
    return (bool)(CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCVLD_MASK);
}

/*!
 * @brief Unlock the FIRCCSR control status register.
 */
static inline void CLOCK_UnlockFircControlStatusReg(void)
{
    CLOCK_REG(&SCG0->FIRCCSR) &= ~(SCG_FIRCCSR_LK_MASK);
}

/*!
 * @brief Lock the FIRCCSR control status register.
 */
static inline void CLOCK_LockFircControlStatusReg(void)
{
    CLOCK_REG(&SCG0->FIRCCSR) |= SCG_FIRCCSR_LK_MASK;
}

/*!
 * brief Initializes the SCG ROSC.
 *
 * This function enables the SCG ROSC clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success ROSC is initialized.
 * retval kStatus_SCG_Busy ROSC has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly ROSC control register is locked.
 *
 * note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitRosc(const scg_rosc_config_t *config);

/*!
 * brief De-initializes the SCG ROSC.
 *
 * This function disables the SCG ROSC clock.
 *
 * retval kStatus_Success System OSC is deinitialized.
 * retval kStatus_SCG_Busy System OSC is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the ROSC is used by an IP.
 */
status_t CLOCK_DeinitRosc(void);

/*!
 * @brief Gets the SCG RTC OSC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void);

/*!
 * @brief Initializes the FRO192M clock for the Radio Mode Controller.
 *
 * This function configure the RF FRO192M clock according to the configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success RF FRO192M is configured.
 */
status_t CLOCK_InitRfFro192M(const fro192m_rf_clk_config_t *config);

/*!
 * @brief Gets the FRO192M clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRfFro192MFreq(void);

/*!
 * @brief Checks whether the ROSC clock error occurs.
 *
 * @return  True if the error occurs, false if not.
 */
static inline bool CLOCK_IsRoscErr(void)
{
    return (bool)(CLOCK_REG(&SCG0->ROSCCSR) & SCG_ROSCCSR_ROSCERR_MASK);
}

/*!
 * @brief Clears the ROSC clock error.
 */
static inline void CLOCK_ClearRoscErr(void)
{
    CLOCK_REG(&SCG0->ROSCCSR) |= SCG_ROSCCSR_ROSCERR_MASK;
}

/*!
 * @brief Sets the ROSC monitor mode.
 *
 * This function sets the ROSC monitor mode. The mode can be disabled,
 * it can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
static inline void CLOCK_SetRoscMonitorMode(scg_rosc_monitor_mode_t mode)
{
    uint32_t reg = CLOCK_REG(&SCG0->ROSCCSR);

    reg &= ~(SCG_ROSCCSR_ROSCCM_MASK | SCG_ROSCCSR_ROSCCMRE_MASK);

    reg |= (uint32_t)mode;

    CLOCK_REG(&SCG0->ROSCCSR) = reg;
}

/*!
 * @brief Checks whether the ROSC clock is valid.
 *
 * @return  True if clock is valid, false if not.
 */
static inline bool CLOCK_IsRoscValid(void)
{
    return (bool)(CLOCK_REG(&SCG0->ROSCCSR) & SCG_ROSCCSR_ROSCVLD_MASK);
}

/*!
 * @brief Unlock the ROSCCSR control status register.
 */
static inline void CLOCK_UnlockRoscControlStatusReg(void)
{
    CLOCK_REG(&SCG0->ROSCCSR) &= ~(SCG_ROSCCSR_LK_MASK);
}

/*!
 * @brief Lock the ROSCCSR control status register.
 */
static inline void CLOCK_LockRoscControlStatusReg(void)
{
    CLOCK_REG(&SCG0->ROSCCSR) |= SCG_ROSCCSR_LK_MASK;
}

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

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
