/*
 * Copyright 2023~2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pm_core.h"
#include "fsl_pm_device.h"

#include "fsl_pmu.h"
#include "fsl_pgmc.h"
#include "fsl_gpc.h"
#include "fsl_ssarc.h"
#include "fsl_dcdc.h"
#include "fsl_clock.h"
#include "fsl_soc_src.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

#define NA   31U
#define SP0  0U
#define SP1  1U
#define SP2  2U
#define SP3  3U
#define SP4  4U
#define SP5  5U
#define SP6  6U
#define SP7  7U
#define SP8  8U
#define SP9  9U
#define SP10 10U
#define SP11 11U
#define SP12 12U
#define SP13 13U
#define SP14 14U
#define SP15 15U

#if __CORTEX_M == 7
#define CURRENT_GPC_INSTANCE   GPC_CPU_MODE_CTRL_0
#define CURRENT_STBY_CORE_NAME kGPC_CM4Core

/*! @brief
 * Definition of power domains' setpoint map.
 */
#define PM_DEV_MEGAMIX_SETPOINT_MAP    (0xF800U) // MEGAMIX will be powered off from setpoint 11 to setpoint 15.
#define PM_DEV_DISPLAYMIX_SETPOINT_MAP (0xF800U) // DISPLAYMIX will be powered off from setpoint 11 to setpoint 15.
#define PM_DEV_WAKEUPMIX_SETPOINT_MAP  (0xF800U) // MEGAMIX will be powered off from setpoint 11 to setpoint 15.
#define PM_DEV_LPSRMIX_SETPOINT_MAP    (0x0000U) // LPSRMIX powered on for all setpoint.

/*!
 * @brief Definition of DCDC's setpoint map.
 */
#define PM_DEV_DCDC_ENABLE_SETPOINT_MAP (0x7FFU) // DCDC will be powered off from setpoint 11 to setpoint 15.
#define PM_DEV_DCDC_DIG_ENABLE_SETPOINT_MAP \
    (0x7FFU)                                        // DCDC_DIG will be powered off from setpoint 11 to
                                                    // setpoint 15.
#define PM_DEV_DCDC_LP_MODE_SETPOINT_MAP (0x0U)  // DCDC_LP_MODE will be disabled from all setpoint.
#define PM_DEV_DCDC_STANDBY_SETPOINT_MAP \
    (0x7FFU)                                        // DCDC standby mode will be disabled from setpoint 11 to
                                                    // setpoint 15.
#define PM_DEV_DCDC_LP_MODE_STANDBY_SETPOINT_MAP \
    (0x0U)                                          // Disable standby request from GPC to enter LP mode
                                                    // for all setpoints.S

/*!
 * @brief Definition of bandgap's setpoint map.
 *
 */
#define PM_DEV_BANDGAP_EN_SETPOINT_MAP      (0xFFFFU) // Bandgap is enabled for all setpoints.
#define PM_DEV_BANDGAP_STANDBY_SETPOINT_MAP (0xFFFFU) // Bandgap standby mode is disabled for all setpoints.

/*!
 * @brief Definition of FBB's setpoint map.
 */
#define PM_DEV_FBB_EN_SETPOINT_MAP      (0xEU)    // FBB is enabled from setpoint 1 to setpoint 3.
#define PM_DEV_FBB_STANDBY_SETPOINT_MAP (0xFFFFU) // FBB standby mode is disabled for all setpoints.

/*!
 * @brief Definition of RBBs' setpoint map.
 */
#define PM_DEV_RBB_SOC_EN_SETPOINT_MAP      (0x500U)  // RBB_SOC is enabled for setpoint 8 and setpoint 10.
#define PM_DEV_RBB_SOC_STANDBY_SETPOINT_MAP (0xFFFFU) // RBB_SOC standby mode is disabled for all setpoints.
#define PM_DEV_RBB_LPSR_EN_SETPOINT_MAP \
    (0x8500U) // RBB_LPSR is enabled for setpoint 8, setpoint10 and setpoint 15, ToDo.
#define PM_DEV_RBB_LPSR_STANDBY_SETPOINT_MAP (0xFFFFU) // RBB_LPSR standby mode is disabled for all setpoints.

/*!
 * @brief Definition of LDOs' setpoint map.
 */
#define PM_DEV_PLL_LDO_EN_SETPOINT_MAP      (0x7FU)   // PLL_LDO is enabled from setpoint 0 to setpoint 6.
#define PM_DEV_PLL_LDO_STANDBY_SETPOINT_MAP (0xFFFFU) // PLL_LDO standby mode is disabled for all setpoints.
#define PM_DEV_LPSR_ANA_LDO_EN_SETPOINT_MAP (0xF800U) // LPSR_ANA_DO is enabled from setpoint 11 to setpoint 15.
#define PM_DEV_LPSR_ANA_LDO_STANDBY_SETPOINT_MAP \
    (0xFFFFU)                                            // LPSR_ANA_LDO standby mode is disabled for all setpoints.
#define PM_DEV_LPSR_ANA_LDO_LP_MODE_SETPOINT_MAP \
    (0xFFFFU)                                            // LPSR_ANA_LDO lowpower mode is disabled for all setpoints.
#define PM_DEV_LPSR_ANA_LDO_TRACKING_EN_SETPOINT_MAP \
    ((uint32_t)(~PM_DEV_LPSR_ANA_LDO_EN_SETPOINT_MAP))            // LPSR_ANA_DO tracking is enabled
                                                         // from setpoint 0 to setpoint 10.
#define PM_DEV_LPSR_ANA_LDO_BYPASS_EN_SETPOINT_MAP \
    ((uint32_t)(~PM_DEV_LPSR_ANA_LDO_EN_SETPOINT_MAP))            // LPSR_ANA_DO bypass is enabled from
                                                         // setpoint 0 to setpoint 10.
#define PM_DEV_LPSR_DIG_LDO_EN_SETPOINT_MAP \
    (0xF81CU)                                             // LPSR_DIG_DO is enabled from setpoint 2 to setpoint 4,
                                                         // and setpoint 11 to setpoint 15.
#define PM_DEV_LPSR_DIG_LDO_STANDBY_SETPOINT_MAP (0xFFFFU) // LPSR_DIG_DO standby mode is disabled for all setpoints.
#define PM_DEV_LPSR_DIG_LDO_LP_MODE_SETPOINT_MAP \
    (0xFFFFU)                                 // LPSR_DIG_DO lowpower mode is disabled for all setpoints.
#define PM_DEV_LPSR_DIG_LDO_TRACKING_EN_SETPOINT_MAP \
    ((uint32_t)(~PM_DEV_LPSR_DIG_LDO_EN_SETPOINT_MAP)) // LPSR_DIG_DO tracking is enabled
                                              // from setpoint 0 to setpoint 1,
                                              // and setpoint 5 to setpoint 10.
#define PM_DEV_LPSR_DIG_LDO_BYPASS_EN_SETPOINT_MAP \
    ((uint32_t)(~PM_DEV_LPSR_DIG_LDO_EN_SETPOINT_MAP)) // LPSR_DIG_DO bypass is enabled from
                                              // setpoint 0 to setpoint 1,
                                              // and setpoint 5 to setpoint 10.

/* clang-format off */
#define PM_DEV_CM7_COMPATIBLE_SETPOINT_MAP                           \
{{NA , SP1, SP2, SP3, SP0, SP4, SP5, SP6, SP7, SP8, SP9, SP10, SP11, SP12, SP13, SP14, SP15}, \
{SP1 ,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP2 ,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP3 ,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP0 ,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP4 ,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP5 ,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP6 ,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP7 ,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,    0,    0,    0,    0,    0,    0}, \
{SP8 ,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,    0,    0,    0,    0,    0,    0}, \
{SP9 ,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    0,    0,    0,    0,    0,    0}, \
{SP10,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    0,    0,    0,    0,    0}, \
{SP11,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}, \
{SP12,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}, \
{SP13,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}, \
{SP14,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}, \
{SP15,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}}
/* clang-format on */

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
extern uint32_t __Vectors[];
#define PM_DEV_VECTOR_TABLE ((uint32_t)__Vectors)
#elif defined(__MCUXPRESSO)
extern uint32_t __Vectors[];
#define PM_DEV_VECTOR_TABLE ((uint32_t)__Vectors)
#elif defined(__ICCARM__)
extern uint32_t __VECTOR_TABLE[];
#define PM_DEV_VECTOR_TABLE ((uint32_t)__VECTOR_TABLE)
#elif defined(__GNUC__)
extern uint32_t __VECTOR_TABLE[];
#define PM_DEV_VECTOR_TABLE ((uint32_t)__VECTOR_TABLE)
#endif

#elif __CORTEX_M == 4

#define CURRENT_GPC_INSTANCE   GPC_CPU_MODE_CTRL_1
#define CURRENT_STBY_CORE_NAME kGPC_CM7Core

/* clang-format off */
    #define PM_DEV_CM4_COMPATIBLE_SETPOINT_MAP                           \
    {{NA , SP1, SP2, SP3, SP0, SP4, SP5, SP6, SP7, SP8, SP9, SP10, SP11, SP12, SP13, SP14, SP15}, \
    {SP1 ,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
    {SP2 ,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
    {SP3 ,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP0 ,   1,   1,   0,   1,   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0}, \
    {SP4 ,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP5 ,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP6 ,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP7 ,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP8 ,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,    0,    1,    0,    0,    0,    0}, \
    {SP9 ,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    0,    1,    0,    0,    0,    0}, \
    {SP10,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    0,    0,    0}, \
    {SP11,   1,   1,   0,   1,   0,   0,   0,   0,   0,   0,    0,    1,    0,    0,    0,    0}, \
    {SP12,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    0,    1,    1,    0,    0,    0}, \
    {SP13,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    0,    0}, \
    {SP14,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    0}, \
    {SP15,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,    1,    1,    1,    1,    1}}
/* clang-format on */
#endif /* __CORTEX_M */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if __CORTEX_M == 7
static inline void PM_DEV_SetClockSourcesControlBySetpoint(void);
static inline void PM_DEV_SetCore0PlatformSetpointMap(GPC_CPU_MODE_CTRL_Type *base);
static inline void PM_DEV_SetPowerDomainsControlBySetpoint(void);
static inline void PM_DEV_SetPowerSupplyControlBySetpoint(void);
static inline void PM_DEV_SetSRCControlMode(void);
static inline void PM_DEV_SetSetpointTransitionFlow(void);
static inline void PM_DEV_SetStandbyTransitionFlow(void);
#endif /* __CORTEX_M == 7 */

#if __CORTEX_M == 4
static inline void PM_DEV_SetCore1PlatformSetpointMap(GPC_CPU_MODE_CTRL_Type *base);
#endif /* __CORTEX_M == 4 */

static inline uint8_t PM_DEV_FindOperateMode(uint32_t rescIndex, pm_resc_group_t *pSysRescGroup);
static inline void PM_DEV_SetSleepTransitionFlow(void);

static void PM_DEV_PreparePowerSetting(void);
static void PM_DEV_EnterPowerState(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup);
#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable);
static bool PM_DEV_IsWakeupSource(pm_wakeup_source_t *ws);
#endif /* (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if __CORTEX_M == 7
extern const uint16_t g_clockSourceSpMapping[29U];
const uint16_t g_clockSourceSpMapping[29U] = {
    0xFFFFU, /*!< Clock Source OSCPLL0: 16MHz RC OSC output, turn on in all setpoints. */
    0x0000U, /*!< Clock Source OSCPLL1: 48MHz RC OSC output, turn off in all setpoints. */
    0x0000U, /*!< Clock Source OSCPLL2: 48MHz divide by 2 clock output, turn off in all setpoints. */
    0x7FFFU, /*!< Clock Source OSCPLL3: 400MHz RC OSC output, turn off in setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL4: Turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL5: 24MHz main output clock, turn off from setpoint 7 to setpoint 15. */
    0x1FU,   /*!< Clock Source OSCPLL6: Turn off from setpoint 5 to setpoint 15. */
    0x1FU,   /*!< Clock Source OSCPLL7: ARM PLL main output clock,
                 turn off from setpoint 5 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL8: Turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL9: SYS PLL2 main output clock,
                 turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL10: SYS PLL2 PFD0 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL11: SYS PLL2 PFD1 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL12: SYS PLL2 PFD2 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL13: SYS PLL2 PFD3 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL14: Turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL15 : SYS PLL3 main output clock,
                 turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL16: SYS PLL3 divided by 2 clock,
                 turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL17: SYS PLL3 PFD0 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL18: SYS PLL3 PFD1 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL19: SYS PLL3 PFD2 clock, turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL20: SYS PLL3 PFD3 clock, turn off from setpoint 7 to setpoint 15. */
    0xEU,    /*!< Clock Source OSCPLL21: Turn off in setpoint0 and from setpoint 4 to setpoint 15. */
    0xEU,    /*!< Clock Source OSCPLL22: System PLL1 main clock output, turn off in setpoint0 and from
             setpoint 4 to setpoint 15. */
    0xEU,    /*!< Clock Source OSCPLL23: System PLL1 divided by 2 clock , turn off in setpoint 0 and from
             setpoint 4 to setpoint 15. */
    0xEU,    /*!< Clock Source OSCPLL24: System PLL1 divided by 5 clock , turn off in setpoint 0 and from
             setpoint 4 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL25: Turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL26: Audio PLL main clock output,
                 turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL27: Turn off from setpoint 7 to setpoint 15. */
    0x7FU,   /*!< Clock Source OSCPLL28 : Video PLL main clock output,
                 turn off from setpoint 7 to setpoint 15. */
};

static dcdc_buck_mode_1P8_target_vol_t g_dcdcBuckMode1P8Voltage[16U] = {
    kDCDC_1P8BuckTarget1P8V, // setpoint 0
    kDCDC_1P8BuckTarget1P8V, // setpoint 1
    kDCDC_1P8BuckTarget1P8V, // setpoint 2
    kDCDC_1P8BuckTarget1P8V, // setpoint 3
    kDCDC_1P8BuckTarget1P8V, // setpoint 4
    kDCDC_1P8BuckTarget1P8V, // setpoint 5
    kDCDC_1P8BuckTarget1P8V, // setpoint 6
    kDCDC_1P8BuckTarget1P8V, // setpoint 7
    kDCDC_1P8BuckTarget1P8V, // setpoint 8
    kDCDC_1P8BuckTarget1P8V, // setpoint 9
    kDCDC_1P8BuckTarget1P8V, // setpoint 10
    kDCDC_1P8BuckTarget1P8V, // setpoint 11
    kDCDC_1P8BuckTarget1P8V, // setpoint 12
    kDCDC_1P8BuckTarget1P8V, // setpoint 13
    kDCDC_1P8BuckTarget1P8V, // setpoint 14
    kDCDC_1P8BuckTarget1P8V, // setpoint 15
};

static dcdc_standby_mode_1P8_target_vol_t g_dcdcStandby1P8Voltage[16U] = {
    kDCDC_1P8StbyTarget1P8V, // setpoint 0
    kDCDC_1P8StbyTarget1P8V, // setpoint 1
    kDCDC_1P8StbyTarget1P8V, // setpoint 2
    kDCDC_1P8StbyTarget1P8V, // setpoint 3
    kDCDC_1P8StbyTarget1P8V, // setpoint 4
    kDCDC_1P8StbyTarget1P8V, // setpoint 5
    kDCDC_1P8StbyTarget1P8V, // setpoint 6
    kDCDC_1P8StbyTarget1P8V, // setpoint 7
    kDCDC_1P8StbyTarget1P8V, // setpoint 8
    kDCDC_1P8StbyTarget1P8V, // setpoint 9
    kDCDC_1P8StbyTarget1P8V, // setpoint 10
    kDCDC_1P8StbyTarget1P8V, // setpoint 11
    kDCDC_1P8StbyTarget1P8V, // setpoint 12
    kDCDC_1P8StbyTarget1P8V, // setpoint 13
    kDCDC_1P8StbyTarget1P8V, // setpoint 14
    kDCDC_1P8StbyTarget1P8V, // setpoint 15
};

static dcdc_buck_mode_1P0_target_vol_t g_dcdcBuckMode1P0Voltage[16U] = {
    kDCDC_1P0BuckTarget1P0V, /*!< setpoint 0. */
    kDCDC_1P0BuckTarget1P1V, /*!< setpoint 1. */
    kDCDC_1P0BuckTarget1P1V, /*!< setpoint 2. */
    kDCDC_1P0BuckTarget1P1V, /*!< setpoint 3. */
    kDCDC_1P0BuckTarget1P0V, /*!< setpoint 4. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 5. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 6. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 7. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 8. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 9. */
    kDCDC_1P0BuckTarget0P8V, /*!< setpoint 10. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 11. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 12. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 13. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 14. */
    kDCDC_1P0BuckTarget0P9V, /*!< setpoint 15. */
};

static dcdc_standby_mode_1P0_target_vol_t g_dcdcStandby1P0Voltage[16U] = {
    kDCDC_1P0StbyTarget1P0V, /*!< setpoint 0. */
    kDCDC_1P0StbyTarget1P1V, /*!< setpoint 1. */
    kDCDC_1P0StbyTarget1P1V, /*!< setpoint 2. */
    kDCDC_1P0StbyTarget1P1V, /*!< setpoint 3. */
    kDCDC_1P0StbyTarget1P0V, /*!< setpoint 4. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 5. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 6. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 7. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 8. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 9. */
    kDCDC_1P0StbyTarget0P8V, /*!< setpoint 10. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 11. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 12. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 13. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 14. */
    kDCDC_1P0StbyTarget0P9V, /*!< setpoint 15. */
};

static const dcdc_setpoint_config_t g_dcdcSpConfig = {
    .enableDCDCMap              = PM_DEV_DCDC_ENABLE_SETPOINT_MAP,
    .enableDigLogicMap          = PM_DEV_DCDC_DIG_ENABLE_SETPOINT_MAP,
    .lowpowerMap                = PM_DEV_DCDC_LP_MODE_SETPOINT_MAP,
    .standbyMap                 = PM_DEV_DCDC_STANDBY_SETPOINT_MAP,
    .standbyLowpowerMap         = PM_DEV_DCDC_LP_MODE_STANDBY_SETPOINT_MAP,
    .buckVDD1P8TargetVoltage    = g_dcdcBuckMode1P8Voltage,
    .buckVDD1P0TargetVoltage    = g_dcdcBuckMode1P0Voltage,
    .standbyVDD1P8TargetVoltage = g_dcdcStandby1P8Voltage,
    .standbyVDD1P0TargetVoltage = g_dcdcStandby1P0Voltage,
};

static const pmu_lpsr_dig_target_output_voltage_t g_lpsrDigLdoTargetVoltage[16U] = {
    kPMU_LpsrDigTargetStableVoltage1P0V,   // setpoint 0, target voltage is 1.0V
    kPMU_LpsrDigTargetStableVoltage1P097V, // setpoint 1, target voltage is 1.097V
    kPMU_LpsrDigTargetStableVoltage1P0V,   // setpoint 2, target voltage is 1.0V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 3, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 4, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 5, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 6, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 7, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 8, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 9, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P806V, // setpoint 10, target voltage is 0.806V
    kPMU_LpsrDigTargetStableVoltage1P0V,   // setpoint 11, target voltage is 1.0V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 12, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P903V, // setpoint 13, target voltage is 0.903V
    kPMU_LpsrDigTargetStableVoltage0P806V, // setpoint 14, target voltage is 0.806V
    kPMU_LpsrDigTargetStableVoltage0P806V  // setpoint 15, target voltage is 0.806V
};
#endif                                     /* __CORTEX_M == 7 */

/*!
 * @brief State table for dual-core applications.
 */
const pm_device_option_t g_devicePMOption = {
    .states =
        {
            /* setpoint 0 */
            {
                .exitLatency = 6400UL, // From setpoint 0 standby suspend to setpoint 0 run mode.s
                /* In setpoint 0, following basic resources will be disabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2,
                 *  kResc_SYS_PLL1_DIV5, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO,
                 * kResc_LPSR_DIG_LDO
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3C0000CUL,
                        .rescMask[1] = 0x1D8UL,
                    },
                /*
                 * In setpoint 0, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 1 */
            {
                .exitLatency = 4760UL, // From setpoint 1 standby suspend to setpoint 1 RUN.
                /*
                 * In setpoint 1, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO,
                 *  kResc_LPSR_DIG_LDO
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xCUL,
                        .rescMask[1] = 0x198UL,
                    },
                /*
                 * In setpoint 1, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 2 */
            {
                .exitLatency = 4760UL,
                /*
                 * In setpoint 2, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xCUL,
                        .rescMask[1] = 0x188UL,
                    },
                /*
                 * In setpoint 2, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 3 */
            {
                .exitLatency = 6400UL,
                /*
                 * In setpoint 2, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xCUL,
                        .rescMask[1] = 0x188UL,
                    },
                /*
                 * In setpoint 3, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 4 */
            {
                .exitLatency = 6400UL,
                /*
                 * In setpoint 4, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2,
                 *  kResc_SYS_PLL1_DIV5, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3C0000CUL,
                        .rescMask[1] = 0x1C8UL,
                    },
                /*
                 * In setpoint 4, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 5 */
            {
                .exitLatency = 6960UL,
                /*
                 * In setpoint 5, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_ARM_PLL, kResc_ARM_PLL_CLK, kResc_SYS_PLL1,
                 *  kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5, kResc_FBB_M7, kResc_RBB_SOC,
                 *  kResc_RBB_LPSR, kResc_LPSR_ANA_LDO, kResc_LPSR_DIG_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3C0018CUL,
                        .rescMask[1] = 0x1D8UL,
                    },
                /*
                 * In setpoint 5, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 6 */
            {
                .exitLatency = 6400UL,
                /*
                 * In setpoint 6, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_ARM_PLL, kResc_ARM_PLL_CLK, kResc_SYS_PLL1,
                 *  kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5, kResc_FBB_M7, kResc_RBB_SOC,
                 *  kResc_RBB_LPSR, kResc_LPSR_ANA_LDO, kResc_LPSR_DIG_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3C0018CUL,
                        .rescMask[1] = 0x1D8UL,
                    },
                /*
                 * In setpoint 6, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 7 */
            {
                .exitLatency = 6400UL,
                /*
                 * In setpoint 7, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 * kResc_VIDEO_PLL_CLK，kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO,
                 * kResc_LPSR_DIG_LDO, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3FFFFFECUL,
                        .rescMask[1] = 0x5D8UL,
                    },
                /*
                 * In setpoint 7, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 8 */
            {
                .exitLatency = 64UL,
                /*
                 * In setpoint 8, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_LPSR_ANA_LDO, kResc_LPSR_DIG_LDO, kResc_PLL_LDO
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3FFFFFECUL,
                        .rescMask[1] = 0x458UL,
                    },
                /*
                 * In setpoint 8, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 9 */
            {
                .exitLatency = 6400UL,
                /*
                 * In setpoint 9, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 * kResc_VIDEO_PLL_CLK，kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_LPSR_ANA_LDO,
                 * kResc_LPSR_DIG_LDO, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3FFFFFECUL,
                        .rescMask[1] = 0x5D8UL,
                    },
                /*
                 * In setpoint 9, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 10 */
            {
                .exitLatency = 6740UL,
                /*
                 * In setpoint 10, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_LPSR_ANA_LDO, kResc_LPSR_DIG_LDO, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x3FFFFFECUL,
                        .rescMask[1] = 0x458UL,
                    },
                /*
                 * In setpoint 10, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 11 */
            {
                .exitLatency = 6740UL,
                /*
                 * In setpoint 11, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_DCDC, kResc_MEGA_MIX,
                 *  kResc_DISPLAY_MIX, kResc_WAKEUP_MIX, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFECUL,
                        .rescMask[1] = 0x5C5UL,
                    },
                /*
                 * In setpoint 11, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 12 */
            {
                .exitLatency = 6740UL,
                /*
                 * In setpoint 12, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_DCDC, kResc_MEGA_MIX,
                 *  kResc_DISPLAY_MIX, kResc_WAKEUP_MIX, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFECUL,
                        .rescMask[1] = 0x5C5UL,
                    },
                /*
                 * In setpoint 12, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 13 */
            {
                .exitLatency = 6740UL,
                /*
                 * In setpoint 13, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_DCDC, kResc_MEGA_MIX,
                 *  kResc_DISPLAY_MIX, kResc_WAKEUP_MIX, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFECUL,
                        .rescMask[1] = 0x5C5UL,
                    },
                /*
                 * In setpoint 13, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 14 */
            {
                .exitLatency = 6740UL,
                /*
                 * In setpoint 14, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_RBB_SOC, kResc_RBB_LPSR, kResc_DCDC, kResc_MEGA_MIX,
                 *  kResc_DISPLAY_MIX, kResc_WAKEUP_MIX, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFECUL,
                        .rescMask[1] = 0x5C5UL,
                    },
                /*
                 * In setpoint 14, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* setpoint 15 */
            {
                .exitLatency = 8000UL,
                /*
                 * In setpoint 15, following basic resources will be diabled:
                 *  kResc_OSC_RC_48M, kResc_OSC_RC_48M_DIV2, kResc_OSC_24M, kResc_OSC_24M_CLK, kResc_ARM_PLL,
                 *  kResc_ARM_PLL_CLK, kResc_SYS_PLL1, kResc_SYS_PLL1_CLK, kResc_SYS_PLL1_DIV2, kResc_SYS_PLL1_DIV5,
                 *  kResc_SYS_PLL2, kResc_SYS_PLL2_CLK, kResc_SYS_PLL2_PFD0, kResc_SYS_PLL2_PFD1, kResc_SYS_PLL2_PFD2,
                 *  kResc_SYS_PLL2_PFD3 kResc_SYS_PLL3, kResc_SYS_PLL3_CLK, kResc_SYS_PLL3_PFD0, kResc_SYS_PLL3_PFD1,
                 *  kResc_SYS_PLL3_PFD2, kResc_SYS_PLL3_PFD3, kResc_AUDIO_PLL, kResc_AUDIO_PLL_CLK, kResc_VIDEO_PLL,
                 *  kResc_VIDEO_PLL_CLK, kResc_FBB_M7, kResc_RBB_SOC, kResc_DCDC, kResc_MEGA_MIX, kResc_OSC_RC_400M,
                 *  kResc_DISPLAY_MIX, kResc_WAKEUP_MIX, kResc_PLL_LDO.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFFCUL,
                        .rescMask[1] = 0x4C5UL,
                    },
                /*
                 * In setpoint 15, following basic resources are optional, application can set this to different
                 * operation modes: kResc_CPU_PLATFORM, kResc_STBY_REQ. Please note in default, CPU platform will
                 * powered off, and standby request will be assert.
                 */
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x1UL,
                        .rescMask[1] = 0x200UL,
                    },
            },
            /* SNVS */
            {
                .exitLatency = 8540UL, // From SNVS mode to ROM exit.
                /*
                 * In SNVS mode, none of basic resources are retained.
                 */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xFFFFFFFFUL,
                        .rescMask[1] = 0x7FFUL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x0UL,
                        .rescMask[1] = 0x0UL,
                    },
            },
        },
    .stateCount = 17U,
    .prepare    = PM_DEV_PreparePowerSetting,
    .enter      = PM_DEV_EnterPowerState,
    .clean      = NULL,
#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    .manageWakeupSource = PM_DEV_ManageWakeupSource,
    .isWakeupSource     = PM_DEV_IsWakeupSource,
#endif /* (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) */
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Find operate mode to set.
 */
static inline uint8_t PM_DEV_FindOperateMode(uint32_t rescIndex, pm_resc_group_t *pSysRescGroup)
{
    uint32_t u32Tmp = (pSysRescGroup->groupSlice[rescIndex / 8UL] >> (4UL * (rescIndex % 8UL))) & 0xFUL;

    // Find first set, that is the operate mode to set.
    u32Tmp |= (u32Tmp >> 1U);
    u32Tmp |= (u32Tmp >> 2U);

    return (uint8_t)(uint32_t)((u32Tmp + 1UL) >> 1UL);
}

#if __CORTEX_M == 7
/*!

 * @brief Configure setpoint mapping for CM7.
 */
static inline void PM_DEV_SetCore0PlatformSetpointMap(GPC_CPU_MODE_CTRL_Type *base)
{
    uint8_t i, j;
    uint32_t u32Tmp;

    uint32_t coreSetpointMap[17U][17U] = PM_DEV_CM7_COMPATIBLE_SETPOINT_MAP;

    // Enable CPU sleep hold.
    GPC_CM_EnableCpuSleepHold(base, true);

    for (i = 1U; i < 17U; i++)
    {
        u32Tmp = 0UL;
        for (j = 1U; j < 17U; j++)
        {
            u32Tmp |= coreSetpointMap[i][j] << coreSetpointMap[0U][j];
        }
        GPC_CM_SetSetPointMapping(base, coreSetpointMap[i][0U], u32Tmp);
    }
}

/*!
 * @brief Set clock source controlled by setpoint, CM7 is responsible for set this.
 */
static inline void PM_DEV_SetClockSourcesControlBySetpoint(void)
{
    // 1. Clock sources implement setpoint control scheme.
    // Set OSC_PLL's control mode as software mode.
    ANADIG_OSC->OSC_16M_CTRL &= ~ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_MASK;
    ANADIG_OSC->OSC_48M_CTRL &=
        ~(ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_MASK | ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_MASK);
    ANADIG_OSC->OSC_24M_CTRL &= ~ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_MASK;
    ANADIG_OSC->OSC_400M_CTRL1 &= ~ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_MASK;
    ANADIG_PLL->ARM_PLL_CTRL &= ~ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_CONTROL_MODE_MASK;
    ANADIG_PLL->SYS_PLL1_CTRL &= ~(ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_CONTROL_MODE_MASK |
                                   ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_CONTROL_MODE_MASK |
                                   ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL3_CTRL &= ~(ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_CONTROL_MODE_MASK |
                                   ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL3_UPDATE &=
        ~(ANADIG_PLL_SYS_PLL3_UPDATE_PFD0_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL3_UPDATE_PFD1_CONTROL_MODE_MASK |
          ANADIG_PLL_SYS_PLL3_UPDATE_PDF2_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL3_UPDATE_PFD3_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL2_CTRL &= ~ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_CONTROL_MODE_MASK;
    ANADIG_PLL->SYS_PLL2_UPDATE &=
        ~(ANADIG_PLL_SYS_PLL2_UPDATE_PFD0_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL2_UPDATE_PFD1_CONTROL_MODE_MASK |
          ANADIG_PLL_SYS_PLL2_UPDATE_PFD2_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL2_UPDATE_PFD3_CONTROL_MODE_MASK);
    ANADIG_PLL->PLL_AUDIO_CTRL &= ~ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_CONTROL_MODE_MASK;
    ANADIG_PLL->PLL_VIDEO_CTRL &= ~ANADIG_PLL_PLL_VIDEO_CTRL_PLL_VIDEO_CONTROL_MODE_MASK;

    uint8_t clockSourceName = (uint8_t)kCLOCK_OscRc16M;
    for (clockSourceName = (uint8_t)kCLOCK_OscRc16M; clockSourceName <= (uint8_t)kCLOCK_VideoPllOut; clockSourceName++)
    {
        if (!CLOCK_OSCPLL_IsSetPointImplemented((clock_name_t)clockSourceName))
        {
            assert(0);
        }
        // keep clock source init state aligned with set point 0 state.
        if ((g_clockSourceSpMapping[(uint8_t)clockSourceName] & (uint16_t)0x1U) == (uint16_t)0U)
        {
            CCM->OSCPLL[(uint8_t)clockSourceName].DIRECT = 0;
        }
        else
        {
            CCM->OSCPLL[(uint8_t)clockSourceName].DIRECT = 1;
        }
        // All clock sources except OSC_RC 16M are turned off in standby mode.
        uint16_t standbyValue = 0U;
        if ((clock_name_t)clockSourceName == kCLOCK_OscRc16M)
        {
            standbyValue = 0xFFFFU;
        }
        CLOCK_OSCPLL_ControlBySetPointMode((clock_name_t)clockSourceName, g_clockSourceSpMapping[(uint8_t)clockSourceName],
                                           standbyValue);
    }

    //  2. Set clock sources work as hardware control mode.
    CLOCK_OSC_SetOsc16MControlMode(kCLOCK_GpcMode);
    CLOCK_OSC_SetOsc48MControlMode(kCLOCK_GpcMode);
    CLOCK_OSC_SetOsc48MDiv2ControlMode(kCLOCK_GpcMode);
    CLOCK_OSC_SetOsc24MControlMode(kCLOCK_GpcMode);
    CLOCK_OSC_SetOscRc400MControlMode(kCLOCK_GpcMode);
    ANADIG_PLL->ARM_PLL_CTRL |= ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_CONTROL_MODE_MASK;
    ANADIG_PLL->SYS_PLL1_CTRL |= (ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_CONTROL_MODE_MASK |
                                  ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_CONTROL_MODE_MASK |
                                  ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL3_CTRL |= (ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_CONTROL_MODE_MASK |
                                  ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL3_UPDATE |=
        (ANADIG_PLL_SYS_PLL3_UPDATE_PFD0_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL3_UPDATE_PFD1_CONTROL_MODE_MASK |
         ANADIG_PLL_SYS_PLL3_UPDATE_PDF2_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL3_UPDATE_PFD3_CONTROL_MODE_MASK);
    ANADIG_PLL->SYS_PLL2_CTRL |= ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_CONTROL_MODE_MASK;
    ANADIG_PLL->SYS_PLL2_UPDATE |=
        (ANADIG_PLL_SYS_PLL2_UPDATE_PFD0_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL2_UPDATE_PFD1_CONTROL_MODE_MASK |
         ANADIG_PLL_SYS_PLL2_UPDATE_PFD2_CONTROL_MODE_MASK | ANADIG_PLL_SYS_PLL2_UPDATE_PFD3_CONTROL_MODE_MASK);
    ANADIG_PLL->PLL_AUDIO_CTRL |= ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_CONTROL_MODE_MASK;
    ANADIG_PLL->PLL_VIDEO_CTRL |= ANADIG_PLL_PLL_VIDEO_CTRL_PLL_VIDEO_CONTROL_MODE_MASK;
}

/*!
 * @brief Set power domains controlled by setpoint, including MEGAMIX, DISPLAYMIX, and WANEMIX, CM7 is responsible for
 * set this
 */
static inline void PM_DEV_SetPowerDomainsControlBySetpoint(void)
{
    pgmc_bpc_setpoint_mode_option_t bpcSetpointOption = {
        .stateSave = false,
        .powerOff  = true,
    };
    //    a. MEGAMIX settings.
    PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC0, PM_DEV_MEGAMIX_SETPOINT_MAP, &bpcSetpointOption);
    //    b. DISPLAYMIX settings.
    PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC1, PM_DEV_DISPLAYMIX_SETPOINT_MAP, &bpcSetpointOption);
    //    c. WANEMIX settings.
    PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC2, PM_DEV_WAKEUPMIX_SETPOINT_MAP, &bpcSetpointOption);
    //    d. LPSRMIX settings.
    PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC3, PM_DEV_LPSRMIX_SETPOINT_MAP, &bpcSetpointOption);

    pgmc_bpc_cpu_power_mode_option_t bpcCpuModeOption = {
        .stateSave    = false,
        .assignDomain = kPGMC_CM7Core,
        .powerOff     = true,
    };

    // Maybe need to controlled by user?
    PGMC_BPC_ControlPowerDomainByCpuPowerMode(PGMC_BPC4, kPGMC_SuspendMode, &bpcCpuModeOption);
}

/*!
 * @brief Set power supply controlled by setpoint, including DCDC and internal LPSR LDOs, CM7 is responsible
 * for set this.
 */
static inline void PM_DEV_SetPowerSupplyControlBySetpoint(void)
{
    //    a. Set DCDC controlled by setpoint.
    DCDC_SetPointInit(DCDC, &g_dcdcSpConfig);
    if ((DCDC->CTRL0 & DCDC_CTRL0_CONTROL_MODE_MASK) == 0UL)
    {
        // Change to setpoint control mode.
        DCDC->CTRL0 |= DCDC_CTRL0_CONTROL_MODE_MASK;
    }

    //    b. Set LDOs in LPSR domain controlled by setpoint.
    //     i. Set PLL_LDO controlled by setpoint.
    PMU_GPCEnableLdo(kPMU_PllLdo, PM_DEV_PLL_LDO_EN_SETPOINT_MAP);
    PMU_GPCEnableLdoStandbyMode(kPMU_PllLdo, PM_DEV_PLL_LDO_STANDBY_SETPOINT_MAP);
    PMU_SetPllLdoControlMode(ANADIG_PMU, kPMU_GPCMode);

    //     ii. Set LPSR_DIG LDO controlled by setpoint

    PMU_GPCEnableLdo(kPMU_LpsrDigLdo, PM_DEV_LPSR_DIG_LDO_EN_SETPOINT_MAP);
    PMU_GPCEnableLdoStandbyMode(kPMU_LpsrDigLdo, PM_DEV_LPSR_DIG_LDO_STANDBY_SETPOINT_MAP);
    PMU_GPCSetLdoOperateMode(kPMU_LpsrDigLdo, PM_DEV_LPSR_DIG_LDO_LP_MODE_SETPOINT_MAP, kPMU_HighPowerMode);
    PMU_GPCEnableLdoTrackingMode(kPMU_LpsrDigLdo, PM_DEV_LPSR_DIG_LDO_TRACKING_EN_SETPOINT_MAP);
    PMU_GPCEnableLdoBypassMode(kPMU_LpsrDigLdo, PM_DEV_LPSR_DIG_LDO_BYPASS_EN_SETPOINT_MAP);
    for (uint8_t i = 0U; i < 16U; i++)
    {
        PMU_GPCSetLpsrDigLdoTargetVoltage(1UL << i, g_lpsrDigLdoTargetVoltage[i]);
    }
    PMU_SetLpsrDigLdoControlMode(ANADIG_LDO_SNVS, kPMU_GPCMode);

    //     iii. Set LPSR_ANA LDO controlled by setpoint.
    PMU_GPCEnableLdo(kPMU_LpsrAnaLdo, PM_DEV_LPSR_ANA_LDO_EN_SETPOINT_MAP);
    PMU_GPCEnableLdoStandbyMode(kPMU_LpsrAnaLdo, PM_DEV_LPSR_ANA_LDO_STANDBY_SETPOINT_MAP);
    PMU_GPCSetLdoOperateMode(kPMU_LpsrAnaLdo, PM_DEV_LPSR_ANA_LDO_LP_MODE_SETPOINT_MAP, kPMU_HighPowerMode);
    PMU_GPCEnableLdoTrackingMode(kPMU_LpsrAnaLdo, PM_DEV_LPSR_ANA_LDO_TRACKING_EN_SETPOINT_MAP);
    PMU_GPCEnableLdoBypassMode(kPMU_LpsrAnaLdo, PM_DEV_LPSR_ANA_LDO_BYPASS_EN_SETPOINT_MAP);
    PMU_SetLpsrAnaLdoControlMode(ANADIG_LDO_SNVS, kPMU_GPCMode);
}

/*!
 * @brief Set reset slices's control mode, CM7 is responsible for set this.
 */
static inline void PM_DEV_SetSRCControlMode(void)
{
    SRC_ClearGlobalSystemResetStatus(SRC, 0xFFFFFFFFUL);
    //    a. Reset slice corresponding to MEGA is controlled by setpoint.
    SRC_EnableSetPointTransferReset(SRC, kSRC_MegaSlice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_MegaSlice, PM_DEV_MEGAMIX_SETPOINT_MAP);
    //    b. Reset slice corresponding to DISPLAY is controlled by setpoint.
    SRC_EnableSetPointTransferReset(SRC, kSRC_DisplaySlice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_DisplaySlice, PM_DEV_DISPLAYMIX_SETPOINT_MAP);
    //    c. Reset slice corresponding to WAKEUP is controlled by setpoint.
    SRC_EnableSetPointTransferReset(SRC, kSRC_WakeUpSlice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_WakeUpSlice, PM_DEV_WAKEUPMIX_SETPOINT_MAP);
    //    d. Reset slice corresponding to LPSR is controlled by setpoint.
    SRC_EnableSetPointTransferReset(SRC, kSRC_LpsrSlice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_LpsrSlice, PM_DEV_LPSRMIX_SETPOINT_MAP);
    //    e. Reset slice corresponding to Cortex-M4 platform is controlled by entering of suspend mode.
    SRC_SetAssignList(SRC, kSRC_M4CoreSlice, (uint32_t)kSRC_CM4Core);
    SRC_SetSliceDomainModeConfig(SRC, kSRC_M4CoreSlice, (uint32_t)kSRC_Cpu1SuspendModeAssertReset);
    SRC_EnableDomainModeTransferReset(SRC, kSRC_M4CoreSlice, true);
    //    f. Reset slice corresponding to Cortex-M7 platform is controlled by entering of suspend mode.
    SRC_SetAssignList(SRC, kSRC_M7CoreSlice, (uint32_t)kSRC_CM7Core);
    SRC_SetSliceDomainModeConfig(SRC, kSRC_M7CoreSlice, (uint32_t)kSRC_Cpu0SuspendModeAssertReset);
    SRC_EnableDomainModeTransferReset(SRC, kSRC_M7CoreSlice, true);
    //    g. Reset slice corresponding to CM4 Debug is controlled by entering of suspend mode.
    SRC_SetAssignList(SRC, kSRC_M4DebugSlice, (uint32_t)kSRC_CM4Core);
    SRC_SetSliceDomainModeConfig(SRC, kSRC_M4DebugSlice, (uint32_t)kSRC_Cpu1SuspendModeAssertReset);
    SRC_EnableDomainModeTransferReset(SRC, kSRC_M4DebugSlice, true);
    //    h. Reset slice corresponding to CM7 Debug is controlled by entering of suspend mode.
    SRC_SetAssignList(SRC, kSRC_M7DebugSlice, (uint32_t)kSRC_CM7Core);
    SRC_SetSliceDomainModeConfig(SRC, kSRC_M7DebugSlice, (uint32_t)kSRC_Cpu0SuspendModeAssertReset);
    SRC_EnableDomainModeTransferReset(SRC, kSRC_M7DebugSlice, true);
    //    i. Reset slice corresponding to USBPHY1 and USBPHY2 is controlled by WAKEUP domain's setpoint request.
    SRC_EnableSetPointTransferReset(SRC, kSRC_Usbphy1Slice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_Usbphy1Slice, PM_DEV_WAKEUPMIX_SETPOINT_MAP);
    SRC_EnableSetPointTransferReset(SRC, kSRC_Usbphy2Slice, true);
    SRC_SetSliceSetPointConfig(SRC, kSRC_Usbphy2Slice, PM_DEV_WAKEUPMIX_SETPOINT_MAP);
}

/*!
 * @brief Set setpoint transition flow, CM7 is responsible for this.
 */
static inline void PM_DEV_SetSetpointTransitionFlow(void)
{
    gpc_tran_step_config_t transferStepConfig = {
        .stepCount  = 0UL,
        .cntMode    = kGPC_StepCounterDisableMode,
        .enableStep = false,
    };
    //   a. Disable SSARC Save.
    transferStepConfig.enableStep = false;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_SsarSave, &transferStepConfig);
    //   b. User can determine if LPCG controlled by CPU mode or controlled by setpoint.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_LpcgOff, &transferStepConfig);
    //   c. User can determine if CLOCK GROUP controlled by setpoint.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_GroupDown, &transferStepConfig);
    //   d. User can determine if CLOCK ROOT controlled by setpoint.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_RootDown, &transferStepConfig);
    //   e. Enable PLL off step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_PllOff, &transferStepConfig);
    //   f. Enable ISO.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_IsoOn, &transferStepConfig);
    //   g. Enable Reset early step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_ResetEarly, &transferStepConfig);
    //   h. Enable Power Off step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_PowerOff, &transferStepConfig);
    //   i. Enable Bias off step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_BiasOff, &transferStepConfig);
    //   j. Enable Bandgap and PLL_LDO off step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_BandgapPllLdoOff, &transferStepConfig);
    //   k. Enable LDO pre control step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_LdoPre, &transferStepConfig);
    //   l. Enable DCDC down step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_DcdcDown, &transferStepConfig);
    //   m. Enable DCDC Up step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_DcdcUp, &transferStepConfig);
    //   n. Enable LDO post control step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_LdoPost, &transferStepConfig);
    //   o. Enable Bandgap and PLL_LDO on step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_BandgapPllLdoOn, &transferStepConfig);
    //   p. Enable Bias on step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_BiasOn, &transferStepConfig);
    //   q. Enable Power On step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_PowerOn, &transferStepConfig);
    //   r. Enable Reset late step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_ResetLate, &transferStepConfig);
    //   s. Enable ISO.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_IsoOff, &transferStepConfig);
    //   t. Enable PLL on step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_PllOn, &transferStepConfig);
    //   u. Enable clock root up step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_RootUp, &transferStepConfig);
    //   v. Enable Clock Group up step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_GroupUp, &transferStepConfig);
    //   w. Enable Clock LPCG On step.
    transferStepConfig.enableStep = true;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_LpcgOn, &transferStepConfig);
    //   x. Disable SSARC Restore.
    transferStepConfig.enableStep = false;
    GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL, kGPC_SP_SsarRestore, &transferStepConfig);
}

/*!
 * @brief Set standby transition flow, CM7 is responsible for this.
 */
static inline void PM_DEV_SetStandbyTransitionFlow(void)
{
    gpc_tran_step_config_t transferStepConfig = {
        .stepCount  = 0UL,
        .cntMode    = kGPC_StepCounterDisableMode,
        .enableStep = false,
    };

    //   a. Enable LPCG is control step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_LpcgIn, &transferStepConfig);
    //   b. Enable PLL control step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PllIn, &transferStepConfig);
    //   c. Enable Bias In step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_BiasIn, &transferStepConfig);
    //   d. Enable PLDO In step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PldoIn, &transferStepConfig);
    //   e. Enable Bandgap In step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_BandgapIn, &transferStepConfig);
    //   f. Enable LDO In step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_LdoIn, &transferStepConfig);
    //   g. Enable DCDC In step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_DcdcIn, &transferStepConfig);
    //   h. Disable PMIC In step. TODO: Support PMIC board.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PmicIn, &transferStepConfig);
    //   i. Disable PMIC Out step. TODO: Support PMIC board.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PmicOut, &transferStepConfig);
    //   j. Enable DCDC Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_DcdcOut, &transferStepConfig);
    //   k. Enable LDO Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_LdoOut, &transferStepConfig);
    //   l. Enable Bandgap Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_BandgapOut, &transferStepConfig);
    //   m. Enable PLDO Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PldoOut, &transferStepConfig);
    //   n. Enable Bias Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_BiasOut, &transferStepConfig);
    //   o. Enable PLL Out step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_PllOut, &transferStepConfig);
    //   p. Enable/disable LPCG is control step.
    transferStepConfig.enableStep = true;
    GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL, kGPC_STBY_LpcgOut, &transferStepConfig);
}
#endif /* __CORTEX_M == 7 */

#if __CORTEX_M == 4
/*!
 * @brief Configure setpoint mapping for CM4.
 */
static inline void PM_DEV_SetCore1PlatformSetpointMap(GPC_CPU_MODE_CTRL_Type *base)
{
    uint8_t i, j;
    uint32_t u32Tmp;

    uint32_t coreSetpointMap[17U][17U] = PM_DEV_CM4_COMPATIBLE_SETPOINT_MAP;

    // Enable CPU sleep hold.
    GPC_CM_EnableCpuSleepHold(base, true);

    for (i = 1U; i < 17U; i++)
    {
        u32Tmp = 0UL;
        for (j = 1U; j < 17U; j++)
        {
            u32Tmp |= coreSetpointMap[i][j] << coreSetpointMap[0U][j];
        }
        GPC_CM_SetSetPointMapping(base, coreSetpointMap[i][0U], u32Tmp);
    }
}
#endif /* __CORTEX_M == 4 */

/*!
 * @brief Set CPU mode transition flow.
 */
static inline void PM_DEV_SetSleepTransitionFlow(void)
{
    gpc_tran_step_config_t transferStepConfig = {
        .stepCount  = 0UL,
        .cntMode    = kGPC_StepCounterDisableMode,
        .enableStep = false,
    };
    //    a. Disable Sleep SSARC control temporarily. TODO
    transferStepConfig.enableStep = false;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepSsar, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepSsar, &transferStepConfig);
#endif /* __CORTEX_M */
    //    b. User can determine if LPCG controlled by CPU mode or controlled by setpoint.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepLpcg, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepLpcg, &transferStepConfig);
#endif /* __CORTEX_M */
    //   c. Disable Sleep PLL control by cpu mode, it will be controlled by setpoint.
    transferStepConfig.enableStep = false;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepPll, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepPll, &transferStepConfig);
#endif /* __CORTEX_M */
    //    d. Enable Sleep ISO control by cpu mode, if CPU request to enter into suspend mode,
    //      related platform will be powered off.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepIso, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepIso, &transferStepConfig);
#endif /* __CORTEX_M */
    //    e. Enable Sleep RESET control.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepReset, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepReset, &transferStepConfig);
#endif /* __CORTEX_M */
    //    f. Enable Sleep POWER control, if CPU request to enter into suspend mode,
    //       related platform will be powered off.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_SleepPower, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_SleepPower, &transferStepConfig);
#endif /* __CORTEX_M */
    //    g. Enable Wakeup POWER control.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupPower, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupPower, &transferStepConfig);
#endif /* __CORTEX_M */
    //    h. Enable Wakeup RESET control.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupReset, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupReset, &transferStepConfig);
#endif /* __CORTEX_M */
    //    i. Enable Wakeup ISO control.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupIso, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupIso, &transferStepConfig);
#endif /* __CORTEX_M */
    //    j. Disable Wakeup PLL control by cpu mode, it will be controlled by setpoint.
    transferStepConfig.enableStep = false;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupPll, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupPll, &transferStepConfig);
#endif /* __CORTEX_M */
    //    k. Enable LPCG controlled by CPU mode.
    transferStepConfig.enableStep = true;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupLpcg, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupLpcg, &transferStepConfig);
#endif /* __CORTEX_M */
    //   l. Disable Wakeup SSARC control temporarily. TODO
    transferStepConfig.enableStep = false;
#if __CORTEX_M == 7
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_0, kGPC_CM_WakeupSsar, &transferStepConfig);
#elif __CORTEX_M == 4
    GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_1, kGPC_CM_WakeupSsar, &transferStepConfig);
#endif /* __CORTEX_M */
}

static void PM_DEV_PreparePowerSetting(void)
{
#if __CORTEX_M == 7
    // 1. Control clock sources via setpoint.
    PM_DEV_SetClockSourcesControlBySetpoint();

    // 2. Control power domains via setpoint.
    PM_DEV_SetPowerDomainsControlBySetpoint();

    // 3. Control power supply via setpoint.
    PM_DEV_SetPowerSupplyControlBySetpoint();

    // 4. Control bandgap via GPC, CM7 is responsible for this.
    PMU_GPCEnableBandgap(ANADIG_PMU, PM_DEV_BANDGAP_EN_SETPOINT_MAP);
    PMU_GPCEnableBandgapStandbyMode(ANADIG_PMU, PM_DEV_BANDGAP_STANDBY_SETPOINT_MAP);
    PMU_SetBandgapControlMode(ANADIG_PMU, kPMU_GPCMode);

    // 5. Control body bias via GPC, CM7 is responsible for this.
    /* Check if FBB need to be enabled in OverDrive(OD) mode.
       Note: FUSE could not be read out if OTP memory is powered off.*/
    if (((OCOTP->FUSEN[7].FUSE & 0x10UL) >> 4UL) != 1UL)
    {
        PMU_GPCEnableBodyBias(kPMU_FBB_CM7, PM_DEV_FBB_EN_SETPOINT_MAP);
    }
    else
    {
        PMU_GPCEnableBodyBias(kPMU_FBB_CM7, 0);
    }
    PMU_GPCEnableBodyBiasStandbyMode(kPMU_FBB_CM7, PM_DEV_FBB_STANDBY_SETPOINT_MAP);
    PMU_SetBodyBiasControlMode(ANADIG_PMU, kPMU_FBB_CM7, kPMU_GPCMode);

    PMU_GPCEnableBodyBias(kPMU_RBB_SOC, PM_DEV_RBB_SOC_EN_SETPOINT_MAP);
    PMU_GPCEnableBodyBiasStandbyMode(kPMU_RBB_SOC, PM_DEV_RBB_SOC_STANDBY_SETPOINT_MAP);
    PMU_SetBodyBiasControlMode(ANADIG_PMU, kPMU_RBB_SOC, kPMU_GPCMode);

    PMU_GPCEnableBodyBias(kPMU_RBB_LPSR, PM_DEV_RBB_LPSR_EN_SETPOINT_MAP);
    PMU_GPCEnableBodyBiasStandbyMode(kPMU_RBB_LPSR, PM_DEV_RBB_LPSR_STANDBY_SETPOINT_MAP);
    PMU_SetBodyBiasControlMode(ANADIG_PMU, kPMU_RBB_LPSR, kPMU_GPCMode);

    // 6. Set setpoint mapping for CM7 platforms.
    PM_DEV_SetCore0PlatformSetpointMap(GPC_CPU_MODE_CTRL_0);

    // 7. Configure SRC
    PM_DEV_SetSRCControlMode();

    // 8. Set setpoint transfer steps, CM7 is responsible for this.
    PM_DEV_SetSetpointTransitionFlow();

    // 9. Set standby request steps.
    PM_DEV_SetStandbyTransitionFlow();

    // 10. Save vector offset register.
    IOMUXC_LPSR_GPR->GPR26 &= ~IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_MASK;
    IOMUXC_LPSR_GPR->GPR26 |= IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR(PM_DEV_VECTOR_TABLE >> 7);

    // 11. Power off cpu platform when domain enters suspend mode.
    PGMC_CPC_CORE_PowerOffByCpuPowerMode(PGMC_CPC0, kPGMC_SuspendMode);

    // 12. Miscellaneous settings.
    /* SW should write 1 to OCOTP->PDN bit 0 to shut off power to the OTP memory and avoid unnecessary power wasting.
       Note: FUSE could not be read out if OTP memory is powered off. */
    OCOTP->PDN |= OCOTP_PDN_PDN_MASK;
    IOMUXC_SNVS_GPR->GPR37 |= IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE_MASK;
    /* CM7 SLEEPING is sent to GPC to start sleep sequence */
    IOMUXC_GPR->GPR16 |= IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL_MASK;
    /* CM4 SLEEPING is sent to GPC to start sleep sequence */
    IOMUXC_LPSR_GPR->GPR34 |= IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL_MASK;
#endif /* __CORTEX_M == 7 */

#if __CORTEX_M == 4
    // Set setpoint mapping for all core platforms.
    PM_DEV_SetCore1PlatformSetpointMap(GPC_CPU_MODE_CTRL_1);
    PGMC_CPC_CORE_PowerOffByCpuPowerMode(PGMC_CPC1, kPGMC_SuspendMode);
#endif

    // Set Sleep and WAKEUP steps.
    PM_DEV_SetSleepTransitionFlow();

    // Mask all wakeup interrupts by default for all platform.
    for (uint8_t i = 0U; i < 8U; i++)
    {
#if __CORTEX_M == 7
        GPC_CPU_MODE_CTRL_0->CM_IRQ_WAKEUP_MASK[i] = 0xFFFFFFFFUL;
#elif __CORTEX_M == 4
        GPC_CPU_MODE_CTRL_1->CM_IRQ_WAKEUP_MASK[i] = 0xFFFFFFFFUL;
#endif
    }

#if (defined(PM_PM_DUAL_CORE_USED) && (!PM_PM_DUAL_CORE_USED))
    // 12. In single core application, force unused core request to standby mode.
    GPC_STBY_ForceCoreRequestStandbyMode(GPC_STBY_CTRL, CURRENT_STBY_CORE_NAME);
#endif // PM_PM_DUAL_CORE_USED

    // TODO: Cpu mode trigger data saving by SSARC.
}

static void PM_DEV_EnterPowerState(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup)
{
    assert(pSoftRescMask != NULL);
    assert(pSysRescGroup != NULL);

    gpc_cpu_mode_t nextCpuMode = kGPC_SuspendMode;

    if (stateIndex == 16U)
    {
        // SNVS Mode, in this mode, only SNVS MIX is powered on, other domains are powered off
        SNVS->LPCR |= SNVS_LPCR_TOP_MASK;
    }
    else
    {
        // 1. Get CPU mode to transit based on application request.
        if ((pSoftRescMask->rescMask[0] & (1UL << kResc_CPU_PLATFORM)) != 0UL)
        {
            switch (PM_DEV_FindOperateMode((uint32_t)kResc_CPU_PLATFORM, pSysRescGroup))
            {
                case PM_RESOURCE_FULL_ON:
                    // In case of application request PM_RESC_CORE_DOMAIN_RUN.
                    nextCpuMode = kGPC_RunMode;
                    break;
                case PM_RESOURCE_PARTABLE_ON1:
                    // In case of application request PM_RESC_CORE_DOMAIN_WAIT.
                    nextCpuMode = kGPC_WaitMode;
                    break;
                case PM_RESOURCE_PARTABLE_ON2:
                    // In case of application request PM_RESC_CORE_DOMAIN_STOP.
                    nextCpuMode = kGPC_StopMode;
                    break;
                case PM_RESOURCE_OFF:
                    // In case of application request PM_RESC_CORE_DOMAIN_SUSPEND.
                    nextCpuMode = kGPC_SuspendMode;
                    break;
                default:
                    // To avoid violation of MISRA C-2012 Rule 15.7
                    assert(false);
                    break;
            }
        }
        else
        {
            // In case of no application request, CPU platform will be powered off.
            nextCpuMode = kGPC_SuspendMode;
        }
        GPC_CM_SetNextCpuMode(CURRENT_GPC_INSTANCE, nextCpuMode);

        // 2. Target setpoint is stateIndex, wakeup setpoint is current setpoint.
        if (nextCpuMode == kGPC_RunMode)
        {
            // Only need to switch setpoint.
            GPC_CM_RequestRunModeSetPointTransition(CURRENT_GPC_INSTANCE, stateIndex);
        }
        else
        {
            // Set to target setpoint in low power state, and then switch to previous setpoint.
            // For example, if current setpoint is 0, target setpoint is 10, system will switch into setpoint 10 when
            // CPU is low power mode and after waking from low power mode, system will back to setpoint 0 automatically.
            GPC_CM_RequestSleepModeSetPointTransition(CURRENT_GPC_INSTANCE, stateIndex, stateIndex,
                                                      kGPC_CM_RequestPreviousSetpoint);
        }

        if (nextCpuMode != kGPC_RunMode)
        {
            // 3. Request standby or not based on application request, if nextCPU mode is Run Mode, it is no need to
            //    request standby. In default, standby request will be assert to get lowest power consumption, and
            //    application can request to de-assert standby request to get better performance by set
            //    PM_STANDBY_REQ_OFF.

            // Clear all standby request before setting new standby request.
            GPC_CM_ClearStandbyModeRequest(CURRENT_GPC_INSTANCE, kGPC_WaitMode);
            GPC_CM_ClearStandbyModeRequest(CURRENT_GPC_INSTANCE, kGPC_StopMode);
            GPC_CM_ClearStandbyModeRequest(CURRENT_GPC_INSTANCE, kGPC_SuspendMode);

            if (PM_DEV_FindOperateMode((uint32_t)kResc_STBY_REQ, pSysRescGroup) != PM_RESOURCE_FULL_ON)
            {
                // If not request to de-assert standby request, assert standby request when CPU entering selected CPU
                // mode.
                GPC_CM_RequestStandbyMode(CURRENT_GPC_INSTANCE, nextCpuMode);
            }

            if (nextCpuMode == kGPC_WaitMode)
            {
                // Clear the SLEEPDEEP bit to go into sleep mode (WAIT)
                SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            }
            else
            {
                // Set the SLEEPDEEP bit to go into deep sleep mode (STOP and SUSPEND)
                SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            }
            __DSB();
            __ISB();
            __WFI();
        }
    }
}

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable)
{
    uint32_t irqId = 0UL;
    irqId          = PM_DECODE_WAKEUP_SOURCE_ID(ws->wsId);
    if (enable)
    {
        // Enabled selected wakeup source, including enable it in NVIC and GPC.
        (void)EnableIRQ((IRQn_Type)irqId);
        GPC_CM_EnableIrqWakeup(CURRENT_GPC_INSTANCE, irqId, true);
    }
    else
    {
        // Disable selected wakeup source, including disable it in NVIC and GPC.
        (void)DisableIRQ((IRQn_Type)irqId);
        GPC_CM_EnableIrqWakeup(CURRENT_GPC_INSTANCE, irqId, false);
    }

    return kStatus_Success;
}

static bool PM_DEV_IsWakeupSource(pm_wakeup_source_t *ws)
{
    uint32_t irqId = 0UL;
    bool ret       = false;

    irqId = PM_DECODE_WAKEUP_SOURCE_ID(ws->wsId);
    ret   = GPC_CM_GetIrqWakeupStatus(CURRENT_GPC_INSTANCE, irqId);

    return ret;
}
#endif /* (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) */
