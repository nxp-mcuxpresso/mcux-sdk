/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_hsadc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.hsadc"
#endif

/*
 * Define the MACROs to help calculating the position of register field for specific sample index.
 */
/* ZXCTRL1 & ZXCTRL2. */
#define HSADC_ZXCTRL_ZCE_MASK(index)   ((uint16_t)3U << (2U * ((uint16_t)(index))))
#define HSADC_ZXCTRL_ZCE(index, value) (uint16_t)(((uint16_t)(value)) << (2U * ((uint16_t)(index))))
/* CLIST1 & CLIST2 & CLIST3 & CLIST4 */
#define HSADC_CLIST_SAMPLE_MASK(index)   ((uint16_t)0xFU << (4U * ((uint16_t)(index))))
#define HSADC_CLIST_SAMPLE(index, value) (uint16_t)(((uint16_t)(value)) << (4U * ((uint16_t)(index))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for HSADC module.
 *
 * @param base HSADC peripheral base address.
 */
static uint32_t HSADC_GetInstance(HSADC_Type *base);

/*!
 * @brief Set channel 6/7's sub mux channel number.
 *
 * When channel number is 6/7, it represents to configure converterA's channel 6/7 sub multiplex channel number.
 * When channel number is 14/15, it represents to configure converterB's channel 6/7 sub multiplex channel number.
 * In other cases, this function won't be functional.
 *
 * @param base                   HSADC peripheral base address.
 * @param channelNumber          Channel number.
 * @param muxNumber              Channel 6/7's sub multiplex channel number.
 * @param enableDifferentialPair Enable channel 6/7 to be differential pair or not.
 */
static void HSADC_SetChannel67Mux(HSADC_Type *base,
                                  uint16_t channelNumber,
                                  uint16_t muxNumber,
                                  bool enableDifferentialPair);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to HSADC bases for each instance. */
static HSADC_Type *const s_hsadcBases[] = HSADC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to HSADC clocks for each instance. */
static const clock_ip_name_t s_hsadcClocks[] = HSADC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t HSADC_GetInstance(HSADC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_hsadcBases); instance++)
    {
        if (s_hsadcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_hsadcBases));

    return instance;
}

/*!
 * brief Initializes the HSADC module.
 *
 * This function initializes the HSADC module.
 * The operations are:
 *  - Enable the clock for HSADC.
 *  - Set the global settings for HSADC converter.
 *
 * param base   HSADC peripheral base address.
 * param config Pointer to configuration structure. See the "hsadc_config_t".
 */
void HSADC_Init(HSADC_Type *base, const hsadc_config_t *config)
{
    assert(NULL != config);
    assert(config->powerUpDelayCount <= (HSADC_PWR_PUDELAY_MASK >> HSADC_PWR_PUDELAY_SHIFT));

    uint16_t tmp16;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable module clock. */
    CLOCK_EnableClock(s_hsadcClocks[HSADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* CTRL1 */
    tmp16 = (uint16_t)(base->CTRL1 & ~HSADC_CTRL1_SMODE_MASK);
    tmp16 |= HSADC_CTRL1_SMODE(config->dualConverterScanMode);
    base->CTRL1 = tmp16;

    /* CTRL2 */
    tmp16 = (uint16_t)(base->CTRL2 & ~HSADC_CTRL2_SIMULT_MASK);
    if (config->enableSimultaneousMode)
    {
        tmp16 |= HSADC_CTRL2_SIMULT_MASK;
    }
    base->CTRL2 = tmp16;

    /* CTRL3 */
    tmp16 = (uint16_t)(base->CTRL3 & ~(HSADC_CTRL3_ADCRES_MASK | HSADC_CTRL3_DMASRC_MASK));
    tmp16 |= (HSADC_CTRL3_ADCRES(config->resolution) | HSADC_CTRL3_DMASRC(config->DMATriggerSoruce));
    base->CTRL3 = tmp16;

    /* PWR */
    tmp16 = (uint16_t)(base->PWR & ~(HSADC_PWR_ASB_MASK | HSADC_PWR_APD_MASK | HSADC_PWR_PUDELAY_MASK));
    switch (config->idleWorkMode)
    {
        case kHSADC_IdleKeepNormal:
            break;
        case kHSADC_IdleAutoStandby:
            tmp16 |= HSADC_PWR_ASB_MASK;
            break;
        case kHSADC_IdleAutoPowerDown:
            tmp16 |= HSADC_PWR_APD_MASK;
            break;
        default:
            assert(false);
            break;
    }
    tmp16 |= HSADC_PWR_PUDELAY(config->powerUpDelayCount);
    base->PWR = tmp16;
}

/*!
 * brief Gets an available pre-defined settings for module's configuration.
 *
 * This function initializes the module's configuration structure with an available settings.
 * The default value are:
 * code
 *   config->dualConverterScanMode = kHSADC_DualConverterWorkAsTriggeredParallel;
 *   config->enableSimultaneousMode = true;
 *   config->resolution = kHSADC_Resolution12Bit;
 *   config->DMATriggerSoruce = kHSADC_DMATriggerSourceAsEndOfScan;
 *   config->idleWorkMode = kHSADC_IdleKeepNormal;
 *   config->powerUpDelay = 18U;
 * endcode
 * param config Pointer to configuration structure. See the "hsadc_config_t"
 */
void HSADC_GetDefaultConfig(hsadc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->dualConverterScanMode  = kHSADC_DualConverterWorkAsTriggeredParallel;
    config->enableSimultaneousMode = true;
    config->resolution             = kHSADC_Resolution12Bit;
    config->DMATriggerSoruce       = kHSADC_DMATriggerSourceAsEndOfScan;
    config->idleWorkMode           = kHSADC_IdleKeepNormal;
    config->powerUpDelayCount      = 18U;
}

/*!
 * brief De-initializes the HSADC module.
 *
 * This function de-initializes the HSADC module.
 * The operations are:
 *  - Power down both converters.
 *  - Disable the clock for HSADC.
 *
 * param base HSADC peripheral base address.
 */
void HSADC_Deinit(HSADC_Type *base)
{
    /* Power down both converter. */
    base->PWR &= (uint16_t)(~(HSADC_PWR_PDA_MASK | HSADC_PWR_PDB_MASK));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable module clock. */
    CLOCK_DisableClock(s_hsadcClocks[HSADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Configures the converter.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be configured. See the "_hsadc_converter_id".
 * param config        Pointer to configuration structure. See the "hsadc_converter_config_t".
 */
void HSADC_SetConverterConfig(HSADC_Type *base, uint16_t converterMask, const hsadc_converter_config_t *config)
{
    assert(NULL != config);
    /* Check the divisor value's range. */
    assert((config->clockDivisor >= 2U) &&
           (config->clockDivisor <= ((HSADC_CTRL2_DIVA_MASK >> HSADC_CTRL2_DIVA_SHIFT) + 1U)));

    uint16_t tmp16;

    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        assert(config->samplingTimeCount <= (HSADC_SAMPTIM_SAMPT_A_MASK >> HSADC_SAMPTIM_SAMPT_A_SHIFT));

        /* CTRL2 */
        tmp16 = (uint16_t)(base->CTRL2 & ~HSADC_CTRL2_DIVA_MASK);
        tmp16 |= HSADC_CTRL2_DIVA(config->clockDivisor - 1U);
        base->CTRL2 = tmp16;

        /* SAMPTIM */
        tmp16 = (uint16_t)(base->SAMPTIM & ~HSADC_SAMPTIM_SAMPT_A_MASK);
        tmp16 |= HSADC_SAMPTIM_SAMPT_A(config->samplingTimeCount);
        base->SAMPTIM = tmp16;

        /* CALIB */
        tmp16 = (uint16_t)(base->CALIB & ~(HSADC_CALIB_REQSINGA_MASK | HSADC_CALIB_REQDIFA_MASK));
        if ((uint16_t)kHSADC_CalibrationModeSingleEnded ==
            ((uint16_t)kHSADC_CalibrationModeSingleEnded & config->powerUpCalibrationModeMask))
        {
            tmp16 |= HSADC_CALIB_REQSINGA_MASK;
        }
        if ((uint16_t)kHSADC_CalibrationModeDifferential ==
            ((uint16_t)kHSADC_CalibrationModeDifferential & config->powerUpCalibrationModeMask))
        {
            tmp16 |= HSADC_CALIB_REQDIFA_MASK;
        }
        base->CALIB = tmp16;
    }

    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        assert(config->samplingTimeCount <= (HSADC_SAMPTIM_SAMPT_B_MASK >> HSADC_SAMPTIM_SAMPT_B_SHIFT));

        /* PWR2 */
        tmp16 = (uint16_t)(base->PWR2 & ~HSADC_PWR2_DIVB_MASK);
        tmp16 |= HSADC_PWR2_DIVB(config->clockDivisor - 1U);
        base->PWR2 = tmp16;

        /* SAMPTIM */
        tmp16 = (uint16_t)(base->SAMPTIM & ~HSADC_SAMPTIM_SAMPT_B_MASK);
        tmp16 |= HSADC_SAMPTIM_SAMPT_B(config->samplingTimeCount);
        base->SAMPTIM = tmp16;

        /* CALIB */
        tmp16 = (uint16_t)(base->CALIB & ~(HSADC_CALIB_REQSINGB_MASK | HSADC_CALIB_REQDIFB_MASK));
        if ((uint16_t)kHSADC_CalibrationModeSingleEnded ==
            ((uint16_t)kHSADC_CalibrationModeSingleEnded & config->powerUpCalibrationModeMask))
        {
            tmp16 |= HSADC_CALIB_REQSINGB_MASK;
        }
        if ((uint16_t)kHSADC_CalibrationModeDifferential ==
            ((uint16_t)kHSADC_CalibrationModeDifferential & config->powerUpCalibrationModeMask))
        {
            tmp16 |= HSADC_CALIB_REQDIFB_MASK;
        }
        base->CALIB = tmp16;
    }
}

/*!
 * brief Gets an available pre-defined settings for each converter's configuration.
 *
 * This function initializes each converter's configuration structure with available settings.
 * The default value are:
 * code
 *   config->clockDivisor = 4U;
 *   config->samplingTimeCount = 0U;
 *   config->enablePowerUpCalibration = false;
 *   config->powerUpCalibrationModeMask = kHSADC_CalibrationModeSingleEnded;
 * endcode
 * param config Pointer to configuration structure. See the "hsadc_converter_config_t"
 */
void HSADC_GetDefaultConverterConfig(hsadc_converter_config_t *config)
{
    assert(NULL != config);

    config->clockDivisor               = 5U;
    config->samplingTimeCount          = 0U;
    config->powerUpCalibrationModeMask = 0U;
}

/*!
 * brief Enables the converter's conversion.
 *
 * This function enables the converter's conversion by making the converter exit stop mode. The conversion should
 * only be launched after the converter is enabled. When this feature is asserted to be "false", the current scan is
 * stopped and no further scans can start. All the software and hardware triggers are ignored.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 * param enable         Enable or disable the feature.
 */
void HSADC_EnableConverter(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 &= ~(uint16_t)HSADC_CTRL1_STOPA_MASK;
        }
        else
        {
            base->CTRL1 |= HSADC_CTRL1_STOPA_MASK;
        }
    }
    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 &= ~(uint16_t)HSADC_CTRL2_STOPB_MASK;
        }
        else
        {
            base->CTRL2 |= HSADC_CTRL2_STOPB_MASK;
        }
    }
}

/*!
 * brief Enables the input of an external sync signal.
 *
 * This function enables the input of the external sync signal. The external sync signal could be used to trigger the
 * conversion if the hardware trigger-related setting is used.
 * Note: When in "Once" scan mode, this gate is off automatically after an available sync is received.
 * Enable the input again manually if another sync signal is needed.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 * param enable        Enable or disable the feature.
 */
void HSADC_EnableConverterSyncInput(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 |= HSADC_CTRL1_SYNCA_MASK;
        }
        else
        {
            base->CTRL1 &= ~(uint16_t)HSADC_CTRL1_SYNCA_MASK;
        }
    }
    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 |= HSADC_CTRL2_SYNCB_MASK;
        }
        else
        {
            base->CTRL2 &= ~(uint16_t)HSADC_CTRL2_SYNCB_MASK;
        }
    }
}

/*!
 * brief Enables power for the converter.
 *
 * This function enables the power for the converter. The converter should be powered on before conversion. Once
 * this API is called, the converter is powered on after a few moments (so-called power up delay) to make the
 * power stable.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 * param enable        Enable or disable the feature.
 */
void HSADC_EnableConverterPower(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* PWR */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->PWR &= ~(uint16_t)HSADC_PWR_PDA_MASK;
        }
        else
        {
            base->PWR |= HSADC_PWR_PDA_MASK;
        }
    }
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->PWR &= ~(uint16_t)HSADC_PWR_PDB_MASK;
        }
        else
        {
            base->PWR |= HSADC_PWR_PDB_MASK;
        }
    }
}

/*!
 * brief Triggers the converter by using the software trigger.
 *
 * This function triggers  the converter using a software trigger. The software trigger can be used to start a
 * conversion
 * sequence.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 */
void HSADC_DoSoftwareTriggerConverter(HSADC_Type *base, uint16_t converterMask)
{
    /* CTRL1 */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        base->CTRL1 |= HSADC_CTRL1_STARTA_MASK;
    }
    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        base->CTRL2 |= HSADC_CTRL2_STARTB_MASK;
    }
}

/*!
 * brief Enables the DMA feature.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 * param enable        Enable or disable the feature.
 */
void HSADC_EnableConverterDMA(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 |= HSADC_CTRL1_DMAENA_MASK;
        }
        else
        {
            base->CTRL1 &= (uint16_t)(~HSADC_CTRL1_DMAENA_MASK);
        }
    }
    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 |= HSADC_CTRL2_DMAENB_MASK;
        }
        else
        {
            base->CTRL2 &= (uint16_t)(~HSADC_CTRL2_DMAENB_MASK);
        }
    }
}

/*!
 * brief Enables the interrupts.
 *
 * param base HSADC peripheral base address.
 * param mask Mask value for interrupt events. See the "_hsadc_interrupt_enable".
 */
void HSADC_EnableInterrupts(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    /* CTRL1 */
    tmp16 = base->CTRL1;
    if ((uint16_t)kHSADC_ZeroCrossingInterruptEnable == ((uint16_t)kHSADC_ZeroCrossingInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_ZCIE_MASK;
    }
    if ((uint16_t)kHSADC_HighLimitInterruptEnable == ((uint16_t)kHSADC_HighLimitInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_HLMTIE_MASK;
    }
    if ((uint16_t)kHSADC_LowLimitInterruptEnable == ((uint16_t)kHSADC_LowLimitInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_LLMTIE_MASK;
    }
    if ((uint16_t)kHSADC_ConverterAEndOfScanInterruptEnable ==
        ((uint16_t)kHSADC_ConverterAEndOfScanInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_EOSIEA_MASK;
    }
    base->CTRL1 = tmp16;

    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterBEndOfScanInterruptEnable ==
        ((uint16_t)kHSADC_ConverterBEndOfScanInterruptEnable & mask))
    {
        base->CTRL2 |= HSADC_CTRL2_EOSIEB_MASK;
    }

    /* CALIB */
    tmp16 = base->CALIB;
    if ((uint16_t)kHSADC_ConverterAEndOfCalibrationInterruptEnable ==
        ((uint16_t)kHSADC_ConverterAEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 |= HSADC_CALIB_EOCALIEA_MASK;
    }
    if ((uint16_t)kHSADC_ConverterBEndOfCalibrationInterruptEnable ==
        ((uint16_t)kHSADC_ConverterBEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 |= HSADC_CALIB_EOCALIEB_MASK;
    }
    base->CALIB = tmp16;
}

/*!
 * brief Disables the interrupts.
 *
 * param base HSADC peripheral base address.
 * param mask Mask value for interrupt events. See the "_hsadc_interrupt_enable".
 */
void HSADC_DisableInterrupts(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    /* CTRL1 */
    tmp16 = base->CTRL1;
    if ((uint16_t)kHSADC_ZeroCrossingInterruptEnable == ((uint16_t)kHSADC_ZeroCrossingInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_ZCIE_MASK;
    }
    if ((uint16_t)kHSADC_HighLimitInterruptEnable == ((uint16_t)kHSADC_HighLimitInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_HLMTIE_MASK;
    }
    if ((uint16_t)kHSADC_LowLimitInterruptEnable == ((uint16_t)kHSADC_LowLimitInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_LLMTIE_MASK;
    }
    if ((uint16_t)kHSADC_ConverterAEndOfScanInterruptEnable ==
        ((uint16_t)kHSADC_ConverterAEndOfScanInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_EOSIEA_MASK;
    }
    base->CTRL1 = tmp16;

    /* CTRL2 */
    if ((uint16_t)kHSADC_ConverterBEndOfScanInterruptEnable ==
        ((uint16_t)kHSADC_ConverterBEndOfScanInterruptEnable & mask))
    {
        base->CTRL2 &= (uint16_t)(~HSADC_CTRL2_EOSIEB_MASK);
    }

    /* CALIB */
    tmp16 = base->CALIB;
    if ((uint16_t)kHSADC_ConverterAEndOfCalibrationInterruptEnable ==
        ((uint16_t)kHSADC_ConverterAEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 &= HSADC_CALIB_EOCALIEA_MASK;
    }
    if ((uint16_t)kHSADC_ConverterBEndOfCalibrationInterruptEnable ==
        ((uint16_t)kHSADC_ConverterBEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 &= HSADC_CALIB_EOCALIEB_MASK;
    }
    base->CALIB = tmp16;
}

/*!
 * brief  Gets the status flags.
 *
 * param  base HSADC peripheral base address.
 *
 * return      Mask value for the event flags. See the "_hsadc_status_flags".
 */
uint16_t HSADC_GetStatusFlags(HSADC_Type *base)
{
    uint16_t tmp16;
    uint16_t status = 0U;

    /* STAT */
    tmp16 = base->STAT;
    if (HSADC_STAT_ZCI_MASK == (tmp16 & HSADC_STAT_ZCI_MASK))
    {
        status |= (uint16_t)kHSADC_ZeroCrossingFlag;
    }
    if (HSADC_STAT_HLMTI_MASK == (tmp16 & HSADC_STAT_HLMTI_MASK))
    {
        status |= (uint16_t)kHSADC_HighLimitFlag;
    }
    if (HSADC_STAT_LLMTI_MASK == (tmp16 & HSADC_STAT_LLMTI_MASK))
    {
        status |= (uint16_t)kHSADC_LowLimitFlag;
    }
    if (HSADC_STAT_EOSIA_MASK == (tmp16 & HSADC_STAT_EOSIA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterAEndOfScanFlag;
    }
    if (HSADC_STAT_EOSIB_MASK == (tmp16 & HSADC_STAT_EOSIB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBEndOfScanFlag;
    }
    if (HSADC_STAT_EOCALIA_MASK == (tmp16 & HSADC_STAT_EOCALIA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterAEndOfCalibrationFlag;
    }
    if (HSADC_STAT_EOCALIB_MASK == (tmp16 & HSADC_STAT_EOCALIB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBEndOfCalibrationFlag;
    }
    if (HSADC_STAT_CIPA_MASK == (tmp16 & HSADC_STAT_CIPA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterAConvertingFlag;
    }
    if (HSADC_STAT_CIPB_MASK == (tmp16 & HSADC_STAT_CIPB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBConvertingFlag;
    }
    if (HSADC_STAT_DUMMYA_MASK == (tmp16 & HSADC_STAT_DUMMYA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterADummyConvertingFlag;
    }
    if (HSADC_STAT_DUMMYB_MASK == (tmp16 & HSADC_STAT_DUMMYB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBDummyConvertingFlag;
    }
    if (HSADC_STAT_CALONA_MASK == (tmp16 & HSADC_STAT_CALONA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterACalibratingFlag;
    }
    if (HSADC_STAT_CALONB_MASK == (tmp16 & HSADC_STAT_CALONB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBCalibratingFlag;
    }

    /* PWR */
    tmp16 = base->PWR;
    if (HSADC_PWR_PSTSA_MASK == (tmp16 & HSADC_PWR_PSTSA_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterAPowerDownFlag;
    }
    if (HSADC_PWR_PSTSB_MASK == (tmp16 & HSADC_PWR_PSTSB_MASK))
    {
        status |= (uint16_t)kHSADC_ConverterBPowerDownFlag;
    }

    return status;
}

/*!
 * brief Clears the status flags.
 *
 * param base  HSADC peripheral base address.
 * param flags Mask value for the event flags to be cleared. See the "_hsadc_status_flags".
 */
void HSADC_ClearStatusFlags(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    if ((uint16_t)kHSADC_ZeroCrossingFlag == (mask & (uint16_t)kHSADC_ZeroCrossingFlag))
    {
        base->ZXSTAT = 0xFFFFU;
    }
    if ((uint16_t)kHSADC_HighLimitFlag == (mask & (uint16_t)kHSADC_HighLimitFlag))
    {
        base->HILIMSTAT = 0xFFFFU;
    }
    if ((uint16_t)kHSADC_LowLimitFlag == (mask & (uint16_t)kHSADC_LowLimitFlag))
    {
        base->LOLIMSTAT = 0xFFFFU;
    }
    /* STAT */
    tmp16 = base->STAT;
    if ((uint16_t)kHSADC_ConverterAEndOfScanFlag == (mask & (uint16_t)kHSADC_ConverterAEndOfScanFlag))
    {
        tmp16 |= HSADC_STAT_EOSIA_MASK;
    }
    if ((uint16_t)kHSADC_ConverterBEndOfScanFlag == (mask & (uint16_t)kHSADC_ConverterBEndOfScanFlag))
    {
        tmp16 |= HSADC_STAT_EOSIB_MASK;
    }
    if ((uint16_t)kHSADC_ConverterAEndOfCalibrationFlag == (mask & (uint16_t)kHSADC_ConverterAEndOfCalibrationFlag))
    {
        tmp16 |= HSADC_STAT_EOCALIA_MASK;
    }
    if ((uint16_t)kHSADC_ConverterBEndOfCalibrationFlag == (mask & (uint16_t)kHSADC_ConverterBEndOfCalibrationFlag))
    {
        tmp16 |= HSADC_STAT_EOCALIB_MASK;
    }
    base->STAT = tmp16;
}

static void HSADC_SetChannel67Mux(HSADC_Type *base,
                                  uint16_t channelNumber,
                                  uint16_t muxNumber,
                                  bool enableDifferentialPair)
{
    uint16_t tmp16;

    /* MUX67_SEL */
    /* When channel number is 6/7, it represents converterA's channel 6/7. */
    /* When channel number is 14/15, it represents converterB's channel 6/7. */
    tmp16 = base->MUX67_SEL;
    /* For differential mode. */
    if (true == enableDifferentialPair)
    {
        switch (channelNumber)
        {
            case 6U:
            case 7U:
                tmp16 &= ~((uint16_t)HSADC_MUX67_SEL_CH6_SELA_MASK | (uint16_t)HSADC_MUX67_SEL_CH7_SELA_MASK);
                tmp16 |= (HSADC_MUX67_SEL_CH6_SELA(muxNumber) | HSADC_MUX67_SEL_CH7_SELA(muxNumber));
                break;
            case 14U:
            case 15U:
                tmp16 &= ~((uint16_t)HSADC_MUX67_SEL_CH6_SELB_MASK | (uint16_t)HSADC_MUX67_SEL_CH7_SELB_MASK);
                tmp16 |= (HSADC_MUX67_SEL_CH6_SELB(muxNumber) | HSADC_MUX67_SEL_CH7_SELB(muxNumber));
                break;
            default:
                tmp16 = base->MUX67_SEL;
                break;
        }
    }
    else /* For single ended mode. */
    {
        switch (channelNumber)
        {
            case 6U:
                tmp16 &= ~(uint16_t)HSADC_MUX67_SEL_CH6_SELA_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH6_SELA(muxNumber);
                break;
            case 7U:
                tmp16 &= ~(uint16_t)HSADC_MUX67_SEL_CH7_SELA_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH7_SELA(muxNumber);
                break;
            case 14U:
                tmp16 &= ~(uint16_t)HSADC_MUX67_SEL_CH6_SELB_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH6_SELB(muxNumber);
                break;
            case 15U:
                tmp16 &= ~(uint16_t)HSADC_MUX67_SEL_CH7_SELB_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH7_SELB(muxNumber);
                break;
            default:
                tmp16 = base->MUX67_SEL;
                break;
        }
    }
    base->MUX67_SEL = tmp16;
}

/*
 * Mask table for channel differential pair setting.
 * The item's value would be set into CTRL1[CHNCFG_L] or CTRL2[CHNCFG_H].
 */
static const uint16_t g_HSADCChannelConfigDifferentialMask[] = {
    0x0010U, /* CHN0-1,   ANA0-ANA1, CTRL1[CHNCFG_L]. */
    0x0020U, /* CHN2-3,   ANA2-ANA3. CTRL1[CHNCFG_L]. */
    0x0080U, /* CHN4-5,   ANA4-ANA5. CTRL2[CHNCFG_H]. */
    0x0100U, /* CHN6-7,   ANA6-ANA7. CTRL2[CHNCFG_H]. */
    0x0040U, /* CHN8-9,   ANB0-ANB1. CTRL1[CHNCFG_L]. */
    0x0080U, /* CHN10-11, ANB2-ANB3. CTRL1[CHNCFG_L]. */
    0x0200U, /* CHN12-13, ANB4-ANB5. CTRL2[CHNCFG_H]. */
    0x0400U  /* CHN14-15, ANB6-ANB7. CTRL2[CHNCFG_H]. */
};
/*!
 * brief Configures the sample slot.
 *
 * A sample list in this module works like a conversion sequence. Each sample slot can be used to designate to sample
 * which channel is in converter A and converter B. The detail mapping relationship between sample slot and converter's
 * channel can be found in the SoC reference manual.
 *
 * param base        HSADC peripheral base address.
 * param sampleIndex Index of sample slot in conversion sequence. Available range is 0-15.
 * param config      Pointer to configuration structure. See the "hsadc_sample_config_t".
 */
void HSADC_SetSampleConfig(HSADC_Type *base, uint16_t sampleIndex, const hsadc_sample_config_t *config)
{
    assert(sampleIndex < HSADC_RSLT_COUNT);
    assert(NULL != config);

    uint16_t tmp16;

    /* Configure the differential conversion channel. */
    if ((config->channelNumber < 4U) || ((config->channelNumber >= 8U) && (config->channelNumber < 12U)))
    {
        if (config->enableDifferentialPair)
        {
            base->CTRL1 |= g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U];
        }
        else
        {
            base->CTRL1 &= (uint16_t)(~g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U]);
        }
    }
    else if (((config->channelNumber >= 4U) && (config->channelNumber < 8U)) ||
             ((config->channelNumber >= 12U) && (config->channelNumber < 16U)))
    {
        if (config->enableDifferentialPair)
        {
            base->CTRL2 |= g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U];
        }
        else
        {
            base->CTRL2 &= (uint16_t)(~g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U]);
        }
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Configure the zero crossing mode. */
    if (sampleIndex < 8U)
    {
        tmp16 = base->ZXCTRL1 & ~HSADC_ZXCTRL_ZCE_MASK(sampleIndex);
        tmp16 |= HSADC_ZXCTRL_ZCE(sampleIndex, config->zeroCrossingMode);
        base->ZXCTRL1 = tmp16;
    }
    else if (sampleIndex < 16U)
    {
        sampleIndex -= 8U;
        tmp16 = base->ZXCTRL2 & ~HSADC_ZXCTRL_ZCE_MASK(sampleIndex);
        tmp16 |= HSADC_ZXCTRL_ZCE(sampleIndex, config->zeroCrossingMode);
        base->ZXCTRL2 = tmp16;
        sampleIndex += 8U;
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Fill the conversion channel into sample slot. */
    if (sampleIndex < 4U)
    {
        tmp16 = base->CLIST1 & ~HSADC_CLIST_SAMPLE_MASK(sampleIndex);
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST1 = tmp16;
    }
    else if (sampleIndex < 8U)
    {
        sampleIndex -= 4U;
        tmp16 = base->CLIST2 & ~HSADC_CLIST_SAMPLE_MASK(sampleIndex);
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST2 = tmp16;
        sampleIndex += 4U;
    }
    else if (sampleIndex < 12U)
    {
        sampleIndex -= 8U;
        tmp16 = base->CLIST3 & ~HSADC_CLIST_SAMPLE_MASK(sampleIndex);
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST3 = tmp16;
        sampleIndex += 8U;
    }
    else if (sampleIndex < 16U)
    {
        sampleIndex -= 12U;
        tmp16 = base->CLIST4 & ~HSADC_CLIST_SAMPLE_MASK(sampleIndex);
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST4 = tmp16;
        sampleIndex += 12U;
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Configure the hardware compare. */
    base->LOLIM[sampleIndex] = config->lowLimitValue;
    base->HILIM[sampleIndex] = config->highLimitValue;
    base->OFFST[sampleIndex] = config->offsetValue;

    /* Configure the hardware trigger. */
    /* SCTRL. */
    if (config->enableWaitSync)
    {
        base->SCTRL |= ((uint16_t)1U << sampleIndex);
    }
    else
    {
        base->SCTRL &= ~((uint16_t)1U << sampleIndex);
    }

    /* Configure the channel 6/7's additional multiplex selector. */
    HSADC_SetChannel67Mux(base, config->channelNumber, config->channel67MuxNumber, config->enableDifferentialPair);
}

/*!
 * brief Gets the default sample configuration.
 *
 * This function initializes each sample's configuration structure with an available settings.
 * The default values are:
 * code
 *   config->channelNumber = 0U;
 *   config->channel6MuxNumber = 0U;
 *   config->channel7MuxNumber = 0U;
 *   config->enableDifferentialPair = false;
 *   config->zeroCrossingMode = kHSADC_ZeroCorssingDisabled;
 *   config->highLimitValue = 0x7FF8U;
 *   config->lowLimitValue = 0U;
 *   config->offsetValue = 0U;
 *   config->enableWaitSync = false;
 * endcode
 * param config Pointer to configuration structure. See the "hsadc_sample_config_t".
 */
void HSADC_GetDefaultSampleConfig(hsadc_sample_config_t *config)
{
    assert(NULL != config);

    config->channelNumber          = 0U;
    config->channel67MuxNumber     = 0U;
    config->enableDifferentialPair = false;
    config->zeroCrossingMode       = kHSADC_ZeroCorssingDisabled;
    config->highLimitValue         = 0x7FF8U;
    config->lowLimitValue          = 0U;
    config->offsetValue            = 0U;
    config->enableWaitSync         = false;
}

/*!
 * brief Starts the hardware calibration.
 *
 * This function starts the single ended calibration and differential calibration for converter A and converter B
 * at the same time.
 * Note that this is a non blocking function. End of Scan flag and End of Calibration flag are both be set after the
 * calibration process. As a result, the user should check these two flags by using the function HSADC_GetStatusFlags()
 * to wait for the
 * calibration process to complete.
 *
 * param base                HSADC peripheral base address.
 * param converterMask       Mask for converters to be operated. See the "_hsadc_converter_id".
 * param calibrationModeMask Mask for calibration mode to be operated. See the "_hsadc_calibration_mode". Shouldn't be
 * zero.
 */
void HSADC_DoAutoCalibration(HSADC_Type *base, uint16_t converterMask, uint16_t calibrationModeMask)
{
    assert(0U != calibrationModeMask);

    /* CALIB */
    /* Set the calibration mode.
     * Hardware requires that the bit REQSINGA, REQDIFA, REQA, REQSINGB, REQDIFB, REQB in CALIB register can't be set
     * at the same time. They must be set as the sequency description in the reference manual.
     */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if ((uint16_t)kHSADC_CalibrationModeSingleEnded ==
            ((uint16_t)kHSADC_CalibrationModeSingleEnded & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQSINGA_MASK;
        }
        if ((uint16_t)kHSADC_CalibrationModeDifferential ==
            ((uint16_t)kHSADC_CalibrationModeDifferential & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQDIFA_MASK;
        }
        base->CALIB |= HSADC_CALIB_CAL_REQA_MASK;
    }
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if ((uint16_t)kHSADC_CalibrationModeSingleEnded ==
            ((uint16_t)kHSADC_CalibrationModeSingleEnded & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQSINGB_MASK;
        }
        if ((uint16_t)kHSADC_CalibrationModeDifferential ==
            ((uint16_t)kHSADC_CalibrationModeDifferential & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQDIFB_MASK;
        }
        base->CALIB |= HSADC_CALIB_CAL_REQB_MASK;
    }

    /* Trigger the calibration. */
    HSADC_DoSoftwareTriggerConverter(base, converterMask);
}

/*!
 * brief Gets the calibration result value.
 *
 * This function returns the single ended calibration value and differential calibration value for converter A and
 * converter B. The calibration value of each calibration mode for each converter can be received from this function's
 * return value by using the mask and shift definition from HSADC_CALIBRATION_VALUE_A_SINGLE_ENDED_MASK to
 * HSADC_CALIBRATION_VALUE_B_DIFFERENTIAL_SHIFT.
 *
 * param base                HSADC peripheral base address.
 * return                    Calibration value for converter A and converter B.
 */
uint32_t HSADC_GetCalibrationResultValue(HSADC_Type *base)
{
    uint32_t calValA = ((uint32_t)(base->CALVAL_A) << 16U);
    return (calValA + base->CALVAL_B);
}

/*!
 * brief Enables or disables the calibration result value.
 *
 * This function enables or disables converter A and converter B to use the calibration values to obtain the final
 * conversion result by calibration sum operation.
 *
 * param base          HSADC peripheral base address.
 * param converterMask Mask for converters to be operated. See the "_hsadc_converter_id".
 * param enable        Enable or disable the feature.
 */
void HSADC_EnableCalibrationResultValue(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CALIB */
    /* Enable means not to bypass the calibration operation. */
    if ((uint16_t)kHSADC_ConverterA == ((uint16_t)kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CALIB &= ~(uint16_t)HSADC_CALIB_BYPA_MASK;
        }
        else
        {
            base->CALIB |= HSADC_CALIB_BYPA_MASK;
        }
    }
    if ((uint16_t)kHSADC_ConverterB == ((uint16_t)kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CALIB &= ~(uint16_t)HSADC_CALIB_BYPB_MASK;
        }
        else
        {
            base->CALIB |= HSADC_CALIB_BYPB_MASK;
        }
    }
}
