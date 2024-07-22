/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_UTILITY_H_
#define _BOARD_UTILITY_H_

/*! @brief ADC high resolution is used, single-ended 16-bit conversion. */
#define LPADC_USE_HIGH_RESOLUTION true
/*! @brief ADC used to monitor the temperature sensor. */
#define LPADC_BASE ADC0
/*! @brief ADC channel of the on-chip temperature sensor. */
#define LPADC_TEMPEATURE_SENSOR_CHANNEL 26U
/*! @brief ID for command in command buffer. */
#define LPADC_USER_CMDID 1U
/*! @brief ADC reference, for temperature sensor monitoring, VREFO voltage reference driven from the VREF block is the
 * best option. */
#define LPADC_REFERENCE_TEMPERATURE kLPADC_ReferenceVoltageAlt2
/*! @brief ADC reference, for battery voltage monitoring. */
#define LPADC_REFERENCE_BATTERY kLPADC_ReferenceVoltageAlt2
/*! @brief The slope factor for temperature sensor calculation. */
#define LPADC_TEMP_PARAMETER_A FSL_FEATURE_LPADC_TEMP_PARAMETER_A
/*! @brief The offset factorfor temperature sensor calculation. */
#define LPADC_TEMP_PARAMETER_B FSL_FEATURE_LPADC_TEMP_PARAMETER_B
/*! @brief The bandgap coefficent temperature sensor calculation. */
#define LPADC_TEMP_PARAMETER_ALPHA FSL_FEATURE_LPADC_TEMP_PARAMETER_ALPHA
/*! @brief ADC channel of the battery monitor. */
#define LPADC_BATTERY_MONITOR_CHANNEL 29U
/*! @brief The voltage of the full battery. */
#define LPADC_BATTERY_FULL_VOLTAGE 3.0f
/*! @brief The voltage of the empty battery. */
#define LPADC_BATTERY_EMPTY_VOLTAGE 1.8f

/*!
 * \brief  type definition for the adc trigger state
 *
 */
typedef enum
{
    BOARD_AdcTriggerNone,
    BOARD_AdcTriggerBattery,
    BOARD_AdcTriggerTemperature
} BOARD_AdcTriggerState;
/*!
 * brief Check if ADC driver is initialized.
 */
bool BOARD_IsAdcInitialized(void);

/*!
 * brief Init ADC driver.
 */
void BOARD_InitAdc(void);

/*!
 * brief Reset ADC initialized flag.
 */
void BOARD_DeinitAdc(void);

/*!
 * brief Do software trigger to conversion command.
 */
void BOARD_AdcSwTrigger(uint32_t channel);

/*!
 * brief Calculate the temperature of the on-chip temperature sensor.
 *
 * return The temperature in degree. ADC conversion is not ready if -273.15f is returned.
 */
float BOARD_GetTemperature(void);

/*!
 * brief Get battery level.
 *
 * return The battery level in percent.
 */
int8_t BOARD_GetBatteryLevel(void);

/*!
 * brief Save ADC driver context to static structure.
 *
 */
void BOARD_SaveAdcContext(void);

/*!
 * brief Restore ADC driver context with static structure.
 *
 */
void BOARD_RestoreAdcContext(void);

/*!
 * @}  end of FWK_Board_Utility addtogroup
 */
/*!
 * @}  end of FWK_Board_module addtogroup
 */
#endif
