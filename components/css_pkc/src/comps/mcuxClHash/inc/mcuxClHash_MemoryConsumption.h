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

/** @file  mcuxClHash_MemoryConsumption.h
 *  @brief Defines the memory consumption for the mcuxClHash component */

/**
 * @defgroup mcuxClHash_Macros mcuxClHash_Macros
 * @brief Defines all macros of @ref mcuxClHash
 * @ingroup mcuxClHash
 * @{
 */

#ifndef MCUXCLHASH_MEMORYCONSUMPTION_H_
#define MCUXCLHASH_MEMORYCONSUMPTION_H_

/**
 * @defgroup MCUXCLHASH_WA MCUXCLHASH_WA
 * @brief Definitions of workarea sizes for the mcuxClHash functions.
 * @ingroup mcuxClHash_Macros
 * @{
 */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClHash functions.               */
/****************************************************************************/

/** @def MCUXCLHASH_WA_SIZE_MAX
 *  @brief Define the max workarea size required for this component
 */
#define MCUXCLHASH_WA_SIZE_MAX (128u+64u)


/** @} */

/** @} */

#endif /* MCUXCLHASH_MEMORYCONSUMPTION_H_ */
