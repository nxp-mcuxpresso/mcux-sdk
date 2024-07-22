/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

#include "common.h"

#include <mcuxClAes_KeyTypes.h>
#include <mcuxClHmac_KeyTypes.h>
#include <mcuxClEls.h>
#include <mcuxClEcc.h>
#include <internal/mcuxClPkc_Macros.h>
#include <mcuxClKey.h>
#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClPsaDriver_Oracle.h>
#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClEcc_Mont_Internal.h>
#include <internal/mcuxClPsaDriver_ExternalMacroWrappers.h>

#include <mcuxClPkc_Operations.h>
#include <mcuxClMath_Functions.h>
#include <mcuxClSession_Internal.h>

#define ASSERT_CALLED_OR_EXIT(call, func, retval)                            \
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, call);                   \
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(func) != token) || (retval != result)) \
    {                                                                        \
        ret = PSA_ERROR_GENERIC_ERROR;                                       \
        goto exit;                                                           \
    }                                                                        \
    MCUX_CSSL_FP_FUNCTION_CALL_END()

#define ASSERT_CALLED_VOID_OR_EXIT(call, func)          \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, call); \
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(func) != token))  \
    {                                                   \
        ret = PSA_ERROR_GENERIC_ERROR;                  \
        goto exit;                                      \
    }                                                   \
    MCUX_CSSL_FP_FUNCTION_CALL_END()

// clang-format off
#define MCUXCLPSADRIVER_DHM_RFC7919_FFDHE2048_P_BIN {   \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        0xAD, 0xF8, 0x54, 0x58, 0xA2, 0xBB, 0x4A, 0x9A, \
        0xAF, 0xDC, 0x56, 0x20, 0x27, 0x3D, 0x3C, 0xF1, \
        0xD8, 0xB9, 0xC5, 0x83, 0xCE, 0x2D, 0x36, 0x95, \
        0xA9, 0xE1, 0x36, 0x41, 0x14, 0x64, 0x33, 0xFB, \
        0xCC, 0x93, 0x9D, 0xCE, 0x24, 0x9B, 0x3E, 0xF9, \
        0x7D, 0x2F, 0xE3, 0x63, 0x63, 0x0C, 0x75, 0xD8, \
        0xF6, 0x81, 0xB2, 0x02, 0xAE, 0xC4, 0x61, 0x7A, \
        0xD3, 0xDF, 0x1E, 0xD5, 0xD5, 0xFD, 0x65, 0x61, \
        0x24, 0x33, 0xF5, 0x1F, 0x5F, 0x06, 0x6E, 0xD0, \
        0x85, 0x63, 0x65, 0x55, 0x3D, 0xED, 0x1A, 0xF3, \
        0xB5, 0x57, 0x13, 0x5E, 0x7F, 0x57, 0xC9, 0x35, \
        0x98, 0x4F, 0x0C, 0x70, 0xE0, 0xE6, 0x8B, 0x77, \
        0xE2, 0xA6, 0x89, 0xDA, 0xF3, 0xEF, 0xE8, 0x72, \
        0x1D, 0xF1, 0x58, 0xA1, 0x36, 0xAD, 0xE7, 0x35, \
        0x30, 0xAC, 0xCA, 0x4F, 0x48, 0x3A, 0x79, 0x7A, \
        0xBC, 0x0A, 0xB1, 0x82, 0xB3, 0x24, 0xFB, 0x61, \
        0xD1, 0x08, 0xA9, 0x4B, 0xB2, 0xC8, 0xE3, 0xFB, \
        0xB9, 0x6A, 0xDA, 0xB7, 0x60, 0xD7, 0xF4, 0x68, \
        0x1D, 0x4F, 0x42, 0xA3, 0xDE, 0x39, 0x4D, 0xF4, \
        0xAE, 0x56, 0xED, 0xE7, 0x63, 0x72, 0xBB, 0x19, \
        0x0B, 0x07, 0xA7, 0xC8, 0xEE, 0x0A, 0x6D, 0x70, \
        0x9E, 0x02, 0xFC, 0xE1, 0xCD, 0xF7, 0xE2, 0xEC, \
        0xC0, 0x34, 0x04, 0xCD, 0x28, 0x34, 0x2F, 0x61, \
        0x91, 0x72, 0xFE, 0x9C, 0xE9, 0x85, 0x83, 0xFF, \
        0x8E, 0x4F, 0x12, 0x32, 0xEE, 0xF2, 0x81, 0x83, \
        0xC3, 0xFE, 0x3B, 0x1B, 0x4C, 0x6F, 0xAD, 0x73, \
        0x3B, 0xB5, 0xFC, 0xBC, 0x2E, 0xC2, 0x20, 0x05, \
        0xC5, 0x8E, 0xF1, 0x83, 0x7D, 0x16, 0x83, 0xB2, \
        0xC6, 0xF3, 0x4A, 0x26, 0xC1, 0xB2, 0xEF, 0xFA, \
        0x88, 0x6B, 0x42, 0x38, 0x61, 0x28, 0x5C, 0x97, \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, }

#define MCUXCLPSADRIVER_DHM_RFC7919_FFDHE3072_P_BIN {   \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        0xAD, 0xF8, 0x54, 0x58, 0xA2, 0xBB, 0x4A, 0x9A, \
        0xAF, 0xDC, 0x56, 0x20, 0x27, 0x3D, 0x3C, 0xF1, \
        0xD8, 0xB9, 0xC5, 0x83, 0xCE, 0x2D, 0x36, 0x95, \
        0xA9, 0xE1, 0x36, 0x41, 0x14, 0x64, 0x33, 0xFB, \
        0xCC, 0x93, 0x9D, 0xCE, 0x24, 0x9B, 0x3E, 0xF9, \
        0x7D, 0x2F, 0xE3, 0x63, 0x63, 0x0C, 0x75, 0xD8, \
        0xF6, 0x81, 0xB2, 0x02, 0xAE, 0xC4, 0x61, 0x7A, \
        0xD3, 0xDF, 0x1E, 0xD5, 0xD5, 0xFD, 0x65, 0x61, \
        0x24, 0x33, 0xF5, 0x1F, 0x5F, 0x06, 0x6E, 0xD0, \
        0x85, 0x63, 0x65, 0x55, 0x3D, 0xED, 0x1A, 0xF3, \
        0xB5, 0x57, 0x13, 0x5E, 0x7F, 0x57, 0xC9, 0x35, \
        0x98, 0x4F, 0x0C, 0x70, 0xE0, 0xE6, 0x8B, 0x77, \
        0xE2, 0xA6, 0x89, 0xDA, 0xF3, 0xEF, 0xE8, 0x72, \
        0x1D, 0xF1, 0x58, 0xA1, 0x36, 0xAD, 0xE7, 0x35, \
        0x30, 0xAC, 0xCA, 0x4F, 0x48, 0x3A, 0x79, 0x7A, \
        0xBC, 0x0A, 0xB1, 0x82, 0xB3, 0x24, 0xFB, 0x61, \
        0xD1, 0x08, 0xA9, 0x4B, 0xB2, 0xC8, 0xE3, 0xFB, \
        0xB9, 0x6A, 0xDA, 0xB7, 0x60, 0xD7, 0xF4, 0x68, \
        0x1D, 0x4F, 0x42, 0xA3, 0xDE, 0x39, 0x4D, 0xF4, \
        0xAE, 0x56, 0xED, 0xE7, 0x63, 0x72, 0xBB, 0x19, \
        0x0B, 0x07, 0xA7, 0xC8, 0xEE, 0x0A, 0x6D, 0x70, \
        0x9E, 0x02, 0xFC, 0xE1, 0xCD, 0xF7, 0xE2, 0xEC, \
        0xC0, 0x34, 0x04, 0xCD, 0x28, 0x34, 0x2F, 0x61, \
        0x91, 0x72, 0xFE, 0x9C, 0xE9, 0x85, 0x83, 0xFF, \
        0x8E, 0x4F, 0x12, 0x32, 0xEE, 0xF2, 0x81, 0x83, \
        0xC3, 0xFE, 0x3B, 0x1B, 0x4C, 0x6F, 0xAD, 0x73, \
        0x3B, 0xB5, 0xFC, 0xBC, 0x2E, 0xC2, 0x20, 0x05, \
        0xC5, 0x8E, 0xF1, 0x83, 0x7D, 0x16, 0x83, 0xB2, \
        0xC6, 0xF3, 0x4A, 0x26, 0xC1, 0xB2, 0xEF, 0xFA, \
        0x88, 0x6B, 0x42, 0x38, 0x61, 0x1F, 0xCF, 0xDC, \
        0xDE, 0x35, 0x5B, 0x3B, 0x65, 0x19, 0x03, 0x5B, \
        0xBC, 0x34, 0xF4, 0xDE, 0xF9, 0x9C, 0x02, 0x38, \
        0x61, 0xB4, 0x6F, 0xC9, 0xD6, 0xE6, 0xC9, 0x07, \
        0x7A, 0xD9, 0x1D, 0x26, 0x91, 0xF7, 0xF7, 0xEE, \
        0x59, 0x8C, 0xB0, 0xFA, 0xC1, 0x86, 0xD9, 0x1C, \
        0xAE, 0xFE, 0x13, 0x09, 0x85, 0x13, 0x92, 0x70, \
        0xB4, 0x13, 0x0C, 0x93, 0xBC, 0x43, 0x79, 0x44, \
        0xF4, 0xFD, 0x44, 0x52, 0xE2, 0xD7, 0x4D, 0xD3, \
        0x64, 0xF2, 0xE2, 0x1E, 0x71, 0xF5, 0x4B, 0xFF, \
        0x5C, 0xAE, 0x82, 0xAB, 0x9C, 0x9D, 0xF6, 0x9E, \
        0xE8, 0x6D, 0x2B, 0xC5, 0x22, 0x36, 0x3A, 0x0D, \
        0xAB, 0xC5, 0x21, 0x97, 0x9B, 0x0D, 0xEA, 0xDA, \
        0x1D, 0xBF, 0x9A, 0x42, 0xD5, 0xC4, 0x48, 0x4E, \
        0x0A, 0xBC, 0xD0, 0x6B, 0xFA, 0x53, 0xDD, 0xEF, \
        0x3C, 0x1B, 0x20, 0xEE, 0x3F, 0xD5, 0x9D, 0x7C, \
        0x25, 0xE4, 0x1D, 0x2B, 0x66, 0xC6, 0x2E, 0x37, \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }

#define MCUXCLPSADRIVER_DHM_RFC7919_FFDHE4096_P_BIN {   \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
        0xAD, 0xF8, 0x54, 0x58, 0xA2, 0xBB, 0x4A, 0x9A, \
        0xAF, 0xDC, 0x56, 0x20, 0x27, 0x3D, 0x3C, 0xF1, \
        0xD8, 0xB9, 0xC5, 0x83, 0xCE, 0x2D, 0x36, 0x95, \
        0xA9, 0xE1, 0x36, 0x41, 0x14, 0x64, 0x33, 0xFB, \
        0xCC, 0x93, 0x9D, 0xCE, 0x24, 0x9B, 0x3E, 0xF9, \
        0x7D, 0x2F, 0xE3, 0x63, 0x63, 0x0C, 0x75, 0xD8, \
        0xF6, 0x81, 0xB2, 0x02, 0xAE, 0xC4, 0x61, 0x7A, \
        0xD3, 0xDF, 0x1E, 0xD5, 0xD5, 0xFD, 0x65, 0x61, \
        0x24, 0x33, 0xF5, 0x1F, 0x5F, 0x06, 0x6E, 0xD0, \
        0x85, 0x63, 0x65, 0x55, 0x3D, 0xED, 0x1A, 0xF3, \
        0xB5, 0x57, 0x13, 0x5E, 0x7F, 0x57, 0xC9, 0x35, \
        0x98, 0x4F, 0x0C, 0x70, 0xE0, 0xE6, 0x8B, 0x77, \
        0xE2, 0xA6, 0x89, 0xDA, 0xF3, 0xEF, 0xE8, 0x72, \
        0x1D, 0xF1, 0x58, 0xA1, 0x36, 0xAD, 0xE7, 0x35, \
        0x30, 0xAC, 0xCA, 0x4F, 0x48, 0x3A, 0x79, 0x7A, \
        0xBC, 0x0A, 0xB1, 0x82, 0xB3, 0x24, 0xFB, 0x61, \
        0xD1, 0x08, 0xA9, 0x4B, 0xB2, 0xC8, 0xE3, 0xFB, \
        0xB9, 0x6A, 0xDA, 0xB7, 0x60, 0xD7, 0xF4, 0x68, \
        0x1D, 0x4F, 0x42, 0xA3, 0xDE, 0x39, 0x4D, 0xF4, \
        0xAE, 0x56, 0xED, 0xE7, 0x63, 0x72, 0xBB, 0x19, \
        0x0B, 0x07, 0xA7, 0xC8, 0xEE, 0x0A, 0x6D, 0x70, \
        0x9E, 0x02, 0xFC, 0xE1, 0xCD, 0xF7, 0xE2, 0xEC, \
        0xC0, 0x34, 0x04, 0xCD, 0x28, 0x34, 0x2F, 0x61, \
        0x91, 0x72, 0xFE, 0x9C, 0xE9, 0x85, 0x83, 0xFF, \
        0x8E, 0x4F, 0x12, 0x32, 0xEE, 0xF2, 0x81, 0x83, \
        0xC3, 0xFE, 0x3B, 0x1B, 0x4C, 0x6F, 0xAD, 0x73, \
        0x3B, 0xB5, 0xFC, 0xBC, 0x2E, 0xC2, 0x20, 0x05, \
        0xC5, 0x8E, 0xF1, 0x83, 0x7D, 0x16, 0x83, 0xB2, \
        0xC6, 0xF3, 0x4A, 0x26, 0xC1, 0xB2, 0xEF, 0xFA, \
        0x88, 0x6B, 0x42, 0x38, 0x61, 0x1F, 0xCF, 0xDC, \
        0xDE, 0x35, 0x5B, 0x3B, 0x65, 0x19, 0x03, 0x5B, \
        0xBC, 0x34, 0xF4, 0xDE, 0xF9, 0x9C, 0x02, 0x38, \
        0x61, 0xB4, 0x6F, 0xC9, 0xD6, 0xE6, 0xC9, 0x07, \
        0x7A, 0xD9, 0x1D, 0x26, 0x91, 0xF7, 0xF7, 0xEE, \
        0x59, 0x8C, 0xB0, 0xFA, 0xC1, 0x86, 0xD9, 0x1C, \
        0xAE, 0xFE, 0x13, 0x09, 0x85, 0x13, 0x92, 0x70, \
        0xB4, 0x13, 0x0C, 0x93, 0xBC, 0x43, 0x79, 0x44, \
        0xF4, 0xFD, 0x44, 0x52, 0xE2, 0xD7, 0x4D, 0xD3, \
        0x64, 0xF2, 0xE2, 0x1E, 0x71, 0xF5, 0x4B, 0xFF, \
        0x5C, 0xAE, 0x82, 0xAB, 0x9C, 0x9D, 0xF6, 0x9E, \
        0xE8, 0x6D, 0x2B, 0xC5, 0x22, 0x36, 0x3A, 0x0D, \
        0xAB, 0xC5, 0x21, 0x97, 0x9B, 0x0D, 0xEA, 0xDA, \
        0x1D, 0xBF, 0x9A, 0x42, 0xD5, 0xC4, 0x48, 0x4E, \
        0x0A, 0xBC, 0xD0, 0x6B, 0xFA, 0x53, 0xDD, 0xEF, \
        0x3C, 0x1B, 0x20, 0xEE, 0x3F, 0xD5, 0x9D, 0x7C, \
        0x25, 0xE4, 0x1D, 0x2B, 0x66, 0x9E, 0x1E, 0xF1, \
        0x6E, 0x6F, 0x52, 0xC3, 0x16, 0x4D, 0xF4, 0xFB, \
        0x79, 0x30, 0xE9, 0xE4, 0xE5, 0x88, 0x57, 0xB6, \
        0xAC, 0x7D, 0x5F, 0x42, 0xD6, 0x9F, 0x6D, 0x18, \
        0x77, 0x63, 0xCF, 0x1D, 0x55, 0x03, 0x40, 0x04, \
        0x87, 0xF5, 0x5B, 0xA5, 0x7E, 0x31, 0xCC, 0x7A, \
        0x71, 0x35, 0xC8, 0x86, 0xEF, 0xB4, 0x31, 0x8A, \
        0xED, 0x6A, 0x1E, 0x01, 0x2D, 0x9E, 0x68, 0x32, \
        0xA9, 0x07, 0x60, 0x0A, 0x91, 0x81, 0x30, 0xC4, \
        0x6D, 0xC7, 0x78, 0xF9, 0x71, 0xAD, 0x00, 0x38, \
        0x09, 0x29, 0x99, 0xA3, 0x33, 0xCB, 0x8B, 0x7A, \
        0x1A, 0x1D, 0xB9, 0x3D, 0x71, 0x40, 0x00, 0x3C, \
        0x2A, 0x4E, 0xCE, 0xA9, 0xF9, 0x8D, 0x0A, 0xCC, \
        0x0A, 0x82, 0x91, 0xCD, 0xCE, 0xC9, 0x7D, 0xCF, \
        0x8E, 0xC9, 0xB5, 0x5A, 0x7F, 0x88, 0xA4, 0x6B, \
        0x4D, 0xB5, 0xA8, 0x51, 0xF4, 0x41, 0x82, 0xE1, \
        0xC6, 0x8A, 0x00, 0x7E, 0x5E, 0x65, 0x5F, 0x6A, \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
// clang-format on

static const unsigned char dhm_P_2048[] = MCUXCLPSADRIVER_DHM_RFC7919_FFDHE2048_P_BIN;
static const unsigned char dhm_P_3072[] = MCUXCLPSADRIVER_DHM_RFC7919_FFDHE3072_P_BIN;
static const unsigned char dhm_P_4096[] = MCUXCLPSADRIVER_DHM_RFC7919_FFDHE4096_P_BIN;

// The following operands are used for calculation of the
// modular exponentiation for DH key agreement.
#define MCUXCLPSADRIVER_DHM_OP_X  0u
#define MCUXCLPSADRIVER_DHM_OP_R  1u
#define MCUXCLPSADRIVER_DHM_OP_N  2u
#define MCUXCLPSADRIVER_DHM_OP_T0 3u
#define MCUXCLPSADRIVER_DHM_OP_T1 4u
#define MCUXCLPSADRIVER_DHM_OP_T2 5u
#define MCUXCLPSADRIVER_DHM_OP_T3 6u
#define MCUXCLPSADRIVER_DHM_OP_TE 7u

// The following ones are used only during calcualtion of montgomery
// representation of N and for transforming the result back. Those can
// be overlayed with (temp) buffers from the exponentiation
// to save memory in PKC RAM.
#define MCUXCLPSADRIVER_DHM_NUM_OPERANDS 8u
#define MCUXCLPSADRIVER_DHM_OP_S         MCUXCLPSADRIVER_DHM_OP_T0
#define MCUXCLPSADRIVER_DHM_OP_Q2        MCUXCLPSADRIVER_DHM_OP_T1
#define MCUXCLPSADRIVER_DHM_OP_T         MCUXCLPSADRIVER_DHM_OP_T2

// The max supported modulus for accelerated DHM is 4096 bits (due to memory
// constraints). Now depending on which recomendation is applied the corresponding
// recommended bit size of the private key (= exponent) varies quite a bit.
// However 512 bit is a good upper bound with a big margin.
#define MCUXCLPSADRIVER_DHM_MAX_EXPONENT_SIZE_BYTES (512U / 8U)
#define MCUXCLPSADRIVER_DHM_WACPU_SIZE              (MCUXCLPSADRIVER_DHM_MAX_EXPONENT_SIZE_BYTES + sizeof(uint32_t))

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_generate_random( uint8_t *output,
                                                                       size_t output_size )
{
    mcuxClSession_Descriptor_t session;

    /* Allocate workarea space */
    uint32_t cpuWorkarea[MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE / sizeof(uint32_t)];

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(retSessionInit, tokenSessionInit, mcuxClSession_init(&session,
                                                                     cpuWorkarea,
                                                                     MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE,
                                                                     NULL,
                                                                     0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != retSessionInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Random init                                                            */
    /**************************************************************************/

    /* Initialize the RNG context, with maximum size */
    uint32_t rng_ctx[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};

    mcuxClRandom_Mode_t randomMode = NULL;
    if(output_size <= 16u)  /* 128-bit security strength */
    {
      randomMode = mcuxClRandomModes_Mode_ELS_Drbg;
    }
    else  /* 256-bit security strength */
    {
      randomMode = mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(retRandomInit, tokenRandInit, mcuxClRandom_init(
                                                  &session,
                                                  (mcuxClRandom_Context_t)rng_ctx,
                                                  randomMode));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != tokenRandInit) || (MCUXCLRANDOM_STATUS_OK != retRandomInit))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate random values.                                                */
    /**************************************************************************/

    /* Generate random values of smaller amount than one word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(retRandGen, tokenRandGen, mcuxClRandom_generate(
                                                  &session,
                                                  output,
                                                  output_size));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != tokenRandGen) || (MCUXCLRANDOM_STATUS_OK != retRandGen))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Return with success */
    return PSA_SUCCESS;
}

/**
 * @brief Creates a CLNS key handle from information provided by the driver interface.
 *
 * The driver functions all receive: (1) key attributes along with a (2) key buffer and
 * (3) the key buffer size. The key attributes encode:
 *
 * 1. the key location, of which we support four:
 *
 *    +-------------------+-------------------+-------------------------+--------------------+
 *    | Key location name | Usage by (IP/SW)  | Storage-time            | Use-time           |
 *    +-------------------+-------------------+-------------------------+--------------------+
 *    | LOCAL_STORAGE     | S50/PKC and       | unencrypted, in memory                       |
 *    | (default)         | Software fallback |                                              |
 *    | (0x000000)        |                   |                                              |
 *    +-------------------+-------------------+-------------------------+--------------------+
 *    | S50_TEMP_STORAGE  | S50 only          | key slot number only    | already present in |
 *    | (0x800002)        |                   |                         | S50 keystore       |
 *    +-------------------+-------------------+-------------------------+--------------------+
 *    | S50_BLOB_STORAGE  | S50 only          | RFC3394-wrapped         | unwrap into S50    |
 *    | (0x800001)        |                   | in memory               | keystore           |
 *    +-------------------+-------------------+-------------------------+--------------------+
 *    | S50_ENC_STORAGE   | S50/PKC and       | AES-CBC encrpted        | decrypt on stack   |
 *    | (0x800000)        | Software fallback | in memory               |                    |
 *    +-------------------+-------------------+-------------------------+--------------------+
 *
 *    As of 7 May 2022, only LOCAL_STORAGE and S50_TEMP_STORAGE shall be implemented. For keys
 *    with LOCAL_STORAGE, the key_buffer (see below) contains the whole key in plain. For keys
 *    with S50_TEMP_STORAGE type, the key buffer contains the key slot number as a
 *    `psa_drv_slot_number_t`.
 *
 *    Update: Only LOCAL_STORAGE will be supported natively by the mcuxClPsaDriver, all other key
 *    types will be handled by a user provided Oracle for which CLNS contains the API definition.
 *    The Oracle API and functionality are described in the header file mcuxClPsaDriver_Oracle.h
 *
 * 2. the type of key, such as whether it is an AES key. Of these we support, possibly among
 *    others:
 *
 *    PSA_KEY_TYPE_HMAC, PSA_KEY_TYPE_AES, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
 *    PSA_KEY_TYPE_RSA_KEY_PAIR, PSA_KEY_TYPE_ECC_KEY_PAIR(...) and PSA_KEY_TYPE_ECC_PUBLIC_KEY.
 *
 * 3. key persistence, i.e. whether it is volatile or persistent. Keys with LOCAL_STORAGE may
 *    be volatile or persistent, while keys with S50_TEMP_STORAGE are always volatile. (see
 *    documentation of `psa_key_lifetime_t`).
 *
 * 4. key usage bits (many of these can be set for a single key!), a list follows:
 *
 *    PSA_KEY_USAGE_EXPORT, PSA_KEY_USAGE_COPY, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_USAGE_DECRYPT,
 *    PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_USAGE_SIGN_HASH,
 *    PSA_KEY_USAGE_VERIFY_HASH, PSA_KEY_USAGE_DERIVE, PSA_KEY_USAGE_VERIFY_DERIVATION
 *
 * 5. a key algorithm (only ONE of these can be set for a single key):
 *
 *    PSA_ALG_SHA_256, PSA_ALG_HMAC(PSA_ALG_SHA_256), PSA_ALG_CMAC, PSA_ALG_CTR,
 *    PSA_ALG_ECB_NO_PADDING, PSA_ALG_CBC_NO_PADDING, ...
 *
 * From this information we construct the key descriptor to use with CLNS functions.
 *
 * @param attributes The key attributes associated with the key.
 * @param key_buffer The PSA-provided key buffer.
 * @param key_buffer_size The PSA-provided key buffer size.
 * @param out_key_descriptor The output key handle.
 * @return A status indicating whether key creation was successful or an error occurred.
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_createClKey(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    mcuxClKey_Descriptor_t *out_key_descriptor
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( psa_get_key_lifetime(attributes) );

    if(out_key_descriptor == NULL)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    // store/backup the attributes and key buffer to the key container, the Oracle expects them to be there
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
    mcuxClKey_setKeyData(out_key_descriptor, (uint8_t*)key_buffer);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
    mcuxClKey_setKeyContainerSize(out_key_descriptor, (uint32_t)key_buffer_size);
    mcuxClKey_setKeyContainerUsedSize(out_key_descriptor, (uint32_t)key_buffer_size);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
    mcuxClKey_setAuxData(out_key_descriptor, (void*)attributes);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
    mcuxClKey_setLoadStatus(out_key_descriptor, MCUXCLKEY_LOADSTATUS_NOTLOADED);

    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )
    {
        psa_status_t retCode = mcuxClPsaDriver_Oracle_LoadKey(out_key_descriptor);
        if(PSA_ERROR_NOT_SUPPORTED == retCode)
        {
            return retCode;
        }
        if(PSA_SUCCESS !=  retCode)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
    }
    else
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Loaded key is aligned")
        mcuxClKey_setLoadedKeyData(out_key_descriptor, (uint32_t *) key_buffer);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
        mcuxClKey_setLoadedKeyLength(out_key_descriptor, (uint32_t)key_buffer_size);
        mcuxClKey_setLoadedKeySlot(out_key_descriptor, 0xFFFFFFu);
        mcuxClKey_setLoadStatus(out_key_descriptor, MCUXCLKEY_LOADSTATUS_MEMORY);
    }

    mcuxClKey_setProtectionType(out_key_descriptor, mcuxClKey_Protection_None);
    mcuxClKey_TypeDescriptor_t keyTypeDesc;

    keyTypeDesc.info = NULL;
    MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
    switch(psa_get_key_type(attributes)) {
        case PSA_KEY_TYPE_AES:
            switch(mcuxClKey_getLoadedKeyLength(out_key_descriptor)) {
                case 16u:
                    keyTypeDesc = mcuxClKey_TypeDescriptor_Aes128;
                    break;
                case 24u:
                    keyTypeDesc = mcuxClKey_TypeDescriptor_Aes192;
                    break;
                case 32u:
                    keyTypeDesc = mcuxClKey_TypeDescriptor_Aes256;
                    break;
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_KEY_TYPE_HMAC:
            if( MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(out_key_descriptor) )
            {
                if(32u == mcuxClKey_getLoadedKeyLength(out_key_descriptor))
                {
                    // the internal key store only supports 256 bit HMAC keys
                    keyTypeDesc = mcuxClKey_TypeDescriptor_HmacSha256;
                }
                else
                {
                    return PSA_ERROR_NOT_SUPPORTED;
                }
            }
            else if( MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(out_key_descriptor) )
            {
                mcuxClKey_TypeDescriptor_t type = {MCUXCLKEY_ALGO_ID_HMAC + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, key_buffer_size, NULL};
                keyTypeDesc = type;
            }
            else
            {
                return PSA_ERROR_CORRUPTION_DETECTED;
            }
            break;
/*
        Provisional support for the ECC iternal key type
*/
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1):
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1):
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1):
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY):
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS):
            keyTypeDesc.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_KEY_PAIR; // not really needed for ECC operation for now
            keyTypeDesc.size = ((mcuxClKey_Size_t) psa_get_key_bits(attributes)  + 7u) / 8u; // not really needed for ECC operation for now
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            keyTypeDesc.info = (void *) mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(attributes);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            break;
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_K1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS):
            keyTypeDesc.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY;
            keyTypeDesc.size = ((mcuxClKey_Size_t) psa_get_key_bits(attributes) + 7u) / 8u;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            keyTypeDesc.info = (void *) mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(attributes);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            break;

        case PSA_KEY_TYPE_RSA_PUBLIC_KEY:
        case PSA_KEY_TYPE_RSA_KEY_PAIR:
            // for now only keys in LOCAL_STORAGE are supported
            keyTypeDesc.algoId = MCUXCLKEY_ALGO_ID_RSA;
            keyTypeDesc.size = ((mcuxClKey_Size_t) psa_get_key_bits(attributes) + 7u) / 8u;

            if( MCUXCLKEY_LOADSTATUS_MEMORY != mcuxClKey_getLoadStatus(out_key_descriptor) )
            {
                return PSA_ERROR_NOT_SUPPORTED;
            }
            if((psa_get_key_type(attributes) & PSA_KEY_TYPE_CATEGORY_FLAG_PAIR) == PSA_KEY_TYPE_CATEGORY_FLAG_PAIR)
            {
                keyTypeDesc.algoId |= MCUXCLKEY_ALGO_ID_KEY_PAIR;
            }
            else
            {
                keyTypeDesc.algoId |= MCUXCLKEY_ALGO_ID_PUBLIC_KEY;
            }
            break;

        case PSA_KEY_TYPE_RAW_DATA:
            {
                // used for psa export
                mcuxClKey_TypeDescriptor_t type = {0u, key_buffer_size, NULL};
                keyTypeDesc = type;
            }
            break;

        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()

    mcuxClKey_setTypeDescriptor(out_key_descriptor, keyTypeDesc);

    return PSA_SUCCESS;
}

static inline psa_status_t mcuxClPsaDriver_psa_driver_wrapper_generate_s50_key(
    const psa_key_attributes_t *attributes,
    mcuxClEls_KeyIndex_t key_index_private_key,
    uint8_t * public_key_buffer, uint32_t public_key_buffer_size)
{
    size_t bitLength = psa_get_key_bits(attributes);
    size_t bytes = (size_t)MCUXCLPSADRIVER_BITS_TO_BYTES(bitLength);
    if(public_key_buffer_size < (2u * bytes))
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    if(bytes != MCUXCLKEY_SIZE_256)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    mcuxClEls_KeyProp_t  keyProp;
    keyProp.word.value       = 0;
    keyProp.bits.ksize       = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv       = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    keyProp.bits.ukgsrc      = MCUXCLELS_KEYPROPERTY_INPUT_FOR_ECC_TRUE;
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_FALSE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_FALSE;
    keyProp.bits.wrpok       = MCUXCLELS_KEYPROPERTY_WRAP_TRUE;

    mcuxClEls_EccKeyGenOption_t KeyGenOptions;
    KeyGenOptions.word.value    = 0u;
    KeyGenOptions.bits.kgsign   = MCUXCLELS_ECC_PUBLICKEY_SIGN_DISABLE;
    KeyGenOptions.bits.kgtypedh = MCUXCLELS_ECC_OUTPUTKEY_SIGN;
    KeyGenOptions.bits.kgsrc    = MCUXCLELS_ECC_OUTPUTKEY_RANDOM;
    KeyGenOptions.bits.skip_pbk = MCUXCLELS_ECC_GEN_PUBLIC_KEY;

    /*Step 1:
        Generate Key pair:
        - Private key will be stored in ELS's KeyStore
        - Public Key will be stored in external RAM
    */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccKeyGen_Async( // Perform key generation.
            KeyGenOptions,                   // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t) 0U,        // This parameter (signingKeyIdx) is ignored, since no signature is requested in the configuration.
            key_index_private_key,           // Keystore index at which the generated private key is stored.
            keyProp,                         // Set the generated key properties.
            NULL,                            // No random data is provided
            public_key_buffer                // Output buffer, which the operation will write the public key to.
            ));
    // mcuxClEls_EccKeyGen_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccKeyGen_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return PSA_ERROR_GENERIC_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_EccKeyGen_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccKeyGen_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
         return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_key_generate(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t type = psa_get_key_type(attributes);
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
    
    /* Step 1:
       Allocate storage for a key to be generated
    */
    mcuxClKey_Descriptor_t key = {0u};
    /* Initialize the key container */
    mcuxClKey_setKeyData(&key, (uint8_t *)key_buffer);
    mcuxClKey_setKeyContainerSize(&key, (uint32_t)key_buffer_size);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
    mcuxClKey_setAuxData(&key, (void*)attributes);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

    /* Initialize the loaded key data (location descr.) as a storage for the public key */
    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)))
    {
        /* key stored in orace - call Orcale to reserve memory for the key */
        status = mcuxClPsaDriver_Oracle_ReserveKey(&key);
        if(PSA_SUCCESS != status)
        {
            return status;
        }
    }
    else
    {
        /* local storage - setup loaded key with buffer from caller */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Loaded key is aligned")
        mcuxClKey_setLoadedKeyData(&key, (uint32_t *)key_buffer);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
        mcuxClKey_setLoadedKeyLength(&key, (uint32_t)key_buffer_size);
        mcuxClKey_setLoadStatus(&key, MCUXCLKEY_LOADSTATUS_MEMORY);
    }

    /* Step 2:
       Depending on the location, see how to generate the private key
    */
    if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(&key))
    {
        /* LoadedKeyData serves as a throw-away buffer for the public key.
           The private key will be kept in the given key slot of the keystore. */

        status = mcuxClPsaDriver_psa_driver_wrapper_generate_s50_key(
            /* const psa_key_attributes_t *attributes:     */ attributes,
            /* mcuxClEls_KeyIndex_t key_index_private_key:  */ mcuxClKey_getLoadedKeySlot(&key),
            /* uint8_t *public_key_buffer:                 */ mcuxClKey_getLoadedKeyData(&key),
            /* uint32_t public_key_buffer_size:            */ mcuxClKey_getLoadedKeyLength(&key)
        );

        if(status != PSA_SUCCESS)
        {
            return status;
        }
    }
    else /* MCUXCLKEY_LOADSTATUS_MEMORY */
    {
        if(key_type_is_raw_bytes(type))
        {
            status = mcuxClPsaDriver_psa_driver_wrapper_generate_random(mcuxClKey_getLoadedKeyData(&key), mcuxClKey_getLoadedKeyLength(&key));
            if(status != PSA_SUCCESS)
            {
                return status;
            }
            *key_buffer_length = mcuxClKey_getLoadedKeyLength(&key);
        }
        else if(type == PSA_KEY_TYPE_RSA_KEY_PAIR)
        {
            status = mcuxClPsaDriver_psa_driver_wrapper_rsa_key(attributes,
                                               mcuxClKey_getLoadedKeyData(&key),
                                               mcuxClKey_getLoadedKeyLength(&key),
                                               key_buffer_length);
            if(status != PSA_SUCCESS)
            {
                return status;
            }
        }
        else if(PSA_KEY_TYPE_IS_ECC(type) && PSA_KEY_TYPE_IS_KEY_PAIR(type))
        {
            status = mcuxClPsaDriver_psa_driver_wrapper_generate_ecp_key(attributes,
                                                  mcuxClKey_getLoadedKeyData(&key),
                                                  mcuxClKey_getLoadedKeyLength(&key),
                                                  key_buffer_length);
            if(status != PSA_SUCCESS)
            {
                return status;
            }
        }
        else
        {
            (void)key_buffer_length;
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }

    /* Step 3:
       Store the generated private key in the buffer provided by the caller
    */
    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)))
    {
        status = mcuxClPsaDriver_Oracle_StoreKey(&key);
        if(PSA_SUCCESS != status)
        {
            return status;
        }
        *key_buffer_length = mcuxClKey_getKeyContainerUsedSize(&key);
    }
    /* Note: For keys in local storage no additional store or copy operation is needed,
             because the key_buffer was already used during the key generation. */

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClEcc_Weier_DomainParams_t* mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(
     const psa_key_attributes_t *attributes)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
    switch(psa_get_key_type(attributes))
    {
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1):
            switch((uint32_t)(MCUXCLPSADRIVER_BITS_TO_BYTES((uint32_t)psa_get_key_bits(attributes)))) {
                case MCUXCLKEY_SIZE_192:
                    return &mcuxClEcc_Weier_DomainParams_secp192r1;
                case MCUXCLKEY_SIZE_224:
                    return &mcuxClEcc_Weier_DomainParams_secp224r1;
                case MCUXCLKEY_SIZE_256:
                    return &mcuxClEcc_Weier_DomainParams_secp256r1;
                case MCUXCLKEY_SIZE_384:
                    return &mcuxClEcc_Weier_DomainParams_secp384r1;
                case MCUXCLKEY_SIZE_521:
                    return &mcuxClEcc_Weier_DomainParams_secp521r1;
                default:
                    return NULL;
            }
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_K1):
            switch((uint32_t)(MCUXCLPSADRIVER_BITS_TO_BYTES((uint32_t)psa_get_key_bits(attributes)))) {
                case MCUXCLKEY_SIZE_192:
                    return &mcuxClEcc_Weier_DomainParams_secp192k1;
                case MCUXCLKEY_SIZE_224:
                    return &mcuxClEcc_Weier_DomainParams_secp224k1;
                case MCUXCLKEY_SIZE_256:
                    return &mcuxClEcc_Weier_DomainParams_secp256k1;
                default:
                    return NULL;
            }
        case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1):
        case PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1):
            switch((uint32_t)(MCUXCLPSADRIVER_BITS_TO_BYTES((uint32_t)psa_get_key_bits(attributes)))) {
                case MCUXCLKEY_SIZE_160:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP160r1;
                case MCUXCLKEY_SIZE_192:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP192r1;
                case MCUXCLKEY_SIZE_224:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP224r1;
                case MCUXCLKEY_SIZE_256:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP256r1;
                case MCUXCLKEY_SIZE_320:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP320r1;
                case MCUXCLKEY_SIZE_384:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP384r1;
                case MCUXCLKEY_SIZE_512:
                    return &mcuxClEcc_Weier_DomainParams_brainpoolP512r1;
                default:
                    return NULL;
            }
        default:
            return NULL;
    }
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_exportKey(const psa_key_attributes_t *attributes,
                                                         const uint8_t *key_buffer,
                                                         size_t key_buffer_size,
                                                         uint8_t *data,
                                                         size_t data_size,
                                                         size_t *data_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t psa_status = PSA_ERROR_NOT_SUPPORTED;
    mcuxClKey_Descriptor_t key = {0};

    psa_status = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS == psa_status)
    {
        /* not supported for internal keys */
        if( MCUXCLKEY_LOADSTATUS_MEMORY != mcuxClKey_getLoadStatus(&key) )
        {
            (void)mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
            return PSA_ERROR_NOT_SUPPORTED;
        }

        /* check for buffer too small */
        if( key.location.length > data_size ) {
            (void)mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
            return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenNxpClMemory_copy, mcuxClMemory_copy(data,
                                                                                     key.location.pData,
                                                                                     key.location.length,
                                                                                     data_size));
        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenNxpClMemory_copy)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

        *data_length = key.location.length;

        /* unload key */
        psa_status = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);
    }
    return psa_status;
}

static size_t calc_bitlen_be(const uint8_t *n, size_t len)
{
    size_t zeros = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (n[i] == 0u)
        {
            zeros += 8u;
        }
        else
        {
            uint8_t mask = 0x80u;
            for (size_t j = 0u; j < 8u; j++)
            {
                if ((n[i] & mask) == 0u)
                {
                    zeros += 1u;
                }
                else
                {
                    return len * 8u - zeros;
                }
                mask >>= 1;
            }
        }
    }
    return len * 8u - zeros;
}

static size_t sz_max(size_t a, size_t b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

static void reverse_and_copy(uint8_t *dst, size_t dst_len, const uint8_t *src, size_t src_len, size_t copy_len)
{
    src = src + src_len;
    for (size_t i = 0; i < copy_len; i++)
    {
        *dst++ = *(--src);
    }
    if (dst_len > copy_len)
    {
        (void)memset(dst, 0, dst_len - copy_len);
    }
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_key_agreement_internal(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *shared_secret,
    size_t shared_secret_size,
    size_t *shared_secret_length)
{
    uint32_t pCpuWa[MCUXCLCORE_MAX(MCUXCLCORE_MAX(MCUXCLCORE_MAX(MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WACPU_SIZE,
                                MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE),
                            MCUXCLECC_POINTMULT_WACPU_SIZE),
                        MCUXCLPSADRIVER_DHM_WACPU_SIZE) /
                    (sizeof(uint32_t))];
    if(PSA_ALG_IS_ECDH(alg))
    {
        if (!PSA_KEY_TYPE_IS_ECC_KEY_PAIR(psa_get_key_type(attributes)))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION("PSA_KEY_TYPE_ECC_GET_FAMILY macro comes from external library outside our control")
        psa_ecc_family_t curve = MCUXCLPSADRIVER_PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
        size_t privateKeySize = MCUXCLPSADRIVER_BITS_TO_BYTES(psa_get_key_bits(attributes));

        /* Setup one session to be used by all functions called */
        mcuxClSession_Descriptor_t session;

        //For Montgomery curves
        if(PSA_ECC_FAMILY_MONTGOMERY == curve)
        {
            /* Curve448 */
            if(MCUXCLECC_MONTDH_CURVE448_SIZE_PRIVATEKEY == privateKeySize)
            {
                if(MCUXCLECC_MONTDH_CURVE448_SIZE_PUBLICKEY != peer_key_length)
                {
                    return PSA_ERROR_INVALID_ARGUMENT;
                }
                /* Initialize session with pkcWA on the beginning of PKC RAM */
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WACPU_SIZE,
                                        (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WAPKC_SIZE));


                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                /* Initialize the PRNG */
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                ALIGNED uint8_t privateKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
                MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                mcuxClKey_Handle_t privKeyHandler = (mcuxClKey_Handle_t) &privateKeyDesc;
                MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(privkeyinit_result, privkeyinit_token, mcuxClKey_init(
                /* mcuxClSession_Handle_t session         */ &session,
                /* mcuxClKey_Handle_t key                 */ privKeyHandler,
                /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve448_PrivateKey,
                /* const uint8_t * pKeyData              */ key_buffer,
                /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE448_SIZE_PRIVATEKEY));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != privkeyinit_token) || (MCUXCLKEY_STATUS_OK != privkeyinit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                ALIGNED uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
                MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                mcuxClKey_Handle_t pubKeyHandler = (mcuxClKey_Handle_t) &pubKeyDesc;
                MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pubkeyinit_result, pubkeyinit_token, mcuxClKey_init(
                /* mcuxClSession_Handle_t session         */ &session,
                /* mcuxClKey_Handle_t key                 */ pubKeyHandler,
                /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve448_PublicKey,
                /* const uint8_t * pKeyData              */ peer_key,
                /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE448_SIZE_PUBLICKEY));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != pubkeyinit_token) || (MCUXCLKEY_STATUS_OK != pubkeyinit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                /* Call Dh KeyAgreement for shared secret generation and check FP and return code */
                uint32_t outLength = 0u;
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_MontDH_KeyAgreement(&session,
                                                                                                privKeyHandler,
                                                                                                pubKeyHandler,
                                                                                                shared_secret,
                                                                                                &outLength));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                *shared_secret_length = (size_t)outLength;

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                return PSA_SUCCESS;
            }
            /* Curve25519 */
            else if(MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY == privateKeySize)
            {
                if(MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY != peer_key_length)
                {
                    return PSA_ERROR_INVALID_ARGUMENT;
                }
                /* Initialize session with pkcWA on the beginning of PKC RAM */
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE,
                                        (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WAPKC_SIZE));


                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                /* Initialize the PRNG */
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                ALIGNED uint8_t privateKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
                MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                mcuxClKey_Handle_t privKeyHandler = (mcuxClKey_Handle_t) &privateKeyDesc;
                MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(privkeyinit_result, privkeyinit_token, mcuxClKey_init(
                /* mcuxClSession_Handle_t session         */ &session,
                /* mcuxClKey_Handle_t key                 */ privKeyHandler,
                /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PrivateKey,
                /* const uint8_t * pKeyData              */ key_buffer,
                /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != privkeyinit_token) || (MCUXCLKEY_STATUS_OK != privkeyinit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                ALIGNED uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
                MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                mcuxClKey_Handle_t pubKeyHandler = (mcuxClKey_Handle_t) &pubKeyDesc;
                MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pubkeyinit_result, pubkeyinit_token, mcuxClKey_init(
                /* mcuxClSession_Handle_t session         */ &session,
                /* mcuxClKey_Handle_t key                 */ pubKeyHandler,
                /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PublicKey,
                /* const uint8_t * pKeyData              */ peer_key,
                /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != pubkeyinit_token) || (MCUXCLKEY_STATUS_OK != pubkeyinit_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                /* Call Dh KeyAgreement for shared secret generation and check FP and return code */
                uint32_t outLength = 0u;
                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_MontDH_KeyAgreement(&session,
                                                                                                privKeyHandler,
                                                                                                pubKeyHandler,
                                                                                                shared_secret,
                                                                                                &outLength));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                *shared_secret_length = (size_t)outLength;

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();

                MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
                if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
                {
                    return PSA_ERROR_GENERIC_ERROR;
                }
                MCUX_CSSL_FP_FUNCTION_CALL_END();
                return PSA_SUCCESS;
            }
            else
            {
                return PSA_ERROR_NOT_SUPPORTED;
            }
        }
        /* For Weierstrass curves, curve_parameters are defined in mcuxClEcc_Constants.h */
        else if((PSA_ECC_FAMILY_SECP_R1 == curve) || (PSA_ECC_FAMILY_SECP_K1 == curve) || (PSA_ECC_FAMILY_BRAINPOOL_P_R1 == curve))
        {
            if ((peer_key_length & 1u) == 0u) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }

            const mcuxClEcc_Weier_DomainParams_t* curveParamData = mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(attributes);
            if(NULL == curveParamData)
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }

            /* Initialize buffers on the stack for domain parameters endianess swap (LE -> BE) */
            const uint32_t byteLenP = curveParamData->common.byteLenP;
            const uint32_t byteLenN = curveParamData->common.byteLenN;

            /* Reverse endianess of domain parameters as current ECC component expects domain parameters in big endian */
            uint8_t pG[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
            uint8_t pA[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
            uint8_t pB[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
            uint8_t pP[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
            uint8_t pN[MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER];
            for(uint32_t i = 0; i < byteLenP; i++)
            {
                pA[i] = curveParamData->common.pCurveParam1[byteLenP - i - 1u];
                pB[i] = curveParamData->common.pCurveParam2[byteLenP - i - 1u];
                pP[i] = curveParamData->common.pFullModulusP[byteLenP + MCUXCLPKC_WORDSIZE - i - 1u];
                pG[i] = curveParamData->common.pGx[byteLenP - i - 1u];
                pG[byteLenP + i] = curveParamData->common.pGy[byteLenP - i - 1u];
            }
            for(uint32_t i = 0; i < byteLenN; i++)
            {
                pN[i] = curveParamData->common.pFullModulusN[byteLenN + MCUXCLPKC_WORDSIZE - i - 1u];
            }

            uint8_t output[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];

            if(peer_key[0] == 0x04u) {
                /* format == MBEDTLS_ECP_PF_UNCOMPRESSED */
                if (peer_key_length != 1u + byteLenP * 2u) {
                    return PSA_ERROR_INVALID_ARGUMENT;
                }
            }
            else if ((peer_key[0] == 0x02u) || (peer_key[0] == 0x03u))
            {
                /* format == MBEDTLS_ECP_PF_COMPRESSED */
                return PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }

            MCUXCLBUFFER_INIT_RO(buffA, NULL, pA, byteLenP);
            MCUXCLBUFFER_INIT_RO(buffB, NULL, pB, byteLenP);
            MCUXCLBUFFER_INIT_RO(buffP, NULL, pP, byteLenP);
            MCUXCLBUFFER_INIT_RO(buffG, NULL, pG, byteLenP * 2u);
            MCUXCLBUFFER_INIT_RO(buffN, NULL, pN, byteLenN);

            const uint8_t *pOtherPublic = peer_key + 1u;
            MCUXCLBUFFER_INIT_RO(buffKeyBuffer,   NULL, key_buffer,   byte_len_n);
            MCUXCLBUFFER_INIT_RO(buffOtherPublic, NULL, pOtherPublic, byte_len_p * 2u);
            MCUXCLBUFFER_INIT(buffOutput,         NULL, output,       byte_len_p * 2u);

            mcuxClEcc_PointMult_Param_t params =
            {
                .curveParam = (mcuxClEcc_DomainParam_t)
                {
                    .pA = buffA,
                    .pB = buffB,
                    .pP = buffP,
                    .pG = buffG,
                    .pN = buffN,
                    .misc = mcuxClEcc_DomainParam_misc_Pack(byteLenN, byteLenP)
                },
                .pScalar = buffKeyBuffer,
                .pPoint = buffOtherPublic,
                .pResult = buffOutput,
                .optLen = 0u
            };

            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_POINTMULT_WACPU_SIZE,
                                    (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_POINTMULT_WAPKC_SIZE_256));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Call PointMult for public keys generation and check FP and return code */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pointMult_result, pointMult_token, mcuxClEcc_PointMult(&session, &params));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointMult) != pointMult_token) || (MCUXCLECC_STATUS_OK != pointMult_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *shared_secret_length = byteLenP;
            MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenNxpClMemory_copy, mcuxClMemory_copy(shared_secret,
                                                                                        output,
                                                                                        byteLenP,
                                                                                        byteLenP));
            if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenNxpClMemory_copy)
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            return PSA_SUCCESS;
        }
        else
        {
            (void) attributes;
            (void) key_buffer;
            (void) key_buffer_size;
            (void) peer_key;
            (void) peer_key_length;
            (void) shared_secret;
            (void) shared_secret_size;
            (void) shared_secret_length;
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else if (PSA_ALG_IS_FFDH(alg))
    {
        if (!PSA_KEY_TYPE_IS_DH_KEY_PAIR(psa_get_key_type(attributes)))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        size_t bitlen_n = psa_get_key_bits(attributes);
        if (MCUXCLPSADRIVER_BITS_TO_BYTES(bitlen_n) != key_buffer_size)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (shared_secret_size < MCUXCLPSADRIVER_BITS_TO_BYTES(bitlen_n))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (peer_key_length != key_buffer_size)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        const uint8_t *modulus = NULL;
        switch (bitlen_n)
        {
            case 2048u:
                modulus = dhm_P_2048;
                break;
            case 3072u:
                modulus = dhm_P_3072;
                break;
            case 4096u:
                modulus = dhm_P_4096;
                break;
            // For the groups with more bits, there is not
            // enough PKC ram
            // case 6144u:
            //     modulus = dhm_P_6144;
            //     break;
            // case 8192u:
            //     modulus = dhm_P_8192;
            //     break;
            default:
                return PSA_ERROR_NOT_SUPPORTED;
        }

        size_t bitlen_e = calc_bitlen_be(key_buffer, key_buffer_size);
        size_t bitlen_a = calc_bitlen_be(peer_key, peer_key_length);

        // If the exponent is 0, fall back to SW implementation.
        if (bitlen_e == 0u)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        // If the modulus or the exponent is too small, fall back to SW implementation.
        if ((bitlen_n < (MCUXCLPKC_WORDSIZE * 8u)) || (bitlen_e < (MCUXCLPKC_WORDSIZE * 8u)))
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        const size_t bytelen_n = MCUXCLPSADRIVER_BITS_TO_BYTES(bitlen_n);
        const size_t bytelen_e = MCUXCLPSADRIVER_BITS_TO_BYTES(bitlen_e);
        const size_t bytelen_a = MCUXCLPSADRIVER_BITS_TO_BYTES(bitlen_a);

        // If the exponent is too big to fit into the reseved temp buffer, we fall back
        // to software implementation.
        if (bytelen_e > MCUXCLPSADRIVER_DHM_MAX_EXPONENT_SIZE_BYTES)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        // The most significant 32 bits / 4 bytes of the modulus need to be 0 because
        // of PKC requirements. We achieve that by artificially increasing the operand size
        // by 4 bytes.
        size_t pkc_operand_size = MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(bytelen_n + 4u);

        // iX (bits 16~23): index of base number (PKC operand),
        const size_t bufferSizeX = pkc_operand_size + MCUXCLPKC_WORDSIZE; // size of the base

        // size of the result of the exponentiation
        // iR (bits 0~7): index of result (PKC operand).
        // The size shall be at least max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(expByteLength + 1u), lenN +
        // MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeR =
            sz_max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(bytelen_e + 1u), pkc_operand_size + MCUXCLPKC_WORDSIZE);

        // iN (bits 24~31): index of modulus (PKC operand), size = operandSize (= lenN).
        const size_t bufferSizeN =
            pkc_operand_size + MCUXCLPKC_WORDSIZE; // size of N + PKC word in front of the modulus buffer for NDash

        // iT0 (bits 8~15): index of temp0 (PKC operand).
        // The size shall be at least max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(expByteLength + 1u), lenN +
        // MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeT0 =
            sz_max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(bytelen_e + 1u), pkc_operand_size + MCUXCLPKC_WORDSIZE);

        // iT1 (bits 0~7): index of temp1 (PKC operand).
        // Its size shall be at least max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(expByteLength + 1u), lenN + MCUXCLPKC_WORDSIZE,
        // 2 * MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeT1 =
            sz_max(sz_max(MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(bytelen_e + 1u), pkc_operand_size + MCUXCLPKC_WORDSIZE),
                   2u * MCUXCLPKC_WORDSIZE);

        // iT2 (bits 8~15): index of temp2 (PKC operand).
        // Its size shall be at least max(lenN + MCUXCLPKC_WORDSIZE, 2u * MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeT2 = sz_max(pkc_operand_size + MCUXCLPKC_WORDSIZE, 2u * MCUXCLPKC_WORDSIZE);

        // iT3 (bits 24~31): index of temp3 (PKC operand).
        // Its size shall be at least max(lenN + MCUXCLPKC_WORDSIZE, 2u * MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeT3 = sz_max(pkc_operand_size + MCUXCLPKC_WORDSIZE, 2u * MCUXCLPKC_WORDSIZE);

        // iTE (bits 16~23): index of temp4 (PKC operand).
        // The size shall be at least (6u * MCUXCLPKC_WORDSIZE).
        const size_t bufferSizeTE = 6u * MCUXCLPKC_WORDSIZE;

        // ### NDash calculation:
        // iT (bits 0~7): index of temp (PKC operand).
        // The size of temp shall be at least (2 * MCUXCLPKC_WORDSIZE).
        // T is overlayed with mod_exp_T2, size is OK.
        // const uint32_t bufferSizeT = bufferSizeT2;

        // ### QSqared calculation:
        // iT (bits 0~7): index of temp (PKC operand).
        // The size of temp shall be at least (operandSize + MCUXCLPKC_WORDSIZE).
        // T is overlayed with mod_exp_T2, size is OK.

        // iN (bits 8~15): index of modulus (PKC operand), size = operandSize.
        // NDash of modulus shall be stored in the PKC word before modulus.
        // This the modulus buffer used throughout the function, size is OK.

        // iNShifted (bits 16~23): index of shifted modulus (PKC operand), size = operandSize.
        // If there is no leading zero in the PKC operand modulus, it can be iN.
        // This is overlayed with mod_exp_T0, size is OK.

        // iQSqr (bits 24~31): index of result QSquared (PKC operand), size = operandSize.
        // QSquared might be greater than modulus.
        // Q2 is overlayed with mod_exp_T1, size is OK

        // ### Calculate montgomery representation of base
        // iR: result of the multiplication size shall be operandSize.
        // iR is overlayed with mod_exp_X - the base of the exponentiation, size is OK.

        // iX, iY: the two numbers that are multiplied, size shall be operandSize.
        // iX is overlayed with mod_exp_T1, size is OK.
        // iY is overlayed with mod_exp_T0, size is OK.

        // iZ: the modulus
        // This the modulus buffer used throughout the function, size is OK.

        // ### reduction of result
        // iR: the result, size shall be operandSize.
        // This is overlayed with mod_exp_T2, size is OK.

        // iX: the number to reduce
        // This is the output of the exponentiaion, mod_exp_R, size is OK.

        // iZ: the modulus
        // This the modulus buffer used throughout the function, size is OK.

        const size_t bufferSizeS = bufferSizeT0;
        const size_t pkcWaLength =
            bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 + bufferSizeT2 + bufferSizeT3 + bufferSizeTE;

        if ((pkcWaLength) > MCUXCLPKC_RAM_SIZE)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        psa_status_t ret         = PSA_ERROR_GENERIC_ERROR;
        bool session_initialized = false;
        bool pkc_initialized     = false;
        mcuxClPkc_State_t pkc_state;

        ASSERT_CALLED_VOID_OR_EXIT(mcuxClPkc_Initialize(&pkc_state), mcuxClPkc_Initialize);
        pkc_initialized = true;

        uint32_t *pPkcWaBuffer = (uint32_t *)(MCUXCLPKC_RAM_START_ADDRESS);
        uint8_t *pPkcWaBuffer8 = (uint8_t *)pPkcWaBuffer;

        mcuxClSession_Descriptor_t session;
        ASSERT_CALLED_OR_EXIT(mcuxClSession_init(&session, pCpuWa, MCUXCLPSADRIVER_DHM_WACPU_SIZE, pPkcWaBuffer, pkcWaLength), mcuxClSession_init,
                              MCUXCLSESSION_STATUS_OK);
        session_initialized = true;

        uint16_t pOperands[MCUXCLPSADRIVER_DHM_NUM_OPERANDS];
        pOperands[MCUXCLPSADRIVER_DHM_OP_X] = MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8);
        pOperands[MCUXCLPSADRIVER_DHM_OP_R] = MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX);
        pOperands[MCUXCLPSADRIVER_DHM_OP_N] = MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX + bufferSizeR);
        pOperands[MCUXCLPSADRIVER_DHM_OP_T0] =
            MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX + bufferSizeR + bufferSizeN);
        pOperands[MCUXCLPSADRIVER_DHM_OP_T1] =
            MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0);
        pOperands[MCUXCLPSADRIVER_DHM_OP_T2] =
            MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1);
        pOperands[MCUXCLPSADRIVER_DHM_OP_T3] = MCUXCLPKC_PTR2OFFSET(
            pPkcWaBuffer8 + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 + bufferSizeT2);
        pOperands[MCUXCLPSADRIVER_DHM_OP_TE] =
            MCUXCLPKC_PTR2OFFSET(pPkcWaBuffer8 + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 +
                                 bufferSizeT2 + bufferSizeT3);

        /* Set UPTRT table */
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_SETUPTRT(pOperands);

        /* Clear work area */
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH(0u, pkcWaLength);
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLPKC_CALC_OP1_CONST(MCUXCLPSADRIVER_DHM_OP_X, 0u), mcuxClPkc_CalcConst);

        /* Set operand size for the rest of the operations */
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH(pkc_operand_size, pkc_operand_size);

        /* Import N. */
        uint16_t offsetN                    = pOperands[MCUXCLPSADRIVER_DHM_OP_N] + MCUXCLPKC_WORDSIZE;
        pOperands[MCUXCLPSADRIVER_DHM_OP_N] = offsetN;

        uint8_t *pN = (uint8_t *)MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLPSADRIVER_DHM_OP_N]);
        uint8_t *pT = (uint8_t *)MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLPSADRIVER_DHM_OP_T]);
        uint8_t *pS = (uint8_t *)MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLPSADRIVER_DHM_OP_S]);

        MCUXCLPKC_WAITFORFINISH();
        reverse_and_copy(pN, bufferSizeN, modulus, bytelen_n, bytelen_n);
        __DSB();

        // Calculate Q^2 and N-Dash
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLMATH_NDASH(MCUXCLPSADRIVER_DHM_OP_N, MCUXCLPSADRIVER_DHM_OP_T),
                                   mcuxClMath_NDash);
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLMATH_SHIFTMODULUS(MCUXCLPSADRIVER_DHM_OP_S, MCUXCLPSADRIVER_DHM_OP_N),
                                   mcuxClMath_ShiftModulus);
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLMATH_QSQUARED(MCUXCLPSADRIVER_DHM_OP_Q2, MCUXCLPSADRIVER_DHM_OP_S,
                                                       MCUXCLPSADRIVER_DHM_OP_N, MCUXCLPSADRIVER_DHM_OP_T),
                                   mcuxClMath_QSquared);

        // Import base
        MCUXCLPKC_WAITFORFINISH();
        reverse_and_copy(pS, bufferSizeS, peer_key, peer_key_length, bytelen_a);
        __DSB();

        // Calculate montgomery representation of base
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLPKC_CALC_MC1_MM(MCUXCLPSADRIVER_DHM_OP_X, MCUXCLPSADRIVER_DHM_OP_Q2,
                                                         MCUXCLPSADRIVER_DHM_OP_S, MCUXCLPSADRIVER_DHM_OP_N),
                                   mcuxClPkc_Calc);

        const uint8_t *exp_buffer = key_buffer + key_buffer_size - bytelen_e;
        uint32_t *tmp_buffer      = mcuxClSession_allocateWords_cpuWa(&session, (bytelen_e / sizeof(uint32_t)) + 1u);
        if (tmp_buffer == NULL)
        {
            ret = PSA_ERROR_CORRUPTION_DETECTED;
            goto exit;
        }

        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_OR_EXIT(
            MCUXCLMATH_SECMODEXP(&session, exp_buffer, tmp_buffer, bytelen_e, MCUXCLPSADRIVER_DHM_OP_R,
                                 MCUXCLPSADRIVER_DHM_OP_X, MCUXCLPSADRIVER_DHM_OP_N, MCUXCLPSADRIVER_DHM_OP_TE,
                                 MCUXCLPSADRIVER_DHM_OP_T0, MCUXCLPSADRIVER_DHM_OP_T1, MCUXCLPSADRIVER_DHM_OP_T2,
                                 MCUXCLPSADRIVER_DHM_OP_T3),
            mcuxClMath_SecModExp, MCUXCLMATH_STATUS_OK);

        /* Convert R back to NR. */
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(
            MCUXCLPKC_CALC_MC1_MR(MCUXCLPSADRIVER_DHM_OP_T, MCUXCLPSADRIVER_DHM_OP_R, MCUXCLPSADRIVER_DHM_OP_N),
            mcuxClPkc_Calc);
        MCUXCLPKC_WAITFORREADY();
        ASSERT_CALLED_VOID_OR_EXIT(MCUXCLPKC_CALC_MC1_MS(MCUXCLPSADRIVER_DHM_OP_T, MCUXCLPSADRIVER_DHM_OP_T,
                                                         MCUXCLPSADRIVER_DHM_OP_N, MCUXCLPSADRIVER_DHM_OP_N),
                                   mcuxClPkc_Calc);

        /* Put the result back into the passed buffer for the shared secret. */
        MCUXCLPKC_WAITFORFINISH();
        *shared_secret_length = bytelen_n;
        reverse_and_copy(shared_secret, *shared_secret_length, pT, *shared_secret_length, *shared_secret_length);

        ret = PSA_SUCCESS;
    exit:
        if (session_initialized)
        {
            MCUXCLPKC_WAITFORREADY();
            MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClSession_cleanup(&session));
            if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != token)
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();
        }

        if (pkc_initialized)
        {
            MCUXCLPKC_WAITFORREADY();
            MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClPkc_Deinitialize(&pkc_state));
            if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) != token)
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();
        }

        return ret;
    }
    else
    {
        (void) attributes;
        (void) key_buffer;
        (void) key_buffer_size;
        (void) peer_key;
        (void) peer_key_length;
        (void) shared_secret;
        (void) shared_secret_size;
        (void) shared_secret_length;
        return PSA_ERROR_NOT_SUPPORTED;
    }
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_key_agreement(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *shared_secret,
    size_t shared_secret_size,
    size_t *shared_secret_length)
{
    psa_status_t psa_status = PSA_ERROR_NOT_SUPPORTED;
    mcuxClKey_Descriptor_t key = {0};

    psa_status = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);

    if(PSA_SUCCESS != psa_status)
    {
        return psa_status;
    }

    /* only supported for external keys */
    if( MCUXCLKEY_LOADSTATUS_COPRO != mcuxClKey_getLoadStatus(&key) )
    {
        psa_status = mcuxClPsaDriver_psa_driver_wrapper_key_agreement_internal(
            attributes,
            key.location.pData,
            key.location.length,
            alg,
            peer_key,
            peer_key_length,
            shared_secret,
            shared_secret_size,
            shared_secret_length);
    } else {
        psa_status = PSA_ERROR_NOT_SUPPORTED;
    }

    /* unload key */
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);

    /* Overwrite status only when status has no error code */
    if(PSA_SUCCESS == psa_status)
    {
        psa_status = keyStatus;
    }

    return psa_status;
}