/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/**
 * @file: mcuxClOsccaSm2_Helper.c
 * @brief: OSCCA SM2 Helper functions
 */

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxCsslMemory.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>
#include <internal/mcuxClBuffer_Internal.h>

/**********************************************************
 * Helper functions
 **********************************************************/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Import)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_Import(
        uint32_t operandIndex,
        mcuxCl_InputBuffer_t pSrc,
        uint32_t length,
        uint32_t buffLen UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Import);
    const uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pDst = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[operandIndex]);

    /* clear the extra buffer */
    if (operandSize != length)
    {
        MCUXCLOSCCAPKC_FXIOP1_XOR(operandIndex, TI_const0, TI_const0);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read_reverse(pSrc, 0u, pDst, length));
    (void)readStatus;

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_Import,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                         MCUX_CSSL_FP_CONDITIONAL((operandSize != length),
                                                                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_SecureImport)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_SecureImport(
        uint32_t operandIndex,
        mcuxCl_InputBuffer_t pSrc,
        uint32_t length,
        uint32_t buffLen UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_SecureImport);
    const uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pDst = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[operandIndex]);

    /* clear the extra buffer */
    if (operandSize != length)
    {
        MCUXCLOSCCAPKC_FXIOP1_XOR(operandIndex, TI_const0, TI_const0);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read_secure_reverse(pSrc, 0u, pDst, length));
    (void)readStatus;

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_SecureImport,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                         MCUX_CSSL_FP_CONDITIONAL((operandSize != length),
                                                                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_secure_reverse));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Export)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_Export(
        uint32_t operandIndex,
        mcuxCl_Buffer_t pDst, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Export);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pSrc = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[operandIndex]);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write_reverse(pDst, 0u, pSrc, length));
    (void)writeStatus;

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_Export,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_reverse));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_SecureExport)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_SecureExport(
        uint32_t operandIndex,
        mcuxCl_Buffer_t pDst, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_SecureExport);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pSrc = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[operandIndex]);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write_secure_reverse(pDst, 0u, pSrc, length));
    (void)writeStatus;

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_SecureExport,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_secure_reverse));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_RobustCompareBoolean) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_RobustCompareBoolean(uint8_t const *pTgt, uint8_t const *pSrc,  uint32_t len)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_RobustCompareBoolean);
    uint32_t i = 0U;
    mcuxClOsccaSm2_Status_t ret;
    uint8_t xorValue = 0U;
    MCUX_CSSL_SC_ADD(2U * (uint32_t)pTgt + 2U * (uint32_t)pSrc + 3U * len);

    for (i = 0U; i < len; i++)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Internal caller should set len properly.")
        xorValue |= *pTgt++ ^ *pSrc++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }

    if (0U == xorValue)
    {
        ret = MCUXCLOSCCASM2_STATUS_CMP_EQUAL;
    }
    else
    {
        ret = MCUXCLOSCCASM2_STATUS_NOT_EQUAL;
    }

    MCUX_CSSL_SC_ADD((uint32_t)ret - (uint32_t)pTgt - (uint32_t)pSrc);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_RobustCompareBoolean, ret);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_RobustCompareToZero) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_RobustCompareToZero(uint8_t const *pData, uint32_t len)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_RobustCompareToZero);
    uint32_t i = 0U;
    mcuxClOsccaSm2_Status_t ret;
    uint8_t orValue = 0U;

    MCUX_CSSL_SC_ADD(2U * (uint32_t)pData + 2U * len);

    for (i = 0U; i < len; i++)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Internal caller should set len properly.")
        orValue |= *pData++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }

    if (0U == orValue)
    {
        ret = MCUXCLOSCCASM2_STATUS_CMP_EQUAL;
    }
    else
    {
        ret = MCUXCLOSCCASM2_STATUS_NOT_EQUAL;
    }

    MCUX_CSSL_SC_ADD((uint32_t)ret - (uint32_t)pData);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_RobustCompareToZero, ret);
}

