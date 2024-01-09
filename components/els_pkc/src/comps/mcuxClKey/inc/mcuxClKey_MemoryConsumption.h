/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClKey_MemoryConsumption.h
 *  @brief Defines the memory consumption for the mcuxClKey component
 *         All work area sizes in bytes are a multiple of CPU wordsize.
 */

#ifndef MCUXCLKEY_MEMORYCONSUMPTION_H_
#define MCUXCLKEY_MEMORYCONSUMPTION_H_

/**
 * @defgroup mcuxClKey_MemoryConsumption mcuxClKey_MemoryConsumption
 * @brief Defines the memory consumption for the mcuxClKey component
 * @ingroup mcuxClKey
 * @{
 */

#define MCUXCLKEY_DESCRIPTOR_SIZE          (56u)
#define MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS (MCUXCLKEY_DESCRIPTOR_SIZE / sizeof(uint32_t))

#define MCUXCLKEY_TYPEDESCRIPTOR_SIZE          (12u)
#define MCUXCLKEY_TYPEDESCRIPTOR_SIZE_IN_WORDS (MCUXCLKEY_TYPEDESCRIPTOR_SIZE / sizeof(uint32_t))

#define MCUXCLKEY_CUSTOMTYPEDESCRIPTOR_SIZE          (12u)
#define MCUXCLKEY_CUSTOMTYPEDESCRIPTOR_SIZE_IN_WORDS (MCUXCLKEY_CUSTOMTYPEDESCRIPTOR_SIZE / sizeof(uint32_t))


/**
 * @}
 */ /* mcuxClKey_MemoryConsumption */

#endif /* MCUXCLKEY_MEMORYCONSUMPTION_H_ */
