/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * \file  mcuxCsslSecureCounter_Impl.h
 * \brief Selection of the implementation for the secure counter mechanism.
 */

#ifndef MCUX_CSSL_SECURE_COUNTER_IMPL_H_
#define MCUX_CSSL_SECURE_COUNTER_IMPL_H_

/* Include the configuration for the secure counter mechanism. */
#include <internal/mcuxCsslSecureCounter_Cfg.h>

/* Include the selected implementation of the secure counter mechanism. */
#if defined(MCUX_CSSL_SC_USE_HW_CDOG) && (1 == MCUX_CSSL_SC_USE_HW_CDOG)
#  include <internal/mcuxCsslSecureCounter_HW_CDOG.h>
#elif defined(MCUX_CSSL_SC_USE_HW_SCM) && (1 == MCUX_CSSL_SC_USE_HW_SCM)
#  include <internal/mcuxCsslSecureCounter_HW_SCM.h>
#elif defined(MCUX_CSSL_SC_USE_SW_LOCAL) && (1 == MCUX_CSSL_SC_USE_SW_LOCAL)
#  include <internal/mcuxCsslSecureCounter_SW_Local.h>
#elif defined(MCUX_CSSL_SC_USE_SW_CONTEXT) && (1 == MCUX_CSSL_SC_USE_SW_CONTEXT)
#  include <internal/mcuxCsslSecureCounter_SW_Context.h>
#elif defined(MCUX_CSSL_SC_USE_SW_GLOBAL) && (1 == MCUX_CSSL_SC_USE_SW_GLOBAL)
#  include <internal/mcuxCsslSecureCounter_SW_Global.h>
#elif defined(MCUX_CSSL_SC_USE_NONE) && (1 == MCUX_CSSL_SC_USE_NONE)
#  include <internal/mcuxCsslSecureCounter_None.h>
#else
#  error "No secure counter implementation found/configured."
#endif

#endif /* MCUX_CSSL_SECURE_COUNTER_IMPL_H_ */
