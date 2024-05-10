/*
 * Copyright  2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpadc.h"
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
    lpadc_config_t config;
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
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    hal_adc_sensor_state_t *state  = (hal_adc_sensor_state_t *)handle;

    assert(state != NULL);
    assert(config != NULL);
    assert((config->type == kHAL_AdcSensorTypeLpAdc28) || (config->type == kHAL_AdcSensorTypeLpAdc40));

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
            assert(config->adcInitConfigSize == sizeof(lpadc_config_t));
            assert(config->adcInitConfig != NULL);
            memcpy(&state->config, config->adcInitConfig, sizeof(lpadc_config_t));
        }
        else
        {
            LPADC_GetDefaultConfig(&state->config);
            state->config.enableAnalogPreliminary = false;
            state->config.powerLevelMode          = kLPADC_PowerLevelAlt1;
            state->config.referenceVoltageSource  = kLPADC_ReferenceVoltageAlt1;
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
            state->config.conversionAverageMode = kLPADC_ConversionAverage128;
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */
#if defined(FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE)
            state->config.FIFO0Watermark = FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE - 1U;
#endif /* FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE */
        }
        LPADC_Init(state->adc, &state->config);

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS
#if defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM
        /* Request offset calibration. */
        LPADC_DoOffsetCalibration(state->adc);
#endif /* FSL_FEATURE_LPADC_HAS_OFSTRIM */
        /* Request gain calibration. */
        LPADC_DoAutoCalibration(state->adc);
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFS */
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
        LPADC_Deinit(state->adc);
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
    lpadc_conv_command_config_t cmdCfg;
    lpadc_conv_trigger_config_t trgCfg;

    if (config->refVoltSrc == kHAL_AdcSensorReferenceVoltageN)
    {
        vrefSrc = state->type == kHAL_AdcSensorTypeLpAdc28 ? kHAL_AdcSensorReferenceVoltage0 :
                                                             kHAL_AdcSensorReferenceVoltage1;
        vrefMv  = state->type == kHAL_AdcSensorTypeLpAdc28 ? 1800U : 3300U;
    }
    else
    {
        vrefSrc = config->refVoltSrc;
        vrefMv  = config->refVoltMv;
    }

    if (config->channel == HAL_ADC_SENSOR_CHANNEL_AUTO)
    {
        channel = state->type == kHAL_AdcSensorTypeLpAdc28 ? 7U : 26U;
    }
    else
    {
        channel = config->channel;
    }

    if (((state->adc->CFG & ADC_CFG_REFSEL_MASK) >> ADC_CFG_REFSEL_SHIFT) != (uint32_t)vrefSrc)
    {
        LPADC_Enable(state->adc, false);
        state->adc->CFG = (state->adc->CFG & ~ADC_CFG_REFSEL_MASK) | ADC_CFG_REFSEL(vrefSrc);
        LPADC_Enable(state->adc, true);
    }
    state->curRefVoltMv = vrefMv;
    state->curConvType  = kHAL_AdcSensorConvTypeTemperature;

    /* Set conversion CMD configuration. */
    LPADC_GetDefaultConvCommandConfig(&cmdCfg);
    cmdCfg.channelNumber = channel;
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_DIFF) && FSL_FEATURE_LPADC_HAS_CMDL_DIFF
    cmdCfg.sampleChannelMode = kLPADC_SampleChannelDiffBothSideAB;
#elif defined(FSL_FEATURE_LPADC_HAS_CMDL_CTYPE) && FSL_FEATURE_LPADC_HAS_CMDL_CTYPE
    cmdCfg.sampleChannelMode = kLPADC_SampleChannelDiffBothSide;
#endif
    cmdCfg.sampleTimeMode      = kLPADC_SampleTimeADCK131;
    cmdCfg.hardwareAverageMode = kLPADC_HardwareAverageCount128;
#if defined(FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE)
    cmdCfg.loopCount = FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE - 1U;
#endif /* FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE */
    state->adc->FCTRL[0] = ADC_FCTRL_FWMARK(cmdCfg.loopCount);
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
    cmdCfg.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_MODE */
    LPADC_SetConvCommandConfig(state->adc, 1U, &cmdCfg);

    /* Set trigger configuration. */
    LPADC_GetDefaultConvTriggerConfig(&trgCfg);
    trgCfg.targetCommandId = 1U;
    LPADC_SetConvTriggerConfig(state->adc, 0U, &trgCfg); /* Configurate the trigger0. */

    LPADC_DoSoftwareTrigger(state->adc, 1U);             /* 1U is trigger0 mask. */
    state->adcTriggered = true;

    return status;
}

static hal_adc_sensor_status_t HAL_AdcSensorTriggerVolt(hal_adc_sensor_state_t *state,
                                                        const hal_adc_sensor_conv_config_t *config)
{
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;
    lpadc_conv_command_config_t cmdCfg;
    lpadc_conv_trigger_config_t trgCfg;

    if (config->refVoltSrc == kHAL_AdcSensorReferenceVoltageN)
    {
        status = kStatus_HAL_AdcSensorInvalidParm;
    }
    else
    {
        if (((state->adc->CFG & ADC_CFG_REFSEL_MASK) >> ADC_CFG_REFSEL_SHIFT) != (uint32_t)config->refVoltSrc)
        {
            LPADC_Enable(state->adc, false);
            state->adc->CFG = (state->adc->CFG & ~ADC_CFG_REFSEL_MASK) | ADC_CFG_REFSEL(config->refVoltSrc);
            LPADC_Enable(state->adc, true);
        }
        state->curRefVoltMv = config->refVoltMv;
        state->curConvType  = kHAL_AdcSensorConvTypeVoltage;

        /* Set conversion CMD configuration. */
        LPADC_GetDefaultConvCommandConfig(&cmdCfg);
        cmdCfg.channelNumber       = config->channel;
        cmdCfg.sampleChannelMode   = kLPADC_SampleChannelSingleEndSideA;
        cmdCfg.sampleTimeMode      = kLPADC_SampleTimeADCK3;
        cmdCfg.hardwareAverageMode = kLPADC_HardwareAverageCount1;
        cmdCfg.loopCount           = 0U;
        state->adc->FCTRL[0]       = ADC_FCTRL_FWMARK(cmdCfg.loopCount);
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
        cmdCfg.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_MODE */
        LPADC_SetConvCommandConfig(state->adc, 1U, &cmdCfg);

        /* Set trigger configuration. */
        LPADC_GetDefaultConvTriggerConfig(&trgCfg);
        trgCfg.targetCommandId = 1U;
        LPADC_SetConvTriggerConfig(state->adc, 0U, &trgCfg); /* Configurate the trigger0. */

        LPADC_DoSoftwareTrigger(state->adc, 1U);             /* 1U is trigger0 mask. */
        state->adcTriggered = true;
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
            LPADC_Enable(state->adc, false);
            state->adcTriggered = false;
            LPADC_Enable(state->adc, true);
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

    return ((state->adc->STAT & ADC_STAT_RDY0_MASK) == 0U) ? false : true;
}

static bool HAL_AdcSensorGetResult(hal_adc_sensor_state_t *state, int16_t *result)
{
    lpadc_conv_result_t convRes;
    bool ret;

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    ret = LPADC_GetConvResult(state->adc, &convRes, 0);
#else
    ret                      = LPADC_GetConvResult(state->adc, &convRes);
#endif

    if (ret)
    {
        *result = (int16_t)convRes.convValue;
    }

    return ret;
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
    bool ret;

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
        ret                 = HAL_AdcSensorGetResult(state, &result);
        state->adcTriggered = false;
        if ((!ret) || (result < 0))
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

static hal_adc_sensor_status_t HAL_AdcSensorCalcTemper(hal_adc_sensor_state_t *state, float *temper)
{
    bool ret;
    int16_t result, vbe1, vbe8;
    hal_adc_sensor_status_t status = kStatus_HAL_AdcSensorSuccess;

    if (state->type == kHAL_AdcSensorTypeLpAdc28)
    {
        ret = HAL_AdcSensorGetResult(state, &result);
        if (!ret)
        {
            status = kStatus_HAL_AdcSensorError;
        }
        else
        {
            *temper = (((float)(result >> 3) * state->curRefVoltMv / 4096U) - state->tsParam.lpAdc28Param.intercept) /
                      state->tsParam.lpAdc28Param.slope;
        }
    }
    else if (state->type == kHAL_AdcSensorTypeLpAdc40)
    {
#if defined(FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE) && (FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE > 2U)
        /* For best temperature measure performance, drop the useless result. */
        for (vbe1 = 0; vbe1 < FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE - 2; vbe1++)
        {
            (void)HAL_AdcSensorGetResult(state, &result);
        }
#endif
        ret = HAL_AdcSensorGetResult(state, &vbe1);
        if (ret)
        {
            ret = HAL_AdcSensorGetResult(state, &vbe8);
        }
        if (!ret)
        {
            status = kStatus_HAL_AdcSensorError;
        }
        else
        {
            vbe1 >>= 3;
            vbe8 >>= 3;
            *temper = state->tsParam.lpAdc40Param.a *
                          (state->tsParam.lpAdc40Param.alpha * ((float)vbe8 - (float)vbe1) /
                           ((float)vbe8 + state->tsParam.lpAdc40Param.alpha * ((float)vbe8 - (float)vbe1))) -
                      state->tsParam.lpAdc40Param.b;
        }
    }
    else
    {
        assert(false);
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
        status              = HAL_AdcSensorCalcTemper(state, temper);
        state->adcTriggered = false;
    }

    return status;
}
