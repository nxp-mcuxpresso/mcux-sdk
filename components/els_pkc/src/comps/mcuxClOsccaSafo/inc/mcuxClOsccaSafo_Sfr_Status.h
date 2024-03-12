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

#ifndef MCUXCLOSCCASAFO_SFR_STATUS_H_
#define MCUXCLOSCCASAFO_SFR_STATUS_H_

#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClOsccaSafo_SfrAccess.h>

#define MCUXCLOSCCASAFO_SFR_STATUS_ERROR_OK      (0x5u)
#define MCUXCLOSCCASAFO_SFR_STATUS_ERROR_ERROR   (0x2u)

#define MCUXCLOSCCASAFO_SFR_STATUS_ERROR(status) ((MCUXCLOSCCASAFO_SFR_STATUS_ERROR_OK << MCUXCLOSCCASAFO_SFR_FIELD_SHIFT(STATUS,ERROR)) != ((status) & MCUXCLOSCCASAFO_SFR_FIELD_MASK(STATUS,ERROR)))
#define MCUXCLOSCCASAFO_SFR_STATUS_BUSY(status)  (0u != ((status) & MCUXCLOSCCASAFO_SFR_FIELD_MASK(STATUS,BUSY)))

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Read the SAFO STATUS register
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Sfr_readStatus)
static inline uint32_t mcuxClOsccaSafo_Sfr_readStatus(void)
{
  return MCUXCLOSCCASAFO_SFR_READ(STATUS);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASAFO_SFR_STATUS_H_ */
