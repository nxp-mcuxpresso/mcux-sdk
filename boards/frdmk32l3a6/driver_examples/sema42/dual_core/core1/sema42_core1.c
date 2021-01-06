/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_sema42.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_mu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_MU     MUB
#define APP_SEMA42 SEMA420
#define LED_OFF()  LED1_OFF()
/* Flag indicates Core Boot Up*/
#define BOOT_FLAG 0x01U
/* Flag indicates Core 0 has locked the sema42 gate. */
#define SEMA42_LOCK_FLAG 0x02U
/* Flag indicates Core 1 has locked the sema42 gate. */
#define SEMA42_CORE1_LOCK_FLAG 0x03U
/* The SEMA42 gate */
#define SEMA42_GATE 0U

/*
 * Use core 0 to boot core 1.
 * When set to 1, the core 0 assign domain ID for core 0 and core 1, then boot core 1.
 * When set to 0, core 0 and core 1 are boot up by uboot or other component, and
 * they assign their own domain ID seperately.
 */
#ifndef CORE0_BOOT_CORE1
#define CORE0_BOOT_CORE1 1
#endif

/*
 * Use static domain ID or dynamic domain ID.
 */
#ifndef USE_STATIC_DOMAIN_ID
#define USE_STATIC_DOMAIN_ID 1
#endif

/*
 * The board has LED to show the status.
 */
#ifndef APP_BOARD_HAS_LED
#define APP_BOARD_HAS_LED 1
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if USE_STATIC_DOMAIN_ID
uint8_t APP_GetCore1DomainID(void)
{
    return 1U;
}
#else
uint8_t APP_GetCore1DomainID(void);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t domainId;

    BOARD_InitPins_Core1();

#if !CORE0_BOOT_CORE1
    APP_InitCore1Domain();
#endif

    /* MUB init */
    MU_Init(APP_MU);

    /* Synchronize with core 0, make sure all resources are ready. */
    while (BOOT_FLAG != MU_GetFlags(APP_MU))
    {
    }

    /* Send flag to Core 0 to indicate Core 1 has startup */
    MU_SetFlags(APP_MU, BOOT_FLAG);

    /* Wait for core 1 lock the sema42 gate. */
    while (SEMA42_LOCK_FLAG != MU_GetFlags(APP_MU))
    {
    }

    /* SEMA42 init */
    SEMA42_Init(APP_SEMA42);

    domainId = APP_GetCore1DomainID();

    /* Lock the sema42 gate. */
    SEMA42_Lock(APP_SEMA42, SEMA42_GATE, domainId);

#if APP_BOARD_HAS_LED
    /* Turn off led */
    LED_OFF();
#endif

    /* Send flag to Core 0 to indicate Core 1 has locked the semaphore. */
    MU_SetFlags(APP_MU, SEMA42_CORE1_LOCK_FLAG);

    while (1)
    {
    }
}
