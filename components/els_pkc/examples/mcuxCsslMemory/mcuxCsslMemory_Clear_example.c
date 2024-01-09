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

/** @file  csslMemory_Clear_example.c
 *  @brief Example constant-time memory clear (CSSL component mcuxCsslMemory) */

#include <mcuxCsslMemory.h>
#include <mcuxCsslMemory_Examples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslFlowProtection_FunctionIdentifiers.h>
#include <mcuxCsslParamIntegrity.h>

MCUXCSSL_MEMORY_EX_FUNCTION(mcuxCsslMemory_Clear_example)
{
  /* Define data array */
  uint8_t arr[] = {0xe4u, 0xf9u, 0x26u, 0x4cu, 0x65u, 0xe2u, 0x13u, 0xa3u,
                   0x9au, 0x40u, 0xd7u, 0x87u, 0xccu, 0x0bu, 0x31u, 0x18u,
                   0xacu, 0x55u, 0xb5u, 0x7du, 0x06u, 0x7fu, 0xceu, 0xe4u,
                   0xb2u, 0x7eu, 0xd5u, 0xaau, 0x90u, 0x9au, 0x42u, 0x56u,
                   0x76u};

  /* Clear whole array => should return success */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(clearResult, clearToken, mcuxCsslMemory_Clear(
  /*  mcuxCsslParamIntegrity_Checksum_t chk */ mcuxCsslParamIntegrity_Protect(3u, arr, sizeof(arr), sizeof(arr)),
  /*  void * pDst                          */ arr,
  /*  size_t dstLength                     */ sizeof(arr),
  /*  size_t length                        */ sizeof(arr)
  ));

  /* Check the return code of mcuxCsslMemory_Clear */
  if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Clear) != clearToken) || (MCUXCSSLMEMORY_STATUS_OK != clearResult))
  {
    return MCUXCSSLMEMORY_EX_ERROR;
  }

  MCUX_CSSL_FP_FUNCTION_CALL_END();


  return MCUXCSSLMEMORY_EX_OK;
}
