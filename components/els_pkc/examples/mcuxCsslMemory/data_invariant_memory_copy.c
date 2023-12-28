/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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

/** @file  data_invariant_memory_copy.c
 *  @brief Example constant-time memory copy (CSSL component mcuxCsslMemory) */

#include <stdbool.h>
#include <stdint.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslMemory_Examples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslFlowProtection_FunctionIdentifiers.h>
#include <mcuxCsslParamIntegrity.h>

#define EXIT_CODE_ERROR false   ///< example return code in case an error occurred
#define EXIT_CODE_OK    true    ///< example return code in case of successful operation

bool data_invariant_memory_copy(void)
{   
    /* Define data arrays */
    uint8_t arr1[] = {0xe4u, 0xf9u, 0x26u, 0x4cu, 0x65u, 0xe2u, 0x13u, 0xa3u,
                      0x9au, 0x40u, 0xd7u, 0x87u, 0xccu, 0x0bu, 0x31u, 0x18u,
                      0xacu, 0x55u, 0xb5u, 0x7du, 0x06u, 0x7fu, 0xceu, 0xe4u,
                      0xb2u, 0x7eu, 0xd5u, 0xaau, 0x90u, 0x9au, 0x42u, 0x56u,
                      0x76u};

    uint8_t arr2[sizeof(arr1)] = {0u};


    /* Provoke buffer overflow => should return invalid parameter error */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(copyResult, copyToken, mcuxCsslMemory_Copy(
    /*  mcuxCsslParamIntegrity_Checksum_t chk,*/ mcuxCsslParamIntegrity_Protect(4u, arr1, arr2, sizeof(arr1), sizeof(arr1) + 1u),
    /*  void const * src,                    */ arr1,
    /*  void * dst,                          */ arr2,
    /*  size_t dstLength,                    */ sizeof(arr1),
    /*  size_t length                        */ sizeof(arr1) + 1u));
    
    /* Check the return code of mcuxCsslMemory_Copy */
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy) != copyToken) || (MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER != copyResult))
    {
        return EXIT_CODE_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Try to copy nothing (length = 0 bytes) => should return invalid parameter error */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(copyResult1, copyToken1, mcuxCsslMemory_Copy(
    /*  mcuxCsslParamIntegrity_Checksum_t chk,*/ mcuxCsslParamIntegrity_Protect(4u, arr1, arr2, sizeof(arr1), 0u),
    /*  void const * src,                    */ arr1,
    /*  void * dst,                          */ arr2,
    /*  size_t dstLength,                    */ sizeof(arr1),
    /*  size_t length                        */ 0u));
    
    /* Check the return code of mcuxCsslMemory_Copy */
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy) != copyToken1) || (MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER != copyResult1))
    {
        return EXIT_CODE_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* Copy arr1 to arr2 => should return success */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(copyResult2, copyToken2, mcuxCsslMemory_Copy(
    /*  mcuxCsslParamIntegrity_Checksum_t chk,*/ mcuxCsslParamIntegrity_Protect(4u, arr1, arr2, sizeof(arr1), sizeof(arr1)),
    /*  void const * src,                    */ arr1,
    /*  void * dst,                          */ arr2,
    /*  size_t dstLength,                    */ sizeof(arr1),
    /*  size_t length                        */ sizeof(arr1)));
    
    /* Check the return code of mcuxCsslMemory_Copy */
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy) != copyToken2) || (MCUXCSSLMEMORY_STATUS_OK != copyResult2))
    {
        return EXIT_CODE_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();


    /* No error occurred during execution, exit with EXIT_CODE_OK */
    return EXIT_CODE_OK;
}
