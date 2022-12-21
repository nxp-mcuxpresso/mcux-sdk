/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file gpio_driver_irq.c
 * @brief The gpio_driver_irq.c file containes the Generic IRQ implmentation for GPIO.
*/

#include "fsl_gint.h"

extern void issdk_gpio_handle_interrupt(GINT_Type *base, gint_port_t portNumber);

/*******************************************************************************
 * Functions - GPIOIRQ implementation
 ******************************************************************/
#if defined(GINT0)
void PORT0_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT0, kGINT_Port0);
}
#endif
#if defined(GINT1)
void PORT1_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT1, kGINT_Port1);
}
#endif
#if defined(GINT2)
void PORT2_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT2, kGINT_Port2);
}
#endif
#if defined(GINT3)
void PORT3_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT3, kGINT_Port3);
}
#endif
#if defined(GINT4)
void PORT4_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT4, kGINT_Port4);
}
#endif
#if defined(GINT5)
void PORT5_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT5, kGINT_Port5);
}
#endif
#if defined(GINT6)
void PORT6_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT6, kGINT_Port6);
}
#endif
#if defined(GINT7)
void PORT7_IRQHandler(void)
{
    issdk_gpio_handle_interrupt(GINT7, kGINT_Port7);
}
#endif
