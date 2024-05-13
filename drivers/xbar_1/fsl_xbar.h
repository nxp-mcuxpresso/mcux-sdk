/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_XBAR_H_
#define FSL_XBAR_H_

#include "fsl_common.h"

/*!
 * @addtogroup xbar
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FSL_XBAR_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))

/*!
 * @brief Find the instance index from base address and register offset mappings.
 */
typedef struct
{
    volatile uint16_t *baseAddr; /* Peripheral base address. */
    uint16_t regSelOffset;       /* SEL register offset in peripheral. */
    uint16_t regSelNum;          /* SEL register number in peripheral. */
    uint16_t regCtrlOffset;      /* CTRL register offset in peripheral. */
    uint16_t regCtrlNum;         /* CTRL register number in peripheral. */
} xbar_info_t;

/*!
 * @brief XBAR active edge for detection
 */
typedef enum _xbar_active_edge
{
    kXBAR_EdgeNone             = 0U, /*!< Edge detection status bit never asserts. */
    kXBAR_EdgeRising           = 1U, /*!< Edge detection status bit asserts on rising edges. */
    kXBAR_EdgeFalling          = 2U, /*!< Edge detection status bit asserts on falling edges. */
    kXBAR_EdgeRisingAndFalling = 3U  /*!< Edge detection status bit asserts on rising and falling edges. */
} xbar_active_edge_t;

/*!
 * @brief Defines the XBAR DMA and interrupt configurations.
 */
typedef enum _xbar_request
{
    kXBAR_RequestDisable         = 0U, /*!< Interrupt and DMA are disabled. */
    kXBAR_RequestDMAEnable       = 1U, /*!< DMA enabled, interrupt disabled. */
    kXBAR_RequestInterruptEnable = 2U  /*!< Interrupt enabled, DMA disabled. */
} xbar_request_t;

/*!
 * @brief Defines the configuration structure of the XBAR control register.
 *
 * This structure keeps the configuration of XBAR control register for one output.
 * Control registers are available only for a few outputs. Not every XBAR module has
 * control registers.
 */
typedef struct _xbar_control_config
{
    xbar_active_edge_t activeEdge; /*!< Active edge to be detected. */
    xbar_request_t requestType;    /*!< Selects DMA/Interrupt request. */
} xbar_control_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name XBAR functional Operation
 * @{
 */

/*!
 * @brief Initializes the XBAR modules.
 *
 * This function un-gates the XBAR clock.
 *
 * @param xbarInstance XBAR peripheral address.
 */
void XBAR_Init(xbar_instance_t xbarInstance);

/*!
 * @brief Shutdown the XBAR modules.
 *
 * This function disables XBAR clock.
 *
 * @param xbarInstance XBAR peripheral address.
 */
void XBAR_Deinit(xbar_instance_t xbarInstance);

/*!
 * @brief Set connection between the selected XBAR_IN[*] input and the XBAR_OUT[*] output signal.
 *
 * This function connects the XBAR input to the selected XBAR output.
 * If more than one XBAR module is available, only the inputs and outputs from the same module
 * can be connected.
 *
 * Example:
   @code
   XBAR_SetSignalsConnection(kXBAR_DSC1_InputLogicLow, kXBAR_DSC1_OutputTriggerSyncIn0);
   @endcode
 *
 * @param input XBAR input signal.
 * @param output XBAR output signal.
 * @retval kStatus_Success Signal connection set successfully.
 * @retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t XBAR_SetSignalsConnection(xbar_input_signal_t input, xbar_output_signal_t output);

/*!
 * @brief Clears the edge detection status flags.
 *
 * @param output XBAR output signal.
 * @retval kStatus_Success Signal connection set successfully.
 * @retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t XBAR_ClearOutputStatusFlag(xbar_output_signal_t output);

/*!
 * @brief Gets the active edge detection status.
 *
 * This function gets the active edge detect status of all XBAR_OUTs. If the
 * active edge occurs, the return value is asserted. When the interrupt or the DMA
 * functionality is enabled for the XBAR_OUTx, this field is 1 when the interrupt
 * or DMA request is asserted and 0 when the interrupt or DMA request has been
 * cleared.
 *
 * @param output XBAR output signal.
 * @param flag get XBAR output status flag.
 * @retval kStatus_Success Signal connection set successfully.
 * @retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t XBAR_GetOutputStatusFlag(xbar_output_signal_t output, bool *flag);

/*!
 * @brief Configures the XBAR control register.
 *
 * This function configures an XBAR control register. The active edge detection
 * and the DMA/IRQ function on the corresponding XBAR output can be set.
 *
 * Example:
   @code
   xbar_control_config_t userConfig;
   userConfig.activeEdge = kXBAR_EdgeRising;
   userConfig.requestType = kXBAR_RequestInterruptEnable;
   XBAR_SetOutputSignalConfig(kXBARA_OutputDMAMUX18, &userConfig);
   @endcode
 *
 * @param output XBAR output signal.
 * @param controlConfig Pointer to structure that keeps configuration of control register.
 * @retval kStatus_Success Signal connection set successfully.
 * @retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t XBAR_SetOutputSignalConfig(xbar_output_signal_t output, const xbar_control_config_t *controlConfig);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

/*! @}*/

#endif /* FSL_XBAR_H_ */
