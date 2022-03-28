/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

#include <mcuxCsslMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <impl/mcuxCsslMemory_Compare_asm.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxCsslMemory_Compare)
mcuxCsslMemory_CompareResult_t mcuxCsslMemory_Compare
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void const * lhs,
    void const * rhs,
    size_t cnt
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxCsslMemory_Compare,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslParamIntegrity_Validate)
    );

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxCsslParamIntegrity_Validate(chk, 3u, lhs, rhs, cnt));
    
    if( (result != MCUXCSSLPARAMINTEGRITY_CHECK_VALID)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Compare, MCUXCSSLMEMORY_COMPARE_FAULT);
    }
    
    if((NULL == lhs) || (NULL == rhs) || (0u == cnt)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Compare, MCUXCSSLMEMORY_COMPARE_INVALID_PARAMETER);
    }

    uint32_t retval;
    uint8_t const * cur_lhs = lhs;
    uint8_t const * cur_rhs = rhs;
    uint32_t const notValid = ~(MCUXCSSLPARAMINTEGRITY_CHECK_VALID);
    uint32_t const errCode = (uint32_t)MCUXCSSLMEMORY_COMPARE_NOT_EQUAL;

    /* Pre-calculate end pointers */
    uint8_t const * end_lhs = &cur_lhs[cnt];
    uint8_t const * end_rhs = &cur_rhs[cnt];

    MCUXCSSLMEMORY_COMPARE_ASM_COMPARISON(retval, cur_lhs, cur_rhs, cnt, notValid, result);

    MCUXCSSLMEMORY_COMPARE_ASM_CALC_RETVAL(retval, errCode);

    /* Check that the pointers reached the end */
    if((end_lhs != cur_lhs) || (end_rhs != cur_rhs)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Compare, MCUXCSSLMEMORY_COMPARE_FAULT);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Compare, (mcuxCsslMemory_CompareResult_t)retval);
}
