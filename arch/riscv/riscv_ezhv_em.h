/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_EZHV_EM_H_
#define RISCV_EZHV_EM_H_

#include "riscv_asm.h"

/*!
 * @ingroup RISCV_CoreCustomExtXzezhv
 * @defgroup RISCV_CoreCustomExtXzezhvEm EZH-V EM
 * @brief Event Manager
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name EM CSR registers
 * @{
 */
#define CSR_EZ_EM_CFG0      (2084U)
#define CSR_EZ_EM_CFG1      (2085U)
#define CSR_EZ_EM_VOFFS_01  (2086U)
#define CSR_EZ_EM_VOFFS_23  (2087U)
/*!
 * @}
 */

/*! @brief LIST of EZHV vectored event isr */
typedef enum _ezhv_event_isr_idx
{
    kEM_EventISR_0   = 0U,
    kEM_EventISR_1   = 1U,
    kEM_EventISR_2   = 2U,
    kEM_EventISR_3   = 3U,
    kEM_EventISR_NUM = 4U,
} ezhv_event_isr_idx_t;

/*! @brief function pointer for vectored event isr */
typedef void (*p_eventVectorFunc_t)(void);

/*!
 * @brief Event manager enable mask
 *
 * bit15~bit0  enable the corresponding event on the event bus as a wake up event source
 * bit21~bit16 enable other enable bits in the ez_em_cfg_1 csr register
 */
enum _ez_em_event
{
    /* enable masks used in ez_em_cfg_0/1 */
    kEM_EventBLCOverAll  = (1UL << 0),    /*!< BLC overall status */
    kEM_EventBLC0        = (1UL << 1),    /*!< BLC slice status [0] */
    kEM_EventBLC1        = (1UL << 2),    /*!< BLC slice status [1] */
    kEM_EventBLC2        = (1UL << 3),    /*!< BLC slice status [2] */
    kEM_EventBLC3        = (1UL << 4),    /*!< BLC slice status [3] */
    kEM_EventBLC4        = (1UL << 5),    /*!< BLC slice status [4] */
    kEM_EventBLC5        = (1UL << 6),    /*!< BLC slice status [5] */
    kEM_EventBLC6        = (1UL << 7),    /*!< BLC slice status [6] */
    kEM_EventBLC7        = (1UL << 8),    /*!< BLC slice status [7] */
    kEM_EventDBIU0       = (1UL << 9),    /*!< DBIU event [0] */
    kEM_EventDBIU1       = (1UL << 10),   /*!< DBIU event [1] */
    kEM_EventDBIU2       = (1UL << 11),   /*!< DBIU event [2] */
    kEM_EventDBIU3       = (1UL << 12),   /*!< DBIU event [3] */
    kEM_EventHeartBeat   = (1UL << 14),   /*!< Heart beat status */
    kEM_EventBLCPattern  = (1UL << 15),   /*!< BLC pattern match */
};

/*!
 * @name EM configuration bits
 * @{
 */

/*! Heart beat enable. */
#define EZHV_EM_CFG1_HEN_MASK (1UL << 16)
/*! Wake exit enable. */
#define EZHV_EM_CFG1_WXN_MASK (1UL << 17)
/*! Vector interrupt enable. */
#define EZHV_EM_CFG1_VIE_MASK (1UL << 18)
/*! GPIO value updates wait until next heart beat. */
#define EZHV_EM_CFG1_GHC_MASK (1UL << 20)
/*! Event Auto-Clear. */
#define EZHV_EM_CFG1_EAC_MASK (1UL << 21)
/*!
 * @}
 */

/*!
 * @name EM event status bit offset
 * @{
 */
#define EZHV_EM_STAT_OFFSET        (16U)                              /*!< ez_em_cfg0, bit[31:16] */
#define EZHV_EM_BLC_EN_MSK(n)      (1U<<((n)+1))                      /*!< ez_em_cfg0, enable BLC */
#define EZHV_EM_BLC_ST_MSK(n)      (1U<<((n)+1+EZHV_EM_STAT_OFFSET))  /*!< ez_em_cfg0, status */
#define EZHV_EM_STAT_MASK          (0xFFFF0000U)                      /*!< ez_em_cfg0, event stat mask */
/*!
 * @}
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Read event manager CFG0.
 *
 * @return the register value of em cfg0
 */
static inline uint32_t EZHV_ReadEmCfg0(void)
{
    return (uint32_t)csr_read(CSR_EZ_EM_CFG0);
}

/*!
 * @brief read event manager CFG1
 *
 * @return the register value of em cfg1
 */
static inline uint32_t EZHV_ReadEmCfg1(void)
{
    return (uint32_t)csr_read(CSR_EZ_EM_CFG1);
}

/*!
 * @brief read event manager Voffs01
 *
 * @return register value of voffs01
 */
static inline uint32_t EZHV_ReadEmVoffs01(void)
{
    return (uint32_t)csr_read(CSR_EZ_EM_VOFFS_01);
}

/*!
 * @brief read event manager Voffs23
 *
 * @return register value of voffs23
 */
static inline uint32_t EZHV_ReadEmVoffs23(void)
{
    return (uint32_t)csr_read(CSR_EZ_EM_VOFFS_23);
}

/*!
 * @brief write event manager cfg0 register.
 *
 * @param regVal   register value to write
 */
static inline void EZHV_WriteEmCfg0(uint32_t regVal)
{
    csr_write(CSR_EZ_EM_CFG0, regVal);
}

/*!
 * @brief write event manager cfg1 register.
 *
 * @param regVal    register value to write
 */
static inline void EZHV_WriteEmCfg1(uint32_t regVal)
{
    csr_write(CSR_EZ_EM_CFG1, regVal);
}

/*!
 * @brief write event manager vector voffs01
 *
 * @param vectoredOff    vectored offset to write
 */
static inline void EZHV_WriteEmVoffs01(uint32_t vectoredOff)
{   /* re-write Voffs01, refer to _InitEventManager */
    csr_write(CSR_EZ_EM_VOFFS_01, vectoredOff);
}

/*!
 * @brief write event manager vector voffs23
 *
 * @param vectoredOff    vectored offset address to write
 */
static inline void EZHV_WriteEmVoffs23(uint32_t vectoredOff)
{
    /* re-write Voffs23, refer to _InitEventManager */
    csr_write(CSR_EZ_EM_VOFFS_23, vectoredOff);
}

/*!
 * @brief de-initialize event manager, clear all cfg registers
 */
static inline void EZHV_DeInitEmCfg(void)
{
    csr_write(CSR_EZ_EM_CFG0, 0);
    csr_write(CSR_EZ_EM_CFG1, 0);
}

/*!
 * @brief enable a normal event of EZ event manager.
 *
 * @param eventEn Event to enable, can be the OR'ed value of _ez_em_event.
 */
static inline void EZHV_EnableEmNormalEvent(uint32_t eventEn)
{
    /* set EV_ENABLE[15:0] of ez_em_cfg0 CSR register */
    csr_set(CSR_EZ_EM_CFG0, eventEn);
}

/*!
 * @brief disable a normal event of EZ event manager.
 *
 * @param eventDis Event to disable can be the OR'ed value of _ez_em_event.
 */
static inline void EZHV_DisableEmNormalEvent(uint32_t eventDis)
{
    /* clear EV_ENABLE[15:0] of ez_em_cfg0 CSR register */
    csr_clear(CSR_EZ_EM_CFG0, eventDis);
}

/*!
 * @brief enable a vectored event.
 *
 * Only 4 maximum may be selected
 *
 * @param eventEn Event to enable, can be the OR'ed value of _ez_em_event.
 */
static inline void EZHV_EnableEmVectoredEvent(uint32_t eventEn)
{
    csr_set(CSR_EZ_EM_CFG0, eventEn);
    csr_set(CSR_EZ_EM_CFG1, eventEn);
}

/*!
 * @brief disable a vectored event.
 *
 * @param eventDis Event to disable can be the OR'ed value of _ez_em_event.
 */
static inline void EZHV_DisableEmVectoredEvent(uint32_t eventDis)
{
    csr_clear(CSR_EZ_EM_CFG1, eventDis);
}

/*!
 * @brief Enable HeartBeat counter
 *
 * This is a simple pulse generating counter that generates a heart beat,
 * when HEART_COUNT+1 number of m_clk pulses has occurred,
 * the output of the heart beat can be used as an event by itself or
 * as a trigger to issue a transaction as defined in DBIU
 */
static inline void EZHV_EnableEmHeartBeat(void)
{
    csr_set(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_HEN_MASK);
}

/*!
 * @brief disable HeartBeat timer
 */
static inline void EZHV_DisableEmHeartBeat(void)
{
    csr_clear(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_HEN_MASK);
}

/*!
 * @brief Enable Wake Exit
 *
 * Used with WFI,
 * when WXN=1, the event will wake the core using the exit_wait signal,
 * but a CSR read of the event status is necessary to determine the cause
 * and to clear the event status. BTW, if EAC=1, no need for SW to read
 * and clear CSR register.
 */
static inline void EZHV_EnableEmWakeExitEn(void)
{
    csr_set(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_WXN_MASK);
}

/*!
 * @brief Disable Wake Exit
 *
 * Used with message receive instruction,
 * when WXN=0, the event will wake the core using the message receive interface
 * to resume execution, and present the event status on the message data bus
 * SW should execute a blocking, retire, wait for data message instruction for p=0
 * when enabled events occur, the contents of EZHV_EM_CFG0_REG are presented as the data message.
 */
static inline void EZHV_DisableEmWakeExitEn(void)
{
    csr_clear(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_WXN_MASK);
}

/*!
 * @brief enable vector interrupt enable
 *
 * Used with WFI, when VIE=1, any vectored event will use MEI to wake core.
 */
static inline void  EZHV_EnableEmVectoredInterrupt(void)
{
    csr_set(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_VIE_MASK);
}

/*!
 * @brief Disable vector interrupt enable
 *
 * Used with receive instruction, when VIE=0, the vectored event will wake the
 * core using the message receive interface to resume execution, and present the
 * vector address on the message data bus
 */
static inline void EZHV_DisableEmVectoredInterrupt(void)
{
    csr_clear(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_VIE_MASK);
}

/*!
 * @brief enable GPIO value updates wait until next heart beat
 */
static inline void EZHV_EnableEmGHC(void)
{
    csr_set(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_GHC_MASK);
}

/*!
* @brief disable GPIO value updates wait until next heart beat
*/
static inline void EZHV_DisableEmGHC(void)
{
    csr_clear(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_GHC_MASK);
}

/*!
 * @brief Enable Event Auto-Clear
 *
 * Sticky event will automatically clear when generating a wake-up.
 * This is intended to be used when WXN=1
 */
static inline void EZHV_EnableEmEventAutoClear(void)
{
    csr_set(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_EAC_MASK);
}

/*!
 * @brief Disable Event Auto-Clear
 *
 * When disabled, it's necessary for SW to read ez_em_cfg0 CSR register
 */
static inline void EZHV_DisableEmEventAutoClear(void)
{
    csr_clear(CSR_EZ_EM_CFG1, EZHV_EM_CFG1_EAC_MASK);
}

/*!
 * @brief Read and clear event status
 *
 * When WXN=1 & EAC=0, SW to call this API to get event status
 *
 * @return Return the event status, it is the OR'ed value of _ez_em_event.
*/
static inline uint32_t EZHV_GetEmEventStat(void)
{
    return (((uint32_t)csr_read(CSR_EZ_EM_CFG0)) & EZHV_EM_STAT_MASK) >> EZHV_EM_STAT_OFFSET;
}

#ifdef __cplusplus
}
#endif

/*! @} */

#endif
