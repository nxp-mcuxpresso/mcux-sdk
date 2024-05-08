/*
 * Copyright 2021-2022 NXP
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

/* Power Mode Index */
#define PM_LP_STATE_SLEEP           (0U)
#define PM_LP_STATE_DEEP_SLEEP      (1U)
#define PM_LP_STATE_POWER_DOWN      (2U)
#define PM_LP_STATE_DEEP_POWER_DOWN (3U)
#define PM_LP_STATE_NO_CONSTRAINT   (0xFFU)

/*! @} */

/*!
 * @name System basic resource constraints definitions.
 * @{
 */

/* Constraints used by application. */
/*!
 * @brief Set the constraint that CORE clock should be ON.
 */
#define PM_RESC_CORE_CLK_ON PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 13U)
/*!
 * @brief Set the constraint that BUS and SYSTEM clock should be ON.
 */
#define PM_RESC_BUS_SYS_CLK_ON PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 12U)

/*!
 * @brief Set the constraint that CTCM0 should in Active mode.
 */
#define PM_RESC_CTCM0_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 0U)
/*!
 * @brief Set the constraint that CTCM0 should in DEEPSLEEP mode.
 */
#define PM_RESC_CTCM0_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 0U)

/*!
 * @brief Set the constraints that CTCM0 should be powered off in all mode.
 */
#define PM_RESC_CTCM0_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 0U);

/*!
 * @brief Set the constraint that CTCM1 should in Active mode.
 */

#define PM_RESC_CTCM1_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 1U)
/*!
 * @brief Set the constraint that CTCM1 should in DEEPSLEEP mode.
 */
#define PM_RESC_CTCM1_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 1U)
/*!
 * @brief Set the constraint that CTCM1 should be powered off in all mode.
 */
#define PM_RESC_CTCM1_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 1U);

/*!
 * @brief Set the constraint that STCM0 should in Active mode.
 */
#define PM_RESC_STCM0_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 2U)
/*!
 * @brief Set the constraint that STCM0 should in DEEPSLEEP mode.
 */
#define PM_RESC_STCM0_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 2U)
/*!
 * @brief Set the constraint the STCM0 should be powered off in all mode.
 */
#define PM_RESC_STCM0_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 2U);

/*!
 * @brief Set the constraint that STCM1 should in Active mode.
 */
#define PM_RESC_STCM1_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 3U)
/*!
 * @brief Set the constraint that STCM1 should in DEEPSLEEP mode.
 */
#define PM_RESC_STCM1_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 3U)
/*!
 * @brief Set the constraint the STCM1 should be powered off in all mode.
 */
#define PM_RESC_STCM1_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 3U)

/*!
 * @brief Set the constraint that STCM2 should in Active mode.
 */
#define PM_RESC_STCM2_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 4U)
/*!
 * @brief Set the constraint that STCM2 should in DEEPSLEEP mode.
 */
#define PM_RESC_STCM2_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 4U)
/*!
 * @brief Set the constraint that STCM2 should be powered of in all modes.
 */
#define PM_RESC_STCM2_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 4U)

/*!
 * @brief Set the constraint that STCM3 should in Active mode.
 */
#define PM_RESC_STCM3_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 5U)
/*!
 * @brief Set the constraint that STCM3 should in DEEPSLEEP mode.
 */
#define PM_RESC_STCM3_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 5U)
/*!
 * @brief Set the constaint that STCM3 should be powered off in all modes.
 */
#define PM_RESC_STCM3_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 5U)

/*!
 * @brief Set the constraint that STCM4 should in Active mode.
 */
#define PM_RESC_STCM4_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 6U)
/*!
 * @brief Set the constraint that STCM4 should in DEEPSLEEP mode.
 */
#define PM_RESC_STCM4_DEEPSLEEP PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 6U)
/*!
 * @brief Set the constraint the STCM4 should be powered off in all modes.
 */
#define PM_RESC_STCM4_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 6U)

/*!
 * @brief Set the constraint that FRO_192M should be ON.
 */
#define PM_RESC_FRO_192M_ON PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 7U)
/*!
 * @brief Set the constraint that FRO_192M should be OFF.
 */
#define PM_RESC_FRO_192M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 7U)

/*!
 * @brief Set the constraint that FRO_6M should be ON.
 */
#define PM_RESC_FRO_6M_ON PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 8U)
/*!
 * @brief Set the constraint that FRO_6M should be OFF.
 */
#define PM_RESC_FRO_6M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, 8U)

/*!
 * @brief Set the constraint that peripherals in CORE_MAIN power domain still be operational.
 */
#define PM_RESC_MAIN_PD_PERI_OPERATIONAL PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 11U)

/*!
 * @brief Set the constraint that peripherals in CORE_MAIN power domain are state retention, that means
 * CORE_MAIN power domain can not be powered off.
 */
#define PM_RESC_MAIN_PD_PERI_STATE_RETENTION PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 10U)

/*!
 * @brief Set the constraint that peripherals in CORE_WAKE power domain are active.
 */
#define PM_RESC_WAKE_PD_PERI_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, 9U)
/*!
 * @brief Set the constraint that peripherals in CORE_WAKE power domain are operational.
 */
#define PM_RESC_WAKE_PD_PERI_OPERATIONAL PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON2, 9U)

/*!
 * @brief Set the constraint that peripherals in CORE_WAKE power domain are state retention, that means
 * CORE_WAKE power domain can not be powered off.
 */
#define PM_RESC_WAKE_PD_PERI_STATE_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, 9U)

/*! @} */

#if FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER

/*!
 * @name System Wakeup source definitions.
 * @{
 */

/*!
 * @brief Enable PTA0 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA0_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 0UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA0 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA0_Falling_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 0UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA0 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA0_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 0UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA2 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA2_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 1UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA2 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA2_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 1UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA2 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA2_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 1UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA4 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA4_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 2UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA4 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA4_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 2UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA4 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA4_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 2UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA17 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA17_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 3UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA17 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA17_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 3UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA17 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA17_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 3UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA19 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA19_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 4UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA19 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA19_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 4UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA19 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA19_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 4UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA21 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA21_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 5UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA21 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA21_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 5UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA21 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA21_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 5UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTA22 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTA22_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 6UL, PORTA_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTA22 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTA22_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 6UL, PORTA_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTA22 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTA22_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 6UL, PORTA_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC0 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC0_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 7UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC0 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC0_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 7UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC0 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC0_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 7UL, PORTC_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC1 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC1_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 8UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC1 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC1_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 8UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC1 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC1_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 8UL, PORTC_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC2 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC2_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 9UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC2 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC2_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 9UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC2 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC2_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 9UL, PORTC_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC4 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC4_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 10UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC4 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC4_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 10UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC4 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC4_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 10UL, PORTC_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC6 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC6_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 11UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC6 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC6_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 11UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC6 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC6_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 11UL, PORTC_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTC7 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTC7_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 12UL, PORTC_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTC7 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTC7_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 12UL, PORTC_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTC7 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTC7_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 12UL, PORTC_EFT_IRQns, 3UL)

/*!
 * @brief Enable PTB0 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTB0_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 13UL, PORTB_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTB0 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTB0_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 13UL, PORTB_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTB0 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTB0_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 13UL, PORTB_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTB3 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTB3_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 14UL, PORTB_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTB3 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTB3_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 14UL, PORTB_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTB3 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTB3_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 14UL, PORTB_EFT_IRQn, 3UL)

/*!
 * @brief Enable PTB4 as a wakeup pin, detect on rising edge.
 */
#define PM_WSID_PTB4_RISING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 15UL, PORTB_EFT_IRQn, 1UL)
/*!
 * @brief Enable PTB4 as a wakeup pin, detect on falling edge.
 */
#define PM_WSID_PTB4_FALLING_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 15UL, PORTB_EFT_IRQn, 2UL)
/*!
 * @brief Enable PTB4 as a wakeup pin, detect on any edge.
 */
#define PM_WSID_PTB4_ANY_EDGE PM_ENCODE_WAKEUP_SOURCE_ID(0UL, 15UL, PORTB_EFT_IRQn, 3UL)

/*!
 * @brief Enable LPTMR0 as a wakeup source.
 */
#define PM_WSID_LPTMR0 PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 0UL, LPTMR0_IRQn, 0UL)

/*!
 * @brief Enable LPTMR1 as a wakeup source.
 */
#define PM_WSID_LPTMR1 PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 0UL, LPTMR1_IRQn, 0UL)

/*!
 * @brief Enable GPIOD Low pins as wakeup source.
 */
#define PM_WSID_GPIOD_LOW PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 1UL, GPIOD_INT0_IRQn, 0UL)

/*!
 * @brief Enable GPIOD High pins as wakeup source.
 */
#define PM_WSID_GPIOD_HIGH PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 2UL, GPIOD_INT1_IRQn, 0UL)

/*!
 * @brief Enable VBAT module as wakeup source.
 */
#define PM_WSID_WFSPSD PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 4UL, VBAT_IRQn, 0UL)

/*!
 * @brief Enable RTC Alarm as wakeup source.
 */
#define PM_WSID_RTC_ALARM PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 6UL, RTC_Alarm_IRQn, 0UL)

/*!
 * @brief Enable RTC Second as wakeup source.
 */
#define PM_WSID_RTC_SECOND PM_ENCODE_WAKEUP_SOURCE_ID(1UL, 7UL, RTC_Second_IRQn, 0UL)

/*! @} */

#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*! @} */

#define PM_RESC_BUS_SYS_CLK_INDEX 12U
#endif /* _FSL_PM_DEVICE_H_ */
