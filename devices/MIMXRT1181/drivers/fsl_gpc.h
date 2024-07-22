/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_GPC_H_
#define _FSL_GPC_H_

#include "fsl_common.h"

/*!
 * @addtogroup gpc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief GPC driver version 2.1.0. */
#define FSL_GPC_RIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @}*/

#define GPC_RESERVED_USE_MACRO 0xFFFFFFFFU

/* GPC CPU module step control register offset. */
#define GPC_CM_SLEEP_SSAR_CTRL_OFFSET  (0x200)
#define GPC_CM_SLEEP_LPCG_CTRL_OFFSET  (0x208)
#define GPC_CM_SLEEP_PLL_CTRL_OFFSET   (0x210)
#define GPC_CM_SLEEP_ISO_CTRL_OFFSET   (0x218)
#define GPC_CM_SLEEP_RESET_CTRL_OFFSET (0x220)
#define GPC_CM_SLEEP_POWER_CTRL_OFFSET (0x228)

#define GPC_CM_WAKEUP_POWER_CTRL_OFFSET (0x290)
#define GPC_CM_WAKEUP_RESET_CTRL_OFFSET (0x298)
#define GPC_CM_WAKEUP_ISO_CTRL_OFFSET   (0x2A0)
#define GPC_CM_WAKEUP_PLL_CTRL_OFFSET   (0x2A8)
#define GPC_CM_WAKEUP_LPCG_CTRL_OFFSET  (0x2B0)
#define GPC_CM_WAKEUP_SSAR_CTRL_OFFSET  (0x2B8)

/* GPC system sleep module step control register offset. */
#define GPC_SS_STEP0_IN_CTRL_OFFSET (0xF0)
#define GPC_SS_STEP1_IN_CTRL_OFFSET (0x100)
#define GPC_SS_STEP2_IN_CTRL_OFFSET (0x110)
#define GPC_SS_STEP3_IN_CTRL_OFFSET (0x120)
#define GPC_SS_DCDC_IN_CTRL_OFFSET  (0x140)
#define GPC_SS_PMIC_IN_CTRL_OFFSET  (0x150)

#define GPC_SS_PMIC_OUT_CTRL_OFFSET  (0x200)
#define GPC_SS_DCDC_OUT_CTRL_OFFSET  (0x210)
#define GPC_SS_STEP3_OUT_CTRL_OFFSET (0x238)
#define GPC_SS_STEP2_OUT_CTRL_OFFSET (0x240)
#define GPC_SS_STEP1_OUT_CTRL_OFFSET (0x250)
#define GPC_SS_STEP0_OUT_CTRL_OFFSET (0x260)

/* GPC CPU module step register offset. */
#define GPC_CM_STEP_REG_OFFSET                                                                             \
    {                                                                                                      \
        GPC_CM_SLEEP_SSAR_CTRL_OFFSET, GPC_CM_SLEEP_LPCG_CTRL_OFFSET, GPC_CM_SLEEP_PLL_CTRL_OFFSET,        \
            GPC_CM_SLEEP_ISO_CTRL_OFFSET, GPC_CM_SLEEP_RESET_CTRL_OFFSET, GPC_CM_SLEEP_POWER_CTRL_OFFSET,  \
            GPC_RESERVED_USE_MACRO, GPC_RESERVED_USE_MACRO, GPC_CM_WAKEUP_POWER_CTRL_OFFSET,               \
            GPC_CM_WAKEUP_RESET_CTRL_OFFSET, GPC_CM_WAKEUP_ISO_CTRL_OFFSET, GPC_CM_WAKEUP_PLL_CTRL_OFFSET, \
            GPC_CM_WAKEUP_LPCG_CTRL_OFFSET, GPC_CM_WAKEUP_SSAR_CTRL_OFFSET,                                \
    }

/* GPC system sleep module step register offset. */
#define GPC_SS_STEP_REG_OFFSET                                                                        \
    {                                                                                                 \
        GPC_SS_STEP0_IN_CTRL_OFFSET, GPC_SS_STEP1_IN_CTRL_OFFSET, GPC_SS_STEP2_IN_CTRL_OFFSET,        \
            GPC_SS_STEP3_IN_CTRL_OFFSET, GPC_SS_DCDC_IN_CTRL_OFFSET, GPC_SS_PMIC_IN_CTRL_OFFSET,      \
            GPC_SS_PMIC_OUT_CTRL_OFFSET, GPC_SS_DCDC_OUT_CTRL_OFFSET, GPC_SS_STEP3_OUT_CTRL_OFFSET,   \
            GPC_SS_STEP2_OUT_CTRL_OFFSET, GPC_SS_STEP1_OUT_CTRL_OFFSET, GPC_SS_STEP0_OUT_CTRL_OFFSET, \
    }

/* Make/Get status. */
/* Make the mask/shift value of GPC status register in a variable. */
#define GPC_STAT(mask, shift) (uint32_t)(((uint32_t)(shift) << 16UL) + ((uint32_t)(mask) >> (uint32_t)(shift)))

/*! @brief _gpc_cm_non_irq_wakeup_request GPC Non-IRQ wakeup request. */
enum
{
    kGPC_CM_DebugWakeupRequest =
        GPC_CPU_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_MASK, /*!< Debug wakeup request. */
};

/* @brief _gpc_domain_map GPC domain map. */
enum
{
    kGPC_Domain0  = 1UL << 0UL,  /*!< GPC domain 0. */
    kGPC_Domain1  = 1UL << 1UL,  /*!< GPC domain 1. */
    kGPC_Domain2  = 1UL << 2UL,  /*!< GPC domain 2. */
    kGPC_Domain3  = 1UL << 3UL,  /*!< GPC domain 3. */
    kGPC_Domain4  = 1UL << 4UL,  /*!< GPC domain 4. */
    kGPC_Domain5  = 1UL << 5UL,  /*!< GPC domain 5. */
    kGPC_Domain6  = 1UL << 6UL,  /*!< GPC domain 6. */
    kGPC_Domain7  = 1UL << 7UL,  /*!< GPC domain 7. */
    kGPC_Domain8  = 1UL << 8UL,  /*!< GPC domain 8. */
    kGPC_Domain9  = 1UL << 9UL,  /*!< GPC domain 9. */
    kGPC_Domain10 = 1UL << 10UL, /*!< GPC domain 10. */
    kGPC_Domain11 = 1UL << 11UL, /*!< GPC domain 11. */
    kGPC_Domain12 = 1UL << 12UL, /*!< GPC domain 12. */
    kGPC_Domain13 = 1UL << 13UL, /*!< GPC domain 13. */
    kGPC_Domain14 = 1UL << 14UL, /*!< GPC domain 14. */
    kGPC_Domain15 = 1UL << 15UL, /*!< GPC domain 15. */
};

/*!
 * @brief CPU slice.
 */
typedef enum _gpc_cpu_slice
{
    kGPC_CPU0 = 0x0U, /*!< CPU slice 0. */
    kGPC_CPU1 = 0x1U, /*!< CPU slice 1. */
} gpc_cpu_slice_t;

/*! @brief CPU mode transition step in sleep/wakeup sequence. */
typedef enum _gpc_cm_tran_step
{
    kGPC_CM_SleepSsar  = 0UL, /*!< SSAR (State Save And Restore) sleep step. */
    kGPC_CM_SleepLpcg  = 1UL, /*!< LPCG (Low Power Clock Gating) sleep step. */
    kGPC_CM_SleepPll   = 2UL, /*!< PLL sleep step. */
    kGPC_CM_SleepIso   = 3UL, /*!< ISO (Isolation) sleep step. */
    kGPC_CM_SleepReset = 4UL, /*!< Reset sleep step. */
    kGPC_CM_SleepPower = 5UL, /*!< Power sleep step. */
    kGPC_CM_SleepSYS =
        6UL, /*!< System sleep sleep step. Note that this step is controlled by system sleep controller. */
    kGPC_CM_WakeupSYS =
        7UL, /*!< System sleep wakeup step. Note that this step is controlled by system sleep controller. */
    kGPC_CM_WakeupPower = 8UL,  /*!< Power wakeup step. */
    kGPC_CM_WakeupReset = 9UL,  /*!< Reset wakeup step. */
    kGPC_CM_WakeupIso   = 10UL, /*!< ISO wakeup step. */
    kGPC_CM_WakeupPll   = 11UL, /*!< PLL wakeup step. */
    kGPC_CM_WakeupLpcg  = 12UL, /*!< LPCG wakeup step. */
    kGPC_CM_WakeupSsar  = 13UL, /*!< SSAR wakeup step. */
} gpc_cm_tran_step_t;

/*! @brief CPU mode. */
typedef enum _gpc_cpu_mode
{
    kGPC_RunMode     = 0x0UL, /*!< Stay in RUN mode. */
    kGPC_WaitMode    = 0x1UL, /*!< Transit to WAIT mode. */
    kGPC_StopMode    = 0x2UL, /*!< Transit to STOP mode. */
    kGPC_SuspendMode = 0x3UL, /*!< Transit to SUSPEND mode. */
} gpc_cpu_mode_t;

/*! @brief GPC system sleep mode transition steps. */
typedef enum _gpc_ss_tran_step
{
    kGPC_SS_Step0In  = 0UL,  /*!< Bias in step. */
    kGPC_SS_Step1In  = 1UL,  /*!< PLDO in step. */
    kGPC_SS_Step2In  = 2UL,  /*!< Bandgap in step. */
    kGPC_SS_Step3In  = 3UL,  /*!< LDO in step. */
    kGPC_SS_DcdcIn   = 4UL,  /*!< DCDC in step. */
    kGPC_SS_PmicIn   = 5UL,  /*!< PMIC in step. */
    kGPC_SS_PmicOut  = 6UL,  /*!< PMIC out step. */
    kGPC_SS_DcdcOut  = 7UL,  /*!< DCDC out step. */
    kGPC_SS_Step3Out = 8UL,  /*!< LDO out step. */
    kGPC_SS_Step2Out = 9UL,  /*!< Bandgap out step. */
    kGPC_SS_Step1Out = 10UL, /*!< PLDO out step. */
    kGPC_SS_Step0Out = 11UL, /*!< Bias out step. */
} gpc_ss_tran_step_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name GPC global control
 * @{
 */

/*
 * brief Assign domain id for each cpu slice.
 *
 * This function assign the domain id for cpu slice. If there are multiple domains, use:
 * code
 *    domainMap = kGPC_Domain0 | kGPC_kGPC_Domain1 | ... | kGPC_kGPC_Domain15;
 * encode
 *
 * param slice GPC CPU slice number.
 * param domainMap Number of the domain. Refer to "_gpc_domain_map".
 */
void GPC_AssignCpuDomain(gpc_cpu_slice_t cpu, uint32_t domainMap);

/*!
 * @}
 */

/*!
 * @name CPU mode control
 * @{
 */

/*
 * @brief Hold core in sleep state.
 *
 * This function is used to hold the core in sleep state once it enters WFI, and until finishing wakeup sequence. If a
 * wakeup IRQ happens during the delay between core sleeps and core clock stops, the core will be woken up but GPC is on
 * sleep sequence and shut off the clock when core is processing the IRQ, this may leads to an unpredictable status.
 *
 * @param slice GPC CPU slice number.
 */
static inline void GPC_CM_EnableCpuSleepHold(gpc_cpu_slice_t slice, bool enable)
{
    if (enable)
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_MISC |= GPC_CPU_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK;
    }
    else
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_MISC &= ~GPC_CPU_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK;
    }
}

/*!
 * @brief Set the CPU mode on the next sleep event.
 *
 * This function configures the CPU mode that the CPU core will transmit to on next sleep event.
 *
 * @note This API must be called each time before entering sleep.
 *
 * @param slice GPC CPU slice number.
 * @param mode The CPU mode that the core will transmit to, refer to "gpc_cpu_mode_t".
 */
static inline void GPC_CM_SetNextCpuMode(gpc_cpu_slice_t slice, gpc_cpu_mode_t mode)
{
    GPC_CPU_CTRL->AUTHEN[slice].CM_MODE_CTRL =
        (GPC_CPU_CTRL->AUTHEN[slice].CM_MODE_CTRL & ~GPC_CPU_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_MASK) |
        GPC_CPU_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET(mode);
}

/*!
 * @brief Get current CPU mode.
 *
 * @param slice GPC CPU slice number.
 * @return The current CPU mode, in type of @ref gpc_cpu_mode_t.
 */
static inline gpc_cpu_mode_t GPC_CM_GetCurrentCpuMode(gpc_cpu_slice_t slice)
{
    return (gpc_cpu_mode_t)(uint32_t)(
        (GPC_CPU_CTRL->AUTHEN[slice].CM_MODE_STAT & GPC_CPU_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_MASK) >>
        GPC_CPU_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_SHIFT);
}

/*!
 * @brief Get previous CPU mode.
 *
 * @param slice GPC CPU slice number.
 * @return The previous CPU mode, in type of @ref gpc_cpu_mode_t.
 */
static inline gpc_cpu_mode_t GPC_CM_GetPreviousCpuMode(gpc_cpu_slice_t slice)
{
    return (gpc_cpu_mode_t)(uint32_t)(
        (GPC_CPU_CTRL->AUTHEN[slice].CM_MODE_STAT & GPC_CPU_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_MASK) >>
        GPC_CPU_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_SHIFT);
}

/*!
 * @brief Enable IRQ wakeup request.
 *
 * This function enables the IRQ request which can wakeup the CPU platform.
 *
 * @param slice GPC CPU slice number.
 * @param irqId ID of the IRQ, accessible range is 0-255.
 * @param enable Enable the IRQ request or not.
 */
void GPC_CM_EnableIrqWakeup(gpc_cpu_slice_t slice, uint32_t irqId, bool enable);

/*!
 * @brief Enable Non-IRQ wakeup request.
 *
 * This function enables the non-IRQ request which can wakeup the CPU platform.
 *
 * @param slice GPC CPU slice number.
 * @param mask Non-IRQ type, refer to "_gpc_cm_non_irq_wakeup_request".
 * @param enable Enable the Non-IRQ request or not.
 */
static inline void GPC_CM_EnableNonIrqWakeup(gpc_cpu_slice_t slice, uint32_t mask, bool enable)
{
    assert(mask < 2UL);

    if (true == enable)
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_NON_IRQ_WAKEUP_MASK &= ~mask;
    }
    else
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_NON_IRQ_WAKEUP_MASK |= mask;
    }
}

/*!
 * @brief Get the status of the IRQ wakeup request.
 *
 * @param slice GPC CPU slice number.
 * @param irqId ID of the IRQ, accessible range is 0-255.
 * @return Indicate the IRQ request is asserted or not.
 */
bool GPC_CM_GetIrqWakeupStatus(gpc_cpu_slice_t slice, uint32_t irqId);

/*!
 * @brief Get the status of the Non-IRQ wakeup request.
 *
 * @param slice GPC CPU slice number.
 * @param mask Non-IRQ type, refer to "_gpc_cm_non_irq_wakeup_request".
 * @return Indicate the Non-IRQ request is asserted or not.
 */
static inline bool GPC_CM_GetNonIrqWakeupStatus(gpc_cpu_slice_t slice, uint32_t mask)
{
    return (mask == (GPC_CPU_CTRL->AUTHEN[slice].CM_NON_IRQ_WAKEUP_STAT & mask));
}

/*!
 * brief Config the cpu mode transition step.
 *
 * param slice GPC CPU slice number.
 * param step step type, refer to "gpc_cm_tran_step_t".
 * param enable Used to control the transition step.
 *            - \b true This step is enabled.
 *            - \b false This step is disabled, GPC will skip this step and not send any request.
 */
void GPC_CM_EnableCpuModeTransitionStep(gpc_cpu_slice_t slice, gpc_cm_tran_step_t step, bool enable);

/*!
 * @brief Request the chip into system sleep mode.
 *
 * @param slice GPC CPU slice number.
 * @param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_RequestSystemSleepMode(gpc_cpu_slice_t slice, const gpc_cpu_mode_t mode);

/*!
 * @brief Clear the system sleep mode request.
 *
 * @param slice GPC CPU slice number.
 * @param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_ClearSystemSleepModeRequest(gpc_cpu_slice_t slice, const gpc_cpu_mode_t mode);

/*!
 * @brief Get the status of the CPU system sleep mode transition.
 *
 * @param slice GPC CPU slice number.
 * @param mask System sleep mode transition status mask, refer to "gpc_cm_system sleep_mode_status_t".
 * @return Indicate the CPU's system sleep transition status.
 */
static inline bool GPC_CM_GetSystemSleepModeStatus(gpc_cpu_slice_t slice, uint32_t mask)
{
    return (mask == (GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL & mask));
}

/*!
 * @}
 */

/*!
 * @name System sleep mode control
 * @{
 */

/*!
 * brief Config the system sleep transition step.
 *
 * param base GPC system sleep controller base address.
 * param step step type, refer to "gpc_ss_tran_step_t".
 * param enable Used to control the transition step.
 *            - \b true This step is enabled.
 *            - \b false This step is disabled, GPC will skip this step and not send any request.
 */
void GPC_SS_EnableSystemSleepTransitionStep(GPC_SYS_SLEEP_CTRL_Type *base, gpc_ss_tran_step_t step, bool enable);

/*!
 * @brief Trigger PMIC standby ON/OFF by software.
 *
 * @param base PMIC module base address.
 * @param enable Trigger on/off PMIC standby.
 *			- \b true Trigger PMIC standby ON.
 *			- \b false Trigger PMIC standby OFF.
 */
static inline void GPC_SS_SoftwareTriggerPMICStandby(GPC_SYS_SLEEP_CTRL_Type *base, bool enable)
{
    if (enable)
    {
        base->PMIC_CTRL |= GPC_SYS_SLEEP_CTRL_PMIC_CTRL_PMIC_STBY_SOFT_MASK;
    }
    else
    {
        base->PMIC_CTRL &= ~GPC_SYS_SLEEP_CTRL_PMIC_CTRL_PMIC_STBY_SOFT_MASK;
    }
}

/*!
 * brief Assert the PMIC standby request when system sleep.
 *
 * @param base PMIC module base address.
 * @param enable Assert PMIC standby request or not.
 *			- \b true Assert PMIC_STBY_REQ when system sleep is entered.
 *			- \b false Do not assert PMIC_STBY_REQ when system sleep is entered.
 */
static inline void GPC_SS_SystemSleepTriggerPMICStandby(GPC_SYS_SLEEP_CTRL_Type *base, bool enable)
{
    if (enable)
    {
        base->PMIC_CTRL |= GPC_SYS_SLEEP_CTRL_PMIC_CTRL_PMIC_STBY_EN_MASK;
    }
    else
    {
        base->PMIC_CTRL &= ~GPC_SYS_SLEEP_CTRL_PMIC_CTRL_PMIC_STBY_EN_MASK;
    }
}

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_GPC_H_ */
