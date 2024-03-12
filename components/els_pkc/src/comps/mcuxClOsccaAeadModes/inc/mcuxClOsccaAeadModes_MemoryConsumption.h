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

/** @file  mcuxClOsccaAeadModes_MemoryConsumption.h
 *  @brief Defines the memory consumption for the mcuxClOsccaAeadModes component */

#ifndef MCUXCLOSCCAAEADMODES_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCAAEADMODES_MEMORYCONSUMPTION_H_
/**
 * @defgroup mcuxClOsccaAeadModes_MemoryConsumption mcuxClOsccaAeadModes_MemoryConsumption
 * @brief Defines the memory consumption for the mcuxClOsccaAeadModes component
 * @ingroup mcuxClOsccaAeadModes
 * @{
 */

#ifdef MCUXCL_FEATURE_SM4_CCM

/** @def MCUXCLOSCCAAEADMODES_WA_MAX_SIZE
 *  @brief Define the max workarea size in bytes required for this component
 */
#define MCUXCLOSCCAAEADMODES_WA_MAX_SIZE (160u)

/** @def MCUXCLOSCCAAEADMODES_WA_MAX_SIZE_IN_WORDS
 *  @brief Define the max workarea size in words required for this component
 */
#define MCUXCLOSCCAAEADMODES_WA_MAX_SIZE_IN_WORDS (MCUXCLOSCCAAEADMODES_WA_MAX_SIZE / sizeof(uint32_t))

/** @def MCUXCLOSCCAAEADMODES_WA_CCM_ENC_SIZE
 *  @brief Define the workarea size in bytes required for CCM ENC mode
 */
#define MCUXCLOSCCAAEADMODES_WA_CCM_ENC_SIZE (160u)

/** @def MCUXCLOSCCAAEADMODES_WA_CCM_ENC_SIZE_IN_WORDS
 *  @brief Define the workarea size in words required for CCM ENC mode
 */
#define MCUXCLOSCCAAEADMODES_WA_CCM_ENC_SIZE_IN_WORDS (MCUXCLOSCCAAEADMODES_WA_CCM_ENC_SIZE / sizeof(uint32_t))

/** @def MCUXCLOSCCAAEADMODES_WA_CCM_DEC_SIZE
 *  @brief Define the workarea size in bytes required for CCM DEC mode
 */
#define MCUXCLOSCCAAEADMODES_WA_CCM_DEC_SIZE (160u)

/** @def MCUXCLOSCCAAEADMODES_WA_CCM_DEC_SIZE_IN_WORDS
 *  @brief Define the workarea size in words required for CCM DEC mode
 */
#define MCUXCLOSCCAAEADMODES_WA_CCM_DEC_SIZE_IN_WORDS (MCUXCLOSCCAAEADMODES_WA_CCM_DEC_SIZE / sizeof(uint32_t))


#define MCUXCLOSCCAAEADMODES_CTX_SIZE               (128u)
#define MCUXCLOSCCAAEADMODES_CTX_SIZE_IN_WORDS      (MCUXCLOSCCAAEADMODES_CTX_SIZE / sizeof(uint32_t))

#endif /* MCUXCL_FEATURE_SM4_CCM */
/**
 * @}
 */ /* mcuxClOsccaAeadModes_MemoryConsumption */
 
#endif /* MCUXCLOSCCAAEADMODES_MEMORYCONSUMPTION_H_ */
