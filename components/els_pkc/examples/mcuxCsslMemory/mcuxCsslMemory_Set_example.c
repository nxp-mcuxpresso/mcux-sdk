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

/** @file  csslMemory_Set_example.c
 *  @brief Example constant-time memory set (CSSL component mcuxCsslMemory) */

#include <mcuxCsslMemory.h>
#include <mcuxCsslMemory_Examples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslFlowProtection_FunctionIdentifiers.h>
#include <mcuxCsslParamIntegrity.h>

MCUXCSSL_MEMORY_EX_FUNCTION(mcuxCsslMemory_Set_example)
{
  /* Define data array */
  uint8_t arr[33] = { 0u };

  /* Try to set nothing (length = 0 bytes) => should return invalid parameter error */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(setResult, setToken, mcuxCsslMemory_Set(
  /*  mcuxCsslParamIntegrity_Checksum_t chk */ mcuxCsslParamIntegrity_Protect(4u, arr, 42u, 0u, sizeof(arr)),
  /*  void * pDst                          */ arr,
  /*  uint8_t val                          */ 42u,
  /*  size_t length                        */ 0u,
  /*  size_t bufLength                     */ sizeof(arr)
  ));

  /* Check the return code of mcuxCsslMemory_Set */
  if(((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Set) != setToken)) || (MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER != setResult))
  {
    return MCUXCSSLMEMORY_EX_ERROR;
  }

  MCUX_CSSL_FP_FUNCTION_CALL_END();

  /* Try to call the function with NULL as destination => should return invalid parameter error */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(setResult1, setToken1, mcuxCsslMemory_Set(
  /*  mcuxCsslParamIntegrity_Checksum_t chk */ mcuxCsslParamIntegrity_Protect(4u, NULL, 42u, sizeof(arr), sizeof(arr)),
  /*  void * pDst                          */ NULL,
  /*  uint8_t val                          */ 42u,
  /*  size_t length                        */ sizeof(arr),
  /*  size_t bufLength                     */ sizeof(arr)
  ));

  /* Check the return code of mcuxCsslMemory_Set */
  if(((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Set) != setToken1)) || (MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER != setResult1))
  {
    return MCUXCSSLMEMORY_EX_ERROR;
  }

  MCUX_CSSL_FP_FUNCTION_CALL_END();

  /* Set all bytes in the buffer to 42 => should return success */
  MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(setResult2, setToken2, mcuxCsslMemory_Set(
  /*  mcuxCsslParamIntegrity_Checksum_t chk */ mcuxCsslParamIntegrity_Protect(4u, arr, 42u, sizeof(arr), sizeof(arr)),
  /*  void * pDst                          */ arr,
  /*  uint8_t val                          */ 42u,
  /*  size_t length                        */ sizeof(arr),
  /*  size_t bufLength                     */ sizeof(arr)
  ));

  /* Check the return code of mcuxCsslMemory_Set */
  if(((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Set) != setToken2)) || (MCUXCSSLMEMORY_STATUS_OK != setResult2))
  {
    return MCUXCSSLMEMORY_EX_ERROR;
  }

  MCUX_CSSL_FP_FUNCTION_CALL_END();

  return MCUXCSSLMEMORY_EX_OK;
}
