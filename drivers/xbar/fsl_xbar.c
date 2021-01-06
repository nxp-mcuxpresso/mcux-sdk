/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xbar.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xbar"
#endif

/* Macros for entire XBAR_CTRL register.  */
#define XBAR_CTRLx(base, index) (((volatile uint16_t *)(&((base)->CTRL0)))[(index)])

typedef union
{
    uint8_t _u8[2];
    uint16_t _u16;
} xbar_u8_u16_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the XBAR instance from peripheral base address.
 *
 * @param base XBAR peripheral base address.
 * @return XBAR instance.
 */
static uint32_t XBAR_GetInstance(XBAR_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of XBAR peripheral base address. */
static XBAR_Type *const s_xbarBases[] = XBAR_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of XBAR clock name. */
static const clock_ip_name_t s_xbarClock[] = XBAR_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t XBAR_GetInstance(XBAR_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_xbarBases); instance++)
    {
        if (s_xbarBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_xbarBases));

    return instance;
}

/*!
 * brief Initializes the XBAR modules.
 *
 * This function un-gates the XBAR clock.
 *
 * param base XBAR peripheral address.
 */
void XBAR_Init(XBAR_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable XBAR module clock. */
    CLOCK_EnableClock(s_xbarClock[XBAR_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Shutdown the XBAR modules.
 *
 * This function disables XBAR clock.
 *
 * param base XBAR peripheral address.
 */
void XBAR_Deinit(XBAR_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable XBAR module clock. */
    CLOCK_DisableClock(s_xbarClock[XBAR_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Set connection between the selected XBAR_IN[*] input and the XBAR_OUT[*] output signal.
 *
 * This function connects the XBAR input to the selected XBAR output.
 * If more than one XBAR module is available, only the inputs and outputs from the same module
 * can be connected.
 *
 * Example:
   code
   XBAR_SetSignalsConnection(XBAR, kXBAR_InputTMR_CH0_Output, kXBAR_OutputXB_DMA_INT2);
   endcode
 *
 * param base XBAR peripheral address
 * param input XBAR input signal.
 * param output XBAR output signal.
 */
void XBAR_SetSignalsConnection(XBAR_Type *base, xbar_input_signal_t input, xbar_output_signal_t output)
{
    xbar_u8_u16_t regVal;
    uint8_t byteInReg;
    uint8_t outputIndex = (uint8_t)output;

    byteInReg = outputIndex % 2U;

    regVal._u16 = XBAR_SELx(base, outputIndex);

    regVal._u8[byteInReg] = (uint8_t)input;

    XBAR_SELx(base, outputIndex) = regVal._u16;
}

/*!
 * brief Gets the active edge detection status.
 *
 * This function gets the active edge detect status of all XBAR_OUTs. If the
 * active edge occurs, the return value is asserted. When the interrupt or the DMA
 * functionality is enabled for the XBAR_OUTx, this field is 1 when the interrupt
 * or DMA request is asserted and 0 when the interrupt or DMA request has been
 * cleared.
 *
 * Example:
   code
   uint32_t status;

   status = XBAR_GetStatusFlags(XBAR);
   endcode
 *
 * param base XBAR peripheral address.
 * return the mask of these status flag bits.
 */
uint32_t XBAR_GetStatusFlags(XBAR_Type *base)
{
    uint32_t status_flag;

    status_flag = ((uint32_t)base->CTRL0 & (XBAR_CTRL0_STS0_MASK | XBAR_CTRL0_STS1_MASK));

    status_flag |= (((uint32_t)base->CTRL1 & (XBAR_CTRL1_STS2_MASK | XBAR_CTRL1_STS3_MASK)) << 16U);

    return status_flag;
}

/*!
 * brief Clears the edge detection status flags of relative mask.
 *
 * param base XBAR peripheral address
 * param mask the status flags to clear.
 */
void XBAR_ClearStatusFlags(XBAR_Type *base, uint32_t mask)
{
    uint16_t regVal;

    /* Assign regVal to CTRL0 register's value */
    regVal = (base->CTRL0);
    /* Perform this command to avoid writing 1 into interrupt flag bits */
    regVal &= (uint16_t)(~(XBAR_CTRL0_STS0_MASK | XBAR_CTRL0_STS1_MASK));
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= (uint16_t)(mask & (XBAR_CTRL0_STS0_MASK | XBAR_CTRL0_STS1_MASK));
    /* Write regVal value into CTRL0 register */
    base->CTRL0 = regVal;

    /* Assign regVal to CTRL1 register's value */
    regVal = (base->CTRL1);
    /* Perform this command to avoid writing 1 into interrupt flag bits */
    regVal &= (uint16_t)(~(XBAR_CTRL1_STS2_MASK | XBAR_CTRL1_STS3_MASK));
    /* Write 1 to interrupt flag bits corresponding to mask */
    regVal |= (uint16_t)((mask >> 16U) & (XBAR_CTRL1_STS2_MASK | XBAR_CTRL1_STS3_MASK));
    /* Write regVal value into CTRL1 register */
    base->CTRL1 = regVal;
}

/*!
 * brief Configures the XBAR control register.
 *
 * This function configures an XBAR control register. The active edge detection
 * and the DMA/IRQ function on the corresponding XBAR output can be set.
 *
 * Example:
   code
   xbar_control_config_t userConfig;
   userConfig.activeEdge = kXBAR_EdgeRising;
   userConfig.requestType = kXBAR_RequestInterruptEnalbe;
   XBAR_SetOutputSignalConfig(XBAR, kXBAR_OutputXB_DMA_INT0, &userConfig);
   endcode
 *
 * param base XBAR peripheral address
 * param output XBAR output number.
 * param controlConfig Pointer to structure that keeps configuration of control register.
 */
void XBAR_SetOutputSignalConfig(XBAR_Type *base,
                                xbar_output_signal_t output,
                                const xbar_control_config_t *controlConfig)

{
    uint8_t outputIndex = (uint8_t)output;
    uint8_t regIndex;
    uint8_t byteInReg;
    xbar_u8_u16_t regVal;

    assert(outputIndex < (uint32_t)FSL_FEATURE_XBAR_INTERRUPT_COUNT);

    regIndex  = outputIndex / 2U;
    byteInReg = outputIndex % 2U;

    regVal._u16 = XBAR_CTRLx(base, regIndex);

    /* Don't clear the status flags. */
    regVal._u16 &= (uint16_t)(~(XBAR_CTRL0_STS0_MASK | XBAR_CTRL0_STS1_MASK));

    regVal._u8[byteInReg] = (uint8_t)(XBAR_CTRL0_EDGE0(controlConfig->activeEdge) |
                                      (uint16_t)(((uint32_t)controlConfig->requestType) << XBAR_CTRL0_DEN0_SHIFT));

    XBAR_CTRLx(base, regIndex) = regVal._u16;
}
