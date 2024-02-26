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

/** @file  mcuxCl_clns.h
 *  @brief CLNS header for component-independent functionality */

#ifndef MCUXCL_CLNS_H_
#define MCUXCL_CLNS_H_

#include <mcuxClConfig.h> // Exported features flags header

/** @def MCUXCL_API
 *  @brief Marks a function as a public API function of the CLNS */

#define MCUXCL_API static inline

/**********************************************
 * CONSTANTS
 **********************************************/

#define MCUXCL_VERSION_MAX_SIZE ((size_t) 16U) ///< Maximum size of the CLNS version string, in bytes (including zero-terminator)

#define MCUXCL_VERSION "SDK_1.7.0" ///< String literal for the version string of CLNS release that this header is part of

/**********************************************
 * FUNCTIONS
 **********************************************/

/** Gets the CLNS version string that uniquely identifies this release of the CLNS. */
/**
 * @return Zero-terminated ASCII string that identifies this release of the CLNS.
 *         Maximum size in bytes (including zero-terminator) is #MCUXCL_VERSION_MAX_SIZE. */
MCUXCL_API char const* mcuxCl_GetVersion(
    void);

#include <impl/mcuxCl_clns_impl.h> // Implementation header
#endif /* MCUXCL_CLNS_H_ */
