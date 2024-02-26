/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022 NXP                                                 */
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

/** @file  impl/mcuxCl_clns_impl.h
 *  @brief Implementation header for component-independent CLNS functionality. */

#ifndef MCUXCL_CLNS_IMPL_H_
#define MCUXCL_CLNS_IMPL_H_

#include <mcuxClConfig.h> // Exported features flags header

MCUXCL_API char const* mcuxCl_GetVersion(
    void)
{
#ifndef MCUXCL_VERSION
#error "Missing definition of MCUXCL_VERSION"
#endif /* ndef MCUXCL_VERSION */
    return MCUXCL_VERSION;
}

#endif /* MCUXCL_CLNS_IMPL_H_ */
