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

#ifndef MCUXCLOSCCASAFO_SFR_REGBANK_H_
#define MCUXCLOSCCASAFO_SFR_REGBANK_H_

#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClOsccaSafo_SfrAccess.h>

#ifdef __cplusplus
extern "C" {
#endif


/** Get the address of an SAFO DATA (DATIN or DATOUT) SFR */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_getAddrOfDataReg)
static inline uint32_t * mcuxClOsccaSafo_Sfr_getAddrOfDataReg(uint32_t dataRegIndex)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ()
  return &(((uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(DATIN0A)))[dataRegIndex]);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ()
}

/** Get the address of an SAFO KEY SFR */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_getAddrOfKeyReg)
static inline uint32_t * mcuxClOsccaSafo_Sfr_getAddrOfKeyReg(uint32_t keyRegIndex)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ()
  return &(((uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(KEY0A)))[keyRegIndex]);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ()
}

/** Index with respect to SAFO->KEY0A. Must be the index of a valid SAFO KEY register. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_writeKeyWord)
static inline void mcuxClOsccaSafo_Sfr_writeKeyWord(uint32_t index, uint32_t value)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_WRITE()
  volatile uint32_t *const safoKeyWord = (uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(KEY0A));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_OUT_OF_BOUNDS_ACCESS("Apply an index to the base address of a HW peripheral to access the correct SFR-word. The caller is responsible for ensuring that the index is valid.")
  safoKeyWord[index] = value;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OUT_OF_BOUNDS_ACCESS()
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_WRITE()
}

/** Index with respect to SAFO->KEY0A. Must be the index of a valid SAFO KEY register. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_readKeyWord)
static inline uint32_t mcuxClOsccaSafo_Sfr_readKeyWord(uint32_t index)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ()
  volatile uint32_t *const safoKeyWord = (uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(KEY0A));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_OUT_OF_BOUNDS_ACCESS("Apply an index to the base address of a HW peripheral to access the correct SFR-word. The caller is responsible for ensuring that the index is valid.")
  return safoKeyWord[index];
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OUT_OF_BOUNDS_ACCESS()
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ()
}

/** Index with respect to SAFO->DATIN0A. Must be the index of a valid SAFO DATIN register. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_writeDatinWord)
static inline void mcuxClOsccaSafo_Sfr_writeDatinWord(uint32_t index, uint32_t value)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_WRITE()
  volatile uint32_t *const safoDatinWord = (uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(DATIN0A));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_OUT_OF_BOUNDS_ACCESS("Apply an index to the base address of a HW peripheral to access the correct SFR-word. The caller is responsible for ensuring that the index is valid.")
  safoDatinWord[index] = value;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OUT_OF_BOUNDS_ACCESS()
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_WRITE()
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_writeFifoWord)
static inline void mcuxClOsccaSafo_Sfr_writeFifoWord(uint32_t value)
{
  MCUXCLOSCCASAFO_SFR_WRITE(SM3_FIFO, value);
}
#endif

/** Index with respect to SAFO->DATIN0A. Must be the index of a valid SAFO DATIN register. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_readDatinWord)
static inline uint32_t mcuxClOsccaSafo_Sfr_readDatinWord(uint32_t index)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ()
  volatile uint32_t *const safoDatinWord = (uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(DATIN0A));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_OUT_OF_BOUNDS_ACCESS("Apply an index to the base address of a HW peripheral to access the correct SFR-word. The caller is responsible for ensuring that the index is valid.")
  return safoDatinWord[index];
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OUT_OF_BOUNDS_ACCESS()
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ()
}

/** Index with respect to SAFO->DATOUTA. Must be the index of a valid SAFO DATOUT register. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_readDatoutWord)
static inline uint32_t mcuxClOsccaSafo_Sfr_readDatoutWord(uint32_t index)
{
  MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ()
  volatile uint32_t *const safoDatoutWord = (uint32_t *) &(MCUXCLOSCCASAFO_SFR_READ(DATOUTA));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_OUT_OF_BOUNDS_ACCESS("Apply an index to the base address of a HW peripheral to access the correct SFR-word. The caller is responsible for ensuring that the index is valid.")
  return safoDatoutWord[index];
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OUT_OF_BOUNDS_ACCESS()
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ()
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASAFO_SFR_REGBANK_H_ */
