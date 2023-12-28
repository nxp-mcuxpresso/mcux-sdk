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

#ifndef MCUXCLMACMODES_INTERNAL_CONSTANTS_H_
#define MCUXCLMACMODES_INTERNAL_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Constants.h>
#include <mcuxClAes_Constants.h>

#define MCUXCLMACMODES_XCBCMAC_SUBKEY_KEY_2_INDEX  (0u)
#define MCUXCLMACMODES_XCBCMAC_SUBKEY_KEY_3_INDEX  (1u)

#define MCUXCLMACMODES_SUBKEY_WORD_SIZE            (4u)

#define MCUXCLMACMODES_COMPARE_OK         (0xA5A5A5A5u)
#define MCUXCLMACMODES_COMPARE_NOT_OK     (0x5A5A5A5Au)

#define MCUXCLMACMODES_TRUE               (0xA5A5A5A5u)
#define MCUXCLMACMODES_FALSE              (0x5A5A5A5Au)


#endif /* MCUXCLMACMODES_INTERNAL_CONSTANTS_H_ */
