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

#include <internal/mcuxClCipherModes_Helper.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_MemClear)
void mcuxClCipherModes_MemClear(uint8_t *pDst, uint32_t length)
{
  for (uint32_t i = 0u; i < length; ++i)
  {
    pDst[i] = 0u;
  }
}
