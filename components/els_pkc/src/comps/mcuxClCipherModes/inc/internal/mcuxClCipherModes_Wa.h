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

#ifndef MCUXCLCIPHERMODES_WA_H_
#define MCUXCLCIPHERMODES_WA_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <mcuxClAes.h>
#include <mcuxClCore_Platform.h>
#include <internal/mcuxClCipher_Internal_Constants.h>
#include <mcuxClCipher_Types.h>
#include <internal/mcuxClAes_Wa.h>
//#include <internal/mcuxClCipher_Internal_Types.h>

/* TODO CLNS-5399: this is AES SGI specific, rework WA */
typedef struct mcuxClCipherModes_WorkArea
{
  uint8_t paddingBuff[MCUXCLAES_BLOCK_SIZE];
  uint32_t *pIV;
} mcuxClCipherModes_WorkArea_t;


#endif /* MCUXCLCIPHERMODES_WA_H_ */
