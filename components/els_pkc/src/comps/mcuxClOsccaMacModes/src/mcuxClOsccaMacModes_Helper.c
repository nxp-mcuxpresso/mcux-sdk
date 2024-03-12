/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

/** @file  mcuxClOsccaMacModes_Helper.c
 *  @brief internal API to implement the SM4 CMAC Key generation of mcuxClOsccaMacModes component */

#include <mcuxClToolchain.h>
#include <mcuxClMac.h>
#include <mcuxClKey.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaMacModes_Internal_Functions.h>


#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_SM4_Gen_K1K2)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaMacModes_SM4_Gen_K1K2(uint8_t *output, uint8_t * input)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_SM4_Gen_K1K2);
    uint8_t mask;
    uint8_t i;

    for(i = 0u; i <= MCUXCLOSCCASM4_BLOCK_SIZE - 1u; i++)
    {
        output[i] = input[i] << 1u;
        uint8_t carryBit = input[i+1u] & 0x80u;
        if((i < MCUXCLOSCCASM4_BLOCK_SIZE - 1u) && (carryBit != 0u))
        {
           output[i] = output[i] | 0x01u;
        }
    }

    mask = ((input[0u] >> 7u) != 0u) ? 0xffu : 0x00u;
    output[ MCUXCLOSCCASM4_BLOCK_SIZE - 1u ] ^= 0x87u & mask;

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaMacModes_SM4_Gen_K1K2);
}
#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */

