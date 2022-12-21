/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file gpio_driver_irq_ke15z.c
 * @brief The gpio_driver_irq_ke15z.c file containes the Generic IRQ implmentation for the FRDM-KE15Z GPIO.
*/

#include "fsl_gpio.h"
#include "frdm_ke15z.h"

extern void ksdk_gpio_handle_interrupt(GPIO_Type *base, port_number_t portNumber);

/*******************************************************************************
 * Functions - GPIOIRQ implementation
 ******************************************************************/
void PORTAE_IRQHandler(void)
{
    ksdk_gpio_handle_interrupt(GPIO_TYPE, GPIO_PORT_NUM);
}

void PORTBCD_IRQHandler(void)
{
    ksdk_gpio_handle_interrupt(GPIO_TYPE, GPIO_PORT_NUM);
}
