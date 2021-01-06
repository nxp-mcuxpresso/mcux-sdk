/*
 * Copyright 2017 , NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_port.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.port_ke04"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
 /*!
 * brief Selects pin for modules.
 *
 * This API is used to select the port pin for the module with multiple port pin
 * selection. For example the FTM Channel 0 can be mapped to ether PTA0 or PTB2.
 * Select FTM channel 0 map to PTA0 port pin as:
 * code
 * PORT_SetPinSelect(kPORT_FTM0CH0, kPORT_FTM0_CH0_PTA0);
 * endcode
 *
 * @Note： This API doesn't support to select specified ALT for a given port pin.
 * The ALT feature is automatically selected by hardware according to the
 * ALT priority:
 *     Low -----> high:
 *     Alt1, Alt2, …
 * when peripheral modules has been enabled.
 *
 * If you want to select a specified ALT for a given port pin, please add two more
 * steps after calling PORT_SetPinSelect:
 * 1. Enable module or the port control in the module for the ALT you want to select.
 *   For I2C ALT feature:all port enable is controlled by the module enable, so
 *   set IICEN in I2CX_C1 to enable the port pins for I2C feature.
 *   For KBI ALT feature:each port pin is controlled independently by each bit in KBIx_PE.
 *   set related bit in this register to enable the KBI feature in the port pin.
 * 2. Make sure there is no module enabled with higher priority than the ALT module feature
 *  you want to select.
 *
 * param module   Modules for pin selection.
 *        For NMI/RST module are write-once attribute after reset.
 * param pin   Port pin selection for modules.
 *
 */
void PORT_SetPinSelect(port_module_t module, port_pin_select_t pin)
{
    if (0UL != (uint32_t)pin)
    {
        if (module > kPORT_SWDE)
        {
            SIM->PINSEL |= (uint32_t)module;
        }
        else
        {
            SIM->SOPT |= (uint32_t)module;
        }
    }
    else
    {
        if (module > kPORT_SWDE)
        {
            SIM->PINSEL &= ~ (uint32_t)module;
        }
        else
        {
            SIM->SOPT &= ~ (uint32_t)module;
        }
    }
}
