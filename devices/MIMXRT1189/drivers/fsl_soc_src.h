/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SRC_H_
#define _FSL_SRC_H_

#include "fsl_common.h"

/*! @addtogroup soc_src */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SRC driver version 2.0.1. */
#define FSL_SRC_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*!
 * @brief System core.
 */
typedef enum _src_core_name
{
    kSRC_CM33Core = 0x1U, /*!< System Core CM33. */
    kSRC_CM7Core  = 0x2U, /*!< System Core CM7. */
} src_core_name_t;

/*!
 * @brief The enumeration of the boot fuse selection.
 */
typedef enum _src_boot_fuse_selection
{
    kSRC_SerialDownloaderBootFlow = 0U, /*!< The Boot flow jumps directly to the serial downloader. */
    kSRC_NormalBootFlow           = 1U  /*!< The Boot flow follows the Normal Boot flow. */
} src_boot_fuse_selection_t;

/*!
 * @brief The enumeration of global system reset sources.
 */
typedef enum _src_reset_source
{
    kSRC_Wdog1Reset           = 0U,  /*!< WDOG1 triggers the global system reset. */
    kSRC_Wdog2Reset           = 1U,  /*!< WDOG2 triggers the global system reset. */
    kSRC_Wdog3Reset           = 2U,  /*!< WDOG3 triggers the global system reset. */
    kSRC_Wdog4Reset           = 3U,  /*!< WODG4 triggers the global system reset. */
    kSRC_Wdog5Reset           = 4U,  /*!< WDOG5 triggers the global system reset. */
    kSRC_TempsenseReset       = 5U,  /*!< Tempsense trigggers the global system reset. */
    kSRC_SentinelReset        = 6U,  /*!< Sentiel trigggers the global system reset. */
    kSRC_JtagSoftwareReset    = 7U,  /*!< JTAG software triggers the global system reset. */
    kSRC_CM33LockUpReset      = 8U,  /*!< CM33 lockup triggers the global system reset. */
    kSRC_CM33RequestReset     = 9U,  /*!< CM33 request triggers the global system reset. */
    kSRC_CM7LockUpReset       = 10U, /*!< CM7 lockup triggers the global system reset. */
    kSRC_CM7RequestReset      = 11U, /*!< CM7 request triggers the global system reset. */
    kSRC_DcdcOverVoltageReset = 12U, /*!< DCDC over voltage triggers the global system reset. */
    kSRC_EcatResetOutputReset = 13U, /*!< EtherCAT reset output triggers the global system reset. */
} src_reset_source_t;

/*!
 * @brief The enumeration of reset status flags.
 */
enum _src_reset_status_flags
{
    kSRC_PORResetFlag             = 1UL << 0UL,  /*!< Reset is the result of POR. */
    kSRC_Wdog1ResetFlag           = 1UL << 1UL,  /*!< Reset is the result of watchdog1 time-out event. */
    kSRC_Wdog2ResetFlag           = 1UL << 2UL,  /*!< Reset is the result of watchdog2 time-out event. */
    kSRC_Wdog3ResetFlag           = 1UL << 3UL,  /*!< Reset is the result of watchdog3 time-out event. */
    kSRC_Wdog4ResetFlag           = 1UL << 4UL,  /*!< Reset is the result of watchdog4 time-out event. */
    kSRC_Wdog5ResetFlag           = 1UL << 5UL,  /*!< Reset is the result of watchdog5 time-out event. */
    kSRC_TempsenseResetFlag       = 1UL << 6UL,  /*!< Reset is the result of software reset from temperature sensor. */
    kSRC_SentinelResetFlag        = 1UL << 7UL,  /*!< Reset is the result of the Sentinel's reset event. */
    kSRC_JtagSoftwareResetFlag    = 1UL << 8UL,  /*!< Reset is the result of software reset from JTAG. */
    kSRC_CM33RequestResetFlag     = 1UL << 9UL,  /*!< Reset is the result of CM33 reset request. */
    kSRC_CM33LockUpResetFlag      = 1UL << 10UL, /*!< Reset is the result of CM33 CPU lockup. */
    kSRC_CM7RequestResetFlag      = 1UL << 11UL, /*!< Reset is the result of CM7 reset request. */
    kSRC_CM7LockUpResetFlag       = 1UL << 12UL, /*!< Reset is the result of CM7 CPU lockup. */
    kSRC_DcdcOverVoltageResetFlag = 1UL << 13UL, /*!< Reset is the result of DCDC over voltage. */
    kSRC_EcatResetOutputResetFlag = 1UL << 14UL, /*!< Reset is the result of ECAT reset output. */
    kSRC_IppResetFlag             = 1UL << 16UL, /*!< Reset is the result of chip PAD POR_B. */
};

/*!
 * @brief The enumeration of global system reset mode.
 */
typedef enum _src_reset_mode
{
    kSRC_ResetSystem      = 0x0U, /*!< Generate the global system reset. */
    kSRC_DoNotResetSystem = 0x1U, /*!< Do not generate the global system reset. */
} src_reset_mode_t;

/*!
 * @brief The index of each general purpose register.
 */
typedef enum _src_general_purpose_register_index
{
    kSRC_GeneralPurposeRegister0 = 0U, /*!< The index of General Purpose Register0. */
    kSRC_GeneralPurposeRegister1,      /*!< The index of General Purpose Register1. */
    kSRC_GeneralPurposeRegister2,      /*!< The index of General Purpose Register2. */
    kSRC_GeneralPurposeRegister3,      /*!< The index of General Purpose Register3. */
    kSRC_GeneralPurposeRegister4,      /*!< The index of General Purpose Register4. */
    kSRC_GeneralPurposeRegister5,      /*!< The index of General Purpose Register5. */
    kSRC_GeneralPurposeRegister6,      /*!< The index of General Purpose Register6. */
    kSRC_GeneralPurposeRegister7,      /*!< The index of General Purpose Register7. */
    kSRC_GeneralPurposeRegister8,      /*!< The index of General Purpose Register8. */
    kSRC_GeneralPurposeRegister9,      /*!< The index of General Purpose Register9. */
    kSRC_GeneralPurposeRegister10,     /*!< The index of General Purpose Register10. */
    kSRC_GeneralPurposeRegister11,     /*!< The index of General Purpose Register11. */
    kSRC_GeneralPurposeRegister12,     /*!< The index of General Purpose Register12. */
    kSRC_GeneralPurposeRegister13,     /*!< The index of General Purpose Register13. */
    kSRC_GeneralPurposeRegister14,     /*!< The index of General Purpose Register14. */
    kSRC_GeneralPurposeRegister15,     /*!< The index of General Purpose Register15. */
    kSRC_GeneralPurposeRegister16,     /*!< The index of General Purpose Register16. */
    kSRC_GeneralPurposeRegister17,     /*!< The index of General Purpose Register17. */
    kSRC_GeneralPurposeRegister18,     /*!< The index of General Purpose Register18. */
    kSRC_GeneralPurposeRegister19,     /*!< The index of General Purpose Register19. */
} src_general_purpose_register_index_t;

/*! @brief software power control step in power on/off sequence. */
typedef enum _src_power_ctrl_step
{
    kSRC_PDN_EdgelockHandshake = 0UL, /*!< Power down Edgelock handshake step. */
    kSRC_PDN_IsolationOn       = 1UL, /*!< Power down isolation on step. */
    kSRC_PDN_ResetAssert       = 2UL, /*!< Power down reset assert step. */
    kSRC_PDN_PowerSwitchOff    = 3UL, /*!< Power down power switch off step. */
    kSRC_PUP_PowerSwitchOn     = 4UL, /*!< Power up power switch on step. */
    kSRC_PUP_ResetRelease      = 5UL, /*!< Power up reset release step. */
    kSRC_PUP_IsolationOff      = 6UL, /*!< Power up isolation off step. */
    kSRC_PUP_EdgeLockHandshake = 7UL, /*!< Power up Edgelock handshake step. */
} src_power_ctrl_step_t;

/*!
 * @brief The power level of low power mode setting.
 */
typedef enum _src_power_level
{
    kSRC_PowerLevel1 = 0x1UL, /*! power on when domain n is in RUN, off in WAIT/STOP/SUSPEND */
    kSRC_PowerLevel2 = 0x2UL, /*! power on when domain n is in RUN/WAIT, off in STOP/SUSPEND */
    kSRC_PowerLevel3 = 0x3UL, /*! power on when domain n is in RUN/WAIT/STOP, off in SUSPEND */
    kSRC_PowerLevel4 = 0x4UL, /*! power always on */
} src_power_level_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Core Reset release
 * @{
 */

/*!
 * @brief Releases related core reset operation.
 *
 * The core reset will be held until the boot core to release it.
 *
 * @param base SRC peripheral base address.
 */
void SRC_ReleaseCM7(SRC_GENERAL_Type *base);

/*! @} */

/*!
 * @name Latched Boot Arguments Related Interfaces
 * @{
 */

/*!
 * @brief Gets Boot configuration.
 *
 * @param base SRC peripheral base address.
 * @return Boot configuration. Please refer to fusemap.
 */
static inline uint32_t SRC_GetBootConfig(SRC_GENERAL_Type *base)
{
    return base->SBMR1;
}

/*!
 * @brief Gets the latched state of the BOOT_MODE1 and BOOT_MODE0 signals.
 *
 * @param base SRC peripheral base address.
 * @return Boot mode. Please refer to the Boot mode pin setting section of System Boot.
 */
static inline uint8_t SRC_GetBootMode(SRC_GENERAL_Type *base)
{
    return (uint8_t)((base->SBMR2 & SRC_GENERAL_SBMR2_IPP_BOOT_MODE_MASK) >> SRC_GENERAL_SBMR2_IPP_BOOT_MODE_SHIFT);
}

/* ! @} */

/*!
 * @name Global System Related Interfaces
 * @{
 */

/*!
 * @brief Sets the reset mode of global system reset source.
 *
 * This function sets the selected mode of the input global system reset sources.
 *
 * @param base SRC peripheral base address.
 * @param resetSource The global system reset source. See @ref src_reset_source_t for more details.
 * @param resetMode The reset mode of each reset source. See @ref src_reset_mode_t for more details.
 */
void SRC_SetGlobalSystemResetMode(SRC_GENERAL_Type *base, src_reset_source_t resetSource, src_reset_mode_t resetMode);

/*!
 * @brief Gets global system reset status flags.
 *
 * @param base SRC peripheral base address.
 * @return The status of global system reset status. See @ref _src_reset_status_flags for more details.
 */
static inline uint32_t SRC_GetResetStatusFlags(SRC_GENERAL_Type *base)
{
    return base->SRSR;
}

/*!
 * @brief Clears the status of global reset.
 *
 * @param base SRC peripheral base address.
 * @param mask The reset status flag to be cleared. See @ref _src_reset_status_flags for more details.
 */
static inline void SRC_ClearGlobalSystemResetStatus(SRC_GENERAL_Type *base, uint32_t mask)
{
    base->SRSR = mask;
}

/*! @} */

/*!
 * @name General Purpose Registers Related Interfaces
 * @{
 */

/*!
 * @brief Sets value to general purpose registers.
 *
 * @param base SRC peripheral base address.
 * @param index The index of GPRx register array. Please refer to @ref src_general_purpose_register_index_t.
 * @param value Setting value for GPRx register.
 */
static inline void SRC_SetGeneralPurposeRegister(SRC_GENERAL_Type *base,
                                                 src_general_purpose_register_index_t index,
                                                 uint32_t value)
{
    base->GPR[index] = value;
}

/*!
 * @brief Gets the value from general purpose registers.
 *
 * @param base SRC peripheral base address.
 * @param index The index of GPRx register array. Please refer to @ref src_general_purpose_register_index_t.
 * @return The setting value for GPRx register.
 */
static inline uint32_t SRC_GetGeneralPurposeRegister(SRC_GENERAL_Type *base, src_general_purpose_register_index_t index)
{
    assert((uint8_t)index < (uint8_t)SRC_GENERAL_GPR_COUNT);

    return base->GPR[index];
}

/*!
 * @name SRC Mix Slice Related Interfaces
 * @{
 */

/*!
 * @brief Allows/disallows user mode access
 *
 * @param base SRC peripheral base address.
 * @param enable Used to control user mode access.
 *              - \b true Allow user mode access.
 *              - \b false Disallow user mode access.
 */
static inline void SRC_SLICE_AllowUserModeAccess(SRC_MIX_SLICE_Type *base, bool enable)
{
    if (enable)
    {
        base->AUTHEN_CTRL |= SRC_MIX_SLICE_AUTHEN_CTRL_TZ_USER_MASK;
    }
    else
    {
        base->AUTHEN_CTRL &= ~SRC_MIX_SLICE_AUTHEN_CTRL_TZ_USER_MASK;
    }
}

/*!
 * @brief Allows/disallows non secure mode access.
 *
 * @param base SRC peripheral base address.
 * @param enable Used to control non secure mode access.
 *              - \b true Allow non secure mode access.
 *              - \b false Disallow non secure mode access.
 */
static inline void SRC_SLICE_AllowNonSecureModeAccess(SRC_MIX_SLICE_Type *base, bool enable)
{
    if (enable)
    {
        base->AUTHEN_CTRL |= SRC_MIX_SLICE_AUTHEN_CTRL_TZ_NS_MASK;
    }
    else
    {
        base->AUTHEN_CTRL &= ~SRC_MIX_SLICE_AUTHEN_CTRL_TZ_NS_MASK;
    }
}

/*!
 * @brief Locks the setting of user mode access and non secure mode access.
 *
 * @note Once locked only reset can unlock related settings.
 *
 * @param base SRC peripheral base address.
 */
static inline void SRC_SLICE_LockAccessSetting(SRC_MIX_SLICE_Type *base)
{
    base->AUTHEN_CTRL |= SRC_MIX_SLICE_AUTHEN_CTRL_LOCK_TZ_MASK;
}

/*!
 * @brief Sets the domain ID white list for the selected slice.
 *
 * @param base SRC peripheral base address.
 * @param domainId The core to access registers, should be the OR'ed value of @ref src_core_name_t.
 */
static inline void SRC_SLICE_SetWhiteList(SRC_MIX_SLICE_Type *base, uint8_t domainId)
{
    base->AUTHEN_CTRL = (base->AUTHEN_CTRL & (~SRC_MIX_SLICE_AUTHEN_CTRL_WHITE_LIST_MASK)) |
                        SRC_MIX_SLICE_AUTHEN_CTRL_WHITE_LIST(domainId);
}

/*!
 * @brief Locks the value of white list.
 *
 * @note Once locked only reset can unlock related settings.
 *
 * @param base SRC peripheral base address.
 */
static inline void SRC_SLICE_LockWhiteList(SRC_MIX_SLICE_Type *base)
{
    base->AUTHEN_CTRL |= SRC_MIX_SLICE_AUTHEN_CTRL_LOCK_LIST_MASK;
}

/*!
 * brief Set software control step for slice power on/off sequence.
 *
 * param base SRC peripheral base address.
 * param step Slice power on/off sequence step. See @ref src_power_ctrl_step_t for more details.
 */

void SRC_SLICE_SoftwareControl(SRC_MIX_SLICE_Type *base, src_power_ctrl_step_t step);

/*!
 * brief Power on/off slice.
 *
 * param base SRC peripheral base address.
 * param powerOff Used to trigger slice power on/off sequence.
 *			   - \b true Trigger a power off sequence.
 *			   - \b false Trigger a power on sequence.
 */
void SRC_SLICE_PowerDown(SRC_MIX_SLICE_Type *base, bool powerOff);

void SRC_SLICE_ControlByCpuLowPowerMode(SRC_MIX_SLICE_Type *base, uint32_t domainMap, src_power_level_t level);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_SRC_H_ */
