/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_qtmr.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.qtmr_2"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base Quad Timer peripheral base address
 *
 * @return The Quad Timer instance
 */
static uint32_t QTMR_GetInstance(TMR_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to Quad Timer bases for each instance. */
static TMR_Type *const s_qtmrBases[] = TMR_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to Quad Timer clocks for each instance. */
static const clock_ip_name_t s_qtmrClocks[] = TMR_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t QTMR_GetInstance(TMR_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_qtmrBases); instance++)
    {
        if (s_qtmrBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_qtmrBases));

    return instance;
}

/*!
 * brief Ungates the Quad Timer clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the Quad Timer driver.
 *
 * param base   Quad Timer peripheral base address
 * param config Pointer to user's Quad Timer config structure
 */
void QTMR_Init(TMR_Type *base, const qtmr_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the module clock */
    CLOCK_EnableClock(s_qtmrClocks[QTMR_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Setup the counter sources */
    base->CTRL = (TMR_CTRL_PCS(config->primarySource) | TMR_CTRL_SCS(config->secondarySource));

    /* Setup the master mode operation */
    base->SCTRL = (TMR_SCTRL_EEOF(config->enableExternalForce) | TMR_SCTRL_MSTR(config->enableMasterMode));

    /* Setup debug mode */
    base->CSCTRL = TMR_CSCTRL_DBG_EN(config->debugMode);

    /* Setup input filter */
    base->FILT = (TMR_FILT_FILT_CNT(config->faultFilterCount) | TMR_FILT_FILT_PER(config->faultFilterPeriod));
}

/*!
 * brief Stops the counter and gates the Quad Timer clock
 *
 * param base Quad Timer peripheral base address
 */
void QTMR_Deinit(TMR_Type *base)
{
    /* Stop the counter */
    base->CTRL &= ~(uint16_t)TMR_CTRL_CM_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the module clock */
    CLOCK_DisableClock(s_qtmrClocks[QTMR_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Fill in the Quad Timer config struct with the default settings
 *
 * The default values are:
 * code
 *    config->debugMode = kQTMR_RunNormalInDebug;
 *    config->enableExternalForce = false;
 *    config->enableMasterMode = false;
 *    config->faultFilterCount = 0;
 *    config->faultFilterPeriod = 0;
 *    config->primarySource = kQTMR_ClockDivide_2;
 *    config->secondarySource = kQTMR_Counter0InputPin;
 * endcode
 * param config Pointer to user's Quad Timer config structure.
 */
void QTMR_GetDefaultConfig(qtmr_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Halt counter during debug mode */
    config->debugMode = kQTMR_RunNormalInDebug;
    /* Another counter cannot force state of OFLAG signal */
    config->enableExternalForce = false;
    /* Compare function's output from this counter is not broadcast to other counters */
    config->enableMasterMode = false;
    /* Fault filter count is set to 0 */
    config->faultFilterCount = 0;
    /* Fault filter period is set to 0 which disables the fault filter */
    config->faultFilterPeriod = 0;
    /* Primary count source is IP bus clock divide by 2 */
    config->primarySource = kQTMR_ClockDivide_2;
    /* Secondary count source is counter 0 input pin */
    config->secondarySource = kQTMR_Counter0InputPin;
}

/*!
 * brief Sets up Quad timer module for PWM signal output.
 *
 * The function initializes the timer module according to the parameters passed in by the user. The
 * function also sets up the value compare registers to match the PWM signal requirements.
 *
 * param base             Quad Timer peripheral base address
 * param pwmFreqHz        PWM signal frequency in Hz
 * param dutyCyclePercent PWM pulse width, value should be between 0 to 100
 *                         0=inactive signal(0% duty cycle)...
 *                         100=active signal (100% duty cycle)
 * param outputPolarity   true: invert polarity of the output signal, false: no inversion
 * param srcClock_Hz      Main counter clock in Hz.
 *
 * return Returns an error if there was error setting up the signal.
 */
status_t QTMR_SetupPwm(
    TMR_Type *base, uint32_t pwmFreqHz, uint8_t dutyCyclePercent, bool outputPolarity, uint32_t srcClock_Hz)
{
    uint32_t periodCount, highCount, lowCount;
    uint16_t reg;
    status_t status = kStatus_Success;

    if (dutyCyclePercent <= 100U)
    {
        /* Set OFLAG pin for output mode and force out a low on the pin */
        base->SCTRL |= (TMR_SCTRL_FORCE_MASK | TMR_SCTRL_OEN_MASK);

        /* Counter values to generate a PWM signal */
        periodCount = (srcClock_Hz / pwmFreqHz);
        highCount   = (periodCount * dutyCyclePercent) / 100U;
        lowCount    = periodCount - highCount;

        /* Setup the compare registers for PWM output */
        base->COMP1 = (uint16_t)lowCount;
        base->COMP2 = (uint16_t)highCount;

        /* Setup the pre-load registers for PWM output */
        base->CMPLD1 = (uint16_t)lowCount;
        base->CMPLD2 = (uint16_t)highCount;

        reg = base->CSCTRL;
        /* Setup the compare load control for COMP1 and COMP2.
         * Load COMP1 when CSCTRL[TCF2] is asserted, load COMP2 when CSCTRL[TCF1] is asserted
         */
        reg &= ~((uint16_t)TMR_CSCTRL_CL1_MASK | (uint16_t)TMR_CSCTRL_CL2_MASK);
        reg |= (TMR_CSCTRL_CL1(kQTMR_LoadOnComp2) | TMR_CSCTRL_CL2(kQTMR_LoadOnComp1));
        base->CSCTRL = reg;

        if (outputPolarity)
        {
            /* Invert the polarity */
            base->SCTRL |= TMR_SCTRL_OPS_MASK;
        }
        else
        {
            /* True polarity, no inversion */
            base->SCTRL &= ~(uint16_t)TMR_SCTRL_OPS_MASK;
        }

        reg = base->CTRL;
        reg &= ~(uint16_t)TMR_CTRL_OUTMODE_MASK;
        /* Count until compare value is  reached and re-initialize the counter, toggle OFLAG output
         * using alternating compare register
         */
        reg |= (TMR_CTRL_LENGTH_MASK | TMR_CTRL_OUTMODE(kQTMR_ToggleOnAltCompareReg));
        base->CTRL = reg;
    }
    else
    {
        /* Invalid dutycycle */
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Allows the user to count the source clock cycles until a capture event arrives.
 *
 * The count is stored in the capture register.
 *
 * param base            Quad Timer peripheral base address
 * param capturePin      Pin through which we receive the input signal to trigger the capture
 * param inputPolarity   true: invert polarity of the input signal, false: no inversion
 * param reloadOnCapture true: reload the counter when an input capture occurs, false: no reload
 * param captureMode     Specifies which edge of the input signal  triggers a capture
 */
void QTMR_SetupInputCapture(TMR_Type *base,
                            qtmr_input_source_t capturePin,
                            bool inputPolarity,
                            bool reloadOnCapture,
                            qtmr_input_capture_edge_t captureMode)
{
    uint16_t reg;

    /* Clear the prior value for the input source for capture */
    reg = base->CTRL & (~(uint16_t)TMR_CTRL_SCS_MASK);

    /* Set the new input source */
    reg |= TMR_CTRL_SCS(capturePin);
    base->CTRL = reg;

    /* Clear the prior values for input polarity, capture mode. Set the external pin as input */
    reg = base->SCTRL &
          (~((uint16_t)TMR_SCTRL_IPS_MASK | (uint16_t)TMR_SCTRL_CAPTURE_MODE_MASK | (uint16_t)TMR_SCTRL_OEN_MASK));
    /* Set the new values */
    reg |= (TMR_SCTRL_IPS(inputPolarity) | TMR_SCTRL_CAPTURE_MODE(captureMode));
    base->SCTRL = reg;

    /* Setup if counter should reload when a capture occurs */
    if (reloadOnCapture)
    {
        base->CSCTRL |= TMR_CSCTRL_ROC_MASK;
    }
    else
    {
        base->CSCTRL &= ~(uint16_t)TMR_CSCTRL_ROC_MASK;
    }
}

/*!
 * brief Enables the selected Quad Timer interrupts
 *
 * param base Quad Timer peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::qtmr_interrupt_enable_t
 */
void QTMR_EnableInterrupts(TMR_Type *base, uint32_t mask)
{
    uint16_t reg;

    reg = base->SCTRL;
    /* Compare interrupt */
    if (0U != (mask & (uint32_t)kQTMR_CompareInterruptEnable))
    {
        reg |= TMR_SCTRL_TCFIE_MASK;
    }
    /* Overflow interrupt */
    if (0U != (mask & (uint32_t)kQTMR_OverflowInterruptEnable))
    {
        reg |= TMR_SCTRL_TOFIE_MASK;
    }
    /* Input edge interrupt */
    if (0U != (mask & (uint32_t)kQTMR_EdgeInterruptEnable))
    {
        reg |= TMR_SCTRL_IEFIE_MASK;
    }
    base->SCTRL = reg;

    reg = base->CSCTRL;
    /* Compare 1 interrupt */
    if (0U != (mask & (uint32_t)kQTMR_Compare1InterruptEnable))
    {
        reg |= TMR_CSCTRL_TCF1EN_MASK;
    }
    /* Compare 2 interrupt */
    if (0U != (mask & (uint32_t)kQTMR_Compare2InterruptEnable))
    {
        reg |= TMR_CSCTRL_TCF2EN_MASK;
    }
    base->CSCTRL = reg;
}

/*!
 * brief Disables the selected Quad Timer interrupts
 *
 * param base Quad Timer peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::qtmr_interrupt_enable_t
 */
void QTMR_DisableInterrupts(TMR_Type *base, uint32_t mask)
{
    uint16_t reg;

    reg = base->SCTRL;
    /* Compare interrupt */
    if (0U != (mask & (uint32_t)kQTMR_CompareInterruptEnable))
    {
        reg &= ~(uint16_t)TMR_SCTRL_TCFIE_MASK;
    }
    /* Overflow interrupt */
    if (0U != (mask & (uint32_t)kQTMR_OverflowInterruptEnable))
    {
        reg &= ~(uint16_t)TMR_SCTRL_TOFIE_MASK;
    }
    /* Input edge interrupt */
    if (0U != (mask & (uint32_t)kQTMR_EdgeInterruptEnable))
    {
        reg &= ~(uint16_t)TMR_SCTRL_IEFIE_MASK;
    }
    base->SCTRL = reg;

    reg = base->CSCTRL;
    /* Compare 1 interrupt */
    if (0U != (mask & (uint32_t)kQTMR_Compare1InterruptEnable))
    {
        reg &= ~(uint16_t)TMR_CSCTRL_TCF1EN_MASK;
    }
    /* Compare 2 interrupt */
    if (0U != (mask & (uint32_t)kQTMR_Compare2InterruptEnable))
    {
        reg &= ~(uint16_t)TMR_CSCTRL_TCF2EN_MASK;
    }
    base->CSCTRL = reg;
}

/*!
 * brief Gets the enabled Quad Timer interrupts
 *
 * param base Quad Timer peripheral base address
 *
 * return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::qtmr_interrupt_enable_t
 */
uint32_t QTMR_GetEnabledInterrupts(TMR_Type *base)
{
    uint32_t enabledInterrupts = 0;
    uint16_t reg;

    reg = base->SCTRL;
    /* Compare interrupt */
    if (0U != (reg & TMR_SCTRL_TCFIE_MASK))
    {
        enabledInterrupts |= (uint32_t)kQTMR_CompareFlag;
    }
    /* Overflow interrupt */
    if (0U != (reg & TMR_SCTRL_TOFIE_MASK))
    {
        enabledInterrupts |= (uint32_t)kQTMR_OverflowInterruptEnable;
    }
    /* Input edge interrupt */
    if (0U != (reg & TMR_SCTRL_IEFIE_MASK))
    {
        enabledInterrupts |= (uint32_t)kQTMR_EdgeInterruptEnable;
    }

    reg = base->CSCTRL;
    /* Compare 1 interrupt */
    if (0U != (reg & TMR_CSCTRL_TCF1EN_MASK))
    {
        enabledInterrupts |= (uint32_t)kQTMR_Compare1InterruptEnable;
    }
    /* Compare 2 interrupt */
    if (0U != (reg & TMR_CSCTRL_TCF2EN_MASK))
    {
        enabledInterrupts |= (uint32_t)kQTMR_Compare2InterruptEnable;
    }

    return enabledInterrupts;
}

/*!
 * brief Gets the Quad Timer status flags
 *
 * param base Quad Timer peripheral base address
 *
 * return The status flags. This is the logical OR of members of the
 *         enumeration ::qtmr_status_flags_t
 */
uint32_t QTMR_GetStatus(TMR_Type *base)
{
    uint32_t statusFlags = 0;
    uint16_t reg;

    reg = base->SCTRL;
    /* Timer compare flag */
    if (0U != (reg & TMR_SCTRL_TCF_MASK))
    {
        statusFlags |= (uint32_t)kQTMR_CompareFlag;
    }
    /* Timer overflow flag */
    if (0U != (reg & TMR_SCTRL_TOF_MASK))
    {
        statusFlags |= (uint32_t)kQTMR_OverflowFlag;
    }
    /* Input edge flag */
    if (0U != (reg & TMR_SCTRL_IEF_MASK))
    {
        statusFlags |= (uint32_t)kQTMR_EdgeFlag;
    }

    reg = base->CSCTRL;
    /* Compare 1 flag */
    if (0U != (reg & TMR_CSCTRL_TCF1_MASK))
    {
        statusFlags |= (uint32_t)kQTMR_Compare1Flag;
    }
    /* Compare 2 flag */
    if (0U != (reg & TMR_CSCTRL_TCF2_MASK))
    {
        statusFlags |= (uint32_t)kQTMR_Compare2Flag;
    }

    return statusFlags;
}

/*!
 * brief Clears the Quad Timer status flags.
 *
 * param base Quad Timer peripheral base address
 * param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::qtmr_status_flags_t
 */
void QTMR_ClearStatusFlags(TMR_Type *base, uint32_t mask)
{
    uint16_t reg;

    reg = base->SCTRL;
    /* Timer compare flag */
    if (0U != (mask & (uint32_t)kQTMR_CompareFlag))
    {
        reg &= ~(uint16_t)TMR_SCTRL_TCF_MASK;
    }
    /* Timer overflow flag */
    if (0U != (mask & (uint32_t)kQTMR_OverflowFlag))
    {
        reg &= ~(uint16_t)TMR_SCTRL_TOF_MASK;
    }
    /* Input edge flag */
    if (0U != (mask & (uint32_t)kQTMR_EdgeFlag))
    {
        reg &= ~(uint16_t)TMR_SCTRL_IEF_MASK;
    }
    base->SCTRL = reg;

    reg = base->CSCTRL;
    /* Compare 1 flag */
    if (0U != (mask & (uint32_t)kQTMR_Compare1Flag))
    {
        reg &= ~(uint16_t)TMR_CSCTRL_TCF1_MASK;
    }
    /* Compare 2 flag */
    if (0U != (mask & (uint32_t)kQTMR_Compare2Flag))
    {
        reg &= ~(uint16_t)TMR_CSCTRL_TCF2_MASK;
    }
    base->CSCTRL = reg;
}

/*!
 * brief Sets the timer period in ticks.
 *
 * Timers counts from initial value till it equals the count value set here. The counter
 * will then reinitialize to the value specified in the Load register.
 *
 * note
 * 1. This function will write the time period in ticks to COMP1 or COMP2 register
 *    depending on the count direction
 * 2. User can call the utility macros provided in fsl_common.h to convert to ticks
 * 3. This function supports cases, providing only primary source clock without secondary source clock.
 *
 * param base  Quad Timer peripheral base address
 * param ticks Timer period in units of ticks
 */
void QTMR_SetTimerPeriod(TMR_Type *base, uint16_t ticks)
{
    /* Set the length bit to reinitialize the counters on a match */
    base->CTRL |= TMR_CTRL_LENGTH_MASK;

    if (0U != (base->CTRL & TMR_CTRL_DIR_MASK))
    {
        /* Counting down */
        base->COMP2 = ticks;
    }
    else
    {
        /* Counting up */
        base->COMP1 = ticks;
    }
}
