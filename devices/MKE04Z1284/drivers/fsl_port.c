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
#define FSL_COMPONENT_ID "platform.drivers.port_ke06"
#endif
#define PORT_PINNUMS_EACHPORT (8U)   /* PORT pin numbers in each PTA/PTB etc. */
#define PORT_NUM_EACH_PULLUPREG (4U) /* The port numbers in each pull up register. */
#define FSL_PORT_FILTER_SELECT_BITMASK  (0x3U) /* The filter selection bit width. */
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
 * Note： This API doesn't support to select specified ALT for a given port pin. 
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
    uint32_t pinSelReg;
    uint32_t bitwidth = ((uint32_t)module >> PORT_MODULEPS_BITWIDTH_OFFSET) & PORT_MODULEPS_BITWIDTH_MASK;
    uint32_t shift = (uint32_t)module & ~((uint32_t)PORT_PINSEL_REG_OFFSET | ((uint32_t)PORT_MODULEPS_BITWIDTH_MASK << PORT_MODULEPS_BITWIDTH_OFFSET));

    if (module > kPORT_SWDE)
    {
        if (((uint32_t)module & PORT_PINSEL_REG_OFFSET) == 0U)
        {
            pinSelReg = SIM->PINSEL0 & ~ (((1UL << bitwidth) - 1U) << shift);
            SIM->PINSEL0 = pinSelReg | ((uint32_t)pin << shift);
        }
        else
        {
            pinSelReg = SIM->PINSEL1 & ~ (((1UL << bitwidth) - 1U) << shift);
            SIM->PINSEL1 = pinSelReg | ((uint32_t)pin << shift);
        }
    }
    else
    {
        SIM->SOPT0 = (SIM->SOPT0 & ~(1UL << (uint32_t)module)) | ((uint32_t)pin << (uint32_t)module);
    }
}

/*!
 * brief Selects the glitch filter for input pins.
 *
 * param base   PORT peripheral base pointer.
 * param port   PORT pin, see "port_filter_pin_t".
 * param filter  Filter select, see "port_filter_select_t".
 */
void PORT_SetFilterSelect(PORT_Type *base, port_filter_pin_t port, port_filter_select_t filter)
{
    uint32_t fltReg;

    if ((uint32_t)port < (uint32_t)KPORT_Filter0MAX)
    {
        /* Clear the filed to zero. */
        fltReg = base->IOFLT0 & ~((uint32_t)FSL_PORT_FILTER_SELECT_BITMASK << (uint32_t)port);
        /* Set the filter selection. */
        base->IOFLT0 = ((uint32_t)filter << (uint32_t)port) | fltReg;        
    }
    else
    {
        uint32_t port_unsigned;
        port_unsigned = (uint32_t)port;
        port_unsigned -= PORT_FILTER_REG_OFFSET;
        /* Clear the filed to zero. */
        fltReg = base->IOFLT1 & ~((uint32_t)FSL_PORT_FILTER_SELECT_BITMASK << port_unsigned);
        /* Set the filter selection. */
        base->IOFLT1 = ((uint32_t)filter << port_unsigned) | fltReg;         
    }

}

/*!
 * brief Enables or disables the port pull up.
 *
 * param base   PORT peripheral base pointer.
 * param port   PORT type, such as PTA/PTB/PTC etc, see "port_type_t".
 * param num    PORT pin number, such as 0, 1, 2...
 *               For PTI, only PTI0 ~ PTI6 pins are supported. so when set pull
 *               up feature for PTI, please don't set number 7. see reference manual for more details.
 * param enable  Enable or disable the pull up feature switch.
 */
void PORT_SetPinPullUpEnable(PORT_Type *base, port_type_t port, uint8_t num, bool enable)
{
    if (enable)
    {
        /* Enable the pull up */
        if (port < kPORT_PTE)
        {
            base->PUE0 |= (1UL << (PORT_PINNUMS_EACHPORT * (uint32_t)port + num));
        }
        else if (port < kPORT_PTI)
        {
            base->PUE1 |= (1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));
        }
        else
        {
            base->PUE2 |= (1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - 2U * PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));
        }
    }
    else
    {
        /* Disable the pull up */
        if (port < kPORT_PTE)
        {
            base->PUE0 &= ~(1UL << (PORT_PINNUMS_EACHPORT * (uint32_t)port + (uint32_t)num));
        }
        else if (port < kPORT_PTI)
        {
            base->PUE1 &= ~(1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));
        }
        else
        {
            base->PUE2 &= ~(1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - 2U * PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));            
        }
    }
}
