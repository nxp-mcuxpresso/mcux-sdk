/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cwt.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cwt"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Sets the default configuration of CWT
 *
 * This function initialize CWT config structure to default values.
 *
 * param conf CWT configuration structure
 */
void CWT_GetDefaultConfig(cwt_config_t *conf)
{
    /* Default configuration after reset */
    conf->lock       = (uint8_t)kCDOG_LockCtrl_Unlock;    /* Lock control */
    conf->timeout    = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Timeout control */
    conf->miscompare = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Miscompare control */
    conf->sequence   = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Sequence control */
    conf->control    = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Control */
    conf->state      = (uint8_t)kCDOG_FaultCtrl_NoAction; /* State control */
    conf->address    = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Address control */
    conf->irq_pause  = (uint8_t)kCDOG_IrqPauseCtrl_Run;   /* IRQ pause control */
    conf->debug_halt = (uint8_t)kCDOG_DebugHaltCtrl_Run;  /* Debug halt control */
    return;
}

/*!
 * brief Sets secure counter and instruction timer values
 *
 * This function sets value in RELOAD and START registers for instruction timer.
 *
 * param base CWT peripheral base address
 * param reload reload value
 * param start start value
 */
void CWT_Start(CDOG_Type *base, uint32_t reload, uint32_t start)
{
    base->RELOAD = reload;
    base->START  = start;
}

/*!
 * brief Stops secure counter and instruction timer
 *
 * This function stops instruction timer and secure counter.
 * This also change state of CWT to IDLE.
 *
 * param base CWT peripheral base address
 * param stop expected value which will be compared with value of secure counter
 */
void CWT_Stop(CDOG_Type *base, uint32_t stop)
{
    base->STOP = stop;
}

/*!
 * brief Sets secure counter and instruction timer values
 *
 * This function sets value in STOP, RELOAD and START registers
 * for instruction timer and secure counter.
 *
 * param base CWT peripheral base address
 * param stop expected value which will be compared with value of secure counter
 * param reload reload value for instruction timer
 * param start start value for secure timer
 */
void CWT_Set(CDOG_Type *base, uint32_t stop, uint32_t reload, uint32_t start)
{
    base->STOP   = stop;
    base->RELOAD = reload;
    base->START  = start;
}

/*!
 * brief Add value to secure counter
 *
 * This function add specified value to secure counter.
 *
 * param base CWT peripheral base address.
 * param add Value to be added.
 */
void CWT_Add(CDOG_Type *base, uint32_t add)
{
    base->ADD = (secure_counter_t)add;
}

/*!
 * brief Add 1 to secure counter
 *
 * This function add 1 to secure counter.
 *
 * param base CWT peripheral base address.
 * param add Value to be added.
 */
void CWT_Add1(CDOG_Type *base)
{
    base->ADD1 = (secure_counter_t)0x1U;
}

/*!
 * brief Add 16 to secure counter
 *
 * This function add 16 to secure counter.
 *
 * param base CWT peripheral base address.
 * param add Value to be added.
 */
void CWT_Add16(CDOG_Type *base)
{
    base->ADD16 = (secure_counter_t)0x1U;
}

/*!
 * brief Add 256 to secure counter
 *
 * This function add 256 to secure counter.
 *
 * param base CWT peripheral base address.
 * param add Value to be added.
 */
void CWT_Add256(CDOG_Type *base)
{
    base->ADD256 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract value to secure counter
 *
 * This function substract specified value to secure counter.
 *
 * param base CWT peripheral base address.
 * param sub Value to be substracted.
 */
void CWT_Sub(CDOG_Type *base, uint32_t sub)
{
    base->SUB = (secure_counter_t)sub;
}

/*!
 * brief Substract 1 from secure counter
 *
 * This function substract specified 1 from secure counter.
 *
 * param base CWT peripheral base address.
 */
void CWT_Sub1(CDOG_Type *base)
{
    base->SUB1 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract 16 from secure counter
 *
 * This function substract specified 16 from secure counter.
 *
 * param base CWT peripheral base address.
 */
void CWT_Sub16(CDOG_Type *base)
{
    base->SUB16 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract 256 from secure counter
 *
 * This function substract specified 256 from secure counter.
 *
 * param base CWT peripheral base address.
 */
void CWT_Sub256(CDOG_Type *base)
{
    base->SUB256 = (secure_counter_t)0x1U;
}

/*!
 * brief Checks secure counter.
 *
 * This function compares stop value with secure counter value
 * by writting to RELOAD refister.
 *
 * param base CWT peripheral base address
 * param check expected (stop) value.
 */
void CWT_Check(CDOG_Type *base, uint32_t check)
{
    base->RESTART = check;
}

/*!
 * brief Set the CWT persistent word.
 *
 * param base CWT peripheral base address.
 * param value The value to be written.
 */
void CWT_WritePersistent(CDOG_Type *base, uint32_t value)
{
    base->PERSISTENT = value;
}

/*!
 * brief Get the CWT persistent word.
 *
 * param base CWT peripheral base address.
 * return The persistent word.
 */
uint32_t CWT_ReadPersistent(CDOG_Type *base)
{
    return base->PERSISTENT;
}

/*!
 * brief Initialize CWT
 *
 * This function initializes CWT block and setting.
 *
 * param base CWT peripheral base address
 * param conf CWT configuration structure
 * return Status of the init operation
 */
status_t CWT_Init(CDOG_Type *base, cwt_config_t *conf)
{
    /* Ungate clock to CWT engine and reset it */
    CLOCK_EnableClock(kCLOCK_Cwt);
    RESET_PeripheralReset(kCWT_RST_SHIFT_RSTn);

    if (base->CONTROL == 0x0U)
    {
        /* CWT is not in IDLE mode, which may be cause after SW reset. */
        /* Writing to CONTROL register will trigger fault. */
        return kStatus_Fail;
    }

    /* Clear pending errors, otherwise the device will reset */
    /* itself immediately after enable Code Watchdog */
    if ((uint32_t)kCDOG_LockCtrl_Lock ==
        ((base->CONTROL & CDOG_CONTROL_LOCK_CTRL_MASK) >> CDOG_CONTROL_LOCK_CTRL_SHIFT))

    {
        CDOG->FLAGS = CDOG_FLAGS_TO_FLAG(1U) | CDOG_FLAGS_MISCOM_FLAG(1U) | CDOG_FLAGS_SEQ_FLAG(1U) |
                      CDOG_FLAGS_CNT_FLAG(1U) | CDOG_FLAGS_STATE_FLAG(1U) | CDOG_FLAGS_ADDR_FLAG(1U) |
                      CDOG_FLAGS_POR_FLAG(1U);
    }
    else
    {
        CDOG->FLAGS = CDOG_FLAGS_TO_FLAG(0U) | CDOG_FLAGS_MISCOM_FLAG(0U) | CDOG_FLAGS_SEQ_FLAG(0U) |
                      CDOG_FLAGS_CNT_FLAG(0U) | CDOG_FLAGS_STATE_FLAG(0U) | CDOG_FLAGS_ADDR_FLAG(0U) |
                      CDOG_FLAGS_POR_FLAG(0U);
    }

    base->CONTROL =
        CDOG_CONTROL_TIMEOUT_CTRL(conf->timeout) |       /* Action if the timeout event is triggered  */
        CDOG_CONTROL_MISCOMPARE_CTRL(conf->miscompare) | /* Action if the miscompare error event is triggered  */
        CDOG_CONTROL_SEQUENCE_CTRL(conf->sequence) |     /* Action if the sequence error event is triggered  */
        CDOG_CONTROL_CONTROL_CTRL(conf->control) |       /* Action if the control error event is triggered  */
        CDOG_CONTROL_STATE_CTRL(conf->state) |           /* Action if the state error event is triggered  */
        CDOG_CONTROL_ADDRESS_CTRL(conf->address) |       /* Action if the address error event is triggered */
        CDOG_CONTROL_IRQ_PAUSE(conf->irq_pause) |        /* Pause running during interrupts setup */
        CDOG_CONTROL_DEBUG_HALT_CTRL(
            conf->debug_halt) |             /* Halt CWT timer during debug so we have chance to debug code */
        CDOG_CONTROL_LOCK_CTRL(conf->lock); /* Lock control register */

    NVIC_EnableIRQ(CodeWDG_IRQn);

    return kStatus_Success;
}

/*!
 * brief Deinitialize CWT
 *
 * This function stops CWT secure counter.
 *
 * param base CWT peripheral base address
 */
void CWT_Deinit(CDOG_Type *base)
{
    NVIC_DisableIRQ(CodeWDG_IRQn);

    RESET_SetPeripheralReset(kCWT_RST_SHIFT_RSTn);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Cwt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
