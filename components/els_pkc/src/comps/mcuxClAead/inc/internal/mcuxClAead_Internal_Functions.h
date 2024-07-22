/*--------------------------------------------------------------------------*/
/* Copyright 2024 NXP                                                       */
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

#ifndef MCUXCLAEAD_INTERNAL_FUNCTONS_H_
#define MCUXCLAEAD_INTERNAL_FUNCTONS_H_

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_computeContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClAead_computeContextCrc(mcuxClAead_Context_t * const pCtx, uint32_t contextSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_computeContextCrc);


    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClAead_computeContextCrc
                    );

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_verifyContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_verifyContextCrc(mcuxClAead_Context_t * const pCtx, uint32_t contextSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_verifyContextCrc);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_verifyContextCrc, MCUXCLAEAD_STATUS_OK
                    );
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEAD_INTERNAL_FUNCTONS_H_ */
