/*--------------------------------------------------------------------------*/
/* Copyright 2018-2023 NXP                                                  */
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
 * @file  mcuxClOsccaPkc_Types.h
 * @brief Type definitions of mcuxClOsccaPkc component
 */


#ifndef MCUXCLOSCCAPKC_TYPES_H
#define MCUXCLOSCCAPKC_TYPES_H


#include <stdint.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

/**********************************************************/
/* Helper macros                                          */
/**********************************************************/
/** @brief Macros for packing 2 8-bit parameters. */
#define MCUXCLOSCCAPKC_PKCPACKARGS2(hi8, lo8)  \
    ( ((uint16_t) (hi8) << 8u) | ((uint16_t) (lo8)) )


/**********************************************************/
/* PKC information                                        */
/**********************************************************/
#define MCUXCLOSCCAPKC_PKC_RAM_BASEADDR              ((uint32_t)PKC_RAM_ADDR)
#define MCUXCLOSCCAPKC_WORD_SIZE                     (PKC_WORD_SIZE)

/**
 * @}
 */ /* mcuxClOsccaPkc_Types */

#endif /* #MCUXCLOSCCAPKC_TYPES_H */
