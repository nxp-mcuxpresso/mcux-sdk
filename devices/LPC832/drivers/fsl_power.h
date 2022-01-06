/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018, 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_POWER_H_
#define _FSL_POWER_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup power
 * @{
 */

/*! @name Driver version */
/*@{*/
/*! @brief power driver version 2.1.0. */
#define FSL_POWER_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/*! @brief PMU PCON reserved mask, used to clear reserved field which should not write 1*/
#define PMUC_PCON_RESERVED_MASK ((0xf << 4) | (0x6 << 8) | 0xfffff000u)

#define POWER_EnbaleLPO                    POWER_EnableLPO
#define POWER_EnbaleLPOInDeepPowerDownMode POWER_EnableLPOInDeepPowerDownMode

typedef enum pd_bits
{
    kPDRUNCFG_PD_IRC_OUT = SYSCON_PDRUNCFG_IRCOUT_PD_MASK,
    kPDRUNCFG_PD_IRC     = SYSCON_PDRUNCFG_IRC_PD_MASK,
    kPDRUNCFG_PD_FLASH   = SYSCON_PDRUNCFG_FLASH_PD_MASK,
    kPDRUNCFG_PD_BOD     = SYSCON_PDRUNCFG_BOD_PD_MASK,
    kPDRUNCFG_PD_ADC0    = SYSCON_PDRUNCFG_ADC_PD_MASK,
    kPDRUNCFG_PD_SYSOSC  = SYSCON_PDRUNCFG_SYSOSC_PD_MASK,
    kPDRUNCFG_PD_WDT_OSC = SYSCON_PDRUNCFG_WDTOSC_PD_MASK,
    kPDRUNCFG_PD_SYSPLL  = SYSCON_PDRUNCFG_SYSPLL_PD_MASK,
    kPDRUNCFG_PD_ACMP    = SYSCON_PDRUNCFG_ACMP_MASK,

    /*
    This enum member has no practical meaning,it is used to avoid MISRA issue,
    user should not trying to use it.
    */
    kPDRUNCFG_ForceUnsigned = (int)0x80000000U,
} pd_bit_t;

/*! @brief Deep sleep and power down mode wake up configurations */
enum _power_wakeup
{
    kPDAWAKECFG_Wakeup_IRC_OUT = SYSCON_PDAWAKECFG_IRCOUT_PD_MASK,
    kPDAWAKECFG_Wakeup_IRC     = SYSCON_PDAWAKECFG_IRC_PD_MASK,
    kPDAWAKECFG_Wakeup_FLASH   = SYSCON_PDAWAKECFG_FLASH_PD_MASK,
    kPDAWAKECFG_Wakeup_BOD     = SYSCON_PDAWAKECFG_BOD_PD_MASK,
    kPDAWAKECFG_Wakeup_ADC     = SYSCON_PDAWAKECFG_ADC_PD_MASK,
    kPDAWAKECFG_Wakeup_SYSOSC  = SYSCON_PDAWAKECFG_SYSOSC_PD_MASK,
    kPDAWAKECFG_Wakeup_WDT_OSC = SYSCON_PDAWAKECFG_WDTOSC_PD_MASK,
    kPDAWAKECFG_Wakeup_SYSPLL  = SYSCON_PDAWAKECFG_SYSPLL_PD_MASK,
    kPDAWAKECFG_Wakeup_ACMP    = SYSCON_PDAWAKECFG_ACMP_MASK,
};

/*! @brief Deep sleep/power down mode active part */
enum _power_deep_sleep_active
{
    kPDSLEEPCFG_DeepSleepBODActive    = SYSCON_PDSLEEPCFG_BOD_PD_MASK,
    kPDSLEEPCFG_DeepSleepWDTOscActive = SYSCON_PDSLEEPCFG_WDTOSC_PD_MASK,
};

/*! @brief pmu general purpose register index */
typedef enum _power_gen_reg
{
    kPmu_GenReg0 = 0U, /*!< general purpose register0 */
    kPmu_GenReg1 = 1U, /*!< general purpose register1 */
    kPmu_GenReg2 = 2U, /*!< general purpose register2 */
    kPmu_GenReg3 = 3U, /*!< general purpose register3 */
    kPmu_GenReg4 = 4U, /*!< DPDCTRL bit 31-4 */
} power_gen_reg_t;

/* Power mode configuration API parameter */
typedef enum _power_mode_config
{
    kPmu_Sleep          = 0U,
    kPmu_Deep_Sleep     = 1U,
    kPmu_PowerDown      = 2U,
    kPmu_Deep_PowerDown = 3U,
} power_mode_cfg_t;

/*!
 * @brief BOD reset level, if VDD below reset level value, the reset will be
 * asserted.
 */
typedef enum _power_bod_reset_level
{
    kBod_ResetLevelReserved = 0U, /*!< BOD Reset Level reserved. */
    kBod_ResetLevel1,             /*!< BOD Reset Level1: 2.05V */
    kBod_ResetLevel2,             /*!< BOD Reset Level2: 2.34V */
    kBod_ResetLevel3,             /*!< BOD Reset Level3: 2.63V */
} power_bod_reset_level_t;

/*!
 * @brief BOD interrupt level, if VDD below interrupt level value, the BOD interrupt
 * will be asserted.
 */
typedef enum _power_bod_interrupt_level
{
    kBod_InterruptLevelReserved = 0U, /*!< BOD interrupt level reserved. */
    kBod_InterruptLevel1,             /*!< BOD interrupt level1: 2.25V. */
    kBod_InterruptLevel2,             /*!< BOD interrupt level2: 2.54V. */
    kBod_InterruptLevel3,             /*!< BOD interrupt level3: 2.85V. */
} power_bod_interrupt_level_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @name SYSCON Power Configuration
 * @{
 */

/*!
 * @brief API to enable PDRUNCFG bit in the Syscon. Note that enabling the bit powers down the peripheral
 *
 * @param en    peripheral for which to enable the PDRUNCFG bit
 * @return none
 */
static inline void POWER_EnablePD(pd_bit_t en)
{
    SYSCON->PDRUNCFG |= (uint32_t)en;
}

/*!
 * @brief API to disable PDRUNCFG bit in the Syscon. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 * @return none
 */
static inline void POWER_DisablePD(pd_bit_t en)
{
    SYSCON->PDRUNCFG &= ~(uint32_t)en;
}

/*!
 * @brief API to config wakeup configurations for deep sleep mode and power down mode.
 *
 * @param mask: wake up configurations for deep sleep mode and power down mode, reference _power_wakeup.
 * @param powerDown: true is power down the mask part, false is powered part.
 */
static inline void POWER_WakeUpConfig(uint32_t mask, bool powerDown)
{
    if (powerDown)
    {
        SYSCON->PDAWAKECFG |= mask;
    }
    else
    {
        SYSCON->PDAWAKECFG &= ~mask;
    }
}

/*!
 * @brief API to config active part for deep sleep mode and power down mode.
 *
 * @param mask: active part configurations for deep sleep mode and power down mode, reference _power_deep_sleep_active.
 * @param powerDown: true is power down the mask part, false is powered part.
 */
static inline void POWER_DeepSleepConfig(uint32_t mask, bool powerDown)
{
    if (powerDown)
    {
        SYSCON->PDSLEEPCFG |= mask;
    }
    else
    {
        SYSCON->PDSLEEPCFG &= ~mask;
    }
}

/* @} */

/*!
 * @name ARM core Power Configuration
 * @{
 */

/*!
 * @brief API to enable deep sleep bit in the ARM Core.
 *
 * @return none
 */
static inline void POWER_EnableDeepSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/*!
 * @brief API to disable deep sleep bit in the ARM Core.
 *
 * @return none
 */
static inline void POWER_DisableDeepSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/* @} */

/*!
 * @name PMU functionality
 * @{
 */

/*!
 * @brief API to enter sleep power mode.
 *
 * @return none
 */
void POWER_EnterSleep(void);

/*!
 * @brief API to enter deep sleep power mode.
 *
 * @param activePart: should be a single or combine value of _power_deep_sleep_active .
 * @return none
 */
void POWER_EnterDeepSleep(uint32_t activePart);

/*!
 * @brief API to enter power down mode.
 *
 * @param activePart: should be a single or combine value of _power_deep_sleep_active .
 * @return none
 */
void POWER_EnterPowerDown(uint32_t activePart);

/*!
 * @brief API to enter deep power down mode.
 *
 * @return none
 */
void POWER_EnterDeepPowerDownMode(void);

/*!
 * @brief API to get sleep mode flag.
 *
 * @return sleep mode flag: 0 is active mode, 1 is sleep mode entered.
 */
static inline uint32_t POWER_GetSleepModeFlag(void)
{
    return (PMU->PCON & PMU_PCON_SLEEPFLAG_MASK) >> PMU_PCON_SLEEPFLAG_SHIFT;
}

/*!
 * @brief API to clear sleep mode flag.
 *
 */
static inline void POWER_ClrSleepModeFlag(void)
{
    PMU->PCON |= PMU_PCON_SLEEPFLAG_MASK;
}

/*!
 * @brief API to get deep power down mode flag.
 *
 * @return sleep mode flag: 0 not deep power down, 1 is deep power down mode entered.
 */
static inline uint32_t POWER_GetDeepPowerDownModeFlag(void)
{
    return (PMU->PCON & PMU_PCON_DPDFLAG_MASK) >> PMU_PCON_DPDFLAG_SHIFT;
}

/*!
 * @brief API to clear deep power down mode flag.
 *
 */
static inline void POWER_ClrDeepPowerDownModeFlag(void)
{
    PMU->PCON |= PMU_PCON_DPDFLAG_MASK;
}

/*!
 * @brief API to enable non deep power down mode.
 *
 * @param enable: true is enable non deep power down, otherwise disable.
 */
static inline void POWER_EnableNonDpd(bool enable)
{
    if (enable)
    {
        PMU->PCON |= PMU_PCON_NODPD_MASK;
    }
    else
    {
        PMU->PCON &= ~PMU_PCON_NODPD_MASK;
    }
}

/*!
 * @brief API to enable LPO.
 *
 * @param enable: true to enable LPO, false to disable LPO.
 */
static inline void POWER_EnableLPO(bool enable)
{
    if (enable)
    {
        PMU->DPDCTRL |= PMU_DPDCTRL_LPOSCEN_MASK;
    }
    else
    {
        PMU->DPDCTRL &= ~PMU_DPDCTRL_LPOSCEN_MASK;
    }
}

/*!
 * @brief API to enable LPO in deep power down mode.
 *
 * @param enable: true to enable LPO, false to disable LPO.
 */
static inline void POWER_EnableLPOInDeepPowerDownMode(bool enable)
{
    if (enable)
    {
        PMU->DPDCTRL |= PMU_DPDCTRL_LPOSCDPDEN_MASK;
    }
    else
    {
        PMU->DPDCTRL &= ~PMU_DPDCTRL_LPOSCDPDEN_MASK;
    }
}

/*!
 * @brief API to retore data to general purpose register which can be retain during deep power down mode.
 * Note the kPMU_GenReg4 can retore 3 byte data only, so the general purpose register can store 19bytes data.
 * @param index: general purpose data register index.
 * @param data: data to restore.
 */
static inline void POWER_SetRetainData(power_gen_reg_t index, uint32_t data)
{
    if (index <= kPmu_GenReg3)
    {
        PMU->GPREG[index] = data;
    }
    else
    {
        /* only 26 bits can store in GPDATA field */
        PMU->DPDCTRL = (PMU->DPDCTRL & (~PMU_DPDCTRL_GPDATA_MASK)) | PMU_DPDCTRL_GPDATA(data);
    }
}

/*!
 * @brief API to get data from general purpose register which retain during deep power down mode.
 * Note the kPMU_GenReg4 can retore 3 byte data only, so the general purpose register can store 19bytes data.
 * @param index: general purpose data register index.
 * @return data stored in the general purpose register.
 */
static inline uint32_t POWER_GetRetainData(power_gen_reg_t index)
{
    if (index == kPmu_GenReg4)
    {
        return (PMU->DPDCTRL & PMU_DPDCTRL_GPDATA_MASK) >> PMU_DPDCTRL_GPDATA_SHIFT;
    }

    return PMU->GPREG[index];
}

/*!
 * @brief API to enable external clock input for self wake up timer.
 *
 * @param enable: true is enable external clock input for self-wake-up timer, otherwise disable.
 * @param enHysteresis: true is enable Hysteresis for the pin, otherwise disable.
 */
static inline void POWER_EnableWktClkIn(bool enable, bool enHysteresis)
{
    PMU->DPDCTRL = (PMU->DPDCTRL & (~(PMU_DPDCTRL_WAKEUPCLKHYS_MASK | PMU_DPDCTRL_WAKECLKPAD_DISABLE_MASK))) |
                   PMU_DPDCTRL_WAKECLKPAD_DISABLE(enable) | PMU_DPDCTRL_WAKEUPCLKHYS(enHysteresis);
}

/*!
 * @brief API to enable wake up pin for deep power down mode.
 *
 * @param enable: true is enable, otherwise disable.
 * @param enHysteresis: true is enable Hysteresis for the pin, otherwise disable.
 */
static inline void POWER_EnableWakeupPinForDeepPowerDown(bool enable, bool enHysteresis)
{
    PMU->DPDCTRL = (PMU->DPDCTRL & (~(PMU_DPDCTRL_WAKEUPHYS_MASK | PMU_DPDCTRL_WAKEPAD_DISABLE_MASK))) |
                   PMU_DPDCTRL_WAKEPAD_DISABLE(!enable) | PMU_DPDCTRL_WAKEUPHYS(enHysteresis);
}

/*!
 * @brief Set Bod interrupt level and reset level.
 *
 * @param resetLevel BOD reset threshold level, please refer to @ref power_bod_reset_level_t.
 * @param interruptLevel BOD interrupt threshold level, please refer to @ref power_bod_interrupt_level_t.
 * @param enable Used to enable/disable the BOD interrupt and BOD reset.
 */
static inline void POWER_SetBodLevel(power_bod_reset_level_t resetLevel,
                                     power_bod_interrupt_level_t interruptLevel,
                                     bool enable)
{
    SYSCON->BODCTRL = SYSCON_BODCTRL_BODRSTLEV(resetLevel) | SYSCON_BODCTRL_BODINTVAL(interruptLevel) |
                      SYSCON_BODCTRL_BODRSTENA(enable);
}

/* @} */

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_POWER_H_ */
