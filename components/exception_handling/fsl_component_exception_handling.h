/*
 * Copyright 2019 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __EXCEPTION_HANDLING_H__
#define __EXCEPTION_HANDLING_H__

#include "fsl_debug_console.h"

/*! @addtogroup Exception */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Configurations
 ******************************************************************************/

/*! @brief Enable or disable exception handling log (1 - enable, 0 - disable) */
#ifndef EXCEPTION_HANDLING_LOG_ENABLE
#define EXCEPTION_HANDLING_LOG_ENABLE (0U)
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief exception stack data structure. */
typedef struct _exception_stack_data_t
{
    /* Software save */
    uint32_t IPSR;
    uint32_t SP;
    /* Hardware save */
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R12;
    uint32_t LR;
    uint32_t PC;
    uint32_t xPSR;
} exception_stack_data_t;

/*! @brief scb data structure. */
typedef struct _scb_data_text
{
    uint16_t type;   /*!< scb register address type, 32 means uint32_t type address, 8 means uint8_t type address */
    uint16_t offset; /*!< scb register address offset */
    char *str;       /*!< string buffer pointer to scb register description string */
} scb_data_text_t;

#if (defined(EXCEPTION_HANDLING_LOG_ENABLE) && (EXCEPTION_HANDLING_LOG_ENABLE == 1U))
#if defined(DEBUG_CONSOLE_TRANSFER_NON_BLOCKING)
#define EXCEPTION_PRINTF DbgConsole_BlockingPrintf
#else
#define EXCEPTION_PRINTF DbgConsole_Printf
#endif
#else
#define EXCEPTION_PRINTF \
    do                   \
    {                    \
    } while (0)
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Exception data print function.
 *
 * This function should be called at first place in the ISR where the R0-R3, R12, LR, PC and xPSR
 * have been saved in the stack by ARM,
 * so that the SP and IPSR could be saved right after them. By default, exception handling module will
 * overwrite the following ISR as the reference:
 * NMI_Handler, HardFault_Handler, MemManage_Handler, BusFault_Handler, UsageFault_Handler.
 * The users can refer to these ISRs to have their owner ISRs to output the stack frame information.
 *
 * At last, all the stack frame information would be output from UART instance initialized in the debug
 * console if EXCEPTION_HANDLING_LOG_ENABLE is set to 1.
 * USB CDC could not be supported.
 * SWO is not supported yet.
 * If no UART instance is initialized because debug console is not enabled or there is no HW UART instance available,
 * the users need to route EXCEPTION_PRINTF to an available IO function to output the stack frame information.
 * This function should NOT be called in the task context.
 *
 * @note For MCUXpresso IDE, make sure unselect Include semihost Hardfault handler feature on SDK import wizard,
 * otherwise HardFault_Handler function of semihost_hardfault.c project will be used on MCUXpresso project.
 * Make sure __SEMIHOST_HARDFAULT_DISABLE Macro is defined in if want to use  HardFault_Handler function
 * in exception_handling.c.
 *
 * @retval No return vaule.
 */
void EXCEPTION_DataPrint(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

#endif /* __EXCEPTION_HANDLING_H__ */
