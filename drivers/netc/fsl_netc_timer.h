/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_TIMER_H_
#define FSL_NETC_TIMER_H_

#include "fsl_netc.h"
#include "fsl_netc_soc.h"
#include "netc_hw/fsl_netc_hw.h"

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region api_timer
#endif
//////////////////////////////////////
// Group for the Timer
//////////////////////////////////////
/*!
 * @defgroup netc_timer NETC Timer Driver
 * @details Group for Timer API and data structure.
 * API starts with NETC_Timer.
 * Parameter starts with netc_timer_handle_t.
 * This driver provides the API to enable IEEE1588 timer. After timer initialzation, the timestamp in frame transmission
 * will use it as reference. There're timer adjustment APIs to synchronize time with other system. The separate
 * ALARM/FIPER/ExtTrigger APIs can generate output pulse or capture input pulse timestamp for local system time
 * synchronization.
 * @ingroup netc_api
 */

/*!
 * @defgroup netc_timer_init Timer initialization module
 * @details IEEE1588 Timer Initialization.
 * @ingroup netc_timer
 */
/*!
 * @defgroup netc_timer_adjust Timer adjustment module
 * @details IEEE1588 Timer adjustment.
 * @ingroup netc_timer
 */
/*!
 * @defgroup netc_timer_local_sync Local time synchronization module
 * @details Generate output pulse or capture input pulse timestamp to check the local system time synchronization.
 *
 * @ingroup netc_timer
 */
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion api_timer
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_timer_init
#endif
/*! @addtogroup netc_timer_init
 * @{
 */

/*!
 * @brief Timer interrupt flags
 */
typedef enum _netc_timer_irq_flags
{
    kNETC_TimerFiper1IrqFlag = ENETC_PF_TMR_TMR_TEVENT_PP1EN_MASK,  /*!< Periodic pulse 1 interrupt. */
    kNETC_TimerFiper2IrqFlag = ENETC_PF_TMR_TMR_TEVENT_PP2EN_MASK,  /*!< Periodic pulse 2 interrupt. */
    kNETC_TimerFiper3IrqFlag = ENETC_PF_TMR_TMR_TEVENT_PP3EN_MASK,  /*!< Periodic pulse 3 interrupt. */
    kNETC_TimerAlarm1IrqFlag = ENETC_PF_TMR_TMR_TEVENT_ALM1EN_MASK, /*!< Alarm 1 interrupt. */
    kNETC_TimerAlarm2IrqFlag = ENETC_PF_TMR_TMR_TEVENT_ALM2EN_MASK, /*!< Alarm 2 interrupt. */
    kNETC_TimerExtTrig1ThresholdIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS1_THREN_MASK, /*!< External trigger 1 timestamp FIFO threshold hit interrupt.
                                                  */
    kNETC_TimerExtTrig2ThresholdIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS2_THREN_MASK, /*!< External trigger 2 timestamp FIFO threshold hit interrupt.
                                                  */
    kNETC_TimerExtTrig1TsAvailIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS1EN_MASK, /*!< External trigger 1 new timestamp available interrupt. */
    kNETC_TimerExtTrig2TsAvailIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS2EN_MASK, /*!< External trigger 2 new timestamp available interrupt. */
    kNETC_TimerExtTrig1OverflowIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS1_OVEN_MASK, /*!< External trigger 1 timestamp FIFO overflow interrupt. */
    kNETC_TimerExtTrig2OverflowIrqFlag =
        ENETC_PF_TMR_TMR_TEVENT_ETS2_OVEN_MASK, /*!< External trigger 2 timestamp FIFO overflow interrupt. */
} netc_timer_irq_flags_t;

typedef struct _netc_timer_handle netc_timer_handle_t;

/*!
 * @brief Timer handler structure
 */
struct _netc_timer_handle
{
    netc_timer_hw_t hw; /*!< Hardware register map resource. */
    uint32_t timerFreq; /*!< Timer clock frequency(Hz). */
    uint8_t entryNum;   /*!< MSIX entry number. */
};

/*!
 * @brief Enumeration for NETC timer reference clock
 */
typedef enum _netc_timer_ref_clk
{
    kNETC_TimerExtRefClk = 0,
    kNETC_TimerSystemClk,
} netc_timer_ref_clk_t;

/*!
 * @brief Structure to configure timer
 */
typedef struct _netc_timer_config
{
    bool clkOutputPhase; /*!< True: Inverted divided clock is output, False: Non-inverted divided clock is output. */
    bool clkInputPhase; /*!< True: Inverted frequency tuned timer input clock, False: Non-inverted frequency tuned timer
                           input clock. */
    bool enableTimer;   /*!< True: Enable 1588 timer, False: Disable 1588 timer, use default counter. */
    bool atomicMode;   /*!< True: Allow atomic updates to TMR_PERIOD and TMR_ADD, False: Disable it. */
    netc_timer_ref_clk_t clockSelect; /*!< Timer reference clock. */
    uint32_t refClkHz;                /*!< Timer reference clock frequency in Hz. */
    int32_t defaultPpb;               /*!< Default ppb. */
    netc_msix_entry_t *msixEntry;     /*!< MSIX table entry array. */
    uint8_t entryNum;                 /*!< MSIX entry number. */
} netc_timer_config_t;

/*! @} */ // end of netc_timer_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_timer_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_timer_local_sync
#endif
/*! @addtogroup netc_timer_local_sync
 * @{
 */

/*!
 * @brief Enumeration for NETC timer alarm index
 */
typedef enum _netc_timer_alarm_index
{
    kNETC_TimerAlarm1 = 0,
    kNETC_TimerAlarm2,
} netc_timer_alarm_index_t;

/*!
 * @brief Structure to configure timer alarm
 */
typedef struct _netc_timer_alarm_t
{
    bool enableInterrupt; /*!< Enable/Disable ALARM interrupt enable. */
    bool polarity;        /*!< True: Active low output, False: Active high output. */
    bool pulseGenSync;    /*!< True: ALARM output asserted synchronous to timer generated clock, False: ALARM output
                               asserted immediately. */
    uint8_t pulseWidth;   /*!< Pulse width in number of timer generated clocks the alarm will be active for. */
} netc_timer_alarm_t;

/*!
 * @brief Enumeration for NETC timer FIPER index
 */
typedef enum _netc_timer_fiper_index
{
    kNETC_TimerFiper1 = 0,
    kNETC_TimerFiper2,
    kNETC_TimerFiper3,
} netc_timer_fiper_index_t;

/*!
 * @brief Structure to configure timer FIPER
 */
typedef struct _netc_timer_fiper_config
{
    bool startCondition; /*!< True: FIPER is enabled through timer enable and alarm getting set, False: FIPER is enabled
                            through timer enable. */
    bool fiper1Loopback; /*!< True: FIPER1 pulse is looped back into Trigger1 input, False: Trigger1 input is based
                              upon normal external trigger input. */
    bool fiper2Loopback; /*!< True: FIPER2 pulse is looped back into Trigger2 input, False: Trigger2 input is based
                              upon normal external trigger input. */
    uint16_t prescale; /*!< Output FIPER pulse clock is generated by dividing the timer input clock by this number. Must
                          be an even value. */
} netc_timer_fiper_config_t;

/*!
 * @brief Structure to set and start timer FIPER
 */
typedef struct _netc_timer_fiper
{
    bool enableInterrupt; /*!< Enable/Disable FIPER interrupt interrupt. */
    bool pulseGenSync;    /*!< True: FIPER output asserted synchronous to timer generated clock, False: FIPER output
                             asserted immediately. */
    uint8_t pulseWidth;   /*!< FIPER pulse width. */
    uint32_t pulsePeriod; /*!< Interval of FIPER pulses. */
} netc_timer_fiper_t;

/*!
 * @brief Structure to configure external pulse trigger timestamp
 */
typedef struct _netc_timer_ext_pulse_trig
{
    bool polarity; /*!< Time stamp on the falling(true)/rising(false) edge of the external trigger. */
    bool enableFifoOverflowInterrupt;     /*!< Enable/Disable FIFO Overflow interrupt. */
    bool enableFifoThresholdHitInterrupt; /*!< Enable/Disable FIFO Threshold Hit interrupt. */
    bool enableTsAvailInterrupt;          /*!< Enable/Disable timestamp capture interrupt. */
} netc_timer_ext_trig_t;

/*! @} */ // end of netc_timer_local_sync
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_timer_local_sync
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_timer_init
#endif
/*! @addtogroup netc_timer_init
 * @{
 */

/*!
 * @brief Initialize the NETC PTP1588 timer
 *
 * @param handle NETC timer handle.
 * @param config The configuration of the timer.
 * @return status_t
 */
status_t NETC_TimerInit(netc_timer_handle_t *handle, const netc_timer_config_t *config);

/*!
 * @brief Deinitialize the NETC PTP1588 timer
 *
 * @param handle NETC timer handle.
 */
void NETC_TimerDeinit(netc_timer_handle_t *handle);

/*!
 * @brief Initialize a NETC PTP1588 timer handle
 *
 * @param handle NETC timer handle.
 */
void NETC_TimerInitHandle(netc_timer_handle_t *handle);

/*!
 * @brief Enable/Disable the NETC PTP1588 timer
 *
 * @param handle NETC timer handle.
 * @param enable Whether enable the PTP1588 timer.
 */
void NETC_TimerEnable(netc_timer_handle_t *handle, bool enable);

/*! @} */ // end of netc_timer_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_timer_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_timer_local_sync
#endif
/*! @addtogroup netc_timer_local_sync
 * @{
 */

/*!
 * @brief Configure the timer alarm feature
 *
 * @param handle NETC timer handle.
 * @param alarmId The alarm index.
 * @param alarm The timer alarm configuration structure.
 */
void NETC_TimerConfigureAlarm(netc_timer_handle_t *handle,
                              netc_timer_alarm_index_t alarmId,
                              const netc_timer_alarm_t *alarm);

/*!
 * @brief Start the alarm with specified time after alarm feature is configured
 * This function can generate a pulse on a GPIO and/or an interrupt at specified future time.
 * It also can trigger FIPER at specified time.
 *
 * @param handle NETC timer handle.
 * @param alarmId The alarm index.
 * @param nanosecond The time in nanosecond to generate alarm pulse.
 */
void NETC_TimerStartAlarm(netc_timer_handle_t *handle, netc_timer_alarm_index_t alarmId, uint64_t nanosecond);

/*!
 * @brief Stop the alarm before/after it's fired
 * This function can deactivate alarm.
 *
 * @param handle NETC timer handle.
 * @param alarmId The alarm index.
 */
void NETC_TimerStopAlarm(netc_timer_handle_t *handle, netc_timer_alarm_index_t alarmId);

/*!
 * @brief Configure the timer FIPER feature
 *
 * @param handle NETC timer handle.
 * @param config The timer FIPER configuration structure.
 */
void NETC_TimerConfigureFIPER(netc_timer_handle_t *handle, const netc_timer_fiper_config_t *config);

/*!
 * @brief Start the timer FIPER to generate pulse
 * This function can generate a periodic(Fixed Period-FIPER) pulse on a GPIO pin and/or an interrupt to the host.
 *
 * @param handle NETC timer handle.
 * @param fiperId The timer FIPER index.
 * @param fiper The timer FIPER configuration structure.
 */
void NETC_TimerStartFIPER(netc_timer_handle_t *handle,
                          netc_timer_fiper_index_t fiperId,
                          const netc_timer_fiper_t *fiper);

/*!
 * @brief Stop the timer FIPER to generate pulse
 *
 * @param handle NETC timer handle.
 * @param fiperId The timer FIPER index.
 */
void NETC_TimerStopFIPER(netc_timer_handle_t *handle, netc_timer_fiper_index_t fiperId);

/*!
 * @brief Configure the external pulse trigger timestamp capture
 *
 * @param handle NETC timer handle.
 * @param extTrigId The timer FIPER index.
 * @param extTrig The external pulse trigger configuration structure.
 */
void NETC_TimerConfigureExtPulseTrig(netc_timer_handle_t *handle,
                                     netc_timer_exttrig_index_t extTrigId,
                                     const netc_timer_ext_trig_t *extTrig);

/*!
 * @brief Set timestamp FIFO threshold of the external pulse trigger timestamp capture
 *
 * @param handle NETC timer handle.
 * @param threshold Timestamp FIFO threshold.
 * @return status_t
 */
status_t NETC_TimerSetTsFifoThreshold(netc_timer_handle_t *handle, uint8_t threshold);

/*!
 * @brief Read the timestamp captured by external pulse trigger in FIFO
 *
 * @param handle NETC timer handle.
 * @param extTrigId The timer FIPER index.
 * @param nanosecond Timestamp in nanosecond.
 * @return status_t
 */
status_t NETC_TimerReadExtPulseCaptureTime(netc_timer_handle_t *handle,
                                           netc_timer_exttrig_index_t extTrigId,
                                           uint64_t *nanosecond);

/*!
 * @brief Clear timer interrupt flags
 *
 * @param handle NETC timer handle.
 * @param flags Timer interrupt flags. This is a logical OR of enumeration :: netc_timer_irq_flags_t.
 */
static inline void NETC_TimerClearInterruptStatus(netc_timer_handle_t *handle, uint32_t flags)
{
    handle->hw.base->TMR_TEVENT = flags;
}

/*!
 * @brief Set the global MSIX mask status
 *
 * This function masks/unmasks global MSIX message.
 * Mask - All of the vectors are masked, regardless of their per-entry mask bit states.
 * Unmask - Each entry's mask status determines whether the vector is masked or not.
 *
 * @param handle    The timer handle
 * @param mask      The mask state. True: Mask, False: Unmask.
 * @return status_t
 */
status_t NETC_TimerMsixSetGlobalMask(netc_timer_handle_t *handle, bool mask);

/*!
 * @brief Set the MSIX entry mask status for specified entry
 *
 * This function masks/unmasks MSIX message for specified entry.
 *
 * @param handle    NETC timer handle.
 * @param entryIdx  The entry index in the table.
 * @param mask      The mask state. True: Mask, False: Unmask.
 * @return status_t
 */
status_t NETC_TimerMsixSetEntryMask(netc_timer_handle_t *handle, uint8_t entryIdx, bool mask);

/*!
 * @brief Get the MSIX pending status in MSIX PBA table
 *
 * This function is to get the entry pending status from MSIX PBA table. If interrupt occurs but masked by vector
 * control of entry, pending bit in PBA will be set.
 *
 * @param handle  NETC timer handle.
 * @param pbaIdx  The index of PBA array with 64-bit unit.
 * @param status  Pending status bit mask, bit n for entry n.
 * @return status_t
 */
status_t NETC_TimerMsixGetPendingStatus(netc_timer_handle_t *handle, uint8_t pbaIdx, uint64_t *status);

/*! @} */ // end of netc_timer_local_sync
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_timer_local_sync
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_timer_adjust
#endif
/*! @addtogroup netc_timer_adjust
 * @{
 */

/*!
 * @brief Get the timer's current or default time
 *
 * @param base NETC timer base address.
 * @param nanosecond Time in nanosecond.
 */
void NETC_TimerGetTime(ENETC_PF_TMR_Type *base, uint64_t *nanosecond);

/*!
 * @brief Get the timer's current time
 *
 * @param handle NETC timer handle.
 * @param nanosecond Time in nanosecond.
 */
void NETC_TimerGetCurrentTime(netc_timer_handle_t *handle, uint64_t *nanosecond);

/*!
 * @brief Get the timer's freerunning time
 *
 * @param handle NETC timer handle.
 * @param nanosecond Time in nanosecond.
 */
void NETC_TimerGetFreeRunningTime(netc_timer_handle_t *handle, uint64_t *nanosecond);

/*!
 * @brief Correct the current timer
 * @note Need stop all mechanims based on 1588 timers during call this API. To take time gate scheduling as example,
 *       if the port is enabled with TGS and it contains an operational list, user need to call
 *       SWT_TxPortTGSEnable()/SWT_TxPortTGSEnable() to disable the port time gate before call this API, and re-enable
 *       and configure the port TGS after the execution of this API.
 *
 * @param handle NETC timer handle.
 * @param nanosecond Time in nanosecond.
 */
void NETC_TimerAddOffset(netc_timer_handle_t *handle, int64_t nanosecond);

/*!
 * @brief Adjust the timer frequency
 *
 * @param handle NETC timer handle.
 * @param ppb Parts per billion.
 */
void NETC_TimerAdjustFreq(netc_timer_handle_t *handle, int32_t ppb);

/*!
 * @brief Get the free running and synchronized current time with an atomic read
 *
 * @param handle NETC timer handle.
 * @param frt The free-running time in nanosecond.
 * @param srt The synchronized current time in nanosecond.
 */
void NETC_TimerGetFrtSrtTime(netc_timer_handle_t *handle, uint64_t *frt, uint64_t *srt);

/*! @} */ // end of netc_timer_adjust
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_timer_adjust
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_TIMER_H_ */
