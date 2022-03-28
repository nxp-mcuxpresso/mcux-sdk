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
 * \file  mcuxCsslSecureCounter_Cfg.h
 * \brief Configuration of the implementation for the secure counter mechanism.
 */

#ifndef MCUX_CSSL_SECURE_COUNTER_CFG_H_
#define MCUX_CSSL_SECURE_COUNTER_CFG_H_

/**
 * \addtogroup mcuxCsslCFG MCUX CSSL -- Configurations
 *
 * \defgroup mcuxCsslSecureCounter_CFG Secure Counter Configuration
 * \brief Configuration options for the secure counter mechanism.
 * \ingroup mcuxCsslCFG
 */

/**
 * \def MCUX_CSSL_SC_USE_HW_CDOG
 * \brief If set to 1, use the secure counter mechanism implementation based on
 *        the code watchdog (CDOG) HW IP block.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_HW_CDOG      0

/**
 * \def MCUX_CSSL_SC_USE_HW_SCM
 * \brief If set to 1, use the secure counter mechanism implementation based on
 *        the subsystem control module (SCM) HW IP block.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_HW_SCM      0

/**
 * \def MCUX_CSSL_SC_USE_SW_LOCAL
 * \brief If set to 1, use the secure counter mechanism implementation based on
 *        a SW counter stored in a local variable.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_SW_LOCAL    1

/**
 * \def MCUX_CSSL_SC_USE_SW_CONTEXT
 * \brief If set to 1, use the secure counter mechanism implementation based on
 *        a SW counter stored in a context structure.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_SW_CONTEXT    0

/**
 * \def MCUX_CSSL_SC_USE_SW_GLOBAL
 * \brief If set to 1, use the secure counter mechanism implementation based on
 *        a SW counter stored in a global variable.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_SW_GLOBAL    0

/**
 * \def MCUX_CSSL_SC_USE_NONE
 * \brief If set to 1, do not use the secure counter mechanism.
 * \ingroup mcuxCsslSecureCounter_CFG
 */
    #define MCUX_CSSL_SC_USE_NONE    0

/* Basic configuration sanity check */

#endif /* MCUX_CSSL_SECURE_COUNTER_CFG_H_ */
