/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file gpio_driver_irq.c
 * @brief The gpio_driver_irq.c file containes the Generic IRQ implmentation for GPIO.
*/

#include "fsl_gpio.h"
#include "gpio_driver.h"

extern void imxsdk_gpio_handle_interrupt(GPIO_Type *base, port_number_t gpioPortNumber);

/*******************************************************************************
 * Functions - GPIOIRQ implementation
 ******************************************************************/

void GPIO1_Combined_0_15_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO1, GPIO1_NUM);
}

void GPIO1_Combined_16_31_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO1, GPIO1_NUM);
}

void GPIO2_Combined_0_15_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO2, GPIO2_NUM);
}

void GPIO2_Combined_16_31_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO2, GPIO2_NUM);
}

void GPIO3_Combined_0_15_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO3, GPIO3_NUM);
}

void GPIO3_Combined_16_31_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO3, GPIO3_NUM);
}

#if !defined(CPU_MIMXRT1021DAG5A) && !defined(CPU_MIMXRT1024DAG5A)
void GPIO4_Combined_0_15_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO4, GPIO4_NUM);
}

void GPIO4_Combined_16_31_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO4, GPIO4_NUM);
}
#endif

void GPIO5_Combined_0_15_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO5, GPIO5_NUM);
}

void GPIO5_Combined_16_31_IRQHandler (void)
{
    imxsdk_gpio_handle_interrupt(GPIO5, GPIO5_NUM);
}
