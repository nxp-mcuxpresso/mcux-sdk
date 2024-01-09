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

#ifndef MCUXCLCIPHER_INTERNAL_FUNCTONS_H_
#define MCUXCLCIPHER_INTERNAL_FUNCTONS_H_

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_computeContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClCipher_computeContextCrc(mcuxClCipher_Context_t * const pCtx, uint32_t contextSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_computeContextCrc);


    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClCipher_computeContextCrc
                    );

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_verifyContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_verifyContextCrc(mcuxClCipher_Context_t * const pCtx, uint32_t contextSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_verifyContextCrc);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipher_verifyContextCrc, MCUXCLCIPHER_STATUS_OK
                    );
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHER_INTERNAL_FUNCTONS_H_ */
