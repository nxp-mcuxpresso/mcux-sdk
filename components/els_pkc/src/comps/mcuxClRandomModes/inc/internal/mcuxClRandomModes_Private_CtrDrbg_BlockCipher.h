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

#ifndef MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_BLOCKCIPHER_H_
#define MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_BLOCKCIPHER_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClSession.h>
#include <mcuxClRandom_Types.h>


#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_DRBG_AES_Internal_blockcipher)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_DRBG_AES_Internal_blockcipher(
    uint32_t const *pV,
    uint32_t const *pKey,
    uint8_t *pOut,
    uint32_t keyLength
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_BLOCKCIPHER_H_ */
