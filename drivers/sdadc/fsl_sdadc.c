/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdadc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sdadc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to SDADC bases for each instance. */
#if defined(SDADC_BASE_PTRS_NS)
static SDADC_Type *s_sdadcBases_ns[] = SDADC_BASE_PTRS_NS;
#endif /* SDADC_BASE_PTRS_NS */
static SDADC_Type *s_sdadcBases[] = SDADC_BASE_PTRS;

/*! @brief Pointers to SDADC clocks for each instance. */
static const clock_ip_name_t s_sdadcClocks[] = SDADC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief SDADC reset array for each instance. */
#if defined(SDADC_RSTS)
static const reset_ip_name_t s_sdadcResets[] = SDADC_RSTS;
#endif                                    /* SDADC_RSTS */

static char sdadcChannelModeRecord = 'D'; /* Record the conversion mode used by the SDADC channel
                                          in the initialization state, by default, it is set to 'D',
                                          which means only differential mode is executed. */
/*******************************************************************************
 * Code
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*!
 * brief This function is used to get the SDADC instance.
 *
 * param base SDADC peripheral base address.
 *
 * return SDADC instance.
 */
static uint32_t SDADC_GetInstance(SDADC_Type *base)
{
    uint32_t instance             = 0U;
    uint8_t sdadcBaseSize         = ARRAY_SIZE(s_sdadcBases);
    SDADC_Type **sdadcBaseAddress = s_sdadcBases;

#if defined(SDADC_BASE_PTRS_NS)
    if (0U == ((uint32_t)base & 0x10000000U))
    {
        /* Input instance is in the non-secure area. */
        sdadcBaseSize    = ARRAY_SIZE(s_sdadcBases_ns);
        sdadcBaseAddress = s_sdadcBases_ns;
    }
#endif /* SDADC_BASE_PTRS_NS */

    /* Find the instance index from base address mappings. */
    for (; instance < sdadcBaseSize; ++instance)
    {
        if (sdadcBaseAddress[instance] == base)
        {
            break;
        }
    }

    assert(instance < sdadcBaseSize);

    return instance;
}
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * brief This function is used to get available predefined configurations for the SDADC initialization.
 *
 * param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 */
void SDADC_GetDefaultConfig(sdadc_config_t *config)
{
    assert(config != NULL);

    config->channelCount  = 0U;
    config->channelConfig = NULL;
}

/*!
 * brief This function is used to initialize the SDADC.
 *
 * param base SDADC peripheral base address.
 * param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 */
void SDADC_Init(SDADC_Type *base, const sdadc_config_t *config)
{
    assert(config != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock for the SDADC instance. */
    (void)CLOCK_EnableClock(s_sdadcClocks[SDADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(SDADC_RSTS)
    /* Release the SDADC reset. */
    RESET_ReleasePeripheralReset(s_sdadcResets[SDADC_GetInstance(base)]);
#endif /* SDADC_RSTS */

    sdadc_channel_config_t *channelConfig = config->channelConfig;

    for (uint8_t index = 0U; index < config->channelCount; ++index)
    {
        SDADC_ConfigureChannelMode(base, channelConfig->number, channelConfig->mode);

        if (kSDADC_SingleEnd_Mode == channelConfig->mode)
        {
            sdadcChannelModeRecord = 'S'; /* If there is a single-end mode conversion, mark it as 'S'. */

            /*! Configure DAC compensation. */
            SDADC_ControlDacCompensationEnable(base, channelConfig->number, channelConfig->type,
                                               channelConfig->enableDacCompensation);
            /*! Configure DC Loop. */
            SDADC_ControlModulatorDcLoopEnable(base, channelConfig->number, channelConfig->type,
                                               channelConfig->enableDCLoop);
        }
        else
        {
            /*! Disable DAC compensation. */
            SDADC_ControlDacCompensationEnable(base, channelConfig->number, channelConfig->type, false);
            /*! Disable DC Loop. */
            SDADC_ControlModulatorDcLoopEnable(base, channelConfig->number, channelConfig->type, false);
        }

        /*! Decimator DC Filter configuration. */
        SDADC_ControlDecimatorDcFilterEnable(base, channelConfig->number, channelConfig->type,
                                             channelConfig->enableDcFilter);
        /*! Decimator output signal invert configuration. */
        SDADC_ControlDecimatorOutputInvertEnable(base, channelConfig->number, channelConfig->type,
                                                 channelConfig->enablePolarityInvert);

        /*! Configure channel volume (gain). */
        SDADC_ConfigureDecimatorVolume(base, channelConfig->number, channelConfig->type, channelConfig->volume);
        /*! Configure decimator sample rate. */
        SDADC_ConfigureDecimatorSampleRate(base, channelConfig->number, channelConfig->type, channelConfig->samplerate);
        /*! Configure FIFO watermark. */
        SDADC_ConfigureFifoWatermark(base, channelConfig->number, channelConfig->type, channelConfig->watermark);

        channelConfig += 1U;
    }
}

/*!
 * brief This function is used to power up the ADC in the initialization state.
 *
 * param base SDADC peripheral base address.
 * param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 * param clock Core clock frequency with Hz.
 */
void SDADC_DoInitPowerUp(SDADC_Type *base, sdadc_config_t *config, uint32_t clock)
{
    /*! Enable reference power, set the reference mode to fast charge mode at the beginning, delay 1ms waiting for the
        reference power up then set the reference mode to retain mode (when there is only differential mode executing)
        or set to the low noise mode (when there is a single-end mode executing).
    */
    SDADC_ControlReferencePowerEnable(base, true);
    SDADC_ConfigureReferenceMode(base, kSDADC_RefFastChargeMode);
    SDK_DelayAtLeastUs(1000U, clock);

    if ('S' == sdadcChannelModeRecord) /* If only single end mode enabled, entry low noise mode to reduce noise. */
    {
        SDADC_ConfigureReferenceMode(base, kSDADC_RefLowNoiseMode);
    }
    else /* If there is no single end mode enabled, entry retain mode to save power. */
    {
        SDADC_ConfigureReferenceMode(base, kSDADC_RefRetainMode);
    }

    /*! Enable LDO power and set LDO drive capability. */
    SDADC_ControlLdoPowerEnable(base, true);
    if (config->channelCount <= 1U)
    {
        SDADC_ConfigureLdoDriveCapability(base, kSDADC_LdoLowPower);
    }
    else
    {
        SDADC_ConfigureLdoDriveCapability(base, kSDADC_LdoHighPower);
    }

    /*! Enable conversion channel's modulator power. */
    for (uint8_t index = 0U; index < config->channelCount; ++index)
    {
        SDADC_ControlModulatorPowerEnable(base, (config->channelConfig + index)->number,
                                          (config->channelConfig + index)->type, true);
    }

    /*! Reset the SDADC channel P-Side or/and N-Side 15us to avoid saturation behavior. */
    for (uint8_t index = 0U; index < config->channelCount; ++index)
    {
        SDADC_ControlModulatorReset(base, (config->channelConfig + index)->number,
                                    (config->channelConfig + index)->type, true);
    }

    SDK_DelayAtLeastUs(50U, clock);

    for (uint8_t index = 0U; index < config->channelCount; ++index)
    {
        SDADC_ControlModulatorReset(base, (config->channelConfig + index)->number,
                                    (config->channelConfig + index)->type, false);
    }
}

/*!
 * brief This function is used to de-initialize the SDADC.
 *
 * param base SDADC peripheral base address.
 */
void SDADC_Deinit(SDADC_Type *base, const sdadc_config_t *config)
{
    /*! Disable SDADC channels power. */
    for (uint8_t index = 0U; index < config->channelCount; ++index)
    {
        SDADC_ControlModulatorPowerEnable(base, (config->channelConfig + index)->number,
                                          (config->channelConfig + index)->type, false);
    }

    base->ADC_CTL_0 &= (~(SDADC_ADC_CTL_0_ADCP_POWER_ENABLE_MASK | SDADC_ADC_CTL_0_ADCN_POWER_ENABLE_MASK));
    /*! Disable the LDO power. */
    SDADC_ControlLdoPowerEnable(base, false);
    /*! Disable the reference power. */
    SDADC_ControlReferencePowerEnable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /*! Disable the clock gate. */
    CLOCK_DisableClock(s_sdadcClocks[SDADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(SDADC_RSTS)
    RESET_PeripheralReset(s_sdadcResets[SDADC_GetInstance(base)]);
#endif /* SDADC_RSTS */
}

/*!
 * brief This function is used to copy specific conversion channels' data from FIFO to buffer.
 *
 * note This function will copy all 16 entries in the specified FIFO.
 *
 * param base SDADC peripheral base address.
 * param group Indicates which group of channels data to obtain.
 * param count Indicates how many channels in the specified group.
 * param buffer The buffer which stores conversion data.
 */
void SDADC_CopyConvChannelFifoToBuffer(SDADC_Type *base, sdadc_channel_group *group, uint8_t count, void *buffer)
{
    uint32_t *dataAddr = (uint32_t *)buffer;

    for (uint8_t fifoItemIndex = 0U; fifoItemIndex < SDADC_FIFO_DEPTH; fifoItemIndex++)
    {
        for (uint8_t fifoIndex = 0; fifoIndex < count; fifoIndex++)
        {
            *dataAddr = SDADC_GetConvChannelFifoRawData(base, (group + fifoIndex)->number, (group + fifoIndex)->type);
            dataAddr  = (uint32_t *)((uint32_t)dataAddr + SDADC_FIFO_WIDTH);
        }
    }
}
