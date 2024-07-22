/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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


#ifndef MCUXCLOSCCASM4_INTERNAL_FUNCTONS_H_
#define MCUXCLOSCCASM4_INTERNAL_FUNCTONS_H_

#include <internal/mcuxClOsccaSm4_Internal_Constants.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Core functions
 * */

/**
 * @brief This function encrypts/decrypts one block of data using algorithm OSCCA SM4
 *
 * @param pRoundKeys   Pointer to round keys, not used in SGI implementation
 * @param pIn          Pointer to the input (plaintext)
 * @param pOut         Pointer to the result (ciphertext)
 * @param direction    Encryption or decryption

 * @return status
 * @retval #MCUXCLOSCCASM4_STATUS_CRYPT_OK    pOut generated successfully;
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm4_Engine)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm4_Status_t) mcuxClOsccaSm4_Engine(
  uint32_t * const pRoKeys,
  const uint8_t * const pIn,
  uint8_t * const pOut,
  uint32_t direction
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm4_ScheduleSM4Key)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm4_Status_t) mcuxClOsccaSm4_ScheduleSM4Key(
    uint32_t *pRoundKeys, uint8_t const *pMKey, uint32_t direction);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm4_Tau)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaSm4_Tau(uint32_t in);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASM4_INTERNAL_FUNCTONS_H_ */
