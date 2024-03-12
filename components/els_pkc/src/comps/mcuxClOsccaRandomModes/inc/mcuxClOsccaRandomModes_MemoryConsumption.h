/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClOsccaRandomModes_MemoryConsumption.h
 * @brief Defines the memory consumption for the mcuxClOsccaRandomModes component
 */

#ifndef MCUXCLOSCCARANDOMMODES_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCARANDOMMODES_MEMORYCONSUMPTION_H_

/**
 * @defgroup mcuxClOsccaRandomModes_MemoryConsumption mcuxClOsccaRandomModes_MemoryConsumption
 * @brief Defines the memory consumption for the @ref mcuxClOsccaRandomModes component
 * @ingroup mcuxClOsccaRandomModes
 * @{
 */

#ifdef MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG
#define MCUXCLOSCCARANDOMMODES_OSCCARNG_CONTEXT_SIZE (148u)
#define MCUXCLOSCCARANDOMMODES_OSCCARNG_CONTEXT_SIZE_IN_WORDS (MCUXCLOSCCARANDOMMODES_OSCCARNG_CONTEXT_SIZE/sizeof(uint32_t))

#define MCUXCLOSCCARANDOMMODES_OSCCARNG_SELFTEST_CPU_SIZE (148u)
#define MCUXCLOSCCARANDOMMODES_OSCCARNG_SELFTEST_CPU_SIZE_IN_WORDS (MCUXCLOSCCARANDOMMODES_OSCCARNG_SELFTEST_CPU_SIZE/sizeof(uint32_t))

#endif /* MCUXCL_FEATURE_RANDOMMODES_OSCCA_TRNG */

/**
 * @}
 */ /* mcuxClOsccaRandomModes_MemoryConsumption */

#endif /* MCUXCLOSCCARANDOMMODES_MEMORYCONSUMPTION_H_ */
