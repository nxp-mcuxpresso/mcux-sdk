/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClOsccaSafo_Constants.h
 *  @brief SAFO constant header.
 * This header exposes constants used by the @ref mcuxClOsccaSafo functions. */

#include <mcuxClOsccaSafo_Types.h>

/**
 * @defgroup mcuxClOsccaSafo_Constants mcuxClOsccaSafo_Constants
 * @brief Defines all constants used by the @ref mcuxClOsccaSafo functions.
 * @ingroup mcuxClOsccaSafo
 * @{
 */

#ifndef MCUXCLOSCCASAFO_CONSTANTS_H
#define MCUXCLOSCCASAFO_CONSTANTS_H

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @defgroup MCUXCLOSCCASAFO_STATUS_ MCUXCLOSCCASAFO_STATUS_
 * @brief Defines valid mcuxClOsccaSafo function return codes
 * @ingroup mcuxClOsccaSafo_Types_Macros
 * @{
 */
/* Status/error codes */
#define MCUXCLOSCCASAFO_STATUS_ERROR           ((mcuxClOsccaSafo_Status_t) 0x0FF95330u) ///< An error occured during an SAFO operation
#define MCUXCLOSCCASAFO_STATUS_OK              ((mcuxClOsccaSafo_Status_t) 0x0FF92E03u) ///< No error occured

/**
 * @}
 */

#endif  /* MCUXCLOSCCASAFO_CONSTANTS_H */

/**
 * @}
 */
