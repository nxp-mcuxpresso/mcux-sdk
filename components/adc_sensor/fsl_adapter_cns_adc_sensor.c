/*
 * Copyright  2022, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_adapter_adc_sensor.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
typedef struct _hal_adc_sensor_state
{
    ADC_Type *adc;
    hal_adc_sensor_type_t type;
    hal_adc_sensor_conv_type_t curConvType;
    uint16_t curRefVoltMv;
    bool adcTriggered;
    hal_adc_sensor_ts_param_t tsParam;
    adc_config_t config;
} hal_adc_sensor_state_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static ADC_Type *const s_adcBases[] = ADC_BASE_PTRS;

/*******************************************************************************
 * Code
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
hal_adc_sensor_status_t HAL_AdcSensorInit(hal_adc_sensor_handle_t handle, const hal_adc_sensor_init_config_t *config)
{
    hal_adc_sensor_status_t status;
    hal_adc_sensor_state_t *state = (hal_adc_sensor_state_t *)handle;

    assert(state != NULL);
    assert(config != NULL);
    assert(config->type == kHAL_AdcSensorTypeCnsAdc);

    if (config->adcInstance >= ARRAY_SIZE(s_adcBases))
    {
        status = kStatus_HAL_AdcSensorInvalidParm;
    }
    else
    {
        memset(state, 0, sizeof(hal_adc_sensor_state_t));
        state->type         = config->type;
        state->adc          = s_adcBases[config->adcInstance];
        state->adcTriggered = false;
        state->curConvType  = kHAL_AdcSensorConvTypeInvalid;
        memcpy(&state->tsParam, &config->tsParam, sizeof(hal_adc_sensor_ts_param_t));

        if (config->adcInitConfigSize > 0)
        {
            assert(config->adcInitConfigSize == sizeof(adc_config_t));
            assert(config->adcInitConfig != NULL);
            memcpy(&state->config, config->adcInitConfig, sizeof(adc_config_t));
        }
        else
        {
            ADC_GetDefaultConfig(&state->config);
            state->config.clockDivider          = kADC_ClockDivider16;
            state->config.resolution            = kADC_Resolution16BitAudio;
            state->config.inputMode             = kADC_InputSingleEnded;
            state->config.conversionMode        = kADC_ConversionOneShot;
            state->config.enableInputGainBuffer = true;
            state->config.inputGain             = kADC_InputGain1;
            state->config.scanLength            = kADC_ScanLength_1;
            state->config.averageLength         = kADC_Average16;
        }
        state->config.enableADC = true;
        ADC_Init(state->adc, &state->config);

        if (ADC_DoAutoCalibration(state->adc, kADC_CalibrationVrefInternal) != kStatus_Success)
        {
            status = kStatus_HAL_AdcSensorError;
        }
        else
        {
            status = kStatus_HAL_AdcSensorSuccess;
        }
    }

    return status;
}

/*!
 * brief Deinitialize the HAL ADC sensor peripheral.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorDeinit(hal_adc_sensor_handle_t handle)
{
    hal_adc_sensor_state_t *state = (hal_adc_sensor_state_t *)handle;
    assert(state != NULL);

    if (state->adc != NULL)
    {
        ADC_StopConversion(state->adc);
        ADC_Deinit(state->adc);
    }
    memset(state, 0, sizeof(hal_adc_sensor_state_t));

    return kStatus_HAL_AdcSensorSuccess;
}

static hal_adc_sensor_status_t HAL_AdcSensorTriggerTemp(hal_adc_sensor_state_t *state,
                                                        const hal_adc_sensor_conv_config_t *config)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    hal_adc_sensor_reference_voltage_t vrefSrc;
    uint16_t vrefMv;
    uint16_t channel;

    if (config->refVoltSrc == kHAL_AdcSensorReferenceVoltageN)
    {
        vrefSrc = kHAL_AdcSensorReferenceVoltage1; /* internal 1.2V bandgap */
        vrefMv  = 1200U;
    }
    else
    {
        vrefSrc = config->refVoltSrc;
        vrefMv  = config->refVoltMv;
    }
    if (config->channel == HAL_ADC_SENSOR_CHANNEL_AUTO)
    {
#if !(defined(FSL_FEATURE_ADC_HAS_NO_SINGLEEND_TEMP_CHANNEL) && FSL_FEATURE_ADC_HAS_NO_SINGLEEND_TEMP_CHANNEL)
        channel = kADC_TEMPP;
#else
        channel = HAL_ADC_SENSOR_CHANNEL_AUTO; /* Invalid channel */
#endif
    }
    else
    {
        channel = config->channel;
    }
    if (channel > 15U)
    {
        status = kStatus_HAL_AdcSensorInvalidParm;
    }
    else
    {
        if (((state->adc->ADC_REG_ANA & ADC_ADC_REG_ANA_VREF_SEL_MASK) >> ADC_ADC_REG_ANA_VREF_SEL_SHIFT) !=
            (uint32_t)vrefSrc)
        {
            state->adc->ADC_REG_ANA =
                (state->adc->ADC_REG_ANA & ~ADC_ADC_REG_ANA_VREF_SEL_MASK) | ADC_ADC_REG_ANA_VREF_SEL(vrefSrc);
            if (ADC_DoAutoCalibration(state->adc, kADC_CalibrationVrefInternal) != kStatus_Success)
            {
                status = kStatus_HAL_AdcSensorError;
            }
        }
        state->curRefVoltMv = vrefMv;

        if (status == kStatus_HAL_AdcSensorSuccess)
        {
            if (state->curConvType != kHAL_AdcSensorConvTypeTemperature)
            {
                ADC_EnableTemperatureSensor(state->adc, true);
                ADC_SetTemperatureSensorMode(state->adc,
#if ((!(defined(FSL_FEATURE_ADC_HAS_NO_SINGLEEND_TEMP_CHANNEL) && FSL_FEATURE_ADC_HAS_NO_SINGLEEND_TEMP_CHANNEL)) || \
     (!(defined(FSL_FEATURE_ADC_HAS_NO_DIFFERENTIAL_TEMP_CHANNEL) &&                                                 \
        FSL_FEATURE_ADC_HAS_NO_DIFFERENTIAL_TEMP_CHANNEL)))
                                kADC_TSensorInternal
#else
                                kADC_TSensorExternal
                                );
#endif
                state->curConvType = kHAL_AdcSensorConvTypeTemperature;
            }

            ADC_ClearStatusFlags(state->adc, kADC_DataReadyInterruptFlag);
            ADC_SetScanChannel(state->adc, kADC_ScanChannel0, (adc_channel_source_t)channel);
            ADC_DoSoftwareTrigger(state->adc);
            state->adcTriggered = true;
        }
    }

    return status;
}

static hal_adc_sensor_status_t HAL_AdcSensorTriggerVolt(hal_adc_sensor_state_t *state,
                                                        const hal_adc_sensor_conv_config_t *config)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;

    if ((config->channel > 15U) || (config->refVoltSrc == kHAL_AdcSensorReferenceVoltageN))
    {
        status = kStatus_HAL_AdcSensorInvalidParm;
    }
    else
    {
        if (((state->adc->ADC_REG_ANA & ADC_ADC_REG_ANA_VREF_SEL_MASK) >> ADC_ADC_REG_ANA_VREF_SEL_SHIFT) !=
            (uint32_t)config->refVoltSrc)
        {
            state->adc->ADC_REG_ANA = (state->adc->ADC_REG_ANA & ~ADC_ADC_REG_ANA_VREF_SEL_MASK) |
                                      ADC_ADC_REG_ANA_VREF_SEL(config->refVoltSrc);
            if (ADC_DoAutoCalibration(state->adc, kADC_CalibrationVrefInternal) != kStatus_Success)
            {
                status = kStatus_HAL_AdcSensorError;
            }
        }
        state->curRefVoltMv = config->refVoltMv;

        if (status == kStatus_HAL_AdcSensorSuccess)
        {
            if (state->curConvType != kHAL_AdcSensorConvTypeVoltage)
            {
                ADC_EnableTemperatureSensor(state->adc, false);
                state->curConvType = kHAL_AdcSensorConvTypeVoltage;
            }

            ADC_ClearStatusFlags(state->adc, kADC_DataReadyInterruptFlag);
            ADC_SetScanChannel(state->adc, kADC_ScanChannel0, (adc_channel_source_t)config->channel);
            ADC_DoSoftwareTrigger(state->adc);
            state->adcTriggered = true;
        }
    }

    return status;
}

/*!
 * brief Software trigger the ADC to do a conversion.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param config A pointer to the adc conversion configuration structure
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorSwTrigger(hal_adc_sensor_handle_t handle,
                                               const hal_adc_sensor_conv_config_t *config)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    hal_adc_sensor_state_t *state  = (hal_adc_sensor_state_t *)handle;

    assert(state != NULL);
    assert(state->adc != NULL);
    assert(config != NULL);

    do
    {
        if (state->adcTriggered)
        {
            /* Conversion already ongoing and result not popped. */
            if (!config->forceConv)
            {
                status = kStatus_HAL_AdcSensorBusy;
                break;
            }
            ADC_StopConversion(state->adc);
            state->adcTriggered = false;
        }

        if (config->type == kHAL_AdcSensorConvTypeTemperature)
        {
            status = HAL_AdcSensorTriggerTemp(state, config);
        }
        else if (config->type == kHAL_AdcSensorConvTypeVoltage)
        {
            status = HAL_AdcSensorTriggerVolt(state, config);
        }
        else
        {
            assert(false);
        }
    } while (false);

    return status;
}

/*!
 * brief Check if the ADC conversion finished and data available.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @retval true The conversion data available.
 * @retval false The conversion data not available.
 */
bool HAL_AdcSensorDataReady(hal_adc_sensor_handle_t handle)
{
    hal_adc_sensor_state_t *state = (hal_adc_sensor_state_t *)handle;

    assert(state != NULL);
    assert(state->adc != NULL);

    return ((state->adc->ADC_REG_IRSR & ADC_ADC_REG_IRSR_RDY_RAW_MASK) == 0U) ? false : true;
}

static int16_t HAL_AdcSensorGetResult(hal_adc_sensor_state_t *state)
{
    uint32_t shift;
    int16_t result;

    switch (state->config.resolution)
    {
        case kADC_Resolution12Bit:
            shift = 4U;
            break;
        case kADC_Resolution14Bit:
            shift = 2U;
            break;
        default:
            shift = 0U;
            break;
    }

    result = (int16_t)(ADC_GetConversionResult(state->adc) & 0xFFFFU);

    return (result << shift);
}

/*!
 * brief Get the voltage of the ADC channel. Must follow a software trigger with kHAL_AdcSensorTypeVoltage.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param voltMv pointer to save calculated voltage in millivolts.
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorGetVoltage(hal_adc_sensor_handle_t handle, uint32_t *voltMv)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    hal_adc_sensor_state_t *state  = (hal_adc_sensor_state_t *)handle;
    int16_t result;

    assert(state != NULL);
    assert(state->adc != NULL);
    assert(voltMv != NULL);

    if (!state->adcTriggered)
    {
        status = kStatus_HAL_AdcSensorNotTriggered;
    }
    else if (state->curConvType != kHAL_AdcSensorConvTypeVoltage)
    {
        status = kStatus_HAL_AdcSensorNotTriggered;
    }
    else if (!HAL_AdcSensorDataReady(handle))
    {
        status = kStatus_HAL_AdcSensorNotReady;
    }
    else
    {
        result = HAL_AdcSensorGetResult(state);
        ADC_StopConversion(state->adc);
        state->adcTriggered = false;
        ADC_ClearStatusFlags(state->adc, kADC_DataReadyInterruptFlag);
        if (result < 0)
        {
            status = kStatus_HAL_AdcSensorError;
        }
        else
        {
            *voltMv = (state->curRefVoltMv * (uint32_t)result) / 32768U;
        }
    }

    return status;
}

/*!
 * brief Get the temperature of the on-chip temperature sensor. Must follow a software trigger with
 * kHAL_AdcSensorTypeTemperature.
 * @param handle same handle used in HAL_AdcSensorInit().
 * @param temper pointer to save calculated temperature.
 * @return kStatus_HAL_AdcSensorSuccess on success, others on failure.
 */
hal_adc_sensor_status_t HAL_AdcSensorGetTemperature(hal_adc_sensor_handle_t handle, float *temper)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    hal_adc_sensor_state_t *state  = (hal_adc_sensor_state_t *)handle;
    int16_t result;

    assert(state != NULL);
    assert(state->adc != NULL);
    assert(temper != NULL);

    if (!state->adcTriggered)
    {
        status = kStatus_HAL_AdcSensorNotTriggered;
    }
    else if (state->curConvType != kHAL_AdcSensorConvTypeTemperature)
    {
        status = kStatus_HAL_AdcSensorNotTriggered;
    }
    else if (!HAL_AdcSensorDataReady(handle))
    {
        status = kStatus_HAL_AdcSensorNotReady;
    }
    else
    {
        result = HAL_AdcSensorGetResult(state);
        ADC_StopConversion(state->adc);
        state->adcTriggered = false;
        ADC_ClearStatusFlags(state->adc, kADC_DataReadyInterruptFlag);
        *temper = ((float)result / state->tsParam.cnsAdcParam.gain) - state->tsParam.cnsAdcParam.offset;
    }

    return status;
}
