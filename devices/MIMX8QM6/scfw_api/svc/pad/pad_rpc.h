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
 * Header file for the PAD RPC implementation.
 *
 * @addtogroup PAD_SVC
 * @{
 */

#ifndef SC_PAD_RPC_H
#define SC_PAD_RPC_H

/* Includes */

/* Defines */

/*!
 * @name Defines for RPC PAD function calls
 */
/*@{*/
#define PAD_FUNC_UNKNOWN 0 /*!< Unknown function */
#define PAD_FUNC_SET_MUX 1U /*!< Index for sc_pad_set_mux() RPC call */
#define PAD_FUNC_GET_MUX 6U /*!< Index for sc_pad_get_mux() RPC call */
#define PAD_FUNC_SET_GP 2U /*!< Index for sc_pad_set_gp() RPC call */
#define PAD_FUNC_GET_GP 7U /*!< Index for sc_pad_get_gp() RPC call */
#define PAD_FUNC_SET_WAKEUP 4U /*!< Index for sc_pad_set_wakeup() RPC call */
#define PAD_FUNC_GET_WAKEUP 9U /*!< Index for sc_pad_get_wakeup() RPC call */
#define PAD_FUNC_SET_ALL 5U /*!< Index for sc_pad_set_all() RPC call */
#define PAD_FUNC_GET_ALL 10U /*!< Index for sc_pad_get_all() RPC call */
#define PAD_FUNC_SET 15U /*!< Index for sc_pad_set() RPC call */
#define PAD_FUNC_GET 16U /*!< Index for sc_pad_get() RPC call */
#define PAD_FUNC_CONFIG 17U /*!< Index for sc_pad_config() RPC call */
#define PAD_FUNC_SET_GP_28FDSOI 11U /*!< Index for sc_pad_set_gp_28fdsoi() RPC call */
#define PAD_FUNC_GET_GP_28FDSOI 12U /*!< Index for sc_pad_get_gp_28fdsoi() RPC call */
#define PAD_FUNC_SET_GP_28FDSOI_HSIC 3U /*!< Index for sc_pad_set_gp_28fdsoi_hsic() RPC call */
#define PAD_FUNC_GET_GP_28FDSOI_HSIC 8U /*!< Index for sc_pad_get_gp_28fdsoi_hsic() RPC call */
#define PAD_FUNC_SET_GP_28FDSOI_COMP 13U /*!< Index for sc_pad_set_gp_28fdsoi_comp() RPC call */
#define PAD_FUNC_GET_GP_28FDSOI_COMP 14U /*!< Index for sc_pad_get_gp_28fdsoi_comp() RPC call */
/*@}*/

/* Types */

/* Functions */

/*!
 * This function dispatches an incoming PAD RPC request.
 *
 * @param[in]     caller_pt   caller partition
 * @param[in]     mu          MU message came from
 * @param[in]     msg         pointer to RPC message
 */
void pad_dispatch(sc_rm_pt_t caller_pt, sc_rsrc_t mu, sc_rpc_msg_t *msg);

#endif /* SC_PAD_RPC_H */

/**@}*/

