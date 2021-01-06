/*
** ###################################################################
**     Processor:           MIMX8QX4AVLFZ
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
**     Reference manual:    IMX8DQXPRM, Rev. E, 6/2019
**     Version:             rev. 4.0, 2020-06-19
**     Build:               b200806
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-06-02)
**         Initial version.
**     - rev. 2.0 (2017-08-23)
**         RevA Header EAR
**     - rev. 3.0 (2018-08-22)
**         RevB Header EAR
**     - rev. 4.0 (2020-06-19)
**         RevC Header RFP
**
** ###################################################################
*/

/*!
 * @file MIMX8QX4_cm4
 * @version 1.0
 * @date 060820
 * @brief Device specific configuration file for MIMX8QX4_cm4 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
static sc_ipc_t ipcHandle;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit(void)
{
#if (ENABLE_ECC_DEBUG)
    volatile uint32_t *p = (uint32_t *)0xE0080480U;

    /* Configure LMEM Parity/ECC Control Register
    ;
    ; Note: ECC Multi-bit IRQ should be disabled
    ;       prior to list/dump of locations that
    ;       have not been written to avoid vectoring
    ;       to the NMI
    ;
    ; 31:22 RESERVED
    ; 21    Enable Cache Parity IRQ
    ; 20    Enable Cache Parity Report
    ; 19:17 RESERVED
    ; 16    Enable RAM Parity Reporting
    ; 15:10 RESERVED
    ; 9     Enable RAM ECC 1-bit IRQ
    ; 8     Enable RAM ECC 1-bit Report
    ; 7:2   RESERVED
    ; 1     Enable RAM ECC Multi-bit IRQ
    ; 0     Enable RAM ECC Multi-bit
    */
    *p = 0x00300003;
#endif

#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access */
#endif                                                 /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if (DISABLE_WDOG)
    CM4__WDOG->CNT   = WDOG_UPDATE_KEY;
    CM4__WDOG->TOVAL = 0xFFFF;
    CM4__WDOG->CS    = (uint32_t)((CM4__WDOG->CS) & ~WDOG_CS_EN_MASK) | WDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

    /* Initialize Cache */
    /* Enable Code Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PCCCR |= LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK;
    LMEM->PCCCR |= LMEM_PCCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) != 0UL)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PCCCR |= (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);

    /* Enable System Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PSCCR |= LMEM_PSCCR_INVW1_MASK | LMEM_PSCCR_INVW0_MASK;
    LMEM->PSCCR |= LMEM_PSCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) != 0UL)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PSCCR |= (LMEM_PSCCR_ENWRBUF_MASK | LMEM_PSCCR_ENCACHE_MASK);
    /* i.MX8QX systemInit */
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    /* i.MX8QX SystemCoreClockUpdate */
    sc_err_t err;
    uint32_t freq = SystemCoreClock;

    err = sc_pm_get_clock_rate(ipcHandle, SC_R_M4_0_PID0, SC_PM_CLK_CPU, &freq);

    if (SC_ERR_NONE == err)
    {
        SystemCoreClock = freq;
    }
}

/* ----------------------------------------------------------------------------
   -- SystemInitScfwIpc()
   ---------------------------------------------------------------------------- */

void SystemInitScfwIpc(void)
{
    sc_ipc_t ipc;
    sc_err_t err;

    err = sc_ipc_open(&ipc, (sc_ipc_id_t)CM4__MU1_A);

    if (err == SC_ERR_NONE)
    {
        ipcHandle = ipc;
    }
    else
    {
        ipcHandle = 0;
    }
}

/* ----------------------------------------------------------------------------
   -- SystemGetScfwIpcHandle()
   ---------------------------------------------------------------------------- */

sc_ipc_t SystemGetScfwIpcHandle(void)
{
    return ipcHandle;
}
