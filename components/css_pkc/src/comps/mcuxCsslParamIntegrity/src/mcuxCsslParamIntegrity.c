/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslFlowProtection.h>
#include <stdarg.h>
#include <stddef.h>

static uint32_t rotate_right(uint32_t val, uint32_t shift_amt) {
    return ((val) >> (shift_amt) % 32u) | ((val) << (32u - (shift_amt)) % 32u);
}

static mcuxCsslParamIntegrity_Checksum_t mcuxCsslParamIntegrity_InternalProtect(size_t nargs, va_list args) {
    mcuxCsslParamIntegrity_Checksum_t result = MCUXCSSLPARAMINTEGRITY_BASE_CHECKSUM;
    for(size_t i = 0; i < nargs; i++) {
        result += rotate_right(va_arg(args, uint32_t), i);
    }
    return result;
}

mcuxCsslParamIntegrity_Checksum_t mcuxCsslParamIntegrity_Protect
(
    size_t nargs, 
    ...
)
{
    va_list args;
    /* MISRA Ex. 9 - Rule 17.1 – Intentional use for flow protection */
    va_start(args, nargs);
    mcuxCsslParamIntegrity_Checksum_t result = mcuxCsslParamIntegrity_InternalProtect(nargs, args);
    /* MISRA Ex. 9 - Rule 17.1 – Intentional use for flow protection */
    va_end(args);
    return result;
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxCsslParamIntegrity_Validate)
uint64_t mcuxCsslParamIntegrity_Validate
(
    mcuxCsslParamIntegrity_Checksum_t chk, 
    size_t nargs, 
    ...
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxCsslParamIntegrity_Validate);

    va_list args;
    /* MISRA Ex. 9 - Rule 17.1 – Intentional use for flow protection */
    va_start(args, nargs);
    mcuxCsslParamIntegrity_Checksum_t recalculatedChecksum = mcuxCsslParamIntegrity_InternalProtect(nargs, args);
    /* MISRA Ex. 9 - Rule 17.1 – Intentional use for flow protection */
    va_end(args);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslParamIntegrity_Validate, 
        (recalculatedChecksum == chk) ? MCUXCSSLPARAMINTEGRITY_CHECK_VALID : MCUXCSSLPARAMINTEGRITY_CHECK_INVALID
    );
}
