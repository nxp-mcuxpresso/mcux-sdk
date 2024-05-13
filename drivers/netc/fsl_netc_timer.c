/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <math.h>
#include "fsl_netc_timer.h"

#define NETC_TIMER_GLOBAL_BASE_OFFSET          (0x10000U) /*!< The Timer global register base address offset. */
#define NETC_TIMER_EXT_TRIG_FIFO_THRESHOLD_MAX (15U)

/*!
 * @brief Set the MSIX entry table
 *
 * This function is to set entry table in specified MSIX Table memory.
 *
 * @param handle  The Timer handle.
 * @param config  The Timer configuration.
 * @return status_t
 */
static status_t NETC_TimerMSIXSetEntryTable(netc_timer_handle_t *handle, const netc_timer_config_t *config)
{
    uint32_t *msixTable  = (uint32_t *)(uintptr_t)handle->hw.msixTable;
    uint32_t *entryTable = (uint32_t *)(uintptr_t)config->msixEntry;
    uint8_t msixNum;

    msixNum = (uint8_t)((handle->hw.base->TMR_CAPR & ENETC_PF_TMR_TMR_CAPR_NUM_MSIX_MASK) >>
                        ENETC_PF_TMR_TMR_CAPR_NUM_MSIX_SHIFT) +
              1U;

    /* Entry > 0, enable MSIX. */
    if (config->entryNum != 0U)
    {
        if (config->entryNum > msixNum)
        {
            return kStatus_InvalidArgument;
        }

        /* Use 32-bit access to set MSIX table. */
        msixTable[0] = entryTable[0];
        msixTable[1] = entryTable[1];
        msixTable[2] = entryTable[2];
        msixTable[3] = entryTable[3];

        /* Enable MSIX. */
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK;
    }
    else
    {
        /* Disable MSIX. */
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
    }

    return kStatus_Success;
}

void NETC_TimerInitHandle(netc_timer_handle_t *handle)
{
    /* Initialize the handle. */
    handle->hw.func      = TMR_PCI_HDR_TYPE0;
    handle->hw.base      = TMR0_BASE;
    handle->hw.global    = (ENETC_GLOBAL_Type *)(TMR0_BASE_BASE + NETC_TIMER_GLOBAL_BASE_OFFSET);
    handle->hw.msixTable = (netc_msix_entry_t *)(FSL_FEATURE_NETC_MSIX_TABLE_BASE);
}

status_t NETC_TimerInit(netc_timer_handle_t *handle, const netc_timer_config_t *config)
{
    status_t result = kStatus_Success;
    uint32_t period = NETC_NANOSECOND_ONE_SECOND / config->refClkHz;

    /* Initialize the handle. */
    NETC_TimerInitHandle(handle);
    handle->entryNum     = config->entryNum;
    handle->timerFreq    = config->refClkHz;

    /* Reset this function */
    handle->hw.func->PCI_CFC_PCIE_DEV_CTL |= ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK;
    while ((handle->hw.func->PCI_CFC_PCIE_DEV_CTL & ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK) != 0U)
    {
    }

    /* Enable master bus and memory access for PCIe and MSI-X. */
    handle->hw.func->PCI_CFH_CMD |=
        ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;

    result = NETC_TimerMSIXSetEntryTable(handle, config);
    if (result != kStatus_Success)
    {
        return result;
    }

    handle->hw.base->TMR_CTRL =
        ENETC_PF_TMR_TMR_CTRL_TCLK_PERIOD(period) | ENETC_PF_TMR_TMR_CTRL_COPH(config->clkOutputPhase) |
        ENETC_PF_TMR_TMR_CTRL_CIPH(config->clkInputPhase) | ENETC_PF_TMR_TMR_CTRL_TE(config->enableTimer) |
        ENETC_PF_TMR_TMR_CTRL_COMP_MODE(config->atomicMode) | ENETC_PF_TMR_TMR_CTRL_CK_SEL(config->clockSelect);

    NETC_TimerAdjustFreq(handle, config->defaultPpb);

    handle->hw.base->TMR_CNT_L = 0;
    handle->hw.base->TMR_CNT_H = 0;

    return kStatus_Success;
}

void NETC_TimerDeinit(netc_timer_handle_t *handle)
{
    /* Disable the 1588 timer. */
    NETC_TimerEnable(handle, false);

    /* Disable master bus and memory access for PCIe and MSI-X. */
    TMR_PCI_HDR_TYPE0->PCI_CFH_CMD &=
        (uint16_t)(~(ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK));

    (void)memset(handle, 0, sizeof(netc_timer_handle_t));
}

void NETC_TimerEnable(netc_timer_handle_t *handle, bool enable)
{
    if (enable)
    {
        handle->hw.base->TMR_CTRL |= ENETC_PF_TMR_TMR_CTRL_TE_MASK;
    }
    else
    {
        handle->hw.base->TMR_CTRL &= ~ENETC_PF_TMR_TMR_CTRL_TE_MASK;
    }
}

void NETC_TimerConfigureAlarm(netc_timer_handle_t *handle,
                              netc_timer_alarm_index_t alarmId,
                              const netc_timer_alarm_t *alarm)
{
    uint32_t control;

    control = handle->hw.base->TMR_CTRL;
    control &=
        (alarmId == kNETC_TimerAlarm1) ? (~ENETC_PF_TMR_TMR_CTRL_ALM1P_MASK) : (~ENETC_PF_TMR_TMR_CTRL_ALM2P_MASK);
    control |= (alarmId == kNETC_TimerAlarm1) ? (ENETC_PF_TMR_TMR_CTRL_ALM1P(alarm->polarity)) :
                                                ENETC_PF_TMR_TMR_CTRL_ALM2P(alarm->polarity);
    handle->hw.base->TMR_CTRL = control;

    control = handle->hw.base->TMR_ALARM_CTRL;
    control &= (alarmId == kNETC_TimerAlarm1) ?
                   (~(ENETC_PF_TMR_TMR_ALARM_CTRL_PG1_MASK | ENETC_PF_TMR_TMR_ALARM_CTRL_ALARM1_PW_MASK)) :
                   (~(ENETC_PF_TMR_TMR_ALARM_CTRL_PG2_MASK | ENETC_PF_TMR_TMR_ALARM_CTRL_ALARM2_PW_MASK));
    control |= (alarmId == kNETC_TimerAlarm1) ? (ENETC_PF_TMR_TMR_ALARM_CTRL_PG1(alarm->pulseGenSync) |
                                                 ENETC_PF_TMR_TMR_ALARM_CTRL_ALARM1_PW(alarm->pulseWidth)) :
                                                (ENETC_PF_TMR_TMR_ALARM_CTRL_PG2(alarm->pulseGenSync) |
                                                 ENETC_PF_TMR_TMR_ALARM_CTRL_ALARM2_PW(alarm->pulseWidth));
    handle->hw.base->TMR_ALARM_CTRL = control;

    /* Alarm interrupt mask configuration. */
    control = handle->hw.base->TMR_TEMASK;
    control &= (alarmId == kNETC_TimerAlarm1) ? (~ENETC_PF_TMR_TMR_TEMASK_ALM1EN_MASK) :
                                                (~ENETC_PF_TMR_TMR_TEMASK_ALM2EN_MASK);
    control |= (alarmId == kNETC_TimerAlarm1) ? ENETC_PF_TMR_TMR_TEMASK_ALM1EN(alarm->enableInterrupt) :
                                                ENETC_PF_TMR_TMR_TEMASK_ALM2EN(alarm->enableInterrupt);
    handle->hw.base->TMR_TEMASK = control;
}

void NETC_TimerStartAlarm(netc_timer_handle_t *handle, netc_timer_alarm_index_t alarmId, uint64_t nanosecond)
{
    if (alarmId == kNETC_TimerAlarm1)
    {
        handle->hw.base->TMR_ALARM1_L = (uint32_t)nanosecond;
        handle->hw.base->TMR_ALARM1_H = (uint32_t)(nanosecond >> 32U);
    }
    else
    {
        handle->hw.base->TMR_ALARM2_L = (uint32_t)nanosecond;
        handle->hw.base->TMR_ALARM2_H = (uint32_t)(nanosecond >> 32U);
    }
}

void NETC_TimerStopAlarm(netc_timer_handle_t *handle, netc_timer_alarm_index_t alarmId)
{
    if (alarmId == kNETC_TimerAlarm1)
    {
        handle->hw.base->TMR_ALARM1_L = 0;
    }
    else
    {
        handle->hw.base->TMR_ALARM2_L = 0;
    }
}

void NETC_TimerConfigureFIPER(netc_timer_handle_t *handle, const netc_timer_fiper_config_t *config)
{
    assert((config->prescale % 2U) == 0U);

    handle->hw.base->TMR_CTRL &=
        ~(ENETC_PF_TMR_TMR_CTRL_FS_MASK | ENETC_PF_TMR_TMR_CTRL_PP1L_MASK | ENETC_PF_TMR_TMR_CTRL_PP2L_MASK);
    handle->hw.base->TMR_CTRL |= ENETC_PF_TMR_TMR_CTRL_FS(config->startCondition) |
                                 ENETC_PF_TMR_TMR_CTRL_PP1L(config->fiper1Loopback) |
                                 ENETC_PF_TMR_TMR_CTRL_PP2L(config->fiper1Loopback);
    handle->hw.base->TMR_PRSC = config->prescale;
}

void NETC_TimerStartFIPER(netc_timer_handle_t *handle,
                          netc_timer_fiper_index_t fiperId,
                          const netc_timer_fiper_t *fiper)
{
    uint32_t control;
    uint32_t clear;

    if (fiperId == kNETC_TimerFiper1)
    {
        /* Disbale the FIPER first */
        handle->hw.base->TMR_FIPER_CTRL |= ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER1_DIS_MASK;

        handle->hw.base->TMR_TEMASK &= ~ENETC_PF_TMR_TMR_TEMASK_PP1EN_MASK;
        handle->hw.base->TMR_TEMASK |= ENETC_PF_TMR_TMR_TEMASK_PP1EN(fiper->enableInterrupt);
        clear   = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER1_PW_MASK | ENETC_PF_TMR_TMR_FIPER_CTRL_PG1_MASK;
        control = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER1_PW(fiper->pulseWidth) |
                  ENETC_PF_TMR_TMR_FIPER_CTRL_PG1(fiper->pulseGenSync);
    }
    else if (fiperId == kNETC_TimerFiper2)
    {
        /* Disbale the FIPER first */
        handle->hw.base->TMR_FIPER_CTRL |= ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER2_DIS_MASK;

        handle->hw.base->TMR_TEMASK &= ~ENETC_PF_TMR_TMR_TEMASK_PP2EN_MASK;
        handle->hw.base->TMR_TEMASK |= ENETC_PF_TMR_TMR_TEMASK_PP2EN(fiper->enableInterrupt);
        clear   = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER2_PW_MASK | ENETC_PF_TMR_TMR_FIPER_CTRL_PG2_MASK;
        control = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER2_PW(fiper->pulseWidth) |
                  ENETC_PF_TMR_TMR_FIPER_CTRL_PG2(fiper->pulseGenSync);
    }
    else
    {
        /* Disbale the FIPER first */
        handle->hw.base->TMR_FIPER_CTRL |= ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER3_DIS_MASK;

        handle->hw.base->TMR_TEMASK &= ~ENETC_PF_TMR_TMR_TEMASK_PP3EN_MASK;
        handle->hw.base->TMR_TEMASK |= ENETC_PF_TMR_TMR_TEMASK_PP3EN(fiper->enableInterrupt);
        clear   = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER3_PW_MASK | ENETC_PF_TMR_TMR_FIPER_CTRL_PG3_MASK;
        control = ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER3_PW(fiper->pulseWidth) |
                  ENETC_PF_TMR_TMR_FIPER_CTRL_PG3(fiper->pulseGenSync);
    }

    handle->hw.base->TMR_FIPER[fiperId] = fiper->pulsePeriod;
    handle->hw.base->TMR_FIPER_CTRL &= ~clear;
    handle->hw.base->TMR_FIPER_CTRL |= control;

    handle->hw.base->TMR_FIPER_CTRL &=
        ~((uint32_t)ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER1_DIS_MASK << ((uint32_t)fiperId * 8U));
}

void NETC_TimerStopFIPER(netc_timer_handle_t *handle, netc_timer_fiper_index_t fiperId)
{
    handle->hw.base->TMR_FIPER_CTRL |=
        ((uint32_t)ENETC_PF_TMR_TMR_FIPER_CTRL_FIPER1_DIS_MASK << ((uint32_t)fiperId * 8U));
}

status_t NETC_TimerSetTsFifoThreshold(netc_timer_handle_t *handle, uint8_t threshold)
{
    status_t result = kStatus_Fail;

    if (threshold <= NETC_TIMER_EXT_TRIG_FIFO_THRESHOLD_MAX)
    {
        handle->hw.base->TMR_ECTRL = threshold;
        result                     = kStatus_Success;
    }

    return result;
}

void NETC_TimerConfigureExtPulseTrig(netc_timer_handle_t *handle,
                                     netc_timer_exttrig_index_t extTrigId,
                                     const netc_timer_ext_trig_t *extTrig)
{
    uint32_t control;
    uint32_t clear;

    clear   = (extTrigId == kNETC_TimerExtTrig1) ? ENETC_PF_TMR_TMR_CTRL_ETEP1_MASK : ENETC_PF_TMR_TMR_CTRL_ETEP2_MASK;
    control = (extTrigId == kNETC_TimerExtTrig1) ? ENETC_PF_TMR_TMR_CTRL_ETEP1(extTrig->polarity) :
                                                   ENETC_PF_TMR_TMR_CTRL_ETEP2(extTrig->polarity);
    handle->hw.base->TMR_CTRL &= ~clear;
    handle->hw.base->TMR_CTRL |= control;

    clear = (extTrigId == kNETC_TimerExtTrig1) ?
                (ENETC_PF_TMR_TMR_TEMASK_ETS1EN_MASK | ENETC_PF_TMR_TMR_TEMASK_ETS1_THREN_MASK |
                 ENETC_PF_TMR_TMR_TEMASK_ETS1_OVEN_MASK) :
                (ENETC_PF_TMR_TMR_TEMASK_ETS2EN_MASK | ENETC_PF_TMR_TMR_TEMASK_ETS2_THREN_MASK |
                 ENETC_PF_TMR_TMR_TEMASK_ETS2_OVEN_MASK);
    control = (extTrigId == kNETC_TimerExtTrig1) ?
                  (ENETC_PF_TMR_TMR_TEMASK_ETS1EN(extTrig->enableTsAvailInterrupt) |
                   ENETC_PF_TMR_TMR_TEMASK_ETS1_THREN(extTrig->enableFifoThresholdHitInterrupt) |
                   ENETC_PF_TMR_TMR_TEMASK_ETS1_OVEN(extTrig->enableFifoOverflowInterrupt)) :
                  (ENETC_PF_TMR_TMR_TEMASK_ETS2EN(extTrig->enableTsAvailInterrupt) |
                   ENETC_PF_TMR_TMR_TEMASK_ETS2_THREN(extTrig->enableFifoThresholdHitInterrupt) |
                   ENETC_PF_TMR_TMR_TEMASK_ETS2_OVEN(extTrig->enableFifoOverflowInterrupt));
    handle->hw.base->TMR_TEMASK &= ~clear;
    handle->hw.base->TMR_TEMASK |= control;
}

/*!
 * @brief Check the timestamp available status in FIFO
 *
 * @param base NETC timer peripheral base address.
 * @param tsFifo The FIFO number to read timestamp out.
 * @return True: FIFO is empty, False: FIFO is not empty
 */
static bool NETC_TimerCheckTsFifoEmpty(netc_timer_handle_t *handle, netc_timer_exttrig_index_t extTrigId)
{
    return ((handle->hw.base->TMR_STAT & (ENETC_PF_TMR_TMR_STAT_ETS1_VLD_MASK << (uint32_t)extTrigId)) == 0U);
}

status_t NETC_TimerReadExtPulseCaptureTime(netc_timer_handle_t *handle,
                                           netc_timer_exttrig_index_t extTrigId,
                                           uint64_t *nanosecond)
{
    status_t result = kStatus_Fail;
    uint32_t timeLow, timeHigh;

    if (!NETC_TimerCheckTsFifoEmpty(handle, extTrigId))
    {
        if (extTrigId == kNETC_TimerExtTrig1)
        {
            timeLow  = handle->hw.base->TMR_ETTS1_L;
            timeHigh = handle->hw.base->TMR_ETTS1_H;
        }
        else
        {
            timeLow  = handle->hw.base->TMR_ETTS2_L;
            timeHigh = handle->hw.base->TMR_ETTS2_H;
        }
        *nanosecond = ((uint64_t)timeHigh << 32U) + timeLow;
        result      = kStatus_Success;
    }
    return result;
}

static void __NETC_TimerGetCurrentTime(ENETC_PF_TMR_Type *base, uint64_t *nanosecond)
{
    uint32_t timeLow, timeHigh[2];

    timeHigh[0] = base->TMR_CUR_TIME_H;
    do {
        timeHigh[1] = timeHigh[0];
        timeLow     = base->TMR_CUR_TIME_L;
        timeHigh[0] = base->TMR_CUR_TIME_H;
    } while (timeHigh[0] != timeHigh[1]);

    *nanosecond = ((uint64_t)timeHigh[0] << 32U) + timeLow;
}

void NETC_TimerGetTime(ENETC_PF_TMR_Type *base, uint64_t *nanosecond)
{
    if ((base->TMR_CTRL & ENETC_PF_TMR_TMR_CTRL_TE_MASK) != 0U) {
        __NETC_TimerGetCurrentTime(base, nanosecond);
    } else {
        uint32_t timeLow, timeHigh[2];

        timeHigh[0] = base->TMR_DEF_CNT_H;
        do {
            timeHigh[1] = timeHigh[0];
            timeLow     = base->TMR_DEF_CNT_L;
            timeHigh[0] = base->TMR_DEF_CNT_H;
        } while (timeHigh[0] != timeHigh[1]);

        *nanosecond = ((uint64_t)timeHigh[0] << 32U) + timeLow;
    }
}

void NETC_TimerGetCurrentTime(netc_timer_handle_t *handle, uint64_t *nanosecond)
{
    __NETC_TimerGetCurrentTime(handle->hw.base, nanosecond);
}

void NETC_TimerGetFreeRunningTime(netc_timer_handle_t *handle, uint64_t *nanosecond)
{
    uint32_t timeLow, timeHigh[2];

    timeHigh[0] = handle->hw.base->TMR_FRT_H;
    do {
        timeHigh[1] = timeHigh[0];
        timeLow     = handle->hw.base->TMR_FRT_L;
        timeHigh[0] = handle->hw.base->TMR_FRT_H;
    } while (timeHigh[0] != timeHigh[1]);

    *nanosecond = ((uint64_t)timeHigh[0] << 32U) + timeLow;
}

void NETC_TimerAddOffset(netc_timer_handle_t *handle, int64_t nanosecond)
{
    uint64_t offset;

    if (nanosecond >= 0)
    {
        offset = (uint64_t)nanosecond;
    }
    else
    {
        offset = UINT64_MAX - (uint64_t)(-nanosecond);
    }

    /* Calculate a new offset value based on the current one. */
    offset += ((uint64_t)handle->hw.base->TMROFF_H << 32U) + handle->hw.base->TMROFF_L;
    /* Update the latest offset. */
    handle->hw.base->TMROFF_L = (uint32_t)offset;
    handle->hw.base->TMROFF_H = (uint32_t)(offset >> 32U);
}

void NETC_TimerAdjustFreq(netc_timer_handle_t *handle, int32_t ppb)
{
    int64_t offset = 1000000000LL + ppb;
    uint64_t addend;

    /* period (in ns) is given by: 10^9 / freq */
    /* ppb is applied to period: period' = period * (1 + ppb / 10^9) */
    /* addend is the fractional part of the period (in ns) scaled by 2^32, */
    /* which is equivalent to scaling period by 2^32, and then taking the lower 32bits */
    /* addend' = 10^9 / freq * (1 + ppp / 10^9) * 2^32 = (2^32 * (10^9 + ppb)) / freq */
    addend = (((uint64_t)1ULL << 32) * (uint64_t)offset) / handle->timerFreq;

    handle->hw.base->TMR_ADD = (uint32_t)addend;
}

void NETC_TimerGetFrtSrtTime(netc_timer_handle_t *handle, uint64_t *frt, uint64_t *srt)
{
    uint32_t tsLow, tsHigh;

    /* Read TMR_FRT_L captures all 64b of FRT_H/L and 64b of SRT_H/L for an atomic read of all 4 registers. */
    tsLow  = handle->hw.base->TMR_FRT_L;
    tsHigh = handle->hw.base->TMR_FRT_H;
    *frt   = ((uint64_t)tsHigh << 32U) + tsLow;

    tsLow  = handle->hw.base->TMR_SRT_L;
    tsHigh = handle->hw.base->TMR_SRT_H;
    *srt   = ((uint64_t)tsHigh << 32U) + tsLow;
}

status_t NETC_TimerMsixSetGlobalMask(netc_timer_handle_t *handle, bool mask)
{
    if (mask)
    {
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL |= ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
    }
    else
    {
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL &= ~(uint16_t)ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
    }

    return kStatus_Success;
}

status_t NETC_TimerMsixSetEntryMask(netc_timer_handle_t *handle, uint8_t entryIdx, bool mask)
{
    status_t result;

    if (entryIdx < handle->entryNum)
    {
        handle->hw.msixTable[entryIdx].control = (uint32_t)mask;
        result                                 = kStatus_Success;
    }
    else
    {
        result = kStatus_Fail;
    }

    return result;
}

status_t NETC_TimerMsixGetPendingStatus(netc_timer_handle_t *handle, uint8_t pbaIdx, uint64_t *status)
{
    status_t result = kStatus_Success;
    bool funcEnable;

    if (handle->entryNum == 0U)
    {
        return kStatus_Fail;
    }

    /* Check MSIX enable status. */
    funcEnable = ((handle->hw.func->PCI_CFC_MSIX_MSG_CTL & ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK) != 0U);

    if (funcEnable)
    {
        if (pbaIdx <= ((handle->entryNum - 1U) / 64U))
        {
            *status = *(uint64_t *)((uintptr_t)handle->hw.msixTable + NETC_MSIX_TABLE_PBA_OFFSET + 8U * pbaIdx);
            result  = kStatus_Success;
        }
        else
        {
            result = kStatus_InvalidArgument;
        }
    }
    else
    {
        *status = 0;
        result  = kStatus_Fail;
    }

    return result;
}
