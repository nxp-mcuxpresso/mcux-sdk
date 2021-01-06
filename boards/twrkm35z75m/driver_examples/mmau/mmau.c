/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_mmau.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Calculate sin(x)
 * This function calculates sin(x) by Tailor series:
 * f(x) ~ a[0]*x + a[1]&x^3 + a[2]&x^5 + a[3]&x^7 + a[4]&x^9 + a[5]&x^11 + a[6]&x^13
 * or f(x) ~ ((((((a[6]*x*x + a[5])*x*x + a[4])*x*x +a[3])*x*x + a[2])*x*x + a[1])*x*x + a[0]
 * where a[i] = ((-i)^i) * (pi^i) / (i!)
 * In this example, in order to use q fractal format the function has to be modified:
 * f(pi*x) = 2*pi*(a[0]*x + a[1]&x^3 + a[2]&x^5 + a[3]&x^7 + a[4]&x^9 + a[5]&x^11 + a[6]&x^13)
 * where (-1<=x<=1) and a[i] = ((-i)^i) * (pi^(i-1) /2 /(i!)
 */
static frac32_t sine(frac32_t x)
{
    uint32_t temp             = 0;
    static const frac64_t a[] = {0x4000000000000830ll, -0x694699894C1EDEC0ll, 0x33F3968057894B90ll,
                                 -0xC354723906D7540ll, 0x1AC6805CF356930ll,   -0x26702D548C6050ll,
                                 0x26E8E33F5F5F0ll};

    /* If x > 1/2, change x to x = 1-x */
    if (x > 0x40000000)
    {
        x = 0x7FFFFFFFU - x;
    }
    /* If x < -1/2, change x to x = -1-x */
    else if (x < -0x40000000)
    {
        x = 0x80000000UL - x;
    }
    else
    {
    };
    MMAU_d_mul_dl(a[6], x);            /* acc=    x*a[6]  */
    MMAU_d_maca_dl(a[5], x);           /* acc=acc*x+a[5]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    MMAU_d_maca_dl(a[4], x);           /* acc=acc*x+a[4]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    MMAU_d_maca_dl(a[3], x);           /* acc=acc*x+a[3]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    MMAU_d_maca_dl(a[2], x);           /* acc=acc*x+a[2]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    MMAU_d_maca_dl(a[1], x);           /* acc=acc*x+a[1]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    MMAU_d_maca_dl(a[0], x);           /* acc=acc*x+a[0]  */
    MMAU_d_mula_l(x);                  /* acc=acc*x       */
    temp = MMAU_l_mula_l(0x6487ED51U); /* acc=acc*(2*pi/8)*/
    temp = temp << 3U;                 /* acc=acc*8       */
    return (frac32_t)temp;
}

/*!
 * @brief Main function
 */
int main(void)
{
    frac32_t result;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF("\r\nMMAU example : start\n");

    result = sine((frac32_t)0x7FFFFFFF);
    PRINTF("\r\n Sin(pi)      = 0x%X in frac32 format", result);
    result = sine((frac32_t)0x66666666);
    PRINTF("\r\n Sin(0.8*pi)  = 0x%X in frac32 format", result);
    result = sine((frac32_t)0x4CCCCCCD);
    PRINTF("\r\n Sin(0.6*pi)  = 0x%X in frac32 format", result);
    result = sine((frac32_t)0x33333333);
    PRINTF("\r\n Sin(0.4*pi)  = 0x%X in frac32 format", result);
    result = sine((frac32_t)0x19999999);
    PRINTF("\r\n Sin(0.2*pi)  = 0x%X in frac32 format", result);
    result = sine(0);
    PRINTF("\r\n Sin(0)       = 0x%X in frac32 format", result);
    result = sine((frac32_t)0x99999999UL);
    PRINTF("\r\n Sin(-0.2*pi) = 0x%X in frac32 format", result);
    result = sine((frac32_t)0xB3333333UL);
    PRINTF("\r\n Sin(-0.4*pi) = 0x%X in frac32 format", result);
    result = sine((frac32_t)0xCCCCCCCDUL);
    PRINTF("\r\n Sin(-0.6*pi) = 0x%X in frac32 format", result);
    result = sine((frac32_t)0xE6666666UL);
    PRINTF("\r\n Sin(-0.8*pi) = 0x%X in frac32 format", result);
    result = sine((frac32_t)(0x80000000UL));
    PRINTF("\r\n Sin(-pi)     = 0x%X in frac32 format\n", result);

    PRINTF("\r\nMMAU example : end\n");
    while (1)
    {
    }
}
