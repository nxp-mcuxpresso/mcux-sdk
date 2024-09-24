/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_reset.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.reset"
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
 * brief Assert reset to peripheral.
 *
 * Asserts reset signal to specified peripheral module.
 *
 * param peripheral Assert reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_SetPeripheralReset(reset_ip_name_t peripheral)
{
    const uint32_t regIndex = ((uint32_t)peripheral & 0x0000FF00u) >> 8;
    const uint32_t bitPos   = ((uint32_t)peripheral & 0x000000FFu);
    const uint32_t bitMask  = 1UL << bitPos;

    assert(bitPos < 32u);

    switch (regIndex)
    {
#if defined(FSL_RESET_DRIVER_COMPUTE) || defined(FSL_RESET_DRIVER_MEDIA)
        case RST_CTL0_PSCCTL0:
            RSTCTL0->PRSTCTL0_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL1:
            RSTCTL0->PRSTCTL1_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL1 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL2:
            RSTCTL0->PRSTCTL2_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL2 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL3:
            RSTCTL0->PRSTCTL3_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL3 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL4:
            RSTCTL0->PRSTCTL4_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL4 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL5:
            RSTCTL0->PRSTCTL5_SET = bitMask;
            while (0u == (RSTCTL0->PRSTCTL5 & bitMask))
            {
            }
            break;
#endif
#if defined(FSL_RESET_DRIVER_SENSE) || defined(FSL_RESET_DRIVER_MEDIA)
        case RST_CTL1_PSCCTL0:
            RSTCTL1->PRSTCTL0_SET = bitMask;
            while (0u == (RSTCTL1->PRSTCTL0 & bitMask))
            {
            }
            break;
#endif
        case RST_CTL2_PSCCTL0:
            RSTCTL2->PRSTCTL0_SET = bitMask;
            while (0u == (RSTCTL2->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL3_PSCCTL0:
            RSTCTL3->PRSTCTL0_SET = bitMask;
            while (0u == (RSTCTL3->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL3_PSCCTL1:
            RSTCTL3->PRSTCTL1_SET = bitMask;
            while (0u == (RSTCTL3->PRSTCTL1 & bitMask))
            {
            }
            break;
        case RST_CTL4_PSCCTL0:
            RSTCTL4->PRSTCTL0_SET = bitMask;
            while (0u == (RSTCTL4->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL4_PSCCTL1:
            RSTCTL4->PRSTCTL1_SET = bitMask;
            while (0u == (RSTCTL4->PRSTCTL1 & bitMask))
            {
            }
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }
}

/*!
 * brief Clear reset to peripheral.
 *
 * Clears reset signal to specified peripheral module, allows it to operate.
 *
 * param peripheral Clear reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral)
{
    const uint32_t regIndex = ((uint32_t)peripheral & 0x0000FF00u) >> 8;
    const uint32_t bitPos   = ((uint32_t)peripheral & 0x000000FFu);
    const uint32_t bitMask  = 1UL << bitPos;

    assert(bitPos < 32u);

    switch (regIndex)
    {
#if defined(FSL_RESET_DRIVER_COMPUTE) || defined(FSL_RESET_DRIVER_MEDIA)
        case RST_CTL0_PSCCTL0:
            RSTCTL0->PRSTCTL0_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL1:
            RSTCTL0->PRSTCTL1_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL1 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL2:
            RSTCTL0->PRSTCTL2_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL2 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL3:
            RSTCTL0->PRSTCTL3_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL3 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL4:
            RSTCTL0->PRSTCTL4_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL4 & bitMask))
            {
            }
            break;
        case RST_CTL0_PSCCTL5:
            RSTCTL0->PRSTCTL5_CLR = bitMask;
            while (bitMask == (RSTCTL0->PRSTCTL5 & bitMask))
            {
            }
            break;
#endif
#if defined(FSL_RESET_DRIVER_SENSE) || defined(FSL_RESET_DRIVER_MEDIA)
        case RST_CTL1_PSCCTL0:
            RSTCTL1->PRSTCTL0_CLR = bitMask;
            while (bitMask == (RSTCTL1->PRSTCTL0 & bitMask))
            {
            }
            break;
#endif

        case RST_CTL2_PSCCTL0:
            RSTCTL2->PRSTCTL0_CLR = bitMask;
            while (bitMask == (RSTCTL2->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL3_PSCCTL0:
            RSTCTL3->PRSTCTL0_CLR = bitMask;
            while (bitMask == (RSTCTL3->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL3_PSCCTL1:
            RSTCTL3->PRSTCTL1_CLR = bitMask;
            while (bitMask == (RSTCTL3->PRSTCTL1 & bitMask))
            {
            }
            break;
        case RST_CTL4_PSCCTL0:
            RSTCTL4->PRSTCTL0_CLR = bitMask;
            while (bitMask == (RSTCTL4->PRSTCTL0 & bitMask))
            {
            }
            break;
        case RST_CTL4_PSCCTL1:
            RSTCTL4->PRSTCTL1_CLR = bitMask;
            while (bitMask == (RSTCTL4->PRSTCTL1 & bitMask))
            {
            }
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }
}

/*!
 * brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * param peripheral Peripheral to reset. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral)
{
    RESET_SetPeripheralReset(peripheral);
    RESET_ClearPeripheralReset(peripheral);
}
