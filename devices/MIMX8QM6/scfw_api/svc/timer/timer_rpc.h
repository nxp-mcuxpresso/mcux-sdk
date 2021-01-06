/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * Header file for the TIMER RPC implementation.
 *
 * @addtogroup TIMER_SVC
 * @{
 */

#ifndef SC_TIMER_RPC_H
#define SC_TIMER_RPC_H

/* Includes */

/* Defines */

/*!
 * @name Defines for RPC TIMER function calls
 */
/*@{*/
#define TIMER_FUNC_UNKNOWN 0 /*!< Unknown function */
#define TIMER_FUNC_SET_WDOG_TIMEOUT 1U /*!< Index for sc_timer_set_wdog_timeout() RPC call */
#define TIMER_FUNC_SET_WDOG_PRE_TIMEOUT 12U /*!< Index for sc_timer_set_wdog_pre_timeout() RPC call */
#define TIMER_FUNC_SET_WDOG_WINDOW 19U /*!< Index for sc_timer_set_wdog_window() RPC call */
#define TIMER_FUNC_START_WDOG 2U /*!< Index for sc_timer_start_wdog() RPC call */
#define TIMER_FUNC_STOP_WDOG 3U /*!< Index for sc_timer_stop_wdog() RPC call */
#define TIMER_FUNC_PING_WDOG 4U /*!< Index for sc_timer_ping_wdog() RPC call */
#define TIMER_FUNC_GET_WDOG_STATUS 5U /*!< Index for sc_timer_get_wdog_status() RPC call */
#define TIMER_FUNC_PT_GET_WDOG_STATUS 13U /*!< Index for sc_timer_pt_get_wdog_status() RPC call */
#define TIMER_FUNC_SET_WDOG_ACTION 10U /*!< Index for sc_timer_set_wdog_action() RPC call */
#define TIMER_FUNC_SET_RTC_TIME 6U /*!< Index for sc_timer_set_rtc_time() RPC call */
#define TIMER_FUNC_GET_RTC_TIME 7U /*!< Index for sc_timer_get_rtc_time() RPC call */
#define TIMER_FUNC_GET_RTC_SEC1970 9U /*!< Index for sc_timer_get_rtc_sec1970() RPC call */
#define TIMER_FUNC_SET_RTC_ALARM 8U /*!< Index for sc_timer_set_rtc_alarm() RPC call */
#define TIMER_FUNC_SET_RTC_PERIODIC_ALARM 14U /*!< Index for sc_timer_set_rtc_periodic_alarm() RPC call */
#define TIMER_FUNC_CANCEL_RTC_ALARM 15U /*!< Index for sc_timer_cancel_rtc_alarm() RPC call */
#define TIMER_FUNC_SET_RTC_CALB 11U /*!< Index for sc_timer_set_rtc_calb() RPC call */
#define TIMER_FUNC_SET_SYSCTR_ALARM 16U /*!< Index for sc_timer_set_sysctr_alarm() RPC call */
#define TIMER_FUNC_SET_SYSCTR_PERIODIC_ALARM 17U /*!< Index for sc_timer_set_sysctr_periodic_alarm() RPC call */
#define TIMER_FUNC_CANCEL_SYSCTR_ALARM 18U /*!< Index for sc_timer_cancel_sysctr_alarm() RPC call */
/*@}*/

/* Types */

/* Functions */

/*!
 * This function dispatches an incoming TIMER RPC request.
 *
 * @param[in]     caller_pt   caller partition
 * @param[in]     mu          MU message came from
 * @param[in]     msg         pointer to RPC message
 */
void timer_dispatch(sc_rm_pt_t caller_pt, sc_rsrc_t mu, sc_rpc_msg_t *msg);

#endif /* SC_TIMER_RPC_H */

/**@}*/

