/*
 * Copyright  2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_ADC_SENSOR_ADAPTER_H__
#define __HAL_ADC_SENSOR_ADAPTER_H__

/*!
 * @addtogroup ADC_Sensor_Adapter
 * @{
 */

/*******************************************************************************
 * Public macro
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
#define FSL_ADC_SENSOR_ADAPTER_VERSION (MAKE_VERSION(1, 0, 0)) /*!< Version 1.0.0. */
/*! @} */

/*! @brief Definition of ADC_SENSOR adapter handle size. */
#define HAL_ADC_SENSOR_HANDLE_SIZE (64U)

/*! @brief Definition of ADC_SENSOR automatically identified channel. */
#define HAL_ADC_SENSOR_CHANNEL_AUTO (0xFFFFU)

/*!
 * @brief Defines the adc_sensor handle
 *
 * This macro is used to define a 4 byte aligned adc_sensor handle.
 * Then use "(hal_adc_sensor_handle_t)name" to get the adc_sensor handle.
 *
 * The macro should be global and could be optional. You could also define adc_sensor handle by yourself.
 *
 * This is an example,
 * @code
 * ADC_SENSOR_HANDLE_DEFINE(adc_sensorHandle);
 * @endcode
 *
 * @param name The name string of the adc_sensor handle.
 */
#define HAL_ADC_SENSOR_HANDLE_DEFINE(name) \
    uint32_t name[((HAL_ADC_SENSOR_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The handle of ADC_SENSOR adapter. */
typedef void *hal_adc_sensor_handle_t;

/*! @brief The status of ADC_SENSOR adapter. */
typedef enum _hal_adc_sensor_status
{
    kStatus_HAL_AdcSensorSuccess      = kStatus_Success,                             /*!< Success */
    kStatus_HAL_AdcSensorError        = MAKE_STATUS(kStatusGroup_HAL_ADC_SENSOR, 1), /*!< Failed */
    kStatus_HAL_AdcSensorInvalidParm  = MAKE_STATUS(kStatusGroup_HAL_ADC_SENSOR, 2), /*!< Invalid parameter */
    kStatus_HAL_AdcSensorBusy         = MAKE_STATUS(kStatusGroup_HAL_ADC_SENSOR, 3), /*!< ADC busy */
    kStatus_HAL_AdcSensorNotTriggered = MAKE_STATUS(kStatusGroup_HAL_ADC_SENSOR, 4), /*!< Not triggered */
    kStatus_HAL_AdcSensorNotReady     = MAKE_STATUS(kStatusGroup_HAL_ADC_SENSOR, 5), /*!< Result not ready */
} hal_adc_sensor_status_t;

/*!
 * @brief Define enumeration of reference voltage source.
 *
 * The source differs between differnt devices. For detail information, need to check the SoC's specification.
 */
typedef enum _hal_adc_sensor_reference_voltage
{
    kHAL_AdcSensorReferenceVoltage0 = 0x0U, /*!< Option 0 setting. */
    kHAL_AdcSensorReferenceVoltage1 = 0x1U, /*!< Option 1 setting. */
    kHAL_AdcSensorReferenceVoltage2 = 0x2U, /*!< Option 2 setting. */
    kHAL_AdcSensorReferenceVoltage3 = 0x3U, /*!< Option 3 setting. */
    kHAL_AdcSensorReferenceVoltageN = 0xFU, /*!< Voltage not identified. */
} hal_adc_sensor_reference_voltage_t;

/*!
 * @brief Define enumeration of sensor type.
 */
typedef enum _hal_adc_sensor_type
{
    kHAL_AdcSensorTypeCnsAdc  = 0U, /*!< CNS_ADC. */
    kHAL_AdcSensorTypeLpAdc28 = 1U, /*!< 28nm LPADC. */
    kHAL_AdcSensorTypeLpAdc40 = 2U, /*!< 40nm LPADC. */
} hal_adc_sensor_type_t;

/*!
 * @brief Define enumeration of sensor conversion type.
 */
typedef enum _hal_adc_sensor_conv_type
{
    kHAL_AdcSensorConvTypeInvalid     = 0U, /*!< Invalid type. */
    kHAL_AdcSensorConvTypeVoltage     = 1U, /*!< Capture voltage. */
    kHAL_AdcSensorConvTypeTemperature = 2U, /*!< Capture temperature. */
} hal_adc_sensor_conv_type_t;

/*! @brief The temperature sensor converter parameters. */
typedef union _hal_adc_sensor_ts_param
{
    struct
    {
        float gain;
        float offset;
    } cnsAdcParam;
    struct
    {
        float slope;
        float intercept;
    } lpAdc28Param;
    struct
    {
        float a;
        float b;
        float alpha;
    } lpAdc40Param;
} hal_adc_sensor_ts_param_t;

/*! @brief The init config struct of adc sensor adapter. */
typedef struct _hal_adc_sensor_init_config
{
    hal_adc_sensor_type_t type;        /*!< ADC type */
    uint8_t adcInstance;               /*!< ADC instance */
    uint16_t adcInitConfigSize;        /*! ADC init config size in bytes */
    const void *adcInitConfig;         /*!< ADC configuration dedicated for ADC peripheral. */
    hal_adc_sensor_ts_param_t tsParam; /*!< Temperature sensor parameters, only used in temperature sensor case */
} hal_adc_sensor_init_config_t;

/*! @brief The conversion config struct of adc sensor adapter. */
typedef struct _hal_adc_sensor_conv_config
{
    bool forceConv;                  /*!< Stop previous conversion and force a new one */
    hal_adc_sensor_conv_type_t type; /*!< ADC sensor type */
    hal_adc_sensor_reference_voltage_t
        refVoltSrc;     /*!< Reference voltage source, can be kHAL_AdcSensorReferenceVoltageN for temperature sensor */
    uint16_t refVoltMv; /*!< Reference voltage in millivolts, optional for temperature sensor */
    uint16_t channel;   /*!< ADC channel for conversion, can be HAL_ADC_SENSOR_CHANNEL_AUTO for temperature sensor */
} hal_adc_sensor_conv_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Initialize the HAL ADC sensor peripheral.
 *
 * @param handle Pointer to point to a memory space of size #HAL_ADC_SENSOR_HANDLE_SIZE allocated by the caller.
 * You can define the handle in the following two ways:
 * #HAL_ADC_SENSOR_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_ADC_SENSOR_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param instance ADC instance number
 * @param config A pointer to the adc init configuration structure
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorInit(hal_adc_sensor_handle_t handle, const hal_adc_sensor_init_config_t *config);

/*!
 * brief Deinitialize the HAL ADC sensor peripheral.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorDeinit(hal_adc_sensor_handle_t handle);

/*!
 * brief Software trigger the ADC to do a conversion.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param config A pointer to the adc conversion configuration structure
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorSwTrigger(hal_adc_sensor_handle_t handle,
                                               const hal_adc_sensor_conv_config_t *config);

/*!
 * brief Check if the ADC conversion finished and data available.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @retval true The conversion data available.
 * @retval false The conversion data not available.
 */
bool HAL_AdcSensorDataReady(hal_adc_sensor_handle_t handle);

/*!
 * brief Get the voltage of the ADC channel. Must follow a software trigger with kHAL_AdcSensorTypeVoltage.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param voltMv pointer to save calculated voltage in millivolts.
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorGetVoltage(hal_adc_sensor_handle_t handle, uint32_t *voltMv);

/*!
 * brief Get the temperature of the on-chip temperature sensor. Must follow a software trigger with
 * kHAL_AdcSensorTypeTemperature.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param temper pointer to save calculated temperature.
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorGetTemperature(hal_adc_sensor_handle_t handle, float *temper);

/*!
 * @}  end of FWK_Board_Utility addtogroup
 */
/*!
 * @}  end of FWK_Board_module addtogroup
 */
#endif /* __HAL_ADC_SENSOR_ADAPTER_H__ */
