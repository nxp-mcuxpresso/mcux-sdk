/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PM_DEVICE_H_
#define _FSL_PM_DEVICE_H_

#include "fsl_common.h"

#include "fsl_pm_config.h"

/*!
 * @addtogroup PM Framework: Power Manager Framework
 * @brief This section includes Power Mode macros, System Constraints macros, and Wakeup source macros.
 * @{
 */

/*!
 * @name Power Mode Definition
 * @{
 */
#define PM_LP_STATE_SP0  (0U)  /*!< Low power state 0, setpoint 0. */
#define PM_LP_STATE_SP1  (1U)  /*!< Low power state 1, setpoint 1. */
#define PM_LP_STATE_SP2  (2U)  /*!< Low power state 2, setpoint 2. */
#define PM_LP_STATE_SP3  (3U)  /*!< Low power state 3, setpoint 3. */
#define PM_LP_STATE_SP4  (4U)  /*!< Low power state 4, setpoint 4. */
#define PM_LP_STATE_SP5  (5U)  /*!< Low power state 5, setpoint 5. */
#define PM_LP_STATE_SP6  (6U)  /*!< Low power state 6, setpoint 6. */
#define PM_LP_STATE_SP7  (7U)  /*!< Low power state 7, setpoint 7. */
#define PM_LP_STATE_SP8  (8U)  /*!< Low power state 8, setpoint 8. */
#define PM_LP_STATE_SP9  (9U)  /*!< Low power state 9, setpoint 9. */
#define PM_LP_STATE_SP10 (10U) /*!< Low power state 10, setpoint 10. */
#define PM_LP_STATE_SP11 (11U) /*!< Low power state 11, setpoint 11. */
#define PM_LP_STATE_SP12 (12U) /*!< Low power state 12, setpoint 12. */
#define PM_LP_STATE_SP13 (13U) /*!< Low power state 13, setpoint 13. */
#define PM_LP_STATE_SP14 (14U) /*!< Low power state 14, setpoint 14. */
#define PM_LP_STATE_SP15 (15U) /*!< Low power state 15, setpoint 15. */
#define PM_LP_STATE_SNVS (16U) /*!< Low power state 16, SNVS. */

#define PM_LP_STATE_NO_CONSTRAINT (0xFFU)

/*! @} */

/*!
 * @brief List  of system basic resources that controlled by PM.
 */
enum _resc_name
{
    /* Controlled by GPC_CMC. */
    kResc_CPU_PLATFORM = 0U, /*!< CPU platform, this resource is suitable for CM7 and CM4. */

    /* Controlled by CCM. */
    kResc_OSC_RC_16M      = 1U,  /*!< Clock Source: 16MHz RC OSC output. */
    kResc_OSC_RC_48M      = 2U,  /*!< Clock Source: 48MHz RC OSC output. */
    kResc_OSC_RC_48M_DIV2 = 3U,  /*!< Clock Source: 48MHz divided by 2 clock output. */
    kResc_OSC_RC_400M     = 4U,  /*!< Clock Source: 400MHz RC OSC output. */
    kResc_OSC_24M         = 5U,  /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_OSC_24M_CLK     = 6U,  /*!< Clock Source: 24MHz main output clock. */
    kResc_ARM_PLL         = 7U,  /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_ARM_PLL_CLK     = 8U,  /*!< Clock Source: ARM PLL main output clock. */
    kResc_SYS_PLL2        = 9U,  /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_SYS_PLL2_CLK    = 10U, /*!< Clock Source: System PLL2 main output clock. */
    kResc_SYS_PLL2_PFD0   = 11U, /*!< Clock Source: System PLL2 PFD0 clock. */
    kResc_SYS_PLL2_PFD1   = 12U, /*!< Clock Source: System PLL2 PFD1 clock. */
    kResc_SYS_PLL2_PFD2   = 13U, /*!< Clock Source: System PLL2 PFD2 clock. */
    kResc_SYS_PLL2_PFD3   = 14U, /*!< Clock Source: System PLL2 PFD3 clock. */
    kResc_SYS_PLL3        = 15U, /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_SYS_PLL3_CLK    = 16U, /*!< Clock Source: System PLL3 main output */
    kResc_SYS_PLL3_DIV2   = 17U, /*!< Clock Source: System PLL3 divided by 2 clock. */
    kResc_SYS_PLL3_PFD0   = 18U, /*!< Clock Source: System PLL3 PFD0 clock. */
    kResc_SYS_PLL3_PFD1   = 19U, /*!< Clock Source: System PLL3 PFD1 clock. */
    kResc_SYS_PLL3_PFD2   = 20U, /*!< Clock Source: System PLL3 PFD2 clock. */
    kResc_SYS_PLL3_PFD3   = 21U, /*!< Clock Source: System PLL3 PFD3 clock. */
    kResc_SYS_PLL1        = 22U, /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_SYS_PLL1_CLK    = 23U, /*!< Clock Source: System PLL1 main clock output. */
    kResc_SYS_PLL1_DIV2   = 24U, /*!< Clock Source: System PLL1 divided by 2 clock. */
    kResc_SYS_PLL1_DIV5   = 25U, /*!< Clock Source: System PLL1 divided by 5 clock. */
    kResc_AUDIO_PLL       = 26U, /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_AUDIO_PLL_CLK   = 27U, /*!< Clock Source: Audio PLL main clock output. */
    kResc_VIDEO_PLL       = 28U, /*!< Clock Source: VCO, not connect to the clock tree. */
    kResc_VIDEO_PLL_CLK   = 29U, /*!< Clock Source: Video PLL main clock outout. */

    /* Controlled by PGMC_BPC. */
    kResc_MEGA_MIX    = 30U, /*!< Power Domain: MEGA. */
    kResc_DISPLAY_MIX = 31U, /*!< Power Domain: Display. */
    kResc_WAKEUP_MIX  = 32U, /*!< Power Domain: Wakeup. */
    kResc_LPSR_MIX    = 33U, /*!< Power Domain: LPSR. */

    /* Controlled by PMU.  */
    kResc_DCDC         = 34U, /*!< Power supply: DCDC. */
    kResc_LPSR_ANA_LDO = 35U, /*!< Power supply: LPSR ANA LDO. */
    kResc_LPSR_DIG_LDO = 36U, /*!< Power supply: LPSR DIG LDO. */
    kResc_BANDGAP      = 37U, /*!< Internal bandgap. */
    kResc_FBB_M7       = 38U, /*!< Forward body biasing for CM7 platform. */
    kResc_RBB_SOC      = 39U, /*!< Reverse body biasing for Soc
                                  Power domains(MEGA, DISPLAY, WAKEUP, CM7). */
    kResc_RBB_LPSR = 40U,     /*!< Reverse body biasing for LPSR power domain. */

    /* Controlled by GPC_SBC. */
    kResc_STBY_REQ = 41U, /*!< Standby request. */

    kResc_PLL_LDO = 42U,  /*!< Power supply: PLL LDO. */
};

/*!
 * @name System basic resource constraints definitions.
 * @{
 */

/*!
 * @brief Resource constraints definition of CPU platform (suitable for CM7 and CM4 processors), with support for four
 * modes:
 *   1. The CPU domain is in run mode, core is active and cache, TCM, and peripherals inside the CPU platform can be
 * accessed when needed, as specified in @ref PM_CORE_DOMAIN_RUN;
 *   2. The CPU domain is in wait mode, clocks to the CPU core and cache are gated off, as specified in @ref
 * PM_CORE_DOMAIN_WAIT;
 *   3. The CPU domain is in stop mode, clocks to the CPU core, cache, and TCM are gated off, as specified in @ref
 * PM_CORE_DOMAIN_STOP;
 *   4. The CPU platform is powered off, as specified in @ref PM_CORE_DOMAIN_SUSPEND.
 */
#define PM_RESC_CORE_DOMAIN_RUN     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_CPU_PLATFORM)
#define PM_RESC_CORE_DOMAIN_WAIT    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_CPU_PLATFORM)
#define PM_RESC_CORE_DOMAIN_STOP    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON2, kResc_CPU_PLATFORM)
#define PM_RESC_CORE_DOMAIN_SUSPEND PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_CPU_PLATFORM)

/*!
 * @brief Resource constraints definition of OSC_RC_16M, with support for 2 modes:
 *    1. OSC_RC_16M is disabled in low power state, as specified in @ref PM_OSC_RC_16M_OFF;
 *    2. OSC_RC_16M is enabled in low power state, as specificed in @ref PM_OSC_RC_16M_ON.
 */
#define PM_RESC_OSC_RC_16M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_RC_16M)
#define PM_RESC_OSC_RC_16M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_RC_16M)

/*!
 * @brief Resource constraints definition of OSC_RC_48M, with support for 2 modes:
 *    1. OSC_RC_48M is disabled in low power state, as specified in @ref PM_OSC_RC_48M_OFF;
 *    2. OSC_RC_48M is enabled in low power state, as specified in @ref PM_OSC_RC_48M_ON.
 */
#define PM_RESC_OSC_RC_48M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_RC_48M)
#define PM_RESC_OSC_RC_48M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_RC_48M)

/*!
 * @brief Resource constraints definition of OSC_RC_48M_DIV2, with support for 2 modes:
 *    1. OSC_RC_48M_DIV2 is disabled in low power state, as specified in @ref PM_OSC_RC_48M_DIV2_OFF;
 *    2. OSC_RC_48M_DIV2 is enabled in low power state, as specified in @ref PM_OSC_RC_48M_DIV2_ON.
 */
#define PM_RESC_OSC_RC_48M_DIV2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_RC_48M_DIV2)
#define PM_RESC_OSC_RC_48M_DIV2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_RC_48M_DIV2)

/*!
 * @brief Resource constraints definition of OSC_RC_400M, with support for 2 modes:
 *    1. OSC_RC_400M is disabled in low power state, as specified in @ref PM_OSC_RC_400M_OFF;
 *    2. OSC_RC_400M is enabled in low power state, as specified in @ref PM_OSC_RC_400M_ON.
 */
#define PM_RESC_OSC_RC_400M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_RC_400M)
#define PM_RESC_OSC_RC_400M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_RC_400M)

/*!
 * @brief Resource constraints definition of OSC_RC_24M, with support for 2 modes:
 *    1. OSC_RC_24M is disabled in low power state, as specified in @ref PM_OSC_RC_24M_OFF;
 *    2. OSC_RC_24M is enabled in low power state, as specified in @ref PM_OSC_RC_24M_ON.
 */
#define PM_RESC_OSC_RC_24M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_24M)
#define PM_RESC_OSC_RC_24M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_24M)

/*!
 * @brief Resource constraints definition of OSC_RC_24M_CLK, with support for 2 modes:
 *    1. OSC_RC_24M_CLK is disabled in low power state, as specified in @ref PM_OSC_RC_24M_CLK_OFF;
 *    2. OSC_RC_24M_CLK is enabled in low power state, as specified in @ref PM_OSC_RC_24M_CLK_ON.
 */
#define PM_RESC_OSC_RC_24M_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_24M_CLK)
#define PM_RESC_OSC_RC_24M_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_24M_CLK)

/*!
 * @brief Resource constraints definition of ARM_PLL, with support for 2 modes:
 *    1. ARM_PLL is disabled in low power state, as specified in @ref PM_ARM_PLL_OFF;
 *    2. ARM_PLL is enabled in low power state, as specified in @ref PM_ARM_PLL_ON.
 */
#define PM_RESC_ARM_PLL_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ARM_PLL)
#define PM_RESC_ARM_PLL_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_ARM_PLL)

/*!
 * @brief Resource constraints definition of ARM_PLL_CLK, with support for 2 modes:
 *    1. ARM_PLL_CLK is disabled in low power state, as specified in @ref PM_ARM_PLL_CLK_OFF;
 *    2. ARM_PLL_CLK is enabled in low power state, as specified in @ref PM_ARM_PLL_CLK_ON.
 */
#define PM_RESC_ARM_PLL_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ARM_PLL_CLK)
#define PM_RESC_ARM_PLL_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_ARM_PLL_CLK)

/*!
 * @brief Resource constraints definition of SYS_PLL2, with support for 2 modes:
 *    1. SYS_PLL2 is disabled in low power state, as specified in @ref PM_SYS_PLL2_OFF;
 *    2. SYS_PLL2 is enabled in low power state, as specified in @ref PM_SYS_PLL2_ON.
 */
#define PM_RESC_SYS_PLL2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2)
#define PM_RESC_SYS_PLL2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2)

/*!
 * @brief Resource constraints definition of SYS_PLL2_CLK, with support for 2 modes:
 *    1. SYS_PLL2_CLK is disabled in low power state, as specified in @ref PM_SYS_PLL2_CLK_OFF;
 *    2. SYS_PLL2_CLK is enabled in low power state, as specified in @ref PM_SYS_PLL2_CLK_ON.
 */
#define PM_RESC_SYS_PLL2_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2_CLK)
#define PM_RESC_SYS_PLL2_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2_CLK)

/*!
 * @brief Resource constraints definition of SYS_PLL2_PFD0, with support for 2 modes:
 *    1. SYS_PLL2_PFD0 is disabled in low power state, as specified in @ref PM_SYS_PLL2_PFD0_OFF;
 *    2. SYS_PLL2_PFD0 is enabled in low power state, as specified in @ref PM_SYS_PLL2_PFD0_ON.
 */
#define PM_RESC_SYS_PLL2_PFD0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2_PFD0)
#define PM_RESC_SYS_PLL2_PFD0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2_PFD0)

/*!
 * @brief Resource constraints definition of SYS_PLL2_PFD1, with support for 2 modes:
 *    1. SYS_PLL2_PFD1 is disabled in low power state, as specified in @ref PM_SYS_PLL2_PFD1_OFF;
 *    2. SYS_PLL2_PFD1 is enabled in low power state, as specified in @ref PM_SYS_PLL2_PFD1_ON.
 */
#define PM_RESC_SYS_PLL2_PFD1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2_PFD1)
#define PM_RESC_SYS_PLL2_PFD1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2_PFD1)

/*!
 * @brief Resource constraints definition of SYS_PLL2_PFD2, with support for 2 modes:
 *    1. SYS_PLL2_PFD2 is disabled in low power state, as specified in @ref PM_SYS_PLL2_PFD2_OFF;
 *    2. SYS_PLL2_PFD2 is enabled in low power state, as specified in @ref PM_SYS_PLL2_PFD2_ON.
 */
#define PM_RESC_SYS_PLL2_PFD2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2_PFD2)
#define PM_RESC_SYS_PLL2_PFD2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2_PFD2)

/*!
 * @brief Resource constraints definition of SYS_PLL2_PFD3, with support for 2 modes:
 *    1. SYS_PLL2_PFD3 is disabled in low power state, as specified in @ref PM_SYS_PLL2_PFD3_OFF;
 *    2. SYS_PLL2_PFD3 is enabled in low power state, as specified in @ref PM_SYS_PLL2_PFD3_ON.
 */
#define PM_RESC_SYS_PLL2_PFD3_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL2_PFD3)
#define PM_RESC_SYS_PLL2_PFD3_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL2_PFD3)

/*!
 * @brief Resource constraints definition of SYS_PLL3, with support for 2 modes:
 *    1. SYS_PLL3 is disabled in low power state, as specified in @ref PM_SYS_PLL3_OFF;
 *    2. SYS_PLL3 is enabled in low power state, as specified in @ref PM_SYS_PLL3_ON.
 */
#define PM_RESC_SYS_PLL3_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3)
#define PM_RESC_SYS_PLL3_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3)

/*!
 * @brief Resource constraints definition of SYS_PLL3_CLK, with support for 2 modes:
 *    1. SYS_PLL3_CLK is disabled in low power state, as specified in @ref PM_SYS_PLL3_CLK_OFF;
 *    2. SYS_PLL3_CLK is enabled in low power state, as specified in @ref PM_SYS_PLL3_CLK_ON.
 */
#define PM_RESC_SYS_PLL3_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_CLK)
#define PM_RESC_SYS_PLL3_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_CLK)

/*!
 * @brief Resource constraints definition of SYS_PLL3_DVI2, with support for 2 modes:
 *    1. SYS_PLL3_DVI2 is disabled in low power state, as specified in @ref PM_SYS_PLL3_DVI2_OFF;
 *    2. SYS_PLL3_DVI2 is enabled in low power state, as specified in @ref PM_SYS_PLL3_DVI2_ON.
 */
#define PM_RESC_SYS_PLL3_DVI2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_DIV2)
#define PM_RESC_SYS_PLL3_DVI2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_DIV2)

/*!
 * @brief Resource constraints definition of SYS_PLL3_PFD0, with support for 2 modes:
 *    1. SYS_PLL3_PFD0 is disabled in low power state, as specified in @ref PM_SYS_PLL3_PFD0_OFF;
 *    2. SYS_PLL3_PFD0 is enabled in low power state, as specified in @ref PM_SYS_PLL3_PFD0_ON.
 */
#define PM_RESC_SYS_PLL3_PFD0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_PFD0)
#define PM_RESC_SYS_PLL3_PFD0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_PFD0)

/*!
 * @brief Resource constraints definition of SYS_PLL3_PFD1, with support for 2 modes:
 *    1. SYS_PLL3_PFD1 is disabled in low power state, as specified in @ref PM_SYS_PLL3_PFD1_OFF;
 *    2. SYS_PLL3_PFD1 is enabled in low power state, as specified in @ref PM_SYS_PLL3_PFD1_ON.
 */
#define PM_RESC_SYS_PLL3_PFD1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_PFD1)
#define PM_RESC_SYS_PLL3_PFD1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_PFD1)

/*!
 * @brief Resource constraints definition of SYS_PLL3_PFD2, with support for 2 modes:
 *    1. SYS_PLL3_PFD2 is disabled in low power state, as specified in @ref PM_SYS_PLL3_PFD2_OFF;
 *    2. SYS_PLL3_PFD2 is enabled in low power state, as specified in @ref PM_SYS_PLL3_PFD2_ON.
 */
#define PM_RESC_SYS_PLL3_PFD2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_PFD2)
#define PM_RESC_SYS_PLL3_PFD2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_PFD2)

/*!
 * @brief Resource constraints definition of SYS_PLL3_PFD3, with support for 2 modes:
 *    1. SYS_PLL3_PFD3 is disabled in low power state, as specified in @ref PM_SYS_PLL3_PFD3_OFF;
 *    2. SYS_PLL3_PFD3 is enabled in low power state, as specified in @ref PM_SYS_PLL3_PFD3_ON.
 */
#define PM_RESC_SYS_PLL3_PFD3_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL3_PFD3)
#define PM_RESC_SYS_PLL3_PFD3_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL3_PFD3)

/*!
 * @brief Resource constraints definition of SYS_PLL1, with support for 2 modes:
 *    1. SYS_PLL1 is disabled in low power state, as specified in @ref PM_SYS_PLL1_OFF;
 *    2. SYS_PLL1 is enabled in low power state, as specified in @ref PM_SYS_PLL1_ON.
 */
#define PM_RESC_SYS_PLL1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL1)
#define PM_RESC_SYS_PLL1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL1)

/*!
 * @brief Resource constraints definition of SYS_PLL1_CLK, with support for 2 modes:
 *    1. SYS_PLL1_CLK is disabled in low power state, as specified in @ref PM_SYS_PLL1_CLK_OFF;
 *    2. SYS_PLL1_CLK is enabled in low power state, as specified in @ref PM_SYS_PLL1_CLK_ON.
 */
#define PM_RESC_SYS_PLL1_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL1_CLK)
#define PM_RESC_SYS_PLL1_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL1_CLK)

/*!
 * @brief Resource constraints definition of SYS_PLL1_DIV2, with support for 2 modes:
 *    1. SYS_PLL1_DIV2 is disabled in low power state, as specified in @ref PM_SYS_PLL1_DIV2_OFF;
 *    2. SYS_PLL1_DIV2 is enabled in low power state, as specified in @ref PM_SYS_PLL1_DIV2_ON.
 */
#define PM_RESC_SYS_PLL1_DIV2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL1_DIV2)
#define PM_RESC_SYS_PLL1_DIV2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL1_DIV2)

/*!
 * @brief Resource constraints definition of SYS_PLL1_DIV5, with support for 2 modes:
 *    1. SYS_PLL1_DIV5 is disabled in low power state, as specified in @ref PM_SYS_PLL1_DIV5_OFF;
 *    2. SYS_PLL1_DIV5 is enabled in low power state, as specified in @ref PM_SYS_PLL1_DIV5_ON.
 */
#define PM_RESC_SYS_PLL1_DIV5_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYS_PLL1_DIV5)
#define PM_RESC_SYS_PLL1_DIV5_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SYS_PLL1_DIV5)

/*!
 * @brief Resource constraints definition of AUDIO_PLL, with support for 2 modes:
 *    1. AUDIO_PLL is disabled in low power state, as specified in @ref PM_AUDIO_PLL_OFF;
 *    2. AUDIO_PLL is enabled in low power state, as specified in @ref PM_AUDIO_PLL_ON.
 */
#define PM_RESC_AUDIO_PLL_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_AUDIO_PLL)
#define PM_RESC_AUDIO_PLL_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_AUDIO_PLL)

/*!
 * @brief Resource constraints definition of AUDIO_PLL_CLK, with support for 2 modes:
 *    1. AUDIO_PLL_CLK is disabled in low power state, as specified in @ref PM_AUDIO_PLL_CLK_OFF;
 *    2. AUDIO_PLL_CLK is enabled in low power state, as specified in @ref PM_AUDIO_PLL_CLK_ON.
 */
#define PM_RESC_AUDIO_PLL_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_AUDIO_PLL_CLK)
#define PM_RESC_AUDIO_PLL_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_AUDIO_PLL_CLK)

/*!
 * @brief Resource constraints definition of VIDEO_PLL, with support for 2 modes:
 *    1. VIDEO_PLL is disabled in low power state, as specified in @ref PM_VIDEO_PLL_OFF;
 *    2. VIDEO_PLL is enabled in low power state, as specified in @ref PM_VIDEO_PLL_ON.
 */
#define PM_RESC_VIDEO_PLL_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_VIDEO_PLL)
#define PM_RESC_VIDEO_PLL_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_VIDEO_PLL)

/*!
 * @brief Resource constraints definition of VIDEO_PLL_CLK, with support for 2 modes:
 *    1. VIDEO_PLL_CLK is disabled in low power state, as specified in @ref PM_VIDEO_PLL_CLK_OFF;
 *    2. VIDEO_PLL_CLK is enabled in low power state, as specified in @ref PM_VIDEO_PLL_CLK_ON.
 */
#define PM_RESC_VIDEO_PLL_CLK_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_VIDEO_PLL_CLK)
#define PM_RESC_VIDEO_PLL_CLK_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_VIDEO_PLL_CLK)

/*!
 * @brief Resource constraints definition of MEGA_MIX(contains the connectivity peripherals and audio peripherals, the
 * specific modules include: \b ENET1G , \b ENET , \b ENET QoS, \b uSDHC , \b USB , \b CAAM , \b ASRC , \b MQS ,
 * \b SAI1-3 , \b SPDIF ), with support for 2 modes:
 *     1. MEGA MIX is disabled in low power state, as specified in @ref PM_MEGA_MIX_OFF;
 *     2. MEGA MIX is enabled in low power state, as specified in @ref PM_MEGA_MIX_ON.
 *
 */
#define PM_RESC_MEGA_MIX_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_MEGA_MIX)
#define PM_RESC_MEGA_MIX_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_MEGA_MIX)

/*!
 * @brief Resource constraints definition of DISPLAY MIX(contains the display and graphics peripherals on the chip, the
 * specific modules include: \b GPU2D , \b PXP , \b eLCDIF , \b LCDOFv2 , \b CSI , \b MIPI_CSI2 , \b MIPI_DSI ,
 * \b VIDEO_MUX ), with support for 2 modes:
 *      1. DISPLAY MIX is disabled in low power state, as specified in @ref PM_DISPLAY_MXI_OFF;
 *      2. DISPLAY MIX is enabled in low power state, as specified in @ref PM_DISPLAY_MIX_ON.
 */
#define PM_RESC_DISPLAY_MIX_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DISPLAY_MIX)
#define PM_RESC_DISPLAY_MXI_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_DISPLAY_MIX)

/*!
 * @brief Resource constraints definition of WAKEUP MIX(contains the memory controllers and analog periperhal on the
 * chip, the specific modules include: \b EWM , \b WDOG1-3 , \b eDMA , \b DMAMUX0 , \b ACMP1-4 , \b LPADC1-2 ,
 * \b ADC_ETC , \b DAC , \b XBAR1-3 , \b KPP , \b IOMUX , \b IOMUX_GPR , \b GPIO1-6 , \b LPUART1-10 , \b MTR ,
 * \b FLEXCAN1-2 , \b QDC1-4 , \b PIT1 , \b AOI1-2 , \b GPT1-6 , \b TMR1-4 , \b FLEXPWM1-4 , \b LPI2C1-4 , \b LPSPI1-4 ,
 * \b FLEXIO1-2 , \b EMVSIM1-2 , \b FLEXSPI1-2 , \b SEMC , \b MECC1-2 , \b XECC , \b IEE ), with support for 2 modes:
 *       1. WAKEUP MIX is disabled in low power state, as specified in @ref PM_WAKEUP_MIX_OFF;
 *       2. WAKEUP MIX is enabled in low power state, as specified in @ref PM_WAKEUP_MIX_ON.
 */
#define PM_RESC_WAKEUP_MIX_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_WAKEUP_MIX)
#define PM_RESC_WAKEUP_MIX_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_WAKEUP_MIX)

/*!
 * @brief Resource constraints definition of LPSR MIX(contains the System control blocks and associated peripherals, the
 * specific modules include: \b GPC , \b PGMC , \b DCDC , \b SRC , \b SSARC , \b PMU , \b TEMPSENSE , \b XTALOSC ,
 * \b CCM , \b OCOTP , \b SNVS_HP , \b KEYMGR , \b WDOG_CM4 , \b IOMUX_SNVS , \b IOMUX_LPSR , \b MU , \b xRDC2 ,
 * \b RDC1-2 , \b SEMA4 , \b SEMA42, \b eDMA , \b DMAMUX1 , \b GPIO7-12 , \b PDM , \b SAI4, \b PIT2 , \b LPUART11-12 ,
 * \b LPSPI5-6 , \b LPI2C5-6 , \b FLEXCAN3 ), with support for 2 modes:
 *      1. LPSR MIX is disabled in low power state, as specificed in @ref PM_LPSR_MIX_OFF;
 *      2. LPSR MIX is enabled in low power state, as specificed in @ref PM_LPSR_MIX_ON.
 */
#define PM_RESC_LPSR_MIX_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LPSR_MIX)
#define PM_RESC_LPSR_MIX_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LPSR_MIX)

/*!
 * @brief Resource constraints definition of DCDC, with support for 2 modes:
 *      1. DCDC is diabled in low power state, as specificed in @ref PM_DCDC_OFF;
 *      2. DCDC is enabled in low power state, as specificed in @ref PM_DCDC_ON,
 * \note Only for application that use on-chip DCDC.
 */
#define PM_RESC_DCDC_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DCDC)
#define PM_RESC_DCDC_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_DCDC)

/*!
 * @brief Resource constraints definition of LPSR ANA LDO, with support for 2 modes:
 *      1. LPSR ANA LDO is disabled in low power state, as specified in @ref PM_LPSR_ANA_LDO_OFF;
 *      2. LPSR ANA LDO is enabled in low power state, as specified in @ref PM_LPSR_ANA_LDO_ON.
 */
#define PM_RESC_LPSR_ANA_LDO_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LPSR_ANA_LDO)
#define PM_RESC_LPSR_ANA_LDO_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LPSR_ANA_LDO)

/*!
 * @brief Resource constraints definition of LPSR DIG LDO, with support for 2 modes:
 *      1. LPSR DIG LDO is disabled in low power state, as specificed in @ref PM_LPSR_DIG_LDO_OFF;
 *      2. LPSR DIG LDO is enabled in low power state, as specificed in @ref PM_LPSR_DIG_LDO_ON.
 */
#define PM_RESC_LPSR_DIG_LDO_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LPSR_DIG_LDO)
#define PM_RESC_LPSR_DIG_LDO_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LPSR_DIG_LDO)

/*!
 * @brief Resource constraints definition of BANDGAP, with support for 2 modes:
 *      1. BANDGAP is disabled in low power state, as specificed in @ref PM_BANDGAP_OFF.
 *      2. BANDGAP is enabled in low power state, as specificed in @ref PM_BANDGAP_ON.
 */
#define PM_RESC_BANDGAP_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_BANDGAP)
#define PM_RESC_BANDGAP_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_BANDGAP)

/*!
 * @brief Resource constraints definition of M7's FBB, with support for 2 modes:
 *      1. FBB for M7 is disabled in low power state, as specificed in @ref PM_FBB_M7_OFF;
 *      2. FBB for M7 is enabled in low power state, as specificed in @ref PM_FBB_M7_ON.
 */
#define PM_RESC_FBB_M7_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_FBB_M7)
#define PM_RESC_FBB_M7_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_FBB_M7)

/*!
 * @brief Resource constraints definition of SOC' RBB, with support for 2 modes:
 *      1. RBB for SOC is disabled in low power state, as specified in @ref PM_RBB_SOC_OFF;
 *      2. RBB for SOC is enabled in low power state, as specified in @ref PM_RBB_SOC_ON.
 */
#define PM_RESC_RBB_SOC_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_RBB_SOC)
#define PM_RESC_RBB_SOC_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_RBB_SOC)

/*!
 * @brief Resource constraints definition of LPSR' RBB, with support for 2 modes:
 *      1. RBB for LPSR is disabled in low power state, as specified in @ref PM_RBB_LPSR_OFF;
 *      2. RBB for LPSR is enabled in low power state, as specified in @ref PM_RBB_LPSR_ON.
 */
#define PM_RESC_RBB_LPSR_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_RBB_LPSR)
#define PM_RESC_RBB_LPSR_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_RBB_LPSR)

/*!
 * @brief Resource constraints definition of standby request, with support for 2 modes:
 *      1. Standby request is disabled in low power state, as specified in @ref PM_STANDBY_REQ_OFF;
 *      2. Standby request is enabled in low power state, as specified in @ref PM_STANDBY_REQ_ON.
 */
#define PM_RESC_STANDBY_REQ_ON  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_STBY_REQ)
#define PM_RESC_STANDBY_REQ_OFF PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_STBY_REQ)

/*!
 * @brief Resource constraints definition of PLL LDO, with support for 2 modes:
 *       1. PLL LDO is disabled in low power state, as specified in @ref PM_PLL_LDO_OFF;
 *       2. PLL LDO is enabled in low power state, as specified in @ref PM_PLL_LDO_ON.
 */
#define PM_RESC_PLL_LDO_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_PLL_LDO)
#define PM_RESC_PLL_LDO_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_PLL_LDO)

/*! @} */

#if FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER
/*!
 * @name System Wakeup Source Definitions.
 * @{
 */

/* clang-format off */
#define PM_WSID_DMA0_DMA16_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA0_DMA16_IRQn)     /*!< DMA channel 0/16 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA1_DMA16_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA1_DMA17_IRQn)     /*!< DMA channel 1/17 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA2_DMA18_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA2_DMA18_IRQn)     /*!< DMA channel 2/18 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA3_DMA19_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA3_DMA19_IRQn)     /*!< DMA channel 3/19 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA4_DMA20_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA4_DMA20_IRQn)     /*!< DMA channel 4/20 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA5_DMA21_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA5_DMA21_IRQn)     /*!< DMA channel 5/21 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA6_DMA22_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA6_DMA22_IRQn)     /*!< DMA channel 6/22 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA7_DMA23_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA7_DMA23_IRQn)     /*!< DMA channel 7/23 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA8_DMA24_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA8_DMA24_IRQn)     /*!< DMA channel 8/24 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA9_DMA25_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(DMA9_DMA25_IRQn)     /*!< DMA channel 9/25 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA10_DMA26_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA10_DMA26_IRQn)    /*!< DMA channel 10/26 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA11_DMA27_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA11_DMA27_IRQn)    /*!< DMA channel 11/27 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA12_DMA28_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA12_DMA28_IRQn)    /*!< DMA channel 12/28 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA13_DMA29_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA13_DMA29_IRQn)    /*!< DMA channel 13/29 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA14_DMA30_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA14_DMA30_IRQn)    /*!< DMA channel 14/30 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA15_DMA31_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(DMA15_DMA31_IRQn)    /*!< DMA channel 15/31 transfer complete, available for CM4 and CM7. */
#define PM_WSID_DMA_ERROR_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(DMA_Error_IRQn)      /*!< DMA error interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_CTI_TRIGGER_OUT0_IRQ         PM_ENCODE_WAKEUP_SOURCE_ID(CTI_TRIGGER_OUT0_IRQn)    /*!< CTI trigger out 0 interrupt, available for CM7. */
#define PM_WSID_CTI_TRIGGER_OUT1_IRQ         PM_ENCODE_WAKEUP_SOURCE_ID(CTI_TRIGGER_OUT1_IRQn)    /*!< CTI trigger out 1 interrupt, available for CM7. */
#endif /* __CORTEX_M */
#define PM_WSID_CORE_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(CORE_IRQn)          /*!< Core platform exception IRQ, available for CM4 and CM7. */
#define PM_WSID_LPUART1_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART1_IRQn)       /*!< LPUART1 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART2_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART2_IRQn)       /*!< LPUART2 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART3_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART3_IRQn)       /*!< LPUART3 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART4_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART4_IRQn)       /*!< LPUART4 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART5_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART5_IRQn)       /*!< LPUART5 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART6_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART6_IRQn)       /*!< LPUART6 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART7_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART7_IRQn)       /*!< LPUART7 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART8_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART8_IRQn)       /*!< LPUART8 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART9_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LPUART9_IRQn)       /*!< LPUART9 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART10_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(LPUART10_IRQn)      /*!< LPUART10 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART11_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(LPUART11_IRQn)      /*!< LPUART11 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPUART12_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(LPUART12_IRQn)      /*!< LPUART12 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C1_IRQn)        /*!< LPI2C1 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C2_IRQn)        /*!< LPI2C2 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C3_IRQn)        /*!< LPI2C3 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C4_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C4_IRQn)        /*!< LPI2C4 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C5_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C5_IRQn)        /*!< LPI2C5 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPI2C6_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPI2C6_IRQn)        /*!< LPI2C6 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI1_IRQn)        /*!< LPSPI1 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI2_IRQn)        /*!< LPSPI2 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI3_IRQn)        /*!< LPSPI3 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI4_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI4_IRQn)        /*!< LPSPI4 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI5_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI5_IRQn)        /*!< LPSPI5 interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSPI6_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(LPSPI6_IRQn)        /*!< LPSPI6 interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(CAN1_IRQn)          /*!< CAN1 interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN1_ERROR_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(CAN1_ERROR_IRQn)    /*!< CAN1 error interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(CAN2_IRQn)          /*!< CAN2 interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN2_ERROR_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(CAN2_ERROR_IRQn)    /*!< CAN2 error interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN3_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(CAN3_IRQn)          /*!< CAN3 interrupt, available for CM4 and CM7. */
#define PM_WSID_CAN3_ERROR_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(CAN3_ERROR_IRQn)    /*!< CAN3 error interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_FLEXRAM_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(FLEXRAM_IRQn)       /*!< FLEXRAM address out of range or access hit IRQ interrupt, available for CM7. */
#endif /* __CORTEX_M == 7 */
#define PM_WSID_KPP_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(KPP_IRQn)           /*!< keypad interrupt, available for CM4 and CM7. */
#define PM_WSID_GPR_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(GPR_IRQ_IRQn)       /*!< GPR interrupt, available for CM4 and CM7. */
#define PM_WSID_ELCDIF_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(eLCDIF_IRQn)        /*!< eLCDIF  interrupt, available for CM4 and CM7. */
#define PM_WSID_LCDIFV2_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(LCDIFv2_IRQn)       /*!< LCDIFv2 interrupt, available for CM4 and CM7. */
#define PM_WSID_CSI_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(CSI_IRQn)           /*!< CSI interrupt, available for CM4 and CM7. */
#define PM_WSID_PXP_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(PXP_IRQn)           /*!< PXP interrupt, available for CM4 and CM7. */
#define PM_WSID_MIPI_CSI_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(MIPI_CSI_IRQn)      /*!< MIPI CSI interrupt, available for CM4 and CM7. */
#define PM_WSID_MIPI_DSI_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(MIPI_DSI_IRQn)      /*!< MIPI DSI interrupt, available for CM4 and CM7. */
#define PM_WSID_GPU2D_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(GPU2D_IRQn)         /*!< GPU2D interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_GPIO6_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO6_Combined_0_15_IRQn) /*!< GPIO6 combined interrupt 0-15, available for CM7. */
#define PM_WSID_GPIO6_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO6_Combined_16_31_IRQn) /*!< GPIO6 combined interrupt 16-31, available for CM7. */
#elif __CORTEX_M == 4
#define PM_WSID_GPIO12_COMBINED_0_15_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO12_Combined_0_15_IRQn) /*!< GPIO12 combined interrupt 0-15, available for CM4. */
#define PM_WSID_GPIO12_COMBINED_16_31_IRQ    PM_ENCODE_WAKEUP_SOURCE_ID(GPIO12_Combined_16_31_IRQn) /*!< GPIO12 combined interrupt 16-31, available for CM4. */
#endif /* __CORTEX_M */
#define PM_WSID_DAC_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(DAC_IRQn)           /*!< DAC interrupt, available for CM4 and CM7. */
#define PM_WSID_KEY_MANAGER_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(KEY_MANAGER_IRQn)   /*!< KEY_MANAGER interrupt, available for CM4 and CM7. */
#define PM_WSID_WDOG2_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(WDOG2_IRQn)         /*!< WDOG2 interrupt, available for CM4 and CM7. */
#define PM_WSID_SNVS_HP_NON_TZ_IRQ           PM_ENCODE_WAKEUP_SOURCE_ID(SNVS_HP_NON_TZ_IRQn) /*!< SRTC Consolidated Interrupt(Non trustzone), available for CM4 and CM7. */
#define PM_WSID_SNVS_HP_TZ_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(SNVS_HP_TZ_IRQn)    /*!< SRTC Consolidated Interrupt(trustzone), available for CM4 and CM7. */
#define PM_WSID_SNVS_PLUSE_EVENT_IRQ         PM_ENCODE_WAKEUP_SOURCE_ID(SNVS_PULSE_EVENT_IRQn) /*!< SNVS pulse event interrupt, available for CM4 and CM7. */
#define PM_WSID_CAAM_JQ0_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_IRQ0_IRQn)      /*!< CAAM interrupt queue for JQ0, available for CM4 and CM7. */
#define PM_WSID_CAAM_JQ1_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_IRQ1_IRQn)      /*!< CAAM interrupt queue for JQ1, available for CM4 and CM7. */
#define PM_WSID_CAAM_JQ2_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_IRQ2_IRQn)      /*!< CAAM interrupt queue for JQ2, available for CM4 and CM7. */
#define PM_WSID_CAAM_JQ3_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_IRQ3_IRQn)      /*!< CAAM interrupt queue for JQ3, available for CM4 and CM7. */
#define PM_WSID_CAAM_RECORVE_ERROR_IRQ       PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_RECORVE_ERRPR_IRQn)      /*!< CAAM interrupt for recoverable error, available for CM4 and CM7. */
#define PM_WSID_CAAM_RTIC_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(CAAM_RTIC_IRQn)     /*!< CAAM interrupt for RTIC, available for CM4 and CM7. */
#define PM_WSID_CDOG_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(CDOG_IRQn)          /*!< CDOG interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(SAI1_IRQn)          /*!< SAI1 interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(SAI2_IRQn)          /*!< SAI2 interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI3_RX_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(SAI3_RX_IRQn)       /*!< SAI3 RX interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI3_TX_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(SAI3_TX_IRQn)       /*!< SAI3 TX interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI4_RX_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(SAI4_RX_IRQn)       /*!< SAI4 RX interrupt, available for CM4 and CM7. */
#define PM_WSID_SAI4_TX_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(SAI4_TX_IRQn)       /*!< SAI4 TX interrupt, available for CM4 and CM7. */
#define PM_WSID_SPDIF_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(SPDIF_IRQn)         /*!< SPDIF interrupt, available for CM4 and CM7. */
#define PM_WSID_TMPSNS_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(TMPSNS_INT_IRQn)        /*!< TMPSNS interrupt, available for CM4 and CM7. */
#define PM_WSID_TMPSNS_LOW_HIGH_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(TMPSNS_LOW_HIGH_IRQn)   /*!< TMPSNS low/high interrupt, available for CM4 and CM7. */
#define PM_WSID_TMPSNS_PANIC_IRQ             PM_ENCODE_WAKEUP_SOURCE_ID(TMPSNS_PANIC_IRQn)      /*!< TMPSNS panic interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSR_LP8_BROWNOUT_IRQ        PM_ENCODE_WAKEUP_SOURCE_ID(LPSR_LP8_BROWNOUT_IRQn) /*!< LPSR LP8 brownout interrupt, available for CM4 and CM7. */
#define PM_WSID_LPSR_LP0_BROWNOUT_IRQ        PM_ENCODE_WAKEUP_SOURCE_ID(LPSR_LP0_BROWNOUT_IRQn) /*!< LPSR LP0 brownout interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ADC1_IRQn)          /*!< ADC1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ADC2_IRQn)          /*!< ADC2 interrupt, available for CM4 and CM7. */
#define PM_WSID_USBPHY1_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(USBPHY1_IRQn)       /*!< USBPHY1 interrupt, available for CM4 and CM7. */
#define PM_WSID_USBPHY2_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(USBPHY2_IRQn)       /*!< USBPHY2 interrupt, available for CM4 and CM7. */
#define PM_WSID_RDC_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(RDC_IRQn)           /*!< RDC interrupt, available for CM4 and CM7. */
#define PM_WSID_GPIO13_COMBINED_0_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO13_Combined_0_31_IRQn) /*!< GPIO13 combined interrupt for pins 0 to 31, available for CM4 and CM7. */
#define PM_WSID_DCIC1_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(DCIC1_IRQn)         /*!< DCIC1 interrupt, available for CM4 and CM7. */
#define PM_WSID_DCIC2_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(DCIC2_IRQn)         /*!< DCIC2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ASRC_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ASRC_IRQn)          /*!< ASRC interrupt, available for CM4 and CM7. */
#define PM_WSID_FLEXRAM_ECC_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(FLEXRAM_ECC_IRQn)   /*!< FLEXRAM ECC interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_CM7_GPIO2_3_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(CM7_GPIO2_3_IRQn) /*!< CM7_GPIO2,CM7_GPIO3 interrupt, available for CM7. */
#elif __CORTEX_M == 4
#define PM_WSID_GPIO7_8_9_10_11_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(GPIO7_8_9_10_11_IRQn) /*!< GPIO7,GPIO8,GPIO9,GPIO10,GPIO11 interrupt, available for CM4. */
#endif /* __CORTEX_M */
#define PM_WSID_GPIO1_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO1_Combined_0_15_IRQn) /*!< GPIO1 combined interrupt for pins 0 to 15, available for CM4 and CM7. */
#define PM_WSID_GPIO1_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO1_Combined_16_31_IRQn) /*!< GPIO1 combined interrupt for pins 16 to 31, available for CM4 and CM7. */
#define PM_WSID_GPIO2_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO2_Combined_0_15_IRQn) /*!< GPIO2 combined interrupt for pins 0 to 15, available for CM4 and CM7. */
#define PM_WSID_GPIO2_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO2_Combined_16_31_IRQn) /*!< GPIO2 combined interrupt for pins 16 to 31, available for CM4 and CM7. */
#define PM_WSID_GPIO3_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO3_Combined_0_15_IRQn) /*!< GPIO3 combined interrupt for pins 0 to 15, available for CM4 and CM7. */
#define PM_WSID_GPIO3_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO3_Combined_16_31_IRQn) /*!< GPIO3 combined interrupt for pins 16 to 31, available for CM4 and CM7. */
#define PM_WSID_GPIO4_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO4_Combined_0_15_IRQn) /*!< GPIO4 combined interrupt for pins 0 to 15, available for CM4 and CM7. */
#define PM_WSID_GPIO4_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO4_Combined_16_31_IRQn) /*!< GPIO4 combined interrupt for pins 16 to 31, available for CM4 and CM7. */
#define PM_WSID_GPIO5_COMBINED_0_15_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(GPIO5_Combined_0_15_IRQn) /*!< GPIO5 combined interrupt for pins 0 to 15, available for CM4 and CM7. */
#define PM_WSID_GPIO5_COMBINED_16_31_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(GPIO5_Combined_16_31_IRQn) /*!< GPIO5 combined interrupt for pins 16 to 31, available for CM4 and CM7. */
#define PM_WSID_FLEXIO1_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(FLEXIO1_IRQn)       /*!< FLEXIO1 interrupt, available for CM4 and CM7. */
#define PM_WSID_FLEXIO2_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(FLEXIO2_IRQn)       /*!< FLEXIO2 interrupt, available for CM4 and CM7. */
#define PM_WSID_WDOG1_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(WDOG1_IRQn)         /*!< WDOG1 interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_RTWDOG3_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(RTWDOG3_IRQn)       /*!< RTWDOG3 interrupt, available for CM7. */
#elif __CORTEX_M == 4
#define PM_WSID_RTWDOG4_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(RTWDOG4_IRQn)       /*!< RTWDOG4 interrupt, available for CM4. */
#endif /* __CORTEX_M */
#define PM_WSID_EWM_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(EWM_IRQn)           /*!< EWM interrupt, available for CM4 and CM7. */
#define PM_WSID_OCOTP_READ_FUSE_ERROR_IRQ    PM_ENCODE_WAKEUP_SOURCE_ID(OCOTP_READ_FUSE_ERROR_IRQn) /*!< OCOTP_READ_FUSE_ERROR interrupt, available for CM4 and CM7. */
#define PM_WSID_OCOTP_READ_DONE_ERROR_IRQ    PM_ENCODE_WAKEUP_SOURCE_ID(OCOTP_READ_DONE_ERROR_IRQn) /*!< OCOTP_READ_DONE_ERROR interrupt, available for CM4 and CM7. */
#define PM_WSID_GPC_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(GPC_IRQn)           /*!< GPC interrupt, available for CM4 and CM7. */
#if __CORTEX_M == 7
#define PM_WSID_MUA_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(MUA_IRQn)           /*!< MUA interrupt, available for CM7. */
#elif __CORTEX_M == 4
#define PM_WSID_MUB_IRQ                      PM_ENCODE_WAKEUP_SOURCE_ID(MUB_IRQn)           /*!< MUB interrupt, available for CM4. */
#endif /* __CORTEX_M */
#define PM_WSID_GPT1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT1_IRQn)          /*!< GPT1 interrupt, available for CM4 and CM7. */
#define PM_WSID_GPT2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT2_IRQn)          /*!< GPT2 interrupt, available for CM4 and CM7. */
#define PM_WSID_GPT3_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT3_IRQn)          /*!< GPT3 interrupt, available for CM4 and CM7. */
#define PM_WSID_GPT4_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT4_IRQn)          /*!< GPT4 interrupt, available for CM4 and CM7. */
#define PM_WSID_GPT5_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT5_IRQn)          /*!< GPT5 interrupt, available for CM4 and CM7. */
#define PM_WSID_GPT6_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(GPT6_IRQn)          /*!< GPT6 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM1_0_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM1_0_IRQn)        /*!< PWM1 capture 0, compare 0, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM1_1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM1_1_IRQn)        /*!< PWM1 capture 1, compare 1, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM1_2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM1_2_IRQn)        /*!< PWM1 capture 2, compare 2, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM1_3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM1_3_IRQn)        /*!< PWM1 capture 3, compare 3, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM1_FAULT_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(PWM1_FAULT_IRQn)    /*!< PWM1 fault or reload error interrupt, available for CM4 and CM7. */
#define PM_WSID_FLEXSPI1_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(FLEXSPI1_IRQn)      /*!< FLEXSPI1 interrupt, available for CM4 and CM7. */
#define PM_WSID_FLEXSPI2_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(FLEXSPI2_IRQn)      /*!< FLEXSPI2 interrupt, available for CM4 and CM7. */
#define PM_WSID_SEMC_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(SEMC_IRQn)          /*!< SEMC interrupt, available for CM4 and CM7. */
#define PM_WSID_USDHC1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(USDHC1_IRQn)        /*!< USDHC1 interrupt, available for CM4 and CM7. */
#define PM_WSID_USDHC2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(USDHC2_IRQn)        /*!< USDHC2 interrupt, available for CM4 and CM7. */
#define PM_WSID_USB_OTG2_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(USB_OTG2_IRQn)      /*!< USBO2 USB OTG2 interrupt, available for CM4 and CM7. */
#define PM_WSID_USB_OTG1_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(USB_OTG1_IRQn)      /*!< USBO2 USB OTG1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ENET_IRQn)          /*!< ENET interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_1588_TIMER_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(ENET_1588_Timer_IRQn) /*!< ENET 1588 timer interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_1G_MAC0_TX_RX_1_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(ENET_1G_MAC0_Tx_Rx_1_IRQn) /*!< ENET 1G MAC0 TX/RX 1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_1G_MAC0_TX_RX_2_IRQ     PM_ENCODE_WAKEUP_SOURCE_ID(ENET_1G_MAC0_Tx_Rx_2_IRQn) /*!< ENET 1G MAC0 TX/RX 2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_1G_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(ENET_1G_IRQn)        /*!< ENET 1G interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_1G_1588_TIMER_IRQ       PM_ENCODE_WAKEUP_SOURCE_ID(ENET_1G_1588_Timer_IRQn) /*!< ENET 1G 1588 timer interrupt, available for CM4 and CM7. */
#define PM_WSID_XBAR1_0_1_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(XBAR1_IRQ_0_1_IRQn)     /*!< XBAR1 interrupt, available for CM4 and CM7. */
#define PM_WSID_XBAR1_2_3_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(XBAR1_IRQ_2_3_IRQn)     /*!< XBAR1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC_ETC_0_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(ADC_ETC_IRQ0_IRQn)     /*!< ADC_ETC IRQ0 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC_ETC_1_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(ADC_ETC_IRQ1_IRQn)     /*!< ADC_ETC IRQ1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC_ETC_2_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(ADC_ETC_IRQ2_IRQn)     /*!< ADC_ETC IRQ2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC_ETC_3_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(ADC_ETC_IRQ3_IRQn)     /*!< ADC_ETC IRQ3 interrupt, available for CM4 and CM7. */
#define PM_WSID_ADC_ETC_ERROR_IRQ            PM_ENCODE_WAKEUP_SOURCE_ID(ADC_ETC_ERROR_IRQ_IRQn)   /*!< ADC_ETC error interrupt, available for CM4 and CM7. */
#define PM_WSID_PIT1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(PIT1_IRQn)          /*!< PIT1 interrupt, available for CM4 and CM7. */
#define PM_WSID_PIT2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(PIT2_IRQn)          /*!< PIT2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ACMP1_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(ACMP1_IRQn)         /*!< ACMP1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ACMP2_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(ACMP2_IRQn)         /*!< ACMP2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ACMP3_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(ACMP3_IRQn)         /*!< ACMP3 interrupt, available for CM4 and CM7. */
#define PM_WSID_ACMP4_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(ACMP4_IRQn)         /*!< ACMP4 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENC1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ENC1_IRQn)          /*!< ENC1 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENC2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ENC2_IRQn)          /*!< ENC2 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENC3_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ENC3_IRQn)          /*!< ENC3 interrupt, available for CM4 and CM7. */
#define PM_WSID_ENC4_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(ENC4_IRQn)          /*!< ENC4 interrupt, available for CM4 and CM7. */
#define PM_WSID_TMR1_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(TMR1_IRQn)          /*!< TMR1 interrupt, available for CM4 and CM7. */
#define PM_WSID_TMR2_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(TMR2_IRQn)          /*!< TMR2 interrupt, available for CM4 and CM7. */
#define PM_WSID_TMR3_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(TMR3_IRQn)          /*!< TMR3 interrupt, available for CM4 and CM7. */
#define PM_WSID_TMR4_IRQ                     PM_ENCODE_WAKEUP_SOURCE_ID(TMR4_IRQn)          /*!< TMR4 interrupt, available for CM4 and CM7. */
#define PM_WSID_SEMA4_CP0_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(SEMA4_CP0_IRQn)     /*!< SEMA4 CP0 interrupt, available for CM4 and CM7. */
#define PM_WSID_SEMA4_CP1_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(SEMA4_CP1_IRQn)     /*!< SEMA4 CP1 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM2_0_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM2_0_IRQn)        /*!< PWM2 capture 0, compare 0, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM2_1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM2_1_IRQn)        /*!< PWM2 capture 1, compare 1, or reload 1 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM2_2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM2_2_IRQn)        /*!< PWM2 capture 2, compare 2, or reload 2 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM2_3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM2_3_IRQn)        /*!< PWM2 capture 3, compare 3, or reload 3 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM2_FAULT_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(PWM2_FAULT_IRQn)    /*!< PWM2 fault or reload error interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM3_0_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM3_0_IRQn)        /*!< PWM3 capture 0, compare 0, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM3_1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM3_1_IRQn)        /*!< PWM3 capture 1, compare 1, or reload 1 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM3_2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM3_2_IRQn)        /*!< PWM3 capture 2, compare 2, or reload 2 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM3_3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM3_3_IRQn)        /*!< PWM3 capture 3, compare 3, or reload 3 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM3_FAULT_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(PWM3_FAULT_IRQn)    /*!< PWM3 fault or reload error interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM4_0_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM4_0_IRQn)        /*!< PWM4 capture 0, compare 0, or reload 0 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM4_1_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM4_1_IRQn)        /*!< PWM4 capture 1, compare 1, or reload 1 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM4_2_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM4_2_IRQn)        /*!< PWM4 capture 2, compare 2, or reload 2 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM4_3_IRQ                   PM_ENCODE_WAKEUP_SOURCE_ID(PWM4_3_IRQn)        /*!< PWM4 capture 3, compare 3, or reload 3 interrupt, available for CM4 and CM7. */
#define PM_WSID_PWM4_FAULT_IRQ               PM_ENCODE_WAKEUP_SOURCE_ID(PWM4_FAULT_IRQn)    /*!< PWM4 fault or reload error interrupt, available for CM4 and CM7. */
#define PM_WSID_PDM_HWVAD_EVENT_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(PDM_HWVAD_EVENT_IRQn) /*!< PDM HWVAD event interrupt, available for CM4 and CM7. */
#define PM_WSID_PDM_HWVAD_ERROR_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(PDM_HWVAD_ERROR_IRQn) /*!< PDM HWVAD error interrupt, available for CM4 and CM7. */
#define PM_WSID_PDM_EVENT_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(PDM_EVENT_IRQn)     /*!< PDM event interrupt, available for CM4 and CM7. */
#define PM_WSID_PDM_ERROR_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(PDM_ERROR_IRQn)     /*!< PDM error interrupt, available for CM4 and CM7. */
#define PM_WSID_EMVSIM1_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(EMVSIM1_IRQn)       /*!< EMVSIM1 interrupt, available for CM4 and CM7. */
#define PM_WSID_EMVSIM2_IRQ                  PM_ENCODE_WAKEUP_SOURCE_ID(EMVSIM2_IRQn)       /*!< EMVSIM2 interrupt, available for CM4 and CM7. */
#define PM_WSID_MECC1_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(MECC1_INT_IRQn)         /*!< MECC1 interrupt, available for CM4 and CM7. */
#define PM_WSID_MECC1_FATAL_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(MECC1_FATAL_INT_IRQn)   /*!< MECC1 fatal interrupt, available for CM4 and CM7. */
#define PM_WSID_MECC2_IRQ                    PM_ENCODE_WAKEUP_SOURCE_ID(MECC2_INT_IRQn)         /*!< MECC2 interrupt, available for CM4 and CM7. */
#define PM_WSID_MECC2_FATAL_IRQ              PM_ENCODE_WAKEUP_SOURCE_ID(MECC2_FATAL_INT_IRQn)   /*!< MECC2 fatal interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_FLEXSPI1_IRQ            PM_ENCODE_WAKEUP_SOURCE_ID(XECC_FLEXSPI1_INT_IRQn) /*!< XECC interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_FLEXSPI1_FATAL_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(XECC_FLEXSPI1_FATAL_INT_IRQn) /*!< XECC fatal interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_FLEXSPI2_IRQ            PM_ENCODE_WAKEUP_SOURCE_ID(XECC_FLEXSPI2_INT_IRQn) /*!< XECC interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_FLEXSPI2_FATAL_IRQ      PM_ENCODE_WAKEUP_SOURCE_ID(XECC_FLEXSPI2_FATAL_INT_IRQn) /*!< XECC fatal interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_SEMC_IRQ                PM_ENCODE_WAKEUP_SOURCE_ID(XECC_SEMC_INT_IRQn)          /*!< XECC interrupt, available for CM4 and CM7. */
#define PM_WSID_XECC_SEMC_FATAL_IRQ          PM_ENCODE_WAKEUP_SOURCE_ID(XECC_SEMC_FATAL_INT_IRQn)    /*!< XECC fatal interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_QOS_IRQ                 PM_ENCODE_WAKEUP_SOURCE_ID(ENET_QOS_IRQn)            /*!< ENET QOS interrupt, available for CM4 and CM7. */
#define PM_WSID_ENET_QOS_PMT_IRQ             PM_ENCODE_WAKEUP_SOURCE_ID(ENET_QOS_PMT_IRQn)         /*!< ENET QOS PMT interrupt, available for CM4 and CM7. */
/* clang-format on */
/*! @} */
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*! @} */

#endif /* _FSL_PM_DEVICE_H_ */
